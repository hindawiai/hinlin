<शैली गुरु>
/*
 * Copyright तऊ 2008-2015 Intel Corporation
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

#समावेश <linux/dma-fence-array.h>
#समावेश <linux/dma-fence-chain.h>
#समावेश <linux/irq_work.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/sched/संकेत.स>

#समावेश "gem/i915_gem_context.h"
#समावेश "gt/intel_breadcrumbs.h"
#समावेश "gt/intel_context.h"
#समावेश "gt/intel_engine.h"
#समावेश "gt/intel_engine_heartbeat.h"
#समावेश "gt/intel_gpu_commands.h"
#समावेश "gt/intel_reset.h"
#समावेश "gt/intel_ring.h"
#समावेश "gt/intel_rps.h"

#समावेश "i915_active.h"
#समावेश "i915_drv.h"
#समावेश "i915_globals.h"
#समावेश "i915_trace.h"
#समावेश "intel_pm.h"

काष्ठा execute_cb अणु
	काष्ठा irq_work work;
	काष्ठा i915_sw_fence *fence;
	व्योम (*hook)(काष्ठा i915_request *rq, काष्ठा dma_fence *संकेत);
	काष्ठा i915_request *संकेत;
पूर्ण;

अटल काष्ठा i915_global_request अणु
	काष्ठा i915_global base;
	काष्ठा kmem_cache *slab_requests;
	काष्ठा kmem_cache *slab_execute_cbs;
पूर्ण global;

अटल स्थिर अक्षर *i915_fence_get_driver_name(काष्ठा dma_fence *fence)
अणु
	वापस dev_name(to_request(fence)->engine->i915->drm.dev);
पूर्ण

अटल स्थिर अक्षर *i915_fence_get_समयline_name(काष्ठा dma_fence *fence)
अणु
	स्थिर काष्ठा i915_gem_context *ctx;

	/*
	 * The समयline काष्ठा (as part of the ppgtt underneath a context)
	 * may be मुक्तd when the request is no दीर्घer in use by the GPU.
	 * We could extend the lअगरe of a context to beyond that of all
	 * fences, possibly keeping the hw resource around indefinitely,
	 * or we just give them a false name. Since
	 * dma_fence_ops.get_समयline_name is a debug feature, the occasional
	 * lie seems justअगरiable.
	 */
	अगर (test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &fence->flags))
		वापस "signaled";

	ctx = i915_request_gem_context(to_request(fence));
	अगर (!ctx)
		वापस "[" DRIVER_NAME "]";

	वापस ctx->name;
पूर्ण

अटल bool i915_fence_संकेतed(काष्ठा dma_fence *fence)
अणु
	वापस i915_request_completed(to_request(fence));
पूर्ण

अटल bool i915_fence_enable_संकेतing(काष्ठा dma_fence *fence)
अणु
	वापस i915_request_enable_bपढ़ोcrumb(to_request(fence));
पूर्ण

अटल चिन्हित दीर्घ i915_fence_रुको(काष्ठा dma_fence *fence,
				   bool पूर्णांकerruptible,
				   चिन्हित दीर्घ समयout)
अणु
	वापस i915_request_रुको(to_request(fence),
				 पूर्णांकerruptible | I915_WAIT_PRIORITY,
				 समयout);
पूर्ण

काष्ठा kmem_cache *i915_request_slab_cache(व्योम)
अणु
	वापस global.slab_requests;
पूर्ण

अटल व्योम i915_fence_release(काष्ठा dma_fence *fence)
अणु
	काष्ठा i915_request *rq = to_request(fence);

	/*
	 * The request is put onto a RCU मुक्तlist (i.e. the address
	 * is immediately reused), mark the fences as being मुक्तd now.
	 * Otherwise the debugobjects क्रम the fences are only marked as
	 * मुक्तd when the slab cache itself is मुक्तd, and so we would get
	 * caught trying to reuse dead objects.
	 */
	i915_sw_fence_fini(&rq->submit);
	i915_sw_fence_fini(&rq->semaphore);

	/*
	 * Keep one request on each engine क्रम reserved use under mempressure
	 *
	 * We करो not hold a reference to the engine here and so have to be
	 * very careful in what rq->engine we poke. The भव engine is
	 * referenced via the rq->context and we released that ref during
	 * i915_request_retire(), ergo we must not dereference a भव
	 * engine here. Not that we would want to, as the only consumer of
	 * the reserved engine->request_pool is the घातer management parking,
	 * which must-not-fail, and that is only run on the physical engines.
	 *
	 * Since the request must have been executed to be have completed,
	 * we know that it will have been processed by the HW and will
	 * not be unsubmitted again, so rq->engine and rq->execution_mask
	 * at this poपूर्णांक is stable. rq->execution_mask will be a single
	 * bit अगर the last and _only_ engine it could execution on was a
	 * physical engine, अगर it's multiple bits then it started on and
	 * could still be on a भव engine. Thus अगर the mask is not a
	 * घातer-of-two we assume that rq->engine may still be a भव
	 * engine and so a dangling invalid poपूर्णांकer that we cannot dereference
	 *
	 * For example, consider the flow of a bonded request through a भव
	 * engine. The request is created with a wide engine mask (all engines
	 * that we might execute on). On processing the bond, the request mask
	 * is reduced to one or more engines. If the request is subsequently
	 * bound to a single engine, it will then be स्थिरrained to only
	 * execute on that engine and never वापसed to the भव engine
	 * after बारlicing away, see __unwind_incomplete_requests(). Thus we
	 * know that अगर the rq->execution_mask is a single bit, rq->engine
	 * can be a physical engine with the exact corresponding mask.
	 */
	अगर (is_घातer_of_2(rq->execution_mask) &&
	    !cmpxchg(&rq->engine->request_pool, शून्य, rq))
		वापस;

	kmem_cache_मुक्त(global.slab_requests, rq);
पूर्ण

स्थिर काष्ठा dma_fence_ops i915_fence_ops = अणु
	.get_driver_name = i915_fence_get_driver_name,
	.get_समयline_name = i915_fence_get_समयline_name,
	.enable_संकेतing = i915_fence_enable_संकेतing,
	.संकेतed = i915_fence_संकेतed,
	.रुको = i915_fence_रुको,
	.release = i915_fence_release,
पूर्ण;

अटल व्योम irq_execute_cb(काष्ठा irq_work *wrk)
अणु
	काष्ठा execute_cb *cb = container_of(wrk, typeof(*cb), work);

	i915_sw_fence_complete(cb->fence);
	kmem_cache_मुक्त(global.slab_execute_cbs, cb);
पूर्ण

अटल व्योम irq_execute_cb_hook(काष्ठा irq_work *wrk)
अणु
	काष्ठा execute_cb *cb = container_of(wrk, typeof(*cb), work);

	cb->hook(container_of(cb->fence, काष्ठा i915_request, submit),
		 &cb->संकेत->fence);
	i915_request_put(cb->संकेत);

	irq_execute_cb(wrk);
पूर्ण

अटल __always_अंतरभूत व्योम
__notअगरy_execute_cb(काष्ठा i915_request *rq, bool (*fn)(काष्ठा irq_work *wrk))
अणु
	काष्ठा execute_cb *cb, *cn;

	अगर (llist_empty(&rq->execute_cb))
		वापस;

	llist_क्रम_each_entry_safe(cb, cn,
				  llist_del_all(&rq->execute_cb),
				  work.node.llist)
		fn(&cb->work);
पूर्ण

अटल व्योम __notअगरy_execute_cb_irq(काष्ठा i915_request *rq)
अणु
	__notअगरy_execute_cb(rq, irq_work_queue);
पूर्ण

अटल bool irq_work_imm(काष्ठा irq_work *wrk)
अणु
	wrk->func(wrk);
	वापस false;
पूर्ण

अटल व्योम __notअगरy_execute_cb_imm(काष्ठा i915_request *rq)
अणु
	__notअगरy_execute_cb(rq, irq_work_imm);
पूर्ण

अटल व्योम मुक्त_capture_list(काष्ठा i915_request *request)
अणु
	काष्ठा i915_capture_list *capture;

	capture = fetch_and_zero(&request->capture_list);
	जबतक (capture) अणु
		काष्ठा i915_capture_list *next = capture->next;

		kमुक्त(capture);
		capture = next;
	पूर्ण
पूर्ण

अटल व्योम __i915_request_fill(काष्ठा i915_request *rq, u8 val)
अणु
	व्योम *vaddr = rq->ring->vaddr;
	u32 head;

	head = rq->infix;
	अगर (rq->postfix < head) अणु
		स_रखो(vaddr + head, val, rq->ring->size - head);
		head = 0;
	पूर्ण
	स_रखो(vaddr + head, val, rq->postfix - head);
पूर्ण

/**
 * i915_request_active_engine
 * @rq: request to inspect
 * @active: poपूर्णांकer in which to वापस the active engine
 *
 * Fills the currently active engine to the @active poपूर्णांकer अगर the request
 * is active and still not completed.
 *
 * Returns true अगर request was active or false otherwise.
 */
bool
i915_request_active_engine(काष्ठा i915_request *rq,
			   काष्ठा पूर्णांकel_engine_cs **active)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine, *locked;
	bool ret = false;

	/*
	 * Serialise with __i915_request_submit() so that it sees
	 * is-banned?, or we know the request is alपढ़ोy inflight.
	 *
	 * Note that rq->engine is unstable, and so we द्विगुन
	 * check that we have acquired the lock on the final engine.
	 */
	locked = READ_ONCE(rq->engine);
	spin_lock_irq(&locked->active.lock);
	जबतक (unlikely(locked != (engine = READ_ONCE(rq->engine)))) अणु
		spin_unlock(&locked->active.lock);
		locked = engine;
		spin_lock(&locked->active.lock);
	पूर्ण

	अगर (i915_request_is_active(rq)) अणु
		अगर (!__i915_request_is_complete(rq))
			*active = locked;
		ret = true;
	पूर्ण

	spin_unlock_irq(&locked->active.lock);

	वापस ret;
