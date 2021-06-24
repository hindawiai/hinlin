<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * RT-Mutexes: simple blocking mutual exclusion locks with PI support
 *
 * started by Ingo Molnar and Thomas Gleixner.
 *
 *  Copyright (C) 2004-2006 Red Hat, Inc., Ingo Molnar <mingo@redhat.com>
 *  Copyright (C) 2005-2006 Timesys Corp., Thomas Gleixner <tglx@बारys.com>
 *  Copyright (C) 2005 Kihon Technologies Inc., Steven Rostedt
 *  Copyright (C) 2006 Esben Niअन्यथाn
 *
 *  See Documentation/locking/rt-mutex-design.rst क्रम details.
 */
#समावेश <linux/spinlock.h>
#समावेश <linux/export.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/rt.h>
#समावेश <linux/sched/deadline.h>
#समावेश <linux/sched/wake_q.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/समयr.h>

#समावेश "rtmutex_common.h"

/*
 * lock->owner state tracking:
 *
 * lock->owner holds the task_काष्ठा poपूर्णांकer of the owner. Bit 0
 * is used to keep track of the "lock has waiters" state.
 *
 * owner	bit0
 * शून्य		0	lock is मुक्त (fast acquire possible)
 * शून्य		1	lock is मुक्त and has रुकोers and the top रुकोer
 *				is going to take the lock*
 * taskpoपूर्णांकer	0	lock is held (fast release possible)
 * taskpoपूर्णांकer	1	lock is held and has रुकोers**
 *
 * The fast atomic compare exchange based acquire and release is only
 * possible when bit 0 of lock->owner is 0.
 *
 * (*) It also can be a transitional state when grabbing the lock
 * with ->रुको_lock is held. To prevent any fast path cmpxchg to the lock,
 * we need to set the bit0 beक्रमe looking at the lock, and the owner may be
 * शून्य in this small समय, hence this can be a transitional state.
 *
 * (**) There is a small समय when bit 0 is set but there are no
 * रुकोers. This can happen when grabbing the lock in the slow path.
 * To prevent a cmpxchg of the owner releasing the lock, we need to
 * set this bit beक्रमe looking at the lock.
 */

अटल __always_अंतरभूत व्योम
rt_mutex_set_owner(काष्ठा rt_mutex *lock, काष्ठा task_काष्ठा *owner)
अणु
	अचिन्हित दीर्घ val = (अचिन्हित दीर्घ)owner;

	अगर (rt_mutex_has_रुकोers(lock))
		val |= RT_MUTEX_HAS_WAITERS;

	WRITE_ONCE(lock->owner, (काष्ठा task_काष्ठा *)val);
पूर्ण

अटल __always_अंतरभूत व्योम clear_rt_mutex_रुकोers(काष्ठा rt_mutex *lock)
अणु
	lock->owner = (काष्ठा task_काष्ठा *)
			((अचिन्हित दीर्घ)lock->owner & ~RT_MUTEX_HAS_WAITERS);
पूर्ण

अटल __always_अंतरभूत व्योम fixup_rt_mutex_रुकोers(काष्ठा rt_mutex *lock)
अणु
	अचिन्हित दीर्घ owner, *p = (अचिन्हित दीर्घ *) &lock->owner;

	अगर (rt_mutex_has_रुकोers(lock))
		वापस;

	/*
	 * The rbtree has no रुकोers enqueued, now make sure that the
	 * lock->owner still has the रुकोers bit set, otherwise the
	 * following can happen:
	 *
	 * CPU 0	CPU 1		CPU2
	 * l->owner=T1
	 *		rt_mutex_lock(l)
	 *		lock(l->lock)
	 *		l->owner = T1 | HAS_WAITERS;
	 *		enqueue(T2)
	 *		boost()
	 *		  unlock(l->lock)
	 *		block()
	 *
	 *				rt_mutex_lock(l)
	 *				lock(l->lock)
	 *				l->owner = T1 | HAS_WAITERS;
	 *				enqueue(T3)
	 *				boost()
	 *				  unlock(l->lock)
	 *				block()
	 *		संकेत(->T2)	संकेत(->T3)
	 *		lock(l->lock)
	 *		dequeue(T2)
	 *		deboost()
	 *		  unlock(l->lock)
	 *				lock(l->lock)
	 *				dequeue(T3)
	 *				 ==> रुको list is empty
	 *				deboost()
	 *				 unlock(l->lock)
	 *		lock(l->lock)
	 *		fixup_rt_mutex_रुकोers()
	 *		  अगर (रुको_list_empty(l) अणु
	 *		    l->owner = owner
	 *		    owner = l->owner & ~HAS_WAITERS;
	 *		      ==> l->owner = T1
	 *		  पूर्ण
	 *				lock(l->lock)
	 * rt_mutex_unlock(l)		fixup_rt_mutex_रुकोers()
	 *				  अगर (रुको_list_empty(l) अणु
	 *				    owner = l->owner & ~HAS_WAITERS;
	 * cmpxchg(l->owner, T1, शून्य)
	 *  ===> Success (l->owner = शून्य)
	 *
	 *				    l->owner = owner
	 *				      ==> l->owner = T1
	 *				  पूर्ण
	 *
	 * With the check क्रम the रुकोer bit in place T3 on CPU2 will not
	 * overग_लिखो. All tasks fiddling with the रुकोers bit are
	 * serialized by l->lock, so nothing अन्यथा can modअगरy the रुकोers
	 * bit. If the bit is set then nothing can change l->owner either
	 * so the simple RMW is safe. The cmpxchg() will simply fail अगर it
	 * happens in the middle of the RMW because the रुकोers bit is
	 * still set.
	 */
	owner = READ_ONCE(*p);
	अगर (owner & RT_MUTEX_HAS_WAITERS)
		WRITE_ONCE(*p, owner & ~RT_MUTEX_HAS_WAITERS);
पूर्ण

/*
 * We can speed up the acquire/release, अगर there's no debugging state to be
 * set up.
 */
#अगर_अघोषित CONFIG_DEBUG_RT_MUTEXES
# define rt_mutex_cmpxchg_acquire(l,c,n) (cmpxchg_acquire(&l->owner, c, n) == c)
# define rt_mutex_cmpxchg_release(l,c,n) (cmpxchg_release(&l->owner, c, n) == c)

/*
 * Callers must hold the ->रुको_lock -- which is the whole purpose as we क्रमce
 * all future thपढ़ोs that attempt to [Rmw] the lock to the slowpath. As such
 * relaxed semantics suffice.
 */
अटल __always_अंतरभूत व्योम mark_rt_mutex_रुकोers(काष्ठा rt_mutex *lock)
अणु
	अचिन्हित दीर्घ owner, *p = (अचिन्हित दीर्घ *) &lock->owner;

	करो अणु
		owner = *p;
	पूर्ण जबतक (cmpxchg_relaxed(p, owner,
				 owner | RT_MUTEX_HAS_WAITERS) != owner);
पूर्ण

/*
 * Safe fastpath aware unlock:
 * 1) Clear the रुकोers bit
 * 2) Drop lock->रुको_lock
 * 3) Try to unlock the lock with cmpxchg
 */
अटल __always_अंतरभूत bool unlock_rt_mutex_safe(काष्ठा rt_mutex *lock,
						 अचिन्हित दीर्घ flags)
	__releases(lock->रुको_lock)
अणु
	काष्ठा task_काष्ठा *owner = rt_mutex_owner(lock);

	clear_rt_mutex_रुकोers(lock);
	raw_spin_unlock_irqrestore(&lock->रुको_lock, flags);
	/*
	 * If a new रुकोer comes in between the unlock and the cmpxchg
	 * we have two situations:
	 *
	 * unlock(रुको_lock);
	 *					lock(रुको_lock);
	 * cmpxchg(p, owner, 0) == owner
	 *					mark_rt_mutex_रुकोers(lock);
	 *					acquire(lock);
	 * or:
	 *
	 * unlock(रुको_lock);
	 *					lock(रुको_lock);
	 *					mark_rt_mutex_रुकोers(lock);
	 *
	 * cmpxchg(p, owner, 0) != owner
	 *					enqueue_रुकोer();
	 *					unlock(रुको_lock);
	 * lock(रुको_lock);
	 * wake रुकोer();
	 * unlock(रुको_lock);
	 *					lock(रुको_lock);
	 *					acquire(lock);
	 */
	वापस rt_mutex_cmpxchg_release(lock, owner, शून्य);
पूर्ण

#अन्यथा
# define rt_mutex_cmpxchg_acquire(l,c,n)	(0)
# define rt_mutex_cmpxchg_release(l,c,n)	(0)

