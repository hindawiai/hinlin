<शैली गुरु>
/*
 * Allwinner A1X SoCs समयr handling.
 *
 * Copyright (C) 2012 Maxime Ripard
 *
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 *
 * Based on code from
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 * Benn Huang <benn@allwinnertech.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clk.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>

#समावेश "timer-of.h"

#घोषणा TIMER_IRQ_EN_REG	0x00
#घोषणा TIMER_IRQ_EN(val)		BIT(val)
#घोषणा TIMER_IRQ_ST_REG	0x04
#घोषणा TIMER_CTL_REG(val)	(0x10 * val + 0x10)
#घोषणा TIMER_CTL_ENABLE		BIT(0)
#घोषणा TIMER_CTL_RELOAD		BIT(1)
#घोषणा TIMER_CTL_CLK_SRC(val)		(((val) & 0x3) << 2)
#घोषणा TIMER_CTL_CLK_SRC_OSC24M		(1)
#घोषणा TIMER_CTL_CLK_PRES(val)		(((val) & 0x7) << 4)
#घोषणा TIMER_CTL_ONESHOT		BIT(7)
#घोषणा TIMER_INTVAL_REG(val)	(0x10 * (val) + 0x14)
#घोषणा TIMER_CNTVAL_REG(val)	(0x10 * (val) + 0x18)

#घोषणा TIMER_SYNC_TICKS	3

/*
 * When we disable a समयr, we need to रुको at least क्रम 2 cycles of
 * the समयr source घड़ी. We will use क्रम that the घड़ीsource समयr
 * that is alपढ़ोy setup and runs at the same frequency than the other
 * समयrs, and we never will be disabled.
 */
अटल व्योम sun4i_clkevt_sync(व्योम __iomem *base)
अणु
	u32 old = पढ़ोl(base + TIMER_CNTVAL_REG(1));

	जबतक ((old - पढ़ोl(base + TIMER_CNTVAL_REG(1))) < TIMER_SYNC_TICKS)
		cpu_relax();
पूर्ण

अटल व्योम sun4i_clkevt_समय_stop(व्योम __iomem *base, u8 समयr)
अणु
	u32 val = पढ़ोl(base + TIMER_CTL_REG(समयr));
	ग_लिखोl(val & ~TIMER_CTL_ENABLE, base + TIMER_CTL_REG(समयr));
	sun4i_clkevt_sync(base);
पूर्ण

अटल व्योम sun4i_clkevt_समय_setup(व्योम __iomem *base, u8 समयr,
				    अचिन्हित दीर्घ delay)
अणु
	ग_लिखोl(delay, base + TIMER_INTVAL_REG(समयr));
पूर्ण

अटल व्योम sun4i_clkevt_समय_start(व्योम __iomem *base, u8 समयr,
				    bool periodic)
अणु
	u32 val = पढ़ोl(base + TIMER_CTL_REG(समयr));

	अगर (periodic)
		val &= ~TIMER_CTL_ONESHOT;
	अन्यथा
		val |= TIMER_CTL_ONESHOT;

	ग_लिखोl(val | TIMER_CTL_ENABLE | TIMER_CTL_RELOAD,
	       base + TIMER_CTL_REG(समयr));
पूर्ण

