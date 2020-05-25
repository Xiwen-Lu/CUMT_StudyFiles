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
		sw	$s1	4($t8)
		sw	$s2	8($t8)
		sw	$s3	12($t8)
		sw	$s4	16($t8)
		sw	$s5	20($t8)
		sw	$s6	24($t8)
		sw	$s7	28($t8)
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
		lw	$s1	-288($fp)
		lw	$s2	-284($fp)
		lw	$s3	-280($fp)
		lw	$s4	-276($fp)
		lw	$s5	-272($fp)
		lw	$s6	-268($fp)
		lw	$s7	-264($fp)
li	$t0	0	#arr1
sw	$t0	($sp)
subi	$sp	$sp	4
li	$t0	0	#var2
sw	$t0	($sp)
subi	$sp	$sp	4
		lw	$s1	-296($fp)
		lw	$s2	-292($fp)
		lw	$s3	-288($fp)
		lw	$s4	-284($fp)
		lw	$s5	-280($fp)
		lw	$s6	-276($fp)
		lw	$s7	-272($fp)
subi	$sp	$sp	8
li	$t0	0	#var3
sw	$t0	($sp)
subi	$sp	$sp	4
		lw	$s1	-308($fp)
		lw	$s2	-300($fp)
		lw	$s3	-296($fp)
		lw	$s4	-292($fp)
		lw	$s5	-288($fp)
		lw	$s6	-284($fp)
		lw	$s7	-280($fp)
subi	$sp	$sp	12
li	$t0	0	#var4
sw	$t0	($sp)
subi	$sp	$sp	4
		lw	$s1	-324($fp)
		lw	$s2	-312($fp)
		lw	$s3	-308($fp)
		lw	$s4	-300($fp)
		lw	$s5	-296($fp)
		lw	$s6	-292($fp)
		lw	$s7	-288($fp)
subi	$sp	$sp	16
li	$t0	0	#var5
sw	$t0	($sp)
subi	$sp	$sp	4
		lw	$s1	-344($fp)
		lw	$s2	-328($fp)
		lw	$s3	-324($fp)
		lw	$s4	-312($fp)
		lw	$s5	-308($fp)
		lw	$s6	-300($fp)
		lw	$s7	-296($fp)
subi	$sp	$sp	20
li	$t0	0	#var6
sw	$t0	($sp)
subi	$sp	$sp	4
		lw	$s1	-368($fp)
		lw	$s2	-348($fp)
		lw	$s3	-344($fp)
		lw	$s4	-328($fp)
		lw	$s5	-324($fp)
		lw	$s6	-312($fp)
		lw	$s7	-308($fp)
subi	$sp	$sp	24
li	$t0	0	#var7
sw	$t0	($sp)
subi	$sp	$sp	4
		lw	$s1	-396($fp)
		lw	$s2	-372($fp)
		lw	$s3	-368($fp)
		lw	$s4	-348($fp)
		lw	$s5	-344($fp)
		lw	$s6	-328($fp)
		lw	$s7	-324($fp)
subi	$sp	$sp	28
li	$t0	0	#var8
sw	$t0	($sp)
subi	$sp	$sp	4
		lw	$s1	-428($fp)
		lw	$s2	-400($fp)
		lw	$s3	-396($fp)
		lw	$s4	-372($fp)
		lw	$s5	-368($fp)
		lw	$s6	-348($fp)
		lw	$s7	-344($fp)
subi	$sp	$sp	32
li	$t0	0	#var9
sw	$t0	($sp)
subi	$sp	$sp	4
		lw	$s1	-464($fp)
		lw	$s2	-432($fp)
		lw	$s3	-428($fp)
		lw	$s4	-400($fp)
		lw	$s5	-396($fp)
		lw	$s6	-372($fp)
		lw	$s7	-368($fp)
subi	$sp	$sp	36
li	$t0	0	#var10
sw	$t0	($sp)
subi	$sp	$sp	4
		lw	$s1	-504($fp)
		lw	$s2	-468($fp)
		lw	$s3	-464($fp)
		lw	$s4	-432($fp)
		lw	$s5	-428($fp)
		lw	$s6	-400($fp)
		lw	$s7	-396($fp)
