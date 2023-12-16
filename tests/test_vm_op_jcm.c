#include <stdio.h>
#include <assert.h>
#include "../vm.h"

void
test (
    word_t initial_address,
    word_t lt_address, word_t eq_address, word_t gt_address,
    word_t register_a, word_t register_b)
{
    struct VM vm;
    vm_reset (&vm);

    vm.register_a = register_a;
    vm.register_b = register_b;
    vm.program_counter = initial_address;

    /* TODO: create vm_memory_write_word */
}

int
main (void)
{
    assert (1);

    return 0;
}
