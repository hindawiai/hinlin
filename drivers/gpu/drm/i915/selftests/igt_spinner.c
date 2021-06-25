<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2018 Intel Corporation
 */
#समावेश "gt/intel_gpu_commands.h"
#समावेश "gt/intel_gt.h"

#समावेश "gem/selftests/igt_gem_utils.h"

#समावेश "igt_spinner.h"

पूर्णांक igt_spinner_init(काष्ठा igt_spinner *spin, काष्ठा पूर्णांकel_gt *gt)
अणु
	पूर्णांक err;

	स_रखो(spin, 0, माप(*spin));
	spin->gt = gt;

	spin->hws = i915_gem_object_create_पूर्णांकernal(gt->i915, PAGE_SIZE);
	अगर (IS_ERR(spin->hws)) अणु
		err = PTR_ERR(spin->hws);
		जाओ err;
	पूर्ण
	i915_gem_object_set_cache_coherency(spin->hws, I915_CACHE_LLC);

	spin->obj = i915_gem_object_create_पूर्णांकernal(gt->i915, PAGE_SIZE);
	अगर (IS_ERR(spin->obj)) अणु
		err = PTR_ERR(spin->obj);
		जाओ err_hws;
	पूर्ण

	वापस 0;

err_hws:
	i915_gem_object_put(spin->hws);
err:
	वापस err;
पूर्ण

अटल व्योम *igt_spinner_pin_obj(काष्ठा पूर्णांकel_context *ce,
				 काष्ठा i915_gem_ww_ctx *ww,
				 काष्ठा drm_i915_gem_object *obj,
				 अचिन्हित पूर्णांक mode, काष्ठा i915_vma **vma)
अणु
	व्योम *vaddr;
	पूर्णांक ret;

	*vma = i915_vma_instance(obj, ce->vm, शून्य);
	अगर (IS_ERR(*vma))
		वापस ERR_CAST(*vma);

	ret = i915_gem_object_lock(obj, ww);
	अगर (ret)
		वापस ERR_PTR(ret);

	vaddr = i915_gem_object_pin_map(obj, mode);

	अगर (!ww)
		i915_gem_object_unlock(obj);

	अगर (IS_ERR(vaddr))
		वापस vaddr;

	अगर (ww)
		ret = i915_vma_pin_ww(*vma, ww, 0, 0, PIN_USER);
	अन्यथा
		ret = i915_vma_pin(*vma, 0, 0, PIN_USER);

	अगर (ret) अणु
		i915_gem_object_unpin_map(obj);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस vaddr;
पूर्ण

पूर्णांक igt_spinner_pin(काष्ठा igt_spinner *spin,
		    काष्ठा पूर्णांकel_context *ce,
		    काष्ठा i915_gem_ww_ctx *ww)
अणु
	व्योम *vaddr;

	अगर (spin->ce && WARN_ON(spin->ce != ce))
		वापस -ENODEV;
	spin->ce = ce;

	अगर (!spin->seqno) अणु
		vaddr = igt_spinner_pin_obj(ce, ww, spin->hws, I915_MAP_WB, &spin->hws_vma);
		अगर (IS_ERR(vaddr))
			वापस PTR_ERR(vaddr);

		spin->seqno = स_रखो(vaddr, 0xff, PAGE_SIZE);
	पूर्ण

	अगर (!spin->batch) अणु
		अचिन्हित पूर्णांक mode =
			i915_coherent_map_type(spin->gt->i915);

		vaddr = igt_spinner_pin_obj(ce, ww, spin->obj, mode, &spin->batch_vma);
		अगर (IS_ERR(vaddr))
			वापस PTR_ERR(vaddr);

		spin->batch = vaddr;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक seqno_offset(u64 fence)
अणु
	वापस offset_in_page(माप(u32) * fence);
पूर्ण

अटल u64 hws_address(स्थिर काष्ठा i915_vma *hws,
		       स्थिर काष्ठा i915_request *rq)
अणु
	वापस hws->node.start + seqno_offset(rq->fence.context);
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

