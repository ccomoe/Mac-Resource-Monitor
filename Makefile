CC = gcc
CFLAGS = -Wall -I./src/include
LDFLAGS = -lncurses
SRC_DIR = src
INC_DIR = src/include
TEST_DIR = tests
TARGET = monitor

OBJS = $(SRC_DIR)/main.o $(SRC_DIR)/cpu_monitor.o $(SRC_DIR)/memory_monitor.o $(SRC_DIR)/disk_monitor.o $(SRC_DIR)/log_manager.o
TESTS = $(TEST_DIR)/test_cpu $(TEST_DIR)/test_memory $(TEST_DIR)/test_disk

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJS)

$(SRC_DIR)/main.o: $(SRC_DIR)/main.c $(INC_DIR)/cpu_monitor.h $(INC_DIR)/memory_monitor.h $(INC_DIR)/disk_monitor.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o $(SRC_DIR)/main.o

$(SRC_DIR)/cpu_monitor.o: $(SRC_DIR)/cpu_monitor.c $(INC_DIR)/cpu_monitor.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/cpu_monitor.c -o $(SRC_DIR)/cpu_monitor.o

$(SRC_DIR)/memory_monitor.o: $(SRC_DIR)/memory_monitor.c $(INC_DIR)/memory_monitor.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/memory_monitor.c -o $(SRC_DIR)/memory_monitor.o

$(SRC_DIR)/disk_monitor.o: $(SRC_DIR)/disk_monitor.c $(INC_DIR)/disk_monitor.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/disk_monitor.c -o $(SRC_DIR)/disk_monitor.o

$(SRC_DIR)/log_manager.o: $(SRC_DIR)/log_manager.c $(INC_DIR)/log_manager.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/log_manager.c -o $(SRC_DIR)/log_manager.o

test: $(TESTS)

# 修改测试程序规则，确保链接到 log_manager.o
$(TEST_DIR)/test_cpu: $(SRC_DIR)/cpu_monitor.o $(SRC_DIR)/log_manager.o $(TEST_DIR)/test_cpu.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TEST_DIR)/test_cpu $(SRC_DIR)/cpu_monitor.o $(SRC_DIR)/log_manager.o $(TEST_DIR)/test_cpu.c

$(TEST_DIR)/test_memory: $(SRC_DIR)/memory_monitor.o $(SRC_DIR)/log_manager.o $(TEST_DIR)/test_memory.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TEST_DIR)/test_memory $(SRC_DIR)/memory_monitor.o $(SRC_DIR)/log_manager.o $(TEST_DIR)/test_memory.c

$(TEST_DIR)/test_disk: $(SRC_DIR)/disk_monitor.o $(SRC_DIR)/log_manager.o $(TEST_DIR)/test_disk.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TEST_DIR)/test_disk $(SRC_DIR)/disk_monitor.o $(SRC_DIR)/log_manager.o $(TEST_DIR)/test_disk.c

clean:
	rm -f $(TARGET) $(SRC_DIR)/*.o $(TESTS)
