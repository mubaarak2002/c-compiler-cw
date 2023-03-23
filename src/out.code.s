.text
.globl f

f:
li a0, 1
li a1, 2
j g
li t1, 1
li t0, -1
mul t0, t0, t1
add t0, t0, a0
seqz t0, t0
seqz t0, t0
seqz t0, t0
add a0, t0, zero
ret
