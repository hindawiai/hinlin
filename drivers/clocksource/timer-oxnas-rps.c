<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/घड़ीsource/समयr-oxnas-rps.c
 *
 * Copyright (C) 2009 Oxक्रमd Semiconductor Ltd
 * Copyright (C) 2013 Ma Haijun <mahaijuns@gmail.com>
 * Copyright (C) 2016 Neil Armstrong <narmstrong@baylibre.com>
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/sched_घड़ी.h>

/* TIMER1 used as tick
 * TIMER2 used as घड़ीsource
 */

/* Registers definitions */

#घोषणा TIMER_LOAD_REG		0x0
#घोषणा TIMER_CURR_REG		0x4
#घोषणा TIMER_CTRL_REG		0x8
#घोषणा TIMER_CLRINT_REG	0xC

#घोषणा TIMER_BITS		24

#घोषणा TIMER_MAX_VAL		(BIT(TIMER_BITS) - 1)

#घोषणा TIMER_PERIODIC		BIT(6)
#घोषणा TIMER_ENABLE		BIT(7)

#घोषणा TIMER_DIV1		(0)
#घोषणा TIMER_DIV16		(1 << 2)
#घोषणा TIMER_DIV256		(2 << 2)

#घोषणा TIMER1_REG_OFFSET	0
#घोषणा TIMER2_REG_OFFSET	0x20

/* Clockevent & Clocksource data */

काष्ठा oxnas_rps_समयr अणु
	काष्ठा घड़ी_event_device clkevent;
	व्योम __iomem *clksrc_base;
	व्योम __iomem *clkevt_base;
	अचिन्हित दीर्घ समयr_period;
	अचिन्हित पूर्णांक समयr_prescaler;
	काष्ठा clk *clk;
	पूर्णांक irq;
पूर्ण;

अटल irqवापस_t oxnas_rps_समयr_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा oxnas_rps_समयr *rps = dev_id;

	ग_लिखोl_relaxed(0, rps->clkevt_base + TIMER_CLRINT_REG);

	rps->clkevent.event_handler(&rps->clkevent);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम oxnas_rps_समयr_config(काष्ठा oxnas_rps_समयr *rps,
				   अचिन्हित दीर्घ period,
				   अचिन्हित पूर्णांक periodic)
अणु
	uपूर्णांक32_t cfg = rps->समयr_prescaler;

	अगर (period)
		cfg |= TIMER_ENABLE;

	अगर (periodic)
		cfg |= TIMER_PERIODIC;

	ग_लिखोl_relaxed(period, rps->clkevt_base + TIMER_LOAD_REG);
	ग_लिखोl_relaxed(cfg, rps->clkevt_base + TIMER_CTRL_REG);
पूर्ण

