#include <stdio.h>
#include <assert.h>
#include "../vm.h"

void
test (word_t address, word_t data)
{
    word_t result;
    struct VM vm;
    vm_reset(&vm);

    /* TODO: don't assume word size */

    /* write lsb */
    vm_memory_write_byte (&vm, address, (byte_t) ((data << 8) >> 8));
    
    /* write msb */
    word_t msb_address = word_t_add (address, 1);
    vm_memory_write_byte (&vm, msb_address, (byte_t) (data >> 8));

    assert (vm_memory_read_word (&vm, address, &result) == VM_STATUS_OK);
    assert (result == data);
}

int
main (void)
{
    test (0x00, 0x0000u);
    test (0x00, 0xeeffu);
    test (WORD_T_MAX, 0xeeffu);

    return 0;
}