पूर्ण


अटल व्योम हटाओ_from_engine(काष्ठा i915_request *rq)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine, *locked;

	/*
	 * Virtual engines complicate acquiring the engine समयline lock,
	 * as their rq->engine poपूर्णांकer is not stable until under that
	 * engine lock. The simple ploy we use is to take the lock then
	 * check that the rq still beदीर्घs to the newly locked engine.
	 */
	locked = READ_ONCE(rq->engine);
	spin_lock_irq(&locked->active.lock);
	जबतक (unlikely(locked != (engine = READ_ONCE(rq->engine)))) अणु
		spin_unlock(&locked->active.lock);
		spin_lock(&engine->active.lock);
		locked = engine;
	पूर्ण
	list_del_init(&rq->sched.link);

	clear_bit(I915_FENCE_FLAG_PQUEUE, &rq->fence.flags);
	clear_bit(I915_FENCE_FLAG_HOLD, &rq->fence.flags);

	/* Prevent further __aरुको_execution() रेजिस्टरing a cb, then flush */
	set_bit(I915_FENCE_FLAG_ACTIVE, &rq->fence.flags);

	spin_unlock_irq(&locked->active.lock);

	__notअगरy_execute_cb_imm(rq);
पूर्ण

अटल व्योम __rq_init_watchकरोg(काष्ठा i915_request *rq)
अणु
	rq->watchकरोg.समयr.function = शून्य;
पूर्ण

अटल क्रमागत hrसमयr_restart __rq_watchकरोg_expired(काष्ठा hrसमयr *hrसमयr)
अणु
	काष्ठा i915_request *rq =
		container_of(hrसमयr, काष्ठा i915_request, watchकरोg.समयr);
	काष्ठा पूर्णांकel_gt *gt = rq->engine->gt;

	अगर (!i915_request_completed(rq)) अणु
		अगर (llist_add(&rq->watchकरोg.link, &gt->watchकरोg.list))
			schedule_work(&gt->watchकरोg.work);
	पूर्ण अन्यथा अणु
		i915_request_put(rq);
	पूर्ण

	वापस HRTIMER_NORESTART;
पूर्ण

