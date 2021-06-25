<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2007 MIPS Technologies, Inc.
 * Copyright (C) 2007 Ralf Baechle <ralf@linux-mips.org>
 */
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/percpu.h>
#समावेश <linux/smp.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/cevt-r4k.h>

अटल पूर्णांक mips_next_event(अचिन्हित दीर्घ delta,
			   काष्ठा घड़ी_event_device *evt)
अणु
	अचिन्हित पूर्णांक cnt;
	पूर्णांक res;

	cnt = पढ़ो_c0_count();
	cnt += delta;
	ग_लिखो_c0_compare(cnt);
	res = ((पूर्णांक)(पढ़ो_c0_count() - cnt) >= 0) ? -ETIME : 0;
	वापस res;
पूर्ण

/**
 * calculate_min_delta() - Calculate a good minimum delta क्रम mips_next_event().
 *
 * Running under भवisation can पूर्णांकroduce overhead पूर्णांकo mips_next_event() in
 * the क्रमm of hypervisor emulation of CP0_Count/CP0_Compare रेजिस्टरs,
 * potentially with an unnatural frequency, which makes a fixed min_delta_ns
 * value inappropriate as it may be too small.
 *
 * It can also पूर्णांकroduce occasional latency from the guest being descheduled.
 *
 * This function calculates a good minimum delta based roughly on the 75th
 * percentile of the समय taken to करो the mips_next_event() sequence, in order
 * to handle potentially higher overhead जबतक also eliminating outliers due to
 * unpredictable hypervisor latency (which can be handled by retries).
 *
 * Return:	An appropriate minimum delta क्रम the घड़ी event device.
 */
अटल अचिन्हित पूर्णांक calculate_min_delta(व्योम)
अणु
	अचिन्हित पूर्णांक cnt, i, j, k, l;
	अचिन्हित पूर्णांक buf1[4], buf2[3];
	अचिन्हित पूर्णांक min_delta;

	/*
	 * Calculate the median of 5 75th percentiles of 5 samples of how दीर्घ
	 * it takes to set CP0_Compare = CP0_Count + delta.
	 */
	क्रम (i = 0; i < 5; ++i) अणु
		क्रम (j = 0; j < 5; ++j) अणु
			/*
			 * This is like the code in mips_next_event(), and
			 * directly measures the borderline "safe" delta.
			 */
			cnt = पढ़ो_c0_count();
			ग_लिखो_c0_compare(cnt);
			cnt = पढ़ो_c0_count() - cnt;

			/* Sorted insert पूर्णांकo buf1 */
			क्रम (k = 0; k < j; ++k) अणु
				अगर (cnt < buf1[k]) अणु
					l = min_t(अचिन्हित पूर्णांक,
						  j, ARRAY_SIZE(buf1) - 1);
					क्रम (; l > k; --l)
						buf1[l] = buf1[l - 1];
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (k < ARRAY_SIZE(buf1))
				buf1[k] = cnt;
		पूर्ण

		/* Sorted insert of 75th percentile पूर्णांकo buf2 */
		क्रम (k = 0; k < i && k < ARRAY_SIZE(buf2); ++k) अणु
			अगर (buf1[ARRAY_SIZE(buf1) - 1] < buf2[k]) अणु
				l = min_t(अचिन्हित पूर्णांक,
					  i, ARRAY_SIZE(buf2) - 1);
				क्रम (; l > k; --l)
					buf2[l] = buf2[l - 1];
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (k < ARRAY_SIZE(buf2))
			buf2[k] = buf1[ARRAY_SIZE(buf1) - 1];
	पूर्ण

	/* Use 2 * median of 75th percentiles */
	min_delta = buf2[ARRAY_SIZE(buf2) - 1] * 2;

	/* Don't go too low */
	अगर (min_delta < 0x300)
		min_delta = 0x300;

	pr_debug("%s: median 75th percentile=%#x, min_delta=%#x\n",
		 __func__, buf2[ARRAY_SIZE(buf2) - 1], min_delta);
	वापस min_delta;
पूर्ण

DEFINE_PER_CPU(काष्ठा घड़ी_event_device, mips_घड़ीevent_device);
पूर्णांक cp0_समयr_irq_installed;

/*
 * Possibly handle a perक्रमmance counter पूर्णांकerrupt.
 * Return true अगर the समयr पूर्णांकerrupt should not be checked
 */
