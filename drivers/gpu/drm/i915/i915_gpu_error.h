<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright oडट 2008-2018 Intel Corporation
 */

#अगर_अघोषित _I915_GPU_ERROR_H_
#घोषणा _I915_GPU_ERROR_H_

#समावेश <linux/atomic.h>
#समावेश <linux/kref.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/sched.h>

#समावेश <drm/drm_mm.h>

#समावेश "gt/intel_engine.h"
#समावेश "gt/intel_gt_types.h"
#समावेश "gt/uc/intel_uc_fw.h"

#समावेश "intel_device_info.h"

#समावेश "i915_gem.h"
#समावेश "i915_gem_gtt.h"
#समावेश "i915_params.h"
#समावेश "i915_scheduler.h"

काष्ठा drm_i915_निजी;
काष्ठा i915_vma_compress;
काष्ठा पूर्णांकel_engine_capture_vma;
काष्ठा पूर्णांकel_overlay_error_state;
काष्ठा पूर्णांकel_display_error_state;

काष्ठा i915_vma_coredump अणु
	काष्ठा i915_vma_coredump *next;

	अक्षर name[20];

	u64 gtt_offset;
	u64 gtt_size;
	u32 gtt_page_sizes;

	पूर्णांक num_pages;
	पूर्णांक page_count;
	पूर्णांक unused;
	u32 *pages[];
पूर्ण;

काष्ठा i915_request_coredump अणु
	अचिन्हित दीर्घ flags;
	pid_t pid;
	u32 context;
	u32 seqno;
	u32 head;
	u32 tail;
	काष्ठा i915_sched_attr sched_attr;
पूर्ण;

काष्ठा पूर्णांकel_engine_coredump अणु
	स्थिर काष्ठा पूर्णांकel_engine_cs *engine;

	bool hung;
	bool simulated;
	u32 reset_count;

	/* position of active request inside the ring */
	u32 rq_head, rq_post, rq_tail;

	/* Register state */
	u32 ccid;
	u32 start;
	u32 tail;
	u32 head;
	u32 ctl;
	u32 mode;
	u32 hws;
	u32 ipeir;
	u32 ipehr;
	u32 esr;
	u32 bbstate;
	u32 instpm;
	u32 instps;
	u64 bbaddr;
	u64 acthd;
	u32 fault_reg;
	u64 faddr;
	u32 rc_psmi; /* sleep state */
	काष्ठा पूर्णांकel_instकरोne instकरोne;

	काष्ठा i915_gem_context_coredump अणु
		अक्षर comm[TASK_COMM_LEN];

		u64 total_runसमय;
		u32 avg_runसमय;

		pid_t pid;
		पूर्णांक active;
		पूर्णांक guilty;
		काष्ठा i915_sched_attr sched_attr;
	पूर्ण context;

	काष्ठा i915_vma_coredump *vma;

	काष्ठा i915_request_coredump execlist[EXECLIST_MAX_PORTS];
	अचिन्हित पूर्णांक num_ports;

	काष्ठा अणु
		u32 gfx_mode;
		जोड़ अणु
			u64 pdp[4];
			u32 pp_dir_base;
		पूर्ण;
	पूर्ण vm_info;

	काष्ठा पूर्णांकel_engine_coredump *next;
पूर्ण;

काष्ठा पूर्णांकel_gt_coredump अणु
	स्थिर काष्ठा पूर्णांकel_gt *_gt;
	bool awake;
	bool simulated;

	काष्ठा पूर्णांकel_gt_info info;

	/* Generic रेजिस्टर state */
	u32 eir;
	u32 pgtbl_er;
	u32 ier;
	u32 gtier[6], ngtier;
	u32 derrmr;
	u32 क्रमcewake;
	u32 error; /* gen6+ */
	u32 err_पूर्णांक; /* gen7 */
	u32 fault_data0; /* gen8, gen9 */
	u32 fault_data1; /* gen8, gen9 */
	u32 करोne_reg;
	u32 gac_eco;
	u32 gam_ecochk;
	u32 gab_ctl;
	u32 gfx_mode;
	u32 gtt_cache;
	u32 aux_err; /* gen12 */
	u32 sfc_करोne[GEN12_SFC_DONE_MAX]; /* gen12 */
	u32 gam_करोne; /* gen12 */

	u32 nfence;
	u64 fence[I915_MAX_NUM_FENCES];

	काष्ठा पूर्णांकel_engine_coredump *engine;

	काष्ठा पूर्णांकel_uc_coredump अणु
		काष्ठा पूर्णांकel_uc_fw guc_fw;
		काष्ठा पूर्णांकel_uc_fw huc_fw;
		काष्ठा i915_vma_coredump *guc_log;
	पूर्ण *uc;

	काष्ठा पूर्णांकel_gt_coredump *next;
