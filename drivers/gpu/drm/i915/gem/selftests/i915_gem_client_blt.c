<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश "i915_selftest.h"

#समावेश "gt/intel_engine_user.h"
#समावेश "gt/intel_gt.h"
#समावेश "gt/intel_gpu_commands.h"
#समावेश "gem/i915_gem_lmem.h"

#समावेश "selftests/igt_flush_test.h"
#समावेश "selftests/mock_drm.h"
#समावेश "selftests/i915_random.h"
#समावेश "huge_gem_object.h"
#समावेश "mock_context.h"

अटल पूर्णांक __igt_client_fill(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_context *ce = engine->kernel_context;
	काष्ठा drm_i915_gem_object *obj;
	I915_RND_STATE(prng);
	IGT_TIMEOUT(end);
	u32 *vaddr;
	पूर्णांक err = 0;

	पूर्णांकel_engine_pm_get(engine);
	करो अणु
		स्थिर u32 max_block_size = S16_MAX * PAGE_SIZE;
		u32 sz = min_t(u64, ce->vm->total >> 4, pअक्रमom_u32_state(&prng));
		u32 phys_sz = sz % (max_block_size + 1);
		u32 val = pअक्रमom_u32_state(&prng);
		u32 i;

		sz = round_up(sz, PAGE_SIZE);
		phys_sz = round_up(phys_sz, PAGE_SIZE);

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
		 * XXX: The goal is move this to get_pages, so try to dirty the
		 * CPU cache first to check that we करो the required clflush
		 * beक्रमe scheduling the blt क्रम !llc platक्रमms. This matches
		 * some version of reality where at get_pages the pages
		 * themselves may not yet be coherent with the GPU(swap-in). If
		 * we are missing the flush then we should see the stale cache
		 * values after we करो the set_to_cpu_करोमुख्य and pick it up as a
		 * test failure.
		 */
		स_रखो32(vaddr, val ^ 0xdeadbeaf,
			 huge_gem_object_phys_size(obj) / माप(u32));

		अगर (!(obj->cache_coherent & I915_BO_CACHE_COHERENT_FOR_WRITE))
			obj->cache_dirty = true;

		err = i915_gem_schedule_fill_pages_blt(obj, ce, obj->mm.pages,
						       &obj->mm.page_sizes,
						       val);
		अगर (err)
			जाओ err_unpin;

		i915_gem_object_lock(obj, शून्य);
		err = i915_gem_object_set_to_cpu_करोमुख्य(obj, false);
		i915_gem_object_unlock(obj);
		अगर (err)
			जाओ err_unpin;

		क्रम (i = 0; i < huge_gem_object_phys_size(obj) / माप(u32); ++i) अणु
			अगर (vaddr[i] != val) अणु
				pr_err("vaddr[%u]=%x, expected=%x\n", i,
				       vaddr[i], val);
				err = -EINVAL;
				जाओ err_unpin;
			पूर्ण
		पूर्ण

		i915_gem_object_unpin_map(obj);
		i915_gem_object_put(obj);
	पूर्ण जबतक (!समय_after(jअगरfies, end));

	जाओ err_flush;

err_unpin:
	i915_gem_object_unpin_map(obj);
err_put:
	i915_gem_object_put(obj);
err_flush:
	अगर (err == -ENOMEM)
		err = 0;
	पूर्णांकel_engine_pm_put(engine);

	वापस err;
पूर्ण

अटल पूर्णांक igt_client_fill(व्योम *arg)
अणु
	पूर्णांक inst = 0;

	करो अणु
		काष्ठा पूर्णांकel_engine_cs *engine;
		पूर्णांक err;

		engine = पूर्णांकel_engine_lookup_user(arg,
						  I915_ENGINE_CLASS_COPY,
						  inst++);
		अगर (!engine)
			वापस 0;

		err = __igt_client_fill(engine);
		अगर (err == -ENOMEM)
			err = 0;
		अगर (err)
			वापस err;
	पूर्ण जबतक (1);
पूर्ण

#घोषणा WIDTH 512
#घोषणा HEIGHT 32

काष्ठा blit_buffer अणु
	काष्ठा i915_vma *vma;
	u32 start_val;
	u32 tiling;
पूर्ण;

काष्ठा tiled_blits अणु
	काष्ठा पूर्णांकel_context *ce;
	काष्ठा blit_buffer buffers[3];
	काष्ठा blit_buffer scratch;
	काष्ठा i915_vma *batch;
	u64 hole;
	u32 width;
	u32 height;
पूर्ण;

अटल पूर्णांक prepare_blit(स्थिर काष्ठा tiled_blits *t,
			काष्ठा blit_buffer *dst,
			काष्ठा blit_buffer *src,
			काष्ठा drm_i915_gem_object *batch)
अणु
	स्थिर पूर्णांक gen = INTEL_GEN(to_i915(batch->base.dev));
	bool use_64b_reloc = gen >= 8;
	u32 src_pitch, dst_pitch;
	u32 cmd, *cs;

	cs = i915_gem_object_pin_map_unlocked(batch, I915_MAP_WC);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	*cs++ = MI_LOAD_REGISTER_IMM(1);
	*cs++ = i915_mmio_reg_offset(BCS_SWCTRL);
	cmd = (BCS_SRC_Y | BCS_DST_Y) << 16;
	अगर (src->tiling == I915_TILING_Y)
		cmd |= BCS_SRC_Y;
	अगर (dst->tiling == I915_TILING_Y)
		cmd |= BCS_DST_Y;
	*cs++ = cmd;

	cmd = MI_FLUSH_DW;
	अगर (gen >= 8)
		cmd++;
	*cs++ = cmd;
	*cs++ = 0;
	*cs++ = 0;
	*cs++ = 0;

	cmd = XY_SRC_COPY_BLT_CMD | BLT_WRITE_RGBA | (8 - 2);
	अगर (gen >= 8)
		cmd += 2;

	src_pitch = t->width * 4;
	अगर (src->tiling) अणु
		cmd |= XY_SRC_COPY_BLT_SRC_TILED;
		src_pitch /= 4;
	पूर्ण

	dst_pitch = t->width * 4;
	अगर (dst->tiling) अणु
		cmd |= XY_SRC_COPY_BLT_DST_TILED;
		dst_pitch /= 4;
	पूर्ण

	*cs++ = cmd;
	*cs++ = BLT_DEPTH_32 | BLT_ROP_SRC_COPY | dst_pitch;
	*cs++ = 0;
	*cs++ = t->height << 16 | t->width;
	*cs++ = lower_32_bits(dst->vma->node.start);
	अगर (use_64b_reloc)
		*cs++ = upper_32_bits(dst->vma->node.start);
	*cs++ = 0;
	*cs++ = src_pitch;
	*cs++ = lower_32_bits(src->vma->node.start);
	अगर (use_64b_reloc)
		*cs++ = upper_32_bits(src->vma->node.start);

	*cs++ = MI_BATCH_BUFFER_END;

	i915_gem_object_flush_map(batch);
	i915_gem_object_unpin_map(batch);

	वापस 0;
पूर्ण

अटल व्योम tiled_blits_destroy_buffers(काष्ठा tiled_blits *t)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(t->buffers); i++)
		i915_vma_put(t->buffers[i].vma);

	i915_vma_put(t->scratch.vma);
	i915_vma_put(t->batch);
