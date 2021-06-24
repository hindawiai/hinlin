<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* kernel/rwsem.c: R/W semaphores, खुला implementation
 *
 * Written by David Howells (dhowells@redhat.com).
 * Derived from यंत्र-i386/semaphore.h
 *
 * Writer lock-stealing by Alex Shi <alex.shi@पूर्णांकel.com>
 * and Michel Lespinasse <walken@google.com>
 *
 * Optimistic spinning by Tim Chen <tim.c.chen@पूर्णांकel.com>
 * and Davidlohr Bueso <davidlohr@hp.com>. Based on mutexes.
 *
 * Rwsem count bit fields re-definition and rwsem rearchitecture by
 * Waiman Long <दीर्घman@redhat.com> and
 * Peter Zijlstra <peterz@infradead.org>.
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/rt.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/wake_q.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/export.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/atomic.h>

#समावेश "lock_events.h"

/*
 * The least signअगरicant 2 bits of the owner value has the following
 * meanings when set.
 *  - Bit 0: RWSEM_READER_OWNED - The rwsem is owned by पढ़ोers
 *  - Bit 1: RWSEM_NONSPINNABLE - Cannot spin on a पढ़ोer-owned lock
 *
 * When the rwsem is पढ़ोer-owned and a spinning ग_लिखोr has समयd out,
 * the nonspinnable bit will be set to disable optimistic spinning.

 * When a ग_लिखोr acquires a rwsem, it माला_दो its task_काष्ठा poपूर्णांकer
 * पूर्णांकo the owner field. It is cleared after an unlock.
 *
 * When a पढ़ोer acquires a rwsem, it will also माला_दो its task_काष्ठा
 * poपूर्णांकer पूर्णांकo the owner field with the RWSEM_READER_OWNED bit set.
 * On unlock, the owner field will largely be left untouched. So
 * क्रम a मुक्त or पढ़ोer-owned rwsem, the owner value may contain
 * inक्रमmation about the last पढ़ोer that acquires the rwsem.
 *
 * That inक्रमmation may be helpful in debugging हालs where the प्रणाली
 * seems to hang on a पढ़ोer owned rwsem especially अगर only one पढ़ोer
 * is involved. Ideally we would like to track all the पढ़ोers that own
 * a rwsem, but the overhead is simply too big.
 *
 * A fast path पढ़ोer optimistic lock stealing is supported when the rwsem
 * is previously owned by a ग_लिखोr and the following conditions are met:
 *  - OSQ is empty
 *  - rwsem is not currently ग_लिखोr owned
 *  - the hanकरोff isn't set.
 */
#घोषणा RWSEM_READER_OWNED	(1UL << 0)
#घोषणा RWSEM_NONSPINNABLE	(1UL << 1)
#घोषणा RWSEM_OWNER_FLAGS_MASK	(RWSEM_READER_OWNED | RWSEM_NONSPINNABLE)

#अगर_घोषित CONFIG_DEBUG_RWSEMS
# define DEBUG_RWSEMS_WARN_ON(c, sem)	करो अणु			\
	अगर (!debug_locks_silent &&				\
	    WARN_ONCE(c, "DEBUG_RWSEMS_WARN_ON(%s): count = 0x%lx, magic = 0x%lx, owner = 0x%lx, curr 0x%lx, list %sempty\n",\
		#c, atomic_दीर्घ_पढ़ो(&(sem)->count),		\
		(अचिन्हित दीर्घ) sem->magic,			\
		atomic_दीर्घ_पढ़ो(&(sem)->owner), (दीर्घ)current,	\
		list_empty(&(sem)->रुको_list) ? "" : "not "))	\
			debug_locks_off();			\
	पूर्ण जबतक (0)
#अन्यथा
# define DEBUG_RWSEMS_WARN_ON(c, sem)
#पूर्ण_अगर

/*
 * On 64-bit architectures, the bit definitions of the count are:
 *
 * Bit  0    - ग_लिखोr locked bit
 * Bit  1    - रुकोers present bit
 * Bit  2    - lock hanकरोff bit
 * Bits 3-7  - reserved
 * Bits 8-62 - 55-bit पढ़ोer count
 * Bit  63   - पढ़ो fail bit
 *
 * On 32-bit architectures, the bit definitions of the count are:
 *
 * Bit  0    - ग_लिखोr locked bit
 * Bit  1    - रुकोers present bit
 * Bit  2    - lock hanकरोff bit
 * Bits 3-7  - reserved
 * Bits 8-30 - 23-bit पढ़ोer count
 * Bit  31   - पढ़ो fail bit
 *
 * It is not likely that the most signअगरicant bit (पढ़ो fail bit) will ever
 * be set. This guard bit is still checked anyway in the करोwn_पढ़ो() fastpath
 * just in हाल we need to use up more of the पढ़ोer bits क्रम other purpose
 * in the future.
 *
 * atomic_दीर्घ_fetch_add() is used to obtain पढ़ोer lock, whereas
 * atomic_दीर्घ_cmpxchg() will be used to obtain ग_लिखोr lock.
 *
 * There are three places where the lock hanकरोff bit may be set or cleared.
 * 1) rwsem_mark_wake() क्रम पढ़ोers.
 * 2) rwsem_try_ग_लिखो_lock() क्रम ग_लिखोrs.
 * 3) Error path of rwsem_करोwn_ग_लिखो_slowpath().
 *
 * For all the above हालs, रुको_lock will be held. A ग_लिखोr must also
 * be the first one in the रुको_list to be eligible क्रम setting the hanकरोff
 * bit. So concurrent setting/clearing of hanकरोff bit is not possible.
 */
#घोषणा RWSEM_WRITER_LOCKED	(1UL << 0)
#घोषणा RWSEM_FLAG_WAITERS	(1UL << 1)
#घोषणा RWSEM_FLAG_HANDOFF	(1UL << 2)
#घोषणा RWSEM_FLAG_READFAIL	(1UL << (BITS_PER_LONG - 1))

#घोषणा RWSEM_READER_SHIFT	8
#घोषणा RWSEM_READER_BIAS	(1UL << RWSEM_READER_SHIFT)
#घोषणा RWSEM_READER_MASK	(~(RWSEM_READER_BIAS - 1))
#घोषणा RWSEM_WRITER_MASK	RWSEM_WRITER_LOCKED
#घोषणा RWSEM_LOCK_MASK		(RWSEM_WRITER_MASK|RWSEM_READER_MASK)
#घोषणा RWSEM_READ_FAILED_MASK	(RWSEM_WRITER_MASK|RWSEM_FLAG_WAITERS|\
				 RWSEM_FLAG_HANDOFF|RWSEM_FLAG_READFAIL)

/*
 * All ग_लिखोs to owner are रक्षित by WRITE_ONCE() to make sure that
 * store tearing can't happen as optimistic spinners may पढ़ो and use
 * the owner value concurrently without lock. Read from owner, however,
 * may not need READ_ONCE() as दीर्घ as the poपूर्णांकer value is only used
 * क्रम comparison and isn't being dereferenced.
 */
अटल अंतरभूत व्योम rwsem_set_owner(काष्ठा rw_semaphore *sem)
अणु
	atomic_दीर्घ_set(&sem->owner, (दीर्घ)current);
पूर्ण

अटल अंतरभूत व्योम rwsem_clear_owner(काष्ठा rw_semaphore *sem)
अणु
	atomic_दीर्घ_set(&sem->owner, 0);
पूर्ण

/*
 * Test the flags in the owner field.
 */
अटल अंतरभूत bool rwsem_test_oflags(काष्ठा rw_semaphore *sem, दीर्घ flags)
अणु
	वापस atomic_दीर्घ_पढ़ो(&sem->owner) & flags;
पूर्ण

/*
 * The task_काष्ठा poपूर्णांकer of the last owning पढ़ोer will be left in
 * the owner field.
 *
 * Note that the owner value just indicates the task has owned the rwsem
 * previously, it may not be the real owner or one of the real owners
 * anymore when that field is examined, so take it with a grain of salt.
 *
 * The पढ़ोer non-spinnable bit is preserved.
 */
