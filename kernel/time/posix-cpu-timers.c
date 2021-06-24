<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Implement CPU समय घड़ीs क्रम the POSIX घड़ी पूर्णांकerface.
 */

#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/cpuसमय.स>
#समावेश <linux/posix-समयrs.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/math64.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <trace/events/समयr.h>
#समावेश <linux/tick.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/compat.h>
#समावेश <linux/sched/deadline.h>

#समावेश "posix-timers.h"

अटल व्योम posix_cpu_समयr_rearm(काष्ठा k_iसमयr *समयr);

व्योम posix_cpuसमयrs_group_init(काष्ठा posix_cpuसमयrs *pct, u64 cpu_limit)
अणु
	posix_cpuसमयrs_init(pct);
	अगर (cpu_limit != RLIM_अनन्त) अणु
		pct->bases[CPUCLOCK_PROF].nextevt = cpu_limit * NSEC_PER_SEC;
		pct->समयrs_active = true;
	पूर्ण
पूर्ण

/*
 * Called after updating RLIMIT_CPU to run cpu समयr and update
 * tsk->संकेत->posix_cpuसमयrs.bases[घड़ी].nextevt expiration cache अगर
 * necessary. Needs siglock protection since other code may update the
 * expiration cache as well.
 */
व्योम update_rlimit_cpu(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ rlim_new)
अणु
	u64 nsecs = rlim_new * NSEC_PER_SEC;

	spin_lock_irq(&task->sighand->siglock);
	set_process_cpu_समयr(task, CPUCLOCK_PROF, &nsecs, शून्य);
	spin_unlock_irq(&task->sighand->siglock);
पूर्ण

/*
 * Functions क्रम validating access to tasks.
 */
अटल काष्ठा pid *pid_क्रम_घड़ी(स्थिर घड़ीid_t घड़ी, bool समय_लो)
अणु
	स्थिर bool thपढ़ो = !!CPUCLOCK_PERTHREAD(घड़ी);
	स्थिर pid_t upid = CPUCLOCK_PID(घड़ी);
	काष्ठा pid *pid;

	अगर (CPUCLOCK_WHICH(घड़ी) >= CPUCLOCK_MAX)
		वापस शून्य;

	/*
	 * If the encoded PID is 0, then the समयr is targeted at current
	 * or the process to which current beदीर्घs.
	 */
	अगर (upid == 0)
		वापस thपढ़ो ? task_pid(current) : task_tgid(current);

	pid = find_vpid(upid);
	अगर (!pid)
		वापस शून्य;

	अगर (thपढ़ो) अणु
		काष्ठा task_काष्ठा *tsk = pid_task(pid, PIDTYPE_PID);
		वापस (tsk && same_thपढ़ो_group(tsk, current)) ? pid : शून्य;
	पूर्ण

	/*
	 * For घड़ी_समय_लो(PROCESS) allow finding the process by
	 * with the pid of the current task.  The code needs the tgid
	 * of the process so that pid_task(pid, PIDTYPE_TGID) can be
	 * used to find the process.
	 */
	अगर (समय_लो && (pid == task_pid(current)))
		वापस task_tgid(current);

	/*
	 * For processes require that pid identअगरies a process.
	 */
	वापस pid_has_task(pid, PIDTYPE_TGID) ? pid : शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक validate_घड़ी_permissions(स्थिर घड़ीid_t घड़ी)
अणु
	पूर्णांक ret;

	rcu_पढ़ो_lock();
	ret = pid_क्रम_घड़ी(घड़ी, false) ? 0 : -EINVAL;
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

अटल अंतरभूत क्रमागत pid_type घड़ी_pid_type(स्थिर घड़ीid_t घड़ी)
अणु
	वापस CPUCLOCK_PERTHREAD(घड़ी) ? PIDTYPE_PID : PIDTYPE_TGID;
पूर्ण

अटल अंतरभूत काष्ठा task_काष्ठा *cpu_समयr_task_rcu(काष्ठा k_iसमयr *समयr)
अणु
	वापस pid_task(समयr->it.cpu.pid, घड़ी_pid_type(समयr->it_घड़ी));
पूर्ण

/*
 * Update expiry समय from increment, and increase overrun count,
 * given the current घड़ी sample.
 */
अटल u64 bump_cpu_समयr(काष्ठा k_iसमयr *समयr, u64 now)
अणु
	u64 delta, incr, expires = समयr->it.cpu.node.expires;
	पूर्णांक i;

	अगर (!समयr->it_पूर्णांकerval)
		वापस expires;

	अगर (now < expires)
		वापस expires;

	incr = समयr->it_पूर्णांकerval;
	delta = now + incr - expires;

	/* Don't use (incr*2 < delta), incr*2 might overflow. */
	क्रम (i = 0; incr < delta - incr; i++)
		incr = incr << 1;

	क्रम (; i >= 0; incr >>= 1, i--) अणु
		अगर (delta < incr)
			जारी;

		समयr->it.cpu.node.expires += incr;
		समयr->it_overrun += 1LL << i;
		delta -= incr;
	पूर्ण
	वापस समयr->it.cpu.node.expires;
पूर्ण

/* Check whether all cache entries contain U64_MAX, i.e. eternal expiry समय */
अटल अंतरभूत bool expiry_cache_is_inactive(स्थिर काष्ठा posix_cpuसमयrs *pct)
अणु
	वापस !(~pct->bases[CPUCLOCK_PROF].nextevt |
		 ~pct->bases[CPUCLOCK_VIRT].nextevt |
		 ~pct->bases[CPUCLOCK_SCHED].nextevt);
पूर्ण

अटल पूर्णांक
posix_cpu_घड़ी_getres(स्थिर घड़ीid_t which_घड़ी, काष्ठा बारpec64 *tp)
अणु
	पूर्णांक error = validate_घड़ी_permissions(which_घड़ी);

	अगर (!error) अणु
		tp->tv_sec = 0;
		tp->tv_nsec = ((NSEC_PER_SEC + HZ - 1) / HZ);
		अगर (CPUCLOCK_WHICH(which_घड़ी) == CPUCLOCK_SCHED) अणु
			/*
			 * If sched_घड़ी is using a cycle counter, we
			 * करोn't have any idea of its true resolution
			 * exported, but it is much more than 1s/HZ.
			 */
			tp->tv_nsec = 1;
		पूर्ण
	पूर्ण
	वापस error;
पूर्ण

अटल पूर्णांक
posix_cpu_घड़ी_set(स्थिर घड़ीid_t घड़ी, स्थिर काष्ठा बारpec64 *tp)
अणु
	पूर्णांक error = validate_घड़ी_permissions(घड़ी);

	/*
	 * You can never reset a CPU घड़ी, but we check क्रम other errors
	 * in the call beक्रमe failing with EPERM.
	 */
	वापस error ? : -EPERM;
पूर्ण

/*
 * Sample a per-thपढ़ो घड़ी क्रम the given task. clkid is validated.
 */
अटल u64 cpu_घड़ी_sample(स्थिर घड़ीid_t clkid, काष्ठा task_काष्ठा *p)
अणु
	u64 uसमय, sसमय;

	अगर (clkid == CPUCLOCK_SCHED)
		वापस task_sched_runसमय(p);

	task_cpuसमय(p, &uसमय, &sसमय);

	चयन (clkid) अणु
	हाल CPUCLOCK_PROF:
		वापस uसमय + sसमय;
	हाल CPUCLOCK_VIRT:
		वापस uसमय;
	शेष:
		WARN_ON_ONCE(1);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम store_samples(u64 *samples, u64 sसमय, u64 uसमय, u64 rसमय)
अणु
	samples[CPUCLOCK_PROF] = sसमय + uसमय;
	samples[CPUCLOCK_VIRT] = uसमय;
	samples[CPUCLOCK_SCHED] = rसमय;
पूर्ण

अटल व्योम task_sample_cpuसमय(काष्ठा task_काष्ठा *p, u64 *samples)
अणु
	u64 sसमय, uसमय;

	task_cpuसमय(p, &uसमय, &sसमय);
	store_samples(samples, sसमय, uसमय, p->se.sum_exec_runसमय);
