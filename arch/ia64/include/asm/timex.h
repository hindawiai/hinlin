<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_TIMEX_H
#घोषणा _ASM_IA64_TIMEX_H

/*
 * Copyright (C) 1998-2001, 2003 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 */
/*
 * 2001/01/18 davidm	Removed CLOCK_TICK_RATE.  It makes no sense on IA-64.
 *			Also हटाओd cacheflush_समय as it's entirely unused.
 */

#समावेश <यंत्र/पूर्णांकrinsics.h>
#समावेश <यंत्र/processor.h>

प्रकार अचिन्हित दीर्घ cycles_t;

बाह्य व्योम (*ia64_udelay)(अचिन्हित दीर्घ usecs);

/*
 * For perक्रमmance reasons, we करोn't want to define CLOCK_TICK_TRATE as
 * local_cpu_data->itc_rate.  Fortunately, we करोn't have to, either: according to George
 * Anzinger, 1/CLOCK_TICK_RATE is taken as the resolution of the समयr घड़ी.  The समय
 * calculation assumes that you will use enough of these so that your tick size <= 1/HZ.
 * If the calculation shows that your CLOCK_TICK_RATE can not supply exactly 1/HZ ticks,
 * the actual value is calculated and used to update the wall घड़ी each jअगरfie.  Setting
 * the CLOCK_TICK_RATE to x*HZ insures that the calculation will find no errors.  Hence we
 * pick a multiple of HZ which gives us a (totally भव) CLOCK_TICK_RATE of about
 * 100MHz.
 */
#घोषणा CLOCK_TICK_RATE		(HZ * 100000UL)

अटल अंतरभूत cycles_t
get_cycles (व्योम)
अणु
	cycles_t ret;

	ret = ia64_getreg(_IA64_REG_AR_ITC);
	वापस ret;
पूर्ण

बाह्य व्योम ia64_cpu_local_tick (व्योम);
बाह्य अचिन्हित दीर्घ दीर्घ ia64_native_sched_घड़ी (व्योम);

#पूर्ण_अगर /* _ASM_IA64_TIMEX_H */
