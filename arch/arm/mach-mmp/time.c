<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-mmp/समय.c
 *
 *   Support क्रम घड़ीsource and घड़ीevents
 *
 * Copyright (C) 2008 Marvell International Ltd.
 * All rights reserved.
 *
 *   2008-04-11: Jason Chagas <Jason.chagas@marvell.com>
 *   2008-10-08: Bin Yang <bin.yang@marvell.com>
 *
 * The समयrs module actually includes three समयrs, each समयr with up to
 * three match comparators. Timer #0 is used here in मुक्त-running mode as
 * the घड़ी source, and match comparator #1 used as घड़ी event device.
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/clk.h>

#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <यंत्र/mach/समय.स>

#समावेश "addr-map.h"
#समावेश "regs-timers.h"
#समावेश "regs-apbc.h"
#समावेश "irqs.h"
#समावेश <linux/soc/mmp/cputype.h>

#घोषणा TIMERS_VIRT_BASE	TIMERS1_VIRT_BASE

#घोषणा MAX_DELTA		(0xfffffffe)
#घोषणा MIN_DELTA		(16)

अटल व्योम __iomem *mmp_समयr_base = TIMERS_VIRT_BASE;

/*
 * FIXME: the समयr needs some delay to stablize the counter capture
 */
अटल अंतरभूत uपूर्णांक32_t समयr_पढ़ो(व्योम)
अणु
	पूर्णांक delay = 100;

	__raw_ग_लिखोl(1, mmp_समयr_base + TMR_CVWR(1));

	जबतक (delay--)
		cpu_relax();

	वापस __raw_पढ़ोl(mmp_समयr_base + TMR_CVWR(1));
पूर्ण

अटल u64 notrace mmp_पढ़ो_sched_घड़ी(व्योम)
अणु
	वापस समयr_पढ़ो();
पूर्ण

अटल irqवापस_t समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *c = dev_id;

	/*
	 * Clear pending पूर्णांकerrupt status.
	 */
	__raw_ग_लिखोl(0x01, mmp_समयr_base + TMR_ICR(0));

	/*
	 * Disable समयr 0.
	 */
	__raw_ग_लिखोl(0x02, mmp_समयr_base + TMR_CER);

	c->event_handler(c);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक समयr_set_next_event(अचिन्हित दीर्घ delta,
				काष्ठा घड़ी_event_device *dev)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	/*
	 * Disable समयr 0.
	 */
	__raw_ग_लिखोl(0x02, mmp_समयr_base + TMR_CER);

	/*
	 * Clear and enable समयr match 0 पूर्णांकerrupt.
	 */
	__raw_ग_लिखोl(0x01, mmp_समयr_base + TMR_ICR(0));
	__raw_ग_लिखोl(0x01, mmp_समयr_base + TMR_IER(0));

	/*
	 * Setup new घड़ीevent समयr value.
	 */
	__raw_ग_लिखोl(delta - 1, mmp_समयr_base + TMR_TN_MM(0, 0));

	/*
	 * Enable समयr 0.
	 */
	__raw_ग_लिखोl(0x03, mmp_समयr_base + TMR_CER);

	local_irq_restore(flags);

	वापस 0;
पूर्ण

अटल पूर्णांक समयr_set_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	/* disable the matching पूर्णांकerrupt */
	__raw_ग_लिखोl(0x00, mmp_समयr_base + TMR_IER(0));
	local_irq_restore(flags);

	वापस 0;
पूर्ण

अटल काष्ठा घड़ी_event_device ckevt = अणु
	.name			= "clockevent",
	.features		= CLOCK_EVT_FEAT_ONESHOT,
	.rating			= 200,
	.set_next_event		= समयr_set_next_event,
	.set_state_shutकरोwn	= समयr_set_shutकरोwn,
	.set_state_oneshot	= समयr_set_shutकरोwn,
पूर्ण;

अटल u64 clksrc_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	वापस समयr_पढ़ो();
पूर्ण

अटल काष्ठा घड़ीsource cksrc = अणु
	.name		= "clocksource",
	.rating		= 200,
	.पढ़ो		= clksrc_पढ़ो,
	.mask		= CLOCKSOURCE_MASK(32),
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

अटल व्योम __init समयr_config(व्योम)
अणु
	uपूर्णांक32_t ccr = __raw_पढ़ोl(mmp_समयr_base + TMR_CCR);

	__raw_ग_लिखोl(0x0, mmp_समयr_base + TMR_CER); /* disable */

	ccr &= (cpu_is_mmp2() || cpu_is_mmp3()) ?
		(TMR_CCR_CS_0(0) | TMR_CCR_CS_1(0)) :
		(TMR_CCR_CS_0(3) | TMR_CCR_CS_1(3));
	__raw_ग_लिखोl(ccr, mmp_समयr_base + TMR_CCR);

	/* set समयr 0 to periodic mode, and समयr 1 to मुक्त-running mode */
	__raw_ग_लिखोl(0x2, mmp_समयr_base + TMR_CMR);

	__raw_ग_लिखोl(0x1, mmp_समयr_base + TMR_PLCR(0)); /* periodic */
	__raw_ग_लिखोl(0x7, mmp_समयr_base + TMR_ICR(0));  /* clear status */
	__raw_ग_लिखोl(0x0, mmp_समयr_base + TMR_IER(0));

	__raw_ग_लिखोl(0x0, mmp_समयr_base + TMR_PLCR(1)); /* मुक्त-running */
	__raw_ग_लिखोl(0x7, mmp_समयr_base + TMR_ICR(1));  /* clear status */
	__raw_ग_लिखोl(0x0, mmp_समयr_base + TMR_IER(1));

	/* enable समयr 1 counter */
	__raw_ग_लिखोl(0x2, mmp_समयr_base + TMR_CER);
पूर्ण

व्योम __init mmp_समयr_init(पूर्णांक irq, अचिन्हित दीर्घ rate)
अणु
	समयr_config();

	sched_घड़ी_रेजिस्टर(mmp_पढ़ो_sched_घड़ी, 32, rate);

	ckevt.cpumask = cpumask_of(0);

	अगर (request_irq(irq, समयr_पूर्णांकerrupt, IRQF_TIMER | IRQF_IRQPOLL,
			"timer", &ckevt))
		pr_err("Failed to request irq %d (timer)\n", irq);

	घड़ीsource_रेजिस्टर_hz(&cksrc, rate);
	घड़ीevents_config_and_रेजिस्टर(&ckevt, rate, MIN_DELTA, MAX_DELTA);
पूर्ण

अटल पूर्णांक __init mmp_dt_init_समयr(काष्ठा device_node *np)
अणु
	काष्ठा clk *clk;
	पूर्णांक irq, ret;
	अचिन्हित दीर्घ rate;

	clk = of_clk_get(np, 0);
	अगर (!IS_ERR(clk)) अणु
		ret = clk_prepare_enable(clk);
		अगर (ret)
			वापस ret;
		rate = clk_get_rate(clk);
	पूर्ण अन्यथा अगर (cpu_is_pj4()) अणु
		rate = 6500000;
	पूर्ण अन्यथा अणु
		rate = 3250000;
	पूर्ण

	irq = irq_of_parse_and_map(np, 0);
	अगर (!irq)
		वापस -EINVAL;

	mmp_समयr_base = of_iomap(np, 0);
	अगर (!mmp_समयr_base)
		वापस -ENOMEM;

	mmp_समयr_init(irq, rate);
	वापस 0;
पूर्ण

TIMER_OF_DECLARE(mmp_समयr, "mrvl,mmp-timer", mmp_dt_init_समयr);
