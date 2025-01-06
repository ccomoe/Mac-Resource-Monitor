#include <ncurses.h>
#include <unistd.h>
#include "include/cpu_monitor.h"
#include "include/memory_monitor.h"
#include "include/disk_monitor.h"
#include "include/log_manager.h" // 添加日志管理头文件

int main() {
    // 初始化 ncurses
    initscr();
    curs_set(0); // 隐藏光标

    // 设置日志函数为 ncurses 的 printw
    set_log_function((log_func_t)printw);

    // 检查日志函数是否成功设置
    if (!get_log_function()) {
        printw("Error: Log function not set.\n");
        refresh();
        sleep(2); // 保留错误信息 2 秒钟
        endwin(); // 结束 ncurses 模式
        return 1; // 返回非零值表示错误
    }

    // 主循环
    while (1) {
        clear(); // 清屏
        printw("System Resource Monitor:\n");

        // 调用各监控模块的函数
        get_cpu_usage();
        get_memory_usage();
        get_disk_usage();

        refresh(); // 刷新显示
        sleep(2);  // 等待 2 秒
    }

    // 结束 ncurses 模式
    endwin();
    return 0;
}
