/**
 * @file lexer.c
 * @brief 词法分析器实现
 *
 * ## 模块职责
 *
 * 词法分析器（lexer_t）将输入字符串分解为词素（token_t）序列。
 * 它是编译器前端的第一个阶段，位于语法分析之前。
 *
 * ## 核心概念
 *
 * ### 预读模式
 * - 每次调用 lexer_next_token() 获取下一个 token_t
 * - 当前 token_t 存储在 lexer->current 中
 * - 使用预读模式便于处理二元运算符判断
 *
 * ### token_t
 * - NUMBER : 数字常量（整数、小数、科学计数法）
 * - PLUS/MINUS/MUL/DIV : 算术运算符
 * - LPAREN/RPAREN : 左右括号
 * - END : 输入结束标记
 * - ERROR : 错误标记
 *
 * ## 错误处理策略
 *
 * 仅记录第一个错误（first error only），避免错误信息被覆盖。
 * 错误发生时立即返回，后续调用不再处理。
 */

#include "lexer.h"

#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calculator.h"
#include "debug.h"

#if DEBUG_ENABLE

/**
 * @brief token_t 类型转字符串（用于调试输出）
 *
 * @param type token_t 类型
 * @return 字符串形式的类型名
 */
static const char *token_type_name(token_type_t type) {
    switch (type) {
    case TOKEN_NUMBER:
        return "NUM";
    case TOKEN_PLUS:
        return "PLUS";
    case TOKEN_MINUS:
        return "MINUS";
    case TOKEN_MUL:
        return "MUL";
    case TOKEN_DIV:
        return "DIV";
    case TOKEN_LPAREN:
        return "LPAREN";
    case TOKEN_RPAREN:
        return "RPAREN";
    case TOKEN_END:
        return "END";
    default:
        return "ERROR";
    }
}

#endif /* DEBUG_ENABLE */

/* ========================================================================
 * 预扫描并输出所有 token_t
 * ======================================================================== */

#if DEBUG_ENABLE

void lexer_debug_print_all(lexer_t *lexer) {
    if (g_debug_level < DEBUG_LEVEL_TRACE)
        return;

    token_type_t saved_type = lexer->current.type;
    size_t saved_start = lexer->current.start_pos;
    size_t saved_end = lexer->current.end_pos;
    calc_error_t saved_err = lexer->err;
    size_t saved_err_pos = lexer->err_pos;
    size_t saved_pos = lexer->pos;

    const char *color = g_debug_color ? DEBUG_ANSI_CYAN : "";
    const char *reset = g_debug_color ? DEBUG_ANSI_RESET : "";
    printf("%s[LEXER]%s ", color, reset);
    lexer->pos = 0;
    lexer->err = CALC_OK;

    while (1) {
        while (lexer->pos < lexer->length && isspace((unsigned char)lexer->input[lexer->pos])) {
            lexer->pos++;
        }

        if (lexer->pos >= lexer->length || lexer->input[lexer->pos] == '\0') {
            printf("%s@%zu", token_type_name(TOKEN_END), lexer->pos);
            break;
        }

        size_t start = lexer->pos;
        unsigned char c = (unsigned char)lexer->input[start];
        const char *name = NULL;

        switch (c) {
        case '+':
            name = "PLUS";
            lexer->pos++;
            break;
        case '-':
            name = "MINUS";
            lexer->pos++;
            break;
        case '*':
            name = "MUL";
            lexer->pos++;
            break;
        case '/':
            name = "DIV";
            lexer->pos++;
            break;
        case '(':
            name = "LPAREN";
            lexer->pos++;
            break;
        case ')':
            name = "RPAREN";
            lexer->pos++;
            break;
        default:
            if (isdigit(c) || (c == '.' && start + 1 < lexer->length &&
                               isdigit((unsigned char)lexer->input[start + 1]))) {
                char *endp = NULL;
                strtod(lexer->input + start, &endp);
                if (endp > lexer->input + start) {
                    name = "NUM";
                    lexer->pos = (size_t)(endp - lexer->input);
                } else {
                    lexer->pos++;
                }
            } else {
                lexer->pos++;
            }
            break;
        }

        if (name) {
            printf("%s@%zu", name, start);
            printf(" | ");
        }
    }
    printf("\n");

    lexer->current.type = saved_type;
    lexer->current.start_pos = saved_start;
    lexer->current.end_pos = saved_end;
    lexer->err = saved_err;
    lexer->err_pos = saved_err_pos;
    lexer->pos = saved_pos;
}

#endif /* DEBUG_ENABLE */

/* ========================================================================
 * 错误处理
 * ======================================================================== */

/**
 * @brief 设置词法错误状态
 *
 * 错误仅设置第一次，之后调用无效（first error only）。
 * 同时设置当前 token 为 TOKEN_ERROR 标记。
 *
 * @param lexer 词法分析器
 * @param err   错误码
 * @param pos   错误发生位置
 */