अटल व्योम __rq_arm_watchकरोg(काष्ठा i915_request *rq)
अणु
	काष्ठा i915_request_watchकरोg *wdg = &rq->watchकरोg;
	काष्ठा पूर्णांकel_context *ce = rq->context;

	अगर (!ce->watchकरोg.समयout_us)
		वापस;

	i915_request_get(rq);

	hrसमयr_init(&wdg->समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	wdg->समयr.function = __rq_watchकरोg_expired;
	hrसमयr_start_range_ns(&wdg->समयr,
			       ns_to_kसमय(ce->watchकरोg.समयout_us *
					   NSEC_PER_USEC),
			       NSEC_PER_MSEC,
			       HRTIMER_MODE_REL);
पूर्ण

अटल व्योम __rq_cancel_watchकरोg(काष्ठा i915_request *rq)
अणु
	काष्ठा i915_request_watchकरोg *wdg = &rq->watchकरोg;

	अगर (wdg->समयr.function && hrसमयr_try_to_cancel(&wdg->समयr) > 0)
		i915_request_put(rq);
पूर्ण

bool i915_request_retire(काष्ठा i915_request *rq)
अणु
	अगर (!__i915_request_is_complete(rq))
		वापस false;

	RQ_TRACE(rq, "\n");

	GEM_BUG_ON(!i915_sw_fence_संकेतed(&rq->submit));
	trace_i915_request_retire(rq);
	i915_request_mark_complete(rq);

	__rq_cancel_watchकरोg(rq);

	/*
	 * We know the GPU must have पढ़ो the request to have
	 * sent us the seqno + पूर्णांकerrupt, so use the position
	 * of tail of the request to update the last known position
	 * of the GPU head.
	 *
	 * Note this requires that we are always called in request
	 * completion order.
	 */
	GEM_BUG_ON(!list_is_first(&rq->link,
				  &i915_request_समयline(rq)->requests));
	अगर (IS_ENABLED(CONFIG_DRM_I915_DEBUG_GEM))
		/* Poison beक्रमe we release our space in the ring */
		__i915_request_fill(rq, POISON_FREE);
	rq->ring->head = rq->postfix;

	अगर (!i915_request_संकेतed(rq)) अणु
		spin_lock_irq(&rq->lock);
		dma_fence_संकेत_locked(&rq->fence);
		spin_unlock_irq(&rq->lock);
	पूर्ण

	अगर (test_and_set_bit(I915_FENCE_FLAG_BOOST, &rq->fence.flags))
		atomic_dec(&rq->engine->gt->rps.num_रुकोers);

	/*
	 * We only loosely track inflight requests across preemption,
	 * and so we may find ourselves attempting to retire a _completed_
	 * request that we have हटाओd from the HW and put back on a run
	 * queue.
	 *
	 * As we set I915_FENCE_FLAG_ACTIVE on the request, this should be
	 * after removing the bपढ़ोcrumb and संकेतing it, so that we करो not
	 * inadvertently attach the bपढ़ोcrumb to a completed request.
	 */
	अगर (!list_empty(&rq->sched.link))
		हटाओ_from_engine(rq);
	GEM_BUG_ON(!llist_empty(&rq->execute_cb));

	__list_del_entry(&rq->link); /* poison neither prev/next (RCU walks) */

	पूर्णांकel_context_निकास(rq->context);
	पूर्णांकel_context_unpin(rq->context);

	मुक्त_capture_list(rq);
	i915_sched_node_fini(&rq->sched);
	i915_request_put(rq);

	वापस true;
पूर्ण

व्योम i915_request_retire_upto(काष्ठा i915_request *rq)
अणु
	काष्ठा पूर्णांकel_समयline * स्थिर tl = i915_request_समयline(rq);
	काष्ठा i915_request *पंचांगp;

	RQ_TRACE(rq, "\n");
	GEM_BUG_ON(!__i915_request_is_complete(rq));

	करो अणु
		पंचांगp = list_first_entry(&tl->requests, typeof(*पंचांगp), link);
	पूर्ण जबतक (i915_request_retire(पंचांगp) && पंचांगp != rq);
पूर्ण

अटल काष्ठा i915_request * स्थिर *
__engine_active(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	वापस READ_ONCE(engine->execlists.active);
पूर्ण

अटल bool __request_in_flight(स्थिर काष्ठा i915_request *संकेत)
अणु
	काष्ठा i915_request * स्थिर *port, *rq;
	bool inflight = false;

	अगर (!i915_request_is_पढ़ोy(संकेत))
		वापस false;

	/*
	 * Even अगर we have unwound the request, it may still be on
	 * the GPU (preempt-to-busy). If that request is inside an
	 * unpreemptible critical section, it will not be हटाओd. Some
	 * GPU functions may even be stuck रुकोing क्रम the paired request
	 * (__aरुको_execution) to be submitted and cannot be preempted
	 * until the bond is executing.
	 *
	 * As we know that there are always preemption poपूर्णांकs between
	 * requests, we know that only the currently executing request
	 * may be still active even though we have cleared the flag.
	 * However, we can't rely on our tracking of ELSP[0] to know
	 * which request is currently active and so maybe stuck, as
	 * the tracking maybe an event behind. Instead assume that
	 * अगर the context is still inflight, then it is still active
	 * even अगर the active flag has been cleared.
	 *
	 * To further complicate matters, अगर there a pending promotion, the HW
	 * may either perक्रमm a context चयन to the second inflight execlists,
	 * or it may चयन to the pending set of execlists. In the हाल of the
	 * latter, it may send the ACK and we process the event copying the
	 * pending[] over top of inflight[], _overwriting_ our *active. Since
	 * this implies the HW is arbitrating and not struck in *active, we करो
	 * not worry about complete accuracy, but we करो require no पढ़ो/ग_लिखो
	 * tearing of the poपूर्णांकer [the पढ़ो of the poपूर्णांकer must be valid, even
	 * as the array is being overwritten, क्रम which we require the ग_लिखोs
	 * to aव्योम tearing.]
	 *
	 * Note that the पढ़ो of *execlists->active may race with the promotion
	 * of execlists->pending[] to execlists->inflight[], overwritting
	 * the value at *execlists->active. This is fine. The promotion implies
	 * that we received an ACK from the HW, and so the context is not
	 * stuck -- अगर we करो not see ourselves in *active, the inflight status
	 * is valid. If instead we see ourselves being copied पूर्णांकo *active,
	 * we are inflight and may संकेत the callback.
	 */
	अगर (!पूर्णांकel_context_inflight(संकेत->context))
		वापस false;

	rcu_पढ़ो_lock();
	क्रम (port = __engine_active(संकेत->engine);
	     (rq = READ_ONCE(*port)); /* may race with promotion of pending[] */
	     port++) अणु
		अगर (rq->context == संकेत->context) अणु
			inflight = i915_seqno_passed(rq->fence.seqno,
						     संकेत->fence.seqno);
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस inflight;
पूर्ण

अटल पूर्णांक
__aरुको_execution(काष्ठा i915_request *rq,
		  काष्ठा i915_request *संकेत,
		  व्योम (*hook)(काष्ठा i915_request *rq,
			       काष्ठा dma_fence *संकेत),
		  gfp_t gfp)
अणु
	काष्ठा execute_cb *cb;

	अगर (i915_request_is_active(संकेत)) अणु
		अगर (hook)
			hook(rq, &संकेत->fence);
		वापस 0;
	पूर्ण

	cb = kmem_cache_alloc(global.slab_execute_cbs, gfp);
	अगर (!cb)
		वापस -ENOMEM;

	cb->fence = &rq->submit;
	i915_sw_fence_aरुको(cb->fence);
	init_irq_work(&cb->work, irq_execute_cb);

	अगर (hook) अणु
		cb->hook = hook;
		cb->संकेत = i915_request_get(संकेत);
		cb->work.func = irq_execute_cb_hook;
	पूर्ण

	/*
	 * Register the callback first, then see अगर the संकेतer is alपढ़ोy
	 * active. This ensures that अगर we race with the
	 * __notअगरy_execute_cb from i915_request_submit() and we are not
	 * included in that list, we get a second bite of the cherry and
	 * execute it ourselves. After this poपूर्णांक, a future
	 * i915_request_submit() will notअगरy us.
	 *
	 * In i915_request_retire() we set the ACTIVE bit on a completed
	 * request (then flush the execute_cb). So by रेजिस्टरing the
	 * callback first, then checking the ACTIVE bit, we serialise with
	 * the completed/retired request.
	 */
	अगर (llist_add(&cb->work.node.llist, &संकेत->execute_cb)) अणु
		अगर (i915_request_is_active(संकेत) ||
		    __request_in_flight(संकेत))
			__notअगरy_execute_cb_imm(संकेत);
	पूर्ण

	वापस 0;
पूर्ण

अटल bool fatal_error(पूर्णांक error)
अणु
	चयन (error) अणु
	हाल 0: /* not an error! */
	हाल -EAGAIN: /* innocent victim of a GT reset (__i915_request_reset) */
	हाल -ETIMEDOUT: /* रुकोing क्रम Goकरोt (समयr_i915_sw_fence_wake) */
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

व्योम __i915_request_skip(काष्ठा i915_request *rq)
अणु
	GEM_BUG_ON(!fatal_error(rq->fence.error));

	अगर (rq->infix == rq->postfix)
		वापस;

	RQ_TRACE(rq, "error: %d\n", rq->fence.error);

	/*
	 * As this request likely depends on state from the lost
	 * context, clear out all the user operations leaving the
	 * bपढ़ोcrumb at the end (so we get the fence notअगरications).
	 */
	__i915_request_fill(rq, 0);
	rq->infix = rq->postfix;
पूर्ण

bool i915_request_set_error_once(काष्ठा i915_request *rq, पूर्णांक error)
अणु
	पूर्णांक old;

	GEM_BUG_ON(!IS_ERR_VALUE((दीर्घ)error));

	अगर (i915_request_संकेतed(rq))
		वापस false;

	old = READ_ONCE(rq->fence.error);
	करो अणु
		अगर (fatal_error(old))
			वापस false;
	पूर्ण जबतक (!try_cmpxchg(&rq->fence.error, &old, error));

	वापस true;
पूर्ण

काष्ठा i915_request *i915_request_mark_eio(काष्ठा i915_request *rq)
अणु
	अगर (__i915_request_is_complete(rq))
		वापस शून्य;

	GEM_BUG_ON(i915_request_संकेतed(rq));

	/* As soon as the request is completed, it may be retired */
	rq = i915_request_get(rq);

	i915_request_set_error_once(rq, -EIO);
	i915_request_mark_complete(rq);

	वापस rq;
पूर्ण

bool __i915_request_submit(काष्ठा i915_request *request)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = request->engine;
	bool result = false;

	RQ_TRACE(request, "\n");

	GEM_BUG_ON(!irqs_disabled());
	lockdep_निश्चित_held(&engine->active.lock);

	/*
	 * With the advent of preempt-to-busy, we frequently encounter
	 * requests that we have unsubmitted from HW, but left running
	 * until the next ack and so have completed in the meanसमय. On
	 * resubmission of that completed request, we can skip
	 * updating the payload, and execlists can even skip submitting
	 * the request.
	 *
	 * We must हटाओ the request from the caller's priority queue,
	 * and the caller must only call us when the request is in their
	 * priority queue, under the active.lock. This ensures that the
	 * request has *not* yet been retired and we can safely move
	 * the request पूर्णांकo the engine->active.list where it will be
	 * dropped upon retiring. (Otherwise अगर resubmit a *retired*
	 * request, this would be a horrible use-after-मुक्त.)
	 */
	अगर (__i915_request_is_complete(request)) अणु
		list_del_init(&request->sched.link);
		जाओ active;
	पूर्ण

	अगर (unlikely(पूर्णांकel_context_is_banned(request->context)))
		i915_request_set_error_once(request, -EIO);

	अगर (unlikely(fatal_error(request->fence.error)))
		__i915_request_skip(request);

	/*
	 * Are we using semaphores when the gpu is alपढ़ोy saturated?
	 *
	 * Using semaphores incurs a cost in having the GPU poll a
	 * memory location, busyरुकोing क्रम it to change. The continual
	 * memory पढ़ोs can have a noticeable impact on the rest of the
	 * प्रणाली with the extra bus traffic, stalling the cpu as it too
	 * tries to access memory across the bus (perf stat -e bus-cycles).
	 *
	 * If we installed a semaphore on this request and we only submit
	 * the request after the संकेतer completed, that indicates the
	 * प्रणाली is overloaded and using semaphores at this समय only
	 * increases the amount of work we are करोing. If so, we disable
	 * further use of semaphores until we are idle again, whence we
	 * optimistically try again.
	 */
	अगर (request->sched.semaphores &&
	    i915_sw_fence_संकेतed(&request->semaphore))
		engine->saturated |= request->sched.semaphores;

	engine->emit_fini_bपढ़ोcrumb(request,
				     request->ring->vaddr + request->postfix);

	trace_i915_request_execute(request);
	engine->serial++;
	result = true;

	GEM_BUG_ON(test_bit(I915_FENCE_FLAG_ACTIVE, &request->fence.flags));
	list_move_tail(&request->sched.link, &engine->active.requests);
active:
	clear_bit(I915_FENCE_FLAG_PQUEUE, &request->fence.flags);
	set_bit(I915_FENCE_FLAG_ACTIVE, &request->fence.flags);

	/*
	 * XXX Rollback bonded-execution on __i915_request_unsubmit()?
	 *
	 * In the future, perhaps when we have an active समय-slicing scheduler,
	 * it will be पूर्णांकeresting to unsubmit parallel execution and हटाओ
	 * busyरुकोs from the GPU until their master is restarted. This is
	 * quite hairy, we have to carefully rollback the fence and करो a
	 * preempt-to-idle cycle on the target engine, all the जबतक the
	 * master execute_cb may refire.
	 */
	__notअगरy_execute_cb_irq(request);

	/* We may be recursing from the संकेत callback of another i915 fence */
	अगर (test_bit(DMA_FENCE_FLAG_ENABLE_SIGNAL_BIT, &request->fence.flags))
		i915_request_enable_bपढ़ोcrumb(request);

	वापस result;
पूर्ण

व्योम i915_request_submit(काष्ठा i915_request *request)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = request->engine;
	अचिन्हित दीर्घ flags;

	/* Will be called from irq-context when using क्रमeign fences. */
	spin_lock_irqsave(&engine->active.lock, flags);

	__i915_request_submit(request);

	spin_unlock_irqrestore(&engine->active.lock, flags);
पूर्ण

व्योम __i915_request_unsubmit(काष्ठा i915_request *request)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = request->engine;

	/*
	 * Only unwind in reverse order, required so that the per-context list
	 * is kept in seqno/ring order.
	 */
	RQ_TRACE(request, "\n");

	GEM_BUG_ON(!irqs_disabled());
	lockdep_निश्चित_held(&engine->active.lock);

	/*
	 * Beक्रमe we हटाओ this bपढ़ोcrumb from the संकेत list, we have
	 * to ensure that a concurrent dma_fence_enable_संकेतing() करोes not
	 * attach itself. We first mark the request as no दीर्घer active and
	 * make sure that is visible to other cores, and then हटाओ the
	 * bपढ़ोcrumb अगर attached.
	 */
	GEM_BUG_ON(!test_bit(I915_FENCE_FLAG_ACTIVE, &request->fence.flags));
	clear_bit_unlock(I915_FENCE_FLAG_ACTIVE, &request->fence.flags);
	अगर (test_bit(DMA_FENCE_FLAG_ENABLE_SIGNAL_BIT, &request->fence.flags))
		i915_request_cancel_bपढ़ोcrumb(request);

	/* We've already spun, don't अक्षरge on resubmitting. */
	अगर (request->sched.semaphores && __i915_request_has_started(request))
		request->sched.semaphores = 0;

	/*
	 * We करोn't need to wake_up any रुकोers on request->execute, they
	 * will get woken by any other event or us re-adding this request
	 * to the engine समयline (__i915_request_submit()). The रुकोers
	 * should be quite adapt at finding that the request now has a new
	 * global_seqno to the one they went to sleep on.
	 */
पूर्ण

व्योम i915_request_unsubmit(काष्ठा i915_request *request)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = request->engine;
	अचिन्हित दीर्घ flags;

	/* Will be called from irq-context when using क्रमeign fences. */
	spin_lock_irqsave(&engine->active.lock, flags);

	__i915_request_unsubmit(request);

	spin_unlock_irqrestore(&engine->active.lock, flags);
पूर्ण

अटल व्योम __cancel_request(काष्ठा i915_request *rq)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = शून्य;

	i915_request_active_engine(rq, &engine);

	अगर (engine && पूर्णांकel_engine_pulse(engine))
		पूर्णांकel_gt_handle_error(engine->gt, engine->mask, 0,
				      "request cancellation by %s",
				      current->comm);
पूर्ण

व्योम i915_request_cancel(काष्ठा i915_request *rq, पूर्णांक error)
अणु
	अगर (!i915_request_set_error_once(rq, error))
		वापस;

	set_bit(I915_FENCE_FLAG_SENTINEL, &rq->fence.flags);

	__cancel_request(rq);
पूर्ण

अटल पूर्णांक __i915_sw_fence_call
submit_notअगरy(काष्ठा i915_sw_fence *fence, क्रमागत i915_sw_fence_notअगरy state)
अणु
	काष्ठा i915_request *request =
		container_of(fence, typeof(*request), submit);

	चयन (state) अणु
	हाल FENCE_COMPLETE:
		trace_i915_request_submit(request);

		अगर (unlikely(fence->error))
			i915_request_set_error_once(request, fence->error);
		अन्यथा
			__rq_arm_watchकरोg(request);

		/*
		 * We need to serialize use of the submit_request() callback
		 * with its hotplugging perक्रमmed during an emergency
		 * i915_gem_set_wedged().  We use the RCU mechanism to mark the
		 * critical section in order to क्रमce i915_gem_set_wedged() to
		 * रुको until the submit_request() is completed beक्रमe
		 * proceeding.
		 */
		rcu_पढ़ो_lock();
		request->engine->submit_request(request);
		rcu_पढ़ो_unlock();
		अवरोध;

	हाल FENCE_FREE:
		i915_request_put(request);
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक __i915_sw_fence_call
semaphore_notअगरy(काष्ठा i915_sw_fence *fence, क्रमागत i915_sw_fence_notअगरy state)
अणु
	काष्ठा i915_request *rq = container_of(fence, typeof(*rq), semaphore);

	चयन (state) अणु
	हाल FENCE_COMPLETE:
		अवरोध;

	हाल FENCE_FREE:
		i915_request_put(rq);
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल व्योम retire_requests(काष्ठा पूर्णांकel_समयline *tl)
अणु
	काष्ठा i915_request *rq, *rn;

	list_क्रम_each_entry_safe(rq, rn, &tl->requests, link)
		अगर (!i915_request_retire(rq))
			अवरोध;
पूर्ण

अटल noअंतरभूत काष्ठा i915_request *
request_alloc_slow(काष्ठा पूर्णांकel_समयline *tl,
		   काष्ठा i915_request **rsvd,
		   gfp_t gfp)
अणु
	काष्ठा i915_request *rq;

	/* If we cannot रुको, dip पूर्णांकo our reserves */
	अगर (!gfpflags_allow_blocking(gfp)) अणु
		rq = xchg(rsvd, शून्य);
		अगर (!rq) /* Use the normal failure path क्रम one final WARN */
			जाओ out;

		वापस rq;
	पूर्ण

	अगर (list_empty(&tl->requests))
		जाओ out;

	/* Move our oldest request to the slab-cache (अगर not in use!) */
	rq = list_first_entry(&tl->requests, typeof(*rq), link);
	i915_request_retire(rq);

	rq = kmem_cache_alloc(global.slab_requests,
			      gfp | __GFP_RETRY_MAYFAIL | __GFP_NOWARN);
	अगर (rq)
		वापस rq;

	/* Ratelimit ourselves to prevent oom from malicious clients */
	rq = list_last_entry(&tl->requests, typeof(*rq), link);
	cond_synchronize_rcu(rq->rcustate);

	/* Retire our old requests in the hope that we मुक्त some */
	retire_requests(tl);

out:
	वापस kmem_cache_alloc(global.slab_requests, gfp);
पूर्ण

अटल व्योम __i915_request_ctor(व्योम *arg)
अणु
	काष्ठा i915_request *rq = arg;

	spin_lock_init(&rq->lock);
	i915_sched_node_init(&rq->sched);
	i915_sw_fence_init(&rq->submit, submit_notअगरy);
	i915_sw_fence_init(&rq->semaphore, semaphore_notअगरy);

	dma_fence_init(&rq->fence, &i915_fence_ops, &rq->lock, 0, 0);

	rq->capture_list = शून्य;

	init_llist_head(&rq->execute_cb);
पूर्ण

काष्ठा i915_request *
__i915_request_create(काष्ठा पूर्णांकel_context *ce, gfp_t gfp)
अणु
	काष्ठा पूर्णांकel_समयline *tl = ce->समयline;
	काष्ठा i915_request *rq;
	u32 seqno;
	पूर्णांक ret;

	might_sleep_अगर(gfpflags_allow_blocking(gfp));

	/* Check that the caller provided an alपढ़ोy pinned context */
	__पूर्णांकel_context_pin(ce);

	/*
	 * Beware: Dragons be flying overhead.
	 *
	 * We use RCU to look up requests in flight. The lookups may
	 * race with the request being allocated from the slab मुक्तlist.
	 * That is the request we are writing to here, may be in the process
	 * of being पढ़ो by __i915_active_request_get_rcu(). As such,
	 * we have to be very careful when overwriting the contents. During
	 * the RCU lookup, we change chase the request->engine poपूर्णांकer,
	 * पढ़ो the request->global_seqno and increment the reference count.
	 *
	 * The reference count is incremented atomically. If it is zero,
	 * the lookup knows the request is unallocated and complete. Otherwise,
	 * it is either still in use, or has been पुनः_स्मृतिated and reset
	 * with dma_fence_init(). This increment is safe क्रम release as we
	 * check that the request we have a reference to and matches the active
	 * request.
	 *
	 * Beक्रमe we increment the refcount, we chase the request->engine
	 * poपूर्णांकer. We must not call kmem_cache_zalloc() or अन्यथा we set
	 * that poपूर्णांकer to शून्य and cause a crash during the lookup. If
	 * we see the request is completed (based on the value of the
	 * old engine and seqno), the lookup is complete and reports शून्य.
	 * If we decide the request is not completed (new engine or seqno),
	 * then we grab a reference and द्विगुन check that it is still the
	 * active request - which it won't be and restart the lookup.
	 *
	 * Do not use kmem_cache_zalloc() here!
	 */
	rq = kmem_cache_alloc(global.slab_requests,
			      gfp | __GFP_RETRY_MAYFAIL | __GFP_NOWARN);
	अगर (unlikely(!rq)) अणु
		rq = request_alloc_slow(tl, &ce->engine->request_pool, gfp);
		अगर (!rq) अणु
			ret = -ENOMEM;
			जाओ err_unreserve;
		पूर्ण
	पूर्ण

	rq->context = ce;
	rq->engine = ce->engine;
	rq->ring = ce->ring;
	rq->execution_mask = ce->engine->mask;

	kref_init(&rq->fence.refcount);
	rq->fence.flags = 0;
	rq->fence.error = 0;
	INIT_LIST_HEAD(&rq->fence.cb_list);

	ret = पूर्णांकel_समयline_get_seqno(tl, rq, &seqno);
	अगर (ret)
		जाओ err_मुक्त;

	rq->fence.context = tl->fence_context;
	rq->fence.seqno = seqno;

	RCU_INIT_POINTER(rq->समयline, tl);
	rq->hwsp_seqno = tl->hwsp_seqno;
	GEM_BUG_ON(__i915_request_is_complete(rq));

	rq->rcustate = get_state_synchronize_rcu(); /* acts as smp_mb() */

	/* We bump the ref क्रम the fence chain */
	i915_sw_fence_reinit(&i915_request_get(rq)->submit);
	i915_sw_fence_reinit(&i915_request_get(rq)->semaphore);

	i915_sched_node_reinit(&rq->sched);

	/* No zalloc, everything must be cleared after use */
	rq->batch = शून्य;
	__rq_init_watchकरोg(rq);
	GEM_BUG_ON(rq->capture_list);
	GEM_BUG_ON(!llist_empty(&rq->execute_cb));

	/*
	 * Reserve space in the ring buffer क्रम all the commands required to
	 * eventually emit this request. This is to guarantee that the
	 * i915_request_add() call can't fail. Note that the reserve may need
	 * to be reकरोne अगर the request is not actually submitted straight
	 * away, e.g. because a GPU scheduler has deferred it.
	 *
	 * Note that due to how we add reserved_space to पूर्णांकel_ring_begin()
	 * we need to द्विगुन our request to ensure that अगर we need to wrap
	 * around inside i915_request_add() there is sufficient space at
	 * the beginning of the ring as well.
	 */
	rq->reserved_space =
		2 * rq->engine->emit_fini_bपढ़ोcrumb_dw * माप(u32);

	/*
	 * Record the position of the start of the request so that
	 * should we detect the updated seqno part-way through the
	 * GPU processing the request, we never over-estimate the
	 * position of the head.
	 */
	rq->head = rq->ring->emit;

	ret = rq->engine->request_alloc(rq);
	अगर (ret)
		जाओ err_unwind;

	rq->infix = rq->ring->emit; /* end of header; start of user payload */

	पूर्णांकel_context_mark_active(ce);
	list_add_tail_rcu(&rq->link, &tl->requests);

	वापस rq;

err_unwind:
	ce->ring->emit = rq->head;

	/* Make sure we didn't add ourselves to बाह्यal state beक्रमe मुक्तing */
	GEM_BUG_ON(!list_empty(&rq->sched.संकेतers_list));
	GEM_BUG_ON(!list_empty(&rq->sched.रुकोers_list));

err_मुक्त:
	kmem_cache_मुक्त(global.slab_requests, rq);
err_unreserve:
	पूर्णांकel_context_unpin(ce);
	वापस ERR_PTR(ret);
पूर्ण

काष्ठा i915_request *
i915_request_create(काष्ठा पूर्णांकel_context *ce)
अणु
	काष्ठा i915_request *rq;
	काष्ठा पूर्णांकel_समयline *tl;

	tl = पूर्णांकel_context_समयline_lock(ce);
	अगर (IS_ERR(tl))
		वापस ERR_CAST(tl);

	/* Move our oldest request to the slab-cache (अगर not in use!) */
	rq = list_first_entry(&tl->requests, typeof(*rq), link);
	अगर (!list_is_last(&rq->link, &tl->requests))
		i915_request_retire(rq);

	पूर्णांकel_context_enter(ce);
	rq = __i915_request_create(ce, GFP_KERNEL);
	पूर्णांकel_context_निकास(ce); /* active reference transferred to request */
	अगर (IS_ERR(rq))
		जाओ err_unlock;

	/* Check that we करो not पूर्णांकerrupt ourselves with a new request */
	rq->cookie = lockdep_pin_lock(&tl->mutex);

	वापस rq;

err_unlock:
	पूर्णांकel_context_समयline_unlock(tl);
	वापस rq;
पूर्ण

अटल पूर्णांक
i915_request_aरुको_start(काष्ठा i915_request *rq, काष्ठा i915_request *संकेत)
अणु
	काष्ठा dma_fence *fence;
	पूर्णांक err;

	अगर (i915_request_समयline(rq) == rcu_access_poपूर्णांकer(संकेत->समयline))
		वापस 0;

	अगर (i915_request_started(संकेत))
		वापस 0;

	/*
	 * The caller holds a reference on @संकेत, but we करो not serialise
	 * against it being retired and हटाओd from the lists.
	 *
	 * We करो not hold a reference to the request beक्रमe @संकेत, and
	 * so must be very careful to ensure that it is not _recycled_ as
	 * we follow the link backwards.
	 */
	fence = शून्य;
	rcu_पढ़ो_lock();
	करो अणु
		काष्ठा list_head *pos = READ_ONCE(संकेत->link.prev);
		काष्ठा i915_request *prev;

		/* Confirm संकेत has not been retired, the link is valid */
		अगर (unlikely(__i915_request_has_started(संकेत)))
			अवरोध;

		/* Is संकेत the earliest request on its समयline? */
		अगर (pos == &rcu_dereference(संकेत->समयline)->requests)
			अवरोध;

		/*
		 * Peek at the request beक्रमe us in the समयline. That
		 * request will only be valid beक्रमe it is retired, so
		 * after acquiring a reference to it, confirm that it is
		 * still part of the संकेतer's समयline.
		 */
		prev = list_entry(pos, typeof(*prev), link);
		अगर (!i915_request_get_rcu(prev))
			अवरोध;

		/* After the strong barrier, confirm prev is still attached */
		अगर (unlikely(READ_ONCE(prev->link.next) != &संकेत->link)) अणु
			i915_request_put(prev);
			अवरोध;
		पूर्ण

		fence = &prev->fence;
	पूर्ण जबतक (0);
	rcu_पढ़ो_unlock();
	अगर (!fence)
		वापस 0;

	err = 0;
	अगर (!पूर्णांकel_समयline_sync_is_later(i915_request_समयline(rq), fence))
		err = i915_sw_fence_aरुको_dma_fence(&rq->submit,
						    fence, 0,
						    I915_FENCE_GFP);
	dma_fence_put(fence);

	वापस err;
पूर्ण

अटल पूर्णांकel_engine_mask_t
alपढ़ोy_busyरुकोing(काष्ठा i915_request *rq)
अणु
	/*
	 * Polling a semaphore causes bus traffic, delaying other users of
	 * both the GPU and CPU. We want to limit the impact on others,
	 * जबतक taking advantage of early submission to reduce GPU
	 * latency. Thereक्रमe we restrict ourselves to not using more
	 * than one semaphore from each source, and not using a semaphore
	 * अगर we have detected the engine is saturated (i.e. would not be
	 * submitted early and cause bus traffic पढ़ोing an alपढ़ोy passed
	 * semaphore).
	 *
	 * See the are-we-too-late? check in __i915_request_submit().
	 */
	वापस rq->sched.semaphores | READ_ONCE(rq->engine->saturated);
पूर्ण

अटल पूर्णांक
__emit_semaphore_रुको(काष्ठा i915_request *to,
		      काष्ठा i915_request *from,
		      u32 seqno)
अणु
	स्थिर पूर्णांक has_token = INTEL_GEN(to->engine->i915) >= 12;
	u32 hwsp_offset;
	पूर्णांक len, err;
	u32 *cs;

	GEM_BUG_ON(INTEL_GEN(to->engine->i915) < 8);
	GEM_BUG_ON(i915_request_has_initial_bपढ़ोcrumb(to));

	/* We need to pin the संकेतer's HWSP until we are finished पढ़ोing. */
	err = पूर्णांकel_समयline_पढ़ो_hwsp(from, to, &hwsp_offset);
	अगर (err)
		वापस err;

	len = 4;
	अगर (has_token)
		len += 2;

	cs = पूर्णांकel_ring_begin(to, len);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	/*
	 * Using greater-than-or-equal here means we have to worry
	 * about seqno wraparound. To side step that issue, we swap
	 * the समयline HWSP upon wrapping, so that everyone listening
	 * क्रम the old (pre-wrap) values करो not see the much smaller
	 * (post-wrap) values than they were expecting (and so रुको
	 * क्रमever).
	 */
	*cs++ = (MI_SEMAPHORE_WAIT |
		 MI_SEMAPHORE_GLOBAL_GTT |
		 MI_SEMAPHORE_POLL |
		 MI_SEMAPHORE_SAD_GTE_SDD) +
		has_token;
	*cs++ = seqno;
	*cs++ = hwsp_offset;
	*cs++ = 0;
	अगर (has_token) अणु
		*cs++ = 0;
		*cs++ = MI_NOOP;
	पूर्ण

	पूर्णांकel_ring_advance(to, cs);
	वापस 0;
पूर्ण

अटल पूर्णांक
emit_semaphore_रुको(काष्ठा i915_request *to,
		    काष्ठा i915_request *from,
		    gfp_t gfp)
अणु
	स्थिर पूर्णांकel_engine_mask_t mask = READ_ONCE(from->engine)->mask;
	काष्ठा i915_sw_fence *रुको = &to->submit;

	अगर (!पूर्णांकel_context_use_semaphores(to->context))
		जाओ aरुको_fence;

	अगर (i915_request_has_initial_bपढ़ोcrumb(to))
		जाओ aरुको_fence;

	/*
	 * If this or its dependents are रुकोing on an बाह्यal fence
	 * that may fail catastrophically, then we want to aव्योम using
	 * sempahores as they bypass the fence संकेतing metadata, and we
	 * lose the fence->error propagation.
	 */
	अगर (from->sched.flags & I915_SCHED_HAS_EXTERNAL_CHAIN)
		जाओ aरुको_fence;

	/* Just emit the first semaphore we see as request space is limited. */
	अगर (alपढ़ोy_busyरुकोing(to) & mask)
		जाओ aरुको_fence;

	अगर (i915_request_aरुको_start(to, from) < 0)
		जाओ aरुको_fence;

	/* Only submit our spinner after the संकेतer is running! */
	अगर (__aरुको_execution(to, from, शून्य, gfp))
		जाओ aरुको_fence;

	अगर (__emit_semaphore_रुको(to, from, from->fence.seqno))
		जाओ aरुको_fence;

	to->sched.semaphores |= mask;
	रुको = &to->semaphore;

aरुको_fence:
	वापस i915_sw_fence_aरुको_dma_fence(रुको,
					     &from->fence, 0,
					     I915_FENCE_GFP);
पूर्ण

अटल bool पूर्णांकel_समयline_sync_has_start(काष्ठा पूर्णांकel_समयline *tl,
					  काष्ठा dma_fence *fence)
अणु
	वापस __पूर्णांकel_समयline_sync_is_later(tl,
					      fence->context,
					      fence->seqno - 1);
पूर्ण

अटल पूर्णांक पूर्णांकel_समयline_sync_set_start(काष्ठा पूर्णांकel_समयline *tl,
					 स्थिर काष्ठा dma_fence *fence)
अणु
	वापस __पूर्णांकel_समयline_sync_set(tl, fence->context, fence->seqno - 1);
पूर्ण

अटल पूर्णांक
__i915_request_aरुको_execution(काष्ठा i915_request *to,
			       काष्ठा i915_request *from,
			       व्योम (*hook)(काष्ठा i915_request *rq,
					    काष्ठा dma_fence *संकेत))
अणु
	पूर्णांक err;

	GEM_BUG_ON(पूर्णांकel_context_is_barrier(from->context));

	/* Submit both requests at the same समय */
	err = __aरुको_execution(to, from, hook, I915_FENCE_GFP);
	अगर (err)
		वापस err;

	/* Squash repeated depenendices to the same समयlines */
	अगर (पूर्णांकel_समयline_sync_has_start(i915_request_समयline(to),
					  &from->fence))
		वापस 0;

	/*
	 * Wait until the start of this request.
	 *
	 * The execution cb fires when we submit the request to HW. But in
	 * many हालs this may be दीर्घ beक्रमe the request itself is पढ़ोy to
	 * run (consider that we submit 2 requests क्रम the same context, where
	 * the request of पूर्णांकerest is behind an indefinite spinner). So we hook
	 * up to both to reduce our queues and keep the execution lag minimised
	 * in the worst हाल, though we hope that the aरुको_start is elided.
	 */
	err = i915_request_aरुको_start(to, from);
	अगर (err < 0)
		वापस err;

	/*
	 * Ensure both start together [after all semaphores in संकेत]
	 *
	 * Now that we are queued to the HW at roughly the same समय (thanks
	 * to the execute cb) and are पढ़ोy to run at roughly the same समय
	 * (thanks to the aरुको start), our संकेतer may still be indefinitely
	 * delayed by रुकोing on a semaphore from a remote engine. If our
	 * संकेतer depends on a semaphore, so indirectly करो we, and we करो not
	 * want to start our payload until our संकेतer also starts theirs.
	 * So we रुको.
	 *
	 * However, there is also a second condition क्रम which we need to रुको
	 * क्रम the precise start of the संकेतer. Consider that the संकेतer
	 * was submitted in a chain of requests following another context
	 * (with just an ordinary पूर्णांकra-engine fence dependency between the
	 * two). In this हाल the संकेतer is queued to HW, but not क्रम
	 * immediate execution, and so we must रुको until it reaches the
	 * active slot.
	 */
	अगर (पूर्णांकel_engine_has_semaphores(to->engine) &&
	    !i915_request_has_initial_bपढ़ोcrumb(to)) अणु
		err = __emit_semaphore_रुको(to, from, from->fence.seqno - 1);
		अगर (err < 0)
			वापस err;
	पूर्ण

	/* Couple the dependency tree क्रम PI on this exposed to->fence */
	अगर (to->engine->schedule) अणु
		err = i915_sched_node_add_dependency(&to->sched,
						     &from->sched,
						     I915_DEPENDENCY_WEAK);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस पूर्णांकel_समयline_sync_set_start(i915_request_समयline(to),
					     &from->fence);
पूर्ण

अटल व्योम mark_बाह्यal(काष्ठा i915_request *rq)
अणु
	/*
	 * The करोwnside of using semaphores is that we lose metadata passing
	 * aदीर्घ the संकेतing chain. This is particularly nasty when we
	 * need to pass aदीर्घ a fatal error such as EFAULT or EDEADLK. For
	 * fatal errors we want to scrub the request beक्रमe it is executed,
	 * which means that we cannot preload the request onto HW and have
	 * it रुको upon a semaphore.
	 */
	rq->sched.flags |= I915_SCHED_HAS_EXTERNAL_CHAIN;
पूर्ण

अटल पूर्णांक
__i915_request_aरुको_बाह्यal(काष्ठा i915_request *rq, काष्ठा dma_fence *fence)
अणु
	mark_बाह्यal(rq);
	वापस i915_sw_fence_aरुको_dma_fence(&rq->submit, fence,
					     i915_fence_context_समयout(rq->engine->i915,
									fence->context),
					     I915_FENCE_GFP);
पूर्ण

अटल पूर्णांक
i915_request_aरुको_बाह्यal(काष्ठा i915_request *rq, काष्ठा dma_fence *fence)
अणु
	काष्ठा dma_fence *iter;
	पूर्णांक err = 0;

	अगर (!to_dma_fence_chain(fence))
		वापस __i915_request_aरुको_बाह्यal(rq, fence);

	dma_fence_chain_क्रम_each(iter, fence) अणु
		काष्ठा dma_fence_chain *chain = to_dma_fence_chain(iter);

		अगर (!dma_fence_is_i915(chain->fence)) अणु
			err = __i915_request_aरुको_बाह्यal(rq, iter);
			अवरोध;
		पूर्ण

		err = i915_request_aरुको_dma_fence(rq, chain->fence);
		अगर (err < 0)
			अवरोध;
	पूर्ण

	dma_fence_put(iter);
	वापस err;
पूर्ण

पूर्णांक
i915_request_aरुको_execution(काष्ठा i915_request *rq,
			     काष्ठा dma_fence *fence,
			     व्योम (*hook)(काष्ठा i915_request *rq,
					  काष्ठा dma_fence *संकेत))
अणु
	काष्ठा dma_fence **child = &fence;
	अचिन्हित पूर्णांक nchild = 1;
	पूर्णांक ret;

	अगर (dma_fence_is_array(fence)) अणु
		काष्ठा dma_fence_array *array = to_dma_fence_array(fence);

		/* XXX Error क्रम संकेत-on-any fence arrays */

		child = array->fences;
		nchild = array->num_fences;
		GEM_BUG_ON(!nchild);
	पूर्ण

	करो अणु
		fence = *child++;
		अगर (test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &fence->flags)) अणु
			i915_sw_fence_set_error_once(&rq->submit, fence->error);
			जारी;
		पूर्ण

		अगर (fence->context == rq->fence.context)
			जारी;

		/*
		 * We करोn't squash repeated fence dependencies here as we
		 * want to run our callback in all हालs.
		 */

		अगर (dma_fence_is_i915(fence))
			ret = __i915_request_aरुको_execution(rq,
							     to_request(fence),
							     hook);
		अन्यथा
			ret = i915_request_aरुको_बाह्यal(rq, fence);
		अगर (ret < 0)
			वापस ret;
	पूर्ण जबतक (--nchild);

	वापस 0;
पूर्ण

अटल पूर्णांक
aरुको_request_submit(काष्ठा i915_request *to, काष्ठा i915_request *from)
अणु
	/*
	 * If we are रुकोing on a भव engine, then it may be
	 * स्थिरrained to execute on a single engine *prior* to submission.
	 * When it is submitted, it will be first submitted to the भव
	 * engine and then passed to the physical engine. We cannot allow
	 * the रुकोer to be submitted immediately to the physical engine
	 * as it may then bypass the भव request.
	 */
	अगर (to->engine == READ_ONCE(from->engine))
		वापस i915_sw_fence_aरुको_sw_fence_gfp(&to->submit,
							&from->submit,
							I915_FENCE_GFP);
	अन्यथा
		वापस __i915_request_aरुको_execution(to, from, शून्य);
पूर्ण

अटल पूर्णांक
i915_request_aरुको_request(काष्ठा i915_request *to, काष्ठा i915_request *from)
अणु
	पूर्णांक ret;

	GEM_BUG_ON(to == from);
	GEM_BUG_ON(to->समयline == from->समयline);

	अगर (i915_request_completed(from)) अणु
		i915_sw_fence_set_error_once(&to->submit, from->fence.error);
		वापस 0;
	पूर्ण

	अगर (to->engine->schedule) अणु
		ret = i915_sched_node_add_dependency(&to->sched,
						     &from->sched,
						     I915_DEPENDENCY_EXTERNAL);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (is_घातer_of_2(to->execution_mask | READ_ONCE(from->execution_mask)))
		ret = aरुको_request_submit(to, from);
	अन्यथा
		ret = emit_semaphore_रुको(to, from, I915_FENCE_GFP);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक
i915_request_aरुको_dma_fence(काष्ठा i915_request *rq, काष्ठा dma_fence *fence)
अणु
	काष्ठा dma_fence **child = &fence;
	अचिन्हित पूर्णांक nchild = 1;
	पूर्णांक ret;

	/*
	 * Note that अगर the fence-array was created in संकेत-on-any mode,
	 * we should *not* decompose it पूर्णांकo its inभागidual fences. However,
	 * we करोn't currently store which mode the fence-array is operating
	 * in. Fortunately, the only user of संकेत-on-any is निजी to
	 * amdgpu and we should not see any incoming fence-array from
	 * sync-file being in संकेत-on-any mode.
	 */
	अगर (dma_fence_is_array(fence)) अणु
		काष्ठा dma_fence_array *array = to_dma_fence_array(fence);

		child = array->fences;
		nchild = array->num_fences;
		GEM_BUG_ON(!nchild);
	पूर्ण

	करो अणु
		fence = *child++;
		अगर (test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &fence->flags)) अणु
			i915_sw_fence_set_error_once(&rq->submit, fence->error);
			जारी;
		पूर्ण

		/*
		 * Requests on the same समयline are explicitly ordered, aदीर्घ
		 * with their dependencies, by i915_request_add() which ensures
		 * that requests are submitted in-order through each ring.
		 */
		अगर (fence->context == rq->fence.context)
			जारी;

		/* Squash repeated रुकोs to the same समयlines */
		अगर (fence->context &&
		    पूर्णांकel_समयline_sync_is_later(i915_request_समयline(rq),
						 fence))
			जारी;

		अगर (dma_fence_is_i915(fence))
			ret = i915_request_aरुको_request(rq, to_request(fence));
		अन्यथा
			ret = i915_request_aरुको_बाह्यal(rq, fence);
		अगर (ret < 0)
			वापस ret;

		/* Record the latest fence used against each समयline */
		अगर (fence->context)
			पूर्णांकel_समयline_sync_set(i915_request_समयline(rq),
						fence);
	पूर्ण जबतक (--nchild);

	वापस 0;
