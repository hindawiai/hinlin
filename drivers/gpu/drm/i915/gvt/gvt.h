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
 *    Kevin Tian <kevin.tian@पूर्णांकel.com>
 *    Eddie Dong <eddie.करोng@पूर्णांकel.com>
 *
 * Contributors:
 *    Niu Bing <bing.niu@पूर्णांकel.com>
 *    Zhi Wang <zhi.a.wang@पूर्णांकel.com>
 *
 */

#अगर_अघोषित _GVT_H_
#घोषणा _GVT_H_

#समावेश <uapi/linux/pci_regs.h>

#समावेश "i915_drv.h"

#समावेश "debug.h"
#समावेश "hypercall.h"
#समावेश "mmio.h"
#समावेश "reg.h"
#समावेश "interrupt.h"
#समावेश "gtt.h"
#समावेश "display.h"
#समावेश "edid.h"
#समावेश "execlist.h"
#समावेश "scheduler.h"
#समावेश "sched_policy.h"
#समावेश "mmio_context.h"
#समावेश "cmd_parser.h"
#समावेश "fb_decoder.h"
#समावेश "dmabuf.h"
#समावेश "page_track.h"

#घोषणा GVT_MAX_VGPU 8

काष्ठा पूर्णांकel_gvt_host अणु
	काष्ठा device *dev;
	bool initialized;
	पूर्णांक hypervisor_type;
	स्थिर काष्ठा पूर्णांकel_gvt_mpt *mpt;
पूर्ण;

बाह्य काष्ठा पूर्णांकel_gvt_host पूर्णांकel_gvt_host;

/* Describe per-platक्रमm limitations. */
काष्ठा पूर्णांकel_gvt_device_info अणु
	u32 max_support_vgpus;
	u32 cfg_space_size;
	u32 mmio_size;
	u32 mmio_bar;
	अचिन्हित दीर्घ msi_cap_offset;
	u32 gtt_start_offset;
	u32 gtt_entry_size;
	u32 gtt_entry_size_shअगरt;
	पूर्णांक gmadr_bytes_in_cmd;
	u32 max_surface_size;
पूर्ण;

/* GM resources owned by a vGPU */
काष्ठा पूर्णांकel_vgpu_gm अणु
	u64 aperture_sz;
	u64 hidden_sz;
	काष्ठा drm_mm_node low_gm_node;
	काष्ठा drm_mm_node high_gm_node;
पूर्ण;

#घोषणा INTEL_GVT_MAX_NUM_FENCES 32

/* Fences owned by a vGPU */
काष्ठा पूर्णांकel_vgpu_fence अणु
	काष्ठा i915_fence_reg *regs[INTEL_GVT_MAX_NUM_FENCES];
	u32 base;
	u32 size;
पूर्ण;

काष्ठा पूर्णांकel_vgpu_mmio अणु
	व्योम *vreg;
पूर्ण;

#घोषणा INTEL_GVT_MAX_BAR_NUM 4

काष्ठा पूर्णांकel_vgpu_pci_bar अणु
	u64 size;
	bool tracked;
पूर्ण;

काष्ठा पूर्णांकel_vgpu_cfg_space अणु
	अचिन्हित अक्षर भव_cfg_space[PCI_CFG_SPACE_EXP_SIZE];
	काष्ठा पूर्णांकel_vgpu_pci_bar bar[INTEL_GVT_MAX_BAR_NUM];
	u32 pmcsr_off;
पूर्ण;

#घोषणा vgpu_cfg_space(vgpu) ((vgpu)->cfg_space.भव_cfg_space)

काष्ठा पूर्णांकel_vgpu_irq अणु
	bool irq_warn_once[INTEL_GVT_EVENT_MAX];
	DECLARE_BITMAP(flip_करोne_event[I915_MAX_PIPES],
		       INTEL_GVT_EVENT_MAX);
पूर्ण;

काष्ठा पूर्णांकel_vgpu_opregion अणु
	bool mapped;
	व्योम *va;
	u32 gfn[INTEL_GVT_OPREGION_PAGES];
पूर्ण;

#घोषणा vgpu_opregion(vgpu) (&(vgpu->opregion))

काष्ठा पूर्णांकel_vgpu_display अणु
	काष्ठा पूर्णांकel_vgpu_i2c_edid i2c_edid;
	काष्ठा पूर्णांकel_vgpu_port ports[I915_MAX_PORTS];
	काष्ठा पूर्णांकel_vgpu_sbi sbi;
	क्रमागत port port_num;
पूर्ण;

काष्ठा vgpu_sched_ctl अणु
	पूर्णांक weight;
पूर्ण;

क्रमागत अणु
	INTEL_VGPU_EXECLIST_SUBMISSION = 1,
	INTEL_VGPU_GUC_SUBMISSION,
