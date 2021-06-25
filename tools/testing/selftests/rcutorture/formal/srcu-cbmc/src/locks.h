<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LOCKS_H
#घोषणा LOCKS_H

#समावेश <सीमा.स>
#समावेश <pthपढ़ो.h>
#समावेश <stdbool.h>

#समावेश "assume.h"
#समावेश "bug_on.h"
#समावेश "preempt.h"

पूर्णांक nondet_पूर्णांक(व्योम);

#घोषणा __acquire(x)
#घोषणा __acquires(x)
#घोषणा __release(x)
#घोषणा __releases(x)

/* Only use one lock mechanism. Select which one. */
#अगर_घोषित PTHREAD_LOCK
काष्ठा lock_impl अणु
	pthपढ़ो_mutex_t mutex;
पूर्ण;

अटल अंतरभूत व्योम lock_impl_lock(काष्ठा lock_impl *lock)
अणु
	BUG_ON(pthपढ़ो_mutex_lock(&lock->mutex));
पूर्ण

अटल अंतरभूत व्योम lock_impl_unlock(काष्ठा lock_impl *lock)
अणु
	BUG_ON(pthपढ़ो_mutex_unlock(&lock->mutex));
पूर्ण

अटल अंतरभूत bool lock_impl_trylock(काष्ठा lock_impl *lock)
अणु
	पूर्णांक err = pthपढ़ो_mutex_trylock(&lock->mutex);

	अगर (!err)
		वापस true;
	अन्यथा अगर (err == EBUSY)
		वापस false;
	BUG();
पूर्ण

अटल अंतरभूत व्योम lock_impl_init(काष्ठा lock_impl *lock)
अणु
	pthपढ़ो_mutex_init(&lock->mutex, शून्य);
पूर्ण

#घोषणा LOCK_IMPL_INITIALIZER अणु.mutex = PTHREAD_MUTEX_INITIALIZERपूर्ण

#अन्यथा /* !defined(PTHREAD_LOCK) */
/* Spinlock that assumes that it always माला_लो the lock immediately. */

काष्ठा lock_impl अणु
	bool locked;
पूर्ण;

अटल अंतरभूत bool lock_impl_trylock(काष्ठा lock_impl *lock)
अणु
#अगर_घोषित RUN
	/* TODO: Should this be a test and set? */
	वापस __sync_bool_compare_and_swap(&lock->locked, false, true);
#अन्यथा
	__CPROVER_atomic_begin();
	bool old_locked = lock->locked;
	lock->locked = true;
	__CPROVER_atomic_end();

	/* Minimal barrier to prevent accesses leaking out of lock. */
	__CPROVER_fence("RRfence", "RWfence");

	वापस !old_locked;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम lock_impl_lock(काष्ठा lock_impl *lock)
अणु
	/*
	 * CBMC करोesn't support busy रुकोing, so just assume that the
	 * lock is available.
	 */
	assume(lock_impl_trylock(lock));

	/*
	 * If the lock was alपढ़ोy held by this thपढ़ो then the assumption
	 * is unsatisfiable (deadlock).
	 */
पूर्ण

अटल अंतरभूत व्योम lock_impl_unlock(काष्ठा lock_impl *lock)
अणु
#अगर_घोषित RUN
	BUG_ON(!__sync_bool_compare_and_swap(&lock->locked, true, false));
#अन्यथा
	/* Minimal barrier to prevent accesses leaking out of lock. */
	__CPROVER_fence("RWfence", "WWfence");

	__CPROVER_atomic_begin();
	bool old_locked = lock->locked;
	lock->locked = false;
	__CPROVER_atomic_end();

	BUG_ON(!old_locked);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम lock_impl_init(काष्ठा lock_impl *lock)
अणु
	lock->locked = false;
पूर्ण

#घोषणा LOCK_IMPL_INITIALIZER अणु.locked = falseपूर्ण

#पूर्ण_अगर /* !defined(PTHREAD_LOCK) */

