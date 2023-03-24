.text
.globl f

f:
j LOOP_0
LOOP_0:
li t1, 5
slt t0, s0, t1
add t0, t0, zero
beq t0, zero, EXIT_0
j WHILETRUE_0
WHILETRUE_0:
j LOOP_0
li t2, 5
add s0, t2, zero
j LOOP_0
EXIT_0:
j LOOP_1
LOOP_1:
li t3, 5
sgt t0, s0, t3
add t0, t0, zero
beq t0, zero, EXIT_1
j WHILETRUE_1
WHILETRUE_1:
j EXIT_1
li t4, 10
add s0, t4, zero
j LOOP_1
EXIT_1:
