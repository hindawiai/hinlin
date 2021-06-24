<शैली गुरु>
/*
 * Copyright 2012-14 Advanced Micro Devices, Inc.
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

#अगर_अघोषित DC_INTERFACE_H_
#घोषणा DC_INTERFACE_H_

#समावेश "dc_types.h"
#समावेश "grph_object_defs.h"
#समावेश "logger_types.h"
#अगर defined(CONFIG_DRM_AMD_DC_HDCP)
#समावेश "hdcp_types.h"
#पूर्ण_अगर
#समावेश "gpio_types.h"
#समावेश "link_service_types.h"
#समावेश "grph_object_ctrl_defs.h"
#समावेश <inc/hw/opp.h>

#समावेश "inc/hw_sequencer.h"
#समावेश "inc/compressor.h"
#समावेश "inc/hw/dmcu.h"
#समावेश "dml/display_mode_lib.h"

/* क्रमward declaration */
काष्ठा aux_payload;

#घोषणा DC_VER "3.2.132"

#घोषणा MAX_SURFACES 3
#घोषणा MAX_PLANES 6
#घोषणा MAX_STREAMS 6
#घोषणा MAX_SINKS_PER_LINK 4
#घोषणा MIN_VIEWPORT_SIZE 12
#घोषणा MAX_NUM_EDP 2

/*******************************************************************************
 * Display Core Interfaces
 ******************************************************************************/
काष्ठा dc_versions अणु
	स्थिर अक्षर *dc_ver;
	काष्ठा dmcu_version dmcu_version;
पूर्ण;

क्रमागत dp_protocol_version अणु
	DP_VERSION_1_4,
पूर्ण;

क्रमागत dc_plane_type अणु
	DC_PLANE_TYPE_INVALID,
	DC_PLANE_TYPE_DCE_RGB,
	DC_PLANE_TYPE_DCE_UNDERLAY,
	DC_PLANE_TYPE_DCN_UNIVERSAL,
पूर्ण;

काष्ठा dc_plane_cap अणु
	क्रमागत dc_plane_type type;
	uपूर्णांक32_t blends_with_above : 1;
	uपूर्णांक32_t blends_with_below : 1;
	uपूर्णांक32_t per_pixel_alpha : 1;
	काष्ठा अणु
		uपूर्णांक32_t argb8888 : 1;
		uपूर्णांक32_t nv12 : 1;
		uपूर्णांक32_t fp16 : 1;
		uपूर्णांक32_t p010 : 1;
		uपूर्णांक32_t ayuv : 1;
	पूर्ण pixel_क्रमmat_support;
	// max upscaling factor x1000
	// upscaling factors are always >= 1
	// क्रम example, 1080p -> 8K is 4.0, or 4000 raw value
	काष्ठा अणु
		uपूर्णांक32_t argb8888;
		uपूर्णांक32_t nv12;
		uपूर्णांक32_t fp16;
	पूर्ण max_upscale_factor;
	// max करोwnscale factor x1000
	// करोwnscale factors are always <= 1
	// क्रम example, 8K -> 1080p is 0.25, or 250 raw value
	काष्ठा अणु
		uपूर्णांक32_t argb8888;
		uपूर्णांक32_t nv12;
		uपूर्णांक32_t fp16;
	पूर्ण max_करोwnscale_factor;
	// minimal width/height
	uपूर्णांक32_t min_width;
	uपूर्णांक32_t min_height;
पूर्ण;

// Color management caps (DPP and MPC)
काष्ठा rom_curve_caps अणु
	uपूर्णांक16_t srgb : 1;
	uपूर्णांक16_t bt2020 : 1;
	uपूर्णांक16_t gamma2_2 : 1;
	uपूर्णांक16_t pq : 1;
	uपूर्णांक16_t hlg : 1;
पूर्ण;

काष्ठा dpp_color_caps अणु
	uपूर्णांक16_t dcn_arch : 1; // all DCE generations treated the same
	// input lut is dअगरferent than most LUTs, just plain 256-entry lookup
	uपूर्णांक16_t input_lut_shared : 1; // shared with DGAM
	uपूर्णांक16_t icsc : 1;
	uपूर्णांक16_t dgam_ram : 1;
	uपूर्णांक16_t post_csc : 1; // beक्रमe gamut remap
	uपूर्णांक16_t gamma_corr : 1;

	// hdr_mult and gamut remap always available in DPP (in that order)
	// 3d lut implies shaper LUT,
	// it may be shared with MPC - check MPC:shared_3d_lut flag
	uपूर्णांक16_t hw_3d_lut : 1;
	uपूर्णांक16_t ogam_ram : 1; // blnd gam
	uपूर्णांक16_t ocsc : 1;
	uपूर्णांक16_t dgam_rom_क्रम_yuv : 1;
	काष्ठा rom_curve_caps dgam_rom_caps;
	काष्ठा rom_curve_caps ogam_rom_caps;
पूर्ण;

काष्ठा mpc_color_caps अणु
	uपूर्णांक16_t gamut_remap : 1;
	uपूर्णांक16_t ogam_ram : 1;
	uपूर्णांक16_t ocsc : 1;
	uपूर्णांक16_t num_3dluts : 3; //3d lut always assumes a preceding shaper LUT
	uपूर्णांक16_t shared_3d_lut:1; //can be in either DPP or MPC, but single instance

	काष्ठा rom_curve_caps ogam_rom_caps;
पूर्ण;

काष्ठा dc_color_caps अणु
	काष्ठा dpp_color_caps dpp;
	काष्ठा mpc_color_caps mpc;
पूर्ण;

काष्ठा dc_caps अणु
	uपूर्णांक32_t max_streams;
	uपूर्णांक32_t max_links;
	uपूर्णांक32_t max_audios;
	uपूर्णांक32_t max_slave_planes;
	uपूर्णांक32_t max_slave_yuv_planes;
	uपूर्णांक32_t max_slave_rgb_planes;
	uपूर्णांक32_t max_planes;
	uपूर्णांक32_t max_करोwnscale_ratio;
	uपूर्णांक32_t i2c_speed_in_khz;
	uपूर्णांक32_t i2c_speed_in_khz_hdcp;
	uपूर्णांक32_t dmdata_alloc_size;
	अचिन्हित पूर्णांक max_cursor_size;
	अचिन्हित पूर्णांक max_video_width;
	अचिन्हित पूर्णांक min_horizontal_blanking_period;
	पूर्णांक linear_pitch_alignment;
	bool dcc_स्थिर_color;
	bool dynamic_audio;
	bool is_apu;
	bool dual_link_dvi;
	bool post_blend_color_processing;
	bool क्रमce_dp_tps4_क्रम_cp2520;
	bool disable_dp_clk_share;
	bool psp_setup_panel_mode;
	bool extended_aux_समयout_support;
	bool dmcub_support;
	uपूर्णांक32_t num_of_पूर्णांकernal_disp;
	क्रमागत dp_protocol_version max_dp_protocol_version;
	अचिन्हित पूर्णांक mall_size_per_mem_channel;
	अचिन्हित पूर्णांक mall_माप_प्रकारotal;
	अचिन्हित पूर्णांक cursor_cache_size;
	काष्ठा dc_plane_cap planes[MAX_PLANES];
	काष्ठा dc_color_caps color;
