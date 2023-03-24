.text
.globl f

f:
li t0, 0b00111111100000000000000000000000
fmv.w.x ft1, t0
fadd.s fs2, ft1, ft11
li t1, 0
add s0, t1, zero
j CONDITION_0
CONDITION_0:
slt t0, s0, a0
add t0, t0, zero
beq t0, zero, EXIT_0
j WHILETRUE_0
WHILETRUE_0:
addi s0, s0, 1
fmul.s ft0, fs2, fa0
fadd.s fs2, ft0, ft11
j CONDITION_0
EXIT_0:
fadd.s fa0, fs2, ft11
ret
