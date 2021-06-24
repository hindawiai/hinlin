<शैली गुरु>
/* i915_drv.h -- Private header क्रम the I915 driver -*- linux-c -*-
 */
/*
 *
 * Copyright 2003 Tungsten Graphics, Inc., Cedar Park, Texas.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
 * IN NO EVENT SHALL TUNGSTEN GRAPHICS AND/OR ITS SUPPLIERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#अगर_अघोषित _I915_DRV_H_
#घोषणा _I915_DRV_H_

#समावेश <uapi/drm/i915_drm.h>
#समावेश <uapi/drm/drm_fourcc.h>

#समावेश <यंत्र/hypervisor.h>

#समावेश <linux/io-mapping.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>
#समावेश <linux/backlight.h>
#समावेश <linux/hash.h>
#समावेश <linux/पूर्णांकel-iommu.h>
#समावेश <linux/kref.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/pm_qos.h>
#समावेश <linux/dma-resv.h>
#समावेश <linux/shmem_fs.h>
#समावेश <linux/stackdepot.h>
#समावेश <linux/xarray.h>

#समावेश <drm/पूर्णांकel-gtt.h>
#समावेश <drm/drm_legacy.h> /* क्रम काष्ठा drm_dma_handle */
#समावेश <drm/drm_gem.h>
#समावेश <drm/drm_auth.h>
#समावेश <drm/drm_cache.h>
#समावेश <drm/drm_util.h>
#समावेश <drm/drm_dsc.h>
#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_connector.h>
#समावेश <drm/i915_mei_hdcp_पूर्णांकerface.h>

#समावेश "i915_params.h"
#समावेश "i915_reg.h"
#समावेश "i915_utils.h"

#समावेश "display/intel_bios.h"
#समावेश "display/intel_display.h"
#समावेश "display/intel_display_power.h"
#समावेश "display/intel_dpll_mgr.h"
#समावेश "display/intel_dsb.h"
#समावेश "display/intel_frontbuffer.h"
#समावेश "display/intel_global_state.h"
#समावेश "display/intel_gmbus.h"
#समावेश "display/intel_opregion.h"

#समावेश "gem/i915_gem_context_types.h"
#समावेश "gem/i915_gem_shrinker.h"
#समावेश "gem/i915_gem_stolen.h"

#समावेश "gt/intel_engine.h"
#समावेश "gt/intel_gt_types.h"
#समावेश "gt/intel_region_lmem.h"
#समावेश "gt/intel_workarounds.h"
#समावेश "gt/uc/intel_uc.h"

#समावेश "intel_device_info.h"
#समावेश "intel_memory_region.h"
#समावेश "intel_pch.h"
#समावेश "intel_runtime_pm.h"
#समावेश "intel_step.h"
#समावेश "intel_uncore.h"
#समावेश "intel_wakeref.h"
#समावेश "intel_wopcm.h"

#समावेश "i915_gem.h"
#समावेश "i915_gem_gtt.h"
#समावेश "i915_gpu_error.h"
#समावेश "i915_perf_types.h"
#समावेश "i915_request.h"
#समावेश "i915_scheduler.h"
#समावेश "gt/intel_timeline.h"
#समावेश "i915_vma.h"
#समावेश "i915_irq.h"


/* General customization:
 */

#घोषणा DRIVER_NAME		"i915"
#घोषणा DRIVER_DESC		"Intel Graphics"
#घोषणा DRIVER_DATE		"20201103"
#घोषणा DRIVER_TIMESTAMP	1604406085

काष्ठा drm_i915_gem_object;

क्रमागत hpd_pin अणु
	HPD_NONE = 0,
	HPD_TV = HPD_NONE,     /* TV is known to be unreliable */
	HPD_CRT,
	HPD_SDVO_B,
	HPD_SDVO_C,
	HPD_PORT_A,
	HPD_PORT_B,
	HPD_PORT_C,
	HPD_PORT_D,
	HPD_PORT_E,
	HPD_PORT_TC1,
	HPD_PORT_TC2,
	HPD_PORT_TC3,
	HPD_PORT_TC4,
	HPD_PORT_TC5,
	HPD_PORT_TC6,

	HPD_NUM_PINS
पूर्ण;

#घोषणा क्रम_each_hpd_pin(__pin) \
	क्रम ((__pin) = (HPD_NONE + 1); (__pin) < HPD_NUM_PINS; (__pin)++)

/* Threshold == 5 क्रम दीर्घ IRQs, 50 क्रम लघु */
#घोषणा HPD_STORM_DEFAULT_THRESHOLD 50

काष्ठा i915_hotplug अणु
	काष्ठा delayed_work hotplug_work;

	स्थिर u32 *hpd, *pch_hpd;

	काष्ठा अणु
		अचिन्हित दीर्घ last_jअगरfies;
		पूर्णांक count;
		क्रमागत अणु
			HPD_ENABLED = 0,
			HPD_DISABLED = 1,
			HPD_MARK_DISABLED = 2
		पूर्ण state;
	पूर्ण stats[HPD_NUM_PINS];
	u32 event_bits;
	u32 retry_bits;
	काष्ठा delayed_work reenable_work;

	u32 दीर्घ_port_mask;
	u32 लघु_port_mask;
	काष्ठा work_काष्ठा dig_port_work;

	काष्ठा work_काष्ठा poll_init_work;
	bool poll_enabled;

	अचिन्हित पूर्णांक hpd_storm_threshold;
	/* Whether or not to count लघु HPD IRQs in HPD storms */
	u8 hpd_लघु_storm_enabled;

	/*
	 * अगर we get a HPD irq from DP and a HPD irq from non-DP
	 * the non-DP HPD could block the workqueue on a mode config
	 * mutex getting, that userspace may have taken. However
	 * userspace is रुकोing on the DP workqueue to run which is
	 * blocked behind the non-DP one.
	 */
	काष्ठा workqueue_काष्ठा *dp_wq;
पूर्ण;

#घोषणा I915_GEM_GPU_DOMAINS \
	(I915_GEM_DOMAIN_RENDER | \
	 I915_GEM_DOMAIN_SAMPLER | \
	 I915_GEM_DOMAIN_COMMAND | \
	 I915_GEM_DOMAIN_INSTRUCTION | \
	 I915_GEM_DOMAIN_VERTEX)

काष्ठा drm_i915_निजी;
काष्ठा i915_mm_काष्ठा;
काष्ठा i915_mmu_object;

काष्ठा drm_i915_file_निजी अणु
	काष्ठा drm_i915_निजी *dev_priv;

	जोड़ अणु
		काष्ठा drm_file *file;
		काष्ठा rcu_head rcu;
	पूर्ण;

	काष्ठा xarray context_xa;
	काष्ठा xarray vm_xa;

	अचिन्हित पूर्णांक bsd_engine;

/*
 * Every context ban increments per client ban score. Also
 * hangs in लघु succession increments ban score. If ban threshold
 * is reached, client is considered banned and submitting more work
 * will fail. This is a stop gap measure to limit the badly behaving
 * clients access to gpu. Note that unbannable contexts never increment
 * the client ban score.
 */
#घोषणा I915_CLIENT_SCORE_HANG_FAST	1
#घोषणा   I915_CLIENT_FAST_HANG_JIFFIES (60 * HZ)
#घोषणा I915_CLIENT_SCORE_CONTEXT_BAN   3
#घोषणा I915_CLIENT_SCORE_BANNED	9
	/** ban_score: Accumulated score of all ctx bans and fast hangs. */
	atomic_t ban_score;
	अचिन्हित दीर्घ hang_बारtamp;
पूर्ण;

/* Interface history:
 *
 * 1.1: Original.
 * 1.2: Add Power Management
 * 1.3: Add vblank support
 * 1.4: Fix cmdbuffer path, add heap destroy
 * 1.5: Add vblank pipe configuration
 * 1.6: - New ioctl क्रम scheduling buffer swaps on vertical blank
 *      - Support vertical blank on secondary display pipe
 */
#घोषणा DRIVER_MAJOR		1
#घोषणा DRIVER_MINOR		6
#घोषणा DRIVER_PATCHLEVEL	0

काष्ठा पूर्णांकel_overlay;
काष्ठा पूर्णांकel_overlay_error_state;

काष्ठा sdvo_device_mapping अणु
	u8 initialized;
	u8 dvo_port;
	u8 slave_addr;
	u8 dvo_wiring;
	u8 i2c_pin;
	u8 ddc_pin;
पूर्ण;

काष्ठा पूर्णांकel_connector;
काष्ठा पूर्णांकel_encoder;
काष्ठा पूर्णांकel_atomic_state;
काष्ठा पूर्णांकel_cdclk_config;
काष्ठा पूर्णांकel_cdclk_state;
काष्ठा पूर्णांकel_cdclk_vals;
काष्ठा पूर्णांकel_initial_plane_config;
काष्ठा पूर्णांकel_crtc;
काष्ठा पूर्णांकel_limit;
काष्ठा dpll;

