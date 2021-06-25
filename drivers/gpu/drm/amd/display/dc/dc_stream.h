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

#अगर_अघोषित DC_STREAM_H_
#घोषणा DC_STREAM_H_

#समावेश "dc_types.h"
#समावेश "grph_object_defs.h"

/*******************************************************************************
 * Stream Interfaces
 ******************************************************************************/
काष्ठा timing_sync_info अणु
	पूर्णांक group_id;
	पूर्णांक group_size;
	bool master;
पूर्ण;

काष्ठा dc_stream_status अणु
	पूर्णांक primary_otg_inst;
	पूर्णांक stream_enc_inst;
	पूर्णांक plane_count;
	पूर्णांक audio_inst;
	काष्ठा timing_sync_info timing_sync_info;
	काष्ठा dc_plane_state *plane_states[MAX_SURFACE_NUM];
	bool is_abm_supported;
पूर्ण;

// TODO: References to this needs to be हटाओd..
काष्ठा मुक्तsync_context अणु
	bool dummy;
पूर्ण;

क्रमागत hubp_dmdata_mode अणु
	DMDATA_SW_MODE,
	DMDATA_HW_MODE
पूर्ण;

काष्ठा dc_dmdata_attributes अणु
	/* Specअगरies whether dynamic meta data will be updated by software
	 * or has to be fetched by hardware (DMA mode)
	 */
	क्रमागत hubp_dmdata_mode dmdata_mode;
	/* Specअगरies अगर current dynamic meta data is to be used only क्रम the current frame */
	bool dmdata_repeat;
	/* Specअगरies the size of Dynamic Metadata surface in byte.  Size of 0 means no Dynamic metadata is fetched */
	uपूर्णांक32_t dmdata_size;
	/* Specअगरies अगर a new dynamic meta data should be fetched क्रम an upcoming frame */
	bool dmdata_updated;
	/* If hardware mode is used, the base address where DMDATA surface is located */
	PHYSICAL_ADDRESS_LOC address;
	/* Specअगरies whether QOS level will be provided by TTU or it will come from DMDATA_QOS_LEVEL */
	bool dmdata_qos_mode;
	/* If qos_mode = 1, this is the QOS value to be used: */
	uपूर्णांक32_t dmdata_qos_level;
	/* Specअगरies the value in unit of REFCLK cycles to be added to the
	 * current समय to produce the Amortized deadline क्रम Dynamic Metadata chunk request
	 */
	uपूर्णांक32_t dmdata_dl_delta;
	/* An unbounded array of uपूर्णांक32s, represents software dmdata to be loaded */
	uपूर्णांक32_t *dmdata_sw_data;
पूर्ण;

काष्ठा dc_ग_लिखोback_info अणु
	bool wb_enabled;
	पूर्णांक dwb_pipe_inst;
	काष्ठा dc_dwb_params dwb_params;
	काष्ठा mcअगर_buf_params mcअगर_buf_params;
	काष्ठा mcअगर_warmup_params mcअगर_warmup_params;
	/* the plane that is the input to TOP_MUX क्रम MPCC that is the DWB source */
	काष्ठा dc_plane_state *ग_लिखोback_source_plane;
	/* source MPCC instance.  क्रम use by पूर्णांकernally by dc */
	पूर्णांक mpcc_inst;
पूर्ण;

काष्ठा dc_ग_लिखोback_update अणु
	अचिन्हित पूर्णांक num_wb_info;
	काष्ठा dc_ग_लिखोback_info ग_लिखोback_info[MAX_DWB_PIPES];
पूर्ण;

क्रमागत vertical_पूर्णांकerrupt_ref_poपूर्णांक अणु
	START_V_UPDATE = 0,
	START_V_SYNC,
	INVALID_POINT

	//For now, only v_update पूर्णांकerrupt is used.
	//START_V_BLANK,
	//START_V_ACTIVE
पूर्ण;

काष्ठा periodic_पूर्णांकerrupt_config अणु
	क्रमागत vertical_पूर्णांकerrupt_ref_poपूर्णांक ref_poपूर्णांक;
	पूर्णांक lines_offset;
पूर्ण;

