<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Fence mechanism क्रम dma-buf to allow क्रम asynchronous dma access
 *
 * Copyright (C) 2012 Canonical Ltd
 * Copyright (C) 2012 Texas Instruments
 *
 * Authors:
 * Rob Clark <robdclark@gmail.com>
 * Maarten Lankhorst <maarten.lankhorst@canonical.com>
 */

#अगर_अघोषित __LINUX_DMA_FENCE_H
#घोषणा __LINUX_DMA_FENCE_H

#समावेश <linux/err.h>
#समावेश <linux/रुको.h>
#समावेश <linux/list.h>
#समावेश <linux/bitops.h>
#समावेश <linux/kref.h>
#समावेश <linux/sched.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/rcupdate.h>

काष्ठा dma_fence;
काष्ठा dma_fence_ops;
काष्ठा dma_fence_cb;

/**
 * काष्ठा dma_fence - software synchronization primitive
 * @refcount: refcount क्रम this fence
 * @ops: dma_fence_ops associated with this fence
 * @rcu: used क्रम releasing fence with kमुक्त_rcu
 * @cb_list: list of all callbacks to call
 * @lock: spin_lock_irqsave used क्रम locking
 * @context: execution context this fence beदीर्घs to, वापसed by
 *           dma_fence_context_alloc()
 * @seqno: the sequence number of this fence inside the execution context,
 * can be compared to decide which fence would be संकेतed later.
 * @flags: A mask of DMA_FENCE_FLAG_* defined below
 * @बारtamp: Timestamp when the fence was संकेतed.
 * @error: Optional, only valid अगर < 0, must be set beक्रमe calling
 * dma_fence_संकेत, indicates that the fence has completed with an error.
 *
 * the flags member must be manipulated and पढ़ो using the appropriate
 * atomic ops (bit_*), so taking the spinlock will not be needed most
 * of the समय.
 *
 * DMA_FENCE_FLAG_SIGNALED_BIT - fence is alपढ़ोy संकेतed
 * DMA_FENCE_FLAG_TIMESTAMP_BIT - बारtamp recorded क्रम fence संकेतing
 * DMA_FENCE_FLAG_ENABLE_SIGNAL_BIT - enable_संकेतing might have been called
 * DMA_FENCE_FLAG_USER_BITS - start of the unused bits, can be used by the
 * implementer of the fence क्रम its own purposes. Can be used in dअगरferent
 * ways by dअगरferent fence implementers, so करो not rely on this.
 *
 * Since atomic bitops are used, this is not guaranteed to be the हाल.
 * Particularly, अगर the bit was set, but dma_fence_संकेत was called right
 * beक्रमe this bit was set, it would have been able to set the
 * DMA_FENCE_FLAG_SIGNALED_BIT, beक्रमe enable_संकेतing was called.
 * Adding a check क्रम DMA_FENCE_FLAG_SIGNALED_BIT after setting
 * DMA_FENCE_FLAG_ENABLE_SIGNAL_BIT बंदs this race, and makes sure that
 * after dma_fence_संकेत was called, any enable_संकेतing call will have either
 * been completed, or never called at all.
 */
काष्ठा dma_fence अणु
	spinlock_t *lock;
	स्थिर काष्ठा dma_fence_ops *ops;
	/*
	 * We clear the callback list on kref_put so that by the समय we
	 * release the fence it is unused. No one should be adding to the
	 * cb_list that they करोn't themselves hold a reference क्रम.
	 *
	 * The lअगरeसमय of the बारtamp is similarly tied to both the
	 * rcu मुक्तlist and the cb_list. The बारtamp is only set upon
	 * संकेतing जबतक simultaneously notअगरying the cb_list. Ergo, we
	 * only use either the cb_list of बारtamp. Upon deकाष्ठाion,
	 * neither are accessible, and so we can use the rcu. This means
	 * that the cb_list is *only* valid until the संकेत bit is set,
	 * and to पढ़ो either you *must* hold a reference to the fence,
	 * and not just the rcu_पढ़ो_lock.
	 *
	 * Listed in chronological order.
	 */
	जोड़ अणु
		काष्ठा list_head cb_list;
		/* @cb_list replaced by @बारtamp on dma_fence_संकेत() */
		kसमय_प्रकार बारtamp;
		/* @बारtamp replaced by @rcu on dma_fence_release() */
		काष्ठा rcu_head rcu;
	पूर्ण;
	u64 context;
	u64 seqno;
	अचिन्हित दीर्घ flags;
	काष्ठा kref refcount;
	पूर्णांक error;
