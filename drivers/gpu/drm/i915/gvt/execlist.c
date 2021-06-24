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
 *    Zhiyuan Lv <zhiyuan.lv@पूर्णांकel.com>
 *    Zhi Wang <zhi.a.wang@पूर्णांकel.com>
 *
 * Contributors:
 *    Min He <min.he@पूर्णांकel.com>
 *    Bing Niu <bing.niu@पूर्णांकel.com>
 *    Ping Gao <ping.a.gao@पूर्णांकel.com>
 *    Tina Zhang <tina.zhang@पूर्णांकel.com>
 *
 */

#समावेश "i915_drv.h"
#समावेश "gvt.h"

#घोषणा _EL_OFFSET_STATUS       0x234
#घोषणा _EL_OFFSET_STATUS_BUF   0x370
#घोषणा _EL_OFFSET_STATUS_PTR   0x3A0

#घोषणा execlist_ring_mmio(e, offset) ((e)->mmio_base + (offset))

#घोषणा valid_context(ctx) ((ctx)->valid)
#घोषणा same_context(a, b) (((a)->context_id == (b)->context_id) && \
		((a)->lrca == (b)->lrca))

अटल पूर्णांक context_चयन_events[] = अणु
	[RCS0]  = RCS_AS_CONTEXT_SWITCH,
	[BCS0]  = BCS_AS_CONTEXT_SWITCH,
	[VCS0]  = VCS_AS_CONTEXT_SWITCH,
	[VCS1]  = VCS2_AS_CONTEXT_SWITCH,
	[VECS0] = VECS_AS_CONTEXT_SWITCH,
पूर्ण;

