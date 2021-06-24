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
#अगर_अघोषित __RADEON_H__
#घोषणा __RADEON_H__

/* TODO: Here are things that needs to be करोne :
 *	- surface allocator & initializer : (bit like scratch reg) should
 *	  initialize HDP_ stuff on RS600, R600, R700 hw, well anythings
 *	  related to surface
 *	- WB : ग_लिखो back stuff (करो it bit like scratch reg things)
 *	- Vblank : look at Jesse's rework and what we should करो
 *	- r600/r700: gart & cp
 *	- cs : clean cs ioctl use biपंचांगap & things like that.
 *	- घातer management stuff
 *	- Barrier in gart code
 *	- Unmappabled vram ?
 *	- TESTING, TESTING, TESTING
 */

/* Initialization path:
 *  We expect that acceleration initialization might fail क्रम various
 *  reasons even thought we work hard to make it works on most
 *  configurations. In order to still have a working userspace in such
 *  situation the init path must succeed up to the memory controller
 *  initialization poपूर्णांक. Failure beक्रमe this poपूर्णांक are considered as
 *  fatal error. Here is the init callchain :
 *      radeon_device_init  perक्रमm common काष्ठाure, mutex initialization
 *      asic_init           setup the GPU memory layout and perक्रमm all
 *                          one समय initialization (failure in this
 *                          function are considered fatal)
 *      asic_startup        setup the GPU acceleration, in order to
 *                          follow guideline the first thing this
 *                          function should करो is setting the GPU
 *                          memory controller (only MC setup failure
 *                          are considered as fatal)
 */

#समावेश <linux/atomic.h>
#समावेश <linux/रुको.h>
#समावेश <linux/list.h>
#समावेश <linux/kref.h>
#समावेश <linux/पूर्णांकerval_tree.h>
#समावेश <linux/hashtable.h>
#समावेश <linux/dma-fence.h>

#अगर_घोषित CONFIG_MMU_NOTIFIER
#समावेश <linux/mmu_notअगरier.h>
#पूर्ण_अगर

#समावेश <drm/tपंचांग/tपंचांग_bo_api.h>
#समावेश <drm/tपंचांग/tपंचांग_bo_driver.h>
#समावेश <drm/tपंचांग/tपंचांग_placement.h>
#समावेश <drm/tपंचांग/tपंचांग_execbuf_util.h>

#समावेश <drm/drm_gem.h>

#समावेश "radeon_family.h"
#समावेश "radeon_mode.h"
#समावेश "radeon_reg.h"

/*
 * Modules parameters.
 */
बाह्य पूर्णांक radeon_no_wb;
बाह्य पूर्णांक radeon_modeset;
बाह्य पूर्णांक radeon_dynclks;
बाह्य पूर्णांक radeon_r4xx_atom;
बाह्य पूर्णांक radeon_agpmode;
बाह्य पूर्णांक radeon_vram_limit;
बाह्य पूर्णांक radeon_gart_size;
बाह्य पूर्णांक radeon_benchmarking;
बाह्य पूर्णांक radeon_testing;
बाह्य पूर्णांक radeon_connector_table;
बाह्य पूर्णांक radeon_tv;
बाह्य पूर्णांक radeon_audio;
बाह्य पूर्णांक radeon_disp_priority;
बाह्य पूर्णांक radeon_hw_i2c;
बाह्य पूर्णांक radeon_pcie_gen2;
बाह्य पूर्णांक radeon_msi;
बाह्य पूर्णांक radeon_lockup_समयout;
बाह्य पूर्णांक radeon_fastfb;
बाह्य पूर्णांक radeon_dpm;
बाह्य पूर्णांक radeon_aspm;
बाह्य पूर्णांक radeon_runसमय_pm;
बाह्य पूर्णांक radeon_hard_reset;
बाह्य पूर्णांक radeon_vm_size;
बाह्य पूर्णांक radeon_vm_block_size;
बाह्य पूर्णांक radeon_deep_color;
बाह्य पूर्णांक radeon_use_pflipirq;
बाह्य पूर्णांक radeon_bapm;
बाह्य पूर्णांक radeon_backlight;
बाह्य पूर्णांक radeon_auxch;
बाह्य पूर्णांक radeon_mst;
बाह्य पूर्णांक radeon_uvd;
बाह्य पूर्णांक radeon_vce;
बाह्य पूर्णांक radeon_si_support;
बाह्य पूर्णांक radeon_cik_support;

/*
 * Copy from radeon_drv.h so we करोn't have to include both and have conflicting
 * symbol;
 */
#घोषणा RADEON_MAX_USEC_TIMEOUT			100000	/* 100 ms */
#घोषणा RADEON_FENCE_JIFFIES_TIMEOUT		(HZ / 2)
#घोषणा RADEON_USEC_IB_TEST_TIMEOUT		1000000 /* 1s */
/* RADEON_IB_POOL_SIZE must be a घातer of 2 */
#घोषणा RADEON_IB_POOL_SIZE			16
#घोषणा RADEON_DEBUGFS_MAX_COMPONENTS		32
#घोषणा RADEONFB_CONN_LIMIT			4
#घोषणा RADEON_BIOS_NUM_SCRATCH			8

/* पूर्णांकernal ring indices */
/* r1xx+ has gfx CP ring */
#घोषणा RADEON_RING_TYPE_GFX_INDEX		0

/* cayman has 2 compute CP rings */
#घोषणा CAYMAN_RING_TYPE_CP1_INDEX		1
#घोषणा CAYMAN_RING_TYPE_CP2_INDEX		2

/* R600+ has an async dma ring */
#घोषणा R600_RING_TYPE_DMA_INDEX		3
/* cayman add a second async dma ring */
#घोषणा CAYMAN_RING_TYPE_DMA1_INDEX		4

/* R600+ */
#घोषणा R600_RING_TYPE_UVD_INDEX		5

/* TN+ */
#घोषणा TN_RING_TYPE_VCE1_INDEX			6
#घोषणा TN_RING_TYPE_VCE2_INDEX			7

/* max number of rings */
#घोषणा RADEON_NUM_RINGS			8

/* number of hw syncs beक्रमe falling back on blocking */
#घोषणा RADEON_NUM_SYNCS			4

/* hardcode those limit क्रम now */
#घोषणा RADEON_VA_IB_OFFSET			(1 << 20)
#घोषणा RADEON_VA_RESERVED_SIZE			(8 << 20)
#घोषणा RADEON_IB_VM_MAX_SIZE			(64 << 10)

/* hard reset data */
#घोषणा RADEON_ASIC_RESET_DATA                  0x39d5e86b

/* reset flags */
#घोषणा RADEON_RESET_GFX			(1 << 0)
#घोषणा RADEON_RESET_COMPUTE			(1 << 1)
#घोषणा RADEON_RESET_DMA			(1 << 2)
#घोषणा RADEON_RESET_CP				(1 << 3)
#घोषणा RADEON_RESET_GRBM			(1 << 4)
#घोषणा RADEON_RESET_DMA1			(1 << 5)
#घोषणा RADEON_RESET_RLC			(1 << 6)
#घोषणा RADEON_RESET_SEM			(1 << 7)
#घोषणा RADEON_RESET_IH				(1 << 8)
#घोषणा RADEON_RESET_VMC			(1 << 9)
#घोषणा RADEON_RESET_MC				(1 << 10)
#घोषणा RADEON_RESET_DISPLAY			(1 << 11)

/* CG block flags */
#घोषणा RADEON_CG_BLOCK_GFX			(1 << 0)
#घोषणा RADEON_CG_BLOCK_MC			(1 << 1)
#घोषणा RADEON_CG_BLOCK_SDMA			(1 << 2)
#घोषणा RADEON_CG_BLOCK_UVD			(1 << 3)
#घोषणा RADEON_CG_BLOCK_VCE			(1 << 4)
#घोषणा RADEON_CG_BLOCK_HDP			(1 << 5)
#घोषणा RADEON_CG_BLOCK_BIF			(1 << 6)

/* CG flags */
#घोषणा RADEON_CG_SUPPORT_GFX_MGCG		(1 << 0)
#घोषणा RADEON_CG_SUPPORT_GFX_MGLS		(1 << 1)
#घोषणा RADEON_CG_SUPPORT_GFX_CGCG		(1 << 2)
#घोषणा RADEON_CG_SUPPORT_GFX_CGLS		(1 << 3)
#घोषणा RADEON_CG_SUPPORT_GFX_CGTS		(1 << 4)
#घोषणा RADEON_CG_SUPPORT_GFX_CGTS_LS		(1 << 5)
#घोषणा RADEON_CG_SUPPORT_GFX_CP_LS		(1 << 6)
#घोषणा RADEON_CG_SUPPORT_GFX_RLC_LS		(1 << 7)
#घोषणा RADEON_CG_SUPPORT_MC_LS			(1 << 8)
#घोषणा RADEON_CG_SUPPORT_MC_MGCG		(1 << 9)
#घोषणा RADEON_CG_SUPPORT_SDMA_LS		(1 << 10)
#घोषणा RADEON_CG_SUPPORT_SDMA_MGCG		(1 << 11)
#घोषणा RADEON_CG_SUPPORT_BIF_LS		(1 << 12)
#घोषणा RADEON_CG_SUPPORT_UVD_MGCG		(1 << 13)
#घोषणा RADEON_CG_SUPPORT_VCE_MGCG		(1 << 14)
#घोषणा RADEON_CG_SUPPORT_HDP_LS		(1 << 15)
#घोषणा RADEON_CG_SUPPORT_HDP_MGCG		(1 << 16)

/* PG flags */
#घोषणा RADEON_PG_SUPPORT_GFX_PG		(1 << 0)
#घोषणा RADEON_PG_SUPPORT_GFX_SMG		(1 << 1)
#घोषणा RADEON_PG_SUPPORT_GFX_DMG		(1 << 2)
#घोषणा RADEON_PG_SUPPORT_UVD			(1 << 3)
#घोषणा RADEON_PG_SUPPORT_VCE			(1 << 4)
#घोषणा RADEON_PG_SUPPORT_CP			(1 << 5)
#घोषणा RADEON_PG_SUPPORT_GDS			(1 << 6)
#घोषणा RADEON_PG_SUPPORT_RLC_SMU_HS		(1 << 7)
#घोषणा RADEON_PG_SUPPORT_SDMA			(1 << 8)
#घोषणा RADEON_PG_SUPPORT_ACP			(1 << 9)
#घोषणा RADEON_PG_SUPPORT_SAMU			(1 << 10)

/* max cursor sizes (in pixels) */
#घोषणा CURSOR_WIDTH 64
#घोषणा CURSOR_HEIGHT 64

#घोषणा CIK_CURSOR_WIDTH 128
#घोषणा CIK_CURSOR_HEIGHT 128

/*
 * Errata workarounds.
 */
क्रमागत radeon_pll_errata अणु
	CHIP_ERRATA_R300_CG             = 0x00000001,
	CHIP_ERRATA_PLL_DUMMYREADS      = 0x00000002,
	CHIP_ERRATA_PLL_DELAY           = 0x00000004
पूर्ण;


काष्ठा radeon_device;


/*
 * BIOS.
 */
bool radeon_get_bios(काष्ठा radeon_device *rdev);

/*
 * Dummy page
 */
काष्ठा radeon_dummy_page अणु
	uपूर्णांक64_t	entry;
	काष्ठा page	*page;
	dma_addr_t	addr;
पूर्ण;
पूर्णांक radeon_dummy_page_init(काष्ठा radeon_device *rdev);
व्योम radeon_dummy_page_fini(काष्ठा radeon_device *rdev);


/*
 * Clocks
 */
काष्ठा radeon_घड़ी अणु
	काष्ठा radeon_pll p1pll;
	काष्ठा radeon_pll p2pll;
	काष्ठा radeon_pll dcpll;
	काष्ठा radeon_pll spll;
	काष्ठा radeon_pll mpll;
	/* 10 Khz units */
	uपूर्णांक32_t शेष_mclk;
	uपूर्णांक32_t शेष_sclk;
	uपूर्णांक32_t शेष_dispclk;
	uपूर्णांक32_t current_dispclk;
	uपूर्णांक32_t dp_extclk;
	uपूर्णांक32_t max_pixel_घड़ी;
	uपूर्णांक32_t vco_freq;
पूर्ण;

/*
 * Power management
 */
पूर्णांक radeon_pm_init(काष्ठा radeon_device *rdev);
पूर्णांक radeon_pm_late_init(काष्ठा radeon_device *rdev);
व्योम radeon_pm_fini(काष्ठा radeon_device *rdev);
व्योम radeon_pm_compute_घड़ीs(काष्ठा radeon_device *rdev);
व्योम radeon_pm_suspend(काष्ठा radeon_device *rdev);
व्योम radeon_pm_resume(काष्ठा radeon_device *rdev);
व्योम radeon_combios_get_घातer_modes(काष्ठा radeon_device *rdev);
व्योम radeon_atombios_get_घातer_modes(काष्ठा radeon_device *rdev);
पूर्णांक radeon_atom_get_घड़ी_भागiders(काष्ठा radeon_device *rdev,
				   u8 घड़ी_प्रकारype,
				   u32 घड़ी,
				   bool strobe_mode,
				   काष्ठा atom_घड़ी_भागiders *भागiders);
पूर्णांक radeon_atom_get_memory_pll_भागiders(काष्ठा radeon_device *rdev,
					u32 घड़ी,
					bool strobe_mode,
					काष्ठा atom_mpll_param *mpll_param);
व्योम radeon_atom_set_voltage(काष्ठा radeon_device *rdev, u16 voltage_level, u8 voltage_type);
पूर्णांक radeon_atom_get_voltage_gpio_settings(काष्ठा radeon_device *rdev,
					  u16 voltage_level, u8 voltage_type,
					  u32 *gpio_value, u32 *gpio_mask);
व्योम radeon_atom_set_engine_dram_timings(काष्ठा radeon_device *rdev,
					 u32 eng_घड़ी, u32 mem_घड़ी);
पूर्णांक radeon_atom_get_voltage_step(काष्ठा radeon_device *rdev,
				 u8 voltage_type, u16 *voltage_step);
पूर्णांक radeon_atom_get_max_vddc(काष्ठा radeon_device *rdev, u8 voltage_type,
			     u16 voltage_id, u16 *voltage);
पूर्णांक radeon_atom_get_leakage_vddc_based_on_leakage_idx(काष्ठा radeon_device *rdev,
						      u16 *voltage,
						      u16 leakage_idx);
पूर्णांक radeon_atom_get_leakage_id_from_vbios(काष्ठा radeon_device *rdev,
					  u16 *leakage_id);
पूर्णांक radeon_atom_get_leakage_vddc_based_on_leakage_params(काष्ठा radeon_device *rdev,
							 u16 *vddc, u16 *vddci,
							 u16 भव_voltage_id,
							 u16 vbios_voltage_id);
पूर्णांक radeon_atom_get_voltage_evv(काष्ठा radeon_device *rdev,
				u16 भव_voltage_id,
				u16 *voltage);
पूर्णांक radeon_atom_round_to_true_voltage(काष्ठा radeon_device *rdev,
				      u8 voltage_type,
				      u16 nominal_voltage,
				      u16 *true_voltage);
पूर्णांक radeon_atom_get_min_voltage(काष्ठा radeon_device *rdev,
				u8 voltage_type, u16 *min_voltage);
पूर्णांक radeon_atom_get_max_voltage(काष्ठा radeon_device *rdev,
				u8 voltage_type, u16 *max_voltage);
पूर्णांक radeon_atom_get_voltage_table(काष्ठा radeon_device *rdev,
				  u8 voltage_type, u8 voltage_mode,
				  काष्ठा atom_voltage_table *voltage_table);
bool radeon_atom_is_voltage_gpio(काष्ठा radeon_device *rdev,
				 u8 voltage_type, u8 voltage_mode);
पूर्णांक radeon_atom_get_svi2_info(काष्ठा radeon_device *rdev,
			      u8 voltage_type,
			      u8 *svd_gpio_id, u8 *svc_gpio_id);
व्योम radeon_atom_update_memory_dll(काष्ठा radeon_device *rdev,
				   u32 mem_घड़ी);
व्योम radeon_atom_set_ac_timing(काष्ठा radeon_device *rdev,
			       u32 mem_घड़ी);
पूर्णांक radeon_atom_init_mc_reg_table(काष्ठा radeon_device *rdev,
				  u8 module_index,
				  काष्ठा atom_mc_reg_table *reg_table);
पूर्णांक radeon_atom_get_memory_info(काष्ठा radeon_device *rdev,
				u8 module_index, काष्ठा atom_memory_info *mem_info);
पूर्णांक radeon_atom_get_mclk_range_table(काष्ठा radeon_device *rdev,
				     bool gddr5, u8 module_index,
				     काष्ठा atom_memory_घड़ी_range_table *mclk_range_table);
पूर्णांक radeon_atom_get_max_vddc(काष्ठा radeon_device *rdev, u8 voltage_type,
			     u16 voltage_id, u16 *voltage);
व्योम rs690_pm_info(काष्ठा radeon_device *rdev);
बाह्य व्योम evergreen_tiling_fields(अचिन्हित tiling_flags, अचिन्हित *bankw,
				    अचिन्हित *bankh, अचिन्हित *mtaspect,
				    अचिन्हित *tile_split);

/*
 * Fences.
 */
काष्ठा radeon_fence_driver अणु
	काष्ठा radeon_device		*rdev;
	uपूर्णांक32_t			scratch_reg;
	uपूर्णांक64_t			gpu_addr;
	अस्थिर uपूर्णांक32_t		*cpu_addr;
	/* sync_seq is रक्षित by ring emission lock */
	uपूर्णांक64_t			sync_seq[RADEON_NUM_RINGS];
	atomic64_t			last_seq;
	bool				initialized, delayed_irq;
	काष्ठा delayed_work		lockup_work;
पूर्ण;

काष्ठा radeon_fence अणु
	काष्ठा dma_fence		base;

	काष्ठा radeon_device	*rdev;
	uपूर्णांक64_t		seq;
	/* RB, DMA, etc. */
	अचिन्हित		ring;
	bool			is_vm_update;

	रुको_queue_entry_t		fence_wake;
पूर्ण;

