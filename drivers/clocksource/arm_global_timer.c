<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/घड़ीsource/arm_global_समयr.c
 *
 * Copyright (C) 2013 STMicroelectronics (R&D) Limited.
 * Author: Stuart Menefy <stuart.menefy@st.com>
 * Author: Srinivas Kandagatla <srinivas.kandagatla@st.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/cpu.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/sched_घड़ी.h>

#समावेश <यंत्र/cputype.h>

#घोषणा GT_COUNTER0	0x00
#घोषणा GT_COUNTER1	0x04

#घोषणा GT_CONTROL	0x08
#घोषणा GT_CONTROL_TIMER_ENABLE		BIT(0)  /* this bit is NOT banked */
#घोषणा GT_CONTROL_COMP_ENABLE		BIT(1)	/* banked */
#घोषणा GT_CONTROL_IRQ_ENABLE		BIT(2)	/* banked */
#घोषणा GT_CONTROL_AUTO_INC		BIT(3)	/* banked */

#घोषणा GT_INT_STATUS	0x0c
#घोषणा GT_INT_STATUS_EVENT_FLAG	BIT(0)

#घोषणा GT_COMP0	0x10
#घोषणा GT_COMP1	0x14
#घोषणा GT_AUTO_INC	0x18

/*
 * We are expecting to be घड़ीed by the ARM peripheral घड़ी.
 *
 * Note: it is assumed we are using a prescaler value of zero, so this is
 * the units क्रम all operations.
 */
अटल व्योम __iomem *gt_base;
अटल अचिन्हित दीर्घ gt_clk_rate;
अटल पूर्णांक gt_ppi;
अटल काष्ठा घड़ी_event_device __percpu *gt_evt;

/*
 * To get the value from the Global Timer Counter रेजिस्टर proceed as follows:
 * 1. Read the upper 32-bit समयr counter रेजिस्टर
 * 2. Read the lower 32-bit समयr counter रेजिस्टर
 * 3. Read the upper 32-bit समयr counter रेजिस्टर again. If the value is
 *  dअगरferent to the 32-bit upper value पढ़ो previously, go back to step 2.
 *  Otherwise the 64-bit समयr counter value is correct.
 */
अटल u64 notrace _gt_counter_पढ़ो(व्योम)
अणु
	u64 counter;
	u32 lower;
	u32 upper, old_upper;

	upper = पढ़ोl_relaxed(gt_base + GT_COUNTER1);
	करो अणु
		old_upper = upper;
		lower = पढ़ोl_relaxed(gt_base + GT_COUNTER0);
		upper = पढ़ोl_relaxed(gt_base + GT_COUNTER1);
	पूर्ण जबतक (upper != old_upper);

	counter = upper;
	counter <<= 32;
	counter |= lower;
	वापस counter;
पूर्ण

अटल u64 gt_counter_पढ़ो(व्योम)
अणु
	वापस _gt_counter_पढ़ो();
पूर्ण

/**
 * To ensure that updates to comparator value रेजिस्टर करो not set the
 * Interrupt Status Register proceed as follows:
 * 1. Clear the Comp Enable bit in the Timer Control Register.
 * 2. Write the lower 32-bit Comparator Value Register.
 * 3. Write the upper 32-bit Comparator Value Register.
 * 4. Set the Comp Enable bit and, अगर necessary, the IRQ enable bit.
 */
अटल व्योम gt_compare_set(अचिन्हित दीर्घ delta, पूर्णांक periodic)
अणु
	u64 counter = gt_counter_पढ़ो();
	अचिन्हित दीर्घ ctrl;

	counter += delta;
	ctrl = GT_CONTROL_TIMER_ENABLE;
	ग_लिखोl_relaxed(ctrl, gt_base + GT_CONTROL);
	ग_लिखोl_relaxed(lower_32_bits(counter), gt_base + GT_COMP0);
	ग_लिखोl_relaxed(upper_32_bits(counter), gt_base + GT_COMP1);

	अगर (periodic) अणु
		ग_लिखोl_relaxed(delta, gt_base + GT_AUTO_INC);
		ctrl |= GT_CONTROL_AUTO_INC;
	पूर्ण

	ctrl |= GT_CONTROL_COMP_ENABLE | GT_CONTROL_IRQ_ENABLE;
	ग_लिखोl_relaxed(ctrl, gt_base + GT_CONTROL);
पूर्ण

