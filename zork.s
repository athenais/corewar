.name "zork"
.comment "just a basic living prog"

        sti r1    ,%12,%1 #
		and %3278012121212112112,12, r11
        sti r2,23,%34
l2:     sti r3,%0,r14
        sti r1,r3,%34
        sti r2,r3,r1
        add r1,r2,r3

live:   live %12
        zjmp %:l2
