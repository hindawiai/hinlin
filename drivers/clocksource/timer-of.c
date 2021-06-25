<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2017, Linaro Ltd.  All rights reserved.
 *
 * Author: Daniel Lezcano <daniel.lezcano@linaro.org>
 */
#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/slab.h>

#समावेश "timer-of.h"

/**
 * समयr_of_irq_निकास - Release the पूर्णांकerrupt
 * @of_irq: an of_समयr_irq काष्ठाure poपूर्णांकer
 *
 * Free the irq resource
 */
अटल __init व्योम समयr_of_irq_निकास(काष्ठा of_समयr_irq *of_irq)
अणु
	काष्ठा समयr_of *to = container_of(of_irq, काष्ठा समयr_of, of_irq);

	काष्ठा घड़ी_event_device *clkevt = &to->clkevt;

	अगर (of_irq->percpu)
		मुक्त_percpu_irq(of_irq->irq, clkevt);
	अन्यथा
		मुक्त_irq(of_irq->irq, clkevt);
पूर्ण

/**
 * समयr_of_irq_init - Request the पूर्णांकerrupt
 * @np: a device tree node poपूर्णांकer
 * @of_irq: an of_समयr_irq काष्ठाure poपूर्णांकer
 *
 * Get the पूर्णांकerrupt number from the DT from its definition and
 * request it. The पूर्णांकerrupt is gotten by falling back the following way:
 *
 * - Get पूर्णांकerrupt number by name
 * - Get पूर्णांकerrupt number by index
 *
 * When the पूर्णांकerrupt is per CPU, 'request_percpu_irq()' is called,
 * otherwise 'request_irq()' is used.
 *
 * Returns 0 on success, < 0 otherwise
 */
अटल __init पूर्णांक समयr_of_irq_init(काष्ठा device_node *np,
				    काष्ठा of_समयr_irq *of_irq)
अणु
	पूर्णांक ret;
	काष्ठा समयr_of *to = container_of(of_irq, काष्ठा समयr_of, of_irq);
	काष्ठा घड़ी_event_device *clkevt = &to->clkevt;

	अगर (of_irq->name) अणु
		of_irq->irq = ret = of_irq_get_byname(np, of_irq->name);
		अगर (ret < 0) अणु
			pr_err("Failed to get interrupt %s for %pOF\n",
			       of_irq->name, np);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा	अणु
		of_irq->irq = irq_of_parse_and_map(np, of_irq->index);
	पूर्ण
	अगर (!of_irq->irq) अणु
		pr_err("Failed to map interrupt for %pOF\n", np);
		वापस -EINVAL;
	पूर्ण

	ret = of_irq->percpu ?
		request_percpu_irq(of_irq->irq, of_irq->handler,
				   np->full_name, clkevt) :
		request_irq(of_irq->irq, of_irq->handler,
			    of_irq->flags ? of_irq->flags : IRQF_TIMER,
			    np->full_name, clkevt);
	अगर (ret) अणु
		pr_err("Failed to request irq %d for %pOF\n", of_irq->irq, np);
		वापस ret;
	पूर्ण

	clkevt->irq = of_irq->irq;

	वापस 0;
पूर्ण

/**
 * समयr_of_clk_निकास - Release the घड़ी resources
 * @of_clk: a of_समयr_clk काष्ठाure poपूर्णांकer
 *
 * Disables and releases the refcount on the clk
 */
अटल __init व्योम समयr_of_clk_निकास(काष्ठा of_समयr_clk *of_clk)
अणु
	of_clk->rate = 0;
	clk_disable_unprepare(of_clk->clk);
	clk_put(of_clk->clk);
पूर्ण

/**
 * समयr_of_clk_init - Initialize the घड़ी resources
 * @np: a device tree node poपूर्णांकer
 * @of_clk: a of_समयr_clk काष्ठाure poपूर्णांकer
 *
 * Get the घड़ी by name or by index, enable it and get the rate
 *
 * Returns 0 on success, < 0 otherwise
 */
