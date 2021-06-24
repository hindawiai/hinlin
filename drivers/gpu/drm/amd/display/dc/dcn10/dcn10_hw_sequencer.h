<शैली गुरु>
/*
* Copyright 2016-2020 Advanced Micro Devices, Inc.
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

#अगर_अघोषित __DC_HWSS_DCN10_H__
#घोषणा __DC_HWSS_DCN10_H__

#समावेश "core_types.h"
#समावेश "hw_sequencer_private.h"

काष्ठा dc;

व्योम dcn10_hw_sequencer_स्थिरruct(काष्ठा dc *dc);

पूर्णांक dcn10_get_vupdate_offset_from_vsync(काष्ठा pipe_ctx *pipe_ctx);
व्योम dcn10_calc_vupdate_position(
		काष्ठा dc *dc,
		काष्ठा pipe_ctx *pipe_ctx,
		uपूर्णांक32_t *start_line,
		uपूर्णांक32_t *end_line);
व्योम dcn10_setup_vupdate_पूर्णांकerrupt(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx);
क्रमागत dc_status dcn10_enable_stream_timing(
		काष्ठा pipe_ctx *pipe_ctx,
		काष्ठा dc_state *context,
		काष्ठा dc *dc);
व्योम dcn10_optimize_bandwidth(
		काष्ठा dc *dc,
		काष्ठा dc_state *context);
व्योम dcn10_prepare_bandwidth(
		काष्ठा dc *dc,
		काष्ठा dc_state *context);
व्योम dcn10_pipe_control_lock(
	काष्ठा dc *dc,
	काष्ठा pipe_ctx *pipe,
	bool lock);
व्योम dcn10_cursor_lock(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe, bool lock);
व्योम dcn10_blank_pixel_data(
		काष्ठा dc *dc,
		काष्ठा pipe_ctx *pipe_ctx,
		bool blank);
व्योम dcn10_unblank_stream(काष्ठा pipe_ctx *pipe_ctx,
		काष्ठा dc_link_settings *link_settings);
व्योम dcn10_program_output_csc(काष्ठा dc *dc,
		काष्ठा pipe_ctx *pipe_ctx,
		क्रमागत dc_color_space colorspace,
		uपूर्णांक16_t *matrix,
		पूर्णांक opp_id);
bool dcn10_set_output_transfer_func(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx,
				स्थिर काष्ठा dc_stream_state *stream);
bool dcn10_set_input_transfer_func(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx,
			स्थिर काष्ठा dc_plane_state *plane_state);
व्योम dcn10_update_plane_addr(स्थिर काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx);
व्योम dcn10_update_mpcc(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx);
व्योम dcn10_reset_hw_ctx_wrap(
		काष्ठा dc *dc,
		काष्ठा dc_state *context);
व्योम dcn10_disable_plane(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx);
व्योम dcn10_lock_all_pipes(
		काष्ठा dc *dc,
		काष्ठा dc_state *context,
		bool lock);
व्योम dcn10_apply_ctx_क्रम_surface(
		काष्ठा dc *dc,
		स्थिर काष्ठा dc_stream_state *stream,
		पूर्णांक num_planes,
		काष्ठा dc_state *context);
व्योम dcn10_post_unlock_program_front_end(
		काष्ठा dc *dc,
		काष्ठा dc_state *context);
व्योम dcn10_hubp_pg_control(
		काष्ठा dce_hwseq *hws,
		अचिन्हित पूर्णांक hubp_inst,
		bool घातer_on);
व्योम dcn10_dpp_pg_control(
		काष्ठा dce_hwseq *hws,
		अचिन्हित पूर्णांक dpp_inst,
		bool घातer_on);
व्योम dcn10_enable_घातer_gating_plane(
	काष्ठा dce_hwseq *hws,
	bool enable);
व्योम dcn10_plane_atomic_disable(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx);
व्योम dcn10_disable_vga(
	काष्ठा dce_hwseq *hws);
व्योम dcn10_program_pipe(
		काष्ठा dc *dc,
		काष्ठा pipe_ctx *pipe_ctx,
		काष्ठा dc_state *context);
व्योम dcn10_program_gamut_remap(काष्ठा pipe_ctx *pipe_ctx);
व्योम dcn10_init_hw(काष्ठा dc *dc);
व्योम dcn10_init_pipes(काष्ठा dc *dc, काष्ठा dc_state *context);
व्योम dcn10_घातer_करोwn_on_boot(काष्ठा dc *dc);
क्रमागत dc_status dce110_apply_ctx_to_hw(
		काष्ठा dc *dc,
		काष्ठा dc_state *context);
व्योम dcn10_plane_atomic_disconnect(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx);
व्योम dcn10_update_dchub(काष्ठा dce_hwseq *hws, काष्ठा dchub_init_data *dh_data);
व्योम dcn10_update_pending_status(काष्ठा pipe_ctx *pipe_ctx);
व्योम dce110_घातer_करोwn(काष्ठा dc *dc);
व्योम dce110_enable_accelerated_mode(काष्ठा dc *dc, काष्ठा dc_state *context);
व्योम dcn10_enable_timing_synchronization(
		काष्ठा dc *dc,
		पूर्णांक group_index,
		पूर्णांक group_size,
		काष्ठा pipe_ctx *grouped_pipes[]);
व्योम dcn10_enable_vblanks_synchronization(
		काष्ठा dc *dc,
		पूर्णांक group_index,
		पूर्णांक group_size,
		काष्ठा pipe_ctx *grouped_pipes[]);
व्योम dcn10_enable_per_frame_crtc_position_reset(
		काष्ठा dc *dc,
		पूर्णांक group_size,
		काष्ठा pipe_ctx *grouped_pipes[]);
व्योम dce110_update_info_frame(काष्ठा pipe_ctx *pipe_ctx);
व्योम dcn10_send_immediate_sdp_message(काष्ठा pipe_ctx *pipe_ctx,
		स्थिर uपूर्णांक8_t *custom_sdp_message,
		अचिन्हित पूर्णांक sdp_message_size);
व्योम dce110_blank_stream(काष्ठा pipe_ctx *pipe_ctx);
व्योम dce110_enable_audio_stream(काष्ठा pipe_ctx *pipe_ctx);
व्योम dce110_disable_audio_stream(काष्ठा pipe_ctx *pipe_ctx);
bool dcn10_dummy_display_घातer_gating(
		काष्ठा dc *dc,
		uपूर्णांक8_t controller_id,
		काष्ठा dc_bios *dcb,
		क्रमागत pipe_gating_control घातer_gating);
व्योम dcn10_set_drr(काष्ठा pipe_ctx **pipe_ctx,
		पूर्णांक num_pipes, काष्ठा dc_crtc_timing_adjust adjust);
व्योम dcn10_get_position(काष्ठा pipe_ctx **pipe_ctx,
		पूर्णांक num_pipes,
		काष्ठा crtc_position *position);
व्योम dcn10_set_अटल_screen_control(काष्ठा pipe_ctx **pipe_ctx,
		पूर्णांक num_pipes, स्थिर काष्ठा dc_अटल_screen_params *params);
व्योम dcn10_setup_stereo(काष्ठा pipe_ctx *pipe_ctx, काष्ठा dc *dc);
व्योम dce110_set_avmute(काष्ठा pipe_ctx *pipe_ctx, bool enable);
व्योम dcn10_log_hw_state(काष्ठा dc *dc,
		काष्ठा dc_log_buffer_ctx *log_ctx);
व्योम dcn10_get_hw_state(काष्ठा dc *dc,
		अक्षर *pBuf,
		अचिन्हित पूर्णांक bufSize,
		अचिन्हित पूर्णांक mask);
व्योम dcn10_clear_status_bits(काष्ठा dc *dc, अचिन्हित पूर्णांक mask);
व्योम dcn10_रुको_क्रम_mpcc_disconnect(
		काष्ठा dc *dc,
		काष्ठा resource_pool *res_pool,
		काष्ठा pipe_ctx *pipe_ctx);
व्योम dce110_edp_backlight_control(
		काष्ठा dc_link *link,
		bool enable);
व्योम dce110_edp_रुको_क्रम_T12(
		काष्ठा dc_link *link);
व्योम dce110_edp_घातer_control(
		काष्ठा dc_link *link,
		bool घातer_up);
व्योम dce110_edp_रुको_क्रम_hpd_पढ़ोy(
		काष्ठा dc_link *link,
		bool घातer_up);
व्योम dcn10_set_cursor_position(काष्ठा pipe_ctx *pipe_ctx);
व्योम dcn10_set_cursor_attribute(काष्ठा pipe_ctx *pipe_ctx);
व्योम dcn10_set_cursor_sdr_white_level(काष्ठा pipe_ctx *pipe_ctx);
व्योम dcn10_setup_periodic_पूर्णांकerrupt(
		काष्ठा dc *dc,
		काष्ठा pipe_ctx *pipe_ctx,
		क्रमागत vline_select vline);
क्रमागत dc_status dcn10_set_घड़ी(काष्ठा dc *dc,
		क्रमागत dc_घड़ी_प्रकारype घड़ी_प्रकारype,
		uपूर्णांक32_t clk_khz,
		uपूर्णांक32_t stepping);
व्योम dcn10_get_घड़ी(काष्ठा dc *dc,
		क्रमागत dc_घड़ी_प्रकारype घड़ी_प्रकारype,
		काष्ठा dc_घड़ी_config *घड़ी_cfg);
bool dcn10_did_underflow_occur(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx);
व्योम dcn10_bios_golden_init(काष्ठा dc *dc);
व्योम dcn10_plane_atomic_घातer_करोwn(काष्ठा dc *dc,
		काष्ठा dpp *dpp,
		काष्ठा hubp *hubp);
व्योम dcn10_get_surface_visual_confirm_color(
		स्थिर काष्ठा pipe_ctx *pipe_ctx,
		काष्ठा tg_color *color);
व्योम dcn10_get_hdr_visual_confirm_color(
		काष्ठा pipe_ctx *pipe_ctx,
		काष्ठा tg_color *color);
bool dcn10_disconnect_pipes(
		काष्ठा dc *dc,
		काष्ठा dc_state *context);

व्योम dcn10_रुको_क्रम_pending_cleared(काष्ठा dc *dc,
		काष्ठा dc_state *context);
व्योम dcn10_set_hdr_multiplier(काष्ठा pipe_ctx *pipe_ctx);
व्योम dcn10_verअगरy_allow_pstate_change_high(काष्ठा dc *dc);

व्योम dcn10_get_dcc_en_bits(काष्ठा dc *dc, पूर्णांक *dcc_en_bits);

#पूर्ण_अगर /* __DC_HWSS_DCN10_H__ */
