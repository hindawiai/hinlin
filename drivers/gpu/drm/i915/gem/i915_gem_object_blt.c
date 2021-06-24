<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश "i915_drv.h"
#समावेश "gt/intel_context.h"
#समावेश "gt/intel_engine_pm.h"
#समावेश "gt/intel_gpu_commands.h"
#समावेश "gt/intel_gt.h"
#समावेश "gt/intel_gt_buffer_pool.h"
#समावेश "gt/intel_ring.h"
#समावेश "i915_gem_clflush.h"
#समावेश "i915_gem_object_blt.h"

काष्ठा i915_vma *पूर्णांकel_emit_vma_fill_blt(काष्ठा पूर्णांकel_context *ce,
					 काष्ठा i915_vma *vma,
					 काष्ठा i915_gem_ww_ctx *ww,
					 u32 value)
अणु
	काष्ठा drm_i915_निजी *i915 = ce->vm->i915;
	स्थिर u32 block_size = SZ_8M; /* ~1ms at 8GiB/s preemption delay */
	काष्ठा पूर्णांकel_gt_buffer_pool_node *pool;
	काष्ठा i915_vma *batch;
	u64 offset;
	u64 count;
	u64 rem;
	u32 size;
	u32 *cmd;
	पूर्णांक err;

	GEM_BUG_ON(पूर्णांकel_engine_is_भव(ce->engine));
	पूर्णांकel_engine_pm_get(ce->engine);

	count = भाग_u64(round_up(vma->size, block_size), block_size);
	size = (1 + 8 * count) * माप(u32);
	size = round_up(size, PAGE_SIZE);
	pool = पूर्णांकel_gt_get_buffer_pool(ce->engine->gt, size, I915_MAP_WC);
	अगर (IS_ERR(pool)) अणु
		err = PTR_ERR(pool);
		जाओ out_pm;
	पूर्ण

	err = i915_gem_object_lock(pool->obj, ww);
	अगर (err)
		जाओ out_put;

	batch = i915_vma_instance(pool->obj, ce->vm, शून्य);
	अगर (IS_ERR(batch)) अणु
		err = PTR_ERR(batch);
		जाओ out_put;
	पूर्ण

	err = i915_vma_pin_ww(batch, ww, 0, 0, PIN_USER);
	अगर (unlikely(err))
		जाओ out_put;

	/* we pinned the pool, mark it as such */
	पूर्णांकel_gt_buffer_pool_mark_used(pool);

	cmd = i915_gem_object_pin_map(pool->obj, pool->type);
	अगर (IS_ERR(cmd)) अणु
		err = PTR_ERR(cmd);
		जाओ out_unpin;
	पूर्ण

	rem = vma->size;
	offset = vma->node.start;

	करो अणु
		u32 size = min_t(u64, rem, block_size);

		GEM_BUG_ON(size >> PAGE_SHIFT > S16_MAX);

		अगर (INTEL_GEN(i915) >= 8) अणु
			*cmd++ = XY_COLOR_BLT_CMD | BLT_WRITE_RGBA | (7 - 2);
			*cmd++ = BLT_DEPTH_32 | BLT_ROP_COLOR_COPY | PAGE_SIZE;
			*cmd++ = 0;
			*cmd++ = size >> PAGE_SHIFT << 16 | PAGE_SIZE / 4;
			*cmd++ = lower_32_bits(offset);
			*cmd++ = upper_32_bits(offset);
			*cmd++ = value;
		पूर्ण अन्यथा अणु
			*cmd++ = XY_COLOR_BLT_CMD | BLT_WRITE_RGBA | (6 - 2);
			*cmd++ = BLT_DEPTH_32 | BLT_ROP_COLOR_COPY | PAGE_SIZE;
			*cmd++ = 0;
			*cmd++ = size >> PAGE_SHIFT << 16 | PAGE_SIZE / 4;
			*cmd++ = offset;
			*cmd++ = value;
		पूर्ण

		/* Allow ourselves to be preempted in between blocks. */
		*cmd++ = MI_ARB_CHECK;

		offset += size;
		rem -= size;
	पूर्ण जबतक (rem);

	*cmd = MI_BATCH_BUFFER_END;

	i915_gem_object_flush_map(pool->obj);
	i915_gem_object_unpin_map(pool->obj);

	पूर्णांकel_gt_chipset_flush(ce->vm->gt);

	batch->निजी = pool;
	वापस batch;

out_unpin:
	i915_vma_unpin(batch);
