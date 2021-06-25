<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Out-of-line refcount functions.
 */

#समावेश <linux/mutex.h>
#समावेश <linux/refcount.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/bug.h>

#घोषणा REFCOUNT_WARN(str)	WARN_ONCE(1, "refcount_t: " str ".\n")

व्योम refcount_warn_saturate(refcount_t *r, क्रमागत refcount_saturation_type t)
अणु
	refcount_set(r, REFCOUNT_SATURATED);

	चयन (t) अणु
	हाल REFCOUNT_ADD_NOT_ZERO_OVF:
		REFCOUNT_WARN("saturated; leaking memory");
		अवरोध;
	हाल REFCOUNT_ADD_OVF:
		REFCOUNT_WARN("saturated; leaking memory");
		अवरोध;
	हाल REFCOUNT_ADD_UAF:
		REFCOUNT_WARN("addition on 0; use-after-free");
		अवरोध;
	हाल REFCOUNT_SUB_UAF:
		REFCOUNT_WARN("underflow; use-after-free");
		अवरोध;
	हाल REFCOUNT_DEC_LEAK:
		REFCOUNT_WARN("decrement hit 0; leaking memory");
		अवरोध;
	शेष:
		REFCOUNT_WARN("unknown saturation event!?");
	पूर्ण
पूर्ण
EXPORT_SYMBOL(refcount_warn_saturate);

/**
 * refcount_dec_अगर_one - decrement a refcount अगर it is 1
 * @r: the refcount
 *
 * No atomic_t counterpart, it attempts a 1 -> 0 transition and वापसs the
 * success thereof.
 *
 * Like all decrement operations, it provides release memory order and provides
 * a control dependency.
 *
 * It can be used like a try-delete चालक; this explicit हाल is provided
 * and not cmpxchg in generic, because that would allow implementing unsafe
 * operations.
 *
 * Return: true अगर the resulting refcount is 0, false otherwise
 */
bool refcount_dec_अगर_one(refcount_t *r)
अणु
	पूर्णांक val = 1;

	वापस atomic_try_cmpxchg_release(&r->refs, &val, 0);
पूर्ण
EXPORT_SYMBOL(refcount_dec_अगर_one);

/**
 * refcount_dec_not_one - decrement a refcount अगर it is not 1
 * @r: the refcount
 *
 * No atomic_t counterpart, it decrements unless the value is 1, in which हाल
 * it will वापस false.
 *
 * Was often करोne like: atomic_add_unless(&var, -1, 1)
 *
 * Return: true अगर the decrement operation was successful, false otherwise
 */
bool refcount_dec_not_one(refcount_t *r)
अणु
	अचिन्हित पूर्णांक new, val = atomic_पढ़ो(&r->refs);

	करो अणु
		अगर (unlikely(val == REFCOUNT_SATURATED))
			वापस true;

		अगर (val == 1)
			वापस false;

		new = val - 1;
		अगर (new > val) अणु
			WARN_ONCE(new > val, "refcount_t: underflow; use-after-free.\n");
			वापस true;
		पूर्ण

	पूर्ण जबतक (!atomic_try_cmpxchg_release(&r->refs, &val, new));

	वापस true;
पूर्ण
EXPORT_SYMBOL(refcount_dec_not_one);

/**
 * refcount_dec_and_mutex_lock - वापस holding mutex अगर able to decrement
 *                               refcount to 0
 * @r: the refcount
 * @lock: the mutex to be locked
 *
 * Similar to atomic_dec_and_mutex_lock(), it will WARN on underflow and fail
 * to decrement when saturated at REFCOUNT_SATURATED.
 *
 * Provides release memory ordering, such that prior loads and stores are करोne
 * beक्रमe, and provides a control dependency such that मुक्त() must come after.
 * See the comment on top.
 *
 * Return: true and hold mutex अगर able to decrement refcount to 0, false
 *         otherwise
 */
bool refcount_dec_and_mutex_lock(refcount_t *r, काष्ठा mutex *lock)
अणु
	अगर (refcount_dec_not_one(r))
		वापस false;

	mutex_lock(lock);
	अगर (!refcount_dec_and_test(r)) अणु
		mutex_unlock(lock);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL(refcount_dec_and_mutex_lock);

/**
 * refcount_dec_and_lock - वापस holding spinlock अगर able to decrement
 *                         refcount to 0
 * @r: the refcount
 * @lock: the spinlock to be locked
 *
 * Similar to atomic_dec_and_lock(), it will WARN on underflow and fail to
 * decrement when saturated at REFCOUNT_SATURATED.
 *
 * Provides release memory ordering, such that prior loads and stores are करोne
 * beक्रमe, and provides a control dependency such that मुक्त() must come after.
 * See the comment on top.
 *
 * Return: true and hold spinlock अगर able to decrement refcount to 0, false
 *         otherwise
 */
bool refcount_dec_and_lock(refcount_t *r, spinlock_t *lock)
अणु
	अगर (refcount_dec_not_one(r))
		वापस false;

	spin_lock(lock);
	अगर (!refcount_dec_and_test(r)) अणु
		spin_unlock(lock);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL(refcount_dec_and_lock);

/**
 * refcount_dec_and_lock_irqsave - वापस holding spinlock with disabled
 *                                 पूर्णांकerrupts अगर able to decrement refcount to 0
 * @r: the refcount
 * @lock: the spinlock to be locked
 * @flags: saved IRQ-flags अगर the is acquired
 *
 * Same as refcount_dec_and_lock() above except that the spinlock is acquired
 * with disabled पूर्णांकerupts.
 *
 * Return: true and hold spinlock अगर able to decrement refcount to 0, false
 *         otherwise
 */
bool refcount_dec_and_lock_irqsave(refcount_t *r, spinlock_t *lock,
				   अचिन्हित दीर्घ *flags)
अणु
	अगर (refcount_dec_not_one(r))
		वापस false;

	spin_lock_irqsave(lock, *flags);
	अगर (!refcount_dec_and_test(r)) अणु
		spin_unlock_irqrestore(lock, *flags);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL(refcount_dec_and_lock_irqsave);