subi	$sp	$sp	40
li	$t0	0	#var11
sw	$t0	($sp)
subi	$sp	$sp	4
		lw	$s1	-548($fp)
		lw	$s2	-508($fp)
		lw	$s3	-504($fp)
		lw	$s4	-468($fp)
		lw	$s5	-464($fp)
		lw	$s6	-432($fp)
		lw	$s7	-428($fp)
subi	$sp	$sp	44
li	$t0	0	#var12
sw	$t0	($sp)
subi	$sp	$sp	4
		lw	$s1	-596($fp)
		lw	$s2	-552($fp)
		lw	$s3	-548($fp)
		lw	$s4	-508($fp)
		lw	$s5	-504($fp)
		lw	$s6	-468($fp)
		lw	$s7	-464($fp)
subi	$sp	$sp	48
li	$t0	0	#var13
sw	$t0	($sp)
subi	$sp	$sp	4
		lw	$s1	-648($fp)
		lw	$s2	-600($fp)
		lw	$s3	-596($fp)
		lw	$s4	-552($fp)
		lw	$s5	-548($fp)
		lw	$s6	-508($fp)
		lw	$s7	-504($fp)
subi	$sp	$sp	52
li	$t0	0	#var14
sw	$t0	($sp)
subi	$sp	$sp	4
		lw	$s1	-704($fp)
		lw	$s2	-652($fp)
		lw	$s3	-648($fp)
		lw	$s4	-600($fp)
		lw	$s5	-596($fp)
		lw	$s6	-552($fp)
		lw	$s7	-548($fp)
subi	$sp	$sp	56
li	$t0	0	#var15
sw	$t0	($sp)
subi	$sp	$sp	4
		lw	$s1	-764($fp)
		lw	$s2	-708($fp)
		lw	$s3	-704($fp)
		lw	$s4	-652($fp)
		lw	$s5	-648($fp)
		lw	$s6	-600($fp)
		lw	$s7	-596($fp)
subi	$sp	$sp	60
li	$t0	0	#var16
sw	$t0	($sp)
subi	$sp	$sp	4
		lw	$s1	-828($fp)
		lw	$s2	-768($fp)
		lw	$s3	-764($fp)
		lw	$s4	-708($fp)
		lw	$s5	-704($fp)
		lw	$s6	-652($fp)
		lw	$s7	-648($fp)
subi	$sp	$sp	64
li	$t0	0	#var17
sw	$t0	($sp)
subi	$sp	$sp	4
		lw	$s1	-896($fp)
		lw	$s2	-832($fp)
		lw	$s3	-828($fp)
		lw	$s4	-768($fp)
		lw	$s5	-764($fp)
		lw	$s6	-708($fp)
		lw	$s7	-704($fp)
subi	$sp	$sp	68
li	$t0	0	#var18
sw	$t0	($sp)
subi	$sp	$sp	4
		lw	$s1	-968($fp)
		lw	$s2	-900($fp)
		lw	$s3	-896($fp)
		lw	$s4	-832($fp)
		lw	$s5	-828($fp)
		lw	$s6	-768($fp)
		lw	$s7	-764($fp)
subi	$sp	$sp	72
li	$t0	0	#var19
sw	$t0	($sp)
subi	$sp	$sp	4
		lw	$s1	-1044($fp)
		lw	$s2	-972($fp)
		lw	$s3	-968($fp)
		lw	$s4	-900($fp)
		lw	$s5	-896($fp)
		lw	$s6	-832($fp)
		lw	$s7	-828($fp)
subi	$sp	$sp	76
__FEND_LAB_14:
lw  $ra 0($fp)
lw  $sp 8($fp)
lw  $fp 4($fp)
		lw	$s1	4($t8)
		lw	$s2	8($t8)
		lw	$s3	12($t8)
		lw	$s4	16($t8)
		lw	$s5	20($t8)
		lw	$s6	24($t8)
		lw	$s7	28($t8)
