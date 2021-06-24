<शैली गुरु>
/*
 * arch/arm/plat-orion/समय.c
 *
 * Marvell Orion SoC समयr handling.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 *
 * Timer 0 is used as मुक्त-running घड़ीsource, जबतक समयr 1 is
 * used as घड़ी_event_device.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/समयr.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <plat/समय.स>
#समावेश <यंत्र/delay.h>

/*
 * MBus bridge block रेजिस्टरs.
 */
#घोषणा BRIDGE_CAUSE_OFF	0x0110
#घोषणा BRIDGE_MASK_OFF		0x0114
#घोषणा  BRIDGE_INT_TIMER0	 0x0002
#घोषणा  BRIDGE_INT_TIMER1	 0x0004


/*
 * Timer block रेजिस्टरs.
 */
#घोषणा TIMER_CTRL_OFF		0x0000
#घोषणा  TIMER0_EN		 0x0001
#घोषणा  TIMER0_RELOAD_EN	 0x0002
#घोषणा  TIMER1_EN		 0x0004
#घोषणा  TIMER1_RELOAD_EN	 0x0008
#घोषणा TIMER0_RELOAD_OFF	0x0010
#घोषणा TIMER0_VAL_OFF		0x0014
#घोषणा TIMER1_RELOAD_OFF	0x0018
#घोषणा TIMER1_VAL_OFF		0x001c


/*
 * SoC-specअगरic data.
 */
अटल व्योम __iomem *bridge_base;
अटल u32 bridge_समयr1_clr_mask;
अटल व्योम __iomem *समयr_base;


/*
 * Number of समयr ticks per jअगरfy.
 */
अटल u32 ticks_per_jअगरfy;


/*
 * Orion's sched_घड़ी implementation. It has a resolution of
 * at least 7.5ns (133MHz TCLK).
 */

अटल u64 notrace orion_पढ़ो_sched_घड़ी(व्योम)
अणु
	वापस ~पढ़ोl(समयr_base + TIMER0_VAL_OFF);
पूर्ण

/*
 * Clockevent handling.
 */
अटल पूर्णांक
orion_clkevt_next_event(अचिन्हित दीर्घ delta, काष्ठा घड़ी_event_device *dev)
अणु
	अचिन्हित दीर्घ flags;
	u32 u;

	अगर (delta == 0)
		वापस -ETIME;

	local_irq_save(flags);

	/*
	 * Clear and enable घड़ीevent समयr पूर्णांकerrupt.
	 */
	ग_लिखोl(bridge_समयr1_clr_mask, bridge_base + BRIDGE_CAUSE_OFF);

	u = पढ़ोl(bridge_base + BRIDGE_MASK_OFF);
	u |= BRIDGE_INT_TIMER1;
	ग_लिखोl(u, bridge_base + BRIDGE_MASK_OFF);

	/*
	 * Setup new घड़ीevent समयr value.
	 */
	ग_लिखोl(delta, समयr_base + TIMER1_VAL_OFF);

	/*
	 * Enable the समयr.
	 */
	u = पढ़ोl(समयr_base + TIMER_CTRL_OFF);
	u = (u & ~TIMER1_RELOAD_EN) | TIMER1_EN;
	ग_लिखोl(u, समयr_base + TIMER_CTRL_OFF);

	local_irq_restore(flags);

	वापस 0;
पूर्ण

अटल पूर्णांक orion_clkevt_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	अचिन्हित दीर्घ flags;
	u32 u;

	local_irq_save(flags);

	/* Disable समयr */
	u = पढ़ोl(समयr_base + TIMER_CTRL_OFF);
	ग_लिखोl(u & ~TIMER1_EN, समयr_base + TIMER_CTRL_OFF);

	/* Disable समयr पूर्णांकerrupt */
	u = पढ़ोl(bridge_base + BRIDGE_MASK_OFF);
	ग_लिखोl(u & ~BRIDGE_INT_TIMER1, bridge_base + BRIDGE_MASK_OFF);

	/* ACK pending समयr पूर्णांकerrupt */
	ग_लिखोl(bridge_समयr1_clr_mask, bridge_base + BRIDGE_CAUSE_OFF);

	local_irq_restore(flags);

	वापस 0;
पूर्ण

