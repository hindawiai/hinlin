<शैली गुरु>
/*
* Copyright 2020 Advanced Micro Devices, Inc.
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

#अगर_अघोषित __DC_HWSS_DCN30_H__
#घोषणा __DC_HWSS_DCN30_H__

#समावेश "hw_sequencer_private.h"

काष्ठा dc;

व्योम dcn30_init_hw(काष्ठा dc *dc);
व्योम dcn30_program_all_ग_लिखोback_pipes_in_tree(
		काष्ठा dc *dc,
		स्थिर काष्ठा dc_stream_state *stream,
		काष्ठा dc_state *context);
व्योम dcn30_update_ग_लिखोback(
		काष्ठा dc *dc,
		काष्ठा dc_ग_लिखोback_info *wb_info,
		काष्ठा dc_state *context);
व्योम dcn30_enable_ग_लिखोback(
		काष्ठा dc *dc,
		काष्ठा dc_ग_लिखोback_info *wb_info,
		काष्ठा dc_state *context);
व्योम dcn30_disable_ग_लिखोback(
		काष्ठा dc *dc,
		अचिन्हित पूर्णांक dwb_pipe_inst);

bool dcn30_mmhubbub_warmup(
	काष्ठा dc *dc,
	अचिन्हित पूर्णांक num_dwb,
	काष्ठा dc_ग_लिखोback_info *wb_info);

bool dcn30_set_blend_lut(काष्ठा pipe_ctx *pipe_ctx,
		स्थिर काष्ठा dc_plane_state *plane_state);

bool dcn30_set_input_transfer_func(काष्ठा dc *dc,
				काष्ठा pipe_ctx *pipe_ctx,
				स्थिर काष्ठा dc_plane_state *plane_state);
bool dcn30_set_output_transfer_func(काष्ठा dc *dc,
				काष्ठा pipe_ctx *pipe_ctx,
				स्थिर काष्ठा dc_stream_state *stream);
व्योम dcn30_set_avmute(काष्ठा pipe_ctx *pipe_ctx, bool enable);
व्योम dcn30_update_info_frame(काष्ठा pipe_ctx *pipe_ctx);
व्योम dcn30_program_dmdata_engine(काष्ठा pipe_ctx *pipe_ctx);

bool dcn30_करोes_plane_fit_in_mall(काष्ठा dc *dc, काष्ठा dc_plane_state *plane,
		काष्ठा dc_cursor_attributes *cursor_attr);

bool dcn30_apply_idle_घातer_optimizations(काष्ठा dc *dc, bool enable);

व्योम dcn30_hardware_release(काष्ठा dc *dc);

व्योम dcn30_set_disp_pattern_generator(स्थिर काष्ठा dc *dc,
		काष्ठा pipe_ctx *pipe_ctx,
		क्रमागत controller_dp_test_pattern test_pattern,
		क्रमागत controller_dp_color_space color_space,
		क्रमागत dc_color_depth color_depth,
		स्थिर काष्ठा tg_color *solid_color,
		पूर्णांक width, पूर्णांक height, पूर्णांक offset);

#पूर्ण_अगर /* __DC_HWSS_DCN30_H__ */
