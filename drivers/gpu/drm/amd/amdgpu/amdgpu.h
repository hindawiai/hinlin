<शैली गुरु>
/*
 * Copyright 2008 Advanced Micro Devices, Inc.
 * Copyright 2008 Red Hat Inc.
 * Copyright 2009 Jerome Glisse.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Dave Airlie
 *          Alex Deucher
 *          Jerome Glisse
 */
#अगर_अघोषित __AMDGPU_H__
#घोषणा __AMDGPU_H__

#अगर_घोषित pr_fmt
#अघोषित pr_fmt
#पूर्ण_अगर

#घोषणा pr_fmt(fmt) "amdgpu: " fmt

#अगर_घोषित dev_fmt
#अघोषित dev_fmt
#पूर्ण_अगर

#घोषणा dev_fmt(fmt) "amdgpu: " fmt

#समावेश "amdgpu_ctx.h"

#समावेश <linux/atomic.h>
#समावेश <linux/रुको.h>
#समावेश <linux/list.h>
#समावेश <linux/kref.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/hashtable.h>
#समावेश <linux/dma-fence.h>
#समावेश <linux/pci.h>
#समावेश <linux/aer.h>

#समावेश <drm/tपंचांग/tपंचांग_bo_api.h>
#समावेश <drm/tपंचांग/tपंचांग_bo_driver.h>
#समावेश <drm/tपंचांग/tपंचांग_placement.h>
#समावेश <drm/tपंचांग/tपंचांग_execbuf_util.h>

#समावेश <drm/amdgpu_drm.h>
#समावेश <drm/drm_gem.h>
#समावेश <drm/drm_ioctl.h>
#समावेश <drm/gpu_scheduler.h>

#समावेश <kgd_kfd_पूर्णांकerface.h>
#समावेश "dm_pp_interface.h"
#समावेश "kgd_pp_interface.h"

#समावेश "amd_shared.h"
#समावेश "amdgpu_mode.h"
#समावेश "amdgpu_ih.h"
#समावेश "amdgpu_irq.h"
#समावेश "amdgpu_ucode.h"
#समावेश "amdgpu_ttm.h"
#समावेश "amdgpu_psp.h"
#समावेश "amdgpu_gds.h"
#समावेश "amdgpu_sync.h"
#समावेश "amdgpu_ring.h"
#समावेश "amdgpu_vm.h"
#समावेश "amdgpu_dpm.h"
#समावेश "amdgpu_acp.h"
#समावेश "amdgpu_uvd.h"
#समावेश "amdgpu_vce.h"
#समावेश "amdgpu_vcn.h"
#समावेश "amdgpu_jpeg.h"
#समावेश "amdgpu_mn.h"
#समावेश "amdgpu_gmc.h"
#समावेश "amdgpu_gfx.h"
#समावेश "amdgpu_sdma.h"
#समावेश "amdgpu_nbio.h"
#समावेश "amdgpu_hdp.h"
#समावेश "amdgpu_dm.h"
#समावेश "amdgpu_virt.h"
#समावेश "amdgpu_csa.h"
#समावेश "amdgpu_gart.h"
#समावेश "amdgpu_debugfs.h"
#समावेश "amdgpu_job.h"
#समावेश "amdgpu_bo_list.h"
#समावेश "amdgpu_gem.h"
#समावेश "amdgpu_doorbell.h"
#समावेश "amdgpu_amdkfd.h"
#समावेश "amdgpu_smu.h"
#समावेश "amdgpu_discovery.h"
#समावेश "amdgpu_mes.h"
#समावेश "amdgpu_umc.h"
#समावेश "amdgpu_mmhub.h"
#समावेश "amdgpu_gfxhub.h"
#समावेश "amdgpu_df.h"
#समावेश "amdgpu_smuio.h"

#घोषणा MAX_GPU_INSTANCE		16

काष्ठा amdgpu_gpu_instance
अणु
	काष्ठा amdgpu_device		*adev;
	पूर्णांक				mgpu_fan_enabled;
पूर्ण;

काष्ठा amdgpu_mgpu_info
अणु
	काष्ठा amdgpu_gpu_instance	gpu_ins[MAX_GPU_INSTANCE];
	काष्ठा mutex			mutex;
	uपूर्णांक32_t			num_gpu;
	uपूर्णांक32_t			num_dgpu;
	uपूर्णांक32_t			num_apu;

	/* delayed reset_func क्रम XGMI configuration अगर necessary */
	काष्ठा delayed_work		delayed_reset_work;
	bool				pending_reset;
पूर्ण;

काष्ठा amdgpu_watchकरोg_समयr
अणु
	bool समयout_fatal_disable;
	uपूर्णांक32_t period; /* maxCycles = (1 << period), the number of cycles beक्रमe a समयout */
पूर्ण;

#घोषणा AMDGPU_MAX_TIMEOUT_PARAM_LENGTH	256

/*
 * Modules parameters.
 */
बाह्य पूर्णांक amdgpu_modeset;
बाह्य पूर्णांक amdgpu_vram_limit;
बाह्य पूर्णांक amdgpu_vis_vram_limit;
बाह्य पूर्णांक amdgpu_gart_size;
बाह्य पूर्णांक amdgpu_gtt_size;
बाह्य पूर्णांक amdgpu_moverate;
बाह्य पूर्णांक amdgpu_benchmarking;
बाह्य पूर्णांक amdgpu_testing;
बाह्य पूर्णांक amdgpu_audio;
बाह्य पूर्णांक amdgpu_disp_priority;
बाह्य पूर्णांक amdgpu_hw_i2c;
बाह्य पूर्णांक amdgpu_pcie_gen2;
बाह्य पूर्णांक amdgpu_msi;
बाह्य अक्षर amdgpu_lockup_समयout[AMDGPU_MAX_TIMEOUT_PARAM_LENGTH];
बाह्य पूर्णांक amdgpu_dpm;
बाह्य पूर्णांक amdgpu_fw_load_type;
बाह्य पूर्णांक amdgpu_aspm;
बाह्य पूर्णांक amdgpu_runसमय_pm;
बाह्य uपूर्णांक amdgpu_ip_block_mask;
बाह्य पूर्णांक amdgpu_bapm;
बाह्य पूर्णांक amdgpu_deep_color;
बाह्य पूर्णांक amdgpu_vm_size;
बाह्य पूर्णांक amdgpu_vm_block_size;
बाह्य पूर्णांक amdgpu_vm_fragment_size;
बाह्य पूर्णांक amdgpu_vm_fault_stop;
बाह्य पूर्णांक amdgpu_vm_debug;
बाह्य पूर्णांक amdgpu_vm_update_mode;
बाह्य पूर्णांक amdgpu_exp_hw_support;
बाह्य पूर्णांक amdgpu_dc;
बाह्य पूर्णांक amdgpu_sched_jobs;
बाह्य पूर्णांक amdgpu_sched_hw_submission;
बाह्य uपूर्णांक amdgpu_pcie_gen_cap;
बाह्य uपूर्णांक amdgpu_pcie_lane_cap;
बाह्य uपूर्णांक amdgpu_cg_mask;
बाह्य uपूर्णांक amdgpu_pg_mask;
बाह्य uपूर्णांक amdgpu_sdma_phase_quantum;
बाह्य अक्षर *amdgpu_disable_cu;
बाह्य अक्षर *amdgpu_भव_display;
बाह्य uपूर्णांक amdgpu_pp_feature_mask;
बाह्य uपूर्णांक amdgpu_क्रमce_दीर्घ_training;
बाह्य पूर्णांक amdgpu_job_hang_limit;
बाह्य पूर्णांक amdgpu_lbpw;
बाह्य पूर्णांक amdgpu_compute_multipipe;
बाह्य पूर्णांक amdgpu_gpu_recovery;
बाह्य पूर्णांक amdgpu_emu_mode;
बाह्य uपूर्णांक amdgpu_smu_memory_pool_size;
बाह्य पूर्णांक amdgpu_smu_pptable_id;
बाह्य uपूर्णांक amdgpu_dc_feature_mask;
बाह्य uपूर्णांक amdgpu_मुक्तsync_vid_mode;
बाह्य uपूर्णांक amdgpu_dc_debug_mask;
बाह्य uपूर्णांक amdgpu_dm_abm_level;
बाह्य पूर्णांक amdgpu_backlight;
बाह्य काष्ठा amdgpu_mgpu_info mgpu_info;
बाह्य पूर्णांक amdgpu_ras_enable;
बाह्य uपूर्णांक amdgpu_ras_mask;
बाह्य पूर्णांक amdgpu_bad_page_threshold;
बाह्य काष्ठा amdgpu_watchकरोg_समयr amdgpu_watchकरोg_समयr;
बाह्य पूर्णांक amdgpu_async_gfx_ring;
बाह्य पूर्णांक amdgpu_mcbp;
बाह्य पूर्णांक amdgpu_discovery;
बाह्य पूर्णांक amdgpu_mes;
बाह्य पूर्णांक amdgpu_noretry;
बाह्य पूर्णांक amdgpu_क्रमce_asic_type;
#अगर_घोषित CONFIG_HSA_AMD
बाह्य पूर्णांक sched_policy;
बाह्य bool debug_evictions;
बाह्य bool no_प्रणाली_mem_limit;
#अन्यथा
अटल स्थिर पूर्णांक __maybe_unused sched_policy = KFD_SCHED_POLICY_HWS;
अटल स्थिर bool __maybe_unused debug_evictions; /* = false */
अटल स्थिर bool __maybe_unused no_प्रणाली_mem_limit;
#पूर्ण_अगर