अटल __init पूर्णांक समयr_of_clk_init(काष्ठा device_node *np,
				    काष्ठा of_समयr_clk *of_clk)
अणु
	पूर्णांक ret;

	of_clk->clk = of_clk->name ? of_clk_get_by_name(np, of_clk->name) :
		of_clk_get(np, of_clk->index);
	अगर (IS_ERR(of_clk->clk)) अणु
		ret = PTR_ERR(of_clk->clk);
		अगर (ret != -EPROBE_DEFER)
			pr_err("Failed to get clock for %pOF\n", np);
		जाओ out;
	पूर्ण

	ret = clk_prepare_enable(of_clk->clk);
	अगर (ret) अणु
		pr_err("Failed for enable clock for %pOF\n", np);
		जाओ out_clk_put;
	पूर्ण

	of_clk->rate = clk_get_rate(of_clk->clk);
	अगर (!of_clk->rate) अणु
		ret = -EINVAL;
		pr_err("Failed to get clock rate for %pOF\n", np);
		जाओ out_clk_disable;
	पूर्ण

	of_clk->period = DIV_ROUND_UP(of_clk->rate, HZ);
out:
	वापस ret;

out_clk_disable:
	clk_disable_unprepare(of_clk->clk);
out_clk_put:
	clk_put(of_clk->clk);

	जाओ out;
पूर्ण

अटल __init व्योम समयr_of_base_निकास(काष्ठा of_समयr_base *of_base)
अणु
	iounmap(of_base->base);
पूर्ण

अटल __init पूर्णांक समयr_of_base_init(काष्ठा device_node *np,
				     काष्ठा of_समयr_base *of_base)
अणु
	of_base->base = of_base->name ?
		of_io_request_and_map(np, of_base->index, of_base->name) :
		of_iomap(np, of_base->index);
	अगर (IS_ERR(of_base->base)) अणु
		pr_err("Failed to iomap (%s)\n", of_base->name);
		वापस PTR_ERR(of_base->base);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक __init समयr_of_init(काष्ठा device_node *np, काष्ठा समयr_of *to)
अणु
	पूर्णांक ret = -EINVAL;
	पूर्णांक flags = 0;

	अगर (to->flags & TIMER_OF_BASE) अणु
		ret = समयr_of_base_init(np, &to->of_base);
		अगर (ret)
			जाओ out_fail;
		flags |= TIMER_OF_BASE;
	पूर्ण

	अगर (to->flags & TIMER_OF_CLOCK) अणु
		ret = समयr_of_clk_init(np, &to->of_clk);
		अगर (ret)
			जाओ out_fail;
		flags |= TIMER_OF_CLOCK;
	पूर्ण

	अगर (to->flags & TIMER_OF_IRQ) अणु
		ret = समयr_of_irq_init(np, &to->of_irq);
		अगर (ret)
			जाओ out_fail;
		flags |= TIMER_OF_IRQ;
	पूर्ण

	अगर (!to->clkevt.name)
		to->clkevt.name = np->full_name;

	to->np = np;

	वापस ret;

out_fail:
	अगर (flags & TIMER_OF_IRQ)
		समयr_of_irq_निकास(&to->of_irq);

	अगर (flags & TIMER_OF_CLOCK)
		समयr_of_clk_निकास(&to->of_clk);

	अगर (flags & TIMER_OF_BASE)
		समयr_of_base_निकास(&to->of_base);
	वापस ret;
पूर्ण

/**
 * समयr_of_cleanup - release समयr_of resources
 * @to: समयr_of काष्ठाure
 *
 * Release the resources that has been used in समयr_of_init().
 * This function should be called in init error हालs
 */
व्योम __init समयr_of_cleanup(काष्ठा समयr_of *to)
अणु
	अगर (to->flags & TIMER_OF_IRQ)
		समयr_of_irq_निकास(&to->of_irq);

	अगर (to->flags & TIMER_OF_CLOCK)
		समयr_of_clk_निकास(&to->of_clk);

	अगर (to->flags & TIMER_OF_BASE)
		समयr_of_base_निकास(&to->of_base);
पूर्ण
