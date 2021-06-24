<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * kernel/locking/mutex.c
 *
 * Mutexes: blocking mutual exclusion locks
 *
 * Started by Ingo Molnar:
 *
 *  Copyright (C) 2004, 2005, 2006 Red Hat, Inc., Ingo Molnar <mingo@redhat.com>
 *
 * Many thanks to Arjan van de Ven, Thomas Gleixner, Steven Rostedt and
 * David Howells क्रम suggestions and improvements.
 *
 *  - Adaptive spinning क्रम mutexes by Peter Zijlstra. (Ported to मुख्यline
 *    from the -rt tree, where it was originally implemented क्रम rपंचांगutexes
 *    by Steven Rostedt, based on work by Gregory Haskins, Peter Morreale
 *    and Sven Dietrich.
 *
 * Also see Documentation/locking/mutex-design.rst.
 */
#समावेश <linux/mutex.h>
#समावेश <linux/ww_mutex.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/rt.h>
#समावेश <linux/sched/wake_q.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/export.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/debug_locks.h>
#समावेश <linux/osq_lock.h>

#अगर_घोषित CONFIG_DEBUG_MUTEXES
# include "mutex-debug.h"
#अन्यथा
# include "mutex.h"
#पूर्ण_अगर

व्योम
__mutex_init(काष्ठा mutex *lock, स्थिर अक्षर *name, काष्ठा lock_class_key *key)
अणु
	atomic_दीर्घ_set(&lock->owner, 0);
	spin_lock_init(&lock->रुको_lock);
	INIT_LIST_HEAD(&lock->रुको_list);
#अगर_घोषित CONFIG_MUTEX_SPIN_ON_OWNER
	osq_lock_init(&lock->osq);
#पूर्ण_अगर

	debug_mutex_init(lock, name, key);
पूर्ण
EXPORT_SYMBOL(__mutex_init);

/*
 * @owner: contains: 'struct task_struct *' to the current lock owner,
 * शून्य means not owned. Since task_काष्ठा poपूर्णांकers are aligned at
 * at least L1_CACHE_BYTES, we have low bits to store extra state.
 *
 * Bit0 indicates a non-empty रुकोer list; unlock must issue a wakeup.
 * Bit1 indicates unlock needs to hand the lock to the top-रुकोer
 * Bit2 indicates hanकरोff has been करोne and we're रुकोing क्रम pickup.
 */
#घोषणा MUTEX_FLAG_WAITERS	0x01
#घोषणा MUTEX_FLAG_HANDOFF	0x02
#घोषणा MUTEX_FLAG_PICKUP	0x04

#घोषणा MUTEX_FLAGS		0x07

/*
 * Internal helper function; C करोesn't allow us to hide it :/
 *
 * DO NOT USE (outside of mutex code).
 */
अटल अंतरभूत काष्ठा task_काष्ठा *__mutex_owner(काष्ठा mutex *lock)
अणु
	वापस (काष्ठा task_काष्ठा *)(atomic_दीर्घ_पढ़ो(&lock->owner) & ~MUTEX_FLAGS);
पूर्ण

अटल अंतरभूत काष्ठा task_काष्ठा *__owner_task(अचिन्हित दीर्घ owner)
अणु
	वापस (काष्ठा task_काष्ठा *)(owner & ~MUTEX_FLAGS);
पूर्ण

bool mutex_is_locked(काष्ठा mutex *lock)
अणु
	वापस __mutex_owner(lock) != शून्य;
पूर्ण
EXPORT_SYMBOL(mutex_is_locked);

अटल अंतरभूत अचिन्हित दीर्घ __owner_flags(अचिन्हित दीर्घ owner)
अणु
	वापस owner & MUTEX_FLAGS;
पूर्ण

/*
 * Trylock variant that वापसs the owning task on failure.
 */
अटल अंतरभूत काष्ठा task_काष्ठा *__mutex_trylock_or_owner(काष्ठा mutex *lock)
अणु
	अचिन्हित दीर्घ owner, curr = (अचिन्हित दीर्घ)current;

	owner = atomic_दीर्घ_पढ़ो(&lock->owner);
	क्रम (;;) अणु /* must loop, can race against a flag */
		अचिन्हित दीर्घ old, flags = __owner_flags(owner);
		अचिन्हित दीर्घ task = owner & ~MUTEX_FLAGS;

		अगर (task) अणु
			अगर (likely(task != curr))
				अवरोध;

			अगर (likely(!(flags & MUTEX_FLAG_PICKUP)))
				अवरोध;

			flags &= ~MUTEX_FLAG_PICKUP;
		पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_DEBUG_MUTEXES
			DEBUG_LOCKS_WARN_ON(flags & MUTEX_FLAG_PICKUP);
#पूर्ण_अगर
		पूर्ण

		/*
		 * We set the HANDOFF bit, we must make sure it करोesn't live
		 * past the poपूर्णांक where we acquire it. This would be possible
		 * अगर we (accidentally) set the bit on an unlocked mutex.
		 */
		flags &= ~MUTEX_FLAG_HANDOFF;

		old = atomic_दीर्घ_cmpxchg_acquire(&lock->owner, owner, curr | flags);
		अगर (old == owner)
			वापस शून्य;

		owner = old;
	पूर्ण

	वापस __owner_task(owner);
पूर्ण

/*
 * Actual trylock that will work on any unlocked state.
 */
अटल अंतरभूत bool __mutex_trylock(काष्ठा mutex *lock)
अणु
	वापस !__mutex_trylock_or_owner(lock);
पूर्ण

#अगर_अघोषित CONFIG_DEBUG_LOCK_ALLOC
/*
 * Lockdep annotations are contained to the slow paths क्रम simplicity.
 * There is nothing that would stop spपढ़ोing the lockdep annotations outwards
 * except more code.
 */

/*
 * Optimistic trylock that only works in the uncontended हाल. Make sure to
 * follow with a __mutex_trylock() beक्रमe failing.
 */
अटल __always_अंतरभूत bool __mutex_trylock_fast(काष्ठा mutex *lock)
अणु
	अचिन्हित दीर्घ curr = (अचिन्हित दीर्घ)current;
	अचिन्हित दीर्घ zero = 0UL;

	अगर (atomic_दीर्घ_try_cmpxchg_acquire(&lock->owner, &zero, curr))
		वापस true;

	वापस false;
पूर्ण

अटल __always_अंतरभूत bool __mutex_unlock_fast(काष्ठा mutex *lock)
अणु
	अचिन्हित दीर्घ curr = (अचिन्हित दीर्घ)current;

	अगर (atomic_दीर्घ_cmpxchg_release(&lock->owner, curr, 0UL) == curr)
		वापस true;

	वापस false;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम __mutex_set_flag(काष्ठा mutex *lock, अचिन्हित दीर्घ flag)
अणु
	atomic_दीर्घ_or(flag, &lock->owner);
पूर्ण

अटल अंतरभूत व्योम __mutex_clear_flag(काष्ठा mutex *lock, अचिन्हित दीर्घ flag)
अणु
	atomic_दीर्घ_andnot(flag, &lock->owner);
पूर्ण

अटल अंतरभूत bool __mutex_रुकोer_is_first(काष्ठा mutex *lock, काष्ठा mutex_रुकोer *रुकोer)
अणु
	वापस list_first_entry(&lock->रुको_list, काष्ठा mutex_रुकोer, list) == रुकोer;
पूर्ण

/*
 * Add @रुकोer to a given location in the lock रुको_list and set the
 * FLAG_WAITERS flag अगर it's the first रुकोer.
 */
अटल व्योम
__mutex_add_रुकोer(काष्ठा mutex *lock, काष्ठा mutex_रुकोer *रुकोer,
		   काष्ठा list_head *list)
अणु
	debug_mutex_add_रुकोer(lock, रुकोer, current);

	list_add_tail(&रुकोer->list, list);
	अगर (__mutex_रुकोer_is_first(lock, रुकोer))
		__mutex_set_flag(lock, MUTEX_FLAG_WAITERS);
पूर्ण

अटल व्योम
__mutex_हटाओ_रुकोer(काष्ठा mutex *lock, काष्ठा mutex_रुकोer *रुकोer)
अणु
	list_del(&रुकोer->list);
	अगर (likely(list_empty(&lock->रुको_list)))
		__mutex_clear_flag(lock, MUTEX_FLAGS);

	debug_mutex_हटाओ_रुकोer(lock, रुकोer, current);
पूर्ण

/*
 * Give up ownership to a specअगरic task, when @task = शून्य, this is equivalent
 * to a regular unlock. Sets PICKUP on a hanकरोff, clears HANDOFF, preserves
 * WAITERS. Provides RELEASE semantics like a regular unlock, the
 * __mutex_trylock() provides a matching ACQUIRE semantics क्रम the hanकरोff.
 */
अटल व्योम __mutex_hanकरोff(काष्ठा mutex *lock, काष्ठा task_काष्ठा *task)
अणु
	अचिन्हित दीर्घ owner = atomic_दीर्घ_पढ़ो(&lock->owner);

	क्रम (;;) अणु
		अचिन्हित दीर्घ old, new;

#अगर_घोषित CONFIG_DEBUG_MUTEXES
		DEBUG_LOCKS_WARN_ON(__owner_task(owner) != current);
		DEBUG_LOCKS_WARN_ON(owner & MUTEX_FLAG_PICKUP);
#पूर्ण_अगर

		new = (owner & MUTEX_FLAG_WAITERS);
		new |= (अचिन्हित दीर्घ)task;
		अगर (task)
			new |= MUTEX_FLAG_PICKUP;

		old = atomic_दीर्घ_cmpxchg_release(&lock->owner, owner, new);
		अगर (old == owner)
			अवरोध;

		owner = old;
	पूर्ण
पूर्ण

#अगर_अघोषित CONFIG_DEBUG_LOCK_ALLOC
/*
 * We split the mutex lock/unlock logic पूर्णांकo separate fastpath and
 * slowpath functions, to reduce the रेजिस्टर pressure on the fastpath.
 * We also put the fastpath first in the kernel image, to make sure the
 * branch is predicted by the CPU as शेष-untaken.
 */
अटल व्योम __sched __mutex_lock_slowpath(काष्ठा mutex *lock);

/**
 * mutex_lock - acquire the mutex
 * @lock: the mutex to be acquired
 *
 * Lock the mutex exclusively क्रम this task. If the mutex is not
 * available right now, it will sleep until it can get it.
 *
 * The mutex must later on be released by the same task that
 * acquired it. Recursive locking is not allowed. The task
 * may not निकास without first unlocking the mutex. Also, kernel
 * memory where the mutex resides must not be मुक्तd with
 * the mutex still locked. The mutex must first be initialized
 * (or अटलally defined) beक्रमe it can be locked. स_रखो()-ing
 * the mutex to 0 is not allowed.
 *
 * (The CONFIG_DEBUG_MUTEXES .config option turns on debugging
 * checks that will enक्रमce the restrictions and will also करो
 * deadlock debugging)
 *
 * This function is similar to (but not equivalent to) करोwn().
 */
व्योम __sched mutex_lock(काष्ठा mutex *lock)
अणु
	might_sleep();

	अगर (!__mutex_trylock_fast(lock))
		__mutex_lock_slowpath(lock);
पूर्ण
EXPORT_SYMBOL(mutex_lock);
#पूर्ण_अगर

/*
 * Wait-Die:
 *   The newer transactions are समाप्तed when:
 *     It (the new transaction) makes a request क्रम a lock being held
 *     by an older transaction.
 *
 * Wound-Wait:
 *   The newer transactions are wounded when:
 *     An older transaction makes a request क्रम a lock being held by
 *     the newer transaction.
 */

/*
 * Associate the ww_mutex @ww with the context @ww_ctx under which we acquired
 * it.
 */
अटल __always_अंतरभूत व्योम
ww_mutex_lock_acquired(काष्ठा ww_mutex *ww, काष्ठा ww_acquire_ctx *ww_ctx)
अणु
#अगर_घोषित CONFIG_DEBUG_MUTEXES
	/*
	 * If this WARN_ON triggers, you used ww_mutex_lock to acquire,
	 * but released with a normal mutex_unlock in this call.
	 *
	 * This should never happen, always use ww_mutex_unlock.
	 */
	DEBUG_LOCKS_WARN_ON(ww->ctx);

	/*
	 * Not quite करोne after calling ww_acquire_करोne() ?
	 */
	DEBUG_LOCKS_WARN_ON(ww_ctx->करोne_acquire);

	अगर (ww_ctx->contending_lock) अणु
		/*
		 * After -EDEADLK you tried to
		 * acquire a dअगरferent ww_mutex? Bad!
		 */
		DEBUG_LOCKS_WARN_ON(ww_ctx->contending_lock != ww);

		/*
		 * You called ww_mutex_lock after receiving -EDEADLK,
		 * but 'forgot' to unlock everything अन्यथा first?
		 */
		DEBUG_LOCKS_WARN_ON(ww_ctx->acquired > 0);
		ww_ctx->contending_lock = शून्य;
	पूर्ण

	/*
	 * Naughty, using a dअगरferent class will lead to undefined behavior!
	 */
	DEBUG_LOCKS_WARN_ON(ww_ctx->ww_class != ww->ww_class);
#पूर्ण_अगर
	ww_ctx->acquired++;
	ww->ctx = ww_ctx;
पूर्ण

/*
 * Determine अगर context @a is 'after' context @b. IOW, @a is a younger
 * transaction than @b and depending on algorithm either needs to रुको क्रम
 * @b or die.
 */
अटल अंतरभूत bool __sched
__ww_ctx_stamp_after(काष्ठा ww_acquire_ctx *a, काष्ठा ww_acquire_ctx *b)
अणु

	वापस (चिन्हित दीर्घ)(a->stamp - b->stamp) > 0;
पूर्ण

/*
 * Wait-Die; wake a younger रुकोer context (when locks held) such that it can
 * die.
 *
 * Among रुकोers with context, only the first one can have other locks acquired
 * alपढ़ोy (ctx->acquired > 0), because __ww_mutex_add_रुकोer() and
 * __ww_mutex_check_समाप्त() wake any but the earliest context.
 */
अटल bool __sched
__ww_mutex_die(काष्ठा mutex *lock, काष्ठा mutex_रुकोer *रुकोer,
	       काष्ठा ww_acquire_ctx *ww_ctx)
अणु
	अगर (!ww_ctx->is_रुको_die)
		वापस false;

	अगर (रुकोer->ww_ctx->acquired > 0 &&
			__ww_ctx_stamp_after(रुकोer->ww_ctx, ww_ctx)) अणु
		debug_mutex_wake_रुकोer(lock, रुकोer);
		wake_up_process(रुकोer->task);
	पूर्ण

	वापस true;
पूर्ण

/*
 * Wound-Wait; wound a younger @hold_ctx अगर it holds the lock.
 *
 * Wound the lock holder अगर there are रुकोers with older transactions than
 * the lock holders. Even अगर multiple रुकोers may wound the lock holder,
 * it's sufficient that only one करोes.
 */
अटल bool __ww_mutex_wound(काष्ठा mutex *lock,
			     काष्ठा ww_acquire_ctx *ww_ctx,
			     काष्ठा ww_acquire_ctx *hold_ctx)
अणु
	काष्ठा task_काष्ठा *owner = __mutex_owner(lock);

	lockdep_निश्चित_held(&lock->रुको_lock);

	/*
	 * Possible through __ww_mutex_add_रुकोer() when we race with
	 * ww_mutex_set_context_fastpath(). In that हाल we'll get here again
	 * through __ww_mutex_check_रुकोers().
	 */
	अगर (!hold_ctx)
		वापस false;

	/*
	 * Can have !owner because of __mutex_unlock_slowpath(), but अगर owner,
	 * it cannot go away because we'll have FLAG_WAITERS set and hold
	 * रुको_lock.
	 */
	अगर (!owner)
		वापस false;

	अगर (ww_ctx->acquired > 0 && __ww_ctx_stamp_after(hold_ctx, ww_ctx)) अणु
		hold_ctx->wounded = 1;

		/*
		 * wake_up_process() paired with set_current_state()
		 * inserts sufficient barriers to make sure @owner either sees
		 * it's wounded in __ww_mutex_check_समाप्त() or has a
		 * wakeup pending to re-पढ़ो the wounded state.
		 */
		अगर (owner != current)
			wake_up_process(owner);

		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * We just acquired @lock under @ww_ctx, अगर there are later contexts रुकोing
 * behind us on the रुको-list, check अगर they need to die, or wound us.
 *
 * See __ww_mutex_add_रुकोer() क्रम the list-order स्थिरruction; basically the
 * list is ordered by stamp, smallest (oldest) first.
 *
 * This relies on never mixing रुको-die/wound-रुको on the same रुको-list;
 * which is currently ensured by that being a ww_class property.
 *
 * The current task must not be on the रुको list.
 */
अटल व्योम __sched
__ww_mutex_check_रुकोers(काष्ठा mutex *lock, काष्ठा ww_acquire_ctx *ww_ctx)
अणु
	काष्ठा mutex_रुकोer *cur;

	lockdep_निश्चित_held(&lock->रुको_lock);

	list_क्रम_each_entry(cur, &lock->रुको_list, list) अणु
		अगर (!cur->ww_ctx)
			जारी;

		अगर (__ww_mutex_die(lock, cur, ww_ctx) ||
		    __ww_mutex_wound(lock, cur->ww_ctx, ww_ctx))
			अवरोध;
	पूर्ण
पूर्ण

/*
 * After acquiring lock with fastpath, where we करो not hold रुको_lock, set ctx
 * and wake up any रुकोers so they can recheck.
 */
अटल __always_अंतरभूत व्योम
ww_mutex_set_context_fastpath(काष्ठा ww_mutex *lock, काष्ठा ww_acquire_ctx *ctx)
अणु
	ww_mutex_lock_acquired(lock, ctx);

	/*
	 * The lock->ctx update should be visible on all cores beक्रमe
	 * the WAITERS check is करोne, otherwise contended रुकोers might be
	 * missed. The contended रुकोers will either see ww_ctx == शून्य
	 * and keep spinning, or it will acquire रुको_lock, add itself
	 * to रुकोer list and sleep.
	 */
	smp_mb(); /* See comments above and below. */

	/*
	 * [W] ww->ctx = ctx	    [W] MUTEX_FLAG_WAITERS
	 *     MB		        MB
	 * [R] MUTEX_FLAG_WAITERS   [R] ww->ctx
	 *
	 * The memory barrier above pairs with the memory barrier in
	 * __ww_mutex_add_रुकोer() and makes sure we either observe ww->ctx
	 * and/or !empty list.
	 */
	अगर (likely(!(atomic_दीर्घ_पढ़ो(&lock->base.owner) & MUTEX_FLAG_WAITERS)))
		वापस;

	/*
	 * Uh oh, we raced in fastpath, check अगर any of the रुकोers need to
	 * die or wound us.
	 */
	spin_lock(&lock->base.रुको_lock);
	__ww_mutex_check_रुकोers(&lock->base, ctx);
	spin_unlock(&lock->base.रुको_lock);
पूर्ण

#अगर_घोषित CONFIG_MUTEX_SPIN_ON_OWNER

अटल अंतरभूत
bool ww_mutex_spin_on_owner(काष्ठा mutex *lock, काष्ठा ww_acquire_ctx *ww_ctx,
			    काष्ठा mutex_रुकोer *रुकोer)
अणु
	काष्ठा ww_mutex *ww;

	ww = container_of(lock, काष्ठा ww_mutex, base);

	/*
	 * If ww->ctx is set the contents are undefined, only
	 * by acquiring रुको_lock there is a guarantee that
	 * they are not invalid when पढ़ोing.
	 *
	 * As such, when deadlock detection needs to be
	 * perक्रमmed the optimistic spinning cannot be करोne.
	 *
	 * Check this in every inner iteration because we may
	 * be racing against another thपढ़ो's ww_mutex_lock.
	 */
	अगर (ww_ctx->acquired > 0 && READ_ONCE(ww->ctx))
		वापस false;

	/*
	 * If we aren't on the रुको list yet, cancel the spin
	 * अगर there are रुकोers. We want  to aव्योम stealing the
	 * lock from a रुकोer with an earlier stamp, since the
	 * other thपढ़ो may alपढ़ोy own a lock that we also
	 * need.
	 */
	अगर (!रुकोer && (atomic_दीर्घ_पढ़ो(&lock->owner) & MUTEX_FLAG_WAITERS))
		वापस false;

	/*
	 * Similarly, stop spinning अगर we are no दीर्घer the
	 * first रुकोer.
	 */
	अगर (रुकोer && !__mutex_रुकोer_is_first(lock, रुकोer))
		वापस false;

	वापस true;
पूर्ण

/*
 * Look out! "owner" is an entirely speculative poपूर्णांकer access and not
 * reliable.
 *
 * "noinline" so that this function shows up on perf profiles.
 */
अटल noअंतरभूत
bool mutex_spin_on_owner(काष्ठा mutex *lock, काष्ठा task_काष्ठा *owner,
			 काष्ठा ww_acquire_ctx *ww_ctx, काष्ठा mutex_रुकोer *रुकोer)
अणु
	bool ret = true;

	rcu_पढ़ो_lock();
	जबतक (__mutex_owner(lock) == owner) अणु
		/*
		 * Ensure we emit the owner->on_cpu, dereference _after_
		 * checking lock->owner still matches owner. If that fails,
		 * owner might poपूर्णांक to मुक्तd memory. If it still matches,
		 * the rcu_पढ़ो_lock() ensures the memory stays valid.
		 */
		barrier();

		/*
		 * Use vcpu_is_preempted to detect lock holder preemption issue.
		 */
		अगर (!owner->on_cpu || need_resched() ||
				vcpu_is_preempted(task_cpu(owner))) अणु
			ret = false;
			अवरोध;
		पूर्ण

		अगर (ww_ctx && !ww_mutex_spin_on_owner(lock, ww_ctx, रुकोer)) अणु
			ret = false;
			अवरोध;
		पूर्ण

		cpu_relax();
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

/*
 * Initial check क्रम entering the mutex spinning loop
 */
अटल अंतरभूत पूर्णांक mutex_can_spin_on_owner(काष्ठा mutex *lock)
अणु
	काष्ठा task_काष्ठा *owner;
	पूर्णांक retval = 1;

	अगर (need_resched())
		वापस 0;

	rcu_पढ़ो_lock();
	owner = __mutex_owner(lock);

	/*
	 * As lock holder preemption issue, we both skip spinning अगर task is not
	 * on cpu or its cpu is preempted
	 */
	अगर (owner)
		retval = owner->on_cpu && !vcpu_is_preempted(task_cpu(owner));
	rcu_पढ़ो_unlock();

	/*
	 * If lock->owner is not set, the mutex has been released. Return true
	 * such that we'll trylock in the spin path, which is a faster option
	 * than the blocking slow path.
	 */
	वापस retval;
पूर्ण

/*
 * Optimistic spinning.
 *
 * We try to spin क्रम acquisition when we find that the lock owner
 * is currently running on a (dअगरferent) CPU and जबतक we करोn't
 * need to reschedule. The rationale is that अगर the lock owner is
 * running, it is likely to release the lock soon.
 *
 * The mutex spinners are queued up using MCS lock so that only one
 * spinner can compete क्रम the mutex. However, अगर mutex spinning isn't
 * going to happen, there is no poपूर्णांक in going through the lock/unlock
 * overhead.
 *
 * Returns true when the lock was taken, otherwise false, indicating
 * that we need to jump to the slowpath and sleep.
 *
 * The रुकोer flag is set to true अगर the spinner is a रुकोer in the रुको
 * queue. The रुकोer-spinner will spin on the lock directly and concurrently
 * with the spinner at the head of the OSQ, अगर present, until the owner is
 * changed to itself.
 */
अटल __always_अंतरभूत bool
mutex_optimistic_spin(काष्ठा mutex *lock, काष्ठा ww_acquire_ctx *ww_ctx,
		      काष्ठा mutex_रुकोer *रुकोer)
अणु
	अगर (!रुकोer) अणु
		/*
		 * The purpose of the mutex_can_spin_on_owner() function is
		 * to eliminate the overhead of osq_lock() and osq_unlock()
		 * in हाल spinning isn't possible. As a रुकोer-spinner
		 * is not going to take OSQ lock anyway, there is no need
		 * to call mutex_can_spin_on_owner().
		 */
		अगर (!mutex_can_spin_on_owner(lock))
			जाओ fail;

		/*
		 * In order to aव्योम a stampede of mutex spinners trying to
		 * acquire the mutex all at once, the spinners need to take a
		 * MCS (queued) lock first beक्रमe spinning on the owner field.
		 */
		अगर (!osq_lock(&lock->osq))
			जाओ fail;
	पूर्ण

	क्रम (;;) अणु
		काष्ठा task_काष्ठा *owner;

		/* Try to acquire the mutex... */
		owner = __mutex_trylock_or_owner(lock);
		अगर (!owner)
			अवरोध;

		/*
		 * There's an owner, रुको क्रम it to either
		 * release the lock or go to sleep.
		 */
		अगर (!mutex_spin_on_owner(lock, owner, ww_ctx, रुकोer))
			जाओ fail_unlock;

		/*
		 * The cpu_relax() call is a compiler barrier which क्रमces
		 * everything in this loop to be re-loaded. We करोn't need
		 * memory barriers as we'll eventually observe the right
		 * values at the cost of a few extra spins.
		 */
		cpu_relax();
	पूर्ण

	अगर (!रुकोer)
		osq_unlock(&lock->osq);

	वापस true;


fail_unlock:
	अगर (!रुकोer)
		osq_unlock(&lock->osq);

fail:
	/*
	 * If we fell out of the spin path because of need_resched(),
	 * reschedule now, beक्रमe we try-lock the mutex. This aव्योमs getting
	 * scheduled out right after we obtained the mutex.
	 */
	अगर (need_resched()) अणु
		/*
		 * We _should_ have TASK_RUNNING here, but just in हाल
		 * we करो not, make it so, otherwise we might get stuck.
		 */
		__set_current_state(TASK_RUNNING);
		schedule_preempt_disabled();
	पूर्ण

	वापस false;
पूर्ण
#अन्यथा
अटल __always_अंतरभूत bool
mutex_optimistic_spin(काष्ठा mutex *lock, काष्ठा ww_acquire_ctx *ww_ctx,
		      काष्ठा mutex_रुकोer *रुकोer)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

अटल noअंतरभूत व्योम __sched __mutex_unlock_slowpath(काष्ठा mutex *lock, अचिन्हित दीर्घ ip);

/**
 * mutex_unlock - release the mutex
 * @lock: the mutex to be released
 *
 * Unlock a mutex that has been locked by this task previously.
 *
 * This function must not be used in पूर्णांकerrupt context. Unlocking
 * of a not locked mutex is not allowed.
 *
 * This function is similar to (but not equivalent to) up().
 */
व्योम __sched mutex_unlock(काष्ठा mutex *lock)
अणु
#अगर_अघोषित CONFIG_DEBUG_LOCK_ALLOC
	अगर (__mutex_unlock_fast(lock))
		वापस;
#पूर्ण_अगर
	__mutex_unlock_slowpath(lock, _RET_IP_);
पूर्ण
EXPORT_SYMBOL(mutex_unlock);

/**
 * ww_mutex_unlock - release the w/w mutex
 * @lock: the mutex to be released
 *
 * Unlock a mutex that has been locked by this task previously with any of the
 * ww_mutex_lock* functions (with or without an acquire context). It is
 * क्रमbidden to release the locks after releasing the acquire context.
 *
 * This function must not be used in पूर्णांकerrupt context. Unlocking
 * of a unlocked mutex is not allowed.
 */
व्योम __sched ww_mutex_unlock(काष्ठा ww_mutex *lock)
अणु
	/*
	 * The unlocking fastpath is the 0->1 transition from 'locked'
	 * पूर्णांकo 'unlocked' state:
	 */
	अगर (lock->ctx) अणु
#अगर_घोषित CONFIG_DEBUG_MUTEXES
		DEBUG_LOCKS_WARN_ON(!lock->ctx->acquired);
#पूर्ण_अगर
		अगर (lock->ctx->acquired > 0)
			lock->ctx->acquired--;
		lock->ctx = शून्य;
	पूर्ण

	mutex_unlock(&lock->base);
पूर्ण
EXPORT_SYMBOL(ww_mutex_unlock);


अटल __always_अंतरभूत पूर्णांक __sched
__ww_mutex_समाप्त(काष्ठा mutex *lock, काष्ठा ww_acquire_ctx *ww_ctx)
अणु
	अगर (ww_ctx->acquired > 0) अणु
#अगर_घोषित CONFIG_DEBUG_MUTEXES
		काष्ठा ww_mutex *ww;

		ww = container_of(lock, काष्ठा ww_mutex, base);
		DEBUG_LOCKS_WARN_ON(ww_ctx->contending_lock);
		ww_ctx->contending_lock = ww;
#पूर्ण_अगर
		वापस -EDEADLK;
	पूर्ण

	वापस 0;
पूर्ण


/*
 * Check the wound condition क्रम the current lock acquire.
 *
 * Wound-Wait: If we're wounded, समाप्त ourself.
 *
 * Wait-Die: If we're trying to acquire a lock alपढ़ोy held by an older
 *           context, समाप्त ourselves.
 *
 * Since __ww_mutex_add_रुकोer() orders the रुको-list on stamp, we only have to
 * look at रुकोers beक्रमe us in the रुको-list.
 */
अटल अंतरभूत पूर्णांक __sched
__ww_mutex_check_समाप्त(काष्ठा mutex *lock, काष्ठा mutex_रुकोer *रुकोer,
		      काष्ठा ww_acquire_ctx *ctx)
अणु
	काष्ठा ww_mutex *ww = container_of(lock, काष्ठा ww_mutex, base);
	काष्ठा ww_acquire_ctx *hold_ctx = READ_ONCE(ww->ctx);
	काष्ठा mutex_रुकोer *cur;

	अगर (ctx->acquired == 0)
		वापस 0;

	अगर (!ctx->is_रुको_die) अणु
		अगर (ctx->wounded)
			वापस __ww_mutex_समाप्त(lock, ctx);

		वापस 0;
	पूर्ण

	अगर (hold_ctx && __ww_ctx_stamp_after(ctx, hold_ctx))
		वापस __ww_mutex_समाप्त(lock, ctx);

	/*
	 * If there is a रुकोer in front of us that has a context, then its
	 * stamp is earlier than ours and we must समाप्त ourself.
	 */
	cur = रुकोer;
	list_क्रम_each_entry_जारी_reverse(cur, &lock->रुको_list, list) अणु
		अगर (!cur->ww_ctx)
			जारी;

		वापस __ww_mutex_समाप्त(lock, ctx);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Add @रुकोer to the रुको-list, keep the रुको-list ordered by stamp, smallest
 * first. Such that older contexts are preferred to acquire the lock over
 * younger contexts.
 *
 * Waiters without context are पूर्णांकerspersed in FIFO order.
 *
 * Furthermore, क्रम Wait-Die समाप्त ourself immediately when possible (there are
 * older contexts alपढ़ोy रुकोing) to aव्योम unnecessary रुकोing and क्रम
 * Wound-Wait ensure we wound the owning context when it is younger.
 */
अटल अंतरभूत पूर्णांक __sched
__ww_mutex_add_रुकोer(काष्ठा mutex_रुकोer *रुकोer,
		      काष्ठा mutex *lock,
		      काष्ठा ww_acquire_ctx *ww_ctx)
अणु
	काष्ठा mutex_रुकोer *cur;
	काष्ठा list_head *pos;
	bool is_रुको_die;

	अगर (!ww_ctx) अणु
		__mutex_add_रुकोer(lock, रुकोer, &lock->रुको_list);
		वापस 0;
	पूर्ण

	is_रुको_die = ww_ctx->is_रुको_die;

	/*
	 * Add the रुकोer beक्रमe the first रुकोer with a higher stamp.
	 * Waiters without a context are skipped to aव्योम starving
	 * them. Wait-Die रुकोers may die here. Wound-Wait रुकोers
	 * never die here, but they are sorted in stamp order and
	 * may wound the lock holder.
	 */
	pos = &lock->रुको_list;
	list_क्रम_each_entry_reverse(cur, &lock->रुको_list, list) अणु
		अगर (!cur->ww_ctx)
			जारी;

		अगर (__ww_ctx_stamp_after(ww_ctx, cur->ww_ctx)) अणु
			/*
			 * Wait-Die: अगर we find an older context रुकोing, there
			 * is no poपूर्णांक in queueing behind it, as we'd have to
			 * die the moment it would acquire the lock.
			 */
			अगर (is_रुको_die) अणु
				पूर्णांक ret = __ww_mutex_समाप्त(lock, ww_ctx);

				अगर (ret)
					वापस ret;
			पूर्ण

			अवरोध;
		पूर्ण

		pos = &cur->list;

		/* Wait-Die: ensure younger रुकोers die. */
		__ww_mutex_die(lock, cur, ww_ctx);
	पूर्ण

	__mutex_add_रुकोer(lock, रुकोer, pos);

	/*
	 * Wound-Wait: अगर we're blocking on a mutex owned by a younger context,
	 * wound that such that we might proceed.
	 */
	अगर (!is_रुको_die) अणु
		काष्ठा ww_mutex *ww = container_of(lock, काष्ठा ww_mutex, base);

		/*
		 * See ww_mutex_set_context_fastpath(). Orders setting
		 * MUTEX_FLAG_WAITERS vs the ww->ctx load,
		 * such that either we or the fastpath will wound @ww->ctx.
		 */
		smp_mb();
		__ww_mutex_wound(lock, ww_ctx, ww->ctx);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Lock a mutex (possibly पूर्णांकerruptible), slowpath:
 */
अटल __always_अंतरभूत पूर्णांक __sched
__mutex_lock_common(काष्ठा mutex *lock, दीर्घ state, अचिन्हित पूर्णांक subclass,
		    काष्ठा lockdep_map *nest_lock, अचिन्हित दीर्घ ip,
		    काष्ठा ww_acquire_ctx *ww_ctx, स्थिर bool use_ww_ctx)
अणु
	काष्ठा mutex_रुकोer रुकोer;
	bool first = false;
	काष्ठा ww_mutex *ww;
	पूर्णांक ret;

	अगर (!use_ww_ctx)
		ww_ctx = शून्य;

	might_sleep();

#अगर_घोषित CONFIG_DEBUG_MUTEXES
	DEBUG_LOCKS_WARN_ON(lock->magic != lock);
#पूर्ण_अगर

	ww = container_of(lock, काष्ठा ww_mutex, base);
	अगर (ww_ctx) अणु
		अगर (unlikely(ww_ctx == READ_ONCE(ww->ctx)))
			वापस -EALREADY;

		/*
		 * Reset the wounded flag after a समाप्त. No other process can
		 * race and wound us here since they can't have a valid owner
		 * poपूर्णांकer अगर we करोn't have any locks held.
		 */
		अगर (ww_ctx->acquired == 0)
			ww_ctx->wounded = 0;
	पूर्ण

	preempt_disable();
	mutex_acquire_nest(&lock->dep_map, subclass, 0, nest_lock, ip);

	अगर (__mutex_trylock(lock) ||
	    mutex_optimistic_spin(lock, ww_ctx, शून्य)) अणु
		/* got the lock, yay! */
		lock_acquired(&lock->dep_map, ip);
		अगर (ww_ctx)
			ww_mutex_set_context_fastpath(ww, ww_ctx);
		preempt_enable();
		वापस 0;
	पूर्ण

	spin_lock(&lock->रुको_lock);
	/*
	 * After रुकोing to acquire the रुको_lock, try again.
	 */
	अगर (__mutex_trylock(lock)) अणु
		अगर (ww_ctx)
			__ww_mutex_check_रुकोers(lock, ww_ctx);

		जाओ skip_रुको;
	पूर्ण

	debug_mutex_lock_common(lock, &रुकोer);

	lock_contended(&lock->dep_map, ip);

	अगर (!use_ww_ctx) अणु
		/* add रुकोing tasks to the end of the रुकोqueue (FIFO): */
		__mutex_add_रुकोer(lock, &रुकोer, &lock->रुको_list);


#अगर_घोषित CONFIG_DEBUG_MUTEXES
		रुकोer.ww_ctx = MUTEX_POISON_WW_CTX;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		/*
		 * Add in stamp order, waking up रुकोers that must समाप्त
		 * themselves.
		 */
		ret = __ww_mutex_add_रुकोer(&रुकोer, lock, ww_ctx);
		अगर (ret)
			जाओ err_early_समाप्त;

		रुकोer.ww_ctx = ww_ctx;
	पूर्ण

	रुकोer.task = current;

	set_current_state(state);
	क्रम (;;) अणु
		/*
		 * Once we hold रुको_lock, we're serialized against
		 * mutex_unlock() handing the lock off to us, करो a trylock
		 * beक्रमe testing the error conditions to make sure we pick up
		 * the hanकरोff.
		 */
		अगर (__mutex_trylock(lock))
			जाओ acquired;

		/*
		 * Check क्रम संकेतs and समाप्त conditions जबतक holding
		 * रुको_lock. This ensures the lock cancellation is ordered
		 * against mutex_unlock() and wake-ups करो not go missing.
		 */
		अगर (संकेत_pending_state(state, current)) अणु
			ret = -EINTR;
			जाओ err;
		पूर्ण

		अगर (ww_ctx) अणु
			ret = __ww_mutex_check_समाप्त(lock, &रुकोer, ww_ctx);
			अगर (ret)
				जाओ err;
		पूर्ण

		spin_unlock(&lock->रुको_lock);
		schedule_preempt_disabled();

		/*
		 * ww_mutex needs to always recheck its position since its रुकोer
		 * list is not FIFO ordered.
		 */
		अगर (ww_ctx || !first) अणु
			first = __mutex_रुकोer_is_first(lock, &रुकोer);
			अगर (first)
				__mutex_set_flag(lock, MUTEX_FLAG_HANDOFF);
		पूर्ण

		set_current_state(state);
		/*
		 * Here we order against unlock; we must either see it change
		 * state back to RUNNING and fall through the next schedule(),
		 * or we must see its unlock and acquire.
		 */
		अगर (__mutex_trylock(lock) ||
		    (first && mutex_optimistic_spin(lock, ww_ctx, &रुकोer)))
			अवरोध;

		spin_lock(&lock->रुको_lock);
	पूर्ण
	spin_lock(&lock->रुको_lock);
acquired:
	__set_current_state(TASK_RUNNING);

	अगर (ww_ctx) अणु
		/*
		 * Wound-Wait; we stole the lock (!first_रुकोer), check the
		 * रुकोers as anyone might want to wound us.
		 */
		अगर (!ww_ctx->is_रुको_die &&
		    !__mutex_रुकोer_is_first(lock, &रुकोer))
			__ww_mutex_check_रुकोers(lock, ww_ctx);
	पूर्ण

	__mutex_हटाओ_रुकोer(lock, &रुकोer);

	debug_mutex_मुक्त_रुकोer(&रुकोer);

skip_रुको:
	/* got the lock - cleanup and rejoice! */
	lock_acquired(&lock->dep_map, ip);

	अगर (ww_ctx)
		ww_mutex_lock_acquired(ww, ww_ctx);

	spin_unlock(&lock->रुको_lock);
	preempt_enable();
	वापस 0;

err:
	__set_current_state(TASK_RUNNING);
	__mutex_हटाओ_रुकोer(lock, &रुकोer);
err_early_समाप्त:
	spin_unlock(&lock->रुको_lock);
	debug_mutex_मुक्त_रुकोer(&रुकोer);
	mutex_release(&lock->dep_map, ip);
	preempt_enable();
	वापस ret;
पूर्ण

अटल पूर्णांक __sched
__mutex_lock(काष्ठा mutex *lock, दीर्घ state, अचिन्हित पूर्णांक subclass,
	     काष्ठा lockdep_map *nest_lock, अचिन्हित दीर्घ ip)
अणु
	वापस __mutex_lock_common(lock, state, subclass, nest_lock, ip, शून्य, false);
पूर्ण

अटल पूर्णांक __sched
__ww_mutex_lock(काष्ठा mutex *lock, दीर्घ state, अचिन्हित पूर्णांक subclass,
		काष्ठा lockdep_map *nest_lock, अचिन्हित दीर्घ ip,
		काष्ठा ww_acquire_ctx *ww_ctx)
अणु
	वापस __mutex_lock_common(lock, state, subclass, nest_lock, ip, ww_ctx, true);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
व्योम __sched
mutex_lock_nested(काष्ठा mutex *lock, अचिन्हित पूर्णांक subclass)
अणु
	__mutex_lock(lock, TASK_UNINTERRUPTIBLE, subclass, शून्य, _RET_IP_);
पूर्ण

EXPORT_SYMBOL_GPL(mutex_lock_nested);

व्योम __sched
_mutex_lock_nest_lock(काष्ठा mutex *lock, काष्ठा lockdep_map *nest)
अणु
	__mutex_lock(lock, TASK_UNINTERRUPTIBLE, 0, nest, _RET_IP_);
पूर्ण
EXPORT_SYMBOL_GPL(_mutex_lock_nest_lock);

पूर्णांक __sched
mutex_lock_समाप्तable_nested(काष्ठा mutex *lock, अचिन्हित पूर्णांक subclass)
अणु
	वापस __mutex_lock(lock, TASK_KILLABLE, subclass, शून्य, _RET_IP_);
पूर्ण
EXPORT_SYMBOL_GPL(mutex_lock_समाप्तable_nested);

पूर्णांक __sched
mutex_lock_पूर्णांकerruptible_nested(काष्ठा mutex *lock, अचिन्हित पूर्णांक subclass)
अणु
	वापस __mutex_lock(lock, TASK_INTERRUPTIBLE, subclass, शून्य, _RET_IP_);
पूर्ण
EXPORT_SYMBOL_GPL(mutex_lock_पूर्णांकerruptible_nested);

व्योम __sched
mutex_lock_io_nested(काष्ठा mutex *lock, अचिन्हित पूर्णांक subclass)
अणु
	पूर्णांक token;

	might_sleep();

	token = io_schedule_prepare();
	__mutex_lock_common(lock, TASK_UNINTERRUPTIBLE,
			    subclass, शून्य, _RET_IP_, शून्य, 0);
	io_schedule_finish(token);
पूर्ण
EXPORT_SYMBOL_GPL(mutex_lock_io_nested);

अटल अंतरभूत पूर्णांक
ww_mutex_deadlock_injection(काष्ठा ww_mutex *lock, काष्ठा ww_acquire_ctx *ctx)
अणु
#अगर_घोषित CONFIG_DEBUG_WW_MUTEX_SLOWPATH
	अचिन्हित पंचांगp;

	अगर (ctx->deadlock_inject_countकरोwn-- == 0) अणु
		पंचांगp = ctx->deadlock_inject_पूर्णांकerval;
		अगर (पंचांगp > अच_पूर्णांक_उच्च/4)
			पंचांगp = अच_पूर्णांक_उच्च;
		अन्यथा
			पंचांगp = पंचांगp*2 + पंचांगp + पंचांगp/2;

		ctx->deadlock_inject_पूर्णांकerval = पंचांगp;
		ctx->deadlock_inject_countकरोwn = पंचांगp;
		ctx->contending_lock = lock;

		ww_mutex_unlock(lock);

		वापस -EDEADLK;
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

पूर्णांक __sched
ww_mutex_lock(काष्ठा ww_mutex *lock, काष्ठा ww_acquire_ctx *ctx)
अणु
	पूर्णांक ret;

	might_sleep();
	ret =  __ww_mutex_lock(&lock->base, TASK_UNINTERRUPTIBLE,
			       0, ctx ? &ctx->dep_map : शून्य, _RET_IP_,
			       ctx);
	अगर (!ret && ctx && ctx->acquired > 1)
		वापस ww_mutex_deadlock_injection(lock, ctx);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ww_mutex_lock);