jr	$ra	
fibo:
#Save Register
		sw	$s1	4($t8)
		sw	$s2	8($t8)
		sw	$s3	12($t8)
		sw	$s4	16($t8)
		sw	$s5	20($t8)
		sw	$s6	24($t8)
		sw	$s7	28($t8)
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
j	__FEND_LAB_15
j	_LABEL_1
_LABEL_0:
lw	$t0	12($fp)
li	$t1	0
bne	$t0	$t1	__tLABEL30
li	$t0	1
j	__tLABEL31
__tLABEL30:
li	$t0	0
__tLABEL31:
bne	$t0	1	_LABEL_2
li	$v0	0
j	__FEND_LAB_15
j	_LABEL_3
_LABEL_2:
lw	$t0	12($fp)
li	$t1	1
bne	$t0	$t1	__tLABEL32
li	$t0	1
j	__tLABEL33
__tLABEL32:
li	$t0	0
__tLABEL33:
bne	$t0	1	_LABEL_4
li	$v0	1
j	__FEND_LAB_15
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
j	__FEND_LAB_15
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
j	__FEND_LAB_15
_LABEL_7:
_LABEL_5:
_LABEL_3:
_LABEL_1:
__FEND_LAB_15:
lw  $ra 0($fp)
lw  $sp 8($fp)
lw  $fp 4($fp)
		lw	$s1	4($t8)
		lw	$s2	8($t8)
		lw	$s3	12($t8)
		lw	$s4	16($t8)
		lw	$s5	20($t8)
		lw	$s6	24($t8)
		lw	$s7	28($t8)
jr	$ra	
upcase:
#Save Register
		sw	$s1	4($t8)
		sw	$s2	8($t8)
		sw	$s3	12($t8)
		sw	$s4	16($t8)
		sw	$s5	20($t8)
		sw	$s6	24($t8)
		sw	$s7	28($t8)
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
		lw	$s1	-8($fp)
		lw	$s2	-4($fp)
		lw	$s3	-12($fp)
		lw	$s4	12($fp)
		add	$t0	$s4	$0
li	$t1	97
slt	$t0	$t0	$t1
li	$t1	1
sub	$t0	$t1	$t0
bne	$t0	1	_LABEL_8
		add	$t0	$s4	$0
li	$t1	122
slt	$t0	$t1	$t0
li	$t1	1
sub	$t0	$t1	$t0
bne	$t0	1	_LABEL_10
		add	$t0	$s4	$0
li	$t1	97
sub	$t0	$t0	$t1
		add	$s2	$t0	$0
		add	$t0	$s2	$0
li	$t1	65
add	$t0	$t0	$t1
		add	$s1	$t0	$0
		add	$t0	$s1	$0
		add	$s3	$t0	$0
		add	$v0	$s3	$0
j	__FEND_LAB_16
j	_LABEL_11
_LABEL_10:
		add	$v0	$s4	$0
j	__FEND_LAB_16
_LABEL_11:
j	_LABEL_9
_LABEL_8:
		add	$v0	$s4	$0
j	__FEND_LAB_16
_LABEL_9:
__FEND_LAB_16:
lw  $ra 0($fp)
lw  $sp 8($fp)
lw  $fp 4($fp)
		lw	$s1	4($t8)
		lw	$s2	8($t8)
		lw	$s3	12($t8)
		lw	$s4	16($t8)
		lw	$s5	20($t8)
		lw	$s6	24($t8)
		lw	$s7	28($t8)
jr	$ra	
lowcase:
#Save Register
		sw	$s1	4($t8)
		sw	$s2	8($t8)
		sw	$s3	12($t8)
		sw	$s4	16($t8)
		sw	$s5	20($t8)
		sw	$s6	24($t8)
		sw	$s7	28($t8)
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
		lw	$s1	-8($fp)
		lw	$s2	-4($fp)
		lw	$s3	-12($fp)
		lw	$s4	12($fp)
		add	$t0	$s4	$0
li	$t1	65
slt	$t0	$t0	$t1
li	$t1	1
sub	$t0	$t1	$t0
bne	$t0	1	_LABEL_12
		add	$t0	$s4	$0
li	$t1	90
slt	$t0	$t1	$t0
li	$t1	1
sub	$t0	$t1	$t0
bne	$t0	1	_LABEL_14
		add	$t0	$s4	$0
li	$t1	65
sub	$t0	$t0	$t1
		add	$s2	$t0	$0
		add	$t0	$s2	$0
li	$t1	97
add	$t0	$t0	$t1
		add	$s1	$t0	$0
		add	$t0	$s1	$0
		add	$s3	$t0	$0
		add	$v0	$s3	$0
j	__FEND_LAB_17
j	_LABEL_15
_LABEL_14:
		add	$v0	$s4	$0
j	__FEND_LAB_17
_LABEL_15:
j	_LABEL_13
_LABEL_12:
		add	$v0	$s4	$0
j	__FEND_LAB_17
_LABEL_13:
__FEND_LAB_17:
lw  $ra 0($fp)
lw  $sp 8($fp)
lw  $fp 4($fp)
		lw	$s1	4($t8)
		lw	$s2	8($t8)
		lw	$s3	12($t8)
		lw	$s4	16($t8)
		lw	$s5	20($t8)
		lw	$s6	24($t8)
		lw	$s7	28($t8)
jr	$ra	
printspace:
#Save Register
		sw	$s1	4($t8)
		sw	$s2	8($t8)
		sw	$s3	12($t8)
		sw	$s4	16($t8)
		sw	$s5	20($t8)
		sw	$s6	24($t8)
		sw	$s7	28($t8)
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
__FEND_LAB_18:
lw  $ra 0($fp)
lw  $sp 8($fp)
lw  $fp 4($fp)
		lw	$s1	4($t8)
		lw	$s2	8($t8)
		lw	$s3	12($t8)
		lw	$s4	16($t8)
		lw	$s5	20($t8)
		lw	$s6	24($t8)
		lw	$s7	28($t8)
jr	$ra	
operation:
#Save Register
		sw	$s1	4($t8)
		sw	$s2	8($t8)
		sw	$s3	12($t8)
		sw	$s4	16($t8)
		sw	$s5	20($t8)
		sw	$s6	24($t8)
		sw	$s7	28($t8)
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
bne	$t0	$t1	__tLABEL34
li	$t0	1
j	__tLABEL35
__tLABEL34:
li	$t0	0
__tLABEL35:
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
j	__FEND_LAB_19
j	_LABEL_16
_LABEL_17:
lw	$t0	12($fp)
li	$t1	2
bne	$t0	$t1	__tLABEL36
li	$t0	1
j	__tLABEL37
__tLABEL36:
li	$t0	0
__tLABEL37:
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
j	__FEND_LAB_19
j	_LABEL_16
_LABEL_18:
lw	$t0	12($fp)
li	$t1	3
bne	$t0	$t1	__tLABEL38
li	$t0	1
j	__tLABEL39
__tLABEL38:
li	$t0	0
__tLABEL39:
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
j	__FEND_LAB_19
j	_LABEL_16
_LABEL_19:
lw	$t0	12($fp)
li	$t1	4
bne	$t0	$t1	__tLABEL40
li	$t0	1
j	__tLABEL41
__tLABEL40:
li	$t0	0
__tLABEL41:
bne	$t0	1	_LABEL_20
lw	$t0	16($fp)
li	$t1	0
beq	$t0	$t1	__tLABEL42
li	$t0	1
j	__tLABEL43
__tLABEL42:
li	$t0	0
__tLABEL43:
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
j	__FEND_LAB_19
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
j	__FEND_LAB_19
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
j	__FEND_LAB_19
_LABEL_16:
__FEND_LAB_19:
lw  $ra 0($fp)
lw  $sp 8($fp)
lw  $fp 4($fp)
		lw	$s1	4($t8)
		lw	$s2	8($t8)
		lw	$s3	12($t8)
		lw	$s4	16($t8)
		lw	$s5	20($t8)
		lw	$s6	24($t8)
		lw	$s7	28($t8)
jr	$ra	
display:
#Save Register
		sw	$s1	4($t8)
		sw	$s2	8($t8)
		sw	$s3	12($t8)
		sw	$s4	16($t8)
		sw	$s5	20($t8)
		sw	$s6	24($t8)
		sw	$s7	28($t8)
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
		lw	$s1	-40($fp)
		lw	$s2	-16($fp)
		lw	$s3	-8($fp)
		lw	$s4	-4($fp)
		lw	$s5	-44($fp)
		lw	$s6	-36($fp)
		lw	$s7	-20($fp)
lw	$t0	12($fp)
li	$t1	0
slt	$t0	$t1	$t0
li	$t1	1
sub	$t0	$t1	$t0
bne	$t0	1	_LABEL_23
j	__FEND_LAB_20
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
		add	$s1	$t0	$0
lw	$t0	-4($t9)
		add	$s5	$t0	$0
li	$t0	0
		add	$s1	$t0	$0
j	_LABEL_29
_LABEL_27:
		add	$t0	$s1	$0
lw	$t1	12($fp)
slt	$t0	$t0	$t1
bne	$t0	1	_LABEL_28
_LABEL_29:
move $s0 $sp
		add	$t0	$s5	$0
sw	$t0	($sp)
subi	$sp	$sp	4
jal	upcase
nop
		add	$s4	$v0	$0
		add	$t1	$s1	$0
mul	$t1	$t1	-4
addi	$t1	$t1	-60
		add	$t0	$s4	$0
add	$t1	$t1	$t9
sw	$t0	0($t1)
move $s0 $sp
		add	$t0	$s5	$0
sw	$t0	($sp)
subi	$sp	$sp	4
jal	upcase
nop
		add	$s3	$v0	$0
		add	$t1	$s1	$0
mul	$t1	$t1	-4
addi	$t1	$t1	-60
		add	$t0	$s3	$0
add	$t1	$t1	$t9
sw	$t0	0($t1)
		add	$t1	$s1	$0
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
		add	$t0	$s5	$0
li	$t1	1
add	$t0	$t0	$t1
		add	$s2	$t0	$0
		add	$t0	$s2	$0
		add	$s5	$t0	$0
		add	$t0	$s1	$0
li	$t1	1
add	$t0	$t0	$t1
		add	$s7	$t0	$0
		add	$t0	$s7	$0
		add	$s1	$t0	$0
j	_LABEL_27
_LABEL_28:
move $s0 $sp
jal	printspace
nop
li	$t0	0
		add	$s1	$t0	$0
li	$t0	0
		add	$s1	$t0	$0
j	_LABEL_32
_LABEL_30:
		add	$t0	$s1	$0
lw	$t1	12($fp)
slt	$t0	$t0	$t1
bne	$t0	1	_LABEL_31
_LABEL_32:
		add	$t1	$s1	$0
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
		add	$t1	$s1	$0
mul	$t1	$t1	-4
addi	$t1	$t1	-60
lw	$t0	-28($fp)
add	$t1	$t1	$t9
sw	$t0	0($t1)
		add	$t1	$s1	$0
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
		add	$t0	$s1	$0
li	$t1	1
add	$t0	$t0	$t1
		add	$s6	$t0	$0
		add	$t0	$s6	$0
		add	$s1	$t0	$0
j	_LABEL_30
_LABEL_31:
move $s0 $sp
jal	printspace
nop
_LABEL_26:
_LABEL_24:
__FEND_LAB_20:
lw  $ra 0($fp)
lw  $sp 8($fp)
lw  $fp 4($fp)
		lw	$s1	4($t8)
		lw	$s2	8($t8)
		lw	$s3	12($t8)
		lw	$s4	16($t8)
		lw	$s5	20($t8)
		lw	$s6	24($t8)
		lw	$s7	28($t8)
