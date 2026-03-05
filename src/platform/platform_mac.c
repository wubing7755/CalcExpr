/**
 * @file platform_mac.c
 * @brief macOS 平台特定实现
 */

/* 
 * 定义 POSIX 特性宏以启用 usleep
 * 必须在所有 include 之前定义
 */
#define _POSIX_C_SOURCE 200809L

#include "platform.h"
#include <unistd.h>
#include <mach/mach_time.h>
#include <stdio.h>

/* ========================================================================
 * 公共函数实现
 * ======================================================================== */

int platform_init(void)
{
    /* macOS 平台初始化 - 当前无需特殊处理 */
    return 0;
}

void platform_cleanup(void)
{
    /* macOS 平台清理 - 当前无需特殊处理 */
}

const char* platform_get_name(void)
{
    return "macOS";
}

uint64_t platform_get_tick_ms(void)
{
    /* 使用 mach_absolute_time 获取高精度时间 */
    static mach_timebase_info_data_t timebase;
    uint64_t time;
    
    if (timebase.denom == 0) {
        mach_timebase_info(&timebase);
    }
    
    time = mach_absolute_time();
    
    /* 转换为毫秒 */
    return (time * timebase.numer) / (timebase.denom * 1000000);
}

void platform_sleep_ms(uint32_t ms)
{
    usleep(ms * 1000);  /* usleep 接受微秒 */
}
