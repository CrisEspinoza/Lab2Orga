lw $t1, 0($sp)
j END
add $t0, $t0, $t5
addi $t2, $zero, 3
sub $t3, $t2, $t1
END:
lw $t1, 0($sp)
add $t0, $t1, $t5
j FIN
addi $t2, $zero, 3
sub $t3, $t2, $t1
FIN:
lw $t1, 0($sp)
add $t0, $t1, $t5