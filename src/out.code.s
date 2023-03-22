.text
.globl f

f:
j CONDITION_0
CONDITION_0:
li t1, 0
add t0, t1, zero
beq t0, zero, EXIT_0
j WHILETRUE_0
WHILETRUE_0:
j CONDITION_0
EXIT_0:
li t2, 19937
add a0, t2, zero
ret
