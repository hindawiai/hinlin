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

#समावेश "core_types.h"
#समावेश "dc_common.h"
#समावेश "basics/conversion.h"

bool is_rgb_cspace(क्रमागत dc_color_space output_color_space)
अणु
	चयन (output_color_space) अणु
	हाल COLOR_SPACE_SRGB:
	हाल COLOR_SPACE_SRGB_LIMITED:
	हाल COLOR_SPACE_2020_RGB_FULLRANGE:
	हाल COLOR_SPACE_2020_RGB_LIMITEDRANGE:
	हाल COLOR_SPACE_ADOBERGB:
		वापस true;
	हाल COLOR_SPACE_YCBCR601:
	हाल COLOR_SPACE_YCBCR709:
	हाल COLOR_SPACE_YCBCR601_LIMITED:
	हाल COLOR_SPACE_YCBCR709_LIMITED:
	हाल COLOR_SPACE_2020_YCBCR:
		वापस false;
	शेष:
		/* Add a हाल to चयन */
		BREAK_TO_DEBUGGER();
		वापस false;
	पूर्ण
पूर्ण

bool is_lower_pipe_tree_visible(काष्ठा pipe_ctx *pipe_ctx)
अणु
	अगर (pipe_ctx->plane_state && pipe_ctx->plane_state->visible)
		वापस true;
	अगर (pipe_ctx->bottom_pipe && is_lower_pipe_tree_visible(pipe_ctx->bottom_pipe))
		वापस true;
	वापस false;
पूर्ण

bool is_upper_pipe_tree_visible(काष्ठा pipe_ctx *pipe_ctx)
अणु
	अगर (pipe_ctx->plane_state && pipe_ctx->plane_state->visible)
		वापस true;
	अगर (pipe_ctx->top_pipe && is_upper_pipe_tree_visible(pipe_ctx->top_pipe))
		वापस true;
	वापस false;
पूर्ण

bool is_pipe_tree_visible(काष्ठा pipe_ctx *pipe_ctx)
अणु
	अगर (pipe_ctx->plane_state && pipe_ctx->plane_state->visible)
		वापस true;
	अगर (pipe_ctx->top_pipe && is_upper_pipe_tree_visible(pipe_ctx->top_pipe))
		वापस true;
	अगर (pipe_ctx->bottom_pipe && is_lower_pipe_tree_visible(pipe_ctx->bottom_pipe))
		वापस true;
	वापस false;
पूर्ण

व्योम build_prescale_params(काष्ठा  dc_bias_and_scale *bias_and_scale,
		स्थिर काष्ठा dc_plane_state *plane_state)
अणु
	अगर (plane_state->क्रमmat >= SURFACE_PIXEL_FORMAT_VIDEO_BEGIN
			&& plane_state->क्रमmat != SURFACE_PIXEL_FORMAT_INVALID
			&& plane_state->input_csc_color_matrix.enable_adjusपंचांगent
			&& plane_state->coeff_reduction_factor.value != 0) अणु
		bias_and_scale->scale_blue = fixed_poपूर्णांक_to_पूर्णांक_frac(
			dc_fixpt_mul(plane_state->coeff_reduction_factor,
					dc_fixpt_from_fraction(256, 255)),
				2,
				13);
		bias_and_scale->scale_red = bias_and_scale->scale_blue;
		bias_and_scale->scale_green = bias_and_scale->scale_blue;
	पूर्ण अन्यथा अणु
		bias_and_scale->scale_blue = 0x2000;
		bias_and_scale->scale_red = 0x2000;
		bias_and_scale->scale_green = 0x2000;
	पूर्ण
पूर्ण

