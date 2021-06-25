<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016-17 Synopsys, Inc. (www.synopsys.com)
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

/* ARC700 has two 32bit independent prog Timers: TIMER0 and TIMER1, Each can be
 * programmed to go from @count to @limit and optionally पूर्णांकerrupt.
 * We've designated TIMER0 क्रम घड़ीevents and TIMER1 क्रम घड़ीsource
 *
 * ARCv2 based HS38 cores have RTC (in-core) and GFRC (inside ARConnect/MCIP)
 * which are suitable क्रम UP and SMP based घड़ीsources respectively
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/bits.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/cpu.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/sched_घड़ी.h>

#समावेश <soc/arc/समयrs.h>
#समावेश <soc/arc/mcip.h>


अटल अचिन्हित दीर्घ arc_समयr_freq;

अटल पूर्णांक noअंतरभूत arc_get_समयr_clk(काष्ठा device_node *node)
अणु
	काष्ठा clk *clk;
	पूर्णांक ret;

	clk = of_clk_get(node, 0);
	अगर (IS_ERR(clk)) अणु
		pr_err("timer missing clk\n");
		वापस PTR_ERR(clk);
	पूर्ण

	ret = clk_prepare_enable(clk);
	अगर (ret) अणु
		pr_err("Couldn't enable parent clk\n");
		वापस ret;
	पूर्ण

	arc_समयr_freq = clk_get_rate(clk);

	वापस 0;
पूर्ण

/********** Clock Source Device *********/

#अगर_घोषित CONFIG_ARC_TIMERS_64BIT

अटल u64 arc_पढ़ो_gfrc(काष्ठा घड़ीsource *cs)
अणु
	अचिन्हित दीर्घ flags;
	u32 l, h;

	/*
	 * From a programming model pov, there seems to be just one instance of
	 * MCIP_CMD/MCIP_READBACK however micro-architecturally there's
	 * an instance PER ARC CORE (not per cluster), and there are dedicated
	 * hardware decode logic (per core) inside ARConnect to handle
	 * simultaneous पढ़ो/ग_लिखो accesses from cores via those two रेजिस्टरs.
	 * So several concurrent commands to ARConnect are OK अगर they are
	 * trying to access two dअगरferent sub-components (like GFRC,
	 * पूर्णांकer-core पूर्णांकerrupt, etc...). HW also supports simultaneously
	 * accessing GFRC by multiple cores.
	 * That's why it is safe to disable hard पूर्णांकerrupts on the local CPU
	 * beक्रमe access to GFRC instead of taking global MCIP spinlock
	 * defined in arch/arc/kernel/mcip.c
	 */
	local_irq_save(flags);

	__mcip_cmd(CMD_GFRC_READ_LO, 0);
	l = पढ़ो_aux_reg(ARC_REG_MCIP_READBACK);

	__mcip_cmd(CMD_GFRC_READ_HI, 0);
	h = पढ़ो_aux_reg(ARC_REG_MCIP_READBACK);

	local_irq_restore(flags);

	वापस (((u64)h) << 32) | l;
पूर्ण

अटल notrace u64 arc_gfrc_घड़ी_पढ़ो(व्योम)
अणु
	वापस arc_पढ़ो_gfrc(शून्य);
पूर्ण

अटल काष्ठा घड़ीsource arc_counter_gfrc = अणु
	.name   = "ARConnect GFRC",
	.rating = 400,
	.पढ़ो   = arc_पढ़ो_gfrc,
	.mask   = CLOCKSOURCE_MASK(64),
	.flags  = CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

अटल पूर्णांक __init arc_cs_setup_gfrc(काष्ठा device_node *node)
अणु
	काष्ठा mcip_bcr mp;
	पूर्णांक ret;

	READ_BCR(ARC_REG_MCIP_BCR, mp);
	अगर (!mp.gfrc) अणु
		pr_warn("Global-64-bit-Ctr clocksource not detected\n");
		वापस -ENXIO;
	पूर्ण

	ret = arc_get_समयr_clk(node);
	अगर (ret)
		वापस ret;

	sched_घड़ी_रेजिस्टर(arc_gfrc_घड़ी_पढ़ो, 64, arc_समयr_freq);

	वापस घड़ीsource_रेजिस्टर_hz(&arc_counter_gfrc, arc_समयr_freq);
पूर्ण
TIMER_OF_DECLARE(arc_gfrc, "snps,archs-timer-gfrc", arc_cs_setup_gfrc);

#घोषणा AUX_RTC_CTRL	0x103
#घोषणा AUX_RTC_LOW	0x104
#घोषणा AUX_RTC_HIGH	0x105

