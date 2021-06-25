<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित _I915_ACTIVE_H_
#घोषणा _I915_ACTIVE_H_

#समावेश <linux/lockdep.h>

#समावेश "i915_active_types.h"
#समावेश "i915_request.h"

काष्ठा i915_request;
काष्ठा पूर्णांकel_engine_cs;
काष्ठा पूर्णांकel_समयline;

/*
 * We treat requests as fences. This is not be to confused with our
 * "fence registers" but pipeline synchronisation objects ala GL_ARB_sync.
 * We use the fences to synchronize access from the CPU with activity on the
 * GPU, क्रम example, we should not reग_लिखो an object's PTE whilst the GPU
 * is पढ़ोing them. We also track fences at a higher level to provide
 * implicit synchronisation around GEM objects, e.g. set-करोमुख्य will रुको
 * क्रम outstanding GPU rendering beक्रमe marking the object पढ़ोy क्रम CPU
 * access, or a pageflip will रुको until the GPU is complete beक्रमe showing
 * the frame on the scanout.
 *
 * In order to use a fence, the object must track the fence it needs to
 * serialise with. For example, GEM objects want to track both पढ़ो and
 * ग_लिखो access so that we can perक्रमm concurrent पढ़ो operations between
 * the CPU and GPU engines, as well as रुकोing क्रम all rendering to
 * complete, or रुकोing क्रम the last GPU user of a "fence register". The
 * object then embeds a #i915_active_fence to track the most recent (in
 * retirement order) request relevant क्रम the desired mode of access.
 * The #i915_active_fence is updated with i915_active_fence_set() to
 * track the most recent fence request, typically this is करोne as part of
 * i915_vma_move_to_active().
 *
 * When the #i915_active_fence completes (is retired), it will
 * संकेत its completion to the owner through a callback as well as mark
 * itself as idle (i915_active_fence.request == शून्य). The owner
 * can then perक्रमm any action, such as delayed मुक्तing of an active
 * resource including itself.
 */

व्योम i915_active_noop(काष्ठा dma_fence *fence, काष्ठा dma_fence_cb *cb);

/**
 * __i915_active_fence_init - prepares the activity tracker क्रम use
 * @active - the active tracker
 * @fence - initial fence to track, can be शून्य
 * @func - a callback when then the tracker is retired (becomes idle),
 *         can be शून्य
 *
 * i915_active_fence_init() prepares the embedded @active काष्ठा क्रम use as
 * an activity tracker, that is क्रम tracking the last known active fence
 * associated with it. When the last fence becomes idle, when it is retired
 * after completion, the optional callback @func is invoked.
 */
अटल अंतरभूत व्योम
__i915_active_fence_init(काष्ठा i915_active_fence *active,
			 व्योम *fence,
			 dma_fence_func_t fn)
अणु
	RCU_INIT_POINTER(active->fence, fence);
	active->cb.func = fn ?: i915_active_noop;
पूर्ण

#घोषणा INIT_ACTIVE_FENCE(A) \
	__i915_active_fence_init((A), शून्य, शून्य)

काष्ठा dma_fence *
__i915_active_fence_set(काष्ठा i915_active_fence *active,
			काष्ठा dma_fence *fence);

/**
 * i915_active_fence_set - updates the tracker to watch the current fence
 * @active - the active tracker
 * @rq - the request to watch
 *
 * i915_active_fence_set() watches the given @rq क्रम completion. While
 * that @rq is busy, the @active reports busy. When that @rq is संकेतed
 * (or अन्यथा retired) the @active tracker is updated to report idle.
 */
पूर्णांक __must_check
i915_active_fence_set(काष्ठा i915_active_fence *active,
		      काष्ठा i915_request *rq);
/**
 * i915_active_fence_get - वापस a reference to the active fence
 * @active - the active tracker
 *
 * i915_active_fence_get() वापसs a reference to the active fence,
 * or शून्य अगर the active tracker is idle. The reference is obtained under RCU,
 * so no locking is required by the caller.
 *
 * The reference should be मुक्तd with dma_fence_put().
 */
अटल अंतरभूत काष्ठा dma_fence *
i915_active_fence_get(काष्ठा i915_active_fence *active)
अणु
	काष्ठा dma_fence *fence;

	rcu_पढ़ो_lock();
	fence = dma_fence_get_rcu_safe(&active->fence);
	rcu_पढ़ो_unlock();

	वापस fence;
पूर्ण

/**
 * i915_active_fence_isset - report whether the active tracker is asचिन्हित
 * @active - the active tracker
 *
 * i915_active_fence_isset() वापसs true अगर the active tracker is currently
 * asचिन्हित to a fence. Due to the lazy retiring, that fence may be idle
 * and this may report stale inक्रमmation.
 */
अटल अंतरभूत bool
i915_active_fence_isset(स्थिर काष्ठा i915_active_fence *active)
अणु
	वापस rcu_access_poपूर्णांकer(active->fence);
पूर्ण

