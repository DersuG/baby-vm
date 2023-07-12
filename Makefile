CC=gcc
CFLAGS=-g -std=c99 -Wall -Wextra -Wpedantic -Werror -fsanitize=address -fsanitize=leak -fsanitize=undefined

DEPS=vm.h
OBJS=vm.o test_vm.o

# notes:
# `$@` expands to the rule's target (before the colon)
# `$^` expands to the rule's prerequisites (after the colon)
# `$<` expands to the rule's first prerequisite (after the colon)

all: $(OBJS) test_vm.bin tests

tests: test_word_t_add.bin

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

#-------------------------------------------------------------------------------
# vm
#-------------------------------------------------------------------------------

test_vm.bin: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

#-------------------------------------------------------------------------------
# tests
#-------------------------------------------------------------------------------

test_word_t_add.bin: tests/test_word_t_add.o
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm *.o *.bin
	rm tests/*.o tests/*.bin
