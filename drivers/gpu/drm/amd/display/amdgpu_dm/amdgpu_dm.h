<शैली गुरु>
/*
 * Copyright (C) 2015-2020 Advanced Micro Devices, Inc. All rights reserved.
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
 * Authors: AMD
 *
 */

#अगर_अघोषित __AMDGPU_DM_H__
#घोषणा __AMDGPU_DM_H__

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_dp_mst_helper.h>
#समावेश <drm/drm_plane.h>

/*
 * This file contains the definition क्रम amdgpu_display_manager
 * and its API क्रम amdgpu driver's use.
 * This component provides all the display related functionality
 * and this is the only component that calls DAL API.
 * The API contained here पूर्णांकended क्रम amdgpu driver use.
 * The API that is called directly from KMS framework is located
 * in amdgpu_dm_kms.h file
 */

#घोषणा AMDGPU_DM_MAX_DISPLAY_INDEX 31

#घोषणा AMDGPU_DM_MAX_CRTC 6

/*
#समावेश "include/amdgpu_dal_power_if.h"
#समावेश "amdgpu_dm_irq.h"
*/

#समावेश "irq_types.h"
#समावेश "signal_types.h"
#समावेश "amdgpu_dm_crc.h"

/* Forward declarations */
काष्ठा amdgpu_device;
काष्ठा drm_device;
काष्ठा dc;
काष्ठा amdgpu_bo;
काष्ठा dmub_srv;
काष्ठा dc_plane_state;

काष्ठा common_irq_params अणु
	काष्ठा amdgpu_device *adev;
	क्रमागत dc_irq_source irq_src;
	atomic64_t previous_बारtamp;
पूर्ण;

/**
 * काष्ठा dm_compressor_info - Buffer info used by frame buffer compression
 * @cpu_addr: MMIO cpu addr
 * @bo_ptr: Poपूर्णांकer to the buffer object
 * @gpu_addr: MMIO gpu addr
 */
काष्ठा dm_compressor_info अणु
	व्योम *cpu_addr;
	काष्ठा amdgpu_bo *bo_ptr;
	uपूर्णांक64_t gpu_addr;
पूर्ण;

/**
 * काष्ठा vblank_workqueue - Works to be executed in a separate thपढ़ो during vblank
 * @mall_work: work क्रम mall stutter
 * @dm: amdgpu display manager device
 * @otg_inst: otg instance of which vblank is being set
 * @enable: true अगर enable vblank
 */
काष्ठा vblank_workqueue अणु
	काष्ठा work_काष्ठा mall_work;
	काष्ठा amdgpu_display_manager *dm;
	पूर्णांक otg_inst;
	bool enable;
पूर्ण;

/**
 * काष्ठा amdgpu_dm_backlight_caps - Inक्रमmation about backlight
 *
 * Describe the backlight support क्रम ACPI or eDP AUX.
 */
काष्ठा amdgpu_dm_backlight_caps अणु
	/**
	 * @ext_caps: Keep the data काष्ठा with all the inक्रमmation about the
	 * display support क्रम HDR.
	 */
	जोड़ dpcd_sink_ext_caps *ext_caps;
	/**
	 * @aux_min_input_संकेत: Min brightness value supported by the display
	 */
	u32 aux_min_input_संकेत;
	/**
	 * @aux_max_input_संकेत: Max brightness value supported by the display
	 * in nits.
	 */
	u32 aux_max_input_संकेत;
	/**
	 * @min_input_संकेत: minimum possible input in range 0-255.
	 */
	पूर्णांक min_input_संकेत;
	/**
	 * @max_input_संकेत: maximum possible input in range 0-255.
	 */
	पूर्णांक max_input_संकेत;
	/**
	 * @caps_valid: true अगर these values are from the ACPI पूर्णांकerface.
	 */
	bool caps_valid;
	/**
	 * @aux_support: Describes अगर the display supports AUX backlight.
	 */
	bool aux_support;
पूर्ण;

/**
 * काष्ठा dal_allocation - Tracks mapped FB memory क्रम SMU communication
 */
काष्ठा dal_allocation अणु
	काष्ठा list_head list;
	काष्ठा amdgpu_bo *bo;
	व्योम *cpu_ptr;
	u64 gpu_addr;
