<शैली गुरु>
/*
 * Copyright 2017 Advanced Micro Devices, Inc.
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
/*
 * dc_debug.c
 *
 *  Created on: Nov 3, 2016
 *      Author: yonsun
 */

#समावेश "dm_services.h"

#समावेश "dc.h"

#समावेश "core_status.h"
#समावेश "core_types.h"

#समावेश "resource.h"

#घोषणा DC_LOGGER_INIT(logger)


#घोषणा SURFACE_TRACE(...) करो अणु\
		अगर (dc->debug.surface_trace) \
			DC_LOG_IF_TRACE(__VA_ARGS__); \
पूर्ण जबतक (0)

#घोषणा TIMING_TRACE(...) करो अणु\
	अगर (dc->debug.timing_trace) \
		DC_LOG_SYNC(__VA_ARGS__); \
पूर्ण जबतक (0)

#घोषणा CLOCK_TRACE(...) करो अणु\
	अगर (dc->debug.घड़ी_प्रकारrace) \
		DC_LOG_BANDWIDTH_CALCS(__VA_ARGS__); \
पूर्ण जबतक (0)

व्योम pre_surface_trace(
		काष्ठा dc *dc,
		स्थिर काष्ठा dc_plane_state *स्थिर *plane_states,
		पूर्णांक surface_count)
