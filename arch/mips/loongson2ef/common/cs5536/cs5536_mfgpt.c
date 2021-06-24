<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * CS5536 General समयr functions
 *
 * Copyright (C) 2007 Lemote Inc. & Institute of Computing Technology
 * Author: Yanhua, yanh@lemote.com
 *
 * Copyright (C) 2009 Lemote Inc.
 * Author: Wu zhangjin, wuzhangjin@gmail.com
 *
 * Reference: AMD Geode(TM) CS5536 Companion Device Data Book
 */

#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/घड़ीchips.h>

#समावेश <यंत्र/समय.स>

#समावेश <cs5536/cs5536_mfgpt.h>

अटल DEFINE_RAW_SPINLOCK(mfgpt_lock);

अटल u32 mfgpt_base;

/*
 * Initialize the MFGPT समयr.
 *
 * This is also called after resume to bring the MFGPT पूर्णांकo operation again.
 */

/* disable counter */
व्योम disable_mfgpt0_counter(व्योम)
अणु
	outw(inw(MFGPT0_SETUP) & 0x7fff, MFGPT0_SETUP);
पूर्ण
EXPORT_SYMBOL(disable_mfgpt0_counter);

/* enable counter, comparator2 to event mode, 14.318MHz घड़ी */
व्योम enable_mfgpt0_counter(व्योम)
अणु
	outw(0xe310, MFGPT0_SETUP);
पूर्ण
EXPORT_SYMBOL(enable_mfgpt0_counter);

अटल पूर्णांक mfgpt_समयr_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	raw_spin_lock(&mfgpt_lock);

	outw(COMPARE, MFGPT0_CMP2);	/* set comparator2 */
	outw(0, MFGPT0_CNT);		/* set counter to 0 */
	enable_mfgpt0_counter();

	raw_spin_unlock(&mfgpt_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक mfgpt_समयr_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	अगर (घड़ीevent_state_periodic(evt) || घड़ीevent_state_oneshot(evt)) अणु
		raw_spin_lock(&mfgpt_lock);
		disable_mfgpt0_counter();
		raw_spin_unlock(&mfgpt_lock);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा घड़ी_event_device mfgpt_घड़ीevent = अणु
	.name = "mfgpt",
	.features = CLOCK_EVT_FEAT_PERIODIC,

	/* The oneshot mode have very high deviation, करोn't use it! */
	.set_state_shutकरोwn = mfgpt_समयr_shutकरोwn,
	.set_state_periodic = mfgpt_समयr_set_periodic,
	.irq = CS5536_MFGPT_INTR,
पूर्ण;

अटल irqवापस_t समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	u32 basehi;

	/*
	 * get MFGPT base address
	 *
	 * NOTE: करो not हटाओ me, it's need क्रम the value of mfgpt_base is
	 * variable
	 */
	_rdmsr(DIVIL_MSR_REG(DIVIL_LBAR_MFGPT), &basehi, &mfgpt_base);

	/* ack */
	outw(inw(MFGPT0_SETUP) | 0x4000, MFGPT0_SETUP);

	mfgpt_घड़ीevent.event_handler(&mfgpt_घड़ीevent);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Initialize the conversion factor and the min/max deltas of the घड़ी event
 * काष्ठाure and रेजिस्टर the घड़ी event source with the framework.
 */
व्योम __init setup_mfgpt0_समयr(व्योम)
अणु
	u32 basehi;
	काष्ठा घड़ी_event_device *cd = &mfgpt_घड़ीevent;
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	cd->cpumask = cpumask_of(cpu);
	घड़ीevent_set_घड़ी(cd, MFGPT_TICK_RATE);
	cd->max_delta_ns = घड़ीevent_delta2ns(0xffff, cd);
	cd->max_delta_ticks = 0xffff;
	cd->min_delta_ns = घड़ीevent_delta2ns(0xf, cd);
	cd->min_delta_ticks = 0xf;

	/* Enable MFGPT0 Comparator 2 Output to the Interrupt Mapper */
	_wrmsr(DIVIL_MSR_REG(MFGPT_IRQ), 0, 0x100);

	/* Enable Interrupt Gate 5 */
	_wrmsr(DIVIL_MSR_REG(PIC_ZSEL_LOW), 0, 0x50000);

	/* get MFGPT base address */
	_rdmsr(DIVIL_MSR_REG(DIVIL_LBAR_MFGPT), &basehi, &mfgpt_base);

	घड़ीevents_रेजिस्टर_device(cd);

	अगर (request_irq(CS5536_MFGPT_INTR, समयr_पूर्णांकerrupt,
			IRQF_NOBALANCING | IRQF_TIMER, "timer", शून्य))
		pr_err("Failed to register timer interrupt\n");
पूर्ण

/*
 * Since the MFGPT overflows every tick, its not very useful
 * to just पढ़ो by itself. So use jअगरfies to emulate a मुक्त
 * running counter:
 */
अटल u64 mfgpt_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक count;
	u32 jअगरs;
	अटल पूर्णांक old_count;
	अटल u32 old_jअगरs;

	raw_spin_lock_irqsave(&mfgpt_lock, flags);
	/*
	 * Although our caller may have the पढ़ो side of xसमय_lock,
	 * this is now a seqlock, and we are cheating in this routine
	 * by having side effects on state that we cannot unकरो अगर
	 * there is a collision on the seqlock and our caller has to
	 * retry.  (Namely, old_jअगरs and old_count.)  So we must treat
	 * jअगरfies as अस्थिर despite the lock.  We पढ़ो jअगरfies
	 * beक्रमe latching the समयr count to guarantee that although
	 * the jअगरfies value might be older than the count (that is,
	 * the counter may underflow between the last poपूर्णांक where
	 * jअगरfies was incremented and the poपूर्णांक where we latch the
	 * count), it cannot be newer.
	 */
	jअगरs = jअगरfies;
	/* पढ़ो the count */
	count = inw(MFGPT0_CNT);

	/*
	 * It's possible क्रम count to appear to go the wrong way क्रम this
	 * reason:
	 *
	 *  The समयr counter underflows, but we haven't handled the resulting
	 *  पूर्णांकerrupt and incremented jअगरfies yet.
	 *
	 * Previous attempts to handle these हालs पूर्णांकelligently were buggy, so
	 * we just करो the simple thing now.
	 */
	अगर (count < old_count && jअगरs == old_jअगरs)
		count = old_count;

	old_count = count;
	old_jअगरs = jअगरs;

	raw_spin_unlock_irqrestore(&mfgpt_lock, flags);

	वापस (u64) (jअगरs * COMPARE) + count;
पूर्ण

अटल काष्ठा घड़ीsource घड़ीsource_mfgpt = अणु
	.name = "mfgpt",
	.rating = 120, /* Functional क्रम real use, but not desired */
	.पढ़ो = mfgpt_पढ़ो,
	.mask = CLOCKSOURCE_MASK(32),
पूर्ण;

पूर्णांक __init init_mfgpt_घड़ीsource(व्योम)
अणु
	अगर (num_possible_cpus() > 1)	/* MFGPT करोes not scale! */
		वापस 0;

	वापस घड़ीsource_रेजिस्टर_hz(&घड़ीsource_mfgpt, MFGPT_TICK_RATE);
पूर्ण

arch_initcall(init_mfgpt_घड़ीsource);