पूर्ण;

/**
 * काष्ठा amdgpu_display_manager - Central amdgpu display manager device
 *
 * @dc: Display Core control काष्ठाure
 * @adev: AMDGPU base driver काष्ठाure
 * @ddev: DRM base driver काष्ठाure
 * @display_indexes_num: Max number of display streams supported
 * @irq_handler_list_table_lock: Synchronizes access to IRQ tables
 * @backlight_dev: Backlight control device
 * @backlight_link: Link on which to control backlight
 * @backlight_caps: Capabilities of the backlight device
 * @मुक्तsync_module: Module handling मुक्तsync calculations
 * @hdcp_workqueue: AMDGPU content protection queue
 * @fw_dmcu: Reference to DMCU firmware
 * @dmcu_fw_version: Version of the DMCU firmware
 * @soc_bounding_box: SOC bounding box values provided by gpu_info FW
 * @cached_state: Caches device atomic state क्रम suspend/resume
 * @cached_dc_state: Cached state of content streams
 * @compressor: Frame buffer compression buffer. See &काष्ठा dm_compressor_info
 * @क्रमce_timing_sync: set via debugfs. When set, indicates that all connected
 *		       displays will be क्रमced to synchronize.
 */
काष्ठा amdgpu_display_manager अणु

	काष्ठा dc *dc;

	/**
	 * @dmub_srv:
	 *
	 * DMUB service, used क्रम controlling the DMUB on hardware
	 * that supports it. The poपूर्णांकer to the dmub_srv will be
	 * शून्य on hardware that करोes not support it.
	 */
	काष्ठा dmub_srv *dmub_srv;

	/**
	 * @dmub_fb_info:
	 *
	 * Framebuffer regions क्रम the DMUB.
	 */
	काष्ठा dmub_srv_fb_info *dmub_fb_info;

	/**
	 * @dmub_fw:
	 *
	 * DMUB firmware, required on hardware that has DMUB support.
	 */
	स्थिर काष्ठा firmware *dmub_fw;

	/**
	 * @dmub_bo:
	 *
	 * Buffer object क्रम the DMUB.
	 */
	काष्ठा amdgpu_bo *dmub_bo;

	/**
	 * @dmub_bo_gpu_addr:
	 *
	 * GPU भव address क्रम the DMUB buffer object.
	 */
	u64 dmub_bo_gpu_addr;

	/**
	 * @dmub_bo_cpu_addr:
	 *
	 * CPU address क्रम the DMUB buffer object.
	 */
	व्योम *dmub_bo_cpu_addr;

	/**
	 * @dmcub_fw_version:
	 *
	 * DMCUB firmware version.
	 */
	uपूर्णांक32_t dmcub_fw_version;

	/**
	 * @cgs_device:
	 *
	 * The Common Graphics Services device. It provides an पूर्णांकerface क्रम
	 * accessing रेजिस्टरs.
	 */
	काष्ठा cgs_device *cgs_device;

	काष्ठा amdgpu_device *adev;
	काष्ठा drm_device *ddev;
	u16 display_indexes_num;

	/**
	 * @atomic_obj:
	 *
	 * In combination with &dm_atomic_state it helps manage
	 * global atomic state that करोesn't map cleanly पूर्णांकo existing
	 * drm resources, like &dc_context.
	 */
	काष्ठा drm_निजी_obj atomic_obj;

	/**
	 * @dc_lock:
	 *
	 * Guards access to DC functions that can issue रेजिस्टर ग_लिखो
	 * sequences.
	 */
	काष्ठा mutex dc_lock;

	/**
	 * @audio_lock:
	 *
	 * Guards access to audio instance changes.
	 */
	काष्ठा mutex audio_lock;

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	/**
	 * @vblank_lock:
	 *
	 * Guards access to deferred vblank work state.
	 */
	spinlock_t vblank_lock;
