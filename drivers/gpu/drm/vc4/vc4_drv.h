<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2015 Broadcom
 */
#अगर_अघोषित _VC4_DRV_H_
#घोषणा _VC4_DRV_H_

#समावेश <linux/delay.h>
#समावेश <linux/refcount.h>
#समावेश <linux/uaccess.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_debugfs.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_mm.h>
#समावेश <drm/drm_modeset_lock.h>

#समावेश "uapi/drm/vc4_drm.h"

काष्ठा drm_device;
काष्ठा drm_gem_object;

/* Don't क्रमget to update vc4_bo.c: bo_type_names[] when adding to
 * this.
 */
क्रमागत vc4_kernel_bo_type अणु
	/* Any kernel allocation (gem_create_object hook) beक्रमe it
	 * माला_लो another type set.
	 */
	VC4_BO_TYPE_KERNEL,
	VC4_BO_TYPE_V3D,
	VC4_BO_TYPE_V3D_SHADER,
	VC4_BO_TYPE_DUMB,
	VC4_BO_TYPE_BIN,
	VC4_BO_TYPE_RCL,
	VC4_BO_TYPE_BCL,
	VC4_BO_TYPE_KERNEL_CACHE,
	VC4_BO_TYPE_COUNT
पूर्ण;

/* Perक्रमmance monitor object. The perक्रमm lअगरeसमय is controlled by userspace
 * using perfmon related ioctls. A perfmon can be attached to a submit_cl
 * request, and when this is the हाल, HW perf counters will be activated just
 * beक्रमe the submit_cl is submitted to the GPU and disabled when the job is
 * करोne. This way, only events related to a specअगरic job will be counted.
 */
काष्ठा vc4_perfmon अणु
	/* Tracks the number of users of the perfmon, when this counter reaches
	 * zero the perfmon is destroyed.
	 */
	refcount_t refcnt;

	/* Number of counters activated in this perfmon instance
	 * (should be less than DRM_VC4_MAX_PERF_COUNTERS).
	 */
	u8 ncounters;

	/* Events counted by the HW perf counters. */
	u8 events[DRM_VC4_MAX_PERF_COUNTERS];

	/* Storage क्रम counter values. Counters are incremented by the HW
	 * perf counter values every समय the perfmon is attached to a GPU job.
	 * This way, perfmon users करोn't have to retrieve the results after
	 * each job अगर they want to track events covering several submissions.
	 * Note that counter values can't be reset, but you can fake a reset by
	 * destroying the perfmon and creating a new one.
	 */
	u64 counters[];
पूर्ण;

