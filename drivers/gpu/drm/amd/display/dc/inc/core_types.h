<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
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

#अगर_अघोषित _CORE_TYPES_H_
#घोषणा _CORE_TYPES_H_

#समावेश "dc.h"
#समावेश "dce_calcs.h"
#समावेश "dcn_calcs.h"
#समावेश "ddc_service_types.h"
#समावेश "dc_bios_types.h"
#समावेश "mem_input.h"
#समावेश "hubp.h"
#अगर defined(CONFIG_DRM_AMD_DC_DCN)
#समावेश "mpc.h"
#पूर्ण_अगर
#समावेश "dwb.h"
#समावेश "mcif_wb.h"
#समावेश "panel_cntl.h"

#घोषणा MAX_CLOCK_SOURCES 7

व्योम enable_surface_flip_reporting(काष्ठा dc_plane_state *plane_state,
		uपूर्णांक32_t controller_id);

#समावेश "grph_object_id.h"
#समावेश "link_encoder.h"
#समावेश "stream_encoder.h"
#समावेश "clock_source.h"
#समावेश "audio.h"
#समावेश "dm_pp_smu.h"
#अगर_घोषित CONFIG_DRM_AMD_DC_HDCP
#समावेश "dm_cp_psp.h"
#पूर्ण_अगर

/************ link *****************/
काष्ठा link_init_data अणु
	स्थिर काष्ठा dc *dc;
	काष्ठा dc_context *ctx; /* TODO: हटाओ 'dal' when DC is complete. */
	uपूर्णांक32_t connector_index; /* this will be mapped to the HPD pins */
	uपूर्णांक32_t link_index; /* this is mapped to DAL display_index
				TODO: हटाओ it when DC is complete. */
पूर्ण;

काष्ठा dc_link *link_create(स्थिर काष्ठा link_init_data *init_params);
व्योम link_destroy(काष्ठा dc_link **link);

क्रमागत dc_status dc_link_validate_mode_timing(
		स्थिर काष्ठा dc_stream_state *stream,
		काष्ठा dc_link *link,
		स्थिर काष्ठा dc_crtc_timing *timing);

व्योम core_link_resume(काष्ठा dc_link *link);

व्योम core_link_enable_stream(
		काष्ठा dc_state *state,
		काष्ठा pipe_ctx *pipe_ctx);

व्योम core_link_disable_stream(काष्ठा pipe_ctx *pipe_ctx);

व्योम core_link_set_avmute(काष्ठा pipe_ctx *pipe_ctx, bool enable);
/********** DAL Core*********************/
#समावेश "transform.h"
#समावेश "dpp.h"

काष्ठा resource_pool;
काष्ठा dc_state;
काष्ठा resource_context;
काष्ठा clk_bw_params;

काष्ठा resource_funcs अणु
	व्योम (*destroy)(काष्ठा resource_pool **pool);
	व्योम (*link_init)(काष्ठा dc_link *link);
	काष्ठा panel_cntl*(*panel_cntl_create)(
		स्थिर काष्ठा panel_cntl_init_data *panel_cntl_init_data);
	काष्ठा link_encoder *(*link_enc_create)(
			स्थिर काष्ठा encoder_init_data *init);
	/* Create a minimal link encoder object with no dc_link object
	 * associated with it. */
	काष्ठा link_encoder *(*link_enc_create_minimal)(काष्ठा dc_context *ctx, क्रमागत engine_id eng_id);

	bool (*validate_bandwidth)(
					काष्ठा dc *dc,
					काष्ठा dc_state *context,
					bool fast_validate);
	व्योम (*calculate_wm_and_dlg)(
				काष्ठा dc *dc, काष्ठा dc_state *context,
				display_e2e_pipe_params_st *pipes,
				पूर्णांक pipe_cnt,
				पूर्णांक vlevel);
	व्योम (*update_soc_क्रम_wm_a)(
				काष्ठा dc *dc, काष्ठा dc_state *context);
	पूर्णांक (*populate_dml_pipes)(
		काष्ठा dc *dc,
		काष्ठा dc_state *context,
		display_e2e_pipe_params_st *pipes,
		bool fast_validate);

	/*
	 * Algorithm क्रम assigning available link encoders to links.
	 *
	 * Update link_enc_assignments table and link_enc_avail list accordingly in
	 * काष्ठा resource_context.
	 */
	व्योम (*link_encs_assign)(
			काष्ठा dc *dc,
			काष्ठा dc_state *state,
			काष्ठा dc_stream_state *streams[],
			uपूर्णांक8_t stream_count);
	/*
	 * Unassign a link encoder from a stream.
	 *
	 * Update link_enc_assignments table and link_enc_avail list accordingly in
	 * काष्ठा resource_context.
	 */
	व्योम (*link_enc_unassign)(
			काष्ठा dc_state *state,
			काष्ठा dc_stream_state *stream);

	क्रमागत dc_status (*validate_global)(
		काष्ठा dc *dc,
		काष्ठा dc_state *context);

	काष्ठा pipe_ctx *(*acquire_idle_pipe_क्रम_layer)(
			काष्ठा dc_state *context,
			स्थिर काष्ठा resource_pool *pool,
			काष्ठा dc_stream_state *stream);

	क्रमागत dc_status (*validate_plane)(स्थिर काष्ठा dc_plane_state *plane_state, काष्ठा dc_caps *caps);

	क्रमागत dc_status (*add_stream_to_ctx)(
			काष्ठा dc *dc,
			काष्ठा dc_state *new_ctx,
			काष्ठा dc_stream_state *dc_stream);

	क्रमागत dc_status (*हटाओ_stream_from_ctx)(
				काष्ठा dc *dc,
				काष्ठा dc_state *new_ctx,
				काष्ठा dc_stream_state *stream);
	क्रमागत dc_status (*patch_unknown_plane_state)(
			काष्ठा dc_plane_state *plane_state);

	काष्ठा stream_encoder *(*find_first_मुक्त_match_stream_enc_क्रम_link)(
			काष्ठा resource_context *res_ctx,
			स्थिर काष्ठा resource_pool *pool,
			काष्ठा dc_stream_state *stream);
	व्योम (*populate_dml_ग_लिखोback_from_context)(
			काष्ठा dc *dc,
			काष्ठा resource_context *res_ctx,
			display_e2e_pipe_params_st *pipes);

	व्योम (*set_mcअगर_arb_params)(
			काष्ठा dc *dc,
			काष्ठा dc_state *context,
			display_e2e_pipe_params_st *pipes,
			पूर्णांक pipe_cnt);
	व्योम (*update_bw_bounding_box)(
			काष्ठा dc *dc,
			काष्ठा clk_bw_params *bw_params);