jr	$ra	
expre:
#Save Register
		sw	$s1	4($t8)
		sw	$s2	8($t8)
		sw	$s3	12($t8)
		sw	$s4	16($t8)
		sw	$s5	20($t8)
		sw	$s6	24($t8)
		sw	$s7	28($t8)
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
		lw	$s1	-44($fp)
		lw	$s2	-16($fp)
		lw	$s3	-8($fp)
		lw	$s4	-4($fp)
		lw	$s5	-20($fp)
		lw	$s6	-12($fp)
		lw	$s7	-40($fp)
li	$v0	5
syscall
sw	$v0	-36($fp)
li	$v0	5
syscall
		add	$s7	$v0	$0
lw	$t0	-36($fp)
		add	$t1	$s7	$0
add	$t0	$t0	$t1
		add	$s4	$t0	$0
li	$t0	0 
li	$t1	2
sub	$t0	$t0	$t1
		add	$s3	$t0	$0
		add	$t0	$s7	$0
		add	$t1	$s3	$0
mul	$t0	$t0	$t1
		add	$s6	$t0	$0
li	$t0	0 
		add	$t1	$s6	$0
sub	$t0	$t0	$t1
		add	$s2	$t0	$0
		add	$t0	$s4	$0
		add	$t1	$s2	$0
sub	$t0	$t0	$t1
		add	$s5	$t0	$0
li	$t0	2
li	$t1	0
mul	$t0	$t0	$t1
sw	$t0	-24($fp)
li	$t0	0 
lw	$t1	-24($fp)
sub	$t0	$t0	$t1
sw	$t0	-28($fp)
		add	$t0	$s5	$0
lw	$t1	-28($fp)
add	$t0	$t0	$t1
sw	$t0	-32($fp)
lw	$t0	-32($fp)
		add	$s1	$t0	$0
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
		add	$a0	$s1	$0
syscall
li	$v0	4
la	$a0	Enter
syscall
move $s0 $sp
jal	printspace
nop
__FEND_LAB_21:
lw  $ra 0($fp)
lw  $sp 8($fp)
lw  $fp 4($fp)
		lw	$s1	4($t8)
		lw	$s2	8($t8)
		lw	$s3	12($t8)
		lw	$s4	16($t8)
		lw	$s5	20($t8)
		lw	$s6	24($t8)
		lw	$s7	28($t8)
jr	$ra	
mod:
#Save Register
		sw	$s1	4($t8)
		sw	$s2	8($t8)
		sw	$s3	12($t8)
		sw	$s4	16($t8)
		sw	$s5	20($t8)
		sw	$s6	24($t8)
		sw	$s7	28($t8)
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
		lw	$s1	16($fp)
		lw	$s2	-8($fp)
		lw	$s3	-4($fp)
		lw	$s4	12($fp)
		lw	$s5	-12($fp)
		lw	$s6	-16($fp)
		add	$t0	$s1	$0
		add	$t1	$s4	$0
div	$t0	$t0	$t1
		add	$s3	$t0	$0
		add	$t0	$s3	$0
		add	$t1	$s4	$0
mul	$t0	$t0	$t1
		add	$s2	$t0	$0
		add	$t0	$s1	$0
		add	$t1	$s2	$0
sub	$t0	$t0	$t1
		add	$s5	$t0	$0
		add	$t0	$s5	$0
		add	$s6	$t0	$0
		add	$v0	$s6	$0
j	__FEND_LAB_22
__FEND_LAB_22:
lw  $ra 0($fp)
lw  $sp 8($fp)
lw  $fp 4($fp)
		lw	$s1	4($t8)
		lw	$s2	8($t8)
		lw	$s3	12($t8)
		lw	$s4	16($t8)
		lw	$s5	20($t8)
		lw	$s6	24($t8)
		lw	$s7	28($t8)
