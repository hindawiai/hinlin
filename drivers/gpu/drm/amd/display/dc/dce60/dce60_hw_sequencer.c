<शैली गुरु>
/*
 * Copyright 2020 Mauro Rossi <issor.oruam@gmail.com>
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

#समावेश "dm_services.h"
#समावेश "dc.h"
#समावेश "core_types.h"
#समावेश "dce60_hw_sequencer.h"

#समावेश "dce/dce_hwseq.h"
#समावेश "dce110/dce110_hw_sequencer.h"
#समावेश "dce100/dce100_hw_sequencer.h"

/* include DCE6 रेजिस्टर header files */
#समावेश "dce/dce_6_0_d.h"
#समावेश "dce/dce_6_0_sh_mask.h"

#घोषणा DC_LOGGER_INIT()

/*******************************************************************************
 * Private definitions
 ******************************************************************************/

/***************************PIPE_CONTROL***********************************/

/*
 *  Check अगर FBC can be enabled
 */
अटल bool dce60_should_enable_fbc(काष्ठा dc *dc,
		काष्ठा dc_state *context,
		uपूर्णांक32_t *pipe_idx)
अणु
	uपूर्णांक32_t i;
	काष्ठा pipe_ctx *pipe_ctx = शून्य;
	काष्ठा resource_context *res_ctx = &context->res_ctx;
	अचिन्हित पूर्णांक underlay_idx = dc->res_pool->underlay_pipe_index;


	ASSERT(dc->fbc_compressor);

	/* FBC memory should be allocated */
	अगर (!dc->ctx->fbc_gpu_addr)
		वापस false;

	/* Only supports single display */
	अगर (context->stream_count != 1)
		वापस false;

	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		अगर (res_ctx->pipe_ctx[i].stream) अणु

			pipe_ctx = &res_ctx->pipe_ctx[i];

			अगर (!pipe_ctx)
				जारी;

			/* fbc not applicable on underlay pipe */
			अगर (pipe_ctx->pipe_idx != underlay_idx) अणु
				*pipe_idx = i;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (i == dc->res_pool->pipe_count)
		वापस false;

	अगर (!pipe_ctx->stream->link)
		वापस false;

	/* Only supports eDP */
	अगर (pipe_ctx->stream->link->connector_संकेत != SIGNAL_TYPE_EDP)
		वापस false;

	/* PSR should not be enabled */
	अगर (pipe_ctx->stream->link->psr_settings.psr_feature_enabled)
		वापस false;

	/* Nothing to compress */
	अगर (!pipe_ctx->plane_state)
		वापस false;

	/* Only क्रम non-linear tiling */
	अगर (pipe_ctx->plane_state->tiling_info.gfx8.array_mode == DC_ARRAY_LINEAR_GENERAL)
		वापस false;

	वापस true;
पूर्ण

/*
 *  Enable FBC
 */
अटल व्योम dce60_enable_fbc(
		काष्ठा dc *dc,
		काष्ठा dc_state *context)
अणु
	uपूर्णांक32_t pipe_idx = 0;

	अगर (dce60_should_enable_fbc(dc, context, &pipe_idx)) अणु
		/* Program GRPH COMPRESSED ADDRESS and PITCH */
		काष्ठा compr_addr_and_pitch_params params = अणु0, 0, 0पूर्ण;
		काष्ठा compressor *compr = dc->fbc_compressor;
		काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[pipe_idx];

		params.source_view_width = pipe_ctx->stream->timing.h_addressable;
		params.source_view_height = pipe_ctx->stream->timing.v_addressable;
		params.inst = pipe_ctx->stream_res.tg->inst;
		compr->compr_surface_address.quad_part = dc->ctx->fbc_gpu_addr;

		compr->funcs->surface_address_and_pitch(compr, &params);
		compr->funcs->set_fbc_invalidation_triggers(compr, 1);

		compr->funcs->enable_fbc(compr, &params);
	पूर्ण
पूर्ण


/*******************************************************************************
 * Front End programming
 ******************************************************************************/

