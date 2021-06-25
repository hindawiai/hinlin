<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Percpu refcounts:
 * (C) 2012 Google, Inc.
 * Author: Kent Overstreet <koverstreet@google.com>
 *
 * This implements a refcount with similar semantics to atomic_t - atomic_inc(),
 * atomic_dec_and_test() - but percpu.
 *
 * There's one important dअगरference between percpu refs and normal atomic_t
 * refcounts; you have to keep track of your initial refcount, and then when you
 * start shutting करोwn you call percpu_ref_समाप्त() _beक्रमe_ dropping the initial
 * refcount.
 *
 * The refcount will have a range of 0 to ((1U << 31) - 1), i.e. one bit less
 * than an atomic_t - this is because of the way shutकरोwn works, see
 * percpu_ref_समाप्त()/PERCPU_COUNT_BIAS.
 *
 * Beक्रमe you call percpu_ref_समाप्त(), percpu_ref_put() करोes not check क्रम the
 * refcount hitting 0 - it can't, अगर it was in percpu mode. percpu_ref_समाप्त()
 * माला_दो the ref back in single atomic_t mode, collecting the per cpu refs and
 * issuing the appropriate barriers, and then marks the ref as shutting करोwn so
 * that percpu_ref_put() will check क्रम the ref hitting 0.  After it वापसs,
 * it's safe to drop the initial ref.
 *
 * USAGE:
 *
 * See fs/aio.c क्रम some example usage; it's used there क्रम काष्ठा kioctx, which
 * is created when userspaces calls io_setup(), and destroyed when userspace
 * calls io_destroy() or the process निकासs.
 *
 * In the aio code, समाप्त_ioctx() is called when we wish to destroy a kioctx; it
 * हटाओs the kioctx from the proccess's table of kioctxs and समाप्तs percpu_ref.
 * After that, there can't be any new users of the kioctx (from lookup_ioctx())
 * and it's then safe to drop the initial ref with percpu_ref_put().
 *
 * Note that the मुक्त path, मुक्त_ioctx(), needs to go through explicit call_rcu()
 * to synchronize with RCU रक्षित lookup_ioctx().  percpu_ref operations करोn't
 * imply RCU grace periods of any kind and अगर a user wants to combine percpu_ref
 * with RCU protection, it must be करोne explicitly.
 *
 * Code that करोes a two stage shutकरोwn like this often needs some kind of
 * explicit synchronization to ensure the initial refcount can only be dropped
 * once - percpu_ref_समाप्त() करोes this क्रम you, it वापसs true once and false अगर
 * someone अन्यथा alपढ़ोy called it. The aio code uses it this way, but it's not
 * necessary अगर the code has some other mechanism to synchronize tearकरोwn.
 * around.
 */

#अगर_अघोषित _LINUX_PERCPU_REFCOUNT_H
#घोषणा _LINUX_PERCPU_REFCOUNT_H

#समावेश <linux/atomic.h>
#समावेश <linux/kernel.h>
#समावेश <linux/percpu.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/gfp.h>

काष्ठा percpu_ref;
प्रकार व्योम (percpu_ref_func_t)(काष्ठा percpu_ref *);

/* flags set in the lower bits of percpu_ref->percpu_count_ptr */
क्रमागत अणु
	__PERCPU_REF_ATOMIC	= 1LU << 0,	/* operating in atomic mode */
	__PERCPU_REF_DEAD	= 1LU << 1,	/* (being) समाप्तed */
	__PERCPU_REF_ATOMIC_DEAD = __PERCPU_REF_ATOMIC | __PERCPU_REF_DEAD,

	__PERCPU_REF_FLAG_BITS	= 2,
पूर्ण;

/* @flags क्रम percpu_ref_init() */
क्रमागत अणु
	/*
	 * Start w/ ref == 1 in atomic mode.  Can be चयनed to percpu
	 * operation using percpu_ref_चयन_to_percpu().  If initialized
	 * with this flag, the ref will stay in atomic mode until
	 * percpu_ref_चयन_to_percpu() is invoked on it.
	 * Implies ALLOW_REINIT.
	 */
	PERCPU_REF_INIT_ATOMIC	= 1 << 0,

	/*
	 * Start dead w/ ref == 0 in atomic mode.  Must be revived with
	 * percpu_ref_reinit() beक्रमe used.  Implies INIT_ATOMIC and
	 * ALLOW_REINIT.
	 */
	PERCPU_REF_INIT_DEAD	= 1 << 1,

	/*
	 * Allow चयनing from atomic mode to percpu mode.
	 */
	PERCPU_REF_ALLOW_REINIT	= 1 << 2,
पूर्ण;

काष्ठा percpu_ref_data अणु
	atomic_दीर्घ_t		count;
	percpu_ref_func_t	*release;
	percpu_ref_func_t	*confirm_चयन;
	bool			क्रमce_atomic:1;
	bool			allow_reinit:1;
	काष्ठा rcu_head		rcu;
	काष्ठा percpu_ref	*ref;
पूर्ण;

