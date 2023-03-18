

-------Function name : Declare
intType
Variable: f
-------Arguements: Declare
intType
Variable: a
-------Code: Assign: Variable: a
5
Li s0,5
next: Return


.text
.globl f

f:
addi  t0, zero, 0
addi  t0, t0,   5
add   a0, zero, t0
ret
