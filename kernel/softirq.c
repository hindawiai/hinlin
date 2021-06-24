<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	linux/kernel/softirq.c
 *
 *	Copyright (C) 1992 Linus Torvalds
 *
 *	Rewritten. Old one was good in 2.2, but in 2.3 it was immoral. --ANK (990903)
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/export.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/local_lock.h>
#समावेश <linux/mm.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/percpu.h>
#समावेश <linux/cpu.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/smp.h>
#समावेश <linux/smpboot.h>
#समावेश <linux/tick.h>
#समावेश <linux/irq.h>
#समावेश <linux/रुको_bit.h>

#समावेश <यंत्र/softirq_stack.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/irq.h>

/*
   - No shared variables, all the data are CPU local.
   - If a softirq needs serialization, let it serialize itself
     by its own spinlocks.
   - Even अगर softirq is serialized, only local cpu is marked क्रम
     execution. Hence, we get something sort of weak cpu binding.
     Though it is still not clear, will it result in better locality
     or will not.

   Examples:
   - NET RX softirq. It is multithपढ़ोed and करोes not require
     any global serialization.
   - NET TX softirq. It kicks software netdevice queues, hence
     it is logically serialized per device, but this serialization
     is invisible to common code.
   - Tasklets: serialized wrt itself.
 */

#अगर_अघोषित __ARCH_IRQ_STAT
DEFINE_PER_CPU_ALIGNED(irq_cpustat_t, irq_stat);
EXPORT_PER_CPU_SYMBOL(irq_stat);
#पूर्ण_अगर

अटल काष्ठा softirq_action softirq_vec[NR_SOFTIRQS] __cacheline_aligned_in_smp;

DEFINE_PER_CPU(काष्ठा task_काष्ठा *, ksoftirqd);

स्थिर अक्षर * स्थिर softirq_to_name[NR_SOFTIRQS] = अणु
	"HI", "TIMER", "NET_TX", "NET_RX", "BLOCK", "IRQ_POLL",
	"TASKLET", "SCHED", "HRTIMER", "RCU"
पूर्ण;

/*
 * we cannot loop indefinitely here to aव्योम userspace starvation,
 * but we also करोn't want to पूर्णांकroduce a worst हाल 1/HZ latency
 * to the pending events, so lets the scheduler to balance
 * the softirq load क्रम us.
 */
अटल व्योम wakeup_softirqd(व्योम)
अणु
	/* Interrupts are disabled: no need to stop preemption */
	काष्ठा task_काष्ठा *tsk = __this_cpu_पढ़ो(ksoftirqd);

	अगर (tsk && tsk->state != TASK_RUNNING)
		wake_up_process(tsk);
पूर्ण

/*
 * If ksoftirqd is scheduled, we करो not want to process pending softirqs
 * right now. Let ksoftirqd handle this at its own rate, to get fairness,
 * unless we're करोing some of the synchronous softirqs.
 */
#घोषणा SOFTIRQ_NOW_MASK ((1 << HI_SOFTIRQ) | (1 << TASKLET_SOFTIRQ))
अटल bool ksoftirqd_running(अचिन्हित दीर्घ pending)
अणु
	काष्ठा task_काष्ठा *tsk = __this_cpu_पढ़ो(ksoftirqd);

	अगर (pending & SOFTIRQ_NOW_MASK)
		वापस false;
	वापस tsk && (tsk->state == TASK_RUNNING) &&
		!__kthपढ़ो_should_park(tsk);
पूर्ण

#अगर_घोषित CONFIG_TRACE_IRQFLAGS
DEFINE_PER_CPU(पूर्णांक, hardirqs_enabled);
DEFINE_PER_CPU(पूर्णांक, hardirq_context);
EXPORT_PER_CPU_SYMBOL_GPL(hardirqs_enabled);
EXPORT_PER_CPU_SYMBOL_GPL(hardirq_context);
#पूर्ण_अगर

/*
 * SOFTIRQ_OFFSET usage:
 *
 * On !RT kernels 'count' is the preempt counter, on RT kernels this applies
 * to a per CPU counter and to task::softirqs_disabled_cnt.
 *
 * - count is changed by SOFTIRQ_OFFSET on entering or leaving softirq
 *   processing.
 *
 * - count is changed by SOFTIRQ_DISABLE_OFFSET (= 2 * SOFTIRQ_OFFSET)
 *   on local_bh_disable or local_bh_enable.
 *
 * This lets us distinguish between whether we are currently processing
 * softirq and whether we just have bh disabled.
 */
