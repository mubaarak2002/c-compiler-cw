.text
.globl f

f:
li t1, 0
add t0, t1, zero
beq t0, zero, ENDIF_0
j IFTRUE_0
IFTRUE_0:
li t2, 11
add a0, t2, zero
ret
j ENDIF_0
ENDIF_0:
li t3, 10
add a0, t3, zero
ret
