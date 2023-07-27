#include <stdio.h>
#include <assert.h>
#include "../vm.h"

int
main (void)
{
    /* sanity checks */
    assert (word_t_add (0, 0) == 0);
    assert (word_t_add (0, 1) == 1);
    assert (word_t_add (1, 1) == 2);

    /* test overflows */
    assert (word_t_add (0, WORD_T_MAX) == WORD_T_MAX);
    assert (word_t_add (WORD_T_MAX, 0) == WORD_T_MAX);
    assert (word_t_add (1, WORD_T_MAX) == 0);
    assert (word_t_add (WORD_T_MAX, 1) == 0);
    assert (word_t_add (2, WORD_T_MAX) == 1);
    assert (word_t_add (WORD_T_MAX, 2) == 1);
    assert (word_t_add (WORD_T_MAX, WORD_T_MAX) == WORD_T_MAX - 1);

    return 0;
}
