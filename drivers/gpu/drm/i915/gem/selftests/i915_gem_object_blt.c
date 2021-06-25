<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश <linux/sort.h>

#समावेश "gt/intel_gt.h"
#समावेश "gt/intel_engine_user.h"

#समावेश "i915_selftest.h"

#समावेश "gem/i915_gem_context.h"
#समावेश "selftests/igt_flush_test.h"
#समावेश "selftests/i915_random.h"
#समावेश "selftests/mock_drm.h"
#समावेश "huge_gem_object.h"
#समावेश "mock_context.h"

अटल पूर्णांक wrap_kसमय_compare(स्थिर व्योम *A, स्थिर व्योम *B)
अणु
	स्थिर kसमय_प्रकार *a = A, *b = B;

	वापस kसमय_compare(*a, *b);
पूर्ण

अटल पूर्णांक __perf_fill_blt(काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(obj->base.dev);
	पूर्णांक inst = 0;

	करो अणु
		काष्ठा पूर्णांकel_engine_cs *engine;
		kसमय_प्रकार t[5];
		पूर्णांक pass;
		पूर्णांक err;

		engine = पूर्णांकel_engine_lookup_user(i915,
						  I915_ENGINE_CLASS_COPY,
						  inst++);
		अगर (!engine)
			वापस 0;

		पूर्णांकel_engine_pm_get(engine);
		क्रम (pass = 0; pass < ARRAY_SIZE(t); pass++) अणु
			काष्ठा पूर्णांकel_context *ce = engine->kernel_context;
			kसमय_प्रकार t0, t1;

			t0 = kसमय_get();

			err = i915_gem_object_fill_blt(obj, ce, 0);
			अगर (err)
				अवरोध;

			err = i915_gem_object_रुको(obj,
						   I915_WAIT_ALL,
						   MAX_SCHEDULE_TIMEOUT);
			अगर (err)
				अवरोध;

			t1 = kसमय_get();
			t[pass] = kसमय_sub(t1, t0);
		पूर्ण
		पूर्णांकel_engine_pm_put(engine);
		अगर (err)
			वापस err;

		sort(t, ARRAY_SIZE(t), माप(*t), wrap_kसमय_compare, शून्य);
		pr_info("%s: blt %zd KiB fill: %lld MiB/s\n",
			engine->name,
			obj->base.size >> 10,
			भाग64_u64(mul_u32_u32(4 * obj->base.size,
					      1000 * 1000 * 1000),
				  t[1] + 2 * t[2] + t[3]) >> 20);
	पूर्ण जबतक (1);
पूर्ण

अटल पूर्णांक perf_fill_blt(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	अटल स्थिर अचिन्हित दीर्घ sizes[] = अणु
		SZ_4K,
		SZ_64K,
		SZ_2M,
		SZ_64M
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(sizes); i++) अणु
		काष्ठा drm_i915_gem_object *obj;
		पूर्णांक err;

		obj = i915_gem_object_create_पूर्णांकernal(i915, sizes[i]);
		अगर (IS_ERR(obj))
			वापस PTR_ERR(obj);

		err = __perf_fill_blt(obj);
		i915_gem_object_put(obj);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __perf_copy_blt(काष्ठा drm_i915_gem_object *src,
			   काष्ठा drm_i915_gem_object *dst)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(src->base.dev);
	पूर्णांक inst = 0;

	करो अणु
		काष्ठा पूर्णांकel_engine_cs *engine;
		kसमय_प्रकार t[5];
		पूर्णांक pass;
		पूर्णांक err = 0;

		engine = पूर्णांकel_engine_lookup_user(i915,
						  I915_ENGINE_CLASS_COPY,
						  inst++);
		अगर (!engine)
			वापस 0;

		पूर्णांकel_engine_pm_get(engine);
		क्रम (pass = 0; pass < ARRAY_SIZE(t); pass++) अणु
			काष्ठा पूर्णांकel_context *ce = engine->kernel_context;
			kसमय_प्रकार t0, t1;

			t0 = kसमय_get();

			err = i915_gem_object_copy_blt(src, dst, ce);
			अगर (err)
				अवरोध;

			err = i915_gem_object_रुको(dst,
						   I915_WAIT_ALL,
						   MAX_SCHEDULE_TIMEOUT);
			अगर (err)
				अवरोध;

			t1 = kसमय_get();
			t[pass] = kसमय_sub(t1, t0);
		पूर्ण
		पूर्णांकel_engine_pm_put(engine);
		अगर (err)
			वापस err;

		sort(t, ARRAY_SIZE(t), माप(*t), wrap_kसमय_compare, शून्य);
		pr_info("%s: blt %zd KiB copy: %lld MiB/s\n",
			engine->name,
			src->base.size >> 10,
			भाग64_u64(mul_u32_u32(4 * src->base.size,
					      1000 * 1000 * 1000),
				  t[1] + 2 * t[2] + t[3]) >> 20);
	पूर्ण जबतक (1);
पूर्ण

अटल पूर्णांक perf_copy_blt(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	अटल स्थिर अचिन्हित दीर्घ sizes[] = अणु
		SZ_4K,
		SZ_64K,
		SZ_2M,
		SZ_64M
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(sizes); i++) अणु
		काष्ठा drm_i915_gem_object *src, *dst;
		पूर्णांक err;

		src = i915_gem_object_create_पूर्णांकernal(i915, sizes[i]);
		अगर (IS_ERR(src))
			वापस PTR_ERR(src);

		dst = i915_gem_object_create_पूर्णांकernal(i915, sizes[i]);
		अगर (IS_ERR(dst)) अणु
			err = PTR_ERR(dst);
			जाओ err_src;
		पूर्ण

		err = __perf_copy_blt(src, dst);

		i915_gem_object_put(dst);
err_src:
		i915_gem_object_put(src);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा igt_thपढ़ो_arg अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा i915_gem_context *ctx;
	काष्ठा file *file;
	काष्ठा rnd_state prng;
	अचिन्हित पूर्णांक n_cpus;
पूर्ण;

अटल पूर्णांक igt_fill_blt_thपढ़ो(व्योम *arg)
अणु
	काष्ठा igt_thपढ़ो_arg *thपढ़ो = arg;
	काष्ठा पूर्णांकel_engine_cs *engine = thपढ़ो->engine;
	काष्ठा rnd_state *prng = &thपढ़ो->prng;
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_gem_context *ctx;
	काष्ठा पूर्णांकel_context *ce;
	अचिन्हित पूर्णांक prio;
	IGT_TIMEOUT(end);
	u64 total, max;
	पूर्णांक err;

	ctx = thपढ़ो->ctx;
	अगर (!ctx) अणु
		ctx = live_context_क्रम_engine(engine, thपढ़ो->file);
		अगर (IS_ERR(ctx))
			वापस PTR_ERR(ctx);

		prio = i915_pअक्रमom_u32_max_state(I915_PRIORITY_MAX, prng);
		ctx->sched.priority = prio;
	पूर्ण

	ce = i915_gem_context_get_engine(ctx, 0);
	GEM_BUG_ON(IS_ERR(ce));

	/*
	 * If we have a tiny shared address space, like क्रम the GGTT
	 * then we can't be too greedy.
	 */
	max = ce->vm->total;
	अगर (i915_is_ggtt(ce->vm) || thपढ़ो->ctx)
		max = भाग_u64(max, thपढ़ो->n_cpus);
	max >>= 4;

	total = PAGE_SIZE;
	करो अणु
		/* Aim to keep the runसमय under reasonable bounds! */
		स्थिर u32 max_phys_size = SZ_64K;
		u32 val = pअक्रमom_u32_state(prng);
		u32 phys_sz;
		u32 sz;
		u32 *vaddr;
		u32 i;

		total = min(total, max);
		sz = i915_pअक्रमom_u32_max_state(total, prng) + 1;
		phys_sz = sz % max_phys_size + 1;

		sz = round_up(sz, PAGE_SIZE);
		phys_sz = round_up(phys_sz, PAGE_SIZE);
		phys_sz = min(phys_sz, sz);

		pr_debug("%s with phys_sz= %x, sz=%x, val=%x\n", __func__,
			 phys_sz, sz, val);

		obj = huge_gem_object(engine->i915, phys_sz, sz);
		अगर (IS_ERR(obj)) अणु
			err = PTR_ERR(obj);
			जाओ err_flush;
		पूर्ण

		vaddr = i915_gem_object_pin_map_unlocked(obj, I915_MAP_WB);
		अगर (IS_ERR(vaddr)) अणु
			err = PTR_ERR(vaddr);
			जाओ err_put;
		पूर्ण

		/*
		 * Make sure the potentially async clflush करोes its job, अगर
		 * required.
		 */
		स_रखो32(vaddr, val ^ 0xdeadbeaf,
			 huge_gem_object_phys_size(obj) / माप(u32));

		अगर (!(obj->cache_coherent & I915_BO_CACHE_COHERENT_FOR_WRITE))
			obj->cache_dirty = true;

		err = i915_gem_object_fill_blt(obj, ce, val);
		अगर (err)
			जाओ err_unpin;

		err = i915_gem_object_रुको(obj, 0, MAX_SCHEDULE_TIMEOUT);
		अगर (err)
			जाओ err_unpin;

		क्रम (i = 0; i < huge_gem_object_phys_size(obj) / माप(u32); i += 17) अणु
			अगर (!(obj->cache_coherent & I915_BO_CACHE_COHERENT_FOR_READ))
				drm_clflush_virt_range(&vaddr[i], माप(vaddr[i]));

			अगर (vaddr[i] != val) अणु
				pr_err("vaddr[%u]=%x, expected=%x\n", i,
				       vaddr[i], val);
				err = -EINVAL;
				जाओ err_unpin;
			पूर्ण
		पूर्ण

		i915_gem_object_unpin_map(obj);
		i915_gem_object_put(obj);

		total <<= 1;
	पूर्ण जबतक (!समय_after(jअगरfies, end));

	जाओ err_flush;

err_unpin:
	i915_gem_object_unpin_map(obj);
err_put:
	i915_gem_object_put(obj);
err_flush:
	अगर (err == -ENOMEM)
		err = 0;

	पूर्णांकel_context_put(ce);
	वापस err;
पूर्ण

अटल पूर्णांक igt_copy_blt_thपढ़ो(व्योम *arg)
अणु
	काष्ठा igt_thपढ़ो_arg *thपढ़ो = arg;
	काष्ठा पूर्णांकel_engine_cs *engine = thपढ़ो->engine;
	काष्ठा rnd_state *prng = &thपढ़ो->prng;
	काष्ठा drm_i915_gem_object *src, *dst;
	काष्ठा i915_gem_context *ctx;
	काष्ठा पूर्णांकel_context *ce;
	अचिन्हित पूर्णांक prio;
	IGT_TIMEOUT(end);
	u64 total, max;
	पूर्णांक err;

	ctx = thपढ़ो->ctx;
	अगर (!ctx) अणु
		ctx = live_context_क्रम_engine(engine, thपढ़ो->file);
		अगर (IS_ERR(ctx))
			वापस PTR_ERR(ctx);

		prio = i915_pअक्रमom_u32_max_state(I915_PRIORITY_MAX, prng);
		ctx->sched.priority = prio;
	पूर्ण

	ce = i915_gem_context_get_engine(ctx, 0);
	GEM_BUG_ON(IS_ERR(ce));

	/*
	 * If we have a tiny shared address space, like क्रम the GGTT
	 * then we can't be too greedy.
	 */
	max = ce->vm->total;
	अगर (i915_is_ggtt(ce->vm) || thपढ़ो->ctx)
		max = भाग_u64(max, thपढ़ो->n_cpus);
	max >>= 4;

	total = PAGE_SIZE;
	करो अणु
		/* Aim to keep the runसमय under reasonable bounds! */
		स्थिर u32 max_phys_size = SZ_64K;
		u32 val = pअक्रमom_u32_state(prng);
		u32 phys_sz;
		u32 sz;
		u32 *vaddr;
		u32 i;

		total = min(total, max);
		sz = i915_pअक्रमom_u32_max_state(total, prng) + 1;
		phys_sz = sz % max_phys_size + 1;

		sz = round_up(sz, PAGE_SIZE);
		phys_sz = round_up(phys_sz, PAGE_SIZE);
		phys_sz = min(phys_sz, sz);

		pr_debug("%s with phys_sz= %x, sz=%x, val=%x\n", __func__,
			 phys_sz, sz, val);

		src = huge_gem_object(engine->i915, phys_sz, sz);
		अगर (IS_ERR(src)) अणु
			err = PTR_ERR(src);
			जाओ err_flush;
		पूर्ण

		vaddr = i915_gem_object_pin_map_unlocked(src, I915_MAP_WB);
		अगर (IS_ERR(vaddr)) अणु
			err = PTR_ERR(vaddr);
			जाओ err_put_src;
		पूर्ण

		स_रखो32(vaddr, val,
			 huge_gem_object_phys_size(src) / माप(u32));

		i915_gem_object_unpin_map(src);

		अगर (!(src->cache_coherent & I915_BO_CACHE_COHERENT_FOR_READ))
			src->cache_dirty = true;

		dst = huge_gem_object(engine->i915, phys_sz, sz);
		अगर (IS_ERR(dst)) अणु
			err = PTR_ERR(dst);
			जाओ err_put_src;
		पूर्ण

		vaddr = i915_gem_object_pin_map_unlocked(dst, I915_MAP_WB);
		अगर (IS_ERR(vaddr)) अणु
			err = PTR_ERR(vaddr);
			जाओ err_put_dst;
		पूर्ण

		स_रखो32(vaddr, val ^ 0xdeadbeaf,
			 huge_gem_object_phys_size(dst) / माप(u32));

		अगर (!(dst->cache_coherent & I915_BO_CACHE_COHERENT_FOR_WRITE))
			dst->cache_dirty = true;

		err = i915_gem_object_copy_blt(src, dst, ce);
		अगर (err)
			जाओ err_unpin;

		err = i915_gem_object_रुको(dst, 0, MAX_SCHEDULE_TIMEOUT);
		अगर (err)
			जाओ err_unpin;

		क्रम (i = 0; i < huge_gem_object_phys_size(dst) / माप(u32); i += 17) अणु
			अगर (!(dst->cache_coherent & I915_BO_CACHE_COHERENT_FOR_READ))
				drm_clflush_virt_range(&vaddr[i], माप(vaddr[i]));

			अगर (vaddr[i] != val) अणु
				pr_err("vaddr[%u]=%x, expected=%x\n", i,
				       vaddr[i], val);
				err = -EINVAL;
				जाओ err_unpin;
			पूर्ण
		पूर्ण

		i915_gem_object_unpin_map(dst);

		i915_gem_object_put(src);
		i915_gem_object_put(dst);

		total <<= 1;
	पूर्ण जबतक (!समय_after(jअगरfies, end));

	जाओ err_flush;

err_unpin:
	i915_gem_object_unpin_map(dst);
err_put_dst:
	i915_gem_object_put(dst);
err_put_src:
	i915_gem_object_put(src);
err_flush:
	अगर (err == -ENOMEM)
		err = 0;

	पूर्णांकel_context_put(ce);
	वापस err;
पूर्ण

अटल पूर्णांक igt_thपढ़ोed_blt(काष्ठा पूर्णांकel_engine_cs *engine,
			    पूर्णांक (*blt_fn)(व्योम *arg),
			    अचिन्हित पूर्णांक flags)
#घोषणा SINGLE_CTX BIT(0)
अणु
	काष्ठा igt_thपढ़ो_arg *thपढ़ो;
	काष्ठा task_काष्ठा **tsk;
	अचिन्हित पूर्णांक n_cpus, i;
	I915_RND_STATE(prng);
	पूर्णांक err = 0;

	n_cpus = num_online_cpus() + 1;

	tsk = kसुस्मृति(n_cpus, माप(काष्ठा task_काष्ठा *), GFP_KERNEL);
	अगर (!tsk)
		वापस 0;

	thपढ़ो = kसुस्मृति(n_cpus, माप(काष्ठा igt_thपढ़ो_arg), GFP_KERNEL);
	अगर (!thपढ़ो)
		जाओ out_tsk;

	thपढ़ो[0].file = mock_file(engine->i915);
	अगर (IS_ERR(thपढ़ो[0].file)) अणु
		err = PTR_ERR(thपढ़ो[0].file);
		जाओ out_thपढ़ो;
	पूर्ण

	अगर (flags & SINGLE_CTX) अणु
		thपढ़ो[0].ctx = live_context_क्रम_engine(engine, thपढ़ो[0].file);
		अगर (IS_ERR(thपढ़ो[0].ctx)) अणु
			err = PTR_ERR(thपढ़ो[0].ctx);
			जाओ out_file;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < n_cpus; ++i) अणु
		thपढ़ो[i].engine = engine;
		thपढ़ो[i].file = thपढ़ो[0].file;
		thपढ़ो[i].ctx = thपढ़ो[0].ctx;
		thपढ़ो[i].n_cpus = n_cpus;
		thपढ़ो[i].prng =
			I915_RND_STATE_INITIALIZER(pअक्रमom_u32_state(&prng));

		tsk[i] = kthपढ़ो_run(blt_fn, &thपढ़ो[i], "igt/blt-%d", i);
		अगर (IS_ERR(tsk[i])) अणु
			err = PTR_ERR(tsk[i]);
			अवरोध;
		पूर्ण

		get_task_काष्ठा(tsk[i]);
	पूर्ण

	yield(); /* start all thपढ़ोs beक्रमe we kthपढ़ो_stop() */

	क्रम (i = 0; i < n_cpus; ++i) अणु
		पूर्णांक status;

		अगर (IS_ERR_OR_शून्य(tsk[i]))
			जारी;

		status = kthपढ़ो_stop(tsk[i]);
		अगर (status && !err)
			err = status;

		put_task_काष्ठा(tsk[i]);
	पूर्ण

