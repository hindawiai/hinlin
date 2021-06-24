<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2014 Intel Corporation
 */

#समावेश "gen8_engine_cs.h"
#समावेश "i915_drv.h"
#समावेश "intel_lrc.h"
#समावेश "intel_gpu_commands.h"
#समावेश "intel_ring.h"

पूर्णांक gen8_emit_flush_rcs(काष्ठा i915_request *rq, u32 mode)
अणु
	bool vf_flush_wa = false, dc_flush_wa = false;
	u32 *cs, flags = 0;
	पूर्णांक len;

	flags |= PIPE_CONTROL_CS_STALL;

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
		flags |= PIPE_CONTROL_QW_WRITE;
		flags |= PIPE_CONTROL_STORE_DATA_INDEX;

		/*
		 * On GEN9: beक्रमe VF_CACHE_INVALIDATE we need to emit a शून्य
		 * pipe control.
		 */
		अगर (IS_GEN(rq->engine->i915, 9))
			vf_flush_wa = true;

		/* WaForGAMHang:kbl */
		अगर (IS_KBL_GT_STEP(rq->engine->i915, 0, STEP_B0))
			dc_flush_wa = true;
	पूर्ण

	len = 6;

	अगर (vf_flush_wa)
		len += 6;

	अगर (dc_flush_wa)
		len += 12;

	cs = पूर्णांकel_ring_begin(rq, len);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	अगर (vf_flush_wa)
		cs = gen8_emit_pipe_control(cs, 0, 0);

	अगर (dc_flush_wa)
		cs = gen8_emit_pipe_control(cs, PIPE_CONTROL_DC_FLUSH_ENABLE,
					    0);

	cs = gen8_emit_pipe_control(cs, flags, LRC_PPHWSP_SCRATCH_ADDR);

	अगर (dc_flush_wa)
		cs = gen8_emit_pipe_control(cs, PIPE_CONTROL_CS_STALL, 0);

	पूर्णांकel_ring_advance(rq, cs);

	वापस 0;
पूर्ण

पूर्णांक gen8_emit_flush_xcs(काष्ठा i915_request *rq, u32 mode)
अणु
	u32 cmd, *cs;

	cs = पूर्णांकel_ring_begin(rq, 4);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	cmd = MI_FLUSH_DW + 1;

	/*
	 * We always require a command barrier so that subsequent
	 * commands, such as bपढ़ोcrumb पूर्णांकerrupts, are strictly ordered
	 * wrt the contents of the ग_लिखो cache being flushed to memory
	 * (and thus being coherent from the CPU).
	 */
	cmd |= MI_FLUSH_DW_STORE_INDEX | MI_FLUSH_DW_OP_STOREDW;

	अगर (mode & EMIT_INVALIDATE) अणु
		cmd |= MI_INVALIDATE_TLB;
		अगर (rq->engine->class == VIDEO_DECODE_CLASS)
			cmd |= MI_INVALIDATE_BSD;
	पूर्ण

	*cs++ = cmd;
	*cs++ = LRC_PPHWSP_SCRATCH_ADDR;
	*cs++ = 0; /* upper addr */
	*cs++ = 0; /* value */
	पूर्णांकel_ring_advance(rq, cs);

	वापस 0;
पूर्ण

