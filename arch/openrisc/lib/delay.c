<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OpenRISC Linux
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * Modअगरications क्रम the OpenRISC architecture:
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 *
 * Precise Delay Loops
 */

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <यंत्र/param.h>
#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/समयx.h>
#समावेश <यंत्र/processor.h>

पूर्णांक पढ़ो_current_समयr(अचिन्हित दीर्घ *समयr_value)
अणु
	*समयr_value = get_cycles();
	वापस 0;
पूर्ण

व्योम __delay(अचिन्हित दीर्घ cycles)
अणु
	cycles_t start = get_cycles();

	जबतक ((get_cycles() - start) < cycles)
		cpu_relax();
पूर्ण
EXPORT_SYMBOL(__delay);

अंतरभूत व्योम __स्थिर_udelay(अचिन्हित दीर्घ xloops)
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
