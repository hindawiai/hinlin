<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/atomic.h>
#समावेश <linux/percpu.h>
#समावेश <linux/रुको.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/percpu-rwsem.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/त्रुटिसं.स>

पूर्णांक __percpu_init_rwsem(काष्ठा percpu_rw_semaphore *sem,
			स्थिर अक्षर *name, काष्ठा lock_class_key *key)
अणु
	sem->पढ़ो_count = alloc_percpu(पूर्णांक);
	अगर (unlikely(!sem->पढ़ो_count))
		वापस -ENOMEM;

	rcu_sync_init(&sem->rss);
	rcuरुको_init(&sem->ग_लिखोr);
	init_रुकोqueue_head(&sem->रुकोers);
	atomic_set(&sem->block, 0);
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	debug_check_no_locks_मुक्तd((व्योम *)sem, माप(*sem));
	lockdep_init_map(&sem->dep_map, name, key, 0);
#पूर्ण_अगर
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__percpu_init_rwsem);

व्योम percpu_मुक्त_rwsem(काष्ठा percpu_rw_semaphore *sem)
अणु
	/*
	 * XXX: temporary kludge. The error path in alloc_super()
	 * assumes that percpu_मुक्त_rwsem() is safe after kzalloc().
	 */
	अगर (!sem->पढ़ो_count)
		वापस;

	rcu_sync_dtor(&sem->rss);
	मुक्त_percpu(sem->पढ़ो_count);
	sem->पढ़ो_count = शून्य; /* catch use after मुक्त bugs */
पूर्ण
EXPORT_SYMBOL_GPL(percpu_मुक्त_rwsem);

अटल bool __percpu_करोwn_पढ़ो_trylock(काष्ठा percpu_rw_semaphore *sem)
अणु
	this_cpu_inc(*sem->पढ़ो_count);

	/*
	 * Due to having preemption disabled the decrement happens on
	 * the same CPU as the increment, aव्योमing the
	 * increment-on-one-CPU-and-decrement-on-another problem.
	 *
	 * If the पढ़ोer misses the ग_लिखोr's assignment of sem->block, then the
	 * ग_लिखोr is guaranteed to see the पढ़ोer's increment.
	 *
	 * Conversely, any पढ़ोers that increment their sem->पढ़ो_count after
	 * the ग_लिखोr looks are guaranteed to see the sem->block value, which
	 * in turn means that they are guaranteed to immediately decrement
	 * their sem->पढ़ो_count, so that it करोesn't matter that the ग_लिखोr
	 * missed them.
	 */

	smp_mb(); /* A matches D */

	/*
	 * If !sem->block the critical section starts here, matched by the
	 * release in percpu_up_ग_लिखो().
	 */
	अगर (likely(!atomic_पढ़ो_acquire(&sem->block)))
		वापस true;

	this_cpu_dec(*sem->पढ़ो_count);

	/* Prod ग_लिखोr to re-evaluate पढ़ोers_active_check() */
	rcuरुको_wake_up(&sem->ग_लिखोr);

	वापस false;
पूर्ण

अटल अंतरभूत bool __percpu_करोwn_ग_लिखो_trylock(काष्ठा percpu_rw_semaphore *sem)
अणु
	अगर (atomic_पढ़ो(&sem->block))
		वापस false;

	वापस atomic_xchg(&sem->block, 1) == 0;
पूर्ण

अटल bool __percpu_rwsem_trylock(काष्ठा percpu_rw_semaphore *sem, bool पढ़ोer)
अणु
	अगर (पढ़ोer) अणु
		bool ret;

		preempt_disable();
		ret = __percpu_करोwn_पढ़ो_trylock(sem);
		preempt_enable();

		वापस ret;
	पूर्ण
	वापस __percpu_करोwn_ग_लिखो_trylock(sem);
पूर्ण

/*
 * The वापस value of रुको_queue_entry::func means:
 *
 *  <0 - error, wakeup is terminated and the error is वापसed
 *   0 - no wakeup, a next रुकोer is tried
 *  >0 - woken, अगर EXCLUSIVE, counted towards @nr_exclusive.
 *
 * We use EXCLUSIVE क्रम both पढ़ोers and ग_लिखोrs to preserve FIFO order,
 * and play games with the वापस value to allow waking multiple पढ़ोers.
 *
 * Specअगरically, we wake पढ़ोers until we've woken a single ग_लिखोr, or until a
 * trylock fails.
 */
अटल पूर्णांक percpu_rwsem_wake_function(काष्ठा रुको_queue_entry *wq_entry,
				      अचिन्हित पूर्णांक mode, पूर्णांक wake_flags,
				      व्योम *key)
अणु
	bool पढ़ोer = wq_entry->flags & WQ_FLAG_CUSTOM;
	काष्ठा percpu_rw_semaphore *sem = key;
	काष्ठा task_काष्ठा *p;

	/* concurrent against percpu_करोwn_ग_लिखो(), can get stolen */
	अगर (!__percpu_rwsem_trylock(sem, पढ़ोer))
		वापस 1;

	p = get_task_काष्ठा(wq_entry->निजी);
	list_del_init(&wq_entry->entry);
	smp_store_release(&wq_entry->निजी, शून्य);

	wake_up_process(p);
	put_task_काष्ठा(p);

	वापस !पढ़ोer; /* wake (पढ़ोers until) 1 ग_लिखोr */