पूर्णांक radeon_fence_driver_start_ring(काष्ठा radeon_device *rdev, पूर्णांक ring);
पूर्णांक radeon_fence_driver_init(काष्ठा radeon_device *rdev);
व्योम radeon_fence_driver_fini(काष्ठा radeon_device *rdev);
व्योम radeon_fence_driver_क्रमce_completion(काष्ठा radeon_device *rdev, पूर्णांक ring);
पूर्णांक radeon_fence_emit(काष्ठा radeon_device *rdev, काष्ठा radeon_fence **fence, पूर्णांक ring);
व्योम radeon_fence_process(काष्ठा radeon_device *rdev, पूर्णांक ring);
bool radeon_fence_संकेतed(काष्ठा radeon_fence *fence);
दीर्घ radeon_fence_रुको_समयout(काष्ठा radeon_fence *fence, bool पूर्णांकerruptible, दीर्घ समयout);
पूर्णांक radeon_fence_रुको(काष्ठा radeon_fence *fence, bool पूर्णांकerruptible);
पूर्णांक radeon_fence_रुको_next(काष्ठा radeon_device *rdev, पूर्णांक ring);
पूर्णांक radeon_fence_रुको_empty(काष्ठा radeon_device *rdev, पूर्णांक ring);
पूर्णांक radeon_fence_रुको_any(काष्ठा radeon_device *rdev,
			  काष्ठा radeon_fence **fences,
			  bool पूर्णांकr);
काष्ठा radeon_fence *radeon_fence_ref(काष्ठा radeon_fence *fence);
व्योम radeon_fence_unref(काष्ठा radeon_fence **fence);
अचिन्हित radeon_fence_count_emitted(काष्ठा radeon_device *rdev, पूर्णांक ring);
bool radeon_fence_need_sync(काष्ठा radeon_fence *fence, पूर्णांक ring);
व्योम radeon_fence_note_sync(काष्ठा radeon_fence *fence, पूर्णांक ring);
अटल अंतरभूत काष्ठा radeon_fence *radeon_fence_later(काष्ठा radeon_fence *a,
						      काष्ठा radeon_fence *b)
अणु
	अगर (!a) अणु
		वापस b;
	पूर्ण

	अगर (!b) अणु
		वापस a;
	पूर्ण

	BUG_ON(a->ring != b->ring);

	अगर (a->seq > b->seq) अणु
		वापस a;
	पूर्ण अन्यथा अणु
		वापस b;
	पूर्ण
पूर्ण

अटल अंतरभूत bool radeon_fence_is_earlier(काष्ठा radeon_fence *a,
					   काष्ठा radeon_fence *b)
अणु
	अगर (!a) अणु
		वापस false;
	पूर्ण

	अगर (!b) अणु
		वापस true;
	पूर्ण

	BUG_ON(a->ring != b->ring);

	वापस a->seq < b->seq;
पूर्ण

/*
 * Tiling रेजिस्टरs
 */
काष्ठा radeon_surface_reg अणु
	काष्ठा radeon_bo *bo;
पूर्ण;

#घोषणा RADEON_GEM_MAX_SURFACES 8

/*
 * TTM.
 */
काष्ठा radeon_mman अणु
	काष्ठा tपंचांग_device		bdev;
	bool				initialized;
पूर्ण;

काष्ठा radeon_bo_list अणु
	काष्ठा radeon_bo		*robj;
	काष्ठा tपंचांग_validate_buffer	tv;
	uपूर्णांक64_t			gpu_offset;
	अचिन्हित			preferred_करोमुख्यs;
	अचिन्हित			allowed_करोमुख्यs;
	uपूर्णांक32_t			tiling_flags;
पूर्ण;

/* bo भव address in a specअगरic vm */
काष्ठा radeon_bo_va अणु
	/* रक्षित by bo being reserved */
	काष्ठा list_head		bo_list;
	uपूर्णांक32_t			flags;
	काष्ठा radeon_fence		*last_pt_update;
	अचिन्हित			ref_count;

	/* रक्षित by vm mutex */
	काष्ठा पूर्णांकerval_tree_node	it;
	काष्ठा list_head		vm_status;

	/* स्थिरant after initialization */
	काष्ठा radeon_vm		*vm;
	काष्ठा radeon_bo		*bo;
पूर्ण;

काष्ठा radeon_bo अणु
	/* Protected by gem.mutex */
	काष्ठा list_head		list;
	/* Protected by tbo.reserved */
	u32				initial_करोमुख्य;
	काष्ठा tपंचांग_place		placements[4];
	काष्ठा tपंचांग_placement		placement;
	काष्ठा tपंचांग_buffer_object	tbo;
	काष्ठा tपंचांग_bo_kmap_obj		kmap;
	u32				flags;
	व्योम				*kptr;
	u32				tiling_flags;
	u32				pitch;
	पूर्णांक				surface_reg;
	अचिन्हित			prime_shared_count;
	/* list of all भव address to which this bo
	 * is associated to
	 */
	काष्ठा list_head		va;
	/* Constant after initialization */
	काष्ठा radeon_device		*rdev;

	pid_t				pid;

#अगर_घोषित CONFIG_MMU_NOTIFIER
	काष्ठा mmu_पूर्णांकerval_notअगरier	notअगरier;
#पूर्ण_अगर
पूर्ण;
#घोषणा gem_to_radeon_bo(gobj) container_of((gobj), काष्ठा radeon_bo, tbo.base)

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
काष्ठा radeon_sa_manager अणु
	रुको_queue_head_t	wq;
	काष्ठा radeon_bo	*bo;
	काष्ठा list_head	*hole;
	काष्ठा list_head	flist[RADEON_NUM_RINGS];
	काष्ठा list_head	olist;
	अचिन्हित		size;
	uपूर्णांक64_t		gpu_addr;
	व्योम			*cpu_ptr;
	uपूर्णांक32_t		करोमुख्य;
	uपूर्णांक32_t		align;
पूर्ण;

काष्ठा radeon_sa_bo;

/* sub-allocation buffer */
काष्ठा radeon_sa_bo अणु
	काष्ठा list_head		olist;
	काष्ठा list_head		flist;
	काष्ठा radeon_sa_manager	*manager;
	अचिन्हित			soffset;
	अचिन्हित			eoffset;
	काष्ठा radeon_fence		*fence;
पूर्ण;

/*
 * GEM objects.
 */
काष्ठा radeon_gem अणु
	काष्ठा mutex		mutex;
	काष्ठा list_head	objects;
पूर्ण;

बाह्य स्थिर काष्ठा drm_gem_object_funcs radeon_gem_object_funcs;

पूर्णांक radeon_gem_init(काष्ठा radeon_device *rdev);
व्योम radeon_gem_fini(काष्ठा radeon_device *rdev);
पूर्णांक radeon_gem_object_create(काष्ठा radeon_device *rdev, अचिन्हित दीर्घ size,
				पूर्णांक alignment, पूर्णांक initial_करोमुख्य,
				u32 flags, bool kernel,
				काष्ठा drm_gem_object **obj);

पूर्णांक radeon_mode_dumb_create(काष्ठा drm_file *file_priv,
			    काष्ठा drm_device *dev,
			    काष्ठा drm_mode_create_dumb *args);
पूर्णांक radeon_mode_dumb_mmap(काष्ठा drm_file *filp,
			  काष्ठा drm_device *dev,
			  uपूर्णांक32_t handle, uपूर्णांक64_t *offset_p);

/*
 * Semaphores.
 */
काष्ठा radeon_semaphore अणु
	काष्ठा radeon_sa_bo	*sa_bo;
	चिन्हित			रुकोers;
	uपूर्णांक64_t		gpu_addr;
पूर्ण;

पूर्णांक radeon_semaphore_create(काष्ठा radeon_device *rdev,
			    काष्ठा radeon_semaphore **semaphore);
bool radeon_semaphore_emit_संकेत(काष्ठा radeon_device *rdev, पूर्णांक ring,
				  काष्ठा radeon_semaphore *semaphore);
bool radeon_semaphore_emit_रुको(काष्ठा radeon_device *rdev, पूर्णांक ring,
				काष्ठा radeon_semaphore *semaphore);
व्योम radeon_semaphore_मुक्त(काष्ठा radeon_device *rdev,
			   काष्ठा radeon_semaphore **semaphore,
			   काष्ठा radeon_fence *fence);

/*
 * Synchronization
 */
काष्ठा radeon_sync अणु
	काष्ठा radeon_semaphore *semaphores[RADEON_NUM_SYNCS];
	काष्ठा radeon_fence	*sync_to[RADEON_NUM_RINGS];
	काष्ठा radeon_fence	*last_vm_update;
पूर्ण;

व्योम radeon_sync_create(काष्ठा radeon_sync *sync);
व्योम radeon_sync_fence(काष्ठा radeon_sync *sync,
		       काष्ठा radeon_fence *fence);
पूर्णांक radeon_sync_resv(काष्ठा radeon_device *rdev,
		     काष्ठा radeon_sync *sync,
		     काष्ठा dma_resv *resv,
		     bool shared);
पूर्णांक radeon_sync_rings(काष्ठा radeon_device *rdev,
		      काष्ठा radeon_sync *sync,
		      पूर्णांक रुकोing_ring);
व्योम radeon_sync_मुक्त(काष्ठा radeon_device *rdev, काष्ठा radeon_sync *sync,
		      काष्ठा radeon_fence *fence);

/*
 * GART काष्ठाures, functions & helpers
 */
काष्ठा radeon_mc;

#घोषणा RADEON_GPU_PAGE_SIZE 4096
#घोषणा RADEON_GPU_PAGE_MASK (RADEON_GPU_PAGE_SIZE - 1)
#घोषणा RADEON_GPU_PAGE_SHIFT 12
#घोषणा RADEON_GPU_PAGE_ALIGN(a) (((a) + RADEON_GPU_PAGE_MASK) & ~RADEON_GPU_PAGE_MASK)

#घोषणा RADEON_GART_PAGE_DUMMY  0
#घोषणा RADEON_GART_PAGE_VALID	(1 << 0)
#घोषणा RADEON_GART_PAGE_READ	(1 << 1)
#घोषणा RADEON_GART_PAGE_WRITE	(1 << 2)
#घोषणा RADEON_GART_PAGE_SNOOP	(1 << 3)

काष्ठा radeon_gart अणु
	dma_addr_t			table_addr;
	काष्ठा radeon_bo		*robj;
	व्योम				*ptr;
	अचिन्हित			num_gpu_pages;
	अचिन्हित			num_cpu_pages;
	अचिन्हित			table_size;
	काष्ठा page			**pages;
	uपूर्णांक64_t			*pages_entry;
	bool				पढ़ोy;
पूर्ण;

पूर्णांक radeon_gart_table_ram_alloc(काष्ठा radeon_device *rdev);
व्योम radeon_gart_table_ram_मुक्त(काष्ठा radeon_device *rdev);
पूर्णांक radeon_gart_table_vram_alloc(काष्ठा radeon_device *rdev);
व्योम radeon_gart_table_vram_मुक्त(काष्ठा radeon_device *rdev);
पूर्णांक radeon_gart_table_vram_pin(काष्ठा radeon_device *rdev);
व्योम radeon_gart_table_vram_unpin(काष्ठा radeon_device *rdev);
पूर्णांक radeon_gart_init(काष्ठा radeon_device *rdev);
व्योम radeon_gart_fini(काष्ठा radeon_device *rdev);
व्योम radeon_gart_unbind(काष्ठा radeon_device *rdev, अचिन्हित offset,
			पूर्णांक pages);
पूर्णांक radeon_gart_bind(काष्ठा radeon_device *rdev, अचिन्हित offset,
		     पूर्णांक pages, काष्ठा page **pagelist,
		     dma_addr_t *dma_addr, uपूर्णांक32_t flags);


/*
 * GPU MC काष्ठाures, functions & helpers
 */
काष्ठा radeon_mc अणु
	resource_माप_प्रकार		aper_size;
	resource_माप_प्रकार		aper_base;
	resource_माप_प्रकार		agp_base;
	/* क्रम some chips with <= 32MB we need to lie
	 * about vram size near mc fb location */
	u64			mc_vram_size;
	u64			visible_vram_size;
	u64			gtt_size;
	u64			gtt_start;
	u64			gtt_end;
	u64			vram_start;
	u64			vram_end;
	अचिन्हित		vram_width;
	u64			real_vram_size;
	पूर्णांक			vram_mtrr;
	bool			vram_is_ddr;
	bool			igp_sideport_enabled;
	u64                     gtt_base_align;
	u64                     mc_mask;
पूर्ण;

bool radeon_combios_sideport_present(काष्ठा radeon_device *rdev);
bool radeon_atombios_sideport_present(काष्ठा radeon_device *rdev);

/*
 * GPU scratch रेजिस्टरs काष्ठाures, functions & helpers
 */
काष्ठा radeon_scratch अणु
	अचिन्हित		num_reg;
	uपूर्णांक32_t                reg_base;
	bool			मुक्त[32];
	uपूर्णांक32_t		reg[32];
पूर्ण;

पूर्णांक radeon_scratch_get(काष्ठा radeon_device *rdev, uपूर्णांक32_t *reg);
व्योम radeon_scratch_मुक्त(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg);

/*
 * GPU करोorbell काष्ठाures, functions & helpers
 */
#घोषणा RADEON_MAX_DOORBELLS 1024	/* Reserve at most 1024 करोorbell slots क्रम radeon-owned rings. */

काष्ठा radeon_करोorbell अणु
	/* करोorbell mmio */
	resource_माप_प्रकार		base;
	resource_माप_प्रकार		size;
	u32 __iomem		*ptr;
	u32			num_करोorbells;	/* Number of करोorbells actually reserved क्रम radeon. */
	DECLARE_BITMAP(used, RADEON_MAX_DOORBELLS);
पूर्ण;

पूर्णांक radeon_करोorbell_get(काष्ठा radeon_device *rdev, u32 *page);
व्योम radeon_करोorbell_मुक्त(काष्ठा radeon_device *rdev, u32 करोorbell);

/*
 * IRQS.
 */

काष्ठा radeon_flip_work अणु
	काष्ठा work_काष्ठा		flip_work;
	काष्ठा work_काष्ठा		unpin_work;
	काष्ठा radeon_device		*rdev;
	पूर्णांक				crtc_id;
	u32				target_vblank;
	uपूर्णांक64_t			base;
	काष्ठा drm_pending_vblank_event *event;
	काष्ठा radeon_bo		*old_rbo;
	काष्ठा dma_fence		*fence;
	bool				async;
पूर्ण;

काष्ठा r500_irq_stat_regs अणु
	u32 disp_पूर्णांक;
	u32 hdmi0_status;
पूर्ण;

काष्ठा r600_irq_stat_regs अणु
	u32 disp_पूर्णांक;
	u32 disp_पूर्णांक_cont;
	u32 disp_पूर्णांक_cont2;
	u32 d1grph_पूर्णांक;
	u32 d2grph_पूर्णांक;
	u32 hdmi0_status;
	u32 hdmi1_status;
पूर्ण;

काष्ठा evergreen_irq_stat_regs अणु
	u32 disp_पूर्णांक[6];
	u32 grph_पूर्णांक[6];
	u32 afmt_status[6];
पूर्ण;

काष्ठा cik_irq_stat_regs अणु
	u32 disp_पूर्णांक;
	u32 disp_पूर्णांक_cont;
	u32 disp_पूर्णांक_cont2;
	u32 disp_पूर्णांक_cont3;
	u32 disp_पूर्णांक_cont4;
	u32 disp_पूर्णांक_cont5;
	u32 disp_पूर्णांक_cont6;
	u32 d1grph_पूर्णांक;
	u32 d2grph_पूर्णांक;
	u32 d3grph_पूर्णांक;
	u32 d4grph_पूर्णांक;
	u32 d5grph_पूर्णांक;
	u32 d6grph_पूर्णांक;
पूर्ण;

जोड़ radeon_irq_stat_regs अणु
	काष्ठा r500_irq_stat_regs r500;
	काष्ठा r600_irq_stat_regs r600;
	काष्ठा evergreen_irq_stat_regs evergreen;
	काष्ठा cik_irq_stat_regs cik;
पूर्ण;

काष्ठा radeon_irq अणु
	bool				installed;
	spinlock_t			lock;
	atomic_t			ring_पूर्णांक[RADEON_NUM_RINGS];
	bool				crtc_vblank_पूर्णांक[RADEON_MAX_CRTCS];
	atomic_t			pflip[RADEON_MAX_CRTCS];
	रुको_queue_head_t		vblank_queue;
	bool				hpd[RADEON_MAX_HPD_PINS];
	bool				afmt[RADEON_MAX_AFMT_BLOCKS];
	जोड़ radeon_irq_stat_regs	stat_regs;
	bool				dpm_thermal;
पूर्ण;

पूर्णांक radeon_irq_kms_init(काष्ठा radeon_device *rdev);
व्योम radeon_irq_kms_fini(काष्ठा radeon_device *rdev);
व्योम radeon_irq_kms_sw_irq_get(काष्ठा radeon_device *rdev, पूर्णांक ring);
bool radeon_irq_kms_sw_irq_get_delayed(काष्ठा radeon_device *rdev, पूर्णांक ring);
व्योम radeon_irq_kms_sw_irq_put(काष्ठा radeon_device *rdev, पूर्णांक ring);
व्योम radeon_irq_kms_pflip_irq_get(काष्ठा radeon_device *rdev, पूर्णांक crtc);
व्योम radeon_irq_kms_pflip_irq_put(काष्ठा radeon_device *rdev, पूर्णांक crtc);
व्योम radeon_irq_kms_enable_afmt(काष्ठा radeon_device *rdev, पूर्णांक block);
व्योम radeon_irq_kms_disable_afmt(काष्ठा radeon_device *rdev, पूर्णांक block);
व्योम radeon_irq_kms_enable_hpd(काष्ठा radeon_device *rdev, अचिन्हित hpd_mask);
व्योम radeon_irq_kms_disable_hpd(काष्ठा radeon_device *rdev, अचिन्हित hpd_mask);

/*
 * CP & rings.
 */

काष्ठा radeon_ib अणु
	काष्ठा radeon_sa_bo		*sa_bo;
	uपूर्णांक32_t			length_dw;
	uपूर्णांक64_t			gpu_addr;
	uपूर्णांक32_t			*ptr;
	पूर्णांक				ring;
	काष्ठा radeon_fence		*fence;
	काष्ठा radeon_vm		*vm;
	bool				is_स्थिर_ib;
	काष्ठा radeon_sync		sync;
पूर्ण;

