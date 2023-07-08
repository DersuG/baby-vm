CC=gcc
CFLAGS=-g -std=c99 -Wall -Wextra -Wpedantic -Werror -fsanitize=address -fsanitize=leak -fsanitize=undefined

all: test_vm

test_vm: test_vm.o vm.o
	$(CC) $(CFLAGS) test_vm.o vm.o -o test_vm.out

clean:
	rm *.o *.out
