<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#समावेश "gen2_engine_cs.h"
#समावेश "i915_drv.h"
#समावेश "intel_engine.h"
#समावेश "intel_gpu_commands.h"
#समावेश "intel_gt.h"
#समावेश "intel_gt_irq.h"
#समावेश "intel_ring.h"

पूर्णांक gen2_emit_flush(काष्ठा i915_request *rq, u32 mode)
अणु
	अचिन्हित पूर्णांक num_store_dw = 12;
	u32 cmd, *cs;

	cmd = MI_FLUSH;
	अगर (mode & EMIT_INVALIDATE)
		cmd |= MI_READ_FLUSH;

	cs = पूर्णांकel_ring_begin(rq, 2 + 4 * num_store_dw);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	*cs++ = cmd;
	जबतक (num_store_dw--) अणु
		*cs++ = MI_STORE_DWORD_INDEX;
		*cs++ = I915_GEM_HWS_SCRATCH * माप(u32);
		*cs++ = 0;
		*cs++ = MI_FLUSH | MI_NO_WRITE_FLUSH;
	पूर्ण
	*cs++ = cmd;

	पूर्णांकel_ring_advance(rq, cs);

	वापस 0;
पूर्ण

पूर्णांक gen4_emit_flush_rcs(काष्ठा i915_request *rq, u32 mode)
अणु
	u32 cmd, *cs;
	पूर्णांक i;

	/*
	 * पढ़ो/ग_लिखो caches:
	 *
	 * I915_GEM_DOMAIN_RENDER is always invalidated, but is
	 * only flushed अगर MI_NO_WRITE_FLUSH is unset.  On 965, it is
	 * also flushed at 2d versus 3d pipeline चयनes.
	 *
	 * पढ़ो-only caches:
	 *
	 * I915_GEM_DOMAIN_SAMPLER is flushed on pre-965 अगर
	 * MI_READ_FLUSH is set, and is always flushed on 965.
	 *
	 * I915_GEM_DOMAIN_COMMAND may not exist?
	 *
	 * I915_GEM_DOMAIN_INSTRUCTION, which exists on 965, is
	 * invalidated when MI_EXE_FLUSH is set.
	 *
	 * I915_GEM_DOMAIN_VERTEX, which exists on 965, is
	 * invalidated with every MI_FLUSH.
	 *
	 * TLBs:
	 *
	 * On 965, TLBs associated with I915_GEM_DOMAIN_COMMAND
	 * and I915_GEM_DOMAIN_CPU in are invalidated at PTE ग_लिखो and
	 * I915_GEM_DOMAIN_RENDER and I915_GEM_DOMAIN_SAMPLER
	 * are flushed at any MI_FLUSH.
	 */

	cmd = MI_FLUSH;
	अगर (mode & EMIT_INVALIDATE) अणु
		cmd |= MI_EXE_FLUSH;
		अगर (IS_G4X(rq->engine->i915) || IS_GEN(rq->engine->i915, 5))
			cmd |= MI_INVALIDATE_ISP;
	पूर्ण

	i = 2;
	अगर (mode & EMIT_INVALIDATE)
		i += 20;

	cs = पूर्णांकel_ring_begin(rq, i);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	*cs++ = cmd;

	/*
	 * A अक्रमom delay to let the CS invalidate take effect? Without this
	 * delay, the GPU relocation path fails as the CS करोes not see
	 * the updated contents. Just as important, अगर we apply the flushes
	 * to the EMIT_FLUSH branch (i.e. immediately after the relocation
	 * ग_लिखो and beक्रमe the invalidate on the next batch), the relocations
	 * still fail. This implies that is a delay following invalidation
	 * that is required to reset the caches as opposed to a delay to
	 * ensure the memory is written.
	 */
	अगर (mode & EMIT_INVALIDATE) अणु
		*cs++ = GFX_OP_PIPE_CONTROL(4) | PIPE_CONTROL_QW_WRITE;
		*cs++ = पूर्णांकel_gt_scratch_offset(rq->engine->gt,
						INTEL_GT_SCRATCH_FIELD_DEFAULT) |
			PIPE_CONTROL_GLOBAL_GTT;
		*cs++ = 0;
		*cs++ = 0;

		क्रम (i = 0; i < 12; i++)
			*cs++ = MI_FLUSH;

		*cs++ = GFX_OP_PIPE_CONTROL(4) | PIPE_CONTROL_QW_WRITE;
		*cs++ = पूर्णांकel_gt_scratch_offset(rq->engine->gt,
						INTEL_GT_SCRATCH_FIELD_DEFAULT) |
			PIPE_CONTROL_GLOBAL_GTT;
		*cs++ = 0;
		*cs++ = 0;
	पूर्ण

	*cs++ = cmd;

	पूर्णांकel_ring_advance(rq, cs);

	वापस 0;