अटल __always_अंतरभूत व्योम mark_rt_mutex_रुकोers(काष्ठा rt_mutex *lock)
अणु
	lock->owner = (काष्ठा task_काष्ठा *)
			((अचिन्हित दीर्घ)lock->owner | RT_MUTEX_HAS_WAITERS);
पूर्ण

/*
 * Simple slow path only version: lock->owner is रक्षित by lock->रुको_lock.
 */
अटल __always_अंतरभूत bool unlock_rt_mutex_safe(काष्ठा rt_mutex *lock,
						 अचिन्हित दीर्घ flags)
	__releases(lock->रुको_lock)
अणु
	lock->owner = शून्य;
	raw_spin_unlock_irqrestore(&lock->रुको_lock, flags);
	वापस true;
पूर्ण
#पूर्ण_अगर

/*
 * Only use with rt_mutex_रुकोer_अणुless,equalपूर्ण()
 */
#घोषणा task_to_रुकोer(p)	\
	&(काष्ठा rt_mutex_रुकोer)अणु .prio = (p)->prio, .deadline = (p)->dl.deadline पूर्ण

अटल __always_अंतरभूत पूर्णांक rt_mutex_रुकोer_less(काष्ठा rt_mutex_रुकोer *left,
						काष्ठा rt_mutex_रुकोer *right)
अणु
	अगर (left->prio < right->prio)
		वापस 1;

	/*
	 * If both रुकोers have dl_prio(), we check the deadlines of the
	 * associated tasks.
	 * If left रुकोer has a dl_prio(), and we didn't वापस 1 above,
	 * then right रुकोer has a dl_prio() too.
	 */
	अगर (dl_prio(left->prio))
		वापस dl_समय_beक्रमe(left->deadline, right->deadline);

	वापस 0;
पूर्ण

अटल __always_अंतरभूत पूर्णांक rt_mutex_रुकोer_equal(काष्ठा rt_mutex_रुकोer *left,
						 काष्ठा rt_mutex_रुकोer *right)
अणु
	अगर (left->prio != right->prio)
		वापस 0;

	/*
	 * If both रुकोers have dl_prio(), we check the deadlines of the
	 * associated tasks.
	 * If left रुकोer has a dl_prio(), and we didn't वापस 0 above,
	 * then right रुकोer has a dl_prio() too.
	 */
	अगर (dl_prio(left->prio))
		वापस left->deadline == right->deadline;

	वापस 1;
पूर्ण

#घोषणा __node_2_रुकोer(node) \
	rb_entry((node), काष्ठा rt_mutex_रुकोer, tree_entry)

अटल __always_अंतरभूत bool __रुकोer_less(काष्ठा rb_node *a, स्थिर काष्ठा rb_node *b)
अणु
	वापस rt_mutex_रुकोer_less(__node_2_रुकोer(a), __node_2_रुकोer(b));
पूर्ण

अटल __always_अंतरभूत व्योम
rt_mutex_enqueue(काष्ठा rt_mutex *lock, काष्ठा rt_mutex_रुकोer *रुकोer)
अणु
	rb_add_cached(&रुकोer->tree_entry, &lock->रुकोers, __रुकोer_less);
पूर्ण

अटल __always_अंतरभूत व्योम
rt_mutex_dequeue(काष्ठा rt_mutex *lock, काष्ठा rt_mutex_रुकोer *रुकोer)
अणु
	अगर (RB_EMPTY_NODE(&रुकोer->tree_entry))
		वापस;

	rb_erase_cached(&रुकोer->tree_entry, &lock->रुकोers);
	RB_CLEAR_NODE(&रुकोer->tree_entry);
पूर्ण

#घोषणा __node_2_pi_रुकोer(node) \
	rb_entry((node), काष्ठा rt_mutex_रुकोer, pi_tree_entry)

अटल __always_अंतरभूत bool
__pi_रुकोer_less(काष्ठा rb_node *a, स्थिर काष्ठा rb_node *b)
अणु
	वापस rt_mutex_रुकोer_less(__node_2_pi_रुकोer(a), __node_2_pi_रुकोer(b));
पूर्ण

अटल __always_अंतरभूत व्योम
rt_mutex_enqueue_pi(काष्ठा task_काष्ठा *task, काष्ठा rt_mutex_रुकोer *रुकोer)
अणु
	rb_add_cached(&रुकोer->pi_tree_entry, &task->pi_रुकोers, __pi_रुकोer_less);
पूर्ण

अटल __always_अंतरभूत व्योम
rt_mutex_dequeue_pi(काष्ठा task_काष्ठा *task, काष्ठा rt_mutex_रुकोer *रुकोer)
अणु
	अगर (RB_EMPTY_NODE(&रुकोer->pi_tree_entry))
		वापस;

	rb_erase_cached(&रुकोer->pi_tree_entry, &task->pi_रुकोers);
	RB_CLEAR_NODE(&रुकोer->pi_tree_entry);
पूर्ण

अटल __always_अंतरभूत व्योम rt_mutex_adjust_prio(काष्ठा task_काष्ठा *p)
अणु
	काष्ठा task_काष्ठा *pi_task = शून्य;

	lockdep_निश्चित_held(&p->pi_lock);

	अगर (task_has_pi_रुकोers(p))
		pi_task = task_top_pi_रुकोer(p)->task;

	rt_mutex_setprio(p, pi_task);
पूर्ण

/*
 * Deadlock detection is conditional:
 *
 * If CONFIG_DEBUG_RT_MUTEXES=n, deadlock detection is only conducted
 * अगर the detect argument is == RT_MUTEX_FULL_CHAINWALK.
 *
 * If CONFIG_DEBUG_RT_MUTEXES=y, deadlock detection is always
 * conducted independent of the detect argument.
 *
 * If the रुकोer argument is शून्य this indicates the deboost path and
 * deadlock detection is disabled independent of the detect argument
 * and the config settings.
 */
अटल __always_अंतरभूत bool
rt_mutex_cond_detect_deadlock(काष्ठा rt_mutex_रुकोer *रुकोer,
			      क्रमागत rपंचांगutex_chainwalk chwalk)
अणु
	अगर (IS_ENABLED(CONFIG_DEBUG_RT_MUTEX))
		वापस रुकोer != शून्य;
	वापस chwalk == RT_MUTEX_FULL_CHAINWALK;
पूर्ण

/*
 * Max number of बार we'll walk the boosting chain:
 */
पूर्णांक max_lock_depth = 1024;

अटल __always_अंतरभूत काष्ठा rt_mutex *task_blocked_on_lock(काष्ठा task_काष्ठा *p)
अणु
	वापस p->pi_blocked_on ? p->pi_blocked_on->lock : शून्य;
पूर्ण

/*
 * Adjust the priority chain. Also used क्रम deadlock detection.
 * Decreases task's usage by one - may thus मुक्त the task.
 *
 * @task:	the task owning the mutex (owner) क्रम which a chain walk is
 *		probably needed
 * @chwalk:	करो we have to carry out deadlock detection?
 * @orig_lock:	the mutex (can be शून्य अगर we are walking the chain to recheck
 *		things क्रम a task that has just got its priority adjusted, and
 *		is रुकोing on a mutex)
 * @next_lock:	the mutex on which the owner of @orig_lock was blocked beक्रमe
 *		we dropped its pi_lock. Is never dereferenced, only used क्रम
 *		comparison to detect lock chain changes.
 * @orig_रुकोer: rt_mutex_रुकोer काष्ठा क्रम the task that has just करोnated
 *		its priority to the mutex owner (can be शून्य in the हाल
 *		depicted above or अगर the top रुकोer is gone away and we are
 *		actually deboosting the owner)
 * @top_task:	the current top रुकोer
 *
 * Returns 0 or -EDEADLK.
 *
 * Chain walk basics and protection scope
 *
 * [R] refcount on task
 * [P] task->pi_lock held
 * [L] rपंचांगutex->रुको_lock held
 *
 * Step	Description				Protected by
 *	function arguments:
 *	@task					[R]
 *	@orig_lock अगर != शून्य			@top_task is blocked on it
 *	@next_lock				Unरक्षित. Cannot be
 *						dereferenced. Only used क्रम
 *						comparison.
 *	@orig_रुकोer अगर != शून्य			@top_task is blocked on it
 *	@top_task				current, or in हाल of proxy
 *						locking रक्षित by calling
 *						code
 *	again:
 *	  loop_sanity_check();
 *	retry:
 * [1]	  lock(task->pi_lock);			[R] acquire [P]
 * [2]	  रुकोer = task->pi_blocked_on;		[P]
 * [3]	  check_निकास_conditions_1();		[P]
 * [4]	  lock = रुकोer->lock;			[P]
 * [5]	  अगर (!try_lock(lock->रुको_lock)) अणु	[P] try to acquire [L]
 *	    unlock(task->pi_lock);		release [P]
 *	    जाओ retry;
 *	  पूर्ण
 * [6]	  check_निकास_conditions_2();		[P] + [L]
 * [7]	  requeue_lock_रुकोer(lock, रुकोer);	[P] + [L]
 * [8]	  unlock(task->pi_lock);		release [P]
 *	  put_task_काष्ठा(task);		release [R]
 * [9]	  check_निकास_conditions_3();		[L]
 * [10]	  task = owner(lock);			[L]
 *	  get_task_काष्ठा(task);		[L] acquire [R]
 *	  lock(task->pi_lock);			[L] acquire [P]
 * [11]	  requeue_pi_रुकोer(tsk, रुकोers(lock));[P] + [L]
 * [12]	  check_निकास_conditions_4();		[P] + [L]
 * [13]	  unlock(task->pi_lock);		release [P]
 *	  unlock(lock->रुको_lock);		release [L]
 *	  जाओ again;
 */
