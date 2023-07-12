#include "vm.h"
#include <stdio.h>
#include <stdint.h>

word_t
word_t_add (word_t a, word_t b)
{
    /* TODO: do this properly */
    uint64_t result = (uint32_t) a + (uint64_t) b;
    while (result > WORD_T_MAX)
    {
        result -= WORD_T_MAX;
    }
    return result;
}

void
vm_reset (struct VM *vm)
{
    vm->program_counter = 0;
    vm->status = VM_STATUS_OK;
    vm->register_a = 0;
    vm->register_b = 0;
    for (size_t i = 0; i < sizeof (vm->memory); i++)
    {
        vm->memory[i] = 0;
    }
}

byte_t
vm_read_memory (struct VM *vm, word_t address)
{
    return vm->memory[address];
}

void
vm_write_memory (struct VM *vm, word_t address, byte_t data)
{
    vm->memory[address] = data;
}

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

void
vm_program_counter_add (struct VM *vm, word_t amount)
{
    vm->program_counter = word_t_add(vm->program_counter, amount);
}

int
vm_read_byte (byte_t *result, struct VM *vm)
{
    *result = vm->memory[vm->program_counter];
    vm_program_counter_add(vm, 1);

    vm->status = VM_STATUS_OK;
    return VM_STATUS_OK;
}

int
vm_read_word (word_t *result, struct VM *vm)
{
    /* reset result */
    *result = 0;

    /* get bytes (little endian) */
    for (size_t i = 0; i < sizeof (*result); i++)
    {
        byte_t byte;
        vm_read_byte(&byte, vm);
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

    vm->register_a = vm_read_memory(vm, address);

    return VM_STATUS_OK;
}

int
vm_op_ldb (struct VM *vm)
{
    word_t address;
    vm->status = vm_read_word (&address, vm);
    if (vm->status != VM_STATUS_OK)
    {
        return vm->status;
    }

    vm->register_b = vm_read_memory(vm, address);

    return VM_STATUS_OK;
}

int
vm_op_lwa (struct VM *vm)
{
    word_t address;
    vm->status = vm_read_word(&address, vm);
    if (vm->status != VM_STATUS_OK)
    {
        return vm->status;
    }

    vm->register_a = 0;
    for (size_t i = 0; i < sizeof (vm->register_a); i++)
    {
        vm->register_a |= vm_read_memory(vm, address) << (i * 8);
        address = word_t_add(address, (word_t) i);
    }

    return VM_STATUS_OK;
}

int
vm_op_lwb (struct VM *vm)
{
    word_t address;
    vm->status = vm_read_word(&address, vm);
    if (vm->status != VM_STATUS_OK)
    {
        return vm->status;
    }

    vm->register_b = 0;
    for (size_t i = 0; i < sizeof (vm->register_b); i++)
    {
        vm->register_b |= vm_read_memory(vm, address) << (i * 8);
        address = word_t_add(address, (word_t) i);
    }

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

int
vm_op_jmp (struct VM *vm)
{
    word_t address;
    vm->status = vm_read_word (&address, vm);
    if (vm->status != VM_STATUS_OK)
    {
        return vm->status;
    }

    vm->program_counter = address;
    return VM_STATUS_OK;
}

int
vm_op_jcm (struct VM *vm)
{
    word_t lt_address;
    word_t eq_address;
    word_t gt_address;

    vm->status = vm_read_word (&lt_address, vm);
    if (vm->status != VM_STATUS_OK)
    {
        return vm->status;
    }

    vm->status = vm_read_word (&eq_address, vm);
    if (vm->status != VM_STATUS_OK)
    {
        return vm->status;
    }

    vm->status = vm_read_word (&gt_address, vm);
    if (vm->status != VM_STATUS_OK)
    {
        return vm->status;
    }

    if (vm->register_a < vm->register_b)
    {
        vm->program_counter = lt_address;
    }
    else if (vm->register_a == vm->register_b)
    {
        vm->program_counter = eq_address;
    }
    else
    {
        vm->program_counter = gt_address;
    }

    return VM_STATUS_OK;
}
