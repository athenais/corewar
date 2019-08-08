.name "zork"
.comment "just a basic living prog"

l2:     sti r1,%-12,%1
		and r1,%12,r1
        sti r2,23,%34
        sti  r15,%0,r14

live:   live %1
        zjmp %:live
