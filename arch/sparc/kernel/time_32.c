<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* linux/arch/sparc/kernel/समय.c
 *
 * Copyright (C) 1995 David S. Miller (davem@davemloft.net)
 * Copyright (C) 1996 Thomas K. Dyas (tdyas@eden.rutgers.edu)
 *
 * Chris Davis (cdavis@cois.on.ca) 03/27/1998
 * Added support क्रम the पूर्णांकersil on the sun4/4200
 *
 * Gleb Raiko (rajko@mech.math.msu.su) 08/18/1998
 * Support क्रम MicroSPARC-IIep, PCI CPU.
 *
 * This file handles the Sparc specअगरic समय handling details.
 *
 * 1997-09-10	Updated NTP code according to technical memoअक्रमum Jan '96
 *		"A Kernel Model for Precision Timekeeping" by Dave Mills
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/param.h>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/समय.स>
#समावेश <linux/rtc/m48t59.h>
#समावेश <linux/समयx.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/ioport.h>
#समावेश <linux/profile.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/mc146818rtc.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/समयx.h>
#समावेश <यंत्र/समयr.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/idprom.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/pcic.h>
#समावेश <यंत्र/irq_regs.h>
#समावेश <यंत्र/setup.h>

#समावेश "kernel.h"
#समावेश "irq.h"

अटल __cacheline_aligned_in_smp DEFINE_SEQLOCK(समयr_cs_lock);
अटल __अस्थिर__ u64 समयr_cs_पूर्णांकernal_counter = 0;
अटल अक्षर समयr_cs_enabled = 0;

अटल काष्ठा घड़ी_event_device समयr_ce;
अटल अक्षर समयr_ce_enabled = 0;

#अगर_घोषित CONFIG_SMP
DEFINE_PER_CPU(काष्ठा घड़ी_event_device, sparc32_घड़ीevent);
#पूर्ण_अगर

DEFINE_SPINLOCK(rtc_lock);
EXPORT_SYMBOL(rtc_lock);

अचिन्हित दीर्घ profile_pc(काष्ठा pt_regs *regs)
अणु
	बाह्य अक्षर __copy_user_begin[], __copy_user_end[];
	बाह्य अक्षर __bzero_begin[], __bzero_end[];

	अचिन्हित दीर्घ pc = regs->pc;

	अगर (in_lock_functions(pc) ||
	    (pc >= (अचिन्हित दीर्घ) __copy_user_begin &&
	     pc < (अचिन्हित दीर्घ) __copy_user_end) ||
	    (pc >= (अचिन्हित दीर्घ) __bzero_begin &&
	     pc < (अचिन्हित दीर्घ) __bzero_end))
		pc = regs->u_regs[UREG_RETPC];
	वापस pc;
पूर्ण

EXPORT_SYMBOL(profile_pc);

अस्थिर u32 __iomem *master_l10_counter;

irqवापस_t notrace समयr_पूर्णांकerrupt(पूर्णांक dummy, व्योम *dev_id)
अणु
	अगर (समयr_cs_enabled) अणु
		ग_लिखो_seqlock(&समयr_cs_lock);
		समयr_cs_पूर्णांकernal_counter++;
		sparc_config.clear_घड़ी_irq();
		ग_लिखो_sequnlock(&समयr_cs_lock);
	पूर्ण अन्यथा अणु
		sparc_config.clear_घड़ी_irq();
	पूर्ण

	अगर (समयr_ce_enabled)
		समयr_ce.event_handler(&समयr_ce);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक समयr_ce_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	समयr_ce_enabled = 0;
	smp_mb();
	वापस 0;
पूर्ण

अटल पूर्णांक समयr_ce_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	समयr_ce_enabled = 1;
	smp_mb();
	वापस 0;
पूर्ण