static void lexer_set_error(lexer_t *lexer, calc_error_t err, size_t pos) {
    if (lexer->err == CALC_OK) { /* 仅记录第一个错误 */
        lexer->err = err;
        lexer->err_pos = pos;
    }
    lexer->current.type = TOKEN_ERROR;
    lexer->current.value = 0.0;
    lexer->current.start_pos = pos;
    lexer->current.end_pos = pos;
}

/* ========================================================================
 * 空白字符跳过
 * ======================================================================== */

/**
 * @brief 跳过空白字符
 *
 * @param lexer 词法分析器
 */
static void lexer_skip_whitespace(lexer_t *lexer) {
    while (lexer->pos < lexer->length && isspace((unsigned char)lexer->input[lexer->pos])) {
        lexer->pos++;
    }
}

/* ========================================================================
 * 词法分析器初始化
 * ======================================================================== */

/**
 * @brief 初始化词法分析器
 *
 * 设置输入字符串并重置所有状态。
 *
 * @param lexer 词法分析器实例
 * @param input 要分析的输入字符串（不复制，仅保存指针）
 */
void lexer_init(lexer_t *lexer, const char *input) {
    lexer->input = input;
    lexer->length = strlen(input);
    lexer->pos = 0;
    lexer->err = CALC_OK;
    lexer->err_pos = 0;
    lexer->current.type = TOKEN_ERROR;
    lexer->current.value = 0.0;
    lexer->current.start_pos = 0;
    lexer->current.end_pos = 0;
}

/* ========================================================================
 * 核心：词法分析 - 读取下一个 token_t
 * ======================================================================== */

/**
 * @brief 获取下一个 token_t
 *
 * 读取并返回下一个词素。结果存储在 lexer->current 中。
 *
 * 处理流程：
 *   1. 检查是否已有错误（快速返回）
 *   2. 跳过空白字符
 *   3. 检查输入结束
 *   4. 识别运算符（+ - * / ( )）
 *   5. 识别数字（使用 strtod，支持小数和科学计数法）
 *   6. 识别非法字符
 *
 * @param lexer 词法分析器实例
 */
void lexer_next_token(lexer_t *lexer) {
    if (lexer->err != CALC_OK) {
        return;
    }

    lexer_skip_whitespace(lexer);

    if (lexer->pos >= lexer->length || lexer->input[lexer->pos] == '\0') {
        lexer->current.type = TOKEN_END;
        lexer->current.value = 0.0;
        lexer->current.start_pos = lexer->pos;
        lexer->current.end_pos = lexer->pos;
        return;
    }

    {
        const size_t start = lexer->pos;
        const unsigned char c = (unsigned char)lexer->input[start];

        switch (c) {
        case '+':
            lexer->current.type = TOKEN_PLUS;
            lexer->current.value = 0.0;
            lexer->current.start_pos = start;
            lexer->current.end_pos = start + 1;
            lexer->pos++;
            return;

        case '-':
            lexer->current.type = TOKEN_MINUS;
            lexer->current.value = 0.0;
            lexer->current.start_pos = start;
            lexer->current.end_pos = start + 1;
            lexer->pos++;
            return;

        case '*':
            lexer->current.type = TOKEN_MUL;
            lexer->current.value = 0.0;
            lexer->current.start_pos = start;
            lexer->current.end_pos = start + 1;
            lexer->pos++;
            return;

        case '/':
            lexer->current.type = TOKEN_DIV;
            lexer->current.value = 0.0;
            lexer->current.start_pos = start;
            lexer->current.end_pos = start + 1;
            lexer->pos++;
            return;

        case '(':
            lexer->current.type = TOKEN_LPAREN;
            lexer->current.value = 0.0;
            lexer->current.start_pos = start;
            lexer->current.end_pos = start + 1;
            lexer->pos++;
            return;

        case ')':
            lexer->current.type = TOKEN_RPAREN;
            lexer->current.value = 0.0;
            lexer->current.start_pos = start;
            lexer->current.end_pos = start + 1;
            lexer->pos++;
            return;

        default:
            break;
        }

        if (isdigit(c) || (c == '.' && start + 1 < lexer->length &&
                           isdigit((unsigned char)lexer->input[start + 1]))) {
            char *endp = NULL;
            errno = 0;
            const double value = strtod(lexer->input + start, &endp);

            if (endp == lexer->input + start) {
                lexer_set_error(lexer, CALC_ERROR_INVALID_CHAR, start);
                return;
            }

            if (errno == ERANGE || !isfinite(value)) {
                lexer_set_error(lexer, CALC_ERROR_NUMBER_OVERFLOW, start);
                return;
            }

            lexer->pos = (size_t)(endp - lexer->input);
            lexer->current.type = TOKEN_NUMBER;
            lexer->current.value = value;
            lexer->current.start_pos = start;
            lexer->current.end_pos = lexer->pos;
            return;
        }

        lexer->pos++;
        lexer_set_error(lexer, CALC_ERROR_INVALID_CHAR, start);
    }
}
