<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Integrator/AP समयr driver
 * Copyright (C) 2000-2003 Deep Blue Solutions Ltd
 * Copyright (c) 2014, Linaro Limited
 */

#समावेश <linux/clk.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched_घड़ी.h>

#समावेश "timer-sp.h"

अटल व्योम __iomem * sched_clk_base;

अटल u64 notrace पूर्णांकegrator_पढ़ो_sched_घड़ी(व्योम)
अणु
	वापस -पढ़ोl(sched_clk_base + TIMER_VALUE);
पूर्ण

अटल पूर्णांक __init पूर्णांकegrator_घड़ीsource_init(अचिन्हित दीर्घ inrate,
					      व्योम __iomem *base)
अणु
	u32 ctrl = TIMER_CTRL_ENABLE | TIMER_CTRL_PERIODIC;
	अचिन्हित दीर्घ rate = inrate;
	पूर्णांक ret;

	अगर (rate >= 1500000) अणु
		rate /= 16;
		ctrl |= TIMER_CTRL_DIV16;
	पूर्ण

	ग_लिखोl(0xffff, base + TIMER_LOAD);
	ग_लिखोl(ctrl, base + TIMER_CTRL);

	ret = घड़ीsource_mmio_init(base + TIMER_VALUE, "timer2",
				    rate, 200, 16, घड़ीsource_mmio_पढ़ोl_करोwn);
	अगर (ret)
		वापस ret;

	sched_clk_base = base;
	sched_घड़ी_रेजिस्टर(पूर्णांकegrator_पढ़ो_sched_घड़ी, 16, rate);

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ समयr_reload;
अटल व्योम __iomem * clkevt_base;

/*
 * IRQ handler क्रम the समयr
 */
अटल irqवापस_t पूर्णांकegrator_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = dev_id;

	/* clear the पूर्णांकerrupt */
	ग_लिखोl(1, clkevt_base + TIMER_INTCLR);

	evt->event_handler(evt);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक clkevt_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	u32 ctrl = पढ़ोl(clkevt_base + TIMER_CTRL) & ~TIMER_CTRL_ENABLE;

	/* Disable समयr */
	ग_लिखोl(ctrl, clkevt_base + TIMER_CTRL);
	वापस 0;
पूर्ण

अटल पूर्णांक clkevt_set_oneshot(काष्ठा घड़ी_event_device *evt)
अणु
	u32 ctrl = पढ़ोl(clkevt_base + TIMER_CTRL) &
		   ~(TIMER_CTRL_ENABLE | TIMER_CTRL_PERIODIC);

	/* Leave the समयr disabled, .set_next_event will enable it */
	ग_लिखोl(ctrl, clkevt_base + TIMER_CTRL);
	वापस 0;
पूर्ण

अटल पूर्णांक clkevt_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	u32 ctrl = पढ़ोl(clkevt_base + TIMER_CTRL) & ~TIMER_CTRL_ENABLE;

	/* Disable समयr */
	ग_लिखोl(ctrl, clkevt_base + TIMER_CTRL);

	/* Enable the समयr and start the periodic tick */
	ग_लिखोl(समयr_reload, clkevt_base + TIMER_LOAD);
	ctrl |= TIMER_CTRL_PERIODIC | TIMER_CTRL_ENABLE;
	ग_लिखोl(ctrl, clkevt_base + TIMER_CTRL);
	वापस 0;
पूर्ण

अटल पूर्णांक clkevt_set_next_event(अचिन्हित दीर्घ next, काष्ठा घड़ी_event_device *evt)
अणु
	अचिन्हित दीर्घ ctrl = पढ़ोl(clkevt_base + TIMER_CTRL);

	ग_लिखोl(ctrl & ~TIMER_CTRL_ENABLE, clkevt_base + TIMER_CTRL);
	ग_लिखोl(next, clkevt_base + TIMER_LOAD);
	ग_लिखोl(ctrl | TIMER_CTRL_ENABLE, clkevt_base + TIMER_CTRL);

	वापस 0;
पूर्ण

