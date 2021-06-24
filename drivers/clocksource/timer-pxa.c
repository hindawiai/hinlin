<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/mach-pxa/समय.c
 *
 * PXA घड़ीsource, घड़ीevents, and OST पूर्णांकerrupt handlers.
 * Copyright (c) 2007 by Bill Gatlअगरf <bgat@billgatlअगरf.com>.
 *
 * Derived from Nicolas Pitre's PXA समयr handler Copyright (c) 2001
 * by MontaVista Software, Inc.  (Nico, your code rocks!)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/clk.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/sched_घड़ी.h>

#समावेश <घड़ीsource/pxa.h>

#समावेश <यंत्र/भाग64.h>

#घोषणा OSMR0		0x00	/* OS Timer 0 Match Register */
#घोषणा OSMR1		0x04	/* OS Timer 1 Match Register */
#घोषणा OSMR2		0x08	/* OS Timer 2 Match Register */
#घोषणा OSMR3		0x0C	/* OS Timer 3 Match Register */

#घोषणा OSCR		0x10	/* OS Timer Counter Register */
#घोषणा OSSR		0x14	/* OS Timer Status Register */
#घोषणा OWER		0x18	/* OS Timer Watchकरोg Enable Register */
#घोषणा OIER		0x1C	/* OS Timer Interrupt Enable Register */

#घोषणा OSSR_M3		(1 << 3)	/* Match status channel 3 */
#घोषणा OSSR_M2		(1 << 2)	/* Match status channel 2 */
#घोषणा OSSR_M1		(1 << 1)	/* Match status channel 1 */
#घोषणा OSSR_M0		(1 << 0)	/* Match status channel 0 */

#घोषणा OIER_E0		(1 << 0)	/* Interrupt enable channel 0 */

/*
 * This is PXA's sched_घड़ी implementation. This has a resolution
 * of at least 308 ns and a maximum value of 208 days.
 *
 * The वापस value is guaranteed to be monotonic in that range as
 * दीर्घ as there is always less than 582 seconds between successive
 * calls to sched_घड़ी() which should always be the हाल in practice.
 */

#घोषणा समयr_पढ़ोl(reg) पढ़ोl_relaxed(समयr_base + (reg))
#घोषणा समयr_ग_लिखोl(val, reg) ग_लिखोl_relaxed((val), समयr_base + (reg))

अटल व्योम __iomem *समयr_base;

अटल u64 notrace pxa_पढ़ो_sched_घड़ी(व्योम)
अणु
	वापस समयr_पढ़ोl(OSCR);
पूर्ण


#घोषणा MIN_OSCR_DELTA 16

अटल irqवापस_t
pxa_ost0_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *c = dev_id;

	/* Disarm the compare/match, संकेत the event. */
	समयr_ग_लिखोl(समयr_पढ़ोl(OIER) & ~OIER_E0, OIER);
	समयr_ग_लिखोl(OSSR_M0, OSSR);
	c->event_handler(c);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक
pxa_osmr0_set_next_event(अचिन्हित दीर्घ delta, काष्ठा घड़ी_event_device *dev)
अणु
	अचिन्हित दीर्घ next, oscr;

	समयr_ग_लिखोl(समयr_पढ़ोl(OIER) | OIER_E0, OIER);
	next = समयr_पढ़ोl(OSCR) + delta;
	समयr_ग_लिखोl(next, OSMR0);
	oscr = समयr_पढ़ोl(OSCR);

	वापस (चिन्हित)(next - oscr) <= MIN_OSCR_DELTA ? -ETIME : 0;
पूर्ण

अटल पूर्णांक pxa_osmr0_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	/* initializing, released, or preparing क्रम suspend */
	समयr_ग_लिखोl(समयr_पढ़ोl(OIER) & ~OIER_E0, OIER);
	समयr_ग_लिखोl(OSSR_M0, OSSR);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल अचिन्हित दीर्घ osmr[4], oier, oscr;

अटल व्योम pxa_समयr_suspend(काष्ठा घड़ी_event_device *cedev)
अणु
	osmr[0] = समयr_पढ़ोl(OSMR0);
	osmr[1] = समयr_पढ़ोl(OSMR1);
	osmr[2] = समयr_पढ़ोl(OSMR2);
	osmr[3] = समयr_पढ़ोl(OSMR3);
	oier = समयr_पढ़ोl(OIER);
	oscr = समयr_पढ़ोl(OSCR);
पूर्ण