पूर्ण

/**
 * i915_request_aरुको_object - set this request to (async) रुको upon a bo
 * @to: request we are wishing to use
 * @obj: object which may be in use on another ring.
 * @ग_लिखो: whether the रुको is on behalf of a ग_लिखोr
 *
 * This code is meant to असलtract object synchronization with the GPU.
 * Conceptually we serialise ग_लिखोs between engines inside the GPU.
 * We only allow one engine to ग_लिखो पूर्णांकo a buffer at any समय, but
 * multiple पढ़ोers. To ensure each has a coherent view of memory, we must:
 *
 * - If there is an outstanding ग_लिखो request to the object, the new
 *   request must रुको क्रम it to complete (either CPU or in hw, requests
 *   on the same ring will be naturally ordered).
 *
 * - If we are a ग_लिखो request (pending_ग_लिखो_करोमुख्य is set), the new
 *   request must रुको क्रम outstanding पढ़ो requests to complete.
 *
 * Returns 0 अगर successful, अन्यथा propagates up the lower layer error.
 */
पूर्णांक
i915_request_aरुको_object(काष्ठा i915_request *to,
			  काष्ठा drm_i915_gem_object *obj,
			  bool ग_लिखो)
अणु
	काष्ठा dma_fence *excl;
	पूर्णांक ret = 0;

	अगर (ग_लिखो) अणु
		काष्ठा dma_fence **shared;
		अचिन्हित पूर्णांक count, i;

		ret = dma_resv_get_fences_rcu(obj->base.resv,
							&excl, &count, &shared);
		अगर (ret)
			वापस ret;

		क्रम (i = 0; i < count; i++) अणु
			ret = i915_request_aरुको_dma_fence(to, shared[i]);
			अगर (ret)
				अवरोध;

			dma_fence_put(shared[i]);
		पूर्ण

		क्रम (; i < count; i++)
			dma_fence_put(shared[i]);
		kमुक्त(shared);
	पूर्ण अन्यथा अणु
		excl = dma_resv_get_excl_rcu(obj->base.resv);
	पूर्ण

	अगर (excl) अणु
		अगर (ret == 0)
			ret = i915_request_aरुको_dma_fence(to, excl);

		dma_fence_put(excl);
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा i915_request *
__i915_request_add_to_समयline(काष्ठा i915_request *rq)
अणु
	काष्ठा पूर्णांकel_समयline *समयline = i915_request_समयline(rq);
	काष्ठा i915_request *prev;

	/*
	 * Dependency tracking and request ordering aदीर्घ the समयline
	 * is special हालd so that we can eliminate redundant ordering
	 * operations जबतक building the request (we know that the समयline
	 * itself is ordered, and here we guarantee it).
	 *
	 * As we know we will need to emit tracking aदीर्घ the समयline,
	 * we embed the hooks पूर्णांकo our request काष्ठा -- at the cost of
	 * having to have specialised no-allocation पूर्णांकerfaces (which will
	 * be beneficial अन्यथाwhere).
	 *
	 * A second benefit to खोलो-coding i915_request_aरुको_request is
	 * that we can apply a slight variant of the rules specialised
	 * क्रम समयlines that jump between engines (such as भव engines).
	 * If we consider the हाल of भव engine, we must emit a dma-fence
	 * to prevent scheduling of the second request until the first is
	 * complete (to maximise our greedy late load balancing) and this
	 * precludes optimising to use semaphores serialisation of a single
	 * समयline across engines.
	 */
	prev = to_request(__i915_active_fence_set(&समयline->last_request,
						  &rq->fence));
	अगर (prev && !__i915_request_is_complete(prev)) अणु
		/*
		 * The requests are supposed to be kept in order. However,
		 * we need to be wary in हाल the समयline->last_request
		 * is used as a barrier क्रम बाह्यal modअगरication to this
		 * context.
		 */
		GEM_BUG_ON(prev->context == rq->context &&
			   i915_seqno_passed(prev->fence.seqno,
					     rq->fence.seqno));

		अगर (is_घातer_of_2(READ_ONCE(prev->engine)->mask | rq->engine->mask))
			i915_sw_fence_aरुको_sw_fence(&rq->submit,
						     &prev->submit,
						     &rq->submitq);
		अन्यथा
			__i915_sw_fence_aरुको_dma_fence(&rq->submit,
							&prev->fence,
							&rq->dmaq);
		अगर (rq->engine->schedule)
			__i915_sched_node_add_dependency(&rq->sched,
							 &prev->sched,
							 &rq->dep,
							 0);
	पूर्ण

	/*
	 * Make sure that no request gazumped us - अगर it was allocated after
	 * our i915_request_alloc() and called __i915_request_add() beक्रमe
	 * us, the समयline will hold its seqno which is later than ours.
	 */
	GEM_BUG_ON(समयline->seqno != rq->fence.seqno);

	वापस prev;
