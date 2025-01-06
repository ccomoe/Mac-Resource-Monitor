#include <stdarg.h> // 提供 va_list、va_start 和 va_end
#include <stdio.h>  // 提供 vprintf
#include "include/log_manager.h"

// 默认日志函数
static int default_log_function(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args); // 将日志输出到 stdout
    va_end(args);
    return 0; // 返回默认值
}

// 全局日志函数指针
static log_func_t current_log_function = default_log_function;

void set_log_function(log_func_t func) {
    current_log_function = func ? func : default_log_function; // 如果传入空指针，使用默认日志函数
}

log_func_t get_log_function() {
    return current_log_function;
}
