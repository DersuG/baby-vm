#ifndef VM_H
#define VM_H

#include <stdint.h>

#define vm_byte uint8_t
#define VM_BYTE_MAX UINT8_MAX

#define vm_word uint16_t
#define VM_WORD_MAX UINT16_MAX

#define VM_MEMORY_SIZE ((uint_least32_t) VM_WORD_MAX + 1)

/* Add 2 bytes using 2's compliment representation.
 * Wraps properly on overflow. */
vm_byte
vm_byte_2c_add (vm_byte a, vm_byte b);

/* Subtract 2 bytes using 2's compliment representation.
 * Wraps properly on overflow. */
vm_byte
vm_byte_2c_subtract (vm_byte a, vm_byte b);

/* Add 2 bytes using binary coded decimal representation.
 * Wraps properly on overflow. */
vm_byte
vm_byte_bcd_add (vm_byte a, vm_byte b);

/* Subtract 2 bytes using binary coded decimal representation.
 * Wraps properly on overflow. */
vm_byte
vm_byte_bcd_subtract (vm_byte a, vm_byte b);

/* Add 2 words together using 2's compliment representation.
 * Wraps properly on overflow. */
vm_word
vm_word_2c_add (vm_word a, vm_word b);

/* Subtract 2 words using 2's compliment representation.
 * Wraps properly on overflow. */
vm_word
vm_word_2c_subtract (vm_word a, vm_word b);

struct vm
{
    vm_word pc;
    vm_byte sp;
    vm_byte status; /* NV-BDIZC */
    vm_byte a;
    vm_byte x;
    vm_byte y;

    vm_byte memory[VM_MEMORY_SIZE];
};

/* Initializes/resets the vm to an initial state. */
void
vm_init (struct vm *vm);

/* Loads an array of vm_byte of size VM_MEMORY_SIZE into the vm's memory. */
void
vm_memory_load (struct vm *vm, vm_byte *data);

/* ======================= */
/* arithmetic instructions */
/* ======================= */

void
vm_op_adc (struct vm *vm, vm_byte instruction);

void
vm_op_sbc (struct vm *vm, vm_byte instruction);

/* ==================== */
/* bitwise instructions */
/* ==================== */

void
vm_op_and (struct vm *vm, vm_byte instruction);

void
vm_op_ora (struct vm *vm, vm_byte instruction);

void
vm_op_eor (struct vm *vm, vm_byte instruction);

void
vm_op_asl (struct vm *vm, vm_byte instruction);

void
vm_op_lsr (struct vm *vm, vm_byte instruction);

void
vm_op_rol (struct vm *vm, vm_byte instruction);

void
vm_op_ror (struct vm *vm, vm_byte instruction);

/* =============== */
/* BIT instruction */
/* =============== */

void
vm_op_bit (struct vm *vm, vm_byte instruction);

/* =================== */
/* branch instructions */
/* =================== */

void
vm_op_bpl (struct vm *vm, vm_byte instruction);

void
vm_op_bmi (struct vm *vm, vm_byte instruction);

void
vm_op_bvc (struct vm *vm, vm_byte instruction);

void
vm_op_bvs (struct vm *vm, vm_byte instruction);

void
vm_op_bcc (struct vm *vm, vm_byte instruction);

void
vm_op_bcs (struct vm *vm, vm_byte instruction);

void
vm_op_bne (struct vm *vm, vm_byte instruction);

void
vm_op_beq (struct vm *vm, vm_byte instruction);

/* =============== */
/* BRK instruction */
/* =============== */

void
vm_op_brk (struct vm *vm, vm_byte instruction);

/* ======================= */
/* comparison instructions */
/* ======================= */

void
vm_op_cmp (struct vm *vm, vm_byte instruction);

void
vm_op_cpx (struct vm *vm, vm_byte instruction);

void
vm_op_cpy (struct vm *vm, vm_byte instruction);

/* =============== */
/* DEC instruction */
/* =============== */

void
vm_op_dec (struct vm *vm, vm_byte instruction);

/* ================= */
/* flag instructions */
/* ================= */

void
vm_op_clc (struct vm *vm, vm_byte instruction);

void
vm_op_sec (struct vm *vm, vm_byte instruction);

void
vm_op_cli (struct vm *vm, vm_byte instruction);

void
vm_op_sei (struct vm *vm, vm_byte instruction);

void
vm_op_clv (struct vm *vm, vm_byte instruction);

void
vm_op_cld (struct vm *vm, vm_byte instruction);

void
vm_op_sed (struct vm *vm, vm_byte instruction);

/* =============== */
/* INC instruction */
/* =============== */

void
vm_op_inc (struct vm *vm, vm_byte instruction);

/* =============== */
/* JMP instruction */
/* =============== */

void
vm_op_jmp (struct vm *vm, vm_byte instruction);

/* =============== */
/* JSR instruction */
/* =============== */

void
vm_op_jsr (struct vm *vm, vm_byte instruction);

/* ================= */
/* load instructions */
/* ================= */

void
vm_op_lda (struct vm *vm, vm_byte instruction);

void
vm_op_ldx (struct vm *vm, vm_byte instruction);

void
vm_op_ldy (struct vm *vm, vm_byte instruction);

/* ================== */
/* store instructions */
/* ================== */

void
vm_op_sta (struct vm *vm, vm_byte instruction);

void
vm_op_stx (struct vm *vm, vm_byte instruction);

void
vm_op_sty (struct vm *vm, vm_byte instruction);

/* =============== */
/* NOP instruction */
/* =============== */

void
vm_op_nop (struct vm *vm, vm_byte instruction);

/* ===================== */
/* transfer instructions */
/* ===================== */

void
vm_op_tax (struct vm *vm, vm_byte instruction);

void
vm_op_txa (struct vm *vm, vm_byte instruction);

void
vm_op_tay (struct vm *vm, vm_byte instruction);

void
vm_op_tya (struct vm *vm, vm_byte instruction);

/* =============================== */
/* register increment instructions */
/* =============================== */

void
vm_op_inx (struct vm *vm, vm_byte instruction);

void
vm_op_iny (struct vm *vm, vm_byte instruction);

/* =============================== */
/* register decrement instructions */
/* =============================== */

void
vm_op_dex (struct vm *vm, vm_byte instruction);

void
vm_op_dey (struct vm *vm, vm_byte instruction);

/* =================== */
/* return instructions */
/* =================== */

void
vm_op_rti (struct vm *vm, vm_byte instruction);

void
vm_op_rts (struct vm *vm, vm_byte instruction);

/* ================== */
/* stack instructions */
/* ================== */

void
vm_op_txs (struct vm *vm, vm_byte instruction);

void
vm_op_tsx (struct vm *vm, vm_byte instruction);

void
vm_op_pha (struct vm *vm, vm_byte instruction);

void
vm_op_pla (struct vm *vm, vm_byte instruction);

void
vm_op_php (struct vm *vm, vm_byte instruction);

void
vm_op_plp (struct vm *vm, vm_byte instruction);

#endif /* VM_H */