अटल पूर्णांक __sched rt_mutex_adjust_prio_chain(काष्ठा task_काष्ठा *task,
					      क्रमागत rपंचांगutex_chainwalk chwalk,
					      काष्ठा rt_mutex *orig_lock,
					      काष्ठा rt_mutex *next_lock,
					      काष्ठा rt_mutex_रुकोer *orig_रुकोer,
					      काष्ठा task_काष्ठा *top_task)
अणु
	काष्ठा rt_mutex_रुकोer *रुकोer, *top_रुकोer = orig_रुकोer;
	काष्ठा rt_mutex_रुकोer *prerequeue_top_रुकोer;
	पूर्णांक ret = 0, depth = 0;
	काष्ठा rt_mutex *lock;
	bool detect_deadlock;
	bool requeue = true;

	detect_deadlock = rt_mutex_cond_detect_deadlock(orig_रुकोer, chwalk);

	/*
	 * The (de)boosting is a step by step approach with a lot of
	 * pitfalls. We want this to be preemptible and we want hold a
	 * maximum of two locks per step. So we have to check
	 * carefully whether things change under us.
	 */
 again:
	/*
	 * We limit the lock chain length क्रम each invocation.
	 */
	अगर (++depth > max_lock_depth) अणु
		अटल पूर्णांक prev_max;

		/*
		 * Prपूर्णांक this only once. If the admin changes the limit,
		 * prपूर्णांक a new message when reaching the limit again.
		 */
		अगर (prev_max != max_lock_depth) अणु
			prev_max = max_lock_depth;
			prपूर्णांकk(KERN_WARNING "Maximum lock depth %d reached "
			       "task: %s (%d)\n", max_lock_depth,
			       top_task->comm, task_pid_nr(top_task));
		पूर्ण
		put_task_काष्ठा(task);

		वापस -EDEADLK;
	पूर्ण

	/*
	 * We are fully preemptible here and only hold the refcount on
	 * @task. So everything can have changed under us since the
	 * caller or our own code below (जाओ retry/again) dropped all
	 * locks.
	 */
 retry:
	/*
	 * [1] Task cannot go away as we did a get_task() beक्रमe !
	 */
	raw_spin_lock_irq(&task->pi_lock);

	/*
	 * [2] Get the रुकोer on which @task is blocked on.
	 */
	रुकोer = task->pi_blocked_on;

	/*
	 * [3] check_निकास_conditions_1() रक्षित by task->pi_lock.
	 */

	/*
	 * Check whether the end of the boosting chain has been
	 * reached or the state of the chain has changed जबतक we
	 * dropped the locks.
	 */
	अगर (!रुकोer)
		जाओ out_unlock_pi;

	/*
	 * Check the orig_रुकोer state. After we dropped the locks,
	 * the previous owner of the lock might have released the lock.
	 */
	अगर (orig_रुकोer && !rt_mutex_owner(orig_lock))
		जाओ out_unlock_pi;

	/*
	 * We dropped all locks after taking a refcount on @task, so
	 * the task might have moved on in the lock chain or even left
	 * the chain completely and blocks now on an unrelated lock or
	 * on @orig_lock.
	 *
	 * We stored the lock on which @task was blocked in @next_lock,
	 * so we can detect the chain change.
	 */
	अगर (next_lock != रुकोer->lock)
		जाओ out_unlock_pi;

	/*
	 * Drop out, when the task has no रुकोers. Note,
	 * top_रुकोer can be शून्य, when we are in the deboosting
	 * mode!
	 */
	अगर (top_रुकोer) अणु
		अगर (!task_has_pi_रुकोers(task))
			जाओ out_unlock_pi;
		/*
		 * If deadlock detection is off, we stop here अगर we
		 * are not the top pi रुकोer of the task. If deadlock
		 * detection is enabled we जारी, but stop the
		 * requeueing in the chain walk.
		 */
		अगर (top_रुकोer != task_top_pi_रुकोer(task)) अणु
			अगर (!detect_deadlock)
				जाओ out_unlock_pi;
			अन्यथा
				requeue = false;
		पूर्ण
	पूर्ण

	/*
	 * If the रुकोer priority is the same as the task priority
	 * then there is no further priority adjusपंचांगent necessary.  If
	 * deadlock detection is off, we stop the chain walk. If its
	 * enabled we जारी, but stop the requeueing in the chain
	 * walk.
	 */
	अगर (rt_mutex_रुकोer_equal(रुकोer, task_to_रुकोer(task))) अणु
		अगर (!detect_deadlock)
			जाओ out_unlock_pi;
		अन्यथा
			requeue = false;
	पूर्ण

	/*
	 * [4] Get the next lock
	 */
	lock = रुकोer->lock;
	/*
	 * [5] We need to trylock here as we are holding task->pi_lock,
	 * which is the reverse lock order versus the other rपंचांगutex
	 * operations.
	 */
	अगर (!raw_spin_trylock(&lock->रुको_lock)) अणु
		raw_spin_unlock_irq(&task->pi_lock);
		cpu_relax();
		जाओ retry;
	पूर्ण

	/*
	 * [6] check_निकास_conditions_2() रक्षित by task->pi_lock and
	 * lock->रुको_lock.
	 *
	 * Deadlock detection. If the lock is the same as the original
	 * lock which caused us to walk the lock chain or अगर the
	 * current lock is owned by the task which initiated the chain
	 * walk, we detected a deadlock.
	 */
	अगर (lock == orig_lock || rt_mutex_owner(lock) == top_task) अणु
		raw_spin_unlock(&lock->रुको_lock);
		ret = -EDEADLK;
		जाओ out_unlock_pi;
	पूर्ण

	/*
	 * If we just follow the lock chain क्रम deadlock detection, no
	 * need to करो all the requeue operations. To aव्योम a truckload
	 * of conditionals around the various places below, just करो the
	 * minimum chain walk checks.
	 */
	अगर (!requeue) अणु
		/*
		 * No requeue[7] here. Just release @task [8]
		 */
		raw_spin_unlock(&task->pi_lock);
		put_task_काष्ठा(task);

		/*
		 * [9] check_निकास_conditions_3 रक्षित by lock->रुको_lock.
		 * If there is no owner of the lock, end of chain.
		 */
		अगर (!rt_mutex_owner(lock)) अणु
			raw_spin_unlock_irq(&lock->रुको_lock);
			वापस 0;
		पूर्ण

		/* [10] Grab the next task, i.e. owner of @lock */
		task = get_task_काष्ठा(rt_mutex_owner(lock));
		raw_spin_lock(&task->pi_lock);

		/*
		 * No requeue [11] here. We just करो deadlock detection.
		 *
		 * [12] Store whether owner is blocked
		 * itself. Decision is made after dropping the locks
		 */
		next_lock = task_blocked_on_lock(task);
		/*
		 * Get the top रुकोer क्रम the next iteration
		 */
		top_रुकोer = rt_mutex_top_रुकोer(lock);

		/* [13] Drop locks */
		raw_spin_unlock(&task->pi_lock);
		raw_spin_unlock_irq(&lock->रुको_lock);

		/* If owner is not blocked, end of chain. */
		अगर (!next_lock)
			जाओ out_put_task;
		जाओ again;
	पूर्ण

	/*
	 * Store the current top रुकोer beक्रमe करोing the requeue
	 * operation on @lock. We need it क्रम the boost/deboost
	 * decision below.
	 */
	prerequeue_top_रुकोer = rt_mutex_top_रुकोer(lock);

	/* [7] Requeue the रुकोer in the lock रुकोer tree. */
	rt_mutex_dequeue(lock, रुकोer);

	/*
	 * Update the रुकोer prio fields now that we're dequeued.
	 *
	 * These values can have changed through either:
	 *
	 *   sys_sched_set_scheduler() / sys_sched_setattr()
	 *
	 * or
	 *
	 *   DL CBS enक्रमcement advancing the effective deadline.
	 *
	 * Even though pi_रुकोers also uses these fields, and that tree is only
	 * updated in [11], we can करो this here, since we hold [L], which
	 * serializes all pi_रुकोers access and rb_erase() करोes not care about
	 * the values of the node being हटाओd.
	 */
	रुकोer->prio = task->prio;
	रुकोer->deadline = task->dl.deadline;

	rt_mutex_enqueue(lock, रुकोer);

	/* [8] Release the task */
	raw_spin_unlock(&task->pi_lock);
	put_task_काष्ठा(task);

	/*
	 * [9] check_निकास_conditions_3 रक्षित by lock->रुको_lock.
	 *
	 * We must पात the chain walk अगर there is no lock owner even
	 * in the dead lock detection हाल, as we have nothing to
	 * follow here. This is the end of the chain we are walking.
	 */
	अगर (!rt_mutex_owner(lock)) अणु
		/*
		 * If the requeue [7] above changed the top रुकोer,
		 * then we need to wake the new top रुकोer up to try
		 * to get the lock.
		 */
		अगर (prerequeue_top_रुकोer != rt_mutex_top_रुकोer(lock))
			wake_up_process(rt_mutex_top_रुकोer(lock)->task);
		raw_spin_unlock_irq(&lock->रुको_lock);
		वापस 0;
	पूर्ण

	/* [10] Grab the next task, i.e. the owner of @lock */
	task = get_task_काष्ठा(rt_mutex_owner(lock));
	raw_spin_lock(&task->pi_lock);

	/* [11] requeue the pi रुकोers अगर necessary */
	अगर (रुकोer == rt_mutex_top_रुकोer(lock)) अणु
		/*
		 * The रुकोer became the new top (highest priority)
		 * रुकोer on the lock. Replace the previous top रुकोer
		 * in the owner tasks pi रुकोers tree with this रुकोer
		 * and adjust the priority of the owner.
		 */
		rt_mutex_dequeue_pi(task, prerequeue_top_रुकोer);
		rt_mutex_enqueue_pi(task, रुकोer);
		rt_mutex_adjust_prio(task);

	पूर्ण अन्यथा अगर (prerequeue_top_रुकोer == रुकोer) अणु
		/*
		 * The रुकोer was the top रुकोer on the lock, but is
		 * no दीर्घer the top priority रुकोer. Replace रुकोer in
		 * the owner tasks pi रुकोers tree with the new top
		 * (highest priority) रुकोer and adjust the priority
		 * of the owner.
		 * The new top रुकोer is stored in @रुकोer so that
		 * @रुकोer == @top_रुकोer evaluates to true below and
		 * we जारी to deboost the rest of the chain.
		 */
		rt_mutex_dequeue_pi(task, रुकोer);
		रुकोer = rt_mutex_top_रुकोer(lock);
		rt_mutex_enqueue_pi(task, रुकोer);
		rt_mutex_adjust_prio(task);
	पूर्ण अन्यथा अणु
		/*
		 * Nothing changed. No need to करो any priority
		 * adjusपंचांगent.
		 */
	पूर्ण

	/*
	 * [12] check_निकास_conditions_4() रक्षित by task->pi_lock
	 * and lock->रुको_lock. The actual decisions are made after we
	 * dropped the locks.
	 *
	 * Check whether the task which owns the current lock is pi
	 * blocked itself. If yes we store a poपूर्णांकer to the lock क्रम
	 * the lock chain change detection above. After we dropped
	 * task->pi_lock next_lock cannot be dereferenced anymore.
	 */
	next_lock = task_blocked_on_lock(task);
	/*
	 * Store the top रुकोer of @lock क्रम the end of chain walk
	 * decision below.
	 */
	top_रुकोer = rt_mutex_top_रुकोer(lock);

	/* [13] Drop the locks */
	raw_spin_unlock(&task->pi_lock);
	raw_spin_unlock_irq(&lock->रुको_lock);

	/*
	 * Make the actual निकास decisions [12], based on the stored
	 * values.
	 *
	 * We reached the end of the lock chain. Stop right here. No
	 * poपूर्णांक to go back just to figure that out.
	 */
	अगर (!next_lock)
		जाओ out_put_task;

	/*
	 * If the current रुकोer is not the top रुकोer on the lock,
	 * then we can stop the chain walk here अगर we are not in full
	 * deadlock detection mode.
	 */
	अगर (!detect_deadlock && रुकोer != top_रुकोer)
		जाओ out_put_task;

	जाओ again;

 out_unlock_pi:
	raw_spin_unlock_irq(&task->pi_lock);
 out_put_task:
	put_task_काष्ठा(task);

	वापस ret;