काष्ठा percpu_ref अणु
	/*
	 * The low bit of the poपूर्णांकer indicates whether the ref is in percpu
	 * mode; अगर set, then get/put will manipulate the atomic_t.
	 */
	अचिन्हित दीर्घ		percpu_count_ptr;

	/*
	 * 'percpu_ref' is often embedded पूर्णांकo user काष्ठाure, and only
	 * 'percpu_count_ptr' is required in fast path, move other fields
	 * पूर्णांकo 'percpu_ref_data', so we can reduce memory footprपूर्णांक in
	 * fast path.
	 */
	काष्ठा percpu_ref_data  *data;
पूर्ण;

पूर्णांक __must_check percpu_ref_init(काष्ठा percpu_ref *ref,
				 percpu_ref_func_t *release, अचिन्हित पूर्णांक flags,
				 gfp_t gfp);
व्योम percpu_ref_निकास(काष्ठा percpu_ref *ref);
व्योम percpu_ref_चयन_to_atomic(काष्ठा percpu_ref *ref,
				 percpu_ref_func_t *confirm_चयन);
व्योम percpu_ref_चयन_to_atomic_sync(काष्ठा percpu_ref *ref);
व्योम percpu_ref_चयन_to_percpu(काष्ठा percpu_ref *ref);
व्योम percpu_ref_समाप्त_and_confirm(काष्ठा percpu_ref *ref,
				 percpu_ref_func_t *confirm_समाप्त);
व्योम percpu_ref_resurrect(काष्ठा percpu_ref *ref);
व्योम percpu_ref_reinit(काष्ठा percpu_ref *ref);
bool percpu_ref_is_zero(काष्ठा percpu_ref *ref);

/**
 * percpu_ref_समाप्त - drop the initial ref
 * @ref: percpu_ref to समाप्त
 *
 * Must be used to drop the initial ref on a percpu refcount; must be called
 * precisely once beक्रमe shutकरोwn.
 *
 * Switches @ref पूर्णांकo atomic mode beक्रमe gathering up the percpu counters
 * and dropping the initial ref.
 *
 * There are no implied RCU grace periods between समाप्त and release.
 */
अटल अंतरभूत व्योम percpu_ref_समाप्त(काष्ठा percpu_ref *ref)
अणु
	percpu_ref_समाप्त_and_confirm(ref, शून्य);
पूर्ण

/*
 * Internal helper.  Don't use outside percpu-refcount proper.  The
 * function करोesn't वापस the poपूर्णांकer and let the caller test it क्रम शून्य
 * because करोing so क्रमces the compiler to generate two conditional
 * branches as it can't assume that @ref->percpu_count is not शून्य.
 */
अटल अंतरभूत bool __ref_is_percpu(काष्ठा percpu_ref *ref,
					  अचिन्हित दीर्घ __percpu **percpu_countp)
अणु
	अचिन्हित दीर्घ percpu_ptr;

	/*
	 * The value of @ref->percpu_count_ptr is tested क्रम
	 * !__PERCPU_REF_ATOMIC, which may be set asynchronously, and then
	 * used as a poपूर्णांकer.  If the compiler generates a separate fetch
	 * when using it as a poपूर्णांकer, __PERCPU_REF_ATOMIC may be set in
	 * between contaminating the poपूर्णांकer value, meaning that
	 * READ_ONCE() is required when fetching it.
	 *
	 * The dependency ordering from the READ_ONCE() pairs
	 * with smp_store_release() in __percpu_ref_चयन_to_percpu().
	 */
	percpu_ptr = READ_ONCE(ref->percpu_count_ptr);

	/*
	 * Theoretically, the following could test just ATOMIC; however,
	 * then we'd have to mask off DEAD separately as DEAD may be
	 * visible without ATOMIC अगर we race with percpu_ref_समाप्त().  DEAD
	 * implies ATOMIC anyway.  Test them together.
	 */
	अगर (unlikely(percpu_ptr & __PERCPU_REF_ATOMIC_DEAD))
		वापस false;

	*percpu_countp = (अचिन्हित दीर्घ __percpu *)percpu_ptr;
	वापस true;
पूर्ण

/**
 * percpu_ref_get_many - increment a percpu refcount
 * @ref: percpu_ref to get
 * @nr: number of references to get
 *
 * Analogous to atomic_दीर्घ_add().
 *
 * This function is safe to call as दीर्घ as @ref is between init and निकास.
 */
अटल अंतरभूत व्योम percpu_ref_get_many(काष्ठा percpu_ref *ref, अचिन्हित दीर्घ nr)
अणु
	अचिन्हित दीर्घ __percpu *percpu_count;

	rcu_पढ़ो_lock();

	अगर (__ref_is_percpu(ref, &percpu_count))
		this_cpu_add(*percpu_count, nr);
	अन्यथा
		atomic_दीर्घ_add(nr, &ref->data->count);

	rcu_पढ़ो_unlock();
पूर्ण