jr	$ra	
gcd:
#Save Register
		sw	$s1	4($t8)
		sw	$s2	8($t8)
		sw	$s3	12($t8)
		sw	$s4	16($t8)
		sw	$s5	20($t8)
		sw	$s6	24($t8)
		sw	$s7	28($t8)
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
bne	$t0	$t1	__tLABEL44
li	$t0	1
j	__tLABEL45
__tLABEL44:
li	$t0	0
__tLABEL45:
bne	$t0	1	_LABEL_33
li	$v0	0
j	__FEND_LAB_23
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
bne	$t0	$t1	__tLABEL46
li	$t0	1
j	__tLABEL47
__tLABEL46:
li	$t0	0
__tLABEL47:
bne	$t0	1	_LABEL_35
lw	$v0	12($fp)
j	__FEND_LAB_23
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
j	__FEND_LAB_23
_LABEL_36:
_LABEL_34:
__FEND_LAB_23:
lw  $ra 0($fp)
lw  $sp 8($fp)
lw  $fp 4($fp)
		lw	$s1	4($t8)
		lw	$s2	8($t8)
		lw	$s3	12($t8)
		lw	$s4	16($t8)
		lw	$s5	20($t8)
		lw	$s6	24($t8)
		lw	$s7	28($t8)
jr	$ra	
optimize:
#Save Register
		sw	$s1	4($t8)
		sw	$s2	8($t8)
		sw	$s3	12($t8)
		sw	$s4	16($t8)
		sw	$s5	20($t8)
		sw	$s6	24($t8)
		sw	$s7	28($t8)
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
		lw	$s1	-44($fp)
		lw	$s2	-16($fp)
		lw	$s3	-8($fp)
		lw	$s4	-4($fp)
		lw	$s5	-40($fp)
		lw	$s6	-20($fp)
		lw	$s7	-12($fp)
li	$t0	0
sw	$t0	-28($fp)  #   i
li	$t0	1
		add	$s5	$t0	$0
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
		add	$t1	$s5	$0
sub	$t0	$t0	$t1
		add	$s4	$t0	$0
		add	$t0	$s4	$0
		add	$s1	$t0	$0
lw	$t0	-36($fp)
		add	$t1	$s1	$0
mul	$t0	$t0	$t1
		add	$s3	$t0	$0
		add	$t0	$s3	$0
sw	$t0	-48($fp)  #   t2
li	$t0	0 
		add	$t1	$s5	$0
sub	$t0	$t0	$t1
		add	$s7	$t0	$0
		add	$t0	$s7	$0
sw	$t0	-52($fp)  #   t3
lw	$t0	-36($fp)
lw	$t1	-52($fp)
mul	$t0	$t0	$t1
		add	$s2	$t0	$0
		add	$t0	$s2	$0
		add	$s5	$t0	$0
lw	$t0	-48($fp)
		add	$t1	$s5	$0
add	$t0	$t0	$t1
		add	$s6	$t0	$0
		add	$t0	$s6	$0
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
		add	$a0	$s5	$0
syscall
li	$v0	4
la	$a0	Enter
syscall
move $s0 $sp
jal	printspace
nop
li	$v0	1
		add	$a0	$s1	$0
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
__FEND_LAB_24:
lw  $ra 0($fp)
lw  $sp 8($fp)
lw  $fp 4($fp)
		lw	$s1	4($t8)
		lw	$s2	8($t8)
		lw	$s3	12($t8)
		lw	$s4	16($t8)
		lw	$s5	20($t8)
		lw	$s6	24($t8)
		lw	$s7	28($t8)
jr	$ra	
process:
#Save Register
		sw	$s1	4($t8)
		sw	$s2	8($t8)
		sw	$s3	12($t8)
		sw	$s4	16($t8)
		sw	$s5	20($t8)
		sw	$s6	24($t8)
		sw	$s7	28($t8)
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
		lw	$s1	-8($fp)
		lw	$s2	-4($fp)
		lw	$s3	-16($fp)
		lw	$s4	-12($fp)
		lw	$s5	-20($fp)
		lw	$s6	-28($fp)
		lw	$s7	-24($fp)
li	$v0	5
syscall
		add	$s7	$v0	$0
		add	$t0	$s7	$0
li	$t1	97
add	$t0	$t0	$t1
		add	$s2	$t0	$0
		add	$t0	$s2	$0
li	$t1	1
sub	$t0	$t0	$t1
		add	$s1	$t0	$0
		add	$t0	$s1	$0
		add	$s6	$t0	$0
		add	$t0	$s6	$0
