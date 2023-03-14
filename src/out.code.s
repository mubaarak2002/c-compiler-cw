Assign: int
Variable: a
reg 8: a
reg 9: .
next: Assign: int
Variable: b
reg 8: a
reg 9: b
.text
.globl f

f:
addi  t0, zero, 0
addi  t0, t0,   5
add   a0, zero, t0
ret
