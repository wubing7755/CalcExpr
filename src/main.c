#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "calculator.h"
#include "command.h"
#include "debug.h"
#include "logger.h"
#include "platform.h"

#define INPUT_BUFFER_SIZE 1024U

typedef enum { INPUT_OK, INPUT_EOF, INPUT_TRUNCATED } input_read_status_t;

static void print_welcome(void) {
    logger_log(LOG_INFO, "===========================================\n");
    logger_log(LOG_INFO, "       C语言控制台计算器 v2.0\n");
    logger_log(LOG_INFO, "===========================================\n");
    logger_log(LOG_INFO, "支持运算: + - * / ( )\n");
    logger_log(LOG_INFO, "输入 'quit' 或 'exit' 退出程序\n\n");
}

static void print_help(void) {
    logger_log(LOG_INFO, "【使用提示】\n");
    logger_log(LOG_INFO, "- 直接输入数学表达式，例如: 2+3*4\n");
    logger_log(LOG_INFO, "- 使用括号改变优先级，例如: (2+3)*4\n");
    logger_log(LOG_INFO, "- 支持小数和科学计数法，例如: 1e-3 * 5\n\n");
    logger_log(LOG_INFO, "- 输入 /help 查看全部命令\n");
    logger_log(LOG_INFO, "- 输入 /show process 开启计算过程输出\n");
    logger_log(LOG_INFO, "- 输入 /hide process 关闭计算过程输出\n\n");
}

static input_read_status_t read_input_line(char *input, size_t capacity) {
    size_t len;
    int ch;

    if (fgets(input, (int)capacity, stdin) == NULL) {
        return INPUT_EOF;
    }

    len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        return INPUT_OK;
    }

    /* 输入过长，丢弃剩余字符直到行尾 */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        /* 丢弃超出缓冲区的字符 */
    }
    input[capacity - 1] = '\0';
    return INPUT_TRUNCATED;
}

static bool is_valid_expression(const char *input) {
    while (*input != '\0') {
        if (!isspace((unsigned char)*input)) {
            return true;
        }
        input++;
    }
    return false;
}

static void print_result(const char *expression, double result) {
    logger_log(LOG_INFO, "表达式: %s\n", expression);
    logger_log(LOG_INFO, "结果:   %.10g\n\n", result);
}

typedef enum { REPL_CONTINUE, REPL_EXIT } repl_action_t;

static void print_prompt(const command_state_t *state) {
    if (state->interactive.mode != INPUT_MODE_NORMAL &&
        state->interactive.prompt != NULL) {
        logger_log(LOG_INFO, "%s", state->interactive.prompt);
        return;
    }

    logger_log(LOG_INFO, "请输入表达式> ");
}

static bool is_command_input(const char *input) {
    return input[0] == '/';
}

/**
 * @brief 尝试将输入作为命令分发
 *
 * @param input 以 '/' 开头的命令输入
 * @param state 命令状态
 * @return true 表示命令已处理，false 表示不是命令
 */
static bool handle_command_input(const char *input, command_state_t *state) {
    const command_result_t cmd_result = command_dispatch(input + 1, state);

    if (cmd_result == COMMAND_RESULT_NOT_COMMAND) {
        return false;
    }

    if (state->should_exit) {
        logger_log(LOG_INFO, "感谢使用，再见！\n");
    }

    return true;
}

/**
 * @brief 求值表达式并输出结果或错误
 *
 * @param input 用户输入的表达式
 */
static void evaluate_and_print(const char *input) {
    double result = 0.0;
    size_t err_pos = 0;
    calc_error_t err = evaluate(input, &result, &err_pos);

    if (err == CALC_OK) {
        print_result(input, result);
        return;
    }

    if (err_pos < strlen(input)) {
        logger_log(LOG_ERROR, "错误: %s (位置: %zu, 附近: '%.16s')\n\n",
                   calc_get_error_message(err), err_pos, input + err_pos);
    } else {
        logger_log(LOG_ERROR, "错误: %s\n\n", calc_get_error_message(err));
    }
}

/**
 * @brief 处理一次 REPL 输入
 *
 * @param input        读取到的输入
 * @param input_status 读取状态
 * @param state        命令状态
 * @return REPL_EXIT 时主循环应退出，否则 REPL_CONTINUE
 */
static repl_action_t process_repl_line(const char *input,
                                       input_read_status_t input_status,
                                       command_state_t *state) {
    if (input_status == INPUT_EOF) {
        logger_log(LOG_INFO, "\n程序结束\n");
        return REPL_EXIT;
    }

    if (input_status == INPUT_TRUNCATED) {
        logger_log(LOG_ERROR, "错误: 输入长度超过 %u 字符，请缩短表达式后重试。\n\n",
                   (INPUT_BUFFER_SIZE - 1U));
        return REPL_CONTINUE;
    }

    if (!is_valid_expression(input)) {
        return REPL_CONTINUE;
    }

    if (state->interactive.mode != INPUT_MODE_NORMAL) {
        command_handle_interactive(input, state);
        return REPL_CONTINUE;
    }

    if (is_command_input(input)) {
        if (handle_command_input(input, state)) {
            if (state->should_exit) {
                return REPL_EXIT;
            }
            return REPL_CONTINUE;
        }
    }

    evaluate_and_print(input);
    return REPL_CONTINUE;
}

/* ========================================================================
 * 主程序
 * ======================================================================== */

/**
 * @brief 计算器 REPL 主循环
 *
 * 程序流程：
 *   1. 初始化（调试参数、平台、日志、命令状态）
 *   2. 显示欢迎信息和帮助
 *   3. 进入 REPL 循环：
 *      - 读取用户输入
 *      - 处理命令（以 '/' 开头）
 *      - 求值表达式
 *      - 输出结果或错误
 *   4. 清理并退出
 */
int main(int argc, char *argv[]) {
    command_state_t command_state;

    /* -------- 初始化阶段 -------- */

    /* 解析调试参数（必须在其他初始化之前） */
    debug_init(DEBUG_LEVEL_NONE, 0);
    bool debug_active = debug_parse_args(argc, argv);

    platform_init();
    platform_enable_utf8();
    logger_init(LOG_INFO);
    command_state_init(&command_state);

    if (debug_active) {
        DEBUG_INFO("调试模式已开启，级别=%d", debug_get_level());
    }

    print_welcome();
    print_help();

    /* -------- REPL 循环 -------- */

    while (true) {
        char input[INPUT_BUFFER_SIZE];
        input_read_status_t input_status;

        print_prompt(&command_state);
        input_status = read_input_line(input, sizeof(input));

        if (process_repl_line(input, input_status, &command_state) == REPL_EXIT) {
            break;
        }
    }

    /* -------- 清理阶段 -------- */

    platform_cleanup();
    return 0;
}