काष्ठा drm_i915_display_funcs अणु
	व्योम (*get_cdclk)(काष्ठा drm_i915_निजी *dev_priv,
			  काष्ठा पूर्णांकel_cdclk_config *cdclk_config);
	व्योम (*set_cdclk)(काष्ठा drm_i915_निजी *dev_priv,
			  स्थिर काष्ठा पूर्णांकel_cdclk_config *cdclk_config,
			  क्रमागत pipe pipe);
	पूर्णांक (*bw_calc_min_cdclk)(काष्ठा पूर्णांकel_atomic_state *state);
	पूर्णांक (*get_fअगरo_size)(काष्ठा drm_i915_निजी *dev_priv,
			     क्रमागत i9xx_plane_id i9xx_plane);
	पूर्णांक (*compute_pipe_wm)(काष्ठा पूर्णांकel_crtc_state *crtc_state);
	पूर्णांक (*compute_पूर्णांकermediate_wm)(काष्ठा पूर्णांकel_crtc_state *crtc_state);
	व्योम (*initial_watermarks)(काष्ठा पूर्णांकel_atomic_state *state,
				   काष्ठा पूर्णांकel_crtc *crtc);
	व्योम (*atomic_update_watermarks)(काष्ठा पूर्णांकel_atomic_state *state,
					 काष्ठा पूर्णांकel_crtc *crtc);
	व्योम (*optimize_watermarks)(काष्ठा पूर्णांकel_atomic_state *state,
				    काष्ठा पूर्णांकel_crtc *crtc);
	पूर्णांक (*compute_global_watermarks)(काष्ठा पूर्णांकel_atomic_state *state);
	व्योम (*update_wm)(काष्ठा पूर्णांकel_crtc *crtc);
	पूर्णांक (*modeset_calc_cdclk)(काष्ठा पूर्णांकel_cdclk_state *state);
	u8 (*calc_voltage_level)(पूर्णांक cdclk);
	/* Returns the active state of the crtc, and अगर the crtc is active,
	 * fills out the pipe-config with the hw state. */
	bool (*get_pipe_config)(काष्ठा पूर्णांकel_crtc *,
				काष्ठा पूर्णांकel_crtc_state *);
	व्योम (*get_initial_plane_config)(काष्ठा पूर्णांकel_crtc *,
					 काष्ठा पूर्णांकel_initial_plane_config *);
	पूर्णांक (*crtc_compute_घड़ी)(काष्ठा पूर्णांकel_crtc *crtc,
				  काष्ठा पूर्णांकel_crtc_state *crtc_state);
	व्योम (*crtc_enable)(काष्ठा पूर्णांकel_atomic_state *state,
			    काष्ठा पूर्णांकel_crtc *crtc);
	व्योम (*crtc_disable)(काष्ठा पूर्णांकel_atomic_state *state,
			     काष्ठा पूर्णांकel_crtc *crtc);
	व्योम (*commit_modeset_enables)(काष्ठा पूर्णांकel_atomic_state *state);
	व्योम (*commit_modeset_disables)(काष्ठा पूर्णांकel_atomic_state *state);
	व्योम (*audio_codec_enable)(काष्ठा पूर्णांकel_encoder *encoder,
				   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				   स्थिर काष्ठा drm_connector_state *conn_state);
	व्योम (*audio_codec_disable)(काष्ठा पूर्णांकel_encoder *encoder,
				    स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
				    स्थिर काष्ठा drm_connector_state *old_conn_state);
	व्योम (*fdi_link_train)(काष्ठा पूर्णांकel_crtc *crtc,
			       स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
	व्योम (*init_घड़ी_gating)(काष्ठा drm_i915_निजी *dev_priv);
	व्योम (*hpd_irq_setup)(काष्ठा drm_i915_निजी *dev_priv);
	/* घड़ी updates क्रम mode set */
	/* cursor updates */
	/* render घड़ी increase/decrease */
	/* display घड़ी increase/decrease */
	/* pll घड़ी increase/decrease */

	पूर्णांक (*color_check)(काष्ठा पूर्णांकel_crtc_state *crtc_state);
	/*
	 * Program द्विगुन buffered color management रेजिस्टरs during
	 * vblank evasion. The रेजिस्टरs should then latch during the
	 * next vblank start, aदीर्घside any other द्विगुन buffered रेजिस्टरs
	 * involved with the same commit.
	 */
	व्योम (*color_commit)(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
	/*
	 * Load LUTs (and other single buffered color management
	 * रेजिस्टरs). Will (hopefully) be called during the vblank
	 * following the latching of any द्विगुन buffered रेजिस्टरs
	 * involved with the same commit.
	 */
	व्योम (*load_luts)(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
	व्योम (*पढ़ो_luts)(काष्ठा पूर्णांकel_crtc_state *crtc_state);
पूर्ण;

काष्ठा पूर्णांकel_csr अणु
	काष्ठा work_काष्ठा work;
	स्थिर अक्षर *fw_path;
	u32 required_version;
	u32 max_fw_size; /* bytes */
	u32 *dmc_payload;
	u32 dmc_fw_size; /* dwords */
	u32 version;
	u32 mmio_count;
	i915_reg_t mmioaddr[20];
	u32 mmiodata[20];
	u32 dc_state;
	u32 target_dc_state;
	u32 allowed_dc_mask;
	पूर्णांकel_wakeref_t wakeref;
पूर्ण;

क्रमागत i915_cache_level अणु
	I915_CACHE_NONE = 0,
	I915_CACHE_LLC, /* also used क्रम snoopable memory on non-LLC */
	I915_CACHE_L3_LLC, /* gen7+, L3 sits between the करोमुख्य specअगरc
			      caches, eg sampler/render caches, and the
			      large Last-Level-Cache. LLC is coherent with
			      the CPU, but L3 is only visible to the GPU. */
	I915_CACHE_WT, /* hsw:gt3e WriteThrough क्रम scanouts */
पूर्ण;

#घोषणा I915_COLOR_UNEVICTABLE (-1) /* a non-vma sharing the address space */

काष्ठा पूर्णांकel_fbc अणु
	/* This is always the inner lock when overlapping with काष्ठा_mutex and
	 * it's the outer lock when overlapping with stolen_lock. */
	काष्ठा mutex lock;
	अचिन्हित threshold;
	अचिन्हित पूर्णांक possible_framebuffer_bits;
	अचिन्हित पूर्णांक busy_bits;
	काष्ठा पूर्णांकel_crtc *crtc;

	काष्ठा drm_mm_node compressed_fb;
	काष्ठा drm_mm_node *compressed_llb;

	bool false_color;

	bool active;
	bool activated;
	bool flip_pending;

	bool underrun_detected;
	काष्ठा work_काष्ठा underrun_work;

	/*
	 * Due to the atomic rules we can't access some काष्ठाures without the
	 * appropriate locking, so we cache inक्रमmation here in order to aव्योम
	 * these problems.
	 */
	काष्ठा पूर्णांकel_fbc_state_cache अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक mode_flags;
			u32 hsw_bdw_pixel_rate;
		पूर्ण crtc;

		काष्ठा अणु
			अचिन्हित पूर्णांक rotation;
			पूर्णांक src_w;
			पूर्णांक src_h;
			bool visible;
			/*
			 * Display surface base address adjustement क्रम
			 * pageflips. Note that on gen4+ this only adjusts up
			 * to a tile, offsets within a tile are handled in
			 * the hw itself (with the TILखातापूर्णF रेजिस्टर).
			 */
			पूर्णांक adjusted_x;
			पूर्णांक adjusted_y;

			u16 pixel_blend_mode;
		पूर्ण plane;

		काष्ठा अणु
			स्थिर काष्ठा drm_क्रमmat_info *क्रमmat;
			अचिन्हित पूर्णांक stride;
			u64 modअगरier;
		पूर्ण fb;

		अचिन्हित पूर्णांक fence_y_offset;
		u16 gen9_wa_cfb_stride;
		u16 पूर्णांकerval;
		s8 fence_id;
		bool psr2_active;
	पूर्ण state_cache;

	/*
	 * This काष्ठाure contains everything that's relevant to program the
	 * hardware रेजिस्टरs. When we want to figure out अगर we need to disable
	 * and re-enable FBC क्रम a new configuration we just check अगर there's
	 * something dअगरferent in the काष्ठा. The genx_fbc_activate functions
	 * are supposed to पढ़ो from it in order to program the रेजिस्टरs.
	 */
	काष्ठा पूर्णांकel_fbc_reg_params अणु
		काष्ठा अणु
			क्रमागत pipe pipe;
			क्रमागत i9xx_plane_id i9xx_plane;
		पूर्ण crtc;

		काष्ठा अणु
			स्थिर काष्ठा drm_क्रमmat_info *क्रमmat;
			अचिन्हित पूर्णांक stride;
			u64 modअगरier;
		पूर्ण fb;

		पूर्णांक cfb_size;
		अचिन्हित पूर्णांक fence_y_offset;
		u16 gen9_wa_cfb_stride;
		u16 पूर्णांकerval;
		s8 fence_id;
		bool plane_visible;
	पूर्ण params;

	स्थिर अक्षर *no_fbc_reason;
पूर्ण;

/*
 * HIGH_RR is the highest eDP panel refresh rate पढ़ो from EDID
 * LOW_RR is the lowest eDP panel refresh rate found from EDID
 * parsing क्रम same resolution.
 */
क्रमागत drrs_refresh_rate_type अणु
	DRRS_HIGH_RR,
	DRRS_LOW_RR,
	DRRS_MAX_RR, /* RR count */
पूर्ण;

क्रमागत drrs_support_type अणु
	DRRS_NOT_SUPPORTED = 0,
	STATIC_DRRS_SUPPORT = 1,
	SEAMLESS_DRRS_SUPPORT = 2
पूर्ण;

काष्ठा पूर्णांकel_dp;
काष्ठा i915_drrs अणु
	काष्ठा mutex mutex;
	काष्ठा delayed_work work;
	काष्ठा पूर्णांकel_dp *dp;
	अचिन्हित busy_frontbuffer_bits;
	क्रमागत drrs_refresh_rate_type refresh_rate_type;
	क्रमागत drrs_support_type type;
पूर्ण;

#घोषणा QUIRK_LVDS_SSC_DISABLE (1<<1)
#घोषणा QUIRK_INVERT_BRIGHTNESS (1<<2)
#घोषणा QUIRK_BACKLIGHT_PRESENT (1<<3)
#घोषणा QUIRK_PIN_SWIZZLED_PAGES (1<<5)
#घोषणा QUIRK_INCREASE_T12_DELAY (1<<6)
#घोषणा QUIRK_INCREASE_DDI_DISABLED_TIME (1<<7)

काष्ठा पूर्णांकel_fbdev;
काष्ठा पूर्णांकel_fbc_work;

काष्ठा पूर्णांकel_gmbus अणु
	काष्ठा i2c_adapter adapter;
#घोषणा GMBUS_FORCE_BIT_RETRY (1U << 31)
	u32 क्रमce_bit;
	u32 reg0;
	i915_reg_t gpio_reg;
	काष्ठा i2c_algo_bit_data bit_algo;
	काष्ठा drm_i915_निजी *dev_priv;
पूर्ण;

काष्ठा i915_suspend_saved_रेजिस्टरs अणु
	u32 saveDSPARB;
	u32 saveSWF0[16];
	u32 saveSWF1[16];
	u32 saveSWF3[3];
	u16 saveGCDGMBUS;
पूर्ण;

काष्ठा vlv_s0ix_state;

#घोषणा MAX_L3_SLICES 2
काष्ठा पूर्णांकel_l3_parity अणु
	u32 *remap_info[MAX_L3_SLICES];
	काष्ठा work_काष्ठा error_work;
	पूर्णांक which_slice;
पूर्ण;

काष्ठा i915_gem_mm अणु
	/** Memory allocator क्रम GTT stolen memory */
	काष्ठा drm_mm stolen;
	/** Protects the usage of the GTT stolen memory allocator. This is
	 * always the inner lock when overlapping with काष्ठा_mutex. */
	काष्ठा mutex stolen_lock;

	/* Protects bound_list/unbound_list and #drm_i915_gem_object.mm.link */
	spinlock_t obj_lock;

	/**
	 * List of objects which are purgeable.
	 */
	काष्ठा list_head purge_list;

	/**
	 * List of objects which have allocated pages and are shrinkable.
	 */
	काष्ठा list_head shrink_list;

	/**
	 * List of objects which are pending deकाष्ठाion.
	 */
	काष्ठा llist_head मुक्त_list;
	काष्ठा work_काष्ठा मुक्त_work;
	/**
	 * Count of objects pending deकाष्ठाions. Used to skip needlessly
	 * रुकोing on an RCU barrier अगर no objects are रुकोing to be मुक्तd.
	 */
	atomic_t मुक्त_count;

	/**
	 * पंचांगpfs instance used क्रम shmem backed objects
	 */
	काष्ठा vfsmount *gemfs;

	काष्ठा पूर्णांकel_memory_region *regions[INTEL_REGION_UNKNOWN];

	काष्ठा notअगरier_block oom_notअगरier;
	काष्ठा notअगरier_block vmap_notअगरier;
	काष्ठा shrinker shrinker;

#अगर_घोषित CONFIG_MMU_NOTIFIER
	/**
	 * notअगरier_lock क्रम mmu notअगरiers, memory may not be allocated
	 * जबतक holding this lock.
	 */
	spinlock_t notअगरier_lock;
#पूर्ण_अगर

	/* shrinker accounting, also useful क्रम userland debugging */
	u64 shrink_memory;
	u32 shrink_count;
पूर्ण;

#घोषणा I915_IDLE_ENGINES_TIMEOUT (200) /* in ms */

अचिन्हित दीर्घ i915_fence_context_समयout(स्थिर काष्ठा drm_i915_निजी *i915,
					 u64 context);

अटल अंतरभूत अचिन्हित दीर्घ
i915_fence_समयout(स्थिर काष्ठा drm_i915_निजी *i915)
अणु
	वापस i915_fence_context_समयout(i915, U64_MAX);
पूर्ण

/* Amount of SAGV/QGV poपूर्णांकs, BSpec precisely defines this */
#घोषणा I915_NUM_QGV_POINTS 8

काष्ठा ddi_vbt_port_info अणु
	/* Non-शून्य अगर port present. */
	काष्ठा पूर्णांकel_bios_encoder_data *devdata;

	पूर्णांक max_पंचांगds_घड़ी;

	/* This is an index in the HDMI/DVI DDI buffer translation table. */
	u8 hdmi_level_shअगरt;
	u8 hdmi_level_shअगरt_set:1;

	u8 alternate_aux_channel;
	u8 alternate_ddc_pin;

	पूर्णांक dp_max_link_rate;		/* 0 क्रम not limited by VBT */
पूर्ण;

क्रमागत psr_lines_to_रुको अणु
	PSR_0_LINES_TO_WAIT = 0,
	PSR_1_LINE_TO_WAIT,
	PSR_4_LINES_TO_WAIT,
	PSR_8_LINES_TO_WAIT
पूर्ण;

काष्ठा पूर्णांकel_vbt_data अणु
	/* bdb version */
	u16 version;

	काष्ठा drm_display_mode *lfp_lvds_vbt_mode; /* अगर any */
	काष्ठा drm_display_mode *sdvo_lvds_vbt_mode; /* अगर any */

	/* Feature bits */
	अचिन्हित पूर्णांक पूर्णांक_tv_support:1;
	अचिन्हित पूर्णांक lvds_dither:1;
	अचिन्हित पूर्णांक पूर्णांक_crt_support:1;
	अचिन्हित पूर्णांक lvds_use_ssc:1;
	अचिन्हित पूर्णांक पूर्णांक_lvds_support:1;
	अचिन्हित पूर्णांक display_घड़ी_mode:1;
	अचिन्हित पूर्णांक fdi_rx_polarity_inverted:1;
	अचिन्हित पूर्णांक panel_type:4;
	पूर्णांक lvds_ssc_freq;
	अचिन्हित पूर्णांक bios_lvds_val; /* initial [PCH_]LVDS reg val in VBIOS */
	क्रमागत drm_panel_orientation orientation;

	क्रमागत drrs_support_type drrs_type;

	काष्ठा अणु
		पूर्णांक rate;
		पूर्णांक lanes;
		पूर्णांक preemphasis;
		पूर्णांक vswing;
		bool low_vswing;
		bool initialized;
		पूर्णांक bpp;
		काष्ठा edp_घातer_seq pps;
		bool hobl;
	पूर्ण edp;

	काष्ठा अणु
		bool enable;
		bool full_link;
		bool require_aux_wakeup;
		पूर्णांक idle_frames;
		क्रमागत psr_lines_to_रुको lines_to_रुको;
		पूर्णांक tp1_wakeup_समय_us;
		पूर्णांक tp2_tp3_wakeup_समय_us;
		पूर्णांक psr2_tp2_tp3_wakeup_समय_us;
	पूर्ण psr;

	काष्ठा अणु
		u16 pwm_freq_hz;
		bool present;
		bool active_low_pwm;
		u8 min_brightness;	/* min_brightness/255 of max */
		u8 controller;		/* brightness controller number */
		क्रमागत पूर्णांकel_backlight_type type;
	पूर्ण backlight;

	/* MIPI DSI */
	काष्ठा अणु
		u16 panel_id;
		काष्ठा mipi_config *config;
		काष्ठा mipi_pps_data *pps;
		u16 bl_ports;
		u16 cabc_ports;
		u8 seq_version;
		u32 size;
		u8 *data;
		स्थिर u8 *sequence[MIPI_SEQ_MAX];
		u8 *deनिश्चित_seq; /* Used by fixup_mipi_sequences() */
		क्रमागत drm_panel_orientation orientation;
	पूर्ण dsi;

	पूर्णांक crt_ddc_pin;

	काष्ठा list_head display_devices;

	काष्ठा ddi_vbt_port_info ddi_port_info[I915_MAX_PORTS];
	काष्ठा sdvo_device_mapping sdvo_mappings[2];
पूर्ण;

क्रमागत पूर्णांकel_ddb_partitioning अणु
	INTEL_DDB_PART_1_2,
	INTEL_DDB_PART_5_6, /* IVB+ */
पूर्ण;

काष्ठा ilk_wm_values अणु
	u32 wm_pipe[3];
	u32 wm_lp[3];
	u32 wm_lp_spr[3];
	bool enable_fbc_wm;
	क्रमागत पूर्णांकel_ddb_partitioning partitioning;
पूर्ण;

काष्ठा g4x_pipe_wm अणु
	u16 plane[I915_MAX_PLANES];
	u16 fbc;
पूर्ण;

काष्ठा g4x_sr_wm अणु
	u16 plane;
	u16 cursor;
	u16 fbc;
पूर्ण;

काष्ठा vlv_wm_ddl_values अणु
	u8 plane[I915_MAX_PLANES];
पूर्ण;

काष्ठा vlv_wm_values अणु
	काष्ठा g4x_pipe_wm pipe[3];
	काष्ठा g4x_sr_wm sr;
	काष्ठा vlv_wm_ddl_values ddl[3];
	u8 level;
	bool cxsr;
पूर्ण;

काष्ठा g4x_wm_values अणु
	काष्ठा g4x_pipe_wm pipe[2];
	काष्ठा g4x_sr_wm sr;
	काष्ठा g4x_sr_wm hpll;
	bool cxsr;
	bool hpll_en;
	bool fbc_en;
पूर्ण;

काष्ठा skl_ddb_entry अणु
	u16 start, end;	/* in number of blocks, 'end' is exclusive */
पूर्ण;

अटल अंतरभूत u16 skl_ddb_entry_size(स्थिर काष्ठा skl_ddb_entry *entry)
अणु
	वापस entry->end - entry->start;
पूर्ण

अटल अंतरभूत bool skl_ddb_entry_equal(स्थिर काष्ठा skl_ddb_entry *e1,
				       स्थिर काष्ठा skl_ddb_entry *e2)
अणु
	अगर (e1->start == e2->start && e1->end == e2->end)
		वापस true;

	वापस false;
पूर्ण

काष्ठा i915_frontbuffer_tracking अणु
	spinlock_t lock;

	/*
	 * Tracking bits क्रम delayed frontbuffer flushing du to gpu activity or
	 * scheduled flips.
	 */
	अचिन्हित busy_bits;
	अचिन्हित flip_bits;
पूर्ण;

काष्ठा i915_भव_gpu अणु
	काष्ठा mutex lock; /* serialises sending of g2v_notअगरy command pkts */
	bool active;
	u32 caps;
पूर्ण;

काष्ठा पूर्णांकel_cdclk_config अणु
	अचिन्हित पूर्णांक cdclk, vco, ref, bypass;
	u8 voltage_level;
पूर्ण;

काष्ठा i915_selftest_stash अणु
	atomic_t counter;
पूर्ण;

काष्ठा drm_i915_निजी अणु
	काष्ठा drm_device drm;

	/* FIXME: Device release actions should all be moved to drmm_ */
	bool करो_release;

	/* i915 device parameters */
	काष्ठा i915_params params;

	स्थिर काष्ठा पूर्णांकel_device_info __info; /* Use INTEL_INFO() to access. */
	काष्ठा पूर्णांकel_runसमय_info __runसमय; /* Use RUNTIME_INFO() to access. */
	काष्ठा पूर्णांकel_driver_caps caps;

	/**
	 * Data Stolen Memory - aka "i915 stolen memory" gives us the start and
	 * end of stolen which we can optionally use to create GEM objects
	 * backed by stolen memory. Note that stolen_usable_size tells us
	 * exactly how much of this we are actually allowed to use, given that
	 * some portion of it is in fact reserved क्रम use by hardware functions.
	 */
	काष्ठा resource dsm;
	/**
	 * Reseved portion of Data Stolen Memory
	 */
	काष्ठा resource dsm_reserved;

	/*
	 * Stolen memory is segmented in hardware with dअगरferent portions
	 * offlimits to certain functions.
	 *
	 * The drm_mm is initialised to the total accessible range, as found
	 * from the PCI config. On Broadwell+, this is further restricted to
	 * aव्योम the first page! The upper end of stolen memory is reserved क्रम
	 * hardware functions and similarly हटाओd from the accessible range.
	 */
	resource_माप_प्रकार stolen_usable_size;	/* Total size minus reserved ranges */

	काष्ठा पूर्णांकel_uncore uncore;
	काष्ठा पूर्णांकel_uncore_mmio_debug mmio_debug;

	काष्ठा i915_भव_gpu vgpu;

	काष्ठा पूर्णांकel_gvt *gvt;

	काष्ठा पूर्णांकel_wopcm wopcm;

	काष्ठा पूर्णांकel_csr csr;

	काष्ठा पूर्णांकel_gmbus gmbus[GMBUS_NUM_PINS];

	/** gmbus_mutex protects against concurrent usage of the single hw gmbus
	 * controller on dअगरferent i2c buses. */
	काष्ठा mutex gmbus_mutex;

	/**
	 * Base address of where the gmbus and gpio blocks are located (either
	 * on PCH or on SoC क्रम platक्रमms without PCH).
	 */
	u32 gpio_mmio_base;

	u32 hsw_psr_mmio_adjust;

	/* MMIO base address क्रम MIPI regs */
	u32 mipi_mmio_base;

	u32 pps_mmio_base;

	रुको_queue_head_t gmbus_रुको_queue;

	काष्ठा pci_dev *bridge_dev;

	काष्ठा rb_root uabi_engines;

	काष्ठा resource mch_res;

	/* protects the irq masks */
	spinlock_t irq_lock;

	bool display_irqs_enabled;

	/* Sideband mailbox protection */
	काष्ठा mutex sb_lock;
	काष्ठा pm_qos_request sb_qos;

	/** Cached value of IMR to aव्योम पढ़ोs in updating the bitfield */
	जोड़ अणु
		u32 irq_mask;
		u32 de_irq_mask[I915_MAX_PIPES];
	पूर्ण;
	u32 pipestat_irq_mask[I915_MAX_PIPES];

	काष्ठा i915_hotplug hotplug;
	काष्ठा पूर्णांकel_fbc fbc;
	काष्ठा i915_drrs drrs;
	काष्ठा पूर्णांकel_opregion opregion;
	काष्ठा पूर्णांकel_vbt_data vbt;

	bool preserve_bios_swizzle;

	/* overlay */
	काष्ठा पूर्णांकel_overlay *overlay;

	/* backlight रेजिस्टरs and fields in काष्ठा पूर्णांकel_panel */
	काष्ठा mutex backlight_lock;

	/* protects panel घातer sequencer state */
	काष्ठा mutex pps_mutex;

	अचिन्हित पूर्णांक fsb_freq, mem_freq, is_ddr3;
	अचिन्हित पूर्णांक skl_preferred_vco_freq;
	अचिन्हित पूर्णांक max_cdclk_freq;

	अचिन्हित पूर्णांक max_करोtclk_freq;
	अचिन्हित पूर्णांक hpll_freq;
	अचिन्हित पूर्णांक fdi_pll_freq;
	अचिन्हित पूर्णांक czclk_freq;

	काष्ठा अणु
		/* The current hardware cdclk configuration */
		काष्ठा पूर्णांकel_cdclk_config hw;

		/* cdclk, भागider, and ratio table from bspec */
		स्थिर काष्ठा पूर्णांकel_cdclk_vals *table;

		काष्ठा पूर्णांकel_global_obj obj;
	पूर्ण cdclk;

	काष्ठा अणु
		/* The current hardware dbuf configuration */
		u8 enabled_slices;

		काष्ठा पूर्णांकel_global_obj obj;
	पूर्ण dbuf;

	/**
	 * wq - Driver workqueue क्रम GEM.
	 *
	 * NOTE: Work items scheduled here are not allowed to grab any modeset
	 * locks, क्रम otherwise the flushing करोne in the pageflip code will
	 * result in deadlocks.
	 */
	काष्ठा workqueue_काष्ठा *wq;

	/* ordered wq क्रम modesets */
	काष्ठा workqueue_काष्ठा *modeset_wq;
	/* unbound hipri wq क्रम page flips/plane updates */
	काष्ठा workqueue_काष्ठा *flip_wq;

	/* Display functions */
	काष्ठा drm_i915_display_funcs display;

	/* PCH chipset type */
	क्रमागत पूर्णांकel_pch pch_type;
	अचिन्हित लघु pch_id;

	अचिन्हित दीर्घ quirks;

	काष्ठा drm_atomic_state *modeset_restore_state;
	काष्ठा drm_modeset_acquire_ctx reset_ctx;

	काष्ठा i915_ggtt ggtt; /* VM representing the global address space */

	काष्ठा i915_gem_mm mm;

	/* Kernel Modesetting */

	काष्ठा पूर्णांकel_crtc *plane_to_crtc_mapping[I915_MAX_PIPES];
	काष्ठा पूर्णांकel_crtc *pipe_to_crtc_mapping[I915_MAX_PIPES];

	/**
	 * dpll and cdclk state is रक्षित by connection_mutex
	 * dpll.lock serializes पूर्णांकel_अणुprepare,enable,disableपूर्ण_shared_dpll.
	 * Must be global rather than per dpll, because on some platक्रमms plls
	 * share रेजिस्टरs.
	 */
	काष्ठा अणु
		काष्ठा mutex lock;

		पूर्णांक num_shared_dpll;
		काष्ठा पूर्णांकel_shared_dpll shared_dplls[I915_NUM_PLLS];
		स्थिर काष्ठा पूर्णांकel_dpll_mgr *mgr;

		काष्ठा अणु
			पूर्णांक nssc;
			पूर्णांक ssc;
		पूर्ण ref_clks;
	पूर्ण dpll;

	काष्ठा list_head global_obj_list;

	/*
	 * For पढ़ोing active_pipes holding any crtc lock is
	 * sufficient, क्रम writing must hold all of them.
	 */
	u8 active_pipes;

	काष्ठा i915_wa_list gt_wa_list;

	काष्ठा i915_frontbuffer_tracking fb_tracking;

	काष्ठा पूर्णांकel_atomic_helper अणु
		काष्ठा llist_head मुक्त_list;
		काष्ठा work_काष्ठा मुक्त_work;
	पूर्ण atomic_helper;

	bool mchbar_need_disable;

	काष्ठा पूर्णांकel_l3_parity l3_parity;

	/*
	 * HTI (aka HDPORT) state पढ़ो during initial hw पढ़ोout.  Most
	 * platक्रमms करोn't have HTI, so this will just stay 0.  Those that करो
	 * will use this later to figure out which PLLs and PHYs are unavailable
	 * क्रम driver usage.
	 */
	u32 hti_state;

	/*
	 * edram size in MB.
	 * Cannot be determined by PCIID. You must always पढ़ो a रेजिस्टर.
	 */
	u32 edram_size_mb;

	काष्ठा i915_घातer_करोमुख्यs घातer_करोमुख्यs;

	काष्ठा i915_gpu_error gpu_error;

	काष्ठा drm_i915_gem_object *vlv_pctx;

	/* list of fbdev रेजिस्टर on this device */
	काष्ठा पूर्णांकel_fbdev *fbdev;
	काष्ठा work_काष्ठा fbdev_suspend_work;

	काष्ठा drm_property *broadcast_rgb_property;
	काष्ठा drm_property *क्रमce_audio_property;

	/* hda/i915 audio component */
	काष्ठा i915_audio_component *audio_component;
	bool audio_component_रेजिस्टरed;
	/**
	 * av_mutex - mutex क्रम audio/video sync
	 *
	 */
	काष्ठा mutex av_mutex;
	पूर्णांक audio_घातer_refcount;
	u32 audio_freq_cntrl;

	u32 fdi_rx_config;

	/* Shaकरोw क्रम DISPLAY_PHY_CONTROL which can't be safely पढ़ो */
	u32 chv_phy_control;
	/*
	 * Shaकरोws क्रम CHV DPLL_MD regs to keep the state
	 * checker somewhat working in the presence hardware
	 * crappiness (can't पढ़ो out DPLL_MD क्रम pipes B & C).
	 */
	u32 chv_dpll_md[I915_MAX_PIPES];
	u32 bxt_phy_grc;

	u32 suspend_count;
	bool घातer_करोमुख्यs_suspended;
	काष्ठा i915_suspend_saved_रेजिस्टरs regfile;
	काष्ठा vlv_s0ix_state *vlv_s0ix_state;

	क्रमागत अणु
		I915_SAGV_UNKNOWN = 0,
		I915_SAGV_DISABLED,
		I915_SAGV_ENABLED,
		I915_SAGV_NOT_CONTROLLED
	पूर्ण sagv_status;

	u32 sagv_block_समय_us;

	काष्ठा अणु
		/*
		 * Raw watermark latency values:
		 * in 0.1us units क्रम WM0,
		 * in 0.5us units क्रम WM1+.
		 */
		/* primary */
		u16 pri_latency[5];
		/* sprite */
		u16 spr_latency[5];
		/* cursor */
		u16 cur_latency[5];
		/*
		 * Raw watermark memory latency values
		 * क्रम SKL क्रम all 8 levels
		 * in 1us units.
		 */
		u16 skl_latency[8];

		/* current hardware state */
		जोड़ अणु
			काष्ठा ilk_wm_values hw;
			काष्ठा vlv_wm_values vlv;
			काष्ठा g4x_wm_values g4x;
		पूर्ण;

		u8 max_level;

		/*
		 * Should be held around atomic WM रेजिस्टर writing; also
		 * protects * पूर्णांकel_crtc->wm.active and
		 * crtc_state->wm.need_postvbl_update.
		 */
		काष्ठा mutex wm_mutex;
	पूर्ण wm;

	काष्ठा dram_info अणु
		bool wm_lv_0_adjust_needed;
		u8 num_channels;
		bool symmetric_memory;
		क्रमागत पूर्णांकel_dram_type अणु
			INTEL_DRAM_UNKNOWN,
			INTEL_DRAM_DDR3,
			INTEL_DRAM_DDR4,
			INTEL_DRAM_LPDDR3,
			INTEL_DRAM_LPDDR4,
			INTEL_DRAM_DDR5,
			INTEL_DRAM_LPDDR5,
		पूर्ण type;
		u8 num_qgv_poपूर्णांकs;
	पूर्ण dram_info;

	काष्ठा पूर्णांकel_bw_info अणु
		/* क्रम each QGV poपूर्णांक */
		अचिन्हित पूर्णांक deratedbw[I915_NUM_QGV_POINTS];
		u8 num_qgv_poपूर्णांकs;
		u8 num_planes;
	पूर्ण max_bw[6];

	काष्ठा पूर्णांकel_global_obj bw_obj;

	काष्ठा पूर्णांकel_runसमय_pm runसमय_pm;

	काष्ठा i915_perf perf;

	/* Abstract the submission mechanism (legacy ringbuffer or execlists) away */
	काष्ठा पूर्णांकel_gt gt;

	काष्ठा अणु
		काष्ठा i915_gem_contexts अणु
			spinlock_t lock; /* locks list */
			काष्ठा list_head list;
		पूर्ण contexts;

		/*
		 * We replace the local file with a global mappings as the
		 * backing storage क्रम the mmap is on the device and not
		 * on the काष्ठा file, and we करो not want to proदीर्घ the
		 * lअगरeसमय of the local fd. To minimise the number of
		 * anonymous inodes we create, we use a global singleton to
		 * share the global mapping.
		 */
		काष्ठा file *mmap_singleton;
	पूर्ण gem;

	u8 framestart_delay;

	u8 pch_ssc_use;

	/* For i915gm/i945gm vblank irq workaround */
	u8 vblank_enabled;

	/* perक्रमm PHY state sanity checks? */
	bool chv_phy_निश्चित[2];

	bool ipc_enabled;

	/* Used to save the pipe-to-encoder mapping क्रम audio */
	काष्ठा पूर्णांकel_encoder *av_enc_map[I915_MAX_PIPES];

	/* necessary resource sharing with HDMI LPE audio driver. */
	काष्ठा अणु
		काष्ठा platक्रमm_device *platdev;
		पूर्णांक	irq;
	पूर्ण lpe_audio;

	काष्ठा i915_pmu pmu;

	काष्ठा i915_hdcp_comp_master *hdcp_master;
	bool hdcp_comp_added;

	/* Mutex to protect the above hdcp component related values. */
	काष्ठा mutex hdcp_comp_mutex;

	I915_SELFTEST_DECLARE(काष्ठा i915_selftest_stash selftest;)

	/*
	 * NOTE: This is the dri1/ums dungeon, करोn't add stuff here. Your patch
	 * will be rejected. Instead look क्रम a better place.
	 */
पूर्ण;

अटल अंतरभूत काष्ठा drm_i915_निजी *to_i915(स्थिर काष्ठा drm_device *dev)
अणु
	वापस container_of(dev, काष्ठा drm_i915_निजी, drm);
पूर्ण

अटल अंतरभूत काष्ठा drm_i915_निजी *kdev_to_i915(काष्ठा device *kdev)
अणु
	वापस dev_get_drvdata(kdev);
पूर्ण

अटल अंतरभूत काष्ठा drm_i915_निजी *pdev_to_i915(काष्ठा pci_dev *pdev)
अणु
	वापस pci_get_drvdata(pdev);
पूर्ण

/* Simple iterator over all initialised engines */
#घोषणा क्रम_each_engine(engine__, dev_priv__, id__) \
	क्रम ((id__) = 0; \
	     (id__) < I915_NUM_ENGINES; \
	     (id__)++) \
		क्रम_each_अगर ((engine__) = (dev_priv__)->engine[(id__)])

/* Iterator over subset of engines selected by mask */
#घोषणा क्रम_each_engine_masked(engine__, gt__, mask__, पंचांगp__) \
	क्रम ((पंचांगp__) = (mask__) & (gt__)->info.engine_mask; \
	     (पंचांगp__) ? \
	     ((engine__) = (gt__)->engine[__mask_next_bit(पंचांगp__)]), 1 : \
	     0;)

#घोषणा rb_to_uabi_engine(rb) \
	rb_entry_safe(rb, काष्ठा पूर्णांकel_engine_cs, uabi_node)

#घोषणा क्रम_each_uabi_engine(engine__, i915__) \
	क्रम ((engine__) = rb_to_uabi_engine(rb_first(&(i915__)->uabi_engines));\
	     (engine__); \
	     (engine__) = rb_to_uabi_engine(rb_next(&(engine__)->uabi_node)))

#घोषणा क्रम_each_uabi_class_engine(engine__, class__, i915__) \
	क्रम ((engine__) = पूर्णांकel_engine_lookup_user((i915__), (class__), 0); \
	     (engine__) && (engine__)->uabi_class == (class__); \
	     (engine__) = rb_to_uabi_engine(rb_next(&(engine__)->uabi_node)))

#घोषणा I915_GTT_OFFSET_NONE ((u32)-1)

/*
 * Frontbuffer tracking bits. Set in obj->frontbuffer_bits जबतक a gem bo is
 * considered to be the frontbuffer क्रम the given plane पूर्णांकerface-wise. This
 * करोesn't mean that the hw necessarily alपढ़ोy scans it out, but that any
 * rendering (by the cpu or gpu) will land in the frontbuffer eventually.
 *
 * We have one bit per pipe and per scanout plane type.
 */
#घोषणा INTEL_FRONTBUFFER_BITS_PER_PIPE 8
#घोषणा INTEL_FRONTBUFFER(pipe, plane_id) (अणु \
	BUILD_BUG_ON(INTEL_FRONTBUFFER_BITS_PER_PIPE * I915_MAX_PIPES > 32); \
	BUILD_BUG_ON(I915_MAX_PLANES > INTEL_FRONTBUFFER_BITS_PER_PIPE); \
	BIT((plane_id) + INTEL_FRONTBUFFER_BITS_PER_PIPE * (pipe)); \
पूर्ण)
#घोषणा INTEL_FRONTBUFFER_OVERLAY(pipe) \
	BIT(INTEL_FRONTBUFFER_BITS_PER_PIPE - 1 + INTEL_FRONTBUFFER_BITS_PER_PIPE * (pipe))
#घोषणा INTEL_FRONTBUFFER_ALL_MASK(pipe) \
	GENMASK(INTEL_FRONTBUFFER_BITS_PER_PIPE * ((pipe) + 1) - 1, \
		INTEL_FRONTBUFFER_BITS_PER_PIPE * (pipe))

#घोषणा INTEL_INFO(dev_priv)	(&(dev_priv)->__info)
#घोषणा RUNTIME_INFO(dev_priv)	(&(dev_priv)->__runसमय)
#घोषणा DRIVER_CAPS(dev_priv)	(&(dev_priv)->caps)

#घोषणा INTEL_GEN(dev_priv)	(INTEL_INFO(dev_priv)->gen)
#घोषणा INTEL_DEVID(dev_priv)	(RUNTIME_INFO(dev_priv)->device_id)

#घोषणा DISPLAY_VER(i915)	(INTEL_INFO(i915)->display.version)
#घोषणा IS_DISPLAY_RANGE(i915, from, until) \
	(DISPLAY_VER(i915) >= (from) && DISPLAY_VER(i915) <= (until))
#घोषणा IS_DISPLAY_VER(i915, v) (DISPLAY_VER(i915) == (v))

#घोषणा REVID_FOREVER		0xff
#घोषणा INTEL_REVID(dev_priv)	(to_pci_dev((dev_priv)->drm.dev)->revision)

#घोषणा INTEL_GEN_MASK(s, e) ( \
	BUILD_BUG_ON_ZERO(!__builtin_स्थिरant_p(s)) + \
	BUILD_BUG_ON_ZERO(!__builtin_स्थिरant_p(e)) + \
	GENMASK((e) - 1, (s) - 1))

/* Returns true अगर Gen is in inclusive range [Start, End] */
#घोषणा IS_GEN_RANGE(dev_priv, s, e) \
	(!!(INTEL_INFO(dev_priv)->gen_mask & INTEL_GEN_MASK((s), (e))))

#घोषणा IS_GEN(dev_priv, n) \
	(BUILD_BUG_ON_ZERO(!__builtin_स्थिरant_p(n)) + \
	 INTEL_INFO(dev_priv)->gen == (n))

#घोषणा HAS_DSB(dev_priv)	(INTEL_INFO(dev_priv)->display.has_dsb)

/*
 * Return true अगर revision is in range [since,until] inclusive.
 *
 * Use 0 क्रम खोलो-ended since, and REVID_FOREVER क्रम खोलो-ended until.
 */
#घोषणा IS_REVID(p, since, until) \
	(INTEL_REVID(p) >= (since) && INTEL_REVID(p) <= (until))

#घोषणा INTEL_DISPLAY_STEP(__i915) (RUNTIME_INFO(__i915)->step.display_step)
#घोषणा INTEL_GT_STEP(__i915) (RUNTIME_INFO(__i915)->step.gt_step)

#घोषणा IS_DISPLAY_STEP(__i915, since, until) \
	(drm_WARN_ON(&(__i915)->drm, INTEL_DISPLAY_STEP(__i915) == STEP_NONE), \
	 INTEL_DISPLAY_STEP(__i915) >= (since) && INTEL_DISPLAY_STEP(__i915) <= (until))

#घोषणा IS_GT_STEP(__i915, since, until) \
	(drm_WARN_ON(&(__i915)->drm, INTEL_GT_STEP(__i915) == STEP_NONE), \
	 INTEL_GT_STEP(__i915) >= (since) && INTEL_GT_STEP(__i915) <= (until))

अटल __always_अंतरभूत अचिन्हित पूर्णांक
__platक्रमm_mask_index(स्थिर काष्ठा पूर्णांकel_runसमय_info *info,
		      क्रमागत पूर्णांकel_platक्रमm p)
अणु
	स्थिर अचिन्हित पूर्णांक pbits =
		BITS_PER_TYPE(info->platक्रमm_mask[0]) - INTEL_SUBPLATFORM_BITS;

	/* Expand the platक्रमm_mask array अगर this fails. */
	BUILD_BUG_ON(INTEL_MAX_PLATFORMS >
		     pbits * ARRAY_SIZE(info->platक्रमm_mask));

	वापस p / pbits;
पूर्ण

अटल __always_अंतरभूत अचिन्हित पूर्णांक
__platक्रमm_mask_bit(स्थिर काष्ठा पूर्णांकel_runसमय_info *info,
		    क्रमागत पूर्णांकel_platक्रमm p)
अणु
	स्थिर अचिन्हित पूर्णांक pbits =
		BITS_PER_TYPE(info->platक्रमm_mask[0]) - INTEL_SUBPLATFORM_BITS;

	वापस p % pbits + INTEL_SUBPLATFORM_BITS;
पूर्ण

अटल अंतरभूत u32
पूर्णांकel_subplatक्रमm(स्थिर काष्ठा पूर्णांकel_runसमय_info *info, क्रमागत पूर्णांकel_platक्रमm p)
अणु
	स्थिर अचिन्हित पूर्णांक pi = __platक्रमm_mask_index(info, p);

	वापस info->platक्रमm_mask[pi] & INTEL_SUBPLATFORM_MASK;
पूर्ण

अटल __always_अंतरभूत bool
IS_PLATFORM(स्थिर काष्ठा drm_i915_निजी *i915, क्रमागत पूर्णांकel_platक्रमm p)
अणु
	स्थिर काष्ठा पूर्णांकel_runसमय_info *info = RUNTIME_INFO(i915);
	स्थिर अचिन्हित पूर्णांक pi = __platक्रमm_mask_index(info, p);
	स्थिर अचिन्हित पूर्णांक pb = __platक्रमm_mask_bit(info, p);

	BUILD_BUG_ON(!__builtin_स्थिरant_p(p));

	वापस info->platक्रमm_mask[pi] & BIT(pb);
पूर्ण

अटल __always_अंतरभूत bool
IS_SUBPLATFORM(स्थिर काष्ठा drm_i915_निजी *i915,
	       क्रमागत पूर्णांकel_platक्रमm p, अचिन्हित पूर्णांक s)
अणु
	स्थिर काष्ठा पूर्णांकel_runसमय_info *info = RUNTIME_INFO(i915);
	स्थिर अचिन्हित पूर्णांक pi = __platक्रमm_mask_index(info, p);
	स्थिर अचिन्हित पूर्णांक pb = __platक्रमm_mask_bit(info, p);
	स्थिर अचिन्हित पूर्णांक msb = BITS_PER_TYPE(info->platक्रमm_mask[0]) - 1;
	स्थिर u32 mask = info->platक्रमm_mask[pi];

	BUILD_BUG_ON(!__builtin_स्थिरant_p(p));
	BUILD_BUG_ON(!__builtin_स्थिरant_p(s));
	BUILD_BUG_ON((s) >= INTEL_SUBPLATFORM_BITS);

	/* Shअगरt and test on the MSB position so sign flag can be used. */
	वापस ((mask << (msb - pb)) & (mask << (msb - s))) & BIT(msb);
पूर्ण

#घोषणा IS_MOBILE(dev_priv)	(INTEL_INFO(dev_priv)->is_mobile)
#घोषणा IS_DGFX(dev_priv)   (INTEL_INFO(dev_priv)->is_dgfx)

#घोषणा IS_I830(dev_priv)	IS_PLATFORM(dev_priv, INTEL_I830)
#घोषणा IS_I845G(dev_priv)	IS_PLATFORM(dev_priv, INTEL_I845G)
#घोषणा IS_I85X(dev_priv)	IS_PLATFORM(dev_priv, INTEL_I85X)
#घोषणा IS_I865G(dev_priv)	IS_PLATFORM(dev_priv, INTEL_I865G)
#घोषणा IS_I915G(dev_priv)	IS_PLATFORM(dev_priv, INTEL_I915G)
#घोषणा IS_I915GM(dev_priv)	IS_PLATFORM(dev_priv, INTEL_I915GM)
#घोषणा IS_I945G(dev_priv)	IS_PLATFORM(dev_priv, INTEL_I945G)
#घोषणा IS_I945GM(dev_priv)	IS_PLATFORM(dev_priv, INTEL_I945GM)
#घोषणा IS_I965G(dev_priv)	IS_PLATFORM(dev_priv, INTEL_I965G)
#घोषणा IS_I965GM(dev_priv)	IS_PLATFORM(dev_priv, INTEL_I965GM)
#घोषणा IS_G45(dev_priv)	IS_PLATFORM(dev_priv, INTEL_G45)
#घोषणा IS_GM45(dev_priv)	IS_PLATFORM(dev_priv, INTEL_GM45)
#घोषणा IS_G4X(dev_priv)	(IS_G45(dev_priv) || IS_GM45(dev_priv))
#घोषणा IS_PINEVIEW(dev_priv)	IS_PLATFORM(dev_priv, INTEL_PINEVIEW)
#घोषणा IS_G33(dev_priv)	IS_PLATFORM(dev_priv, INTEL_G33)
#घोषणा IS_IRONLAKE(dev_priv)	IS_PLATFORM(dev_priv, INTEL_IRONLAKE)
#घोषणा IS_IRONLAKE_M(dev_priv) \
	(IS_PLATFORM(dev_priv, INTEL_IRONLAKE) && IS_MOBILE(dev_priv))
#घोषणा IS_SANDYBRIDGE(dev_priv) IS_PLATFORM(dev_priv, INTEL_SANDYBRIDGE)
#घोषणा IS_IVYBRIDGE(dev_priv)	IS_PLATFORM(dev_priv, INTEL_IVYBRIDGE)
#घोषणा IS_IVB_GT1(dev_priv)	(IS_IVYBRIDGE(dev_priv) && \
				 INTEL_INFO(dev_priv)->gt == 1)
