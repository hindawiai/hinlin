<शैली गुरु>
/*
 * Copyright तऊ 2008-2018 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */

#अगर_अघोषित I915_REQUEST_H
#घोषणा I915_REQUEST_H

#समावेश <linux/dma-fence.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/irq_work.h>
#समावेश <linux/llist.h>
#समावेश <linux/lockdep.h>

#समावेश "gem/i915_gem_context_types.h"
#समावेश "gt/intel_context_types.h"
#समावेश "gt/intel_engine_types.h"
#समावेश "gt/intel_timeline_types.h"

#समावेश "i915_gem.h"
#समावेश "i915_scheduler.h"
#समावेश "i915_selftest.h"
#समावेश "i915_sw_fence.h"

#समावेश <uapi/drm/i915_drm.h>

काष्ठा drm_file;
काष्ठा drm_i915_gem_object;
काष्ठा drm_prपूर्णांकer;
काष्ठा i915_request;

काष्ठा i915_capture_list अणु
	काष्ठा i915_capture_list *next;
	काष्ठा i915_vma *vma;
पूर्ण;

#घोषणा RQ_TRACE(rq, fmt, ...) करो अणु					\
	स्थिर काष्ठा i915_request *rq__ = (rq);				\
	ENGINE_TRACE(rq__->engine, "fence %llx:%lld, current %d " fmt,	\
		     rq__->fence.context, rq__->fence.seqno,		\
		     hwsp_seqno(rq__), ##__VA_ARGS__);			\
पूर्ण जबतक (0)

क्रमागत अणु
	/*
	 * I915_FENCE_FLAG_ACTIVE - this request is currently submitted to HW.
	 *
	 * Set by __i915_request_submit() on handing over to HW, and cleared
	 * by __i915_request_unsubmit() अगर we preempt this request.
	 *
	 * Finally cleared क्रम consistency on retiring the request, when
	 * we know the HW is no दीर्घer running this request.
	 *
	 * See i915_request_is_active()
	 */
	I915_FENCE_FLAG_ACTIVE = DMA_FENCE_FLAG_USER_BITS,

	/*
	 * I915_FENCE_FLAG_PQUEUE - this request is पढ़ोy क्रम execution
	 *
	 * Using the scheduler, when a request is पढ़ोy क्रम execution it is put
	 * पूर्णांकo the priority queue, and हटाओd from that queue when transferred
	 * to the HW runlists. We want to track its membership within the
	 * priority queue so that we can easily check beक्रमe rescheduling.
	 *
	 * See i915_request_in_priority_queue()
	 */
	I915_FENCE_FLAG_PQUEUE,

	/*
	 * I915_FENCE_FLAG_HOLD - this request is currently on hold
	 *
	 * This request has been suspended, pending an ongoing investigation.
	 */
	I915_FENCE_FLAG_HOLD,

	/*
	 * I915_FENCE_FLAG_INITIAL_BREADCRUMB - this request has the initial
	 * bपढ़ोcrumb that marks the end of semaphore रुकोs and start of the
	 * user payload.
	 */
	I915_FENCE_FLAG_INITIAL_BREADCRUMB,

	/*
	 * I915_FENCE_FLAG_SIGNAL - this request is currently on संकेत_list
	 *
	 * Internal bookkeeping used by the bपढ़ोcrumb code to track when
	 * a request is on the various संकेत_list.
	 */
	I915_FENCE_FLAG_SIGNAL,

	/*
	 * I915_FENCE_FLAG_NOPREEMPT - this request should not be preempted
	 *
	 * The execution of some requests should not be पूर्णांकerrupted. This is
	 * a sensitive operation as it makes the request super important,
	 * blocking other higher priority work. Abuse of this flag will
	 * lead to quality of service issues.
	 */
	I915_FENCE_FLAG_NOPREEMPT,

	/*
	 * I915_FENCE_FLAG_SENTINEL - this request should be last in the queue
	 *
	 * A high priority sentinel request may be submitted to clear the
	 * submission queue. As it will be the only request in-flight, upon
	 * execution all other active requests will have been preempted and
	 * unsubmitted. This preemptive pulse is used to re-evaluate the
	 * in-flight requests, particularly in हालs where an active context
	 * is banned and those active requests need to be cancelled.
	 */
	I915_FENCE_FLAG_SENTINEL,

	/*
	 * I915_FENCE_FLAG_BOOST - upघड़ी the gpu क्रम this request
	 *
	 * Some requests are more important than others! In particular, a
	 * request that the user is रुकोing on is typically required क्रम
	 * पूर्णांकeractive latency, क्रम which we want to minimise by upघड़ीing
	 * the GPU. Here we track such boost requests on a per-request basis.
	 */
	I915_FENCE_FLAG_BOOST,
पूर्ण;

/**
 * Request queue काष्ठाure.
 *
 * The request queue allows us to note sequence numbers that have been emitted
 * and may be associated with active buffers to be retired.
 *
 * By keeping this list, we can aव्योम having to करो questionable sequence
 * number comparisons on buffer last_पढ़ो|ग_लिखो_seqno. It also allows an
 * emission समय to be associated with the request क्रम tracking how far ahead
 * of the GPU the submission is.
 *
 * When modअगरying this काष्ठाure be very aware that we perक्रमm a lockless
 * RCU lookup of it that may race against पुनः_स्मृतिation of the काष्ठा
 * from the slab मुक्तlist. We पूर्णांकentionally करो not zero the काष्ठाure on
 * allocation so that the lookup can use the dangling poपूर्णांकers (and is
 * cogniscent that those poपूर्णांकers may be wrong). Instead, everything that
 * needs to be initialised must be करोne so explicitly.
 *
 * The requests are reference counted.
 */
काष्ठा i915_request अणु
	काष्ठा dma_fence fence;
	spinlock_t lock;

	/**
	 * Context and ring buffer related to this request
	 * Contexts are refcounted, so when this request is associated with a
	 * context, we must increment the context's refcount, to guarantee that
	 * it persists जबतक any request is linked to it. Requests themselves
	 * are also refcounted, so the request will only be मुक्तd when the last
	 * reference to it is dismissed, and the code in
	 * i915_request_मुक्त() will then decrement the refcount on the
	 * context.
	 */
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा पूर्णांकel_context *context;
	काष्ठा पूर्णांकel_ring *ring;
	काष्ठा पूर्णांकel_समयline __rcu *समयline;

	काष्ठा list_head संकेत_link;
	काष्ठा llist_node संकेत_node;

	/*
	 * The rcu epoch of when this request was allocated. Used to judiciously
	 * apply backpressure on future allocations to ensure that under
	 * mempressure there is sufficient RCU ticks क्रम us to reclaim our
	 * RCU रक्षित sद_असल.
	 */
	अचिन्हित दीर्घ rcustate;

	/*
	 * We pin the समयline->mutex जबतक स्थिरructing the request to
	 * ensure that no caller accidentally drops it during स्थिरruction.
	 * The समयline->mutex must be held to ensure that only this caller
	 * can use the ring and manipulate the associated समयline during
	 * स्थिरruction.
	 */
	काष्ठा pin_cookie cookie;

	/*
	 * Fences क्रम the various phases in the request's lअगरeसमय.
	 *
	 * The submit fence is used to aरुको upon all of the request's
	 * dependencies. When it is संकेतed, the request is पढ़ोy to run.
	 * It is used by the driver to then queue the request क्रम execution.
	 */
	काष्ठा i915_sw_fence submit;
	जोड़ अणु
		रुको_queue_entry_t submitq;
		काष्ठा i915_sw_dma_fence_cb dmaq;
		काष्ठा i915_request_duration_cb अणु
			काष्ठा dma_fence_cb cb;
			kसमय_प्रकार emitted;
		पूर्ण duration;
	पूर्ण;
	काष्ठा llist_head execute_cb;
	काष्ठा i915_sw_fence semaphore;

	/*
	 * A list of everyone we रुको upon, and everyone who रुकोs upon us.
	 * Even though we will not be submitted to the hardware beक्रमe the
	 * submit fence is संकेतed (it रुकोs क्रम all बाह्यal events as well
	 * as our own requests), the scheduler still needs to know the
	 * dependency tree क्रम the lअगरeसमय of the request (from execbuf
	 * to retirement), i.e. bidirectional dependency inक्रमmation क्रम the
	 * request not tied to inभागidual fences.
	 */
	काष्ठा i915_sched_node sched;
	काष्ठा i915_dependency dep;
	पूर्णांकel_engine_mask_t execution_mask;

	/*
	 * A convenience poपूर्णांकer to the current bपढ़ोcrumb value stored in
	 * the HW status page (or our समयline's local equivalent). The full
	 * path would be rq->hw_context->ring->समयline->hwsp_seqno.
	 */
	स्थिर u32 *hwsp_seqno;

	/** Position in the ring of the start of the request */
	u32 head;

	/** Position in the ring of the start of the user packets */
	u32 infix;

	/**
	 * Position in the ring of the start of the postfix.
	 * This is required to calculate the maximum available ring space
	 * without overwriting the postfix.
	 */
	u32 postfix;

	/** Position in the ring of the end of the whole request */
	u32 tail;

	/** Position in the ring of the end of any workarounds after the tail */
	u32 wa_tail;

	/** Pपुनः_स्मृतिate space in the ring क्रम the emitting the request */
	u32 reserved_space;

	/** Batch buffer related to this request अगर any (used क्रम
	 * error state dump only).
	 */
	काष्ठा i915_vma *batch;
	/**
	 * Additional buffers requested by userspace to be captured upon
	 * a GPU hang. The vma/obj on this list are रक्षित by their
	 * active reference - all objects on this list must also be
	 * on the active_list (of their final request).
	 */
	काष्ठा i915_capture_list *capture_list;

	/** Time at which this request was emitted, in jअगरfies. */
	अचिन्हित दीर्घ emitted_jअगरfies;

	/** समयline->request entry क्रम this request */
	काष्ठा list_head link;

	/** Watchकरोg support fields. */
	काष्ठा i915_request_watchकरोg अणु
		काष्ठा llist_node link;
		काष्ठा hrसमयr समयr;
	पूर्ण watchकरोg;

	I915_SELFTEST_DECLARE(काष्ठा अणु
		काष्ठा list_head link;
		अचिन्हित दीर्घ delay;
	पूर्ण mock;)
पूर्ण;

#घोषणा I915_FENCE_GFP (GFP_KERNEL | __GFP_RETRY_MAYFAIL | __GFP_NOWARN)

बाह्य स्थिर काष्ठा dma_fence_ops i915_fence_ops;

अटल अंतरभूत bool dma_fence_is_i915(स्थिर काष्ठा dma_fence *fence)
अणु
	वापस fence->ops == &i915_fence_ops;
पूर्ण

काष्ठा kmem_cache *i915_request_slab_cache(व्योम);

काष्ठा i915_request * __must_check
__i915_request_create(काष्ठा पूर्णांकel_context *ce, gfp_t gfp);
काष्ठा i915_request * __must_check
i915_request_create(काष्ठा पूर्णांकel_context *ce);

व्योम __i915_request_skip(काष्ठा i915_request *rq);
bool i915_request_set_error_once(काष्ठा i915_request *rq, पूर्णांक error);
काष्ठा i915_request *i915_request_mark_eio(काष्ठा i915_request *rq);

काष्ठा i915_request *__i915_request_commit(काष्ठा i915_request *request);
व्योम __i915_request_queue(काष्ठा i915_request *rq,
			  स्थिर काष्ठा i915_sched_attr *attr);
व्योम __i915_request_queue_bh(काष्ठा i915_request *rq);

bool i915_request_retire(काष्ठा i915_request *rq);
व्योम i915_request_retire_upto(काष्ठा i915_request *rq);

अटल अंतरभूत काष्ठा i915_request *
to_request(काष्ठा dma_fence *fence)
अणु
	/* We assume that शून्य fence/request are पूर्णांकeroperable */
	BUILD_BUG_ON(दुरत्व(काष्ठा i915_request, fence) != 0);
	GEM_BUG_ON(fence && !dma_fence_is_i915(fence));
	वापस container_of(fence, काष्ठा i915_request, fence);
पूर्ण

अटल अंतरभूत काष्ठा i915_request *
i915_request_get(काष्ठा i915_request *rq)
अणु
	वापस to_request(dma_fence_get(&rq->fence));
पूर्ण

अटल अंतरभूत काष्ठा i915_request *
i915_request_get_rcu(काष्ठा i915_request *rq)
अणु
	वापस to_request(dma_fence_get_rcu(&rq->fence));
पूर्ण

अटल अंतरभूत व्योम
i915_request_put(काष्ठा i915_request *rq)
अणु
	dma_fence_put(&rq->fence);
पूर्ण

पूर्णांक i915_request_aरुको_object(काष्ठा i915_request *to,
			      काष्ठा drm_i915_gem_object *obj,
			      bool ग_लिखो);
पूर्णांक i915_request_aरुको_dma_fence(काष्ठा i915_request *rq,
				 काष्ठा dma_fence *fence);
पूर्णांक i915_request_aरुको_execution(काष्ठा i915_request *rq,
				 काष्ठा dma_fence *fence,
				 व्योम (*hook)(काष्ठा i915_request *rq,
					      काष्ठा dma_fence *संकेत));

व्योम i915_request_add(काष्ठा i915_request *rq);

bool __i915_request_submit(काष्ठा i915_request *request);
व्योम i915_request_submit(काष्ठा i915_request *request);

व्योम __i915_request_unsubmit(काष्ठा i915_request *request);
व्योम i915_request_unsubmit(काष्ठा i915_request *request);

व्योम i915_request_cancel(काष्ठा i915_request *rq, पूर्णांक error);

दीर्घ i915_request_रुको(काष्ठा i915_request *rq,
		       अचिन्हित पूर्णांक flags,
		       दीर्घ समयout)
	__attribute__((nonnull(1)));
#घोषणा I915_WAIT_INTERRUPTIBLE	BIT(0)
#घोषणा I915_WAIT_PRIORITY	BIT(1) /* small priority bump क्रम the request */
#घोषणा I915_WAIT_ALL		BIT(2) /* used by i915_gem_object_रुको() */

व्योम i915_request_show(काष्ठा drm_prपूर्णांकer *m,
		       स्थिर काष्ठा i915_request *rq,
		       स्थिर अक्षर *prefix,
		       पूर्णांक indent);

अटल अंतरभूत bool i915_request_संकेतed(स्थिर काष्ठा i915_request *rq)
अणु
	/* The request may live दीर्घer than its HWSP, so check flags first! */
	वापस test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &rq->fence.flags);