पूर्णांक __sched
ww_mutex_lock_पूर्णांकerruptible(काष्ठा ww_mutex *lock, काष्ठा ww_acquire_ctx *ctx)
अणु
	पूर्णांक ret;

	might_sleep();
	ret = __ww_mutex_lock(&lock->base, TASK_INTERRUPTIBLE,
			      0, ctx ? &ctx->dep_map : शून्य, _RET_IP_,
			      ctx);

	अगर (!ret && ctx && ctx->acquired > 1)
		वापस ww_mutex_deadlock_injection(lock, ctx);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ww_mutex_lock_पूर्णांकerruptible);

#पूर्ण_अगर

/*
 * Release the lock, slowpath:
 */
अटल noअंतरभूत व्योम __sched __mutex_unlock_slowpath(काष्ठा mutex *lock, अचिन्हित दीर्घ ip)
अणु
	काष्ठा task_काष्ठा *next = शून्य;
	DEFINE_WAKE_Q(wake_q);
	अचिन्हित दीर्घ owner;

	mutex_release(&lock->dep_map, ip);

	/*
	 * Release the lock beक्रमe (potentially) taking the spinlock such that
	 * other contenders can get on with things ASAP.
	 *
	 * Except when HANDOFF, in that हाल we must not clear the owner field,
	 * but instead set it to the top रुकोer.
	 */
	owner = atomic_दीर्घ_पढ़ो(&lock->owner);
	क्रम (;;) अणु
		अचिन्हित दीर्घ old;

