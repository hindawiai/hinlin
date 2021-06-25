<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Detect hard and soft lockups on a प्रणाली
 *
 * started by Don Zickus, Copyright (C) 2010 Red Hat, Inc.
 *
 * Note: Most of this code is borrowed heavily from the original softlockup
 * detector, so thanks to Ingo क्रम the initial implementation.
 * Some chunks also taken from the old x86-specअगरic nmi watchकरोg code, thanks
 * to those contributors as well.
 */

#घोषणा pr_fmt(fmt) "watchdog: " fmt

#समावेश <linux/mm.h>
#समावेश <linux/cpu.h>
#समावेश <linux/nmi.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/tick.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/isolation.h>
#समावेश <linux/stop_machine.h>

#समावेश <यंत्र/irq_regs.h>
#समावेश <linux/kvm_para.h>

अटल DEFINE_MUTEX(watchकरोg_mutex);

#अगर defined(CONFIG_HARDLOCKUP_DETECTOR) || defined(CONFIG_HAVE_NMI_WATCHDOG)
# define WATCHDOG_DEFAULT	(SOFT_WATCHDOG_ENABLED | NMI_WATCHDOG_ENABLED)
# define NMI_WATCHDOG_DEFAULT	1
#अन्यथा
# define WATCHDOG_DEFAULT	(SOFT_WATCHDOG_ENABLED)
# define NMI_WATCHDOG_DEFAULT	0
#पूर्ण_अगर

अचिन्हित दीर्घ __पढ़ो_mostly watchकरोg_enabled;
पूर्णांक __पढ़ो_mostly watchकरोg_user_enabled = 1;
पूर्णांक __पढ़ो_mostly nmi_watchकरोg_user_enabled = NMI_WATCHDOG_DEFAULT;
पूर्णांक __पढ़ो_mostly soft_watchकरोg_user_enabled = 1;
पूर्णांक __पढ़ो_mostly watchकरोg_thresh = 10;
अटल पूर्णांक __पढ़ो_mostly nmi_watchकरोg_available;

काष्ठा cpumask watchकरोg_cpumask __पढ़ो_mostly;
अचिन्हित दीर्घ *watchकरोg_cpumask_bits = cpumask_bits(&watchकरोg_cpumask);

#अगर_घोषित CONFIG_HARDLOCKUP_DETECTOR

# अगरdef CONFIG_SMP
पूर्णांक __पढ़ो_mostly sysctl_hardlockup_all_cpu_backtrace;
# endअगर /* CONFIG_SMP */

/*
 * Should we panic when a soft-lockup or hard-lockup occurs:
 */
अचिन्हित पूर्णांक __पढ़ो_mostly hardlockup_panic =
			CONFIG_BOOTPARAM_HARDLOCKUP_PANIC_VALUE;
/*
 * We may not want to enable hard lockup detection by शेष in all हालs,
 * क्रम example when running the kernel as a guest on a hypervisor. In these
 * हालs this function can be called to disable hard lockup detection. This
 * function should only be executed once by the boot processor beक्रमe the
 * kernel command line parameters are parsed, because otherwise it is not
 * possible to override this in hardlockup_panic_setup().
 */
व्योम __init hardlockup_detector_disable(व्योम)
अणु
	nmi_watchकरोg_user_enabled = 0;
पूर्ण

अटल पूर्णांक __init hardlockup_panic_setup(अक्षर *str)
अणु
	अगर (!म_भेदन(str, "panic", 5))
		hardlockup_panic = 1;
	अन्यथा अगर (!म_भेदन(str, "nopanic", 7))
		hardlockup_panic = 0;
	अन्यथा अगर (!म_भेदन(str, "0", 1))
		nmi_watchकरोg_user_enabled = 0;
	अन्यथा अगर (!म_भेदन(str, "1", 1))
		nmi_watchकरोg_user_enabled = 1;
	वापस 1;
पूर्ण
__setup("nmi_watchdog=", hardlockup_panic_setup);

#पूर्ण_अगर /* CONFIG_HARDLOCKUP_DETECTOR */

/*
 * These functions can be overridden अगर an architecture implements its
 * own hardlockup detector.
 *
 * watchकरोg_nmi_enable/disable can be implemented to start and stop when
 * softlockup watchकरोg thपढ़ोs start and stop. The arch must select the
 * SOFTLOCKUP_DETECTOR Kconfig.
 */