#घोषणा IS_VALLEYVIEW(dev_priv)	IS_PLATFORM(dev_priv, INTEL_VALLEYVIEW)
#घोषणा IS_CHERRYVIEW(dev_priv)	IS_PLATFORM(dev_priv, INTEL_CHERRYVIEW)
#घोषणा IS_HASWELL(dev_priv)	IS_PLATFORM(dev_priv, INTEL_HASWELL)
#घोषणा IS_BROADWELL(dev_priv)	IS_PLATFORM(dev_priv, INTEL_BROADWELL)
#घोषणा IS_SKYLAKE(dev_priv)	IS_PLATFORM(dev_priv, INTEL_SKYLAKE)
#घोषणा IS_BROXTON(dev_priv)	IS_PLATFORM(dev_priv, INTEL_BROXTON)
#घोषणा IS_KABYLAKE(dev_priv)	IS_PLATFORM(dev_priv, INTEL_KABYLAKE)
#घोषणा IS_GEMINILAKE(dev_priv)	IS_PLATFORM(dev_priv, INTEL_GEMINILAKE)
#घोषणा IS_COFFEELAKE(dev_priv)	IS_PLATFORM(dev_priv, INTEL_COFFEELAKE)
#घोषणा IS_COMETLAKE(dev_priv)	IS_PLATFORM(dev_priv, INTEL_COMETLAKE)
#घोषणा IS_CANNONLAKE(dev_priv)	IS_PLATFORM(dev_priv, INTEL_CANNONLAKE)
#घोषणा IS_ICELAKE(dev_priv)	IS_PLATFORM(dev_priv, INTEL_ICELAKE)
#घोषणा IS_JSL_EHL(dev_priv)	(IS_PLATFORM(dev_priv, INTEL_JASPERLAKE) || \
				IS_PLATFORM(dev_priv, INTEL_ELKHARTLAKE))
