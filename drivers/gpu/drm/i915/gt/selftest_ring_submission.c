<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#समावेश "intel_engine_pm.h"
#समावेश "selftests/igt_flush_test.h"

अटल काष्ठा i915_vma *create_wally(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_vma *vma;
	u32 *cs;
	पूर्णांक err;

	obj = i915_gem_object_create_पूर्णांकernal(engine->i915, 4096);
	अगर (IS_ERR(obj))
		वापस ERR_CAST(obj);

	vma = i915_vma_instance(obj, engine->gt->vm, शून्य);
	अगर (IS_ERR(vma)) अणु
		i915_gem_object_put(obj);
		वापस vma;
	पूर्ण

	err = i915_vma_pin(vma, 0, 0, PIN_USER | PIN_HIGH);
	अगर (err) अणु
		i915_gem_object_put(obj);
		वापस ERR_PTR(err);
	पूर्ण

	err = i915_vma_sync(vma);
	अगर (err) अणु
		i915_gem_object_put(obj);
		वापस ERR_PTR(err);
	पूर्ण

	cs = i915_gem_object_pin_map_unlocked(obj, I915_MAP_WC);
	अगर (IS_ERR(cs)) अणु
		i915_gem_object_put(obj);
		वापस ERR_CAST(cs);
	पूर्ण

	अगर (INTEL_GEN(engine->i915) >= 6) अणु
		*cs++ = MI_STORE_DWORD_IMM_GEN4;
		*cs++ = 0;
	पूर्ण अन्यथा अगर (INTEL_GEN(engine->i915) >= 4) अणु
		*cs++ = MI_STORE_DWORD_IMM_GEN4 | MI_USE_GGTT;
		*cs++ = 0;
	पूर्ण अन्यथा अणु
		*cs++ = MI_STORE_DWORD_IMM | MI_MEM_VIRTUAL;
	पूर्ण
	*cs++ = vma->node.start + 4000;
	*cs++ = STACK_MAGIC;

	*cs++ = MI_BATCH_BUFFER_END;

	i915_gem_object_flush_map(obj);
	i915_gem_object_unpin_map(obj);

	vma->निजी = पूर्णांकel_context_create(engine); /* dummy residuals */
	अगर (IS_ERR(vma->निजी)) अणु
		vma = ERR_CAST(vma->निजी);
		i915_gem_object_put(obj);
	पूर्ण

	वापस vma;
पूर्ण

अटल पूर्णांक context_sync(काष्ठा पूर्णांकel_context *ce)
अणु
	काष्ठा i915_request *rq;
	पूर्णांक err = 0;

	rq = पूर्णांकel_context_create_request(ce);
	अगर (IS_ERR(rq))
		वापस PTR_ERR(rq);

	i915_request_get(rq);
	i915_request_add(rq);

	अगर (i915_request_रुको(rq, 0, HZ / 5) < 0)
		err = -ETIME;
	i915_request_put(rq);

	वापस err;
पूर्ण

अटल पूर्णांक new_context_sync(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_context *ce;
	पूर्णांक err;

	ce = पूर्णांकel_context_create(engine);
	अगर (IS_ERR(ce))
		वापस PTR_ERR(ce);

	err = context_sync(ce);
	पूर्णांकel_context_put(ce);

	वापस err;
पूर्ण

अटल पूर्णांक mixed_contexts_sync(काष्ठा पूर्णांकel_engine_cs *engine, u32 *result)
अणु
	पूर्णांक pass;
	पूर्णांक err;

	क्रम (pass = 0; pass < 2; pass++) अणु
		WRITE_ONCE(*result, 0);
		err = context_sync(engine->kernel_context);
		अगर (err || READ_ONCE(*result)) अणु
			अगर (!err) अणु
				pr_err("pass[%d] wa_bb emitted for the kernel context\n",
				       pass);
				err = -EINVAL;
			पूर्ण
			वापस err;
		पूर्ण

		WRITE_ONCE(*result, 0);
		err = new_context_sync(engine);
		अगर (READ_ONCE(*result) != STACK_MAGIC) अणु
			अगर (!err) अणु
				pr_err("pass[%d] wa_bb *NOT* emitted after the kernel context\n",
				       pass);
				err = -EINVAL;
			पूर्ण
			वापस err;
		पूर्ण

		WRITE_ONCE(*result, 0);
		err = new_context_sync(engine);
		अगर (READ_ONCE(*result) != STACK_MAGIC) अणु
			अगर (!err) अणु
				pr_err("pass[%d] wa_bb *NOT* emitted for the user context switch\n",
				       pass);
				err = -EINVAL;
			पूर्ण
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक द्विगुन_context_sync_00(काष्ठा पूर्णांकel_engine_cs *engine, u32 *result)
अणु
	काष्ठा पूर्णांकel_context *ce;
	पूर्णांक err, i;

	ce = पूर्णांकel_context_create(engine);
	अगर (IS_ERR(ce))
		वापस PTR_ERR(ce);

	क्रम (i = 0; i < 2; i++) अणु
		WRITE_ONCE(*result, 0);
		err = context_sync(ce);
		अगर (err)
			अवरोध;
	पूर्ण
	पूर्णांकel_context_put(ce);
	अगर (err)
		वापस err;

	अगर (READ_ONCE(*result)) अणु
		pr_err("wa_bb emitted between the same user context\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kernel_context_sync_00(काष्ठा पूर्णांकel_engine_cs *engine, u32 *result)
अणु
	काष्ठा पूर्णांकel_context *ce;
	पूर्णांक err, i;

	ce = पूर्णांकel_context_create(engine);
	अगर (IS_ERR(ce))
		वापस PTR_ERR(ce);

	क्रम (i = 0; i < 2; i++) अणु
		WRITE_ONCE(*result, 0);
		err = context_sync(ce);
		अगर (err)
			अवरोध;

		err = context_sync(engine->kernel_context);
		अगर (err)
			अवरोध;
	पूर्ण
	पूर्णांकel_context_put(ce);
	अगर (err)
		वापस err;

	अगर (READ_ONCE(*result)) अणु
		pr_err("wa_bb emitted between the same user context [with intervening kernel]\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __live_ctx_चयन_wa(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा i915_vma *bb;
	u32 *result;
	पूर्णांक err;

	bb = create_wally(engine);
	अगर (IS_ERR(bb))
		वापस PTR_ERR(bb);

	result = i915_gem_object_pin_map_unlocked(bb->obj, I915_MAP_WC);
	अगर (IS_ERR(result)) अणु
		पूर्णांकel_context_put(bb->निजी);
		i915_vma_unpin_and_release(&bb, 0);
		वापस PTR_ERR(result);
	पूर्ण
	result += 1000;

	engine->wa_ctx.vma = bb;

	err = mixed_contexts_sync(engine, result);
	अगर (err)
		जाओ out;

	err = द्विगुन_context_sync_00(engine, result);
	अगर (err)
		जाओ out;

	err = kernel_context_sync_00(engine, result);
	अगर (err)
		जाओ out;

out:
	पूर्णांकel_context_put(engine->wa_ctx.vma->निजी);
	i915_vma_unpin_and_release(&engine->wa_ctx.vma, I915_VMA_RELEASE_MAP);
	वापस err;
पूर्ण

अटल पूर्णांक live_ctx_चयन_wa(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;

	/*
	 * Exercise the पूर्णांकer-context wa batch.
	 *
	 * Between each user context we run a wa batch, and since it may
	 * have implications क्रम user visible state, we have to check that
	 * we करो actually execute it.
	 *
	 * The trick we use is to replace the normal wa batch with a custom
	 * one that ग_लिखोs to a marker within it, and we can then look क्रम
	 * that marker to confirm अगर the batch was run when we expect it,
	 * and equally important it was wasn't run when we don't!
	 */

	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा i915_vma *saved_wa;
		पूर्णांक err;

		अगर (!पूर्णांकel_engine_can_store_dword(engine))
			जारी;

		अगर (IS_GEN_RANGE(gt->i915, 4, 5))
			जारी; /* MI_STORE_DWORD is privileged! */

		saved_wa = fetch_and_zero(&engine->wa_ctx.vma);

		पूर्णांकel_engine_pm_get(engine);
		err = __live_ctx_चयन_wa(engine);
		पूर्णांकel_engine_pm_put(engine);
		अगर (igt_flush_test(gt->i915))
			err = -EIO;

		engine->wa_ctx.vma = saved_wa;
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_ring_submission_live_selftests(काष्ठा drm_i915_निजी *i915)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(live_ctx_चयन_wa),
	पूर्ण;

	अगर (HAS_EXECLISTS(i915))
		वापस 0;

	वापस पूर्णांकel_gt_live_subtests(tests, &i915->gt);
पूर्ण