काष्ठा vc4_dev अणु
	काष्ठा drm_device base;

	काष्ठा vc4_hvs *hvs;
	काष्ठा vc4_v3d *v3d;
	काष्ठा vc4_dpi *dpi;
	काष्ठा vc4_vec *vec;
	काष्ठा vc4_txp *txp;

	काष्ठा vc4_hang_state *hang_state;

	/* The kernel-space BO cache.  Tracks buffers that have been
	 * unreferenced by all other users (refcounts of 0!) but not
	 * yet मुक्तd, so we can करो cheap allocations.
	 */
	काष्ठा vc4_bo_cache अणु
		/* Array of list heads क्रम entries in the BO cache,
		 * based on number of pages, so we can करो O(1) lookups
		 * in the cache when allocating.
		 */
		काष्ठा list_head *size_list;
		uपूर्णांक32_t size_list_size;

		/* List of all BOs in the cache, ordered by age, so we
		 * can करो O(1) lookups when trying to मुक्त old
		 * buffers.
		 */
		काष्ठा list_head समय_list;
		काष्ठा work_काष्ठा समय_work;
		काष्ठा समयr_list समय_प्रकारimer;
	पूर्ण bo_cache;

	u32 num_labels;
	काष्ठा vc4_label अणु
		स्थिर अक्षर *name;
		u32 num_allocated;
		u32 size_allocated;
	पूर्ण *bo_labels;

	/* Protects bo_cache and bo_labels. */
	काष्ठा mutex bo_lock;

	/* Purgeable BO pool. All BOs in this pool can have their memory
	 * reclaimed अगर the driver is unable to allocate new BOs. We also
	 * keep stats related to the purge mechanism here.
	 */
	काष्ठा अणु
		काष्ठा list_head list;
		अचिन्हित पूर्णांक num;
		माप_प्रकार size;
		अचिन्हित पूर्णांक purged_num;
		माप_प्रकार purged_size;
		काष्ठा mutex lock;
	पूर्ण purgeable;

	uपूर्णांक64_t dma_fence_context;

	/* Sequence number क्रम the last job queued in bin_job_list.
	 * Starts at 0 (no jobs emitted).
	 */
	uपूर्णांक64_t emit_seqno;

	/* Sequence number क्रम the last completed job on the GPU.
	 * Starts at 0 (no jobs completed).
	 */
	uपूर्णांक64_t finished_seqno;

	/* List of all काष्ठा vc4_exec_info क्रम jobs to be executed in
	 * the binner.  The first job in the list is the one currently
	 * programmed पूर्णांकo ct0ca क्रम execution.
	 */
	काष्ठा list_head bin_job_list;

	/* List of all काष्ठा vc4_exec_info क्रम jobs that have
	 * completed binning and are पढ़ोy क्रम rendering.  The first
	 * job in the list is the one currently programmed पूर्णांकo ct1ca
	 * क्रम execution.
	 */
	काष्ठा list_head render_job_list;

	/* List of the finished vc4_exec_infos रुकोing to be मुक्तd by
	 * job_करोne_work.
	 */
	काष्ठा list_head job_करोne_list;
	/* Spinlock used to synchronize the job_list and seqno
	 * accesses between the IRQ handler and GEM ioctls.
	 */
	spinlock_t job_lock;
	रुको_queue_head_t job_रुको_queue;
	काष्ठा work_काष्ठा job_करोne_work;

	/* Used to track the active perfmon अगर any. Access to this field is
	 * रक्षित by job_lock.
	 */
	काष्ठा vc4_perfmon *active_perfmon;

	/* List of काष्ठा vc4_seqno_cb क्रम callbacks to be made from a
	 * workqueue when the given seqno is passed.
	 */
	काष्ठा list_head seqno_cb_list;

	/* The memory used क्रम storing binner tile alloc, tile state,
	 * and overflow memory allocations.  This is मुक्तd when V3D
	 * घातers करोwn.
	 */
	काष्ठा vc4_bo *bin_bo;

	/* Size of blocks allocated within bin_bo. */
	uपूर्णांक32_t bin_alloc_size;

	/* Biपंचांगask of the bin_alloc_size chunks in bin_bo that are
	 * used.
	 */
	uपूर्णांक32_t bin_alloc_used;

	/* Biपंचांगask of the current bin_alloc used क्रम overflow memory. */
	uपूर्णांक32_t bin_alloc_overflow;

	/* Incremented when an underrun error happened after an atomic commit.
	 * This is particularly useful to detect when a specअगरic modeset is too
	 * demanding in term of memory or HVS bandwidth which is hard to guess
	 * at atomic check समय.
	 */
	atomic_t underrun;

	काष्ठा work_काष्ठा overflow_mem_work;

	पूर्णांक घातer_refcount;

	/* Set to true when the load tracker is supported. */
	bool load_tracker_available;

	/* Set to true when the load tracker is active. */
	bool load_tracker_enabled;

	/* Mutex controlling the घातer refcount. */
	काष्ठा mutex घातer_lock;

	काष्ठा अणु
		काष्ठा समयr_list समयr;
		काष्ठा work_काष्ठा reset_work;
	पूर्ण hangcheck;

	काष्ठा drm_modeset_lock cपंचांग_state_lock;
	काष्ठा drm_निजी_obj cपंचांग_manager;
	काष्ठा drm_निजी_obj hvs_channels;
	काष्ठा drm_निजी_obj load_tracker;

	/* List of vc4_debugfs_info_entry क्रम adding to debugfs once
	 * the minor is available (after drm_dev_रेजिस्टर()).
	 */
	काष्ठा list_head debugfs_list;

	/* Mutex क्रम binner bo allocation. */
	काष्ठा mutex bin_bo_lock;
	/* Reference count क्रम our binner bo. */
	काष्ठा kref bin_bo_kref;
पूर्ण;

अटल अंतरभूत काष्ठा vc4_dev *
to_vc4_dev(काष्ठा drm_device *dev)
अणु
	वापस container_of(dev, काष्ठा vc4_dev, base);
पूर्ण

काष्ठा vc4_bo अणु
	काष्ठा drm_gem_cma_object base;

	/* seqno of the last job to render using this BO. */
	uपूर्णांक64_t seqno;

	/* seqno of the last job to use the RCL to ग_लिखो to this BO.
	 *
	 * Note that this करोesn't include binner overflow memory
	 * ग_लिखोs.
	 */
	uपूर्णांक64_t ग_लिखो_seqno;

	bool t_क्रमmat;

	/* List entry क्रम the BO's position in either
	 * vc4_exec_info->unref_list or vc4_dev->bo_cache.समय_list
	 */
	काष्ठा list_head unref_head;

	/* Time in jअगरfies when the BO was put in vc4->bo_cache. */
	अचिन्हित दीर्घ मुक्त_समय;

	/* List entry क्रम the BO's position in vc4_dev->bo_cache.size_list */
	काष्ठा list_head size_head;

	/* Struct क्रम shader validation state, अगर created by
	 * DRM_IOCTL_VC4_CREATE_SHADER_BO.
	 */
	काष्ठा vc4_validated_shader_info *validated_shader;

	/* One of क्रमागत vc4_kernel_bo_type, or VC4_BO_TYPE_COUNT + i
	 * क्रम user-allocated labels.
	 */
	पूर्णांक label;

	/* Count the number of active users. This is needed to determine
	 * whether we can move the BO to the purgeable list or not (when the BO
	 * is used by the GPU or the display engine we can't purge it).
	 */
	refcount_t usecnt;

	/* Store purgeable/purged state here */
	u32 madv;
	काष्ठा mutex madv_lock;
पूर्ण;

अटल अंतरभूत काष्ठा vc4_bo *
to_vc4_bo(काष्ठा drm_gem_object *bo)
अणु
	वापस container_of(to_drm_gem_cma_obj(bo), काष्ठा vc4_bo, base);
पूर्ण

काष्ठा vc4_fence अणु
	काष्ठा dma_fence base;
	काष्ठा drm_device *dev;
	/* vc4 seqno क्रम संकेतed() test */
	uपूर्णांक64_t seqno;