अटल व्योम dce60_set_शेष_colors(काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा शेष_adjusपंचांगent शेष_adjust = अणु 0 पूर्ण;

	शेष_adjust.क्रमce_hw_शेष = false;
	शेष_adjust.in_color_space = pipe_ctx->plane_state->color_space;
	शेष_adjust.out_color_space = pipe_ctx->stream->output_color_space;
	शेष_adjust.csc_adjust_type = GRAPHICS_CSC_ADJUST_TYPE_SW;
	शेष_adjust.surface_pixel_क्रमmat = pipe_ctx->plane_res.scl_data.क्रमmat;

	/* display color depth */
	शेष_adjust.color_depth =
		pipe_ctx->stream->timing.display_color_depth;

	/* Lb color depth */
	शेष_adjust.lb_color_depth = pipe_ctx->plane_res.scl_data.lb_params.depth;

	pipe_ctx->plane_res.xfm->funcs->opp_set_csc_शेष(
					pipe_ctx->plane_res.xfm, &शेष_adjust);
पूर्ण

/*******************************************************************************
 * In order to turn on surface we will program
 * CRTC
 *
 * DCE6 has no bottom_pipe and no Blender HW
 * We need to set 'blank_target' to false in order to turn on the display
 *
 * |-----------|------------|---------|
 * |curr pipe  | set_blank  |         |
 * |Surface    |blank_target|  CRCT   |
 * |visibility |  argument  |         |
 * |-----------|------------|---------|
 * |    off    |   true     | blank   |
 * |    on     |   false    | unblank |
 * |-----------|------------|---------|
 *
 ******************************************************************************/
अटल व्योम dce60_program_surface_visibility(स्थिर काष्ठा dc *dc,
		काष्ठा pipe_ctx *pipe_ctx)
अणु
	bool blank_target = false;

	/* DCE6 has no bottom_pipe and no Blender HW */

	अगर (!pipe_ctx->plane_state->visible)
		blank_target = true;

	/* DCE6 skip dce_set_blender_mode() but then proceed to 'unblank' CRTC */
	pipe_ctx->stream_res.tg->funcs->set_blank(pipe_ctx->stream_res.tg, blank_target);

पूर्ण


अटल व्योम dce60_get_surface_visual_confirm_color(स्थिर काष्ठा pipe_ctx *pipe_ctx,
		काष्ठा tg_color *color)
अणु
	uपूर्णांक32_t color_value = MAX_TG_COLOR_VALUE * (4 - pipe_ctx->stream_res.tg->inst) / 4;

	चयन (pipe_ctx->plane_res.scl_data.क्रमmat) अणु
	हाल PIXEL_FORMAT_ARGB8888:
		/* set boarder color to red */
		color->color_r_cr = color_value;
		अवरोध;

	हाल PIXEL_FORMAT_ARGB2101010:
		/* set boarder color to blue */
		color->color_b_cb = color_value;
		अवरोध;
	हाल PIXEL_FORMAT_420BPP8:
		/* set boarder color to green */
		color->color_g_y = color_value;
		अवरोध;
	हाल PIXEL_FORMAT_420BPP10:
		/* set boarder color to yellow */
		color->color_g_y = color_value;
		color->color_r_cr = color_value;
		अवरोध;
	हाल PIXEL_FORMAT_FP16:
		/* set boarder color to white */
		color->color_r_cr = color_value;
		color->color_b_cb = color_value;
		color->color_g_y = color_value;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम dce60_program_scaler(स्थिर काष्ठा dc *dc,
		स्थिर काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा tg_color color = अणु0पूर्ण;

	/* DCE6 skips DCN TOFPGA check क्रम transक्रमm_set_pixel_storage_depth == शून्य */

	अगर (dc->debug.visual_confirm == VISUAL_CONFIRM_SURFACE)
		dce60_get_surface_visual_confirm_color(pipe_ctx, &color);
	अन्यथा
		color_space_to_black_color(dc,
				pipe_ctx->stream->output_color_space,
				&color);

	pipe_ctx->plane_res.xfm->funcs->transक्रमm_set_pixel_storage_depth(
		pipe_ctx->plane_res.xfm,
		pipe_ctx->plane_res.scl_data.lb_params.depth,
		&pipe_ctx->stream->bit_depth_params);

	अगर (pipe_ctx->stream_res.tg->funcs->set_overscan_blank_color) अणु
		/*
		 * The way 420 is packed, 2 channels carry Y component, 1 channel
		 * alternate between Cb and Cr, so both channels need the pixel
		 * value क्रम Y
		 */
		अगर (pipe_ctx->stream->timing.pixel_encoding == PIXEL_ENCODING_YCBCR420)
			color.color_r_cr = color.color_g_y;

		pipe_ctx->stream_res.tg->funcs->set_overscan_blank_color(
				pipe_ctx->stream_res.tg,
				&color);
	पूर्ण

	pipe_ctx->plane_res.xfm->funcs->transक्रमm_set_scaler(pipe_ctx->plane_res.xfm,
		&pipe_ctx->plane_res.scl_data);
पूर्ण

अटल व्योम
dce60_program_front_end_क्रम_pipe(
		काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा mem_input *mi = pipe_ctx->plane_res.mi;
	काष्ठा dc_plane_state *plane_state = pipe_ctx->plane_state;
	काष्ठा xfm_grph_csc_adjusपंचांगent adjust;
	काष्ठा out_csc_color_matrix tbl_entry;
	अचिन्हित पूर्णांक i;
	काष्ठा dce_hwseq *hws = dc->hwseq;

	DC_LOGGER_INIT();
	स_रखो(&tbl_entry, 0, माप(tbl_entry));

	स_रखो(&adjust, 0, माप(adjust));
	adjust.gamut_adjust_type = GRAPHICS_GAMUT_ADJUST_TYPE_BYPASS;

	dce_enable_fe_घड़ी(dc->hwseq, mi->inst, true);

	dce60_set_शेष_colors(pipe_ctx);
	अगर (pipe_ctx->stream->csc_color_matrix.enable_adjusपंचांगent
			== true) अणु
		tbl_entry.color_space =
			pipe_ctx->stream->output_color_space;

		क्रम (i = 0; i < 12; i++)
			tbl_entry.regval[i] =
			pipe_ctx->stream->csc_color_matrix.matrix[i];

		pipe_ctx->plane_res.xfm->funcs->opp_set_csc_adjusपंचांगent
				(pipe_ctx->plane_res.xfm, &tbl_entry);
	पूर्ण

	अगर (pipe_ctx->stream->gamut_remap_matrix.enable_remap == true) अणु
		adjust.gamut_adjust_type = GRAPHICS_GAMUT_ADJUST_TYPE_SW;

		क्रम (i = 0; i < CSC_TEMPERATURE_MATRIX_SIZE; i++)
			adjust.temperature_matrix[i] =
				pipe_ctx->stream->gamut_remap_matrix.matrix[i];
	पूर्ण

	pipe_ctx->plane_res.xfm->funcs->transक्रमm_set_gamut_remap(pipe_ctx->plane_res.xfm, &adjust);

	pipe_ctx->plane_res.scl_data.lb_params.alpha_en = pipe_ctx->bottom_pipe != 0;

	dce60_program_scaler(dc, pipe_ctx);

	mi->funcs->mem_input_program_surface_config(
			mi,
			plane_state->क्रमmat,
			&plane_state->tiling_info,
			&plane_state->plane_size,
			plane_state->rotation,
			शून्य,
			false);
	अगर (mi->funcs->set_blank)
		mi->funcs->set_blank(mi, pipe_ctx->plane_state->visible);

	अगर (dc->config.gpu_vm_support)
		mi->funcs->mem_input_program_pte_vm(
				pipe_ctx->plane_res.mi,
				plane_state->क्रमmat,
				&plane_state->tiling_info,
				plane_state->rotation);

	/* Moved programming gamma from dc to hwss */
	अगर (pipe_ctx->plane_state->update_flags.bits.full_update ||
			pipe_ctx->plane_state->update_flags.bits.in_transfer_func_change ||
			pipe_ctx->plane_state->update_flags.bits.gamma_change)
		hws->funcs.set_input_transfer_func(dc, pipe_ctx, pipe_ctx->plane_state);

	अगर (pipe_ctx->plane_state->update_flags.bits.full_update)
		hws->funcs.set_output_transfer_func(dc, pipe_ctx, pipe_ctx->stream);

	DC_LOG_SURFACE(
			"Pipe:%d %p: addr hi:0x%x, "
			"addr low:0x%x, "
			"src: %d, %d, %d,"
			" %d; dst: %d, %d, %d, %d;"
			"clip: %d, %d, %d, %d\n",
			pipe_ctx->pipe_idx,
			(व्योम *) pipe_ctx->plane_state,
			pipe_ctx->plane_state->address.grph.addr.high_part,
			pipe_ctx->plane_state->address.grph.addr.low_part,
			pipe_ctx->plane_state->src_rect.x,
			pipe_ctx->plane_state->src_rect.y,
			pipe_ctx->plane_state->src_rect.width,
			pipe_ctx->plane_state->src_rect.height,
			pipe_ctx->plane_state->dst_rect.x,
			pipe_ctx->plane_state->dst_rect.y,
			pipe_ctx->plane_state->dst_rect.width,
			pipe_ctx->plane_state->dst_rect.height,
			pipe_ctx->plane_state->clip_rect.x,
			pipe_ctx->plane_state->clip_rect.y,
			pipe_ctx->plane_state->clip_rect.width,
			pipe_ctx->plane_state->clip_rect.height);

	DC_LOG_SURFACE(
			"Pipe %d: width, height, x, y\n"
			"viewport:%d, %d, %d, %d\n"
			"recout:  %d, %d, %d, %d\n",
			pipe_ctx->pipe_idx,
			pipe_ctx->plane_res.scl_data.viewport.width,
			pipe_ctx->plane_res.scl_data.viewport.height,
			pipe_ctx->plane_res.scl_data.viewport.x,
			pipe_ctx->plane_res.scl_data.viewport.y,
			pipe_ctx->plane_res.scl_data.recout.width,
			pipe_ctx->plane_res.scl_data.recout.height,
			pipe_ctx->plane_res.scl_data.recout.x,
			pipe_ctx->plane_res.scl_data.recout.y);
पूर्ण

अटल व्योम dce60_apply_ctx_क्रम_surface(
		काष्ठा dc *dc,
		स्थिर काष्ठा dc_stream_state *stream,
		पूर्णांक num_planes,
		काष्ठा dc_state *context)
अणु
	पूर्णांक i;

	अगर (num_planes == 0)
		वापस;

	अगर (dc->fbc_compressor)
		dc->fbc_compressor->funcs->disable_fbc(dc->fbc_compressor);

	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];

		अगर (pipe_ctx->stream != stream)
			जारी;

		/* Need to allocate mem beक्रमe program front end क्रम Fiji */
		pipe_ctx->plane_res.mi->funcs->allocate_mem_input(
				pipe_ctx->plane_res.mi,
				pipe_ctx->stream->timing.h_total,
				pipe_ctx->stream->timing.v_total,
				pipe_ctx->stream->timing.pix_clk_100hz / 10,
				context->stream_count);

		dce60_program_front_end_क्रम_pipe(dc, pipe_ctx);

		dc->hwss.update_plane_addr(dc, pipe_ctx);

		dce60_program_surface_visibility(dc, pipe_ctx);

	पूर्ण

	अगर (dc->fbc_compressor)
		dce60_enable_fbc(dc, context);
पूर्ण

व्योम dce60_hw_sequencer_स्थिरruct(काष्ठा dc *dc)
अणु
	dce110_hw_sequencer_स्थिरruct(dc);

	dc->hwseq->funcs.enable_display_घातer_gating = dce100_enable_display_घातer_gating;
	dc->hwss.apply_ctx_क्रम_surface = dce60_apply_ctx_क्रम_surface;
	dc->hwss.cursor_lock = dce60_pipe_control_lock;
	dc->hwss.pipe_control_lock = dce60_pipe_control_lock;
	dc->hwss.prepare_bandwidth = dce100_prepare_bandwidth;
	dc->hwss.optimize_bandwidth = dce100_optimize_bandwidth;
पूर्ण