पूर्ण

अटल व्योम proc_sample_cpuसमय_atomic(काष्ठा task_cpuसमय_atomic *at,
				       u64 *samples)
अणु
	u64 sसमय, uसमय, rसमय;

	uसमय = atomic64_पढ़ो(&at->uसमय);
	sसमय = atomic64_पढ़ो(&at->sसमय);
	rसमय = atomic64_पढ़ो(&at->sum_exec_runसमय);
	store_samples(samples, sसमय, uसमय, rसमय);
पूर्ण

/*
 * Set cpuसमय to sum_cpuसमय अगर sum_cpuसमय > cpuसमय. Use cmpxchg
 * to aव्योम race conditions with concurrent updates to cpuसमय.
 */
अटल अंतरभूत व्योम __update_gt_cpuसमय(atomic64_t *cpuसमय, u64 sum_cpuसमय)
अणु
	u64 curr_cpuसमय;
retry:
	curr_cpuसमय = atomic64_पढ़ो(cpuसमय);
	अगर (sum_cpuसमय > curr_cpuसमय) अणु
		अगर (atomic64_cmpxchg(cpuसमय, curr_cpuसमय, sum_cpuसमय) != curr_cpuसमय)
			जाओ retry;
	पूर्ण
पूर्ण

अटल व्योम update_gt_cpuसमय(काष्ठा task_cpuसमय_atomic *cpuसमय_atomic,
			      काष्ठा task_cpuसमय *sum)
अणु
	__update_gt_cpuसमय(&cpuसमय_atomic->uसमय, sum->uसमय);
	__update_gt_cpuसमय(&cpuसमय_atomic->sसमय, sum->sसमय);
	__update_gt_cpuसमय(&cpuसमय_atomic->sum_exec_runसमय, sum->sum_exec_runसमय);
पूर्ण

/**
 * thपढ़ो_group_sample_cpuसमय - Sample cpuसमय क्रम a given task
 * @tsk:	Task क्रम which cpuसमय needs to be started
 * @samples:	Storage क्रम समय samples
 *
 * Called from sys_getiसमयr() to calculate the expiry समय of an active
 * समयr. That means group cpuसमय accounting is alपढ़ोy active. Called
 * with task sighand lock held.
 *
 * Updates @बार with an uptodate sample of the thपढ़ो group cpuबार.
 */
व्योम thपढ़ो_group_sample_cpuसमय(काष्ठा task_काष्ठा *tsk, u64 *samples)
अणु
	काष्ठा thपढ़ो_group_cpuसमयr *cpuसमयr = &tsk->संकेत->cpuसमयr;
	काष्ठा posix_cpuसमयrs *pct = &tsk->संकेत->posix_cpuसमयrs;

	WARN_ON_ONCE(!pct->समयrs_active);

	proc_sample_cpuसमय_atomic(&cpuसमयr->cpuसमय_atomic, samples);
पूर्ण

/**
 * thपढ़ो_group_start_cpuसमय - Start cpuसमय and वापस a sample
 * @tsk:	Task क्रम which cpuसमय needs to be started
 * @samples:	Storage क्रम समय samples
 *
 * The thपढ़ो group cpuसमय accounting is aव्योमed when there are no posix
 * CPU समयrs armed. Beक्रमe starting a समयr it's required to check whether
 * the समय accounting is active. If not, a full update of the atomic
 * accounting store needs to be करोne and the accounting enabled.
 *
 * Updates @बार with an uptodate sample of the thपढ़ो group cpuबार.
 */
अटल व्योम thपढ़ो_group_start_cpuसमय(काष्ठा task_काष्ठा *tsk, u64 *samples)
अणु
	काष्ठा thपढ़ो_group_cpuसमयr *cpuसमयr = &tsk->संकेत->cpuसमयr;
	काष्ठा posix_cpuसमयrs *pct = &tsk->संकेत->posix_cpuसमयrs;

	/* Check अगर cpuसमयr isn't running. This is accessed without locking. */
	अगर (!READ_ONCE(pct->समयrs_active)) अणु
		काष्ठा task_cpuसमय sum;

		/*
		 * The POSIX समयr पूर्णांकerface allows क्रम असलolute समय expiry
		 * values through the TIMER_ABSTIME flag, thereक्रमe we have
		 * to synchronize the समयr to the घड़ी every समय we start it.
		 */
		thपढ़ो_group_cpuसमय(tsk, &sum);
		update_gt_cpuसमय(&cpuसमयr->cpuसमय_atomic, &sum);

		/*
		 * We're setting समयrs_active without a lock. Ensure this
		 * only माला_लो written to in one operation. We set it after
		 * update_gt_cpuसमय() as a small optimization, but
		 * barriers are not required because update_gt_cpuसमय()
		 * can handle concurrent updates.
		 */
		WRITE_ONCE(pct->समयrs_active, true);
	पूर्ण
	proc_sample_cpuसमय_atomic(&cpuसमयr->cpuसमय_atomic, samples);
पूर्ण

अटल व्योम __thपढ़ो_group_cpuसमय(काष्ठा task_काष्ठा *tsk, u64 *samples)
अणु
	काष्ठा task_cpuसमय ct;

	thपढ़ो_group_cpuसमय(tsk, &ct);
	store_samples(samples, ct.sसमय, ct.uसमय, ct.sum_exec_runसमय);
पूर्ण

/*
 * Sample a process (thपढ़ो group) घड़ी क्रम the given task clkid. If the
 * group's cpuसमय accounting is alपढ़ोy enabled, पढ़ो the atomic
 * store. Otherwise a full update is required.  clkid is alपढ़ोy validated.
 */
अटल u64 cpu_घड़ी_sample_group(स्थिर घड़ीid_t clkid, काष्ठा task_काष्ठा *p,
				  bool start)
अणु
	काष्ठा thपढ़ो_group_cpuसमयr *cpuसमयr = &p->संकेत->cpuसमयr;
	काष्ठा posix_cpuसमयrs *pct = &p->संकेत->posix_cpuसमयrs;
	u64 samples[CPUCLOCK_MAX];

	अगर (!READ_ONCE(pct->समयrs_active)) अणु
		अगर (start)
			thपढ़ो_group_start_cpuसमय(p, samples);
		अन्यथा
			__thपढ़ो_group_cpuसमय(p, samples);
	पूर्ण अन्यथा अणु
		proc_sample_cpuसमय_atomic(&cpuसमयr->cpuसमय_atomic, samples);
	पूर्ण

	वापस samples[clkid];
पूर्ण

अटल पूर्णांक posix_cpu_घड़ी_get(स्थिर घड़ीid_t घड़ी, काष्ठा बारpec64 *tp)
अणु
	स्थिर घड़ीid_t clkid = CPUCLOCK_WHICH(घड़ी);
	काष्ठा task_काष्ठा *tsk;
	u64 t;

	rcu_पढ़ो_lock();
	tsk = pid_task(pid_क्रम_घड़ी(घड़ी, true), घड़ी_pid_type(घड़ी));
	अगर (!tsk) अणु
		rcu_पढ़ो_unlock();
		वापस -EINVAL;
	पूर्ण

	अगर (CPUCLOCK_PERTHREAD(घड़ी))
		t = cpu_घड़ी_sample(clkid, tsk);
	अन्यथा
		t = cpu_घड़ी_sample_group(clkid, tsk, false);
	rcu_पढ़ो_unlock();

	*tp = ns_to_बारpec64(t);
	वापस 0;
पूर्ण

/*
 * Validate the घड़ीid_t क्रम a new CPU-घड़ी समयr, and initialize the समयr.
 * This is called from sys_समयr_create() and करो_cpu_nanosleep() with the
 * new समयr alपढ़ोy all-zeros initialized.
 */