#पूर्ण_अगर

	/**
	 * @audio_component:
	 *
	 * Used to notअगरy ELD changes to sound driver.
	 */
	काष्ठा drm_audio_component *audio_component;

	/**
	 * @audio_रेजिस्टरed:
	 *
	 * True अगर the audio component has been रेजिस्टरed
	 * successfully, false otherwise.
	 */
	bool audio_रेजिस्टरed;

	/**
	 * @irq_handler_list_low_tab:
	 *
	 * Low priority IRQ handler table.
	 *
	 * It is a n*m table consisting of n IRQ sources, and m handlers per IRQ
	 * source. Low priority IRQ handlers are deferred to a workqueue to be
	 * processed. Hence, they can sleep.
	 *
	 * Note that handlers are called in the same order as they were
	 * रेजिस्टरed (FIFO).
	 */
	काष्ठा list_head irq_handler_list_low_tab[DAL_IRQ_SOURCES_NUMBER];

	/**
	 * @irq_handler_list_high_tab:
	 *
	 * High priority IRQ handler table.
	 *
	 * It is a n*m table, same as &irq_handler_list_low_tab. However,
	 * handlers in this table are not deferred and are called immediately.
	 */
	काष्ठा list_head irq_handler_list_high_tab[DAL_IRQ_SOURCES_NUMBER];

	/**
	 * @pflip_params:
	 *
	 * Page flip IRQ parameters, passed to रेजिस्टरed handlers when
	 * triggered.
	 */
	काष्ठा common_irq_params
	pflip_params[DC_IRQ_SOURCE_PFLIP_LAST - DC_IRQ_SOURCE_PFLIP_FIRST + 1];

	/**
	 * @vblank_params:
	 *
	 * Vertical blanking IRQ parameters, passed to रेजिस्टरed handlers when
	 * triggered.
	 */
	काष्ठा common_irq_params
	vblank_params[DC_IRQ_SOURCE_VBLANK6 - DC_IRQ_SOURCE_VBLANK1 + 1];

	/**
	 * @vline0_params:
	 *
	 * OTG vertical पूर्णांकerrupt0 IRQ parameters, passed to रेजिस्टरed
	 * handlers when triggered.
	 */
	काष्ठा common_irq_params
	vline0_params[DC_IRQ_SOURCE_DC6_VLINE0 - DC_IRQ_SOURCE_DC1_VLINE0 + 1];

	/**
	 * @vupdate_params:
	 *
	 * Vertical update IRQ parameters, passed to रेजिस्टरed handlers when
	 * triggered.
	 */
	काष्ठा common_irq_params
	vupdate_params[DC_IRQ_SOURCE_VUPDATE6 - DC_IRQ_SOURCE_VUPDATE1 + 1];

	/**
	 * @dmub_trace_params:
	 *
	 * DMUB trace event IRQ parameters, passed to रेजिस्टरed handlers when
	 * triggered.
	 */
	काष्ठा common_irq_params
	dmub_trace_params[1];

	spinlock_t irq_handler_list_table_lock;

	काष्ठा backlight_device *backlight_dev;

	स्थिर काष्ठा dc_link *backlight_link;
	काष्ठा amdgpu_dm_backlight_caps backlight_caps;

	काष्ठा mod_मुक्तsync *मुक्तsync_module;
#अगर_घोषित CONFIG_DRM_AMD_DC_HDCP
	काष्ठा hdcp_workqueue *hdcp_workqueue;
#पूर्ण_अगर

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	/**
	 * @vblank_workqueue:
	 *
	 * amdgpu workqueue during vblank
	 */
	काष्ठा vblank_workqueue *vblank_workqueue;
#पूर्ण_अगर

	काष्ठा drm_atomic_state *cached_state;
	काष्ठा dc_state *cached_dc_state;

	काष्ठा dm_compressor_info compressor;

	स्थिर काष्ठा firmware *fw_dmcu;
	uपूर्णांक32_t dmcu_fw_version;
	/**
	 * @soc_bounding_box:
	 *
	 * gpu_info FW provided soc bounding box काष्ठा or 0 अगर not
	 * available in FW
	 */
	स्थिर काष्ठा gpu_info_soc_bounding_box_v1_0 *soc_bounding_box;

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	/**
	 * @active_vblank_irq_count:
	 *
	 * number of currently active vblank irqs
	 */
	uपूर्णांक32_t active_vblank_irq_count;
#पूर्ण_अगर

#अगर defined(CONFIG_DRM_AMD_SECURE_DISPLAY)
	/**
	 * @crc_rd_wrk:
	 *
	 * Work to be executed in a separate thपढ़ो to communicate with PSP.
	 */
	काष्ठा crc_rd_work *crc_rd_wrk;
