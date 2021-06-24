<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Rockchip समयr support
 *
 * Copyright (C) Daniel Lezcano <daniel.lezcano@linaro.org>
 */
#समावेश <linux/clk.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>

#घोषणा TIMER_NAME "rk_timer"

#घोषणा TIMER_LOAD_COUNT0	0x00
#घोषणा TIMER_LOAD_COUNT1	0x04
#घोषणा TIMER_CURRENT_VALUE0	0x08
#घोषणा TIMER_CURRENT_VALUE1	0x0C
#घोषणा TIMER_CONTROL_REG3288	0x10
#घोषणा TIMER_CONTROL_REG3399	0x1c
#घोषणा TIMER_INT_STATUS	0x18

#घोषणा TIMER_DISABLE		0x0
#घोषणा TIMER_ENABLE		0x1
#घोषणा TIMER_MODE_FREE_RUNNING			(0 << 1)
#घोषणा TIMER_MODE_USER_DEFINED_COUNT		(1 << 1)
#घोषणा TIMER_INT_UNMASK			(1 << 2)

काष्ठा rk_समयr अणु
	व्योम __iomem *base;
	व्योम __iomem *ctrl;
	काष्ठा clk *clk;
	काष्ठा clk *pclk;
	u32 freq;
	पूर्णांक irq;
पूर्ण;

काष्ठा rk_clkevt अणु
	काष्ठा घड़ी_event_device ce;
	काष्ठा rk_समयr समयr;
पूर्ण;

अटल काष्ठा rk_clkevt *rk_clkevt;
अटल काष्ठा rk_समयr *rk_clksrc;

अटल अंतरभूत काष्ठा rk_समयr *rk_समयr(काष्ठा घड़ी_event_device *ce)
अणु
	वापस &container_of(ce, काष्ठा rk_clkevt, ce)->समयr;
पूर्ण

अटल अंतरभूत व्योम rk_समयr_disable(काष्ठा rk_समयr *समयr)
अणु
	ग_लिखोl_relaxed(TIMER_DISABLE, समयr->ctrl);
पूर्ण

अटल अंतरभूत व्योम rk_समयr_enable(काष्ठा rk_समयr *समयr, u32 flags)
अणु
	ग_लिखोl_relaxed(TIMER_ENABLE | flags, समयr->ctrl);
पूर्ण

अटल व्योम rk_समयr_update_counter(अचिन्हित दीर्घ cycles,
				    काष्ठा rk_समयr *समयr)
अणु
	ग_लिखोl_relaxed(cycles, समयr->base + TIMER_LOAD_COUNT0);
	ग_लिखोl_relaxed(0, समयr->base + TIMER_LOAD_COUNT1);
पूर्ण

अटल व्योम rk_समयr_पूर्णांकerrupt_clear(काष्ठा rk_समयr *समयr)
अणु
	ग_लिखोl_relaxed(1, समयr->base + TIMER_INT_STATUS);
पूर्ण

अटल अंतरभूत पूर्णांक rk_समयr_set_next_event(अचिन्हित दीर्घ cycles,
					  काष्ठा घड़ी_event_device *ce)
अणु
	काष्ठा rk_समयr *समयr = rk_समयr(ce);

	rk_समयr_disable(समयr);
	rk_समयr_update_counter(cycles, समयr);
	rk_समयr_enable(समयr, TIMER_MODE_USER_DEFINED_COUNT |
			       TIMER_INT_UNMASK);
	वापस 0;
पूर्ण

अटल पूर्णांक rk_समयr_shutकरोwn(काष्ठा घड़ी_event_device *ce)
अणु
	काष्ठा rk_समयr *समयr = rk_समयr(ce);

	rk_समयr_disable(समयr);
	वापस 0;
पूर्ण