#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	bool (*acquire_post_bldn_3dlut)(
			काष्ठा resource_context *res_ctx,
			स्थिर काष्ठा resource_pool *pool,
			पूर्णांक mpcc_id,
			काष्ठा dc_3dlut **lut,
			काष्ठा dc_transfer_func **shaper);

	bool (*release_post_bldn_3dlut)(
			काष्ठा resource_context *res_ctx,
			स्थिर काष्ठा resource_pool *pool,
			काष्ठा dc_3dlut **lut,
			काष्ठा dc_transfer_func **shaper);
#पूर्ण_अगर
	क्रमागत dc_status (*add_dsc_to_stream_resource)(
			काष्ठा dc *dc, काष्ठा dc_state *state,
			काष्ठा dc_stream_state *stream);
पूर्ण;

काष्ठा audio_supportअणु
	bool dp_audio;
	bool hdmi_audio_on_करोngle;
	bool hdmi_audio_native;
पूर्ण;

#घोषणा NO_UNDERLAY_PIPE -1

काष्ठा resource_pool अणु
	काष्ठा mem_input *mis[MAX_PIPES];
	काष्ठा hubp *hubps[MAX_PIPES];
	काष्ठा input_pixel_processor *ipps[MAX_PIPES];
	काष्ठा transक्रमm *transक्रमms[MAX_PIPES];
	काष्ठा dpp *dpps[MAX_PIPES];
	काष्ठा output_pixel_processor *opps[MAX_PIPES];
	काष्ठा timing_generator *timing_generators[MAX_PIPES];
	काष्ठा stream_encoder *stream_enc[MAX_PIPES * 2];
	काष्ठा hubbub *hubbub;
	काष्ठा mpc *mpc;
	काष्ठा pp_smu_funcs *pp_smu;
	काष्ठा dce_aux *engines[MAX_PIPES];
	काष्ठा dce_i2c_hw *hw_i2cs[MAX_PIPES];
	काष्ठा dce_i2c_sw *sw_i2cs[MAX_PIPES];
	bool i2c_hw_buffer_in_use;

	काष्ठा dwbc *dwbc[MAX_DWB_PIPES];
	काष्ठा mcअगर_wb *mcअगर_wb[MAX_DWB_PIPES];
	काष्ठा अणु
		अचिन्हित पूर्णांक gsl_0:1;
		अचिन्हित पूर्णांक gsl_1:1;
		अचिन्हित पूर्णांक gsl_2:1;
	पूर्ण gsl_groups;

	काष्ठा display_stream_compressor *dscs[MAX_PIPES];

	अचिन्हित पूर्णांक pipe_count;
	अचिन्हित पूर्णांक underlay_pipe_index;
	अचिन्हित पूर्णांक stream_enc_count;

	/* An array क्रम accessing the link encoder objects that have been created.
	 * Index in array corresponds to engine ID - viz. 0: ENGINE_ID_DIGA
	 */
	काष्ठा link_encoder *link_encoders[MAX_DIG_LINK_ENCODERS];
	/* Number of DIG link encoder objects created - i.e. number of valid
	 * entries in link_encoders array.
	 */
	अचिन्हित पूर्णांक dig_link_enc_count;

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	काष्ठा dc_3dlut *mpc_lut[MAX_PIPES];
	काष्ठा dc_transfer_func *mpc_shaper[MAX_PIPES];