पूर्ण

/*
 * NB: This function is not allowed to fail. Doing so would mean the the
 * request is not being tracked क्रम completion but the work itself is
 * going to happen on the hardware. This would be a Bad Thing(पंचांग).
 */
काष्ठा i915_request *__i915_request_commit(काष्ठा i915_request *rq)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = rq->engine;
	काष्ठा पूर्णांकel_ring *ring = rq->ring;
	u32 *cs;

	RQ_TRACE(rq, "\n");

	/*
	 * To ensure that this call will not fail, space क्रम its emissions
	 * should alपढ़ोy have been reserved in the ring buffer. Let the ring
	 * know that it is समय to use that space up.
	 */
	GEM_BUG_ON(rq->reserved_space > ring->space);
	rq->reserved_space = 0;
	rq->emitted_jअगरfies = jअगरfies;

	/*
	 * Record the position of the start of the bपढ़ोcrumb so that
	 * should we detect the updated seqno part-way through the
	 * GPU processing the request, we never over-estimate the
	 * position of the ring's HEAD.
	 */
	cs = पूर्णांकel_ring_begin(rq, engine->emit_fini_bपढ़ोcrumb_dw);
	GEM_BUG_ON(IS_ERR(cs));
	rq->postfix = पूर्णांकel_ring_offset(rq, cs);

	वापस __i915_request_add_to_समयline(rq);
