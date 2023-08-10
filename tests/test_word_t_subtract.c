#include <stdio.h>
#include <assert.h>
#include "../vm.h"

int
main (void)
{
    assert (word_t_subtract (1, 0) == 1);
    assert (word_t_subtract (10, 20) == WORD_T_MAX - 9);
    assert (word_t_subtract (0, 1) == WORD_T_MAX);
    assert (word_t_subtract (0, WORD_T_MAX) == 1);

    return 0;
}
