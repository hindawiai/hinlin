<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Detect hard lockups on a प्रणाली
 *
 * started by Don Zickus, Copyright (C) 2010 Red Hat, Inc.
 *
 * Note: Most of this code is borrowed heavily from the original softlockup
 * detector, so thanks to Ingo क्रम the initial implementation.
 * Some chunks also taken from the old x86-specअगरic nmi watchकरोg code, thanks
 * to those contributors as well.
 */

#घोषणा pr_fmt(fmt) "NMI watchdog: " fmt

#समावेश <linux/nmi.h>
#समावेश <linux/atomic.h>
#समावेश <linux/module.h>
#समावेश <linux/sched/debug.h>

#समावेश <यंत्र/irq_regs.h>
#समावेश <linux/perf_event.h>

अटल DEFINE_PER_CPU(bool, hard_watchकरोg_warn);
अटल DEFINE_PER_CPU(bool, watchकरोg_nmi_touch);
अटल DEFINE_PER_CPU(काष्ठा perf_event *, watchकरोg_ev);
अटल DEFINE_PER_CPU(काष्ठा perf_event *, dead_event);
अटल काष्ठा cpumask dead_events_mask;

अटल अचिन्हित दीर्घ hardlockup_allcpu_dumped;
अटल atomic_t watchकरोg_cpus = ATOMIC_INIT(0);

notrace व्योम arch_touch_nmi_watchकरोg(व्योम)
अणु
	/*
	 * Using __raw here because some code paths have
	 * preemption enabled.  If preemption is enabled
	 * then पूर्णांकerrupts should be enabled too, in which
	 * हाल we shouldn't have to worry about the watchकरोg
	 * going off.
	 */
	raw_cpu_ग_लिखो(watchकरोg_nmi_touch, true);
पूर्ण
EXPORT_SYMBOL(arch_touch_nmi_watchकरोg);

#अगर_घोषित CONFIG_HARDLOCKUP_CHECK_TIMESTAMP
अटल DEFINE_PER_CPU(kसमय_प्रकार, last_बारtamp);
अटल DEFINE_PER_CPU(अचिन्हित पूर्णांक, nmi_rearmed);
अटल kसमय_प्रकार watchकरोg_hrसमयr_sample_threshold __पढ़ो_mostly;

व्योम watchकरोg_update_hrसमयr_threshold(u64 period)
अणु
	/*
	 * The hrसमयr runs with a period of (watchकरोg_threshold * 2) / 5
	 *
	 * So it runs effectively with 2.5 बार the rate of the NMI
	 * watchकरोg. That means the hrसमयr should fire 2-3 बार beक्रमe
	 * the NMI watchकरोg expires. The NMI watchकरोg on x86 is based on
	 * unhalted CPU cycles, so अगर Turbo-Mode is enabled the CPU cycles
	 * might run way faster than expected and the NMI fires in a
	 * smaller period than the one deduced from the nominal CPU
	 * frequency. Depending on the Turbo-Mode factor this might be fast
	 * enough to get the NMI period smaller than the hrसमयr watchकरोg
	 * period and trigger false positives.
	 *
	 * The sample threshold is used to check in the NMI handler whether
	 * the minimum समय between two NMI samples has elapsed. That
	 * prevents false positives.
	 *
	 * Set this to 4/5 of the actual watchकरोg threshold period so the
	 * hrसमयr is guaranteed to fire at least once within the real
	 * watchकरोg threshold.
	 */
	watchकरोg_hrसमयr_sample_threshold = period * 2;
पूर्ण

अटल bool watchकरोg_check_बारtamp(व्योम)
अणु
	kसमय_प्रकार delta, now = kसमय_get_mono_fast_ns();

	delta = now - __this_cpu_पढ़ो(last_बारtamp);
	अगर (delta < watchकरोg_hrसमयr_sample_threshold) अणु
		/*
		 * If kसमय is jअगरfies based, a stalled समयr would prevent
		 * jअगरfies from being incremented and the filter would look
		 * at a stale बारtamp and never trigger.
		 */
		अगर (__this_cpu_inc_वापस(nmi_rearmed) < 10)
			वापस false;
	पूर्ण
	__this_cpu_ग_लिखो(nmi_rearmed, 0);
	__this_cpu_ग_लिखो(last_बारtamp, now);
	वापस true;
पूर्ण
#अन्यथा
अटल अंतरभूत bool watchकरोg_check_बारtamp(व्योम)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा perf_event_attr wd_hw_attr = अणु
	.type		= PERF_TYPE_HARDWARE,
	.config		= PERF_COUNT_HW_CPU_CYCLES,
	.size		= माप(काष्ठा perf_event_attr),
	.pinned		= 1,
	.disabled	= 1,
पूर्ण;

/* Callback function क्रम perf event subप्रणाली */
अटल व्योम watchकरोg_overflow_callback(काष्ठा perf_event *event,
				       काष्ठा perf_sample_data *data,
				       काष्ठा pt_regs *regs)