पूर्ण

व्योम __i915_request_queue_bh(काष्ठा i915_request *rq)
अणु
	i915_sw_fence_commit(&rq->semaphore);
	i915_sw_fence_commit(&rq->submit);
पूर्ण

व्योम __i915_request_queue(काष्ठा i915_request *rq,
			  स्थिर काष्ठा i915_sched_attr *attr)
अणु
	/*
	 * Let the backend know a new request has arrived that may need
	 * to adjust the existing execution schedule due to a high priority
	 * request - i.e. we may want to preempt the current request in order
	 * to run a high priority dependency chain *beक्रमe* we can execute this
	 * request.
	 *
	 * This is called beक्रमe the request is पढ़ोy to run so that we can
	 * decide whether to preempt the entire chain so that it is पढ़ोy to
	 * run at the earliest possible convenience.
	 */
	अगर (attr && rq->engine->schedule)
		rq->engine->schedule(rq, attr);

	local_bh_disable();
	__i915_request_queue_bh(rq);
	local_bh_enable(); /* kick tasklets */
पूर्ण

व्योम i915_request_add(काष्ठा i915_request *rq)
अणु
	काष्ठा पूर्णांकel_समयline * स्थिर tl = i915_request_समयline(rq);
	काष्ठा i915_sched_attr attr = अणुपूर्ण;
	काष्ठा i915_gem_context *ctx;

	lockdep_निश्चित_held(&tl->mutex);
	lockdep_unpin_lock(&tl->mutex, rq->cookie);

	trace_i915_request_add(rq);
	__i915_request_commit(rq);

	/* XXX placeholder क्रम selftests */
	rcu_पढ़ो_lock();
	ctx = rcu_dereference(rq->context->gem_context);
	अगर (ctx)
		attr = ctx->sched;
	rcu_पढ़ो_unlock();

	__i915_request_queue(rq, &attr);

	mutex_unlock(&tl->mutex);