अटल अंतरभूत व्योम __rwsem_set_पढ़ोer_owned(काष्ठा rw_semaphore *sem,
					    काष्ठा task_काष्ठा *owner)
अणु
	अचिन्हित दीर्घ val = (अचिन्हित दीर्घ)owner | RWSEM_READER_OWNED |
		(atomic_दीर्घ_पढ़ो(&sem->owner) & RWSEM_NONSPINNABLE);

	atomic_दीर्घ_set(&sem->owner, val);
पूर्ण

अटल अंतरभूत व्योम rwsem_set_पढ़ोer_owned(काष्ठा rw_semaphore *sem)
अणु
	__rwsem_set_पढ़ोer_owned(sem, current);
पूर्ण

/*
 * Return true अगर the rwsem is owned by a पढ़ोer.
 */
अटल अंतरभूत bool is_rwsem_पढ़ोer_owned(काष्ठा rw_semaphore *sem)
अणु
#अगर_घोषित CONFIG_DEBUG_RWSEMS
	/*
	 * Check the count to see अगर it is ग_लिखो-locked.
	 */
	दीर्घ count = atomic_दीर्घ_पढ़ो(&sem->count);

	अगर (count & RWSEM_WRITER_MASK)
		वापस false;
#पूर्ण_अगर
	वापस rwsem_test_oflags(sem, RWSEM_READER_OWNED);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_RWSEMS
/*
 * With CONFIG_DEBUG_RWSEMS configured, it will make sure that अगर there
 * is a task poपूर्णांकer in owner of a पढ़ोer-owned rwsem, it will be the
 * real owner or one of the real owners. The only exception is when the
 * unlock is करोne by up_पढ़ो_non_owner().
 */
अटल अंतरभूत व्योम rwsem_clear_पढ़ोer_owned(काष्ठा rw_semaphore *sem)
अणु
	अचिन्हित दीर्घ val = atomic_दीर्घ_पढ़ो(&sem->owner);

	जबतक ((val & ~RWSEM_OWNER_FLAGS_MASK) == (अचिन्हित दीर्घ)current) अणु
		अगर (atomic_दीर्घ_try_cmpxchg(&sem->owner, &val,
					    val & RWSEM_OWNER_FLAGS_MASK))
			वापस;
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम rwsem_clear_पढ़ोer_owned(काष्ठा rw_semaphore *sem)
अणु
पूर्ण
#पूर्ण_अगर

/*
 * Set the RWSEM_NONSPINNABLE bits अगर the RWSEM_READER_OWNED flag
 * reमुख्यs set. Otherwise, the operation will be पातed.
 */
अटल अंतरभूत व्योम rwsem_set_nonspinnable(काष्ठा rw_semaphore *sem)
अणु
	अचिन्हित दीर्घ owner = atomic_दीर्घ_पढ़ो(&sem->owner);

	करो अणु
		अगर (!(owner & RWSEM_READER_OWNED))
			अवरोध;
		अगर (owner & RWSEM_NONSPINNABLE)
			अवरोध;
	पूर्ण जबतक (!atomic_दीर्घ_try_cmpxchg(&sem->owner, &owner,
					  owner | RWSEM_NONSPINNABLE));
पूर्ण

अटल अंतरभूत bool rwsem_पढ़ो_trylock(काष्ठा rw_semaphore *sem, दीर्घ *cntp)
अणु
	*cntp = atomic_दीर्घ_add_वापस_acquire(RWSEM_READER_BIAS, &sem->count);

	अगर (WARN_ON_ONCE(*cntp < 0))
		rwsem_set_nonspinnable(sem);

	अगर (!(*cntp & RWSEM_READ_FAILED_MASK)) अणु
		rwsem_set_पढ़ोer_owned(sem);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल अंतरभूत bool rwsem_ग_लिखो_trylock(काष्ठा rw_semaphore *sem)
अणु
	दीर्घ पंचांगp = RWSEM_UNLOCKED_VALUE;

	अगर (atomic_दीर्घ_try_cmpxchg_acquire(&sem->count, &पंचांगp, RWSEM_WRITER_LOCKED)) अणु
		rwsem_set_owner(sem);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * Return just the real task काष्ठाure poपूर्णांकer of the owner
 */
अटल अंतरभूत काष्ठा task_काष्ठा *rwsem_owner(काष्ठा rw_semaphore *sem)
अणु
	वापस (काष्ठा task_काष्ठा *)
		(atomic_दीर्घ_पढ़ो(&sem->owner) & ~RWSEM_OWNER_FLAGS_MASK);
पूर्ण

/*
 * Return the real task काष्ठाure poपूर्णांकer of the owner and the embedded
 * flags in the owner. pflags must be non-शून्य.
 */
अटल अंतरभूत काष्ठा task_काष्ठा *
rwsem_owner_flags(काष्ठा rw_semaphore *sem, अचिन्हित दीर्घ *pflags)
अणु
	अचिन्हित दीर्घ owner = atomic_दीर्घ_पढ़ो(&sem->owner);

	*pflags = owner & RWSEM_OWNER_FLAGS_MASK;
	वापस (काष्ठा task_काष्ठा *)(owner & ~RWSEM_OWNER_FLAGS_MASK);
पूर्ण

/*
 * Guide to the rw_semaphore's count field.
 *
 * When the RWSEM_WRITER_LOCKED bit in count is set, the lock is owned
 * by a ग_लिखोr.
 *
 * The lock is owned by पढ़ोers when
 * (1) the RWSEM_WRITER_LOCKED isn't set in count,
 * (2) some of the पढ़ोer bits are set in count, and
 * (3) the owner field has RWSEM_READ_OWNED bit set.
 *
 * Having some पढ़ोer bits set is not enough to guarantee a पढ़ोers owned
 * lock as the पढ़ोers may be in the process of backing out from the count
 * and a ग_लिखोr has just released the lock. So another ग_लिखोr may steal
 * the lock immediately after that.
 */

/*
 * Initialize an rwsem:
 */
व्योम __init_rwsem(काष्ठा rw_semaphore *sem, स्थिर अक्षर *name,
		  काष्ठा lock_class_key *key)
अणु
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	/*
	 * Make sure we are not reinitializing a held semaphore:
	 */
	debug_check_no_locks_मुक्तd((व्योम *)sem, माप(*sem));
	lockdep_init_map_रुको(&sem->dep_map, name, key, 0, LD_WAIT_SLEEP);
#पूर्ण_अगर
#अगर_घोषित CONFIG_DEBUG_RWSEMS
	sem->magic = sem;
#पूर्ण_अगर
	atomic_दीर्घ_set(&sem->count, RWSEM_UNLOCKED_VALUE);
	raw_spin_lock_init(&sem->रुको_lock);
	INIT_LIST_HEAD(&sem->रुको_list);
	atomic_दीर्घ_set(&sem->owner, 0L);
#अगर_घोषित CONFIG_RWSEM_SPIN_ON_OWNER
	osq_lock_init(&sem->osq);
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(__init_rwsem);

क्रमागत rwsem_रुकोer_type अणु
	RWSEM_WAITING_FOR_WRITE,
	RWSEM_WAITING_FOR_READ
पूर्ण;

काष्ठा rwsem_रुकोer अणु
	काष्ठा list_head list;
	काष्ठा task_काष्ठा *task;
	क्रमागत rwsem_रुकोer_type type;
	अचिन्हित दीर्घ समयout;
पूर्ण;
#घोषणा rwsem_first_रुकोer(sem) \
	list_first_entry(&sem->रुको_list, काष्ठा rwsem_रुकोer, list)

क्रमागत rwsem_wake_type अणु
	RWSEM_WAKE_ANY,		/* Wake whatever's at head of रुको list */
	RWSEM_WAKE_READERS,	/* Wake पढ़ोers only */
	RWSEM_WAKE_READ_OWNED	/* Waker thपढ़ो holds the पढ़ो lock */
पूर्ण;

क्रमागत ग_लिखोr_रुको_state अणु
	WRITER_NOT_FIRST,	/* Writer is not first in रुको list */
	WRITER_FIRST,		/* Writer is first in रुको list     */
	WRITER_HANDOFF		/* Writer is first & hanकरोff needed */
पूर्ण;