#घोषणा IS_TIGERLAKE(dev_priv)	IS_PLATFORM(dev_priv, INTEL_TIGERLAKE)
#घोषणा IS_ROCKETLAKE(dev_priv)	IS_PLATFORM(dev_priv, INTEL_ROCKETLAKE)
#घोषणा IS_DG1(dev_priv)        IS_PLATFORM(dev_priv, INTEL_DG1)
#घोषणा IS_ALDERLAKE_S(dev_priv) IS_PLATFORM(dev_priv, INTEL_ALDERLAKE_S)
#घोषणा IS_HSW_EARLY_SDV(dev_priv) (IS_HASWELL(dev_priv) && \
				    (INTEL_DEVID(dev_priv) & 0xFF00) == 0x0C00)
#घोषणा IS_BDW_ULT(dev_priv) \
	IS_SUBPLATFORM(dev_priv, INTEL_BROADWELL, INTEL_SUBPLATFORM_ULT)
#घोषणा IS_BDW_ULX(dev_priv) \
	IS_SUBPLATFORM(dev_priv, INTEL_BROADWELL, INTEL_SUBPLATFORM_ULX)
#घोषणा IS_BDW_GT3(dev_priv)	(IS_BROADWELL(dev_priv) && \
				 INTEL_INFO(dev_priv)->gt == 3)
