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

#समावेश <linux/delay.h>
#समावेश <linux/slab.h>

#समावेश "dm_services.h"
#समावेश "basics/dc_common.h"
#समावेश "dc.h"
#समावेश "core_types.h"
#समावेश "resource.h"
#समावेश "ipp.h"
#समावेश "timing_generator.h"

#घोषणा DC_LOGGER dc->ctx->logger

/*******************************************************************************
 * Private functions
 ******************************************************************************/
व्योम update_stream_संकेत(काष्ठा dc_stream_state *stream, काष्ठा dc_sink *sink)
अणु
	अगर (sink->sink_संकेत == SIGNAL_TYPE_NONE)
		stream->संकेत = stream->link->connector_संकेत;
	अन्यथा
		stream->संकेत = sink->sink_संकेत;

	अगर (dc_is_dvi_संकेत(stream->संकेत)) अणु
		अगर (stream->ctx->dc->caps.dual_link_dvi &&
			(stream->timing.pix_clk_100hz / 10) > TMDS_MAX_PIXEL_CLOCK &&
			sink->sink_संकेत != SIGNAL_TYPE_DVI_SINGLE_LINK)
			stream->संकेत = SIGNAL_TYPE_DVI_DUAL_LINK;
		अन्यथा
			stream->संकेत = SIGNAL_TYPE_DVI_SINGLE_LINK;
	पूर्ण
पूर्ण

अटल bool dc_stream_स्थिरruct(काष्ठा dc_stream_state *stream,
	काष्ठा dc_sink *dc_sink_data)
अणु
	uपूर्णांक32_t i = 0;

	stream->sink = dc_sink_data;
	dc_sink_retain(dc_sink_data);

	stream->ctx = dc_sink_data->ctx;
	stream->link = dc_sink_data->link;
	stream->sink_patches = dc_sink_data->edid_caps.panel_patch;
	stream->converter_disable_audio = dc_sink_data->converter_disable_audio;
	stream->qs_bit = dc_sink_data->edid_caps.qs_bit;
	stream->qy_bit = dc_sink_data->edid_caps.qy_bit;

	/* Copy audio modes */
	/* TODO - Remove this translation */
	क्रम (i = 0; i < (dc_sink_data->edid_caps.audio_mode_count); i++)
	अणु
		stream->audio_info.modes[i].channel_count = dc_sink_data->edid_caps.audio_modes[i].channel_count;
		stream->audio_info.modes[i].क्रमmat_code = dc_sink_data->edid_caps.audio_modes[i].क्रमmat_code;
		stream->audio_info.modes[i].sample_rates.all = dc_sink_data->edid_caps.audio_modes[i].sample_rate;
		stream->audio_info.modes[i].sample_size = dc_sink_data->edid_caps.audio_modes[i].sample_size;
	पूर्ण
	stream->audio_info.mode_count = dc_sink_data->edid_caps.audio_mode_count;
	stream->audio_info.audio_latency = dc_sink_data->edid_caps.audio_latency;
	stream->audio_info.video_latency = dc_sink_data->edid_caps.video_latency;
	स_हटाओ(
		stream->audio_info.display_name,
		dc_sink_data->edid_caps.display_name,
		AUDIO_INFO_DISPLAY_NAME_SIZE_IN_CHARS);
	stream->audio_info.manufacture_id = dc_sink_data->edid_caps.manufacturer_id;
	stream->audio_info.product_id = dc_sink_data->edid_caps.product_id;
	stream->audio_info.flags.all = dc_sink_data->edid_caps.speaker_flags;

	अगर (dc_sink_data->dc_container_id != शून्य) अणु
		काष्ठा dc_container_id *dc_container_id = dc_sink_data->dc_container_id;

		stream->audio_info.port_id[0] = dc_container_id->portId[0];
		stream->audio_info.port_id[1] = dc_container_id->portId[1];
	पूर्ण अन्यथा अणु
		/* TODO - WinकरोwDM has implemented,
		other DMs need Unhardcode port_id */
		stream->audio_info.port_id[0] = 0x5558859e;
		stream->audio_info.port_id[1] = 0xd989449;
	पूर्ण

	/* EDID CAP translation क्रम HDMI 2.0 */
	stream->timing.flags.LTE_340MCSC_SCRAMBLE = dc_sink_data->edid_caps.lte_340mcsc_scramble;

	स_रखो(&stream->timing.dsc_cfg, 0, माप(stream->timing.dsc_cfg));
	stream->timing.dsc_cfg.num_slices_h = 0;
	stream->timing.dsc_cfg.num_slices_v = 0;
	stream->timing.dsc_cfg.bits_per_pixel = 128;
	stream->timing.dsc_cfg.block_pred_enable = 1;
	stream->timing.dsc_cfg.linebuf_depth = 9;
	stream->timing.dsc_cfg.version_minor = 2;
	stream->timing.dsc_cfg.ycbcr422_simple = 0;

	update_stream_संकेत(stream, dc_sink_data);

	stream->out_transfer_func = dc_create_transfer_func();
	अगर (stream->out_transfer_func == शून्य) अणु
		dc_sink_release(dc_sink_data);
		वापस false;
	पूर्ण
	stream->out_transfer_func->type = TF_TYPE_BYPASS;

	stream->stream_id = stream->ctx->dc_stream_id_count;
	stream->ctx->dc_stream_id_count++;

	वापस true;