पूर्ण;

क्रमागत dma_fence_flag_bits अणु
	DMA_FENCE_FLAG_SIGNALED_BIT,
	DMA_FENCE_FLAG_TIMESTAMP_BIT,
	DMA_FENCE_FLAG_ENABLE_SIGNAL_BIT,
	DMA_FENCE_FLAG_USER_BITS, /* must always be last member */
पूर्ण;

प्रकार व्योम (*dma_fence_func_t)(काष्ठा dma_fence *fence,
				 काष्ठा dma_fence_cb *cb);

/**
 * काष्ठा dma_fence_cb - callback क्रम dma_fence_add_callback()
 * @node: used by dma_fence_add_callback() to append this काष्ठा to fence::cb_list
 * @func: dma_fence_func_t to call
 *
 * This काष्ठा will be initialized by dma_fence_add_callback(), additional
 * data can be passed aदीर्घ by embedding dma_fence_cb in another काष्ठा.
 */
काष्ठा dma_fence_cb अणु
	काष्ठा list_head node;
	dma_fence_func_t func;
पूर्ण;

/**
 * काष्ठा dma_fence_ops - operations implemented क्रम fence
 *
 */
काष्ठा dma_fence_ops अणु
	/**
	 * @use_64bit_seqno:
	 *
	 * True अगर this dma_fence implementation uses 64bit seqno, false
	 * otherwise.
	 */
	bool use_64bit_seqno;

	/**
	 * @get_driver_name:
	 *
	 * Returns the driver name. This is a callback to allow drivers to
	 * compute the name at runसमय, without having it to store permanently
	 * क्रम each fence, or build a cache of some sort.
	 *
	 * This callback is mandatory.
	 */
	स्थिर अक्षर * (*get_driver_name)(काष्ठा dma_fence *fence);

	/**
	 * @get_समयline_name:
	 *
	 * Return the name of the context this fence beदीर्घs to. This is a
	 * callback to allow drivers to compute the name at runसमय, without
	 * having it to store permanently क्रम each fence, or build a cache of
	 * some sort.
	 *
	 * This callback is mandatory.
	 */
	स्थिर अक्षर * (*get_समयline_name)(काष्ठा dma_fence *fence);

	/**
	 * @enable_संकेतing:
	 *
	 * Enable software संकेतing of fence.
	 *
	 * For fence implementations that have the capability क्रम hw->hw
	 * संकेतing, they can implement this op to enable the necessary
	 * पूर्णांकerrupts, or insert commands पूर्णांकo cmdstream, etc, to aव्योम these
	 * costly operations क्रम the common हाल where only hw->hw
	 * synchronization is required.  This is called in the first
	 * dma_fence_रुको() or dma_fence_add_callback() path to let the fence
	 * implementation know that there is another driver रुकोing on the
	 * संकेत (ie. hw->sw हाल).
	 *
	 * This function can be called from atomic context, but not
	 * from irq context, so normal spinlocks can be used.
	 *
	 * A वापस value of false indicates the fence alपढ़ोy passed,
	 * or some failure occurred that made it impossible to enable
	 * संकेतing. True indicates successful enabling.
	 *
	 * &dma_fence.error may be set in enable_संकेतing, but only when false
	 * is वापसed.
	 *
	 * Since many implementations can call dma_fence_संकेत() even when beक्रमe
	 * @enable_संकेतing has been called there's a race winकरोw, where the
	 * dma_fence_संकेत() might result in the final fence reference being
	 * released and its memory मुक्तd. To aव्योम this, implementations of this
	 * callback should grab their own reference using dma_fence_get(), to be
	 * released when the fence is संकेतled (through e.g. the पूर्णांकerrupt
	 * handler).
	 *
	 * This callback is optional. If this callback is not present, then the
	 * driver must always have संकेतing enabled.
	 */
	bool (*enable_संकेतing)(काष्ठा dma_fence *fence);

	/**
	 * @संकेतed:
	 *
	 * Peek whether the fence is संकेतed, as a fastpath optimization क्रम
	 * e.g. dma_fence_रुको() or dma_fence_add_callback(). Note that this
	 * callback करोes not need to make any guarantees beyond that a fence
	 * once indicates as संकेतled must always वापस true from this
	 * callback. This callback may वापस false even अगर the fence has
	 * completed alपढ़ोy, in this हाल inक्रमmation hasn't propogated throug
	 * the प्रणाली yet. See also dma_fence_is_संकेतed().
	 *
	 * May set &dma_fence.error अगर वापसing true.
	 *
	 * This callback is optional.
	 */
	bool (*संकेतed)(काष्ठा dma_fence *fence);

	/**
	 * @रुको:
	 *
	 * Custom रुको implementation, शेषs to dma_fence_शेष_रुको() अगर
	 * not set.
	 *
	 * The dma_fence_शेष_रुको implementation should work क्रम any fence, as दीर्घ
	 * as @enable_संकेतing works correctly. This hook allows drivers to
	 * have an optimized version क्रम the हाल where a process context is
	 * alपढ़ोy available, e.g. अगर @enable_संकेतing क्रम the general हाल
	 * needs to set up a worker thपढ़ो.
	 *
	 * Must वापस -ERESTARTSYS अगर the रुको is पूर्णांकr = true and the रुको was
	 * पूर्णांकerrupted, and reमुख्यing jअगरfies अगर fence has संकेतed, or 0 अगर रुको
	 * समयd out. Can also वापस other error values on custom implementations,
	 * which should be treated as अगर the fence is संकेतed. For example a hardware
	 * lockup could be reported like that.
	 *
	 * This callback is optional.
	 */
	चिन्हित दीर्घ (*रुको)(काष्ठा dma_fence *fence,
			    bool पूर्णांकr, चिन्हित दीर्घ समयout);

	/**
	 * @release:
	 *
	 * Called on deकाष्ठाion of fence to release additional resources.
	 * Can be called from irq context.  This callback is optional. If it is
	 * शून्य, then dma_fence_मुक्त() is instead called as the शेष
	 * implementation.
	 */
	व्योम (*release)(काष्ठा dma_fence *fence);

	/**
	 * @fence_value_str:
	 *
	 * Callback to fill in मुक्त-क्रमm debug info specअगरic to this fence, like
	 * the sequence number.
	 *
	 * This callback is optional.
	 */
	व्योम (*fence_value_str)(काष्ठा dma_fence *fence, अक्षर *str, पूर्णांक size);

	/**
	 * @समयline_value_str:
	 *
	 * Fills in the current value of the समयline as a string, like the
	 * sequence number. Note that the specअगरic fence passed to this function
	 * should not matter, drivers should only use it to look up the
	 * corresponding समयline काष्ठाures.
	 */
	व्योम (*समयline_value_str)(काष्ठा dma_fence *fence,
				   अक्षर *str, पूर्णांक size);