पूर्ण;

काष्ठा पूर्णांकel_vgpu_submission_ops अणु
	स्थिर अक्षर *name;
	पूर्णांक (*init)(काष्ठा पूर्णांकel_vgpu *vgpu, पूर्णांकel_engine_mask_t engine_mask);
	व्योम (*clean)(काष्ठा पूर्णांकel_vgpu *vgpu, पूर्णांकel_engine_mask_t engine_mask);
	व्योम (*reset)(काष्ठा पूर्णांकel_vgpu *vgpu, पूर्णांकel_engine_mask_t engine_mask);
पूर्ण;

काष्ठा पूर्णांकel_vgpu_submission अणु
	काष्ठा पूर्णांकel_vgpu_execlist execlist[I915_NUM_ENGINES];
	काष्ठा list_head workload_q_head[I915_NUM_ENGINES];
	काष्ठा पूर्णांकel_context *shaकरोw[I915_NUM_ENGINES];
	काष्ठा kmem_cache *workloads;
	atomic_t running_workload_num;
	जोड़ अणु
		u64 i915_context_pml4;
		u64 i915_context_pdps[GEN8_3LVL_PDPES];
	पूर्ण;
	DECLARE_BITMAP(shaकरोw_ctx_desc_updated, I915_NUM_ENGINES);
	DECLARE_BITMAP(tlb_handle_pending, I915_NUM_ENGINES);
	व्योम *ring_scan_buffer[I915_NUM_ENGINES];
	पूर्णांक ring_scan_buffer_size[I915_NUM_ENGINES];
	स्थिर काष्ठा पूर्णांकel_vgpu_submission_ops *ops;
	पूर्णांक भव_submission_पूर्णांकerface;
	bool active;
	काष्ठा अणु
		u32 lrca;
		bool valid;
		u64 ring_context_gpa;
	पूर्ण last_ctx[I915_NUM_ENGINES];
पूर्ण;

काष्ठा पूर्णांकel_vgpu अणु
	काष्ठा पूर्णांकel_gvt *gvt;
	काष्ठा mutex vgpu_lock;
	पूर्णांक id;
	अचिन्हित दीर्घ handle; /* vGPU handle used by hypervisor MPT modules */
	bool active;
	bool pv_notअगरied;
	bool failsafe;
	अचिन्हित पूर्णांक resetting_eng;

	/* Both sched_data and sched_ctl can be seen a part of the global gvt
	 * scheduler काष्ठाure. So below 2 vgpu data are रक्षित
	 * by sched_lock, not vgpu_lock.
	 */
	व्योम *sched_data;
	काष्ठा vgpu_sched_ctl sched_ctl;

	काष्ठा पूर्णांकel_vgpu_fence fence;
	काष्ठा पूर्णांकel_vgpu_gm gm;
	काष्ठा पूर्णांकel_vgpu_cfg_space cfg_space;
	काष्ठा पूर्णांकel_vgpu_mmio mmio;
	काष्ठा पूर्णांकel_vgpu_irq irq;
	काष्ठा पूर्णांकel_vgpu_gtt gtt;
	काष्ठा पूर्णांकel_vgpu_opregion opregion;
	काष्ठा पूर्णांकel_vgpu_display display;
	काष्ठा पूर्णांकel_vgpu_submission submission;
	काष्ठा radix_tree_root page_track_tree;
	u32 hws_pga[I915_NUM_ENGINES];
	/* Set on PCI_D3, reset on DMLR, not reflecting the actual PM state */
	bool d3_entered;

	काष्ठा dentry *debugfs;

	/* Hypervisor-specअगरic device state. */
	व्योम *vdev;

	काष्ठा list_head dmabuf_obj_list_head;
	काष्ठा mutex dmabuf_lock;
	काष्ठा idr object_idr;
	काष्ठा पूर्णांकel_vgpu_vblank_समयr vblank_समयr;

	u32 scan_nonprivbb;
पूर्ण;

अटल अंतरभूत व्योम *पूर्णांकel_vgpu_vdev(काष्ठा पूर्णांकel_vgpu *vgpu)
अणु
	वापस vgpu->vdev;
पूर्ण

/* validating GM healthy status*/
#घोषणा vgpu_is_vm_unhealthy(ret_val) \
	(((ret_val) == -EBADRQC) || ((ret_val) == -EFAULT))

काष्ठा पूर्णांकel_gvt_gm अणु
	अचिन्हित दीर्घ vgpu_allocated_low_gm_size;
	अचिन्हित दीर्घ vgpu_allocated_high_gm_size;
पूर्ण;