अटल पूर्णांक posix_cpu_समयr_create(काष्ठा k_iसमयr *new_समयr)
अणु
	अटल काष्ठा lock_class_key posix_cpu_समयrs_key;
	काष्ठा pid *pid;

	rcu_पढ़ो_lock();
	pid = pid_क्रम_घड़ी(new_समयr->it_घड़ी, false);
	अगर (!pid) अणु
		rcu_पढ़ो_unlock();
		वापस -EINVAL;
	पूर्ण

	/*
	 * If posix समयr expiry is handled in task work context then
	 * समयr::it_lock can be taken without disabling पूर्णांकerrupts as all
	 * other locking happens in task context. This requires a separate
	 * lock class key otherwise regular posix समयr expiry would record
	 * the lock class being taken in पूर्णांकerrupt context and generate a
	 * false positive warning.
	 */
	अगर (IS_ENABLED(CONFIG_POSIX_CPU_TIMERS_TASK_WORK))
		lockdep_set_class(&new_समयr->it_lock, &posix_cpu_समयrs_key);

	new_समयr->kघड़ी = &घड़ी_posix_cpu;
	समयrqueue_init(&new_समयr->it.cpu.node);
	new_समयr->it.cpu.pid = get_pid(pid);
	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण

/*
 * Clean up a CPU-घड़ी समयr that is about to be destroyed.
 * This is called from समयr deletion with the समयr alपढ़ोy locked.
 * If we वापस TIMER_RETRY, it's necessary to release the timer's lock
 * and try again.  (This happens when the समयr is in the middle of firing.)
 */
अटल पूर्णांक posix_cpu_समयr_del(काष्ठा k_iसमयr *समयr)
अणु
	काष्ठा cpu_समयr *cपंचांगr = &समयr->it.cpu;
	काष्ठा sighand_काष्ठा *sighand;
	काष्ठा task_काष्ठा *p;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	rcu_पढ़ो_lock();
	p = cpu_समयr_task_rcu(समयr);
	अगर (!p)
		जाओ out;

	/*
	 * Protect against sighand release/चयन in निकास/exec and process/
	 * thपढ़ो समयr list entry concurrent पढ़ो/ग_लिखोs.
	 */
	sighand = lock_task_sighand(p, &flags);
	अगर (unlikely(sighand == शून्य)) अणु
		/*
		 * This raced with the reaping of the task. The निकास cleanup
		 * should have हटाओd this समयr from the समयr queue.
		 */
		WARN_ON_ONCE(cपंचांगr->head || समयrqueue_node_queued(&cपंचांगr->node));
	पूर्ण अन्यथा अणु
		अगर (समयr->it.cpu.firing)
			ret = TIMER_RETRY;
		अन्यथा
			cpu_समयr_dequeue(cपंचांगr);

		unlock_task_sighand(p, &flags);
	पूर्ण

out:
	rcu_पढ़ो_unlock();
	अगर (!ret)
		put_pid(cपंचांगr->pid);

	वापस ret;
पूर्ण

अटल व्योम cleanup_समयrqueue(काष्ठा समयrqueue_head *head)
अणु
	काष्ठा समयrqueue_node *node;
	काष्ठा cpu_समयr *cपंचांगr;

	जबतक ((node = समयrqueue_getnext(head))) अणु
		समयrqueue_del(head, node);
		cपंचांगr = container_of(node, काष्ठा cpu_समयr, node);
		cपंचांगr->head = शून्य;
	पूर्ण
पूर्ण

/*
 * Clean out CPU समयrs which are still armed when a thपढ़ो निकासs. The
 * समयrs are only हटाओd from the list. No other updates are करोne. The
 * corresponding posix समयrs are still accessible, but cannot be rearmed.
 *
 * This must be called with the siglock held.
 */
अटल व्योम cleanup_समयrs(काष्ठा posix_cpuसमयrs *pct)
अणु
	cleanup_समयrqueue(&pct->bases[CPUCLOCK_PROF].tqhead);
	cleanup_समयrqueue(&pct->bases[CPUCLOCK_VIRT].tqhead);
	cleanup_समयrqueue(&pct->bases[CPUCLOCK_SCHED].tqhead);
पूर्ण

/*
 * These are both called with the siglock held, when the current thपढ़ो
 * is being reaped.  When the final (leader) thपढ़ो in the group is reaped,
 * posix_cpu_समयrs_निकास_group will be called after posix_cpu_समयrs_निकास.
 */
व्योम posix_cpu_समयrs_निकास(काष्ठा task_काष्ठा *tsk)
अणु
	cleanup_समयrs(&tsk->posix_cpuसमयrs);
पूर्ण
व्योम posix_cpu_समयrs_निकास_group(काष्ठा task_काष्ठा *tsk)
अणु
	cleanup_समयrs(&tsk->संकेत->posix_cpuसमयrs);
पूर्ण

/*
 * Insert the समयr on the appropriate list beक्रमe any समयrs that
 * expire later.  This must be called with the sighand lock held.
 */
अटल व्योम arm_समयr(काष्ठा k_iसमयr *समयr, काष्ठा task_काष्ठा *p)
अणु
	पूर्णांक clkidx = CPUCLOCK_WHICH(समयr->it_घड़ी);
	काष्ठा cpu_समयr *cपंचांगr = &समयr->it.cpu;
	u64 newexp = cpu_समयr_getexpires(cपंचांगr);
	काष्ठा posix_cpuसमयr_base *base;

	अगर (CPUCLOCK_PERTHREAD(समयr->it_घड़ी))
		base = p->posix_cpuसमयrs.bases + clkidx;
	अन्यथा
		base = p->संकेत->posix_cpuसमयrs.bases + clkidx;

	अगर (!cpu_समयr_enqueue(&base->tqhead, cपंचांगr))
		वापस;

	/*
	 * We are the new earliest-expiring POSIX 1.b समयr, hence
	 * need to update expiration cache. Take पूर्णांकo account that
	 * क्रम process समयrs we share expiration cache with iसमयrs
	 * and RLIMIT_CPU and क्रम thपढ़ो समयrs with RLIMIT_RTTIME.
	 */
	अगर (newexp < base->nextevt)
		base->nextevt = newexp;

	अगर (CPUCLOCK_PERTHREAD(समयr->it_घड़ी))
		tick_dep_set_task(p, TICK_DEP_BIT_POSIX_TIMER);
	अन्यथा
		tick_dep_set_संकेत(p->संकेत, TICK_DEP_BIT_POSIX_TIMER);
पूर्ण

/*
 * The समयr is locked, fire it and arrange क्रम its reload.
 */
अटल व्योम cpu_समयr_fire(काष्ठा k_iसमयr *समयr)
अणु
	काष्ठा cpu_समयr *cपंचांगr = &समयr->it.cpu;

	अगर ((समयr->it_sigev_notअगरy & ~SIGEV_THREAD_ID) == SIGEV_NONE) अणु
		/*
		 * User करोn't want any संकेत.
		 */
		cpu_समयr_setexpires(cपंचांगr, 0);
	पूर्ण अन्यथा अगर (unlikely(समयr->sigq == शून्य)) अणु
		/*
		 * This a special हाल क्रम घड़ी_nanosleep,
		 * not a normal समयr from sys_समयr_create.
		 */
		wake_up_process(समयr->it_process);
		cpu_समयr_setexpires(cपंचांगr, 0);
	पूर्ण अन्यथा अगर (!समयr->it_पूर्णांकerval) अणु
		/*
		 * One-shot समयr.  Clear it as soon as it's fired.
		 */
		posix_समयr_event(समयr, 0);
		cpu_समयr_setexpires(cपंचांगr, 0);
	पूर्ण अन्यथा अगर (posix_समयr_event(समयr, ++समयr->it_requeue_pending)) अणु
		/*
		 * The संकेत did not get queued because the संकेत
		 * was ignored, so we won't get any callback to
		 * reload the समयr.  But we need to keep it
		 * ticking in हाल the संकेत is deliverable next समय.
		 */
		posix_cpu_समयr_rearm(समयr);
		++समयr->it_requeue_pending;
	पूर्ण
पूर्ण