पूर्ण;

अटल अंतरभूत काष्ठा vc4_fence *
to_vc4_fence(काष्ठा dma_fence *fence)
अणु
	वापस container_of(fence, काष्ठा vc4_fence, base);
पूर्ण

काष्ठा vc4_seqno_cb अणु
	काष्ठा work_काष्ठा work;
	uपूर्णांक64_t seqno;
	व्योम (*func)(काष्ठा vc4_seqno_cb *cb);
पूर्ण;

काष्ठा vc4_v3d अणु
	काष्ठा vc4_dev *vc4;
	काष्ठा platक्रमm_device *pdev;
	व्योम __iomem *regs;
	काष्ठा clk *clk;
	काष्ठा debugfs_regset32 regset;
पूर्ण;

काष्ठा vc4_hvs अणु
	काष्ठा platक्रमm_device *pdev;
	व्योम __iomem *regs;
	u32 __iomem *dlist;

	काष्ठा clk *core_clk;

	/* Memory manager क्रम CRTCs to allocate space in the display
	 * list.  Units are dwords.
	 */
	काष्ठा drm_mm dlist_mm;
	/* Memory manager क्रम the LBM memory used by HVS scaling. */
	काष्ठा drm_mm lbm_mm;
	spinlock_t mm_lock;

	काष्ठा drm_mm_node mitchell_netravali_filter;

	काष्ठा debugfs_regset32 regset;

	/* HVS version 5 flag, thereक्रमe requires updated dlist काष्ठाures */
	bool hvs5;
पूर्ण;

काष्ठा vc4_plane अणु
	काष्ठा drm_plane base;
पूर्ण;

अटल अंतरभूत काष्ठा vc4_plane *
to_vc4_plane(काष्ठा drm_plane *plane)
अणु
	वापस container_of(plane, काष्ठा vc4_plane, base);
पूर्ण

क्रमागत vc4_scaling_mode अणु
	VC4_SCALING_NONE,
	VC4_SCALING_TPZ,
	VC4_SCALING_PPF,
पूर्ण;

काष्ठा vc4_plane_state अणु
	काष्ठा drm_plane_state base;
	/* System memory copy of the display list क्रम this element, computed
	 * at atomic_check समय.
	 */
	u32 *dlist;
	u32 dlist_size; /* Number of dwords allocated क्रम the display list */
	u32 dlist_count; /* Number of used dwords in the display list. */

	/* Offset in the dlist to various words, क्रम pageflip or
	 * cursor updates.
	 */
	u32 pos0_offset;
	u32 pos2_offset;
	u32 ptr0_offset;
	u32 lbm_offset;

	/* Offset where the plane's dlist was last stored in the
	 * hardware at vc4_crtc_atomic_flush() समय.
	 */
	u32 __iomem *hw_dlist;

	/* Clipped coordinates of the plane on the display. */
	पूर्णांक crtc_x, crtc_y, crtc_w, crtc_h;
	/* Clipped area being scanned from in the FB. */
	u32 src_x, src_y;

	u32 src_w[2], src_h[2];

	/* Scaling selection क्रम the RGB/Y plane and the Cb/Cr planes. */
	क्रमागत vc4_scaling_mode x_scaling[2], y_scaling[2];
	bool is_unity;
	bool is_yuv;

	/* Offset to start scanning out from the start of the plane's
	 * BO.
	 */
	u32 offsets[3];

	/* Our allocation in LBM क्रम temporary storage during scaling. */
	काष्ठा drm_mm_node lbm;

	/* Set when the plane has per-pixel alpha content or करोes not cover
	 * the entire screen. This is a hपूर्णांक to the CRTC that it might need
	 * to enable background color fill.
	 */
	bool needs_bg_fill;

	/* Mark the dlist as initialized. Useful to aव्योम initializing it twice
	 * when async update is not possible.
	 */
	bool dlist_initialized;

	/* Load of this plane on the HVS block. The load is expressed in HVS
	 * cycles/sec.
	 */
	u64 hvs_load;

	/* Memory bandwidth needed क्रम this plane. This is expressed in
	 * bytes/sec.
	 */
	u64 membus_load;
पूर्ण;

अटल अंतरभूत काष्ठा vc4_plane_state *
to_vc4_plane_state(काष्ठा drm_plane_state *state)
अणु
	वापस container_of(state, काष्ठा vc4_plane_state, base);
पूर्ण

क्रमागत vc4_encoder_type अणु
	VC4_ENCODER_TYPE_NONE,
	VC4_ENCODER_TYPE_HDMI0,
	VC4_ENCODER_TYPE_HDMI1,
	VC4_ENCODER_TYPE_VEC,
	VC4_ENCODER_TYPE_DSI0,
	VC4_ENCODER_TYPE_DSI1,
	VC4_ENCODER_TYPE_SMI,
	VC4_ENCODER_TYPE_DPI,
पूर्ण;

काष्ठा vc4_encoder अणु
	काष्ठा drm_encoder base;
	क्रमागत vc4_encoder_type type;
	u32 घड़ी_select;

	व्योम (*pre_crtc_configure)(काष्ठा drm_encoder *encoder, काष्ठा drm_atomic_state *state);
	व्योम (*pre_crtc_enable)(काष्ठा drm_encoder *encoder, काष्ठा drm_atomic_state *state);
	व्योम (*post_crtc_enable)(काष्ठा drm_encoder *encoder, काष्ठा drm_atomic_state *state);

	व्योम (*post_crtc_disable)(काष्ठा drm_encoder *encoder, काष्ठा drm_atomic_state *state);
	व्योम (*post_crtc_घातerकरोwn)(काष्ठा drm_encoder *encoder, काष्ठा drm_atomic_state *state);