पूर्ण

अटल व्योम dc_stream_deकाष्ठा(काष्ठा dc_stream_state *stream)
अणु
	dc_sink_release(stream->sink);
	अगर (stream->out_transfer_func != शून्य) अणु
		dc_transfer_func_release(stream->out_transfer_func);
		stream->out_transfer_func = शून्य;
	पूर्ण
पूर्ण

व्योम dc_stream_retain(काष्ठा dc_stream_state *stream)
अणु
	kref_get(&stream->refcount);
पूर्ण

अटल व्योम dc_stream_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा dc_stream_state *stream = container_of(kref, काष्ठा dc_stream_state, refcount);

	dc_stream_deकाष्ठा(stream);
	kमुक्त(stream);
पूर्ण

व्योम dc_stream_release(काष्ठा dc_stream_state *stream)
अणु
	अगर (stream != शून्य) अणु
		kref_put(&stream->refcount, dc_stream_मुक्त);
	पूर्ण
पूर्ण

काष्ठा dc_stream_state *dc_create_stream_क्रम_sink(
		काष्ठा dc_sink *sink)
अणु
	काष्ठा dc_stream_state *stream;

	अगर (sink == शून्य)
		वापस शून्य;

	stream = kzalloc(माप(काष्ठा dc_stream_state), GFP_KERNEL);
	अगर (stream == शून्य)
		जाओ alloc_fail;

	अगर (dc_stream_स्थिरruct(stream, sink) == false)
		जाओ स्थिरruct_fail;

	kref_init(&stream->refcount);

	वापस stream;

स्थिरruct_fail:
	kमुक्त(stream);

alloc_fail:
	वापस शून्य;
पूर्ण

काष्ठा dc_stream_state *dc_copy_stream(स्थिर काष्ठा dc_stream_state *stream)
अणु
	काष्ठा dc_stream_state *new_stream;

	new_stream = kmemdup(stream, माप(काष्ठा dc_stream_state), GFP_KERNEL);
	अगर (!new_stream)
		वापस शून्य;

	अगर (new_stream->sink)
		dc_sink_retain(new_stream->sink);

	अगर (new_stream->out_transfer_func)
		dc_transfer_func_retain(new_stream->out_transfer_func);

	new_stream->stream_id = new_stream->ctx->dc_stream_id_count;
	new_stream->ctx->dc_stream_id_count++;

	kref_init(&new_stream->refcount);

	वापस new_stream;
पूर्ण

/**
 * dc_stream_get_status_from_state - Get stream status from given dc state
 * @state: DC state to find the stream status in
 * @stream: The stream to get the stream status क्रम
 *
 * The given stream is expected to exist in the given dc state. Otherwise, शून्य
 * will be वापसed.
 */
काष्ठा dc_stream_status *dc_stream_get_status_from_state(
	काष्ठा dc_state *state,
	काष्ठा dc_stream_state *stream)
अणु
	uपूर्णांक8_t i;

	क्रम (i = 0; i < state->stream_count; i++) अणु
		अगर (stream == state->streams[i])
			वापस &state->stream_status[i];
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * dc_stream_get_status() - Get current stream status of the given stream state
 * @stream: The stream to get the stream status क्रम.
 *
 * The given stream is expected to exist in dc->current_state. Otherwise, शून्य
 * will be वापसed.
 */