पूर्ण

अटल व्योम percpu_rwsem_रुको(काष्ठा percpu_rw_semaphore *sem, bool पढ़ोer)
अणु
	DEFINE_WAIT_FUNC(wq_entry, percpu_rwsem_wake_function);
	bool रुको;

	spin_lock_irq(&sem->रुकोers.lock);
	/*
	 * Serialize against the wakeup in percpu_up_ग_लिखो(), अगर we fail
	 * the trylock, the wakeup must see us on the list.
	 */
	रुको = !__percpu_rwsem_trylock(sem, पढ़ोer);
	अगर (रुको) अणु
		wq_entry.flags |= WQ_FLAG_EXCLUSIVE | पढ़ोer * WQ_FLAG_CUSTOM;
		__add_रुको_queue_entry_tail(&sem->रुकोers, &wq_entry);
	पूर्ण
	spin_unlock_irq(&sem->रुकोers.lock);

	जबतक (रुको) अणु
		set_current_state(TASK_UNINTERRUPTIBLE);
		अगर (!smp_load_acquire(&wq_entry.निजी))
			अवरोध;
		schedule();
	पूर्ण
	__set_current_state(TASK_RUNNING);
पूर्ण

bool __percpu_करोwn_पढ़ो(काष्ठा percpu_rw_semaphore *sem, bool try)
अणु
	अगर (__percpu_करोwn_पढ़ो_trylock(sem))
		वापस true;

	अगर (try)
		वापस false;

	preempt_enable();
	percpu_rwsem_रुको(sem, /* .पढ़ोer = */ true);
	preempt_disable();

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(__percpu_करोwn_पढ़ो);

#घोषणा per_cpu_sum(var)						\
(अणु									\
	typeof(var) __sum = 0;						\
	पूर्णांक cpu;							\
	compileसमय_निश्चित_atomic_type(__sum);				\
	क्रम_each_possible_cpu(cpu)					\
		__sum += per_cpu(var, cpu);				\
	__sum;								\
पूर्ण)

/*
 * Return true अगर the modular sum of the sem->पढ़ो_count per-CPU variable is
 * zero.  If this sum is zero, then it is stable due to the fact that अगर any
 * newly arriving पढ़ोers increment a given counter, they will immediately
 * decrement that same counter.
 *
 * Assumes sem->block is set.
 */
अटल bool पढ़ोers_active_check(काष्ठा percpu_rw_semaphore *sem)
अणु
	अगर (per_cpu_sum(*sem->पढ़ो_count) != 0)
		वापस false;

	/*
	 * If we observed the decrement; ensure we see the entire critical
	 * section.
	 */

	smp_mb(); /* C matches B */

	वापस true;
पूर्ण

व्योम percpu_करोwn_ग_लिखो(काष्ठा percpu_rw_semaphore *sem)
अणु
	might_sleep();
	rwsem_acquire(&sem->dep_map, 0, 0, _RET_IP_);

	/* Notअगरy पढ़ोers to take the slow path. */
	rcu_sync_enter(&sem->rss);

	/*
	 * Try set sem->block; this provides ग_लिखोr-ग_लिखोr exclusion.
	 * Having sem->block set makes new पढ़ोers block.
	 */
	अगर (!__percpu_करोwn_ग_लिखो_trylock(sem))
		percpu_rwsem_रुको(sem, /* .पढ़ोer = */ false);

	/* smp_mb() implied by __percpu_करोwn_ग_लिखो_trylock() on success -- D matches A */

	/*
	 * If they करोn't see our store of sem->block, then we are guaranteed to
	 * see their sem->पढ़ो_count increment, and thereक्रमe will रुको क्रम
	 * them.
	 */

	/* Wait क्रम all active पढ़ोers to complete. */
	rcuरुको_रुको_event(&sem->ग_लिखोr, पढ़ोers_active_check(sem), TASK_UNINTERRUPTIBLE);
पूर्ण
EXPORT_SYMBOL_GPL(percpu_करोwn_ग_लिखो);

व्योम percpu_up_ग_लिखो(काष्ठा percpu_rw_semaphore *sem)
अणु
	rwsem_release(&sem->dep_map, _RET_IP_);

	/*
	 * Signal the ग_लिखोr is करोne, no fast path yet.
	 *
	 * One reason that we cannot just immediately flip to पढ़ोers_fast is
	 * that new पढ़ोers might fail to see the results of this ग_लिखोr's
	 * critical section.
	 *
	 * Thereक्रमe we क्रमce it through the slow path which guarantees an
	 * acquire and thereby guarantees the critical section's consistency.
	 */
	atomic_set_release(&sem->block, 0);

	/*
	 * Prod any pending पढ़ोer/ग_लिखोr to make progress.
	 */
	__wake_up(&sem->रुकोers, TASK_NORMAL, 1, sem);

	/*
	 * Once this completes (at least one RCU-sched grace period hence) the
	 * पढ़ोer fast path will be available again. Safe to use outside the
	 * exclusive ग_लिखो lock because its counting.
	 */
	rcu_sync_निकास(&sem->rss);
पूर्ण
EXPORT_SYMBOL_GPL(percpu_up_ग_लिखो);