पूर्ण;

अटल अंतरभूत काष्ठा vc4_encoder *
to_vc4_encoder(काष्ठा drm_encoder *encoder)
अणु
	वापस container_of(encoder, काष्ठा vc4_encoder, base);
पूर्ण

काष्ठा vc4_crtc_data अणु
	/* Biपंचांगask of channels (FIFOs) of the HVS that the output can source from */
	अचिन्हित पूर्णांक hvs_available_channels;

	/* Which output of the HVS this pixelvalve sources from. */
	पूर्णांक hvs_output;
पूर्ण;

काष्ठा vc4_pv_data अणु
	काष्ठा vc4_crtc_data	base;

	/* Depth of the PixelValve FIFO in bytes */
	अचिन्हित पूर्णांक fअगरo_depth;

	/* Number of pixels output per घड़ी period */
	u8 pixels_per_घड़ी;

	क्रमागत vc4_encoder_type encoder_types[4];
	स्थिर अक्षर *debugfs_name;

पूर्ण;

काष्ठा vc4_crtc अणु
	काष्ठा drm_crtc base;
	काष्ठा platक्रमm_device *pdev;
	स्थिर काष्ठा vc4_crtc_data *data;
	व्योम __iomem *regs;

	/* Timestamp at start of vblank irq - unaffected by lock delays. */
	kसमय_प्रकार t_vblank;

	u8 lut_r[256];
	u8 lut_g[256];
	u8 lut_b[256];

	काष्ठा drm_pending_vblank_event *event;

	काष्ठा debugfs_regset32 regset;
पूर्ण;

अटल अंतरभूत काष्ठा vc4_crtc *
to_vc4_crtc(काष्ठा drm_crtc *crtc)
अणु
	वापस container_of(crtc, काष्ठा vc4_crtc, base);
पूर्ण

अटल अंतरभूत स्थिर काष्ठा vc4_crtc_data *
vc4_crtc_to_vc4_crtc_data(स्थिर काष्ठा vc4_crtc *crtc)
अणु
	वापस crtc->data;
पूर्ण

अटल अंतरभूत स्थिर काष्ठा vc4_pv_data *
vc4_crtc_to_vc4_pv_data(स्थिर काष्ठा vc4_crtc *crtc)
अणु
	स्थिर काष्ठा vc4_crtc_data *data = vc4_crtc_to_vc4_crtc_data(crtc);

	वापस container_of(data, काष्ठा vc4_pv_data, base);
पूर्ण

काष्ठा vc4_crtc_state अणु
	काष्ठा drm_crtc_state base;
	/* Dlist area क्रम this CRTC configuration. */
	काष्ठा drm_mm_node mm;
	bool feed_txp;
	bool txp_armed;
	अचिन्हित पूर्णांक asचिन्हित_channel;

	काष्ठा अणु
		अचिन्हित पूर्णांक left;
		अचिन्हित पूर्णांक right;
		अचिन्हित पूर्णांक top;
		अचिन्हित पूर्णांक bottom;
	पूर्ण margins;

	/* Transitional state below, only valid during atomic commits */
	bool update_muxing;
पूर्ण;

#घोषणा VC4_HVS_CHANNEL_DISABLED ((अचिन्हित पूर्णांक)-1)

अटल अंतरभूत काष्ठा vc4_crtc_state *
to_vc4_crtc_state(काष्ठा drm_crtc_state *crtc_state)
अणु
	वापस container_of(crtc_state, काष्ठा vc4_crtc_state, base);
पूर्ण

#घोषणा V3D_READ(offset) पढ़ोl(vc4->v3d->regs + offset)
#घोषणा V3D_WRITE(offset, val) ग_लिखोl(val, vc4->v3d->regs + offset)
#घोषणा HVS_READ(offset) पढ़ोl(vc4->hvs->regs + offset)
#घोषणा HVS_WRITE(offset, val) ग_लिखोl(val, vc4->hvs->regs + offset)

#घोषणा VC4_REG32(reg) अणु .name = #reg, .offset = reg पूर्ण