#अगर_घोषित CONFIG_PREEMPT_RT

/*
 * RT accounts क्रम BH disabled sections in task::softirqs_disabled_cnt and
 * also in per CPU softirq_ctrl::cnt. This is necessary to allow tasks in a
 * softirq disabled section to be preempted.
 *
 * The per task counter is used क्रम softirq_count(), in_softirq() and
 * in_serving_softirqs() because these counts are only valid when the task
 * holding softirq_ctrl::lock is running.
 *
 * The per CPU counter prevents poपूर्णांकless wakeups of ksoftirqd in हाल that
 * the task which is in a softirq disabled section is preempted or blocks.
 */
काष्ठा softirq_ctrl अणु
	local_lock_t	lock;
	पूर्णांक		cnt;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा softirq_ctrl, softirq_ctrl) = अणु
	.lock	= INIT_LOCAL_LOCK(softirq_ctrl.lock),
पूर्ण;

/**
 * local_bh_blocked() - Check क्रम idle whether BH processing is blocked
 *
 * Returns false अगर the per CPU softirq::cnt is 0 otherwise true.
 *
 * This is invoked from the idle task to guard against false positive
 * softirq pending warnings, which would happen when the task which holds
 * softirq_ctrl::lock was the only running task on the CPU and blocks on
 * some other lock.
 */
bool local_bh_blocked(व्योम)
अणु
	वापस __this_cpu_पढ़ो(softirq_ctrl.cnt) != 0;
पूर्ण

व्योम __local_bh_disable_ip(अचिन्हित दीर्घ ip, अचिन्हित पूर्णांक cnt)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक newcnt;

	WARN_ON_ONCE(in_hardirq());

	/* First entry of a task पूर्णांकo a BH disabled section? */
	अगर (!current->softirq_disable_cnt) अणु
		अगर (preemptible()) अणु
			local_lock(&softirq_ctrl.lock);
			/* Required to meet the RCU bottomhalf requirements. */
			rcu_पढ़ो_lock();
		पूर्ण अन्यथा अणु
			DEBUG_LOCKS_WARN_ON(this_cpu_पढ़ो(softirq_ctrl.cnt));
		पूर्ण
	पूर्ण

	/*
	 * Track the per CPU softirq disabled state. On RT this is per CPU
	 * state to allow preemption of bottom half disabled sections.
	 */
	newcnt = __this_cpu_add_वापस(softirq_ctrl.cnt, cnt);
	/*
	 * Reflect the result in the task state to prevent recursion on the
	 * local lock and to make softirq_count() & al work.
	 */
	current->softirq_disable_cnt = newcnt;

	अगर (IS_ENABLED(CONFIG_TRACE_IRQFLAGS) && newcnt == cnt) अणु
		raw_local_irq_save(flags);
		lockdep_softirqs_off(ip);
		raw_local_irq_restore(flags);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__local_bh_disable_ip);

अटल व्योम __local_bh_enable(अचिन्हित पूर्णांक cnt, bool unlock)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक newcnt;

	DEBUG_LOCKS_WARN_ON(current->softirq_disable_cnt !=
			    this_cpu_पढ़ो(softirq_ctrl.cnt));

	अगर (IS_ENABLED(CONFIG_TRACE_IRQFLAGS) && softirq_count() == cnt) अणु
		raw_local_irq_save(flags);
		lockdep_softirqs_on(_RET_IP_);
		raw_local_irq_restore(flags);
	पूर्ण

	newcnt = __this_cpu_sub_वापस(softirq_ctrl.cnt, cnt);
	current->softirq_disable_cnt = newcnt;

	अगर (!newcnt && unlock) अणु
		rcu_पढ़ो_unlock();
		local_unlock(&softirq_ctrl.lock);
	पूर्ण
पूर्ण

व्योम __local_bh_enable_ip(अचिन्हित दीर्घ ip, अचिन्हित पूर्णांक cnt)
अणु
	bool preempt_on = preemptible();
	अचिन्हित दीर्घ flags;
	u32 pending;
	पूर्णांक curcnt;

	WARN_ON_ONCE(in_irq());
	lockdep_निश्चित_irqs_enabled();

	local_irq_save(flags);
	curcnt = __this_cpu_पढ़ो(softirq_ctrl.cnt);

	/*
	 * If this is not reenabling soft पूर्णांकerrupts, no poपूर्णांक in trying to
	 * run pending ones.
	 */
	अगर (curcnt != cnt)
		जाओ out;

	pending = local_softirq_pending();
	अगर (!pending || ksoftirqd_running(pending))
		जाओ out;

	/*
	 * If this was called from non preemptible context, wake up the
	 * softirq daemon.
	 */
	अगर (!preempt_on) अणु
		wakeup_softirqd();
		जाओ out;
	पूर्ण

	/*
	 * Adjust softirq count to SOFTIRQ_OFFSET which makes
	 * in_serving_softirq() become true.
	 */
	cnt = SOFTIRQ_OFFSET;
	__local_bh_enable(cnt, false);
	__करो_softirq();

