<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश "i915_drv.h"
#समावेश "i915_request.h"

#समावेश "intel_context.h"
#समावेश "intel_engine_heartbeat.h"
#समावेश "intel_engine_pm.h"
#समावेश "intel_engine.h"
#समावेश "intel_gt.h"
#समावेश "intel_reset.h"

/*
 * While the engine is active, we send a periodic pulse aदीर्घ the engine
 * to check on its health and to flush any idle-barriers. If that request
 * is stuck, and we fail to preempt it, we declare the engine hung and
 * issue a reset -- in the hope that restores progress.
 */

अटल bool next_heartbeat(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	दीर्घ delay;

	delay = READ_ONCE(engine->props.heartbeat_पूर्णांकerval_ms);
	अगर (!delay)
		वापस false;

	delay = msecs_to_jअगरfies_समयout(delay);
	अगर (delay >= HZ)
		delay = round_jअगरfies_up_relative(delay);
	mod_delayed_work(प्रणाली_highpri_wq, &engine->heartbeat.work, delay + 1);

	वापस true;
पूर्ण

अटल काष्ठा i915_request *
heartbeat_create(काष्ठा पूर्णांकel_context *ce, gfp_t gfp)
अणु
	काष्ठा i915_request *rq;

	पूर्णांकel_context_enter(ce);
	rq = __i915_request_create(ce, gfp);
	पूर्णांकel_context_निकास(ce);

	वापस rq;
पूर्ण

अटल व्योम idle_pulse(काष्ठा पूर्णांकel_engine_cs *engine, काष्ठा i915_request *rq)
अणु
	engine->wakeref_serial = READ_ONCE(engine->serial) + 1;
	i915_request_add_active_barriers(rq);
	अगर (!engine->heartbeat.systole && पूर्णांकel_engine_has_heartbeat(engine))
		engine->heartbeat.systole = i915_request_get(rq);
पूर्ण

अटल व्योम heartbeat_commit(काष्ठा i915_request *rq,
			     स्थिर काष्ठा i915_sched_attr *attr)
अणु
	idle_pulse(rq->engine, rq);

	__i915_request_commit(rq);
	__i915_request_queue(rq, attr);
पूर्ण

अटल व्योम show_heartbeat(स्थिर काष्ठा i915_request *rq,
			   काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा drm_prपूर्णांकer p = drm_debug_prपूर्णांकer("heartbeat");

	पूर्णांकel_engine_dump(engine, &p,
			  "%s heartbeat {seqno:%llx:%lld, prio:%d} not ticking\n",
			  engine->name,
			  rq->fence.context,
			  rq->fence.seqno,
			  rq->sched.attr.priority);
पूर्ण

अटल व्योम heartbeat(काष्ठा work_काष्ठा *wrk)
अणु
	काष्ठा i915_sched_attr attr = अणु .priority = I915_PRIORITY_MIN पूर्ण;
	काष्ठा पूर्णांकel_engine_cs *engine =
		container_of(wrk, typeof(*engine), heartbeat.work.work);
	काष्ठा पूर्णांकel_context *ce = engine->kernel_context;
	काष्ठा i915_request *rq;
	अचिन्हित दीर्घ serial;

	/* Just in हाल everything has gone horribly wrong, give it a kick */
	पूर्णांकel_engine_flush_submission(engine);

	rq = engine->heartbeat.systole;
	अगर (rq && i915_request_completed(rq)) अणु
		i915_request_put(rq);
		engine->heartbeat.systole = शून्य;
	पूर्ण

	अगर (!पूर्णांकel_engine_pm_get_अगर_awake(engine))
		वापस;

	अगर (पूर्णांकel_gt_is_wedged(engine->gt))
		जाओ out;

	अगर (engine->heartbeat.systole) अणु
		दीर्घ delay = READ_ONCE(engine->props.heartbeat_पूर्णांकerval_ms);

		/* Safeguard against too-fast worker invocations */
		अगर (!समय_after(jअगरfies,
				rq->emitted_jअगरfies + msecs_to_jअगरfies(delay)))
			जाओ out;

		अगर (!i915_sw_fence_संकेतed(&rq->submit)) अणु
			/*
			 * Not yet submitted, प्रणाली is stalled.
			 *
			 * This more often happens क्रम ring submission,
			 * where all contexts are funnelled पूर्णांकo a common
			 * ringbuffer. If one context is blocked on an
			 * बाह्यal fence, not only is it not submitted,
			 * but all other contexts, including the kernel
			 * context are stuck रुकोing क्रम the संकेत.
			 */
		पूर्ण अन्यथा अगर (engine->schedule &&
			   rq->sched.attr.priority < I915_PRIORITY_BARRIER) अणु
			/*
			 * Gradually उठाओ the priority of the heartbeat to
			 * give high priority work [which presumably desires
			 * low latency and no jitter] the chance to naturally
			 * complete beक्रमe being preempted.
			 */
			attr.priority = 0;
			अगर (rq->sched.attr.priority >= attr.priority)
				attr.priority = I915_PRIORITY_HEARTBEAT;
			अगर (rq->sched.attr.priority >= attr.priority)
				attr.priority = I915_PRIORITY_BARRIER;

			local_bh_disable();
			engine->schedule(rq, &attr);
			local_bh_enable();
		पूर्ण अन्यथा अणु
			अगर (IS_ENABLED(CONFIG_DRM_I915_DEBUG_GEM))
				show_heartbeat(rq, engine);

			पूर्णांकel_gt_handle_error(engine->gt, engine->mask,
					      I915_ERROR_CAPTURE,
					      "stopped heartbeat on %s",
					      engine->name);
		पूर्ण

		rq->emitted_jअगरfies = jअगरfies;
		जाओ out;
	पूर्ण

	serial = READ_ONCE(engine->serial);
	अगर (engine->wakeref_serial == serial)
		जाओ out;

	अगर (!mutex_trylock(&ce->समयline->mutex)) अणु
		/* Unable to lock the kernel समयline, is the engine stuck? */
		अगर (xchg(&engine->heartbeat.blocked, serial) == serial)
			पूर्णांकel_gt_handle_error(engine->gt, engine->mask,
					      I915_ERROR_CAPTURE,
					      "no heartbeat on %s",
					      engine->name);
		जाओ out;
	पूर्ण

	rq = heartbeat_create(ce, GFP_NOWAIT | __GFP_NOWARN);
	अगर (IS_ERR(rq))
		जाओ unlock;

	heartbeat_commit(rq, &attr);

unlock:
	mutex_unlock(&ce->समयline->mutex);
out:
	अगर (!engine->i915->params.enable_hangcheck || !next_heartbeat(engine))
		i915_request_put(fetch_and_zero(&engine->heartbeat.systole));
	पूर्णांकel_engine_pm_put(engine);
पूर्ण

व्योम पूर्णांकel_engine_unpark_heartbeat(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	अगर (!IS_ACTIVE(CONFIG_DRM_I915_HEARTBEAT_INTERVAL))
		वापस;

	next_heartbeat(engine);
पूर्ण

व्योम पूर्णांकel_engine_park_heartbeat(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	अगर (cancel_delayed_work(&engine->heartbeat.work))
		i915_request_put(fetch_and_zero(&engine->heartbeat.systole));
पूर्ण

व्योम पूर्णांकel_engine_init_heartbeat(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	INIT_DELAYED_WORK(&engine->heartbeat.work, heartbeat);
पूर्ण

अटल पूर्णांक __पूर्णांकel_engine_pulse(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा i915_sched_attr attr = अणु .priority = I915_PRIORITY_BARRIER पूर्ण;
	काष्ठा पूर्णांकel_context *ce = engine->kernel_context;
	काष्ठा i915_request *rq;

	lockdep_निश्चित_held(&ce->समयline->mutex);
	GEM_BUG_ON(!पूर्णांकel_engine_has_preemption(engine));
	GEM_BUG_ON(!पूर्णांकel_engine_pm_is_awake(engine));

	rq = heartbeat_create(ce, GFP_NOWAIT | __GFP_NOWARN);
	अगर (IS_ERR(rq))
		वापस PTR_ERR(rq);

	__set_bit(I915_FENCE_FLAG_SENTINEL, &rq->fence.flags);

	heartbeat_commit(rq, &attr);
	GEM_BUG_ON(rq->sched.attr.priority < I915_PRIORITY_BARRIER);

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ set_heartbeat(काष्ठा पूर्णांकel_engine_cs *engine,
				   अचिन्हित दीर्घ delay)
अणु
	अचिन्हित दीर्घ old;

	old = xchg(&engine->props.heartbeat_पूर्णांकerval_ms, delay);
	अगर (delay)
		पूर्णांकel_engine_unpark_heartbeat(engine);
	अन्यथा
		पूर्णांकel_engine_park_heartbeat(engine);

	वापस old;
पूर्ण

पूर्णांक पूर्णांकel_engine_set_heartbeat(काष्ठा पूर्णांकel_engine_cs *engine,
			       अचिन्हित दीर्घ delay)
अणु
	काष्ठा पूर्णांकel_context *ce = engine->kernel_context;
	पूर्णांक err = 0;

	अगर (!delay && !पूर्णांकel_engine_has_preempt_reset(engine))
		वापस -ENODEV;

	पूर्णांकel_engine_pm_get(engine);

	err = mutex_lock_पूर्णांकerruptible(&ce->समयline->mutex);
	अगर (err)
		जाओ out_rpm;

	अगर (delay != engine->props.heartbeat_पूर्णांकerval_ms) अणु
		अचिन्हित दीर्घ saved = set_heartbeat(engine, delay);

		/* recheck current execution */
		अगर (पूर्णांकel_engine_has_preemption(engine)) अणु
			err = __पूर्णांकel_engine_pulse(engine);
			अगर (err)
				set_heartbeat(engine, saved);
		पूर्ण
	पूर्ण

	mutex_unlock(&ce->समयline->mutex);

out_rpm:
	पूर्णांकel_engine_pm_put(engine);
	वापस err;
पूर्ण

पूर्णांक पूर्णांकel_engine_pulse(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_context *ce = engine->kernel_context;
	पूर्णांक err;

	अगर (!पूर्णांकel_engine_has_preemption(engine))
		वापस -ENODEV;

	अगर (!पूर्णांकel_engine_pm_get_अगर_awake(engine))
		वापस 0;

	err = -EINTR;
	अगर (!mutex_lock_पूर्णांकerruptible(&ce->समयline->mutex)) अणु
		err = __पूर्णांकel_engine_pulse(engine);
		mutex_unlock(&ce->समयline->mutex);
	पूर्ण

	पूर्णांकel_engine_flush_submission(engine);
	पूर्णांकel_engine_pm_put(engine);
	वापस err;
पूर्ण

पूर्णांक पूर्णांकel_engine_flush_barriers(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा i915_sched_attr attr = अणु .priority = I915_PRIORITY_MIN पूर्ण;
	काष्ठा पूर्णांकel_context *ce = engine->kernel_context;
	काष्ठा i915_request *rq;
	पूर्णांक err;

	अगर (llist_empty(&engine->barrier_tasks))
		वापस 0;

	अगर (!पूर्णांकel_engine_pm_get_अगर_awake(engine))
		वापस 0;

	अगर (mutex_lock_पूर्णांकerruptible(&ce->समयline->mutex)) अणु
		err = -EINTR;
		जाओ out_rpm;
	पूर्ण

	rq = heartbeat_create(ce, GFP_KERNEL);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ out_unlock;
	पूर्ण

	heartbeat_commit(rq, &attr);

	err = 0;
out_unlock:
	mutex_unlock(&ce->समयline->mutex);
out_rpm:
	पूर्णांकel_engine_pm_put(engine);
	वापस err;
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "selftest_engine_heartbeat.c"
#पूर्ण_अगर