पूर्ण;

काष्ठा i915_gpu_coredump अणु
	काष्ठा kref ref;
	kसमय_प्रकार समय;
	kसमय_प्रकार bootसमय;
	kसमय_प्रकार upसमय;
	अचिन्हित दीर्घ capture;

	काष्ठा drm_i915_निजी *i915;

	काष्ठा पूर्णांकel_gt_coredump *gt;

	अक्षर error_msg[128];
	bool simulated;
	bool wakelock;
	bool suspended;
	पूर्णांक iommu;
	u32 reset_count;
	u32 suspend_count;

	काष्ठा पूर्णांकel_device_info device_info;
	काष्ठा पूर्णांकel_runसमय_info runसमय_info;
	काष्ठा पूर्णांकel_driver_caps driver_caps;
	काष्ठा i915_params params;

	काष्ठा पूर्णांकel_overlay_error_state *overlay;
	काष्ठा पूर्णांकel_display_error_state *display;

	काष्ठा scatterlist *sgl, *fit;
पूर्ण;

काष्ठा i915_gpu_error अणु
	/* For reset and error_state handling. */
	spinlock_t lock;
	/* Protected by the above dev->gpu_error.lock. */
	काष्ठा i915_gpu_coredump *first_error;

	atomic_t pending_fb_pin;

	/** Number of बार the device has been reset (global) */
	atomic_t reset_count;

	/** Number of बार an engine has been reset */
	atomic_t reset_engine_count[I915_NUM_ENGINES];
पूर्ण;

काष्ठा drm_i915_error_state_buf अणु
	काष्ठा drm_i915_निजी *i915;
	काष्ठा scatterlist *sgl, *cur, *end;

	अक्षर *buf;
	माप_प्रकार bytes;
	माप_प्रकार size;
	loff_t iter;

	पूर्णांक err;
पूर्ण;

#अगर IS_ENABLED(CONFIG_DRM_I915_CAPTURE_ERROR)

__म_लिखो(2, 3)
व्योम i915_error_म_लिखो(काष्ठा drm_i915_error_state_buf *e, स्थिर अक्षर *f, ...);

काष्ठा i915_gpu_coredump *i915_gpu_coredump(काष्ठा पूर्णांकel_gt *gt,
					    पूर्णांकel_engine_mask_t engine_mask);
व्योम i915_capture_error_state(काष्ठा पूर्णांकel_gt *gt,
			      पूर्णांकel_engine_mask_t engine_mask);

काष्ठा i915_gpu_coredump *
i915_gpu_coredump_alloc(काष्ठा drm_i915_निजी *i915, gfp_t gfp);

काष्ठा पूर्णांकel_gt_coredump *
पूर्णांकel_gt_coredump_alloc(काष्ठा पूर्णांकel_gt *gt, gfp_t gfp);

काष्ठा पूर्णांकel_engine_coredump *
पूर्णांकel_engine_coredump_alloc(काष्ठा पूर्णांकel_engine_cs *engine, gfp_t gfp);

काष्ठा पूर्णांकel_engine_capture_vma *
पूर्णांकel_engine_coredump_add_request(काष्ठा पूर्णांकel_engine_coredump *ee,
				  काष्ठा i915_request *rq,
				  gfp_t gfp);

