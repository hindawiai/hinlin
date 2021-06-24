<शैली गुरु>
/*
 * Conexant Digicolor समयr driver
 *
 * Author: Baruch Siach <baruch@tkos.co.il>
 *
 * Copyright (C) 2014 Paraकरोx Innovation Ltd.
 *
 * Based on:
 *	Allwinner SoCs hsसमयr driver
 *
 * Copyright (C) 2013 Maxime Ripard
 *
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

/*
 * Conexant Digicolor SoCs have 8 configurable समयrs, named from "Timer A" to
 * "Timer H". Timer A is the only one with watchकरोg support, so it is dedicated
 * to the watchकरोg driver. This driver uses Timer B क्रम sched_घड़ी(), and
 * Timer C क्रम घड़ीevents.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/clk.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>

क्रमागत अणु
	TIMER_A,
	TIMER_B,
	TIMER_C,
	TIMER_D,
	TIMER_E,
	TIMER_F,
	TIMER_G,
	TIMER_H,
पूर्ण;

#घोषणा CONTROL(t)	((t)*8)
#घोषणा COUNT(t)	((t)*8 + 4)

#घोषणा CONTROL_DISABLE		0
#घोषणा CONTROL_ENABLE		BIT(0)
#घोषणा CONTROL_MODE(m)		((m) << 4)
#घोषणा CONTROL_MODE_ONESHOT	CONTROL_MODE(1)
#घोषणा CONTROL_MODE_PERIODIC	CONTROL_MODE(2)

काष्ठा digicolor_समयr अणु
	काष्ठा घड़ी_event_device ce;
	व्योम __iomem *base;
	u32 ticks_per_jअगरfy;
	पूर्णांक समयr_id; /* one of TIMER_* */
पूर्ण;

अटल काष्ठा digicolor_समयr *dc_समयr(काष्ठा घड़ी_event_device *ce)
अणु
	वापस container_of(ce, काष्ठा digicolor_समयr, ce);
पूर्ण

अटल अंतरभूत व्योम dc_समयr_disable(काष्ठा घड़ी_event_device *ce)
अणु
	काष्ठा digicolor_समयr *dt = dc_समयr(ce);
	ग_लिखोb(CONTROL_DISABLE, dt->base + CONTROL(dt->समयr_id));
पूर्ण

अटल अंतरभूत व्योम dc_समयr_enable(काष्ठा घड़ी_event_device *ce, u32 mode)
अणु
	काष्ठा digicolor_समयr *dt = dc_समयr(ce);
	ग_लिखोb(CONTROL_ENABLE | mode, dt->base + CONTROL(dt->समयr_id));
पूर्ण

अटल अंतरभूत व्योम dc_समयr_set_count(काष्ठा घड़ी_event_device *ce,
				      अचिन्हित दीर्घ count)
अणु
	काष्ठा digicolor_समयr *dt = dc_समयr(ce);
	ग_लिखोl(count, dt->base + COUNT(dt->समयr_id));
पूर्ण

अटल पूर्णांक digicolor_clkevt_shutकरोwn(काष्ठा घड़ी_event_device *ce)
अणु
	dc_समयr_disable(ce);
	वापस 0;
पूर्ण

अटल पूर्णांक digicolor_clkevt_set_oneshot(काष्ठा घड़ी_event_device *ce)
अणु
	dc_समयr_disable(ce);
	dc_समयr_enable(ce, CONTROL_MODE_ONESHOT);
	वापस 0;
पूर्ण

अटल पूर्णांक digicolor_clkevt_set_periodic(काष्ठा घड़ी_event_device *ce)
अणु
	काष्ठा digicolor_समयr *dt = dc_समयr(ce);

	dc_समयr_disable(ce);
	dc_समयr_set_count(ce, dt->ticks_per_jअगरfy);
	dc_समयr_enable(ce, CONTROL_MODE_PERIODIC);
	वापस 0;
पूर्ण

अटल पूर्णांक digicolor_clkevt_next_event(अचिन्हित दीर्घ evt,
				       काष्ठा घड़ी_event_device *ce)
