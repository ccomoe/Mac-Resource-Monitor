#include <mach/mach.h>
#include <ncurses.h>
#include "include/memory_monitor.h"
#include "include/log_manager.h"

void get_memory_usage() {
    log_func_t log_function = get_log_function();

    vm_size_t page_size;
    mach_port_t mach_port = mach_host_self();
    vm_statistics64_data_t vm_stats;
    mach_msg_type_number_t count = HOST_VM_INFO64_COUNT;

    // 获取内存信息
    if (host_page_size(mach_port, &page_size) != KERN_SUCCESS || 
        host_statistics64(mach_port, HOST_VM_INFO, (host_info_t)&vm_stats, &count) != KERN_SUCCESS) {
        log_function("Error: Unable to obtain memory information.\n");
        return;
    }

    // 计算总内存和已用内存
    unsigned long long total_memory = (vm_stats.wire_count + 
                                       vm_stats.active_count + 
                                       vm_stats.inactive_count + 
                                       vm_stats.free_count) * page_size;
    unsigned long long used_memory = (vm_stats.wire_count + vm_stats.active_count) * page_size;

    // 避免除以零
    if (total_memory == 0) {
        log_function("Error: Total memory is zero.\n");
        return;
    }

    // 计算内存使用率
    float memory_usage = (float)used_memory / total_memory * 100.0;
    log_function("Memory utilization: %.2f%%\n", memory_usage);
}