पूर्ण

/*
 * Try to take an rt-mutex
 *
 * Must be called with lock->रुको_lock held and पूर्णांकerrupts disabled
 *
 * @lock:   The lock to be acquired.
 * @task:   The task which wants to acquire the lock
 * @रुकोer: The रुकोer that is queued to the lock's रुको tree अगर the
 *	    callsite called task_blocked_on_lock(), otherwise शून्य
 */
अटल पूर्णांक __sched
try_to_take_rt_mutex(काष्ठा rt_mutex *lock, काष्ठा task_काष्ठा *task,
		     काष्ठा rt_mutex_रुकोer *रुकोer)
अणु
	lockdep_निश्चित_held(&lock->रुको_lock);

	/*
	 * Beक्रमe testing whether we can acquire @lock, we set the
	 * RT_MUTEX_HAS_WAITERS bit in @lock->owner. This क्रमces all
	 * other tasks which try to modअगरy @lock पूर्णांकo the slow path
	 * and they serialize on @lock->रुको_lock.
	 *
	 * The RT_MUTEX_HAS_WAITERS bit can have a transitional state
	 * as explained at the top of this file अगर and only अगर:
	 *
	 * - There is a lock owner. The caller must fixup the
	 *   transient state अगर it करोes a trylock or leaves the lock
	 *   function due to a संकेत or समयout.
	 *
	 * - @task acquires the lock and there are no other
	 *   रुकोers. This is unकरोne in rt_mutex_set_owner(@task) at
	 *   the end of this function.
	 */
	mark_rt_mutex_रुकोers(lock);

	/*
	 * If @lock has an owner, give up.
	 */
	अगर (rt_mutex_owner(lock))
		वापस 0;

	/*
	 * If @रुकोer != शून्य, @task has alपढ़ोy enqueued the रुकोer
	 * पूर्णांकo @lock रुकोer tree. If @रुकोer == शून्य then this is a
	 * trylock attempt.
	 */
	अगर (रुकोer) अणु
		/*
		 * If रुकोer is not the highest priority रुकोer of
		 * @lock, give up.
		 */
		अगर (रुकोer != rt_mutex_top_रुकोer(lock))
			वापस 0;

		/*
		 * We can acquire the lock. Remove the रुकोer from the
		 * lock रुकोers tree.
		 */
		rt_mutex_dequeue(lock, रुकोer);

	पूर्ण अन्यथा अणु
		/*
		 * If the lock has रुकोers alपढ़ोy we check whether @task is
		 * eligible to take over the lock.
		 *
		 * If there are no other रुकोers, @task can acquire
		 * the lock.  @task->pi_blocked_on is शून्य, so it करोes
		 * not need to be dequeued.
		 */
		अगर (rt_mutex_has_रुकोers(lock)) अणु
			/*
			 * If @task->prio is greater than or equal to
			 * the top रुकोer priority (kernel view),
			 * @task lost.
			 */
			अगर (!rt_mutex_रुकोer_less(task_to_रुकोer(task),
						  rt_mutex_top_रुकोer(lock)))
				वापस 0;

			/*
			 * The current top रुकोer stays enqueued. We
			 * करोn't have to change anything in the lock
			 * रुकोers order.
			 */
		पूर्ण अन्यथा अणु
			/*
			 * No रुकोers. Take the lock without the
			 * pi_lock dance.@task->pi_blocked_on is शून्य
			 * and we have no रुकोers to enqueue in @task
			 * pi रुकोers tree.
			 */
			जाओ takeit;
		पूर्ण
	पूर्ण

	/*
	 * Clear @task->pi_blocked_on. Requires protection by
	 * @task->pi_lock. Redundant operation क्रम the @रुकोer == शून्य
	 * हाल, but conditionals are more expensive than a redundant
	 * store.
	 */
	raw_spin_lock(&task->pi_lock);
	task->pi_blocked_on = शून्य;
	/*
	 * Finish the lock acquisition. @task is the new owner. If
	 * other रुकोers exist we have to insert the highest priority
	 * रुकोer पूर्णांकo @task->pi_रुकोers tree.
	 */
	अगर (rt_mutex_has_रुकोers(lock))
		rt_mutex_enqueue_pi(task, rt_mutex_top_रुकोer(lock));
	raw_spin_unlock(&task->pi_lock);