अणु
	/* Ensure the watchकरोg never माला_लो throttled */
	event->hw.पूर्णांकerrupts = 0;

	अगर (__this_cpu_पढ़ो(watchकरोg_nmi_touch) == true) अणु
		__this_cpu_ग_लिखो(watchकरोg_nmi_touch, false);
		वापस;
	पूर्ण

	अगर (!watchकरोg_check_बारtamp())
		वापस;

	/* check क्रम a hardlockup
	 * This is करोne by making sure our समयr पूर्णांकerrupt
	 * is incrementing.  The समयr पूर्णांकerrupt should have
	 * fired multiple बार beक्रमe we overflow'd.  If it hasn't
	 * then this is a good indication the cpu is stuck
	 */
	अगर (is_hardlockup()) अणु
		पूर्णांक this_cpu = smp_processor_id();

		/* only prपूर्णांक hardlockups once */
		अगर (__this_cpu_पढ़ो(hard_watchकरोg_warn) == true)
			वापस;

		pr_emerg("Watchdog detected hard LOCKUP on cpu %d\n",
			 this_cpu);
		prपूर्णांक_modules();
		prपूर्णांक_irqtrace_events(current);
		अगर (regs)
			show_regs(regs);
		अन्यथा
			dump_stack();

		/*
		 * Perक्रमm all-CPU dump only once to aव्योम multiple hardlockups
		 * generating पूर्णांकerleaving traces
		 */
		अगर (sysctl_hardlockup_all_cpu_backtrace &&
				!test_and_set_bit(0, &hardlockup_allcpu_dumped))
			trigger_allbutself_cpu_backtrace();

		अगर (hardlockup_panic)
			nmi_panic(regs, "Hard LOCKUP");

		__this_cpu_ग_लिखो(hard_watchकरोg_warn, true);
		वापस;
	पूर्ण

	__this_cpu_ग_लिखो(hard_watchकरोg_warn, false);
	वापस;
पूर्ण

अटल पूर्णांक hardlockup_detector_event_create(व्योम)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	काष्ठा perf_event_attr *wd_attr;
	काष्ठा perf_event *evt;

	wd_attr = &wd_hw_attr;
	wd_attr->sample_period = hw_nmi_get_sample_period(watchकरोg_thresh);

	/* Try to रेजिस्टर using hardware perf events */
	evt = perf_event_create_kernel_counter(wd_attr, cpu, शून्य,
					       watchकरोg_overflow_callback, शून्य);
	अगर (IS_ERR(evt)) अणु
		pr_debug("Perf event create on CPU %d failed with %ld\n", cpu,
			 PTR_ERR(evt));
		वापस PTR_ERR(evt);
	पूर्ण
	this_cpu_ग_लिखो(watchकरोg_ev, evt);
	वापस 0;
पूर्ण

/**
 * hardlockup_detector_perf_enable - Enable the local event
 */
व्योम hardlockup_detector_perf_enable(व्योम)
अणु
	अगर (hardlockup_detector_event_create())
		वापस;

	/* use original value क्रम check */
	अगर (!atomic_fetch_inc(&watchकरोg_cpus))
		pr_info("Enabled. Permanently consumes one hw-PMU counter.\n");

	perf_event_enable(this_cpu_पढ़ो(watchकरोg_ev));
पूर्ण

/**
 * hardlockup_detector_perf_disable - Disable the local event
 */
व्योम hardlockup_detector_perf_disable(व्योम)
अणु
	काष्ठा perf_event *event = this_cpu_पढ़ो(watchकरोg_ev);

	अगर (event) अणु
		perf_event_disable(event);
		this_cpu_ग_लिखो(watchकरोg_ev, शून्य);
		this_cpu_ग_लिखो(dead_event, event);
		cpumask_set_cpu(smp_processor_id(), &dead_events_mask);
		atomic_dec(&watchकरोg_cpus);
	पूर्ण
पूर्ण

/**
 * hardlockup_detector_perf_cleanup - Cleanup disabled events and destroy them
 *
 * Called from lockup_detector_cleanup(). Serialized by the caller.
 */
व्योम hardlockup_detector_perf_cleanup(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_cpu(cpu, &dead_events_mask) अणु
		काष्ठा perf_event *event = per_cpu(dead_event, cpu);

		/*
		 * Required because क्रम_each_cpu() reports  unconditionally
		 * CPU0 as set on UP kernels. Sigh.
		 */
		अगर (event)
			perf_event_release_kernel(event);
		per_cpu(dead_event, cpu) = शून्य;
	पूर्ण
	cpumask_clear(&dead_events_mask);
पूर्ण

/**
 * hardlockup_detector_perf_stop - Globally stop watchकरोg events
 *
 * Special पूर्णांकerface क्रम x86 to handle the perf HT bug.
 */
व्योम __init hardlockup_detector_perf_stop(व्योम)
अणु
	पूर्णांक cpu;

	lockdep_निश्चित_cpus_held();

	क्रम_each_online_cpu(cpu) अणु
		काष्ठा perf_event *event = per_cpu(watchकरोg_ev, cpu);

		अगर (event)
			perf_event_disable(event);
	पूर्ण
पूर्ण

/**
 * hardlockup_detector_perf_restart - Globally restart watchकरोg events
 *
 * Special पूर्णांकerface क्रम x86 to handle the perf HT bug.
 */
व्योम __init hardlockup_detector_perf_restart(व्योम)
अणु
	पूर्णांक cpu;

	lockdep_निश्चित_cpus_held();

	अगर (!(watchकरोg_enabled & NMI_WATCHDOG_ENABLED))
		वापस;

	क्रम_each_online_cpu(cpu) अणु
		काष्ठा perf_event *event = per_cpu(watchकरोg_ev, cpu);

		अगर (event)
			perf_event_enable(event);
	पूर्ण
पूर्ण

/**
 * hardlockup_detector_perf_init - Probe whether NMI event is available at all
 */
पूर्णांक __init hardlockup_detector_perf_init(व्योम)
अणु
	पूर्णांक ret = hardlockup_detector_event_create();

	अगर (ret) अणु
		pr_info("Perf NMI watchdog permanently disabled\n");
	पूर्ण अन्यथा अणु
		perf_event_release_kernel(this_cpu_पढ़ो(watchकरोg_ev));
		this_cpu_ग_लिखो(watchकरोg_ev, शून्य);
	पूर्ण
	वापस ret;
पूर्ण