/*
 * The typical HZ value is either 250 or 1000. So set the minimum रुकोing
 * समय to at least 4ms or 1 jअगरfy (अगर it is higher than 4ms) in the रुको
 * queue beक्रमe initiating the hanकरोff protocol.
 */
#घोषणा RWSEM_WAIT_TIMEOUT	DIV_ROUND_UP(HZ, 250)

/*
 * Magic number to batch-wakeup रुकोing पढ़ोers, even when ग_लिखोrs are
 * also present in the queue. This both limits the amount of work the
 * waking thपढ़ो must करो and also prevents any potential counter overflow,
 * however unlikely.
 */
#घोषणा MAX_READERS_WAKEUP	0x100

/*
 * handle the lock release when processes blocked on it that can now run
 * - अगर we come here from up_xxxx(), then the RWSEM_FLAG_WAITERS bit must
 *   have been set.
 * - there must be someone on the queue
 * - the रुको_lock must be held by the caller
 * - tasks are marked क्रम wakeup, the caller must later invoke wake_up_q()
 *   to actually wakeup the blocked task(s) and drop the reference count,
 *   preferably when the रुको_lock is released
 * - woken process blocks are discarded from the list after having task zeroed
 * - ग_लिखोrs are only marked woken अगर करोwngrading is false
 */
अटल व्योम rwsem_mark_wake(काष्ठा rw_semaphore *sem,
			    क्रमागत rwsem_wake_type wake_type,
			    काष्ठा wake_q_head *wake_q)
अणु
	काष्ठा rwsem_रुकोer *रुकोer, *पंचांगp;
	दीर्घ oldcount, woken = 0, adjusपंचांगent = 0;
	काष्ठा list_head wlist;

	lockdep_निश्चित_held(&sem->रुको_lock);

	/*
	 * Take a peek at the queue head रुकोer such that we can determine
	 * the wakeup(s) to perक्रमm.
	 */
	रुकोer = rwsem_first_रुकोer(sem);

	अगर (रुकोer->type == RWSEM_WAITING_FOR_WRITE) अणु
		अगर (wake_type == RWSEM_WAKE_ANY) अणु
			/*
			 * Mark ग_लिखोr at the front of the queue क्रम wakeup.
			 * Until the task is actually later awoken later by
			 * the caller, other ग_लिखोrs are able to steal it.
			 * Readers, on the other hand, will block as they
			 * will notice the queued ग_लिखोr.
			 */
			wake_q_add(wake_q, रुकोer->task);
			lockevent_inc(rwsem_wake_ग_लिखोr);
		पूर्ण

		वापस;
	पूर्ण

	/*
	 * No पढ़ोer wakeup अगर there are too many of them alपढ़ोy.
	 */
	अगर (unlikely(atomic_दीर्घ_पढ़ो(&sem->count) < 0))
		वापस;

	/*
	 * Writers might steal the lock beक्रमe we grant it to the next पढ़ोer.
	 * We prefer to करो the first पढ़ोer grant beक्रमe counting पढ़ोers
	 * so we can bail out early अगर a ग_लिखोr stole the lock.
	 */
	अगर (wake_type != RWSEM_WAKE_READ_OWNED) अणु
		काष्ठा task_काष्ठा *owner;

		adjusपंचांगent = RWSEM_READER_BIAS;
		oldcount = atomic_दीर्घ_fetch_add(adjusपंचांगent, &sem->count);
		अगर (unlikely(oldcount & RWSEM_WRITER_MASK)) अणु
			/*
			 * When we've been रुकोing "too" दीर्घ (क्रम ग_लिखोrs
			 * to give up the lock), request a HANDOFF to
			 * क्रमce the issue.
			 */
			अगर (!(oldcount & RWSEM_FLAG_HANDOFF) &&
			    समय_after(jअगरfies, रुकोer->समयout)) अणु
				adjusपंचांगent -= RWSEM_FLAG_HANDOFF;
				lockevent_inc(rwsem_rlock_hanकरोff);
			पूर्ण

			atomic_दीर्घ_add(-adjusपंचांगent, &sem->count);
			वापस;
		पूर्ण
		/*
		 * Set it to पढ़ोer-owned to give spinners an early
		 * indication that पढ़ोers now have the lock.
		 * The पढ़ोer nonspinnable bit seen at slowpath entry of
		 * the पढ़ोer is copied over.
		 */
		owner = रुकोer->task;
		__rwsem_set_पढ़ोer_owned(sem, owner);
	पूर्ण

	/*
	 * Grant up to MAX_READERS_WAKEUP पढ़ो locks to all the पढ़ोers in the
	 * queue. We know that the woken will be at least 1 as we accounted
	 * क्रम above. Note we increment the 'active part' of the count by the
	 * number of पढ़ोers beक्रमe waking any processes up.
	 *
	 * This is an adaptation of the phase-fair R/W locks where at the
	 * पढ़ोer phase (first रुकोer is a पढ़ोer), all पढ़ोers are eligible
	 * to acquire the lock at the same समय irrespective of their order
	 * in the queue. The ग_लिखोrs acquire the lock according to their
	 * order in the queue.
	 *
	 * We have to करो wakeup in 2 passes to prevent the possibility that
	 * the पढ़ोer count may be decremented beक्रमe it is incremented. It
	 * is because the to-be-woken रुकोer may not have slept yet. So it
	 * may see रुकोer->task got cleared, finish its critical section and
	 * करो an unlock beक्रमe the पढ़ोer count increment.
	 *
	 * 1) Collect the पढ़ो-रुकोers in a separate list, count them and
	 *    fully increment the पढ़ोer count in rwsem.
	 * 2) For each रुकोers in the new list, clear रुकोer->task and
	 *    put them पूर्णांकo wake_q to be woken up later.
	 */
	INIT_LIST_HEAD(&wlist);
	list_क्रम_each_entry_safe(रुकोer, पंचांगp, &sem->रुको_list, list) अणु
		अगर (रुकोer->type == RWSEM_WAITING_FOR_WRITE)
			जारी;

		woken++;
		list_move_tail(&रुकोer->list, &wlist);

		/*
		 * Limit # of पढ़ोers that can be woken up per wakeup call.
		 */
		अगर (woken >= MAX_READERS_WAKEUP)
			अवरोध;
	पूर्ण

	adjusपंचांगent = woken * RWSEM_READER_BIAS - adjusपंचांगent;
	lockevent_cond_inc(rwsem_wake_पढ़ोer, woken);
	अगर (list_empty(&sem->रुको_list)) अणु
		/* hit end of list above */
		adjusपंचांगent -= RWSEM_FLAG_WAITERS;
	पूर्ण

	/*
	 * When we've woken a पढ़ोer, we no दीर्घer need to क्रमce ग_लिखोrs
	 * to give up the lock and we can clear HANDOFF.
	 */
	अगर (woken && (atomic_दीर्घ_पढ़ो(&sem->count) & RWSEM_FLAG_HANDOFF))
		adjusपंचांगent -= RWSEM_FLAG_HANDOFF;

	अगर (adjusपंचांगent)
		atomic_दीर्घ_add(adjusपंचांगent, &sem->count);

	/* 2nd pass */
	list_क्रम_each_entry_safe(रुकोer, पंचांगp, &wlist, list) अणु
		काष्ठा task_काष्ठा *tsk;

		tsk = रुकोer->task;
		get_task_काष्ठा(tsk);

		/*
		 * Ensure calling get_task_काष्ठा() beक्रमe setting the पढ़ोer
		 * रुकोer to nil such that rwsem_करोwn_पढ़ो_slowpath() cannot
		 * race with करो_निकास() by always holding a reference count
		 * to the task to wakeup.
		 */
		smp_store_release(&रुकोer->task, शून्य);
		/*
		 * Ensure issuing the wakeup (either by us or someone अन्यथा)
		 * after setting the पढ़ोer रुकोer to nil.
		 */
		wake_q_add_safe(wake_q, tsk);
	पूर्ण
पूर्ण

/*
 * This function must be called with the sem->रुको_lock held to prevent
 * race conditions between checking the rwsem रुको list and setting the
 * sem->count accordingly.
 *
 * If wstate is WRITER_HANDOFF, it will make sure that either the hanकरोff
 * bit is set or the lock is acquired with hanकरोff bit cleared.
 */
