#include <stdio.h>
#include <assert.h>
#include "../vm.h"

void
test (word_t a, word_t b, word_t expected_result, int expected_status)
{
    struct VM vm;
    vm_reset (&vm);

    vm.register_a = a;
    vm.register_b = b;

    assert (vm_op_add (&vm) == expected_status);
    assert (vm.status == expected_status);
    assert (vm.register_a == expected_result);
}

int
main (void)
{
    test (0, 0, 0, VM_STATUS_OK);
    test (1, 1, 2, VM_STATUS_OK);
    test (WORD_T_MAX, 0, WORD_T_MAX, VM_STATUS_OK);
    test (WORD_T_MAX, 1, 0, VM_STATUS_OVERFLOW);
    test (WORD_T_MAX, WORD_T_MAX, WORD_T_MAX - 1, VM_STATUS_OVERFLOW);

    return 0;
}