out:
	__local_bh_enable(cnt, preempt_on);
	local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL(__local_bh_enable_ip);

/*
 * Invoked from ksoftirqd_run() outside of the पूर्णांकerrupt disabled section
 * to acquire the per CPU local lock क्रम reentrancy protection.
 */
अटल अंतरभूत व्योम ksoftirqd_run_begin(व्योम)
अणु
	__local_bh_disable_ip(_RET_IP_, SOFTIRQ_OFFSET);
	local_irq_disable();
पूर्ण

/* Counterpart to ksoftirqd_run_begin() */
अटल अंतरभूत व्योम ksoftirqd_run_end(व्योम)
अणु
	__local_bh_enable(SOFTIRQ_OFFSET, true);
	WARN_ON_ONCE(in_पूर्णांकerrupt());
	local_irq_enable();
पूर्ण

अटल अंतरभूत व्योम softirq_handle_begin(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम softirq_handle_end(व्योम) अणु पूर्ण

अटल अंतरभूत bool should_wake_ksoftirqd(व्योम)
अणु
	वापस !this_cpu_पढ़ो(softirq_ctrl.cnt);
पूर्ण

अटल अंतरभूत व्योम invoke_softirq(व्योम)
अणु
	अगर (should_wake_ksoftirqd())
		wakeup_softirqd();
पूर्ण

#अन्यथा /* CONFIG_PREEMPT_RT */

/*
 * This one is क्रम softirq.c-पूर्णांकernal use, where hardirqs are disabled
 * legitimately:
 */
#अगर_घोषित CONFIG_TRACE_IRQFLAGS
व्योम __local_bh_disable_ip(अचिन्हित दीर्घ ip, अचिन्हित पूर्णांक cnt)
अणु
	अचिन्हित दीर्घ flags;

	WARN_ON_ONCE(in_irq());

	raw_local_irq_save(flags);
	/*
	 * The preempt tracer hooks पूर्णांकo preempt_count_add and will अवरोध
	 * lockdep because it calls back पूर्णांकo lockdep after SOFTIRQ_OFFSET
	 * is set and beक्रमe current->softirq_enabled is cleared.
	 * We must manually increment preempt_count here and manually
	 * call the trace_preempt_off later.
	 */
	__preempt_count_add(cnt);
	/*
	 * Were softirqs turned off above:
	 */
	अगर (softirq_count() == (cnt & SOFTIRQ_MASK))
		lockdep_softirqs_off(ip);
	raw_local_irq_restore(flags);

	अगर (preempt_count() == cnt) अणु
#अगर_घोषित CONFIG_DEBUG_PREEMPT
		current->preempt_disable_ip = get_lock_parent_ip();
#पूर्ण_अगर
		trace_preempt_off(CALLER_ADDR0, get_lock_parent_ip());
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__local_bh_disable_ip);
#पूर्ण_अगर /* CONFIG_TRACE_IRQFLAGS */

अटल व्योम __local_bh_enable(अचिन्हित पूर्णांक cnt)
अणु
	lockdep_निश्चित_irqs_disabled();

	अगर (preempt_count() == cnt)
		trace_preempt_on(CALLER_ADDR0, get_lock_parent_ip());

	अगर (softirq_count() == (cnt & SOFTIRQ_MASK))
		lockdep_softirqs_on(_RET_IP_);

	__preempt_count_sub(cnt);
पूर्ण

/*
 * Special-हाल - softirqs can safely be enabled by __करो_softirq(),
 * without processing still-pending softirqs:
 */
व्योम _local_bh_enable(व्योम)
अणु
	WARN_ON_ONCE(in_irq());
	__local_bh_enable(SOFTIRQ_DISABLE_OFFSET);
पूर्ण
EXPORT_SYMBOL(_local_bh_enable);

व्योम __local_bh_enable_ip(अचिन्हित दीर्घ ip, अचिन्हित पूर्णांक cnt)
अणु
	WARN_ON_ONCE(in_irq());
	lockdep_निश्चित_irqs_enabled();