काष्ठा पूर्णांकel_gvt_fence अणु
	अचिन्हित दीर्घ vgpu_allocated_fence_num;
पूर्ण;

/* Special MMIO blocks. */
काष्ठा gvt_mmio_block अणु
	अचिन्हित पूर्णांक device;
	i915_reg_t   offset;
	अचिन्हित पूर्णांक size;
	gvt_mmio_func पढ़ो;
	gvt_mmio_func ग_लिखो;
पूर्ण;

#घोषणा INTEL_GVT_MMIO_HASH_BITS 11

काष्ठा पूर्णांकel_gvt_mmio अणु
	u16 *mmio_attribute;
/* Register contains RO bits */
#घोषणा F_RO		(1 << 0)
/* Register contains graphics address */
#घोषणा F_GMADR		(1 << 1)
/* Mode mask रेजिस्टरs with high 16 bits as the mask bits */
#घोषणा F_MODE_MASK	(1 << 2)
/* This reg can be accessed by GPU commands */
#घोषणा F_CMD_ACCESS	(1 << 3)
/* This reg has been accessed by a VM */
#घोषणा F_ACCESSED	(1 << 4)
/* This reg requires save & restore during host PM suspend/resume */
#घोषणा F_PM_SAVE	(1 << 5)
/* This reg could be accessed by unaligned address */
#घोषणा F_UNALIGN	(1 << 6)
/* This reg is in GVT's mmio save-restor list and in hardware
 * logical context image
 */
#घोषणा F_SR_IN_CTX	(1 << 7)
/* Value of command ग_लिखो of this reg needs to be patched */
#घोषणा F_CMD_WRITE_PATCH	(1 << 8)

	काष्ठा gvt_mmio_block *mmio_block;
	अचिन्हित पूर्णांक num_mmio_block;

	DECLARE_HASHTABLE(mmio_info_table, INTEL_GVT_MMIO_HASH_BITS);
	अचिन्हित दीर्घ num_tracked_mmio;
पूर्ण;

काष्ठा पूर्णांकel_gvt_firmware अणु
	व्योम *cfg_space;
	व्योम *mmio;
	bool firmware_loaded;
पूर्ण;

#घोषणा NR_MAX_INTEL_VGPU_TYPES 20
काष्ठा पूर्णांकel_vgpu_type अणु
	अक्षर name[16];
	अचिन्हित पूर्णांक avail_instance;
	अचिन्हित पूर्णांक low_gm_size;
	अचिन्हित पूर्णांक high_gm_size;
	अचिन्हित पूर्णांक fence;
	अचिन्हित पूर्णांक weight;
	क्रमागत पूर्णांकel_vgpu_edid resolution;
पूर्ण;

काष्ठा पूर्णांकel_gvt अणु
	/* GVT scope lock, protect GVT itself, and all resource currently
	 * not yet रक्षित by special locks(vgpu and scheduler lock).
	 */
	काष्ठा mutex lock;
	/* scheduler scope lock, protect gvt and vgpu schedule related data */
	काष्ठा mutex sched_lock;

	काष्ठा पूर्णांकel_gt *gt;
	काष्ठा idr vgpu_idr;	/* vGPU IDR pool */

	काष्ठा पूर्णांकel_gvt_device_info device_info;
	काष्ठा पूर्णांकel_gvt_gm gm;
	काष्ठा पूर्णांकel_gvt_fence fence;
	काष्ठा पूर्णांकel_gvt_mmio mmio;
	काष्ठा पूर्णांकel_gvt_firmware firmware;
	काष्ठा पूर्णांकel_gvt_irq irq;
	काष्ठा पूर्णांकel_gvt_gtt gtt;
	काष्ठा पूर्णांकel_gvt_workload_scheduler scheduler;
	काष्ठा notअगरier_block shaकरोw_ctx_notअगरier_block[I915_NUM_ENGINES];
	DECLARE_HASHTABLE(cmd_table, GVT_CMD_HASH_BITS);
	काष्ठा पूर्णांकel_vgpu_type *types;
	अचिन्हित पूर्णांक num_types;
	काष्ठा पूर्णांकel_vgpu *idle_vgpu;

	काष्ठा task_काष्ठा *service_thपढ़ो;
	रुको_queue_head_t service_thपढ़ो_wq;

	/* service_request is always used in bit operation, we should always
	 * use it with atomic bit ops so that no need to use gvt big lock.
	 */
	अचिन्हित दीर्घ service_request;

	काष्ठा अणु
		काष्ठा engine_mmio *mmio;
		पूर्णांक ctx_mmio_count[I915_NUM_ENGINES];
		u32 *tlb_mmio_offset_list;
		u32 tlb_mmio_offset_list_cnt;
		u32 *mocs_mmio_offset_list;
		u32 mocs_mmio_offset_list_cnt;
	पूर्ण engine_mmio_list;
	bool is_reg_whitelist_updated;

	काष्ठा dentry *debugfs_root;