काष्ठा radeon_ring अणु
	काष्ठा radeon_device	*rdev;
	काष्ठा radeon_bo	*ring_obj;
	अस्थिर uपूर्णांक32_t	*ring;
	अचिन्हित		rptr_offs;
	अचिन्हित		rptr_save_reg;
	u64			next_rptr_gpu_addr;
	अस्थिर u32		*next_rptr_cpu_addr;
	अचिन्हित		wptr;
	अचिन्हित		wptr_old;
	अचिन्हित		ring_size;
	अचिन्हित		ring_मुक्त_dw;
	पूर्णांक			count_dw;
	atomic_t		last_rptr;
	atomic64_t		last_activity;
	uपूर्णांक64_t		gpu_addr;
	uपूर्णांक32_t		align_mask;
	uपूर्णांक32_t		ptr_mask;
	bool			पढ़ोy;
	u32			nop;
	u32			idx;
	u64			last_semaphore_संकेत_addr;
	u64			last_semaphore_रुको_addr;
	/* क्रम CIK queues */
	u32 me;
	u32 pipe;
	u32 queue;
	काष्ठा radeon_bo	*mqd_obj;
	u32 करोorbell_index;
	अचिन्हित		wptr_offs;
पूर्ण;

काष्ठा radeon_mec अणु
	काष्ठा radeon_bo	*hpd_eop_obj;
	u64			hpd_eop_gpu_addr;
	u32 num_pipe;
	u32 num_mec;
	u32 num_queue;
पूर्ण;

/*
 * VM
 */

/* maximum number of VMIDs */
#घोषणा RADEON_NUM_VM	16

/* number of entries in page table */
#घोषणा RADEON_VM_PTE_COUNT (1 << radeon_vm_block_size)

/* PTBs (Page Table Blocks) need to be aligned to 32K */
#घोषणा RADEON_VM_PTB_ALIGN_SIZE   32768
#घोषणा RADEON_VM_PTB_ALIGN_MASK (RADEON_VM_PTB_ALIGN_SIZE - 1)
#घोषणा RADEON_VM_PTB_ALIGN(a) (((a) + RADEON_VM_PTB_ALIGN_MASK) & ~RADEON_VM_PTB_ALIGN_MASK)

#घोषणा R600_PTE_VALID		(1 << 0)
#घोषणा R600_PTE_SYSTEM		(1 << 1)
#घोषणा R600_PTE_SNOOPED	(1 << 2)
#घोषणा R600_PTE_READABLE	(1 << 5)
#घोषणा R600_PTE_WRITEABLE	(1 << 6)

/* PTE (Page Table Entry) fragment field क्रम dअगरferent page sizes */
#घोषणा R600_PTE_FRAG_4KB	(0 << 7)
#घोषणा R600_PTE_FRAG_64KB	(4 << 7)
#घोषणा R600_PTE_FRAG_256KB	(6 << 7)

/* flags needed to be set so we can copy directly from the GART table */
#घोषणा R600_PTE_GART_MASK	( R600_PTE_READABLE | R600_PTE_WRITEABLE | \
				  R600_PTE_SYSTEM | R600_PTE_VALID )

काष्ठा radeon_vm_pt अणु
	काष्ठा radeon_bo		*bo;
	uपूर्णांक64_t			addr;
पूर्ण;

काष्ठा radeon_vm_id अणु
	अचिन्हित		id;
	uपूर्णांक64_t		pd_gpu_addr;
	/* last flushed PD/PT update */
	काष्ठा radeon_fence	*flushed_updates;
	/* last use of vmid */
	काष्ठा radeon_fence	*last_id_use;
पूर्ण;

काष्ठा radeon_vm अणु
	काष्ठा mutex		mutex;

	काष्ठा rb_root_cached	va;

	/* protecting invalidated and मुक्तd */
	spinlock_t		status_lock;

	/* BOs moved, but not yet updated in the PT */
	काष्ठा list_head	invalidated;

	/* BOs मुक्तd, but not yet updated in the PT */
	काष्ठा list_head	मुक्तd;

	/* BOs cleared in the PT */
	काष्ठा list_head	cleared;

	/* contains the page directory */
	काष्ठा radeon_bo	*page_directory;
	अचिन्हित		max_pde_used;

	/* array of page tables, one क्रम each page directory entry */
	काष्ठा radeon_vm_pt	*page_tables;

	काष्ठा radeon_bo_va	*ib_bo_va;

	/* क्रम id and flush management per ring */
	काष्ठा radeon_vm_id	ids[RADEON_NUM_RINGS];
पूर्ण;

काष्ठा radeon_vm_manager अणु
	काष्ठा radeon_fence		*active[RADEON_NUM_VM];
	uपूर्णांक32_t			max_pfn;
	/* number of VMIDs */
	अचिन्हित			nvm;
	/* vram base address क्रम page table entry  */
	u64				vram_base_offset;
	/* is vm enabled? */
	bool				enabled;
	/* क्रम hw to save the PD addr on suspend/resume */
	uपूर्णांक32_t			saved_table_addr[RADEON_NUM_VM];
पूर्ण;

/*
 * file निजी काष्ठाure
 */
काष्ठा radeon_fpriv अणु
	काष्ठा radeon_vm		vm;
पूर्ण;

/*
 * R6xx+ IH ring
 */
काष्ठा r600_ih अणु
	काष्ठा radeon_bo	*ring_obj;
	अस्थिर uपूर्णांक32_t	*ring;
	अचिन्हित		rptr;
	अचिन्हित		ring_size;
	uपूर्णांक64_t		gpu_addr;
	uपूर्णांक32_t		ptr_mask;
	atomic_t		lock;
	bool                    enabled;
पूर्ण;

/*
 * RLC stuff
 */
#समावेश "clearstate_defs.h"

काष्ठा radeon_rlc अणु
	/* क्रम घातer gating */
	काष्ठा radeon_bo	*save_restore_obj;
	uपूर्णांक64_t		save_restore_gpu_addr;
	अस्थिर uपूर्णांक32_t	*sr_ptr;
	स्थिर u32               *reg_list;
	u32                     reg_list_size;
	/* क्रम clear state */
	काष्ठा radeon_bo	*clear_state_obj;
	uपूर्णांक64_t		clear_state_gpu_addr;
	अस्थिर uपूर्णांक32_t	*cs_ptr;
	स्थिर काष्ठा cs_section_def   *cs_data;
	u32                     clear_state_size;
	/* क्रम cp tables */
	काष्ठा radeon_bo	*cp_table_obj;
	uपूर्णांक64_t		cp_table_gpu_addr;
	अस्थिर uपूर्णांक32_t	*cp_table_ptr;
	u32                     cp_table_size;
पूर्ण;

पूर्णांक radeon_ib_get(काष्ठा radeon_device *rdev, पूर्णांक ring,
		  काष्ठा radeon_ib *ib, काष्ठा radeon_vm *vm,
		  अचिन्हित size);
व्योम radeon_ib_मुक्त(काष्ठा radeon_device *rdev, काष्ठा radeon_ib *ib);
पूर्णांक radeon_ib_schedule(काष्ठा radeon_device *rdev, काष्ठा radeon_ib *ib,
		       काष्ठा radeon_ib *स्थिर_ib, bool hdp_flush);
पूर्णांक radeon_ib_pool_init(काष्ठा radeon_device *rdev);
व्योम radeon_ib_pool_fini(काष्ठा radeon_device *rdev);
पूर्णांक radeon_ib_ring_tests(काष्ठा radeon_device *rdev);
/* Ring access between begin & end cannot sleep */
bool radeon_ring_supports_scratch_reg(काष्ठा radeon_device *rdev,
				      काष्ठा radeon_ring *ring);
व्योम radeon_ring_मुक्त_size(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *cp);
पूर्णांक radeon_ring_alloc(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *cp, अचिन्हित ndw);
पूर्णांक radeon_ring_lock(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *cp, अचिन्हित ndw);
व्योम radeon_ring_commit(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *cp,
			bool hdp_flush);
व्योम radeon_ring_unlock_commit(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *cp,
			       bool hdp_flush);
व्योम radeon_ring_unकरो(काष्ठा radeon_ring *ring);
व्योम radeon_ring_unlock_unकरो(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *cp);
पूर्णांक radeon_ring_test(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *cp);
व्योम radeon_ring_lockup_update(काष्ठा radeon_device *rdev,
			       काष्ठा radeon_ring *ring);
bool radeon_ring_test_lockup(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring);
अचिन्हित radeon_ring_backup(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring,
			    uपूर्णांक32_t **data);
पूर्णांक radeon_ring_restore(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring,
			अचिन्हित size, uपूर्णांक32_t *data);
पूर्णांक radeon_ring_init(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *cp, अचिन्हित ring_size,
		     अचिन्हित rptr_offs, u32 nop);
व्योम radeon_ring_fini(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *cp);


/* r600 async dma */
व्योम r600_dma_stop(काष्ठा radeon_device *rdev);
पूर्णांक r600_dma_resume(काष्ठा radeon_device *rdev);
व्योम r600_dma_fini(काष्ठा radeon_device *rdev);

व्योम cayman_dma_stop(काष्ठा radeon_device *rdev);
पूर्णांक cayman_dma_resume(काष्ठा radeon_device *rdev);
व्योम cayman_dma_fini(काष्ठा radeon_device *rdev);

/*
 * CS.
 */
काष्ठा radeon_cs_chunk अणु
	uपूर्णांक32_t		length_dw;
	uपूर्णांक32_t		*kdata;
	व्योम __user		*user_ptr;
पूर्ण;

काष्ठा radeon_cs_parser अणु
	काष्ठा device		*dev;
	काष्ठा radeon_device	*rdev;
	काष्ठा drm_file		*filp;
	/* chunks */
	अचिन्हित		nchunks;
	काष्ठा radeon_cs_chunk	*chunks;
	uपूर्णांक64_t		*chunks_array;
	/* IB */
	अचिन्हित		idx;
	/* relocations */
	अचिन्हित		nrelocs;
	काष्ठा radeon_bo_list	*relocs;
	काष्ठा radeon_bo_list	*vm_bos;
	काष्ठा list_head	validated;
	अचिन्हित		dma_reloc_idx;
	/* indices of various chunks */
	काष्ठा radeon_cs_chunk  *chunk_ib;
	काष्ठा radeon_cs_chunk  *chunk_relocs;
	काष्ठा radeon_cs_chunk  *chunk_flags;
	काष्ठा radeon_cs_chunk  *chunk_स्थिर_ib;
	काष्ठा radeon_ib	ib;
	काष्ठा radeon_ib	स्थिर_ib;
	व्योम			*track;
	अचिन्हित		family;
	पूर्णांक			parser_error;
	u32			cs_flags;
	u32			ring;
	s32			priority;
	काष्ठा ww_acquire_ctx	ticket;
पूर्ण;

अटल अंतरभूत u32 radeon_get_ib_value(काष्ठा radeon_cs_parser *p, पूर्णांक idx)
अणु
	काष्ठा radeon_cs_chunk *ibc = p->chunk_ib;

	अगर (ibc->kdata)
		वापस ibc->kdata[idx];
	वापस p->ib.ptr[idx];
पूर्ण


काष्ठा radeon_cs_packet अणु
	अचिन्हित	idx;
	अचिन्हित	type;
	अचिन्हित	reg;
	अचिन्हित	opcode;
	पूर्णांक		count;
	अचिन्हित	one_reg_wr;
पूर्ण;

प्रकार पूर्णांक (*radeon_packet0_check_t)(काष्ठा radeon_cs_parser *p,
				      काष्ठा radeon_cs_packet *pkt,
				      अचिन्हित idx, अचिन्हित reg);

/*
 * AGP
 */
पूर्णांक radeon_agp_init(काष्ठा radeon_device *rdev);
व्योम radeon_agp_resume(काष्ठा radeon_device *rdev);
व्योम radeon_agp_suspend(काष्ठा radeon_device *rdev);
व्योम radeon_agp_fini(काष्ठा radeon_device *rdev);


/*
 * Writeback
 */
काष्ठा radeon_wb अणु
	काष्ठा radeon_bo	*wb_obj;
	अस्थिर uपूर्णांक32_t	*wb;
	uपूर्णांक64_t		gpu_addr;
	bool                    enabled;
	bool                    use_event;
पूर्ण;

#घोषणा RADEON_WB_SCRATCH_OFFSET 0
#घोषणा RADEON_WB_RING0_NEXT_RPTR 256
#घोषणा RADEON_WB_CP_RPTR_OFFSET 1024
#घोषणा RADEON_WB_CP1_RPTR_OFFSET 1280
#घोषणा RADEON_WB_CP2_RPTR_OFFSET 1536
#घोषणा R600_WB_DMA_RPTR_OFFSET   1792
#घोषणा R600_WB_IH_WPTR_OFFSET   2048
#घोषणा CAYMAN_WB_DMA1_RPTR_OFFSET   2304
#घोषणा R600_WB_EVENT_OFFSET     3072
#घोषणा CIK_WB_CP1_WPTR_OFFSET     3328
#घोषणा CIK_WB_CP2_WPTR_OFFSET     3584
#घोषणा R600_WB_DMA_RING_TEST_OFFSET 3588
#घोषणा CAYMAN_WB_DMA1_RING_TEST_OFFSET 3592

/**
 * काष्ठा radeon_pm - घातer management datas
 * @max_bandwidth:      maximum bandwidth the gpu has (MByte/s)
 * @igp_sideport_mclk:  sideport memory घड़ी Mhz (rs690,rs740,rs780,rs880)
 * @igp_प्रणाली_mclk:    प्रणाली घड़ी Mhz (rs690,rs740,rs780,rs880)
 * @igp_ht_link_clk:    ht link घड़ी Mhz (rs690,rs740,rs780,rs880)
 * @igp_ht_link_width:  ht link width in bits (rs690,rs740,rs780,rs880)
 * @k8_bandwidth:       k8 bandwidth the gpu has (MByte/s) (IGP)
 * @sideport_bandwidth: sideport bandwidth the gpu has (MByte/s) (IGP)
 * @ht_bandwidth:       ht bandwidth the gpu has (MByte/s) (IGP)
 * @core_bandwidth:     core GPU bandwidth the gpu has (MByte/s) (IGP)
 * @sclk:          	GPU घड़ी Mhz (core bandwidth depends of this घड़ी)
 * @needed_bandwidth:   current bandwidth needs
 *
 * It keeps track of various data needed to take घातermanagement decision.
 * Bandwidth need is used to determine minimun घड़ी of the GPU and memory.
 * Equation between gpu/memory घड़ी and available bandwidth is hw dependent
 * (type of memory, bus size, efficiency, ...)
 */

क्रमागत radeon_pm_method अणु
	PM_METHOD_PROखाता,
	PM_METHOD_DYNPM,
	PM_METHOD_DPM,
पूर्ण;

क्रमागत radeon_dynpm_state अणु
	DYNPM_STATE_DISABLED,
	DYNPM_STATE_MINIMUM,
	DYNPM_STATE_PAUSED,
	DYNPM_STATE_ACTIVE,
	DYNPM_STATE_SUSPENDED,
पूर्ण;
क्रमागत radeon_dynpm_action अणु
	DYNPM_ACTION_NONE,
	DYNPM_ACTION_MINIMUM,
	DYNPM_ACTION_DOWNCLOCK,
	DYNPM_ACTION_UPCLOCK,
	DYNPM_ACTION_DEFAULT
पूर्ण;

क्रमागत radeon_voltage_type अणु
	VOLTAGE_NONE = 0,
	VOLTAGE_GPIO,
	VOLTAGE_VDDC,
	VOLTAGE_SW
पूर्ण;

क्रमागत radeon_pm_state_type अणु
	/* not used क्रम dpm */
	POWER_STATE_TYPE_DEFAULT,
	POWER_STATE_TYPE_POWERSAVE,
	/* user selectable states */
	POWER_STATE_TYPE_BATTERY,
	POWER_STATE_TYPE_BALANCED,
	POWER_STATE_TYPE_PERFORMANCE,
	/* पूर्णांकernal states */
	POWER_STATE_TYPE_INTERNAL_UVD,
	POWER_STATE_TYPE_INTERNAL_UVD_SD,
	POWER_STATE_TYPE_INTERNAL_UVD_HD,
	POWER_STATE_TYPE_INTERNAL_UVD_HD2,
	POWER_STATE_TYPE_INTERNAL_UVD_MVC,
	POWER_STATE_TYPE_INTERNAL_BOOT,
	POWER_STATE_TYPE_INTERNAL_THERMAL,
	POWER_STATE_TYPE_INTERNAL_ACPI,
	POWER_STATE_TYPE_INTERNAL_ULV,
	POWER_STATE_TYPE_INTERNAL_3DPERF,
पूर्ण;

क्रमागत radeon_pm_profile_type अणु
	PM_PROखाता_DEFAULT,
	PM_PROखाता_AUTO,
	PM_PROखाता_LOW,
	PM_PROखाता_MID,
	PM_PROखाता_HIGH,
पूर्ण;

#घोषणा PM_PROखाता_DEFAULT_IDX 0
#घोषणा PM_PROखाता_LOW_SH_IDX  1
#घोषणा PM_PROखाता_MID_SH_IDX  2
#घोषणा PM_PROखाता_HIGH_SH_IDX 3
#घोषणा PM_PROखाता_LOW_MH_IDX  4
#घोषणा PM_PROखाता_MID_MH_IDX  5
#घोषणा PM_PROखाता_HIGH_MH_IDX 6
#घोषणा PM_PROखाता_MAX         7

काष्ठा radeon_pm_profile अणु
	पूर्णांक dpms_off_ps_idx;
	पूर्णांक dpms_on_ps_idx;
	पूर्णांक dpms_off_cm_idx;
	पूर्णांक dpms_on_cm_idx;
पूर्ण;

क्रमागत radeon_पूर्णांक_thermal_type अणु
	THERMAL_TYPE_NONE,
	THERMAL_TYPE_EXTERNAL,
	THERMAL_TYPE_EXTERNAL_GPIO,
	THERMAL_TYPE_RV6XX,
	THERMAL_TYPE_RV770,
	THERMAL_TYPE_ADT7473_WITH_INTERNAL,
	THERMAL_TYPE_EVERGREEN,
	THERMAL_TYPE_SUMO,
	THERMAL_TYPE_NI,
	THERMAL_TYPE_SI,
	THERMAL_TYPE_EMC2103_WITH_INTERNAL,
	THERMAL_TYPE_CI,
	THERMAL_TYPE_KV,
पूर्ण;

काष्ठा radeon_voltage अणु
	क्रमागत radeon_voltage_type type;
	/* gpio voltage */
	काष्ठा radeon_gpio_rec gpio;
	u32 delay; /* delay in usec from voltage drop to sclk change */
	bool active_high; /* voltage drop is active when bit is high */
	/* VDDC voltage */
	u8 vddc_id; /* index पूर्णांकo vddc voltage table */
	u8 vddci_id; /* index पूर्णांकo vddci voltage table */
	bool vddci_enabled;
	/* r6xx+ sw */
	u16 voltage;
	/* evergreen+ vddci */
	u16 vddci;
पूर्ण;

/* घड़ी mode flags */
#घोषणा RADEON_PM_MODE_NO_DISPLAY          (1 << 0)

