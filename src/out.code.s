f:
li t1 7
li t2 6
add t0 t1 t2
li a0,t0
Return


.text
.globl f

f:
addi  t0, zero, 0
addi  t0, t0,   5
add   a0, zero, t0
ret
