.name "zork"
.comment "just a basic living prog"
l1:     sti r1,%12,%1
l3:     sti r1,r3,%34
        zjmp %:l1
live:   live %:l1
        live %:l3
        zjmp %:l3
        zjmp %:l4
        zjmp %:l1
        zjmp %:l5
        zjmp %:l6
l5:		and %3278012121212112112,12,r11
l6:     sti r2,23,%34
l2:     sti r3,%0,r14
l4:     sti r2,r3,r1
        add r1,r2,r3