अटल अंतरभूत bool rwsem_try_ग_लिखो_lock(काष्ठा rw_semaphore *sem,
					क्रमागत ग_लिखोr_रुको_state wstate)
अणु
	दीर्घ count, new;

	lockdep_निश्चित_held(&sem->रुको_lock);

	count = atomic_दीर्घ_पढ़ो(&sem->count);
	करो अणु
		bool has_hanकरोff = !!(count & RWSEM_FLAG_HANDOFF);

		अगर (has_hanकरोff && wstate == WRITER_NOT_FIRST)
			वापस false;

		new = count;

		अगर (count & RWSEM_LOCK_MASK) अणु
			अगर (has_hanकरोff || (wstate != WRITER_HANDOFF))
				वापस false;

			new |= RWSEM_FLAG_HANDOFF;
		पूर्ण अन्यथा अणु
			new |= RWSEM_WRITER_LOCKED;
			new &= ~RWSEM_FLAG_HANDOFF;

			अगर (list_is_singular(&sem->रुको_list))
				new &= ~RWSEM_FLAG_WAITERS;
		पूर्ण
	पूर्ण जबतक (!atomic_दीर्घ_try_cmpxchg_acquire(&sem->count, &count, new));

	/*
	 * We have either acquired the lock with hanकरोff bit cleared or
	 * set the hanकरोff bit.
	 */
	अगर (new & RWSEM_FLAG_HANDOFF)
		वापस false;

	rwsem_set_owner(sem);
	वापस true;
पूर्ण

#अगर_घोषित CONFIG_RWSEM_SPIN_ON_OWNER
/*
 * Try to acquire ग_लिखो lock beक्रमe the ग_लिखोr has been put on रुको queue.
 */
अटल अंतरभूत bool rwsem_try_ग_लिखो_lock_unqueued(काष्ठा rw_semaphore *sem)
अणु
	दीर्घ count = atomic_दीर्घ_पढ़ो(&sem->count);

	जबतक (!(count & (RWSEM_LOCK_MASK|RWSEM_FLAG_HANDOFF))) अणु
		अगर (atomic_दीर्घ_try_cmpxchg_acquire(&sem->count, &count,
					count | RWSEM_WRITER_LOCKED)) अणु
			rwsem_set_owner(sem);
			lockevent_inc(rwsem_opt_lock);
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल अंतरभूत bool owner_on_cpu(काष्ठा task_काष्ठा *owner)
अणु
	/*
	 * As lock holder preemption issue, we both skip spinning अगर
	 * task is not on cpu or its cpu is preempted
	 */
	वापस owner->on_cpu && !vcpu_is_preempted(task_cpu(owner));
पूर्ण

अटल अंतरभूत bool rwsem_can_spin_on_owner(काष्ठा rw_semaphore *sem)
अणु
	काष्ठा task_काष्ठा *owner;
	अचिन्हित दीर्घ flags;
	bool ret = true;

	अगर (need_resched()) अणु
		lockevent_inc(rwsem_opt_fail);
		वापस false;
	पूर्ण

	preempt_disable();
	rcu_पढ़ो_lock();
	owner = rwsem_owner_flags(sem, &flags);
	/*
	 * Don't check the पढ़ो-owner as the entry may be stale.
	 */
	अगर ((flags & RWSEM_NONSPINNABLE) ||
	    (owner && !(flags & RWSEM_READER_OWNED) && !owner_on_cpu(owner)))
		ret = false;
	rcu_पढ़ो_unlock();
	preempt_enable();

	lockevent_cond_inc(rwsem_opt_fail, !ret);
	वापस ret;
पूर्ण

/*
 * The rwsem_spin_on_owner() function वापसs the following 4 values
 * depending on the lock owner state.
 *   OWNER_शून्य  : owner is currently शून्य
 *   OWNER_WRITER: when owner changes and is a ग_लिखोr
 *   OWNER_READER: when owner changes and the new owner may be a पढ़ोer.
 *   OWNER_NONSPINNABLE:
 *		   when optimistic spinning has to stop because either the
 *		   owner stops running, is unknown, or its बारlice has
 *		   been used up.
 */
क्रमागत owner_state अणु
	OWNER_शून्य		= 1 << 0,
	OWNER_WRITER		= 1 << 1,
	OWNER_READER		= 1 << 2,
	OWNER_NONSPINNABLE	= 1 << 3,
पूर्ण;
#घोषणा OWNER_SPINNABLE		(OWNER_शून्य | OWNER_WRITER | OWNER_READER)

अटल अंतरभूत क्रमागत owner_state
rwsem_owner_state(काष्ठा task_काष्ठा *owner, अचिन्हित दीर्घ flags)
अणु
	अगर (flags & RWSEM_NONSPINNABLE)
		वापस OWNER_NONSPINNABLE;

	अगर (flags & RWSEM_READER_OWNED)
		वापस OWNER_READER;

	वापस owner ? OWNER_WRITER : OWNER_शून्य;
पूर्ण

अटल noअंतरभूत क्रमागत owner_state
rwsem_spin_on_owner(काष्ठा rw_semaphore *sem)
अणु
	काष्ठा task_काष्ठा *new, *owner;
	अचिन्हित दीर्घ flags, new_flags;
	क्रमागत owner_state state;

	owner = rwsem_owner_flags(sem, &flags);
	state = rwsem_owner_state(owner, flags);
	अगर (state != OWNER_WRITER)
		वापस state;

	rcu_पढ़ो_lock();
	क्रम (;;) अणु
		/*
		 * When a रुकोing ग_लिखोr set the hanकरोff flag, it may spin
		 * on the owner as well. Once that ग_लिखोr acquires the lock,
		 * we can spin on it. So we करोn't need to quit even when the
		 * hanकरोff bit is set.
		 */
		new = rwsem_owner_flags(sem, &new_flags);
		अगर ((new != owner) || (new_flags != flags)) अणु
			state = rwsem_owner_state(new, new_flags);
			अवरोध;
		पूर्ण

		/*
		 * Ensure we emit the owner->on_cpu, dereference _after_
		 * checking sem->owner still matches owner, अगर that fails,
		 * owner might poपूर्णांक to मुक्त()d memory, अगर it still matches,
		 * the rcu_पढ़ो_lock() ensures the memory stays valid.
		 */
		barrier();

		अगर (need_resched() || !owner_on_cpu(owner)) अणु
			state = OWNER_NONSPINNABLE;
			अवरोध;
		पूर्ण

		cpu_relax();
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस state;
पूर्ण

/*
 * Calculate पढ़ोer-owned rwsem spinning threshold क्रम ग_लिखोr
 *
 * The more पढ़ोers own the rwsem, the दीर्घer it will take क्रम them to
 * wind करोwn and मुक्त the rwsem. So the empirical क्रमmula used to
 * determine the actual spinning समय limit here is:
 *
 *   Spinning threshold = (10 + nr_पढ़ोers/2)us
 *
 * The limit is capped to a maximum of 25us (30 पढ़ोers). This is just
 * a heuristic and is subjected to change in the future.
 */
अटल अंतरभूत u64 rwsem_rspin_threshold(काष्ठा rw_semaphore *sem)
अणु
	दीर्घ count = atomic_दीर्घ_पढ़ो(&sem->count);
	पूर्णांक पढ़ोers = count >> RWSEM_READER_SHIFT;
	u64 delta;

	अगर (पढ़ोers > 30)
		पढ़ोers = 30;
	delta = (20 + पढ़ोers) * NSEC_PER_USEC / 2;

	वापस sched_घड़ी() + delta;
पूर्ण