अटल अंतरभूत पूर्णांक handle_perf_irq(पूर्णांक r2)
अणु
	/*
	 * The perक्रमmance counter overflow पूर्णांकerrupt may be shared with the
	 * समयr पूर्णांकerrupt (cp0_perfcount_irq < 0). If it is and a
	 * perक्रमmance counter has overflowed (perf_irq() == IRQ_HANDLED)
	 * and we can't reliably determine अगर a counter पूर्णांकerrupt has also
	 * happened (!r2) then करोn't check क्रम a समयr पूर्णांकerrupt.
	 */
	वापस (cp0_perfcount_irq < 0) &&
		perf_irq() == IRQ_HANDLED &&
		!r2;
पूर्ण

irqवापस_t c0_compare_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	स्थिर पूर्णांक r2 = cpu_has_mips_r2_r6;
	काष्ठा घड़ी_event_device *cd;
	पूर्णांक cpu = smp_processor_id();

	/*
	 * Suckage alert:
	 * Beक्रमe R2 of the architecture there was no way to see अगर a
	 * perक्रमmance counter पूर्णांकerrupt was pending, so we have to run
	 * the perक्रमmance counter पूर्णांकerrupt handler anyway.
	 */
	अगर (handle_perf_irq(r2))
		वापस IRQ_HANDLED;

	/*
	 * The same applies to perक्रमmance counter पूर्णांकerrupts.	But with the
	 * above we now know that the reason we got here must be a समयr
	 * पूर्णांकerrupt.  Being the paranoiacs we are we check anyway.
	 */
	अगर (!r2 || (पढ़ो_c0_cause() & CAUSEF_TI)) अणु
		/* Clear Count/Compare Interrupt */
		ग_लिखो_c0_compare(पढ़ो_c0_compare());
		cd = &per_cpu(mips_घड़ीevent_device, cpu);
		cd->event_handler(cd);

		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

काष्ठा irqaction c0_compare_irqaction = अणु
	.handler = c0_compare_पूर्णांकerrupt,
	/*
	 * IRQF_SHARED: The समयr पूर्णांकerrupt may be shared with other पूर्णांकerrupts
	 * such as perf counter and FDC पूर्णांकerrupts.
	 */
	.flags = IRQF_PERCPU | IRQF_TIMER | IRQF_SHARED,
	.name = "timer",
पूर्ण;


व्योम mips_event_handler(काष्ठा घड़ी_event_device *dev)
अणु
पूर्ण

/*
 * FIXME: This करोesn't hold क्रम the relocated E9000 compare पूर्णांकerrupt.
 */
अटल पूर्णांक c0_compare_पूर्णांक_pending(व्योम)
अणु
	/* When cpu_has_mips_r2, this checks Cause.TI instead of Cause.IP7 */
	वापस (पढ़ो_c0_cause() >> cp0_compare_irq_shअगरt) & (1ul << CAUSEB_IP);
पूर्ण

/*
 * Compare पूर्णांकerrupt can be routed and latched outside the core,
 * so रुको up to worst हाल number of cycle counter ticks क्रम समयr पूर्णांकerrupt
 * changes to propagate to the cause रेजिस्टर.
 */
#घोषणा COMPARE_INT_SEEN_TICKS 50

पूर्णांक c0_compare_पूर्णांक_usable(व्योम)
अणु
	अचिन्हित पूर्णांक delta;
	अचिन्हित पूर्णांक cnt;

	/*
	 * IP7 alपढ़ोy pending?	 Try to clear it by acking the समयr.
	 */
	अगर (c0_compare_पूर्णांक_pending()) अणु
		cnt = पढ़ो_c0_count();
		ग_लिखो_c0_compare(cnt);
		back_to_back_c0_hazard();
		जबतक (पढ़ो_c0_count() < (cnt  + COMPARE_INT_SEEN_TICKS))
			अगर (!c0_compare_पूर्णांक_pending())
				अवरोध;
		अगर (c0_compare_पूर्णांक_pending())
			वापस 0;
	पूर्ण

	क्रम (delta = 0x10; delta <= 0x400000; delta <<= 1) अणु
		cnt = पढ़ो_c0_count();
		cnt += delta;
		ग_लिखो_c0_compare(cnt);
		back_to_back_c0_hazard();
		अगर ((पूर्णांक)(पढ़ो_c0_count() - cnt) < 0)
		    अवरोध;
		/* increase delta अगर the समयr was alपढ़ोy expired */
	पूर्ण

	जबतक ((पूर्णांक)(पढ़ो_c0_count() - cnt) <= 0)
		;	/* Wait क्रम expiry  */

	जबतक (पढ़ो_c0_count() < (cnt + COMPARE_INT_SEEN_TICKS))
		अगर (c0_compare_पूर्णांक_pending())
			अवरोध;
	अगर (!c0_compare_पूर्णांक_pending())
		वापस 0;
	cnt = पढ़ो_c0_count();
	ग_लिखो_c0_compare(cnt);
	back_to_back_c0_hazard();
	जबतक (पढ़ो_c0_count() < (cnt + COMPARE_INT_SEEN_TICKS))
		अगर (!c0_compare_पूर्णांक_pending())
			अवरोध;
	अगर (c0_compare_पूर्णांक_pending())
		वापस 0;

	/*
	 * Feels like a real count / compare समयr.
	 */
	वापस 1;
