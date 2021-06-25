<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Watchकरोg support on घातerpc प्रणालीs.
 *
 * Copyright 2017, IBM Corporation.
 *
 * This uses code from arch/sparc/kernel/nmi.c and kernel/watchकरोg.c
 */

#घोषणा pr_fmt(fmt) "watchdog: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/param.h>
#समावेश <linux/init.h>
#समावेश <linux/percpu.h>
#समावेश <linux/cpu.h>
#समावेश <linux/nmi.h>
#समावेश <linux/module.h>
#समावेश <linux/export.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/reboot.h>
#समावेश <linux/slab.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/delay.h>
#समावेश <linux/smp.h>

#समावेश <यंत्र/पूर्णांकerrupt.h>
#समावेश <यंत्र/paca.h>
#समावेश <यंत्र/nmi.h>

/*
 * The घातerpc watchकरोg ensures that each CPU is able to service समयrs.
 * The watchकरोg sets up a simple समयr on each CPU to run once per समयr
 * period, and updates a per-cpu बारtamp and a "pending" cpumask. This is
 * the heartbeat.
 *
 * Then there are two प्रणालीs to check that the heartbeat is still running.
 * The local soft-NMI, and the SMP checker.
 *
 * The soft-NMI checker can detect lockups on the local CPU. When पूर्णांकerrupts
 * are disabled with local_irq_disable(), platक्रमms that use soft-masking
 * can leave hardware पूर्णांकerrupts enabled and handle them with a masked
 * पूर्णांकerrupt handler. The masked handler can send the समयr पूर्णांकerrupt to the
 * watchकरोg's soft_nmi_पूर्णांकerrupt(), which appears to Linux as an NMI
 * पूर्णांकerrupt, and can be used to detect CPUs stuck with IRQs disabled.
 *
 * The soft-NMI checker will compare the heartbeat बारtamp क्रम this CPU
 * with the current समय, and take action अगर the dअगरference exceeds the
 * watchकरोg threshold.
 *
 * The limitation of the soft-NMI watchकरोg is that it करोes not work when
 * पूर्णांकerrupts are hard disabled or otherwise not being serviced. This is
 * solved by also having a SMP watchकरोg where all CPUs check all other
 * CPUs heartbeat.
 *
 * The SMP checker can detect lockups on other CPUs. A gobal "pending"
 * cpumask is kept, containing all CPUs which enable the watchकरोg. Each
 * CPU clears their pending bit in their heartbeat समयr. When the biपंचांगask
 * becomes empty, the last CPU to clear its pending bit updates a global
 * बारtamp and refills the pending biपंचांगask.
 *
 * In the heartbeat समयr, अगर any CPU notices that the global बारtamp has
 * not been updated क्रम a period exceeding the watchकरोg threshold, then it
 * means the CPU(s) with their bit still set in the pending mask have had
 * their heartbeat stop, and action is taken.
 *
 * Some platक्रमms implement true NMI IPIs, which can be used by the SMP
 * watchकरोg to detect an unresponsive CPU and pull it out of its stuck
 * state with the NMI IPI, to get crash/debug data from it. This way the
 * SMP watchकरोg can detect hardware पूर्णांकerrupts off lockups.
 */

अटल cpumask_t wd_cpus_enabled __पढ़ो_mostly;

अटल u64 wd_panic_समयout_tb __पढ़ो_mostly; /* समयbase ticks until panic */
अटल u64 wd_smp_panic_समयout_tb __पढ़ो_mostly; /* panic other CPUs */

अटल u64 wd_समयr_period_ms __पढ़ो_mostly;  /* पूर्णांकerval between heartbeat */

अटल DEFINE_PER_CPU(काष्ठा hrसमयr, wd_hrसमयr);
अटल DEFINE_PER_CPU(u64, wd_समयr_tb);

/* SMP checker bits */
अटल अचिन्हित दीर्घ __wd_smp_lock;
अटल cpumask_t wd_smp_cpus_pending;
अटल cpumask_t wd_smp_cpus_stuck;
अटल u64 wd_smp_last_reset_tb;

अटल अंतरभूत व्योम wd_smp_lock(अचिन्हित दीर्घ *flags)
अणु
	/*
	 * Aव्योम locking layers अगर possible.
	 * This may be called from low level पूर्णांकerrupt handlers at some
	 * poपूर्णांक in future.
	 */
	raw_local_irq_save(*flags);
	hard_irq_disable(); /* Make it soft-NMI safe */
	जबतक (unlikely(test_and_set_bit_lock(0, &__wd_smp_lock))) अणु
		raw_local_irq_restore(*flags);
		spin_until_cond(!test_bit(0, &__wd_smp_lock));
		raw_local_irq_save(*flags);
		hard_irq_disable();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम wd_smp_unlock(अचिन्हित दीर्घ *flags)
