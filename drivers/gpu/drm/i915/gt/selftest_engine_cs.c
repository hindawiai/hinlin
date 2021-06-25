<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright तऊ 2018 Intel Corporation
 */

#समावेश <linux/sort.h>

#समावेश "intel_gpu_commands.h"
#समावेश "intel_gt_pm.h"
#समावेश "intel_rps.h"

#समावेश "i915_selftest.h"
#समावेश "selftests/igt_flush_test.h"

#घोषणा COUNT 5

अटल पूर्णांक cmp_u32(स्थिर व्योम *A, स्थिर व्योम *B)
अणु
	स्थिर u32 *a = A, *b = B;

	वापस *a - *b;
पूर्ण

अटल व्योम perf_begin(काष्ठा पूर्णांकel_gt *gt)
अणु
	पूर्णांकel_gt_pm_get(gt);

	/* Boost gpufreq to max [रुकोboost] and keep it fixed */
	atomic_inc(&gt->rps.num_रुकोers);
	schedule_work(&gt->rps.work);
	flush_work(&gt->rps.work);
पूर्ण

अटल पूर्णांक perf_end(काष्ठा पूर्णांकel_gt *gt)
अणु
	atomic_dec(&gt->rps.num_रुकोers);
	पूर्णांकel_gt_pm_put(gt);

	वापस igt_flush_test(gt->i915);
पूर्ण

अटल पूर्णांक ग_लिखो_बारtamp(काष्ठा i915_request *rq, पूर्णांक slot)
अणु
	काष्ठा पूर्णांकel_समयline *tl =
		rcu_dereference_रक्षित(rq->समयline,
					  !i915_request_संकेतed(rq));
	u32 cmd;
	u32 *cs;

	cs = पूर्णांकel_ring_begin(rq, 4);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	cmd = MI_STORE_REGISTER_MEM | MI_USE_GGTT;
	अगर (INTEL_GEN(rq->engine->i915) >= 8)
		cmd++;
	*cs++ = cmd;
	*cs++ = i915_mmio_reg_offset(RING_TIMESTAMP(rq->engine->mmio_base));
	*cs++ = tl->hwsp_offset + slot * माप(u32);
	*cs++ = 0;

	पूर्णांकel_ring_advance(rq, cs);

	वापस 0;
पूर्ण

अटल काष्ठा i915_vma *create_empty_batch(काष्ठा पूर्णांकel_context *ce)
अणु
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_vma *vma;
	u32 *cs;
	पूर्णांक err;

	obj = i915_gem_object_create_पूर्णांकernal(ce->engine->i915, PAGE_SIZE);
	अगर (IS_ERR(obj))
		वापस ERR_CAST(obj);

	cs = i915_gem_object_pin_map_unlocked(obj, I915_MAP_WB);
	अगर (IS_ERR(cs)) अणु
		err = PTR_ERR(cs);
		जाओ err_put;
	पूर्ण

	cs[0] = MI_BATCH_BUFFER_END;

	i915_gem_object_flush_map(obj);

	vma = i915_vma_instance(obj, ce->vm, शून्य);
	अगर (IS_ERR(vma)) अणु
		err = PTR_ERR(vma);
		जाओ err_unpin;
	पूर्ण

	err = i915_vma_pin(vma, 0, 0, PIN_USER);
	अगर (err)
		जाओ err_unpin;

	i915_gem_object_unpin_map(obj);
	वापस vma;

err_unpin:
	i915_gem_object_unpin_map(obj);
err_put:
	i915_gem_object_put(obj);
	वापस ERR_PTR(err);
पूर्ण

अटल u32 trअगरilter(u32 *a)
अणु
	u64 sum;

	sort(a, COUNT, माप(*a), cmp_u32, शून्य);

	sum = mul_u32_u32(a[2], 2);
	sum += a[1];
	sum += a[3];

	वापस sum >> 2;
पूर्ण

