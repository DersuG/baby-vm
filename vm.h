#ifndef VM_H
#define VM_H

#include <stdint.h>

#define vm_byte uint8_t
#define VM_BYTE_MAX UINT8_MAX

#define vm_word uint16_t
#define VM_WORD_MAX UINT16_MAX

#define VM_MEMORY_SIZE ((uint_least32_t) VM_WORD_MAX + 1)

/* Add 2 `vm_word` values together. If this would overflow, the result will be
   properly wrapped around. */
vm_word
vm_word_add (vm_word a, vm_word b);

/* Subtract 2 `word_t` values. If this would overflow, the result will be
   properly wrapped around. */
vm_word
vm_word_subtract (vm_word a, vm_word b);

struct vm
{
    vm_word pc;
    vm_byte sp;
    vm_byte a;
    vm_byte x;
    vm_byte y;

    vm_byte memory[VM_MEMORY_SIZE];
};

/* Initializes/resets the vm to an initial state. */
void
vm_init (struct vm *vm);

/* Loads an array of vm_byte of size VM_MEMORY_SIZE into the vm's memory. */
void
vm_memory_load (struct vm *vm, vm_byte *data);

#endif /* VM_H */

