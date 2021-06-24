<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright(C) 2005-2006, Thomas Gleixner <tglx@linutronix.de>
 *  Copyright(C) 2005-2007, Red Hat, Inc., Ingo Molnar
 *  Copyright(C) 2006-2007  Timesys Corp., Thomas Gleixner
 *
 *  No idle tick implementation क्रम low and high resolution समयrs
 *
 *  Started by: Thomas Gleixner and Ingo Molnar
 */
#समावेश <linux/cpu.h>
#समावेश <linux/err.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/percpu.h>
#समावेश <linux/nmi.h>
#समावेश <linux/profile.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/sched/स्थिति.स>
#समावेश <linux/sched/nohz.h>
#समावेश <linux/sched/loadavg.h>
#समावेश <linux/module.h>
#समावेश <linux/irq_work.h>
#समावेश <linux/posix-समयrs.h>
#समावेश <linux/context_tracking.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/irq_regs.h>

#समावेश "tick-internal.h"

#समावेश <trace/events/समयr.h>

/*
 * Per-CPU nohz control काष्ठाure
 */
अटल DEFINE_PER_CPU(काष्ठा tick_sched, tick_cpu_sched);

काष्ठा tick_sched *tick_get_tick_sched(पूर्णांक cpu)
अणु
	वापस &per_cpu(tick_cpu_sched, cpu);
पूर्ण

#अगर defined(CONFIG_NO_HZ_COMMON) || defined(CONFIG_HIGH_RES_TIMERS)
/*
 * The समय, when the last jअगरfy update happened. Write access must hold
 * jअगरfies_lock and jअगरfies_seq. tick_nohz_next_event() needs to get a
 * consistent view of jअगरfies and last_jअगरfies_update.
 */
अटल kसमय_प्रकार last_jअगरfies_update;

/*
 * Must be called with पूर्णांकerrupts disabled !
 */
अटल व्योम tick_करो_update_jअगरfies64(kसमय_प्रकार now)
अणु
	अचिन्हित दीर्घ ticks = 1;
	kसमय_प्रकार delta, nextp;

	/*
	 * 64bit can करो a quick check without holding jअगरfies lock and
	 * without looking at the sequence count. The smp_load_acquire()
	 * pairs with the update करोne later in this function.
	 *
	 * 32bit cannot करो that because the store of tick_next_period
	 * consists of two 32bit stores and the first store could move it
	 * to a अक्रमom poपूर्णांक in the future.
	 */
	अगर (IS_ENABLED(CONFIG_64BIT)) अणु
		अगर (kसमय_beक्रमe(now, smp_load_acquire(&tick_next_period)))
			वापस;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक seq;

		/*
		 * Aव्योम contention on jअगरfies_lock and protect the quick
		 * check with the sequence count.
		 */
		करो अणु
			seq = पढ़ो_seqcount_begin(&jअगरfies_seq);
			nextp = tick_next_period;
		पूर्ण जबतक (पढ़ो_seqcount_retry(&jअगरfies_seq, seq));

		अगर (kसमय_beक्रमe(now, nextp))
			वापस;
	पूर्ण

	/* Quick check failed, i.e. update is required. */
	raw_spin_lock(&jअगरfies_lock);
	/*
	 * Reevaluate with the lock held. Another CPU might have करोne the
	 * update alपढ़ोy.
	 */
	अगर (kसमय_beक्रमe(now, tick_next_period)) अणु
		raw_spin_unlock(&jअगरfies_lock);
		वापस;
	पूर्ण

	ग_लिखो_seqcount_begin(&jअगरfies_seq);

	delta = kसमय_sub(now, tick_next_period);
	अगर (unlikely(delta >= TICK_NSEC)) अणु
		/* Slow path क्रम दीर्घ idle sleep बार */
		s64 incr = TICK_NSEC;

		ticks += kसमय_भागns(delta, incr);

		last_jअगरfies_update = kसमय_add_ns(last_jअगरfies_update,
						   incr * ticks);
	पूर्ण अन्यथा अणु
		last_jअगरfies_update = kसमय_add_ns(last_jअगरfies_update,
						   TICK_NSEC);
	पूर्ण

	/* Advance jअगरfies to complete the jअगरfies_seq रक्षित job */
	jअगरfies_64 += ticks;

	/*
	 * Keep the tick_next_period variable up to date.
	 */
	nextp = kसमय_add_ns(last_jअगरfies_update, TICK_NSEC);

	अगर (IS_ENABLED(CONFIG_64BIT)) अणु
		/*
		 * Pairs with smp_load_acquire() in the lockless quick
		 * check above and ensures that the update to jअगरfies_64 is
		 * not reordered vs. the store to tick_next_period, neither
		 * by the compiler nor by the CPU.
		 */
		smp_store_release(&tick_next_period, nextp);
	पूर्ण अन्यथा अणु
		/*
		 * A plain store is good enough on 32bit as the quick check
		 * above is रक्षित by the sequence count.
		 */
		tick_next_period = nextp;
	पूर्ण

	/*
	 * Release the sequence count. calc_global_load() below is not
	 * रक्षित by it, but jअगरfies_lock needs to be held to prevent
	 * concurrent invocations.
	 */
	ग_लिखो_seqcount_end(&jअगरfies_seq);

	calc_global_load();

	raw_spin_unlock(&jअगरfies_lock);
	update_wall_समय();
पूर्ण

/*
 * Initialize and वापस retrieve the jअगरfies update.
 */
अटल kसमय_प्रकार tick_init_jअगरfy_update(व्योम)
अणु
	kसमय_प्रकार period;

	raw_spin_lock(&jअगरfies_lock);
	ग_लिखो_seqcount_begin(&jअगरfies_seq);
	/* Did we start the jअगरfies update yet ? */
	अगर (last_jअगरfies_update == 0)
		last_jअगरfies_update = tick_next_period;
	period = last_jअगरfies_update;
	ग_लिखो_seqcount_end(&jअगरfies_seq);
	raw_spin_unlock(&jअगरfies_lock);
	वापस period;
पूर्ण

अटल व्योम tick_sched_करो_समयr(काष्ठा tick_sched *ts, kसमय_प्रकार now)
अणु
	पूर्णांक cpu = smp_processor_id();

#अगर_घोषित CONFIG_NO_HZ_COMMON
	/*
	 * Check अगर the करो_समयr duty was dropped. We करोn't care about
	 * concurrency: This happens only when the CPU in अक्षरge went
	 * पूर्णांकo a दीर्घ sleep. If two CPUs happen to assign themselves to
	 * this duty, then the jअगरfies update is still serialized by
	 * jअगरfies_lock.
	 *
	 * If nohz_full is enabled, this should not happen because the
	 * tick_करो_समयr_cpu never relinquishes.
	 */
	अगर (unlikely(tick_करो_समयr_cpu == TICK_DO_TIMER_NONE)) अणु
#अगर_घोषित CONFIG_NO_HZ_FULL
		WARN_ON(tick_nohz_full_running);