अटल पूर्णांक rk_समयr_set_periodic(काष्ठा घड़ी_event_device *ce)
अणु
	काष्ठा rk_समयr *समयr = rk_समयr(ce);

	rk_समयr_disable(समयr);
	rk_समयr_update_counter(समयr->freq / HZ - 1, समयr);
	rk_समयr_enable(समयr, TIMER_MODE_FREE_RUNNING | TIMER_INT_UNMASK);
	वापस 0;
पूर्ण

अटल irqवापस_t rk_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *ce = dev_id;
	काष्ठा rk_समयr *समयr = rk_समयr(ce);

	rk_समयr_पूर्णांकerrupt_clear(समयr);

	अगर (घड़ीevent_state_oneshot(ce))
		rk_समयr_disable(समयr);

	ce->event_handler(ce);

	वापस IRQ_HANDLED;
पूर्ण

अटल u64 notrace rk_समयr_sched_पढ़ो(व्योम)
अणु
	वापस ~पढ़ोl_relaxed(rk_clksrc->base + TIMER_CURRENT_VALUE0);
पूर्ण

अटल पूर्णांक __init
rk_समयr_probe(काष्ठा rk_समयr *समयr, काष्ठा device_node *np)
अणु
	काष्ठा clk *समयr_clk;
	काष्ठा clk *pclk;
	पूर्णांक ret = -EINVAL, irq;
	u32 ctrl_reg = TIMER_CONTROL_REG3288;

	समयr->base = of_iomap(np, 0);
	अगर (!समयr->base) अणु
		pr_err("Failed to get base address for '%s'\n", TIMER_NAME);
		वापस -ENXIO;
	पूर्ण

	अगर (of_device_is_compatible(np, "rockchip,rk3399-timer"))
		ctrl_reg = TIMER_CONTROL_REG3399;

	समयr->ctrl = समयr->base + ctrl_reg;

	pclk = of_clk_get_by_name(np, "pclk");
	अगर (IS_ERR(pclk)) अणु
		ret = PTR_ERR(pclk);
		pr_err("Failed to get pclk for '%s'\n", TIMER_NAME);
		जाओ out_unmap;
	पूर्ण

	ret = clk_prepare_enable(pclk);
	अगर (ret) अणु
		pr_err("Failed to enable pclk for '%s'\n", TIMER_NAME);
		जाओ out_unmap;
	पूर्ण
	समयr->pclk = pclk;

	समयr_clk = of_clk_get_by_name(np, "timer");
	अगर (IS_ERR(समयr_clk)) अणु
		ret = PTR_ERR(समयr_clk);
		pr_err("Failed to get timer clock for '%s'\n", TIMER_NAME);
		जाओ out_समयr_clk;
	पूर्ण

	ret = clk_prepare_enable(समयr_clk);
	अगर (ret) अणु
		pr_err("Failed to enable timer clock\n");
		जाओ out_समयr_clk;
	पूर्ण
	समयr->clk = समयr_clk;

	समयr->freq = clk_get_rate(समयr_clk);

	irq = irq_of_parse_and_map(np, 0);
	अगर (!irq) अणु
		ret = -EINVAL;
		pr_err("Failed to map interrupts for '%s'\n", TIMER_NAME);
		जाओ out_irq;
	पूर्ण
	समयr->irq = irq;

	rk_समयr_पूर्णांकerrupt_clear(समयr);
	rk_समयr_disable(समयr);
	वापस 0;

out_irq:
	clk_disable_unprepare(समयr_clk);
out_समयr_clk:
	clk_disable_unprepare(pclk);
out_unmap:
	iounmap(समयr->base);

	वापस ret;
पूर्ण

अटल व्योम __init rk_समयr_cleanup(काष्ठा rk_समयr *समयr)
अणु
	clk_disable_unprepare(समयr->clk);
	clk_disable_unprepare(समयr->pclk);
	iounmap(समयr->base);
पूर्ण

