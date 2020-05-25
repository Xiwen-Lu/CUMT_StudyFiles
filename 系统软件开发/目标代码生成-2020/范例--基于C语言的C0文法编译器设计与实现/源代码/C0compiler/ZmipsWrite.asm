.data
	Enter: .asciiz  "\n"
.text
ori	$fp	$sp	0
li	$t9	0x7fffeffc	#global stack bottom
li	$t8	0x10010000	#save word
li	$t0	10	#MAX
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	97	#A
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	43	#plus
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	45	#minus
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	42	#mult
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	47	#div
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#n
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#x
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#y
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#kind
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#m
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#ans
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#_a
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#_b
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#ch
sw	$t0	($sp)
subi	$sp	$sp	4
subi	$sp	$sp	104
		j	__main
testDefine:
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
li	$t0	8	#int8
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	9	#int9
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	10	#int10
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	11	#int11
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	12	#int12
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	13	#int13
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	14	#int14
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	15	#int15
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	16	#int16
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	17	#int17
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	18	#int18
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	19	#int19
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#int_0
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	-1	#int_1
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	-2	#int_2
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	-3	#int_3
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	-4	#int_4
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	-5	#int_5
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	-6	#int_6
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	-7	#int_7
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	-8	#int_8
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	-9	#int_9
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	-10	#int_10
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	-11	#int_11
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	-12	#int_12
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	-13	#int_13
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	-14	#int_14
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	-15	#int_15
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	-16	#int_16
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	-17	#int_17
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	-18	#int_18
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	-19	#int_19
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#_int0
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	1	#_int1
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	2	#_int2
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	3	#_int3
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	4	#_int4
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	5	#_int5
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	6	#_int6
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	7	#_int7
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	8	#_int8
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	9	#_int9
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	10	#_int10
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	11	#_int11
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	12	#_int12
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	13	#_int13
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	14	#_int14
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	15	#_int15
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	16	#_int16
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	17	#_int17
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	18	#_int18
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	19	#_int19
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	48	#char0
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	49	#char1
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	50	#char2
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	51	#char3
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	52	#char4
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	53	#char5
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	54	#char6
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	55	#char7
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	56	#char8
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	57	#char9
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#var0
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#var1
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#arr1
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#var2
sw	$t0	($sp)
subi	$sp	$sp	4
subi	$sp	$sp	8
li	$t0	0	#var3
sw	$t0	($sp)
subi	$sp	$sp	4
subi	$sp	$sp	12
li	$t0	0	#var4
sw	$t0	($sp)
subi	$sp	$sp	4
subi	$sp	$sp	16
li	$t0	0	#var5
sw	$t0	($sp)
subi	$sp	$sp	4
subi	$sp	$sp	20
li	$t0	0	#var6
sw	$t0	($sp)
subi	$sp	$sp	4
subi	$sp	$sp	24
li	$t0	0	#var7
sw	$t0	($sp)
subi	$sp	$sp	4
subi	$sp	$sp	28
li	$t0	0	#var8
sw	$t0	($sp)
subi	$sp	$sp	4
subi	$sp	$sp	32
li	$t0	0	#var9
sw	$t0	($sp)
subi	$sp	$sp	4
subi	$sp	$sp	36
li	$t0	0	#var10
sw	$t0	($sp)
subi	$sp	$sp	4
subi	$sp	$sp	40
li	$t0	0	#var11
sw	$t0	($sp)
subi	$sp	$sp	4
subi	$sp	$sp	44
li	$t0	0	#var12
sw	$t0	($sp)
subi	$sp	$sp	4
subi	$sp	$sp	48
li	$t0	0	#var13
sw	$t0	($sp)
subi	$sp	$sp	4
subi	$sp	$sp	52
li	$t0	0	#var14
sw	$t0	($sp)
subi	$sp	$sp	4
subi	$sp	$sp	56
li	$t0	0	#var15
sw	$t0	($sp)
subi	$sp	$sp	4
subi	$sp	$sp	60
li	$t0	0	#var16
sw	$t0	($sp)
subi	$sp	$sp	4
subi	$sp	$sp	64
li	$t0	0	#var17
sw	$t0	($sp)
subi	$sp	$sp	4
subi	$sp	$sp	68
li	$t0	0	#var18
sw	$t0	($sp)
subi	$sp	$sp	4
subi	$sp	$sp	72
li	$t0	0	#var19
sw	$t0	($sp)
subi	$sp	$sp	4
subi	$sp	$sp	76
__FEND_LAB_1:
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
bne	$t0	1	_LABEL_0
li	$t0	0 
li	$t1	1
sub	$t0	$t0	$t1
sw	$t0	-4($fp)
lw	$v0	-4($fp)
j	__FEND_LAB_2
j	_LABEL_1
_LABEL_0:
lw	$t0	12($fp)
li	$t1	0
bne	$t0	$t1	__tLABEL0
li	$t0	1
j	__tLABEL1
__tLABEL0:
li	$t0	0
__tLABEL1:
bne	$t0	1	_LABEL_2
li	$v0	0
j	__FEND_LAB_2
j	_LABEL_3
_LABEL_2:
lw	$t0	12($fp)
li	$t1	1
bne	$t0	$t1	__tLABEL2
li	$t0	1
j	__tLABEL3
__tLABEL2:
li	$t0	0
__tLABEL3:
bne	$t0	1	_LABEL_4
li	$v0	1
j	__FEND_LAB_2
j	_LABEL_5
_LABEL_4:
lw	$t0	12($fp)
lw	$t1	0($t9)
slt	$t0	$t1	$t0
bne	$t0	1	_LABEL_6
li	$t0	0 
li	$t1	2
sub	$t0	$t0	$t1
sw	$t0	-8($fp)
lw	$v0	-8($fp)
j	__FEND_LAB_2
j	_LABEL_7
_LABEL_6:
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
j	__FEND_LAB_2
_LABEL_7:
_LABEL_5:
_LABEL_3:
_LABEL_1:
__FEND_LAB_2:
lw  $ra 0($fp)
lw  $sp 8($fp)
lw  $fp 4($fp)
jr	$ra	
upcase:
#Save Register
sw  $s0 0($sp)
subi    $sp $sp 4
sw  $fp 0($sp)
subi    $sp $sp 4
add	$fp	$sp	$0
sw	$ra	($sp)
subi	$sp	$sp	4
#Save Register Done!
li	$t0	0	#x
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#x
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#y
sw	$t0	($sp)
subi	$sp	$sp	4
lw	$t0	12($fp)
li	$t1	97
slt	$t0	$t0	$t1
li	$t1	1
sub	$t0	$t1	$t0
bne	$t0	1	_LABEL_8
lw	$t0	12($fp)
li	$t1	122
slt	$t0	$t1	$t0
li	$t1	1
sub	$t0	$t1	$t0
bne	$t0	1	_LABEL_10
lw	$t0	12($fp)
li	$t1	97
sub	$t0	$t0	$t1
sw	$t0	-4($fp)
lw	$t0	-4($fp)
li	$t1	65
add	$t0	$t0	$t1
sw	$t0	-8($fp)
lw	$t0	-8($fp)
sw	$t0	-12($fp)  #   y
lw	$v0	-12($fp)
j	__FEND_LAB_3
j	_LABEL_11
_LABEL_10:
lw	$v0	12($fp)
j	__FEND_LAB_3
_LABEL_11:
j	_LABEL_9
_LABEL_8:
lw	$v0	12($fp)
j	__FEND_LAB_3
_LABEL_9:
__FEND_LAB_3:
lw  $ra 0($fp)
lw  $sp 8($fp)
lw  $fp 4($fp)
jr	$ra	
lowcase:
#Save Register
sw  $s0 0($sp)
subi    $sp $sp 4
sw  $fp 0($sp)
subi    $sp $sp 4
add	$fp	$sp	$0
sw	$ra	($sp)
subi	$sp	$sp	4
#Save Register Done!
li	$t0	0	#x
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#x
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#y
sw	$t0	($sp)
subi	$sp	$sp	4
lw	$t0	12($fp)
li	$t1	65
slt	$t0	$t0	$t1
li	$t1	1
sub	$t0	$t1	$t0
bne	$t0	1	_LABEL_12
lw	$t0	12($fp)
li	$t1	90
slt	$t0	$t1	$t0
li	$t1	1
sub	$t0	$t1	$t0
bne	$t0	1	_LABEL_14
lw	$t0	12($fp)
li	$t1	65
sub	$t0	$t0	$t1
sw	$t0	-4($fp)
lw	$t0	-4($fp)
li	$t1	97
add	$t0	$t0	$t1
sw	$t0	-8($fp)
lw	$t0	-8($fp)
sw	$t0	-12($fp)  #   y
lw	$v0	-12($fp)
j	__FEND_LAB_4
j	_LABEL_15
_LABEL_14:
lw	$v0	12($fp)
j	__FEND_LAB_4
_LABEL_15:
j	_LABEL_13
_LABEL_12:
lw	$v0	12($fp)
j	__FEND_LAB_4
_LABEL_13:
__FEND_LAB_4:
lw  $ra 0($fp)
lw  $sp 8($fp)
lw  $fp 4($fp)
jr	$ra	
printspace:
#Save Register
sw  $s0 0($sp)
subi    $sp $sp 4
sw  $fp 0($sp)
subi    $sp $sp 4
add	$fp	$sp	$0
sw	$ra	($sp)
subi	$sp	$sp	4
#Save Register Done!
li	$v0	11
li	$a0	32
syscall
__FEND_LAB_5:
lw  $ra 0($fp)
lw  $sp 8($fp)
lw  $fp 4($fp)
jr	$ra	
operation:
#Save Register
sw  $s0 0($sp)
subi    $sp $sp 4
sw  $fp 0($sp)
subi    $sp $sp 4
add	$fp	$sp	$0
sw	$ra	($sp)
subi	$sp	$sp	4
#Save Register Done!
li	$t0	0	#x
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#x
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#x
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#x
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#x
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#x
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#x
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#x
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#x
sw	$t0	($sp)
subi	$sp	$sp	4
lw	$t0	12($fp)
li	$t1	1
bne	$t0	$t1	__tLABEL4
li	$t0	1
j	__tLABEL5
__tLABEL4:
li	$t0	0
__tLABEL5:
bne	$t0	1	_LABEL_17
lw	$t0	20($fp)
lw	$t1	16($fp)
add	$t0	$t0	$t1
sw	$t0	-4($fp)
li	$v0	11
li	$a0	111
syscall
li	$v0	11
li	$a0	112
syscall
li	$v0	11
li	$a0	101
syscall
li	$v0	11
li	$a0	114
syscall
li	$v0	11
li	$a0	97
syscall
li	$v0	11
li	$a0	116
syscall
li	$v0	11
li	$a0	105
syscall
li	$v0	11
li	$a0	111
syscall
li	$v0	11
li	$a0	110
syscall
li	$v0	11
li	$a0	58
syscall
li	$v0	1
lw	$a0	-4($fp)
syscall
li	$v0	4
la	$a0	Enter
syscall
lw	$t0	20($fp)
lw	$t1	16($fp)
add	$t0	$t0	$t1
sw	$t0	-8($fp)
lw	$v0	-8($fp)
j	__FEND_LAB_6
j	_LABEL_16
_LABEL_17:
lw	$t0	12($fp)
li	$t1	2
bne	$t0	$t1	__tLABEL6
li	$t0	1
j	__tLABEL7
__tLABEL6:
li	$t0	0
__tLABEL7:
bne	$t0	1	_LABEL_18
lw	$t0	20($fp)
lw	$t1	16($fp)
sub	$t0	$t0	$t1
sw	$t0	-12($fp)
li	$v0	11
li	$a0	111
syscall
li	$v0	11
li	$a0	112
syscall
li	$v0	11
li	$a0	101
syscall
li	$v0	11
li	$a0	114
syscall
li	$v0	11
li	$a0	97
syscall
li	$v0	11
li	$a0	116
syscall
li	$v0	11
li	$a0	105
syscall
li	$v0	11
li	$a0	111
syscall
li	$v0	11
li	$a0	110
syscall
li	$v0	11
li	$a0	58
syscall
li	$v0	1
lw	$a0	-12($fp)
syscall
li	$v0	4
la	$a0	Enter
syscall
lw	$t0	20($fp)
lw	$t1	16($fp)
sub	$t0	$t0	$t1
sw	$t0	-16($fp)
lw	$v0	-16($fp)
j	__FEND_LAB_6
j	_LABEL_16
_LABEL_18:
lw	$t0	12($fp)
li	$t1	3
bne	$t0	$t1	__tLABEL8
li	$t0	1
j	__tLABEL9
__tLABEL8:
li	$t0	0
__tLABEL9:
bne	$t0	1	_LABEL_19
lw	$t0	20($fp)
lw	$t1	16($fp)
mul	$t0	$t0	$t1
sw	$t0	-20($fp)
li	$v0	11
li	$a0	111
syscall
li	$v0	11
li	$a0	112
syscall
li	$v0	11
li	$a0	101
syscall
li	$v0	11
li	$a0	114
syscall
li	$v0	11
li	$a0	97
syscall
li	$v0	11
li	$a0	116
syscall
li	$v0	11
li	$a0	105
syscall
li	$v0	11
li	$a0	111
syscall
li	$v0	11
li	$a0	110
syscall
li	$v0	11
li	$a0	58
syscall
li	$v0	1
lw	$a0	-20($fp)
syscall
li	$v0	4
la	$a0	Enter
syscall
lw	$t0	20($fp)
lw	$t1	16($fp)
mul	$t0	$t0	$t1
sw	$t0	-24($fp)
lw	$v0	-24($fp)
j	__FEND_LAB_6
j	_LABEL_16
_LABEL_19:
lw	$t0	12($fp)
li	$t1	4
bne	$t0	$t1	__tLABEL10
li	$t0	1
j	__tLABEL11
__tLABEL10:
li	$t0	0
__tLABEL11:
bne	$t0	1	_LABEL_20
lw	$t0	16($fp)
li	$t1	0
beq	$t0	$t1	__tLABEL12
li	$t0	1
j	__tLABEL13
__tLABEL12:
li	$t0	0
__tLABEL13:
bne	$t0	1	_LABEL_21
lw	$t0	20($fp)
lw	$t1	16($fp)
div	$t0	$t0	$t1
sw	$t0	-28($fp)
li	$v0	11
li	$a0	111
syscall
li	$v0	11
li	$a0	112
syscall
li	$v0	11
li	$a0	101
syscall
li	$v0	11
li	$a0	114
syscall
li	$v0	11
li	$a0	97
syscall
li	$v0	11
li	$a0	116
syscall
li	$v0	11
li	$a0	105
syscall
li	$v0	11
li	$a0	111
syscall
li	$v0	11
li	$a0	110
syscall
li	$v0	11
li	$a0	58
syscall
li	$v0	1
lw	$a0	-28($fp)
syscall
li	$v0	4
la	$a0	Enter
syscall
lw	$t0	20($fp)
lw	$t1	16($fp)
div	$t0	$t0	$t1
sw	$t0	-32($fp)
lw	$v0	-32($fp)
j	__FEND_LAB_6
j	_LABEL_22
_LABEL_21:
li	$v0	11
li	$a0	99
syscall
li	$v0	11
li	$a0	97
syscall
li	$v0	11
li	$a0	110
syscall
li	$v0	11
li	$a0	110
syscall
li	$v0	11
li	$a0	111
syscall
li	$v0	11
li	$a0	116
syscall
li	$v0	11
li	$a0	32
syscall
li	$v0	11
li	$a0	100
syscall
li	$v0	11
li	$a0	105
syscall
li	$v0	11
li	$a0	118
syscall
li	$v0	11
li	$a0	32
syscall
li	$v0	11
li	$a0	48
syscall
li	$v0	11
li	$a0	33
syscall
li	$v0	11
li	$a0	33
syscall
li	$v0	11
li	$a0	33
syscall
li	$v0	0
j	__FEND_LAB_6
_LABEL_22:
j	_LABEL_16
_LABEL_20:
li	$v0	11
li	$a0	111
syscall
li	$v0	11
li	$a0	112
syscall
li	$v0	11
li	$a0	101
syscall
li	$v0	11
li	$a0	114
syscall
li	$v0	11
li	$a0	97
syscall
li	$v0	11
li	$a0	116
syscall
li	$v0	11
li	$a0	105
syscall
li	$v0	11
li	$a0	111
syscall
li	$v0	11
li	$a0	110
syscall
li	$v0	11
li	$a0	32
syscall
li	$v0	11
li	$a0	107
syscall
li	$v0	11
li	$a0	105
syscall
li	$v0	11
li	$a0	110
syscall
li	$v0	11
li	$a0	100
syscall
li	$v0	11
li	$a0	32
syscall
li	$v0	11
li	$a0	105
syscall
li	$v0	11
li	$a0	115
syscall
li	$v0	11
li	$a0	32
syscall
li	$v0	11
li	$a0	110
syscall
li	$v0	11
li	$a0	111
syscall
li	$v0	11
li	$a0	116
syscall
li	$v0	11
li	$a0	32
syscall
li	$v0	11
li	$a0	105
syscall
li	$v0	11
li	$a0	110
syscall
li	$v0	11
li	$a0	32
syscall
li	$v0	11
li	$a0	91
syscall
li	$v0	11
li	$a0	43
syscall
li	$v0	11
li	$a0	45
syscall
li	$v0	11
li	$a0	42
syscall
li	$v0	11
li	$a0	47
syscall
li	$v0	11
li	$a0	93
syscall
li	$v0	11
li	$a0	33
syscall
li	$v0	11
li	$a0	33
syscall
li	$v0	11
li	$a0	33
syscall
li	$t0	0 
li	$t1	1
sub	$t0	$t0	$t1
sw	$t0	-36($fp)
lw	$v0	-36($fp)
j	__FEND_LAB_6
_LABEL_16:
__FEND_LAB_6:
lw  $ra 0($fp)
lw  $sp 8($fp)
lw  $fp 4($fp)
jr	$ra	
display:
#Save Register
sw  $s0 0($sp)
subi    $sp $sp 4
sw  $fp 0($sp)
subi    $sp $sp 4
add	$fp	$sp	$0
sw	$ra	($sp)
subi	$sp	$sp	4
#Save Register Done!
li	$t0	0	#m
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#m
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#m
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#m
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#m
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#m
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#m
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#m
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#m
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#i
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#letter
sw	$t0	($sp)
subi	$sp	$sp	4
lw	$t0	12($fp)
li	$t1	0
slt	$t0	$t1	$t0
li	$t1	1
sub	$t0	$t1	$t0
bne	$t0	1	_LABEL_23
j	__FEND_LAB_7
j	_LABEL_24
_LABEL_23:
lw	$t0	12($fp)
li	$t1	26
slt	$t0	$t1	$t0
bne	$t0	1	_LABEL_25
li	$t0	26
sw	$t0	12($fp)  #   m
j	_LABEL_26
_LABEL_25:
li	$t0	0
sw	$t0	-40($fp)  #   i
lw	$t0	-4($t9)
sw	$t0	-44($fp)  #   letter
li	$t0	0
sw	$t0	-40($fp)  #   i
j	_LABEL_29
_LABEL_27:
lw	$t0	-40($fp)
lw	$t1	12($fp)
slt	$t0	$t0	$t1
bne	$t0	1	_LABEL_28
_LABEL_29:
move $s0 $sp
lw	$t0	-44($fp)
sw	$t0	($sp)
subi	$sp	$sp	4
jal	upcase
nop
sw	$v0	-4($fp)
lw	$t1	-40($fp)
mul	$t1	$t1	-4
addi	$t1	$t1	-60
lw	$t0	-4($fp)
add	$t1	$t1	$t9
sw	$t0	0($t1)
move $s0 $sp
lw	$t0	-44($fp)
sw	$t0	($sp)
subi	$sp	$sp	4
jal	upcase
nop
sw	$v0	-8($fp)
lw	$t1	-40($fp)
mul	$t1	$t1	-4
addi	$t1	$t1	-60
lw	$t0	-8($fp)
add	$t1	$t1	$t9
sw	$t0	0($t1)
lw	$t1	-40($fp)
mul	$t1	$t1	-4
addi	$t1	$t1	-60
add	$t1	$t1	$t9
lw	$t0	0($t1)
sw	$t0	-12($fp)
li	$v0	11
lw	$a0	-12($fp)
syscall
li	$v0	4
la	$a0	Enter
syscall
lw	$t0	-44($fp)
li	$t1	1
add	$t0	$t0	$t1
sw	$t0	-16($fp)
lw	$t0	-16($fp)
sw	$t0	-44($fp)  #   letter
lw	$t0	-40($fp)
li	$t1	1
add	$t0	$t0	$t1
sw	$t0	-20($fp)
lw	$t0	-20($fp)
sw	$t0	-40($fp)  #   i
j	_LABEL_27
_LABEL_28:
move $s0 $sp
jal	printspace
nop
li	$t0	0
sw	$t0	-40($fp)  #   i
li	$t0	0
sw	$t0	-40($fp)  #   i
j	_LABEL_32
_LABEL_30:
lw	$t0	-40($fp)
lw	$t1	12($fp)
slt	$t0	$t0	$t1
bne	$t0	1	_LABEL_31
_LABEL_32:
lw	$t1	-40($fp)
mul	$t1	$t1	-4
addi	$t1	$t1	-60
add	$t1	$t1	$t9
lw	$t0	0($t1)
sw	$t0	-24($fp)
move $s0 $sp
lw	$t0	-24($fp)
sw	$t0	($sp)
subi	$sp	$sp	4
jal	lowcase
nop
sw	$v0	-28($fp)
lw	$t1	-40($fp)
mul	$t1	$t1	-4
addi	$t1	$t1	-60
lw	$t0	-28($fp)
add	$t1	$t1	$t9
sw	$t0	0($t1)
lw	$t1	-40($fp)
mul	$t1	$t1	-4
addi	$t1	$t1	-60
add	$t1	$t1	$t9
lw	$t0	0($t1)
sw	$t0	-32($fp)
li	$v0	11
lw	$a0	-32($fp)
syscall
li	$v0	4
la	$a0	Enter
syscall
lw	$t0	-40($fp)
li	$t1	1
add	$t0	$t0	$t1
sw	$t0	-36($fp)
lw	$t0	-36($fp)
sw	$t0	-40($fp)  #   i
j	_LABEL_30
_LABEL_31:
move $s0 $sp
jal	printspace
nop
_LABEL_26:
_LABEL_24:
__FEND_LAB_7:
lw  $ra 0($fp)
lw  $sp 8($fp)
lw  $fp 4($fp)
jr	$ra	
expre:
#Save Register
sw  $s0 0($sp)
subi    $sp $sp 4
sw  $fp 0($sp)
subi    $sp $sp 4
add	$fp	$sp	$0
sw	$ra	($sp)
subi	$sp	$sp	4
#Save Register Done!
li	$t0	0	#x
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#x
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#x
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#x
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#x
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#x
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#x
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#x
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#x
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#y
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#z
sw	$t0	($sp)
subi	$sp	$sp	4
li	$v0	5
syscall
sw	$v0	-36($fp)
li	$v0	5
syscall
sw	$v0	-40($fp)
lw	$t0	-36($fp)
lw	$t1	-40($fp)
add	$t0	$t0	$t1
sw	$t0	-4($fp)
li	$t0	0 
li	$t1	2
sub	$t0	$t0	$t1
sw	$t0	-8($fp)
lw	$t0	-40($fp)
lw	$t1	-8($fp)
mul	$t0	$t0	$t1
sw	$t0	-12($fp)
li	$t0	0 
lw	$t1	-12($fp)
sub	$t0	$t0	$t1
sw	$t0	-16($fp)
lw	$t0	-4($fp)
lw	$t1	-16($fp)
sub	$t0	$t0	$t1
sw	$t0	-20($fp)
li	$t0	2
li	$t1	0
mul	$t0	$t0	$t1
sw	$t0	-24($fp)
li	$t0	0 
lw	$t1	-24($fp)
sub	$t0	$t0	$t1
sw	$t0	-28($fp)
lw	$t0	-20($fp)
lw	$t1	-28($fp)
add	$t0	$t0	$t1
sw	$t0	-32($fp)
lw	$t0	-32($fp)
sw	$t0	-44($fp)  #   z
li	$v0	11
li	$a0	101
syscall
li	$v0	11
li	$a0	120
syscall
li	$v0	11
li	$a0	112
syscall
li	$v0	11
li	$a0	114
syscall
li	$v0	11
li	$a0	101
syscall
li	$v0	11
li	$a0	58
syscall
li	$v0	1
lw	$a0	-44($fp)
syscall
li	$v0	4
la	$a0	Enter
syscall
move $s0 $sp
jal	printspace
nop
__FEND_LAB_8:
lw  $ra 0($fp)
lw  $sp 8($fp)
lw  $fp 4($fp)
jr	$ra	
mod:
#Save Register
sw  $s0 0($sp)
subi    $sp $sp 4
sw  $fp 0($sp)
subi    $sp $sp 4
add	$fp	$sp	$0
sw	$ra	($sp)
subi	$sp	$sp	4
#Save Register Done!
li	$t0	0	#x
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#x
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#x
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#z
sw	$t0	($sp)
subi	$sp	$sp	4
lw	$t0	16($fp)
lw	$t1	12($fp)
div	$t0	$t0	$t1
sw	$t0	-4($fp)
lw	$t0	-4($fp)
lw	$t1	12($fp)
mul	$t0	$t0	$t1
sw	$t0	-8($fp)
lw	$t0	16($fp)
lw	$t1	-8($fp)
sub	$t0	$t0	$t1
sw	$t0	-12($fp)
lw	$t0	-12($fp)
sw	$t0	-16($fp)  #   z
lw	$v0	-16($fp)
j	__FEND_LAB_9
__FEND_LAB_9:
lw  $ra 0($fp)
lw  $sp 8($fp)
lw  $fp 4($fp)
jr	$ra	
gcd:
#Save Register
sw  $s0 0($sp)
subi    $sp $sp 4
sw  $fp 0($sp)
subi    $sp $sp 4
add	$fp	$sp	$0
sw	$ra	($sp)
subi	$sp	$sp	4
#Save Register Done!
li	$t0	0	#a
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#a
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#a
sw	$t0	($sp)
subi	$sp	$sp	4
lw	$t0	12($fp)
li	$t1	0
bne	$t0	$t1	__tLABEL14
li	$t0	1
j	__tLABEL15
__tLABEL14:
li	$t0	0
__tLABEL15:
bne	$t0	1	_LABEL_33
li	$v0	0
j	__FEND_LAB_10
j	_LABEL_34
_LABEL_33:
move $s0 $sp
lw	$t0	16($fp)
sw	$t0	($sp)
subi	$sp	$sp	4
lw	$t0	12($fp)
sw	$t0	($sp)
subi	$sp	$sp	4
jal	mod
nop
sw	$v0	-4($fp)
lw	$t0	-4($fp)
li	$t1	0
bne	$t0	$t1	__tLABEL16
li	$t0	1
j	__tLABEL17
__tLABEL16:
li	$t0	0
__tLABEL17:
bne	$t0	1	_LABEL_35
lw	$v0	12($fp)
j	__FEND_LAB_10
j	_LABEL_36
_LABEL_35:
move $s0 $sp
lw	$t0	16($fp)
sw	$t0	($sp)
subi	$sp	$sp	4
lw	$t0	12($fp)
sw	$t0	($sp)
subi	$sp	$sp	4
jal	mod
nop
sw	$v0	-8($fp)
move $s0 $sp
lw	$t0	12($fp)
sw	$t0	($sp)
subi	$sp	$sp	4
lw	$t0	-8($fp)
sw	$t0	($sp)
subi	$sp	$sp	4
jal	gcd
nop
sw	$v0	-12($fp)
lw	$v0	-12($fp)
j	__FEND_LAB_10
_LABEL_36:
_LABEL_34:
__FEND_LAB_10:
lw  $ra 0($fp)
lw  $sp 8($fp)
lw  $fp 4($fp)
jr	$ra	
optimize:
#Save Register
sw  $s0 0($sp)
subi    $sp $sp 4
sw  $fp 0($sp)
subi    $sp $sp 4
add	$fp	$sp	$0
sw	$ra	($sp)
subi	$sp	$sp	4
#Save Register Done!
li	$t0	0	#i
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#i
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#i
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#i
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#i
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#i
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#i
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#a
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#b
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#c
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#t1
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#t2
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#t3
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#t4
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0
sw	$t0	-28($fp)  #   i
li	$t0	1
sw	$t0	-40($fp)  #   c
li	$t0	1
sw	$t0	-36($fp)  #   b
li	$t0	0
sw	$t0	-28($fp)  #   i
j	_LABEL_39
_LABEL_37:
lw	$t0	-28($fp)
li	$t1	10000
slt	$t0	$t0	$t1
bne	$t0	1	_LABEL_38
_LABEL_39:
li	$t0	0 
lw	$t1	-40($fp)
sub	$t0	$t0	$t1
sw	$t0	-4($fp)
lw	$t0	-4($fp)
sw	$t0	-44($fp)  #   t1
lw	$t0	-36($fp)
lw	$t1	-44($fp)
mul	$t0	$t0	$t1
sw	$t0	-8($fp)
lw	$t0	-8($fp)
sw	$t0	-48($fp)  #   t2
li	$t0	0 
lw	$t1	-40($fp)
sub	$t0	$t0	$t1
sw	$t0	-12($fp)
lw	$t0	-12($fp)
sw	$t0	-52($fp)  #   t3
lw	$t0	-36($fp)
lw	$t1	-52($fp)
mul	$t0	$t0	$t1
sw	$t0	-16($fp)
lw	$t0	-16($fp)
sw	$t0	-40($fp)  #   c
lw	$t0	-48($fp)
lw	$t1	-40($fp)
add	$t0	$t0	$t1
sw	$t0	-20($fp)
lw	$t0	-20($fp)
sw	$t0	-56($fp)  #   t4
lw	$t0	-56($fp)
sw	$t0	-32($fp)  #   a
lw	$t0	-28($fp)
li	$t1	1
add	$t0	$t0	$t1
sw	$t0	-24($fp)
lw	$t0	-24($fp)
sw	$t0	-28($fp)  #   i
j	_LABEL_37
_LABEL_38:
li	$v0	1
lw	$a0	-32($fp)
syscall
li	$v0	4
la	$a0	Enter
syscall
move $s0 $sp
jal	printspace
nop
li	$v0	1
lw	$a0	-36($fp)
syscall
li	$v0	4
la	$a0	Enter
syscall
move $s0 $sp
jal	printspace
nop
li	$v0	1
lw	$a0	-40($fp)
syscall
li	$v0	4
la	$a0	Enter
syscall
move $s0 $sp
jal	printspace
nop
li	$v0	1
lw	$a0	-44($fp)
syscall
li	$v0	4
la	$a0	Enter
syscall
move $s0 $sp
jal	printspace
nop
li	$v0	1
lw	$a0	-48($fp)
syscall
li	$v0	4
la	$a0	Enter
syscall
move $s0 $sp
jal	printspace
nop
li	$v0	1
lw	$a0	-52($fp)
syscall
li	$v0	4
la	$a0	Enter
syscall
move $s0 $sp
jal	printspace
nop
li	$v0	1
lw	$a0	-56($fp)
syscall
li	$v0	4
la	$a0	Enter
syscall
__FEND_LAB_11:
lw  $ra 0($fp)
lw  $sp 8($fp)
lw  $fp 4($fp)
jr	$ra	
process:
#Save Register
sw  $s0 0($sp)
subi    $sp $sp 4
sw  $fp 0($sp)
subi    $sp $sp 4
add	$fp	$sp	$0
sw	$ra	($sp)
subi	$sp	$sp	4
#Save Register Done!
li	$t0	0	#choice
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#choice
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#choice
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#choice
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#choice
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#choice
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#choice_ch
sw	$t0	($sp)
subi	$sp	$sp	4
li	$v0	5
syscall
sw	$v0	-24($fp)
lw	$t0	-24($fp)
li	$t1	97
add	$t0	$t0	$t1
sw	$t0	-4($fp)
lw	$t0	-4($fp)
li	$t1	1
sub	$t0	$t0	$t1
sw	$t0	-8($fp)
lw	$t0	-8($fp)
sw	$t0	-28($fp)  #   choice_ch
lw	$t0	-28($fp)
li	$t1	97
bne	$t0	$t1	__tLABEL18
li	$t0	1
j	__tLABEL19
__tLABEL18:
li	$t0	0
__tLABEL19:
bne	$t0	1	_LABEL_41
move $s0 $sp
jal	expre
nop
j	_LABEL_40
_LABEL_41:
lw	$t0	-28($fp)
li	$t1	98
bne	$t0	$t1	__tLABEL20
li	$t0	1
j	__tLABEL21
__tLABEL20:
li	$t0	0
__tLABEL21:
bne	$t0	1	_LABEL_42
li	$v0	5
syscall
sw	$v0	-24($t9)
move $s0 $sp
lw	$t0	-24($t9)
sw	$t0	($sp)
subi	$sp	$sp	4
jal	fibo
nop
sw	$v0	-12($fp)
lw	$t0	-12($fp)
sw	$t0	-44($t9)  #   ans
li	$v0	11
li	$a0	102
syscall
li	$v0	11
li	$a0	105
syscall
li	$v0	11
li	$a0	98
syscall
li	$v0	11
li	$a0	111
syscall
li	$v0	11
li	$a0	58
syscall
li	$v0	1
lw	$a0	-44($t9)
syscall
li	$v0	4
la	$a0	Enter
syscall
move $s0 $sp
jal	printspace
nop
j	_LABEL_40
_LABEL_42:
lw	$t0	-28($fp)
li	$t1	99
bne	$t0	$t1	__tLABEL22
li	$t0	1
j	__tLABEL23
__tLABEL22:
li	$t0	0
__tLABEL23:
bne	$t0	1	_LABEL_43
li	$v0	5
syscall
sw	$v0	-28($t9)
li	$v0	5
syscall
sw	$v0	-32($t9)
li	$v0	5
syscall
sw	$v0	-36($t9)
move $s0 $sp
lw	$t0	-28($t9)
sw	$t0	($sp)
subi	$sp	$sp	4
lw	$t0	-32($t9)
sw	$t0	($sp)
subi	$sp	$sp	4
lw	$t0	-36($t9)
sw	$t0	($sp)
subi	$sp	$sp	4
jal	operation
nop
sw	$v0	-16($fp)
lw	$t0	-16($fp)
sw	$t0	-44($t9)  #   ans
move $s0 $sp
jal	printspace
nop
j	_LABEL_40
_LABEL_43:
lw	$t0	-28($fp)
li	$t1	100
bne	$t0	$t1	__tLABEL24
li	$t0	1
j	__tLABEL25
__tLABEL24:
li	$t0	0
__tLABEL25:
bne	$t0	1	_LABEL_44
li	$v0	5
syscall
sw	$v0	-40($t9)
move $s0 $sp
lw	$t0	-40($t9)
sw	$t0	($sp)
subi	$sp	$sp	4
jal	display
nop
j	_LABEL_40
_LABEL_44:
lw	$t0	-28($fp)
li	$t1	101
bne	$t0	$t1	__tLABEL26
li	$t0	1
j	__tLABEL27
__tLABEL26:
li	$t0	0
__tLABEL27:
bne	$t0	1	_LABEL_45
li	$v0	5
syscall
sw	$v0	-48($t9)
li	$v0	5
syscall
sw	$v0	-52($t9)
move $s0 $sp
lw	$t0	-48($t9)
sw	$t0	($sp)
subi	$sp	$sp	4
lw	$t0	-52($t9)
sw	$t0	($sp)
subi	$sp	$sp	4
jal	gcd
nop
sw	$v0	-20($fp)
li	$v0	11
li	$a0	103
syscall
li	$v0	11
li	$a0	99
syscall
li	$v0	11
li	$a0	100
syscall
li	$v0	11
li	$a0	58
syscall
li	$v0	1
lw	$a0	-20($fp)
syscall
li	$v0	4
la	$a0	Enter
syscall
move $s0 $sp
jal	printspace
nop
j	_LABEL_40
_LABEL_45:
lw	$t0	-28($fp)
li	$t1	102
bne	$t0	$t1	__tLABEL28
li	$t0	1
j	__tLABEL29
__tLABEL28:
li	$t0	0
__tLABEL29:
bne	$t0	1	_LABEL_46
li	$v0	11
li	$a0	115
syscall
li	$v0	11
li	$a0	116
syscall
li	$v0	11
li	$a0	114
syscall
li	$v0	11
li	$a0	105
syscall
li	$v0	11
li	$a0	110
syscall
li	$v0	11
li	$a0	103
syscall
li	$v0	11
li	$a0	58
syscall
li	$v0	11
li	$a0	33
syscall
li	$v0	11
li	$a0	35
syscall
li	$v0	11
li	$a0	36
syscall
li	$v0	11
li	$a0	37
syscall
li	$v0	11
li	$a0	38
syscall
li	$v0	11
li	$a0	39
syscall
li	$v0	11
li	$a0	40
syscall
li	$v0	11
li	$a0	41
syscall
li	$v0	11
li	$a0	42
syscall
li	$v0	11
li	$a0	43
syscall
li	$v0	11
li	$a0	44
syscall
li	$v0	11
li	$a0	45
syscall
li	$v0	11
li	$a0	46
syscall
li	$v0	11
li	$a0	47
syscall
li	$v0	11
li	$a0	58
syscall
li	$v0	11
li	$a0	59
syscall
li	$v0	11
li	$a0	60
syscall
li	$v0	11
li	$a0	61
syscall
li	$v0	11
li	$a0	62
syscall
li	$v0	11
li	$a0	63
syscall
li	$v0	11
li	$a0	64
syscall
li	$v0	11
li	$a0	91
syscall
li	$v0	11
li	$a0	92
syscall
li	$v0	11
li	$a0	93
syscall
li	$v0	11
li	$a0	94
syscall
li	$v0	11
li	$a0	95
syscall
li	$v0	11
li	$a0	96
syscall
li	$v0	11
li	$a0	123
syscall
li	$v0	11
li	$a0	124
syscall
li	$v0	11
li	$a0	125
syscall
li	$v0	11
li	$a0	126
syscall
j	_LABEL_40
_LABEL_46:
move $s0 $sp
jal	optimize
nop
_LABEL_40:
__FEND_LAB_12:
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
li	$t0	0	#i
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#i
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#num
sw	$t0	($sp)
subi	$sp	$sp	4
move $s0 $sp
jal	testDefine
nop
li	$v0	5
syscall
sw	$v0	-12($fp)
li	$t0	0
sw	$t0	-8($fp)  #   i
j	_LABEL_49
_LABEL_47:
lw	$t0	-8($fp)
lw	$t1	-12($fp)
slt	$t0	$t0	$t1
bne	$t0	1	_LABEL_48
_LABEL_49:
move $s0 $sp
jal	process
nop
lw	$t0	-8($fp)
li	$t1	1
add	$t0	$t0	$t1
sw	$t0	-4($fp)
lw	$t0	-4($fp)
sw	$t0	-8($fp)  #   i
j	_LABEL_47
_LABEL_48:
j	__FEND_LAB_13
li	$v0	11
li	$a0	97
syscall
li	$v0	11
li	$a0	97
syscall
li	$v0	11
li	$a0	97
syscall
__FEND_LAB_13:
lw  $ra 0($fp)
lw  $sp 8($fp)
lw  $fp 4($fp)
li	$v0	10
syscall