काष्ठा radeon_pm_घड़ी_info अणु
	/* memory घड़ी */
	u32 mclk;
	/* engine घड़ी */
	u32 sclk;
	/* voltage info */
	काष्ठा radeon_voltage voltage;
	/* standardized घड़ी flags */
	u32 flags;
पूर्ण;

/* state flags */
#घोषणा RADEON_PM_STATE_SINGLE_DISPLAY_ONLY (1 << 0)

काष्ठा radeon_घातer_state अणु
	क्रमागत radeon_pm_state_type type;
	काष्ठा radeon_pm_घड़ी_info *घड़ी_info;
	/* number of valid घड़ी modes in this घातer state */
	पूर्णांक num_घड़ी_modes;
	काष्ठा radeon_pm_घड़ी_info *शेष_घड़ी_mode;
	/* standardized state flags */
	u32 flags;
	u32 misc; /* vbios specअगरic flags */
	u32 misc2; /* vbios specअगरic flags */
	पूर्णांक pcie_lanes; /* pcie lanes */
पूर्ण;

/*
 * Some modes are overघड़ीed by very low value, accept them
 */
#घोषणा RADEON_MODE_OVERCLOCK_MARGIN 500 /* 5 MHz */

क्रमागत radeon_dpm_स्वतः_throttle_src अणु
	RADEON_DPM_AUTO_THROTTLE_SRC_THERMAL,
	RADEON_DPM_AUTO_THROTTLE_SRC_EXTERNAL
पूर्ण;

क्रमागत radeon_dpm_event_src अणु
	RADEON_DPM_EVENT_SRC_ANALOG = 0,
	RADEON_DPM_EVENT_SRC_EXTERNAL = 1,
	RADEON_DPM_EVENT_SRC_DIGITAL = 2,
	RADEON_DPM_EVENT_SRC_ANALOG_OR_EXTERNAL = 3,
	RADEON_DPM_EVENT_SRC_DIGIAL_OR_EXTERNAL = 4
पूर्ण;

#घोषणा RADEON_MAX_VCE_LEVELS 6

क्रमागत radeon_vce_level अणु
	RADEON_VCE_LEVEL_AC_ALL = 0,     /* AC, All हालs */
	RADEON_VCE_LEVEL_DC_EE = 1,      /* DC, entropy encoding */
	RADEON_VCE_LEVEL_DC_LL_LOW = 2,  /* DC, low latency queue, res <= 720 */
	RADEON_VCE_LEVEL_DC_LL_HIGH = 3, /* DC, low latency queue, 1080 >= res > 720 */
	RADEON_VCE_LEVEL_DC_GP_LOW = 4,  /* DC, general purpose queue, res <= 720 */
	RADEON_VCE_LEVEL_DC_GP_HIGH = 5, /* DC, general purpose queue, 1080 >= res > 720 */
पूर्ण;

काष्ठा radeon_ps अणु
	u32 caps; /* vbios flags */
	u32 class; /* vbios flags */
	u32 class2; /* vbios flags */
	/* UVD घड़ीs */
	u32 vclk;
	u32 dclk;
	/* VCE घड़ीs */
	u32 evclk;
	u32 ecclk;
	bool vce_active;
	क्रमागत radeon_vce_level vce_level;
	/* asic priv */
	व्योम *ps_priv;
पूर्ण;

काष्ठा radeon_dpm_thermal अणु
	/* thermal पूर्णांकerrupt work */
	काष्ठा work_काष्ठा work;
	/* low temperature threshold */
	पूर्णांक                min_temp;
	/* high temperature threshold */
	पूर्णांक                max_temp;
	/* was पूर्णांकerrupt low to high or high to low */
	bool               high_to_low;
पूर्ण;

क्रमागत radeon_clk_action
अणु
	RADEON_SCLK_UP = 1,
	RADEON_SCLK_DOWN
पूर्ण;

काष्ठा radeon_blacklist_घड़ीs
अणु
	u32 sclk;
	u32 mclk;
	क्रमागत radeon_clk_action action;
पूर्ण;

काष्ठा radeon_घड़ी_and_voltage_limits अणु
	u32 sclk;
	u32 mclk;
	u16 vddc;
	u16 vddci;
पूर्ण;

काष्ठा radeon_घड़ी_array अणु
	u32 count;
	u32 *values;
पूर्ण;

काष्ठा radeon_घड़ी_voltage_dependency_entry अणु
	u32 clk;
	u16 v;
पूर्ण;

काष्ठा radeon_घड़ी_voltage_dependency_table अणु
	u32 count;
	काष्ठा radeon_घड़ी_voltage_dependency_entry *entries;
पूर्ण;

जोड़ radeon_cac_leakage_entry अणु
	काष्ठा अणु
		u16 vddc;
		u32 leakage;
	पूर्ण;
	काष्ठा अणु
		u16 vddc1;
		u16 vddc2;
		u16 vddc3;
	पूर्ण;
पूर्ण;

काष्ठा radeon_cac_leakage_table अणु
	u32 count;
	जोड़ radeon_cac_leakage_entry *entries;
पूर्ण;

काष्ठा radeon_phase_shedding_limits_entry अणु
	u16 voltage;
	u32 sclk;
	u32 mclk;
पूर्ण;

काष्ठा radeon_phase_shedding_limits_table अणु
	u32 count;
	काष्ठा radeon_phase_shedding_limits_entry *entries;
पूर्ण;

काष्ठा radeon_uvd_घड़ी_voltage_dependency_entry अणु
	u32 vclk;
	u32 dclk;
	u16 v;
पूर्ण;

काष्ठा radeon_uvd_घड़ी_voltage_dependency_table अणु
	u8 count;
	काष्ठा radeon_uvd_घड़ी_voltage_dependency_entry *entries;
पूर्ण;

काष्ठा radeon_vce_घड़ी_voltage_dependency_entry अणु
	u32 ecclk;
	u32 evclk;
	u16 v;
पूर्ण;

काष्ठा radeon_vce_घड़ी_voltage_dependency_table अणु
	u8 count;
	काष्ठा radeon_vce_घड़ी_voltage_dependency_entry *entries;
पूर्ण;

काष्ठा radeon_ppm_table अणु
	u8 ppm_design;
	u16 cpu_core_number;
	u32 platक्रमm_tdp;
	u32 small_ac_platक्रमm_tdp;
	u32 platक्रमm_tdc;
	u32 small_ac_platक्रमm_tdc;
	u32 apu_tdp;
	u32 dgpu_tdp;
	u32 dgpu_ulv_घातer;
	u32 tj_max;
पूर्ण;

काष्ठा radeon_cac_tdp_table अणु
	u16 tdp;
	u16 configurable_tdp;
	u16 tdc;
	u16 battery_घातer_limit;
	u16 small_घातer_limit;
	u16 low_cac_leakage;
	u16 high_cac_leakage;
	u16 maximum_घातer_delivery_limit;
पूर्ण;

काष्ठा radeon_dpm_dynamic_state अणु
	काष्ठा radeon_घड़ी_voltage_dependency_table vddc_dependency_on_sclk;
	काष्ठा radeon_घड़ी_voltage_dependency_table vddci_dependency_on_mclk;
	काष्ठा radeon_घड़ी_voltage_dependency_table vddc_dependency_on_mclk;
	काष्ठा radeon_घड़ी_voltage_dependency_table mvdd_dependency_on_mclk;
	काष्ठा radeon_घड़ी_voltage_dependency_table vddc_dependency_on_dispclk;
	काष्ठा radeon_uvd_घड़ी_voltage_dependency_table uvd_घड़ी_voltage_dependency_table;
	काष्ठा radeon_vce_घड़ी_voltage_dependency_table vce_घड़ी_voltage_dependency_table;
	काष्ठा radeon_घड़ी_voltage_dependency_table samu_घड़ी_voltage_dependency_table;
	काष्ठा radeon_घड़ी_voltage_dependency_table acp_घड़ी_voltage_dependency_table;
	काष्ठा radeon_घड़ी_array valid_sclk_values;
	काष्ठा radeon_घड़ी_array valid_mclk_values;
	काष्ठा radeon_घड़ी_and_voltage_limits max_घड़ी_voltage_on_dc;
	काष्ठा radeon_घड़ी_and_voltage_limits max_घड़ी_voltage_on_ac;
	u32 mclk_sclk_ratio;
	u32 sclk_mclk_delta;
	u16 vddc_vddci_delta;
	u16 min_vddc_क्रम_pcie_gen2;
	काष्ठा radeon_cac_leakage_table cac_leakage_table;
	काष्ठा radeon_phase_shedding_limits_table phase_shedding_limits_table;
	काष्ठा radeon_ppm_table *ppm_table;
	काष्ठा radeon_cac_tdp_table *cac_tdp_table;
पूर्ण;

काष्ठा radeon_dpm_fan अणु
	u16 t_min;
	u16 t_med;
	u16 t_high;
	u16 pwm_min;
	u16 pwm_med;
	u16 pwm_high;
	u8 t_hyst;
	u32 cycle_delay;
	u16 t_max;
	u8 control_mode;
	u16 शेष_max_fan_pwm;
	u16 शेष_fan_output_sensitivity;
	u16 fan_output_sensitivity;
	bool ucode_fan_control;
पूर्ण;

क्रमागत radeon_pcie_gen अणु
	RADEON_PCIE_GEN1 = 0,
	RADEON_PCIE_GEN2 = 1,
	RADEON_PCIE_GEN3 = 2,
	RADEON_PCIE_GEN_INVALID = 0xffff
पूर्ण;

क्रमागत radeon_dpm_क्रमced_level अणु
	RADEON_DPM_FORCED_LEVEL_AUTO = 0,
	RADEON_DPM_FORCED_LEVEL_LOW = 1,
	RADEON_DPM_FORCED_LEVEL_HIGH = 2,
पूर्ण;

काष्ठा radeon_vce_state अणु
	/* vce घड़ीs */
	u32 evclk;
	u32 ecclk;
	/* gpu घड़ीs */
	u32 sclk;
	u32 mclk;
	u8 clk_idx;
	u8 pstate;
पूर्ण;

काष्ठा radeon_dpm अणु
	काष्ठा radeon_ps        *ps;
	/* number of valid घातer states */
	पूर्णांक                     num_ps;
	/* current घातer state that is active */
	काष्ठा radeon_ps        *current_ps;
	/* requested घातer state */
	काष्ठा radeon_ps        *requested_ps;
	/* boot up घातer state */
	काष्ठा radeon_ps        *boot_ps;
	/* शेष uvd घातer state */
	काष्ठा radeon_ps        *uvd_ps;
	/* vce requirements */
	काष्ठा radeon_vce_state vce_states[RADEON_MAX_VCE_LEVELS];
	क्रमागत radeon_vce_level vce_level;
	क्रमागत radeon_pm_state_type state;
	क्रमागत radeon_pm_state_type user_state;
	u32                     platक्रमm_caps;
	u32                     voltage_response_समय;
	u32                     backbias_response_समय;
	व्योम                    *priv;
	u32			new_active_crtcs;
	पूर्णांक			new_active_crtc_count;
	पूर्णांक			high_pixelघड़ी_count;
	u32			current_active_crtcs;
	पूर्णांक			current_active_crtc_count;
	bool single_display;
	काष्ठा radeon_dpm_dynamic_state dyn_state;
	काष्ठा radeon_dpm_fan fan;
	u32 tdp_limit;
	u32 near_tdp_limit;
	u32 near_tdp_limit_adjusted;
	u32 sq_ramping_threshold;
	u32 cac_leakage;
	u16 tdp_od_limit;
	u32 tdp_adjusपंचांगent;
	u16 load_line_slope;
	bool घातer_control;
	bool ac_घातer;
	/* special states active */
	bool                    thermal_active;
	bool                    uvd_active;
	bool                    vce_active;
	/* thermal handling */
	काष्ठा radeon_dpm_thermal thermal;
	/* क्रमced levels */
	क्रमागत radeon_dpm_क्रमced_level क्रमced_level;
	/* track UVD streams */
	अचिन्हित sd;
	अचिन्हित hd;
पूर्ण;

व्योम radeon_dpm_enable_uvd(काष्ठा radeon_device *rdev, bool enable);
व्योम radeon_dpm_enable_vce(काष्ठा radeon_device *rdev, bool enable);

काष्ठा radeon_pm अणु
	काष्ठा mutex		mutex;
	/* ग_लिखो locked जबतक reprogramming mclk */
	काष्ठा rw_semaphore	mclk_lock;
	u32			active_crtcs;
	पूर्णांक			active_crtc_count;
	पूर्णांक			req_vblank;
	bool			vblank_sync;
	fixed20_12		max_bandwidth;
	fixed20_12		igp_sideport_mclk;
	fixed20_12		igp_प्रणाली_mclk;
	fixed20_12		igp_ht_link_clk;
	fixed20_12		igp_ht_link_width;
	fixed20_12		k8_bandwidth;
	fixed20_12		sideport_bandwidth;
	fixed20_12		ht_bandwidth;
	fixed20_12		core_bandwidth;
	fixed20_12		sclk;
	fixed20_12		mclk;
	fixed20_12		needed_bandwidth;
	काष्ठा radeon_घातer_state *घातer_state;
	/* number of valid घातer states */
	पूर्णांक                     num_घातer_states;
	पूर्णांक                     current_घातer_state_index;
	पूर्णांक                     current_घड़ी_mode_index;
	पूर्णांक                     requested_घातer_state_index;
	पूर्णांक                     requested_घड़ी_mode_index;
	पूर्णांक                     शेष_घातer_state_index;
	u32                     current_sclk;
	u32                     current_mclk;
	u16                     current_vddc;
	u16                     current_vddci;
	u32                     शेष_sclk;
	u32                     शेष_mclk;
	u16                     शेष_vddc;
	u16                     शेष_vddci;
	काष्ठा radeon_i2c_chan *i2c_bus;
	/* selected pm method */
	क्रमागत radeon_pm_method     pm_method;
	/* dynpm घातer management */
	काष्ठा delayed_work	dynpm_idle_work;
	क्रमागत radeon_dynpm_state	dynpm_state;
	क्रमागत radeon_dynpm_action	dynpm_planned_action;
	अचिन्हित दीर्घ		dynpm_action_समयout;
	bool                    dynpm_can_upघड़ी;
	bool                    dynpm_can_करोwnघड़ी;
	/* profile-based घातer management */
	क्रमागत radeon_pm_profile_type profile;
	पूर्णांक                     profile_index;
	काष्ठा radeon_pm_profile profiles[PM_PROखाता_MAX];
	/* पूर्णांकernal thermal controller on rv6xx+ */
	क्रमागत radeon_पूर्णांक_thermal_type पूर्णांक_thermal_type;
	काष्ठा device	        *पूर्णांक_hwmon_dev;
	/* fan control parameters */
	bool                    no_fan;
	u8                      fan_pulses_per_revolution;
	u8                      fan_min_rpm;
	u8                      fan_max_rpm;
	/* dpm */
	bool                    dpm_enabled;
	bool                    sysfs_initialized;
	काष्ठा radeon_dpm       dpm;
पूर्ण;

#घोषणा RADEON_PCIE_SPEED_25 1
#घोषणा RADEON_PCIE_SPEED_50 2
#घोषणा RADEON_PCIE_SPEED_80 4

पूर्णांक radeon_pm_get_type_index(काष्ठा radeon_device *rdev,
			     क्रमागत radeon_pm_state_type ps_type,
			     पूर्णांक instance);
/*
 * UVD
 */
#घोषणा RADEON_DEFAULT_UVD_HANDLES	10
#घोषणा RADEON_MAX_UVD_HANDLES		30
#घोषणा RADEON_UVD_STACK_SIZE		(200*1024)
#घोषणा RADEON_UVD_HEAP_SIZE		(256*1024)
#घोषणा RADEON_UVD_SESSION_SIZE		(50*1024)

काष्ठा radeon_uvd अणु
	bool			fw_header_present;
	काष्ठा radeon_bo	*vcpu_bo;
	व्योम			*cpu_addr;
	uपूर्णांक64_t		gpu_addr;
	अचिन्हित		max_handles;
	atomic_t		handles[RADEON_MAX_UVD_HANDLES];
	काष्ठा drm_file		*filp[RADEON_MAX_UVD_HANDLES];
	अचिन्हित		img_size[RADEON_MAX_UVD_HANDLES];
	काष्ठा delayed_work	idle_work;
पूर्ण;

पूर्णांक radeon_uvd_init(काष्ठा radeon_device *rdev);
व्योम radeon_uvd_fini(काष्ठा radeon_device *rdev);
पूर्णांक radeon_uvd_suspend(काष्ठा radeon_device *rdev);
पूर्णांक radeon_uvd_resume(काष्ठा radeon_device *rdev);
पूर्णांक radeon_uvd_get_create_msg(काष्ठा radeon_device *rdev, पूर्णांक ring,
			      uपूर्णांक32_t handle, काष्ठा radeon_fence **fence);
पूर्णांक radeon_uvd_get_destroy_msg(काष्ठा radeon_device *rdev, पूर्णांक ring,
			       uपूर्णांक32_t handle, काष्ठा radeon_fence **fence);
व्योम radeon_uvd_क्रमce_पूर्णांकo_uvd_segment(काष्ठा radeon_bo *rbo,
				       uपूर्णांक32_t allowed_करोमुख्यs);
व्योम radeon_uvd_मुक्त_handles(काष्ठा radeon_device *rdev,
			     काष्ठा drm_file *filp);
पूर्णांक radeon_uvd_cs_parse(काष्ठा radeon_cs_parser *parser);
व्योम radeon_uvd_note_usage(काष्ठा radeon_device *rdev);
पूर्णांक radeon_uvd_calc_upll_भागiders(काष्ठा radeon_device *rdev,
				  अचिन्हित vclk, अचिन्हित dclk,
				  अचिन्हित vco_min, अचिन्हित vco_max,
				  अचिन्हित fb_factor, अचिन्हित fb_mask,
				  अचिन्हित pd_min, अचिन्हित pd_max,
				  अचिन्हित pd_even,
				  अचिन्हित *optimal_fb_भाग,
				  अचिन्हित *optimal_vclk_भाग,
				  अचिन्हित *optimal_dclk_भाग);
पूर्णांक radeon_uvd_send_upll_ctlreq(काष्ठा radeon_device *rdev,
                                अचिन्हित cg_upll_func_cntl);

/*
 * VCE
 */
#घोषणा RADEON_MAX_VCE_HANDLES	16

