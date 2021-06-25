<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2014 Intel Corporation
 */

#समावेश "i915_drv.h"
#समावेश "intel_renderstate.h"
#समावेश "intel_context.h"
#समावेश "intel_gpu_commands.h"
#समावेश "intel_ring.h"

अटल स्थिर काष्ठा पूर्णांकel_renderstate_rodata *
render_state_get_rodata(स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	अगर (engine->class != RENDER_CLASS)
		वापस शून्य;

	चयन (INTEL_GEN(engine->i915)) अणु
	हाल 6:
		वापस &gen6_null_state;
	हाल 7:
		वापस &gen7_null_state;
	हाल 8:
		वापस &gen8_null_state;
	हाल 9:
		वापस &gen9_null_state;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Macro to add commands to auxiliary batch.
 * This macro only checks क्रम page overflow beक्रमe inserting the commands,
 * this is sufficient as the null state generator makes the final batch
 * with two passes to build command and state separately. At this poपूर्णांक
 * the size of both are known and it compacts them by relocating the state
 * right after the commands taking care of alignment so we should sufficient
 * space below them क्रम adding new commands.
 */
#घोषणा OUT_BATCH(batch, i, val)				\
	करो अणु							\
		अगर ((i) >= PAGE_SIZE / माप(u32))		\
			जाओ out;				\
		(batch)[(i)++] = (val);				\
	पूर्ण जबतक (0)

अटल पूर्णांक render_state_setup(काष्ठा पूर्णांकel_renderstate *so,
			      काष्ठा drm_i915_निजी *i915)
अणु
	स्थिर काष्ठा पूर्णांकel_renderstate_rodata *rodata = so->rodata;
	अचिन्हित पूर्णांक i = 0, reloc_index = 0;
	पूर्णांक ret = -EINVAL;
	u32 *d;

	d = i915_gem_object_pin_map(so->vma->obj, I915_MAP_WB);
	अगर (IS_ERR(d))
		वापस PTR_ERR(d);

	जबतक (i < rodata->batch_items) अणु
		u32 s = rodata->batch[i];

		अगर (i * 4  == rodata->reloc[reloc_index]) अणु
			u64 r = s + so->vma->node.start;

			s = lower_32_bits(r);
			अगर (HAS_64BIT_RELOC(i915)) अणु
				अगर (i + 1 >= rodata->batch_items ||
				    rodata->batch[i + 1] != 0)
					जाओ out;

				d[i++] = s;
				s = upper_32_bits(r);
			पूर्ण

			reloc_index++;
		पूर्ण

		d[i++] = s;
	पूर्ण

	अगर (rodata->reloc[reloc_index] != -1) अणु
		drm_err(&i915->drm, "only %d relocs resolved\n", reloc_index);
		जाओ out;
	पूर्ण

	so->batch_offset = i915_ggtt_offset(so->vma);
	so->batch_size = rodata->batch_items * माप(u32);

	जबतक (i % CACHELINE_DWORDS)
		OUT_BATCH(d, i, MI_NOOP);

	so->aux_offset = i * माप(u32);

	अगर (HAS_POOLED_EU(i915)) अणु
		/*
		 * We always program 3x6 pool config but depending upon which
		 * subslice is disabled HW drops करोwn to appropriate config
		 * shown below.
		 *
		 * In the below table 2x6 config always refers to
		 * fused-करोwn version, native 2x6 is not available and can
		 * be ignored
		 *
		 * SNo  subslices config                eu pool configuration
		 * -----------------------------------------------------------
		 * 1    3 subslices enabled (3x6)  -    0x00777000  (9+9)
		 * 2    ss0 disabled (2x6)         -    0x00777000  (3+9)
		 * 3    ss1 disabled (2x6)         -    0x00770000  (6+6)
		 * 4    ss2 disabled (2x6)         -    0x00007000  (9+3)
		 */
		u32 eu_pool_config = 0x00777000;

		OUT_BATCH(d, i, GEN9_MEDIA_POOL_STATE);
		OUT_BATCH(d, i, GEN9_MEDIA_POOL_ENABLE);
		OUT_BATCH(d, i, eu_pool_config);
		OUT_BATCH(d, i, 0);
		OUT_BATCH(d, i, 0);
		OUT_BATCH(d, i, 0);
	पूर्ण

	OUT_BATCH(d, i, MI_BATCH_BUFFER_END);
	so->aux_size = i * माप(u32) - so->aux_offset;
	so->aux_offset += so->batch_offset;
	/*
	 * Since we are sending length, we need to strictly conक्रमm to
	 * all requirements. For Gen2 this must be a multiple of 8.
	 */
	so->aux_size = ALIGN(so->aux_size, 8);

	ret = 0;
out:
	__i915_gem_object_flush_map(so->vma->obj, 0, i * माप(u32));
	__i915_gem_object_release_map(so->vma->obj);
	वापस ret;
पूर्ण

#अघोषित OUT_BATCH

पूर्णांक पूर्णांकel_renderstate_init(काष्ठा पूर्णांकel_renderstate *so,
			   काष्ठा पूर्णांकel_context *ce)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = ce->engine;
	काष्ठा drm_i915_gem_object *obj = शून्य;
	पूर्णांक err;

	स_रखो(so, 0, माप(*so));

	so->rodata = render_state_get_rodata(engine);
	अगर (so->rodata) अणु
		अगर (so->rodata->batch_items * 4 > PAGE_SIZE)
			वापस -EINVAL;

		obj = i915_gem_object_create_पूर्णांकernal(engine->i915, PAGE_SIZE);
		अगर (IS_ERR(obj))
			वापस PTR_ERR(obj);

		so->vma = i915_vma_instance(obj, &engine->gt->ggtt->vm, शून्य);
		अगर (IS_ERR(so->vma)) अणु
			err = PTR_ERR(so->vma);
			जाओ err_obj;
		पूर्ण
	पूर्ण

	i915_gem_ww_ctx_init(&so->ww, true);
retry:
	err = पूर्णांकel_context_pin_ww(ce, &so->ww);
	अगर (err)
		जाओ err_fini;

	/* वापस early अगर there's nothing to setup */
	अगर (!err && !so->rodata)
		वापस 0;

	err = i915_gem_object_lock(so->vma->obj, &so->ww);
	अगर (err)
		जाओ err_context;

	err = i915_vma_pin_ww(so->vma, &so->ww, 0, 0, PIN_GLOBAL | PIN_HIGH);
	अगर (err)
		जाओ err_context;

	err = render_state_setup(so, engine->i915);
	अगर (err)
		जाओ err_unpin;

	वापस 0;

err_unpin:
	i915_vma_unpin(so->vma);
err_context:
	पूर्णांकel_context_unpin(ce);
err_fini:
	अगर (err == -EDEADLK) अणु
		err = i915_gem_ww_ctx_backoff(&so->ww);
		अगर (!err)
			जाओ retry;
	पूर्ण
	i915_gem_ww_ctx_fini(&so->ww);
err_obj:
	अगर (obj)
		i915_gem_object_put(obj);
	so->vma = शून्य;
	वापस err;
पूर्ण

पूर्णांक पूर्णांकel_renderstate_emit(काष्ठा पूर्णांकel_renderstate *so,
			   काष्ठा i915_request *rq)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = rq->engine;
	पूर्णांक err;

	अगर (!so->vma)
		वापस 0;

	err = i915_request_aरुको_object(rq, so->vma->obj, false);
	अगर (err == 0)
		err = i915_vma_move_to_active(so->vma, rq, 0);
	अगर (err)
		वापस err;

	err = engine->emit_bb_start(rq,
				    so->batch_offset, so->batch_size,
				    I915_DISPATCH_SECURE);
	अगर (err)
		वापस err;

	अगर (so->aux_size > 8) अणु
		err = engine->emit_bb_start(rq,
					    so->aux_offset, so->aux_size,
					    I915_DISPATCH_SECURE);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

व्योम पूर्णांकel_renderstate_fini(काष्ठा पूर्णांकel_renderstate *so,
			    काष्ठा पूर्णांकel_context *ce)
अणु
	अगर (so->vma) अणु
		i915_vma_unpin(so->vma);
		i915_vma_बंद(so->vma);
	पूर्ण

	पूर्णांकel_context_unpin(ce);
	i915_gem_ww_ctx_fini(&so->ww);

	अगर (so->vma)
		i915_gem_object_put(so->vma->obj);
पूर्ण