/*
 * Guts of sys_समयr_समय_रखो क्रम CPU समयrs.
 * This is called with the समयr locked and पूर्णांकerrupts disabled.
 * If we वापस TIMER_RETRY, it's necessary to release the timer's lock
 * and try again.  (This happens when the समयr is in the middle of firing.)
 */
अटल पूर्णांक posix_cpu_समयr_set(काष्ठा k_iसमयr *समयr, पूर्णांक समयr_flags,
			       काष्ठा iसमयrspec64 *new, काष्ठा iसमयrspec64 *old)
अणु
	घड़ीid_t clkid = CPUCLOCK_WHICH(समयr->it_घड़ी);
	u64 old_expires, new_expires, old_incr, val;
	काष्ठा cpu_समयr *cपंचांगr = &समयr->it.cpu;
	काष्ठा sighand_काष्ठा *sighand;
	काष्ठा task_काष्ठा *p;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	rcu_पढ़ो_lock();
	p = cpu_समयr_task_rcu(समयr);
	अगर (!p) अणु
		/*
		 * If p has just been reaped, we can no
		 * दीर्घer get any inक्रमmation about it at all.
		 */
		rcu_पढ़ो_unlock();
		वापस -ESRCH;
	पूर्ण

	/*
	 * Use the to_kसमय conversion because that clamps the maximum
	 * value to KTIME_MAX and aव्योम multiplication overflows.
	 */
	new_expires = kसमय_प्रकारo_ns(बारpec64_to_kसमय(new->it_value));

	/*
	 * Protect against sighand release/चयन in निकास/exec and p->cpu_समयrs
	 * and p->संकेत->cpu_समयrs पढ़ो/ग_लिखो in arm_समयr()
	 */
	sighand = lock_task_sighand(p, &flags);
	/*
	 * If p has just been reaped, we can no
	 * दीर्घer get any inक्रमmation about it at all.
	 */
	अगर (unlikely(sighand == शून्य)) अणु
		rcu_पढ़ो_unlock();
		वापस -ESRCH;
	पूर्ण

	/*
	 * Disarm any old समयr after extracting its expiry समय.
	 */
	old_incr = समयr->it_पूर्णांकerval;
	old_expires = cpu_समयr_getexpires(cपंचांगr);

	अगर (unlikely(समयr->it.cpu.firing)) अणु
		समयr->it.cpu.firing = -1;
		ret = TIMER_RETRY;
	पूर्ण अन्यथा अणु
		cpu_समयr_dequeue(cपंचांगr);
	पूर्ण

	/*
	 * We need to sample the current value to convert the new
	 * value from to relative and असलolute, and to convert the
	 * old value from असलolute to relative.  To set a process
	 * समयr, we need a sample to balance the thपढ़ो expiry
	 * बार (in arm_समयr).  With an असलolute समय, we must
	 * check अगर it's alपढ़ोy passed.  In लघु, we need a sample.
	 */
	अगर (CPUCLOCK_PERTHREAD(समयr->it_घड़ी))
		val = cpu_घड़ी_sample(clkid, p);
	अन्यथा
		val = cpu_घड़ी_sample_group(clkid, p, true);

	अगर (old) अणु
		अगर (old_expires == 0) अणु
			old->it_value.tv_sec = 0;
			old->it_value.tv_nsec = 0;
		पूर्ण अन्यथा अणु
			/*
			 * Update the समयr in हाल it has overrun alपढ़ोy.
			 * If it has, we'll report it as having overrun and
			 * with the next reloaded समयr alपढ़ोy ticking,
			 * though we are swallowing that pending
			 * notअगरication here to install the new setting.
			 */
			u64 exp = bump_cpu_समयr(समयr, val);

			अगर (val < exp) अणु
				old_expires = exp - val;
				old->it_value = ns_to_बारpec64(old_expires);
			पूर्ण अन्यथा अणु
				old->it_value.tv_nsec = 1;
				old->it_value.tv_sec = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (unlikely(ret)) अणु
		/*
		 * We are colliding with the समयr actually firing.
		 * Punt after filling in the समयr's old value, and
		 * disable this firing since we are alपढ़ोy reporting
		 * it as an overrun (thanks to bump_cpu_समयr above).
		 */
		unlock_task_sighand(p, &flags);
		जाओ out;
	पूर्ण

	अगर (new_expires != 0 && !(समयr_flags & TIMER_ABSTIME)) अणु
		new_expires += val;
	पूर्ण

	/*
	 * Install the new expiry समय (or zero).
	 * For a समयr with no notअगरication action, we करोn't actually
	 * arm the समयr (we'll just fake it क्रम समयr_समय_लो).
	 */
	cpu_समयr_setexpires(cपंचांगr, new_expires);
	अगर (new_expires != 0 && val < new_expires) अणु
		arm_समयr(समयr, p);
	पूर्ण

	unlock_task_sighand(p, &flags);
	/*
	 * Install the new reload setting, and
	 * set up the संकेत and overrun bookkeeping.
	 */
	समयr->it_पूर्णांकerval = बारpec64_to_kसमय(new->it_पूर्णांकerval);

	/*
	 * This acts as a modअगरication बारtamp क्रम the समयr,
	 * so any स्वतःmatic reload attempt will punt on seeing
	 * that we have reset the समयr manually.
	 */
	समयr->it_requeue_pending = (समयr->it_requeue_pending + 2) &
		~REQUEUE_PENDING;
	समयr->it_overrun_last = 0;
	समयr->it_overrun = -1;

	अगर (new_expires != 0 && !(val < new_expires)) अणु
		/*
		 * The designated समय alपढ़ोy passed, so we notअगरy
		 * immediately, even अगर the thपढ़ो never runs to
		 * accumulate more समय on this घड़ी.
		 */
		cpu_समयr_fire(समयr);
	पूर्ण

	ret = 0;
 out:
	rcu_पढ़ो_unlock();
	अगर (old)
		old->it_पूर्णांकerval = ns_to_बारpec64(old_incr);

	वापस ret;
पूर्ण

अटल व्योम posix_cpu_समयr_get(काष्ठा k_iसमयr *समयr, काष्ठा iसमयrspec64 *itp)
अणु
	घड़ीid_t clkid = CPUCLOCK_WHICH(समयr->it_घड़ी);
	काष्ठा cpu_समयr *cपंचांगr = &समयr->it.cpu;
	u64 now, expires = cpu_समयr_getexpires(cपंचांगr);
	काष्ठा task_काष्ठा *p;

	rcu_पढ़ो_lock();
	p = cpu_समयr_task_rcu(समयr);
	अगर (!p)
		जाओ out;

	/*
	 * Easy part: convert the reload समय.
	 */
	itp->it_पूर्णांकerval = kसमय_प्रकारo_बारpec64(समयr->it_पूर्णांकerval);

	अगर (!expires)
		जाओ out;

	/*
	 * Sample the घड़ी to take the dअगरference with the expiry समय.
	 */
	अगर (CPUCLOCK_PERTHREAD(समयr->it_घड़ी))
		now = cpu_घड़ी_sample(clkid, p);
	अन्यथा
		now = cpu_घड़ी_sample_group(clkid, p, false);

	अगर (now < expires) अणु
		itp->it_value = ns_to_बारpec64(expires - now);
	पूर्ण अन्यथा अणु
		/*
		 * The समयr should have expired alपढ़ोy, but the firing
		 * hasn't taken place yet.  Say it's just about to expire.
		 */
		itp->it_value.tv_nsec = 1;
		itp->it_value.tv_sec = 0;
	पूर्ण
out:
	rcu_पढ़ो_unlock();
पूर्ण

#घोषणा MAX_COLLECTED	20

अटल u64 collect_समयrqueue(काष्ठा समयrqueue_head *head,
			      काष्ठा list_head *firing, u64 now)