अणु
	clear_bit_unlock(0, &__wd_smp_lock);
	raw_local_irq_restore(*flags);
पूर्ण

अटल व्योम wd_lockup_ipi(काष्ठा pt_regs *regs)
अणु
	पूर्णांक cpu = raw_smp_processor_id();
	u64 tb = get_tb();

	pr_emerg("CPU %d Hard LOCKUP\n", cpu);
	pr_emerg("CPU %d TB:%lld, last heartbeat TB:%lld (%lldms ago)\n",
		 cpu, tb, per_cpu(wd_समयr_tb, cpu),
		 tb_to_ns(tb - per_cpu(wd_समयr_tb, cpu)) / 1000000);
	prपूर्णांक_modules();
	prपूर्णांक_irqtrace_events(current);
	अगर (regs)
		show_regs(regs);
	अन्यथा
		dump_stack();

	/* Do not panic from here because that can recurse पूर्णांकo NMI IPI layer */
पूर्ण

अटल व्योम set_cpumask_stuck(स्थिर काष्ठा cpumask *cpumask, u64 tb)
अणु
	cpumask_or(&wd_smp_cpus_stuck, &wd_smp_cpus_stuck, cpumask);
	cpumask_andnot(&wd_smp_cpus_pending, &wd_smp_cpus_pending, cpumask);
	अगर (cpumask_empty(&wd_smp_cpus_pending)) अणु
		wd_smp_last_reset_tb = tb;
		cpumask_andnot(&wd_smp_cpus_pending,
				&wd_cpus_enabled,
				&wd_smp_cpus_stuck);
	पूर्ण
पूर्ण
अटल व्योम set_cpu_stuck(पूर्णांक cpu, u64 tb)
अणु
	set_cpumask_stuck(cpumask_of(cpu), tb);
पूर्ण

अटल व्योम watchकरोg_smp_panic(पूर्णांक cpu, u64 tb)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक c;

	wd_smp_lock(&flags);
	/* Double check some things under lock */
	अगर ((s64)(tb - wd_smp_last_reset_tb) < (s64)wd_smp_panic_समयout_tb)
		जाओ out;
	अगर (cpumask_test_cpu(cpu, &wd_smp_cpus_pending))
		जाओ out;
	अगर (cpumask_weight(&wd_smp_cpus_pending) == 0)
		जाओ out;

	pr_emerg("CPU %d detected hard LOCKUP on other CPUs %*pbl\n",
		 cpu, cpumask_pr_args(&wd_smp_cpus_pending));
	pr_emerg("CPU %d TB:%lld, last SMP heartbeat TB:%lld (%lldms ago)\n",
		 cpu, tb, wd_smp_last_reset_tb,
		 tb_to_ns(tb - wd_smp_last_reset_tb) / 1000000);

	अगर (!sysctl_hardlockup_all_cpu_backtrace) अणु
		/*
		 * Try to trigger the stuck CPUs, unless we are going to
		 * get a backtrace on all of them anyway.
		 */
		क्रम_each_cpu(c, &wd_smp_cpus_pending) अणु
			अगर (c == cpu)
				जारी;
			smp_send_nmi_ipi(c, wd_lockup_ipi, 1000000);
		पूर्ण
	पूर्ण

	/* Take the stuck CPUs out of the watch group */
	set_cpumask_stuck(&wd_smp_cpus_pending, tb);

	wd_smp_unlock(&flags);

	prपूर्णांकk_safe_flush();
	/*
	 * prपूर्णांकk_safe_flush() seems to require another prपूर्णांक
	 * beक्रमe anything actually goes out to console.
	 */
	अगर (sysctl_hardlockup_all_cpu_backtrace)
		trigger_allbutself_cpu_backtrace();

	अगर (hardlockup_panic)
		nmi_panic(शून्य, "Hard LOCKUP");

	वापस;

out:
	wd_smp_unlock(&flags);
पूर्ण