अटल पूर्णांक gt_घड़ीevent_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	अचिन्हित दीर्घ ctrl;

	ctrl = पढ़ोl(gt_base + GT_CONTROL);
	ctrl &= ~(GT_CONTROL_COMP_ENABLE | GT_CONTROL_IRQ_ENABLE |
		  GT_CONTROL_AUTO_INC);
	ग_लिखोl(ctrl, gt_base + GT_CONTROL);
	वापस 0;
पूर्ण

अटल पूर्णांक gt_घड़ीevent_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	gt_compare_set(DIV_ROUND_CLOSEST(gt_clk_rate, HZ), 1);
	वापस 0;
पूर्ण

अटल पूर्णांक gt_घड़ीevent_set_next_event(अचिन्हित दीर्घ evt,
					काष्ठा घड़ी_event_device *unused)
अणु
	gt_compare_set(evt, 0);
	वापस 0;
पूर्ण

अटल irqवापस_t gt_घड़ीevent_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = dev_id;

	अगर (!(पढ़ोl_relaxed(gt_base + GT_INT_STATUS) &
				GT_INT_STATUS_EVENT_FLAG))
		वापस IRQ_NONE;

	/**
	 * ERRATA 740657( Global Timer can send 2 पूर्णांकerrupts क्रम
	 * the same event in single-shot mode)
	 * Workaround:
	 *	Either disable single-shot mode.
	 *	Or
	 *	Modअगरy the Interrupt Handler to aव्योम the
	 *	offending sequence. This is achieved by clearing
	 *	the Global Timer flag _after_ having incremented
	 *	the Comparator रेजिस्टर	value to a higher value.
	 */
	अगर (घड़ीevent_state_oneshot(evt))
		gt_compare_set(अच_दीर्घ_उच्च, 0);

	ग_लिखोl_relaxed(GT_INT_STATUS_EVENT_FLAG, gt_base + GT_INT_STATUS);
	evt->event_handler(evt);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक gt_starting_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा घड़ी_event_device *clk = this_cpu_ptr(gt_evt);

	clk->name = "arm_global_timer";
	clk->features = CLOCK_EVT_FEAT_PERIODIC | CLOCK_EVT_FEAT_ONESHOT |
		CLOCK_EVT_FEAT_PERCPU;
	clk->set_state_shutकरोwn = gt_घड़ीevent_shutकरोwn;
	clk->set_state_periodic = gt_घड़ीevent_set_periodic;
	clk->set_state_oneshot = gt_घड़ीevent_shutकरोwn;
	clk->set_state_oneshot_stopped = gt_घड़ीevent_shutकरोwn;
	clk->set_next_event = gt_घड़ीevent_set_next_event;
	clk->cpumask = cpumask_of(cpu);
	clk->rating = 300;
	clk->irq = gt_ppi;
	घड़ीevents_config_and_रेजिस्टर(clk, gt_clk_rate,
					1, 0xffffffff);
	enable_percpu_irq(clk->irq, IRQ_TYPE_NONE);
	वापस 0;
पूर्ण

अटल पूर्णांक gt_dying_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा घड़ी_event_device *clk = this_cpu_ptr(gt_evt);

	gt_घड़ीevent_shutकरोwn(clk);
	disable_percpu_irq(clk->irq);
	वापस 0;
पूर्ण

अटल u64 gt_घड़ीsource_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	वापस gt_counter_पढ़ो();
पूर्ण

अटल व्योम gt_resume(काष्ठा घड़ीsource *cs)
अणु
	अचिन्हित दीर्घ ctrl;

	ctrl = पढ़ोl(gt_base + GT_CONTROL);
	अगर (!(ctrl & GT_CONTROL_TIMER_ENABLE))
		/* re-enable समयr on resume */
		ग_लिखोl(GT_CONTROL_TIMER_ENABLE, gt_base + GT_CONTROL);
पूर्ण

अटल काष्ठा घड़ीsource gt_घड़ीsource = अणु
	.name	= "arm_global_timer",
	.rating	= 300,
	.पढ़ो	= gt_घड़ीsource_पढ़ो,
	.mask	= CLOCKSOURCE_MASK(64),
	.flags	= CLOCK_SOURCE_IS_CONTINUOUS,
	.resume = gt_resume,
पूर्ण;

#अगर_घोषित CONFIG_CLKSRC_ARM_GLOBAL_TIMER_SCHED_CLOCK
अटल u64 notrace gt_sched_घड़ी_पढ़ो(व्योम)
अणु
	वापस _gt_counter_पढ़ो();
पूर्ण
#पूर्ण_अगर

अटल अचिन्हित दीर्घ gt_पढ़ो_दीर्घ(व्योम)
अणु
	वापस पढ़ोl_relaxed(gt_base + GT_COUNTER0);
