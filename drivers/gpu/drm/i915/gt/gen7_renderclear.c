<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश "gen7_renderclear.h"
#समावेश "i915_drv.h"
#समावेश "intel_gpu_commands.h"

#घोषणा GT3_INLINE_DATA_DELAYS 0x1E00
#घोषणा batch_advance(Y, CS) GEM_BUG_ON((Y)->end != (CS))

काष्ठा cb_kernel अणु
	स्थिर व्योम *data;
	u32 size;
पूर्ण;

#घोषणा CB_KERNEL(name) अणु .data = (name), .size = माप(name) पूर्ण

#समावेश "ivb_clear_kernel.c"
अटल स्थिर काष्ठा cb_kernel cb_kernel_ivb = CB_KERNEL(ivb_clear_kernel);

#समावेश "hsw_clear_kernel.c"
अटल स्थिर काष्ठा cb_kernel cb_kernel_hsw = CB_KERNEL(hsw_clear_kernel);

काष्ठा batch_chunk अणु
	काष्ठा i915_vma *vma;
	u32 offset;
	u32 *start;
	u32 *end;
	u32 max_items;
पूर्ण;

काष्ठा batch_vals अणु
	u32 max_thपढ़ोs;
	u32 state_start;
	u32 surface_start;
	u32 surface_height;
	u32 surface_width;
	u32 size;
पूर्ण;

अटल पूर्णांक num_primitives(स्थिर काष्ठा batch_vals *bv)
अणु
	/*
	 * We need to saturate the GPU with work in order to dispatch
	 * a shader on every HW thपढ़ो, and clear the thपढ़ो-local रेजिस्टरs.
	 * In लघु, we have to dispatch work faster than the shaders can
	 * run in order to fill the EU and occupy each HW thपढ़ो.
	 */
	वापस bv->max_thपढ़ोs;
पूर्ण

अटल व्योम
batch_get_शेषs(काष्ठा drm_i915_निजी *i915, काष्ठा batch_vals *bv)
अणु
	अगर (IS_HASWELL(i915)) अणु
		चयन (INTEL_INFO(i915)->gt) अणु
		शेष:
		हाल 1:
			bv->max_thपढ़ोs = 70;
			अवरोध;
		हाल 2:
			bv->max_thपढ़ोs = 140;
			अवरोध;
		हाल 3:
			bv->max_thपढ़ोs = 280;
			अवरोध;
		पूर्ण
		bv->surface_height = 16 * 16;
		bv->surface_width = 32 * 2 * 16;
	पूर्ण अन्यथा अणु
		चयन (INTEL_INFO(i915)->gt) अणु
		शेष:
		हाल 1: /* including vlv */
			bv->max_thपढ़ोs = 36;
			अवरोध;
		हाल 2:
			bv->max_thपढ़ोs = 128;
			अवरोध;
		पूर्ण
		bv->surface_height = 16 * 8;
		bv->surface_width = 32 * 16;
	पूर्ण
	bv->state_start = round_up(SZ_1K + num_primitives(bv) * 64, SZ_4K);
	bv->surface_start = bv->state_start + SZ_4K;
	bv->size = bv->surface_start + bv->surface_height * bv->surface_width;
पूर्ण

अटल व्योम batch_init(काष्ठा batch_chunk *bc,
		       काष्ठा i915_vma *vma,
		       u32 *start, u32 offset, u32 max_bytes)
अणु
	bc->vma = vma;
	bc->offset = offset;
	bc->start = start + bc->offset / माप(*bc->start);
	bc->end = bc->start;
	bc->max_items = max_bytes / माप(*bc->start);
पूर्ण

अटल u32 batch_offset(स्थिर काष्ठा batch_chunk *bc, u32 *cs)
अणु
	वापस (cs - bc->start) * माप(*bc->start) + bc->offset;
पूर्ण

अटल u32 batch_addr(स्थिर काष्ठा batch_chunk *bc)
अणु
	वापस bc->vma->node.start;
पूर्ण

अटल व्योम batch_add(काष्ठा batch_chunk *bc, स्थिर u32 d)
अणु
	GEM_BUG_ON((bc->end - bc->start) >= bc->max_items);
	*bc->end++ = d;
पूर्ण

