<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2016 Intel Corporation
 */

#समावेश <linux/kthपढ़ो.h>

#समावेश "gem/i915_gem_context.h"

#समावेश "intel_gt.h"
#समावेश "intel_engine_heartbeat.h"
#समावेश "intel_engine_pm.h"
#समावेश "selftest_engine_heartbeat.h"

#समावेश "i915_selftest.h"
#समावेश "selftests/i915_random.h"
#समावेश "selftests/igt_flush_test.h"
#समावेश "selftests/igt_reset.h"
#समावेश "selftests/igt_atomic.h"

#समावेश "selftests/mock_drm.h"

#समावेश "gem/selftests/mock_context.h"
#समावेश "gem/selftests/igt_gem_utils.h"

#घोषणा IGT_IDLE_TIMEOUT 50 /* ms; समय to रुको after flushing between tests */

काष्ठा hang अणु
	काष्ठा पूर्णांकel_gt *gt;
	काष्ठा drm_i915_gem_object *hws;
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_gem_context *ctx;
	u32 *seqno;
	u32 *batch;
पूर्ण;

अटल पूर्णांक hang_init(काष्ठा hang *h, काष्ठा पूर्णांकel_gt *gt)
अणु
	व्योम *vaddr;
	पूर्णांक err;

	स_रखो(h, 0, माप(*h));
	h->gt = gt;

	h->ctx = kernel_context(gt->i915);
	अगर (IS_ERR(h->ctx))
		वापस PTR_ERR(h->ctx);

	GEM_BUG_ON(i915_gem_context_is_bannable(h->ctx));

	h->hws = i915_gem_object_create_पूर्णांकernal(gt->i915, PAGE_SIZE);
	अगर (IS_ERR(h->hws)) अणु
		err = PTR_ERR(h->hws);
		जाओ err_ctx;
	पूर्ण

	h->obj = i915_gem_object_create_पूर्णांकernal(gt->i915, PAGE_SIZE);
	अगर (IS_ERR(h->obj)) अणु
		err = PTR_ERR(h->obj);
		जाओ err_hws;
	पूर्ण

	i915_gem_object_set_cache_coherency(h->hws, I915_CACHE_LLC);
	vaddr = i915_gem_object_pin_map_unlocked(h->hws, I915_MAP_WB);
	अगर (IS_ERR(vaddr)) अणु
		err = PTR_ERR(vaddr);
		जाओ err_obj;
	पूर्ण
	h->seqno = स_रखो(vaddr, 0xff, PAGE_SIZE);

	vaddr = i915_gem_object_pin_map_unlocked(h->obj,
						 i915_coherent_map_type(gt->i915));
	अगर (IS_ERR(vaddr)) अणु
		err = PTR_ERR(vaddr);
		जाओ err_unpin_hws;
	पूर्ण
	h->batch = vaddr;

	वापस 0;

err_unpin_hws:
	i915_gem_object_unpin_map(h->hws);
err_obj:
	i915_gem_object_put(h->obj);
err_hws:
	i915_gem_object_put(h->hws);
err_ctx:
	kernel_context_बंद(h->ctx);
	वापस err;
पूर्ण

अटल u64 hws_address(स्थिर काष्ठा i915_vma *hws,
		       स्थिर काष्ठा i915_request *rq)
अणु
	वापस hws->node.start + offset_in_page(माप(u32)*rq->fence.context);
पूर्ण