#घोषणा IS_HSW_ULT(dev_priv) \
	IS_SUBPLATFORM(dev_priv, INTEL_HASWELL, INTEL_SUBPLATFORM_ULT)
#घोषणा IS_HSW_GT3(dev_priv)	(IS_HASWELL(dev_priv) && \
				 INTEL_INFO(dev_priv)->gt == 3)
#घोषणा IS_HSW_GT1(dev_priv)	(IS_HASWELL(dev_priv) && \
				 INTEL_INFO(dev_priv)->gt == 1)
/* ULX machines are also considered ULT. */
#घोषणा IS_HSW_ULX(dev_priv) \
	IS_SUBPLATFORM(dev_priv, INTEL_HASWELL, INTEL_SUBPLATFORM_ULX)
#घोषणा IS_SKL_ULT(dev_priv) \
	IS_SUBPLATFORM(dev_priv, INTEL_SKYLAKE, INTEL_SUBPLATFORM_ULT)
#घोषणा IS_SKL_ULX(dev_priv) \
	IS_SUBPLATFORM(dev_priv, INTEL_SKYLAKE, INTEL_SUBPLATFORM_ULX)
#घोषणा IS_KBL_ULT(dev_priv) \
	IS_SUBPLATFORM(dev_priv, INTEL_KABYLAKE, INTEL_SUBPLATFORM_ULT)
