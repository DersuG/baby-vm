#include <stdio.h>
#include <assert.h>
#include "vm.h"

void
test_vm_read_byte (byte_t *initial_memory, size_t initial_memory_size,
                   word_t initial_program_counter, byte_t expected,
                   int expected_status)
{
    struct VM vm;
    for (int i = 0; i < initial_memory_size; i++)
    {
        vm.memory[i] = initial_memory[i];
    }
    vm.program_counter = initial_program_counter;

    byte_t result;

    assert (vm_read_byte (&result, &vm) == expected_status);
    assert (vm.status == expected_status);
    if (expected_status == VM_STATUS_OK)
    {
        assert (result == expected);
        assert (vm.program_counter == initial_program_counter + 1);
    }
}

void
test_vm_read_word (byte_t *initial_memory, size_t initial_memory_size,
                   word_t initial_program_counter, word_t expected,
                   int expected_status)
{
    struct VM vm;
    for (int i = 0; i < initial_memory_size; i++)
    {
        vm.memory[i] = initial_memory[i];
    }
    vm.program_counter = initial_program_counter;

    word_t result;

    assert (vm_read_word (&result, &vm) == expected_status);
    assert (vm.status == expected_status);
    if (expected_status == VM_STATUS_OK)
    {
        assert (result == expected);
        assert (vm.program_counter == initial_program_counter + 2);
    }
}

void
test_vm_op_lda (byte_t *initial_memory, size_t initial_memory_size,
                word_t initial_program_counter, byte_t expected,
                int expected_status)
{
    struct VM vm;
    for (int i = 0; i < initial_memory_size; i++)
    {
        vm.memory[i] = initial_memory[i];
    }
    vm.program_counter = initial_program_counter;

    assert (vm_op_lda (&vm) == expected_status);
    assert (vm.status == expected_status);
    if (expected_status == VM_STATUS_OK)
    {
        assert (vm.register_a == expected);
    }
}

void
test_vm_op_ldb (byte_t *initial_memory, size_t initial_memory_size,
                word_t initial_program_counter, byte_t expected,
                int expected_status)
{
    struct VM vm;
    for (int i = 0; i < initial_memory_size; i++)
    {
        vm.memory[i] = initial_memory[i];
    }
    vm.program_counter = initial_program_counter;

    assert (vm_op_ldb (&vm) == expected_status);
    assert (vm.status == expected_status);
    if (expected_status == VM_STATUS_OK)
    {
        assert (vm.register_b == expected);
    }
}

void
test_vm_op_lwa (byte_t *initial_memory, size_t initial_memory_size,
                word_t initial_program_counter, word_t expected,
                int expected_status)
{
    struct VM vm;
    for (int i = 0; i < initial_memory_size; i++)
    {
        vm.memory[i] = initial_memory[i];
    }
    vm.program_counter = initial_program_counter;

    assert (vm_op_lwa (&vm) == expected_status);
    assert (vm.status == expected_status);
    if (expected_status == VM_STATUS_OK)
    {
        assert (vm.register_a == expected);
    }
}

void
test_vm_op_lwb (byte_t *initial_memory, size_t initial_memory_size,
                word_t initial_program_counter, word_t expected,
                int expected_status)
{
    struct VM vm;
    for (int i = 0; i < initial_memory_size; i++)
    {
        vm.memory[i] = initial_memory[i];
    }
    vm.program_counter = initial_program_counter;

    assert (vm_op_lwb (&vm) == expected_status);
    assert (vm.status == expected_status);
    if (expected_status == VM_STATUS_OK)
    {
        assert (vm.register_b == expected);
    }
}

void
test_vm_op_add (word_t a, word_t b, word_t expected, int expected_status)
{
    struct VM vm;
    vm.register_a = a;
    vm.register_b = b;
    
    assert (vm_op_add (&vm) == expected_status);
    assert (vm.status == expected_status);
    if (expected_status == VM_STATUS_OK)
    {
        assert (vm.register_a == expected);
    }
}

