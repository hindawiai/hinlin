<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2016 Intel Corporation
 */

#समावेश <linux/prime_numbers.h>

#समावेश "gt/intel_engine_pm.h"
#समावेश "gt/intel_gpu_commands.h"
#समावेश "gt/intel_gt.h"
#समावेश "gt/intel_gt_pm.h"
#समावेश "gem/i915_gem_region.h"
#समावेश "huge_gem_object.h"
#समावेश "i915_selftest.h"
#समावेश "selftests/i915_random.h"
#समावेश "selftests/igt_flush_test.h"
#समावेश "selftests/igt_mmap.h"

काष्ठा tile अणु
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक height;
	अचिन्हित पूर्णांक stride;
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक tiling;
	अचिन्हित पूर्णांक swizzle;
पूर्ण;

अटल u64 swizzle_bit(अचिन्हित पूर्णांक bit, u64 offset)
अणु
	वापस (offset & BIT_ULL(bit)) >> (bit - 6);
पूर्ण

अटल u64 tiled_offset(स्थिर काष्ठा tile *tile, u64 v)
अणु
	u64 x, y;

	अगर (tile->tiling == I915_TILING_NONE)
		वापस v;

	y = भाग64_u64_rem(v, tile->stride, &x);
	v = भाग64_u64_rem(y, tile->height, &y) * tile->stride * tile->height;

	अगर (tile->tiling == I915_TILING_X) अणु
		v += y * tile->width;
		v += भाग64_u64_rem(x, tile->width, &x) << tile->size;
		v += x;
	पूर्ण अन्यथा अगर (tile->width == 128) अणु
		स्थिर अचिन्हित पूर्णांक ytile_span = 16;
		स्थिर अचिन्हित पूर्णांक ytile_height = 512;

		v += y * ytile_span;
		v += भाग64_u64_rem(x, ytile_span, &x) * ytile_height;
		v += x;
	पूर्ण अन्यथा अणु
		स्थिर अचिन्हित पूर्णांक ytile_span = 32;
		स्थिर अचिन्हित पूर्णांक ytile_height = 256;

		v += y * ytile_span;
		v += भाग64_u64_rem(x, ytile_span, &x) * ytile_height;
		v += x;
	पूर्ण

	चयन (tile->swizzle) अणु
	हाल I915_BIT_6_SWIZZLE_9:
		v ^= swizzle_bit(9, v);
		अवरोध;
	हाल I915_BIT_6_SWIZZLE_9_10:
		v ^= swizzle_bit(9, v) ^ swizzle_bit(10, v);
		अवरोध;
	हाल I915_BIT_6_SWIZZLE_9_11:
		v ^= swizzle_bit(9, v) ^ swizzle_bit(11, v);
		अवरोध;
	हाल I915_BIT_6_SWIZZLE_9_10_11:
		v ^= swizzle_bit(9, v) ^ swizzle_bit(10, v) ^ swizzle_bit(11, v);
		अवरोध;
	पूर्ण

	वापस v;
पूर्ण

अटल पूर्णांक check_partial_mapping(काष्ठा drm_i915_gem_object *obj,
				 स्थिर काष्ठा tile *tile,
				 काष्ठा rnd_state *prng)
अणु
	स्थिर अचिन्हित दीर्घ npages = obj->base.size / PAGE_SIZE;
	काष्ठा i915_ggtt_view view;
	काष्ठा i915_vma *vma;
	अचिन्हित दीर्घ page;
	u32 __iomem *io;
	काष्ठा page *p;
	अचिन्हित पूर्णांक n;
	u64 offset;
	u32 *cpu;
	पूर्णांक err;

	err = i915_gem_object_set_tiling(obj, tile->tiling, tile->stride);
	अगर (err) अणु
		pr_err("Failed to set tiling mode=%u, stride=%u, err=%d\n",
		       tile->tiling, tile->stride, err);
		वापस err;
	पूर्ण

	GEM_BUG_ON(i915_gem_object_get_tiling(obj) != tile->tiling);
	GEM_BUG_ON(i915_gem_object_get_stride(obj) != tile->stride);

	i915_gem_object_lock(obj, शून्य);
	err = i915_gem_object_set_to_gtt_करोमुख्य(obj, true);
	i915_gem_object_unlock(obj);
	अगर (err) अणु
		pr_err("Failed to flush to GTT write domain; err=%d\n", err);
		वापस err;
	पूर्ण

	page = i915_pअक्रमom_u32_max_state(npages, prng);
	view = compute_partial_view(obj, page, MIN_CHUNK_PAGES);

	vma = i915_gem_object_ggtt_pin(obj, &view, 0, 0, PIN_MAPPABLE);
	अगर (IS_ERR(vma)) अणु
		pr_err("Failed to pin partial view: offset=%lu; err=%d\n",
		       page, (पूर्णांक)PTR_ERR(vma));
		वापस PTR_ERR(vma);
	पूर्ण

	n = page - view.partial.offset;
	GEM_BUG_ON(n >= view.partial.size);

	io = i915_vma_pin_iomap(vma);
	i915_vma_unpin(vma);
	अगर (IS_ERR(io)) अणु
		pr_err("Failed to iomap partial view: offset=%lu; err=%d\n",
		       page, (पूर्णांक)PTR_ERR(io));
		err = PTR_ERR(io);
		जाओ out;
	पूर्ण

	ioग_लिखो32(page, io + n * PAGE_SIZE / माप(*io));
	i915_vma_unpin_iomap(vma);

	offset = tiled_offset(tile, page << PAGE_SHIFT);
	अगर (offset >= obj->base.size)
		जाओ out;

	पूर्णांकel_gt_flush_ggtt_ग_लिखोs(&to_i915(obj->base.dev)->gt);

	p = i915_gem_object_get_page(obj, offset >> PAGE_SHIFT);
	cpu = kmap(p) + offset_in_page(offset);
	drm_clflush_virt_range(cpu, माप(*cpu));
	अगर (*cpu != (u32)page) अणु
		pr_err("Partial view for %lu [%u] (offset=%llu, size=%u [%llu, row size %u], fence=%d, tiling=%d, stride=%d) misalignment, expected write to page (%llu + %u [0x%llx]) of 0x%x, found 0x%x\n",
		       page, n,
		       view.partial.offset,
		       view.partial.size,
		       vma->size >> PAGE_SHIFT,
		       tile->tiling ? tile_row_pages(obj) : 0,
		       vma->fence ? vma->fence->id : -1, tile->tiling, tile->stride,
		       offset >> PAGE_SHIFT,
		       (अचिन्हित पूर्णांक)offset_in_page(offset),
		       offset,
		       (u32)page, *cpu);
		err = -EINVAL;
	पूर्ण
	*cpu = 0;
	drm_clflush_virt_range(cpu, माप(*cpu));
	kunmap(p);