व्योम पूर्णांकel_engine_coredump_add_vma(काष्ठा पूर्णांकel_engine_coredump *ee,
				   काष्ठा पूर्णांकel_engine_capture_vma *capture,
				   काष्ठा i915_vma_compress *compress);

काष्ठा i915_vma_compress *
i915_vma_capture_prepare(काष्ठा पूर्णांकel_gt_coredump *gt);

व्योम i915_vma_capture_finish(काष्ठा पूर्णांकel_gt_coredump *gt,
			     काष्ठा i915_vma_compress *compress);

व्योम i915_error_state_store(काष्ठा i915_gpu_coredump *error);

अटल अंतरभूत काष्ठा i915_gpu_coredump *
i915_gpu_coredump_get(काष्ठा i915_gpu_coredump *gpu)
अणु
	kref_get(&gpu->ref);
	वापस gpu;
पूर्ण

sमाप_प्रकार
i915_gpu_coredump_copy_to_buffer(काष्ठा i915_gpu_coredump *error,
				 अक्षर *buf, loff_t offset, माप_प्रकार count);

व्योम __i915_gpu_coredump_मुक्त(काष्ठा kref *kref);
अटल अंतरभूत व्योम i915_gpu_coredump_put(काष्ठा i915_gpu_coredump *gpu)
अणु
	अगर (gpu)
		kref_put(&gpu->ref, __i915_gpu_coredump_मुक्त);
पूर्ण

काष्ठा i915_gpu_coredump *i915_first_error_state(काष्ठा drm_i915_निजी *i915);
व्योम i915_reset_error_state(काष्ठा drm_i915_निजी *i915);
व्योम i915_disable_error_state(काष्ठा drm_i915_निजी *i915, पूर्णांक err);

#अन्यथा

अटल अंतरभूत व्योम
i915_capture_error_state(काष्ठा पूर्णांकel_gt *gt, पूर्णांकel_engine_mask_t engine_mask)
अणु
पूर्ण

अटल अंतरभूत काष्ठा i915_gpu_coredump *
i915_gpu_coredump_alloc(काष्ठा drm_i915_निजी *i915, gfp_t gfp)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_gt_coredump *
पूर्णांकel_gt_coredump_alloc(काष्ठा पूर्णांकel_gt *gt, gfp_t gfp)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_engine_coredump *
पूर्णांकel_engine_coredump_alloc(काष्ठा पूर्णांकel_engine_cs *engine, gfp_t gfp)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_engine_capture_vma *
पूर्णांकel_engine_coredump_add_request(काष्ठा पूर्णांकel_engine_coredump *ee,
				  काष्ठा i915_request *rq,
				  gfp_t gfp)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम
पूर्णांकel_engine_coredump_add_vma(काष्ठा पूर्णांकel_engine_coredump *ee,
			      काष्ठा पूर्णांकel_engine_capture_vma *capture,
			      काष्ठा i915_vma_compress *compress)
अणु
पूर्ण

अटल अंतरभूत काष्ठा i915_vma_compress *
i915_vma_capture_prepare(काष्ठा पूर्णांकel_gt_coredump *gt)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम
i915_vma_capture_finish(काष्ठा पूर्णांकel_gt_coredump *gt,
			काष्ठा i915_vma_compress *compress)
अणु
पूर्ण

अटल अंतरभूत व्योम
i915_error_state_store(काष्ठा i915_gpu_coredump *error)
अणु
पूर्ण

अटल अंतरभूत व्योम i915_gpu_coredump_put(काष्ठा i915_gpu_coredump *gpu)
अणु
पूर्ण

अटल अंतरभूत काष्ठा i915_gpu_coredump *
i915_first_error_state(काष्ठा drm_i915_निजी *i915)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत व्योम i915_reset_error_state(काष्ठा drm_i915_निजी *i915)
अणु
पूर्ण

अटल अंतरभूत व्योम i915_disable_error_state(काष्ठा drm_i915_निजी *i915,
					    पूर्णांक err)
अणु
पूर्ण

#पूर्ण_अगर /* IS_ENABLED(CONFIG_DRM_I915_CAPTURE_ERROR) */

#पूर्ण_अगर /* _I915_GPU_ERROR_H_ */