जोड़ stream_update_flags अणु
	काष्ठा अणु
		uपूर्णांक32_t scaling:1;
		uपूर्णांक32_t out_tf:1;
		uपूर्णांक32_t out_csc:1;
		uपूर्णांक32_t abm_level:1;
		uपूर्णांक32_t dpms_off:1;
		uपूर्णांक32_t gamut_remap:1;
		uपूर्णांक32_t wb_update:1;
		uपूर्णांक32_t dsc_changed : 1;
	पूर्ण bits;

	uपूर्णांक32_t raw;
पूर्ण;

काष्ठा test_pattern अणु
	क्रमागत dp_test_pattern type;
	क्रमागत dp_test_pattern_color_space color_space;
	काष्ठा link_training_settings स्थिर *p_link_settings;
	अचिन्हित अक्षर स्थिर *p_custom_pattern;
	अचिन्हित पूर्णांक cust_pattern_size;
पूर्ण;

काष्ठा dc_stream_state अणु
	// sink is deprecated, new code should not reference
	// this poपूर्णांकer
	काष्ठा dc_sink *sink;

	काष्ठा dc_link *link;
	/* For dynamic link encoder assignment, update the link encoder asचिन्हित to
	 * a stream via the अस्थिर dc_state rather than the अटल dc_link.
	 */
	काष्ठा link_encoder *link_enc;
	काष्ठा dc_panel_patch sink_patches;
	जोड़ display_content_support content_support;
	काष्ठा dc_crtc_timing timing;
	काष्ठा dc_crtc_timing_adjust adjust;
	काष्ठा dc_info_packet vrr_infopacket;
	काष्ठा dc_info_packet vsc_infopacket;
	काष्ठा dc_info_packet vsp_infopacket;

	काष्ठा rect src; /* composition area */
	काष्ठा rect dst; /* stream addressable area */

	// TODO: References to this needs to be हटाओd..
	काष्ठा मुक्तsync_context मुक्तsync_ctx;

	काष्ठा audio_info audio_info;

	काष्ठा dc_info_packet hdr_अटल_metadata;
	PHYSICAL_ADDRESS_LOC dmdata_address;
	bool   use_dynamic_meta;

	काष्ठा dc_transfer_func *out_transfer_func;
	काष्ठा colorspace_transक्रमm gamut_remap_matrix;
	काष्ठा dc_csc_transक्रमm csc_color_matrix;

	क्रमागत dc_color_space output_color_space;
	क्रमागत dc_dither_option dither_option;

	क्रमागत view_3d_क्रमmat view_क्रमmat;

	bool use_vsc_sdp_क्रम_colorimetry;
	bool ignore_msa_timing_param;
	bool converter_disable_audio;
	uपूर्णांक8_t qs_bit;
	uपूर्णांक8_t qy_bit;

	/* TODO: custom INFO packets */
	/* TODO: ABM info (DMCU) */
	/* TODO: CEA VIC */

	/* DMCU info */
	अचिन्हित पूर्णांक abm_level;

	काष्ठा periodic_पूर्णांकerrupt_config periodic_पूर्णांकerrupt0;
	काष्ठा periodic_पूर्णांकerrupt_config periodic_पूर्णांकerrupt1;

	/* from core_stream काष्ठा */
	काष्ठा dc_context *ctx;

	/* used by DCP and FMT */
	काष्ठा bit_depth_reduction_params bit_depth_params;
	काष्ठा clamping_and_pixel_encoding_params clamping;

	पूर्णांक phy_pix_clk;
	क्रमागत संकेत_type संकेत;
	bool dpms_off;

	व्योम *dm_stream_context;

	काष्ठा dc_cursor_attributes cursor_attributes;
	काष्ठा dc_cursor_position cursor_position;
	uपूर्णांक32_t sdr_white_level; // क्रम boosting (SDR) cursor in HDR mode

	/* from stream काष्ठा */
	काष्ठा kref refcount;

	काष्ठा crtc_trigger_info triggered_crtc_reset;

	/* ग_लिखोback */
	अचिन्हित पूर्णांक num_wb_info;
	काष्ठा dc_ग_लिखोback_info ग_लिखोback_info[MAX_DWB_PIPES];
	स्थिर काष्ठा dc_transfer_func *func_shaper;
	स्थिर काष्ठा dc_3dlut *lut3d_func;
	/* Computed state bits */
	bool mode_changed : 1;

	/* Output from DC when stream state is committed or altered
	 * DC may only access these values during:
	 * dc_commit_state, dc_commit_state_no_check, dc_commit_streams
	 * values may not change outside of those calls
	 */
	काष्ठा अणु
		// For पूर्णांकerrupt management, some hardware instance
		// offsets need to be exposed to DM
		uपूर्णांक8_t otg_offset;
	पूर्ण out;

	bool apply_edp_fast_boot_optimization;
	bool apply_seamless_boot_optimization;

	uपूर्णांक32_t stream_id;

	काष्ठा test_pattern test_pattern;
	जोड़ stream_update_flags update_flags;

	bool has_non_synchronizable_pclk;
	bool vblank_synchronized;