अणु
	काष्ठा समयrqueue_node *next;
	पूर्णांक i = 0;

	जबतक ((next = समयrqueue_getnext(head))) अणु
		काष्ठा cpu_समयr *cपंचांगr;
		u64 expires;

		cपंचांगr = container_of(next, काष्ठा cpu_समयr, node);
		expires = cpu_समयr_getexpires(cपंचांगr);
		/* Limit the number of समयrs to expire at once */
		अगर (++i == MAX_COLLECTED || now < expires)
			वापस expires;

		cपंचांगr->firing = 1;
		cpu_समयr_dequeue(cपंचांगr);
		list_add_tail(&cपंचांगr->elist, firing);
	पूर्ण

	वापस U64_MAX;
पूर्ण

अटल व्योम collect_posix_cpuसमयrs(काष्ठा posix_cpuसमयrs *pct, u64 *samples,
				    काष्ठा list_head *firing)
अणु
	काष्ठा posix_cpuसमयr_base *base = pct->bases;
	पूर्णांक i;

	क्रम (i = 0; i < CPUCLOCK_MAX; i++, base++) अणु
		base->nextevt = collect_समयrqueue(&base->tqhead, firing,
						    samples[i]);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम check_dl_overrun(काष्ठा task_काष्ठा *tsk)
अणु
	अगर (tsk->dl.dl_overrun) अणु
		tsk->dl.dl_overrun = 0;
		__group_send_sig_info(SIGXCPU, SEND_SIG_PRIV, tsk);
	पूर्ण
पूर्ण

अटल bool check_rlimit(u64 समय, u64 limit, पूर्णांक signo, bool rt, bool hard)
अणु
	अगर (समय < limit)
		वापस false;

	अगर (prपूर्णांक_fatal_संकेतs) अणु
		pr_info("%s Watchdog Timeout (%s): %s[%d]\n",
			rt ? "RT" : "CPU", hard ? "hard" : "soft",
			current->comm, task_pid_nr(current));
	पूर्ण
	__group_send_sig_info(signo, SEND_SIG_PRIV, current);
	वापस true;
पूर्ण

/*
 * Check क्रम any per-thपढ़ो CPU समयrs that have fired and move them off
 * the tsk->cpu_समयrs[N] list onto the firing list.  Here we update the
 * tsk->it_*_expires values to reflect the reमुख्यing thपढ़ो CPU समयrs.
 */
अटल व्योम check_thपढ़ो_समयrs(काष्ठा task_काष्ठा *tsk,
				काष्ठा list_head *firing)
अणु
	काष्ठा posix_cpuसमयrs *pct = &tsk->posix_cpuसमयrs;
	u64 samples[CPUCLOCK_MAX];
	अचिन्हित दीर्घ soft;

	अगर (dl_task(tsk))
		check_dl_overrun(tsk);

	अगर (expiry_cache_is_inactive(pct))
		वापस;

	task_sample_cpuसमय(tsk, samples);
	collect_posix_cpuसमयrs(pct, samples, firing);

	/*
	 * Check क्रम the special हाल thपढ़ो समयrs.
	 */
	soft = task_rlimit(tsk, RLIMIT_RTTIME);
	अगर (soft != RLIM_अनन्त) अणु
		/* Task RT समयout is accounted in jअगरfies. RTTIME is usec */
		अचिन्हित दीर्घ rtसमय = tsk->rt.समयout * (USEC_PER_SEC / HZ);
		अचिन्हित दीर्घ hard = task_rlimit_max(tsk, RLIMIT_RTTIME);

		/* At the hard limit, send SIGKILL. No further action. */
		अगर (hard != RLIM_अनन्त &&
		    check_rlimit(rtसमय, hard, SIGKILL, true, true))
			वापस;

		/* At the soft limit, send a SIGXCPU every second */
		अगर (check_rlimit(rtसमय, soft, SIGXCPU, true, false)) अणु
			soft += USEC_PER_SEC;
			tsk->संकेत->rlim[RLIMIT_RTTIME].rlim_cur = soft;
		पूर्ण
	पूर्ण

	अगर (expiry_cache_is_inactive(pct))
		tick_dep_clear_task(tsk, TICK_DEP_BIT_POSIX_TIMER);
पूर्ण

अटल अंतरभूत व्योम stop_process_समयrs(काष्ठा संकेत_काष्ठा *sig)
अणु
	काष्ठा posix_cpuसमयrs *pct = &sig->posix_cpuसमयrs;

	/* Turn off the active flag. This is करोne without locking. */
	WRITE_ONCE(pct->समयrs_active, false);
	tick_dep_clear_संकेत(sig, TICK_DEP_BIT_POSIX_TIMER);
पूर्ण

अटल व्योम check_cpu_iसमयr(काष्ठा task_काष्ठा *tsk, काष्ठा cpu_iसमयr *it,
			     u64 *expires, u64 cur_समय, पूर्णांक signo)
अणु
	अगर (!it->expires)
		वापस;

	अगर (cur_समय >= it->expires) अणु
		अगर (it->incr)
			it->expires += it->incr;
		अन्यथा
			it->expires = 0;

		trace_iसमयr_expire(signo == SIGPROF ?
				    ITIMER_PROF : ITIMER_VIRTUAL,
				    task_tgid(tsk), cur_समय);
		__group_send_sig_info(signo, SEND_SIG_PRIV, tsk);
	पूर्ण

	अगर (it->expires && it->expires < *expires)
		*expires = it->expires;
पूर्ण

/*
 * Check क्रम any per-thपढ़ो CPU समयrs that have fired and move them
 * off the tsk->*_समयrs list onto the firing list.  Per-thपढ़ो समयrs
 * have alपढ़ोy been taken off.
 */
अटल व्योम check_process_समयrs(काष्ठा task_काष्ठा *tsk,
				 काष्ठा list_head *firing)
अणु
	काष्ठा संकेत_काष्ठा *स्थिर sig = tsk->संकेत;
	काष्ठा posix_cpuसमयrs *pct = &sig->posix_cpuसमयrs;
	u64 samples[CPUCLOCK_MAX];
	अचिन्हित दीर्घ soft;

	/*
	 * If there are no active process wide समयrs (POSIX 1.b, iसमयrs,
	 * RLIMIT_CPU) nothing to check. Also skip the process wide समयr
	 * processing when there is alपढ़ोy another task handling them.
	 */
	अगर (!READ_ONCE(pct->समयrs_active) || pct->expiry_active)
		वापस;

	/*
	 * Signअगरy that a thपढ़ो is checking क्रम process समयrs.
	 * Write access to this field is रक्षित by the sighand lock.
	 */
	pct->expiry_active = true;

	/*
	 * Collect the current process totals. Group accounting is active
	 * so the sample can be taken directly.
	 */
	proc_sample_cpuसमय_atomic(&sig->cpuसमयr.cpuसमय_atomic, samples);
	collect_posix_cpuसमयrs(pct, samples, firing);

	/*
	 * Check क्रम the special हाल process समयrs.
	 */
	check_cpu_iसमयr(tsk, &sig->it[CPUCLOCK_PROF],
			 &pct->bases[CPUCLOCK_PROF].nextevt,
			 samples[CPUCLOCK_PROF], SIGPROF);
	check_cpu_iसमयr(tsk, &sig->it[CPUCLOCK_VIRT],
			 &pct->bases[CPUCLOCK_VIRT].nextevt,
			 samples[CPUCLOCK_VIRT], SIGVTALRM);

	soft = task_rlimit(tsk, RLIMIT_CPU);
	अगर (soft != RLIM_अनन्त) अणु
		/* RLIMIT_CPU is in seconds. Samples are nanoseconds */
		अचिन्हित दीर्घ hard = task_rlimit_max(tsk, RLIMIT_CPU);
		u64 pसमय = samples[CPUCLOCK_PROF];
		u64 softns = (u64)soft * NSEC_PER_SEC;
		u64 hardns = (u64)hard * NSEC_PER_SEC;

		/* At the hard limit, send SIGKILL. No further action. */
		अगर (hard != RLIM_अनन्त &&
		    check_rlimit(pसमय, hardns, SIGKILL, false, true))
			वापस;

		/* At the soft limit, send a SIGXCPU every second */
		अगर (check_rlimit(pसमय, softns, SIGXCPU, false, false)) अणु
			sig->rlim[RLIMIT_CPU].rlim_cur = soft + 1;
			softns += NSEC_PER_SEC;
		पूर्ण

		/* Update the expiry cache */
		अगर (softns < pct->bases[CPUCLOCK_PROF].nextevt)
			pct->bases[CPUCLOCK_PROF].nextevt = softns;
	पूर्ण

	अगर (expiry_cache_is_inactive(pct))
		stop_process_समयrs(sig);

	pct->expiry_active = false;