#अगर_घोषित CONFIG_TRACE_IRQFLAGS
	local_irq_disable();
#पूर्ण_अगर
	/*
	 * Are softirqs going to be turned on now:
	 */
	अगर (softirq_count() == SOFTIRQ_DISABLE_OFFSET)
		lockdep_softirqs_on(ip);
	/*
	 * Keep preemption disabled until we are करोne with
	 * softirq processing:
	 */
	__preempt_count_sub(cnt - 1);

	अगर (unlikely(!in_पूर्णांकerrupt() && local_softirq_pending())) अणु
		/*
		 * Run softirq अगर any pending. And करो it in its own stack
		 * as we may be calling this deep in a task call stack alपढ़ोy.
		 */
		करो_softirq();
	पूर्ण

	preempt_count_dec();
#अगर_घोषित CONFIG_TRACE_IRQFLAGS
	local_irq_enable();
#पूर्ण_अगर
	preempt_check_resched();
पूर्ण
EXPORT_SYMBOL(__local_bh_enable_ip);

अटल अंतरभूत व्योम softirq_handle_begin(व्योम)
अणु
	__local_bh_disable_ip(_RET_IP_, SOFTIRQ_OFFSET);
पूर्ण

अटल अंतरभूत व्योम softirq_handle_end(व्योम)
अणु
	__local_bh_enable(SOFTIRQ_OFFSET);
	WARN_ON_ONCE(in_पूर्णांकerrupt());
पूर्ण

अटल अंतरभूत व्योम ksoftirqd_run_begin(व्योम)
अणु
	local_irq_disable();
पूर्ण

अटल अंतरभूत व्योम ksoftirqd_run_end(व्योम)
अणु
	local_irq_enable();
पूर्ण

अटल अंतरभूत bool should_wake_ksoftirqd(व्योम)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत व्योम invoke_softirq(व्योम)
अणु
	अगर (ksoftirqd_running(local_softirq_pending()))
		वापस;

	अगर (!क्रमce_irqthपढ़ोs || !__this_cpu_पढ़ो(ksoftirqd)) अणु
#अगर_घोषित CONFIG_HAVE_IRQ_EXIT_ON_IRQ_STACK
		/*
		 * We can safely execute softirq on the current stack अगर
		 * it is the irq stack, because it should be near empty
		 * at this stage.
		 */
		__करो_softirq();
#अन्यथा
		/*
		 * Otherwise, irq_निकास() is called on the task stack that can
		 * be potentially deep alपढ़ोy. So call softirq in its own stack
		 * to prevent from any overrun.
		 */
		करो_softirq_own_stack();
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		wakeup_softirqd();
	पूर्ण
पूर्ण

यंत्रlinkage __visible व्योम करो_softirq(व्योम)
अणु
	__u32 pending;
	अचिन्हित दीर्घ flags;

	अगर (in_पूर्णांकerrupt())
		वापस;

	local_irq_save(flags);

	pending = local_softirq_pending();

	अगर (pending && !ksoftirqd_running(pending))
		करो_softirq_own_stack();

	local_irq_restore(flags);
पूर्ण

#पूर्ण_अगर /* !CONFIG_PREEMPT_RT */

/*
 * We restart softirq processing क्रम at most MAX_SOFTIRQ_RESTART बार,
 * but अवरोध the loop अगर need_resched() is set or after 2 ms.
 * The MAX_SOFTIRQ_TIME provides a nice upper bound in most हालs, but in
 * certain हालs, such as stop_machine(), jअगरfies may cease to
 * increment and so we need the MAX_SOFTIRQ_RESTART limit as
 * well to make sure we eventually वापस from this method.
 *
 * These limits have been established via experimentation.
 * The two things to balance is latency against fairness -
 * we want to handle softirqs as soon as possible, but they
 * should not be able to lock up the box.
 */
#घोषणा MAX_SOFTIRQ_TIME  msecs_to_jअगरfies(2)
#घोषणा MAX_SOFTIRQ_RESTART 10

#अगर_घोषित CONFIG_TRACE_IRQFLAGS
/*
 * When we run softirqs from irq_निकास() and thus on the hardirq stack we need
 * to keep the lockdep irq context tracking as tight as possible in order to
 * not miss-qualअगरy lock contexts and miss possible deadlocks.
 */