बाह्य पूर्णांक amdgpu_पंचांगz;
बाह्य पूर्णांक amdgpu_reset_method;

#अगर_घोषित CONFIG_DRM_AMDGPU_SI
बाह्य पूर्णांक amdgpu_si_support;
#पूर्ण_अगर
#अगर_घोषित CONFIG_DRM_AMDGPU_CIK
बाह्य पूर्णांक amdgpu_cik_support;
#पूर्ण_अगर
बाह्य पूर्णांक amdgpu_num_kcq;

#घोषणा AMDGPU_VM_MAX_NUM_CTX			4096
#घोषणा AMDGPU_SG_THRESHOLD			(256*1024*1024)
#घोषणा AMDGPU_DEFAULT_GTT_SIZE_MB		3072ULL /* 3GB by शेष */
#घोषणा AMDGPU_WAIT_IDLE_TIMEOUT_IN_MS	        3000
#घोषणा AMDGPU_MAX_USEC_TIMEOUT			100000	/* 100 ms */
#घोषणा AMDGPU_FENCE_JIFFIES_TIMEOUT		(HZ / 2)
#घोषणा AMDGPU_DEBUGFS_MAX_COMPONENTS		32
#घोषणा AMDGPUFB_CONN_LIMIT			4
#घोषणा AMDGPU_BIOS_NUM_SCRATCH			16

#घोषणा AMDGPU_VBIOS_VGA_ALLOCATION		(9 * 1024 * 1024) /* reserve 8MB क्रम vga emulator and 1 MB क्रम FB */

/* hard reset data */
#घोषणा AMDGPU_ASIC_RESET_DATA                  0x39d5e86b

/* reset flags */
#घोषणा AMDGPU_RESET_GFX			(1 << 0)
#घोषणा AMDGPU_RESET_COMPUTE			(1 << 1)
#घोषणा AMDGPU_RESET_DMA			(1 << 2)
#घोषणा AMDGPU_RESET_CP				(1 << 3)
#घोषणा AMDGPU_RESET_GRBM			(1 << 4)
#घोषणा AMDGPU_RESET_DMA1			(1 << 5)
#घोषणा AMDGPU_RESET_RLC			(1 << 6)
#घोषणा AMDGPU_RESET_SEM			(1 << 7)
#घोषणा AMDGPU_RESET_IH				(1 << 8)
#घोषणा AMDGPU_RESET_VMC			(1 << 9)
#घोषणा AMDGPU_RESET_MC				(1 << 10)
#घोषणा AMDGPU_RESET_DISPLAY			(1 << 11)
#घोषणा AMDGPU_RESET_UVD			(1 << 12)
#घोषणा AMDGPU_RESET_VCE			(1 << 13)
#घोषणा AMDGPU_RESET_VCE1			(1 << 14)

/* max cursor sizes (in pixels) */
#घोषणा CIK_CURSOR_WIDTH 128
#घोषणा CIK_CURSOR_HEIGHT 128

काष्ठा amdgpu_device;
काष्ठा amdgpu_ib;
काष्ठा amdgpu_cs_parser;
काष्ठा amdgpu_job;
काष्ठा amdgpu_irq_src;
काष्ठा amdgpu_fpriv;
काष्ठा amdgpu_bo_va_mapping;
काष्ठा amdgpu_atअगर;
काष्ठा kfd_vm_fault_info;
काष्ठा amdgpu_hive_info;
काष्ठा amdgpu_reset_context;
काष्ठा amdgpu_reset_control;

क्रमागत amdgpu_cp_irq अणु
	AMDGPU_CP_IRQ_GFX_ME0_PIPE0_EOP = 0,
	AMDGPU_CP_IRQ_GFX_ME0_PIPE1_EOP,
	AMDGPU_CP_IRQ_COMPUTE_MEC1_PIPE0_EOP,
	AMDGPU_CP_IRQ_COMPUTE_MEC1_PIPE1_EOP,
	AMDGPU_CP_IRQ_COMPUTE_MEC1_PIPE2_EOP,
	AMDGPU_CP_IRQ_COMPUTE_MEC1_PIPE3_EOP,
	AMDGPU_CP_IRQ_COMPUTE_MEC2_PIPE0_EOP,
	AMDGPU_CP_IRQ_COMPUTE_MEC2_PIPE1_EOP,
	AMDGPU_CP_IRQ_COMPUTE_MEC2_PIPE2_EOP,
	AMDGPU_CP_IRQ_COMPUTE_MEC2_PIPE3_EOP,

	AMDGPU_CP_IRQ_LAST
पूर्ण;

क्रमागत amdgpu_thermal_irq अणु
	AMDGPU_THERMAL_IRQ_LOW_TO_HIGH = 0,
	AMDGPU_THERMAL_IRQ_HIGH_TO_LOW,

	AMDGPU_THERMAL_IRQ_LAST
पूर्ण;

क्रमागत amdgpu_kiq_irq अणु
	AMDGPU_CP_KIQ_IRQ_DRIVER0 = 0,
	AMDGPU_CP_KIQ_IRQ_LAST
पूर्ण;

#घोषणा MAX_KIQ_REG_WAIT       5000 /* in usecs, 5ms */
#घोषणा MAX_KIQ_REG_BAILOUT_INTERVAL   5 /* in msecs, 5ms */
#घोषणा MAX_KIQ_REG_TRY 1000

पूर्णांक amdgpu_device_ip_set_घड़ीgating_state(व्योम *dev,
					   क्रमागत amd_ip_block_type block_type,
					   क्रमागत amd_घड़ीgating_state state);
पूर्णांक amdgpu_device_ip_set_घातergating_state(व्योम *dev,
					   क्रमागत amd_ip_block_type block_type,
					   क्रमागत amd_घातergating_state state);
व्योम amdgpu_device_ip_get_घड़ीgating_state(काष्ठा amdgpu_device *adev,
					    u32 *flags);
पूर्णांक amdgpu_device_ip_रुको_क्रम_idle(काष्ठा amdgpu_device *adev,
				   क्रमागत amd_ip_block_type block_type);
bool amdgpu_device_ip_is_idle(काष्ठा amdgpu_device *adev,
			      क्रमागत amd_ip_block_type block_type);

#घोषणा AMDGPU_MAX_IP_NUM 16

काष्ठा amdgpu_ip_block_status अणु
	bool valid;
	bool sw;
	bool hw;
	bool late_initialized;
	bool hang;
पूर्ण;

काष्ठा amdgpu_ip_block_version अणु
	स्थिर क्रमागत amd_ip_block_type type;
	स्थिर u32 major;
	स्थिर u32 minor;
	स्थिर u32 rev;
	स्थिर काष्ठा amd_ip_funcs *funcs;
पूर्ण;

#घोषणा HW_REV(_Major, _Minor, _Rev) \
	((((uपूर्णांक32_t) (_Major)) << 16) | ((uपूर्णांक32_t) (_Minor) << 8) | ((uपूर्णांक32_t) (_Rev)))

काष्ठा amdgpu_ip_block अणु
	काष्ठा amdgpu_ip_block_status status;
	स्थिर काष्ठा amdgpu_ip_block_version *version;
पूर्ण;

पूर्णांक amdgpu_device_ip_block_version_cmp(काष्ठा amdgpu_device *adev,
				       क्रमागत amd_ip_block_type type,
				       u32 major, u32 minor);

काष्ठा amdgpu_ip_block *
amdgpu_device_ip_get_ip_block(काष्ठा amdgpu_device *adev,
			      क्रमागत amd_ip_block_type type);

पूर्णांक amdgpu_device_ip_block_add(काष्ठा amdgpu_device *adev,
			       स्थिर काष्ठा amdgpu_ip_block_version *ip_block_version);

/*
 * BIOS.
 */
bool amdgpu_get_bios(काष्ठा amdgpu_device *adev);
bool amdgpu_पढ़ो_bios(काष्ठा amdgpu_device *adev);

