<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_घोषित CONFIG_SCHEDSTATS

/*
 * Expects runqueue lock to be held क्रम atomicity of update
 */
अटल अंतरभूत व्योम
rq_sched_info_arrive(काष्ठा rq *rq, अचिन्हित दीर्घ दीर्घ delta)
अणु
	अगर (rq) अणु
		rq->rq_sched_info.run_delay += delta;
		rq->rq_sched_info.pcount++;
	पूर्ण
पूर्ण

/*
 * Expects runqueue lock to be held क्रम atomicity of update
 */
अटल अंतरभूत व्योम
rq_sched_info_depart(काष्ठा rq *rq, अचिन्हित दीर्घ दीर्घ delta)
अणु
	अगर (rq)
		rq->rq_cpu_समय += delta;
पूर्ण

अटल अंतरभूत व्योम
rq_sched_info_dequeued(काष्ठा rq *rq, अचिन्हित दीर्घ दीर्घ delta)
अणु
	अगर (rq)
		rq->rq_sched_info.run_delay += delta;
पूर्ण
#घोषणा   schedstat_enabled()		अटल_branch_unlikely(&sched_schedstats)
#घोषणा __schedstat_inc(var)		करो अणु var++; पूर्ण जबतक (0)
#घोषणा   schedstat_inc(var)		करो अणु अगर (schedstat_enabled()) अणु var++; पूर्ण पूर्ण जबतक (0)
#घोषणा __schedstat_add(var, amt)	करो अणु var += (amt); पूर्ण जबतक (0)
#घोषणा   schedstat_add(var, amt)	करो अणु अगर (schedstat_enabled()) अणु var += (amt); पूर्ण पूर्ण जबतक (0)
#घोषणा __schedstat_set(var, val)	करो अणु var = (val); पूर्ण जबतक (0)
#घोषणा   schedstat_set(var, val)	करो अणु अगर (schedstat_enabled()) अणु var = (val); पूर्ण पूर्ण जबतक (0)
#घोषणा   schedstat_val(var)		(var)
#घोषणा   schedstat_val_or_zero(var)	((schedstat_enabled()) ? (var) : 0)

#अन्यथा /* !CONFIG_SCHEDSTATS: */
अटल अंतरभूत व्योम rq_sched_info_arrive  (काष्ठा rq *rq, अचिन्हित दीर्घ दीर्घ delta) अणु पूर्ण
अटल अंतरभूत व्योम rq_sched_info_dequeued(काष्ठा rq *rq, अचिन्हित दीर्घ दीर्घ delta) अणु पूर्ण
अटल अंतरभूत व्योम rq_sched_info_depart  (काष्ठा rq *rq, अचिन्हित दीर्घ दीर्घ delta) अणु पूर्ण
# define   schedstat_enabled()		0
# define __schedstat_inc(var)		करो अणु पूर्ण जबतक (0)
# define   schedstat_inc(var)		करो अणु पूर्ण जबतक (0)
# define __schedstat_add(var, amt)	करो अणु पूर्ण जबतक (0)
# define   schedstat_add(var, amt)	करो अणु पूर्ण जबतक (0)
# define __schedstat_set(var, val)	करो अणु पूर्ण जबतक (0)
# define   schedstat_set(var, val)	करो अणु पूर्ण जबतक (0)
# define   schedstat_val(var)		0
# define   schedstat_val_or_zero(var)	0
#पूर्ण_अगर /* CONFIG_SCHEDSTATS */

#अगर_घोषित CONFIG_PSI
/*
 * PSI tracks state that persists across sleeps, such as ioरुकोs and
 * memory stalls. As a result, it has to distinguish between sleeps,
 * where a task's runnable state changes, and requeues, where a task
 * and its state are being moved between CPUs and runqueues.
 */
