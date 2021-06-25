<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  kernel/sched/core.c
 *
 *  Core kernel scheduler code and related syscalls
 *
 *  Copyright (C) 1991-2002  Linus Torvalds
 */
#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/sched.h>
#अघोषित CREATE_TRACE_POINTS

#समावेश "sched.h"

#समावेश <linux/nospec.h>

#समावेश <linux/kcov.h>
#समावेश <linux/scs.h>

#समावेश <यंत्र/चयन_to.h>
#समावेश <यंत्र/tlb.h>

#समावेश "../workqueue_internal.h"
#समावेश "../../fs/io-wq.h"
#समावेश "../smpboot.h"

#समावेश "pelt.h"
#समावेश "smp.h"

/*
 * Export tracepoपूर्णांकs that act as a bare tracehook (ie: have no trace event
 * associated with them) to allow बाह्यal modules to probe them.
 */
EXPORT_TRACEPOINT_SYMBOL_GPL(pelt_cfs_tp);
EXPORT_TRACEPOINT_SYMBOL_GPL(pelt_rt_tp);
EXPORT_TRACEPOINT_SYMBOL_GPL(pelt_dl_tp);
EXPORT_TRACEPOINT_SYMBOL_GPL(pelt_irq_tp);
EXPORT_TRACEPOINT_SYMBOL_GPL(pelt_se_tp);
EXPORT_TRACEPOINT_SYMBOL_GPL(sched_cpu_capacity_tp);
EXPORT_TRACEPOINT_SYMBOL_GPL(sched_overutilized_tp);
EXPORT_TRACEPOINT_SYMBOL_GPL(sched_util_est_cfs_tp);
EXPORT_TRACEPOINT_SYMBOL_GPL(sched_util_est_se_tp);
EXPORT_TRACEPOINT_SYMBOL_GPL(sched_update_nr_running_tp);

DEFINE_PER_CPU_SHARED_ALIGNED(काष्ठा rq, runqueues);

#अगर_घोषित CONFIG_SCHED_DEBUG
/*
 * Debugging: various feature bits
 *
 * If SCHED_DEBUG is disabled, each compilation unit has its own copy of
 * sysctl_sched_features, defined in sched.h, to allow स्थिरants propagation
 * at compile समय and compiler optimization based on features शेष.
 */
#घोषणा SCHED_FEAT(name, enabled)	\
	(1UL << __SCHED_FEAT_##name) * enabled |
स्थिर_debug अचिन्हित पूर्णांक sysctl_sched_features =
#समावेश "features.h"
	0;
#अघोषित SCHED_FEAT

/*
 * Prपूर्णांक a warning अगर need_resched is set क्रम the given duration (अगर
 * LATENCY_WARN is enabled).
 *
 * If sysctl_resched_latency_warn_once is set, only one warning will be shown
 * per boot.
 */
__पढ़ो_mostly पूर्णांक sysctl_resched_latency_warn_ms = 100;
__पढ़ो_mostly पूर्णांक sysctl_resched_latency_warn_once = 1;
#पूर्ण_अगर /* CONFIG_SCHED_DEBUG */

/*
 * Number of tasks to iterate in a single balance run.
 * Limited because this is करोne with IRQs disabled.
 */
स्थिर_debug अचिन्हित पूर्णांक sysctl_sched_nr_migrate = 32;

/*
 * period over which we measure -rt task CPU usage in us.
 * शेष: 1s
 */
अचिन्हित पूर्णांक sysctl_sched_rt_period = 1000000;

__पढ़ो_mostly पूर्णांक scheduler_running;

/*
 * part of the period that we allow rt tasks to run in us.
 * शेष: 0.95s
 */
पूर्णांक sysctl_sched_rt_runसमय = 950000;


/*
 * Serialization rules:
 *
 * Lock order:
 *
 *   p->pi_lock
 *     rq->lock
 *       hrसमयr_cpu_base->lock (hrसमयr_start() क्रम bandwidth controls)
 *
 *  rq1->lock
 *    rq2->lock  where: rq1 < rq2
 *
 * Regular state:
 *
 * Normal scheduling state is serialized by rq->lock. __schedule() takes the
 * local CPU's rq->lock, it optionally हटाओs the task from the runqueue and
 * always looks at the local rq data काष्ठाures to find the most eligible task
 * to run next.
 *
 * Task enqueue is also under rq->lock, possibly taken from another CPU.
 * Wakeups from another LLC करोमुख्य might use an IPI to transfer the enqueue to
 * the local CPU to aव्योम bouncing the runqueue state around [ see
 * ttwu_queue_wakelist() ]
 *
 * Task wakeup, specअगरically wakeups that involve migration, are horribly
 * complicated to aव्योम having to take two rq->locks.
 *
 * Special state:
 *
 * System-calls and anything बाह्यal will use task_rq_lock() which acquires
 * both p->pi_lock and rq->lock. As a consequence the state they change is
 * stable जबतक holding either lock:
 *
 *  - sched_setaffinity()/
 *    set_cpus_allowed_ptr():	p->cpus_ptr, p->nr_cpus_allowed
 *  - set_user_nice():		p->se.load, p->*prio
 *  - __sched_setscheduler():	p->sched_class, p->policy, p->*prio,
 *				p->se.load, p->rt_priority,
 *				p->dl.dl_अणुrunसमय, deadline, period, flags, bw, densityपूर्ण
 *  - sched_setnuma():		p->numa_preferred_nid
 *  - sched_move_task()/
 *    cpu_cgroup_विभाजन():	p->sched_task_group
 *  - uclamp_update_active()	p->uclamp*
 *
 * p->state <- TASK_*:
 *
 *   is changed locklessly using set_current_state(), __set_current_state() or
 *   set_special_state(), see their respective comments, or by
 *   try_to_wake_up(). This latter uses p->pi_lock to serialize against
 *   concurrent self.
 *
 * p->on_rq <- अणु 0, 1 = TASK_ON_RQ_QUEUED, 2 = TASK_ON_RQ_MIGRATING पूर्ण:
 *
 *   is set by activate_task() and cleared by deactivate_task(), under
 *   rq->lock. Non-zero indicates the task is runnable, the special
 *   ON_RQ_MIGRATING state is used क्रम migration without holding both
 *   rq->locks. It indicates task_cpu() is not stable, see task_rq_lock().
 *
 * p->on_cpu <- अणु 0, 1 पूर्ण:
 *
 *   is set by prepare_task() and cleared by finish_task() such that it will be
 *   set beक्रमe p is scheduled-in and cleared after p is scheduled-out, both
 *   under rq->lock. Non-zero indicates the task is running on its CPU.
 *
 *   [ The astute पढ़ोer will observe that it is possible क्रम two tasks on one
 *     CPU to have ->on_cpu = 1 at the same समय. ]
 *
 * task_cpu(p): is changed by set_task_cpu(), the rules are:
 *
 *  - Don't call set_task_cpu() on a blocked task:
 *
 *    We करोn't care what CPU we're not running on, this simplअगरies hotplug,
 *    the CPU assignment of blocked tasks isn't required to be valid.
 *
 *  - क्रम try_to_wake_up(), called under p->pi_lock:
 *
 *    This allows try_to_wake_up() to only take one rq->lock, see its comment.
 *
 *  - क्रम migration called under rq->lock:
 *    [ see task_on_rq_migrating() in task_rq_lock() ]
 *
 *    o move_queued_task()
 *    o detach_task()
 *
 *  - क्रम migration called under द्विगुन_rq_lock():
 *
 *    o __migrate_swap_task()
 *    o push_rt_task() / pull_rt_task()
 *    o push_dl_task() / pull_dl_task()
 *    o dl_task_offline_migration()
 *
 */

/*
 * __task_rq_lock - lock the rq @p resides on.
 */
काष्ठा rq *__task_rq_lock(काष्ठा task_काष्ठा *p, काष्ठा rq_flags *rf)
	__acquires(rq->lock)
अणु
	काष्ठा rq *rq;

	lockdep_निश्चित_held(&p->pi_lock);

	क्रम (;;) अणु
		rq = task_rq(p);
		raw_spin_lock(&rq->lock);
		अगर (likely(rq == task_rq(p) && !task_on_rq_migrating(p))) अणु
			rq_pin_lock(rq, rf);
			वापस rq;
		पूर्ण
		raw_spin_unlock(&rq->lock);

		जबतक (unlikely(task_on_rq_migrating(p)))
			cpu_relax();
	पूर्ण
पूर्ण

/*
 * task_rq_lock - lock p->pi_lock and lock the rq @p resides on.
 */
काष्ठा rq *task_rq_lock(काष्ठा task_काष्ठा *p, काष्ठा rq_flags *rf)
	__acquires(p->pi_lock)
	__acquires(rq->lock)
अणु
	काष्ठा rq *rq;

	क्रम (;;) अणु
		raw_spin_lock_irqsave(&p->pi_lock, rf->flags);
		rq = task_rq(p);
		raw_spin_lock(&rq->lock);
		/*
		 *	move_queued_task()		task_rq_lock()
		 *
		 *	ACQUIRE (rq->lock)
		 *	[S] ->on_rq = MIGRATING		[L] rq = task_rq()
		 *	WMB (__set_task_cpu())		ACQUIRE (rq->lock);
		 *	[S] ->cpu = new_cpu		[L] task_rq()
		 *					[L] ->on_rq
		 *	RELEASE (rq->lock)
		 *
		 * If we observe the old CPU in task_rq_lock(), the acquire of
		 * the old rq->lock will fully serialize against the stores.
		 *
		 * If we observe the new CPU in task_rq_lock(), the address
		 * dependency headed by '[L] rq = task_rq()' and the acquire
		 * will pair with the WMB to ensure we then also see migrating.
		 */
		अगर (likely(rq == task_rq(p) && !task_on_rq_migrating(p))) अणु
			rq_pin_lock(rq, rf);
			वापस rq;
		पूर्ण
		raw_spin_unlock(&rq->lock);
		raw_spin_unlock_irqrestore(&p->pi_lock, rf->flags);

		जबतक (unlikely(task_on_rq_migrating(p)))
			cpu_relax();
	पूर्ण
पूर्ण

/*
 * RQ-घड़ी updating methods:
 */

अटल व्योम update_rq_घड़ी_प्रकारask(काष्ठा rq *rq, s64 delta)
अणु
/*
 * In theory, the compile should just see 0 here, and optimize out the call
 * to sched_rt_avg_update. But I करोn't trust it...
 */
	s64 __maybe_unused steal = 0, irq_delta = 0;

#अगर_घोषित CONFIG_IRQ_TIME_ACCOUNTING
	irq_delta = irq_समय_पढ़ो(cpu_of(rq)) - rq->prev_irq_समय;

	/*
	 * Since irq_समय is only updated on अणुsoft,पूर्णirq_निकास, we might run पूर्णांकo
	 * this हाल when a previous update_rq_घड़ी() happened inside a
	 * अणुsoft,पूर्णirq region.
	 *
	 * When this happens, we stop ->घड़ी_प्रकारask and only update the
	 * prev_irq_समय stamp to account क्रम the part that fit, so that a next
	 * update will consume the rest. This ensures ->घड़ी_प्रकारask is
	 * monotonic.
	 *
	 * It करोes however cause some slight miss-attribution of अणुsoft,पूर्णirq
	 * समय, a more accurate solution would be to update the irq_समय using
	 * the current rq->घड़ी बारtamp, except that would require using
	 * atomic ops.
	 */
	अगर (irq_delta > delta)
		irq_delta = delta;

	rq->prev_irq_समय += irq_delta;
	delta -= irq_delta;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PARAVIRT_TIME_ACCOUNTING
	अगर (अटल_key_false((&paravirt_steal_rq_enabled))) अणु
		steal = paravirt_steal_घड़ी(cpu_of(rq));
		steal -= rq->prev_steal_समय_rq;

		अगर (unlikely(steal > delta))
			steal = delta;

		rq->prev_steal_समय_rq += steal;
		delta -= steal;
	पूर्ण
#पूर्ण_अगर

	rq->घड़ी_प्रकारask += delta;

#अगर_घोषित CONFIG_HAVE_SCHED_AVG_IRQ
	अगर ((irq_delta + steal) && sched_feat(NONTASK_CAPACITY))
		update_irq_load_avg(rq, irq_delta + steal);
#पूर्ण_अगर
	update_rq_घड़ी_pelt(rq, delta);
पूर्ण

व्योम update_rq_घड़ी(काष्ठा rq *rq)
अणु
	s64 delta;

	lockdep_निश्चित_held(&rq->lock);

	अगर (rq->घड़ी_update_flags & RQCF_ACT_SKIP)
		वापस;

#अगर_घोषित CONFIG_SCHED_DEBUG
	अगर (sched_feat(WARN_DOUBLE_CLOCK))
		SCHED_WARN_ON(rq->घड़ी_update_flags & RQCF_UPDATED);
	rq->घड़ी_update_flags |= RQCF_UPDATED;
#पूर्ण_अगर

	delta = sched_घड़ी_cpu(cpu_of(rq)) - rq->घड़ी;
	अगर (delta < 0)
		वापस;
	rq->घड़ी += delta;
	update_rq_घड़ी_प्रकारask(rq, delta);
पूर्ण

#अगर_घोषित CONFIG_SCHED_HRTICK
/*
 * Use HR-समयrs to deliver accurate preemption poपूर्णांकs.
 */

अटल व्योम hrtick_clear(काष्ठा rq *rq)
अणु
	अगर (hrसमयr_active(&rq->hrtick_समयr))
		hrसमयr_cancel(&rq->hrtick_समयr);
पूर्ण

/*
 * High-resolution समयr tick.
 * Runs from hardirq context with पूर्णांकerrupts disabled.
 */
अटल क्रमागत hrसमयr_restart hrtick(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा rq *rq = container_of(समयr, काष्ठा rq, hrtick_समयr);
	काष्ठा rq_flags rf;

	WARN_ON_ONCE(cpu_of(rq) != smp_processor_id());

	rq_lock(rq, &rf);
	update_rq_घड़ी(rq);
	rq->curr->sched_class->task_tick(rq, rq->curr, 1);
	rq_unlock(rq, &rf);

	वापस HRTIMER_NORESTART;
पूर्ण

#अगर_घोषित CONFIG_SMP

अटल व्योम __hrtick_restart(काष्ठा rq *rq)
अणु
	काष्ठा hrसमयr *समयr = &rq->hrtick_समयr;
	kसमय_प्रकार समय = rq->hrtick_समय;

	hrसमयr_start(समयr, समय, HRTIMER_MODE_ABS_PINNED_HARD);
पूर्ण

/*
 * called from hardirq (IPI) context
 */
अटल व्योम __hrtick_start(व्योम *arg)
अणु
	काष्ठा rq *rq = arg;
	काष्ठा rq_flags rf;

	rq_lock(rq, &rf);
	__hrtick_restart(rq);
	rq_unlock(rq, &rf);
पूर्ण

/*
 * Called to set the hrtick समयr state.
 *
 * called with rq->lock held and irqs disabled
 */
व्योम hrtick_start(काष्ठा rq *rq, u64 delay)
अणु
	काष्ठा hrसमयr *समयr = &rq->hrtick_समयr;
	s64 delta;

	/*
	 * Don't schedule slices लघुer than 10000ns, that just
	 * करोesn't make sense and can cause समयr DoS.
	 */
	delta = max_t(s64, delay, 10000LL);
	rq->hrtick_समय = kसमय_add_ns(समयr->base->get_समय(), delta);

	अगर (rq == this_rq())
		__hrtick_restart(rq);
	अन्यथा
		smp_call_function_single_async(cpu_of(rq), &rq->hrtick_csd);
पूर्ण

#अन्यथा
/*
 * Called to set the hrtick समयr state.
 *
 * called with rq->lock held and irqs disabled
 */
व्योम hrtick_start(काष्ठा rq *rq, u64 delay)
अणु
	/*
	 * Don't schedule slices लघुer than 10000ns, that just
	 * करोesn't make sense. Rely on vrunसमय क्रम fairness.
	 */
	delay = max_t(u64, delay, 10000LL);
	hrसमयr_start(&rq->hrtick_समयr, ns_to_kसमय(delay),
		      HRTIMER_MODE_REL_PINNED_HARD);
पूर्ण

#पूर्ण_अगर /* CONFIG_SMP */

अटल व्योम hrtick_rq_init(काष्ठा rq *rq)
अणु
#अगर_घोषित CONFIG_SMP
	INIT_CSD(&rq->hrtick_csd, __hrtick_start, rq);
#पूर्ण_अगर
	hrसमयr_init(&rq->hrtick_समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL_HARD);
	rq->hrtick_समयr.function = hrtick;
पूर्ण
#अन्यथा	/* CONFIG_SCHED_HRTICK */
अटल अंतरभूत व्योम hrtick_clear(काष्ठा rq *rq)
अणु
पूर्ण

अटल अंतरभूत व्योम hrtick_rq_init(काष्ठा rq *rq)
अणु
पूर्ण
#पूर्ण_अगर	/* CONFIG_SCHED_HRTICK */

/*
 * cmpxchg based fetch_or, macro so it works क्रम dअगरferent पूर्णांकeger types
 */
#घोषणा fetch_or(ptr, mask)						\
	(अणु								\
		typeof(ptr) _ptr = (ptr);				\
		typeof(mask) _mask = (mask);				\
		typeof(*_ptr) _old, _val = *_ptr;			\
									\
		क्रम (;;) अणु						\
			_old = cmpxchg(_ptr, _val, _val | _mask);	\
			अगर (_old == _val)				\
				अवरोध;					\
			_val = _old;					\
		पूर्ण							\
	_old;								\
पूर्ण)

#अगर defined(CONFIG_SMP) && defined(TIF_POLLING_NRFLAG)
/*
 * Atomically set TIF_NEED_RESCHED and test क्रम TIF_POLLING_NRFLAG,
 * this aव्योमs any races wrt polling state changes and thereby aव्योमs
 * spurious IPIs.
 */
अटल bool set_nr_and_not_polling(काष्ठा task_काष्ठा *p)
अणु
	काष्ठा thपढ़ो_info *ti = task_thपढ़ो_info(p);
	वापस !(fetch_or(&ti->flags, _TIF_NEED_RESCHED) & _TIF_POLLING_NRFLAG);
पूर्ण

/*
 * Atomically set TIF_NEED_RESCHED अगर TIF_POLLING_NRFLAG is set.
 *
 * If this वापसs true, then the idle task promises to call
 * sched_ttwu_pending() and reschedule soon.
 */
अटल bool set_nr_अगर_polling(काष्ठा task_काष्ठा *p)
अणु
	काष्ठा thपढ़ो_info *ti = task_thपढ़ो_info(p);
	typeof(ti->flags) old, val = READ_ONCE(ti->flags);

	क्रम (;;) अणु
		अगर (!(val & _TIF_POLLING_NRFLAG))
			वापस false;
		अगर (val & _TIF_NEED_RESCHED)
			वापस true;
		old = cmpxchg(&ti->flags, val, val | _TIF_NEED_RESCHED);
		अगर (old == val)
			अवरोध;
		val = old;
	पूर्ण
	वापस true;
पूर्ण

#अन्यथा
अटल bool set_nr_and_not_polling(काष्ठा task_काष्ठा *p)
अणु
	set_tsk_need_resched(p);
	वापस true;
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल bool set_nr_अगर_polling(काष्ठा task_काष्ठा *p)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

अटल bool __wake_q_add(काष्ठा wake_q_head *head, काष्ठा task_काष्ठा *task)
अणु
	काष्ठा wake_q_node *node = &task->wake_q;

	/*
	 * Atomically grab the task, अगर ->wake_q is !nil alपढ़ोy it means
	 * it's alपढ़ोy queued (either by us or someone अन्यथा) and will get the
	 * wakeup due to that.
	 *
	 * In order to ensure that a pending wakeup will observe our pending
	 * state, even in the failed हाल, an explicit smp_mb() must be used.
	 */
	smp_mb__beक्रमe_atomic();
	अगर (unlikely(cmpxchg_relaxed(&node->next, शून्य, WAKE_Q_TAIL)))
		वापस false;

	/*
	 * The head is context local, there can be no concurrency.
	 */
	*head->lastp = node;
	head->lastp = &node->next;
	वापस true;
पूर्ण

/**
 * wake_q_add() - queue a wakeup क्रम 'later' waking.
 * @head: the wake_q_head to add @task to
 * @task: the task to queue क्रम 'later' wakeup
 *
 * Queue a task क्रम later wakeup, most likely by the wake_up_q() call in the
 * same context, _HOWEVER_ this is not guaranteed, the wakeup can come
 * instantly.
 *
 * This function must be used as-अगर it were wake_up_process(); IOW the task
 * must be पढ़ोy to be woken at this location.
 */
व्योम wake_q_add(काष्ठा wake_q_head *head, काष्ठा task_काष्ठा *task)
अणु
	अगर (__wake_q_add(head, task))
		get_task_काष्ठा(task);
पूर्ण

/**
 * wake_q_add_safe() - safely queue a wakeup क्रम 'later' waking.
 * @head: the wake_q_head to add @task to
 * @task: the task to queue क्रम 'later' wakeup
 *
 * Queue a task क्रम later wakeup, most likely by the wake_up_q() call in the
 * same context, _HOWEVER_ this is not guaranteed, the wakeup can come
 * instantly.
 *
 * This function must be used as-अगर it were wake_up_process(); IOW the task
 * must be पढ़ोy to be woken at this location.
 *
 * This function is essentially a task-safe equivalent to wake_q_add(). Callers
 * that alपढ़ोy hold reference to @task can call the 'safe' version and trust
 * wake_q to करो the right thing depending whether or not the @task is alपढ़ोy
 * queued क्रम wakeup.
 */
व्योम wake_q_add_safe(काष्ठा wake_q_head *head, काष्ठा task_काष्ठा *task)
अणु
	अगर (!__wake_q_add(head, task))
		put_task_काष्ठा(task);
पूर्ण

व्योम wake_up_q(काष्ठा wake_q_head *head)
अणु
	काष्ठा wake_q_node *node = head->first;

	जबतक (node != WAKE_Q_TAIL) अणु
		काष्ठा task_काष्ठा *task;

		task = container_of(node, काष्ठा task_काष्ठा, wake_q);
		BUG_ON(!task);
		/* Task can safely be re-inserted now: */
		node = node->next;
		task->wake_q.next = शून्य;

		/*
		 * wake_up_process() executes a full barrier, which pairs with
		 * the queueing in wake_q_add() so as not to miss wakeups.
		 */
		wake_up_process(task);
		put_task_काष्ठा(task);
	पूर्ण
पूर्ण

/*
 * resched_curr - mark rq's current task 'to be rescheduled now'.
 *
 * On UP this means the setting of the need_resched flag, on SMP it
 * might also involve a cross-CPU call to trigger the scheduler on
 * the target CPU.
 */
व्योम resched_curr(काष्ठा rq *rq)
अणु
	काष्ठा task_काष्ठा *curr = rq->curr;
	पूर्णांक cpu;

	lockdep_निश्चित_held(&rq->lock);

	अगर (test_tsk_need_resched(curr))
		वापस;

	cpu = cpu_of(rq);

	अगर (cpu == smp_processor_id()) अणु
		set_tsk_need_resched(curr);
		set_preempt_need_resched();
		वापस;
	पूर्ण

	अगर (set_nr_and_not_polling(curr))
		smp_send_reschedule(cpu);
	अन्यथा
		trace_sched_wake_idle_without_ipi(cpu);
पूर्ण

व्योम resched_cpu(पूर्णांक cpu)
अणु
	काष्ठा rq *rq = cpu_rq(cpu);
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&rq->lock, flags);
	अगर (cpu_online(cpu) || cpu == smp_processor_id())
		resched_curr(rq);
	raw_spin_unlock_irqrestore(&rq->lock, flags);
पूर्ण

#अगर_घोषित CONFIG_SMP
#अगर_घोषित CONFIG_NO_HZ_COMMON
/*
 * In the semi idle हाल, use the nearest busy CPU क्रम migrating समयrs
 * from an idle CPU.  This is good क्रम घातer-savings.
 *
 * We करोn't करो similar optimization क्रम completely idle प्रणाली, as
 * selecting an idle CPU will add more delays to the समयrs than पूर्णांकended
 * (as that CPU's समयr base may not be uptodate wrt jअगरfies etc).
 */
पूर्णांक get_nohz_समयr_target(व्योम)
अणु
	पूर्णांक i, cpu = smp_processor_id(), शेष_cpu = -1;
	काष्ठा sched_करोमुख्य *sd;

	अगर (housekeeping_cpu(cpu, HK_FLAG_TIMER)) अणु
		अगर (!idle_cpu(cpu))
			वापस cpu;
		शेष_cpu = cpu;
	पूर्ण

	rcu_पढ़ो_lock();
	क्रम_each_करोमुख्य(cpu, sd) अणु
		क्रम_each_cpu_and(i, sched_करोमुख्य_span(sd),
			housekeeping_cpumask(HK_FLAG_TIMER)) अणु
			अगर (cpu == i)
				जारी;

			अगर (!idle_cpu(i)) अणु
				cpu = i;
				जाओ unlock;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (शेष_cpu == -1)
		शेष_cpu = housekeeping_any_cpu(HK_FLAG_TIMER);
	cpu = शेष_cpu;
unlock:
	rcu_पढ़ो_unlock();
	वापस cpu;
पूर्ण

/*
 * When add_समयr_on() enqueues a समयr पूर्णांकo the समयr wheel of an
 * idle CPU then this समयr might expire beक्रमe the next समयr event
 * which is scheduled to wake up that CPU. In हाल of a completely
 * idle प्रणाली the next event might even be infinite समय पूर्णांकo the
 * future. wake_up_idle_cpu() ensures that the CPU is woken up and
 * leaves the inner idle loop so the newly added समयr is taken पूर्णांकo
 * account when the CPU goes back to idle and evaluates the समयr
 * wheel क्रम the next समयr event.
 */
अटल व्योम wake_up_idle_cpu(पूर्णांक cpu)
अणु
	काष्ठा rq *rq = cpu_rq(cpu);

	अगर (cpu == smp_processor_id())
		वापस;

	अगर (set_nr_and_not_polling(rq->idle))
		smp_send_reschedule(cpu);
	अन्यथा
		trace_sched_wake_idle_without_ipi(cpu);
पूर्ण

अटल bool wake_up_full_nohz_cpu(पूर्णांक cpu)
अणु
	/*
	 * We just need the target to call irq_निकास() and re-evaluate
	 * the next tick. The nohz full kick at least implies that.
	 * If needed we can still optimize that later with an
	 * empty IRQ.
	 */
	अगर (cpu_is_offline(cpu))
		वापस true;  /* Don't try to wake offline CPUs. */
	अगर (tick_nohz_full_cpu(cpu)) अणु
		अगर (cpu != smp_processor_id() ||
		    tick_nohz_tick_stopped())
			tick_nohz_full_kick_cpu(cpu);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * Wake up the specअगरied CPU.  If the CPU is going offline, it is the
 * caller's responsibility to deal with the lost wakeup, क्रम example,
 * by hooking पूर्णांकo the CPU_DEAD notअगरier like समयrs and hrसमयrs करो.
 */
व्योम wake_up_nohz_cpu(पूर्णांक cpu)
अणु
	अगर (!wake_up_full_nohz_cpu(cpu))
		wake_up_idle_cpu(cpu);
पूर्ण

अटल व्योम nohz_csd_func(व्योम *info)
अणु
	काष्ठा rq *rq = info;
	पूर्णांक cpu = cpu_of(rq);
	अचिन्हित पूर्णांक flags;

	/*
	 * Release the rq::nohz_csd.
	 */
	flags = atomic_fetch_andnot(NOHZ_KICK_MASK | NOHZ_NEWILB_KICK, nohz_flags(cpu));
	WARN_ON(!(flags & NOHZ_KICK_MASK));

	rq->idle_balance = idle_cpu(cpu);
	अगर (rq->idle_balance && !need_resched()) अणु
		rq->nohz_idle_balance = flags;
		उठाओ_softirq_irqoff(SCHED_SOFTIRQ);
	पूर्ण
पूर्ण

#पूर्ण_अगर /* CONFIG_NO_HZ_COMMON */

#अगर_घोषित CONFIG_NO_HZ_FULL
bool sched_can_stop_tick(काष्ठा rq *rq)
अणु
	पूर्णांक fअगरo_nr_running;

	/* Deadline tasks, even अगर single, need the tick */
	अगर (rq->dl.dl_nr_running)
		वापस false;

	/*
	 * If there are more than one RR tasks, we need the tick to affect the
	 * actual RR behaviour.
	 */
	अगर (rq->rt.rr_nr_running) अणु
		अगर (rq->rt.rr_nr_running == 1)
			वापस true;
		अन्यथा
			वापस false;
	पूर्ण

	/*
	 * If there's no RR tasks, but FIFO tasks, we can skip the tick, no
	 * क्रमced preemption between FIFO tasks.
	 */
	fअगरo_nr_running = rq->rt.rt_nr_running - rq->rt.rr_nr_running;
	अगर (fअगरo_nr_running)
		वापस true;

	/*
	 * If there are no DL,RR/FIFO tasks, there must only be CFS tasks left;
	 * अगर there's more than one we need the tick क्रम involuntary
	 * preemption.
	 */
	अगर (rq->nr_running > 1)
		वापस false;

	वापस true;
पूर्ण
#पूर्ण_अगर /* CONFIG_NO_HZ_FULL */
#पूर्ण_अगर /* CONFIG_SMP */

#अगर defined(CONFIG_RT_GROUP_SCHED) || (defined(CONFIG_FAIR_GROUP_SCHED) && \
			(defined(CONFIG_SMP) || defined(CONFIG_CFS_BANDWIDTH)))
/*
 * Iterate task_group tree rooted at *from, calling @करोwn when first entering a
 * node and @up when leaving it क्रम the final समय.
 *
 * Caller must hold rcu_lock or sufficient equivalent.
 */
पूर्णांक walk_tg_tree_from(काष्ठा task_group *from,
			     tg_visitor करोwn, tg_visitor up, व्योम *data)
अणु
	काष्ठा task_group *parent, *child;
	पूर्णांक ret;

	parent = from;

करोwn:
	ret = (*करोwn)(parent, data);
	अगर (ret)
		जाओ out;
	list_क्रम_each_entry_rcu(child, &parent->children, siblings) अणु
		parent = child;
		जाओ करोwn;

up:
		जारी;
	पूर्ण
	ret = (*up)(parent, data);
	अगर (ret || parent == from)
		जाओ out;

	child = parent;
	parent = parent->parent;
	अगर (parent)
		जाओ up;
out:
	वापस ret;
पूर्ण

पूर्णांक tg_nop(काष्ठा task_group *tg, व्योम *data)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम set_load_weight(काष्ठा task_काष्ठा *p, bool update_load)
अणु
	पूर्णांक prio = p->अटल_prio - MAX_RT_PRIO;
	काष्ठा load_weight *load = &p->se.load;

	/*
	 * SCHED_IDLE tasks get minimal weight:
	 */
	अगर (task_has_idle_policy(p)) अणु
		load->weight = scale_load(WEIGHT_IDLEPRIO);
		load->inv_weight = WMULT_IDLEPRIO;
		वापस;
	पूर्ण

	/*
	 * SCHED_OTHER tasks have to update their load when changing their
	 * weight
	 */
	अगर (update_load && p->sched_class == &fair_sched_class) अणु
		reweight_task(p, prio);
	पूर्ण अन्यथा अणु
		load->weight = scale_load(sched_prio_to_weight[prio]);
		load->inv_weight = sched_prio_to_wmult[prio];
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_UCLAMP_TASK
/*
 * Serializes updates of utilization clamp values
 *
 * The (slow-path) user-space triggers utilization clamp value updates which
 * can require updates on (fast-path) scheduler's data काष्ठाures used to
 * support enqueue/dequeue operations.
 * While the per-CPU rq lock protects fast-path update operations, user-space
 * requests are serialized using a mutex to reduce the risk of conflicting
 * updates or API abuses.
 */
अटल DEFINE_MUTEX(uclamp_mutex);

/* Max allowed minimum utilization */
अचिन्हित पूर्णांक sysctl_sched_uclamp_util_min = SCHED_CAPACITY_SCALE;

/* Max allowed maximum utilization */
अचिन्हित पूर्णांक sysctl_sched_uclamp_util_max = SCHED_CAPACITY_SCALE;

/*
 * By शेष RT tasks run at the maximum perक्रमmance poपूर्णांक/capacity of the
 * प्रणाली. Uclamp enक्रमces this by always setting UCLAMP_MIN of RT tasks to
 * SCHED_CAPACITY_SCALE.
 *
 * This knob allows admins to change the शेष behavior when uclamp is being
 * used. In battery घातered devices, particularly, running at the maximum
 * capacity and frequency will increase energy consumption and लघुen the
 * battery lअगरe.
 *
 * This knob only affects RT tasks that their uclamp_se->user_defined == false.
 *
 * This knob will not override the प्रणाली शेष sched_util_clamp_min defined
 * above.
 */
अचिन्हित पूर्णांक sysctl_sched_uclamp_util_min_rt_शेष = SCHED_CAPACITY_SCALE;

/* All clamps are required to be less or equal than these values */
अटल काष्ठा uclamp_se uclamp_शेष[UCLAMP_CNT];

/*
 * This अटल key is used to reduce the uclamp overhead in the fast path. It
 * primarily disables the call to uclamp_rq_अणुinc, decपूर्ण() in
 * enqueue/dequeue_task().
 *
 * This allows users to जारी to enable uclamp in their kernel config with
 * minimum uclamp overhead in the fast path.
 *
 * As soon as userspace modअगरies any of the uclamp knobs, the अटल key is
 * enabled, since we have an actual users that make use of uclamp
 * functionality.
 *
 * The knobs that would enable this अटल key are:
 *
 *   * A task modअगरying its uclamp value with sched_setattr().
 *   * An admin modअगरying the sysctl_sched_uclamp_अणुmin, maxपूर्ण via procfs.
 *   * An admin modअगरying the cgroup cpu.uclamp.अणुmin, maxपूर्ण
 */
DEFINE_STATIC_KEY_FALSE(sched_uclamp_used);

/* Integer rounded range क्रम each bucket */
#घोषणा UCLAMP_BUCKET_DELTA DIV_ROUND_CLOSEST(SCHED_CAPACITY_SCALE, UCLAMP_BUCKETS)

#घोषणा क्रम_each_clamp_id(clamp_id) \
	क्रम ((clamp_id) = 0; (clamp_id) < UCLAMP_CNT; (clamp_id)++)

अटल अंतरभूत अचिन्हित पूर्णांक uclamp_bucket_id(अचिन्हित पूर्णांक clamp_value)
अणु
	वापस min_t(अचिन्हित पूर्णांक, clamp_value / UCLAMP_BUCKET_DELTA, UCLAMP_BUCKETS - 1);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक uclamp_none(क्रमागत uclamp_id clamp_id)
अणु
	अगर (clamp_id == UCLAMP_MIN)
		वापस 0;
	वापस SCHED_CAPACITY_SCALE;
पूर्ण

अटल अंतरभूत व्योम uclamp_se_set(काष्ठा uclamp_se *uc_se,
				 अचिन्हित पूर्णांक value, bool user_defined)
अणु
	uc_se->value = value;
	uc_se->bucket_id = uclamp_bucket_id(value);
	uc_se->user_defined = user_defined;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
uclamp_idle_value(काष्ठा rq *rq, क्रमागत uclamp_id clamp_id,
		  अचिन्हित पूर्णांक clamp_value)
अणु
	/*
	 * Aव्योम blocked utilization pushing up the frequency when we go
	 * idle (which drops the max-clamp) by retaining the last known
	 * max-clamp.
	 */
	अगर (clamp_id == UCLAMP_MAX) अणु
		rq->uclamp_flags |= UCLAMP_FLAG_IDLE;
		वापस clamp_value;
	पूर्ण

	वापस uclamp_none(UCLAMP_MIN);
पूर्ण

अटल अंतरभूत व्योम uclamp_idle_reset(काष्ठा rq *rq, क्रमागत uclamp_id clamp_id,
				     अचिन्हित पूर्णांक clamp_value)
अणु
	/* Reset max-clamp retention only on idle निकास */
	अगर (!(rq->uclamp_flags & UCLAMP_FLAG_IDLE))
		वापस;

	WRITE_ONCE(rq->uclamp[clamp_id].value, clamp_value);
पूर्ण

अटल अंतरभूत
अचिन्हित पूर्णांक uclamp_rq_max_value(काष्ठा rq *rq, क्रमागत uclamp_id clamp_id,
				   अचिन्हित पूर्णांक clamp_value)
अणु
	काष्ठा uclamp_bucket *bucket = rq->uclamp[clamp_id].bucket;
	पूर्णांक bucket_id = UCLAMP_BUCKETS - 1;

	/*
	 * Since both min and max clamps are max aggregated, find the
	 * top most bucket with tasks in.
	 */
	क्रम ( ; bucket_id >= 0; bucket_id--) अणु
		अगर (!bucket[bucket_id].tasks)
			जारी;
		वापस bucket[bucket_id].value;
	पूर्ण

	/* No tasks -- शेष clamp values */
	वापस uclamp_idle_value(rq, clamp_id, clamp_value);
पूर्ण

अटल व्योम __uclamp_update_util_min_rt_शेष(काष्ठा task_काष्ठा *p)
अणु
	अचिन्हित पूर्णांक शेष_util_min;
	काष्ठा uclamp_se *uc_se;

	lockdep_निश्चित_held(&p->pi_lock);

	uc_se = &p->uclamp_req[UCLAMP_MIN];

	/* Only sync अगर user didn't override the शेष */
	अगर (uc_se->user_defined)
		वापस;

	शेष_util_min = sysctl_sched_uclamp_util_min_rt_शेष;
	uclamp_se_set(uc_se, शेष_util_min, false);
पूर्ण

अटल व्योम uclamp_update_util_min_rt_शेष(काष्ठा task_काष्ठा *p)
अणु
	काष्ठा rq_flags rf;
	काष्ठा rq *rq;

	अगर (!rt_task(p))
		वापस;

	/* Protect updates to p->uclamp_* */
	rq = task_rq_lock(p, &rf);
	__uclamp_update_util_min_rt_शेष(p);
	task_rq_unlock(rq, p, &rf);
पूर्ण

अटल व्योम uclamp_sync_util_min_rt_शेष(व्योम)
अणु
	काष्ठा task_काष्ठा *g, *p;

	/*
	 * copy_process()			sysctl_uclamp
	 *					  uclamp_min_rt = X;
	 *   ग_लिखो_lock(&tasklist_lock)		  पढ़ो_lock(&tasklist_lock)
	 *   // link thपढ़ो			  smp_mb__after_spinlock()
	 *   ग_लिखो_unlock(&tasklist_lock)	  पढ़ो_unlock(&tasklist_lock);
	 *   sched_post_विभाजन()			  क्रम_each_process_thपढ़ो()
	 *     __uclamp_sync_rt()		    __uclamp_sync_rt()
	 *
	 * Ensures that either sched_post_विभाजन() will observe the new
	 * uclamp_min_rt or क्रम_each_process_thपढ़ो() will observe the new
	 * task.
	 */
	पढ़ो_lock(&tasklist_lock);
	smp_mb__after_spinlock();
	पढ़ो_unlock(&tasklist_lock);

	rcu_पढ़ो_lock();
	क्रम_each_process_thपढ़ो(g, p)
		uclamp_update_util_min_rt_शेष(p);
	rcu_पढ़ो_unlock();
पूर्ण

अटल अंतरभूत काष्ठा uclamp_se
uclamp_tg_restrict(काष्ठा task_काष्ठा *p, क्रमागत uclamp_id clamp_id)
अणु
	काष्ठा uclamp_se uc_req = p->uclamp_req[clamp_id];
#अगर_घोषित CONFIG_UCLAMP_TASK_GROUP
	काष्ठा uclamp_se uc_max;

	/*
	 * Tasks in स्वतःgroups or root task group will be
	 * restricted by प्रणाली शेषs.
	 */
	अगर (task_group_is_स्वतःgroup(task_group(p)))
		वापस uc_req;
	अगर (task_group(p) == &root_task_group)
		वापस uc_req;

	uc_max = task_group(p)->uclamp[clamp_id];
	अगर (uc_req.value > uc_max.value || !uc_req.user_defined)
		वापस uc_max;
#पूर्ण_अगर

	वापस uc_req;
पूर्ण

/*
 * The effective clamp bucket index of a task depends on, by increasing
 * priority:
 * - the task specअगरic clamp value, when explicitly requested from userspace
 * - the task group effective clamp value, क्रम tasks not either in the root
 *   group or in an स्वतःgroup
 * - the प्रणाली शेष clamp value, defined by the sysadmin
 */
अटल अंतरभूत काष्ठा uclamp_se
uclamp_eff_get(काष्ठा task_काष्ठा *p, क्रमागत uclamp_id clamp_id)
अणु
	काष्ठा uclamp_se uc_req = uclamp_tg_restrict(p, clamp_id);
	काष्ठा uclamp_se uc_max = uclamp_शेष[clamp_id];

	/* System शेष restrictions always apply */
	अगर (unlikely(uc_req.value > uc_max.value))
		वापस uc_max;

	वापस uc_req;
पूर्ण

अचिन्हित दीर्घ uclamp_eff_value(काष्ठा task_काष्ठा *p, क्रमागत uclamp_id clamp_id)
अणु
	काष्ठा uclamp_se uc_eff;

	/* Task currently refcounted: use back-annotated (effective) value */
	अगर (p->uclamp[clamp_id].active)
		वापस (अचिन्हित दीर्घ)p->uclamp[clamp_id].value;

	uc_eff = uclamp_eff_get(p, clamp_id);

	वापस (अचिन्हित दीर्घ)uc_eff.value;
पूर्ण

/*
 * When a task is enqueued on a rq, the clamp bucket currently defined by the
 * task's uclamp::bucket_id is refcounted on that rq. This also immediately
 * updates the rq's clamp value अगर required.
 *
 * Tasks can have a task-specअगरic value requested from user-space, track
 * within each bucket the maximum value क्रम tasks refcounted in it.
 * This "local max aggregation" allows to track the exact "requested" value
 * क्रम each bucket when all its RUNNABLE tasks require the same clamp.
 */
अटल अंतरभूत व्योम uclamp_rq_inc_id(काष्ठा rq *rq, काष्ठा task_काष्ठा *p,
				    क्रमागत uclamp_id clamp_id)
अणु
	काष्ठा uclamp_rq *uc_rq = &rq->uclamp[clamp_id];
	काष्ठा uclamp_se *uc_se = &p->uclamp[clamp_id];
	काष्ठा uclamp_bucket *bucket;

	lockdep_निश्चित_held(&rq->lock);

	/* Update task effective clamp */
	p->uclamp[clamp_id] = uclamp_eff_get(p, clamp_id);

	bucket = &uc_rq->bucket[uc_se->bucket_id];
	bucket->tasks++;
	uc_se->active = true;

	uclamp_idle_reset(rq, clamp_id, uc_se->value);

	/*
	 * Local max aggregation: rq buckets always track the max
	 * "requested" clamp value of its RUNNABLE tasks.
	 */
	अगर (bucket->tasks == 1 || uc_se->value > bucket->value)
		bucket->value = uc_se->value;

	अगर (uc_se->value > READ_ONCE(uc_rq->value))
		WRITE_ONCE(uc_rq->value, uc_se->value);
पूर्ण

/*
 * When a task is dequeued from a rq, the clamp bucket refcounted by the task
 * is released. If this is the last task reference counting the rq's max
 * active clamp value, then the rq's clamp value is updated.
 *
 * Both refcounted tasks and rq's cached clamp values are expected to be
 * always valid. If it's detected they are not, as defensive programming,
 * enक्रमce the expected state and warn.
 */
अटल अंतरभूत व्योम uclamp_rq_dec_id(काष्ठा rq *rq, काष्ठा task_काष्ठा *p,
				    क्रमागत uclamp_id clamp_id)
अणु
	काष्ठा uclamp_rq *uc_rq = &rq->uclamp[clamp_id];
	काष्ठा uclamp_se *uc_se = &p->uclamp[clamp_id];
	काष्ठा uclamp_bucket *bucket;
	अचिन्हित पूर्णांक bkt_clamp;
	अचिन्हित पूर्णांक rq_clamp;

	lockdep_निश्चित_held(&rq->lock);

	/*
	 * If sched_uclamp_used was enabled after task @p was enqueued,
	 * we could end up with unbalanced call to uclamp_rq_dec_id().
	 *
	 * In this हाल the uc_se->active flag should be false since no uclamp
	 * accounting was perक्रमmed at enqueue समय and we can just वापस
	 * here.
	 *
	 * Need to be careful of the following enqueue/dequeue ordering
	 * problem too
	 *
	 *	enqueue(taskA)
	 *	// sched_uclamp_used माला_लो enabled
	 *	enqueue(taskB)
	 *	dequeue(taskA)
	 *	// Must not decrement bucket->tasks here
	 *	dequeue(taskB)
	 *
	 * where we could end up with stale data in uc_se and
	 * bucket[uc_se->bucket_id].
	 *
	 * The following check here eliminates the possibility of such race.
	 */
	अगर (unlikely(!uc_se->active))
		वापस;

	bucket = &uc_rq->bucket[uc_se->bucket_id];

	SCHED_WARN_ON(!bucket->tasks);
	अगर (likely(bucket->tasks))
		bucket->tasks--;

	uc_se->active = false;

	/*
	 * Keep "local max aggregation" simple and accept to (possibly)
	 * overboost some RUNNABLE tasks in the same bucket.
	 * The rq clamp bucket value is reset to its base value whenever
	 * there are no more RUNNABLE tasks refcounting it.
	 */
	अगर (likely(bucket->tasks))
		वापस;

	rq_clamp = READ_ONCE(uc_rq->value);
	/*
	 * Defensive programming: this should never happen. If it happens,
	 * e.g. due to future modअगरication, warn and fixup the expected value.
	 */
	SCHED_WARN_ON(bucket->value > rq_clamp);
	अगर (bucket->value >= rq_clamp) अणु
		bkt_clamp = uclamp_rq_max_value(rq, clamp_id, uc_se->value);
		WRITE_ONCE(uc_rq->value, bkt_clamp);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम uclamp_rq_inc(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
	क्रमागत uclamp_id clamp_id;

	/*
	 * Aव्योम any overhead until uclamp is actually used by the userspace.
	 *
	 * The condition is स्थिरructed such that a NOP is generated when
	 * sched_uclamp_used is disabled.
	 */
	अगर (!अटल_branch_unlikely(&sched_uclamp_used))
		वापस;

	अगर (unlikely(!p->sched_class->uclamp_enabled))
		वापस;

	क्रम_each_clamp_id(clamp_id)
		uclamp_rq_inc_id(rq, p, clamp_id);

	/* Reset clamp idle holding when there is one RUNNABLE task */
	अगर (rq->uclamp_flags & UCLAMP_FLAG_IDLE)
		rq->uclamp_flags &= ~UCLAMP_FLAG_IDLE;
पूर्ण

अटल अंतरभूत व्योम uclamp_rq_dec(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
	क्रमागत uclamp_id clamp_id;

	/*
	 * Aव्योम any overhead until uclamp is actually used by the userspace.
	 *
	 * The condition is स्थिरructed such that a NOP is generated when
	 * sched_uclamp_used is disabled.
	 */
	अगर (!अटल_branch_unlikely(&sched_uclamp_used))
		वापस;

	अगर (unlikely(!p->sched_class->uclamp_enabled))
		वापस;

	क्रम_each_clamp_id(clamp_id)
		uclamp_rq_dec_id(rq, p, clamp_id);
पूर्ण

अटल अंतरभूत व्योम
uclamp_update_active(काष्ठा task_काष्ठा *p, क्रमागत uclamp_id clamp_id)
अणु
	काष्ठा rq_flags rf;
	काष्ठा rq *rq;

	/*
	 * Lock the task and the rq where the task is (or was) queued.
	 *
	 * We might lock the (previous) rq of a !RUNNABLE task, but that's the
	 * price to pay to safely serialize util_अणुmin,maxपूर्ण updates with
	 * enqueues, dequeues and migration operations.
	 * This is the same locking schema used by __set_cpus_allowed_ptr().
	 */
	rq = task_rq_lock(p, &rf);

	/*
	 * Setting the clamp bucket is serialized by task_rq_lock().
	 * If the task is not yet RUNNABLE and its task_काष्ठा is not
	 * affecting a valid clamp bucket, the next समय it's enqueued,
	 * it will alपढ़ोy see the updated clamp bucket value.
	 */
	अगर (p->uclamp[clamp_id].active) अणु
		uclamp_rq_dec_id(rq, p, clamp_id);
		uclamp_rq_inc_id(rq, p, clamp_id);
	पूर्ण

	task_rq_unlock(rq, p, &rf);
पूर्ण

#अगर_घोषित CONFIG_UCLAMP_TASK_GROUP
अटल अंतरभूत व्योम
uclamp_update_active_tasks(काष्ठा cgroup_subsys_state *css,
			   अचिन्हित पूर्णांक clamps)
अणु
	क्रमागत uclamp_id clamp_id;
	काष्ठा css_task_iter it;
	काष्ठा task_काष्ठा *p;

	css_task_iter_start(css, 0, &it);
	जबतक ((p = css_task_iter_next(&it))) अणु
		क्रम_each_clamp_id(clamp_id) अणु
			अगर ((0x1 << clamp_id) & clamps)
				uclamp_update_active(p, clamp_id);
		पूर्ण
	पूर्ण
	css_task_iter_end(&it);
पूर्ण

अटल व्योम cpu_util_update_eff(काष्ठा cgroup_subsys_state *css);
अटल व्योम uclamp_update_root_tg(व्योम)
अणु
	काष्ठा task_group *tg = &root_task_group;

	uclamp_se_set(&tg->uclamp_req[UCLAMP_MIN],
		      sysctl_sched_uclamp_util_min, false);
	uclamp_se_set(&tg->uclamp_req[UCLAMP_MAX],
		      sysctl_sched_uclamp_util_max, false);

	rcu_पढ़ो_lock();
	cpu_util_update_eff(&root_task_group.css);
	rcu_पढ़ो_unlock();
पूर्ण
#अन्यथा
अटल व्योम uclamp_update_root_tg(व्योम) अणु पूर्ण
#पूर्ण_अगर

पूर्णांक sysctl_sched_uclamp_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
				व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	bool update_root_tg = false;
	पूर्णांक old_min, old_max, old_min_rt;
	पूर्णांक result;

	mutex_lock(&uclamp_mutex);
	old_min = sysctl_sched_uclamp_util_min;
	old_max = sysctl_sched_uclamp_util_max;
	old_min_rt = sysctl_sched_uclamp_util_min_rt_शेष;

	result = proc_करोपूर्णांकvec(table, ग_लिखो, buffer, lenp, ppos);
	अगर (result)
		जाओ unकरो;
	अगर (!ग_लिखो)
		जाओ करोne;

	अगर (sysctl_sched_uclamp_util_min > sysctl_sched_uclamp_util_max ||
	    sysctl_sched_uclamp_util_max > SCHED_CAPACITY_SCALE	||
	    sysctl_sched_uclamp_util_min_rt_शेष > SCHED_CAPACITY_SCALE) अणु

		result = -EINVAL;
		जाओ unकरो;
	पूर्ण

	अगर (old_min != sysctl_sched_uclamp_util_min) अणु
		uclamp_se_set(&uclamp_शेष[UCLAMP_MIN],
			      sysctl_sched_uclamp_util_min, false);
		update_root_tg = true;
	पूर्ण
	अगर (old_max != sysctl_sched_uclamp_util_max) अणु
		uclamp_se_set(&uclamp_शेष[UCLAMP_MAX],
			      sysctl_sched_uclamp_util_max, false);
		update_root_tg = true;
	पूर्ण

	अगर (update_root_tg) अणु
		अटल_branch_enable(&sched_uclamp_used);
		uclamp_update_root_tg();
	पूर्ण

	अगर (old_min_rt != sysctl_sched_uclamp_util_min_rt_शेष) अणु
		अटल_branch_enable(&sched_uclamp_used);
		uclamp_sync_util_min_rt_शेष();
	पूर्ण

	/*
	 * We update all RUNNABLE tasks only when task groups are in use.
	 * Otherwise, keep it simple and करो just a lazy update at each next
	 * task enqueue समय.
	 */

	जाओ करोne;

unकरो:
	sysctl_sched_uclamp_util_min = old_min;
	sysctl_sched_uclamp_util_max = old_max;
	sysctl_sched_uclamp_util_min_rt_शेष = old_min_rt;
करोne:
	mutex_unlock(&uclamp_mutex);

	वापस result;
पूर्ण

अटल पूर्णांक uclamp_validate(काष्ठा task_काष्ठा *p,
			   स्थिर काष्ठा sched_attr *attr)
अणु
	पूर्णांक util_min = p->uclamp_req[UCLAMP_MIN].value;
	पूर्णांक util_max = p->uclamp_req[UCLAMP_MAX].value;

	अगर (attr->sched_flags & SCHED_FLAG_UTIL_CLAMP_MIN) अणु
		util_min = attr->sched_util_min;

		अगर (util_min + 1 > SCHED_CAPACITY_SCALE + 1)
			वापस -EINVAL;
	पूर्ण

	अगर (attr->sched_flags & SCHED_FLAG_UTIL_CLAMP_MAX) अणु
		util_max = attr->sched_util_max;

		अगर (util_max + 1 > SCHED_CAPACITY_SCALE + 1)
			वापस -EINVAL;
	पूर्ण

	अगर (util_min != -1 && util_max != -1 && util_min > util_max)
		वापस -EINVAL;

	/*
	 * We have valid uclamp attributes; make sure uclamp is enabled.
	 *
	 * We need to करो that here, because enabling अटल branches is a
	 * blocking operation which obviously cannot be करोne जबतक holding
	 * scheduler locks.
	 */
	अटल_branch_enable(&sched_uclamp_used);

	वापस 0;
पूर्ण

अटल bool uclamp_reset(स्थिर काष्ठा sched_attr *attr,
			 क्रमागत uclamp_id clamp_id,
			 काष्ठा uclamp_se *uc_se)
अणु
	/* Reset on sched class change क्रम a non user-defined clamp value. */
	अगर (likely(!(attr->sched_flags & SCHED_FLAG_UTIL_CLAMP)) &&
	    !uc_se->user_defined)
		वापस true;

	/* Reset on sched_util_अणुmin,maxपूर्ण == -1. */
	अगर (clamp_id == UCLAMP_MIN &&
	    attr->sched_flags & SCHED_FLAG_UTIL_CLAMP_MIN &&
	    attr->sched_util_min == -1) अणु
		वापस true;
	पूर्ण

	अगर (clamp_id == UCLAMP_MAX &&
	    attr->sched_flags & SCHED_FLAG_UTIL_CLAMP_MAX &&
	    attr->sched_util_max == -1) अणु
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम __setscheduler_uclamp(काष्ठा task_काष्ठा *p,
				  स्थिर काष्ठा sched_attr *attr)
अणु
	क्रमागत uclamp_id clamp_id;

	क्रम_each_clamp_id(clamp_id) अणु
		काष्ठा uclamp_se *uc_se = &p->uclamp_req[clamp_id];
		अचिन्हित पूर्णांक value;

		अगर (!uclamp_reset(attr, clamp_id, uc_se))
			जारी;

		/*
		 * RT by शेष have a 100% boost value that could be modअगरied
		 * at runसमय.
		 */
		अगर (unlikely(rt_task(p) && clamp_id == UCLAMP_MIN))
			value = sysctl_sched_uclamp_util_min_rt_शेष;
		अन्यथा
			value = uclamp_none(clamp_id);

		uclamp_se_set(uc_se, value, false);

	पूर्ण

	अगर (likely(!(attr->sched_flags & SCHED_FLAG_UTIL_CLAMP)))
		वापस;

	अगर (attr->sched_flags & SCHED_FLAG_UTIL_CLAMP_MIN &&
	    attr->sched_util_min != -1) अणु
		uclamp_se_set(&p->uclamp_req[UCLAMP_MIN],
			      attr->sched_util_min, true);
	पूर्ण

	अगर (attr->sched_flags & SCHED_FLAG_UTIL_CLAMP_MAX &&
	    attr->sched_util_max != -1) अणु
		uclamp_se_set(&p->uclamp_req[UCLAMP_MAX],
			      attr->sched_util_max, true);
	पूर्ण
पूर्ण

अटल व्योम uclamp_विभाजन(काष्ठा task_काष्ठा *p)
अणु
	क्रमागत uclamp_id clamp_id;

	/*
	 * We करोn't need to hold task_rq_lock() when updating p->uclamp_* here
	 * as the task is still at its early विभाजन stages.
	 */
	क्रम_each_clamp_id(clamp_id)
		p->uclamp[clamp_id].active = false;

	अगर (likely(!p->sched_reset_on_विभाजन))
		वापस;

	क्रम_each_clamp_id(clamp_id) अणु
		uclamp_se_set(&p->uclamp_req[clamp_id],
			      uclamp_none(clamp_id), false);
	पूर्ण
पूर्ण

अटल व्योम uclamp_post_विभाजन(काष्ठा task_काष्ठा *p)
अणु
	uclamp_update_util_min_rt_शेष(p);
पूर्ण

अटल व्योम __init init_uclamp_rq(काष्ठा rq *rq)
अणु
	क्रमागत uclamp_id clamp_id;
	काष्ठा uclamp_rq *uc_rq = rq->uclamp;

	क्रम_each_clamp_id(clamp_id) अणु
		uc_rq[clamp_id] = (काष्ठा uclamp_rq) अणु
			.value = uclamp_none(clamp_id)
		पूर्ण;
	पूर्ण

	rq->uclamp_flags = 0;
पूर्ण

अटल व्योम __init init_uclamp(व्योम)
अणु
	काष्ठा uclamp_se uc_max = अणुपूर्ण;
	क्रमागत uclamp_id clamp_id;
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu)
		init_uclamp_rq(cpu_rq(cpu));

	क्रम_each_clamp_id(clamp_id) अणु
		uclamp_se_set(&init_task.uclamp_req[clamp_id],
			      uclamp_none(clamp_id), false);
	पूर्ण

	/* System शेषs allow max clamp values क्रम both indexes */
	uclamp_se_set(&uc_max, uclamp_none(UCLAMP_MAX), false);
	क्रम_each_clamp_id(clamp_id) अणु
		uclamp_शेष[clamp_id] = uc_max;
#अगर_घोषित CONFIG_UCLAMP_TASK_GROUP
		root_task_group.uclamp_req[clamp_id] = uc_max;
		root_task_group.uclamp[clamp_id] = uc_max;
#पूर्ण_अगर
	पूर्ण
पूर्ण

#अन्यथा /* CONFIG_UCLAMP_TASK */
अटल अंतरभूत व्योम uclamp_rq_inc(काष्ठा rq *rq, काष्ठा task_काष्ठा *p) अणु पूर्ण
अटल अंतरभूत व्योम uclamp_rq_dec(काष्ठा rq *rq, काष्ठा task_काष्ठा *p) अणु पूर्ण
अटल अंतरभूत पूर्णांक uclamp_validate(काष्ठा task_काष्ठा *p,
				  स्थिर काष्ठा sched_attr *attr)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
अटल व्योम __setscheduler_uclamp(काष्ठा task_काष्ठा *p,
				  स्थिर काष्ठा sched_attr *attr) अणु पूर्ण
अटल अंतरभूत व्योम uclamp_विभाजन(काष्ठा task_काष्ठा *p) अणु पूर्ण
अटल अंतरभूत व्योम uclamp_post_विभाजन(काष्ठा task_काष्ठा *p) अणु पूर्ण
अटल अंतरभूत व्योम init_uclamp(व्योम) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_UCLAMP_TASK */

अटल अंतरभूत व्योम enqueue_task(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक flags)
अणु
	अगर (!(flags & ENQUEUE_NOCLOCK))
		update_rq_घड़ी(rq);

	अगर (!(flags & ENQUEUE_RESTORE)) अणु
		sched_info_queued(rq, p);
		psi_enqueue(p, flags & ENQUEUE_WAKEUP);
	पूर्ण

	uclamp_rq_inc(rq, p);
	p->sched_class->enqueue_task(rq, p, flags);
पूर्ण

अटल अंतरभूत व्योम dequeue_task(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक flags)
अणु
	अगर (!(flags & DEQUEUE_NOCLOCK))
		update_rq_घड़ी(rq);

	अगर (!(flags & DEQUEUE_SAVE)) अणु
		sched_info_dequeued(rq, p);
		psi_dequeue(p, flags & DEQUEUE_SLEEP);
	पूर्ण

	uclamp_rq_dec(rq, p);
	p->sched_class->dequeue_task(rq, p, flags);
पूर्ण

व्योम activate_task(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक flags)
अणु
	enqueue_task(rq, p, flags);

	p->on_rq = TASK_ON_RQ_QUEUED;
पूर्ण

व्योम deactivate_task(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक flags)
अणु
	p->on_rq = (flags & DEQUEUE_SLEEP) ? 0 : TASK_ON_RQ_MIGRATING;

	dequeue_task(rq, p, flags);
पूर्ण

/*
 * __normal_prio - वापस the priority that is based on the अटल prio
 */
अटल अंतरभूत पूर्णांक __normal_prio(काष्ठा task_काष्ठा *p)
अणु
	वापस p->अटल_prio;
पूर्ण

/*
 * Calculate the expected normal priority: i.e. priority
 * without taking RT-inheritance पूर्णांकo account. Might be
 * boosted by पूर्णांकeractivity modअगरiers. Changes upon विभाजन,
 * setprio syscalls, and whenever the पूर्णांकeractivity
 * estimator recalculates.
 */
अटल अंतरभूत पूर्णांक normal_prio(काष्ठा task_काष्ठा *p)
अणु
	पूर्णांक prio;

	अगर (task_has_dl_policy(p))
		prio = MAX_DL_PRIO-1;
	अन्यथा अगर (task_has_rt_policy(p))
		prio = MAX_RT_PRIO-1 - p->rt_priority;
	अन्यथा
		prio = __normal_prio(p);
	वापस prio;
पूर्ण

/*
 * Calculate the current priority, i.e. the priority
 * taken पूर्णांकo account by the scheduler. This value might
 * be boosted by RT tasks, or might be boosted by
 * पूर्णांकeractivity modअगरiers. Will be RT अगर the task got
 * RT-boosted. If not then it वापसs p->normal_prio.
 */
अटल पूर्णांक effective_prio(काष्ठा task_काष्ठा *p)
अणु
	p->normal_prio = normal_prio(p);
	/*
	 * If we are RT tasks or we were boosted to RT priority,
	 * keep the priority unchanged. Otherwise, update priority
	 * to the normal priority:
	 */
	अगर (!rt_prio(p->prio))
		वापस p->normal_prio;
	वापस p->prio;
पूर्ण

/**
 * task_curr - is this task currently executing on a CPU?
 * @p: the task in question.
 *
 * Return: 1 अगर the task is currently executing. 0 otherwise.
 */
अंतरभूत पूर्णांक task_curr(स्थिर काष्ठा task_काष्ठा *p)
अणु
	वापस cpu_curr(task_cpu(p)) == p;
पूर्ण

/*
 * चयनed_from, चयनed_to and prio_changed must _NOT_ drop rq->lock,
 * use the balance_callback list अगर you want balancing.
 *
 * this means any call to check_class_changed() must be followed by a call to
 * balance_callback().
 */
अटल अंतरभूत व्योम check_class_changed(काष्ठा rq *rq, काष्ठा task_काष्ठा *p,
				       स्थिर काष्ठा sched_class *prev_class,
				       पूर्णांक oldprio)
अणु
	अगर (prev_class != p->sched_class) अणु
		अगर (prev_class->चयनed_from)
			prev_class->चयनed_from(rq, p);

		p->sched_class->चयनed_to(rq, p);
	पूर्ण अन्यथा अगर (oldprio != p->prio || dl_task(p))
		p->sched_class->prio_changed(rq, p, oldprio);
पूर्ण

व्योम check_preempt_curr(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक flags)
अणु
	अगर (p->sched_class == rq->curr->sched_class)
		rq->curr->sched_class->check_preempt_curr(rq, p, flags);
	अन्यथा अगर (p->sched_class > rq->curr->sched_class)
		resched_curr(rq);

	/*
	 * A queue event has occurred, and we're going to schedule.  In
	 * this हाल, we can save a useless back to back घड़ी update.
	 */
	अगर (task_on_rq_queued(rq->curr) && test_tsk_need_resched(rq->curr))
		rq_घड़ी_skip_update(rq);
पूर्ण

#अगर_घोषित CONFIG_SMP

अटल व्योम
__करो_set_cpus_allowed(काष्ठा task_काष्ठा *p, स्थिर काष्ठा cpumask *new_mask, u32 flags);

अटल पूर्णांक __set_cpus_allowed_ptr(काष्ठा task_काष्ठा *p,
				  स्थिर काष्ठा cpumask *new_mask,
				  u32 flags);

अटल व्योम migrate_disable_चयन(काष्ठा rq *rq, काष्ठा task_काष्ठा *p)
अणु
	अगर (likely(!p->migration_disabled))
		वापस;

	अगर (p->cpus_ptr != &p->cpus_mask)
		वापस;

	/*
	 * Violates locking rules! see comment in __करो_set_cpus_allowed().
	 */
	__करो_set_cpus_allowed(p, cpumask_of(rq->cpu), SCA_MIGRATE_DISABLE);
पूर्ण

व्योम migrate_disable(व्योम)
अणु
	काष्ठा task_काष्ठा *p = current;

	अगर (p->migration_disabled) अणु
		p->migration_disabled++;
		वापस;
	पूर्ण

	preempt_disable();
	this_rq()->nr_pinned++;
	p->migration_disabled = 1;
	preempt_enable();
पूर्ण
EXPORT_SYMBOL_GPL(migrate_disable);

व्योम migrate_enable(व्योम)
अणु
	काष्ठा task_काष्ठा *p = current;

	अगर (p->migration_disabled > 1) अणु
		p->migration_disabled--;
		वापस;
	पूर्ण

	/*
	 * Ensure stop_task runs either beक्रमe or after this, and that
	 * __set_cpus_allowed_ptr(SCA_MIGRATE_ENABLE) करोesn't schedule().
	 */
	preempt_disable();
	अगर (p->cpus_ptr != &p->cpus_mask)
		__set_cpus_allowed_ptr(p, &p->cpus_mask, SCA_MIGRATE_ENABLE);
	/*
	 * Mustn't clear migration_disabled() until cpus_ptr poपूर्णांकs back at the
	 * regular cpus_mask, otherwise things that race (eg.
	 * select_fallback_rq) get confused.
	 */
	barrier();
	p->migration_disabled = 0;
	this_rq()->nr_pinned--;
	preempt_enable();
पूर्ण
EXPORT_SYMBOL_GPL(migrate_enable);

अटल अंतरभूत bool rq_has_pinned_tasks(काष्ठा rq *rq)
अणु
	वापस rq->nr_pinned;
पूर्ण

/*
 * Per-CPU kthपढ़ोs are allowed to run on !active && online CPUs, see
 * __set_cpus_allowed_ptr() and select_fallback_rq().
 */
अटल अंतरभूत bool is_cpu_allowed(काष्ठा task_काष्ठा *p, पूर्णांक cpu)
अणु
	/* When not in the task's cpumask, no poपूर्णांक in looking further. */
	अगर (!cpumask_test_cpu(cpu, p->cpus_ptr))
		वापस false;

	/* migrate_disabled() must be allowed to finish. */
	अगर (is_migration_disabled(p))
		वापस cpu_online(cpu);

	/* Non kernel thपढ़ोs are not allowed during either online or offline. */
	अगर (!(p->flags & PF_KTHREAD))
		वापस cpu_active(cpu);

	/* KTHREAD_IS_PER_CPU is always allowed. */
	अगर (kthपढ़ो_is_per_cpu(p))
		वापस cpu_online(cpu);

	/* Regular kernel thपढ़ोs करोn't get to stay during offline. */
	अगर (cpu_dying(cpu))
		वापस false;

	/* But are allowed during online. */
	वापस cpu_online(cpu);
पूर्ण

/*
 * This is how migration works:
 *
 * 1) we invoke migration_cpu_stop() on the target CPU using
 *    stop_one_cpu().
 * 2) stopper starts to run (implicitly क्रमcing the migrated thपढ़ो
 *    off the CPU)
 * 3) it checks whether the migrated task is still in the wrong runqueue.
 * 4) अगर it's in the wrong runqueue then the migration thपढ़ो हटाओs
 *    it and माला_दो it पूर्णांकo the right queue.
 * 5) stopper completes and stop_one_cpu() वापसs and the migration
 *    is करोne.
 */

/*
 * move_queued_task - move a queued task to new rq.
 *
 * Returns (locked) new rq. Old rq's lock is released.
 */
अटल काष्ठा rq *move_queued_task(काष्ठा rq *rq, काष्ठा rq_flags *rf,
				   काष्ठा task_काष्ठा *p, पूर्णांक new_cpu)
अणु
	lockdep_निश्चित_held(&rq->lock);

	deactivate_task(rq, p, DEQUEUE_NOCLOCK);
	set_task_cpu(p, new_cpu);
	rq_unlock(rq, rf);

	rq = cpu_rq(new_cpu);

	rq_lock(rq, rf);
	BUG_ON(task_cpu(p) != new_cpu);
	activate_task(rq, p, 0);
	check_preempt_curr(rq, p, 0);

	वापस rq;
पूर्ण

काष्ठा migration_arg अणु
	काष्ठा task_काष्ठा		*task;
	पूर्णांक				dest_cpu;
	काष्ठा set_affinity_pending	*pending;
पूर्ण;

/*
 * @refs: number of रुको_क्रम_completion()
 * @stop_pending: is @stop_work in use
 */
काष्ठा set_affinity_pending अणु
	refcount_t		refs;
	अचिन्हित पूर्णांक		stop_pending;
	काष्ठा completion	करोne;
	काष्ठा cpu_stop_work	stop_work;
	काष्ठा migration_arg	arg;
पूर्ण;

/*
 * Move (not current) task off this CPU, onto the destination CPU. We're करोing
 * this because either it can't run here any more (set_cpus_allowed()
 * away from this CPU, or CPU going करोwn), or because we're
 * attempting to rebalance this task on exec (sched_exec).
 *
 * So we race with normal scheduler movements, but that's OK, as दीर्घ
 * as the task is no दीर्घer on this CPU.
 */
अटल काष्ठा rq *__migrate_task(काष्ठा rq *rq, काष्ठा rq_flags *rf,
				 काष्ठा task_काष्ठा *p, पूर्णांक dest_cpu)
अणु
	/* Affinity changed (again). */
	अगर (!is_cpu_allowed(p, dest_cpu))
		वापस rq;

	update_rq_घड़ी(rq);
	rq = move_queued_task(rq, rf, p, dest_cpu);

	वापस rq;
पूर्ण

/*
 * migration_cpu_stop - this will be executed by a highprio stopper thपढ़ो
 * and perक्रमms thपढ़ो migration by bumping thपढ़ो off CPU then
 * 'pushing' onto another runqueue.
 */
अटल पूर्णांक migration_cpu_stop(व्योम *data)
अणु
	काष्ठा migration_arg *arg = data;
	काष्ठा set_affinity_pending *pending = arg->pending;
	काष्ठा task_काष्ठा *p = arg->task;
	पूर्णांक dest_cpu = arg->dest_cpu;
	काष्ठा rq *rq = this_rq();
	bool complete = false;
	काष्ठा rq_flags rf;

	/*
	 * The original target CPU might have gone करोwn and we might
	 * be on another CPU but it करोesn't matter.
	 */
	local_irq_save(rf.flags);
	/*
	 * We need to explicitly wake pending tasks beक्रमe running
	 * __migrate_task() such that we will not miss enक्रमcing cpus_ptr
	 * during wakeups, see set_cpus_allowed_ptr()'s TASK_WAKING test.
	 */
	flush_smp_call_function_from_idle();

	raw_spin_lock(&p->pi_lock);
	rq_lock(rq, &rf);

	/*
	 * If we were passed a pending, then ->stop_pending was set, thus
	 * p->migration_pending must have reमुख्यed stable.
	 */
	WARN_ON_ONCE(pending && pending != p->migration_pending);

	/*
	 * If task_rq(p) != rq, it cannot be migrated here, because we're
	 * holding rq->lock, अगर p->on_rq == 0 it cannot get enqueued because
	 * we're holding p->pi_lock.
	 */
	अगर (task_rq(p) == rq) अणु
		अगर (is_migration_disabled(p))
			जाओ out;

		अगर (pending) अणु
			p->migration_pending = शून्य;
			complete = true;
		पूर्ण

		अगर (dest_cpu < 0) अणु
			अगर (cpumask_test_cpu(task_cpu(p), &p->cpus_mask))
				जाओ out;

			dest_cpu = cpumask_any_distribute(&p->cpus_mask);
		पूर्ण

		अगर (task_on_rq_queued(p))
			rq = __migrate_task(rq, &rf, p, dest_cpu);
		अन्यथा
			p->wake_cpu = dest_cpu;

		/*
		 * XXX __migrate_task() can fail, at which poपूर्णांक we might end
		 * up running on a करोdgy CPU, AFAICT this can only happen
		 * during CPU hotplug, at which poपूर्णांक we'll get pushed out
		 * anyway, so it's probably not a big deal.
		 */

	पूर्ण अन्यथा अगर (pending) अणु
		/*
		 * This happens when we get migrated between migrate_enable()'s
		 * preempt_enable() and scheduling the stopper task. At that
		 * poपूर्णांक we're a regular task again and not current anymore.
		 *
		 * A !PREEMPT kernel has a giant hole here, which makes it far
		 * more likely.
		 */

		/*
		 * The task moved beक्रमe the stopper got to run. We're holding
		 * ->pi_lock, so the allowed mask is stable - अगर it got
		 * somewhere allowed, we're करोne.
		 */
		अगर (cpumask_test_cpu(task_cpu(p), p->cpus_ptr)) अणु
			p->migration_pending = शून्य;
			complete = true;
			जाओ out;
		पूर्ण

		/*
		 * When migrate_enable() hits a rq mis-match we can't reliably
		 * determine is_migration_disabled() and so have to chase after
		 * it.
		 */
		WARN_ON_ONCE(!pending->stop_pending);
		task_rq_unlock(rq, p, &rf);
		stop_one_cpu_noरुको(task_cpu(p), migration_cpu_stop,
				    &pending->arg, &pending->stop_work);
		वापस 0;
	पूर्ण
out:
	अगर (pending)
		pending->stop_pending = false;
	task_rq_unlock(rq, p, &rf);

	अगर (complete)
		complete_all(&pending->करोne);

	वापस 0;
पूर्ण

पूर्णांक push_cpu_stop(व्योम *arg)
अणु
	काष्ठा rq *lowest_rq = शून्य, *rq = this_rq();
	काष्ठा task_काष्ठा *p = arg;

	raw_spin_lock_irq(&p->pi_lock);
	raw_spin_lock(&rq->lock);

	अगर (task_rq(p) != rq)
		जाओ out_unlock;

	अगर (is_migration_disabled(p)) अणु
		p->migration_flags |= MDF_PUSH;
		जाओ out_unlock;
	पूर्ण

	p->migration_flags &= ~MDF_PUSH;

	अगर (p->sched_class->find_lock_rq)
		lowest_rq = p->sched_class->find_lock_rq(p, rq);

	अगर (!lowest_rq)
		जाओ out_unlock;

	// XXX validate p is still the highest prio task
	अगर (task_rq(p) == rq) अणु
		deactivate_task(rq, p, 0);
		set_task_cpu(p, lowest_rq->cpu);
		activate_task(lowest_rq, p, 0);
		resched_curr(lowest_rq);
	पूर्ण

	द्विगुन_unlock_balance(rq, lowest_rq);

out_unlock:
	rq->push_busy = false;
	raw_spin_unlock(&rq->lock);
	raw_spin_unlock_irq(&p->pi_lock);

	put_task_काष्ठा(p);
	वापस 0;
पूर्ण

/*
 * sched_class::set_cpus_allowed must करो the below, but is not required to
 * actually call this function.
 */
व्योम set_cpus_allowed_common(काष्ठा task_काष्ठा *p, स्थिर काष्ठा cpumask *new_mask, u32 flags)
अणु
	अगर (flags & (SCA_MIGRATE_ENABLE | SCA_MIGRATE_DISABLE)) अणु
		p->cpus_ptr = new_mask;
		वापस;
	पूर्ण

	cpumask_copy(&p->cpus_mask, new_mask);
	p->nr_cpus_allowed = cpumask_weight(new_mask);
पूर्ण

अटल व्योम
__करो_set_cpus_allowed(काष्ठा task_काष्ठा *p, स्थिर काष्ठा cpumask *new_mask, u32 flags)
अणु
	काष्ठा rq *rq = task_rq(p);
	bool queued, running;

	/*
	 * This here violates the locking rules क्रम affinity, since we're only
	 * supposed to change these variables जबतक holding both rq->lock and
	 * p->pi_lock.
	 *
	 * HOWEVER, it magically works, because ttwu() is the only code that
	 * accesses these variables under p->pi_lock and only करोes so after
	 * smp_cond_load_acquire(&p->on_cpu, !VAL), and we're in __schedule()
	 * beक्रमe finish_task().
	 *
	 * XXX करो further audits, this smells like something putrid.
	 */
	अगर (flags & SCA_MIGRATE_DISABLE)
		SCHED_WARN_ON(!p->on_cpu);
	अन्यथा
		lockdep_निश्चित_held(&p->pi_lock);

	queued = task_on_rq_queued(p);
	running = task_current(rq, p);

	अगर (queued) अणु
		/*
		 * Because __kthपढ़ो_bind() calls this on blocked tasks without
		 * holding rq->lock.
		 */
		lockdep_निश्चित_held(&rq->lock);
		dequeue_task(rq, p, DEQUEUE_SAVE | DEQUEUE_NOCLOCK);
	पूर्ण
	अगर (running)
		put_prev_task(rq, p);

	p->sched_class->set_cpus_allowed(p, new_mask, flags);

	अगर (queued)
		enqueue_task(rq, p, ENQUEUE_RESTORE | ENQUEUE_NOCLOCK);
	अगर (running)
		set_next_task(rq, p);
पूर्ण

व्योम करो_set_cpus_allowed(काष्ठा task_काष्ठा *p, स्थिर काष्ठा cpumask *new_mask)
अणु
	__करो_set_cpus_allowed(p, new_mask, 0);
पूर्ण

/*
 * This function is wildly self concurrent; here be dragons.
 *
 *
 * When given a valid mask, __set_cpus_allowed_ptr() must block until the
 * designated task is enqueued on an allowed CPU. If that task is currently
 * running, we have to kick it out using the CPU stopper.
 *
 * Migrate-Disable comes aदीर्घ and tramples all over our nice sandcastle.
 * Consider:
 *
 *     Initial conditions: P0->cpus_mask = [0, 1]
 *
 *     P0@CPU0                  P1
 *
 *     migrate_disable();
 *     <preempted>
 *                              set_cpus_allowed_ptr(P0, [1]);
 *
 * P1 *cannot* वापस from this set_cpus_allowed_ptr() call until P0 executes
 * its outermost migrate_enable() (i.e. it निकासs its Migrate-Disable region).
 * This means we need the following scheme:
 *
 *     P0@CPU0                  P1
 *
 *     migrate_disable();
 *     <preempted>
 *                              set_cpus_allowed_ptr(P0, [1]);
 *                                <blocks>
 *     <resumes>
 *     migrate_enable();
 *       __set_cpus_allowed_ptr();
 *       <wakes local stopper>
 *                         `--> <woken on migration completion>
 *
 * Now the fun stuff: there may be several P1-like tasks, i.e. multiple
 * concurrent set_cpus_allowed_ptr(P0, [*]) calls. CPU affinity changes of any
 * task p are serialized by p->pi_lock, which we can leverage: the one that
 * should come पूर्णांकo effect at the end of the Migrate-Disable region is the last
 * one. This means we only need to track a single cpumask (i.e. p->cpus_mask),
 * but we still need to properly संकेत those रुकोing tasks at the appropriate
 * moment.
 *
 * This is implemented using काष्ठा set_affinity_pending. The first
 * __set_cpus_allowed_ptr() caller within a given Migrate-Disable region will
 * setup an instance of that काष्ठा and install it on the targeted task_काष्ठा.
 * Any and all further callers will reuse that instance. Those then रुको क्रम
 * a completion संकेतed at the tail of the CPU stopper callback (1), triggered
 * on the end of the Migrate-Disable region (i.e. outermost migrate_enable()).
 *
 *
 * (1) In the हालs covered above. There is one more where the completion is
 * संकेतed within affine_move_task() itself: when a subsequent affinity request
 * occurs after the stopper bailed out due to the targeted task still being
 * Migrate-Disable. Consider:
 *
 *     Initial conditions: P0->cpus_mask = [0, 1]
 *
 *     CPU0		  P1				P2
 *     <P0>
 *       migrate_disable();
 *       <preempted>
 *                        set_cpus_allowed_ptr(P0, [1]);
 *                          <blocks>
 *     <migration/0>
 *       migration_cpu_stop()
 *         is_migration_disabled()
 *           <bails>
 *                                                       set_cpus_allowed_ptr(P0, [0, 1]);
 *                                                         <संकेत completion>
 *                          <awakes>
 *
 * Note that the above is safe vs a concurrent migrate_enable(), as any
 * pending affinity completion is preceded by an uninstallation of
 * p->migration_pending करोne with p->pi_lock held.
 */
अटल पूर्णांक affine_move_task(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, काष्ठा rq_flags *rf,
			    पूर्णांक dest_cpu, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा set_affinity_pending my_pending = अणु पूर्ण, *pending = शून्य;
	bool stop_pending, complete = false;

	/* Can the task run on the task's current CPU? If so, we're करोne */
	अगर (cpumask_test_cpu(task_cpu(p), &p->cpus_mask)) अणु
		काष्ठा task_काष्ठा *push_task = शून्य;

		अगर ((flags & SCA_MIGRATE_ENABLE) &&
		    (p->migration_flags & MDF_PUSH) && !rq->push_busy) अणु
			rq->push_busy = true;
			push_task = get_task_काष्ठा(p);
		पूर्ण

		/*
		 * If there are pending रुकोers, but no pending stop_work,
		 * then complete now.
		 */
		pending = p->migration_pending;
		अगर (pending && !pending->stop_pending) अणु
			p->migration_pending = शून्य;
			complete = true;
		पूर्ण

		task_rq_unlock(rq, p, rf);

		अगर (push_task) अणु
			stop_one_cpu_noरुको(rq->cpu, push_cpu_stop,
					    p, &rq->push_work);
		पूर्ण

		अगर (complete)
			complete_all(&pending->करोne);

		वापस 0;
	पूर्ण

	अगर (!(flags & SCA_MIGRATE_ENABLE)) अणु
		/* serialized by p->pi_lock */
		अगर (!p->migration_pending) अणु
			/* Install the request */
			refcount_set(&my_pending.refs, 1);
			init_completion(&my_pending.करोne);
			my_pending.arg = (काष्ठा migration_arg) अणु
				.task = p,
				.dest_cpu = -1,		/* any */
				.pending = &my_pending,
			पूर्ण;

			p->migration_pending = &my_pending;
		पूर्ण अन्यथा अणु
			pending = p->migration_pending;
			refcount_inc(&pending->refs);
		पूर्ण
	पूर्ण
	pending = p->migration_pending;
	/*
	 * - !MIGRATE_ENABLE:
	 *   we'll have installed a pending if there wasn't one alपढ़ोy.
	 *
	 * - MIGRATE_ENABLE:
	 *   we're here because the current CPU isn't matching anymore,
	 *   the only way that can happen is because of a concurrent
	 *   set_cpus_allowed_ptr() call, which should then still be
	 *   pending completion.
	 *
	 * Either way, we really should have a @pending here.
	 */
	अगर (WARN_ON_ONCE(!pending)) अणु
		task_rq_unlock(rq, p, rf);
		वापस -EINVAL;
	पूर्ण

	अगर (task_running(rq, p) || p->state == TASK_WAKING) अणु
		/*
		 * MIGRATE_ENABLE माला_लो here because 'p == current', but क्रम
		 * anything अन्यथा we cannot करो is_migration_disabled(), punt
		 * and have the stopper function handle it all race-मुक्त.
		 */
		stop_pending = pending->stop_pending;
		अगर (!stop_pending)
			pending->stop_pending = true;

		अगर (flags & SCA_MIGRATE_ENABLE)
			p->migration_flags &= ~MDF_PUSH;

		task_rq_unlock(rq, p, rf);

		अगर (!stop_pending) अणु
			stop_one_cpu_noरुको(cpu_of(rq), migration_cpu_stop,
					    &pending->arg, &pending->stop_work);
		पूर्ण

		अगर (flags & SCA_MIGRATE_ENABLE)
			वापस 0;
	पूर्ण अन्यथा अणु

		अगर (!is_migration_disabled(p)) अणु
			अगर (task_on_rq_queued(p))
				rq = move_queued_task(rq, rf, p, dest_cpu);

			अगर (!pending->stop_pending) अणु
				p->migration_pending = शून्य;
				complete = true;
			पूर्ण
		पूर्ण
		task_rq_unlock(rq, p, rf);

		अगर (complete)
			complete_all(&pending->करोne);
	पूर्ण

	रुको_क्रम_completion(&pending->करोne);

	अगर (refcount_dec_and_test(&pending->refs))
		wake_up_var(&pending->refs); /* No UaF, just an address */

	/*
	 * Block the original owner of &pending until all subsequent callers
	 * have seen the completion and decremented the refcount
	 */
	रुको_var_event(&my_pending.refs, !refcount_पढ़ो(&my_pending.refs));

	/* ARGH */
	WARN_ON_ONCE(my_pending.stop_pending);

	वापस 0;
पूर्ण

/*
 * Change a given task's CPU affinity. Migrate the thपढ़ो to a
 * proper CPU and schedule it away अगर the CPU it's executing on
 * is हटाओd from the allowed biपंचांगask.
 *
 * NOTE: the caller must have a valid reference to the task, the
 * task must not निकास() & deallocate itself prematurely. The
 * call is not atomic; no spinlocks may be held.
 */
अटल पूर्णांक __set_cpus_allowed_ptr(काष्ठा task_काष्ठा *p,
				  स्थिर काष्ठा cpumask *new_mask,
				  u32 flags)
अणु
	स्थिर काष्ठा cpumask *cpu_valid_mask = cpu_active_mask;
	अचिन्हित पूर्णांक dest_cpu;
	काष्ठा rq_flags rf;
	काष्ठा rq *rq;
	पूर्णांक ret = 0;

	rq = task_rq_lock(p, &rf);
	update_rq_घड़ी(rq);

	अगर (p->flags & PF_KTHREAD || is_migration_disabled(p)) अणु
		/*
		 * Kernel thपढ़ोs are allowed on online && !active CPUs,
		 * however, during cpu-hot-unplug, even these might get pushed
		 * away अगर not KTHREAD_IS_PER_CPU.
		 *
		 * Specअगरically, migration_disabled() tasks must not fail the
		 * cpumask_any_and_distribute() pick below, esp. so on
		 * SCA_MIGRATE_ENABLE, otherwise we'll not call
		 * set_cpus_allowed_common() and actually reset p->cpus_ptr.
		 */
		cpu_valid_mask = cpu_online_mask;
	पूर्ण

	/*
	 * Must re-check here, to बंद a race against __kthपढ़ो_bind(),
	 * sched_setaffinity() is not guaranteed to observe the flag.
	 */
	अगर ((flags & SCA_CHECK) && (p->flags & PF_NO_SETAFFINITY)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (!(flags & SCA_MIGRATE_ENABLE)) अणु
		अगर (cpumask_equal(&p->cpus_mask, new_mask))
			जाओ out;

		अगर (WARN_ON_ONCE(p == current &&
				 is_migration_disabled(p) &&
				 !cpumask_test_cpu(task_cpu(p), new_mask))) अणु
			ret = -EBUSY;
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * Picking a ~अक्रमom cpu helps in हालs where we are changing affinity
	 * क्रम groups of tasks (ie. cpuset), so that load balancing is not
	 * immediately required to distribute the tasks within their new mask.
	 */
	dest_cpu = cpumask_any_and_distribute(cpu_valid_mask, new_mask);
	अगर (dest_cpu >= nr_cpu_ids) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	__करो_set_cpus_allowed(p, new_mask, flags);

	वापस affine_move_task(rq, p, &rf, dest_cpu, flags);

out:
	task_rq_unlock(rq, p, &rf);

	वापस ret;
पूर्ण

पूर्णांक set_cpus_allowed_ptr(काष्ठा task_काष्ठा *p, स्थिर काष्ठा cpumask *new_mask)
अणु
	वापस __set_cpus_allowed_ptr(p, new_mask, 0);
पूर्ण
EXPORT_SYMBOL_GPL(set_cpus_allowed_ptr);

व्योम set_task_cpu(काष्ठा task_काष्ठा *p, अचिन्हित पूर्णांक new_cpu)
अणु
#अगर_घोषित CONFIG_SCHED_DEBUG
	/*
	 * We should never call set_task_cpu() on a blocked task,
	 * ttwu() will sort out the placement.
	 */
	WARN_ON_ONCE(p->state != TASK_RUNNING && p->state != TASK_WAKING &&
			!p->on_rq);

	/*
	 * Migrating fair class task must have p->on_rq = TASK_ON_RQ_MIGRATING,
	 * because schedstat_रुको_अणुstart,endपूर्ण rebase migrating task's रुको_start
	 * समय relying on p->on_rq.
	 */
	WARN_ON_ONCE(p->state == TASK_RUNNING &&
		     p->sched_class == &fair_sched_class &&
		     (p->on_rq && !task_on_rq_migrating(p)));

#अगर_घोषित CONFIG_LOCKDEP
	/*
	 * The caller should hold either p->pi_lock or rq->lock, when changing
	 * a task's CPU. ->pi_lock क्रम waking tasks, rq->lock क्रम runnable tasks.
	 *
	 * sched_move_task() holds both and thus holding either pins the cgroup,
	 * see task_group().
	 *
	 * Furthermore, all task_rq users should acquire both locks, see
	 * task_rq_lock().
	 */
	WARN_ON_ONCE(debug_locks && !(lockdep_is_held(&p->pi_lock) ||
				      lockdep_is_held(&task_rq(p)->lock)));
#पूर्ण_अगर
	/*
	 * Clearly, migrating tasks to offline CPUs is a fairly daft thing.
	 */
	WARN_ON_ONCE(!cpu_online(new_cpu));

	WARN_ON_ONCE(is_migration_disabled(p));
#पूर्ण_अगर

	trace_sched_migrate_task(p, new_cpu);

	अगर (task_cpu(p) != new_cpu) अणु
		अगर (p->sched_class->migrate_task_rq)
			p->sched_class->migrate_task_rq(p, new_cpu);
		p->se.nr_migrations++;
		rseq_migrate(p);
		perf_event_task_migrate(p);
	पूर्ण

	__set_task_cpu(p, new_cpu);
पूर्ण

#अगर_घोषित CONFIG_NUMA_BALANCING
अटल व्योम __migrate_swap_task(काष्ठा task_काष्ठा *p, पूर्णांक cpu)
अणु
	अगर (task_on_rq_queued(p)) अणु
		काष्ठा rq *src_rq, *dst_rq;
		काष्ठा rq_flags srf, drf;

		src_rq = task_rq(p);
		dst_rq = cpu_rq(cpu);

		rq_pin_lock(src_rq, &srf);
		rq_pin_lock(dst_rq, &drf);

		deactivate_task(src_rq, p, 0);
		set_task_cpu(p, cpu);
		activate_task(dst_rq, p, 0);
		check_preempt_curr(dst_rq, p, 0);

		rq_unpin_lock(dst_rq, &drf);
		rq_unpin_lock(src_rq, &srf);

	पूर्ण अन्यथा अणु
		/*
		 * Task isn't running anymore; make it appear like we migrated
		 * it beक्रमe it went to sleep. This means on wakeup we make the
		 * previous CPU our target instead of where it really is.
		 */
		p->wake_cpu = cpu;
	पूर्ण
पूर्ण

काष्ठा migration_swap_arg अणु
	काष्ठा task_काष्ठा *src_task, *dst_task;
	पूर्णांक src_cpu, dst_cpu;
पूर्ण;

अटल पूर्णांक migrate_swap_stop(व्योम *data)
अणु
	काष्ठा migration_swap_arg *arg = data;
	काष्ठा rq *src_rq, *dst_rq;
	पूर्णांक ret = -EAGAIN;

	अगर (!cpu_active(arg->src_cpu) || !cpu_active(arg->dst_cpu))
		वापस -EAGAIN;

	src_rq = cpu_rq(arg->src_cpu);
	dst_rq = cpu_rq(arg->dst_cpu);

	द्विगुन_raw_lock(&arg->src_task->pi_lock,
			&arg->dst_task->pi_lock);
	द्विगुन_rq_lock(src_rq, dst_rq);

	अगर (task_cpu(arg->dst_task) != arg->dst_cpu)
		जाओ unlock;

	अगर (task_cpu(arg->src_task) != arg->src_cpu)
		जाओ unlock;

	अगर (!cpumask_test_cpu(arg->dst_cpu, arg->src_task->cpus_ptr))
		जाओ unlock;

	अगर (!cpumask_test_cpu(arg->src_cpu, arg->dst_task->cpus_ptr))
		जाओ unlock;

	__migrate_swap_task(arg->src_task, arg->dst_cpu);
	__migrate_swap_task(arg->dst_task, arg->src_cpu);

	ret = 0;

unlock:
	द्विगुन_rq_unlock(src_rq, dst_rq);
	raw_spin_unlock(&arg->dst_task->pi_lock);
	raw_spin_unlock(&arg->src_task->pi_lock);

	वापस ret;
पूर्ण

/*
 * Cross migrate two tasks
 */
पूर्णांक migrate_swap(काष्ठा task_काष्ठा *cur, काष्ठा task_काष्ठा *p,
		पूर्णांक target_cpu, पूर्णांक curr_cpu)
अणु
	काष्ठा migration_swap_arg arg;
	पूर्णांक ret = -EINVAL;

	arg = (काष्ठा migration_swap_arg)अणु
		.src_task = cur,
		.src_cpu = curr_cpu,
		.dst_task = p,
		.dst_cpu = target_cpu,
	पूर्ण;

	अगर (arg.src_cpu == arg.dst_cpu)
		जाओ out;

	/*
	 * These three tests are all lockless; this is OK since all of them
	 * will be re-checked with proper locks held further करोwn the line.
	 */
	अगर (!cpu_active(arg.src_cpu) || !cpu_active(arg.dst_cpu))
		जाओ out;

	अगर (!cpumask_test_cpu(arg.dst_cpu, arg.src_task->cpus_ptr))
		जाओ out;

	अगर (!cpumask_test_cpu(arg.src_cpu, arg.dst_task->cpus_ptr))
		जाओ out;

	trace_sched_swap_numa(cur, arg.src_cpu, p, arg.dst_cpu);
	ret = stop_two_cpus(arg.dst_cpu, arg.src_cpu, migrate_swap_stop, &arg);

out:
	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_NUMA_BALANCING */

/*
 * रुको_task_inactive - रुको क्रम a thपढ़ो to unschedule.
 *
 * If @match_state is nonzero, it's the @p->state value just checked and
 * not expected to change.  If it changes, i.e. @p might have woken up,
 * then वापस zero.  When we succeed in रुकोing क्रम @p to be off its CPU,
 * we वापस a positive number (its total चयन count).  If a second call
 * a लघु जबतक later वापसs the same number, the caller can be sure that
 * @p has reमुख्यed unscheduled the whole समय.
 *
 * The caller must ensure that the task *will* unschedule someसमय soon,
 * अन्यथा this function might spin क्रम a *दीर्घ* समय. This function can't
 * be called with पूर्णांकerrupts off, or it may पूर्णांकroduce deadlock with
 * smp_call_function() अगर an IPI is sent by the same process we are
 * रुकोing to become inactive.
 */
अचिन्हित दीर्घ रुको_task_inactive(काष्ठा task_काष्ठा *p, दीर्घ match_state)
अणु
	पूर्णांक running, queued;
	काष्ठा rq_flags rf;
	अचिन्हित दीर्घ ncsw;
	काष्ठा rq *rq;

	क्रम (;;) अणु
		/*
		 * We करो the initial early heuristics without holding
		 * any task-queue locks at all. We'll only try to get
		 * the runqueue lock when things look like they will
		 * work out!
		 */
		rq = task_rq(p);

		/*
		 * If the task is actively running on another CPU
		 * still, just relax and busy-रुको without holding
		 * any locks.
		 *
		 * NOTE! Since we करोn't hold any locks, it's not
		 * even sure that "rq" stays as the right runqueue!
		 * But we करोn't care, since "task_running()" will
		 * वापस false अगर the runqueue has changed and p
		 * is actually now running somewhere अन्यथा!
		 */
		जबतक (task_running(rq, p)) अणु
			अगर (match_state && unlikely(p->state != match_state))
				वापस 0;
			cpu_relax();
		पूर्ण

		/*
		 * Ok, समय to look more बंदly! We need the rq
		 * lock now, to be *sure*. If we're wrong, we'll
		 * just go back and repeat.
		 */
		rq = task_rq_lock(p, &rf);
		trace_sched_रुको_task(p);
		running = task_running(rq, p);
		queued = task_on_rq_queued(p);
		ncsw = 0;
		अगर (!match_state || p->state == match_state)
			ncsw = p->nvcsw | दीर्घ_न्यून; /* sets MSB */
		task_rq_unlock(rq, p, &rf);

		/*
		 * If it changed from the expected state, bail out now.
		 */
		अगर (unlikely(!ncsw))
			अवरोध;

		/*
		 * Was it really running after all now that we
		 * checked with the proper locks actually held?
		 *
		 * Oops. Go back and try again..
		 */
		अगर (unlikely(running)) अणु
			cpu_relax();
			जारी;
		पूर्ण

		/*
		 * It's not enough that it's not actively running,
		 * it must be off the runqueue _entirely_, and not
		 * preempted!
		 *
		 * So अगर it was still runnable (but just not actively
		 * running right now), it's preempted, and we should
		 * yield - it could be a जबतक.
		 */
		अगर (unlikely(queued)) अणु
			kसमय_प्रकार to = NSEC_PER_SEC / HZ;

			set_current_state(TASK_UNINTERRUPTIBLE);
			schedule_hrसमयout(&to, HRTIMER_MODE_REL);
			जारी;
		पूर्ण

		/*
		 * Ahh, all good. It wasn't running, and it wasn't
		 * runnable, which means that it will never become
		 * running in the future either. We're all करोne!
		 */
		अवरोध;
	पूर्ण

	वापस ncsw;
पूर्ण

/***
 * kick_process - kick a running thपढ़ो to enter/निकास the kernel
 * @p: the to-be-kicked thपढ़ो
 *
 * Cause a process which is running on another CPU to enter
 * kernel-mode, without any delay. (to get संकेतs handled.)
 *
 * NOTE: this function करोesn't have to take the runqueue lock,
 * because all it wants to ensure is that the remote task enters
 * the kernel. If the IPI races and the task has been migrated
 * to another CPU then no harm is करोne and the purpose has been
 * achieved as well.
 */
व्योम kick_process(काष्ठा task_काष्ठा *p)
अणु
	पूर्णांक cpu;

	preempt_disable();
	cpu = task_cpu(p);
	अगर ((cpu != smp_processor_id()) && task_curr(p))
		smp_send_reschedule(cpu);
	preempt_enable();
पूर्ण
EXPORT_SYMBOL_GPL(kick_process);

/*
 * ->cpus_ptr is रक्षित by both rq->lock and p->pi_lock
 *
 * A few notes on cpu_active vs cpu_online:
 *
 *  - cpu_active must be a subset of cpu_online
 *
 *  - on CPU-up we allow per-CPU kthपढ़ोs on the online && !active CPU,
 *    see __set_cpus_allowed_ptr(). At this poपूर्णांक the newly online
 *    CPU isn't yet part of the sched करोमुख्यs, and balancing will not
 *    see it.
 *
 *  - on CPU-करोwn we clear cpu_active() to mask the sched करोमुख्यs and
 *    aव्योम the load balancer to place new tasks on the to be हटाओd
 *    CPU. Existing tasks will reमुख्य running there and will be taken
 *    off.
 *
 * This means that fallback selection must not select !active CPUs.
 * And can assume that any active CPU must be online. Conversely
 * select_task_rq() below may allow selection of !active CPUs in order
 * to satisfy the above rules.
 */
अटल पूर्णांक select_fallback_rq(पूर्णांक cpu, काष्ठा task_काष्ठा *p)
अणु
	पूर्णांक nid = cpu_to_node(cpu);
	स्थिर काष्ठा cpumask *nodemask = शून्य;
	क्रमागत अणु cpuset, possible, fail पूर्ण state = cpuset;
	पूर्णांक dest_cpu;

	/*
	 * If the node that the CPU is on has been offlined, cpu_to_node()
	 * will वापस -1. There is no CPU on the node, and we should
	 * select the CPU on the other node.
	 */
	अगर (nid != -1) अणु
		nodemask = cpumask_of_node(nid);

		/* Look क्रम allowed, online CPU in same node. */
		क्रम_each_cpu(dest_cpu, nodemask) अणु
			अगर (!cpu_active(dest_cpu))
				जारी;
			अगर (cpumask_test_cpu(dest_cpu, p->cpus_ptr))
				वापस dest_cpu;
		पूर्ण
	पूर्ण

	क्रम (;;) अणु
		/* Any allowed, online CPU? */
		क्रम_each_cpu(dest_cpu, p->cpus_ptr) अणु
			अगर (!is_cpu_allowed(p, dest_cpu))
				जारी;

			जाओ out;
		पूर्ण

		/* No more Mr. Nice Guy. */
		चयन (state) अणु
		हाल cpuset:
			अगर (IS_ENABLED(CONFIG_CPUSETS)) अणु
				cpuset_cpus_allowed_fallback(p);
				state = possible;
				अवरोध;
			पूर्ण
			fallthrough;
		हाल possible:
			/*
			 * XXX When called from select_task_rq() we only
			 * hold p->pi_lock and again violate locking order.
			 *
			 * More yuck to audit.
			 */
			करो_set_cpus_allowed(p, cpu_possible_mask);
			state = fail;
			अवरोध;

		हाल fail:
			BUG();
			अवरोध;
		पूर्ण
	पूर्ण

out:
	अगर (state != cpuset) अणु
		/*
		 * Don't tell them about moving निकासing tasks or
		 * kernel thपढ़ोs (both mm शून्य), since they never
		 * leave kernel.
		 */
		अगर (p->mm && prपूर्णांकk_ratelimit()) अणु
			prपूर्णांकk_deferred("process %d (%s) no longer affine to cpu%d\n",
					task_pid_nr(p), p->comm, cpu);
		पूर्ण
	पूर्ण

	वापस dest_cpu;
पूर्ण

/*
 * The caller (विभाजन, wakeup) owns p->pi_lock, ->cpus_ptr is stable.
 */
अटल अंतरभूत
पूर्णांक select_task_rq(काष्ठा task_काष्ठा *p, पूर्णांक cpu, पूर्णांक wake_flags)
अणु
	lockdep_निश्चित_held(&p->pi_lock);

	अगर (p->nr_cpus_allowed > 1 && !is_migration_disabled(p))
		cpu = p->sched_class->select_task_rq(p, cpu, wake_flags);
	अन्यथा
		cpu = cpumask_any(p->cpus_ptr);

	/*
	 * In order not to call set_task_cpu() on a blocking task we need
	 * to rely on ttwu() to place the task on a valid ->cpus_ptr
	 * CPU.
	 *
	 * Since this is common to all placement strategies, this lives here.
	 *
	 * [ this allows ->select_task() to simply वापस task_cpu(p) and
	 *   not worry about this generic स्थिरraपूर्णांक ]
	 */
	अगर (unlikely(!is_cpu_allowed(p, cpu)))
		cpu = select_fallback_rq(task_cpu(p), p);

	वापस cpu;
पूर्ण

व्योम sched_set_stop_task(पूर्णांक cpu, काष्ठा task_काष्ठा *stop)
अणु
	अटल काष्ठा lock_class_key stop_pi_lock;
	काष्ठा sched_param param = अणु .sched_priority = MAX_RT_PRIO - 1 पूर्ण;
	काष्ठा task_काष्ठा *old_stop = cpu_rq(cpu)->stop;

	अगर (stop) अणु
		/*
		 * Make it appear like a SCHED_FIFO task, its something
		 * userspace knows about and won't get confused about.
		 *
		 * Also, it will make PI more or less work without too
		 * much confusion -- but then, stop work should not
		 * rely on PI working anyway.
		 */
		sched_setscheduler_nocheck(stop, SCHED_FIFO, &param);

		stop->sched_class = &stop_sched_class;

		/*
		 * The PI code calls rt_mutex_setprio() with ->pi_lock held to
		 * adjust the effective priority of a task. As a result,
		 * rt_mutex_setprio() can trigger (RT) balancing operations,
		 * which can then trigger wakeups of the stop thपढ़ो to push
		 * around the current task.
		 *
		 * The stop task itself will never be part of the PI-chain, it
		 * never blocks, thereक्रमe that ->pi_lock recursion is safe.
		 * Tell lockdep about this by placing the stop->pi_lock in its
		 * own class.
		 */
		lockdep_set_class(&stop->pi_lock, &stop_pi_lock);
	पूर्ण

	cpu_rq(cpu)->stop = stop;

	अगर (old_stop) अणु
		/*
		 * Reset it back to a normal scheduling class so that
		 * it can die in pieces.
		 */
		old_stop->sched_class = &rt_sched_class;
	पूर्ण
पूर्ण

#अन्यथा /* CONFIG_SMP */

अटल अंतरभूत पूर्णांक __set_cpus_allowed_ptr(काष्ठा task_काष्ठा *p,
					 स्थिर काष्ठा cpumask *new_mask,
					 u32 flags)
अणु
	वापस set_cpus_allowed_ptr(p, new_mask);
पूर्ण

अटल अंतरभूत व्योम migrate_disable_चयन(काष्ठा rq *rq, काष्ठा task_काष्ठा *p) अणु पूर्ण

अटल अंतरभूत bool rq_has_pinned_tasks(काष्ठा rq *rq)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर /* !CONFIG_SMP */

अटल व्योम
ttwu_stat(काष्ठा task_काष्ठा *p, पूर्णांक cpu, पूर्णांक wake_flags)
अणु
	काष्ठा rq *rq;

	अगर (!schedstat_enabled())
		वापस;

	rq = this_rq();

#अगर_घोषित CONFIG_SMP
	अगर (cpu == rq->cpu) अणु
		__schedstat_inc(rq->ttwu_local);
		__schedstat_inc(p->se.statistics.nr_wakeups_local);
	पूर्ण अन्यथा अणु
		काष्ठा sched_करोमुख्य *sd;

		__schedstat_inc(p->se.statistics.nr_wakeups_remote);
		rcu_पढ़ो_lock();
		क्रम_each_करोमुख्य(rq->cpu, sd) अणु
			अगर (cpumask_test_cpu(cpu, sched_करोमुख्य_span(sd))) अणु
				__schedstat_inc(sd->ttwu_wake_remote);
				अवरोध;
			पूर्ण
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	अगर (wake_flags & WF_MIGRATED)
		__schedstat_inc(p->se.statistics.nr_wakeups_migrate);
#पूर्ण_अगर /* CONFIG_SMP */

	__schedstat_inc(rq->ttwu_count);
	__schedstat_inc(p->se.statistics.nr_wakeups);

	अगर (wake_flags & WF_SYNC)
		__schedstat_inc(p->se.statistics.nr_wakeups_sync);
पूर्ण

/*
 * Mark the task runnable and perक्रमm wakeup-preemption.
 */
अटल व्योम ttwu_करो_wakeup(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक wake_flags,
			   काष्ठा rq_flags *rf)
अणु
	check_preempt_curr(rq, p, wake_flags);
	p->state = TASK_RUNNING;
	trace_sched_wakeup(p);

#अगर_घोषित CONFIG_SMP
	अगर (p->sched_class->task_woken) अणु
		/*
		 * Our task @p is fully woken up and running; so it's safe to
		 * drop the rq->lock, hereafter rq is only used क्रम statistics.
		 */
		rq_unpin_lock(rq, rf);
		p->sched_class->task_woken(rq, p);
		rq_repin_lock(rq, rf);
	पूर्ण

	अगर (rq->idle_stamp) अणु
		u64 delta = rq_घड़ी(rq) - rq->idle_stamp;
		u64 max = 2*rq->max_idle_balance_cost;

		update_avg(&rq->avg_idle, delta);

		अगर (rq->avg_idle > max)
			rq->avg_idle = max;

		rq->idle_stamp = 0;
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम
ttwu_करो_activate(काष्ठा rq *rq, काष्ठा task_काष्ठा *p, पूर्णांक wake_flags,
		 काष्ठा rq_flags *rf)
अणु
	पूर्णांक en_flags = ENQUEUE_WAKEUP | ENQUEUE_NOCLOCK;

	lockdep_निश्चित_held(&rq->lock);

	अगर (p->sched_contributes_to_load)
		rq->nr_unपूर्णांकerruptible--;

#अगर_घोषित CONFIG_SMP
	अगर (wake_flags & WF_MIGRATED)
		en_flags |= ENQUEUE_MIGRATED;
	अन्यथा
#पूर्ण_अगर
	अगर (p->in_ioरुको) अणु
		delayacct_blkio_end(p);
		atomic_dec(&task_rq(p)->nr_ioरुको);
	पूर्ण

	activate_task(rq, p, en_flags);
	ttwu_करो_wakeup(rq, p, wake_flags, rf);
पूर्ण

/*
 * Consider @p being inside a रुको loop:
 *
 *   क्रम (;;) अणु
 *      set_current_state(TASK_UNINTERRUPTIBLE);
 *
 *      अगर (CONDITION)
 *         अवरोध;
 *
 *      schedule();
 *   पूर्ण
 *   __set_current_state(TASK_RUNNING);
 *
 * between set_current_state() and schedule(). In this हाल @p is still
 * runnable, so all that needs करोing is change p->state back to TASK_RUNNING in
 * an atomic manner.
 *
 * By taking task_rq(p)->lock we serialize against schedule(), अगर @p->on_rq
 * then schedule() must still happen and p->state can be changed to
 * TASK_RUNNING. Otherwise we lost the race, schedule() has happened, and we
 * need to करो a full wakeup with enqueue.
 *
 * Returns: %true when the wakeup is करोne,
 *          %false otherwise.
 */
अटल पूर्णांक ttwu_runnable(काष्ठा task_काष्ठा *p, पूर्णांक wake_flags)
अणु
	काष्ठा rq_flags rf;
	काष्ठा rq *rq;
	पूर्णांक ret = 0;

	rq = __task_rq_lock(p, &rf);
	अगर (task_on_rq_queued(p)) अणु
		/* check_preempt_curr() may use rq घड़ी */
		update_rq_घड़ी(rq);
		ttwu_करो_wakeup(rq, p, wake_flags, &rf);
		ret = 1;
	पूर्ण
	__task_rq_unlock(rq, &rf);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_SMP
व्योम sched_ttwu_pending(व्योम *arg)
अणु
	काष्ठा llist_node *llist = arg;
	काष्ठा rq *rq = this_rq();
	काष्ठा task_काष्ठा *p, *t;
	काष्ठा rq_flags rf;

	अगर (!llist)
		वापस;

	/*
	 * rq::ttwu_pending racy indication of out-standing wakeups.
	 * Races such that false-negatives are possible, since they
	 * are लघुer lived that false-positives would be.
	 */
	WRITE_ONCE(rq->ttwu_pending, 0);

	rq_lock_irqsave(rq, &rf);
	update_rq_घड़ी(rq);

	llist_क्रम_each_entry_safe(p, t, llist, wake_entry.llist) अणु
		अगर (WARN_ON_ONCE(p->on_cpu))
			smp_cond_load_acquire(&p->on_cpu, !VAL);

		अगर (WARN_ON_ONCE(task_cpu(p) != cpu_of(rq)))
			set_task_cpu(p, cpu_of(rq));

		ttwu_करो_activate(rq, p, p->sched_remote_wakeup ? WF_MIGRATED : 0, &rf);
	पूर्ण

	rq_unlock_irqrestore(rq, &rf);
पूर्ण

व्योम send_call_function_single_ipi(पूर्णांक cpu)
अणु
	काष्ठा rq *rq = cpu_rq(cpu);

	अगर (!set_nr_अगर_polling(rq->idle))
		arch_send_call_function_single_ipi(cpu);
	अन्यथा
		trace_sched_wake_idle_without_ipi(cpu);
पूर्ण

/*
 * Queue a task on the target CPUs wake_list and wake the CPU via IPI अगर
 * necessary. The wakee CPU on receipt of the IPI will queue the task
 * via sched_ttwu_wakeup() क्रम activation so the wakee incurs the cost
 * of the wakeup instead of the waker.
 */
अटल व्योम __ttwu_queue_wakelist(काष्ठा task_काष्ठा *p, पूर्णांक cpu, पूर्णांक wake_flags)
अणु
	काष्ठा rq *rq = cpu_rq(cpu);

	p->sched_remote_wakeup = !!(wake_flags & WF_MIGRATED);

	WRITE_ONCE(rq->ttwu_pending, 1);
	__smp_call_single_queue(cpu, &p->wake_entry.llist);
पूर्ण

व्योम wake_up_अगर_idle(पूर्णांक cpu)
अणु
	काष्ठा rq *rq = cpu_rq(cpu);
	काष्ठा rq_flags rf;

	rcu_पढ़ो_lock();

	अगर (!is_idle_task(rcu_dereference(rq->curr)))
		जाओ out;

	अगर (set_nr_अगर_polling(rq->idle)) अणु
		trace_sched_wake_idle_without_ipi(cpu);
	पूर्ण अन्यथा अणु
		rq_lock_irqsave(rq, &rf);
		अगर (is_idle_task(rq->curr))
			smp_send_reschedule(cpu);
		/* Else CPU is not idle, करो nothing here: */
		rq_unlock_irqrestore(rq, &rf);
	पूर्ण

out:
	rcu_पढ़ो_unlock();
पूर्ण

bool cpus_share_cache(पूर्णांक this_cpu, पूर्णांक that_cpu)
अणु
	वापस per_cpu(sd_llc_id, this_cpu) == per_cpu(sd_llc_id, that_cpu);
पूर्ण

अटल अंतरभूत bool ttwu_queue_cond(पूर्णांक cpu, पूर्णांक wake_flags)
अणु
	/*
	 * Do not complicate things with the async wake_list जबतक the CPU is
	 * in hotplug state.
	 */
	अगर (!cpu_active(cpu))
		वापस false;

	/*
	 * If the CPU करोes not share cache, then queue the task on the
	 * remote rqs wakelist to aव्योम accessing remote data.
	 */
	अगर (!cpus_share_cache(smp_processor_id(), cpu))
		वापस true;

	/*
	 * If the task is descheduling and the only running task on the
	 * CPU then use the wakelist to offload the task activation to
	 * the soon-to-be-idle CPU as the current CPU is likely busy.
	 * nr_running is checked to aव्योम unnecessary task stacking.
	 */
	अगर ((wake_flags & WF_ON_CPU) && cpu_rq(cpu)->nr_running <= 1)
		वापस true;

	वापस false;
पूर्ण

अटल bool ttwu_queue_wakelist(काष्ठा task_काष्ठा *p, पूर्णांक cpu, पूर्णांक wake_flags)
अणु
	अगर (sched_feat(TTWU_QUEUE) && ttwu_queue_cond(cpu, wake_flags)) अणु
		अगर (WARN_ON_ONCE(cpu == smp_processor_id()))
			वापस false;

		sched_घड़ी_cpu(cpu); /* Sync घड़ीs across CPUs */
		__ttwu_queue_wakelist(p, cpu, wake_flags);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

#अन्यथा /* !CONFIG_SMP */

अटल अंतरभूत bool ttwu_queue_wakelist(काष्ठा task_काष्ठा *p, पूर्णांक cpu, पूर्णांक wake_flags)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर /* CONFIG_SMP */

अटल व्योम ttwu_queue(काष्ठा task_काष्ठा *p, पूर्णांक cpu, पूर्णांक wake_flags)
अणु
	काष्ठा rq *rq = cpu_rq(cpu);
	काष्ठा rq_flags rf;

	अगर (ttwu_queue_wakelist(p, cpu, wake_flags))
		वापस;

	rq_lock(rq, &rf);
	update_rq_घड़ी(rq);
	ttwu_करो_activate(rq, p, wake_flags, &rf);
	rq_unlock(rq, &rf);
पूर्ण

/*
 * Notes on Program-Order guarantees on SMP प्रणालीs.
 *
 *  MIGRATION
 *
 * The basic program-order guarantee on SMP प्रणालीs is that when a task [t]
 * migrates, all its activity on its old CPU [c0] happens-beक्रमe any subsequent
 * execution on its new CPU [c1].
 *
 * For migration (of runnable tasks) this is provided by the following means:
 *
 *  A) UNLOCK of the rq(c0)->lock scheduling out task t
 *  B) migration क्रम t is required to synchronize *both* rq(c0)->lock and
 *     rq(c1)->lock (अगर not at the same समय, then in that order).
 *  C) LOCK of the rq(c1)->lock scheduling in task
 *
 * Release/acquire chaining guarantees that B happens after A and C after B.
 * Note: the CPU करोing B need not be c0 or c1
 *
 * Example:
 *
 *   CPU0            CPU1            CPU2
 *
 *   LOCK rq(0)->lock
 *   sched-out X
 *   sched-in Y
 *   UNLOCK rq(0)->lock
 *
 *                                   LOCK rq(0)->lock // orders against CPU0
 *                                   dequeue X
 *                                   UNLOCK rq(0)->lock
 *
 *                                   LOCK rq(1)->lock
 *                                   enqueue X
 *                                   UNLOCK rq(1)->lock
 *
 *                   LOCK rq(1)->lock // orders against CPU2
 *                   sched-out Z
 *                   sched-in X
 *                   UNLOCK rq(1)->lock
 *
 *
 *  BLOCKING -- aka. SLEEP + WAKEUP
 *
 * For blocking we (obviously) need to provide the same guarantee as क्रम
 * migration. However the means are completely dअगरferent as there is no lock
 * chain to provide order. Instead we करो:
 *
 *   1) smp_store_release(X->on_cpu, 0)   -- finish_task()
 *   2) smp_cond_load_acquire(!X->on_cpu) -- try_to_wake_up()
 *
 * Example:
 *
 *   CPU0 (schedule)  CPU1 (try_to_wake_up) CPU2 (schedule)
 *
 *   LOCK rq(0)->lock LOCK X->pi_lock
 *   dequeue X
 *   sched-out X
 *   smp_store_release(X->on_cpu, 0);
 *
 *                    smp_cond_load_acquire(&X->on_cpu, !VAL);
 *                    X->state = WAKING
 *                    set_task_cpu(X,2)
 *
 *                    LOCK rq(2)->lock
 *                    enqueue X
 *                    X->state = RUNNING
 *                    UNLOCK rq(2)->lock
 *
 *                                          LOCK rq(2)->lock // orders against CPU1
 *                                          sched-out Z
 *                                          sched-in X
 *                                          UNLOCK rq(2)->lock
 *
 *                    UNLOCK X->pi_lock
 *   UNLOCK rq(0)->lock
 *
 *
 * However, क्रम wakeups there is a second guarantee we must provide, namely we
 * must ensure that CONDITION=1 करोne by the caller can not be reordered with
 * accesses to the task state; see try_to_wake_up() and set_current_state().
 */

/**
 * try_to_wake_up - wake up a thपढ़ो
 * @p: the thपढ़ो to be awakened
 * @state: the mask of task states that can be woken
 * @wake_flags: wake modअगरier flags (WF_*)
 *
 * Conceptually करोes:
 *
 *   If (@state & @p->state) @p->state = TASK_RUNNING.
 *
 * If the task was not queued/runnable, also place it back on a runqueue.
 *
 * This function is atomic against schedule() which would dequeue the task.
 *
 * It issues a full memory barrier beक्रमe accessing @p->state, see the comment
 * with set_current_state().
 *
 * Uses p->pi_lock to serialize against concurrent wake-ups.
 *
 * Relies on p->pi_lock stabilizing:
 *  - p->sched_class
 *  - p->cpus_ptr
 *  - p->sched_task_group
 * in order to करो migration, see its use of select_task_rq()/set_task_cpu().
 *
 * Tries really hard to only take one task_rq(p)->lock क्रम perक्रमmance.
 * Takes rq->lock in:
 *  - ttwu_runnable()    -- old rq, unaव्योमable, see comment there;
 *  - ttwu_queue()       -- new rq, क्रम enqueue of the task;
 *  - psi_ttwu_dequeue() -- much sadness :-( accounting will समाप्त us.
 *
 * As a consequence we race really badly with just about everything. See the
 * many memory barriers and their comments क्रम details.
 *
 * Return: %true अगर @p->state changes (an actual wakeup was करोne),
 *	   %false otherwise.
 */
अटल पूर्णांक
try_to_wake_up(काष्ठा task_काष्ठा *p, अचिन्हित पूर्णांक state, पूर्णांक wake_flags)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक cpu, success = 0;

	preempt_disable();
	अगर (p == current) अणु
		/*
		 * We're waking current, this means 'p->on_rq' and 'task_cpu(p)
		 * == smp_processor_id()'. Together this means we can special
		 * हाल the whole 'p->on_rq && ttwu_runnable()' हाल below
		 * without taking any locks.
		 *
		 * In particular:
		 *  - we rely on Program-Order guarantees क्रम all the ordering,
		 *  - we're serialized against set_special_state() by virtue of
		 *    it disabling IRQs (this allows not taking ->pi_lock).
		 */
		अगर (!(p->state & state))
			जाओ out;

		success = 1;
		trace_sched_waking(p);
		p->state = TASK_RUNNING;
		trace_sched_wakeup(p);
		जाओ out;
	पूर्ण

	/*
	 * If we are going to wake up a thपढ़ो रुकोing क्रम CONDITION we
	 * need to ensure that CONDITION=1 करोne by the caller can not be
	 * reordered with p->state check below. This pairs with smp_store_mb()
	 * in set_current_state() that the रुकोing thपढ़ो करोes.
	 */
	raw_spin_lock_irqsave(&p->pi_lock, flags);
	smp_mb__after_spinlock();
	अगर (!(p->state & state))
		जाओ unlock;

	trace_sched_waking(p);

	/* We're going to change ->state: */
	success = 1;

	/*
	 * Ensure we load p->on_rq _after_ p->state, otherwise it would
	 * be possible to, falsely, observe p->on_rq == 0 and get stuck
	 * in smp_cond_load_acquire() below.
	 *
	 * sched_ttwu_pending()			try_to_wake_up()
	 *   STORE p->on_rq = 1			  LOAD p->state
	 *   UNLOCK rq->lock
	 *
	 * __schedule() (चयन to task 'p')
	 *   LOCK rq->lock			  smp_rmb();
	 *   smp_mb__after_spinlock();
	 *   UNLOCK rq->lock
	 *
	 * [task p]
	 *   STORE p->state = UNINTERRUPTIBLE	  LOAD p->on_rq
	 *
	 * Pairs with the LOCK+smp_mb__after_spinlock() on rq->lock in
	 * __schedule().  See the comment क्रम smp_mb__after_spinlock().
	 *
	 * A similar smb_rmb() lives in try_invoke_on_locked_करोwn_task().
	 */
	smp_rmb();
	अगर (READ_ONCE(p->on_rq) && ttwu_runnable(p, wake_flags))
		जाओ unlock;

#अगर_घोषित CONFIG_SMP
	/*
	 * Ensure we load p->on_cpu _after_ p->on_rq, otherwise it would be
	 * possible to, falsely, observe p->on_cpu == 0.
	 *
	 * One must be running (->on_cpu == 1) in order to हटाओ oneself
	 * from the runqueue.
	 *
	 * __schedule() (चयन to task 'p')	try_to_wake_up()
	 *   STORE p->on_cpu = 1		  LOAD p->on_rq
	 *   UNLOCK rq->lock
	 *
	 * __schedule() (put 'p' to sleep)
	 *   LOCK rq->lock			  smp_rmb();
	 *   smp_mb__after_spinlock();
	 *   STORE p->on_rq = 0			  LOAD p->on_cpu
	 *
	 * Pairs with the LOCK+smp_mb__after_spinlock() on rq->lock in
	 * __schedule().  See the comment क्रम smp_mb__after_spinlock().
	 *
	 * Form a control-dep-acquire with p->on_rq == 0 above, to ensure
	 * schedule()'s deactivate_task() has 'happened' and p will no दीर्घer
	 * care about it's own p->state. See the comment in __schedule().
	 */
	smp_acquire__after_ctrl_dep();

	/*
	 * We're करोing the wakeup (@success == 1), they did a dequeue (p->on_rq
	 * == 0), which means we need to करो an enqueue, change p->state to
	 * TASK_WAKING such that we can unlock p->pi_lock beक्रमe करोing the
	 * enqueue, such as ttwu_queue_wakelist().
	 */
	p->state = TASK_WAKING;

	/*
	 * If the owning (remote) CPU is still in the middle of schedule() with
	 * this task as prev, considering queueing p on the remote CPUs wake_list
	 * which potentially sends an IPI instead of spinning on p->on_cpu to
	 * let the waker make क्रमward progress. This is safe because IRQs are
	 * disabled and the IPI will deliver after on_cpu is cleared.
	 *
	 * Ensure we load task_cpu(p) after p->on_cpu:
	 *
	 * set_task_cpu(p, cpu);
	 *   STORE p->cpu = @cpu
	 * __schedule() (चयन to task 'p')
	 *   LOCK rq->lock
	 *   smp_mb__after_spin_lock()		smp_cond_load_acquire(&p->on_cpu)
	 *   STORE p->on_cpu = 1		LOAD p->cpu
	 *
	 * to ensure we observe the correct CPU on which the task is currently
	 * scheduling.
	 */
	अगर (smp_load_acquire(&p->on_cpu) &&
	    ttwu_queue_wakelist(p, task_cpu(p), wake_flags | WF_ON_CPU))
		जाओ unlock;

	/*
	 * If the owning (remote) CPU is still in the middle of schedule() with
	 * this task as prev, रुको until it's करोne referencing the task.
	 *
	 * Pairs with the smp_store_release() in finish_task().
	 *
	 * This ensures that tasks getting woken will be fully ordered against
	 * their previous state and preserve Program Order.
	 */
	smp_cond_load_acquire(&p->on_cpu, !VAL);

	cpu = select_task_rq(p, p->wake_cpu, wake_flags | WF_TTWU);
	अगर (task_cpu(p) != cpu) अणु
		अगर (p->in_ioरुको) अणु
			delayacct_blkio_end(p);
			atomic_dec(&task_rq(p)->nr_ioरुको);
		पूर्ण

		wake_flags |= WF_MIGRATED;
		psi_ttwu_dequeue(p);
		set_task_cpu(p, cpu);
	पूर्ण
#अन्यथा
	cpu = task_cpu(p);
#पूर्ण_अगर /* CONFIG_SMP */

	ttwu_queue(p, cpu, wake_flags);
unlock:
	raw_spin_unlock_irqrestore(&p->pi_lock, flags);
out:
	अगर (success)
		ttwu_stat(p, task_cpu(p), wake_flags);
	preempt_enable();

	वापस success;
पूर्ण

/**
 * try_invoke_on_locked_करोwn_task - Invoke a function on task in fixed state
 * @p: Process क्रम which the function is to be invoked, can be @current.
 * @func: Function to invoke.
 * @arg: Argument to function.
 *
 * If the specअगरied task can be quickly locked पूर्णांकo a definite state
 * (either sleeping or on a given runqueue), arrange to keep it in that
 * state जबतक invoking @func(@arg).  This function can use ->on_rq and
 * task_curr() to work out what the state is, अगर required.  Given that
 * @func can be invoked with a runqueue lock held, it had better be quite
 * lightweight.
 *
 * Returns:
 *	@false अगर the task slipped out from under the locks.
 *	@true अगर the task was locked onto a runqueue or is sleeping.
 *		However, @func can override this by वापसing @false.
 */
bool try_invoke_on_locked_करोwn_task(काष्ठा task_काष्ठा *p, bool (*func)(काष्ठा task_काष्ठा *t, व्योम *arg), व्योम *arg)
अणु
	काष्ठा rq_flags rf;
	bool ret = false;
	काष्ठा rq *rq;

	raw_spin_lock_irqsave(&p->pi_lock, rf.flags);
	अगर (p->on_rq) अणु
		rq = __task_rq_lock(p, &rf);
		अगर (task_rq(p) == rq)
			ret = func(p, arg);
		rq_unlock(rq, &rf);
	पूर्ण अन्यथा अणु
		चयन (p->state) अणु
		हाल TASK_RUNNING:
		हाल TASK_WAKING:
			अवरोध;
		शेष:
			smp_rmb(); // See smp_rmb() comment in try_to_wake_up().
			अगर (!p->on_rq)
				ret = func(p, arg);
		पूर्ण
	पूर्ण
	raw_spin_unlock_irqrestore(&p->pi_lock, rf.flags);
	वापस ret;
पूर्ण

/**
 * wake_up_process - Wake up a specअगरic process
 * @p: The process to be woken up.
 *
 * Attempt to wake up the nominated process and move it to the set of runnable
 * processes.
 *
 * Return: 1 अगर the process was woken up, 0 अगर it was alपढ़ोy running.
 *
 * This function executes a full memory barrier beक्रमe accessing the task state.
 */
पूर्णांक wake_up_process(काष्ठा task_काष्ठा *p)
अणु
	वापस try_to_wake_up(p, TASK_NORMAL, 0);
पूर्ण
EXPORT_SYMBOL(wake_up_process);

पूर्णांक wake_up_state(काष्ठा task_काष्ठा *p, अचिन्हित पूर्णांक state)
अणु
	वापस try_to_wake_up(p, state, 0);
पूर्ण

/*
 * Perक्रमm scheduler related setup क्रम a newly विभाजनed process p.
 * p is विभाजनed by current.
 *
 * __sched_विभाजन() is basic setup used by init_idle() too:
 */
अटल व्योम __sched_विभाजन(अचिन्हित दीर्घ clone_flags, काष्ठा task_काष्ठा *p)
अणु
	p->on_rq			= 0;

	p->se.on_rq			= 0;
	p->se.exec_start		= 0;
	p->se.sum_exec_runसमय		= 0;
	p->se.prev_sum_exec_runसमय	= 0;
	p->se.nr_migrations		= 0;
	p->se.vrunसमय			= 0;
	INIT_LIST_HEAD(&p->se.group_node);

#अगर_घोषित CONFIG_FAIR_GROUP_SCHED
	p->se.cfs_rq			= शून्य;
#पूर्ण_अगर

#अगर_घोषित CONFIG_SCHEDSTATS
	/* Even अगर schedstat is disabled, there should not be garbage */
	स_रखो(&p->se.statistics, 0, माप(p->se.statistics));
#पूर्ण_अगर

	RB_CLEAR_NODE(&p->dl.rb_node);
	init_dl_task_समयr(&p->dl);
	init_dl_inactive_task_समयr(&p->dl);
	__dl_clear_params(p);

	INIT_LIST_HEAD(&p->rt.run_list);
	p->rt.समयout		= 0;
	p->rt.समय_slice	= sched_rr_बारlice;
	p->rt.on_rq		= 0;
	p->rt.on_list		= 0;

#अगर_घोषित CONFIG_PREEMPT_NOTIFIERS
	INIT_HLIST_HEAD(&p->preempt_notअगरiers);
#पूर्ण_अगर

#अगर_घोषित CONFIG_COMPACTION
	p->capture_control = शून्य;
#पूर्ण_अगर
	init_numa_balancing(clone_flags, p);
#अगर_घोषित CONFIG_SMP
	p->wake_entry.u_flags = CSD_TYPE_TTWU;
	p->migration_pending = शून्य;
#पूर्ण_अगर
पूर्ण

DEFINE_STATIC_KEY_FALSE(sched_numa_balancing);

#अगर_घोषित CONFIG_NUMA_BALANCING

व्योम set_numabalancing_state(bool enabled)
अणु
	अगर (enabled)
		अटल_branch_enable(&sched_numa_balancing);
	अन्यथा
		अटल_branch_disable(&sched_numa_balancing);
पूर्ण

#अगर_घोषित CONFIG_PROC_SYSCTL
पूर्णांक sysctl_numa_balancing(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			  व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा ctl_table t;
	पूर्णांक err;
	पूर्णांक state = अटल_branch_likely(&sched_numa_balancing);

	अगर (ग_लिखो && !capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	t = *table;
	t.data = &state;
	err = proc_करोपूर्णांकvec_minmax(&t, ग_लिखो, buffer, lenp, ppos);
	अगर (err < 0)
		वापस err;
	अगर (ग_लिखो)
		set_numabalancing_state(state);
	वापस err;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_SCHEDSTATS

DEFINE_STATIC_KEY_FALSE(sched_schedstats);
अटल bool __initdata __sched_schedstats = false;

अटल व्योम set_schedstats(bool enabled)
अणु
	अगर (enabled)
		अटल_branch_enable(&sched_schedstats);
	अन्यथा
		अटल_branch_disable(&sched_schedstats);
पूर्ण

व्योम क्रमce_schedstat_enabled(व्योम)
अणु
	अगर (!schedstat_enabled()) अणु
		pr_info("kernel profiling enabled schedstats, disable via kernel.sched_schedstats.\n");
		अटल_branch_enable(&sched_schedstats);
	पूर्ण
पूर्ण

अटल पूर्णांक __init setup_schedstats(अक्षर *str)
अणु
	पूर्णांक ret = 0;
	अगर (!str)
		जाओ out;

	/*
	 * This code is called beक्रमe jump labels have been set up, so we can't
	 * change the अटल branch directly just yet.  Instead set a temporary
	 * variable so init_schedstats() can करो it later.
	 */
	अगर (!म_भेद(str, "enable")) अणु
		__sched_schedstats = true;
		ret = 1;
	पूर्ण अन्यथा अगर (!म_भेद(str, "disable")) अणु
		__sched_schedstats = false;
		ret = 1;
	पूर्ण
out:
	अगर (!ret)
		pr_warn("Unable to parse schedstats=\n");

	वापस ret;
पूर्ण
__setup("schedstats=", setup_schedstats);

अटल व्योम __init init_schedstats(व्योम)
अणु
	set_schedstats(__sched_schedstats);
पूर्ण

#अगर_घोषित CONFIG_PROC_SYSCTL
पूर्णांक sysctl_schedstats(काष्ठा ctl_table *table, पूर्णांक ग_लिखो, व्योम *buffer,
		माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा ctl_table t;
	पूर्णांक err;
	पूर्णांक state = अटल_branch_likely(&sched_schedstats);

	अगर (ग_लिखो && !capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	t = *table;
	t.data = &state;
	err = proc_करोपूर्णांकvec_minmax(&t, ग_लिखो, buffer, lenp, ppos);
	अगर (err < 0)
		वापस err;
	अगर (ग_लिखो)
		set_schedstats(state);
	वापस err;
पूर्ण
#पूर्ण_अगर /* CONFIG_PROC_SYSCTL */
#अन्यथा  /* !CONFIG_SCHEDSTATS */
अटल अंतरभूत व्योम init_schedstats(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_SCHEDSTATS */

/*
 * विभाजन()/clone()-समय setup:
 */
पूर्णांक sched_विभाजन(अचिन्हित दीर्घ clone_flags, काष्ठा task_काष्ठा *p)
अणु
	अचिन्हित दीर्घ flags;

	__sched_विभाजन(clone_flags, p);
	/*
	 * We mark the process as NEW here. This guarantees that
	 * nobody will actually run it, and a संकेत or other बाह्यal
	 * event cannot wake it up and insert it on the runqueue either.
	 */
	p->state = TASK_NEW;

	/*
	 * Make sure we करो not leak PI boosting priority to the child.
	 */
	p->prio = current->normal_prio;

	uclamp_विभाजन(p);

	/*
	 * Revert to शेष priority/policy on विभाजन अगर requested.
	 */
	अगर (unlikely(p->sched_reset_on_विभाजन)) अणु
		अगर (task_has_dl_policy(p) || task_has_rt_policy(p)) अणु
			p->policy = SCHED_NORMAL;
			p->अटल_prio = NICE_TO_PRIO(0);
			p->rt_priority = 0;
		पूर्ण अन्यथा अगर (PRIO_TO_NICE(p->अटल_prio) < 0)
			p->अटल_prio = NICE_TO_PRIO(0);

		p->prio = p->normal_prio = __normal_prio(p);
		set_load_weight(p, false);

		/*
		 * We करोn't need the reset flag anymore after the विभाजन. It has
		 * fulfilled its duty:
		 */
		p->sched_reset_on_विभाजन = 0;
	पूर्ण

	अगर (dl_prio(p->prio))
		वापस -EAGAIN;
	अन्यथा अगर (rt_prio(p->prio))
		p->sched_class = &rt_sched_class;
	अन्यथा
		p->sched_class = &fair_sched_class;

	init_entity_runnable_average(&p->se);

	/*
	 * The child is not yet in the pid-hash so no cgroup attach races,
	 * and the cgroup is pinned to this child due to cgroup_विभाजन()
	 * is ran beक्रमe sched_विभाजन().
	 *
	 * Silence PROVE_RCU.
	 */
	raw_spin_lock_irqsave(&p->pi_lock, flags);
	rseq_migrate(p);
	/*
	 * We're setting the CPU for the first time, we don't migrate,
	 * so use __set_task_cpu().
	 */
	__set_task_cpu(p, smp_processor_id());
	अगर (p->sched_class->task_विभाजन)
		p->sched_class->task_विभाजन(p);
	raw_spin_unlock_irqrestore(&p->pi_lock, flags);

#अगर_घोषित CONFIG_SCHED_INFO
	अगर (likely(sched_info_on()))
		स_रखो(&p->sched_info, 0, माप(p->sched_info));
#पूर्ण_अगर
#अगर defined(CONFIG_SMP)
	p->on_cpu = 0;
#पूर्ण_अगर
	init_task_preempt_count(p);
#अगर_घोषित CONFIG_SMP
	plist_node_init(&p->pushable_tasks, MAX_PRIO);
	RB_CLEAR_NODE(&p->pushable_dl_tasks);
#पूर्ण_अगर
	वापस 0;
पूर्ण

व्योम sched_post_विभाजन(काष्ठा task_काष्ठा *p)
अणु
	uclamp_post_विभाजन(p);
पूर्ण

अचिन्हित दीर्घ to_ratio(u64 period, u64 runसमय)
अणु
	अगर (runसमय == RUNTIME_INF)
		वापस BW_UNIT;

	/*
	 * Doing this here saves a lot of checks in all
	 * the calling paths, and वापसing zero seems
	 * safe क्रम them anyway.
	 */
	अगर (period == 0)
		वापस 0;

	वापस भाग64_u64(runसमय << BW_SHIFT, period);
पूर्ण

/*
 * wake_up_new_task - wake up a newly created task क्रम the first समय.
 *
 * This function will करो some initial scheduler statistics housekeeping
 * that must be करोne क्रम every newly created context, then माला_दो the task
 * on the runqueue and wakes it.
 */
व्योम wake_up_new_task(काष्ठा task_काष्ठा *p)
अणु
	काष्ठा rq_flags rf;
	काष्ठा rq *rq;

	raw_spin_lock_irqsave(&p->pi_lock, rf.flags);
	p->state = TASK_RUNNING;
#अगर_घोषित CONFIG_SMP
	/*
	 * Fork balancing, करो it here and not earlier because:
	 *  - cpus_ptr can change in the विभाजन path
	 *  - any previously selected CPU might disappear through hotplug
	 *
	 * Use __set_task_cpu() to aव्योम calling sched_class::migrate_task_rq,
	 * as we're not fully set-up yet.
	 */
	p->recent_used_cpu = task_cpu(p);
	rseq_migrate(p);
	__set_task_cpu(p, select_task_rq(p, task_cpu(p), WF_FORK));
#पूर्ण_अगर
	rq = __task_rq_lock(p, &rf);
	update_rq_घड़ी(rq);
	post_init_entity_util_avg(p);

	activate_task(rq, p, ENQUEUE_NOCLOCK);
	trace_sched_wakeup_new(p);
	check_preempt_curr(rq, p, WF_FORK);
#अगर_घोषित CONFIG_SMP
	अगर (p->sched_class->task_woken) अणु
		/*
		 * Nothing relies on rq->lock after this, so it's fine to
		 * drop it.
		 */
		rq_unpin_lock(rq, &rf);
		p->sched_class->task_woken(rq, p);
		rq_repin_lock(rq, &rf);
	पूर्ण
#पूर्ण_अगर
	task_rq_unlock(rq, p, &rf);
पूर्ण

#अगर_घोषित CONFIG_PREEMPT_NOTIFIERS

अटल DEFINE_STATIC_KEY_FALSE(preempt_notअगरier_key);

व्योम preempt_notअगरier_inc(व्योम)
अणु
	अटल_branch_inc(&preempt_notअगरier_key);
पूर्ण
EXPORT_SYMBOL_GPL(preempt_notअगरier_inc);

व्योम preempt_notअगरier_dec(व्योम)
अणु
	अटल_branch_dec(&preempt_notअगरier_key);
पूर्ण
EXPORT_SYMBOL_GPL(preempt_notअगरier_dec);

/**
 * preempt_notअगरier_रेजिस्टर - tell me when current is being preempted & rescheduled
 * @notअगरier: notअगरier काष्ठा to रेजिस्टर
 */
व्योम preempt_notअगरier_रेजिस्टर(काष्ठा preempt_notअगरier *notअगरier)
अणु
	अगर (!अटल_branch_unlikely(&preempt_notअगरier_key))
		WARN(1, "registering preempt_notifier while notifiers disabled\n");

	hlist_add_head(&notअगरier->link, &current->preempt_notअगरiers);
पूर्ण
EXPORT_SYMBOL_GPL(preempt_notअगरier_रेजिस्टर);

/**
 * preempt_notअगरier_unरेजिस्टर - no दीर्घer पूर्णांकerested in preemption notअगरications
 * @notअगरier: notअगरier काष्ठा to unरेजिस्टर
 *
 * This is *not* safe to call from within a preemption notअगरier.
 */
व्योम preempt_notअगरier_unरेजिस्टर(काष्ठा preempt_notअगरier *notअगरier)
अणु
	hlist_del(&notअगरier->link);
पूर्ण
EXPORT_SYMBOL_GPL(preempt_notअगरier_unरेजिस्टर);

अटल व्योम __fire_sched_in_preempt_notअगरiers(काष्ठा task_काष्ठा *curr)
अणु
	काष्ठा preempt_notअगरier *notअगरier;

	hlist_क्रम_each_entry(notअगरier, &curr->preempt_notअगरiers, link)
		notअगरier->ops->sched_in(notअगरier, raw_smp_processor_id());
पूर्ण

अटल __always_अंतरभूत व्योम fire_sched_in_preempt_notअगरiers(काष्ठा task_काष्ठा *curr)
अणु
	अगर (अटल_branch_unlikely(&preempt_notअगरier_key))
		__fire_sched_in_preempt_notअगरiers(curr);
पूर्ण

अटल व्योम
__fire_sched_out_preempt_notअगरiers(काष्ठा task_काष्ठा *curr,
				   काष्ठा task_काष्ठा *next)
अणु
	काष्ठा preempt_notअगरier *notअगरier;

	hlist_क्रम_each_entry(notअगरier, &curr->preempt_notअगरiers, link)
		notअगरier->ops->sched_out(notअगरier, next);
पूर्ण

अटल __always_अंतरभूत व्योम
fire_sched_out_preempt_notअगरiers(काष्ठा task_काष्ठा *curr,
				 काष्ठा task_काष्ठा *next)
अणु
	अगर (अटल_branch_unlikely(&preempt_notअगरier_key))
		__fire_sched_out_preempt_notअगरiers(curr, next);
पूर्ण

#अन्यथा /* !CONFIG_PREEMPT_NOTIFIERS */

अटल अंतरभूत व्योम fire_sched_in_preempt_notअगरiers(काष्ठा task_काष्ठा *curr)
अणु
पूर्ण

अटल अंतरभूत व्योम
fire_sched_out_preempt_notअगरiers(काष्ठा task_काष्ठा *curr,
				 काष्ठा task_काष्ठा *next)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_PREEMPT_NOTIFIERS */

अटल अंतरभूत व्योम prepare_task(काष्ठा task_काष्ठा *next)
अणु
#अगर_घोषित CONFIG_SMP
	/*
	 * Claim the task as running, we करो this beक्रमe चयनing to it
	 * such that any running task will have this set.
	 *
	 * See the ttwu() WF_ON_CPU हाल and its ordering comment.
	 */
	WRITE_ONCE(next->on_cpu, 1);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम finish_task(काष्ठा task_काष्ठा *prev)
अणु
#अगर_घोषित CONFIG_SMP
	/*
	 * This must be the very last reference to @prev from this CPU. After
	 * p->on_cpu is cleared, the task can be moved to a dअगरferent CPU. We
	 * must ensure this करोesn't happen until the चयन is completely
	 * finished.
	 *
	 * In particular, the load of prev->state in finish_task_चयन() must
	 * happen beक्रमe this.
	 *
	 * Pairs with the smp_cond_load_acquire() in try_to_wake_up().
	 */
	smp_store_release(&prev->on_cpu, 0);
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_SMP

अटल व्योम करो_balance_callbacks(काष्ठा rq *rq, काष्ठा callback_head *head)
अणु
	व्योम (*func)(काष्ठा rq *rq);
	काष्ठा callback_head *next;

	lockdep_निश्चित_held(&rq->lock);

	जबतक (head) अणु
		func = (व्योम (*)(काष्ठा rq *))head->func;
		next = head->next;
		head->next = शून्य;
		head = next;

		func(rq);
	पूर्ण
पूर्ण

अटल व्योम balance_push(काष्ठा rq *rq);

काष्ठा callback_head balance_push_callback = अणु
	.next = शून्य,
	.func = (व्योम (*)(काष्ठा callback_head *))balance_push,
पूर्ण;

अटल अंतरभूत काष्ठा callback_head *splice_balance_callbacks(काष्ठा rq *rq)
अणु
	काष्ठा callback_head *head = rq->balance_callback;

	lockdep_निश्चित_held(&rq->lock);
	अगर (head)
		rq->balance_callback = शून्य;

	वापस head;
पूर्ण

अटल व्योम __balance_callbacks(काष्ठा rq *rq)
अणु
	करो_balance_callbacks(rq, splice_balance_callbacks(rq));
पूर्ण

अटल अंतरभूत व्योम balance_callbacks(काष्ठा rq *rq, काष्ठा callback_head *head)
अणु
	अचिन्हित दीर्घ flags;

	अगर (unlikely(head)) अणु
		raw_spin_lock_irqsave(&rq->lock, flags);
		करो_balance_callbacks(rq, head);
		raw_spin_unlock_irqrestore(&rq->lock, flags);
	पूर्ण
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम __balance_callbacks(काष्ठा rq *rq)
अणु
पूर्ण

अटल अंतरभूत काष्ठा callback_head *splice_balance_callbacks(काष्ठा rq *rq)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम balance_callbacks(काष्ठा rq *rq, काष्ठा callback_head *head)
अणु
पूर्ण

#पूर्ण_अगर

अटल अंतरभूत व्योम
prepare_lock_चयन(काष्ठा rq *rq, काष्ठा task_काष्ठा *next, काष्ठा rq_flags *rf)
अणु
	/*
	 * Since the runqueue lock will be released by the next
	 * task (which is an invalid locking op but in the हाल
	 * of the scheduler it's an obvious special-हाल), so we
	 * करो an early lockdep release here:
	 */
	rq_unpin_lock(rq, rf);
	spin_release(&rq->lock.dep_map, _THIS_IP_);
#अगर_घोषित CONFIG_DEBUG_SPINLOCK
	/* this is a valid हाल when another task releases the spinlock */
	rq->lock.owner = next;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम finish_lock_चयन(काष्ठा rq *rq)
अणु
	/*
	 * If we are tracking spinlock dependencies then we have to
	 * fix up the runqueue lock - which माला_लो 'carried over' from
	 * prev पूर्णांकo current:
	 */
	spin_acquire(&rq->lock.dep_map, 0, 0, _THIS_IP_);
	__balance_callbacks(rq);
	raw_spin_unlock_irq(&rq->lock);
पूर्ण

/*
 * NOP अगर the arch has not defined these:
 */

#अगर_अघोषित prepare_arch_चयन
# define prepare_arch_चयन(next)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_अघोषित finish_arch_post_lock_चयन
# define finish_arch_post_lock_चयन()	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

अटल अंतरभूत व्योम kmap_local_sched_out(व्योम)
अणु
#अगर_घोषित CONFIG_KMAP_LOCAL
	अगर (unlikely(current->kmap_ctrl.idx))
		__kmap_local_sched_out();
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम kmap_local_sched_in(व्योम)
अणु
#अगर_घोषित CONFIG_KMAP_LOCAL
	अगर (unlikely(current->kmap_ctrl.idx))
		__kmap_local_sched_in();
#पूर्ण_अगर
पूर्ण

/**
 * prepare_task_चयन - prepare to चयन tasks
 * @rq: the runqueue preparing to चयन
 * @prev: the current task that is being चयनed out
 * @next: the task we are going to चयन to.
 *
 * This is called with the rq lock held and पूर्णांकerrupts off. It must
 * be paired with a subsequent finish_task_चयन after the context
 * चयन.
 *
 * prepare_task_चयन sets up locking and calls architecture specअगरic
 * hooks.
 */
अटल अंतरभूत व्योम
prepare_task_चयन(काष्ठा rq *rq, काष्ठा task_काष्ठा *prev,
		    काष्ठा task_काष्ठा *next)
अणु
	kcov_prepare_चयन(prev);
	sched_info_चयन(rq, prev, next);
	perf_event_task_sched_out(prev, next);
	rseq_preempt(prev);
	fire_sched_out_preempt_notअगरiers(prev, next);
	kmap_local_sched_out();
	prepare_task(next);
	prepare_arch_चयन(next);
पूर्ण

/**
 * finish_task_चयन - clean up after a task-चयन
 * @prev: the thपढ़ो we just चयनed away from.
 *
 * finish_task_चयन must be called after the context चयन, paired
 * with a prepare_task_चयन call beक्रमe the context चयन.
 * finish_task_चयन will reconcile locking set up by prepare_task_चयन,
 * and करो any other architecture-specअगरic cleanup actions.
 *
 * Note that we may have delayed dropping an mm in context_चयन(). If
 * so, we finish that here outside of the runqueue lock. (Doing it
 * with the lock held can cause deadlocks; see schedule() क्रम
 * details.)
 *
 * The context चयन have flipped the stack from under us and restored the
 * local variables which were saved when this task called schedule() in the
 * past. prev == current is still correct but we need to recalculate this_rq
 * because prev may have moved to another CPU.
 */
अटल काष्ठा rq *finish_task_चयन(काष्ठा task_काष्ठा *prev)
	__releases(rq->lock)
अणु
	काष्ठा rq *rq = this_rq();
	काष्ठा mm_काष्ठा *mm = rq->prev_mm;
	दीर्घ prev_state;

	/*
	 * The previous task will have left us with a preempt_count of 2
	 * because it left us after:
	 *
	 *	schedule()
	 *	  preempt_disable();			// 1
	 *	  __schedule()
	 *	    raw_spin_lock_irq(&rq->lock)	// 2
	 *
	 * Also, see FORK_PREEMPT_COUNT.
	 */
	अगर (WARN_ONCE(preempt_count() != 2*PREEMPT_DISABLE_OFFSET,
		      "corrupted preempt_count: %s/%d/0x%x\n",
		      current->comm, current->pid, preempt_count()))
		preempt_count_set(FORK_PREEMPT_COUNT);

	rq->prev_mm = शून्य;

	/*
	 * A task काष्ठा has one reference क्रम the use as "current".
	 * If a task dies, then it sets TASK_DEAD in tsk->state and calls
	 * schedule one last समय. The schedule call will never वापस, and
	 * the scheduled task must drop that reference.
	 *
	 * We must observe prev->state beक्रमe clearing prev->on_cpu (in
	 * finish_task), otherwise a concurrent wakeup can get prev
	 * running on another CPU and we could rave with its RUNNING -> DEAD
	 * transition, resulting in a द्विगुन drop.
	 */
	prev_state = prev->state;
	vसमय_प्रकारask_चयन(prev);
	perf_event_task_sched_in(prev, current);
	finish_task(prev);
	finish_lock_चयन(rq);
	finish_arch_post_lock_चयन();
	kcov_finish_चयन(current);
	/*
	 * kmap_local_sched_out() is invoked with rq::lock held and
	 * पूर्णांकerrupts disabled. There is no requirement क्रम that, but the
	 * sched out code करोes not have an पूर्णांकerrupt enabled section.
	 * Restoring the maps on sched in करोes not require पूर्णांकerrupts being
	 * disabled either.
	 */
	kmap_local_sched_in();

	fire_sched_in_preempt_notअगरiers(current);
	/*
	 * When चयनing through a kernel thपढ़ो, the loop in
	 * membarrier_अणुनिजी,globalपूर्ण_expedited() may have observed that
	 * kernel thपढ़ो and not issued an IPI. It is thereक्रमe possible to
	 * schedule between user->kernel->user thपढ़ोs without passing though
	 * चयन_mm(). Membarrier requires a barrier after storing to
	 * rq->curr, beक्रमe वापसing to userspace, so provide them here:
	 *
	 * - a full memory barrier क्रम अणुPRIVATE,GLOBALपूर्ण_EXPEDITED, implicitly
	 *   provided by mmdrop(),
	 * - a sync_core क्रम SYNC_CORE.
	 */
	अगर (mm) अणु
		membarrier_mm_sync_core_beक्रमe_usermode(mm);
		mmdrop(mm);
	पूर्ण
	अगर (unlikely(prev_state == TASK_DEAD)) अणु
		अगर (prev->sched_class->task_dead)
			prev->sched_class->task_dead(prev);

		/*
		 * Remove function-वापस probe instances associated with this
		 * task and put them back on the मुक्त list.
		 */
		kprobe_flush_task(prev);

		/* Task is करोne with its stack. */
		put_task_stack(prev);

		put_task_काष्ठा_rcu_user(prev);
	पूर्ण

	tick_nohz_task_चयन();
	वापस rq;
पूर्ण

/**
 * schedule_tail - first thing a freshly विभाजनed thपढ़ो must call.
 * @prev: the thपढ़ो we just चयनed away from.
 */
यंत्रlinkage __visible व्योम schedule_tail(काष्ठा task_काष्ठा *prev)
	__releases(rq->lock)
अणु
	/*
	 * New tasks start with FORK_PREEMPT_COUNT, see there and
	 * finish_task_चयन() क्रम details.
	 *
	 * finish_task_चयन() will drop rq->lock() and lower preempt_count
	 * and the preempt_enable() will end up enabling preemption (on
	 * PREEMPT_COUNT kernels).
	 */

	finish_task_चयन(prev);
	preempt_enable();

	अगर (current->set_child_tid)
		put_user(task_pid_vnr(current), current->set_child_tid);

	calculate_संक_बाकी();
पूर्ण

/*
 * context_चयन - चयन to the new MM and the new thपढ़ो's रेजिस्टर state.
 */
अटल __always_अंतरभूत काष्ठा rq *
context_चयन(काष्ठा rq *rq, काष्ठा task_काष्ठा *prev,
	       काष्ठा task_काष्ठा *next, काष्ठा rq_flags *rf)
अणु
	prepare_task_चयन(rq, prev, next);

	/*
	 * For paravirt, this is coupled with an निकास in चयन_to to
	 * combine the page table reload and the चयन backend पूर्णांकo
	 * one hypercall.
	 */
	arch_start_context_चयन(prev);

	/*
	 * kernel -> kernel   lazy + transfer active
	 *   user -> kernel   lazy + mmgrab() active
	 *
	 * kernel ->   user   चयन + mmdrop() active
	 *   user ->   user   चयन
	 */
	अगर (!next->mm) अणु                                // to kernel
		enter_lazy_tlb(prev->active_mm, next);

		next->active_mm = prev->active_mm;
		अगर (prev->mm)                           // from user
			mmgrab(prev->active_mm);
		अन्यथा
			prev->active_mm = शून्य;
	पूर्ण अन्यथा अणु                                        // to user
		membarrier_चयन_mm(rq, prev->active_mm, next->mm);
		/*
		 * sys_membarrier() requires an smp_mb() between setting
		 * rq->curr / membarrier_चयन_mm() and वापसing to userspace.
		 *
		 * The below provides this either through चयन_mm(), or in
		 * हाल 'prev->active_mm == next->mm' through
		 * finish_task_चयन()'s mmdrop().
		 */
		चयन_mm_irqs_off(prev->active_mm, next->mm, next);

		अगर (!prev->mm) अणु                        // from kernel
			/* will mmdrop() in finish_task_चयन(). */
			rq->prev_mm = prev->active_mm;
			prev->active_mm = शून्य;
		पूर्ण
	पूर्ण

	rq->घड़ी_update_flags &= ~(RQCF_ACT_SKIP|RQCF_REQ_SKIP);

	prepare_lock_चयन(rq, next, rf);

	/* Here we just चयन the रेजिस्टर state and the stack. */
	चयन_to(prev, next, prev);
	barrier();

	वापस finish_task_चयन(prev);
पूर्ण

/*
 * nr_running and nr_context_चयनes:
 *
 * बाह्यally visible scheduler statistics: current number of runnable
 * thपढ़ोs, total number of context चयनes perक्रमmed since bootup.
 */
अचिन्हित दीर्घ nr_running(व्योम)
अणु
	अचिन्हित दीर्घ i, sum = 0;

	क्रम_each_online_cpu(i)
		sum += cpu_rq(i)->nr_running;

	वापस sum;
पूर्ण

/*
 * Check अगर only the current task is running on the CPU.
 *
 * Caution: this function करोes not check that the caller has disabled
 * preemption, thus the result might have a समय-of-check-to-समय-of-use
 * race.  The caller is responsible to use it correctly, क्रम example:
 *
 * - from a non-preemptible section (of course)
 *
 * - from a thपढ़ो that is bound to a single CPU
 *
 * - in a loop with very लघु iterations (e.g. a polling loop)
 */
bool single_task_running(व्योम)
अणु
	वापस raw_rq()->nr_running == 1;
पूर्ण
EXPORT_SYMBOL(single_task_running);

अचिन्हित दीर्घ दीर्घ nr_context_चयनes(व्योम)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ दीर्घ sum = 0;

	क्रम_each_possible_cpu(i)
		sum += cpu_rq(i)->nr_चयनes;

	वापस sum;
पूर्ण

/*
 * Consumers of these two पूर्णांकerfaces, like क्रम example the cpuidle menu
 * governor, are using nonsensical data. Preferring shallow idle state selection
 * क्रम a CPU that has IO-रुको which might not even end up running the task when
 * it करोes become runnable.
 */

अचिन्हित दीर्घ nr_ioरुको_cpu(पूर्णांक cpu)
अणु
	वापस atomic_पढ़ो(&cpu_rq(cpu)->nr_ioरुको);
पूर्ण

/*
 * IO-रुको accounting, and how it's mostly bollocks (on SMP).
 *
 * The idea behind IO-रुको account is to account the idle समय that we could
 * have spend running अगर it were not क्रम IO. That is, अगर we were to improve the
 * storage perक्रमmance, we'd have a proportional reduction in IO-रुको समय.
 *
 * This all works nicely on UP, where, when a task blocks on IO, we account
 * idle समय as IO-रुको, because अगर the storage were faster, it could've been
 * running and we'd not be idle.
 *
 * This has been extended to SMP, by करोing the same क्रम each CPU. This however
 * is broken.
 *
 * Imagine क्रम instance the हाल where two tasks block on one CPU, only the one
 * CPU will have IO-रुको accounted, जबतक the other has regular idle. Even
 * though, अगर the storage were faster, both could've ran at the same समय,
 * utilising both CPUs.
 *
 * This means, that when looking globally, the current IO-रुको accounting on
 * SMP is a lower bound, by reason of under accounting.
 *
 * Worse, since the numbers are provided per CPU, they are someबार
 * पूर्णांकerpreted per CPU, and that is nonsensical. A blocked task isn't strictly
 * associated with any one particular CPU, it can wake to another CPU than it
 * blocked on. This means the per CPU IO-रुको number is meaningless.
 *
 * Task CPU affinities can make all that even more 'interesting'.
 */

अचिन्हित दीर्घ nr_ioरुको(व्योम)
अणु
	अचिन्हित दीर्घ i, sum = 0;

	क्रम_each_possible_cpu(i)
		sum += nr_ioरुको_cpu(i);

	वापस sum;
पूर्ण

#अगर_घोषित CONFIG_SMP

/*
 * sched_exec - execve() is a valuable balancing opportunity, because at
 * this poपूर्णांक the task has the smallest effective memory and cache footprपूर्णांक.
 */
व्योम sched_exec(व्योम)
अणु
	काष्ठा task_काष्ठा *p = current;
	अचिन्हित दीर्घ flags;
	पूर्णांक dest_cpu;

	raw_spin_lock_irqsave(&p->pi_lock, flags);
	dest_cpu = p->sched_class->select_task_rq(p, task_cpu(p), WF_EXEC);
	अगर (dest_cpu == smp_processor_id())
		जाओ unlock;

	अगर (likely(cpu_active(dest_cpu))) अणु
		काष्ठा migration_arg arg = अणु p, dest_cpu पूर्ण;

		raw_spin_unlock_irqrestore(&p->pi_lock, flags);
		stop_one_cpu(task_cpu(p), migration_cpu_stop, &arg);
		वापस;
	पूर्ण
unlock:
	raw_spin_unlock_irqrestore(&p->pi_lock, flags);
पूर्ण

#पूर्ण_अगर

DEFINE_PER_CPU(काष्ठा kernel_stat, kstat);
DEFINE_PER_CPU(काष्ठा kernel_cpustat, kernel_cpustat);

EXPORT_PER_CPU_SYMBOL(kstat);
EXPORT_PER_CPU_SYMBOL(kernel_cpustat);

/*
 * The function fair_sched_class.update_curr accesses the काष्ठा curr
 * and its field curr->exec_start; when called from task_sched_runसमय(),
 * we observe a high rate of cache misses in practice.
 * Prefetching this data results in improved perक्रमmance.
 */
अटल अंतरभूत व्योम prefetch_curr_exec_start(काष्ठा task_काष्ठा *p)
अणु
#अगर_घोषित CONFIG_FAIR_GROUP_SCHED
	काष्ठा sched_entity *curr = (&p->se)->cfs_rq->curr;
#अन्यथा
	काष्ठा sched_entity *curr = (&task_rq(p)->cfs)->curr;
#पूर्ण_अगर
	prefetch(curr);
	prefetch(&curr->exec_start);
पूर्ण

/*
 * Return accounted runसमय क्रम the task.
 * In हाल the task is currently running, वापस the runसमय plus current's
 * pending runसमय that have not been accounted yet.
 */
अचिन्हित दीर्घ दीर्घ task_sched_runसमय(काष्ठा task_काष्ठा *p)
अणु
	काष्ठा rq_flags rf;
	काष्ठा rq *rq;
	u64 ns;

#अगर defined(CONFIG_64BIT) && defined(CONFIG_SMP)
	/*
	 * 64-bit करोesn't need locks to atomically पढ़ो a 64-bit value.
	 * So we have a optimization chance when the task's delta_exec is 0.
	 * Reading ->on_cpu is racy, but this is ok.
	 *
	 * If we race with it leaving CPU, we'll take a lock. So we're correct.
	 * If we race with it entering CPU, unaccounted समय is 0. This is
	 * indistinguishable from the पढ़ो occurring a few cycles earlier.
	 * If we see ->on_cpu without ->on_rq, the task is leaving, and has
	 * been accounted, so we're correct here as well.
	 */
	अगर (!p->on_cpu || !task_on_rq_queued(p))
		वापस p->se.sum_exec_runसमय;
#पूर्ण_अगर

	rq = task_rq_lock(p, &rf);
	/*
	 * Must be ->curr _and_ ->on_rq.  If dequeued, we would
	 * project cycles that may never be accounted to this
	 * thपढ़ो, अवरोधing घड़ी_समय_लो().
	 */
	अगर (task_current(rq, p) && task_on_rq_queued(p)) अणु
		prefetch_curr_exec_start(p);
		update_rq_घड़ी(rq);
		p->sched_class->update_curr(rq);
	पूर्ण
	ns = p->se.sum_exec_runसमय;
	task_rq_unlock(rq, p, &rf);

	वापस ns;
पूर्ण

#अगर_घोषित CONFIG_SCHED_DEBUG
अटल u64 cpu_resched_latency(काष्ठा rq *rq)
अणु
	पूर्णांक latency_warn_ms = READ_ONCE(sysctl_resched_latency_warn_ms);
	u64 resched_latency, now = rq_घड़ी(rq);
	अटल bool warned_once;

	अगर (sysctl_resched_latency_warn_once && warned_once)
		वापस 0;

	अगर (!need_resched() || !latency_warn_ms)
		वापस 0;

	अगर (प्रणाली_state == SYSTEM_BOOTING)
		वापस 0;

	अगर (!rq->last_seen_need_resched_ns) अणु
		rq->last_seen_need_resched_ns = now;
		rq->ticks_without_resched = 0;
		वापस 0;
	पूर्ण

	rq->ticks_without_resched++;
	resched_latency = now - rq->last_seen_need_resched_ns;
	अगर (resched_latency <= latency_warn_ms * NSEC_PER_MSEC)
		वापस 0;

	warned_once = true;

	वापस resched_latency;
पूर्ण

अटल पूर्णांक __init setup_resched_latency_warn_ms(अक्षर *str)
अणु
	दीर्घ val;

	अगर ((kम_से_दीर्घ(str, 0, &val))) अणु
		pr_warn("Unable to set resched_latency_warn_ms\n");
		वापस 1;
	पूर्ण

	sysctl_resched_latency_warn_ms = val;
	वापस 1;
पूर्ण
__setup("resched_latency_warn_ms=", setup_resched_latency_warn_ms);
#अन्यथा
अटल अंतरभूत u64 cpu_resched_latency(काष्ठा rq *rq) अणु वापस 0; पूर्ण
#पूर्ण_अगर /* CONFIG_SCHED_DEBUG */

/*
 * This function माला_लो called by the समयr code, with HZ frequency.
 * We call it with पूर्णांकerrupts disabled.
 */
व्योम scheduler_tick(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();
	काष्ठा rq *rq = cpu_rq(cpu);
	काष्ठा task_काष्ठा *curr = rq->curr;
	काष्ठा rq_flags rf;
	अचिन्हित दीर्घ thermal_pressure;
	u64 resched_latency;

	arch_scale_freq_tick();
	sched_घड़ी_प्रकारick();

	rq_lock(rq, &rf);

	update_rq_घड़ी(rq);
	thermal_pressure = arch_scale_thermal_pressure(cpu_of(rq));
	update_thermal_load_avg(rq_घड़ी_प्रकारhermal(rq), rq, thermal_pressure);
	curr->sched_class->task_tick(rq, curr, 0);
	अगर (sched_feat(LATENCY_WARN))
		resched_latency = cpu_resched_latency(rq);
	calc_global_load_tick(rq);

	rq_unlock(rq, &rf);

	अगर (sched_feat(LATENCY_WARN) && resched_latency)
		resched_latency_warn(cpu, resched_latency);

	perf_event_task_tick();

#अगर_घोषित CONFIG_SMP
	rq->idle_balance = idle_cpu(cpu);
	trigger_load_balance(rq);
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_NO_HZ_FULL

काष्ठा tick_work अणु
	पूर्णांक			cpu;
	atomic_t		state;
	काष्ठा delayed_work	work;
पूर्ण;
/* Values क्रम ->state, see diagram below. */
#घोषणा TICK_SCHED_REMOTE_OFFLINE	0
#घोषणा TICK_SCHED_REMOTE_OFFLINING	1
#घोषणा TICK_SCHED_REMOTE_RUNNING	2

/*
 * State diagram क्रम ->state:
 *
 *
 *          TICK_SCHED_REMOTE_OFFLINE
 *                    |   ^
 *                    |   |
 *                    |   | sched_tick_remote()
 *                    |   |
 *                    |   |
 *                    +--TICK_SCHED_REMOTE_OFFLINING
 *                    |   ^
 *                    |   |
 * sched_tick_start() |   | sched_tick_stop()
 *                    |   |
 *                    V   |
 *          TICK_SCHED_REMOTE_RUNNING
 *
 *
 * Other transitions get WARN_ON_ONCE(), except that sched_tick_remote()
 * and sched_tick_start() are happy to leave the state in RUNNING.
 */

अटल काष्ठा tick_work __percpu *tick_work_cpu;

अटल व्योम sched_tick_remote(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा tick_work *twork = container_of(dwork, काष्ठा tick_work, work);
	पूर्णांक cpu = twork->cpu;
	काष्ठा rq *rq = cpu_rq(cpu);
	काष्ठा task_काष्ठा *curr;
	काष्ठा rq_flags rf;
	u64 delta;
	पूर्णांक os;

	/*
	 * Handle the tick only अगर it appears the remote CPU is running in full
	 * dynticks mode. The check is racy by nature, but missing a tick or
	 * having one too much is no big deal because the scheduler tick updates
	 * statistics and checks बारlices in a समय-independent way, regardless
	 * of when exactly it is running.
	 */
	अगर (!tick_nohz_tick_stopped_cpu(cpu))
		जाओ out_requeue;

	rq_lock_irq(rq, &rf);
	curr = rq->curr;
	अगर (cpu_is_offline(cpu))
		जाओ out_unlock;

	update_rq_घड़ी(rq);

	अगर (!is_idle_task(curr)) अणु
		/*
		 * Make sure the next tick runs within a reasonable
		 * amount of समय.
		 */
		delta = rq_घड़ी_प्रकारask(rq) - curr->se.exec_start;
		WARN_ON_ONCE(delta > (u64)NSEC_PER_SEC * 3);
	पूर्ण
	curr->sched_class->task_tick(rq, curr, 0);

	calc_load_nohz_remote(rq);
out_unlock:
	rq_unlock_irq(rq, &rf);
out_requeue:

	/*
	 * Run the remote tick once per second (1Hz). This arbitrary
	 * frequency is large enough to aव्योम overload but लघु enough
	 * to keep scheduler पूर्णांकernal stats reasonably up to date.  But
	 * first update state to reflect hotplug activity अगर required.
	 */
	os = atomic_fetch_add_unless(&twork->state, -1, TICK_SCHED_REMOTE_RUNNING);
	WARN_ON_ONCE(os == TICK_SCHED_REMOTE_OFFLINE);
	अगर (os == TICK_SCHED_REMOTE_RUNNING)
		queue_delayed_work(प्रणाली_unbound_wq, dwork, HZ);
पूर्ण

अटल व्योम sched_tick_start(पूर्णांक cpu)
अणु
	पूर्णांक os;
	काष्ठा tick_work *twork;

	अगर (housekeeping_cpu(cpu, HK_FLAG_TICK))
		वापस;

	WARN_ON_ONCE(!tick_work_cpu);

	twork = per_cpu_ptr(tick_work_cpu, cpu);
	os = atomic_xchg(&twork->state, TICK_SCHED_REMOTE_RUNNING);
	WARN_ON_ONCE(os == TICK_SCHED_REMOTE_RUNNING);
	अगर (os == TICK_SCHED_REMOTE_OFFLINE) अणु
		twork->cpu = cpu;
		INIT_DELAYED_WORK(&twork->work, sched_tick_remote);
		queue_delayed_work(प्रणाली_unbound_wq, &twork->work, HZ);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल व्योम sched_tick_stop(पूर्णांक cpu)
अणु
	काष्ठा tick_work *twork;
	पूर्णांक os;

	अगर (housekeeping_cpu(cpu, HK_FLAG_TICK))
		वापस;

	WARN_ON_ONCE(!tick_work_cpu);

	twork = per_cpu_ptr(tick_work_cpu, cpu);
	/* There cannot be competing actions, but करोn't rely on stop-machine. */
	os = atomic_xchg(&twork->state, TICK_SCHED_REMOTE_OFFLINING);
	WARN_ON_ONCE(os != TICK_SCHED_REMOTE_RUNNING);
	/* Don't cancel, as this would mess up the state machine. */
पूर्ण
#पूर्ण_अगर /* CONFIG_HOTPLUG_CPU */

पूर्णांक __init sched_tick_offload_init(व्योम)
अणु
	tick_work_cpu = alloc_percpu(काष्ठा tick_work);
	BUG_ON(!tick_work_cpu);
	वापस 0;
पूर्ण

#अन्यथा /* !CONFIG_NO_HZ_FULL */
अटल अंतरभूत व्योम sched_tick_start(पूर्णांक cpu) अणु पूर्ण
अटल अंतरभूत व्योम sched_tick_stop(पूर्णांक cpu) अणु पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_PREEMPTION) && (defined(CONFIG_DEBUG_PREEMPT) || \
				defined(CONFIG_TRACE_PREEMPT_TOGGLE))
/*
 * If the value passed in is equal to the current preempt count
 * then we just disabled preemption. Start timing the latency.
 */
अटल अंतरभूत व्योम preempt_latency_start(पूर्णांक val)
अणु
	अगर (preempt_count() == val) अणु
		अचिन्हित दीर्घ ip = get_lock_parent_ip();
#अगर_घोषित CONFIG_DEBUG_PREEMPT
		current->preempt_disable_ip = ip;
#पूर्ण_अगर
		trace_preempt_off(CALLER_ADDR0, ip);
	पूर्ण
पूर्ण

व्योम preempt_count_add(पूर्णांक val)
अणु
#अगर_घोषित CONFIG_DEBUG_PREEMPT
	/*
	 * Underflow?
	 */
	अगर (DEBUG_LOCKS_WARN_ON((preempt_count() < 0)))
		वापस;
#पूर्ण_अगर
	__preempt_count_add(val);
#अगर_घोषित CONFIG_DEBUG_PREEMPT
	/*
	 * Spinlock count overflowing soon?
	 */
	DEBUG_LOCKS_WARN_ON((preempt_count() & PREEMPT_MASK) >=
				PREEMPT_MASK - 10);
#पूर्ण_अगर
	preempt_latency_start(val);
पूर्ण
EXPORT_SYMBOL(preempt_count_add);
NOKPROBE_SYMBOL(preempt_count_add);

/*
 * If the value passed in equals to the current preempt count
 * then we just enabled preemption. Stop timing the latency.
 */
अटल अंतरभूत व्योम preempt_latency_stop(पूर्णांक val)
अणु
	अगर (preempt_count() == val)
		trace_preempt_on(CALLER_ADDR0, get_lock_parent_ip());
पूर्ण

व्योम preempt_count_sub(पूर्णांक val)
अणु
#अगर_घोषित CONFIG_DEBUG_PREEMPT
	/*
	 * Underflow?
	 */
	अगर (DEBUG_LOCKS_WARN_ON(val > preempt_count()))
		वापस;
	/*
	 * Is the spinlock portion underflowing?
	 */
	अगर (DEBUG_LOCKS_WARN_ON((val < PREEMPT_MASK) &&
			!(preempt_count() & PREEMPT_MASK)))
		वापस;
#पूर्ण_अगर

	preempt_latency_stop(val);
	__preempt_count_sub(val);
पूर्ण
EXPORT_SYMBOL(preempt_count_sub);
NOKPROBE_SYMBOL(preempt_count_sub);

#अन्यथा
अटल अंतरभूत व्योम preempt_latency_start(पूर्णांक val) अणु पूर्ण
अटल अंतरभूत व्योम preempt_latency_stop(पूर्णांक val) अणु पूर्ण
#पूर्ण_अगर

अटल अंतरभूत अचिन्हित दीर्घ get_preempt_disable_ip(काष्ठा task_काष्ठा *p)
अणु
#अगर_घोषित CONFIG_DEBUG_PREEMPT
	वापस p->preempt_disable_ip;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

/*
 * Prपूर्णांक scheduling जबतक atomic bug:
 */
अटल noअंतरभूत व्योम __schedule_bug(काष्ठा task_काष्ठा *prev)
अणु
	/* Save this beक्रमe calling prपूर्णांकk(), since that will clobber it */
	अचिन्हित दीर्घ preempt_disable_ip = get_preempt_disable_ip(current);

	अगर (oops_in_progress)
		वापस;

	prपूर्णांकk(KERN_ERR "BUG: scheduling while atomic: %s/%d/0x%08x\n",
		prev->comm, prev->pid, preempt_count());

	debug_show_held_locks(prev);
	prपूर्णांक_modules();
	अगर (irqs_disabled())
		prपूर्णांक_irqtrace_events(prev);
	अगर (IS_ENABLED(CONFIG_DEBUG_PREEMPT)
	    && in_atomic_preempt_off()) अणु
		pr_err("Preemption disabled at:");
		prपूर्णांक_ip_sym(KERN_ERR, preempt_disable_ip);
	पूर्ण
	अगर (panic_on_warn)
		panic("scheduling while atomic\n");

	dump_stack();
	add_taपूर्णांक(TAINT_WARN, LOCKDEP_STILL_OK);
पूर्ण

/*
 * Various schedule()-समय debugging checks and statistics:
 */
अटल अंतरभूत व्योम schedule_debug(काष्ठा task_काष्ठा *prev, bool preempt)
अणु
#अगर_घोषित CONFIG_SCHED_STACK_END_CHECK
	अगर (task_stack_end_corrupted(prev))
		panic("corrupted stack end detected inside scheduler\n");

	अगर (task_scs_end_corrupted(prev))
		panic("corrupted shadow stack detected inside scheduler\n");
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_ATOMIC_SLEEP
	अगर (!preempt && prev->state && prev->non_block_count) अणु
		prपूर्णांकk(KERN_ERR "BUG: scheduling in a non-blocking section: %s/%d/%i\n",
			prev->comm, prev->pid, prev->non_block_count);
		dump_stack();
		add_taपूर्णांक(TAINT_WARN, LOCKDEP_STILL_OK);
	पूर्ण
#पूर्ण_अगर

	अगर (unlikely(in_atomic_preempt_off())) अणु
		__schedule_bug(prev);
		preempt_count_set(PREEMPT_DISABLED);
	पूर्ण
	rcu_sleep_check();
	SCHED_WARN_ON(ct_state() == CONTEXT_USER);

	profile_hit(SCHED_PROFILING, __builtin_वापस_address(0));

	schedstat_inc(this_rq()->sched_count);
पूर्ण

अटल व्योम put_prev_task_balance(काष्ठा rq *rq, काष्ठा task_काष्ठा *prev,
				  काष्ठा rq_flags *rf)
अणु
#अगर_घोषित CONFIG_SMP
	स्थिर काष्ठा sched_class *class;
	/*
	 * We must करो the balancing pass beक्रमe put_prev_task(), such
	 * that when we release the rq->lock the task is in the same
	 * state as beक्रमe we took rq->lock.
	 *
	 * We can terminate the balance pass as soon as we know there is
	 * a runnable task of @class priority or higher.
	 */
	क्रम_class_range(class, prev->sched_class, &idle_sched_class) अणु
		अगर (class->balance(rq, prev, rf))
			अवरोध;
	पूर्ण
#पूर्ण_अगर

	put_prev_task(rq, prev);
पूर्ण

/*
 * Pick up the highest-prio task:
 */
अटल अंतरभूत काष्ठा task_काष्ठा *
pick_next_task(काष्ठा rq *rq, काष्ठा task_काष्ठा *prev, काष्ठा rq_flags *rf)
अणु
	स्थिर काष्ठा sched_class *class;
	काष्ठा task_काष्ठा *p;

	/*
	 * Optimization: we know that अगर all tasks are in the fair class we can
	 * call that function directly, but only अगर the @prev task wasn't of a
	 * higher scheduling class, because otherwise those lose the
	 * opportunity to pull in more work from other CPUs.
	 */
	अगर (likely(prev->sched_class <= &fair_sched_class &&
		   rq->nr_running == rq->cfs.h_nr_running)) अणु

		p = pick_next_task_fair(rq, prev, rf);
		अगर (unlikely(p == RETRY_TASK))
			जाओ restart;

		/* Assumes fair_sched_class->next == idle_sched_class */
		अगर (!p) अणु
			put_prev_task(rq, prev);
			p = pick_next_task_idle(rq);
		पूर्ण

		वापस p;
	पूर्ण

restart:
	put_prev_task_balance(rq, prev, rf);

	क्रम_each_class(class) अणु
		p = class->pick_next_task(rq);
		अगर (p)
			वापस p;
	पूर्ण

	/* The idle class should always have a runnable task: */
	BUG();
पूर्ण

/*
 * __schedule() is the मुख्य scheduler function.
 *
 * The मुख्य means of driving the scheduler and thus entering this function are:
 *
 *   1. Explicit blocking: mutex, semaphore, रुकोqueue, etc.
 *
 *   2. TIF_NEED_RESCHED flag is checked on पूर्णांकerrupt and userspace वापस
 *      paths. For example, see arch/x86/entry_64.S.
 *
 *      To drive preemption between tasks, the scheduler sets the flag in समयr
 *      पूर्णांकerrupt handler scheduler_tick().
 *
 *   3. Wakeups करोn't really cause entry पूर्णांकo schedule(). They add a
 *      task to the run-queue and that's it.
 *
 *      Now, अगर the new task added to the run-queue preempts the current
 *      task, then the wakeup sets TIF_NEED_RESCHED and schedule() माला_लो
 *      called on the nearest possible occasion:
 *
 *       - If the kernel is preemptible (CONFIG_PREEMPTION=y):
 *
 *         - in syscall or exception context, at the next ouपंचांगost
 *           preempt_enable(). (this might be as soon as the wake_up()'s
 *           spin_unlock()!)
 *
 *         - in IRQ context, वापस from पूर्णांकerrupt-handler to
 *           preemptible context
 *
 *       - If the kernel is not preemptible (CONFIG_PREEMPTION is not set)
 *         then at the next:
 *
 *          - cond_resched() call
 *          - explicit schedule() call
 *          - वापस from syscall or exception to user-space
 *          - वापस from पूर्णांकerrupt-handler to user-space
 *
 * WARNING: must be called with preemption disabled!
 */
अटल व्योम __sched notrace __schedule(bool preempt)
अणु
	काष्ठा task_काष्ठा *prev, *next;
	अचिन्हित दीर्घ *चयन_count;
	अचिन्हित दीर्घ prev_state;
	काष्ठा rq_flags rf;
	काष्ठा rq *rq;
	पूर्णांक cpu;

	cpu = smp_processor_id();
	rq = cpu_rq(cpu);
	prev = rq->curr;

	schedule_debug(prev, preempt);

	अगर (sched_feat(HRTICK) || sched_feat(HRTICK_DL))
		hrtick_clear(rq);

	local_irq_disable();
	rcu_note_context_चयन(preempt);

	/*
	 * Make sure that संकेत_pending_state()->संकेत_pending() below
	 * can't be reordered with __set_current_state(TASK_INTERRUPTIBLE)
	 * करोne by the caller to aव्योम the race with संकेत_wake_up():
	 *
	 * __set_current_state(@state)		संकेत_wake_up()
	 * schedule()				  set_tsk_thपढ़ो_flag(p, TIF_SIGPENDING)
	 *					  wake_up_state(p, state)
	 *   LOCK rq->lock			    LOCK p->pi_state
	 *   smp_mb__after_spinlock()		    smp_mb__after_spinlock()
	 *     अगर (संकेत_pending_state())	    अगर (p->state & @state)
	 *
	 * Also, the membarrier प्रणाली call requires a full memory barrier
	 * after coming from user-space, beक्रमe storing to rq->curr.
	 */
	rq_lock(rq, &rf);
	smp_mb__after_spinlock();

	/* Promote REQ to ACT */
	rq->घड़ी_update_flags <<= 1;
	update_rq_घड़ी(rq);

	चयन_count = &prev->nivcsw;

	/*
	 * We must load prev->state once (task_काष्ठा::state is अस्थिर), such
	 * that:
	 *
	 *  - we क्रमm a control dependency vs deactivate_task() below.
	 *  - ptrace_अणु,unपूर्णमुक्तze_traced() can change ->state underneath us.
	 */
	prev_state = prev->state;
	अगर (!preempt && prev_state) अणु
		अगर (संकेत_pending_state(prev_state, prev)) अणु
			prev->state = TASK_RUNNING;
		पूर्ण अन्यथा अणु
			prev->sched_contributes_to_load =
				(prev_state & TASK_UNINTERRUPTIBLE) &&
				!(prev_state & TASK_NOLOAD) &&
				!(prev->flags & PF_FROZEN);

			अगर (prev->sched_contributes_to_load)
				rq->nr_unपूर्णांकerruptible++;

			/*
			 * __schedule()			ttwu()
			 *   prev_state = prev->state;    अगर (p->on_rq && ...)
			 *   अगर (prev_state)		    जाओ out;
			 *     p->on_rq = 0;		  smp_acquire__after_ctrl_dep();
			 *				  p->state = TASK_WAKING
			 *
			 * Where __schedule() and ttwu() have matching control dependencies.
			 *
			 * After this, schedule() must not care about p->state any more.
			 */
			deactivate_task(rq, prev, DEQUEUE_SLEEP | DEQUEUE_NOCLOCK);

			अगर (prev->in_ioरुको) अणु
				atomic_inc(&rq->nr_ioरुको);
				delayacct_blkio_start();
			पूर्ण
		पूर्ण
		चयन_count = &prev->nvcsw;
	पूर्ण

	next = pick_next_task(rq, prev, &rf);
	clear_tsk_need_resched(prev);
	clear_preempt_need_resched();
#अगर_घोषित CONFIG_SCHED_DEBUG
	rq->last_seen_need_resched_ns = 0;
#पूर्ण_अगर

	अगर (likely(prev != next)) अणु
		rq->nr_चयनes++;
		/*
		 * RCU users of rcu_dereference(rq->curr) may not see
		 * changes to task_काष्ठा made by pick_next_task().
		 */
		RCU_INIT_POINTER(rq->curr, next);
		/*
		 * The membarrier प्रणाली call requires each architecture
		 * to have a full memory barrier after updating
		 * rq->curr, beक्रमe वापसing to user-space.
		 *
		 * Here are the schemes providing that barrier on the
		 * various architectures:
		 * - mm ? चयन_mm() : mmdrop() क्रम x86, s390, sparc, PowerPC.
		 *   चयन_mm() rely on membarrier_arch_चयन_mm() on PowerPC.
		 * - finish_lock_चयन() क्रम weakly-ordered
		 *   architectures where spin_unlock is a full barrier,
		 * - चयन_to() क्रम arm64 (weakly-ordered, spin_unlock
		 *   is a RELEASE barrier),
		 */
		++*चयन_count;

		migrate_disable_चयन(rq, prev);
		psi_sched_चयन(prev, next, !task_on_rq_queued(prev));

		trace_sched_चयन(preempt, prev, next);

		/* Also unlocks the rq: */
		rq = context_चयन(rq, prev, next, &rf);
	पूर्ण अन्यथा अणु
		rq->घड़ी_update_flags &= ~(RQCF_ACT_SKIP|RQCF_REQ_SKIP);

		rq_unpin_lock(rq, &rf);
		__balance_callbacks(rq);
		raw_spin_unlock_irq(&rq->lock);
	पूर्ण
पूर्ण

व्योम __noवापस करो_task_dead(व्योम)
अणु
	/* Causes final put_task_काष्ठा in finish_task_चयन(): */
	set_special_state(TASK_DEAD);

	/* Tell मुक्तzer to ignore us: */
	current->flags |= PF_NOFREEZE;

	__schedule(false);
	BUG();

	/* Aव्योम "noreturn function does return" - but करोn't जारी अगर BUG() is a NOP: */
	क्रम (;;)
		cpu_relax();
पूर्ण

अटल अंतरभूत व्योम sched_submit_work(काष्ठा task_काष्ठा *tsk)
अणु
	अचिन्हित पूर्णांक task_flags;

	अगर (!tsk->state)
		वापस;

	task_flags = tsk->flags;
	/*
	 * If a worker went to sleep, notअगरy and ask workqueue whether
	 * it wants to wake up a task to मुख्यtain concurrency.
	 * As this function is called inside the schedule() context,
	 * we disable preemption to aव्योम it calling schedule() again
	 * in the possible wakeup of a kworker and because wq_worker_sleeping()
	 * requires it.
	 */
	अगर (task_flags & (PF_WQ_WORKER | PF_IO_WORKER)) अणु
		preempt_disable();
		अगर (task_flags & PF_WQ_WORKER)
			wq_worker_sleeping(tsk);
		अन्यथा
			io_wq_worker_sleeping(tsk);
		preempt_enable_no_resched();
	पूर्ण

	अगर (tsk_is_pi_blocked(tsk))
		वापस;

	/*
	 * If we are going to sleep and we have plugged IO queued,
	 * make sure to submit it to aव्योम deadlocks.
	 */
	अगर (blk_needs_flush_plug(tsk))
		blk_schedule_flush_plug(tsk);
पूर्ण

अटल व्योम sched_update_worker(काष्ठा task_काष्ठा *tsk)
अणु
	अगर (tsk->flags & (PF_WQ_WORKER | PF_IO_WORKER)) अणु
		अगर (tsk->flags & PF_WQ_WORKER)
			wq_worker_running(tsk);
		अन्यथा
			io_wq_worker_running(tsk);
	पूर्ण
पूर्ण

यंत्रlinkage __visible व्योम __sched schedule(व्योम)
अणु
	काष्ठा task_काष्ठा *tsk = current;

	sched_submit_work(tsk);
	करो अणु
		preempt_disable();
		__schedule(false);
		sched_preempt_enable_no_resched();
	पूर्ण जबतक (need_resched());
	sched_update_worker(tsk);
पूर्ण
EXPORT_SYMBOL(schedule);

/*
 * synchronize_rcu_tasks() makes sure that no task is stuck in preempted
 * state (have scheduled out non-voluntarily) by making sure that all
 * tasks have either left the run queue or have gone पूर्णांकo user space.
 * As idle tasks करो not करो either, they must not ever be preempted
 * (schedule out non-voluntarily).
 *
 * schedule_idle() is similar to schedule_preempt_disable() except that it
 * never enables preemption because it करोes not call sched_submit_work().
 */
व्योम __sched schedule_idle(व्योम)
अणु
	/*
	 * As this skips calling sched_submit_work(), which the idle task करोes
	 * regardless because that function is a nop when the task is in a
	 * TASK_RUNNING state, make sure this isn't used someplace that the
	 * current task can be in any other state. Note, idle is always in the
	 * TASK_RUNNING state.
	 */
	WARN_ON_ONCE(current->state);
	करो अणु
		__schedule(false);
	पूर्ण जबतक (need_resched());
पूर्ण

#अगर defined(CONFIG_CONTEXT_TRACKING) && !defined(CONFIG_HAVE_CONTEXT_TRACKING_OFFSTACK)
यंत्रlinkage __visible व्योम __sched schedule_user(व्योम)
अणु
	/*
	 * If we come here after a अक्रमom call to set_need_resched(),
	 * or we have been woken up remotely but the IPI has not yet arrived,
	 * we haven't yet निकासed the RCU idle mode. Do it here manually until
	 * we find a better solution.
	 *
	 * NB: There are buggy callers of this function.  Ideally we
	 * should warn अगर prev_state != CONTEXT_USER, but that will trigger
	 * too frequently to make sense yet.
	 */
	क्रमागत ctx_state prev_state = exception_enter();
	schedule();
	exception_निकास(prev_state);
पूर्ण
#पूर्ण_अगर

/**
 * schedule_preempt_disabled - called with preemption disabled
 *
 * Returns with preemption disabled. Note: preempt_count must be 1
 */
व्योम __sched schedule_preempt_disabled(व्योम)
अणु
	sched_preempt_enable_no_resched();
	schedule();
	preempt_disable();
पूर्ण

अटल व्योम __sched notrace preempt_schedule_common(व्योम)
अणु
	करो अणु
		/*
		 * Because the function tracer can trace preempt_count_sub()
		 * and it also uses preempt_enable/disable_notrace(), अगर
		 * NEED_RESCHED is set, the preempt_enable_notrace() called
		 * by the function tracer will call this function again and
		 * cause infinite recursion.
		 *
		 * Preemption must be disabled here beक्रमe the function
		 * tracer can trace. Break up preempt_disable() पूर्णांकo two
		 * calls. One to disable preemption without fear of being
		 * traced. The other to still record the preemption latency,
		 * which can also be traced by the function tracer.
		 */
		preempt_disable_notrace();
		preempt_latency_start(1);
		__schedule(true);
		preempt_latency_stop(1);
		preempt_enable_no_resched_notrace();

		/*
		 * Check again in हाल we missed a preemption opportunity
		 * between schedule and now.
		 */
	पूर्ण जबतक (need_resched());
पूर्ण

#अगर_घोषित CONFIG_PREEMPTION
/*
 * This is the entry poपूर्णांक to schedule() from in-kernel preemption
 * off of preempt_enable.
 */
यंत्रlinkage __visible व्योम __sched notrace preempt_schedule(व्योम)
अणु
	/*
	 * If there is a non-zero preempt_count or पूर्णांकerrupts are disabled,
	 * we करो not want to preempt the current task. Just वापस..
	 */
	अगर (likely(!preemptible()))
		वापस;

	preempt_schedule_common();
पूर्ण
NOKPROBE_SYMBOL(preempt_schedule);
EXPORT_SYMBOL(preempt_schedule);

#अगर_घोषित CONFIG_PREEMPT_DYNAMIC
DEFINE_STATIC_CALL(preempt_schedule, __preempt_schedule_func);
EXPORT_STATIC_CALL_TRAMP(preempt_schedule);
#पूर्ण_अगर


/**
 * preempt_schedule_notrace - preempt_schedule called by tracing
 *
 * The tracing infraकाष्ठाure uses preempt_enable_notrace to prevent
 * recursion and tracing preempt enabling caused by the tracing
 * infraकाष्ठाure itself. But as tracing can happen in areas coming
 * from userspace or just about to enter userspace, a preempt enable
 * can occur beक्रमe user_निकास() is called. This will cause the scheduler
 * to be called when the प्रणाली is still in usermode.
 *
 * To prevent this, the preempt_enable_notrace will use this function
 * instead of preempt_schedule() to निकास user context अगर needed beक्रमe
 * calling the scheduler.
 */
यंत्रlinkage __visible व्योम __sched notrace preempt_schedule_notrace(व्योम)
अणु
	क्रमागत ctx_state prev_ctx;

	अगर (likely(!preemptible()))
		वापस;

	करो अणु
		/*
		 * Because the function tracer can trace preempt_count_sub()
		 * and it also uses preempt_enable/disable_notrace(), अगर
		 * NEED_RESCHED is set, the preempt_enable_notrace() called
		 * by the function tracer will call this function again and
		 * cause infinite recursion.
		 *
		 * Preemption must be disabled here beक्रमe the function
		 * tracer can trace. Break up preempt_disable() पूर्णांकo two
		 * calls. One to disable preemption without fear of being
		 * traced. The other to still record the preemption latency,
		 * which can also be traced by the function tracer.
		 */
		preempt_disable_notrace();
		preempt_latency_start(1);
		/*
		 * Needs preempt disabled in हाल user_निकास() is traced
		 * and the tracer calls preempt_enable_notrace() causing
		 * an infinite recursion.
		 */
		prev_ctx = exception_enter();
		__schedule(true);
		exception_निकास(prev_ctx);

		preempt_latency_stop(1);
		preempt_enable_no_resched_notrace();
	पूर्ण जबतक (need_resched());
पूर्ण
EXPORT_SYMBOL_GPL(preempt_schedule_notrace);

#अगर_घोषित CONFIG_PREEMPT_DYNAMIC
DEFINE_STATIC_CALL(preempt_schedule_notrace, __preempt_schedule_notrace_func);
EXPORT_STATIC_CALL_TRAMP(preempt_schedule_notrace);
#पूर्ण_अगर

#पूर्ण_अगर /* CONFIG_PREEMPTION */

#अगर_घोषित CONFIG_PREEMPT_DYNAMIC

#समावेश <linux/entry-common.h>

/*
 * SC:cond_resched
 * SC:might_resched
 * SC:preempt_schedule
 * SC:preempt_schedule_notrace
 * SC:irqentry_निकास_cond_resched
 *
 *
 * NONE:
 *   cond_resched               <- __cond_resched
 *   might_resched              <- RET0
 *   preempt_schedule           <- NOP
 *   preempt_schedule_notrace   <- NOP
 *   irqentry_निकास_cond_resched <- NOP
 *
 * VOLUNTARY:
 *   cond_resched               <- __cond_resched
 *   might_resched              <- __cond_resched
 *   preempt_schedule           <- NOP
 *   preempt_schedule_notrace   <- NOP
 *   irqentry_निकास_cond_resched <- NOP
 *
 * FULL:
 *   cond_resched               <- RET0
 *   might_resched              <- RET0
 *   preempt_schedule           <- preempt_schedule
 *   preempt_schedule_notrace   <- preempt_schedule_notrace
 *   irqentry_निकास_cond_resched <- irqentry_निकास_cond_resched
 */

क्रमागत अणु
	preempt_dynamic_none = 0,
	preempt_dynamic_voluntary,
	preempt_dynamic_full,
पूर्ण;

पूर्णांक preempt_dynamic_mode = preempt_dynamic_full;

पूर्णांक sched_dynamic_mode(स्थिर अक्षर *str)
अणु
	अगर (!म_भेद(str, "none"))
		वापस preempt_dynamic_none;

	अगर (!म_भेद(str, "voluntary"))
		वापस preempt_dynamic_voluntary;

	अगर (!म_भेद(str, "full"))
		वापस preempt_dynamic_full;

	वापस -EINVAL;
पूर्ण

व्योम sched_dynamic_update(पूर्णांक mode)
अणु
	/*
	 * Aव्योम अणुNONE,VOLUNTARYपूर्ण -> FULL transitions from ever ending up in
	 * the ZERO state, which is invalid.
	 */
	अटल_call_update(cond_resched, __cond_resched);
	अटल_call_update(might_resched, __cond_resched);
	अटल_call_update(preempt_schedule, __preempt_schedule_func);
	अटल_call_update(preempt_schedule_notrace, __preempt_schedule_notrace_func);
	अटल_call_update(irqentry_निकास_cond_resched, irqentry_निकास_cond_resched);

	चयन (mode) अणु
	हाल preempt_dynamic_none:
		अटल_call_update(cond_resched, __cond_resched);
		अटल_call_update(might_resched, (व्योम *)&__अटल_call_वापस0);
		अटल_call_update(preempt_schedule, शून्य);
		अटल_call_update(preempt_schedule_notrace, शून्य);
		अटल_call_update(irqentry_निकास_cond_resched, शून्य);
		pr_info("Dynamic Preempt: none\n");
		अवरोध;

	हाल preempt_dynamic_voluntary:
		अटल_call_update(cond_resched, __cond_resched);
		अटल_call_update(might_resched, __cond_resched);
		अटल_call_update(preempt_schedule, शून्य);
		अटल_call_update(preempt_schedule_notrace, शून्य);
		अटल_call_update(irqentry_निकास_cond_resched, शून्य);
		pr_info("Dynamic Preempt: voluntary\n");
		अवरोध;

	हाल preempt_dynamic_full:
		अटल_call_update(cond_resched, (व्योम *)&__अटल_call_वापस0);
		अटल_call_update(might_resched, (व्योम *)&__अटल_call_वापस0);
		अटल_call_update(preempt_schedule, __preempt_schedule_func);
		अटल_call_update(preempt_schedule_notrace, __preempt_schedule_notrace_func);
		अटल_call_update(irqentry_निकास_cond_resched, irqentry_निकास_cond_resched);
		pr_info("Dynamic Preempt: full\n");
		अवरोध;
	पूर्ण

	preempt_dynamic_mode = mode;
पूर्ण

अटल पूर्णांक __init setup_preempt_mode(अक्षर *str)
अणु
	पूर्णांक mode = sched_dynamic_mode(str);
	अगर (mode < 0) अणु
		pr_warn("Dynamic Preempt: unsupported mode: %s\n", str);
		वापस 1;
	पूर्ण

	sched_dynamic_update(mode);
	वापस 0;
पूर्ण
__setup("preempt=", setup_preempt_mode);

#पूर्ण_अगर /* CONFIG_PREEMPT_DYNAMIC */

/*
 * This is the entry poपूर्णांक to schedule() from kernel preemption
 * off of irq context.
 * Note, that this is called and वापस with irqs disabled. This will
 * protect us against recursive calling from irq.
 */
यंत्रlinkage __visible व्योम __sched preempt_schedule_irq(व्योम)
अणु
	क्रमागत ctx_state prev_state;

	/* Catch callers which need to be fixed */
	BUG_ON(preempt_count() || !irqs_disabled());

	prev_state = exception_enter();

	करो अणु
		preempt_disable();
		local_irq_enable();
		__schedule(true);
		local_irq_disable();
		sched_preempt_enable_no_resched();
	पूर्ण जबतक (need_resched());

	exception_निकास(prev_state);
पूर्ण

पूर्णांक शेष_wake_function(रुको_queue_entry_t *curr, अचिन्हित mode, पूर्णांक wake_flags,
			  व्योम *key)
अणु
	WARN_ON_ONCE(IS_ENABLED(CONFIG_SCHED_DEBUG) && wake_flags & ~WF_SYNC);
	वापस try_to_wake_up(curr->निजी, mode, wake_flags);
पूर्ण
EXPORT_SYMBOL(शेष_wake_function);

#अगर_घोषित CONFIG_RT_MUTEXES

अटल अंतरभूत पूर्णांक __rt_effective_prio(काष्ठा task_काष्ठा *pi_task, पूर्णांक prio)
अणु
	अगर (pi_task)
		prio = min(prio, pi_task->prio);

	वापस prio;
पूर्ण

अटल अंतरभूत पूर्णांक rt_effective_prio(काष्ठा task_काष्ठा *p, पूर्णांक prio)
अणु
	काष्ठा task_काष्ठा *pi_task = rt_mutex_get_top_task(p);

	वापस __rt_effective_prio(pi_task, prio);
पूर्ण

/*
 * rt_mutex_setprio - set the current priority of a task
 * @p: task to boost
 * @pi_task: करोnor task
 *
 * This function changes the 'effective' priority of a task. It करोes
 * not touch ->normal_prio like __setscheduler().
 *
 * Used by the rt_mutex code to implement priority inheritance
 * logic. Call site only calls अगर the priority of the task changed.
 */
व्योम rt_mutex_setprio(काष्ठा task_काष्ठा *p, काष्ठा task_काष्ठा *pi_task)
अणु
	पूर्णांक prio, oldprio, queued, running, queue_flag =
		DEQUEUE_SAVE | DEQUEUE_MOVE | DEQUEUE_NOCLOCK;
	स्थिर काष्ठा sched_class *prev_class;
	काष्ठा rq_flags rf;
	काष्ठा rq *rq;

	/* XXX used to be रुकोer->prio, not रुकोer->task->prio */
	prio = __rt_effective_prio(pi_task, p->normal_prio);

	/*
	 * If nothing changed; bail early.
	 */
	अगर (p->pi_top_task == pi_task && prio == p->prio && !dl_prio(prio))
		वापस;

	rq = __task_rq_lock(p, &rf);
	update_rq_घड़ी(rq);
	/*
	 * Set under pi_lock && rq->lock, such that the value can be used under
	 * either lock.
	 *
	 * Note that there is loads of tricky to make this poपूर्णांकer cache work
	 * right. rt_mutex_slowunlock()+rt_mutex_postunlock() work together to
	 * ensure a task is de-boosted (pi_task is set to शून्य) beक्रमe the
	 * task is allowed to run again (and can निकास). This ensures the poपूर्णांकer
	 * poपूर्णांकs to a blocked task -- which guarantees the task is present.
	 */
	p->pi_top_task = pi_task;

	/*
	 * For FIFO/RR we only need to set prio, अगर that matches we're करोne.
	 */
	अगर (prio == p->prio && !dl_prio(prio))
		जाओ out_unlock;

	/*
	 * Idle task boosting is a nono in general. There is one
	 * exception, when PREEMPT_RT and NOHZ is active:
	 *
	 * The idle task calls get_next_समयr_पूर्णांकerrupt() and holds
	 * the समयr wheel base->lock on the CPU and another CPU wants
	 * to access the समयr (probably to cancel it). We can safely
	 * ignore the boosting request, as the idle CPU runs this code
	 * with पूर्णांकerrupts disabled and will complete the lock
	 * रक्षित section without being पूर्णांकerrupted. So there is no
	 * real need to boost.
	 */
	अगर (unlikely(p == rq->idle)) अणु
		WARN_ON(p != rq->curr);
		WARN_ON(p->pi_blocked_on);
		जाओ out_unlock;
	पूर्ण

	trace_sched_pi_setprio(p, pi_task);
	oldprio = p->prio;

	अगर (oldprio == prio)
		queue_flag &= ~DEQUEUE_MOVE;

	prev_class = p->sched_class;
	queued = task_on_rq_queued(p);
	running = task_current(rq, p);
	अगर (queued)
		dequeue_task(rq, p, queue_flag);
	अगर (running)
		put_prev_task(rq, p);

	/*
	 * Boosting condition are:
	 * 1. -rt task is running and holds mutex A
	 *      --> -dl task blocks on mutex A
	 *
	 * 2. -dl task is running and holds mutex A
	 *      --> -dl task blocks on mutex A and could preempt the
	 *          running task
	 */
	अगर (dl_prio(prio)) अणु
		अगर (!dl_prio(p->normal_prio) ||
		    (pi_task && dl_prio(pi_task->prio) &&
		     dl_entity_preempt(&pi_task->dl, &p->dl))) अणु
			p->dl.pi_se = pi_task->dl.pi_se;
			queue_flag |= ENQUEUE_REPLENISH;
		पूर्ण अन्यथा अणु
			p->dl.pi_se = &p->dl;
		पूर्ण
		p->sched_class = &dl_sched_class;
	पूर्ण अन्यथा अगर (rt_prio(prio)) अणु
		अगर (dl_prio(oldprio))
			p->dl.pi_se = &p->dl;
		अगर (oldprio < prio)
			queue_flag |= ENQUEUE_HEAD;
		p->sched_class = &rt_sched_class;
	पूर्ण अन्यथा अणु
		अगर (dl_prio(oldprio))
			p->dl.pi_se = &p->dl;
		अगर (rt_prio(oldprio))
			p->rt.समयout = 0;
		p->sched_class = &fair_sched_class;
	पूर्ण

	p->prio = prio;

	अगर (queued)
		enqueue_task(rq, p, queue_flag);
	अगर (running)
		set_next_task(rq, p);

	check_class_changed(rq, p, prev_class, oldprio);
out_unlock:
	/* Aव्योम rq from going away on us: */
	preempt_disable();

	rq_unpin_lock(rq, &rf);
	__balance_callbacks(rq);
	raw_spin_unlock(&rq->lock);

	preempt_enable();
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक rt_effective_prio(काष्ठा task_काष्ठा *p, पूर्णांक prio)
अणु
	वापस prio;
पूर्ण
#पूर्ण_अगर

व्योम set_user_nice(काष्ठा task_काष्ठा *p, दीर्घ nice)
अणु
	bool queued, running;
	पूर्णांक old_prio;
	काष्ठा rq_flags rf;
	काष्ठा rq *rq;

	अगर (task_nice(p) == nice || nice < MIN_NICE || nice > MAX_NICE)
		वापस;
	/*
	 * We have to be careful, अगर called from sys_setpriority(),
	 * the task might be in the middle of scheduling on another CPU.
	 */
	rq = task_rq_lock(p, &rf);
	update_rq_घड़ी(rq);

	/*
	 * The RT priorities are set via sched_setscheduler(), but we still
	 * allow the 'normal' nice value to be set - but as expected
	 * it won't have any effect on scheduling until the task is
	 * SCHED_DEADLINE, SCHED_FIFO or SCHED_RR:
	 */
	अगर (task_has_dl_policy(p) || task_has_rt_policy(p)) अणु
		p->अटल_prio = NICE_TO_PRIO(nice);
		जाओ out_unlock;
	पूर्ण
	queued = task_on_rq_queued(p);
	running = task_current(rq, p);
	अगर (queued)
		dequeue_task(rq, p, DEQUEUE_SAVE | DEQUEUE_NOCLOCK);
	अगर (running)
		put_prev_task(rq, p);

	p->अटल_prio = NICE_TO_PRIO(nice);
	set_load_weight(p, true);
	old_prio = p->prio;
	p->prio = effective_prio(p);

	अगर (queued)
		enqueue_task(rq, p, ENQUEUE_RESTORE | ENQUEUE_NOCLOCK);
	अगर (running)
		set_next_task(rq, p);

	/*
	 * If the task increased its priority or is running and
	 * lowered its priority, then reschedule its CPU:
	 */
	p->sched_class->prio_changed(rq, p, old_prio);

out_unlock:
	task_rq_unlock(rq, p, &rf);
पूर्ण
EXPORT_SYMBOL(set_user_nice);

/*
 * can_nice - check अगर a task can reduce its nice value
 * @p: task
 * @nice: nice value
 */
पूर्णांक can_nice(स्थिर काष्ठा task_काष्ठा *p, स्थिर पूर्णांक nice)
अणु
	/* Convert nice value [19,-20] to rlimit style value [1,40]: */
	पूर्णांक nice_rlim = nice_to_rlimit(nice);

	वापस (nice_rlim <= task_rlimit(p, RLIMIT_NICE) ||
		capable(CAP_SYS_NICE));
पूर्ण

#अगर_घोषित __ARCH_WANT_SYS_NICE

/*
 * sys_nice - change the priority of the current process.
 * @increment: priority increment
 *
 * sys_setpriority is a more generic, but much slower function that
 * करोes similar things.
 */
SYSCALL_DEFINE1(nice, पूर्णांक, increment)
अणु
	दीर्घ nice, retval;

	/*
	 * Setpriority might change our priority at the same moment.
	 * We करोn't have to worry. Conceptually one call occurs first
	 * and we have a single winner.
	 */
	increment = clamp(increment, -NICE_WIDTH, NICE_WIDTH);
	nice = task_nice(current) + increment;

	nice = clamp_val(nice, MIN_NICE, MAX_NICE);
	अगर (increment < 0 && !can_nice(current, nice))
		वापस -EPERM;

	retval = security_task_setnice(current, nice);
	अगर (retval)
		वापस retval;

	set_user_nice(current, nice);
	वापस 0;
पूर्ण

#पूर्ण_अगर

/**
 * task_prio - वापस the priority value of a given task.
 * @p: the task in question.
 *
 * Return: The priority value as seen by users in /proc.
 *
 * sched policy         वापस value   kernel prio    user prio/nice
 *
 * normal, batch, idle     [0 ... 39]  [100 ... 139]          0/[-20 ... 19]
 * fअगरo, rr             [-2 ... -100]     [98 ... 0]  [1 ... 99]
 * deadline                     -101             -1           0
 */
पूर्णांक task_prio(स्थिर काष्ठा task_काष्ठा *p)
अणु
	वापस p->prio - MAX_RT_PRIO;
पूर्ण

/**
 * idle_cpu - is a given CPU idle currently?
 * @cpu: the processor in question.
 *
 * Return: 1 अगर the CPU is currently idle. 0 otherwise.
 */
पूर्णांक idle_cpu(पूर्णांक cpu)
अणु
	काष्ठा rq *rq = cpu_rq(cpu);

	अगर (rq->curr != rq->idle)
		वापस 0;

	अगर (rq->nr_running)
		वापस 0;

#अगर_घोषित CONFIG_SMP
	अगर (rq->ttwu_pending)
		वापस 0;
#पूर्ण_अगर

	वापस 1;
पूर्ण

/**
 * available_idle_cpu - is a given CPU idle क्रम enqueuing work.
 * @cpu: the CPU in question.
 *
 * Return: 1 अगर the CPU is currently idle. 0 otherwise.
 */
पूर्णांक available_idle_cpu(पूर्णांक cpu)
अणु
	अगर (!idle_cpu(cpu))
		वापस 0;

	अगर (vcpu_is_preempted(cpu))
		वापस 0;

	वापस 1;
पूर्ण

/**
 * idle_task - वापस the idle task क्रम a given CPU.
 * @cpu: the processor in question.
 *
 * Return: The idle task क्रम the CPU @cpu.
 */
काष्ठा task_काष्ठा *idle_task(पूर्णांक cpu)
अणु
	वापस cpu_rq(cpu)->idle;
पूर्ण

#अगर_घोषित CONFIG_SMP
/*
 * This function computes an effective utilization क्रम the given CPU, to be
 * used क्रम frequency selection given the linear relation: f = u * f_max.
 *
 * The scheduler tracks the following metrics:
 *
 *   cpu_util_अणुcfs,rt,dl,irqपूर्ण()
 *   cpu_bw_dl()
 *
 * Where the cfs,rt and dl util numbers are tracked with the same metric and
 * synchronized winकरोws and are thus directly comparable.
 *
 * The cfs,rt,dl utilization are the running बार measured with rq->घड़ी_प्रकारask
 * which excludes things like IRQ and steal-समय. These latter are then accrued
 * in the irq utilization.
 *
 * The DL bandwidth number otoh is not a measured metric but a value computed
 * based on the task model parameters and gives the minimal utilization
 * required to meet deadlines.
 */
अचिन्हित दीर्घ effective_cpu_util(पूर्णांक cpu, अचिन्हित दीर्घ util_cfs,
				 अचिन्हित दीर्घ max, क्रमागत cpu_util_type type,
				 काष्ठा task_काष्ठा *p)
अणु
	अचिन्हित दीर्घ dl_util, util, irq;
	काष्ठा rq *rq = cpu_rq(cpu);

	अगर (!uclamp_is_used() &&
	    type == FREQUENCY_UTIL && rt_rq_is_runnable(&rq->rt)) अणु
		वापस max;
	पूर्ण

	/*
	 * Early check to see अगर IRQ/steal समय saturates the CPU, can be
	 * because of inaccuracies in how we track these -- see
	 * update_irq_load_avg().
	 */
	irq = cpu_util_irq(rq);
	अगर (unlikely(irq >= max))
		वापस max;

	/*
	 * Because the समय spend on RT/DL tasks is visible as 'lost' समय to
	 * CFS tasks and we use the same metric to track the effective
	 * utilization (PELT winकरोws are synchronized) we can directly add them
	 * to obtain the CPU's actual utilization.
	 *
	 * CFS and RT utilization can be boosted or capped, depending on
	 * utilization clamp स्थिरraपूर्णांकs requested by currently RUNNABLE
	 * tasks.
	 * When there are no CFS RUNNABLE tasks, clamps are released and
	 * frequency will be gracefully reduced with the utilization decay.
	 */
	util = util_cfs + cpu_util_rt(rq);
	अगर (type == FREQUENCY_UTIL)
		util = uclamp_rq_util_with(rq, util, p);

	dl_util = cpu_util_dl(rq);

	/*
	 * For frequency selection we करो not make cpu_util_dl() a permanent part
	 * of this sum because we want to use cpu_bw_dl() later on, but we need
	 * to check अगर the CFS+RT+DL sum is saturated (ie. no idle समय) such
	 * that we select f_max when there is no idle समय.
	 *
	 * NOTE: numerical errors or stop class might cause us to not quite hit
	 * saturation when we should -- something क्रम later.
	 */
	अगर (util + dl_util >= max)
		वापस max;

	/*
	 * OTOH, क्रम energy computation we need the estimated running समय, so
	 * include util_dl and ignore dl_bw.
	 */
	अगर (type == ENERGY_UTIL)
		util += dl_util;

	/*
	 * There is still idle समय; further improve the number by using the
	 * irq metric. Because IRQ/steal समय is hidden from the task घड़ी we
	 * need to scale the task numbers:
	 *
	 *              max - irq
	 *   U' = irq + --------- * U
	 *                 max
	 */
	util = scale_irq_capacity(util, irq, max);
	util += irq;

	/*
	 * Bandwidth required by DEADLINE must always be granted जबतक, क्रम
	 * FAIR and RT, we use blocked utilization of IDLE CPUs as a mechanism
	 * to gracefully reduce the frequency when no tasks show up क्रम दीर्घer
	 * periods of समय.
	 *
	 * Ideally we would like to set bw_dl as min/guaranteed freq and util +
	 * bw_dl as requested freq. However, cpufreq is not yet पढ़ोy क्रम such
	 * an पूर्णांकerface. So, we only करो the latter क्रम now.
	 */
	अगर (type == FREQUENCY_UTIL)
		util += cpu_bw_dl(rq);

	वापस min(max, util);
पूर्ण

अचिन्हित दीर्घ sched_cpu_util(पूर्णांक cpu, अचिन्हित दीर्घ max)
अणु
	वापस effective_cpu_util(cpu, cpu_util_cfs(cpu_rq(cpu)), max,
				  ENERGY_UTIL, शून्य);
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

/**
 * find_process_by_pid - find a process with a matching PID value.
 * @pid: the pid in question.
 *
 * The task of @pid, अगर found. %शून्य otherwise.
 */
अटल काष्ठा task_काष्ठा *find_process_by_pid(pid_t pid)
अणु
	वापस pid ? find_task_by_vpid(pid) : current;
पूर्ण

/*
 * sched_setparam() passes in -1 क्रम its policy, to let the functions
 * it calls know not to change it.
 */
#घोषणा SETPARAM_POLICY	-1

अटल व्योम __setscheduler_params(काष्ठा task_काष्ठा *p,
		स्थिर काष्ठा sched_attr *attr)
अणु
	पूर्णांक policy = attr->sched_policy;

	अगर (policy == SETPARAM_POLICY)
		policy = p->policy;

	p->policy = policy;

	अगर (dl_policy(policy))
		__setparam_dl(p, attr);
	अन्यथा अगर (fair_policy(policy))
		p->अटल_prio = NICE_TO_PRIO(attr->sched_nice);

	/*
	 * __sched_setscheduler() ensures attr->sched_priority == 0 when
	 * !rt_policy. Always setting this ensures that things like
	 * getparam()/getattr() करोn't report silly values क्रम !rt tasks.
	 */
	p->rt_priority = attr->sched_priority;
	p->normal_prio = normal_prio(p);
	set_load_weight(p, true);
पूर्ण

/* Actually करो priority change: must hold pi & rq lock. */
अटल व्योम __setscheduler(काष्ठा rq *rq, काष्ठा task_काष्ठा *p,
			   स्थिर काष्ठा sched_attr *attr, bool keep_boost)
अणु
	/*
	 * If params can't change scheduling class changes aren't allowed
	 * either.
	 */
	अगर (attr->sched_flags & SCHED_FLAG_KEEP_PARAMS)
		वापस;

	__setscheduler_params(p, attr);

	/*
	 * Keep a potential priority boosting अगर called from
	 * sched_setscheduler().
	 */
	p->prio = normal_prio(p);
	अगर (keep_boost)
		p->prio = rt_effective_prio(p, p->prio);

	अगर (dl_prio(p->prio))
		p->sched_class = &dl_sched_class;
	अन्यथा अगर (rt_prio(p->prio))
		p->sched_class = &rt_sched_class;
	अन्यथा
		p->sched_class = &fair_sched_class;
पूर्ण

/*
 * Check the target process has a UID that matches the current process's:
 */
अटल bool check_same_owner(काष्ठा task_काष्ठा *p)
अणु
	स्थिर काष्ठा cred *cred = current_cred(), *pcred;
	bool match;

	rcu_पढ़ो_lock();
	pcred = __task_cred(p);
	match = (uid_eq(cred->euid, pcred->euid) ||
		 uid_eq(cred->euid, pcred->uid));
	rcu_पढ़ो_unlock();
	वापस match;
पूर्ण

अटल पूर्णांक __sched_setscheduler(काष्ठा task_काष्ठा *p,
				स्थिर काष्ठा sched_attr *attr,
				bool user, bool pi)
अणु
	पूर्णांक newprio = dl_policy(attr->sched_policy) ? MAX_DL_PRIO - 1 :
		      MAX_RT_PRIO - 1 - attr->sched_priority;
	पूर्णांक retval, oldprio, oldpolicy = -1, queued, running;
	पूर्णांक new_effective_prio, policy = attr->sched_policy;
	स्थिर काष्ठा sched_class *prev_class;
	काष्ठा callback_head *head;
	काष्ठा rq_flags rf;
	पूर्णांक reset_on_विभाजन;
	पूर्णांक queue_flags = DEQUEUE_SAVE | DEQUEUE_MOVE | DEQUEUE_NOCLOCK;
	काष्ठा rq *rq;

	/* The pi code expects पूर्णांकerrupts enabled */
	BUG_ON(pi && in_पूर्णांकerrupt());
recheck:
	/* Double check policy once rq lock held: */
	अगर (policy < 0) अणु
		reset_on_विभाजन = p->sched_reset_on_विभाजन;
		policy = oldpolicy = p->policy;
	पूर्ण अन्यथा अणु
		reset_on_विभाजन = !!(attr->sched_flags & SCHED_FLAG_RESET_ON_FORK);

		अगर (!valid_policy(policy))
			वापस -EINVAL;
	पूर्ण

	अगर (attr->sched_flags & ~(SCHED_FLAG_ALL | SCHED_FLAG_SUGOV))
		वापस -EINVAL;

	/*
	 * Valid priorities क्रम SCHED_FIFO and SCHED_RR are
	 * 1..MAX_RT_PRIO-1, valid priority क्रम SCHED_NORMAL,
	 * SCHED_BATCH and SCHED_IDLE is 0.
	 */
	अगर (attr->sched_priority > MAX_RT_PRIO-1)
		वापस -EINVAL;
	अगर ((dl_policy(policy) && !__checkparam_dl(attr)) ||
	    (rt_policy(policy) != (attr->sched_priority != 0)))
		वापस -EINVAL;

	/*
	 * Allow unprivileged RT tasks to decrease priority:
	 */
	अगर (user && !capable(CAP_SYS_NICE)) अणु
		अगर (fair_policy(policy)) अणु
			अगर (attr->sched_nice < task_nice(p) &&
			    !can_nice(p, attr->sched_nice))
				वापस -EPERM;
		पूर्ण

		अगर (rt_policy(policy)) अणु
			अचिन्हित दीर्घ rlim_rtprio =
					task_rlimit(p, RLIMIT_RTPRIO);

			/* Can't set/change the rt policy: */
			अगर (policy != p->policy && !rlim_rtprio)
				वापस -EPERM;

			/* Can't increase priority: */
			अगर (attr->sched_priority > p->rt_priority &&
			    attr->sched_priority > rlim_rtprio)
				वापस -EPERM;
		पूर्ण

		 /*
		  * Can't set/change SCHED_DEADLINE policy at all क्रम now
		  * (safest behavior); in the future we would like to allow
		  * unprivileged DL tasks to increase their relative deadline
		  * or reduce their runसमय (both ways reducing utilization)
		  */
		अगर (dl_policy(policy))
			वापस -EPERM;

		/*
		 * Treat SCHED_IDLE as nice 20. Only allow a चयन to
		 * SCHED_NORMAL अगर the RLIMIT_NICE would normally permit it.
		 */
		अगर (task_has_idle_policy(p) && !idle_policy(policy)) अणु
			अगर (!can_nice(p, task_nice(p)))
				वापस -EPERM;
		पूर्ण

		/* Can't change other user's priorities: */
		अगर (!check_same_owner(p))
			वापस -EPERM;

		/* Normal users shall not reset the sched_reset_on_विभाजन flag: */
		अगर (p->sched_reset_on_विभाजन && !reset_on_विभाजन)
			वापस -EPERM;
	पूर्ण

	अगर (user) अणु
		अगर (attr->sched_flags & SCHED_FLAG_SUGOV)
			वापस -EINVAL;

		retval = security_task_setscheduler(p);
		अगर (retval)
			वापस retval;
	पूर्ण

	/* Update task specअगरic "requested" clamps */
	अगर (attr->sched_flags & SCHED_FLAG_UTIL_CLAMP) अणु
		retval = uclamp_validate(p, attr);
		अगर (retval)
			वापस retval;
	पूर्ण

	अगर (pi)
		cpuset_पढ़ो_lock();

	/*
	 * Make sure no PI-रुकोers arrive (or leave) जबतक we are
	 * changing the priority of the task:
	 *
	 * To be able to change p->policy safely, the appropriate
	 * runqueue lock must be held.
	 */
	rq = task_rq_lock(p, &rf);
	update_rq_घड़ी(rq);

	/*
	 * Changing the policy of the stop thपढ़ोs its a very bad idea:
	 */
	अगर (p == rq->stop) अणु
		retval = -EINVAL;
		जाओ unlock;
	पूर्ण

	/*
	 * If not changing anything there's no need to proceed further,
	 * but store a possible modअगरication of reset_on_विभाजन.
	 */
	अगर (unlikely(policy == p->policy)) अणु
		अगर (fair_policy(policy) && attr->sched_nice != task_nice(p))
			जाओ change;
		अगर (rt_policy(policy) && attr->sched_priority != p->rt_priority)
			जाओ change;
		अगर (dl_policy(policy) && dl_param_changed(p, attr))
			जाओ change;
		अगर (attr->sched_flags & SCHED_FLAG_UTIL_CLAMP)
			जाओ change;

		p->sched_reset_on_विभाजन = reset_on_विभाजन;
		retval = 0;
		जाओ unlock;
	पूर्ण
change:

	अगर (user) अणु
#अगर_घोषित CONFIG_RT_GROUP_SCHED
		/*
		 * Do not allow realसमय tasks पूर्णांकo groups that have no runसमय
		 * asचिन्हित.
		 */
		अगर (rt_bandwidth_enabled() && rt_policy(policy) &&
				task_group(p)->rt_bandwidth.rt_runसमय == 0 &&
				!task_group_is_स्वतःgroup(task_group(p))) अणु
			retval = -EPERM;
			जाओ unlock;
		पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_SMP
		अगर (dl_bandwidth_enabled() && dl_policy(policy) &&
				!(attr->sched_flags & SCHED_FLAG_SUGOV)) अणु
			cpumask_t *span = rq->rd->span;

			/*
			 * Don't allow tasks with an affinity mask smaller than
			 * the entire root_करोमुख्य to become SCHED_DEADLINE. We
			 * will also fail अगर there's no bandwidth available.
			 */
			अगर (!cpumask_subset(span, p->cpus_ptr) ||
			    rq->rd->dl_bw.bw == 0) अणु
				retval = -EPERM;
				जाओ unlock;
			पूर्ण
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	/* Re-check policy now with rq lock held: */
	अगर (unlikely(oldpolicy != -1 && oldpolicy != p->policy)) अणु
		policy = oldpolicy = -1;
		task_rq_unlock(rq, p, &rf);
		अगर (pi)
			cpuset_पढ़ो_unlock();
		जाओ recheck;
	पूर्ण

	/*
	 * If setscheduling to SCHED_DEADLINE (or changing the parameters
	 * of a SCHED_DEADLINE task) we need to check अगर enough bandwidth
	 * is available.
	 */
	अगर ((dl_policy(policy) || dl_task(p)) && sched_dl_overflow(p, policy, attr)) अणु
		retval = -EBUSY;
		जाओ unlock;
	पूर्ण

	p->sched_reset_on_विभाजन = reset_on_विभाजन;
	oldprio = p->prio;

	अगर (pi) अणु
		/*
		 * Take priority boosted tasks पूर्णांकo account. If the new
		 * effective priority is unchanged, we just store the new
		 * normal parameters and करो not touch the scheduler class and
		 * the runqueue. This will be करोne when the task deboost
		 * itself.
		 */
		new_effective_prio = rt_effective_prio(p, newprio);
		अगर (new_effective_prio == oldprio)
			queue_flags &= ~DEQUEUE_MOVE;
	पूर्ण

	queued = task_on_rq_queued(p);
	running = task_current(rq, p);
	अगर (queued)
		dequeue_task(rq, p, queue_flags);
	अगर (running)
		put_prev_task(rq, p);

	prev_class = p->sched_class;

	__setscheduler(rq, p, attr, pi);
	__setscheduler_uclamp(p, attr);

	अगर (queued) अणु
		/*
		 * We enqueue to tail when the priority of a task is
		 * increased (user space view).
		 */
		अगर (oldprio < p->prio)
			queue_flags |= ENQUEUE_HEAD;

		enqueue_task(rq, p, queue_flags);
	पूर्ण
	अगर (running)
		set_next_task(rq, p);

	check_class_changed(rq, p, prev_class, oldprio);

	/* Aव्योम rq from going away on us: */
	preempt_disable();
	head = splice_balance_callbacks(rq);
	task_rq_unlock(rq, p, &rf);

	अगर (pi) अणु
		cpuset_पढ़ो_unlock();
		rt_mutex_adjust_pi(p);
	पूर्ण

	/* Run balance callbacks after we've adjusted the PI chain: */
	balance_callbacks(rq, head);
	preempt_enable();

	वापस 0;

unlock:
	task_rq_unlock(rq, p, &rf);
	अगर (pi)
		cpuset_पढ़ो_unlock();
	वापस retval;
पूर्ण

अटल पूर्णांक _sched_setscheduler(काष्ठा task_काष्ठा *p, पूर्णांक policy,
			       स्थिर काष्ठा sched_param *param, bool check)
अणु
	काष्ठा sched_attr attr = अणु
		.sched_policy   = policy,
		.sched_priority = param->sched_priority,
		.sched_nice	= PRIO_TO_NICE(p->अटल_prio),
	पूर्ण;

	/* Fixup the legacy SCHED_RESET_ON_FORK hack. */
	अगर ((policy != SETPARAM_POLICY) && (policy & SCHED_RESET_ON_FORK)) अणु
		attr.sched_flags |= SCHED_FLAG_RESET_ON_FORK;
		policy &= ~SCHED_RESET_ON_FORK;
		attr.sched_policy = policy;
	पूर्ण

	वापस __sched_setscheduler(p, &attr, check, true);
पूर्ण
/**
 * sched_setscheduler - change the scheduling policy and/or RT priority of a thपढ़ो.
 * @p: the task in question.
 * @policy: new policy.
 * @param: काष्ठाure containing the new RT priority.
 *
 * Use sched_set_fअगरo(), पढ़ो its comment.
 *
 * Return: 0 on success. An error code otherwise.
 *
 * NOTE that the task may be alपढ़ोy dead.
 */
पूर्णांक sched_setscheduler(काष्ठा task_काष्ठा *p, पूर्णांक policy,
		       स्थिर काष्ठा sched_param *param)
अणु
	वापस _sched_setscheduler(p, policy, param, true);
पूर्ण

पूर्णांक sched_setattr(काष्ठा task_काष्ठा *p, स्थिर काष्ठा sched_attr *attr)
अणु
	वापस __sched_setscheduler(p, attr, true, true);
पूर्ण

पूर्णांक sched_setattr_nocheck(काष्ठा task_काष्ठा *p, स्थिर काष्ठा sched_attr *attr)
अणु
	वापस __sched_setscheduler(p, attr, false, true);
पूर्ण

/**
 * sched_setscheduler_nocheck - change the scheduling policy and/or RT priority of a thपढ़ो from kernelspace.
 * @p: the task in question.
 * @policy: new policy.
 * @param: काष्ठाure containing the new RT priority.
 *
 * Just like sched_setscheduler, only करोn't bother checking अगर the
 * current context has permission.  For example, this is needed in
 * stop_machine(): we create temporary high priority worker thपढ़ोs,
 * but our caller might not have that capability.
 *
 * Return: 0 on success. An error code otherwise.
 */
पूर्णांक sched_setscheduler_nocheck(काष्ठा task_काष्ठा *p, पूर्णांक policy,
			       स्थिर काष्ठा sched_param *param)
अणु
	वापस _sched_setscheduler(p, policy, param, false);
पूर्ण

/*
 * SCHED_FIFO is a broken scheduler model; that is, it is fundamentally
 * incapable of resource management, which is the one thing an OS really should
 * be करोing.
 *
 * This is of course the reason it is limited to privileged users only.
 *
 * Worse still; it is fundamentally impossible to compose अटल priority
 * workloads. You cannot take two correctly working अटल prio workloads
 * and smash them together and still expect them to work.
 *
 * For this reason 'all' FIFO tasks the kernel creates are basically at:
 *
 *   MAX_RT_PRIO / 2
 *
 * The administrator _MUST_ configure the प्रणाली, the kernel simply करोesn't
 * know enough inक्रमmation to make a sensible choice.
 */
व्योम sched_set_fअगरo(काष्ठा task_काष्ठा *p)
अणु
	काष्ठा sched_param sp = अणु .sched_priority = MAX_RT_PRIO / 2 पूर्ण;
	WARN_ON_ONCE(sched_setscheduler_nocheck(p, SCHED_FIFO, &sp) != 0);
पूर्ण
EXPORT_SYMBOL_GPL(sched_set_fअगरo);

/*
 * For when you करोn't much care about FIFO, but want to be above SCHED_NORMAL.
 */
व्योम sched_set_fअगरo_low(काष्ठा task_काष्ठा *p)
अणु
	काष्ठा sched_param sp = अणु .sched_priority = 1 पूर्ण;
	WARN_ON_ONCE(sched_setscheduler_nocheck(p, SCHED_FIFO, &sp) != 0);
पूर्ण
EXPORT_SYMBOL_GPL(sched_set_fअगरo_low);

व्योम sched_set_normal(काष्ठा task_काष्ठा *p, पूर्णांक nice)
अणु
	काष्ठा sched_attr attr = अणु
		.sched_policy = SCHED_NORMAL,
		.sched_nice = nice,
	पूर्ण;
	WARN_ON_ONCE(sched_setattr_nocheck(p, &attr) != 0);
पूर्ण
EXPORT_SYMBOL_GPL(sched_set_normal);

अटल पूर्णांक
करो_sched_setscheduler(pid_t pid, पूर्णांक policy, काष्ठा sched_param __user *param)
अणु
	काष्ठा sched_param lparam;
	काष्ठा task_काष्ठा *p;
	पूर्णांक retval;

	अगर (!param || pid < 0)
		वापस -EINVAL;
	अगर (copy_from_user(&lparam, param, माप(काष्ठा sched_param)))
		वापस -EFAULT;

	rcu_पढ़ो_lock();
	retval = -ESRCH;
	p = find_process_by_pid(pid);
	अगर (likely(p))
		get_task_काष्ठा(p);
	rcu_पढ़ो_unlock();

	अगर (likely(p)) अणु
		retval = sched_setscheduler(p, policy, &lparam);
		put_task_काष्ठा(p);
	पूर्ण

	वापस retval;
पूर्ण

/*
 * Mimics kernel/events/core.c perf_copy_attr().
 */
अटल पूर्णांक sched_copy_attr(काष्ठा sched_attr __user *uattr, काष्ठा sched_attr *attr)
अणु
	u32 size;
	पूर्णांक ret;

	/* Zero the full काष्ठाure, so that a लघु copy will be nice: */
	स_रखो(attr, 0, माप(*attr));

	ret = get_user(size, &uattr->size);
	अगर (ret)
		वापस ret;

	/* ABI compatibility quirk: */
	अगर (!size)
		size = SCHED_ATTR_SIZE_VER0;
	अगर (size < SCHED_ATTR_SIZE_VER0 || size > PAGE_SIZE)
		जाओ err_size;

	ret = copy_काष्ठा_from_user(attr, माप(*attr), uattr, size);
	अगर (ret) अणु
		अगर (ret == -E2BIG)
			जाओ err_size;
		वापस ret;
	पूर्ण

	अगर ((attr->sched_flags & SCHED_FLAG_UTIL_CLAMP) &&
	    size < SCHED_ATTR_SIZE_VER1)
		वापस -EINVAL;

	/*
	 * XXX: Do we want to be lenient like existing syscalls; or करो we want
	 * to be strict and वापस an error on out-of-bounds values?
	 */
	attr->sched_nice = clamp(attr->sched_nice, MIN_NICE, MAX_NICE);

	वापस 0;

err_size:
	put_user(माप(*attr), &uattr->size);
	वापस -E2BIG;
पूर्ण

/**
 * sys_sched_setscheduler - set/change the scheduler policy and RT priority
 * @pid: the pid in question.
 * @policy: new policy.
 * @param: काष्ठाure containing the new RT priority.
 *
 * Return: 0 on success. An error code otherwise.
 */
SYSCALL_DEFINE3(sched_setscheduler, pid_t, pid, पूर्णांक, policy, काष्ठा sched_param __user *, param)
अणु
	अगर (policy < 0)
		वापस -EINVAL;

	वापस करो_sched_setscheduler(pid, policy, param);
पूर्ण

/**
 * sys_sched_setparam - set/change the RT priority of a thपढ़ो
 * @pid: the pid in question.
 * @param: काष्ठाure containing the new RT priority.
 *
 * Return: 0 on success. An error code otherwise.
 */
SYSCALL_DEFINE2(sched_setparam, pid_t, pid, काष्ठा sched_param __user *, param)
अणु
	वापस करो_sched_setscheduler(pid, SETPARAM_POLICY, param);
पूर्ण

/**
 * sys_sched_setattr - same as above, but with extended sched_attr
 * @pid: the pid in question.
 * @uattr: काष्ठाure containing the extended parameters.
 * @flags: क्रम future extension.
 */
SYSCALL_DEFINE3(sched_setattr, pid_t, pid, काष्ठा sched_attr __user *, uattr,
			       अचिन्हित पूर्णांक, flags)
अणु
	काष्ठा sched_attr attr;
	काष्ठा task_काष्ठा *p;
	पूर्णांक retval;

	अगर (!uattr || pid < 0 || flags)
		वापस -EINVAL;

	retval = sched_copy_attr(uattr, &attr);
	अगर (retval)
		वापस retval;

	अगर ((पूर्णांक)attr.sched_policy < 0)
		वापस -EINVAL;
	अगर (attr.sched_flags & SCHED_FLAG_KEEP_POLICY)
		attr.sched_policy = SETPARAM_POLICY;

	rcu_पढ़ो_lock();
	retval = -ESRCH;
	p = find_process_by_pid(pid);
	अगर (likely(p))
		get_task_काष्ठा(p);
	rcu_पढ़ो_unlock();

	अगर (likely(p)) अणु
		retval = sched_setattr(p, &attr);
		put_task_काष्ठा(p);
	पूर्ण

	वापस retval;
पूर्ण

/**
 * sys_sched_माला_लोcheduler - get the policy (scheduling class) of a thपढ़ो
 * @pid: the pid in question.
 *
 * Return: On success, the policy of the thपढ़ो. Otherwise, a negative error
 * code.
 */
SYSCALL_DEFINE1(sched_माला_लोcheduler, pid_t, pid)
अणु
	काष्ठा task_काष्ठा *p;
	पूर्णांक retval;

	अगर (pid < 0)
		वापस -EINVAL;

	retval = -ESRCH;
	rcu_पढ़ो_lock();
	p = find_process_by_pid(pid);
	अगर (p) अणु
		retval = security_task_माला_लोcheduler(p);
		अगर (!retval)
			retval = p->policy
				| (p->sched_reset_on_विभाजन ? SCHED_RESET_ON_FORK : 0);
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस retval;
पूर्ण

/**
 * sys_sched_getparam - get the RT priority of a thपढ़ो
 * @pid: the pid in question.
 * @param: काष्ठाure containing the RT priority.
 *
 * Return: On success, 0 and the RT priority is in @param. Otherwise, an error
 * code.
 */
SYSCALL_DEFINE2(sched_getparam, pid_t, pid, काष्ठा sched_param __user *, param)
अणु
	काष्ठा sched_param lp = अणु .sched_priority = 0 पूर्ण;
	काष्ठा task_काष्ठा *p;
	पूर्णांक retval;

	अगर (!param || pid < 0)
		वापस -EINVAL;

	rcu_पढ़ो_lock();
	p = find_process_by_pid(pid);
	retval = -ESRCH;
	अगर (!p)
		जाओ out_unlock;

	retval = security_task_माला_लोcheduler(p);
	अगर (retval)
		जाओ out_unlock;

	अगर (task_has_rt_policy(p))
		lp.sched_priority = p->rt_priority;
	rcu_पढ़ो_unlock();

	/*
	 * This one might sleep, we cannot करो it with a spinlock held ...
	 */
	retval = copy_to_user(param, &lp, माप(*param)) ? -EFAULT : 0;

	वापस retval;

out_unlock:
	rcu_पढ़ो_unlock();
	वापस retval;
पूर्ण

/*
 * Copy the kernel size attribute काष्ठाure (which might be larger
 * than what user-space knows about) to user-space.
 *
 * Note that all हालs are valid: user-space buffer can be larger or
 * smaller than the kernel-space buffer. The usual हाल is that both
 * have the same size.
 */
अटल पूर्णांक
sched_attr_copy_to_user(काष्ठा sched_attr __user *uattr,
			काष्ठा sched_attr *kattr,
			अचिन्हित पूर्णांक usize)
अणु
	अचिन्हित पूर्णांक ksize = माप(*kattr);

	अगर (!access_ok(uattr, usize))
		वापस -EFAULT;

	/*
	 * sched_getattr() ABI क्रमwards and backwards compatibility:
	 *
	 * If usize == ksize then we just copy everything to user-space and all is good.
	 *
	 * If usize < ksize then we only copy as much as user-space has space क्रम,
	 * this keeps ABI compatibility as well. We skip the rest.
	 *
	 * If usize > ksize then user-space is using a newer version of the ABI,
	 * which part the kernel करोesn't know about. Just ignore it - tooling can
	 * detect the kernel's knowledge of attributes from the attr->size value
	 * which is set to ksize in this हाल.
	 */
	kattr->size = min(usize, ksize);

	अगर (copy_to_user(uattr, kattr, kattr->size))
		वापस -EFAULT;

	वापस 0;
पूर्ण

/**
 * sys_sched_getattr - similar to sched_getparam, but with sched_attr
 * @pid: the pid in question.
 * @uattr: काष्ठाure containing the extended parameters.
 * @usize: माप(attr) क्रम fwd/bwd comp.
 * @flags: क्रम future extension.
 */
SYSCALL_DEFINE4(sched_getattr, pid_t, pid, काष्ठा sched_attr __user *, uattr,
		अचिन्हित पूर्णांक, usize, अचिन्हित पूर्णांक, flags)
अणु
	काष्ठा sched_attr kattr = अणु पूर्ण;
	काष्ठा task_काष्ठा *p;
	पूर्णांक retval;

	अगर (!uattr || pid < 0 || usize > PAGE_SIZE ||
	    usize < SCHED_ATTR_SIZE_VER0 || flags)
		वापस -EINVAL;

	rcu_पढ़ो_lock();
	p = find_process_by_pid(pid);
	retval = -ESRCH;
	अगर (!p)
		जाओ out_unlock;

	retval = security_task_माला_लोcheduler(p);
	अगर (retval)
		जाओ out_unlock;

	kattr.sched_policy = p->policy;
	अगर (p->sched_reset_on_विभाजन)
		kattr.sched_flags |= SCHED_FLAG_RESET_ON_FORK;
	अगर (task_has_dl_policy(p))
		__getparam_dl(p, &kattr);
	अन्यथा अगर (task_has_rt_policy(p))
		kattr.sched_priority = p->rt_priority;
	अन्यथा
		kattr.sched_nice = task_nice(p);

#अगर_घोषित CONFIG_UCLAMP_TASK
	/*
	 * This could race with another potential updater, but this is fine
	 * because it'll correctly read the old or the new value. We don't need
	 * to guarantee who wins the race as दीर्घ as it करोesn't वापस garbage.
	 */
	kattr.sched_util_min = p->uclamp_req[UCLAMP_MIN].value;
	kattr.sched_util_max = p->uclamp_req[UCLAMP_MAX].value;
#पूर्ण_अगर

	rcu_पढ़ो_unlock();

	वापस sched_attr_copy_to_user(uattr, &kattr, usize);

out_unlock:
	rcu_पढ़ो_unlock();
	वापस retval;
पूर्ण

दीर्घ sched_setaffinity(pid_t pid, स्थिर काष्ठा cpumask *in_mask)
अणु
	cpumask_var_t cpus_allowed, new_mask;
	काष्ठा task_काष्ठा *p;
	पूर्णांक retval;

	rcu_पढ़ो_lock();

	p = find_process_by_pid(pid);
	अगर (!p) अणु
		rcu_पढ़ो_unlock();
		वापस -ESRCH;
	पूर्ण

	/* Prevent p going away */
	get_task_काष्ठा(p);
	rcu_पढ़ो_unlock();

	अगर (p->flags & PF_NO_SETAFFINITY) अणु
		retval = -EINVAL;
		जाओ out_put_task;
	पूर्ण
	अगर (!alloc_cpumask_var(&cpus_allowed, GFP_KERNEL)) अणु
		retval = -ENOMEM;
		जाओ out_put_task;
	पूर्ण
	अगर (!alloc_cpumask_var(&new_mask, GFP_KERNEL)) अणु
		retval = -ENOMEM;
		जाओ out_मुक्त_cpus_allowed;
	पूर्ण
	retval = -EPERM;
	अगर (!check_same_owner(p)) अणु
		rcu_पढ़ो_lock();
		अगर (!ns_capable(__task_cred(p)->user_ns, CAP_SYS_NICE)) अणु
			rcu_पढ़ो_unlock();
			जाओ out_मुक्त_new_mask;
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	retval = security_task_setscheduler(p);
	अगर (retval)
		जाओ out_मुक्त_new_mask;


	cpuset_cpus_allowed(p, cpus_allowed);
	cpumask_and(new_mask, in_mask, cpus_allowed);

	/*
	 * Since bandwidth control happens on root_करोमुख्य basis,
	 * अगर admission test is enabled, we only admit -deadline
	 * tasks allowed to run on all the CPUs in the task's
	 * root_करोमुख्य.
	 */
#अगर_घोषित CONFIG_SMP
	अगर (task_has_dl_policy(p) && dl_bandwidth_enabled()) अणु
		rcu_पढ़ो_lock();
		अगर (!cpumask_subset(task_rq(p)->rd->span, new_mask)) अणु
			retval = -EBUSY;
			rcu_पढ़ो_unlock();
			जाओ out_मुक्त_new_mask;
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण
#पूर्ण_अगर
again:
	retval = __set_cpus_allowed_ptr(p, new_mask, SCA_CHECK);

	अगर (!retval) अणु
		cpuset_cpus_allowed(p, cpus_allowed);
		अगर (!cpumask_subset(new_mask, cpus_allowed)) अणु
			/*
			 * We must have raced with a concurrent cpuset
			 * update. Just reset the cpus_allowed to the
			 * cpuset's cpus_allowed
			 */
			cpumask_copy(new_mask, cpus_allowed);
			जाओ again;
		पूर्ण
	पूर्ण
out_मुक्त_new_mask:
	मुक्त_cpumask_var(new_mask);
out_मुक्त_cpus_allowed:
	मुक्त_cpumask_var(cpus_allowed);
out_put_task:
	put_task_काष्ठा(p);
	वापस retval;
पूर्ण

अटल पूर्णांक get_user_cpu_mask(अचिन्हित दीर्घ __user *user_mask_ptr, अचिन्हित len,
			     काष्ठा cpumask *new_mask)
अणु
	अगर (len < cpumask_size())
		cpumask_clear(new_mask);
	अन्यथा अगर (len > cpumask_size())
		len = cpumask_size();

	वापस copy_from_user(new_mask, user_mask_ptr, len) ? -EFAULT : 0;
पूर्ण

/**
 * sys_sched_setaffinity - set the CPU affinity of a process
 * @pid: pid of the process
 * @len: length in bytes of the biपंचांगask poपूर्णांकed to by user_mask_ptr
 * @user_mask_ptr: user-space poपूर्णांकer to the new CPU mask
 *
 * Return: 0 on success. An error code otherwise.
 */
SYSCALL_DEFINE3(sched_setaffinity, pid_t, pid, अचिन्हित पूर्णांक, len,
		अचिन्हित दीर्घ __user *, user_mask_ptr)
अणु
	cpumask_var_t new_mask;
	पूर्णांक retval;

	अगर (!alloc_cpumask_var(&new_mask, GFP_KERNEL))
		वापस -ENOMEM;

	retval = get_user_cpu_mask(user_mask_ptr, len, new_mask);
	अगर (retval == 0)
		retval = sched_setaffinity(pid, new_mask);
	मुक्त_cpumask_var(new_mask);
	वापस retval;
पूर्ण

दीर्घ sched_getaffinity(pid_t pid, काष्ठा cpumask *mask)
अणु
	काष्ठा task_काष्ठा *p;
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;

	rcu_पढ़ो_lock();

	retval = -ESRCH;
	p = find_process_by_pid(pid);
	अगर (!p)
		जाओ out_unlock;

	retval = security_task_माला_लोcheduler(p);
	अगर (retval)
		जाओ out_unlock;

	raw_spin_lock_irqsave(&p->pi_lock, flags);
	cpumask_and(mask, &p->cpus_mask, cpu_active_mask);
	raw_spin_unlock_irqrestore(&p->pi_lock, flags);

out_unlock:
	rcu_पढ़ो_unlock();

	वापस retval;
पूर्ण

/**
 * sys_sched_getaffinity - get the CPU affinity of a process
 * @pid: pid of the process
 * @len: length in bytes of the biपंचांगask poपूर्णांकed to by user_mask_ptr
 * @user_mask_ptr: user-space poपूर्णांकer to hold the current CPU mask
 *
 * Return: size of CPU mask copied to user_mask_ptr on success. An
 * error code otherwise.
 */
SYSCALL_DEFINE3(sched_getaffinity, pid_t, pid, अचिन्हित पूर्णांक, len,
		अचिन्हित दीर्घ __user *, user_mask_ptr)
अणु
	पूर्णांक ret;
	cpumask_var_t mask;

	अगर ((len * BITS_PER_BYTE) < nr_cpu_ids)
		वापस -EINVAL;
	अगर (len & (माप(अचिन्हित दीर्घ)-1))
		वापस -EINVAL;

	अगर (!alloc_cpumask_var(&mask, GFP_KERNEL))
		वापस -ENOMEM;

	ret = sched_getaffinity(pid, mask);
	अगर (ret == 0) अणु
		अचिन्हित पूर्णांक retlen = min(len, cpumask_size());

		अगर (copy_to_user(user_mask_ptr, mask, retlen))
			ret = -EFAULT;
		अन्यथा
			ret = retlen;
	पूर्ण
	मुक्त_cpumask_var(mask);

	वापस ret;
पूर्ण

अटल व्योम करो_sched_yield(व्योम)
अणु
	काष्ठा rq_flags rf;
	काष्ठा rq *rq;

	rq = this_rq_lock_irq(&rf);

	schedstat_inc(rq->yld_count);
	current->sched_class->yield_task(rq);

	preempt_disable();
	rq_unlock_irq(rq, &rf);
	sched_preempt_enable_no_resched();

	schedule();
पूर्ण

/**
 * sys_sched_yield - yield the current processor to other thपढ़ोs.
 *
 * This function yields the current CPU to other tasks. If there are no
 * other thपढ़ोs running on this CPU then this function will वापस.
 *
 * Return: 0.
 */
SYSCALL_DEFINE0(sched_yield)
अणु
	करो_sched_yield();
	वापस 0;
पूर्ण

#अगर !defined(CONFIG_PREEMPTION) || defined(CONFIG_PREEMPT_DYNAMIC)
पूर्णांक __sched __cond_resched(व्योम)
अणु
	अगर (should_resched(0)) अणु
		preempt_schedule_common();
		वापस 1;
	पूर्ण
#अगर_अघोषित CONFIG_PREEMPT_RCU
	rcu_all_qs();
#पूर्ण_अगर
	वापस 0;
पूर्ण
EXPORT_SYMBOL(__cond_resched);
#पूर्ण_अगर

#अगर_घोषित CONFIG_PREEMPT_DYNAMIC
DEFINE_STATIC_CALL_RET0(cond_resched, __cond_resched);
EXPORT_STATIC_CALL_TRAMP(cond_resched);

DEFINE_STATIC_CALL_RET0(might_resched, __cond_resched);
EXPORT_STATIC_CALL_TRAMP(might_resched);
#पूर्ण_अगर

/*
 * __cond_resched_lock() - अगर a reschedule is pending, drop the given lock,
 * call schedule, and on वापस reacquire the lock.
 *
 * This works OK both with and without CONFIG_PREEMPTION. We करो strange low-level
 * operations here to prevent schedule() from being called twice (once via
 * spin_unlock(), once by hand).
 */
पूर्णांक __cond_resched_lock(spinlock_t *lock)
अणु
	पूर्णांक resched = should_resched(PREEMPT_LOCK_OFFSET);
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(lock);

	अगर (spin_needअवरोध(lock) || resched) अणु
		spin_unlock(lock);
		अगर (resched)
			preempt_schedule_common();
		अन्यथा
			cpu_relax();
		ret = 1;
		spin_lock(lock);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(__cond_resched_lock);

पूर्णांक __cond_resched_rwlock_पढ़ो(rwlock_t *lock)
अणु
	पूर्णांक resched = should_resched(PREEMPT_LOCK_OFFSET);
	पूर्णांक ret = 0;

	lockdep_निश्चित_held_पढ़ो(lock);

	अगर (rwlock_needअवरोध(lock) || resched) अणु
		पढ़ो_unlock(lock);
		अगर (resched)
			preempt_schedule_common();
		अन्यथा
			cpu_relax();
		ret = 1;
		पढ़ो_lock(lock);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(__cond_resched_rwlock_पढ़ो);

पूर्णांक __cond_resched_rwlock_ग_लिखो(rwlock_t *lock)
अणु
	पूर्णांक resched = should_resched(PREEMPT_LOCK_OFFSET);
	पूर्णांक ret = 0;

	lockdep_निश्चित_held_ग_लिखो(lock);

	अगर (rwlock_needअवरोध(lock) || resched) अणु
		ग_लिखो_unlock(lock);
		अगर (resched)
			preempt_schedule_common();
		अन्यथा
			cpu_relax();
		ret = 1;
		ग_लिखो_lock(lock);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(__cond_resched_rwlock_ग_लिखो);

/**
 * yield - yield the current processor to other thपढ़ोs.
 *
 * Do not ever use this function, there's a 99% chance you're करोing it wrong.
 *
 * The scheduler is at all बार मुक्त to pick the calling task as the most
 * eligible task to run, अगर removing the yield() call from your code अवरोधs
 * it, it's alपढ़ोy broken.
 *
 * Typical broken usage is:
 *
 * जबतक (!event)
 *	yield();
 *
 * where one assumes that yield() will let 'the other' process run that will
 * make event true. If the current task is a SCHED_FIFO task that will never
 * happen. Never use yield() as a progress guarantee!!
 *
 * If you want to use yield() to रुको क्रम something, use रुको_event().
 * If you want to use yield() to be 'nice' क्रम others, use cond_resched().
 * If you still want to use yield(), करो not!
 */
व्योम __sched yield(व्योम)
अणु
	set_current_state(TASK_RUNNING);
	करो_sched_yield();
पूर्ण
EXPORT_SYMBOL(yield);

/**
 * yield_to - yield the current processor to another thपढ़ो in
 * your thपढ़ो group, or accelerate that thपढ़ो toward the
 * processor it's on.
 * @p: target task
 * @preempt: whether task preemption is allowed or not
 *
 * It's the caller's job to ensure that the target task काष्ठा
 * can't go away on us beक्रमe we can करो any checks.
 *
 * Return:
 *	true (>0) अगर we indeed boosted the target task.
 *	false (0) अगर we failed to boost the target.
 *	-ESRCH अगर there's no task to yield to.
 */
पूर्णांक __sched yield_to(काष्ठा task_काष्ठा *p, bool preempt)
अणु
	काष्ठा task_काष्ठा *curr = current;
	काष्ठा rq *rq, *p_rq;
	अचिन्हित दीर्घ flags;
	पूर्णांक yielded = 0;

	local_irq_save(flags);
	rq = this_rq();

again:
	p_rq = task_rq(p);
	/*
	 * If we're the only runnable task on the rq and target rq also
	 * has only one task, there's असलolutely no poपूर्णांक in yielding.
	 */
	अगर (rq->nr_running == 1 && p_rq->nr_running == 1) अणु
		yielded = -ESRCH;
		जाओ out_irq;
	पूर्ण

	द्विगुन_rq_lock(rq, p_rq);
	अगर (task_rq(p) != p_rq) अणु
		द्विगुन_rq_unlock(rq, p_rq);
		जाओ again;
	पूर्ण

	अगर (!curr->sched_class->yield_to_task)
		जाओ out_unlock;

	अगर (curr->sched_class != p->sched_class)
		जाओ out_unlock;

	अगर (task_running(p_rq, p) || p->state)
		जाओ out_unlock;

	yielded = curr->sched_class->yield_to_task(rq, p);
	अगर (yielded) अणु
		schedstat_inc(rq->yld_count);
		/*
		 * Make p's CPU reschedule; pick_next_entity takes care of
		 * fairness.
		 */
		अगर (preempt && rq != p_rq)
			resched_curr(p_rq);
	पूर्ण

out_unlock:
	द्विगुन_rq_unlock(rq, p_rq);
out_irq:
	local_irq_restore(flags);

	अगर (yielded > 0)
		schedule();

	वापस yielded;
पूर्ण
EXPORT_SYMBOL_GPL(yield_to);

पूर्णांक io_schedule_prepare(व्योम)
अणु
	पूर्णांक old_ioरुको = current->in_ioरुको;

	current->in_ioरुको = 1;
	blk_schedule_flush_plug(current);

	वापस old_ioरुको;
पूर्ण

व्योम io_schedule_finish(पूर्णांक token)
अणु
	current->in_ioरुको = token;
पूर्ण

/*
 * This task is about to go to sleep on IO. Increment rq->nr_ioरुको so
 * that process accounting knows that this is a task in IO रुको state.
 */
दीर्घ __sched io_schedule_समयout(दीर्घ समयout)
अणु
	पूर्णांक token;
	दीर्घ ret;

	token = io_schedule_prepare();
	ret = schedule_समयout(समयout);
	io_schedule_finish(token);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(io_schedule_समयout);

व्योम __sched io_schedule(व्योम)
अणु
	पूर्णांक token;

	token = io_schedule_prepare();
	schedule();
	io_schedule_finish(token);
पूर्ण
EXPORT_SYMBOL(io_schedule);

/**
 * sys_sched_get_priority_max - वापस maximum RT priority.
 * @policy: scheduling class.
 *
 * Return: On success, this syscall वापसs the maximum
 * rt_priority that can be used by a given scheduling class.
 * On failure, a negative error code is वापसed.
 */
SYSCALL_DEFINE1(sched_get_priority_max, पूर्णांक, policy)
अणु
	पूर्णांक ret = -EINVAL;

	चयन (policy) अणु
	हाल SCHED_FIFO:
	हाल SCHED_RR:
		ret = MAX_RT_PRIO-1;
		अवरोध;
	हाल SCHED_DEADLINE:
	हाल SCHED_NORMAL:
	हाल SCHED_BATCH:
	हाल SCHED_IDLE:
		ret = 0;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * sys_sched_get_priority_min - वापस minimum RT priority.
 * @policy: scheduling class.
 *
 * Return: On success, this syscall वापसs the minimum
 * rt_priority that can be used by a given scheduling class.
 * On failure, a negative error code is वापसed.
 */
SYSCALL_DEFINE1(sched_get_priority_min, पूर्णांक, policy)
अणु
	पूर्णांक ret = -EINVAL;

	चयन (policy) अणु
	हाल SCHED_FIFO:
	हाल SCHED_RR:
		ret = 1;
		अवरोध;
	हाल SCHED_DEADLINE:
	हाल SCHED_NORMAL:
	हाल SCHED_BATCH:
	हाल SCHED_IDLE:
		ret = 0;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक sched_rr_get_पूर्णांकerval(pid_t pid, काष्ठा बारpec64 *t)
अणु
	काष्ठा task_काष्ठा *p;
	अचिन्हित पूर्णांक समय_slice;
	काष्ठा rq_flags rf;
	काष्ठा rq *rq;
	पूर्णांक retval;

	अगर (pid < 0)
		वापस -EINVAL;

	retval = -ESRCH;
	rcu_पढ़ो_lock();
	p = find_process_by_pid(pid);
	अगर (!p)
		जाओ out_unlock;

	retval = security_task_माला_लोcheduler(p);
	अगर (retval)
		जाओ out_unlock;

	rq = task_rq_lock(p, &rf);
	समय_slice = 0;
	अगर (p->sched_class->get_rr_पूर्णांकerval)
		समय_slice = p->sched_class->get_rr_पूर्णांकerval(rq, p);
	task_rq_unlock(rq, p, &rf);

	rcu_पढ़ो_unlock();
	jअगरfies_to_बारpec64(समय_slice, t);
	वापस 0;

out_unlock:
	rcu_पढ़ो_unlock();
	वापस retval;
पूर्ण

/**
 * sys_sched_rr_get_पूर्णांकerval - वापस the शेष बारlice of a process.
 * @pid: pid of the process.
 * @पूर्णांकerval: userspace poपूर्णांकer to the बारlice value.
 *
 * this syscall ग_लिखोs the शेष बारlice value of a given process
 * पूर्णांकo the user-space बारpec buffer. A value of '0' means infinity.
 *
 * Return: On success, 0 and the बारlice is in @पूर्णांकerval. Otherwise,
 * an error code.
 */
SYSCALL_DEFINE2(sched_rr_get_पूर्णांकerval, pid_t, pid,
		काष्ठा __kernel_बारpec __user *, पूर्णांकerval)
अणु
	काष्ठा बारpec64 t;
	पूर्णांक retval = sched_rr_get_पूर्णांकerval(pid, &t);

	अगर (retval == 0)
		retval = put_बारpec64(&t, पूर्णांकerval);

	वापस retval;
पूर्ण

#अगर_घोषित CONFIG_COMPAT_32BIT_TIME
SYSCALL_DEFINE2(sched_rr_get_पूर्णांकerval_समय32, pid_t, pid,
		काष्ठा old_बारpec32 __user *, पूर्णांकerval)
अणु
	काष्ठा बारpec64 t;
	पूर्णांक retval = sched_rr_get_पूर्णांकerval(pid, &t);

	अगर (retval == 0)
		retval = put_old_बारpec32(&t, पूर्णांकerval);
	वापस retval;
पूर्ण
#पूर्ण_अगर

व्योम sched_show_task(काष्ठा task_काष्ठा *p)
अणु
	अचिन्हित दीर्घ मुक्त = 0;
	पूर्णांक ppid;

	अगर (!try_get_task_stack(p))
		वापस;

	pr_info("task:%-15.15s state:%c", p->comm, task_state_to_अक्षर(p));

	अगर (p->state == TASK_RUNNING)
		pr_cont("  running task    ");
#अगर_घोषित CONFIG_DEBUG_STACK_USAGE
	मुक्त = stack_not_used(p);
#पूर्ण_अगर
	ppid = 0;
	rcu_पढ़ो_lock();
	अगर (pid_alive(p))
		ppid = task_pid_nr(rcu_dereference(p->real_parent));
	rcu_पढ़ो_unlock();
	pr_cont(" stack:%5lu pid:%5d ppid:%6d flags:0x%08lx\n",
		मुक्त, task_pid_nr(p), ppid,
		(अचिन्हित दीर्घ)task_thपढ़ो_info(p)->flags);

	prपूर्णांक_worker_info(KERN_INFO, p);
	prपूर्णांक_stop_info(KERN_INFO, p);
	show_stack(p, शून्य, KERN_INFO);
	put_task_stack(p);
पूर्ण
EXPORT_SYMBOL_GPL(sched_show_task);

अटल अंतरभूत bool
state_filter_match(अचिन्हित दीर्घ state_filter, काष्ठा task_काष्ठा *p)
अणु
	/* no filter, everything matches */
	अगर (!state_filter)
		वापस true;

	/* filter, but करोesn't match */
	अगर (!(p->state & state_filter))
		वापस false;

	/*
	 * When looking क्रम TASK_UNINTERRUPTIBLE skip TASK_IDLE (allows
	 * TASK_KILLABLE).
	 */
	अगर (state_filter == TASK_UNINTERRUPTIBLE && p->state == TASK_IDLE)
		वापस false;

	वापस true;
पूर्ण


व्योम show_state_filter(अचिन्हित दीर्घ state_filter)
अणु
	काष्ठा task_काष्ठा *g, *p;

	rcu_पढ़ो_lock();
	क्रम_each_process_thपढ़ो(g, p) अणु
		/*
		 * reset the NMI-समयout, listing all files on a slow
		 * console might take a lot of समय:
		 * Also, reset softlockup watchकरोgs on all CPUs, because
		 * another CPU might be blocked रुकोing क्रम us to process
		 * an IPI.
		 */
		touch_nmi_watchकरोg();
		touch_all_softlockup_watchकरोgs();
		अगर (state_filter_match(state_filter, p))
			sched_show_task(p);
	पूर्ण

#अगर_घोषित CONFIG_SCHED_DEBUG
	अगर (!state_filter)
		sysrq_sched_debug_show();
#पूर्ण_अगर
	rcu_पढ़ो_unlock();
	/*
	 * Only show locks अगर all tasks are dumped:
	 */
	अगर (!state_filter)
		debug_show_all_locks();
पूर्ण

/**
 * init_idle - set up an idle thपढ़ो क्रम a given CPU
 * @idle: task in question
 * @cpu: CPU the idle task beदीर्घs to
 *
 * NOTE: this function करोes not set the idle thपढ़ो's NEED_RESCHED
 * flag, to make booting more robust.
 */
व्योम init_idle(काष्ठा task_काष्ठा *idle, पूर्णांक cpu)
अणु
	काष्ठा rq *rq = cpu_rq(cpu);
	अचिन्हित दीर्घ flags;

	__sched_विभाजन(0, idle);

	raw_spin_lock_irqsave(&idle->pi_lock, flags);
	raw_spin_lock(&rq->lock);

	idle->state = TASK_RUNNING;
	idle->se.exec_start = sched_घड़ी();
	idle->flags |= PF_IDLE;

	scs_task_reset(idle);
	kasan_unpoison_task_stack(idle);

#अगर_घोषित CONFIG_SMP
	/*
	 * It's possible that init_idle() माला_लो called multiple बार on a task,
	 * in that हाल करो_set_cpus_allowed() will not करो the right thing.
	 *
	 * And since this is boot we can क्रमgo the serialization.
	 */
	set_cpus_allowed_common(idle, cpumask_of(cpu), 0);
#पूर्ण_अगर
	/*
	 * We're having a chicken and egg problem, even though we are
	 * holding rq->lock, the CPU isn't yet set to this CPU so the
	 * lockdep check in task_group() will fail.
	 *
	 * Similar हाल to sched_विभाजन(). / Alternatively we could
	 * use task_rq_lock() here and obtain the other rq->lock.
	 *
	 * Silence PROVE_RCU
	 */
	rcu_पढ़ो_lock();
	__set_task_cpu(idle, cpu);
	rcu_पढ़ो_unlock();

	rq->idle = idle;
	rcu_assign_poपूर्णांकer(rq->curr, idle);
	idle->on_rq = TASK_ON_RQ_QUEUED;
#अगर_घोषित CONFIG_SMP
	idle->on_cpu = 1;
#पूर्ण_अगर
	raw_spin_unlock(&rq->lock);
	raw_spin_unlock_irqrestore(&idle->pi_lock, flags);

	/* Set the preempt count _outside_ the spinlocks! */
	init_idle_preempt_count(idle, cpu);

	/*
	 * The idle tasks have their own, simple scheduling class:
	 */
	idle->sched_class = &idle_sched_class;
	ftrace_graph_init_idle_task(idle, cpu);
	vसमय_init_idle(idle, cpu);
#अगर_घोषित CONFIG_SMP
	प्र_लिखो(idle->comm, "%s/%d", INIT_TASK_COMM, cpu);
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_SMP

पूर्णांक cpuset_cpumask_can_shrink(स्थिर काष्ठा cpumask *cur,
			      स्थिर काष्ठा cpumask *trial)
अणु
	पूर्णांक ret = 1;

	अगर (!cpumask_weight(cur))
		वापस ret;

	ret = dl_cpuset_cpumask_can_shrink(cur, trial);

	वापस ret;
पूर्ण

पूर्णांक task_can_attach(काष्ठा task_काष्ठा *p,
		    स्थिर काष्ठा cpumask *cs_cpus_allowed)
अणु
	पूर्णांक ret = 0;

	/*
	 * Kthपढ़ोs which disallow setaffinity shouldn't be moved
	 * to a new cpuset; we करोn't want to change their CPU
	 * affinity and isolating such thपढ़ोs by their set of
	 * allowed nodes is unnecessary.  Thus, cpusets are not
	 * applicable क्रम such thपढ़ोs.  This prevents checking क्रम
	 * success of set_cpus_allowed_ptr() on all attached tasks
	 * beक्रमe cpus_mask may be changed.
	 */
	अगर (p->flags & PF_NO_SETAFFINITY) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (dl_task(p) && !cpumask_पूर्णांकersects(task_rq(p)->rd->span,
					      cs_cpus_allowed))
		ret = dl_task_can_attach(p, cs_cpus_allowed);

out:
	वापस ret;
पूर्ण

bool sched_smp_initialized __पढ़ो_mostly;

#अगर_घोषित CONFIG_NUMA_BALANCING
/* Migrate current task p to target_cpu */
पूर्णांक migrate_task_to(काष्ठा task_काष्ठा *p, पूर्णांक target_cpu)
अणु
	काष्ठा migration_arg arg = अणु p, target_cpu पूर्ण;
	पूर्णांक curr_cpu = task_cpu(p);

	अगर (curr_cpu == target_cpu)
		वापस 0;

	अगर (!cpumask_test_cpu(target_cpu, p->cpus_ptr))
		वापस -EINVAL;

	/* TODO: This is not properly updating schedstats */

	trace_sched_move_numa(p, curr_cpu, target_cpu);
	वापस stop_one_cpu(curr_cpu, migration_cpu_stop, &arg);
पूर्ण

/*
 * Requeue a task on a given node and accurately track the number of NUMA
 * tasks on the runqueues
 */
व्योम sched_setnuma(काष्ठा task_काष्ठा *p, पूर्णांक nid)
अणु
	bool queued, running;
	काष्ठा rq_flags rf;
	काष्ठा rq *rq;

	rq = task_rq_lock(p, &rf);
	queued = task_on_rq_queued(p);
	running = task_current(rq, p);

	अगर (queued)
		dequeue_task(rq, p, DEQUEUE_SAVE);
	अगर (running)
		put_prev_task(rq, p);

	p->numa_preferred_nid = nid;

	अगर (queued)
		enqueue_task(rq, p, ENQUEUE_RESTORE | ENQUEUE_NOCLOCK);
	अगर (running)
		set_next_task(rq, p);
	task_rq_unlock(rq, p, &rf);
पूर्ण
#पूर्ण_अगर /* CONFIG_NUMA_BALANCING */

#अगर_घोषित CONFIG_HOTPLUG_CPU
/*
 * Ensure that the idle task is using init_mm right beक्रमe its CPU goes
 * offline.
 */
व्योम idle_task_निकास(व्योम)
अणु
	काष्ठा mm_काष्ठा *mm = current->active_mm;

	BUG_ON(cpu_online(smp_processor_id()));
	BUG_ON(current != this_rq()->idle);

	अगर (mm != &init_mm) अणु
		चयन_mm(mm, &init_mm, current);
		finish_arch_post_lock_चयन();
	पूर्ण

	/* finish_cpu(), as ran on the BP, will clean up the active_mm state */
पूर्ण

अटल पूर्णांक __balance_push_cpu_stop(व्योम *arg)
अणु
	काष्ठा task_काष्ठा *p = arg;
	काष्ठा rq *rq = this_rq();
	काष्ठा rq_flags rf;
	पूर्णांक cpu;

	raw_spin_lock_irq(&p->pi_lock);
	rq_lock(rq, &rf);

	update_rq_घड़ी(rq);

	अगर (task_rq(p) == rq && task_on_rq_queued(p)) अणु
		cpu = select_fallback_rq(rq->cpu, p);
		rq = __migrate_task(rq, &rf, p, cpu);
	पूर्ण

	rq_unlock(rq, &rf);
	raw_spin_unlock_irq(&p->pi_lock);

	put_task_काष्ठा(p);

	वापस 0;
पूर्ण

अटल DEFINE_PER_CPU(काष्ठा cpu_stop_work, push_work);

/*
 * Ensure we only run per-cpu kthपढ़ोs once the CPU goes !active.
 *
 * This is enabled below SCHED_AP_ACTIVE; when !cpu_active(), but only
 * effective when the hotplug motion is करोwn.
 */
अटल व्योम balance_push(काष्ठा rq *rq)
अणु
	काष्ठा task_काष्ठा *push_task = rq->curr;

	lockdep_निश्चित_held(&rq->lock);
	SCHED_WARN_ON(rq->cpu != smp_processor_id());

	/*
	 * Ensure the thing is persistent until balance_push_set(.on = false);
	 */
	rq->balance_callback = &balance_push_callback;

	/*
	 * Only active जबतक going offline.
	 */
	अगर (!cpu_dying(rq->cpu))
		वापस;

	/*
	 * Both the cpu-hotplug and stop task are in this हाल and are
	 * required to complete the hotplug process.
	 *
	 * XXX: the idle task करोes not match kthपढ़ो_is_per_cpu() due to
	 * histerical raisins.
	 */
	अगर (rq->idle == push_task ||
	    kthपढ़ो_is_per_cpu(push_task) ||
	    is_migration_disabled(push_task)) अणु

		/*
		 * If this is the idle task on the outgoing CPU try to wake
		 * up the hotplug control thपढ़ो which might रुको क्रम the
		 * last task to vanish. The rcuरुको_active() check is
		 * accurate here because the रुकोer is pinned on this CPU
		 * and can't obviously be running in parallel.
		 *
		 * On RT kernels this also has to check whether there are
		 * pinned and scheduled out tasks on the runqueue. They
		 * need to leave the migrate disabled section first.
		 */
		अगर (!rq->nr_running && !rq_has_pinned_tasks(rq) &&
		    rcuरुको_active(&rq->hotplug_रुको)) अणु
			raw_spin_unlock(&rq->lock);
			rcuरुको_wake_up(&rq->hotplug_रुको);
			raw_spin_lock(&rq->lock);
		पूर्ण
		वापस;
	पूर्ण

	get_task_काष्ठा(push_task);
	/*
	 * Temporarily drop rq->lock such that we can wake-up the stop task.
	 * Both preemption and IRQs are still disabled.
	 */
	raw_spin_unlock(&rq->lock);
	stop_one_cpu_noरुको(rq->cpu, __balance_push_cpu_stop, push_task,
			    this_cpu_ptr(&push_work));
	/*
	 * At this poपूर्णांक need_resched() is true and we'll take the loop in
	 * schedule(). The next pick is obviously going to be the stop task
	 * which kthपढ़ो_is_per_cpu() and will push this task away.
	 */
	raw_spin_lock(&rq->lock);
पूर्ण

अटल व्योम balance_push_set(पूर्णांक cpu, bool on)
अणु
	काष्ठा rq *rq = cpu_rq(cpu);
	काष्ठा rq_flags rf;

	rq_lock_irqsave(rq, &rf);
	अगर (on) अणु
		WARN_ON_ONCE(rq->balance_callback);
		rq->balance_callback = &balance_push_callback;
	पूर्ण अन्यथा अगर (rq->balance_callback == &balance_push_callback) अणु
		rq->balance_callback = शून्य;
	पूर्ण
	rq_unlock_irqrestore(rq, &rf);
पूर्ण

/*
 * Invoked from a CPUs hotplug control thपढ़ो after the CPU has been marked
 * inactive. All tasks which are not per CPU kernel thपढ़ोs are either
 * pushed off this CPU now via balance_push() or placed on a dअगरferent CPU
 * during wakeup. Wait until the CPU is quiescent.
 */
अटल व्योम balance_hotplug_रुको(व्योम)
अणु
	काष्ठा rq *rq = this_rq();

	rcuरुको_रुको_event(&rq->hotplug_रुको,
			   rq->nr_running == 1 && !rq_has_pinned_tasks(rq),
			   TASK_UNINTERRUPTIBLE);
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम balance_push(काष्ठा rq *rq)
अणु
पूर्ण

अटल अंतरभूत व्योम balance_push_set(पूर्णांक cpu, bool on)
अणु
पूर्ण

अटल अंतरभूत व्योम balance_hotplug_रुको(व्योम)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_HOTPLUG_CPU */

व्योम set_rq_online(काष्ठा rq *rq)
अणु
	अगर (!rq->online) अणु
		स्थिर काष्ठा sched_class *class;

		cpumask_set_cpu(rq->cpu, rq->rd->online);
		rq->online = 1;

		क्रम_each_class(class) अणु
			अगर (class->rq_online)
				class->rq_online(rq);
		पूर्ण
	पूर्ण
पूर्ण

व्योम set_rq_offline(काष्ठा rq *rq)
अणु
	अगर (rq->online) अणु
		स्थिर काष्ठा sched_class *class;

		क्रम_each_class(class) अणु
			अगर (class->rq_offline)
				class->rq_offline(rq);
		पूर्ण

		cpumask_clear_cpu(rq->cpu, rq->rd->online);
		rq->online = 0;
	पूर्ण
पूर्ण

/*
 * used to mark begin/end of suspend/resume:
 */
अटल पूर्णांक num_cpus_frozen;

/*
 * Update cpusets according to cpu_active mask.  If cpusets are
 * disabled, cpuset_update_active_cpus() becomes a simple wrapper
 * around partition_sched_करोमुख्यs().
 *
 * If we come here as part of a suspend/resume, करोn't touch cpusets because we
 * want to restore it back to its original state upon resume anyway.
 */
अटल व्योम cpuset_cpu_active(व्योम)
अणु
	अगर (cpuhp_tasks_frozen) अणु
		/*
		 * num_cpus_frozen tracks how many CPUs are involved in suspend
		 * resume sequence. As दीर्घ as this is not the last online
		 * operation in the resume sequence, just build a single sched
		 * करोमुख्य, ignoring cpusets.
		 */
		partition_sched_करोमुख्यs(1, शून्य, शून्य);
		अगर (--num_cpus_frozen)
			वापस;
		/*
		 * This is the last CPU online operation. So fall through and
		 * restore the original sched करोमुख्यs by considering the
		 * cpuset configurations.
		 */
		cpuset_क्रमce_rebuild();
	पूर्ण
	cpuset_update_active_cpus();
पूर्ण

अटल पूर्णांक cpuset_cpu_inactive(अचिन्हित पूर्णांक cpu)
अणु
	अगर (!cpuhp_tasks_frozen) अणु
		अगर (dl_cpu_busy(cpu))
			वापस -EBUSY;
		cpuset_update_active_cpus();
	पूर्ण अन्यथा अणु
		num_cpus_frozen++;
		partition_sched_करोमुख्यs(1, शून्य, शून्य);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक sched_cpu_activate(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा rq *rq = cpu_rq(cpu);
	काष्ठा rq_flags rf;

	/*
	 * Clear the balance_push callback and prepare to schedule
	 * regular tasks.
	 */
	balance_push_set(cpu, false);

#अगर_घोषित CONFIG_SCHED_SMT
	/*
	 * When going up, increment the number of cores with SMT present.
	 */
	अगर (cpumask_weight(cpu_smt_mask(cpu)) == 2)
		अटल_branch_inc_cpuslocked(&sched_smt_present);
#पूर्ण_अगर
	set_cpu_active(cpu, true);

	अगर (sched_smp_initialized) अणु
		sched_करोमुख्यs_numa_masks_set(cpu);
		cpuset_cpu_active();
	पूर्ण

	/*
	 * Put the rq online, अगर not alपढ़ोy. This happens:
	 *
	 * 1) In the early boot process, because we build the real करोमुख्यs
	 *    after all CPUs have been brought up.
	 *
	 * 2) At runसमय, अगर cpuset_cpu_active() fails to rebuild the
	 *    करोमुख्यs.
	 */
	rq_lock_irqsave(rq, &rf);
	अगर (rq->rd) अणु
		BUG_ON(!cpumask_test_cpu(cpu, rq->rd->span));
		set_rq_online(rq);
	पूर्ण
	rq_unlock_irqrestore(rq, &rf);

	वापस 0;
पूर्ण

पूर्णांक sched_cpu_deactivate(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा rq *rq = cpu_rq(cpu);
	काष्ठा rq_flags rf;
	पूर्णांक ret;

	/*
	 * Remove CPU from nohz.idle_cpus_mask to prevent participating in
	 * load balancing when not active
	 */
	nohz_balance_निकास_idle(rq);

	set_cpu_active(cpu, false);

	/*
	 * From this poपूर्णांक क्रमward, this CPU will refuse to run any task that
	 * is not: migrate_disable() or KTHREAD_IS_PER_CPU, and will actively
	 * push those tasks away until this माला_लो cleared, see
	 * sched_cpu_dying().
	 */
	balance_push_set(cpu, true);

	/*
	 * We've cleared cpu_active_mask / set balance_push, रुको क्रम all
	 * preempt-disabled and RCU users of this state to go away such that
	 * all new such users will observe it.
	 *
	 * Specअगरically, we rely on ttwu to no दीर्घer target this CPU, see
	 * ttwu_queue_cond() and is_cpu_allowed().
	 *
	 * Do sync beक्रमe park smpboot thपढ़ोs to take care the rcu boost हाल.
	 */
	synchronize_rcu();

	rq_lock_irqsave(rq, &rf);
	अगर (rq->rd) अणु
		update_rq_घड़ी(rq);
		BUG_ON(!cpumask_test_cpu(cpu, rq->rd->span));
		set_rq_offline(rq);
	पूर्ण
	rq_unlock_irqrestore(rq, &rf);

#अगर_घोषित CONFIG_SCHED_SMT
	/*
	 * When going करोwn, decrement the number of cores with SMT present.
	 */
	अगर (cpumask_weight(cpu_smt_mask(cpu)) == 2)
		अटल_branch_dec_cpuslocked(&sched_smt_present);
#पूर्ण_अगर

	अगर (!sched_smp_initialized)
		वापस 0;

	ret = cpuset_cpu_inactive(cpu);
	अगर (ret) अणु
		balance_push_set(cpu, false);
		set_cpu_active(cpu, true);
		वापस ret;
	पूर्ण
	sched_करोमुख्यs_numa_masks_clear(cpu);
	वापस 0;
पूर्ण

अटल व्योम sched_rq_cpu_starting(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा rq *rq = cpu_rq(cpu);

	rq->calc_load_update = calc_load_update;
	update_max_पूर्णांकerval();
पूर्ण

पूर्णांक sched_cpu_starting(अचिन्हित पूर्णांक cpu)
अणु
	sched_rq_cpu_starting(cpu);
	sched_tick_start(cpu);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU

/*
 * Invoked immediately beक्रमe the stopper thपढ़ो is invoked to bring the
 * CPU करोwn completely. At this poपूर्णांक all per CPU kthपढ़ोs except the
 * hotplug thपढ़ो (current) and the stopper thपढ़ो (inactive) have been
 * either parked or have been unbound from the outgoing CPU. Ensure that
 * any of those which might be on the way out are gone.
 *
 * If after this poपूर्णांक a bound task is being woken on this CPU then the
 * responsible hotplug callback has failed to करो it's job.
 * sched_cpu_dying() will catch it with the appropriate fireworks.
 */
पूर्णांक sched_cpu_रुको_empty(अचिन्हित पूर्णांक cpu)
अणु
	balance_hotplug_रुको();
	वापस 0;
पूर्ण

/*
 * Since this CPU is going 'away' क्रम a जबतक, fold any nr_active delta we
 * might have. Called from the CPU stopper task after ensuring that the
 * stopper is the last running task on the CPU, so nr_active count is
 * stable. We need to take the tearकरोwn thपढ़ो which is calling this पूर्णांकo
 * account, so we hand in adjust = 1 to the load calculation.
 *
 * Also see the comment "Global load-average calculations".
 */
अटल व्योम calc_load_migrate(काष्ठा rq *rq)
अणु
	दीर्घ delta = calc_load_fold_active(rq, 1);

	अगर (delta)
		atomic_दीर्घ_add(delta, &calc_load_tasks);
पूर्ण

अटल व्योम dump_rq_tasks(काष्ठा rq *rq, स्थिर अक्षर *loglvl)
अणु
	काष्ठा task_काष्ठा *g, *p;
	पूर्णांक cpu = cpu_of(rq);

	lockdep_निश्चित_held(&rq->lock);

	prपूर्णांकk("%sCPU%d enqueued tasks (%u total):\n", loglvl, cpu, rq->nr_running);
	क्रम_each_process_thपढ़ो(g, p) अणु
		अगर (task_cpu(p) != cpu)
			जारी;

		अगर (!task_on_rq_queued(p))
			जारी;

		prपूर्णांकk("%s\tpid: %d, name: %s\n", loglvl, p->pid, p->comm);
	पूर्ण
पूर्ण

पूर्णांक sched_cpu_dying(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा rq *rq = cpu_rq(cpu);
	काष्ठा rq_flags rf;

	/* Handle pending wakeups and then migrate everything off */
	sched_tick_stop(cpu);

	rq_lock_irqsave(rq, &rf);
	अगर (rq->nr_running != 1 || rq_has_pinned_tasks(rq)) अणु
		WARN(true, "Dying CPU not properly vacated!");
		dump_rq_tasks(rq, KERN_WARNING);
	पूर्ण
	rq_unlock_irqrestore(rq, &rf);

	calc_load_migrate(rq);
	update_max_पूर्णांकerval();
	hrtick_clear(rq);
	वापस 0;
पूर्ण
#पूर्ण_अगर

व्योम __init sched_init_smp(व्योम)
अणु
	sched_init_numa();

	/*
	 * There's no userspace yet to cause hotplug operations; hence all the
	 * CPU masks are stable and all blatant races in the below code cannot
	 * happen.
	 */
	mutex_lock(&sched_करोमुख्यs_mutex);
	sched_init_करोमुख्यs(cpu_active_mask);
	mutex_unlock(&sched_करोमुख्यs_mutex);

	/* Move init over to a non-isolated CPU */
	अगर (set_cpus_allowed_ptr(current, housekeeping_cpumask(HK_FLAG_DOMAIN)) < 0)
		BUG();
	sched_init_granularity();

	init_sched_rt_class();
	init_sched_dl_class();

	sched_smp_initialized = true;
पूर्ण

अटल पूर्णांक __init migration_init(व्योम)
अणु
	sched_cpu_starting(smp_processor_id());
	वापस 0;
पूर्ण
early_initcall(migration_init);

#अन्यथा
व्योम __init sched_init_smp(व्योम)
अणु
	sched_init_granularity();
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

पूर्णांक in_sched_functions(अचिन्हित दीर्घ addr)
अणु
	वापस in_lock_functions(addr) ||
		(addr >= (अचिन्हित दीर्घ)__sched_text_start
		&& addr < (अचिन्हित दीर्घ)__sched_text_end);
पूर्ण

#अगर_घोषित CONFIG_CGROUP_SCHED
/*
 * Default task group.
 * Every task in प्रणाली beदीर्घs to this group at bootup.
 */
काष्ठा task_group root_task_group;
LIST_HEAD(task_groups);

/* Cacheline aligned slab cache क्रम task_group */
अटल काष्ठा kmem_cache *task_group_cache __पढ़ो_mostly;
#पूर्ण_अगर

DECLARE_PER_CPU(cpumask_var_t, load_balance_mask);
DECLARE_PER_CPU(cpumask_var_t, select_idle_mask);

व्योम __init sched_init(व्योम)
अणु
	अचिन्हित दीर्घ ptr = 0;
	पूर्णांक i;

	/* Make sure the linker didn't screw up */
	BUG_ON(&idle_sched_class + 1 != &fair_sched_class ||
	       &fair_sched_class + 1 != &rt_sched_class ||
	       &rt_sched_class + 1   != &dl_sched_class);
#अगर_घोषित CONFIG_SMP
	BUG_ON(&dl_sched_class + 1 != &stop_sched_class);
#पूर्ण_अगर

	रुको_bit_init();

#अगर_घोषित CONFIG_FAIR_GROUP_SCHED
	ptr += 2 * nr_cpu_ids * माप(व्योम **);
#पूर्ण_अगर
#अगर_घोषित CONFIG_RT_GROUP_SCHED
	ptr += 2 * nr_cpu_ids * माप(व्योम **);
#पूर्ण_अगर
	अगर (ptr) अणु
		ptr = (अचिन्हित दीर्घ)kzalloc(ptr, GFP_NOWAIT);

#अगर_घोषित CONFIG_FAIR_GROUP_SCHED
		root_task_group.se = (काष्ठा sched_entity **)ptr;
		ptr += nr_cpu_ids * माप(व्योम **);

		root_task_group.cfs_rq = (काष्ठा cfs_rq **)ptr;
		ptr += nr_cpu_ids * माप(व्योम **);

		root_task_group.shares = ROOT_TASK_GROUP_LOAD;
		init_cfs_bandwidth(&root_task_group.cfs_bandwidth);
#पूर्ण_अगर /* CONFIG_FAIR_GROUP_SCHED */
#अगर_घोषित CONFIG_RT_GROUP_SCHED
		root_task_group.rt_se = (काष्ठा sched_rt_entity **)ptr;
		ptr += nr_cpu_ids * माप(व्योम **);

		root_task_group.rt_rq = (काष्ठा rt_rq **)ptr;
		ptr += nr_cpu_ids * माप(व्योम **);

#पूर्ण_अगर /* CONFIG_RT_GROUP_SCHED */
	पूर्ण
#अगर_घोषित CONFIG_CPUMASK_OFFSTACK
	क्रम_each_possible_cpu(i) अणु
		per_cpu(load_balance_mask, i) = (cpumask_var_t)kzalloc_node(
			cpumask_size(), GFP_KERNEL, cpu_to_node(i));
		per_cpu(select_idle_mask, i) = (cpumask_var_t)kzalloc_node(
			cpumask_size(), GFP_KERNEL, cpu_to_node(i));
	पूर्ण
#पूर्ण_अगर /* CONFIG_CPUMASK_OFFSTACK */

	init_rt_bandwidth(&def_rt_bandwidth, global_rt_period(), global_rt_runसमय());
	init_dl_bandwidth(&def_dl_bandwidth, global_rt_period(), global_rt_runसमय());

#अगर_घोषित CONFIG_SMP
	init_defrootकरोमुख्य();
#पूर्ण_अगर

#अगर_घोषित CONFIG_RT_GROUP_SCHED
	init_rt_bandwidth(&root_task_group.rt_bandwidth,
			global_rt_period(), global_rt_runसमय());
#पूर्ण_अगर /* CONFIG_RT_GROUP_SCHED */

#अगर_घोषित CONFIG_CGROUP_SCHED
	task_group_cache = KMEM_CACHE(task_group, 0);

	list_add(&root_task_group.list, &task_groups);
	INIT_LIST_HEAD(&root_task_group.children);
	INIT_LIST_HEAD(&root_task_group.siblings);
	स्वतःgroup_init(&init_task);
#पूर्ण_अगर /* CONFIG_CGROUP_SCHED */

	क्रम_each_possible_cpu(i) अणु
		काष्ठा rq *rq;

		rq = cpu_rq(i);
		raw_spin_lock_init(&rq->lock);
		rq->nr_running = 0;
		rq->calc_load_active = 0;
		rq->calc_load_update = jअगरfies + LOAD_FREQ;
		init_cfs_rq(&rq->cfs);
		init_rt_rq(&rq->rt);
		init_dl_rq(&rq->dl);
#अगर_घोषित CONFIG_FAIR_GROUP_SCHED
		INIT_LIST_HEAD(&rq->leaf_cfs_rq_list);
		rq->पंचांगp_alone_branch = &rq->leaf_cfs_rq_list;
		/*
		 * How much CPU bandwidth करोes root_task_group get?
		 *
		 * In हाल of task-groups क्रमmed thr' the cgroup fileप्रणाली, it
		 * माला_लो 100% of the CPU resources in the प्रणाली. This overall
		 * प्रणाली CPU resource is भागided among the tasks of
		 * root_task_group and its child task-groups in a fair manner,
		 * based on each entity's (task or task-group's) weight
		 * (se->load.weight).
		 *
		 * In other words, अगर root_task_group has 10 tasks of weight
		 * 1024) and two child groups A0 and A1 (of weight 1024 each),
		 * then A0's share of the CPU resource is:
		 *
		 *	A0's bandwidth = 1024 / (10*1024 + 1024 + 1024) = 8.33%
		 *
		 * We achieve this by letting root_task_group's tasks sit
		 * directly in rq->cfs (i.e root_task_group->se[] = शून्य).
		 */
		init_tg_cfs_entry(&root_task_group, &rq->cfs, शून्य, i, शून्य);
#पूर्ण_अगर /* CONFIG_FAIR_GROUP_SCHED */

		rq->rt.rt_runसमय = def_rt_bandwidth.rt_runसमय;
#अगर_घोषित CONFIG_RT_GROUP_SCHED
		init_tg_rt_entry(&root_task_group, &rq->rt, शून्य, i, शून्य);
#पूर्ण_अगर
#अगर_घोषित CONFIG_SMP
		rq->sd = शून्य;
		rq->rd = शून्य;
		rq->cpu_capacity = rq->cpu_capacity_orig = SCHED_CAPACITY_SCALE;
		rq->balance_callback = &balance_push_callback;
		rq->active_balance = 0;
		rq->next_balance = jअगरfies;
		rq->push_cpu = 0;
		rq->cpu = i;
		rq->online = 0;
		rq->idle_stamp = 0;
		rq->avg_idle = 2*sysctl_sched_migration_cost;
		rq->max_idle_balance_cost = sysctl_sched_migration_cost;

		INIT_LIST_HEAD(&rq->cfs_tasks);

		rq_attach_root(rq, &def_root_करोमुख्य);
#अगर_घोषित CONFIG_NO_HZ_COMMON
		rq->last_blocked_load_update_tick = jअगरfies;
		atomic_set(&rq->nohz_flags, 0);

		INIT_CSD(&rq->nohz_csd, nohz_csd_func, rq);
#पूर्ण_अगर
#अगर_घोषित CONFIG_HOTPLUG_CPU
		rcuरुको_init(&rq->hotplug_रुको);
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_SMP */
		hrtick_rq_init(rq);
		atomic_set(&rq->nr_ioरुको, 0);
	पूर्ण

	set_load_weight(&init_task, false);

	/*
	 * The boot idle thपढ़ो करोes lazy MMU चयनing as well:
	 */
	mmgrab(&init_mm);
	enter_lazy_tlb(&init_mm, current);

	/*
	 * Make us the idle thपढ़ो. Technically, schedule() should not be
	 * called from this thपढ़ो, however somewhere below it might be,
	 * but because we are the idle thपढ़ो, we just pick up running again
	 * when this runqueue becomes "idle".
	 */
	init_idle(current, smp_processor_id());

	calc_load_update = jअगरfies + LOAD_FREQ;

#अगर_घोषित CONFIG_SMP
	idle_thपढ़ो_set_boot_cpu();
	balance_push_set(smp_processor_id(), false);
#पूर्ण_अगर
	init_sched_fair_class();

	init_schedstats();

	psi_init();

	init_uclamp();

	scheduler_running = 1;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_ATOMIC_SLEEP
अटल अंतरभूत पूर्णांक preempt_count_equals(पूर्णांक preempt_offset)
अणु
	पूर्णांक nested = preempt_count() + rcu_preempt_depth();

	वापस (nested == preempt_offset);
पूर्ण

व्योम __might_sleep(स्थिर अक्षर *file, पूर्णांक line, पूर्णांक preempt_offset)
अणु
	/*
	 * Blocking primitives will set (and thereक्रमe destroy) current->state,
	 * since we will निकास with TASK_RUNNING make sure we enter with it,
	 * otherwise we will destroy state.
	 */
	WARN_ONCE(current->state != TASK_RUNNING && current->task_state_change,
			"do not call blocking ops when !TASK_RUNNING; "
			"state=%lx set at [<%p>] %pS\n",
			current->state,
			(व्योम *)current->task_state_change,
			(व्योम *)current->task_state_change);

	___might_sleep(file, line, preempt_offset);
पूर्ण
EXPORT_SYMBOL(__might_sleep);

व्योम ___might_sleep(स्थिर अक्षर *file, पूर्णांक line, पूर्णांक preempt_offset)
अणु
	/* Ratelimiting बारtamp: */
	अटल अचिन्हित दीर्घ prev_jअगरfy;

	अचिन्हित दीर्घ preempt_disable_ip;

	/* WARN_ON_ONCE() by शेष, no rate limit required: */
	rcu_sleep_check();

	अगर ((preempt_count_equals(preempt_offset) && !irqs_disabled() &&
	     !is_idle_task(current) && !current->non_block_count) ||
	    प्रणाली_state == SYSTEM_BOOTING || प्रणाली_state > SYSTEM_RUNNING ||
	    oops_in_progress)
		वापस;

	अगर (समय_beक्रमe(jअगरfies, prev_jअगरfy + HZ) && prev_jअगरfy)
		वापस;
	prev_jअगरfy = jअगरfies;

	/* Save this beक्रमe calling prपूर्णांकk(), since that will clobber it: */
	preempt_disable_ip = get_preempt_disable_ip(current);

	prपूर्णांकk(KERN_ERR
		"BUG: sleeping function called from invalid context at %s:%d\n",
			file, line);
	prपूर्णांकk(KERN_ERR
		"in_atomic(): %d, irqs_disabled(): %d, non_block: %d, pid: %d, name: %s\n",
			in_atomic(), irqs_disabled(), current->non_block_count,
			current->pid, current->comm);

	अगर (task_stack_end_corrupted(current))
		prपूर्णांकk(KERN_EMERG "Thread overran stack, or stack corrupted\n");

	debug_show_held_locks(current);
	अगर (irqs_disabled())
		prपूर्णांक_irqtrace_events(current);
	अगर (IS_ENABLED(CONFIG_DEBUG_PREEMPT)
	    && !preempt_count_equals(preempt_offset)) अणु
		pr_err("Preemption disabled at:");
		prपूर्णांक_ip_sym(KERN_ERR, preempt_disable_ip);
	पूर्ण
	dump_stack();
	add_taपूर्णांक(TAINT_WARN, LOCKDEP_STILL_OK);
पूर्ण
EXPORT_SYMBOL(___might_sleep);

व्योम __cant_sleep(स्थिर अक्षर *file, पूर्णांक line, पूर्णांक preempt_offset)
अणु
	अटल अचिन्हित दीर्घ prev_jअगरfy;

	अगर (irqs_disabled())
		वापस;

	अगर (!IS_ENABLED(CONFIG_PREEMPT_COUNT))
		वापस;

	अगर (preempt_count() > preempt_offset)
		वापस;

	अगर (समय_beक्रमe(jअगरfies, prev_jअगरfy + HZ) && prev_jअगरfy)
		वापस;
	prev_jअगरfy = jअगरfies;

	prपूर्णांकk(KERN_ERR "BUG: assuming atomic context at %s:%d\n", file, line);
	prपूर्णांकk(KERN_ERR "in_atomic(): %d, irqs_disabled(): %d, pid: %d, name: %s\n",
			in_atomic(), irqs_disabled(),
			current->pid, current->comm);

	debug_show_held_locks(current);
	dump_stack();
	add_taपूर्णांक(TAINT_WARN, LOCKDEP_STILL_OK);
पूर्ण
EXPORT_SYMBOL_GPL(__cant_sleep);

#अगर_घोषित CONFIG_SMP
व्योम __cant_migrate(स्थिर अक्षर *file, पूर्णांक line)
अणु
	अटल अचिन्हित दीर्घ prev_jअगरfy;

	अगर (irqs_disabled())
		वापस;

	अगर (is_migration_disabled(current))
		वापस;

	अगर (!IS_ENABLED(CONFIG_PREEMPT_COUNT))
		वापस;

	अगर (preempt_count() > 0)
		वापस;

	अगर (समय_beक्रमe(jअगरfies, prev_jअगरfy + HZ) && prev_jअगरfy)
		वापस;
	prev_jअगरfy = jअगरfies;

	pr_err("BUG: assuming non migratable context at %s:%d\n", file, line);
	pr_err("in_atomic(): %d, irqs_disabled(): %d, migration_disabled() %u pid: %d, name: %s\n",
	       in_atomic(), irqs_disabled(), is_migration_disabled(current),
	       current->pid, current->comm);

	debug_show_held_locks(current);
	dump_stack();
	add_taपूर्णांक(TAINT_WARN, LOCKDEP_STILL_OK);
पूर्ण
EXPORT_SYMBOL_GPL(__cant_migrate);
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_MAGIC_SYSRQ
व्योम normalize_rt_tasks(व्योम)
अणु
	काष्ठा task_काष्ठा *g, *p;
	काष्ठा sched_attr attr = अणु
		.sched_policy = SCHED_NORMAL,
	पूर्ण;

	पढ़ो_lock(&tasklist_lock);
	क्रम_each_process_thपढ़ो(g, p) अणु
		/*
		 * Only normalize user tasks:
		 */
		अगर (p->flags & PF_KTHREAD)
			जारी;

		p->se.exec_start = 0;
		schedstat_set(p->se.statistics.रुको_start,  0);
		schedstat_set(p->se.statistics.sleep_start, 0);
		schedstat_set(p->se.statistics.block_start, 0);

		अगर (!dl_task(p) && !rt_task(p)) अणु
			/*
			 * Renice negative nice level userspace
			 * tasks back to 0:
			 */
			अगर (task_nice(p) < 0)
				set_user_nice(p, 0);
			जारी;
		पूर्ण

		__sched_setscheduler(p, &attr, false, false);
	पूर्ण
	पढ़ो_unlock(&tasklist_lock);
पूर्ण

#पूर्ण_अगर /* CONFIG_MAGIC_SYSRQ */

#अगर defined(CONFIG_IA64) || defined(CONFIG_KGDB_KDB)
/*
 * These functions are only useful क्रम the IA64 MCA handling, or kdb.
 *
 * They can only be called when the whole प्रणाली has been
 * stopped - every CPU needs to be quiescent, and no scheduling
 * activity can take place. Using them क्रम anything अन्यथा would
 * be a serious bug, and as a result, they aren't even visible
 * under any other configuration.
 */

/**
 * curr_task - वापस the current task क्रम a given CPU.
 * @cpu: the processor in question.
 *
 * ONLY VALID WHEN THE WHOLE SYSTEM IS STOPPED!
 *
 * Return: The current task क्रम @cpu.
 */
काष्ठा task_काष्ठा *curr_task(पूर्णांक cpu)
अणु
	वापस cpu_curr(cpu);
पूर्ण

#पूर्ण_अगर /* defined(CONFIG_IA64) || defined(CONFIG_KGDB_KDB) */

#अगर_घोषित CONFIG_IA64
/**
 * ia64_set_curr_task - set the current task क्रम a given CPU.
 * @cpu: the processor in question.
 * @p: the task poपूर्णांकer to set.
 *
 * Description: This function must only be used when non-maskable पूर्णांकerrupts
 * are serviced on a separate stack. It allows the architecture to चयन the
 * notion of the current task on a CPU in a non-blocking manner. This function
 * must be called with all CPU's synchronized, and पूर्णांकerrupts disabled, the
 * and caller must save the original value of the current task (see
 * curr_task() above) and restore that value beक्रमe reenabling पूर्णांकerrupts and
 * re-starting the प्रणाली.
 *
 * ONLY VALID WHEN THE WHOLE SYSTEM IS STOPPED!
 */
व्योम ia64_set_curr_task(पूर्णांक cpu, काष्ठा task_काष्ठा *p)
अणु
	cpu_curr(cpu) = p;
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_CGROUP_SCHED
/* task_group_lock serializes the addition/removal of task groups */
अटल DEFINE_SPINLOCK(task_group_lock);

अटल अंतरभूत व्योम alloc_uclamp_sched_group(काष्ठा task_group *tg,
					    काष्ठा task_group *parent)
अणु
#अगर_घोषित CONFIG_UCLAMP_TASK_GROUP
	क्रमागत uclamp_id clamp_id;

	क्रम_each_clamp_id(clamp_id) अणु
		uclamp_se_set(&tg->uclamp_req[clamp_id],
			      uclamp_none(clamp_id), false);
		tg->uclamp[clamp_id] = parent->uclamp[clamp_id];
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम sched_मुक्त_group(काष्ठा task_group *tg)
अणु
	मुक्त_fair_sched_group(tg);
	मुक्त_rt_sched_group(tg);
	स्वतःgroup_मुक्त(tg);
	kmem_cache_मुक्त(task_group_cache, tg);
पूर्ण

/* allocate runqueue etc क्रम a new task group */
काष्ठा task_group *sched_create_group(काष्ठा task_group *parent)
अणु
	काष्ठा task_group *tg;

	tg = kmem_cache_alloc(task_group_cache, GFP_KERNEL | __GFP_ZERO);
	अगर (!tg)
		वापस ERR_PTR(-ENOMEM);

	अगर (!alloc_fair_sched_group(tg, parent))
		जाओ err;

	अगर (!alloc_rt_sched_group(tg, parent))
		जाओ err;

	alloc_uclamp_sched_group(tg, parent);

	वापस tg;

err:
	sched_मुक्त_group(tg);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

व्योम sched_online_group(काष्ठा task_group *tg, काष्ठा task_group *parent)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&task_group_lock, flags);
	list_add_rcu(&tg->list, &task_groups);

	/* Root should alपढ़ोy exist: */
	WARN_ON(!parent);

	tg->parent = parent;
	INIT_LIST_HEAD(&tg->children);
	list_add_rcu(&tg->siblings, &parent->children);
	spin_unlock_irqrestore(&task_group_lock, flags);

	online_fair_sched_group(tg);
पूर्ण

/* rcu callback to मुक्त various काष्ठाures associated with a task group */
अटल व्योम sched_मुक्त_group_rcu(काष्ठा rcu_head *rhp)
अणु
	/* Now it should be safe to मुक्त those cfs_rqs: */
	sched_मुक्त_group(container_of(rhp, काष्ठा task_group, rcu));
पूर्ण

व्योम sched_destroy_group(काष्ठा task_group *tg)
अणु
	/* Wait क्रम possible concurrent references to cfs_rqs complete: */
	call_rcu(&tg->rcu, sched_मुक्त_group_rcu);
पूर्ण

व्योम sched_offline_group(काष्ठा task_group *tg)
अणु
	अचिन्हित दीर्घ flags;

	/* End participation in shares distribution: */
	unरेजिस्टर_fair_sched_group(tg);

	spin_lock_irqsave(&task_group_lock, flags);
	list_del_rcu(&tg->list);
	list_del_rcu(&tg->siblings);
	spin_unlock_irqrestore(&task_group_lock, flags);
पूर्ण

अटल व्योम sched_change_group(काष्ठा task_काष्ठा *tsk, पूर्णांक type)
अणु
	काष्ठा task_group *tg;

	/*
	 * All callers are synchronized by task_rq_lock(); we करो not use RCU
	 * which is poपूर्णांकless here. Thus, we pass "true" to task_css_check()
	 * to prevent lockdep warnings.
	 */
	tg = container_of(task_css_check(tsk, cpu_cgrp_id, true),
			  काष्ठा task_group, css);
	tg = स्वतःgroup_task_group(tsk, tg);
	tsk->sched_task_group = tg;

#अगर_घोषित CONFIG_FAIR_GROUP_SCHED
	अगर (tsk->sched_class->task_change_group)
		tsk->sched_class->task_change_group(tsk, type);
	अन्यथा
#पूर्ण_अगर
		set_task_rq(tsk, task_cpu(tsk));
पूर्ण

/*
 * Change task's runqueue when it moves between groups.
 *
 * The caller of this function should have put the task in its new group by
 * now. This function just updates tsk->se.cfs_rq and tsk->se.parent to reflect
 * its new group.
 */
व्योम sched_move_task(काष्ठा task_काष्ठा *tsk)
अणु
	पूर्णांक queued, running, queue_flags =
		DEQUEUE_SAVE | DEQUEUE_MOVE | DEQUEUE_NOCLOCK;
	काष्ठा rq_flags rf;
	काष्ठा rq *rq;

	rq = task_rq_lock(tsk, &rf);
	update_rq_घड़ी(rq);

	running = task_current(rq, tsk);
	queued = task_on_rq_queued(tsk);

	अगर (queued)
		dequeue_task(rq, tsk, queue_flags);
	अगर (running)
		put_prev_task(rq, tsk);

	sched_change_group(tsk, TASK_MOVE_GROUP);

	अगर (queued)
		enqueue_task(rq, tsk, queue_flags);
	अगर (running) अणु
		set_next_task(rq, tsk);
		/*
		 * After changing group, the running task may have joined a
		 * throttled one but it's still the running task. Trigger a
		 * resched to make sure that task can still run.
		 */
		resched_curr(rq);
	पूर्ण

	task_rq_unlock(rq, tsk, &rf);
पूर्ण

अटल अंतरभूत काष्ठा task_group *css_tg(काष्ठा cgroup_subsys_state *css)
अणु
	वापस css ? container_of(css, काष्ठा task_group, css) : शून्य;
पूर्ण

अटल काष्ठा cgroup_subsys_state *
cpu_cgroup_css_alloc(काष्ठा cgroup_subsys_state *parent_css)
अणु
	काष्ठा task_group *parent = css_tg(parent_css);
	काष्ठा task_group *tg;

	अगर (!parent) अणु
		/* This is early initialization क्रम the top cgroup */
		वापस &root_task_group.css;
	पूर्ण

	tg = sched_create_group(parent);
	अगर (IS_ERR(tg))
		वापस ERR_PTR(-ENOMEM);

	वापस &tg->css;
पूर्ण

/* Expose task group only after completing cgroup initialization */
अटल पूर्णांक cpu_cgroup_css_online(काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा task_group *tg = css_tg(css);
	काष्ठा task_group *parent = css_tg(css->parent);

	अगर (parent)
		sched_online_group(tg, parent);

#अगर_घोषित CONFIG_UCLAMP_TASK_GROUP
	/* Propagate the effective uclamp value क्रम the new group */
	cpu_util_update_eff(css);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल व्योम cpu_cgroup_css_released(काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा task_group *tg = css_tg(css);

	sched_offline_group(tg);
पूर्ण

अटल व्योम cpu_cgroup_css_मुक्त(काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा task_group *tg = css_tg(css);

	/*
	 * Relies on the RCU grace period between css_released() and this.
	 */
	sched_मुक्त_group(tg);
पूर्ण

/*
 * This is called beक्रमe wake_up_new_task(), thereक्रमe we really only
 * have to set its group bits, all the other stuff करोes not apply.
 */
अटल व्योम cpu_cgroup_विभाजन(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा rq_flags rf;
	काष्ठा rq *rq;

	rq = task_rq_lock(task, &rf);

	update_rq_घड़ी(rq);
	sched_change_group(task, TASK_SET_GROUP);

	task_rq_unlock(rq, task, &rf);
पूर्ण

अटल पूर्णांक cpu_cgroup_can_attach(काष्ठा cgroup_taskset *tset)
अणु
	काष्ठा task_काष्ठा *task;
	काष्ठा cgroup_subsys_state *css;
	पूर्णांक ret = 0;

	cgroup_taskset_क्रम_each(task, css, tset) अणु
#अगर_घोषित CONFIG_RT_GROUP_SCHED
		अगर (!sched_rt_can_attach(css_tg(css), task))
			वापस -EINVAL;
#पूर्ण_अगर
		/*
		 * Serialize against wake_up_new_task() such that अगर it's
		 * running, we're sure to observe its full state.
		 */
		raw_spin_lock_irq(&task->pi_lock);
		/*
		 * Aव्योम calling sched_move_task() beक्रमe wake_up_new_task()
		 * has happened. This would lead to problems with PELT, due to
		 * move wanting to detach+attach जबतक we're not attached yet.
		 */
		अगर (task->state == TASK_NEW)
			ret = -EINVAL;
		raw_spin_unlock_irq(&task->pi_lock);

		अगर (ret)
			अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम cpu_cgroup_attach(काष्ठा cgroup_taskset *tset)
अणु
	काष्ठा task_काष्ठा *task;
	काष्ठा cgroup_subsys_state *css;

	cgroup_taskset_क्रम_each(task, css, tset)
		sched_move_task(task);
पूर्ण

#अगर_घोषित CONFIG_UCLAMP_TASK_GROUP
अटल व्योम cpu_util_update_eff(काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा cgroup_subsys_state *top_css = css;
	काष्ठा uclamp_se *uc_parent = शून्य;
	काष्ठा uclamp_se *uc_se = शून्य;
	अचिन्हित पूर्णांक eff[UCLAMP_CNT];
	क्रमागत uclamp_id clamp_id;
	अचिन्हित पूर्णांक clamps;

	css_क्रम_each_descendant_pre(css, top_css) अणु
		uc_parent = css_tg(css)->parent
			? css_tg(css)->parent->uclamp : शून्य;

		क्रम_each_clamp_id(clamp_id) अणु
			/* Assume effective clamps matches requested clamps */
			eff[clamp_id] = css_tg(css)->uclamp_req[clamp_id].value;
			/* Cap effective clamps with parent's effective clamps */
			अगर (uc_parent &&
			    eff[clamp_id] > uc_parent[clamp_id].value) अणु
				eff[clamp_id] = uc_parent[clamp_id].value;
			पूर्ण
		पूर्ण
		/* Ensure protection is always capped by limit */
		eff[UCLAMP_MIN] = min(eff[UCLAMP_MIN], eff[UCLAMP_MAX]);

		/* Propagate most restrictive effective clamps */
		clamps = 0x0;
		uc_se = css_tg(css)->uclamp;
		क्रम_each_clamp_id(clamp_id) अणु
			अगर (eff[clamp_id] == uc_se[clamp_id].value)
				जारी;
			uc_se[clamp_id].value = eff[clamp_id];
			uc_se[clamp_id].bucket_id = uclamp_bucket_id(eff[clamp_id]);
			clamps |= (0x1 << clamp_id);
		पूर्ण
		अगर (!clamps) अणु
			css = css_righपंचांगost_descendant(css);
			जारी;
		पूर्ण

		/* Immediately update descendants RUNNABLE tasks */
		uclamp_update_active_tasks(css, clamps);
	पूर्ण
पूर्ण

/*
 * Integer 10^N with a given N exponent by casting to पूर्णांकeger the literal "1eN"
 * C expression. Since there is no way to convert a macro argument (N) पूर्णांकo a
 * अक्षरacter स्थिरant, use two levels of macros.
 */
#घोषणा _POW10(exp) ((अचिन्हित पूर्णांक)1e##exp)
#घोषणा POW10(exp) _POW10(exp)

काष्ठा uclamp_request अणु
#घोषणा UCLAMP_PERCENT_SHIFT	2
#घोषणा UCLAMP_PERCENT_SCALE	(100 * POW10(UCLAMP_PERCENT_SHIFT))
	s64 percent;
	u64 util;
	पूर्णांक ret;
पूर्ण;

अटल अंतरभूत काष्ठा uclamp_request
capacity_from_percent(अक्षर *buf)
अणु
	काष्ठा uclamp_request req = अणु
		.percent = UCLAMP_PERCENT_SCALE,
		.util = SCHED_CAPACITY_SCALE,
		.ret = 0,
	पूर्ण;

	buf = strim(buf);
	अगर (म_भेद(buf, "max")) अणु
		req.ret = cgroup_parse_भग्न(buf, UCLAMP_PERCENT_SHIFT,
					     &req.percent);
		अगर (req.ret)
			वापस req;
		अगर ((u64)req.percent > UCLAMP_PERCENT_SCALE) अणु
			req.ret = -दुस्फल;
			वापस req;
		पूर्ण

		req.util = req.percent << SCHED_CAPACITY_SHIFT;
		req.util = DIV_ROUND_CLOSEST_ULL(req.util, UCLAMP_PERCENT_SCALE);
	पूर्ण

	वापस req;
पूर्ण

अटल sमाप_प्रकार cpu_uclamp_ग_लिखो(काष्ठा kernfs_खोलो_file *of, अक्षर *buf,
				माप_प्रकार nbytes, loff_t off,
				क्रमागत uclamp_id clamp_id)
अणु
	काष्ठा uclamp_request req;
	काष्ठा task_group *tg;

	req = capacity_from_percent(buf);
	अगर (req.ret)
		वापस req.ret;

	अटल_branch_enable(&sched_uclamp_used);

	mutex_lock(&uclamp_mutex);
	rcu_पढ़ो_lock();

	tg = css_tg(of_css(of));
	अगर (tg->uclamp_req[clamp_id].value != req.util)
		uclamp_se_set(&tg->uclamp_req[clamp_id], req.util, false);

	/*
	 * Because of not recoverable conversion rounding we keep track of the
	 * exact requested value
	 */
	tg->uclamp_pct[clamp_id] = req.percent;

	/* Update effective clamps to track the most restrictive value */
	cpu_util_update_eff(of_css(of));

	rcu_पढ़ो_unlock();
	mutex_unlock(&uclamp_mutex);

	वापस nbytes;
पूर्ण

अटल sमाप_प्रकार cpu_uclamp_min_ग_लिखो(काष्ठा kernfs_खोलो_file *of,
				    अक्षर *buf, माप_प्रकार nbytes,
				    loff_t off)
अणु
	वापस cpu_uclamp_ग_लिखो(of, buf, nbytes, off, UCLAMP_MIN);
पूर्ण

अटल sमाप_प्रकार cpu_uclamp_max_ग_लिखो(काष्ठा kernfs_खोलो_file *of,
				    अक्षर *buf, माप_प्रकार nbytes,
				    loff_t off)
अणु
	वापस cpu_uclamp_ग_लिखो(of, buf, nbytes, off, UCLAMP_MAX);
पूर्ण

अटल अंतरभूत व्योम cpu_uclamp_prपूर्णांक(काष्ठा seq_file *sf,
				    क्रमागत uclamp_id clamp_id)
अणु
	काष्ठा task_group *tg;
	u64 util_clamp;
	u64 percent;
	u32 rem;

	rcu_पढ़ो_lock();
	tg = css_tg(seq_css(sf));
	util_clamp = tg->uclamp_req[clamp_id].value;
	rcu_पढ़ो_unlock();

	अगर (util_clamp == SCHED_CAPACITY_SCALE) अणु
		seq_माला_दो(sf, "max\n");
		वापस;
	पूर्ण

	percent = tg->uclamp_pct[clamp_id];
	percent = भाग_u64_rem(percent, POW10(UCLAMP_PERCENT_SHIFT), &rem);
	seq_म_लिखो(sf, "%llu.%0*u\n", percent, UCLAMP_PERCENT_SHIFT, rem);
पूर्ण

अटल पूर्णांक cpu_uclamp_min_show(काष्ठा seq_file *sf, व्योम *v)
अणु
	cpu_uclamp_prपूर्णांक(sf, UCLAMP_MIN);
	वापस 0;
पूर्ण

अटल पूर्णांक cpu_uclamp_max_show(काष्ठा seq_file *sf, व्योम *v)
अणु
	cpu_uclamp_prपूर्णांक(sf, UCLAMP_MAX);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_UCLAMP_TASK_GROUP */

#अगर_घोषित CONFIG_FAIR_GROUP_SCHED
अटल पूर्णांक cpu_shares_ग_लिखो_u64(काष्ठा cgroup_subsys_state *css,
				काष्ठा cftype *cftype, u64 shareval)
अणु
	अगर (shareval > scale_load_करोwn(अच_दीर्घ_उच्च))
		shareval = MAX_SHARES;
	वापस sched_group_set_shares(css_tg(css), scale_load(shareval));
पूर्ण

अटल u64 cpu_shares_पढ़ो_u64(काष्ठा cgroup_subsys_state *css,
			       काष्ठा cftype *cft)
अणु
	काष्ठा task_group *tg = css_tg(css);

	वापस (u64) scale_load_करोwn(tg->shares);
पूर्ण

#अगर_घोषित CONFIG_CFS_BANDWIDTH
अटल DEFINE_MUTEX(cfs_स्थिरraपूर्णांकs_mutex);

स्थिर u64 max_cfs_quota_period = 1 * NSEC_PER_SEC; /* 1s */
अटल स्थिर u64 min_cfs_quota_period = 1 * NSEC_PER_MSEC; /* 1ms */
/* More than 203 days अगर BW_SHIFT equals 20. */
अटल स्थिर u64 max_cfs_runसमय = MAX_BW * NSEC_PER_USEC;

अटल पूर्णांक __cfs_schedulable(काष्ठा task_group *tg, u64 period, u64 runसमय);

अटल पूर्णांक tg_set_cfs_bandwidth(काष्ठा task_group *tg, u64 period, u64 quota)
अणु
	पूर्णांक i, ret = 0, runसमय_enabled, runसमय_was_enabled;
	काष्ठा cfs_bandwidth *cfs_b = &tg->cfs_bandwidth;

	अगर (tg == &root_task_group)
		वापस -EINVAL;

	/*
	 * Ensure we have at some amount of bandwidth every period.  This is
	 * to prevent reaching a state of large arrears when throttled via
	 * entity_tick() resulting in proदीर्घed निकास starvation.
	 */
	अगर (quota < min_cfs_quota_period || period < min_cfs_quota_period)
		वापस -EINVAL;

	/*
	 * Likewise, bound things on the other side by preventing insane quota
	 * periods.  This also allows us to normalize in computing quota
	 * feasibility.
	 */
	अगर (period > max_cfs_quota_period)
		वापस -EINVAL;

	/*
	 * Bound quota to defend quota against overflow during bandwidth shअगरt.
	 */
	अगर (quota != RUNTIME_INF && quota > max_cfs_runसमय)
		वापस -EINVAL;

	/*
	 * Prevent race between setting of cfs_rq->runसमय_enabled and
	 * unthrottle_offline_cfs_rqs().
	 */
	get_online_cpus();
	mutex_lock(&cfs_स्थिरraपूर्णांकs_mutex);
	ret = __cfs_schedulable(tg, period, quota);
	अगर (ret)
		जाओ out_unlock;

	runसमय_enabled = quota != RUNTIME_INF;
	runसमय_was_enabled = cfs_b->quota != RUNTIME_INF;
	/*
	 * If we need to toggle cfs_bandwidth_used, off->on must occur
	 * beक्रमe making related changes, and on->off must occur afterwards
	 */
	अगर (runसमय_enabled && !runसमय_was_enabled)
		cfs_bandwidth_usage_inc();
	raw_spin_lock_irq(&cfs_b->lock);
	cfs_b->period = ns_to_kसमय(period);
	cfs_b->quota = quota;

	__refill_cfs_bandwidth_runसमय(cfs_b);

	/* Restart the period समयr (अगर active) to handle new period expiry: */
	अगर (runसमय_enabled)
		start_cfs_bandwidth(cfs_b);

	raw_spin_unlock_irq(&cfs_b->lock);

	क्रम_each_online_cpu(i) अणु
		काष्ठा cfs_rq *cfs_rq = tg->cfs_rq[i];
		काष्ठा rq *rq = cfs_rq->rq;
		काष्ठा rq_flags rf;

		rq_lock_irq(rq, &rf);
		cfs_rq->runसमय_enabled = runसमय_enabled;
		cfs_rq->runसमय_reमुख्यing = 0;

		अगर (cfs_rq->throttled)
			unthrottle_cfs_rq(cfs_rq);
		rq_unlock_irq(rq, &rf);
	पूर्ण
	अगर (runसमय_was_enabled && !runसमय_enabled)
		cfs_bandwidth_usage_dec();
out_unlock:
	mutex_unlock(&cfs_स्थिरraपूर्णांकs_mutex);
	put_online_cpus();

	वापस ret;
पूर्ण

अटल पूर्णांक tg_set_cfs_quota(काष्ठा task_group *tg, दीर्घ cfs_quota_us)
अणु
	u64 quota, period;

	period = kसमय_प्रकारo_ns(tg->cfs_bandwidth.period);
	अगर (cfs_quota_us < 0)
		quota = RUNTIME_INF;
	अन्यथा अगर ((u64)cfs_quota_us <= U64_MAX / NSEC_PER_USEC)
		quota = (u64)cfs_quota_us * NSEC_PER_USEC;
	अन्यथा
		वापस -EINVAL;

	वापस tg_set_cfs_bandwidth(tg, period, quota);
पूर्ण

अटल दीर्घ tg_get_cfs_quota(काष्ठा task_group *tg)
अणु
	u64 quota_us;

	अगर (tg->cfs_bandwidth.quota == RUNTIME_INF)
		वापस -1;

	quota_us = tg->cfs_bandwidth.quota;
	करो_भाग(quota_us, NSEC_PER_USEC);

	वापस quota_us;
पूर्ण

अटल पूर्णांक tg_set_cfs_period(काष्ठा task_group *tg, दीर्घ cfs_period_us)
अणु
	u64 quota, period;

	अगर ((u64)cfs_period_us > U64_MAX / NSEC_PER_USEC)
		वापस -EINVAL;

	period = (u64)cfs_period_us * NSEC_PER_USEC;
	quota = tg->cfs_bandwidth.quota;

	वापस tg_set_cfs_bandwidth(tg, period, quota);
पूर्ण

अटल दीर्घ tg_get_cfs_period(काष्ठा task_group *tg)
अणु
	u64 cfs_period_us;

	cfs_period_us = kसमय_प्रकारo_ns(tg->cfs_bandwidth.period);
	करो_भाग(cfs_period_us, NSEC_PER_USEC);

	वापस cfs_period_us;
पूर्ण

अटल s64 cpu_cfs_quota_पढ़ो_s64(काष्ठा cgroup_subsys_state *css,
				  काष्ठा cftype *cft)
अणु
	वापस tg_get_cfs_quota(css_tg(css));
पूर्ण

अटल पूर्णांक cpu_cfs_quota_ग_लिखो_s64(काष्ठा cgroup_subsys_state *css,
				   काष्ठा cftype *cftype, s64 cfs_quota_us)
अणु
	वापस tg_set_cfs_quota(css_tg(css), cfs_quota_us);
पूर्ण

अटल u64 cpu_cfs_period_पढ़ो_u64(काष्ठा cgroup_subsys_state *css,
				   काष्ठा cftype *cft)
अणु
	वापस tg_get_cfs_period(css_tg(css));
पूर्ण

अटल पूर्णांक cpu_cfs_period_ग_लिखो_u64(काष्ठा cgroup_subsys_state *css,
				    काष्ठा cftype *cftype, u64 cfs_period_us)
अणु
	वापस tg_set_cfs_period(css_tg(css), cfs_period_us);
पूर्ण

काष्ठा cfs_schedulable_data अणु
	काष्ठा task_group *tg;
	u64 period, quota;
पूर्ण;

/*
 * normalize group quota/period to be quota/max_period
 * note: units are usecs
 */
अटल u64 normalize_cfs_quota(काष्ठा task_group *tg,
			       काष्ठा cfs_schedulable_data *d)
अणु
	u64 quota, period;

	अगर (tg == d->tg) अणु
		period = d->period;
		quota = d->quota;
	पूर्ण अन्यथा अणु
		period = tg_get_cfs_period(tg);
		quota = tg_get_cfs_quota(tg);
	पूर्ण

	/* note: these should typically be equivalent */
	अगर (quota == RUNTIME_INF || quota == -1)
		वापस RUNTIME_INF;

	वापस to_ratio(period, quota);
पूर्ण

अटल पूर्णांक tg_cfs_schedulable_करोwn(काष्ठा task_group *tg, व्योम *data)
अणु
	काष्ठा cfs_schedulable_data *d = data;
	काष्ठा cfs_bandwidth *cfs_b = &tg->cfs_bandwidth;
	s64 quota = 0, parent_quota = -1;

	अगर (!tg->parent) अणु
		quota = RUNTIME_INF;
	पूर्ण अन्यथा अणु
		काष्ठा cfs_bandwidth *parent_b = &tg->parent->cfs_bandwidth;

		quota = normalize_cfs_quota(tg, d);
		parent_quota = parent_b->hierarchical_quota;

		/*
		 * Ensure max(child_quota) <= parent_quota.  On cgroup2,
		 * always take the min.  On cgroup1, only inherit when no
		 * limit is set:
		 */
		अगर (cgroup_subsys_on_dfl(cpu_cgrp_subsys)) अणु
			quota = min(quota, parent_quota);
		पूर्ण अन्यथा अणु
			अगर (quota == RUNTIME_INF)
				quota = parent_quota;
			अन्यथा अगर (parent_quota != RUNTIME_INF && quota > parent_quota)
				वापस -EINVAL;
		पूर्ण
	पूर्ण
	cfs_b->hierarchical_quota = quota;

	वापस 0;
पूर्ण

अटल पूर्णांक __cfs_schedulable(काष्ठा task_group *tg, u64 period, u64 quota)
अणु
	पूर्णांक ret;
	काष्ठा cfs_schedulable_data data = अणु
		.tg = tg,
		.period = period,
		.quota = quota,
	पूर्ण;

	अगर (quota != RUNTIME_INF) अणु
		करो_भाग(data.period, NSEC_PER_USEC);
		करो_भाग(data.quota, NSEC_PER_USEC);
	पूर्ण

	rcu_पढ़ो_lock();
	ret = walk_tg_tree(tg_cfs_schedulable_करोwn, tg_nop, &data);
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

अटल पूर्णांक cpu_cfs_stat_show(काष्ठा seq_file *sf, व्योम *v)
अणु
	काष्ठा task_group *tg = css_tg(seq_css(sf));
	काष्ठा cfs_bandwidth *cfs_b = &tg->cfs_bandwidth;

	seq_म_लिखो(sf, "nr_periods %d\n", cfs_b->nr_periods);
	seq_म_लिखो(sf, "nr_throttled %d\n", cfs_b->nr_throttled);
	seq_म_लिखो(sf, "throttled_time %llu\n", cfs_b->throttled_समय);

	अगर (schedstat_enabled() && tg != &root_task_group) अणु
		u64 ws = 0;
		पूर्णांक i;

		क्रम_each_possible_cpu(i)
			ws += schedstat_val(tg->se[i]->statistics.रुको_sum);

		seq_म_लिखो(sf, "wait_sum %llu\n", ws);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_CFS_BANDWIDTH */
#पूर्ण_अगर /* CONFIG_FAIR_GROUP_SCHED */

#अगर_घोषित CONFIG_RT_GROUP_SCHED
अटल पूर्णांक cpu_rt_runसमय_ग_लिखो(काष्ठा cgroup_subsys_state *css,
				काष्ठा cftype *cft, s64 val)
अणु
	वापस sched_group_set_rt_runसमय(css_tg(css), val);
पूर्ण

अटल s64 cpu_rt_runसमय_पढ़ो(काष्ठा cgroup_subsys_state *css,
			       काष्ठा cftype *cft)
अणु
	वापस sched_group_rt_runसमय(css_tg(css));
पूर्ण

अटल पूर्णांक cpu_rt_period_ग_लिखो_uपूर्णांक(काष्ठा cgroup_subsys_state *css,
				    काष्ठा cftype *cftype, u64 rt_period_us)
अणु
	वापस sched_group_set_rt_period(css_tg(css), rt_period_us);
पूर्ण

अटल u64 cpu_rt_period_पढ़ो_uपूर्णांक(काष्ठा cgroup_subsys_state *css,
				   काष्ठा cftype *cft)
अणु
	वापस sched_group_rt_period(css_tg(css));
पूर्ण
#पूर्ण_अगर /* CONFIG_RT_GROUP_SCHED */

अटल काष्ठा cftype cpu_legacy_files[] = अणु
#अगर_घोषित CONFIG_FAIR_GROUP_SCHED
	अणु
		.name = "shares",
		.पढ़ो_u64 = cpu_shares_पढ़ो_u64,
		.ग_लिखो_u64 = cpu_shares_ग_लिखो_u64,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CFS_BANDWIDTH
	अणु
		.name = "cfs_quota_us",
		.पढ़ो_s64 = cpu_cfs_quota_पढ़ो_s64,
		.ग_लिखो_s64 = cpu_cfs_quota_ग_लिखो_s64,
	पूर्ण,
	अणु
		.name = "cfs_period_us",
		.पढ़ो_u64 = cpu_cfs_period_पढ़ो_u64,
		.ग_लिखो_u64 = cpu_cfs_period_ग_लिखो_u64,
	पूर्ण,
	अणु
		.name = "stat",
		.seq_show = cpu_cfs_stat_show,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_RT_GROUP_SCHED
	अणु
		.name = "rt_runtime_us",
		.पढ़ो_s64 = cpu_rt_runसमय_पढ़ो,
		.ग_लिखो_s64 = cpu_rt_runसमय_ग_लिखो,
	पूर्ण,
	अणु
		.name = "rt_period_us",
		.पढ़ो_u64 = cpu_rt_period_पढ़ो_uपूर्णांक,
		.ग_लिखो_u64 = cpu_rt_period_ग_लिखो_uपूर्णांक,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_UCLAMP_TASK_GROUP
	अणु
		.name = "uclamp.min",
		.flags = CFTYPE_NOT_ON_ROOT,
		.seq_show = cpu_uclamp_min_show,
		.ग_लिखो = cpu_uclamp_min_ग_लिखो,
	पूर्ण,
	अणु
		.name = "uclamp.max",
		.flags = CFTYPE_NOT_ON_ROOT,
		.seq_show = cpu_uclamp_max_show,
		.ग_लिखो = cpu_uclamp_max_ग_लिखो,
	पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण	/* Terminate */
पूर्ण;

अटल पूर्णांक cpu_extra_stat_show(काष्ठा seq_file *sf,
			       काष्ठा cgroup_subsys_state *css)
अणु
#अगर_घोषित CONFIG_CFS_BANDWIDTH
	अणु
		काष्ठा task_group *tg = css_tg(css);
		काष्ठा cfs_bandwidth *cfs_b = &tg->cfs_bandwidth;
		u64 throttled_usec;

		throttled_usec = cfs_b->throttled_समय;
		करो_भाग(throttled_usec, NSEC_PER_USEC);

		seq_म_लिखो(sf, "nr_periods %d\n"
			   "nr_throttled %d\n"
			   "throttled_usec %llu\n",
			   cfs_b->nr_periods, cfs_b->nr_throttled,
			   throttled_usec);
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_FAIR_GROUP_SCHED
अटल u64 cpu_weight_पढ़ो_u64(काष्ठा cgroup_subsys_state *css,
			       काष्ठा cftype *cft)
अणु
	काष्ठा task_group *tg = css_tg(css);
	u64 weight = scale_load_करोwn(tg->shares);

	वापस DIV_ROUND_CLOSEST_ULL(weight * CGROUP_WEIGHT_DFL, 1024);
पूर्ण

अटल पूर्णांक cpu_weight_ग_लिखो_u64(काष्ठा cgroup_subsys_state *css,
				काष्ठा cftype *cft, u64 weight)
अणु
	/*
	 * cgroup weight knobs should use the common MIN, DFL and MAX
	 * values which are 1, 100 and 10000 respectively.  While it loses
	 * a bit of range on both ends, it maps pretty well onto the shares
	 * value used by scheduler and the round-trip conversions preserve
	 * the original value over the entire range.
	 */
	अगर (weight < CGROUP_WEIGHT_MIN || weight > CGROUP_WEIGHT_MAX)
		वापस -दुस्फल;

	weight = DIV_ROUND_CLOSEST_ULL(weight * 1024, CGROUP_WEIGHT_DFL);

	वापस sched_group_set_shares(css_tg(css), scale_load(weight));
पूर्ण

अटल s64 cpu_weight_nice_पढ़ो_s64(काष्ठा cgroup_subsys_state *css,
				    काष्ठा cftype *cft)
अणु
	अचिन्हित दीर्घ weight = scale_load_करोwn(css_tg(css)->shares);
	पूर्णांक last_delta = पूर्णांक_उच्च;
	पूर्णांक prio, delta;

	/* find the बंदst nice value to the current weight */
	क्रम (prio = 0; prio < ARRAY_SIZE(sched_prio_to_weight); prio++) अणु
		delta = असल(sched_prio_to_weight[prio] - weight);
		अगर (delta >= last_delta)
			अवरोध;
		last_delta = delta;
	पूर्ण

	वापस PRIO_TO_NICE(prio - 1 + MAX_RT_PRIO);
पूर्ण

अटल पूर्णांक cpu_weight_nice_ग_लिखो_s64(काष्ठा cgroup_subsys_state *css,
				     काष्ठा cftype *cft, s64 nice)
अणु
	अचिन्हित दीर्घ weight;
	पूर्णांक idx;

	अगर (nice < MIN_NICE || nice > MAX_NICE)
		वापस -दुस्फल;

	idx = NICE_TO_PRIO(nice) - MAX_RT_PRIO;
	idx = array_index_nospec(idx, 40);
	weight = sched_prio_to_weight[idx];

	वापस sched_group_set_shares(css_tg(css), scale_load(weight));
पूर्ण
#पूर्ण_अगर

अटल व्योम __maybe_unused cpu_period_quota_prपूर्णांक(काष्ठा seq_file *sf,
						  दीर्घ period, दीर्घ quota)
अणु
	अगर (quota < 0)
		seq_माला_दो(sf, "max");
	अन्यथा
		seq_म_लिखो(sf, "%ld", quota);

	seq_म_लिखो(sf, " %ld\n", period);
पूर्ण

/* caller should put the current value in *@periodp beक्रमe calling */
अटल पूर्णांक __maybe_unused cpu_period_quota_parse(अक्षर *buf,
						 u64 *periodp, u64 *quotap)
अणु
	अक्षर tok[21];	/* U64_MAX */

	अगर (माला_पूछो(buf, "%20s %llu", tok, periodp) < 1)
		वापस -EINVAL;

	*periodp *= NSEC_PER_USEC;

	अगर (माला_पूछो(tok, "%llu", quotap))
		*quotap *= NSEC_PER_USEC;
	अन्यथा अगर (!म_भेद(tok, "max"))
		*quotap = RUNTIME_INF;
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_CFS_BANDWIDTH
अटल पूर्णांक cpu_max_show(काष्ठा seq_file *sf, व्योम *v)
अणु
	काष्ठा task_group *tg = css_tg(seq_css(sf));

	cpu_period_quota_prपूर्णांक(sf, tg_get_cfs_period(tg), tg_get_cfs_quota(tg));
	वापस 0;
पूर्ण

अटल sमाप_प्रकार cpu_max_ग_लिखो(काष्ठा kernfs_खोलो_file *of,
			     अक्षर *buf, माप_प्रकार nbytes, loff_t off)
अणु
	काष्ठा task_group *tg = css_tg(of_css(of));
	u64 period = tg_get_cfs_period(tg);
	u64 quota;
	पूर्णांक ret;

	ret = cpu_period_quota_parse(buf, &period, &quota);
	अगर (!ret)
		ret = tg_set_cfs_bandwidth(tg, period, quota);
	वापस ret ?: nbytes;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा cftype cpu_files[] = अणु
#अगर_घोषित CONFIG_FAIR_GROUP_SCHED
	अणु
		.name = "weight",
		.flags = CFTYPE_NOT_ON_ROOT,
		.पढ़ो_u64 = cpu_weight_पढ़ो_u64,
		.ग_लिखो_u64 = cpu_weight_ग_लिखो_u64,
	पूर्ण,
	अणु
		.name = "weight.nice",
		.flags = CFTYPE_NOT_ON_ROOT,
		.पढ़ो_s64 = cpu_weight_nice_पढ़ो_s64,
		.ग_लिखो_s64 = cpu_weight_nice_ग_लिखो_s64,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CFS_BANDWIDTH
	अणु
		.name = "max",
		.flags = CFTYPE_NOT_ON_ROOT,
		.seq_show = cpu_max_show,
		.ग_लिखो = cpu_max_ग_लिखो,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_UCLAMP_TASK_GROUP
	अणु
		.name = "uclamp.min",
		.flags = CFTYPE_NOT_ON_ROOT,
		.seq_show = cpu_uclamp_min_show,
		.ग_लिखो = cpu_uclamp_min_ग_लिखो,
	पूर्ण,
	अणु
		.name = "uclamp.max",
		.flags = CFTYPE_NOT_ON_ROOT,
		.seq_show = cpu_uclamp_max_show,
		.ग_लिखो = cpu_uclamp_max_ग_लिखो,
	पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण	/* terminate */
पूर्ण;

काष्ठा cgroup_subsys cpu_cgrp_subsys = अणु
	.css_alloc	= cpu_cgroup_css_alloc,
	.css_online	= cpu_cgroup_css_online,
	.css_released	= cpu_cgroup_css_released,
	.css_मुक्त	= cpu_cgroup_css_मुक्त,
	.css_extra_stat_show = cpu_extra_stat_show,
	.विभाजन		= cpu_cgroup_विभाजन,
	.can_attach	= cpu_cgroup_can_attach,
	.attach		= cpu_cgroup_attach,
	.legacy_cftypes	= cpu_legacy_files,
	.dfl_cftypes	= cpu_files,
	.early_init	= true,
	.thपढ़ोed	= true,
पूर्ण;

#पूर्ण_अगर	/* CONFIG_CGROUP_SCHED */

व्योम dump_cpu_task(पूर्णांक cpu)
अणु
	pr_info("Task dump for CPU %d:\n", cpu);
	sched_show_task(cpu_curr(cpu));
पूर्ण

/*
 * Nice levels are multiplicative, with a gentle 10% change क्रम every
 * nice level changed. I.e. when a CPU-bound task goes from nice 0 to
 * nice 1, it will get ~10% less CPU समय than another CPU-bound task
 * that reमुख्यed on nice 0.
 *
 * The "10% effect" is relative and cumulative: from _any_ nice level,
 * अगर you go up 1 level, it's -10% CPU usage, अगर you go करोwn 1 level
 * it's +10% CPU usage. (to achieve that we use a multiplier of 1.25.
 * If a task goes up by ~10% and another task goes करोwn by ~10% then
 * the relative distance between them is ~25%.)
 */
स्थिर पूर्णांक sched_prio_to_weight[40] = अणु
 /* -20 */     88761,     71755,     56483,     46273,     36291,
 /* -15 */     29154,     23254,     18705,     14949,     11916,
 /* -10 */      9548,      7620,      6100,      4904,      3906,
 /*  -5 */      3121,      2501,      1991,      1586,      1277,
 /*   0 */      1024,       820,       655,       526,       423,
 /*   5 */       335,       272,       215,       172,       137,
 /*  10 */       110,        87,        70,        56,        45,
 /*  15 */        36,        29,        23,        18,        15,
पूर्ण;

/*
 * Inverse (2^32/x) values of the sched_prio_to_weight[] array, precalculated.
 *
 * In हालs where the weight करोes not change often, we can use the
 * precalculated inverse to speed up arithmetics by turning भागisions
 * पूर्णांकo multiplications:
 */
स्थिर u32 sched_prio_to_wmult[40] = अणु
 /* -20 */     48388,     59856,     76040,     92818,    118348,
 /* -15 */    147320,    184698,    229616,    287308,    360437,
 /* -10 */    449829,    563644,    704093,    875809,   1099582,
 /*  -5 */   1376151,   1717300,   2157191,   2708050,   3363326,
 /*   0 */   4194304,   5237765,   6557202,   8165337,  10153587,
 /*   5 */  12820798,  15790321,  19976592,  24970740,  31350126,
 /*  10 */  39045157,  49367440,  61356676,  76695844,  95443717,
 /*  15 */ 119304647, 148102320, 186737708, 238609294, 286331153,
पूर्ण;

व्योम call_trace_sched_update_nr_running(काष्ठा rq *rq, पूर्णांक count)
अणु
        trace_sched_update_nr_running_tp(rq, count);
पूर्ण