अटल u64 arc_पढ़ो_rtc(काष्ठा घड़ीsource *cs)
अणु
	अचिन्हित दीर्घ status;
	u32 l, h;

	/*
	 * hardware has an पूर्णांकernal state machine which tracks पढ़ोout of
	 * low/high and updates the CTRL.status अगर
	 *  - पूर्णांकerrupt/exception taken between the two पढ़ोs
	 *  - high increments after low has been पढ़ो
	 */
	करो अणु
		l = पढ़ो_aux_reg(AUX_RTC_LOW);
		h = पढ़ो_aux_reg(AUX_RTC_HIGH);
		status = पढ़ो_aux_reg(AUX_RTC_CTRL);
	पूर्ण जबतक (!(status & BIT(31)));

	वापस (((u64)h) << 32) | l;
पूर्ण

अटल notrace u64 arc_rtc_घड़ी_पढ़ो(व्योम)
अणु
	वापस arc_पढ़ो_rtc(शून्य);
पूर्ण

अटल काष्ठा घड़ीsource arc_counter_rtc = अणु
	.name   = "ARCv2 RTC",
	.rating = 350,
	.पढ़ो   = arc_पढ़ो_rtc,
	.mask   = CLOCKSOURCE_MASK(64),
	.flags  = CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

अटल पूर्णांक __init arc_cs_setup_rtc(काष्ठा device_node *node)
अणु
	काष्ठा bcr_समयr समयr;
	पूर्णांक ret;

	READ_BCR(ARC_REG_TIMERS_BCR, समयr);
	अगर (!समयr.rtc) अणु
		pr_warn("Local-64-bit-Ctr clocksource not detected\n");
		वापस -ENXIO;
	पूर्ण

	/* Local to CPU hence not usable in SMP */
	अगर (IS_ENABLED(CONFIG_SMP)) अणु
		pr_warn("Local-64-bit-Ctr not usable in SMP\n");
		वापस -EINVAL;
	पूर्ण

	ret = arc_get_समयr_clk(node);
	अगर (ret)
		वापस ret;

	ग_लिखो_aux_reg(AUX_RTC_CTRL, 1);

	sched_घड़ी_रेजिस्टर(arc_rtc_घड़ी_पढ़ो, 64, arc_समयr_freq);

	वापस घड़ीsource_रेजिस्टर_hz(&arc_counter_rtc, arc_समयr_freq);
पूर्ण
TIMER_OF_DECLARE(arc_rtc, "snps,archs-timer-rtc", arc_cs_setup_rtc);

#पूर्ण_अगर

/*
 * 32bit TIMER1 to keep counting monotonically and wraparound
 */

अटल u64 arc_पढ़ो_समयr1(काष्ठा घड़ीsource *cs)
अणु
	वापस (u64) पढ़ो_aux_reg(ARC_REG_TIMER1_CNT);
पूर्ण

अटल notrace u64 arc_समयr1_घड़ी_पढ़ो(व्योम)
अणु
	वापस arc_पढ़ो_समयr1(शून्य);
पूर्ण

अटल काष्ठा घड़ीsource arc_counter_समयr1 = अणु
	.name   = "ARC Timer1",
	.rating = 300,
	.पढ़ो   = arc_पढ़ो_समयr1,
	.mask   = CLOCKSOURCE_MASK(32),
	.flags  = CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

अटल पूर्णांक __init arc_cs_setup_समयr1(काष्ठा device_node *node)
अणु
	पूर्णांक ret;

	/* Local to CPU hence not usable in SMP */
	अगर (IS_ENABLED(CONFIG_SMP))
		वापस -EINVAL;

	ret = arc_get_समयr_clk(node);
	अगर (ret)
		वापस ret;

	ग_लिखो_aux_reg(ARC_REG_TIMER1_LIMIT, ARC_TIMERN_MAX);
	ग_लिखो_aux_reg(ARC_REG_TIMER1_CNT, 0);
	ग_लिखो_aux_reg(ARC_REG_TIMER1_CTRL, TIMER_CTRL_NH);

	sched_घड़ी_रेजिस्टर(arc_समयr1_घड़ी_पढ़ो, 32, arc_समयr_freq);

	वापस घड़ीsource_रेजिस्टर_hz(&arc_counter_समयr1, arc_समयr_freq);
पूर्ण

/********** Clock Event Device *********/

अटल पूर्णांक arc_समयr_irq;

/*
 * Arm the समयr to पूर्णांकerrupt after @cycles
 * The distinction क्रम oneshot/periodic is करोne in arc_event_समयr_ack() below
 */
अटल व्योम arc_समयr_event_setup(अचिन्हित पूर्णांक cycles)
अणु
	ग_लिखो_aux_reg(ARC_REG_TIMER0_LIMIT, cycles);
	ग_लिखो_aux_reg(ARC_REG_TIMER0_CNT, 0);	/* start from 0 */

	ग_लिखो_aux_reg(ARC_REG_TIMER0_CTRL, TIMER_CTRL_IE | TIMER_CTRL_NH);
