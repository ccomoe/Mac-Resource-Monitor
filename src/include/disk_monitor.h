#ifndef DISK_MONITOR_H
#define DISK_MONITOR_H

typedef int (*log_func_t)(const char *fmt, ...); // 返回类型为 int
void set_log_function(log_func_t func);
void get_disk_usage();

#endif