अटल अंतरभूत bool lockdep_softirq_start(व्योम)
अणु
	bool in_hardirq = false;

	अगर (lockdep_hardirq_context()) अणु
		in_hardirq = true;
		lockdep_hardirq_निकास();
	पूर्ण

	lockdep_softirq_enter();

	वापस in_hardirq;
पूर्ण

अटल अंतरभूत व्योम lockdep_softirq_end(bool in_hardirq)
अणु
	lockdep_softirq_निकास();

	अगर (in_hardirq)
		lockdep_hardirq_enter();
पूर्ण
#अन्यथा
अटल अंतरभूत bool lockdep_softirq_start(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम lockdep_softirq_end(bool in_hardirq) अणु पूर्ण
#पूर्ण_अगर

यंत्रlinkage __visible व्योम __softirq_entry __करो_softirq(व्योम)
अणु
	अचिन्हित दीर्घ end = jअगरfies + MAX_SOFTIRQ_TIME;
	अचिन्हित दीर्घ old_flags = current->flags;
	पूर्णांक max_restart = MAX_SOFTIRQ_RESTART;
	काष्ठा softirq_action *h;
	bool in_hardirq;
	__u32 pending;
	पूर्णांक softirq_bit;

	/*
	 * Mask out PF_MEMALLOC as the current task context is borrowed क्रम the
	 * softirq. A softirq handled, such as network RX, might set PF_MEMALLOC
	 * again अगर the socket is related to swapping.
	 */
	current->flags &= ~PF_MEMALLOC;

	pending = local_softirq_pending();

	softirq_handle_begin();
	in_hardirq = lockdep_softirq_start();
	account_softirq_enter(current);

restart:
	/* Reset the pending biपंचांगask beक्रमe enabling irqs */
	set_softirq_pending(0);

	local_irq_enable();

	h = softirq_vec;

	जबतक ((softirq_bit = ffs(pending))) अणु
		अचिन्हित पूर्णांक vec_nr;
		पूर्णांक prev_count;

		h += softirq_bit - 1;

		vec_nr = h - softirq_vec;
		prev_count = preempt_count();

		kstat_incr_softirqs_this_cpu(vec_nr);

		trace_softirq_entry(vec_nr);
		h->action(h);
		trace_softirq_निकास(vec_nr);
		अगर (unlikely(prev_count != preempt_count())) अणु
			pr_err("huh, entered softirq %u %s %p with preempt_count %08x, exited with %08x?\n",
			       vec_nr, softirq_to_name[vec_nr], h->action,
			       prev_count, preempt_count());
			preempt_count_set(prev_count);
		पूर्ण
		h++;
		pending >>= softirq_bit;
	पूर्ण

	अगर (!IS_ENABLED(CONFIG_PREEMPT_RT) &&
	    __this_cpu_पढ़ो(ksoftirqd) == current)
		rcu_softirq_qs();

	local_irq_disable();

	pending = local_softirq_pending();
	अगर (pending) अणु
		अगर (समय_beक्रमe(jअगरfies, end) && !need_resched() &&
		    --max_restart)
			जाओ restart;

		wakeup_softirqd();
	पूर्ण

	account_softirq_निकास(current);
	lockdep_softirq_end(in_hardirq);
	softirq_handle_end();
	current_restore_flags(old_flags, PF_MEMALLOC);
पूर्ण

/**
 * irq_enter_rcu - Enter an पूर्णांकerrupt context with RCU watching
 */
व्योम irq_enter_rcu(व्योम)
अणु
	__irq_enter_raw();

	अगर (is_idle_task(current) && (irq_count() == HARसूचीQ_OFFSET))
		tick_irq_enter();

	account_hardirq_enter(current);
पूर्ण

/**
 * irq_enter - Enter an पूर्णांकerrupt context including RCU update
 */
व्योम irq_enter(व्योम)
अणु
	rcu_irq_enter();
	irq_enter_rcu();
पूर्ण

अटल अंतरभूत व्योम tick_irq_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_NO_HZ_COMMON
	पूर्णांक cpu = smp_processor_id();

	/* Make sure that समयr wheel updates are propagated */
	अगर ((idle_cpu(cpu) && !need_resched()) || tick_nohz_full_cpu(cpu)) अणु
		अगर (!in_irq())
			tick_nohz_irq_निकास();
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम __irq_निकास_rcu(व्योम)
अणु
#अगर_अघोषित __ARCH_IRQ_EXIT_IRQS_DISABLED
	local_irq_disable();
#अन्यथा
	lockdep_निश्चित_irqs_disabled();
#पूर्ण_अगर
	account_hardirq_निकास(current);
	preempt_count_sub(HARसूचीQ_OFFSET);
	अगर (!in_पूर्णांकerrupt() && local_softirq_pending())
		invoke_softirq();

	tick_irq_निकास();
पूर्ण

/**
 * irq_निकास_rcu() - Exit an पूर्णांकerrupt context without updating RCU
 *
 * Also processes softirqs अगर needed and possible.
 */
व्योम irq_निकास_rcu(व्योम)
अणु
	__irq_निकास_rcu();
	 /* must be last! */
	lockdep_hardirq_निकास();
पूर्ण

/**
 * irq_निकास - Exit an पूर्णांकerrupt context, update RCU and lockdep
 *
 * Also processes softirqs अगर needed and possible.
 */
व्योम irq_निकास(व्योम)
अणु
	__irq_निकास_rcu();
	rcu_irq_निकास();
	 /* must be last! */
	lockdep_hardirq_निकास();
पूर्ण

/*
 * This function must run with irqs disabled!
 */
अंतरभूत व्योम उठाओ_softirq_irqoff(अचिन्हित पूर्णांक nr)
अणु
	__उठाओ_softirq_irqoff(nr);

	/*
	 * If we're in an interrupt or softirq, we're करोne
	 * (this also catches softirq-disabled code). We will
	 * actually run the softirq once we वापस from
	 * the irq or softirq.
	 *
	 * Otherwise we wake up ksoftirqd to make sure we
	 * schedule the softirq soon.
	 */
	अगर (!in_पूर्णांकerrupt() && should_wake_ksoftirqd())
		wakeup_softirqd();
पूर्ण

व्योम उठाओ_softirq(अचिन्हित पूर्णांक nr)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	उठाओ_softirq_irqoff(nr);
	local_irq_restore(flags);
पूर्ण

व्योम __उठाओ_softirq_irqoff(अचिन्हित पूर्णांक nr)
अणु
	lockdep_निश्चित_irqs_disabled();
	trace_softirq_उठाओ(nr);
	or_softirq_pending(1UL << nr);
पूर्ण

व्योम खोलो_softirq(पूर्णांक nr, व्योम (*action)(काष्ठा softirq_action *))
अणु
	softirq_vec[nr].action = action;
पूर्ण

/*
 * Tasklets
 */
काष्ठा tasklet_head अणु
	काष्ठा tasklet_काष्ठा *head;
	काष्ठा tasklet_काष्ठा **tail;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा tasklet_head, tasklet_vec);
