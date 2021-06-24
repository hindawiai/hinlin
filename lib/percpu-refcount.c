<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#घोषणा pr_fmt(fmt) "%s: " fmt, __func__

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/percpu-refcount.h>

/*
 * Initially, a percpu refcount is just a set of percpu counters. Initially, we
 * करोn't try to detect the ref hitting 0 - which means that get/put can just
 * increment or decrement the local counter. Note that the counter on a
 * particular cpu can (and will) wrap - this is fine, when we go to shutकरोwn the
 * percpu counters will all sum to the correct value
 *
 * (More precisely: because modular arithmetic is commutative the sum of all the
 * percpu_count vars will be equal to what it would have been अगर all the माला_लो
 * and माला_दो were करोne to a single पूर्णांकeger, even अगर some of the percpu पूर्णांकegers
 * overflow or underflow).
 *
 * The real trick to implementing percpu refcounts is shutकरोwn. We can't detect
 * the ref hitting 0 on every put - this would require global synchronization
 * and defeat the whole purpose of using percpu refs.
 *
 * What we करो is require the user to keep track of the initial refcount; we know
 * the ref can't hit 0 beक्रमe the user drops the initial ref, so as दीर्घ as we
 * convert to non percpu mode beक्रमe the initial ref is dropped everything
 * works.
 *
 * Converting to non percpu mode is करोne with some RCUish stuff in
 * percpu_ref_समाप्त. Additionally, we need a bias value so that the
 * atomic_दीर्घ_t can't hit 0 before we've added up all the percpu refs.
 */

#घोषणा PERCPU_COUNT_BIAS	(1LU << (BITS_PER_LONG - 1))

अटल DEFINE_SPINLOCK(percpu_ref_चयन_lock);
अटल DECLARE_WAIT_QUEUE_HEAD(percpu_ref_चयन_रुकोq);

अटल अचिन्हित दीर्घ __percpu *percpu_count_ptr(काष्ठा percpu_ref *ref)
अणु
	वापस (अचिन्हित दीर्घ __percpu *)
		(ref->percpu_count_ptr & ~__PERCPU_REF_ATOMIC_DEAD);
पूर्ण

/**
 * percpu_ref_init - initialize a percpu refcount
 * @ref: percpu_ref to initialize
 * @release: function which will be called when refcount hits 0
 * @flags: PERCPU_REF_INIT_* flags
 * @gfp: allocation mask to use
 *
 * Initializes @ref.  @ref starts out in percpu mode with a refcount of 1 unless
 * @flags contains PERCPU_REF_INIT_ATOMIC or PERCPU_REF_INIT_DEAD.  These flags
 * change the start state to atomic with the latter setting the initial refcount
 * to 0.  See the definitions of PERCPU_REF_INIT_* flags क्रम flag behaviors.
 *
 * Note that @release must not sleep - it may potentially be called from RCU
 * callback context by percpu_ref_समाप्त().
 */
पूर्णांक percpu_ref_init(काष्ठा percpu_ref *ref, percpu_ref_func_t *release,
		    अचिन्हित पूर्णांक flags, gfp_t gfp)
अणु
	माप_प्रकार align = max_t(माप_प्रकार, 1 << __PERCPU_REF_FLAG_BITS,
			     __alignof__(अचिन्हित दीर्घ));
	अचिन्हित दीर्घ start_count = 0;
	काष्ठा percpu_ref_data *data;

	ref->percpu_count_ptr = (अचिन्हित दीर्घ)
		__alloc_percpu_gfp(माप(अचिन्हित दीर्घ), align, gfp);
	अगर (!ref->percpu_count_ptr)
		वापस -ENOMEM;

	data = kzalloc(माप(*ref->data), gfp);
	अगर (!data) अणु
		मुक्त_percpu((व्योम __percpu *)ref->percpu_count_ptr);
		वापस -ENOMEM;
	पूर्ण

	data->क्रमce_atomic = flags & PERCPU_REF_INIT_ATOMIC;
	data->allow_reinit = flags & PERCPU_REF_ALLOW_REINIT;

	अगर (flags & (PERCPU_REF_INIT_ATOMIC | PERCPU_REF_INIT_DEAD)) अणु
		ref->percpu_count_ptr |= __PERCPU_REF_ATOMIC;
		data->allow_reinit = true;
	पूर्ण अन्यथा अणु
		start_count += PERCPU_COUNT_BIAS;
	पूर्ण

	अगर (flags & PERCPU_REF_INIT_DEAD)
		ref->percpu_count_ptr |= __PERCPU_REF_DEAD;
	अन्यथा
		start_count++;

	atomic_दीर्घ_set(&data->count, start_count);

	data->release = release;
	data->confirm_चयन = शून्य;
	data->ref = ref;
	ref->data = data;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(percpu_ref_init);

