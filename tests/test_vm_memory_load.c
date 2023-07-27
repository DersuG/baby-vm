#include <stdio.h>
#include <assert.h>
#include "../vm.h"

int
main (void)
{
    struct VM vm;
    byte_t rom[VM_MEMORY_SIZE];

    /* clear memory */
    for (size_t i = 0; i < sizeof (rom); i++)
    {
        rom[i] = 0;
    }
    
    /* apply some chaos */
    for (size_t i = 0; i < sizeof (rom); i++)
    {
        rom[i] = 0;
    }
    for (size_t i = 0; i < sizeof (rom); i += 3)
    {
        rom[i] = 0x03u;
    }
    for (size_t i = 8; i < sizeof (rom); i += 8)
    {
        if (rom[i] == 0)
        {
            rom[i] = 8;
        }
        rom[i] *= 8;
    }

    /* test */
    vm_memory_load (&vm, rom);
    for (size_t i = 0; i < sizeof (rom); i++)
    {
        assert (vm.memory[i] == rom[i]);
    }

    return 0;
}
