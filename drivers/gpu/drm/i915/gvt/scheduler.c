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
 *    Zhi Wang <zhi.a.wang@पूर्णांकel.com>
 *
 * Contributors:
 *    Ping Gao <ping.a.gao@पूर्णांकel.com>
 *    Tina Zhang <tina.zhang@पूर्णांकel.com>
 *    Chanbin Du <changbin.du@पूर्णांकel.com>
 *    Min He <min.he@पूर्णांकel.com>
 *    Bing Niu <bing.niu@पूर्णांकel.com>
 *    Zhenyu Wang <zhenyuw@linux.पूर्णांकel.com>
 *
 */

#समावेश <linux/kthपढ़ो.h>

#समावेश "gem/i915_gem_pm.h"
#समावेश "gt/intel_context.h"
#समावेश "gt/intel_execlists_submission.h"
#समावेश "gt/intel_lrc.h"
#समावेश "gt/intel_ring.h"

#समावेश "i915_drv.h"
#समावेश "i915_gem_gtt.h"
#समावेश "gvt.h"

#घोषणा RING_CTX_OFF(x) \
	दुरत्व(काष्ठा execlist_ring_context, x)

अटल व्योम set_context_pdp_root_poपूर्णांकer(
		काष्ठा execlist_ring_context *ring_context,
		u32 pdp[8])
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++)
		ring_context->pdps[i].val = pdp[7 - i];
पूर्ण

अटल व्योम update_shaकरोw_pdps(काष्ठा पूर्णांकel_vgpu_workload *workload)
अणु
	काष्ठा execlist_ring_context *shaकरोw_ring_context;
	काष्ठा पूर्णांकel_context *ctx = workload->req->context;

	अगर (WARN_ON(!workload->shaकरोw_mm))
		वापस;

	अगर (WARN_ON(!atomic_पढ़ो(&workload->shaकरोw_mm->pincount)))
		वापस;

	shaकरोw_ring_context = (काष्ठा execlist_ring_context *)ctx->lrc_reg_state;
	set_context_pdp_root_poपूर्णांकer(shaकरोw_ring_context,
			(व्योम *)workload->shaकरोw_mm->ppgtt_mm.shaकरोw_pdps);
पूर्ण

/*
 * when populating shaकरोw ctx from guest, we should not overrride oa related
 * रेजिस्टरs, so that they will not be overlapped by guest oa configs. Thus
 * made it possible to capture oa data from host क्रम both host and guests.
 */
अटल व्योम sr_oa_regs(काष्ठा पूर्णांकel_vgpu_workload *workload,
		u32 *reg_state, bool save)
अणु
	काष्ठा drm_i915_निजी *dev_priv = workload->vgpu->gvt->gt->i915;
	u32 ctx_oactxctrl = dev_priv->perf.ctx_oactxctrl_offset;
	u32 ctx_flexeu0 = dev_priv->perf.ctx_flexeu0_offset;
	पूर्णांक i = 0;
	u32 flex_mmio[] = अणु
		i915_mmio_reg_offset(EU_PERF_CNTL0),
		i915_mmio_reg_offset(EU_PERF_CNTL1),
		i915_mmio_reg_offset(EU_PERF_CNTL2),
		i915_mmio_reg_offset(EU_PERF_CNTL3),
		i915_mmio_reg_offset(EU_PERF_CNTL4),
		i915_mmio_reg_offset(EU_PERF_CNTL5),
		i915_mmio_reg_offset(EU_PERF_CNTL6),
	पूर्ण;

	अगर (workload->engine->id != RCS0)
		वापस;

	अगर (save) अणु
		workload->oactxctrl = reg_state[ctx_oactxctrl + 1];

		क्रम (i = 0; i < ARRAY_SIZE(workload->flex_mmio); i++) अणु
			u32 state_offset = ctx_flexeu0 + i * 2;

			workload->flex_mmio[i] = reg_state[state_offset + 1];
		पूर्ण
	पूर्ण अन्यथा अणु
		reg_state[ctx_oactxctrl] =
			i915_mmio_reg_offset(GEN8_OACTXCONTROL);
		reg_state[ctx_oactxctrl + 1] = workload->oactxctrl;

		क्रम (i = 0; i < ARRAY_SIZE(workload->flex_mmio); i++) अणु
			u32 state_offset = ctx_flexeu0 + i * 2;
			u32 mmio = flex_mmio[i];

			reg_state[state_offset] = mmio;
			reg_state[state_offset + 1] = workload->flex_mmio[i];
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक populate_shaकरोw_context(काष्ठा पूर्णांकel_vgpu_workload *workload)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = workload->vgpu;
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	काष्ठा पूर्णांकel_context *ctx = workload->req->context;
	काष्ठा execlist_ring_context *shaकरोw_ring_context;
	व्योम *dst;
	व्योम *context_base;
	अचिन्हित दीर्घ context_gpa, context_page_num;
	अचिन्हित दीर्घ gpa_base; /* first gpa of consecutive GPAs */
	अचिन्हित दीर्घ gpa_size; /* size of consecutive GPAs */
	काष्ठा पूर्णांकel_vgpu_submission *s = &vgpu->submission;
	पूर्णांक i;
	bool skip = false;
	पूर्णांक ring_id = workload->engine->id;
	पूर्णांक ret;

	GEM_BUG_ON(!पूर्णांकel_context_is_pinned(ctx));

	context_base = (व्योम *) ctx->lrc_reg_state -
				(LRC_STATE_PN << I915_GTT_PAGE_SHIFT);

	shaकरोw_ring_context = (व्योम *) ctx->lrc_reg_state;

	sr_oa_regs(workload, (u32 *)shaकरोw_ring_context, true);
#घोषणा COPY_REG(name) \
	पूर्णांकel_gvt_hypervisor_पढ़ो_gpa(vgpu, workload->ring_context_gpa \
		+ RING_CTX_OFF(name.val), &shaकरोw_ring_context->name.val, 4)
#घोषणा COPY_REG_MASKED(name) अणु\
		पूर्णांकel_gvt_hypervisor_पढ़ो_gpa(vgpu, workload->ring_context_gpa \
					      + RING_CTX_OFF(name.val),\
					      &shaकरोw_ring_context->name.val, 4);\
		shaकरोw_ring_context->name.val |= 0xffff << 16;\
	पूर्ण

	COPY_REG_MASKED(ctx_ctrl);
	COPY_REG(ctx_बारtamp);

	अगर (workload->engine->id == RCS0) अणु
		COPY_REG(bb_per_ctx_ptr);
		COPY_REG(rcs_indirect_ctx);
		COPY_REG(rcs_indirect_ctx_offset);
	पूर्ण अन्यथा अगर (workload->engine->id == BCS0)
		पूर्णांकel_gvt_hypervisor_पढ़ो_gpa(vgpu,
				workload->ring_context_gpa +
				BCS_TILE_REGISTER_VAL_OFFSET,
				(व्योम *)shaकरोw_ring_context +
				BCS_TILE_REGISTER_VAL_OFFSET, 4);
#अघोषित COPY_REG
#अघोषित COPY_REG_MASKED

	/* करोn't copy Ring Context (the first 0x50 dwords),
	 * only copy the Engine Context part from guest
	 */
	पूर्णांकel_gvt_hypervisor_पढ़ो_gpa(vgpu,
			workload->ring_context_gpa +
			RING_CTX_SIZE,
			(व्योम *)shaकरोw_ring_context +
			RING_CTX_SIZE,
			I915_GTT_PAGE_SIZE - RING_CTX_SIZE);

	sr_oa_regs(workload, (u32 *)shaकरोw_ring_context, false);

	gvt_dbg_sched("ring %s workload lrca %x, ctx_id %x, ctx gpa %llx",
			workload->engine->name, workload->ctx_desc.lrca,
			workload->ctx_desc.context_id,
			workload->ring_context_gpa);

	/* only need to ensure this context is not pinned/unpinned during the
	 * period from last submission to this this submission.
	 * Upon reaching this function, the currently submitted context is not
	 * supposed to get unpinned. If a misbehaving guest driver ever करोes
	 * this, it would corrupt itself.
	 */
	अगर (s->last_ctx[ring_id].valid &&
			(s->last_ctx[ring_id].lrca ==
				workload->ctx_desc.lrca) &&
			(s->last_ctx[ring_id].ring_context_gpa ==
				workload->ring_context_gpa))
		skip = true;

	s->last_ctx[ring_id].lrca = workload->ctx_desc.lrca;
	s->last_ctx[ring_id].ring_context_gpa = workload->ring_context_gpa;

	अगर (IS_RESTORE_INHIBIT(shaकरोw_ring_context->ctx_ctrl.val) || skip)
		वापस 0;

	s->last_ctx[ring_id].valid = false;
	context_page_num = workload->engine->context_size;
	context_page_num = context_page_num >> PAGE_SHIFT;

	अगर (IS_BROADWELL(gvt->gt->i915) && workload->engine->id == RCS0)
		context_page_num = 19;

	/* find consecutive GPAs from gma until the first inconsecutive GPA.
	 * पढ़ो from the continuous GPAs पूर्णांकo dst भव address
	 */
	gpa_size = 0;
	क्रम (i = 2; i < context_page_num; i++) अणु
		context_gpa = पूर्णांकel_vgpu_gma_to_gpa(vgpu->gtt.ggtt_mm,
				(u32)((workload->ctx_desc.lrca + i) <<
				I915_GTT_PAGE_SHIFT));
		अगर (context_gpa == INTEL_GVT_INVALID_ADDR) अणु
			gvt_vgpu_err("Invalid guest context descriptor\n");
			वापस -EFAULT;
		पूर्ण

		अगर (gpa_size == 0) अणु
			gpa_base = context_gpa;
			dst = context_base + (i << I915_GTT_PAGE_SHIFT);
		पूर्ण अन्यथा अगर (context_gpa != gpa_base + gpa_size)
			जाओ पढ़ो;

		gpa_size += I915_GTT_PAGE_SIZE;

		अगर (i == context_page_num - 1)
			जाओ पढ़ो;

		जारी;