takeit:
	/*
	 * This either preserves the RT_MUTEX_HAS_WAITERS bit अगर there
	 * are still रुकोers or clears it.
	 */
	rt_mutex_set_owner(lock, task);

	वापस 1;
पूर्ण

/*
 * Task blocks on lock.
 *
 * Prepare रुकोer and propagate pi chain
 *
 * This must be called with lock->रुको_lock held and पूर्णांकerrupts disabled
 */
अटल पूर्णांक __sched task_blocks_on_rt_mutex(काष्ठा rt_mutex *lock,
					   काष्ठा rt_mutex_रुकोer *रुकोer,
					   काष्ठा task_काष्ठा *task,
					   क्रमागत rपंचांगutex_chainwalk chwalk)
अणु
	काष्ठा task_काष्ठा *owner = rt_mutex_owner(lock);
	काष्ठा rt_mutex_रुकोer *top_रुकोer = रुकोer;
	काष्ठा rt_mutex *next_lock;
	पूर्णांक chain_walk = 0, res;

	lockdep_निश्चित_held(&lock->रुको_lock);

	/*
	 * Early deadlock detection. We really करोn't want the task to
	 * enqueue on itself just to untangle the mess later. It's not
	 * only an optimization. We drop the locks, so another रुकोer
	 * can come in beक्रमe the chain walk detects the deadlock. So
	 * the other will detect the deadlock and वापस -EDEADLOCK,
	 * which is wrong, as the other रुकोer is not in a deadlock
	 * situation.
	 */
	अगर (owner == task)
		वापस -EDEADLK;

	raw_spin_lock(&task->pi_lock);
	रुकोer->task = task;
	रुकोer->lock = lock;
	रुकोer->prio = task->prio;
	रुकोer->deadline = task->dl.deadline;

	/* Get the top priority रुकोer on the lock */
	अगर (rt_mutex_has_रुकोers(lock))
		top_रुकोer = rt_mutex_top_रुकोer(lock);
	rt_mutex_enqueue(lock, रुकोer);

	task->pi_blocked_on = रुकोer;

	raw_spin_unlock(&task->pi_lock);

	अगर (!owner)
		वापस 0;

	raw_spin_lock(&owner->pi_lock);
	अगर (रुकोer == rt_mutex_top_रुकोer(lock)) अणु
		rt_mutex_dequeue_pi(owner, top_रुकोer);
		rt_mutex_enqueue_pi(owner, रुकोer);

		rt_mutex_adjust_prio(owner);
		अगर (owner->pi_blocked_on)
			chain_walk = 1;
	पूर्ण अन्यथा अगर (rt_mutex_cond_detect_deadlock(रुकोer, chwalk)) अणु
		chain_walk = 1;
	पूर्ण

	/* Store the lock on which owner is blocked or शून्य */
	next_lock = task_blocked_on_lock(owner);

	raw_spin_unlock(&owner->pi_lock);
	/*
	 * Even अगर full deadlock detection is on, अगर the owner is not
	 * blocked itself, we can aव्योम finding this out in the chain
	 * walk.
	 */
	अगर (!chain_walk || !next_lock)
		वापस 0;

	/*
	 * The owner can't disappear जबतक holding a lock,
	 * so the owner काष्ठा is रक्षित by रुको_lock.
	 * Gets dropped in rt_mutex_adjust_prio_chain()!
	 */
	get_task_काष्ठा(owner);

	raw_spin_unlock_irq(&lock->रुको_lock);

	res = rt_mutex_adjust_prio_chain(owner, chwalk, lock,
					 next_lock, रुकोer, task);

	raw_spin_lock_irq(&lock->रुको_lock);

	वापस res;
पूर्ण

/*
 * Remove the top रुकोer from the current tasks pi रुकोer tree and
 * queue it up.
 *
 * Called with lock->रुको_lock held and पूर्णांकerrupts disabled.
 */
अटल व्योम __sched mark_wakeup_next_रुकोer(काष्ठा wake_q_head *wake_q,
					    काष्ठा rt_mutex *lock)
अणु
	काष्ठा rt_mutex_रुकोer *रुकोer;

	raw_spin_lock(&current->pi_lock);

	रुकोer = rt_mutex_top_रुकोer(lock);

	/*
	 * Remove it from current->pi_रुकोers and deboost.
	 *
	 * We must in fact deboost here in order to ensure we call
	 * rt_mutex_setprio() to update p->pi_top_task beक्रमe the
	 * task unblocks.
	 */
	rt_mutex_dequeue_pi(current, रुकोer);
	rt_mutex_adjust_prio(current);

	/*
	 * As we are waking up the top रुकोer, and the रुकोer stays
	 * queued on the lock until it माला_लो the lock, this lock
	 * obviously has रुकोers. Just set the bit here and this has
	 * the added benefit of क्रमcing all new tasks पूर्णांकo the
	 * slow path making sure no task of lower priority than
	 * the top रुकोer can steal this lock.
	 */
	lock->owner = (व्योम *) RT_MUTEX_HAS_WAITERS;

	/*
	 * We deboosted beक्रमe waking the top रुकोer task such that we करोn't
	 * run two tasks with the 'same' priority (and ensure the
	 * p->pi_top_task poपूर्णांकer poपूर्णांकs to a blocked task). This however can
	 * lead to priority inversion अगर we would get preempted after the
	 * deboost but beक्रमe waking our करोnor task, hence the preempt_disable()
	 * beक्रमe unlock.
	 *
	 * Pairs with preempt_enable() in rt_mutex_postunlock();
	 */
	preempt_disable();
	wake_q_add(wake_q, रुकोer->task);
	raw_spin_unlock(&current->pi_lock);
पूर्ण

/*
 * Remove a रुकोer from a lock and give up
 *
 * Must be called with lock->रुको_lock held and पूर्णांकerrupts disabled. I must
 * have just failed to try_to_take_rt_mutex().
 */
अटल व्योम __sched हटाओ_रुकोer(काष्ठा rt_mutex *lock,
				  काष्ठा rt_mutex_रुकोer *रुकोer)
अणु
	bool is_top_रुकोer = (रुकोer == rt_mutex_top_रुकोer(lock));
	काष्ठा task_काष्ठा *owner = rt_mutex_owner(lock);
	काष्ठा rt_mutex *next_lock;

	lockdep_निश्चित_held(&lock->रुको_lock);

	raw_spin_lock(&current->pi_lock);
	rt_mutex_dequeue(lock, रुकोer);
	current->pi_blocked_on = शून्य;
	raw_spin_unlock(&current->pi_lock);

	/*
	 * Only update priority अगर the रुकोer was the highest priority
	 * रुकोer of the lock and there is an owner to update.
	 */
	अगर (!owner || !is_top_रुकोer)
		वापस;

	raw_spin_lock(&owner->pi_lock);

	rt_mutex_dequeue_pi(owner, रुकोer);

	अगर (rt_mutex_has_रुकोers(lock))
		rt_mutex_enqueue_pi(owner, rt_mutex_top_रुकोer(lock));

	rt_mutex_adjust_prio(owner);

	/* Store the lock on which owner is blocked or शून्य */
	next_lock = task_blocked_on_lock(owner);

	raw_spin_unlock(&owner->pi_lock);

	/*
	 * Don't walk the chain, अगर the owner task is not blocked
	 * itself.
	 */
	अगर (!next_lock)
		वापस;

	/* माला_लो dropped in rt_mutex_adjust_prio_chain()! */
	get_task_काष्ठा(owner);

	raw_spin_unlock_irq(&lock->रुको_lock);

	rt_mutex_adjust_prio_chain(owner, RT_MUTEX_MIN_CHAINWALK, lock,
				   next_lock, शून्य, current);

	raw_spin_lock_irq(&lock->रुको_lock);
पूर्ण

/*
 * Recheck the pi chain, in हाल we got a priority setting
 *
 * Called from sched_setscheduler
 */