#पूर्ण_अगर
		tick_करो_समयr_cpu = cpu;
	पूर्ण
#पूर्ण_अगर

	/* Check, अगर the jअगरfies need an update */
	अगर (tick_करो_समयr_cpu == cpu)
		tick_करो_update_jअगरfies64(now);

	अगर (ts->inidle)
		ts->got_idle_tick = 1;
पूर्ण

अटल व्योम tick_sched_handle(काष्ठा tick_sched *ts, काष्ठा pt_regs *regs)
अणु
#अगर_घोषित CONFIG_NO_HZ_COMMON
	/*
	 * When we are idle and the tick is stopped, we have to touch
	 * the watchकरोg as we might not schedule क्रम a really दीर्घ
	 * समय. This happens on complete idle SMP प्रणालीs जबतक
	 * रुकोing on the login prompt. We also increment the "start of
	 * idle" jअगरfy stamp so the idle accounting adjusपंचांगent we करो
	 * when we go busy again करोes not account too much ticks.
	 */
	अगर (ts->tick_stopped) अणु
		touch_softlockup_watchकरोg_sched();
		अगर (is_idle_task(current))
			ts->idle_jअगरfies++;
		/*
		 * In हाल the current tick fired too early past its expected
		 * expiration, make sure we करोn't bypass the next घड़ी reprogramming
		 * to the same deadline.
		 */
		ts->next_tick = 0;
	पूर्ण
#पूर्ण_अगर
	update_process_बार(user_mode(regs));
	profile_tick(CPU_PROFILING);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_NO_HZ_FULL
cpumask_var_t tick_nohz_full_mask;
EXPORT_SYMBOL_GPL(tick_nohz_full_mask);
bool tick_nohz_full_running;
EXPORT_SYMBOL_GPL(tick_nohz_full_running);
अटल atomic_t tick_dep_mask;

अटल bool check_tick_dependency(atomic_t *dep)
अणु
	पूर्णांक val = atomic_पढ़ो(dep);

	अगर (val & TICK_DEP_MASK_POSIX_TIMER) अणु
		trace_tick_stop(0, TICK_DEP_MASK_POSIX_TIMER);
		वापस true;
	पूर्ण

	अगर (val & TICK_DEP_MASK_PERF_EVENTS) अणु
		trace_tick_stop(0, TICK_DEP_MASK_PERF_EVENTS);
		वापस true;
	पूर्ण

	अगर (val & TICK_DEP_MASK_SCHED) अणु
		trace_tick_stop(0, TICK_DEP_MASK_SCHED);
		वापस true;
	पूर्ण

	अगर (val & TICK_DEP_MASK_CLOCK_UNSTABLE) अणु
		trace_tick_stop(0, TICK_DEP_MASK_CLOCK_UNSTABLE);
		वापस true;
	पूर्ण

	अगर (val & TICK_DEP_MASK_RCU) अणु
		trace_tick_stop(0, TICK_DEP_MASK_RCU);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool can_stop_full_tick(पूर्णांक cpu, काष्ठा tick_sched *ts)
अणु
	lockdep_निश्चित_irqs_disabled();

	अगर (unlikely(!cpu_online(cpu)))
		वापस false;

	अगर (check_tick_dependency(&tick_dep_mask))
		वापस false;

	अगर (check_tick_dependency(&ts->tick_dep_mask))
		वापस false;

	अगर (check_tick_dependency(&current->tick_dep_mask))
		वापस false;

	अगर (check_tick_dependency(&current->संकेत->tick_dep_mask))
		वापस false;

	वापस true;
पूर्ण

अटल व्योम nohz_full_kick_func(काष्ठा irq_work *work)
अणु
	/* Empty, the tick restart happens on tick_nohz_irq_निकास() */
पूर्ण

अटल DEFINE_PER_CPU(काष्ठा irq_work, nohz_full_kick_work) =
	IRQ_WORK_INIT_HARD(nohz_full_kick_func);

/*
 * Kick this CPU अगर it's full dynticks in order to क्रमce it to
 * re-evaluate its dependency on the tick and restart it अगर necessary.
 * This kick, unlike tick_nohz_full_kick_cpu() and tick_nohz_full_kick_all(),
 * is NMI safe.
 */
अटल व्योम tick_nohz_full_kick(व्योम)
अणु
	अगर (!tick_nohz_full_cpu(smp_processor_id()))
		वापस;

	irq_work_queue(this_cpu_ptr(&nohz_full_kick_work));
पूर्ण

/*
 * Kick the CPU अगर it's full dynticks in order to क्रमce it to
 * re-evaluate its dependency on the tick and restart it अगर necessary.
 */
व्योम tick_nohz_full_kick_cpu(पूर्णांक cpu)
अणु
	अगर (!tick_nohz_full_cpu(cpu))
		वापस;

	irq_work_queue_on(&per_cpu(nohz_full_kick_work, cpu), cpu);
पूर्ण

/*
 * Kick all full dynticks CPUs in order to क्रमce these to re-evaluate
 * their dependency on the tick and restart it अगर necessary.
 */
अटल व्योम tick_nohz_full_kick_all(व्योम)
अणु
	पूर्णांक cpu;

	अगर (!tick_nohz_full_running)
		वापस;

	preempt_disable();
	क्रम_each_cpu_and(cpu, tick_nohz_full_mask, cpu_online_mask)
		tick_nohz_full_kick_cpu(cpu);
	preempt_enable();
पूर्ण

अटल व्योम tick_nohz_dep_set_all(atomic_t *dep,
				  क्रमागत tick_dep_bits bit)
अणु
	पूर्णांक prev;

	prev = atomic_fetch_or(BIT(bit), dep);
	अगर (!prev)
		tick_nohz_full_kick_all();
पूर्ण

/*
 * Set a global tick dependency. Used by perf events that rely on freq and
 * by unstable घड़ी.
 */
व्योम tick_nohz_dep_set(क्रमागत tick_dep_bits bit)
अणु
	tick_nohz_dep_set_all(&tick_dep_mask, bit);
पूर्ण

व्योम tick_nohz_dep_clear(क्रमागत tick_dep_bits bit)
अणु
	atomic_andnot(BIT(bit), &tick_dep_mask);
पूर्ण

/*
 * Set per-CPU tick dependency. Used by scheduler and perf events in order to
 * manage events throttling.
 */
व्योम tick_nohz_dep_set_cpu(पूर्णांक cpu, क्रमागत tick_dep_bits bit)
अणु
	पूर्णांक prev;
	काष्ठा tick_sched *ts;

	ts = per_cpu_ptr(&tick_cpu_sched, cpu);

	prev = atomic_fetch_or(BIT(bit), &ts->tick_dep_mask);
	अगर (!prev) अणु
		preempt_disable();
		/* Perf needs local kick that is NMI safe */
		अगर (cpu == smp_processor_id()) अणु
			tick_nohz_full_kick();
		पूर्ण अन्यथा अणु
			/* Remote irq work not NMI-safe */
			अगर (!WARN_ON_ONCE(in_nmi()))
				tick_nohz_full_kick_cpu(cpu);
		पूर्ण
		preempt_enable();
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(tick_nohz_dep_set_cpu);

