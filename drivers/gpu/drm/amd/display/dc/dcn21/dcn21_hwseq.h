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

#अगर_अघोषित __DC_HWSS_DCN21_H__
#घोषणा __DC_HWSS_DCN21_H__

#समावेश "hw_sequencer_private.h"

काष्ठा dc;

पूर्णांक dcn21_init_sys_ctx(काष्ठा dce_hwseq *hws,
		काष्ठा dc *dc,
		काष्ठा dc_phy_addr_space_config *pa_config);

bool dcn21_s0i3_golden_init_wa(काष्ठा dc *dc);

व्योम dcn21_निकास_optimized_pwr_state(
		स्थिर काष्ठा dc *dc,
		काष्ठा dc_state *context);

व्योम dcn21_optimize_pwr_state(
		स्थिर काष्ठा dc *dc,
		काष्ठा dc_state *context);

व्योम dcn21_PLAT_58856_wa(काष्ठा dc_state *context,
		काष्ठा pipe_ctx *pipe_ctx);

व्योम dcn21_set_pipe(काष्ठा pipe_ctx *pipe_ctx);
व्योम dcn21_set_abm_immediate_disable(काष्ठा pipe_ctx *pipe_ctx);
bool dcn21_set_backlight_level(काष्ठा pipe_ctx *pipe_ctx,
		uपूर्णांक32_t backlight_pwm_u16_16,
		uपूर्णांक32_t frame_ramp);
bool dcn21_is_abm_supported(काष्ठा dc *dc,
		काष्ठा dc_state *context, काष्ठा dc_stream_state *stream);

#पूर्ण_अगर /* __DC_HWSS_DCN21_H__ */
