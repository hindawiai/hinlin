<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2018 Intel Corporation
 */

#समावेश <linux/sort.h>

#समावेश "i915_drv.h"

#समावेश "intel_gt_requests.h"
#समावेश "i915_selftest.h"
#समावेश "selftest_engine_heartbeat.h"

अटल व्योम reset_heartbeat(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	पूर्णांकel_engine_set_heartbeat(engine,
				   engine->शेषs.heartbeat_पूर्णांकerval_ms);
पूर्ण

अटल पूर्णांक समयline_sync(काष्ठा पूर्णांकel_समयline *tl)
अणु
	काष्ठा dma_fence *fence;
	दीर्घ समयout;

	fence = i915_active_fence_get(&tl->last_request);
	अगर (!fence)
		वापस 0;

	समयout = dma_fence_रुको_समयout(fence, true, HZ / 2);
	dma_fence_put(fence);
	अगर (समयout < 0)
		वापस समयout;

	वापस 0;
पूर्ण

अटल पूर्णांक engine_sync_barrier(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	वापस समयline_sync(engine->kernel_context->समयline);
पूर्ण

काष्ठा pulse अणु
	काष्ठा i915_active active;
	काष्ठा kref kref;
पूर्ण;

अटल पूर्णांक pulse_active(काष्ठा i915_active *active)
अणु
	kref_get(&container_of(active, काष्ठा pulse, active)->kref);
	वापस 0;
पूर्ण

अटल व्योम pulse_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा pulse *p = container_of(kref, typeof(*p), kref);

	i915_active_fini(&p->active);
	kमुक्त(p);
पूर्ण

अटल व्योम pulse_put(काष्ठा pulse *p)
अणु
	kref_put(&p->kref, pulse_मुक्त);
पूर्ण

अटल व्योम pulse_retire(काष्ठा i915_active *active)
अणु
	pulse_put(container_of(active, काष्ठा pulse, active));
पूर्ण

अटल काष्ठा pulse *pulse_create(व्योम)
अणु
	काष्ठा pulse *p;

	p = kदो_स्मृति(माप(*p), GFP_KERNEL);
	अगर (!p)
		वापस p;

	kref_init(&p->kref);
	i915_active_init(&p->active, pulse_active, pulse_retire);

	वापस p;
पूर्ण

अटल व्योम pulse_unlock_रुको(काष्ठा pulse *p)
अणु
	i915_active_unlock_रुको(&p->active);
पूर्ण

अटल पूर्णांक __live_idle_pulse(काष्ठा पूर्णांकel_engine_cs *engine,
			     पूर्णांक (*fn)(काष्ठा पूर्णांकel_engine_cs *cs))
अणु
	काष्ठा pulse *p;
	पूर्णांक err;

	GEM_BUG_ON(!पूर्णांकel_engine_pm_is_awake(engine));

	p = pulse_create();
	अगर (!p)
		वापस -ENOMEM;

	err = i915_active_acquire(&p->active);
	अगर (err)
		जाओ out;

	err = i915_active_acquire_pपुनः_स्मृतिate_barrier(&p->active, engine);
	अगर (err) अणु
		i915_active_release(&p->active);
		जाओ out;
	पूर्ण

	i915_active_acquire_barrier(&p->active);
	i915_active_release(&p->active);

	GEM_BUG_ON(i915_active_is_idle(&p->active));
	GEM_BUG_ON(llist_empty(&engine->barrier_tasks));

	err = fn(engine);
	अगर (err)
		जाओ out;

	GEM_BUG_ON(!llist_empty(&engine->barrier_tasks));

	अगर (engine_sync_barrier(engine)) अणु
		काष्ठा drm_prपूर्णांकer m = drm_err_prपूर्णांकer("pulse");

		pr_err("%s: no heartbeat pulse?\n", engine->name);
		पूर्णांकel_engine_dump(engine, &m, "%s", engine->name);

		err = -ETIME;
		जाओ out;
	पूर्ण

	GEM_BUG_ON(READ_ONCE(engine->serial) != engine->wakeref_serial);

	pulse_unlock_रुको(p); /* synchronize with the retirement callback */

	अगर (!i915_active_is_idle(&p->active)) अणु
		काष्ठा drm_prपूर्णांकer m = drm_err_prपूर्णांकer("pulse");

		pr_err("%s: heartbeat pulse did not flush idle tasks\n",
		       engine->name);
		i915_active_prपूर्णांक(&p->active, &m);

		err = -EINVAL;
		जाओ out;
	पूर्ण

out:
	pulse_put(p);
	वापस err;
पूर्ण

अटल पूर्णांक live_idle_flush(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err = 0;

	/* Check that we can flush the idle barriers */

	क्रम_each_engine(engine, gt, id) अणु
		st_engine_heartbeat_disable(engine);
		err = __live_idle_pulse(engine, पूर्णांकel_engine_flush_barriers);
		st_engine_heartbeat_enable(engine);
		अगर (err)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक live_idle_pulse(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err = 0;

	/* Check that heartbeat pulses flush the idle barriers */

	क्रम_each_engine(engine, gt, id) अणु
		st_engine_heartbeat_disable(engine);
		err = __live_idle_pulse(engine, पूर्णांकel_engine_pulse);
		st_engine_heartbeat_enable(engine);
		अगर (err && err != -ENODEV)
			अवरोध;

		err = 0;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक cmp_u32(स्थिर व्योम *_a, स्थिर व्योम *_b)
अणु
	स्थिर u32 *a = _a, *b = _b;

	वापस *a - *b;
पूर्ण

अटल पूर्णांक __live_heartbeat_fast(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	स्थिर अचिन्हित पूर्णांक error_threshold = max(20000u, jअगरfies_to_usecs(6));
	काष्ठा पूर्णांकel_context *ce;
	काष्ठा i915_request *rq;
	kसमय_प्रकार t0, t1;
	u32 बार[5];
	पूर्णांक err;
	पूर्णांक i;

	ce = पूर्णांकel_context_create(engine);
	अगर (IS_ERR(ce))
		वापस PTR_ERR(ce);

	पूर्णांकel_engine_pm_get(engine);

	err = पूर्णांकel_engine_set_heartbeat(engine, 1);
	अगर (err)
		जाओ err_pm;

	क्रम (i = 0; i < ARRAY_SIZE(बार); i++) अणु
		करो अणु
			/* Manufacture a tick */
			पूर्णांकel_engine_park_heartbeat(engine);
			GEM_BUG_ON(engine->heartbeat.systole);
			engine->serial++; /*  pretend we are not idle! */
			पूर्णांकel_engine_unpark_heartbeat(engine);

			flush_delayed_work(&engine->heartbeat.work);
			अगर (!delayed_work_pending(&engine->heartbeat.work)) अणु
				pr_err("%s: heartbeat %d did not start\n",
				       engine->name, i);
				err = -EINVAL;
				जाओ err_pm;
			पूर्ण

			rcu_पढ़ो_lock();
			rq = READ_ONCE(engine->heartbeat.systole);
			अगर (rq)
				rq = i915_request_get_rcu(rq);
			rcu_पढ़ो_unlock();
		पूर्ण जबतक (!rq);

		t0 = kसमय_get();
		जबतक (rq == READ_ONCE(engine->heartbeat.systole))
			yield(); /* work is on the local cpu! */
		t1 = kसमय_get();

		i915_request_put(rq);
		बार[i] = kसमय_us_delta(t1, t0);
	पूर्ण

	sort(बार, ARRAY_SIZE(बार), माप(बार[0]), cmp_u32, शून्य);

	pr_info("%s: Heartbeat delay: %uus [%u, %u]\n",
		engine->name,
		बार[ARRAY_SIZE(बार) / 2],
		बार[0],
		बार[ARRAY_SIZE(बार) - 1]);

	/*
	 * Ideally, the upper bound on min work delay would be something like
	 * 2 * 2 (worst), +1 क्रम scheduling, +1 क्रम slack. In practice, we
	 * are, even with प्रणाली_wq_highpri, at the mercy of the CPU scheduler
	 * and may be stuck behind some slow work क्रम many millisecond. Such
	 * as our very own display workers.
	 */
	अगर (बार[ARRAY_SIZE(बार) / 2] > error_threshold) अणु
		pr_err("%s: Heartbeat delay was %uus, expected less than %dus\n",
		       engine->name,
		       बार[ARRAY_SIZE(बार) / 2],
		       error_threshold);
		err = -EINVAL;
	पूर्ण

	reset_heartbeat(engine);
err_pm:
	पूर्णांकel_engine_pm_put(engine);
	पूर्णांकel_context_put(ce);
	वापस err;
पूर्ण

अटल पूर्णांक live_heartbeat_fast(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err = 0;

	/* Check that the heartbeat ticks at the desired rate. */
	अगर (!IS_ACTIVE(CONFIG_DRM_I915_HEARTBEAT_INTERVAL))
		वापस 0;

	क्रम_each_engine(engine, gt, id) अणु
		err = __live_heartbeat_fast(engine);
		अगर (err)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक __live_heartbeat_off(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	पूर्णांक err;

	पूर्णांकel_engine_pm_get(engine);

	engine->serial++;
	flush_delayed_work(&engine->heartbeat.work);
	अगर (!delayed_work_pending(&engine->heartbeat.work)) अणु
		pr_err("%s: heartbeat not running\n",
		       engine->name);
		err = -EINVAL;
		जाओ err_pm;
	पूर्ण

	err = पूर्णांकel_engine_set_heartbeat(engine, 0);
	अगर (err)
		जाओ err_pm;

	engine->serial++;
	flush_delayed_work(&engine->heartbeat.work);
	अगर (delayed_work_pending(&engine->heartbeat.work)) अणु
		pr_err("%s: heartbeat still running\n",
		       engine->name);
		err = -EINVAL;
		जाओ err_beat;
	पूर्ण

	अगर (READ_ONCE(engine->heartbeat.systole)) अणु
		pr_err("%s: heartbeat still allocated\n",
		       engine->name);
		err = -EINVAL;
		जाओ err_beat;
	पूर्ण

err_beat:
	reset_heartbeat(engine);
err_pm:
	पूर्णांकel_engine_pm_put(engine);
	वापस err;
पूर्ण

अटल पूर्णांक live_heartbeat_off(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err = 0;

	/* Check that we can turn off heartbeat and not पूर्णांकerrupt VIP */
	अगर (!IS_ACTIVE(CONFIG_DRM_I915_HEARTBEAT_INTERVAL))
		वापस 0;

	क्रम_each_engine(engine, gt, id) अणु
		अगर (!पूर्णांकel_engine_has_preemption(engine))
			जारी;

		err = __live_heartbeat_off(engine);
		अगर (err)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक पूर्णांकel_heartbeat_live_selftests(काष्ठा drm_i915_निजी *i915)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(live_idle_flush),
		SUBTEST(live_idle_pulse),
		SUBTEST(live_heartbeat_fast),
		SUBTEST(live_heartbeat_off),
	पूर्ण;
	पूर्णांक saved_hangcheck;
	पूर्णांक err;

	अगर (पूर्णांकel_gt_is_wedged(&i915->gt))
		वापस 0;

	saved_hangcheck = i915->params.enable_hangcheck;
	i915->params.enable_hangcheck = पूर्णांक_उच्च;

	err = पूर्णांकel_gt_live_subtests(tests, &i915->gt);

	i915->params.enable_hangcheck = saved_hangcheck;
	वापस err;
पूर्ण

व्योम st_engine_heartbeat_disable(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	engine->props.heartbeat_पूर्णांकerval_ms = 0;

	पूर्णांकel_engine_pm_get(engine);
	पूर्णांकel_engine_park_heartbeat(engine);
पूर्ण

व्योम st_engine_heartbeat_enable(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	पूर्णांकel_engine_pm_put(engine);

	engine->props.heartbeat_पूर्णांकerval_ms =
		engine->शेषs.heartbeat_पूर्णांकerval_ms;
पूर्ण