अटल व्योम __percpu_ref_निकास(काष्ठा percpu_ref *ref)
अणु
	अचिन्हित दीर्घ __percpu *percpu_count = percpu_count_ptr(ref);

	अगर (percpu_count) अणु
		/* non-शून्य confirm_चयन indicates चयनing in progress */
		WARN_ON_ONCE(ref->data && ref->data->confirm_चयन);
		मुक्त_percpu(percpu_count);
		ref->percpu_count_ptr = __PERCPU_REF_ATOMIC_DEAD;
	पूर्ण
पूर्ण

/**
 * percpu_ref_निकास - unकरो percpu_ref_init()
 * @ref: percpu_ref to निकास
 *
 * This function निकासs @ref.  The caller is responsible क्रम ensuring that
 * @ref is no दीर्घer in active use.  The usual places to invoke this
 * function from are the @ref->release() callback or in init failure path
 * where percpu_ref_init() succeeded but other parts of the initialization
 * of the embedding object failed.
 */
व्योम percpu_ref_निकास(काष्ठा percpu_ref *ref)
अणु
	काष्ठा percpu_ref_data *data = ref->data;
	अचिन्हित दीर्घ flags;

	__percpu_ref_निकास(ref);

	अगर (!data)
		वापस;

	spin_lock_irqsave(&percpu_ref_चयन_lock, flags);
	ref->percpu_count_ptr |= atomic_दीर्घ_पढ़ो(&ref->data->count) <<
		__PERCPU_REF_FLAG_BITS;
	ref->data = शून्य;
	spin_unlock_irqrestore(&percpu_ref_चयन_lock, flags);

	kमुक्त(data);
पूर्ण
EXPORT_SYMBOL_GPL(percpu_ref_निकास);

अटल व्योम percpu_ref_call_confirm_rcu(काष्ठा rcu_head *rcu)
अणु
	काष्ठा percpu_ref_data *data = container_of(rcu,
			काष्ठा percpu_ref_data, rcu);
	काष्ठा percpu_ref *ref = data->ref;

	data->confirm_चयन(ref);
	data->confirm_चयन = शून्य;
	wake_up_all(&percpu_ref_चयन_रुकोq);

	अगर (!data->allow_reinit)
		__percpu_ref_निकास(ref);

	/* drop ref from percpu_ref_चयन_to_atomic() */
	percpu_ref_put(ref);
पूर्ण

अटल व्योम percpu_ref_चयन_to_atomic_rcu(काष्ठा rcu_head *rcu)
अणु
	काष्ठा percpu_ref_data *data = container_of(rcu,
			काष्ठा percpu_ref_data, rcu);
	काष्ठा percpu_ref *ref = data->ref;
	अचिन्हित दीर्घ __percpu *percpu_count = percpu_count_ptr(ref);
	अटल atomic_t underflows;
	अचिन्हित दीर्घ count = 0;
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu)
		count += *per_cpu_ptr(percpu_count, cpu);

	pr_debug("global %lu percpu %lu\n",
		 atomic_दीर्घ_पढ़ो(&data->count), count);

	/*
	 * It's crucial that we sum the percpu counters _beक्रमe_ adding the sum
	 * to &ref->count; since माला_लो could be happening on one cpu जबतक माला_दो
	 * happen on another, adding a single cpu's count could cause
	 * @ref->count to hit 0 beक्रमe we've got a consistent value - but the
	 * sum of all the counts will be consistent and correct.
	 *
	 * Subtracting the bias value then has to happen _after_ adding count to
	 * &ref->count; we need the bias value to prevent &ref->count from
	 * reaching 0 beक्रमe we add the percpu counts. But करोing it at the same
	 * समय is equivalent and saves us atomic operations:
	 */
	atomic_दीर्घ_add((दीर्घ)count - PERCPU_COUNT_BIAS, &data->count);

	अगर (WARN_ONCE(atomic_दीर्घ_पढ़ो(&data->count) <= 0,
		      "percpu ref (%ps) <= 0 (%ld) after switching to atomic",
		      data->release, atomic_दीर्घ_पढ़ो(&data->count)) &&
	    atomic_inc_वापस(&underflows) < 4) अणु
		pr_err("%s(): percpu_ref underflow", __func__);
		mem_dump_obj(data);
	पूर्ण

	/* @ref is viewed as dead on all CPUs, send out चयन confirmation */
	percpu_ref_call_confirm_rcu(rcu);
