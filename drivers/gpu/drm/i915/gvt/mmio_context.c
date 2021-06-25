<शैली गुरु>
/*
 * Copyright(c) 2011-2016 Intel Corporation. All rights reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Authors:
 *    Eddie Dong <eddie.करोng@पूर्णांकel.com>
 *    Kevin Tian <kevin.tian@पूर्णांकel.com>
 *
 * Contributors:
 *    Zhi Wang <zhi.a.wang@पूर्णांकel.com>
 *    Changbin Du <changbin.du@पूर्णांकel.com>
 *    Zhenyu Wang <zhenyuw@linux.पूर्णांकel.com>
 *    Tina Zhang <tina.zhang@पूर्णांकel.com>
 *    Bing Niu <bing.niu@पूर्णांकel.com>
 *
 */

#समावेश "i915_drv.h"
#समावेश "gt/intel_context.h"
#समावेश "gt/intel_gpu_commands.h"
#समावेश "gt/intel_ring.h"
#समावेश "gvt.h"
#समावेश "trace.h"

#घोषणा GEN9_MOCS_SIZE		64

/* Raw offset is appened to each line क्रम convenience. */
अटल काष्ठा engine_mmio gen8_engine_mmio_list[] __cacheline_aligned = अणु
	अणुRCS0, GFX_MODE_GEN7, 0xffff, falseपूर्ण, /* 0x229c */
	अणुRCS0, GEN9_CTX_PREEMPT_REG, 0x0, falseपूर्ण, /* 0x2248 */
	अणुRCS0, HWSTAM, 0x0, falseपूर्ण, /* 0x2098 */
	अणुRCS0, INSTPM, 0xffff, trueपूर्ण, /* 0x20c0 */
	अणुRCS0, RING_FORCE_TO_NONPRIV(RENDER_RING_BASE, 0), 0, falseपूर्ण, /* 0x24d0 */
	अणुRCS0, RING_FORCE_TO_NONPRIV(RENDER_RING_BASE, 1), 0, falseपूर्ण, /* 0x24d4 */
	अणुRCS0, RING_FORCE_TO_NONPRIV(RENDER_RING_BASE, 2), 0, falseपूर्ण, /* 0x24d8 */
	अणुRCS0, RING_FORCE_TO_NONPRIV(RENDER_RING_BASE, 3), 0, falseपूर्ण, /* 0x24dc */
	अणुRCS0, RING_FORCE_TO_NONPRIV(RENDER_RING_BASE, 4), 0, falseपूर्ण, /* 0x24e0 */
	अणुRCS0, RING_FORCE_TO_NONPRIV(RENDER_RING_BASE, 5), 0, falseपूर्ण, /* 0x24e4 */
	अणुRCS0, RING_FORCE_TO_NONPRIV(RENDER_RING_BASE, 6), 0, falseपूर्ण, /* 0x24e8 */
	अणुRCS0, RING_FORCE_TO_NONPRIV(RENDER_RING_BASE, 7), 0, falseपूर्ण, /* 0x24ec */
	अणुRCS0, RING_FORCE_TO_NONPRIV(RENDER_RING_BASE, 8), 0, falseपूर्ण, /* 0x24f0 */
	अणुRCS0, RING_FORCE_TO_NONPRIV(RENDER_RING_BASE, 9), 0, falseपूर्ण, /* 0x24f4 */
	अणुRCS0, RING_FORCE_TO_NONPRIV(RENDER_RING_BASE, 10), 0, falseपूर्ण, /* 0x24f8 */
	अणुRCS0, RING_FORCE_TO_NONPRIV(RENDER_RING_BASE, 11), 0, falseपूर्ण, /* 0x24fc */
	अणुRCS0, CACHE_MODE_1, 0xffff, trueपूर्ण, /* 0x7004 */
	अणुRCS0, GEN7_GT_MODE, 0xffff, trueपूर्ण, /* 0x7008 */
	अणुRCS0, CACHE_MODE_0_GEN7, 0xffff, trueपूर्ण, /* 0x7000 */
	अणुRCS0, GEN7_COMMON_SLICE_CHICKEN1, 0xffff, trueपूर्ण, /* 0x7010 */
	अणुRCS0, HDC_CHICKEN0, 0xffff, trueपूर्ण, /* 0x7300 */
	अणुRCS0, VF_GUARDBAND, 0xffff, trueपूर्ण, /* 0x83a4 */

	अणुBCS0, RING_GFX_MODE(BLT_RING_BASE), 0xffff, falseपूर्ण, /* 0x2229c */
	अणुBCS0, RING_MI_MODE(BLT_RING_BASE), 0xffff, falseपूर्ण, /* 0x2209c */
	अणुBCS0, RING_INSTPM(BLT_RING_BASE), 0xffff, falseपूर्ण, /* 0x220c0 */
	अणुBCS0, RING_HWSTAM(BLT_RING_BASE), 0x0, falseपूर्ण, /* 0x22098 */
	अणुBCS0, RING_EXCC(BLT_RING_BASE), 0xffff, falseपूर्ण, /* 0x22028 */
	अणुRCS0, INVALID_MMIO_REG, 0, false पूर्ण /* Terminated */
