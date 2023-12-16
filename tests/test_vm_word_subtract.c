#include <stdio.h>
#include <assert.h>
#include "../vm.h"

int
main (void)
{
    assert (vm_word_subtract (1, 0) == 1);
    assert (vm_word_subtract (10, 20) == VM_WORD_MAX - 9);
    assert (vm_word_subtract (0, 1) == VM_WORD_MAX);
    assert (vm_word_subtract (0, VM_WORD_MAX) == 1);

    return 0;
}