अटल DEFINE_PER_CPU(काष्ठा tasklet_head, tasklet_hi_vec);

अटल व्योम __tasklet_schedule_common(काष्ठा tasklet_काष्ठा *t,
				      काष्ठा tasklet_head __percpu *headp,
				      अचिन्हित पूर्णांक softirq_nr)
अणु
	काष्ठा tasklet_head *head;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	head = this_cpu_ptr(headp);
	t->next = शून्य;
	*head->tail = t;
	head->tail = &(t->next);
	उठाओ_softirq_irqoff(softirq_nr);
	local_irq_restore(flags);
पूर्ण

व्योम __tasklet_schedule(काष्ठा tasklet_काष्ठा *t)
अणु
	__tasklet_schedule_common(t, &tasklet_vec,
				  TASKLET_SOFTIRQ);
पूर्ण
EXPORT_SYMBOL(__tasklet_schedule);

व्योम __tasklet_hi_schedule(काष्ठा tasklet_काष्ठा *t)
अणु
	__tasklet_schedule_common(t, &tasklet_hi_vec,
				  HI_SOFTIRQ);
पूर्ण
EXPORT_SYMBOL(__tasklet_hi_schedule);

अटल bool tasklet_clear_sched(काष्ठा tasklet_काष्ठा *t)
अणु
	अगर (test_and_clear_bit(TASKLET_STATE_SCHED, &t->state)) अणु
		wake_up_var(&t->state);
		वापस true;
	पूर्ण

	WARN_ONCE(1, "tasklet SCHED state not set: %s %pS\n",
		  t->use_callback ? "callback" : "func",
		  t->use_callback ? (व्योम *)t->callback : (व्योम *)t->func);

	वापस false;
पूर्ण

अटल व्योम tasklet_action_common(काष्ठा softirq_action *a,
				  काष्ठा tasklet_head *tl_head,
				  अचिन्हित पूर्णांक softirq_nr)
