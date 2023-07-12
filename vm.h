#ifndef VM_H
#define VM_H

#include <stdio.h>
#include <stdint.h>

/* Prints up to size_t bytes in binary, doesn't account for endianness. */
void
print_binary (void *data, size_t bytes);

typedef uint8_t byte_t;
#define BYTE_T_MAX UINT8_MAX

typedef uint16_t word_t;
#define WORD_T_MAX UINT16_MAX
#define VM_MEMORY_SIZE ((uint_least16_t) WORD_T_MAX + 1)

/* Add 2 `word_t` values together. If this would overflow, the result will be
   properly wrapped around. */
word_t
word_t_add (word_t a, word_t b);

#define VM_STATUS_OK 0            /* nothing */
#define VM_STATUS_OVERFLOW 1      /* any operation overflows */

struct VM
{
    word_t program_counter; /* "address" (index) of current instruction byte*/
    word_t status;          /* status register */
    word_t register_a;      /* user register A */
    word_t register_b;      /* user register B */

    byte_t memory[VM_MEMORY_SIZE];
};

/* resets the vm to an initial state */
void
vm_reset (struct VM *vm);

/* Dumps a vm's registers to stdout. */
void
vm_print (struct VM *vm);

/* Reads a byte from memory. Sets and returns status codes:
   - `VM_STATUS_OK` if ok */
int
vm_memory_read_byte (struct VM *vm, word_t address, byte_t *result);

/* Writes a byte from memory. Sets and returns status codes:
   - `VM_STATUS_OK` if ok */
int
vm_memory_write_byte (struct VM *vm, word_t address, byte_t data);

/* Reads a word from memory. Sets and returns status codes:
   - `VM_STATUS_OK` if ok */
int
vm_memory_read_word (struct VM *vm, word_t address, word_t *result);

/* Increases the program counter by some amount. If it overflows, it will wrap
   around properly. */
void
vm_program_counter_add (struct VM *vm, word_t amount);

/* Load A
   Uses the next 2 bytes after the instruction as an absolute address,
   (little-endian) and loads the byte at that location into register A.
   Sets and returns status codes:
   - `VM_STATUS_OK` if ok */
int
vm_op_lda (struct VM *vm);

/* Load B
   Uses the next 2 bytes after the instruction as an absolute address,
   (little-endian) and loads the byte at that location into register B.
   Sets and returns status codes:
   - `VM_STATUS_OK` if ok */
int
vm_op_ldb (struct VM *vm);

/* Load Word A
   Uses the next 2 bytes after the instruction as an absolute address,
   (little-endian) and loads the word at that location into register A
   (also little-endian).
   Sets and returns status codes:
   - `VM_STATUS_OK` if ok */
int
vm_op_lwa (struct VM *vm);

/* Load Word B
   Uses the next 2 bytes after the instruction as an absolute address,
   (little-endian) and loads the word at that location into register B
   (also little-endian).
   Sets and returns status codes:
   - `VM_STATUS_OK` if ok */
int
vm_op_lwb (struct VM *vm);

/* Add
   Adds registers A and B, storing to A.
   Sets and returns status codes:
   - `VM_STATUS_OK` if ok,
   - `VM_STATUS_OVERFLOW` if addition overflows */
int
vm_op_add (struct VM *vm);

/* Subtract
   Subtracts register B from A, storing to A.
   Sets and returns status codes:
   - `VM_STATUS_OK` if ok,
   - `VM_STATUS_OVERFLOW` if subtraction overflows */
int
vm_op_sub (struct VM *vm);

/* Unconditional Jump
   Uses the next 2 bytes after the instruction as an absolute address, and sets
   the program counter to it.
   Sets and returns status codes:
   - `VM_STATUS_OK` if ok */
int
vm_op_jmp(struct VM *vm);

/* 3-Way Conditional Jump
   Uses the next 6 bytes after the instruction as 3 absolute addresses. If
   register A < register B, jumps to the first address. If register A ==
   register B, jumps to the second address. If register A > register B, jumps
   to the third address.
   Sets and returns status codes:
   - `VM_STATUS_OK` if ok */
int
vm_op_jcm (struct VM *vm);

#endif /* VM_H */
