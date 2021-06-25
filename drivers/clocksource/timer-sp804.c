<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  linux/drivers/घड़ीsource/समयr-sp.c
 *
 *  Copyright (C) 1999 - 2003 ARM Limited
 *  Copyright (C) 2000 Deep Blue Solutions Ltd
 */

#घोषणा pr_fmt(fmt)    KBUILD_MODNAME ": " fmt

#समावेश <linux/clk.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_clk.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/sched_घड़ी.h>

#समावेश "timer-sp.h"

/* Hisilicon 64-bit समयr(a variant of ARM SP804) */
#घोषणा HISI_TIMER_1_BASE	0x00
#घोषणा HISI_TIMER_2_BASE	0x40
#घोषणा HISI_TIMER_LOAD		0x00
#घोषणा HISI_TIMER_LOAD_H	0x04
#घोषणा HISI_TIMER_VALUE	0x08
#घोषणा HISI_TIMER_VALUE_H	0x0c
#घोषणा HISI_TIMER_CTRL		0x10
#घोषणा HISI_TIMER_INTCLR	0x14
#घोषणा HISI_TIMER_RIS		0x18
#घोषणा HISI_TIMER_MIS		0x1c
#घोषणा HISI_TIMER_BGLOAD	0x20
#घोषणा HISI_TIMER_BGLOAD_H	0x24

अटल काष्ठा sp804_समयr arm_sp804_समयr __initdata = अणु
	.load		= TIMER_LOAD,
	.value		= TIMER_VALUE,
	.ctrl		= TIMER_CTRL,
	.पूर्णांकclr		= TIMER_INTCLR,
	.समयr_base	= अणुTIMER_1_BASE, TIMER_2_BASEपूर्ण,
	.width		= 32,
पूर्ण;

अटल काष्ठा sp804_समयr hisi_sp804_समयr __initdata = अणु
	.load		= HISI_TIMER_LOAD,
	.load_h		= HISI_TIMER_LOAD_H,
	.value		= HISI_TIMER_VALUE,
	.value_h	= HISI_TIMER_VALUE_H,
	.ctrl		= HISI_TIMER_CTRL,
	.पूर्णांकclr		= HISI_TIMER_INTCLR,
	.समयr_base	= अणुHISI_TIMER_1_BASE, HISI_TIMER_2_BASEपूर्ण,
	.width		= 64,
पूर्ण;

अटल काष्ठा sp804_clkevt sp804_clkevt[NR_TIMERS];

अटल दीर्घ __init sp804_get_घड़ी_rate(काष्ठा clk *clk, स्थिर अक्षर *name)
अणु
	पूर्णांक err;

	अगर (!clk)
		clk = clk_get_sys("sp804", name);
	अगर (IS_ERR(clk)) अणु
		pr_err("%s clock not found: %ld\n", name, PTR_ERR(clk));
		वापस PTR_ERR(clk);
	पूर्ण

	err = clk_prepare_enable(clk);
	अगर (err) अणु
		pr_err("clock failed to enable: %d\n", err);
		clk_put(clk);
		वापस err;
	पूर्ण

	वापस clk_get_rate(clk);
पूर्ण

अटल काष्ठा sp804_clkevt * __init sp804_clkevt_get(व्योम __iomem *base)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NR_TIMERS; i++) अणु
		अगर (sp804_clkevt[i].base == base)
			वापस &sp804_clkevt[i];
	पूर्ण

	/* It's impossible to reach here */
	WARN_ON(1);

	वापस शून्य;
पूर्ण

अटल काष्ठा sp804_clkevt *sched_clkevt;

अटल u64 notrace sp804_पढ़ो(व्योम)
अणु
	वापस ~पढ़ोl_relaxed(sched_clkevt->value);
पूर्ण

अटल पूर्णांक __init sp804_घड़ीsource_and_sched_घड़ी_init(व्योम __iomem *base,
							 स्थिर अक्षर *name,
							 काष्ठा clk *clk,
							 पूर्णांक use_sched_घड़ी)
अणु
	दीर्घ rate;
	काष्ठा sp804_clkevt *clkevt;

	rate = sp804_get_घड़ी_rate(clk, name);
	अगर (rate < 0)
		वापस -EINVAL;

	clkevt = sp804_clkevt_get(base);

	ग_लिखोl(0, clkevt->ctrl);
	ग_लिखोl(0xffffffff, clkevt->load);
	ग_लिखोl(0xffffffff, clkevt->value);
	अगर (clkevt->width == 64) अणु
		ग_लिखोl(0xffffffff, clkevt->load_h);
		ग_लिखोl(0xffffffff, clkevt->value_h);
	पूर्ण
	ग_लिखोl(TIMER_CTRL_32BIT | TIMER_CTRL_ENABLE | TIMER_CTRL_PERIODIC,
		clkevt->ctrl);

	घड़ीsource_mmio_init(clkevt->value, name,
		rate, 200, 32, घड़ीsource_mmio_पढ़ोl_करोwn);

	अगर (use_sched_घड़ी) अणु
		sched_clkevt = clkevt;
		sched_घड़ी_रेजिस्टर(sp804_पढ़ो, 32, rate);
	पूर्ण

	वापस 0;