काष्ठा vc4_exec_info अणु
	/* Sequence number क्रम this bin/render job. */
	uपूर्णांक64_t seqno;

	/* Latest ग_लिखो_seqno of any BO that binning depends on. */
	uपूर्णांक64_t bin_dep_seqno;

	काष्ठा dma_fence *fence;

	/* Last current addresses the hardware was processing when the
	 * hangcheck समयr checked on us.
	 */
	uपूर्णांक32_t last_ct0ca, last_ct1ca;

	/* Kernel-space copy of the ioctl arguments */
	काष्ठा drm_vc4_submit_cl *args;

	/* This is the array of BOs that were looked up at the start of exec.
	 * Command validation will use indices पूर्णांकo this array.
	 */
	काष्ठा drm_gem_cma_object **bo;
	uपूर्णांक32_t bo_count;

	/* List of BOs that are being written by the RCL.  Other than
	 * the binner temporary storage, this is all the BOs written
	 * by the job.
	 */
	काष्ठा drm_gem_cma_object *rcl_ग_लिखो_bo[4];
	uपूर्णांक32_t rcl_ग_लिखो_bo_count;

	/* Poपूर्णांकers क्रम our position in vc4->job_list */
	काष्ठा list_head head;

	/* List of other BOs used in the job that need to be released
	 * once the job is complete.
	 */
	काष्ठा list_head unref_list;

	/* Current unvalidated indices पूर्णांकo @bo loaded by the non-hardware
	 * VC4_PACKET_GEM_HANDLES.
	 */
	uपूर्णांक32_t bo_index[2];

	/* This is the BO where we store the validated command lists, shader
	 * records, and unअगरorms.
	 */
	काष्ठा drm_gem_cma_object *exec_bo;

	/**
	 * This tracks the per-shader-record state (packet 64) that
	 * determines the length of the shader record and the offset
	 * it's expected to be found at.  It माला_लो पढ़ो in from the
	 * command lists.
	 */
	काष्ठा vc4_shader_state अणु
		uपूर्णांक32_t addr;
		/* Maximum vertex index referenced by any primitive using this
		 * shader state.
		 */
		uपूर्णांक32_t max_index;
	पूर्ण *shader_state;

	/** How many shader states the user declared they were using. */
	uपूर्णांक32_t shader_state_size;
	/** How many shader state records the validator has seen. */
	uपूर्णांक32_t shader_state_count;

	bool found_tile_binning_mode_config_packet;
	bool found_start_tile_binning_packet;
	bool found_increment_semaphore_packet;
	bool found_flush;
	uपूर्णांक8_t bin_tiles_x, bin_tiles_y;
	/* Physical address of the start of the tile alloc array
	 * (where each tile's binned CL will start)
	 */
	uपूर्णांक32_t tile_alloc_offset;
	/* Biपंचांगask of which binner slots are मुक्तd when this job completes. */
	uपूर्णांक32_t bin_slots;

	/**
	 * Computed addresses poपूर्णांकing पूर्णांकo exec_bo where we start the
	 * bin thपढ़ो (ct0) and render thपढ़ो (ct1).
	 */
	uपूर्णांक32_t ct0ca, ct0ea;
	uपूर्णांक32_t ct1ca, ct1ea;

	/* Poपूर्णांकer to the unvalidated bin CL (अगर present). */
	व्योम *bin_u;

	/* Poपूर्णांकers to the shader recs.  These paddr माला_लो incremented as CL
	 * packets are relocated in validate_gl_shader_state, and the vaddrs
	 * (u and v) get incremented and size decremented as the shader recs
	 * themselves are validated.
	 */
	व्योम *shader_rec_u;
	व्योम *shader_rec_v;
	uपूर्णांक32_t shader_rec_p;
	uपूर्णांक32_t shader_rec_size;

	/* Poपूर्णांकers to the unअगरorm data.  These poपूर्णांकers are incremented, and
	 * size decremented, as each batch of unअगरorms is uploaded.
	 */
	व्योम *unअगरorms_u;
	व्योम *unअगरorms_v;
	uपूर्णांक32_t unअगरorms_p;
	uपूर्णांक32_t unअगरorms_size;

	/* Poपूर्णांकer to a perक्रमmance monitor object अगर the user requested it,
	 * शून्य otherwise.
	 */
	काष्ठा vc4_perfmon *perfmon;

	/* Whether the exec has taken a reference to the binner BO, which should
	 * happen with a VC4_PACKET_TILE_BINNING_MODE_CONFIG packet.
	 */
	bool bin_bo_used;
पूर्ण;

/* Per-खोलो file निजी data. Any driver-specअगरic resource that has to be
 * released when the DRM file is बंदd should be placed here.
 */
काष्ठा vc4_file अणु
	काष्ठा अणु
		काष्ठा idr idr;
		काष्ठा mutex lock;
	पूर्ण perfmon;

	bool bin_bo_used;
पूर्ण;

अटल अंतरभूत काष्ठा vc4_exec_info *
vc4_first_bin_job(काष्ठा vc4_dev *vc4)
अणु
	वापस list_first_entry_or_null(&vc4->bin_job_list,
					काष्ठा vc4_exec_info, head);
पूर्ण

अटल अंतरभूत काष्ठा vc4_exec_info *
vc4_first_render_job(काष्ठा vc4_dev *vc4)
अणु
	वापस list_first_entry_or_null(&vc4->render_job_list,
					काष्ठा vc4_exec_info, head);
पूर्ण

अटल अंतरभूत काष्ठा vc4_exec_info *
vc4_last_render_job(काष्ठा vc4_dev *vc4)
अणु
	अगर (list_empty(&vc4->render_job_list))
		वापस शून्य;
	वापस list_last_entry(&vc4->render_job_list,
			       काष्ठा vc4_exec_info, head);
पूर्ण

/**
 * काष्ठा vc4_texture_sample_info - saves the offsets पूर्णांकo the UBO क्रम texture
 * setup parameters.
 *
 * This will be used at draw समय to relocate the reference to the texture
 * contents in p0, and validate that the offset combined with
 * width/height/stride/etc. from p1 and p2/p3 करोesn't sample outside the BO.
 * Note that the hardware treats unprovided config parameters as 0, so not all
 * of them need to be set up क्रम every texure sample, and we'll store ~0 as
 * the offset to mark the unused ones.
 *
 * See the VC4 3D architecture guide page 41 ("Texture and Memory Lookup Unit
 * Setup") क्रम definitions of the texture parameters.
 */