अटल व्योम pxa_समयr_resume(काष्ठा घड़ी_event_device *cedev)
अणु
	/*
	 * Ensure that we have at least MIN_OSCR_DELTA between match
	 * रेजिस्टर 0 and the OSCR, to guarantee that we will receive
	 * the one-shot समयr पूर्णांकerrupt.  We adjust OSMR0 in preference
	 * to OSCR to guarantee that OSCR is monotonically incrementing.
	 */
	अगर (osmr[0] - oscr < MIN_OSCR_DELTA)
		osmr[0] += MIN_OSCR_DELTA;

	समयr_ग_लिखोl(osmr[0], OSMR0);
	समयr_ग_लिखोl(osmr[1], OSMR1);
	समयr_ग_लिखोl(osmr[2], OSMR2);
	समयr_ग_लिखोl(osmr[3], OSMR3);
	समयr_ग_लिखोl(oier, OIER);
	समयr_ग_लिखोl(oscr, OSCR);
पूर्ण
#अन्यथा
#घोषणा pxa_समयr_suspend शून्य
#घोषणा pxa_समयr_resume शून्य
#पूर्ण_अगर

अटल काष्ठा घड़ी_event_device ckevt_pxa_osmr0 = अणु
	.name			= "osmr0",
	.features		= CLOCK_EVT_FEAT_ONESHOT,
	.rating			= 200,
	.set_next_event		= pxa_osmr0_set_next_event,
	.set_state_shutकरोwn	= pxa_osmr0_shutकरोwn,
	.set_state_oneshot	= pxa_osmr0_shutकरोwn,
	.suspend		= pxa_समयr_suspend,
	.resume			= pxa_समयr_resume,
पूर्ण;

अटल पूर्णांक __init pxa_समयr_common_init(पूर्णांक irq, अचिन्हित दीर्घ घड़ी_प्रकारick_rate)
अणु
	पूर्णांक ret;

	समयr_ग_लिखोl(0, OIER);
	समयr_ग_लिखोl(OSSR_M0 | OSSR_M1 | OSSR_M2 | OSSR_M3, OSSR);

	sched_घड़ी_रेजिस्टर(pxa_पढ़ो_sched_घड़ी, 32, घड़ी_प्रकारick_rate);

	ckevt_pxa_osmr0.cpumask = cpumask_of(0);

	ret = request_irq(irq, pxa_ost0_पूर्णांकerrupt, IRQF_TIMER | IRQF_IRQPOLL,
			  "ost0", &ckevt_pxa_osmr0);
	अगर (ret) अणु
		pr_err("Failed to setup irq\n");
		वापस ret;
	पूर्ण

	ret = घड़ीsource_mmio_init(समयr_base + OSCR, "oscr0", घड़ी_प्रकारick_rate, 200,
				    32, घड़ीsource_mmio_पढ़ोl_up);
	अगर (ret) अणु
		pr_err("Failed to init clocksource\n");
		वापस ret;
	पूर्ण

	घड़ीevents_config_and_रेजिस्टर(&ckevt_pxa_osmr0, घड़ी_प्रकारick_rate,
					MIN_OSCR_DELTA * 2, 0x7fffffff);

	वापस 0;
पूर्ण

अटल पूर्णांक __init pxa_समयr_dt_init(काष्ठा device_node *np)
अणु
	काष्ठा clk *clk;
	पूर्णांक irq, ret;

	/* समयr रेजिस्टरs are shared with watchकरोg समयr */
	समयr_base = of_iomap(np, 0);
	अगर (!समयr_base) अणु
		pr_err("%pOFn: unable to map resource\n", np);
		वापस -ENXIO;
	पूर्ण

	clk = of_clk_get(np, 0);
	अगर (IS_ERR(clk)) अणु
		pr_crit("%pOFn: unable to get clk\n", np);
		वापस PTR_ERR(clk);
	पूर्ण

	ret = clk_prepare_enable(clk);
	अगर (ret) अणु
		pr_crit("Failed to prepare clock\n");
		वापस ret;
	पूर्ण

	/* we are only पूर्णांकerested in OS-समयr0 irq */
	irq = irq_of_parse_and_map(np, 0);
	अगर (irq <= 0) अणु
		pr_crit("%pOFn: unable to parse OS-timer0 irq\n", np);
		वापस -EINVAL;
	पूर्ण

	वापस pxa_समयr_common_init(irq, clk_get_rate(clk));
पूर्ण
TIMER_OF_DECLARE(pxa_समयr, "marvell,pxa-timer", pxa_समयr_dt_init);

/*
 * Legacy समयr init क्रम non device-tree boards.
 */
व्योम __init pxa_समयr_nodt_init(पूर्णांक irq, व्योम __iomem *base)
अणु
	काष्ठा clk *clk;

	समयr_base = base;
	clk = clk_get(शून्य, "OSTIMER0");
	अगर (clk && !IS_ERR(clk)) अणु
		clk_prepare_enable(clk);
		pxa_समयr_common_init(irq, clk_get_rate(clk));
	पूर्ण अन्यथा अणु
		pr_crit("%s: unable to get clk\n", __func__);
	पूर्ण
पूर्ण
