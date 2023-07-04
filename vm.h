#ifndef VM_H
#define VM_H

#include <stdio.h>
#include <stdint.h>

typedef uint8_t byte_t;
#define BYTE_T_MAX UINT8_MAX

typedef uint16_t word_t;
#define WORD_T_MAX UINT16_MAX
#define VM_MEMORY_SIZE ((uint_least16_t) WORD_T_MAX + 1)

struct VM
{
    word_t program_counter;
    word_t register_a;
    word_t register_b;

    byte_t memory[VM_MEMORY_SIZE];
};

/* Prints up to size_t bytes in binary, doesn't account for endianness. */
void
print_binary (void *data, size_t bytes);

/* Reads the byte in memory pointed to by the program counter,
   then increments the program counter.
   Returns 0 instead if the program counter would overflow,
   1 otherwise. */
int
vm_read_byte (byte_t *result, struct VM *vm);

/* Reads the word in memory pointed to by the program counter,
   and loads that memory value into register A (little-endian).
   The program counter is incremented for each byte read.
   Returns 0 if the 2 bytes couldn't be loaded (program counter overflow).
   Returns 1 otherwise. */
int
vm_read_word (word_t *result, struct VM *vm);

/* Uses the next 2 bytes after the instruction as an absolute address,
   (little-endian) and loads that memory value into register A.
   Returns 0 if the 2 bytes couldn't be loaded (program counter overflow).
   Returns 1 otherwise. */
int
vm_op_lda (struct VM *vm);

/* Adds registers A and B, storing to A.
   Returns 0 on overflow, 1 otherwise. */
int
vm_op_add (struct VM *vm);

/* Subtracts register B from A, storing to A.
   Returns 0 on overflow, 1 otherwise.*/
int
vm_op_sub (struct VM *vm);

#endif /* VM_H */
