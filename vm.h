#ifndef VM_H
#define VM_H

#include <stdio.h>
#include <stdint.h>

typedef uint8_t byte_t;
#define BYTE_T_MAX UINT8_MAX

typedef uint16_t word_t;
#define WORD_T_MAX UINT16_MAX
#define VM_MEMORY_SIZE ((uint_least16_t) WORD_T_MAX + 1)

#define VM_STATUS_OK 0            /* nothing */
#define VM_STATUS_OVERFLOW 1      /* any operation overflows */
#define VM_STATUS_END_OF_MEMORY 2 /* program counter reached end of memory */

struct VM
{
    word_t program_counter; /* "address" (index) of current instruction byte*/
    word_t status;          /* status register */
    word_t register_a;      /* user register A */
    word_t register_b;      /* user register B */

    byte_t memory[VM_MEMORY_SIZE];
};

/* Prints up to size_t bytes in binary, doesn't account for endianness. */
void
print_binary (void *data, size_t bytes);

/* Reads the byte in memory pointed to by the program counter,
   then increments the program counter.
   Sets and returns status codes:
   - `VM_STATUS_OK` if ok,
   - `VM_STATUS_END_OF_MEMORY` if program counter reaches end of memory */
int
vm_read_byte (byte_t *result, struct VM *vm);

/* Reads the word in memory pointed to by the program counter,
   and loads that memory value into register A (little-endian).
   Sets and returns status codes:
   - `VM_STATUS_OK` if ok,
   - `VM_STATUS_END_OF_MEMORY` if program counter reaches end of memory */
int
vm_read_word (word_t *result, struct VM *vm);

/* Uses the next 2 bytes after the instruction as an absolute address,
   (little-endian) and loads the byte at that location into register A.
   Sets and returns status codes:
   - `VM_STATUS_OK` if ok,
   - `VM_STATUS_END_OF_MEMORY` if program counter reaches end of memory */
int
vm_op_lda (struct VM *vm);

/* Uses the next 2 bytes after the instruction as an absolute address,
   (little-endian) and loads the byte at that location into register B.
   Sets and returns status codes:
   - `VM_STATUS_OK` if ok,
   - `VM_STATUS_END_OF_MEMORY` if program counter reaches end of memory */
int
vm_op_ldb (struct VM *vm);

/* Uses the next 2 bytes after the instruction as an absolute address,
   (little-endian) and loads the word at that location into register B
   (also little-endian).
   Sets and returns status codes:
   - `VM_STATUS_OK` if ok,
   - `VM_STATUS_END_OF_MEMORY` if program counter reaches end of memory,
     or if the address points to memory which can't hold a full word. */
int
vm_op_lwa (struct VM *vm);

/* Adds registers A and B, storing to A.
   Sets and returns status codes:
   - `VM_STATUS_OK` if ok,
   - `VM_STATUS_OVERFLOW` if addition overflows */
int
vm_op_add (struct VM *vm);

/* Subtracts register B from A, storing to A.
   Sets and returns status codes:
   - `VM_STATUS_OK` if ok,
   - `VM_STATUS_OVERFLOW` if subtraction overflows */
int
vm_op_sub (struct VM *vm);

#endif /* VM_H */
