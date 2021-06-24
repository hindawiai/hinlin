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
 */

#समावेश "amdgpu_dm_trace.h"

#घोषणा TRACE_DC_PIPE_STATE(pipe_ctx, index, max_pipes) \
	क्रम (index = 0; index < max_pipes; ++index) अणु \
		काष्ठा pipe_ctx *pipe_ctx = &dc->current_state->res_ctx.pipe_ctx[index]; \
		अगर (pipe_ctx->plane_state) \
			trace_amdgpu_dm_dc_pipe_state(pipe_ctx->pipe_idx, pipe_ctx->plane_state, \
						      pipe_ctx->stream, &pipe_ctx->plane_res, \
						      pipe_ctx->update_flags.raw); \
	पूर्ण

#घोषणा TRACE_DCE_CLOCK_STATE(dce_घड़ीs) \
	trace_amdgpu_dm_dce_घड़ीs_state(dce_घड़ीs)

#घोषणा TRACE_DCN_CLOCK_STATE(dcn_घड़ीs) \
	trace_amdgpu_dm_dc_घड़ीs_state(dcn_घड़ीs)
