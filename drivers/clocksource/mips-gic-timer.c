<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2012 MIPS Technologies, Inc.  All rights reserved.
 */

#घोषणा pr_fmt(fmt) "mips-gic-timer: " fmt

#समावेश <linux/clk.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/cpu.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/percpu.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/smp.h>
#समावेश <linux/समय.स>
#समावेश <यंत्र/mips-cps.h>

अटल DEFINE_PER_CPU(काष्ठा घड़ी_event_device, gic_घड़ीevent_device);
अटल पूर्णांक gic_समयr_irq;
अटल अचिन्हित पूर्णांक gic_frequency;
अटल bool __पढ़ो_mostly gic_घड़ी_unstable;

अटल व्योम gic_घड़ीsource_unstable(अक्षर *reason);

अटल u64 notrace gic_पढ़ो_count_2x32(व्योम)
अणु
	अचिन्हित पूर्णांक hi, hi2, lo;

	करो अणु
		hi = पढ़ो_gic_counter_32h();
		lo = पढ़ो_gic_counter_32l();
		hi2 = पढ़ो_gic_counter_32h();
	पूर्ण जबतक (hi2 != hi);

	वापस (((u64) hi) << 32) + lo;
पूर्ण

अटल u64 notrace gic_पढ़ो_count_64(व्योम)
अणु
	वापस पढ़ो_gic_counter();
पूर्ण

अटल u64 notrace gic_पढ़ो_count(व्योम)
अणु
	अगर (mips_cm_is64)
		वापस gic_पढ़ो_count_64();

	वापस gic_पढ़ो_count_2x32();
पूर्ण

अटल पूर्णांक gic_next_event(अचिन्हित दीर्घ delta, काष्ठा घड़ी_event_device *evt)
अणु
	पूर्णांक cpu = cpumask_first(evt->cpumask);
	u64 cnt;
	पूर्णांक res;

	cnt = gic_पढ़ो_count();
	cnt += (u64)delta;
	अगर (cpu == raw_smp_processor_id()) अणु
		ग_लिखो_gic_vl_compare(cnt);
	पूर्ण अन्यथा अणु
		ग_लिखो_gic_vl_other(mips_cm_vp_id(cpu));
		ग_लिखो_gic_vo_compare(cnt);
	पूर्ण
	res = ((पूर्णांक)(gic_पढ़ो_count() - cnt) >= 0) ? -ETIME : 0;
	वापस res;
पूर्ण

अटल irqवापस_t gic_compare_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *cd = dev_id;

	ग_लिखो_gic_vl_compare(पढ़ो_gic_vl_compare());
	cd->event_handler(cd);
	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा irqaction gic_compare_irqaction = अणु
	.handler = gic_compare_पूर्णांकerrupt,
	.percpu_dev_id = &gic_घड़ीevent_device,
	.flags = IRQF_PERCPU | IRQF_TIMER,
	.name = "timer",
पूर्ण;

अटल व्योम gic_घड़ीevent_cpu_init(अचिन्हित पूर्णांक cpu,
				    काष्ठा घड़ी_event_device *cd)
अणु
	cd->name		= "MIPS GIC";
	cd->features		= CLOCK_EVT_FEAT_ONESHOT |
				  CLOCK_EVT_FEAT_C3STOP;

	cd->rating		= 350;
	cd->irq			= gic_समयr_irq;
	cd->cpumask		= cpumask_of(cpu);
	cd->set_next_event	= gic_next_event;

	घड़ीevents_config_and_रेजिस्टर(cd, gic_frequency, 0x300, 0x7fffffff);

	enable_percpu_irq(gic_समयr_irq, IRQ_TYPE_NONE);
पूर्ण

अटल व्योम gic_घड़ीevent_cpu_निकास(काष्ठा घड़ी_event_device *cd)
अणु
	disable_percpu_irq(gic_समयr_irq);
पूर्ण

अटल व्योम gic_update_frequency(व्योम *data)
अणु
	अचिन्हित दीर्घ rate = (अचिन्हित दीर्घ)data;

	घड़ीevents_update_freq(this_cpu_ptr(&gic_घड़ीevent_device), rate);
पूर्ण

अटल पूर्णांक gic_starting_cpu(अचिन्हित पूर्णांक cpu)
अणु
	gic_घड़ीevent_cpu_init(cpu, this_cpu_ptr(&gic_घड़ीevent_device));
	वापस 0;
पूर्ण

अटल पूर्णांक gic_clk_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ action,
			    व्योम *data)
अणु
	काष्ठा clk_notअगरier_data *cnd = data;

	अगर (action == POST_RATE_CHANGE) अणु
		gic_घड़ीsource_unstable("ref clock rate change");
		on_each_cpu(gic_update_frequency, (व्योम *)cnd->new_rate, 1);
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक gic_dying_cpu(अचिन्हित पूर्णांक cpu)
अणु
	gic_घड़ीevent_cpu_निकास(this_cpu_ptr(&gic_घड़ीevent_device));
	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block gic_clk_nb = अणु
	.notअगरier_call = gic_clk_notअगरier,
