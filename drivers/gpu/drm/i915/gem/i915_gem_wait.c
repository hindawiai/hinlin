<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2016 Intel Corporation
 */

#समावेश <linux/dma-fence-array.h>
#समावेश <linux/dma-fence-chain.h>
#समावेश <linux/jअगरfies.h>

#समावेश "gt/intel_engine.h"

#समावेश "dma_resv_utils.h"
#समावेश "i915_gem_ioctls.h"
#समावेश "i915_gem_object.h"

अटल दीर्घ
i915_gem_object_रुको_fence(काष्ठा dma_fence *fence,
			   अचिन्हित पूर्णांक flags,
			   दीर्घ समयout)
अणु
	BUILD_BUG_ON(I915_WAIT_INTERRUPTIBLE != 0x1);

	अगर (test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &fence->flags))
		वापस समयout;

	अगर (dma_fence_is_i915(fence))
		वापस i915_request_रुको(to_request(fence), flags, समयout);

	वापस dma_fence_रुको_समयout(fence,
				      flags & I915_WAIT_INTERRUPTIBLE,
				      समयout);
पूर्ण

अटल दीर्घ
i915_gem_object_रुको_reservation(काष्ठा dma_resv *resv,
				 अचिन्हित पूर्णांक flags,
				 दीर्घ समयout)
अणु
	काष्ठा dma_fence *excl;
	bool prune_fences = false;

	अगर (flags & I915_WAIT_ALL) अणु
		काष्ठा dma_fence **shared;
		अचिन्हित पूर्णांक count, i;
		पूर्णांक ret;

		ret = dma_resv_get_fences_rcu(resv, &excl, &count, &shared);
		अगर (ret)
			वापस ret;

		क्रम (i = 0; i < count; i++) अणु
			समयout = i915_gem_object_रुको_fence(shared[i],
							     flags, समयout);
			अगर (समयout < 0)
				अवरोध;

			dma_fence_put(shared[i]);
		पूर्ण

		क्रम (; i < count; i++)
			dma_fence_put(shared[i]);
		kमुक्त(shared);

		/*
		 * If both shared fences and an exclusive fence exist,
		 * then by स्थिरruction the shared fences must be later
		 * than the exclusive fence. If we successfully रुको क्रम
		 * all the shared fences, we know that the exclusive fence
		 * must all be संकेतed. If all the shared fences are
		 * संकेतed, we can prune the array and recover the
		 * भग्नing references on the fences/requests.
		 */
		prune_fences = count && समयout >= 0;
	पूर्ण अन्यथा अणु
		excl = dma_resv_get_excl_rcu(resv);
	पूर्ण

	अगर (excl && समयout >= 0)
		समयout = i915_gem_object_रुको_fence(excl, flags, समयout);

	dma_fence_put(excl);

	/*
	 * Opportunistically prune the fences अगरf we know they have *all* been
	 * संकेतed.
	 */
	अगर (prune_fences)
		dma_resv_prune(resv);

	वापस समयout;
पूर्ण

अटल व्योम fence_set_priority(काष्ठा dma_fence *fence,
			       स्थिर काष्ठा i915_sched_attr *attr)
अणु
	काष्ठा i915_request *rq;
	काष्ठा पूर्णांकel_engine_cs *engine;

	अगर (dma_fence_is_संकेतed(fence) || !dma_fence_is_i915(fence))
		वापस;

	rq = to_request(fence);
	engine = rq->engine;

	rcu_पढ़ो_lock(); /* RCU serialisation क्रम set-wedged protection */
	अगर (engine->schedule)
		engine->schedule(rq, attr);
	rcu_पढ़ो_unlock();
पूर्ण

अटल अंतरभूत bool __dma_fence_is_chain(स्थिर काष्ठा dma_fence *fence)
अणु
	वापस fence->ops == &dma_fence_chain_ops;
पूर्ण

व्योम i915_gem_fence_रुको_priority(काष्ठा dma_fence *fence,
				  स्थिर काष्ठा i915_sched_attr *attr)
अणु
	अगर (dma_fence_is_संकेतed(fence))
		वापस;

	local_bh_disable();

	/* Recurse once पूर्णांकo a fence-array */
	अगर (dma_fence_is_array(fence)) अणु
		काष्ठा dma_fence_array *array = to_dma_fence_array(fence);
		पूर्णांक i;

		क्रम (i = 0; i < array->num_fences; i++)
			fence_set_priority(array->fences[i], attr);
	पूर्ण अन्यथा अगर (__dma_fence_is_chain(fence)) अणु
		काष्ठा dma_fence *iter;

		/* The chain is ordered; अगर we boost the last, we boost all */
		dma_fence_chain_क्रम_each(iter, fence) अणु
			fence_set_priority(to_dma_fence_chain(iter)->fence,
					   attr);
			अवरोध;
		पूर्ण
		dma_fence_put(iter);
	पूर्ण अन्यथा अणु
		fence_set_priority(fence, attr);
	पूर्ण

	local_bh_enable(); /* kick the tasklets अगर queues were reprioritised */
पूर्ण

पूर्णांक
i915_gem_object_रुको_priority(काष्ठा drm_i915_gem_object *obj,
			      अचिन्हित पूर्णांक flags,
			      स्थिर काष्ठा i915_sched_attr *attr)
