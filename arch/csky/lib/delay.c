<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microप्रणालीs co.,ltd.
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>

व्योम __delay(अचिन्हित दीर्घ loops)
अणु
	यंत्र अस्थिर (
		"mov r0, r0\n"
		"1:declt %0\n"
		"bf	1b"
		: "=r"(loops)
		: "0"(loops));
पूर्ण
EXPORT_SYMBOL(__delay);

व्योम __स्थिर_udelay(अचिन्हित दीर्घ xloops)
अणु
	अचिन्हित दीर्घ दीर्घ loops;

	loops = (अचिन्हित दीर्घ दीर्घ)xloops * loops_per_jअगरfy * HZ;

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
