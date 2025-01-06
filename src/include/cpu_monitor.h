#ifndef CPU_MONITOR_H
#define CPU_MONITOR_H

typedef int (*log_func_t)(const char *fmt, ...);
void set_log_function(log_func_t func);
void get_cpu_usage();

#endif
