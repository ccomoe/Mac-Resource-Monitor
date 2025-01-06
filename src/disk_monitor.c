#include <sys/mount.h>
#include <ncurses.h>
#include "include/disk_monitor.h"
#include "include/log_manager.h"

void get_disk_usage() {
    log_func_t log_function = get_log_function();
    
    struct statfs buf;

    // 获取磁盘信息
    if (statfs("/", &buf) != 0) {
        log_function("Error: Unable to get disk information.\n");
        return;
    }

    // 计算磁盘总空间、空闲空间和已用空间
    unsigned long long total_space = buf.f_blocks * buf.f_bsize;
    unsigned long long free_space = buf.f_bfree * buf.f_bsize;

    // 检查总空间是否为零
    if (total_space == 0) {
        log_function("Error: Total disk space is zero.\n");
        return;
    }

    unsigned long long used_space = total_space - free_space;
    float disk_usage = (float)used_space / total_space * 100.0;

    // 打印磁盘使用率
    log_function("Disk usage rate: %.2f%%\n", disk_usage);
}