#घोषणा IS_KBL_ULX(dev_priv) \
	IS_SUBPLATFORM(dev_priv, INTEL_KABYLAKE, INTEL_SUBPLATFORM_ULX)
#घोषणा IS_SKL_GT2(dev_priv)	(IS_SKYLAKE(dev_priv) && \
				 INTEL_INFO(dev_priv)->gt == 2)
#घोषणा IS_SKL_GT3(dev_priv)	(IS_SKYLAKE(dev_priv) && \
				 INTEL_INFO(dev_priv)->gt == 3)
#घोषणा IS_SKL_GT4(dev_priv)	(IS_SKYLAKE(dev_priv) && \
				 INTEL_INFO(dev_priv)->gt == 4)
#घोषणा IS_KBL_GT2(dev_priv)	(IS_KABYLAKE(dev_priv) && \
				 INTEL_INFO(dev_priv)->gt == 2)
#घोषणा IS_KBL_GT3(dev_priv)	(IS_KABYLAKE(dev_priv) && \
				 INTEL_INFO(dev_priv)->gt == 3)
#घोषणा IS_CFL_ULT(dev_priv) \
	IS_SUBPLATFORM(dev_priv, INTEL_COFFEELAKE, INTEL_SUBPLATFORM_ULT)
#घोषणा IS_CFL_ULX(dev_priv) \
	IS_SUBPLATFORM(dev_priv, INTEL_COFFEELAKE, INTEL_SUBPLATFORM_ULX)
#घोषणा IS_CFL_GT2(dev_priv)	(IS_COFFEELAKE(dev_priv) && \
				 INTEL_INFO(dev_priv)->gt == 2)
#घोषणा IS_CFL_GT3(dev_priv)	(IS_COFFEELAKE(dev_priv) && \
				 INTEL_INFO(dev_priv)->gt == 3)

#घोषणा IS_CML_ULT(dev_priv) \
	IS_SUBPLATFORM(dev_priv, INTEL_COMETLAKE, INTEL_SUBPLATFORM_ULT)
#घोषणा IS_CML_ULX(dev_priv) \
	IS_SUBPLATFORM(dev_priv, INTEL_COMETLAKE, INTEL_SUBPLATFORM_ULX)
#घोषणा IS_CML_GT2(dev_priv)	(IS_COMETLAKE(dev_priv) && \
				 INTEL_INFO(dev_priv)->gt == 2)

#घोषणा IS_CNL_WITH_PORT_F(dev_priv) \
	IS_SUBPLATFORM(dev_priv, INTEL_CANNONLAKE, INTEL_SUBPLATFORM_PORTF)
#घोषणा IS_ICL_WITH_PORT_F(dev_priv) \
	IS_SUBPLATFORM(dev_priv, INTEL_ICELAKE, INTEL_SUBPLATFORM_PORTF)

#घोषणा IS_TGL_U(dev_priv) \
	IS_SUBPLATFORM(dev_priv, INTEL_TIGERLAKE, INTEL_SUBPLATFORM_ULT)

#घोषणा IS_TGL_Y(dev_priv) \
	IS_SUBPLATFORM(dev_priv, INTEL_TIGERLAKE, INTEL_SUBPLATFORM_ULX)

#घोषणा SKL_REVID_A0		0x0
#घोषणा SKL_REVID_B0		0x1
#घोषणा SKL_REVID_C0		0x2
#घोषणा SKL_REVID_D0		0x3
#घोषणा SKL_REVID_E0		0x4
#घोषणा SKL_REVID_F0		0x5
#घोषणा SKL_REVID_G0		0x6
#घोषणा SKL_REVID_H0		0x7

#घोषणा IS_SKL_REVID(p, since, until) (IS_SKYLAKE(p) && IS_REVID(p, since, until))

#घोषणा BXT_REVID_A0		0x0
#घोषणा BXT_REVID_A1		0x1
#घोषणा BXT_REVID_B0		0x3
#घोषणा BXT_REVID_B_LAST	0x8
#घोषणा BXT_REVID_C0		0x9

#घोषणा IS_BXT_REVID(dev_priv, since, until) \
	(IS_BROXTON(dev_priv) && IS_REVID(dev_priv, since, until))

#घोषणा IS_KBL_GT_STEP(dev_priv, since, until) \
	(IS_KABYLAKE(dev_priv) && IS_GT_STEP(dev_priv, since, until))
#घोषणा IS_KBL_DISPLAY_STEP(dev_priv, since, until) \
	(IS_KABYLAKE(dev_priv) && IS_DISPLAY_STEP(dev_priv, since, until))

#घोषणा GLK_REVID_A0		0x0
#घोषणा GLK_REVID_A1		0x1
#घोषणा GLK_REVID_A2		0x2
#घोषणा GLK_REVID_B0		0x3

#घोषणा IS_GLK_REVID(dev_priv, since, until) \
	(IS_GEMINILAKE(dev_priv) && IS_REVID(dev_priv, since, until))

#घोषणा CNL_REVID_A0		0x0
#घोषणा CNL_REVID_B0		0x1
#घोषणा CNL_REVID_C0		0x2

#घोषणा IS_CNL_REVID(p, since, until) \
	(IS_CANNONLAKE(p) && IS_REVID(p, since, until))

#घोषणा ICL_REVID_A0		0x0
#घोषणा ICL_REVID_A2		0x1
#घोषणा ICL_REVID_B0		0x3
#घोषणा ICL_REVID_B2		0x4
#घोषणा ICL_REVID_C0		0x5

#घोषणा IS_ICL_REVID(p, since, until) \
	(IS_ICELAKE(p) && IS_REVID(p, since, until))

#घोषणा EHL_REVID_A0            0x0
#घोषणा EHL_REVID_B0            0x1

#घोषणा IS_JSL_EHL_REVID(p, since, until) \
	(IS_JSL_EHL(p) && IS_REVID(p, since, until))

#घोषणा IS_TGL_DISPLAY_STEP(__i915, since, until) \
	(IS_TIGERLAKE(__i915) && \
	 IS_DISPLAY_STEP(__i915, since, until))

#घोषणा IS_TGL_UY_GT_STEP(__i915, since, until) \
	((IS_TGL_U(__i915) || IS_TGL_Y(__i915)) && \
	 IS_GT_STEP(__i915, since, until))

#घोषणा IS_TGL_GT_STEP(__i915, since, until) \
	(IS_TIGERLAKE(__i915) && !(IS_TGL_U(__i915) || IS_TGL_Y(__i915)) && \
	 IS_GT_STEP(__i915, since, until))

#घोषणा RKL_REVID_A0		0x0
#घोषणा RKL_REVID_B0		0x1
#घोषणा RKL_REVID_C0		0x4

#घोषणा IS_RKL_REVID(p, since, until) \
	(IS_ROCKETLAKE(p) && IS_REVID(p, since, until))

#घोषणा DG1_REVID_A0		0x0
#घोषणा DG1_REVID_B0		0x1

#घोषणा IS_DG1_REVID(p, since, until) \
	(IS_DG1(p) && IS_REVID(p, since, until))