पूर्ण


अटल पूर्णांक arc_clkevent_set_next_event(अचिन्हित दीर्घ delta,
				       काष्ठा घड़ी_event_device *dev)
अणु
	arc_समयr_event_setup(delta);
	वापस 0;
पूर्ण

अटल पूर्णांक arc_clkevent_set_periodic(काष्ठा घड़ी_event_device *dev)
अणु
	/*
	 * At X Hz, 1 sec = 1000ms -> X cycles;
	 *		      10ms -> X / 100 cycles
	 */
	arc_समयr_event_setup(arc_समयr_freq / HZ);
	वापस 0;
पूर्ण

अटल DEFINE_PER_CPU(काष्ठा घड़ी_event_device, arc_घड़ीevent_device) = अणु
	.name			= "ARC Timer0",
	.features		= CLOCK_EVT_FEAT_ONESHOT |
				  CLOCK_EVT_FEAT_PERIODIC,
	.rating			= 300,
	.set_next_event		= arc_clkevent_set_next_event,
	.set_state_periodic	= arc_clkevent_set_periodic,
पूर्ण;

अटल irqवापस_t समयr_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	/*
	 * Note that generic IRQ core could have passed @evt क्रम @dev_id अगर
	 * irq_set_chip_and_handler() asked क्रम handle_percpu_devid_irq()
	 */
	काष्ठा घड़ी_event_device *evt = this_cpu_ptr(&arc_घड़ीevent_device);
	पूर्णांक irq_reenable = घड़ीevent_state_periodic(evt);

	/*
	 * 1. ACK the पूर्णांकerrupt
	 *    - For ARC700, any ग_लिखो to CTRL reg ACKs it, so just reग_लिखो
	 *      Count when [N]ot [H]alted bit.
	 *    - For HS3x, it is a bit subtle. On taken count-करोwn पूर्णांकerrupt,
	 *      IP bit [3] is set, which needs to be cleared क्रम ACK'ing.
	 *      The ग_लिखो below can only update the other two bits, hence
	 *      explicitly clears IP bit
	 * 2. Re-arm पूर्णांकerrupt अगर periodic by writing to IE bit [0]
	 */
	ग_लिखो_aux_reg(ARC_REG_TIMER0_CTRL, irq_reenable | TIMER_CTRL_NH);

	evt->event_handler(evt);

	वापस IRQ_HANDLED;
पूर्ण


अटल पूर्णांक arc_समयr_starting_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा घड़ी_event_device *evt = this_cpu_ptr(&arc_घड़ीevent_device);

	evt->cpumask = cpumask_of(smp_processor_id());

	घड़ीevents_config_and_रेजिस्टर(evt, arc_समयr_freq, 0, ARC_TIMERN_MAX);
	enable_percpu_irq(arc_समयr_irq, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक arc_समयr_dying_cpu(अचिन्हित पूर्णांक cpu)
अणु
	disable_percpu_irq(arc_समयr_irq);
	वापस 0;
पूर्ण

/*
 * घड़ीevent setup क्रम boot CPU
 */
अटल पूर्णांक __init arc_घड़ीevent_setup(काष्ठा device_node *node)
अणु
	काष्ठा घड़ी_event_device *evt = this_cpu_ptr(&arc_घड़ीevent_device);
	पूर्णांक ret;

	arc_समयr_irq = irq_of_parse_and_map(node, 0);
	अगर (arc_समयr_irq <= 0) अणु
		pr_err("clockevent: missing irq\n");
		वापस -EINVAL;
	पूर्ण

	ret = arc_get_समयr_clk(node);
	अगर (ret)
		वापस ret;

	/* Needs apriori irq_set_percpu_devid() करोne in पूर्णांकc map function */
	ret = request_percpu_irq(arc_समयr_irq, समयr_irq_handler,
				 "Timer0 (per-cpu-tick)", evt);
	अगर (ret) अणु
		pr_err("clockevent: unable to request irq\n");
		वापस ret;
	पूर्ण

	ret = cpuhp_setup_state(CPUHP_AP_ARC_TIMER_STARTING,
				"clockevents/arc/timer:starting",
				arc_समयr_starting_cpu,
				arc_समयr_dying_cpu);
	अगर (ret) अणु
		pr_err("Failed to setup hotplug state\n");
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init arc_of_समयr_init(काष्ठा device_node *np)
अणु
	अटल पूर्णांक init_count = 0;
	पूर्णांक ret;

	अगर (!init_count) अणु
		init_count = 1;
		ret = arc_घड़ीevent_setup(np);
	पूर्ण अन्यथा अणु
		ret = arc_cs_setup_समयr1(np);
	पूर्ण

	वापस ret;
पूर्ण
TIMER_OF_DECLARE(arc_clkevt, "snps,arc-timer", arc_of_समयr_init);