#अगर_घोषित CONFIG_DEBUG_MUTEXES
		DEBUG_LOCKS_WARN_ON(__owner_task(owner) != current);
		DEBUG_LOCKS_WARN_ON(owner & MUTEX_FLAG_PICKUP);
#पूर्ण_अगर

		अगर (owner & MUTEX_FLAG_HANDOFF)
			अवरोध;

		old = atomic_दीर्घ_cmpxchg_release(&lock->owner, owner,
						  __owner_flags(owner));
		अगर (old == owner) अणु
			अगर (owner & MUTEX_FLAG_WAITERS)
				अवरोध;

			वापस;
		पूर्ण

		owner = old;
	पूर्ण

	spin_lock(&lock->रुको_lock);
	debug_mutex_unlock(lock);
	अगर (!list_empty(&lock->रुको_list)) अणु
		/* get the first entry from the रुको-list: */
		काष्ठा mutex_रुकोer *रुकोer =
			list_first_entry(&lock->रुको_list,
					 काष्ठा mutex_रुकोer, list);

		next = रुकोer->task;

		debug_mutex_wake_रुकोer(lock, रुकोer);
		wake_q_add(&wake_q, next);
	पूर्ण

	अगर (owner & MUTEX_FLAG_HANDOFF)
		__mutex_hanकरोff(lock, next);

	spin_unlock(&lock->रुको_lock);

	wake_up_q(&wake_q);