अणु
	काष्ठा tasklet_काष्ठा *list;

	local_irq_disable();
	list = tl_head->head;
	tl_head->head = शून्य;
	tl_head->tail = &tl_head->head;
	local_irq_enable();

	जबतक (list) अणु
		काष्ठा tasklet_काष्ठा *t = list;

		list = list->next;

		अगर (tasklet_trylock(t)) अणु
			अगर (!atomic_पढ़ो(&t->count)) अणु
				अगर (tasklet_clear_sched(t)) अणु
					अगर (t->use_callback)
						t->callback(t);
					अन्यथा
						t->func(t->data);
				पूर्ण
				tasklet_unlock(t);
				जारी;
			पूर्ण
			tasklet_unlock(t);
		पूर्ण

		local_irq_disable();
		t->next = शून्य;
		*tl_head->tail = t;
		tl_head->tail = &t->next;
		__उठाओ_softirq_irqoff(softirq_nr);
		local_irq_enable();
	पूर्ण
पूर्ण

अटल __latent_entropy व्योम tasklet_action(काष्ठा softirq_action *a)
अणु
	tasklet_action_common(a, this_cpu_ptr(&tasklet_vec), TASKLET_SOFTIRQ);
पूर्ण

अटल __latent_entropy व्योम tasklet_hi_action(काष्ठा softirq_action *a)
अणु
	tasklet_action_common(a, this_cpu_ptr(&tasklet_hi_vec), HI_SOFTIRQ);
पूर्ण

व्योम tasklet_setup(काष्ठा tasklet_काष्ठा *t,
		   व्योम (*callback)(काष्ठा tasklet_काष्ठा *))
अणु
	t->next = शून्य;
	t->state = 0;
	atomic_set(&t->count, 0);
	t->callback = callback;
	t->use_callback = true;
	t->data = 0;
पूर्ण
EXPORT_SYMBOL(tasklet_setup);

व्योम tasklet_init(काष्ठा tasklet_काष्ठा *t,
		  व्योम (*func)(अचिन्हित दीर्घ), अचिन्हित दीर्घ data)
अणु
	t->next = शून्य;
	t->state = 0;
	atomic_set(&t->count, 0);
	t->func = func;
	t->use_callback = false;
	t->data = data;
पूर्ण
EXPORT_SYMBOL(tasklet_init);

#अगर defined(CONFIG_SMP) || defined(CONFIG_PREEMPT_RT)
/*
 * Do not use in new code. Waiting क्रम tasklets from atomic contexts is
 * error prone and should be aव्योमed.
 */
व्योम tasklet_unlock_spin_रुको(काष्ठा tasklet_काष्ठा *t)
अणु
	जबतक (test_bit(TASKLET_STATE_RUN, &(t)->state)) अणु
		अगर (IS_ENABLED(CONFIG_PREEMPT_RT)) अणु
			/*
			 * Prevent a live lock when current preempted soft
			 * पूर्णांकerrupt processing or prevents ksoftirqd from
			 * running. If the tasklet runs on a dअगरferent CPU
			 * then this has no effect other than करोing the BH
			 * disable/enable dance क्रम nothing.
			 */
			local_bh_disable();
			local_bh_enable();
		पूर्ण अन्यथा अणु
			cpu_relax();
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(tasklet_unlock_spin_रुको);
#पूर्ण_अगर

व्योम tasklet_समाप्त(काष्ठा tasklet_काष्ठा *t)
अणु
	अगर (in_पूर्णांकerrupt())
		pr_notice("Attempt to kill tasklet from interrupt\n");

	जबतक (test_and_set_bit(TASKLET_STATE_SCHED, &t->state))
		रुको_var_event(&t->state, !test_bit(TASKLET_STATE_SCHED, &t->state));

	tasklet_unlock_रुको(t);
	tasklet_clear_sched(t);
पूर्ण
EXPORT_SYMBOL(tasklet_समाप्त);

#अगर defined(CONFIG_SMP) || defined(CONFIG_PREEMPT_RT)
व्योम tasklet_unlock(काष्ठा tasklet_काष्ठा *t)
अणु
	smp_mb__beक्रमe_atomic();
	clear_bit(TASKLET_STATE_RUN, &t->state);
	smp_mb__after_atomic();
	wake_up_var(&t->state);
पूर्ण
EXPORT_SYMBOL_GPL(tasklet_unlock);

व्योम tasklet_unlock_रुको(काष्ठा tasklet_काष्ठा *t)
अणु
	रुको_var_event(&t->state, !test_bit(TASKLET_STATE_RUN, &t->state));