/*
 * Clocks
 */

#घोषणा AMDGPU_MAX_PPLL 3

काष्ठा amdgpu_घड़ी अणु
	काष्ठा amdgpu_pll ppll[AMDGPU_MAX_PPLL];
	काष्ठा amdgpu_pll spll;
	काष्ठा amdgpu_pll mpll;
	/* 10 Khz units */
	uपूर्णांक32_t शेष_mclk;
	uपूर्णांक32_t शेष_sclk;
	uपूर्णांक32_t शेष_dispclk;
	uपूर्णांक32_t current_dispclk;
	uपूर्णांक32_t dp_extclk;
	uपूर्णांक32_t max_pixel_घड़ी;
पूर्ण;

/* sub-allocation manager, it has to be रक्षित by another lock.
 * By conception this is an helper क्रम other part of the driver
 * like the indirect buffer or semaphore, which both have their
 * locking.
 *
 * Principe is simple, we keep a list of sub allocation in offset
 * order (first entry has offset == 0, last entry has the highest
 * offset).
 *
 * When allocating new object we first check अगर there is room at
 * the end total_size - (last_object_offset + last_object_size) >=
 * alloc_size. If so we allocate new object there.
 *
 * When there is not enough room at the end, we start रुकोing क्रम
 * each sub object until we reach object_offset+object_size >=
 * alloc_size, this object then become the sub object we वापस.
 *
 * Alignment can't be bigger than page size.
 *
 * Hole are not considered क्रम allocation to keep things simple.
 * Assumption is that there won't be hole (all object on same
 * alignment).
 */

#घोषणा AMDGPU_SA_NUM_FENCE_LISTS	32

काष्ठा amdgpu_sa_manager अणु
	रुको_queue_head_t	wq;
	काष्ठा amdgpu_bo	*bo;
	काष्ठा list_head	*hole;
	काष्ठा list_head	flist[AMDGPU_SA_NUM_FENCE_LISTS];
	काष्ठा list_head	olist;
	अचिन्हित		size;
	uपूर्णांक64_t		gpu_addr;
	व्योम			*cpu_ptr;
	uपूर्णांक32_t		करोमुख्य;
	uपूर्णांक32_t		align;
पूर्ण;

/* sub-allocation buffer */
काष्ठा amdgpu_sa_bo अणु
	काष्ठा list_head		olist;
	काष्ठा list_head		flist;
	काष्ठा amdgpu_sa_manager	*manager;
	अचिन्हित			soffset;
	अचिन्हित			eoffset;
	काष्ठा dma_fence	        *fence;
पूर्ण;

पूर्णांक amdgpu_fence_slab_init(व्योम);
व्योम amdgpu_fence_slab_fini(व्योम);

/*
 * IRQS.
 */

काष्ठा amdgpu_flip_work अणु
	काष्ठा delayed_work		flip_work;
	काष्ठा work_काष्ठा		unpin_work;
	काष्ठा amdgpu_device		*adev;
	पूर्णांक				crtc_id;
	u32				target_vblank;
	uपूर्णांक64_t			base;
	काष्ठा drm_pending_vblank_event *event;
	काष्ठा amdgpu_bo		*old_abo;
	काष्ठा dma_fence		*excl;
	अचिन्हित			shared_count;
	काष्ठा dma_fence		**shared;
	काष्ठा dma_fence_cb		cb;
	bool				async;
पूर्ण;


/*
 * CP & rings.
 */

काष्ठा amdgpu_ib अणु
	काष्ठा amdgpu_sa_bo		*sa_bo;
	uपूर्णांक32_t			length_dw;
	uपूर्णांक64_t			gpu_addr;
	uपूर्णांक32_t			*ptr;
	uपूर्णांक32_t			flags;
पूर्ण;

बाह्य स्थिर काष्ठा drm_sched_backend_ops amdgpu_sched_ops;

/*
 * file निजी काष्ठाure
 */

काष्ठा amdgpu_fpriv अणु
	काष्ठा amdgpu_vm	vm;
	काष्ठा amdgpu_bo_va	*prt_va;
	काष्ठा amdgpu_bo_va	*csa_va;
	काष्ठा mutex		bo_list_lock;
	काष्ठा idr		bo_list_handles;
	काष्ठा amdgpu_ctx_mgr	ctx_mgr;
पूर्ण;

पूर्णांक amdgpu_file_to_fpriv(काष्ठा file *filp, काष्ठा amdgpu_fpriv **fpriv);

पूर्णांक amdgpu_ib_get(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_vm *vm,
		  अचिन्हित size,
		  क्रमागत amdgpu_ib_pool_type pool,
		  काष्ठा amdgpu_ib *ib);
व्योम amdgpu_ib_मुक्त(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_ib *ib,
		    काष्ठा dma_fence *f);
पूर्णांक amdgpu_ib_schedule(काष्ठा amdgpu_ring *ring, अचिन्हित num_ibs,
		       काष्ठा amdgpu_ib *ibs, काष्ठा amdgpu_job *job,
		       काष्ठा dma_fence **f);