पूर्णांक __weak watchकरोg_nmi_enable(अचिन्हित पूर्णांक cpu)
अणु
	hardlockup_detector_perf_enable();
	वापस 0;
पूर्ण

व्योम __weak watchकरोg_nmi_disable(अचिन्हित पूर्णांक cpu)
अणु
	hardlockup_detector_perf_disable();
पूर्ण

/* Return 0, अगर a NMI watchकरोg is available. Error code otherwise */
पूर्णांक __weak __init watchकरोg_nmi_probe(व्योम)
अणु
	वापस hardlockup_detector_perf_init();
पूर्ण

/**
 * watchकरोg_nmi_stop - Stop the watchकरोg क्रम reconfiguration
 *
 * The reconfiguration steps are:
 * watchकरोg_nmi_stop();
 * update_variables();
 * watchकरोg_nmi_start();
 */
व्योम __weak watchकरोg_nmi_stop(व्योम) अणु पूर्ण

/**
 * watchकरोg_nmi_start - Start the watchकरोg after reconfiguration
 *
 * Counterpart to watchकरोg_nmi_stop().
 *
 * The following variables have been updated in update_variables() and
 * contain the currently valid configuration:
 * - watchकरोg_enabled
 * - watchकरोg_thresh
 * - watchकरोg_cpumask
 */
व्योम __weak watchकरोg_nmi_start(व्योम) अणु पूर्ण

/**
 * lockup_detector_update_enable - Update the sysctl enable bit
 *
 * Caller needs to make sure that the NMI/perf watchकरोgs are off, so this
 * can't race with watchकरोg_nmi_disable().
 */
अटल व्योम lockup_detector_update_enable(व्योम)
अणु
	watchकरोg_enabled = 0;
	अगर (!watchकरोg_user_enabled)
		वापस;
	अगर (nmi_watchकरोg_available && nmi_watchकरोg_user_enabled)
		watchकरोg_enabled |= NMI_WATCHDOG_ENABLED;
	अगर (soft_watchकरोg_user_enabled)
		watchकरोg_enabled |= SOFT_WATCHDOG_ENABLED;
पूर्ण

#अगर_घोषित CONFIG_SOFTLOCKUP_DETECTOR

/*
 * Delay the soflockup report when running a known slow code.
 * It करोes _not_ affect the बारtamp of the last successdul reschedule.
 */
#घोषणा SOFTLOCKUP_DELAY_REPORT	अच_दीर्घ_उच्च

#अगर_घोषित CONFIG_SMP
पूर्णांक __पढ़ो_mostly sysctl_softlockup_all_cpu_backtrace;
#पूर्ण_अगर

अटल काष्ठा cpumask watchकरोg_allowed_mask __पढ़ो_mostly;

/* Global variables, exported क्रम sysctl */
अचिन्हित पूर्णांक __पढ़ो_mostly softlockup_panic =
			CONFIG_BOOTPARAM_SOFTLOCKUP_PANIC_VALUE;

अटल bool softlockup_initialized __पढ़ो_mostly;
अटल u64 __पढ़ो_mostly sample_period;

/* Timestamp taken after the last successful reschedule. */
अटल DEFINE_PER_CPU(अचिन्हित दीर्घ, watchकरोg_touch_ts);
/* Timestamp of the last softlockup report. */
अटल DEFINE_PER_CPU(अचिन्हित दीर्घ, watchकरोg_report_ts);
अटल DEFINE_PER_CPU(काष्ठा hrसमयr, watchकरोg_hrसमयr);
अटल DEFINE_PER_CPU(bool, softlockup_touch_sync);
अटल DEFINE_PER_CPU(अचिन्हित दीर्घ, hrसमयr_पूर्णांकerrupts);
अटल DEFINE_PER_CPU(अचिन्हित दीर्घ, hrसमयr_पूर्णांकerrupts_saved);
अटल अचिन्हित दीर्घ soft_lockup_nmi_warn;

अटल पूर्णांक __init nowatchकरोg_setup(अक्षर *str)
अणु
	watchकरोg_user_enabled = 0;
	वापस 1;
पूर्ण
__setup("nowatchdog", nowatchकरोg_setup);

अटल पूर्णांक __init nosoftlockup_setup(अक्षर *str)
अणु
	soft_watchकरोg_user_enabled = 0;
	वापस 1;