#पूर्ण_अगर
	काष्ठा अणु
		अचिन्हित पूर्णांक xtalin_घड़ी_inKhz;
		अचिन्हित पूर्णांक dccg_ref_घड़ी_inKhz;
		अचिन्हित पूर्णांक dchub_ref_घड़ी_inKhz;
	पूर्ण ref_घड़ीs;
	अचिन्हित पूर्णांक timing_generator_count;
	अचिन्हित पूर्णांक mpcc_count;

	अचिन्हित पूर्णांक ग_लिखोback_pipe_count;
	/*
	 * reserved घड़ी source क्रम DP
	 */
	काष्ठा घड़ी_source *dp_घड़ी_source;

	काष्ठा घड़ी_source *घड़ी_sources[MAX_CLOCK_SOURCES];
	अचिन्हित पूर्णांक clk_src_count;

	काष्ठा audio *audios[MAX_AUDIOS];
	अचिन्हित पूर्णांक audio_count;
	काष्ठा audio_support audio_support;

	काष्ठा dccg *dccg;
	काष्ठा irq_service *irqs;

	काष्ठा abm *abm;
	काष्ठा dmcu *dmcu;
	काष्ठा dmub_psr *psr;

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	काष्ठा abm *multiple_abms[MAX_PIPES];
#पूर्ण_अगर

	स्थिर काष्ठा resource_funcs *funcs;
	स्थिर काष्ठा resource_caps *res_cap;

	काष्ठा ddc_service *oem_device;
पूर्ण;

काष्ठा dcn_fe_bandwidth अणु
	पूर्णांक dppclk_khz;

पूर्ण;

काष्ठा stream_resource अणु
	काष्ठा output_pixel_processor *opp;
	काष्ठा display_stream_compressor *dsc;
	काष्ठा timing_generator *tg;
	काष्ठा stream_encoder *stream_enc;
	काष्ठा audio *audio;

	काष्ठा pixel_clk_params pix_clk_params;
	काष्ठा encoder_info_frame encoder_info_frame;

	काष्ठा abm *abm;
	/* There are only (num_pipes+1)/2 groups. 0 means unasचिन्हित,
	 * otherwise it's using group number 'gsl_group-1'
	 */
	uपूर्णांक8_t gsl_group;
पूर्ण;

काष्ठा plane_resource अणु
	काष्ठा scaler_data scl_data;
	काष्ठा hubp *hubp;
	काष्ठा mem_input *mi;
	काष्ठा input_pixel_processor *ipp;
	काष्ठा transक्रमm *xfm;
	काष्ठा dpp *dpp;
	uपूर्णांक8_t mpcc_inst;

	काष्ठा dcn_fe_bandwidth bw;
पूर्ण;

जोड़ pipe_update_flags अणु
	काष्ठा अणु
		uपूर्णांक32_t enable : 1;
		uपूर्णांक32_t disable : 1;
		uपूर्णांक32_t odm : 1;
		uपूर्णांक32_t global_sync : 1;
		uपूर्णांक32_t opp_changed : 1;
		uपूर्णांक32_t tg_changed : 1;
		uपूर्णांक32_t mpcc : 1;
		uपूर्णांक32_t dppclk : 1;
		uपूर्णांक32_t hubp_पूर्णांकerdependent : 1;
		uपूर्णांक32_t hubp_rq_dlg_ttu : 1;
		uपूर्णांक32_t gamut_remap : 1;
		uपूर्णांक32_t scaler : 1;
		uपूर्णांक32_t viewport : 1;
		uपूर्णांक32_t plane_changed : 1;
	पूर्ण bits;
	uपूर्णांक32_t raw;
पूर्ण;

काष्ठा pipe_ctx अणु
	काष्ठा dc_plane_state *plane_state;
	काष्ठा dc_stream_state *stream;

	काष्ठा plane_resource plane_res;
	काष्ठा stream_resource stream_res;

	काष्ठा घड़ी_source *घड़ी_source;

	काष्ठा pll_settings pll_settings;

	uपूर्णांक8_t pipe_idx;

	काष्ठा pipe_ctx *top_pipe;
	काष्ठा pipe_ctx *bottom_pipe;
	काष्ठा pipe_ctx *next_odm_pipe;
	काष्ठा pipe_ctx *prev_odm_pipe;

