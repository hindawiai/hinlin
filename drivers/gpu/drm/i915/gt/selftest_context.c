<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश "i915_selftest.h"
#समावेश "intel_engine_heartbeat.h"
#समावेश "intel_engine_pm.h"
#समावेश "intel_gt.h"

#समावेश "gem/selftests/mock_context.h"
#समावेश "selftests/igt_flush_test.h"
#समावेश "selftests/mock_drm.h"

अटल पूर्णांक request_sync(काष्ठा i915_request *rq)
अणु
	काष्ठा पूर्णांकel_समयline *tl = i915_request_समयline(rq);
	दीर्घ समयout;
	पूर्णांक err = 0;

	पूर्णांकel_समयline_get(tl);
	i915_request_get(rq);

	/* Opencode i915_request_add() so we can keep the समयline locked. */
	__i915_request_commit(rq);
	rq->sched.attr.priority = I915_PRIORITY_BARRIER;
	__i915_request_queue_bh(rq);

	समयout = i915_request_रुको(rq, 0, HZ / 10);
	अगर (समयout < 0)
		err = समयout;
	अन्यथा
		i915_request_retire_upto(rq);

	lockdep_unpin_lock(&tl->mutex, rq->cookie);
	mutex_unlock(&tl->mutex);

	i915_request_put(rq);
	पूर्णांकel_समयline_put(tl);

	वापस err;
पूर्ण

अटल पूर्णांक context_sync(काष्ठा पूर्णांकel_context *ce)
अणु
	काष्ठा पूर्णांकel_समयline *tl = ce->समयline;
	पूर्णांक err = 0;

	mutex_lock(&tl->mutex);
	करो अणु
		काष्ठा i915_request *rq;
		दीर्घ समयout;

		अगर (list_empty(&tl->requests))
			अवरोध;

		rq = list_last_entry(&tl->requests, typeof(*rq), link);
		i915_request_get(rq);

		समयout = i915_request_रुको(rq, 0, HZ / 10);
		अगर (समयout < 0)
			err = समयout;
		अन्यथा
			i915_request_retire_upto(rq);

		i915_request_put(rq);
	पूर्ण जबतक (!err);
	mutex_unlock(&tl->mutex);

	/* Wait क्रम all barriers to complete (remote CPU) beक्रमe we check */
	i915_active_unlock_रुको(&ce->active);
	वापस err;
पूर्ण

