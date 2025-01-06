#include <mach/mach.h>
#include <ncurses.h>
#include "include/cpu_monitor.h"
#include "include/log_manager.h"

void get_cpu_usage() {
    log_func_t log_function = get_log_function();

    static host_cpu_load_info_data_t previous_load = {0};
    static int is_initialized = 0; // 用于第一次运行的标志
    host_cpu_load_info_data_t current_load = {0};
    mach_msg_type_number_t count = HOST_CPU_LOAD_INFO_COUNT;

    // 获取 CPU 统计信息
    kern_return_t kr = host_statistics(mach_host_self(), HOST_CPU_LOAD_INFO, (host_info_t)&current_load, &count);
    if (kr != KERN_SUCCESS) {
        log_function("Error: Unable to obtain CPU information (error code: %d)\n", kr);
        return;
    }

    // 如果是第一次运行，初始化 previous_load
    if (!is_initialized) {
        previous_load = current_load;
        is_initialized = 1;
        log_function("CPU usage: Initialization complete.\n");
        return;
    }

    // 计算总时间片和空闲时间片
    unsigned long total_ticks = 0, idle_ticks = 0;
    for (int i = 0; i < CPU_STATE_MAX; i++) {
        total_ticks += current_load.cpu_ticks[i];
    }
    idle_ticks = current_load.cpu_ticks[CPU_STATE_IDLE];

    // 检查 total_ticks 是否为零
    if (total_ticks == 0) {
        log_function("Error: No CPU activity detected.\n");
        return;
    }

    // 计算时间差
    unsigned long previous_total = previous_load.cpu_ticks[CPU_STATE_USER] +
                                   previous_load.cpu_ticks[CPU_STATE_SYSTEM] +
                                   previous_load.cpu_ticks[CPU_STATE_NICE] +
                                   previous_load.cpu_ticks[CPU_STATE_IDLE];

    unsigned long total_diff = total_ticks - previous_total;
    unsigned long idle_diff = idle_ticks - previous_load.cpu_ticks[CPU_STATE_IDLE];

    // 检查时间差是否合理
    if (total_diff == 0 || total_diff < idle_diff) {
        log_function("Error: Insufficient data to calculate CPU usage.\n");
        return;
    }

    // 计算 CPU 使用率
    float cpu_usage = 100.0 * (total_diff - idle_diff) / total_diff;
    log_function("CPU usage: %.2f%%\n", cpu_usage);

    // 更新 previous_load
    previous_load = current_load;
}