पूर्ण

पूर्णांक gen4_emit_flush_vcs(काष्ठा i915_request *rq, u32 mode)
अणु
	u32 *cs;

	cs = पूर्णांकel_ring_begin(rq, 2);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	*cs++ = MI_FLUSH;
	*cs++ = MI_NOOP;
	पूर्णांकel_ring_advance(rq, cs);

	वापस 0;
पूर्ण

अटल u32 *__gen2_emit_bपढ़ोcrumb(काष्ठा i915_request *rq, u32 *cs,
				   पूर्णांक flush, पूर्णांक post)
अणु
	GEM_BUG_ON(i915_request_active_समयline(rq)->hwsp_ggtt != rq->engine->status_page.vma);
	GEM_BUG_ON(offset_in_page(rq->hwsp_seqno) != I915_GEM_HWS_SEQNO_ADDR);

	*cs++ = MI_FLUSH;

	जबतक (flush--) अणु
		*cs++ = MI_STORE_DWORD_INDEX;
		*cs++ = I915_GEM_HWS_SCRATCH * माप(u32);
		*cs++ = rq->fence.seqno;
	पूर्ण

	जबतक (post--) अणु
		*cs++ = MI_STORE_DWORD_INDEX;
		*cs++ = I915_GEM_HWS_SEQNO_ADDR;
		*cs++ = rq->fence.seqno;
	पूर्ण

	*cs++ = MI_USER_INTERRUPT;

	rq->tail = पूर्णांकel_ring_offset(rq, cs);
	निश्चित_ring_tail_valid(rq->ring, rq->tail);

	वापस cs;
पूर्ण

u32 *gen3_emit_bपढ़ोcrumb(काष्ठा i915_request *rq, u32 *cs)
अणु
	वापस __gen2_emit_bपढ़ोcrumb(rq, cs, 16, 8);
पूर्ण

u32 *gen5_emit_bपढ़ोcrumb(काष्ठा i915_request *rq, u32 *cs)
अणु
	वापस __gen2_emit_bपढ़ोcrumb(rq, cs, 8, 8);
पूर्ण

/* Just userspace ABI convention to limit the wa batch bo to a resonable size */
#घोषणा I830_BATCH_LIMIT SZ_256K
#घोषणा I830_TLB_ENTRIES (2)
#घोषणा I830_WA_SIZE max(I830_TLB_ENTRIES * SZ_4K, I830_BATCH_LIMIT)
पूर्णांक i830_emit_bb_start(काष्ठा i915_request *rq,
		       u64 offset, u32 len,
		       अचिन्हित पूर्णांक dispatch_flags)
