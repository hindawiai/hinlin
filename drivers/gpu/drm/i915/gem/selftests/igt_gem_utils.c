<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2018 Intel Corporation
 */

#समावेश "igt_gem_utils.h"

#समावेश "gem/i915_gem_context.h"
#समावेश "gem/i915_gem_pm.h"
#समावेश "gt/intel_context.h"
#समावेश "gt/intel_gpu_commands.h"
#समावेश "gt/intel_gt.h"
#समावेश "i915_vma.h"
#समावेश "i915_drv.h"

#समावेश "i915_request.h"

काष्ठा i915_request *
igt_request_alloc(काष्ठा i915_gem_context *ctx, काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_context *ce;
	काष्ठा i915_request *rq;

	/*
	 * Pinning the contexts may generate requests in order to acquire
	 * GGTT space, so करो this first beक्रमe we reserve a seqno क्रम
	 * ourselves.
	 */
	ce = i915_gem_context_get_engine(ctx, engine->legacy_idx);
	अगर (IS_ERR(ce))
		वापस ERR_CAST(ce);

	rq = पूर्णांकel_context_create_request(ce);
	पूर्णांकel_context_put(ce);

	वापस rq;
पूर्ण

काष्ठा i915_vma *
igt_emit_store_dw(काष्ठा i915_vma *vma,
		  u64 offset,
		  अचिन्हित दीर्घ count,
		  u32 val)
अणु
	काष्ठा drm_i915_gem_object *obj;
	स्थिर पूर्णांक gen = INTEL_GEN(vma->vm->i915);
	अचिन्हित दीर्घ n, size;
	u32 *cmd;
	पूर्णांक err;

	size = (4 * count + 1) * माप(u32);
	size = round_up(size, PAGE_SIZE);
	obj = i915_gem_object_create_पूर्णांकernal(vma->vm->i915, size);
	अगर (IS_ERR(obj))
		वापस ERR_CAST(obj);

	cmd = i915_gem_object_pin_map_unlocked(obj, I915_MAP_WC);
	अगर (IS_ERR(cmd)) अणु
		err = PTR_ERR(cmd);
		जाओ err;
	पूर्ण

	GEM_BUG_ON(offset + (count - 1) * PAGE_SIZE > vma->node.size);
	offset += vma->node.start;

	क्रम (n = 0; n < count; n++) अणु
		अगर (gen >= 8) अणु
			*cmd++ = MI_STORE_DWORD_IMM_GEN4;
			*cmd++ = lower_32_bits(offset);
			*cmd++ = upper_32_bits(offset);
			*cmd++ = val;
		पूर्ण अन्यथा अगर (gen >= 4) अणु
			*cmd++ = MI_STORE_DWORD_IMM_GEN4 |
				(gen < 6 ? MI_USE_GGTT : 0);
			*cmd++ = 0;
			*cmd++ = offset;
			*cmd++ = val;
		पूर्ण अन्यथा अणु
			*cmd++ = MI_STORE_DWORD_IMM | MI_MEM_VIRTUAL;
			*cmd++ = offset;
			*cmd++ = val;
		पूर्ण
		offset += PAGE_SIZE;
	पूर्ण
	*cmd = MI_BATCH_BUFFER_END;

	i915_gem_object_flush_map(obj);
	i915_gem_object_unpin_map(obj);

	पूर्णांकel_gt_chipset_flush(vma->vm->gt);

	vma = i915_vma_instance(obj, vma->vm, शून्य);
	अगर (IS_ERR(vma)) अणु
		err = PTR_ERR(vma);
		जाओ err;
	पूर्ण

	err = i915_vma_pin(vma, 0, 0, PIN_USER);
	अगर (err)
		जाओ err;

	वापस vma;

err:
	i915_gem_object_put(obj);
	वापस ERR_PTR(err);
पूर्ण

पूर्णांक igt_gpu_fill_dw(काष्ठा पूर्णांकel_context *ce,
		    काष्ठा i915_vma *vma, u64 offset,
		    अचिन्हित दीर्घ count, u32 val)
अणु
	काष्ठा i915_request *rq;
	काष्ठा i915_vma *batch;
	अचिन्हित पूर्णांक flags;
	पूर्णांक err;

	GEM_BUG_ON(!पूर्णांकel_engine_can_store_dword(ce->engine));
	GEM_BUG_ON(!i915_vma_is_pinned(vma));

	batch = igt_emit_store_dw(vma, offset, count, val);
	अगर (IS_ERR(batch))
		वापस PTR_ERR(batch);

	rq = पूर्णांकel_context_create_request(ce);
	अगर (IS_ERR(rq)) अणु
		err = PTR_ERR(rq);
		जाओ err_batch;
	पूर्ण

	i915_vma_lock(batch);
	err = i915_request_aरुको_object(rq, batch->obj, false);
	अगर (err == 0)
		err = i915_vma_move_to_active(batch, rq, 0);
	i915_vma_unlock(batch);
	अगर (err)
		जाओ skip_request;

	i915_vma_lock(vma);
	err = i915_request_aरुको_object(rq, vma->obj, true);
	अगर (err == 0)
		err = i915_vma_move_to_active(vma, rq, EXEC_OBJECT_WRITE);
	i915_vma_unlock(vma);
	अगर (err)
		जाओ skip_request;

	flags = 0;
	अगर (INTEL_GEN(ce->vm->i915) <= 5)
		flags |= I915_DISPATCH_SECURE;

	err = rq->engine->emit_bb_start(rq,
					batch->node.start, batch->node.size,
					flags);

skip_request:
	अगर (err)
		i915_request_set_error_once(rq, err);
	i915_request_add(rq);
err_batch:
	i915_vma_unpin_and_release(&batch, 0);
	वापस err;
पूर्ण