out_put:
	पूर्णांकel_gt_buffer_pool_put(pool);
out_pm:
	पूर्णांकel_engine_pm_put(ce->engine);
	वापस ERR_PTR(err);
पूर्ण

पूर्णांक पूर्णांकel_emit_vma_mark_active(काष्ठा i915_vma *vma, काष्ठा i915_request *rq)
अणु
	पूर्णांक err;

	err = i915_request_aरुको_object(rq, vma->obj, false);
	अगर (err == 0)
		err = i915_vma_move_to_active(vma, rq, 0);
	अगर (unlikely(err))
		वापस err;

	वापस पूर्णांकel_gt_buffer_pool_mark_active(vma->निजी, rq);
पूर्ण

व्योम पूर्णांकel_emit_vma_release(काष्ठा पूर्णांकel_context *ce, काष्ठा i915_vma *vma)
अणु
	i915_vma_unpin(vma);
	पूर्णांकel_gt_buffer_pool_put(vma->निजी);
	पूर्णांकel_engine_pm_put(ce->engine);
पूर्ण

अटल पूर्णांक
move_obj_to_gpu(काष्ठा drm_i915_gem_object *obj,
		काष्ठा i915_request *rq,
		bool ग_लिखो)
अणु
	अगर (obj->cache_dirty & ~obj->cache_coherent)
		i915_gem_clflush_object(obj, 0);

	वापस i915_request_aरुको_object(rq, obj, ग_लिखो);
पूर्ण

पूर्णांक i915_gem_object_fill_blt(काष्ठा drm_i915_gem_object *obj,
			     काष्ठा पूर्णांकel_context *ce,
			     u32 value)
अणु
	काष्ठा i915_gem_ww_ctx ww;
	काष्ठा i915_request *rq;
	काष्ठा i915_vma *batch;
	काष्ठा i915_vma *vma;
	पूर्णांक err;

	vma = i915_vma_instance(obj, ce->vm, शून्य);
	अगर (IS_ERR(vma))
		वापस PTR_ERR(vma);

	i915_gem_ww_ctx_init(&ww, true);
	पूर्णांकel_engine_pm_get(ce->engine);
retry:
	err = i915_gem_object_lock(obj, &ww);
	अगर (err)
		जाओ out;

	err = पूर्णांकel_context_pin_ww(ce, &ww);
	अगर (err)
		जाओ out;

	err = i915_vma_pin_ww(vma, &ww, 0, 0, PIN_USER);
	अगर (err)
		जाओ out_ctx;

	batch = पूर्णांकel_emit_vma_fill_blt(ce, vma, &ww, value);
	अगर (IS_ERR(batch)) अणु
		err = PTR_ERR(batch);
		जाओ out_vma;
	पूर्ण

	rq = i915_request_create(ce);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ out_batch;
	पूर्ण

	err = पूर्णांकel_emit_vma_mark_active(batch, rq);
	अगर (unlikely(err))
		जाओ out_request;

	err = move_obj_to_gpu(vma->obj, rq, true);
	अगर (err == 0)
		err = i915_vma_move_to_active(vma, rq, EXEC_OBJECT_WRITE);
	अगर (unlikely(err))
		जाओ out_request;

	अगर (ce->engine->emit_init_bपढ़ोcrumb)
		err = ce->engine->emit_init_bपढ़ोcrumb(rq);

	अगर (likely(!err))
		err = ce->engine->emit_bb_start(rq,
						batch->node.start,
						batch->node.size,
						0);
out_request:
	अगर (unlikely(err))
		i915_request_set_error_once(rq, err);

	i915_request_add(rq);
out_batch:
	पूर्णांकel_emit_vma_release(ce, batch);
out_vma:
	i915_vma_unpin(vma);
out_ctx:
	पूर्णांकel_context_unpin(ce);
out:
	अगर (err == -EDEADLK) अणु
		err = i915_gem_ww_ctx_backoff(&ww);
		अगर (!err)
			जाओ retry;
	पूर्ण
	i915_gem_ww_ctx_fini(&ww);
	पूर्णांकel_engine_pm_put(ce->engine);
	वापस err;
पूर्ण

/* Wa_1209644611:icl,ehl */
अटल bool wa_1209644611_applies(काष्ठा drm_i915_निजी *i915, u32 size)
अणु
	u32 height = size >> PAGE_SHIFT;

	अगर (!IS_GEN(i915, 11))
		वापस false;

	वापस height % 4 == 3 && height <= 8;