पूर्ण

#अगर_अघोषित CONFIG_DEBUG_LOCK_ALLOC
/*
 * Here come the less common (and hence less perक्रमmance-critical) APIs:
 * mutex_lock_पूर्णांकerruptible() and mutex_trylock().
 */
अटल noअंतरभूत पूर्णांक __sched
__mutex_lock_समाप्तable_slowpath(काष्ठा mutex *lock);

अटल noअंतरभूत पूर्णांक __sched
__mutex_lock_पूर्णांकerruptible_slowpath(काष्ठा mutex *lock);

/**
 * mutex_lock_पूर्णांकerruptible() - Acquire the mutex, पूर्णांकerruptible by संकेतs.
 * @lock: The mutex to be acquired.
 *
 * Lock the mutex like mutex_lock().  If a संकेत is delivered जबतक the
 * process is sleeping, this function will वापस without acquiring the
 * mutex.
 *
 * Context: Process context.
 * Return: 0 अगर the lock was successfully acquired or %-EINTR अगर a
 * संकेत arrived.
 */
पूर्णांक __sched mutex_lock_पूर्णांकerruptible(काष्ठा mutex *lock)
अणु
	might_sleep();

	अगर (__mutex_trylock_fast(lock))
		वापस 0;

	वापस __mutex_lock_पूर्णांकerruptible_slowpath(lock);