अटल __init व्योम setup_समयr_ce(व्योम)
अणु
	काष्ठा घड़ी_event_device *ce = &समयr_ce;

	BUG_ON(smp_processor_id() != boot_cpu_id);

	ce->name     = "timer_ce";
	ce->rating   = 100;
	ce->features = CLOCK_EVT_FEAT_PERIODIC;
	ce->set_state_shutकरोwn = समयr_ce_shutकरोwn;
	ce->set_state_periodic = समयr_ce_set_periodic;
	ce->tick_resume = समयr_ce_set_periodic;
	ce->cpumask  = cpu_possible_mask;
	ce->shअगरt    = 32;
	ce->mult     = भाग_sc(sparc_config.घड़ी_rate, NSEC_PER_SEC,
	                      ce->shअगरt);
	घड़ीevents_रेजिस्टर_device(ce);
पूर्ण

अटल अचिन्हित पूर्णांक sbus_cycles_offset(व्योम)
अणु
	u32 val, offset;

	val = sbus_पढ़ोl(master_l10_counter);
	offset = (val >> TIMER_VALUE_SHIFT) & TIMER_VALUE_MASK;

	/* Limit hit? */
	अगर (val & TIMER_LIMIT_BIT)
		offset += sparc_config.cs_period;

	वापस offset;
पूर्ण

अटल u64 समयr_cs_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	अचिन्हित पूर्णांक seq, offset;
	u64 cycles;

	करो अणु
		seq = पढ़ो_seqbegin(&समयr_cs_lock);

		cycles = समयr_cs_पूर्णांकernal_counter;
		offset = sparc_config.get_cycles_offset();
	पूर्ण जबतक (पढ़ो_seqretry(&समयr_cs_lock, seq));

	/* Count असलolute cycles */
	cycles *= sparc_config.cs_period;
	cycles += offset;

	वापस cycles;
पूर्ण

अटल काष्ठा घड़ीsource समयr_cs = अणु
	.name	= "timer_cs",
	.rating	= 100,
	.पढ़ो	= समयr_cs_पढ़ो,
	.mask	= CLOCKSOURCE_MASK(64),
	.flags	= CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