काष्ठा radeon_vce अणु
	काष्ठा radeon_bo	*vcpu_bo;
	uपूर्णांक64_t		gpu_addr;
	अचिन्हित		fw_version;
	अचिन्हित		fb_version;
	atomic_t		handles[RADEON_MAX_VCE_HANDLES];
	काष्ठा drm_file		*filp[RADEON_MAX_VCE_HANDLES];
	अचिन्हित		img_size[RADEON_MAX_VCE_HANDLES];
	काष्ठा delayed_work	idle_work;
	uपूर्णांक32_t		keyselect;
पूर्ण;

पूर्णांक radeon_vce_init(काष्ठा radeon_device *rdev);
व्योम radeon_vce_fini(काष्ठा radeon_device *rdev);
पूर्णांक radeon_vce_suspend(काष्ठा radeon_device *rdev);
पूर्णांक radeon_vce_resume(काष्ठा radeon_device *rdev);
पूर्णांक radeon_vce_get_create_msg(काष्ठा radeon_device *rdev, पूर्णांक ring,
			      uपूर्णांक32_t handle, काष्ठा radeon_fence **fence);
पूर्णांक radeon_vce_get_destroy_msg(काष्ठा radeon_device *rdev, पूर्णांक ring,
			       uपूर्णांक32_t handle, काष्ठा radeon_fence **fence);
व्योम radeon_vce_मुक्त_handles(काष्ठा radeon_device *rdev, काष्ठा drm_file *filp);
व्योम radeon_vce_note_usage(काष्ठा radeon_device *rdev);
पूर्णांक radeon_vce_cs_reloc(काष्ठा radeon_cs_parser *p, पूर्णांक lo, पूर्णांक hi, अचिन्हित size);
पूर्णांक radeon_vce_cs_parse(काष्ठा radeon_cs_parser *p);
bool radeon_vce_semaphore_emit(काष्ठा radeon_device *rdev,
			       काष्ठा radeon_ring *ring,
			       काष्ठा radeon_semaphore *semaphore,
			       bool emit_रुको);
व्योम radeon_vce_ib_execute(काष्ठा radeon_device *rdev, काष्ठा radeon_ib *ib);
व्योम radeon_vce_fence_emit(काष्ठा radeon_device *rdev,
			   काष्ठा radeon_fence *fence);
पूर्णांक radeon_vce_ring_test(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring);
पूर्णांक radeon_vce_ib_test(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring);

काष्ठा r600_audio_pin अणु
	पूर्णांक			channels;
	पूर्णांक			rate;
	पूर्णांक			bits_per_sample;
	u8			status_bits;
	u8			category_code;
	u32			offset;
	bool			connected;
	u32			id;
पूर्ण;

काष्ठा r600_audio अणु
	bool enabled;
	काष्ठा r600_audio_pin pin[RADEON_MAX_AFMT_BLOCKS];
	पूर्णांक num_pins;
	काष्ठा radeon_audio_funcs *hdmi_funcs;
	काष्ठा radeon_audio_funcs *dp_funcs;
	काष्ठा radeon_audio_basic_funcs *funcs;
पूर्ण;

/*
 * Benchmarking
 */
व्योम radeon_benchmark(काष्ठा radeon_device *rdev, पूर्णांक test_number);


/*
 * Testing
 */
व्योम radeon_test_moves(काष्ठा radeon_device *rdev);
व्योम radeon_test_ring_sync(काष्ठा radeon_device *rdev,
			   काष्ठा radeon_ring *cpA,
			   काष्ठा radeon_ring *cpB);
व्योम radeon_test_syncing(काष्ठा radeon_device *rdev);

/*
 * MMU Notअगरier
 */
#अगर defined(CONFIG_MMU_NOTIFIER)
पूर्णांक radeon_mn_रेजिस्टर(काष्ठा radeon_bo *bo, अचिन्हित दीर्घ addr);
व्योम radeon_mn_unरेजिस्टर(काष्ठा radeon_bo *bo);
#अन्यथा
अटल अंतरभूत पूर्णांक radeon_mn_रेजिस्टर(काष्ठा radeon_bo *bo, अचिन्हित दीर्घ addr)
अणु
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत व्योम radeon_mn_unरेजिस्टर(काष्ठा radeon_bo *bo) अणुपूर्ण
#पूर्ण_अगर

/*
 * Debugfs
 */
व्योम radeon_debugfs_fence_init(काष्ठा radeon_device *rdev);
व्योम radeon_gem_debugfs_init(काष्ठा radeon_device *rdev);

/*
 * ASIC ring specअगरic functions.
 */
काष्ठा radeon_asic_ring अणु
	/* ring पढ़ो/ग_लिखो ptr handling */
	u32 (*get_rptr)(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring);
	u32 (*get_wptr)(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring);
	व्योम (*set_wptr)(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring);

	/* validating and patching of IBs */
	पूर्णांक (*ib_parse)(काष्ठा radeon_device *rdev, काष्ठा radeon_ib *ib);
	पूर्णांक (*cs_parse)(काष्ठा radeon_cs_parser *p);

	/* command emmit functions */
	व्योम (*ib_execute)(काष्ठा radeon_device *rdev, काष्ठा radeon_ib *ib);
	व्योम (*emit_fence)(काष्ठा radeon_device *rdev, काष्ठा radeon_fence *fence);
	व्योम (*hdp_flush)(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring);
	bool (*emit_semaphore)(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *cp,
			       काष्ठा radeon_semaphore *semaphore, bool emit_रुको);
	व्योम (*vm_flush)(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring,
			 अचिन्हित vm_id, uपूर्णांक64_t pd_addr);

	/* testing functions */
	पूर्णांक (*ring_test)(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *cp);
	पूर्णांक (*ib_test)(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *cp);
	bool (*is_lockup)(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *cp);

	/* deprecated */
	व्योम (*ring_start)(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *cp);
पूर्ण;

/*
 * ASIC specअगरic functions.
 */
काष्ठा radeon_asic अणु
	पूर्णांक (*init)(काष्ठा radeon_device *rdev);
	व्योम (*fini)(काष्ठा radeon_device *rdev);
	पूर्णांक (*resume)(काष्ठा radeon_device *rdev);
	पूर्णांक (*suspend)(काष्ठा radeon_device *rdev);
	व्योम (*vga_set_state)(काष्ठा radeon_device *rdev, bool state);
	पूर्णांक (*asic_reset)(काष्ठा radeon_device *rdev, bool hard);
	/* Flush the HDP cache via MMIO */
	व्योम (*mmio_hdp_flush)(काष्ठा radeon_device *rdev);
	/* check अगर 3D engine is idle */
	bool (*gui_idle)(काष्ठा radeon_device *rdev);
	/* रुको क्रम mc_idle */
	पूर्णांक (*mc_रुको_क्रम_idle)(काष्ठा radeon_device *rdev);
	/* get the reference घड़ी */
	u32 (*get_xclk)(काष्ठा radeon_device *rdev);
	/* get the gpu घड़ी counter */
	uपूर्णांक64_t (*get_gpu_घड़ी_counter)(काष्ठा radeon_device *rdev);
	/* get रेजिस्टर क्रम info ioctl */
	पूर्णांक (*get_allowed_info_रेजिस्टर)(काष्ठा radeon_device *rdev, u32 reg, u32 *val);
	/* gart */
	काष्ठा अणु
		व्योम (*tlb_flush)(काष्ठा radeon_device *rdev);
		uपूर्णांक64_t (*get_page_entry)(uपूर्णांक64_t addr, uपूर्णांक32_t flags);
		व्योम (*set_page)(काष्ठा radeon_device *rdev, अचिन्हित i,
				 uपूर्णांक64_t entry);
	पूर्ण gart;
	काष्ठा अणु
		पूर्णांक (*init)(काष्ठा radeon_device *rdev);
		व्योम (*fini)(काष्ठा radeon_device *rdev);
		व्योम (*copy_pages)(काष्ठा radeon_device *rdev,
				   काष्ठा radeon_ib *ib,
				   uपूर्णांक64_t pe, uपूर्णांक64_t src,
				   अचिन्हित count);
		व्योम (*ग_लिखो_pages)(काष्ठा radeon_device *rdev,
				    काष्ठा radeon_ib *ib,
				    uपूर्णांक64_t pe,
				    uपूर्णांक64_t addr, अचिन्हित count,
				    uपूर्णांक32_t incr, uपूर्णांक32_t flags);
		व्योम (*set_pages)(काष्ठा radeon_device *rdev,
				  काष्ठा radeon_ib *ib,
				  uपूर्णांक64_t pe,
				  uपूर्णांक64_t addr, अचिन्हित count,
				  uपूर्णांक32_t incr, uपूर्णांक32_t flags);
		व्योम (*pad_ib)(काष्ठा radeon_ib *ib);
	पूर्ण vm;
	/* ring specअगरic callbacks */
	स्थिर काष्ठा radeon_asic_ring *ring[RADEON_NUM_RINGS];
	/* irqs */
	काष्ठा अणु
		पूर्णांक (*set)(काष्ठा radeon_device *rdev);
		पूर्णांक (*process)(काष्ठा radeon_device *rdev);
	पूर्ण irq;
	/* displays */
	काष्ठा अणु
		/* display watermarks */
		व्योम (*bandwidth_update)(काष्ठा radeon_device *rdev);
		/* get frame count */
		u32 (*get_vblank_counter)(काष्ठा radeon_device *rdev, पूर्णांक crtc);
		/* रुको क्रम vblank */
		व्योम (*रुको_क्रम_vblank)(काष्ठा radeon_device *rdev, पूर्णांक crtc);
		/* set backlight level */
		व्योम (*set_backlight_level)(काष्ठा radeon_encoder *radeon_encoder, u8 level);
		/* get backlight level */
		u8 (*get_backlight_level)(काष्ठा radeon_encoder *radeon_encoder);
		/* audio callbacks */
		व्योम (*hdmi_enable)(काष्ठा drm_encoder *encoder, bool enable);
		व्योम (*hdmi_seपंचांगode)(काष्ठा drm_encoder *encoder, काष्ठा drm_display_mode *mode);
	पूर्ण display;
	/* copy functions क्रम bo handling */
	काष्ठा अणु
		काष्ठा radeon_fence *(*blit)(काष्ठा radeon_device *rdev,
					     uपूर्णांक64_t src_offset,
					     uपूर्णांक64_t dst_offset,
					     अचिन्हित num_gpu_pages,
					     काष्ठा dma_resv *resv);
		u32 blit_ring_index;
		काष्ठा radeon_fence *(*dma)(काष्ठा radeon_device *rdev,
					    uपूर्णांक64_t src_offset,
					    uपूर्णांक64_t dst_offset,
					    अचिन्हित num_gpu_pages,
					    काष्ठा dma_resv *resv);
		u32 dma_ring_index;
		/* method used क्रम bo copy */
		काष्ठा radeon_fence *(*copy)(काष्ठा radeon_device *rdev,
					     uपूर्णांक64_t src_offset,
					     uपूर्णांक64_t dst_offset,
					     अचिन्हित num_gpu_pages,
					     काष्ठा dma_resv *resv);
		/* ring used क्रम bo copies */
		u32 copy_ring_index;
	पूर्ण copy;
	/* surfaces */
	काष्ठा अणु
		पूर्णांक (*set_reg)(काष्ठा radeon_device *rdev, पूर्णांक reg,
				       uपूर्णांक32_t tiling_flags, uपूर्णांक32_t pitch,
				       uपूर्णांक32_t offset, uपूर्णांक32_t obj_size);
		व्योम (*clear_reg)(काष्ठा radeon_device *rdev, पूर्णांक reg);
	पूर्ण surface;
	/* hotplug detect */
	काष्ठा अणु
		व्योम (*init)(काष्ठा radeon_device *rdev);
		व्योम (*fini)(काष्ठा radeon_device *rdev);
		bool (*sense)(काष्ठा radeon_device *rdev, क्रमागत radeon_hpd_id hpd);
		व्योम (*set_polarity)(काष्ठा radeon_device *rdev, क्रमागत radeon_hpd_id hpd);
	पूर्ण hpd;
	/* अटल घातer management */
	काष्ठा अणु
		व्योम (*misc)(काष्ठा radeon_device *rdev);
		व्योम (*prepare)(काष्ठा radeon_device *rdev);
		व्योम (*finish)(काष्ठा radeon_device *rdev);
		व्योम (*init_profile)(काष्ठा radeon_device *rdev);
		व्योम (*get_dynpm_state)(काष्ठा radeon_device *rdev);
		uपूर्णांक32_t (*get_engine_घड़ी)(काष्ठा radeon_device *rdev);
		व्योम (*set_engine_घड़ी)(काष्ठा radeon_device *rdev, uपूर्णांक32_t eng_घड़ी);
		uपूर्णांक32_t (*get_memory_घड़ी)(काष्ठा radeon_device *rdev);
		व्योम (*set_memory_घड़ी)(काष्ठा radeon_device *rdev, uपूर्णांक32_t mem_घड़ी);
		पूर्णांक (*get_pcie_lanes)(काष्ठा radeon_device *rdev);
		व्योम (*set_pcie_lanes)(काष्ठा radeon_device *rdev, पूर्णांक lanes);
		व्योम (*set_घड़ी_gating)(काष्ठा radeon_device *rdev, पूर्णांक enable);
		पूर्णांक (*set_uvd_घड़ीs)(काष्ठा radeon_device *rdev, u32 vclk, u32 dclk);
		पूर्णांक (*set_vce_घड़ीs)(काष्ठा radeon_device *rdev, u32 evclk, u32 ecclk);
		पूर्णांक (*get_temperature)(काष्ठा radeon_device *rdev);
	पूर्ण pm;
	/* dynamic घातer management */
	काष्ठा अणु
		पूर्णांक (*init)(काष्ठा radeon_device *rdev);
		व्योम (*setup_asic)(काष्ठा radeon_device *rdev);
		पूर्णांक (*enable)(काष्ठा radeon_device *rdev);
		पूर्णांक (*late_enable)(काष्ठा radeon_device *rdev);
		व्योम (*disable)(काष्ठा radeon_device *rdev);
		पूर्णांक (*pre_set_घातer_state)(काष्ठा radeon_device *rdev);
		पूर्णांक (*set_घातer_state)(काष्ठा radeon_device *rdev);
		व्योम (*post_set_घातer_state)(काष्ठा radeon_device *rdev);
		व्योम (*display_configuration_changed)(काष्ठा radeon_device *rdev);
		व्योम (*fini)(काष्ठा radeon_device *rdev);
		u32 (*get_sclk)(काष्ठा radeon_device *rdev, bool low);
		u32 (*get_mclk)(काष्ठा radeon_device *rdev, bool low);
		व्योम (*prपूर्णांक_घातer_state)(काष्ठा radeon_device *rdev, काष्ठा radeon_ps *ps);
		व्योम (*debugfs_prपूर्णांक_current_perक्रमmance_level)(काष्ठा radeon_device *rdev, काष्ठा seq_file *m);
		पूर्णांक (*क्रमce_perक्रमmance_level)(काष्ठा radeon_device *rdev, क्रमागत radeon_dpm_क्रमced_level level);
		bool (*vblank_too_लघु)(काष्ठा radeon_device *rdev);
		व्योम (*घातergate_uvd)(काष्ठा radeon_device *rdev, bool gate);
		व्योम (*enable_bapm)(काष्ठा radeon_device *rdev, bool enable);
		व्योम (*fan_ctrl_set_mode)(काष्ठा radeon_device *rdev, u32 mode);
		u32 (*fan_ctrl_get_mode)(काष्ठा radeon_device *rdev);
		पूर्णांक (*set_fan_speed_percent)(काष्ठा radeon_device *rdev, u32 speed);
		पूर्णांक (*get_fan_speed_percent)(काष्ठा radeon_device *rdev, u32 *speed);
		u32 (*get_current_sclk)(काष्ठा radeon_device *rdev);
		u32 (*get_current_mclk)(काष्ठा radeon_device *rdev);
		u16 (*get_current_vddc)(काष्ठा radeon_device *rdev);
	पूर्ण dpm;
	/* pageflipping */
	काष्ठा अणु
		व्योम (*page_flip)(काष्ठा radeon_device *rdev, पूर्णांक crtc, u64 crtc_base, bool async);
		bool (*page_flip_pending)(काष्ठा radeon_device *rdev, पूर्णांक crtc);
	पूर्ण pflip;
पूर्ण;

/*
 * Asic काष्ठाures
 */
काष्ठा r100_asic अणु
	स्थिर अचिन्हित		*reg_safe_bm;
	अचिन्हित		reg_safe_bm_size;
	u32			hdp_cntl;
पूर्ण;

काष्ठा r300_asic अणु
	स्थिर अचिन्हित		*reg_safe_bm;
	अचिन्हित		reg_safe_bm_size;
	u32			resync_scratch;
	u32			hdp_cntl;
पूर्ण;

काष्ठा r600_asic अणु
	अचिन्हित		max_pipes;
	अचिन्हित		max_tile_pipes;
	अचिन्हित		max_simds;
	अचिन्हित		max_backends;
	अचिन्हित		max_gprs;
	अचिन्हित		max_thपढ़ोs;
	अचिन्हित		max_stack_entries;
	अचिन्हित		max_hw_contexts;
	अचिन्हित		max_gs_thपढ़ोs;
	अचिन्हित		sx_max_export_size;
	अचिन्हित		sx_max_export_pos_size;
	अचिन्हित		sx_max_export_smx_size;
	अचिन्हित		sq_num_cf_insts;
	अचिन्हित		tiling_nbanks;
	अचिन्हित		tiling_npipes;
	अचिन्हित		tiling_group_size;
	अचिन्हित		tile_config;
	अचिन्हित		backend_map;
	अचिन्हित		active_simds;
पूर्ण;

काष्ठा rv770_asic अणु
	अचिन्हित		max_pipes;
	अचिन्हित		max_tile_pipes;
	अचिन्हित		max_simds;
	अचिन्हित		max_backends;
	अचिन्हित		max_gprs;
	अचिन्हित		max_thपढ़ोs;
	अचिन्हित		max_stack_entries;
	अचिन्हित		max_hw_contexts;
	अचिन्हित		max_gs_thपढ़ोs;
	अचिन्हित		sx_max_export_size;
	अचिन्हित		sx_max_export_pos_size;
	अचिन्हित		sx_max_export_smx_size;
	अचिन्हित		sq_num_cf_insts;
	अचिन्हित		sx_num_of_sets;
	अचिन्हित		sc_prim_fअगरo_size;
	अचिन्हित		sc_hiz_tile_fअगरo_size;
	अचिन्हित		sc_earlyz_tile_fअगरo_fize;
	अचिन्हित		tiling_nbanks;
	अचिन्हित		tiling_npipes;
	अचिन्हित		tiling_group_size;
	अचिन्हित		tile_config;
	अचिन्हित		backend_map;
	अचिन्हित		active_simds;
