<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011 Riअक्षरd Weinberger <richrd@nod.at>
 * Mostly copied from arch/x86/lib/delay.c
 */

#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/param.h>

व्योम __delay(अचिन्हित दीर्घ loops)
अणु
	यंत्र अस्थिर(
		"test %0,%0\n"
		"jz 3f\n"
		"jmp 1f\n"

		".align 16\n"
		"1: jmp 2f\n"

		".align 16\n"
		"2: dec %0\n"
		" jnz 2b\n"
		"3: dec %0\n"

		: /* we करोn't need output */
		: "a" (loops)
	);
पूर्ण
EXPORT_SYMBOL(__delay);

अंतरभूत व्योम __स्थिर_udelay(अचिन्हित दीर्घ xloops)
अणु
	पूर्णांक d0;

	xloops *= 4;
	यंत्र("mull %%edx"
		: "=d" (xloops), "=&a" (d0)
		: "1" (xloops), "0"
		(loops_per_jअगरfy * (HZ/4)));

	__delay(++xloops);
पूर्ण
EXPORT_SYMBOL(__स्थिर_udelay);

व्योम __udelay(अचिन्हित दीर्घ usecs)
अणु
	__स्थिर_udelay(usecs * 0x000010c7); /* 2**32 / 1000000 (rounded up) */
पूर्ण
EXPORT_SYMBOL(__udelay);

व्योम __ndelay(अचिन्हित दीर्घ nsecs)
अणु
	__स्थिर_udelay(nsecs * 0x00005); /* 2**32 / 1000000000 (rounded up) */
पूर्ण
EXPORT_SYMBOL(__ndelay);