काष्ठा i915_request *
igt_spinner_create_request(काष्ठा igt_spinner *spin,
			   काष्ठा पूर्णांकel_context *ce,
			   u32 arbitration_command)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = ce->engine;
	काष्ठा i915_request *rq = शून्य;
	काष्ठा i915_vma *hws, *vma;
	अचिन्हित पूर्णांक flags;
	u32 *batch;
	पूर्णांक err;

	GEM_BUG_ON(spin->gt != ce->vm->gt);

	अगर (!पूर्णांकel_engine_can_store_dword(ce->engine))
		वापस ERR_PTR(-ENODEV);

	अगर (!spin->batch) अणु
		err = igt_spinner_pin(spin, ce, शून्य);
		अगर (err)
			वापस ERR_PTR(err);
	पूर्ण

	hws = spin->hws_vma;
	vma = spin->batch_vma;

	rq = पूर्णांकel_context_create_request(ce);
	अगर (IS_ERR(rq))
		वापस ERR_CAST(rq);

	err = move_to_active(vma, rq, 0);
	अगर (err)
		जाओ cancel_rq;

	err = move_to_active(hws, rq, 0);
	अगर (err)
		जाओ cancel_rq;

	batch = spin->batch;

	अगर (INTEL_GEN(rq->engine->i915) >= 8) अणु
		*batch++ = MI_STORE_DWORD_IMM_GEN4;
		*batch++ = lower_32_bits(hws_address(hws, rq));
		*batch++ = upper_32_bits(hws_address(hws, rq));
	पूर्ण अन्यथा अगर (INTEL_GEN(rq->engine->i915) >= 6) अणु
		*batch++ = MI_STORE_DWORD_IMM_GEN4;
		*batch++ = 0;
		*batch++ = hws_address(hws, rq);
	पूर्ण अन्यथा अगर (INTEL_GEN(rq->engine->i915) >= 4) अणु
		*batch++ = MI_STORE_DWORD_IMM_GEN4 | MI_USE_GGTT;
		*batch++ = 0;
		*batch++ = hws_address(hws, rq);
	पूर्ण अन्यथा अणु
		*batch++ = MI_STORE_DWORD_IMM | MI_MEM_VIRTUAL;
		*batch++ = hws_address(hws, rq);
	पूर्ण
	*batch++ = rq->fence.seqno;

	*batch++ = arbitration_command;

	अगर (INTEL_GEN(rq->engine->i915) >= 8)
		*batch++ = MI_BATCH_BUFFER_START | BIT(8) | 1;
	अन्यथा अगर (IS_HASWELL(rq->engine->i915))
		*batch++ = MI_BATCH_BUFFER_START | MI_BATCH_PPGTT_HSW;
	अन्यथा अगर (INTEL_GEN(rq->engine->i915) >= 6)
		*batch++ = MI_BATCH_BUFFER_START;
	अन्यथा
		*batch++ = MI_BATCH_BUFFER_START | MI_BATCH_GTT;
	*batch++ = lower_32_bits(vma->node.start);
	*batch++ = upper_32_bits(vma->node.start);

	*batch++ = MI_BATCH_BUFFER_END; /* not reached */

	पूर्णांकel_gt_chipset_flush(engine->gt);

	अगर (engine->emit_init_bपढ़ोcrumb) अणु
		err = engine->emit_init_bपढ़ोcrumb(rq);
		अगर (err)
			जाओ cancel_rq;
	पूर्ण

	flags = 0;
	अगर (INTEL_GEN(rq->engine->i915) <= 5)
		flags |= I915_DISPATCH_SECURE;
	err = engine->emit_bb_start(rq, vma->node.start, PAGE_SIZE, flags);

cancel_rq:
	अगर (err) अणु
		i915_request_set_error_once(rq, err);
		i915_request_add(rq);
	पूर्ण
	वापस err ? ERR_PTR(err) : rq;
पूर्ण

अटल u32
hws_seqno(स्थिर काष्ठा igt_spinner *spin, स्थिर काष्ठा i915_request *rq)
अणु
	u32 *seqno = spin->seqno + seqno_offset(rq->fence.context);

	वापस READ_ONCE(*seqno);
पूर्ण

व्योम igt_spinner_end(काष्ठा igt_spinner *spin)
अणु
	अगर (!spin->batch)
		वापस;

	*spin->batch = MI_BATCH_BUFFER_END;
	पूर्णांकel_gt_chipset_flush(spin->gt);
पूर्ण

व्योम igt_spinner_fini(काष्ठा igt_spinner *spin)
अणु
	igt_spinner_end(spin);

	अगर (spin->batch) अणु
		i915_vma_unpin(spin->batch_vma);
		i915_gem_object_unpin_map(spin->obj);
	पूर्ण
	i915_gem_object_put(spin->obj);

	अगर (spin->seqno) अणु
		i915_vma_unpin(spin->hws_vma);
		i915_gem_object_unpin_map(spin->hws);
	पूर्ण
	i915_gem_object_put(spin->hws);
पूर्ण

bool igt_रुको_क्रम_spinner(काष्ठा igt_spinner *spin, काष्ठा i915_request *rq)
अणु
	अगर (i915_request_is_पढ़ोy(rq))
		पूर्णांकel_engine_flush_submission(rq->engine);

	वापस !(रुको_क्रम_us(i915_seqno_passed(hws_seqno(spin, rq),
					       rq->fence.seqno),
			     100) &&
		 रुको_क्रम(i915_seqno_passed(hws_seqno(spin, rq),
					    rq->fence.seqno),
			  50));
पूर्ण