/*
 * Implement spinlocks using the lock mechanism. Wrap the lock to prevent mixing
 * locks of dअगरferent types.
 */
प्रकार काष्ठा अणु
	काष्ठा lock_impl पूर्णांकernal_lock;
पूर्ण spinlock_t;

#घोषणा SPIN_LOCK_UNLOCKED अणु.पूर्णांकernal_lock = LOCK_IMPL_INITIALIZERपूर्ण
#घोषणा __SPIN_LOCK_UNLOCKED(x) SPIN_LOCK_UNLOCKED
#घोषणा DEFINE_SPINLOCK(x) spinlock_t x = SPIN_LOCK_UNLOCKED

अटल अंतरभूत व्योम spin_lock_init(spinlock_t *lock)
अणु
	lock_impl_init(&lock->पूर्णांकernal_lock);
पूर्ण

अटल अंतरभूत व्योम spin_lock(spinlock_t *lock)
अणु
	/*
	 * Spin locks also need to be हटाओd in order to eliminate all
	 * memory barriers. They are only used by the ग_लिखो side anyway.
	 */
#अगर_अघोषित NO_SYNC_SMP_MB
	preempt_disable();
	lock_impl_lock(&lock->पूर्णांकernal_lock);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम spin_unlock(spinlock_t *lock)
अणु
#अगर_अघोषित NO_SYNC_SMP_MB
	lock_impl_unlock(&lock->पूर्णांकernal_lock);
	preempt_enable();
#पूर्ण_अगर
पूर्ण

/* Don't bother with पूर्णांकerrupts */
#घोषणा spin_lock_irq(lock) spin_lock(lock)
#घोषणा spin_unlock_irq(lock) spin_unlock(lock)
#घोषणा spin_lock_irqsave(lock, flags) spin_lock(lock)
#घोषणा spin_unlock_irqrestore(lock, flags) spin_unlock(lock)

/*
 * This is supposed to वापस an पूर्णांक, but I think that a bool should work as
 * well.
 */
अटल अंतरभूत bool spin_trylock(spinlock_t *lock)
अणु
#अगर_अघोषित NO_SYNC_SMP_MB
	preempt_disable();
	वापस lock_impl_trylock(&lock->पूर्णांकernal_lock);
#अन्यथा
	वापस true;
#पूर्ण_अगर
पूर्ण

काष्ठा completion अणु
	/* Hopefuly this won't overflow. */
	अचिन्हित पूर्णांक count;
पूर्ण;

#घोषणा COMPLETION_INITIALIZER(x) अणु.count = 0पूर्ण
#घोषणा DECLARE_COMPLETION(x) काष्ठा completion x = COMPLETION_INITIALIZER(x)
#घोषणा DECLARE_COMPLETION_ONSTACK(x) DECLARE_COMPLETION(x)

अटल अंतरभूत व्योम init_completion(काष्ठा completion *c)
अणु
	c->count = 0;
पूर्ण

अटल अंतरभूत व्योम रुको_क्रम_completion(काष्ठा completion *c)
अणु
	अचिन्हित पूर्णांक prev_count = __sync_fetch_and_sub(&c->count, 1);

	assume(prev_count);
पूर्ण

अटल अंतरभूत व्योम complete(काष्ठा completion *c)
अणु
	अचिन्हित पूर्णांक prev_count = __sync_fetch_and_add(&c->count, 1);

	BUG_ON(prev_count == अच_पूर्णांक_उच्च);
पूर्ण

/* This function probably isn't very useful क्रम CBMC. */
अटल अंतरभूत bool try_रुको_क्रम_completion(काष्ठा completion *c)
अणु
	BUG();
पूर्ण

अटल अंतरभूत bool completion_करोne(काष्ठा completion *c)
अणु
	वापस c->count;
पूर्ण

/* TODO: Implement complete_all */
अटल अंतरभूत व्योम complete_all(काष्ठा completion *c)
अणु
	BUG();
पूर्ण

#पूर्ण_अगर