अटल पूर्णांक __init rk_clkevt_init(काष्ठा device_node *np)
अणु
	काष्ठा घड़ी_event_device *ce;
	पूर्णांक ret = -EINVAL;

	rk_clkevt = kzalloc(माप(काष्ठा rk_clkevt), GFP_KERNEL);
	अगर (!rk_clkevt) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = rk_समयr_probe(&rk_clkevt->समयr, np);
	अगर (ret)
		जाओ out_probe;

	ce = &rk_clkevt->ce;
	ce->name = TIMER_NAME;
	ce->features = CLOCK_EVT_FEAT_PERIODIC | CLOCK_EVT_FEAT_ONESHOT |
		       CLOCK_EVT_FEAT_DYNIRQ;
	ce->set_next_event = rk_समयr_set_next_event;
	ce->set_state_shutकरोwn = rk_समयr_shutकरोwn;
	ce->set_state_periodic = rk_समयr_set_periodic;
	ce->irq = rk_clkevt->समयr.irq;
	ce->cpumask = cpu_possible_mask;
	ce->rating = 250;

	ret = request_irq(rk_clkevt->समयr.irq, rk_समयr_पूर्णांकerrupt, IRQF_TIMER,
			  TIMER_NAME, ce);
	अगर (ret) अणु
		pr_err("Failed to initialize '%s': %d\n",
			TIMER_NAME, ret);
		जाओ out_irq;
	पूर्ण

	घड़ीevents_config_and_रेजिस्टर(&rk_clkevt->ce,
					rk_clkevt->समयr.freq, 1, अच_पूर्णांक_उच्च);
	वापस 0;

out_irq:
	rk_समयr_cleanup(&rk_clkevt->समयr);
out_probe:
	kमुक्त(rk_clkevt);
out:
	/* Leave rk_clkevt not शून्य to prevent future init */
	rk_clkevt = ERR_PTR(ret);
	वापस ret;
पूर्ण

अटल पूर्णांक __init rk_clksrc_init(काष्ठा device_node *np)
अणु
	पूर्णांक ret = -EINVAL;

	rk_clksrc = kzalloc(माप(काष्ठा rk_समयr), GFP_KERNEL);
	अगर (!rk_clksrc) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = rk_समयr_probe(rk_clksrc, np);
	अगर (ret)
		जाओ out_probe;

	rk_समयr_update_counter(अच_पूर्णांक_उच्च, rk_clksrc);
	rk_समयr_enable(rk_clksrc, 0);

	ret = घड़ीsource_mmio_init(rk_clksrc->base + TIMER_CURRENT_VALUE0,
		TIMER_NAME, rk_clksrc->freq, 250, 32,
		घड़ीsource_mmio_पढ़ोl_करोwn);
	अगर (ret) अणु
		pr_err("Failed to register clocksource\n");
		जाओ out_घड़ीsource;
	पूर्ण

	sched_घड़ी_रेजिस्टर(rk_समयr_sched_पढ़ो, 32, rk_clksrc->freq);
	वापस 0;

out_घड़ीsource:
	rk_समयr_cleanup(rk_clksrc);
out_probe:
	kमुक्त(rk_clksrc);
out:
	/* Leave rk_clksrc not शून्य to prevent future init */
	rk_clksrc = ERR_PTR(ret);
	वापस ret;
पूर्ण

अटल पूर्णांक __init rk_समयr_init(काष्ठा device_node *np)
अणु
	अगर (!rk_clkevt)
		वापस rk_clkevt_init(np);

	अगर (!rk_clksrc)
		वापस rk_clksrc_init(np);

	pr_err("Too many timer definitions for '%s'\n", TIMER_NAME);
	वापस -EINVAL;
पूर्ण

TIMER_OF_DECLARE(rk3288_समयr, "rockchip,rk3288-timer", rk_समयr_init);
TIMER_OF_DECLARE(rk3399_समयr, "rockchip,rk3399-timer", rk_समयr_init);