पूर्ण


अटल काष्ठा sp804_clkevt *common_clkevt;

/*
 * IRQ handler क्रम the समयr
 */
अटल irqवापस_t sp804_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = dev_id;

	/* clear the पूर्णांकerrupt */
	ग_लिखोl(1, common_clkevt->पूर्णांकclr);

	evt->event_handler(evt);

	वापस IRQ_HANDLED;
पूर्ण

अटल अंतरभूत व्योम समयr_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	ग_लिखोl(0, common_clkevt->ctrl);
पूर्ण

अटल पूर्णांक sp804_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	समयr_shutकरोwn(evt);
	वापस 0;
पूर्ण

अटल पूर्णांक sp804_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	अचिन्हित दीर्घ ctrl = TIMER_CTRL_32BIT | TIMER_CTRL_IE |
			     TIMER_CTRL_PERIODIC | TIMER_CTRL_ENABLE;

	समयr_shutकरोwn(evt);
	ग_लिखोl(common_clkevt->reload, common_clkevt->load);
	ग_लिखोl(ctrl, common_clkevt->ctrl);
	वापस 0;
पूर्ण

अटल पूर्णांक sp804_set_next_event(अचिन्हित दीर्घ next,
	काष्ठा घड़ी_event_device *evt)
अणु
	अचिन्हित दीर्घ ctrl = TIMER_CTRL_32BIT | TIMER_CTRL_IE |
			     TIMER_CTRL_ONESHOT | TIMER_CTRL_ENABLE;

	ग_लिखोl(next, common_clkevt->load);
	ग_लिखोl(ctrl, common_clkevt->ctrl);

	वापस 0;
पूर्ण

अटल काष्ठा घड़ी_event_device sp804_घड़ीevent = अणु
	.features		= CLOCK_EVT_FEAT_PERIODIC |
				  CLOCK_EVT_FEAT_ONESHOT |
				  CLOCK_EVT_FEAT_DYNIRQ,
	.set_state_shutकरोwn	= sp804_shutकरोwn,
	.set_state_periodic	= sp804_set_periodic,
	.set_state_oneshot	= sp804_shutकरोwn,
	.tick_resume		= sp804_shutकरोwn,
	.set_next_event		= sp804_set_next_event,
	.rating			= 300,
पूर्ण;

अटल पूर्णांक __init sp804_घड़ीevents_init(व्योम __iomem *base, अचिन्हित पूर्णांक irq,
					 काष्ठा clk *clk, स्थिर अक्षर *name)
अणु
	काष्ठा घड़ी_event_device *evt = &sp804_घड़ीevent;
	दीर्घ rate;

	rate = sp804_get_घड़ी_rate(clk, name);
	अगर (rate < 0)
		वापस -EINVAL;

	common_clkevt = sp804_clkevt_get(base);
	common_clkevt->reload = DIV_ROUND_CLOSEST(rate, HZ);
	evt->name = name;
	evt->irq = irq;
	evt->cpumask = cpu_possible_mask;

	ग_लिखोl(0, common_clkevt->ctrl);

	अगर (request_irq(irq, sp804_समयr_पूर्णांकerrupt, IRQF_TIMER | IRQF_IRQPOLL,
			"timer", &sp804_घड़ीevent))
		pr_err("request_irq() failed\n");
	घड़ीevents_config_and_रेजिस्टर(evt, rate, 0xf, 0xffffffff);

	वापस 0;
पूर्ण

अटल व्योम __init sp804_clkevt_init(काष्ठा sp804_समयr *समयr, व्योम __iomem *base)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NR_TIMERS; i++) अणु
		व्योम __iomem *समयr_base;
		काष्ठा sp804_clkevt *clkevt;

		समयr_base = base + समयr->समयr_base[i];
		clkevt = &sp804_clkevt[i];
		clkevt->base	= समयr_base;
		clkevt->load	= समयr_base + समयr->load;
		clkevt->load_h	= समयr_base + समयr->load_h;
		clkevt->value	= समयr_base + समयr->value;
		clkevt->value_h	= समयr_base + समयr->value_h;
		clkevt->ctrl	= समयr_base + समयr->ctrl;
		clkevt->पूर्णांकclr	= समयr_base + समयr->पूर्णांकclr;
		clkevt->width	= समयr->width;
	पूर्ण
पूर्ण

