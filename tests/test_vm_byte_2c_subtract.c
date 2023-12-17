#include <stdio.h>
#include <assert.h>
#include "../vm.h"

int
main (void)
{
    assert (vm_byte_2c_subtract (0x00u, 0x00u) == 0x00u);
    assert (vm_byte_2c_subtract (0x01u, 0x00u) == 0x01u);
    assert (vm_byte_2c_subtract (0x01u, 0x01u) == 0x01u);
    assert (vm_byte_2c_subtract (0x0Fu, 0x01u) == 0x0Eu);
    assert (vm_byte_2c_subtract (0xFFu, 0xFFu) == 0x00u);
    assert (vm_byte_2c_subtract (0x00u, 0x01u) == 0xFFu);
    assert (vm_byte_2c_subtract (0x00u, 0xFFu) == 0xFEu);

    return 0;
}

