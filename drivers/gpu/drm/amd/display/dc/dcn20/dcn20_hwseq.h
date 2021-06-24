<शैली गुरु>
/*
* Copyright 2016 Advanced Micro Devices, Inc.
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

#अगर_अघोषित __DC_HWSS_DCN20_H__
#घोषणा __DC_HWSS_DCN20_H__

#समावेश "hw_sequencer_private.h"

bool dcn20_set_blend_lut(
	काष्ठा pipe_ctx *pipe_ctx, स्थिर काष्ठा dc_plane_state *plane_state);
bool dcn20_set_shaper_3dlut(
	काष्ठा pipe_ctx *pipe_ctx, स्थिर काष्ठा dc_plane_state *plane_state);
व्योम dcn20_program_front_end_क्रम_ctx(
		काष्ठा dc *dc,
		काष्ठा dc_state *context);
व्योम dcn20_post_unlock_program_front_end(
		काष्ठा dc *dc,
		काष्ठा dc_state *context);
व्योम dcn20_update_plane_addr(स्थिर काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx);
व्योम dcn20_update_mpcc(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx);
bool dcn20_set_input_transfer_func(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx,
			स्थिर काष्ठा dc_plane_state *plane_state);
bool dcn20_set_output_transfer_func(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx,
			स्थिर काष्ठा dc_stream_state *stream);
व्योम dcn20_program_output_csc(काष्ठा dc *dc,
		काष्ठा pipe_ctx *pipe_ctx,
		क्रमागत dc_color_space colorspace,
		uपूर्णांक16_t *matrix,
		पूर्णांक opp_id);
व्योम dcn20_enable_stream(काष्ठा pipe_ctx *pipe_ctx);
व्योम dcn20_unblank_stream(काष्ठा pipe_ctx *pipe_ctx,
		काष्ठा dc_link_settings *link_settings);
व्योम dcn20_disable_plane(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx);
व्योम dcn20_blank_pixel_data(
		काष्ठा dc *dc,
		काष्ठा pipe_ctx *pipe_ctx,
		bool blank);
व्योम dcn20_pipe_control_lock(
	काष्ठा dc *dc,
	काष्ठा pipe_ctx *pipe,
	bool lock);
व्योम dcn20_prepare_bandwidth(
		काष्ठा dc *dc,
		काष्ठा dc_state *context);
व्योम dcn20_optimize_bandwidth(
		काष्ठा dc *dc,
		काष्ठा dc_state *context);
bool dcn20_update_bandwidth(
		काष्ठा dc *dc,
		काष्ठा dc_state *context);
व्योम dcn20_reset_hw_ctx_wrap(
		काष्ठा dc *dc,
		काष्ठा dc_state *context);
क्रमागत dc_status dcn20_enable_stream_timing(
		काष्ठा pipe_ctx *pipe_ctx,
		काष्ठा dc_state *context,
		काष्ठा dc *dc);
व्योम dcn20_disable_stream_gating(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx);
व्योम dcn20_enable_stream_gating(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx);
व्योम dcn20_setup_vupdate_पूर्णांकerrupt(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx);
व्योम dcn20_init_blank(
		काष्ठा dc *dc,
		काष्ठा timing_generator *tg);
व्योम dcn20_disable_vga(
	काष्ठा dce_hwseq *hws);
व्योम dcn20_plane_atomic_disable(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx);
व्योम dcn20_enable_घातer_gating_plane(
	काष्ठा dce_hwseq *hws,
	bool enable);
व्योम dcn20_dpp_pg_control(
		काष्ठा dce_hwseq *hws,
		अचिन्हित पूर्णांक dpp_inst,
		bool घातer_on);
व्योम dcn20_hubp_pg_control(
		काष्ठा dce_hwseq *hws,
		अचिन्हित पूर्णांक hubp_inst,
		bool घातer_on);
व्योम dcn20_program_triple_buffer(
	स्थिर काष्ठा dc *dc,
	काष्ठा pipe_ctx *pipe_ctx,
	bool enable_triple_buffer);
व्योम dcn20_enable_ग_लिखोback(
		काष्ठा dc *dc,
		काष्ठा dc_ग_लिखोback_info *wb_info,
		काष्ठा dc_state *context);
व्योम dcn20_disable_ग_लिखोback(
		काष्ठा dc *dc,
		अचिन्हित पूर्णांक dwb_pipe_inst);
व्योम dcn20_update_odm(काष्ठा dc *dc, काष्ठा dc_state *context, काष्ठा pipe_ctx *pipe_ctx);
bool dcn20_dmdata_status_करोne(काष्ठा pipe_ctx *pipe_ctx);
व्योम dcn20_program_dmdata_engine(काष्ठा pipe_ctx *pipe_ctx);
व्योम dcn20_set_dmdata_attributes(काष्ठा pipe_ctx *pipe_ctx);
व्योम dcn20_init_vm_ctx(
		काष्ठा dce_hwseq *hws,
		काष्ठा dc *dc,
		काष्ठा dc_भव_addr_space_config *va_config,
		पूर्णांक vmid);
व्योम dcn20_set_flip_control_gsl(
		काष्ठा pipe_ctx *pipe_ctx,
		bool flip_immediate);
व्योम dcn20_dsc_pg_control(
		काष्ठा dce_hwseq *hws,
		अचिन्हित पूर्णांक dsc_inst,
		bool घातer_on);
व्योम dcn20_fpga_init_hw(काष्ठा dc *dc);
bool dcn20_रुको_क्रम_blank_complete(
		काष्ठा output_pixel_processor *opp);
व्योम dcn20_dccg_init(काष्ठा dce_hwseq *hws);
पूर्णांक dcn20_init_sys_ctx(काष्ठा dce_hwseq *hws,
		काष्ठा dc *dc,
		काष्ठा dc_phy_addr_space_config *pa_config);

#अगर_अघोषित TRIM_FSFT
bool dcn20_optimize_timing_क्रम_fsft(काष्ठा dc *dc,
		काष्ठा dc_crtc_timing *timing,
		अचिन्हित पूर्णांक max_input_rate_in_khz);
#पूर्ण_अगर

व्योम dcn20_set_disp_pattern_generator(स्थिर काष्ठा dc *dc,
		काष्ठा pipe_ctx *pipe_ctx,
		क्रमागत controller_dp_test_pattern test_pattern,
		क्रमागत controller_dp_color_space color_space,
		क्रमागत dc_color_depth color_depth,
		स्थिर काष्ठा tg_color *solid_color,
		पूर्णांक width, पूर्णांक height, पूर्णांक offset);

#पूर्ण_अगर /* __DC_HWSS_DCN20_H__ */

