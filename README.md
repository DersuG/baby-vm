# baby-vm

A toy vm implemented in c.
Made as a learning exercise.

## Building

You will need [meson](https://mesonbuild.com/).

1. Create/setup build directory: `meson setup build`
2. Enter build directory: `cd build`
3. Compile: `meson compile`
4. Run tests: `meson test`

## Architecture

- byte size: 8 bits
- word size: 2 bytes
- little-endian
- 1-word program counter register (wraps around upon overflow)
- 1-word status register
- 2 1-word user registers (A and B)

## Instruction set

- `<byte>`: 1 byte
- `<address>`: a 1-word absolute memory address (little-endian)

| instruction/format | opcode | status codes                         | description |
|--------------------|--------|--------------------------------------|-------------|
| `lda <address>`    | `0xA1` | `VM_STATUS_OK` | loads the byte at the address into register A |
| `ldb <address>`    | `0xB1` | `VM_STATUS_OK` | loads the byte at the address into register B |
| `lwa <address>`    | `0xA2` | `VM_STATUS_OK` | loads the word at the address into register A |
| `lwb <address>`    | `0xB2` | `VM_STATUS_OK` | loads the word at the address into register B |
| `add`              | `0x10` | `VM_STATUS_OK`, `VM_STATUS_OVERFLOW` | adds register A to register B, storing result in register A |
| `sub`              | `0x11` | `VM_STATUS_OK`, `VM_STATUS_OVERFLOW` | subtracts register A to register B, storing result in register A |
| `jmp <address>`    | `0x20` | `VM_STATUS_OK`                       | unconditionally jumps to address |
| `jcm <address1> <address2> <address3>` | `0x21` | `VM_STATUS_OK`   | compares register A to register B and jumps to first address if A&lt;B, second address if A=B, and third address if A&gt;B |
| `jer <address>`    | `0x22` | `VM_STATUS_OK`                       | jumps to address if status register is not `VM_STATUS_OK` |

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