अटल पूर्णांक to_context_चयन_event(स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	अगर (WARN_ON(engine->id >= ARRAY_SIZE(context_चयन_events)))
		वापस -EINVAL;

	वापस context_चयन_events[engine->id];
पूर्ण

अटल व्योम चयन_भव_execlist_slot(काष्ठा पूर्णांकel_vgpu_execlist *execlist)
अणु
	gvt_dbg_el("[before] running slot %d/context %x pending slot %d\n",
			execlist->running_slot ?
			execlist->running_slot->index : -1,
			execlist->running_context ?
			execlist->running_context->context_id : 0,
			execlist->pending_slot ?
			execlist->pending_slot->index : -1);

	execlist->running_slot = execlist->pending_slot;
	execlist->pending_slot = शून्य;
	execlist->running_context = execlist->running_context ?
		&execlist->running_slot->ctx[0] : शून्य;

	gvt_dbg_el("[after] running slot %d/context %x pending slot %d\n",
			execlist->running_slot ?
			execlist->running_slot->index : -1,
			execlist->running_context ?
			execlist->running_context->context_id : 0,
			execlist->pending_slot ?
			execlist->pending_slot->index : -1);
पूर्ण

अटल व्योम emulate_execlist_status(काष्ठा पूर्णांकel_vgpu_execlist *execlist)
अणु
	काष्ठा पूर्णांकel_vgpu_execlist_slot *running = execlist->running_slot;
	काष्ठा पूर्णांकel_vgpu_execlist_slot *pending = execlist->pending_slot;
	काष्ठा execlist_ctx_descriptor_क्रमmat *desc = execlist->running_context;
	काष्ठा पूर्णांकel_vgpu *vgpu = execlist->vgpu;
	काष्ठा execlist_status_क्रमmat status;
	u32 status_reg =
		execlist_ring_mmio(execlist->engine, _EL_OFFSET_STATUS);

	status.ldw = vgpu_vreg(vgpu, status_reg);
	status.udw = vgpu_vreg(vgpu, status_reg + 4);

	अगर (running) अणु
		status.current_execlist_poपूर्णांकer = !!running->index;
		status.execlist_ग_लिखो_poपूर्णांकer = !!!running->index;
		status.execlist_0_active = status.execlist_0_valid =
			!!!(running->index);
		status.execlist_1_active = status.execlist_1_valid =
			!!(running->index);
	पूर्ण अन्यथा अणु
		status.context_id = 0;
		status.execlist_0_active = status.execlist_0_valid = 0;
		status.execlist_1_active = status.execlist_1_valid = 0;
	पूर्ण

	status.context_id = desc ? desc->context_id : 0;
	status.execlist_queue_full = !!(pending);

	vgpu_vreg(vgpu, status_reg) = status.ldw;
	vgpu_vreg(vgpu, status_reg + 4) = status.udw;

	gvt_dbg_el("vgpu%d: status reg offset %x ldw %x udw %x\n",
		vgpu->id, status_reg, status.ldw, status.udw);
पूर्ण

अटल व्योम emulate_csb_update(काष्ठा पूर्णांकel_vgpu_execlist *execlist,
			       काष्ठा execlist_context_status_क्रमmat *status,
			       bool trigger_पूर्णांकerrupt_later)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = execlist->vgpu;
	काष्ठा execlist_context_status_poपूर्णांकer_क्रमmat ctx_status_ptr;
	u32 ग_लिखो_poपूर्णांकer;
	u32 ctx_status_ptr_reg, ctx_status_buf_reg, offset;
	अचिन्हित दीर्घ hwsp_gpa;

	ctx_status_ptr_reg =
		execlist_ring_mmio(execlist->engine, _EL_OFFSET_STATUS_PTR);
	ctx_status_buf_reg =
		execlist_ring_mmio(execlist->engine, _EL_OFFSET_STATUS_BUF);

	ctx_status_ptr.dw = vgpu_vreg(vgpu, ctx_status_ptr_reg);

	ग_लिखो_poपूर्णांकer = ctx_status_ptr.ग_लिखो_ptr;

	अगर (ग_लिखो_poपूर्णांकer == 0x7)
		ग_लिखो_poपूर्णांकer = 0;
	अन्यथा अणु
		++ग_लिखो_poपूर्णांकer;
		ग_लिखो_poपूर्णांकer %= 0x6;
	पूर्ण

	offset = ctx_status_buf_reg + ग_लिखो_poपूर्णांकer * 8;

	vgpu_vreg(vgpu, offset) = status->ldw;
	vgpu_vreg(vgpu, offset + 4) = status->udw;

	ctx_status_ptr.ग_लिखो_ptr = ग_लिखो_poपूर्णांकer;
	vgpu_vreg(vgpu, ctx_status_ptr_reg) = ctx_status_ptr.dw;

	/* Update the CSB and CSB ग_लिखो poपूर्णांकer in HWSP */
	hwsp_gpa = पूर्णांकel_vgpu_gma_to_gpa(vgpu->gtt.ggtt_mm,
					 vgpu->hws_pga[execlist->engine->id]);
	अगर (hwsp_gpa != INTEL_GVT_INVALID_ADDR) अणु
		पूर्णांकel_gvt_hypervisor_ग_लिखो_gpa(vgpu,
					       hwsp_gpa + I915_HWS_CSB_BUF0_INDEX * 4 + ग_लिखो_poपूर्णांकer * 8,
					       status, 8);
		पूर्णांकel_gvt_hypervisor_ग_लिखो_gpa(vgpu,
					       hwsp_gpa + पूर्णांकel_hws_csb_ग_लिखो_index(execlist->engine->i915) * 4,
					       &ग_लिखो_poपूर्णांकer, 4);
	पूर्ण

	gvt_dbg_el("vgpu%d: w pointer %u reg %x csb l %x csb h %x\n",
		   vgpu->id, ग_लिखो_poपूर्णांकer, offset, status->ldw, status->udw);

	अगर (trigger_पूर्णांकerrupt_later)
		वापस;

	पूर्णांकel_vgpu_trigger_भव_event(vgpu,
					 to_context_चयन_event(execlist->engine));
पूर्ण

अटल पूर्णांक emulate_execlist_ctx_schedule_out(
		काष्ठा पूर्णांकel_vgpu_execlist *execlist,
		काष्ठा execlist_ctx_descriptor_क्रमmat *ctx)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = execlist->vgpu;
	काष्ठा पूर्णांकel_vgpu_execlist_slot *running = execlist->running_slot;
	काष्ठा पूर्णांकel_vgpu_execlist_slot *pending = execlist->pending_slot;
	काष्ठा execlist_ctx_descriptor_क्रमmat *ctx0 = &running->ctx[0];
	काष्ठा execlist_ctx_descriptor_क्रमmat *ctx1 = &running->ctx[1];
	काष्ठा execlist_context_status_क्रमmat status;

	स_रखो(&status, 0, माप(status));

	gvt_dbg_el("schedule out context id %x\n", ctx->context_id);

	अगर (WARN_ON(!same_context(ctx, execlist->running_context))) अणु
		gvt_vgpu_err("schedule out context is not running context,"
				"ctx id %x running ctx id %x\n",
				ctx->context_id,
				execlist->running_context->context_id);
		वापस -EINVAL;
	पूर्ण

	/* ctx1 is valid, ctx0/ctx is scheduled-out -> element चयन */
	अगर (valid_context(ctx1) && same_context(ctx0, ctx)) अणु
		gvt_dbg_el("ctx 1 valid, ctx/ctx 0 is scheduled-out\n");

		execlist->running_context = ctx1;

		emulate_execlist_status(execlist);

		status.context_complete = status.element_चयन = 1;
		status.context_id = ctx->context_id;

		emulate_csb_update(execlist, &status, false);
		/*
		 * ctx1 is not valid, ctx == ctx0
		 * ctx1 is valid, ctx1 == ctx
		 *	--> last element is finished
		 * emulate:
		 *	active-to-idle अगर there is *no* pending execlist
		 *	context-complete अगर there *is* pending execlist
		 */
	पूर्ण अन्यथा अगर ((!valid_context(ctx1) && same_context(ctx0, ctx))
			|| (valid_context(ctx1) && same_context(ctx1, ctx))) अणु
		gvt_dbg_el("need to switch virtual execlist slot\n");

		चयन_भव_execlist_slot(execlist);

		emulate_execlist_status(execlist);

		status.context_complete = status.active_to_idle = 1;
		status.context_id = ctx->context_id;

		अगर (!pending) अणु
			emulate_csb_update(execlist, &status, false);
		पूर्ण अन्यथा अणु
			emulate_csb_update(execlist, &status, true);

			स_रखो(&status, 0, माप(status));

			status.idle_to_active = 1;
			status.context_id = 0;

			emulate_csb_update(execlist, &status, false);
		पूर्ण
	पूर्ण अन्यथा अणु
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा पूर्णांकel_vgpu_execlist_slot *get_next_execlist_slot(
		काष्ठा पूर्णांकel_vgpu_execlist *execlist)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = execlist->vgpu;
	u32 status_reg =
		execlist_ring_mmio(execlist->engine, _EL_OFFSET_STATUS);
	काष्ठा execlist_status_क्रमmat status;

	status.ldw = vgpu_vreg(vgpu, status_reg);
	status.udw = vgpu_vreg(vgpu, status_reg + 4);

	अगर (status.execlist_queue_full) अणु
		gvt_vgpu_err("virtual execlist slots are full\n");
		वापस शून्य;
	पूर्ण

	वापस &execlist->slot[status.execlist_ग_लिखो_poपूर्णांकer];
पूर्ण

अटल पूर्णांक emulate_execlist_schedule_in(काष्ठा पूर्णांकel_vgpu_execlist *execlist,
		काष्ठा execlist_ctx_descriptor_क्रमmat ctx[2])
अणु
	काष्ठा पूर्णांकel_vgpu_execlist_slot *running = execlist->running_slot;
	काष्ठा पूर्णांकel_vgpu_execlist_slot *slot =
		get_next_execlist_slot(execlist);

	काष्ठा execlist_ctx_descriptor_क्रमmat *ctx0, *ctx1;
	काष्ठा execlist_context_status_क्रमmat status;
	काष्ठा पूर्णांकel_vgpu *vgpu = execlist->vgpu;

	gvt_dbg_el("emulate schedule-in\n");

	अगर (!slot) अणु
		gvt_vgpu_err("no available execlist slot\n");
		वापस -EINVAL;
	पूर्ण

	स_रखो(&status, 0, माप(status));
	स_रखो(slot->ctx, 0, माप(slot->ctx));

	slot->ctx[0] = ctx[0];
	slot->ctx[1] = ctx[1];

	gvt_dbg_el("alloc slot index %d ctx 0 %x ctx 1 %x\n",
			slot->index, ctx[0].context_id,
			ctx[1].context_id);

	/*
	 * no running execlist, make this ग_लिखो bundle as running execlist
	 * -> idle-to-active
	 */
	अगर (!running) अणु
		gvt_dbg_el("no current running execlist\n");

		execlist->running_slot = slot;
		execlist->pending_slot = शून्य;
		execlist->running_context = &slot->ctx[0];

		gvt_dbg_el("running slot index %d running context %x\n",
				execlist->running_slot->index,
				execlist->running_context->context_id);

		emulate_execlist_status(execlist);

		status.idle_to_active = 1;
		status.context_id = 0;

		emulate_csb_update(execlist, &status, false);
		वापस 0;
	पूर्ण

	ctx0 = &running->ctx[0];
	ctx1 = &running->ctx[1];

	gvt_dbg_el("current running slot index %d ctx 0 %x ctx 1 %x\n",
		running->index, ctx0->context_id, ctx1->context_id);

	/*
	 * alपढ़ोy has an running execlist
	 *	a. running ctx1 is valid,
	 *	   ctx0 is finished, and running ctx1 == new execlist ctx[0]
	 *	b. running ctx1 is not valid,
	 *	   ctx0 == new execlist ctx[0]
	 * ----> lite-restore + preempted
	 */
	अगर ((valid_context(ctx1) && same_context(ctx1, &slot->ctx[0]) &&
		/* condition a */
		(!same_context(ctx0, execlist->running_context))) ||
			(!valid_context(ctx1) &&
			 same_context(ctx0, &slot->ctx[0]))) अणु /* condition b */
		gvt_dbg_el("need to switch virtual execlist slot\n");

		execlist->pending_slot = slot;
		चयन_भव_execlist_slot(execlist);

		emulate_execlist_status(execlist);

		status.lite_restore = status.preempted = 1;
		status.context_id = ctx[0].context_id;

		emulate_csb_update(execlist, &status, false);
	पूर्ण अन्यथा अणु
		gvt_dbg_el("emulate as pending slot\n");
		/*
		 * otherwise
		 * --> emulate pending execlist exist + but no preemption हाल
		 */
		execlist->pending_slot = slot;
		emulate_execlist_status(execlist);
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा get_desc_from_elsp_dwords(ed, i) \
	((काष्ठा execlist_ctx_descriptor_क्रमmat *)&((ed)->data[i * 2]))

अटल पूर्णांक prepare_execlist_workload(काष्ठा पूर्णांकel_vgpu_workload *workload)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = workload->vgpu;
	काष्ठा पूर्णांकel_vgpu_submission *s = &vgpu->submission;
	काष्ठा execlist_ctx_descriptor_क्रमmat ctx[2];
	पूर्णांक ret;

	अगर (!workload->emulate_schedule_in)
		वापस 0;

	ctx[0] = *get_desc_from_elsp_dwords(&workload->elsp_dwords, 0);
	ctx[1] = *get_desc_from_elsp_dwords(&workload->elsp_dwords, 1);

	ret = emulate_execlist_schedule_in(&s->execlist[workload->engine->id],
					   ctx);
	अगर (ret) अणु
		gvt_vgpu_err("fail to emulate execlist schedule in\n");
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक complete_execlist_workload(काष्ठा पूर्णांकel_vgpu_workload *workload)
अणु
	काष्ठा पूर्णांकel_vgpu *vgpu = workload->vgpu;
	काष्ठा पूर्णांकel_vgpu_submission *s = &vgpu->submission;
	काष्ठा पूर्णांकel_vgpu_execlist *execlist =
		&s->execlist[workload->engine->id];
	काष्ठा पूर्णांकel_vgpu_workload *next_workload;
	काष्ठा list_head *next = workload_q_head(vgpu, workload->engine)->next;
	bool lite_restore = false;
	पूर्णांक ret = 0;

	gvt_dbg_el("complete workload %p status %d\n",
		   workload, workload->status);

	अगर (workload->status || vgpu->resetting_eng & workload->engine->mask)
		जाओ out;

	अगर (!list_empty(workload_q_head(vgpu, workload->engine))) अणु
		काष्ठा execlist_ctx_descriptor_क्रमmat *this_desc, *next_desc;

		next_workload = container_of(next,
				काष्ठा पूर्णांकel_vgpu_workload, list);
		this_desc = &workload->ctx_desc;
		next_desc = &next_workload->ctx_desc;

		lite_restore = same_context(this_desc, next_desc);
	पूर्ण

	अगर (lite_restore) अणु
		gvt_dbg_el("next context == current - no schedule-out\n");
		जाओ out;
	पूर्ण

	ret = emulate_execlist_ctx_schedule_out(execlist, &workload->ctx_desc);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक submit_context(काष्ठा पूर्णांकel_vgpu *vgpu,
			  स्थिर काष्ठा पूर्णांकel_engine_cs *engine,
			  काष्ठा execlist_ctx_descriptor_क्रमmat *desc,
			  bool emulate_schedule_in)
अणु
	काष्ठा पूर्णांकel_vgpu_submission *s = &vgpu->submission;
	काष्ठा पूर्णांकel_vgpu_workload *workload = शून्य;

	workload = पूर्णांकel_vgpu_create_workload(vgpu, engine, desc);
	अगर (IS_ERR(workload))
		वापस PTR_ERR(workload);

	workload->prepare = prepare_execlist_workload;
	workload->complete = complete_execlist_workload;
	workload->emulate_schedule_in = emulate_schedule_in;

	अगर (emulate_schedule_in)
		workload->elsp_dwords = s->execlist[engine->id].elsp_dwords;

	gvt_dbg_el("workload %p emulate schedule_in %d\n", workload,
		   emulate_schedule_in);

	पूर्णांकel_vgpu_queue_workload(workload);
	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_vgpu_submit_execlist(काष्ठा पूर्णांकel_vgpu *vgpu,
			       स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_vgpu_submission *s = &vgpu->submission;
	काष्ठा पूर्णांकel_vgpu_execlist *execlist = &s->execlist[engine->id];
	काष्ठा execlist_ctx_descriptor_क्रमmat *desc[2];
	पूर्णांक i, ret;

	desc[0] = get_desc_from_elsp_dwords(&execlist->elsp_dwords, 0);
	desc[1] = get_desc_from_elsp_dwords(&execlist->elsp_dwords, 1);

	अगर (!desc[0]->valid) अणु
		gvt_vgpu_err("invalid elsp submission, desc0 is invalid\n");
		जाओ inv_desc;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(desc); i++) अणु
		अगर (!desc[i]->valid)
			जारी;
		अगर (!desc[i]->privilege_access) अणु
			gvt_vgpu_err("unexpected GGTT elsp submission\n");
			जाओ inv_desc;
		पूर्ण
	पूर्ण

	/* submit workload */
	क्रम (i = 0; i < ARRAY_SIZE(desc); i++) अणु
		अगर (!desc[i]->valid)
			जारी;
		ret = submit_context(vgpu, engine, desc[i], i == 0);
		अगर (ret) अणु
			gvt_vgpu_err("failed to submit desc %d\n", i);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;

inv_desc:
	gvt_vgpu_err("descriptors content: desc0 %08x %08x desc1 %08x %08x\n",
		     desc[0]->udw, desc[0]->ldw, desc[1]->udw, desc[1]->ldw);
	वापस -EINVAL;
पूर्ण

अटल व्योम init_vgpu_execlist(काष्ठा पूर्णांकel_vgpu *vgpu,
			       स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा पूर्णांकel_vgpu_submission *s = &vgpu->submission;
	काष्ठा पूर्णांकel_vgpu_execlist *execlist = &s->execlist[engine->id];
	काष्ठा execlist_context_status_poपूर्णांकer_क्रमmat ctx_status_ptr;
	u32 ctx_status_ptr_reg;

	स_रखो(execlist, 0, माप(*execlist));

	execlist->vgpu = vgpu;
	execlist->engine = engine;
	execlist->slot[0].index = 0;
	execlist->slot[1].index = 1;

	ctx_status_ptr_reg = execlist_ring_mmio(engine, _EL_OFFSET_STATUS_PTR);
	ctx_status_ptr.dw = vgpu_vreg(vgpu, ctx_status_ptr_reg);
	ctx_status_ptr.पढ़ो_ptr = 0;
	ctx_status_ptr.ग_लिखो_ptr = 0x7;
	vgpu_vreg(vgpu, ctx_status_ptr_reg) = ctx_status_ptr.dw;
पूर्ण

अटल व्योम clean_execlist(काष्ठा पूर्णांकel_vgpu *vgpu,
			   पूर्णांकel_engine_mask_t engine_mask)
अणु
	काष्ठा पूर्णांकel_vgpu_submission *s = &vgpu->submission;
	काष्ठा पूर्णांकel_engine_cs *engine;
	पूर्णांकel_engine_mask_t पंचांगp;

	क्रम_each_engine_masked(engine, vgpu->gvt->gt, engine_mask, पंचांगp) अणु
		kमुक्त(s->ring_scan_buffer[engine->id]);
		s->ring_scan_buffer[engine->id] = शून्य;
		s->ring_scan_buffer_size[engine->id] = 0;
	पूर्ण
पूर्ण

अटल व्योम reset_execlist(काष्ठा पूर्णांकel_vgpu *vgpu,
			   पूर्णांकel_engine_mask_t engine_mask)
अणु
	काष्ठा पूर्णांकel_engine_cs *engine;
	पूर्णांकel_engine_mask_t पंचांगp;

	क्रम_each_engine_masked(engine, vgpu->gvt->gt, engine_mask, पंचांगp)
		init_vgpu_execlist(vgpu, engine);
पूर्ण

अटल पूर्णांक init_execlist(काष्ठा पूर्णांकel_vgpu *vgpu,
			 पूर्णांकel_engine_mask_t engine_mask)
अणु
	reset_execlist(vgpu, engine_mask);
	वापस 0;
पूर्ण

स्थिर काष्ठा पूर्णांकel_vgpu_submission_ops पूर्णांकel_vgpu_execlist_submission_ops = अणु
	.name = "execlist",
	.init = init_execlist,
	.reset = reset_execlist,
	.clean = clean_execlist,
पूर्ण;
