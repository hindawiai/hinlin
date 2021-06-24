<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Queue पढ़ो/ग_लिखो lock
 *
 * (C) Copyright 2013-2014 Hewlett-Packard Development Company, L.P.
 *
 * Authors: Waiman Long <waiman.दीर्घ@hp.com>
 */
#अगर_अघोषित __ASM_GENERIC_QRWLOCK_H
#घोषणा __ASM_GENERIC_QRWLOCK_H

#समावेश <linux/atomic.h>
#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/processor.h>

#समावेश <यंत्र-generic/qrwlock_types.h>

/* Must be included from यंत्र/spinlock.h after defining arch_spin_is_locked.  */

/*
 * Writer states & पढ़ोer shअगरt and bias.
 */
#घोषणा	_QW_WAITING	0x100		/* A ग_लिखोr is रुकोing	   */
#घोषणा	_QW_LOCKED	0x0ff		/* A ग_लिखोr holds the lock */
#घोषणा	_QW_WMASK	0x1ff		/* Writer mask		   */
#घोषणा	_QR_SHIFT	9		/* Reader count shअगरt	   */
#घोषणा _QR_BIAS	(1U << _QR_SHIFT)

/*
 * External function declarations
 */
बाह्य व्योम queued_पढ़ो_lock_slowpath(काष्ठा qrwlock *lock);
बाह्य व्योम queued_ग_लिखो_lock_slowpath(काष्ठा qrwlock *lock);

/**
 * queued_पढ़ो_trylock - try to acquire पढ़ो lock of a queue rwlock
 * @lock : Poपूर्णांकer to queue rwlock काष्ठाure
 * Return: 1 अगर lock acquired, 0 अगर failed
 */
अटल अंतरभूत पूर्णांक queued_पढ़ो_trylock(काष्ठा qrwlock *lock)
अणु
	पूर्णांक cnts;

	cnts = atomic_पढ़ो(&lock->cnts);
	अगर (likely(!(cnts & _QW_WMASK))) अणु
		cnts = (u32)atomic_add_वापस_acquire(_QR_BIAS, &lock->cnts);
		अगर (likely(!(cnts & _QW_WMASK)))
			वापस 1;
		atomic_sub(_QR_BIAS, &lock->cnts);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * queued_ग_लिखो_trylock - try to acquire ग_लिखो lock of a queue rwlock
 * @lock : Poपूर्णांकer to queue rwlock काष्ठाure
 * Return: 1 अगर lock acquired, 0 अगर failed
 */
अटल अंतरभूत पूर्णांक queued_ग_लिखो_trylock(काष्ठा qrwlock *lock)
अणु
	पूर्णांक cnts;

	cnts = atomic_पढ़ो(&lock->cnts);
	अगर (unlikely(cnts))
		वापस 0;

	वापस likely(atomic_try_cmpxchg_acquire(&lock->cnts, &cnts,
				_QW_LOCKED));
पूर्ण
/**
 * queued_पढ़ो_lock - acquire पढ़ो lock of a queue rwlock
 * @lock: Poपूर्णांकer to queue rwlock काष्ठाure
 */
अटल अंतरभूत व्योम queued_पढ़ो_lock(काष्ठा qrwlock *lock)
अणु
	पूर्णांक cnts;

	cnts = atomic_add_वापस_acquire(_QR_BIAS, &lock->cnts);
	अगर (likely(!(cnts & _QW_WMASK)))
		वापस;

	/* The slowpath will decrement the पढ़ोer count, अगर necessary. */
	queued_पढ़ो_lock_slowpath(lock);
पूर्ण

/**
 * queued_ग_लिखो_lock - acquire ग_लिखो lock of a queue rwlock
 * @lock : Poपूर्णांकer to queue rwlock काष्ठाure
 */
अटल अंतरभूत व्योम queued_ग_लिखो_lock(काष्ठा qrwlock *lock)
अणु
	पूर्णांक cnts = 0;
	/* Optimize क्रम the unfair lock हाल where the fair flag is 0. */
	अगर (likely(atomic_try_cmpxchg_acquire(&lock->cnts, &cnts, _QW_LOCKED)))
		वापस;

	queued_ग_लिखो_lock_slowpath(lock);
पूर्ण

/**
 * queued_पढ़ो_unlock - release पढ़ो lock of a queue rwlock
 * @lock : Poपूर्णांकer to queue rwlock काष्ठाure
 */
अटल अंतरभूत व्योम queued_पढ़ो_unlock(काष्ठा qrwlock *lock)
अणु
	/*
	 * Atomically decrement the पढ़ोer count
	 */
	(व्योम)atomic_sub_वापस_release(_QR_BIAS, &lock->cnts);
पूर्ण

/**
 * queued_ग_लिखो_unlock - release ग_लिखो lock of a queue rwlock
 * @lock : Poपूर्णांकer to queue rwlock काष्ठाure
 */
अटल अंतरभूत व्योम queued_ग_लिखो_unlock(काष्ठा qrwlock *lock)
अणु
	smp_store_release(&lock->wlocked, 0);
पूर्ण

/**
 * queued_rwlock_is_contended - check अगर the lock is contended
 * @lock : Poपूर्णांकer to queue rwlock काष्ठाure
 * Return: 1 अगर lock contended, 0 otherwise
 */
अटल अंतरभूत पूर्णांक queued_rwlock_is_contended(काष्ठा qrwlock *lock)
अणु
	वापस arch_spin_is_locked(&lock->रुको_lock);
पूर्ण

/*
 * Remapping rwlock architecture specअगरic functions to the corresponding
 * queue rwlock functions.
 */
#घोषणा arch_पढ़ो_lock(l)		queued_पढ़ो_lock(l)
#घोषणा arch_ग_लिखो_lock(l)		queued_ग_लिखो_lock(l)
#घोषणा arch_पढ़ो_trylock(l)		queued_पढ़ो_trylock(l)
#घोषणा arch_ग_लिखो_trylock(l)		queued_ग_लिखो_trylock(l)
#घोषणा arch_पढ़ो_unlock(l)		queued_पढ़ो_unlock(l)
#घोषणा arch_ग_लिखो_unlock(l)		queued_ग_लिखो_unlock(l)
#घोषणा arch_rwlock_is_contended(l)	queued_rwlock_is_contended(l)

#पूर्ण_अगर /* __ASM_GENERIC_QRWLOCK_H */