पूर्ण

अटल व्योम percpu_ref_noop_confirm_चयन(काष्ठा percpu_ref *ref)
अणु
पूर्ण

अटल व्योम __percpu_ref_चयन_to_atomic(काष्ठा percpu_ref *ref,
					  percpu_ref_func_t *confirm_चयन)
अणु
	अगर (ref->percpu_count_ptr & __PERCPU_REF_ATOMIC) अणु
		अगर (confirm_चयन)
			confirm_चयन(ref);
		वापस;
	पूर्ण

	/* चयनing from percpu to atomic */
	ref->percpu_count_ptr |= __PERCPU_REF_ATOMIC;

	/*
	 * Non-शून्य ->confirm_चयन is used to indicate that चयनing is
	 * in progress.  Use noop one अगर unspecअगरied.
	 */
	ref->data->confirm_चयन = confirm_चयन ?:
		percpu_ref_noop_confirm_चयन;

	percpu_ref_get(ref);	/* put after confirmation */
	call_rcu(&ref->data->rcu, percpu_ref_चयन_to_atomic_rcu);
पूर्ण

अटल व्योम __percpu_ref_चयन_to_percpu(काष्ठा percpu_ref *ref)
अणु
	अचिन्हित दीर्घ __percpu *percpu_count = percpu_count_ptr(ref);
	पूर्णांक cpu;

	BUG_ON(!percpu_count);

	अगर (!(ref->percpu_count_ptr & __PERCPU_REF_ATOMIC))
		वापस;

	अगर (WARN_ON_ONCE(!ref->data->allow_reinit))
		वापस;

	atomic_दीर्घ_add(PERCPU_COUNT_BIAS, &ref->data->count);

	/*
	 * Restore per-cpu operation.  smp_store_release() is paired
	 * with READ_ONCE() in __ref_is_percpu() and guarantees that the
	 * zeroing is visible to all percpu accesses which can see the
	 * following __PERCPU_REF_ATOMIC clearing.
	 */
	क्रम_each_possible_cpu(cpu)
		*per_cpu_ptr(percpu_count, cpu) = 0;

	smp_store_release(&ref->percpu_count_ptr,
			  ref->percpu_count_ptr & ~__PERCPU_REF_ATOMIC);
पूर्ण

अटल व्योम __percpu_ref_चयन_mode(काष्ठा percpu_ref *ref,
				     percpu_ref_func_t *confirm_चयन)
अणु
	काष्ठा percpu_ref_data *data = ref->data;

	lockdep_निश्चित_held(&percpu_ref_चयन_lock);

	/*
	 * If the previous ATOMIC चयनing hasn't finished yet, रुको क्रम
	 * its completion.  If the caller ensures that ATOMIC चयनing
	 * isn't in progress, this function can be called from any context.
	 */
	रुको_event_lock_irq(percpu_ref_चयन_रुकोq, !data->confirm_चयन,
			    percpu_ref_चयन_lock);

	अगर (data->क्रमce_atomic || percpu_ref_is_dying(ref))
		__percpu_ref_चयन_to_atomic(ref, confirm_चयन);
	अन्यथा
		__percpu_ref_चयन_to_percpu(ref);
