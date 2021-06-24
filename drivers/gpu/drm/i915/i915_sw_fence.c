<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * (C) Copyright 2016 Intel Corporation
 */

#समावेश <linux/slab.h>
#समावेश <linux/dma-fence.h>
#समावेश <linux/irq_work.h>
#समावेश <linux/dma-resv.h>

#समावेश "i915_sw_fence.h"
#समावेश "i915_selftest.h"

#अगर IS_ENABLED(CONFIG_DRM_I915_DEBUG)
#घोषणा I915_SW_FENCE_BUG_ON(expr) BUG_ON(expr)
#अन्यथा
#घोषणा I915_SW_FENCE_BUG_ON(expr) BUILD_BUG_ON_INVALID(expr)
#पूर्ण_अगर

अटल DEFINE_SPINLOCK(i915_sw_fence_lock);

#घोषणा WQ_FLAG_BITS \
	BITS_PER_TYPE(typeof_member(काष्ठा रुको_queue_entry, flags))

/* after WQ_FLAG_* क्रम safety */
#घोषणा I915_SW_FENCE_FLAG_FENCE BIT(WQ_FLAG_BITS - 1)
#घोषणा I915_SW_FENCE_FLAG_ALLOC BIT(WQ_FLAG_BITS - 2)

क्रमागत अणु
	DEBUG_FENCE_IDLE = 0,
	DEBUG_FENCE_NOTIFY,
पूर्ण;

अटल व्योम *i915_sw_fence_debug_hपूर्णांक(व्योम *addr)
अणु
	वापस (व्योम *)(((काष्ठा i915_sw_fence *)addr)->flags & I915_SW_FENCE_MASK);
पूर्ण

#अगर_घोषित CONFIG_DRM_I915_SW_FENCE_DEBUG_OBJECTS

अटल स्थिर काष्ठा debug_obj_descr i915_sw_fence_debug_descr = अणु
	.name = "i915_sw_fence",
	.debug_hपूर्णांक = i915_sw_fence_debug_hपूर्णांक,
पूर्ण;

अटल अंतरभूत व्योम debug_fence_init(काष्ठा i915_sw_fence *fence)
अणु
	debug_object_init(fence, &i915_sw_fence_debug_descr);
पूर्ण

अटल अंतरभूत व्योम debug_fence_init_onstack(काष्ठा i915_sw_fence *fence)
अणु
	debug_object_init_on_stack(fence, &i915_sw_fence_debug_descr);
पूर्ण

अटल अंतरभूत व्योम debug_fence_activate(काष्ठा i915_sw_fence *fence)
अणु
	debug_object_activate(fence, &i915_sw_fence_debug_descr);
पूर्ण

अटल अंतरभूत व्योम debug_fence_set_state(काष्ठा i915_sw_fence *fence,
					 पूर्णांक old, पूर्णांक new)
अणु
	debug_object_active_state(fence, &i915_sw_fence_debug_descr, old, new);
पूर्ण

अटल अंतरभूत व्योम debug_fence_deactivate(काष्ठा i915_sw_fence *fence)
अणु
	debug_object_deactivate(fence, &i915_sw_fence_debug_descr);
पूर्ण

अटल अंतरभूत व्योम debug_fence_destroy(काष्ठा i915_sw_fence *fence)
अणु
	debug_object_destroy(fence, &i915_sw_fence_debug_descr);
पूर्ण

अटल अंतरभूत व्योम debug_fence_मुक्त(काष्ठा i915_sw_fence *fence)
अणु
	debug_object_मुक्त(fence, &i915_sw_fence_debug_descr);
	smp_wmb(); /* flush the change in state beक्रमe पुनः_स्मृतिation */
पूर्ण

अटल अंतरभूत व्योम debug_fence_निश्चित(काष्ठा i915_sw_fence *fence)
अणु
	debug_object_निश्चित_init(fence, &i915_sw_fence_debug_descr);
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम debug_fence_init(काष्ठा i915_sw_fence *fence)
अणु
पूर्ण

