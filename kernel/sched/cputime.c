<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Simple CPU accounting cgroup controller
 */
#समावेश "sched.h"

#अगर_घोषित CONFIG_IRQ_TIME_ACCOUNTING

/*
 * There are no locks covering percpu hardirq/softirq समय.
 * They are only modअगरied in vसमय_account, on corresponding CPU
 * with पूर्णांकerrupts disabled. So, ग_लिखोs are safe.
 * They are पढ़ो and saved off onto काष्ठा rq in update_rq_घड़ी().
 * This may result in other CPU पढ़ोing this CPU's irq समय and can
 * race with irq/vसमय_account on this CPU. We would either get old
 * or new value with a side effect of accounting a slice of irq समय to wrong
 * task when irq is in progress जबतक we पढ़ो rq->घड़ी. That is a worthy
 * compromise in place of having locks on each irq in account_प्रणाली_समय.
 */
DEFINE_PER_CPU(काष्ठा irqसमय, cpu_irqसमय);

अटल पूर्णांक sched_घड़ी_irqसमय;

व्योम enable_sched_घड़ी_irqसमय(व्योम)
अणु
	sched_घड़ी_irqसमय = 1;
पूर्ण

व्योम disable_sched_घड़ी_irqसमय(व्योम)
अणु
	sched_घड़ी_irqसमय = 0;
पूर्ण

अटल व्योम irqसमय_account_delta(काष्ठा irqसमय *irqसमय, u64 delta,
				  क्रमागत cpu_usage_stat idx)
अणु
	u64 *cpustat = kcpustat_this_cpu->cpustat;

	u64_stats_update_begin(&irqसमय->sync);
	cpustat[idx] += delta;
	irqसमय->total += delta;
	irqसमय->tick_delta += delta;
	u64_stats_update_end(&irqसमय->sync);
पूर्ण

/*
 * Called after incrementing preempt_count on अणुsoft,पूर्णirq_enter
 * and beक्रमe decrementing preempt_count on अणुsoft,पूर्णirq_निकास.
 */