पूर्णांक gen11_emit_flush_rcs(काष्ठा i915_request *rq, u32 mode)
अणु
	अगर (mode & EMIT_FLUSH) अणु
		u32 *cs;
		u32 flags = 0;

		flags |= PIPE_CONTROL_CS_STALL;

		flags |= PIPE_CONTROL_TILE_CACHE_FLUSH;
		flags |= PIPE_CONTROL_RENDER_TARGET_CACHE_FLUSH;
		flags |= PIPE_CONTROL_DEPTH_CACHE_FLUSH;
		flags |= PIPE_CONTROL_DC_FLUSH_ENABLE;
		flags |= PIPE_CONTROL_FLUSH_ENABLE;
		flags |= PIPE_CONTROL_QW_WRITE;
		flags |= PIPE_CONTROL_STORE_DATA_INDEX;

		cs = पूर्णांकel_ring_begin(rq, 6);
		अगर (IS_ERR(cs))
			वापस PTR_ERR(cs);

		cs = gen8_emit_pipe_control(cs, flags, LRC_PPHWSP_SCRATCH_ADDR);
		पूर्णांकel_ring_advance(rq, cs);
	पूर्ण

	अगर (mode & EMIT_INVALIDATE) अणु
		u32 *cs;
		u32 flags = 0;

		flags |= PIPE_CONTROL_CS_STALL;

		flags |= PIPE_CONTROL_COMMAND_CACHE_INVALIDATE;
		flags |= PIPE_CONTROL_TLB_INVALIDATE;
		flags |= PIPE_CONTROL_INSTRUCTION_CACHE_INVALIDATE;
		flags |= PIPE_CONTROL_TEXTURE_CACHE_INVALIDATE;
		flags |= PIPE_CONTROL_VF_CACHE_INVALIDATE;
		flags |= PIPE_CONTROL_CONST_CACHE_INVALIDATE;
		flags |= PIPE_CONTROL_STATE_CACHE_INVALIDATE;
		flags |= PIPE_CONTROL_QW_WRITE;
		flags |= PIPE_CONTROL_STORE_DATA_INDEX;

		cs = पूर्णांकel_ring_begin(rq, 6);
		अगर (IS_ERR(cs))
			वापस PTR_ERR(cs);

		cs = gen8_emit_pipe_control(cs, flags, LRC_PPHWSP_SCRATCH_ADDR);
		पूर्णांकel_ring_advance(rq, cs);
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 preparser_disable(bool state)
अणु
	वापस MI_ARB_CHECK | 1 << 8 | state;
पूर्ण

