#include <stdio.h>
#include <assert.h>
#include "../vm.h"

void
test (word_t a, word_t b, word_t expected_sum)
{
    struct VM vm;
    vm_reset (&vm);

    vm.register_a = a;
    vm.register_b = b;

    /* if overflow should occur */
    if (expected_sum < a || expected_sum < b)
    {
        assert (vm_op_add (&vm) == VM_STATUS_OVERFLOW);
        assert (vm.status == VM_STATUS_OVERFLOW);
    }
    else
    {
        assert (vm_op_add (&vm) == VM_STATUS_OK);
        assert (vm.status == VM_STATUS_OK);
    }

    assert (vm.register_a == expected_sum);
}

int
main (void)
{
    test (0, 0, 0);
    test (1, 1, 2);
    test (WORD_T_MAX, 0, WORD_T_MAX);
    test (WORD_T_MAX, 1, 0);
    test (WORD_T_MAX, WORD_T_MAX, WORD_T_MAX - 1);

    return 0;
}
