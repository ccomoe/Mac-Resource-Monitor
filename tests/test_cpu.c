#include <stdio.h>
#include <stdarg.h>
#include <unistd.h> // 添加此头文件以声明 sleep
#include "../src/include/cpu_monitor.h"
#include "../src/include/log_manager.h"

int test_log_function(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args); // 重定向到 stdout 进行测试输出
    va_end(args);
    return 0;
}

int main() {
    printf("Testing CPU Module...\n");

    // 设置自定义日志函数
    set_log_function(test_log_function);
    for (int i = 0; i < 5; i++) { // 多次调用模拟连续监控
        get_cpu_usage();
        sleep(1); // 等待 1 秒钟
    }

    printf("CPU Module Test Completed.\n");
    return 0;
}