पूर्ण;

काष्ठा evergreen_asic अणु
	अचिन्हित num_ses;
	अचिन्हित max_pipes;
	अचिन्हित max_tile_pipes;
	अचिन्हित max_simds;
	अचिन्हित max_backends;
	अचिन्हित max_gprs;
	अचिन्हित max_thपढ़ोs;
	अचिन्हित max_stack_entries;
	अचिन्हित max_hw_contexts;
	अचिन्हित max_gs_thपढ़ोs;
	अचिन्हित sx_max_export_size;
	अचिन्हित sx_max_export_pos_size;
	अचिन्हित sx_max_export_smx_size;
	अचिन्हित sq_num_cf_insts;
	अचिन्हित sx_num_of_sets;
	अचिन्हित sc_prim_fअगरo_size;
	अचिन्हित sc_hiz_tile_fअगरo_size;
	अचिन्हित sc_earlyz_tile_fअगरo_size;
	अचिन्हित tiling_nbanks;
	अचिन्हित tiling_npipes;
	अचिन्हित tiling_group_size;
	अचिन्हित tile_config;
	अचिन्हित backend_map;
	अचिन्हित active_simds;
पूर्ण;

काष्ठा cayman_asic अणु
	अचिन्हित max_shader_engines;
	अचिन्हित max_pipes_per_simd;
	अचिन्हित max_tile_pipes;
	अचिन्हित max_simds_per_se;
	अचिन्हित max_backends_per_se;
	अचिन्हित max_texture_channel_caches;
	अचिन्हित max_gprs;
	अचिन्हित max_thपढ़ोs;
	अचिन्हित max_gs_thपढ़ोs;
	अचिन्हित max_stack_entries;
	अचिन्हित sx_num_of_sets;
	अचिन्हित sx_max_export_size;
	अचिन्हित sx_max_export_pos_size;
	अचिन्हित sx_max_export_smx_size;
	अचिन्हित max_hw_contexts;
	अचिन्हित sq_num_cf_insts;
	अचिन्हित sc_prim_fअगरo_size;
	अचिन्हित sc_hiz_tile_fअगरo_size;
	अचिन्हित sc_earlyz_tile_fअगरo_size;

	अचिन्हित num_shader_engines;
	अचिन्हित num_shader_pipes_per_simd;
	अचिन्हित num_tile_pipes;
	अचिन्हित num_simds_per_se;
	अचिन्हित num_backends_per_se;
	अचिन्हित backend_disable_mask_per_asic;
	अचिन्हित backend_map;
	अचिन्हित num_texture_channel_caches;
	अचिन्हित mem_max_burst_length_bytes;
	अचिन्हित mem_row_size_in_kb;
	अचिन्हित shader_engine_tile_size;
	अचिन्हित num_gpus;
	अचिन्हित multi_gpu_tile_size;

	अचिन्हित tile_config;
	अचिन्हित active_simds;
पूर्ण;

काष्ठा si_asic अणु
	अचिन्हित max_shader_engines;
	अचिन्हित max_tile_pipes;
	अचिन्हित max_cu_per_sh;
	अचिन्हित max_sh_per_se;
	अचिन्हित max_backends_per_se;
	अचिन्हित max_texture_channel_caches;
	अचिन्हित max_gprs;
	अचिन्हित max_gs_thपढ़ोs;
	अचिन्हित max_hw_contexts;
	अचिन्हित sc_prim_fअगरo_size_frontend;
	अचिन्हित sc_prim_fअगरo_size_backend;
	अचिन्हित sc_hiz_tile_fअगरo_size;
	अचिन्हित sc_earlyz_tile_fअगरo_size;

	अचिन्हित num_tile_pipes;
	अचिन्हित backend_enable_mask;
	अचिन्हित backend_disable_mask_per_asic;
	अचिन्हित backend_map;
	अचिन्हित num_texture_channel_caches;
	अचिन्हित mem_max_burst_length_bytes;
	अचिन्हित mem_row_size_in_kb;
	अचिन्हित shader_engine_tile_size;
	अचिन्हित num_gpus;
	अचिन्हित multi_gpu_tile_size;

	अचिन्हित tile_config;
	uपूर्णांक32_t tile_mode_array[32];
	uपूर्णांक32_t active_cus;
पूर्ण;

काष्ठा cik_asic अणु
	अचिन्हित max_shader_engines;
	अचिन्हित max_tile_pipes;
	अचिन्हित max_cu_per_sh;
	अचिन्हित max_sh_per_se;
	अचिन्हित max_backends_per_se;
	अचिन्हित max_texture_channel_caches;
	अचिन्हित max_gprs;
	अचिन्हित max_gs_thपढ़ोs;
	अचिन्हित max_hw_contexts;
	अचिन्हित sc_prim_fअगरo_size_frontend;
	अचिन्हित sc_prim_fअगरo_size_backend;
	अचिन्हित sc_hiz_tile_fअगरo_size;
	अचिन्हित sc_earlyz_tile_fअगरo_size;

	अचिन्हित num_tile_pipes;
	अचिन्हित backend_enable_mask;
	अचिन्हित backend_disable_mask_per_asic;
	अचिन्हित backend_map;
	अचिन्हित num_texture_channel_caches;
	अचिन्हित mem_max_burst_length_bytes;
	अचिन्हित mem_row_size_in_kb;
	अचिन्हित shader_engine_tile_size;
	अचिन्हित num_gpus;
	अचिन्हित multi_gpu_tile_size;

	अचिन्हित tile_config;
	uपूर्णांक32_t tile_mode_array[32];
	uपूर्णांक32_t macrotile_mode_array[16];
	uपूर्णांक32_t active_cus;
पूर्ण;

जोड़ radeon_asic_config अणु
	काष्ठा r300_asic	r300;
	काष्ठा r100_asic	r100;
	काष्ठा r600_asic	r600;
	काष्ठा rv770_asic	rv770;
	काष्ठा evergreen_asic	evergreen;
	काष्ठा cayman_asic	cayman;
	काष्ठा si_asic		si;
	काष्ठा cik_asic		cik;
पूर्ण;

/*
 * asic initizalization from radeon_asic.c
 */
व्योम radeon_agp_disable(काष्ठा radeon_device *rdev);
पूर्णांक radeon_asic_init(काष्ठा radeon_device *rdev);


/*
 * IOCTL.
 */
पूर्णांक radeon_gem_info_ioctl(काष्ठा drm_device *dev, व्योम *data,
			  काष्ठा drm_file *filp);
पूर्णांक radeon_gem_create_ioctl(काष्ठा drm_device *dev, व्योम *data,
			    काष्ठा drm_file *filp);
पूर्णांक radeon_gem_userptr_ioctl(काष्ठा drm_device *dev, व्योम *data,
			     काष्ठा drm_file *filp);
पूर्णांक radeon_gem_pin_ioctl(काष्ठा drm_device *dev, व्योम *data,
			 काष्ठा drm_file *file_priv);
पूर्णांक radeon_gem_unpin_ioctl(काष्ठा drm_device *dev, व्योम *data,
			   काष्ठा drm_file *file_priv);
पूर्णांक radeon_gem_pग_लिखो_ioctl(काष्ठा drm_device *dev, व्योम *data,
			    काष्ठा drm_file *file_priv);
पूर्णांक radeon_gem_pपढ़ो_ioctl(काष्ठा drm_device *dev, व्योम *data,
			   काष्ठा drm_file *file_priv);
पूर्णांक radeon_gem_set_करोमुख्य_ioctl(काष्ठा drm_device *dev, व्योम *data,
				काष्ठा drm_file *filp);
पूर्णांक radeon_gem_mmap_ioctl(काष्ठा drm_device *dev, व्योम *data,
			  काष्ठा drm_file *filp);
पूर्णांक radeon_gem_busy_ioctl(काष्ठा drm_device *dev, व्योम *data,
			  काष्ठा drm_file *filp);
पूर्णांक radeon_gem_रुको_idle_ioctl(काष्ठा drm_device *dev, व्योम *data,
			      काष्ठा drm_file *filp);
पूर्णांक radeon_gem_va_ioctl(काष्ठा drm_device *dev, व्योम *data,
			  काष्ठा drm_file *filp);
पूर्णांक radeon_gem_op_ioctl(काष्ठा drm_device *dev, व्योम *data,
			काष्ठा drm_file *filp);
पूर्णांक radeon_cs_ioctl(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *filp);
पूर्णांक radeon_gem_set_tiling_ioctl(काष्ठा drm_device *dev, व्योम *data,
				काष्ठा drm_file *filp);
पूर्णांक radeon_gem_get_tiling_ioctl(काष्ठा drm_device *dev, व्योम *data,
				काष्ठा drm_file *filp);
पूर्णांक radeon_info_ioctl(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *filp);

/* VRAM scratch page क्रम HDP bug, शेष vram page */
काष्ठा r600_vram_scratch अणु
	काष्ठा radeon_bo		*robj;
	अस्थिर uपूर्णांक32_t		*ptr;
	u64				gpu_addr;
पूर्ण;

/*
 * ACPI
 */
काष्ठा radeon_atअगर_notअगरication_cfg अणु
	bool enabled;
	पूर्णांक command_code;
पूर्ण;

काष्ठा radeon_atअगर_notअगरications अणु
	bool display_चयन;
	bool expansion_mode_change;
	bool thermal_state;
	bool क्रमced_घातer_state;
	bool प्रणाली_घातer_state;
	bool display_conf_change;
	bool px_gfx_चयन;
	bool brightness_change;
	bool dgpu_display_event;
पूर्ण;

काष्ठा radeon_atअगर_functions अणु
	bool प्रणाली_params;
	bool sbios_requests;
	bool select_active_disp;
	bool lid_state;
	bool get_tv_standard;
	bool set_tv_standard;
	bool get_panel_expansion_mode;
	bool set_panel_expansion_mode;
	bool temperature_change;
	bool graphics_device_types;
पूर्ण;

काष्ठा radeon_atअगर अणु
	काष्ठा radeon_atअगर_notअगरications notअगरications;
	काष्ठा radeon_atअगर_functions functions;
	काष्ठा radeon_atअगर_notअगरication_cfg notअगरication_cfg;
	काष्ठा radeon_encoder *encoder_क्रम_bl;
पूर्ण;

काष्ठा radeon_atcs_functions अणु
	bool get_ext_state;
	bool pcie_perf_req;
	bool pcie_dev_rdy;
	bool pcie_bus_width;
पूर्ण;

काष्ठा radeon_atcs अणु
	काष्ठा radeon_atcs_functions functions;
पूर्ण;

/*
 * Core काष्ठाure, functions and helpers.
 */
प्रकार uपूर्णांक32_t (*radeon_rreg_t)(काष्ठा radeon_device*, uपूर्णांक32_t);
प्रकार व्योम (*radeon_wreg_t)(काष्ठा radeon_device*, uपूर्णांक32_t, uपूर्णांक32_t);

काष्ठा radeon_device अणु
	काष्ठा device			*dev;
	काष्ठा drm_device		*ddev;
	काष्ठा pci_dev			*pdev;
#अगर_घोषित __alpha__
	काष्ठा pci_controller		*hose;
#पूर्ण_अगर
	काष्ठा rw_semaphore		exclusive_lock;
	/* ASIC */
	जोड़ radeon_asic_config	config;
	क्रमागत radeon_family		family;
	अचिन्हित दीर्घ			flags;
	पूर्णांक				usec_समयout;
	क्रमागत radeon_pll_errata		pll_errata;
	पूर्णांक				num_gb_pipes;
	पूर्णांक				num_z_pipes;
	पूर्णांक				disp_priority;
	/* BIOS */
	uपूर्णांक8_t				*bios;
	bool				is_atom_bios;
	uपूर्णांक16_t			bios_header_start;
	काष्ठा radeon_bo		*stolen_vga_memory;
	/* Register mmio */
	resource_माप_प्रकार			rmmio_base;
	resource_माप_प्रकार			rmmio_size;
	/* protects concurrent MM_INDEX/DATA based रेजिस्टर access */
	spinlock_t mmio_idx_lock;
	/* protects concurrent SMC based रेजिस्टर access */
	spinlock_t smc_idx_lock;
	/* protects concurrent PLL रेजिस्टर access */
	spinlock_t pll_idx_lock;
	/* protects concurrent MC रेजिस्टर access */
	spinlock_t mc_idx_lock;
	/* protects concurrent PCIE रेजिस्टर access */
	spinlock_t pcie_idx_lock;
	/* protects concurrent PCIE_PORT रेजिस्टर access */
	spinlock_t pciep_idx_lock;
	/* protects concurrent PIF रेजिस्टर access */
	spinlock_t pअगर_idx_lock;
	/* protects concurrent CG रेजिस्टर access */
	spinlock_t cg_idx_lock;
	/* protects concurrent UVD रेजिस्टर access */
	spinlock_t uvd_idx_lock;
	/* protects concurrent RCU रेजिस्टर access */
	spinlock_t rcu_idx_lock;
	/* protects concurrent DIDT रेजिस्टर access */
	spinlock_t didt_idx_lock;
	/* protects concurrent ENDPOINT (audio) रेजिस्टर access */
	spinlock_t end_idx_lock;
	व्योम __iomem			*rmmio;
	radeon_rreg_t			mc_rreg;
	radeon_wreg_t			mc_wreg;
	radeon_rreg_t			pll_rreg;
	radeon_wreg_t			pll_wreg;
	uपूर्णांक32_t                        pcie_reg_mask;
	radeon_rreg_t			pciep_rreg;
	radeon_wreg_t			pciep_wreg;
	/* io port */
	व्योम __iomem                    *rio_mem;
	resource_माप_प्रकार			rio_mem_size;
	काष्ठा radeon_घड़ी             घड़ी;
	काष्ठा radeon_mc		mc;
	काष्ठा radeon_gart		gart;
	काष्ठा radeon_mode_info		mode_info;
	काष्ठा radeon_scratch		scratch;
	काष्ठा radeon_करोorbell		करोorbell;
	काष्ठा radeon_mman		mman;
	काष्ठा radeon_fence_driver	fence_drv[RADEON_NUM_RINGS];
	रुको_queue_head_t		fence_queue;
	u64				fence_context;
	काष्ठा mutex			ring_lock;
	काष्ठा radeon_ring		ring[RADEON_NUM_RINGS];
	bool				ib_pool_पढ़ोy;
	काष्ठा radeon_sa_manager	ring_पंचांगp_bo;
	काष्ठा radeon_irq		irq;
	काष्ठा radeon_asic		*asic;
	काष्ठा radeon_gem		gem;
	काष्ठा radeon_pm		pm;
	काष्ठा radeon_uvd		uvd;
	काष्ठा radeon_vce		vce;
	uपूर्णांक32_t			bios_scratch[RADEON_BIOS_NUM_SCRATCH];
	काष्ठा radeon_wb		wb;
	काष्ठा radeon_dummy_page	dummy_page;
	bool				shutकरोwn;
	bool				need_swiotlb;
	bool				accel_working;
	bool				fastfb_working; /* IGP feature*/
	bool				needs_reset, in_reset;
	काष्ठा radeon_surface_reg surface_regs[RADEON_GEM_MAX_SURFACES];
	स्थिर काष्ठा firmware *me_fw;	/* all family ME firmware */
	स्थिर काष्ठा firmware *pfp_fw;	/* r6/700 PFP firmware */
	स्थिर काष्ठा firmware *rlc_fw;	/* r6/700 RLC firmware */
	स्थिर काष्ठा firmware *mc_fw;	/* NI MC firmware */
	स्थिर काष्ठा firmware *ce_fw;	/* SI CE firmware */
	स्थिर काष्ठा firmware *mec_fw;	/* CIK MEC firmware */
	स्थिर काष्ठा firmware *mec2_fw;	/* KV MEC2 firmware */
	स्थिर काष्ठा firmware *sdma_fw;	/* CIK SDMA firmware */
	स्थिर काष्ठा firmware *smc_fw;	/* SMC firmware */
	स्थिर काष्ठा firmware *uvd_fw;	/* UVD firmware */
	स्थिर काष्ठा firmware *vce_fw;	/* VCE firmware */
	bool new_fw;
	काष्ठा r600_vram_scratch vram_scratch;
	पूर्णांक msi_enabled; /* msi enabled */
	काष्ठा r600_ih ih; /* r6/700 पूर्णांकerrupt ring */
	काष्ठा radeon_rlc rlc;
	काष्ठा radeon_mec mec;
	काष्ठा delayed_work hotplug_work;
	काष्ठा work_काष्ठा dp_work;
	काष्ठा work_काष्ठा audio_work;
	पूर्णांक num_crtc; /* number of crtcs */
	काष्ठा mutex dc_hw_i2c_mutex; /* display controller hw i2c mutex */
	bool has_uvd;
	bool has_vce;
	काष्ठा r600_audio audio; /* audio stuff */
	काष्ठा notअगरier_block acpi_nb;
	/* only one userspace can use Hyperz features or CMASK at a समय */
	काष्ठा drm_file *hyperz_filp;
	काष्ठा drm_file *cmask_filp;
	/* i2c buses */
	काष्ठा radeon_i2c_chan *i2c_bus[RADEON_MAX_I2C_BUS];
	/* भव memory */
	काष्ठा radeon_vm_manager	vm_manager;
	काष्ठा mutex			gpu_घड़ी_mutex;
	/* memory stats */
	atomic64_t			vram_usage;
	atomic64_t			gtt_usage;
	atomic64_t			num_bytes_moved;
	atomic_t			gpu_reset_counter;
	/* ACPI पूर्णांकerface */
	काष्ठा radeon_atअगर		atअगर;
	काष्ठा radeon_atcs		atcs;
	/* srbm instance रेजिस्टरs */
	काष्ठा mutex			srbm_mutex;
	/* घड़ी, घातergating flags */
	u32 cg_flags;
	u32 pg_flags;

	काष्ठा dev_pm_करोमुख्य vga_pm_करोमुख्य;
	bool have_disp_घातer_ref;
	u32 px_quirk_flags;

	/* tracking pinned memory */
	u64 vram_pin_size;
	u64 gart_pin_size;
पूर्ण;

bool radeon_is_px(काष्ठा drm_device *dev);
पूर्णांक radeon_device_init(काष्ठा radeon_device *rdev,
		       काष्ठा drm_device *ddev,
		       काष्ठा pci_dev *pdev,
		       uपूर्णांक32_t flags);
व्योम radeon_device_fini(काष्ठा radeon_device *rdev);
पूर्णांक radeon_gpu_रुको_क्रम_idle(काष्ठा radeon_device *rdev);

#घोषणा RADEON_MIN_MMIO_SIZE 0x10000