अणु
	पूर्णांक i;
	DC_LOGGER_INIT(dc->ctx->logger);

	क्रम (i = 0; i < surface_count; i++) अणु
		स्थिर काष्ठा dc_plane_state *plane_state = plane_states[i];

		SURFACE_TRACE("Planes %d:\n", i);

		SURFACE_TRACE(
				"plane_state->visible = %d;\n"
				"plane_state->flip_immediate = %d;\n"
				"plane_state->address.type = %d;\n"
				"plane_state->address.grph.addr.quad_part = 0x%llX;\n"
				"plane_state->address.grph.meta_addr.quad_part = 0x%llX;\n"
				"plane_state->scaling_quality.h_taps = %d;\n"
				"plane_state->scaling_quality.v_taps = %d;\n"
				"plane_state->scaling_quality.h_taps_c = %d;\n"
				"plane_state->scaling_quality.v_taps_c = %d;\n",
				plane_state->visible,
				plane_state->flip_immediate,
				plane_state->address.type,
				plane_state->address.grph.addr.quad_part,
				plane_state->address.grph.meta_addr.quad_part,
				plane_state->scaling_quality.h_taps,
				plane_state->scaling_quality.v_taps,
				plane_state->scaling_quality.h_taps_c,
				plane_state->scaling_quality.v_taps_c);

		SURFACE_TRACE(
				"plane_state->src_rect.x = %d;\n"
				"plane_state->src_rect.y = %d;\n"
				"plane_state->src_rect.width = %d;\n"
				"plane_state->src_rect.height = %d;\n"
				"plane_state->dst_rect.x = %d;\n"
				"plane_state->dst_rect.y = %d;\n"
				"plane_state->dst_rect.width = %d;\n"
				"plane_state->dst_rect.height = %d;\n"
				"plane_state->clip_rect.x = %d;\n"
				"plane_state->clip_rect.y = %d;\n"
				"plane_state->clip_rect.width = %d;\n"
				"plane_state->clip_rect.height = %d;\n",
				plane_state->src_rect.x,
				plane_state->src_rect.y,
				plane_state->src_rect.width,
				plane_state->src_rect.height,
				plane_state->dst_rect.x,
				plane_state->dst_rect.y,
				plane_state->dst_rect.width,
				plane_state->dst_rect.height,
				plane_state->clip_rect.x,
				plane_state->clip_rect.y,
				plane_state->clip_rect.width,
				plane_state->clip_rect.height);

		SURFACE_TRACE(
				"plane_state->plane_size.surface_size.x = %d;\n"
				"plane_state->plane_size.surface_size.y = %d;\n"
				"plane_state->plane_size.surface_size.width = %d;\n"
				"plane_state->plane_size.surface_size.height = %d;\n"
				"plane_state->plane_size.surface_pitch = %d;\n",
				plane_state->plane_size.surface_size.x,
				plane_state->plane_size.surface_size.y,
				plane_state->plane_size.surface_size.width,
				plane_state->plane_size.surface_size.height,
				plane_state->plane_size.surface_pitch);


		SURFACE_TRACE(
				"plane_state->tiling_info.gfx8.num_banks = %d;\n"
				"plane_state->tiling_info.gfx8.bank_width = %d;\n"
				"plane_state->tiling_info.gfx8.bank_width_c = %d;\n"
				"plane_state->tiling_info.gfx8.bank_height = %d;\n"
				"plane_state->tiling_info.gfx8.bank_height_c = %d;\n"
				"plane_state->tiling_info.gfx8.tile_aspect = %d;\n"
				"plane_state->tiling_info.gfx8.tile_aspect_c = %d;\n"
				"plane_state->tiling_info.gfx8.tile_split = %d;\n"
				"plane_state->tiling_info.gfx8.tile_split_c = %d;\n"
				"plane_state->tiling_info.gfx8.tile_mode = %d;\n"
				"plane_state->tiling_info.gfx8.tile_mode_c = %d;\n",
				plane_state->tiling_info.gfx8.num_banks,
				plane_state->tiling_info.gfx8.bank_width,
				plane_state->tiling_info.gfx8.bank_width_c,
				plane_state->tiling_info.gfx8.bank_height,
				plane_state->tiling_info.gfx8.bank_height_c,
				plane_state->tiling_info.gfx8.tile_aspect,
				plane_state->tiling_info.gfx8.tile_aspect_c,
				plane_state->tiling_info.gfx8.tile_split,
				plane_state->tiling_info.gfx8.tile_split_c,
				plane_state->tiling_info.gfx8.tile_mode,
				plane_state->tiling_info.gfx8.tile_mode_c);

		SURFACE_TRACE(
				"plane_state->tiling_info.gfx8.pipe_config = %d;\n"
				"plane_state->tiling_info.gfx8.array_mode = %d;\n"
				"plane_state->color_space = %d;\n"
				"plane_state->dcc.enable = %d;\n"
				"plane_state->format = %d;\n"
				"plane_state->rotation = %d;\n"
				"plane_state->stereo_format = %d;\n",
				plane_state->tiling_info.gfx8.pipe_config,
				plane_state->tiling_info.gfx8.array_mode,
				plane_state->color_space,
				plane_state->dcc.enable,
				plane_state->क्रमmat,
				plane_state->rotation,
				plane_state->stereo_क्रमmat);

		SURFACE_TRACE("plane_state->tiling_info.gfx9.swizzle = %d;\n",
				plane_state->tiling_info.gfx9.swizzle);

		SURFACE_TRACE("\n");
	पूर्ण
	SURFACE_TRACE("\n");
पूर्ण

व्योम update_surface_trace(
		काष्ठा dc *dc,
		स्थिर काष्ठा dc_surface_update *updates,
		पूर्णांक surface_count)
