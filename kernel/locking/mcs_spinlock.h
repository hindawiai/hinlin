<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * MCS lock defines
 *
 * This file contains the मुख्य data काष्ठाure and API definitions of MCS lock.
 *
 * The MCS lock (proposed by Mellor-Crummey and Scott) is a simple spin-lock
 * with the desirable properties of being fair, and with each cpu trying
 * to acquire the lock spinning on a local variable.
 * It aव्योमs expensive cache bounces that common test-and-set spin-lock
 * implementations incur.
 */
#अगर_अघोषित __LINUX_MCS_SPINLOCK_H
#घोषणा __LINUX_MCS_SPINLOCK_H

#समावेश <यंत्र/mcs_spinlock.h>

काष्ठा mcs_spinlock अणु
	काष्ठा mcs_spinlock *next;
	पूर्णांक locked; /* 1 अगर lock acquired */
	पूर्णांक count;  /* nesting count, see qspinlock.c */
पूर्ण;

#अगर_अघोषित arch_mcs_spin_lock_contended
/*
 * Using smp_cond_load_acquire() provides the acquire semantics
 * required so that subsequent operations happen after the
 * lock is acquired. Additionally, some architectures such as
 * ARM64 would like to करो spin-रुकोing instead of purely
 * spinning, and smp_cond_load_acquire() provides that behavior.
 */
#घोषणा arch_mcs_spin_lock_contended(l)					\
करो अणु									\
	smp_cond_load_acquire(l, VAL);					\
पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_अघोषित arch_mcs_spin_unlock_contended
/*
 * smp_store_release() provides a memory barrier to ensure all
 * operations in the critical section has been completed beक्रमe
 * unlocking.
 */
#घोषणा arch_mcs_spin_unlock_contended(l)				\
	smp_store_release((l), 1)
#पूर्ण_अगर

/*
 * Note: the smp_load_acquire/smp_store_release pair is not
 * sufficient to क्रमm a full memory barrier across
 * cpus क्रम many architectures (except x86) क्रम mcs_unlock and mcs_lock.
 * For applications that need a full barrier across multiple cpus
 * with mcs_unlock and mcs_lock pair, smp_mb__after_unlock_lock() should be
 * used after mcs_lock.
 */

/*
 * In order to acquire the lock, the caller should declare a local node and
 * pass a reference of the node to this function in addition to the lock.
 * If the lock has alपढ़ोy been acquired, then this will proceed to spin
 * on this node->locked until the previous lock holder sets the node->locked
 * in mcs_spin_unlock().
 */
अटल अंतरभूत
व्योम mcs_spin_lock(काष्ठा mcs_spinlock **lock, काष्ठा mcs_spinlock *node)
अणु
	काष्ठा mcs_spinlock *prev;

	/* Init node */
	node->locked = 0;
	node->next   = शून्य;

	/*
	 * We rely on the full barrier with global transitivity implied by the
	 * below xchg() to order the initialization stores above against any
	 * observation of @node. And to provide the ACQUIRE ordering associated
	 * with a LOCK primitive.
	 */
	prev = xchg(lock, node);
	अगर (likely(prev == शून्य)) अणु
		/*
		 * Lock acquired, करोn't need to set node->locked to 1. Thपढ़ोs
		 * only spin on its own node->locked value क्रम lock acquisition.
		 * However, since this thपढ़ो can immediately acquire the lock
		 * and करोes not proceed to spin on its own node->locked, this
		 * value won't be used. If a debug mode is needed to
		 * audit lock status, then set node->locked value here.
		 */
		वापस;
	पूर्ण
	WRITE_ONCE(prev->next, node);

	/* Wait until the lock holder passes the lock करोwn. */
	arch_mcs_spin_lock_contended(&node->locked);
पूर्ण

/*
 * Releases the lock. The caller should pass in the corresponding node that
 * was used to acquire the lock.
 */
अटल अंतरभूत
व्योम mcs_spin_unlock(काष्ठा mcs_spinlock **lock, काष्ठा mcs_spinlock *node)
अणु
	काष्ठा mcs_spinlock *next = READ_ONCE(node->next);

	अगर (likely(!next)) अणु
		/*
		 * Release the lock by setting it to शून्य
		 */
		अगर (likely(cmpxchg_release(lock, node, शून्य) == node))
			वापस;
		/* Wait until the next poपूर्णांकer is set */
		जबतक (!(next = READ_ONCE(node->next)))
			cpu_relax();
	पूर्ण

	/* Pass lock to next रुकोer. */
	arch_mcs_spin_unlock_contended(&next->locked);
पूर्ण

#पूर्ण_अगर /* __LINUX_MCS_SPINLOCK_H */
