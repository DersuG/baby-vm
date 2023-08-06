#include <stdio.h>
#include <assert.h>
#include "../vm.h"

void
test (word_t starting_address, word_t data_address, byte_t data)
{
    struct VM vm;
    vm_reset (&vm);
    vm.program_counter = starting_address;

    byte_t program[VM_MEMORY_SIZE];
    for (size_t i = 0; i < sizeof (program); i++)
    {
        program[i] = 0;
    }

    /* write data address at starting address */
    word_t lsb_address = starting_address;
    word_t msb_address = word_t_add (starting_address, 1);
    program[lsb_address] = (byte_t) (data_address & 0x00ffu);
    program[msb_address] = (byte_t) (data_address >> 8);

    /* write data */
    program[data_address] = data;

    /* test */
    vm_memory_load (&vm, program);
    assert (vm_op_ld (&vm, VM_REGISTER_A) == VM_STATUS_OK);
    assert (vm.register_a == data);
    assert (vm_op_ld (&vm, VM_REGISTER_B) == VM_STATUS_OK);
    assert (vm.register_b == data);
}

int
main (void)
{
    test (0x0000u, 0xff00u, 0xffu);
    test (0x0001u, 0xeeffu, 0x42u);
    test (WORD_T_MAX, 0xbeeeu, 0xaau);

    return 0;
}
