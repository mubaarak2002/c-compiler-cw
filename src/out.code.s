.text
.globl f

f:
add t0, a0, a1
li t0, -1
mul t0, t0, t0
add t0, t0, a0
seqz t0, t0
add s0, t0, zero
add a0, s0, zero
ret