पूर्ण;

अटल पूर्णांक gic_घड़ीevent_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!gic_frequency)
		वापस -ENXIO;

	ret = setup_percpu_irq(gic_समयr_irq, &gic_compare_irqaction);
	अगर (ret < 0) अणु
		pr_err("IRQ %d setup failed (%d)\n", gic_समयr_irq, ret);
		वापस ret;
	पूर्ण

	cpuhp_setup_state(CPUHP_AP_MIPS_GIC_TIMER_STARTING,
			  "clockevents/mips/gic/timer:starting",
			  gic_starting_cpu, gic_dying_cpu);
	वापस 0;
पूर्ण

अटल u64 gic_hpt_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	वापस gic_पढ़ो_count();
पूर्ण

अटल काष्ठा घड़ीsource gic_घड़ीsource = अणु
	.name			= "GIC",
	.पढ़ो			= gic_hpt_पढ़ो,
	.flags			= CLOCK_SOURCE_IS_CONTINUOUS,
	.vdso_घड़ी_mode	= VDSO_CLOCKMODE_GIC,
पूर्ण;

अटल व्योम gic_घड़ीsource_unstable(अक्षर *reason)
अणु
	अगर (gic_घड़ी_unstable)
		वापस;

	gic_घड़ी_unstable = true;

	pr_info("GIC timer is unstable due to %s\n", reason);

	घड़ीsource_mark_unstable(&gic_घड़ीsource);
पूर्ण

अटल पूर्णांक __init __gic_घड़ीsource_init(व्योम)
अणु
	अचिन्हित पूर्णांक count_width;
	पूर्णांक ret;

	/* Set घड़ीsource mask. */
	count_width = पढ़ो_gic_config() & GIC_CONFIG_COUNTBITS;
	count_width >>= __ffs(GIC_CONFIG_COUNTBITS);
	count_width *= 4;
	count_width += 32;
	gic_घड़ीsource.mask = CLOCKSOURCE_MASK(count_width);

	/* Calculate a somewhat reasonable rating value. */
	gic_घड़ीsource.rating = 200 + gic_frequency / 10000000;

	ret = घड़ीsource_रेजिस्टर_hz(&gic_घड़ीsource, gic_frequency);
	अगर (ret < 0)
		pr_warn("Unable to register clocksource\n");

	वापस ret;
पूर्ण

अटल पूर्णांक __init gic_घड़ीsource_of_init(काष्ठा device_node *node)
अणु
	काष्ठा clk *clk;
	पूर्णांक ret;

	अगर (!mips_gic_present() || !node->parent ||
	    !of_device_is_compatible(node->parent, "mti,gic")) अणु
		pr_warn("No DT definition\n");
		वापस -ENXIO;
	पूर्ण

	clk = of_clk_get(node, 0);
	अगर (!IS_ERR(clk)) अणु
		ret = clk_prepare_enable(clk);
		अगर (ret < 0) अणु
			pr_err("Failed to enable clock\n");
			clk_put(clk);
			वापस ret;
		पूर्ण

		gic_frequency = clk_get_rate(clk);
	पूर्ण अन्यथा अगर (of_property_पढ़ो_u32(node, "clock-frequency",
					&gic_frequency)) अणु
		pr_err("Frequency not specified\n");
		वापस -EINVAL;
	पूर्ण
	gic_समयr_irq = irq_of_parse_and_map(node, 0);
	अगर (!gic_समयr_irq) अणु
		pr_err("IRQ not specified\n");
		वापस -EINVAL;
	पूर्ण

	ret = __gic_घड़ीsource_init();
	अगर (ret)
		वापस ret;

	ret = gic_घड़ीevent_init();
	अगर (!ret && !IS_ERR(clk)) अणु
		अगर (clk_notअगरier_रेजिस्टर(clk, &gic_clk_nb) < 0)
			pr_warn("Unable to register clock notifier\n");
	पूर्ण

	/* And finally start the counter */
	clear_gic_config(GIC_CONFIG_COUNTSTOP);

	/*
	 * It's safe to use the MIPS GIC समयr as a sched घड़ी source only अगर
	 * its ticks are stable, which is true on either the platक्रमms with
	 * stable CPU frequency or on the platक्रमms with CM3 and CPU frequency
	 * change perक्रमmed by the CPC core घड़ीs भागider.
	 */
	अगर (mips_cm_revision() >= CM_REV_CM3 || !IS_ENABLED(CONFIG_CPU_FREQ)) अणु
		sched_घड़ी_रेजिस्टर(mips_cm_is64 ?
				     gic_पढ़ो_count_64 : gic_पढ़ो_count_2x32,
				     64, gic_frequency);
	पूर्ण

	वापस 0;
पूर्ण
TIMER_OF_DECLARE(mips_gic_समयr, "mti,gic-timer",
		       gic_घड़ीsource_of_init);