अणु
	dc_समयr_disable(ce);
	dc_समयr_set_count(ce, evt);
	dc_समयr_enable(ce, CONTROL_MODE_ONESHOT);

	वापस 0;
पूर्ण

अटल काष्ठा digicolor_समयr dc_समयr_dev = अणु
	.ce = अणु
		.name = "digicolor_tick",
		.rating = 340,
		.features = CLOCK_EVT_FEAT_PERIODIC | CLOCK_EVT_FEAT_ONESHOT,
		.set_state_shutकरोwn = digicolor_clkevt_shutकरोwn,
		.set_state_periodic = digicolor_clkevt_set_periodic,
		.set_state_oneshot = digicolor_clkevt_set_oneshot,
		.tick_resume = digicolor_clkevt_shutकरोwn,
		.set_next_event = digicolor_clkevt_next_event,
	पूर्ण,
	.समयr_id = TIMER_C,
पूर्ण;

अटल irqवापस_t digicolor_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = dev_id;

	evt->event_handler(evt);

	वापस IRQ_HANDLED;
पूर्ण

अटल u64 notrace digicolor_समयr_sched_पढ़ो(व्योम)
अणु
	वापस ~पढ़ोl(dc_समयr_dev.base + COUNT(TIMER_B));
पूर्ण

अटल पूर्णांक __init digicolor_समयr_init(काष्ठा device_node *node)
अणु
	अचिन्हित दीर्घ rate;
	काष्ठा clk *clk;
	पूर्णांक ret, irq;

	/*
	 * समयr रेजिस्टरs are shared with the watchकरोg समयr;
	 * करोn't map exclusively
	 */
	dc_समयr_dev.base = of_iomap(node, 0);
	अगर (!dc_समयr_dev.base) अणु
		pr_err("Can't map registers\n");
		वापस -ENXIO;
	पूर्ण

	irq = irq_of_parse_and_map(node, dc_समयr_dev.समयr_id);
	अगर (irq <= 0) अणु
		pr_err("Can't parse IRQ\n");
		वापस -EINVAL;
	पूर्ण

	clk = of_clk_get(node, 0);
	अगर (IS_ERR(clk)) अणु
		pr_err("Can't get timer clock\n");
		वापस PTR_ERR(clk);
	पूर्ण
	clk_prepare_enable(clk);
	rate = clk_get_rate(clk);
	dc_समयr_dev.ticks_per_jअगरfy = DIV_ROUND_UP(rate, HZ);

	ग_लिखोb(CONTROL_DISABLE, dc_समयr_dev.base + CONTROL(TIMER_B));
	ग_लिखोl(अच_पूर्णांक_उच्च, dc_समयr_dev.base + COUNT(TIMER_B));
	ग_लिखोb(CONTROL_ENABLE, dc_समयr_dev.base + CONTROL(TIMER_B));

	sched_घड़ी_रेजिस्टर(digicolor_समयr_sched_पढ़ो, 32, rate);
	घड़ीsource_mmio_init(dc_समयr_dev.base + COUNT(TIMER_B), node->name,
			      rate, 340, 32, घड़ीsource_mmio_पढ़ोl_करोwn);

	ret = request_irq(irq, digicolor_समयr_पूर्णांकerrupt,
			  IRQF_TIMER | IRQF_IRQPOLL, "digicolor_timerC",
			  &dc_समयr_dev.ce);
	अगर (ret) अणु
		pr_warn("request of timer irq %d failed (%d)\n", irq, ret);
		वापस ret;
	पूर्ण

	dc_समयr_dev.ce.cpumask = cpu_possible_mask;
	dc_समयr_dev.ce.irq = irq;

	घड़ीevents_config_and_रेजिस्टर(&dc_समयr_dev.ce, rate, 0, 0xffffffff);

	वापस 0;
पूर्ण
TIMER_OF_DECLARE(conexant_digicolor, "cnxt,cx92755-timer",
		       digicolor_समयr_init);
