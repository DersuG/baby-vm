#include "vm.h"
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

vm_word
vm_word_add (vm_word a, vm_word b)
{
    /* TODO: do this properly */
    uint64_t result = (uint64_t) a + (uint64_t) b;
    while (result > VM_WORD_MAX)
    {
        result -= VM_WORD_MAX;
        result--;
    }
    return result;
}

vm_word
vm_word_subtract (vm_word a, vm_word b)
{
    vm_word result = 0;
    if (a < b)
    {
        result = VM_WORD_MAX - b;
        result += a + 1;
    }
    else
    {
        result = a - b;
    }

    return result;
}

void
vm_init (struct vm *vm)
{
    vm->pc = 0x0000u;
    vm->sp = 0xFFu;
    vm->a = 0x00u;
    vm->x = 0x00u;
    vm->y = 0x00u;
    for (size_t i = 0; i < sizeof (vm->memory); i++)
    {
        vm->memory[i] = 0;
    }
}

void
vm_memory_load (struct vm *vm, vm_byte *data)
{
    for (int i = 0; i < VM_MEMORY_SIZE; i++)
    {
        vm->memory[i] = data[i];
    }
}

