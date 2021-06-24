<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2010 Google, Inc.
 *
 * Author:
 *	Colin Cross <ccross@google.com>
 */

#घोषणा pr_fmt(fmt)	"tegra-timer: " fmt

#समावेश <linux/clk.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/percpu.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/समय.स>

#समावेश "timer-of.h"

#घोषणा RTC_SECONDS		0x08
#घोषणा RTC_SHADOW_SECONDS	0x0c
#घोषणा RTC_MILLISECONDS	0x10

#घोषणा TIMERUS_CNTR_1US	0x10
#घोषणा TIMERUS_USEC_CFG	0x14
#घोषणा TIMERUS_CNTR_FREEZE	0x4c

#घोषणा TIMER_PTV		0x0
#घोषणा TIMER_PTV_EN		BIT(31)
#घोषणा TIMER_PTV_PER		BIT(30)
#घोषणा TIMER_PCR		0x4
#घोषणा TIMER_PCR_INTR_CLR	BIT(30)

#घोषणा TIMER1_BASE		0x00
#घोषणा TIMER2_BASE		0x08
#घोषणा TIMER3_BASE		0x50
#घोषणा TIMER4_BASE		0x58
#घोषणा TIMER10_BASE		0x90

#घोषणा TIMER1_IRQ_IDX		0
#घोषणा TIMER10_IRQ_IDX		10

#घोषणा TIMER_1MHz		1000000

अटल u32 usec_config;
अटल व्योम __iomem *समयr_reg_base;

अटल पूर्णांक tegra_समयr_set_next_event(अचिन्हित दीर्घ cycles,
				      काष्ठा घड़ी_event_device *evt)
अणु
	व्योम __iomem *reg_base = समयr_of_base(to_समयr_of(evt));

	/*
	 * Tegra's समयr uses n+1 scheme क्रम the counter, i.e. समयr will
	 * fire after one tick अगर 0 is loaded.
	 *
	 * The minimum and maximum numbers of oneshot ticks are defined
	 * by घड़ीevents_config_and_रेजिस्टर(1, 0x1fffffff + 1) invocation
	 * below in the code. Hence the cycles (ticks) can't be outside of
	 * a range supportable by hardware.
	 */
	ग_लिखोl_relaxed(TIMER_PTV_EN | (cycles - 1), reg_base + TIMER_PTV);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_समयr_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	व्योम __iomem *reg_base = समयr_of_base(to_समयr_of(evt));

	ग_लिखोl_relaxed(0, reg_base + TIMER_PTV);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_समयr_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	व्योम __iomem *reg_base = समयr_of_base(to_समयr_of(evt));
	अचिन्हित दीर्घ period = समयr_of_period(to_समयr_of(evt));

	ग_लिखोl_relaxed(TIMER_PTV_EN | TIMER_PTV_PER | (period - 1),
		       reg_base + TIMER_PTV);

	वापस 0;
पूर्ण

अटल irqवापस_t tegra_समयr_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = dev_id;
	व्योम __iomem *reg_base = समयr_of_base(to_समयr_of(evt));

	ग_लिखोl_relaxed(TIMER_PCR_INTR_CLR, reg_base + TIMER_PCR);
	evt->event_handler(evt);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम tegra_समयr_suspend(काष्ठा घड़ी_event_device *evt)
अणु
	व्योम __iomem *reg_base = समयr_of_base(to_समयr_of(evt));

	ग_लिखोl_relaxed(TIMER_PCR_INTR_CLR, reg_base + TIMER_PCR);
पूर्ण

अटल व्योम tegra_समयr_resume(काष्ठा घड़ी_event_device *evt)
अणु
	ग_लिखोl_relaxed(usec_config, समयr_reg_base + TIMERUS_USEC_CFG);
पूर्ण