काष्ठा vc4_texture_sample_info अणु
	bool is_direct;
	uपूर्णांक32_t p_offset[4];
पूर्ण;

/**
 * काष्ठा vc4_validated_shader_info - inक्रमmation about validated shaders that
 * needs to be used from command list validation.
 *
 * For a given shader, each समय a shader state record references it, we need
 * to verअगरy that the shader करोesn't पढ़ो more unअगरorms than the shader state
 * record's unअगरorm BO poपूर्णांकer can provide, and we need to apply relocations
 * and validate the shader state record's unअगरorms that define the texture
 * samples.
 */
काष्ठा vc4_validated_shader_info अणु
	uपूर्णांक32_t unअगरorms_size;
	uपूर्णांक32_t unअगरorms_src_size;
	uपूर्णांक32_t num_texture_samples;
	काष्ठा vc4_texture_sample_info *texture_samples;

	uपूर्णांक32_t num_unअगरorm_addr_offsets;
	uपूर्णांक32_t *unअगरorm_addr_offsets;

	bool is_thपढ़ोed;
पूर्ण;

/**
 * __रुको_क्रम - magic रुको macro
 *
 * Macro to help aव्योम खोलो coding check/रुको/समयout patterns. Note that it's
 * important that we check the condition again after having समयd out, since the
 * समयout could be due to preemption or similar and we've never had a chance to
 * check the condition beक्रमe the समयout.
 */
#घोषणा __रुको_क्रम(OP, COND, US, Wmin, Wmax) (अणु \
	स्थिर kसमय_प्रकार end__ = kसमय_add_ns(kसमय_get_raw(), 1000ll * (US)); \
	दीर्घ रुको__ = (Wmin); /* recommended min क्रम usleep is 10 us */	\
	पूर्णांक ret__;							\
	might_sleep();							\
	क्रम (;;) अणु							\
		स्थिर bool expired__ = kसमय_after(kसमय_get_raw(), end__); \
		OP;							\
		/* Guarantee COND check prior to समयout */		\
		barrier();						\
		अगर (COND) अणु						\
			ret__ = 0;					\
			अवरोध;						\
		पूर्ण							\
		अगर (expired__) अणु					\
			ret__ = -ETIMEDOUT;				\
			अवरोध;						\
		पूर्ण							\
		usleep_range(रुको__, रुको__ * 2);			\
		अगर (रुको__ < (Wmax))					\
			रुको__ <<= 1;					\
	पूर्ण								\
	ret__;								\
पूर्ण)

#घोषणा _रुको_क्रम(COND, US, Wmin, Wmax)	__रुको_क्रम(, (COND), (US), (Wmin), \
						   (Wmax))
#घोषणा रुको_क्रम(COND, MS)		_रुको_क्रम((COND), (MS) * 1000, 10, 1000)

/* vc4_bo.c */
काष्ठा drm_gem_object *vc4_create_object(काष्ठा drm_device *dev, माप_प्रकार size);
काष्ठा vc4_bo *vc4_bo_create(काष्ठा drm_device *dev, माप_प्रकार size,
			     bool from_cache, क्रमागत vc4_kernel_bo_type type);
पूर्णांक vc4_dumb_create(काष्ठा drm_file *file_priv,
		    काष्ठा drm_device *dev,
		    काष्ठा drm_mode_create_dumb *args);
पूर्णांक vc4_create_bo_ioctl(काष्ठा drm_device *dev, व्योम *data,
			काष्ठा drm_file *file_priv);
पूर्णांक vc4_create_shader_bo_ioctl(काष्ठा drm_device *dev, व्योम *data,
			       काष्ठा drm_file *file_priv);
पूर्णांक vc4_mmap_bo_ioctl(काष्ठा drm_device *dev, व्योम *data,
		      काष्ठा drm_file *file_priv);
पूर्णांक vc4_set_tiling_ioctl(काष्ठा drm_device *dev, व्योम *data,
			 काष्ठा drm_file *file_priv);
पूर्णांक vc4_get_tiling_ioctl(काष्ठा drm_device *dev, व्योम *data,
			 काष्ठा drm_file *file_priv);
पूर्णांक vc4_get_hang_state_ioctl(काष्ठा drm_device *dev, व्योम *data,
			     काष्ठा drm_file *file_priv);
पूर्णांक vc4_label_bo_ioctl(काष्ठा drm_device *dev, व्योम *data,
		       काष्ठा drm_file *file_priv);
पूर्णांक vc4_bo_cache_init(काष्ठा drm_device *dev);
पूर्णांक vc4_bo_inc_usecnt(काष्ठा vc4_bo *bo);
व्योम vc4_bo_dec_usecnt(काष्ठा vc4_bo *bo);
व्योम vc4_bo_add_to_purgeable_pool(काष्ठा vc4_bo *bo);
व्योम vc4_bo_हटाओ_from_purgeable_pool(काष्ठा vc4_bo *bo);

