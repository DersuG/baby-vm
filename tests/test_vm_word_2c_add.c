#include <stdio.h>
#include <assert.h>
#include "../vm.h"

int
main (void)
{
    /* sanity checks */
    assert (vm_word_2c_add (0, 0) == 0);
    assert (vm_word_2c_add (0, 1) == 1);
    assert (vm_word_2c_add (1, 1) == 2);

    /* test overflows */
    assert (vm_word_2c_add (0, VM_WORD_MAX) == VM_WORD_MAX);
    assert (vm_word_2c_add (VM_WORD_MAX, 0) == VM_WORD_MAX);
    assert (vm_word_2c_add (1, VM_WORD_MAX) == 0);
    assert (vm_word_2c_add (VM_WORD_MAX, 1) == 0);
    assert (vm_word_2c_add (2, VM_WORD_MAX) == 1);
    assert (vm_word_2c_add (VM_WORD_MAX, 2) == 1);
    assert (vm_word_2c_add (VM_WORD_MAX, VM_WORD_MAX) == VM_WORD_MAX - 1);

    return 0;
}

