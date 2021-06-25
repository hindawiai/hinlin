<शैली गुरु>
/*
 * arch/xtensa/kernel/समय.c
 *
 * Timer and घड़ी support.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2005 Tensilica Inc.
 *
 * Chris Zankel <chris@zankel.net>
 */

#समावेश <linux/clk.h>
#समावेश <linux/of_clk.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/समय.स>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/profile.h>
#समावेश <linux/delay.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/sched_घड़ी.h>

#समावेश <यंत्र/समयx.h>
#समावेश <यंत्र/platक्रमm.h>

अचिन्हित दीर्घ ccount_freq;		/* ccount Hz */
EXPORT_SYMBOL(ccount_freq);

अटल u64 ccount_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	वापस (u64)get_ccount();
पूर्ण

अटल u64 notrace ccount_sched_घड़ी_पढ़ो(व्योम)
अणु
	वापस get_ccount();
पूर्ण

अटल काष्ठा घड़ीsource ccount_घड़ीsource = अणु
	.name = "ccount",
	.rating = 200,
	.पढ़ो = ccount_पढ़ो,
	.mask = CLOCKSOURCE_MASK(32),
	.flags = CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

काष्ठा ccount_समयr अणु
	काष्ठा घड़ी_event_device evt;
	पूर्णांक irq_enabled;
	अक्षर name[24];
पूर्ण;

अटल पूर्णांक ccount_समयr_set_next_event(अचिन्हित दीर्घ delta,
		काष्ठा घड़ी_event_device *dev)
अणु
	अचिन्हित दीर्घ flags, next;
	पूर्णांक ret = 0;

	local_irq_save(flags);
	next = get_ccount() + delta;
	set_linux_समयr(next);
	अगर (next - get_ccount() > delta)
		ret = -ETIME;
	local_irq_restore(flags);

	वापस ret;
पूर्ण

/*
 * There is no way to disable the समयr पूर्णांकerrupt at the device level,
 * only at the पूर्णांकenable रेजिस्टर itself. Since enable_irq/disable_irq
 * calls are nested, we need to make sure that these calls are
 * balanced.
 */
अटल पूर्णांक ccount_समयr_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा ccount_समयr *समयr =
		container_of(evt, काष्ठा ccount_समयr, evt);

	अगर (समयr->irq_enabled) अणु
		disable_irq_nosync(evt->irq);
		समयr->irq_enabled = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ccount_समयr_set_oneshot(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा ccount_समयr *समयr =
		container_of(evt, काष्ठा ccount_समयr, evt);

	अगर (!समयr->irq_enabled) अणु
		enable_irq(evt->irq);
		समयr->irq_enabled = 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल DEFINE_PER_CPU(काष्ठा ccount_समयr, ccount_समयr) = अणु
	.evt = अणु
		.features = CLOCK_EVT_FEAT_ONESHOT,
		.rating = 300,
		.set_next_event = ccount_समयr_set_next_event,
		.set_state_shutकरोwn = ccount_समयr_shutकरोwn,
		.set_state_oneshot = ccount_समयr_set_oneshot,
		.tick_resume = ccount_समयr_set_oneshot,
	पूर्ण,
पूर्ण;

अटल irqवापस_t समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = &this_cpu_ptr(&ccount_समयr)->evt;

	set_linux_समयr(get_linux_समयr());
	evt->event_handler(evt);

	/* Allow platक्रमm to करो something useful (Wकरोg). */
	platक्रमm_heartbeat();

	वापस IRQ_HANDLED;
पूर्ण

व्योम local_समयr_setup(अचिन्हित cpu)
अणु
	काष्ठा ccount_समयr *समयr = &per_cpu(ccount_समयr, cpu);
	काष्ठा घड़ी_event_device *घड़ीevent = &समयr->evt;

	समयr->irq_enabled = 1;
	snम_लिखो(समयr->name, माप(समयr->name), "ccount_clockevent_%u", cpu);
	घड़ीevent->name = समयr->name;
	घड़ीevent->cpumask = cpumask_of(cpu);
	घड़ीevent->irq = irq_create_mapping(शून्य, LINUX_TIMER_INT);
	अगर (WARN(!घड़ीevent->irq, "error: can't map timer irq"))
		वापस;
	घड़ीevents_config_and_रेजिस्टर(घड़ीevent, ccount_freq,
					0xf, 0xffffffff);
पूर्ण

#अगर_घोषित CONFIG_XTENSA_CALIBRATE_CCOUNT
#अगर_घोषित CONFIG_OF
अटल व्योम __init calibrate_ccount(व्योम)
अणु
	काष्ठा device_node *cpu;
	काष्ठा clk *clk;

	cpu = of_find_compatible_node(शून्य, शून्य, "cdns,xtensa-cpu");
	अगर (cpu) अणु
		clk = of_clk_get(cpu, 0);
		अगर (!IS_ERR(clk)) अणु
			ccount_freq = clk_get_rate(clk);
			वापस;
		पूर्ण अन्यथा अणु
			pr_warn("%s: CPU input clock not found\n",
				__func__);
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_warn("%s: CPU node not found in the device tree\n",
			__func__);
	पूर्ण

	platक्रमm_calibrate_ccount();
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम calibrate_ccount(व्योम)
अणु
	platक्रमm_calibrate_ccount();
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

व्योम __init समय_init(व्योम)
अणु
	पूर्णांक irq;

	of_clk_init(शून्य);
#अगर_घोषित CONFIG_XTENSA_CALIBRATE_CCOUNT
	pr_info("Calibrating CPU frequency ");
	calibrate_ccount();
	pr_cont("%d.%02d MHz\n",
		(पूर्णांक)ccount_freq / 1000000,
		(पूर्णांक)(ccount_freq / 10000) % 100);
#अन्यथा
	ccount_freq = CONFIG_XTENSA_CPU_CLOCK*1000000UL;
#पूर्ण_अगर
	WARN(!ccount_freq,
	     "%s: CPU clock frequency is not set up correctly\n",
	     __func__);
	घड़ीsource_रेजिस्टर_hz(&ccount_घड़ीsource, ccount_freq);
	local_समयr_setup(0);
	irq = this_cpu_ptr(&ccount_समयr)->evt.irq;
	अगर (request_irq(irq, समयr_पूर्णांकerrupt, IRQF_TIMER, "timer", शून्य))
		pr_err("Failed to request irq %d (timer)\n", irq);
	sched_घड़ी_रेजिस्टर(ccount_sched_घड़ी_पढ़ो, 32, ccount_freq);
	समयr_probe();
पूर्ण

#अगर_अघोषित CONFIG_GENERIC_CALIBRATE_DELAY
व्योम calibrate_delay(व्योम)
अणु
	loops_per_jअगरfy = ccount_freq / HZ;
	pr_info("Calibrating delay loop (skipped)... %lu.%02lu BogoMIPS preset\n",
		loops_per_jअगरfy / (1000000 / HZ),
		(loops_per_jअगरfy / (10000 / HZ)) % 100);
पूर्ण
#पूर्ण_अगर