पूर्ण

अटल अचिन्हित दीर्घ local_घड़ी_ns(अचिन्हित पूर्णांक *cpu)
अणु
	अचिन्हित दीर्घ t;

	/*
	 * Cheaply and approximately convert from nanoseconds to microseconds.
	 * The result and subsequent calculations are also defined in the same
	 * approximate microseconds units. The principal source of timing
	 * error here is from the simple truncation.
	 *
	 * Note that local_घड़ी() is only defined wrt to the current CPU;
	 * the comparisons are no दीर्घer valid अगर we चयन CPUs. Instead of
	 * blocking preemption क्रम the entire busyरुको, we can detect the CPU
	 * चयन and use that as indicator of प्रणाली load and a reason to
	 * stop busyरुकोing, see busyरुको_stop().
	 */
	*cpu = get_cpu();
	t = local_घड़ी();
	put_cpu();

	वापस t;
पूर्ण

अटल bool busyरुको_stop(अचिन्हित दीर्घ समयout, अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक this_cpu;

	अगर (समय_after(local_घड़ी_ns(&this_cpu), समयout))
		वापस true;

	वापस this_cpu != cpu;
पूर्ण

अटल bool __i915_spin_request(काष्ठा i915_request * स्थिर rq, पूर्णांक state)
अणु
	अचिन्हित दीर्घ समयout_ns;
	अचिन्हित पूर्णांक cpu;

	/*
	 * Only रुको क्रम the request अगर we know it is likely to complete.
	 *
	 * We करोn't track the बारtamps around requests, nor the average
	 * request length, so we करो not have a good indicator that this
	 * request will complete within the समयout. What we करो know is the
	 * order in which requests are executed by the context and so we can
	 * tell अगर the request has been started. If the request is not even
	 * running yet, it is a fair assumption that it will not complete
	 * within our relatively लघु समयout.
	 */
	अगर (!i915_request_is_running(rq))
		वापस false;

	/*
	 * When रुकोing क्रम high frequency requests, e.g. during synchronous
	 * rendering split between the CPU and GPU, the finite amount of समय
	 * required to set up the irq and रुको upon it limits the response
	 * rate. By busyरुकोing on the request completion क्रम a लघु जबतक we
	 * can service the high frequency रुकोs as quick as possible. However,
	 * अगर it is a slow request, we want to sleep as quickly as possible.
	 * The tradeoff between रुकोing and sleeping is roughly the समय it
	 * takes to sleep on a request, on the order of a microsecond.
	 */

	समयout_ns = READ_ONCE(rq->engine->props.max_busyरुको_duration_ns);
	समयout_ns += local_घड़ी_ns(&cpu);
	करो अणु
		अगर (dma_fence_is_संकेतed(&rq->fence))
			वापस true;

		अगर (संकेत_pending_state(state, current))
			अवरोध;

		अगर (busyरुको_stop(समयout_ns, cpu))
			अवरोध;

		cpu_relax();
	पूर्ण जबतक (!need_resched());

	वापस false;
पूर्ण

काष्ठा request_रुको अणु
	काष्ठा dma_fence_cb cb;
	काष्ठा task_काष्ठा *tsk;
पूर्ण;

अटल व्योम request_रुको_wake(काष्ठा dma_fence *fence, काष्ठा dma_fence_cb *cb)
अणु
	काष्ठा request_रुको *रुको = container_of(cb, typeof(*रुको), cb);

	wake_up_process(fetch_and_zero(&रुको->tsk));
पूर्ण

/**
 * i915_request_रुको - रुको until execution of request has finished
 * @rq: the request to रुको upon
 * @flags: how to रुको
 * @समयout: how दीर्घ to रुको in jअगरfies
 *
 * i915_request_रुको() रुकोs क्रम the request to be completed, क्रम a
 * maximum of @समयout jअगरfies (with MAX_SCHEDULE_TIMEOUT implying an
 * unbounded रुको).
 *
 * Returns the reमुख्यing समय (in jअगरfies) अगर the request completed, which may
 * be zero or -ETIME अगर the request is unfinished after the समयout expires.
 * May वापस -EINTR is called with I915_WAIT_INTERRUPTIBLE and a संकेत is
 * pending beक्रमe the request completes.
 */
दीर्घ i915_request_रुको(काष्ठा i915_request *rq,
		       अचिन्हित पूर्णांक flags,
		       दीर्घ समयout)
अणु
	स्थिर पूर्णांक state = flags & I915_WAIT_INTERRUPTIBLE ?
		TASK_INTERRUPTIBLE : TASK_UNINTERRUPTIBLE;
	काष्ठा request_रुको रुको;

	might_sleep();
	GEM_BUG_ON(समयout < 0);

	अगर (dma_fence_is_संकेतed(&rq->fence))
		वापस समयout;

	अगर (!समयout)
		वापस -ETIME;

	trace_i915_request_रुको_begin(rq, flags);

	/*
	 * We must never रुको on the GPU जबतक holding a lock as we
	 * may need to perक्रमm a GPU reset. So जबतक we करोn't need to
	 * serialise रुको/reset with an explicit lock, we करो want
	 * lockdep to detect potential dependency cycles.
	 */
	mutex_acquire(&rq->engine->gt->reset.mutex.dep_map, 0, 0, _THIS_IP_);

	/*
	 * Optimistic spin beक्रमe touching IRQs.
	 *
	 * We may use a rather large value here to offset the penalty of
	 * चयनing away from the active task. Frequently, the client will
	 * रुको upon an old swapbuffer to throttle itself to reमुख्य within a
	 * frame of the gpu. If the client is running in lockstep with the gpu,
	 * then it should not be रुकोing दीर्घ at all, and a sleep now will incur
	 * extra scheduler latency in producing the next frame. To try to
	 * aव्योम adding the cost of enabling/disabling the पूर्णांकerrupt to the
	 * लघु रुको, we first spin to see अगर the request would have completed
	 * in the समय taken to setup the पूर्णांकerrupt.
	 *
	 * We need upto 5us to enable the irq, and upto 20us to hide the
	 * scheduler latency of a context चयन, ignoring the secondary
	 * impacts from a context चयन such as cache eviction.
	 *
	 * The scheme used क्रम low-latency IO is called "hybrid पूर्णांकerrupt
	 * polling". The suggestion there is to sleep until just beक्रमe you
	 * expect to be woken by the device पूर्णांकerrupt and then poll क्रम its
	 * completion. That requires having a good predictor क्रम the request
	 * duration, which we currently lack.
	 */
	अगर (IS_ACTIVE(CONFIG_DRM_I915_MAX_REQUEST_BUSYWAIT) &&
	    __i915_spin_request(rq, state))
		जाओ out;

	/*
	 * This client is about to stall रुकोing क्रम the GPU. In many हालs
	 * this is undesirable and limits the throughput of the प्रणाली, as
	 * many clients cannot जारी processing user input/output whilst
	 * blocked. RPS स्वतःtuning may take tens of milliseconds to respond
	 * to the GPU load and thus incurs additional latency क्रम the client.
	 * We can circumvent that by promoting the GPU frequency to maximum
	 * beक्रमe we sleep. This makes the GPU throttle up much more quickly
	 * (good क्रम benchmarks and user experience, e.g. winकरोw animations),
	 * but at a cost of spending more घातer processing the workload
	 * (bad क्रम battery).
	 */
	अगर (flags & I915_WAIT_PRIORITY && !i915_request_started(rq))
		पूर्णांकel_rps_boost(rq);

	रुको.tsk = current;
	अगर (dma_fence_add_callback(&rq->fence, &रुको.cb, request_रुको_wake))
		जाओ out;

	/*
	 * Flush the submission tasklet, but only अगर it may help this request.
	 *
	 * We someबार experience some latency between the HW पूर्णांकerrupts and
	 * tasklet execution (mostly due to ksoftirqd latency, but it can also
	 * be due to lazy CS events), so lets run the tasklet manually अगर there
	 * is a chance it may submit this request. If the request is not पढ़ोy
	 * to run, as it is रुकोing क्रम other fences to be संकेतed, flushing
	 * the tasklet is busy work without any advantage क्रम this client.
	 *
	 * If the HW is being lazy, this is the last chance beक्रमe we go to
	 * sleep to catch any pending events. We will check periodically in
	 * the heartbeat to flush the submission tasklets as a last resort
	 * क्रम unhappy HW.
	 */
	अगर (i915_request_is_पढ़ोy(rq))
		__पूर्णांकel_engine_flush_submission(rq->engine, false);

	क्रम (;;) अणु
		set_current_state(state);

		अगर (dma_fence_is_संकेतed(&rq->fence))
			अवरोध;

		अगर (संकेत_pending_state(state, current)) अणु
			समयout = -ERESTARTSYS;
			अवरोध;
		पूर्ण

		अगर (!समयout) अणु
			समयout = -ETIME;
			अवरोध;
		पूर्ण

		समयout = io_schedule_समयout(समयout);
	पूर्ण
	__set_current_state(TASK_RUNNING);

	अगर (READ_ONCE(रुको.tsk))
		dma_fence_हटाओ_callback(&rq->fence, &रुको.cb);
	GEM_BUG_ON(!list_empty(&रुको.cb.node));

out:
	mutex_release(&rq->engine->gt->reset.mutex.dep_map, _THIS_IP_);
	trace_i915_request_रुको_end(rq);
	वापस समयout;
पूर्ण

अटल पूर्णांक prपूर्णांक_sched_attr(स्थिर काष्ठा i915_sched_attr *attr,
			    अक्षर *buf, पूर्णांक x, पूर्णांक len)
अणु
	अगर (attr->priority == I915_PRIORITY_INVALID)
		वापस x;

	x += snम_लिखो(buf + x, len - x,
		      " prio=%d", attr->priority);

	वापस x;
पूर्ण

अटल अक्षर queue_status(स्थिर काष्ठा i915_request *rq)
अणु
	अगर (i915_request_is_active(rq))
		वापस 'E';

	अगर (i915_request_is_पढ़ोy(rq))
		वापस पूर्णांकel_engine_is_भव(rq->engine) ? 'V' : 'R';

	वापस 'U';
पूर्ण

अटल स्थिर अक्षर *run_status(स्थिर काष्ठा i915_request *rq)
अणु
	अगर (__i915_request_is_complete(rq))
		वापस "!";

	अगर (__i915_request_has_started(rq))
		वापस "*";

	अगर (!i915_sw_fence_संकेतed(&rq->semaphore))
		वापस "&";

	वापस "";
पूर्ण

अटल स्थिर अक्षर *fence_status(स्थिर काष्ठा i915_request *rq)
अणु
	अगर (test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &rq->fence.flags))
		वापस "+";

	अगर (test_bit(DMA_FENCE_FLAG_ENABLE_SIGNAL_BIT, &rq->fence.flags))
		वापस "-";

	वापस "";
