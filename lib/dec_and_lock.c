<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/export.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/atomic.h>

/*
 * This is an implementation of the notion of "decrement a
 * reference count, and वापस locked अगर it decremented to zero".
 *
 * NOTE NOTE NOTE! This is _not_ equivalent to
 *
 *	अगर (atomic_dec_and_test(&atomic)) अणु
 *		spin_lock(&lock);
 *		वापस 1;
 *	पूर्ण
 *	वापस 0;
 *
 * because the spin-lock and the decrement must be
 * "atomic".
 */
पूर्णांक _atomic_dec_and_lock(atomic_t *atomic, spinlock_t *lock)
अणु
	/* Subtract 1 from counter unless that drops it to 0 (ie. it was 1) */
	अगर (atomic_add_unless(atomic, -1, 1))
		वापस 0;

	/* Otherwise करो it the slow way */
	spin_lock(lock);
	अगर (atomic_dec_and_test(atomic))
		वापस 1;
	spin_unlock(lock);
	वापस 0;
पूर्ण

EXPORT_SYMBOL(_atomic_dec_and_lock);

पूर्णांक _atomic_dec_and_lock_irqsave(atomic_t *atomic, spinlock_t *lock,
				 अचिन्हित दीर्घ *flags)
अणु
	/* Subtract 1 from counter unless that drops it to 0 (ie. it was 1) */
	अगर (atomic_add_unless(atomic, -1, 1))
		वापस 0;

	/* Otherwise करो it the slow way */
	spin_lock_irqsave(lock, *flags);
	अगर (atomic_dec_and_test(atomic))
		वापस 1;
	spin_unlock_irqrestore(lock, *flags);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(_atomic_dec_and_lock_irqsave);