पूर्ण

काष्ठा i915_vma *पूर्णांकel_emit_vma_copy_blt(काष्ठा पूर्णांकel_context *ce,
					 काष्ठा i915_gem_ww_ctx *ww,
					 काष्ठा i915_vma *src,
					 काष्ठा i915_vma *dst)
अणु
	काष्ठा drm_i915_निजी *i915 = ce->vm->i915;
	स्थिर u32 block_size = SZ_8M; /* ~1ms at 8GiB/s preemption delay */
	काष्ठा पूर्णांकel_gt_buffer_pool_node *pool;
	काष्ठा i915_vma *batch;
	u64 src_offset, dst_offset;
	u64 count, rem;
	u32 size, *cmd;
	पूर्णांक err;

	GEM_BUG_ON(src->size != dst->size);

	GEM_BUG_ON(पूर्णांकel_engine_is_भव(ce->engine));
	पूर्णांकel_engine_pm_get(ce->engine);

	count = भाग_u64(round_up(dst->size, block_size), block_size);
	size = (1 + 11 * count) * माप(u32);
	size = round_up(size, PAGE_SIZE);
	pool = पूर्णांकel_gt_get_buffer_pool(ce->engine->gt, size, I915_MAP_WC);
	अगर (IS_ERR(pool)) अणु
		err = PTR_ERR(pool);
		जाओ out_pm;
	पूर्ण

	err = i915_gem_object_lock(pool->obj, ww);
	अगर (err)
		जाओ out_put;

	batch = i915_vma_instance(pool->obj, ce->vm, शून्य);
	अगर (IS_ERR(batch)) अणु
		err = PTR_ERR(batch);
		जाओ out_put;
	पूर्ण

	err = i915_vma_pin_ww(batch, ww, 0, 0, PIN_USER);
	अगर (unlikely(err))
		जाओ out_put;

	/* we pinned the pool, mark it as such */
	पूर्णांकel_gt_buffer_pool_mark_used(pool);

	cmd = i915_gem_object_pin_map(pool->obj, pool->type);
	अगर (IS_ERR(cmd)) अणु
		err = PTR_ERR(cmd);
		जाओ out_unpin;
	पूर्ण

	rem = src->size;
	src_offset = src->node.start;
	dst_offset = dst->node.start;

	करो अणु
		size = min_t(u64, rem, block_size);
		GEM_BUG_ON(size >> PAGE_SHIFT > S16_MAX);

		अगर (INTEL_GEN(i915) >= 9 &&
		    !wa_1209644611_applies(i915, size)) अणु
			*cmd++ = GEN9_XY_FAST_COPY_BLT_CMD | (10 - 2);
			*cmd++ = BLT_DEPTH_32 | PAGE_SIZE;
			*cmd++ = 0;
			*cmd++ = size >> PAGE_SHIFT << 16 | PAGE_SIZE / 4;
			*cmd++ = lower_32_bits(dst_offset);
			*cmd++ = upper_32_bits(dst_offset);
			*cmd++ = 0;
			*cmd++ = PAGE_SIZE;
			*cmd++ = lower_32_bits(src_offset);
			*cmd++ = upper_32_bits(src_offset);
		पूर्ण अन्यथा अगर (INTEL_GEN(i915) >= 8) अणु
			*cmd++ = XY_SRC_COPY_BLT_CMD | BLT_WRITE_RGBA | (10 - 2);
			*cmd++ = BLT_DEPTH_32 | BLT_ROP_SRC_COPY | PAGE_SIZE;
			*cmd++ = 0;
			*cmd++ = size >> PAGE_SHIFT << 16 | PAGE_SIZE / 4;
			*cmd++ = lower_32_bits(dst_offset);
			*cmd++ = upper_32_bits(dst_offset);
			*cmd++ = 0;
			*cmd++ = PAGE_SIZE;
			*cmd++ = lower_32_bits(src_offset);
			*cmd++ = upper_32_bits(src_offset);
		पूर्ण अन्यथा अणु
			*cmd++ = SRC_COPY_BLT_CMD | BLT_WRITE_RGBA | (6 - 2);
			*cmd++ = BLT_DEPTH_32 | BLT_ROP_SRC_COPY | PAGE_SIZE;
			*cmd++ = size >> PAGE_SHIFT << 16 | PAGE_SIZE;
			*cmd++ = dst_offset;
			*cmd++ = PAGE_SIZE;
			*cmd++ = src_offset;
		पूर्ण

		/* Allow ourselves to be preempted in between blocks. */
		*cmd++ = MI_ARB_CHECK;

		src_offset += size;
		dst_offset += size;
		rem -= size;
	पूर्ण जबतक (rem);

	*cmd = MI_BATCH_BUFFER_END;

	i915_gem_object_flush_map(pool->obj);
	i915_gem_object_unpin_map(pool->obj);

	पूर्णांकel_gt_chipset_flush(ce->vm->gt);
	batch->निजी = pool;
	वापस batch;

out_unpin:
	i915_vma_unpin(batch);
out_put:
	पूर्णांकel_gt_buffer_pool_put(pool);
out_pm:
	पूर्णांकel_engine_pm_put(ce->engine);
	वापस ERR_PTR(err);
पूर्ण

पूर्णांक i915_gem_object_copy_blt(काष्ठा drm_i915_gem_object *src,
			     काष्ठा drm_i915_gem_object *dst,
			     काष्ठा पूर्णांकel_context *ce)
अणु
	काष्ठा i915_address_space *vm = ce->vm;
	काष्ठा i915_vma *vma[2], *batch;
	काष्ठा i915_gem_ww_ctx ww;
	काष्ठा i915_request *rq;
	पूर्णांक err, i;

	vma[0] = i915_vma_instance(src, vm, शून्य);
	अगर (IS_ERR(vma[0]))
		वापस PTR_ERR(vma[0]);

	vma[1] = i915_vma_instance(dst, vm, शून्य);
	अगर (IS_ERR(vma[1]))
		वापस PTR_ERR(vma[1]);

	i915_gem_ww_ctx_init(&ww, true);
	पूर्णांकel_engine_pm_get(ce->engine);
retry:
	err = i915_gem_object_lock(src, &ww);
	अगर (!err)
		err = i915_gem_object_lock(dst, &ww);
	अगर (!err)
		err = पूर्णांकel_context_pin_ww(ce, &ww);
	अगर (err)
		जाओ out;

	err = i915_vma_pin_ww(vma[0], &ww, 0, 0, PIN_USER);
	अगर (err)
		जाओ out_ctx;

	err = i915_vma_pin_ww(vma[1], &ww, 0, 0, PIN_USER);
	अगर (unlikely(err))
		जाओ out_unpin_src;

	batch = पूर्णांकel_emit_vma_copy_blt(ce, &ww, vma[0], vma[1]);
	अगर (IS_ERR(batch)) अणु
		err = PTR_ERR(batch);
		जाओ out_unpin_dst;
	पूर्ण

	rq = i915_request_create(ce);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ out_batch;
	पूर्ण

	err = पूर्णांकel_emit_vma_mark_active(batch, rq);
	अगर (unlikely(err))
		जाओ out_request;

	क्रम (i = 0; i < ARRAY_SIZE(vma); i++) अणु
		err = move_obj_to_gpu(vma[i]->obj, rq, i);
		अगर (unlikely(err))
			जाओ out_request;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(vma); i++) अणु
		अचिन्हित पूर्णांक flags = i ? EXEC_OBJECT_WRITE : 0;

		err = i915_vma_move_to_active(vma[i], rq, flags);
		अगर (unlikely(err))
			जाओ out_request;
	पूर्ण

	अगर (rq->engine->emit_init_bपढ़ोcrumb) अणु
		err = rq->engine->emit_init_bपढ़ोcrumb(rq);
		अगर (unlikely(err))
			जाओ out_request;
	पूर्ण

	err = rq->engine->emit_bb_start(rq,
					batch->node.start, batch->node.size,
					0);

out_request:
	अगर (unlikely(err))
		i915_request_set_error_once(rq, err);

	i915_request_add(rq);
out_batch:
	पूर्णांकel_emit_vma_release(ce, batch);
out_unpin_dst:
	i915_vma_unpin(vma[1]);
out_unpin_src:
	i915_vma_unpin(vma[0]);
out_ctx:
	पूर्णांकel_context_unpin(ce);
out:
	अगर (err == -EDEADLK) अणु
		err = i915_gem_ww_ctx_backoff(&ww);
		अगर (!err)
			जाओ retry;
	पूर्ण
	i915_gem_ww_ctx_fini(&ww);
	पूर्णांकel_engine_pm_put(ce->engine);
	वापस err;
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "selftests/i915_gem_object_blt.c"
#पूर्ण_अगर
