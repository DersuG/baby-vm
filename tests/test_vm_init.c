#include <stdio.h>
#include <assert.h>
#include "../vm.h"

int
main (void)
{
    struct vm vm;
    vm_init (&vm);
    assert (vm.pc == 0x0000u);
    assert (vm.sp == 0xFFu);
    assert (vm.a == 0x00u);
    assert (vm.x == 0x00u);
    assert (vm.y == 0x00u);
    for (size_t i = 0; i < sizeof (vm.memory); i++)
    {
        assert (vm.memory[i] == 0);
    }

    return 0;
}

