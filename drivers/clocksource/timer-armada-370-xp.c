<शैली गुरु>
/*
 * Marvell Armada 370/XP SoC समयr handling.
 *
 * Copyright (C) 2012 Marvell
 *
 * Lior Amsalem <alior@marvell.com>
 * Gregory CLEMENT <gregory.clement@मुक्त-electrons.com>
 * Thomas Petazzoni <thomas.petazzoni@मुक्त-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 *
 * Timer 0 is used as मुक्त-running घड़ीsource, जबतक समयr 1 is
 * used as घड़ी_event_device.
 *
 * ---
 * Clocksource driver क्रम Armada 370 and Armada XP SoC.
 * This driver implements one compatible string क्रम each SoC, given
 * each has its own अक्षरacteristics:
 *
 *   * Armada 370 has no 25 MHz fixed समयr.
 *
 *   * Armada XP cannot work properly without such 25 MHz fixed समयr as
 *     करोing otherwise leads to using a घड़ीsource whose frequency varies
 *     when करोing cpufreq frequency changes.
 *
 * See Documentation/devicetree/bindings/समयr/marvell,armada-370-xp-समयr.txt
 */

#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/clk.h>
#समावेश <linux/cpu.h>
#समावेश <linux/समयr.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/percpu.h>
#समावेश <linux/syscore_ops.h>

#समावेश <यंत्र/delay.h>

/*
 * Timer block रेजिस्टरs.
 */
#घोषणा TIMER_CTRL_OFF		0x0000
#घोषणा  TIMER0_EN		 BIT(0)
#घोषणा  TIMER0_RELOAD_EN	 BIT(1)
#घोषणा  TIMER0_25MHZ            BIT(11)
#घोषणा  TIMER0_DIV(भाग)         ((भाग) << 19)
#घोषणा  TIMER1_EN		 BIT(2)
#घोषणा  TIMER1_RELOAD_EN	 BIT(3)
#घोषणा  TIMER1_25MHZ            BIT(12)
#घोषणा  TIMER1_DIV(भाग)         ((भाग) << 22)
#घोषणा TIMER_EVENTS_STATUS	0x0004
#घोषणा  TIMER0_CLR_MASK         (~0x1)
#घोषणा  TIMER1_CLR_MASK         (~0x100)
#घोषणा TIMER0_RELOAD_OFF	0x0010
#घोषणा TIMER0_VAL_OFF		0x0014
#घोषणा TIMER1_RELOAD_OFF	0x0018
#घोषणा TIMER1_VAL_OFF		0x001c

#घोषणा LCL_TIMER_EVENTS_STATUS	0x0028
/* Global समयrs are connected to the coherency fabric घड़ी, and the
   below भागider reduces their incrementing frequency. */
#घोषणा TIMER_DIVIDER_SHIFT     5
#घोषणा TIMER_DIVIDER           (1 << TIMER_DIVIDER_SHIFT)

/*
 * SoC-specअगरic data.
 */
अटल व्योम __iomem *समयr_base, *local_base;
अटल अचिन्हित पूर्णांक समयr_clk;
अटल bool समयr25Mhz = true;
अटल u32 enable_mask;

/*
 * Number of समयr ticks per jअगरfy.
 */
अटल u32 ticks_per_jअगरfy;

अटल काष्ठा घड़ी_event_device __percpu *armada_370_xp_evt;

अटल व्योम local_समयr_ctrl_clrset(u32 clr, u32 set)
अणु
	ग_लिखोl((पढ़ोl(local_base + TIMER_CTRL_OFF) & ~clr) | set,
		local_base + TIMER_CTRL_OFF);
पूर्ण

अटल u64 notrace armada_370_xp_पढ़ो_sched_घड़ी(व्योम)
अणु
	वापस ~पढ़ोl(समयr_base + TIMER0_VAL_OFF);
पूर्ण

/*
 * Clockevent handling.
 */