अटल i915_reg_t aux_inv_reg(स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	अटल स्थिर i915_reg_t vd[] = अणु
		GEN12_VD0_AUX_NV,
		GEN12_VD1_AUX_NV,
		GEN12_VD2_AUX_NV,
		GEN12_VD3_AUX_NV,
	पूर्ण;

	अटल स्थिर i915_reg_t ve[] = अणु
		GEN12_VE0_AUX_NV,
		GEN12_VE1_AUX_NV,
	पूर्ण;

	अगर (engine->class == VIDEO_DECODE_CLASS)
		वापस vd[engine->instance];

	अगर (engine->class == VIDEO_ENHANCEMENT_CLASS)
		वापस ve[engine->instance];

	GEM_BUG_ON("unknown aux_inv reg\n");
	वापस INVALID_MMIO_REG;
पूर्ण

अटल u32 *gen12_emit_aux_table_inv(स्थिर i915_reg_t inv_reg, u32 *cs)
अणु
	*cs++ = MI_LOAD_REGISTER_IMM(1);
	*cs++ = i915_mmio_reg_offset(inv_reg);
	*cs++ = AUX_INV;
	*cs++ = MI_NOOP;

	वापस cs;
पूर्ण

पूर्णांक gen12_emit_flush_rcs(काष्ठा i915_request *rq, u32 mode)
अणु
	अगर (mode & EMIT_FLUSH) अणु
		u32 flags = 0;
		u32 *cs;

		flags |= PIPE_CONTROL_TILE_CACHE_FLUSH;
		flags |= PIPE_CONTROL_FLUSH_L3;
		flags |= PIPE_CONTROL_RENDER_TARGET_CACHE_FLUSH;
		flags |= PIPE_CONTROL_DEPTH_CACHE_FLUSH;
		/* Wa_1409600907:tgl */
		flags |= PIPE_CONTROL_DEPTH_STALL;
		flags |= PIPE_CONTROL_DC_FLUSH_ENABLE;
		flags |= PIPE_CONTROL_FLUSH_ENABLE;

		flags |= PIPE_CONTROL_STORE_DATA_INDEX;
		flags |= PIPE_CONTROL_QW_WRITE;

		flags |= PIPE_CONTROL_CS_STALL;

		cs = पूर्णांकel_ring_begin(rq, 6);
		अगर (IS_ERR(cs))
			वापस PTR_ERR(cs);

		cs = gen12_emit_pipe_control(cs,
					     PIPE_CONTROL0_HDC_PIPELINE_FLUSH,
					     flags, LRC_PPHWSP_SCRATCH_ADDR);
		पूर्णांकel_ring_advance(rq, cs);
	पूर्ण

	अगर (mode & EMIT_INVALIDATE) अणु
		u32 flags = 0;
		u32 *cs;

		flags |= PIPE_CONTROL_COMMAND_CACHE_INVALIDATE;
		flags |= PIPE_CONTROL_TLB_INVALIDATE;
		flags |= PIPE_CONTROL_INSTRUCTION_CACHE_INVALIDATE;
		flags |= PIPE_CONTROL_TEXTURE_CACHE_INVALIDATE;
		flags |= PIPE_CONTROL_VF_CACHE_INVALIDATE;
		flags |= PIPE_CONTROL_CONST_CACHE_INVALIDATE;
		flags |= PIPE_CONTROL_STATE_CACHE_INVALIDATE;

		flags |= PIPE_CONTROL_STORE_DATA_INDEX;
		flags |= PIPE_CONTROL_QW_WRITE;

		flags |= PIPE_CONTROL_CS_STALL;

		cs = पूर्णांकel_ring_begin(rq, 8 + 4);
		अगर (IS_ERR(cs))
			वापस PTR_ERR(cs);

		/*
		 * Prevent the pre-parser from skipping past the TLB
		 * invalidate and loading a stale page क्रम the batch
		 * buffer / request payload.
		 */
		*cs++ = preparser_disable(true);

		cs = gen8_emit_pipe_control(cs, flags, LRC_PPHWSP_SCRATCH_ADDR);

		/* hsdes: 1809175790 */
		cs = gen12_emit_aux_table_inv(GEN12_GFX_CCS_AUX_NV, cs);

		*cs++ = preparser_disable(false);
		पूर्णांकel_ring_advance(rq, cs);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक gen12_emit_flush_xcs(काष्ठा i915_request *rq, u32 mode)
अणु
	पूर्णांकel_engine_mask_t aux_inv = 0;
	u32 cmd, *cs;

	cmd = 4;
	अगर (mode & EMIT_INVALIDATE)
		cmd += 2;
	अगर (mode & EMIT_INVALIDATE)
		aux_inv = rq->engine->mask & ~BIT(BCS0);
	अगर (aux_inv)
		cmd += 2 * hweight8(aux_inv) + 2;

	cs = पूर्णांकel_ring_begin(rq, cmd);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	अगर (mode & EMIT_INVALIDATE)
		*cs++ = preparser_disable(true);

	cmd = MI_FLUSH_DW + 1;

	/*
	 * We always require a command barrier so that subsequent
	 * commands, such as bपढ़ोcrumb पूर्णांकerrupts, are strictly ordered
	 * wrt the contents of the ग_लिखो cache being flushed to memory
	 * (and thus being coherent from the CPU).
	 */
	cmd |= MI_FLUSH_DW_STORE_INDEX | MI_FLUSH_DW_OP_STOREDW;

	अगर (mode & EMIT_INVALIDATE) अणु
		cmd |= MI_INVALIDATE_TLB;
		अगर (rq->engine->class == VIDEO_DECODE_CLASS)
			cmd |= MI_INVALIDATE_BSD;
	पूर्ण

	*cs++ = cmd;
	*cs++ = LRC_PPHWSP_SCRATCH_ADDR;
	*cs++ = 0; /* upper addr */
	*cs++ = 0; /* value */

	अगर (aux_inv) अणु /* hsdes: 1809175790 */
		काष्ठा पूर्णांकel_engine_cs *engine;
		अचिन्हित पूर्णांक पंचांगp;

		*cs++ = MI_LOAD_REGISTER_IMM(hweight8(aux_inv));
		क्रम_each_engine_masked(engine, rq->engine->gt,
				       aux_inv, पंचांगp) अणु
			*cs++ = i915_mmio_reg_offset(aux_inv_reg(engine));
			*cs++ = AUX_INV;
		पूर्ण
		*cs++ = MI_NOOP;
	पूर्ण

	अगर (mode & EMIT_INVALIDATE)
		*cs++ = preparser_disable(false);

	पूर्णांकel_ring_advance(rq, cs);

	वापस 0;
पूर्ण

अटल u32 preempt_address(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	वापस (i915_ggtt_offset(engine->status_page.vma) +
		I915_GEM_HWS_PREEMPT_ADDR);
पूर्ण

अटल u32 hwsp_offset(स्थिर काष्ठा i915_request *rq)
अणु
	स्थिर काष्ठा पूर्णांकel_समयline *tl;

	/* Beक्रमe the request is executed, the समयline is fixed */
	tl = rcu_dereference_रक्षित(rq->समयline,
				       !i915_request_संकेतed(rq));

	/* See the comment in i915_request_active_seqno(). */
	वापस page_mask_bits(tl->hwsp_offset) + offset_in_page(rq->hwsp_seqno);
पूर्ण

पूर्णांक gen8_emit_init_bपढ़ोcrumb(काष्ठा i915_request *rq)
अणु
	u32 *cs;

	GEM_BUG_ON(i915_request_has_initial_bपढ़ोcrumb(rq));
	अगर (!i915_request_समयline(rq)->has_initial_bपढ़ोcrumb)
		वापस 0;

	cs = पूर्णांकel_ring_begin(rq, 6);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	*cs++ = MI_STORE_DWORD_IMM_GEN4 | MI_USE_GGTT;
	*cs++ = hwsp_offset(rq);
	*cs++ = 0;
	*cs++ = rq->fence.seqno - 1;

	/*
	 * Check अगर we have been preempted beक्रमe we even get started.
	 *
	 * After this poपूर्णांक i915_request_started() reports true, even अगर
	 * we get preempted and so are no दीर्घer running.
	 *
	 * i915_request_started() is used during preemption processing
	 * to decide अगर the request is currently inside the user payload
	 * or spinning on a kernel semaphore (or earlier). For no-preemption
	 * requests, we करो allow preemption on the semaphore beक्रमe the user
	 * payload, but करो not allow preemption once the request is started.
	 *
	 * i915_request_started() is similarly used during GPU hangs to
	 * determine अगर the user's payload was guilty, and अगर so, the
	 * request is banned. Beक्रमe the request is started, it is assumed
	 * to be unharmed and an innocent victim of another's hang.
	 */
	*cs++ = MI_NOOP;
	*cs++ = MI_ARB_CHECK;

	पूर्णांकel_ring_advance(rq, cs);

	/* Record the updated position of the request's payload */
	rq->infix = पूर्णांकel_ring_offset(rq, cs);

	__set_bit(I915_FENCE_FLAG_INITIAL_BREADCRUMB, &rq->fence.flags);

	वापस 0;
पूर्ण

पूर्णांक gen8_emit_bb_start_noarb(काष्ठा i915_request *rq,
			     u64 offset, u32 len,
			     स्थिर अचिन्हित पूर्णांक flags)
अणु
	u32 *cs;

	cs = पूर्णांकel_ring_begin(rq, 4);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	/*
	 * WaDisableCtxRestoreArbitration:bdw,chv
	 *
	 * We करोn't need to perक्रमm MI_ARB_ENABLE as often as we करो (in
	 * particular all the gen that करो not need the w/a at all!), अगर we
	 * took care to make sure that on every चयन पूर्णांकo this context
	 * (both ordinary and क्रम preemption) that arbitrartion was enabled
	 * we would be fine.  However, क्रम gen8 there is another w/a that
	 * requires us to not preempt inside GPGPU execution, so we keep
	 * arbitration disabled क्रम gen8 batches. Arbitration will be
	 * re-enabled beक्रमe we बंद the request
	 * (engine->emit_fini_bपढ़ोcrumb).
	 */
	*cs++ = MI_ARB_ON_OFF | MI_ARB_DISABLE;

	/* FIXME(BDW+): Address space and security selectors. */
	*cs++ = MI_BATCH_BUFFER_START_GEN8 |
		(flags & I915_DISPATCH_SECURE ? 0 : BIT(8));
	*cs++ = lower_32_bits(offset);
	*cs++ = upper_32_bits(offset);

	पूर्णांकel_ring_advance(rq, cs);

	वापस 0;
पूर्ण

पूर्णांक gen8_emit_bb_start(काष्ठा i915_request *rq,
		       u64 offset, u32 len,
		       स्थिर अचिन्हित पूर्णांक flags)
अणु
	u32 *cs;

	अगर (unlikely(i915_request_has_nopreempt(rq)))
		वापस gen8_emit_bb_start_noarb(rq, offset, len, flags);

	cs = पूर्णांकel_ring_begin(rq, 6);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	*cs++ = MI_ARB_ON_OFF | MI_ARB_ENABLE;

	*cs++ = MI_BATCH_BUFFER_START_GEN8 |
		(flags & I915_DISPATCH_SECURE ? 0 : BIT(8));
	*cs++ = lower_32_bits(offset);
	*cs++ = upper_32_bits(offset);

	*cs++ = MI_ARB_ON_OFF | MI_ARB_DISABLE;
	*cs++ = MI_NOOP;

	पूर्णांकel_ring_advance(rq, cs);

	वापस 0;
पूर्ण

अटल व्योम निश्चित_request_valid(काष्ठा i915_request *rq)
अणु
	काष्ठा पूर्णांकel_ring *ring __maybe_unused = rq->ring;

	/* Can we unwind this request without appearing to go क्रमwards? */
	GEM_BUG_ON(पूर्णांकel_ring_direction(ring, rq->wa_tail, rq->head) <= 0);
पूर्ण

/*
 * Reserve space क्रम 2 NOOPs at the end of each request to be
 * used as a workaround क्रम not being allowed to करो lite
 * restore with HEAD==TAIL (WaIdleLiteRestore).
 */
अटल u32 *gen8_emit_wa_tail(काष्ठा i915_request *rq, u32 *cs)
अणु
	/* Ensure there's always at least one preemption poपूर्णांक per-request. */
	*cs++ = MI_ARB_CHECK;
	*cs++ = MI_NOOP;
	rq->wa_tail = पूर्णांकel_ring_offset(rq, cs);

	/* Check that entire request is less than half the ring */
	निश्चित_request_valid(rq);

	वापस cs;
पूर्ण

अटल u32 *emit_preempt_busyरुको(काष्ठा i915_request *rq, u32 *cs)
अणु
	*cs++ = MI_ARB_CHECK; /* trigger IDLE->ACTIVE first */
	*cs++ = MI_SEMAPHORE_WAIT |
		MI_SEMAPHORE_GLOBAL_GTT |
		MI_SEMAPHORE_POLL |
		MI_SEMAPHORE_SAD_EQ_SDD;
	*cs++ = 0;
	*cs++ = preempt_address(rq->engine);
	*cs++ = 0;
	*cs++ = MI_NOOP;

	वापस cs;
पूर्ण

अटल __always_अंतरभूत u32*
gen8_emit_fini_bपढ़ोcrumb_tail(काष्ठा i915_request *rq, u32 *cs)
अणु
	*cs++ = MI_USER_INTERRUPT;

	*cs++ = MI_ARB_ON_OFF | MI_ARB_ENABLE;
	अगर (पूर्णांकel_engine_has_semaphores(rq->engine))
		cs = emit_preempt_busyरुको(rq, cs);

	rq->tail = पूर्णांकel_ring_offset(rq, cs);
	निश्चित_ring_tail_valid(rq->ring, rq->tail);

	वापस gen8_emit_wa_tail(rq, cs);
पूर्ण

अटल u32 *emit_xcs_bपढ़ोcrumb(काष्ठा i915_request *rq, u32 *cs)
अणु
	वापस gen8_emit_ggtt_ग_लिखो(cs, rq->fence.seqno, hwsp_offset(rq), 0);
पूर्ण

u32 *gen8_emit_fini_bपढ़ोcrumb_xcs(काष्ठा i915_request *rq, u32 *cs)
अणु
	वापस gen8_emit_fini_bपढ़ोcrumb_tail(rq, emit_xcs_bपढ़ोcrumb(rq, cs));
पूर्ण

u32 *gen8_emit_fini_bपढ़ोcrumb_rcs(काष्ठा i915_request *rq, u32 *cs)
अणु
	cs = gen8_emit_pipe_control(cs,
				    PIPE_CONTROL_RENDER_TARGET_CACHE_FLUSH |
				    PIPE_CONTROL_DEPTH_CACHE_FLUSH |
				    PIPE_CONTROL_DC_FLUSH_ENABLE,
				    0);

	/* XXX flush+ग_लिखो+CS_STALL all in one upsets gem_concurrent_blt:kbl */
	cs = gen8_emit_ggtt_ग_लिखो_rcs(cs,
				      rq->fence.seqno,
				      hwsp_offset(rq),
				      PIPE_CONTROL_FLUSH_ENABLE |
				      PIPE_CONTROL_CS_STALL);

	वापस gen8_emit_fini_bपढ़ोcrumb_tail(rq, cs);
पूर्ण

u32 *gen11_emit_fini_bपढ़ोcrumb_rcs(काष्ठा i915_request *rq, u32 *cs)
अणु
	cs = gen8_emit_ggtt_ग_लिखो_rcs(cs,
				      rq->fence.seqno,
				      hwsp_offset(rq),
				      PIPE_CONTROL_CS_STALL |
				      PIPE_CONTROL_TILE_CACHE_FLUSH |
				      PIPE_CONTROL_RENDER_TARGET_CACHE_FLUSH |
				      PIPE_CONTROL_DEPTH_CACHE_FLUSH |
				      PIPE_CONTROL_DC_FLUSH_ENABLE |
				      PIPE_CONTROL_FLUSH_ENABLE);

	वापस gen8_emit_fini_bपढ़ोcrumb_tail(rq, cs);
पूर्ण

/*
 * Note that the CS inकाष्ठाion pre-parser will not stall on the bपढ़ोcrumb
 * flush and will जारी pre-fetching the inकाष्ठाions after it beक्रमe the
 * memory sync is completed. On pre-gen12 HW, the pre-parser will stop at
 * BB_START/END inकाष्ठाions, so, even though we might pre-fetch the pre-amble
 * of the next request beक्रमe the memory has been flushed, we're guaranteed that
 * we won't access the batch itself too early.
 * However, on gen12+ the parser can pre-fetch across the BB_START/END commands,
 * so, अगर the current request is modअगरying an inकाष्ठाion in the next request on
 * the same पूर्णांकel_context, we might pre-fetch and then execute the pre-update
 * inकाष्ठाion. To aव्योम this, the users of self-modअगरying code should either
 * disable the parser around the code emitting the memory ग_लिखोs, via a new flag
 * added to MI_ARB_CHECK, or emit the ग_लिखोs from a dअगरferent पूर्णांकel_context. For
 * the in-kernel use-हालs we've opted to use a separate context, see
 * reloc_gpu() as an example.
 * All the above applies only to the inकाष्ठाions themselves. Non-अंतरभूत data
 * used by the inकाष्ठाions is not pre-fetched.
 */

अटल u32 *gen12_emit_preempt_busyरुको(काष्ठा i915_request *rq, u32 *cs)
अणु
	*cs++ = MI_ARB_CHECK; /* trigger IDLE->ACTIVE first */
	*cs++ = MI_SEMAPHORE_WAIT_TOKEN |
		MI_SEMAPHORE_GLOBAL_GTT |
		MI_SEMAPHORE_POLL |
		MI_SEMAPHORE_SAD_EQ_SDD;
	*cs++ = 0;
	*cs++ = preempt_address(rq->engine);
	*cs++ = 0;
	*cs++ = 0;

	वापस cs;
पूर्ण

अटल __always_अंतरभूत u32*
gen12_emit_fini_bपढ़ोcrumb_tail(काष्ठा i915_request *rq, u32 *cs)
अणु
	*cs++ = MI_USER_INTERRUPT;

	*cs++ = MI_ARB_ON_OFF | MI_ARB_ENABLE;
	अगर (पूर्णांकel_engine_has_semaphores(rq->engine))
		cs = gen12_emit_preempt_busyरुको(rq, cs);

	rq->tail = पूर्णांकel_ring_offset(rq, cs);
	निश्चित_ring_tail_valid(rq->ring, rq->tail);

	वापस gen8_emit_wa_tail(rq, cs);
पूर्ण

u32 *gen12_emit_fini_bपढ़ोcrumb_xcs(काष्ठा i915_request *rq, u32 *cs)
अणु
	/* XXX Stalling flush beक्रमe seqno ग_लिखो; post-sync not */
	cs = emit_xcs_bपढ़ोcrumb(rq, __gen8_emit_flush_dw(cs, 0, 0, 0));
	वापस gen12_emit_fini_bपढ़ोcrumb_tail(rq, cs);
पूर्ण

u32 *gen12_emit_fini_bपढ़ोcrumb_rcs(काष्ठा i915_request *rq, u32 *cs)
अणु
	cs = gen12_emit_ggtt_ग_लिखो_rcs(cs,
				       rq->fence.seqno,
				       hwsp_offset(rq),
				       PIPE_CONTROL0_HDC_PIPELINE_FLUSH,
				       PIPE_CONTROL_CS_STALL |
				       PIPE_CONTROL_TILE_CACHE_FLUSH |
				       PIPE_CONTROL_FLUSH_L3 |
				       PIPE_CONTROL_RENDER_TARGET_CACHE_FLUSH |
				       PIPE_CONTROL_DEPTH_CACHE_FLUSH |
				       /* Wa_1409600907:tgl */
				       PIPE_CONTROL_DEPTH_STALL |
				       PIPE_CONTROL_DC_FLUSH_ENABLE |
				       PIPE_CONTROL_FLUSH_ENABLE);

	वापस gen12_emit_fini_bपढ़ोcrumb_tail(rq, cs);
पूर्ण
