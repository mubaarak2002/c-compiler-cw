.text
.globl f

f:
sgt t0, a0, a1
xori t0, t0, 1
add s0, t0, zero
add a0, s0, zero
ret
