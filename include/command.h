/**
 * @file command.h
 * @brief 命令处理模块公共接口
 * 
 * ## 模块介绍
 * 
 * 这个模块负责处理控制台命令（如 quit、help 等）。
 * 与数学表达式不同，命令不需要经过词法分析和语法分析。
 * 
 * ## 支持的命令
 * 
 * | 命令          | 描述               |
 * |--------------|--------------------|
 * | quit/exit/q | 退出程序            |
 * | help         | 显示帮助信息        |
 * | show help    | 显示帮助信息        |
 * | show process | 开启计算过程显示    |
 * | hide process | 关闭计算过程显示    |
 * 
 * ## 使用流程
 * 
 * @code
 *   CommandState state;
 *   commandStateInit(&state);
 *   
 *   // 主循环中
 *   CommandResult result = commandDispatch(input, &state);
 *   if (result == COMMAND_RESULT_HANDLED) {
 *       // 命令已处理，无需计算表达式
 *   }
 *   
 *   if (state.should_exit) {
 *       // 用户请求退出
 *   }
 * @endcode
 * 
 * ## 设计要点
 * 
 * - 使用"规格表驱动"设计，易于扩展新命令
 * - 支持大小写不敏感的命令匹配
 * - 命令分词处理，支持多词命令
 */

#ifndef COMMAND_H
#define COMMAND_H

#include <stdbool.h>

/* ========================================================================
 * 类型定义
 * ======================================================================== */

/**
 * @brief 交互式输入状态
 *
 * 用于处理需要多步输入的命令交互。
 */
typedef enum {
    INPUT_MODE_NORMAL,         /**< 正常模式：表达式或命令 */
    INPUT_MODE_DEBUG_LEVEL,    /**< 等待选择调试级别 */
} InputMode;

/**
 * @brief 交互状态结构
 *
 * 当命令需要额外输入时，设置交互状态并返回提示。
 */
typedef struct {
    InputMode mode;         /**< 当前输入模式 */
    const char* prompt;    /**< 提示信息 */
} InteractiveState;

/**
 * @brief 命令状态结构
 *
 * 存储命令处理模块的运行时状态。
 */
typedef struct {
    bool show_process;           /**< 是否显示调试输出 */
    bool should_exit;           /**< 是否请求退出 */
    const char* last_input;     /**< 上一次命令输入（供处理器解析参数） */
    InteractiveState interactive; /**< 交互状态 */
} CommandState;

/**
 * @brief 命令处理结果
 * 
 * 表示 commandDispatch() 函数的返回值。
 * 
 * ## 值说明
 * 
 *   - COMMAND_RESULT_NOT_COMMAND : 输入不是命令（可能是表达式）
 *   - COMMAND_RESULT_HANDLED     : 命令已处理
 *   - COMMAND_RESULT_ERROR       : 命令处理出错
 */
typedef enum {
    COMMAND_RESULT_NOT_COMMAND = 0,  /**< 不是命令 */
    COMMAND_RESULT_HANDLED,          /**< 命令已处理 */
    COMMAND_RESULT_ERROR             /**< 命令错误 */
} CommandResult;

/* ========================================================================
 * 函数声明
 * ======================================================================== */

/**
 * @brief 初始化命令状态
 * 
 * 将状态设置为默认值：
 *   - show_process = false
 *   - should_exit = false
 * 
 * @param state 要初始化的状态指针
 */
void commandStateInit(CommandState* state);

/**
 * @brief 处理交互式输入
 *
 * 当处于交互模式时，调用此函数处理用户输入。
 *
 * @param input 用户输入
 * @param state 命令状态
 */
void commandHandleInteractive(const char* input, CommandState* state);

/**
 * @brief 分发并执行命令
 * 
 * 分析输入字符串，如果是命令则执行。
 * 
 * ## 处理流程
 * 
 *   1. 分词输入
 *   2. 检查是否可能是命令（以字母开头）
 *   3. 与命令规格表匹配
 *   4. 匹配成功则执行处理函数
 * 
 * @param input 用户输入字符串
 * @param state 命令状态指针
 * @return 命令结果
 */
CommandResult commandDispatch(const char* input, CommandState* state);

#endif  /* COMMAND_H */
