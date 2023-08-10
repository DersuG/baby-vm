#include <stdio.h>
#include <assert.h>
#include "../vm.h"

void
test (word_t a, word_t b, word_t expected_result, int expected_status)
{
    struct VM vm;
    vm_reset(&vm);

    vm.register_a = a;
    vm.register_b = b;

    assert (vm_op_sub (&vm) == expected_status);
    assert (vm.status == expected_status);
    assert (vm.register_a == expected_result);
}

int
main (void)
{
    test (1, 0, 1, VM_STATUS_OK);
    test (10, 6, 4, VM_STATUS_OK);
    test (10, 11, 0, VM_STATUS_OVERFLOW);
    test (0, 1, WORD_T_MAX, VM_STATUS_OVERFLOW);
    test (0, WORD_T_MAX, 1, VM_STATUS_OVERFLOW);

    return 0;
}