पूर्ण

EXPORT_SYMBOL(mutex_lock_पूर्णांकerruptible);

/**
 * mutex_lock_समाप्तable() - Acquire the mutex, पूर्णांकerruptible by fatal संकेतs.
 * @lock: The mutex to be acquired.
 *
 * Lock the mutex like mutex_lock().  If a संकेत which will be fatal to
 * the current process is delivered जबतक the process is sleeping, this
 * function will वापस without acquiring the mutex.
 *
 * Context: Process context.
 * Return: 0 अगर the lock was successfully acquired or %-EINTR अगर a
 * fatal संकेत arrived.
 */
पूर्णांक __sched mutex_lock_समाप्तable(काष्ठा mutex *lock)
अणु
	might_sleep();

	अगर (__mutex_trylock_fast(lock))
		वापस 0;

	वापस __mutex_lock_समाप्तable_slowpath(lock);
पूर्ण
EXPORT_SYMBOL(mutex_lock_समाप्तable);

/**
 * mutex_lock_io() - Acquire the mutex and mark the process as रुकोing क्रम I/O
 * @lock: The mutex to be acquired.
 *
 * Lock the mutex like mutex_lock().  While the task is रुकोing क्रम this
 * mutex, it will be accounted as being in the IO रुको state by the
 * scheduler.
 *
 * Context: Process context.
 */