पूर्ण

अटल काष्ठा i915_vma *
__create_vma(काष्ठा tiled_blits *t, माप_प्रकार size, bool lmem)
अणु
	काष्ठा drm_i915_निजी *i915 = t->ce->vm->i915;
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_vma *vma;

	अगर (lmem)
		obj = i915_gem_object_create_lmem(i915, size, 0);
	अन्यथा
		obj = i915_gem_object_create_shmem(i915, size);
	अगर (IS_ERR(obj))
		वापस ERR_CAST(obj);

	vma = i915_vma_instance(obj, t->ce->vm, शून्य);
	अगर (IS_ERR(vma))
		i915_gem_object_put(obj);

	वापस vma;
पूर्ण

अटल काष्ठा i915_vma *create_vma(काष्ठा tiled_blits *t, bool lmem)
अणु
	वापस __create_vma(t, PAGE_ALIGN(t->width * t->height * 4), lmem);
पूर्ण

अटल पूर्णांक tiled_blits_create_buffers(काष्ठा tiled_blits *t,
				      पूर्णांक width, पूर्णांक height,
				      काष्ठा rnd_state *prng)
अणु
	काष्ठा drm_i915_निजी *i915 = t->ce->engine->i915;
	पूर्णांक i;

	t->width = width;
	t->height = height;

	t->batch = __create_vma(t, PAGE_SIZE, false);
	अगर (IS_ERR(t->batch))
		वापस PTR_ERR(t->batch);

	t->scratch.vma = create_vma(t, false);
	अगर (IS_ERR(t->scratch.vma)) अणु
		i915_vma_put(t->batch);
		वापस PTR_ERR(t->scratch.vma);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(t->buffers); i++) अणु
		काष्ठा i915_vma *vma;

		vma = create_vma(t, HAS_LMEM(i915) && i % 2);
		अगर (IS_ERR(vma)) अणु
			tiled_blits_destroy_buffers(t);
			वापस PTR_ERR(vma);
		पूर्ण

		t->buffers[i].vma = vma;
		t->buffers[i].tiling =
			i915_pअक्रमom_u32_max_state(I915_TILING_Y + 1, prng);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम fill_scratch(काष्ठा tiled_blits *t, u32 *vaddr, u32 val)