अटल u32 *batch_alloc_items(काष्ठा batch_chunk *bc, u32 align, u32 items)
अणु
	u32 *map;

	अगर (align) अणु
		u32 *end = PTR_ALIGN(bc->end, align);

		स_रखो32(bc->end, 0, end - bc->end);
		bc->end = end;
	पूर्ण

	map = bc->end;
	bc->end += items;

	वापस map;
पूर्ण

अटल u32 *batch_alloc_bytes(काष्ठा batch_chunk *bc, u32 align, u32 bytes)
अणु
	GEM_BUG_ON(!IS_ALIGNED(bytes, माप(*bc->start)));
	वापस batch_alloc_items(bc, align, bytes / माप(*bc->start));
पूर्ण

अटल u32
gen7_fill_surface_state(काष्ठा batch_chunk *state,
			स्थिर u32 dst_offset,
			स्थिर काष्ठा batch_vals *bv)
अणु
	u32 surface_h = bv->surface_height;
	u32 surface_w = bv->surface_width;
	u32 *cs = batch_alloc_items(state, 32, 8);
	u32 offset = batch_offset(state, cs);

#घोषणा SURFACE_2D 1
#घोषणा SURFACEFORMAT_B8G8R8A8_UNORM 0x0C0
#घोषणा RENDER_CACHE_READ_WRITE 1

	*cs++ = SURFACE_2D << 29 |
		(SURFACEFORMAT_B8G8R8A8_UNORM << 18) |
		(RENDER_CACHE_READ_WRITE << 8);

	*cs++ = batch_addr(state) + dst_offset;

	*cs++ = ((surface_h / 4 - 1) << 16) | (surface_w / 4 - 1);
	*cs++ = surface_w;
	*cs++ = 0;
	*cs++ = 0;
	*cs++ = 0;
#घोषणा SHADER_CHANNELS(r, g, b, a) \
	(((r) << 25) | ((g) << 22) | ((b) << 19) | ((a) << 16))
	*cs++ = SHADER_CHANNELS(4, 5, 6, 7);
	batch_advance(state, cs);

	वापस offset;
पूर्ण

अटल u32
gen7_fill_binding_table(काष्ठा batch_chunk *state,
			स्थिर काष्ठा batch_vals *bv)
अणु
	u32 surface_start =
		gen7_fill_surface_state(state, bv->surface_start, bv);
	u32 *cs = batch_alloc_items(state, 32, 8);
	u32 offset = batch_offset(state, cs);

	*cs++ = surface_start - state->offset;
	*cs++ = 0;
	*cs++ = 0;
	*cs++ = 0;
	*cs++ = 0;
	*cs++ = 0;
	*cs++ = 0;
	*cs++ = 0;
	batch_advance(state, cs);

	वापस offset;
पूर्ण

अटल u32
gen7_fill_kernel_data(काष्ठा batch_chunk *state,
		      स्थिर u32 *data,
		      स्थिर u32 size)
अणु
	वापस batch_offset(state,
			    स_नकल(batch_alloc_bytes(state, 64, size),
				   data, size));
पूर्ण

अटल u32
gen7_fill_पूर्णांकerface_descriptor(काष्ठा batch_chunk *state,
			       स्थिर काष्ठा batch_vals *bv,
			       स्थिर काष्ठा cb_kernel *kernel,
			       अचिन्हित पूर्णांक count)
अणु
	u32 kernel_offset =
		gen7_fill_kernel_data(state, kernel->data, kernel->size);
	u32 binding_table = gen7_fill_binding_table(state, bv);
	u32 *cs = batch_alloc_items(state, 32, 8 * count);
	u32 offset = batch_offset(state, cs);

	*cs++ = kernel_offset;
	*cs++ = (1 << 7) | (1 << 13);
	*cs++ = 0;
	*cs++ = (binding_table - state->offset) | 1;
	*cs++ = 0;
	*cs++ = 0;
	*cs++ = 0;
	*cs++ = 0;

	/* 1 - 63dummy idds */
	स_रखो32(cs, 0x00, (count - 1) * 8);
	batch_advance(state, cs + (count - 1) * 8);

	वापस offset;
पूर्ण

अटल व्योम
gen7_emit_state_base_address(काष्ठा batch_chunk *batch,
			     u32 surface_state_base)
