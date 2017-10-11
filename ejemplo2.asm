beq $t0,$t1,END
lw $t2, 0($sp)
addi $t2, $zero, 3
sub $t3, $t2, $t1
addi $t2, $zero, 3
sub $t3, $t2, $t1
addi $t2, $zero, 3
sub $t3, $t2, $t1
END:
addi $t3, $zero, 3
sub $t4, $t5, $t6