अटल व्योम wd_smp_clear_cpu_pending(पूर्णांक cpu, u64 tb)
अणु
	अगर (!cpumask_test_cpu(cpu, &wd_smp_cpus_pending)) अणु
		अगर (unlikely(cpumask_test_cpu(cpu, &wd_smp_cpus_stuck))) अणु
			काष्ठा pt_regs *regs = get_irq_regs();
			अचिन्हित दीर्घ flags;

			wd_smp_lock(&flags);

			pr_emerg("CPU %d became unstuck TB:%lld\n",
				 cpu, tb);
			prपूर्णांक_irqtrace_events(current);
			अगर (regs)
				show_regs(regs);
			अन्यथा
				dump_stack();

			cpumask_clear_cpu(cpu, &wd_smp_cpus_stuck);
			wd_smp_unlock(&flags);
		पूर्ण
		वापस;
	पूर्ण
	cpumask_clear_cpu(cpu, &wd_smp_cpus_pending);
	अगर (cpumask_empty(&wd_smp_cpus_pending)) अणु
		अचिन्हित दीर्घ flags;

		wd_smp_lock(&flags);
		अगर (cpumask_empty(&wd_smp_cpus_pending)) अणु
			wd_smp_last_reset_tb = tb;
			cpumask_andnot(&wd_smp_cpus_pending,
					&wd_cpus_enabled,
					&wd_smp_cpus_stuck);
		पूर्ण
		wd_smp_unlock(&flags);
	पूर्ण
पूर्ण

अटल व्योम watchकरोg_समयr_पूर्णांकerrupt(पूर्णांक cpu)
अणु
	u64 tb = get_tb();

	per_cpu(wd_समयr_tb, cpu) = tb;

	wd_smp_clear_cpu_pending(cpu, tb);

	अगर ((s64)(tb - wd_smp_last_reset_tb) >= (s64)wd_smp_panic_समयout_tb)
		watchकरोg_smp_panic(cpu, tb);
पूर्ण

DEFINE_INTERRUPT_HANDLER_NMI(soft_nmi_पूर्णांकerrupt)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक cpu = raw_smp_processor_id();
	u64 tb;

	/* should only arrive from kernel, with irqs disabled */
	WARN_ON_ONCE(!arch_irq_disabled_regs(regs));

	अगर (!cpumask_test_cpu(cpu, &wd_cpus_enabled))
		वापस 0;

	__this_cpu_inc(irq_stat.soft_nmi_irqs);

	tb = get_tb();
	अगर (tb - per_cpu(wd_समयr_tb, cpu) >= wd_panic_समयout_tb) अणु
		wd_smp_lock(&flags);
		अगर (cpumask_test_cpu(cpu, &wd_smp_cpus_stuck)) अणु
			wd_smp_unlock(&flags);
			वापस 0;
		पूर्ण
		set_cpu_stuck(cpu, tb);

		pr_emerg("CPU %d self-detected hard LOCKUP @ %pS\n",
			 cpu, (व्योम *)regs->nip);
		pr_emerg("CPU %d TB:%lld, last heartbeat TB:%lld (%lldms ago)\n",
			 cpu, tb, per_cpu(wd_समयr_tb, cpu),
			 tb_to_ns(tb - per_cpu(wd_समयr_tb, cpu)) / 1000000);
		prपूर्णांक_modules();
		prपूर्णांक_irqtrace_events(current);
		show_regs(regs);

		wd_smp_unlock(&flags);

		अगर (sysctl_hardlockup_all_cpu_backtrace)
			trigger_allbutself_cpu_backtrace();

		अगर (hardlockup_panic)
			nmi_panic(regs, "Hard LOCKUP");
	पूर्ण
	अगर (wd_panic_समयout_tb < 0x7fffffff)
		mtspr(SPRN_DEC, wd_panic_समयout_tb);

	वापस 0;
पूर्ण

अटल क्रमागत hrसमयr_restart watchकरोg_समयr_fn(काष्ठा hrसमयr *hrसमयr)
अणु
	पूर्णांक cpu = smp_processor_id();

	अगर (!(watchकरोg_enabled & NMI_WATCHDOG_ENABLED))
		वापस HRTIMER_NORESTART;

	अगर (!cpumask_test_cpu(cpu, &watchकरोg_cpumask))
		वापस HRTIMER_NORESTART;

	watchकरोg_समयr_पूर्णांकerrupt(cpu);

	hrसमयr_क्रमward_now(hrसमयr, ms_to_kसमय(wd_समयr_period_ms));

	वापस HRTIMER_RESTART;
पूर्ण