अटल पूर्णांक sun4i_clkevt_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा समयr_of *to = to_समयr_of(evt);

	sun4i_clkevt_समय_stop(समयr_of_base(to), 0);

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_clkevt_set_oneshot(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा समयr_of *to = to_समयr_of(evt);

	sun4i_clkevt_समय_stop(समयr_of_base(to), 0);
	sun4i_clkevt_समय_start(समयr_of_base(to), 0, false);

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_clkevt_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा समयr_of *to = to_समयr_of(evt);

	sun4i_clkevt_समय_stop(समयr_of_base(to), 0);
	sun4i_clkevt_समय_setup(समयr_of_base(to), 0, समयr_of_period(to));
	sun4i_clkevt_समय_start(समयr_of_base(to), 0, true);

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_clkevt_next_event(अचिन्हित दीर्घ evt,
				   काष्ठा घड़ी_event_device *clkevt)
अणु
	काष्ठा समयr_of *to = to_समयr_of(clkevt);

	sun4i_clkevt_समय_stop(समयr_of_base(to), 0);
	sun4i_clkevt_समय_setup(समयr_of_base(to), 0, evt - TIMER_SYNC_TICKS);
	sun4i_clkevt_समय_start(समयr_of_base(to), 0, false);

	वापस 0;
पूर्ण

अटल व्योम sun4i_समयr_clear_पूर्णांकerrupt(व्योम __iomem *base)
अणु
	ग_लिखोl(TIMER_IRQ_EN(0), base + TIMER_IRQ_ST_REG);
पूर्ण

अटल irqवापस_t sun4i_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = (काष्ठा घड़ी_event_device *)dev_id;
	काष्ठा समयr_of *to = to_समयr_of(evt);

	sun4i_समयr_clear_पूर्णांकerrupt(समयr_of_base(to));
	evt->event_handler(evt);

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा समयr_of to = अणु
	.flags = TIMER_OF_IRQ | TIMER_OF_CLOCK | TIMER_OF_BASE,

	.clkevt = अणु
		.name = "sun4i_tick",
		.rating = 350,
		.features = CLOCK_EVT_FEAT_PERIODIC | CLOCK_EVT_FEAT_ONESHOT,
		.set_state_shutकरोwn = sun4i_clkevt_shutकरोwn,
		.set_state_periodic = sun4i_clkevt_set_periodic,
		.set_state_oneshot = sun4i_clkevt_set_oneshot,
		.tick_resume = sun4i_clkevt_shutकरोwn,
		.set_next_event = sun4i_clkevt_next_event,
		.cpumask = cpu_possible_mask,
	पूर्ण,

	.of_irq = अणु
		.handler = sun4i_समयr_पूर्णांकerrupt,
		.flags = IRQF_TIMER | IRQF_IRQPOLL,
	पूर्ण,
पूर्ण;

अटल u64 notrace sun4i_समयr_sched_पढ़ो(व्योम)
अणु
	वापस ~पढ़ोl(समयr_of_base(&to) + TIMER_CNTVAL_REG(1));
पूर्ण

अटल पूर्णांक __init sun4i_समयr_init(काष्ठा device_node *node)
अणु
	पूर्णांक ret;
	u32 val;

	ret = समयr_of_init(node, &to);
	अगर (ret)
		वापस ret;

	ग_लिखोl(~0, समयr_of_base(&to) + TIMER_INTVAL_REG(1));
	ग_लिखोl(TIMER_CTL_ENABLE | TIMER_CTL_RELOAD |
	       TIMER_CTL_CLK_SRC(TIMER_CTL_CLK_SRC_OSC24M),
	       समयr_of_base(&to) + TIMER_CTL_REG(1));

	/*
	 * sched_घड़ी_रेजिस्टर करोes not have priorities, and on sun6i and
	 * later there is a better sched_घड़ी रेजिस्टरed by arm_arch_समयr.c
	 */
	अगर (of_machine_is_compatible("allwinner,sun4i-a10") ||
	    of_machine_is_compatible("allwinner,sun5i-a13") ||
	    of_machine_is_compatible("allwinner,sun5i-a10s") ||
	    of_machine_is_compatible("allwinner,suniv-f1c100s"))
		sched_घड़ी_रेजिस्टर(sun4i_समयr_sched_पढ़ो, 32,
				     समयr_of_rate(&to));

	ret = घड़ीsource_mmio_init(समयr_of_base(&to) + TIMER_CNTVAL_REG(1),
				    node->name, समयr_of_rate(&to), 350, 32,
				    घड़ीsource_mmio_पढ़ोl_करोwn);
	अगर (ret) अणु
		pr_err("Failed to register clocksource\n");
		वापस ret;
	पूर्ण

	ग_लिखोl(TIMER_CTL_CLK_SRC(TIMER_CTL_CLK_SRC_OSC24M),
	       समयr_of_base(&to) + TIMER_CTL_REG(0));

	/* Make sure समयr is stopped beक्रमe playing with पूर्णांकerrupts */
	sun4i_clkevt_समय_stop(समयr_of_base(&to), 0);

	/* clear समयr0 पूर्णांकerrupt */
	sun4i_समयr_clear_पूर्णांकerrupt(समयr_of_base(&to));

	घड़ीevents_config_and_रेजिस्टर(&to.clkevt, समयr_of_rate(&to),
					TIMER_SYNC_TICKS, 0xffffffff);

	/* Enable समयr0 पूर्णांकerrupt */
	val = पढ़ोl(समयr_of_base(&to) + TIMER_IRQ_EN_REG);
	ग_लिखोl(val | TIMER_IRQ_EN(0), समयr_of_base(&to) + TIMER_IRQ_EN_REG);

	वापस ret;
पूर्ण
TIMER_OF_DECLARE(sun4i, "allwinner,sun4i-a10-timer",
		       sun4i_समयr_init);
TIMER_OF_DECLARE(sun8i_a23, "allwinner,sun8i-a23-timer",
		 sun4i_समयr_init);
TIMER_OF_DECLARE(sun8i_v3s, "allwinner,sun8i-v3s-timer",
		 sun4i_समयr_init);
TIMER_OF_DECLARE(suniv, "allwinner,suniv-f1c100s-timer",
		       sun4i_समयr_init);