व्योम __sched rt_mutex_adjust_pi(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा rt_mutex_रुकोer *रुकोer;
	काष्ठा rt_mutex *next_lock;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&task->pi_lock, flags);

	रुकोer = task->pi_blocked_on;
	अगर (!रुकोer || rt_mutex_रुकोer_equal(रुकोer, task_to_रुकोer(task))) अणु
		raw_spin_unlock_irqrestore(&task->pi_lock, flags);
		वापस;
	पूर्ण
	next_lock = रुकोer->lock;
	raw_spin_unlock_irqrestore(&task->pi_lock, flags);

	/* माला_लो dropped in rt_mutex_adjust_prio_chain()! */
	get_task_काष्ठा(task);

	rt_mutex_adjust_prio_chain(task, RT_MUTEX_MIN_CHAINWALK, शून्य,
				   next_lock, शून्य, task);
पूर्ण

व्योम __sched rt_mutex_init_रुकोer(काष्ठा rt_mutex_रुकोer *रुकोer)
अणु
	debug_rt_mutex_init_रुकोer(रुकोer);
	RB_CLEAR_NODE(&रुकोer->pi_tree_entry);
	RB_CLEAR_NODE(&रुकोer->tree_entry);
	रुकोer->task = शून्य;
पूर्ण

/**
 * __rt_mutex_slowlock() - Perक्रमm the रुको-wake-try-to-take loop
 * @lock:		 the rt_mutex to take
 * @state:		 the state the task should block in (TASK_INTERRUPTIBLE
 *			 or TASK_UNINTERRUPTIBLE)
 * @समयout:		 the pre-initialized and started समयr, or शून्य क्रम none
 * @रुकोer:		 the pre-initialized rt_mutex_रुकोer
 *
 * Must be called with lock->रुको_lock held and पूर्णांकerrupts disabled
 */
अटल पूर्णांक __sched __rt_mutex_slowlock(काष्ठा rt_mutex *lock, पूर्णांक state,
				       काष्ठा hrसमयr_sleeper *समयout,
				       काष्ठा rt_mutex_रुकोer *रुकोer)
अणु
	पूर्णांक ret = 0;

	क्रम (;;) अणु
		/* Try to acquire the lock: */
		अगर (try_to_take_rt_mutex(lock, current, रुकोer))
			अवरोध;

		अगर (समयout && !समयout->task) अणु
			ret = -ETIMEDOUT;
			अवरोध;
		पूर्ण
		अगर (संकेत_pending_state(state, current)) अणु
			ret = -EINTR;
			अवरोध;
		पूर्ण

		raw_spin_unlock_irq(&lock->रुको_lock);

		schedule();

		raw_spin_lock_irq(&lock->रुको_lock);
		set_current_state(state);
	पूर्ण

	__set_current_state(TASK_RUNNING);
	वापस ret;
पूर्ण

अटल व्योम __sched rt_mutex_handle_deadlock(पूर्णांक res, पूर्णांक detect_deadlock,
					     काष्ठा rt_mutex_रुकोer *w)
अणु
	/*
	 * If the result is not -EDEADLOCK or the caller requested
	 * deadlock detection, nothing to करो here.
	 */
	अगर (res != -EDEADLOCK || detect_deadlock)
		वापस;

	/*
	 * Yell loudly and stop the task right here.
	 */
	WARN(1, "rtmutex deadlock detected\n");
	जबतक (1) अणु
		set_current_state(TASK_INTERRUPTIBLE);
		schedule();
	पूर्ण
पूर्ण

/*
 * Slow path lock function:
 */
अटल पूर्णांक __sched rt_mutex_slowlock(काष्ठा rt_mutex *lock, पूर्णांक state,
				     काष्ठा hrसमयr_sleeper *समयout,
				     क्रमागत rपंचांगutex_chainwalk chwalk)
अणु
	काष्ठा rt_mutex_रुकोer रुकोer;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	rt_mutex_init_रुकोer(&रुकोer);

	/*
	 * Technically we could use raw_spin_[un]lock_irq() here, but this can
	 * be called in early boot अगर the cmpxchg() fast path is disabled
	 * (debug, no architecture support). In this हाल we will acquire the
	 * rपंचांगutex with lock->रुको_lock held. But we cannot unconditionally
	 * enable पूर्णांकerrupts in that early boot हाल. So we need to use the
	 * irqsave/restore variants.
	 */
	raw_spin_lock_irqsave(&lock->रुको_lock, flags);

	/* Try to acquire the lock again: */
	अगर (try_to_take_rt_mutex(lock, current, शून्य)) अणु
		raw_spin_unlock_irqrestore(&lock->रुको_lock, flags);
		वापस 0;
	पूर्ण

	set_current_state(state);

	/* Setup the समयr, when समयout != शून्य */
	अगर (unlikely(समयout))
		hrसमयr_start_expires(&समयout->समयr, HRTIMER_MODE_ABS);

	ret = task_blocks_on_rt_mutex(lock, &रुकोer, current, chwalk);

	अगर (likely(!ret))
		/* sleep on the mutex */
		ret = __rt_mutex_slowlock(lock, state, समयout, &रुकोer);

	अगर (unlikely(ret)) अणु
		__set_current_state(TASK_RUNNING);
		हटाओ_रुकोer(lock, &रुकोer);
		rt_mutex_handle_deadlock(ret, chwalk, &रुकोer);
	पूर्ण

	/*
	 * try_to_take_rt_mutex() sets the रुकोer bit
	 * unconditionally. We might have to fix that up.
	 */
	fixup_rt_mutex_रुकोers(lock);

	raw_spin_unlock_irqrestore(&lock->रुको_lock, flags);

	/* Remove pending समयr: */
	अगर (unlikely(समयout))
		hrसमयr_cancel(&समयout->समयr);

	debug_rt_mutex_मुक्त_रुकोer(&रुकोer);

	वापस ret;
पूर्ण

अटल पूर्णांक __sched __rt_mutex_slowtrylock(काष्ठा rt_mutex *lock)
अणु
	पूर्णांक ret = try_to_take_rt_mutex(lock, current, शून्य);

	/*
	 * try_to_take_rt_mutex() sets the lock रुकोers bit
	 * unconditionally. Clean this up.
	 */
	fixup_rt_mutex_रुकोers(lock);

	वापस ret;
पूर्ण

/*
 * Slow path try-lock function:
 */
अटल पूर्णांक __sched rt_mutex_slowtrylock(काष्ठा rt_mutex *lock)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/*
	 * If the lock alपढ़ोy has an owner we fail to get the lock.
	 * This can be करोne without taking the @lock->रुको_lock as
	 * it is only being पढ़ो, and this is a trylock anyway.
	 */
	अगर (rt_mutex_owner(lock))
		वापस 0;

	/*
	 * The mutex has currently no owner. Lock the रुको lock and try to
	 * acquire the lock. We use irqsave here to support early boot calls.
	 */
	raw_spin_lock_irqsave(&lock->रुको_lock, flags);

	ret = __rt_mutex_slowtrylock(lock);

	raw_spin_unlock_irqrestore(&lock->रुको_lock, flags);

	वापस ret;
पूर्ण

/*
 * Perक्रमms the wakeup of the top-रुकोer and re-enables preemption.
 */
व्योम __sched rt_mutex_postunlock(काष्ठा wake_q_head *wake_q)
अणु
	wake_up_q(wake_q);

	/* Pairs with preempt_disable() in mark_wakeup_next_रुकोer() */
	preempt_enable();
पूर्ण

/*
 * Slow path to release a rt-mutex.
 *
 * Return whether the current task needs to call rt_mutex_postunlock().
 */