uपूर्णांक32_t r100_mm_rreg_slow(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg);
व्योम r100_mm_wreg_slow(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg, uपूर्णांक32_t v);
अटल अंतरभूत uपूर्णांक32_t r100_mm_rreg(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg,
				    bool always_indirect)
अणु
	/* The mmio size is 64kb at minimum. Allows the अगर to be optimized out. */
	अगर ((reg < rdev->rmmio_size || reg < RADEON_MIN_MMIO_SIZE) && !always_indirect)
		वापस पढ़ोl(((व्योम __iomem *)rdev->rmmio) + reg);
	अन्यथा
		वापस r100_mm_rreg_slow(rdev, reg);
पूर्ण
अटल अंतरभूत व्योम r100_mm_wreg(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg, uपूर्णांक32_t v,
				bool always_indirect)
अणु
	अगर ((reg < rdev->rmmio_size || reg < RADEON_MIN_MMIO_SIZE) && !always_indirect)
		ग_लिखोl(v, ((व्योम __iomem *)rdev->rmmio) + reg);
	अन्यथा
		r100_mm_wreg_slow(rdev, reg, v);
पूर्ण

u32 r100_io_rreg(काष्ठा radeon_device *rdev, u32 reg);
व्योम r100_io_wreg(काष्ठा radeon_device *rdev, u32 reg, u32 v);

u32 cik_mm_rकरोorbell(काष्ठा radeon_device *rdev, u32 index);
व्योम cik_mm_wकरोorbell(काष्ठा radeon_device *rdev, u32 index, u32 v);

/*
 * Cast helper
 */
बाह्य स्थिर काष्ठा dma_fence_ops radeon_fence_ops;

अटल अंतरभूत काष्ठा radeon_fence *to_radeon_fence(काष्ठा dma_fence *f)
अणु
	काष्ठा radeon_fence *__f = container_of(f, काष्ठा radeon_fence, base);

	अगर (__f->base.ops == &radeon_fence_ops)
		वापस __f;

	वापस शून्य;
पूर्ण

/*
 * Registers पढ़ो & ग_लिखो functions.
 */
#घोषणा RREG8(reg) पढ़ोb((rdev->rmmio) + (reg))
#घोषणा WREG8(reg, v) ग_लिखोb(v, (rdev->rmmio) + (reg))
#घोषणा RREG16(reg) पढ़ोw((rdev->rmmio) + (reg))
#घोषणा WREG16(reg, v) ग_लिखोw(v, (rdev->rmmio) + (reg))
#घोषणा RREG32(reg) r100_mm_rreg(rdev, (reg), false)
#घोषणा RREG32_IDX(reg) r100_mm_rreg(rdev, (reg), true)
#घोषणा DREG32(reg) pr_info("REGISTER: " #reg " : 0x%08X\n",	\
			    r100_mm_rreg(rdev, (reg), false))
#घोषणा WREG32(reg, v) r100_mm_wreg(rdev, (reg), (v), false)
#घोषणा WREG32_IDX(reg, v) r100_mm_wreg(rdev, (reg), (v), true)
#घोषणा REG_SET(FIELD, v) (((v) << FIELD##_SHIFT) & FIELD##_MASK)
#घोषणा REG_GET(FIELD, v) (((v) << FIELD##_SHIFT) & FIELD##_MASK)
#घोषणा RREG32_PLL(reg) rdev->pll_rreg(rdev, (reg))
#घोषणा WREG32_PLL(reg, v) rdev->pll_wreg(rdev, (reg), (v))
#घोषणा RREG32_MC(reg) rdev->mc_rreg(rdev, (reg))
#घोषणा WREG32_MC(reg, v) rdev->mc_wreg(rdev, (reg), (v))
#घोषणा RREG32_PCIE(reg) rv370_pcie_rreg(rdev, (reg))
#घोषणा WREG32_PCIE(reg, v) rv370_pcie_wreg(rdev, (reg), (v))
#घोषणा RREG32_PCIE_PORT(reg) rdev->pciep_rreg(rdev, (reg))
#घोषणा WREG32_PCIE_PORT(reg, v) rdev->pciep_wreg(rdev, (reg), (v))
#घोषणा RREG32_SMC(reg) tn_smc_rreg(rdev, (reg))
#घोषणा WREG32_SMC(reg, v) tn_smc_wreg(rdev, (reg), (v))
#घोषणा RREG32_RCU(reg) r600_rcu_rreg(rdev, (reg))
#घोषणा WREG32_RCU(reg, v) r600_rcu_wreg(rdev, (reg), (v))
#घोषणा RREG32_CG(reg) eg_cg_rreg(rdev, (reg))
#घोषणा WREG32_CG(reg, v) eg_cg_wreg(rdev, (reg), (v))
#घोषणा RREG32_PIF_PHY0(reg) eg_pअगर_phy0_rreg(rdev, (reg))
#घोषणा WREG32_PIF_PHY0(reg, v) eg_pअगर_phy0_wreg(rdev, (reg), (v))
#घोषणा RREG32_PIF_PHY1(reg) eg_pअगर_phy1_rreg(rdev, (reg))
#घोषणा WREG32_PIF_PHY1(reg, v) eg_pअगर_phy1_wreg(rdev, (reg), (v))
#घोषणा RREG32_UVD_CTX(reg) r600_uvd_ctx_rreg(rdev, (reg))
#घोषणा WREG32_UVD_CTX(reg, v) r600_uvd_ctx_wreg(rdev, (reg), (v))
#घोषणा RREG32_DIDT(reg) cik_didt_rreg(rdev, (reg))
#घोषणा WREG32_DIDT(reg, v) cik_didt_wreg(rdev, (reg), (v))
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
#घोषणा WREG32_SMC_P(reg, val, mask)				\
	करो अणु							\
		uपूर्णांक32_t पंचांगp_ = RREG32_SMC(reg);		\
		पंचांगp_ &= (mask);					\
		पंचांगp_ |= ((val) & ~(mask));			\
		WREG32_SMC(reg, पंचांगp_);				\
	पूर्ण जबतक (0)
#घोषणा DREG32_SYS(sqf, rdev, reg) seq_म_लिखो((sqf), #reg " : 0x%08X\n", r100_mm_rreg((rdev), (reg), false))
#घोषणा RREG32_IO(reg) r100_io_rreg(rdev, (reg))
#घोषणा WREG32_IO(reg, v) r100_io_wreg(rdev, (reg), (v))

#घोषणा RDOORBELL32(index) cik_mm_rकरोorbell(rdev, (index))
#घोषणा WDOORBELL32(index, v) cik_mm_wकरोorbell(rdev, (index), (v))

/*
 * Indirect रेजिस्टरs accessors.
 * They used to be अंतरभूतd, but this increases code size by ~65 kbytes.
 * Since each perक्रमms a pair of MMIO ops
 * within a spin_lock_irqsave/spin_unlock_irqrestore region,
 * the cost of call+ret is almost negligible. MMIO and locking
 * costs several करोzens of cycles each at best, call+ret is ~5 cycles.
 */
uपूर्णांक32_t rv370_pcie_rreg(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg);
व्योम rv370_pcie_wreg(काष्ठा radeon_device *rdev, uपूर्णांक32_t reg, uपूर्णांक32_t v);
u32 tn_smc_rreg(काष्ठा radeon_device *rdev, u32 reg);
व्योम tn_smc_wreg(काष्ठा radeon_device *rdev, u32 reg, u32 v);
u32 r600_rcu_rreg(काष्ठा radeon_device *rdev, u32 reg);
व्योम r600_rcu_wreg(काष्ठा radeon_device *rdev, u32 reg, u32 v);
u32 eg_cg_rreg(काष्ठा radeon_device *rdev, u32 reg);
व्योम eg_cg_wreg(काष्ठा radeon_device *rdev, u32 reg, u32 v);
u32 eg_pअगर_phy0_rreg(काष्ठा radeon_device *rdev, u32 reg);
व्योम eg_pअगर_phy0_wreg(काष्ठा radeon_device *rdev, u32 reg, u32 v);
u32 eg_pअगर_phy1_rreg(काष्ठा radeon_device *rdev, u32 reg);
व्योम eg_pअगर_phy1_wreg(काष्ठा radeon_device *rdev, u32 reg, u32 v);
u32 r600_uvd_ctx_rreg(काष्ठा radeon_device *rdev, u32 reg);
व्योम r600_uvd_ctx_wreg(काष्ठा radeon_device *rdev, u32 reg, u32 v);
u32 cik_didt_rreg(काष्ठा radeon_device *rdev, u32 reg);
व्योम cik_didt_wreg(काष्ठा radeon_device *rdev, u32 reg, u32 v);

व्योम r100_pll_errata_after_index(काष्ठा radeon_device *rdev);


/*
 * ASICs helpers.
 */
#घोषणा ASIC_IS_RN50(rdev) ((rdev->pdev->device == 0x515e) || \
			    (rdev->pdev->device == 0x5969))
#घोषणा ASIC_IS_RV100(rdev) ((rdev->family == CHIP_RV100) || \
		(rdev->family == CHIP_RV200) || \
		(rdev->family == CHIP_RS100) || \
		(rdev->family == CHIP_RS200) || \
		(rdev->family == CHIP_RV250) || \
		(rdev->family == CHIP_RV280) || \
		(rdev->family == CHIP_RS300))
#घोषणा ASIC_IS_R300(rdev) ((rdev->family == CHIP_R300)  ||	\
		(rdev->family == CHIP_RV350) ||			\
		(rdev->family == CHIP_R350)  ||			\
		(rdev->family == CHIP_RV380) ||			\
		(rdev->family == CHIP_R420)  ||			\
		(rdev->family == CHIP_R423)  ||			\
		(rdev->family == CHIP_RV410) ||			\
		(rdev->family == CHIP_RS400) ||			\
		(rdev->family == CHIP_RS480))
#घोषणा ASIC_IS_X2(rdev) ((rdev->pdev->device == 0x9441) || \
		(rdev->pdev->device == 0x9443) || \
		(rdev->pdev->device == 0x944B) || \
		(rdev->pdev->device == 0x9506) || \
		(rdev->pdev->device == 0x9509) || \
		(rdev->pdev->device == 0x950F) || \
		(rdev->pdev->device == 0x689C) || \
		(rdev->pdev->device == 0x689D))
#घोषणा ASIC_IS_AVIVO(rdev) ((rdev->family >= CHIP_RS600))
#घोषणा ASIC_IS_DCE2(rdev) ((rdev->family == CHIP_RS600)  ||	\
			    (rdev->family == CHIP_RS690)  ||	\
			    (rdev->family == CHIP_RS740)  ||	\
			    (rdev->family >= CHIP_R600))
#घोषणा ASIC_IS_DCE3(rdev) ((rdev->family >= CHIP_RV620))
#घोषणा ASIC_IS_DCE32(rdev) ((rdev->family >= CHIP_RV730))
#घोषणा ASIC_IS_DCE4(rdev) ((rdev->family >= CHIP_CEDAR))
#घोषणा ASIC_IS_DCE41(rdev) ((rdev->family >= CHIP_PALM) && \
			     (rdev->flags & RADEON_IS_IGP))
#घोषणा ASIC_IS_DCE5(rdev) ((rdev->family >= CHIP_BARTS))
#घोषणा ASIC_IS_DCE6(rdev) ((rdev->family >= CHIP_ARUBA))
#घोषणा ASIC_IS_DCE61(rdev) ((rdev->family >= CHIP_ARUBA) && \
			     (rdev->flags & RADEON_IS_IGP))
#घोषणा ASIC_IS_DCE64(rdev) ((rdev->family == CHIP_OLAND))
#घोषणा ASIC_IS_NODCE(rdev) ((rdev->family == CHIP_HAIन_अंक))
#घोषणा ASIC_IS_DCE8(rdev) ((rdev->family >= CHIP_BONAIRE))
#घोषणा ASIC_IS_DCE81(rdev) ((rdev->family == CHIP_KAVERI))
#घोषणा ASIC_IS_DCE82(rdev) ((rdev->family == CHIP_BONAIRE))
#घोषणा ASIC_IS_DCE83(rdev) ((rdev->family == CHIP_KABINI) || \
			     (rdev->family == CHIP_MULLINS))

#घोषणा ASIC_IS_LOMBOK(rdev) ((rdev->pdev->device == 0x6849) || \
			      (rdev->pdev->device == 0x6850) || \
			      (rdev->pdev->device == 0x6858) || \
			      (rdev->pdev->device == 0x6859) || \
			      (rdev->pdev->device == 0x6840) || \
			      (rdev->pdev->device == 0x6841) || \
			      (rdev->pdev->device == 0x6842) || \
			      (rdev->pdev->device == 0x6843))

/*
 * BIOS helpers.
 */
#घोषणा RBIOS8(i) (rdev->bios[i])
#घोषणा RBIOS16(i) (RBIOS8(i) | (RBIOS8((i)+1) << 8))
#घोषणा RBIOS32(i) ((RBIOS16(i)) | (RBIOS16((i)+2) << 16))

पूर्णांक radeon_combios_init(काष्ठा radeon_device *rdev);
व्योम radeon_combios_fini(काष्ठा radeon_device *rdev);
पूर्णांक radeon_atombios_init(काष्ठा radeon_device *rdev);
व्योम radeon_atombios_fini(काष्ठा radeon_device *rdev);


/*
 * RING helpers.
 */

/**
 * radeon_ring_ग_लिखो - ग_लिखो a value to the ring
 *
 * @ring: radeon_ring काष्ठाure holding ring inक्रमmation
 * @v: dword (dw) value to ग_लिखो
 *
 * Write a value to the requested ring buffer (all asics).
 */
अटल अंतरभूत व्योम radeon_ring_ग_लिखो(काष्ठा radeon_ring *ring, uपूर्णांक32_t v)
अणु
	अगर (ring->count_dw <= 0)
		DRM_ERROR("radeon: writing more dwords to the ring than expected!\n");

	ring->ring[ring->wptr++] = v;
	ring->wptr &= ring->ptr_mask;
	ring->count_dw--;
	ring->ring_मुक्त_dw--;
पूर्ण

/*
 * ASICs macro.
 */