अटल अंतरभूत व्योम debug_fence_init_onstack(काष्ठा i915_sw_fence *fence)
अणु
पूर्ण

अटल अंतरभूत व्योम debug_fence_activate(काष्ठा i915_sw_fence *fence)
अणु
पूर्ण

अटल अंतरभूत व्योम debug_fence_set_state(काष्ठा i915_sw_fence *fence,
					 पूर्णांक old, पूर्णांक new)
अणु
पूर्ण

अटल अंतरभूत व्योम debug_fence_deactivate(काष्ठा i915_sw_fence *fence)
अणु
पूर्ण

अटल अंतरभूत व्योम debug_fence_destroy(काष्ठा i915_sw_fence *fence)
अणु
पूर्ण

अटल अंतरभूत व्योम debug_fence_मुक्त(काष्ठा i915_sw_fence *fence)
अणु
पूर्ण

अटल अंतरभूत व्योम debug_fence_निश्चित(काष्ठा i915_sw_fence *fence)
अणु
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक __i915_sw_fence_notअगरy(काष्ठा i915_sw_fence *fence,
				  क्रमागत i915_sw_fence_notअगरy state)
अणु
	i915_sw_fence_notअगरy_t fn;

	fn = (i915_sw_fence_notअगरy_t)(fence->flags & I915_SW_FENCE_MASK);
	वापस fn(fence, state);
पूर्ण

#अगर_घोषित CONFIG_DRM_I915_SW_FENCE_DEBUG_OBJECTS
व्योम i915_sw_fence_fini(काष्ठा i915_sw_fence *fence)
अणु
	debug_fence_मुक्त(fence);
पूर्ण
#पूर्ण_अगर

अटल व्योम __i915_sw_fence_wake_up_all(काष्ठा i915_sw_fence *fence,
					काष्ठा list_head *continuation)
अणु
	रुको_queue_head_t *x = &fence->रुको;
	रुको_queue_entry_t *pos, *next;
	अचिन्हित दीर्घ flags;

	debug_fence_deactivate(fence);
	atomic_set_release(&fence->pending, -1); /* 0 -> -1 [करोne] */

	/*
	 * To prevent unbounded recursion as we traverse the graph of
	 * i915_sw_fences, we move the entry list from this, the next पढ़ोy
	 * fence, to the tail of the original fence's entry list
	 * (and so added to the list to be woken).
	 */

	spin_lock_irqsave_nested(&x->lock, flags, 1 + !!continuation);
	अगर (continuation) अणु
		list_क्रम_each_entry_safe(pos, next, &x->head, entry) अणु
			अगर (pos->flags & I915_SW_FENCE_FLAG_FENCE)
				list_move_tail(&pos->entry, continuation);
			अन्यथा
				pos->func(pos, TASK_NORMAL, 0, continuation);
		पूर्ण
	पूर्ण अन्यथा अणु
		LIST_HEAD(extra);

		करो अणु
			list_क्रम_each_entry_safe(pos, next, &x->head, entry) अणु
				पूर्णांक wake_flags;

				wake_flags = 0;
				अगर (pos->flags & I915_SW_FENCE_FLAG_FENCE)
					wake_flags = fence->error;

				pos->func(pos, TASK_NORMAL, wake_flags, &extra);
			पूर्ण

			अगर (list_empty(&extra))
				अवरोध;

			list_splice_tail_init(&extra, &x->head);
		पूर्ण जबतक (1);
	पूर्ण
	spin_unlock_irqrestore(&x->lock, flags);

	debug_fence_निश्चित(fence);
पूर्ण

अटल व्योम __i915_sw_fence_complete(काष्ठा i915_sw_fence *fence,
				     काष्ठा list_head *continuation)