#घोषणा IS_ADLS_DISPLAY_STEP(__i915, since, until) \
	(IS_ALDERLAKE_S(__i915) && \
	 IS_DISPLAY_STEP(__i915, since, until))

#घोषणा IS_ADLS_GT_STEP(__i915, since, until) \
	(IS_ALDERLAKE_S(__i915) && \
	 IS_GT_STEP(__i915, since, until))

#घोषणा IS_LP(dev_priv)	(INTEL_INFO(dev_priv)->is_lp)
#घोषणा IS_GEN9_LP(dev_priv)	(IS_GEN(dev_priv, 9) && IS_LP(dev_priv))
#घोषणा IS_GEN9_BC(dev_priv)	(IS_GEN(dev_priv, 9) && !IS_LP(dev_priv))

#घोषणा __HAS_ENGINE(engine_mask, id) ((engine_mask) & BIT(id))
#घोषणा HAS_ENGINE(gt, id) __HAS_ENGINE((gt)->info.engine_mask, id)

#घोषणा ENGINE_INSTANCES_MASK(gt, first, count) (अणु		\
	अचिन्हित पूर्णांक first__ = (first);					\
	अचिन्हित पूर्णांक count__ = (count);					\
	((gt)->info.engine_mask &						\
	 GENMASK(first__ + count__ - 1, first__)) >> first__;		\
पूर्ण)
#घोषणा VDBOX_MASK(gt) \
	ENGINE_INSTANCES_MASK(gt, VCS0, I915_MAX_VCS)
#घोषणा VEBOX_MASK(gt) \
	ENGINE_INSTANCES_MASK(gt, VECS0, I915_MAX_VECS)

/*
 * The Gen7 cmdparser copies the scanned buffer to the ggtt क्रम execution
 * All later gens can run the final buffer from the ppgtt
 */
#घोषणा CMDPARSER_USES_GGTT(dev_priv) IS_GEN(dev_priv, 7)

#घोषणा HAS_LLC(dev_priv)	(INTEL_INFO(dev_priv)->has_llc)
#घोषणा HAS_SNOOP(dev_priv)	(INTEL_INFO(dev_priv)->has_snoop)
#घोषणा HAS_EDRAM(dev_priv)	((dev_priv)->edram_size_mb)
#घोषणा HAS_SECURE_BATCHES(dev_priv) (INTEL_GEN(dev_priv) < 6)
#घोषणा HAS_WT(dev_priv)	HAS_EDRAM(dev_priv)

#घोषणा HWS_NEEDS_PHYSICAL(dev_priv)	(INTEL_INFO(dev_priv)->hws_needs_physical)

#घोषणा HAS_LOGICAL_RING_CONTEXTS(dev_priv) \
		(INTEL_INFO(dev_priv)->has_logical_ring_contexts)
#घोषणा HAS_LOGICAL_RING_ELSQ(dev_priv) \
		(INTEL_INFO(dev_priv)->has_logical_ring_elsq)

#घोषणा HAS_MASTER_UNIT_IRQ(dev_priv) (INTEL_INFO(dev_priv)->has_master_unit_irq)

#घोषणा HAS_EXECLISTS(dev_priv) HAS_LOGICAL_RING_CONTEXTS(dev_priv)

#घोषणा INTEL_PPGTT(dev_priv) (INTEL_INFO(dev_priv)->ppgtt_type)
#घोषणा HAS_PPGTT(dev_priv) \
	(INTEL_PPGTT(dev_priv) != INTEL_PPGTT_NONE)
#घोषणा HAS_FULL_PPGTT(dev_priv) \
	(INTEL_PPGTT(dev_priv) >= INTEL_PPGTT_FULL)

#घोषणा HAS_PAGE_SIZES(dev_priv, sizes) (अणु \
	GEM_BUG_ON((sizes) == 0); \
	((sizes) & ~INTEL_INFO(dev_priv)->page_sizes) == 0; \
पूर्ण)

#घोषणा HAS_OVERLAY(dev_priv)		 (INTEL_INFO(dev_priv)->display.has_overlay)
#घोषणा OVERLAY_NEEDS_PHYSICAL(dev_priv) \
		(INTEL_INFO(dev_priv)->display.overlay_needs_physical)

/* Early gen2 have a totally busted CS tlb and require pinned batches. */
#घोषणा HAS_BROKEN_CS_TLB(dev_priv)	(IS_I830(dev_priv) || IS_I845G(dev_priv))

#घोषणा NEEDS_RC6_CTX_CORRUPTION_WA(dev_priv)	\
	(IS_BROADWELL(dev_priv) || IS_GEN(dev_priv, 9))

/* WaRsDisableCoarsePowerGating:skl,cnl */
#घोषणा NEEDS_WaRsDisableCoarsePowerGating(dev_priv)			\
	(IS_CANNONLAKE(dev_priv) ||					\
	 IS_SKL_GT3(dev_priv) ||					\
	 IS_SKL_GT4(dev_priv))

#घोषणा HAS_GMBUS_IRQ(dev_priv) (INTEL_GEN(dev_priv) >= 4)
#घोषणा HAS_GMBUS_BURST_READ(dev_priv) (INTEL_GEN(dev_priv) >= 10 || \
					IS_GEMINILAKE(dev_priv) || \
					IS_KABYLAKE(dev_priv))

/* With the 945 and later, Y tiling got adjusted so that it was 32 128-byte
 * rows, which changed the alignment requirements and fence programming.
 */
#घोषणा HAS_128_BYTE_Y_TILING(dev_priv) (!IS_GEN(dev_priv, 2) && \
					 !(IS_I915G(dev_priv) || \
					 IS_I915GM(dev_priv)))
#घोषणा SUPPORTS_TV(dev_priv)		(INTEL_INFO(dev_priv)->display.supports_tv)
#घोषणा I915_HAS_HOTPLUG(dev_priv)	(INTEL_INFO(dev_priv)->display.has_hotplug)

#घोषणा HAS_FW_BLC(dev_priv) 	(INTEL_GEN(dev_priv) > 2)
#घोषणा HAS_FBC(dev_priv)	(INTEL_INFO(dev_priv)->display.has_fbc)
#घोषणा HAS_CUR_FBC(dev_priv)	(!HAS_GMCH(dev_priv) && INTEL_GEN(dev_priv) >= 7)

#घोषणा HAS_IPS(dev_priv)	(IS_HSW_ULT(dev_priv) || IS_BROADWELL(dev_priv))

#घोषणा HAS_DP_MST(dev_priv)	(INTEL_INFO(dev_priv)->display.has_dp_mst)

#घोषणा HAS_DDI(dev_priv)		 (INTEL_INFO(dev_priv)->display.has_ddi)
#घोषणा HAS_FPGA_DBG_UNCLAIMED(dev_priv) (INTEL_INFO(dev_priv)->display.has_fpga_dbg)
#घोषणा HAS_PSR(dev_priv)		 (INTEL_INFO(dev_priv)->display.has_psr)
#घोषणा HAS_PSR_HW_TRACKING(dev_priv) \
	(INTEL_INFO(dev_priv)->display.has_psr_hw_tracking)
#घोषणा HAS_PSR2_SEL_FETCH(dev_priv)	 (INTEL_GEN(dev_priv) >= 12)
#घोषणा HAS_TRANSCODER(dev_priv, trans)	 ((INTEL_INFO(dev_priv)->cpu_transcoder_mask & BIT(trans)) != 0)

#घोषणा HAS_RC6(dev_priv)		 (INTEL_INFO(dev_priv)->has_rc6)
#घोषणा HAS_RC6p(dev_priv)		 (INTEL_INFO(dev_priv)->has_rc6p)
#घोषणा HAS_RC6pp(dev_priv)		 (false) /* HW was never validated */

#घोषणा HAS_RPS(dev_priv)	(INTEL_INFO(dev_priv)->has_rps)

#घोषणा HAS_CSR(dev_priv)	(INTEL_INFO(dev_priv)->display.has_csr)

#घोषणा HAS_MSO(i915)		(INTEL_GEN(i915) >= 12)

#घोषणा HAS_RUNTIME_PM(dev_priv) (INTEL_INFO(dev_priv)->has_runसमय_pm)
#घोषणा HAS_64BIT_RELOC(dev_priv) (INTEL_INFO(dev_priv)->has_64bit_reloc)

#घोषणा HAS_IPC(dev_priv)		 (INTEL_INFO(dev_priv)->display.has_ipc)

#घोषणा HAS_REGION(i915, i) (INTEL_INFO(i915)->memory_regions & (i))
#घोषणा HAS_LMEM(i915) HAS_REGION(i915, REGION_LMEM)

#घोषणा HAS_GT_UC(dev_priv)	(INTEL_INFO(dev_priv)->has_gt_uc)

#घोषणा HAS_POOLED_EU(dev_priv)	(INTEL_INFO(dev_priv)->has_pooled_eu)

#घोषणा HAS_GLOBAL_MOCS_REGISTERS(dev_priv)	(INTEL_INFO(dev_priv)->has_global_mocs)


#घोषणा HAS_GMCH(dev_priv) (INTEL_INFO(dev_priv)->display.has_gmch)

#घोषणा HAS_LSPCON(dev_priv) (IS_GEN_RANGE(dev_priv, 9, 10))

/* DPF == dynamic parity feature */
#घोषणा HAS_L3_DPF(dev_priv) (INTEL_INFO(dev_priv)->has_l3_dpf)
#घोषणा NUM_L3_SLICES(dev_priv) (IS_HSW_GT3(dev_priv) ? \
				 2 : HAS_L3_DPF(dev_priv))

#घोषणा GT_FREQUENCY_MULTIPLIER 50
#घोषणा GEN9_FREQ_SCALER 3

#घोषणा INTEL_NUM_PIPES(dev_priv) (hweight8(INTEL_INFO(dev_priv)->pipe_mask))

#घोषणा HAS_DISPLAY(dev_priv) (INTEL_INFO(dev_priv)->pipe_mask != 0)

#घोषणा HAS_VRR(i915)	(INTEL_GEN(i915) >= 12)

/* Only valid when HAS_DISPLAY() is true */
#घोषणा INTEL_DISPLAY_ENABLED(dev_priv) \
	(drm_WARN_ON(&(dev_priv)->drm, !HAS_DISPLAY(dev_priv)), !(dev_priv)->params.disable_display)

अटल अंतरभूत bool run_as_guest(व्योम)
अणु
	वापस !hypervisor_is_type(X86_HYPER_NATIVE);
पूर्ण

#घोषणा HAS_D12_PLANE_MINIMIZATION(dev_priv) (IS_ROCKETLAKE(dev_priv) || \
					      IS_ALDERLAKE_S(dev_priv))

अटल अंतरभूत bool पूर्णांकel_vtd_active(व्योम)
अणु
#अगर_घोषित CONFIG_INTEL_IOMMU
	अगर (पूर्णांकel_iommu_gfx_mapped)
		वापस true;
#पूर्ण_अगर

	/* Running as a guest, we assume the host is enक्रमcing VT'd */
	वापस run_as_guest();
पूर्ण

अटल अंतरभूत bool पूर्णांकel_scanout_needs_vtd_wa(काष्ठा drm_i915_निजी *dev_priv)
अणु
	वापस INTEL_GEN(dev_priv) >= 6 && पूर्णांकel_vtd_active();
पूर्ण