पूर्ण

अटल अंतरभूत bool i915_request_is_active(स्थिर काष्ठा i915_request *rq)
अणु
	वापस test_bit(I915_FENCE_FLAG_ACTIVE, &rq->fence.flags);
पूर्ण

अटल अंतरभूत bool i915_request_in_priority_queue(स्थिर काष्ठा i915_request *rq)
अणु
	वापस test_bit(I915_FENCE_FLAG_PQUEUE, &rq->fence.flags);
पूर्ण

अटल अंतरभूत bool
i915_request_has_initial_bपढ़ोcrumb(स्थिर काष्ठा i915_request *rq)
अणु
	वापस test_bit(I915_FENCE_FLAG_INITIAL_BREADCRUMB, &rq->fence.flags);
पूर्ण

/**
 * Returns true अगर seq1 is later than seq2.
 */
अटल अंतरभूत bool i915_seqno_passed(u32 seq1, u32 seq2)
अणु
	वापस (s32)(seq1 - seq2) >= 0;
पूर्ण

अटल अंतरभूत u32 __hwsp_seqno(स्थिर काष्ठा i915_request *rq)
अणु
	स्थिर u32 *hwsp = READ_ONCE(rq->hwsp_seqno);

	वापस READ_ONCE(*hwsp);
पूर्ण

