<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/arm/mach-footbridge/dc21285-समयr.c
 *
 *  Copyright (C) 1998 Russell King.
 *  Copyright (C) 1998 Phil Blundell
 */
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/sched_घड़ी.h>

#समावेश <यंत्र/irq.h>

#समावेश <यंत्र/hardware/dec21285.h>
#समावेश <यंत्र/mach/समय.स>
#समावेश <यंत्र/प्रणाली_info.h>

#समावेश "common.h"

अटल u64 cksrc_dc21285_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	वापस cs->mask - *CSR_TIMER2_VALUE;
पूर्ण

अटल पूर्णांक cksrc_dc21285_enable(काष्ठा घड़ीsource *cs)
अणु
	*CSR_TIMER2_LOAD = cs->mask;
	*CSR_TIMER2_CLR = 0;
	*CSR_TIMER2_CNTL = TIMER_CNTL_ENABLE | TIMER_CNTL_DIV16;
	वापस 0;
पूर्ण

अटल व्योम cksrc_dc21285_disable(काष्ठा घड़ीsource *cs)
अणु
	*CSR_TIMER2_CNTL = 0;
पूर्ण

अटल काष्ठा घड़ीsource cksrc_dc21285 = अणु
	.name		= "dc21285_timer2",
	.rating		= 200,
	.पढ़ो		= cksrc_dc21285_पढ़ो,
	.enable		= cksrc_dc21285_enable,
	.disable	= cksrc_dc21285_disable,
	.mask		= CLOCKSOURCE_MASK(24),
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

अटल पूर्णांक ckevt_dc21285_set_next_event(अचिन्हित दीर्घ delta,
	काष्ठा घड़ी_event_device *c)
अणु
	*CSR_TIMER1_CLR = 0;
	*CSR_TIMER1_LOAD = delta;
	*CSR_TIMER1_CNTL = TIMER_CNTL_ENABLE | TIMER_CNTL_DIV16;

	वापस 0;
पूर्ण

अटल पूर्णांक ckevt_dc21285_shutकरोwn(काष्ठा घड़ी_event_device *c)
अणु
	*CSR_TIMER1_CNTL = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक ckevt_dc21285_set_periodic(काष्ठा घड़ी_event_device *c)
अणु
	*CSR_TIMER1_CLR = 0;
	*CSR_TIMER1_LOAD = (mem_fclk_21285 + 8 * HZ) / (16 * HZ);
	*CSR_TIMER1_CNTL = TIMER_CNTL_ENABLE | TIMER_CNTL_AUTORELOAD |
			   TIMER_CNTL_DIV16;
	वापस 0;
पूर्ण

अटल काष्ठा घड़ी_event_device ckevt_dc21285 = अणु
	.name			= "dc21285_timer1",
	.features		= CLOCK_EVT_FEAT_PERIODIC |
				  CLOCK_EVT_FEAT_ONESHOT,
	.rating			= 200,
	.irq			= IRQ_TIMER1,
	.set_next_event		= ckevt_dc21285_set_next_event,
	.set_state_shutकरोwn	= ckevt_dc21285_shutकरोwn,
	.set_state_periodic	= ckevt_dc21285_set_periodic,
	.set_state_oneshot	= ckevt_dc21285_shutकरोwn,
	.tick_resume		= ckevt_dc21285_set_periodic,
पूर्ण;

अटल irqवापस_t समयr1_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *ce = dev_id;

	*CSR_TIMER1_CLR = 0;

	/* Stop the समयr अगर in one-shot mode */
	अगर (घड़ीevent_state_oneshot(ce))
		*CSR_TIMER1_CNTL = 0;

	ce->event_handler(ce);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Set up समयr पूर्णांकerrupt.
 */
व्योम __init footbridge_समयr_init(व्योम)
अणु
	काष्ठा घड़ी_event_device *ce = &ckevt_dc21285;
	अचिन्हित rate = DIV_ROUND_CLOSEST(mem_fclk_21285, 16);

	घड़ीsource_रेजिस्टर_hz(&cksrc_dc21285, rate);

	अगर (request_irq(ce->irq, समयr1_पूर्णांकerrupt, IRQF_TIMER | IRQF_IRQPOLL,
			"dc21285_timer1", &ckevt_dc21285))
		pr_err("Failed to request irq %d (dc21285_timer1)", ce->irq);

	ce->cpumask = cpumask_of(smp_processor_id());
	घड़ीevents_config_and_रेजिस्टर(ce, rate, 0x4, 0xffffff);
पूर्ण

अटल u64 notrace footbridge_पढ़ो_sched_घड़ी(व्योम)
अणु
	वापस ~*CSR_TIMER3_VALUE;
पूर्ण

व्योम __init footbridge_sched_घड़ी(व्योम)
अणु
	अचिन्हित rate = DIV_ROUND_CLOSEST(mem_fclk_21285, 16);

	*CSR_TIMER3_LOAD = 0;
	*CSR_TIMER3_CLR = 0;
	*CSR_TIMER3_CNTL = TIMER_CNTL_ENABLE | TIMER_CNTL_DIV16;

	sched_घड़ी_रेजिस्टर(footbridge_पढ़ो_sched_घड़ी, 24, rate);
पूर्ण
