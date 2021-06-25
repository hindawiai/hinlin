<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Queued spinlock
 *
 * (C) Copyright 2013-2015 Hewlett-Packard Development Company, L.P.
 * (C) Copyright 2015 Hewlett-Packard Enterprise Development LP
 *
 * Authors: Waiman Long <waiman.दीर्घ@hpe.com>
 */
#अगर_अघोषित __ASM_GENERIC_QSPINLOCK_H
#घोषणा __ASM_GENERIC_QSPINLOCK_H

#समावेश <यंत्र-generic/qspinlock_types.h>
#समावेश <linux/atomic.h>

#अगर_अघोषित queued_spin_is_locked
/**
 * queued_spin_is_locked - is the spinlock locked?
 * @lock: Poपूर्णांकer to queued spinlock काष्ठाure
 * Return: 1 अगर it is locked, 0 otherwise
 */
अटल __always_अंतरभूत पूर्णांक queued_spin_is_locked(काष्ठा qspinlock *lock)
अणु
	/*
	 * Any !0 state indicates it is locked, even अगर _Q_LOCKED_VAL
	 * isn't immediately observable.
	 */
	वापस atomic_पढ़ो(&lock->val);
पूर्ण
#पूर्ण_अगर

/**
 * queued_spin_value_unlocked - is the spinlock काष्ठाure unlocked?
 * @lock: queued spinlock काष्ठाure
 * Return: 1 अगर it is unlocked, 0 otherwise
 *
 * N.B. Whenever there are tasks रुकोing क्रम the lock, it is considered
 *      locked wrt the lockref code to aव्योम lock stealing by the lockref
 *      code and change things underneath the lock. This also allows some
 *      optimizations to be applied without conflict with lockref.
 */
अटल __always_अंतरभूत पूर्णांक queued_spin_value_unlocked(काष्ठा qspinlock lock)
अणु
	वापस !atomic_पढ़ो(&lock.val);
पूर्ण

/**
 * queued_spin_is_contended - check अगर the lock is contended
 * @lock : Poपूर्णांकer to queued spinlock काष्ठाure
 * Return: 1 अगर lock contended, 0 otherwise
 */
अटल __always_अंतरभूत पूर्णांक queued_spin_is_contended(काष्ठा qspinlock *lock)
अणु
	वापस atomic_पढ़ो(&lock->val) & ~_Q_LOCKED_MASK;
पूर्ण
/**
 * queued_spin_trylock - try to acquire the queued spinlock
 * @lock : Poपूर्णांकer to queued spinlock काष्ठाure
 * Return: 1 अगर lock acquired, 0 अगर failed
 */
अटल __always_अंतरभूत पूर्णांक queued_spin_trylock(काष्ठा qspinlock *lock)
अणु
	पूर्णांक val = atomic_पढ़ो(&lock->val);

	अगर (unlikely(val))
		वापस 0;

	वापस likely(atomic_try_cmpxchg_acquire(&lock->val, &val, _Q_LOCKED_VAL));
पूर्ण

बाह्य व्योम queued_spin_lock_slowpath(काष्ठा qspinlock *lock, u32 val);

#अगर_अघोषित queued_spin_lock
/**
 * queued_spin_lock - acquire a queued spinlock
 * @lock: Poपूर्णांकer to queued spinlock काष्ठाure
 */
अटल __always_अंतरभूत व्योम queued_spin_lock(काष्ठा qspinlock *lock)
अणु
	पूर्णांक val = 0;

	अगर (likely(atomic_try_cmpxchg_acquire(&lock->val, &val, _Q_LOCKED_VAL)))
		वापस;

	queued_spin_lock_slowpath(lock, val);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित queued_spin_unlock
/**
 * queued_spin_unlock - release a queued spinlock
 * @lock : Poपूर्णांकer to queued spinlock काष्ठाure
 */
अटल __always_अंतरभूत व्योम queued_spin_unlock(काष्ठा qspinlock *lock)
अणु
	/*
	 * unlock() needs release semantics:
	 */
	smp_store_release(&lock->locked, 0);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित virt_spin_lock
अटल __always_अंतरभूत bool virt_spin_lock(काष्ठा qspinlock *lock)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

/*
 * Remapping spinlock architecture specअगरic functions to the corresponding
 * queued spinlock functions.
 */
#घोषणा arch_spin_is_locked(l)		queued_spin_is_locked(l)
#घोषणा arch_spin_is_contended(l)	queued_spin_is_contended(l)
#घोषणा arch_spin_value_unlocked(l)	queued_spin_value_unlocked(l)
#घोषणा arch_spin_lock(l)		queued_spin_lock(l)
#घोषणा arch_spin_trylock(l)		queued_spin_trylock(l)
#घोषणा arch_spin_unlock(l)		queued_spin_unlock(l)

#पूर्ण_अगर /* __ASM_GENERIC_QSPINLOCK_H */
