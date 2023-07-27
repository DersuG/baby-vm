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
            printf (" ");
        }

        byte = *((unsigned char *) data + i);
        print_byte_as_binary (byte);
    }
}

word_t
word_t_add (word_t a, word_t b)
{
    /* TODO: do this properly */
    uint64_t result = (uint64_t) a + (uint64_t) b;
    while (result > WORD_T_MAX)
    {
        result -= WORD_T_MAX;
        result--;
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
vm_memory_load (struct VM *vm, byte_t *data)
{
    for (int i = 0; i < VM_MEMORY_SIZE; i++)
    {
        vm->memory[i] = data[i];
    }
}

int
vm_memory_read_byte (struct VM *vm, word_t address, byte_t *result)
{
    *result = vm->memory[address];
    vm->status = VM_STATUS_OK;
    return VM_STATUS_OK;
}

int
vm_memory_write_byte (struct VM *vm, word_t address, byte_t data)
{
    vm->memory[address] = data;
    vm->status = VM_STATUS_OK;
    return VM_STATUS_OK;
}

int
vm_memory_read_word (struct VM *vm, word_t address, word_t *result)
{
    /* reset result */
    *result = 0;

    /* get bytes (little endian) */
    for (size_t i = 0; i < sizeof (*result); i++)
    {
        byte_t byte;
        vm_memory_read_byte (vm, address, &byte);
        word_t shifted = (word_t) byte;
        shifted <<= i * 8;
        *result |= shifted;

        address = word_t_add (address, 1);
    }

    vm->status = VM_STATUS_OK;
    return VM_STATUS_OK;
}

void
vm_program_counter_add (struct VM *vm, word_t amount)
{
    vm->program_counter = word_t_add (vm->program_counter, amount);
}

int
vm_op_lda (struct VM *vm)
{
    word_t address;
    vm->status = vm_memory_read_word (vm, vm->program_counter, &address);
    vm_program_counter_add (vm, sizeof (address));
    if (vm->status != VM_STATUS_OK)
    {
        return vm->status;
    }

    byte_t result;
    if (vm_memory_read_byte (vm, address, &result) != VM_STATUS_OK)
    {
        return vm->status;
    }
    vm->register_a = result;

    return VM_STATUS_OK;
}

int
vm_op_ldb (struct VM *vm)
{
    word_t address;
    vm->status = vm_memory_read_word (vm, vm->program_counter, &address);
    vm_program_counter_add (vm, sizeof (address));
    if (vm->status != VM_STATUS_OK)
    {
        return vm->status;
    }

    byte_t result;
    if (vm_memory_read_byte (vm, address, &result) != VM_STATUS_OK)
    {
        return vm->status;
    }
    vm->register_b = result;

    return VM_STATUS_OK;
}

int
vm_op_lwa (struct VM *vm)
{
    word_t address;
    vm->status = vm_memory_read_word (vm, vm->program_counter, &address);
    vm->program_counter = word_t_add (vm->program_counter, sizeof (address));
    if (vm->status != VM_STATUS_OK)
    {
        return vm->status;
    }

    vm->status = vm_memory_read_word (vm, address, &vm->register_a);
    if (vm->status != VM_STATUS_OK)
    {
        return vm->status;
    }

    return VM_STATUS_OK;
}

int
vm_op_lwb (struct VM *vm)
{
    word_t address;
    vm->status = vm_memory_read_word (vm, vm->program_counter, &address);
    vm->program_counter = word_t_add (vm->program_counter, sizeof (address));
    if (vm->status != VM_STATUS_OK)
    {
        return vm->status;
    }

    vm->status = vm_memory_read_word (vm, address, &vm->register_b);
    if (vm->status != VM_STATUS_OK)
    {
        return vm->status;
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
    vm->status = vm_memory_read_word (vm, vm->program_counter, &address);
    vm_program_counter_add (vm, sizeof (address));
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

    vm->status = vm_memory_read_word (vm, vm->program_counter, &lt_address);
    vm_program_counter_add (vm, sizeof (lt_address));
    if (vm->status != VM_STATUS_OK)
    {
        return vm->status;
    }

    vm->status = vm_memory_read_word (vm, vm->program_counter, &eq_address);
    vm_program_counter_add (vm, sizeof (eq_address));
    if (vm->status != VM_STATUS_OK)
    {
        return vm->status;
    }

    vm->status = vm_memory_read_word (vm, vm->program_counter, &gt_address);
    vm_program_counter_add (vm, sizeof (gt_address));
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