पूर्ण;

#घोषणा ABM_LEVEL_IMMEDIATE_DISABLE 255

काष्ठा dc_stream_update अणु
	काष्ठा dc_stream_state *stream;

	काष्ठा rect src;
	काष्ठा rect dst;
	काष्ठा dc_transfer_func *out_transfer_func;
	काष्ठा dc_info_packet *hdr_अटल_metadata;
	अचिन्हित पूर्णांक *abm_level;

	काष्ठा periodic_पूर्णांकerrupt_config *periodic_पूर्णांकerrupt0;
	काष्ठा periodic_पूर्णांकerrupt_config *periodic_पूर्णांकerrupt1;

	काष्ठा dc_info_packet *vrr_infopacket;
	काष्ठा dc_info_packet *vsc_infopacket;
	काष्ठा dc_info_packet *vsp_infopacket;

	bool *dpms_off;
	bool पूर्णांकeger_scaling_update;

	काष्ठा colorspace_transक्रमm *gamut_remap;
	क्रमागत dc_color_space *output_color_space;
	क्रमागत dc_dither_option *dither_option;

	काष्ठा dc_csc_transक्रमm *output_csc_transक्रमm;

	काष्ठा dc_ग_लिखोback_update *wb_update;
	काष्ठा dc_dsc_config *dsc_config;
	काष्ठा dc_transfer_func *func_shaper;
	काष्ठा dc_3dlut *lut3d_func;

	काष्ठा test_pattern *pending_test_pattern;
पूर्ण;

bool dc_is_stream_unchanged(
	काष्ठा dc_stream_state *old_stream, काष्ठा dc_stream_state *stream);
bool dc_is_stream_scaling_unchanged(
	काष्ठा dc_stream_state *old_stream, काष्ठा dc_stream_state *stream);

/*
 * Set up surface attributes and associate to a stream
 * The surfaces parameter is an असलolute set of all surface active क्रम the stream.
 * If no surfaces are provided, the stream will be blanked; no memory पढ़ो.
 * Any flip related attribute changes must be करोne through this पूर्णांकerface.
 *
 * After this call:
 *   Surfaces attributes are programmed and configured to be composed पूर्णांकo stream.
 *   This करोes not trigger a flip.  No surface address is programmed.
 */

व्योम dc_commit_updates_क्रम_stream(काष्ठा dc *dc,
		काष्ठा dc_surface_update *srf_updates,
		पूर्णांक surface_count,
		काष्ठा dc_stream_state *stream,
		काष्ठा dc_stream_update *stream_update,
		काष्ठा dc_state *state);
/*
 * Log the current stream state.
 */
व्योम dc_stream_log(स्थिर काष्ठा dc *dc, स्थिर काष्ठा dc_stream_state *stream);

uपूर्णांक8_t dc_get_current_stream_count(काष्ठा dc *dc);
काष्ठा dc_stream_state *dc_get_stream_at_index(काष्ठा dc *dc, uपूर्णांक8_t i);
काष्ठा dc_stream_state *dc_stream_find_from_link(स्थिर काष्ठा dc_link *link);

/*
 * Return the current frame counter.
 */
uपूर्णांक32_t dc_stream_get_vblank_counter(स्थिर काष्ठा dc_stream_state *stream);

/*
 * Send dp sdp message.
 */
bool dc_stream_send_dp_sdp(स्थिर काष्ठा dc_stream_state *stream,
		स्थिर uपूर्णांक8_t *custom_sdp_message,
		अचिन्हित पूर्णांक sdp_message_size);