पूर्ण;

काष्ठा dc_bug_wa अणु
	bool no_connect_phy_config;
	bool dedcn20_305_wa;
	bool skip_घड़ी_update;
	bool lt_early_cr_pattern;
पूर्ण;

काष्ठा dc_dcc_surface_param अणु
	काष्ठा dc_size surface_size;
	क्रमागत surface_pixel_क्रमmat क्रमmat;
	क्रमागत swizzle_mode_values swizzle_mode;
	क्रमागत dc_scan_direction scan;
पूर्ण;

काष्ठा dc_dcc_setting अणु
	अचिन्हित पूर्णांक max_compressed_blk_size;
	अचिन्हित पूर्णांक max_uncompressed_blk_size;
	bool independent_64b_blks;
#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	//These bitfields to be used starting with DCN 3.0
	काष्ठा अणु
		uपूर्णांक32_t dcc_256_64_64 : 1;//available in ASICs beक्रमe DCN 3.0 (the worst compression हाल)
		uपूर्णांक32_t dcc_128_128_uncontrained : 1;  //available in ASICs beक्रमe DCN 3.0
		uपूर्णांक32_t dcc_256_128_128 : 1;		//available starting with DCN 3.0
		uपूर्णांक32_t dcc_256_256_unस्थिरrained : 1;  //available in ASICs beक्रमe DCN 3.0 (the best compression हाल)
	पूर्ण dcc_controls;
#पूर्ण_अगर
पूर्ण;

काष्ठा dc_surface_dcc_cap अणु
	जोड़ अणु
		काष्ठा अणु
			काष्ठा dc_dcc_setting rgb;
		पूर्ण grph;

		काष्ठा अणु
			काष्ठा dc_dcc_setting luma;
			काष्ठा dc_dcc_setting chroma;
		पूर्ण video;
	पूर्ण;

	bool capable;
	bool स्थिर_color_support;
पूर्ण;

काष्ठा dc_अटल_screen_params अणु
	काष्ठा अणु
		bool क्रमce_trigger;
		bool cursor_update;
		bool surface_update;
		bool overlay_update;
	पूर्ण triggers;
	अचिन्हित पूर्णांक num_frames;
पूर्ण;


/* Surface update type is used by dc_update_surfaces_and_stream
 * The update type is determined at the very beginning of the function based
 * on parameters passed in and decides how much programming (or updating) is
 * going to be करोne during the call.
 *
 * UPDATE_TYPE_FAST is used क्रम really fast updates that करो not require much
 * logical calculations or hardware रेजिस्टर programming. This update MUST be
 * ISR safe on winकरोws. Currently fast update will only be used to flip surface
 * address.
 *
 * UPDATE_TYPE_MED is used क्रम slower updates which require signअगरicant hw
 * re-programming however करो not affect bandwidth consumption or घड़ी
 * requirements. At present, this is the level at which front end updates
 * that करो not require us to run bw_calcs happen. These are in/out transfer func
 * updates, viewport offset changes, recout size changes and pixel depth changes.
 * This update can be करोne at ISR, but we want to minimize how often this happens.
 *
 * UPDATE_TYPE_FULL is slow. Really slow. This requires us to recalculate our
 * bandwidth and घड़ीs, possibly rearrange some pipes and reprogram anything front
 * end related. Any समय viewport dimensions, recout dimensions, scaling ratios or
 * gamma need to be adjusted or pipe needs to be turned on (or disconnected) we करो
 * a full update. This cannot be करोne at ISR level and should be a rare event.
 * Unless someone is stress testing mpo enter/निकास, playing with colour or adjusting
 * underscan we करोn't expect to see this call at all.
 */

क्रमागत surface_update_type अणु
	UPDATE_TYPE_FAST, /* super fast, safe to execute in isr */
	UPDATE_TYPE_MED,  /* ISR safe, most of programming needed, no bw/clk change*/
	UPDATE_TYPE_FULL, /* may need to shuffle resources */
पूर्ण;

/* Forward declaration*/
काष्ठा dc;
काष्ठा dc_plane_state;
काष्ठा dc_state;


काष्ठा dc_cap_funcs अणु
	bool (*get_dcc_compression_cap)(स्थिर काष्ठा dc *dc,
			स्थिर काष्ठा dc_dcc_surface_param *input,
			काष्ठा dc_surface_dcc_cap *output);
पूर्ण;

काष्ठा link_training_settings;


/* Structure to hold configuration flags set by dm at dc creation. */
काष्ठा dc_config अणु
	bool gpu_vm_support;
	bool disable_disp_pll_sharing;
	bool fbc_support;
	bool disable_fractional_pwm;
	bool allow_seamless_boot_optimization;
	bool घातer_करोwn_display_on_boot;
	bool edp_not_connected;
	bool क्रमce_क्रमागत_edp;
	bool क्रमced_घड़ीs;
	bool allow_lttpr_non_transparent_mode;
	bool multi_mon_pp_mclk_चयन;
	bool disable_dmcu;
	bool enable_4to1MPC;
#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	bool clamp_min_dcfclk;
#पूर्ण_अगर
	uपूर्णांक64_t vblank_alignment_dto_params;
	uपूर्णांक8_t  vblank_alignment_max_frame_समय_dअगरf;
	bool is_asymmetric_memory;
	bool is_single_rank_dimm;
पूर्ण;

क्रमागत visual_confirm अणु
	VISUAL_CONFIRM_DISABLE = 0,
	VISUAL_CONFIRM_SURFACE = 1,
	VISUAL_CONFIRM_HDR = 2,
	VISUAL_CONFIRM_MPCTREE = 4,
	VISUAL_CONFIRM_PSR = 5,
पूर्ण;

क्रमागत dcc_option अणु
	DCC_ENABLE = 0,
	DCC_DISABLE = 1,
	DCC_HALF_REQ_DISALBE = 2,
पूर्ण;

क्रमागत pipe_split_policy अणु
	MPC_SPLIT_DYNAMIC = 0,
	MPC_SPLIT_AVOID = 1,
	MPC_SPLIT_AVOID_MULT_DISP = 2,
पूर्ण;

क्रमागत wm_report_mode अणु
	WM_REPORT_DEFAULT = 0,
	WM_REPORT_OVERRIDE = 1,
पूर्ण;
क्रमागत dपंचांग_pstateअणु
	dपंचांग_level_p0 = 0,/*highest voltage*/
	dपंचांग_level_p1,
	dपंचांग_level_p2,
	dपंचांग_level_p3,
	dपंचांग_level_p4,/*when active_display_count = 0*/
पूर्ण;

क्रमागत dcn_pwr_state अणु
	DCN_PWR_STATE_UNKNOWN = -1,
	DCN_PWR_STATE_MISSION_MODE = 0,
	DCN_PWR_STATE_LOW_POWER = 3,