अटल पूर्णांक
armada_370_xp_clkevt_next_event(अचिन्हित दीर्घ delta,
				काष्ठा घड़ी_event_device *dev)
अणु
	/*
	 * Clear घड़ीevent समयr पूर्णांकerrupt.
	 */
	ग_लिखोl(TIMER0_CLR_MASK, local_base + LCL_TIMER_EVENTS_STATUS);

	/*
	 * Setup new घड़ीevent समयr value.
	 */
	ग_लिखोl(delta, local_base + TIMER0_VAL_OFF);

	/*
	 * Enable the समयr.
	 */
	local_समयr_ctrl_clrset(TIMER0_RELOAD_EN, enable_mask);
	वापस 0;
पूर्ण

अटल पूर्णांक armada_370_xp_clkevt_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	/*
	 * Disable समयr.
	 */
	local_समयr_ctrl_clrset(TIMER0_EN, 0);

	/*
	 * ACK pending समयr पूर्णांकerrupt.
	 */
	ग_लिखोl(TIMER0_CLR_MASK, local_base + LCL_TIMER_EVENTS_STATUS);
	वापस 0;
पूर्ण

अटल पूर्णांक armada_370_xp_clkevt_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	/*
	 * Setup समयr to fire at 1/HZ पूर्णांकervals.
	 */
	ग_लिखोl(ticks_per_jअगरfy - 1, local_base + TIMER0_RELOAD_OFF);
	ग_लिखोl(ticks_per_jअगरfy - 1, local_base + TIMER0_VAL_OFF);

	/*
	 * Enable समयr.
	 */
	local_समयr_ctrl_clrset(0, TIMER0_RELOAD_EN | enable_mask);
	वापस 0;
पूर्ण

अटल पूर्णांक armada_370_xp_clkevt_irq;

अटल irqवापस_t armada_370_xp_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	/*
	 * ACK समयr पूर्णांकerrupt and call event handler.
	 */
	काष्ठा घड़ी_event_device *evt = dev_id;

	ग_लिखोl(TIMER0_CLR_MASK, local_base + LCL_TIMER_EVENTS_STATUS);
	evt->event_handler(evt);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Setup the local घड़ी events क्रम a CPU.
 */