पूर्णांक amdgpu_ib_pool_init(काष्ठा amdgpu_device *adev);
व्योम amdgpu_ib_pool_fini(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_ib_ring_tests(काष्ठा amdgpu_device *adev);

/*
 * CS.
 */
काष्ठा amdgpu_cs_chunk अणु
	uपूर्णांक32_t		chunk_id;
	uपूर्णांक32_t		length_dw;
	व्योम			*kdata;
पूर्ण;

काष्ठा amdgpu_cs_post_dep अणु
	काष्ठा drm_syncobj *syncobj;
	काष्ठा dma_fence_chain *chain;
	u64 poपूर्णांक;
पूर्ण;

काष्ठा amdgpu_cs_parser अणु
	काष्ठा amdgpu_device	*adev;
	काष्ठा drm_file		*filp;
	काष्ठा amdgpu_ctx	*ctx;

	/* chunks */
	अचिन्हित		nchunks;
	काष्ठा amdgpu_cs_chunk	*chunks;

	/* scheduler job object */
	काष्ठा amdgpu_job	*job;
	काष्ठा drm_sched_entity	*entity;

	/* buffer objects */
	काष्ठा ww_acquire_ctx		ticket;
	काष्ठा amdgpu_bo_list		*bo_list;
	काष्ठा amdgpu_mn		*mn;
	काष्ठा amdgpu_bo_list_entry	vm_pd;
	काष्ठा list_head		validated;
	काष्ठा dma_fence		*fence;
	uपूर्णांक64_t			bytes_moved_threshold;
	uपूर्णांक64_t			bytes_moved_vis_threshold;
	uपूर्णांक64_t			bytes_moved;
	uपूर्णांक64_t			bytes_moved_vis;

	/* user fence */
	काष्ठा amdgpu_bo_list_entry	uf_entry;

	अचिन्हित			num_post_deps;
	काष्ठा amdgpu_cs_post_dep	*post_deps;
पूर्ण;

अटल अंतरभूत u32 amdgpu_get_ib_value(काष्ठा amdgpu_cs_parser *p,
				      uपूर्णांक32_t ib_idx, पूर्णांक idx)
अणु
	वापस p->job->ibs[ib_idx].ptr[idx];
पूर्ण

अटल अंतरभूत व्योम amdgpu_set_ib_value(काष्ठा amdgpu_cs_parser *p,
				       uपूर्णांक32_t ib_idx, पूर्णांक idx,
				       uपूर्णांक32_t value)
अणु
	p->job->ibs[ib_idx].ptr[idx] = value;
पूर्ण

/*
 * Writeback
 */
#घोषणा AMDGPU_MAX_WB 256	/* Reserve at most 256 WB slots क्रम amdgpu-owned rings. */

काष्ठा amdgpu_wb अणु
	काष्ठा amdgpu_bo	*wb_obj;
	अस्थिर uपूर्णांक32_t	*wb;
	uपूर्णांक64_t		gpu_addr;
	u32			num_wb;	/* Number of wb slots actually reserved क्रम amdgpu. */
	अचिन्हित दीर्घ		used[DIV_ROUND_UP(AMDGPU_MAX_WB, BITS_PER_LONG)];
पूर्ण;

पूर्णांक amdgpu_device_wb_get(काष्ठा amdgpu_device *adev, u32 *wb);
व्योम amdgpu_device_wb_मुक्त(काष्ठा amdgpu_device *adev, u32 wb);

/*
 * Benchmarking
 */
व्योम amdgpu_benchmark(काष्ठा amdgpu_device *adev, पूर्णांक test_number);


/*
 * Testing
 */
व्योम amdgpu_test_moves(काष्ठा amdgpu_device *adev);

/*
 * ASIC specअगरic रेजिस्टर table accessible by UMD
 */
काष्ठा amdgpu_allowed_रेजिस्टर_entry अणु
	uपूर्णांक32_t reg_offset;
	bool grbm_indexed;
पूर्ण;

क्रमागत amd_reset_method अणु
	AMD_RESET_METHOD_NONE = -1,
	AMD_RESET_METHOD_LEGACY = 0,
	AMD_RESET_METHOD_MODE0,
	AMD_RESET_METHOD_MODE1,
	AMD_RESET_METHOD_MODE2,
	AMD_RESET_METHOD_BACO,
	AMD_RESET_METHOD_PCI,
पूर्ण;

काष्ठा amdgpu_video_codec_info अणु
	u32 codec_type;
	u32 max_width;
	u32 max_height;
	u32 max_pixels_per_frame;
	u32 max_level;
पूर्ण;

काष्ठा amdgpu_video_codecs अणु
	स्थिर u32 codec_count;
	स्थिर काष्ठा amdgpu_video_codec_info *codec_array;
पूर्ण;

/*
 * ASIC specअगरic functions.
 */
काष्ठा amdgpu_asic_funcs अणु
	bool (*पढ़ो_disabled_bios)(काष्ठा amdgpu_device *adev);
	bool (*पढ़ो_bios_from_rom)(काष्ठा amdgpu_device *adev,
				   u8 *bios, u32 length_bytes);
	पूर्णांक (*पढ़ो_रेजिस्टर)(काष्ठा amdgpu_device *adev, u32 se_num,
			     u32 sh_num, u32 reg_offset, u32 *value);
	व्योम (*set_vga_state)(काष्ठा amdgpu_device *adev, bool state);
	पूर्णांक (*reset)(काष्ठा amdgpu_device *adev);
	क्रमागत amd_reset_method (*reset_method)(काष्ठा amdgpu_device *adev);
	/* get the reference घड़ी */
	u32 (*get_xclk)(काष्ठा amdgpu_device *adev);
	/* MM block घड़ीs */
	पूर्णांक (*set_uvd_घड़ीs)(काष्ठा amdgpu_device *adev, u32 vclk, u32 dclk);
	पूर्णांक (*set_vce_घड़ीs)(काष्ठा amdgpu_device *adev, u32 evclk, u32 ecclk);
	/* अटल घातer management */
	पूर्णांक (*get_pcie_lanes)(काष्ठा amdgpu_device *adev);
	व्योम (*set_pcie_lanes)(काष्ठा amdgpu_device *adev, पूर्णांक lanes);
	/* get config memsize रेजिस्टर */
	u32 (*get_config_memsize)(काष्ठा amdgpu_device *adev);
	/* flush hdp ग_लिखो queue */
	व्योम (*flush_hdp)(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_ring *ring);
	/* invalidate hdp पढ़ो cache */
	व्योम (*invalidate_hdp)(काष्ठा amdgpu_device *adev,
			       काष्ठा amdgpu_ring *ring);
	/* check अगर the asic needs a full reset of अगर soft reset will work */
	bool (*need_full_reset)(काष्ठा amdgpu_device *adev);
	/* initialize करोorbell layout क्रम specअगरic asic*/
	व्योम (*init_करोorbell_index)(काष्ठा amdgpu_device *adev);
	/* PCIe bandwidth usage */
	व्योम (*get_pcie_usage)(काष्ठा amdgpu_device *adev, uपूर्णांक64_t *count0,
			       uपूर्णांक64_t *count1);
	/* करो we need to reset the asic at init समय (e.g., kexec) */
	bool (*need_reset_on_init)(काष्ठा amdgpu_device *adev);
	/* PCIe replay counter */
	uपूर्णांक64_t (*get_pcie_replay_count)(काष्ठा amdgpu_device *adev);
	/* device supports BACO */
	bool (*supports_baco)(काष्ठा amdgpu_device *adev);
	/* pre asic_init quirks */
	व्योम (*pre_asic_init)(काष्ठा amdgpu_device *adev);
	/* enter/निकास umd stable pstate */
	पूर्णांक (*update_umd_stable_pstate)(काष्ठा amdgpu_device *adev, bool enter);
	/* query video codecs */
	पूर्णांक (*query_video_codecs)(काष्ठा amdgpu_device *adev, bool encode,
				  स्थिर काष्ठा amdgpu_video_codecs **codecs);
पूर्ण;

/*
 * IOCTL.
 */
पूर्णांक amdgpu_bo_list_ioctl(काष्ठा drm_device *dev, व्योम *data,
				काष्ठा drm_file *filp);

पूर्णांक amdgpu_cs_ioctl(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *filp);
पूर्णांक amdgpu_cs_fence_to_handle_ioctl(काष्ठा drm_device *dev, व्योम *data,
				    काष्ठा drm_file *filp);
पूर्णांक amdgpu_cs_रुको_ioctl(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *filp);
पूर्णांक amdgpu_cs_रुको_fences_ioctl(काष्ठा drm_device *dev, व्योम *data,
				काष्ठा drm_file *filp);

/* VRAM scratch page क्रम HDP bug, शेष vram page */
काष्ठा amdgpu_vram_scratch अणु
	काष्ठा amdgpu_bo		*robj;
	अस्थिर uपूर्णांक32_t		*ptr;
	u64				gpu_addr;
पूर्ण;

/*
 * ACPI
 */
काष्ठा amdgpu_atcs_functions अणु
	bool get_ext_state;
	bool pcie_perf_req;
	bool pcie_dev_rdy;
	bool pcie_bus_width;
पूर्ण;

काष्ठा amdgpu_atcs अणु
	काष्ठा amdgpu_atcs_functions functions;
पूर्ण;

/*
 * CGS
 */
काष्ठा cgs_device *amdgpu_cgs_create_device(काष्ठा amdgpu_device *adev);
व्योम amdgpu_cgs_destroy_device(काष्ठा cgs_device *cgs_device);

/*
 * Core काष्ठाure, functions and helpers.
 */
प्रकार uपूर्णांक32_t (*amdgpu_rreg_t)(काष्ठा amdgpu_device*, uपूर्णांक32_t);
प्रकार व्योम (*amdgpu_wreg_t)(काष्ठा amdgpu_device*, uपूर्णांक32_t, uपूर्णांक32_t);

प्रकार uपूर्णांक64_t (*amdgpu_rreg64_t)(काष्ठा amdgpu_device*, uपूर्णांक32_t);
प्रकार व्योम (*amdgpu_wreg64_t)(काष्ठा amdgpu_device*, uपूर्णांक32_t, uपूर्णांक64_t);

प्रकार uपूर्णांक32_t (*amdgpu_block_rreg_t)(काष्ठा amdgpu_device*, uपूर्णांक32_t, uपूर्णांक32_t);
प्रकार व्योम (*amdgpu_block_wreg_t)(काष्ठा amdgpu_device*, uपूर्णांक32_t, uपूर्णांक32_t, uपूर्णांक32_t);

काष्ठा amdgpu_mmio_remap अणु
	u32 reg_offset;
	resource_माप_प्रकार bus_addr;
पूर्ण;

/* Define the HW IP blocks will be used in driver , add more अगर necessary */
क्रमागत amd_hw_ip_block_type अणु
	GC_HWIP = 1,
	HDP_HWIP,
	SDMA0_HWIP,
	SDMA1_HWIP,
	SDMA2_HWIP,
	SDMA3_HWIP,
	SDMA4_HWIP,
	SDMA5_HWIP,
	SDMA6_HWIP,
	SDMA7_HWIP,
	MMHUB_HWIP,
	ATHUB_HWIP,
	NBIO_HWIP,
	MP0_HWIP,
	MP1_HWIP,
	UVD_HWIP,
	VCN_HWIP = UVD_HWIP,
	JPEG_HWIP = VCN_HWIP,
	VCE_HWIP,
	DF_HWIP,
	DCE_HWIP,
	OSSSYS_HWIP,
	SMUIO_HWIP,
	PWR_HWIP,
	NBIF_HWIP,
	THM_HWIP,
	CLK_HWIP,
	UMC_HWIP,
	RSMU_HWIP,
	MAX_HWIP
पूर्ण;

#घोषणा HWIP_MAX_INSTANCE	8

काष्ठा amd_घातerplay अणु
	व्योम *pp_handle;
	स्थिर काष्ठा amd_pm_funcs *pp_funcs;
पूर्ण;

/* polaris10 kickers */
#घोषणा ASICID_IS_P20(did, rid)		(((did == 0x67DF) && \
					 ((rid == 0xE3) || \
					  (rid == 0xE4) || \
					  (rid == 0xE5) || \
					  (rid == 0xE7) || \
					  (rid == 0xEF))) || \
					 ((did == 0x6FDF) && \
					 ((rid == 0xE7) || \
					  (rid == 0xEF) || \
					  (rid == 0xFF))))