अणु
	पूर्णांक i;
	DC_LOGGER_INIT(dc->ctx->logger);

	क्रम (i = 0; i < surface_count; i++) अणु
		स्थिर काष्ठा dc_surface_update *update = &updates[i];

		SURFACE_TRACE("Update %d\n", i);
		अगर (update->flip_addr) अणु
			SURFACE_TRACE("flip_addr->address.type = %d;\n"
					"flip_addr->address.grph.addr.quad_part = 0x%llX;\n"
					"flip_addr->address.grph.meta_addr.quad_part = 0x%llX;\n"
					"flip_addr->flip_immediate = %d;\n",
					update->flip_addr->address.type,
					update->flip_addr->address.grph.addr.quad_part,
					update->flip_addr->address.grph.meta_addr.quad_part,
					update->flip_addr->flip_immediate);
		पूर्ण

		अगर (update->plane_info) अणु
			SURFACE_TRACE(
					"plane_info->color_space = %d;\n"
					"plane_info->format = %d;\n"
					"plane_info->plane_size.surface_pitch = %d;\n"
					"plane_info->plane_size.surface_size.height = %d;\n"
					"plane_info->plane_size.surface_size.width = %d;\n"
					"plane_info->plane_size.surface_size.x = %d;\n"
					"plane_info->plane_size.surface_size.y = %d;\n"
					"plane_info->rotation = %d;\n"
					"plane_info->stereo_format = %d;\n",
					update->plane_info->color_space,
					update->plane_info->क्रमmat,
					update->plane_info->plane_size.surface_pitch,
					update->plane_info->plane_size.surface_size.height,
					update->plane_info->plane_size.surface_size.width,
					update->plane_info->plane_size.surface_size.x,
					update->plane_info->plane_size.surface_size.y,
					update->plane_info->rotation,
					update->plane_info->stereo_क्रमmat);

			SURFACE_TRACE(
					"plane_info->tiling_info.gfx8.num_banks = %d;\n"
					"plane_info->tiling_info.gfx8.bank_width = %d;\n"
					"plane_info->tiling_info.gfx8.bank_width_c = %d;\n"
					"plane_info->tiling_info.gfx8.bank_height = %d;\n"
					"plane_info->tiling_info.gfx8.bank_height_c = %d;\n"
					"plane_info->tiling_info.gfx8.tile_aspect = %d;\n"
					"plane_info->tiling_info.gfx8.tile_aspect_c = %d;\n"
					"plane_info->tiling_info.gfx8.tile_split = %d;\n"
					"plane_info->tiling_info.gfx8.tile_split_c = %d;\n"
					"plane_info->tiling_info.gfx8.tile_mode = %d;\n"
					"plane_info->tiling_info.gfx8.tile_mode_c = %d;\n",
					update->plane_info->tiling_info.gfx8.num_banks,
					update->plane_info->tiling_info.gfx8.bank_width,
					update->plane_info->tiling_info.gfx8.bank_width_c,
					update->plane_info->tiling_info.gfx8.bank_height,
					update->plane_info->tiling_info.gfx8.bank_height_c,
					update->plane_info->tiling_info.gfx8.tile_aspect,
					update->plane_info->tiling_info.gfx8.tile_aspect_c,
					update->plane_info->tiling_info.gfx8.tile_split,
					update->plane_info->tiling_info.gfx8.tile_split_c,
					update->plane_info->tiling_info.gfx8.tile_mode,
					update->plane_info->tiling_info.gfx8.tile_mode_c);

			SURFACE_TRACE(
					"plane_info->tiling_info.gfx8.pipe_config = %d;\n"
					"plane_info->tiling_info.gfx8.array_mode = %d;\n"
					"plane_info->visible = %d;\n"
					"plane_info->per_pixel_alpha = %d;\n",
					update->plane_info->tiling_info.gfx8.pipe_config,
					update->plane_info->tiling_info.gfx8.array_mode,
					update->plane_info->visible,
					update->plane_info->per_pixel_alpha);

			SURFACE_TRACE("surface->tiling_info.gfx9.swizzle = %d;\n",
					update->plane_info->tiling_info.gfx9.swizzle);
		पूर्ण

		अगर (update->scaling_info) अणु
			SURFACE_TRACE(
					"scaling_info->src_rect.x = %d;\n"
					"scaling_info->src_rect.y = %d;\n"
					"scaling_info->src_rect.width = %d;\n"
					"scaling_info->src_rect.height = %d;\n"
					"scaling_info->dst_rect.x = %d;\n"
					"scaling_info->dst_rect.y = %d;\n"
					"scaling_info->dst_rect.width = %d;\n"
					"scaling_info->dst_rect.height = %d;\n"
					"scaling_info->clip_rect.x = %d;\n"
					"scaling_info->clip_rect.y = %d;\n"
					"scaling_info->clip_rect.width = %d;\n"
					"scaling_info->clip_rect.height = %d;\n"
					"scaling_info->scaling_quality.h_taps = %d;\n"
					"scaling_info->scaling_quality.v_taps = %d;\n"
					"scaling_info->scaling_quality.h_taps_c = %d;\n"
					"scaling_info->scaling_quality.v_taps_c = %d;\n",
					update->scaling_info->src_rect.x,
					update->scaling_info->src_rect.y,
					update->scaling_info->src_rect.width,
					update->scaling_info->src_rect.height,
					update->scaling_info->dst_rect.x,
					update->scaling_info->dst_rect.y,
					update->scaling_info->dst_rect.width,
					update->scaling_info->dst_rect.height,
					update->scaling_info->clip_rect.x,
					update->scaling_info->clip_rect.y,
					update->scaling_info->clip_rect.width,
					update->scaling_info->clip_rect.height,
					update->scaling_info->scaling_quality.h_taps,
					update->scaling_info->scaling_quality.v_taps,
					update->scaling_info->scaling_quality.h_taps_c,
					update->scaling_info->scaling_quality.v_taps_c);
		पूर्ण
		SURFACE_TRACE("\n");
	पूर्ण
	SURFACE_TRACE("\n");
