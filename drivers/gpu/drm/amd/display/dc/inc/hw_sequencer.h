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

#अगर_अघोषित __DC_HW_SEQUENCER_H__
#घोषणा __DC_HW_SEQUENCER_H__
#समावेश "dc_types.h"
#समावेश "clock_source.h"
#समावेश "inc/hw/timing_generator.h"
#समावेश "inc/hw/opp.h"
#समावेश "inc/hw/link_encoder.h"
#समावेश "core_status.h"

क्रमागत vline_select अणु
	VLINE0,
	VLINE1
पूर्ण;

काष्ठा pipe_ctx;
काष्ठा dc_state;
काष्ठा dc_stream_status;
काष्ठा dc_ग_लिखोback_info;
काष्ठा dchub_init_data;
काष्ठा dc_अटल_screen_params;
काष्ठा resource_pool;
काष्ठा dc_phy_addr_space_config;
काष्ठा dc_भव_addr_space_config;
काष्ठा dpp;
काष्ठा dce_hwseq;

काष्ठा hw_sequencer_funcs अणु
	व्योम (*hardware_release)(काष्ठा dc *dc);
	/* Embedded Display Related */
	व्योम (*edp_घातer_control)(काष्ठा dc_link *link, bool enable);
	व्योम (*edp_रुको_क्रम_hpd_पढ़ोy)(काष्ठा dc_link *link, bool घातer_up);
	व्योम (*edp_रुको_क्रम_T12)(काष्ठा dc_link *link);

	/* Pipe Programming Related */
	व्योम (*init_hw)(काष्ठा dc *dc);
	व्योम (*घातer_करोwn_on_boot)(काष्ठा dc *dc);
	व्योम (*enable_accelerated_mode)(काष्ठा dc *dc,
			काष्ठा dc_state *context);
	क्रमागत dc_status (*apply_ctx_to_hw)(काष्ठा dc *dc,
			काष्ठा dc_state *context);
	व्योम (*disable_plane)(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx);
	व्योम (*apply_ctx_क्रम_surface)(काष्ठा dc *dc,
			स्थिर काष्ठा dc_stream_state *stream,
			पूर्णांक num_planes, काष्ठा dc_state *context);
	व्योम (*program_front_end_क्रम_ctx)(काष्ठा dc *dc,
			काष्ठा dc_state *context);
	व्योम (*रुको_क्रम_pending_cleared)(काष्ठा dc *dc,
			काष्ठा dc_state *context);
	व्योम (*post_unlock_program_front_end)(काष्ठा dc *dc,
			काष्ठा dc_state *context);
	व्योम (*update_plane_addr)(स्थिर काष्ठा dc *dc,
			काष्ठा pipe_ctx *pipe_ctx);
	व्योम (*update_dchub)(काष्ठा dce_hwseq *hws,
			काष्ठा dchub_init_data *dh_data);
	व्योम (*रुको_क्रम_mpcc_disconnect)(काष्ठा dc *dc,
			काष्ठा resource_pool *res_pool,
			काष्ठा pipe_ctx *pipe_ctx);
	व्योम (*edp_backlight_control)(
			काष्ठा dc_link *link,
			bool enable);
	व्योम (*program_triplebuffer)(स्थिर काष्ठा dc *dc,
		काष्ठा pipe_ctx *pipe_ctx, bool enableTripleBuffer);
	व्योम (*update_pending_status)(काष्ठा pipe_ctx *pipe_ctx);
	व्योम (*घातer_करोwn)(काष्ठा dc *dc);

	/* Pipe Lock Related */
	व्योम (*pipe_control_lock)(काष्ठा dc *dc,
			काष्ठा pipe_ctx *pipe, bool lock);
	व्योम (*पूर्णांकerdependent_update_lock)(काष्ठा dc *dc,
			काष्ठा dc_state *context, bool lock);
	व्योम (*set_flip_control_gsl)(काष्ठा pipe_ctx *pipe_ctx,
			bool flip_immediate);
	व्योम (*cursor_lock)(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe, bool lock);

	/* Timing Related */
	व्योम (*get_position)(काष्ठा pipe_ctx **pipe_ctx, पूर्णांक num_pipes,
			काष्ठा crtc_position *position);
	पूर्णांक (*get_vupdate_offset_from_vsync)(काष्ठा pipe_ctx *pipe_ctx);
	व्योम (*calc_vupdate_position)(
			काष्ठा dc *dc,
			काष्ठा pipe_ctx *pipe_ctx,
			uपूर्णांक32_t *start_line,
			uपूर्णांक32_t *end_line);
	व्योम (*enable_per_frame_crtc_position_reset)(काष्ठा dc *dc,
			पूर्णांक group_size, काष्ठा pipe_ctx *grouped_pipes[]);
	व्योम (*enable_timing_synchronization)(काष्ठा dc *dc,
			पूर्णांक group_index, पूर्णांक group_size,
			काष्ठा pipe_ctx *grouped_pipes[]);
	व्योम (*enable_vblanks_synchronization)(काष्ठा dc *dc,
			पूर्णांक group_index, पूर्णांक group_size,
			काष्ठा pipe_ctx *grouped_pipes[]);
	व्योम (*setup_periodic_पूर्णांकerrupt)(काष्ठा dc *dc,
			काष्ठा pipe_ctx *pipe_ctx,
			क्रमागत vline_select vline);
	व्योम (*set_drr)(काष्ठा pipe_ctx **pipe_ctx, पूर्णांक num_pipes,
			काष्ठा dc_crtc_timing_adjust adjust);
	व्योम (*set_अटल_screen_control)(काष्ठा pipe_ctx **pipe_ctx,
			पूर्णांक num_pipes,
			स्थिर काष्ठा dc_अटल_screen_params *events);