अटल __init पूर्णांक setup_समयr_cs(व्योम)
अणु
	समयr_cs_enabled = 1;
	वापस घड़ीsource_रेजिस्टर_hz(&समयr_cs, sparc_config.घड़ी_rate);
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल पूर्णांक percpu_ce_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	पूर्णांक cpu = cpumask_first(evt->cpumask);

	sparc_config.load_profile_irq(cpu, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक percpu_ce_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	पूर्णांक cpu = cpumask_first(evt->cpumask);

	sparc_config.load_profile_irq(cpu, SBUS_CLOCK_RATE / HZ);
	वापस 0;
पूर्ण

अटल पूर्णांक percpu_ce_set_next_event(अचिन्हित दीर्घ delta,
				    काष्ठा घड़ी_event_device *evt)
अणु
	पूर्णांक cpu = cpumask_first(evt->cpumask);
	अचिन्हित पूर्णांक next = (अचिन्हित पूर्णांक)delta;

	sparc_config.load_profile_irq(cpu, next);
	वापस 0;
पूर्ण

व्योम रेजिस्टर_percpu_ce(पूर्णांक cpu)
अणु
	काष्ठा घड़ी_event_device *ce = &per_cpu(sparc32_घड़ीevent, cpu);
	अचिन्हित पूर्णांक features = CLOCK_EVT_FEAT_PERIODIC;

	अगर (sparc_config.features & FEAT_L14_ONESHOT)
		features |= CLOCK_EVT_FEAT_ONESHOT;

	ce->name           = "percpu_ce";
	ce->rating         = 200;
	ce->features       = features;
	ce->set_state_shutकरोwn = percpu_ce_shutकरोwn;
	ce->set_state_periodic = percpu_ce_set_periodic;
	ce->set_state_oneshot = percpu_ce_shutकरोwn;
	ce->set_next_event = percpu_ce_set_next_event;
	ce->cpumask        = cpumask_of(cpu);
	ce->shअगरt          = 32;
	ce->mult           = भाग_sc(sparc_config.घड़ी_rate, NSEC_PER_SEC,
	                            ce->shअगरt);
	ce->max_delta_ns   = घड़ीevent_delta2ns(sparc_config.घड़ी_rate, ce);
	ce->max_delta_ticks = (अचिन्हित दीर्घ)sparc_config.घड़ी_rate;
	ce->min_delta_ns   = घड़ीevent_delta2ns(100, ce);
	ce->min_delta_ticks = 100;

	घड़ीevents_रेजिस्टर_device(ce);
पूर्ण
#पूर्ण_अगर

अटल अचिन्हित अक्षर mostek_पढ़ो_byte(काष्ठा device *dev, u32 ofs)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा m48t59_plat_data *pdata = pdev->dev.platक्रमm_data;

	वापस पढ़ोb(pdata->ioaddr + ofs);
पूर्ण

अटल व्योम mostek_ग_लिखो_byte(काष्ठा device *dev, u32 ofs, u8 val)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा m48t59_plat_data *pdata = pdev->dev.platक्रमm_data;

	ग_लिखोb(val, pdata->ioaddr + ofs);
पूर्ण

अटल काष्ठा m48t59_plat_data m48t59_data = अणु
	.पढ़ो_byte = mostek_पढ़ो_byte,
	.ग_लिखो_byte = mostek_ग_लिखो_byte,
पूर्ण;

/* resource is set at runसमय */
अटल काष्ठा platक्रमm_device m48t59_rtc = अणु
	.name		= "rtc-m48t59",
	.id		= 0,
	.num_resources	= 1,
	.dev	= अणु
		.platक्रमm_data = &m48t59_data,
	पूर्ण,
पूर्ण;

अटल पूर्णांक घड़ी_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा device_node *dp = op->dev.of_node;
	स्थिर अक्षर *model = of_get_property(dp, "model", शून्य);

	अगर (!model)
		वापस -ENODEV;

	/* Only the primary RTC has an address property */
	अगर (!of_find_property(dp, "address", शून्य))
		वापस -ENODEV;

	m48t59_rtc.resource = &op->resource[0];
	अगर (!म_भेद(model, "mk48t02")) अणु
		/* Map the घड़ी रेजिस्टर io area पढ़ो-only */
		m48t59_data.ioaddr = of_ioremap(&op->resource[0], 0,
						2048, "rtc-m48t59");
		m48t59_data.type = M48T59RTC_TYPE_M48T02;
	पूर्ण अन्यथा अगर (!म_भेद(model, "mk48t08")) अणु
		m48t59_data.ioaddr = of_ioremap(&op->resource[0], 0,
						8192, "rtc-m48t59");
		m48t59_data.type = M48T59RTC_TYPE_M48T08;
	पूर्ण अन्यथा
		वापस -ENODEV;

	अगर (platक्रमm_device_रेजिस्टर(&m48t59_rtc) < 0)
		prपूर्णांकk(KERN_ERR "Registering RTC device failed\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id घड़ी_match[] = अणु
	अणु
		.name = "eeprom",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver घड़ी_driver = अणु
	.probe		= घड़ी_probe,
	.driver = अणु
		.name = "rtc",
		.of_match_table = घड़ी_match,
	पूर्ण,
पूर्ण;


/* Probe क्रम the mostek real समय घड़ी chip. */
अटल पूर्णांक __init घड़ी_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&घड़ी_driver);
पूर्ण
/* Must be after subsys_initcall() so that busses are probed.  Must
 * be beक्रमe device_initcall() because things like the RTC driver
 * need to see the घड़ी रेजिस्टरs.
 */
fs_initcall(घड़ी_init);

अटल व्योम __init sparc32_late_समय_init(व्योम)
अणु
	अगर (sparc_config.features & FEAT_L10_CLOCKEVENT)
		setup_समयr_ce();
	अगर (sparc_config.features & FEAT_L10_CLOCKSOURCE)
		setup_समयr_cs();
#अगर_घोषित CONFIG_SMP
	रेजिस्टर_percpu_ce(smp_processor_id());
#पूर्ण_अगर
पूर्ण

अटल व्योम __init sbus_समय_init(व्योम)
अणु
	sparc_config.get_cycles_offset = sbus_cycles_offset;
	sparc_config.init_समयrs();
पूर्ण

व्योम __init समय_init(व्योम)
अणु
	sparc_config.features = 0;
	late_समय_init = sparc32_late_समय_init;

	अगर (pcic_present())
		pci_समय_init();
	अन्यथा
		sbus_समय_init();
पूर्ण