अटल पूर्णांक armada_370_xp_समयr_starting_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा घड़ी_event_device *evt = per_cpu_ptr(armada_370_xp_evt, cpu);
	u32 clr = 0, set = 0;

	अगर (समयr25Mhz)
		set = TIMER0_25MHZ;
	अन्यथा
		clr = TIMER0_25MHZ;
	local_समयr_ctrl_clrset(clr, set);

	evt->name		= "armada_370_xp_per_cpu_tick";
	evt->features		= CLOCK_EVT_FEAT_ONESHOT |
				  CLOCK_EVT_FEAT_PERIODIC;
	evt->shअगरt		= 32;
	evt->rating		= 300;
	evt->set_next_event	= armada_370_xp_clkevt_next_event;
	evt->set_state_shutकरोwn	= armada_370_xp_clkevt_shutकरोwn;
	evt->set_state_periodic	= armada_370_xp_clkevt_set_periodic;
	evt->set_state_oneshot	= armada_370_xp_clkevt_shutकरोwn;
	evt->tick_resume	= armada_370_xp_clkevt_shutकरोwn;
	evt->irq		= armada_370_xp_clkevt_irq;
	evt->cpumask		= cpumask_of(cpu);

	घड़ीevents_config_and_रेजिस्टर(evt, समयr_clk, 1, 0xfffffffe);
	enable_percpu_irq(evt->irq, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक armada_370_xp_समयr_dying_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा घड़ी_event_device *evt = per_cpu_ptr(armada_370_xp_evt, cpu);

	evt->set_state_shutकरोwn(evt);
	disable_percpu_irq(evt->irq);
	वापस 0;
पूर्ण

अटल u32 समयr0_ctrl_reg, समयr0_local_ctrl_reg;

अटल पूर्णांक armada_370_xp_समयr_suspend(व्योम)
अणु
	समयr0_ctrl_reg = पढ़ोl(समयr_base + TIMER_CTRL_OFF);
	समयr0_local_ctrl_reg = पढ़ोl(local_base + TIMER_CTRL_OFF);
	वापस 0;
पूर्ण

अटल व्योम armada_370_xp_समयr_resume(व्योम)
अणु
	ग_लिखोl(0xffffffff, समयr_base + TIMER0_VAL_OFF);
	ग_लिखोl(0xffffffff, समयr_base + TIMER0_RELOAD_OFF);
	ग_लिखोl(समयr0_ctrl_reg, समयr_base + TIMER_CTRL_OFF);
	ग_लिखोl(समयr0_local_ctrl_reg, local_base + TIMER_CTRL_OFF);
पूर्ण

अटल काष्ठा syscore_ops armada_370_xp_समयr_syscore_ops = अणु
	.suspend	= armada_370_xp_समयr_suspend,
	.resume		= armada_370_xp_समयr_resume,
पूर्ण;

अटल अचिन्हित दीर्घ armada_370_delay_समयr_पढ़ो(व्योम)
अणु
	वापस ~पढ़ोl(समयr_base + TIMER0_VAL_OFF);
पूर्ण

अटल काष्ठा delay_समयr armada_370_delay_समयr = अणु
	.पढ़ो_current_समयr = armada_370_delay_समयr_पढ़ो,
पूर्ण;

अटल पूर्णांक __init armada_370_xp_समयr_common_init(काष्ठा device_node *np)
अणु
	u32 clr = 0, set = 0;
	पूर्णांक res;

	समयr_base = of_iomap(np, 0);
	अगर (!समयr_base) अणु
		pr_err("Failed to iomap\n");
		वापस -ENXIO;
	पूर्ण

	local_base = of_iomap(np, 1);
	अगर (!local_base) अणु
		pr_err("Failed to iomap\n");
		वापस -ENXIO;
	पूर्ण

	अगर (समयr25Mhz) अणु
		set = TIMER0_25MHZ;		
		enable_mask = TIMER0_EN;
	पूर्ण अन्यथा अणु
		clr = TIMER0_25MHZ;
		enable_mask = TIMER0_EN | TIMER0_DIV(TIMER_DIVIDER_SHIFT);
	पूर्ण
	atomic_io_modअगरy(समयr_base + TIMER_CTRL_OFF, clr | set, set);
	local_समयr_ctrl_clrset(clr, set);

	/*
	 * We use समयr 0 as घड़ीsource, and निजी(local) समयr 0
	 * क्रम घड़ीevents
	 */
	armada_370_xp_clkevt_irq = irq_of_parse_and_map(np, 4);

	ticks_per_jअगरfy = (समयr_clk + HZ / 2) / HZ;

	/*
	 * Setup मुक्त-running घड़ीsource समयr (पूर्णांकerrupts
	 * disabled).
	 */
	ग_लिखोl(0xffffffff, समयr_base + TIMER0_VAL_OFF);
	ग_लिखोl(0xffffffff, समयr_base + TIMER0_RELOAD_OFF);

	atomic_io_modअगरy(समयr_base + TIMER_CTRL_OFF,
		TIMER0_RELOAD_EN | enable_mask,
		TIMER0_RELOAD_EN | enable_mask);

	armada_370_delay_समयr.freq = समयr_clk;
	रेजिस्टर_current_समयr_delay(&armada_370_delay_समयr);

	/*
	 * Set scale and समयr क्रम sched_घड़ी.
	 */
	sched_घड़ी_रेजिस्टर(armada_370_xp_पढ़ो_sched_घड़ी, 32, समयr_clk);

	res = घड़ीsource_mmio_init(समयr_base + TIMER0_VAL_OFF,
				    "armada_370_xp_clocksource",
				    समयr_clk, 300, 32, घड़ीsource_mmio_पढ़ोl_करोwn);
	अगर (res) अणु
		pr_err("Failed to initialize clocksource mmio\n");
		वापस res;
	पूर्ण

	armada_370_xp_evt = alloc_percpu(काष्ठा घड़ी_event_device);
	अगर (!armada_370_xp_evt)
		वापस -ENOMEM;

	/*
	 * Setup घड़ीevent समयr (पूर्णांकerrupt-driven).
	 */
	res = request_percpu_irq(armada_370_xp_clkevt_irq,
				armada_370_xp_समयr_पूर्णांकerrupt,
				"armada_370_xp_per_cpu_tick",
				armada_370_xp_evt);
	/* Immediately configure the समयr on the boot CPU */
	अगर (res) अणु
		pr_err("Failed to request percpu irq\n");
		वापस res;
	पूर्ण

	res = cpuhp_setup_state(CPUHP_AP_ARMADA_TIMER_STARTING,
				"clockevents/armada:starting",
				armada_370_xp_समयr_starting_cpu,
				armada_370_xp_समयr_dying_cpu);
	अगर (res) अणु
		pr_err("Failed to setup hotplug state and timer\n");
		वापस res;
	पूर्ण

	रेजिस्टर_syscore_ops(&armada_370_xp_समयr_syscore_ops);
	
	वापस 0;
पूर्ण

अटल पूर्णांक __init armada_xp_समयr_init(काष्ठा device_node *np)
अणु
	काष्ठा clk *clk = of_clk_get_by_name(np, "fixed");
	पूर्णांक ret;

	अगर (IS_ERR(clk)) अणु
		pr_err("Failed to get clock\n");
		वापस PTR_ERR(clk);
	पूर्ण

	ret = clk_prepare_enable(clk);
	अगर (ret)
		वापस ret;

	समयr_clk = clk_get_rate(clk);

	वापस armada_370_xp_समयr_common_init(np);
पूर्ण
TIMER_OF_DECLARE(armada_xp, "marvell,armada-xp-timer",
		       armada_xp_समयr_init);

अटल पूर्णांक __init armada_375_समयr_init(काष्ठा device_node *np)
अणु
	काष्ठा clk *clk;
	पूर्णांक ret;

	clk = of_clk_get_by_name(np, "fixed");
	अगर (!IS_ERR(clk)) अणु
		ret = clk_prepare_enable(clk);
		अगर (ret)
			वापस ret;
		समयr_clk = clk_get_rate(clk);
	पूर्ण अन्यथा अणु

		/*
		 * This fallback is required in order to retain proper
		 * devicetree backwards compatibility.
		 */
		clk = of_clk_get(np, 0);

		/* Must have at least a घड़ी */
		अगर (IS_ERR(clk)) अणु
			pr_err("Failed to get clock\n");
			वापस PTR_ERR(clk);
		पूर्ण

		ret = clk_prepare_enable(clk);
		अगर (ret)
			वापस ret;

		समयr_clk = clk_get_rate(clk) / TIMER_DIVIDER;
		समयr25Mhz = false;
	पूर्ण

	वापस armada_370_xp_समयr_common_init(np);
पूर्ण
TIMER_OF_DECLARE(armada_375, "marvell,armada-375-timer",
		       armada_375_समयr_init);

अटल पूर्णांक __init armada_370_समयr_init(काष्ठा device_node *np)
अणु
	काष्ठा clk *clk;
	पूर्णांक ret;

	clk = of_clk_get(np, 0);
	अगर (IS_ERR(clk)) अणु
		pr_err("Failed to get clock\n");
		वापस PTR_ERR(clk);
	पूर्ण

	ret = clk_prepare_enable(clk);
	अगर (ret)
		वापस ret;

	समयr_clk = clk_get_rate(clk) / TIMER_DIVIDER;
	समयr25Mhz = false;

	वापस armada_370_xp_समयr_common_init(np);
पूर्ण
TIMER_OF_DECLARE(armada_370, "marvell,armada-370-timer",
		       armada_370_समयr_init);