व्योम tick_nohz_dep_clear_cpu(पूर्णांक cpu, क्रमागत tick_dep_bits bit)
अणु
	काष्ठा tick_sched *ts = per_cpu_ptr(&tick_cpu_sched, cpu);

	atomic_andnot(BIT(bit), &ts->tick_dep_mask);
पूर्ण
EXPORT_SYMBOL_GPL(tick_nohz_dep_clear_cpu);

/*
 * Set a per-task tick dependency. RCU need this. Also posix CPU समयrs
 * in order to elapse per task समयrs.
 */
व्योम tick_nohz_dep_set_task(काष्ठा task_काष्ठा *tsk, क्रमागत tick_dep_bits bit)
अणु
	अगर (!atomic_fetch_or(BIT(bit), &tsk->tick_dep_mask)) अणु
		अगर (tsk == current) अणु
			preempt_disable();
			tick_nohz_full_kick();
			preempt_enable();
		पूर्ण अन्यथा अणु
			/*
			 * Some future tick_nohz_full_kick_task()
			 * should optimize this.
			 */
			tick_nohz_full_kick_all();
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(tick_nohz_dep_set_task);

व्योम tick_nohz_dep_clear_task(काष्ठा task_काष्ठा *tsk, क्रमागत tick_dep_bits bit)
अणु
	atomic_andnot(BIT(bit), &tsk->tick_dep_mask);
पूर्ण
EXPORT_SYMBOL_GPL(tick_nohz_dep_clear_task);

/*
 * Set a per-taskgroup tick dependency. Posix CPU समयrs need this in order to elapse
 * per process समयrs.
 */
व्योम tick_nohz_dep_set_संकेत(काष्ठा संकेत_काष्ठा *sig, क्रमागत tick_dep_bits bit)
अणु
	tick_nohz_dep_set_all(&sig->tick_dep_mask, bit);
पूर्ण

व्योम tick_nohz_dep_clear_संकेत(काष्ठा संकेत_काष्ठा *sig, क्रमागत tick_dep_bits bit)
अणु
	atomic_andnot(BIT(bit), &sig->tick_dep_mask);
पूर्ण

/*
 * Re-evaluate the need क्रम the tick as we चयन the current task.
 * It might need the tick due to per task/process properties:
 * perf events, posix CPU समयrs, ...
 */
व्योम __tick_nohz_task_चयन(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा tick_sched *ts;

	local_irq_save(flags);

	अगर (!tick_nohz_full_cpu(smp_processor_id()))
		जाओ out;

	ts = this_cpu_ptr(&tick_cpu_sched);

	अगर (ts->tick_stopped) अणु
		अगर (atomic_पढ़ो(&current->tick_dep_mask) ||
		    atomic_पढ़ो(&current->संकेत->tick_dep_mask))
			tick_nohz_full_kick();
	पूर्ण
out:
	local_irq_restore(flags);
पूर्ण

/* Get the boot-समय nohz CPU list from the kernel parameters. */
व्योम __init tick_nohz_full_setup(cpumask_var_t cpumask)
अणु
	alloc_booपंचांगem_cpumask_var(&tick_nohz_full_mask);
	cpumask_copy(tick_nohz_full_mask, cpumask);
	tick_nohz_full_running = true;
पूर्ण
EXPORT_SYMBOL_GPL(tick_nohz_full_setup);

अटल पूर्णांक tick_nohz_cpu_करोwn(अचिन्हित पूर्णांक cpu)
अणु
	/*
	 * The tick_करो_समयr_cpu CPU handles housekeeping duty (unbound
	 * समयrs, workqueues, समयkeeping, ...) on behalf of full dynticks
	 * CPUs. It must reमुख्य online when nohz full is enabled.
	 */
	अगर (tick_nohz_full_running && tick_करो_समयr_cpu == cpu)
		वापस -EBUSY;
	वापस 0;
पूर्ण

व्योम __init tick_nohz_init(व्योम)
अणु
	पूर्णांक cpu, ret;

	अगर (!tick_nohz_full_running)
		वापस;

	/*
	 * Full dynticks uses irq work to drive the tick rescheduling on safe
	 * locking contexts. But then we need irq work to उठाओ its own
	 * पूर्णांकerrupts to aव्योम circular dependency on the tick
	 */
	अगर (!arch_irq_work_has_पूर्णांकerrupt()) अणु
		pr_warn("NO_HZ: Can't run full dynticks because arch doesn't support irq work self-IPIs\n");
		cpumask_clear(tick_nohz_full_mask);
		tick_nohz_full_running = false;
		वापस;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_PM_SLEEP_SMP) &&
			!IS_ENABLED(CONFIG_PM_SLEEP_SMP_NONZERO_CPU)) अणु
		cpu = smp_processor_id();

		अगर (cpumask_test_cpu(cpu, tick_nohz_full_mask)) अणु
			pr_warn("NO_HZ: Clearing %d from nohz_full range "
				"for timekeeping\n", cpu);
			cpumask_clear_cpu(cpu, tick_nohz_full_mask);
		पूर्ण
	पूर्ण

	क्रम_each_cpu(cpu, tick_nohz_full_mask)
		context_tracking_cpu_set(cpu);

	ret = cpuhp_setup_state_nocalls(CPUHP_AP_ONLINE_DYN,
					"kernel/nohz:predown", शून्य,
					tick_nohz_cpu_करोwn);
	WARN_ON(ret < 0);
	pr_info("NO_HZ: Full dynticks CPUs: %*pbl.\n",
		cpumask_pr_args(tick_nohz_full_mask));
पूर्ण
#पूर्ण_अगर

/*
 * NOHZ - aka dynamic tick functionality
 */
#अगर_घोषित CONFIG_NO_HZ_COMMON
/*
 * NO HZ enabled ?
 */
bool tick_nohz_enabled __पढ़ो_mostly  = true;
अचिन्हित दीर्घ tick_nohz_active  __पढ़ो_mostly;
/*
 * Enable / Disable tickless mode
 */
अटल पूर्णांक __init setup_tick_nohz(अक्षर *str)
अणु
	वापस (kstrtobool(str, &tick_nohz_enabled) == 0);
पूर्ण

__setup("nohz=", setup_tick_nohz);

bool tick_nohz_tick_stopped(व्योम)
अणु
	काष्ठा tick_sched *ts = this_cpu_ptr(&tick_cpu_sched);

	वापस ts->tick_stopped;
पूर्ण

bool tick_nohz_tick_stopped_cpu(पूर्णांक cpu)
अणु
	काष्ठा tick_sched *ts = per_cpu_ptr(&tick_cpu_sched, cpu);

	वापस ts->tick_stopped;
पूर्ण

/**
 * tick_nohz_update_jअगरfies - update jअगरfies when idle was पूर्णांकerrupted
 *
 * Called from पूर्णांकerrupt entry when the CPU was idle
 *
 * In हाल the sched_tick was stopped on this CPU, we have to check अगर jअगरfies
 * must be updated. Otherwise an पूर्णांकerrupt handler could use a stale jअगरfy
 * value. We करो this unconditionally on any CPU, as we करोn't know whether the
 * CPU, which has the update task asचिन्हित is in a दीर्घ sleep.
 */
अटल व्योम tick_nohz_update_jअगरfies(kसमय_प्रकार now)
अणु
	अचिन्हित दीर्घ flags;

	__this_cpu_ग_लिखो(tick_cpu_sched.idle_wakeसमय, now);

	local_irq_save(flags);
	tick_करो_update_jअगरfies64(now);
	local_irq_restore(flags);

	touch_softlockup_watchकरोg_sched();
पूर्ण

/*
 * Updates the per-CPU समय idle statistics counters
 */
अटल व्योम
update_ts_समय_stats(पूर्णांक cpu, काष्ठा tick_sched *ts, kसमय_प्रकार now, u64 *last_update_समय)
अणु
	kसमय_प्रकार delta;

	अगर (ts->idle_active) अणु
		delta = kसमय_sub(now, ts->idle_entryसमय);
		अगर (nr_ioरुको_cpu(cpu) > 0)
			ts->ioरुको_sleepसमय = kसमय_add(ts->ioरुको_sleepसमय, delta);
		अन्यथा
			ts->idle_sleepसमय = kसमय_add(ts->idle_sleepसमय, delta);
		ts->idle_entryसमय = now;
	पूर्ण

	अगर (last_update_समय)
		*last_update_समय = kसमय_प्रकारo_us(now);

पूर्ण

अटल व्योम tick_nohz_stop_idle(काष्ठा tick_sched *ts, kसमय_प्रकार now)
अणु
	update_ts_समय_stats(smp_processor_id(), ts, now, शून्य);
	ts->idle_active = 0;

	sched_घड़ी_idle_wakeup_event();
पूर्ण

अटल व्योम tick_nohz_start_idle(काष्ठा tick_sched *ts)
अणु
	ts->idle_entryसमय = kसमय_get();
	ts->idle_active = 1;
	sched_घड़ी_idle_sleep_event();
पूर्ण

/**
 * get_cpu_idle_समय_us - get the total idle समय of a CPU
 * @cpu: CPU number to query
 * @last_update_समय: variable to store update समय in. Do not update
 * counters अगर शून्य.
 *
 * Return the cumulative idle समय (since boot) क्रम a given
 * CPU, in microseconds.
 *
 * This समय is measured via accounting rather than sampling,
 * and is as accurate as kसमय_get() is.
 *
 * This function वापसs -1 अगर NOHZ is not enabled.
 */
u64 get_cpu_idle_समय_us(पूर्णांक cpu, u64 *last_update_समय)
अणु
	काष्ठा tick_sched *ts = &per_cpu(tick_cpu_sched, cpu);
	kसमय_प्रकार now, idle;

	अगर (!tick_nohz_active)
		वापस -1;

	now = kसमय_get();
	अगर (last_update_समय) अणु
		update_ts_समय_stats(cpu, ts, now, last_update_समय);
		idle = ts->idle_sleepसमय;
	पूर्ण अन्यथा अणु
		अगर (ts->idle_active && !nr_ioरुको_cpu(cpu)) अणु
			kसमय_प्रकार delta = kसमय_sub(now, ts->idle_entryसमय);

			idle = kसमय_add(ts->idle_sleepसमय, delta);
		पूर्ण अन्यथा अणु
			idle = ts->idle_sleepसमय;
		पूर्ण
	पूर्ण

	वापस kसमय_प्रकारo_us(idle);

पूर्ण
EXPORT_SYMBOL_GPL(get_cpu_idle_समय_us);

/**
 * get_cpu_ioरुको_समय_us - get the total ioरुको समय of a CPU
 * @cpu: CPU number to query
 * @last_update_समय: variable to store update समय in. Do not update
 * counters अगर शून्य.
 *
 * Return the cumulative ioरुको समय (since boot) क्रम a given
 * CPU, in microseconds.
 *
 * This समय is measured via accounting rather than sampling,
 * and is as accurate as kसमय_get() is.
 *
 * This function वापसs -1 अगर NOHZ is not enabled.
 */
u64 get_cpu_ioरुको_समय_us(पूर्णांक cpu, u64 *last_update_समय)
अणु
	काष्ठा tick_sched *ts = &per_cpu(tick_cpu_sched, cpu);
	kसमय_प्रकार now, ioरुको;

	अगर (!tick_nohz_active)
		वापस -1;

	now = kसमय_get();
	अगर (last_update_समय) अणु
		update_ts_समय_stats(cpu, ts, now, last_update_समय);
		ioरुको = ts->ioरुको_sleepसमय;
	पूर्ण अन्यथा अणु
		अगर (ts->idle_active && nr_ioरुको_cpu(cpu) > 0) अणु
			kसमय_प्रकार delta = kसमय_sub(now, ts->idle_entryसमय);

			ioरुको = kसमय_add(ts->ioरुको_sleepसमय, delta);
		पूर्ण अन्यथा अणु
			ioरुको = ts->ioरुको_sleepसमय;
		पूर्ण
	पूर्ण

	वापस kसमय_प्रकारo_us(ioरुको);
पूर्ण
EXPORT_SYMBOL_GPL(get_cpu_ioरुको_समय_us);

अटल व्योम tick_nohz_restart(काष्ठा tick_sched *ts, kसमय_प्रकार now)
अणु
	hrसमयr_cancel(&ts->sched_समयr);
	hrसमयr_set_expires(&ts->sched_समयr, ts->last_tick);

	/* Forward the समय to expire in the future */
	hrसमयr_क्रमward(&ts->sched_समयr, now, TICK_NSEC);

	अगर (ts->nohz_mode == NOHZ_MODE_HIGHRES) अणु
		hrसमयr_start_expires(&ts->sched_समयr,
				      HRTIMER_MODE_ABS_PINNED_HARD);
	पूर्ण अन्यथा अणु
		tick_program_event(hrसमयr_get_expires(&ts->sched_समयr), 1);
	पूर्ण

	/*
	 * Reset to make sure next tick stop करोesn't get fooled by past
	 * cached घड़ी deadline.
	 */
	ts->next_tick = 0;
पूर्ण

अटल अंतरभूत bool local_समयr_softirq_pending(व्योम)
अणु
	वापस local_softirq_pending() & BIT(TIMER_SOFTIRQ);
पूर्ण

अटल kसमय_प्रकार tick_nohz_next_event(काष्ठा tick_sched *ts, पूर्णांक cpu)
अणु
	u64 basemono, next_tick, next_पंचांगr, next_rcu, delta, expires;
	अचिन्हित दीर्घ basejअगरf;
	अचिन्हित पूर्णांक seq;

	/* Read jअगरfies and the समय when jअगरfies were updated last */
	करो अणु
		seq = पढ़ो_seqcount_begin(&jअगरfies_seq);
		basemono = last_jअगरfies_update;
		basejअगरf = jअगरfies;
	पूर्ण जबतक (पढ़ो_seqcount_retry(&jअगरfies_seq, seq));
	ts->last_jअगरfies = basejअगरf;
	ts->समयr_expires_base = basemono;

	/*
	 * Keep the periodic tick, when RCU, architecture or irq_work
	 * requests it.
	 * Aside of that check whether the local समयr softirq is
	 * pending. If so its a bad idea to call get_next_समयr_पूर्णांकerrupt()
	 * because there is an alपढ़ोy expired समयr, so it will request
	 * immediate expiry, which rearms the hardware समयr with a
	 * minimal delta which brings us back to this place
	 * immediately. Lather, rinse and repeat...
	 */
	अगर (rcu_needs_cpu(basemono, &next_rcu) || arch_needs_cpu() ||
	    irq_work_needs_cpu() || local_समयr_softirq_pending()) अणु
		next_tick = basemono + TICK_NSEC;
	पूर्ण अन्यथा अणु
		/*
		 * Get the next pending समयr. If high resolution
		 * समयrs are enabled this only takes the समयr wheel
		 * समयrs पूर्णांकo account. If high resolution समयrs are
		 * disabled this also looks at the next expiring
		 * hrसमयr.
		 */
		next_पंचांगr = get_next_समयr_पूर्णांकerrupt(basejअगरf, basemono);
		ts->next_समयr = next_पंचांगr;
		/* Take the next rcu event पूर्णांकo account */
		next_tick = next_rcu < next_पंचांगr ? next_rcu : next_पंचांगr;
	पूर्ण

	/*
	 * If the tick is due in the next period, keep it ticking or
	 * क्रमce prod the समयr.
	 */
	delta = next_tick - basemono;
	अगर (delta <= (u64)TICK_NSEC) अणु
		/*
		 * Tell the समयr code that the base is not idle, i.e. unकरो
		 * the effect of get_next_समयr_पूर्णांकerrupt():
		 */
		समयr_clear_idle();
		/*
		 * We've not stopped the tick yet, and there's a समयr in the
		 * next period, so no poपूर्णांक in stopping it either, bail.
		 */
		अगर (!ts->tick_stopped) अणु
			ts->समयr_expires = 0;
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * If this CPU is the one which had the करो_समयr() duty last, we limit
	 * the sleep समय to the समयkeeping max_deferment value.
	 * Otherwise we can sleep as दीर्घ as we want.
	 */
	delta = समयkeeping_max_deferment();
	अगर (cpu != tick_करो_समयr_cpu &&
	    (tick_करो_समयr_cpu != TICK_DO_TIMER_NONE || !ts->करो_समयr_last))
		delta = KTIME_MAX;

	/* Calculate the next expiry समय */
	अगर (delta < (KTIME_MAX - basemono))
		expires = basemono + delta;
	अन्यथा
		expires = KTIME_MAX;

	ts->समयr_expires = min_t(u64, expires, next_tick);

out:
	वापस ts->समयr_expires;
पूर्ण

अटल व्योम tick_nohz_stop_tick(काष्ठा tick_sched *ts, पूर्णांक cpu)
अणु
	काष्ठा घड़ी_event_device *dev = __this_cpu_पढ़ो(tick_cpu_device.evtdev);
	u64 basemono = ts->समयr_expires_base;
	u64 expires = ts->समयr_expires;
	kसमय_प्रकार tick = expires;

	/* Make sure we won't be trying to stop it twice in a row. */
	ts->समयr_expires_base = 0;

	/*
	 * If this CPU is the one which updates jअगरfies, then give up
	 * the assignment and let it be taken by the CPU which runs
	 * the tick समयr next, which might be this CPU as well. If we
	 * करोn't drop this here the jअगरfies might be stale and
	 * करो_समयr() never invoked. Keep track of the fact that it
	 * was the one which had the करो_समयr() duty last.
	 */
	अगर (cpu == tick_करो_समयr_cpu) अणु
		tick_करो_समयr_cpu = TICK_DO_TIMER_NONE;
		ts->करो_समयr_last = 1;
	पूर्ण अन्यथा अगर (tick_करो_समयr_cpu != TICK_DO_TIMER_NONE) अणु
		ts->करो_समयr_last = 0;
	पूर्ण

	/* Skip reprogram of event अगर its not changed */
	अगर (ts->tick_stopped && (expires == ts->next_tick)) अणु
		/* Sanity check: make sure घड़ीevent is actually programmed */
		अगर (tick == KTIME_MAX || ts->next_tick == hrसमयr_get_expires(&ts->sched_समयr))
			वापस;

		WARN_ON_ONCE(1);
		prपूर्णांकk_once("basemono: %llu ts->next_tick: %llu dev->next_event: %llu timer->active: %d timer->expires: %llu\n",
			    basemono, ts->next_tick, dev->next_event,
			    hrसमयr_active(&ts->sched_समयr), hrसमयr_get_expires(&ts->sched_समयr));
	पूर्ण

	/*
	 * nohz_stop_sched_tick can be called several बार beक्रमe
	 * the nohz_restart_sched_tick is called. This happens when
	 * पूर्णांकerrupts arrive which करो not cause a reschedule. In the
	 * first call we save the current tick समय, so we can restart
	 * the scheduler tick in nohz_restart_sched_tick.
	 */
	अगर (!ts->tick_stopped) अणु
		calc_load_nohz_start();
		quiet_vmstat();

		ts->last_tick = hrसमयr_get_expires(&ts->sched_समयr);
		ts->tick_stopped = 1;
		trace_tick_stop(1, TICK_DEP_MASK_NONE);
	पूर्ण

	ts->next_tick = tick;

	/*
	 * If the expiration समय == KTIME_MAX, then we simply stop
	 * the tick समयr.
	 */
	अगर (unlikely(expires == KTIME_MAX)) अणु
		अगर (ts->nohz_mode == NOHZ_MODE_HIGHRES)
			hrसमयr_cancel(&ts->sched_समयr);
		वापस;
	पूर्ण

	अगर (ts->nohz_mode == NOHZ_MODE_HIGHRES) अणु
		hrसमयr_start(&ts->sched_समयr, tick,
			      HRTIMER_MODE_ABS_PINNED_HARD);
	पूर्ण अन्यथा अणु
		hrसमयr_set_expires(&ts->sched_समयr, tick);
		tick_program_event(tick, 1);
	पूर्ण
पूर्ण

अटल व्योम tick_nohz_retain_tick(काष्ठा tick_sched *ts)
अणु
	ts->समयr_expires_base = 0;
पूर्ण

#अगर_घोषित CONFIG_NO_HZ_FULL
अटल व्योम tick_nohz_stop_sched_tick(काष्ठा tick_sched *ts, पूर्णांक cpu)
अणु
	अगर (tick_nohz_next_event(ts, cpu))
		tick_nohz_stop_tick(ts, cpu);
	अन्यथा
		tick_nohz_retain_tick(ts);
पूर्ण
#पूर्ण_अगर /* CONFIG_NO_HZ_FULL */

अटल व्योम tick_nohz_restart_sched_tick(काष्ठा tick_sched *ts, kसमय_प्रकार now)
अणु
	/* Update jअगरfies first */
	tick_करो_update_jअगरfies64(now);

	/*
	 * Clear the समयr idle flag, so we aव्योम IPIs on remote queueing and
	 * the घड़ी क्रमward checks in the enqueue path:
	 */
	समयr_clear_idle();

	calc_load_nohz_stop();
	touch_softlockup_watchकरोg_sched();
	/*
	 * Cancel the scheduled समयr and restore the tick
	 */
	ts->tick_stopped  = 0;
	ts->idle_निकाससमय = now;

	tick_nohz_restart(ts, now);
पूर्ण

अटल व्योम tick_nohz_full_update_tick(काष्ठा tick_sched *ts)
अणु
#अगर_घोषित CONFIG_NO_HZ_FULL
	पूर्णांक cpu = smp_processor_id();

	अगर (!tick_nohz_full_cpu(cpu))
		वापस;

	अगर (!ts->tick_stopped && ts->nohz_mode == NOHZ_MODE_INACTIVE)
		वापस;

	अगर (can_stop_full_tick(cpu, ts))
		tick_nohz_stop_sched_tick(ts, cpu);
	अन्यथा अगर (ts->tick_stopped)
		tick_nohz_restart_sched_tick(ts, kसमय_get());
#पूर्ण_अगर
पूर्ण

अटल bool can_stop_idle_tick(पूर्णांक cpu, काष्ठा tick_sched *ts)
अणु
	/*
	 * If this CPU is offline and it is the one which updates
	 * jअगरfies, then give up the assignment and let it be taken by
	 * the CPU which runs the tick समयr next. If we करोn't drop
	 * this here the jअगरfies might be stale and करो_समयr() never
	 * invoked.
	 */
	अगर (unlikely(!cpu_online(cpu))) अणु
		अगर (cpu == tick_करो_समयr_cpu)
			tick_करो_समयr_cpu = TICK_DO_TIMER_NONE;
		/*
		 * Make sure the CPU करोesn't get fooled by obsolete tick
		 * deadline अगर it comes back online later.
		 */
		ts->next_tick = 0;
		वापस false;
	पूर्ण

	अगर (unlikely(ts->nohz_mode == NOHZ_MODE_INACTIVE))
		वापस false;

	अगर (need_resched())
		वापस false;

	अगर (unlikely(local_softirq_pending())) अणु
		अटल पूर्णांक ratelimit;

		अगर (ratelimit < 10 && !local_bh_blocked() &&
		    (local_softirq_pending() & SOFTIRQ_STOP_IDLE_MASK)) अणु
			pr_warn("NOHZ tick-stop error: Non-RCU local softirq work is pending, handler #%02x!!!\n",
				(अचिन्हित पूर्णांक) local_softirq_pending());
			ratelimit++;
		पूर्ण
		वापस false;
	पूर्ण

	अगर (tick_nohz_full_enabled()) अणु
		/*
		 * Keep the tick alive to guarantee समयkeeping progression
		 * अगर there are full dynticks CPUs around
		 */
		अगर (tick_करो_समयr_cpu == cpu)
			वापस false;

		/* Should not happen क्रम nohz-full */
		अगर (WARN_ON_ONCE(tick_करो_समयr_cpu == TICK_DO_TIMER_NONE))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम __tick_nohz_idle_stop_tick(काष्ठा tick_sched *ts)
अणु
	kसमय_प्रकार expires;
	पूर्णांक cpu = smp_processor_id();

	/*
	 * If tick_nohz_get_sleep_length() ran tick_nohz_next_event(), the
	 * tick समयr expiration समय is known alपढ़ोy.
	 */
	अगर (ts->समयr_expires_base)
		expires = ts->समयr_expires;
	अन्यथा अगर (can_stop_idle_tick(cpu, ts))
		expires = tick_nohz_next_event(ts, cpu);
	अन्यथा
		वापस;

	ts->idle_calls++;

	अगर (expires > 0LL) अणु
		पूर्णांक was_stopped = ts->tick_stopped;

		tick_nohz_stop_tick(ts, cpu);

		ts->idle_sleeps++;
		ts->idle_expires = expires;

		अगर (!was_stopped && ts->tick_stopped) अणु
			ts->idle_jअगरfies = ts->last_jअगरfies;
			nohz_balance_enter_idle(cpu);
		पूर्ण
	पूर्ण अन्यथा अणु
		tick_nohz_retain_tick(ts);
	पूर्ण
पूर्ण

/**
 * tick_nohz_idle_stop_tick - stop the idle tick from the idle task
 *
 * When the next event is more than a tick पूर्णांकo the future, stop the idle tick
 */
व्योम tick_nohz_idle_stop_tick(व्योम)
अणु
	__tick_nohz_idle_stop_tick(this_cpu_ptr(&tick_cpu_sched));
पूर्ण

व्योम tick_nohz_idle_retain_tick(व्योम)
अणु
	tick_nohz_retain_tick(this_cpu_ptr(&tick_cpu_sched));
	/*
	 * Unकरो the effect of get_next_समयr_पूर्णांकerrupt() called from
	 * tick_nohz_next_event().
	 */
	समयr_clear_idle();
पूर्ण

/**
 * tick_nohz_idle_enter - prepare क्रम entering idle on the current CPU
 *
 * Called when we start the idle loop.
 */
व्योम tick_nohz_idle_enter(व्योम)
अणु
	काष्ठा tick_sched *ts;

	lockdep_निश्चित_irqs_enabled();

	local_irq_disable();

	ts = this_cpu_ptr(&tick_cpu_sched);

	WARN_ON_ONCE(ts->समयr_expires_base);

	ts->inidle = 1;
	tick_nohz_start_idle(ts);

	local_irq_enable();
पूर्ण

/**
 * tick_nohz_irq_निकास - update next tick event from पूर्णांकerrupt निकास
 *
 * When an पूर्णांकerrupt fires जबतक we are idle and it करोesn't cause
 * a reschedule, it may still add, modअगरy or delete a समयr, enqueue
 * an RCU callback, etc...
 * So we need to re-calculate and reprogram the next tick event.
 */
व्योम tick_nohz_irq_निकास(व्योम)
अणु
	काष्ठा tick_sched *ts = this_cpu_ptr(&tick_cpu_sched);

	अगर (ts->inidle)
		tick_nohz_start_idle(ts);
	अन्यथा
		tick_nohz_full_update_tick(ts);
पूर्ण

/**
 * tick_nohz_idle_got_tick - Check whether or not the tick handler has run
 */
