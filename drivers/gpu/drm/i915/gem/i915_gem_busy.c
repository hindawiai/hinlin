<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2014-2016 Intel Corporation
 */

#समावेश "gt/intel_engine.h"

#समावेश "i915_gem_ioctls.h"
#समावेश "i915_gem_object.h"

अटल __always_अंतरभूत u32 __busy_पढ़ो_flag(u16 id)
अणु
	अगर (id == (u16)I915_ENGINE_CLASS_INVALID)
		वापस 0xffff0000u;

	GEM_BUG_ON(id >= 16);
	वापस 0x10000u << id;
पूर्ण

अटल __always_अंतरभूत u32 __busy_ग_लिखो_id(u16 id)
अणु
	/*
	 * The uABI guarantees an active ग_लिखोr is also amongst the पढ़ो
	 * engines. This would be true अगर we accessed the activity tracking
	 * under the lock, but as we perक्रमm the lookup of the object and
	 * its activity locklessly we can not guarantee that the last_ग_लिखो
	 * being active implies that we have set the same engine flag from
	 * last_पढ़ो - hence we always set both पढ़ो and ग_लिखो busy क्रम
	 * last_ग_लिखो.
	 */
	अगर (id == (u16)I915_ENGINE_CLASS_INVALID)
		वापस 0xffffffffu;

	वापस (id + 1) | __busy_पढ़ो_flag(id);
पूर्ण

अटल __always_अंतरभूत अचिन्हित पूर्णांक
__busy_set_अगर_active(स्थिर काष्ठा dma_fence *fence, u32 (*flag)(u16 id))
अणु
	स्थिर काष्ठा i915_request *rq;

	/*
	 * We have to check the current hw status of the fence as the uABI
	 * guarantees क्रमward progress. We could rely on the idle worker
	 * to eventually flush us, but to minimise latency just ask the
	 * hardware.
	 *
	 * Note we only report on the status of native fences.
	 */
	अगर (!dma_fence_is_i915(fence))
		वापस 0;

	/* खोलोcode to_request() in order to aव्योम स्थिर warnings */
	rq = container_of(fence, स्थिर काष्ठा i915_request, fence);
	अगर (i915_request_completed(rq))
		वापस 0;

	/* Beware type-expansion follies! */
	BUILD_BUG_ON(!typecheck(u16, rq->engine->uabi_class));
	वापस flag(rq->engine->uabi_class);
पूर्ण

अटल __always_अंतरभूत अचिन्हित पूर्णांक
busy_check_पढ़ोer(स्थिर काष्ठा dma_fence *fence)
अणु
	वापस __busy_set_अगर_active(fence, __busy_पढ़ो_flag);
पूर्ण

अटल __always_अंतरभूत अचिन्हित पूर्णांक
busy_check_ग_लिखोr(स्थिर काष्ठा dma_fence *fence)
अणु
	अगर (!fence)
		वापस 0;

	वापस __busy_set_अगर_active(fence, __busy_ग_लिखो_id);
पूर्ण

पूर्णांक
i915_gem_busy_ioctl(काष्ठा drm_device *dev, व्योम *data,
		    काष्ठा drm_file *file)
अणु
	काष्ठा drm_i915_gem_busy *args = data;
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा dma_resv_list *list;
	अचिन्हित पूर्णांक seq;
	पूर्णांक err;

	err = -ENOENT;
	rcu_पढ़ो_lock();
	obj = i915_gem_object_lookup_rcu(file, args->handle);
	अगर (!obj)
		जाओ out;

	/*
	 * A discrepancy here is that we करो not report the status of
	 * non-i915 fences, i.e. even though we may report the object as idle,
	 * a call to set-करोमुख्य may still stall रुकोing क्रम क्रमeign rendering.
	 * This also means that रुको-ioctl may report an object as busy,
	 * where busy-ioctl considers it idle.
	 *
	 * We trade the ability to warn of क्रमeign fences to report on which
	 * i915 engines are active क्रम the object.
	 *
	 * Alternatively, we can trade that extra inक्रमmation on पढ़ो/ग_लिखो
	 * activity with
	 *	args->busy =
	 *		!dma_resv_test_संकेतed_rcu(obj->resv, true);
	 * to report the overall busyness. This is what the रुको-ioctl करोes.
	 *
	 */
retry:
	seq = raw_पढ़ो_seqcount(&obj->base.resv->seq);

	/* Translate the exclusive fence to the READ *and* WRITE engine */
	args->busy =
		busy_check_ग_लिखोr(rcu_dereference(obj->base.resv->fence_excl));

	/* Translate shared fences to READ set of engines */
	list = rcu_dereference(obj->base.resv->fence);
	अगर (list) अणु
		अचिन्हित पूर्णांक shared_count = list->shared_count, i;

		क्रम (i = 0; i < shared_count; ++i) अणु
			काष्ठा dma_fence *fence =
				rcu_dereference(list->shared[i]);

			args->busy |= busy_check_पढ़ोer(fence);
		पूर्ण
	पूर्ण

	अगर (args->busy && पढ़ो_seqcount_retry(&obj->base.resv->seq, seq))
		जाओ retry;

	err = 0;
out:
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण
