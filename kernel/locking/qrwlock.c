<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Queued पढ़ो/ग_लिखो locks
 *
 * (C) Copyright 2013-2014 Hewlett-Packard Development Company, L.P.
 *
 * Authors: Waiman Long <waiman.दीर्घ@hp.com>
 */
#समावेश <linux/smp.h>
#समावेश <linux/bug.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/percpu.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/spinlock.h>

/**
 * queued_पढ़ो_lock_slowpath - acquire पढ़ो lock of a queue rwlock
 * @lock: Poपूर्णांकer to queue rwlock काष्ठाure
 */
व्योम queued_पढ़ो_lock_slowpath(काष्ठा qrwlock *lock)
अणु
	/*
	 * Readers come here when they cannot get the lock without रुकोing
	 */
	अगर (unlikely(in_पूर्णांकerrupt())) अणु
		/*
		 * Readers in पूर्णांकerrupt context will get the lock immediately
		 * अगर the ग_लिखोr is just रुकोing (not holding the lock yet),
		 * so spin with ACQUIRE semantics until the lock is available
		 * without रुकोing in the queue.
		 */
		atomic_cond_पढ़ो_acquire(&lock->cnts, !(VAL & _QW_LOCKED));
		वापस;
	पूर्ण
	atomic_sub(_QR_BIAS, &lock->cnts);

	/*
	 * Put the पढ़ोer पूर्णांकo the रुको queue
	 */
	arch_spin_lock(&lock->रुको_lock);
	atomic_add(_QR_BIAS, &lock->cnts);

	/*
	 * The ACQUIRE semantics of the following spinning code ensure
	 * that accesses can't leak upwards out of our subsequent critical
	 * section in the हाल that the lock is currently held क्रम ग_लिखो.
	 */
	atomic_cond_पढ़ो_acquire(&lock->cnts, !(VAL & _QW_LOCKED));

	/*
	 * Signal the next one in queue to become queue head
	 */
	arch_spin_unlock(&lock->रुको_lock);
पूर्ण
EXPORT_SYMBOL(queued_पढ़ो_lock_slowpath);

/**
 * queued_ग_लिखो_lock_slowpath - acquire ग_लिखो lock of a queue rwlock
 * @lock : Poपूर्णांकer to queue rwlock काष्ठाure
 */
व्योम queued_ग_लिखो_lock_slowpath(काष्ठा qrwlock *lock)
अणु
	पूर्णांक cnts;

	/* Put the ग_लिखोr पूर्णांकo the रुको queue */
	arch_spin_lock(&lock->रुको_lock);

	/* Try to acquire the lock directly अगर no पढ़ोer is present */
	अगर (!(cnts = atomic_पढ़ो(&lock->cnts)) &&
	    atomic_try_cmpxchg_acquire(&lock->cnts, &cnts, _QW_LOCKED))
		जाओ unlock;

	/* Set the रुकोing flag to notअगरy पढ़ोers that a ग_लिखोr is pending */
	atomic_or(_QW_WAITING, &lock->cnts);

	/* When no more पढ़ोers or ग_लिखोrs, set the locked flag */
	करो अणु
		cnts = atomic_cond_पढ़ो_relaxed(&lock->cnts, VAL == _QW_WAITING);
	पूर्ण जबतक (!atomic_try_cmpxchg_acquire(&lock->cnts, &cnts, _QW_LOCKED));
unlock:
	arch_spin_unlock(&lock->रुको_lock);
पूर्ण
EXPORT_SYMBOL(queued_ग_लिखो_lock_slowpath);
