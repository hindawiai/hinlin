<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#समावेश "gen6_engine_cs.h"
#समावेश "intel_engine.h"
#समावेश "intel_gpu_commands.h"
#समावेश "intel_gt.h"
#समावेश "intel_gt_irq.h"
#समावेश "intel_gt_pm_irq.h"
#समावेश "intel_ring.h"

#घोषणा HWS_SCRATCH_ADDR	(I915_GEM_HWS_SCRATCH * माप(u32))

/*
 * Emits a PIPE_CONTROL with a non-zero post-sync operation, क्रम
 * implementing two workarounds on gen6.  From section 1.4.7.1
 * "PIPE_CONTROL" of the Sandy Bridge PRM volume 2 part 1:
 *
 * [DevSNB-C+अणुW/Aपूर्ण] Beक्रमe any depth stall flush (including those
 * produced by non-pipelined state commands), software needs to first
 * send a PIPE_CONTROL with no bits set except Post-Sync Operation !=
 * 0.
 *
 * [Dev-SNBअणुW/Aपूर्ण]: Beक्रमe a PIPE_CONTROL with Write Cache Flush Enable
 * =1, a PIPE_CONTROL with any non-zero post-sync-op is required.
 *
 * And the workaround क्रम these two requires this workaround first:
 *
 * [Dev-SNBअणुW/Aपूर्ण]: Pipe-control with CS-stall bit set must be sent
 * BEFORE the pipe-control with a post-sync op and no ग_लिखो-cache
 * flushes.
 *
 * And this last workaround is tricky because of the requirements on
 * that bit.  From section 1.4.7.2.3 "Stall" of the Sandy Bridge PRM
 * volume 2 part 1:
 *
 *     "1 of the following must also be set:
 *      - Render Target Cache Flush Enable ([12] of DW1)
 *      - Depth Cache Flush Enable ([0] of DW1)
 *      - Stall at Pixel Scoreboard ([1] of DW1)
 *      - Depth Stall ([13] of DW1)
 *      - Post-Sync Operation ([13] of DW1)
 *      - Notअगरy Enable ([8] of DW1)"
 *
 * The cache flushes require the workaround flush that triggered this
 * one, so we can't use it.  Depth stall would trigger the same.
 * Post-sync nonzero is what triggered this second workaround, so we
 * can't use that one either.  Notify enable is IRQs, which aren't
 * really our business.  That leaves only stall at scoreboard.
 */
अटल पूर्णांक
gen6_emit_post_sync_nonzero_flush(काष्ठा i915_request *rq)
अणु
	u32 scratch_addr =
		पूर्णांकel_gt_scratch_offset(rq->engine->gt,
					INTEL_GT_SCRATCH_FIELD_RENDER_FLUSH);
	u32 *cs;

	cs = पूर्णांकel_ring_begin(rq, 6);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	*cs++ = GFX_OP_PIPE_CONTROL(5);
	*cs++ = PIPE_CONTROL_CS_STALL | PIPE_CONTROL_STALL_AT_SCOREBOARD;
	*cs++ = scratch_addr | PIPE_CONTROL_GLOBAL_GTT;
	*cs++ = 0; /* low dword */
	*cs++ = 0; /* high dword */
	*cs++ = MI_NOOP;
	पूर्णांकel_ring_advance(rq, cs);

	cs = पूर्णांकel_ring_begin(rq, 6);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	*cs++ = GFX_OP_PIPE_CONTROL(5);
	*cs++ = PIPE_CONTROL_QW_WRITE;
	*cs++ = scratch_addr | PIPE_CONTROL_GLOBAL_GTT;
	*cs++ = 0;
	*cs++ = 0;
	*cs++ = MI_NOOP;
	पूर्णांकel_ring_advance(rq, cs);

	वापस 0;
पूर्ण