अणु
	काष्ठा dma_fence *excl;

	अगर (flags & I915_WAIT_ALL) अणु
		काष्ठा dma_fence **shared;
		अचिन्हित पूर्णांक count, i;
		पूर्णांक ret;

		ret = dma_resv_get_fences_rcu(obj->base.resv,
					      &excl, &count, &shared);
		अगर (ret)
			वापस ret;

		क्रम (i = 0; i < count; i++) अणु
			i915_gem_fence_रुको_priority(shared[i], attr);
			dma_fence_put(shared[i]);
		पूर्ण

		kमुक्त(shared);
	पूर्ण अन्यथा अणु
		excl = dma_resv_get_excl_rcu(obj->base.resv);
	पूर्ण

	अगर (excl) अणु
		i915_gem_fence_रुको_priority(excl, attr);
		dma_fence_put(excl);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * Waits क्रम rendering to the object to be completed
 * @obj: i915 gem object
 * @flags: how to रुको (under a lock, क्रम all rendering or just क्रम ग_लिखोs etc)
 * @समयout: how दीर्घ to रुको
 */
पूर्णांक
i915_gem_object_रुको(काष्ठा drm_i915_gem_object *obj,
		     अचिन्हित पूर्णांक flags,
		     दीर्घ समयout)
अणु
	might_sleep();
	GEM_BUG_ON(समयout < 0);

	समयout = i915_gem_object_रुको_reservation(obj->base.resv,
						   flags, समयout);
	वापस समयout < 0 ? समयout : 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ nsecs_to_jअगरfies_समयout(स्थिर u64 n)
अणु
	/* nsecs_to_jअगरfies64() करोes not guard against overflow */
	अगर (NSEC_PER_SEC % HZ &&
	    भाग_u64(n, NSEC_PER_SEC) >= MAX_JIFFY_OFFSET / HZ)
		वापस MAX_JIFFY_OFFSET;

	वापस min_t(u64, MAX_JIFFY_OFFSET, nsecs_to_jअगरfies64(n) + 1);
पूर्ण

अटल अचिन्हित दीर्घ to_रुको_समयout(s64 समयout_ns)
अणु
	अगर (समयout_ns < 0)
		वापस MAX_SCHEDULE_TIMEOUT;

	अगर (समयout_ns == 0)
		वापस 0;

	वापस nsecs_to_jअगरfies_समयout(समयout_ns);
पूर्ण

/**
 * i915_gem_रुको_ioctl - implements DRM_IOCTL_I915_GEM_WAIT
 * @dev: drm device poपूर्णांकer
 * @data: ioctl data blob
 * @file: drm file poपूर्णांकer
 *
 * Returns 0 अगर successful, अन्यथा an error is वापसed with the reमुख्यing समय in
 * the समयout parameter.
 *  -ETIME: object is still busy after समयout
 *  -ERESTARTSYS: संकेत पूर्णांकerrupted the रुको
 *  -ENONENT: object करोesn't exist
 * Also possible, but rare:
 *  -EAGAIN: incomplete, restart syscall
 *  -ENOMEM: damn
 *  -ENODEV: Internal IRQ fail
 *  -E?: The add request failed
 *
 * The रुको ioctl with a समयout of 0 reimplements the busy ioctl. With any
 * non-zero समयout parameter the रुको ioctl will रुको क्रम the given number of
 * nanoseconds on an object becoming unbusy. Since the रुको itself करोes so
 * without holding काष्ठा_mutex the object may become re-busied beक्रमe this
 * function completes. A similar but लघुer * race condition exists in the busy
 * ioctl
 */
पूर्णांक
i915_gem_रुको_ioctl(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file)
अणु
	काष्ठा drm_i915_gem_रुको *args = data;
	काष्ठा drm_i915_gem_object *obj;
	kसमय_प्रकार start;
	दीर्घ ret;

	अगर (args->flags != 0)
		वापस -EINVAL;

	obj = i915_gem_object_lookup(file, args->bo_handle);
	अगर (!obj)
		वापस -ENOENT;

	start = kसमय_get();

	ret = i915_gem_object_रुको(obj,
				   I915_WAIT_INTERRUPTIBLE |
				   I915_WAIT_PRIORITY |
				   I915_WAIT_ALL,
				   to_रुको_समयout(args->समयout_ns));

	अगर (args->समयout_ns > 0) अणु
		args->समयout_ns -= kसमय_प्रकारo_ns(kसमय_sub(kसमय_get(), start));
		अगर (args->समयout_ns < 0)
			args->समयout_ns = 0;

		/*
		 * Apparently kसमय isn't accurate enough and occasionally has a
		 * bit of mismatch in the jअगरfies<->nsecs<->kसमय loop. So patch
		 * things up to make the test happy. We allow up to 1 jअगरfy.
		 *
		 * This is a regression from the बारpec->kसमय conversion.
		 */
		अगर (ret == -ETIME && !nsecs_to_jअगरfies(args->समयout_ns))
			args->समयout_ns = 0;

		/* Asked to रुको beyond the jअगरfie/scheduler precision? */
		अगर (ret == -ETIME && args->समयout_ns)
			ret = -EAGAIN;
	पूर्ण

	i915_gem_object_put(obj);
	वापस ret;
पूर्ण