अणु
	u32 *cs = batch_alloc_items(batch, 0, 10);

	*cs++ = STATE_BASE_ADDRESS | (10 - 2);
	/* general */
	*cs++ = batch_addr(batch) | BASE_ADDRESS_MODIFY;
	/* surface */
	*cs++ = (batch_addr(batch) + surface_state_base) | BASE_ADDRESS_MODIFY;
	/* dynamic */
	*cs++ = batch_addr(batch) | BASE_ADDRESS_MODIFY;
	/* indirect */
	*cs++ = batch_addr(batch) | BASE_ADDRESS_MODIFY;
	/* inकाष्ठाion */
	*cs++ = batch_addr(batch) | BASE_ADDRESS_MODIFY;

	/* general/dynamic/indirect/inकाष्ठाion access Bound */
	*cs++ = 0;
	*cs++ = BASE_ADDRESS_MODIFY;
	*cs++ = 0;
	*cs++ = BASE_ADDRESS_MODIFY;
	batch_advance(batch, cs);
पूर्ण

अटल व्योम
gen7_emit_vfe_state(काष्ठा batch_chunk *batch,
		    स्थिर काष्ठा batch_vals *bv,
		    u32 urb_size, u32 curbe_size,
		    u32 mode)
अणु
	u32 thपढ़ोs = bv->max_thपढ़ोs - 1;
	u32 *cs = batch_alloc_items(batch, 32, 8);

	*cs++ = MEDIA_VFE_STATE | (8 - 2);

	/* scratch buffer */
	*cs++ = 0;

	/* number of thपढ़ोs & urb entries क्रम GPGPU vs Media Mode */
	*cs++ = thपढ़ोs << 16 | 1 << 8 | mode << 2;

	*cs++ = 0;

	/* urb entry size & curbe size in 256 bits unit */
	*cs++ = urb_size << 16 | curbe_size;

	/* scoreboard */
	*cs++ = 0;
	*cs++ = 0;
	*cs++ = 0;
	batch_advance(batch, cs);
पूर्ण

अटल व्योम
gen7_emit_पूर्णांकerface_descriptor_load(काष्ठा batch_chunk *batch,
				    स्थिर u32 पूर्णांकerface_descriptor,
				    अचिन्हित पूर्णांक count)
अणु
	u32 *cs = batch_alloc_items(batch, 8, 4);

	*cs++ = MEDIA_INTERFACE_DESCRIPTOR_LOAD | (4 - 2);
	*cs++ = 0;
	*cs++ = count * 8 * माप(*cs);

	/*
	 * पूर्णांकerface descriptor address - it is relative to the dynamics base
	 * address
	 */
	*cs++ = पूर्णांकerface_descriptor;
	batch_advance(batch, cs);
पूर्ण

अटल व्योम
gen7_emit_media_object(काष्ठा batch_chunk *batch,
		       अचिन्हित पूर्णांक media_object_index)
अणु
	अचिन्हित पूर्णांक x_offset = (media_object_index % 16) * 64;
	अचिन्हित पूर्णांक y_offset = (media_object_index / 16) * 16;
	अचिन्हित पूर्णांक pkt = 6 + 3;
	u32 *cs;

	cs = batch_alloc_items(batch, 8, pkt);

	*cs++ = MEDIA_OBJECT | (pkt - 2);

	/* पूर्णांकerface descriptor offset */
	*cs++ = 0;

	/* without indirect data */
	*cs++ = 0;
	*cs++ = 0;

	/* scoreboard */
	*cs++ = 0;
	*cs++ = 0;

	/* अंतरभूत */
	*cs++ = y_offset << 16 | x_offset;
	*cs++ = 0;
	*cs++ = GT3_INLINE_DATA_DELAYS;

	batch_advance(batch, cs);
पूर्ण

अटल व्योम gen7_emit_pipeline_flush(काष्ठा batch_chunk *batch)
अणु
	u32 *cs = batch_alloc_items(batch, 0, 4);

	*cs++ = GFX_OP_PIPE_CONTROL(4);
	*cs++ = PIPE_CONTROL_RENDER_TARGET_CACHE_FLUSH |
		PIPE_CONTROL_DEPTH_CACHE_FLUSH |
		PIPE_CONTROL_DC_FLUSH_ENABLE |
		PIPE_CONTROL_CS_STALL;
	*cs++ = 0;
	*cs++ = 0;

	batch_advance(batch, cs);
पूर्ण