पूर्ण

/*
 * This is called from the संकेत code (via posixसमयr_rearm)
 * when the last समयr संकेत was delivered and we have to reload the समयr.
 */
अटल व्योम posix_cpu_समयr_rearm(काष्ठा k_iसमयr *समयr)
अणु
	घड़ीid_t clkid = CPUCLOCK_WHICH(समयr->it_घड़ी);
	काष्ठा task_काष्ठा *p;
	काष्ठा sighand_काष्ठा *sighand;
	अचिन्हित दीर्घ flags;
	u64 now;

	rcu_पढ़ो_lock();
	p = cpu_समयr_task_rcu(समयr);
	अगर (!p)
		जाओ out;

	/*
	 * Fetch the current sample and update the समयr's expiry समय.
	 */
	अगर (CPUCLOCK_PERTHREAD(समयr->it_घड़ी))
		now = cpu_घड़ी_sample(clkid, p);
	अन्यथा
		now = cpu_घड़ी_sample_group(clkid, p, true);

	bump_cpu_समयr(समयr, now);

	/* Protect समयr list r/w in arm_समयr() */
	sighand = lock_task_sighand(p, &flags);
	अगर (unlikely(sighand == शून्य))
		जाओ out;

	/*
	 * Now re-arm क्रम the new expiry समय.
	 */
	arm_समयr(समयr, p);
	unlock_task_sighand(p, &flags);
out:
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * task_cpuसमयrs_expired - Check whether posix CPU समयrs are expired
 *
 * @samples:	Array of current samples क्रम the CPUCLOCK घड़ीs
 * @pct:	Poपूर्णांकer to a posix_cpuसमयrs container
 *
 * Returns true अगर any member of @samples is greater than the corresponding
 * member of @pct->bases[CLK].nextevt. False otherwise
 */
अटल अंतरभूत bool
task_cpuसमयrs_expired(स्थिर u64 *samples, काष्ठा posix_cpuसमयrs *pct)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < CPUCLOCK_MAX; i++) अणु
		अगर (samples[i] >= pct->bases[i].nextevt)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * fastpath_समयr_check - POSIX CPU समयrs fast path.
 *
 * @tsk:	The task (thपढ़ो) being checked.
 *
 * Check the task and thपढ़ो group समयrs.  If both are zero (there are no
 * समयrs set) वापस false.  Otherwise snapshot the task and thपढ़ो group
 * समयrs and compare them with the corresponding expiration बार.  Return
 * true अगर a समयr has expired, अन्यथा वापस false.
 */
