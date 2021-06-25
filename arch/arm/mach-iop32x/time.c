<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/arm/plat-iop/समय.c
 *
 * Timer code क्रम IOP32x and IOP33x based प्रणालीs
 *
 * Author: Deepak Saxena <dsaxena@mvista.com>
 *
 * Copyright 2002-2003 MontaVista Software Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/समय.स>
#समावेश <linux/init.h>
#समावेश <linux/समयx.h>
#समावेश <linux/पन.स>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/export.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <यंत्र/irq.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/mach/irq.h>
#समावेश <यंत्र/mach/समय.स>

#समावेश "hardware.h"
#समावेश "irqs.h"

/*
 * Minimum घड़ीsource/घड़ीevent समयr range in seconds
 */
#घोषणा IOP_MIN_RANGE 4

/*
 * IOP घड़ीsource (मुक्त-running समयr 1).
 */
अटल u64 notrace iop_घड़ीsource_पढ़ो(काष्ठा घड़ीsource *unused)
अणु
	वापस 0xffffffffu - पढ़ो_tcr1();
पूर्ण

अटल काष्ठा घड़ीsource iop_घड़ीsource = अणु
	.name 		= "iop_timer1",
	.rating		= 300,
	.पढ़ो		= iop_घड़ीsource_पढ़ो,
	.mask		= CLOCKSOURCE_MASK(32),
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

/*
 * IOP sched_घड़ी() implementation via its घड़ीsource.
 */
अटल u64 notrace iop_पढ़ो_sched_घड़ी(व्योम)
अणु
	वापस 0xffffffffu - पढ़ो_tcr1();
पूर्ण

/*
 * IOP घड़ीevents (पूर्णांकerrupting समयr 0).
 */
अटल पूर्णांक iop_set_next_event(अचिन्हित दीर्घ delta,
			      काष्ठा घड़ी_event_device *unused)
अणु
	u32 पंचांगr = IOP_TMR_PRIVILEGED | IOP_TMR_RATIO_1_1;

	BUG_ON(delta == 0);
	ग_लिखो_पंचांगr0(पंचांगr & ~(IOP_TMR_EN | IOP_TMR_RELOAD));
	ग_लिखो_tcr0(delta);
	ग_लिखो_पंचांगr0((पंचांगr & ~IOP_TMR_RELOAD) | IOP_TMR_EN);

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ ticks_per_jअगरfy;

अटल पूर्णांक iop_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	u32 पंचांगr = पढ़ो_पंचांगr0();

	ग_लिखो_पंचांगr0(पंचांगr & ~IOP_TMR_EN);
	ग_लिखो_tcr0(ticks_per_jअगरfy - 1);
	ग_लिखो_trr0(ticks_per_jअगरfy - 1);
	पंचांगr |= (IOP_TMR_RELOAD | IOP_TMR_EN);

	ग_लिखो_पंचांगr0(पंचांगr);
	वापस 0;
पूर्ण

अटल पूर्णांक iop_set_oneshot(काष्ठा घड़ी_event_device *evt)
अणु
	u32 पंचांगr = पढ़ो_पंचांगr0();

	/* ->set_next_event sets period and enables समयr */
	पंचांगr &= ~(IOP_TMR_RELOAD | IOP_TMR_EN);
	ग_लिखो_पंचांगr0(पंचांगr);
	वापस 0;
पूर्ण

अटल पूर्णांक iop_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	u32 पंचांगr = पढ़ो_पंचांगr0();

	पंचांगr &= ~IOP_TMR_EN;
	ग_लिखो_पंचांगr0(पंचांगr);
	वापस 0;
पूर्ण

अटल पूर्णांक iop_resume(काष्ठा घड़ी_event_device *evt)
अणु
	u32 पंचांगr = पढ़ो_पंचांगr0();

	पंचांगr |= IOP_TMR_EN;
	ग_लिखो_पंचांगr0(पंचांगr);
	वापस 0;
पूर्ण

अटल काष्ठा घड़ी_event_device iop_घड़ीevent = अणु
	.name			= "iop_timer0",
	.features		= CLOCK_EVT_FEAT_PERIODIC |
				  CLOCK_EVT_FEAT_ONESHOT,
	.rating			= 300,
	.set_next_event		= iop_set_next_event,
	.set_state_shutकरोwn	= iop_shutकरोwn,
	.set_state_periodic	= iop_set_periodic,
	.tick_resume		= iop_resume,
	.set_state_oneshot	= iop_set_oneshot,
पूर्ण;

अटल irqवापस_t
iop_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = dev_id;

	ग_लिखो_tisr(1);
	evt->event_handler(evt);
	वापस IRQ_HANDLED;
पूर्ण

अटल अचिन्हित दीर्घ iop_tick_rate;
अचिन्हित दीर्घ get_iop_tick_rate(व्योम)
अणु
	वापस iop_tick_rate;
पूर्ण
EXPORT_SYMBOL(get_iop_tick_rate);

व्योम __init iop_init_समय(अचिन्हित दीर्घ tick_rate)
अणु
	u32 समयr_ctl;
	पूर्णांक irq = IRQ_IOP32X_TIMER0;

	sched_घड़ी_रेजिस्टर(iop_पढ़ो_sched_घड़ी, 32, tick_rate);

	ticks_per_jअगरfy = DIV_ROUND_CLOSEST(tick_rate, HZ);
	iop_tick_rate = tick_rate;

	समयr_ctl = IOP_TMR_EN | IOP_TMR_PRIVILEGED |
			IOP_TMR_RELOAD | IOP_TMR_RATIO_1_1;

	/*
	 * Set up पूर्णांकerrupting घड़ीevent समयr 0.
	 */
	ग_लिखो_पंचांगr0(समयr_ctl & ~IOP_TMR_EN);
	ग_लिखो_tisr(1);
	अगर (request_irq(irq, iop_समयr_पूर्णांकerrupt, IRQF_TIMER | IRQF_IRQPOLL,
			"IOP Timer Tick", &iop_घड़ीevent))
		pr_err("Failed to request irq() %d (IOP Timer Tick)\n", irq);
	iop_घड़ीevent.cpumask = cpumask_of(0);
	घड़ीevents_config_and_रेजिस्टर(&iop_घड़ीevent, tick_rate,
					0xf, 0xfffffffe);

	/*
	 * Set up मुक्त-running घड़ीsource समयr 1.
	 */
	ग_लिखो_trr1(0xffffffff);
	ग_लिखो_tcr1(0xffffffff);
	ग_लिखो_पंचांगr1(समयr_ctl);
	घड़ीsource_रेजिस्टर_hz(&iop_घड़ीsource, tick_rate);
पूर्ण