अटल पूर्णांक orion_clkevt_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	अचिन्हित दीर्घ flags;
	u32 u;

	local_irq_save(flags);

	/* Setup समयr to fire at 1/HZ पूर्णांकervals */
	ग_लिखोl(ticks_per_jअगरfy - 1, समयr_base + TIMER1_RELOAD_OFF);
	ग_लिखोl(ticks_per_jअगरfy - 1, समयr_base + TIMER1_VAL_OFF);

	/* Enable समयr पूर्णांकerrupt */
	u = पढ़ोl(bridge_base + BRIDGE_MASK_OFF);
	ग_लिखोl(u | BRIDGE_INT_TIMER1, bridge_base + BRIDGE_MASK_OFF);

	/* Enable समयr */
	u = पढ़ोl(समयr_base + TIMER_CTRL_OFF);
	ग_लिखोl(u | TIMER1_EN | TIMER1_RELOAD_EN, समयr_base + TIMER_CTRL_OFF);

	local_irq_restore(flags);

	वापस 0;
पूर्ण

अटल काष्ठा घड़ी_event_device orion_clkevt = अणु
	.name			= "orion_tick",
	.features		= CLOCK_EVT_FEAT_ONESHOT |
				  CLOCK_EVT_FEAT_PERIODIC,
	.rating			= 300,
	.set_next_event		= orion_clkevt_next_event,
	.set_state_shutकरोwn	= orion_clkevt_shutकरोwn,
	.set_state_periodic	= orion_clkevt_set_periodic,
	.set_state_oneshot	= orion_clkevt_shutकरोwn,
	.tick_resume		= orion_clkevt_shutकरोwn,
पूर्ण;

अटल irqवापस_t orion_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	/*
	 * ACK समयr पूर्णांकerrupt and call event handler.
	 */
	ग_लिखोl(bridge_समयr1_clr_mask, bridge_base + BRIDGE_CAUSE_OFF);
	orion_clkevt.event_handler(&orion_clkevt);

	वापस IRQ_HANDLED;
पूर्ण

व्योम __init
orion_समय_set_base(व्योम __iomem *_समयr_base)
अणु
	समयr_base = _समयr_base;
पूर्ण

अटल अचिन्हित दीर्घ orion_delay_समयr_पढ़ो(व्योम)
अणु
	वापस ~पढ़ोl(समयr_base + TIMER0_VAL_OFF);
पूर्ण

अटल काष्ठा delay_समयr orion_delay_समयr = अणु
	.पढ़ो_current_समयr = orion_delay_समयr_पढ़ो,
पूर्ण;

व्योम __init
orion_समय_init(व्योम __iomem *_bridge_base, u32 _bridge_समयr1_clr_mask,
		अचिन्हित पूर्णांक irq, अचिन्हित पूर्णांक tclk)
अणु
	u32 u;

	/*
	 * Set SoC-specअगरic data.
	 */
	bridge_base = _bridge_base;
	bridge_समयr1_clr_mask = _bridge_समयr1_clr_mask;

	ticks_per_jअगरfy = (tclk + HZ/2) / HZ;

	orion_delay_समयr.freq = tclk;
	रेजिस्टर_current_समयr_delay(&orion_delay_समयr);

	/*
	 * Set scale and समयr क्रम sched_घड़ी.
	 */
	sched_घड़ी_रेजिस्टर(orion_पढ़ो_sched_घड़ी, 32, tclk);

	/*
	 * Setup मुक्त-running घड़ीsource समयr (पूर्णांकerrupts
	 * disabled).
	 */
	ग_लिखोl(0xffffffff, समयr_base + TIMER0_VAL_OFF);
	ग_लिखोl(0xffffffff, समयr_base + TIMER0_RELOAD_OFF);
	u = पढ़ोl(bridge_base + BRIDGE_MASK_OFF);
	ग_लिखोl(u & ~BRIDGE_INT_TIMER0, bridge_base + BRIDGE_MASK_OFF);
	u = पढ़ोl(समयr_base + TIMER_CTRL_OFF);
	ग_लिखोl(u | TIMER0_EN | TIMER0_RELOAD_EN, समयr_base + TIMER_CTRL_OFF);
	घड़ीsource_mmio_init(समयr_base + TIMER0_VAL_OFF, "orion_clocksource",
		tclk, 300, 32, घड़ीsource_mmio_पढ़ोl_करोwn);

	/*
	 * Setup घड़ीevent समयr (पूर्णांकerrupt-driven).
	 */
	अगर (request_irq(irq, orion_समयr_पूर्णांकerrupt, IRQF_TIMER, "orion_tick",
			शून्य))
		pr_err("Failed to request irq %u (orion_tick)\n", irq);
	orion_clkevt.cpumask = cpumask_of(0);
	घड़ीevents_config_and_रेजिस्टर(&orion_clkevt, tclk, 1, 0xfffffffe);
पूर्ण