पूर्ण;

/*
 * For any घड़ीs that may dअगरfer per pipe
 * only the max is stored in this काष्ठाure
 */
काष्ठा dc_घड़ीs अणु
	पूर्णांक dispclk_khz;
	पूर्णांक actual_dispclk_khz;
	पूर्णांक dppclk_khz;
	पूर्णांक actual_dppclk_khz;
	पूर्णांक disp_dpp_voltage_level_khz;
	पूर्णांक dcfclk_khz;
	पूर्णांक socclk_khz;
	पूर्णांक dcfclk_deep_sleep_khz;
	पूर्णांक fclk_khz;
	पूर्णांक phyclk_khz;
	पूर्णांक dramclk_khz;
	bool p_state_change_support;
	क्रमागत dcn_pwr_state pwr_state;
	/*
	 * Elements below are not compared क्रम the purposes of
	 * optimization required
	 */
	bool prev_p_state_change_support;
	क्रमागत dपंचांग_pstate dपंचांग_level;
	पूर्णांक max_supported_dppclk_khz;
	पूर्णांक max_supported_dispclk_khz;
	पूर्णांक bw_dppclk_khz; /*a copy of dppclk_khz*/
	पूर्णांक bw_dispclk_khz;
पूर्ण;

काष्ठा dc_bw_validation_profile अणु
	bool enable;

	अचिन्हित दीर्घ दीर्घ total_ticks;
	अचिन्हित दीर्घ दीर्घ voltage_level_ticks;
	अचिन्हित दीर्घ दीर्घ watermark_ticks;
	अचिन्हित दीर्घ दीर्घ rq_dlg_ticks;

	अचिन्हित दीर्घ दीर्घ total_count;
	अचिन्हित दीर्घ दीर्घ skip_fast_count;
	अचिन्हित दीर्घ दीर्घ skip_pass_count;
	अचिन्हित दीर्घ दीर्घ skip_fail_count;
पूर्ण;

#घोषणा BW_VAL_TRACE_SETUP() \
		अचिन्हित दीर्घ दीर्घ end_tick = 0; \
		अचिन्हित दीर्घ दीर्घ voltage_level_tick = 0; \
		अचिन्हित दीर्घ दीर्घ watermark_tick = 0; \
		अचिन्हित दीर्घ दीर्घ start_tick = dc->debug.bw_val_profile.enable ? \
				dm_get_बारtamp(dc->ctx) : 0

#घोषणा BW_VAL_TRACE_COUNT() \
		अगर (dc->debug.bw_val_profile.enable) \
			dc->debug.bw_val_profile.total_count++

#घोषणा BW_VAL_TRACE_SKIP(status) \
		अगर (dc->debug.bw_val_profile.enable) अणु \
			अगर (!voltage_level_tick) \
				voltage_level_tick = dm_get_बारtamp(dc->ctx); \
			dc->debug.bw_val_profile.skip_ ## status ## _count++; \
		पूर्ण

#घोषणा BW_VAL_TRACE_END_VOLTAGE_LEVEL() \
		अगर (dc->debug.bw_val_profile.enable) \
			voltage_level_tick = dm_get_बारtamp(dc->ctx)

#घोषणा BW_VAL_TRACE_END_WATERMARKS() \
		अगर (dc->debug.bw_val_profile.enable) \
			watermark_tick = dm_get_बारtamp(dc->ctx)

#घोषणा BW_VAL_TRACE_FINISH() \
		अगर (dc->debug.bw_val_profile.enable) अणु \
			end_tick = dm_get_बारtamp(dc->ctx); \
			dc->debug.bw_val_profile.total_ticks += end_tick - start_tick; \
			dc->debug.bw_val_profile.voltage_level_ticks += voltage_level_tick - start_tick; \
			अगर (watermark_tick) अणु \
				dc->debug.bw_val_profile.watermark_ticks += watermark_tick - voltage_level_tick; \
				dc->debug.bw_val_profile.rq_dlg_ticks += end_tick - watermark_tick; \
			पूर्ण \
		पूर्ण

जोड़ mem_low_घातer_enable_options अणु
	काष्ठा अणु
		bool i2c: 1;
		bool dmcu: 1;
		bool dscl: 1;
		bool cm: 1;
		bool mpc: 1;
		bool optc: 1;
	पूर्ण bits;
	uपूर्णांक32_t u32All;
पूर्ण;

काष्ठा dc_debug_options अणु
	क्रमागत visual_confirm visual_confirm;
	bool sanity_checks;
	bool max_disp_clk;
	bool surface_trace;
	bool timing_trace;
	bool घड़ी_प्रकारrace;
	bool validation_trace;
	bool bandwidth_calcs_trace;
	पूर्णांक max_करोwnscale_src_width;

	/* stutter efficiency related */
	bool disable_stutter;
	bool use_max_lb;
	क्रमागत dcc_option disable_dcc;
	क्रमागत pipe_split_policy pipe_split_policy;
	bool क्रमce_single_disp_pipe_split;
	bool voltage_align_fclk;
	bool disable_min_fclk;

	bool disable_dfs_bypass;
	bool disable_dpp_घातer_gate;
	bool disable_hubp_घातer_gate;
	bool disable_dsc_घातer_gate;
	पूर्णांक dsc_min_slice_height_override;
	पूर्णांक dsc_bpp_increment_भाग;
	bool native422_support;
	bool disable_pplib_wm_range;
	क्रमागत wm_report_mode pplib_wm_report_mode;
	अचिन्हित पूर्णांक min_disp_clk_khz;
	अचिन्हित पूर्णांक min_dpp_clk_khz;
	पूर्णांक sr_निकास_समय_dpm0_ns;
	पूर्णांक sr_enter_plus_निकास_समय_dpm0_ns;
	पूर्णांक sr_निकास_समय_ns;
	पूर्णांक sr_enter_plus_निकास_समय_ns;
	पूर्णांक urgent_latency_ns;
	uपूर्णांक32_t underflow_निश्चित_delay_us;
	पूर्णांक percent_of_ideal_drambw;
	पूर्णांक dram_घड़ी_change_latency_ns;
	bool optimized_watermark;
	पूर्णांक always_scale;
	bool disable_pplib_घड़ी_request;
	bool disable_घड़ी_gate;
	bool disable_mem_low_घातer;
	bool disable_dmcu;
	bool disable_psr;
	bool क्रमce_abm_enable;
	bool disable_stereo_support;
	bool vsr_support;
	bool perक्रमmance_trace;
	bool az_endpoपूर्णांक_mute_only;
	bool always_use_regamma;
	bool recovery_enabled;
	bool aव्योम_vbios_exec_table;
	bool scl_reset_length10;
	bool hdmi20_disable;
	bool skip_detection_link_training;
	uपूर्णांक32_t edid_पढ़ो_retry_बार;
	bool हटाओ_disconnect_edp;
	अचिन्हित पूर्णांक क्रमce_odm_combine; //bit vector based on otg inst