/**
 * hwsp_seqno - the current bपढ़ोcrumb value in the HW status page
 * @rq: the request, to chase the relevant HW status page
 *
 * The emphasis in naming here is that hwsp_seqno() is not a property of the
 * request, but an indication of the current HW state (associated with this
 * request). Its value will change as the GPU executes more requests.
 *
 * Returns the current bपढ़ोcrumb value in the associated HW status page (or
 * the local समयline's equivalent) क्रम this request. The request itself
 * has the associated bपढ़ोcrumb value of rq->fence.seqno, when the HW
 * status page has that bपढ़ोcrumb or later, this request is complete.
 */
अटल अंतरभूत u32 hwsp_seqno(स्थिर काष्ठा i915_request *rq)
अणु
	u32 seqno;

	rcu_पढ़ो_lock(); /* the HWSP may be मुक्तd at runसमय */
	seqno = __hwsp_seqno(rq);
	rcu_पढ़ो_unlock();

	वापस seqno;
पूर्ण

अटल अंतरभूत bool __i915_request_has_started(स्थिर काष्ठा i915_request *rq)
अणु
	वापस i915_seqno_passed(__hwsp_seqno(rq), rq->fence.seqno - 1);
पूर्ण

/**
 * i915_request_started - check अगर the request has begun being executed
 * @rq: the request
 *
 * If the समयline is not using initial bपढ़ोcrumbs, a request is
 * considered started अगर the previous request on its समयline (i.e.
 * context) has been संकेतed.
 *
 * If the समयline is using semaphores, it will also be emitting an
 * "initial breadcrumb" after the semaphores are complete and just beक्रमe
 * it began executing the user payload. A request can thereक्रमe be active
 * on the HW and not yet started as it is still busyरुकोing on its
 * dependencies (via HW semaphores).
 *
 * If the request has started, its dependencies will have been संकेतed
 * (either by fences or by semaphores) and it will have begun processing
 * the user payload.
 *
 * However, even अगर a request has started, it may have been preempted and
 * so no दीर्घer active, or it may have alपढ़ोy completed.
 *
 * See also i915_request_is_active().
 *
 * Returns true अगर the request has begun executing the user payload, or
 * has completed:
 */