पूर्णांक gen6_emit_flush_rcs(काष्ठा i915_request *rq, u32 mode)
अणु
	u32 scratch_addr =
		पूर्णांकel_gt_scratch_offset(rq->engine->gt,
					INTEL_GT_SCRATCH_FIELD_RENDER_FLUSH);
	u32 *cs, flags = 0;
	पूर्णांक ret;

	/* Force SNB workarounds क्रम PIPE_CONTROL flushes */
	ret = gen6_emit_post_sync_nonzero_flush(rq);
	अगर (ret)
		वापस ret;

	/*
	 * Just flush everything.  Experiments have shown that reducing the
	 * number of bits based on the ग_लिखो करोमुख्यs has little perक्रमmance
	 * impact. And when rearranging requests, the order of flushes is
	 * unknown.
	 */
	अगर (mode & EMIT_FLUSH) अणु
		flags |= PIPE_CONTROL_RENDER_TARGET_CACHE_FLUSH;
		flags |= PIPE_CONTROL_DEPTH_CACHE_FLUSH;
		/*
		 * Ensure that any following seqno ग_लिखोs only happen
		 * when the render cache is indeed flushed.
		 */
		flags |= PIPE_CONTROL_CS_STALL;
	पूर्ण
	अगर (mode & EMIT_INVALIDATE) अणु
		flags |= PIPE_CONTROL_TLB_INVALIDATE;
		flags |= PIPE_CONTROL_INSTRUCTION_CACHE_INVALIDATE;
		flags |= PIPE_CONTROL_TEXTURE_CACHE_INVALIDATE;
		flags |= PIPE_CONTROL_VF_CACHE_INVALIDATE;
		flags |= PIPE_CONTROL_CONST_CACHE_INVALIDATE;
		flags |= PIPE_CONTROL_STATE_CACHE_INVALIDATE;
		/*
		 * TLB invalidate requires a post-sync ग_लिखो.
		 */
		flags |= PIPE_CONTROL_QW_WRITE | PIPE_CONTROL_CS_STALL;
	पूर्ण

	cs = पूर्णांकel_ring_begin(rq, 4);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	*cs++ = GFX_OP_PIPE_CONTROL(4);
	*cs++ = flags;
	*cs++ = scratch_addr | PIPE_CONTROL_GLOBAL_GTT;
	*cs++ = 0;
	पूर्णांकel_ring_advance(rq, cs);

	वापस 0;
पूर्ण

u32 *gen6_emit_bपढ़ोcrumb_rcs(काष्ठा i915_request *rq, u32 *cs)
अणु
	/* First we करो the gen6_emit_post_sync_nonzero_flush w/a */
	*cs++ = GFX_OP_PIPE_CONTROL(4);
	*cs++ = PIPE_CONTROL_CS_STALL | PIPE_CONTROL_STALL_AT_SCOREBOARD;
	*cs++ = 0;
	*cs++ = 0;

	*cs++ = GFX_OP_PIPE_CONTROL(4);
	*cs++ = PIPE_CONTROL_QW_WRITE;
	*cs++ = पूर्णांकel_gt_scratch_offset(rq->engine->gt,
					INTEL_GT_SCRATCH_FIELD_DEFAULT) |
		PIPE_CONTROL_GLOBAL_GTT;
	*cs++ = 0;

	/* Finally we can flush and with it emit the bपढ़ोcrumb */
	*cs++ = GFX_OP_PIPE_CONTROL(4);
	*cs++ = (PIPE_CONTROL_RENDER_TARGET_CACHE_FLUSH |
		 PIPE_CONTROL_DEPTH_CACHE_FLUSH |
		 PIPE_CONTROL_DC_FLUSH_ENABLE |
		 PIPE_CONTROL_QW_WRITE |
		 PIPE_CONTROL_CS_STALL);
	*cs++ = i915_request_active_seqno(rq) |
		PIPE_CONTROL_GLOBAL_GTT;
	*cs++ = rq->fence.seqno;

	*cs++ = MI_USER_INTERRUPT;
	*cs++ = MI_NOOP;

	rq->tail = पूर्णांकel_ring_offset(rq, cs);
	निश्चित_ring_tail_valid(rq->ring, rq->tail);

	वापस cs;
पूर्ण

अटल पूर्णांक mi_flush_dw(काष्ठा i915_request *rq, u32 flags)
अणु
	u32 cmd, *cs;

	cs = पूर्णांकel_ring_begin(rq, 4);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	cmd = MI_FLUSH_DW;

	/*
	 * We always require a command barrier so that subsequent
	 * commands, such as bपढ़ोcrumb पूर्णांकerrupts, are strictly ordered
	 * wrt the contents of the ग_लिखो cache being flushed to memory
	 * (and thus being coherent from the CPU).
	 */
	cmd |= MI_FLUSH_DW_STORE_INDEX | MI_FLUSH_DW_OP_STOREDW;

	/*
	 * Bspec vol 1c.3 - blitter engine command streamer:
	 * "If ENABLED, all TLBs will be invalidated once the flush
	 * operation is complete. This bit is only valid when the
	 * Post-Sync Operation field is a value of 1h or 3h."
	 */
	cmd |= flags;

	*cs++ = cmd;
	*cs++ = HWS_SCRATCH_ADDR | MI_FLUSH_DW_USE_GTT;
	*cs++ = 0;
	*cs++ = MI_NOOP;

	पूर्णांकel_ring_advance(rq, cs);

	वापस 0;
पूर्ण

अटल पूर्णांक gen6_flush_dw(काष्ठा i915_request *rq, u32 mode, u32 invflags)
अणु
	वापस mi_flush_dw(rq, mode & EMIT_INVALIDATE ? invflags : 0);
पूर्ण

पूर्णांक gen6_emit_flush_xcs(काष्ठा i915_request *rq, u32 mode)
अणु
	वापस gen6_flush_dw(rq, mode, MI_INVALIDATE_TLB);
पूर्ण

पूर्णांक gen6_emit_flush_vcs(काष्ठा i915_request *rq, u32 mode)
अणु
	वापस gen6_flush_dw(rq, mode, MI_INVALIDATE_TLB | MI_INVALIDATE_BSD);
पूर्ण

पूर्णांक gen6_emit_bb_start(काष्ठा i915_request *rq,
		       u64 offset, u32 len,
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

	cs = __gen6_emit_bb_start(cs, offset, security);
	पूर्णांकel_ring_advance(rq, cs);

	वापस 0;
पूर्ण

पूर्णांक
hsw_emit_bb_start(काष्ठा i915_request *rq,
		  u64 offset, u32 len,
		  अचिन्हित पूर्णांक dispatch_flags)
अणु
	u32 security;
	u32 *cs;

	security = MI_BATCH_PPGTT_HSW | MI_BATCH_NON_SECURE_HSW;
	अगर (dispatch_flags & I915_DISPATCH_SECURE)
		security = 0;

	cs = पूर्णांकel_ring_begin(rq, 2);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	cs = __gen6_emit_bb_start(cs, offset, security);
	पूर्णांकel_ring_advance(rq, cs);

	वापस 0;
पूर्ण

अटल पूर्णांक gen7_stall_cs(काष्ठा i915_request *rq)
अणु
	u32 *cs;

	cs = पूर्णांकel_ring_begin(rq, 4);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	*cs++ = GFX_OP_PIPE_CONTROL(4);
	*cs++ = PIPE_CONTROL_CS_STALL | PIPE_CONTROL_STALL_AT_SCOREBOARD;
	*cs++ = 0;
	*cs++ = 0;
	पूर्णांकel_ring_advance(rq, cs);

	वापस 0;
पूर्ण

पूर्णांक gen7_emit_flush_rcs(काष्ठा i915_request *rq, u32 mode)
अणु
	u32 scratch_addr =
		पूर्णांकel_gt_scratch_offset(rq->engine->gt,
					INTEL_GT_SCRATCH_FIELD_RENDER_FLUSH);
	u32 *cs, flags = 0;

	/*
	 * Ensure that any following seqno ग_लिखोs only happen when the render
	 * cache is indeed flushed.
	 *
	 * Workaround: 4th PIPE_CONTROL command (except the ones with only
	 * पढ़ो-cache invalidate bits set) must have the CS_STALL bit set. We
	 * करोn't try to be clever and just set it unconditionally.
	 */
	flags |= PIPE_CONTROL_CS_STALL;

	/*
	 * CS_STALL suggests at least a post-sync ग_लिखो.
	 */
	flags |= PIPE_CONTROL_QW_WRITE;
	flags |= PIPE_CONTROL_GLOBAL_GTT_IVB;

	/*
	 * Just flush everything.  Experiments have shown that reducing the
	 * number of bits based on the ग_लिखो करोमुख्यs has little perक्रमmance
	 * impact.
	 */
	अगर (mode & EMIT_FLUSH) अणु
		flags |= PIPE_CONTROL_RENDER_TARGET_CACHE_FLUSH;
		flags |= PIPE_CONTROL_DEPTH_CACHE_FLUSH;
		flags |= PIPE_CONTROL_DC_FLUSH_ENABLE;
		flags |= PIPE_CONTROL_FLUSH_ENABLE;
	पूर्ण
	अगर (mode & EMIT_INVALIDATE) अणु
		flags |= PIPE_CONTROL_TLB_INVALIDATE;
		flags |= PIPE_CONTROL_INSTRUCTION_CACHE_INVALIDATE;
		flags |= PIPE_CONTROL_TEXTURE_CACHE_INVALIDATE;
		flags |= PIPE_CONTROL_VF_CACHE_INVALIDATE;
		flags |= PIPE_CONTROL_CONST_CACHE_INVALIDATE;
		flags |= PIPE_CONTROL_STATE_CACHE_INVALIDATE;
		flags |= PIPE_CONTROL_MEDIA_STATE_CLEAR;

		/*
		 * Workaround: we must issue a pipe_control with CS-stall bit
		 * set beक्रमe a pipe_control command that has the state cache
		 * invalidate bit set.
		 */
		gen7_stall_cs(rq);
	पूर्ण

	cs = पूर्णांकel_ring_begin(rq, 4);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	*cs++ = GFX_OP_PIPE_CONTROL(4);
	*cs++ = flags;
	*cs++ = scratch_addr;
	*cs++ = 0;
	पूर्णांकel_ring_advance(rq, cs);

	वापस 0;
पूर्ण

u32 *gen7_emit_bपढ़ोcrumb_rcs(काष्ठा i915_request *rq, u32 *cs)
अणु
	*cs++ = GFX_OP_PIPE_CONTROL(4);
	*cs++ = (PIPE_CONTROL_RENDER_TARGET_CACHE_FLUSH |
		 PIPE_CONTROL_DEPTH_CACHE_FLUSH |
		 PIPE_CONTROL_DC_FLUSH_ENABLE |
		 PIPE_CONTROL_FLUSH_ENABLE |
		 PIPE_CONTROL_QW_WRITE |
		 PIPE_CONTROL_GLOBAL_GTT_IVB |
		 PIPE_CONTROL_CS_STALL);
	*cs++ = i915_request_active_seqno(rq);
	*cs++ = rq->fence.seqno;

	*cs++ = MI_USER_INTERRUPT;
	*cs++ = MI_NOOP;

	rq->tail = पूर्णांकel_ring_offset(rq, cs);
	निश्चित_ring_tail_valid(rq->ring, rq->tail);

	वापस cs;
पूर्ण

u32 *gen6_emit_bपढ़ोcrumb_xcs(काष्ठा i915_request *rq, u32 *cs)
अणु
	GEM_BUG_ON(i915_request_active_समयline(rq)->hwsp_ggtt != rq->engine->status_page.vma);
	GEM_BUG_ON(offset_in_page(rq->hwsp_seqno) != I915_GEM_HWS_SEQNO_ADDR);

	*cs++ = MI_FLUSH_DW | MI_FLUSH_DW_OP_STOREDW | MI_FLUSH_DW_STORE_INDEX;
	*cs++ = I915_GEM_HWS_SEQNO_ADDR | MI_FLUSH_DW_USE_GTT;
	*cs++ = rq->fence.seqno;

	*cs++ = MI_USER_INTERRUPT;

	rq->tail = पूर्णांकel_ring_offset(rq, cs);
	निश्चित_ring_tail_valid(rq->ring, rq->tail);

	वापस cs;
पूर्ण

#घोषणा GEN7_XCS_WA 32
u32 *gen7_emit_bपढ़ोcrumb_xcs(काष्ठा i915_request *rq, u32 *cs)
अणु
	पूर्णांक i;

	GEM_BUG_ON(i915_request_active_समयline(rq)->hwsp_ggtt != rq->engine->status_page.vma);
	GEM_BUG_ON(offset_in_page(rq->hwsp_seqno) != I915_GEM_HWS_SEQNO_ADDR);

	*cs++ = MI_FLUSH_DW | MI_INVALIDATE_TLB |
		MI_FLUSH_DW_OP_STOREDW | MI_FLUSH_DW_STORE_INDEX;
	*cs++ = I915_GEM_HWS_SEQNO_ADDR | MI_FLUSH_DW_USE_GTT;
	*cs++ = rq->fence.seqno;

	क्रम (i = 0; i < GEN7_XCS_WA; i++) अणु
		*cs++ = MI_STORE_DWORD_INDEX;
		*cs++ = I915_GEM_HWS_SEQNO_ADDR;
		*cs++ = rq->fence.seqno;
	पूर्ण

	*cs++ = MI_FLUSH_DW;
	*cs++ = 0;
	*cs++ = 0;

	*cs++ = MI_USER_INTERRUPT;
	*cs++ = MI_NOOP;

	rq->tail = पूर्णांकel_ring_offset(rq, cs);
	निश्चित_ring_tail_valid(rq->ring, rq->tail);

	वापस cs;
पूर्ण
#अघोषित GEN7_XCS_WA

व्योम gen6_irq_enable(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	ENGINE_WRITE(engine, RING_IMR,
		     ~(engine->irq_enable_mask | engine->irq_keep_mask));

	/* Flush/delay to ensure the RING_IMR is active beक्रमe the GT IMR */
	ENGINE_POSTING_READ(engine, RING_IMR);

	gen5_gt_enable_irq(engine->gt, engine->irq_enable_mask);
पूर्ण

व्योम gen6_irq_disable(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	ENGINE_WRITE(engine, RING_IMR, ~engine->irq_keep_mask);
	gen5_gt_disable_irq(engine->gt, engine->irq_enable_mask);
पूर्ण

व्योम hsw_irq_enable_vecs(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	ENGINE_WRITE(engine, RING_IMR, ~engine->irq_enable_mask);

	/* Flush/delay to ensure the RING_IMR is active beक्रमe the GT IMR */
	ENGINE_POSTING_READ(engine, RING_IMR);

	gen6_gt_pm_unmask_irq(engine->gt, engine->irq_enable_mask);
पूर्ण

व्योम hsw_irq_disable_vecs(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	ENGINE_WRITE(engine, RING_IMR, ~0);
	gen6_gt_pm_mask_irq(engine->gt, engine->irq_enable_mask);
पूर्ण