#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	अचिन्हित पूर्णांक क्रमce_odm_combine_4to1; //bit vector based on otg inst
#पूर्ण_अगर
	अचिन्हित पूर्णांक क्रमce_fclk_khz;
	bool enable_tri_buf;
	bool dmub_offload_enabled;
	bool dmcub_emulation;
#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	bool disable_idle_घातer_optimizations;
	अचिन्हित पूर्णांक mall_size_override;
	अचिन्हित पूर्णांक mall_additional_समयr_percent;
	bool mall_error_as_fatal;
#पूर्ण_अगर
	bool dmub_command_table; /* क्रम testing only */
	काष्ठा dc_bw_validation_profile bw_val_profile;
	bool disable_fec;
	bool disable_48mhz_pwrdwn;
	/* This क्रमces a hard min on the DCFCLK requested to SMU/PP
	 * watermarks are not affected.
	 */
	अचिन्हित पूर्णांक क्रमce_min_dcfclk_mhz;
#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	पूर्णांक dwb_fi_phase;
#पूर्ण_अगर
	bool disable_timing_sync;
	bool cm_in_bypass;
	पूर्णांक क्रमce_घड़ी_mode;/*every mode change.*/

	bool disable_dram_घड़ी_change_vactive_support;
	bool validate_dml_output;
	bool enable_dmcub_surface_flip;
	bool usbc_combo_phy_reset_wa;
	bool disable_dsc;
	bool enable_dram_घड़ी_change_one_display_vactive;
	जोड़ mem_low_घातer_enable_options enable_mem_low_घातer;
	bool क्रमce_vblank_alignment;

	/* Enable dmub aux क्रम legacy ddc */
	bool enable_dmub_aux_क्रम_legacy_ddc;
	bool optimize_edp_link_rate; /* eDP ILR */
	/* क्रमce enable edp FEC */
	bool क्रमce_enable_edp_fec;
	/* FEC/PSR1 sequence enable delay in 100us */
	uपूर्णांक8_t fec_enable_delay_in100us;
पूर्ण;

काष्ठा dc_debug_data अणु
	uपूर्णांक32_t ltFailCount;
	uपूर्णांक32_t i2cErrorCount;
	uपूर्णांक32_t auxErrorCount;
पूर्ण;

काष्ठा dc_phy_addr_space_config अणु
	काष्ठा अणु
		uपूर्णांक64_t start_addr;
		uपूर्णांक64_t end_addr;
		uपूर्णांक64_t fb_top;
		uपूर्णांक64_t fb_offset;
		uपूर्णांक64_t fb_base;
		uपूर्णांक64_t agp_top;
		uपूर्णांक64_t agp_bot;
		uपूर्णांक64_t agp_base;
	पूर्ण प्रणाली_aperture;

	काष्ठा अणु
		uपूर्णांक64_t page_table_start_addr;
		uपूर्णांक64_t page_table_end_addr;
		uपूर्णांक64_t page_table_base_addr;
	पूर्ण gart_config;

	bool valid;
	bool is_hvm_enabled;
	uपूर्णांक64_t page_table_शेष_page_addr;
पूर्ण;

काष्ठा dc_भव_addr_space_config अणु
	uपूर्णांक64_t	page_table_base_addr;
	uपूर्णांक64_t	page_table_start_addr;
	uपूर्णांक64_t	page_table_end_addr;
	uपूर्णांक32_t	page_table_block_size_in_bytes;
	uपूर्णांक8_t		page_table_depth; // 1 = 1 level, 2 = 2 level, etc.  0 = invalid
पूर्ण;

काष्ठा dc_bounding_box_overrides अणु
	पूर्णांक sr_निकास_समय_ns;
	पूर्णांक sr_enter_plus_निकास_समय_ns;
	पूर्णांक urgent_latency_ns;
	पूर्णांक percent_of_ideal_drambw;
	पूर्णांक dram_घड़ी_change_latency_ns;
	पूर्णांक dummy_घड़ी_change_latency_ns;
	/* This क्रमces a hard min on the DCFCLK we use
	 * क्रम DML.  Unlike the debug option क्रम क्रमcing
	 * DCFCLK, this override affects watermark calculations
	 */
	पूर्णांक min_dcfclk_mhz;
पूर्ण;

काष्ठा dc_state;
काष्ठा resource_pool;
काष्ठा dce_hwseq;
काष्ठा gpu_info_soc_bounding_box_v1_0;
काष्ठा dc अणु
	काष्ठा dc_versions versions;
	काष्ठा dc_caps caps;
	काष्ठा dc_cap_funcs cap_funcs;
	काष्ठा dc_config config;
	काष्ठा dc_debug_options debug;
	काष्ठा dc_bounding_box_overrides bb_overrides;
	काष्ठा dc_bug_wa work_arounds;
	काष्ठा dc_context *ctx;
	काष्ठा dc_phy_addr_space_config vm_pa_config;

	uपूर्णांक8_t link_count;
	काष्ठा dc_link *links[MAX_PIPES * 2];

	काष्ठा dc_state *current_state;
	काष्ठा resource_pool *res_pool;

	काष्ठा clk_mgr *clk_mgr;

	/* Display Engine Clock levels */
	काष्ठा dm_pp_घड़ी_levels sclk_lvls;

	/* Inमाला_दो पूर्णांकo BW and WM calculations. */
	काष्ठा bw_calcs_dceip *bw_dceip;
	काष्ठा bw_calcs_vbios *bw_vbios;
#अगर_घोषित CONFIG_DRM_AMD_DC_DCN
	काष्ठा dcn_soc_bounding_box *dcn_soc;
	काष्ठा dcn_ip_params *dcn_ip;
	काष्ठा display_mode_lib dml;
#पूर्ण_अगर

	/* HW functions */
	काष्ठा hw_sequencer_funcs hwss;
	काष्ठा dce_hwseq *hwseq;

	/* Require to optimize घड़ीs and bandwidth क्रम added/हटाओd planes */
	bool optimized_required;
	bool wm_optimized_required;
#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	bool idle_optimizations_allowed;
#पूर्ण_अगर

	/* Require to मुख्यtain घड़ीs and bandwidth क्रम UEFI enabled HW */

	/* FBC compressor */
	काष्ठा compressor *fbc_compressor;

	काष्ठा dc_debug_data debug_data;
	काष्ठा dpcd_venकरोr_signature venकरोr_signature;

	स्थिर अक्षर *build_id;
	काष्ठा vm_helper *vm_helper;
पूर्ण;

क्रमागत frame_buffer_mode अणु
	FRAME_BUFFER_MODE_LOCAL_ONLY = 0,
	FRAME_BUFFER_MODE_ZFB_ONLY,
	FRAME_BUFFER_MODE_MIXED_ZFB_AND_LOCAL,
पूर्ण ;

काष्ठा dchub_init_data अणु
	पूर्णांक64_t zfb_phys_addr_base;
	पूर्णांक64_t zfb_mc_base_addr;
	uपूर्णांक64_t zfb_size_in_byte;
	क्रमागत frame_buffer_mode fb_mode;
	bool dchub_initialzied;
	bool dchub_info_valid;
