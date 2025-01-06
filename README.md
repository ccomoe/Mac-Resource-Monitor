# 系统资源监视器

## 项目介绍

本项目旨在通过 C 语言构建一个简单的系统资源监控工具，实时监测系统的 **CPU 使用率**、**内存利用率** 和 **磁盘使用率**。工具基于 `ncurses` 实现动态终端界面展示，用户可以清晰地观察系统资源的实时状态，适合用作基础系统工具开发的学习案例。

## 功能特点

1. **实时监控**
   动态显示系统的 CPU 使用率、内存利用率和磁盘使用率，每隔 2 秒刷新一次。
2. **模块化设计**
   各个功能模块独立开发，分别负责 CPU、内存和磁盘的监控功能，提升代码的可读性和可维护性。
3. **日志功能**
   提供灵活的日志函数管理机制，通过 `log_manager` 模块可以设置不同的日志输出函数（如 `ncurses` 的 `printw` 或标准输出的 `printf`）。
4. **可测试性**
   每个功能模块都提供单独的测试程序，方便开发者验证模块的独立功能和输出效果。

## 技术实现

1. **CPU 监控**
   使用 macOS 的 `host_statistics` 接口获取 CPU 的负载信息，通过计算总时间片和空闲时间片的差值，推算 CPU 使用率。
2. **内存监控**
   使用 macOS 的 `vm_statistics64` 接口获取内存的分页信息，计算总内存、已用内存和空闲内存，从而得出内存利用率。
3. **磁盘监控**
   使用 `statfs` 接口获取根目录的文件系统状态，计算磁盘的总空间、已用空间和空闲空间，进而得出磁盘使用率。
4. **终端动态显示**
   使用 `ncurses` 库提供动态终端界面，通过 `printw` 和 `refresh` 实现实时刷新效果。
5. **日志管理**
   提供可配置的日志函数接口，通过 `set_log_function` 设置日志输出目标（如终端显示或文件记录）。



## 项目结构

mac-resource-monitor/
│
├── src/                   # 源代码目录
│   ├── include/           # 头文件目录
│   │   ├── cpu_monitor.h      # CPU 监控模块头文件
│   │   ├── memory_monitor.h   # 内存监控模块头文件
│   │   ├── disk_monitor.h     # 磁盘监控模块头文件
│   │   ├── log_manager.h      # 日志管理模块头文件
│   ├── cpu_monitor.c      # CPU 监控模块
│   ├── memory_monitor.c   # 内存监控模块
│   ├── disk_monitor.c     # 磁盘监控模块
│   ├── log_manager.c      # 日志管理模块
│   ├── main.c             # 主程序
│
├── tests/                 # 测试文件目录
│   ├── test_cpu.c         # CPU 监控模块测试
│   ├── test_memory.c      # 内存监控模块测试
│   ├── test_disk.c        # 磁盘监控模块测试
│
├── Makefile               # 项目编译和测试的构建文件
└── README.md              # 项目说明文档



## 安装与使用

### 1. 环境要求

- Macos 操作系统
- GCC 编译器

### 2. 安装方式

```sh
git clone https://github.com/ccomoe/mac-resource-monitor.git
```

### 3. 如何使用

测试：

```sh
cd mac-resource-monitor
make test
./tsets/test_cpu
./tests/test_memory
./tests/test_disk
```

使用：

```sh
cd mac-resource-monitor
make all
./monitor
```

  然后就会显示如下结果：

![](https://s3.bmp.ovh/imgs/2025/01/06/619c46867500885d.png)

项目清理：

```sh
make clean
```