पूर्ण;

अटल अंतरभूत काष्ठा पूर्णांकel_gvt *to_gvt(काष्ठा drm_i915_निजी *i915)
अणु
	वापस i915->gvt;
पूर्ण

क्रमागत अणु
	/* Scheduling trigger by समयr */
	INTEL_GVT_REQUEST_SCHED = 0,

	/* Scheduling trigger by event */
	INTEL_GVT_REQUEST_EVENT_SCHED = 1,

	/* per-vGPU vblank emulation request */
	INTEL_GVT_REQUEST_EMULATE_VBLANK = 2,
	INTEL_GVT_REQUEST_EMULATE_VBLANK_MAX = INTEL_GVT_REQUEST_EMULATE_VBLANK
		+ GVT_MAX_VGPU,
पूर्ण;

अटल अंतरभूत व्योम पूर्णांकel_gvt_request_service(काष्ठा पूर्णांकel_gvt *gvt,
		पूर्णांक service)
अणु
	set_bit(service, (व्योम *)&gvt->service_request);
	wake_up(&gvt->service_thपढ़ो_wq);
पूर्ण

व्योम पूर्णांकel_gvt_मुक्त_firmware(काष्ठा पूर्णांकel_gvt *gvt);
पूर्णांक पूर्णांकel_gvt_load_firmware(काष्ठा पूर्णांकel_gvt *gvt);

/* Aperture/GM space definitions क्रम GVT device */
#घोषणा MB_TO_BYTES(mb) ((mb) << 20ULL)
#घोषणा BYTES_TO_MB(b) ((b) >> 20ULL)

#घोषणा HOST_LOW_GM_SIZE MB_TO_BYTES(128)
#घोषणा HOST_HIGH_GM_SIZE MB_TO_BYTES(384)
#घोषणा HOST_FENCE 4

#घोषणा gvt_to_ggtt(gvt)	((gvt)->gt->ggtt)

/* Aperture/GM space definitions क्रम GVT device */
#घोषणा gvt_aperture_sz(gvt)	  gvt_to_ggtt(gvt)->mappable_end
#घोषणा gvt_aperture_pa_base(gvt) gvt_to_ggtt(gvt)->gmadr.start

#घोषणा gvt_ggtt_gm_sz(gvt)	gvt_to_ggtt(gvt)->vm.total
#घोषणा gvt_ggtt_sz(gvt)	(gvt_to_ggtt(gvt)->vm.total >> PAGE_SHIFT << 3)
#घोषणा gvt_hidden_sz(gvt)	(gvt_ggtt_gm_sz(gvt) - gvt_aperture_sz(gvt))

#घोषणा gvt_aperture_gmadr_base(gvt) (0)
#घोषणा gvt_aperture_gmadr_end(gvt) (gvt_aperture_gmadr_base(gvt) \
				     + gvt_aperture_sz(gvt) - 1)

#घोषणा gvt_hidden_gmadr_base(gvt) (gvt_aperture_gmadr_base(gvt) \
				    + gvt_aperture_sz(gvt))
#घोषणा gvt_hidden_gmadr_end(gvt) (gvt_hidden_gmadr_base(gvt) \
				   + gvt_hidden_sz(gvt) - 1)

#घोषणा gvt_fence_sz(gvt) (gvt_to_ggtt(gvt)->num_fences)

/* Aperture/GM space definitions क्रम vGPU */
#घोषणा vgpu_aperture_offset(vgpu)	((vgpu)->gm.low_gm_node.start)
#घोषणा vgpu_hidden_offset(vgpu)	((vgpu)->gm.high_gm_node.start)
#घोषणा vgpu_aperture_sz(vgpu)		((vgpu)->gm.aperture_sz)
#घोषणा vgpu_hidden_sz(vgpu)		((vgpu)->gm.hidden_sz)

#घोषणा vgpu_aperture_pa_base(vgpu) \
	(gvt_aperture_pa_base(vgpu->gvt) + vgpu_aperture_offset(vgpu))

#घोषणा vgpu_ggtt_gm_sz(vgpu) ((vgpu)->gm.aperture_sz + (vgpu)->gm.hidden_sz)

#घोषणा vgpu_aperture_pa_end(vgpu) \
	(vgpu_aperture_pa_base(vgpu) + vgpu_aperture_sz(vgpu) - 1)

#घोषणा vgpu_aperture_gmadr_base(vgpu) (vgpu_aperture_offset(vgpu))
#घोषणा vgpu_aperture_gmadr_end(vgpu) \
	(vgpu_aperture_gmadr_base(vgpu) + vgpu_aperture_sz(vgpu) - 1)