अटल पूर्णांक __init sp804_of_init(काष्ठा device_node *np, काष्ठा sp804_समयr *समयr)
अणु
	अटल bool initialized = false;
	व्योम __iomem *base;
	व्योम __iomem *समयr1_base;
	व्योम __iomem *समयr2_base;
	पूर्णांक irq, ret = -EINVAL;
	u32 irq_num = 0;
	काष्ठा clk *clk1, *clk2;
	स्थिर अक्षर *name = of_get_property(np, "compatible", शून्य);

	base = of_iomap(np, 0);
	अगर (!base)
		वापस -ENXIO;

	समयr1_base = base + समयr->समयr_base[0];
	समयr2_base = base + समयr->समयr_base[1];

	/* Ensure समयrs are disabled */
	ग_लिखोl(0, समयr1_base + समयr->ctrl);
	ग_लिखोl(0, समयr2_base + समयr->ctrl);

	अगर (initialized || !of_device_is_available(np)) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	clk1 = of_clk_get(np, 0);
	अगर (IS_ERR(clk1))
		clk1 = शून्य;

	/* Get the 2nd घड़ी अगर the समयr has 3 समयr घड़ीs */
	अगर (of_clk_get_parent_count(np) == 3) अणु
		clk2 = of_clk_get(np, 1);
		अगर (IS_ERR(clk2)) अणु
			pr_err("%pOFn clock not found: %d\n", np,
				(पूर्णांक)PTR_ERR(clk2));
			clk2 = शून्य;
		पूर्ण
	पूर्ण अन्यथा
		clk2 = clk1;

	irq = irq_of_parse_and_map(np, 0);
	अगर (irq <= 0)
		जाओ err;

	sp804_clkevt_init(समयr, base);

	of_property_पढ़ो_u32(np, "arm,sp804-has-irq", &irq_num);
	अगर (irq_num == 2) अणु

		ret = sp804_घड़ीevents_init(समयr2_base, irq, clk2, name);
		अगर (ret)
			जाओ err;

		ret = sp804_घड़ीsource_and_sched_घड़ी_init(समयr1_base,
							     name, clk1, 1);
		अगर (ret)
			जाओ err;
	पूर्ण अन्यथा अणु

		ret = sp804_घड़ीevents_init(समयr1_base, irq, clk1, name);
		अगर (ret)
			जाओ err;

		ret = sp804_घड़ीsource_and_sched_घड़ी_init(समयr2_base,
							     name, clk2, 1);
		अगर (ret)
			जाओ err;
	पूर्ण
	initialized = true;

	वापस 0;
err:
	iounmap(base);
	वापस ret;
पूर्ण

अटल पूर्णांक __init arm_sp804_of_init(काष्ठा device_node *np)
अणु
	वापस sp804_of_init(np, &arm_sp804_समयr);
पूर्ण
TIMER_OF_DECLARE(sp804, "arm,sp804", arm_sp804_of_init);

अटल पूर्णांक __init hisi_sp804_of_init(काष्ठा device_node *np)
अणु
	वापस sp804_of_init(np, &hisi_sp804_समयr);
पूर्ण
TIMER_OF_DECLARE(hisi_sp804, "hisilicon,sp804", hisi_sp804_of_init);

अटल पूर्णांक __init पूर्णांकegrator_cp_of_init(काष्ठा device_node *np)
अणु
	अटल पूर्णांक init_count = 0;
	व्योम __iomem *base;
	पूर्णांक irq, ret = -EINVAL;
	स्थिर अक्षर *name = of_get_property(np, "compatible", शून्य);
	काष्ठा clk *clk;

	base = of_iomap(np, 0);
	अगर (!base) अणु
		pr_err("Failed to iomap\n");
		वापस -ENXIO;
	पूर्ण

	clk = of_clk_get(np, 0);
	अगर (IS_ERR(clk)) अणु
		pr_err("Failed to get clock\n");
		वापस PTR_ERR(clk);
	पूर्ण

	/* Ensure समयr is disabled */
	ग_लिखोl(0, base + arm_sp804_समयr.ctrl);

	अगर (init_count == 2 || !of_device_is_available(np))
		जाओ err;

	sp804_clkevt_init(&arm_sp804_समयr, base);

	अगर (!init_count) अणु
		ret = sp804_घड़ीsource_and_sched_घड़ी_init(base,
							     name, clk, 0);
		अगर (ret)
			जाओ err;
	पूर्ण अन्यथा अणु
		irq = irq_of_parse_and_map(np, 0);
		अगर (irq <= 0)
			जाओ err;

		ret = sp804_घड़ीevents_init(base, irq, clk, name);
		अगर (ret)
			जाओ err;
	पूर्ण

	init_count++;
	वापस 0;
err:
	iounmap(base);
	वापस ret;
पूर्ण
TIMER_OF_DECLARE(पूर्णांकcp, "arm,integrator-cp-timer", पूर्णांकegrator_cp_of_init);