अटल अंतरभूत bool i915_request_started(स्थिर काष्ठा i915_request *rq)
अणु
	bool result;

	अगर (i915_request_संकेतed(rq))
		वापस true;

	result = true;
	rcu_पढ़ो_lock(); /* the HWSP may be मुक्तd at runसमय */
	अगर (likely(!i915_request_संकेतed(rq)))
		/* Remember: started but may have since been preempted! */
		result = __i915_request_has_started(rq);
	rcu_पढ़ो_unlock();

	वापस result;
पूर्ण

/**
 * i915_request_is_running - check अगर the request may actually be executing
 * @rq: the request
 *
 * Returns true अगर the request is currently submitted to hardware, has passed
 * its start poपूर्णांक (i.e. the context is setup and not busyरुकोing). Note that
 * it may no दीर्घer be running by the समय the function वापसs!
 */
अटल अंतरभूत bool i915_request_is_running(स्थिर काष्ठा i915_request *rq)
अणु
	bool result;

	अगर (!i915_request_is_active(rq))
		वापस false;

	rcu_पढ़ो_lock();
	result = __i915_request_has_started(rq) && i915_request_is_active(rq);
	rcu_पढ़ो_unlock();

	वापस result;
पूर्ण

/**
 * i915_request_is_पढ़ोy - check अगर the request is पढ़ोy क्रम execution
 * @rq: the request
 *
 * Upon स्थिरruction, the request is inकाष्ठाed to रुको upon various
 * संकेतs beक्रमe it is पढ़ोy to be executed by the HW. That is, we करो
 * not want to start execution and पढ़ो data beक्रमe it is written. In practice,
 * this is controlled with a mixture of पूर्णांकerrupts and semaphores. Once
 * the submit fence is completed, the backend scheduler will place the
 * request पूर्णांकo its queue and from there submit it क्रम execution. So we
 * can detect when a request is eligible क्रम execution (and is under control
 * of the scheduler) by querying where it is in any of the scheduler's lists.
 *
 * Returns true अगर the request is पढ़ोy क्रम execution (it may be inflight),
 * false otherwise.
 */
