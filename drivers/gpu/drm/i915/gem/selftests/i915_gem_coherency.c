<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2017 Intel Corporation
 */

#समावेश <linux/prime_numbers.h>

#समावेश "gt/intel_engine_pm.h"
#समावेश "gt/intel_gpu_commands.h"
#समावेश "gt/intel_gt.h"
#समावेश "gt/intel_gt_pm.h"
#समावेश "gt/intel_ring.h"

#समावेश "i915_selftest.h"
#समावेश "selftests/i915_random.h"

काष्ठा context अणु
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा पूर्णांकel_engine_cs *engine;
पूर्ण;

अटल पूर्णांक cpu_set(काष्ठा context *ctx, अचिन्हित दीर्घ offset, u32 v)
अणु
	अचिन्हित पूर्णांक needs_clflush;
	काष्ठा page *page;
	व्योम *map;
	u32 *cpu;
	पूर्णांक err;

	i915_gem_object_lock(ctx->obj, शून्य);
	err = i915_gem_object_prepare_ग_लिखो(ctx->obj, &needs_clflush);
	अगर (err)
		जाओ out;

	page = i915_gem_object_get_page(ctx->obj, offset >> PAGE_SHIFT);
	map = kmap_atomic(page);
	cpu = map + offset_in_page(offset);

	अगर (needs_clflush & CLFLUSH_BEFORE)
		drm_clflush_virt_range(cpu, माप(*cpu));

	*cpu = v;

	अगर (needs_clflush & CLFLUSH_AFTER)
		drm_clflush_virt_range(cpu, माप(*cpu));

	kunmap_atomic(map);
	i915_gem_object_finish_access(ctx->obj);

out:
	i915_gem_object_unlock(ctx->obj);
	वापस err;
पूर्ण

अटल पूर्णांक cpu_get(काष्ठा context *ctx, अचिन्हित दीर्घ offset, u32 *v)
अणु
	अचिन्हित पूर्णांक needs_clflush;
	काष्ठा page *page;
	व्योम *map;
	u32 *cpu;
	पूर्णांक err;

	i915_gem_object_lock(ctx->obj, शून्य);
	err = i915_gem_object_prepare_पढ़ो(ctx->obj, &needs_clflush);
	अगर (err)
		जाओ out;

	page = i915_gem_object_get_page(ctx->obj, offset >> PAGE_SHIFT);
	map = kmap_atomic(page);
	cpu = map + offset_in_page(offset);

	अगर (needs_clflush & CLFLUSH_BEFORE)
		drm_clflush_virt_range(cpu, माप(*cpu));

	*v = *cpu;

	kunmap_atomic(map);
	i915_gem_object_finish_access(ctx->obj);

out:
	i915_gem_object_unlock(ctx->obj);
	वापस err;
पूर्ण

अटल पूर्णांक gtt_set(काष्ठा context *ctx, अचिन्हित दीर्घ offset, u32 v)
अणु
	काष्ठा i915_vma *vma;
	u32 __iomem *map;
	पूर्णांक err = 0;

	i915_gem_object_lock(ctx->obj, शून्य);
	err = i915_gem_object_set_to_gtt_करोमुख्य(ctx->obj, true);
	i915_gem_object_unlock(ctx->obj);
	अगर (err)
		वापस err;

	vma = i915_gem_object_ggtt_pin(ctx->obj, शून्य, 0, 0, PIN_MAPPABLE);
	अगर (IS_ERR(vma))
		वापस PTR_ERR(vma);

	पूर्णांकel_gt_pm_get(vma->vm->gt);

	map = i915_vma_pin_iomap(vma);
	i915_vma_unpin(vma);
	अगर (IS_ERR(map)) अणु
		err = PTR_ERR(map);
		जाओ out_rpm;
	पूर्ण

	ioग_लिखो32(v, &map[offset / माप(*map)]);
	i915_vma_unpin_iomap(vma);

out_rpm:
	पूर्णांकel_gt_pm_put(vma->vm->gt);
	वापस err;