अटल व्योम __sched rt_mutex_slowunlock(काष्ठा rt_mutex *lock)
अणु
	DEFINE_WAKE_Q(wake_q);
	अचिन्हित दीर्घ flags;

	/* irqsave required to support early boot calls */
	raw_spin_lock_irqsave(&lock->रुको_lock, flags);

	debug_rt_mutex_unlock(lock);

	/*
	 * We must be careful here अगर the fast path is enabled. If we
	 * have no रुकोers queued we cannot set owner to शून्य here
	 * because of:
	 *
	 * foo->lock->owner = शून्य;
	 *			rपंचांगutex_lock(foo->lock);   <- fast path
	 *			मुक्त = atomic_dec_and_test(foo->refcnt);
	 *			rपंचांगutex_unlock(foo->lock); <- fast path
	 *			अगर (मुक्त)
	 *				kमुक्त(foo);
	 * raw_spin_unlock(foo->lock->रुको_lock);
	 *
	 * So क्रम the fastpath enabled kernel:
	 *
	 * Nothing can set the रुकोers bit as दीर्घ as we hold
	 * lock->रुको_lock. So we करो the following sequence:
	 *
	 *	owner = rt_mutex_owner(lock);
	 *	clear_rt_mutex_रुकोers(lock);
	 *	raw_spin_unlock(&lock->रुको_lock);
	 *	अगर (cmpxchg(&lock->owner, owner, 0) == owner)
	 *		वापस;
	 *	जाओ retry;
	 *
	 * The fastpath disabled variant is simple as all access to
	 * lock->owner is serialized by lock->रुको_lock:
	 *
	 *	lock->owner = शून्य;
	 *	raw_spin_unlock(&lock->रुको_lock);
	 */
	जबतक (!rt_mutex_has_रुकोers(lock)) अणु
		/* Drops lock->रुको_lock ! */
		अगर (unlock_rt_mutex_safe(lock, flags) == true)
			वापस;
		/* Relock the rपंचांगutex and try again */
		raw_spin_lock_irqsave(&lock->रुको_lock, flags);
	पूर्ण

	/*
	 * The wakeup next रुकोer path करोes not suffer from the above
	 * race. See the comments there.
	 *
	 * Queue the next रुकोer क्रम wakeup once we release the रुको_lock.
	 */
	mark_wakeup_next_रुकोer(&wake_q, lock);
	raw_spin_unlock_irqrestore(&lock->रुको_lock, flags);

	rt_mutex_postunlock(&wake_q);
पूर्ण

/*
 * debug aware fast / slowpath lock,trylock,unlock
 *
 * The atomic acquire/release ops are compiled away, when either the
 * architecture करोes not support cmpxchg or when debugging is enabled.
 */
अटल __always_अंतरभूत पूर्णांक __rt_mutex_lock(काष्ठा rt_mutex *lock, दीर्घ state,
					   अचिन्हित पूर्णांक subclass)
अणु
	पूर्णांक ret;

	might_sleep();
	mutex_acquire(&lock->dep_map, subclass, 0, _RET_IP_);

	अगर (likely(rt_mutex_cmpxchg_acquire(lock, शून्य, current)))
		वापस 0;

	ret = rt_mutex_slowlock(lock, state, शून्य, RT_MUTEX_MIN_CHAINWALK);
	अगर (ret)
		mutex_release(&lock->dep_map, _RET_IP_);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
/**
 * rt_mutex_lock_nested - lock a rt_mutex
 *
 * @lock: the rt_mutex to be locked
 * @subclass: the lockdep subclass
 */
व्योम __sched rt_mutex_lock_nested(काष्ठा rt_mutex *lock, अचिन्हित पूर्णांक subclass)
अणु
	__rt_mutex_lock(lock, TASK_UNINTERRUPTIBLE, subclass);
पूर्ण
EXPORT_SYMBOL_GPL(rt_mutex_lock_nested);

#अन्यथा /* !CONFIG_DEBUG_LOCK_ALLOC */

/**
 * rt_mutex_lock - lock a rt_mutex
 *
 * @lock: the rt_mutex to be locked
 */
व्योम __sched rt_mutex_lock(काष्ठा rt_mutex *lock)
अणु
	__rt_mutex_lock(lock, TASK_UNINTERRUPTIBLE, 0);
पूर्ण
EXPORT_SYMBOL_GPL(rt_mutex_lock);
#पूर्ण_अगर

/**
 * rt_mutex_lock_पूर्णांकerruptible - lock a rt_mutex पूर्णांकerruptible
 *
 * @lock:		the rt_mutex to be locked
 *
 * Returns:
 *  0		on success
 * -EINTR	when पूर्णांकerrupted by a संकेत
 */
पूर्णांक __sched rt_mutex_lock_पूर्णांकerruptible(काष्ठा rt_mutex *lock)
अणु
	वापस __rt_mutex_lock(lock, TASK_INTERRUPTIBLE, 0);
पूर्ण
EXPORT_SYMBOL_GPL(rt_mutex_lock_पूर्णांकerruptible);

/**
 * rt_mutex_trylock - try to lock a rt_mutex
 *
 * @lock:	the rt_mutex to be locked
 *
 * This function can only be called in thपढ़ो context. It's safe to call it
 * from atomic regions, but not from hard or soft पूर्णांकerrupt context.
 *
 * Returns:
 *  1 on success
 *  0 on contention
 */
पूर्णांक __sched rt_mutex_trylock(काष्ठा rt_mutex *lock)
अणु
	पूर्णांक ret;

	अगर (IS_ENABLED(CONFIG_DEBUG_RT_MUTEXES) && WARN_ON_ONCE(!in_task()))
		वापस 0;

	/*
	 * No lockdep annotation required because lockdep disables the fast
	 * path.
	 */
	अगर (likely(rt_mutex_cmpxchg_acquire(lock, शून्य, current)))
		वापस 1;

	ret = rt_mutex_slowtrylock(lock);
	अगर (ret)
		mutex_acquire(&lock->dep_map, 0, 1, _RET_IP_);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(rt_mutex_trylock);

/**
 * rt_mutex_unlock - unlock a rt_mutex
 *
 * @lock: the rt_mutex to be unlocked
 */
व्योम __sched rt_mutex_unlock(काष्ठा rt_mutex *lock)
अणु
	mutex_release(&lock->dep_map, _RET_IP_);
	अगर (likely(rt_mutex_cmpxchg_release(lock, current, शून्य)))
		वापस;

	rt_mutex_slowunlock(lock);
पूर्ण
EXPORT_SYMBOL_GPL(rt_mutex_unlock);

/*
 * Futex variants, must not use fastpath.
 */
पूर्णांक __sched rt_mutex_futex_trylock(काष्ठा rt_mutex *lock)
अणु
	वापस rt_mutex_slowtrylock(lock);
पूर्ण

पूर्णांक __sched __rt_mutex_futex_trylock(काष्ठा rt_mutex *lock)
अणु
	वापस __rt_mutex_slowtrylock(lock);
पूर्ण

/**
 * __rt_mutex_futex_unlock - Futex variant, that since futex variants
 * करो not use the fast-path, can be simple and will not need to retry.
 *
 * @lock:	The rt_mutex to be unlocked
 * @wake_q:	The wake queue head from which to get the next lock रुकोer
 */
bool __sched __rt_mutex_futex_unlock(काष्ठा rt_mutex *lock,
				     काष्ठा wake_q_head *wake_q)
अणु
	lockdep_निश्चित_held(&lock->रुको_lock);

	debug_rt_mutex_unlock(lock);

	अगर (!rt_mutex_has_रुकोers(lock)) अणु
		lock->owner = शून्य;
		वापस false; /* करोne */
	पूर्ण

	/*
	 * We've alपढ़ोy deboosted, mark_wakeup_next_रुकोer() will
	 * retain preempt_disabled when we drop the रुको_lock, to
	 * aव्योम inversion prior to the wakeup.  preempt_disable()
	 * therein pairs with rt_mutex_postunlock().
	 */
	mark_wakeup_next_रुकोer(wake_q, lock);

	वापस true; /* call postunlock() */
पूर्ण

व्योम __sched rt_mutex_futex_unlock(काष्ठा rt_mutex *lock)
अणु
	DEFINE_WAKE_Q(wake_q);
	अचिन्हित दीर्घ flags;
	bool postunlock;

	raw_spin_lock_irqsave(&lock->रुको_lock, flags);
	postunlock = __rt_mutex_futex_unlock(lock, &wake_q);
	raw_spin_unlock_irqrestore(&lock->रुको_lock, flags);

	अगर (postunlock)
		rt_mutex_postunlock(&wake_q);
पूर्ण

/**
 * __rt_mutex_init - initialize the rt_mutex
 *
 * @lock:	The rt_mutex to be initialized
 * @name:	The lock name used क्रम debugging
 * @key:	The lock class key used क्रम debugging
 *
 * Initialize the rt_mutex to unlocked state.
 *
 * Initializing of a locked rt_mutex is not allowed
 */
व्योम __sched __rt_mutex_init(काष्ठा rt_mutex *lock, स्थिर अक्षर *name,
		     काष्ठा lock_class_key *key)
अणु
	debug_check_no_locks_मुक्तd((व्योम *)lock, माप(*lock));
	lockdep_init_map(&lock->dep_map, name, key, 0);

	__rt_mutex_basic_init(lock);
पूर्ण
EXPORT_SYMBOL_GPL(__rt_mutex_init);