पूर्ण;

अटल काष्ठा engine_mmio gen9_engine_mmio_list[] __cacheline_aligned = अणु
	अणुRCS0, GFX_MODE_GEN7, 0xffff, falseपूर्ण, /* 0x229c */
	अणुRCS0, GEN9_CTX_PREEMPT_REG, 0x0, falseपूर्ण, /* 0x2248 */
	अणुRCS0, HWSTAM, 0x0, falseपूर्ण, /* 0x2098 */
	अणुRCS0, INSTPM, 0xffff, trueपूर्ण, /* 0x20c0 */
	अणुRCS0, RING_FORCE_TO_NONPRIV(RENDER_RING_BASE, 0), 0, falseपूर्ण, /* 0x24d0 */
	अणुRCS0, RING_FORCE_TO_NONPRIV(RENDER_RING_BASE, 1), 0, falseपूर्ण, /* 0x24d4 */
	अणुRCS0, RING_FORCE_TO_NONPRIV(RENDER_RING_BASE, 2), 0, falseपूर्ण, /* 0x24d8 */
	अणुRCS0, RING_FORCE_TO_NONPRIV(RENDER_RING_BASE, 3), 0, falseपूर्ण, /* 0x24dc */
	अणुRCS0, RING_FORCE_TO_NONPRIV(RENDER_RING_BASE, 4), 0, falseपूर्ण, /* 0x24e0 */
	अणुRCS0, RING_FORCE_TO_NONPRIV(RENDER_RING_BASE, 5), 0, falseपूर्ण, /* 0x24e4 */
	अणुRCS0, RING_FORCE_TO_NONPRIV(RENDER_RING_BASE, 6), 0, falseपूर्ण, /* 0x24e8 */
	अणुRCS0, RING_FORCE_TO_NONPRIV(RENDER_RING_BASE, 7), 0, falseपूर्ण, /* 0x24ec */
	अणुRCS0, RING_FORCE_TO_NONPRIV(RENDER_RING_BASE, 8), 0, falseपूर्ण, /* 0x24f0 */
	अणुRCS0, RING_FORCE_TO_NONPRIV(RENDER_RING_BASE, 9), 0, falseपूर्ण, /* 0x24f4 */
	अणुRCS0, RING_FORCE_TO_NONPRIV(RENDER_RING_BASE, 10), 0, falseपूर्ण, /* 0x24f8 */
	अणुRCS0, RING_FORCE_TO_NONPRIV(RENDER_RING_BASE, 11), 0, falseपूर्ण, /* 0x24fc */
	अणुRCS0, CACHE_MODE_1, 0xffff, trueपूर्ण, /* 0x7004 */
	अणुRCS0, GEN7_GT_MODE, 0xffff, trueपूर्ण, /* 0x7008 */
	अणुRCS0, CACHE_MODE_0_GEN7, 0xffff, trueपूर्ण, /* 0x7000 */
	अणुRCS0, GEN7_COMMON_SLICE_CHICKEN1, 0xffff, trueपूर्ण, /* 0x7010 */
	अणुRCS0, HDC_CHICKEN0, 0xffff, trueपूर्ण, /* 0x7300 */
	अणुRCS0, VF_GUARDBAND, 0xffff, trueपूर्ण, /* 0x83a4 */

	अणुRCS0, GEN8_PRIVATE_PAT_LO, 0, falseपूर्ण, /* 0x40e0 */
	अणुRCS0, GEN8_PRIVATE_PAT_HI, 0, falseपूर्ण, /* 0x40e4 */
	अणुRCS0, GEN8_CS_CHICKEN1, 0xffff, trueपूर्ण, /* 0x2580 */
	अणुRCS0, COMMON_SLICE_CHICKEN2, 0xffff, trueपूर्ण, /* 0x7014 */
	अणुRCS0, GEN9_CS_DEBUG_MODE1, 0xffff, falseपूर्ण, /* 0x20ec */
	अणुRCS0, GEN8_L3SQCREG4, 0, falseपूर्ण, /* 0xb118 */
	अणुRCS0, GEN7_HALF_SLICE_CHICKEN1, 0xffff, trueपूर्ण, /* 0xe100 */
	अणुRCS0, HALF_SLICE_CHICKEN2, 0xffff, trueपूर्ण, /* 0xe180 */
	अणुRCS0, HALF_SLICE_CHICKEN3, 0xffff, trueपूर्ण, /* 0xe184 */
	अणुRCS0, GEN9_HALF_SLICE_CHICKEN5, 0xffff, trueपूर्ण, /* 0xe188 */
	अणुRCS0, GEN9_HALF_SLICE_CHICKEN7, 0xffff, trueपूर्ण, /* 0xe194 */
	अणुRCS0, GEN8_ROW_CHICKEN, 0xffff, trueपूर्ण, /* 0xe4f0 */
	अणुRCS0, TRVATTL3PTRDW(0), 0, trueपूर्ण, /* 0x4de0 */
	अणुRCS0, TRVATTL3PTRDW(1), 0, trueपूर्ण, /* 0x4de4 */
	अणुRCS0, TRशून्यDETCT, 0, trueपूर्ण, /* 0x4de8 */
	अणुRCS0, TRINVTILEDETCT, 0, trueपूर्ण, /* 0x4dec */
	अणुRCS0, TRVADR, 0, trueपूर्ण, /* 0x4df0 */
	अणुRCS0, TRTTE, 0, trueपूर्ण, /* 0x4df4 */
	अणुRCS0, _MMIO(0x4dfc), 0, trueपूर्ण,

	अणुBCS0, RING_GFX_MODE(BLT_RING_BASE), 0xffff, falseपूर्ण, /* 0x2229c */
	अणुBCS0, RING_MI_MODE(BLT_RING_BASE), 0xffff, falseपूर्ण, /* 0x2209c */
	अणुBCS0, RING_INSTPM(BLT_RING_BASE), 0xffff, falseपूर्ण, /* 0x220c0 */
	अणुBCS0, RING_HWSTAM(BLT_RING_BASE), 0x0, falseपूर्ण, /* 0x22098 */
	अणुBCS0, RING_EXCC(BLT_RING_BASE), 0xffff, falseपूर्ण, /* 0x22028 */

	अणुVCS1, RING_EXCC(GEN8_BSD2_RING_BASE), 0xffff, falseपूर्ण, /* 0x1c028 */

	अणुVECS0, RING_EXCC(VEBOX_RING_BASE), 0xffff, falseपूर्ण, /* 0x1a028 */

	अणुRCS0, GEN8_HDC_CHICKEN1, 0xffff, trueपूर्ण, /* 0x7304 */
	अणुRCS0, GEN9_CTX_PREEMPT_REG, 0x0, falseपूर्ण, /* 0x2248 */
	अणुRCS0, GEN7_UCGCTL4, 0x0, falseपूर्ण, /* 0x940c */
	अणुRCS0, GAMT_CHKN_BIT_REG, 0x0, falseपूर्ण, /* 0x4ab8 */

	अणुRCS0, GEN9_GAMT_ECO_REG_RW_IA, 0x0, falseपूर्ण, /* 0x4ab0 */
	अणुRCS0, GEN9_CSFE_CHICKEN1_RCS, 0xffff, falseपूर्ण, /* 0x20d4 */
	अणुRCS0, _MMIO(0x20D8), 0xffff, trueपूर्ण, /* 0x20d8 */

	अणुRCS0, GEN8_GARBCNTL, 0x0, falseपूर्ण, /* 0xb004 */
	अणुRCS0, GEN7_FF_THREAD_MODE, 0x0, falseपूर्ण, /* 0x20a0 */
	अणुRCS0, FF_SLICE_CS_CHICKEN2, 0xffff, falseपूर्ण, /* 0x20e4 */
	अणुRCS0, INVALID_MMIO_REG, 0, false पूर्ण /* Terminated */
