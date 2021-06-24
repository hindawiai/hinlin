<शैली गुरु>
/*
* Copyright 2012-15 Advanced Micro Devices, Inc.
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

#अगर_अघोषित __DC_HWSS_DCE110_H__
#घोषणा __DC_HWSS_DCE110_H__

#समावेश "core_types.h"
#समावेश "hw_sequencer_private.h"

काष्ठा dc;
काष्ठा dc_state;
काष्ठा dm_pp_display_configuration;

व्योम dce110_hw_sequencer_स्थिरruct(काष्ठा dc *dc);

क्रमागत dc_status dce110_apply_ctx_to_hw(
		काष्ठा dc *dc,
		काष्ठा dc_state *context);


व्योम dce110_enable_stream(काष्ठा pipe_ctx *pipe_ctx);

व्योम dce110_disable_stream(काष्ठा pipe_ctx *pipe_ctx);

व्योम dce110_unblank_stream(काष्ठा pipe_ctx *pipe_ctx,
		काष्ठा dc_link_settings *link_settings);

व्योम dce110_blank_stream(काष्ठा pipe_ctx *pipe_ctx);

व्योम dce110_enable_audio_stream(काष्ठा pipe_ctx *pipe_ctx);
व्योम dce110_disable_audio_stream(काष्ठा pipe_ctx *pipe_ctx);

व्योम dce110_update_info_frame(काष्ठा pipe_ctx *pipe_ctx);

व्योम dce110_set_avmute(काष्ठा pipe_ctx *pipe_ctx, bool enable);
व्योम dce110_enable_accelerated_mode(काष्ठा dc *dc, काष्ठा dc_state *context);

व्योम dce110_घातer_करोwn(काष्ठा dc *dc);

व्योम dce110_set_safe_displaymarks(
		काष्ठा resource_context *res_ctx,
		स्थिर काष्ठा resource_pool *pool);

व्योम dce110_prepare_bandwidth(
		काष्ठा dc *dc,
		काष्ठा dc_state *context);

व्योम dce110_optimize_bandwidth(
		काष्ठा dc *dc,
		काष्ठा dc_state *context);

व्योम dp_receiver_घातer_ctrl(काष्ठा dc_link *link, bool on);

व्योम dce110_edp_घातer_control(
		काष्ठा dc_link *link,
		bool घातer_up);

व्योम dce110_edp_backlight_control(
	काष्ठा dc_link *link,
	bool enable);

व्योम dce110_edp_रुको_क्रम_hpd_पढ़ोy(
		काष्ठा dc_link *link,
		bool घातer_up);

bool dce110_set_backlight_level(काष्ठा pipe_ctx *pipe_ctx,
		uपूर्णांक32_t backlight_pwm_u16_16,
		uपूर्णांक32_t frame_ramp);
व्योम dce110_set_abm_immediate_disable(काष्ठा pipe_ctx *pipe_ctx);
व्योम dce110_set_pipe(काष्ठा pipe_ctx *pipe_ctx);

#पूर्ण_अगर /* __DC_HWSS_DCE110_H__ */

