<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2007 Google, Inc.
 * Copyright (c) 2009-2012,2014, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/घड़ीsource.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/cpu.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/sched_घड़ी.h>

#समावेश <यंत्र/delay.h>

#घोषणा TIMER_MATCH_VAL			0x0000
#घोषणा TIMER_COUNT_VAL			0x0004
#घोषणा TIMER_ENABLE			0x0008
#घोषणा TIMER_ENABLE_CLR_ON_MATCH_EN	BIT(1)
#घोषणा TIMER_ENABLE_EN			BIT(0)
#घोषणा TIMER_CLEAR			0x000C
#घोषणा DGT_CLK_CTL			0x10
#घोषणा DGT_CLK_CTL_DIV_4		0x3
#घोषणा TIMER_STS_GPT0_CLR_PEND		BIT(10)

#घोषणा GPT_HZ 32768

अटल व्योम __iomem *event_base;
अटल व्योम __iomem *sts_base;

अटल irqवापस_t msm_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = dev_id;
	/* Stop the समयr tick */
	अगर (घड़ीevent_state_oneshot(evt)) अणु
		u32 ctrl = पढ़ोl_relaxed(event_base + TIMER_ENABLE);
		ctrl &= ~TIMER_ENABLE_EN;
		ग_लिखोl_relaxed(ctrl, event_base + TIMER_ENABLE);
	पूर्ण
	evt->event_handler(evt);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक msm_समयr_set_next_event(अचिन्हित दीर्घ cycles,
				    काष्ठा घड़ी_event_device *evt)
अणु
	u32 ctrl = पढ़ोl_relaxed(event_base + TIMER_ENABLE);

	ctrl &= ~TIMER_ENABLE_EN;
	ग_लिखोl_relaxed(ctrl, event_base + TIMER_ENABLE);

	ग_लिखोl_relaxed(ctrl, event_base + TIMER_CLEAR);
	ग_लिखोl_relaxed(cycles, event_base + TIMER_MATCH_VAL);

	अगर (sts_base)
		जबतक (पढ़ोl_relaxed(sts_base) & TIMER_STS_GPT0_CLR_PEND)
			cpu_relax();

	ग_लिखोl_relaxed(ctrl | TIMER_ENABLE_EN, event_base + TIMER_ENABLE);
	वापस 0;
पूर्ण

अटल पूर्णांक msm_समयr_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	u32 ctrl;

	ctrl = पढ़ोl_relaxed(event_base + TIMER_ENABLE);
	ctrl &= ~(TIMER_ENABLE_EN | TIMER_ENABLE_CLR_ON_MATCH_EN);
	ग_लिखोl_relaxed(ctrl, event_base + TIMER_ENABLE);
	वापस 0;
पूर्ण

अटल काष्ठा घड़ी_event_device __percpu *msm_evt;

अटल व्योम __iomem *source_base;

अटल notrace u64 msm_पढ़ो_समयr_count(काष्ठा घड़ीsource *cs)
अणु
	वापस पढ़ोl_relaxed(source_base + TIMER_COUNT_VAL);
पूर्ण

अटल काष्ठा घड़ीsource msm_घड़ीsource = अणु
	.name	= "dg_timer",
	.rating	= 300,
	.पढ़ो	= msm_पढ़ो_समयr_count,
	.mask	= CLOCKSOURCE_MASK(32),
	.flags	= CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

अटल पूर्णांक msm_समयr_irq;
अटल पूर्णांक msm_समयr_has_ppi;

