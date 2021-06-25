<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 ARM Limited
 *
 * Author: Vladimir Murzin <vladimir.murzin@arm.com>
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/clk.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/slab.h>

#घोषणा TIMER_CTRL		0x0
#घोषणा TIMER_CTRL_ENABLE	BIT(0)
#घोषणा TIMER_CTRL_IE		BIT(3)

#घोषणा TIMER_VALUE		0x4
#घोषणा TIMER_RELOAD		0x8
#घोषणा TIMER_INT		0xc

काष्ठा घड़ीevent_mps2 अणु
	व्योम __iomem *reg;
	u32 घड़ी_count_per_tick;
	काष्ठा घड़ी_event_device clkevt;
पूर्ण;

अटल व्योम __iomem *sched_घड़ी_base;

अटल u64 notrace mps2_sched_पढ़ो(व्योम)
अणु
	वापस ~पढ़ोl_relaxed(sched_घड़ी_base + TIMER_VALUE);
पूर्ण

अटल अंतरभूत काष्ठा घड़ीevent_mps2 *to_mps2_clkevt(काष्ठा घड़ी_event_device *c)
अणु
	वापस container_of(c, काष्ठा घड़ीevent_mps2, clkevt);
पूर्ण

अटल व्योम घड़ीevent_mps2_ग_लिखोl(u32 val, काष्ठा घड़ी_event_device *c, u32 offset)
अणु
	ग_लिखोl_relaxed(val, to_mps2_clkevt(c)->reg + offset);
पूर्ण

अटल पूर्णांक mps2_समयr_shutकरोwn(काष्ठा घड़ी_event_device *ce)
अणु
	घड़ीevent_mps2_ग_लिखोl(0, ce, TIMER_RELOAD);
	घड़ीevent_mps2_ग_लिखोl(0, ce, TIMER_CTRL);

	वापस 0;
पूर्ण

अटल पूर्णांक mps2_समयr_set_next_event(अचिन्हित दीर्घ next, काष्ठा घड़ी_event_device *ce)
अणु
	घड़ीevent_mps2_ग_लिखोl(next, ce, TIMER_VALUE);
	घड़ीevent_mps2_ग_लिखोl(TIMER_CTRL_IE | TIMER_CTRL_ENABLE, ce, TIMER_CTRL);

	वापस 0;
पूर्ण

अटल पूर्णांक mps2_समयr_set_periodic(काष्ठा घड़ी_event_device *ce)
अणु
	u32 घड़ी_count_per_tick = to_mps2_clkevt(ce)->घड़ी_count_per_tick;

	घड़ीevent_mps2_ग_लिखोl(घड़ी_count_per_tick, ce, TIMER_RELOAD);
	घड़ीevent_mps2_ग_लिखोl(घड़ी_count_per_tick, ce, TIMER_VALUE);
	घड़ीevent_mps2_ग_लिखोl(TIMER_CTRL_IE | TIMER_CTRL_ENABLE, ce, TIMER_CTRL);

	वापस 0;
पूर्ण

अटल irqवापस_t mps2_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ीevent_mps2 *ce = dev_id;
	u32 status = पढ़ोl_relaxed(ce->reg + TIMER_INT);

	अगर (!status) अणु
		pr_warn("spurious interrupt\n");
		वापस IRQ_NONE;
	पूर्ण

	ग_लिखोl_relaxed(1, ce->reg + TIMER_INT);

	ce->clkevt.event_handler(&ce->clkevt);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init mps2_घड़ीevent_init(काष्ठा device_node *np)
