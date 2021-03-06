library_FLAGS=-lpthread -lm 
CC=gcc
BIN_DIR=bin
flag= -g -O0

all: 

%.o: %.c
	$(CC) -c $< -o $@  $(flag)

$(BIN_DIR)/%: %.o
	$(CC) $< -o $@ $(library_FLAGS) $(flag)


#cpu_workload:cpu_workload.c $(CC) -o $@ $< $(library_FLAGS)

test_get_cpu_info:get_cpu_info
	./get_cpu_info
test_get_cpu_usage:get_cpu_usage
	./get_cpu_usage

test_cpu_workload:bin/cpu_workload
	./$(BIN_DIR)/cpu_workload

test_get_cpu_mem_io_info:bin/get_cpu_mem_io_info
	./$(BIN_DIR)/get_cpu_mem_io_info

clean:
	rm -rf bin/*

test_pro_1:bin/pro_1
	./$(BIN_DIR)/pro_1
	

test:bin/pthread_setaffinity_np_test
	./$(BIN_DIR)/pthread_setaffinity_np_test