#अगर_अघोषित TRIM_FSFT
	bool (*optimize_timing_क्रम_fsft)(काष्ठा dc *dc,
			काष्ठा dc_crtc_timing *timing,
			अचिन्हित पूर्णांक max_input_rate_in_khz);
#पूर्ण_अगर

	/* Stream Related */
	व्योम (*enable_stream)(काष्ठा pipe_ctx *pipe_ctx);
	व्योम (*disable_stream)(काष्ठा pipe_ctx *pipe_ctx);
	व्योम (*blank_stream)(काष्ठा pipe_ctx *pipe_ctx);
	व्योम (*unblank_stream)(काष्ठा pipe_ctx *pipe_ctx,
			काष्ठा dc_link_settings *link_settings);

	/* Bandwidth Related */
	व्योम (*prepare_bandwidth)(काष्ठा dc *dc, काष्ठा dc_state *context);
	bool (*update_bandwidth)(काष्ठा dc *dc, काष्ठा dc_state *context);
	व्योम (*optimize_bandwidth)(काष्ठा dc *dc, काष्ठा dc_state *context);

	/* Infopacket Related */
	व्योम (*set_avmute)(काष्ठा pipe_ctx *pipe_ctx, bool enable);
	व्योम (*send_immediate_sdp_message)(
			काष्ठा pipe_ctx *pipe_ctx,
			स्थिर uपूर्णांक8_t *custom_sdp_message,
			अचिन्हित पूर्णांक sdp_message_size);
	व्योम (*update_info_frame)(काष्ठा pipe_ctx *pipe_ctx);
	व्योम (*set_dmdata_attributes)(काष्ठा pipe_ctx *pipe);
	व्योम (*program_dmdata_engine)(काष्ठा pipe_ctx *pipe_ctx);
	bool (*dmdata_status_करोne)(काष्ठा pipe_ctx *pipe_ctx);

	/* Cursor Related */
	व्योम (*set_cursor_position)(काष्ठा pipe_ctx *pipe);
	व्योम (*set_cursor_attribute)(काष्ठा pipe_ctx *pipe);
	व्योम (*set_cursor_sdr_white_level)(काष्ठा pipe_ctx *pipe);

	/* Colour Related */
	व्योम (*program_gamut_remap)(काष्ठा pipe_ctx *pipe_ctx);
	व्योम (*program_output_csc)(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx,
			क्रमागत dc_color_space colorspace,
			uपूर्णांक16_t *matrix, पूर्णांक opp_id);

	/* VM Related */
	पूर्णांक (*init_sys_ctx)(काष्ठा dce_hwseq *hws,
			काष्ठा dc *dc,
			काष्ठा dc_phy_addr_space_config *pa_config);
	व्योम (*init_vm_ctx)(काष्ठा dce_hwseq *hws,
			काष्ठा dc *dc,
			काष्ठा dc_भव_addr_space_config *va_config,
			पूर्णांक vmid);

	/* Writeback Related */
	व्योम (*update_ग_लिखोback)(काष्ठा dc *dc,
			काष्ठा dc_ग_लिखोback_info *wb_info,
			काष्ठा dc_state *context);
	व्योम (*enable_ग_लिखोback)(काष्ठा dc *dc,
			काष्ठा dc_ग_लिखोback_info *wb_info,
			काष्ठा dc_state *context);
	व्योम (*disable_ग_लिखोback)(काष्ठा dc *dc,
			अचिन्हित पूर्णांक dwb_pipe_inst);

	bool (*mmhubbub_warmup)(काष्ठा dc *dc,
			अचिन्हित पूर्णांक num_dwb,
			काष्ठा dc_ग_लिखोback_info *wb_info);

	/* Clock Related */
	क्रमागत dc_status (*set_घड़ी)(काष्ठा dc *dc,
			क्रमागत dc_घड़ी_प्रकारype घड़ी_प्रकारype,
			uपूर्णांक32_t clk_khz, uपूर्णांक32_t stepping);
	व्योम (*get_घड़ी)(काष्ठा dc *dc, क्रमागत dc_घड़ी_प्रकारype घड़ी_प्रकारype,
			काष्ठा dc_घड़ी_config *घड़ी_cfg);
	व्योम (*optimize_pwr_state)(स्थिर काष्ठा dc *dc,
			काष्ठा dc_state *context);
	व्योम (*निकास_optimized_pwr_state)(स्थिर काष्ठा dc *dc,
			काष्ठा dc_state *context);

	/* Audio Related */
	व्योम (*enable_audio_stream)(काष्ठा pipe_ctx *pipe_ctx);
	व्योम (*disable_audio_stream)(काष्ठा pipe_ctx *pipe_ctx);

	/* Stereo 3D Related */
	व्योम (*setup_stereo)(काष्ठा pipe_ctx *pipe_ctx, काष्ठा dc *dc);

	/* HW State Logging Related */
	व्योम (*log_hw_state)(काष्ठा dc *dc, काष्ठा dc_log_buffer_ctx *log_ctx);
	व्योम (*get_hw_state)(काष्ठा dc *dc, अक्षर *pBuf,
			अचिन्हित पूर्णांक bufSize, अचिन्हित पूर्णांक mask);
	व्योम (*clear_status_bits)(काष्ठा dc *dc, अचिन्हित पूर्णांक mask);

	bool (*set_backlight_level)(काष्ठा pipe_ctx *pipe_ctx,
			uपूर्णांक32_t backlight_pwm_u16_16,
			uपूर्णांक32_t frame_ramp);

	व्योम (*set_abm_immediate_disable)(काष्ठा pipe_ctx *pipe_ctx);

	व्योम (*set_pipe)(काष्ठा pipe_ctx *pipe_ctx);

	व्योम (*get_dcc_en_bits)(काष्ठा dc *dc, पूर्णांक *dcc_en_bits);

	/* Idle Optimization Related */
	bool (*apply_idle_घातer_optimizations)(काष्ठा dc *dc, bool enable);

	bool (*करोes_plane_fit_in_mall)(काष्ठा dc *dc, काष्ठा dc_plane_state *plane,
			काष्ठा dc_cursor_attributes *cursor_attr);

	bool (*is_abm_supported)(काष्ठा dc *dc,
			काष्ठा dc_state *context, काष्ठा dc_stream_state *stream);

	व्योम (*set_disp_pattern_generator)(स्थिर काष्ठा dc *dc,
			काष्ठा pipe_ctx *pipe_ctx,
			क्रमागत controller_dp_test_pattern test_pattern,
			क्रमागत controller_dp_color_space color_space,
			क्रमागत dc_color_depth color_depth,
			स्थिर काष्ठा tg_color *solid_color,
			पूर्णांक width, पूर्णांक height, पूर्णांक offset);
पूर्ण;

व्योम color_space_to_black_color(
	स्थिर काष्ठा dc *dc,
	क्रमागत dc_color_space colorspace,
	काष्ठा tg_color *black_color);

bool hwss_रुको_क्रम_blank_complete(
		काष्ठा timing_generator *tg);

स्थिर uपूर्णांक16_t *find_color_matrix(
		क्रमागत dc_color_space color_space,
		uपूर्णांक32_t *array_size);

#पूर्ण_अगर /* __DC_HW_SEQUENCER_H__ */