out:
	__i915_vma_put(vma);
	वापस err;
पूर्ण

अटल पूर्णांक check_partial_mappings(काष्ठा drm_i915_gem_object *obj,
				  स्थिर काष्ठा tile *tile,
				  अचिन्हित दीर्घ end_समय)
अणु
	स्थिर अचिन्हित पूर्णांक nreal = obj->scratch / PAGE_SIZE;
	स्थिर अचिन्हित दीर्घ npages = obj->base.size / PAGE_SIZE;
	काष्ठा i915_vma *vma;
	अचिन्हित दीर्घ page;
	पूर्णांक err;

	err = i915_gem_object_set_tiling(obj, tile->tiling, tile->stride);
	अगर (err) अणु
		pr_err("Failed to set tiling mode=%u, stride=%u, err=%d\n",
		       tile->tiling, tile->stride, err);
		वापस err;
	पूर्ण

	GEM_BUG_ON(i915_gem_object_get_tiling(obj) != tile->tiling);
	GEM_BUG_ON(i915_gem_object_get_stride(obj) != tile->stride);

	i915_gem_object_lock(obj, शून्य);
	err = i915_gem_object_set_to_gtt_करोमुख्य(obj, true);
	i915_gem_object_unlock(obj);
	अगर (err) अणु
		pr_err("Failed to flush to GTT write domain; err=%d\n", err);
		वापस err;
	पूर्ण

	क्रम_each_prime_number_from(page, 1, npages) अणु
		काष्ठा i915_ggtt_view view =
			compute_partial_view(obj, page, MIN_CHUNK_PAGES);
		u32 __iomem *io;
		काष्ठा page *p;
		अचिन्हित पूर्णांक n;
		u64 offset;
		u32 *cpu;

		GEM_BUG_ON(view.partial.size > nreal);
		cond_resched();

		vma = i915_gem_object_ggtt_pin(obj, &view, 0, 0, PIN_MAPPABLE);
		अगर (IS_ERR(vma)) अणु
			pr_err("Failed to pin partial view: offset=%lu; err=%d\n",
			       page, (पूर्णांक)PTR_ERR(vma));
			वापस PTR_ERR(vma);
		पूर्ण

		n = page - view.partial.offset;
		GEM_BUG_ON(n >= view.partial.size);

		io = i915_vma_pin_iomap(vma);
		i915_vma_unpin(vma);
		अगर (IS_ERR(io)) अणु
			pr_err("Failed to iomap partial view: offset=%lu; err=%d\n",
			       page, (पूर्णांक)PTR_ERR(io));
			वापस PTR_ERR(io);
		पूर्ण

		ioग_लिखो32(page, io + n * PAGE_SIZE / माप(*io));
		i915_vma_unpin_iomap(vma);

		offset = tiled_offset(tile, page << PAGE_SHIFT);
		अगर (offset >= obj->base.size)
			जारी;

		पूर्णांकel_gt_flush_ggtt_ग_लिखोs(&to_i915(obj->base.dev)->gt);

		p = i915_gem_object_get_page(obj, offset >> PAGE_SHIFT);
		cpu = kmap(p) + offset_in_page(offset);
		drm_clflush_virt_range(cpu, माप(*cpu));
		अगर (*cpu != (u32)page) अणु
			pr_err("Partial view for %lu [%u] (offset=%llu, size=%u [%llu, row size %u], fence=%d, tiling=%d, stride=%d) misalignment, expected write to page (%llu + %u [0x%llx]) of 0x%x, found 0x%x\n",
			       page, n,
			       view.partial.offset,
			       view.partial.size,
			       vma->size >> PAGE_SHIFT,
			       tile->tiling ? tile_row_pages(obj) : 0,
			       vma->fence ? vma->fence->id : -1, tile->tiling, tile->stride,
			       offset >> PAGE_SHIFT,
			       (अचिन्हित पूर्णांक)offset_in_page(offset),
			       offset,
			       (u32)page, *cpu);
			err = -EINVAL;
		पूर्ण
		*cpu = 0;
		drm_clflush_virt_range(cpu, माप(*cpu));
		kunmap(p);
		अगर (err)
			वापस err;

		__i915_vma_put(vma);

		अगर (igt_समयout(end_समय,
				"%s: timed out after tiling=%d stride=%d\n",
				__func__, tile->tiling, tile->stride))
			वापस -EINTR;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक
setup_tile_size(काष्ठा tile *tile, काष्ठा drm_i915_निजी *i915)
अणु
	अगर (INTEL_GEN(i915) <= 2) अणु
		tile->height = 16;
		tile->width = 128;
		tile->size = 11;
	पूर्ण अन्यथा अगर (tile->tiling == I915_TILING_Y &&
		   HAS_128_BYTE_Y_TILING(i915)) अणु
		tile->height = 32;
		tile->width = 128;
		tile->size = 12;
	पूर्ण अन्यथा अणु
		tile->height = 8;
		tile->width = 512;
		tile->size = 12;
	पूर्ण

	अगर (INTEL_GEN(i915) < 4)
		वापस 8192 / tile->width;
	अन्यथा अगर (INTEL_GEN(i915) < 7)
		वापस 128 * I965_FENCE_MAX_PITCH_VAL / tile->width;
	अन्यथा
		वापस 128 * GEN7_FENCE_MAX_PITCH_VAL / tile->width;
पूर्ण