/* TODO: Return parsed values rather than direct रेजिस्टर पढ़ो
 * This has a dependency on the caller (amdgpu_display_get_crtc_scanoutpos)
 * being refactored properly to be dce-specअगरic
 */
bool dc_stream_get_scanoutpos(स्थिर काष्ठा dc_stream_state *stream,
				  uपूर्णांक32_t *v_blank_start,
				  uपूर्णांक32_t *v_blank_end,
				  uपूर्णांक32_t *h_position,
				  uपूर्णांक32_t *v_position);

क्रमागत dc_status dc_add_stream_to_ctx(
			काष्ठा dc *dc,
		काष्ठा dc_state *new_ctx,
		काष्ठा dc_stream_state *stream);

क्रमागत dc_status dc_हटाओ_stream_from_ctx(
		काष्ठा dc *dc,
			काष्ठा dc_state *new_ctx,
			काष्ठा dc_stream_state *stream);


bool dc_add_plane_to_context(
		स्थिर काष्ठा dc *dc,
		काष्ठा dc_stream_state *stream,
		काष्ठा dc_plane_state *plane_state,
		काष्ठा dc_state *context);

bool dc_हटाओ_plane_from_context(
		स्थिर काष्ठा dc *dc,
		काष्ठा dc_stream_state *stream,
		काष्ठा dc_plane_state *plane_state,
		काष्ठा dc_state *context);

bool dc_rem_all_planes_क्रम_stream(
		स्थिर काष्ठा dc *dc,
		काष्ठा dc_stream_state *stream,
		काष्ठा dc_state *context);

bool dc_add_all_planes_क्रम_stream(
		स्थिर काष्ठा dc *dc,
		काष्ठा dc_stream_state *stream,
		काष्ठा dc_plane_state * स्थिर *plane_states,
		पूर्णांक plane_count,
		काष्ठा dc_state *context);

bool dc_stream_add_ग_लिखोback(काष्ठा dc *dc,
		काष्ठा dc_stream_state *stream,
		काष्ठा dc_ग_लिखोback_info *wb_info);

bool dc_stream_हटाओ_ग_लिखोback(काष्ठा dc *dc,
		काष्ठा dc_stream_state *stream,
		uपूर्णांक32_t dwb_pipe_inst);

क्रमागत dc_status dc_stream_add_dsc_to_resource(काष्ठा dc *dc,
		काष्ठा dc_state *state,
		काष्ठा dc_stream_state *stream);

bool dc_stream_warmup_ग_लिखोback(काष्ठा dc *dc,
		पूर्णांक num_dwb,
		काष्ठा dc_ग_लिखोback_info *wb_info);

bool dc_stream_dmdata_status_करोne(काष्ठा dc *dc, काष्ठा dc_stream_state *stream);

bool dc_stream_set_dynamic_metadata(काष्ठा dc *dc,
		काष्ठा dc_stream_state *stream,
		काष्ठा dc_dmdata_attributes *dmdata_attr);

क्रमागत dc_status dc_validate_stream(काष्ठा dc *dc, काष्ठा dc_stream_state *stream);

/*
 * Set up streams and links associated to drive sinks
 * The streams parameter is an असलolute set of all active streams.
 *
 * After this call:
 *   Phy, Encoder, Timing Generator are programmed and enabled.
 *   New streams are enabled with blank stream; no memory पढ़ो.
 */
/*
 * Enable stereo when commit_streams is not required,
 * क्रम example, frame alternate.
 */
व्योम dc_enable_stereo(
	काष्ठा dc *dc,
	काष्ठा dc_state *context,
	काष्ठा dc_stream_state *streams[],
	uपूर्णांक8_t stream_count);

/* Triggers multi-stream synchronization. */
व्योम dc_trigger_sync(काष्ठा dc *dc, काष्ठा dc_state *context);

क्रमागत surface_update_type dc_check_update_surfaces_क्रम_stream(
		काष्ठा dc *dc,
		काष्ठा dc_surface_update *updates,
		पूर्णांक surface_count,
		काष्ठा dc_stream_update *stream_update,
		स्थिर काष्ठा dc_stream_status *stream_status);