पूर्ण;

व्योम dma_fence_init(काष्ठा dma_fence *fence, स्थिर काष्ठा dma_fence_ops *ops,
		    spinlock_t *lock, u64 context, u64 seqno);

व्योम dma_fence_release(काष्ठा kref *kref);
व्योम dma_fence_मुक्त(काष्ठा dma_fence *fence);

/**
 * dma_fence_put - decreases refcount of the fence
 * @fence: fence to reduce refcount of
 */
अटल अंतरभूत व्योम dma_fence_put(काष्ठा dma_fence *fence)
अणु
	अगर (fence)
		kref_put(&fence->refcount, dma_fence_release);
पूर्ण

/**
 * dma_fence_get - increases refcount of the fence
 * @fence: fence to increase refcount of
 *
 * Returns the same fence, with refcount increased by 1.
 */
अटल अंतरभूत काष्ठा dma_fence *dma_fence_get(काष्ठा dma_fence *fence)
अणु
	अगर (fence)
		kref_get(&fence->refcount);
	वापस fence;
पूर्ण

/**
 * dma_fence_get_rcu - get a fence from a dma_resv_list with
 *                     rcu पढ़ो lock
 * @fence: fence to increase refcount of
 *
 * Function वापसs शून्य अगर no refcount could be obtained, or the fence.
 */
अटल अंतरभूत काष्ठा dma_fence *dma_fence_get_rcu(काष्ठा dma_fence *fence)
अणु
	अगर (kref_get_unless_zero(&fence->refcount))
		वापस fence;
	अन्यथा
		वापस शून्य;
पूर्ण