अटल पूर्णांक igt_partial_tiling(व्योम *arg)
अणु
	स्थिर अचिन्हित पूर्णांक nreal = 1 << 12; /* largest tile row x2 */
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा drm_i915_gem_object *obj;
	पूर्णांकel_wakeref_t wakeref;
	पूर्णांक tiling;
	पूर्णांक err;

	अगर (!i915_ggtt_has_aperture(&i915->ggtt))
		वापस 0;

	/* We want to check the page mapping and fencing of a large object
	 * mmapped through the GTT. The object we create is larger than can
	 * possibly be mmaped as a whole, and so we must use partial GGTT vma.
	 * We then check that a ग_लिखो through each partial GGTT vma ends up
	 * in the right set of pages within the object, and with the expected
	 * tiling, which we verअगरy by manual swizzling.
	 */

	obj = huge_gem_object(i915,
			      nreal << PAGE_SHIFT,
			      (1 + next_prime_number(i915->ggtt.vm.total >> PAGE_SHIFT)) << PAGE_SHIFT);
	अगर (IS_ERR(obj))
		वापस PTR_ERR(obj);

	err = i915_gem_object_pin_pages_unlocked(obj);
	अगर (err) अणु
		pr_err("Failed to allocate %u pages (%lu total), err=%d\n",
		       nreal, obj->base.size / PAGE_SIZE, err);
		जाओ out;
	पूर्ण

	wakeref = पूर्णांकel_runसमय_pm_get(&i915->runसमय_pm);

	अगर (1) अणु
		IGT_TIMEOUT(end);
		काष्ठा tile tile;

		tile.height = 1;
		tile.width = 1;
		tile.size = 0;
		tile.stride = 0;
		tile.swizzle = I915_BIT_6_SWIZZLE_NONE;
		tile.tiling = I915_TILING_NONE;

		err = check_partial_mappings(obj, &tile, end);
		अगर (err && err != -EINTR)
			जाओ out_unlock;
	पूर्ण

	क्रम (tiling = I915_TILING_X; tiling <= I915_TILING_Y; tiling++) अणु
		IGT_TIMEOUT(end);
		अचिन्हित पूर्णांक max_pitch;
		अचिन्हित पूर्णांक pitch;
		काष्ठा tile tile;

		अगर (i915->quirks & QUIRK_PIN_SWIZZLED_PAGES)
			/*
			 * The swizzling pattern is actually unknown as it
			 * varies based on physical address of each page.
			 * See i915_gem_detect_bit_6_swizzle().
			 */
			अवरोध;

		tile.tiling = tiling;
		चयन (tiling) अणु
		हाल I915_TILING_X:
			tile.swizzle = i915->ggtt.bit_6_swizzle_x;
			अवरोध;
		हाल I915_TILING_Y:
			tile.swizzle = i915->ggtt.bit_6_swizzle_y;
			अवरोध;
		पूर्ण

		GEM_BUG_ON(tile.swizzle == I915_BIT_6_SWIZZLE_UNKNOWN);
		अगर (tile.swizzle == I915_BIT_6_SWIZZLE_9_17 ||
		    tile.swizzle == I915_BIT_6_SWIZZLE_9_10_17)
			जारी;

		max_pitch = setup_tile_size(&tile, i915);

		क्रम (pitch = max_pitch; pitch; pitch >>= 1) अणु
			tile.stride = tile.width * pitch;
			err = check_partial_mappings(obj, &tile, end);
			अगर (err == -EINTR)
				जाओ next_tiling;
			अगर (err)
				जाओ out_unlock;

			अगर (pitch > 2 && INTEL_GEN(i915) >= 4) अणु
				tile.stride = tile.width * (pitch - 1);
				err = check_partial_mappings(obj, &tile, end);
				अगर (err == -EINTR)
					जाओ next_tiling;
				अगर (err)
					जाओ out_unlock;
			पूर्ण

			अगर (pitch < max_pitch && INTEL_GEN(i915) >= 4) अणु
				tile.stride = tile.width * (pitch + 1);
				err = check_partial_mappings(obj, &tile, end);
				अगर (err == -EINTR)
					जाओ next_tiling;
				अगर (err)
					जाओ out_unlock;
			पूर्ण
		पूर्ण

		अगर (INTEL_GEN(i915) >= 4) अणु
			क्रम_each_prime_number(pitch, max_pitch) अणु
				tile.stride = tile.width * pitch;
				err = check_partial_mappings(obj, &tile, end);
				अगर (err == -EINTR)
					जाओ next_tiling;
				अगर (err)
					जाओ out_unlock;
			पूर्ण
		पूर्ण

next_tiling: ;
	पूर्ण

out_unlock:
	पूर्णांकel_runसमय_pm_put(&i915->runसमय_pm, wakeref);
	i915_gem_object_unpin_pages(obj);
out:
	i915_gem_object_put(obj);
	वापस err;
पूर्ण

अटल पूर्णांक igt_smoke_tiling(व्योम *arg)
अणु
	स्थिर अचिन्हित पूर्णांक nreal = 1 << 12; /* largest tile row x2 */
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा drm_i915_gem_object *obj;
	पूर्णांकel_wakeref_t wakeref;
	I915_RND_STATE(prng);
	अचिन्हित दीर्घ count;
	IGT_TIMEOUT(end);
	पूर्णांक err;

	अगर (!i915_ggtt_has_aperture(&i915->ggtt))
		वापस 0;

	/*
	 * igt_partial_tiling() करोes an exhastive check of partial tiling
	 * chunking, but will unकरोubtably run out of समय. Here, we करो a
	 * अक्रमomised search and hope over many runs of 1s with dअगरferent
	 * seeds we will करो a thorough check.
	 *
	 * Remember to look at the st_seed अगर we see a flip-flop in BAT!
	 */

	अगर (i915->quirks & QUIRK_PIN_SWIZZLED_PAGES)
		वापस 0;

	obj = huge_gem_object(i915,
			      nreal << PAGE_SHIFT,
			      (1 + next_prime_number(i915->ggtt.vm.total >> PAGE_SHIFT)) << PAGE_SHIFT);
	अगर (IS_ERR(obj))
		वापस PTR_ERR(obj);

	err = i915_gem_object_pin_pages_unlocked(obj);
	अगर (err) अणु
		pr_err("Failed to allocate %u pages (%lu total), err=%d\n",
		       nreal, obj->base.size / PAGE_SIZE, err);
		जाओ out;
	पूर्ण

	wakeref = पूर्णांकel_runसमय_pm_get(&i915->runसमय_pm);

	count = 0;
	करो अणु
		काष्ठा tile tile;

		tile.tiling =
			i915_pअक्रमom_u32_max_state(I915_TILING_Y + 1, &prng);
		चयन (tile.tiling) अणु
		हाल I915_TILING_NONE:
			tile.height = 1;
			tile.width = 1;
			tile.size = 0;
			tile.stride = 0;
			tile.swizzle = I915_BIT_6_SWIZZLE_NONE;
			अवरोध;

		हाल I915_TILING_X:
			tile.swizzle = i915->ggtt.bit_6_swizzle_x;
			अवरोध;
		हाल I915_TILING_Y:
			tile.swizzle = i915->ggtt.bit_6_swizzle_y;
			अवरोध;
		पूर्ण

		अगर (tile.swizzle == I915_BIT_6_SWIZZLE_9_17 ||
		    tile.swizzle == I915_BIT_6_SWIZZLE_9_10_17)
			जारी;

		अगर (tile.tiling != I915_TILING_NONE) अणु
			अचिन्हित पूर्णांक max_pitch = setup_tile_size(&tile, i915);

			tile.stride =
				i915_pअक्रमom_u32_max_state(max_pitch, &prng);
			tile.stride = (1 + tile.stride) * tile.width;
			अगर (INTEL_GEN(i915) < 4)
				tile.stride = roundकरोwn_घात_of_two(tile.stride);
		पूर्ण

		err = check_partial_mapping(obj, &tile, &prng);
		अगर (err)
			अवरोध;

		count++;
	पूर्ण जबतक (!__igt_समयout(end, शून्य));

	pr_info("%s: Completed %lu trials\n", __func__, count);

	पूर्णांकel_runसमय_pm_put(&i915->runसमय_pm, wakeref);
	i915_gem_object_unpin_pages(obj);