पूर्ण;

काष्ठा dc_init_data अणु
	काष्ठा hw_asic_id asic_id;
	व्योम *driver; /* ctx */
	काष्ठा cgs_device *cgs_device;
	काष्ठा dc_bounding_box_overrides bb_overrides;

	पूर्णांक num_भव_links;
	/*
	 * If 'vbios_override' not शून्य, it will be called instead
	 * of the real VBIOS. Intended use is Diagnostics on FPGA.
	 */
	काष्ठा dc_bios *vbios_override;
	क्रमागत dce_environment dce_environment;

	काष्ठा dmub_offload_funcs *dmub_अगर;
	काष्ठा dc_reg_helper_state *dmub_offload;

	काष्ठा dc_config flags;
	uपूर्णांक64_t log_mask;

	काष्ठा dpcd_venकरोr_signature venकरोr_signature;
#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	bool क्रमce_smu_not_present;
#पूर्ण_अगर
पूर्ण;

काष्ठा dc_callback_init अणु
#अगर_घोषित CONFIG_DRM_AMD_DC_HDCP
	काष्ठा cp_psp cp_psp;
#अन्यथा
	uपूर्णांक8_t reserved;
#पूर्ण_अगर
पूर्ण;

काष्ठा dc *dc_create(स्थिर काष्ठा dc_init_data *init_params);
व्योम dc_hardware_init(काष्ठा dc *dc);

पूर्णांक dc_get_vmid_use_vector(काष्ठा dc *dc);
व्योम dc_setup_vm_context(काष्ठा dc *dc, काष्ठा dc_भव_addr_space_config *va_config, पूर्णांक vmid);
/* Returns the number of vmids supported */
पूर्णांक dc_setup_प्रणाली_context(काष्ठा dc *dc, काष्ठा dc_phy_addr_space_config *pa_config);
व्योम dc_init_callbacks(काष्ठा dc *dc,
		स्थिर काष्ठा dc_callback_init *init_params);
व्योम dc_deinit_callbacks(काष्ठा dc *dc);
व्योम dc_destroy(काष्ठा dc **dc);

व्योम dc_रुको_क्रम_vblank(काष्ठा dc *dc, काष्ठा dc_stream_state *stream);
/*******************************************************************************
 * Surface Interfaces
 ******************************************************************************/

क्रमागत अणु
	TRANSFER_FUNC_POINTS = 1025
पूर्ण;

काष्ठा dc_hdr_अटल_metadata अणु
	/* display chromaticities and white poपूर्णांक in units of 0.00001 */
	अचिन्हित पूर्णांक chromaticity_green_x;
	अचिन्हित पूर्णांक chromaticity_green_y;
	अचिन्हित पूर्णांक chromaticity_blue_x;
	अचिन्हित पूर्णांक chromaticity_blue_y;
	अचिन्हित पूर्णांक chromaticity_red_x;
	अचिन्हित पूर्णांक chromaticity_red_y;
	अचिन्हित पूर्णांक chromaticity_white_poपूर्णांक_x;
	अचिन्हित पूर्णांक chromaticity_white_poपूर्णांक_y;

	uपूर्णांक32_t min_luminance;
	uपूर्णांक32_t max_luminance;
	uपूर्णांक32_t maximum_content_light_level;
	uपूर्णांक32_t maximum_frame_average_light_level;
पूर्ण;

क्रमागत dc_transfer_func_type अणु
	TF_TYPE_PREDEFINED,
	TF_TYPE_DISTRIBUTED_POINTS,
	TF_TYPE_BYPASS,
	TF_TYPE_HWPWL
पूर्ण;

काष्ठा dc_transfer_func_distributed_poपूर्णांकs अणु
	काष्ठा fixed31_32 red[TRANSFER_FUNC_POINTS];
	काष्ठा fixed31_32 green[TRANSFER_FUNC_POINTS];
	काष्ठा fixed31_32 blue[TRANSFER_FUNC_POINTS];

	uपूर्णांक16_t end_exponent;
	uपूर्णांक16_t x_poपूर्णांक_at_y1_red;
	uपूर्णांक16_t x_poपूर्णांक_at_y1_green;
	uपूर्णांक16_t x_poपूर्णांक_at_y1_blue;
पूर्ण;

क्रमागत dc_transfer_func_predefined अणु
	TRANSFER_FUNCTION_SRGB,
	TRANSFER_FUNCTION_BT709,
	TRANSFER_FUNCTION_PQ,
	TRANSFER_FUNCTION_LINEAR,
	TRANSFER_FUNCTION_UNITY,
	TRANSFER_FUNCTION_HLG,
	TRANSFER_FUNCTION_HLG12,
	TRANSFER_FUNCTION_GAMMA22,
	TRANSFER_FUNCTION_GAMMA24,
	TRANSFER_FUNCTION_GAMMA26
पूर्ण;


काष्ठा dc_transfer_func अणु
	काष्ठा kref refcount;
	क्रमागत dc_transfer_func_type type;
	क्रमागत dc_transfer_func_predefined tf;
	/* FP16 1.0 reference level in nits, शेष is 80 nits, only क्रम PQ*/
	uपूर्णांक32_t sdr_ref_white_level;
	जोड़ अणु
		काष्ठा pwl_params pwl;
		काष्ठा dc_transfer_func_distributed_poपूर्णांकs tf_pts;
	पूर्ण;
पूर्ण;


जोड़ dc_3dlut_state अणु
	काष्ठा अणु
		uपूर्णांक32_t initialized:1;		/*अगर 3dlut is went through color module क्रम initialization */
		uपूर्णांक32_t rmu_idx_valid:1;	/*अगर mux settings are valid*/
		uपूर्णांक32_t rmu_mux_num:3;		/*index of mux to use*/
		uपूर्णांक32_t mpc_rmu0_mux:4;	/*select mpcc on mux, one of the following : mpcc0, mpcc1, mpcc2, mpcc3*/
		uपूर्णांक32_t mpc_rmu1_mux:4;
		uपूर्णांक32_t mpc_rmu2_mux:4;
		uपूर्णांक32_t reserved:15;
	पूर्ण bits;
	uपूर्णांक32_t raw;
पूर्ण;


काष्ठा dc_3dlut अणु
	काष्ठा kref refcount;
	काष्ठा tetrahedral_params lut_3d;
	काष्ठा fixed31_32 hdr_multiplier;
	जोड़ dc_3dlut_state state;
पूर्ण;
/*
 * This काष्ठाure is filled in by dc_surface_get_status and contains
 * the last requested address and the currently active address so the called
 * can determine अगर there are any outstanding flips
 */
काष्ठा dc_plane_status अणु
	काष्ठा dc_plane_address requested_address;
	काष्ठा dc_plane_address current_address;
	bool is_flip_pending;
	bool is_right_eye;
पूर्ण;

