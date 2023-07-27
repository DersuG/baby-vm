#include <stdio.h>
#include <assert.h>
#include "../vm.h"

int
main (void)
{
    struct VM vm;
    vm_reset (&vm);
    assert (vm.program_counter == 0);
    assert (vm.status == VM_STATUS_OK);
    assert (vm.register_a == 0);
    assert (vm.register_b == 0);
    for (int i = 0; i < sizeof (vm.memory); i++)
    {
        assert (vm.memory[i] == 0);
    }

    return 0;
}
