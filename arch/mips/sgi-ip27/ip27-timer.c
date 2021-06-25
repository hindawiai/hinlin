<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 1999, 2000, 05, 06 Ralf Baechle (ralf@linux-mips.org)
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 */
#समावेश <linux/bcd.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/param.h>
#समावेश <linux/smp.h>
#समावेश <linux/समय.स>
#समावेश <linux/समयx.h>
#समावेश <linux/mm.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/sgialib.h>
#समावेश <यंत्र/sn/klconfig.h>
#समावेश <यंत्र/sn/arch.h>
#समावेश <यंत्र/sn/addrs.h>
#समावेश <यंत्र/sn/agent.h>

#समावेश "ip27-common.h"

अटल पूर्णांक rt_next_event(अचिन्हित दीर्घ delta, काष्ठा घड़ी_event_device *evt)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	पूर्णांक slice = cputoslice(cpu);
	अचिन्हित दीर्घ cnt;

	cnt = LOCAL_HUB_L(PI_RT_COUNT);
	cnt += delta;
	LOCAL_HUB_S(PI_RT_COMPARE_A + PI_COUNT_OFFSET * slice, cnt);

	वापस LOCAL_HUB_L(PI_RT_COUNT) >= cnt ? -ETIME : 0;
पूर्ण

अटल DEFINE_PER_CPU(काष्ठा घड़ी_event_device, hub_rt_घड़ीevent);
अटल DEFINE_PER_CPU(अक्षर [11], hub_rt_name);

अटल irqवापस_t hub_rt_counter_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	काष्ठा घड़ी_event_device *cd = &per_cpu(hub_rt_घड़ीevent, cpu);
	पूर्णांक slice = cputoslice(cpu);

	/*
	 * Ack
	 */
	LOCAL_HUB_S(PI_RT_PEND_A + PI_COUNT_OFFSET * slice, 0);
	cd->event_handler(cd);

	वापस IRQ_HANDLED;
पूर्ण

काष्ठा irqaction hub_rt_irqaction = अणु
	.handler	= hub_rt_counter_handler,
	.percpu_dev_id	= &hub_rt_घड़ीevent,
	.flags		= IRQF_PERCPU | IRQF_TIMER,
	.name		= "hub-rt",
पूर्ण;

/*
 * This is a hack; we really need to figure these values out dynamically
 *
 * Since 800 ns works very well with various HUB frequencies, such as
 * 360, 380, 390 and 400 MHZ, we use 800 ns rtc cycle समय.
 *
 * Ralf: which घड़ी rate is used to feed the counter?
 */
#घोषणा NSEC_PER_CYCLE		800
#घोषणा CYCLES_PER_SEC		(NSEC_PER_SEC / NSEC_PER_CYCLE)

व्योम hub_rt_घड़ी_event_init(व्योम)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	काष्ठा घड़ी_event_device *cd = &per_cpu(hub_rt_घड़ीevent, cpu);
	अचिन्हित अक्षर *name = per_cpu(hub_rt_name, cpu);

	प्र_लिखो(name, "hub-rt %d", cpu);
	cd->name		= name;
	cd->features		= CLOCK_EVT_FEAT_ONESHOT;
	घड़ीevent_set_घड़ी(cd, CYCLES_PER_SEC);
	cd->max_delta_ns	= घड़ीevent_delta2ns(0xfffffffffffff, cd);
	cd->max_delta_ticks	= 0xfffffffffffff;
	cd->min_delta_ns	= घड़ीevent_delta2ns(0x300, cd);
	cd->min_delta_ticks	= 0x300;
	cd->rating		= 200;
	cd->irq			= IP27_RT_TIMER_IRQ;
	cd->cpumask		= cpumask_of(cpu);
	cd->set_next_event	= rt_next_event;
	घड़ीevents_रेजिस्टर_device(cd);

	enable_percpu_irq(IP27_RT_TIMER_IRQ, IRQ_TYPE_NONE);
पूर्ण

अटल व्योम __init hub_rt_घड़ी_event_global_init(व्योम)
अणु
	irq_set_handler(IP27_RT_TIMER_IRQ, handle_percpu_devid_irq);
	irq_set_percpu_devid(IP27_RT_TIMER_IRQ);
	setup_percpu_irq(IP27_RT_TIMER_IRQ, &hub_rt_irqaction);
पूर्ण

अटल u64 hub_rt_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	वापस REMOTE_HUB_L(cputonasid(0), PI_RT_COUNT);
पूर्ण

काष्ठा घड़ीsource hub_rt_घड़ीsource = अणु
	.name	= "HUB-RT",
	.rating = 200,
	.पढ़ो	= hub_rt_पढ़ो,
	.mask	= CLOCKSOURCE_MASK(52),
	.flags	= CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

अटल u64 notrace hub_rt_पढ़ो_sched_घड़ी(व्योम)
अणु
	वापस REMOTE_HUB_L(cputonasid(0), PI_RT_COUNT);
पूर्ण

अटल व्योम __init hub_rt_घड़ीsource_init(व्योम)
अणु
	काष्ठा घड़ीsource *cs = &hub_rt_घड़ीsource;

	घड़ीsource_रेजिस्टर_hz(cs, CYCLES_PER_SEC);

	sched_घड़ी_रेजिस्टर(hub_rt_पढ़ो_sched_घड़ी, 52, CYCLES_PER_SEC);
पूर्ण

व्योम __init plat_समय_init(व्योम)
अणु
	hub_rt_घड़ीsource_init();
	hub_rt_घड़ी_event_global_init();
	hub_rt_घड़ी_event_init();
पूर्ण

व्योम hub_rtc_init(nasid_t nasid)
अणु

	/*
	 * We only need to initialize the current node.
	 * If this is not the current node then it is a cpuless
	 * node and समयouts will not happen there.
	 */
	अगर (get_nasid() == nasid) अणु
		LOCAL_HUB_S(PI_RT_EN_A, 1);
		LOCAL_HUB_S(PI_RT_EN_B, 1);
		LOCAL_HUB_S(PI_PROF_EN_A, 0);
		LOCAL_HUB_S(PI_PROF_EN_B, 0);
		LOCAL_HUB_S(PI_RT_COUNT, 0);
		LOCAL_HUB_S(PI_RT_PEND_A, 0);
		LOCAL_HUB_S(PI_RT_PEND_B, 0);
	पूर्ण
पूर्ण