अणु
	debug_fence_निश्चित(fence);

	अगर (!atomic_dec_and_test(&fence->pending))
		वापस;

	debug_fence_set_state(fence, DEBUG_FENCE_IDLE, DEBUG_FENCE_NOTIFY);

	अगर (__i915_sw_fence_notअगरy(fence, FENCE_COMPLETE) != NOTIFY_DONE)
		वापस;

	debug_fence_set_state(fence, DEBUG_FENCE_NOTIFY, DEBUG_FENCE_IDLE);

	__i915_sw_fence_wake_up_all(fence, continuation);

	debug_fence_destroy(fence);
	__i915_sw_fence_notअगरy(fence, FENCE_FREE);
पूर्ण

व्योम i915_sw_fence_complete(काष्ठा i915_sw_fence *fence)
अणु
	debug_fence_निश्चित(fence);

	अगर (WARN_ON(i915_sw_fence_करोne(fence)))
		वापस;

	__i915_sw_fence_complete(fence, शून्य);
पूर्ण

bool i915_sw_fence_aरुको(काष्ठा i915_sw_fence *fence)
अणु
	पूर्णांक pending;

	/*
	 * It is only safe to add a new aरुको to the fence जबतक it has
	 * not yet been संकेतed (i.e. there are still existing संकेतers).
	 */
	pending = atomic_पढ़ो(&fence->pending);
	करो अणु
		अगर (pending < 1)
			वापस false;
	पूर्ण जबतक (!atomic_try_cmpxchg(&fence->pending, &pending, pending + 1));

	वापस true;
पूर्ण

व्योम __i915_sw_fence_init(काष्ठा i915_sw_fence *fence,
			  i915_sw_fence_notअगरy_t fn,
			  स्थिर अक्षर *name,
			  काष्ठा lock_class_key *key)
अणु
	BUG_ON(!fn || (अचिन्हित दीर्घ)fn & ~I915_SW_FENCE_MASK);

	__init_रुकोqueue_head(&fence->रुको, name, key);
	fence->flags = (अचिन्हित दीर्घ)fn;

	i915_sw_fence_reinit(fence);
पूर्ण

व्योम i915_sw_fence_reinit(काष्ठा i915_sw_fence *fence)
अणु
	debug_fence_init(fence);

	atomic_set(&fence->pending, 1);
	fence->error = 0;

	I915_SW_FENCE_BUG_ON(!fence->flags);
	I915_SW_FENCE_BUG_ON(!list_empty(&fence->रुको.head));
पूर्ण

व्योम i915_sw_fence_commit(काष्ठा i915_sw_fence *fence)
अणु
	debug_fence_activate(fence);
	i915_sw_fence_complete(fence);
पूर्ण

अटल पूर्णांक i915_sw_fence_wake(रुको_queue_entry_t *wq, अचिन्हित mode, पूर्णांक flags, व्योम *key)
अणु
	i915_sw_fence_set_error_once(wq->निजी, flags);

	list_del(&wq->entry);
	__i915_sw_fence_complete(wq->निजी, key);

	अगर (wq->flags & I915_SW_FENCE_FLAG_ALLOC)
		kमुक्त(wq);
	वापस 0;
पूर्ण

अटल bool __i915_sw_fence_check_अगर_after(काष्ठा i915_sw_fence *fence,
				    स्थिर काष्ठा i915_sw_fence * स्थिर संकेतer)
अणु
	रुको_queue_entry_t *wq;

	अगर (__test_and_set_bit(I915_SW_FENCE_CHECKED_BIT, &fence->flags))
		वापस false;

	अगर (fence == संकेतer)
		वापस true;

	list_क्रम_each_entry(wq, &fence->रुको.head, entry) अणु
		अगर (wq->func != i915_sw_fence_wake)
			जारी;

		अगर (__i915_sw_fence_check_अगर_after(wq->निजी, संकेतer))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम __i915_sw_fence_clear_checked_bit(काष्ठा i915_sw_fence *fence)
