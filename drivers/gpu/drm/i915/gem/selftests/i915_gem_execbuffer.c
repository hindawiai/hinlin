<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#समावेश "i915_selftest.h"

#समावेश "gt/intel_engine_pm.h"
#समावेश "selftests/igt_flush_test.h"

अटल u64 पढ़ो_reloc(स्थिर u32 *map, पूर्णांक x, स्थिर u64 mask)
अणु
	u64 reloc;

	स_नकल(&reloc, &map[x], माप(reloc));
	वापस reloc & mask;
पूर्ण

अटल पूर्णांक __igt_gpu_reloc(काष्ठा i915_execbuffer *eb,
			   काष्ठा drm_i915_gem_object *obj)
अणु
	स्थिर अचिन्हित पूर्णांक offsets[] = अणु 8, 3, 0 पूर्ण;
	स्थिर u64 mask =
		GENMASK_ULL(eb->reloc_cache.use_64bit_reloc ? 63 : 31, 0);
	स्थिर u32 *map = page_mask_bits(obj->mm.mapping);
	काष्ठा i915_request *rq;
	काष्ठा i915_vma *vma;
	पूर्णांक err;
	पूर्णांक i;

	vma = i915_vma_instance(obj, eb->context->vm, शून्य);
	अगर (IS_ERR(vma))
		वापस PTR_ERR(vma);

	err = i915_gem_object_lock(obj, &eb->ww);
	अगर (err)
		वापस err;

	err = i915_vma_pin_ww(vma, &eb->ww, 0, 0, PIN_USER | PIN_HIGH);
	अगर (err)
		वापस err;

	/* 8-Byte aligned */
	err = __reloc_entry_gpu(eb, vma, offsets[0] * माप(u32), 0);
	अगर (err <= 0)
		जाओ reloc_err;

	/* !8-Byte aligned */
	err = __reloc_entry_gpu(eb, vma, offsets[1] * माप(u32), 1);
	अगर (err <= 0)
		जाओ reloc_err;

	/* Skip to the end of the cmd page */
	i = PAGE_SIZE / माप(u32) - 1;
	i -= eb->reloc_cache.rq_size;
	स_रखो32(eb->reloc_cache.rq_cmd + eb->reloc_cache.rq_size,
		 MI_NOOP, i);
	eb->reloc_cache.rq_size += i;

	/* Force next batch */
	err = __reloc_entry_gpu(eb, vma, offsets[2] * माप(u32), 2);
	अगर (err <= 0)
		जाओ reloc_err;

	GEM_BUG_ON(!eb->reloc_cache.rq);
	rq = i915_request_get(eb->reloc_cache.rq);
	reloc_gpu_flush(eb, &eb->reloc_cache);
	GEM_BUG_ON(eb->reloc_cache.rq);

	err = i915_gem_object_रुको(obj, I915_WAIT_INTERRUPTIBLE, HZ / 2);
	अगर (err) अणु
		पूर्णांकel_gt_set_wedged(eb->engine->gt);
		जाओ put_rq;
	पूर्ण

	अगर (!i915_request_completed(rq)) अणु
		pr_err("%s: did not wait for relocations!\n", eb->engine->name);
		err = -EINVAL;
		जाओ put_rq;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(offsets); i++) अणु
		u64 reloc = पढ़ो_reloc(map, offsets[i], mask);

		अगर (reloc != i) अणु
			pr_err("%s[%d]: map[%d] %llx != %x\n",
			       eb->engine->name, i, offsets[i], reloc, i);
			err = -EINVAL;
		पूर्ण
	पूर्ण
	अगर (err)
		igt_hexdump(map, 4096);

put_rq:
	i915_request_put(rq);
unpin_vma:
	i915_vma_unpin(vma);
	वापस err;

reloc_err:
	अगर (!err)
		err = -EIO;
	जाओ unpin_vma;
पूर्ण

अटल पूर्णांक igt_gpu_reloc(व्योम *arg)
अणु
	काष्ठा i915_execbuffer eb;
	काष्ठा drm_i915_gem_object *scratch;
	पूर्णांक err = 0;
	u32 *map;

	eb.i915 = arg;

	scratch = i915_gem_object_create_पूर्णांकernal(eb.i915, 4096);
	अगर (IS_ERR(scratch))
		वापस PTR_ERR(scratch);

	map = i915_gem_object_pin_map_unlocked(scratch, I915_MAP_WC);
	अगर (IS_ERR(map)) अणु
		err = PTR_ERR(map);
		जाओ err_scratch;
	पूर्ण

	पूर्णांकel_gt_pm_get(&eb.i915->gt);

	क्रम_each_uabi_engine(eb.engine, eb.i915) अणु
		reloc_cache_init(&eb.reloc_cache, eb.i915);
		स_रखो(map, POISON_INUSE, 4096);

		पूर्णांकel_engine_pm_get(eb.engine);
		eb.context = पूर्णांकel_context_create(eb.engine);
		अगर (IS_ERR(eb.context)) अणु
			err = PTR_ERR(eb.context);
			जाओ err_pm;
		पूर्ण
		eb.reloc_pool = शून्य;
		eb.reloc_context = शून्य;

		i915_gem_ww_ctx_init(&eb.ww, false);
retry:
		err = पूर्णांकel_context_pin_ww(eb.context, &eb.ww);
		अगर (!err) अणु
			err = __igt_gpu_reloc(&eb, scratch);

			पूर्णांकel_context_unpin(eb.context);
		पूर्ण
		अगर (err == -EDEADLK) अणु
			err = i915_gem_ww_ctx_backoff(&eb.ww);
			अगर (!err)
				जाओ retry;
		पूर्ण
		i915_gem_ww_ctx_fini(&eb.ww);

		अगर (eb.reloc_pool)
			पूर्णांकel_gt_buffer_pool_put(eb.reloc_pool);
		अगर (eb.reloc_context)
			पूर्णांकel_context_put(eb.reloc_context);

		पूर्णांकel_context_put(eb.context);
err_pm:
		पूर्णांकel_engine_pm_put(eb.engine);
		अगर (err)
			अवरोध;
	पूर्ण

	अगर (igt_flush_test(eb.i915))
		err = -EIO;

	पूर्णांकel_gt_pm_put(&eb.i915->gt);
err_scratch:
	i915_gem_object_put(scratch);
	वापस err;
पूर्ण

पूर्णांक i915_gem_execbuffer_live_selftests(काष्ठा drm_i915_निजी *i915)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(igt_gpu_reloc),
	पूर्ण;

	अगर (पूर्णांकel_gt_is_wedged(&i915->gt))
		वापस 0;

	वापस i915_live_subtests(tests, i915);
पूर्ण