पूर्ण
__setup("nosoftlockup", nosoftlockup_setup);

अटल पूर्णांक __init watchकरोg_thresh_setup(अक्षर *str)
अणु
	get_option(&str, &watchकरोg_thresh);
	वापस 1;
पूर्ण
__setup("watchdog_thresh=", watchकरोg_thresh_setup);

अटल व्योम __lockup_detector_cleanup(व्योम);

/*
 * Hard-lockup warnings should be triggered after just a few seconds. Soft-
 * lockups can have false positives under extreme conditions. So we generally
 * want a higher threshold क्रम soft lockups than क्रम hard lockups. So we couple
 * the thresholds with a factor: we make the soft threshold twice the amount of
 * समय the hard threshold is.
 */
अटल पूर्णांक get_softlockup_thresh(व्योम)
अणु
	वापस watchकरोg_thresh * 2;
पूर्ण

/*
 * Returns seconds, approximately.  We करोn't need nanosecond
 * resolution, and we करोn't need to waste समय with a big भागide when
 * 2^30ns == 1.074s.
 */
अटल अचिन्हित दीर्घ get_बारtamp(व्योम)
अणु
	वापस running_घड़ी() >> 30LL;  /* 2^30 ~= 10^9 */
पूर्ण

अटल व्योम set_sample_period(व्योम)
अणु
	/*
	 * convert watchकरोg_thresh from seconds to ns
	 * the भागide by 5 is to give hrसमयr several chances (two
	 * or three with the current relation between the soft
	 * and hard thresholds) to increment beक्रमe the
	 * hardlockup detector generates a warning
	 */
	sample_period = get_softlockup_thresh() * ((u64)NSEC_PER_SEC / 5);
	watchकरोg_update_hrसमयr_threshold(sample_period);
पूर्ण

अटल व्योम update_report_ts(व्योम)
अणु
	__this_cpu_ग_लिखो(watchकरोg_report_ts, get_बारtamp());
पूर्ण

/* Commands क्रम resetting the watchकरोg */
अटल व्योम update_touch_ts(व्योम)
अणु
	__this_cpu_ग_लिखो(watchकरोg_touch_ts, get_बारtamp());
	update_report_ts();
पूर्ण

/**
 * touch_softlockup_watchकरोg_sched - touch watchकरोg on scheduler stalls
 *
 * Call when the scheduler may have stalled क्रम legitimate reasons
 * preventing the watchकरोg task from executing - e.g. the scheduler
 * entering idle state.  This should only be used क्रम scheduler events.
 * Use touch_softlockup_watchकरोg() क्रम everything अन्यथा.
 */
notrace व्योम touch_softlockup_watchकरोg_sched(व्योम)
अणु
	/*
	 * Preemption can be enabled.  It करोesn't matter which CPU's watchकरोg
	 * report period माला_लो restarted here, so use the raw_ operation.
	 */
	raw_cpu_ग_लिखो(watchकरोg_report_ts, SOFTLOCKUP_DELAY_REPORT);
पूर्ण

notrace व्योम touch_softlockup_watchकरोg(व्योम)
अणु
	touch_softlockup_watchकरोg_sched();
	wq_watchकरोg_touch(raw_smp_processor_id());
पूर्ण
EXPORT_SYMBOL(touch_softlockup_watchकरोg);

व्योम touch_all_softlockup_watchकरोgs(व्योम)
अणु
	पूर्णांक cpu;

	/*
	 * watchकरोg_mutex cannpt be taken here, as this might be called
	 * from (soft)पूर्णांकerrupt context, so the access to
	 * watchकरोg_allowed_cpumask might race with a concurrent update.
	 *
	 * The watchकरोg समय stamp can race against a concurrent real
	 * update as well, the only side effect might be a cycle delay क्रम
	 * the softlockup check.
	 */
	क्रम_each_cpu(cpu, &watchकरोg_allowed_mask) अणु
		per_cpu(watchकरोg_report_ts, cpu) = SOFTLOCKUP_DELAY_REPORT;
		wq_watchकरोg_touch(cpu);
	पूर्ण
पूर्ण

व्योम touch_softlockup_watchकरोg_sync(व्योम)
अणु
	__this_cpu_ग_लिखो(softlockup_touch_sync, true);
	__this_cpu_ग_लिखो(watchकरोg_report_ts, SOFTLOCKUP_DELAY_REPORT);
