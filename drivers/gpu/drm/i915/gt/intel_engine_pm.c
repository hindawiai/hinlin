<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश "i915_drv.h"

#समावेश "intel_breadcrumbs.h"
#समावेश "intel_context.h"
#समावेश "intel_engine.h"
#समावेश "intel_engine_heartbeat.h"
#समावेश "intel_engine_pm.h"
#समावेश "intel_gt.h"
#समावेश "intel_gt_pm.h"
#समावेश "intel_rc6.h"
#समावेश "intel_ring.h"
#समावेश "shmem_utils.h"

अटल व्योम dbg_poison_ce(काष्ठा पूर्णांकel_context *ce)
अणु
	अगर (!IS_ENABLED(CONFIG_DRM_I915_DEBUG_GEM))
		वापस;

	अगर (ce->state) अणु
		काष्ठा drm_i915_gem_object *obj = ce->state->obj;
		पूर्णांक type = i915_coherent_map_type(ce->engine->i915);
		व्योम *map;

		अगर (!i915_gem_object_trylock(obj))
			वापस;

		map = i915_gem_object_pin_map(obj, type);
		अगर (!IS_ERR(map)) अणु
			स_रखो(map, CONTEXT_REDZONE, obj->base.size);
			i915_gem_object_flush_map(obj);
			i915_gem_object_unpin_map(obj);
		पूर्ण
		i915_gem_object_unlock(obj);
	पूर्ण
पूर्ण

अटल पूर्णांक __engine_unpark(काष्ठा पूर्णांकel_wakeref *wf)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine =
		container_of(wf, typeof(*engine), wakeref);
	काष्ठा पूर्णांकel_context *ce;

	ENGINE_TRACE(engine, "\n");

	पूर्णांकel_gt_pm_get(engine->gt);

	/* Discard stale context state from across idling */
	ce = engine->kernel_context;
	अगर (ce) अणु
		GEM_BUG_ON(test_bit(CONTEXT_VALID_BIT, &ce->flags));

		/* Flush all pending HW ग_लिखोs beक्रमe we touch the context */
		जबतक (unlikely(पूर्णांकel_context_inflight(ce)))
			पूर्णांकel_engine_flush_submission(engine);

		/* First poison the image to verअगरy we never fully trust it */
		dbg_poison_ce(ce);

		/* Scrub the context image after our loss of control */
		ce->ops->reset(ce);

		CE_TRACE(ce, "reset { seqno:%x, *hwsp:%x, ring:%x }\n",
			 ce->समयline->seqno,
			 READ_ONCE(*ce->समयline->hwsp_seqno),
			 ce->ring->emit);
		GEM_BUG_ON(ce->समयline->seqno !=
			   READ_ONCE(*ce->समयline->hwsp_seqno));
	पूर्ण

	अगर (engine->unpark)
		engine->unpark(engine);

	पूर्णांकel_bपढ़ोcrumbs_unpark(engine->bपढ़ोcrumbs);
	पूर्णांकel_engine_unpark_heartbeat(engine);
	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_LOCKDEP)

अटल अचिन्हित दीर्घ __समयline_mark_lock(काष्ठा पूर्णांकel_context *ce)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	mutex_acquire(&ce->समयline->mutex.dep_map, 2, 0, _THIS_IP_);

	वापस flags;
पूर्ण

अटल व्योम __समयline_mark_unlock(काष्ठा पूर्णांकel_context *ce,
				   अचिन्हित दीर्घ flags)
अणु
	mutex_release(&ce->समयline->mutex.dep_map, _THIS_IP_);
	local_irq_restore(flags);
पूर्ण

#अन्यथा

अटल अचिन्हित दीर्घ __समयline_mark_lock(काष्ठा पूर्णांकel_context *ce)
अणु
	वापस 0;
पूर्ण

अटल व्योम __समयline_mark_unlock(काष्ठा पूर्णांकel_context *ce,
				   अचिन्हित दीर्घ flags)
अणु
पूर्ण

#पूर्ण_अगर /* !IS_ENABLED(CONFIG_LOCKDEP) */

अटल व्योम duration(काष्ठा dma_fence *fence, काष्ठा dma_fence_cb *cb)
अणु
	काष्ठा i915_request *rq = to_request(fence);

	ewma__engine_latency_add(&rq->engine->latency,
				 kसमय_us_delta(rq->fence.बारtamp,
						rq->duration.emitted));
पूर्ण