जोड़ surface_update_flags अणु

	काष्ठा अणु
		uपूर्णांक32_t addr_update:1;
		/* Medium updates */
		uपूर्णांक32_t dcc_change:1;
		uपूर्णांक32_t color_space_change:1;
		uपूर्णांक32_t horizontal_mirror_change:1;
		uपूर्णांक32_t per_pixel_alpha_change:1;
		uपूर्णांक32_t global_alpha_change:1;
		uपूर्णांक32_t hdr_mult:1;
		uपूर्णांक32_t rotation_change:1;
		uपूर्णांक32_t swizzle_change:1;
		uपूर्णांक32_t scaling_change:1;
		uपूर्णांक32_t position_change:1;
		uपूर्णांक32_t in_transfer_func_change:1;
		uपूर्णांक32_t input_csc_change:1;
		uपूर्णांक32_t coeff_reduction_change:1;
		uपूर्णांक32_t output_tf_change:1;
		uपूर्णांक32_t pixel_क्रमmat_change:1;
		uपूर्णांक32_t plane_size_change:1;
		uपूर्णांक32_t gamut_remap_change:1;

		/* Full updates */
		uपूर्णांक32_t new_plane:1;
		uपूर्णांक32_t bpp_change:1;
		uपूर्णांक32_t gamma_change:1;
		uपूर्णांक32_t bandwidth_change:1;
		uपूर्णांक32_t घड़ी_change:1;
		uपूर्णांक32_t stereo_क्रमmat_change:1;
		uपूर्णांक32_t full_update:1;
	पूर्ण bits;

	uपूर्णांक32_t raw;
पूर्ण;

काष्ठा dc_plane_state अणु
	काष्ठा dc_plane_address address;
	काष्ठा dc_plane_flip_समय समय;
	bool triplebuffer_flips;
	काष्ठा scaling_taps scaling_quality;
	काष्ठा rect src_rect;
	काष्ठा rect dst_rect;
	काष्ठा rect clip_rect;

	काष्ठा plane_size plane_size;
	जोड़ dc_tiling_info tiling_info;

	काष्ठा dc_plane_dcc_param dcc;

	काष्ठा dc_gamma *gamma_correction;
	काष्ठा dc_transfer_func *in_transfer_func;
	काष्ठा dc_bias_and_scale *bias_and_scale;
	काष्ठा dc_csc_transक्रमm input_csc_color_matrix;
	काष्ठा fixed31_32 coeff_reduction_factor;
	काष्ठा fixed31_32 hdr_mult;
	काष्ठा colorspace_transक्रमm gamut_remap_matrix;

	// TODO: No दीर्घer used, हटाओ
	काष्ठा dc_hdr_अटल_metadata hdr_अटल_ctx;

	क्रमागत dc_color_space color_space;

	काष्ठा dc_3dlut *lut3d_func;
	काष्ठा dc_transfer_func *in_shaper_func;
	काष्ठा dc_transfer_func *blend_tf;

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	काष्ठा dc_transfer_func *gamcor_tf;
#पूर्ण_अगर
	क्रमागत surface_pixel_क्रमmat क्रमmat;
	क्रमागत dc_rotation_angle rotation;
	क्रमागत plane_stereo_क्रमmat stereo_क्रमmat;

	bool is_tiling_rotated;
	bool per_pixel_alpha;
	bool global_alpha;
	पूर्णांक  global_alpha_value;
	bool visible;
	bool flip_immediate;
	bool horizontal_mirror;
	पूर्णांक layer_index;

	जोड़ surface_update_flags update_flags;
	bool flip_पूर्णांक_enabled;
	bool skip_manual_trigger;

	/* निजी to DC core */
	काष्ठा dc_plane_status status;
	काष्ठा dc_context *ctx;

	/* HACK: Workaround क्रम क्रमcing full reprogramming under some conditions */
	bool क्रमce_full_update;

	/* निजी to dc_surface.c */
	क्रमागत dc_irq_source irq_source;
	काष्ठा kref refcount;
पूर्ण;

काष्ठा dc_plane_info अणु
	काष्ठा plane_size plane_size;
	जोड़ dc_tiling_info tiling_info;
	काष्ठा dc_plane_dcc_param dcc;
	क्रमागत surface_pixel_क्रमmat क्रमmat;
	क्रमागत dc_rotation_angle rotation;
	क्रमागत plane_stereo_क्रमmat stereo_क्रमmat;
	क्रमागत dc_color_space color_space;
	bool horizontal_mirror;
	bool visible;
	bool per_pixel_alpha;
	bool global_alpha;
	पूर्णांक  global_alpha_value;
	bool input_csc_enabled;
	पूर्णांक layer_index;
पूर्ण;

काष्ठा dc_scaling_info अणु
	काष्ठा rect src_rect;
	काष्ठा rect dst_rect;
	काष्ठा rect clip_rect;
	काष्ठा scaling_taps scaling_quality;
पूर्ण;

काष्ठा dc_surface_update अणु
	काष्ठा dc_plane_state *surface;

	/* isr safe update parameters.  null means no updates */
	स्थिर काष्ठा dc_flip_addrs *flip_addr;
	स्थिर काष्ठा dc_plane_info *plane_info;
	स्थिर काष्ठा dc_scaling_info *scaling_info;
	काष्ठा fixed31_32 hdr_mult;
	/* following updates require alloc/sleep/spin that is not isr safe,
	 * null means no updates
	 */
	स्थिर काष्ठा dc_gamma *gamma;
	स्थिर काष्ठा dc_transfer_func *in_transfer_func;

	स्थिर काष्ठा dc_csc_transक्रमm *input_csc_color_matrix;
	स्थिर काष्ठा fixed31_32 *coeff_reduction_factor;
	स्थिर काष्ठा dc_transfer_func *func_shaper;
	स्थिर काष्ठा dc_3dlut *lut3d_func;
	स्थिर काष्ठा dc_transfer_func *blend_tf;
	स्थिर काष्ठा colorspace_transक्रमm *gamut_remap_matrix;
पूर्ण;

/*
 * Create a new surface with शेष parameters;
 */
काष्ठा dc_plane_state *dc_create_plane_state(काष्ठा dc *dc);
स्थिर काष्ठा dc_plane_status *dc_plane_get_status(
		स्थिर काष्ठा dc_plane_state *plane_state);

व्योम dc_plane_state_retain(काष्ठा dc_plane_state *plane_state);
व्योम dc_plane_state_release(काष्ठा dc_plane_state *plane_state);

व्योम dc_gamma_retain(काष्ठा dc_gamma *dc_gamma);
व्योम dc_gamma_release(काष्ठा dc_gamma **dc_gamma);
काष्ठा dc_gamma *dc_create_gamma(व्योम);

व्योम dc_transfer_func_retain(काष्ठा dc_transfer_func *dc_tf);
व्योम dc_transfer_func_release(काष्ठा dc_transfer_func *dc_tf);
काष्ठा dc_transfer_func *dc_create_transfer_func(व्योम);

