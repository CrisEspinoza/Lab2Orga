beq $t0,$t1,FIN
lw $t2, 0($sp)
addi $t4, $zero, 3
FIN:
subi $t0, $t0, 1
addi $t2, $zero, 3
sub $t3, $t2, $t1
addi $t2, $zero, 3
sub $t3, $t2, $t1