अटल bool rwsem_optimistic_spin(काष्ठा rw_semaphore *sem)
अणु
	bool taken = false;
	पूर्णांक prev_owner_state = OWNER_शून्य;
	पूर्णांक loop = 0;
	u64 rspin_threshold = 0;

	preempt_disable();

	/* sem->रुको_lock should not be held when करोing optimistic spinning */
	अगर (!osq_lock(&sem->osq))
		जाओ करोne;

	/*
	 * Optimistically spin on the owner field and attempt to acquire the
	 * lock whenever the owner changes. Spinning will be stopped when:
	 *  1) the owning ग_लिखोr isn't running; or
	 *  2) पढ़ोers own the lock and spinning समय has exceeded limit.
	 */
	क्रम (;;) अणु
		क्रमागत owner_state owner_state;

		owner_state = rwsem_spin_on_owner(sem);
		अगर (!(owner_state & OWNER_SPINNABLE))
			अवरोध;

		/*
		 * Try to acquire the lock
		 */
		taken = rwsem_try_ग_लिखो_lock_unqueued(sem);

		अगर (taken)
			अवरोध;

		/*
		 * Time-based पढ़ोer-owned rwsem optimistic spinning
		 */
		अगर (owner_state == OWNER_READER) अणु
			/*
			 * Re-initialize rspin_threshold every समय when
			 * the owner state changes from non-पढ़ोer to पढ़ोer.
			 * This allows a ग_लिखोr to steal the lock in between
			 * 2 पढ़ोer phases and have the threshold reset at
			 * the beginning of the 2nd पढ़ोer phase.
			 */
			अगर (prev_owner_state != OWNER_READER) अणु
				अगर (rwsem_test_oflags(sem, RWSEM_NONSPINNABLE))
					अवरोध;
				rspin_threshold = rwsem_rspin_threshold(sem);
				loop = 0;
			पूर्ण

			/*
			 * Check समय threshold once every 16 iterations to
			 * aव्योम calling sched_घड़ी() too frequently so
			 * as to reduce the average latency between the बार
			 * when the lock becomes मुक्त and when the spinner
			 * is पढ़ोy to करो a trylock.
			 */
			अन्यथा अगर (!(++loop & 0xf) && (sched_घड़ी() > rspin_threshold)) अणु
				rwsem_set_nonspinnable(sem);
				lockevent_inc(rwsem_opt_nospin);
				अवरोध;
			पूर्ण
		पूर्ण

		/*
		 * An RT task cannot करो optimistic spinning अगर it cannot
		 * be sure the lock holder is running or live-lock may
		 * happen अगर the current task and the lock holder happen
		 * to run in the same CPU. However, पातing optimistic
		 * spinning जबतक a शून्य owner is detected may miss some
		 * opportunity where spinning can जारी without causing
		 * problem.
		 *
		 * There are 2 possible हालs where an RT task may be able
		 * to जारी spinning.
		 *
		 * 1) The lock owner is in the process of releasing the
		 *    lock, sem->owner is cleared but the lock has not
		 *    been released yet.
		 * 2) The lock was मुक्त and owner cleared, but another
		 *    task just comes in and acquire the lock beक्रमe
		 *    we try to get it. The new owner may be a spinnable
		 *    ग_लिखोr.
		 *
		 * To take advantage of two scenarios listed above, the RT
		 * task is made to retry one more समय to see अगर it can
		 * acquire the lock or जारी spinning on the new owning
		 * ग_लिखोr. Of course, अगर the समय lag is दीर्घ enough or the
		 * new owner is not a ग_लिखोr or spinnable, the RT task will
		 * quit spinning.
		 *
		 * If the owner is a ग_लिखोr, the need_resched() check is
		 * करोne inside rwsem_spin_on_owner(). If the owner is not
		 * a ग_लिखोr, need_resched() check needs to be करोne here.
		 */
		अगर (owner_state != OWNER_WRITER) अणु
			अगर (need_resched())
				अवरोध;
			अगर (rt_task(current) &&
			   (prev_owner_state != OWNER_WRITER))
				अवरोध;
		पूर्ण
		prev_owner_state = owner_state;

		/*
		 * The cpu_relax() call is a compiler barrier which क्रमces
		 * everything in this loop to be re-loaded. We करोn't need
		 * memory barriers as we'll eventually observe the right
		 * values at the cost of a few extra spins.
		 */
		cpu_relax();
	पूर्ण
	osq_unlock(&sem->osq);
करोne:
	preempt_enable();
	lockevent_cond_inc(rwsem_opt_fail, !taken);
	वापस taken;
पूर्ण

/*
 * Clear the owner's RWSEM_NONSPINNABLE bit अगर it is set. This should
 * only be called when the पढ़ोer count reaches 0.
 */
अटल अंतरभूत व्योम clear_nonspinnable(काष्ठा rw_semaphore *sem)
अणु
	अगर (rwsem_test_oflags(sem, RWSEM_NONSPINNABLE))
		atomic_दीर्घ_andnot(RWSEM_NONSPINNABLE, &sem->owner);
पूर्ण

#अन्यथा
अटल अंतरभूत bool rwsem_can_spin_on_owner(काष्ठा rw_semaphore *sem)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool rwsem_optimistic_spin(काष्ठा rw_semaphore *sem)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम clear_nonspinnable(काष्ठा rw_semaphore *sem) अणु पूर्ण

अटल अंतरभूत पूर्णांक
rwsem_spin_on_owner(काष्ठा rw_semaphore *sem)
अणु
	वापस 0;
पूर्ण
#घोषणा OWNER_शून्य	1
#पूर्ण_अगर

/*
 * Wait क्रम the पढ़ो lock to be granted
 */
अटल काष्ठा rw_semaphore __sched *
rwsem_करोwn_पढ़ो_slowpath(काष्ठा rw_semaphore *sem, दीर्घ count, पूर्णांक state)
अणु
	दीर्घ adjusपंचांगent = -RWSEM_READER_BIAS;
	दीर्घ rcnt = (count >> RWSEM_READER_SHIFT);
	काष्ठा rwsem_रुकोer रुकोer;
	DEFINE_WAKE_Q(wake_q);
	bool wake = false;

	/*
	 * To prevent a स्थिरant stream of पढ़ोers from starving a sleeping
	 * रुकोer, करोn't attempt optimistic lock stealing अगर the lock is
	 * currently owned by पढ़ोers.
	 */
	अगर ((atomic_दीर्घ_पढ़ो(&sem->owner) & RWSEM_READER_OWNED) &&
	    (rcnt > 1) && !(count & RWSEM_WRITER_LOCKED))
		जाओ queue;

	/*
	 * Reader optimistic lock stealing.
	 */
	अगर (!(count & (RWSEM_WRITER_LOCKED | RWSEM_FLAG_HANDOFF))) अणु
		rwsem_set_पढ़ोer_owned(sem);
		lockevent_inc(rwsem_rlock_steal);

		/*
		 * Wake up other पढ़ोers in the रुको queue अगर it is
		 * the first पढ़ोer.
		 */
		अगर ((rcnt == 1) && (count & RWSEM_FLAG_WAITERS)) अणु
			raw_spin_lock_irq(&sem->रुको_lock);
			अगर (!list_empty(&sem->रुको_list))
				rwsem_mark_wake(sem, RWSEM_WAKE_READ_OWNED,
						&wake_q);
			raw_spin_unlock_irq(&sem->रुको_lock);
			wake_up_q(&wake_q);
		पूर्ण
		वापस sem;
	पूर्ण

