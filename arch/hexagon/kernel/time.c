<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Time related functions क्रम Hexagon architecture
 *
 * Copyright (c) 2010-2011, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/init.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ioport.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/समयr-regs.h>
#समावेश <यंत्र/hexagon_vm.h>

/*
 * For the घड़ीsource we need:
 *	pcycle frequency (600MHz)
 * For the loops_per_jअगरfy we need:
 *	thपढ़ो/cpu frequency (100MHz)
 * And क्रम the समयr, we need:
 *	sleep घड़ी rate
 */

cycles_t	pcycle_freq_mhz;
cycles_t	thपढ़ो_freq_mhz;
cycles_t	sleep_clk_freq;

अटल काष्ठा resource rtos_समयr_resources[] = अणु
	अणु
		.start	= RTOS_TIMER_REGS_ADDR,
		.end	= RTOS_TIMER_REGS_ADDR+PAGE_SIZE-1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device rtos_समयr_device = अणु
	.name		= "rtos_timer",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(rtos_समयr_resources),
	.resource	= rtos_समयr_resources,
पूर्ण;

/*  A lot of this stuff should move पूर्णांकo a platक्रमm specअगरic section.  */
काष्ठा adsp_hw_समयr_काष्ठा अणु
	u32 match;   /*  Match value  */
	u32 count;
	u32 enable;  /*  [1] - CLR_ON_MATCH_EN, [0] - EN  */
	u32 clear;   /*  one-shot रेजिस्टर that clears the count  */
पूर्ण;

/*  Look क्रम "TCX0" क्रम related स्थिरants.  */
अटल __iomem काष्ठा adsp_hw_समयr_काष्ठा *rtos_समयr;

अटल u64 समयr_get_cycles(काष्ठा घड़ीsource *cs)
अणु
	वापस (u64) __vmसमय_लो();
पूर्ण

अटल काष्ठा घड़ीsource hexagon_घड़ीsource = अणु
	.name		= "pcycles",
	.rating		= 250,
	.पढ़ो		= समयr_get_cycles,
	.mask		= CLOCKSOURCE_MASK(64),
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

अटल पूर्णांक set_next_event(अचिन्हित दीर्घ delta, काष्ठा घड़ी_event_device *evt)
अणु
	/*  Assuming the समयr will be disabled when we enter here.  */

	ioग_लिखो32(1, &rtos_समयr->clear);
	ioग_लिखो32(0, &rtos_समयr->clear);

	ioग_लिखो32(delta, &rtos_समयr->match);
	ioग_लिखो32(1 << TIMER_ENABLE, &rtos_समयr->enable);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SMP
/*  Broadcast mechanism  */
अटल व्योम broadcast(स्थिर काष्ठा cpumask *mask)
अणु
	send_ipi(mask, IPI_TIMER);
पूर्ण
#पूर्ण_अगर

/* XXX Implement set_state_shutकरोwn() */
अटल काष्ठा घड़ी_event_device hexagon_घड़ीevent_dev = अणु
	.name		= "clockevent",
	.features	= CLOCK_EVT_FEAT_ONESHOT,
	.rating		= 400,
	.irq		= RTOS_TIMER_INT,
	.set_next_event = set_next_event,
#अगर_घोषित CONFIG_SMP
	.broadcast	= broadcast,
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_SMP
अटल DEFINE_PER_CPU(काष्ठा घड़ी_event_device, घड़ी_events);

