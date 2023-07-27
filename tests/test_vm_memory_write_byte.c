#include <stdio.h>
#include <assert.h>
#include "../vm.h"

void
test (word_t address, byte_t data)
{
    struct VM vm;
    vm_reset (&vm);
    assert (vm_memory_write_byte (&vm, address, data) == VM_STATUS_OK);
    assert (vm.memory[address] == data);
}

int
main (void)
{
    test (0, 0xffu);
    test (1, 0x01u);
    test (WORD_T_MAX - 1, 0xffu);
    test (WORD_T_MAX, 0x33u);

    return 0;
}