अटल DEFINE_PER_CPU(काष्ठा समयr_of, tegra_to) = अणु
	.flags = TIMER_OF_CLOCK | TIMER_OF_BASE,

	.clkevt = अणु
		.name = "tegra_timer",
		.features = CLOCK_EVT_FEAT_ONESHOT | CLOCK_EVT_FEAT_PERIODIC,
		.set_next_event = tegra_समयr_set_next_event,
		.set_state_shutकरोwn = tegra_समयr_shutकरोwn,
		.set_state_periodic = tegra_समयr_set_periodic,
		.set_state_oneshot = tegra_समयr_shutकरोwn,
		.tick_resume = tegra_समयr_shutकरोwn,
		.suspend = tegra_समयr_suspend,
		.resume = tegra_समयr_resume,
	पूर्ण,
पूर्ण;

अटल पूर्णांक tegra_समयr_setup(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा समयr_of *to = per_cpu_ptr(&tegra_to, cpu);

	ग_लिखोl_relaxed(0, समयr_of_base(to) + TIMER_PTV);
	ग_लिखोl_relaxed(TIMER_PCR_INTR_CLR, समयr_of_base(to) + TIMER_PCR);

	irq_क्रमce_affinity(to->clkevt.irq, cpumask_of(cpu));
	enable_irq(to->clkevt.irq);

	/*
	 * Tegra's समयr uses n+1 scheme क्रम the counter, i.e. समयr will
	 * fire after one tick अगर 0 is loaded and thus minimum number of
	 * ticks is 1. In result both of the घड़ीsource's tick limits are
	 * higher than a minimum and maximum that hardware रेजिस्टर can
	 * take by 1, this is then taken पूर्णांकo account by set_next_event
	 * callback.
	 */
	घड़ीevents_config_and_रेजिस्टर(&to->clkevt, समयr_of_rate(to),
					1, /* min */
					0x1fffffff + 1); /* max 29 bits + 1 */

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_समयr_stop(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा समयr_of *to = per_cpu_ptr(&tegra_to, cpu);

	to->clkevt.set_state_shutकरोwn(&to->clkevt);
	disable_irq_nosync(to->clkevt.irq);

	वापस 0;
पूर्ण

अटल u64 notrace tegra_पढ़ो_sched_घड़ी(व्योम)
अणु
	वापस पढ़ोl_relaxed(समयr_reg_base + TIMERUS_CNTR_1US);
पूर्ण

#अगर_घोषित CONFIG_ARM
अटल अचिन्हित दीर्घ tegra_delay_समयr_पढ़ो_counter_दीर्घ(व्योम)
अणु
	वापस पढ़ोl_relaxed(समयr_reg_base + TIMERUS_CNTR_1US);
पूर्ण

अटल काष्ठा delay_समयr tegra_delay_समयr = अणु
	.पढ़ो_current_समयr = tegra_delay_समयr_पढ़ो_counter_दीर्घ,
	.freq = TIMER_1MHz,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा समयr_of suspend_rtc_to = अणु
	.flags = TIMER_OF_BASE | TIMER_OF_CLOCK,
पूर्ण;

/*
 * tegra_rtc_पढ़ो - Reads the Tegra RTC रेजिस्टरs
 * Care must be taken that this function is not called जबतक the
 * tegra_rtc driver could be executing to aव्योम race conditions
 * on the RTC shaकरोw रेजिस्टर
 */
अटल u64 tegra_rtc_पढ़ो_ms(काष्ठा घड़ीsource *cs)
अणु
	व्योम __iomem *reg_base = समयr_of_base(&suspend_rtc_to);

	u32 ms = पढ़ोl_relaxed(reg_base + RTC_MILLISECONDS);
	u32 s = पढ़ोl_relaxed(reg_base + RTC_SHADOW_SECONDS);

	वापस (u64)s * MSEC_PER_SEC + ms;
पूर्ण

अटल काष्ठा घड़ीsource suspend_rtc_घड़ीsource = अणु
	.name	= "tegra_suspend_timer",
	.rating	= 200,
	.पढ़ो	= tegra_rtc_पढ़ो_ms,
	.mask	= CLOCKSOURCE_MASK(32),
	.flags	= CLOCK_SOURCE_IS_CONTINUOUS | CLOCK_SOURCE_SUSPEND_NONSTOP,
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक tegra_base_क्रम_cpu(पूर्णांक cpu, bool tegra20)
अणु
	अगर (tegra20) अणु
		चयन (cpu) अणु
		हाल 0:
			वापस TIMER1_BASE;
		हाल 1:
			वापस TIMER2_BASE;
		हाल 2:
			वापस TIMER3_BASE;
		शेष:
			वापस TIMER4_BASE;
		पूर्ण
	पूर्ण

	वापस TIMER10_BASE + cpu * 8;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक tegra_irq_idx_क्रम_cpu(पूर्णांक cpu, bool tegra20)
अणु
	अगर (tegra20)
		वापस TIMER1_IRQ_IDX + cpu;

	वापस TIMER10_IRQ_IDX + cpu;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ tegra_rate_क्रम_समयr(काष्ठा समयr_of *to,
						 bool tegra20)
अणु
	/*
	 * TIMER1-9 are fixed to 1MHz, TIMER10-13 are running off the
	 * parent घड़ी.
	 */
	अगर (tegra20)
		वापस TIMER_1MHz;

	वापस समयr_of_rate(to);
पूर्ण

अटल पूर्णांक __init tegra_init_समयr(काष्ठा device_node *np, bool tegra20,
				   पूर्णांक rating)
अणु
	काष्ठा समयr_of *to;
	पूर्णांक cpu, ret;

	to = this_cpu_ptr(&tegra_to);
	ret = समयr_of_init(np, to);
	अगर (ret)
		जाओ out;

	समयr_reg_base = समयr_of_base(to);

	/*
	 * Configure microsecond समयrs to have 1MHz घड़ी
	 * Config रेजिस्टर is 0xqqww, where qq is "dividend", ww is "divisor"
	 * Uses n+1 scheme
	 */
	चयन (समयr_of_rate(to)) अणु
	हाल 12000000:
		usec_config = 0x000b; /* (11+1)/(0+1) */
		अवरोध;
	हाल 12800000:
		usec_config = 0x043f; /* (63+1)/(4+1) */
		अवरोध;
	हाल 13000000:
		usec_config = 0x000c; /* (12+1)/(0+1) */
		अवरोध;
	हाल 16800000:
		usec_config = 0x0453; /* (83+1)/(4+1) */
		अवरोध;
	हाल 19200000:
		usec_config = 0x045f; /* (95+1)/(4+1) */
		अवरोध;
	हाल 26000000:
		usec_config = 0x0019; /* (25+1)/(0+1) */
		अवरोध;
	हाल 38400000:
		usec_config = 0x04bf; /* (191+1)/(4+1) */
		अवरोध;
	हाल 48000000:
		usec_config = 0x002f; /* (47+1)/(0+1) */
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ग_लिखोl_relaxed(usec_config, समयr_reg_base + TIMERUS_USEC_CFG);

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा समयr_of *cpu_to = per_cpu_ptr(&tegra_to, cpu);
		अचिन्हित दीर्घ flags = IRQF_TIMER | IRQF_NOBALANCING;
		अचिन्हित दीर्घ rate = tegra_rate_क्रम_समयr(to, tegra20);
		अचिन्हित पूर्णांक base = tegra_base_क्रम_cpu(cpu, tegra20);
		अचिन्हित पूर्णांक idx = tegra_irq_idx_क्रम_cpu(cpu, tegra20);
		अचिन्हित पूर्णांक irq = irq_of_parse_and_map(np, idx);

		अगर (!irq) अणु
			pr_err("failed to map irq for cpu%d\n", cpu);
			ret = -EINVAL;
			जाओ out_irq;
		पूर्ण

		cpu_to->clkevt.irq = irq;
		cpu_to->clkevt.rating = rating;
		cpu_to->clkevt.cpumask = cpumask_of(cpu);
		cpu_to->of_base.base = समयr_reg_base + base;
		cpu_to->of_clk.period = rate / HZ;
		cpu_to->of_clk.rate = rate;

		irq_set_status_flags(cpu_to->clkevt.irq, IRQ_NOAUTOEN);

		ret = request_irq(cpu_to->clkevt.irq, tegra_समयr_isr, flags,
				  cpu_to->clkevt.name, &cpu_to->clkevt);
		अगर (ret) अणु
			pr_err("failed to set up irq for cpu%d: %d\n",
			       cpu, ret);
			irq_dispose_mapping(cpu_to->clkevt.irq);
			cpu_to->clkevt.irq = 0;
			जाओ out_irq;
		पूर्ण
	पूर्ण

	sched_घड़ी_रेजिस्टर(tegra_पढ़ो_sched_घड़ी, 32, TIMER_1MHz);

	ret = घड़ीsource_mmio_init(समयr_reg_base + TIMERUS_CNTR_1US,
				    "timer_us", TIMER_1MHz, 300, 32,
				    घड़ीsource_mmio_पढ़ोl_up);
	अगर (ret)
		pr_err("failed to register clocksource: %d\n", ret);

#अगर_घोषित CONFIG_ARM
	रेजिस्टर_current_समयr_delay(&tegra_delay_समयr);
#पूर्ण_अगर

	ret = cpuhp_setup_state(CPUHP_AP_TEGRA_TIMER_STARTING,
				"AP_TEGRA_TIMER_STARTING", tegra_समयr_setup,
				tegra_समयr_stop);
	अगर (ret)
		pr_err("failed to set up cpu hp state: %d\n", ret);

	वापस ret;

out_irq:
	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा समयr_of *cpu_to;

		cpu_to = per_cpu_ptr(&tegra_to, cpu);
		अगर (cpu_to->clkevt.irq) अणु
			मुक्त_irq(cpu_to->clkevt.irq, &cpu_to->clkevt);
			irq_dispose_mapping(cpu_to->clkevt.irq);
		पूर्ण
	पूर्ण

	to->of_base.base = समयr_reg_base;
out:
	समयr_of_cleanup(to);

	वापस ret;
पूर्ण

अटल पूर्णांक __init tegra210_init_समयr(काष्ठा device_node *np)
अणु
	/*
	 * Arch-समयr can't survive across घातer cycle of CPU core and
	 * after CPUPORESET संकेत due to a प्रणाली design लघुcoming,
	 * hence tegra-समयr is more preferable on Tegra210.
	 */
	वापस tegra_init_समयr(np, false, 460);
पूर्ण
TIMER_OF_DECLARE(tegra210_समयr, "nvidia,tegra210-timer", tegra210_init_समयr);

अटल पूर्णांक __init tegra20_init_समयr(काष्ठा device_node *np)
अणु
	पूर्णांक rating;

	/*
	 * Tegra20 and Tegra30 have Cortex A9 CPU that has a TWD समयr,
	 * that समयr runs off the CPU घड़ी and hence is subjected to
	 * a jitter caused by DVFS घड़ी rate changes. Tegra-समयr is
	 * more preferable क्रम older Tegra's, जबतक later SoC generations
	 * have arch-समयr as a मुख्य per-CPU समयr and it is not affected
	 * by DVFS changes.
	 */
	अगर (of_machine_is_compatible("nvidia,tegra20") ||
	    of_machine_is_compatible("nvidia,tegra30"))
		rating = 460;
	अन्यथा
		rating = 330;

	वापस tegra_init_समयr(np, true, rating);
पूर्ण
TIMER_OF_DECLARE(tegra20_समयr, "nvidia,tegra20-timer", tegra20_init_समयr);

अटल पूर्णांक __init tegra20_init_rtc(काष्ठा device_node *np)
अणु
	पूर्णांक ret;

	ret = समयr_of_init(np, &suspend_rtc_to);
	अगर (ret)
		वापस ret;

	वापस घड़ीsource_रेजिस्टर_hz(&suspend_rtc_घड़ीsource, 1000);
पूर्ण
TIMER_OF_DECLARE(tegra20_rtc, "nvidia,tegra20-rtc", tegra20_init_rtc);