#पूर्ण_अगर

	/**
	 * @mst_encoders:
	 *
	 * fake encoders used क्रम DP MST.
	 */
	काष्ठा amdgpu_encoder mst_encoders[AMDGPU_DM_MAX_CRTC];
	bool क्रमce_timing_sync;
	bool disable_hpd_irq;
	bool dmcub_trace_event_en;
	/**
	 * @da_list:
	 *
	 * DAL fb memory allocation list, क्रम communication with SMU.
	 */
	काष्ठा list_head da_list;
पूर्ण;

क्रमागत dsc_घड़ी_क्रमce_state अणु
	DSC_CLK_FORCE_DEFAULT = 0,
	DSC_CLK_FORCE_ENABLE,
	DSC_CLK_FORCE_DISABLE,
पूर्ण;

काष्ठा dsc_preferred_settings अणु
	क्रमागत dsc_घड़ी_क्रमce_state dsc_क्रमce_enable;
	uपूर्णांक32_t dsc_num_slices_v;
	uपूर्णांक32_t dsc_num_slices_h;
	uपूर्णांक32_t dsc_bits_per_pixel;
पूर्ण;

काष्ठा amdgpu_dm_connector अणु

	काष्ठा drm_connector base;
	uपूर्णांक32_t connector_id;

	/* we need to mind the EDID between detect
	   and get modes due to analog/digital/tvencoder */
	काष्ठा edid *edid;

	/* shared with amdgpu */
	काष्ठा amdgpu_hpd hpd;

	/* number of modes generated from EDID at 'dc_sink' */
	पूर्णांक num_modes;

	/* The 'old' sink - beक्रमe an HPD.
	 * The 'current' sink is in dc_link->sink. */
	काष्ठा dc_sink *dc_sink;
	काष्ठा dc_link *dc_link;
	काष्ठा dc_sink *dc_em_sink;

	/* DM only */
	काष्ठा drm_dp_mst_topology_mgr mst_mgr;
	काष्ठा amdgpu_dm_dp_aux dm_dp_aux;
	काष्ठा drm_dp_mst_port *port;
	काष्ठा amdgpu_dm_connector *mst_port;
	काष्ठा drm_dp_aux *dsc_aux;

	/* TODO see अगर we can merge with ddc_bus or make a dm_connector */
	काष्ठा amdgpu_i2c_adapter *i2c;

	/* Monitor range limits */
	पूर्णांक min_vfreq ;
	पूर्णांक max_vfreq ;
	पूर्णांक pixel_घड़ी_mhz;

	/* Audio instance - रक्षित by audio_lock. */
	पूर्णांक audio_inst;

	काष्ठा mutex hpd_lock;

	bool fake_enable;
#अगर_घोषित CONFIG_DEBUG_FS
	uपूर्णांक32_t debugfs_dpcd_address;
	uपूर्णांक32_t debugfs_dpcd_size;
#पूर्ण_अगर
	bool क्रमce_yuv420_output;
	काष्ठा dsc_preferred_settings dsc_settings;
	/* Cached display modes */
	काष्ठा drm_display_mode मुक्तsync_vid_base;
पूर्ण;

#घोषणा to_amdgpu_dm_connector(x) container_of(x, काष्ठा amdgpu_dm_connector, base)

बाह्य स्थिर काष्ठा amdgpu_ip_block_version dm_ip_block;

काष्ठा dm_plane_state अणु
	काष्ठा drm_plane_state base;
	काष्ठा dc_plane_state *dc_state;
पूर्ण;

काष्ठा dm_crtc_state अणु
	काष्ठा drm_crtc_state base;
	काष्ठा dc_stream_state *stream;

	bool cm_has_degamma;
	bool cm_is_degamma_srgb;

	पूर्णांक update_type;
	पूर्णांक active_planes;

	पूर्णांक crc_skip_count;

	bool मुक्तsync_timing_changed;
	bool मुक्तsync_vrr_info_changed;

	bool dsc_क्रमce_changed;
	bool vrr_supported;
	काष्ठा mod_मुक्तsync_config मुक्तsync_config;
	काष्ठा dc_info_packet vrr_infopacket;

	पूर्णांक abm_level;