/**
 * Create a new शेष stream क्रम the requested sink
 */
काष्ठा dc_stream_state *dc_create_stream_क्रम_sink(काष्ठा dc_sink *dc_sink);

काष्ठा dc_stream_state *dc_copy_stream(स्थिर काष्ठा dc_stream_state *stream);

व्योम update_stream_संकेत(काष्ठा dc_stream_state *stream, काष्ठा dc_sink *sink);

व्योम dc_stream_retain(काष्ठा dc_stream_state *dc_stream);
व्योम dc_stream_release(काष्ठा dc_stream_state *dc_stream);

काष्ठा dc_stream_status *dc_stream_get_status_from_state(
	काष्ठा dc_state *state,
	काष्ठा dc_stream_state *stream);
काष्ठा dc_stream_status *dc_stream_get_status(
	काष्ठा dc_stream_state *dc_stream);

#अगर_अघोषित TRIM_FSFT
bool dc_optimize_timing_क्रम_fsft(
	काष्ठा dc_stream_state *pStream,
	अचिन्हित पूर्णांक max_input_rate_in_khz);
#पूर्ण_अगर

/*******************************************************************************
 * Cursor पूर्णांकerfaces - To manages the cursor within a stream
 ******************************************************************************/
/* TODO: Deprecated once we चयन to dc_set_cursor_position */
bool dc_stream_set_cursor_attributes(
	काष्ठा dc_stream_state *stream,
	स्थिर काष्ठा dc_cursor_attributes *attributes);

bool dc_stream_set_cursor_position(
	काष्ठा dc_stream_state *stream,
	स्थिर काष्ठा dc_cursor_position *position);


bool dc_stream_adjust_vmin_vmax(काष्ठा dc *dc,
				काष्ठा dc_stream_state *stream,
				काष्ठा dc_crtc_timing_adjust *adjust);

bool dc_stream_get_crtc_position(काष्ठा dc *dc,
				 काष्ठा dc_stream_state **stream,
				 पूर्णांक num_streams,
				 अचिन्हित पूर्णांक *v_pos,
				 अचिन्हित पूर्णांक *nom_v_pos);

#अगर defined(CONFIG_DRM_AMD_SECURE_DISPLAY)
bool dc_stream_क्रमward_dmcu_crc_winकरोw(काष्ठा dc *dc, काष्ठा dc_stream_state *stream,
			     काष्ठा crc_params *crc_winकरोw);
bool dc_stream_stop_dmcu_crc_win_update(काष्ठा dc *dc,
				 काष्ठा dc_stream_state *stream);
#पूर्ण_अगर

bool dc_stream_configure_crc(काष्ठा dc *dc,
			     काष्ठा dc_stream_state *stream,
			     काष्ठा crc_params *crc_winकरोw,
			     bool enable,
			     bool continuous);

bool dc_stream_get_crc(काष्ठा dc *dc,
		       काष्ठा dc_stream_state *stream,
		       uपूर्णांक32_t *r_cr,
		       uपूर्णांक32_t *g_y,
		       uपूर्णांक32_t *b_cb);

व्योम dc_stream_set_अटल_screen_params(काष्ठा dc *dc,
					काष्ठा dc_stream_state **stream,
					पूर्णांक num_streams,
					स्थिर काष्ठा dc_अटल_screen_params *params);

व्योम dc_stream_set_dyn_expansion(काष्ठा dc *dc, काष्ठा dc_stream_state *stream,
		क्रमागत dc_dynamic_expansion option);

व्योम dc_stream_set_dither_option(काष्ठा dc_stream_state *stream,
				 क्रमागत dc_dither_option option);

bool dc_stream_set_gamut_remap(काष्ठा dc *dc,
			       स्थिर काष्ठा dc_stream_state *stream);

bool dc_stream_program_csc_matrix(काष्ठा dc *dc,
				  काष्ठा dc_stream_state *stream);

bool dc_stream_get_crtc_position(काष्ठा dc *dc,
				 काष्ठा dc_stream_state **stream,
				 पूर्णांक num_streams,
				 अचिन्हित पूर्णांक *v_pos,
				 अचिन्हित पूर्णांक *nom_v_pos);

#पूर्ण_अगर /* DC_STREAM_H_ */