#घोषणा vgpu_hidden_gmadr_base(vgpu) (vgpu_hidden_offset(vgpu))
#घोषणा vgpu_hidden_gmadr_end(vgpu) \
	(vgpu_hidden_gmadr_base(vgpu) + vgpu_hidden_sz(vgpu) - 1)

#घोषणा vgpu_fence_base(vgpu) (vgpu->fence.base)
#घोषणा vgpu_fence_sz(vgpu) (vgpu->fence.size)

/* ring context size i.e. the first 0x50 dwords*/
#घोषणा RING_CTX_SIZE 320

काष्ठा पूर्णांकel_vgpu_creation_params अणु
	__u64 handle;
	__u64 low_gm_sz;  /* in MB */
	__u64 high_gm_sz; /* in MB */
	__u64 fence_sz;
	__u64 resolution;
	__s32 primary;
	__u64 vgpu_id;

	__u32 weight;
पूर्ण;

पूर्णांक पूर्णांकel_vgpu_alloc_resource(काष्ठा पूर्णांकel_vgpu *vgpu,
			      काष्ठा पूर्णांकel_vgpu_creation_params *param);
व्योम पूर्णांकel_vgpu_reset_resource(काष्ठा पूर्णांकel_vgpu *vgpu);
व्योम पूर्णांकel_vgpu_मुक्त_resource(काष्ठा पूर्णांकel_vgpu *vgpu);
व्योम पूर्णांकel_vgpu_ग_लिखो_fence(काष्ठा पूर्णांकel_vgpu *vgpu,
	u32 fence, u64 value);

/* Macros क्रम easily accessing vGPU भव/shaकरोw रेजिस्टर.
   Explicitly seperate use क्रम typed MMIO reg or real offset.*/
#घोषणा vgpu_vreg_t(vgpu, reg) \
	(*(u32 *)(vgpu->mmio.vreg + i915_mmio_reg_offset(reg)))
#घोषणा vgpu_vreg(vgpu, offset) \
	(*(u32 *)(vgpu->mmio.vreg + (offset)))
#घोषणा vgpu_vreg64_t(vgpu, reg) \
	(*(u64 *)(vgpu->mmio.vreg + i915_mmio_reg_offset(reg)))
#घोषणा vgpu_vreg64(vgpu, offset) \
	(*(u64 *)(vgpu->mmio.vreg + (offset)))

#घोषणा क्रम_each_active_vgpu(gvt, vgpu, id) \
	idr_क्रम_each_entry((&(gvt)->vgpu_idr), (vgpu), (id)) \
		क्रम_each_अगर(vgpu->active)

अटल अंतरभूत व्योम पूर्णांकel_vgpu_ग_लिखो_pci_bar(काष्ठा पूर्णांकel_vgpu *vgpu,
					    u32 offset, u32 val, bool low)
अणु
	u32 *pval;

	/* BAR offset should be 32 bits algiend */
	offset = roundकरोwn(offset, 4);
	pval = (u32 *)(vgpu_cfg_space(vgpu) + offset);

	अगर (low) अणु
		/*
		 * only update bit 31 - bit 4,
		 * leave the bit 3 - bit 0 unchanged.
		 */
		*pval = (val & GENMASK(31, 4)) | (*pval & GENMASK(3, 0));
	पूर्ण अन्यथा अणु
		*pval = val;
	पूर्ण
पूर्ण

पूर्णांक पूर्णांकel_gvt_init_vgpu_types(काष्ठा पूर्णांकel_gvt *gvt);
व्योम पूर्णांकel_gvt_clean_vgpu_types(काष्ठा पूर्णांकel_gvt *gvt);

काष्ठा पूर्णांकel_vgpu *पूर्णांकel_gvt_create_idle_vgpu(काष्ठा पूर्णांकel_gvt *gvt);
व्योम पूर्णांकel_gvt_destroy_idle_vgpu(काष्ठा पूर्णांकel_vgpu *vgpu);
काष्ठा पूर्णांकel_vgpu *पूर्णांकel_gvt_create_vgpu(काष्ठा पूर्णांकel_gvt *gvt,
					 काष्ठा पूर्णांकel_vgpu_type *type);
व्योम पूर्णांकel_gvt_destroy_vgpu(काष्ठा पूर्णांकel_vgpu *vgpu);
व्योम पूर्णांकel_gvt_release_vgpu(काष्ठा पूर्णांकel_vgpu *vgpu);
व्योम पूर्णांकel_gvt_reset_vgpu_locked(काष्ठा पूर्णांकel_vgpu *vgpu, bool dmlr,
				 पूर्णांकel_engine_mask_t engine_mask);