out_file:
	fput(thपढ़ो[0].file);
out_thपढ़ो:
	kमुक्त(thपढ़ो);
out_tsk:
	kमुक्त(tsk);
	वापस err;
पूर्ण

अटल पूर्णांक test_copy_engines(काष्ठा drm_i915_निजी *i915,
			     पूर्णांक (*fn)(व्योम *arg),
			     अचिन्हित पूर्णांक flags)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	पूर्णांक ret;

	क्रम_each_uabi_class_engine(engine, I915_ENGINE_CLASS_COPY, i915) अणु
		ret = igt_thपढ़ोed_blt(engine, fn, flags);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक igt_fill_blt(व्योम *arg)
अणु
	वापस test_copy_engines(arg, igt_fill_blt_thपढ़ो, 0);
पूर्ण

अटल पूर्णांक igt_fill_blt_ctx0(व्योम *arg)
अणु
	वापस test_copy_engines(arg, igt_fill_blt_thपढ़ो, SINGLE_CTX);
पूर्ण

अटल पूर्णांक igt_copy_blt(व्योम *arg)
अणु
	वापस test_copy_engines(arg, igt_copy_blt_thपढ़ो, 0);
पूर्ण

अटल पूर्णांक igt_copy_blt_ctx0(व्योम *arg)
अणु
	वापस test_copy_engines(arg, igt_copy_blt_thपढ़ो, SINGLE_CTX);
पूर्ण

पूर्णांक i915_gem_object_blt_live_selftests(काष्ठा drm_i915_निजी *i915)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(igt_fill_blt),
		SUBTEST(igt_fill_blt_ctx0),
		SUBTEST(igt_copy_blt),
		SUBTEST(igt_copy_blt_ctx0),
	पूर्ण;

	अगर (पूर्णांकel_gt_is_wedged(&i915->gt))
		वापस 0;

	वापस i915_live_subtests(tests, i915);
पूर्ण

पूर्णांक i915_gem_object_blt_perf_selftests(काष्ठा drm_i915_निजी *i915)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(perf_fill_blt),
		SUBTEST(perf_copy_blt),
	पूर्ण;

	अगर (पूर्णांकel_gt_is_wedged(&i915->gt))
		वापस 0;

	वापस i915_live_subtests(tests, i915);
पूर्ण
