#include <stdio.h>
#include <assert.h>
#include "../vm.h"

int
main (void)
{
    struct VM vm;
    vm_reset(&vm);
    assert (vm.program_counter == 0);
    
    /* test adding zero */
    vm_program_counter_add(&vm, 0);
    assert (vm.program_counter == 0);

    /* test adding 1 */
    vm_program_counter_add (&vm, 1);
    assert (vm.program_counter == 1);

    /* test overflow */
    vm_program_counter_add (&vm, WORD_T_MAX);
    assert (vm.program_counter == 0);

    return 0;
}