पूर्ण

व्योम post_surface_trace(काष्ठा dc *dc)
अणु
	DC_LOGGER_INIT(dc->ctx->logger);

	SURFACE_TRACE("post surface process.\n");

पूर्ण

व्योम context_timing_trace(
		काष्ठा dc *dc,
		काष्ठा resource_context *res_ctx)
अणु
	पूर्णांक i;
	पूर्णांक h_pos[MAX_PIPES] = अणु0पूर्ण, v_pos[MAX_PIPES] = अणु0पूर्ण;
	काष्ठा crtc_position position;
	अचिन्हित पूर्णांक underlay_idx = dc->res_pool->underlay_pipe_index;
	DC_LOGGER_INIT(dc->ctx->logger);


	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe_ctx = &res_ctx->pipe_ctx[i];
		/* get_position() वापसs CRTC vertical/horizontal counter
		 * hence not applicable क्रम underlay pipe
		 */
		अगर (pipe_ctx->stream == शून्य || pipe_ctx->pipe_idx == underlay_idx)
			जारी;

		pipe_ctx->stream_res.tg->funcs->get_position(pipe_ctx->stream_res.tg, &position);
		h_pos[i] = position.horizontal_count;
		v_pos[i] = position.vertical_count;
	पूर्ण
	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe_ctx = &res_ctx->pipe_ctx[i];

		अगर (pipe_ctx->stream == शून्य || pipe_ctx->pipe_idx == underlay_idx)
			जारी;

		TIMING_TRACE("OTG_%d   H_tot:%d  V_tot:%d   H_pos:%d  V_pos:%d\n",
				pipe_ctx->stream_res.tg->inst,
				pipe_ctx->stream->timing.h_total,
				pipe_ctx->stream->timing.v_total,
				h_pos[i], v_pos[i]);
	पूर्ण
पूर्ण

व्योम context_घड़ी_प्रकारrace(
		काष्ठा dc *dc,
		काष्ठा dc_state *context)
