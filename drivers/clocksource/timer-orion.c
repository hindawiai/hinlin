<शैली गुरु>
/*
 * Marvell Orion SoC समयr handling.
 *
 * Sebastian Hesselbarth <sebastian.hesselbarth@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 *
 * Timer 0 is used as मुक्त-running घड़ीsource, जबतक समयr 1 is
 * used as घड़ी_event_device.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sched_घड़ी.h>

#घोषणा TIMER_CTRL		0x00
#घोषणा  TIMER0_EN		BIT(0)
#घोषणा  TIMER0_RELOAD_EN	BIT(1)
#घोषणा  TIMER1_EN		BIT(2)
#घोषणा  TIMER1_RELOAD_EN	BIT(3)
#घोषणा TIMER0_RELOAD		0x10
#घोषणा TIMER0_VAL		0x14
#घोषणा TIMER1_RELOAD		0x18
#घोषणा TIMER1_VAL		0x1c

#घोषणा ORION_ONESHOT_MIN	1
#घोषणा ORION_ONESHOT_MAX	0xfffffffe

अटल व्योम __iomem *समयr_base;

अटल अचिन्हित दीर्घ notrace orion_पढ़ो_समयr(व्योम)
अणु
	वापस ~पढ़ोl(समयr_base + TIMER0_VAL);
पूर्ण

अटल काष्ठा delay_समयr orion_delay_समयr = अणु
	.पढ़ो_current_समयr = orion_पढ़ो_समयr,
पूर्ण;

अटल व्योम orion_delay_समयr_init(अचिन्हित दीर्घ rate)
अणु
	orion_delay_समयr.freq = rate;
	रेजिस्टर_current_समयr_delay(&orion_delay_समयr);
पूर्ण

/*
 * Free-running घड़ीsource handling.
 */
अटल u64 notrace orion_पढ़ो_sched_घड़ी(व्योम)
अणु
	वापस ~पढ़ोl(समयr_base + TIMER0_VAL);
पूर्ण

/*
 * Clockevent handling.
 */
अटल u32 ticks_per_jअगरfy;

अटल पूर्णांक orion_clkevt_next_event(अचिन्हित दीर्घ delta,
				   काष्ठा घड़ी_event_device *dev)
अणु
	/* setup and enable one-shot समयr */
	ग_लिखोl(delta, समयr_base + TIMER1_VAL);
	atomic_io_modअगरy(समयr_base + TIMER_CTRL,
		TIMER1_RELOAD_EN | TIMER1_EN, TIMER1_EN);

	वापस 0;
पूर्ण

अटल पूर्णांक orion_clkevt_shutकरोwn(काष्ठा घड़ी_event_device *dev)
अणु
	/* disable समयr */
	atomic_io_modअगरy(समयr_base + TIMER_CTRL,
			 TIMER1_RELOAD_EN | TIMER1_EN, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक orion_clkevt_set_periodic(काष्ठा घड़ी_event_device *dev)
अणु
	/* setup and enable periodic समयr at 1/HZ पूर्णांकervals */
	ग_लिखोl(ticks_per_jअगरfy - 1, समयr_base + TIMER1_RELOAD);
	ग_लिखोl(ticks_per_jअगरfy - 1, समयr_base + TIMER1_VAL);
	atomic_io_modअगरy(समयr_base + TIMER_CTRL,
			 TIMER1_RELOAD_EN | TIMER1_EN,
			 TIMER1_RELOAD_EN | TIMER1_EN);
	वापस 0;
पूर्ण

अटल काष्ठा घड़ी_event_device orion_clkevt = अणु
	.name			= "orion_event",
	.features		= CLOCK_EVT_FEAT_ONESHOT |
				  CLOCK_EVT_FEAT_PERIODIC,
	.shअगरt			= 32,
	.rating			= 300,
	.set_next_event		= orion_clkevt_next_event,
	.set_state_shutकरोwn	= orion_clkevt_shutकरोwn,
	.set_state_periodic	= orion_clkevt_set_periodic,
	.set_state_oneshot	= orion_clkevt_shutकरोwn,
	.tick_resume		= orion_clkevt_shutकरोwn,
पूर्ण;

अटल irqवापस_t orion_clkevt_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	orion_clkevt.event_handler(&orion_clkevt);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init orion_समयr_init(काष्ठा device_node *np)
अणु
	अचिन्हित दीर्घ rate;
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
		pr_err("%pOFn: unable to get clk\n", np);
		वापस PTR_ERR(clk);
	पूर्ण

	ret = clk_prepare_enable(clk);
	अगर (ret) अणु
		pr_err("Failed to prepare clock\n");
		वापस ret;
	पूर्ण

	/* we are only पूर्णांकerested in समयr1 irq */
	irq = irq_of_parse_and_map(np, 1);
	अगर (irq <= 0) अणु
		pr_err("%pOFn: unable to parse timer1 irq\n", np);
		ret = -EINVAL;
		जाओ out_unprep_clk;
	पूर्ण

	rate = clk_get_rate(clk);

	/* setup समयr0 as मुक्त-running घड़ीsource */
	ग_लिखोl(~0, समयr_base + TIMER0_VAL);
	ग_लिखोl(~0, समयr_base + TIMER0_RELOAD);
	atomic_io_modअगरy(समयr_base + TIMER_CTRL,
		TIMER0_RELOAD_EN | TIMER0_EN,
		TIMER0_RELOAD_EN | TIMER0_EN);

	ret = घड़ीsource_mmio_init(समयr_base + TIMER0_VAL,
				    "orion_clocksource", rate, 300, 32,
				    घड़ीsource_mmio_पढ़ोl_करोwn);
	अगर (ret) अणु
		pr_err("Failed to initialize mmio timer\n");
		जाओ out_unprep_clk;
	पूर्ण

	sched_घड़ी_रेजिस्टर(orion_पढ़ो_sched_घड़ी, 32, rate);

	/* setup समयr1 as घड़ीevent समयr */
	ret = request_irq(irq, orion_clkevt_irq_handler, IRQF_TIMER,
			  "orion_event", शून्य);
	अगर (ret) अणु
		pr_err("%pOFn: unable to setup irq\n", np);
		जाओ out_unprep_clk;
	पूर्ण

	ticks_per_jअगरfy = (clk_get_rate(clk) + HZ/2) / HZ;
	orion_clkevt.cpumask = cpumask_of(0);
	orion_clkevt.irq = irq;
	घड़ीevents_config_and_रेजिस्टर(&orion_clkevt, rate,
					ORION_ONESHOT_MIN, ORION_ONESHOT_MAX);


	orion_delay_समयr_init(rate);

	वापस 0;

out_unprep_clk:
	clk_disable_unprepare(clk);
	वापस ret;
पूर्ण
TIMER_OF_DECLARE(orion_समयr, "marvell,orion-timer", orion_समयr_init);