/**
 * dma_fence_get_rcu_safe  - acquire a reference to an RCU tracked fence
 * @fencep: poपूर्णांकer to fence to increase refcount of
 *
 * Function वापसs शून्य अगर no refcount could be obtained, or the fence.
 * This function handles acquiring a reference to a fence that may be
 * पुनः_स्मृतिated within the RCU grace period (such as with SLAB_TYPESAFE_BY_RCU),
 * so दीर्घ as the caller is using RCU on the poपूर्णांकer to the fence.
 *
 * An alternative mechanism is to employ a seqlock to protect a bunch of
 * fences, such as used by काष्ठा dma_resv. When using a seqlock,
 * the seqlock must be taken beक्रमe and checked after a reference to the
 * fence is acquired (as shown here).
 *
 * The caller is required to hold the RCU पढ़ो lock.
 */
अटल अंतरभूत काष्ठा dma_fence *
dma_fence_get_rcu_safe(काष्ठा dma_fence __rcu **fencep)
अणु
	करो अणु
		काष्ठा dma_fence *fence;

		fence = rcu_dereference(*fencep);
		अगर (!fence)
			वापस शून्य;

		अगर (!dma_fence_get_rcu(fence))
			जारी;

		/* The atomic_inc_not_zero() inside dma_fence_get_rcu()
		 * provides a full memory barrier upon success (such as now).
		 * This is paired with the ग_लिखो barrier from assigning
		 * to the __rcu रक्षित fence poपूर्णांकer so that अगर that
		 * poपूर्णांकer still matches the current fence, we know we
		 * have successfully acquire a reference to it. If it no
		 * दीर्घer matches, we are holding a reference to some other
		 * पुनः_स्मृतिated poपूर्णांकer. This is possible अगर the allocator
		 * is using a मुक्तlist like SLAB_TYPESAFE_BY_RCU where the
		 * fence reमुख्यs valid क्रम the RCU grace period, but it
		 * may be पुनः_स्मृतिated. When using such allocators, we are
		 * responsible क्रम ensuring the reference we get is to
		 * the right fence, as below.
		 */
		अगर (fence == rcu_access_poपूर्णांकer(*fencep))
			वापस rcu_poपूर्णांकer_hanकरोff(fence);

		dma_fence_put(fence);
	पूर्ण जबतक (1);
पूर्ण

#अगर_घोषित CONFIG_LOCKDEP
bool dma_fence_begin_संकेतling(व्योम);
व्योम dma_fence_end_संकेतling(bool cookie);
व्योम __dma_fence_might_रुको(व्योम);
#अन्यथा
अटल अंतरभूत bool dma_fence_begin_संकेतling(व्योम)
अणु
	वापस true;
पूर्ण
अटल अंतरभूत व्योम dma_fence_end_संकेतling(bool cookie) अणुपूर्ण
अटल अंतरभूत व्योम __dma_fence_might_रुको(व्योम) अणुपूर्ण
#पूर्ण_अगर

पूर्णांक dma_fence_संकेत(काष्ठा dma_fence *fence);
पूर्णांक dma_fence_संकेत_locked(काष्ठा dma_fence *fence);
पूर्णांक dma_fence_संकेत_बारtamp(काष्ठा dma_fence *fence, kसमय_प्रकार बारtamp);
पूर्णांक dma_fence_संकेत_बारtamp_locked(काष्ठा dma_fence *fence,
				      kसमय_प्रकार बारtamp);
चिन्हित दीर्घ dma_fence_शेष_रुको(काष्ठा dma_fence *fence,
				   bool पूर्णांकr, चिन्हित दीर्घ समयout);
पूर्णांक dma_fence_add_callback(काष्ठा dma_fence *fence,
			   काष्ठा dma_fence_cb *cb,
			   dma_fence_func_t func);
bool dma_fence_हटाओ_callback(काष्ठा dma_fence *fence,
			       काष्ठा dma_fence_cb *cb);
व्योम dma_fence_enable_sw_संकेतing(काष्ठा dma_fence *fence);

/**
 * dma_fence_is_संकेतed_locked - Return an indication अगर the fence
 *                                is संकेतed yet.
 * @fence: the fence to check
 *
 * Returns true अगर the fence was alपढ़ोy संकेतed, false अगर not. Since this
 * function करोesn't enable संकेतing, it is not guaranteed to ever वापस
 * true अगर dma_fence_add_callback(), dma_fence_रुको() or
 * dma_fence_enable_sw_संकेतing() haven't been called beक्रमe.
 *
 * This function requires &dma_fence.lock to be held.
 *
 * See also dma_fence_is_संकेतed().
 */