bool tick_nohz_idle_got_tick(व्योम)
अणु
	काष्ठा tick_sched *ts = this_cpu_ptr(&tick_cpu_sched);

	अगर (ts->got_idle_tick) अणु
		ts->got_idle_tick = 0;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * tick_nohz_get_next_hrसमयr - वापस the next expiration समय क्रम the hrसमयr
 * or the tick, whatever that expires first. Note that, अगर the tick has been
 * stopped, it वापसs the next hrसमयr.
 *
 * Called from घातer state control code with पूर्णांकerrupts disabled
 */
kसमय_प्रकार tick_nohz_get_next_hrसमयr(व्योम)
अणु
	वापस __this_cpu_पढ़ो(tick_cpu_device.evtdev)->next_event;
पूर्ण

/**
 * tick_nohz_get_sleep_length - वापस the expected length of the current sleep
 * @delta_next: duration until the next event अगर the tick cannot be stopped
 *
 * Called from घातer state control code with पूर्णांकerrupts disabled.
 *
 * The वापस value of this function and/or the value वापसed by it through the
 * @delta_next poपूर्णांकer can be negative which must be taken पूर्णांकo account by its
 * callers.
 */
kसमय_प्रकार tick_nohz_get_sleep_length(kसमय_प्रकार *delta_next)
अणु
	काष्ठा घड़ी_event_device *dev = __this_cpu_पढ़ो(tick_cpu_device.evtdev);
	काष्ठा tick_sched *ts = this_cpu_ptr(&tick_cpu_sched);
	पूर्णांक cpu = smp_processor_id();
	/*
	 * The idle entry समय is expected to be a sufficient approximation of
	 * the current समय at this poपूर्णांक.
	 */
	kसमय_प्रकार now = ts->idle_entryसमय;
	kसमय_प्रकार next_event;

	WARN_ON_ONCE(!ts->inidle);

	*delta_next = kसमय_sub(dev->next_event, now);

	अगर (!can_stop_idle_tick(cpu, ts))
		वापस *delta_next;

	next_event = tick_nohz_next_event(ts, cpu);
	अगर (!next_event)
		वापस *delta_next;

	/*
	 * If the next highres समयr to expire is earlier than next_event, the
	 * idle governor needs to know that.
	 */
	next_event = min_t(u64, next_event,
			   hrसमयr_next_event_without(&ts->sched_समयr));

	वापस kसमय_sub(next_event, now);
पूर्ण

/**
 * tick_nohz_get_idle_calls_cpu - वापस the current idle calls counter value
 * क्रम a particular CPU.
 *
 * Called from the schedutil frequency scaling governor in scheduler context.
 */
अचिन्हित दीर्घ tick_nohz_get_idle_calls_cpu(पूर्णांक cpu)
अणु
	काष्ठा tick_sched *ts = tick_get_tick_sched(cpu);

	वापस ts->idle_calls;
पूर्ण

/**
 * tick_nohz_get_idle_calls - वापस the current idle calls counter value
 *
 * Called from the schedutil frequency scaling governor in scheduler context.
 */
अचिन्हित दीर्घ tick_nohz_get_idle_calls(व्योम)
अणु
	काष्ठा tick_sched *ts = this_cpu_ptr(&tick_cpu_sched);

	वापस ts->idle_calls;
पूर्ण

अटल व्योम tick_nohz_account_idle_ticks(काष्ठा tick_sched *ts)
अणु
#अगर_अघोषित CONFIG_VIRT_CPU_ACCOUNTING_NATIVE
	अचिन्हित दीर्घ ticks;

	अगर (vसमय_accounting_enabled_this_cpu())
		वापस;
	/*
	 * We stopped the tick in idle. Update process बार would miss the
	 * समय we slept as update_process_बार करोes only a 1 tick
	 * accounting. Enक्रमce that this is accounted to idle !
	 */
	ticks = jअगरfies - ts->idle_jअगरfies;
	/*
	 * We might be one off. Do not अक्रमomly account a huge number of ticks!
	 */
	अगर (ticks && ticks < दीर्घ_उच्च)
		account_idle_ticks(ticks);
#पूर्ण_अगर
पूर्ण

अटल व्योम __tick_nohz_idle_restart_tick(काष्ठा tick_sched *ts, kसमय_प्रकार now)
अणु
	tick_nohz_restart_sched_tick(ts, now);
	tick_nohz_account_idle_ticks(ts);
पूर्ण

व्योम tick_nohz_idle_restart_tick(व्योम)
अणु
	काष्ठा tick_sched *ts = this_cpu_ptr(&tick_cpu_sched);

	अगर (ts->tick_stopped)
		__tick_nohz_idle_restart_tick(ts, kसमय_get());
पूर्ण

/**
 * tick_nohz_idle_निकास - restart the idle tick from the idle task
 *
 * Restart the idle tick when the CPU is woken up from idle
 * This also निकास the RCU extended quiescent state. The CPU
 * can use RCU again after this function is called.
 */
व्योम tick_nohz_idle_निकास(व्योम)
अणु
	काष्ठा tick_sched *ts = this_cpu_ptr(&tick_cpu_sched);
	bool idle_active, tick_stopped;
	kसमय_प्रकार now;

	local_irq_disable();

	WARN_ON_ONCE(!ts->inidle);
	WARN_ON_ONCE(ts->समयr_expires_base);

	ts->inidle = 0;
	idle_active = ts->idle_active;
	tick_stopped = ts->tick_stopped;

	अगर (idle_active || tick_stopped)
		now = kसमय_get();

	अगर (idle_active)
		tick_nohz_stop_idle(ts, now);

	अगर (tick_stopped)
		__tick_nohz_idle_restart_tick(ts, now);

	local_irq_enable();
पूर्ण

/*
 * The nohz low res पूर्णांकerrupt handler
 */
अटल व्योम tick_nohz_handler(काष्ठा घड़ी_event_device *dev)
अणु
	काष्ठा tick_sched *ts = this_cpu_ptr(&tick_cpu_sched);
	काष्ठा pt_regs *regs = get_irq_regs();
	kसमय_प्रकार now = kसमय_get();

	dev->next_event = KTIME_MAX;

	tick_sched_करो_समयr(ts, now);
	tick_sched_handle(ts, regs);

	/* No need to reprogram अगर we are running tickless  */
	अगर (unlikely(ts->tick_stopped))
		वापस;

	hrसमयr_क्रमward(&ts->sched_समयr, now, TICK_NSEC);
	tick_program_event(hrसमयr_get_expires(&ts->sched_समयr), 1);
पूर्ण

अटल अंतरभूत व्योम tick_nohz_activate(काष्ठा tick_sched *ts, पूर्णांक mode)
अणु
	अगर (!tick_nohz_enabled)
		वापस;
	ts->nohz_mode = mode;
	/* One update is enough */
	अगर (!test_and_set_bit(0, &tick_nohz_active))
		समयrs_update_nohz();
पूर्ण

/**
 * tick_nohz_चयन_to_nohz - चयन to nohz mode
 */
