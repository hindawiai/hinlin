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

#अगर_अघोषित _GVT_SCHEDULER_H_
#घोषणा _GVT_SCHEDULER_H_

#समावेश "gt/intel_engine_types.h"

#समावेश "execlist.h"
#समावेश "interrupt.h"

काष्ठा पूर्णांकel_gvt_workload_scheduler अणु
	काष्ठा पूर्णांकel_vgpu *current_vgpu;
	काष्ठा पूर्णांकel_vgpu *next_vgpu;
	काष्ठा पूर्णांकel_vgpu_workload *current_workload[I915_NUM_ENGINES];
	bool need_reschedule;

	spinlock_t mmio_context_lock;
	/* can be null when owner is host */
	काष्ठा पूर्णांकel_vgpu *engine_owner[I915_NUM_ENGINES];

	रुको_queue_head_t workload_complete_wq;
	काष्ठा task_काष्ठा *thपढ़ो[I915_NUM_ENGINES];
	रुको_queue_head_t रुकोq[I915_NUM_ENGINES];

	व्योम *sched_data;
	काष्ठा पूर्णांकel_gvt_sched_policy_ops *sched_ops;
पूर्ण;

#घोषणा INसूचीECT_CTX_ADDR_MASK 0xffffffc0
#घोषणा INसूचीECT_CTX_SIZE_MASK 0x3f
काष्ठा shaकरोw_indirect_ctx अणु
	काष्ठा drm_i915_gem_object *obj;
	अचिन्हित दीर्घ guest_gma;
	अचिन्हित दीर्घ shaकरोw_gma;
	व्योम *shaकरोw_va;
	u32 size;
पूर्ण;

#घोषणा PER_CTX_ADDR_MASK 0xfffff000
काष्ठा shaकरोw_per_ctx अणु
	अचिन्हित दीर्घ guest_gma;
	अचिन्हित दीर्घ shaकरोw_gma;
	अचिन्हित valid;
पूर्ण;

काष्ठा पूर्णांकel_shaकरोw_wa_ctx अणु
	काष्ठा shaकरोw_indirect_ctx indirect_ctx;
	काष्ठा shaकरोw_per_ctx per_ctx;

पूर्ण;

काष्ठा पूर्णांकel_vgpu_workload अणु
	काष्ठा पूर्णांकel_vgpu *vgpu;
	स्थिर काष्ठा पूर्णांकel_engine_cs *engine;
	काष्ठा i915_request *req;
	/* अगर this workload has been dispatched to i915? */
	bool dispatched;
	bool shaकरोw;      /* अगर workload has करोne shaकरोw of guest request */
	पूर्णांक status;

	काष्ठा पूर्णांकel_vgpu_mm *shaकरोw_mm;
	काष्ठा list_head lri_shaकरोw_mm; /* For PPGTT load cmd */

	/* dअगरferent submission model may need dअगरferent handler */
	पूर्णांक (*prepare)(काष्ठा पूर्णांकel_vgpu_workload *);
	पूर्णांक (*complete)(काष्ठा पूर्णांकel_vgpu_workload *);
	काष्ठा list_head list;

	DECLARE_BITMAP(pending_events, INTEL_GVT_EVENT_MAX);
	व्योम *shaकरोw_ring_buffer_va;

	/* execlist context inक्रमmation */
	काष्ठा execlist_ctx_descriptor_क्रमmat ctx_desc;
	काष्ठा execlist_ring_context *ring_context;
	अचिन्हित दीर्घ rb_head, rb_tail, rb_ctl, rb_start, rb_len;
	अचिन्हित दीर्घ guest_rb_head;
	bool restore_inhibit;
	काष्ठा पूर्णांकel_vgpu_elsp_dwords elsp_dwords;
	bool emulate_schedule_in;
	atomic_t shaकरोw_ctx_active;
	रुको_queue_head_t shaकरोw_ctx_status_wq;
	u64 ring_context_gpa;

	/* shaकरोw batch buffer */
	काष्ठा list_head shaकरोw_bb;
	काष्ठा पूर्णांकel_shaकरोw_wa_ctx wa_ctx;

	/* oa रेजिस्टरs */
	u32 oactxctrl;
	u32 flex_mmio[7];
पूर्ण;

काष्ठा पूर्णांकel_vgpu_shaकरोw_bb अणु
	काष्ठा list_head list;
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_vma *vma;
	व्योम *va;
	u32 *bb_start_cmd_va;
	अचिन्हित दीर्घ bb_offset;
	bool ppgtt;
पूर्ण;

#घोषणा workload_q_head(vgpu, e) \
	(&(vgpu)->submission.workload_q_head[(e)->id])

व्योम पूर्णांकel_vgpu_queue_workload(काष्ठा पूर्णांकel_vgpu_workload *workload);

पूर्णांक पूर्णांकel_gvt_init_workload_scheduler(काष्ठा पूर्णांकel_gvt *gvt);

व्योम पूर्णांकel_gvt_clean_workload_scheduler(काष्ठा पूर्णांकel_gvt *gvt);

व्योम पूर्णांकel_gvt_रुको_vgpu_idle(काष्ठा पूर्णांकel_vgpu *vgpu);

पूर्णांक पूर्णांकel_vgpu_setup_submission(काष्ठा पूर्णांकel_vgpu *vgpu);

व्योम पूर्णांकel_vgpu_reset_submission(काष्ठा पूर्णांकel_vgpu *vgpu,
				 पूर्णांकel_engine_mask_t engine_mask);

व्योम पूर्णांकel_vgpu_clean_submission(काष्ठा पूर्णांकel_vgpu *vgpu);

पूर्णांक पूर्णांकel_vgpu_select_submission_ops(काष्ठा पूर्णांकel_vgpu *vgpu,
				     पूर्णांकel_engine_mask_t engine_mask,
				     अचिन्हित पूर्णांक पूर्णांकerface);

बाह्य स्थिर काष्ठा पूर्णांकel_vgpu_submission_ops
पूर्णांकel_vgpu_execlist_submission_ops;

काष्ठा पूर्णांकel_vgpu_workload *
पूर्णांकel_vgpu_create_workload(काष्ठा पूर्णांकel_vgpu *vgpu,
			   स्थिर काष्ठा पूर्णांकel_engine_cs *engine,
			   काष्ठा execlist_ctx_descriptor_क्रमmat *desc);

व्योम पूर्णांकel_vgpu_destroy_workload(काष्ठा पूर्णांकel_vgpu_workload *workload);

व्योम पूर्णांकel_vgpu_clean_workloads(काष्ठा पूर्णांकel_vgpu *vgpu,
				पूर्णांकel_engine_mask_t engine_mask);

#पूर्ण_अगर