अटल अंतरभूत bool
dma_fence_is_संकेतed_locked(काष्ठा dma_fence *fence)
अणु
	अगर (test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &fence->flags))
		वापस true;

	अगर (fence->ops->संकेतed && fence->ops->संकेतed(fence)) अणु
		dma_fence_संकेत_locked(fence);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * dma_fence_is_संकेतed - Return an indication अगर the fence is संकेतed yet.
 * @fence: the fence to check
 *
 * Returns true अगर the fence was alपढ़ोy संकेतed, false अगर not. Since this
 * function करोesn't enable संकेतing, it is not guaranteed to ever वापस
 * true अगर dma_fence_add_callback(), dma_fence_रुको() or
 * dma_fence_enable_sw_संकेतing() haven't been called beक्रमe.
 *
 * It's recommended क्रम seqno fences to call dma_fence_संकेत when the
 * operation is complete, it makes it possible to prevent issues from
 * wraparound between समय of issue and समय of use by checking the वापस
 * value of this function beक्रमe calling hardware-specअगरic रुको inकाष्ठाions.
 *
 * See also dma_fence_is_संकेतed_locked().
 */
अटल अंतरभूत bool
dma_fence_is_संकेतed(काष्ठा dma_fence *fence)
अणु
	अगर (test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &fence->flags))
		वापस true;

	अगर (fence->ops->संकेतed && fence->ops->संकेतed(fence)) अणु
		dma_fence_संकेत(fence);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * __dma_fence_is_later - वापस अगर f1 is chronologically later than f2
 * @f1: the first fence's seqno
 * @f2: the second fence's seqno from the same context
 * @ops: dma_fence_ops associated with the seqno
 *
 * Returns true अगर f1 is chronologically later than f2. Both fences must be
 * from the same context, since a seqno is not common across contexts.
 */
अटल अंतरभूत bool __dma_fence_is_later(u64 f1, u64 f2,
					स्थिर काष्ठा dma_fence_ops *ops)
अणु
	/* This is क्रम backward compatibility with drivers which can only handle
	 * 32bit sequence numbers. Use a 64bit compare when the driver says to
	 * करो so.
	 */
	अगर (ops->use_64bit_seqno)
		वापस f1 > f2;

	वापस (पूर्णांक)(lower_32_bits(f1) - lower_32_bits(f2)) > 0;
पूर्ण

/**
 * dma_fence_is_later - वापस अगर f1 is chronologically later than f2
 * @f1: the first fence from the same context
 * @f2: the second fence from the same context
 *
 * Returns true अगर f1 is chronologically later than f2. Both fences must be
 * from the same context, since a seqno is not re-used across contexts.
 */
अटल अंतरभूत bool dma_fence_is_later(काष्ठा dma_fence *f1,
				      काष्ठा dma_fence *f2)
अणु
	अगर (WARN_ON(f1->context != f2->context))
		वापस false;

	वापस __dma_fence_is_later(f1->seqno, f2->seqno, f1->ops);
पूर्ण

/**
 * dma_fence_later - वापस the chronologically later fence
 * @f1:	the first fence from the same context
 * @f2:	the second fence from the same context
 *
 * Returns शून्य अगर both fences are संकेतed, otherwise the fence that would be
 * संकेतed last. Both fences must be from the same context, since a seqno is
 * not re-used across contexts.
 */
अटल अंतरभूत काष्ठा dma_fence *dma_fence_later(काष्ठा dma_fence *f1,
						काष्ठा dma_fence *f2)
अणु
	अगर (WARN_ON(f1->context != f2->context))
		वापस शून्य;

	/*
	 * Can't check just DMA_FENCE_FLAG_SIGNALED_BIT here, it may never
	 * have been set अगर enable_संकेतing wasn't called, and enabling that
	 * here is overसमाप्त.
	 */
	अगर (dma_fence_is_later(f1, f2))
		वापस dma_fence_is_संकेतed(f1) ? शून्य : f1;
	अन्यथा
		वापस dma_fence_is_संकेतed(f2) ? शून्य : f2;
पूर्ण

/**
 * dma_fence_get_status_locked - वापसs the status upon completion
 * @fence: the dma_fence to query
 *
 * Drivers can supply an optional error status condition beक्रमe they संकेत
 * the fence (to indicate whether the fence was completed due to an error
 * rather than success). The value of the status condition is only valid
 * अगर the fence has been संकेतed, dma_fence_get_status_locked() first checks
 * the संकेत state beक्रमe reporting the error status.
 *
 * Returns 0 अगर the fence has not yet been संकेतed, 1 अगर the fence has
 * been संकेतed without an error condition, or a negative error code
 * अगर the fence has been completed in err.
 */
