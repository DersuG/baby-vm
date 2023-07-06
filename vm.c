#include "vm.h"
#include <stdio.h>
#include <stdint.h>

/* prints 1 byte as binary (so 0xf0 becomes "11110000") */
void
print_byte_as_binary (unsigned char byte)
{
    for (char j = 7; j >= 0; j--) {
        printf ("%d", (byte >> j) & 1);
    }
}

void
print_binary (void *data, size_t bytes)
{
    unsigned char byte; /* current byte */

    for (size_t i = 0; i < bytes; i++)
    {
        if (i > 0)
        {
            printf(" ");
        }

        byte = *((unsigned char *) data + i);
        print_byte_as_binary (byte);
    }
}

void
vm_print (struct VM *vm)
{
    printf ("ic: ");
    print_binary (&vm->program_counter, sizeof (vm->program_counter));
    printf (" 0x%x %d\n", vm->program_counter, vm->program_counter);

    printf ("ra: ");
    print_binary (&vm->register_a, sizeof (vm->register_a));
    printf (" 0x%x %d\n", vm->register_a, vm->register_a);

    printf ("rb: ");
    print_binary (&vm->register_b, sizeof (vm->register_b));
    printf (" 0x%x %d\n", vm->register_b, vm->register_b);
}

int
vm_read_byte (byte_t *result, struct VM *vm)
{
    /* detect overflow */
    if (vm->program_counter >= WORD_T_MAX)
    {
        vm->status = VM_STATUS_END_OF_MEMORY;
        return VM_STATUS_END_OF_MEMORY;
    }

    *result = vm->memory[vm->program_counter];
    vm->program_counter++;

    vm->status = VM_STATUS_OK;
    return VM_STATUS_OK;
}

int
vm_read_word (word_t *result, struct VM *vm)
{
    /* reset result */
    *result = 0;

    /* get bytes (little endian) */
    for (int i = 0; i < sizeof (*result); i++)
    {
        byte_t byte;
        if (vm_read_byte (&byte, vm) == VM_STATUS_END_OF_MEMORY)
        {
            vm->status = VM_STATUS_END_OF_MEMORY;
            return VM_STATUS_END_OF_MEMORY; /* program counter overflow */
        }
        word_t shifted = (word_t) byte;
        shifted <<= i * 8;
        *result |= shifted;
    }

    vm->status = VM_STATUS_OK;
    return VM_STATUS_OK;
}

int
vm_op_lda (struct VM *vm)
{
    word_t address;
    vm->status = vm_read_word (&address, vm);
    if (vm->status != VM_STATUS_OK)
    {
        return vm->status;
    }

    vm->register_a = vm->memory[address];

    return VM_STATUS_OK;
}

int
vm_op_add (struct VM *vm)
{
    /* load 1-word address */
    word_t room = WORD_T_MAX - vm->register_a;
    if (vm->register_b > room)
    {
        vm->status = VM_STATUS_OVERFLOW;
        return VM_STATUS_OVERFLOW;
    }

    word_t result = vm->register_a + vm->register_b;
    vm->register_a = result;

    vm->status = VM_STATUS_OK;
    return VM_STATUS_OK;
}

int
vm_op_sub (struct VM *vm)
{
    /* detect overflow */
    if (vm->register_a < vm->register_b)
    {
        vm->status = VM_STATUS_OVERFLOW;
        return VM_STATUS_OVERFLOW;
    }

    word_t result = vm->register_a - vm->register_b;
    vm->register_a = result;

    vm->status = VM_STATUS_OK;
    return VM_STATUS_OK;
}