अणु
	पूर्णांक i;

	t->scratch.start_val = val;
	क्रम (i = 0; i < t->width * t->height; i++)
		vaddr[i] = val++;

	i915_gem_object_flush_map(t->scratch.vma->obj);
पूर्ण

अटल u64 swizzle_bit(अचिन्हित पूर्णांक bit, u64 offset)
अणु
	वापस (offset & BIT_ULL(bit)) >> (bit - 6);
पूर्ण

अटल u64 tiled_offset(स्थिर काष्ठा पूर्णांकel_gt *gt,
			u64 v,
			अचिन्हित पूर्णांक stride,
			अचिन्हित पूर्णांक tiling)
अणु
	अचिन्हित पूर्णांक swizzle;
	u64 x, y;

	अगर (tiling == I915_TILING_NONE)
		वापस v;

	y = भाग64_u64_rem(v, stride, &x);

	अगर (tiling == I915_TILING_X) अणु
		v = भाग64_u64_rem(y, 8, &y) * stride * 8;
		v += y * 512;
		v += भाग64_u64_rem(x, 512, &x) << 12;
		v += x;

		swizzle = gt->ggtt->bit_6_swizzle_x;
	पूर्ण अन्यथा अणु
		स्थिर अचिन्हित पूर्णांक ytile_span = 16;
		स्थिर अचिन्हित पूर्णांक ytile_height = 512;

		v = भाग64_u64_rem(y, 32, &y) * stride * 32;
		v += y * ytile_span;
		v += भाग64_u64_rem(x, ytile_span, &x) * ytile_height;
		v += x;

		swizzle = gt->ggtt->bit_6_swizzle_y;
	पूर्ण

	चयन (swizzle) अणु
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

अटल स्थिर अक्षर *repr_tiling(पूर्णांक tiling)
अणु
	चयन (tiling) अणु
	हाल I915_TILING_NONE: वापस "linear";
	हाल I915_TILING_X: वापस "X";
	हाल I915_TILING_Y: वापस "Y";
	शेष: वापस "unknown";
	पूर्ण
पूर्ण

अटल पूर्णांक verअगरy_buffer(स्थिर काष्ठा tiled_blits *t,
			 काष्ठा blit_buffer *buf,
			 काष्ठा rnd_state *prng)
अणु
	स्थिर u32 *vaddr;
	पूर्णांक ret = 0;
	पूर्णांक x, y, p;

	x = i915_pअक्रमom_u32_max_state(t->width, prng);
	y = i915_pअक्रमom_u32_max_state(t->height, prng);
	p = y * t->width + x;

	vaddr = i915_gem_object_pin_map_unlocked(buf->vma->obj, I915_MAP_WC);
	अगर (IS_ERR(vaddr))
		वापस PTR_ERR(vaddr);

	अगर (vaddr[0] != buf->start_val) अणु
		ret = -EINVAL;
	पूर्ण अन्यथा अणु
		u64 v = tiled_offset(buf->vma->vm->gt,
				     p * 4, t->width * 4,
				     buf->tiling);

		अगर (vaddr[v / माप(*vaddr)] != buf->start_val + p)
			ret = -EINVAL;
	पूर्ण
	अगर (ret) अणु
		pr_err("Invalid %s tiling detected at (%d, %d), start_val %x\n",
		       repr_tiling(buf->tiling),
		       x, y, buf->start_val);
		igt_hexdump(vaddr, 4096);
	पूर्ण

	i915_gem_object_unpin_map(buf->vma->obj);
	वापस ret;
पूर्ण