queue:
	रुकोer.task = current;
	रुकोer.type = RWSEM_WAITING_FOR_READ;
	रुकोer.समयout = jअगरfies + RWSEM_WAIT_TIMEOUT;

	raw_spin_lock_irq(&sem->रुको_lock);
	अगर (list_empty(&sem->रुको_list)) अणु
		/*
		 * In हाल the रुको queue is empty and the lock isn't owned
		 * by a ग_लिखोr or has the hanकरोff bit set, this पढ़ोer can
		 * निकास the slowpath and वापस immediately as its
		 * RWSEM_READER_BIAS has alपढ़ोy been set in the count.
		 */
		अगर (!(atomic_दीर्घ_पढ़ो(&sem->count) &
		     (RWSEM_WRITER_MASK | RWSEM_FLAG_HANDOFF))) अणु
			/* Provide lock ACQUIRE */
			smp_acquire__after_ctrl_dep();
			raw_spin_unlock_irq(&sem->रुको_lock);
			rwsem_set_पढ़ोer_owned(sem);
			lockevent_inc(rwsem_rlock_fast);
			वापस sem;
		पूर्ण
		adjusपंचांगent += RWSEM_FLAG_WAITERS;
	पूर्ण
	list_add_tail(&रुकोer.list, &sem->रुको_list);

	/* we're now रुकोing on the lock, but no दीर्घer actively locking */
	count = atomic_दीर्घ_add_वापस(adjusपंचांगent, &sem->count);

	/*
	 * If there are no active locks, wake the front queued process(es).
	 *
	 * If there are no ग_लिखोrs and we are first in the queue,
	 * wake our own रुकोer to join the existing active पढ़ोers !
	 */
	अगर (!(count & RWSEM_LOCK_MASK)) अणु
		clear_nonspinnable(sem);
		wake = true;
	पूर्ण
	अगर (wake || (!(count & RWSEM_WRITER_MASK) &&
		    (adjusपंचांगent & RWSEM_FLAG_WAITERS)))
		rwsem_mark_wake(sem, RWSEM_WAKE_ANY, &wake_q);

	raw_spin_unlock_irq(&sem->रुको_lock);
	wake_up_q(&wake_q);

	/* रुको to be given the lock */
	क्रम (;;) अणु
		set_current_state(state);
		अगर (!smp_load_acquire(&रुकोer.task)) अणु
			/* Matches rwsem_mark_wake()'s smp_store_release(). */
			अवरोध;
		पूर्ण
		अगर (संकेत_pending_state(state, current)) अणु
			raw_spin_lock_irq(&sem->रुको_lock);
			अगर (रुकोer.task)
				जाओ out_nolock;
			raw_spin_unlock_irq(&sem->रुको_lock);
			/* Ordered by sem->रुको_lock against rwsem_mark_wake(). */
			अवरोध;
		पूर्ण
		schedule();
		lockevent_inc(rwsem_sleep_पढ़ोer);
	पूर्ण

	__set_current_state(TASK_RUNNING);
	lockevent_inc(rwsem_rlock);
	वापस sem;

out_nolock:
	list_del(&रुकोer.list);
	अगर (list_empty(&sem->रुको_list)) अणु
		atomic_दीर्घ_andnot(RWSEM_FLAG_WAITERS|RWSEM_FLAG_HANDOFF,
				   &sem->count);
	पूर्ण
	raw_spin_unlock_irq(&sem->रुको_lock);
	__set_current_state(TASK_RUNNING);
	lockevent_inc(rwsem_rlock_fail);
	वापस ERR_PTR(-EINTR);
पूर्ण

/*
 * Wait until we successfully acquire the ग_लिखो lock
 */
अटल काष्ठा rw_semaphore *
rwsem_करोwn_ग_लिखो_slowpath(काष्ठा rw_semaphore *sem, पूर्णांक state)
अणु
	दीर्घ count;
	क्रमागत ग_लिखोr_रुको_state wstate;
	काष्ठा rwsem_रुकोer रुकोer;
	काष्ठा rw_semaphore *ret = sem;
	DEFINE_WAKE_Q(wake_q);

	/* करो optimistic spinning and steal lock अगर possible */
	अगर (rwsem_can_spin_on_owner(sem) && rwsem_optimistic_spin(sem)) अणु
		/* rwsem_optimistic_spin() implies ACQUIRE on success */
		वापस sem;
	पूर्ण

	/*
	 * Optimistic spinning failed, proceed to the slowpath
	 * and block until we can acquire the sem.
	 */
	रुकोer.task = current;
	रुकोer.type = RWSEM_WAITING_FOR_WRITE;
	रुकोer.समयout = jअगरfies + RWSEM_WAIT_TIMEOUT;

	raw_spin_lock_irq(&sem->रुको_lock);

	/* account क्रम this beक्रमe adding a new element to the list */
	wstate = list_empty(&sem->रुको_list) ? WRITER_FIRST : WRITER_NOT_FIRST;

	list_add_tail(&रुकोer.list, &sem->रुको_list);

	/* we're now रुकोing on the lock */
	अगर (wstate == WRITER_NOT_FIRST) अणु
		count = atomic_दीर्घ_पढ़ो(&sem->count);

		/*
		 * If there were alपढ़ोy thपढ़ोs queued beक्रमe us and:
		 *  1) there are no active locks, wake the front
		 *     queued process(es) as the hanकरोff bit might be set.
		 *  2) there are no active ग_लिखोrs and some पढ़ोers, the lock
		 *     must be पढ़ो owned; so we try to wake any पढ़ो lock
		 *     रुकोers that were queued ahead of us.
		 */
		अगर (count & RWSEM_WRITER_MASK)
			जाओ रुको;

		rwsem_mark_wake(sem, (count & RWSEM_READER_MASK)
					? RWSEM_WAKE_READERS
					: RWSEM_WAKE_ANY, &wake_q);

		अगर (!wake_q_empty(&wake_q)) अणु
			/*
			 * We want to minimize रुको_lock hold समय especially
			 * when a large number of पढ़ोers are to be woken up.
			 */
			raw_spin_unlock_irq(&sem->रुको_lock);
			wake_up_q(&wake_q);
			wake_q_init(&wake_q);	/* Used again, reinit */
			raw_spin_lock_irq(&sem->रुको_lock);
		पूर्ण
	पूर्ण अन्यथा अणु
		atomic_दीर्घ_or(RWSEM_FLAG_WAITERS, &sem->count);
	पूर्ण

रुको:
	/* रुको until we successfully acquire the lock */
	set_current_state(state);
	क्रम (;;) अणु
		अगर (rwsem_try_ग_लिखो_lock(sem, wstate)) अणु
			/* rwsem_try_ग_लिखो_lock() implies ACQUIRE on success */
			अवरोध;
		पूर्ण

		raw_spin_unlock_irq(&sem->रुको_lock);

		/*
		 * After setting the hanकरोff bit and failing to acquire
		 * the lock, attempt to spin on owner to accelerate lock
		 * transfer. If the previous owner is a on-cpu ग_लिखोr and it
		 * has just released the lock, OWNER_शून्य will be वापसed.
		 * In this हाल, we attempt to acquire the lock again
		 * without sleeping.
		 */
		अगर (wstate == WRITER_HANDOFF &&
		    rwsem_spin_on_owner(sem) == OWNER_शून्य)
			जाओ trylock_again;

		/* Block until there are no active lockers. */
		क्रम (;;) अणु
			अगर (संकेत_pending_state(state, current))
				जाओ out_nolock;

			schedule();
			lockevent_inc(rwsem_sleep_ग_लिखोr);
			set_current_state(state);
			/*
			 * If HANDOFF bit is set, unconditionally करो
			 * a trylock.
			 */
			अगर (wstate == WRITER_HANDOFF)
				अवरोध;

			अगर ((wstate == WRITER_NOT_FIRST) &&
			    (rwsem_first_रुकोer(sem) == &रुकोer))
				wstate = WRITER_FIRST;

			count = atomic_दीर्घ_पढ़ो(&sem->count);
			अगर (!(count & RWSEM_LOCK_MASK))
				अवरोध;

			/*
			 * The setting of the hanकरोff bit is deferred
			 * until rwsem_try_ग_लिखो_lock() is called.
			 */
			अगर ((wstate == WRITER_FIRST) && (rt_task(current) ||
			    समय_after(jअगरfies, रुकोer.समयout))) अणु
				wstate = WRITER_HANDOFF;
				lockevent_inc(rwsem_wlock_hanकरोff);
				अवरोध;
			पूर्ण
		पूर्ण
trylock_again:
		raw_spin_lock_irq(&sem->रुको_lock);
	पूर्ण
	__set_current_state(TASK_RUNNING);
	list_del(&रुकोer.list);
	raw_spin_unlock_irq(&sem->रुको_lock);
	lockevent_inc(rwsem_wlock);

	वापस ret;

out_nolock:
	__set_current_state(TASK_RUNNING);
	raw_spin_lock_irq(&sem->रुको_lock);
	list_del(&रुकोer.list);

	अगर (unlikely(wstate == WRITER_HANDOFF))
		atomic_दीर्घ_add(-RWSEM_FLAG_HANDOFF,  &sem->count);

	अगर (list_empty(&sem->रुको_list))
		atomic_दीर्घ_andnot(RWSEM_FLAG_WAITERS, &sem->count);
	अन्यथा
		rwsem_mark_wake(sem, RWSEM_WAKE_ANY, &wake_q);
	raw_spin_unlock_irq(&sem->रुको_lock);
	wake_up_q(&wake_q);
	lockevent_inc(rwsem_wlock_fail);

	वापस ERR_PTR(-EINTR);