पूर्ण

/**
 * percpu_ref_चयन_to_atomic - चयन a percpu_ref to atomic mode
 * @ref: percpu_ref to चयन to atomic mode
 * @confirm_चयन: optional confirmation callback
 *
 * There's no reason to use this function क्रम the usual reference counting.
 * Use percpu_ref_समाप्त[_and_confirm]().
 *
 * Schedule चयनing of @ref to atomic mode.  All its percpu counts will
 * be collected to the मुख्य atomic counter.  On completion, when all CPUs
 * are guaraneed to be in atomic mode, @confirm_चयन, which may not
 * block, is invoked.  This function may be invoked concurrently with all
 * the get/put operations and can safely be mixed with समाप्त and reinit
 * operations.  Note that @ref will stay in atomic mode across समाप्त/reinit
 * cycles until percpu_ref_चयन_to_percpu() is called.
 *
 * This function may block अगर @ref is in the process of चयनing to atomic
 * mode.  If the caller ensures that @ref is not in the process of
 * चयनing to atomic mode, this function can be called from any context.
 */
व्योम percpu_ref_चयन_to_atomic(काष्ठा percpu_ref *ref,
				 percpu_ref_func_t *confirm_चयन)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&percpu_ref_चयन_lock, flags);

	ref->data->क्रमce_atomic = true;
	__percpu_ref_चयन_mode(ref, confirm_चयन);

	spin_unlock_irqrestore(&percpu_ref_चयन_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(percpu_ref_चयन_to_atomic);

/**
 * percpu_ref_चयन_to_atomic_sync - चयन a percpu_ref to atomic mode
 * @ref: percpu_ref to चयन to atomic mode
 *
 * Schedule चयनing the ref to atomic mode, and रुको क्रम the
 * चयन to complete.  Caller must ensure that no other thपढ़ो
 * will चयन back to percpu mode.
 */
व्योम percpu_ref_चयन_to_atomic_sync(काष्ठा percpu_ref *ref)
अणु
	percpu_ref_चयन_to_atomic(ref, शून्य);
	रुको_event(percpu_ref_चयन_रुकोq, !ref->data->confirm_चयन);
पूर्ण
EXPORT_SYMBOL_GPL(percpu_ref_चयन_to_atomic_sync);

/**
 * percpu_ref_चयन_to_percpu - चयन a percpu_ref to percpu mode
 * @ref: percpu_ref to चयन to percpu mode
 *
 * There's no reason to use this function क्रम the usual reference counting.
 * To re-use an expired ref, use percpu_ref_reinit().
 *
 * Switch @ref to percpu mode.  This function may be invoked concurrently
 * with all the get/put operations and can safely be mixed with समाप्त and
 * reinit operations.  This function reverses the sticky atomic state set
 * by PERCPU_REF_INIT_ATOMIC or percpu_ref_चयन_to_atomic().  If @ref is
 * dying or dead, the actual चयनing takes place on the following
 * percpu_ref_reinit().
 *
 * This function may block अगर @ref is in the process of चयनing to atomic
 * mode.  If the caller ensures that @ref is not in the process of
 * चयनing to atomic mode, this function can be called from any context.
 */
व्योम percpu_ref_चयन_to_percpu(काष्ठा percpu_ref *ref)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&percpu_ref_चयन_lock, flags);

	ref->data->क्रमce_atomic = false;
	__percpu_ref_चयन_mode(ref, शून्य);

	spin_unlock_irqrestore(&percpu_ref_चयन_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(percpu_ref_चयन_to_percpu);

/**
 * percpu_ref_समाप्त_and_confirm - drop the initial ref and schedule confirmation
 * @ref: percpu_ref to समाप्त
 * @confirm_समाप्त: optional confirmation callback
 *
 * Equivalent to percpu_ref_समाप्त() but also schedules समाप्त confirmation अगर
 * @confirm_समाप्त is not शून्य.  @confirm_समाप्त, which may not block, will be
 * called after @ref is seen as dead from all CPUs at which poपूर्णांक all
 * further invocations of percpu_ref_tryget_live() will fail.  See
 * percpu_ref_tryget_live() क्रम details.
 *
 * This function normally करोesn't block and can be called from any context
 * but it may block अगर @confirm_समाप्त is specअगरied and @ref is in the
 * process of चयनing to atomic mode by percpu_ref_चयन_to_atomic().
 *
 * There are no implied RCU grace periods between समाप्त and release.
 */
व्योम percpu_ref_समाप्त_and_confirm(काष्ठा percpu_ref *ref,
				 percpu_ref_func_t *confirm_समाप्त)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&percpu_ref_चयन_lock, flags);

	WARN_ONCE(percpu_ref_is_dying(ref),
		  "%s called more than once on %ps!", __func__,
		  ref->data->release);

	ref->percpu_count_ptr |= __PERCPU_REF_DEAD;
	__percpu_ref_चयन_mode(ref, confirm_समाप्त);
	percpu_ref_put(ref);

	spin_unlock_irqrestore(&percpu_ref_चयन_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(percpu_ref_समाप्त_and_confirm);

/**
 * percpu_ref_is_zero - test whether a percpu refcount reached zero
 * @ref: percpu_ref to test
 *
 * Returns %true अगर @ref reached zero.
 *
 * This function is safe to call as दीर्घ as @ref is between init and निकास.
 */
bool percpu_ref_is_zero(काष्ठा percpu_ref *ref)
अणु
	अचिन्हित दीर्घ __percpu *percpu_count;
	अचिन्हित दीर्घ count, flags;

	अगर (__ref_is_percpu(ref, &percpu_count))
		वापस false;

	/* protect us from being destroyed */
	spin_lock_irqsave(&percpu_ref_चयन_lock, flags);
	अगर (ref->data)
		count = atomic_दीर्घ_पढ़ो(&ref->data->count);
	अन्यथा
		count = ref->percpu_count_ptr >> __PERCPU_REF_FLAG_BITS;
	spin_unlock_irqrestore(&percpu_ref_चयन_lock, flags);

	वापस count == 0;
पूर्ण
EXPORT_SYMBOL_GPL(percpu_ref_is_zero);

/**
 * percpu_ref_reinit - re-initialize a percpu refcount
 * @ref: perpcu_ref to re-initialize
 *
 * Re-initialize @ref so that it's in the same state as when it finished
 * percpu_ref_init() ignoring %PERCPU_REF_INIT_DEAD.  @ref must have been
 * initialized successfully and reached 0 but not निकासed.
 *
 * Note that percpu_ref_tryget[_live]() are safe to perक्रमm on @ref जबतक
 * this function is in progress.
 */
व्योम percpu_ref_reinit(काष्ठा percpu_ref *ref)
अणु
	WARN_ON_ONCE(!percpu_ref_is_zero(ref));

	percpu_ref_resurrect(ref);
पूर्ण
EXPORT_SYMBOL_GPL(percpu_ref_reinit);

/**
 * percpu_ref_resurrect - modअगरy a percpu refcount from dead to live
 * @ref: perpcu_ref to resurrect
 *
 * Modअगरy @ref so that it's in the same state as beक्रमe percpu_ref_समाप्त() was
 * called. @ref must be dead but must not yet have निकासed.
 *
 * If @ref->release() मुक्तs @ref then the caller is responsible क्रम
 * guaranteeing that @ref->release() करोes not get called जबतक this
 * function is in progress.
 *
 * Note that percpu_ref_tryget[_live]() are safe to perक्रमm on @ref जबतक
 * this function is in progress.
 */
व्योम percpu_ref_resurrect(काष्ठा percpu_ref *ref)
अणु
	अचिन्हित दीर्घ __percpu *percpu_count;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&percpu_ref_चयन_lock, flags);

	WARN_ON_ONCE(!percpu_ref_is_dying(ref));
	WARN_ON_ONCE(__ref_is_percpu(ref, &percpu_count));

	ref->percpu_count_ptr &= ~__PERCPU_REF_DEAD;
	percpu_ref_get(ref);
	__percpu_ref_चयन_mode(ref, शून्य);

	spin_unlock_irqrestore(&percpu_ref_चयन_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(percpu_ref_resurrect);