अटल पूर्णांक oxnas_rps_समयr_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा oxnas_rps_समयr *rps =
		container_of(evt, काष्ठा oxnas_rps_समयr, clkevent);

	oxnas_rps_समयr_config(rps, 0, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक oxnas_rps_समयr_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा oxnas_rps_समयr *rps =
		container_of(evt, काष्ठा oxnas_rps_समयr, clkevent);

	oxnas_rps_समयr_config(rps, rps->समयr_period, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक oxnas_rps_समयr_set_oneshot(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा oxnas_rps_समयr *rps =
		container_of(evt, काष्ठा oxnas_rps_समयr, clkevent);

	oxnas_rps_समयr_config(rps, rps->समयr_period, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक oxnas_rps_समयr_next_event(अचिन्हित दीर्घ delta,
				काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा oxnas_rps_समयr *rps =
		container_of(evt, काष्ठा oxnas_rps_समयr, clkevent);

	oxnas_rps_समयr_config(rps, delta, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक __init oxnas_rps_घड़ीevent_init(काष्ठा oxnas_rps_समयr *rps)
अणु
	uदीर्घ clk_rate = clk_get_rate(rps->clk);
	uदीर्घ समयr_rate;

	/* Start with prescaler 1 */
	rps->समयr_prescaler = TIMER_DIV1;
	rps->समयr_period = DIV_ROUND_UP(clk_rate, HZ);
	समयr_rate = clk_rate;

	अगर (rps->समयr_period > TIMER_MAX_VAL) अणु
		rps->समयr_prescaler = TIMER_DIV16;
		समयr_rate = clk_rate / 16;
		rps->समयr_period = DIV_ROUND_UP(समयr_rate, HZ);
	पूर्ण
	अगर (rps->समयr_period > TIMER_MAX_VAL) अणु
		rps->समयr_prescaler = TIMER_DIV256;
		समयr_rate = clk_rate / 256;
		rps->समयr_period = DIV_ROUND_UP(समयr_rate, HZ);
	पूर्ण

	rps->clkevent.name = "oxnas-rps";
	rps->clkevent.features = CLOCK_EVT_FEAT_PERIODIC |
				 CLOCK_EVT_FEAT_ONESHOT |
				 CLOCK_EVT_FEAT_DYNIRQ;
	rps->clkevent.tick_resume = oxnas_rps_समयr_shutकरोwn;
	rps->clkevent.set_state_shutकरोwn = oxnas_rps_समयr_shutकरोwn;
	rps->clkevent.set_state_periodic = oxnas_rps_समयr_set_periodic;
	rps->clkevent.set_state_oneshot = oxnas_rps_समयr_set_oneshot;
	rps->clkevent.set_next_event = oxnas_rps_समयr_next_event;
	rps->clkevent.rating = 200;
	rps->clkevent.cpumask = cpu_possible_mask;
	rps->clkevent.irq = rps->irq;
	घड़ीevents_config_and_रेजिस्टर(&rps->clkevent,
					समयr_rate,
					1,
					TIMER_MAX_VAL);

	pr_info("Registered clock event rate %luHz prescaler %x period %lu\n",
			clk_rate,
			rps->समयr_prescaler,
			rps->समयr_period);

	वापस 0;
पूर्ण

/* Clocksource */

अटल व्योम __iomem *समयr_sched_base;

अटल u64 notrace oxnas_rps_पढ़ो_sched_घड़ी(व्योम)
अणु
	वापस ~पढ़ोl_relaxed(समयr_sched_base);
पूर्ण

अटल पूर्णांक __init oxnas_rps_घड़ीsource_init(काष्ठा oxnas_rps_समयr *rps)
अणु
	uदीर्घ clk_rate = clk_get_rate(rps->clk);
	पूर्णांक ret;

	/* use prescale 16 */
	clk_rate = clk_rate / 16;

	ग_लिखोl_relaxed(TIMER_MAX_VAL, rps->clksrc_base + TIMER_LOAD_REG);
	ग_लिखोl_relaxed(TIMER_PERIODIC | TIMER_ENABLE | TIMER_DIV16,
			rps->clksrc_base + TIMER_CTRL_REG);

	समयr_sched_base = rps->clksrc_base + TIMER_CURR_REG;
	sched_घड़ी_रेजिस्टर(oxnas_rps_पढ़ो_sched_घड़ी,
			     TIMER_BITS, clk_rate);
	ret = घड़ीsource_mmio_init(समयr_sched_base,
				    "oxnas_rps_clocksource_timer",
				    clk_rate, 250, TIMER_BITS,
				    घड़ीsource_mmio_पढ़ोl_करोwn);
	अगर (WARN_ON(ret)) अणु
		pr_err("can't register clocksource\n");
		वापस ret;
	पूर्ण

	pr_info("Registered clocksource rate %luHz\n", clk_rate);

	वापस 0;
पूर्ण

अटल पूर्णांक __init oxnas_rps_समयr_init(काष्ठा device_node *np)
अणु
	काष्ठा oxnas_rps_समयr *rps;
	व्योम __iomem *base;
	पूर्णांक ret;

	rps = kzalloc(माप(*rps), GFP_KERNEL);
	अगर (!rps)
		वापस -ENOMEM;

	rps->clk = of_clk_get(np, 0);
	अगर (IS_ERR(rps->clk)) अणु
		ret = PTR_ERR(rps->clk);
		जाओ err_alloc;
	पूर्ण

	ret = clk_prepare_enable(rps->clk);
	अगर (ret)
		जाओ err_clk;

	base = of_iomap(np, 0);
	अगर (!base) अणु
		ret = -ENXIO;
		जाओ err_clk_prepare;
	पूर्ण

	rps->irq = irq_of_parse_and_map(np, 0);
	अगर (rps->irq < 0) अणु
		ret = -EINVAL;
		जाओ err_iomap;
	पूर्ण

	rps->clkevt_base = base + TIMER1_REG_OFFSET;
	rps->clksrc_base = base + TIMER2_REG_OFFSET;

	/* Disable समयrs */
	ग_लिखोl_relaxed(0, rps->clkevt_base + TIMER_CTRL_REG);
	ग_लिखोl_relaxed(0, rps->clksrc_base + TIMER_CTRL_REG);
	ग_लिखोl_relaxed(0, rps->clkevt_base + TIMER_LOAD_REG);
	ग_लिखोl_relaxed(0, rps->clksrc_base + TIMER_LOAD_REG);
	ग_लिखोl_relaxed(0, rps->clkevt_base + TIMER_CLRINT_REG);
	ग_लिखोl_relaxed(0, rps->clksrc_base + TIMER_CLRINT_REG);

	ret = request_irq(rps->irq, oxnas_rps_समयr_irq,
			  IRQF_TIMER | IRQF_IRQPOLL,
			  "rps-timer", rps);
	अगर (ret)
		जाओ err_iomap;

	ret = oxnas_rps_घड़ीsource_init(rps);
	अगर (ret)
		जाओ err_irqreq;

	ret = oxnas_rps_घड़ीevent_init(rps);
	अगर (ret)
		जाओ err_irqreq;

	वापस 0;

err_irqreq:
	मुक्त_irq(rps->irq, rps);
err_iomap:
	iounmap(base);
err_clk_prepare:
	clk_disable_unprepare(rps->clk);
err_clk:
	clk_put(rps->clk);
err_alloc:
	kमुक्त(rps);

	वापस ret;
पूर्ण

TIMER_OF_DECLARE(ox810se_rps,
		       "oxsemi,ox810se-rps-timer", oxnas_rps_समयr_init);
TIMER_OF_DECLARE(ox820_rps,
		       "oxsemi,ox820-rps-timer", oxnas_rps_समयr_init);
