#ifndef  LOGGER_H
#define LOGGER_H

#include <stdarg.h>

typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
} LogLevel;

void logger_init(LogLevel level);
void logger_set_level(LogLevel level);
void logger_log(LogLevel level, const char* format, ...);

#endif