व्योम irqसमय_account_irq(काष्ठा task_काष्ठा *curr, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा irqसमय *irqसमय = this_cpu_ptr(&cpu_irqसमय);
	अचिन्हित पूर्णांक pc;
	s64 delta;
	पूर्णांक cpu;

	अगर (!sched_घड़ी_irqसमय)
		वापस;

	cpu = smp_processor_id();
	delta = sched_घड़ी_cpu(cpu) - irqसमय->irq_start_समय;
	irqसमय->irq_start_समय += delta;
	pc = irq_count() - offset;

	/*
	 * We करो not account क्रम softirq समय from ksoftirqd here.
	 * We want to जारी accounting softirq समय to ksoftirqd thपढ़ो
	 * in that हाल, so as not to confuse scheduler with a special task
	 * that करो not consume any समय, but still wants to run.
	 */
	अगर (pc & HARसूचीQ_MASK)
		irqसमय_account_delta(irqसमय, delta, CPUTIME_IRQ);
	अन्यथा अगर ((pc & SOFTIRQ_OFFSET) && curr != this_cpu_ksoftirqd())
		irqसमय_account_delta(irqसमय, delta, CPUTIME_SOFTIRQ);
पूर्ण

अटल u64 irqसमय_प्रकारick_accounted(u64 maxसमय)
अणु
	काष्ठा irqसमय *irqसमय = this_cpu_ptr(&cpu_irqसमय);
	u64 delta;

	delta = min(irqसमय->tick_delta, maxसमय);
	irqसमय->tick_delta -= delta;

	वापस delta;
पूर्ण

#अन्यथा /* CONFIG_IRQ_TIME_ACCOUNTING */

#घोषणा sched_घड़ी_irqसमय	(0)

अटल u64 irqसमय_प्रकारick_accounted(u64 dummy)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* !CONFIG_IRQ_TIME_ACCOUNTING */

अटल अंतरभूत व्योम task_group_account_field(काष्ठा task_काष्ठा *p, पूर्णांक index,
					    u64 पंचांगp)
अणु
	/*
	 * Since all updates are sure to touch the root cgroup, we
	 * get ourselves ahead and touch it first. If the root cgroup
	 * is the only cgroup, then nothing अन्यथा should be necessary.
	 *
	 */
	__this_cpu_add(kernel_cpustat.cpustat[index], पंचांगp);

	cgroup_account_cpuसमय_field(p, index, पंचांगp);
पूर्ण

/*
 * Account user CPU समय to a process.
 * @p: the process that the CPU समय माला_लो accounted to
 * @cpuसमय: the CPU समय spent in user space since the last update
 */
व्योम account_user_समय(काष्ठा task_काष्ठा *p, u64 cpuसमय)
अणु
	पूर्णांक index;

	/* Add user समय to process. */
	p->uसमय += cpuसमय;
	account_group_user_समय(p, cpuसमय);

	index = (task_nice(p) > 0) ? CPUTIME_NICE : CPUTIME_USER;

	/* Add user समय to cpustat. */
	task_group_account_field(p, index, cpuसमय);

	/* Account क्रम user समय used */
	acct_account_cpuसमय(p);
पूर्ण

/*
 * Account guest CPU समय to a process.
 * @p: the process that the CPU समय माला_लो accounted to
 * @cpuसमय: the CPU समय spent in भव machine since the last update
 */
व्योम account_guest_समय(काष्ठा task_काष्ठा *p, u64 cpuसमय)
अणु
	u64 *cpustat = kcpustat_this_cpu->cpustat;

	/* Add guest समय to process. */
	p->uसमय += cpuसमय;
	account_group_user_समय(p, cpuसमय);
	p->gसमय += cpuसमय;

	/* Add guest समय to cpustat. */
	अगर (task_nice(p) > 0) अणु
		cpustat[CPUTIME_NICE] += cpuसमय;
		cpustat[CPUTIME_GUEST_NICE] += cpuसमय;
	पूर्ण अन्यथा अणु
		cpustat[CPUTIME_USER] += cpuसमय;
		cpustat[CPUTIME_GUEST] += cpuसमय;
	पूर्ण
पूर्ण

/*
 * Account प्रणाली CPU समय to a process and desired cpustat field
 * @p: the process that the CPU समय माला_लो accounted to
 * @cpuसमय: the CPU समय spent in kernel space since the last update
 * @index: poपूर्णांकer to cpustat field that has to be updated
 */
व्योम account_प्रणाली_index_समय(काष्ठा task_काष्ठा *p,
			       u64 cpuसमय, क्रमागत cpu_usage_stat index)
अणु
	/* Add प्रणाली समय to process. */
	p->sसमय += cpuसमय;
	account_group_प्रणाली_समय(p, cpuसमय);

	/* Add प्रणाली समय to cpustat. */
	task_group_account_field(p, index, cpuसमय);

	/* Account क्रम प्रणाली समय used */
	acct_account_cpuसमय(p);
पूर्ण

/*
 * Account प्रणाली CPU समय to a process.
 * @p: the process that the CPU समय माला_लो accounted to
 * @hardirq_offset: the offset to subtract from hardirq_count()
 * @cpuसमय: the CPU समय spent in kernel space since the last update
 */
व्योम account_प्रणाली_समय(काष्ठा task_काष्ठा *p, पूर्णांक hardirq_offset, u64 cpuसमय)
अणु
	पूर्णांक index;

	अगर ((p->flags & PF_VCPU) && (irq_count() - hardirq_offset == 0)) अणु
		account_guest_समय(p, cpuसमय);
		वापस;
	पूर्ण

	अगर (hardirq_count() - hardirq_offset)
		index = CPUTIME_IRQ;
	अन्यथा अगर (in_serving_softirq())
		index = CPUTIME_SOFTIRQ;
	अन्यथा
		index = CPUTIME_SYSTEM;

	account_प्रणाली_index_समय(p, cpuसमय, index);
पूर्ण

/*
 * Account क्रम involuntary रुको समय.
 * @cpuसमय: the CPU समय spent in involuntary रुको
 */
व्योम account_steal_समय(u64 cpuसमय)
अणु
	u64 *cpustat = kcpustat_this_cpu->cpustat;

	cpustat[CPUTIME_STEAL] += cpuसमय;
पूर्ण

/*
 * Account क्रम idle समय.
 * @cpuसमय: the CPU समय spent in idle रुको
 */
व्योम account_idle_समय(u64 cpuसमय)
अणु
	u64 *cpustat = kcpustat_this_cpu->cpustat;
	काष्ठा rq *rq = this_rq();

	अगर (atomic_पढ़ो(&rq->nr_ioरुको) > 0)
		cpustat[CPUTIME_IOWAIT] += cpuसमय;
	अन्यथा
		cpustat[CPUTIME_IDLE] += cpuसमय;
पूर्ण

/*
 * When a guest is पूर्णांकerrupted क्रम a दीर्घer amount of समय, missed घड़ी
 * ticks are not redelivered later. Due to that, this function may on
 * occasion account more समय than the calling functions think elapsed.
 */
अटल __always_अंतरभूत u64 steal_account_process_समय(u64 maxसमय)
अणु
#अगर_घोषित CONFIG_PARAVIRT
	अगर (अटल_key_false(&paravirt_steal_enabled)) अणु
		u64 steal;

		steal = paravirt_steal_घड़ी(smp_processor_id());
		steal -= this_rq()->prev_steal_समय;
		steal = min(steal, maxसमय);
		account_steal_समय(steal);
		this_rq()->prev_steal_समय += steal;

		वापस steal;
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

/*
 * Account how much elapsed समय was spent in steal, irq, or softirq समय.
 */
अटल अंतरभूत u64 account_other_समय(u64 max)
अणु
	u64 accounted;

	lockdep_निश्चित_irqs_disabled();

	accounted = steal_account_process_समय(max);

	अगर (accounted < max)
		accounted += irqसमय_प्रकारick_accounted(max - accounted);

	वापस accounted;
पूर्ण

#अगर_घोषित CONFIG_64BIT
अटल अंतरभूत u64 पढ़ो_sum_exec_runसमय(काष्ठा task_काष्ठा *t)
अणु
	वापस t->se.sum_exec_runसमय;
पूर्ण
#अन्यथा
अटल u64 पढ़ो_sum_exec_runसमय(काष्ठा task_काष्ठा *t)
अणु
	u64 ns;
	काष्ठा rq_flags rf;
	काष्ठा rq *rq;

	rq = task_rq_lock(t, &rf);
	ns = t->se.sum_exec_runसमय;
	task_rq_unlock(rq, t, &rf);

	वापस ns;
पूर्ण
#पूर्ण_अगर

/*
 * Accumulate raw cpuसमय values of dead tasks (sig->[us]समय) and live
 * tasks (sum on group iteration) beदीर्घing to @tsk's group.
 */
व्योम thपढ़ो_group_cpuसमय(काष्ठा task_काष्ठा *tsk, काष्ठा task_cpuसमय *बार)
अणु
	काष्ठा संकेत_काष्ठा *sig = tsk->संकेत;
	u64 uसमय, sसमय;
	काष्ठा task_काष्ठा *t;
	अचिन्हित पूर्णांक seq, nextseq;
	अचिन्हित दीर्घ flags;

	/*
	 * Update current task runसमय to account pending समय since last
	 * scheduler action or thपढ़ो_group_cpuसमय() call. This thपढ़ो group
	 * might have other running tasks on dअगरferent CPUs, but updating
	 * their runसमय can affect syscall perक्रमmance, so we skip account
	 * those pending बार and rely only on values updated on tick or
	 * other scheduler action.
	 */
	अगर (same_thपढ़ो_group(current, tsk))
		(व्योम) task_sched_runसमय(current);

	rcu_पढ़ो_lock();
	/* Attempt a lockless पढ़ो on the first round. */
	nextseq = 0;
	करो अणु
		seq = nextseq;
		flags = पढ़ो_seqbegin_or_lock_irqsave(&sig->stats_lock, &seq);
		बार->uसमय = sig->uसमय;
		बार->sसमय = sig->sसमय;
		बार->sum_exec_runसमय = sig->sum_sched_runसमय;

		क्रम_each_thपढ़ो(tsk, t) अणु
			task_cpuसमय(t, &uसमय, &sसमय);
			बार->uसमय += uसमय;
			बार->sसमय += sसमय;
			बार->sum_exec_runसमय += पढ़ो_sum_exec_runसमय(t);
		पूर्ण
		/* If lockless access failed, take the lock. */
		nextseq = 1;
	पूर्ण जबतक (need_seqretry(&sig->stats_lock, seq));
	करोne_seqretry_irqrestore(&sig->stats_lock, seq, flags);
	rcu_पढ़ो_unlock();
पूर्ण

#अगर_घोषित CONFIG_IRQ_TIME_ACCOUNTING
/*
 * Account a tick to a process and cpustat
 * @p: the process that the CPU समय माला_लो accounted to
 * @user_tick: is the tick from userspace
 * @rq: the poपूर्णांकer to rq
 *
 * Tick demultiplexing follows the order
 * - pending hardirq update
 * - pending softirq update
 * - user_समय
 * - idle_समय
 * - प्रणाली समय
 *   - check क्रम guest_समय
 *   - अन्यथा account as प्रणाली_समय
 *
 * Check क्रम hardirq is करोne both क्रम प्रणाली and user समय as there is
 * no समयr going off जबतक we are on hardirq and hence we may never get an
 * opportunity to update it solely in प्रणाली समय.
 * p->sसमय and मित्रs are only updated on प्रणाली समय and not on irq
 * softirq as those करो not count in task exec_runसमय any more.
 */
अटल व्योम irqसमय_account_process_tick(काष्ठा task_काष्ठा *p, पूर्णांक user_tick,
					 पूर्णांक ticks)
अणु
	u64 other, cpuसमय = TICK_NSEC * ticks;

	/*
	 * When वापसing from idle, many ticks can get accounted at
	 * once, including some ticks of steal, irq, and softirq समय.
	 * Subtract those ticks from the amount of समय accounted to
	 * idle, or potentially user or प्रणाली समय. Due to rounding,
	 * other समय can exceed ticks occasionally.
	 */
	other = account_other_समय(अच_दीर्घ_उच्च);
	अगर (other >= cpuसमय)
		वापस;

	cpuसमय -= other;

	अगर (this_cpu_ksoftirqd() == p) अणु
		/*
		 * ksoftirqd समय करो not get accounted in cpu_softirq_समय.
		 * So, we have to handle it separately here.
		 * Also, p->sसमय needs to be updated क्रम ksoftirqd.
		 */
		account_प्रणाली_index_समय(p, cpuसमय, CPUTIME_SOFTIRQ);
	पूर्ण अन्यथा अगर (user_tick) अणु
		account_user_समय(p, cpuसमय);
	पूर्ण अन्यथा अगर (p == this_rq()->idle) अणु
		account_idle_समय(cpuसमय);
	पूर्ण अन्यथा अगर (p->flags & PF_VCPU) अणु /* System समय or guest समय */
		account_guest_समय(p, cpuसमय);
	पूर्ण अन्यथा अणु
		account_प्रणाली_index_समय(p, cpuसमय, CPUTIME_SYSTEM);
	पूर्ण
पूर्ण

अटल व्योम irqसमय_account_idle_ticks(पूर्णांक ticks)
अणु
	irqसमय_account_process_tick(current, 0, ticks);
पूर्ण
#अन्यथा /* CONFIG_IRQ_TIME_ACCOUNTING */
अटल अंतरभूत व्योम irqसमय_account_idle_ticks(पूर्णांक ticks) अणु पूर्ण
अटल अंतरभूत व्योम irqसमय_account_process_tick(काष्ठा task_काष्ठा *p, पूर्णांक user_tick,
						पूर्णांक nr_ticks) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_IRQ_TIME_ACCOUNTING */

/*
 * Use precise platक्रमm statistics अगर available:
 */
#अगर_घोषित CONFIG_VIRT_CPU_ACCOUNTING_NATIVE

# अगरndef __ARCH_HAS_VTIME_TASK_SWITCH
व्योम vसमय_प्रकारask_चयन(काष्ठा task_काष्ठा *prev)
अणु
	अगर (is_idle_task(prev))
		vसमय_account_idle(prev);
	अन्यथा
		vसमय_account_kernel(prev);

	vसमय_flush(prev);
	arch_vसमय_प्रकारask_चयन(prev);
पूर्ण
# endअगर

व्योम vसमय_account_irq(काष्ठा task_काष्ठा *tsk, अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित पूर्णांक pc = irq_count() - offset;

	अगर (pc & HARसूचीQ_OFFSET) अणु
		vसमय_account_hardirq(tsk);
	पूर्ण अन्यथा अगर (pc & SOFTIRQ_OFFSET) अणु
		vसमय_account_softirq(tsk);
	पूर्ण अन्यथा अगर (!IS_ENABLED(CONFIG_HAVE_VIRT_CPU_ACCOUNTING_IDLE) &&
		   is_idle_task(tsk)) अणु
		vसमय_account_idle(tsk);
	पूर्ण अन्यथा अणु
		vसमय_account_kernel(tsk);
	पूर्ण
पूर्ण

व्योम cpuसमय_adjust(काष्ठा task_cpuसमय *curr, काष्ठा prev_cpuसमय *prev,
		    u64 *ut, u64 *st)
अणु
	*ut = curr->uसमय;
	*st = curr->sसमय;
पूर्ण

व्योम task_cpuसमय_adjusted(काष्ठा task_काष्ठा *p, u64 *ut, u64 *st)
अणु
	*ut = p->uसमय;
	*st = p->sसमय;
पूर्ण
EXPORT_SYMBOL_GPL(task_cpuसमय_adjusted);

व्योम thपढ़ो_group_cpuसमय_adjusted(काष्ठा task_काष्ठा *p, u64 *ut, u64 *st)
अणु
	काष्ठा task_cpuसमय cpuसमय;

	thपढ़ो_group_cpuसमय(p, &cpuसमय);

	*ut = cpuसमय.uसमय;
	*st = cpuसमय.sसमय;
पूर्ण

#अन्यथा /* !CONFIG_VIRT_CPU_ACCOUNTING_NATIVE: */

/*
 * Account a single tick of CPU समय.
 * @p: the process that the CPU समय माला_लो accounted to
 * @user_tick: indicates अगर the tick is a user or a प्रणाली tick
 */
व्योम account_process_tick(काष्ठा task_काष्ठा *p, पूर्णांक user_tick)
अणु
	u64 cpuसमय, steal;

	अगर (vसमय_accounting_enabled_this_cpu())
		वापस;

	अगर (sched_घड़ी_irqसमय) अणु
		irqसमय_account_process_tick(p, user_tick, 1);
		वापस;
	पूर्ण

	cpuसमय = TICK_NSEC;
	steal = steal_account_process_समय(अच_दीर्घ_उच्च);

	अगर (steal >= cpuसमय)
		वापस;

	cpuसमय -= steal;

	अगर (user_tick)
		account_user_समय(p, cpuसमय);
	अन्यथा अगर ((p != this_rq()->idle) || (irq_count() != HARसूचीQ_OFFSET))
		account_प्रणाली_समय(p, HARसूचीQ_OFFSET, cpuसमय);
	अन्यथा
		account_idle_समय(cpuसमय);
पूर्ण

/*
 * Account multiple ticks of idle समय.
 * @ticks: number of stolen ticks
 */
व्योम account_idle_ticks(अचिन्हित दीर्घ ticks)
अणु
	u64 cpuसमय, steal;

	अगर (sched_घड़ी_irqसमय) अणु
		irqसमय_account_idle_ticks(ticks);
		वापस;
	पूर्ण

	cpuसमय = ticks * TICK_NSEC;
	steal = steal_account_process_समय(अच_दीर्घ_उच्च);

	अगर (steal >= cpuसमय)
		वापस;

	cpuसमय -= steal;
	account_idle_समय(cpuसमय);
पूर्ण

/*
 * Adjust tick based cpuसमय अक्रमom precision against scheduler runसमय
 * accounting.
 *
 * Tick based cpuसमय accounting depend on अक्रमom scheduling बारlices of a
 * task to be पूर्णांकerrupted or not by the समयr.  Depending on these
 * circumstances, the number of these पूर्णांकerrupts may be over or
 * under-optimistic, matching the real user and प्रणाली cpuसमय with a variable
 * precision.
 *
 * Fix this by scaling these tick based values against the total runसमय
 * accounted by the CFS scheduler.
 *
 * This code provides the following guarantees:
 *
 *   sसमय + uसमय == rसमय
 *   sसमय_i+1 >= sसमय_i, uसमय_i+1 >= uसमय_i
 *
 * Assuming that rसमय_i+1 >= rसमय_i.
 */
व्योम cpuसमय_adjust(काष्ठा task_cpuसमय *curr, काष्ठा prev_cpuसमय *prev,
		    u64 *ut, u64 *st)
अणु
	u64 rसमय, sसमय, uसमय;
	अचिन्हित दीर्घ flags;

	/* Serialize concurrent callers such that we can honour our guarantees */
	raw_spin_lock_irqsave(&prev->lock, flags);
	rसमय = curr->sum_exec_runसमय;

	/*
	 * This is possible under two circumstances:
	 *  - rसमय isn't monotonic after all (a bug);
	 *  - we got reordered by the lock.
	 *
	 * In both हालs this acts as a filter such that the rest of the code
	 * can assume it is monotonic regardless of anything अन्यथा.
	 */
	अगर (prev->sसमय + prev->uसमय >= rसमय)
		जाओ out;

	sसमय = curr->sसमय;
	uसमय = curr->uसमय;

	/*
	 * If either sसमय or uसमय are 0, assume all runसमय is userspace.
	 * Once a task माला_लो some ticks, the monotonicity code at 'update:'
	 * will ensure things converge to the observed ratio.
	 */
	अगर (sसमय == 0) अणु
		uसमय = rसमय;
		जाओ update;
	पूर्ण

	अगर (uसमय == 0) अणु
		sसमय = rसमय;
		जाओ update;
	पूर्ण

	sसमय = mul_u64_u64_भाग_u64(sसमय, rसमय, sसमय + uसमय);

update:
	/*
	 * Make sure sसमय करोesn't go backwards; this preserves monotonicity
	 * क्रम uसमय because rसमय is monotonic.
	 *
	 *  uसमय_i+1 = rसमय_i+1 - sसमय_i
	 *            = rसमय_i+1 - (rसमय_i - uसमय_i)
	 *            = (rसमय_i+1 - rसमय_i) + uसमय_i
	 *            >= uसमय_i
	 */
	अगर (sसमय < prev->sसमय)
		sसमय = prev->sसमय;
	uसमय = rसमय - sसमय;

	/*
	 * Make sure uसमय करोesn't go backwards; this still preserves
	 * monotonicity क्रम sसमय, analogous argument to above.
	 */
	अगर (uसमय < prev->uसमय) अणु
		uसमय = prev->uसमय;
		sसमय = rसमय - uसमय;
	पूर्ण

	prev->sसमय = sसमय;
	prev->uसमय = uसमय;
out:
	*ut = prev->uसमय;
	*st = prev->sसमय;
	raw_spin_unlock_irqrestore(&prev->lock, flags);
पूर्ण

व्योम task_cpuसमय_adjusted(काष्ठा task_काष्ठा *p, u64 *ut, u64 *st)
अणु
	काष्ठा task_cpuसमय cpuसमय = अणु
		.sum_exec_runसमय = p->se.sum_exec_runसमय,
	पूर्ण;

	task_cpuसमय(p, &cpuसमय.uसमय, &cpuसमय.sसमय);
	cpuसमय_adjust(&cpuसमय, &p->prev_cpuसमय, ut, st);
पूर्ण
EXPORT_SYMBOL_GPL(task_cpuसमय_adjusted);

व्योम thपढ़ो_group_cpuसमय_adjusted(काष्ठा task_काष्ठा *p, u64 *ut, u64 *st)
अणु
	काष्ठा task_cpuसमय cpuसमय;

	thपढ़ो_group_cpuसमय(p, &cpuसमय);
	cpuसमय_adjust(&cpuसमय, &p->संकेत->prev_cpuसमय, ut, st);
पूर्ण
#पूर्ण_अगर /* !CONFIG_VIRT_CPU_ACCOUNTING_NATIVE */

#अगर_घोषित CONFIG_VIRT_CPU_ACCOUNTING_GEN
अटल u64 vसमय_delta(काष्ठा vसमय *vसमय)
अणु
	अचिन्हित दीर्घ दीर्घ घड़ी;

	घड़ी = sched_घड़ी();
	अगर (घड़ी < vसमय->startसमय)
		वापस 0;

	वापस घड़ी - vसमय->startसमय;
पूर्ण

अटल u64 get_vसमय_delta(काष्ठा vसमय *vसमय)
अणु
	u64 delta = vसमय_delta(vसमय);
	u64 other;

	/*
	 * Unlike tick based timing, vसमय based timing never has lost
	 * ticks, and no need क्रम steal समय accounting to make up क्रम
	 * lost ticks. Vसमय accounts a rounded version of actual
	 * elapsed समय. Limit account_other_समय to prevent rounding
	 * errors from causing elapsed vसमय to go negative.
	 */
	other = account_other_समय(delta);
	WARN_ON_ONCE(vसमय->state == VTIME_INACTIVE);
	vसमय->startसमय += delta;

	वापस delta - other;
पूर्ण

अटल व्योम vसमय_account_प्रणाली(काष्ठा task_काष्ठा *tsk,
				 काष्ठा vसमय *vसमय)
अणु
	vसमय->sसमय += get_vसमय_delta(vसमय);
	अगर (vसमय->sसमय >= TICK_NSEC) अणु
		account_प्रणाली_समय(tsk, irq_count(), vसमय->sसमय);
		vसमय->sसमय = 0;
	पूर्ण
पूर्ण

अटल व्योम vसमय_account_guest(काष्ठा task_काष्ठा *tsk,
				काष्ठा vसमय *vसमय)
अणु
	vसमय->gसमय += get_vसमय_delta(vसमय);
	अगर (vसमय->gसमय >= TICK_NSEC) अणु
		account_guest_समय(tsk, vसमय->gसमय);
		vसमय->gसमय = 0;
	पूर्ण
पूर्ण

अटल व्योम __vसमय_account_kernel(काष्ठा task_काष्ठा *tsk,
				   काष्ठा vसमय *vसमय)
अणु
	/* We might have scheduled out from guest path */
	अगर (vसमय->state == VTIME_GUEST)
		vसमय_account_guest(tsk, vसमय);
	अन्यथा
		vसमय_account_प्रणाली(tsk, vसमय);
पूर्ण

व्योम vसमय_account_kernel(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा vसमय *vसमय = &tsk->vसमय;

	अगर (!vसमय_delta(vसमय))
		वापस;

	ग_लिखो_seqcount_begin(&vसमय->seqcount);
	__vसमय_account_kernel(tsk, vसमय);
	ग_लिखो_seqcount_end(&vसमय->seqcount);
पूर्ण

व्योम vसमय_user_enter(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा vसमय *vसमय = &tsk->vसमय;

	ग_लिखो_seqcount_begin(&vसमय->seqcount);
	vसमय_account_प्रणाली(tsk, vसमय);
	vसमय->state = VTIME_USER;
	ग_लिखो_seqcount_end(&vसमय->seqcount);
पूर्ण

व्योम vसमय_user_निकास(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा vसमय *vसमय = &tsk->vसमय;

	ग_लिखो_seqcount_begin(&vसमय->seqcount);
	vसमय->uसमय += get_vसमय_delta(vसमय);
	अगर (vसमय->uसमय >= TICK_NSEC) अणु
		account_user_समय(tsk, vसमय->uसमय);
		vसमय->uसमय = 0;
	पूर्ण
	vसमय->state = VTIME_SYS;
	ग_लिखो_seqcount_end(&vसमय->seqcount);
पूर्ण

व्योम vसमय_guest_enter(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा vसमय *vसमय = &tsk->vसमय;
	/*
	 * The flags must be updated under the lock with
	 * the vसमय_startसमय flush and update.
	 * That enक्रमces a right ordering and update sequence
	 * synchronization against the पढ़ोer (task_gसमय())
	 * that can thus safely catch up with a tickless delta.
	 */
	ग_लिखो_seqcount_begin(&vसमय->seqcount);
	vसमय_account_प्रणाली(tsk, vसमय);
	tsk->flags |= PF_VCPU;
	vसमय->state = VTIME_GUEST;
	ग_लिखो_seqcount_end(&vसमय->seqcount);
पूर्ण
EXPORT_SYMBOL_GPL(vसमय_guest_enter);

व्योम vसमय_guest_निकास(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा vसमय *vसमय = &tsk->vसमय;

	ग_लिखो_seqcount_begin(&vसमय->seqcount);
	vसमय_account_guest(tsk, vसमय);
	tsk->flags &= ~PF_VCPU;
	vसमय->state = VTIME_SYS;
	ग_लिखो_seqcount_end(&vसमय->seqcount);
पूर्ण
EXPORT_SYMBOL_GPL(vसमय_guest_निकास);

व्योम vसमय_account_idle(काष्ठा task_काष्ठा *tsk)
अणु
	account_idle_समय(get_vसमय_delta(&tsk->vसमय));
पूर्ण

व्योम vसमय_प्रकारask_चयन_generic(काष्ठा task_काष्ठा *prev)
अणु
	काष्ठा vसमय *vसमय = &prev->vसमय;

	ग_लिखो_seqcount_begin(&vसमय->seqcount);
	अगर (vसमय->state == VTIME_IDLE)
		vसमय_account_idle(prev);
	अन्यथा
		__vसमय_account_kernel(prev, vसमय);
	vसमय->state = VTIME_INACTIVE;
	vसमय->cpu = -1;
	ग_लिखो_seqcount_end(&vसमय->seqcount);

	vसमय = &current->vसमय;

	ग_लिखो_seqcount_begin(&vसमय->seqcount);
	अगर (is_idle_task(current))
		vसमय->state = VTIME_IDLE;
	अन्यथा अगर (current->flags & PF_VCPU)
		vसमय->state = VTIME_GUEST;
	अन्यथा
		vसमय->state = VTIME_SYS;
	vसमय->startसमय = sched_घड़ी();
	vसमय->cpu = smp_processor_id();
	ग_लिखो_seqcount_end(&vसमय->seqcount);
पूर्ण

व्योम vसमय_init_idle(काष्ठा task_काष्ठा *t, पूर्णांक cpu)
अणु
	काष्ठा vसमय *vसमय = &t->vसमय;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	ग_लिखो_seqcount_begin(&vसमय->seqcount);
	vसमय->state = VTIME_IDLE;
	vसमय->startसमय = sched_घड़ी();
	vसमय->cpu = cpu;
	ग_लिखो_seqcount_end(&vसमय->seqcount);
	local_irq_restore(flags);
पूर्ण

u64 task_gसमय(काष्ठा task_काष्ठा *t)
अणु
	काष्ठा vसमय *vसमय = &t->vसमय;
	अचिन्हित पूर्णांक seq;
	u64 gसमय;

	अगर (!vसमय_accounting_enabled())
		वापस t->gसमय;

	करो अणु
		seq = पढ़ो_seqcount_begin(&vसमय->seqcount);

		gसमय = t->gसमय;
		अगर (vसमय->state == VTIME_GUEST)
			gसमय += vसमय->gसमय + vसमय_delta(vसमय);

	पूर्ण जबतक (पढ़ो_seqcount_retry(&vसमय->seqcount, seq));

	वापस gसमय;
पूर्ण

/*
 * Fetch cpuसमय raw values from fields of task_काष्ठा and
 * add up the pending nohz execution समय since the last
 * cpuसमय snapshot.
 */
व्योम task_cpuसमय(काष्ठा task_काष्ठा *t, u64 *uसमय, u64 *sसमय)
अणु
	काष्ठा vसमय *vसमय = &t->vसमय;
	अचिन्हित पूर्णांक seq;
	u64 delta;

	अगर (!vसमय_accounting_enabled()) अणु
		*uसमय = t->uसमय;
		*sसमय = t->sसमय;
		वापस;
	पूर्ण

	करो अणु
		seq = पढ़ो_seqcount_begin(&vसमय->seqcount);

		*uसमय = t->uसमय;
		*sसमय = t->sसमय;

		/* Task is sleeping or idle, nothing to add */
		अगर (vसमय->state < VTIME_SYS)
			जारी;

		delta = vसमय_delta(vसमय);

		/*
		 * Task runs either in user (including guest) or kernel space,
		 * add pending nohz समय to the right place.
		 */
		अगर (vसमय->state == VTIME_SYS)
			*sसमय += vसमय->sसमय + delta;
		अन्यथा
			*uसमय += vसमय->uसमय + delta;
	पूर्ण जबतक (पढ़ो_seqcount_retry(&vसमय->seqcount, seq));
पूर्ण

अटल पूर्णांक vसमय_state_fetch(काष्ठा vसमय *vसमय, पूर्णांक cpu)
अणु
	पूर्णांक state = READ_ONCE(vसमय->state);

	/*
	 * We raced against a context चयन, fetch the
	 * kcpustat task again.
	 */
	अगर (vसमय->cpu != cpu && vसमय->cpu != -1)
		वापस -EAGAIN;

	/*
	 * Two possible things here:
	 * 1) We are seeing the scheduling out task (prev) or any past one.
	 * 2) We are seeing the scheduling in task (next) but it hasn't
	 *    passed though vसमय_प्रकारask_चयन() yet so the pending
	 *    cpuसमय of the prev task may not be flushed yet.
	 *
	 * Case 1) is ok but 2) is not. So रुको क्रम a safe VTIME state.
	 */
	अगर (state == VTIME_INACTIVE)
		वापस -EAGAIN;

	वापस state;
पूर्ण

अटल u64 kcpustat_user_vसमय(काष्ठा vसमय *vसमय)
अणु
	अगर (vसमय->state == VTIME_USER)
		वापस vसमय->uसमय + vसमय_delta(vसमय);
	अन्यथा अगर (vसमय->state == VTIME_GUEST)
		वापस vसमय->gसमय + vसमय_delta(vसमय);
	वापस 0;
पूर्ण

अटल पूर्णांक kcpustat_field_vसमय(u64 *cpustat,
				काष्ठा task_काष्ठा *tsk,
				क्रमागत cpu_usage_stat usage,
				पूर्णांक cpu, u64 *val)
अणु
	काष्ठा vसमय *vसमय = &tsk->vसमय;
	अचिन्हित पूर्णांक seq;

	करो अणु
		पूर्णांक state;

		seq = पढ़ो_seqcount_begin(&vसमय->seqcount);

		state = vसमय_state_fetch(vसमय, cpu);
		अगर (state < 0)
			वापस state;

		*val = cpustat[usage];

		/*
		 * Nice VS unnice cpuसमय accounting may be inaccurate अगर
		 * the nice value has changed since the last vसमय update.
		 * But proper fix would involve पूर्णांकerrupting target on nice
		 * updates which is a no go on nohz_full (although the scheduler
		 * may still पूर्णांकerrupt the target अगर rescheduling is needed...)
		 */
		चयन (usage) अणु
		हाल CPUTIME_SYSTEM:
			अगर (state == VTIME_SYS)
				*val += vसमय->sसमय + vसमय_delta(vसमय);
			अवरोध;
		हाल CPUTIME_USER:
			अगर (task_nice(tsk) <= 0)
				*val += kcpustat_user_vसमय(vसमय);
			अवरोध;
		हाल CPUTIME_NICE:
			अगर (task_nice(tsk) > 0)
				*val += kcpustat_user_vसमय(vसमय);
			अवरोध;
		हाल CPUTIME_GUEST:
			अगर (state == VTIME_GUEST && task_nice(tsk) <= 0)
				*val += vसमय->gसमय + vसमय_delta(vसमय);
			अवरोध;
		हाल CPUTIME_GUEST_NICE:
			अगर (state == VTIME_GUEST && task_nice(tsk) > 0)
				*val += vसमय->gसमय + vसमय_delta(vसमय);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण जबतक (पढ़ो_seqcount_retry(&vसमय->seqcount, seq));

	वापस 0;
पूर्ण

u64 kcpustat_field(काष्ठा kernel_cpustat *kcpustat,
		   क्रमागत cpu_usage_stat usage, पूर्णांक cpu)
अणु
	u64 *cpustat = kcpustat->cpustat;
	u64 val = cpustat[usage];
	काष्ठा rq *rq;
	पूर्णांक err;

	अगर (!vसमय_accounting_enabled_cpu(cpu))
		वापस val;

	rq = cpu_rq(cpu);

	क्रम (;;) अणु
		काष्ठा task_काष्ठा *curr;

		rcu_पढ़ो_lock();
		curr = rcu_dereference(rq->curr);
		अगर (WARN_ON_ONCE(!curr)) अणु
			rcu_पढ़ो_unlock();
			वापस cpustat[usage];
		पूर्ण

		err = kcpustat_field_vसमय(cpustat, curr, usage, cpu, &val);
		rcu_पढ़ो_unlock();

		अगर (!err)
			वापस val;

		cpu_relax();
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(kcpustat_field);

अटल पूर्णांक kcpustat_cpu_fetch_vसमय(काष्ठा kernel_cpustat *dst,
				    स्थिर काष्ठा kernel_cpustat *src,
				    काष्ठा task_काष्ठा *tsk, पूर्णांक cpu)
अणु
	काष्ठा vसमय *vसमय = &tsk->vसमय;
	अचिन्हित पूर्णांक seq;

	करो अणु
		u64 *cpustat;
		u64 delta;
		पूर्णांक state;

		seq = पढ़ो_seqcount_begin(&vसमय->seqcount);

		state = vसमय_state_fetch(vसमय, cpu);
		अगर (state < 0)
			वापस state;

		*dst = *src;
		cpustat = dst->cpustat;

		/* Task is sleeping, dead or idle, nothing to add */
		अगर (state < VTIME_SYS)
			जारी;

		delta = vसमय_delta(vसमय);

		/*
		 * Task runs either in user (including guest) or kernel space,
		 * add pending nohz समय to the right place.
		 */
		अगर (state == VTIME_SYS) अणु
			cpustat[CPUTIME_SYSTEM] += vसमय->sसमय + delta;
		पूर्ण अन्यथा अगर (state == VTIME_USER) अणु
			अगर (task_nice(tsk) > 0)
				cpustat[CPUTIME_NICE] += vसमय->uसमय + delta;
			अन्यथा
				cpustat[CPUTIME_USER] += vसमय->uसमय + delta;
		पूर्ण अन्यथा अणु
			WARN_ON_ONCE(state != VTIME_GUEST);
			अगर (task_nice(tsk) > 0) अणु
				cpustat[CPUTIME_GUEST_NICE] += vसमय->gसमय + delta;
				cpustat[CPUTIME_NICE] += vसमय->gसमय + delta;
			पूर्ण अन्यथा अणु
				cpustat[CPUTIME_GUEST] += vसमय->gसमय + delta;
				cpustat[CPUTIME_USER] += vसमय->gसमय + delta;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (पढ़ो_seqcount_retry(&vसमय->seqcount, seq));

	वापस 0;
पूर्ण

व्योम kcpustat_cpu_fetch(काष्ठा kernel_cpustat *dst, पूर्णांक cpu)
अणु
	स्थिर काष्ठा kernel_cpustat *src = &kcpustat_cpu(cpu);
	काष्ठा rq *rq;
	पूर्णांक err;

	अगर (!vसमय_accounting_enabled_cpu(cpu)) अणु
		*dst = *src;
		वापस;
	पूर्ण

	rq = cpu_rq(cpu);

	क्रम (;;) अणु
		काष्ठा task_काष्ठा *curr;

		rcu_पढ़ो_lock();
		curr = rcu_dereference(rq->curr);
		अगर (WARN_ON_ONCE(!curr)) अणु
			rcu_पढ़ो_unlock();
			*dst = *src;
			वापस;
		पूर्ण

		err = kcpustat_cpu_fetch_vसमय(dst, src, curr, cpu);
		rcu_पढ़ो_unlock();

		अगर (!err)
			वापस;

		cpu_relax();
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(kcpustat_cpu_fetch);

#पूर्ण_अगर /* CONFIG_VIRT_CPU_ACCOUNTING_GEN */
