sub 5 5
add 0 6
next: add 5 5
.text
.globl f

f:
addi  t0, zero, 0
addi  t0, t0,   5
add   a0, zero, t0
ret