अटल अंतरभूत bool fastpath_समयr_check(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा posix_cpuसमयrs *pct = &tsk->posix_cpuसमयrs;
	काष्ठा संकेत_काष्ठा *sig;

	अगर (!expiry_cache_is_inactive(pct)) अणु
		u64 samples[CPUCLOCK_MAX];

		task_sample_cpuसमय(tsk, samples);
		अगर (task_cpuसमयrs_expired(samples, pct))
			वापस true;
	पूर्ण

	sig = tsk->संकेत;
	pct = &sig->posix_cpuसमयrs;
	/*
	 * Check अगर thपढ़ो group समयrs expired when समयrs are active and
	 * no other thपढ़ो in the group is alपढ़ोy handling expiry क्रम
	 * thपढ़ो group cpuसमयrs. These fields are पढ़ो without the
	 * sighand lock. However, this is fine because this is meant to be
	 * a fastpath heuristic to determine whether we should try to
	 * acquire the sighand lock to handle समयr expiry.
	 *
	 * In the worst हाल scenario, अगर concurrently समयrs_active is set
	 * or expiry_active is cleared, but the current thपढ़ो करोesn't see
	 * the change yet, the समयr checks are delayed until the next
	 * thपढ़ो in the group माला_लो a scheduler पूर्णांकerrupt to handle the
	 * समयr. This isn't an issue in practice because these types of
	 * delays with संकेतs actually getting sent are expected.
	 */
	अगर (READ_ONCE(pct->समयrs_active) && !READ_ONCE(pct->expiry_active)) अणु
		u64 samples[CPUCLOCK_MAX];

		proc_sample_cpuसमय_atomic(&sig->cpuसमयr.cpuसमय_atomic,
					   samples);

		अगर (task_cpuसमयrs_expired(samples, pct))
			वापस true;
	पूर्ण

	अगर (dl_task(tsk) && tsk->dl.dl_overrun)
		वापस true;

	वापस false;
पूर्ण

अटल व्योम handle_posix_cpu_समयrs(काष्ठा task_काष्ठा *tsk);

#अगर_घोषित CONFIG_POSIX_CPU_TIMERS_TASK_WORK
अटल व्योम posix_cpu_समयrs_work(काष्ठा callback_head *work)
अणु
	handle_posix_cpu_समयrs(current);
पूर्ण

/*
 * Initialize posix CPU समयrs task work in init task. Out of line to
 * keep the callback अटल and to aव्योम header recursion hell.
 */
व्योम __init posix_cpuसमयrs_init_work(व्योम)
अणु
	init_task_work(&current->posix_cpuसमयrs_work.work,
		       posix_cpu_समयrs_work);
पूर्ण

/*
 * Note: All operations on tsk->posix_cpuसमयr_work.scheduled happen either
 * in hard पूर्णांकerrupt context or in task context with पूर्णांकerrupts
 * disabled. Aside of that the ग_लिखोr/पढ़ोer पूर्णांकeraction is always in the
 * context of the current task, which means they are strict per CPU.
 */
अटल अंतरभूत bool posix_cpu_समयrs_work_scheduled(काष्ठा task_काष्ठा *tsk)
अणु
	वापस tsk->posix_cpuसमयrs_work.scheduled;
पूर्ण

अटल अंतरभूत व्योम __run_posix_cpu_समयrs(काष्ठा task_काष्ठा *tsk)
अणु
	अगर (WARN_ON_ONCE(tsk->posix_cpuसमयrs_work.scheduled))
		वापस;

	/* Schedule task work to actually expire the समयrs */
	tsk->posix_cpuसमयrs_work.scheduled = true;
	task_work_add(tsk, &tsk->posix_cpuसमयrs_work.work, TWA_RESUME);
पूर्ण

अटल अंतरभूत bool posix_cpu_समयrs_enable_work(काष्ठा task_काष्ठा *tsk,
						अचिन्हित दीर्घ start)
अणु
	bool ret = true;

	/*
	 * On !RT kernels पूर्णांकerrupts are disabled जबतक collecting expired
	 * समयrs, so no tick can happen and the fast path check can be
	 * reenabled without further checks.
	 */
	अगर (!IS_ENABLED(CONFIG_PREEMPT_RT)) अणु
		tsk->posix_cpuसमयrs_work.scheduled = false;
		वापस true;
	पूर्ण

	/*
	 * On RT enabled kernels ticks can happen जबतक the expired समयrs
	 * are collected under sighand lock. But any tick which observes
	 * the CPUTIMERS_WORK_SCHEDULED bit set, करोes not run the fastpath
	 * checks. So reenabling the tick work has करो be करोne carefully:
	 *
	 * Disable पूर्णांकerrupts and run the fast path check अगर jअगरfies have
	 * advanced since the collecting of expired समयrs started. If
	 * jअगरfies have not advanced or the fast path check did not find
	 * newly expired समयrs, reenable the fast path check in the समयr
	 * पूर्णांकerrupt. If there are newly expired समयrs, वापस false and
	 * let the collection loop repeat.
	 */
	local_irq_disable();
	अगर (start != jअगरfies && fastpath_समयr_check(tsk))
		ret = false;
	अन्यथा
		tsk->posix_cpuसमयrs_work.scheduled = false;
	local_irq_enable();

	वापस ret;
पूर्ण
#अन्यथा /* CONFIG_POSIX_CPU_TIMERS_TASK_WORK */
अटल अंतरभूत व्योम __run_posix_cpu_समयrs(काष्ठा task_काष्ठा *tsk)
अणु
	lockdep_posixसमयr_enter();
	handle_posix_cpu_समयrs(tsk);
	lockdep_posixसमयr_निकास();
पूर्ण

अटल अंतरभूत bool posix_cpu_समयrs_work_scheduled(काष्ठा task_काष्ठा *tsk)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool posix_cpu_समयrs_enable_work(काष्ठा task_काष्ठा *tsk,
						अचिन्हित दीर्घ start)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर /* CONFIG_POSIX_CPU_TIMERS_TASK_WORK */

अटल व्योम handle_posix_cpu_समयrs(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा k_iसमयr *समयr, *next;
	अचिन्हित दीर्घ flags, start;
	LIST_HEAD(firing);

	अगर (!lock_task_sighand(tsk, &flags))
		वापस;

	करो अणु
		/*
		 * On RT locking sighand lock करोes not disable पूर्णांकerrupts,
		 * so this needs to be careful vs. ticks. Store the current
		 * jअगरfies value.
		 */
		start = READ_ONCE(jअगरfies);
		barrier();

		/*
		 * Here we take off tsk->संकेत->cpu_समयrs[N] and
		 * tsk->cpu_समयrs[N] all the समयrs that are firing, and
		 * put them on the firing list.
		 */
		check_thपढ़ो_समयrs(tsk, &firing);

		check_process_समयrs(tsk, &firing);

		/*
		 * The above समयr checks have updated the expiry cache and
		 * because nothing can have queued or modअगरied समयrs after
		 * sighand lock was taken above it is guaranteed to be
		 * consistent. So the next समयr पूर्णांकerrupt fastpath check
		 * will find valid data.
		 *
		 * If समयr expiry runs in the समयr पूर्णांकerrupt context then
		 * the loop is not relevant as समयrs will be directly
		 * expired in पूर्णांकerrupt context. The stub function below
		 * वापसs always true which allows the compiler to
		 * optimize the loop out.
		 *
		 * If समयr expiry is deferred to task work context then
		 * the following rules apply:
		 *
		 * - On !RT kernels no tick can have happened on this CPU
		 *   after sighand lock was acquired because पूर्णांकerrupts are
		 *   disabled. So reenabling task work beक्रमe dropping
		 *   sighand lock and reenabling पूर्णांकerrupts is race मुक्त.
		 *
		 * - On RT kernels ticks might have happened but the tick
		 *   work ignored posix CPU समयr handling because the
		 *   CPUTIMERS_WORK_SCHEDULED bit is set. Reenabling work
		 *   must be करोne very carefully including a check whether
		 *   ticks have happened since the start of the समयr
		 *   expiry checks. posix_cpu_समयrs_enable_work() takes
		 *   care of that and eventually lets the expiry checks
		 *   run again.
		 */
	पूर्ण जबतक (!posix_cpu_समयrs_enable_work(tsk, start));

	/*
	 * We must release sighand lock beक्रमe taking any समयr's lock.
	 * There is a potential race with समयr deletion here, as the
	 * siglock now protects our निजी firing list.  We have set
	 * the firing flag in each समयr, so that a deletion attempt
	 * that माला_लो the समयr lock beक्रमe we करो will give it up and
	 * spin until we've taken care of that समयr below.
	 */
	unlock_task_sighand(tsk, &flags);

	/*
	 * Now that all the समयrs on our list have the firing flag,
	 * no one will touch their list entries but us.  We'll take
	 * each समयr's lock beक्रमe clearing its firing flag, so no
	 * समयr call will पूर्णांकerfere.
	 */
	list_क्रम_each_entry_safe(समयr, next, &firing, it.cpu.elist) अणु
		पूर्णांक cpu_firing;

		/*
		 * spin_lock() is sufficient here even independent of the
		 * expiry context. If expiry happens in hard पूर्णांकerrupt
		 * context it's obvious. For task work context it's safe
		 * because all other operations on समयr::it_lock happen in
		 * task context (syscall or निकास).
		 */
		spin_lock(&समयr->it_lock);
		list_del_init(&समयr->it.cpu.elist);
		cpu_firing = समयr->it.cpu.firing;
		समयr->it.cpu.firing = 0;
		/*
		 * The firing flag is -1 अगर we collided with a reset
		 * of the समयr, which alपढ़ोy reported this
		 * almost-firing as an overrun.  So करोn't generate an event.
		 */
		अगर (likely(cpu_firing >= 0))
			cpu_समयr_fire(समयr);
		spin_unlock(&समयr->it_lock);
	पूर्ण
पूर्ण

/*
 * This is called from the समयr पूर्णांकerrupt handler.  The irq handler has
 * alपढ़ोy updated our counts.  We need to check अगर any समयrs fire now.
 * Interrupts are disabled.
 */
व्योम run_posix_cpu_समयrs(व्योम)
अणु
	काष्ठा task_काष्ठा *tsk = current;

	lockdep_निश्चित_irqs_disabled();

	/*
	 * If the actual expiry is deferred to task work context and the
	 * work is alपढ़ोy scheduled there is no poपूर्णांक to करो anything here.
	 */
	अगर (posix_cpu_समयrs_work_scheduled(tsk))
		वापस;

	/*
	 * The fast path checks that there are no expired thपढ़ो or thपढ़ो
	 * group समयrs.  If that's so, just वापस.
	 */
	अगर (!fastpath_समयr_check(tsk))
		वापस;

	__run_posix_cpu_समयrs(tsk);
पूर्ण

/*
 * Set one of the process-wide special हाल CPU समयrs or RLIMIT_CPU.
 * The tsk->sighand->siglock must be held by the caller.
 */
व्योम set_process_cpu_समयr(काष्ठा task_काष्ठा *tsk, अचिन्हित पूर्णांक clkid,
			   u64 *newval, u64 *oldval)
अणु
	u64 now, *nextevt;

	अगर (WARN_ON_ONCE(clkid >= CPUCLOCK_SCHED))
		वापस;

	nextevt = &tsk->संकेत->posix_cpuसमयrs.bases[clkid].nextevt;
	now = cpu_घड़ी_sample_group(clkid, tsk, true);

	अगर (oldval) अणु
		/*
		 * We are setting iसमयr. The *oldval is असलolute and we update
		 * it to be relative, *newval argument is relative and we update
		 * it to be असलolute.
		 */
		अगर (*oldval) अणु
			अगर (*oldval <= now) अणु
				/* Just about to fire. */
				*oldval = TICK_NSEC;
			पूर्ण अन्यथा अणु
				*oldval -= now;
			पूर्ण
		पूर्ण

		अगर (!*newval)
			वापस;
		*newval += now;
	पूर्ण

	/*
	 * Update expiration cache अगर this is the earliest समयr. CPUCLOCK_PROF
	 * expiry cache is also used by RLIMIT_CPU!.
	 */
	अगर (*newval < *nextevt)
		*nextevt = *newval;

	tick_dep_set_संकेत(tsk->संकेत, TICK_DEP_BIT_POSIX_TIMER);
पूर्ण

अटल पूर्णांक करो_cpu_nanosleep(स्थिर घड़ीid_t which_घड़ी, पूर्णांक flags,
			    स्थिर काष्ठा बारpec64 *rqtp)
अणु
	काष्ठा iसमयrspec64 it;
	काष्ठा k_iसमयr समयr;
	u64 expires;
	पूर्णांक error;

	/*
	 * Set up a temporary समयr and then रुको क्रम it to go off.
	 */
	स_रखो(&समयr, 0, माप समयr);
	spin_lock_init(&समयr.it_lock);
	समयr.it_घड़ी = which_घड़ी;
	समयr.it_overrun = -1;
	error = posix_cpu_समयr_create(&समयr);
	समयr.it_process = current;

	अगर (!error) अणु
		अटल काष्ठा iसमयrspec64 zero_it;
		काष्ठा restart_block *restart;

		स_रखो(&it, 0, माप(it));
		it.it_value = *rqtp;

		spin_lock_irq(&समयr.it_lock);
		error = posix_cpu_समयr_set(&समयr, flags, &it, शून्य);
		अगर (error) अणु
			spin_unlock_irq(&समयr.it_lock);
			वापस error;
		पूर्ण

		जबतक (!संकेत_pending(current)) अणु
			अगर (!cpu_समयr_getexpires(&समयr.it.cpu)) अणु
				/*
				 * Our समयr fired and was reset, below
				 * deletion can not fail.
				 */
				posix_cpu_समयr_del(&समयr);
				spin_unlock_irq(&समयr.it_lock);
				वापस 0;
			पूर्ण

			/*
			 * Block until cpu_समयr_fire (or a संकेत) wakes us.
			 */
			__set_current_state(TASK_INTERRUPTIBLE);
			spin_unlock_irq(&समयr.it_lock);
			schedule();
			spin_lock_irq(&समयr.it_lock);
		पूर्ण

		/*
		 * We were पूर्णांकerrupted by a संकेत.
		 */
		expires = cpu_समयr_getexpires(&समयr.it.cpu);
		error = posix_cpu_समयr_set(&समयr, 0, &zero_it, &it);
		अगर (!error) अणु
			/*
			 * Timer is now unarmed, deletion can not fail.
			 */
			posix_cpu_समयr_del(&समयr);
		पूर्ण
		spin_unlock_irq(&समयr.it_lock);

		जबतक (error == TIMER_RETRY) अणु
			/*
			 * We need to handle हाल when समयr was or is in the
			 * middle of firing. In other हालs we alपढ़ोy मुक्तd
			 * resources.
			 */
			spin_lock_irq(&समयr.it_lock);
			error = posix_cpu_समयr_del(&समयr);
			spin_unlock_irq(&समयr.it_lock);
		पूर्ण

		अगर ((it.it_value.tv_sec | it.it_value.tv_nsec) == 0) अणु
			/*
			 * It actually did fire alपढ़ोy.
			 */
			वापस 0;
		पूर्ण

		error = -ERESTART_RESTARTBLOCK;
		/*
		 * Report back to the user the समय still reमुख्यing.
		 */
		restart = &current->restart_block;
		restart->nanosleep.expires = expires;
		अगर (restart->nanosleep.type != TT_NONE)
			error = nanosleep_copyout(restart, &it.it_value);
	पूर्ण

	वापस error;
पूर्ण

अटल दीर्घ posix_cpu_nsleep_restart(काष्ठा restart_block *restart_block);

अटल पूर्णांक posix_cpu_nsleep(स्थिर घड़ीid_t which_घड़ी, पूर्णांक flags,
			    स्थिर काष्ठा बारpec64 *rqtp)
अणु
	काष्ठा restart_block *restart_block = &current->restart_block;
	पूर्णांक error;

	/*
	 * Diagnose required errors first.
	 */
	अगर (CPUCLOCK_PERTHREAD(which_घड़ी) &&
	    (CPUCLOCK_PID(which_घड़ी) == 0 ||
	     CPUCLOCK_PID(which_घड़ी) == task_pid_vnr(current)))
		वापस -EINVAL;

	error = करो_cpu_nanosleep(which_घड़ी, flags, rqtp);

	अगर (error == -ERESTART_RESTARTBLOCK) अणु

		अगर (flags & TIMER_ABSTIME)
			वापस -ERESTARTNOHAND;

		restart_block->nanosleep.घड़ीid = which_घड़ी;
		set_restart_fn(restart_block, posix_cpu_nsleep_restart);
	पूर्ण
	वापस error;
पूर्ण

अटल दीर्घ posix_cpu_nsleep_restart(काष्ठा restart_block *restart_block)
अणु
	घड़ीid_t which_घड़ी = restart_block->nanosleep.घड़ीid;
	काष्ठा बारpec64 t;

	t = ns_to_बारpec64(restart_block->nanosleep.expires);

	वापस करो_cpu_nanosleep(which_घड़ी, TIMER_ABSTIME, &t);
पूर्ण

#घोषणा PROCESS_CLOCK	make_process_cpuघड़ी(0, CPUCLOCK_SCHED)
#घोषणा THREAD_CLOCK	make_thपढ़ो_cpuघड़ी(0, CPUCLOCK_SCHED)

अटल पूर्णांक process_cpu_घड़ी_getres(स्थिर घड़ीid_t which_घड़ी,
				    काष्ठा बारpec64 *tp)
अणु
	वापस posix_cpu_घड़ी_getres(PROCESS_CLOCK, tp);
पूर्ण
अटल पूर्णांक process_cpu_घड़ी_get(स्थिर घड़ीid_t which_घड़ी,
				 काष्ठा बारpec64 *tp)
अणु
	वापस posix_cpu_घड़ी_get(PROCESS_CLOCK, tp);
पूर्ण
अटल पूर्णांक process_cpu_समयr_create(काष्ठा k_iसमयr *समयr)
अणु
	समयr->it_घड़ी = PROCESS_CLOCK;
	वापस posix_cpu_समयr_create(समयr);
पूर्ण
अटल पूर्णांक process_cpu_nsleep(स्थिर घड़ीid_t which_घड़ी, पूर्णांक flags,
			      स्थिर काष्ठा बारpec64 *rqtp)
अणु
	वापस posix_cpu_nsleep(PROCESS_CLOCK, flags, rqtp);
पूर्ण
अटल पूर्णांक thपढ़ो_cpu_घड़ी_getres(स्थिर घड़ीid_t which_घड़ी,
				   काष्ठा बारpec64 *tp)
अणु
	वापस posix_cpu_घड़ी_getres(THREAD_CLOCK, tp);
पूर्ण
अटल पूर्णांक thपढ़ो_cpu_घड़ी_get(स्थिर घड़ीid_t which_घड़ी,
				काष्ठा बारpec64 *tp)
अणु
	वापस posix_cpu_घड़ी_get(THREAD_CLOCK, tp);
पूर्ण
अटल पूर्णांक thपढ़ो_cpu_समयr_create(काष्ठा k_iसमयr *समयr)
अणु
	समयr->it_घड़ी = THREAD_CLOCK;
	वापस posix_cpu_समयr_create(समयr);
पूर्ण

स्थिर काष्ठा k_घड़ी घड़ी_posix_cpu = अणु
	.घड़ी_getres		= posix_cpu_घड़ी_getres,
	.घड़ी_set		= posix_cpu_घड़ी_set,
	.घड़ी_get_बारpec	= posix_cpu_घड़ी_get,
	.समयr_create		= posix_cpu_समयr_create,
	.nsleep			= posix_cpu_nsleep,
	.समयr_set		= posix_cpu_समयr_set,
	.समयr_del		= posix_cpu_समयr_del,
	.समयr_get		= posix_cpu_समयr_get,
	.समयr_rearm		= posix_cpu_समयr_rearm,
पूर्ण;

स्थिर काष्ठा k_घड़ी घड़ी_process = अणु
	.घड़ी_getres		= process_cpu_घड़ी_getres,
	.घड़ी_get_बारpec	= process_cpu_घड़ी_get,
	.समयr_create		= process_cpu_समयr_create,
	.nsleep			= process_cpu_nsleep,
पूर्ण;

स्थिर काष्ठा k_घड़ी घड़ी_प्रकारhपढ़ो = अणु
	.घड़ी_getres		= thपढ़ो_cpu_घड़ी_getres,
	.घड़ी_get_बारpec	= thपढ़ो_cpu_घड़ी_get,
	.समयr_create		= thपढ़ो_cpu_समयr_create,
पूर्ण;
