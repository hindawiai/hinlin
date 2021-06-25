<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 1993, 2000 Linus Torvalds
 *
 * Delay routines, using a pre-computed "loops_per_jiffy" value.
 */

#समावेश <linux/module.h>
#समावेश <linux/sched.h> /* क्रम udelay's use of smp_processor_id */
#समावेश <यंत्र/param.h>
#समावेश <यंत्र/smp.h>
#समावेश <linux/delay.h>

/*
 * Use only क्रम very small delays (< 1 msec). 
 *
 * The active part of our cycle counter is only 32-bits wide, and
 * we're treating the dअगरference between two marks as चिन्हित.  On
 * a 1GHz box, that's about 2 seconds.
 */

व्योम
__delay(पूर्णांक loops)
अणु
	पूर्णांक पंचांगp;
	__यंत्र__ __अस्थिर__(
		"	rpcc %0\n"
		"	addl %1,%0,%1\n"
		"1:	rpcc %0\n"
		"	subl %1,%0,%0\n"
		"	bgt %0,1b"
		: "=&r" (पंचांगp), "=r" (loops) : "1"(loops));
पूर्ण
EXPORT_SYMBOL(__delay);

#अगर_घोषित CONFIG_SMP
#घोषणा LPJ	 cpu_data[smp_processor_id()].loops_per_jअगरfy
#अन्यथा
#घोषणा LPJ	 loops_per_jअगरfy
#पूर्ण_अगर

व्योम
udelay(अचिन्हित दीर्घ usecs)
अणु
	usecs *= (((अचिन्हित दीर्घ)HZ << 32) / 1000000) * LPJ;
	__delay((दीर्घ)usecs >> 32);
पूर्ण
EXPORT_SYMBOL(udelay);

व्योम
ndelay(अचिन्हित दीर्घ nsecs)
अणु
	nsecs *= (((अचिन्हित दीर्घ)HZ << 32) / 1000000000) * LPJ;
	__delay((दीर्घ)nsecs >> 32);
पूर्ण
EXPORT_SYMBOL(ndelay);