अटल अंतरभूत व्योम psi_enqueue(काष्ठा task_काष्ठा *p, bool wakeup)
अणु
	पूर्णांक clear = 0, set = TSK_RUNNING;

	अगर (अटल_branch_likely(&psi_disabled))
		वापस;

	अगर (!wakeup || p->sched_psi_wake_requeue) अणु
		अगर (p->in_memstall)
			set |= TSK_MEMSTALL;
		अगर (p->sched_psi_wake_requeue)
			p->sched_psi_wake_requeue = 0;
	पूर्ण अन्यथा अणु
		अगर (p->in_ioरुको)
			clear |= TSK_IOWAIT;
	पूर्ण

	psi_task_change(p, clear, set);
पूर्ण

अटल अंतरभूत व्योम psi_dequeue(काष्ठा task_काष्ठा *p, bool sleep)
अणु
	पूर्णांक clear = TSK_RUNNING;

	अगर (अटल_branch_likely(&psi_disabled))
		वापस;

	/*
	 * A voluntary sleep is a dequeue followed by a task चयन. To
	 * aव्योम walking all ancestors twice, psi_task_चयन() handles
	 * TSK_RUNNING and TSK_IOWAIT क्रम us when it moves TSK_ONCPU.
	 * Do nothing here.
	 */
	अगर (sleep)
		वापस;

	अगर (p->in_memstall)
		clear |= TSK_MEMSTALL;

	psi_task_change(p, clear, 0);
पूर्ण

अटल अंतरभूत व्योम psi_ttwu_dequeue(काष्ठा task_काष्ठा *p)
अणु
	अगर (अटल_branch_likely(&psi_disabled))
		वापस;
	/*
	 * Is the task being migrated during a wakeup? Make sure to
	 * deरेजिस्टर its sleep-persistent psi states from the old
	 * queue, and let psi_enqueue() know it has to requeue.
	 */
	अगर (unlikely(p->in_ioरुको || p->in_memstall)) अणु
		काष्ठा rq_flags rf;
		काष्ठा rq *rq;
		पूर्णांक clear = 0;

		अगर (p->in_ioरुको)
			clear |= TSK_IOWAIT;
		अगर (p->in_memstall)
			clear |= TSK_MEMSTALL;

		rq = __task_rq_lock(p, &rf);
		psi_task_change(p, clear, 0);
		p->sched_psi_wake_requeue = 1;
		__task_rq_unlock(rq, &rf);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम psi_sched_चयन(काष्ठा task_काष्ठा *prev,
				    काष्ठा task_काष्ठा *next,
				    bool sleep)
अणु
	अगर (अटल_branch_likely(&psi_disabled))
		वापस;

	psi_task_चयन(prev, next, sleep);
पूर्ण

#अन्यथा /* CONFIG_PSI */
अटल अंतरभूत व्योम psi_enqueue(काष्ठा task_काष्ठा *p, bool wakeup) अणुपूर्ण
अटल अंतरभूत व्योम psi_dequeue(काष्ठा task_काष्ठा *p, bool sleep) अणुपूर्ण
अटल अंतरभूत व्योम psi_ttwu_dequeue(काष्ठा task_काष्ठा *p) अणुपूर्ण
अटल अंतरभूत व्योम psi_sched_चयन(काष्ठा task_काष्ठा *prev,
				    काष्ठा task_काष्ठा *next,
				    bool sleep) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_PSI */

#अगर_घोषित CONFIG_SCHED_INFO
अटल अंतरभूत व्योम sched_info_reset_dequeued(काष्ठा task_काष्ठा *t)
अणु
	t->sched_info.last_queued = 0;
पूर्ण

/*
 * We are पूर्णांकerested in knowing how दीर्घ it was from the *first* समय a
 * task was queued to the समय that it finally hit a CPU, we call this routine
 * from dequeue_task() to account क्रम possible rq->घड़ी skew across CPUs. The
 * delta taken on each CPU would annul the skew.
 */
अटल अंतरभूत व्योम sched_info_dequeued(काष्ठा rq *rq, काष्ठा task_काष्ठा *t)
अणु
	अचिन्हित दीर्घ दीर्घ now = rq_घड़ी(rq), delta = 0;

	अगर (sched_info_on()) अणु
		अगर (t->sched_info.last_queued)
			delta = now - t->sched_info.last_queued;
	पूर्ण
	sched_info_reset_dequeued(t);
	t->sched_info.run_delay += delta;

	rq_sched_info_dequeued(rq, delta);
