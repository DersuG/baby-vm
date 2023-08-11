#include <stdio.h>
#include <assert.h>
#include "../vm.h"

void
test (word_t initial_address, word_t target_address)
{
    struct VM vm;
    vm_reset (&vm);
    for (size_t i = 0; i < sizeof (target_address); i++)
    {
        byte_t b = (target_address >> (8 * i)) & 0xFFu;
        vm_memory_write_byte (&vm, word_t_add (initial_address, (word_t) i), b);
    }

    vm.program_counter = initial_address;

    assert (vm_op_jmp (&vm) == VM_STATUS_OK);
    assert (vm.status == VM_STATUS_OK);
    assert (vm.program_counter == target_address);
}

int
main (void)
{
    test (0x0000u, 0x0000u);
    test (0x0000u, 0x00ffu);
    test (0x0000u, WORD_T_MAX);
    test (0xff00u, WORD_T_MAX);
    test (0xff00u, 0x0000u);
    test (0xff00u, 0x00ffu);
    test (WORD_T_MAX, 0xff00u);
    test (WORD_T_MAX - 1, 0xff00u);

    return 0;
}