अणु
	रुको_queue_entry_t *wq;

	अगर (!__test_and_clear_bit(I915_SW_FENCE_CHECKED_BIT, &fence->flags))
		वापस;

	list_क्रम_each_entry(wq, &fence->रुको.head, entry) अणु
		अगर (wq->func != i915_sw_fence_wake)
			जारी;

		__i915_sw_fence_clear_checked_bit(wq->निजी);
	पूर्ण
पूर्ण

अटल bool i915_sw_fence_check_अगर_after(काष्ठा i915_sw_fence *fence,
				  स्थिर काष्ठा i915_sw_fence * स्थिर संकेतer)
अणु
	अचिन्हित दीर्घ flags;
	bool err;

	अगर (!IS_ENABLED(CONFIG_DRM_I915_SW_FENCE_CHECK_DAG))
		वापस false;

	spin_lock_irqsave(&i915_sw_fence_lock, flags);
	err = __i915_sw_fence_check_अगर_after(fence, संकेतer);
	__i915_sw_fence_clear_checked_bit(fence);
	spin_unlock_irqrestore(&i915_sw_fence_lock, flags);

	वापस err;
पूर्ण

अटल पूर्णांक __i915_sw_fence_aरुको_sw_fence(काष्ठा i915_sw_fence *fence,
					  काष्ठा i915_sw_fence *संकेतer,
					  रुको_queue_entry_t *wq, gfp_t gfp)
अणु
	अचिन्हित पूर्णांक pending;
	अचिन्हित दीर्घ flags;

	debug_fence_निश्चित(fence);
	might_sleep_अगर(gfpflags_allow_blocking(gfp));

	अगर (i915_sw_fence_करोne(संकेतer)) अणु
		i915_sw_fence_set_error_once(fence, संकेतer->error);
		वापस 0;
	पूर्ण

	debug_fence_निश्चित(संकेतer);

	/* The dependency graph must be acyclic. */
	अगर (unlikely(i915_sw_fence_check_अगर_after(fence, संकेतer)))
		वापस -EINVAL;

	pending = I915_SW_FENCE_FLAG_FENCE;
	अगर (!wq) अणु
		wq = kदो_स्मृति(माप(*wq), gfp);
		अगर (!wq) अणु
			अगर (!gfpflags_allow_blocking(gfp))
				वापस -ENOMEM;

			i915_sw_fence_रुको(संकेतer);
			i915_sw_fence_set_error_once(fence, संकेतer->error);
			वापस 0;
		पूर्ण

		pending |= I915_SW_FENCE_FLAG_ALLOC;
	पूर्ण

	INIT_LIST_HEAD(&wq->entry);
	wq->flags = pending;
	wq->func = i915_sw_fence_wake;
	wq->निजी = fence;

	i915_sw_fence_aरुको(fence);

	spin_lock_irqsave(&संकेतer->रुको.lock, flags);
	अगर (likely(!i915_sw_fence_करोne(संकेतer))) अणु
		__add_रुको_queue_entry_tail(&संकेतer->रुको, wq);
		pending = 1;
	पूर्ण अन्यथा अणु
		i915_sw_fence_wake(wq, 0, संकेतer->error, शून्य);
		pending = 0;
	पूर्ण
	spin_unlock_irqrestore(&संकेतer->रुको.lock, flags);

	वापस pending;
पूर्ण

पूर्णांक i915_sw_fence_aरुको_sw_fence(काष्ठा i915_sw_fence *fence,
				 काष्ठा i915_sw_fence *संकेतer,
				 रुको_queue_entry_t *wq)
अणु
	वापस __i915_sw_fence_aरुको_sw_fence(fence, संकेतer, wq, 0);
पूर्ण

पूर्णांक i915_sw_fence_aरुको_sw_fence_gfp(काष्ठा i915_sw_fence *fence,
				     काष्ठा i915_sw_fence *संकेतer,
				     gfp_t gfp)
अणु
	वापस __i915_sw_fence_aरुको_sw_fence(fence, संकेतer, शून्य, gfp);
पूर्ण