व्योम arch_touch_nmi_watchकरोg(व्योम)
अणु
	अचिन्हित दीर्घ ticks = tb_ticks_per_usec * wd_समयr_period_ms * 1000;
	पूर्णांक cpu = smp_processor_id();
	u64 tb = get_tb();

	अगर (tb - per_cpu(wd_समयr_tb, cpu) >= ticks) अणु
		per_cpu(wd_समयr_tb, cpu) = tb;
		wd_smp_clear_cpu_pending(cpu, tb);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(arch_touch_nmi_watchकरोg);

अटल व्योम start_watchकरोg(व्योम *arg)
अणु
	काष्ठा hrसमयr *hrसमयr = this_cpu_ptr(&wd_hrसमयr);
	पूर्णांक cpu = smp_processor_id();
	अचिन्हित दीर्घ flags;

	अगर (cpumask_test_cpu(cpu, &wd_cpus_enabled)) अणु
		WARN_ON(1);
		वापस;
	पूर्ण

	अगर (!(watchकरोg_enabled & NMI_WATCHDOG_ENABLED))
		वापस;

	अगर (!cpumask_test_cpu(cpu, &watchकरोg_cpumask))
		वापस;

	wd_smp_lock(&flags);
	cpumask_set_cpu(cpu, &wd_cpus_enabled);
	अगर (cpumask_weight(&wd_cpus_enabled) == 1) अणु
		cpumask_set_cpu(cpu, &wd_smp_cpus_pending);
		wd_smp_last_reset_tb = get_tb();
	पूर्ण
	wd_smp_unlock(&flags);

	*this_cpu_ptr(&wd_समयr_tb) = get_tb();

	hrसमयr_init(hrसमयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	hrसमयr->function = watchकरोg_समयr_fn;
	hrसमयr_start(hrसमयr, ms_to_kसमय(wd_समयr_period_ms),
		      HRTIMER_MODE_REL_PINNED);
पूर्ण

अटल पूर्णांक start_watchकरोg_on_cpu(अचिन्हित पूर्णांक cpu)
अणु
	वापस smp_call_function_single(cpu, start_watchकरोg, शून्य, true);
पूर्ण

अटल व्योम stop_watchकरोg(व्योम *arg)
अणु
	काष्ठा hrसमयr *hrसमयr = this_cpu_ptr(&wd_hrसमयr);
	पूर्णांक cpu = smp_processor_id();
	अचिन्हित दीर्घ flags;

	अगर (!cpumask_test_cpu(cpu, &wd_cpus_enabled))
		वापस; /* Can happen in CPU unplug हाल */

	hrसमयr_cancel(hrसमयr);

	wd_smp_lock(&flags);
	cpumask_clear_cpu(cpu, &wd_cpus_enabled);
	wd_smp_unlock(&flags);

	wd_smp_clear_cpu_pending(cpu, get_tb());
पूर्ण

अटल पूर्णांक stop_watchकरोg_on_cpu(अचिन्हित पूर्णांक cpu)
अणु
	वापस smp_call_function_single(cpu, stop_watchकरोg, शून्य, true);
पूर्ण

अटल व्योम watchकरोg_calc_समयouts(व्योम)
अणु
	wd_panic_समयout_tb = watchकरोg_thresh * ppc_tb_freq;

	/* Have the SMP detector trigger a bit later */
	wd_smp_panic_समयout_tb = wd_panic_समयout_tb * 3 / 2;

	/* 2/5 is the factor that the perf based detector uses */
	wd_समयr_period_ms = watchकरोg_thresh * 1000 * 2 / 5;
पूर्ण

व्योम watchकरोg_nmi_stop(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_cpu(cpu, &wd_cpus_enabled)
		stop_watchकरोg_on_cpu(cpu);
पूर्ण

व्योम watchकरोg_nmi_start(व्योम)
अणु
	पूर्णांक cpu;

	watchकरोg_calc_समयouts();
	क्रम_each_cpu_and(cpu, cpu_online_mask, &watchकरोg_cpumask)
		start_watchकरोg_on_cpu(cpu);
पूर्ण

/*
 * Invoked from core watchकरोg init.
 */
पूर्णांक __init watchकरोg_nmi_probe(व्योम)
अणु
	पूर्णांक err;

	err = cpuhp_setup_state_nocalls(CPUHP_AP_ONLINE_DYN,
					"powerpc/watchdog:online",
					start_watchकरोg_on_cpu,
					stop_watchकरोg_on_cpu);
	अगर (err < 0) अणु
		pr_warn("could not be initialized");
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण
