<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic entry poपूर्णांकs क्रम the idle thपढ़ोs and
 * implementation of the idle task scheduling class.
 *
 * (NOTE: these are not related to SCHED_IDLE batch scheduled
 *        tasks which are handled in sched/fair.c )
 */
#समावेश "sched.h"

#समावेश <trace/events/घातer.h>

/* Linker adds these: start and end of __cpuidle functions */
बाह्य अक्षर __cpuidle_text_start[], __cpuidle_text_end[];

/**
 * sched_idle_set_state - Record idle state क्रम the current CPU.
 * @idle_state: State to record.
 */
व्योम sched_idle_set_state(काष्ठा cpuidle_state *idle_state)
अणु
	idle_set_state(this_rq(), idle_state);
पूर्ण

अटल पूर्णांक __पढ़ो_mostly cpu_idle_क्रमce_poll;

व्योम cpu_idle_poll_ctrl(bool enable)
अणु
	अगर (enable) अणु
		cpu_idle_क्रमce_poll++;
	पूर्ण अन्यथा अणु
		cpu_idle_क्रमce_poll--;
		WARN_ON_ONCE(cpu_idle_क्रमce_poll < 0);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_GENERIC_IDLE_POLL_SETUP
अटल पूर्णांक __init cpu_idle_poll_setup(अक्षर *__unused)
अणु
	cpu_idle_क्रमce_poll = 1;

	वापस 1;
पूर्ण
__setup("nohlt", cpu_idle_poll_setup);

अटल पूर्णांक __init cpu_idle_nopoll_setup(अक्षर *__unused)
अणु
	cpu_idle_क्रमce_poll = 0;

	वापस 1;
पूर्ण
__setup("hlt", cpu_idle_nopoll_setup);
#पूर्ण_अगर

अटल noअंतरभूत पूर्णांक __cpuidle cpu_idle_poll(व्योम)
अणु
	trace_cpu_idle(0, smp_processor_id());
	stop_critical_timings();
	rcu_idle_enter();
	local_irq_enable();

	जबतक (!tअगर_need_resched() &&
	       (cpu_idle_क्रमce_poll || tick_check_broadcast_expired()))
		cpu_relax();

	rcu_idle_निकास();
	start_critical_timings();
	trace_cpu_idle(PWR_EVENT_EXIT, smp_processor_id());

	वापस 1;
पूर्ण

/* Weak implementations क्रम optional arch specअगरic functions */
व्योम __weak arch_cpu_idle_prepare(व्योम) अणु पूर्ण
व्योम __weak arch_cpu_idle_enter(व्योम) अणु पूर्ण
व्योम __weak arch_cpu_idle_निकास(व्योम) अणु पूर्ण
व्योम __weak arch_cpu_idle_dead(व्योम) अणु पूर्ण
व्योम __weak arch_cpu_idle(व्योम)
अणु
	cpu_idle_क्रमce_poll = 1;
	raw_local_irq_enable();
पूर्ण

/**
 * शेष_idle_call - Default CPU idle routine.
 *
 * To use when the cpuidle framework cannot be used.
 */
व्योम __cpuidle शेष_idle_call(व्योम)
अणु
	अगर (current_clr_polling_and_test()) अणु
		local_irq_enable();
	पूर्ण अन्यथा अणु

		trace_cpu_idle(1, smp_processor_id());
		stop_critical_timings();

		/*
		 * arch_cpu_idle() is supposed to enable IRQs, however
		 * we can't करो that because of RCU and tracing.
		 *
		 * Trace IRQs enable here, then चयन off RCU, and have
		 * arch_cpu_idle() use raw_local_irq_enable(). Note that
		 * rcu_idle_enter() relies on lockdep IRQ state, so चयन that
		 * last -- this is very similar to the entry code.
		 */
		trace_hardirqs_on_prepare();
		lockdep_hardirqs_on_prepare(_THIS_IP_);
		rcu_idle_enter();
		lockdep_hardirqs_on(_THIS_IP_);

		arch_cpu_idle();

		/*
		 * OK, so IRQs are enabled here, but RCU needs them disabled to
		 * turn itself back on.. funny thing is that disabling IRQs
		 * will cause tracing, which needs RCU. Jump through hoops to
		 * make it 'work'.
		 */
		raw_local_irq_disable();
		lockdep_hardirqs_off(_THIS_IP_);
		rcu_idle_निकास();
		lockdep_hardirqs_on(_THIS_IP_);
		raw_local_irq_enable();

		start_critical_timings();
		trace_cpu_idle(PWR_EVENT_EXIT, smp_processor_id());
	पूर्ण