व्योम __sched mutex_lock_io(काष्ठा mutex *lock)
अणु
	पूर्णांक token;

	token = io_schedule_prepare();
	mutex_lock(lock);
	io_schedule_finish(token);
पूर्ण
EXPORT_SYMBOL_GPL(mutex_lock_io);

अटल noअंतरभूत व्योम __sched
__mutex_lock_slowpath(काष्ठा mutex *lock)
अणु
	__mutex_lock(lock, TASK_UNINTERRUPTIBLE, 0, शून्य, _RET_IP_);
पूर्ण

अटल noअंतरभूत पूर्णांक __sched
__mutex_lock_समाप्तable_slowpath(काष्ठा mutex *lock)
अणु
	वापस __mutex_lock(lock, TASK_KILLABLE, 0, शून्य, _RET_IP_);
पूर्ण

अटल noअंतरभूत पूर्णांक __sched
__mutex_lock_पूर्णांकerruptible_slowpath(काष्ठा mutex *lock)
अणु
	वापस __mutex_lock(lock, TASK_INTERRUPTIBLE, 0, शून्य, _RET_IP_);
पूर्ण

अटल noअंतरभूत पूर्णांक __sched
__ww_mutex_lock_slowpath(काष्ठा ww_mutex *lock, काष्ठा ww_acquire_ctx *ctx)
अणु
	वापस __ww_mutex_lock(&lock->base, TASK_UNINTERRUPTIBLE, 0, शून्य,
			       _RET_IP_, ctx);
