<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	Precise Delay Loops क्रम parisc
 *
 *	based on code by:
 *	Copyright (C) 1993 Linus Torvalds
 *	Copyright (C) 1997 Martin Mares <mj@atrey.karlin.mff.cuni.cz>
 *	Copyright (C) 2008 Jiri Hladky <hladky _करोt_ jiri _at_ gmail _करोt_ com>
 *
 *	parisc implementation:
 *	Copyright (C) 2013 Helge Deller <deller@gmx.de>
 */


#समावेश <linux/module.h>
#समावेश <linux/preempt.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/special_insns.h>    /* क्रम mfctl() */
#समावेश <यंत्र/processor.h> /* क्रम boot_cpu_data */

/* CR16 based delay: */
अटल व्योम __cr16_delay(अचिन्हित दीर्घ __loops)
अणु
	/*
	 * Note: Due to अचिन्हित math, cr16 rollovers shouldn't be
	 * a problem here. However, on 32 bit, we need to make sure
	 * we करोn't pass in too big a value. The current शेष
	 * value of MAX_UDELAY_MS should help prevent this.
	 */
	u32 bघड़ी, now, loops = __loops;
	पूर्णांक cpu;

	preempt_disable();
	cpu = smp_processor_id();
	bघड़ी = mfctl(16);
	क्रम (;;) अणु
		now = mfctl(16);
		अगर ((now - bघड़ी) >= loops)
			अवरोध;

		/* Allow RT tasks to run */
		preempt_enable();
		यंत्र अस्थिर("	nop\n");
		barrier();
		preempt_disable();

		/*
		 * It is possible that we moved to another CPU, and
		 * since CR16's are per-cpu we need to calculate
		 * that. The delay must guarantee that we रुको "at
		 * least" the amount of समय. Being moved to another
		 * CPU could make the रुको दीर्घer but we just need to
		 * make sure we रुकोed दीर्घ enough. Rebalance the
		 * counter क्रम this CPU.
		 */
		अगर (unlikely(cpu != smp_processor_id())) अणु
			loops -= (now - bघड़ी);
			cpu = smp_processor_id();
			bघड़ी = mfctl(16);
		पूर्ण
	पूर्ण
	preempt_enable();
पूर्ण


व्योम __udelay(अचिन्हित दीर्घ usecs)
अणु
	__cr16_delay(usecs * ((अचिन्हित दीर्घ)boot_cpu_data.cpu_hz / 1000000UL));
पूर्ण
EXPORT_SYMBOL(__udelay);
