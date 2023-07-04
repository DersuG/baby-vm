# baby-vm

A toy vm implemented in c.
Made as a learning exercise.

## Architecture

- byte size: 8 bits
- word size: 2 bytes
- little-endian
- 2 registers (A and B)

## TODO

- decide opcodes + instruction format
- bitwise ops
- register ops (swap, copy, load)
- conditional jumps (a single 3-way jump instruction would be cool)
- control ops (nop, halt)
- vm control (reset, load program)
- input (map latest keypress to a memory location)
- output (dedicated print op)

## Future TODO

- simulate cpu cycles?
- drawing to screen?