li	$t1	97
bne	$t0	$t1	__tLABEL48
li	$t0	1
j	__tLABEL49
__tLABEL48:
li	$t0	0
__tLABEL49:
bne	$t0	1	_LABEL_41
move $s0 $sp
jal	expre
nop
j	_LABEL_40
_LABEL_41:
		add	$t0	$s6	$0
li	$t1	98
bne	$t0	$t1	__tLABEL50
li	$t0	1
j	__tLABEL51
__tLABEL50:
li	$t0	0
__tLABEL51:
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
		add	$s4	$v0	$0
		add	$t0	$s4	$0
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
		add	$t0	$s6	$0
li	$t1	99
bne	$t0	$t1	__tLABEL52
li	$t0	1
j	__tLABEL53
__tLABEL52:
li	$t0	0
__tLABEL53:
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
		add	$s3	$v0	$0
		add	$t0	$s3	$0
sw	$t0	-44($t9)  #   ans
move $s0 $sp
jal	printspace
nop
j	_LABEL_40
_LABEL_43:
		add	$t0	$s6	$0
li	$t1	100
bne	$t0	$t1	__tLABEL54
li	$t0	1
j	__tLABEL55
__tLABEL54:
li	$t0	0
__tLABEL55:
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
		add	$t0	$s6	$0
li	$t1	101
bne	$t0	$t1	__tLABEL56
li	$t0	1
j	__tLABEL57
__tLABEL56:
li	$t0	0
__tLABEL57:
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
		add	$s5	$v0	$0
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
		add	$a0	$s5	$0
syscall
li	$v0	4
la	$a0	Enter
syscall
move $s0 $sp
jal	printspace
nop
j	_LABEL_40
_LABEL_45:
		add	$t0	$s6	$0
li	$t1	102
bne	$t0	$t1	__tLABEL58
li	$t0	1
j	__tLABEL59
__tLABEL58:
li	$t0	0
__tLABEL59:
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
__FEND_LAB_25:
lw  $ra 0($fp)
lw  $sp 8($fp)
lw  $fp 4($fp)
		lw	$s1	4($t8)
		lw	$s2	8($t8)
		lw	$s3	12($t8)
		lw	$s4	16($t8)
		lw	$s5	20($t8)
		lw	$s6	24($t8)
		lw	$s7	28($t8)
jr	$ra	
__main:
#Save Register
		sw	$s1	4($t8)
		sw	$s2	8($t8)
		sw	$s3	12($t8)
		sw	$s4	16($t8)
		sw	$s5	20($t8)
		sw	$s6	24($t8)
		sw	$s7	28($t8)
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
		lw	$s1	-8($fp)
		lw	$s2	-4($fp)
		lw	$s3	-12($fp)
move $s0 $sp
jal	testDefine
nop
li	$v0	5
syscall
		add	$s3	$v0	$0
li	$t0	0
		add	$s1	$t0	$0
j	_LABEL_49
_LABEL_47:
		add	$t0	$s1	$0
		add	$t1	$s3	$0
slt	$t0	$t0	$t1
bne	$t0	1	_LABEL_48
_LABEL_49:
move $s0 $sp
jal	process
nop
		add	$t0	$s1	$0
li	$t1	1
add	$t0	$t0	$t1
		add	$s2	$t0	$0
		add	$t0	$s2	$0
		add	$s1	$t0	$0
j	_LABEL_47
_LABEL_48:
j	__FEND_LAB_26
li	$v0	11
li	$a0	97
syscall
li	$v0	11
li	$a0	97
syscall
li	$v0	11
li	$a0	97
syscall
__FEND_LAB_26:
lw  $ra 0($fp)
lw  $sp 8($fp)
lw  $fp 4($fp)
		lw	$s1	4($t8)
		lw	$s2	8($t8)
		lw	$s3	12($t8)
		lw	$s4	16($t8)
		lw	$s5	20($t8)
		lw	$s6	24($t8)
		lw	$s7	28($t8)
li	$v0	10
syscall
