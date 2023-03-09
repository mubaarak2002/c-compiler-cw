sub 5 5
add 0 6
next: add 5 5
next: Assign: int
Variable: hello
reg 10 is .
test
registers full
next: Assign: Variable: hello
reg 10 is test
test
registers full
next: 

-------Function name : int
Variable: f
reg 10 is test
test
registers full
-------Arguements: (int
Variable: a
reg 10 is test
test
registers full
int
Variable: b
reg 10 is test
test
registers full
)
-------Code: Variable: SUUUUIIIIII
reg 10 is test
test
registers full


.text
.globl f

f:
addi  t0, zero, 0
addi  t0, t0,   5
add   a0, zero, t0
ret