पूर्ण

/*
 * handle waking up a रुकोer on the semaphore
 * - up_पढ़ो/up_ग_लिखो has decremented the active part of count अगर we come here
 */
अटल काष्ठा rw_semaphore *rwsem_wake(काष्ठा rw_semaphore *sem, दीर्घ count)
अणु
	अचिन्हित दीर्घ flags;
	DEFINE_WAKE_Q(wake_q);

	raw_spin_lock_irqsave(&sem->रुको_lock, flags);

	अगर (!list_empty(&sem->रुको_list))
		rwsem_mark_wake(sem, RWSEM_WAKE_ANY, &wake_q);

	raw_spin_unlock_irqrestore(&sem->रुको_lock, flags);
	wake_up_q(&wake_q);

	वापस sem;
पूर्ण

/*
 * करोwngrade a ग_लिखो lock पूर्णांकo a पढ़ो lock
 * - caller incremented रुकोing part of count and discovered it still negative
 * - just wake up any पढ़ोers at the front of the queue
 */
अटल काष्ठा rw_semaphore *rwsem_करोwngrade_wake(काष्ठा rw_semaphore *sem)
अणु
	अचिन्हित दीर्घ flags;
	DEFINE_WAKE_Q(wake_q);

	raw_spin_lock_irqsave(&sem->रुको_lock, flags);

	अगर (!list_empty(&sem->रुको_list))
		rwsem_mark_wake(sem, RWSEM_WAKE_READ_OWNED, &wake_q);

	raw_spin_unlock_irqrestore(&sem->रुको_lock, flags);
	wake_up_q(&wake_q);

	वापस sem;
पूर्ण

/*
 * lock क्रम पढ़ोing
 */
अटल अंतरभूत पूर्णांक __करोwn_पढ़ो_common(काष्ठा rw_semaphore *sem, पूर्णांक state)
अणु
	दीर्घ count;

	अगर (!rwsem_पढ़ो_trylock(sem, &count)) अणु
		अगर (IS_ERR(rwsem_करोwn_पढ़ो_slowpath(sem, count, state)))
			वापस -EINTR;
		DEBUG_RWSEMS_WARN_ON(!is_rwsem_पढ़ोer_owned(sem), sem);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम __करोwn_पढ़ो(काष्ठा rw_semaphore *sem)
अणु
	__करोwn_पढ़ो_common(sem, TASK_UNINTERRUPTIBLE);
पूर्ण

अटल अंतरभूत पूर्णांक __करोwn_पढ़ो_पूर्णांकerruptible(काष्ठा rw_semaphore *sem)
अणु
	वापस __करोwn_पढ़ो_common(sem, TASK_INTERRUPTIBLE);
पूर्ण

अटल अंतरभूत पूर्णांक __करोwn_पढ़ो_समाप्तable(काष्ठा rw_semaphore *sem)
अणु
	वापस __करोwn_पढ़ो_common(sem, TASK_KILLABLE);
पूर्ण

अटल अंतरभूत पूर्णांक __करोwn_पढ़ो_trylock(काष्ठा rw_semaphore *sem)
अणु
	दीर्घ पंचांगp;

	DEBUG_RWSEMS_WARN_ON(sem->magic != sem, sem);

	/*
	 * Optimize क्रम the हाल when the rwsem is not locked at all.
	 */
	पंचांगp = RWSEM_UNLOCKED_VALUE;
	करो अणु
		अगर (atomic_दीर्घ_try_cmpxchg_acquire(&sem->count, &पंचांगp,
					पंचांगp + RWSEM_READER_BIAS)) अणु
			rwsem_set_पढ़ोer_owned(sem);
			वापस 1;
		पूर्ण
	पूर्ण जबतक (!(पंचांगp & RWSEM_READ_FAILED_MASK));
	वापस 0;
पूर्ण

/*
 * lock क्रम writing
 */
अटल अंतरभूत पूर्णांक __करोwn_ग_लिखो_common(काष्ठा rw_semaphore *sem, पूर्णांक state)
अणु
	अगर (unlikely(!rwsem_ग_लिखो_trylock(sem))) अणु
		अगर (IS_ERR(rwsem_करोwn_ग_लिखो_slowpath(sem, state)))
			वापस -EINTR;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम __करोwn_ग_लिखो(काष्ठा rw_semaphore *sem)
अणु
	__करोwn_ग_लिखो_common(sem, TASK_UNINTERRUPTIBLE);
पूर्ण

अटल अंतरभूत पूर्णांक __करोwn_ग_लिखो_समाप्तable(काष्ठा rw_semaphore *sem)
अणु
	वापस __करोwn_ग_लिखो_common(sem, TASK_KILLABLE);
पूर्ण

अटल अंतरभूत पूर्णांक __करोwn_ग_लिखो_trylock(काष्ठा rw_semaphore *sem)
अणु
	DEBUG_RWSEMS_WARN_ON(sem->magic != sem, sem);
	वापस rwsem_ग_लिखो_trylock(sem);
पूर्ण

/*
 * unlock after पढ़ोing
 */
अटल अंतरभूत व्योम __up_पढ़ो(काष्ठा rw_semaphore *sem)
अणु
	दीर्घ पंचांगp;

	DEBUG_RWSEMS_WARN_ON(sem->magic != sem, sem);
	DEBUG_RWSEMS_WARN_ON(!is_rwsem_पढ़ोer_owned(sem), sem);

	rwsem_clear_पढ़ोer_owned(sem);
	पंचांगp = atomic_दीर्घ_add_वापस_release(-RWSEM_READER_BIAS, &sem->count);
	DEBUG_RWSEMS_WARN_ON(पंचांगp < 0, sem);
	अगर (unlikely((पंचांगp & (RWSEM_LOCK_MASK|RWSEM_FLAG_WAITERS)) ==
		      RWSEM_FLAG_WAITERS)) अणु
		clear_nonspinnable(sem);
		rwsem_wake(sem, पंचांगp);
	पूर्ण
पूर्ण

/*
 * unlock after writing
 */
अटल अंतरभूत व्योम __up_ग_लिखो(काष्ठा rw_semaphore *sem)
अणु
	दीर्घ पंचांगp;

	DEBUG_RWSEMS_WARN_ON(sem->magic != sem, sem);
	/*
	 * sem->owner may dअगरfer from current अगर the ownership is transferred
	 * to an anonymous ग_लिखोr by setting the RWSEM_NONSPINNABLE bits.
	 */
	DEBUG_RWSEMS_WARN_ON((rwsem_owner(sem) != current) &&
			    !rwsem_test_oflags(sem, RWSEM_NONSPINNABLE), sem);

	rwsem_clear_owner(sem);
	पंचांगp = atomic_दीर्घ_fetch_add_release(-RWSEM_WRITER_LOCKED, &sem->count);
	अगर (unlikely(पंचांगp & RWSEM_FLAG_WAITERS))
		rwsem_wake(sem, पंचांगp);
पूर्ण

/*
 * करोwngrade ग_लिखो lock to पढ़ो lock
 */
अटल अंतरभूत व्योम __करोwngrade_ग_लिखो(काष्ठा rw_semaphore *sem)
अणु
	दीर्घ पंचांगp;

	/*
	 * When करोwngrading from exclusive to shared ownership,
	 * anything inside the ग_लिखो-locked region cannot leak
	 * पूर्णांकo the पढ़ो side. In contrast, anything in the
	 * पढ़ो-locked region is ok to be re-ordered पूर्णांकo the
	 * ग_लिखो side. As such, rely on RELEASE semantics.
	 */
	DEBUG_RWSEMS_WARN_ON(rwsem_owner(sem) != current, sem);
	पंचांगp = atomic_दीर्घ_fetch_add_release(
		-RWSEM_WRITER_LOCKED+RWSEM_READER_BIAS, &sem->count);
	rwsem_set_पढ़ोer_owned(sem);
	अगर (पंचांगp & RWSEM_FLAG_WAITERS)
		rwsem_करोwngrade_wake(sem);