पूर्ण
EXPORT_SYMBOL_GPL(tasklet_unlock_रुको);
#पूर्ण_अगर

व्योम __init softirq_init(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		per_cpu(tasklet_vec, cpu).tail =
			&per_cpu(tasklet_vec, cpu).head;
		per_cpu(tasklet_hi_vec, cpu).tail =
			&per_cpu(tasklet_hi_vec, cpu).head;
	पूर्ण

	खोलो_softirq(TASKLET_SOFTIRQ, tasklet_action);
	खोलो_softirq(HI_SOFTIRQ, tasklet_hi_action);
पूर्ण

अटल पूर्णांक ksoftirqd_should_run(अचिन्हित पूर्णांक cpu)
अणु
	वापस local_softirq_pending();
पूर्ण

अटल व्योम run_ksoftirqd(अचिन्हित पूर्णांक cpu)
अणु
	ksoftirqd_run_begin();
	अगर (local_softirq_pending()) अणु
		/*
		 * We can safely run softirq on अंतरभूत stack, as we are not deep
		 * in the task stack here.
		 */
		__करो_softirq();
		ksoftirqd_run_end();
		cond_resched();
		वापस;
	पूर्ण
	ksoftirqd_run_end();
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल पूर्णांक takeover_tasklets(अचिन्हित पूर्णांक cpu)
अणु
	/* CPU is dead, so no lock needed. */
	local_irq_disable();

	/* Find end, append list क्रम that CPU. */
	अगर (&per_cpu(tasklet_vec, cpu).head != per_cpu(tasklet_vec, cpu).tail) अणु
		*__this_cpu_पढ़ो(tasklet_vec.tail) = per_cpu(tasklet_vec, cpu).head;
		__this_cpu_ग_लिखो(tasklet_vec.tail, per_cpu(tasklet_vec, cpu).tail);
		per_cpu(tasklet_vec, cpu).head = शून्य;
		per_cpu(tasklet_vec, cpu).tail = &per_cpu(tasklet_vec, cpu).head;
	पूर्ण
	उठाओ_softirq_irqoff(TASKLET_SOFTIRQ);

	अगर (&per_cpu(tasklet_hi_vec, cpu).head != per_cpu(tasklet_hi_vec, cpu).tail) अणु
		*__this_cpu_पढ़ो(tasklet_hi_vec.tail) = per_cpu(tasklet_hi_vec, cpu).head;
		__this_cpu_ग_लिखो(tasklet_hi_vec.tail, per_cpu(tasklet_hi_vec, cpu).tail);
		per_cpu(tasklet_hi_vec, cpu).head = शून्य;
		per_cpu(tasklet_hi_vec, cpu).tail = &per_cpu(tasklet_hi_vec, cpu).head;
	पूर्ण
	उठाओ_softirq_irqoff(HI_SOFTIRQ);

	local_irq_enable();
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा takeover_tasklets	शून्य
#पूर्ण_अगर /* CONFIG_HOTPLUG_CPU */

अटल काष्ठा smp_hotplug_thपढ़ो softirq_thपढ़ोs = अणु
	.store			= &ksoftirqd,
	.thपढ़ो_should_run	= ksoftirqd_should_run,
	.thपढ़ो_fn		= run_ksoftirqd,
	.thपढ़ो_comm		= "ksoftirqd/%u",
पूर्ण;

अटल __init पूर्णांक spawn_ksoftirqd(व्योम)
अणु
	cpuhp_setup_state_nocalls(CPUHP_SOFTIRQ_DEAD, "softirq:dead", शून्य,
				  takeover_tasklets);
	BUG_ON(smpboot_रेजिस्टर_percpu_thपढ़ो(&softirq_thपढ़ोs));

	वापस 0;
पूर्ण
early_initcall(spawn_ksoftirqd);

/*
 * [ These __weak aliases are kept in a separate compilation unit, so that
 *   GCC करोes not अंतरभूत them incorrectly. ]
 */

पूर्णांक __init __weak early_irq_init(व्योम)
अणु
	वापस 0;
पूर्ण

पूर्णांक __init __weak arch_probe_nr_irqs(व्योम)
अणु
	वापस NR_IRQS_LEGACY;
पूर्ण

पूर्णांक __init __weak arch_early_irq_init(व्योम)
अणु
	वापस 0;
पूर्ण

अचिन्हित पूर्णांक __weak arch_dynirq_lower_bound(अचिन्हित पूर्णांक from)
अणु
	वापस from;
पूर्ण