पूर्ण

अटल पूर्णांक gtt_get(काष्ठा context *ctx, अचिन्हित दीर्घ offset, u32 *v)
अणु
	काष्ठा i915_vma *vma;
	u32 __iomem *map;
	पूर्णांक err = 0;

	i915_gem_object_lock(ctx->obj, शून्य);
	err = i915_gem_object_set_to_gtt_करोमुख्य(ctx->obj, false);
	i915_gem_object_unlock(ctx->obj);
	अगर (err)
		वापस err;

	vma = i915_gem_object_ggtt_pin(ctx->obj, शून्य, 0, 0, PIN_MAPPABLE);
	अगर (IS_ERR(vma))
		वापस PTR_ERR(vma);

	पूर्णांकel_gt_pm_get(vma->vm->gt);

	map = i915_vma_pin_iomap(vma);
	i915_vma_unpin(vma);
	अगर (IS_ERR(map)) अणु
		err = PTR_ERR(map);
		जाओ out_rpm;
	पूर्ण

	*v = ioपढ़ो32(&map[offset / माप(*map)]);
	i915_vma_unpin_iomap(vma);

out_rpm:
	पूर्णांकel_gt_pm_put(vma->vm->gt);
	वापस err;
पूर्ण

अटल पूर्णांक wc_set(काष्ठा context *ctx, अचिन्हित दीर्घ offset, u32 v)
अणु
	u32 *map;
	पूर्णांक err;

	i915_gem_object_lock(ctx->obj, शून्य);
	err = i915_gem_object_set_to_wc_करोमुख्य(ctx->obj, true);
	i915_gem_object_unlock(ctx->obj);
	अगर (err)
		वापस err;

	map = i915_gem_object_pin_map_unlocked(ctx->obj, I915_MAP_WC);
	अगर (IS_ERR(map))
		वापस PTR_ERR(map);

	map[offset / माप(*map)] = v;

	__i915_gem_object_flush_map(ctx->obj, offset, माप(*map));
	i915_gem_object_unpin_map(ctx->obj);

	वापस 0;
पूर्ण

अटल पूर्णांक wc_get(काष्ठा context *ctx, अचिन्हित दीर्घ offset, u32 *v)
अणु
	u32 *map;
	पूर्णांक err;

	i915_gem_object_lock(ctx->obj, शून्य);
	err = i915_gem_object_set_to_wc_करोमुख्य(ctx->obj, false);
	i915_gem_object_unlock(ctx->obj);
	अगर (err)
		वापस err;

	map = i915_gem_object_pin_map_unlocked(ctx->obj, I915_MAP_WC);
	अगर (IS_ERR(map))
		वापस PTR_ERR(map);

	*v = map[offset / माप(*map)];
	i915_gem_object_unpin_map(ctx->obj);

	वापस 0;
पूर्ण

अटल पूर्णांक gpu_set(काष्ठा context *ctx, अचिन्हित दीर्घ offset, u32 v)
अणु
	काष्ठा i915_request *rq;
	काष्ठा i915_vma *vma;
	u32 *cs;
	पूर्णांक err;

	vma = i915_gem_object_ggtt_pin(ctx->obj, शून्य, 0, 0, 0);
	अगर (IS_ERR(vma))
		वापस PTR_ERR(vma);

	i915_gem_object_lock(ctx->obj, शून्य);
	err = i915_gem_object_set_to_gtt_करोमुख्य(ctx->obj, true);
	अगर (err)
		जाओ out_unlock;

	rq = पूर्णांकel_engine_create_kernel_request(ctx->engine);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ out_unpin;
	पूर्ण

	cs = पूर्णांकel_ring_begin(rq, 4);
	अगर (IS_ERR(cs)) अणु
		err = PTR_ERR(cs);
		जाओ out_rq;
	पूर्ण

	अगर (INTEL_GEN(ctx->engine->i915) >= 8) अणु
		*cs++ = MI_STORE_DWORD_IMM_GEN4 | 1 << 22;
		*cs++ = lower_32_bits(i915_ggtt_offset(vma) + offset);
		*cs++ = upper_32_bits(i915_ggtt_offset(vma) + offset);
		*cs++ = v;
	पूर्ण अन्यथा अगर (INTEL_GEN(ctx->engine->i915) >= 4) अणु
		*cs++ = MI_STORE_DWORD_IMM_GEN4 | MI_USE_GGTT;
		*cs++ = 0;
		*cs++ = i915_ggtt_offset(vma) + offset;
		*cs++ = v;
	पूर्ण अन्यथा अणु
		*cs++ = MI_STORE_DWORD_IMM | MI_MEM_VIRTUAL;
		*cs++ = i915_ggtt_offset(vma) + offset;
		*cs++ = v;
		*cs++ = MI_NOOP;
	पूर्ण
	पूर्णांकel_ring_advance(rq, cs);

	err = i915_request_aरुको_object(rq, vma->obj, true);
	अगर (err == 0)
		err = i915_vma_move_to_active(vma, rq, EXEC_OBJECT_WRITE);