अटल अंतरभूत bool i915_request_is_पढ़ोy(स्थिर काष्ठा i915_request *rq)
अणु
	वापस !list_empty(&rq->sched.link);
पूर्ण

अटल अंतरभूत bool __i915_request_is_complete(स्थिर काष्ठा i915_request *rq)
अणु
	वापस i915_seqno_passed(__hwsp_seqno(rq), rq->fence.seqno);
पूर्ण

अटल अंतरभूत bool i915_request_completed(स्थिर काष्ठा i915_request *rq)
अणु
	bool result;

	अगर (i915_request_संकेतed(rq))
		वापस true;

	result = true;
	rcu_पढ़ो_lock(); /* the HWSP may be मुक्तd at runसमय */
	अगर (likely(!i915_request_संकेतed(rq)))
		result = __i915_request_is_complete(rq);
	rcu_पढ़ो_unlock();

	वापस result;
पूर्ण

अटल अंतरभूत व्योम i915_request_mark_complete(काष्ठा i915_request *rq)
अणु
	WRITE_ONCE(rq->hwsp_seqno, /* decouple from HWSP */
		   (u32 *)&rq->fence.seqno);
पूर्ण

अटल अंतरभूत bool i915_request_has_रुकोboost(स्थिर काष्ठा i915_request *rq)
अणु
	वापस test_bit(I915_FENCE_FLAG_BOOST, &rq->fence.flags);