पूर्ण

अटल पूर्णांक is_softlockup(अचिन्हित दीर्घ touch_ts,
			 अचिन्हित दीर्घ period_ts,
			 अचिन्हित दीर्घ now)
अणु
	अगर ((watchकरोg_enabled & SOFT_WATCHDOG_ENABLED) && watchकरोg_thresh)अणु
		/* Warn about unreasonable delays. */
		अगर (समय_after(now, period_ts + get_softlockup_thresh()))
			वापस now - touch_ts;
	पूर्ण
	वापस 0;
पूर्ण

/* watchकरोg detector functions */
bool is_hardlockup(व्योम)
अणु
	अचिन्हित दीर्घ hrपूर्णांक = __this_cpu_पढ़ो(hrसमयr_पूर्णांकerrupts);

	अगर (__this_cpu_पढ़ो(hrसमयr_पूर्णांकerrupts_saved) == hrपूर्णांक)
		वापस true;

	__this_cpu_ग_लिखो(hrसमयr_पूर्णांकerrupts_saved, hrपूर्णांक);
	वापस false;
पूर्ण

अटल व्योम watchकरोg_पूर्णांकerrupt_count(व्योम)
अणु
	__this_cpu_inc(hrसमयr_पूर्णांकerrupts);
पूर्ण

अटल DEFINE_PER_CPU(काष्ठा completion, softlockup_completion);
अटल DEFINE_PER_CPU(काष्ठा cpu_stop_work, softlockup_stop_work);

/*
 * The watchकरोg thपढ़ो function - touches the बारtamp.
 *
 * It only runs once every sample_period seconds (4 seconds by
 * शेष) to reset the softlockup बारtamp. If this माला_लो delayed
 * क्रम more than 2*watchकरोg_thresh seconds then the debug-prपूर्णांकout
 * triggers in watchकरोg_समयr_fn().
 */
अटल पूर्णांक softlockup_fn(व्योम *data)
अणु
	update_touch_ts();
	complete(this_cpu_ptr(&softlockup_completion));

	वापस 0;
पूर्ण

/* watchकरोg kicker functions */
अटल क्रमागत hrसमयr_restart watchकरोg_समयr_fn(काष्ठा hrसमयr *hrसमयr)
अणु
	अचिन्हित दीर्घ touch_ts, period_ts, now;
	काष्ठा pt_regs *regs = get_irq_regs();
	पूर्णांक duration;
	पूर्णांक softlockup_all_cpu_backtrace = sysctl_softlockup_all_cpu_backtrace;

	अगर (!watchकरोg_enabled)
		वापस HRTIMER_NORESTART;

	/* kick the hardlockup detector */
	watchकरोg_पूर्णांकerrupt_count();

	/* kick the softlockup detector */
	अगर (completion_करोne(this_cpu_ptr(&softlockup_completion))) अणु
		reinit_completion(this_cpu_ptr(&softlockup_completion));
		stop_one_cpu_noरुको(smp_processor_id(),
				softlockup_fn, शून्य,
				this_cpu_ptr(&softlockup_stop_work));
	पूर्ण

	/* .. and repeat */
	hrसमयr_क्रमward_now(hrसमयr, ns_to_kसमय(sample_period));

	/*
	 * Read the current बारtamp first. It might become invalid anyसमय
	 * when a भव machine is stopped by the host or when the watchog
	 * is touched from NMI.
	 */
	now = get_बारtamp();
	/*
	 * If a भव machine is stopped by the host it can look to
	 * the watchकरोg like a soft lockup. This function touches the watchकरोg.
	 */
	kvm_check_and_clear_guest_छोड़ोd();
	/*
	 * The stored बारtamp is comparable with @now only when not touched.
	 * It might get touched anyसमय from NMI. Make sure that is_softlockup()
	 * uses the same (valid) value.
	 */
	period_ts = READ_ONCE(*this_cpu_ptr(&watchकरोg_report_ts));

	/* Reset the पूर्णांकerval when touched by known problematic code. */
	अगर (period_ts == SOFTLOCKUP_DELAY_REPORT) अणु
		अगर (unlikely(__this_cpu_पढ़ो(softlockup_touch_sync))) अणु
			/*
			 * If the समय stamp was touched atomically
			 * make sure the scheduler tick is up to date.
			 */
			__this_cpu_ग_लिखो(softlockup_touch_sync, false);
			sched_घड़ी_प्रकारick();
		पूर्ण

		update_report_ts();
		वापस HRTIMER_RESTART;
	पूर्ण

	/* Check क्रम a softlockup. */
	touch_ts = __this_cpu_पढ़ो(watchकरोg_touch_ts);
	duration = is_softlockup(touch_ts, period_ts, now);
	अगर (unlikely(duration)) अणु
		/*
		 * Prevent multiple soft-lockup reports अगर one cpu is alपढ़ोy
		 * engaged in dumping all cpu back traces.
		 */
		अगर (softlockup_all_cpu_backtrace) अणु
			अगर (test_and_set_bit_lock(0, &soft_lockup_nmi_warn))
				वापस HRTIMER_RESTART;
		पूर्ण

		/* Start period क्रम the next softlockup warning. */
		update_report_ts();

		pr_emerg("BUG: soft lockup - CPU#%d stuck for %us! [%s:%d]\n",
			smp_processor_id(), duration,
			current->comm, task_pid_nr(current));
		prपूर्णांक_modules();
		prपूर्णांक_irqtrace_events(current);
		अगर (regs)
			show_regs(regs);
		अन्यथा
			dump_stack();

		अगर (softlockup_all_cpu_backtrace) अणु
			trigger_allbutself_cpu_backtrace();
			clear_bit_unlock(0, &soft_lockup_nmi_warn);
		पूर्ण

		add_taपूर्णांक(TAINT_SOFTLOCKUP, LOCKDEP_STILL_OK);
		अगर (softlockup_panic)
			panic("softlockup: hung tasks");
	पूर्ण

	वापस HRTIMER_RESTART;
पूर्ण

अटल व्योम watchकरोg_enable(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा hrसमयr *hrसमयr = this_cpu_ptr(&watchकरोg_hrसमयr);
	काष्ठा completion *करोne = this_cpu_ptr(&softlockup_completion);

	WARN_ON_ONCE(cpu != smp_processor_id());

	init_completion(करोne);
	complete(करोne);

	/*
	 * Start the समयr first to prevent the NMI watchकरोg triggering
	 * beक्रमe the समयr has a chance to fire.
	 */
	hrसमयr_init(hrसमयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL_HARD);
	hrसमयr->function = watchकरोg_समयr_fn;
	hrसमयr_start(hrसमयr, ns_to_kसमय(sample_period),
		      HRTIMER_MODE_REL_PINNED_HARD);

	/* Initialize बारtamp */
	update_touch_ts();
	/* Enable the perf event */
	अगर (watchकरोg_enabled & NMI_WATCHDOG_ENABLED)
		watchकरोg_nmi_enable(cpu);
पूर्ण

अटल व्योम watchकरोg_disable(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा hrसमयr *hrसमयr = this_cpu_ptr(&watchकरोg_hrसमयr);

	WARN_ON_ONCE(cpu != smp_processor_id());

	/*
	 * Disable the perf event first. That prevents that a large delay
	 * between disabling the समयr and disabling the perf event causes
	 * the perf NMI to detect a false positive.
	 */
	watchकरोg_nmi_disable(cpu);
	hrसमयr_cancel(hrसमयr);
	रुको_क्रम_completion(this_cpu_ptr(&softlockup_completion));
पूर्ण

अटल पूर्णांक softlockup_stop_fn(व्योम *data)
अणु
	watchकरोg_disable(smp_processor_id());
	वापस 0;
पूर्ण

अटल व्योम softlockup_stop_all(व्योम)
अणु
	पूर्णांक cpu;

	अगर (!softlockup_initialized)
		वापस;

	क्रम_each_cpu(cpu, &watchकरोg_allowed_mask)
		smp_call_on_cpu(cpu, softlockup_stop_fn, शून्य, false);

	cpumask_clear(&watchकरोg_allowed_mask);
पूर्ण

अटल पूर्णांक softlockup_start_fn(व्योम *data)
अणु
	watchकरोg_enable(smp_processor_id());
	वापस 0;
पूर्ण

अटल व्योम softlockup_start_all(व्योम)
अणु
	पूर्णांक cpu;

	cpumask_copy(&watchकरोg_allowed_mask, &watchकरोg_cpumask);
	क्रम_each_cpu(cpu, &watchकरोg_allowed_mask)
		smp_call_on_cpu(cpu, softlockup_start_fn, शून्य, false);
पूर्ण

पूर्णांक lockup_detector_online_cpu(अचिन्हित पूर्णांक cpu)
अणु
	अगर (cpumask_test_cpu(cpu, &watchकरोg_allowed_mask))
		watchकरोg_enable(cpu);
	वापस 0;
पूर्ण

पूर्णांक lockup_detector_offline_cpu(अचिन्हित पूर्णांक cpu)
अणु
	अगर (cpumask_test_cpu(cpu, &watchकरोg_allowed_mask))
		watchकरोg_disable(cpu);
	वापस 0;
पूर्ण

अटल व्योम lockup_detector_reconfigure(व्योम)
अणु
	cpus_पढ़ो_lock();
	watchकरोg_nmi_stop();

	softlockup_stop_all();
	set_sample_period();
	lockup_detector_update_enable();
	अगर (watchकरोg_enabled && watchकरोg_thresh)
		softlockup_start_all();

	watchकरोg_nmi_start();
	cpus_पढ़ो_unlock();
	/*
	 * Must be called outside the cpus locked section to prevent
	 * recursive locking in the perf code.
	 */
	__lockup_detector_cleanup();
पूर्ण

/*
 * Create the watchकरोg thपढ़ो infraकाष्ठाure and configure the detector(s).
 *
 * The thपढ़ोs are not unparked as watchकरोg_allowed_mask is empty.  When
 * the thपढ़ोs are successfully initialized, take the proper locks and
 * unpark the thपढ़ोs in the watchकरोg_cpumask अगर the watchकरोg is enabled.
 */
अटल __init व्योम lockup_detector_setup(व्योम)
अणु
	/*
	 * If sysctl is off and watchकरोg got disabled on the command line,
	 * nothing to करो here.
	 */
	lockup_detector_update_enable();

	अगर (!IS_ENABLED(CONFIG_SYSCTL) &&
	    !(watchकरोg_enabled && watchकरोg_thresh))
		वापस;

	mutex_lock(&watchकरोg_mutex);
	lockup_detector_reconfigure();
	softlockup_initialized = true;
	mutex_unlock(&watchकरोg_mutex);
पूर्ण

#अन्यथा /* CONFIG_SOFTLOCKUP_DETECTOR */
अटल व्योम lockup_detector_reconfigure(व्योम)
अणु
	cpus_पढ़ो_lock();
	watchकरोg_nmi_stop();
	lockup_detector_update_enable();
	watchकरोg_nmi_start();
	cpus_पढ़ो_unlock();
पूर्ण
अटल अंतरभूत व्योम lockup_detector_setup(व्योम)
अणु
	lockup_detector_reconfigure();
पूर्ण
#पूर्ण_अगर /* !CONFIG_SOFTLOCKUP_DETECTOR */

अटल व्योम __lockup_detector_cleanup(व्योम)
अणु
	lockdep_निश्चित_held(&watchकरोg_mutex);
	hardlockup_detector_perf_cleanup();
पूर्ण

/**
 * lockup_detector_cleanup - Cleanup after cpu hotplug or sysctl changes
 *
 * Caller must not hold the cpu hotplug rwsem.
 */
व्योम lockup_detector_cleanup(व्योम)
अणु
	mutex_lock(&watchकरोg_mutex);
	__lockup_detector_cleanup();
	mutex_unlock(&watchकरोg_mutex);
पूर्ण

/**
 * lockup_detector_soft_घातeroff - Interface to stop lockup detector(s)
 *
 * Special पूर्णांकerface क्रम parisc. It prevents lockup detector warnings from
 * the शेष pm_घातeroff() function which busy loops क्रमever.
 */
व्योम lockup_detector_soft_घातeroff(व्योम)
अणु
	watchकरोg_enabled = 0;
पूर्ण

#अगर_घोषित CONFIG_SYSCTL

/* Propagate any changes to the watchकरोg thपढ़ोs */
अटल व्योम proc_watchकरोg_update(व्योम)
अणु
	/* Remove impossible cpus to keep sysctl output clean. */
	cpumask_and(&watchकरोg_cpumask, &watchकरोg_cpumask, cpu_possible_mask);
	lockup_detector_reconfigure();
पूर्ण

/*
 * common function क्रम watchकरोg, nmi_watchकरोg and soft_watchकरोg parameter
 *
 * caller             | table->data poपूर्णांकs to      | 'which'
 * -------------------|----------------------------|--------------------------
 * proc_watchकरोg      | watchकरोg_user_enabled      | NMI_WATCHDOG_ENABLED |
 *                    |                            | SOFT_WATCHDOG_ENABLED
 * -------------------|----------------------------|--------------------------
 * proc_nmi_watchकरोg  | nmi_watchकरोg_user_enabled  | NMI_WATCHDOG_ENABLED
 * -------------------|----------------------------|--------------------------
 * proc_soft_watchकरोg | soft_watchकरोg_user_enabled | SOFT_WATCHDOG_ENABLED
 */
अटल पूर्णांक proc_watchकरोg_common(पूर्णांक which, काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
				व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक err, old, *param = table->data;

	mutex_lock(&watchकरोg_mutex);

	अगर (!ग_लिखो) अणु
		/*
		 * On पढ़ो synchronize the userspace पूर्णांकerface. This is a
		 * racy snapshot.
		 */
		*param = (watchकरोg_enabled & which) != 0;
		err = proc_करोपूर्णांकvec_minmax(table, ग_लिखो, buffer, lenp, ppos);
	पूर्ण अन्यथा अणु
		old = READ_ONCE(*param);
		err = proc_करोपूर्णांकvec_minmax(table, ग_लिखो, buffer, lenp, ppos);
		अगर (!err && old != READ_ONCE(*param))
			proc_watchकरोg_update();
	पूर्ण
	mutex_unlock(&watchकरोg_mutex);
	वापस err;
पूर्ण

/*
 * /proc/sys/kernel/watchकरोg
 */
पूर्णांक proc_watchकरोg(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		  व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	वापस proc_watchकरोg_common(NMI_WATCHDOG_ENABLED|SOFT_WATCHDOG_ENABLED,
				    table, ग_लिखो, buffer, lenp, ppos);
पूर्ण

/*
 * /proc/sys/kernel/nmi_watchकरोg
 */
पूर्णांक proc_nmi_watchकरोg(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		      व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	अगर (!nmi_watchकरोg_available && ग_लिखो)
		वापस -ENOTSUPP;
	वापस proc_watchकरोg_common(NMI_WATCHDOG_ENABLED,
				    table, ग_लिखो, buffer, lenp, ppos);
पूर्ण

/*
 * /proc/sys/kernel/soft_watchकरोg
 */
पूर्णांक proc_soft_watchकरोg(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	वापस proc_watchकरोg_common(SOFT_WATCHDOG_ENABLED,
				    table, ग_लिखो, buffer, lenp, ppos);
पूर्ण

/*
 * /proc/sys/kernel/watchकरोg_thresh
 */
पूर्णांक proc_watchकरोg_thresh(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			 व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक err, old;

	mutex_lock(&watchकरोg_mutex);

	old = READ_ONCE(watchकरोg_thresh);
	err = proc_करोपूर्णांकvec_minmax(table, ग_लिखो, buffer, lenp, ppos);

	अगर (!err && ग_लिखो && old != READ_ONCE(watchकरोg_thresh))
		proc_watchकरोg_update();

	mutex_unlock(&watchकरोg_mutex);
	वापस err;
पूर्ण

/*
 * The cpumask is the mask of possible cpus that the watchकरोg can run
 * on, not the mask of cpus it is actually running on.  This allows the
 * user to specअगरy a mask that will include cpus that have not yet
 * been brought online, अगर desired.
 */
पूर्णांक proc_watchकरोg_cpumask(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			  व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक err;

	mutex_lock(&watchकरोg_mutex);

	err = proc_करो_large_biपंचांगap(table, ग_लिखो, buffer, lenp, ppos);
	अगर (!err && ग_लिखो)
		proc_watchकरोg_update();

	mutex_unlock(&watchकरोg_mutex);
	वापस err;
पूर्ण
#पूर्ण_अगर /* CONFIG_SYSCTL */

व्योम __init lockup_detector_init(व्योम)
अणु
	अगर (tick_nohz_full_enabled())
		pr_info("Disabling watchdog on nohz_full cores by default\n");

	cpumask_copy(&watchकरोg_cpumask,
		     housekeeping_cpumask(HK_FLAG_TIMER));

	अगर (!watchकरोg_nmi_probe())
		nmi_watchकरोg_available = true;
	lockup_detector_setup();
पूर्ण