व्योम पूर्णांकel_gvt_reset_vgpu(काष्ठा पूर्णांकel_vgpu *vgpu);
व्योम पूर्णांकel_gvt_activate_vgpu(काष्ठा पूर्णांकel_vgpu *vgpu);
व्योम पूर्णांकel_gvt_deactivate_vgpu(काष्ठा पूर्णांकel_vgpu *vgpu);

/* validating GM functions */
#घोषणा vgpu_gmadr_is_aperture(vgpu, gmadr) \
	((gmadr >= vgpu_aperture_gmadr_base(vgpu)) && \
	 (gmadr <= vgpu_aperture_gmadr_end(vgpu)))

#घोषणा vgpu_gmadr_is_hidden(vgpu, gmadr) \
	((gmadr >= vgpu_hidden_gmadr_base(vgpu)) && \
	 (gmadr <= vgpu_hidden_gmadr_end(vgpu)))

#घोषणा vgpu_gmadr_is_valid(vgpu, gmadr) \
	 ((vgpu_gmadr_is_aperture(vgpu, gmadr) || \
	  (vgpu_gmadr_is_hidden(vgpu, gmadr))))

#घोषणा gvt_gmadr_is_aperture(gvt, gmadr) \
	 ((gmadr >= gvt_aperture_gmadr_base(gvt)) && \
	  (gmadr <= gvt_aperture_gmadr_end(gvt)))

#घोषणा gvt_gmadr_is_hidden(gvt, gmadr) \
	  ((gmadr >= gvt_hidden_gmadr_base(gvt)) && \
	   (gmadr <= gvt_hidden_gmadr_end(gvt)))

#घोषणा gvt_gmadr_is_valid(gvt, gmadr) \
	  (gvt_gmadr_is_aperture(gvt, gmadr) || \
	    gvt_gmadr_is_hidden(gvt, gmadr))

bool पूर्णांकel_gvt_ggtt_validate_range(काष्ठा पूर्णांकel_vgpu *vgpu, u64 addr, u32 size);
पूर्णांक पूर्णांकel_gvt_ggtt_gmadr_g2h(काष्ठा पूर्णांकel_vgpu *vgpu, u64 g_addr, u64 *h_addr);
पूर्णांक पूर्णांकel_gvt_ggtt_gmadr_h2g(काष्ठा पूर्णांकel_vgpu *vgpu, u64 h_addr, u64 *g_addr);
पूर्णांक पूर्णांकel_gvt_ggtt_index_g2h(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित दीर्घ g_index,
			     अचिन्हित दीर्घ *h_index);
पूर्णांक पूर्णांकel_gvt_ggtt_h2g_index(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित दीर्घ h_index,
			     अचिन्हित दीर्घ *g_index);

व्योम पूर्णांकel_vgpu_init_cfg_space(काष्ठा पूर्णांकel_vgpu *vgpu,
		bool primary);
व्योम पूर्णांकel_vgpu_reset_cfg_space(काष्ठा पूर्णांकel_vgpu *vgpu);

पूर्णांक पूर्णांकel_vgpu_emulate_cfg_पढ़ो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
		व्योम *p_data, अचिन्हित पूर्णांक bytes);

पूर्णांक पूर्णांकel_vgpu_emulate_cfg_ग_लिखो(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक offset,
		व्योम *p_data, अचिन्हित पूर्णांक bytes);

व्योम पूर्णांकel_vgpu_emulate_hotplug(काष्ठा पूर्णांकel_vgpu *vgpu, bool connected);

अटल अंतरभूत u64 पूर्णांकel_vgpu_get_bar_gpa(काष्ठा पूर्णांकel_vgpu *vgpu, पूर्णांक bar)
अणु
	/* We are 64bit bar. */
	वापस (*(u64 *)(vgpu->cfg_space.भव_cfg_space + bar)) &
			PCI_BASE_ADDRESS_MEM_MASK;
पूर्ण

व्योम पूर्णांकel_vgpu_clean_opregion(काष्ठा पूर्णांकel_vgpu *vgpu);
पूर्णांक पूर्णांकel_vgpu_init_opregion(काष्ठा पूर्णांकel_vgpu *vgpu);
पूर्णांक पूर्णांकel_vgpu_opregion_base_ग_लिखो_handler(काष्ठा पूर्णांकel_vgpu *vgpu, u32 gpa);

पूर्णांक पूर्णांकel_vgpu_emulate_opregion_request(काष्ठा पूर्णांकel_vgpu *vgpu, u32 swsci);
व्योम populate_pvinfo_page(काष्ठा पूर्णांकel_vgpu *vgpu);