/**
 * percpu_ref_get - increment a percpu refcount
 * @ref: percpu_ref to get
 *
 * Analagous to atomic_दीर्घ_inc().
 *
 * This function is safe to call as दीर्घ as @ref is between init and निकास.
 */
अटल अंतरभूत व्योम percpu_ref_get(काष्ठा percpu_ref *ref)
अणु
	percpu_ref_get_many(ref, 1);
पूर्ण

/**
 * percpu_ref_tryget_many - try to increment a percpu refcount
 * @ref: percpu_ref to try-get
 * @nr: number of references to get
 *
 * Increment a percpu refcount  by @nr unless its count alपढ़ोy reached zero.
 * Returns %true on success; %false on failure.
 *
 * This function is safe to call as दीर्घ as @ref is between init and निकास.
 */
अटल अंतरभूत bool percpu_ref_tryget_many(काष्ठा percpu_ref *ref,
					  अचिन्हित दीर्घ nr)
अणु
	अचिन्हित दीर्घ __percpu *percpu_count;
	bool ret;

	rcu_पढ़ो_lock();

	अगर (__ref_is_percpu(ref, &percpu_count)) अणु
		this_cpu_add(*percpu_count, nr);
		ret = true;
	पूर्ण अन्यथा अणु
		ret = atomic_दीर्घ_add_unless(&ref->data->count, nr, 0);
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

/**
 * percpu_ref_tryget - try to increment a percpu refcount
 * @ref: percpu_ref to try-get
 *
 * Increment a percpu refcount unless its count alपढ़ोy reached zero.
 * Returns %true on success; %false on failure.
 *
 * This function is safe to call as दीर्घ as @ref is between init and निकास.
 */
अटल अंतरभूत bool percpu_ref_tryget(काष्ठा percpu_ref *ref)
अणु
	वापस percpu_ref_tryget_many(ref, 1);
पूर्ण

/**
 * percpu_ref_tryget_live - try to increment a live percpu refcount
 * @ref: percpu_ref to try-get
 *
 * Increment a percpu refcount unless it has alपढ़ोy been समाप्तed.  Returns
 * %true on success; %false on failure.
 *
 * Completion of percpu_ref_समाप्त() in itself करोesn't guarantee that this
 * function will fail.  For such guarantee, percpu_ref_समाप्त_and_confirm()
 * should be used.  After the confirm_समाप्त callback is invoked, it's
 * guaranteed that no new reference will be given out by
 * percpu_ref_tryget_live().
 *
 * This function is safe to call as दीर्घ as @ref is between init and निकास.
 */
अटल अंतरभूत bool percpu_ref_tryget_live(काष्ठा percpu_ref *ref)
अणु
	अचिन्हित दीर्घ __percpu *percpu_count;
	bool ret = false;

	rcu_पढ़ो_lock();

	अगर (__ref_is_percpu(ref, &percpu_count)) अणु
		this_cpu_inc(*percpu_count);
		ret = true;
	पूर्ण अन्यथा अगर (!(ref->percpu_count_ptr & __PERCPU_REF_DEAD)) अणु
		ret = atomic_दीर्घ_inc_not_zero(&ref->data->count);
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

/**
 * percpu_ref_put_many - decrement a percpu refcount
 * @ref: percpu_ref to put
 * @nr: number of references to put
 *
 * Decrement the refcount, and अगर 0, call the release function (which was passed
 * to percpu_ref_init())
 *
 * This function is safe to call as दीर्घ as @ref is between init and निकास.
 */
अटल अंतरभूत व्योम percpu_ref_put_many(काष्ठा percpu_ref *ref, अचिन्हित दीर्घ nr)
अणु
	अचिन्हित दीर्घ __percpu *percpu_count;

	rcu_पढ़ो_lock();

	अगर (__ref_is_percpu(ref, &percpu_count))
		this_cpu_sub(*percpu_count, nr);
	अन्यथा अगर (unlikely(atomic_दीर्घ_sub_and_test(nr, &ref->data->count)))
		ref->data->release(ref);

	rcu_पढ़ो_unlock();
पूर्ण

/**
 * percpu_ref_put - decrement a percpu refcount
 * @ref: percpu_ref to put
 *
 * Decrement the refcount, and अगर 0, call the release function (which was passed
 * to percpu_ref_init())
 *
 * This function is safe to call as दीर्घ as @ref is between init and निकास.
 */
अटल अंतरभूत व्योम percpu_ref_put(काष्ठा percpu_ref *ref)
अणु
	percpu_ref_put_many(ref, 1);
पूर्ण

/**
 * percpu_ref_is_dying - test whether a percpu refcount is dying or dead
 * @ref: percpu_ref to test
 *
 * Returns %true अगर @ref is dying or dead.
 *
 * This function is safe to call as दीर्घ as @ref is between init and निकास
 * and the caller is responsible क्रम synchronizing against state changes.
 */
अटल अंतरभूत bool percpu_ref_is_dying(काष्ठा percpu_ref *ref)
अणु
	वापस ref->percpu_count_ptr & __PERCPU_REF_DEAD;
पूर्ण

#पूर्ण_अगर
