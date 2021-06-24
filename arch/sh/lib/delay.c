<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	Precise Delay Loops क्रम SuperH
 *
 *	Copyright (C) 1999 Niibe Yutaka & Kaz Kojima
 */

#समावेश <linux/sched.h>
#समावेश <linux/delay.h>

व्योम __delay(अचिन्हित दीर्घ loops)
अणु
	__यंत्र__ __अस्थिर__(
		/*
		 * ST40-300 appears to have an issue with this code,
		 * normally taking two cycles each loop, as with all
		 * other SH variants. If however the branch and the
		 * delay slot straddle an 8 byte boundary, this increases
		 * to 3 cycles.
		 * This align directive ensures this करोesn't occur.
		 */
		".balign 8\n\t"

		"tst	%0, %0\n\t"
		"1:\t"
		"bf/s	1b\n\t"
		" dt	%0"
		: "=r" (loops)
		: "0" (loops)
		: "t");
पूर्ण

अंतरभूत व्योम __स्थिर_udelay(अचिन्हित दीर्घ xloops)
अणु
	xloops *= 4;
	__यंत्र__("dmulu.l	%0, %2\n\t"
		"sts	mach, %0"
		: "=r" (xloops)
		: "0" (xloops),
		  "r" (cpu_data[raw_smp_processor_id()].loops_per_jअगरfy * (HZ/4))
		: "macl", "mach");
	__delay(++xloops);
पूर्ण

व्योम __udelay(अचिन्हित दीर्घ usecs)
अणु
	__स्थिर_udelay(usecs * 0x000010c6);  /* 2**32 / 1000000 */
पूर्ण

व्योम __ndelay(अचिन्हित दीर्घ nsecs)
अणु
	__स्थिर_udelay(nsecs * 0x00000005);
पूर्ण

