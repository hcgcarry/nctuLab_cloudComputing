library_FLAGS=-lpthread -lm 
CC=gcc
BIN_DIR=bin

all: 

%.o: %.c
	$(CC) -c $< -o $@ 

$(BIN_DIR)/%: %.o
	$(CC) $< -o $@ $(library_FLAGS)


#cpu_workload:cpu_workload.c $(CC) -o $@ $< $(library_FLAGS)

test_get_cpu_info:get_cpu_info
	./get_cpu_info
test_get_cpu_usage:get_cpu_usage
	./get_cpu_usage

test_cpu_workload:bin/cpu_workload
	./$(BIN_DIR)/cpu_workload

clean:
	rm -rf *.o