.text
.globl f

g:
li t1, 55
add a0, t1, zero
ret
f:
j g
ret