अटल पूर्णांक perf_mi_bb_start(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err = 0;

	अगर (INTEL_GEN(gt->i915) < 7) /* क्रम per-engine CS_TIMESTAMP */
		वापस 0;

	perf_begin(gt);
	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा पूर्णांकel_context *ce = engine->kernel_context;
		काष्ठा i915_vma *batch;
		u32 cycles[COUNT];
		पूर्णांक i;

		पूर्णांकel_engine_pm_get(engine);

		batch = create_empty_batch(ce);
		अगर (IS_ERR(batch)) अणु
			err = PTR_ERR(batch);
			पूर्णांकel_engine_pm_put(engine);
			अवरोध;
		पूर्ण

		err = i915_vma_sync(batch);
		अगर (err) अणु
			पूर्णांकel_engine_pm_put(engine);
			i915_vma_put(batch);
			अवरोध;
		पूर्ण

		क्रम (i = 0; i < ARRAY_SIZE(cycles); i++) अणु
			काष्ठा i915_request *rq;

			rq = i915_request_create(ce);
			अगर (IS_ERR(rq)) अणु
				err = PTR_ERR(rq);
				अवरोध;
			पूर्ण

			err = ग_लिखो_बारtamp(rq, 2);
			अगर (err)
				जाओ out;

			err = rq->engine->emit_bb_start(rq,
							batch->node.start, 8,
							0);
			अगर (err)
				जाओ out;

			err = ग_लिखो_बारtamp(rq, 3);
			अगर (err)
				जाओ out;

out:
			i915_request_get(rq);
			i915_request_add(rq);

			अगर (i915_request_रुको(rq, 0, HZ / 5) < 0)
				err = -EIO;
			i915_request_put(rq);
			अगर (err)
				अवरोध;

			cycles[i] = rq->hwsp_seqno[3] - rq->hwsp_seqno[2];
		पूर्ण
		i915_vma_put(batch);
		पूर्णांकel_engine_pm_put(engine);
		अगर (err)
			अवरोध;

		pr_info("%s: MI_BB_START cycles: %u\n",
			engine->name, trअगरilter(cycles));
	पूर्ण
	अगर (perf_end(gt))
		err = -EIO;

	वापस err;
पूर्ण

अटल काष्ठा i915_vma *create_nop_batch(काष्ठा पूर्णांकel_context *ce)
अणु
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_vma *vma;
	u32 *cs;
	पूर्णांक err;

	obj = i915_gem_object_create_पूर्णांकernal(ce->engine->i915, SZ_64K);
	अगर (IS_ERR(obj))
		वापस ERR_CAST(obj);

	cs = i915_gem_object_pin_map_unlocked(obj, I915_MAP_WB);
	अगर (IS_ERR(cs)) अणु
		err = PTR_ERR(cs);
		जाओ err_put;
	पूर्ण

	स_रखो(cs, 0, SZ_64K);
	cs[SZ_64K / माप(*cs) - 1] = MI_BATCH_BUFFER_END;

	i915_gem_object_flush_map(obj);

	vma = i915_vma_instance(obj, ce->vm, शून्य);
	अगर (IS_ERR(vma)) अणु
		err = PTR_ERR(vma);
		जाओ err_unpin;
	पूर्ण

	err = i915_vma_pin(vma, 0, 0, PIN_USER);
	अगर (err)
		जाओ err_unpin;

	i915_gem_object_unpin_map(obj);
	वापस vma;

err_unpin:
	i915_gem_object_unpin_map(obj);
err_put:
	i915_gem_object_put(obj);
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक perf_mi_noop(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_gt *gt = arg;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	पूर्णांक err = 0;

	अगर (INTEL_GEN(gt->i915) < 7) /* क्रम per-engine CS_TIMESTAMP */
		वापस 0;

	perf_begin(gt);
	क्रम_each_engine(engine, gt, id) अणु
		काष्ठा पूर्णांकel_context *ce = engine->kernel_context;
		काष्ठा i915_vma *base, *nop;
		u32 cycles[COUNT];
		पूर्णांक i;

		पूर्णांकel_engine_pm_get(engine);

		base = create_empty_batch(ce);
		अगर (IS_ERR(base)) अणु
			err = PTR_ERR(base);
			पूर्णांकel_engine_pm_put(engine);
			अवरोध;
		पूर्ण

		err = i915_vma_sync(base);
		अगर (err) अणु
			i915_vma_put(base);
			पूर्णांकel_engine_pm_put(engine);
			अवरोध;
		पूर्ण

		nop = create_nop_batch(ce);
		अगर (IS_ERR(nop)) अणु
			err = PTR_ERR(nop);
			i915_vma_put(base);
			पूर्णांकel_engine_pm_put(engine);
			अवरोध;
		पूर्ण

		err = i915_vma_sync(nop);
		अगर (err) अणु
			i915_vma_put(nop);
			i915_vma_put(base);
			पूर्णांकel_engine_pm_put(engine);
			अवरोध;
		पूर्ण

		क्रम (i = 0; i < ARRAY_SIZE(cycles); i++) अणु
			काष्ठा i915_request *rq;

			rq = i915_request_create(ce);
			अगर (IS_ERR(rq)) अणु
				err = PTR_ERR(rq);
				अवरोध;
			पूर्ण

			err = ग_लिखो_बारtamp(rq, 2);
			अगर (err)
				जाओ out;

			err = rq->engine->emit_bb_start(rq,
							base->node.start, 8,
							0);
			अगर (err)
				जाओ out;

			err = ग_लिखो_बारtamp(rq, 3);
			अगर (err)
				जाओ out;

			err = rq->engine->emit_bb_start(rq,
							nop->node.start,
							nop->node.size,
							0);
			अगर (err)
				जाओ out;

			err = ग_लिखो_बारtamp(rq, 4);
			अगर (err)
				जाओ out;

out:
			i915_request_get(rq);
			i915_request_add(rq);

			अगर (i915_request_रुको(rq, 0, HZ / 5) < 0)
				err = -EIO;
			i915_request_put(rq);
			अगर (err)
				अवरोध;

			cycles[i] =
				(rq->hwsp_seqno[4] - rq->hwsp_seqno[3]) -
				(rq->hwsp_seqno[3] - rq->hwsp_seqno[2]);
		पूर्ण
		i915_vma_put(nop);
		i915_vma_put(base);
		पूर्णांकel_engine_pm_put(engine);
		अगर (err)
			अवरोध;

		pr_info("%s: 16K MI_NOOP cycles: %u\n",
			engine->name, trअगरilter(cycles));
	पूर्ण
	अगर (perf_end(gt))
		err = -EIO;

	वापस err;
पूर्ण

पूर्णांक पूर्णांकel_engine_cs_perf_selftests(काष्ठा drm_i915_निजी *i915)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(perf_mi_bb_start),
		SUBTEST(perf_mi_noop),
	पूर्ण;

	अगर (पूर्णांकel_gt_is_wedged(&i915->gt))
		वापस 0;

	वापस पूर्णांकel_gt_live_subtests(tests, &i915->gt);
पूर्ण

अटल पूर्णांक पूर्णांकel_mmio_bases_check(व्योम *arg)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < ARRAY_SIZE(पूर्णांकel_engines); i++) अणु
		स्थिर काष्ठा engine_info *info = &पूर्णांकel_engines[i];
		u8 prev = U8_MAX;

		क्रम (j = 0; j < MAX_MMIO_BASES; j++) अणु
			u8 gen = info->mmio_bases[j].gen;
			u32 base = info->mmio_bases[j].base;

			अगर (gen >= prev) अणु
				pr_err("%s(%s, class:%d, instance:%d): mmio base for gen %x is before the one for gen %x\n",
				       __func__,
				       पूर्णांकel_engine_class_repr(info->class),
				       info->class, info->instance,
				       prev, gen);
				वापस -EINVAL;
			पूर्ण

			अगर (gen == 0)
				अवरोध;

			अगर (!base) अणु
				pr_err("%s(%s, class:%d, instance:%d): invalid mmio base (%x) for gen %x at entry %u\n",
				       __func__,
				       पूर्णांकel_engine_class_repr(info->class),
				       info->class, info->instance,
				       base, gen, j);
				वापस -EINVAL;
			पूर्ण

			prev = gen;
		पूर्ण

		pr_debug("%s: min gen supported for %s%d is %d\n",
			 __func__,
			 पूर्णांकel_engine_class_repr(info->class),
			 info->instance,
			 prev);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_engine_cs_mock_selftests(व्योम)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(पूर्णांकel_mmio_bases_check),
	पूर्ण;

	वापस i915_subtests(tests, शून्य);
पूर्ण
