# baby-vm

A toy vm implemented in c.
Made as a learning exercise.

## Building

For now it's just: `gcc test_vm.c vm.c`

## Architecture

- byte size: 8 bits
- word size: 2 bytes
- little-endian
- 1-word program counter register
- 1-word status register
- 2 1-word user registers (A and B)

## Instruction set

- `<byte>`: 1 byte
- `<address>`: a 1-word absolute memory address (little-endian)

| instruction/format | status codes                              | description |
|--------------------|-------------------------------------------|-------------|
| `lda <address>`    | `VM_STATUS_OK`, `VM_STATUS_END_OF_MEMORY` | loads the byte at the address into register A |
| `ldb <address>`    | `VM_STATUS_OK`, `VM_STATUS_END_OF_MEMORY` | loads the byte at the address into register B |
| `lwa <address>`    | `VM_STATUS_OK`, `VM_STATUS_END_OF_MEMORY` | loads the word at the address into register A |
| `lwb <address>`    | `VM_STATUS_OK`, `VM_STATUS_END_OF_MEMORY` | loads the word at the address into register B |
| `add`              | `VM_STATUS_OK`, `VM_STATUS_OVERFLOW`      | adds register A to register B, storing result in register A |
| `sub`              | `VM_STATUS_OK`, `VM_STATUS_OVERFLOW`      | subtracts register A to register B, storing result in register A |

## TODO

- restructure tests
- reduce code repetition (need constants to represent registers)
- decide opcodes + instruction format
- bitwise ops
- register ops (swap, copy, load)
- jumps (3-way conditional jump, jump if error, unconditional jump)
- control ops (nop, halt)
- vm control (reset, load program)
- input (map latest keypress to a memory location)
- output (dedicated print op, custom character set)
- error handling (error codes on crash)
- add license
- makefile (or cmake?)

## TODO?

- simulate cpu cycles?
- drawing to screen?
- debug support? (no idea how this works)
- stack? (function call/return can be left up to the assembler, if i make one)
- assembler?
- high level language?