पढ़ो:
		पूर्णांकel_gvt_hypervisor_पढ़ो_gpa(vgpu, gpa_base, dst, gpa_size);
		gpa_base = context_gpa;
		gpa_size = I915_GTT_PAGE_SIZE;
		dst = context_base + (i << I915_GTT_PAGE_SHIFT);
	पूर्ण
	ret = पूर्णांकel_gvt_scan_engine_context(workload);
	अगर (ret) अणु
		gvt_vgpu_err("invalid cmd found in guest context pages\n");
		वापस ret;
	पूर्ण
	s->last_ctx[ring_id].valid = true;
	वापस 0;
पूर्ण

अटल अंतरभूत bool is_gvt_request(काष्ठा i915_request *rq)
अणु
	वापस पूर्णांकel_context_क्रमce_single_submission(rq->context);
पूर्ण

अटल व्योम save_ring_hw_state(काष्ठा पूर्णांकel_vgpu *vgpu,
			       स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = engine->uncore;
	i915_reg_t reg;

	reg = RING_INSTDONE(engine->mmio_base);
	vgpu_vreg(vgpu, i915_mmio_reg_offset(reg)) =
		पूर्णांकel_uncore_पढ़ो(uncore, reg);

	reg = RING_ACTHD(engine->mmio_base);
	vgpu_vreg(vgpu, i915_mmio_reg_offset(reg)) =
		पूर्णांकel_uncore_पढ़ो(uncore, reg);

	reg = RING_ACTHD_UDW(engine->mmio_base);
	vgpu_vreg(vgpu, i915_mmio_reg_offset(reg)) =
		पूर्णांकel_uncore_पढ़ो(uncore, reg);
पूर्ण

अटल पूर्णांक shaकरोw_context_status_change(काष्ठा notअगरier_block *nb,
		अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा i915_request *rq = data;
	काष्ठा पूर्णांकel_gvt *gvt = container_of(nb, काष्ठा पूर्णांकel_gvt,
				shaकरोw_ctx_notअगरier_block[rq->engine->id]);
	काष्ठा पूर्णांकel_gvt_workload_scheduler *scheduler = &gvt->scheduler;
	क्रमागत पूर्णांकel_engine_id ring_id = rq->engine->id;
	काष्ठा पूर्णांकel_vgpu_workload *workload;
	अचिन्हित दीर्घ flags;

	अगर (!is_gvt_request(rq)) अणु
		spin_lock_irqsave(&scheduler->mmio_context_lock, flags);
		अगर (action == INTEL_CONTEXT_SCHEDULE_IN &&
		    scheduler->engine_owner[ring_id]) अणु
			/* Switch ring from vGPU to host. */
			पूर्णांकel_gvt_चयन_mmio(scheduler->engine_owner[ring_id],
					      शून्य, rq->engine);
			scheduler->engine_owner[ring_id] = शून्य;
		पूर्ण
		spin_unlock_irqrestore(&scheduler->mmio_context_lock, flags);

		वापस NOTIFY_OK;
	पूर्ण

	workload = scheduler->current_workload[ring_id];
	अगर (unlikely(!workload))
		वापस NOTIFY_OK;

	चयन (action) अणु
	हाल INTEL_CONTEXT_SCHEDULE_IN:
		spin_lock_irqsave(&scheduler->mmio_context_lock, flags);
		अगर (workload->vgpu != scheduler->engine_owner[ring_id]) अणु
			/* Switch ring from host to vGPU or vGPU to vGPU. */
			पूर्णांकel_gvt_चयन_mmio(scheduler->engine_owner[ring_id],
					      workload->vgpu, rq->engine);
			scheduler->engine_owner[ring_id] = workload->vgpu;
		पूर्ण अन्यथा
			gvt_dbg_sched("skip ring %d mmio switch for vgpu%d\n",
				      ring_id, workload->vgpu->id);
		spin_unlock_irqrestore(&scheduler->mmio_context_lock, flags);
		atomic_set(&workload->shaकरोw_ctx_active, 1);
		अवरोध;
	हाल INTEL_CONTEXT_SCHEDULE_OUT:
		save_ring_hw_state(workload->vgpu, rq->engine);
		atomic_set(&workload->shaकरोw_ctx_active, 0);
		अवरोध;
	हाल INTEL_CONTEXT_SCHEDULE_PREEMPTED:
		save_ring_hw_state(workload->vgpu, rq->engine);
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस NOTIFY_OK;
	पूर्ण
	wake_up(&workload->shaकरोw_ctx_status_wq);
	वापस NOTIFY_OK;
पूर्ण

अटल व्योम
shaकरोw_context_descriptor_update(काष्ठा पूर्णांकel_context *ce,
				 काष्ठा पूर्णांकel_vgpu_workload *workload)
अणु
	u64 desc = ce->lrc.desc;

	/*
	 * Update bits 0-11 of the context descriptor which includes flags
	 * like GEN8_CTX_* cached in desc_ढाँचा
	 */
	desc &= ~(0x3ull << GEN8_CTX_ADDRESSING_MODE_SHIFT);
	desc |= (u64)workload->ctx_desc.addressing_mode <<
		GEN8_CTX_ADDRESSING_MODE_SHIFT;

	ce->lrc.desc = desc;
पूर्ण

अटल पूर्णांक copy_workload_to_ring_buffer(काष्ठा पूर्णांकel_vgpu_workload *workload)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = workload->vgpu;
	काष्ठा i915_request *req = workload->req;
	व्योम *shaकरोw_ring_buffer_va;
	u32 *cs;
	पूर्णांक err;

	अगर (IS_GEN(req->engine->i915, 9) && is_inhibit_context(req->context))
		पूर्णांकel_vgpu_restore_inhibit_context(vgpu, req);

	/*
	 * To track whether a request has started on HW, we can emit a
	 * bपढ़ोcrumb at the beginning of the request and check its
	 * समयline's HWSP to see अगर the bपढ़ोcrumb has advanced past the
	 * start of this request. Actually, the request must have the
	 * init_bपढ़ोcrumb अगर its समयline set has_init_bपढ़ो_crumb, or the
	 * scheduler might get a wrong state of it during reset. Since the
	 * requests from gvt always set the has_init_bपढ़ोcrumb flag, here
	 * need to करो the emit_init_bपढ़ोcrumb क्रम all the requests.
	 */
	अगर (req->engine->emit_init_bपढ़ोcrumb) अणु
		err = req->engine->emit_init_bपढ़ोcrumb(req);
		अगर (err) अणु
			gvt_vgpu_err("fail to emit init breadcrumb\n");
			वापस err;
		पूर्ण
	पूर्ण

	/* allocate shaकरोw ring buffer */
	cs = पूर्णांकel_ring_begin(workload->req, workload->rb_len / माप(u32));
	अगर (IS_ERR(cs)) अणु
		gvt_vgpu_err("fail to alloc size =%ld shadow  ring buffer\n",
			workload->rb_len);
		वापस PTR_ERR(cs);
	पूर्ण

	shaकरोw_ring_buffer_va = workload->shaकरोw_ring_buffer_va;

	/* get shaकरोw ring buffer va */
	workload->shaकरोw_ring_buffer_va = cs;

	स_नकल(cs, shaकरोw_ring_buffer_va,
			workload->rb_len);

	cs += workload->rb_len / माप(u32);
	पूर्णांकel_ring_advance(workload->req, cs);

	वापस 0;
पूर्ण

अटल व्योम release_shaकरोw_wa_ctx(काष्ठा पूर्णांकel_shaकरोw_wa_ctx *wa_ctx)
अणु
	अगर (!wa_ctx->indirect_ctx.obj)
		वापस;

	i915_gem_object_lock(wa_ctx->indirect_ctx.obj, शून्य);
	i915_gem_object_unpin_map(wa_ctx->indirect_ctx.obj);
	i915_gem_object_unlock(wa_ctx->indirect_ctx.obj);
	i915_gem_object_put(wa_ctx->indirect_ctx.obj);

	wa_ctx->indirect_ctx.obj = शून्य;
	wa_ctx->indirect_ctx.shaकरोw_va = शून्य;
पूर्ण

अटल व्योम set_dma_address(काष्ठा i915_page_directory *pd, dma_addr_t addr)
अणु
	काष्ठा scatterlist *sg = pd->pt.base->mm.pages->sgl;

	/* This is not a good idea */
	sg->dma_address = addr;
पूर्ण

अटल व्योम set_context_ppgtt_from_shaकरोw(काष्ठा पूर्णांकel_vgpu_workload *workload,
					  काष्ठा पूर्णांकel_context *ce)
अणु
	काष्ठा पूर्णांकel_vgpu_mm *mm = workload->shaकरोw_mm;
	काष्ठा i915_ppgtt *ppgtt = i915_vm_to_ppgtt(ce->vm);
	पूर्णांक i = 0;

	अगर (mm->ppgtt_mm.root_entry_type == GTT_TYPE_PPGTT_ROOT_L4_ENTRY) अणु
		set_dma_address(ppgtt->pd, mm->ppgtt_mm.shaकरोw_pdps[0]);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < GVT_RING_CTX_NR_PDPS; i++) अणु
			काष्ठा i915_page_directory * स्थिर pd =
				i915_pd_entry(ppgtt->pd, i);
			/* skip now as current i915 ppgtt alloc won't allocate
			   top level pdp क्रम non 4-level table, won't impact
			   shaकरोw ppgtt. */
			अगर (!pd)
				अवरोध;

			set_dma_address(pd, mm->ppgtt_mm.shaकरोw_pdps[i]);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक
पूर्णांकel_gvt_workload_req_alloc(काष्ठा पूर्णांकel_vgpu_workload *workload)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = workload->vgpu;
	काष्ठा पूर्णांकel_vgpu_submission *s = &vgpu->submission;
	काष्ठा i915_request *rq;

	अगर (workload->req)
		वापस 0;

	rq = i915_request_create(s->shaकरोw[workload->engine->id]);
	अगर (IS_ERR(rq)) अणु
		gvt_vgpu_err("fail to allocate gem request\n");
		वापस PTR_ERR(rq);
	पूर्ण

	workload->req = i915_request_get(rq);
	वापस 0;
पूर्ण

/**
 * पूर्णांकel_gvt_scan_and_shaकरोw_workload - audit the workload by scanning and
 * shaकरोw it as well, include ringbuffer,wa_ctx and ctx.
 * @workload: an असलtract entity क्रम each execlist submission.
 *
 * This function is called beक्रमe the workload submitting to i915, to make
 * sure the content of the workload is valid.
 */
पूर्णांक पूर्णांकel_gvt_scan_and_shaकरोw_workload(काष्ठा पूर्णांकel_vgpu_workload *workload)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = workload->vgpu;
	काष्ठा पूर्णांकel_vgpu_submission *s = &vgpu->submission;
	पूर्णांक ret;

	lockdep_निश्चित_held(&vgpu->vgpu_lock);

	अगर (workload->shaकरोw)
		वापस 0;

	अगर (!test_and_set_bit(workload->engine->id, s->shaकरोw_ctx_desc_updated))
		shaकरोw_context_descriptor_update(s->shaकरोw[workload->engine->id],
						 workload);

	ret = पूर्णांकel_gvt_scan_and_shaकरोw_ringbuffer(workload);
	अगर (ret)
		वापस ret;

	अगर (workload->engine->id == RCS0 &&
	    workload->wa_ctx.indirect_ctx.size) अणु
		ret = पूर्णांकel_gvt_scan_and_shaकरोw_wa_ctx(&workload->wa_ctx);
		अगर (ret)
			जाओ err_shaकरोw;
	पूर्ण

	workload->shaकरोw = true;
	वापस 0;

err_shaकरोw:
	release_shaकरोw_wa_ctx(&workload->wa_ctx);
	वापस ret;
पूर्ण

अटल व्योम release_shaकरोw_batch_buffer(काष्ठा पूर्णांकel_vgpu_workload *workload);

अटल पूर्णांक prepare_shaकरोw_batch_buffer(काष्ठा पूर्णांकel_vgpu_workload *workload)
अणु
	काष्ठा पूर्णांकel_gvt *gvt = workload->vgpu->gvt;
	स्थिर पूर्णांक gmadr_bytes = gvt->device_info.gmadr_bytes_in_cmd;
	काष्ठा पूर्णांकel_vgpu_shaकरोw_bb *bb;
	काष्ठा i915_gem_ww_ctx ww;
	पूर्णांक ret;

	list_क्रम_each_entry(bb, &workload->shaकरोw_bb, list) अणु
		/* For privilge batch buffer and not wa_ctx, the bb_start_cmd_va
		 * is only updated पूर्णांकo ring_scan_buffer, not real ring address
		 * allocated in later copy_workload_to_ring_buffer. pls be noted
		 * shaकरोw_ring_buffer_va is now poपूर्णांकed to real ring buffer va
		 * in copy_workload_to_ring_buffer.
		 */

		अगर (bb->bb_offset)
			bb->bb_start_cmd_va = workload->shaकरोw_ring_buffer_va
				+ bb->bb_offset;

		/*
		 * For non-priv bb, scan&shaकरोw is only क्रम
		 * debugging purpose, so the content of shaकरोw bb
		 * is the same as original bb. Thereक्रमe,
		 * here, rather than चयन to shaकरोw bb's gma
		 * address, we directly use original batch buffer's
		 * gma address, and send original bb to hardware
		 * directly
		 */
		अगर (!bb->ppgtt) अणु
			i915_gem_ww_ctx_init(&ww, false);
retry:
			i915_gem_object_lock(bb->obj, &ww);

			bb->vma = i915_gem_object_ggtt_pin_ww(bb->obj, &ww,
							      शून्य, 0, 0, 0);
			अगर (IS_ERR(bb->vma)) अणु
				ret = PTR_ERR(bb->vma);
				अगर (ret == -EDEADLK) अणु
					ret = i915_gem_ww_ctx_backoff(&ww);
					अगर (!ret)
						जाओ retry;
				पूर्ण
				जाओ err;
			पूर्ण

			/* relocate shaकरोw batch buffer */
			bb->bb_start_cmd_va[1] = i915_ggtt_offset(bb->vma);
			अगर (gmadr_bytes == 8)
				bb->bb_start_cmd_va[2] = 0;

			ret = i915_vma_move_to_active(bb->vma,
						      workload->req,
						      0);
			अगर (ret)
				जाओ err;

			/* No one is going to touch shaकरोw bb from now on. */
			i915_gem_object_flush_map(bb->obj);
			i915_gem_object_unlock(bb->obj);
		पूर्ण
	पूर्ण
	वापस 0;
err:
	i915_gem_ww_ctx_fini(&ww);
	release_shaकरोw_batch_buffer(workload);
	वापस ret;
पूर्ण

अटल व्योम update_wa_ctx_2_shaकरोw_ctx(काष्ठा पूर्णांकel_shaकरोw_wa_ctx *wa_ctx)
अणु
	काष्ठा पूर्णांकel_vgpu_workload *workload =
		container_of(wa_ctx, काष्ठा पूर्णांकel_vgpu_workload, wa_ctx);
	काष्ठा i915_request *rq = workload->req;
	काष्ठा execlist_ring_context *shaकरोw_ring_context =
		(काष्ठा execlist_ring_context *)rq->context->lrc_reg_state;

	shaकरोw_ring_context->bb_per_ctx_ptr.val =
		(shaकरोw_ring_context->bb_per_ctx_ptr.val &
		(~PER_CTX_ADDR_MASK)) | wa_ctx->per_ctx.shaकरोw_gma;
	shaकरोw_ring_context->rcs_indirect_ctx.val =
		(shaकरोw_ring_context->rcs_indirect_ctx.val &
		(~INसूचीECT_CTX_ADDR_MASK)) | wa_ctx->indirect_ctx.shaकरोw_gma;
पूर्ण

अटल पूर्णांक prepare_shaकरोw_wa_ctx(काष्ठा पूर्णांकel_shaकरोw_wa_ctx *wa_ctx)
अणु
	काष्ठा i915_vma *vma;
	अचिन्हित अक्षर *per_ctx_va =
		(अचिन्हित अक्षर *)wa_ctx->indirect_ctx.shaकरोw_va +
		wa_ctx->indirect_ctx.size;
	काष्ठा i915_gem_ww_ctx ww;
	पूर्णांक ret;

	अगर (wa_ctx->indirect_ctx.size == 0)
		वापस 0;

	i915_gem_ww_ctx_init(&ww, false);
retry:
	i915_gem_object_lock(wa_ctx->indirect_ctx.obj, &ww);

	vma = i915_gem_object_ggtt_pin_ww(wa_ctx->indirect_ctx.obj, &ww, शून्य,
					  0, CACHELINE_BYTES, 0);
	अगर (IS_ERR(vma)) अणु
		ret = PTR_ERR(vma);
		अगर (ret == -EDEADLK) अणु
			ret = i915_gem_ww_ctx_backoff(&ww);
			अगर (!ret)
				जाओ retry;
		पूर्ण
		वापस ret;
	पूर्ण

	i915_gem_object_unlock(wa_ctx->indirect_ctx.obj);

	/* FIXME: we are not tracking our pinned VMA leaving it
	 * up to the core to fix up the stray pin_count upon
	 * मुक्त.
	 */

	wa_ctx->indirect_ctx.shaकरोw_gma = i915_ggtt_offset(vma);

	wa_ctx->per_ctx.shaकरोw_gma = *((अचिन्हित पूर्णांक *)per_ctx_va + 1);
	स_रखो(per_ctx_va, 0, CACHELINE_BYTES);

	update_wa_ctx_2_shaकरोw_ctx(wa_ctx);
	वापस 0;
पूर्ण

अटल व्योम update_vreg_in_ctx(काष्ठा पूर्णांकel_vgpu_workload *workload)
अणु
	vgpu_vreg_t(workload->vgpu, RING_START(workload->engine->mmio_base)) =
		workload->rb_start;
पूर्ण

अटल व्योम release_shaकरोw_batch_buffer(काष्ठा पूर्णांकel_vgpu_workload *workload)
अणु
	काष्ठा पूर्णांकel_vgpu_shaकरोw_bb *bb, *pos;

	अगर (list_empty(&workload->shaकरोw_bb))
		वापस;

	bb = list_first_entry(&workload->shaकरोw_bb,
			काष्ठा पूर्णांकel_vgpu_shaकरोw_bb, list);

	list_क्रम_each_entry_safe(bb, pos, &workload->shaकरोw_bb, list) अणु
		अगर (bb->obj) अणु
			i915_gem_object_lock(bb->obj, शून्य);
			अगर (bb->va && !IS_ERR(bb->va))
				i915_gem_object_unpin_map(bb->obj);

			अगर (bb->vma && !IS_ERR(bb->vma))
				i915_vma_unpin(bb->vma);

			i915_gem_object_unlock(bb->obj);
			i915_gem_object_put(bb->obj);
		पूर्ण
		list_del(&bb->list);
		kमुक्त(bb);
	पूर्ण
पूर्ण

अटल पूर्णांक
पूर्णांकel_vgpu_shaकरोw_mm_pin(काष्ठा पूर्णांकel_vgpu_workload *workload)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = workload->vgpu;
	काष्ठा पूर्णांकel_vgpu_mm *m;
	पूर्णांक ret = 0;

	ret = पूर्णांकel_vgpu_pin_mm(workload->shaकरोw_mm);
	अगर (ret) अणु
		gvt_vgpu_err("fail to vgpu pin mm\n");
		वापस ret;
	पूर्ण

	अगर (workload->shaकरोw_mm->type != INTEL_GVT_MM_PPGTT ||
	    !workload->shaकरोw_mm->ppgtt_mm.shaकरोwed) अणु
		gvt_vgpu_err("workload shadow ppgtt isn't ready\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!list_empty(&workload->lri_shaकरोw_mm)) अणु
		list_क्रम_each_entry(m, &workload->lri_shaकरोw_mm,
				    ppgtt_mm.link) अणु
			ret = पूर्णांकel_vgpu_pin_mm(m);
			अगर (ret) अणु
				list_क्रम_each_entry_from_reverse(m,
								 &workload->lri_shaकरोw_mm,
								 ppgtt_mm.link)
					पूर्णांकel_vgpu_unpin_mm(m);
				gvt_vgpu_err("LRI shadow ppgtt fail to pin\n");
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (ret)
		पूर्णांकel_vgpu_unpin_mm(workload->shaकरोw_mm);

	वापस ret;
पूर्ण

अटल व्योम
पूर्णांकel_vgpu_shaकरोw_mm_unpin(काष्ठा पूर्णांकel_vgpu_workload *workload)
अणु
	काष्ठा पूर्णांकel_vgpu_mm *m;

	अगर (!list_empty(&workload->lri_shaकरोw_mm)) अणु
		list_क्रम_each_entry(m, &workload->lri_shaकरोw_mm,
				    ppgtt_mm.link)
			पूर्णांकel_vgpu_unpin_mm(m);
	पूर्ण
	पूर्णांकel_vgpu_unpin_mm(workload->shaकरोw_mm);
पूर्ण

अटल पूर्णांक prepare_workload(काष्ठा पूर्णांकel_vgpu_workload *workload)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = workload->vgpu;
	काष्ठा पूर्णांकel_vgpu_submission *s = &vgpu->submission;
	पूर्णांक ret = 0;

	ret = पूर्णांकel_vgpu_shaकरोw_mm_pin(workload);
	अगर (ret) अणु
		gvt_vgpu_err("fail to pin shadow mm\n");
		वापस ret;
	पूर्ण

	update_shaकरोw_pdps(workload);

	set_context_ppgtt_from_shaकरोw(workload, s->shaकरोw[workload->engine->id]);

	ret = पूर्णांकel_vgpu_sync_oos_pages(workload->vgpu);
	अगर (ret) अणु
		gvt_vgpu_err("fail to vgpu sync oos pages\n");
		जाओ err_unpin_mm;
	पूर्ण

	ret = पूर्णांकel_vgpu_flush_post_shaकरोw(workload->vgpu);
	अगर (ret) अणु
		gvt_vgpu_err("fail to flush post shadow\n");
		जाओ err_unpin_mm;
	पूर्ण

	ret = copy_workload_to_ring_buffer(workload);
	अगर (ret) अणु
		gvt_vgpu_err("fail to generate request\n");
		जाओ err_unpin_mm;
	पूर्ण

	ret = prepare_shaकरोw_batch_buffer(workload);
	अगर (ret) अणु
		gvt_vgpu_err("fail to prepare_shadow_batch_buffer\n");
		जाओ err_unpin_mm;
	पूर्ण

	ret = prepare_shaकरोw_wa_ctx(&workload->wa_ctx);
	अगर (ret) अणु
		gvt_vgpu_err("fail to prepare_shadow_wa_ctx\n");
		जाओ err_shaकरोw_batch;
	पूर्ण

	अगर (workload->prepare) अणु
		ret = workload->prepare(workload);
		अगर (ret)
			जाओ err_shaकरोw_wa_ctx;
	पूर्ण

	वापस 0;
err_shaकरोw_wa_ctx:
	release_shaकरोw_wa_ctx(&workload->wa_ctx);
err_shaकरोw_batch:
	release_shaकरोw_batch_buffer(workload);
err_unpin_mm:
	पूर्णांकel_vgpu_shaकरोw_mm_unpin(workload);
	वापस ret;
पूर्ण

अटल पूर्णांक dispatch_workload(काष्ठा पूर्णांकel_vgpu_workload *workload)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = workload->vgpu;
	काष्ठा i915_request *rq;
	पूर्णांक ret;

	gvt_dbg_sched("ring id %s prepare to dispatch workload %p\n",
		      workload->engine->name, workload);

	mutex_lock(&vgpu->vgpu_lock);

	ret = पूर्णांकel_gvt_workload_req_alloc(workload);
	अगर (ret)
		जाओ err_req;

	ret = पूर्णांकel_gvt_scan_and_shaकरोw_workload(workload);
	अगर (ret)
		जाओ out;

	ret = populate_shaकरोw_context(workload);
	अगर (ret) अणु
		release_shaकरोw_wa_ctx(&workload->wa_ctx);
		जाओ out;
	पूर्ण

	ret = prepare_workload(workload);
out:
	अगर (ret) अणु
		/* We might still need to add request with
		 * clean ctx to retire it properly..
		 */
		rq = fetch_and_zero(&workload->req);
		i915_request_put(rq);
	पूर्ण

	अगर (!IS_ERR_OR_शून्य(workload->req)) अणु
		gvt_dbg_sched("ring id %s submit workload to i915 %p\n",
			      workload->engine->name, workload->req);
		i915_request_add(workload->req);
		workload->dispatched = true;
	पूर्ण
err_req:
	अगर (ret)
		workload->status = ret;
	mutex_unlock(&vgpu->vgpu_lock);
	वापस ret;
पूर्ण

अटल काष्ठा पूर्णांकel_vgpu_workload *
pick_next_workload(काष्ठा पूर्णांकel_gvt *gvt, काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_gvt_workload_scheduler *scheduler = &gvt->scheduler;
	काष्ठा पूर्णांकel_vgpu_workload *workload = शून्य;

	mutex_lock(&gvt->sched_lock);

	/*
	 * no current vgpu / will be scheduled out / no workload
	 * bail out
	 */
	अगर (!scheduler->current_vgpu) अणु
		gvt_dbg_sched("ring %s stop - no current vgpu\n", engine->name);
		जाओ out;
	पूर्ण

	अगर (scheduler->need_reschedule) अणु
		gvt_dbg_sched("ring %s stop - will reschedule\n", engine->name);
		जाओ out;
	पूर्ण

	अगर (!scheduler->current_vgpu->active ||
	    list_empty(workload_q_head(scheduler->current_vgpu, engine)))
		जाओ out;

	/*
	 * still have current workload, maybe the workload disptacher
	 * fail to submit it क्रम some reason, resubmit it.
	 */
	अगर (scheduler->current_workload[engine->id]) अणु
		workload = scheduler->current_workload[engine->id];
		gvt_dbg_sched("ring %s still have current workload %p\n",
			      engine->name, workload);
		जाओ out;
	पूर्ण

	/*
	 * pick a workload as current workload
	 * once current workload is set, schedule policy routines
	 * will रुको the current workload is finished when trying to
	 * schedule out a vgpu.
	 */
	scheduler->current_workload[engine->id] =
		list_first_entry(workload_q_head(scheduler->current_vgpu,
						 engine),
				 काष्ठा पूर्णांकel_vgpu_workload, list);

	workload = scheduler->current_workload[engine->id];

	gvt_dbg_sched("ring %s pick new workload %p\n", engine->name, workload);

	atomic_inc(&workload->vgpu->submission.running_workload_num);
out:
	mutex_unlock(&gvt->sched_lock);
	वापस workload;
पूर्ण

अटल व्योम update_guest_pdps(काष्ठा पूर्णांकel_vgpu *vgpu,
			      u64 ring_context_gpa, u32 pdp[8])
अणु
	u64 gpa;
	पूर्णांक i;

	gpa = ring_context_gpa + RING_CTX_OFF(pdps[0].val);

	क्रम (i = 0; i < 8; i++)
		पूर्णांकel_gvt_hypervisor_ग_लिखो_gpa(vgpu,
				gpa + i * 8, &pdp[7 - i], 4);
पूर्ण

अटल __maybe_unused bool
check_shaकरोw_context_ppgtt(काष्ठा execlist_ring_context *c, काष्ठा पूर्णांकel_vgpu_mm *m)
अणु
	अगर (m->ppgtt_mm.root_entry_type == GTT_TYPE_PPGTT_ROOT_L4_ENTRY) अणु
		u64 shaकरोw_pdp = c->pdps[7].val | (u64) c->pdps[6].val << 32;

		अगर (shaकरोw_pdp != m->ppgtt_mm.shaकरोw_pdps[0]) अणु
			gvt_dbg_mm("4-level context ppgtt not match LRI command\n");
			वापस false;
		पूर्ण
		वापस true;
	पूर्ण अन्यथा अणु
		/* see comment in LRI handler in cmd_parser.c */
		gvt_dbg_mm("invalid shadow mm type\n");
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम update_guest_context(काष्ठा पूर्णांकel_vgpu_workload *workload)
अणु
	काष्ठा i915_request *rq = workload->req;
	काष्ठा पूर्णांकel_vgpu *vgpu = workload->vgpu;
	काष्ठा execlist_ring_context *shaकरोw_ring_context;
	काष्ठा पूर्णांकel_context *ctx = workload->req->context;
	व्योम *context_base;
	व्योम *src;
	अचिन्हित दीर्घ context_gpa, context_page_num;
	अचिन्हित दीर्घ gpa_base; /* first gpa of consecutive GPAs */
	अचिन्हित दीर्घ gpa_size; /* size of consecutive GPAs*/
	पूर्णांक i;
	u32 ring_base;
	u32 head, tail;
	u16 wrap_count;

	gvt_dbg_sched("ring id %d workload lrca %x\n", rq->engine->id,
		      workload->ctx_desc.lrca);

	GEM_BUG_ON(!पूर्णांकel_context_is_pinned(ctx));

	head = workload->rb_head;
	tail = workload->rb_tail;
	wrap_count = workload->guest_rb_head >> RB_HEAD_WRAP_CNT_OFF;

	अगर (tail < head) अणु
		अगर (wrap_count == RB_HEAD_WRAP_CNT_MAX)
			wrap_count = 0;
		अन्यथा
			wrap_count += 1;
	पूर्ण

	head = (wrap_count << RB_HEAD_WRAP_CNT_OFF) | tail;

	ring_base = rq->engine->mmio_base;
	vgpu_vreg_t(vgpu, RING_TAIL(ring_base)) = tail;
	vgpu_vreg_t(vgpu, RING_HEAD(ring_base)) = head;

	context_page_num = rq->engine->context_size;
	context_page_num = context_page_num >> PAGE_SHIFT;

	अगर (IS_BROADWELL(rq->engine->i915) && rq->engine->id == RCS0)
		context_page_num = 19;

	context_base = (व्योम *) ctx->lrc_reg_state -
			(LRC_STATE_PN << I915_GTT_PAGE_SHIFT);

	/* find consecutive GPAs from gma until the first inconsecutive GPA.
	 * ग_लिखो to the consecutive GPAs from src भव address
	 */
	gpa_size = 0;
	क्रम (i = 2; i < context_page_num; i++) अणु
		context_gpa = पूर्णांकel_vgpu_gma_to_gpa(vgpu->gtt.ggtt_mm,
				(u32)((workload->ctx_desc.lrca + i) <<
					I915_GTT_PAGE_SHIFT));
		अगर (context_gpa == INTEL_GVT_INVALID_ADDR) अणु
			gvt_vgpu_err("invalid guest context descriptor\n");
			वापस;
		पूर्ण

		अगर (gpa_size == 0) अणु
			gpa_base = context_gpa;
			src = context_base + (i << I915_GTT_PAGE_SHIFT);
		पूर्ण अन्यथा अगर (context_gpa != gpa_base + gpa_size)
			जाओ ग_लिखो;

		gpa_size += I915_GTT_PAGE_SIZE;

		अगर (i == context_page_num - 1)
			जाओ ग_लिखो;

		जारी;

ग_लिखो:
		पूर्णांकel_gvt_hypervisor_ग_लिखो_gpa(vgpu, gpa_base, src, gpa_size);
		gpa_base = context_gpa;
		gpa_size = I915_GTT_PAGE_SIZE;
		src = context_base + (i << I915_GTT_PAGE_SHIFT);
	पूर्ण

	पूर्णांकel_gvt_hypervisor_ग_लिखो_gpa(vgpu, workload->ring_context_gpa +
		RING_CTX_OFF(ring_header.val), &workload->rb_tail, 4);

	shaकरोw_ring_context = (व्योम *) ctx->lrc_reg_state;

	अगर (!list_empty(&workload->lri_shaकरोw_mm)) अणु
		काष्ठा पूर्णांकel_vgpu_mm *m = list_last_entry(&workload->lri_shaकरोw_mm,
							  काष्ठा पूर्णांकel_vgpu_mm,
							  ppgtt_mm.link);
		GEM_BUG_ON(!check_shaकरोw_context_ppgtt(shaकरोw_ring_context, m));
		update_guest_pdps(vgpu, workload->ring_context_gpa,
				  (व्योम *)m->ppgtt_mm.guest_pdps);
	पूर्ण

#घोषणा COPY_REG(name) \
	पूर्णांकel_gvt_hypervisor_ग_लिखो_gpa(vgpu, workload->ring_context_gpa + \
		RING_CTX_OFF(name.val), &shaकरोw_ring_context->name.val, 4)

	COPY_REG(ctx_ctrl);
	COPY_REG(ctx_बारtamp);

#अघोषित COPY_REG

	पूर्णांकel_gvt_hypervisor_ग_लिखो_gpa(vgpu,
			workload->ring_context_gpa +
			माप(*shaकरोw_ring_context),
			(व्योम *)shaकरोw_ring_context +
			माप(*shaकरोw_ring_context),
			I915_GTT_PAGE_SIZE - माप(*shaकरोw_ring_context));
पूर्ण

व्योम पूर्णांकel_vgpu_clean_workloads(काष्ठा पूर्णांकel_vgpu *vgpu,
				पूर्णांकel_engine_mask_t engine_mask)
अणु
	काष्ठा पूर्णांकel_vgpu_submission *s = &vgpu->submission;
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा पूर्णांकel_vgpu_workload *pos, *n;
	पूर्णांकel_engine_mask_t पंचांगp;

	/* मुक्त the unsubmited workloads in the queues. */
	क्रम_each_engine_masked(engine, vgpu->gvt->gt, engine_mask, पंचांगp) अणु
		list_क्रम_each_entry_safe(pos, n,
			&s->workload_q_head[engine->id], list) अणु
			list_del_init(&pos->list);
			पूर्णांकel_vgpu_destroy_workload(pos);
		पूर्ण
		clear_bit(engine->id, s->shaकरोw_ctx_desc_updated);
	पूर्ण
पूर्ण

अटल व्योम complete_current_workload(काष्ठा पूर्णांकel_gvt *gvt, पूर्णांक ring_id)
अणु
	काष्ठा पूर्णांकel_gvt_workload_scheduler *scheduler = &gvt->scheduler;
	काष्ठा पूर्णांकel_vgpu_workload *workload =
		scheduler->current_workload[ring_id];
	काष्ठा पूर्णांकel_vgpu *vgpu = workload->vgpu;
	काष्ठा पूर्णांकel_vgpu_submission *s = &vgpu->submission;
	काष्ठा i915_request *rq = workload->req;
	पूर्णांक event;

	mutex_lock(&vgpu->vgpu_lock);
	mutex_lock(&gvt->sched_lock);

	/* For the workload w/ request, needs to रुको क्रम the context
	 * चयन to make sure request is completed.
	 * For the workload w/o request, directly complete the workload.
	 */
	अगर (rq) अणु
		रुको_event(workload->shaकरोw_ctx_status_wq,
			   !atomic_पढ़ो(&workload->shaकरोw_ctx_active));

		/* If this request caused GPU hang, req->fence.error will
		 * be set to -EIO. Use -EIO to set workload status so
		 * that when this request caused GPU hang, didn't trigger
		 * context चयन पूर्णांकerrupt to guest.
		 */
		अगर (likely(workload->status == -EINPROGRESS)) अणु
			अगर (workload->req->fence.error == -EIO)
				workload->status = -EIO;
			अन्यथा
				workload->status = 0;
		पूर्ण

		अगर (!workload->status &&
		    !(vgpu->resetting_eng & BIT(ring_id))) अणु
			update_guest_context(workload);

			क्रम_each_set_bit(event, workload->pending_events,
					 INTEL_GVT_EVENT_MAX)
				पूर्णांकel_vgpu_trigger_भव_event(vgpu, event);
		पूर्ण

		i915_request_put(fetch_and_zero(&workload->req));
	पूर्ण

	gvt_dbg_sched("ring id %d complete workload %p status %d\n",
			ring_id, workload, workload->status);

	scheduler->current_workload[ring_id] = शून्य;

	list_del_init(&workload->list);

	अगर (workload->status || vgpu->resetting_eng & BIT(ring_id)) अणु
		/* अगर workload->status is not successful means HW GPU
		 * has occurred GPU hang or something wrong with i915/GVT,
		 * and GVT won't inject context चयन पूर्णांकerrupt to guest.
		 * So this error is a vGPU hang actually to the guest.
		 * According to this we should emunlate a vGPU hang. If
		 * there are pending workloads which are alपढ़ोy submitted
		 * from guest, we should clean them up like HW GPU करोes.
		 *
		 * अगर it is in middle of engine resetting, the pending
		 * workloads won't be submitted to HW GPU and will be
		 * cleaned up during the resetting process later, so करोing
		 * the workload clean up here करोesn't have any impact.
		 **/
		पूर्णांकel_vgpu_clean_workloads(vgpu, BIT(ring_id));
	पूर्ण

	workload->complete(workload);

	पूर्णांकel_vgpu_shaकरोw_mm_unpin(workload);
	पूर्णांकel_vgpu_destroy_workload(workload);

	atomic_dec(&s->running_workload_num);
	wake_up(&scheduler->workload_complete_wq);

	अगर (gvt->scheduler.need_reschedule)
		पूर्णांकel_gvt_request_service(gvt, INTEL_GVT_REQUEST_EVENT_SCHED);

	mutex_unlock(&gvt->sched_lock);
	mutex_unlock(&vgpu->vgpu_lock);
पूर्ण

अटल पूर्णांक workload_thपढ़ो(व्योम *arg)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine = arg;
	स्थिर bool need_क्रमce_wake = INTEL_GEN(engine->i915) >= 9;
	काष्ठा पूर्णांकel_gvt *gvt = engine->i915->gvt;
	काष्ठा पूर्णांकel_gvt_workload_scheduler *scheduler = &gvt->scheduler;
	काष्ठा पूर्णांकel_vgpu_workload *workload = शून्य;
	काष्ठा पूर्णांकel_vgpu *vgpu = शून्य;
	पूर्णांक ret;
	DEFINE_WAIT_FUNC(रुको, woken_wake_function);

	gvt_dbg_core("workload thread for ring %s started\n", engine->name);

	जबतक (!kthपढ़ो_should_stop()) अणु
		पूर्णांकel_wakeref_t wakeref;

		add_रुको_queue(&scheduler->रुकोq[engine->id], &रुको);
		करो अणु
			workload = pick_next_workload(gvt, engine);
			अगर (workload)
				अवरोध;
			रुको_woken(&रुको, TASK_INTERRUPTIBLE,
				   MAX_SCHEDULE_TIMEOUT);
		पूर्ण जबतक (!kthपढ़ो_should_stop());
		हटाओ_रुको_queue(&scheduler->रुकोq[engine->id], &रुको);

		अगर (!workload)
			अवरोध;

		gvt_dbg_sched("ring %s next workload %p vgpu %d\n",
			      engine->name, workload,
			      workload->vgpu->id);

		wakeref = पूर्णांकel_runसमय_pm_get(engine->uncore->rpm);

		gvt_dbg_sched("ring %s will dispatch workload %p\n",
			      engine->name, workload);

		अगर (need_क्रमce_wake)
			पूर्णांकel_uncore_क्रमcewake_get(engine->uncore,
						   FORCEWAKE_ALL);
		/*
		 * Update the vReg of the vGPU which submitted this
		 * workload. The vGPU may use these रेजिस्टरs क्रम checking
		 * the context state. The value comes from GPU commands
		 * in this workload.
		 */
		update_vreg_in_ctx(workload);

		ret = dispatch_workload(workload);

		अगर (ret) अणु
			vgpu = workload->vgpu;
			gvt_vgpu_err("fail to dispatch workload, skip\n");
			जाओ complete;
		पूर्ण

		gvt_dbg_sched("ring %s wait workload %p\n",
			      engine->name, workload);
		i915_request_रुको(workload->req, 0, MAX_SCHEDULE_TIMEOUT);

complete:
		gvt_dbg_sched("will complete workload %p, status: %d\n",
			      workload, workload->status);

		complete_current_workload(gvt, engine->id);

		अगर (need_क्रमce_wake)
			पूर्णांकel_uncore_क्रमcewake_put(engine->uncore,
						   FORCEWAKE_ALL);

		पूर्णांकel_runसमय_pm_put(engine->uncore->rpm, wakeref);
		अगर (ret && (vgpu_is_vm_unhealthy(ret)))
			enter_failsafe_mode(vgpu, GVT_FAILSAFE_GUEST_ERR);
	पूर्ण
	वापस 0;
पूर्ण

व्योम पूर्णांकel_gvt_रुको_vgpu_idle(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा पूर्णांकel_vgpu_submission *s = &vgpu->submission;
	काष्ठा पूर्णांकel_gvt *gvt = vgpu->gvt;
	काष्ठा पूर्णांकel_gvt_workload_scheduler *scheduler = &gvt->scheduler;

	अगर (atomic_पढ़ो(&s->running_workload_num)) अणु
		gvt_dbg_sched("wait vgpu idle\n");

		रुको_event(scheduler->workload_complete_wq,
				!atomic_पढ़ो(&s->running_workload_num));
	पूर्ण
पूर्ण

व्योम पूर्णांकel_gvt_clean_workload_scheduler(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	काष्ठा पूर्णांकel_gvt_workload_scheduler *scheduler = &gvt->scheduler;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id i;

	gvt_dbg_core("clean workload scheduler\n");

	क्रम_each_engine(engine, gvt->gt, i) अणु
		atomic_notअगरier_chain_unरेजिस्टर(
					&engine->context_status_notअगरier,
					&gvt->shaकरोw_ctx_notअगरier_block[i]);
		kthपढ़ो_stop(scheduler->thपढ़ो[i]);
	पूर्ण
पूर्ण

पूर्णांक पूर्णांकel_gvt_init_workload_scheduler(काष्ठा पूर्णांकel_gvt *gvt)
अणु
	काष्ठा पूर्णांकel_gvt_workload_scheduler *scheduler = &gvt->scheduler;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id i;
	पूर्णांक ret;

	gvt_dbg_core("init workload scheduler\n");

	init_रुकोqueue_head(&scheduler->workload_complete_wq);

	क्रम_each_engine(engine, gvt->gt, i) अणु
		init_रुकोqueue_head(&scheduler->रुकोq[i]);

		scheduler->thपढ़ो[i] = kthपढ़ो_run(workload_thपढ़ो, engine,
						   "gvt:%s", engine->name);
		अगर (IS_ERR(scheduler->thपढ़ो[i])) अणु
			gvt_err("fail to create workload thread\n");
			ret = PTR_ERR(scheduler->thपढ़ो[i]);
			जाओ err;
		पूर्ण

		gvt->shaकरोw_ctx_notअगरier_block[i].notअगरier_call =
					shaकरोw_context_status_change;
		atomic_notअगरier_chain_रेजिस्टर(&engine->context_status_notअगरier,
					&gvt->shaकरोw_ctx_notअगरier_block[i]);
	पूर्ण

	वापस 0;

err:
	पूर्णांकel_gvt_clean_workload_scheduler(gvt);
	वापस ret;
पूर्ण

अटल व्योम
i915_context_ppgtt_root_restore(काष्ठा पूर्णांकel_vgpu_submission *s,
				काष्ठा i915_ppgtt *ppgtt)
अणु
	पूर्णांक i;

	अगर (i915_vm_is_4lvl(&ppgtt->vm)) अणु
		set_dma_address(ppgtt->pd, s->i915_context_pml4);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < GEN8_3LVL_PDPES; i++) अणु
			काष्ठा i915_page_directory * स्थिर pd =
				i915_pd_entry(ppgtt->pd, i);

			set_dma_address(pd, s->i915_context_pdps[i]);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * पूर्णांकel_vgpu_clean_submission - मुक्त submission-related resource क्रम vGPU
 * @vgpu: a vGPU
 *
 * This function is called when a vGPU is being destroyed.
 *
 */
व्योम पूर्णांकel_vgpu_clean_submission(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा पूर्णांकel_vgpu_submission *s = &vgpu->submission;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;

	पूर्णांकel_vgpu_select_submission_ops(vgpu, ALL_ENGINES, 0);

	i915_context_ppgtt_root_restore(s, i915_vm_to_ppgtt(s->shaकरोw[0]->vm));
	क्रम_each_engine(engine, vgpu->gvt->gt, id)
		पूर्णांकel_context_put(s->shaकरोw[id]);

	kmem_cache_destroy(s->workloads);
पूर्ण


/**
 * पूर्णांकel_vgpu_reset_submission - reset submission-related resource क्रम vGPU
 * @vgpu: a vGPU
 * @engine_mask: engines expected to be reset
 *
 * This function is called when a vGPU is being destroyed.
 *
 */
व्योम पूर्णांकel_vgpu_reset_submission(काष्ठा पूर्णांकel_vgpu *vgpu,
				 पूर्णांकel_engine_mask_t engine_mask)
अणु
	काष्ठा पूर्णांकel_vgpu_submission *s = &vgpu->submission;

	अगर (!s->active)
		वापस;

	पूर्णांकel_vgpu_clean_workloads(vgpu, engine_mask);
	s->ops->reset(vgpu, engine_mask);
पूर्ण

अटल व्योम
i915_context_ppgtt_root_save(काष्ठा पूर्णांकel_vgpu_submission *s,
			     काष्ठा i915_ppgtt *ppgtt)
अणु
	पूर्णांक i;

	अगर (i915_vm_is_4lvl(&ppgtt->vm)) अणु
		s->i915_context_pml4 = px_dma(ppgtt->pd);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < GEN8_3LVL_PDPES; i++) अणु
			काष्ठा i915_page_directory * स्थिर pd =
				i915_pd_entry(ppgtt->pd, i);

			s->i915_context_pdps[i] = px_dma(pd);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * पूर्णांकel_vgpu_setup_submission - setup submission-related resource क्रम vGPU
 * @vgpu: a vGPU
 *
 * This function is called when a vGPU is being created.
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 *
 */
पूर्णांक पूर्णांकel_vgpu_setup_submission(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा drm_i915_निजी *i915 = vgpu->gvt->gt->i915;
	काष्ठा पूर्णांकel_vgpu_submission *s = &vgpu->submission;
	काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा i915_ppgtt *ppgtt;
	क्रमागत पूर्णांकel_engine_id i;
	पूर्णांक ret;

	ppgtt = i915_ppgtt_create(&i915->gt);
	अगर (IS_ERR(ppgtt))
		वापस PTR_ERR(ppgtt);

	i915_context_ppgtt_root_save(s, ppgtt);

	क्रम_each_engine(engine, vgpu->gvt->gt, i) अणु
		काष्ठा पूर्णांकel_context *ce;

		INIT_LIST_HEAD(&s->workload_q_head[i]);
		s->shaकरोw[i] = ERR_PTR(-EINVAL);

		ce = पूर्णांकel_context_create(engine);
		अगर (IS_ERR(ce)) अणु
			ret = PTR_ERR(ce);
			जाओ out_shaकरोw_ctx;
		पूर्ण

		i915_vm_put(ce->vm);
		ce->vm = i915_vm_get(&ppgtt->vm);
		पूर्णांकel_context_set_single_submission(ce);

		/* Max ring buffer size */
		अगर (!पूर्णांकel_uc_wants_guc_submission(&engine->gt->uc)) अणु
			स्थिर अचिन्हित पूर्णांक ring_size = 512 * SZ_4K;

			ce->ring = __पूर्णांकel_context_ring_size(ring_size);
		पूर्ण

		s->shaकरोw[i] = ce;
	पूर्ण

	biपंचांगap_zero(s->shaकरोw_ctx_desc_updated, I915_NUM_ENGINES);

	s->workloads = kmem_cache_create_usercopy("gvt-g_vgpu_workload",
						  माप(काष्ठा पूर्णांकel_vgpu_workload), 0,
						  SLAB_HWCACHE_ALIGN,
						  दुरत्व(काष्ठा पूर्णांकel_vgpu_workload, rb_tail),
						  माप_field(काष्ठा पूर्णांकel_vgpu_workload, rb_tail),
						  शून्य);

	अगर (!s->workloads) अणु
		ret = -ENOMEM;
		जाओ out_shaकरोw_ctx;
	पूर्ण

	atomic_set(&s->running_workload_num, 0);
	biपंचांगap_zero(s->tlb_handle_pending, I915_NUM_ENGINES);

	स_रखो(s->last_ctx, 0, माप(s->last_ctx));

	i915_vm_put(&ppgtt->vm);
	वापस 0;

out_shaकरोw_ctx:
	i915_context_ppgtt_root_restore(s, ppgtt);
	क्रम_each_engine(engine, vgpu->gvt->gt, i) अणु
		अगर (IS_ERR(s->shaकरोw[i]))
			अवरोध;

		पूर्णांकel_context_put(s->shaकरोw[i]);
	पूर्ण
	i915_vm_put(&ppgtt->vm);
	वापस ret;
पूर्ण

/**
 * पूर्णांकel_vgpu_select_submission_ops - select भव submission पूर्णांकerface
 * @vgpu: a vGPU
 * @engine_mask: either ALL_ENGINES or target engine mask
 * @पूर्णांकerface: expected vGPU भव submission पूर्णांकerface
 *
 * This function is called when guest configures submission पूर्णांकerface.
 *
 * Returns:
 * Zero on success, negative error code अगर failed.
 *
 */
पूर्णांक पूर्णांकel_vgpu_select_submission_ops(काष्ठा पूर्णांकel_vgpu *vgpu,
				     पूर्णांकel_engine_mask_t engine_mask,
				     अचिन्हित पूर्णांक पूर्णांकerface)
अणु
	काष्ठा drm_i915_निजी *i915 = vgpu->gvt->gt->i915;
	काष्ठा पूर्णांकel_vgpu_submission *s = &vgpu->submission;
	स्थिर काष्ठा पूर्णांकel_vgpu_submission_ops *ops[] = अणु
		[INTEL_VGPU_EXECLIST_SUBMISSION] =
			&पूर्णांकel_vgpu_execlist_submission_ops,
	पूर्ण;
	पूर्णांक ret;

	अगर (drm_WARN_ON(&i915->drm, पूर्णांकerface >= ARRAY_SIZE(ops)))
		वापस -EINVAL;

	अगर (drm_WARN_ON(&i915->drm,
			पूर्णांकerface == 0 && engine_mask != ALL_ENGINES))
		वापस -EINVAL;

	अगर (s->active)
		s->ops->clean(vgpu, engine_mask);

	अगर (पूर्णांकerface == 0) अणु
		s->ops = शून्य;
		s->भव_submission_पूर्णांकerface = 0;
		s->active = false;
		gvt_dbg_core("vgpu%d: remove submission ops\n", vgpu->id);
		वापस 0;
	पूर्ण

	ret = ops[पूर्णांकerface]->init(vgpu, engine_mask);
	अगर (ret)
		वापस ret;

	s->ops = ops[पूर्णांकerface];
	s->भव_submission_पूर्णांकerface = पूर्णांकerface;
	s->active = true;

	gvt_dbg_core("vgpu%d: activate ops [ %s ]\n",
			vgpu->id, s->ops->name);

	वापस 0;
पूर्ण

/**
 * पूर्णांकel_vgpu_destroy_workload - destroy a vGPU workload
 * @workload: workload to destroy
 *
 * This function is called when destroy a vGPU workload.
 *
 */
व्योम पूर्णांकel_vgpu_destroy_workload(काष्ठा पूर्णांकel_vgpu_workload *workload)
अणु
	काष्ठा पूर्णांकel_vgpu_submission *s = &workload->vgpu->submission;

	पूर्णांकel_context_unpin(s->shaकरोw[workload->engine->id]);
	release_shaकरोw_batch_buffer(workload);
	release_shaकरोw_wa_ctx(&workload->wa_ctx);

	अगर (!list_empty(&workload->lri_shaकरोw_mm)) अणु
		काष्ठा पूर्णांकel_vgpu_mm *m, *mm;
		list_क्रम_each_entry_safe(m, mm, &workload->lri_shaकरोw_mm,
					 ppgtt_mm.link) अणु
			list_del(&m->ppgtt_mm.link);
			पूर्णांकel_vgpu_mm_put(m);
		पूर्ण
	पूर्ण

	GEM_BUG_ON(!list_empty(&workload->lri_shaकरोw_mm));
	अगर (workload->shaकरोw_mm)
		पूर्णांकel_vgpu_mm_put(workload->shaकरोw_mm);

	kmem_cache_मुक्त(s->workloads, workload);
पूर्ण

अटल काष्ठा पूर्णांकel_vgpu_workload *
alloc_workload(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	काष्ठा पूर्णांकel_vgpu_submission *s = &vgpu->submission;
	काष्ठा पूर्णांकel_vgpu_workload *workload;

	workload = kmem_cache_zalloc(s->workloads, GFP_KERNEL);
	अगर (!workload)
		वापस ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&workload->list);
	INIT_LIST_HEAD(&workload->shaकरोw_bb);
	INIT_LIST_HEAD(&workload->lri_shaकरोw_mm);

	init_रुकोqueue_head(&workload->shaकरोw_ctx_status_wq);
	atomic_set(&workload->shaकरोw_ctx_active, 0);

	workload->status = -EINPROGRESS;
	workload->vgpu = vgpu;

	वापस workload;
पूर्ण

#घोषणा RING_CTX_OFF(x) \
	दुरत्व(काष्ठा execlist_ring_context, x)

अटल व्योम पढ़ो_guest_pdps(काष्ठा पूर्णांकel_vgpu *vgpu,
		u64 ring_context_gpa, u32 pdp[8])
अणु
	u64 gpa;
	पूर्णांक i;

	gpa = ring_context_gpa + RING_CTX_OFF(pdps[0].val);

	क्रम (i = 0; i < 8; i++)
		पूर्णांकel_gvt_hypervisor_पढ़ो_gpa(vgpu,
				gpa + i * 8, &pdp[7 - i], 4);
पूर्ण

अटल पूर्णांक prepare_mm(काष्ठा पूर्णांकel_vgpu_workload *workload)
अणु
	काष्ठा execlist_ctx_descriptor_क्रमmat *desc = &workload->ctx_desc;
	काष्ठा पूर्णांकel_vgpu_mm *mm;
	काष्ठा पूर्णांकel_vgpu *vgpu = workload->vgpu;
	क्रमागत पूर्णांकel_gvt_gtt_type root_entry_type;
	u64 pdps[GVT_RING_CTX_NR_PDPS];

	चयन (desc->addressing_mode) अणु
	हाल 1: /* legacy 32-bit */
		root_entry_type = GTT_TYPE_PPGTT_ROOT_L3_ENTRY;
		अवरोध;
	हाल 3: /* legacy 64-bit */
		root_entry_type = GTT_TYPE_PPGTT_ROOT_L4_ENTRY;
		अवरोध;
	शेष:
		gvt_vgpu_err("Advanced Context mode(SVM) is not supported!\n");
		वापस -EINVAL;
	पूर्ण

	पढ़ो_guest_pdps(workload->vgpu, workload->ring_context_gpa, (व्योम *)pdps);

	mm = पूर्णांकel_vgpu_get_ppgtt_mm(workload->vgpu, root_entry_type, pdps);
	अगर (IS_ERR(mm))
		वापस PTR_ERR(mm);

	workload->shaकरोw_mm = mm;
	वापस 0;
पूर्ण

#घोषणा same_context(a, b) (((a)->context_id == (b)->context_id) && \
		((a)->lrca == (b)->lrca))

/**
 * पूर्णांकel_vgpu_create_workload - create a vGPU workload
 * @vgpu: a vGPU
 * @engine: the engine
 * @desc: a guest context descriptor
 *
 * This function is called when creating a vGPU workload.
 *
 * Returns:
 * काष्ठा पूर्णांकel_vgpu_workload * on success, negative error code in
 * poपूर्णांकer अगर failed.
 *
 */
काष्ठा पूर्णांकel_vgpu_workload *
पूर्णांकel_vgpu_create_workload(काष्ठा पूर्णांकel_vgpu *vgpu,
			   स्थिर काष्ठा पूर्णांकel_engine_cs *engine,
			   काष्ठा execlist_ctx_descriptor_क्रमmat *desc)
अणु
	काष्ठा पूर्णांकel_vgpu_submission *s = &vgpu->submission;
	काष्ठा list_head *q = workload_q_head(vgpu, engine);
	काष्ठा पूर्णांकel_vgpu_workload *last_workload = शून्य;
	काष्ठा पूर्णांकel_vgpu_workload *workload = शून्य;
	u64 ring_context_gpa;
	u32 head, tail, start, ctl, ctx_ctl, per_ctx, indirect_ctx;
	u32 guest_head;
	पूर्णांक ret;

	ring_context_gpa = पूर्णांकel_vgpu_gma_to_gpa(vgpu->gtt.ggtt_mm,
			(u32)((desc->lrca + 1) << I915_GTT_PAGE_SHIFT));
	अगर (ring_context_gpa == INTEL_GVT_INVALID_ADDR) अणु
		gvt_vgpu_err("invalid guest context LRCA: %x\n", desc->lrca);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	पूर्णांकel_gvt_hypervisor_पढ़ो_gpa(vgpu, ring_context_gpa +
			RING_CTX_OFF(ring_header.val), &head, 4);

	पूर्णांकel_gvt_hypervisor_पढ़ो_gpa(vgpu, ring_context_gpa +
			RING_CTX_OFF(ring_tail.val), &tail, 4);

	guest_head = head;

	head &= RB_HEAD_OFF_MASK;
	tail &= RB_TAIL_OFF_MASK;

	list_क्रम_each_entry_reverse(last_workload, q, list) अणु

		अगर (same_context(&last_workload->ctx_desc, desc)) अणु
			gvt_dbg_el("ring %s cur workload == last\n",
				   engine->name);
			gvt_dbg_el("ctx head %x real head %lx\n", head,
				   last_workload->rb_tail);
			/*
			 * cannot use guest context head poपूर्णांकer here,
			 * as it might not be updated at this समय
			 */
			head = last_workload->rb_tail;
			अवरोध;
		पूर्ण
	पूर्ण

	gvt_dbg_el("ring %s begin a new workload\n", engine->name);

	/* record some ring buffer रेजिस्टर values क्रम scan and shaकरोw */
	पूर्णांकel_gvt_hypervisor_पढ़ो_gpa(vgpu, ring_context_gpa +
			RING_CTX_OFF(rb_start.val), &start, 4);
	पूर्णांकel_gvt_hypervisor_पढ़ो_gpa(vgpu, ring_context_gpa +
			RING_CTX_OFF(rb_ctrl.val), &ctl, 4);
	पूर्णांकel_gvt_hypervisor_पढ़ो_gpa(vgpu, ring_context_gpa +
			RING_CTX_OFF(ctx_ctrl.val), &ctx_ctl, 4);

	अगर (!पूर्णांकel_gvt_ggtt_validate_range(vgpu, start,
				_RING_CTL_BUF_SIZE(ctl))) अणु
		gvt_vgpu_err("context contain invalid rb at: 0x%x\n", start);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	workload = alloc_workload(vgpu);
	अगर (IS_ERR(workload))
		वापस workload;

	workload->engine = engine;
	workload->ctx_desc = *desc;
	workload->ring_context_gpa = ring_context_gpa;
	workload->rb_head = head;
	workload->guest_rb_head = guest_head;
	workload->rb_tail = tail;
	workload->rb_start = start;
	workload->rb_ctl = ctl;

	अगर (engine->id == RCS0) अणु
		पूर्णांकel_gvt_hypervisor_पढ़ो_gpa(vgpu, ring_context_gpa +
			RING_CTX_OFF(bb_per_ctx_ptr.val), &per_ctx, 4);
		पूर्णांकel_gvt_hypervisor_पढ़ो_gpa(vgpu, ring_context_gpa +
			RING_CTX_OFF(rcs_indirect_ctx.val), &indirect_ctx, 4);

		workload->wa_ctx.indirect_ctx.guest_gma =
			indirect_ctx & INसूचीECT_CTX_ADDR_MASK;
		workload->wa_ctx.indirect_ctx.size =
			(indirect_ctx & INसूचीECT_CTX_SIZE_MASK) *
			CACHELINE_BYTES;

		अगर (workload->wa_ctx.indirect_ctx.size != 0) अणु
			अगर (!पूर्णांकel_gvt_ggtt_validate_range(vgpu,
				workload->wa_ctx.indirect_ctx.guest_gma,
				workload->wa_ctx.indirect_ctx.size)) अणु
				gvt_vgpu_err("invalid wa_ctx at: 0x%lx\n",
				    workload->wa_ctx.indirect_ctx.guest_gma);
				kmem_cache_मुक्त(s->workloads, workload);
				वापस ERR_PTR(-EINVAL);
			पूर्ण
		पूर्ण

		workload->wa_ctx.per_ctx.guest_gma =
			per_ctx & PER_CTX_ADDR_MASK;
		workload->wa_ctx.per_ctx.valid = per_ctx & 1;
		अगर (workload->wa_ctx.per_ctx.valid) अणु
			अगर (!पूर्णांकel_gvt_ggtt_validate_range(vgpu,
				workload->wa_ctx.per_ctx.guest_gma,
				CACHELINE_BYTES)) अणु
				gvt_vgpu_err("invalid per_ctx at: 0x%lx\n",
					workload->wa_ctx.per_ctx.guest_gma);
				kmem_cache_मुक्त(s->workloads, workload);
				वापस ERR_PTR(-EINVAL);
			पूर्ण
		पूर्ण
	पूर्ण

	gvt_dbg_el("workload %p ring %s head %x tail %x start %x ctl %x\n",
		   workload, engine->name, head, tail, start, ctl);

	ret = prepare_mm(workload);
	अगर (ret) अणु
		kmem_cache_मुक्त(s->workloads, workload);
		वापस ERR_PTR(ret);
	पूर्ण

	/* Only scan and shaकरोw the first workload in the queue
	 * as there is only one pre-allocated buf-obj क्रम shaकरोw.
	 */
	अगर (list_empty(q)) अणु
		पूर्णांकel_wakeref_t wakeref;

		with_पूर्णांकel_runसमय_pm(engine->gt->uncore->rpm, wakeref)
			ret = पूर्णांकel_gvt_scan_and_shaकरोw_workload(workload);
	पूर्ण

	अगर (ret) अणु
		अगर (vgpu_is_vm_unhealthy(ret))
			enter_failsafe_mode(vgpu, GVT_FAILSAFE_GUEST_ERR);
		पूर्णांकel_vgpu_destroy_workload(workload);
		वापस ERR_PTR(ret);
	पूर्ण

	ret = पूर्णांकel_context_pin(s->shaकरोw[engine->id]);
	अगर (ret) अणु
		पूर्णांकel_vgpu_destroy_workload(workload);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस workload;
पूर्ण

/**
 * पूर्णांकel_vgpu_queue_workload - Qeue a vGPU workload
 * @workload: the workload to queue in
 */
व्योम पूर्णांकel_vgpu_queue_workload(काष्ठा पूर्णांकel_vgpu_workload *workload)
अणु
	list_add_tail(&workload->list,
		      workload_q_head(workload->vgpu, workload->engine));
	पूर्णांकel_gvt_kick_schedule(workload->vgpu->gvt);
	wake_up(&workload->vgpu->gvt->scheduler.रुकोq[workload->engine->id]);
पूर्ण