out:
	i915_gem_object_put(obj);
	वापस err;
पूर्ण

अटल पूर्णांक make_obj_busy(काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(obj->base.dev);
	काष्ठा पूर्णांकel_engine_cs *engine;

	क्रम_each_uabi_engine(engine, i915) अणु
		काष्ठा i915_request *rq;
		काष्ठा i915_vma *vma;
		काष्ठा i915_gem_ww_ctx ww;
		पूर्णांक err;

		vma = i915_vma_instance(obj, &engine->gt->ggtt->vm, शून्य);
		अगर (IS_ERR(vma))
			वापस PTR_ERR(vma);

		i915_gem_ww_ctx_init(&ww, false);
retry:
		err = i915_gem_object_lock(obj, &ww);
		अगर (!err)
			err = i915_vma_pin_ww(vma, &ww, 0, 0, PIN_USER);
		अगर (err)
			जाओ err;

		rq = पूर्णांकel_engine_create_kernel_request(engine);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			जाओ err_unpin;
		पूर्ण

		err = i915_request_aरुको_object(rq, vma->obj, true);
		अगर (err == 0)
			err = i915_vma_move_to_active(vma, rq,
						      EXEC_OBJECT_WRITE);

		i915_request_add(rq);
err_unpin:
		i915_vma_unpin(vma);
err:
		अगर (err == -EDEADLK) अणु
			err = i915_gem_ww_ctx_backoff(&ww);
			अगर (!err)
				जाओ retry;
		पूर्ण
		i915_gem_ww_ctx_fini(&ww);
		अगर (err)
			वापस err;
	पूर्ण

	i915_gem_object_put(obj); /* leave it only alive via its active ref */
	वापस 0;
पूर्ण

अटल bool निश्चित_mmap_offset(काष्ठा drm_i915_निजी *i915,
			       अचिन्हित दीर्घ size,
			       पूर्णांक expected)
अणु
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_mmap_offset *mmo;

	obj = i915_gem_object_create_पूर्णांकernal(i915, size);
	अगर (IS_ERR(obj))
		वापस false;

	mmo = mmap_offset_attach(obj, I915_MMAP_OFFSET_GTT, शून्य);
	i915_gem_object_put(obj);

	वापस PTR_ERR_OR_ZERO(mmo) == expected;
पूर्ण

अटल व्योम disable_retire_worker(काष्ठा drm_i915_निजी *i915)
अणु
	i915_gem_driver_unरेजिस्टर__shrinker(i915);
	पूर्णांकel_gt_pm_get(&i915->gt);
	cancel_delayed_work_sync(&i915->gt.requests.retire_work);
पूर्ण

अटल व्योम restore_retire_worker(काष्ठा drm_i915_निजी *i915)
अणु
	igt_flush_test(i915);
	पूर्णांकel_gt_pm_put(&i915->gt);
	i915_gem_driver_रेजिस्टर__shrinker(i915);
पूर्ण

अटल व्योम mmap_offset_lock(काष्ठा drm_i915_निजी *i915)
	__acquires(&i915->drm.vma_offset_manager->vm_lock)
अणु
	ग_लिखो_lock(&i915->drm.vma_offset_manager->vm_lock);
पूर्ण

अटल व्योम mmap_offset_unlock(काष्ठा drm_i915_निजी *i915)
	__releases(&i915->drm.vma_offset_manager->vm_lock)
अणु
	ग_लिखो_unlock(&i915->drm.vma_offset_manager->vm_lock);
पूर्ण

अटल पूर्णांक igt_mmap_offset_exhaustion(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा drm_mm *mm = &i915->drm.vma_offset_manager->vm_addr_space_mm;
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा drm_mm_node *hole, *next;
	काष्ठा i915_mmap_offset *mmo;
	पूर्णांक loop, err = 0;

	/* Disable background reaper */
	disable_retire_worker(i915);
	GEM_BUG_ON(!i915->gt.awake);
	पूर्णांकel_gt_retire_requests(&i915->gt);
	i915_gem_drain_मुक्तd_objects(i915);

	/* Trim the device mmap space to only a page */
	mmap_offset_lock(i915);
	loop = 1; /* PAGE_SIZE units */
	list_क्रम_each_entry_safe(hole, next, &mm->hole_stack, hole_stack) अणु
		काष्ठा drm_mm_node *resv;

		resv = kzalloc(माप(*resv), GFP_NOWAIT);
		अगर (!resv) अणु
			err = -ENOMEM;
			जाओ out_park;
		पूर्ण

		resv->start = drm_mm_hole_node_start(hole) + loop;
		resv->size = hole->hole_size - loop;
		resv->color = -1ul;
		loop = 0;

		अगर (!resv->size) अणु
			kमुक्त(resv);
			जारी;
		पूर्ण

		pr_debug("Reserving hole [%llx + %llx]\n",
			 resv->start, resv->size);

		err = drm_mm_reserve_node(mm, resv);
		अगर (err) अणु
			pr_err("Failed to trim VMA manager, err=%d\n", err);
			kमुक्त(resv);
			जाओ out_park;
		पूर्ण
	पूर्ण
	GEM_BUG_ON(!list_is_singular(&mm->hole_stack));
	mmap_offset_unlock(i915);

	/* Just fits! */
	अगर (!निश्चित_mmap_offset(i915, PAGE_SIZE, 0)) अणु
		pr_err("Unable to insert object into single page hole\n");
		err = -EINVAL;
		जाओ out;
	पूर्ण

	/* Too large */
	अगर (!निश्चित_mmap_offset(i915, 2 * PAGE_SIZE, -ENOSPC)) अणु
		pr_err("Unexpectedly succeeded in inserting too large object into single page hole\n");
		err = -EINVAL;
		जाओ out;
	पूर्ण

	/* Fill the hole, further allocation attempts should then fail */
	obj = i915_gem_object_create_पूर्णांकernal(i915, PAGE_SIZE);
	अगर (IS_ERR(obj)) अणु
		err = PTR_ERR(obj);
		जाओ out;
	पूर्ण

	mmo = mmap_offset_attach(obj, I915_MMAP_OFFSET_GTT, शून्य);
	अगर (IS_ERR(mmo)) अणु
		pr_err("Unable to insert object into reclaimed hole\n");
		err = PTR_ERR(mmo);
		जाओ err_obj;
	पूर्ण

	अगर (!निश्चित_mmap_offset(i915, PAGE_SIZE, -ENOSPC)) अणु
		pr_err("Unexpectedly succeeded in inserting object into no holes!\n");
		err = -EINVAL;
		जाओ err_obj;
	पूर्ण

	i915_gem_object_put(obj);

	/* Now fill with busy dead objects that we expect to reap */
	क्रम (loop = 0; loop < 3; loop++) अणु
		अगर (पूर्णांकel_gt_is_wedged(&i915->gt))
			अवरोध;

		obj = i915_gem_object_create_पूर्णांकernal(i915, PAGE_SIZE);
		अगर (IS_ERR(obj)) अणु
			err = PTR_ERR(obj);
			जाओ out;
		पूर्ण

		err = make_obj_busy(obj);
		अगर (err) अणु
			pr_err("[loop %d] Failed to busy the object\n", loop);
			जाओ err_obj;
		पूर्ण
	पूर्ण

out:
	mmap_offset_lock(i915);
out_park:
	drm_mm_क्रम_each_node_safe(hole, next, mm) अणु
		अगर (hole->color != -1ul)
			जारी;

		drm_mm_हटाओ_node(hole);
		kमुक्त(hole);
	पूर्ण
	mmap_offset_unlock(i915);
	restore_retire_worker(i915);
	वापस err;
err_obj:
	i915_gem_object_put(obj);
	जाओ out;
पूर्ण

अटल पूर्णांक gtt_set(काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा i915_vma *vma;
	व्योम __iomem *map;
	पूर्णांक err = 0;

	vma = i915_gem_object_ggtt_pin(obj, शून्य, 0, 0, PIN_MAPPABLE);
	अगर (IS_ERR(vma))
		वापस PTR_ERR(vma);

	पूर्णांकel_gt_pm_get(vma->vm->gt);
	map = i915_vma_pin_iomap(vma);
	i915_vma_unpin(vma);
	अगर (IS_ERR(map)) अणु
		err = PTR_ERR(map);
		जाओ out;
	पूर्ण

	स_रखो_io(map, POISON_INUSE, obj->base.size);
	i915_vma_unpin_iomap(vma);

out:
	पूर्णांकel_gt_pm_put(vma->vm->gt);
	वापस err;
पूर्ण

अटल पूर्णांक gtt_check(काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा i915_vma *vma;
	व्योम __iomem *map;
	पूर्णांक err = 0;

	vma = i915_gem_object_ggtt_pin(obj, शून्य, 0, 0, PIN_MAPPABLE);
	अगर (IS_ERR(vma))
		वापस PTR_ERR(vma);

	पूर्णांकel_gt_pm_get(vma->vm->gt);
	map = i915_vma_pin_iomap(vma);
	i915_vma_unpin(vma);
	अगर (IS_ERR(map)) अणु
		err = PTR_ERR(map);
		जाओ out;
	पूर्ण

	अगर (स_प्रथम_inv((व्योम __क्रमce *)map, POISON_FREE, obj->base.size)) अणु
		pr_err("%s: Write via mmap did not land in backing store (GTT)\n",
		       obj->mm.region->name);
		err = -EINVAL;
	पूर्ण
	i915_vma_unpin_iomap(vma);

out:
	पूर्णांकel_gt_pm_put(vma->vm->gt);
	वापस err;
पूर्ण

अटल पूर्णांक wc_set(काष्ठा drm_i915_gem_object *obj)
अणु
	व्योम *vaddr;

	vaddr = i915_gem_object_pin_map_unlocked(obj, I915_MAP_WC);
	अगर (IS_ERR(vaddr))
		वापस PTR_ERR(vaddr);

	स_रखो(vaddr, POISON_INUSE, obj->base.size);
	i915_gem_object_flush_map(obj);
	i915_gem_object_unpin_map(obj);

	वापस 0;
पूर्ण

अटल पूर्णांक wc_check(काष्ठा drm_i915_gem_object *obj)
अणु
	व्योम *vaddr;
	पूर्णांक err = 0;

	vaddr = i915_gem_object_pin_map_unlocked(obj, I915_MAP_WC);
	अगर (IS_ERR(vaddr))
		वापस PTR_ERR(vaddr);

	अगर (स_प्रथम_inv(vaddr, POISON_FREE, obj->base.size)) अणु
		pr_err("%s: Write via mmap did not land in backing store (WC)\n",
		       obj->mm.region->name);
		err = -EINVAL;
	पूर्ण
	i915_gem_object_unpin_map(obj);

	वापस err;
पूर्ण

अटल bool can_mmap(काष्ठा drm_i915_gem_object *obj, क्रमागत i915_mmap_type type)
अणु
	अगर (type == I915_MMAP_TYPE_GTT &&
	    !i915_ggtt_has_aperture(&to_i915(obj->base.dev)->ggtt))
		वापस false;

	अगर (type != I915_MMAP_TYPE_GTT &&
	    !i915_gem_object_has_काष्ठा_page(obj) &&
	    !i915_gem_object_type_has(obj, I915_GEM_OBJECT_HAS_IOMEM))
		वापस false;

	वापस true;
पूर्ण

#घोषणा expand32(x) (((x) << 0) | ((x) << 8) | ((x) << 16) | ((x) << 24))
अटल पूर्णांक __igt_mmap(काष्ठा drm_i915_निजी *i915,
		      काष्ठा drm_i915_gem_object *obj,
		      क्रमागत i915_mmap_type type)
अणु
	काष्ठा i915_mmap_offset *mmo;
	काष्ठा vm_area_काष्ठा *area;
	अचिन्हित दीर्घ addr;
	पूर्णांक err, i;

	अगर (!can_mmap(obj, type))
		वापस 0;

	err = wc_set(obj);
	अगर (err == -ENXIO)
		err = gtt_set(obj);
	अगर (err)
		वापस err;

	mmo = mmap_offset_attach(obj, type, शून्य);
	अगर (IS_ERR(mmo))
		वापस PTR_ERR(mmo);

	addr = igt_mmap_node(i915, &mmo->vma_node, 0, PROT_WRITE, MAP_SHARED);
	अगर (IS_ERR_VALUE(addr))
		वापस addr;

	pr_debug("igt_mmap(%s, %d) @ %lx\n", obj->mm.region->name, type, addr);

	area = find_vma(current->mm, addr);
	अगर (!area) अणु
		pr_err("%s: Did not create a vm_area_struct for the mmap\n",
		       obj->mm.region->name);
		err = -EINVAL;
		जाओ out_unmap;
	पूर्ण

	अगर (area->vm_निजी_data != mmo) अणु
		pr_err("%s: vm_area_struct did not point back to our mmap_offset object!\n",
		       obj->mm.region->name);
		err = -EINVAL;
		जाओ out_unmap;
	पूर्ण

	क्रम (i = 0; i < obj->base.size / माप(u32); i++) अणु
		u32 __user *ux = u64_to_user_ptr((u64)(addr + i * माप(*ux)));
		u32 x;

		अगर (get_user(x, ux)) अणु
			pr_err("%s: Unable to read from mmap, offset:%zd\n",
			       obj->mm.region->name, i * माप(x));
			err = -EFAULT;
			जाओ out_unmap;
		पूर्ण

		अगर (x != expand32(POISON_INUSE)) अणु
			pr_err("%s: Read incorrect value from mmap, offset:%zd, found:%x, expected:%x\n",
			       obj->mm.region->name,
			       i * माप(x), x, expand32(POISON_INUSE));
			err = -EINVAL;
			जाओ out_unmap;
		पूर्ण

		x = expand32(POISON_FREE);
		अगर (put_user(x, ux)) अणु
			pr_err("%s: Unable to write to mmap, offset:%zd\n",
			       obj->mm.region->name, i * माप(x));
			err = -EFAULT;
			जाओ out_unmap;
		पूर्ण
	पूर्ण

	अगर (type == I915_MMAP_TYPE_GTT)
		पूर्णांकel_gt_flush_ggtt_ग_लिखोs(&i915->gt);

	err = wc_check(obj);
	अगर (err == -ENXIO)
		err = gtt_check(obj);
out_unmap:
	vm_munmap(addr, obj->base.size);
	वापस err;
पूर्ण

अटल पूर्णांक igt_mmap(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा पूर्णांकel_memory_region *mr;
	क्रमागत पूर्णांकel_region_id id;

	क्रम_each_memory_region(mr, i915, id) अणु
		अचिन्हित दीर्घ sizes[] = अणु
			PAGE_SIZE,
			mr->min_page_size,
			SZ_4M,
		पूर्ण;
		पूर्णांक i;

		क्रम (i = 0; i < ARRAY_SIZE(sizes); i++) अणु
			काष्ठा drm_i915_gem_object *obj;
			पूर्णांक err;

			obj = i915_gem_object_create_region(mr, sizes[i], 0);
			अगर (obj == ERR_PTR(-ENODEV))
				जारी;

			अगर (IS_ERR(obj))
				वापस PTR_ERR(obj);

			err = __igt_mmap(i915, obj, I915_MMAP_TYPE_GTT);
			अगर (err == 0)
				err = __igt_mmap(i915, obj, I915_MMAP_TYPE_WC);

			i915_gem_object_put(obj);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *repr_mmap_type(क्रमागत i915_mmap_type type)
अणु
	चयन (type) अणु
	हाल I915_MMAP_TYPE_GTT: वापस "gtt";
	हाल I915_MMAP_TYPE_WB: वापस "wb";
	हाल I915_MMAP_TYPE_WC: वापस "wc";
	हाल I915_MMAP_TYPE_UC: वापस "uc";
	शेष: वापस "unknown";
	पूर्ण
पूर्ण

अटल bool can_access(स्थिर काष्ठा drm_i915_gem_object *obj)
अणु
	वापस i915_gem_object_has_काष्ठा_page(obj) ||
	       i915_gem_object_type_has(obj, I915_GEM_OBJECT_HAS_IOMEM);
पूर्ण

अटल पूर्णांक __igt_mmap_access(काष्ठा drm_i915_निजी *i915,
			     काष्ठा drm_i915_gem_object *obj,
			     क्रमागत i915_mmap_type type)
अणु
	काष्ठा i915_mmap_offset *mmo;
	अचिन्हित दीर्घ __user *ptr;
	अचिन्हित दीर्घ A, B;
	अचिन्हित दीर्घ x, y;
	अचिन्हित दीर्घ addr;
	पूर्णांक err;

	स_रखो(&A, 0xAA, माप(A));
	स_रखो(&B, 0xBB, माप(B));

	अगर (!can_mmap(obj, type) || !can_access(obj))
		वापस 0;

	mmo = mmap_offset_attach(obj, type, शून्य);
	अगर (IS_ERR(mmo))
		वापस PTR_ERR(mmo);

	addr = igt_mmap_node(i915, &mmo->vma_node, 0, PROT_WRITE, MAP_SHARED);
	अगर (IS_ERR_VALUE(addr))
		वापस addr;
	ptr = (अचिन्हित दीर्घ __user *)addr;

	err = __put_user(A, ptr);
	अगर (err) अणु
		pr_err("%s(%s): failed to write into user mmap\n",
		       obj->mm.region->name, repr_mmap_type(type));
		जाओ out_unmap;
	पूर्ण

	पूर्णांकel_gt_flush_ggtt_ग_लिखोs(&i915->gt);

	err = access_process_vm(current, addr, &x, माप(x), 0);
	अगर (err != माप(x)) अणु
		pr_err("%s(%s): access_process_vm() read failed\n",
		       obj->mm.region->name, repr_mmap_type(type));
		जाओ out_unmap;
	पूर्ण

	err = access_process_vm(current, addr, &B, माप(B), FOLL_WRITE);
	अगर (err != माप(B)) अणु
		pr_err("%s(%s): access_process_vm() write failed\n",
		       obj->mm.region->name, repr_mmap_type(type));
		जाओ out_unmap;
	पूर्ण

	पूर्णांकel_gt_flush_ggtt_ग_लिखोs(&i915->gt);

	err = __get_user(y, ptr);
	अगर (err) अणु
		pr_err("%s(%s): failed to read from user mmap\n",
		       obj->mm.region->name, repr_mmap_type(type));
		जाओ out_unmap;
	पूर्ण

	अगर (x != A || y != B) अणु
		pr_err("%s(%s): failed to read/write values, found (%lx, %lx)\n",
		       obj->mm.region->name, repr_mmap_type(type),
		       x, y);
		err = -EINVAL;
		जाओ out_unmap;
	पूर्ण

out_unmap:
	vm_munmap(addr, obj->base.size);
	वापस err;
पूर्ण

अटल पूर्णांक igt_mmap_access(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा पूर्णांकel_memory_region *mr;
	क्रमागत पूर्णांकel_region_id id;

	क्रम_each_memory_region(mr, i915, id) अणु
		काष्ठा drm_i915_gem_object *obj;
		पूर्णांक err;

		obj = i915_gem_object_create_region(mr, PAGE_SIZE, 0);
		अगर (obj == ERR_PTR(-ENODEV))
			जारी;

		अगर (IS_ERR(obj))
			वापस PTR_ERR(obj);

		err = __igt_mmap_access(i915, obj, I915_MMAP_TYPE_GTT);
		अगर (err == 0)
			err = __igt_mmap_access(i915, obj, I915_MMAP_TYPE_WB);
		अगर (err == 0)
			err = __igt_mmap_access(i915, obj, I915_MMAP_TYPE_WC);
		अगर (err == 0)
			err = __igt_mmap_access(i915, obj, I915_MMAP_TYPE_UC);

		i915_gem_object_put(obj);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __igt_mmap_gpu(काष्ठा drm_i915_निजी *i915,
			  काष्ठा drm_i915_gem_object *obj,
			  क्रमागत i915_mmap_type type)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा i915_mmap_offset *mmo;
	अचिन्हित दीर्घ addr;
	u32 __user *ux;
	u32 bbe;
	पूर्णांक err;

	/*
	 * Verअगरy that the mmap access पूर्णांकo the backing store aligns with
	 * that of the GPU, i.e. that mmap is indeed writing पूर्णांकo the same
	 * page as being पढ़ो by the GPU.
	 */

	अगर (!can_mmap(obj, type))
		वापस 0;

	err = wc_set(obj);
	अगर (err == -ENXIO)
		err = gtt_set(obj);
	अगर (err)
		वापस err;

	mmo = mmap_offset_attach(obj, type, शून्य);
	अगर (IS_ERR(mmo))
		वापस PTR_ERR(mmo);

	addr = igt_mmap_node(i915, &mmo->vma_node, 0, PROT_WRITE, MAP_SHARED);
	अगर (IS_ERR_VALUE(addr))
		वापस addr;

	ux = u64_to_user_ptr((u64)addr);
	bbe = MI_BATCH_BUFFER_END;
	अगर (put_user(bbe, ux)) अणु
		pr_err("%s: Unable to write to mmap\n", obj->mm.region->name);
		err = -EFAULT;
		जाओ out_unmap;
	पूर्ण

	अगर (type == I915_MMAP_TYPE_GTT)
		पूर्णांकel_gt_flush_ggtt_ग_लिखोs(&i915->gt);

	क्रम_each_uabi_engine(engine, i915) अणु
		काष्ठा i915_request *rq;
		काष्ठा i915_vma *vma;
		काष्ठा i915_gem_ww_ctx ww;

		vma = i915_vma_instance(obj, engine->kernel_context->vm, शून्य);
		अगर (IS_ERR(vma)) अणु
			err = PTR_ERR(vma);
			जाओ out_unmap;
		पूर्ण

		i915_gem_ww_ctx_init(&ww, false);
retry:
		err = i915_gem_object_lock(obj, &ww);
		अगर (!err)
			err = i915_vma_pin_ww(vma, &ww, 0, 0, PIN_USER);
		अगर (err)
			जाओ out_ww;

		rq = i915_request_create(engine->kernel_context);
		अगर (IS_ERR(rq)) अणु
			err = PTR_ERR(rq);
			जाओ out_unpin;
		पूर्ण

		err = i915_request_aरुको_object(rq, vma->obj, false);
		अगर (err == 0)
			err = i915_vma_move_to_active(vma, rq, 0);

		err = engine->emit_bb_start(rq, vma->node.start, 0, 0);
		i915_request_get(rq);
		i915_request_add(rq);

		अगर (i915_request_रुको(rq, 0, HZ / 5) < 0) अणु
			काष्ठा drm_prपूर्णांकer p =
				drm_info_prपूर्णांकer(engine->i915->drm.dev);

			pr_err("%s(%s, %s): Failed to execute batch\n",
			       __func__, engine->name, obj->mm.region->name);
			पूर्णांकel_engine_dump(engine, &p,
					  "%s\n", engine->name);

			पूर्णांकel_gt_set_wedged(engine->gt);
			err = -EIO;
		पूर्ण
		i915_request_put(rq);

out_unpin:
		i915_vma_unpin(vma);
out_ww:
		अगर (err == -EDEADLK) अणु
			err = i915_gem_ww_ctx_backoff(&ww);
			अगर (!err)
				जाओ retry;
		पूर्ण
		i915_gem_ww_ctx_fini(&ww);
		अगर (err)
			जाओ out_unmap;
	पूर्ण

out_unmap:
	vm_munmap(addr, obj->base.size);
	वापस err;
पूर्ण

अटल पूर्णांक igt_mmap_gpu(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा पूर्णांकel_memory_region *mr;
	क्रमागत पूर्णांकel_region_id id;

	क्रम_each_memory_region(mr, i915, id) अणु
		काष्ठा drm_i915_gem_object *obj;
		पूर्णांक err;

		obj = i915_gem_object_create_region(mr, PAGE_SIZE, 0);
		अगर (obj == ERR_PTR(-ENODEV))
			जारी;

		अगर (IS_ERR(obj))
			वापस PTR_ERR(obj);

		err = __igt_mmap_gpu(i915, obj, I915_MMAP_TYPE_GTT);
		अगर (err == 0)
			err = __igt_mmap_gpu(i915, obj, I915_MMAP_TYPE_WC);

		i915_gem_object_put(obj);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक check_present_pte(pte_t *pte, अचिन्हित दीर्घ addr, व्योम *data)
अणु
	अगर (!pte_present(*pte) || pte_none(*pte)) अणु
		pr_err("missing PTE:%lx\n",
		       (addr - (अचिन्हित दीर्घ)data) >> PAGE_SHIFT);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक check_असलent_pte(pte_t *pte, अचिन्हित दीर्घ addr, व्योम *data)
अणु
	अगर (pte_present(*pte) && !pte_none(*pte)) अणु
		pr_err("present PTE:%lx; expected to be revoked\n",
		       (addr - (अचिन्हित दीर्घ)data) >> PAGE_SHIFT);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक check_present(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len)
अणु
	वापस apply_to_page_range(current->mm, addr, len,
				   check_present_pte, (व्योम *)addr);
पूर्ण

अटल पूर्णांक check_असलent(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len)
अणु
	वापस apply_to_page_range(current->mm, addr, len,
				   check_असलent_pte, (व्योम *)addr);
पूर्ण

अटल पूर्णांक prefault_range(u64 start, u64 len)
अणु
	स्थिर अक्षर __user *addr, *end;
	अक्षर __maybe_unused c;
	पूर्णांक err;

	addr = u64_to_user_ptr(start);
	end = addr + len;

	क्रम (; addr < end; addr += PAGE_SIZE) अणु
		err = __get_user(c, addr);
		अगर (err)
			वापस err;
	पूर्ण

	वापस __get_user(c, end - 1);
पूर्ण

अटल पूर्णांक __igt_mmap_revoke(काष्ठा drm_i915_निजी *i915,
			     काष्ठा drm_i915_gem_object *obj,
			     क्रमागत i915_mmap_type type)
अणु
	काष्ठा i915_mmap_offset *mmo;
	अचिन्हित दीर्घ addr;
	पूर्णांक err;

	अगर (!can_mmap(obj, type))
		वापस 0;

	mmo = mmap_offset_attach(obj, type, शून्य);
	अगर (IS_ERR(mmo))
		वापस PTR_ERR(mmo);

	addr = igt_mmap_node(i915, &mmo->vma_node, 0, PROT_WRITE, MAP_SHARED);
	अगर (IS_ERR_VALUE(addr))
		वापस addr;

	err = prefault_range(addr, obj->base.size);
	अगर (err)
		जाओ out_unmap;

	err = check_present(addr, obj->base.size);
	अगर (err) अणु
		pr_err("%s: was not present\n", obj->mm.region->name);
		जाओ out_unmap;
	पूर्ण

	/*
	 * After unbinding the object from the GGTT, its address may be reused
	 * क्रम other objects. Ergo we have to revoke the previous mmap PTE
	 * access as it no दीर्घer poपूर्णांकs to the same object.
	 */
	err = i915_gem_object_unbind(obj, I915_GEM_OBJECT_UNBIND_ACTIVE);
	अगर (err) अणु
		pr_err("Failed to unbind object!\n");
		जाओ out_unmap;
	पूर्ण

	अगर (type != I915_MMAP_TYPE_GTT) अणु
		i915_gem_object_lock(obj, शून्य);
		__i915_gem_object_put_pages(obj);
		i915_gem_object_unlock(obj);
		अगर (i915_gem_object_has_pages(obj)) अणु
			pr_err("Failed to put-pages object!\n");
			err = -EINVAL;
			जाओ out_unmap;
		पूर्ण
	पूर्ण

	err = check_असलent(addr, obj->base.size);
	अगर (err) अणु
		pr_err("%s: was not absent\n", obj->mm.region->name);
		जाओ out_unmap;
	पूर्ण

out_unmap:
	vm_munmap(addr, obj->base.size);
	वापस err;
पूर्ण

अटल पूर्णांक igt_mmap_revoke(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा पूर्णांकel_memory_region *mr;
	क्रमागत पूर्णांकel_region_id id;

	क्रम_each_memory_region(mr, i915, id) अणु
		काष्ठा drm_i915_gem_object *obj;
		पूर्णांक err;

		obj = i915_gem_object_create_region(mr, PAGE_SIZE, 0);
		अगर (obj == ERR_PTR(-ENODEV))
			जारी;

		अगर (IS_ERR(obj))
			वापस PTR_ERR(obj);

		err = __igt_mmap_revoke(i915, obj, I915_MMAP_TYPE_GTT);
		अगर (err == 0)
			err = __igt_mmap_revoke(i915, obj, I915_MMAP_TYPE_WC);

		i915_gem_object_put(obj);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक i915_gem_mman_live_selftests(काष्ठा drm_i915_निजी *i915)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(igt_partial_tiling),
		SUBTEST(igt_smoke_tiling),
		SUBTEST(igt_mmap_offset_exhaustion),
		SUBTEST(igt_mmap),
		SUBTEST(igt_mmap_access),
		SUBTEST(igt_mmap_revoke),
		SUBTEST(igt_mmap_gpu),
	पूर्ण;

	वापस i915_subtests(tests, i915);
पूर्ण