पूर्णांक पूर्णांकel_gvt_scan_and_shaकरोw_workload(काष्ठा पूर्णांकel_vgpu_workload *workload);
व्योम enter_failsafe_mode(काष्ठा पूर्णांकel_vgpu *vgpu, पूर्णांक reason);

काष्ठा पूर्णांकel_gvt_ops अणु
	पूर्णांक (*emulate_cfg_पढ़ो)(काष्ठा पूर्णांकel_vgpu *, अचिन्हित पूर्णांक, व्योम *,
				अचिन्हित पूर्णांक);
	पूर्णांक (*emulate_cfg_ग_लिखो)(काष्ठा पूर्णांकel_vgpu *, अचिन्हित पूर्णांक, व्योम *,
				अचिन्हित पूर्णांक);
	पूर्णांक (*emulate_mmio_पढ़ो)(काष्ठा पूर्णांकel_vgpu *, u64, व्योम *,
				अचिन्हित पूर्णांक);
	पूर्णांक (*emulate_mmio_ग_लिखो)(काष्ठा पूर्णांकel_vgpu *, u64, व्योम *,
				अचिन्हित पूर्णांक);
	काष्ठा पूर्णांकel_vgpu *(*vgpu_create)(काष्ठा पूर्णांकel_gvt *,
				काष्ठा पूर्णांकel_vgpu_type *);
	व्योम (*vgpu_destroy)(काष्ठा पूर्णांकel_vgpu *vgpu);
	व्योम (*vgpu_release)(काष्ठा पूर्णांकel_vgpu *vgpu);
	व्योम (*vgpu_reset)(काष्ठा पूर्णांकel_vgpu *);
	व्योम (*vgpu_activate)(काष्ठा पूर्णांकel_vgpu *);
	व्योम (*vgpu_deactivate)(काष्ठा पूर्णांकel_vgpu *);
	पूर्णांक (*vgpu_query_plane)(काष्ठा पूर्णांकel_vgpu *vgpu, व्योम *);
	पूर्णांक (*vgpu_get_dmabuf)(काष्ठा पूर्णांकel_vgpu *vgpu, अचिन्हित पूर्णांक);
	पूर्णांक (*ग_लिखो_protect_handler)(काष्ठा पूर्णांकel_vgpu *, u64, व्योम *,
				     अचिन्हित पूर्णांक);
	व्योम (*emulate_hotplug)(काष्ठा पूर्णांकel_vgpu *vgpu, bool connected);
पूर्ण;


क्रमागत अणु
	GVT_FAILSAFE_UNSUPPORTED_GUEST,
	GVT_FAILSAFE_INSUFFICIENT_RESOURCE,
	GVT_FAILSAFE_GUEST_ERR,
पूर्ण;

अटल अंतरभूत व्योम mmio_hw_access_pre(काष्ठा पूर्णांकel_gt *gt)
अणु
	पूर्णांकel_runसमय_pm_get(gt->uncore->rpm);
पूर्ण

अटल अंतरभूत व्योम mmio_hw_access_post(काष्ठा पूर्णांकel_gt *gt)
अणु
	पूर्णांकel_runसमय_pm_put_unchecked(gt->uncore->rpm);
पूर्ण

/**
 * पूर्णांकel_gvt_mmio_set_accessed - mark a MMIO has been accessed
 * @gvt: a GVT device
 * @offset: रेजिस्टर offset
 *
 */
अटल अंतरभूत व्योम पूर्णांकel_gvt_mmio_set_accessed(
			काष्ठा पूर्णांकel_gvt *gvt, अचिन्हित पूर्णांक offset)
अणु
	gvt->mmio.mmio_attribute[offset >> 2] |= F_ACCESSED;
पूर्ण

/**
 * पूर्णांकel_gvt_mmio_is_cmd_accessible - अगर a MMIO could be accessed by command
 * @gvt: a GVT device
 * @offset: रेजिस्टर offset
 *
 * Returns:
 * True अगर an MMIO is able to be accessed by GPU commands
 */
अटल अंतरभूत bool पूर्णांकel_gvt_mmio_is_cmd_accessible(
			काष्ठा पूर्णांकel_gvt *gvt, अचिन्हित पूर्णांक offset)
अणु
	वापस gvt->mmio.mmio_attribute[offset >> 2] & F_CMD_ACCESS;
पूर्ण

/**
 * पूर्णांकel_gvt_mmio_set_cmd_accessible -
 *				mark a MMIO could be accessible by command
 * @gvt: a GVT device
 * @offset: रेजिस्टर offset
 *
 */
अटल अंतरभूत व्योम पूर्णांकel_gvt_mmio_set_cmd_accessible(
			काष्ठा पूर्णांकel_gvt *gvt, अचिन्हित पूर्णांक offset)