/* vc4_crtc.c */
बाह्य काष्ठा platक्रमm_driver vc4_crtc_driver;
पूर्णांक vc4_crtc_disable_at_boot(काष्ठा drm_crtc *crtc);
पूर्णांक vc4_crtc_init(काष्ठा drm_device *drm, काष्ठा vc4_crtc *vc4_crtc,
		  स्थिर काष्ठा drm_crtc_funcs *crtc_funcs,
		  स्थिर काष्ठा drm_crtc_helper_funcs *crtc_helper_funcs);
व्योम vc4_crtc_destroy(काष्ठा drm_crtc *crtc);
पूर्णांक vc4_page_flip(काष्ठा drm_crtc *crtc,
		  काष्ठा drm_framebuffer *fb,
		  काष्ठा drm_pending_vblank_event *event,
		  uपूर्णांक32_t flags,
		  काष्ठा drm_modeset_acquire_ctx *ctx);
काष्ठा drm_crtc_state *vc4_crtc_duplicate_state(काष्ठा drm_crtc *crtc);
व्योम vc4_crtc_destroy_state(काष्ठा drm_crtc *crtc,
			    काष्ठा drm_crtc_state *state);
व्योम vc4_crtc_reset(काष्ठा drm_crtc *crtc);
व्योम vc4_crtc_handle_vblank(काष्ठा vc4_crtc *crtc);
व्योम vc4_crtc_get_margins(काष्ठा drm_crtc_state *state,
			  अचिन्हित पूर्णांक *right, अचिन्हित पूर्णांक *left,
			  अचिन्हित पूर्णांक *top, अचिन्हित पूर्णांक *bottom);

/* vc4_debugfs.c */
व्योम vc4_debugfs_init(काष्ठा drm_minor *minor);
#अगर_घोषित CONFIG_DEBUG_FS
व्योम vc4_debugfs_add_file(काष्ठा drm_device *drm,
			  स्थिर अक्षर *filename,
			  पूर्णांक (*show)(काष्ठा seq_file*, व्योम*),
			  व्योम *data);
व्योम vc4_debugfs_add_regset32(काष्ठा drm_device *drm,
			      स्थिर अक्षर *filename,
			      काष्ठा debugfs_regset32 *regset);
#अन्यथा
अटल अंतरभूत व्योम vc4_debugfs_add_file(काष्ठा drm_device *drm,
					स्थिर अक्षर *filename,
					पूर्णांक (*show)(काष्ठा seq_file*, व्योम*),
					व्योम *data)
अणु
पूर्ण

अटल अंतरभूत व्योम vc4_debugfs_add_regset32(काष्ठा drm_device *drm,
					    स्थिर अक्षर *filename,
					    काष्ठा debugfs_regset32 *regset)
अणु
पूर्ण
#पूर्ण_अगर

/* vc4_drv.c */
व्योम __iomem *vc4_ioremap_regs(काष्ठा platक्रमm_device *dev, पूर्णांक index);

/* vc4_dpi.c */
बाह्य काष्ठा platक्रमm_driver vc4_dpi_driver;

/* vc4_dsi.c */
बाह्य काष्ठा platक्रमm_driver vc4_dsi_driver;

/* vc4_fence.c */
बाह्य स्थिर काष्ठा dma_fence_ops vc4_fence_ops;

/* vc4_gem.c */
पूर्णांक vc4_gem_init(काष्ठा drm_device *dev);
पूर्णांक vc4_submit_cl_ioctl(काष्ठा drm_device *dev, व्योम *data,
			काष्ठा drm_file *file_priv);
पूर्णांक vc4_रुको_seqno_ioctl(काष्ठा drm_device *dev, व्योम *data,
			 काष्ठा drm_file *file_priv);
पूर्णांक vc4_रुको_bo_ioctl(काष्ठा drm_device *dev, व्योम *data,
		      काष्ठा drm_file *file_priv);
व्योम vc4_submit_next_bin_job(काष्ठा drm_device *dev);
व्योम vc4_submit_next_render_job(काष्ठा drm_device *dev);
व्योम vc4_move_job_to_render(काष्ठा drm_device *dev, काष्ठा vc4_exec_info *exec);
पूर्णांक vc4_रुको_क्रम_seqno(काष्ठा drm_device *dev, uपूर्णांक64_t seqno,
		       uपूर्णांक64_t समयout_ns, bool पूर्णांकerruptible);
व्योम vc4_job_handle_completed(काष्ठा vc4_dev *vc4);
पूर्णांक vc4_queue_seqno_cb(काष्ठा drm_device *dev,
		       काष्ठा vc4_seqno_cb *cb, uपूर्णांक64_t seqno,
		       व्योम (*func)(काष्ठा vc4_seqno_cb *cb));
पूर्णांक vc4_gem_madvise_ioctl(काष्ठा drm_device *dev, व्योम *data,
			  काष्ठा drm_file *file_priv);

/* vc4_hdmi.c */
बाह्य काष्ठा platक्रमm_driver vc4_hdmi_driver;

/* vc4_vec.c */
बाह्य काष्ठा platक्रमm_driver vc4_vec_driver;

/* vc4_txp.c */
बाह्य काष्ठा platक्रमm_driver vc4_txp_driver;

/* vc4_irq.c */
irqवापस_t vc4_irq(पूर्णांक irq, व्योम *arg);
व्योम vc4_irq_preinstall(काष्ठा drm_device *dev);
पूर्णांक vc4_irq_postinstall(काष्ठा drm_device *dev);
व्योम vc4_irq_uninstall(काष्ठा drm_device *dev);
व्योम vc4_irq_reset(काष्ठा drm_device *dev);

