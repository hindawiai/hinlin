<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Actions Semi Owl समयr
 *
 * Copyright 2012 Actions Semi Inc.
 * Author: Actions Semi, Inc.
 *
 * Copyright (c) 2017 SUSE Linux GmbH
 * Author: Andreas Fथअrber
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

#घोषणा OWL_Tx_CTL		0x0
#घोषणा OWL_Tx_CMP		0x4
#घोषणा OWL_Tx_VAL		0x8

#घोषणा OWL_Tx_CTL_PD		BIT(0)
#घोषणा OWL_Tx_CTL_INTEN	BIT(1)
#घोषणा OWL_Tx_CTL_EN		BIT(2)

अटल व्योम __iomem *owl_समयr_base;
अटल व्योम __iomem *owl_clksrc_base;
अटल व्योम __iomem *owl_clkevt_base;

अटल अंतरभूत व्योम owl_समयr_reset(व्योम __iomem *base)
अणु
	ग_लिखोl(0, base + OWL_Tx_CTL);
	ग_लिखोl(0, base + OWL_Tx_VAL);
	ग_लिखोl(0, base + OWL_Tx_CMP);
पूर्ण

अटल अंतरभूत व्योम owl_समयr_set_enabled(व्योम __iomem *base, bool enabled)
अणु
	u32 ctl = पढ़ोl(base + OWL_Tx_CTL);

	/* PD bit is cleared when set */
	ctl &= ~OWL_Tx_CTL_PD;

	अगर (enabled)
		ctl |= OWL_Tx_CTL_EN;
	अन्यथा
		ctl &= ~OWL_Tx_CTL_EN;

	ग_लिखोl(ctl, base + OWL_Tx_CTL);
पूर्ण

अटल u64 notrace owl_समयr_sched_पढ़ो(व्योम)
अणु
	वापस (u64)पढ़ोl(owl_clksrc_base + OWL_Tx_VAL);
पूर्ण

अटल पूर्णांक owl_समयr_set_state_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	owl_समयr_set_enabled(owl_clkevt_base, false);

	वापस 0;
पूर्ण

अटल पूर्णांक owl_समयr_set_state_oneshot(काष्ठा घड़ी_event_device *evt)
अणु
	owl_समयr_reset(owl_clkevt_base);

	वापस 0;
पूर्ण

अटल पूर्णांक owl_समयr_tick_resume(काष्ठा घड़ी_event_device *evt)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक owl_समयr_set_next_event(अचिन्हित दीर्घ evt,
				    काष्ठा घड़ी_event_device *ev)
अणु
	व्योम __iomem *base = owl_clkevt_base;

	owl_समयr_set_enabled(base, false);
	ग_लिखोl(OWL_Tx_CTL_INTEN, base + OWL_Tx_CTL);
	ग_लिखोl(0, base + OWL_Tx_VAL);
	ग_लिखोl(evt, base + OWL_Tx_CMP);
	owl_समयr_set_enabled(base, true);

	वापस 0;
पूर्ण

अटल काष्ठा घड़ी_event_device owl_घड़ीevent = अणु
	.name			= "owl_tick",
	.rating			= 200,
	.features		= CLOCK_EVT_FEAT_ONESHOT |
				  CLOCK_EVT_FEAT_DYNIRQ,
	.set_state_shutकरोwn	= owl_समयr_set_state_shutकरोwn,
	.set_state_oneshot	= owl_समयr_set_state_oneshot,
	.tick_resume		= owl_समयr_tick_resume,
	.set_next_event		= owl_समयr_set_next_event,
पूर्ण;

अटल irqवापस_t owl_समयr1_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = (काष्ठा घड़ी_event_device *)dev_id;

	ग_लिखोl(OWL_Tx_CTL_PD, owl_clkevt_base + OWL_Tx_CTL);

	evt->event_handler(evt);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init owl_समयr_init(काष्ठा device_node *node)
अणु
	काष्ठा clk *clk;
	अचिन्हित दीर्घ rate;
	पूर्णांक समयr1_irq, ret;

	owl_समयr_base = of_io_request_and_map(node, 0, "owl-timer");
	अगर (IS_ERR(owl_समयr_base)) अणु
		pr_err("Can't map timer registers\n");
		वापस PTR_ERR(owl_समयr_base);
	पूर्ण

	owl_clksrc_base = owl_समयr_base + 0x08;
	owl_clkevt_base = owl_समयr_base + 0x14;

	समयr1_irq = of_irq_get_byname(node, "timer1");
	अगर (समयr1_irq <= 0) अणु
		pr_err("Can't parse timer1 IRQ\n");
		वापस -EINVAL;
	पूर्ण

	clk = of_clk_get(node, 0);
	अगर (IS_ERR(clk)) अणु
		ret = PTR_ERR(clk);
		pr_err("Failed to get clock for clocksource (%d)\n", ret);
		वापस ret;
	पूर्ण

	rate = clk_get_rate(clk);

	owl_समयr_reset(owl_clksrc_base);
	owl_समयr_set_enabled(owl_clksrc_base, true);

	sched_घड़ी_रेजिस्टर(owl_समयr_sched_पढ़ो, 32, rate);
	ret = घड़ीsource_mmio_init(owl_clksrc_base + OWL_Tx_VAL, node->name,
				    rate, 200, 32, घड़ीsource_mmio_पढ़ोl_up);
	अगर (ret) अणु
		pr_err("Failed to register clocksource (%d)\n", ret);
		वापस ret;
	पूर्ण

	owl_समयr_reset(owl_clkevt_base);

	ret = request_irq(समयr1_irq, owl_समयr1_पूर्णांकerrupt, IRQF_TIMER,
			  "owl-timer", &owl_घड़ीevent);
	अगर (ret) अणु
		pr_err("failed to request irq %d\n", समयr1_irq);
		वापस ret;
	पूर्ण

	owl_घड़ीevent.cpumask = cpumask_of(0);
	owl_घड़ीevent.irq = समयr1_irq;

	घड़ीevents_config_and_रेजिस्टर(&owl_घड़ीevent, rate,
					0xf, 0xffffffff);

	वापस 0;
पूर्ण
TIMER_OF_DECLARE(owl_s500, "actions,s500-timer", owl_समयr_init);
TIMER_OF_DECLARE(owl_s700, "actions,s700-timer", owl_समयr_init);
TIMER_OF_DECLARE(owl_s900, "actions,s900-timer", owl_समयr_init);