पूर्ण

/*
 * Called when a task finally hits the CPU.  We can now calculate how
 * दीर्घ it was रुकोing to run.  We also note when it began so that we
 * can keep stats on how दीर्घ its बारlice is.
 */
अटल व्योम sched_info_arrive(काष्ठा rq *rq, काष्ठा task_काष्ठा *t)
अणु
	अचिन्हित दीर्घ दीर्घ now = rq_घड़ी(rq), delta = 0;

	अगर (t->sched_info.last_queued)
		delta = now - t->sched_info.last_queued;
	sched_info_reset_dequeued(t);
	t->sched_info.run_delay += delta;
	t->sched_info.last_arrival = now;
	t->sched_info.pcount++;

	rq_sched_info_arrive(rq, delta);
पूर्ण

/*
 * This function is only called from enqueue_task(), but also only updates
 * the बारtamp अगर it is alपढ़ोy not set.  It's assumed that
 * sched_info_dequeued() will clear that stamp when appropriate.
 */
अटल अंतरभूत व्योम sched_info_queued(काष्ठा rq *rq, काष्ठा task_काष्ठा *t)
अणु
	अगर (sched_info_on()) अणु
		अगर (!t->sched_info.last_queued)
			t->sched_info.last_queued = rq_घड़ी(rq);
	पूर्ण
पूर्ण

/*
 * Called when a process ceases being the active-running process involuntarily
 * due, typically, to expiring its समय slice (this may also be called when
 * चयनing to the idle task).  Now we can calculate how दीर्घ we ran.
 * Also, अगर the process is still in the TASK_RUNNING state, call
 * sched_info_queued() to mark that it has now again started रुकोing on
 * the runqueue.
 */
अटल अंतरभूत व्योम sched_info_depart(काष्ठा rq *rq, काष्ठा task_काष्ठा *t)
अणु
	अचिन्हित दीर्घ दीर्घ delta = rq_घड़ी(rq) - t->sched_info.last_arrival;

	rq_sched_info_depart(rq, delta);

	अगर (t->state == TASK_RUNNING)
		sched_info_queued(rq, t);
पूर्ण

/*
 * Called when tasks are चयनed involuntarily due, typically, to expiring
 * their समय slice.  (This may also be called when चयनing to or from
 * the idle task.)  We are only called when prev != next.
 */
अटल अंतरभूत व्योम
__sched_info_चयन(काष्ठा rq *rq, काष्ठा task_काष्ठा *prev, काष्ठा task_काष्ठा *next)
अणु
	/*
	 * prev now departs the CPU.  It's not पूर्णांकeresting to record
	 * stats about how efficient we were at scheduling the idle
	 * process, however.
	 */
	अगर (prev != rq->idle)
		sched_info_depart(rq, prev);

	अगर (next != rq->idle)
		sched_info_arrive(rq, next);
पूर्ण

अटल अंतरभूत व्योम
sched_info_चयन(काष्ठा rq *rq, काष्ठा task_काष्ठा *prev, काष्ठा task_काष्ठा *next)
अणु
	अगर (sched_info_on())
		__sched_info_चयन(rq, prev, next);
पूर्ण

#अन्यथा /* !CONFIG_SCHED_INFO: */
# define sched_info_queued(rq, t)	करो अणु पूर्ण जबतक (0)
# define sched_info_reset_dequeued(t)	करो अणु पूर्ण जबतक (0)
# define sched_info_dequeued(rq, t)	करो अणु पूर्ण जबतक (0)
# define sched_info_depart(rq, t)	करो अणु पूर्ण जबतक (0)
# define sched_info_arrive(rq, next)	करो अणु पूर्ण जबतक (0)
# define sched_info_चयन(rq, t, next)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर /* CONFIG_SCHED_INFO */
