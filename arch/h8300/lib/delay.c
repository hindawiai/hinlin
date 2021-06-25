<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * delay loops
 *
 * Copyright (C) 2015 Yoshinori Sato
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/param.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/समयx.h>

व्योम __delay(अचिन्हित दीर्घ cycles)
अणु
	__यंत्र__ अस्थिर ("1: dec.l #1,%0\n\t"
			  "bne 1b":"=r"(cycles):"0"(cycles));
पूर्ण
EXPORT_SYMBOL(__delay);

व्योम __स्थिर_udelay(अचिन्हित दीर्घ xloops)
अणु
	u64 loops;

	loops = (u64)xloops * loops_per_jअगरfy * HZ;

	__delay(loops >> 32);
पूर्ण
EXPORT_SYMBOL(__स्थिर_udelay);

व्योम __udelay(अचिन्हित दीर्घ usecs)
अणु
	__स्थिर_udelay(usecs * 0x10C7UL); /* 2**32 / 1000000 (rounded up) */
पूर्ण
EXPORT_SYMBOL(__udelay);

व्योम __ndelay(अचिन्हित दीर्घ nsecs)
अणु
	__स्थिर_udelay(nsecs * 0x5UL); /* 2**32 / 1000000000 (rounded up) */
पूर्ण
EXPORT_SYMBOL(__ndelay);