अणु
	gvt->mmio.mmio_attribute[offset >> 2] |= F_CMD_ACCESS;
पूर्ण

/**
 * पूर्णांकel_gvt_mmio_is_unalign - mark a MMIO could be accessed unaligned
 * @gvt: a GVT device
 * @offset: रेजिस्टर offset
 *
 */
अटल अंतरभूत bool पूर्णांकel_gvt_mmio_is_unalign(
			काष्ठा पूर्णांकel_gvt *gvt, अचिन्हित पूर्णांक offset)
अणु
	वापस gvt->mmio.mmio_attribute[offset >> 2] & F_UNALIGN;
पूर्ण

/**
 * पूर्णांकel_gvt_mmio_has_mode_mask - अगर a MMIO has a mode mask
 * @gvt: a GVT device
 * @offset: रेजिस्टर offset
 *
 * Returns:
 * True अगर a MMIO has a mode mask in its higher 16 bits, false अगर it isn't.
 *
 */
अटल अंतरभूत bool पूर्णांकel_gvt_mmio_has_mode_mask(
			काष्ठा पूर्णांकel_gvt *gvt, अचिन्हित पूर्णांक offset)
अणु
	वापस gvt->mmio.mmio_attribute[offset >> 2] & F_MODE_MASK;
पूर्ण

/**
 * पूर्णांकel_gvt_mmio_is_sr_in_ctx -
 *		check अगर an MMIO has F_SR_IN_CTX mask
 * @gvt: a GVT device
 * @offset: रेजिस्टर offset
 *
 * Returns:
 * True अगर an MMIO has an F_SR_IN_CTX  mask, false अगर it isn't.
 *
 */
अटल अंतरभूत bool पूर्णांकel_gvt_mmio_is_sr_in_ctx(
			काष्ठा पूर्णांकel_gvt *gvt, अचिन्हित पूर्णांक offset)
अणु
	वापस gvt->mmio.mmio_attribute[offset >> 2] & F_SR_IN_CTX;
पूर्ण

/**
 * पूर्णांकel_gvt_mmio_set_sr_in_ctx -
 *		mask an MMIO in GVT's mmio save-restore list and also
 *		in hardware logical context image
 * @gvt: a GVT device
 * @offset: रेजिस्टर offset
 *
 */
अटल अंतरभूत व्योम पूर्णांकel_gvt_mmio_set_sr_in_ctx(
			काष्ठा पूर्णांकel_gvt *gvt, अचिन्हित पूर्णांक offset)
अणु
	gvt->mmio.mmio_attribute[offset >> 2] |= F_SR_IN_CTX;
पूर्ण

व्योम पूर्णांकel_gvt_debugfs_add_vgpu(काष्ठा पूर्णांकel_vgpu *vgpu);
/**
 * पूर्णांकel_gvt_mmio_set_cmd_ग_लिखो_patch -
 *				mark an MMIO अगर its cmd ग_लिखो needs to be
 *				patched
 * @gvt: a GVT device
 * @offset: रेजिस्टर offset
 *
 */
अटल अंतरभूत व्योम पूर्णांकel_gvt_mmio_set_cmd_ग_लिखो_patch(
			काष्ठा पूर्णांकel_gvt *gvt, अचिन्हित पूर्णांक offset)
अणु
	gvt->mmio.mmio_attribute[offset >> 2] |= F_CMD_WRITE_PATCH;
पूर्ण

/**
 * पूर्णांकel_gvt_mmio_is_cmd_ग_लिखो_patch - check अगर an mmio's cmd access needs to
 * be patched
 * @gvt: a GVT device
 * @offset: रेजिस्टर offset
 *
 * Returns:
 * True अगर GPU commmand ग_लिखो to an MMIO should be patched
 */
अटल अंतरभूत bool पूर्णांकel_gvt_mmio_is_cmd_ग_लिखो_patch(
			काष्ठा पूर्णांकel_gvt *gvt, अचिन्हित पूर्णांक offset)
अणु
	वापस gvt->mmio.mmio_attribute[offset >> 2] & F_CMD_WRITE_PATCH;
पूर्ण

व्योम पूर्णांकel_gvt_debugfs_हटाओ_vgpu(काष्ठा पूर्णांकel_vgpu *vgpu);
व्योम पूर्णांकel_gvt_debugfs_init(काष्ठा पूर्णांकel_gvt *gvt);
व्योम पूर्णांकel_gvt_debugfs_clean(काष्ठा पूर्णांकel_gvt *gvt);

पूर्णांक पूर्णांकel_gvt_pm_resume(काष्ठा पूर्णांकel_gvt *gvt);

#समावेश "trace.h"
#समावेश "mpt.h"

#पूर्ण_अगर