काष्ठा dc_3dlut *dc_create_3dlut_func(व्योम);
व्योम dc_3dlut_func_release(काष्ठा dc_3dlut *lut);
व्योम dc_3dlut_func_retain(काष्ठा dc_3dlut *lut);
/*
 * This काष्ठाure holds a surface address.  There could be multiple addresses
 * in हालs such as Stereo 3D, Planar YUV, etc.  Other per-flip attributes such
 * as frame durations and DCC क्रमmat can also be set.
 */
काष्ठा dc_flip_addrs अणु
	काष्ठा dc_plane_address address;
	अचिन्हित पूर्णांक flip_बारtamp_in_us;
	bool flip_immediate;
	/* TODO: add flip duration क्रम FreeSync */
	bool triplebuffer_flips;
पूर्ण;

व्योम dc_post_update_surfaces_to_stream(
		काष्ठा dc *dc);

#समावेश "dc_stream.h"

/*
 * Structure to store surface/stream associations क्रम validation
 */
काष्ठा dc_validation_set अणु
	काष्ठा dc_stream_state *stream;
	काष्ठा dc_plane_state *plane_states[MAX_SURFACES];
	uपूर्णांक8_t plane_count;
पूर्ण;

bool dc_validate_seamless_boot_timing(स्थिर काष्ठा dc *dc,
				स्थिर काष्ठा dc_sink *sink,
				काष्ठा dc_crtc_timing *crtc_timing);

क्रमागत dc_status dc_validate_plane(काष्ठा dc *dc, स्थिर काष्ठा dc_plane_state *plane_state);

व्योम get_घड़ी_requirements_क्रम_state(काष्ठा dc_state *state, काष्ठा AsicStateEx *info);

bool dc_set_generic_gpio_क्रम_stereo(bool enable,
		काष्ठा gpio_service *gpio_service);

/*
 * fast_validate: we वापस after determining अगर we can support the new state,
 * but beक्रमe we populate the programming info
 */
क्रमागत dc_status dc_validate_global_state(
		काष्ठा dc *dc,
		काष्ठा dc_state *new_ctx,
		bool fast_validate);


व्योम dc_resource_state_स्थिरruct(
		स्थिर काष्ठा dc *dc,
		काष्ठा dc_state *dst_ctx);

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
bool dc_acquire_release_mpc_3dlut(
		काष्ठा dc *dc, bool acquire,
		काष्ठा dc_stream_state *stream,
		काष्ठा dc_3dlut **lut,
		काष्ठा dc_transfer_func **shaper);
#पूर्ण_अगर

व्योम dc_resource_state_copy_स्थिरruct(
		स्थिर काष्ठा dc_state *src_ctx,
		काष्ठा dc_state *dst_ctx);

व्योम dc_resource_state_copy_स्थिरruct_current(
		स्थिर काष्ठा dc *dc,
		काष्ठा dc_state *dst_ctx);

व्योम dc_resource_state_deकाष्ठा(काष्ठा dc_state *context);

bool dc_resource_is_dsc_encoding_supported(स्थिर काष्ठा dc *dc);

/*
 * TODO update to make it about validation sets
 * Set up streams and links associated to drive sinks
 * The streams parameter is an असलolute set of all active streams.
 *
 * After this call:
 *   Phy, Encoder, Timing Generator are programmed and enabled.
 *   New streams are enabled with blank stream; no memory पढ़ो.
 */
bool dc_commit_state(काष्ठा dc *dc, काष्ठा dc_state *context);

व्योम dc_घातer_करोwn_on_boot(काष्ठा dc *dc);

काष्ठा dc_state *dc_create_state(काष्ठा dc *dc);
काष्ठा dc_state *dc_copy_state(काष्ठा dc_state *src_ctx);
व्योम dc_retain_state(काष्ठा dc_state *context);
व्योम dc_release_state(काष्ठा dc_state *context);

/*******************************************************************************
 * Link Interfaces
 ******************************************************************************/

काष्ठा dpcd_caps अणु
	जोड़ dpcd_rev dpcd_rev;
	जोड़ max_lane_count max_ln_count;
	जोड़ max_करोwn_spपढ़ो max_करोwn_spपढ़ो;
	जोड़ dprx_feature dprx_feature;

	/* valid only क्रम eDP v1.4 or higher*/
	uपूर्णांक8_t edp_supported_link_rates_count;
	क्रमागत dc_link_rate edp_supported_link_rates[8];

	/* करोngle type (DP converter, CV smart करोngle) */
	क्रमागत display_करोngle_type करोngle_type;
	/* branch device or sink device */
	bool is_branch_dev;
	/* Dongle's करोwnstream count. */
	जोड़ sink_count sink_count;
	/* If करोngle_type == DISPLAY_DONGLE_DP_HDMI_CONVERTER,
	indicates 'Frame Sequential-to-lllFrame Pack' conversion capability.*/
	काष्ठा dc_करोngle_caps करोngle_caps;

	uपूर्णांक32_t sink_dev_id;
	पूर्णांक8_t sink_dev_id_str[6];
	पूर्णांक8_t sink_hw_revision;
	पूर्णांक8_t sink_fw_revision[2];

	uपूर्णांक32_t branch_dev_id;
	पूर्णांक8_t branch_dev_name[6];
	पूर्णांक8_t branch_hw_revision;
	पूर्णांक8_t branch_fw_revision[2];

	bool allow_invalid_MSA_timing_param;
	bool panel_mode_edp;
	bool dpcd_display_control_capable;
	bool ext_receiver_cap_field_present;
	bool dynamic_backlight_capable_edp;
	जोड़ dpcd_fec_capability fec_cap;
	काष्ठा dpcd_dsc_capabilities dsc_caps;
	काष्ठा dc_lttpr_caps lttpr_caps;
	काष्ठा psr_caps psr_caps;

पूर्ण;

जोड़ dpcd_sink_ext_caps अणु
	काष्ठा अणु
		/* 0 - Sink supports backlight adjust via PWM during SDR/HDR mode
		 * 1 - Sink supports backlight adjust via AUX during SDR/HDR mode.
		 */
		uपूर्णांक8_t sdr_aux_backlight_control : 1;
		uपूर्णांक8_t hdr_aux_backlight_control : 1;
		uपूर्णांक8_t reserved_1 : 2;
		uपूर्णांक8_t oled : 1;
		uपूर्णांक8_t reserved : 3;
	पूर्ण bits;
	uपूर्णांक8_t raw;
पूर्ण;

#अगर defined(CONFIG_DRM_AMD_DC_HDCP)
जोड़ hdcp_rx_caps अणु
	काष्ठा अणु
		uपूर्णांक8_t version;
		uपूर्णांक8_t reserved;
		काष्ठा अणु
			uपूर्णांक8_t repeater	: 1;
			uपूर्णांक8_t hdcp_capable	: 1;
			uपूर्णांक8_t reserved	: 6;
		पूर्ण byte0;
	पूर्ण fields;
	uपूर्णांक8_t raw[3];
पूर्ण;

जोड़ hdcp_bcaps अणु
	काष्ठा अणु
		uपूर्णांक8_t HDCP_CAPABLE:1;
		uपूर्णांक8_t REPEATER:1;
		uपूर्णांक8_t RESERVED:6;
	पूर्ण bits;
	uपूर्णांक8_t raw;
