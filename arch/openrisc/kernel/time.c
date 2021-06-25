<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OpenRISC समय.c
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * Modअगरications क्रम the OpenRISC architecture:
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/समय.स>
#समावेश <linux/समयx.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ftrace.h>

#समावेश <linux/घड़ीsource.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/cpuinfo.h>

/* Test the समयr ticks to count, used in sync routine */
अंतरभूत व्योम खोलोrisc_समयr_set(अचिन्हित दीर्घ count)
अणु
	mtspr(SPR_TTCR, count);
पूर्ण

/* Set the समयr to trigger in delta cycles */
अंतरभूत व्योम खोलोrisc_समयr_set_next(अचिन्हित दीर्घ delta)
अणु
	u32 c;

	/* Read 32-bit counter value, add delta, mask off the low 28 bits.
	 * We're guaranteed delta won't be bigger than 28 bits because the
	 * generic समयkeeping code ensures that क्रम us.
	 */
	c = mfspr(SPR_TTCR);
	c += delta;
	c &= SPR_TTMR_TP;

	/* Set counter and enable पूर्णांकerrupt.
	 * Keep समयr in continuous mode always.
	 */
	mtspr(SPR_TTMR, SPR_TTMR_CR | SPR_TTMR_IE | c);
पूर्ण

अटल पूर्णांक खोलोrisc_समयr_set_next_event(अचिन्हित दीर्घ delta,
					 काष्ठा घड़ी_event_device *dev)
अणु
	खोलोrisc_समयr_set_next(delta);
	वापस 0;
पूर्ण

/* This is the घड़ी event device based on the OR1K tick समयr.
 * As the समयr is being used as a continuous घड़ी-source (required क्रम HR
 * समयrs) we cannot enable the PERIODIC feature.  The tick समयr can run using
 * one-shot events, so no problem.
 */
DEFINE_PER_CPU(काष्ठा घड़ी_event_device, घड़ीevent_खोलोrisc_समयr);

व्योम खोलोrisc_घड़ीevent_init(व्योम)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	काष्ठा घड़ी_event_device *evt =
		&per_cpu(घड़ीevent_खोलोrisc_समयr, cpu);
	काष्ठा cpuinfo_or1k *cpuinfo = &cpuinfo_or1k[cpu];

	mtspr(SPR_TTMR, SPR_TTMR_CR);

#अगर_घोषित CONFIG_SMP
	evt->broadcast = tick_broadcast;
#पूर्ण_अगर
	evt->name = "openrisc_timer_clockevent",
	evt->features = CLOCK_EVT_FEAT_ONESHOT,
	evt->rating = 300,
	evt->set_next_event = खोलोrisc_समयr_set_next_event,

	evt->cpumask = cpumask_of(cpu);

	/* We only have 28 bits */
	घड़ीevents_config_and_रेजिस्टर(evt, cpuinfo->घड़ी_frequency,
					100, 0x0fffffff);

पूर्ण

अटल अंतरभूत व्योम समयr_ack(व्योम)
अणु
	/* Clear the IP bit and disable further पूर्णांकerrupts */
	/* This can be करोne very simply... we just need to keep the समयr
	   running, so just मुख्यtain the CR bits जबतक clearing the rest
	   of the रेजिस्टर
	 */
	mtspr(SPR_TTMR, SPR_TTMR_CR);
पूर्ण

/*
 * The समयr पूर्णांकerrupt is mostly handled in generic code nowadays... this
 * function just acknowledges the पूर्णांकerrupt and fires the event handler that
 * has been set on the घड़ीevent device by the generic समय management code.
 *
 * This function needs to be called by the समयr exception handler and that's
 * all the exception handler needs to करो.
 */

irqवापस_t __irq_entry समयr_पूर्णांकerrupt(काष्ठा pt_regs *regs)
अणु
	काष्ठा pt_regs *old_regs = set_irq_regs(regs);
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	काष्ठा घड़ी_event_device *evt =
		&per_cpu(घड़ीevent_खोलोrisc_समयr, cpu);

	समयr_ack();

	/*
	 * update_process_बार() expects us to have called irq_enter().
	 */
	irq_enter();
	evt->event_handler(evt);
	irq_निकास();

	set_irq_regs(old_regs);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * Clocksource: Based on OpenRISC समयr/counter
 *
 * This sets up the OpenRISC Tick Timer as a घड़ी source.  The tick समयr
 * is 32 bits wide and runs at the CPU घड़ी frequency.
 */
अटल u64 खोलोrisc_समयr_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	वापस (u64) mfspr(SPR_TTCR);
पूर्ण

अटल काष्ठा घड़ीsource खोलोrisc_समयr = अणु
	.name = "openrisc_timer",
	.rating = 200,
	.पढ़ो = खोलोrisc_समयr_पढ़ो,
	.mask = CLOCKSOURCE_MASK(32),
	.flags = CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

अटल पूर्णांक __init खोलोrisc_समयr_init(व्योम)
अणु
	काष्ठा cpuinfo_or1k *cpuinfo = &cpuinfo_or1k[smp_processor_id()];

	अगर (घड़ीsource_रेजिस्टर_hz(&खोलोrisc_समयr, cpuinfo->घड़ी_frequency))
		panic("failed to register clocksource");

	/* Enable the incrementer: 'continuous' mode with पूर्णांकerrupt disabled */
	mtspr(SPR_TTMR, SPR_TTMR_CR);

	वापस 0;
पूर्ण

व्योम __init समय_init(व्योम)
अणु
	u32 upr;

	upr = mfspr(SPR_UPR);
	अगर (!(upr & SPR_UPR_TTP))
		panic("Linux not supported on devices without tick timer");

	खोलोrisc_समयr_init();
	खोलोrisc_घड़ीevent_init();
पूर्ण
