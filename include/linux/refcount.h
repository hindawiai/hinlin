<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Variant of atomic_t specialized क्रम reference counts.
 *
 * The पूर्णांकerface matches the atomic_t पूर्णांकerface (to aid in porting) but only
 * provides the few functions one should use क्रम reference counting.
 *
 * Saturation semantics
 * ====================
 *
 * refcount_t dअगरfers from atomic_t in that the counter saturates at
 * REFCOUNT_SATURATED and will not move once there. This aव्योमs wrapping the
 * counter and causing 'spurious' use-after-मुक्त issues. In order to aव्योम the
 * cost associated with पूर्णांकroducing cmpxchg() loops पूर्णांकo all of the saturating
 * operations, we temporarily allow the counter to take on an unchecked value
 * and then explicitly set it to REFCOUNT_SATURATED on detecting that underflow
 * or overflow has occurred. Although this is racy when multiple thपढ़ोs
 * access the refcount concurrently, by placing REFCOUNT_SATURATED roughly
 * equidistant from 0 and पूर्णांक_उच्च we minimise the scope क्रम error:
 *
 * 	                           पूर्णांक_उच्च     REFCOUNT_SATURATED   अच_पूर्णांक_उच्च
 *   0                          (0x7fff_ffff)    (0xc000_0000)    (0xffff_ffff)
 *   +--------------------------------+----------------+----------------+
 *                                     <---------- bad value! ---------->
 *
 * (in a चिन्हित view of the world, the "bad value" range corresponds to
 * a negative counter value).
 *
 * As an example, consider a refcount_inc() operation that causes the counter
 * to overflow:
 *
 * 	पूर्णांक old = atomic_fetch_add_relaxed(r);
 *	// old is पूर्णांक_उच्च, refcount now पूर्णांक_न्यून (0x8000_0000)
 *	अगर (old < 0)
 *		atomic_set(r, REFCOUNT_SATURATED);
 *
 * If another thपढ़ो also perक्रमms a refcount_inc() operation between the two
 * atomic operations, then the count will जारी to edge बंदr to 0. If it
 * reaches a value of 1 beक्रमe /any/ of the thपढ़ोs reset it to the saturated
 * value, then a concurrent refcount_dec_and_test() may erroneously मुक्त the
 * underlying object.
 * Linux limits the maximum number of tasks to PID_MAX_LIMIT, which is currently
 * 0x400000 (and can't easily be उठाओd in the future beyond FUTEX_TID_MASK).
 * With the current PID limit, अगर no batched refcounting operations are used and
 * the attacker can't repeatedly trigger kernel oopses in the middle of refcount
 * operations, this makes it impossible क्रम a saturated refcount to leave the
 * saturation range, even अगर it is possible क्रम multiple uses of the same
 * refcount to nest in the context of a single task:
 *
 *     (अच_पूर्णांक_उच्च+1-REFCOUNT_SATURATED) / PID_MAX_LIMIT =
 *     0x40000000 / 0x400000 = 0x100 = 256
 *
 * If hundreds of references are added/हटाओd with a single refcounting
 * operation, it may potentially be possible to leave the saturation range; but
 * given the precise timing details involved with the round-robin scheduling of
 * each thपढ़ो manipulating the refcount and the need to hit the race multiple
 * बार in succession, there करोesn't appear to be a practical avenue of attack
 * even अगर using refcount_add() operations with larger increments.
 *
 * Memory ordering
 * ===============
 *
 * Memory ordering rules are slightly relaxed wrt regular atomic_t functions
 * and provide only what is strictly required क्रम refcounts.
 *
 * The increments are fully relaxed; these will not provide ordering. The
 * rationale is that whatever is used to obtain the object we're increasing the
 * reference count on will provide the ordering. For locked data काष्ठाures,
 * its the lock acquire, क्रम RCU/lockless data काष्ठाures its the dependent
 * load.
 *
 * Do note that inc_not_zero() provides a control dependency which will order
 * future stores against the inc, this ensures we'll never modअगरy the object
 * अगर we did not in fact acquire a reference.
 *
 * The decrements will provide release order, such that all the prior loads and
 * stores will be issued beक्रमe, it also provides a control dependency, which
 * will order us against the subsequent मुक्त().
 *
 * The control dependency is against the load of the cmpxchg (ll/sc) that
 * succeeded. This means the stores aren't fully ordered, but this is fine
 * because the 1->0 transition indicates no concurrency.
 *
 * Note that the allocator is responsible क्रम ordering things between मुक्त()
 * and alloc().
 *
 * The decrements dec_and_test() and sub_and_test() also provide acquire
 * ordering on success.
 *
 */

#अगर_अघोषित _LINUX_REFCOUNT_H
#घोषणा _LINUX_REFCOUNT_H

#समावेश <linux/atomic.h>
#समावेश <linux/bug.h>
#समावेश <linux/compiler.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/spinlock_types.h>

काष्ठा mutex;

/**
 * प्रकार refcount_t - variant of atomic_t specialized क्रम reference counts
 * @refs: atomic_t counter field
 *
 * The counter saturates at REFCOUNT_SATURATED and will not move once
 * there. This aव्योमs wrapping the counter and causing 'spurious'
 * use-after-मुक्त bugs.
 */
प्रकार काष्ठा refcount_काष्ठा अणु
	atomic_t refs;
पूर्ण refcount_t;

#घोषणा REFCOUNT_INIT(n)	अणु .refs = ATOMIC_INIT(n), पूर्ण
#घोषणा REFCOUNT_MAX		पूर्णांक_उच्च
#घोषणा REFCOUNT_SATURATED	(पूर्णांक_न्यून / 2)

क्रमागत refcount_saturation_type अणु
	REFCOUNT_ADD_NOT_ZERO_OVF,
	REFCOUNT_ADD_OVF,
	REFCOUNT_ADD_UAF,
	REFCOUNT_SUB_UAF,
	REFCOUNT_DEC_LEAK,
पूर्ण;

व्योम refcount_warn_saturate(refcount_t *r, क्रमागत refcount_saturation_type t);

/**
 * refcount_set - set a refcount's value
 * @r: the refcount
 * @n: value to which the refcount will be set
 */
अटल अंतरभूत व्योम refcount_set(refcount_t *r, पूर्णांक n)
अणु
	atomic_set(&r->refs, n);
पूर्ण

/**
 * refcount_पढ़ो - get a refcount's value
 * @r: the refcount
 *
 * Return: the refcount's value
 */
अटल अंतरभूत अचिन्हित पूर्णांक refcount_पढ़ो(स्थिर refcount_t *r)
अणु
	वापस atomic_पढ़ो(&r->refs);
पूर्ण

अटल अंतरभूत __must_check bool __refcount_add_not_zero(पूर्णांक i, refcount_t *r, पूर्णांक *oldp)
अणु
	पूर्णांक old = refcount_पढ़ो(r);

	करो अणु
		अगर (!old)
			अवरोध;
	पूर्ण जबतक (!atomic_try_cmpxchg_relaxed(&r->refs, &old, old + i));

	अगर (oldp)
		*oldp = old;

	अगर (unlikely(old < 0 || old + i < 0))
		refcount_warn_saturate(r, REFCOUNT_ADD_NOT_ZERO_OVF);

	वापस old;
पूर्ण

/**
 * refcount_add_not_zero - add a value to a refcount unless it is 0
 * @i: the value to add to the refcount
 * @r: the refcount
 *
 * Will saturate at REFCOUNT_SATURATED and WARN.
 *
 * Provides no memory ordering, it is assumed the caller has guaranteed the
 * object memory to be stable (RCU, etc.). It करोes provide a control dependency
 * and thereby orders future stores. See the comment on top.
 *
 * Use of this function is not recommended क्रम the normal reference counting
 * use हाल in which references are taken and released one at a समय.  In these
 * हालs, refcount_inc(), or one of its variants, should instead be used to
 * increment a reference count.
 *
 * Return: false अगर the passed refcount is 0, true otherwise
 */
अटल अंतरभूत __must_check bool refcount_add_not_zero(पूर्णांक i, refcount_t *r)
अणु
	वापस __refcount_add_not_zero(i, r, शून्य);
पूर्ण

अटल अंतरभूत व्योम __refcount_add(पूर्णांक i, refcount_t *r, पूर्णांक *oldp)
अणु
	पूर्णांक old = atomic_fetch_add_relaxed(i, &r->refs);

	अगर (oldp)
		*oldp = old;

	अगर (unlikely(!old))
		refcount_warn_saturate(r, REFCOUNT_ADD_UAF);
	अन्यथा अगर (unlikely(old < 0 || old + i < 0))
		refcount_warn_saturate(r, REFCOUNT_ADD_OVF);
पूर्ण

/**
 * refcount_add - add a value to a refcount
 * @i: the value to add to the refcount
 * @r: the refcount
 *
 * Similar to atomic_add(), but will saturate at REFCOUNT_SATURATED and WARN.
 *
 * Provides no memory ordering, it is assumed the caller has guaranteed the
 * object memory to be stable (RCU, etc.). It करोes provide a control dependency
 * and thereby orders future stores. See the comment on top.
 *
 * Use of this function is not recommended क्रम the normal reference counting
 * use हाल in which references are taken and released one at a समय.  In these
 * हालs, refcount_inc(), or one of its variants, should instead be used to
 * increment a reference count.
 */
अटल अंतरभूत व्योम refcount_add(पूर्णांक i, refcount_t *r)
अणु
	__refcount_add(i, r, शून्य);
पूर्ण

अटल अंतरभूत __must_check bool __refcount_inc_not_zero(refcount_t *r, पूर्णांक *oldp)
अणु
	वापस __refcount_add_not_zero(1, r, oldp);
पूर्ण

/**
 * refcount_inc_not_zero - increment a refcount unless it is 0
 * @r: the refcount to increment
 *
 * Similar to atomic_inc_not_zero(), but will saturate at REFCOUNT_SATURATED
 * and WARN.
 *
 * Provides no memory ordering, it is assumed the caller has guaranteed the
 * object memory to be stable (RCU, etc.). It करोes provide a control dependency
 * and thereby orders future stores. See the comment on top.
 *
 * Return: true अगर the increment was successful, false otherwise
 */
अटल अंतरभूत __must_check bool refcount_inc_not_zero(refcount_t *r)
अणु
	वापस __refcount_inc_not_zero(r, शून्य);
पूर्ण

अटल अंतरभूत व्योम __refcount_inc(refcount_t *r, पूर्णांक *oldp)
अणु
	__refcount_add(1, r, oldp);
पूर्ण

/**
 * refcount_inc - increment a refcount
 * @r: the refcount to increment
 *
 * Similar to atomic_inc(), but will saturate at REFCOUNT_SATURATED and WARN.
 *
 * Provides no memory ordering, it is assumed the caller alपढ़ोy has a
 * reference on the object.
 *
 * Will WARN अगर the refcount is 0, as this represents a possible use-after-मुक्त
 * condition.
 */
अटल अंतरभूत व्योम refcount_inc(refcount_t *r)
अणु
	__refcount_inc(r, शून्य);
पूर्ण

अटल अंतरभूत __must_check bool __refcount_sub_and_test(पूर्णांक i, refcount_t *r, पूर्णांक *oldp)
अणु
	पूर्णांक old = atomic_fetch_sub_release(i, &r->refs);

	अगर (oldp)
		*oldp = old;

	अगर (old == i) अणु
		smp_acquire__after_ctrl_dep();
		वापस true;
	पूर्ण

	अगर (unlikely(old < 0 || old - i < 0))
		refcount_warn_saturate(r, REFCOUNT_SUB_UAF);

	वापस false;
पूर्ण

/**
 * refcount_sub_and_test - subtract from a refcount and test अगर it is 0
 * @i: amount to subtract from the refcount
 * @r: the refcount
 *
 * Similar to atomic_dec_and_test(), but it will WARN, वापस false and
 * ultimately leak on underflow and will fail to decrement when saturated
 * at REFCOUNT_SATURATED.
 *
 * Provides release memory ordering, such that prior loads and stores are करोne
 * beक्रमe, and provides an acquire ordering on success such that मुक्त()
 * must come after.
 *
 * Use of this function is not recommended क्रम the normal reference counting
 * use हाल in which references are taken and released one at a समय.  In these
 * हालs, refcount_dec(), or one of its variants, should instead be used to
 * decrement a reference count.
 *
 * Return: true अगर the resulting refcount is 0, false otherwise
 */
अटल अंतरभूत __must_check bool refcount_sub_and_test(पूर्णांक i, refcount_t *r)
अणु
	वापस __refcount_sub_and_test(i, r, शून्य);
पूर्ण

अटल अंतरभूत __must_check bool __refcount_dec_and_test(refcount_t *r, पूर्णांक *oldp)
अणु
	वापस __refcount_sub_and_test(1, r, oldp);
पूर्ण

/**
 * refcount_dec_and_test - decrement a refcount and test अगर it is 0
 * @r: the refcount
 *
 * Similar to atomic_dec_and_test(), it will WARN on underflow and fail to
 * decrement when saturated at REFCOUNT_SATURATED.
 *
 * Provides release memory ordering, such that prior loads and stores are करोne
 * beक्रमe, and provides an acquire ordering on success such that मुक्त()
 * must come after.
 *
 * Return: true अगर the resulting refcount is 0, false otherwise
 */
अटल अंतरभूत __must_check bool refcount_dec_and_test(refcount_t *r)
अणु
	वापस __refcount_dec_and_test(r, शून्य);
पूर्ण

अटल अंतरभूत व्योम __refcount_dec(refcount_t *r, पूर्णांक *oldp)
अणु
	पूर्णांक old = atomic_fetch_sub_release(1, &r->refs);

	अगर (oldp)
		*oldp = old;

	अगर (unlikely(old <= 1))
		refcount_warn_saturate(r, REFCOUNT_DEC_LEAK);
पूर्ण

/**
 * refcount_dec - decrement a refcount
 * @r: the refcount
 *
 * Similar to atomic_dec(), it will WARN on underflow and fail to decrement
 * when saturated at REFCOUNT_SATURATED.
 *
 * Provides release memory ordering, such that prior loads and stores are करोne
 * beक्रमe.
 */
अटल अंतरभूत व्योम refcount_dec(refcount_t *r)
अणु
	__refcount_dec(r, शून्य);
पूर्ण

बाह्य __must_check bool refcount_dec_अगर_one(refcount_t *r);
बाह्य __must_check bool refcount_dec_not_one(refcount_t *r);
बाह्य __must_check bool refcount_dec_and_mutex_lock(refcount_t *r, काष्ठा mutex *lock);
बाह्य __must_check bool refcount_dec_and_lock(refcount_t *r, spinlock_t *lock);
बाह्य __must_check bool refcount_dec_and_lock_irqsave(refcount_t *r,
						       spinlock_t *lock,
						       अचिन्हित दीर्घ *flags);
#पूर्ण_अगर /* _LINUX_REFCOUNT_H */