पूर्ण

अचिन्हित पूर्णांक __weak get_c0_compare_पूर्णांक(व्योम)
अणु
	वापस MIPS_CPU_IRQ_BASE + cp0_compare_irq;
पूर्ण

#अगर_घोषित CONFIG_CPU_FREQ

अटल अचिन्हित दीर्घ mips_ref_freq;

अटल पूर्णांक r4k_cpufreq_callback(काष्ठा notअगरier_block *nb,
				अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा cpufreq_freqs *freq = data;
	काष्ठा घड़ी_event_device *cd;
	अचिन्हित दीर्घ rate;
	पूर्णांक cpu;

	अगर (!mips_ref_freq)
		mips_ref_freq = freq->old;

	अगर (val == CPUFREQ_POSTCHANGE) अणु
		rate = cpufreq_scale(mips_hpt_frequency, mips_ref_freq,
				     freq->new);

		क्रम_each_cpu(cpu, freq->policy->cpus) अणु
			cd = &per_cpu(mips_घड़ीevent_device, cpu);

			घड़ीevents_update_freq(cd, rate);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block r4k_cpufreq_notअगरier = अणु
	.notअगरier_call  = r4k_cpufreq_callback,
पूर्ण;

अटल पूर्णांक __init r4k_रेजिस्टर_cpufreq_notअगरier(व्योम)
अणु
	वापस cpufreq_रेजिस्टर_notअगरier(&r4k_cpufreq_notअगरier,
					 CPUFREQ_TRANSITION_NOTIFIER);

पूर्ण
core_initcall(r4k_रेजिस्टर_cpufreq_notअगरier);

#पूर्ण_अगर /* !CONFIG_CPU_FREQ */

पूर्णांक r4k_घड़ीevent_init(व्योम)
अणु
	अचिन्हित दीर्घ flags = IRQF_PERCPU | IRQF_TIMER | IRQF_SHARED;
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	काष्ठा घड़ी_event_device *cd;
	अचिन्हित पूर्णांक irq, min_delta;

	अगर (!cpu_has_counter || !mips_hpt_frequency)
		वापस -ENXIO;

	अगर (!c0_compare_पूर्णांक_usable())
		वापस -ENXIO;

	/*
	 * With vectored पूर्णांकerrupts things are getting platक्रमm specअगरic.
	 * get_c0_compare_पूर्णांक is a hook to allow a platक्रमm to वापस the
	 * पूर्णांकerrupt number of its liking.
	 */
	irq = get_c0_compare_पूर्णांक();

	cd = &per_cpu(mips_घड़ीevent_device, cpu);

	cd->name		= "MIPS";
	cd->features		= CLOCK_EVT_FEAT_ONESHOT |
				  CLOCK_EVT_FEAT_C3STOP |
				  CLOCK_EVT_FEAT_PERCPU;

	min_delta		= calculate_min_delta();

	cd->rating		= 300;
	cd->irq			= irq;
	cd->cpumask		= cpumask_of(cpu);
	cd->set_next_event	= mips_next_event;
	cd->event_handler	= mips_event_handler;

	घड़ीevents_config_and_रेजिस्टर(cd, mips_hpt_frequency, min_delta, 0x7fffffff);

	अगर (cp0_समयr_irq_installed)
		वापस 0;

	cp0_समयr_irq_installed = 1;

	अगर (request_irq(irq, c0_compare_पूर्णांकerrupt, flags, "timer",
			c0_compare_पूर्णांकerrupt))
		pr_err("Failed to request irq %d (timer)\n", irq);

	वापस 0;
पूर्ण

