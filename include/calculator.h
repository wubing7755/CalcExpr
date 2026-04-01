/**
 * @file calculator.h
 * @brief 计算器公共接口定义
 */

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stdbool.h>
#include <stddef.h>

/* ========================================================================
 * 错误码枚举
 * ======================================================================== */

typedef enum {
  CALC_OK = 0,                 /**< 成功，无错误 */
  CALC_ERROR_NULL_EXPR,        /**< 表达式为空或 NULL */
  CALC_ERROR_INVALID_CHAR,     /**< 包含非法字符 */
  CALC_ERROR_DIV_BY_ZERO,      /**< 除数为零 */
  CALC_ERROR_UNEXPECTED_TOKEN, /**< 意外的 token */
  CALC_ERROR_MISSING_RPAREN,   /**< 缺少右括号 ) */
  CALC_ERROR_SYNTAX,           /**< 语法错误 */
  CALC_ERROR_RECURSION_LIMIT,  /**< 递归深度超限 */
  CALC_ERROR_NUMBER_OVERFLOW,  /**< 数值超出范围 */
  CALC_ERROR_LAST              /**< 错误码边界标记 */
} CalcError;

/* ========================================================================
 * 步骤回调接口
 * ======================================================================== */

/**
 * @brief 计算步骤信息
 *
 * 包含单个计算步骤的详细信息，用于调试和过程展示。
 *
 * ## 字段说明
 *
 *   - step_index : 步骤序号，从 1 开始递增
 *   - message    : 步骤描述信息（如 "2 * 3 = 6"）
 *   - elapsed_ms : 步骤耗时（毫秒），0 表示不测量
 */
typedef struct {
  unsigned step_index;          /**< 步骤序号 */
  char message[256];            /**< 步骤描述（内嵌缓冲区） */
  double elapsed_ms;            /**< 步骤耗时（毫秒） */
} CalcStepInfo;

/**
 * @brief 步骤回调函数类型
 *
 * 每执行一个计算步骤时调用，用于实现计算过程输出。
 *
 * @param user_data 用户数据（来自 CalcEvalOptions.user_data）
 * @param step      步骤信息（仅在调用期间有效）
 */
typedef void (*CalcStepCallback)(void *user_data, const CalcStepInfo *step);

/* ========================================================================
 * 评估选项结构
 * ======================================================================== */

/**
 * @brief 表达式评估选项
 *
 * 用于控制求值过程中的行为和回调。
 */
typedef struct {
  unsigned max_recursion_depth; /**< 最大递归深度（0=使用默认值 256） */
  bool measure_step_time;      /**< 是否测量每步耗时 */
  CalcStepCallback on_step;    /**< 步骤回调函数（可为 NULL） */
  void *user_data;             /**< 用户数据（传递给回调） */
} CalcEvalOptions;

/* ========================================================================
 * 公共函数声明
 * ======================================================================== */

/**
 * @brief 初始化评估选项为默认值
 *
 * @param options 要初始化的选项结构
 */
void calcEvalOptionsInit(CalcEvalOptions *options);

/**
 * @brief 评估数学表达式
 *
 * 解析并计算表达式的值。
 *
 * @param expression 要计算的数学表达式字符串
 * @param options   评估选项（可为 NULL，使用默认选项）
 * @param result    计算结果输出
 * @param err_pos   错误位置输出（可为 NULL）
 * @return 错误码，CALC_OK 表示成功
 */
CalcError evaluate(const char *expression, const CalcEvalOptions *options,
                   double *result, size_t *err_pos);

/**
 * @brief 获取错误消息
 *
 * @param err 错误码
 * @return 错误码对应的字符串描述
 */
const char *calcGetErrorMessage(CalcError err);

/**
 * @brief 获取解析器错误消息（别名）
 *
 * @param err 错误码
 * @return 错误码对应的字符串描述
 */
const char *parserGetErrorMessage(CalcError err);

#endif /* CALCULATOR_H */