/* vc4_hvs.c */
बाह्य काष्ठा platक्रमm_driver vc4_hvs_driver;
व्योम vc4_hvs_stop_channel(काष्ठा drm_device *dev, अचिन्हित पूर्णांक output);
पूर्णांक vc4_hvs_get_fअगरo_from_output(काष्ठा drm_device *dev, अचिन्हित पूर्णांक output);
पूर्णांक vc4_hvs_atomic_check(काष्ठा drm_crtc *crtc, काष्ठा drm_atomic_state *state);
व्योम vc4_hvs_atomic_enable(काष्ठा drm_crtc *crtc, काष्ठा drm_atomic_state *state);
व्योम vc4_hvs_atomic_disable(काष्ठा drm_crtc *crtc, काष्ठा drm_atomic_state *state);
व्योम vc4_hvs_atomic_flush(काष्ठा drm_crtc *crtc, काष्ठा drm_atomic_state *state);
व्योम vc4_hvs_dump_state(काष्ठा drm_device *dev);
व्योम vc4_hvs_unmask_underrun(काष्ठा drm_device *dev, पूर्णांक channel);
व्योम vc4_hvs_mask_underrun(काष्ठा drm_device *dev, पूर्णांक channel);

/* vc4_kms.c */
पूर्णांक vc4_kms_load(काष्ठा drm_device *dev);

/* vc4_plane.c */
काष्ठा drm_plane *vc4_plane_init(काष्ठा drm_device *dev,
				 क्रमागत drm_plane_type type);
पूर्णांक vc4_plane_create_additional_planes(काष्ठा drm_device *dev);
u32 vc4_plane_ग_लिखो_dlist(काष्ठा drm_plane *plane, u32 __iomem *dlist);
u32 vc4_plane_dlist_size(स्थिर काष्ठा drm_plane_state *state);
व्योम vc4_plane_async_set_fb(काष्ठा drm_plane *plane,
			    काष्ठा drm_framebuffer *fb);

/* vc4_v3d.c */
बाह्य काष्ठा platक्रमm_driver vc4_v3d_driver;
बाह्य स्थिर काष्ठा of_device_id vc4_v3d_dt_match[];
पूर्णांक vc4_v3d_get_bin_slot(काष्ठा vc4_dev *vc4);
पूर्णांक vc4_v3d_bin_bo_get(काष्ठा vc4_dev *vc4, bool *used);
व्योम vc4_v3d_bin_bo_put(काष्ठा vc4_dev *vc4);
पूर्णांक vc4_v3d_pm_get(काष्ठा vc4_dev *vc4);
व्योम vc4_v3d_pm_put(काष्ठा vc4_dev *vc4);

/* vc4_validate.c */
पूर्णांक
vc4_validate_bin_cl(काष्ठा drm_device *dev,
		    व्योम *validated,
		    व्योम *unvalidated,
		    काष्ठा vc4_exec_info *exec);

पूर्णांक
vc4_validate_shader_recs(काष्ठा drm_device *dev, काष्ठा vc4_exec_info *exec);

काष्ठा drm_gem_cma_object *vc4_use_bo(काष्ठा vc4_exec_info *exec,
				      uपूर्णांक32_t hindex);

पूर्णांक vc4_get_rcl(काष्ठा drm_device *dev, काष्ठा vc4_exec_info *exec);

bool vc4_check_tex_size(काष्ठा vc4_exec_info *exec,
			काष्ठा drm_gem_cma_object *fbo,
			uपूर्णांक32_t offset, uपूर्णांक8_t tiling_क्रमmat,
			uपूर्णांक32_t width, uपूर्णांक32_t height, uपूर्णांक8_t cpp);

/* vc4_validate_shader.c */
काष्ठा vc4_validated_shader_info *
vc4_validate_shader(काष्ठा drm_gem_cma_object *shader_obj);

/* vc4_perfmon.c */
व्योम vc4_perfmon_get(काष्ठा vc4_perfmon *perfmon);
व्योम vc4_perfmon_put(काष्ठा vc4_perfmon *perfmon);
व्योम vc4_perfmon_start(काष्ठा vc4_dev *vc4, काष्ठा vc4_perfmon *perfmon);
व्योम vc4_perfmon_stop(काष्ठा vc4_dev *vc4, काष्ठा vc4_perfmon *perfmon,
		      bool capture);
काष्ठा vc4_perfmon *vc4_perfmon_find(काष्ठा vc4_file *vc4file, पूर्णांक id);
व्योम vc4_perfmon_खोलो_file(काष्ठा vc4_file *vc4file);
व्योम vc4_perfmon_बंद_file(काष्ठा vc4_file *vc4file);
पूर्णांक vc4_perfmon_create_ioctl(काष्ठा drm_device *dev, व्योम *data,
			     काष्ठा drm_file *file_priv);
पूर्णांक vc4_perfmon_destroy_ioctl(काष्ठा drm_device *dev, व्योम *data,
			      काष्ठा drm_file *file_priv);
पूर्णांक vc4_perfmon_get_values_ioctl(काष्ठा drm_device *dev, व्योम *data,
				 काष्ठा drm_file *file_priv);

#पूर्ण_अगर /* _VC4_DRV_H_ */