अटल व्योम
__queue_and_release_pm(काष्ठा i915_request *rq,
		       काष्ठा पूर्णांकel_समयline *tl,
		       काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_gt_समयlines *समयlines = &engine->gt->समयlines;

	ENGINE_TRACE(engine, "parking\n");

	/*
	 * We have to serialise all potential retirement paths with our
	 * submission, as we करोn't want to underflow either the
	 * engine->wakeref.counter or our समयline->active_count.
	 *
	 * Equally, we cannot allow a new submission to start until
	 * after we finish queueing, nor could we allow that submitter
	 * to retire us beक्रमe we are पढ़ोy!
	 */
	spin_lock(&समयlines->lock);

	/* Let पूर्णांकel_gt_retire_requests() retire us (acquired under lock) */
	अगर (!atomic_fetch_inc(&tl->active_count))
		list_add_tail(&tl->link, &समयlines->active_list);

	/* Hand the request over to HW and so engine_retire() */
	__i915_request_queue_bh(rq);

	/* Let new submissions commence (and maybe retire this समयline) */
	__पूर्णांकel_wakeref_defer_park(&engine->wakeref);

	spin_unlock(&समयlines->lock);
पूर्ण

अटल bool चयन_to_kernel_context(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_context *ce = engine->kernel_context;
	काष्ठा i915_request *rq;
	अचिन्हित दीर्घ flags;
	bool result = true;

	/* GPU is poपूर्णांकing to the व्योम, as good as in the kernel context. */
	अगर (पूर्णांकel_gt_is_wedged(engine->gt))
		वापस true;

	GEM_BUG_ON(!पूर्णांकel_context_is_barrier(ce));
	GEM_BUG_ON(ce->समयline->hwsp_ggtt != engine->status_page.vma);

	/* Alपढ़ोy inside the kernel context, safe to घातer करोwn. */
	अगर (engine->wakeref_serial == engine->serial)
		वापस true;

	/*
	 * Note, we करो this without taking the समयline->mutex. We cannot
	 * as we may be called जबतक retiring the kernel context and so
	 * alपढ़ोy underneath the समयline->mutex. Instead we rely on the
	 * exclusive property of the __engine_park that prevents anyone
	 * अन्यथा from creating a request on this engine. This also requires
	 * that the ring is empty and we aव्योम any रुकोs जबतक स्थिरructing
	 * the context, as they assume protection by the समयline->mutex.
	 * This should hold true as we can only park the engine after
	 * retiring the last request, thus all rings should be empty and
	 * all समयlines idle.
	 *
	 * For unlocking, there are 2 other parties and the GPU who have a
	 * stake here.
	 *
	 * A new gpu user will be रुकोing on the engine-pm to start their
	 * engine_unpark. New रुकोers are predicated on engine->wakeref.count
	 * and so पूर्णांकel_wakeref_defer_park() acts like a mutex_unlock of the
	 * engine->wakeref.
	 *
	 * The other party is पूर्णांकel_gt_retire_requests(), which is walking the
	 * list of active समयlines looking क्रम completions. Meanजबतक as soon
	 * as we call __i915_request_queue(), the GPU may complete our request.
	 * Ergo, अगर we put ourselves on the समयlines.active_list
	 * (se पूर्णांकel_समयline_enter()) beक्रमe we increment the
	 * engine->wakeref.count, we may see the request completion and retire
	 * it causing an underflow of the engine->wakeref.
	 */
	flags = __समयline_mark_lock(ce);
	GEM_BUG_ON(atomic_पढ़ो(&ce->समयline->active_count) < 0);

	rq = __i915_request_create(ce, GFP_NOWAIT);
	अगर (IS_ERR(rq))
		/* Context चयन failed, hope क्रम the best! Maybe reset? */
		जाओ out_unlock;

	/* Check again on the next retirement. */
	engine->wakeref_serial = engine->serial + 1;
	i915_request_add_active_barriers(rq);

	/* Install ourselves as a preemption barrier */
	rq->sched.attr.priority = I915_PRIORITY_BARRIER;
	अगर (likely(!__i915_request_commit(rq))) अणु /* engine should be idle! */
		/*
		 * Use an पूर्णांकerrupt क्रम precise measurement of duration,
		 * otherwise we rely on someone अन्यथा retiring all the requests
		 * which may delay the संकेतing (i.e. we will likely रुको
		 * until the background request retirement running every
		 * second or two).
		 */
		BUILD_BUG_ON(माप(rq->duration) > माप(rq->submitq));
		dma_fence_add_callback(&rq->fence, &rq->duration.cb, duration);
		rq->duration.emitted = kसमय_get();
	पूर्ण

	/* Expose ourselves to the world */
	__queue_and_release_pm(rq, ce->समयline, engine);

	result = false;
out_unlock:
	__समयline_mark_unlock(ce, flags);
	वापस result;
पूर्ण

अटल व्योम call_idle_barriers(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा llist_node *node, *next;

	llist_क्रम_each_safe(node, next, llist_del_all(&engine->barrier_tasks)) अणु
		काष्ठा dma_fence_cb *cb =
			container_of((काष्ठा list_head *)node,
				     typeof(*cb), node);

		cb->func(ERR_PTR(-EAGAIN), cb);
	पूर्ण
पूर्ण

अटल पूर्णांक __engine_park(काष्ठा पूर्णांकel_wakeref *wf)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine =
		container_of(wf, typeof(*engine), wakeref);

	engine->saturated = 0;

	/*
	 * If one and only one request is completed between pm events,
	 * we know that we are inside the kernel context and it is
	 * safe to घातer करोwn. (We are paranoid in हाल that runसमय
	 * suspend causes corruption to the active context image, and
	 * want to aव्योम that impacting userspace.)
	 */
	अगर (!चयन_to_kernel_context(engine))
		वापस -EBUSY;

	ENGINE_TRACE(engine, "parked\n");

	call_idle_barriers(engine); /* cleanup after wedging */

	पूर्णांकel_engine_park_heartbeat(engine);
	पूर्णांकel_bपढ़ोcrumbs_park(engine->bपढ़ोcrumbs);

	/* Must be reset upon idling, or we may miss the busy wakeup. */
	GEM_BUG_ON(engine->execlists.queue_priority_hपूर्णांक != पूर्णांक_न्यून);

	अगर (engine->park)
		engine->park(engine);

	engine->execlists.no_priolist = false;

	/* While gt calls i915_vma_parked(), we have to अवरोध the lock cycle */
	पूर्णांकel_gt_pm_put_async(engine->gt);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_wakeref_ops wf_ops = अणु
	.get = __engine_unpark,
	.put = __engine_park,
पूर्ण;

व्योम पूर्णांकel_engine_init__pm(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_runसमय_pm *rpm = engine->uncore->rpm;

	पूर्णांकel_wakeref_init(&engine->wakeref, rpm, &wf_ops);
	पूर्णांकel_engine_init_heartbeat(engine);
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "selftest_engine_pm.c"
#पूर्ण_अगर
