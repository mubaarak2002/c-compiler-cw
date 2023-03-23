.text
.globl f

addi t0, s0, 0
beq t0, zero, .FALSE
addi t0, s1, 0
beq t0, zero, .FALSE
li t0 ,1
j .TRUE
.FALSE:
li t0 ,0
.TRUE:
add a0, t0, zero
ret