out_rq:
	i915_request_add(rq);
out_unpin:
	i915_vma_unpin(vma);
out_unlock:
	i915_gem_object_unlock(ctx->obj);

	वापस err;
पूर्ण

अटल bool always_valid(काष्ठा context *ctx)
अणु
	वापस true;
पूर्ण

अटल bool needs_fence_रेजिस्टरs(काष्ठा context *ctx)
अणु
	काष्ठा पूर्णांकel_gt *gt = ctx->engine->gt;

	अगर (पूर्णांकel_gt_is_wedged(gt))
		वापस false;

	वापस gt->ggtt->num_fences;
पूर्ण

अटल bool needs_mi_store_dword(काष्ठा context *ctx)
अणु
	अगर (पूर्णांकel_gt_is_wedged(ctx->engine->gt))
		वापस false;

	वापस पूर्णांकel_engine_can_store_dword(ctx->engine);
पूर्ण

अटल स्थिर काष्ठा igt_coherency_mode अणु
	स्थिर अक्षर *name;
	पूर्णांक (*set)(काष्ठा context *ctx, अचिन्हित दीर्घ offset, u32 v);
	पूर्णांक (*get)(काष्ठा context *ctx, अचिन्हित दीर्घ offset, u32 *v);
	bool (*valid)(काष्ठा context *ctx);
पूर्ण igt_coherency_mode[] = अणु
	अणु "cpu", cpu_set, cpu_get, always_valid पूर्ण,
	अणु "gtt", gtt_set, gtt_get, needs_fence_रेजिस्टरs पूर्ण,
	अणु "wc", wc_set, wc_get, always_valid पूर्ण,
	अणु "gpu", gpu_set, शून्य, needs_mi_store_dword पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा पूर्णांकel_engine_cs *
अक्रमom_engine(काष्ठा drm_i915_निजी *i915, काष्ठा rnd_state *prng)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	अचिन्हित पूर्णांक count;

	count = 0;
	क्रम_each_uabi_engine(engine, i915)
		count++;

	count = i915_pअक्रमom_u32_max_state(count, prng);
	क्रम_each_uabi_engine(engine, i915)
		अगर (count-- == 0)
			वापस engine;

	वापस शून्य;
पूर्ण