अटल पूर्णांक move_to_active(काष्ठा i915_vma *vma,
			  काष्ठा i915_request *rq,
			  अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक err;

	i915_vma_lock(vma);
	err = i915_request_aरुको_object(rq, vma->obj, false);
	अगर (err == 0)
		err = i915_vma_move_to_active(vma, rq, flags);
	i915_vma_unlock(vma);

	वापस err;
पूर्ण

अटल पूर्णांक pin_buffer(काष्ठा i915_vma *vma, u64 addr)
अणु
	पूर्णांक err;

	अगर (drm_mm_node_allocated(&vma->node) && vma->node.start != addr) अणु
		err = i915_vma_unbind(vma);
		अगर (err)
			वापस err;
	पूर्ण

	err = i915_vma_pin(vma, 0, 0, PIN_USER | PIN_OFFSET_FIXED | addr);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक
tiled_blit(काष्ठा tiled_blits *t,
	   काष्ठा blit_buffer *dst, u64 dst_addr,
	   काष्ठा blit_buffer *src, u64 src_addr)
अणु
	काष्ठा i915_request *rq;
	पूर्णांक err;

	err = pin_buffer(src->vma, src_addr);
	अगर (err) अणु
		pr_err("Cannot pin src @ %llx\n", src_addr);
		वापस err;
	पूर्ण

	err = pin_buffer(dst->vma, dst_addr);
	अगर (err) अणु
		pr_err("Cannot pin dst @ %llx\n", dst_addr);
		जाओ err_src;
	पूर्ण

	err = i915_vma_pin(t->batch, 0, 0, PIN_USER | PIN_HIGH);
	अगर (err) अणु
		pr_err("cannot pin batch\n");
		जाओ err_dst;
	पूर्ण

	err = prepare_blit(t, dst, src, t->batch->obj);
	अगर (err)
		जाओ err_bb;

	rq = पूर्णांकel_context_create_request(t->ce);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ err_bb;
	पूर्ण

	err = move_to_active(t->batch, rq, 0);
	अगर (!err)
		err = move_to_active(src->vma, rq, 0);
	अगर (!err)
		err = move_to_active(dst->vma, rq, 0);
	अगर (!err)
		err = rq->engine->emit_bb_start(rq,
						t->batch->node.start,
						t->batch->node.size,
						0);
	i915_request_get(rq);
	i915_request_add(rq);
	अगर (i915_request_रुको(rq, 0, HZ / 2) < 0)
		err = -ETIME;
	i915_request_put(rq);

	dst->start_val = src->start_val;
err_bb:
	i915_vma_unpin(t->batch);
err_dst:
	i915_vma_unpin(dst->vma);
err_src:
	i915_vma_unpin(src->vma);
	वापस err;
पूर्ण

अटल काष्ठा tiled_blits *
tiled_blits_create(काष्ठा पूर्णांकel_engine_cs *engine, काष्ठा rnd_state *prng)
अणु
	काष्ठा drm_mm_node hole;
	काष्ठा tiled_blits *t;
	u64 hole_size;
	पूर्णांक err;

	t = kzalloc(माप(*t), GFP_KERNEL);
	अगर (!t)
		वापस ERR_PTR(-ENOMEM);

	t->ce = पूर्णांकel_context_create(engine);
	अगर (IS_ERR(t->ce)) अणु
		err = PTR_ERR(t->ce);
		जाओ err_मुक्त;
	पूर्ण

	hole_size = 2 * PAGE_ALIGN(WIDTH * HEIGHT * 4);
	hole_size *= 2; /* room to maneuver */
	hole_size += 2 * I915_GTT_MIN_ALIGNMENT;

	mutex_lock(&t->ce->vm->mutex);
	स_रखो(&hole, 0, माप(hole));
	err = drm_mm_insert_node_in_range(&t->ce->vm->mm, &hole,
					  hole_size, 0, I915_COLOR_UNEVICTABLE,
					  0, U64_MAX,
					  DRM_MM_INSERT_BEST);
	अगर (!err)
		drm_mm_हटाओ_node(&hole);
	mutex_unlock(&t->ce->vm->mutex);
	अगर (err) अणु
		err = -ENODEV;
		जाओ err_put;
	पूर्ण

	t->hole = hole.start + I915_GTT_MIN_ALIGNMENT;
	pr_info("Using hole at %llx\n", t->hole);

	err = tiled_blits_create_buffers(t, WIDTH, HEIGHT, prng);
	अगर (err)
		जाओ err_put;

	वापस t;

err_put:
	पूर्णांकel_context_put(t->ce);
err_मुक्त:
	kमुक्त(t);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम tiled_blits_destroy(काष्ठा tiled_blits *t)
अणु
	tiled_blits_destroy_buffers(t);

	पूर्णांकel_context_put(t->ce);
	kमुक्त(t);
पूर्ण

अटल पूर्णांक tiled_blits_prepare(काष्ठा tiled_blits *t,
			       काष्ठा rnd_state *prng)
अणु
	u64 offset = PAGE_ALIGN(t->width * t->height * 4);
	u32 *map;
	पूर्णांक err;
	पूर्णांक i;

	map = i915_gem_object_pin_map_unlocked(t->scratch.vma->obj, I915_MAP_WC);
	अगर (IS_ERR(map))
		वापस PTR_ERR(map);

	/* Use scratch to fill objects */
	क्रम (i = 0; i < ARRAY_SIZE(t->buffers); i++) अणु
		fill_scratch(t, map, pअक्रमom_u32_state(prng));
		GEM_BUG_ON(verअगरy_buffer(t, &t->scratch, prng));

		err = tiled_blit(t,
				 &t->buffers[i], t->hole + offset,
				 &t->scratch, t->hole);
		अगर (err == 0)
			err = verअगरy_buffer(t, &t->buffers[i], prng);
		अगर (err) अणु
			pr_err("Failed to create buffer %d\n", i);
			अवरोध;
		पूर्ण
	पूर्ण

	i915_gem_object_unpin_map(t->scratch.vma->obj);
	वापस err;
पूर्ण

अटल पूर्णांक tiled_blits_bounce(काष्ठा tiled_blits *t, काष्ठा rnd_state *prng)
अणु
	u64 offset =
		round_up(t->width * t->height * 4, 2 * I915_GTT_MIN_ALIGNMENT);
	पूर्णांक err;

	/* We want to check position invariant tiling across GTT eviction */

	err = tiled_blit(t,
			 &t->buffers[1], t->hole + offset / 2,
			 &t->buffers[0], t->hole + 2 * offset);
	अगर (err)
		वापस err;

	/* Reposition so that we overlap the old addresses, and slightly off */
	err = tiled_blit(t,
			 &t->buffers[2], t->hole + I915_GTT_MIN_ALIGNMENT,
			 &t->buffers[1], t->hole + 3 * offset / 2);
	अगर (err)
		वापस err;

	err = verअगरy_buffer(t, &t->buffers[2], prng);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक __igt_client_tiled_blits(काष्ठा पूर्णांकel_engine_cs *engine,
				    काष्ठा rnd_state *prng)
अणु
	काष्ठा tiled_blits *t;
	पूर्णांक err;

	t = tiled_blits_create(engine, prng);
	अगर (IS_ERR(t))
		वापस PTR_ERR(t);

	err = tiled_blits_prepare(t, prng);
	अगर (err)
		जाओ out;

	err = tiled_blits_bounce(t, prng);
	अगर (err)
		जाओ out;

out:
	tiled_blits_destroy(t);
	वापस err;
पूर्ण

अटल bool has_bit17_swizzle(पूर्णांक sw)
अणु
	वापस (sw == I915_BIT_6_SWIZZLE_9_10_17 ||
		sw == I915_BIT_6_SWIZZLE_9_17);
पूर्ण

अटल bool bad_swizzling(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा i915_ggtt *ggtt = &i915->ggtt;

	अगर (i915->quirks & QUIRK_PIN_SWIZZLED_PAGES)
		वापस true;

	अगर (has_bit17_swizzle(ggtt->bit_6_swizzle_x) ||
	    has_bit17_swizzle(ggtt->bit_6_swizzle_y))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक igt_client_tiled_blits(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	I915_RND_STATE(prng);
	पूर्णांक inst = 0;

	/* Test requires explicit BLT tiling controls */
	अगर (INTEL_GEN(i915) < 4)
		वापस 0;

	अगर (bad_swizzling(i915)) /* Requires sane (sub-page) swizzling */
		वापस 0;

	करो अणु
		काष्ठा पूर्णांकel_engine_cs *engine;
		पूर्णांक err;

		engine = पूर्णांकel_engine_lookup_user(i915,
						  I915_ENGINE_CLASS_COPY,
						  inst++);
		अगर (!engine)
			वापस 0;

		err = __igt_client_tiled_blits(engine, &prng);
		अगर (err == -ENODEV)
			err = 0;
		अगर (err)
			वापस err;
	पूर्ण जबतक (1);
पूर्ण

पूर्णांक i915_gem_client_blt_live_selftests(काष्ठा drm_i915_निजी *i915)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(igt_client_fill),
		SUBTEST(igt_client_tiled_blits),
	पूर्ण;

	अगर (पूर्णांकel_gt_is_wedged(&i915->gt))
		वापस 0;

	वापस i915_live_subtests(tests, i915);
पूर्ण