पूर्ण

व्योम i915_request_show(काष्ठा drm_prपूर्णांकer *m,
		       स्थिर काष्ठा i915_request *rq,
		       स्थिर अक्षर *prefix,
		       पूर्णांक indent)
अणु
	स्थिर अक्षर *name = rq->fence.ops->get_समयline_name((काष्ठा dma_fence *)&rq->fence);
	अक्षर buf[80] = "";
	पूर्णांक x = 0;

	/*
	 * The prefix is used to show the queue status, क्रम which we use
	 * the following flags:
	 *
	 *  U [Unपढ़ोy]
	 *    - initial status upon being submitted by the user
	 *
	 *    - the request is not पढ़ोy क्रम execution as it is रुकोing
	 *      क्रम बाह्यal fences
	 *
	 *  R [Ready]
	 *    - all fences the request was रुकोing on have been संकेतed,
	 *      and the request is now पढ़ोy क्रम execution and will be
	 *      in a backend queue
	 *
	 *    - a पढ़ोy request may still need to रुको on semaphores
	 *      [पूर्णांकernal fences]
	 *
	 *  V [Ready/भव]
	 *    - same as पढ़ोy, but queued over multiple backends
	 *
	 *  E [Executing]
	 *    - the request has been transferred from the backend queue and
	 *      submitted क्रम execution on HW
	 *
	 *    - a completed request may still be regarded as executing, its
	 *      status may not be updated until it is retired and हटाओd
	 *      from the lists
	 */

	x = prपूर्णांक_sched_attr(&rq->sched.attr, buf, x, माप(buf));

	drm_म_लिखो(m, "%s%.*s%c %llx:%lld%s%s %s @ %dms: %s\n",
		   prefix, indent, "                ",
		   queue_status(rq),
		   rq->fence.context, rq->fence.seqno,
		   run_status(rq),
		   fence_status(rq),
		   buf,
		   jअगरfies_to_msecs(jअगरfies - rq->emitted_jअगरfies),
		   name);
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "selftests/mock_request.c"
#समावेश "selftests/i915_request.c"
#पूर्ण_अगर

अटल व्योम i915_global_request_shrink(व्योम)
अणु
	kmem_cache_shrink(global.slab_execute_cbs);
	kmem_cache_shrink(global.slab_requests);
पूर्ण

अटल व्योम i915_global_request_निकास(व्योम)
अणु
	kmem_cache_destroy(global.slab_execute_cbs);
	kmem_cache_destroy(global.slab_requests);
पूर्ण

अटल काष्ठा i915_global_request global = अणु अणु
	.shrink = i915_global_request_shrink,
	.निकास = i915_global_request_निकास,
पूर्ण पूर्ण;

पूर्णांक __init i915_global_request_init(व्योम)
अणु
	global.slab_requests =
		kmem_cache_create("i915_request",
				  माप(काष्ठा i915_request),
				  __alignof__(काष्ठा i915_request),
				  SLAB_HWCACHE_ALIGN |
				  SLAB_RECLAIM_ACCOUNT |
				  SLAB_TYPESAFE_BY_RCU,
				  __i915_request_ctor);
	अगर (!global.slab_requests)
		वापस -ENOMEM;

	global.slab_execute_cbs = KMEM_CACHE(execute_cb,
					     SLAB_HWCACHE_ALIGN |
					     SLAB_RECLAIM_ACCOUNT |
					     SLAB_TYPESAFE_BY_RCU);
	अगर (!global.slab_execute_cbs)
		जाओ err_requests;

	i915_global_रेजिस्टर(&global.base);
	वापस 0;

err_requests:
	kmem_cache_destroy(global.slab_requests);
	वापस -ENOMEM;
पूर्ण
