#include <stdio.h>
#include <stdarg.h> // 用于处理可变参数
#include <ncurses.h>
#include "../src/include/disk_monitor.h"
#include "../src/include/log_manager.h" // 包含日志管理头文件

// 自定义日志函数，用于测试
int test_log_function(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args); // 将日志输出重定向到 stdout
    va_end(args);
    return 0; // 返回符合 int 类型
}

int main() {
    printf("Testing Disk Module...\n");

    // 设置自定义日志函数
    set_log_function(test_log_function);

    // 调用磁盘监控函数
    get_disk_usage();

    printf("Disk Module Test Completed.\n");
    return 0;
}