अणु
	u32 *cs, cs_offset =
		पूर्णांकel_gt_scratch_offset(rq->engine->gt,
					INTEL_GT_SCRATCH_FIELD_DEFAULT);

	GEM_BUG_ON(rq->engine->gt->scratch->size < I830_WA_SIZE);

	cs = पूर्णांकel_ring_begin(rq, 6);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	/* Evict the invalid PTE TLBs */
	*cs++ = COLOR_BLT_CMD | BLT_WRITE_RGBA;
	*cs++ = BLT_DEPTH_32 | BLT_ROP_COLOR_COPY | 4096;
	*cs++ = I830_TLB_ENTRIES << 16 | 4; /* load each page */
	*cs++ = cs_offset;
	*cs++ = 0xdeadbeef;
	*cs++ = MI_NOOP;
	पूर्णांकel_ring_advance(rq, cs);

	अगर ((dispatch_flags & I915_DISPATCH_PINNED) == 0) अणु
		अगर (len > I830_BATCH_LIMIT)
			वापस -ENOSPC;

		cs = पूर्णांकel_ring_begin(rq, 6 + 2);
		अगर (IS_ERR(cs))
			वापस PTR_ERR(cs);

		/*
		 * Blit the batch (which has now all relocs applied) to the
		 * stable batch scratch bo area (so that the CS never
		 * stumbles over its tlb invalidation bug) ...
		 */
		*cs++ = SRC_COPY_BLT_CMD | BLT_WRITE_RGBA | (6 - 2);
		*cs++ = BLT_DEPTH_32 | BLT_ROP_SRC_COPY | 4096;
		*cs++ = DIV_ROUND_UP(len, 4096) << 16 | 4096;
		*cs++ = cs_offset;
		*cs++ = 4096;
		*cs++ = offset;

		*cs++ = MI_FLUSH;
		*cs++ = MI_NOOP;
		पूर्णांकel_ring_advance(rq, cs);

		/* ... and execute it. */
		offset = cs_offset;
	पूर्ण

	अगर (!(dispatch_flags & I915_DISPATCH_SECURE))
		offset |= MI_BATCH_NON_SECURE;

	cs = पूर्णांकel_ring_begin(rq, 2);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	*cs++ = MI_BATCH_BUFFER_START | MI_BATCH_GTT;
	*cs++ = offset;
	पूर्णांकel_ring_advance(rq, cs);

	वापस 0;
पूर्ण

पूर्णांक gen3_emit_bb_start(काष्ठा i915_request *rq,
		       u64 offset, u32 len,
		       अचिन्हित पूर्णांक dispatch_flags)
अणु
	u32 *cs;

	अगर (!(dispatch_flags & I915_DISPATCH_SECURE))
		offset |= MI_BATCH_NON_SECURE;

	cs = पूर्णांकel_ring_begin(rq, 2);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	*cs++ = MI_BATCH_BUFFER_START | MI_BATCH_GTT;
	*cs++ = offset;
	पूर्णांकel_ring_advance(rq, cs);

	वापस 0;
पूर्ण

पूर्णांक gen4_emit_bb_start(काष्ठा i915_request *rq,
		       u64 offset, u32 length,
		       अचिन्हित पूर्णांक dispatch_flags)
अणु
	u32 security;
	u32 *cs;

	security = MI_BATCH_NON_SECURE_I965;
	अगर (dispatch_flags & I915_DISPATCH_SECURE)
		security = 0;

	cs = पूर्णांकel_ring_begin(rq, 2);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	*cs++ = MI_BATCH_BUFFER_START | MI_BATCH_GTT | security;
	*cs++ = offset;
	पूर्णांकel_ring_advance(rq, cs);

	वापस 0;
पूर्ण

व्योम gen2_irq_enable(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा drm_i915_निजी *i915 = engine->i915;

	i915->irq_mask &= ~engine->irq_enable_mask;
	पूर्णांकel_uncore_ग_लिखो16(&i915->uncore, GEN2_IMR, i915->irq_mask);
	ENGINE_POSTING_READ16(engine, RING_IMR);
पूर्ण

व्योम gen2_irq_disable(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा drm_i915_निजी *i915 = engine->i915;

	i915->irq_mask |= engine->irq_enable_mask;
	पूर्णांकel_uncore_ग_लिखो16(&i915->uncore, GEN2_IMR, i915->irq_mask);
पूर्ण

व्योम gen3_irq_enable(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	engine->i915->irq_mask &= ~engine->irq_enable_mask;
	पूर्णांकel_uncore_ग_लिखो(engine->uncore, GEN2_IMR, engine->i915->irq_mask);
	पूर्णांकel_uncore_posting_पढ़ो_fw(engine->uncore, GEN2_IMR);
पूर्ण

व्योम gen3_irq_disable(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	engine->i915->irq_mask |= engine->irq_enable_mask;
	पूर्णांकel_uncore_ग_लिखो(engine->uncore, GEN2_IMR, engine->i915->irq_mask);
पूर्ण

व्योम gen5_irq_enable(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	gen5_gt_enable_irq(engine->gt, engine->irq_enable_mask);
पूर्ण

व्योम gen5_irq_disable(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	gen5_gt_disable_irq(engine->gt, engine->irq_enable_mask);
पूर्ण
