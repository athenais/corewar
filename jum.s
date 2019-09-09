#debut du mega truc qu'il est trop dur a faire

.name "Jumper !"
.comment "en fait C forker !"

gobepc:	st r1,:buff
	st r6,-4
	ld :buff,r1
debut:	ld %0,r7
	zjmp %:suite

buff:	st r1,r1	
		
suite:	sti r1,%:livel,%1
livel:	live %66
	sti r2,%:debut,%-60
	ld %4,r4
	st r2,512
finboucle1:	xor r3,r3,r3
		zjmp %1