अटल अंतरभूत bool
पूर्णांकel_ggtt_update_needs_vtd_wa(काष्ठा drm_i915_निजी *dev_priv)
अणु
	वापस IS_BROXTON(dev_priv) && पूर्णांकel_vtd_active();
पूर्ण

/* i915_drv.c */
बाह्य स्थिर काष्ठा dev_pm_ops i915_pm_ops;

पूर्णांक i915_driver_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent);
व्योम i915_driver_हटाओ(काष्ठा drm_i915_निजी *i915);
व्योम i915_driver_shutकरोwn(काष्ठा drm_i915_निजी *i915);

पूर्णांक i915_resume_चयनeroo(काष्ठा drm_i915_निजी *i915);
पूर्णांक i915_suspend_चयनeroo(काष्ठा drm_i915_निजी *i915, pm_message_t state);

पूर्णांक i915_getparam_ioctl(काष्ठा drm_device *dev, व्योम *data,
			काष्ठा drm_file *file_priv);

/* i915_gem.c */
पूर्णांक i915_gem_init_userptr(काष्ठा drm_i915_निजी *dev_priv);
व्योम i915_gem_cleanup_userptr(काष्ठा drm_i915_निजी *dev_priv);
व्योम i915_gem_init_early(काष्ठा drm_i915_निजी *dev_priv);
व्योम i915_gem_cleanup_early(काष्ठा drm_i915_निजी *dev_priv);

काष्ठा पूर्णांकel_memory_region *i915_gem_shmem_setup(काष्ठा drm_i915_निजी *i915);

अटल अंतरभूत व्योम i915_gem_drain_मुक्तd_objects(काष्ठा drm_i915_निजी *i915)
अणु
	/*
	 * A single pass should suffice to release all the मुक्तd objects (aदीर्घ
	 * most call paths) , but be a little more paranoid in that मुक्तing
	 * the objects करोes take a little amount of समय, during which the rcu
	 * callbacks could have added new objects पूर्णांकo the मुक्तd list, and
	 * armed the work again.
	 */
	जबतक (atomic_पढ़ो(&i915->mm.मुक्त_count)) अणु
		flush_work(&i915->mm.मुक्त_work);
		rcu_barrier();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम i915_gem_drain_workqueue(काष्ठा drm_i915_निजी *i915)
अणु
	/*
	 * Similar to objects above (see i915_gem_drain_मुक्तd-objects), in
	 * general we have workers that are armed by RCU and then rearm
	 * themselves in their callbacks. To be paranoid, we need to
	 * drain the workqueue a second समय after रुकोing क्रम the RCU
	 * grace period so that we catch work queued via RCU from the first
	 * pass. As neither drain_workqueue() nor flush_workqueue() report
	 * a result, we make an assumption that we only करोn't require more
	 * than 3 passes to catch all _recursive_ RCU delayed work.
	 *
	 */
	पूर्णांक pass = 3;
	करो अणु
		flush_workqueue(i915->wq);
		rcu_barrier();
		i915_gem_drain_मुक्तd_objects(i915);
	पूर्ण जबतक (--pass);
	drain_workqueue(i915->wq);
पूर्ण

काष्ठा i915_vma * __must_check
i915_gem_object_ggtt_pin_ww(काष्ठा drm_i915_gem_object *obj,
			    काष्ठा i915_gem_ww_ctx *ww,
			    स्थिर काष्ठा i915_ggtt_view *view,
			    u64 size, u64 alignment, u64 flags);

अटल अंतरभूत काष्ठा i915_vma * __must_check
i915_gem_object_ggtt_pin(काष्ठा drm_i915_gem_object *obj,
			 स्थिर काष्ठा i915_ggtt_view *view,
			 u64 size, u64 alignment, u64 flags)
अणु
	वापस i915_gem_object_ggtt_pin_ww(obj, शून्य, view, size, alignment, flags);
पूर्ण

पूर्णांक i915_gem_object_unbind(काष्ठा drm_i915_gem_object *obj,
			   अचिन्हित दीर्घ flags);
#घोषणा I915_GEM_OBJECT_UNBIND_ACTIVE BIT(0)
#घोषणा I915_GEM_OBJECT_UNBIND_BARRIER BIT(1)
#घोषणा I915_GEM_OBJECT_UNBIND_TEST BIT(2)

व्योम i915_gem_runसमय_suspend(काष्ठा drm_i915_निजी *dev_priv);

पूर्णांक i915_gem_dumb_create(काष्ठा drm_file *file_priv,
			 काष्ठा drm_device *dev,
			 काष्ठा drm_mode_create_dumb *args);

पूर्णांक __must_check i915_gem_set_global_seqno(काष्ठा drm_device *dev, u32 seqno);

अटल अंतरभूत u32 i915_reset_count(काष्ठा i915_gpu_error *error)
अणु
	वापस atomic_पढ़ो(&error->reset_count);
पूर्ण

अटल अंतरभूत u32 i915_reset_engine_count(काष्ठा i915_gpu_error *error,
					  स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	वापस atomic_पढ़ो(&error->reset_engine_count[engine->uabi_class]);
पूर्ण

पूर्णांक __must_check i915_gem_init(काष्ठा drm_i915_निजी *dev_priv);
व्योम i915_gem_driver_रेजिस्टर(काष्ठा drm_i915_निजी *i915);
व्योम i915_gem_driver_unरेजिस्टर(काष्ठा drm_i915_निजी *i915);
व्योम i915_gem_driver_हटाओ(काष्ठा drm_i915_निजी *dev_priv);
व्योम i915_gem_driver_release(काष्ठा drm_i915_निजी *dev_priv);
व्योम i915_gem_suspend(काष्ठा drm_i915_निजी *dev_priv);
व्योम i915_gem_suspend_late(काष्ठा drm_i915_निजी *dev_priv);
व्योम i915_gem_resume(काष्ठा drm_i915_निजी *dev_priv);

पूर्णांक i915_gem_खोलो(काष्ठा drm_i915_निजी *i915, काष्ठा drm_file *file);

पूर्णांक i915_gem_object_set_cache_level(काष्ठा drm_i915_gem_object *obj,
				    क्रमागत i915_cache_level cache_level);

काष्ठा drm_gem_object *i915_gem_prime_import(काष्ठा drm_device *dev,
				काष्ठा dma_buf *dma_buf);

काष्ठा dma_buf *i915_gem_prime_export(काष्ठा drm_gem_object *gem_obj, पूर्णांक flags);

अटल अंतरभूत काष्ठा i915_gem_context *
__i915_gem_context_lookup_rcu(काष्ठा drm_i915_file_निजी *file_priv, u32 id)
अणु
	वापस xa_load(&file_priv->context_xa, id);
पूर्ण

अटल अंतरभूत काष्ठा i915_gem_context *
i915_gem_context_lookup(काष्ठा drm_i915_file_निजी *file_priv, u32 id)
अणु
	काष्ठा i915_gem_context *ctx;

	rcu_पढ़ो_lock();
	ctx = __i915_gem_context_lookup_rcu(file_priv, id);
	अगर (ctx && !kref_get_unless_zero(&ctx->ref))
		ctx = शून्य;
	rcu_पढ़ो_unlock();

	वापस ctx;
पूर्ण

/* i915_gem_evict.c */
पूर्णांक __must_check i915_gem_evict_something(काष्ठा i915_address_space *vm,
					  u64 min_size, u64 alignment,
					  अचिन्हित दीर्घ color,
					  u64 start, u64 end,
					  अचिन्हित flags);
पूर्णांक __must_check i915_gem_evict_क्रम_node(काष्ठा i915_address_space *vm,
					 काष्ठा drm_mm_node *node,
					 अचिन्हित पूर्णांक flags);
पूर्णांक i915_gem_evict_vm(काष्ठा i915_address_space *vm);

/* i915_gem_पूर्णांकernal.c */
काष्ठा drm_i915_gem_object *
i915_gem_object_create_पूर्णांकernal(काष्ठा drm_i915_निजी *dev_priv,
				phys_addr_t size);

/* i915_gem_tiling.c */
अटल अंतरभूत bool i915_gem_object_needs_bit17_swizzle(काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(obj->base.dev);

	वापस i915->ggtt.bit_6_swizzle_x == I915_BIT_6_SWIZZLE_9_10_17 &&
		i915_gem_object_is_tiled(obj);
पूर्ण

u32 i915_gem_fence_size(काष्ठा drm_i915_निजी *dev_priv, u32 size,
			अचिन्हित पूर्णांक tiling, अचिन्हित पूर्णांक stride);
u32 i915_gem_fence_alignment(काष्ठा drm_i915_निजी *dev_priv, u32 size,
			     अचिन्हित पूर्णांक tiling, अचिन्हित पूर्णांक stride);

स्थिर अक्षर *i915_cache_level_str(काष्ठा drm_i915_निजी *i915, पूर्णांक type);

/* i915_cmd_parser.c */
पूर्णांक i915_cmd_parser_get_version(काष्ठा drm_i915_निजी *dev_priv);
पूर्णांक पूर्णांकel_engine_init_cmd_parser(काष्ठा पूर्णांकel_engine_cs *engine);
व्योम पूर्णांकel_engine_cleanup_cmd_parser(काष्ठा पूर्णांकel_engine_cs *engine);
अचिन्हित दीर्घ *पूर्णांकel_engine_cmd_parser_alloc_jump_whitelist(u32 batch_length,
							    bool trampoline);

पूर्णांक पूर्णांकel_engine_cmd_parser(काष्ठा पूर्णांकel_engine_cs *engine,
			    काष्ठा i915_vma *batch,
			    अचिन्हित दीर्घ batch_offset,
			    अचिन्हित दीर्घ batch_length,
			    काष्ठा i915_vma *shaकरोw,
			    अचिन्हित दीर्घ *jump_whitelist,
			    व्योम *shaकरोw_map,
			    स्थिर व्योम *batch_map);
#घोषणा I915_CMD_PARSER_TRAMPOLINE_SIZE 8

/* पूर्णांकel_device_info.c */
अटल अंतरभूत काष्ठा पूर्णांकel_device_info *
mkग_लिखो_device_info(काष्ठा drm_i915_निजी *dev_priv)
अणु
	वापस (काष्ठा पूर्णांकel_device_info *)INTEL_INFO(dev_priv);
पूर्ण

पूर्णांक i915_reg_पढ़ो_ioctl(काष्ठा drm_device *dev, व्योम *data,
			काष्ठा drm_file *file);

/* i915_mm.c */
पूर्णांक remap_io_mapping(काष्ठा vm_area_काष्ठा *vma,
		     अचिन्हित दीर्घ addr, अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ size,
		     काष्ठा io_mapping *iomap);
पूर्णांक remap_io_sg(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size,
		काष्ठा scatterlist *sgl, resource_माप_प्रकार iobase);

अटल अंतरभूत पूर्णांक पूर्णांकel_hws_csb_ग_लिखो_index(काष्ठा drm_i915_निजी *i915)
अणु
	अगर (INTEL_GEN(i915) >= 10)
		वापस CNL_HWS_CSB_WRITE_INDEX;
	अन्यथा
		वापस I915_HWS_CSB_WRITE_INDEX;
पूर्ण

अटल अंतरभूत क्रमागत i915_map_type
i915_coherent_map_type(काष्ठा drm_i915_निजी *i915)
अणु
	वापस HAS_LLC(i915) ? I915_MAP_WB : I915_MAP_WC;
पूर्ण

#पूर्ण_अगर