अटल व्योम tick_nohz_चयन_to_nohz(व्योम)
अणु
	काष्ठा tick_sched *ts = this_cpu_ptr(&tick_cpu_sched);
	kसमय_प्रकार next;

	अगर (!tick_nohz_enabled)
		वापस;

	अगर (tick_चयन_to_oneshot(tick_nohz_handler))
		वापस;

	/*
	 * Recycle the hrसमयr in ts, so we can share the
	 * hrसमयr_क्रमward with the highres code.
	 */
	hrसमयr_init(&ts->sched_समयr, CLOCK_MONOTONIC, HRTIMER_MODE_ABS_HARD);
	/* Get the next period */
	next = tick_init_jअगरfy_update();

	hrसमयr_set_expires(&ts->sched_समयr, next);
	hrसमयr_क्रमward_now(&ts->sched_समयr, TICK_NSEC);
	tick_program_event(hrसमयr_get_expires(&ts->sched_समयr), 1);
	tick_nohz_activate(ts, NOHZ_MODE_LOWRES);
पूर्ण

अटल अंतरभूत व्योम tick_nohz_irq_enter(व्योम)
अणु
	काष्ठा tick_sched *ts = this_cpu_ptr(&tick_cpu_sched);
	kसमय_प्रकार now;

	अगर (!ts->idle_active && !ts->tick_stopped)
		वापस;
	now = kसमय_get();
	अगर (ts->idle_active)
		tick_nohz_stop_idle(ts, now);
	अगर (ts->tick_stopped)
		tick_nohz_update_jअगरfies(now);
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम tick_nohz_चयन_to_nohz(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम tick_nohz_irq_enter(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम tick_nohz_activate(काष्ठा tick_sched *ts, पूर्णांक mode) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_NO_HZ_COMMON */

/*
 * Called from irq_enter to notअगरy about the possible पूर्णांकerruption of idle()
 */
व्योम tick_irq_enter(व्योम)
अणु
	tick_check_oneshot_broadcast_this_cpu();
	tick_nohz_irq_enter();
पूर्ण

/*
 * High resolution समयr specअगरic code
 */
#अगर_घोषित CONFIG_HIGH_RES_TIMERS
/*
 * We rearm the समयr until we get disabled by the idle code.
 * Called with पूर्णांकerrupts disabled.
 */
अटल क्रमागत hrसमयr_restart tick_sched_समयr(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा tick_sched *ts =
		container_of(समयr, काष्ठा tick_sched, sched_समयr);
	काष्ठा pt_regs *regs = get_irq_regs();
	kसमय_प्रकार now = kसमय_get();

	tick_sched_करो_समयr(ts, now);

	/*
	 * Do not call, when we are not in irq context and have
	 * no valid regs poपूर्णांकer
	 */
	अगर (regs)
		tick_sched_handle(ts, regs);
	अन्यथा
		ts->next_tick = 0;

	/* No need to reprogram अगर we are in idle or full dynticks mode */
	अगर (unlikely(ts->tick_stopped))
		वापस HRTIMER_NORESTART;

	hrसमयr_क्रमward(समयr, now, TICK_NSEC);

	वापस HRTIMER_RESTART;
पूर्ण

अटल पूर्णांक sched_skew_tick;

अटल पूर्णांक __init skew_tick(अक्षर *str)
अणु
	get_option(&str, &sched_skew_tick);

	वापस 0;
पूर्ण
early_param("skew_tick", skew_tick);

/**
 * tick_setup_sched_समयr - setup the tick emulation समयr
 */
व्योम tick_setup_sched_समयr(व्योम)
अणु
	काष्ठा tick_sched *ts = this_cpu_ptr(&tick_cpu_sched);
	kसमय_प्रकार now = kसमय_get();

	/*
	 * Emulate tick processing via per-CPU hrसमयrs:
	 */
	hrसमयr_init(&ts->sched_समयr, CLOCK_MONOTONIC, HRTIMER_MODE_ABS_HARD);
	ts->sched_समयr.function = tick_sched_समयr;

	/* Get the next period (per-CPU) */
	hrसमयr_set_expires(&ts->sched_समयr, tick_init_jअगरfy_update());

	/* Offset the tick to avert jअगरfies_lock contention. */
	अगर (sched_skew_tick) अणु
		u64 offset = TICK_NSEC >> 1;
		करो_भाग(offset, num_possible_cpus());
		offset *= smp_processor_id();
		hrसमयr_add_expires_ns(&ts->sched_समयr, offset);
	पूर्ण

	hrसमयr_क्रमward(&ts->sched_समयr, now, TICK_NSEC);
	hrसमयr_start_expires(&ts->sched_समयr, HRTIMER_MODE_ABS_PINNED_HARD);
	tick_nohz_activate(ts, NOHZ_MODE_HIGHRES);
पूर्ण
#पूर्ण_अगर /* HIGH_RES_TIMERS */

#अगर defined CONFIG_NO_HZ_COMMON || defined CONFIG_HIGH_RES_TIMERS
व्योम tick_cancel_sched_समयr(पूर्णांक cpu)
अणु
	काष्ठा tick_sched *ts = &per_cpu(tick_cpu_sched, cpu);

# अगरdef CONFIG_HIGH_RES_TIMERS
	अगर (ts->sched_समयr.base)
		hrसमयr_cancel(&ts->sched_समयr);
# endअगर

	स_रखो(ts, 0, माप(*ts));
पूर्ण
#पूर्ण_अगर

/**
 * Async notअगरication about घड़ीsource changes
 */
व्योम tick_घड़ी_notअगरy(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu)
		set_bit(0, &per_cpu(tick_cpu_sched, cpu).check_घड़ीs);
पूर्ण

/*
 * Async notअगरication about घड़ी event changes
 */
व्योम tick_oneshot_notअगरy(व्योम)
अणु
	काष्ठा tick_sched *ts = this_cpu_ptr(&tick_cpu_sched);

	set_bit(0, &ts->check_घड़ीs);
पूर्ण

/**
 * Check, अगर a change happened, which makes oneshot possible.
 *
 * Called cyclic from the hrसमयr softirq (driven by the समयr
 * softirq) allow_nohz संकेतs, that we can चयन पूर्णांकo low-res nohz
 * mode, because high resolution समयrs are disabled (either compile
 * or runसमय). Called with पूर्णांकerrupts disabled.
 */
पूर्णांक tick_check_oneshot_change(पूर्णांक allow_nohz)
अणु
	काष्ठा tick_sched *ts = this_cpu_ptr(&tick_cpu_sched);

	अगर (!test_and_clear_bit(0, &ts->check_घड़ीs))
		वापस 0;

	अगर (ts->nohz_mode != NOHZ_MODE_INACTIVE)
		वापस 0;

	अगर (!समयkeeping_valid_क्रम_hres() || !tick_is_oneshot_available())
		वापस 0;

	अगर (!allow_nohz)
		वापस 1;

	tick_nohz_चयन_to_nohz();
	वापस 0;
पूर्ण