अटल व्योम gen7_emit_pipeline_invalidate(काष्ठा batch_chunk *batch)
अणु
	u32 *cs = batch_alloc_items(batch, 0, 10);

	/* ivb: Stall beक्रमe STATE_CACHE_INVALIDATE */
	*cs++ = GFX_OP_PIPE_CONTROL(5);
	*cs++ = PIPE_CONTROL_STALL_AT_SCOREBOARD |
		PIPE_CONTROL_CS_STALL;
	*cs++ = 0;
	*cs++ = 0;
	*cs++ = 0;

	*cs++ = GFX_OP_PIPE_CONTROL(5);
	*cs++ = PIPE_CONTROL_STATE_CACHE_INVALIDATE;
	*cs++ = 0;
	*cs++ = 0;
	*cs++ = 0;

	batch_advance(batch, cs);
पूर्ण

अटल व्योम emit_batch(काष्ठा i915_vma * स्थिर vma,
		       u32 *start,
		       स्थिर काष्ठा batch_vals *bv)
अणु
	काष्ठा drm_i915_निजी *i915 = vma->vm->i915;
	स्थिर अचिन्हित पूर्णांक desc_count = 1;
	स्थिर अचिन्हित पूर्णांक urb_size = 1;
	काष्ठा batch_chunk cmds, state;
	u32 descriptors;
	अचिन्हित पूर्णांक i;

	batch_init(&cmds, vma, start, 0, bv->state_start);
	batch_init(&state, vma, start, bv->state_start, SZ_4K);

	descriptors = gen7_fill_पूर्णांकerface_descriptor(&state, bv,
						     IS_HASWELL(i915) ?
						     &cb_kernel_hsw :
						     &cb_kernel_ivb,
						     desc_count);

	/* Reset inherited context रेजिस्टरs */
	gen7_emit_pipeline_flush(&cmds);
	gen7_emit_pipeline_invalidate(&cmds);
	batch_add(&cmds, MI_LOAD_REGISTER_IMM(2));
	batch_add(&cmds, i915_mmio_reg_offset(CACHE_MODE_0_GEN7));
	batch_add(&cmds, 0xffff0000 |
			((IS_IVB_GT1(i915) || IS_VALLEYVIEW(i915)) ?
			 HIZ_RAW_STALL_OPT_DISABLE :
			 0));
	batch_add(&cmds, i915_mmio_reg_offset(CACHE_MODE_1));
	batch_add(&cmds, 0xffff0000 | PIXEL_SUBSPAN_COLLECT_OPT_DISABLE);
	gen7_emit_pipeline_invalidate(&cmds);
	gen7_emit_pipeline_flush(&cmds);

	/* Switch to the media pipeline and our base address */
	gen7_emit_pipeline_invalidate(&cmds);
	batch_add(&cmds, PIPELINE_SELECT | PIPELINE_SELECT_MEDIA);
	batch_add(&cmds, MI_NOOP);
	gen7_emit_pipeline_invalidate(&cmds);

	gen7_emit_pipeline_flush(&cmds);
	gen7_emit_state_base_address(&cmds, descriptors);
	gen7_emit_pipeline_invalidate(&cmds);

	/* Set the clear-residual kernel state */
	gen7_emit_vfe_state(&cmds, bv, urb_size - 1, 0, 0);
	gen7_emit_पूर्णांकerface_descriptor_load(&cmds, descriptors, desc_count);

	/* Execute the kernel on all HW thपढ़ोs */
	क्रम (i = 0; i < num_primitives(bv); i++)
		gen7_emit_media_object(&cmds, i);

	batch_add(&cmds, MI_BATCH_BUFFER_END);
पूर्ण

पूर्णांक gen7_setup_clear_gpr_bb(काष्ठा पूर्णांकel_engine_cs * स्थिर engine,
			    काष्ठा i915_vma * स्थिर vma)
अणु
	काष्ठा batch_vals bv;
	u32 *batch;

	batch_get_शेषs(engine->i915, &bv);
	अगर (!vma)
		वापस bv.size;

	GEM_BUG_ON(vma->obj->base.size < bv.size);

	batch = i915_gem_object_pin_map(vma->obj, I915_MAP_WC);
	अगर (IS_ERR(batch))
		वापस PTR_ERR(batch);

	emit_batch(vma, स_रखो(batch, 0, bv.size), &bv);

	i915_gem_object_flush_map(vma->obj);
	__i915_gem_object_release_map(vma->obj);

	वापस 0;
पूर्ण