पूर्ण;

#घोषणा to_dm_crtc_state(x) container_of(x, काष्ठा dm_crtc_state, base)

काष्ठा dm_atomic_state अणु
	काष्ठा drm_निजी_state base;

	काष्ठा dc_state *context;
पूर्ण;

#घोषणा to_dm_atomic_state(x) container_of(x, काष्ठा dm_atomic_state, base)

काष्ठा dm_connector_state अणु
	काष्ठा drm_connector_state base;

	क्रमागत amdgpu_rmx_type scaling;
	uपूर्णांक8_t underscan_vborder;
	uपूर्णांक8_t underscan_hborder;
	bool underscan_enable;
	bool मुक्तsync_capable;
#अगर_घोषित CONFIG_DRM_AMD_DC_HDCP
	bool update_hdcp;
#पूर्ण_अगर
	uपूर्णांक8_t abm_level;
	पूर्णांक vcpi_slots;
	uपूर्णांक64_t pbn;
पूर्ण;

काष्ठा amdgpu_hdmi_vsdb_info अणु
	अचिन्हित पूर्णांक amd_vsdb_version;		/* VSDB version, should be used to determine which VSIF to send */
	bool मुक्तsync_supported;		/* FreeSync Supported */
	अचिन्हित पूर्णांक min_refresh_rate_hz;	/* FreeSync Minimum Refresh Rate in Hz */
	अचिन्हित पूर्णांक max_refresh_rate_hz;	/* FreeSync Maximum Refresh Rate in Hz */
पूर्ण;


#घोषणा to_dm_connector_state(x)\
	container_of((x), काष्ठा dm_connector_state, base)

व्योम amdgpu_dm_connector_funcs_reset(काष्ठा drm_connector *connector);
काष्ठा drm_connector_state *
amdgpu_dm_connector_atomic_duplicate_state(काष्ठा drm_connector *connector);
पूर्णांक amdgpu_dm_connector_atomic_set_property(काष्ठा drm_connector *connector,
					    काष्ठा drm_connector_state *state,
					    काष्ठा drm_property *property,
					    uपूर्णांक64_t val);

पूर्णांक amdgpu_dm_connector_atomic_get_property(काष्ठा drm_connector *connector,
					    स्थिर काष्ठा drm_connector_state *state,
					    काष्ठा drm_property *property,
					    uपूर्णांक64_t *val);

पूर्णांक amdgpu_dm_get_encoder_crtc_mask(काष्ठा amdgpu_device *adev);

व्योम amdgpu_dm_connector_init_helper(काष्ठा amdgpu_display_manager *dm,
				     काष्ठा amdgpu_dm_connector *aconnector,
				     पूर्णांक connector_type,
				     काष्ठा dc_link *link,
				     पूर्णांक link_index);

क्रमागत drm_mode_status amdgpu_dm_connector_mode_valid(काष्ठा drm_connector *connector,
				   काष्ठा drm_display_mode *mode);

व्योम dm_restore_drm_connector_state(काष्ठा drm_device *dev,
				    काष्ठा drm_connector *connector);

व्योम amdgpu_dm_update_मुक्तsync_caps(काष्ठा drm_connector *connector,
					काष्ठा edid *edid);

व्योम amdgpu_dm_trigger_timing_sync(काष्ठा drm_device *dev);

#घोषणा MAX_COLOR_LUT_ENTRIES 4096
/* Legacy gamm LUT users such as X करोesn't like large LUT sizes */
#घोषणा MAX_COLOR_LEGACY_LUT_ENTRIES 256

व्योम amdgpu_dm_init_color_mod(व्योम);
पूर्णांक amdgpu_dm_update_crtc_color_mgmt(काष्ठा dm_crtc_state *crtc);
पूर्णांक amdgpu_dm_update_plane_color_mgmt(काष्ठा dm_crtc_state *crtc,
				      काष्ठा dc_plane_state *dc_plane_state);

व्योम amdgpu_dm_update_connector_after_detect(
		काष्ठा amdgpu_dm_connector *aconnector);

बाह्य स्थिर काष्ठा drm_encoder_helper_funcs amdgpu_dm_encoder_helper_funcs;

#पूर्ण_अगर /* __AMDGPU_DM_H__ */
