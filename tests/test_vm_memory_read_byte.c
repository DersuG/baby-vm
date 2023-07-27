#include <stdio.h>
#include <assert.h>
#include "../vm.h"

void
rom_reset (byte_t *rom)
{
    for (int i = 0; i < VM_MEMORY_SIZE; i++)
    {
        rom[i] = 0;
    }
}

int
main (void)
{
    struct VM vm;
    byte_t rom[VM_MEMORY_SIZE];
    byte_t result;

    vm_reset (&vm);
    rom_reset (rom);
    rom[0] = 0xffu;
    vm_memory_load(&vm, rom);
    assert (vm_memory_read_byte (&vm, 0, &result) == VM_STATUS_OK);
    assert (result == 0xffu);
    
    vm_reset (&vm);
    rom_reset (rom);
    rom[10] = 0x33u;
    vm_memory_load(&vm, rom);
    assert (vm_memory_read_byte (&vm, 10, &result) == VM_STATUS_OK);
    assert (result == 0x33u);
    
    vm_reset (&vm);
    rom_reset (rom);
    rom[WORD_T_MAX] = 0x11u;
    vm_memory_load(&vm, rom);
    assert (vm_memory_read_byte (&vm, WORD_T_MAX, &result) == VM_STATUS_OK);
    assert (result == 0x11u);

    return 0;
}
