<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microप्रणालीs co.,ltd.

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched_घड़ी.h>

#समावेश "timer-of.h"

#घोषणा CLKSRC_OFFSET	0x40

#घोषणा TIMER_STATUS	0x00
#घोषणा TIMER_VALUE	0x04
#घोषणा TIMER_CONTRL	0x10
#घोषणा TIMER_CONFIG	0x20
#घोषणा TIMER_DIV	0x24
#घोषणा TIMER_INI	0x28

#घोषणा GX6605S_STATUS_CLR	BIT(0)
#घोषणा GX6605S_CONTRL_RST	BIT(0)
#घोषणा GX6605S_CONTRL_START	BIT(1)
#घोषणा GX6605S_CONFIG_EN	BIT(0)
#घोषणा GX6605S_CONFIG_IRQ_EN	BIT(1)

अटल irqवापस_t gx6605s_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा घड़ी_event_device *ce = dev;
	व्योम __iomem *base = समयr_of_base(to_समयr_of(ce));

	ग_लिखोl_relaxed(GX6605S_STATUS_CLR, base + TIMER_STATUS);
	ग_लिखोl_relaxed(0, base + TIMER_INI);

	ce->event_handler(ce);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक gx6605s_समयr_set_oneshot(काष्ठा घड़ी_event_device *ce)
अणु
	व्योम __iomem *base = समयr_of_base(to_समयr_of(ce));

	/* reset and stop counter */
	ग_लिखोl_relaxed(GX6605S_CONTRL_RST, base + TIMER_CONTRL);

	/* enable with irq and start */
	ग_लिखोl_relaxed(GX6605S_CONFIG_EN | GX6605S_CONFIG_IRQ_EN,
		       base + TIMER_CONFIG);

	वापस 0;
पूर्ण

अटल पूर्णांक gx6605s_समयr_set_next_event(अचिन्हित दीर्घ delta,
					काष्ठा घड़ी_event_device *ce)
अणु
	व्योम __iomem *base = समयr_of_base(to_समयr_of(ce));

	/* use reset to छोड़ो समयr */
	ग_लिखोl_relaxed(GX6605S_CONTRL_RST, base + TIMER_CONTRL);

	/* config next समयout value */
	ग_लिखोl_relaxed(अच_दीर्घ_उच्च - delta, base + TIMER_INI);
	ग_लिखोl_relaxed(GX6605S_CONTRL_START, base + TIMER_CONTRL);

	वापस 0;
पूर्ण

अटल पूर्णांक gx6605s_समयr_shutकरोwn(काष्ठा घड़ी_event_device *ce)
अणु
	व्योम __iomem *base = समयr_of_base(to_समयr_of(ce));

	ग_लिखोl_relaxed(0, base + TIMER_CONTRL);
	ग_लिखोl_relaxed(0, base + TIMER_CONFIG);

	वापस 0;
पूर्ण

अटल काष्ठा समयr_of to = अणु
	.flags = TIMER_OF_IRQ | TIMER_OF_BASE | TIMER_OF_CLOCK,
	.clkevt = अणु
		.rating			= 300,
		.features		= CLOCK_EVT_FEAT_DYNIRQ |
					  CLOCK_EVT_FEAT_ONESHOT,
		.set_state_shutकरोwn	= gx6605s_समयr_shutकरोwn,
		.set_state_oneshot	= gx6605s_समयr_set_oneshot,
		.set_next_event		= gx6605s_समयr_set_next_event,
		.cpumask		= cpu_possible_mask,
	पूर्ण,
	.of_irq = अणु
		.handler		= gx6605s_समयr_पूर्णांकerrupt,
		.flags			= IRQF_TIMER | IRQF_IRQPOLL,
	पूर्ण,
पूर्ण;

अटल u64 notrace gx6605s_sched_घड़ी_पढ़ो(व्योम)
अणु
	व्योम __iomem *base;

	base = समयr_of_base(&to) + CLKSRC_OFFSET;

	वापस (u64)पढ़ोl_relaxed(base + TIMER_VALUE);
पूर्ण

अटल व्योम gx6605s_clkevt_init(व्योम __iomem *base)
अणु
	ग_लिखोl_relaxed(0, base + TIMER_DIV);
	ग_लिखोl_relaxed(0, base + TIMER_CONFIG);

	घड़ीevents_config_and_रेजिस्टर(&to.clkevt, समयr_of_rate(&to), 2,
					अच_दीर्घ_उच्च);
पूर्ण

अटल पूर्णांक gx6605s_clksrc_init(व्योम __iomem *base)
अणु
	ग_लिखोl_relaxed(0, base + TIMER_DIV);
	ग_लिखोl_relaxed(0, base + TIMER_INI);

	ग_लिखोl_relaxed(GX6605S_CONTRL_RST, base + TIMER_CONTRL);

	ग_लिखोl_relaxed(GX6605S_CONFIG_EN, base + TIMER_CONFIG);

	ग_लिखोl_relaxed(GX6605S_CONTRL_START, base + TIMER_CONTRL);

	sched_घड़ी_रेजिस्टर(gx6605s_sched_घड़ी_पढ़ो, 32, समयr_of_rate(&to));

	वापस घड़ीsource_mmio_init(base + TIMER_VALUE, "gx6605s",
			समयr_of_rate(&to), 200, 32, घड़ीsource_mmio_पढ़ोl_up);
पूर्ण

अटल पूर्णांक __init gx6605s_समयr_init(काष्ठा device_node *np)
अणु
	पूर्णांक ret;

	/*
	 * The समयr driver is क्रम nationalchip gx6605s SOC and there are two
	 * same समयr in gx6605s. We use one क्रम clkevt and another क्रम clksrc.
	 *
	 * The समयr is mmio map to access, so we need give mmio address in dts.
	 *
	 * It provides a 32bit countup समयr and पूर्णांकerrupt will be caused by
	 * count-overflow.
	 * So we need set-next-event by अच_दीर्घ_उच्च - delta in TIMER_INI reg.
	 *
	 * The counter at 0x0  offset is घड़ी event.
	 * The counter at 0x40 offset is घड़ी source.
	 * They are the same in hardware, just dअगरferent used by driver.
	 */
	ret = समयr_of_init(np, &to);
	अगर (ret)
		वापस ret;

	gx6605s_clkevt_init(समयr_of_base(&to));

	वापस gx6605s_clksrc_init(समयr_of_base(&to) + CLKSRC_OFFSET);
पूर्ण
TIMER_OF_DECLARE(csky_gx6605s_समयr, "csky,gx6605s-timer", gx6605s_समयr_init);