अटल काष्ठा घड़ी_event_device पूर्णांकegrator_घड़ीevent = अणु
	.name			= "timer1",
	.features		= CLOCK_EVT_FEAT_PERIODIC |
				  CLOCK_EVT_FEAT_ONESHOT,
	.set_state_shutकरोwn	= clkevt_shutकरोwn,
	.set_state_periodic	= clkevt_set_periodic,
	.set_state_oneshot	= clkevt_set_oneshot,
	.tick_resume		= clkevt_shutकरोwn,
	.set_next_event		= clkevt_set_next_event,
	.rating			= 300,
पूर्ण;

अटल पूर्णांक पूर्णांकegrator_घड़ीevent_init(अचिन्हित दीर्घ inrate,
				      व्योम __iomem *base, पूर्णांक irq)
अणु
	अचिन्हित दीर्घ rate = inrate;
	अचिन्हित पूर्णांक ctrl = 0;
	पूर्णांक ret;

	clkevt_base = base;
	/* Calculate and program a भागisor */
	अगर (rate > 0x100000 * HZ) अणु
		rate /= 256;
		ctrl |= TIMER_CTRL_DIV256;
	पूर्ण अन्यथा अगर (rate > 0x10000 * HZ) अणु
		rate /= 16;
		ctrl |= TIMER_CTRL_DIV16;
	पूर्ण
	समयr_reload = rate / HZ;
	ग_लिखोl(ctrl, clkevt_base + TIMER_CTRL);

	ret = request_irq(irq, पूर्णांकegrator_समयr_पूर्णांकerrupt,
			  IRQF_TIMER | IRQF_IRQPOLL, "timer",
			  &पूर्णांकegrator_घड़ीevent);
	अगर (ret)
		वापस ret;

	घड़ीevents_config_and_रेजिस्टर(&पूर्णांकegrator_घड़ीevent,
					rate,
					1,
					0xffffU);
	वापस 0;
पूर्ण

अटल पूर्णांक __init पूर्णांकegrator_ap_समयr_init_of(काष्ठा device_node *node)
अणु
	स्थिर अक्षर *path;
	व्योम __iomem *base;
	पूर्णांक err;
	पूर्णांक irq;
	काष्ठा clk *clk;
	अचिन्हित दीर्घ rate;
	काष्ठा device_node *alias_node;

	base = of_io_request_and_map(node, 0, "integrator-timer");
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	clk = of_clk_get(node, 0);
	अगर (IS_ERR(clk)) अणु
		pr_err("No clock for %pOFn\n", node);
		वापस PTR_ERR(clk);
	पूर्ण
	clk_prepare_enable(clk);
	rate = clk_get_rate(clk);
	ग_लिखोl(0, base + TIMER_CTRL);

	err = of_property_पढ़ो_string(of_aliases,
				"arm,timer-primary", &path);
	अगर (err) अणु
		pr_warn("Failed to read property\n");
		वापस err;
	पूर्ण

	alias_node = of_find_node_by_path(path);

	/*
	 * The poपूर्णांकer is used as an identअगरier not as a poपूर्णांकer, we
	 * can drop the refcount on the of__node immediately after
	 * getting it.
	 */
	of_node_put(alias_node);

	अगर (node == alias_node)
		/* The primary समयr lacks IRQ, use as घड़ीsource */
		वापस पूर्णांकegrator_घड़ीsource_init(rate, base);

	err = of_property_पढ़ो_string(of_aliases,
				"arm,timer-secondary", &path);
	अगर (err) अणु
		pr_warn("Failed to read property\n");
		वापस err;
	पूर्ण

	alias_node = of_find_node_by_path(path);

	of_node_put(alias_node);

	अगर (node == alias_node) अणु
		/* The secondary समयr will drive the घड़ी event */
		irq = irq_of_parse_and_map(node, 0);
		वापस पूर्णांकegrator_घड़ीevent_init(rate, base, irq);
	पूर्ण

	pr_info("Timer @%p unused\n", base);
	clk_disable_unprepare(clk);

	वापस 0;
पूर्ण

TIMER_OF_DECLARE(पूर्णांकegrator_ap_समयr, "arm,integrator-timer",
		       पूर्णांकegrator_ap_समयr_init_of);
