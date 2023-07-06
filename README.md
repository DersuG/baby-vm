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

## TODO

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