अटल पूर्णांक __live_context_size(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_context *ce;
	काष्ठा i915_request *rq;
	व्योम *vaddr;
	पूर्णांक err;

	ce = पूर्णांकel_context_create(engine);
	अगर (IS_ERR(ce))
		वापस PTR_ERR(ce);

	err = पूर्णांकel_context_pin(ce);
	अगर (err)
		जाओ err;

	vaddr = i915_gem_object_pin_map_unlocked(ce->state->obj,
						 i915_coherent_map_type(engine->i915));
	अगर (IS_ERR(vaddr)) अणु
		err = PTR_ERR(vaddr);
		पूर्णांकel_context_unpin(ce);
		जाओ err;
	पूर्ण

	/*
	 * Note that execlists also applies a redzone which it checks on
	 * context unpin when debugging. We are using the same location
	 * and same poison value so that our checks overlap. Despite the
	 * redundancy, we want to keep this little selftest so that we
	 * get coverage of any and all submission backends, and we can
	 * always extend this test to ensure we trick the HW पूर्णांकo a
	 * compromising position wrt to the various sections that need
	 * to be written पूर्णांकo the context state.
	 *
	 * TLDR; this overlaps with the execlists redzone.
	 */
	vaddr += engine->context_size - I915_GTT_PAGE_SIZE;
	स_रखो(vaddr, POISON_INUSE, I915_GTT_PAGE_SIZE);

	rq = पूर्णांकel_context_create_request(ce);
	पूर्णांकel_context_unpin(ce);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ err_unpin;
	पूर्ण

	err = request_sync(rq);
	अगर (err)
		जाओ err_unpin;

	/* Force the context चयन */
	rq = पूर्णांकel_engine_create_kernel_request(engine);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ err_unpin;
	पूर्ण
	err = request_sync(rq);
	अगर (err)
		जाओ err_unpin;

	अगर (स_प्रथम_inv(vaddr, POISON_INUSE, I915_GTT_PAGE_SIZE)) अणु
		pr_err("%s context overwrote trailing red-zone!", engine->name);
		err = -EINVAL;
	पूर्ण

err_unpin:
	i915_gem_object_unpin_map(ce->state->obj);
err:
	पूर्णांकel_context_put(ce);
	वापस err;
पूर्ण

अटल पूर्णांक live_context_size(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err = 0;

	/*
	 * Check that our context sizes are correct by seeing अगर the
	 * HW tries to ग_लिखो past the end of one.
	 */

	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा file *saved;

		अगर (!engine->context_size)
			जारी;

		पूर्णांकel_engine_pm_get(engine);

		/*
		 * Hide the old शेष state -- we lie about the context size
		 * and get confused when the शेष state is smaller than
		 * expected. For our करो nothing request, inheriting the
		 * active state is sufficient, we are only checking that we
		 * करोn't use more than we planned.
		 */
		saved = fetch_and_zero(&engine->शेष_state);

		/* Overlaps with the execlists redzone */
		engine->context_size += I915_GTT_PAGE_SIZE;

		err = __live_context_size(engine);

		engine->context_size -= I915_GTT_PAGE_SIZE;

		engine->शेष_state = saved;

		पूर्णांकel_engine_pm_put(engine);

		अगर (err)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक __live_active_context(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	अचिन्हित दीर्घ saved_heartbeat;
	काष्ठा पूर्णांकel_context *ce;
	पूर्णांक pass;
	पूर्णांक err;

	/*
	 * We keep active contexts alive until after a subsequent context
	 * चयन as the final ग_लिखो from the context-save will be after
	 * we retire the final request. We track when we unpin the context,
	 * under the presumption that the final pin is from the last request,
	 * and instead of immediately unpinning the context, we add a task
	 * to unpin the context from the next idle-barrier.
	 *
	 * This test makes sure that the context is kept alive until a
	 * subsequent idle-barrier (emitted when the engine wakeref hits 0
	 * with no more outstanding requests).
	 */

	अगर (पूर्णांकel_engine_pm_is_awake(engine)) अणु
		pr_err("%s is awake before starting %s!\n",
		       engine->name, __func__);
		वापस -EINVAL;
	पूर्ण

	ce = पूर्णांकel_context_create(engine);
	अगर (IS_ERR(ce))
		वापस PTR_ERR(ce);

	saved_heartbeat = engine->props.heartbeat_पूर्णांकerval_ms;
	engine->props.heartbeat_पूर्णांकerval_ms = 0;

	क्रम (pass = 0; pass <= 2; pass++) अणु
		काष्ठा i915_request *rq;

		पूर्णांकel_engine_pm_get(engine);

		rq = पूर्णांकel_context_create_request(ce);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			जाओ out_engine;
		पूर्ण

		err = request_sync(rq);
		अगर (err)
			जाओ out_engine;

		/* Context will be kept active until after an idle-barrier. */
		अगर (i915_active_is_idle(&ce->active)) अणु
			pr_err("context is not active; expected idle-barrier (%s pass %d)\n",
			       engine->name, pass);
			err = -EINVAL;
			जाओ out_engine;
		पूर्ण

		अगर (!पूर्णांकel_engine_pm_is_awake(engine)) अणु
			pr_err("%s is asleep before idle-barrier\n",
			       engine->name);
			err = -EINVAL;
			जाओ out_engine;
		पूर्ण

out_engine:
		पूर्णांकel_engine_pm_put(engine);
		अगर (err)
			जाओ err;
	पूर्ण

	/* Now make sure our idle-barriers are flushed */
	err = पूर्णांकel_engine_flush_barriers(engine);
	अगर (err)
		जाओ err;

	/* Wait क्रम the barrier and in the process रुको क्रम engine to park */
	err = context_sync(engine->kernel_context);
	अगर (err)
		जाओ err;

	अगर (!i915_active_is_idle(&ce->active)) अणु
		pr_err("context is still active!");
		err = -EINVAL;
	पूर्ण

	पूर्णांकel_engine_pm_flush(engine);

	अगर (पूर्णांकel_engine_pm_is_awake(engine)) अणु
		काष्ठा drm_prपूर्णांकer p = drm_debug_prपूर्णांकer(__func__);

		पूर्णांकel_engine_dump(engine, &p,
				  "%s is still awake:%d after idle-barriers\n",
				  engine->name,
				  atomic_पढ़ो(&engine->wakeref.count));
		GEM_TRACE_DUMP();

		err = -EINVAL;
		जाओ err;
	पूर्ण

err:
	engine->props.heartbeat_पूर्णांकerval_ms = saved_heartbeat;
	पूर्णांकel_context_put(ce);
	वापस err;
पूर्ण

अटल पूर्णांक live_active_context(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err = 0;

	क्रम_each_engine(engine, gt, id) अणु
		err = __live_active_context(engine);
		अगर (err)
			अवरोध;

		err = igt_flush_test(gt->i915);
		अगर (err)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक __remote_sync(काष्ठा पूर्णांकel_context *ce, काष्ठा पूर्णांकel_context *remote)
अणु
	काष्ठा i915_request *rq;
	पूर्णांक err;

	err = पूर्णांकel_context_pin(remote);
	अगर (err)
		वापस err;

	rq = पूर्णांकel_context_create_request(ce);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ unpin;
	पूर्ण

	err = पूर्णांकel_context_prepare_remote_request(remote, rq);
	अगर (err) अणु
		i915_request_add(rq);
		जाओ unpin;
	पूर्ण

	err = request_sync(rq);

unpin:
	पूर्णांकel_context_unpin(remote);
	वापस err;
पूर्ण

अटल पूर्णांक __live_remote_context(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_context *local, *remote;
	अचिन्हित दीर्घ saved_heartbeat;
	पूर्णांक pass;
	पूर्णांक err;

	/*
	 * Check that our idle barriers करो not पूर्णांकerfere with normal
	 * activity tracking. In particular, check that operating
	 * on the context image remotely (पूर्णांकel_context_prepare_remote_request),
	 * which inserts क्रमeign fences पूर्णांकo पूर्णांकel_context.active, करोes not
	 * clobber the idle-barrier.
	 */

	अगर (पूर्णांकel_engine_pm_is_awake(engine)) अणु
		pr_err("%s is awake before starting %s!\n",
		       engine->name, __func__);
		वापस -EINVAL;
	पूर्ण

	remote = पूर्णांकel_context_create(engine);
	अगर (IS_ERR(remote))
		वापस PTR_ERR(remote);

	local = पूर्णांकel_context_create(engine);
	अगर (IS_ERR(local)) अणु
		err = PTR_ERR(local);
		जाओ err_remote;
	पूर्ण

	saved_heartbeat = engine->props.heartbeat_पूर्णांकerval_ms;
	engine->props.heartbeat_पूर्णांकerval_ms = 0;
	पूर्णांकel_engine_pm_get(engine);

	क्रम (pass = 0; pass <= 2; pass++) अणु
		err = __remote_sync(local, remote);
		अगर (err)
			अवरोध;

		err = __remote_sync(engine->kernel_context, remote);
		अगर (err)
			अवरोध;

		अगर (i915_active_is_idle(&remote->active)) अणु
			pr_err("remote context is not active; expected idle-barrier (%s pass %d)\n",
			       engine->name, pass);
			err = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण

	पूर्णांकel_engine_pm_put(engine);
	engine->props.heartbeat_पूर्णांकerval_ms = saved_heartbeat;

	पूर्णांकel_context_put(local);
err_remote:
	पूर्णांकel_context_put(remote);
	वापस err;
पूर्ण

अटल पूर्णांक live_remote_context(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err = 0;

	क्रम_each_engine(engine, gt, id) अणु
		err = __live_remote_context(engine);
		अगर (err)
			अवरोध;

		err = igt_flush_test(gt->i915);
		अगर (err)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक पूर्णांकel_context_live_selftests(काष्ठा drm_i915_निजी *i915)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(live_context_size),
		SUBTEST(live_active_context),
		SUBTEST(live_remote_context),
	पूर्ण;
	काष्ठा पूर्णांकel_gt *gt = &i915->gt;

	अगर (पूर्णांकel_gt_is_wedged(gt))
		वापस 0;

	वापस पूर्णांकel_gt_live_subtests(tests, gt);
पूर्ण