काष्ठा dc_stream_status *dc_stream_get_status(
	काष्ठा dc_stream_state *stream)
अणु
	काष्ठा dc *dc = stream->ctx->dc;
	वापस dc_stream_get_status_from_state(dc->current_state, stream);
पूर्ण

#अगर_अघोषित TRIM_FSFT
/*
 * dc_optimize_timing_क्रम_fsft() - dc to optimize timing
 */
bool dc_optimize_timing_क्रम_fsft(
	काष्ठा dc_stream_state *pStream,
	अचिन्हित पूर्णांक max_input_rate_in_khz)
अणु
	काष्ठा dc  *dc;

	dc = pStream->ctx->dc;

	वापस (dc->hwss.optimize_timing_क्रम_fsft &&
		dc->hwss.optimize_timing_क्रम_fsft(dc, &pStream->timing, max_input_rate_in_khz));
पूर्ण
#पूर्ण_अगर

/*
 * dc_stream_set_cursor_attributes() - Update cursor attributes and set cursor surface address
 */
bool dc_stream_set_cursor_attributes(
	काष्ठा dc_stream_state *stream,
	स्थिर काष्ठा dc_cursor_attributes *attributes)
अणु
	पूर्णांक i;
	काष्ठा dc  *dc;
	काष्ठा resource_context *res_ctx;
	काष्ठा pipe_ctx *pipe_to_program = शून्य;
#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	bool reset_idle_optimizations = false;
#पूर्ण_अगर

	अगर (शून्य == stream) अणु
		dm_error("DC: dc_stream is NULL!\n");
		वापस false;
	पूर्ण
	अगर (शून्य == attributes) अणु
		dm_error("DC: attributes is NULL!\n");
		वापस false;
	पूर्ण

	अगर (attributes->address.quad_part == 0) अणु
		dm_output_to_console("DC: Cursor address is 0!\n");
		वापस false;
	पूर्ण

	dc = stream->ctx->dc;
	res_ctx = &dc->current_state->res_ctx;
	stream->cursor_attributes = *attributes;

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	/* disable idle optimizations जबतक updating cursor */
	अगर (dc->idle_optimizations_allowed) अणु
		dc_allow_idle_optimizations(dc, false);
		reset_idle_optimizations = true;
	पूर्ण

#पूर्ण_अगर

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		काष्ठा pipe_ctx *pipe_ctx = &res_ctx->pipe_ctx[i];

		अगर (pipe_ctx->stream != stream)
			जारी;

		अगर (!pipe_to_program) अणु
			pipe_to_program = pipe_ctx;
			dc->hwss.cursor_lock(dc, pipe_to_program, true);
		पूर्ण

		dc->hwss.set_cursor_attribute(pipe_ctx);
		अगर (dc->hwss.set_cursor_sdr_white_level)
			dc->hwss.set_cursor_sdr_white_level(pipe_ctx);
	पूर्ण

	अगर (pipe_to_program)
		dc->hwss.cursor_lock(dc, pipe_to_program, false);

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	/* re-enable idle optimizations अगर necessary */
	अगर (reset_idle_optimizations)
		dc_allow_idle_optimizations(dc, true);

#पूर्ण_अगर
	वापस true;
पूर्ण

bool dc_stream_set_cursor_position(
	काष्ठा dc_stream_state *stream,
	स्थिर काष्ठा dc_cursor_position *position)
अणु
	पूर्णांक i;
	काष्ठा dc  *dc;
	काष्ठा resource_context *res_ctx;
	काष्ठा pipe_ctx *pipe_to_program = शून्य;
#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	bool reset_idle_optimizations = false;
#पूर्ण_अगर

	अगर (शून्य == stream) अणु
		dm_error("DC: dc_stream is NULL!\n");
		वापस false;
	पूर्ण

	अगर (शून्य == position) अणु
		dm_error("DC: cursor position is NULL!\n");
		वापस false;
	पूर्ण

	dc = stream->ctx->dc;
	res_ctx = &dc->current_state->res_ctx;
#अगर defined(CONFIG_DRM_AMD_DC_DCN)

	/* disable idle optimizations अगर enabling cursor */
	अगर (dc->idle_optimizations_allowed && !stream->cursor_position.enable && position->enable) अणु
		dc_allow_idle_optimizations(dc, false);
		reset_idle_optimizations = true;
	पूर्ण

