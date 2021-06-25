<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2014 Intel Corporation
 */

#अगर_अघोषित __GEN8_ENGINE_CS_H__
#घोषणा __GEN8_ENGINE_CS_H__

#समावेश <linux/माला.स>
#समावेश <linux/types.h>

#समावेश "i915_gem.h" /* GEM_BUG_ON */

#समावेश "intel_gpu_commands.h"

काष्ठा i915_request;

पूर्णांक gen8_emit_flush_rcs(काष्ठा i915_request *rq, u32 mode);
पूर्णांक gen11_emit_flush_rcs(काष्ठा i915_request *rq, u32 mode);
पूर्णांक gen12_emit_flush_rcs(काष्ठा i915_request *rq, u32 mode);

पूर्णांक gen8_emit_flush_xcs(काष्ठा i915_request *rq, u32 mode);
पूर्णांक gen12_emit_flush_xcs(काष्ठा i915_request *rq, u32 mode);

पूर्णांक gen8_emit_init_bपढ़ोcrumb(काष्ठा i915_request *rq);

पूर्णांक gen8_emit_bb_start_noarb(काष्ठा i915_request *rq,
			     u64 offset, u32 len,
			     स्थिर अचिन्हित पूर्णांक flags);
पूर्णांक gen8_emit_bb_start(काष्ठा i915_request *rq,
		       u64 offset, u32 len,
		       स्थिर अचिन्हित पूर्णांक flags);

u32 *gen8_emit_fini_bपढ़ोcrumb_xcs(काष्ठा i915_request *rq, u32 *cs);
u32 *gen12_emit_fini_bपढ़ोcrumb_xcs(काष्ठा i915_request *rq, u32 *cs);

u32 *gen8_emit_fini_bपढ़ोcrumb_rcs(काष्ठा i915_request *rq, u32 *cs);
u32 *gen11_emit_fini_bपढ़ोcrumb_rcs(काष्ठा i915_request *rq, u32 *cs);
u32 *gen12_emit_fini_bपढ़ोcrumb_rcs(काष्ठा i915_request *rq, u32 *cs);

अटल अंतरभूत u32 *
__gen8_emit_pipe_control(u32 *batch, u32 flags0, u32 flags1, u32 offset)
अणु
	स_रखो(batch, 0, 6 * माप(u32));

	batch[0] = GFX_OP_PIPE_CONTROL(6) | flags0;
	batch[1] = flags1;
	batch[2] = offset;

	वापस batch + 6;
पूर्ण

अटल अंतरभूत u32 *gen8_emit_pipe_control(u32 *batch, u32 flags, u32 offset)
अणु
	वापस __gen8_emit_pipe_control(batch, 0, flags, offset);
पूर्ण

अटल अंतरभूत u32 *gen12_emit_pipe_control(u32 *batch, u32 flags0, u32 flags1, u32 offset)
अणु
	वापस __gen8_emit_pipe_control(batch, flags0, flags1, offset);
पूर्ण

अटल अंतरभूत u32 *
__gen8_emit_ग_लिखो_rcs(u32 *cs, u32 value, u32 offset, u32 flags0, u32 flags1)
अणु
	*cs++ = GFX_OP_PIPE_CONTROL(6) | flags0;
	*cs++ = flags1 | PIPE_CONTROL_QW_WRITE;
	*cs++ = offset;
	*cs++ = 0;
	*cs++ = value;
	*cs++ = 0; /* We're thrashing one extra dword. */

	वापस cs;
पूर्ण

अटल अंतरभूत u32*
gen8_emit_ggtt_ग_लिखो_rcs(u32 *cs, u32 value, u32 gtt_offset, u32 flags)
अणु
	/* We're using qword ग_लिखो, offset should be aligned to 8 bytes. */
	GEM_BUG_ON(!IS_ALIGNED(gtt_offset, 8));

	वापस __gen8_emit_ग_लिखो_rcs(cs,
				     value,
				     gtt_offset,
				     0,
				     flags | PIPE_CONTROL_GLOBAL_GTT_IVB);
पूर्ण

अटल अंतरभूत u32*
gen12_emit_ggtt_ग_लिखो_rcs(u32 *cs, u32 value, u32 gtt_offset, u32 flags0, u32 flags1)
अणु
	/* We're using qword ग_लिखो, offset should be aligned to 8 bytes. */
	GEM_BUG_ON(!IS_ALIGNED(gtt_offset, 8));

	वापस __gen8_emit_ग_लिखो_rcs(cs,
				     value,
				     gtt_offset,
				     flags0,
				     flags1 | PIPE_CONTROL_GLOBAL_GTT_IVB);
पूर्ण

अटल अंतरभूत u32 *
__gen8_emit_flush_dw(u32 *cs, u32 value, u32 gtt_offset, u32 flags)
अणु
	*cs++ = (MI_FLUSH_DW + 1) | flags;
	*cs++ = gtt_offset;
	*cs++ = 0;
	*cs++ = value;

	वापस cs;
पूर्ण

अटल अंतरभूत u32 *
gen8_emit_ggtt_ग_लिखो(u32 *cs, u32 value, u32 gtt_offset, u32 flags)
अणु
	/* w/a: bit 5 needs to be zero क्रम MI_FLUSH_DW address. */
	GEM_BUG_ON(gtt_offset & (1 << 5));
	/* Offset should be aligned to 8 bytes क्रम both (QW/DW) ग_लिखो types */
	GEM_BUG_ON(!IS_ALIGNED(gtt_offset, 8));

	वापस __gen8_emit_flush_dw(cs,
				    value,
				    gtt_offset | MI_FLUSH_DW_USE_GTT,
				    flags | MI_FLUSH_DW_OP_STOREDW);
पूर्ण

#पूर्ण_अगर /* __GEN8_ENGINE_CS_H__ */
