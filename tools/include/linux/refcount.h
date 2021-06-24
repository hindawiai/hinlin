<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _TOOLS_LINUX_REFCOUNT_H
#घोषणा _TOOLS_LINUX_REFCOUNT_H

/*
 * Variant of atomic_t specialized क्रम reference counts.
 *
 * The पूर्णांकerface matches the atomic_t पूर्णांकerface (to aid in porting) but only
 * provides the few functions one should use क्रम reference counting.
 *
 * It dअगरfers in that the counter saturates at अच_पूर्णांक_उच्च and will not move once
 * there. This aव्योमs wrapping the counter and causing 'spurious'
 * use-after-मुक्त issues.
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
 */

#समावेश <linux/atomic.h>
#समावेश <linux/kernel.h>

#अगर_घोषित न_संशोधन
#घोषणा REFCOUNT_WARN(cond, str) (व्योम)(cond)
#घोषणा __refcount_check
#अन्यथा
#घोषणा REFCOUNT_WARN(cond, str) BUG_ON(cond)
#घोषणा __refcount_check	__must_check
#पूर्ण_अगर

प्रकार काष्ठा refcount_काष्ठा अणु
	atomic_t refs;
पूर्ण refcount_t;

#घोषणा REFCOUNT_INIT(n)	अणु .refs = ATOMIC_INIT(n), पूर्ण

अटल अंतरभूत व्योम refcount_set(refcount_t *r, अचिन्हित पूर्णांक n)
अणु
	atomic_set(&r->refs, n);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक refcount_पढ़ो(स्थिर refcount_t *r)
अणु
	वापस atomic_पढ़ो(&r->refs);
पूर्ण

/*
 * Similar to atomic_inc_not_zero(), will saturate at अच_पूर्णांक_उच्च and WARN.
 *
 * Provides no memory ordering, it is assumed the caller has guaranteed the
 * object memory to be stable (RCU, etc.). It करोes provide a control dependency
 * and thereby orders future stores. See the comment on top.
 */
अटल अंतरभूत __refcount_check
bool refcount_inc_not_zero(refcount_t *r)
अणु
	अचिन्हित पूर्णांक old, new, val = atomic_पढ़ो(&r->refs);

	क्रम (;;) अणु
		new = val + 1;

		अगर (!val)
			वापस false;

		अगर (unlikely(!new))
			वापस true;

		old = atomic_cmpxchg_relaxed(&r->refs, val, new);
		अगर (old == val)
			अवरोध;

		val = old;
	पूर्ण

	REFCOUNT_WARN(new == अच_पूर्णांक_उच्च, "refcount_t: saturated; leaking memory.\n");

	वापस true;
पूर्ण

/*
 * Similar to atomic_inc(), will saturate at अच_पूर्णांक_उच्च and WARN.
 *
 * Provides no memory ordering, it is assumed the caller alपढ़ोy has a
 * reference on the object, will WARN when this is not so.
 */
अटल अंतरभूत व्योम refcount_inc(refcount_t *r)
अणु
	REFCOUNT_WARN(!refcount_inc_not_zero(r), "refcount_t: increment on 0; use-after-free.\n");
पूर्ण

/*
 * Similar to atomic_dec_and_test(), it will WARN on underflow and fail to
 * decrement when saturated at अच_पूर्णांक_उच्च.
 *
 * Provides release memory ordering, such that prior loads and stores are करोne
 * beक्रमe, and provides a control dependency such that मुक्त() must come after.
 * See the comment on top.
 */
अटल अंतरभूत __refcount_check
bool refcount_sub_and_test(अचिन्हित पूर्णांक i, refcount_t *r)
अणु
	अचिन्हित पूर्णांक old, new, val = atomic_पढ़ो(&r->refs);

	क्रम (;;) अणु
		अगर (unlikely(val == अच_पूर्णांक_उच्च))
			वापस false;

		new = val - i;
		अगर (new > val) अणु
			REFCOUNT_WARN(new > val, "refcount_t: underflow; use-after-free.\n");
			वापस false;
		पूर्ण

		old = atomic_cmpxchg_release(&r->refs, val, new);
		अगर (old == val)
			अवरोध;

		val = old;
	पूर्ण

	वापस !new;
पूर्ण

अटल अंतरभूत __refcount_check
bool refcount_dec_and_test(refcount_t *r)
अणु
	वापस refcount_sub_and_test(1, r);
पूर्ण


#पूर्ण_अगर /* _ATOMIC_LINUX_REFCOUNT_H */