#पूर्ण_अगर
	stream->cursor_position = *position;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		काष्ठा pipe_ctx *pipe_ctx = &res_ctx->pipe_ctx[i];

		अगर (pipe_ctx->stream != stream ||
				(!pipe_ctx->plane_res.mi  && !pipe_ctx->plane_res.hubp) ||
				!pipe_ctx->plane_state ||
				(!pipe_ctx->plane_res.xfm && !pipe_ctx->plane_res.dpp) ||
				(!pipe_ctx->plane_res.ipp && !pipe_ctx->plane_res.dpp))
			जारी;

		अगर (!pipe_to_program) अणु
			pipe_to_program = pipe_ctx;
			dc->hwss.cursor_lock(dc, pipe_to_program, true);
		पूर्ण

		dc->hwss.set_cursor_position(pipe_ctx);
	पूर्ण

	अगर (pipe_to_program)
		dc->hwss.cursor_lock(dc, pipe_to_program, false);

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	/* re-enable idle optimizations अगर necessary */
	अगर (reset_idle_optimizations)
		dc_allow_idle_optimizations(dc, true);

#पूर्ण_अगर
	वापस true;
पूर्ण

bool dc_stream_add_ग_लिखोback(काष्ठा dc *dc,
		काष्ठा dc_stream_state *stream,
		काष्ठा dc_ग_लिखोback_info *wb_info)
अणु
	bool isDrc = false;
	पूर्णांक i = 0;
	काष्ठा dwbc *dwb;

	अगर (stream == शून्य) अणु
		dm_error("DC: dc_stream is NULL!\n");
		वापस false;
	पूर्ण

	अगर (wb_info == शून्य) अणु
		dm_error("DC: dc_writeback_info is NULL!\n");
		वापस false;
	पूर्ण

	अगर (wb_info->dwb_pipe_inst >= MAX_DWB_PIPES) अणु
		dm_error("DC: writeback pipe is invalid!\n");
		वापस false;
	पूर्ण

	wb_info->dwb_params.out_transfer_func = stream->out_transfer_func;

	dwb = dc->res_pool->dwbc[wb_info->dwb_pipe_inst];
	dwb->dwb_is_drc = false;

	/* recalculate and apply DML parameters */

	क्रम (i = 0; i < stream->num_wb_info; i++) अणु
		/*dynamic update*/
		अगर (stream->ग_लिखोback_info[i].wb_enabled &&
			stream->ग_लिखोback_info[i].dwb_pipe_inst == wb_info->dwb_pipe_inst) अणु
			stream->ग_लिखोback_info[i] = *wb_info;
			isDrc = true;
		पूर्ण
	पूर्ण

	अगर (!isDrc) अणु
		stream->ग_लिखोback_info[stream->num_wb_info++] = *wb_info;
	पूर्ण

	अगर (dc->hwss.enable_ग_लिखोback) अणु
		काष्ठा dc_stream_status *stream_status = dc_stream_get_status(stream);
		काष्ठा dwbc *dwb = dc->res_pool->dwbc[wb_info->dwb_pipe_inst];
		dwb->otg_inst = stream_status->primary_otg_inst;
	पूर्ण
	अगर (IS_DIAG_DC(dc->ctx->dce_environment)) अणु
		अगर (!dc->hwss.update_bandwidth(dc, dc->current_state)) अणु
			dm_error("DC: update_bandwidth failed!\n");
			वापस false;
		पूर्ण

		/* enable ग_लिखोback */
		अगर (dc->hwss.enable_ग_लिखोback) अणु
			काष्ठा dwbc *dwb = dc->res_pool->dwbc[wb_info->dwb_pipe_inst];

			अगर (dwb->funcs->is_enabled(dwb)) अणु
				/* ग_लिखोback pipe alपढ़ोy enabled, only need to update */
				dc->hwss.update_ग_लिखोback(dc, wb_info, dc->current_state);
			पूर्ण अन्यथा अणु
				/* Enable ग_लिखोback pipe from scratch*/
				dc->hwss.enable_ग_लिखोback(dc, wb_info, dc->current_state);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

bool dc_stream_हटाओ_ग_लिखोback(काष्ठा dc *dc,
		काष्ठा dc_stream_state *stream,
		uपूर्णांक32_t dwb_pipe_inst)