पूर्ण

/*
 * lock क्रम पढ़ोing
 */
व्योम __sched करोwn_पढ़ो(काष्ठा rw_semaphore *sem)
अणु
	might_sleep();
	rwsem_acquire_पढ़ो(&sem->dep_map, 0, 0, _RET_IP_);

	LOCK_CONTENDED(sem, __करोwn_पढ़ो_trylock, __करोwn_पढ़ो);
पूर्ण
EXPORT_SYMBOL(करोwn_पढ़ो);

पूर्णांक __sched करोwn_पढ़ो_पूर्णांकerruptible(काष्ठा rw_semaphore *sem)
अणु
	might_sleep();
	rwsem_acquire_पढ़ो(&sem->dep_map, 0, 0, _RET_IP_);

	अगर (LOCK_CONTENDED_RETURN(sem, __करोwn_पढ़ो_trylock, __करोwn_पढ़ो_पूर्णांकerruptible)) अणु
		rwsem_release(&sem->dep_map, _RET_IP_);
		वापस -EINTR;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(करोwn_पढ़ो_पूर्णांकerruptible);

पूर्णांक __sched करोwn_पढ़ो_समाप्तable(काष्ठा rw_semaphore *sem)
अणु
	might_sleep();
	rwsem_acquire_पढ़ो(&sem->dep_map, 0, 0, _RET_IP_);

	अगर (LOCK_CONTENDED_RETURN(sem, __करोwn_पढ़ो_trylock, __करोwn_पढ़ो_समाप्तable)) अणु
		rwsem_release(&sem->dep_map, _RET_IP_);
		वापस -EINTR;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(करोwn_पढ़ो_समाप्तable);

/*
 * trylock क्रम पढ़ोing -- वापसs 1 अगर successful, 0 अगर contention
 */
पूर्णांक करोwn_पढ़ो_trylock(काष्ठा rw_semaphore *sem)
अणु
	पूर्णांक ret = __करोwn_पढ़ो_trylock(sem);

	अगर (ret == 1)
		rwsem_acquire_पढ़ो(&sem->dep_map, 0, 1, _RET_IP_);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(करोwn_पढ़ो_trylock);

/*
 * lock क्रम writing
 */
व्योम __sched करोwn_ग_लिखो(काष्ठा rw_semaphore *sem)
अणु
	might_sleep();
	rwsem_acquire(&sem->dep_map, 0, 0, _RET_IP_);
	LOCK_CONTENDED(sem, __करोwn_ग_लिखो_trylock, __करोwn_ग_लिखो);
पूर्ण
EXPORT_SYMBOL(करोwn_ग_लिखो);

/*
 * lock क्रम writing
 */
पूर्णांक __sched करोwn_ग_लिखो_समाप्तable(काष्ठा rw_semaphore *sem)
अणु
	might_sleep();
	rwsem_acquire(&sem->dep_map, 0, 0, _RET_IP_);

	अगर (LOCK_CONTENDED_RETURN(sem, __करोwn_ग_लिखो_trylock,
				  __करोwn_ग_लिखो_समाप्तable)) अणु
		rwsem_release(&sem->dep_map, _RET_IP_);
		वापस -EINTR;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(करोwn_ग_लिखो_समाप्तable);

/*
 * trylock क्रम writing -- वापसs 1 अगर successful, 0 अगर contention
 */
पूर्णांक करोwn_ग_लिखो_trylock(काष्ठा rw_semaphore *sem)
अणु
	पूर्णांक ret = __करोwn_ग_लिखो_trylock(sem);

	अगर (ret == 1)
		rwsem_acquire(&sem->dep_map, 0, 1, _RET_IP_);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(करोwn_ग_लिखो_trylock);

/*
 * release a पढ़ो lock
 */
व्योम up_पढ़ो(काष्ठा rw_semaphore *sem)
अणु
	rwsem_release(&sem->dep_map, _RET_IP_);
	__up_पढ़ो(sem);
पूर्ण
EXPORT_SYMBOL(up_पढ़ो);

/*
 * release a ग_लिखो lock
 */
व्योम up_ग_लिखो(काष्ठा rw_semaphore *sem)
अणु
	rwsem_release(&sem->dep_map, _RET_IP_);
	__up_ग_लिखो(sem);
पूर्ण
EXPORT_SYMBOL(up_ग_लिखो);

/*
 * करोwngrade ग_लिखो lock to पढ़ो lock
 */
व्योम करोwngrade_ग_लिखो(काष्ठा rw_semaphore *sem)
अणु
	lock_करोwngrade(&sem->dep_map, _RET_IP_);
	__करोwngrade_ग_लिखो(sem);
पूर्ण
EXPORT_SYMBOL(करोwngrade_ग_लिखो);

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC

व्योम करोwn_पढ़ो_nested(काष्ठा rw_semaphore *sem, पूर्णांक subclass)
अणु
	might_sleep();
	rwsem_acquire_पढ़ो(&sem->dep_map, subclass, 0, _RET_IP_);
	LOCK_CONTENDED(sem, __करोwn_पढ़ो_trylock, __करोwn_पढ़ो);
पूर्ण
EXPORT_SYMBOL(करोwn_पढ़ो_nested);

पूर्णांक करोwn_पढ़ो_समाप्तable_nested(काष्ठा rw_semaphore *sem, पूर्णांक subclass)
अणु
	might_sleep();
	rwsem_acquire_पढ़ो(&sem->dep_map, subclass, 0, _RET_IP_);

	अगर (LOCK_CONTENDED_RETURN(sem, __करोwn_पढ़ो_trylock, __करोwn_पढ़ो_समाप्तable)) अणु
		rwsem_release(&sem->dep_map, _RET_IP_);
		वापस -EINTR;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(करोwn_पढ़ो_समाप्तable_nested);

व्योम _करोwn_ग_लिखो_nest_lock(काष्ठा rw_semaphore *sem, काष्ठा lockdep_map *nest)
अणु
	might_sleep();
	rwsem_acquire_nest(&sem->dep_map, 0, 0, nest, _RET_IP_);
	LOCK_CONTENDED(sem, __करोwn_ग_लिखो_trylock, __करोwn_ग_लिखो);
पूर्ण
EXPORT_SYMBOL(_करोwn_ग_लिखो_nest_lock);

व्योम करोwn_पढ़ो_non_owner(काष्ठा rw_semaphore *sem)
अणु
	might_sleep();
	__करोwn_पढ़ो(sem);
	__rwsem_set_पढ़ोer_owned(sem, शून्य);
पूर्ण
EXPORT_SYMBOL(करोwn_पढ़ो_non_owner);

व्योम करोwn_ग_लिखो_nested(काष्ठा rw_semaphore *sem, पूर्णांक subclass)
अणु
	might_sleep();
	rwsem_acquire(&sem->dep_map, subclass, 0, _RET_IP_);
	LOCK_CONTENDED(sem, __करोwn_ग_लिखो_trylock, __करोwn_ग_लिखो);
पूर्ण
EXPORT_SYMBOL(करोwn_ग_लिखो_nested);

पूर्णांक __sched करोwn_ग_लिखो_समाप्तable_nested(काष्ठा rw_semaphore *sem, पूर्णांक subclass)
अणु
	might_sleep();
	rwsem_acquire(&sem->dep_map, subclass, 0, _RET_IP_);

	अगर (LOCK_CONTENDED_RETURN(sem, __करोwn_ग_लिखो_trylock,
				  __करोwn_ग_लिखो_समाप्तable)) अणु
		rwsem_release(&sem->dep_map, _RET_IP_);
		वापस -EINTR;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(करोwn_ग_लिखो_समाप्तable_nested);

व्योम up_पढ़ो_non_owner(काष्ठा rw_semaphore *sem)
अणु
	DEBUG_RWSEMS_WARN_ON(!is_rwsem_पढ़ोer_owned(sem), sem);
	__up_पढ़ो(sem);
पूर्ण
EXPORT_SYMBOL(up_पढ़ो_non_owner);

#पूर्ण_अगर