/**
 * rt_mutex_init_proxy_locked - initialize and lock a rt_mutex on behalf of a
 *				proxy owner
 *
 * @lock:	the rt_mutex to be locked
 * @proxy_owner:the task to set as owner
 *
 * No locking. Caller has to करो serializing itself
 *
 * Special API call क्रम PI-futex support. This initializes the rपंचांगutex and
 * assigns it to @proxy_owner. Concurrent operations on the rपंचांगutex are not
 * possible at this poपूर्णांक because the pi_state which contains the rपंचांगutex
 * is not yet visible to other tasks.
 */
व्योम __sched rt_mutex_init_proxy_locked(काष्ठा rt_mutex *lock,
					काष्ठा task_काष्ठा *proxy_owner)
अणु
	__rt_mutex_basic_init(lock);
	rt_mutex_set_owner(lock, proxy_owner);
पूर्ण

/**
 * rt_mutex_proxy_unlock - release a lock on behalf of owner
 *
 * @lock:	the rt_mutex to be locked
 *
 * No locking. Caller has to करो serializing itself
 *
 * Special API call क्रम PI-futex support. This merrily cleans up the rपंचांगutex
 * (debugging) state. Concurrent operations on this rt_mutex are not
 * possible because it beदीर्घs to the pi_state which is about to be मुक्तd
 * and it is not दीर्घer visible to other tasks.
 */
व्योम __sched rt_mutex_proxy_unlock(काष्ठा rt_mutex *lock)
अणु
	debug_rt_mutex_proxy_unlock(lock);
	rt_mutex_set_owner(lock, शून्य);
पूर्ण

/**
 * __rt_mutex_start_proxy_lock() - Start lock acquisition क्रम another task
 * @lock:		the rt_mutex to take
 * @रुकोer:		the pre-initialized rt_mutex_रुकोer
 * @task:		the task to prepare
 *
 * Starts the rt_mutex acquire; it enqueues the @रुकोer and करोes deadlock
 * detection. It करोes not रुको, see rt_mutex_रुको_proxy_lock() क्रम that.
 *
 * NOTE: करोes _NOT_ हटाओ the @रुकोer on failure; must either call
 * rt_mutex_रुको_proxy_lock() or rt_mutex_cleanup_proxy_lock() after this.
 *
 * Returns:
 *  0 - task blocked on lock
 *  1 - acquired the lock क्रम task, caller should wake it up
 * <0 - error
 *
 * Special API call क्रम PI-futex support.
 */
पूर्णांक __sched __rt_mutex_start_proxy_lock(काष्ठा rt_mutex *lock,
					काष्ठा rt_mutex_रुकोer *रुकोer,
					काष्ठा task_काष्ठा *task)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&lock->रुको_lock);

	अगर (try_to_take_rt_mutex(lock, task, शून्य))
		वापस 1;

	/* We enक्रमce deadlock detection क्रम futexes */
	ret = task_blocks_on_rt_mutex(lock, रुकोer, task,
				      RT_MUTEX_FULL_CHAINWALK);

	अगर (ret && !rt_mutex_owner(lock)) अणु
		/*
		 * Reset the वापस value. We might have
		 * वापसed with -EDEADLK and the owner
		 * released the lock जबतक we were walking the
		 * pi chain.  Let the रुकोer sort it out.
		 */
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * rt_mutex_start_proxy_lock() - Start lock acquisition क्रम another task
 * @lock:		the rt_mutex to take
 * @रुकोer:		the pre-initialized rt_mutex_रुकोer
 * @task:		the task to prepare
 *
 * Starts the rt_mutex acquire; it enqueues the @रुकोer and करोes deadlock
 * detection. It करोes not रुको, see rt_mutex_रुको_proxy_lock() क्रम that.
 *
 * NOTE: unlike __rt_mutex_start_proxy_lock this _DOES_ हटाओ the @रुकोer
 * on failure.
 *
 * Returns:
 *  0 - task blocked on lock
 *  1 - acquired the lock क्रम task, caller should wake it up
 * <0 - error
 *
 * Special API call क्रम PI-futex support.
 */
पूर्णांक __sched rt_mutex_start_proxy_lock(काष्ठा rt_mutex *lock,
				      काष्ठा rt_mutex_रुकोer *रुकोer,
				      काष्ठा task_काष्ठा *task)
अणु
	पूर्णांक ret;

	raw_spin_lock_irq(&lock->रुको_lock);
	ret = __rt_mutex_start_proxy_lock(lock, रुकोer, task);
	अगर (unlikely(ret))
		हटाओ_रुकोer(lock, रुकोer);
	raw_spin_unlock_irq(&lock->रुको_lock);

	वापस ret;
पूर्ण

/**
 * rt_mutex_रुको_proxy_lock() - Wait क्रम lock acquisition
 * @lock:		the rt_mutex we were woken on
 * @to:			the समयout, null अगर none. hrसमयr should alपढ़ोy have
 *			been started.
 * @रुकोer:		the pre-initialized rt_mutex_रुकोer
 *
 * Wait क्रम the lock acquisition started on our behalf by
 * rt_mutex_start_proxy_lock(). Upon failure, the caller must call
 * rt_mutex_cleanup_proxy_lock().
 *
 * Returns:
 *  0 - success
 * <0 - error, one of -EINTR, -ETIMEDOUT
 *
 * Special API call क्रम PI-futex support
 */
पूर्णांक __sched rt_mutex_रुको_proxy_lock(काष्ठा rt_mutex *lock,
				     काष्ठा hrसमयr_sleeper *to,
				     काष्ठा rt_mutex_रुकोer *रुकोer)
अणु
	पूर्णांक ret;

	raw_spin_lock_irq(&lock->रुको_lock);
	/* sleep on the mutex */
	set_current_state(TASK_INTERRUPTIBLE);
	ret = __rt_mutex_slowlock(lock, TASK_INTERRUPTIBLE, to, रुकोer);
	/*
	 * try_to_take_rt_mutex() sets the रुकोer bit unconditionally. We might
	 * have to fix that up.
	 */
	fixup_rt_mutex_रुकोers(lock);
	raw_spin_unlock_irq(&lock->रुको_lock);

	वापस ret;
पूर्ण

/**
 * rt_mutex_cleanup_proxy_lock() - Cleanup failed lock acquisition
 * @lock:		the rt_mutex we were woken on
 * @रुकोer:		the pre-initialized rt_mutex_रुकोer
 *
 * Attempt to clean up after a failed __rt_mutex_start_proxy_lock() or
 * rt_mutex_रुको_proxy_lock().
 *
 * Unless we acquired the lock; we're still enqueued on the रुको-list and can
 * in fact still be granted ownership until we're हटाओd. Thereक्रमe we can
 * find we are in fact the owner and must disregard the
 * rt_mutex_रुको_proxy_lock() failure.
 *
 * Returns:
 *  true  - did the cleanup, we करोne.
 *  false - we acquired the lock after rt_mutex_रुको_proxy_lock() वापसed,
 *          caller should disregards its वापस value.
 *
 * Special API call क्रम PI-futex support
 */
bool __sched rt_mutex_cleanup_proxy_lock(काष्ठा rt_mutex *lock,
					 काष्ठा rt_mutex_रुकोer *रुकोer)
अणु
	bool cleanup = false;

	raw_spin_lock_irq(&lock->रुको_lock);
	/*
	 * Do an unconditional try-lock, this deals with the lock stealing
	 * state where __rt_mutex_futex_unlock() -> mark_wakeup_next_रुकोer()
	 * sets a शून्य owner.
	 *
	 * We're not पूर्णांकerested in the वापस value, because the subsequent
	 * test on rt_mutex_owner() will infer that. If the trylock succeeded,
	 * we will own the lock and it will have हटाओd the रुकोer. If we
	 * failed the trylock, we're still not owner and we need to हटाओ
	 * ourselves.
	 */
	try_to_take_rt_mutex(lock, current, रुकोer);
	/*
	 * Unless we're the owner; we're still enqueued on the रुको_list.
	 * So check अगर we became owner, अगर not, take us off the रुको_list.
	 */
	अगर (rt_mutex_owner(lock) != current) अणु
		हटाओ_रुकोer(lock, रुकोer);
		cleanup = true;
	पूर्ण
	/*
	 * try_to_take_rt_mutex() sets the रुकोer bit unconditionally. We might
	 * have to fix that up.
	 */
	fixup_rt_mutex_रुकोers(lock);

	raw_spin_unlock_irq(&lock->रुको_lock);

	वापस cleanup;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_RT_MUTEXES
व्योम rt_mutex_debug_task_मुक्त(काष्ठा task_काष्ठा *task)
अणु
	DEBUG_LOCKS_WARN_ON(!RB_EMPTY_ROOT(&task->pi_रुकोers.rb_root));
	DEBUG_LOCKS_WARN_ON(task->pi_blocked_on);
पूर्ण
#पूर्ण_अगर