अणु
	पूर्णांक i = 0, j = 0;
	अगर (stream == शून्य) अणु
		dm_error("DC: dc_stream is NULL!\n");
		वापस false;
	पूर्ण

	अगर (dwb_pipe_inst >= MAX_DWB_PIPES) अणु
		dm_error("DC: writeback pipe is invalid!\n");
		वापस false;
	पूर्ण

//	stream->ग_लिखोback_info[dwb_pipe_inst].wb_enabled = false;
	क्रम (i = 0; i < stream->num_wb_info; i++) अणु
		/*dynamic update*/
		अगर (stream->ग_लिखोback_info[i].wb_enabled &&
			stream->ग_लिखोback_info[i].dwb_pipe_inst == dwb_pipe_inst) अणु
			stream->ग_लिखोback_info[i].wb_enabled = false;
		पूर्ण
	पूर्ण

	/* हटाओ ग_लिखोback info क्रम disabled ग_लिखोback pipes from stream */
	क्रम (i = 0, j = 0; i < stream->num_wb_info; i++) अणु
		अगर (stream->ग_लिखोback_info[i].wb_enabled) अणु
			अगर (i != j)
				/* trim the array */
				stream->ग_लिखोback_info[j] = stream->ग_लिखोback_info[i];
			j++;
		पूर्ण
	पूर्ण
	stream->num_wb_info = j;

	अगर (IS_DIAG_DC(dc->ctx->dce_environment)) अणु
		/* recalculate and apply DML parameters */
		अगर (!dc->hwss.update_bandwidth(dc, dc->current_state)) अणु
			dm_error("DC: update_bandwidth failed!\n");
			वापस false;
		पूर्ण

		/* disable ग_लिखोback */
		अगर (dc->hwss.disable_ग_लिखोback)
			dc->hwss.disable_ग_लिखोback(dc, dwb_pipe_inst);
	पूर्ण
	वापस true;
पूर्ण

bool dc_stream_warmup_ग_लिखोback(काष्ठा dc *dc,
		पूर्णांक num_dwb,
		काष्ठा dc_ग_लिखोback_info *wb_info)
अणु
	अगर (dc->hwss.mmhubbub_warmup)
		वापस dc->hwss.mmhubbub_warmup(dc, num_dwb, wb_info);
	अन्यथा
		वापस false;
पूर्ण
uपूर्णांक32_t dc_stream_get_vblank_counter(स्थिर काष्ठा dc_stream_state *stream)
अणु
	uपूर्णांक8_t i;
	काष्ठा dc  *dc = stream->ctx->dc;
	काष्ठा resource_context *res_ctx =
		&dc->current_state->res_ctx;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		काष्ठा timing_generator *tg = res_ctx->pipe_ctx[i].stream_res.tg;

		अगर (res_ctx->pipe_ctx[i].stream != stream)
			जारी;

		वापस tg->funcs->get_frame_count(tg);
	पूर्ण

	वापस 0;
पूर्ण

bool dc_stream_send_dp_sdp(स्थिर काष्ठा dc_stream_state *stream,
		स्थिर uपूर्णांक8_t *custom_sdp_message,
		अचिन्हित पूर्णांक sdp_message_size)
अणु
	पूर्णांक i;
	काष्ठा dc  *dc;
	काष्ठा resource_context *res_ctx;

	अगर (stream == शून्य) अणु
		dm_error("DC: dc_stream is NULL!\n");
		वापस false;
	पूर्ण

	dc = stream->ctx->dc;
	res_ctx = &dc->current_state->res_ctx;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		काष्ठा pipe_ctx *pipe_ctx = &res_ctx->pipe_ctx[i];

		अगर (pipe_ctx->stream != stream)
			जारी;

		अगर (dc->hwss.send_immediate_sdp_message != शून्य)
			dc->hwss.send_immediate_sdp_message(pipe_ctx,
								custom_sdp_message,
								sdp_message_size);
		अन्यथा
			DC_LOG_WARNING("%s:send_immediate_sdp_message not implemented on this ASIC\n",
			__func__);

	पूर्ण

	वापस true;
पूर्ण

bool dc_stream_get_scanoutpos(स्थिर काष्ठा dc_stream_state *stream,
				  uपूर्णांक32_t *v_blank_start,
				  uपूर्णांक32_t *v_blank_end,
				  uपूर्णांक32_t *h_position,
				  uपूर्णांक32_t *v_position)