पूर्ण

अटल पूर्णांक call_cpuidle_s2idle(काष्ठा cpuidle_driver *drv,
			       काष्ठा cpuidle_device *dev)
अणु
	अगर (current_clr_polling_and_test())
		वापस -EBUSY;

	वापस cpuidle_enter_s2idle(drv, dev);
पूर्ण

अटल पूर्णांक call_cpuidle(काष्ठा cpuidle_driver *drv, काष्ठा cpuidle_device *dev,
		      पूर्णांक next_state)
अणु
	/*
	 * The idle task must be scheduled, it is poपूर्णांकless to go to idle, just
	 * update no idle residency and वापस.
	 */
	अगर (current_clr_polling_and_test()) अणु
		dev->last_residency_ns = 0;
		local_irq_enable();
		वापस -EBUSY;
	पूर्ण

	/*
	 * Enter the idle state previously वापसed by the governor decision.
	 * This function will block until an पूर्णांकerrupt occurs and will take
	 * care of re-enabling the local पूर्णांकerrupts
	 */
	वापस cpuidle_enter(drv, dev, next_state);
पूर्ण

/**
 * cpuidle_idle_call - the मुख्य idle function
 *
 * NOTE: no locks or semaphores should be used here
 *
 * On architectures that support TIF_POLLING_NRFLAG, is called with polling
 * set, and it वापसs with polling set.  If it ever stops polling, it
 * must clear the polling bit.
 */
अटल व्योम cpuidle_idle_call(व्योम)
अणु
	काष्ठा cpuidle_device *dev = cpuidle_get_device();
	काष्ठा cpuidle_driver *drv = cpuidle_get_cpu_driver(dev);
	पूर्णांक next_state, entered_state;

	/*
	 * Check अगर the idle task must be rescheduled. If it is the
	 * हाल, निकास the function after re-enabling the local irq.
	 */
	अगर (need_resched()) अणु
		local_irq_enable();
		वापस;
	पूर्ण

	/*
	 * The RCU framework needs to be told that we are entering an idle
	 * section, so no more rcu पढ़ो side critical sections and one more
	 * step to the grace period
	 */

	अगर (cpuidle_not_available(drv, dev)) अणु
		tick_nohz_idle_stop_tick();

		शेष_idle_call();
		जाओ निकास_idle;
	पूर्ण

	/*
	 * Suspend-to-idle ("s2idle") is a प्रणाली state in which all user space
	 * has been frozen, all I/O devices have been suspended and the only
	 * activity happens here and in पूर्णांकerrupts (अगर any). In that हाल bypass
	 * the cpuidle governor and go straight क्रम the deepest idle state
	 * available.  Possibly also suspend the local tick and the entire
	 * समयkeeping to prevent समयr पूर्णांकerrupts from kicking us out of idle
	 * until a proper wakeup पूर्णांकerrupt happens.
	 */

	अगर (idle_should_enter_s2idle() || dev->क्रमced_idle_latency_limit_ns) अणु
		u64 max_latency_ns;

		अगर (idle_should_enter_s2idle()) अणु

			entered_state = call_cpuidle_s2idle(drv, dev);
			अगर (entered_state > 0)
				जाओ निकास_idle;

			max_latency_ns = U64_MAX;
		पूर्ण अन्यथा अणु
			max_latency_ns = dev->क्रमced_idle_latency_limit_ns;
		पूर्ण

		tick_nohz_idle_stop_tick();

		next_state = cpuidle_find_deepest_state(drv, dev, max_latency_ns);
		call_cpuidle(drv, dev, next_state);
	पूर्ण अन्यथा अणु
		bool stop_tick = true;

		/*
		 * Ask the cpuidle framework to choose a convenient idle state.
		 */
		next_state = cpuidle_select(drv, dev, &stop_tick);

		अगर (stop_tick || tick_nohz_tick_stopped())
			tick_nohz_idle_stop_tick();
		अन्यथा
			tick_nohz_idle_retain_tick();

		entered_state = call_cpuidle(drv, dev, next_state);
		/*
		 * Give the governor an opportunity to reflect on the outcome
		 */
		cpuidle_reflect(dev, entered_state);
	पूर्ण

निकास_idle:
	__current_set_polling();

	/*
	 * It is up to the idle functions to reenable local पूर्णांकerrupts
	 */
	अगर (WARN_ON_ONCE(irqs_disabled()))
		local_irq_enable();
पूर्ण

/*
 * Generic idle loop implementation
 *
 * Called with polling cleared.
 */
अटल व्योम करो_idle(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();

	/*
	 * Check अगर we need to update blocked load
	 */
	nohz_run_idle_balance(cpu);

	/*
	 * If the arch has a polling bit, we मुख्यtain an invariant:
	 *
	 * Our polling bit is clear अगर we're not scheduled (i.e. अगर rq->curr !=
	 * rq->idle). This means that, अगर rq->idle has the polling bit set,
	 * then setting need_resched is guaranteed to cause the CPU to
	 * reschedule.
	 */

	__current_set_polling();
	tick_nohz_idle_enter();

	जबतक (!need_resched()) अणु
		rmb();

		local_irq_disable();

		अगर (cpu_is_offline(cpu)) अणु
			tick_nohz_idle_stop_tick();
			cpuhp_report_idle_dead();
			arch_cpu_idle_dead();
		पूर्ण

		arch_cpu_idle_enter();
		rcu_nocb_flush_deferred_wakeup();

		/*
		 * In poll mode we reenable पूर्णांकerrupts and spin. Also अगर we
		 * detected in the wakeup from idle path that the tick
		 * broadcast device expired क्रम us, we करोn't want to go deep
		 * idle as we know that the IPI is going to arrive right away.
		 */
		अगर (cpu_idle_क्रमce_poll || tick_check_broadcast_expired()) अणु
			tick_nohz_idle_restart_tick();
			cpu_idle_poll();
		पूर्ण अन्यथा अणु
			cpuidle_idle_call();
		पूर्ण
		arch_cpu_idle_निकास();
	पूर्ण

	/*
	 * Since we fell out of the loop above, we know TIF_NEED_RESCHED must
	 * be set, propagate it पूर्णांकo PREEMPT_NEED_RESCHED.
	 *
	 * This is required because क्रम polling idle loops we will not have had
	 * an IPI to fold the state क्रम us.
	 */
	preempt_set_need_resched();
	tick_nohz_idle_निकास();
	__current_clr_polling();

	/*
	 * We promise to call sched_ttwu_pending() and reschedule अगर
	 * need_resched() is set जबतक polling is set. That means that clearing
	 * polling needs to be visible beक्रमe करोing these things.
	 */
	smp_mb__after_atomic();

	/*
	 * RCU relies on this call to be करोne outside of an RCU पढ़ो-side
	 * critical section.
	 */
	flush_smp_call_function_from_idle();
	schedule_idle();

	अगर (unlikely(klp_patch_pending(current)))
		klp_update_patch_state(current);
पूर्ण

bool cpu_in_idle(अचिन्हित दीर्घ pc)
अणु
	वापस pc >= (अचिन्हित दीर्घ)__cpuidle_text_start &&
		pc < (अचिन्हित दीर्घ)__cpuidle_text_end;
पूर्ण

काष्ठा idle_समयr अणु
	काष्ठा hrसमयr समयr;
	पूर्णांक करोne;
पूर्ण;

अटल क्रमागत hrसमयr_restart idle_inject_समयr_fn(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा idle_समयr *it = container_of(समयr, काष्ठा idle_समयr, समयr);

	WRITE_ONCE(it->करोne, 1);
	set_tsk_need_resched(current);

	वापस HRTIMER_NORESTART;
पूर्ण

व्योम play_idle_precise(u64 duration_ns, u64 latency_ns)
अणु
	काष्ठा idle_समयr it;

	/*
	 * Only FIFO tasks can disable the tick since they करोn't need the क्रमced
	 * preemption.
	 */
	WARN_ON_ONCE(current->policy != SCHED_FIFO);
	WARN_ON_ONCE(current->nr_cpus_allowed != 1);
	WARN_ON_ONCE(!(current->flags & PF_KTHREAD));
	WARN_ON_ONCE(!(current->flags & PF_NO_SETAFFINITY));
	WARN_ON_ONCE(!duration_ns);
	WARN_ON_ONCE(current->mm);

	rcu_sleep_check();
	preempt_disable();
	current->flags |= PF_IDLE;
	cpuidle_use_deepest_state(latency_ns);

	it.करोne = 0;
	hrसमयr_init_on_stack(&it.समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	it.समयr.function = idle_inject_समयr_fn;
	hrसमयr_start(&it.समयr, ns_to_kसमय(duration_ns),
		      HRTIMER_MODE_REL_PINNED);

	जबतक (!READ_ONCE(it.करोne))
		करो_idle();

	cpuidle_use_deepest_state(0);
	current->flags &= ~PF_IDLE;

	preempt_fold_need_resched();
	preempt_enable();
पूर्ण
EXPORT_SYMBOL_GPL(play_idle_precise);

व्योम cpu_startup_entry(क्रमागत cpuhp_state state)
अणु
	arch_cpu_idle_prepare();
	cpuhp_online_idle(state);
	जबतक (1)
		करो_idle();
पूर्ण

/*
 * idle-task scheduling class.
 */

#अगर_घोषित CONFIG_SMP
अटल पूर्णांक
select_task_rq_idle(काष्ठा task_काष्ठा *p, पूर्णांक cpu, पूर्णांक flags)
अणु
	वापस task_cpu(p); /* IDLE tasks as never migrated */
पूर्ण

अटल पूर्णांक
balance_idle(काष्ठा rq *rq, काष्ठा task_काष्ठा *prev, काष्ठा rq_flags *rf)
अणु
	वापस WARN_ON_ONCE(1);
पूर्ण
#पूर्ण_अगर

/*
 * Idle tasks are unconditionally rescheduled:
 */
अटल व्योम check_preempt_curr_idle(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक flags)
अणु
	resched_curr(rq);
पूर्ण

अटल व्योम put_prev_task_idle(काष्ठा rq *rq, काष्ठा task_काष्ठा *prev)
अणु
पूर्ण

अटल व्योम set_next_task_idle(काष्ठा rq *rq, काष्ठा task_काष्ठा *next, bool first)
अणु
	update_idle_core(rq);
	schedstat_inc(rq->sched_goidle);
पूर्ण

काष्ठा task_काष्ठा *pick_next_task_idle(काष्ठा rq *rq)
अणु
	काष्ठा task_काष्ठा *next = rq->idle;

	set_next_task_idle(rq, next, true);

	वापस next;
पूर्ण

/*
 * It is not legal to sleep in the idle task - prपूर्णांक a warning
 * message अगर some code attempts to करो it:
 */
अटल व्योम
dequeue_task_idle(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक flags)
अणु
	raw_spin_unlock_irq(&rq->lock);
	prपूर्णांकk(KERN_ERR "bad: scheduling from the idle thread!\n");
	dump_stack();
	raw_spin_lock_irq(&rq->lock);
पूर्ण

/*
 * scheduler tick hitting a task of our scheduling class.
 *
 * NOTE: This function can be called remotely by the tick offload that
 * goes aदीर्घ full dynticks. Thereक्रमe no local assumption can be made
 * and everything must be accessed through the @rq and @curr passed in
 * parameters.
 */
अटल व्योम task_tick_idle(काष्ठा rq *rq, काष्ठा task_काष्ठा *curr, पूर्णांक queued)
अणु
पूर्ण

अटल व्योम चयनed_to_idle(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
	BUG();
पूर्ण

अटल व्योम
prio_changed_idle(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक oldprio)
अणु
	BUG();
पूर्ण

अटल व्योम update_curr_idle(काष्ठा rq *rq)
अणु
पूर्ण

/*
 * Simple, special scheduling class क्रम the per-CPU idle tasks:
 */
DEFINE_SCHED_CLASS(idle) = अणु

	/* no enqueue/yield_task क्रम idle tasks */

	/* dequeue is not valid, we prपूर्णांक a debug message there: */
	.dequeue_task		= dequeue_task_idle,

	.check_preempt_curr	= check_preempt_curr_idle,

	.pick_next_task		= pick_next_task_idle,
	.put_prev_task		= put_prev_task_idle,
	.set_next_task          = set_next_task_idle,

#अगर_घोषित CONFIG_SMP
	.balance		= balance_idle,
	.select_task_rq		= select_task_rq_idle,
	.set_cpus_allowed	= set_cpus_allowed_common,
#पूर्ण_अगर

	.task_tick		= task_tick_idle,

	.prio_changed		= prio_changed_idle,
	.चयनed_to		= चयनed_to_idle,
	.update_curr		= update_curr_idle,
पूर्ण;