अटल पूर्णांक msm_local_समयr_starting_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा घड़ी_event_device *evt = per_cpu_ptr(msm_evt, cpu);
	पूर्णांक err;

	evt->irq = msm_समयr_irq;
	evt->name = "msm_timer";
	evt->features = CLOCK_EVT_FEAT_ONESHOT;
	evt->rating = 200;
	evt->set_state_shutकरोwn = msm_समयr_shutकरोwn;
	evt->set_state_oneshot = msm_समयr_shutकरोwn;
	evt->tick_resume = msm_समयr_shutकरोwn;
	evt->set_next_event = msm_समयr_set_next_event;
	evt->cpumask = cpumask_of(cpu);

	घड़ीevents_config_and_रेजिस्टर(evt, GPT_HZ, 4, 0xffffffff);

	अगर (msm_समयr_has_ppi) अणु
		enable_percpu_irq(evt->irq, IRQ_TYPE_EDGE_RISING);
	पूर्ण अन्यथा अणु
		err = request_irq(evt->irq, msm_समयr_पूर्णांकerrupt,
				IRQF_TIMER | IRQF_NOBALANCING |
				IRQF_TRIGGER_RISING, "gp_timer", evt);
		अगर (err)
			pr_err("request_irq failed\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक msm_local_समयr_dying_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा घड़ी_event_device *evt = per_cpu_ptr(msm_evt, cpu);

	evt->set_state_shutकरोwn(evt);
	disable_percpu_irq(evt->irq);
	वापस 0;
पूर्ण

अटल u64 notrace msm_sched_घड़ी_पढ़ो(व्योम)
अणु
	वापस msm_घड़ीsource.पढ़ो(&msm_घड़ीsource);
पूर्ण

अटल अचिन्हित दीर्घ msm_पढ़ो_current_समयr(व्योम)
अणु
	वापस msm_घड़ीsource.पढ़ो(&msm_घड़ीsource);
पूर्ण

अटल काष्ठा delay_समयr msm_delay_समयr = अणु
	.पढ़ो_current_समयr = msm_पढ़ो_current_समयr,
पूर्ण;

अटल पूर्णांक __init msm_समयr_init(u32 dgt_hz, पूर्णांक sched_bits, पूर्णांक irq,
				  bool percpu)
अणु
	काष्ठा घड़ीsource *cs = &msm_घड़ीsource;
	पूर्णांक res = 0;

	msm_समयr_irq = irq;
	msm_समयr_has_ppi = percpu;

	msm_evt = alloc_percpu(काष्ठा घड़ी_event_device);
	अगर (!msm_evt) अणु
		pr_err("memory allocation failed for clockevents\n");
		जाओ err;
	पूर्ण

	अगर (percpu)
		res = request_percpu_irq(irq, msm_समयr_पूर्णांकerrupt,
					 "gp_timer", msm_evt);

	अगर (res) अणु
		pr_err("request_percpu_irq failed\n");
	पूर्ण अन्यथा अणु
		/* Install and invoke hotplug callbacks */
		res = cpuhp_setup_state(CPUHP_AP_QCOM_TIMER_STARTING,
					"clockevents/qcom/timer:starting",
					msm_local_समयr_starting_cpu,
					msm_local_समयr_dying_cpu);
		अगर (res) अणु
			मुक्त_percpu_irq(irq, msm_evt);
			जाओ err;
		पूर्ण
	पूर्ण

err:
	ग_लिखोl_relaxed(TIMER_ENABLE_EN, source_base + TIMER_ENABLE);
	res = घड़ीsource_रेजिस्टर_hz(cs, dgt_hz);
	अगर (res)
		pr_err("clocksource_register failed\n");
	sched_घड़ी_रेजिस्टर(msm_sched_घड़ी_पढ़ो, sched_bits, dgt_hz);
	msm_delay_समयr.freq = dgt_hz;
	रेजिस्टर_current_समयr_delay(&msm_delay_समयr);

	वापस res;
पूर्ण

अटल पूर्णांक __init msm_dt_समयr_init(काष्ठा device_node *np)
अणु
	u32 freq;
	पूर्णांक irq, ret;
	काष्ठा resource res;
	u32 percpu_offset;
	व्योम __iomem *base;
	व्योम __iomem *cpu0_base;

	base = of_iomap(np, 0);
	अगर (!base) अणु
		pr_err("Failed to map event base\n");
		वापस -ENXIO;
	पूर्ण

	/* We use GPT0 क्रम the घड़ीevent */
	irq = irq_of_parse_and_map(np, 1);
	अगर (irq <= 0) अणु
		pr_err("Can't get irq\n");
		वापस -EINVAL;
	पूर्ण

	/* We use CPU0's DGT क्रम the घड़ीsource */
	अगर (of_property_पढ़ो_u32(np, "cpu-offset", &percpu_offset))
		percpu_offset = 0;

	ret = of_address_to_resource(np, 0, &res);
	अगर (ret) अणु
		pr_err("Failed to parse DGT resource\n");
		वापस ret;
	पूर्ण

	cpu0_base = ioremap(res.start + percpu_offset, resource_size(&res));
	अगर (!cpu0_base) अणु
		pr_err("Failed to map source base\n");
		वापस -EINVAL;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "clock-frequency", &freq)) अणु
		pr_err("Unknown frequency\n");
		वापस -EINVAL;
	पूर्ण

	event_base = base + 0x4;
	sts_base = base + 0x88;
	source_base = cpu0_base + 0x24;
	freq /= 4;
	ग_लिखोl_relaxed(DGT_CLK_CTL_DIV_4, source_base + DGT_CLK_CTL);

	वापस msm_समयr_init(freq, 32, irq, !!percpu_offset);
पूर्ण
TIMER_OF_DECLARE(kpss_समयr, "qcom,kpss-timer", msm_dt_समयr_init);
TIMER_OF_DECLARE(scss_समयr, "qcom,scss-timer", msm_dt_समयr_init);