अटल अंतरभूत पूर्णांक dma_fence_get_status_locked(काष्ठा dma_fence *fence)
अणु
	अगर (dma_fence_is_संकेतed_locked(fence))
		वापस fence->error ?: 1;
	अन्यथा
		वापस 0;
पूर्ण

पूर्णांक dma_fence_get_status(काष्ठा dma_fence *fence);

/**
 * dma_fence_set_error - flag an error condition on the fence
 * @fence: the dma_fence
 * @error: the error to store
 *
 * Drivers can supply an optional error status condition beक्रमe they संकेत
 * the fence, to indicate that the fence was completed due to an error
 * rather than success. This must be set beक्रमe संकेतing (so that the value
 * is visible beक्रमe any रुकोers on the संकेत callback are woken). This
 * helper exists to help catching erroneous setting of #dma_fence.error.
 */
अटल अंतरभूत व्योम dma_fence_set_error(काष्ठा dma_fence *fence,
				       पूर्णांक error)
अणु
	WARN_ON(test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &fence->flags));
	WARN_ON(error >= 0 || error < -MAX_ERRNO);

	fence->error = error;
पूर्ण

चिन्हित दीर्घ dma_fence_रुको_समयout(काष्ठा dma_fence *,
				   bool पूर्णांकr, चिन्हित दीर्घ समयout);
चिन्हित दीर्घ dma_fence_रुको_any_समयout(काष्ठा dma_fence **fences,
				       uपूर्णांक32_t count,
				       bool पूर्णांकr, चिन्हित दीर्घ समयout,
				       uपूर्णांक32_t *idx);

/**
 * dma_fence_रुको - sleep until the fence माला_लो संकेतed
 * @fence: the fence to रुको on
 * @पूर्णांकr: अगर true, करो an पूर्णांकerruptible रुको
 *
 * This function will वापस -ERESTARTSYS अगर पूर्णांकerrupted by a संकेत,
 * or 0 अगर the fence was संकेतed. Other error values may be
 * वापसed on custom implementations.
 *
 * Perक्रमms a synchronous रुको on this fence. It is assumed the caller
 * directly or indirectly holds a reference to the fence, otherwise the
 * fence might be मुक्तd beक्रमe वापस, resulting in undefined behavior.
 *
 * See also dma_fence_रुको_समयout() and dma_fence_रुको_any_समयout().
 */
अटल अंतरभूत चिन्हित दीर्घ dma_fence_रुको(काष्ठा dma_fence *fence, bool पूर्णांकr)
अणु
	चिन्हित दीर्घ ret;

	/* Since dma_fence_रुको_समयout cannot समयout with
	 * MAX_SCHEDULE_TIMEOUT, only valid वापस values are
	 * -ERESTARTSYS and MAX_SCHEDULE_TIMEOUT.
	 */
	ret = dma_fence_रुको_समयout(fence, पूर्णांकr, MAX_SCHEDULE_TIMEOUT);

	वापस ret < 0 ? ret : 0;
पूर्ण

काष्ठा dma_fence *dma_fence_get_stub(व्योम);
काष्ठा dma_fence *dma_fence_allocate_निजी_stub(व्योम);
u64 dma_fence_context_alloc(अचिन्हित num);

#घोषणा DMA_FENCE_TRACE(f, fmt, args...) \
	करो अणु								\
		काष्ठा dma_fence *__ff = (f);				\
		अगर (IS_ENABLED(CONFIG_DMA_FENCE_TRACE))			\
			pr_info("f %llu#%llu: " fmt,			\
				__ff->context, __ff->seqno, ##args);	\
	पूर्ण जबतक (0)

#घोषणा DMA_FENCE_WARN(f, fmt, args...) \
	करो अणु								\
		काष्ठा dma_fence *__ff = (f);				\
		pr_warn("f %llu#%llu: " fmt, __ff->context, __ff->seqno,\
			 ##args);					\
	पूर्ण जबतक (0)

#घोषणा DMA_FENCE_ERR(f, fmt, args...) \
	करो अणु								\
		काष्ठा dma_fence *__ff = (f);				\
		pr_err("f %llu#%llu: " fmt, __ff->context, __ff->seqno,	\
			##args);					\
	पूर्ण जबतक (0)

#पूर्ण_अगर /* __LINUX_DMA_FENCE_H */