काष्ठा i915_sw_dma_fence_cb_समयr अणु
	काष्ठा i915_sw_dma_fence_cb base;
	काष्ठा dma_fence *dma;
	काष्ठा समयr_list समयr;
	काष्ठा irq_work work;
	काष्ठा rcu_head rcu;
पूर्ण;

अटल व्योम dma_i915_sw_fence_wake(काष्ठा dma_fence *dma,
				   काष्ठा dma_fence_cb *data)
अणु
	काष्ठा i915_sw_dma_fence_cb *cb = container_of(data, typeof(*cb), base);

	i915_sw_fence_set_error_once(cb->fence, dma->error);
	i915_sw_fence_complete(cb->fence);
	kमुक्त(cb);
पूर्ण

अटल व्योम समयr_i915_sw_fence_wake(काष्ठा समयr_list *t)
अणु
	काष्ठा i915_sw_dma_fence_cb_समयr *cb = from_समयr(cb, t, समयr);
	काष्ठा i915_sw_fence *fence;

	fence = xchg(&cb->base.fence, शून्य);
	अगर (!fence)
		वापस;

	pr_notice("Asynchronous wait on fence %s:%s:%llx timed out (hint:%ps)\n",
		  cb->dma->ops->get_driver_name(cb->dma),
		  cb->dma->ops->get_समयline_name(cb->dma),
		  cb->dma->seqno,
		  i915_sw_fence_debug_hपूर्णांक(fence));

	i915_sw_fence_set_error_once(fence, -ETIMEDOUT);
	i915_sw_fence_complete(fence);
पूर्ण

अटल व्योम dma_i915_sw_fence_wake_समयr(काष्ठा dma_fence *dma,
					 काष्ठा dma_fence_cb *data)
अणु
	काष्ठा i915_sw_dma_fence_cb_समयr *cb =
		container_of(data, typeof(*cb), base.base);
	काष्ठा i915_sw_fence *fence;

	fence = xchg(&cb->base.fence, शून्य);
	अगर (fence) अणु
		i915_sw_fence_set_error_once(fence, dma->error);
		i915_sw_fence_complete(fence);
	पूर्ण

	irq_work_queue(&cb->work);
पूर्ण

अटल व्योम irq_i915_sw_fence_work(काष्ठा irq_work *wrk)
अणु
	काष्ठा i915_sw_dma_fence_cb_समयr *cb =
		container_of(wrk, typeof(*cb), work);

	del_समयr_sync(&cb->समयr);
	dma_fence_put(cb->dma);

	kमुक्त_rcu(cb, rcu);
पूर्ण

पूर्णांक i915_sw_fence_aरुको_dma_fence(काष्ठा i915_sw_fence *fence,
				  काष्ठा dma_fence *dma,
				  अचिन्हित दीर्घ समयout,
				  gfp_t gfp)
अणु
	काष्ठा i915_sw_dma_fence_cb *cb;
	dma_fence_func_t func;
	पूर्णांक ret;

	debug_fence_निश्चित(fence);
	might_sleep_अगर(gfpflags_allow_blocking(gfp));

	अगर (dma_fence_is_संकेतed(dma)) अणु
		i915_sw_fence_set_error_once(fence, dma->error);
		वापस 0;
	पूर्ण

	cb = kदो_स्मृति(समयout ?
		     माप(काष्ठा i915_sw_dma_fence_cb_समयr) :
		     माप(काष्ठा i915_sw_dma_fence_cb),
		     gfp);
	अगर (!cb) अणु
		अगर (!gfpflags_allow_blocking(gfp))
			वापस -ENOMEM;

		ret = dma_fence_रुको(dma, false);
		अगर (ret)
			वापस ret;

		i915_sw_fence_set_error_once(fence, dma->error);
		वापस 0;
	पूर्ण

	cb->fence = fence;
	i915_sw_fence_aरुको(fence);

	func = dma_i915_sw_fence_wake;
	अगर (समयout) अणु
		काष्ठा i915_sw_dma_fence_cb_समयr *समयr =
			container_of(cb, typeof(*समयr), base);

		समयr->dma = dma_fence_get(dma);
		init_irq_work(&समयr->work, irq_i915_sw_fence_work);

		समयr_setup(&समयr->समयr,
			    समयr_i915_sw_fence_wake, TIMER_IRQSAFE);
		mod_समयr(&समयr->समयr, round_jअगरfies_up(jअगरfies + समयout));

		func = dma_i915_sw_fence_wake_समयr;
	पूर्ण

	ret = dma_fence_add_callback(dma, &cb->base, func);
	अगर (ret == 0) अणु
		ret = 1;
	पूर्ण अन्यथा अणु
		func(dma, &cb->base);
		अगर (ret == -ENOENT) /* fence alपढ़ोy संकेतed */
			ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __dma_i915_sw_fence_wake(काष्ठा dma_fence *dma,
				     काष्ठा dma_fence_cb *data)