#घोषणा ASICID_IS_P30(did, rid)		((did == 0x67DF) && \
					((rid == 0xE1) || \
					 (rid == 0xF7)))

/* polaris11 kickers */
#घोषणा ASICID_IS_P21(did, rid)		(((did == 0x67EF) && \
					 ((rid == 0xE0) || \
					  (rid == 0xE5))) || \
					 ((did == 0x67FF) && \
					 ((rid == 0xCF) || \
					  (rid == 0xEF) || \
					  (rid == 0xFF))))

#घोषणा ASICID_IS_P31(did, rid)		((did == 0x67EF) && \
					((rid == 0xE2)))

/* polaris12 kickers */
#घोषणा ASICID_IS_P23(did, rid)		(((did == 0x6987) && \
					 ((rid == 0xC0) || \
					  (rid == 0xC1) || \
					  (rid == 0xC3) || \
					  (rid == 0xC7))) || \
					 ((did == 0x6981) && \
					 ((rid == 0x00) || \
					  (rid == 0x01) || \
					  (rid == 0x10))))

#घोषणा AMDGPU_RESET_MAGIC_NUM 64
#घोषणा AMDGPU_MAX_DF_PERFMONS 4
काष्ठा amdgpu_device अणु
	काष्ठा device			*dev;
	काष्ठा pci_dev			*pdev;
	काष्ठा drm_device		ddev;

#अगर_घोषित CONFIG_DRM_AMD_ACP
	काष्ठा amdgpu_acp		acp;
#पूर्ण_अगर
	काष्ठा amdgpu_hive_info *hive;
	/* ASIC */
	क्रमागत amd_asic_type		asic_type;
	uपूर्णांक32_t			family;
	uपूर्णांक32_t			rev_id;
	uपूर्णांक32_t			बाह्यal_rev_id;
	अचिन्हित दीर्घ			flags;
	अचिन्हित दीर्घ			apu_flags;
	पूर्णांक				usec_समयout;
	स्थिर काष्ठा amdgpu_asic_funcs	*asic_funcs;
	bool				shutकरोwn;
	bool				need_swiotlb;
	bool				accel_working;
	काष्ठा notअगरier_block		acpi_nb;
	काष्ठा amdgpu_i2c_chan		*i2c_bus[AMDGPU_MAX_I2C_BUS];
	काष्ठा debugfs_blob_wrapper     debugfs_vbios_blob;
	काष्ठा amdgpu_atअगर		*atअगर;
	काष्ठा amdgpu_atcs		atcs;
	काष्ठा mutex			srbm_mutex;
	/* GRBM index mutex. Protects concurrent access to GRBM index */
	काष्ठा mutex                    grbm_idx_mutex;
	काष्ठा dev_pm_करोमुख्य		vga_pm_करोमुख्य;
	bool				have_disp_घातer_ref;
	bool                            have_atomics_support;

	/* BIOS */
	bool				is_atom_fw;
	uपूर्णांक8_t				*bios;
	uपूर्णांक32_t			bios_size;
	uपूर्णांक32_t			bios_scratch_reg_offset;
	uपूर्णांक32_t			bios_scratch[AMDGPU_BIOS_NUM_SCRATCH];

	/* Register/करोorbell mmio */
	resource_माप_प्रकार			rmmio_base;
	resource_माप_प्रकार			rmmio_size;
	व्योम __iomem			*rmmio;
	/* protects concurrent MM_INDEX/DATA based रेजिस्टर access */
	spinlock_t mmio_idx_lock;
	काष्ठा amdgpu_mmio_remap        rmmio_remap;
	/* protects concurrent SMC based रेजिस्टर access */
	spinlock_t smc_idx_lock;
	amdgpu_rreg_t			smc_rreg;
	amdgpu_wreg_t			smc_wreg;
	/* protects concurrent PCIE रेजिस्टर access */
	spinlock_t pcie_idx_lock;
	amdgpu_rreg_t			pcie_rreg;
	amdgpu_wreg_t			pcie_wreg;
	amdgpu_rreg_t			pciep_rreg;
	amdgpu_wreg_t			pciep_wreg;
	amdgpu_rreg64_t			pcie_rreg64;
	amdgpu_wreg64_t			pcie_wreg64;
	/* protects concurrent UVD रेजिस्टर access */
	spinlock_t uvd_ctx_idx_lock;
	amdgpu_rreg_t			uvd_ctx_rreg;
	amdgpu_wreg_t			uvd_ctx_wreg;
	/* protects concurrent DIDT रेजिस्टर access */
	spinlock_t didt_idx_lock;
	amdgpu_rreg_t			didt_rreg;
	amdgpu_wreg_t			didt_wreg;
	/* protects concurrent gc_cac रेजिस्टर access */
	spinlock_t gc_cac_idx_lock;
	amdgpu_rreg_t			gc_cac_rreg;
	amdgpu_wreg_t			gc_cac_wreg;
	/* protects concurrent se_cac रेजिस्टर access */
	spinlock_t se_cac_idx_lock;
	amdgpu_rreg_t			se_cac_rreg;
	amdgpu_wreg_t			se_cac_wreg;
	/* protects concurrent ENDPOINT (audio) रेजिस्टर access */
	spinlock_t audio_endpt_idx_lock;
	amdgpu_block_rreg_t		audio_endpt_rreg;
	amdgpu_block_wreg_t		audio_endpt_wreg;
	काष्ठा amdgpu_करोorbell		करोorbell;

	/* घड़ी/pll info */
	काष्ठा amdgpu_घड़ी            घड़ी;

	/* MC */
	काष्ठा amdgpu_gmc		gmc;
	काष्ठा amdgpu_gart		gart;
	dma_addr_t			dummy_page_addr;
	काष्ठा amdgpu_vm_manager	vm_manager;
	काष्ठा amdgpu_vmhub             vmhub[AMDGPU_MAX_VMHUBS];
	अचिन्हित			num_vmhubs;

	/* memory management */
	काष्ठा amdgpu_mman		mman;
	काष्ठा amdgpu_vram_scratch	vram_scratch;
	काष्ठा amdgpu_wb		wb;
	atomic64_t			num_bytes_moved;
	atomic64_t			num_evictions;
	atomic64_t			num_vram_cpu_page_faults;
	atomic_t			gpu_reset_counter;
	atomic_t			vram_lost_counter;

	/* data क्रम buffer migration throttling */
	काष्ठा अणु
		spinlock_t		lock;
		s64			last_update_us;
		s64			accum_us; /* accumulated microseconds */
		s64			accum_us_vis; /* क्रम visible VRAM */
		u32			log2_max_MBps;
	पूर्ण mm_stats;

	/* display */
	bool				enable_भव_display;
	काष्ठा amdgpu_mode_info		mode_info;
	/* For pre-DCE11. DCE11 and later are in "struct amdgpu_device->dm" */
	काष्ठा work_काष्ठा		hotplug_work;
	काष्ठा amdgpu_irq_src		crtc_irq;
	काष्ठा amdgpu_irq_src		vline0_irq;
	काष्ठा amdgpu_irq_src		vupdate_irq;
	काष्ठा amdgpu_irq_src		pageflip_irq;
	काष्ठा amdgpu_irq_src		hpd_irq;
	काष्ठा amdgpu_irq_src		dmub_trace_irq;
	काष्ठा amdgpu_irq_src		dmub_outbox_irq;

	/* rings */
	u64				fence_context;
	अचिन्हित			num_rings;
	काष्ठा amdgpu_ring		*rings[AMDGPU_MAX_RINGS];
	bool				ib_pool_पढ़ोy;
	काष्ठा amdgpu_sa_manager	ib_pools[AMDGPU_IB_POOL_MAX];
	काष्ठा amdgpu_sched		gpu_sched[AMDGPU_HW_IP_NUM][AMDGPU_RING_PRIO_MAX];

	/* पूर्णांकerrupts */
	काष्ठा amdgpu_irq		irq;

	/* घातerplay */
	काष्ठा amd_घातerplay		घातerplay;
	bool				pp_क्रमce_state_enabled;

	/* smu */
	काष्ठा smu_context		smu;

	/* dpm */
	काष्ठा amdgpu_pm		pm;
	u32				cg_flags;
	u32				pg_flags;

	/* nbio */
	काष्ठा amdgpu_nbio		nbio;

	/* hdp */
	काष्ठा amdgpu_hdp		hdp;

	/* smuio */
	काष्ठा amdgpu_smuio		smuio;

	/* mmhub */
	काष्ठा amdgpu_mmhub		mmhub;

	/* gfxhub */
	काष्ठा amdgpu_gfxhub		gfxhub;

	/* gfx */
	काष्ठा amdgpu_gfx		gfx;

	/* sdma */
	काष्ठा amdgpu_sdma		sdma;

	/* uvd */
	काष्ठा amdgpu_uvd		uvd;

	/* vce */
	काष्ठा amdgpu_vce		vce;

	/* vcn */
	काष्ठा amdgpu_vcn		vcn;

	/* jpeg */
	काष्ठा amdgpu_jpeg		jpeg;

	/* firmwares */
	काष्ठा amdgpu_firmware		firmware;

	/* PSP */
	काष्ठा psp_context		psp;

	/* GDS */
	काष्ठा amdgpu_gds		gds;

	/* KFD */
	काष्ठा amdgpu_kfd_dev		kfd;

	/* UMC */
	काष्ठा amdgpu_umc		umc;

	/* display related functionality */
	काष्ठा amdgpu_display_manager dm;

	/* mes */
	bool                            enable_mes;
	काष्ठा amdgpu_mes               mes;

	/* df */
	काष्ठा amdgpu_df                df;

	काष्ठा amdgpu_ip_block          ip_blocks[AMDGPU_MAX_IP_NUM];
	uपूर्णांक32_t		        harvest_ip_mask;
	पूर्णांक				num_ip_blocks;
	काष्ठा mutex	mn_lock;
	DECLARE_HASHTABLE(mn_hash, 7);

	/* tracking pinned memory */
	atomic64_t vram_pin_size;
	atomic64_t visible_pin_size;
	atomic64_t gart_pin_size;

	/* soc15 रेजिस्टर offset based on ip, instance and  segment */
	uपूर्णांक32_t		*reg_offset[MAX_HWIP][HWIP_MAX_INSTANCE];

	/* delayed work_func क्रम deferring घड़ीgating during resume */
	काष्ठा delayed_work     delayed_init_work;

	काष्ठा amdgpu_virt	virt;

	/* link all shaकरोw bo */
	काष्ठा list_head                shaकरोw_list;
	काष्ठा mutex                    shaकरोw_list_lock;

	/* record hw reset is perक्रमmed */
	bool has_hw_reset;
	u8				reset_magic[AMDGPU_RESET_MAGIC_NUM];

	/* s3/s4 mask */
	bool                            in_suspend;
	bool				in_s3;
	bool				in_s4;
	bool				in_s0ix;

	atomic_t 			in_gpu_reset;
	क्रमागत pp_mp1_state               mp1_state;
	काष्ठा rw_semaphore reset_sem;
	काष्ठा amdgpu_करोorbell_index करोorbell_index;

	काष्ठा mutex			notअगरier_lock;

	पूर्णांक asic_reset_res;
	काष्ठा work_काष्ठा		xgmi_reset_work;
	काष्ठा list_head		reset_list;

	दीर्घ				gfx_समयout;
	दीर्घ				sdma_समयout;
	दीर्घ				video_समयout;
	दीर्घ				compute_समयout;

	uपूर्णांक64_t			unique_id;
	uपूर्णांक64_t	df_perfmon_config_assign_mask[AMDGPU_MAX_DF_PERFMONS];

	/* enable runसमय pm on the device */
	bool                            runpm;
	bool                            in_runpm;
	bool                            has_pr3;

	bool                            pm_sysfs_en;
	bool                            ucode_sysfs_en;

	/* Chip product inक्रमmation */
	अक्षर				product_number[16];
	अक्षर				product_name[32];
	अक्षर				serial[20];

	काष्ठा amdgpu_स्वतःdump		स्वतःdump;

	atomic_t			throttling_logging_enabled;
	काष्ठा ratelimit_state		throttling_logging_rs;
	uपूर्णांक32_t			ras_features;

	bool                            in_pci_err_recovery;
	काष्ठा pci_saved_state          *pci_state;

	काष्ठा amdgpu_reset_control     *reset_cntl;