अणु
#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	DC_LOGGER_INIT(dc->ctx->logger);
	CLOCK_TRACE("Current: dispclk_khz:%d  max_dppclk_khz:%d  dcfclk_khz:%d\n"
			"dcfclk_deep_sleep_khz:%d  fclk_khz:%d  socclk_khz:%d\n",
			context->bw_ctx.bw.dcn.clk.dispclk_khz,
			context->bw_ctx.bw.dcn.clk.dppclk_khz,
			context->bw_ctx.bw.dcn.clk.dcfclk_khz,
			context->bw_ctx.bw.dcn.clk.dcfclk_deep_sleep_khz,
			context->bw_ctx.bw.dcn.clk.fclk_khz,
			context->bw_ctx.bw.dcn.clk.socclk_khz);
	CLOCK_TRACE("Calculated: dispclk_khz:%d  max_dppclk_khz:%d  dcfclk_khz:%d\n"
			"dcfclk_deep_sleep_khz:%d  fclk_khz:%d  socclk_khz:%d\n",
			context->bw_ctx.bw.dcn.clk.dispclk_khz,
			context->bw_ctx.bw.dcn.clk.dppclk_khz,
			context->bw_ctx.bw.dcn.clk.dcfclk_khz,
			context->bw_ctx.bw.dcn.clk.dcfclk_deep_sleep_khz,
			context->bw_ctx.bw.dcn.clk.fclk_khz,
			context->bw_ctx.bw.dcn.clk.socclk_khz);
#पूर्ण_अगर
पूर्ण

/**
 * dc_status_to_str - convert dc_status to a human पढ़ोable string
 * @status: dc_status to be converted
 *
 * Return:
 * A string describing the DC status.
 */
अक्षर *dc_status_to_str(क्रमागत dc_status status)
अणु
	चयन (status) अणु
	हाल DC_OK:
		वापस "DC OK";
	हाल DC_NO_CONTROLLER_RESOURCE:
		वापस "No controller resource";
	हाल DC_NO_STREAM_ENC_RESOURCE:
		वापस "No stream encoder";
	हाल DC_NO_CLOCK_SOURCE_RESOURCE:
		वापस "No clock source";
	हाल DC_FAIL_CONTROLLER_VALIDATE:
		वापस "Controller validation failure";
	हाल DC_FAIL_ENC_VALIDATE:
		वापस "Encoder validation failure";
	हाल DC_FAIL_ATTACH_SURFACES:
		वापस "Surfaces attachment failure";
	हाल DC_FAIL_DETACH_SURFACES:
		वापस "Surfaces detachment failure";
	हाल DC_FAIL_SURFACE_VALIDATE:
		वापस "Surface validation failure";
	हाल DC_NO_DP_LINK_BANDWIDTH:
		वापस "No DP link bandwidth";
	हाल DC_EXCEED_DONGLE_CAP:
		वापस "Exceed dongle capability";
	हाल DC_SURFACE_PIXEL_FORMAT_UNSUPPORTED:
		वापस "Unsupported pixel format";
	हाल DC_FAIL_BANDWIDTH_VALIDATE:
		वापस "Bandwidth validation failure (BW and Watermark)";
	हाल DC_FAIL_SCALING:
		वापस "Scaling failure";
	हाल DC_FAIL_DP_LINK_TRAINING:
		वापस "DP link training failure";
	हाल DC_FAIL_DSC_VALIDATE:
		वापस "DSC validation failure";
	हाल DC_NO_DSC_RESOURCE:
		वापस "No DSC resource";
	हाल DC_FAIL_UNSUPPORTED_1:
		वापस "Unsupported";
	हाल DC_FAIL_CLK_EXCEED_MAX:
		वापस "Clk exceed max failure";
	हाल DC_FAIL_CLK_BELOW_MIN:
		वापस "Fail clk below minimum";
	हाल DC_FAIL_CLK_BELOW_CFG_REQUIRED:
		वापस "Fail clk below required CFG (hard_min in PPLIB)";
	हाल DC_NOT_SUPPORTED:
		वापस "The operation is not supported.";
	हाल DC_UNSUPPORTED_VALUE:
		वापस "The value specified is not supported.";
	हाल DC_ERROR_UNEXPECTED:
		वापस "Unexpected error";
	पूर्ण

	वापस "Unexpected status error";
पूर्ण