#अगर_घोषित CONFIG_DRM_AMD_DC_DCN
	काष्ठा _vcs_dpi_display_dlg_regs_st dlg_regs;
	काष्ठा _vcs_dpi_display_ttu_regs_st ttu_regs;
	काष्ठा _vcs_dpi_display_rq_regs_st rq_regs;
	काष्ठा _vcs_dpi_display_pipe_dest_params_st pipe_dlg_param;
#पूर्ण_अगर
	जोड़ pipe_update_flags update_flags;
	काष्ठा dwbc *dwbc;
	काष्ठा mcअगर_wb *mcअगर_wb;
	bool vtp_locked;
पूर्ण;

काष्ठा resource_context अणु
	काष्ठा pipe_ctx pipe_ctx[MAX_PIPES];
	bool is_stream_enc_acquired[MAX_PIPES * 2];
	bool is_audio_acquired[MAX_PIPES];
	uपूर्णांक8_t घड़ी_source_ref_count[MAX_CLOCK_SOURCES];
	uपूर्णांक8_t dp_घड़ी_source_ref_count;
	bool is_dsc_acquired[MAX_PIPES];
	/* A table/array of encoder-to-link assignments. One entry per stream.
	 * Indexed by stream index in dc_state.
	 */
	काष्ठा link_enc_assignment link_enc_assignments[MAX_PIPES];
	/* List of available link encoders. Uses engine ID as encoder identअगरier. */
	क्रमागत engine_id link_enc_avail[MAX_DIG_LINK_ENCODERS];
#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	bool is_mpc_3dlut_acquired[MAX_PIPES];
#पूर्ण_अगर
पूर्ण;

काष्ठा dce_bw_output अणु
	bool cpuc_state_change_enable;
	bool cpup_state_change_enable;
	bool stutter_mode_enable;
	bool nbp_state_change_enable;
	bool all_displays_in_sync;
	काष्ठा dce_watermarks urgent_wm_ns[MAX_PIPES];
	काष्ठा dce_watermarks stutter_निकास_wm_ns[MAX_PIPES];
	काष्ठा dce_watermarks stutter_entry_wm_ns[MAX_PIPES];
	काष्ठा dce_watermarks nbp_state_change_wm_ns[MAX_PIPES];
	पूर्णांक sclk_khz;
	पूर्णांक sclk_deep_sleep_khz;
	पूर्णांक yclk_khz;
	पूर्णांक dispclk_khz;
	पूर्णांक blackout_recovery_समय_us;
पूर्ण;

काष्ठा dcn_bw_ग_लिखोback अणु
	काष्ठा mcअगर_arb_params mcअगर_wb_arb[MAX_DWB_PIPES];
पूर्ण;

काष्ठा dcn_bw_output अणु
	काष्ठा dc_घड़ीs clk;
	काष्ठा dcn_watermark_set watermarks;
	काष्ठा dcn_bw_ग_लिखोback bw_ग_लिखोback;
पूर्ण;

जोड़ bw_output अणु
	काष्ठा dcn_bw_output dcn;
	काष्ठा dce_bw_output dce;
पूर्ण;

काष्ठा bw_context अणु
	जोड़ bw_output bw;
	काष्ठा display_mode_lib dml;
पूर्ण;
/**
 * काष्ठा dc_state - The full description of a state requested by a user
 *
 * @streams: Stream properties
 * @stream_status: The planes on a given stream
 * @res_ctx: Persistent state of resources
 * @bw_ctx: The output from bandwidth and watermark calculations and the DML
 * @pp_display_cfg: PowerPlay घड़ीs and settings
 * @dcn_bw_vars: non-stack memory to support bandwidth calculations
 *
 */
काष्ठा dc_state अणु
	काष्ठा dc_stream_state *streams[MAX_PIPES];
	काष्ठा dc_stream_status stream_status[MAX_PIPES];
	uपूर्णांक8_t stream_count;
	uपूर्णांक8_t stream_mask;

	काष्ठा resource_context res_ctx;

	काष्ठा bw_context bw_ctx;

	/* Note: these are big काष्ठाures, करो *not* put on stack! */
	काष्ठा dm_pp_display_configuration pp_display_cfg;
#अगर_घोषित CONFIG_DRM_AMD_DC_DCN
	काष्ठा dcn_bw_पूर्णांकernal_vars dcn_bw_vars;
#पूर्ण_अगर

	काष्ठा clk_mgr *clk_mgr;

	काष्ठा kref refcount;

	काष्ठा अणु
		अचिन्हित पूर्णांक stutter_period_us;
	पूर्ण perf_params;
पूर्ण;

#पूर्ण_अगर /* _CORE_TYPES_H_ */