पूर्ण;

अटल अंतरभूत काष्ठा amdgpu_device *drm_to_adev(काष्ठा drm_device *ddev)
अणु
	वापस container_of(ddev, काष्ठा amdgpu_device, ddev);
पूर्ण

अटल अंतरभूत काष्ठा drm_device *adev_to_drm(काष्ठा amdgpu_device *adev)
अणु
	वापस &adev->ddev;
पूर्ण

अटल अंतरभूत काष्ठा amdgpu_device *amdgpu_tपंचांग_adev(काष्ठा tपंचांग_device *bdev)
अणु
	वापस container_of(bdev, काष्ठा amdgpu_device, mman.bdev);
पूर्ण

पूर्णांक amdgpu_device_init(काष्ठा amdgpu_device *adev,
		       uपूर्णांक32_t flags);
व्योम amdgpu_device_fini(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_gpu_रुको_क्रम_idle(काष्ठा amdgpu_device *adev);

व्योम amdgpu_device_vram_access(काष्ठा amdgpu_device *adev, loff_t pos,
			       uपूर्णांक32_t *buf, माप_प्रकार size, bool ग_लिखो);
uपूर्णांक32_t amdgpu_device_rreg(काष्ठा amdgpu_device *adev,
			    uपूर्णांक32_t reg, uपूर्णांक32_t acc_flags);
व्योम amdgpu_device_wreg(काष्ठा amdgpu_device *adev,
			uपूर्णांक32_t reg, uपूर्णांक32_t v,
			uपूर्णांक32_t acc_flags);
व्योम amdgpu_mm_wreg_mmio_rlc(काष्ठा amdgpu_device *adev,
			     uपूर्णांक32_t reg, uपूर्णांक32_t v);
व्योम amdgpu_mm_wreg8(काष्ठा amdgpu_device *adev, uपूर्णांक32_t offset, uपूर्णांक8_t value);
uपूर्णांक8_t amdgpu_mm_rreg8(काष्ठा amdgpu_device *adev, uपूर्णांक32_t offset);

u32 amdgpu_device_indirect_rreg(काष्ठा amdgpu_device *adev,
				u32 pcie_index, u32 pcie_data,
				u32 reg_addr);
u64 amdgpu_device_indirect_rreg64(काष्ठा amdgpu_device *adev,
				  u32 pcie_index, u32 pcie_data,
				  u32 reg_addr);
व्योम amdgpu_device_indirect_wreg(काष्ठा amdgpu_device *adev,
				 u32 pcie_index, u32 pcie_data,
				 u32 reg_addr, u32 reg_data);
व्योम amdgpu_device_indirect_wreg64(काष्ठा amdgpu_device *adev,
				   u32 pcie_index, u32 pcie_data,
				   u32 reg_addr, u64 reg_data);

bool amdgpu_device_asic_has_dc_support(क्रमागत amd_asic_type asic_type);
bool amdgpu_device_has_dc_support(काष्ठा amdgpu_device *adev);

पूर्णांक amdgpu_device_pre_asic_reset(काष्ठा amdgpu_device *adev,
				 काष्ठा amdgpu_reset_context *reset_context);

पूर्णांक amdgpu_करो_asic_reset(काष्ठा list_head *device_list_handle,
			 काष्ठा amdgpu_reset_context *reset_context);

पूर्णांक emu_soc_asic_init(काष्ठा amdgpu_device *adev);

/*
 * Registers पढ़ो & ग_लिखो functions.
 */
#घोषणा AMDGPU_REGS_NO_KIQ    (1<<1)

#घोषणा RREG32_NO_KIQ(reg) amdgpu_device_rreg(adev, (reg), AMDGPU_REGS_NO_KIQ)
#घोषणा WREG32_NO_KIQ(reg, v) amdgpu_device_wreg(adev, (reg), (v), AMDGPU_REGS_NO_KIQ)

#घोषणा RREG32_KIQ(reg) amdgpu_kiq_rreg(adev, (reg))
#घोषणा WREG32_KIQ(reg, v) amdgpu_kiq_wreg(adev, (reg), (v))

#घोषणा RREG8(reg) amdgpu_mm_rreg8(adev, (reg))
#घोषणा WREG8(reg, v) amdgpu_mm_wreg8(adev, (reg), (v))

#घोषणा RREG32(reg) amdgpu_device_rreg(adev, (reg), 0)
#घोषणा DREG32(reg) prपूर्णांकk(KERN_INFO "REGISTER: " #reg " : 0x%08X\n", amdgpu_device_rreg(adev, (reg), 0))
#घोषणा WREG32(reg, v) amdgpu_device_wreg(adev, (reg), (v), 0)
#घोषणा REG_SET(FIELD, v) (((v) << FIELD##_SHIFT) & FIELD##_MASK)
#घोषणा REG_GET(FIELD, v) (((v) << FIELD##_SHIFT) & FIELD##_MASK)
#घोषणा RREG32_PCIE(reg) adev->pcie_rreg(adev, (reg))
#घोषणा WREG32_PCIE(reg, v) adev->pcie_wreg(adev, (reg), (v))
#घोषणा RREG32_PCIE_PORT(reg) adev->pciep_rreg(adev, (reg))
#घोषणा WREG32_PCIE_PORT(reg, v) adev->pciep_wreg(adev, (reg), (v))
#घोषणा RREG64_PCIE(reg) adev->pcie_rreg64(adev, (reg))
#घोषणा WREG64_PCIE(reg, v) adev->pcie_wreg64(adev, (reg), (v))
#घोषणा RREG32_SMC(reg) adev->smc_rreg(adev, (reg))
#घोषणा WREG32_SMC(reg, v) adev->smc_wreg(adev, (reg), (v))
#घोषणा RREG32_UVD_CTX(reg) adev->uvd_ctx_rreg(adev, (reg))
#घोषणा WREG32_UVD_CTX(reg, v) adev->uvd_ctx_wreg(adev, (reg), (v))
#घोषणा RREG32_DIDT(reg) adev->didt_rreg(adev, (reg))
#घोषणा WREG32_DIDT(reg, v) adev->didt_wreg(adev, (reg), (v))
#घोषणा RREG32_GC_CAC(reg) adev->gc_cac_rreg(adev, (reg))
#घोषणा WREG32_GC_CAC(reg, v) adev->gc_cac_wreg(adev, (reg), (v))
#घोषणा RREG32_SE_CAC(reg) adev->se_cac_rreg(adev, (reg))
#घोषणा WREG32_SE_CAC(reg, v) adev->se_cac_wreg(adev, (reg), (v))
#घोषणा RREG32_AUDIO_ENDPT(block, reg) adev->audio_endpt_rreg(adev, (block), (reg))
#घोषणा WREG32_AUDIO_ENDPT(block, reg, v) adev->audio_endpt_wreg(adev, (block), (reg), (v))
#घोषणा WREG32_P(reg, val, mask)				\
	करो अणु							\
		uपूर्णांक32_t पंचांगp_ = RREG32(reg);			\
		पंचांगp_ &= (mask);					\
		पंचांगp_ |= ((val) & ~(mask));			\
		WREG32(reg, पंचांगp_);				\
	पूर्ण जबतक (0)
#घोषणा WREG32_AND(reg, and) WREG32_P(reg, 0, and)
#घोषणा WREG32_OR(reg, or) WREG32_P(reg, or, ~(or))
#घोषणा WREG32_PLL_P(reg, val, mask)				\
	करो अणु							\
		uपूर्णांक32_t पंचांगp_ = RREG32_PLL(reg);		\
		पंचांगp_ &= (mask);					\
		पंचांगp_ |= ((val) & ~(mask));			\
		WREG32_PLL(reg, पंचांगp_);				\
	पूर्ण जबतक (0)

#घोषणा WREG32_SMC_P(_Reg, _Val, _Mask)                         \
	करो अणु                                                    \
		u32 पंचांगp = RREG32_SMC(_Reg);                     \
		पंचांगp &= (_Mask);                                 \
		पंचांगp |= ((_Val) & ~(_Mask));                     \
		WREG32_SMC(_Reg, पंचांगp);                          \
	पूर्ण जबतक (0)

#घोषणा DREG32_SYS(sqf, adev, reg) seq_म_लिखो((sqf), #reg " : 0x%08X\n", amdgpu_device_rreg((adev), (reg), false))

#घोषणा REG_FIELD_SHIFT(reg, field) reg##__##field##__SHIFT
#घोषणा REG_FIELD_MASK(reg, field) reg##__##field##_MASK

#घोषणा REG_SET_FIELD(orig_val, reg, field, field_val)			\
	(((orig_val) & ~REG_FIELD_MASK(reg, field)) |			\
	 (REG_FIELD_MASK(reg, field) & ((field_val) << REG_FIELD_SHIFT(reg, field))))

#घोषणा REG_GET_FIELD(value, reg, field)				\
	(((value) & REG_FIELD_MASK(reg, field)) >> REG_FIELD_SHIFT(reg, field))

#घोषणा WREG32_FIELD(reg, field, val)	\
	WREG32(mm##reg, (RREG32(mm##reg) & ~REG_FIELD_MASK(reg, field)) | (val) << REG_FIELD_SHIFT(reg, field))

#घोषणा WREG32_FIELD_OFFSET(reg, offset, field, val)	\
	WREG32(mm##reg + offset, (RREG32(mm##reg + offset) & ~REG_FIELD_MASK(reg, field)) | (val) << REG_FIELD_SHIFT(reg, field))

/*
 * BIOS helpers.
 */
#घोषणा RBIOS8(i) (adev->bios[i])
#घोषणा RBIOS16(i) (RBIOS8(i) | (RBIOS8((i)+1) << 8))
#घोषणा RBIOS32(i) ((RBIOS16(i)) | (RBIOS16((i)+2) << 16))

/*
 * ASICs macro.
 */
#घोषणा amdgpu_asic_set_vga_state(adev, state) (adev)->asic_funcs->set_vga_state((adev), (state))
#घोषणा amdgpu_asic_reset(adev) (adev)->asic_funcs->reset((adev))
#घोषणा amdgpu_asic_reset_method(adev) (adev)->asic_funcs->reset_method((adev))
#घोषणा amdgpu_asic_get_xclk(adev) (adev)->asic_funcs->get_xclk((adev))
#घोषणा amdgpu_asic_set_uvd_घड़ीs(adev, v, d) (adev)->asic_funcs->set_uvd_घड़ीs((adev), (v), (d))
#घोषणा amdgpu_asic_set_vce_घड़ीs(adev, ev, ec) (adev)->asic_funcs->set_vce_घड़ीs((adev), (ev), (ec))
#घोषणा amdgpu_get_pcie_lanes(adev) (adev)->asic_funcs->get_pcie_lanes((adev))
#घोषणा amdgpu_set_pcie_lanes(adev, l) (adev)->asic_funcs->set_pcie_lanes((adev), (l))
#घोषणा amdgpu_asic_get_gpu_घड़ी_counter(adev) (adev)->asic_funcs->get_gpu_घड़ी_counter((adev))
#घोषणा amdgpu_asic_पढ़ो_disabled_bios(adev) (adev)->asic_funcs->पढ़ो_disabled_bios((adev))
#घोषणा amdgpu_asic_पढ़ो_bios_from_rom(adev, b, l) (adev)->asic_funcs->पढ़ो_bios_from_rom((adev), (b), (l))
#घोषणा amdgpu_asic_पढ़ो_रेजिस्टर(adev, se, sh, offset, v)((adev)->asic_funcs->पढ़ो_रेजिस्टर((adev), (se), (sh), (offset), (v)))
#घोषणा amdgpu_asic_get_config_memsize(adev) (adev)->asic_funcs->get_config_memsize((adev))
#घोषणा amdgpu_asic_flush_hdp(adev, r) \
	((adev)->asic_funcs->flush_hdp ? (adev)->asic_funcs->flush_hdp((adev), (r)) : (adev)->hdp.funcs->flush_hdp((adev), (r)))
#घोषणा amdgpu_asic_invalidate_hdp(adev, r) \
	((adev)->asic_funcs->invalidate_hdp ? (adev)->asic_funcs->invalidate_hdp((adev), (r)) : (adev)->hdp.funcs->invalidate_hdp((adev), (r)))
#घोषणा amdgpu_asic_need_full_reset(adev) (adev)->asic_funcs->need_full_reset((adev))
#घोषणा amdgpu_asic_init_करोorbell_index(adev) (adev)->asic_funcs->init_करोorbell_index((adev))
#घोषणा amdgpu_asic_get_pcie_usage(adev, cnt0, cnt1) ((adev)->asic_funcs->get_pcie_usage((adev), (cnt0), (cnt1)))
#घोषणा amdgpu_asic_need_reset_on_init(adev) (adev)->asic_funcs->need_reset_on_init((adev))
#घोषणा amdgpu_asic_get_pcie_replay_count(adev) ((adev)->asic_funcs->get_pcie_replay_count((adev)))
#घोषणा amdgpu_asic_supports_baco(adev) (adev)->asic_funcs->supports_baco((adev))
#घोषणा amdgpu_asic_pre_asic_init(adev) (adev)->asic_funcs->pre_asic_init((adev))
#घोषणा amdgpu_asic_update_umd_stable_pstate(adev, enter) \
	((adev)->asic_funcs->update_umd_stable_pstate ? (adev)->asic_funcs->update_umd_stable_pstate((adev), (enter)) : 0)
#घोषणा amdgpu_asic_query_video_codecs(adev, e, c) (adev)->asic_funcs->query_video_codecs((adev), (e), (c))

#घोषणा amdgpu_inc_vram_lost(adev) atomic_inc(&((adev)->vram_lost_counter));

/* Common functions */
bool amdgpu_device_has_job_running(काष्ठा amdgpu_device *adev);
bool amdgpu_device_should_recover_gpu(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_device_gpu_recover(काष्ठा amdgpu_device *adev,
			      काष्ठा amdgpu_job* job);
व्योम amdgpu_device_pci_config_reset(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_device_pci_reset(काष्ठा amdgpu_device *adev);
bool amdgpu_device_need_post(काष्ठा amdgpu_device *adev);

व्योम amdgpu_cs_report_moved_bytes(काष्ठा amdgpu_device *adev, u64 num_bytes,
				  u64 num_vis_bytes);
पूर्णांक amdgpu_device_resize_fb_bar(काष्ठा amdgpu_device *adev);
व्योम amdgpu_device_program_रेजिस्टर_sequence(काष्ठा amdgpu_device *adev,
					     स्थिर u32 *रेजिस्टरs,
					     स्थिर u32 array_size);

पूर्णांक amdgpu_device_mode1_reset(काष्ठा amdgpu_device *adev);
bool amdgpu_device_supports_atpx(काष्ठा drm_device *dev);
bool amdgpu_device_supports_px(काष्ठा drm_device *dev);
bool amdgpu_device_supports_boco(काष्ठा drm_device *dev);
bool amdgpu_device_supports_baco(काष्ठा drm_device *dev);
bool amdgpu_device_is_peer_accessible(काष्ठा amdgpu_device *adev,
				      काष्ठा amdgpu_device *peer_adev);
पूर्णांक amdgpu_device_baco_enter(काष्ठा drm_device *dev);
पूर्णांक amdgpu_device_baco_निकास(काष्ठा drm_device *dev);

/* atpx handler */
#अगर defined(CONFIG_VGA_SWITCHEROO)
व्योम amdgpu_रेजिस्टर_atpx_handler(व्योम);
व्योम amdgpu_unरेजिस्टर_atpx_handler(व्योम);
bool amdgpu_has_atpx_dgpu_घातer_cntl(व्योम);
bool amdgpu_is_atpx_hybrid(व्योम);
bool amdgpu_atpx_dgpu_req_घातer_क्रम_displays(व्योम);
bool amdgpu_has_atpx(व्योम);
#अन्यथा
अटल अंतरभूत व्योम amdgpu_रेजिस्टर_atpx_handler(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम amdgpu_unरेजिस्टर_atpx_handler(व्योम) अणुपूर्ण
अटल अंतरभूत bool amdgpu_has_atpx_dgpu_घातer_cntl(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत bool amdgpu_is_atpx_hybrid(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत bool amdgpu_atpx_dgpu_req_घातer_क्रम_displays(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत bool amdgpu_has_atpx(व्योम) अणु वापस false; पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_VGA_SWITCHEROO) && defined(CONFIG_ACPI)
व्योम *amdgpu_atpx_get_dhandle(व्योम);
#अन्यथा
अटल अंतरभूत व्योम *amdgpu_atpx_get_dhandle(व्योम) अणु वापस शून्य; पूर्ण
#पूर्ण_अगर

/*
 * KMS
 */
बाह्य स्थिर काष्ठा drm_ioctl_desc amdgpu_ioctls_kms[];
बाह्य स्थिर पूर्णांक amdgpu_max_kms_ioctl;

पूर्णांक amdgpu_driver_load_kms(काष्ठा amdgpu_device *adev, अचिन्हित दीर्घ flags);
व्योम amdgpu_driver_unload_kms(काष्ठा drm_device *dev);
व्योम amdgpu_driver_lastबंद_kms(काष्ठा drm_device *dev);
पूर्णांक amdgpu_driver_खोलो_kms(काष्ठा drm_device *dev, काष्ठा drm_file *file_priv);
व्योम amdgpu_driver_postबंद_kms(काष्ठा drm_device *dev,
				 काष्ठा drm_file *file_priv);
पूर्णांक amdgpu_device_ip_suspend(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_device_suspend(काष्ठा drm_device *dev, bool fbcon);
पूर्णांक amdgpu_device_resume(काष्ठा drm_device *dev, bool fbcon);
u32 amdgpu_get_vblank_counter_kms(काष्ठा drm_crtc *crtc);
पूर्णांक amdgpu_enable_vblank_kms(काष्ठा drm_crtc *crtc);
व्योम amdgpu_disable_vblank_kms(काष्ठा drm_crtc *crtc);
दीर्घ amdgpu_kms_compat_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
			     अचिन्हित दीर्घ arg);
पूर्णांक amdgpu_info_ioctl(काष्ठा drm_device *dev, व्योम *data,
		      काष्ठा drm_file *filp);

/*
 * functions used by amdgpu_encoder.c
 */
काष्ठा amdgpu_afmt_acr अणु
	u32 घड़ी;

	पूर्णांक n_32khz;
	पूर्णांक cts_32khz;

	पूर्णांक n_44_1khz;
	पूर्णांक cts_44_1khz;

	पूर्णांक n_48khz;
	पूर्णांक cts_48khz;

पूर्ण;

काष्ठा amdgpu_afmt_acr amdgpu_afmt_acr(uपूर्णांक32_t घड़ी);

/* amdgpu_acpi.c */
#अगर defined(CONFIG_ACPI)
पूर्णांक amdgpu_acpi_init(काष्ठा amdgpu_device *adev);
व्योम amdgpu_acpi_fini(काष्ठा amdgpu_device *adev);
bool amdgpu_acpi_is_pcie_perक्रमmance_request_supported(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_acpi_pcie_perक्रमmance_request(काष्ठा amdgpu_device *adev,
						u8 perf_req, bool advertise);
पूर्णांक amdgpu_acpi_pcie_notअगरy_device_पढ़ोy(काष्ठा amdgpu_device *adev);

व्योम amdgpu_acpi_get_backlight_caps(काष्ठा amdgpu_device *adev,
		काष्ठा amdgpu_dm_backlight_caps *caps);
bool amdgpu_acpi_is_s0ix_supported(काष्ठा amdgpu_device *adev);
#अन्यथा
अटल अंतरभूत पूर्णांक amdgpu_acpi_init(काष्ठा amdgpu_device *adev) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम amdgpu_acpi_fini(काष्ठा amdgpu_device *adev) अणु पूर्ण
अटल अंतरभूत bool amdgpu_acpi_is_s0ix_supported(काष्ठा amdgpu_device *adev) अणु वापस false; पूर्ण
#पूर्ण_अगर

पूर्णांक amdgpu_cs_find_mapping(काष्ठा amdgpu_cs_parser *parser,
			   uपूर्णांक64_t addr, काष्ठा amdgpu_bo **bo,
			   काष्ठा amdgpu_bo_va_mapping **mapping);

#अगर defined(CONFIG_DRM_AMD_DC)
पूर्णांक amdgpu_dm_display_resume(काष्ठा amdgpu_device *adev );
#अन्यथा
अटल अंतरभूत पूर्णांक amdgpu_dm_display_resume(काष्ठा amdgpu_device *adev) अणु वापस 0; पूर्ण
#पूर्ण_अगर


व्योम amdgpu_रेजिस्टर_gpu_instance(काष्ठा amdgpu_device *adev);
व्योम amdgpu_unरेजिस्टर_gpu_instance(काष्ठा amdgpu_device *adev);

pci_ers_result_t amdgpu_pci_error_detected(काष्ठा pci_dev *pdev,
					   pci_channel_state_t state);
pci_ers_result_t amdgpu_pci_mmio_enabled(काष्ठा pci_dev *pdev);
pci_ers_result_t amdgpu_pci_slot_reset(काष्ठा pci_dev *pdev);
व्योम amdgpu_pci_resume(काष्ठा pci_dev *pdev);

bool amdgpu_device_cache_pci_state(काष्ठा pci_dev *pdev);
bool amdgpu_device_load_pci_state(काष्ठा pci_dev *pdev);

bool amdgpu_device_skip_hw_access(काष्ठा amdgpu_device *adev);

पूर्णांक amdgpu_device_set_cg_state(काष्ठा amdgpu_device *adev,
			       क्रमागत amd_घड़ीgating_state state);
पूर्णांक amdgpu_device_set_pg_state(काष्ठा amdgpu_device *adev,
			       क्रमागत amd_घातergating_state state);

#समावेश "amdgpu_object.h"

अटल अंतरभूत bool amdgpu_is_पंचांगz(काष्ठा amdgpu_device *adev)
अणु
       वापस adev->gmc.पंचांगz_enabled;
पूर्ण

अटल अंतरभूत पूर्णांक amdgpu_in_reset(काष्ठा amdgpu_device *adev)
अणु
	वापस atomic_पढ़ो(&adev->in_gpu_reset);
पूर्ण
#पूर्ण_अगर