अटल पूर्णांक igt_gem_coherency(व्योम *arg)
अणु
	स्थिर अचिन्हित पूर्णांक ncachelines = PAGE_SIZE/64;
	काष्ठा drm_i915_निजी *i915 = arg;
	स्थिर काष्ठा igt_coherency_mode *पढ़ो, *ग_लिखो, *over;
	अचिन्हित दीर्घ count, n;
	u32 *offsets, *values;
	I915_RND_STATE(prng);
	काष्ठा context ctx;
	पूर्णांक err = 0;

	/*
	 * We repeatedly ग_लिखो, overग_लिखो and पढ़ो from a sequence of
	 * cachelines in order to try and detect incoherency (unflushed ग_लिखोs
	 * from either the CPU or GPU). Each setter/getter uses our cache
	 * करोमुख्य API which should prevent incoherency.
	 */

	offsets = kदो_स्मृति_array(ncachelines, 2*माप(u32), GFP_KERNEL);
	अगर (!offsets)
		वापस -ENOMEM;
	क्रम (count = 0; count < ncachelines; count++)
		offsets[count] = count * 64 + 4 * (count % 16);

	values = offsets + ncachelines;

	ctx.engine = अक्रमom_engine(i915, &prng);
	अगर (!ctx.engine) अणु
		err = -ENODEV;
		जाओ out_मुक्त;
	पूर्ण
	pr_info("%s: using %s\n", __func__, ctx.engine->name);
	पूर्णांकel_engine_pm_get(ctx.engine);

	क्रम (over = igt_coherency_mode; over->name; over++) अणु
		अगर (!over->set)
			जारी;

		अगर (!over->valid(&ctx))
			जारी;

		क्रम (ग_लिखो = igt_coherency_mode; ग_लिखो->name; ग_लिखो++) अणु
			अगर (!ग_लिखो->set)
				जारी;

			अगर (!ग_लिखो->valid(&ctx))
				जारी;

			क्रम (पढ़ो = igt_coherency_mode; पढ़ो->name; पढ़ो++) अणु
				अगर (!पढ़ो->get)
					जारी;

				अगर (!पढ़ो->valid(&ctx))
					जारी;

				क्रम_each_prime_number_from(count, 1, ncachelines) अणु
					ctx.obj = i915_gem_object_create_पूर्णांकernal(i915, PAGE_SIZE);
					अगर (IS_ERR(ctx.obj)) अणु
						err = PTR_ERR(ctx.obj);
						जाओ out_pm;
					पूर्ण

					i915_अक्रमom_reorder(offsets, ncachelines, &prng);
					क्रम (n = 0; n < count; n++)
						values[n] = pअक्रमom_u32_state(&prng);

					क्रम (n = 0; n < count; n++) अणु
						err = over->set(&ctx, offsets[n], ~values[n]);
						अगर (err) अणु
							pr_err("Failed to set stale value[%ld/%ld] in object using %s, err=%d\n",
							       n, count, over->name, err);
							जाओ put_object;
						पूर्ण
					पूर्ण

					क्रम (n = 0; n < count; n++) अणु
						err = ग_लिखो->set(&ctx, offsets[n], values[n]);
						अगर (err) अणु
							pr_err("Failed to set value[%ld/%ld] in object using %s, err=%d\n",
							       n, count, ग_लिखो->name, err);
							जाओ put_object;
						पूर्ण
					पूर्ण

					क्रम (n = 0; n < count; n++) अणु
						u32 found;

						err = पढ़ो->get(&ctx, offsets[n], &found);
						अगर (err) अणु
							pr_err("Failed to get value[%ld/%ld] in object using %s, err=%d\n",
							       n, count, पढ़ो->name, err);
							जाओ put_object;
						पूर्ण

						अगर (found != values[n]) अणु
							pr_err("Value[%ld/%ld] mismatch, (overwrite with %s) wrote [%s] %x read [%s] %x (inverse %x), at offset %x\n",
							       n, count, over->name,
							       ग_लिखो->name, values[n],
							       पढ़ो->name, found,
							       ~values[n], offsets[n]);
							err = -EINVAL;
							जाओ put_object;
						पूर्ण
					पूर्ण

					i915_gem_object_put(ctx.obj);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
out_pm:
	पूर्णांकel_engine_pm_put(ctx.engine);
out_मुक्त:
	kमुक्त(offsets);
	वापस err;

put_object:
	i915_gem_object_put(ctx.obj);
	जाओ out_pm;
पूर्ण

पूर्णांक i915_gem_coherency_live_selftests(काष्ठा drm_i915_निजी *i915)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(igt_gem_coherency),
	पूर्ण;

	वापस i915_subtests(tests, i915);
पूर्ण