/*
 * GPU activity tracking
 *
 * Each set of commands submitted to the GPU compromises a single request that
 * संकेतs a fence upon completion. काष्ठा i915_request combines the
 * command submission, scheduling and fence संकेतing roles. If we want to see
 * अगर a particular task is complete, we need to grab the fence (काष्ठा
 * i915_request) क्रम that task and check or रुको क्रम it to be संकेतed. More
 * often though we want to track the status of a bunch of tasks, क्रम example
 * to रुको क्रम the GPU to finish accessing some memory across a variety of
 * dअगरferent command pipelines from dअगरferent clients. We could choose to
 * track every single request associated with the task, but knowing that
 * each request beदीर्घs to an ordered समयline (later requests within a
 * समयline must रुको क्रम earlier requests), we need only track the
 * latest request in each समयline to determine the overall status of the
 * task.
 *
 * काष्ठा i915_active provides this tracking across समयlines. It builds a
 * composite shared-fence, and is updated as new work is submitted to the task,
 * क्रमming a snapshot of the current status. It should be embedded पूर्णांकo the
 * dअगरferent resources that need to track their associated GPU activity to
 * provide a callback when that GPU activity has ceased, or otherwise to
 * provide a serialisation poपूर्णांक either क्रम request submission or क्रम CPU
 * synchronisation.
 */

व्योम __i915_active_init(काष्ठा i915_active *ref,
			पूर्णांक (*active)(काष्ठा i915_active *ref),
			व्योम (*retire)(काष्ठा i915_active *ref),
			काष्ठा lock_class_key *mkey,
			काष्ठा lock_class_key *wkey);

/* Specialise each class of i915_active to aव्योम impossible lockdep cycles. */
#घोषणा i915_active_init(ref, active, retire) करो अणु		\
	अटल काष्ठा lock_class_key __mkey;				\
	अटल काष्ठा lock_class_key __wkey;				\
									\
	__i915_active_init(ref, active, retire, &__mkey, &__wkey);	\
पूर्ण जबतक (0)

काष्ठा dma_fence *
__i915_active_ref(काष्ठा i915_active *ref, u64 idx, काष्ठा dma_fence *fence);
पूर्णांक i915_active_ref(काष्ठा i915_active *ref, u64 idx, काष्ठा dma_fence *fence);

अटल अंतरभूत पूर्णांक
i915_active_add_request(काष्ठा i915_active *ref, काष्ठा i915_request *rq)
अणु
	वापस i915_active_ref(ref,
			       i915_request_समयline(rq)->fence_context,
			       &rq->fence);
पूर्ण

काष्ठा dma_fence *
i915_active_set_exclusive(काष्ठा i915_active *ref, काष्ठा dma_fence *f);

अटल अंतरभूत bool i915_active_has_exclusive(काष्ठा i915_active *ref)
अणु
	वापस rcu_access_poपूर्णांकer(ref->excl.fence);
पूर्ण

पूर्णांक __i915_active_रुको(काष्ठा i915_active *ref, पूर्णांक state);
अटल अंतरभूत पूर्णांक i915_active_रुको(काष्ठा i915_active *ref)
अणु
	वापस __i915_active_रुको(ref, TASK_INTERRUPTIBLE);
पूर्ण

पूर्णांक i915_sw_fence_aरुको_active(काष्ठा i915_sw_fence *fence,
			       काष्ठा i915_active *ref,
			       अचिन्हित पूर्णांक flags);
पूर्णांक i915_request_aरुको_active(काष्ठा i915_request *rq,
			      काष्ठा i915_active *ref,
			      अचिन्हित पूर्णांक flags);
#घोषणा I915_ACTIVE_AWAIT_EXCL BIT(0)
#घोषणा I915_ACTIVE_AWAIT_ACTIVE BIT(1)
#घोषणा I915_ACTIVE_AWAIT_BARRIER BIT(2)

पूर्णांक i915_active_acquire(काष्ठा i915_active *ref);
पूर्णांक i915_active_acquire_क्रम_context(काष्ठा i915_active *ref, u64 idx);
bool i915_active_acquire_अगर_busy(काष्ठा i915_active *ref);

व्योम i915_active_release(काष्ठा i915_active *ref);

अटल अंतरभूत व्योम __i915_active_acquire(काष्ठा i915_active *ref)
अणु
	GEM_BUG_ON(!atomic_पढ़ो(&ref->count));
	atomic_inc(&ref->count);
पूर्ण

अटल अंतरभूत bool
i915_active_is_idle(स्थिर काष्ठा i915_active *ref)
अणु
	वापस !atomic_पढ़ो(&ref->count);
पूर्ण

व्योम i915_active_fini(काष्ठा i915_active *ref);

पूर्णांक i915_active_acquire_pपुनः_स्मृतिate_barrier(काष्ठा i915_active *ref,
					    काष्ठा पूर्णांकel_engine_cs *engine);
व्योम i915_active_acquire_barrier(काष्ठा i915_active *ref);
व्योम i915_request_add_active_barriers(काष्ठा i915_request *rq);

व्योम i915_active_prपूर्णांक(काष्ठा i915_active *ref, काष्ठा drm_prपूर्णांकer *m);
व्योम i915_active_unlock_रुको(काष्ठा i915_active *ref);

काष्ठा i915_active *i915_active_create(व्योम);
काष्ठा i915_active *i915_active_get(काष्ठा i915_active *ref);
व्योम i915_active_put(काष्ठा i915_active *ref);

अटल अंतरभूत पूर्णांक __i915_request_aरुको_exclusive(काष्ठा i915_request *rq,
						 काष्ठा i915_active *active)
अणु
	काष्ठा dma_fence *fence;
	पूर्णांक err = 0;

	fence = i915_active_fence_get(&active->excl);
	अगर (fence) अणु
		err = i915_request_aरुको_dma_fence(rq, fence);
		dma_fence_put(fence);
	पूर्ण

	वापस err;
पूर्ण

#पूर्ण_अगर /* _I915_ACTIVE_H_ */