पूर्ण

अटल काष्ठा delay_समयr gt_delay_समयr = अणु
	.पढ़ो_current_समयr = gt_पढ़ो_दीर्घ,
पूर्ण;

अटल व्योम __init gt_delay_समयr_init(व्योम)
अणु
	gt_delay_समयr.freq = gt_clk_rate;
	रेजिस्टर_current_समयr_delay(&gt_delay_समयr);
पूर्ण

अटल पूर्णांक __init gt_घड़ीsource_init(व्योम)
अणु
	ग_लिखोl(0, gt_base + GT_CONTROL);
	ग_लिखोl(0, gt_base + GT_COUNTER0);
	ग_लिखोl(0, gt_base + GT_COUNTER1);
	/* enables समयr on all the cores */
	ग_लिखोl(GT_CONTROL_TIMER_ENABLE, gt_base + GT_CONTROL);

#अगर_घोषित CONFIG_CLKSRC_ARM_GLOBAL_TIMER_SCHED_CLOCK
	sched_घड़ी_रेजिस्टर(gt_sched_घड़ी_पढ़ो, 64, gt_clk_rate);
#पूर्ण_अगर
	वापस घड़ीsource_रेजिस्टर_hz(&gt_घड़ीsource, gt_clk_rate);
पूर्ण

अटल पूर्णांक __init global_समयr_of_रेजिस्टर(काष्ठा device_node *np)
अणु
	काष्ठा clk *gt_clk;
	पूर्णांक err = 0;

	/*
	 * In A9 r2p0 the comparators क्रम each processor with the global समयr
	 * fire when the समयr value is greater than or equal to. In previous
	 * revisions the comparators fired when the समयr value was equal to.
	 */
	अगर (पढ़ो_cpuid_part() == ARM_CPU_PART_CORTEX_A9
	    && (पढ़ो_cpuid_id() & 0xf0000f) < 0x200000) अणु
		pr_warn("global-timer: non support for this cpu version.\n");
		वापस -ENOSYS;
	पूर्ण

	gt_ppi = irq_of_parse_and_map(np, 0);
	अगर (!gt_ppi) अणु
		pr_warn("global-timer: unable to parse irq\n");
		वापस -EINVAL;
	पूर्ण

	gt_base = of_iomap(np, 0);
	अगर (!gt_base) अणु
		pr_warn("global-timer: invalid base address\n");
		वापस -ENXIO;
	पूर्ण

	gt_clk = of_clk_get(np, 0);
	अगर (!IS_ERR(gt_clk)) अणु
		err = clk_prepare_enable(gt_clk);
		अगर (err)
			जाओ out_unmap;
	पूर्ण अन्यथा अणु
		pr_warn("global-timer: clk not found\n");
		err = -EINVAL;
		जाओ out_unmap;
	पूर्ण

	gt_clk_rate = clk_get_rate(gt_clk);
	gt_evt = alloc_percpu(काष्ठा घड़ी_event_device);
	अगर (!gt_evt) अणु
		pr_warn("global-timer: can't allocate memory\n");
		err = -ENOMEM;
		जाओ out_clk;
	पूर्ण

	err = request_percpu_irq(gt_ppi, gt_घड़ीevent_पूर्णांकerrupt,
				 "gt", gt_evt);
	अगर (err) अणु
		pr_warn("global-timer: can't register interrupt %d (%d)\n",
			gt_ppi, err);
		जाओ out_मुक्त;
	पूर्ण

	/* Register and immediately configure the समयr on the boot CPU */
	err = gt_घड़ीsource_init();
	अगर (err)
		जाओ out_irq;
	
	err = cpuhp_setup_state(CPUHP_AP_ARM_GLOBAL_TIMER_STARTING,
				"clockevents/arm/global_timer:starting",
				gt_starting_cpu, gt_dying_cpu);
	अगर (err)
		जाओ out_irq;

	gt_delay_समयr_init();

	वापस 0;

out_irq:
	मुक्त_percpu_irq(gt_ppi, gt_evt);
out_मुक्त:
	मुक्त_percpu(gt_evt);
out_clk:
	clk_disable_unprepare(gt_clk);
out_unmap:
	iounmap(gt_base);
	WARN(err, "ARM Global timer register failed (%d)\n", err);

	वापस err;
पूर्ण

/* Only tested on r2p2 and r3p0  */
TIMER_OF_DECLARE(arm_gt, "arm,cortex-a9-global-timer",
			global_समयr_of_रेजिस्टर);