पूर्ण

अटल noअंतरभूत पूर्णांक __sched
__ww_mutex_lock_पूर्णांकerruptible_slowpath(काष्ठा ww_mutex *lock,
					    काष्ठा ww_acquire_ctx *ctx)
अणु
	वापस __ww_mutex_lock(&lock->base, TASK_INTERRUPTIBLE, 0, शून्य,
			       _RET_IP_, ctx);
पूर्ण

#पूर्ण_अगर

/**
 * mutex_trylock - try to acquire the mutex, without रुकोing
 * @lock: the mutex to be acquired
 *
 * Try to acquire the mutex atomically. Returns 1 अगर the mutex
 * has been acquired successfully, and 0 on contention.
 *
 * NOTE: this function follows the spin_trylock() convention, so
 * it is negated from the करोwn_trylock() वापस values! Be careful
 * about this when converting semaphore users to mutexes.
 *
 * This function must not be used in पूर्णांकerrupt context. The
 * mutex must be released by the same task that acquired it.
 */
पूर्णांक __sched mutex_trylock(काष्ठा mutex *lock)
अणु
	bool locked;

#अगर_घोषित CONFIG_DEBUG_MUTEXES
	DEBUG_LOCKS_WARN_ON(lock->magic != lock);
#पूर्ण_अगर

	locked = __mutex_trylock(lock);
	अगर (locked)
		mutex_acquire(&lock->dep_map, 0, 1, _RET_IP_);

	वापस locked;
