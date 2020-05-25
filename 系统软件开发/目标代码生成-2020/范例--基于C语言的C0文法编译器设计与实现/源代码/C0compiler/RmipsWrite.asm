.data
	Enter: .asciiz  "\n"
.text
ori	$fp	$sp	0
li	$t9	0x7fffeffc	#global stack bottom
li	$t8	0x10010000	#save word
li	$t0	0	#cint
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	97	#cchar
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#gchara
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#ginta
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#gintb
sw	$t0	($sp)
subi	$sp	$sp	4
		j	__main
factor:
#Save Register
sw  $s0 0($sp)
subi    $sp $sp 4
sw  $fp 0($sp)
subi    $sp $sp 4
add	$fp	$sp	$0
sw	$ra	($sp)
subi	$sp	$sp	4
#Save Register Done!
li	$t0	0	#n
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#n
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#n
sw	$t0	($sp)
subi	$sp	$sp	4
lw	$t0	12($fp)
li	$t1	1
bne	$t0	$t1	__tLABEL0
li	$t0	1
j	__tLABEL1
__tLABEL0:
li	$t0	0
__tLABEL1:
bne	$t0	1	_LABEL_0
li	$v0	1
j	__FEND_LAB_1
j	_LABEL_1
_LABEL_0:
_LABEL_1:
lw	$t0	12($fp)
li	$t1	1
sub	$t0	$t0	$t1
sw	$t0	-4($fp)
move $s0 $sp
lw	$t0	-4($fp)
sw	$t0	($sp)
subi	$sp	$sp	4
jal	factor
nop
sw	$v0	-8($fp)
lw	$t0	12($fp)
lw	$t1	-8($fp)
mul	$t0	$t0	$t1
sw	$t0	-12($fp)
lw	$v0	-12($fp)
j	__FEND_LAB_1
__FEND_LAB_1:
lw  $ra 0($fp)
lw  $sp 8($fp)
lw  $fp 4($fp)
jr	$ra	
MyDefine:
#Save Register
sw  $s0 0($sp)
subi    $sp $sp 4
sw  $fp 0($sp)
subi    $sp $sp 4
add	$fp	$sp	$0
sw	$ra	($sp)
subi	$sp	$sp	4
#Save Register Done!
li	$t0	0	#int0
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	1	#int1
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	2	#int2
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	3	#int3
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	4	#int4
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	5	#int5
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	6	#int6
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	7	#int7
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#int1
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#int2
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#int3
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#int4
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#int5
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#int6
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#int7
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#int8
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#int9
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#int10
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#int11
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#int12
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#int13
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#char1
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#char2
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#char3
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#char4
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#char5
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#char6
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#char7
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#char8
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#char9
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#char10
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#char11
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#char12
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#char13
sw	$t0	($sp)
subi	$sp	$sp	4
__FEND_LAB_2:
lw  $ra 0($fp)
lw  $sp 8($fp)
lw  $fp 4($fp)
jr	$ra	
fibo:
#Save Register
sw  $s0 0($sp)
subi    $sp $sp 4
sw  $fp 0($sp)
subi    $sp $sp 4
add	$fp	$sp	$0
sw	$ra	($sp)
subi	$sp	$sp	4
#Save Register Done!
li	$t0	0	#n
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#n
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#n
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#n
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#n
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#n
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#n
sw	$t0	($sp)
subi	$sp	$sp	4
lw	$t0	12($fp)
li	$t1	0
slt	$t0	$t0	$t1
bne	$t0	1	_LABEL_2
li	$t0	0 
li	$t1	1
sub	$t0	$t0	$t1
sw	$t0	-4($fp)
lw	$v0	-4($fp)
j	__FEND_LAB_3
j	_LABEL_3
_LABEL_2:
lw	$t0	12($fp)
li	$t1	0
bne	$t0	$t1	__tLABEL2
li	$t0	1
j	__tLABEL3
__tLABEL2:
li	$t0	0
__tLABEL3:
bne	$t0	1	_LABEL_4
li	$v0	0
j	__FEND_LAB_3
j	_LABEL_5
_LABEL_4:
lw	$t0	12($fp)
li	$t1	1
bne	$t0	$t1	__tLABEL4
li	$t0	1
j	__tLABEL5
__tLABEL4:
li	$t0	0
__tLABEL5:
bne	$t0	1	_LABEL_6
li	$v0	1
j	__FEND_LAB_3
j	_LABEL_7
_LABEL_6:
lw	$t0	12($fp)
li	$t1	10
slt	$t0	$t1	$t0
bne	$t0	1	_LABEL_8
li	$t0	0 
li	$t1	2
sub	$t0	$t0	$t1
sw	$t0	-8($fp)
lw	$v0	-8($fp)
j	__FEND_LAB_3
j	_LABEL_9
_LABEL_8:
lw	$t0	12($fp)
li	$t1	1
sub	$t0	$t0	$t1
sw	$t0	-12($fp)
move $s0 $sp
lw	$t0	-12($fp)
sw	$t0	($sp)
subi	$sp	$sp	4
jal	fibo
nop
sw	$v0	-16($fp)
lw	$t0	12($fp)
li	$t1	2
sub	$t0	$t0	$t1
sw	$t0	-20($fp)
move $s0 $sp
lw	$t0	-20($fp)
sw	$t0	($sp)
subi	$sp	$sp	4
jal	fibo
nop
sw	$v0	-24($fp)
lw	$t0	-16($fp)
lw	$t1	-24($fp)
add	$t0	$t0	$t1
sw	$t0	-28($fp)
lw	$v0	-28($fp)
j	__FEND_LAB_3
_LABEL_9:
_LABEL_7:
_LABEL_5:
_LABEL_3:
__FEND_LAB_3:
lw  $ra 0($fp)
lw  $sp 8($fp)
lw  $fp 4($fp)
jr	$ra	
__main:
#Save Register
sw  $s0 0($sp)
subi    $sp $sp 4
sw  $fp 0($sp)
subi    $sp $sp 4
add	$fp	$sp	$0
sw	$ra	($sp)
subi	$sp	$sp	4
#Save Register Done!
li	$t0	0	#num1
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#num1
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#num1
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#num1
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#num1
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#num1
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#num1
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#num1
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#num1
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#num1
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#num1
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#num1
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#num2
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#ccc
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#i
sw	$t0	($sp)
subi	$sp	$sp	4
subi	$sp	$sp	60
subi	$sp	$sp	60
li	$v0	5
syscall
sw	$v0	-56($fp)
li	$v0	5
syscall
sw	$v0	-48($fp)
move $s0 $sp
jal	MyDefine
nop
lw	$t0	-56($fp)
li	$t1	1
bne	$t0	$t1	__tLABEL6
li	$t0	1
j	__tLABEL7
__tLABEL6:
li	$t0	0
__tLABEL7:
bne	$t0	1	_LABEL_11
move $s0 $sp
lw	$t0	-48($fp)
sw	$t0	($sp)
subi	$sp	$sp	4
jal	factor
nop
sw	$v0	-4($fp)
li	$v0	1
lw	$a0	-4($fp)
syscall
li	$v0	4
la	$a0	Enter
syscall
j	_LABEL_10
_LABEL_11:
lw	$t0	-56($fp)
li	$t1	2
bne	$t0	$t1	__tLABEL8
li	$t0	1
j	__tLABEL9
__tLABEL8:
li	$t0	0
__tLABEL9:
bne	$t0	1	_LABEL_12
move $s0 $sp
lw	$t0	-48($fp)
sw	$t0	($sp)
subi	$sp	$sp	4
jal	fibo
nop
sw	$v0	-8($fp)
li	$v0	1
lw	$a0	-8($fp)
syscall
li	$v0	4
la	$a0	Enter
syscall
j	_LABEL_10
_LABEL_12:
lw	$t0	-56($fp)
li	$t1	3
bne	$t0	$t1	__tLABEL10
li	$t0	1
j	__tLABEL11
__tLABEL10:
li	$t0	0
__tLABEL11:
bne	$t0	1	_LABEL_13
j	_LABEL_10
_LABEL_13:
li	$t0	1
sw	$t0	-64($fp)
li	$t0	3
sw	$t0	-128($fp)
li	$t0	4
sw	$t0	-76($fp)
li	$t0	6
sw	$t0	-140($fp)
li	$t0	8
sw	$t0	-88($fp)
lw	$t0	-64($fp)
sw	$t0	-12($fp)
lw	$t1	-12($fp)
mul	$t1	$t1	-4
addi	$t1	$t1	-124
add	$t1	$t1	$fp
lw	$t0	0($t1)
sw	$t0	-16($fp)
lw	$t1	-16($fp)
mul	$t1	$t1	-4
addi	$t1	$t1	-64
add	$t1	$t1	$fp
lw	$t0	0($t1)
sw	$t0	-20($fp)
lw	$t1	-20($fp)
mul	$t1	$t1	-4
addi	$t1	$t1	-124
add	$t1	$t1	$fp
lw	$t0	0($t1)
sw	$t0	-24($fp)
lw	$t1	-24($fp)
mul	$t1	$t1	-4
addi	$t1	$t1	-64
add	$t1	$t1	$fp
lw	$t0	0($t1)
sw	$t0	-28($fp)
lw	$t1	-28($fp)
mul	$t1	$t1	-4
addi	$t1	$t1	-124
li	$t0	2333
add	$t1	$t1	$fp
sw	$t0	0($t1)
lw	$t0	-64($fp)
sw	$t0	-32($fp)
lw	$t0	-156($fp)
sw	$t0	-36($fp)
lw	$t0	-32($fp)
lw	$t1	-36($fp)
add	$t0	$t0	$t1
sw	$t0	-40($fp)
li	$v0	1
lw	$a0	-40($fp)
syscall
li	$v0	4
la	$a0	Enter
syscall
_LABEL_10:
li	$v0	12
syscall
sw	$v0	-8($t9)
lw	$t0	-8($t9)
li	$t1	97
bne	$t0	$t1	__tLABEL12
li	$t0	1
j	__tLABEL13
__tLABEL12:
li	$t0	0
__tLABEL13:
bne	$t0	1	_LABEL_15
li	$t0	1
sw	$t0	-12($t9)  #   ginta
j	_LABEL_14
_LABEL_15:
lw	$t0	-8($t9)
li	$t1	98
bne	$t0	$t1	__tLABEL14
li	$t0	1
j	__tLABEL15
__tLABEL14:
li	$t0	0
__tLABEL15:
bne	$t0	1	_LABEL_16
li	$t0	2
sw	$t0	-12($t9)  #   ginta
j	_LABEL_14
_LABEL_16:
lw	$t0	-8($t9)
li	$t1	99
bne	$t0	$t1	__tLABEL16
li	$t0	1
j	__tLABEL17
__tLABEL16:
li	$t0	0
__tLABEL17:
bne	$t0	1	_LABEL_17
li	$t0	10086
sw	$t0	-16($t9)  #   gintb
li	$t0	98
sw	$t0	-8($t9)  #   gchara
li	$t0	10000
sw	$t0	-12($t9)  #   ginta
li	$t0	10000
sw	$t0	-16($t9)  #   gintb
li	$v0	1
lw	$a0	-16($t9)
syscall
li	$v0	4
la	$a0	Enter
syscall
li	$v0	11
li	$a0	70
syscall
li	$v0	11
li	$a0	105
syscall
li	$v0	11
li	$a0	110
syscall
li	$v0	11
li	$a0	105
syscall
li	$v0	11
li	$a0	115
syscall
li	$v0	11
li	$a0	104
syscall
li	$v0	11
li	$a0	33
syscall
j	_LABEL_14
_LABEL_17:
li	$t0	3
sw	$t0	-12($t9)  #   ginta
_LABEL_14:
li	$v0	1
lw	$a0	-12($t9)
syscall
li	$v0	4
la	$a0	Enter
syscall
li	$v0	5
syscall
sw	$v0	-48($fp)
li	$t0	0
sw	$t0	-60($fp)  #   i
j	_LABEL_20
_LABEL_18:
lw	$t0	-60($fp)
lw	$t1	-48($fp)
slt	$t0	$t0	$t1
bne	$t0	1	_LABEL_19
_LABEL_20:
li	$v0	11
li	$a0	102
syscall
li	$v0	11
li	$a0	111
syscall
li	$v0	11
li	$a0	114
syscall
li	$v0	11
li	$a0	45
syscall
li	$v0	11
li	$a0	45
syscall
li	$v0	11
li	$a0	62
syscall
li	$v0	1
lw	$a0	-60($fp)
syscall
li	$v0	4
la	$a0	Enter
syscall
lw	$t0	-60($fp)
li	$t1	1
add	$t0	$t0	$t1
sw	$t0	-44($fp)
lw	$t0	-44($fp)
sw	$t0	-60($fp)  #   i
j	_LABEL_18
_LABEL_19:
li	$v0	11
li	$a0	116
syscall
li	$v0	11
li	$a0	104
syscall
li	$v0	11
li	$a0	101
syscall
li	$v0	11
li	$a0	32
syscall
li	$v0	11
li	$a0	101
syscall
li	$v0	11
li	$a0	110
syscall
li	$v0	11
li	$a0	100
syscall
j	__FEND_LAB_4
__FEND_LAB_4:
lw  $ra 0($fp)
lw  $sp 8($fp)
lw  $fp 4($fp)
li	$v0	10
syscall