अटल पूर्णांक move_to_active(काष्ठा i915_vma *vma,
			  काष्ठा i915_request *rq,
			  अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक err;

	i915_vma_lock(vma);
	err = i915_request_aरुको_object(rq, vma->obj,
					flags & EXEC_OBJECT_WRITE);
	अगर (err == 0)
		err = i915_vma_move_to_active(vma, rq, flags);
	i915_vma_unlock(vma);

	वापस err;
पूर्ण

अटल काष्ठा i915_request *
hang_create_request(काष्ठा hang *h, काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_gt *gt = h->gt;
	काष्ठा i915_address_space *vm = i915_gem_context_get_vm_rcu(h->ctx);
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_request *rq = शून्य;
	काष्ठा i915_vma *hws, *vma;
	अचिन्हित पूर्णांक flags;
	व्योम *vaddr;
	u32 *batch;
	पूर्णांक err;

	obj = i915_gem_object_create_पूर्णांकernal(gt->i915, PAGE_SIZE);
	अगर (IS_ERR(obj)) अणु
		i915_vm_put(vm);
		वापस ERR_CAST(obj);
	पूर्ण

	vaddr = i915_gem_object_pin_map_unlocked(obj, i915_coherent_map_type(gt->i915));
	अगर (IS_ERR(vaddr)) अणु
		i915_gem_object_put(obj);
		i915_vm_put(vm);
		वापस ERR_CAST(vaddr);
	पूर्ण

	i915_gem_object_unpin_map(h->obj);
	i915_gem_object_put(h->obj);

	h->obj = obj;
	h->batch = vaddr;

	vma = i915_vma_instance(h->obj, vm, शून्य);
	अगर (IS_ERR(vma)) अणु
		i915_vm_put(vm);
		वापस ERR_CAST(vma);
	पूर्ण

	hws = i915_vma_instance(h->hws, vm, शून्य);
	अगर (IS_ERR(hws)) अणु
		i915_vm_put(vm);
		वापस ERR_CAST(hws);
	पूर्ण

	err = i915_vma_pin(vma, 0, 0, PIN_USER);
	अगर (err) अणु
		i915_vm_put(vm);
		वापस ERR_PTR(err);
	पूर्ण

	err = i915_vma_pin(hws, 0, 0, PIN_USER);
	अगर (err)
		जाओ unpin_vma;

	rq = igt_request_alloc(h->ctx, engine);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ unpin_hws;
	पूर्ण

	err = move_to_active(vma, rq, 0);
	अगर (err)
		जाओ cancel_rq;

	err = move_to_active(hws, rq, 0);
	अगर (err)
		जाओ cancel_rq;

	batch = h->batch;
	अगर (INTEL_GEN(gt->i915) >= 8) अणु
		*batch++ = MI_STORE_DWORD_IMM_GEN4;
		*batch++ = lower_32_bits(hws_address(hws, rq));
		*batch++ = upper_32_bits(hws_address(hws, rq));
		*batch++ = rq->fence.seqno;
		*batch++ = MI_NOOP;

		स_रखो(batch, 0, 1024);
		batch += 1024 / माप(*batch);

		*batch++ = MI_NOOP;
		*batch++ = MI_BATCH_BUFFER_START | 1 << 8 | 1;
		*batch++ = lower_32_bits(vma->node.start);
		*batch++ = upper_32_bits(vma->node.start);
	पूर्ण अन्यथा अगर (INTEL_GEN(gt->i915) >= 6) अणु
		*batch++ = MI_STORE_DWORD_IMM_GEN4;
		*batch++ = 0;
		*batch++ = lower_32_bits(hws_address(hws, rq));
		*batch++ = rq->fence.seqno;
		*batch++ = MI_NOOP;

		स_रखो(batch, 0, 1024);
		batch += 1024 / माप(*batch);

		*batch++ = MI_NOOP;
		*batch++ = MI_BATCH_BUFFER_START | 1 << 8;
		*batch++ = lower_32_bits(vma->node.start);
	पूर्ण अन्यथा अगर (INTEL_GEN(gt->i915) >= 4) अणु
		*batch++ = MI_STORE_DWORD_IMM_GEN4 | MI_USE_GGTT;
		*batch++ = 0;
		*batch++ = lower_32_bits(hws_address(hws, rq));
		*batch++ = rq->fence.seqno;
		*batch++ = MI_NOOP;

		स_रखो(batch, 0, 1024);
		batch += 1024 / माप(*batch);

		*batch++ = MI_NOOP;
		*batch++ = MI_BATCH_BUFFER_START | 2 << 6;
		*batch++ = lower_32_bits(vma->node.start);
	पूर्ण अन्यथा अणु
		*batch++ = MI_STORE_DWORD_IMM | MI_MEM_VIRTUAL;
		*batch++ = lower_32_bits(hws_address(hws, rq));
		*batch++ = rq->fence.seqno;
		*batch++ = MI_NOOP;

		स_रखो(batch, 0, 1024);
		batch += 1024 / माप(*batch);

		*batch++ = MI_NOOP;
		*batch++ = MI_BATCH_BUFFER_START | 2 << 6;
		*batch++ = lower_32_bits(vma->node.start);
	पूर्ण
	*batch++ = MI_BATCH_BUFFER_END; /* not reached */
	पूर्णांकel_gt_chipset_flush(engine->gt);

	अगर (rq->engine->emit_init_bपढ़ोcrumb) अणु
		err = rq->engine->emit_init_bपढ़ोcrumb(rq);
		अगर (err)
			जाओ cancel_rq;
	पूर्ण

	flags = 0;
	अगर (INTEL_GEN(gt->i915) <= 5)
		flags |= I915_DISPATCH_SECURE;

	err = rq->engine->emit_bb_start(rq, vma->node.start, PAGE_SIZE, flags);

cancel_rq:
	अगर (err) अणु
		i915_request_set_error_once(rq, err);
		i915_request_add(rq);
	पूर्ण
unpin_hws:
	i915_vma_unpin(hws);
unpin_vma:
	i915_vma_unpin(vma);
	i915_vm_put(vm);
	वापस err ? ERR_PTR(err) : rq;
पूर्ण

अटल u32 hws_seqno(स्थिर काष्ठा hang *h, स्थिर काष्ठा i915_request *rq)
अणु
	वापस READ_ONCE(h->seqno[rq->fence.context % (PAGE_SIZE/माप(u32))]);
पूर्ण

अटल व्योम hang_fini(काष्ठा hang *h)
अणु
	*h->batch = MI_BATCH_BUFFER_END;
	पूर्णांकel_gt_chipset_flush(h->gt);

	i915_gem_object_unpin_map(h->obj);
	i915_gem_object_put(h->obj);

	i915_gem_object_unpin_map(h->hws);
	i915_gem_object_put(h->hws);

	kernel_context_बंद(h->ctx);

	igt_flush_test(h->gt->i915);
पूर्ण

अटल bool रुको_until_running(काष्ठा hang *h, काष्ठा i915_request *rq)
अणु
	वापस !(रुको_क्रम_us(i915_seqno_passed(hws_seqno(h, rq),
					       rq->fence.seqno),
			     10) &&
		 रुको_क्रम(i915_seqno_passed(hws_seqno(h, rq),
					    rq->fence.seqno),
			  1000));
पूर्ण

अटल पूर्णांक igt_hang_sanitycheck(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा i915_request *rq;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	काष्ठा hang h;
	पूर्णांक err;

	/* Basic check that we can execute our hanging batch */

	err = hang_init(&h, gt);
	अगर (err)
		वापस err;

	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा पूर्णांकel_wedge_me w;
		दीर्घ समयout;

		अगर (!पूर्णांकel_engine_can_store_dword(engine))
			जारी;

		rq = hang_create_request(&h, engine);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			pr_err("Failed to create request for %s, err=%d\n",
			       engine->name, err);
			जाओ fini;
		पूर्ण

		i915_request_get(rq);

		*h.batch = MI_BATCH_BUFFER_END;
		पूर्णांकel_gt_chipset_flush(engine->gt);

		i915_request_add(rq);

		समयout = 0;
		पूर्णांकel_wedge_on_समयout(&w, gt, HZ / 10 /* 100ms */)
			समयout = i915_request_रुको(rq, 0,
						    MAX_SCHEDULE_TIMEOUT);
		अगर (पूर्णांकel_gt_is_wedged(gt))
			समयout = -EIO;

		i915_request_put(rq);

		अगर (समयout < 0) अणु
			err = समयout;
			pr_err("Wait for request failed on %s, err=%d\n",
			       engine->name, err);
			जाओ fini;
		पूर्ण
	पूर्ण

fini:
	hang_fini(&h);
	वापस err;
पूर्ण

अटल bool रुको_क्रम_idle(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	वापस रुको_क्रम(पूर्णांकel_engine_is_idle(engine), IGT_IDLE_TIMEOUT) == 0;
पूर्ण

अटल पूर्णांक igt_reset_nop(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा i915_gpu_error *global = &gt->i915->gpu_error;
	काष्ठा पूर्णांकel_engine_cs *engine;
	अचिन्हित पूर्णांक reset_count, count;
	क्रमागत पूर्णांकel_engine_id id;
	IGT_TIMEOUT(end_समय);
	पूर्णांक err = 0;

	/* Check that we can reset during non-user portions of requests */

	reset_count = i915_reset_count(global);
	count = 0;
	करो अणु
		क्रम_each_engine(engine, gt, id) अणु
			काष्ठा पूर्णांकel_context *ce;
			पूर्णांक i;

			ce = पूर्णांकel_context_create(engine);
			अगर (IS_ERR(ce)) अणु
				err = PTR_ERR(ce);
				अवरोध;
			पूर्ण

			क्रम (i = 0; i < 16; i++) अणु
				काष्ठा i915_request *rq;

				rq = पूर्णांकel_context_create_request(ce);
				अगर (IS_ERR(rq)) अणु
					err = PTR_ERR(rq);
					अवरोध;
				पूर्ण

				i915_request_add(rq);
			पूर्ण

			पूर्णांकel_context_put(ce);
		पूर्ण

		igt_global_reset_lock(gt);
		पूर्णांकel_gt_reset(gt, ALL_ENGINES, शून्य);
		igt_global_reset_unlock(gt);

		अगर (पूर्णांकel_gt_is_wedged(gt)) अणु
			err = -EIO;
			अवरोध;
		पूर्ण

		अगर (i915_reset_count(global) != reset_count + ++count) अणु
			pr_err("Full GPU reset not recorded!\n");
			err = -EINVAL;
			अवरोध;
		पूर्ण

		err = igt_flush_test(gt->i915);
		अगर (err)
			अवरोध;
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, end_समय));
	pr_info("%s: %d resets\n", __func__, count);

	अगर (igt_flush_test(gt->i915))
		err = -EIO;
	वापस err;
पूर्ण

अटल पूर्णांक igt_reset_nop_engine(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा i915_gpu_error *global = &gt->i915->gpu_error;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;

	/* Check that we can engine-reset during non-user portions */

	अगर (!पूर्णांकel_has_reset_engine(gt))
		वापस 0;

	क्रम_each_engine(engine, gt, id) अणु
		अचिन्हित पूर्णांक reset_count, reset_engine_count, count;
		काष्ठा पूर्णांकel_context *ce;
		IGT_TIMEOUT(end_समय);
		पूर्णांक err;

		ce = पूर्णांकel_context_create(engine);
		अगर (IS_ERR(ce))
			वापस PTR_ERR(ce);

		reset_count = i915_reset_count(global);
		reset_engine_count = i915_reset_engine_count(global, engine);
		count = 0;

		st_engine_heartbeat_disable(engine);
		set_bit(I915_RESET_ENGINE + id, &gt->reset.flags);
		करो अणु
			पूर्णांक i;

			अगर (!रुको_क्रम_idle(engine)) अणु
				pr_err("%s failed to idle before reset\n",
				       engine->name);
				err = -EIO;
				अवरोध;
			पूर्ण

			क्रम (i = 0; i < 16; i++) अणु
				काष्ठा i915_request *rq;

				rq = पूर्णांकel_context_create_request(ce);
				अगर (IS_ERR(rq)) अणु
					काष्ठा drm_prपूर्णांकer p =
						drm_info_prपूर्णांकer(gt->i915->drm.dev);
					पूर्णांकel_engine_dump(engine, &p,
							  "%s(%s): failed to submit request\n",
							  __func__,
							  engine->name);

					GEM_TRACE("%s(%s): failed to submit request\n",
						  __func__,
						  engine->name);
					GEM_TRACE_DUMP();

					पूर्णांकel_gt_set_wedged(gt);

					err = PTR_ERR(rq);
					अवरोध;
				पूर्ण

				i915_request_add(rq);
			पूर्ण
			err = पूर्णांकel_engine_reset(engine, शून्य);
			अगर (err) अणु
				pr_err("intel_engine_reset(%s) failed, err:%d\n",
				       engine->name, err);
				अवरोध;
			पूर्ण

			अगर (i915_reset_count(global) != reset_count) अणु
				pr_err("Full GPU reset recorded! (engine reset expected)\n");
				err = -EINVAL;
				अवरोध;
			पूर्ण

			अगर (i915_reset_engine_count(global, engine) !=
			    reset_engine_count + ++count) अणु
				pr_err("%s engine reset not recorded!\n",
				       engine->name);
				err = -EINVAL;
				अवरोध;
			पूर्ण
		पूर्ण जबतक (समय_beक्रमe(jअगरfies, end_समय));
		clear_bit(I915_RESET_ENGINE + id, &gt->reset.flags);
		st_engine_heartbeat_enable(engine);

		pr_info("%s(%s): %d resets\n", __func__, engine->name, count);

		पूर्णांकel_context_put(ce);
		अगर (igt_flush_test(gt->i915))
			err = -EIO;
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम क्रमce_reset_समयout(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	engine->reset_समयout.probability = 999;
	atomic_set(&engine->reset_समयout.बार, -1);
पूर्ण

अटल व्योम cancel_reset_समयout(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	स_रखो(&engine->reset_समयout, 0, माप(engine->reset_समयout));
पूर्ण

अटल पूर्णांक igt_reset_fail_engine(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;

	/* Check that we can recover from engine-reset failues */

	अगर (!पूर्णांकel_has_reset_engine(gt))
		वापस 0;

	क्रम_each_engine(engine, gt, id) अणु
		अचिन्हित पूर्णांक count;
		काष्ठा पूर्णांकel_context *ce;
		IGT_TIMEOUT(end_समय);
		पूर्णांक err;

		ce = पूर्णांकel_context_create(engine);
		अगर (IS_ERR(ce))
			वापस PTR_ERR(ce);

		st_engine_heartbeat_disable(engine);
		set_bit(I915_RESET_ENGINE + id, &gt->reset.flags);

		क्रमce_reset_समयout(engine);
		err = पूर्णांकel_engine_reset(engine, शून्य);
		cancel_reset_समयout(engine);
		अगर (err == 0) /* समयouts only generated on gen8+ */
			जाओ skip;

		count = 0;
		करो अणु
			काष्ठा i915_request *last = शून्य;
			पूर्णांक i;

			अगर (!रुको_क्रम_idle(engine)) अणु
				pr_err("%s failed to idle before reset\n",
				       engine->name);
				err = -EIO;
				अवरोध;
			पूर्ण

			क्रम (i = 0; i < count % 15; i++) अणु
				काष्ठा i915_request *rq;

				rq = पूर्णांकel_context_create_request(ce);
				अगर (IS_ERR(rq)) अणु
					काष्ठा drm_prपूर्णांकer p =
						drm_info_prपूर्णांकer(gt->i915->drm.dev);
					पूर्णांकel_engine_dump(engine, &p,
							  "%s(%s): failed to submit request\n",
							  __func__,
							  engine->name);

					GEM_TRACE("%s(%s): failed to submit request\n",
						  __func__,
						  engine->name);
					GEM_TRACE_DUMP();

					पूर्णांकel_gt_set_wedged(gt);
					अगर (last)
						i915_request_put(last);

					err = PTR_ERR(rq);
					जाओ out;
				पूर्ण

				अगर (last)
					i915_request_put(last);
				last = i915_request_get(rq);
				i915_request_add(rq);
			पूर्ण

			अगर (count & 1) अणु
				err = पूर्णांकel_engine_reset(engine, शून्य);
				अगर (err) अणु
					GEM_TRACE_ERR("intel_engine_reset(%s) failed, err:%d\n",
						      engine->name, err);
					GEM_TRACE_DUMP();
					i915_request_put(last);
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				क्रमce_reset_समयout(engine);
				err = पूर्णांकel_engine_reset(engine, शून्य);
				cancel_reset_समयout(engine);
				अगर (err != -ETIMEDOUT) अणु
					pr_err("intel_engine_reset(%s) did not fail, err:%d\n",
					       engine->name, err);
					i915_request_put(last);
					अवरोध;
				पूर्ण
			पूर्ण

			err = 0;
			अगर (last) अणु
				अगर (i915_request_रुको(last, 0, HZ / 2) < 0) अणु
					काष्ठा drm_prपूर्णांकer p =
						drm_info_prपूर्णांकer(gt->i915->drm.dev);

					पूर्णांकel_engine_dump(engine, &p,
							  "%s(%s): failed to complete request\n",
							  __func__,
							  engine->name);

					GEM_TRACE("%s(%s): failed to complete request\n",
						  __func__,
						  engine->name);
					GEM_TRACE_DUMP();

					err = -EIO;
				पूर्ण
				i915_request_put(last);
			पूर्ण
			count++;
		पूर्ण जबतक (err == 0 && समय_beक्रमe(jअगरfies, end_समय));
out:
		pr_info("%s(%s): %d resets\n", __func__, engine->name, count);
skip:
		clear_bit(I915_RESET_ENGINE + id, &gt->reset.flags);
		st_engine_heartbeat_enable(engine);
		पूर्णांकel_context_put(ce);

		अगर (igt_flush_test(gt->i915))
			err = -EIO;
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __igt_reset_engine(काष्ठा पूर्णांकel_gt *gt, bool active)
अणु
	काष्ठा i915_gpu_error *global = &gt->i915->gpu_error;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	काष्ठा hang h;
	पूर्णांक err = 0;

	/* Check that we can issue an engine reset on an idle engine (no-op) */

	अगर (!पूर्णांकel_has_reset_engine(gt))
		वापस 0;

	अगर (active) अणु
		err = hang_init(&h, gt);
		अगर (err)
			वापस err;
	पूर्ण

	क्रम_each_engine(engine, gt, id) अणु
		अचिन्हित पूर्णांक reset_count, reset_engine_count;
		अचिन्हित दीर्घ count;
		IGT_TIMEOUT(end_समय);

		अगर (active && !पूर्णांकel_engine_can_store_dword(engine))
			जारी;

		अगर (!रुको_क्रम_idle(engine)) अणु
			pr_err("%s failed to idle before reset\n",
			       engine->name);
			err = -EIO;
			अवरोध;
		पूर्ण

		reset_count = i915_reset_count(global);
		reset_engine_count = i915_reset_engine_count(global, engine);

		st_engine_heartbeat_disable(engine);
		set_bit(I915_RESET_ENGINE + id, &gt->reset.flags);
		count = 0;
		करो अणु
			अगर (active) अणु
				काष्ठा i915_request *rq;

				rq = hang_create_request(&h, engine);
				अगर (IS_ERR(rq)) अणु
					err = PTR_ERR(rq);
					अवरोध;
				पूर्ण

				i915_request_get(rq);
				i915_request_add(rq);

				अगर (!रुको_until_running(&h, rq)) अणु
					काष्ठा drm_prपूर्णांकer p = drm_info_prपूर्णांकer(gt->i915->drm.dev);

					pr_err("%s: Failed to start request %llx, at %x\n",
					       __func__, rq->fence.seqno, hws_seqno(&h, rq));
					पूर्णांकel_engine_dump(engine, &p,
							  "%s\n", engine->name);

					i915_request_put(rq);
					err = -EIO;
					अवरोध;
				पूर्ण

				i915_request_put(rq);
			पूर्ण

			err = पूर्णांकel_engine_reset(engine, शून्य);
			अगर (err) अणु
				pr_err("intel_engine_reset(%s) failed, err:%d\n",
				       engine->name, err);
				अवरोध;
			पूर्ण

			अगर (i915_reset_count(global) != reset_count) अणु
				pr_err("Full GPU reset recorded! (engine reset expected)\n");
				err = -EINVAL;
				अवरोध;
			पूर्ण

			अगर (i915_reset_engine_count(global, engine) !=
			    ++reset_engine_count) अणु
				pr_err("%s engine reset not recorded!\n",
				       engine->name);
				err = -EINVAL;
				अवरोध;
			पूर्ण

			count++;
		पूर्ण जबतक (समय_beक्रमe(jअगरfies, end_समय));
		clear_bit(I915_RESET_ENGINE + id, &gt->reset.flags);
		st_engine_heartbeat_enable(engine);
		pr_info("%s: Completed %lu %s resets\n",
			engine->name, count, active ? "active" : "idle");

		अगर (err)
			अवरोध;

		err = igt_flush_test(gt->i915);
		अगर (err)
			अवरोध;
	पूर्ण

	अगर (पूर्णांकel_gt_is_wedged(gt))
		err = -EIO;

	अगर (active)
		hang_fini(&h);

	वापस err;
पूर्ण

अटल पूर्णांक igt_reset_idle_engine(व्योम *arg)
अणु
	वापस __igt_reset_engine(arg, false);
पूर्ण

अटल पूर्णांक igt_reset_active_engine(व्योम *arg)
अणु
	वापस __igt_reset_engine(arg, true);
पूर्ण

काष्ठा active_engine अणु
	काष्ठा task_काष्ठा *task;
	काष्ठा पूर्णांकel_engine_cs *engine;
	अचिन्हित दीर्घ resets;
	अचिन्हित पूर्णांक flags;
पूर्ण;

#घोषणा TEST_ACTIVE	BIT(0)
#घोषणा TEST_OTHERS	BIT(1)
#घोषणा TEST_SELF	BIT(2)
#घोषणा TEST_PRIORITY	BIT(3)

अटल पूर्णांक active_request_put(काष्ठा i915_request *rq)
अणु
	पूर्णांक err = 0;

	अगर (!rq)
		वापस 0;

	अगर (i915_request_रुको(rq, 0, 5 * HZ) < 0) अणु
		GEM_TRACE("%s timed out waiting for completion of fence %llx:%lld\n",
			  rq->engine->name,
			  rq->fence.context,
			  rq->fence.seqno);
		GEM_TRACE_DUMP();

		पूर्णांकel_gt_set_wedged(rq->engine->gt);
		err = -EIO;
	पूर्ण

	i915_request_put(rq);

	वापस err;
पूर्ण

अटल पूर्णांक active_engine(व्योम *data)
अणु
	I915_RND_STATE(prng);
	काष्ठा active_engine *arg = data;
	काष्ठा पूर्णांकel_engine_cs *engine = arg->engine;
	काष्ठा i915_request *rq[8] = अणुपूर्ण;
	काष्ठा पूर्णांकel_context *ce[ARRAY_SIZE(rq)];
	अचिन्हित दीर्घ count;
	पूर्णांक err = 0;

	क्रम (count = 0; count < ARRAY_SIZE(ce); count++) अणु
		ce[count] = पूर्णांकel_context_create(engine);
		अगर (IS_ERR(ce[count])) अणु
			err = PTR_ERR(ce[count]);
			जबतक (--count)
				पूर्णांकel_context_put(ce[count]);
			वापस err;
		पूर्ण
	पूर्ण

	count = 0;
	जबतक (!kthपढ़ो_should_stop()) अणु
		अचिन्हित पूर्णांक idx = count++ & (ARRAY_SIZE(rq) - 1);
		काष्ठा i915_request *old = rq[idx];
		काष्ठा i915_request *new;

		new = पूर्णांकel_context_create_request(ce[idx]);
		अगर (IS_ERR(new)) अणु
			err = PTR_ERR(new);
			अवरोध;
		पूर्ण

		rq[idx] = i915_request_get(new);
		i915_request_add(new);

		अगर (engine->schedule && arg->flags & TEST_PRIORITY) अणु
			काष्ठा i915_sched_attr attr = अणु
				.priority =
					i915_pअक्रमom_u32_max_state(512, &prng),
			पूर्ण;
			engine->schedule(rq[idx], &attr);
		पूर्ण

		err = active_request_put(old);
		अगर (err)
			अवरोध;

		cond_resched();
	पूर्ण

	क्रम (count = 0; count < ARRAY_SIZE(rq); count++) अणु
		पूर्णांक err__ = active_request_put(rq[count]);

		/* Keep the first error */
		अगर (!err)
			err = err__;

		पूर्णांकel_context_put(ce[count]);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक __igt_reset_engines(काष्ठा पूर्णांकel_gt *gt,
			       स्थिर अक्षर *test_name,
			       अचिन्हित पूर्णांक flags)
अणु
	काष्ठा i915_gpu_error *global = &gt->i915->gpu_error;
	काष्ठा पूर्णांकel_engine_cs *engine, *other;
	क्रमागत पूर्णांकel_engine_id id, पंचांगp;
	काष्ठा hang h;
	पूर्णांक err = 0;

	/* Check that issuing a reset on one engine करोes not पूर्णांकerfere
	 * with any other engine.
	 */

	अगर (!पूर्णांकel_has_reset_engine(gt))
		वापस 0;

	अगर (flags & TEST_ACTIVE) अणु
		err = hang_init(&h, gt);
		अगर (err)
			वापस err;

		अगर (flags & TEST_PRIORITY)
			h.ctx->sched.priority = 1024;
	पूर्ण

	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा active_engine thपढ़ोs[I915_NUM_ENGINES] = अणुपूर्ण;
		अचिन्हित दीर्घ device = i915_reset_count(global);
		अचिन्हित दीर्घ count = 0, reported;
		IGT_TIMEOUT(end_समय);

		अगर (flags & TEST_ACTIVE &&
		    !पूर्णांकel_engine_can_store_dword(engine))
			जारी;

		अगर (!रुको_क्रम_idle(engine)) अणु
			pr_err("i915_reset_engine(%s:%s): failed to idle before reset\n",
			       engine->name, test_name);
			err = -EIO;
			अवरोध;
		पूर्ण

		स_रखो(thपढ़ोs, 0, माप(thपढ़ोs));
		क्रम_each_engine(other, gt, पंचांगp) अणु
			काष्ठा task_काष्ठा *tsk;

			thपढ़ोs[पंचांगp].resets =
				i915_reset_engine_count(global, other);

			अगर (other == engine && !(flags & TEST_SELF))
				जारी;

			अगर (other != engine && !(flags & TEST_OTHERS))
				जारी;

			thपढ़ोs[पंचांगp].engine = other;
			thपढ़ोs[पंचांगp].flags = flags;

			tsk = kthपढ़ो_run(active_engine, &thपढ़ोs[पंचांगp],
					  "igt/%s", other->name);
			अगर (IS_ERR(tsk)) अणु
				err = PTR_ERR(tsk);
				जाओ unwind;
			पूर्ण

			thपढ़ोs[पंचांगp].task = tsk;
			get_task_काष्ठा(tsk);
		पूर्ण

		yield(); /* start all thपढ़ोs beक्रमe we begin */

		st_engine_heartbeat_disable(engine);
		set_bit(I915_RESET_ENGINE + id, &gt->reset.flags);
		करो अणु
			काष्ठा i915_request *rq = शून्य;

			अगर (flags & TEST_ACTIVE) अणु
				rq = hang_create_request(&h, engine);
				अगर (IS_ERR(rq)) अणु
					err = PTR_ERR(rq);
					अवरोध;
				पूर्ण

				i915_request_get(rq);
				i915_request_add(rq);

				अगर (!रुको_until_running(&h, rq)) अणु
					काष्ठा drm_prपूर्णांकer p = drm_info_prपूर्णांकer(gt->i915->drm.dev);

					pr_err("%s: Failed to start request %llx, at %x\n",
					       __func__, rq->fence.seqno, hws_seqno(&h, rq));
					पूर्णांकel_engine_dump(engine, &p,
							  "%s\n", engine->name);

					i915_request_put(rq);
					err = -EIO;
					अवरोध;
				पूर्ण
			पूर्ण

			err = पूर्णांकel_engine_reset(engine, शून्य);
			अगर (err) अणु
				pr_err("i915_reset_engine(%s:%s): failed, err=%d\n",
				       engine->name, test_name, err);
				अवरोध;
			पूर्ण

			count++;

			अगर (rq) अणु
				अगर (rq->fence.error != -EIO) अणु
					pr_err("i915_reset_engine(%s:%s):"
					       " failed to reset request %llx:%lld\n",
					       engine->name, test_name,
					       rq->fence.context,
					       rq->fence.seqno);
					i915_request_put(rq);

					GEM_TRACE_DUMP();
					पूर्णांकel_gt_set_wedged(gt);
					err = -EIO;
					अवरोध;
				पूर्ण

				अगर (i915_request_रुको(rq, 0, HZ / 5) < 0) अणु
					काष्ठा drm_prपूर्णांकer p =
						drm_info_prपूर्णांकer(gt->i915->drm.dev);

					pr_err("i915_reset_engine(%s:%s):"
					       " failed to complete request %llx:%lld after reset\n",
					       engine->name, test_name,
					       rq->fence.context,
					       rq->fence.seqno);
					पूर्णांकel_engine_dump(engine, &p,
							  "%s\n", engine->name);
					i915_request_put(rq);

					GEM_TRACE_DUMP();
					पूर्णांकel_gt_set_wedged(gt);
					err = -EIO;
					अवरोध;
				पूर्ण

				i915_request_put(rq);
			पूर्ण

			अगर (!(flags & TEST_SELF) && !रुको_क्रम_idle(engine)) अणु
				काष्ठा drm_prपूर्णांकer p =
					drm_info_prपूर्णांकer(gt->i915->drm.dev);

				pr_err("i915_reset_engine(%s:%s):"
				       " failed to idle after reset\n",
				       engine->name, test_name);
				पूर्णांकel_engine_dump(engine, &p,
						  "%s\n", engine->name);

				err = -EIO;
				अवरोध;
			पूर्ण
		पूर्ण जबतक (समय_beक्रमe(jअगरfies, end_समय));
		clear_bit(I915_RESET_ENGINE + id, &gt->reset.flags);
		st_engine_heartbeat_enable(engine);

		pr_info("i915_reset_engine(%s:%s): %lu resets\n",
			engine->name, test_name, count);

		reported = i915_reset_engine_count(global, engine);
		reported -= thपढ़ोs[engine->id].resets;
		अगर (reported != count) अणु
			pr_err("i915_reset_engine(%s:%s): reset %lu times, but reported %lu\n",
			       engine->name, test_name, count, reported);
			अगर (!err)
				err = -EINVAL;
		पूर्ण

unwind:
		क्रम_each_engine(other, gt, पंचांगp) अणु
			पूर्णांक ret;

			अगर (!thपढ़ोs[पंचांगp].task)
				जारी;

			ret = kthपढ़ो_stop(thपढ़ोs[पंचांगp].task);
			अगर (ret) अणु
				pr_err("kthread for other engine %s failed, err=%d\n",
				       other->name, ret);
				अगर (!err)
					err = ret;
			पूर्ण
			put_task_काष्ठा(thपढ़ोs[पंचांगp].task);

			अगर (other->uabi_class != engine->uabi_class &&
			    thपढ़ोs[पंचांगp].resets !=
			    i915_reset_engine_count(global, other)) अणु
				pr_err("Innocent engine %s was reset (count=%ld)\n",
				       other->name,
				       i915_reset_engine_count(global, other) -
				       thपढ़ोs[पंचांगp].resets);
				अगर (!err)
					err = -EINVAL;
			पूर्ण
		पूर्ण

		अगर (device != i915_reset_count(global)) अणु
			pr_err("Global reset (count=%ld)!\n",
			       i915_reset_count(global) - device);
			अगर (!err)
				err = -EINVAL;
		पूर्ण

		अगर (err)
			अवरोध;

		err = igt_flush_test(gt->i915);
		अगर (err)
			अवरोध;
	पूर्ण

	अगर (पूर्णांकel_gt_is_wedged(gt))
		err = -EIO;

	अगर (flags & TEST_ACTIVE)
		hang_fini(&h);

	वापस err;
पूर्ण

अटल पूर्णांक igt_reset_engines(व्योम *arg)
अणु
	अटल स्थिर काष्ठा अणु
		स्थिर अक्षर *name;
		अचिन्हित पूर्णांक flags;
	पूर्ण phases[] = अणु
		अणु "idle", 0 पूर्ण,
		अणु "active", TEST_ACTIVE पूर्ण,
		अणु "others-idle", TEST_OTHERS पूर्ण,
		अणु "others-active", TEST_OTHERS | TEST_ACTIVE पूर्ण,
		अणु
			"others-priority",
			TEST_OTHERS | TEST_ACTIVE | TEST_PRIORITY
		पूर्ण,
		अणु
			"self-priority",
			TEST_ACTIVE | TEST_PRIORITY | TEST_SELF,
		पूर्ण,
		अणु पूर्ण
	पूर्ण;
	काष्ठा पूर्णांकel_gt *gt = arg;
	typeof(*phases) *p;
	पूर्णांक err;

	क्रम (p = phases; p->name; p++) अणु
		अगर (p->flags & TEST_PRIORITY) अणु
			अगर (!(gt->i915->caps.scheduler & I915_SCHEDULER_CAP_PRIORITY))
				जारी;
		पूर्ण

		err = __igt_reset_engines(arg, p->name, p->flags);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 fake_hangcheck(काष्ठा पूर्णांकel_gt *gt, पूर्णांकel_engine_mask_t mask)
अणु
	u32 count = i915_reset_count(&gt->i915->gpu_error);

	पूर्णांकel_gt_reset(gt, mask, शून्य);

	वापस count;
पूर्ण

अटल पूर्णांक igt_reset_रुको(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा i915_gpu_error *global = &gt->i915->gpu_error;
	काष्ठा पूर्णांकel_engine_cs *engine = gt->engine[RCS0];
	काष्ठा i915_request *rq;
	अचिन्हित पूर्णांक reset_count;
	काष्ठा hang h;
	दीर्घ समयout;
	पूर्णांक err;

	अगर (!engine || !पूर्णांकel_engine_can_store_dword(engine))
		वापस 0;

	/* Check that we detect a stuck रुकोer and issue a reset */

	igt_global_reset_lock(gt);

	err = hang_init(&h, gt);
	अगर (err)
		जाओ unlock;

	rq = hang_create_request(&h, engine);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ fini;
	पूर्ण

	i915_request_get(rq);
	i915_request_add(rq);

	अगर (!रुको_until_running(&h, rq)) अणु
		काष्ठा drm_prपूर्णांकer p = drm_info_prपूर्णांकer(gt->i915->drm.dev);

		pr_err("%s: Failed to start request %llx, at %x\n",
		       __func__, rq->fence.seqno, hws_seqno(&h, rq));
		पूर्णांकel_engine_dump(rq->engine, &p, "%s\n", rq->engine->name);

		पूर्णांकel_gt_set_wedged(gt);

		err = -EIO;
		जाओ out_rq;
	पूर्ण

	reset_count = fake_hangcheck(gt, ALL_ENGINES);

	समयout = i915_request_रुको(rq, 0, 10);
	अगर (समयout < 0) अणु
		pr_err("i915_request_wait failed on a stuck request: err=%ld\n",
		       समयout);
		err = समयout;
		जाओ out_rq;
	पूर्ण

	अगर (i915_reset_count(global) == reset_count) अणु
		pr_err("No GPU reset recorded!\n");
		err = -EINVAL;
		जाओ out_rq;
	पूर्ण

out_rq:
	i915_request_put(rq);
fini:
	hang_fini(&h);
unlock:
	igt_global_reset_unlock(gt);

	अगर (पूर्णांकel_gt_is_wedged(gt))
		वापस -EIO;

	वापस err;
पूर्ण

काष्ठा evict_vma अणु
	काष्ठा completion completion;
	काष्ठा i915_vma *vma;
पूर्ण;

अटल पूर्णांक evict_vma(व्योम *data)
अणु
	काष्ठा evict_vma *arg = data;
	काष्ठा i915_address_space *vm = arg->vma->vm;
	काष्ठा drm_mm_node evict = arg->vma->node;
	पूर्णांक err;

	complete(&arg->completion);

	mutex_lock(&vm->mutex);
	err = i915_gem_evict_क्रम_node(vm, &evict, 0);
	mutex_unlock(&vm->mutex);

	वापस err;
पूर्ण

अटल पूर्णांक evict_fence(व्योम *data)
अणु
	काष्ठा evict_vma *arg = data;
	पूर्णांक err;

	complete(&arg->completion);

	/* Mark the fence रेजिस्टर as dirty to क्रमce the mmio update. */
	err = i915_gem_object_set_tiling(arg->vma->obj, I915_TILING_Y, 512);
	अगर (err) अणु
		pr_err("Invalid Y-tiling settings; err:%d\n", err);
		वापस err;
	पूर्ण

	err = i915_vma_pin(arg->vma, 0, 0, PIN_GLOBAL | PIN_MAPPABLE);
	अगर (err) अणु
		pr_err("Unable to pin vma for Y-tiled fence; err:%d\n", err);
		वापस err;
	पूर्ण

	err = i915_vma_pin_fence(arg->vma);
	i915_vma_unpin(arg->vma);
	अगर (err) अणु
		pr_err("Unable to pin Y-tiled fence; err:%d\n", err);
		वापस err;
	पूर्ण

	i915_vma_unpin_fence(arg->vma);

	वापस 0;
पूर्ण

अटल पूर्णांक __igt_reset_evict_vma(काष्ठा पूर्णांकel_gt *gt,
				 काष्ठा i915_address_space *vm,
				 पूर्णांक (*fn)(व्योम *),
				 अचिन्हित पूर्णांक flags)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = gt->engine[RCS0];
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा task_काष्ठा *tsk = शून्य;
	काष्ठा i915_request *rq;
	काष्ठा evict_vma arg;
	काष्ठा hang h;
	अचिन्हित पूर्णांक pin_flags;
	पूर्णांक err;

	अगर (!gt->ggtt->num_fences && flags & EXEC_OBJECT_NEEDS_FENCE)
		वापस 0;

	अगर (!engine || !पूर्णांकel_engine_can_store_dword(engine))
		वापस 0;

	/* Check that we can recover an unbind stuck on a hanging request */

	err = hang_init(&h, gt);
	अगर (err)
		वापस err;

	obj = i915_gem_object_create_पूर्णांकernal(gt->i915, SZ_1M);
	अगर (IS_ERR(obj)) अणु
		err = PTR_ERR(obj);
		जाओ fini;
	पूर्ण

	अगर (flags & EXEC_OBJECT_NEEDS_FENCE) अणु
		err = i915_gem_object_set_tiling(obj, I915_TILING_X, 512);
		अगर (err) अणु
			pr_err("Invalid X-tiling settings; err:%d\n", err);
			जाओ out_obj;
		पूर्ण
	पूर्ण

	arg.vma = i915_vma_instance(obj, vm, शून्य);
	अगर (IS_ERR(arg.vma)) अणु
		err = PTR_ERR(arg.vma);
		जाओ out_obj;
	पूर्ण

	rq = hang_create_request(&h, engine);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ out_obj;
	पूर्ण

	pin_flags = i915_vma_is_ggtt(arg.vma) ? PIN_GLOBAL : PIN_USER;

	अगर (flags & EXEC_OBJECT_NEEDS_FENCE)
		pin_flags |= PIN_MAPPABLE;

	err = i915_vma_pin(arg.vma, 0, 0, pin_flags);
	अगर (err) अणु
		i915_request_add(rq);
		जाओ out_obj;
	पूर्ण

	अगर (flags & EXEC_OBJECT_NEEDS_FENCE) अणु
		err = i915_vma_pin_fence(arg.vma);
		अगर (err) अणु
			pr_err("Unable to pin X-tiled fence; err:%d\n", err);
			i915_vma_unpin(arg.vma);
			i915_request_add(rq);
			जाओ out_obj;
		पूर्ण
	पूर्ण

	i915_vma_lock(arg.vma);
	err = i915_request_aरुको_object(rq, arg.vma->obj,
					flags & EXEC_OBJECT_WRITE);
	अगर (err == 0)
		err = i915_vma_move_to_active(arg.vma, rq, flags);
	i915_vma_unlock(arg.vma);

	अगर (flags & EXEC_OBJECT_NEEDS_FENCE)
		i915_vma_unpin_fence(arg.vma);
	i915_vma_unpin(arg.vma);

	i915_request_get(rq);
	i915_request_add(rq);
	अगर (err)
		जाओ out_rq;

	अगर (!रुको_until_running(&h, rq)) अणु
		काष्ठा drm_prपूर्णांकer p = drm_info_prपूर्णांकer(gt->i915->drm.dev);

		pr_err("%s: Failed to start request %llx, at %x\n",
		       __func__, rq->fence.seqno, hws_seqno(&h, rq));
		पूर्णांकel_engine_dump(rq->engine, &p, "%s\n", rq->engine->name);

		पूर्णांकel_gt_set_wedged(gt);
		जाओ out_reset;
	पूर्ण

	init_completion(&arg.completion);

	tsk = kthपढ़ो_run(fn, &arg, "igt/evict_vma");
	अगर (IS_ERR(tsk)) अणु
		err = PTR_ERR(tsk);
		tsk = शून्य;
		जाओ out_reset;
	पूर्ण
	get_task_काष्ठा(tsk);

	रुको_क्रम_completion(&arg.completion);

	अगर (रुको_क्रम(!list_empty(&rq->fence.cb_list), 10)) अणु
		काष्ठा drm_prपूर्णांकer p = drm_info_prपूर्णांकer(gt->i915->drm.dev);

		pr_err("igt/evict_vma kthread did not wait\n");
		पूर्णांकel_engine_dump(rq->engine, &p, "%s\n", rq->engine->name);

		पूर्णांकel_gt_set_wedged(gt);
		जाओ out_reset;
	पूर्ण

out_reset:
	igt_global_reset_lock(gt);
	fake_hangcheck(gt, rq->engine->mask);
	igt_global_reset_unlock(gt);

	अगर (tsk) अणु
		काष्ठा पूर्णांकel_wedge_me w;

		/* The reset, even indirectly, should take less than 10ms. */
		पूर्णांकel_wedge_on_समयout(&w, gt, HZ / 10 /* 100ms */)
			err = kthपढ़ो_stop(tsk);

		put_task_काष्ठा(tsk);
	पूर्ण

out_rq:
	i915_request_put(rq);
out_obj:
	i915_gem_object_put(obj);
fini:
	hang_fini(&h);
	अगर (पूर्णांकel_gt_is_wedged(gt))
		वापस -EIO;

	वापस err;
पूर्ण

अटल पूर्णांक igt_reset_evict_ggtt(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;

	वापस __igt_reset_evict_vma(gt, &gt->ggtt->vm,
				     evict_vma, EXEC_OBJECT_WRITE);
पूर्ण

अटल पूर्णांक igt_reset_evict_ppgtt(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा i915_ppgtt *ppgtt;
	पूर्णांक err;

	/* aliasing == global gtt locking, covered above */
	अगर (INTEL_PPGTT(gt->i915) < INTEL_PPGTT_FULL)
		वापस 0;

	ppgtt = i915_ppgtt_create(gt);
	अगर (IS_ERR(ppgtt))
		वापस PTR_ERR(ppgtt);

	err = __igt_reset_evict_vma(gt, &ppgtt->vm,
				    evict_vma, EXEC_OBJECT_WRITE);
	i915_vm_put(&ppgtt->vm);

	वापस err;
पूर्ण

अटल पूर्णांक igt_reset_evict_fence(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;

	वापस __igt_reset_evict_vma(gt, &gt->ggtt->vm,
				     evict_fence, EXEC_OBJECT_NEEDS_FENCE);
पूर्ण

अटल पूर्णांक रुको_क्रम_others(काष्ठा पूर्णांकel_gt *gt,
			   काष्ठा पूर्णांकel_engine_cs *exclude)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;

	क्रम_each_engine(engine, gt, id) अणु
		अगर (engine == exclude)
			जारी;

		अगर (!रुको_क्रम_idle(engine))
			वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक igt_reset_queue(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा i915_gpu_error *global = &gt->i915->gpu_error;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	काष्ठा hang h;
	पूर्णांक err;

	/* Check that we replay pending requests following a hang */

	igt_global_reset_lock(gt);

	err = hang_init(&h, gt);
	अगर (err)
		जाओ unlock;

	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा i915_request *prev;
		IGT_TIMEOUT(end_समय);
		अचिन्हित पूर्णांक count;

		अगर (!पूर्णांकel_engine_can_store_dword(engine))
			जारी;

		prev = hang_create_request(&h, engine);
		अगर (IS_ERR(prev)) अणु
			err = PTR_ERR(prev);
			जाओ fini;
		पूर्ण

		i915_request_get(prev);
		i915_request_add(prev);

		count = 0;
		करो अणु
			काष्ठा i915_request *rq;
			अचिन्हित पूर्णांक reset_count;

			rq = hang_create_request(&h, engine);
			अगर (IS_ERR(rq)) अणु
				err = PTR_ERR(rq);
				जाओ fini;
			पूर्ण

			i915_request_get(rq);
			i915_request_add(rq);

			/*
			 * XXX We करोn't handle resetting the kernel context
			 * very well. If we trigger a device reset twice in
			 * quick succession जबतक the kernel context is
			 * executing, we may end up skipping the bपढ़ोcrumb.
			 * This is really only a problem क्रम the selftest as
			 * normally there is a large पूर्णांकerlude between resets
			 * (hangcheck), or we focus on resetting just one
			 * engine and so aव्योम repeatedly resetting innocents.
			 */
			err = रुको_क्रम_others(gt, engine);
			अगर (err) अणु
				pr_err("%s(%s): Failed to idle other inactive engines after device reset\n",
				       __func__, engine->name);
				i915_request_put(rq);
				i915_request_put(prev);

				GEM_TRACE_DUMP();
				पूर्णांकel_gt_set_wedged(gt);
				जाओ fini;
			पूर्ण

			अगर (!रुको_until_running(&h, prev)) अणु
				काष्ठा drm_prपूर्णांकer p = drm_info_prपूर्णांकer(gt->i915->drm.dev);

				pr_err("%s(%s): Failed to start request %llx, at %x\n",
				       __func__, engine->name,
				       prev->fence.seqno, hws_seqno(&h, prev));
				पूर्णांकel_engine_dump(engine, &p,
						  "%s\n", engine->name);

				i915_request_put(rq);
				i915_request_put(prev);

				पूर्णांकel_gt_set_wedged(gt);

				err = -EIO;
				जाओ fini;
			पूर्ण

			reset_count = fake_hangcheck(gt, BIT(id));

			अगर (prev->fence.error != -EIO) अणु
				pr_err("GPU reset not recorded on hanging request [fence.error=%d]!\n",
				       prev->fence.error);
				i915_request_put(rq);
				i915_request_put(prev);
				err = -EINVAL;
				जाओ fini;
			पूर्ण

			अगर (rq->fence.error) अणु
				pr_err("Fence error status not zero [%d] after unrelated reset\n",
				       rq->fence.error);
				i915_request_put(rq);
				i915_request_put(prev);
				err = -EINVAL;
				जाओ fini;
			पूर्ण

			अगर (i915_reset_count(global) == reset_count) अणु
				pr_err("No GPU reset recorded!\n");
				i915_request_put(rq);
				i915_request_put(prev);
				err = -EINVAL;
				जाओ fini;
			पूर्ण

			i915_request_put(prev);
			prev = rq;
			count++;
		पूर्ण जबतक (समय_beक्रमe(jअगरfies, end_समय));
		pr_info("%s: Completed %d queued resets\n",
			engine->name, count);

		*h.batch = MI_BATCH_BUFFER_END;
		पूर्णांकel_gt_chipset_flush(engine->gt);

		i915_request_put(prev);

		err = igt_flush_test(gt->i915);
		अगर (err)
			अवरोध;
	पूर्ण

fini:
	hang_fini(&h);
unlock:
	igt_global_reset_unlock(gt);

	अगर (पूर्णांकel_gt_is_wedged(gt))
		वापस -EIO;

	वापस err;
पूर्ण

अटल पूर्णांक igt_handle_error(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा i915_gpu_error *global = &gt->i915->gpu_error;
	काष्ठा पूर्णांकel_engine_cs *engine = gt->engine[RCS0];
	काष्ठा hang h;
	काष्ठा i915_request *rq;
	काष्ठा i915_gpu_coredump *error;
	पूर्णांक err;

	/* Check that we can issue a global GPU and engine reset */

	अगर (!पूर्णांकel_has_reset_engine(gt))
		वापस 0;

	अगर (!engine || !पूर्णांकel_engine_can_store_dword(engine))
		वापस 0;

	err = hang_init(&h, gt);
	अगर (err)
		वापस err;

	rq = hang_create_request(&h, engine);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ err_fini;
	पूर्ण

	i915_request_get(rq);
	i915_request_add(rq);

	अगर (!रुको_until_running(&h, rq)) अणु
		काष्ठा drm_prपूर्णांकer p = drm_info_prपूर्णांकer(gt->i915->drm.dev);

		pr_err("%s: Failed to start request %llx, at %x\n",
		       __func__, rq->fence.seqno, hws_seqno(&h, rq));
		पूर्णांकel_engine_dump(rq->engine, &p, "%s\n", rq->engine->name);

		पूर्णांकel_gt_set_wedged(gt);

		err = -EIO;
		जाओ err_request;
	पूर्ण

	/* Temporarily disable error capture */
	error = xchg(&global->first_error, (व्योम *)-1);

	पूर्णांकel_gt_handle_error(gt, engine->mask, 0, शून्य);

	xchg(&global->first_error, error);

	अगर (rq->fence.error != -EIO) अणु
		pr_err("Guilty request not identified!\n");
		err = -EINVAL;
		जाओ err_request;
	पूर्ण

err_request:
	i915_request_put(rq);
err_fini:
	hang_fini(&h);
	वापस err;
पूर्ण

अटल पूर्णांक __igt_atomic_reset_engine(काष्ठा पूर्णांकel_engine_cs *engine,
				     स्थिर काष्ठा igt_atomic_section *p,
				     स्थिर अक्षर *mode)
अणु
	काष्ठा tasklet_काष्ठा * स्थिर t = &engine->execlists.tasklet;
	पूर्णांक err;

	GEM_TRACE("i915_reset_engine(%s:%s) under %s\n",
		  engine->name, mode, p->name);

	अगर (t->func)
		tasklet_disable(t);
	अगर (म_भेद(p->name, "softirq"))
		local_bh_disable();
	p->critical_section_begin();

	err = __पूर्णांकel_engine_reset_bh(engine, शून्य);

	p->critical_section_end();
	अगर (म_भेद(p->name, "softirq"))
		local_bh_enable();
	अगर (t->func) अणु
		tasklet_enable(t);
		tasklet_hi_schedule(t);
	पूर्ण

	अगर (err)
		pr_err("i915_reset_engine(%s:%s) failed under %s\n",
		       engine->name, mode, p->name);

	वापस err;
पूर्ण

अटल पूर्णांक igt_atomic_reset_engine(काष्ठा पूर्णांकel_engine_cs *engine,
				   स्थिर काष्ठा igt_atomic_section *p)
अणु
	काष्ठा i915_request *rq;
	काष्ठा hang h;
	पूर्णांक err;

	err = __igt_atomic_reset_engine(engine, p, "idle");
	अगर (err)
		वापस err;

	err = hang_init(&h, engine->gt);
	अगर (err)
		वापस err;

	rq = hang_create_request(&h, engine);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ out;
	पूर्ण

	i915_request_get(rq);
	i915_request_add(rq);

	अगर (रुको_until_running(&h, rq)) अणु
		err = __igt_atomic_reset_engine(engine, p, "active");
	पूर्ण अन्यथा अणु
		pr_err("%s(%s): Failed to start request %llx, at %x\n",
		       __func__, engine->name,
		       rq->fence.seqno, hws_seqno(&h, rq));
		पूर्णांकel_gt_set_wedged(engine->gt);
		err = -EIO;
	पूर्ण

	अगर (err == 0) अणु
		काष्ठा पूर्णांकel_wedge_me w;

		पूर्णांकel_wedge_on_समयout(&w, engine->gt, HZ / 20 /* 50ms */)
			i915_request_रुको(rq, 0, MAX_SCHEDULE_TIMEOUT);
		अगर (पूर्णांकel_gt_is_wedged(engine->gt))
			err = -EIO;
	पूर्ण

	i915_request_put(rq);
out:
	hang_fini(&h);
	वापस err;
पूर्ण

अटल पूर्णांक igt_reset_engines_atomic(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	स्थिर typeof(*igt_atomic_phases) *p;
	पूर्णांक err = 0;

	/* Check that the engines resets are usable from atomic context */

	अगर (!पूर्णांकel_has_reset_engine(gt))
		वापस 0;

	अगर (पूर्णांकel_uc_uses_guc_submission(&gt->uc))
		वापस 0;

	igt_global_reset_lock(gt);

	/* Flush any requests beक्रमe we get started and check basics */
	अगर (!igt_क्रमce_reset(gt))
		जाओ unlock;

	क्रम (p = igt_atomic_phases; p->name; p++) अणु
		काष्ठा पूर्णांकel_engine_cs *engine;
		क्रमागत पूर्णांकel_engine_id id;

		क्रम_each_engine(engine, gt, id) अणु
			err = igt_atomic_reset_engine(engine, p);
			अगर (err)
				जाओ out;
		पूर्ण
	पूर्ण

out:
	/* As we poke around the guts, करो a full reset beक्रमe continuing. */
	igt_क्रमce_reset(gt);
unlock:
	igt_global_reset_unlock(gt);

	वापस err;
पूर्ण

पूर्णांक पूर्णांकel_hangcheck_live_selftests(काष्ठा drm_i915_निजी *i915)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(igt_hang_sanitycheck),
		SUBTEST(igt_reset_nop),
		SUBTEST(igt_reset_nop_engine),
		SUBTEST(igt_reset_idle_engine),
		SUBTEST(igt_reset_active_engine),
		SUBTEST(igt_reset_fail_engine),
		SUBTEST(igt_reset_engines),
		SUBTEST(igt_reset_engines_atomic),
		SUBTEST(igt_reset_queue),
		SUBTEST(igt_reset_रुको),
		SUBTEST(igt_reset_evict_ggtt),
		SUBTEST(igt_reset_evict_ppgtt),
		SUBTEST(igt_reset_evict_fence),
		SUBTEST(igt_handle_error),
	पूर्ण;
	काष्ठा पूर्णांकel_gt *gt = &i915->gt;
	पूर्णांकel_wakeref_t wakeref;
	पूर्णांक err;

	अगर (!पूर्णांकel_has_gpu_reset(gt))
		वापस 0;

	अगर (पूर्णांकel_gt_is_wedged(gt))
		वापस -EIO; /* we're दीर्घ past hope of a successful reset */

	wakeref = पूर्णांकel_runसमय_pm_get(gt->uncore->rpm);

	err = पूर्णांकel_gt_live_subtests(tests, gt);

	पूर्णांकel_runसमय_pm_put(gt->uncore->rpm, wakeref);

	वापस err;
पूर्ण