#घोषणा radeon_init(rdev) (rdev)->asic->init((rdev))
#घोषणा radeon_fini(rdev) (rdev)->asic->fini((rdev))
#घोषणा radeon_resume(rdev) (rdev)->asic->resume((rdev))
#घोषणा radeon_suspend(rdev) (rdev)->asic->suspend((rdev))
#घोषणा radeon_cs_parse(rdev, r, p) (rdev)->asic->ring[(r)]->cs_parse((p))
#घोषणा radeon_vga_set_state(rdev, state) (rdev)->asic->vga_set_state((rdev), (state))
#घोषणा radeon_asic_reset(rdev) (rdev)->asic->asic_reset((rdev), false)
#घोषणा radeon_gart_tlb_flush(rdev) (rdev)->asic->gart.tlb_flush((rdev))
#घोषणा radeon_gart_get_page_entry(a, f) (rdev)->asic->gart.get_page_entry((a), (f))
#घोषणा radeon_gart_set_page(rdev, i, e) (rdev)->asic->gart.set_page((rdev), (i), (e))
#घोषणा radeon_asic_vm_init(rdev) (rdev)->asic->vm.init((rdev))
#घोषणा radeon_asic_vm_fini(rdev) (rdev)->asic->vm.fini((rdev))
#घोषणा radeon_asic_vm_copy_pages(rdev, ib, pe, src, count) ((rdev)->asic->vm.copy_pages((rdev), (ib), (pe), (src), (count)))
#घोषणा radeon_asic_vm_ग_लिखो_pages(rdev, ib, pe, addr, count, incr, flags) ((rdev)->asic->vm.ग_लिखो_pages((rdev), (ib), (pe), (addr), (count), (incr), (flags)))
#घोषणा radeon_asic_vm_set_pages(rdev, ib, pe, addr, count, incr, flags) ((rdev)->asic->vm.set_pages((rdev), (ib), (pe), (addr), (count), (incr), (flags)))
#घोषणा radeon_asic_vm_pad_ib(rdev, ib) ((rdev)->asic->vm.pad_ib((ib)))
#घोषणा radeon_ring_start(rdev, r, cp) (rdev)->asic->ring[(r)]->ring_start((rdev), (cp))
#घोषणा radeon_ring_test(rdev, r, cp) (rdev)->asic->ring[(r)]->ring_test((rdev), (cp))
#घोषणा radeon_ib_test(rdev, r, cp) (rdev)->asic->ring[(r)]->ib_test((rdev), (cp))
#घोषणा radeon_ring_ib_execute(rdev, r, ib) (rdev)->asic->ring[(r)]->ib_execute((rdev), (ib))
#घोषणा radeon_ring_ib_parse(rdev, r, ib) (rdev)->asic->ring[(r)]->ib_parse((rdev), (ib))
#घोषणा radeon_ring_is_lockup(rdev, r, cp) (rdev)->asic->ring[(r)]->is_lockup((rdev), (cp))
#घोषणा radeon_ring_vm_flush(rdev, r, vm_id, pd_addr) (rdev)->asic->ring[(r)->idx]->vm_flush((rdev), (r), (vm_id), (pd_addr))
#घोषणा radeon_ring_get_rptr(rdev, r) (rdev)->asic->ring[(r)->idx]->get_rptr((rdev), (r))
#घोषणा radeon_ring_get_wptr(rdev, r) (rdev)->asic->ring[(r)->idx]->get_wptr((rdev), (r))
#घोषणा radeon_ring_set_wptr(rdev, r) (rdev)->asic->ring[(r)->idx]->set_wptr((rdev), (r))
#घोषणा radeon_irq_set(rdev) (rdev)->asic->irq.set((rdev))
#घोषणा radeon_irq_process(rdev) (rdev)->asic->irq.process((rdev))
#घोषणा radeon_get_vblank_counter(rdev, crtc) (rdev)->asic->display.get_vblank_counter((rdev), (crtc))
#घोषणा radeon_set_backlight_level(rdev, e, l) (rdev)->asic->display.set_backlight_level((e), (l))
#घोषणा radeon_get_backlight_level(rdev, e) (rdev)->asic->display.get_backlight_level((e))
#घोषणा radeon_hdmi_enable(rdev, e, b) (rdev)->asic->display.hdmi_enable((e), (b))
#घोषणा radeon_hdmi_seपंचांगode(rdev, e, m) (rdev)->asic->display.hdmi_seपंचांगode((e), (m))
#घोषणा radeon_fence_ring_emit(rdev, r, fence) (rdev)->asic->ring[(r)]->emit_fence((rdev), (fence))
#घोषणा radeon_semaphore_ring_emit(rdev, r, cp, semaphore, emit_रुको) (rdev)->asic->ring[(r)]->emit_semaphore((rdev), (cp), (semaphore), (emit_रुको))
#घोषणा radeon_copy_blit(rdev, s, d, np, resv) (rdev)->asic->copy.blit((rdev), (s), (d), (np), (resv))
#घोषणा radeon_copy_dma(rdev, s, d, np, resv) (rdev)->asic->copy.dma((rdev), (s), (d), (np), (resv))
#घोषणा radeon_copy(rdev, s, d, np, resv) (rdev)->asic->copy.copy((rdev), (s), (d), (np), (resv))
#घोषणा radeon_copy_blit_ring_index(rdev) (rdev)->asic->copy.blit_ring_index
#घोषणा radeon_copy_dma_ring_index(rdev) (rdev)->asic->copy.dma_ring_index
#घोषणा radeon_copy_ring_index(rdev) (rdev)->asic->copy.copy_ring_index
#घोषणा radeon_get_engine_घड़ी(rdev) (rdev)->asic->pm.get_engine_घड़ी((rdev))
#घोषणा radeon_set_engine_घड़ी(rdev, e) (rdev)->asic->pm.set_engine_घड़ी((rdev), (e))
#घोषणा radeon_get_memory_घड़ी(rdev) (rdev)->asic->pm.get_memory_घड़ी((rdev))
#घोषणा radeon_set_memory_घड़ी(rdev, e) (rdev)->asic->pm.set_memory_घड़ी((rdev), (e))
#घोषणा radeon_get_pcie_lanes(rdev) (rdev)->asic->pm.get_pcie_lanes((rdev))
#घोषणा radeon_set_pcie_lanes(rdev, l) (rdev)->asic->pm.set_pcie_lanes((rdev), (l))
#घोषणा radeon_set_घड़ी_gating(rdev, e) (rdev)->asic->pm.set_घड़ी_gating((rdev), (e))
#घोषणा radeon_set_uvd_घड़ीs(rdev, v, d) (rdev)->asic->pm.set_uvd_घड़ीs((rdev), (v), (d))
#घोषणा radeon_set_vce_घड़ीs(rdev, ev, ec) (rdev)->asic->pm.set_vce_घड़ीs((rdev), (ev), (ec))
#घोषणा radeon_get_temperature(rdev) (rdev)->asic->pm.get_temperature((rdev))
#घोषणा radeon_set_surface_reg(rdev, r, f, p, o, s) ((rdev)->asic->surface.set_reg((rdev), (r), (f), (p), (o), (s)))
#घोषणा radeon_clear_surface_reg(rdev, r) ((rdev)->asic->surface.clear_reg((rdev), (r)))
#घोषणा radeon_bandwidth_update(rdev) (rdev)->asic->display.bandwidth_update((rdev))
#घोषणा radeon_hpd_init(rdev) (rdev)->asic->hpd.init((rdev))
#घोषणा radeon_hpd_fini(rdev) (rdev)->asic->hpd.fini((rdev))
#घोषणा radeon_hpd_sense(rdev, h) (rdev)->asic->hpd.sense((rdev), (h))
#घोषणा radeon_hpd_set_polarity(rdev, h) (rdev)->asic->hpd.set_polarity((rdev), (h))
#घोषणा radeon_gui_idle(rdev) (rdev)->asic->gui_idle((rdev))
#घोषणा radeon_pm_misc(rdev) (rdev)->asic->pm.misc((rdev))
#घोषणा radeon_pm_prepare(rdev) (rdev)->asic->pm.prepare((rdev))
#घोषणा radeon_pm_finish(rdev) (rdev)->asic->pm.finish((rdev))
#घोषणा radeon_pm_init_profile(rdev) (rdev)->asic->pm.init_profile((rdev))
#घोषणा radeon_pm_get_dynpm_state(rdev) (rdev)->asic->pm.get_dynpm_state((rdev))
#घोषणा radeon_page_flip(rdev, crtc, base, async) (rdev)->asic->pflip.page_flip((rdev), (crtc), (base), (async))
#घोषणा radeon_page_flip_pending(rdev, crtc) (rdev)->asic->pflip.page_flip_pending((rdev), (crtc))
#घोषणा radeon_रुको_क्रम_vblank(rdev, crtc) (rdev)->asic->display.रुको_क्रम_vblank((rdev), (crtc))
#घोषणा radeon_mc_रुको_क्रम_idle(rdev) (rdev)->asic->mc_रुको_क्रम_idle((rdev))
#घोषणा radeon_get_xclk(rdev) (rdev)->asic->get_xclk((rdev))
#घोषणा radeon_get_gpu_घड़ी_counter(rdev) (rdev)->asic->get_gpu_घड़ी_counter((rdev))
#घोषणा radeon_get_allowed_info_रेजिस्टर(rdev, r, v) (rdev)->asic->get_allowed_info_रेजिस्टर((rdev), (r), (v))
#घोषणा radeon_dpm_init(rdev) rdev->asic->dpm.init((rdev))
#घोषणा radeon_dpm_setup_asic(rdev) rdev->asic->dpm.setup_asic((rdev))
#घोषणा radeon_dpm_enable(rdev) rdev->asic->dpm.enable((rdev))
#घोषणा radeon_dpm_late_enable(rdev) rdev->asic->dpm.late_enable((rdev))
#घोषणा radeon_dpm_disable(rdev) rdev->asic->dpm.disable((rdev))
#घोषणा radeon_dpm_pre_set_घातer_state(rdev) rdev->asic->dpm.pre_set_घातer_state((rdev))
#घोषणा radeon_dpm_set_घातer_state(rdev) rdev->asic->dpm.set_घातer_state((rdev))
#घोषणा radeon_dpm_post_set_घातer_state(rdev) rdev->asic->dpm.post_set_घातer_state((rdev))
#घोषणा radeon_dpm_display_configuration_changed(rdev) rdev->asic->dpm.display_configuration_changed((rdev))
#घोषणा radeon_dpm_fini(rdev) rdev->asic->dpm.fini((rdev))
#घोषणा radeon_dpm_get_sclk(rdev, l) rdev->asic->dpm.get_sclk((rdev), (l))
#घोषणा radeon_dpm_get_mclk(rdev, l) rdev->asic->dpm.get_mclk((rdev), (l))
#घोषणा radeon_dpm_prपूर्णांक_घातer_state(rdev, ps) rdev->asic->dpm.prपूर्णांक_घातer_state((rdev), (ps))
#घोषणा radeon_dpm_debugfs_prपूर्णांक_current_perक्रमmance_level(rdev, m) rdev->asic->dpm.debugfs_prपूर्णांक_current_perक्रमmance_level((rdev), (m))
#घोषणा radeon_dpm_क्रमce_perक्रमmance_level(rdev, l) rdev->asic->dpm.क्रमce_perक्रमmance_level((rdev), (l))
#घोषणा radeon_dpm_vblank_too_लघु(rdev) rdev->asic->dpm.vblank_too_लघु((rdev))
#घोषणा radeon_dpm_घातergate_uvd(rdev, g) rdev->asic->dpm.घातergate_uvd((rdev), (g))
#घोषणा radeon_dpm_enable_bapm(rdev, e) rdev->asic->dpm.enable_bapm((rdev), (e))
#घोषणा radeon_dpm_get_current_sclk(rdev) rdev->asic->dpm.get_current_sclk((rdev))
#घोषणा radeon_dpm_get_current_mclk(rdev) rdev->asic->dpm.get_current_mclk((rdev))

/* Common functions */
/* AGP */
बाह्य पूर्णांक radeon_gpu_reset(काष्ठा radeon_device *rdev);
बाह्य व्योम radeon_pci_config_reset(काष्ठा radeon_device *rdev);
बाह्य व्योम r600_set_bios_scratch_engine_hung(काष्ठा radeon_device *rdev, bool hung);
बाह्य व्योम radeon_agp_disable(काष्ठा radeon_device *rdev);
बाह्य पूर्णांक radeon_modeset_init(काष्ठा radeon_device *rdev);
बाह्य व्योम radeon_modeset_fini(काष्ठा radeon_device *rdev);
बाह्य bool radeon_card_posted(काष्ठा radeon_device *rdev);
बाह्य व्योम radeon_update_bandwidth_info(काष्ठा radeon_device *rdev);
बाह्य व्योम radeon_update_display_priority(काष्ठा radeon_device *rdev);
बाह्य bool radeon_boot_test_post_card(काष्ठा radeon_device *rdev);
बाह्य व्योम radeon_scratch_init(काष्ठा radeon_device *rdev);
बाह्य व्योम radeon_wb_fini(काष्ठा radeon_device *rdev);
बाह्य पूर्णांक radeon_wb_init(काष्ठा radeon_device *rdev);
बाह्य व्योम radeon_wb_disable(काष्ठा radeon_device *rdev);
बाह्य व्योम radeon_surface_init(काष्ठा radeon_device *rdev);
बाह्य पूर्णांक radeon_cs_parser_init(काष्ठा radeon_cs_parser *p, व्योम *data);
बाह्य व्योम radeon_legacy_set_घड़ी_gating(काष्ठा radeon_device *rdev, पूर्णांक enable);
बाह्य व्योम radeon_atom_set_घड़ी_gating(काष्ठा radeon_device *rdev, पूर्णांक enable);
बाह्य व्योम radeon_tपंचांग_placement_from_करोमुख्य(काष्ठा radeon_bo *rbo, u32 करोमुख्य);
बाह्य bool radeon_tपंचांग_bo_is_radeon_bo(काष्ठा tपंचांग_buffer_object *bo);
बाह्य पूर्णांक radeon_tपंचांग_tt_set_userptr(काष्ठा radeon_device *rdev,
				     काष्ठा tपंचांग_tt *tपंचांग, uपूर्णांक64_t addr,
				     uपूर्णांक32_t flags);
बाह्य bool radeon_tपंचांग_tt_has_userptr(काष्ठा radeon_device *rdev, काष्ठा tपंचांग_tt *tपंचांग);
बाह्य bool radeon_tपंचांग_tt_is_पढ़ोonly(काष्ठा radeon_device *rdev, काष्ठा tपंचांग_tt *tपंचांग);
bool radeon_tपंचांग_tt_is_bound(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_tt *tपंचांग);
बाह्य व्योम radeon_vram_location(काष्ठा radeon_device *rdev, काष्ठा radeon_mc *mc, u64 base);
बाह्य व्योम radeon_gtt_location(काष्ठा radeon_device *rdev, काष्ठा radeon_mc *mc);
बाह्य पूर्णांक radeon_resume_kms(काष्ठा drm_device *dev, bool resume, bool fbcon);
बाह्य पूर्णांक radeon_suspend_kms(काष्ठा drm_device *dev, bool suspend,
			      bool fbcon, bool मुक्तze);
बाह्य व्योम radeon_tपंचांग_set_active_vram_size(काष्ठा radeon_device *rdev, u64 size);
बाह्य व्योम radeon_program_रेजिस्टर_sequence(काष्ठा radeon_device *rdev,
					     स्थिर u32 *रेजिस्टरs,
					     स्थिर u32 array_size);
काष्ठा radeon_device *radeon_get_rdev(काष्ठा tपंचांग_device *bdev);

/* KMS */

u32 radeon_get_vblank_counter_kms(काष्ठा drm_crtc *crtc);
पूर्णांक radeon_enable_vblank_kms(काष्ठा drm_crtc *crtc);
व्योम radeon_disable_vblank_kms(काष्ठा drm_crtc *crtc);

/*
 * vm
 */
पूर्णांक radeon_vm_manager_init(काष्ठा radeon_device *rdev);
व्योम radeon_vm_manager_fini(काष्ठा radeon_device *rdev);
पूर्णांक radeon_vm_init(काष्ठा radeon_device *rdev, काष्ठा radeon_vm *vm);
व्योम radeon_vm_fini(काष्ठा radeon_device *rdev, काष्ठा radeon_vm *vm);
काष्ठा radeon_bo_list *radeon_vm_get_bos(काष्ठा radeon_device *rdev,
					  काष्ठा radeon_vm *vm,
                                          काष्ठा list_head *head);
काष्ठा radeon_fence *radeon_vm_grab_id(काष्ठा radeon_device *rdev,
				       काष्ठा radeon_vm *vm, पूर्णांक ring);
व्योम radeon_vm_flush(काष्ठा radeon_device *rdev,
                     काष्ठा radeon_vm *vm,
		     पूर्णांक ring, काष्ठा radeon_fence *fence);
व्योम radeon_vm_fence(काष्ठा radeon_device *rdev,
		     काष्ठा radeon_vm *vm,
		     काष्ठा radeon_fence *fence);
uपूर्णांक64_t radeon_vm_map_gart(काष्ठा radeon_device *rdev, uपूर्णांक64_t addr);
पूर्णांक radeon_vm_update_page_directory(काष्ठा radeon_device *rdev,
				    काष्ठा radeon_vm *vm);
पूर्णांक radeon_vm_clear_मुक्तd(काष्ठा radeon_device *rdev,
			  काष्ठा radeon_vm *vm);
पूर्णांक radeon_vm_clear_invalids(काष्ठा radeon_device *rdev,
			     काष्ठा radeon_vm *vm);
पूर्णांक radeon_vm_bo_update(काष्ठा radeon_device *rdev,
			काष्ठा radeon_bo_va *bo_va,
			काष्ठा tपंचांग_resource *mem);
व्योम radeon_vm_bo_invalidate(काष्ठा radeon_device *rdev,
			     काष्ठा radeon_bo *bo);
काष्ठा radeon_bo_va *radeon_vm_bo_find(काष्ठा radeon_vm *vm,
				       काष्ठा radeon_bo *bo);
काष्ठा radeon_bo_va *radeon_vm_bo_add(काष्ठा radeon_device *rdev,
				      काष्ठा radeon_vm *vm,
				      काष्ठा radeon_bo *bo);
पूर्णांक radeon_vm_bo_set_addr(काष्ठा radeon_device *rdev,
			  काष्ठा radeon_bo_va *bo_va,
			  uपूर्णांक64_t offset,
			  uपूर्णांक32_t flags);
व्योम radeon_vm_bo_rmv(काष्ठा radeon_device *rdev,
		      काष्ठा radeon_bo_va *bo_va);

/* audio */
व्योम r600_audio_update_hdmi(काष्ठा work_काष्ठा *work);
काष्ठा r600_audio_pin *r600_audio_get_pin(काष्ठा radeon_device *rdev);
काष्ठा r600_audio_pin *dce6_audio_get_pin(काष्ठा radeon_device *rdev);
व्योम r600_audio_enable(काष्ठा radeon_device *rdev,
		       काष्ठा r600_audio_pin *pin,
		       u8 enable_mask);
व्योम dce6_audio_enable(काष्ठा radeon_device *rdev,
		       काष्ठा r600_audio_pin *pin,
		       u8 enable_mask);

/*
 * R600 vram scratch functions
 */
पूर्णांक r600_vram_scratch_init(काष्ठा radeon_device *rdev);
व्योम r600_vram_scratch_fini(काष्ठा radeon_device *rdev);

/*
 * r600 cs checking helper
 */
अचिन्हित r600_mip_minअगरy(अचिन्हित size, अचिन्हित level);
bool r600_fmt_is_valid_color(u32 क्रमmat);
bool r600_fmt_is_valid_texture(u32 क्रमmat, क्रमागत radeon_family family);
पूर्णांक r600_fmt_get_blocksize(u32 क्रमmat);
पूर्णांक r600_fmt_get_nblocksx(u32 क्रमmat, u32 w);
पूर्णांक r600_fmt_get_nblocksy(u32 क्रमmat, u32 h);

/*
 * r600 functions used by radeon_encoder.c
 */
काष्ठा radeon_hdmi_acr अणु
	u32 घड़ी;

	पूर्णांक n_32khz;
	पूर्णांक cts_32khz;

	पूर्णांक n_44_1khz;
	पूर्णांक cts_44_1khz;

	पूर्णांक n_48khz;
	पूर्णांक cts_48khz;

पूर्ण;

बाह्य काष्ठा radeon_hdmi_acr r600_hdmi_acr(uपूर्णांक32_t घड़ी);

बाह्य u32 r6xx_remap_render_backend(काष्ठा radeon_device *rdev,
				     u32 tiling_pipe_num,
				     u32 max_rb_num,
				     u32 total_max_rb_num,
				     u32 enabled_rb_mask);

/*
 * evergreen functions used by radeon_encoder.c
 */

बाह्य पूर्णांक ni_init_microcode(काष्ठा radeon_device *rdev);
बाह्य पूर्णांक ni_mc_load_microcode(काष्ठा radeon_device *rdev);

/* radeon_acpi.c */
#अगर defined(CONFIG_ACPI)
बाह्य पूर्णांक radeon_acpi_init(काष्ठा radeon_device *rdev);
बाह्य व्योम radeon_acpi_fini(काष्ठा radeon_device *rdev);
बाह्य bool radeon_acpi_is_pcie_perक्रमmance_request_supported(काष्ठा radeon_device *rdev);
बाह्य पूर्णांक radeon_acpi_pcie_perक्रमmance_request(काष्ठा radeon_device *rdev,
						u8 perf_req, bool advertise);
बाह्य पूर्णांक radeon_acpi_pcie_notअगरy_device_पढ़ोy(काष्ठा radeon_device *rdev);
#अन्यथा
अटल अंतरभूत पूर्णांक radeon_acpi_init(काष्ठा radeon_device *rdev) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम radeon_acpi_fini(काष्ठा radeon_device *rdev) अणु पूर्ण
#पूर्ण_अगर

पूर्णांक radeon_cs_packet_parse(काष्ठा radeon_cs_parser *p,
			   काष्ठा radeon_cs_packet *pkt,
			   अचिन्हित idx);
bool radeon_cs_packet_next_is_pkt3_nop(काष्ठा radeon_cs_parser *p);
व्योम radeon_cs_dump_packet(काष्ठा radeon_cs_parser *p,
			   काष्ठा radeon_cs_packet *pkt);
पूर्णांक radeon_cs_packet_next_reloc(काष्ठा radeon_cs_parser *p,
				काष्ठा radeon_bo_list **cs_reloc,
				पूर्णांक nomm);
पूर्णांक r600_cs_common_vline_parse(काष्ठा radeon_cs_parser *p,
			       uपूर्णांक32_t *vline_start_end,
			       uपूर्णांक32_t *vline_status);

/* पूर्णांकerrupt control रेजिस्टर helpers */
व्योम radeon_irq_kms_set_irq_n_enabled(काष्ठा radeon_device *rdev,
				      u32 reg, u32 mask,
				      bool enable, स्थिर अक्षर *name,
				      अचिन्हित n);

#समावेश "radeon_object.h"

#पूर्ण_अगर