पूर्ण

अटल अंतरभूत bool i915_request_has_nopreempt(स्थिर काष्ठा i915_request *rq)
अणु
	/* Preemption should only be disabled very rarely */
	वापस unlikely(test_bit(I915_FENCE_FLAG_NOPREEMPT, &rq->fence.flags));
पूर्ण

अटल अंतरभूत bool i915_request_has_sentinel(स्थिर काष्ठा i915_request *rq)
अणु
	वापस unlikely(test_bit(I915_FENCE_FLAG_SENTINEL, &rq->fence.flags));
पूर्ण

अटल अंतरभूत bool i915_request_on_hold(स्थिर काष्ठा i915_request *rq)
अणु
	वापस unlikely(test_bit(I915_FENCE_FLAG_HOLD, &rq->fence.flags));
पूर्ण

अटल अंतरभूत व्योम i915_request_set_hold(काष्ठा i915_request *rq)
अणु
	set_bit(I915_FENCE_FLAG_HOLD, &rq->fence.flags);
पूर्ण

अटल अंतरभूत व्योम i915_request_clear_hold(काष्ठा i915_request *rq)
अणु
	clear_bit(I915_FENCE_FLAG_HOLD, &rq->fence.flags);
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_समयline *
i915_request_समयline(स्थिर काष्ठा i915_request *rq)
अणु
	/* Valid only जबतक the request is being स्थिरructed (or retired). */
	वापस rcu_dereference_रक्षित(rq->समयline,
					 lockdep_is_held(&rcu_access_poपूर्णांकer(rq->समयline)->mutex));
पूर्ण

अटल अंतरभूत काष्ठा i915_gem_context *
i915_request_gem_context(स्थिर काष्ठा i915_request *rq)
अणु
	/* Valid only जबतक the request is being स्थिरructed (or retired). */
	वापस rcu_dereference_रक्षित(rq->context->gem_context, true);
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_समयline *
i915_request_active_समयline(स्थिर काष्ठा i915_request *rq)
अणु
	/*
	 * When in use during submission, we are रक्षित by a guarantee that
	 * the context/समयline is pinned and must reमुख्य pinned until after
	 * this submission.
	 */
	वापस rcu_dereference_रक्षित(rq->समयline,
					 lockdep_is_held(&rq->engine->active.lock));
पूर्ण

अटल अंतरभूत u32
i915_request_active_seqno(स्थिर काष्ठा i915_request *rq)
अणु
	u32 hwsp_phys_base =
		page_mask_bits(i915_request_active_समयline(rq)->hwsp_offset);
	u32 hwsp_relative_offset = offset_in_page(rq->hwsp_seqno);

	/*
	 * Because of wraparound, we cannot simply take tl->hwsp_offset,
	 * but instead use the fact that the relative क्रम vaddr is the
	 * offset as क्रम hwsp_offset. Take the top bits from tl->hwsp_offset
	 * and combine them with the relative offset in rq->hwsp_seqno.
	 *
	 * As rw->hwsp_seqno is rewritten when संकेतed, this only works
	 * when the request isn't संकेतed yet, but at that poपूर्णांक you
	 * no दीर्घer need the offset.
	 */

	वापस hwsp_phys_base + hwsp_relative_offset;
पूर्ण

bool
i915_request_active_engine(काष्ठा i915_request *rq,
			   काष्ठा पूर्णांकel_engine_cs **active);

#पूर्ण_अगर /* I915_REQUEST_H */