पूर्ण;

अटल काष्ठा अणु
	bool initialized;
	u32 control_table[I915_NUM_ENGINES][GEN9_MOCS_SIZE];
	u32 l3cc_table[GEN9_MOCS_SIZE / 2];
पूर्ण gen9_render_mocs;

अटल u32 gen9_mocs_mmio_offset_list[] = अणु
	[RCS0]  = 0xc800,
	[VCS0]  = 0xc900,
	[VCS1]  = 0xca00,
	[BCS0]  = 0xcc00,
	[VECS0] = 0xcb00,
पूर्ण;

अटल व्योम load_render_mocs(स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_gvt *gvt = engine->i915->gvt;
	काष्ठा पूर्णांकel_uncore *uncore = engine->uncore;
	u32 cnt = gvt->engine_mmio_list.mocs_mmio_offset_list_cnt;
	u32 *regs = gvt->engine_mmio_list.mocs_mmio_offset_list;
	i915_reg_t offset;
	पूर्णांक ring_id, i;

	/* Platक्रमm करोesn't have mocs mmios. */
	अगर (!regs)
		वापस;

	क्रम (ring_id = 0; ring_id < cnt; ring_id++) अणु
		अगर (!HAS_ENGINE(engine->gt, ring_id))
			जारी;

		offset.reg = regs[ring_id];
		क्रम (i = 0; i < GEN9_MOCS_SIZE; i++) अणु
			gen9_render_mocs.control_table[ring_id][i] =
				पूर्णांकel_uncore_पढ़ो_fw(uncore, offset);
			offset.reg += 4;
		पूर्ण
	पूर्ण

	offset.reg = 0xb020;
	क्रम (i = 0; i < GEN9_MOCS_SIZE / 2; i++) अणु
		gen9_render_mocs.l3cc_table[i] =
			पूर्णांकel_uncore_पढ़ो_fw(uncore, offset);
		offset.reg += 4;
	पूर्ण
	gen9_render_mocs.initialized = true;
पूर्ण

अटल पूर्णांक
restore_context_mmio_क्रम_inhibit(काष्ठा पूर्णांकel_vgpu *vgpu,
				 काष्ठा i915_request *req)
अणु
	u32 *cs;
	पूर्णांक ret;
	काष्ठा engine_mmio *mmio;
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	पूर्णांक ring_id = req->engine->id;
	पूर्णांक count = gvt->engine_mmio_list.ctx_mmio_count[ring_id];

	अगर (count == 0)
		वापस 0;

	ret = req->engine->emit_flush(req, EMIT_BARRIER);
	अगर (ret)
		वापस ret;

	cs = पूर्णांकel_ring_begin(req, count * 2 + 2);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	*cs++ = MI_LOAD_REGISTER_IMM(count);
	क्रम (mmio = gvt->engine_mmio_list.mmio;
	     i915_mmio_reg_valid(mmio->reg); mmio++) अणु
		अगर (mmio->id != ring_id || !mmio->in_context)
			जारी;

		*cs++ = i915_mmio_reg_offset(mmio->reg);
		*cs++ = vgpu_vreg_t(vgpu, mmio->reg) | (mmio->mask << 16);
		gvt_dbg_core("add lri reg pair 0x%x:0x%x in inhibit ctx, vgpu:%d, rind_id:%d\n",
			      *(cs-2), *(cs-1), vgpu->id, ring_id);
	पूर्ण

	*cs++ = MI_NOOP;
	पूर्णांकel_ring_advance(req, cs);

	ret = req->engine->emit_flush(req, EMIT_BARRIER);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक
restore_render_mocs_control_क्रम_inhibit(काष्ठा पूर्णांकel_vgpu *vgpu,
					काष्ठा i915_request *req)
अणु
	अचिन्हित पूर्णांक index;
	u32 *cs;

	cs = पूर्णांकel_ring_begin(req, 2 * GEN9_MOCS_SIZE + 2);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	*cs++ = MI_LOAD_REGISTER_IMM(GEN9_MOCS_SIZE);

	क्रम (index = 0; index < GEN9_MOCS_SIZE; index++) अणु
		*cs++ = i915_mmio_reg_offset(GEN9_GFX_MOCS(index));
		*cs++ = vgpu_vreg_t(vgpu, GEN9_GFX_MOCS(index));
		gvt_dbg_core("add lri reg pair 0x%x:0x%x in inhibit ctx, vgpu:%d, rind_id:%d\n",
			      *(cs-2), *(cs-1), vgpu->id, req->engine->id);

	पूर्ण

	*cs++ = MI_NOOP;
	पूर्णांकel_ring_advance(req, cs);

	वापस 0;
पूर्ण

अटल पूर्णांक
restore_render_mocs_l3cc_क्रम_inhibit(काष्ठा पूर्णांकel_vgpu *vgpu,
				     काष्ठा i915_request *req)
अणु
	अचिन्हित पूर्णांक index;
	u32 *cs;

	cs = पूर्णांकel_ring_begin(req, 2 * GEN9_MOCS_SIZE / 2 + 2);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	*cs++ = MI_LOAD_REGISTER_IMM(GEN9_MOCS_SIZE / 2);

	क्रम (index = 0; index < GEN9_MOCS_SIZE / 2; index++) अणु
		*cs++ = i915_mmio_reg_offset(GEN9_LNCFCMOCS(index));
		*cs++ = vgpu_vreg_t(vgpu, GEN9_LNCFCMOCS(index));
		gvt_dbg_core("add lri reg pair 0x%x:0x%x in inhibit ctx, vgpu:%d, rind_id:%d\n",
			      *(cs-2), *(cs-1), vgpu->id, req->engine->id);

	पूर्ण

	*cs++ = MI_NOOP;
	पूर्णांकel_ring_advance(req, cs);

	वापस 0;
पूर्ण

/*
 * Use lri command to initialize the mmio which is in context state image क्रम
 * inhibit context, it contains tracked engine mmio, render_mocs and
 * render_mocs_l3cc.
 */
पूर्णांक पूर्णांकel_vgpu_restore_inhibit_context(काष्ठा पूर्णांकel_vgpu *vgpu,
				       काष्ठा i915_request *req)
अणु
	पूर्णांक ret;
	u32 *cs;

	cs = पूर्णांकel_ring_begin(req, 2);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	*cs++ = MI_ARB_ON_OFF | MI_ARB_DISABLE;
	*cs++ = MI_NOOP;
	पूर्णांकel_ring_advance(req, cs);

	ret = restore_context_mmio_क्रम_inhibit(vgpu, req);
	अगर (ret)
		जाओ out;

	/* no MOCS रेजिस्टर in context except render engine */
	अगर (req->engine->id != RCS0)
		जाओ out;

	ret = restore_render_mocs_control_क्रम_inhibit(vgpu, req);
	अगर (ret)
		जाओ out;

	ret = restore_render_mocs_l3cc_क्रम_inhibit(vgpu, req);
	अगर (ret)
		जाओ out;

out:
	cs = पूर्णांकel_ring_begin(req, 2);
	अगर (IS_ERR(cs))
		वापस PTR_ERR(cs);

	*cs++ = MI_ARB_ON_OFF | MI_ARB_ENABLE;
	*cs++ = MI_NOOP;
	पूर्णांकel_ring_advance(req, cs);

	वापस ret;
पूर्ण

अटल u32 gen8_tlb_mmio_offset_list[] = अणु
	[RCS0]  = 0x4260,
	[VCS0]  = 0x4264,
	[VCS1]  = 0x4268,
	[BCS0]  = 0x426c,
	[VECS0] = 0x4270,
पूर्ण;

अटल व्योम handle_tlb_pending_event(काष्ठा पूर्णांकel_vgpu *vgpu,
				     स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = engine->uncore;
	काष्ठा पूर्णांकel_vgpu_submission *s = &vgpu->submission;
	u32 *regs = vgpu->gvt->engine_mmio_list.tlb_mmio_offset_list;
	u32 cnt = vgpu->gvt->engine_mmio_list.tlb_mmio_offset_list_cnt;
	क्रमागत क्रमcewake_करोमुख्यs fw;
	i915_reg_t reg;

	अगर (!regs)
		वापस;

	अगर (drm_WARN_ON(&engine->i915->drm, engine->id >= cnt))
		वापस;

	अगर (!test_and_clear_bit(engine->id, (व्योम *)s->tlb_handle_pending))
		वापस;

	reg = _MMIO(regs[engine->id]);

	/* WaForceWakeRenderDuringMmioTLBInvalidate:skl
	 * we need to put a क्रमcewake when invalidating RCS TLB caches,
	 * otherwise device can go to RC6 state and पूर्णांकerrupt invalidation
	 * process
	 */
	fw = पूर्णांकel_uncore_क्रमcewake_क्रम_reg(uncore, reg,
					    FW_REG_READ | FW_REG_WRITE);
	अगर (engine->id == RCS0 && INTEL_GEN(engine->i915) >= 9)
		fw |= FORCEWAKE_RENDER;

	पूर्णांकel_uncore_क्रमcewake_get(uncore, fw);

	पूर्णांकel_uncore_ग_लिखो_fw(uncore, reg, 0x1);

	अगर (रुको_क्रम_atomic(पूर्णांकel_uncore_पढ़ो_fw(uncore, reg) == 0, 50))
		gvt_vgpu_err("timeout in invalidate ring %s tlb\n",
			     engine->name);
	अन्यथा
		vgpu_vreg_t(vgpu, reg) = 0;

	पूर्णांकel_uncore_क्रमcewake_put(uncore, fw);

	gvt_dbg_core("invalidate TLB for ring %s\n", engine->name);
पूर्ण

अटल व्योम चयन_mocs(काष्ठा पूर्णांकel_vgpu *pre, काष्ठा पूर्णांकel_vgpu *next,
			स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	u32 regs[] = अणु
		[RCS0]  = 0xc800,
		[VCS0]  = 0xc900,
		[VCS1]  = 0xca00,
		[BCS0]  = 0xcc00,
		[VECS0] = 0xcb00,
	पूर्ण;
	काष्ठा पूर्णांकel_uncore *uncore = engine->uncore;
	i915_reg_t offset, l3_offset;
	u32 old_v, new_v;
	पूर्णांक i;

	अगर (drm_WARN_ON(&engine->i915->drm, engine->id >= ARRAY_SIZE(regs)))
		वापस;

	अगर (engine->id == RCS0 && IS_GEN(engine->i915, 9))
		वापस;

	अगर (!pre && !gen9_render_mocs.initialized)
		load_render_mocs(engine);

	offset.reg = regs[engine->id];
	क्रम (i = 0; i < GEN9_MOCS_SIZE; i++) अणु
		अगर (pre)
			old_v = vgpu_vreg_t(pre, offset);
		अन्यथा
			old_v = gen9_render_mocs.control_table[engine->id][i];
		अगर (next)
			new_v = vgpu_vreg_t(next, offset);
		अन्यथा
			new_v = gen9_render_mocs.control_table[engine->id][i];

		अगर (old_v != new_v)
			पूर्णांकel_uncore_ग_लिखो_fw(uncore, offset, new_v);

		offset.reg += 4;
	पूर्ण

	अगर (engine->id == RCS0) अणु
		l3_offset.reg = 0xb020;
		क्रम (i = 0; i < GEN9_MOCS_SIZE / 2; i++) अणु
			अगर (pre)
				old_v = vgpu_vreg_t(pre, l3_offset);
			अन्यथा
				old_v = gen9_render_mocs.l3cc_table[i];
			अगर (next)
				new_v = vgpu_vreg_t(next, l3_offset);
			अन्यथा
				new_v = gen9_render_mocs.l3cc_table[i];

			अगर (old_v != new_v)
				पूर्णांकel_uncore_ग_लिखो_fw(uncore, l3_offset, new_v);

			l3_offset.reg += 4;
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा CTX_CONTEXT_CONTROL_VAL	0x03

bool is_inhibit_context(काष्ठा पूर्णांकel_context *ce)
अणु
	स्थिर u32 *reg_state = ce->lrc_reg_state;
	u32 inhibit_mask =
		_MASKED_BIT_ENABLE(CTX_CTRL_ENGINE_CTX_RESTORE_INHIBIT);

	वापस inhibit_mask ==
		(reg_state[CTX_CONTEXT_CONTROL_VAL] & inhibit_mask);
पूर्ण

/* Switch ring mmio values (context). */
अटल व्योम चयन_mmio(काष्ठा पूर्णांकel_vgpu *pre,
			काष्ठा पूर्णांकel_vgpu *next,
			स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = engine->uncore;
	काष्ठा पूर्णांकel_vgpu_submission *s;
	काष्ठा engine_mmio *mmio;
	u32 old_v, new_v;

	अगर (INTEL_GEN(engine->i915) >= 9)
		चयन_mocs(pre, next, engine);

	क्रम (mmio = engine->i915->gvt->engine_mmio_list.mmio;
	     i915_mmio_reg_valid(mmio->reg); mmio++) अणु
		अगर (mmio->id != engine->id)
			जारी;
		/*
		 * No need to करो save or restore of the mmio which is in context
		 * state image on gen9, it's initialized by lri command and
		 * save or restore with context together.
		 */
		अगर (IS_GEN(engine->i915, 9) && mmio->in_context)
			जारी;

		// save
		अगर (pre) अणु
			vgpu_vreg_t(pre, mmio->reg) =
				पूर्णांकel_uncore_पढ़ो_fw(uncore, mmio->reg);
			अगर (mmio->mask)
				vgpu_vreg_t(pre, mmio->reg) &=
					~(mmio->mask << 16);
			old_v = vgpu_vreg_t(pre, mmio->reg);
		पूर्ण अन्यथा अणु
			old_v = mmio->value =
				पूर्णांकel_uncore_पढ़ो_fw(uncore, mmio->reg);
		पूर्ण

		// restore
		अगर (next) अणु
			s = &next->submission;
			/*
			 * No need to restore the mmio which is in context state
			 * image अगर it's not inhibit context, it will restore
			 * itself.
			 */
			अगर (mmio->in_context &&
			    !is_inhibit_context(s->shaकरोw[engine->id]))
				जारी;

			अगर (mmio->mask)
				new_v = vgpu_vreg_t(next, mmio->reg) |
					(mmio->mask << 16);
			अन्यथा
				new_v = vgpu_vreg_t(next, mmio->reg);
		पूर्ण अन्यथा अणु
			अगर (mmio->in_context)
				जारी;
			अगर (mmio->mask)
				new_v = mmio->value | (mmio->mask << 16);
			अन्यथा
				new_v = mmio->value;
		पूर्ण

		पूर्णांकel_uncore_ग_लिखो_fw(uncore, mmio->reg, new_v);

		trace_render_mmio(pre ? pre->id : 0,
				  next ? next->id : 0,
				  "switch",
				  i915_mmio_reg_offset(mmio->reg),
				  old_v, new_v);
	पूर्ण

	अगर (next)
		handle_tlb_pending_event(next, engine);
पूर्ण

/**
 * पूर्णांकel_gvt_चयन_render_mmio - चयन mmio context of specअगरic engine
 * @pre: the last vGPU that own the engine
 * @next: the vGPU to चयन to
 * @engine: the engine
 *
 * If pre is null indicates that host own the engine. If next is null
 * indicates that we are चयनing to host workload.
 */
व्योम पूर्णांकel_gvt_चयन_mmio(काष्ठा पूर्णांकel_vgpu *pre,
			   काष्ठा पूर्णांकel_vgpu *next,
			   स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	अगर (WARN(!pre && !next, "switch ring %s from host to HOST\n",
		 engine->name))
		वापस;

	gvt_dbg_render("switch ring %s from %s to %s\n", engine->name,
		       pre ? "vGPU" : "host", next ? "vGPU" : "HOST");

	/**
	 * We are using raw mmio access wrapper to improve the
	 * perक्रमmace क्रम batch mmio पढ़ो/ग_लिखो, so we need
	 * handle क्रमcewake mannually.
	 */
	पूर्णांकel_uncore_क्रमcewake_get(engine->uncore, FORCEWAKE_ALL);
	चयन_mmio(pre, next, engine);
	पूर्णांकel_uncore_क्रमcewake_put(engine->uncore, FORCEWAKE_ALL);
पूर्ण

/**
 * पूर्णांकel_gvt_init_engine_mmio_context - Initiate the engine mmio list
 * @gvt: GVT device
 *
 */
व्योम पूर्णांकel_gvt_init_engine_mmio_context(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	काष्ठा engine_mmio *mmio;

	अगर (INTEL_GEN(gvt->gt->i915) >= 9) अणु
		gvt->engine_mmio_list.mmio = gen9_engine_mmio_list;
		gvt->engine_mmio_list.tlb_mmio_offset_list = gen8_tlb_mmio_offset_list;
		gvt->engine_mmio_list.tlb_mmio_offset_list_cnt = ARRAY_SIZE(gen8_tlb_mmio_offset_list);
		gvt->engine_mmio_list.mocs_mmio_offset_list = gen9_mocs_mmio_offset_list;
		gvt->engine_mmio_list.mocs_mmio_offset_list_cnt = ARRAY_SIZE(gen9_mocs_mmio_offset_list);
	पूर्ण अन्यथा अणु
		gvt->engine_mmio_list.mmio = gen8_engine_mmio_list;
		gvt->engine_mmio_list.tlb_mmio_offset_list = gen8_tlb_mmio_offset_list;
		gvt->engine_mmio_list.tlb_mmio_offset_list_cnt = ARRAY_SIZE(gen8_tlb_mmio_offset_list);
	पूर्ण

	क्रम (mmio = gvt->engine_mmio_list.mmio;
	     i915_mmio_reg_valid(mmio->reg); mmio++) अणु
		अगर (mmio->in_context) अणु
			gvt->engine_mmio_list.ctx_mmio_count[mmio->id]++;
			पूर्णांकel_gvt_mmio_set_sr_in_ctx(gvt, mmio->reg.reg);
		पूर्ण
	पूर्ण
पूर्ण
