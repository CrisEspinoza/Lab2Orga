beq $t0,$t1,FIN
lw $t2, 0($sp)
addi $a2, $zero, 3
FIN:
subi $t0, $t0, 1
addi $t2, $zero, 3
sub $t3, $t2, $t1
addi $t2, $zero, 3
sub $t3, $t2, $t1
beq $a3,$a2,END
lw $t2, 0($sp)
lw $t2, 0($sp)
END:
subi $t0, $t0, 1
addi $t2, $zero, 3
sub $t3, $t2, $t1
addi $t2, $zero, 3