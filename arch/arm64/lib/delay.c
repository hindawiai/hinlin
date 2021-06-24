<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Delay loops based on the OpenRISC implementation.
 *
 * Copyright (C) 2012 ARM Limited
 *
 * Author: Will Deacon <will.deacon@arm.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/समयx.h>

#समावेश <घड़ीsource/arm_arch_समयr.h>

#घोषणा USECS_TO_CYCLES(समय_usecs)			\
	xloops_to_cycles((समय_usecs) * 0x10C7UL)

अटल अंतरभूत अचिन्हित दीर्घ xloops_to_cycles(अचिन्हित दीर्घ xloops)
अणु
	वापस (xloops * loops_per_jअगरfy * HZ) >> 32;
पूर्ण

व्योम __delay(अचिन्हित दीर्घ cycles)
अणु
	cycles_t start = get_cycles();

	अगर (arch_समयr_evtstrm_available()) अणु
		स्थिर cycles_t समयr_evt_period =
			USECS_TO_CYCLES(ARCH_TIMER_EVT_STREAM_PERIOD_US);

		जबतक ((get_cycles() - start + समयr_evt_period) < cycles)
			wfe();
	पूर्ण

	जबतक ((get_cycles() - start) < cycles)
		cpu_relax();
पूर्ण
EXPORT_SYMBOL(__delay);

अंतरभूत व्योम __स्थिर_udelay(अचिन्हित दीर्घ xloops)
अणु
	__delay(xloops_to_cycles(xloops));
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
