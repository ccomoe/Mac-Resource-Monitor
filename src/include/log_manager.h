#ifndef LOG_MANAGER_H
#define LOG_MANAGER_H

typedef int (*log_func_t)(const char *fmt, ...); // 定义日志函数类型

// 设置全局日志函数
void set_log_function(log_func_t func);

// 获取当前全局日志函数
log_func_t get_log_function();

#endif