अणु
	uपूर्णांक8_t i;
	bool ret = false;
	काष्ठा dc  *dc = stream->ctx->dc;
	काष्ठा resource_context *res_ctx =
		&dc->current_state->res_ctx;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		काष्ठा timing_generator *tg = res_ctx->pipe_ctx[i].stream_res.tg;

		अगर (res_ctx->pipe_ctx[i].stream != stream)
			जारी;

		tg->funcs->get_scanoutpos(tg,
					  v_blank_start,
					  v_blank_end,
					  h_position,
					  v_position);

		ret = true;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

bool dc_stream_dmdata_status_करोne(काष्ठा dc *dc, काष्ठा dc_stream_state *stream)
अणु
	काष्ठा pipe_ctx *pipe = शून्य;
	पूर्णांक i;

	अगर (!dc->hwss.dmdata_status_करोne)
		वापस false;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		pipe = &dc->current_state->res_ctx.pipe_ctx[i];
		अगर (pipe->stream == stream)
			अवरोध;
	पूर्ण
	/* Stream not found, by शेष we'll assume HUBP fetched dm data */
	अगर (i == MAX_PIPES)
		वापस true;

	वापस dc->hwss.dmdata_status_करोne(pipe);
पूर्ण

bool dc_stream_set_dynamic_metadata(काष्ठा dc *dc,
		काष्ठा dc_stream_state *stream,
		काष्ठा dc_dmdata_attributes *attr)
अणु
	काष्ठा pipe_ctx *pipe_ctx = शून्य;
	काष्ठा hubp *hubp;
	पूर्णांक i;

	/* Dynamic metadata is only supported on HDMI or DP */
	अगर (!dc_is_hdmi_संकेत(stream->संकेत) && !dc_is_dp_संकेत(stream->संकेत))
		वापस false;

	/* Check hardware support */
	अगर (!dc->hwss.program_dmdata_engine)
		वापस false;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		pipe_ctx = &dc->current_state->res_ctx.pipe_ctx[i];
		अगर (pipe_ctx->stream == stream)
			अवरोध;
	पूर्ण

	अगर (i == MAX_PIPES)
		वापस false;

	hubp = pipe_ctx->plane_res.hubp;
	अगर (hubp == शून्य)
		वापस false;

	pipe_ctx->stream->dmdata_address = attr->address;

	dc->hwss.program_dmdata_engine(pipe_ctx);

	अगर (hubp->funcs->dmdata_set_attributes != शून्य &&
			pipe_ctx->stream->dmdata_address.quad_part != 0) अणु
		hubp->funcs->dmdata_set_attributes(hubp, attr);
	पूर्ण

	वापस true;
पूर्ण

क्रमागत dc_status dc_stream_add_dsc_to_resource(काष्ठा dc *dc,
		काष्ठा dc_state *state,
		काष्ठा dc_stream_state *stream)
अणु
	अगर (dc->res_pool->funcs->add_dsc_to_stream_resource) अणु
		वापस dc->res_pool->funcs->add_dsc_to_stream_resource(dc, state, stream);
	पूर्ण अन्यथा अणु
		वापस DC_NO_DSC_RESOURCE;
	पूर्ण
पूर्ण

व्योम dc_stream_log(स्थिर काष्ठा dc *dc, स्थिर काष्ठा dc_stream_state *stream)
अणु
	DC_LOG_DC(
			"core_stream 0x%p: src: %d, %d, %d, %d; dst: %d, %d, %d, %d, colorSpace:%d\n",
			stream,
			stream->src.x,
			stream->src.y,
			stream->src.width,
			stream->src.height,
			stream->dst.x,
			stream->dst.y,
			stream->dst.width,
			stream->dst.height,
			stream->output_color_space);
	DC_LOG_DC(
			"\tpix_clk_khz: %d, h_total: %d, v_total: %d, pixelencoder:%d, displaycolorDepth:%d\n",
			stream->timing.pix_clk_100hz / 10,
			stream->timing.h_total,
			stream->timing.v_total,
			stream->timing.pixel_encoding,
			stream->timing.display_color_depth);
	DC_LOG_DC(
			"\tlink: %d\n",
			stream->link->link_index);
पूर्ण

