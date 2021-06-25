<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Cirrus Logic CLPS711X घड़ीsource driver
 *
 *  Copyright (C) 2014 Alexander Shiyan <shc_work@mail.ru>
 */

#समावेश <linux/clk.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/slab.h>

क्रमागत अणु
	CLPS711X_CLKSRC_CLOCKSOURCE,
	CLPS711X_CLKSRC_CLOCKEVENT,
पूर्ण;

अटल व्योम __iomem *tcd;

अटल u64 notrace clps711x_sched_घड़ी_पढ़ो(व्योम)
अणु
	वापस ~पढ़ोw(tcd);
पूर्ण

अटल व्योम __init clps711x_clksrc_init(काष्ठा clk *घड़ी, व्योम __iomem *base)
अणु
	अचिन्हित दीर्घ rate = clk_get_rate(घड़ी);

	tcd = base;

	घड़ीsource_mmio_init(tcd, "clps711x-clocksource", rate, 300, 16,
			      घड़ीsource_mmio_पढ़ोw_करोwn);

	sched_घड़ी_रेजिस्टर(clps711x_sched_घड़ी_पढ़ो, 16, rate);
पूर्ण

अटल irqवापस_t clps711x_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = dev_id;

	evt->event_handler(evt);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init _clps711x_clkevt_init(काष्ठा clk *घड़ी, व्योम __iomem *base,
					अचिन्हित पूर्णांक irq)
अणु
	काष्ठा घड़ी_event_device *clkevt;
	अचिन्हित दीर्घ rate;

	clkevt = kzalloc(माप(*clkevt), GFP_KERNEL);
	अगर (!clkevt)
		वापस -ENOMEM;

	rate = clk_get_rate(घड़ी);

	/* Set Timer prescaler */
	ग_लिखोw(DIV_ROUND_CLOSEST(rate, HZ), base);

	clkevt->name = "clps711x-clockevent";
	clkevt->rating = 300;
	clkevt->features = CLOCK_EVT_FEAT_PERIODIC | CLOCK_EVT_FEAT_C3STOP;
	clkevt->cpumask = cpumask_of(0);
	घड़ीevents_config_and_रेजिस्टर(clkevt, HZ, 0, 0);

	वापस request_irq(irq, clps711x_समयr_पूर्णांकerrupt, IRQF_TIMER,
			   "clps711x-timer", clkevt);
पूर्ण

अटल पूर्णांक __init clps711x_समयr_init(काष्ठा device_node *np)
अणु
	अचिन्हित पूर्णांक irq = irq_of_parse_and_map(np, 0);
	काष्ठा clk *घड़ी = of_clk_get(np, 0);
	व्योम __iomem *base = of_iomap(np, 0);

	अगर (!base)
		वापस -ENOMEM;
	अगर (!irq)
		वापस -EINVAL;
	अगर (IS_ERR(घड़ी))
		वापस PTR_ERR(घड़ी);

	चयन (of_alias_get_id(np, "timer")) अणु
	हाल CLPS711X_CLKSRC_CLOCKSOURCE:
		clps711x_clksrc_init(घड़ी, base);
		अवरोध;
	हाल CLPS711X_CLKSRC_CLOCKEVENT:
		वापस _clps711x_clkevt_init(घड़ी, base, irq);
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
TIMER_OF_DECLARE(clps711x, "cirrus,ep7209-timer", clps711x_समयr_init);