व्योम setup_percpu_घड़ीdev(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();
	काष्ठा घड़ी_event_device *ce_dev = &hexagon_घड़ीevent_dev;
	काष्ठा घड़ी_event_device *dummy_घड़ी_dev =
		&per_cpu(घड़ी_events, cpu);

	स_नकल(dummy_घड़ी_dev, ce_dev, माप(*dummy_घड़ी_dev));
	INIT_LIST_HEAD(&dummy_घड़ी_dev->list);

	dummy_घड़ी_dev->features = CLOCK_EVT_FEAT_DUMMY;
	dummy_घड़ी_dev->cpumask = cpumask_of(cpu);

	घड़ीevents_रेजिस्टर_device(dummy_घड़ी_dev);
पूर्ण

/*  Called from smp.c क्रम each CPU's समयr ipi call  */
व्योम ipi_समयr(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();
	काष्ठा घड़ी_event_device *ce_dev = &per_cpu(घड़ी_events, cpu);

	ce_dev->event_handler(ce_dev);
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

अटल irqवापस_t समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा घड़ी_event_device *ce_dev = &hexagon_घड़ीevent_dev;

	ioग_लिखो32(0, &rtos_समयr->enable);
	ce_dev->event_handler(ce_dev);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * समय_init_deferred - called by start_kernel to set up समयr/घड़ी source
 *
 * Install the IRQ handler क्रम the घड़ी, setup समयrs.
 * This is करोne late, as that way, we can use ioremap().
 *
 * This runs just beक्रमe the delay loop is calibrated, and
 * is used क्रम delay calibration.
 */
व्योम __init समय_init_deferred(व्योम)
अणु
	काष्ठा resource *resource = शून्य;
	काष्ठा घड़ी_event_device *ce_dev = &hexagon_घड़ीevent_dev;
	अचिन्हित दीर्घ flag = IRQF_TIMER | IRQF_TRIGGER_RISING;

	ce_dev->cpumask = cpu_all_mask;

	अगर (!resource)
		resource = rtos_समयr_device.resource;

	/*  ioremap here means this has to run later, after paging init  */
	rtos_समयr = ioremap(resource->start, resource_size(resource));

	अगर (!rtos_समयr) अणु
		release_mem_region(resource->start, resource_size(resource));
	पूर्ण
	घड़ीsource_रेजिस्टर_khz(&hexagon_घड़ीsource, pcycle_freq_mhz * 1000);

	/*  Note: the sim generic RTOS घड़ी is apparently really 18750Hz  */

	/*
	 * Last arg is some guaranteed seconds क्रम which the conversion will
	 * work without overflow.
	 */
	घड़ीevents_calc_mult_shअगरt(ce_dev, sleep_clk_freq, 4);

	ce_dev->max_delta_ns = घड़ीevent_delta2ns(0x7fffffff, ce_dev);
	ce_dev->max_delta_ticks = 0x7fffffff;
	ce_dev->min_delta_ns = घड़ीevent_delta2ns(0xf, ce_dev);
	ce_dev->min_delta_ticks = 0xf;

#अगर_घोषित CONFIG_SMP
	setup_percpu_घड़ीdev();
#पूर्ण_अगर

	घड़ीevents_रेजिस्टर_device(ce_dev);
	अगर (request_irq(ce_dev->irq, समयr_पूर्णांकerrupt, flag, "rtos_timer", शून्य))
		pr_err("Failed to register rtos_timer interrupt\n");
पूर्ण

व्योम __init समय_init(व्योम)
अणु
	late_समय_init = समय_init_deferred;
पूर्ण

व्योम __delay(अचिन्हित दीर्घ cycles)
अणु
	अचिन्हित दीर्घ दीर्घ start = __vmसमय_लो();

	जबतक ((__vmसमय_लो() - start) < cycles)
		cpu_relax();
पूर्ण
EXPORT_SYMBOL(__delay);

/*
 * This could become parametric or perhaps even computed at run-समय,
 * but क्रम now we take the observed simulator jitter.
 */
अटल दीर्घ दीर्घ fudgefactor = 350;  /* Maybe lower अगर kernel optimized. */

व्योम __udelay(अचिन्हित दीर्घ usecs)
अणु
	अचिन्हित दीर्घ दीर्घ start = __vmसमय_लो();
	अचिन्हित दीर्घ दीर्घ finish = (pcycle_freq_mhz * usecs) - fudgefactor;

	जबतक ((__vmसमय_लो() - start) < finish)
		cpu_relax(); /*  not sure how this improves पढ़ोability  */
पूर्ण
EXPORT_SYMBOL(__udelay);