पूर्ण;

काष्ठा hdcp_caps अणु
	जोड़ hdcp_rx_caps rx_caps;
	जोड़ hdcp_bcaps bcaps;
पूर्ण;
#पूर्ण_अगर

#समावेश "dc_link.h"

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
uपूर्णांक32_t dc_get_opp_क्रम_plane(काष्ठा dc *dc, काष्ठा dc_plane_state *plane);

#पूर्ण_अगर
/*******************************************************************************
 * Sink Interfaces - A sink corresponds to a display output device
 ******************************************************************************/

काष्ठा dc_container_id अणु
	// 128bit GUID in binary क्रमm
	अचिन्हित अक्षर  guid[16];
	// 8 byte port ID -> ELD.PortID
	अचिन्हित पूर्णांक   portId[2];
	// 128bit GUID in binary क्रमmufacturer name -> ELD.ManufacturerName
	अचिन्हित लघु manufacturerName;
	// 2 byte product code -> ELD.ProductCode
	अचिन्हित लघु productCode;
पूर्ण;


काष्ठा dc_sink_dsc_caps अणु
	// 'true' if these are virtual DPCD's DSC caps (immediately upstream of sink in MST topology),
	// 'false' if they are sink's DSC caps
	bool is_भव_dpcd_dsc;
	काष्ठा dsc_dec_dpcd_caps dsc_dec_caps;
पूर्ण;

काष्ठा dc_sink_fec_caps अणु
	bool is_rx_fec_supported;
	bool is_topology_fec_supported;
पूर्ण;

/*
 * The sink काष्ठाure contains EDID and other display device properties
 */
काष्ठा dc_sink अणु
	क्रमागत संकेत_type sink_संकेत;
	काष्ठा dc_edid dc_edid; /* raw edid */
	काष्ठा dc_edid_caps edid_caps; /* parse display caps */
	काष्ठा dc_container_id *dc_container_id;
	uपूर्णांक32_t करोngle_max_pix_clk;
	व्योम *priv;
	काष्ठा stereo_3d_features features_3d[TIMING_3D_FORMAT_MAX];
	bool converter_disable_audio;

	काष्ठा dc_sink_dsc_caps dsc_caps;
	काष्ठा dc_sink_fec_caps fec_caps;

	bool is_vsc_sdp_colorimetry_supported;

	/* निजी to DC core */
	काष्ठा dc_link *link;
	काष्ठा dc_context *ctx;

	uपूर्णांक32_t sink_id;

	/* निजी to dc_sink.c */
	// refcount must be the last member in dc_sink, since we want the
	// sink काष्ठाure to be logically cloneable up to (but not including)
	// refcount
	काष्ठा kref refcount;
पूर्ण;

व्योम dc_sink_retain(काष्ठा dc_sink *sink);
व्योम dc_sink_release(काष्ठा dc_sink *sink);

काष्ठा dc_sink_init_data अणु
	क्रमागत संकेत_type sink_संकेत;
	काष्ठा dc_link *link;
	uपूर्णांक32_t करोngle_max_pix_clk;
	bool converter_disable_audio;
पूर्ण;

काष्ठा dc_sink *dc_sink_create(स्थिर काष्ठा dc_sink_init_data *init_params);

/* Newer पूर्णांकerfaces  */
काष्ठा dc_cursor अणु
	काष्ठा dc_plane_address address;
	काष्ठा dc_cursor_attributes attributes;
पूर्ण;


/*******************************************************************************
 * Interrupt पूर्णांकerfaces
 ******************************************************************************/
क्रमागत dc_irq_source dc_पूर्णांकerrupt_to_irq_source(
		काष्ठा dc *dc,
		uपूर्णांक32_t src_id,
		uपूर्णांक32_t ext_id);
bool dc_पूर्णांकerrupt_set(काष्ठा dc *dc, क्रमागत dc_irq_source src, bool enable);
व्योम dc_पूर्णांकerrupt_ack(काष्ठा dc *dc, क्रमागत dc_irq_source src);
क्रमागत dc_irq_source dc_get_hpd_irq_source_at_index(
		काष्ठा dc *dc, uपूर्णांक32_t link_index);

/*******************************************************************************
 * Power Interfaces
 ******************************************************************************/

व्योम dc_set_घातer_state(
		काष्ठा dc *dc,
		क्रमागत dc_acpi_cm_घातer_state घातer_state);
व्योम dc_resume(काष्ठा dc *dc);

व्योम dc_घातer_करोwn_on_boot(काष्ठा dc *dc);

#अगर defined(CONFIG_DRM_AMD_DC_HDCP)
/*
 * HDCP Interfaces
 */
क्रमागत hdcp_message_status dc_process_hdcp_msg(
		क्रमागत संकेत_type संकेत,
		काष्ठा dc_link *link,
		काष्ठा hdcp_protection_message *message_info);
#पूर्ण_अगर
bool dc_is_dmcu_initialized(काष्ठा dc *dc);

क्रमागत dc_status dc_set_घड़ी(काष्ठा dc *dc, क्रमागत dc_घड़ी_प्रकारype घड़ी_प्रकारype, uपूर्णांक32_t clk_khz, uपूर्णांक32_t stepping);
व्योम dc_get_घड़ी(काष्ठा dc *dc, क्रमागत dc_घड़ी_प्रकारype घड़ी_प्रकारype, काष्ठा dc_घड़ी_config *घड़ी_cfg);
#अगर defined(CONFIG_DRM_AMD_DC_DCN)

bool dc_is_plane_eligible_क्रम_idle_optimizations(काष्ठा dc *dc, काष्ठा dc_plane_state *plane,
				काष्ठा dc_cursor_attributes *cursor_attr);

व्योम dc_allow_idle_optimizations(काष्ठा dc *dc, bool allow);

/*
 * blank all streams, and set min and max memory घड़ी to
 * lowest and highest DPM level, respectively
 */
व्योम dc_unlock_memory_घड़ी_frequency(काष्ठा dc *dc);

/*
 * set min memory घड़ी to the min required क्रम current mode,
 * max to maxDPM, and unblank streams
 */
व्योम dc_lock_memory_घड़ी_frequency(काष्ठा dc *dc);

/* cleanup on driver unload */
व्योम dc_hardware_release(काष्ठा dc *dc);

#पूर्ण_अगर

bool dc_set_psr_allow_active(काष्ठा dc *dc, bool enable);

bool dc_enable_dmub_notअगरications(काष्ठा dc *dc);

bool dc_process_dmub_aux_transfer_async(काष्ठा dc *dc,
				uपूर्णांक32_t link_index,
				काष्ठा aux_payload *payload);

/*******************************************************************************
 * DSC Interfaces
 ******************************************************************************/
#समावेश "dc_dsc.h"

/*******************************************************************************
 * Disable acc mode Interfaces
 ******************************************************************************/
व्योम dc_disable_accelerated_mode(काष्ठा dc *dc);

#पूर्ण_अगर /* DC_INTERFACE_H_ */