अणु
	काष्ठा i915_sw_dma_fence_cb *cb = container_of(data, typeof(*cb), base);

	i915_sw_fence_set_error_once(cb->fence, dma->error);
	i915_sw_fence_complete(cb->fence);
पूर्ण

पूर्णांक __i915_sw_fence_aरुको_dma_fence(काष्ठा i915_sw_fence *fence,
				    काष्ठा dma_fence *dma,
				    काष्ठा i915_sw_dma_fence_cb *cb)
अणु
	पूर्णांक ret;

	debug_fence_निश्चित(fence);

	अगर (dma_fence_is_संकेतed(dma)) अणु
		i915_sw_fence_set_error_once(fence, dma->error);
		वापस 0;
	पूर्ण

	cb->fence = fence;
	i915_sw_fence_aरुको(fence);

	ret = 1;
	अगर (dma_fence_add_callback(dma, &cb->base, __dma_i915_sw_fence_wake)) अणु
		/* fence alपढ़ोy संकेतed */
		__dma_i915_sw_fence_wake(dma, &cb->base);
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक i915_sw_fence_aरुको_reservation(काष्ठा i915_sw_fence *fence,
				    काष्ठा dma_resv *resv,
				    स्थिर काष्ठा dma_fence_ops *exclude,
				    bool ग_लिखो,
				    अचिन्हित दीर्घ समयout,
				    gfp_t gfp)
अणु
	काष्ठा dma_fence *excl;
	पूर्णांक ret = 0, pending;

	debug_fence_निश्चित(fence);
	might_sleep_अगर(gfpflags_allow_blocking(gfp));

	अगर (ग_लिखो) अणु
		काष्ठा dma_fence **shared;
		अचिन्हित पूर्णांक count, i;

		ret = dma_resv_get_fences_rcu(resv, &excl, &count, &shared);
		अगर (ret)
			वापस ret;

		क्रम (i = 0; i < count; i++) अणु
			अगर (shared[i]->ops == exclude)
				जारी;

			pending = i915_sw_fence_aरुको_dma_fence(fence,
								shared[i],
								समयout,
								gfp);
			अगर (pending < 0) अणु
				ret = pending;
				अवरोध;
			पूर्ण

			ret |= pending;
		पूर्ण

		क्रम (i = 0; i < count; i++)
			dma_fence_put(shared[i]);
		kमुक्त(shared);
	पूर्ण अन्यथा अणु
		excl = dma_resv_get_excl_rcu(resv);
	पूर्ण

	अगर (ret >= 0 && excl && excl->ops != exclude) अणु
		pending = i915_sw_fence_aरुको_dma_fence(fence,
							excl,
							समयout,
							gfp);
		अगर (pending < 0)
			ret = pending;
		अन्यथा
			ret |= pending;
	पूर्ण

	dma_fence_put(excl);

	वापस ret;
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "selftests/lib_sw_fence.c"
#समावेश "selftests/i915_sw_fence.c"
#पूर्ण_अगर