अणु
	व्योम __iomem *base;
	काष्ठा clk *clk = शून्य;
	काष्ठा घड़ीevent_mps2 *ce;
	u32 rate;
	पूर्णांक irq, ret;
	स्थिर अक्षर *name = "mps2-clkevt";

	ret = of_property_पढ़ो_u32(np, "clock-frequency", &rate);
	अगर (ret) अणु
		clk = of_clk_get(np, 0);
		अगर (IS_ERR(clk)) अणु
			ret = PTR_ERR(clk);
			pr_err("failed to get clock for clockevent: %d\n", ret);
			जाओ out;
		पूर्ण

		ret = clk_prepare_enable(clk);
		अगर (ret) अणु
			pr_err("failed to enable clock for clockevent: %d\n", ret);
			जाओ out_clk_put;
		पूर्ण

		rate = clk_get_rate(clk);
	पूर्ण

	base = of_iomap(np, 0);
	अगर (!base) अणु
		ret = -EADDRNOTAVAIL;
		pr_err("failed to map register for clockevent: %d\n", ret);
		जाओ out_clk_disable;
	पूर्ण

	irq = irq_of_parse_and_map(np, 0);
	अगर (!irq) अणु
		ret = -ENOENT;
		pr_err("failed to get irq for clockevent: %d\n", ret);
		जाओ out_iounmap;
	पूर्ण

	ce = kzalloc(माप(*ce), GFP_KERNEL);
	अगर (!ce) अणु
		ret = -ENOMEM;
		जाओ out_iounmap;
	पूर्ण

	ce->reg = base;
	ce->घड़ी_count_per_tick = DIV_ROUND_CLOSEST(rate, HZ);
	ce->clkevt.irq = irq;
	ce->clkevt.name = name;
	ce->clkevt.rating = 200;
	ce->clkevt.features = CLOCK_EVT_FEAT_PERIODIC | CLOCK_EVT_FEAT_ONESHOT;
	ce->clkevt.cpumask = cpu_possible_mask;
	ce->clkevt.set_state_shutकरोwn	= mps2_समयr_shutकरोwn;
	ce->clkevt.set_state_periodic	= mps2_समयr_set_periodic;
	ce->clkevt.set_state_oneshot	= mps2_समयr_shutकरोwn;
	ce->clkevt.set_next_event	= mps2_समयr_set_next_event;

	/* Ensure समयr is disabled */
	ग_लिखोl_relaxed(0, base + TIMER_CTRL);

	ret = request_irq(irq, mps2_समयr_पूर्णांकerrupt, IRQF_TIMER, name, ce);
	अगर (ret) अणु
		pr_err("failed to request irq for clockevent: %d\n", ret);
		जाओ out_kमुक्त;
	पूर्ण

	घड़ीevents_config_and_रेजिस्टर(&ce->clkevt, rate, 0xf, 0xffffffff);

	वापस 0;

out_kमुक्त:
	kमुक्त(ce);
out_iounmap:
	iounmap(base);
out_clk_disable:
	/* clk_अणुdisable, unprepare, putपूर्ण() can handle शून्य as a parameter */
	clk_disable_unprepare(clk);
out_clk_put:
	clk_put(clk);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक __init mps2_घड़ीsource_init(काष्ठा device_node *np)
अणु
	व्योम __iomem *base;
	काष्ठा clk *clk = शून्य;
	u32 rate;
	पूर्णांक ret;
	स्थिर अक्षर *name = "mps2-clksrc";

	ret = of_property_पढ़ो_u32(np, "clock-frequency", &rate);
	अगर (ret) अणु
		clk = of_clk_get(np, 0);
		अगर (IS_ERR(clk)) अणु
			ret = PTR_ERR(clk);
			pr_err("failed to get clock for clocksource: %d\n", ret);
			जाओ out;
		पूर्ण

		ret = clk_prepare_enable(clk);
		अगर (ret) अणु
			pr_err("failed to enable clock for clocksource: %d\n", ret);
			जाओ out_clk_put;
		पूर्ण

		rate = clk_get_rate(clk);
	पूर्ण

	base = of_iomap(np, 0);
	अगर (!base) अणु
		ret = -EADDRNOTAVAIL;
		pr_err("failed to map register for clocksource: %d\n", ret);
		जाओ out_clk_disable;
	पूर्ण

	/* Ensure समयr is disabled */
	ग_लिखोl_relaxed(0, base + TIMER_CTRL);

	/* ... and set it up as मुक्त-running घड़ीsource */
	ग_लिखोl_relaxed(0xffffffff, base + TIMER_VALUE);
	ग_लिखोl_relaxed(0xffffffff, base + TIMER_RELOAD);

	ग_लिखोl_relaxed(TIMER_CTRL_ENABLE, base + TIMER_CTRL);

	ret = घड़ीsource_mmio_init(base + TIMER_VALUE, name,
				    rate, 200, 32,
				    घड़ीsource_mmio_पढ़ोl_करोwn);
	अगर (ret) अणु
		pr_err("failed to init clocksource: %d\n", ret);
		जाओ out_iounmap;
	पूर्ण

	sched_घड़ी_base = base;
	sched_घड़ी_रेजिस्टर(mps2_sched_पढ़ो, 32, rate);

	वापस 0;

out_iounmap:
	iounmap(base);
out_clk_disable:
	/* clk_अणुdisable, unprepare, putपूर्ण() can handle शून्य as a parameter */
	clk_disable_unprepare(clk);
out_clk_put:
	clk_put(clk);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक __init mps2_समयr_init(काष्ठा device_node *np)
अणु
	अटल पूर्णांक has_घड़ीsource, has_घड़ीevent;
	पूर्णांक ret;

	अगर (!has_घड़ीsource) अणु
		ret = mps2_घड़ीsource_init(np);
		अगर (!ret) अणु
			has_घड़ीsource = 1;
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (!has_घड़ीevent) अणु
		ret = mps2_घड़ीevent_init(np);
		अगर (!ret) अणु
			has_घड़ीevent = 1;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

TIMER_OF_DECLARE(mps2_समयr, "arm,mps2-timer", mps2_समयr_init);