पूर्ण
EXPORT_SYMBOL(mutex_trylock);

#अगर_अघोषित CONFIG_DEBUG_LOCK_ALLOC
पूर्णांक __sched
ww_mutex_lock(काष्ठा ww_mutex *lock, काष्ठा ww_acquire_ctx *ctx)
अणु
	might_sleep();

	अगर (__mutex_trylock_fast(&lock->base)) अणु
		अगर (ctx)
			ww_mutex_set_context_fastpath(lock, ctx);
		वापस 0;
	पूर्ण

	वापस __ww_mutex_lock_slowpath(lock, ctx);
पूर्ण
EXPORT_SYMBOL(ww_mutex_lock);

पूर्णांक __sched
ww_mutex_lock_पूर्णांकerruptible(काष्ठा ww_mutex *lock, काष्ठा ww_acquire_ctx *ctx)
अणु
	might_sleep();

	अगर (__mutex_trylock_fast(&lock->base)) अणु
		अगर (ctx)
			ww_mutex_set_context_fastpath(lock, ctx);
		वापस 0;
	पूर्ण

	वापस __ww_mutex_lock_पूर्णांकerruptible_slowpath(lock, ctx);
पूर्ण
EXPORT_SYMBOL(ww_mutex_lock_पूर्णांकerruptible);

#पूर्ण_अगर

/**
 * atomic_dec_and_mutex_lock - वापस holding mutex अगर we dec to 0
 * @cnt: the atomic which we are to dec
 * @lock: the mutex to वापस holding अगर we dec to 0
 *
 * वापस true and hold lock अगर we dec to 0, वापस false otherwise
 */
पूर्णांक atomic_dec_and_mutex_lock(atomic_t *cnt, काष्ठा mutex *lock)
अणु
	/* dec अगर we can't possibly hit 0 */
	अगर (atomic_add_unless(cnt, -1, 1))
		वापस 0;
	/* we might hit 0, so take the lock */
	mutex_lock(lock);
	अगर (!atomic_dec_and_test(cnt)) अणु
		/* when we actually did the dec, we didn't hit 0 */
		mutex_unlock(lock);
		वापस 0;
	पूर्ण
	/* we hit 0, and we hold the lock */
	वापस 1;
पूर्ण
EXPORT_SYMBOL(atomic_dec_and_mutex_lock);