void
test_vm_op_sub (word_t a, word_t b, word_t expected, int expected_status)
{
    struct VM vm;
    vm.register_a = a;
    vm.register_b = b;

    assert (vm_op_sub (&vm) == expected_status);
    assert (vm.status == expected_status);
    if (expected_status == VM_STATUS_OK)
    {
        assert (vm.register_a == expected);
    }
}

int
main (void)
{
    {
        byte_t m1[2] = {0x00u, 0x01u};
        test_vm_read_byte (m1, 2, 0, 0x00u, VM_STATUS_OK);
        byte_t m2[2] = {0x00u, 0x01u};
        test_vm_read_byte (m2, 2, 1, 0x01u, VM_STATUS_OK);
        byte_t m4[VM_MEMORY_SIZE];
        m4[WORD_T_MAX - 1] = 0x01u;
        test_vm_read_byte (m4, VM_MEMORY_SIZE, WORD_T_MAX - 1, 0x01u, VM_STATUS_OK);
        byte_t m5[VM_MEMORY_SIZE];
        test_vm_read_byte (m5, VM_MEMORY_SIZE, WORD_T_MAX, 0x00u, VM_STATUS_END_OF_MEMORY);
    }

    {
        byte_t m1[2] = {0xcdu, 0xabu};
        test_vm_read_word (m1, 2, 0, 0xabcdu, VM_STATUS_OK);
        byte_t m2[5] = {0x00u, 0x00u, 0x00u, 0xcdu, 0xabu};
        test_vm_read_word(m2, 5, 3, 0xabcdu, VM_STATUS_OK);
        byte_t m4[VM_MEMORY_SIZE];
        m4[WORD_T_MAX - 2] = 0xcdu;
        m4[WORD_T_MAX - 1] = 0xabu;
        test_vm_read_word(m4, VM_MEMORY_SIZE, WORD_T_MAX - 2, 0xabcdu, VM_STATUS_OK);
        byte_t m5[VM_MEMORY_SIZE];
        test_vm_read_word(m5, VM_MEMORY_SIZE, WORD_T_MAX, 0x0000u, VM_STATUS_END_OF_MEMORY);
    }

    {
        byte_t m1[3] = {0x02u, 0x00u, 0xffu};
        test_vm_op_lda (m1, 3, 0, 0xffu, VM_STATUS_OK);
        byte_t m2[5] = {0x00u, 0xffu, 0x00u, 0x01u, 0x00u};
        test_vm_op_lda (m2, 5, 3, 0xffu, VM_STATUS_OK);
        byte_t m3[2] = {0x00u, 0x00u};
        test_vm_op_lda (m3, 2, 0, 0x00u, VM_STATUS_OK);
        byte_t m4[VM_MEMORY_SIZE];
        test_vm_op_lda (m4, VM_MEMORY_SIZE, WORD_T_MAX, 0x00u, VM_STATUS_END_OF_MEMORY);
    }

    {
        byte_t m1[3] = {0x02u, 0x00u, 0xffu};
        test_vm_op_ldb (m1, 3, 0, 0xffu, VM_STATUS_OK);
        byte_t m2[5] = {0x00u, 0xffu, 0x00u, 0x01u, 0x00u};
        test_vm_op_ldb (m2, 5, 3, 0xffu, VM_STATUS_OK);
        byte_t m3[2] = {0x00u, 0x00u};
        test_vm_op_ldb (m3, 2, 0, 0x00u, VM_STATUS_OK);
        byte_t m4[VM_MEMORY_SIZE];
        test_vm_op_ldb (m4, VM_MEMORY_SIZE, WORD_T_MAX, 0x00u, VM_STATUS_END_OF_MEMORY);
    }

    {
        byte_t m1[4] = {0x02u, 0x00u, 0xffu, 0xeeu};
        test_vm_op_lwa(m1, 4, 0, 0xeeffu, VM_STATUS_OK);
        byte_t m2[5] = {0x00u, 0xffu, 0xeeu, 0x01u, 0x00u};
        test_vm_op_lwa(m2, 5, 3, 0xeeffu, VM_STATUS_OK);
        byte_t m3[2] = {0x00u, 0x00u};
        test_vm_op_lwa(m3, 2, 0, 0x0000u, VM_STATUS_OK);
        byte_t m4[VM_MEMORY_SIZE];
        test_vm_op_lwa(m4, VM_MEMORY_SIZE, WORD_T_MAX, 0x0000u, VM_STATUS_END_OF_MEMORY);
        byte_t m5[VM_MEMORY_SIZE];
        for (int i = 0; i < sizeof (word_t); i++) {
            word_t mask = 0xffu << (i * 8);
            m5[i] = ((WORD_T_MAX - 1) & mask) >> (i * 8);
        }
        m5[WORD_T_MAX - 1] = 0xff;
        m5[WORD_T_MAX] = 0xee;
        test_vm_op_lwa(m5, VM_MEMORY_SIZE, 0, 0xeeffu, VM_STATUS_OK);
        byte_t m6[VM_MEMORY_SIZE];
        for (int i = 0; i < sizeof (word_t); i++) {
            word_t mask = 0xffu << (i * 8);
            m6[i] = (WORD_T_MAX & mask) >> (i * 8);
        }
        test_vm_op_lwa(m6, VM_MEMORY_SIZE, 0, 0x0000u, VM_STATUS_END_OF_MEMORY);
    }

    {
        byte_t m1[4] = {0x02u, 0x00u, 0xffu, 0xeeu};
        test_vm_op_lwb(m1, 4, 0, 0xeeffu, VM_STATUS_OK);
        byte_t m2[5] = {0x00u, 0xffu, 0xeeu, 0x01u, 0x00u};
        test_vm_op_lwb(m2, 5, 3, 0xeeffu, VM_STATUS_OK);
        byte_t m3[2] = {0x00u, 0x00u};
        test_vm_op_lwb(m3, 2, 0, 0x0000u, VM_STATUS_OK);
        byte_t m4[VM_MEMORY_SIZE];
        test_vm_op_lwb(m4, VM_MEMORY_SIZE, WORD_T_MAX, 0x0000u, VM_STATUS_END_OF_MEMORY);
        byte_t m5[VM_MEMORY_SIZE];
        for (int i = 0; i < sizeof (word_t); i++) {
            word_t mask = 0xffu << (i * 8);
            m5[i] = ((WORD_T_MAX - 1) & mask) >> (i * 8);
        }
        m5[WORD_T_MAX - 1] = 0xff;
        m5[WORD_T_MAX] = 0xee;
        test_vm_op_lwa(m5, VM_MEMORY_SIZE, 0, 0xeeffu, VM_STATUS_OK);
        byte_t m6[VM_MEMORY_SIZE];
        for (int i = 0; i < sizeof (word_t); i++) {
            word_t mask = 0xffu << (i * 8);
            m6[i] = (WORD_T_MAX & mask) >> (i * 8);
        }
        test_vm_op_lwa(m6, VM_MEMORY_SIZE, 0, 0x0000u, VM_STATUS_END_OF_MEMORY);
    }

    test_vm_op_add (0, 0, 0, VM_STATUS_OK);
    test_vm_op_add (1, 1, 2, VM_STATUS_OK);
    test_vm_op_add (WORD_T_MAX, 0, WORD_T_MAX, VM_STATUS_OK);
    test_vm_op_add (WORD_T_MAX, 1, 0, VM_STATUS_OVERFLOW);
    test_vm_op_add (WORD_T_MAX, WORD_T_MAX, 0, VM_STATUS_OVERFLOW);

    test_vm_op_sub (0, 0, 0, VM_STATUS_OK);
    test_vm_op_sub (1, 0, 1, VM_STATUS_OK);
    test_vm_op_sub (1, 1, 0, VM_STATUS_OK);
    test_vm_op_sub (WORD_T_MAX, 0, WORD_T_MAX, VM_STATUS_OK);
    test_vm_op_sub (WORD_T_MAX, WORD_T_MAX, 0, VM_STATUS_OK);
    test_vm_op_sub (0, WORD_T_MAX, 0, VM_STATUS_OVERFLOW);

    return 0;
}
