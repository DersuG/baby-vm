#include "vm.h"
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <assert.h>

vm_byte
vm_byte_2c_add (vm_byte a, vm_byte b)
{
    vm_byte result = 0;

    int carry = 0;
    for (int i = 0; i < sizeof (vm_byte) * CHAR_BIT; i++)
    {
        int bit1 = a & (1 << i);
        int bit2 = b & (1 << i);

        if (bit1 ^ bit2) /* if exactly 1 bit is set */
        {
            if (carry)
            {
                carry = 1; /* 1+0+1 = 0 with carry */
            }
            else
            {
                result |= (1 << i); /* 1+0+0 = 1 without carry */
                carry = 0;
            }

        }

        else if (!bit1 && !bit2) /* if neither bit is set */
        {
            result |= (carry << i); /* 0+0+X = X without carry */
            carry = 0;
        }

        else /* if both bits are set */
        {
            result |= (carry << i); /* 1+1+X = X with carry */
            carry = 1;
        }
    }

    return result;
}

vm_byte
vm_byte_2c_subtract (vm_byte a, vm_byte b)
{
    /* take compliment of b */
    b = ~b;
    b = vm_byte_2c_add (b, 0x01u);

    return vm_byte_2c_add (a, b);
}

vm_word
vm_word_2c_add (vm_word a, vm_word b)
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
vm_word_2c_subtract (vm_word a, vm_word b)
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

void
vm_op_adc (struct vm *vm, vm_byte instruction)
{
    /* TODO: BCD mode */
    /* see http://www.6502.org/tutorials/decimal_mode.html */


}

