<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
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
 */

#समावेश <linux/slab.h>
#समावेश <linux/mm.h>

#समावेश "dm_services.h"

#समावेश "dc.h"

#समावेश "core_status.h"
#समावेश "core_types.h"
#समावेश "hw_sequencer.h"
#समावेश "dce/dce_hwseq.h"

#समावेश "resource.h"

#समावेश "clk_mgr.h"
#समावेश "clock_source.h"
#समावेश "dc_bios_types.h"

#समावेश "bios_parser_interface.h"
#समावेश "bios/bios_parser_helper.h"
#समावेश "include/irq_service_interface.h"
#समावेश "transform.h"
#समावेश "dmcu.h"
#समावेश "dpp.h"
#समावेश "timing_generator.h"
#समावेश "abm.h"
#समावेश "virtual/virtual_link_encoder.h"
#समावेश "hubp.h"

#समावेश "link_hwss.h"
#समावेश "link_encoder.h"
#समावेश "link_enc_cfg.h"

#समावेश "dc_link.h"
#समावेश "dc_link_ddc.h"
#समावेश "dm_helpers.h"
#समावेश "mem_input.h"
#समावेश "hubp.h"

#समावेश "dc_link_dp.h"
#समावेश "dc_dmub_srv.h"

#समावेश "dsc.h"

#समावेश "vm_helper.h"

#समावेश "dce/dce_i2c.h"

#समावेश "dmub/dmub_srv.h"

#समावेश "i2caux_interface.h"
#समावेश "dce/dmub_hw_lock_mgr.h"

#समावेश "dc_trace.h"

#घोषणा CTX \
	dc->ctx

#घोषणा DC_LOGGER \
	dc->ctx->logger

अटल स्थिर अक्षर DC_BUILD_ID[] = "production-build";

/**
 * DOC: Overview
 *
 * DC is the OS-agnostic component of the amdgpu DC driver.
 *
 * DC मुख्यtains and validates a set of काष्ठाs representing the state of the
 * driver and ग_लिखोs that state to AMD hardware
 *
 * Main DC HW काष्ठाs:
 *
 * काष्ठा dc - The central काष्ठा.  One per driver.  Created on driver load,
 * destroyed on driver unload.
 *
 * काष्ठा dc_context - One per driver.
 * Used as a backpoपूर्णांकer by most other काष्ठाs in dc.
 *
 * काष्ठा dc_link - One per connector (the physical DP, HDMI, miniDP, or eDP
 * plugpoपूर्णांकs).  Created on driver load, destroyed on driver unload.
 *
 * काष्ठा dc_sink - One per display.  Created on boot or hotplug.
 * Destroyed on shutकरोwn or hotunplug.  A dc_link can have a local sink
 * (the display directly attached).  It may also have one or more remote
 * sinks (in the Multi-Stream Transport हाल)
 *
 * काष्ठा resource_pool - One per driver.  Represents the hw blocks not in the
 * मुख्य pipeline.  Not directly accessible by dm.
 *
 * Main dc state काष्ठाs:
 *
 * These काष्ठाs can be created and destroyed as needed.  There is a full set of
 * these काष्ठाs in dc->current_state representing the currently programmed state.
 *
 * काष्ठा dc_state - The global DC state to track global state inक्रमmation,
 * such as bandwidth values.
 *
 * काष्ठा dc_stream_state - Represents the hw configuration क्रम the pipeline from
 * a framebuffer to a display.  Maps one-to-one with dc_sink.
 *
 * काष्ठा dc_plane_state - Represents a framebuffer.  Each stream has at least one,
 * and may have more in the Multi-Plane Overlay हाल.
 *
 * काष्ठा resource_context - Represents the programmable state of everything in
 * the resource_pool.  Not directly accessible by dm.
 *
 * काष्ठा pipe_ctx - A member of काष्ठा resource_context.  Represents the
 * पूर्णांकernal hardware pipeline components.  Each dc_plane_state has either
 * one or two (in the pipe-split हाल).
 */

/*******************************************************************************
 * Private functions
 ******************************************************************************/

अटल अंतरभूत व्योम elevate_update_type(क्रमागत surface_update_type *original, क्रमागत surface_update_type new)
अणु
	अगर (new > *original)
		*original = new;
पूर्ण

अटल व्योम destroy_links(काष्ठा dc *dc)
अणु
	uपूर्णांक32_t i;

	क्रम (i = 0; i < dc->link_count; i++) अणु
		अगर (शून्य != dc->links[i])
			link_destroy(&dc->links[i]);
	पूर्ण
पूर्ण

अटल uपूर्णांक32_t get_num_of_पूर्णांकernal_disp(काष्ठा dc_link **links, uपूर्णांक32_t num_links)
अणु
	पूर्णांक i;
	uपूर्णांक32_t count = 0;

	क्रम (i = 0; i < num_links; i++) अणु
		अगर (links[i]->connector_संकेत == SIGNAL_TYPE_EDP ||
				links[i]->is_पूर्णांकernal_display)
			count++;
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक get_seamless_boot_stream_count(काष्ठा dc_state *ctx)
अणु
	uपूर्णांक8_t i;
	uपूर्णांक8_t seamless_boot_stream_count = 0;

	क्रम (i = 0; i < ctx->stream_count; i++)
		अगर (ctx->streams[i]->apply_seamless_boot_optimization)
			seamless_boot_stream_count++;

	वापस seamless_boot_stream_count;
पूर्ण

अटल bool create_links(
		काष्ठा dc *dc,
		uपूर्णांक32_t num_भव_links)
अणु
	पूर्णांक i;
	पूर्णांक connectors_num;
	काष्ठा dc_bios *bios = dc->ctx->dc_bios;

	dc->link_count = 0;

	connectors_num = bios->funcs->get_connectors_number(bios);

	DC_LOG_DC("BIOS object table - number of connectors: %d", connectors_num);

	अगर (connectors_num > ENUM_ID_COUNT) अणु
		dm_error(
			"DC: Number of connectors %d exceeds maximum of %d!\n",
			connectors_num,
			ENUM_ID_COUNT);
		वापस false;
	पूर्ण

	dm_output_to_console(
		"DC: %s: connectors_num: physical:%d, virtual:%d\n",
		__func__,
		connectors_num,
		num_भव_links);

	क्रम (i = 0; i < connectors_num; i++) अणु
		काष्ठा link_init_data link_init_params = अणु0पूर्ण;
		काष्ठा dc_link *link;

		DC_LOG_DC("BIOS object table - printing link object info for connector number: %d, link_index: %d", i, dc->link_count);

		link_init_params.ctx = dc->ctx;
		/* next BIOS object table connector */
		link_init_params.connector_index = i;
		link_init_params.link_index = dc->link_count;
		link_init_params.dc = dc;
		link = link_create(&link_init_params);

		अगर (link) अणु
				dc->links[dc->link_count] = link;
				link->dc = dc;
				++dc->link_count;
		पूर्ण
	पूर्ण

	DC_LOG_DC("BIOS object table - end");

	क्रम (i = 0; i < num_भव_links; i++) अणु
		काष्ठा dc_link *link = kzalloc(माप(*link), GFP_KERNEL);
		काष्ठा encoder_init_data enc_init = अणु0पूर्ण;

		अगर (link == शून्य) अणु
			BREAK_TO_DEBUGGER();
			जाओ failed_alloc;
		पूर्ण

		link->link_index = dc->link_count;
		dc->links[dc->link_count] = link;
		dc->link_count++;

		link->ctx = dc->ctx;
		link->dc = dc;
		link->connector_संकेत = SIGNAL_TYPE_VIRTUAL;
		link->link_id.type = OBJECT_TYPE_CONNECTOR;
		link->link_id.id = CONNECTOR_ID_VIRTUAL;
		link->link_id.क्रमागत_id = ENUM_ID_1;
		link->link_enc = kzalloc(माप(*link->link_enc), GFP_KERNEL);

		अगर (!link->link_enc) अणु
			BREAK_TO_DEBUGGER();
			जाओ failed_alloc;
		पूर्ण

		link->link_status.dpcd_caps = &link->dpcd_caps;

		enc_init.ctx = dc->ctx;
		enc_init.channel = CHANNEL_ID_UNKNOWN;
		enc_init.hpd_source = HPD_SOURCEID_UNKNOWN;
		enc_init.transmitter = TRANSMITTER_UNKNOWN;
		enc_init.connector = link->link_id;
		enc_init.encoder.type = OBJECT_TYPE_ENCODER;
		enc_init.encoder.id = ENCODER_ID_INTERNAL_VIRTUAL;
		enc_init.encoder.क्रमागत_id = ENUM_ID_1;
		भव_link_encoder_स्थिरruct(link->link_enc, &enc_init);
	पूर्ण

	dc->caps.num_of_पूर्णांकernal_disp = get_num_of_पूर्णांकernal_disp(dc->links, dc->link_count);

	वापस true;

failed_alloc:
	वापस false;
पूर्ण

अटल काष्ठा dc_perf_trace *dc_perf_trace_create(व्योम)
अणु
	वापस kzalloc(माप(काष्ठा dc_perf_trace), GFP_KERNEL);
पूर्ण

अटल व्योम dc_perf_trace_destroy(काष्ठा dc_perf_trace **perf_trace)
अणु
	kमुक्त(*perf_trace);
	*perf_trace = शून्य;
पूर्ण

/**
 *  dc_stream_adjust_vmin_vmax:
 *
 *  Looks up the pipe context of dc_stream_state and updates the
 *  vertical_total_min and vertical_total_max of the DRR, Dynamic Refresh
 *  Rate, which is a घातer-saving feature that tarमाला_लो reducing panel
 *  refresh rate जबतक the screen is अटल
 *
 *  @dc:     dc reference
 *  @stream: Initial dc stream state
 *  @adjust: Updated parameters क्रम vertical_total_min and vertical_total_max
 */
bool dc_stream_adjust_vmin_vmax(काष्ठा dc *dc,
		काष्ठा dc_stream_state *stream,
		काष्ठा dc_crtc_timing_adjust *adjust)
अणु
	पूर्णांक i = 0;
	bool ret = false;

	stream->adjust.v_total_max = adjust->v_total_max;
	stream->adjust.v_total_mid = adjust->v_total_mid;
	stream->adjust.v_total_mid_frame_num = adjust->v_total_mid_frame_num;
	stream->adjust.v_total_min = adjust->v_total_min;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		काष्ठा pipe_ctx *pipe = &dc->current_state->res_ctx.pipe_ctx[i];

		अगर (pipe->stream == stream && pipe->stream_res.tg) अणु
			dc->hwss.set_drr(&pipe,
					1,
					*adjust);

			ret = true;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

bool dc_stream_get_crtc_position(काष्ठा dc *dc,
		काष्ठा dc_stream_state **streams, पूर्णांक num_streams,
		अचिन्हित पूर्णांक *v_pos, अचिन्हित पूर्णांक *nom_v_pos)
अणु
	/* TODO: Support multiple streams */
	स्थिर काष्ठा dc_stream_state *stream = streams[0];
	पूर्णांक i = 0;
	bool ret = false;
	काष्ठा crtc_position position;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		काष्ठा pipe_ctx *pipe =
				&dc->current_state->res_ctx.pipe_ctx[i];

		अगर (pipe->stream == stream && pipe->stream_res.stream_enc) अणु
			dc->hwss.get_position(&pipe, 1, &position);

			*v_pos = position.vertical_count;
			*nom_v_pos = position.nominal_vcount;
			ret = true;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

#अगर defined(CONFIG_DRM_AMD_SECURE_DISPLAY)
bool dc_stream_क्रमward_dmcu_crc_winकरोw(काष्ठा dc *dc, काष्ठा dc_stream_state *stream,
			     काष्ठा crc_params *crc_winकरोw)
अणु
	पूर्णांक i;
	काष्ठा dmcu *dmcu = dc->res_pool->dmcu;
	काष्ठा pipe_ctx *pipe;
	काष्ठा crc_region पंचांगp_win, *crc_win;
	काष्ठा otg_phy_mux mapping_पंचांगp, *mux_mapping;

	/*crc winकरोw can't be null*/
	अगर (!crc_winकरोw)
		वापस false;

	अगर ((dmcu != शून्य && dmcu->funcs->is_dmcu_initialized(dmcu))) अणु
		crc_win = &पंचांगp_win;
		mux_mapping = &mapping_पंचांगp;
		/*set crc winकरोw*/
		पंचांगp_win.x_start = crc_winकरोw->winकरोwa_x_start;
		पंचांगp_win.y_start = crc_winकरोw->winकरोwa_y_start;
		पंचांगp_win.x_end = crc_winकरोw->winकरोwa_x_end;
		पंचांगp_win.y_end = crc_winकरोw->winकरोwa_y_end;

		क्रम (i = 0; i < MAX_PIPES; i++) अणु
			pipe = &dc->current_state->res_ctx.pipe_ctx[i];
			अगर (pipe->stream == stream && !pipe->top_pipe && !pipe->prev_odm_pipe)
				अवरोध;
		पूर्ण

		/* Stream not found */
		अगर (i == MAX_PIPES)
			वापस false;


		/*set mux routing info*/
		mapping_पंचांगp.phy_output_num = stream->link->link_enc_hw_inst;
		mapping_पंचांगp.otg_output_num = pipe->stream_res.tg->inst;

		dmcu->funcs->क्रमward_crc_winकरोw(dmcu, crc_win, mux_mapping);
	पूर्ण अन्यथा अणु
		DC_LOG_DC("dmcu is not initialized");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

bool dc_stream_stop_dmcu_crc_win_update(काष्ठा dc *dc, काष्ठा dc_stream_state *stream)
अणु
	पूर्णांक i;
	काष्ठा dmcu *dmcu = dc->res_pool->dmcu;
	काष्ठा pipe_ctx *pipe;
	काष्ठा otg_phy_mux mapping_पंचांगp, *mux_mapping;

	अगर ((dmcu != शून्य && dmcu->funcs->is_dmcu_initialized(dmcu))) अणु
		mux_mapping = &mapping_पंचांगp;

		क्रम (i = 0; i < MAX_PIPES; i++) अणु
			pipe = &dc->current_state->res_ctx.pipe_ctx[i];
			अगर (pipe->stream == stream && !pipe->top_pipe && !pipe->prev_odm_pipe)
				अवरोध;
		पूर्ण

		/* Stream not found */
		अगर (i == MAX_PIPES)
			वापस false;


		/*set mux routing info*/
		mapping_पंचांगp.phy_output_num = stream->link->link_enc_hw_inst;
		mapping_पंचांगp.otg_output_num = pipe->stream_res.tg->inst;

		dmcu->funcs->stop_crc_win_update(dmcu, mux_mapping);
	पूर्ण अन्यथा अणु
		DC_LOG_DC("dmcu is not initialized");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण
#पूर्ण_अगर

/**
 * dc_stream_configure_crc() - Configure CRC capture क्रम the given stream.
 * @dc: DC Object
 * @stream: The stream to configure CRC on.
 * @enable: Enable CRC अगर true, disable otherwise.
 * @crc_winकरोw: CRC winकरोw (x/y start/end) inक्रमmation
 * @continuous: Capture CRC on every frame अगर true. Otherwise, only capture
 *              once.
 *
 * By शेष, only CRC0 is configured, and the entire frame is used to
 * calculate the crc.
 */
bool dc_stream_configure_crc(काष्ठा dc *dc, काष्ठा dc_stream_state *stream,
			     काष्ठा crc_params *crc_winकरोw, bool enable, bool continuous)
अणु
	पूर्णांक i;
	काष्ठा pipe_ctx *pipe;
	काष्ठा crc_params param;
	काष्ठा timing_generator *tg;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		pipe = &dc->current_state->res_ctx.pipe_ctx[i];
		अगर (pipe->stream == stream && !pipe->top_pipe && !pipe->prev_odm_pipe)
			अवरोध;
	पूर्ण
	/* Stream not found */
	अगर (i == MAX_PIPES)
		वापस false;

	/* By शेष, capture the full frame */
	param.winकरोwa_x_start = 0;
	param.winकरोwa_y_start = 0;
	param.winकरोwa_x_end = pipe->stream->timing.h_addressable;
	param.winकरोwa_y_end = pipe->stream->timing.v_addressable;
	param.winकरोwb_x_start = 0;
	param.winकरोwb_y_start = 0;
	param.winकरोwb_x_end = pipe->stream->timing.h_addressable;
	param.winकरोwb_y_end = pipe->stream->timing.v_addressable;

	अगर (crc_winकरोw) अणु
		param.winकरोwa_x_start = crc_winकरोw->winकरोwa_x_start;
		param.winकरोwa_y_start = crc_winकरोw->winकरोwa_y_start;
		param.winकरोwa_x_end = crc_winकरोw->winकरोwa_x_end;
		param.winकरोwa_y_end = crc_winकरोw->winकरोwa_y_end;
		param.winकरोwb_x_start = crc_winकरोw->winकरोwb_x_start;
		param.winकरोwb_y_start = crc_winकरोw->winकरोwb_y_start;
		param.winकरोwb_x_end = crc_winकरोw->winकरोwb_x_end;
		param.winकरोwb_y_end = crc_winकरोw->winकरोwb_y_end;
	पूर्ण

	param.dsc_mode = pipe->stream->timing.flags.DSC ? 1:0;
	param.odm_mode = pipe->next_odm_pipe ? 1:0;

	/* Default to the जोड़ of both winकरोws */
	param.selection = UNION_WINDOW_A_B;
	param.continuous_mode = continuous;
	param.enable = enable;

	tg = pipe->stream_res.tg;

	/* Only call अगर supported */
	अगर (tg->funcs->configure_crc)
		वापस tg->funcs->configure_crc(tg, &param);
	DC_LOG_WARNING("CRC capture not supported.");
	वापस false;
पूर्ण

/**
 * dc_stream_get_crc() - Get CRC values क्रम the given stream.
 * @dc: DC object
 * @stream: The DC stream state of the stream to get CRCs from.
 * @r_cr: CRC value क्रम the first of the 3 channels stored here.
 * @g_y:  CRC value क्रम the second of the 3 channels stored here.
 * @b_cb: CRC value क्रम the third of the 3 channels stored here.
 *
 * dc_stream_configure_crc needs to be called beक्रमehand to enable CRCs.
 * Return false अगर stream is not found, or अगर CRCs are not enabled.
 */
bool dc_stream_get_crc(काष्ठा dc *dc, काष्ठा dc_stream_state *stream,
		       uपूर्णांक32_t *r_cr, uपूर्णांक32_t *g_y, uपूर्णांक32_t *b_cb)
अणु
	पूर्णांक i;
	काष्ठा pipe_ctx *pipe;
	काष्ठा timing_generator *tg;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		pipe = &dc->current_state->res_ctx.pipe_ctx[i];
		अगर (pipe->stream == stream)
			अवरोध;
	पूर्ण
	/* Stream not found */
	अगर (i == MAX_PIPES)
		वापस false;

	tg = pipe->stream_res.tg;

	अगर (tg->funcs->get_crc)
		वापस tg->funcs->get_crc(tg, r_cr, g_y, b_cb);
	DC_LOG_WARNING("CRC capture not supported.");
	वापस false;
पूर्ण

व्योम dc_stream_set_dyn_expansion(काष्ठा dc *dc, काष्ठा dc_stream_state *stream,
		क्रमागत dc_dynamic_expansion option)
अणु
	/* OPP FMT dyn expansion updates*/
	पूर्णांक i = 0;
	काष्ठा pipe_ctx *pipe_ctx;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		अगर (dc->current_state->res_ctx.pipe_ctx[i].stream
				== stream) अणु
			pipe_ctx = &dc->current_state->res_ctx.pipe_ctx[i];
			pipe_ctx->stream_res.opp->dyn_expansion = option;
			pipe_ctx->stream_res.opp->funcs->opp_set_dyn_expansion(
					pipe_ctx->stream_res.opp,
					COLOR_SPACE_YCBCR601,
					stream->timing.display_color_depth,
					stream->संकेत);
		पूर्ण
	पूर्ण
पूर्ण

व्योम dc_stream_set_dither_option(काष्ठा dc_stream_state *stream,
		क्रमागत dc_dither_option option)
अणु
	काष्ठा bit_depth_reduction_params params;
	काष्ठा dc_link *link = stream->link;
	काष्ठा pipe_ctx *pipes = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		अगर (link->dc->current_state->res_ctx.pipe_ctx[i].stream ==
				stream) अणु
			pipes = &link->dc->current_state->res_ctx.pipe_ctx[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!pipes)
		वापस;
	अगर (option > DITHER_OPTION_MAX)
		वापस;

	stream->dither_option = option;

	स_रखो(&params, 0, माप(params));
	resource_build_bit_depth_reduction_params(stream, &params);
	stream->bit_depth_params = params;

	अगर (pipes->plane_res.xfm &&
	    pipes->plane_res.xfm->funcs->transक्रमm_set_pixel_storage_depth) अणु
		pipes->plane_res.xfm->funcs->transक्रमm_set_pixel_storage_depth(
			pipes->plane_res.xfm,
			pipes->plane_res.scl_data.lb_params.depth,
			&stream->bit_depth_params);
	पूर्ण

	pipes->stream_res.opp->funcs->
		opp_program_bit_depth_reduction(pipes->stream_res.opp, &params);
पूर्ण

bool dc_stream_set_gamut_remap(काष्ठा dc *dc, स्थिर काष्ठा dc_stream_state *stream)
अणु
	पूर्णांक i = 0;
	bool ret = false;
	काष्ठा pipe_ctx *pipes;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		अगर (dc->current_state->res_ctx.pipe_ctx[i].stream == stream) अणु
			pipes = &dc->current_state->res_ctx.pipe_ctx[i];
			dc->hwss.program_gamut_remap(pipes);
			ret = true;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

bool dc_stream_program_csc_matrix(काष्ठा dc *dc, काष्ठा dc_stream_state *stream)
अणु
	पूर्णांक i = 0;
	bool ret = false;
	काष्ठा pipe_ctx *pipes;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		अगर (dc->current_state->res_ctx.pipe_ctx[i].stream
				== stream) अणु

			pipes = &dc->current_state->res_ctx.pipe_ctx[i];
			dc->hwss.program_output_csc(dc,
					pipes,
					stream->output_color_space,
					stream->csc_color_matrix.matrix,
					pipes->stream_res.opp->inst);
			ret = true;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

व्योम dc_stream_set_अटल_screen_params(काष्ठा dc *dc,
		काष्ठा dc_stream_state **streams,
		पूर्णांक num_streams,
		स्थिर काष्ठा dc_अटल_screen_params *params)
अणु
	पूर्णांक i = 0;
	पूर्णांक j = 0;
	काष्ठा pipe_ctx *pipes_affected[MAX_PIPES];
	पूर्णांक num_pipes_affected = 0;

	क्रम (i = 0; i < num_streams; i++) अणु
		काष्ठा dc_stream_state *stream = streams[i];

		क्रम (j = 0; j < MAX_PIPES; j++) अणु
			अगर (dc->current_state->res_ctx.pipe_ctx[j].stream
					== stream) अणु
				pipes_affected[num_pipes_affected++] =
						&dc->current_state->res_ctx.pipe_ctx[j];
			पूर्ण
		पूर्ण
	पूर्ण

	dc->hwss.set_अटल_screen_control(pipes_affected, num_pipes_affected, params);
पूर्ण

अटल व्योम dc_deकाष्ठा(काष्ठा dc *dc)
अणु
	अगर (dc->current_state) अणु
		dc_release_state(dc->current_state);
		dc->current_state = शून्य;
	पूर्ण

	destroy_links(dc);

	अगर (dc->clk_mgr) अणु
		dc_destroy_clk_mgr(dc->clk_mgr);
		dc->clk_mgr = शून्य;
	पूर्ण

	dc_destroy_resource_pool(dc);

	अगर (dc->ctx->gpio_service)
		dal_gpio_service_destroy(&dc->ctx->gpio_service);

	अगर (dc->ctx->created_bios)
		dal_bios_parser_destroy(&dc->ctx->dc_bios);

	dc_perf_trace_destroy(&dc->ctx->perf_trace);

	kमुक्त(dc->ctx);
	dc->ctx = शून्य;

	kमुक्त(dc->bw_vbios);
	dc->bw_vbios = शून्य;

	kमुक्त(dc->bw_dceip);
	dc->bw_dceip = शून्य;

#अगर_घोषित CONFIG_DRM_AMD_DC_DCN
	kमुक्त(dc->dcn_soc);
	dc->dcn_soc = शून्य;

	kमुक्त(dc->dcn_ip);
	dc->dcn_ip = शून्य;

#पूर्ण_अगर
	kमुक्त(dc->vm_helper);
	dc->vm_helper = शून्य;

पूर्ण

अटल bool dc_स्थिरruct_ctx(काष्ठा dc *dc,
		स्थिर काष्ठा dc_init_data *init_params)
अणु
	काष्ठा dc_context *dc_ctx;
	क्रमागत dce_version dc_version = DCE_VERSION_UNKNOWN;

	dc_ctx = kzalloc(माप(*dc_ctx), GFP_KERNEL);
	अगर (!dc_ctx)
		वापस false;

	dc_ctx->cgs_device = init_params->cgs_device;
	dc_ctx->driver_context = init_params->driver;
	dc_ctx->dc = dc;
	dc_ctx->asic_id = init_params->asic_id;
	dc_ctx->dc_sink_id_count = 0;
	dc_ctx->dc_stream_id_count = 0;
	dc_ctx->dce_environment = init_params->dce_environment;

	/* Create logger */

	dc_version = resource_parse_asic_id(init_params->asic_id);
	dc_ctx->dce_version = dc_version;

	dc_ctx->perf_trace = dc_perf_trace_create();
	अगर (!dc_ctx->perf_trace) अणु
		ASSERT_CRITICAL(false);
		वापस false;
	पूर्ण

	dc->ctx = dc_ctx;

	वापस true;
पूर्ण

अटल bool dc_स्थिरruct(काष्ठा dc *dc,
		स्थिर काष्ठा dc_init_data *init_params)
अणु
	काष्ठा dc_context *dc_ctx;
	काष्ठा bw_calcs_dceip *dc_dceip;
	काष्ठा bw_calcs_vbios *dc_vbios;
#अगर_घोषित CONFIG_DRM_AMD_DC_DCN
	काष्ठा dcn_soc_bounding_box *dcn_soc;
	काष्ठा dcn_ip_params *dcn_ip;
#पूर्ण_अगर

	dc->config = init_params->flags;

	// Allocate memory क्रम the vm_helper
	dc->vm_helper = kzalloc(माप(काष्ठा vm_helper), GFP_KERNEL);
	अगर (!dc->vm_helper) अणु
		dm_error("%s: failed to create dc->vm_helper\n", __func__);
		जाओ fail;
	पूर्ण

	स_नकल(&dc->bb_overrides, &init_params->bb_overrides, माप(dc->bb_overrides));

	dc_dceip = kzalloc(माप(*dc_dceip), GFP_KERNEL);
	अगर (!dc_dceip) अणु
		dm_error("%s: failed to create dceip\n", __func__);
		जाओ fail;
	पूर्ण

	dc->bw_dceip = dc_dceip;

	dc_vbios = kzalloc(माप(*dc_vbios), GFP_KERNEL);
	अगर (!dc_vbios) अणु
		dm_error("%s: failed to create vbios\n", __func__);
		जाओ fail;
	पूर्ण

	dc->bw_vbios = dc_vbios;
#अगर_घोषित CONFIG_DRM_AMD_DC_DCN
	dcn_soc = kzalloc(माप(*dcn_soc), GFP_KERNEL);
	अगर (!dcn_soc) अणु
		dm_error("%s: failed to create dcn_soc\n", __func__);
		जाओ fail;
	पूर्ण

	dc->dcn_soc = dcn_soc;

	dcn_ip = kzalloc(माप(*dcn_ip), GFP_KERNEL);
	अगर (!dcn_ip) अणु
		dm_error("%s: failed to create dcn_ip\n", __func__);
		जाओ fail;
	पूर्ण

	dc->dcn_ip = dcn_ip;
#पूर्ण_अगर

	अगर (!dc_स्थिरruct_ctx(dc, init_params)) अणु
		dm_error("%s: failed to create ctx\n", __func__);
		जाओ fail;
	पूर्ण

        dc_ctx = dc->ctx;

	/* Resource should स्थिरruct all asic specअगरic resources.
	 * This should be the only place where we need to parse the asic id
	 */
	अगर (init_params->vbios_override)
		dc_ctx->dc_bios = init_params->vbios_override;
	अन्यथा अणु
		/* Create BIOS parser */
		काष्ठा bp_init_data bp_init_data;

		bp_init_data.ctx = dc_ctx;
		bp_init_data.bios = init_params->asic_id.atombios_base_address;

		dc_ctx->dc_bios = dal_bios_parser_create(
				&bp_init_data, dc_ctx->dce_version);

		अगर (!dc_ctx->dc_bios) अणु
			ASSERT_CRITICAL(false);
			जाओ fail;
		पूर्ण

		dc_ctx->created_bios = true;
	पूर्ण

	dc->venकरोr_signature = init_params->venकरोr_signature;

	/* Create GPIO service */
	dc_ctx->gpio_service = dal_gpio_service_create(
			dc_ctx->dce_version,
			dc_ctx->dce_environment,
			dc_ctx);

	अगर (!dc_ctx->gpio_service) अणु
		ASSERT_CRITICAL(false);
		जाओ fail;
	पूर्ण

	dc->res_pool = dc_create_resource_pool(dc, init_params, dc_ctx->dce_version);
	अगर (!dc->res_pool)
		जाओ fail;

	/* set i2c speed अगर not करोne by the respective dcnxxx__resource.c */
	अगर (dc->caps.i2c_speed_in_khz_hdcp == 0)
		dc->caps.i2c_speed_in_khz_hdcp = dc->caps.i2c_speed_in_khz;

	dc->clk_mgr = dc_clk_mgr_create(dc->ctx, dc->res_pool->pp_smu, dc->res_pool->dccg);
	अगर (!dc->clk_mgr)
		जाओ fail;
#अगर_घोषित CONFIG_DRM_AMD_DC_DCN
	dc->clk_mgr->क्रमce_smu_not_present = init_params->क्रमce_smu_not_present;
#पूर्ण_अगर

	अगर (dc->res_pool->funcs->update_bw_bounding_box)
		dc->res_pool->funcs->update_bw_bounding_box(dc, dc->clk_mgr->bw_params);

	/* Creation of current_state must occur after dc->dml
	 * is initialized in dc_create_resource_pool because
	 * on creation it copies the contents of dc->dml
	 */

	dc->current_state = dc_create_state(dc);

	अगर (!dc->current_state) अणु
		dm_error("%s: failed to create validate ctx\n", __func__);
		जाओ fail;
	पूर्ण

	dc_resource_state_स्थिरruct(dc, dc->current_state);

	अगर (!create_links(dc, init_params->num_भव_links))
		जाओ fail;

	/* Initialise DIG link encoder resource tracking variables. */
	link_enc_cfg_init(dc, dc->current_state);

	वापस true;

fail:
	वापस false;
पूर्ण

अटल व्योम disable_all_ग_लिखोback_pipes_क्रम_stream(
		स्थिर काष्ठा dc *dc,
		काष्ठा dc_stream_state *stream,
		काष्ठा dc_state *context)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < stream->num_wb_info; i++)
		stream->ग_लिखोback_info[i].wb_enabled = false;
पूर्ण

अटल व्योम apply_ctx_पूर्णांकerdependent_lock(काष्ठा dc *dc, काष्ठा dc_state *context,
					  काष्ठा dc_stream_state *stream, bool lock)
अणु
	पूर्णांक i = 0;

	/* Checks अगर पूर्णांकerdependent update function poपूर्णांकer is शून्य or not, takes care of DCE110 हाल */
	अगर (dc->hwss.पूर्णांकerdependent_update_lock)
		dc->hwss.पूर्णांकerdependent_update_lock(dc, context, lock);
	अन्यथा अणु
		क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
			काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];
			काष्ठा pipe_ctx *old_pipe_ctx = &dc->current_state->res_ctx.pipe_ctx[i];

			// Copied conditions that were previously in dce110_apply_ctx_क्रम_surface
			अगर (stream == pipe_ctx->stream) अणु
				अगर (!pipe_ctx->top_pipe &&
					(pipe_ctx->plane_state || old_pipe_ctx->plane_state))
					dc->hwss.pipe_control_lock(dc, pipe_ctx, lock);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम disable_dangling_plane(काष्ठा dc *dc, काष्ठा dc_state *context)
अणु
	पूर्णांक i, j;
	काष्ठा dc_state *dangling_context = dc_create_state(dc);
	काष्ठा dc_state *current_ctx;

	अगर (dangling_context == शून्य)
		वापस;

	dc_resource_state_copy_स्थिरruct(dc->current_state, dangling_context);

	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा dc_stream_state *old_stream =
				dc->current_state->res_ctx.pipe_ctx[i].stream;
		bool should_disable = true;

		क्रम (j = 0; j < context->stream_count; j++) अणु
			अगर (old_stream == context->streams[j]) अणु
				should_disable = false;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (should_disable && old_stream) अणु
			dc_rem_all_planes_क्रम_stream(dc, old_stream, dangling_context);
			disable_all_ग_लिखोback_pipes_क्रम_stream(dc, old_stream, dangling_context);

			अगर (dc->hwss.apply_ctx_क्रम_surface) अणु
				apply_ctx_पूर्णांकerdependent_lock(dc, dc->current_state, old_stream, true);
				dc->hwss.apply_ctx_क्रम_surface(dc, old_stream, 0, dangling_context);
				apply_ctx_पूर्णांकerdependent_lock(dc, dc->current_state, old_stream, false);
				dc->hwss.post_unlock_program_front_end(dc, dangling_context);
			पूर्ण
			अगर (dc->hwss.program_front_end_क्रम_ctx) अणु
				dc->hwss.पूर्णांकerdependent_update_lock(dc, dc->current_state, true);
				dc->hwss.program_front_end_क्रम_ctx(dc, dangling_context);
				dc->hwss.पूर्णांकerdependent_update_lock(dc, dc->current_state, false);
				dc->hwss.post_unlock_program_front_end(dc, dangling_context);
			पूर्ण
		पूर्ण
	पूर्ण

	current_ctx = dc->current_state;
	dc->current_state = dangling_context;
	dc_release_state(current_ctx);
पूर्ण

अटल व्योम disable_vbios_mode_अगर_required(
		काष्ठा dc *dc,
		काष्ठा dc_state *context)
अणु
	अचिन्हित पूर्णांक i, j;

	/* check अगर timing_changed, disable stream*/
	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा dc_stream_state *stream = शून्य;
		काष्ठा dc_link *link = शून्य;
		काष्ठा pipe_ctx *pipe = शून्य;

		pipe = &context->res_ctx.pipe_ctx[i];
		stream = pipe->stream;
		अगर (stream == शून्य)
			जारी;

		// only looking क्रम first odm pipe
		अगर (pipe->prev_odm_pipe)
			जारी;

		अगर (stream->link->local_sink &&
			stream->link->local_sink->sink_संकेत == SIGNAL_TYPE_EDP) अणु
			link = stream->link;
		पूर्ण

		अगर (link != शून्य && link->link_enc->funcs->is_dig_enabled(link->link_enc)) अणु
			अचिन्हित पूर्णांक enc_inst, tg_inst = 0;
			अचिन्हित पूर्णांक pix_clk_100hz;

			enc_inst = link->link_enc->funcs->get_dig_frontend(link->link_enc);
			अगर (enc_inst != ENGINE_ID_UNKNOWN) अणु
				क्रम (j = 0; j < dc->res_pool->stream_enc_count; j++) अणु
					अगर (dc->res_pool->stream_enc[j]->id == enc_inst) अणु
						tg_inst = dc->res_pool->stream_enc[j]->funcs->dig_source_otg(
							dc->res_pool->stream_enc[j]);
						अवरोध;
					पूर्ण
				पूर्ण

				dc->res_pool->dp_घड़ी_source->funcs->get_pixel_clk_frequency_100hz(
					dc->res_pool->dp_घड़ी_source,
					tg_inst, &pix_clk_100hz);

				अगर (link->link_status.link_active) अणु
					uपूर्णांक32_t requested_pix_clk_100hz =
						pipe->stream_res.pix_clk_params.requested_pix_clk_100hz;

					अगर (pix_clk_100hz != requested_pix_clk_100hz) अणु
						core_link_disable_stream(pipe);
						pipe->stream->dpms_off = false;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम रुको_क्रम_no_pipes_pending(काष्ठा dc *dc, काष्ठा dc_state *context)
अणु
	पूर्णांक i;
	PERF_TRACE();
	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		पूर्णांक count = 0;
		काष्ठा pipe_ctx *pipe = &context->res_ctx.pipe_ctx[i];

		अगर (!pipe->plane_state)
			जारी;

		/* Timeout 100 ms */
		जबतक (count < 100000) अणु
			/* Must set to false to start with, due to OR in update function */
			pipe->plane_state->status.is_flip_pending = false;
			dc->hwss.update_pending_status(pipe);
			अगर (!pipe->plane_state->status.is_flip_pending)
				अवरोध;
			udelay(1);
			count++;
		पूर्ण
		ASSERT(!pipe->plane_state->status.is_flip_pending);
	पूर्ण
	PERF_TRACE();
पूर्ण

/*******************************************************************************
 * Public functions
 ******************************************************************************/

काष्ठा dc *dc_create(स्थिर काष्ठा dc_init_data *init_params)
अणु
	काष्ठा dc *dc = kzalloc(माप(*dc), GFP_KERNEL);
	अचिन्हित पूर्णांक full_pipe_count;

	अगर (!dc)
		वापस शून्य;

	अगर (init_params->dce_environment == DCE_ENV_VIRTUAL_HW) अणु
		अगर (!dc_स्थिरruct_ctx(dc, init_params))
			जाओ deकाष्ठा_dc;
	पूर्ण अन्यथा अणु
		अगर (!dc_स्थिरruct(dc, init_params))
			जाओ deकाष्ठा_dc;

		full_pipe_count = dc->res_pool->pipe_count;
		अगर (dc->res_pool->underlay_pipe_index != NO_UNDERLAY_PIPE)
			full_pipe_count--;
		dc->caps.max_streams = min(
				full_pipe_count,
				dc->res_pool->stream_enc_count);

		dc->caps.max_links = dc->link_count;
		dc->caps.max_audios = dc->res_pool->audio_count;
		dc->caps.linear_pitch_alignment = 64;

		dc->caps.max_dp_protocol_version = DP_VERSION_1_4;

		अगर (dc->res_pool->dmcu != शून्य)
			dc->versions.dmcu_version = dc->res_pool->dmcu->dmcu_version;
	पूर्ण

	/* Populate versioning inक्रमmation */
	dc->versions.dc_ver = DC_VER;

	dc->build_id = DC_BUILD_ID;

	DC_LOG_DC("Display Core initialized\n");



	वापस dc;

deकाष्ठा_dc:
	dc_deकाष्ठा(dc);
	kमुक्त(dc);
	वापस शून्य;
पूर्ण

अटल व्योम detect_edp_presence(काष्ठा dc *dc)
अणु
	काष्ठा dc_link *edp_links[MAX_NUM_EDP];
	काष्ठा dc_link *edp_link = शून्य;
	क्रमागत dc_connection_type type;
	पूर्णांक i;
	पूर्णांक edp_num;

	get_edp_links(dc, edp_links, &edp_num);
	अगर (!edp_num)
		वापस;

	क्रम (i = 0; i < edp_num; i++) अणु
		edp_link = edp_links[i];
		अगर (dc->config.edp_not_connected) अणु
			edp_link->edp_sink_present = false;
		पूर्ण अन्यथा अणु
			dc_link_detect_sink(edp_link, &type);
			edp_link->edp_sink_present = (type != dc_connection_none);
		पूर्ण
	पूर्ण
पूर्ण

व्योम dc_hardware_init(काष्ठा dc *dc)
अणु

	detect_edp_presence(dc);
	अगर (dc->ctx->dce_environment != DCE_ENV_VIRTUAL_HW)
		dc->hwss.init_hw(dc);
पूर्ण

व्योम dc_init_callbacks(काष्ठा dc *dc,
		स्थिर काष्ठा dc_callback_init *init_params)
अणु
#अगर_घोषित CONFIG_DRM_AMD_DC_HDCP
	dc->ctx->cp_psp = init_params->cp_psp;
#पूर्ण_अगर
पूर्ण

व्योम dc_deinit_callbacks(काष्ठा dc *dc)
अणु
#अगर_घोषित CONFIG_DRM_AMD_DC_HDCP
	स_रखो(&dc->ctx->cp_psp, 0, माप(dc->ctx->cp_psp));
#पूर्ण_अगर
पूर्ण

व्योम dc_destroy(काष्ठा dc **dc)
अणु
	dc_deकाष्ठा(*dc);
	kमुक्त(*dc);
	*dc = शून्य;
पूर्ण

अटल व्योम enable_timing_multisync(
		काष्ठा dc *dc,
		काष्ठा dc_state *ctx)
अणु
	पूर्णांक i = 0, multisync_count = 0;
	पूर्णांक pipe_count = dc->res_pool->pipe_count;
	काष्ठा pipe_ctx *multisync_pipes[MAX_PIPES] = अणु शून्य पूर्ण;

	क्रम (i = 0; i < pipe_count; i++) अणु
		अगर (!ctx->res_ctx.pipe_ctx[i].stream ||
				!ctx->res_ctx.pipe_ctx[i].stream->triggered_crtc_reset.enabled)
			जारी;
		अगर (ctx->res_ctx.pipe_ctx[i].stream == ctx->res_ctx.pipe_ctx[i].stream->triggered_crtc_reset.event_source)
			जारी;
		multisync_pipes[multisync_count] = &ctx->res_ctx.pipe_ctx[i];
		multisync_count++;
	पूर्ण

	अगर (multisync_count > 0) अणु
		dc->hwss.enable_per_frame_crtc_position_reset(
			dc, multisync_count, multisync_pipes);
	पूर्ण
पूर्ण

अटल व्योम program_timing_sync(
		काष्ठा dc *dc,
		काष्ठा dc_state *ctx)
अणु
	पूर्णांक i, j, k;
	पूर्णांक group_index = 0;
	पूर्णांक num_group = 0;
	पूर्णांक pipe_count = dc->res_pool->pipe_count;
	काष्ठा pipe_ctx *unsynced_pipes[MAX_PIPES] = अणु शून्य पूर्ण;

	क्रम (i = 0; i < pipe_count; i++) अणु
		अगर (!ctx->res_ctx.pipe_ctx[i].stream || ctx->res_ctx.pipe_ctx[i].top_pipe)
			जारी;

		unsynced_pipes[i] = &ctx->res_ctx.pipe_ctx[i];
	पूर्ण

	क्रम (i = 0; i < pipe_count; i++) अणु
		पूर्णांक group_size = 1;
		क्रमागत timing_synchronization_type sync_type = NOT_SYNCHRONIZABLE;
		काष्ठा pipe_ctx *pipe_set[MAX_PIPES];

		अगर (!unsynced_pipes[i])
			जारी;

		pipe_set[0] = unsynced_pipes[i];
		unsynced_pipes[i] = शून्य;

		/* Add tg to the set, search rest of the tg's क्रम ones with
		 * same timing, add all tgs with same timing to the group
		 */
		क्रम (j = i + 1; j < pipe_count; j++) अणु
			अगर (!unsynced_pipes[j])
				जारी;
			अगर (sync_type != TIMING_SYNCHRONIZABLE &&
				dc->hwss.enable_vblanks_synchronization &&
				unsynced_pipes[j]->stream_res.tg->funcs->align_vblanks &&
				resource_are_vblanks_synchronizable(
					unsynced_pipes[j]->stream,
					pipe_set[0]->stream)) अणु
				sync_type = VBLANK_SYNCHRONIZABLE;
				pipe_set[group_size] = unsynced_pipes[j];
				unsynced_pipes[j] = शून्य;
				group_size++;
			पूर्ण अन्यथा
			अगर (sync_type != VBLANK_SYNCHRONIZABLE &&
				resource_are_streams_timing_synchronizable(
					unsynced_pipes[j]->stream,
					pipe_set[0]->stream)) अणु
				sync_type = TIMING_SYNCHRONIZABLE;
				pipe_set[group_size] = unsynced_pipes[j];
				unsynced_pipes[j] = शून्य;
				group_size++;
			पूर्ण
		पूर्ण

		/* set first unblanked pipe as master */
		क्रम (j = 0; j < group_size; j++) अणु
			bool is_blanked;

			अगर (pipe_set[j]->stream_res.opp->funcs->dpg_is_blanked)
				is_blanked =
					pipe_set[j]->stream_res.opp->funcs->dpg_is_blanked(pipe_set[j]->stream_res.opp);
			अन्यथा
				is_blanked =
					pipe_set[j]->stream_res.tg->funcs->is_blanked(pipe_set[j]->stream_res.tg);
			अगर (!is_blanked) अणु
				अगर (j == 0)
					अवरोध;

				swap(pipe_set[0], pipe_set[j]);
				अवरोध;
			पूर्ण
		पूर्ण

		क्रम (k = 0; k < group_size; k++) अणु
			काष्ठा dc_stream_status *status = dc_stream_get_status_from_state(ctx, pipe_set[k]->stream);

			status->timing_sync_info.group_id = num_group;
			status->timing_sync_info.group_size = group_size;
			अगर (k == 0)
				status->timing_sync_info.master = true;
			अन्यथा
				status->timing_sync_info.master = false;

		पूर्ण
		/* हटाओ any other unblanked pipes as they have alपढ़ोy been synced */
		क्रम (j = j + 1; j < group_size; j++) अणु
			bool is_blanked;

			अगर (pipe_set[j]->stream_res.opp->funcs->dpg_is_blanked)
				is_blanked =
					pipe_set[j]->stream_res.opp->funcs->dpg_is_blanked(pipe_set[j]->stream_res.opp);
			अन्यथा
				is_blanked =
					pipe_set[j]->stream_res.tg->funcs->is_blanked(pipe_set[j]->stream_res.tg);
			अगर (!is_blanked) अणु
				group_size--;
				pipe_set[j] = pipe_set[group_size];
				j--;
			पूर्ण
		पूर्ण

		अगर (group_size > 1) अणु
			अगर (sync_type == TIMING_SYNCHRONIZABLE) अणु
				dc->hwss.enable_timing_synchronization(
					dc, group_index, group_size, pipe_set);
			पूर्ण अन्यथा
				अगर (sync_type == VBLANK_SYNCHRONIZABLE) अणु
				dc->hwss.enable_vblanks_synchronization(
					dc, group_index, group_size, pipe_set);
				पूर्ण
			group_index++;
		पूर्ण
		num_group++;
	पूर्ण
पूर्ण

अटल bool context_changed(
		काष्ठा dc *dc,
		काष्ठा dc_state *context)
अणु
	uपूर्णांक8_t i;

	अगर (context->stream_count != dc->current_state->stream_count)
		वापस true;

	क्रम (i = 0; i < dc->current_state->stream_count; i++) अणु
		अगर (dc->current_state->streams[i] != context->streams[i])
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

bool dc_validate_seamless_boot_timing(स्थिर काष्ठा dc *dc,
				स्थिर काष्ठा dc_sink *sink,
				काष्ठा dc_crtc_timing *crtc_timing)
अणु
	काष्ठा timing_generator *tg;
	काष्ठा stream_encoder *se = शून्य;

	काष्ठा dc_crtc_timing hw_crtc_timing = अणु0पूर्ण;

	काष्ठा dc_link *link = sink->link;
	अचिन्हित पूर्णांक i, enc_inst, tg_inst = 0;

	/* Support seamless boot on EDP displays only */
	अगर (sink->sink_संकेत != SIGNAL_TYPE_EDP) अणु
		वापस false;
	पूर्ण

	/* Check क्रम enabled DIG to identअगरy enabled display */
	अगर (!link->link_enc->funcs->is_dig_enabled(link->link_enc))
		वापस false;

	enc_inst = link->link_enc->funcs->get_dig_frontend(link->link_enc);

	अगर (enc_inst == ENGINE_ID_UNKNOWN)
		वापस false;

	क्रम (i = 0; i < dc->res_pool->stream_enc_count; i++) अणु
		अगर (dc->res_pool->stream_enc[i]->id == enc_inst) अणु

			se = dc->res_pool->stream_enc[i];

			tg_inst = dc->res_pool->stream_enc[i]->funcs->dig_source_otg(
				dc->res_pool->stream_enc[i]);
			अवरोध;
		पूर्ण
	पूर्ण

	// tg_inst not found
	अगर (i == dc->res_pool->stream_enc_count)
		वापस false;

	अगर (tg_inst >= dc->res_pool->timing_generator_count)
		वापस false;

	tg = dc->res_pool->timing_generators[tg_inst];

	अगर (!tg->funcs->get_hw_timing)
		वापस false;

	अगर (!tg->funcs->get_hw_timing(tg, &hw_crtc_timing))
		वापस false;

	अगर (crtc_timing->h_total != hw_crtc_timing.h_total)
		वापस false;

	अगर (crtc_timing->h_border_left != hw_crtc_timing.h_border_left)
		वापस false;

	अगर (crtc_timing->h_addressable != hw_crtc_timing.h_addressable)
		वापस false;

	अगर (crtc_timing->h_border_right != hw_crtc_timing.h_border_right)
		वापस false;

	अगर (crtc_timing->h_front_porch != hw_crtc_timing.h_front_porch)
		वापस false;

	अगर (crtc_timing->h_sync_width != hw_crtc_timing.h_sync_width)
		वापस false;

	अगर (crtc_timing->v_total != hw_crtc_timing.v_total)
		वापस false;

	अगर (crtc_timing->v_border_top != hw_crtc_timing.v_border_top)
		वापस false;

	अगर (crtc_timing->v_addressable != hw_crtc_timing.v_addressable)
		वापस false;

	अगर (crtc_timing->v_border_bottom != hw_crtc_timing.v_border_bottom)
		वापस false;

	अगर (crtc_timing->v_front_porch != hw_crtc_timing.v_front_porch)
		वापस false;

	अगर (crtc_timing->v_sync_width != hw_crtc_timing.v_sync_width)
		वापस false;

	/* block DSC क्रम now, as VBIOS करोes not currently support DSC timings */
	अगर (crtc_timing->flags.DSC)
		वापस false;

	अगर (dc_is_dp_संकेत(link->connector_संकेत)) अणु
		अचिन्हित पूर्णांक pix_clk_100hz;

		dc->res_pool->dp_घड़ी_source->funcs->get_pixel_clk_frequency_100hz(
			dc->res_pool->dp_घड़ी_source,
			tg_inst, &pix_clk_100hz);

		अगर (crtc_timing->pix_clk_100hz != pix_clk_100hz)
			वापस false;

		अगर (!se->funcs->dp_get_pixel_क्रमmat)
			वापस false;

		अगर (!se->funcs->dp_get_pixel_क्रमmat(
			se,
			&hw_crtc_timing.pixel_encoding,
			&hw_crtc_timing.display_color_depth))
			वापस false;

		अगर (hw_crtc_timing.display_color_depth != crtc_timing->display_color_depth)
			वापस false;

		अगर (hw_crtc_timing.pixel_encoding != crtc_timing->pixel_encoding)
			वापस false;
	पूर्ण

	अगर (link->dpcd_caps.dprx_feature.bits.VSC_SDP_COLORIMETRY_SUPPORTED) अणु
		वापस false;
	पूर्ण

	अगर (is_edp_ilr_optimization_required(link, crtc_timing)) अणु
		DC_LOG_EVENT_LINK_TRAINING("Seamless boot disabled to optimize eDP link rate\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

व्योम dc_enable_stereo(
	काष्ठा dc *dc,
	काष्ठा dc_state *context,
	काष्ठा dc_stream_state *streams[],
	uपूर्णांक8_t stream_count)
अणु
	पूर्णांक i, j;
	काष्ठा pipe_ctx *pipe;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		अगर (context != शून्य)
			pipe = &context->res_ctx.pipe_ctx[i];
		अन्यथा
			pipe = &dc->current_state->res_ctx.pipe_ctx[i];
		क्रम (j = 0 ; pipe && j < stream_count; j++)  अणु
			अगर (streams[j] && streams[j] == pipe->stream &&
				dc->hwss.setup_stereo)
				dc->hwss.setup_stereo(pipe, dc);
		पूर्ण
	पूर्ण
पूर्ण

व्योम dc_trigger_sync(काष्ठा dc *dc, काष्ठा dc_state *context)
अणु
	अगर (context->stream_count > 1 && !dc->debug.disable_timing_sync) अणु
		enable_timing_multisync(dc, context);
		program_timing_sync(dc, context);
	पूर्ण
पूर्ण

अटल uपूर्णांक8_t get_stream_mask(काष्ठा dc *dc, काष्ठा dc_state *context)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक stream_mask = 0;

	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		अगर (context->res_ctx.pipe_ctx[i].stream)
			stream_mask |= 1 << i;
	पूर्ण

	वापस stream_mask;
पूर्ण

/*
 * Applies given context to HW and copy it पूर्णांकo current context.
 * It's up to the user to release the src context afterwards.
 */
अटल क्रमागत dc_status dc_commit_state_no_check(काष्ठा dc *dc, काष्ठा dc_state *context)
अणु
	काष्ठा dc_bios *dcb = dc->ctx->dc_bios;
	क्रमागत dc_status result = DC_ERROR_UNEXPECTED;
	काष्ठा pipe_ctx *pipe;
	पूर्णांक i, k, l;
	काष्ठा dc_stream_state *dc_streams[MAX_STREAMS] = अणु0पूर्ण;

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	dc_allow_idle_optimizations(dc, false);
#पूर्ण_अगर

	क्रम (i = 0; i < context->stream_count; i++)
		dc_streams[i] =  context->streams[i];

	अगर (!dcb->funcs->is_accelerated_mode(dcb)) अणु
		disable_vbios_mode_अगर_required(dc, context);
		dc->hwss.enable_accelerated_mode(dc, context);
	पूर्ण

	अगर (context->stream_count > get_seamless_boot_stream_count(context) ||
		context->stream_count == 0)
		dc->hwss.prepare_bandwidth(dc, context);

	disable_dangling_plane(dc, context);
	/* re-program planes क्रम existing stream, in हाल we need to
	 * मुक्त up plane resource क्रम later use
	 */
	अगर (dc->hwss.apply_ctx_क्रम_surface) अणु
		क्रम (i = 0; i < context->stream_count; i++) अणु
			अगर (context->streams[i]->mode_changed)
				जारी;
			apply_ctx_पूर्णांकerdependent_lock(dc, context, context->streams[i], true);
			dc->hwss.apply_ctx_क्रम_surface(
				dc, context->streams[i],
				context->stream_status[i].plane_count,
				context); /* use new pipe config in new context */
			apply_ctx_पूर्णांकerdependent_lock(dc, context, context->streams[i], false);
			dc->hwss.post_unlock_program_front_end(dc, context);
		पूर्ण
	पूर्ण

	/* Program hardware */
	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		pipe = &context->res_ctx.pipe_ctx[i];
		dc->hwss.रुको_क्रम_mpcc_disconnect(dc, dc->res_pool, pipe);
	पूर्ण

	result = dc->hwss.apply_ctx_to_hw(dc, context);

	अगर (result != DC_OK)
		वापस result;

	dc_trigger_sync(dc, context);

	/* Program all planes within new context*/
	अगर (dc->hwss.program_front_end_क्रम_ctx) अणु
		dc->hwss.पूर्णांकerdependent_update_lock(dc, context, true);
		dc->hwss.program_front_end_क्रम_ctx(dc, context);
		dc->hwss.पूर्णांकerdependent_update_lock(dc, context, false);
		dc->hwss.post_unlock_program_front_end(dc, context);
	पूर्ण
	क्रम (i = 0; i < context->stream_count; i++) अणु
		स्थिर काष्ठा dc_link *link = context->streams[i]->link;

		अगर (!context->streams[i]->mode_changed)
			जारी;

		अगर (dc->hwss.apply_ctx_क्रम_surface) अणु
			apply_ctx_पूर्णांकerdependent_lock(dc, context, context->streams[i], true);
			dc->hwss.apply_ctx_क्रम_surface(
					dc, context->streams[i],
					context->stream_status[i].plane_count,
					context);
			apply_ctx_पूर्णांकerdependent_lock(dc, context, context->streams[i], false);
			dc->hwss.post_unlock_program_front_end(dc, context);
		पूर्ण

		/*
		 * enable stereo
		 * TODO rework dc_enable_stereo call to work with validation sets?
		 */
		क्रम (k = 0; k < MAX_PIPES; k++) अणु
			pipe = &context->res_ctx.pipe_ctx[k];

			क्रम (l = 0 ; pipe && l < context->stream_count; l++)  अणु
				अगर (context->streams[l] &&
					context->streams[l] == pipe->stream &&
					dc->hwss.setup_stereo)
					dc->hwss.setup_stereo(pipe, dc);
			पूर्ण
		पूर्ण

		CONN_MSG_MODE(link, "{%dx%d, %dx%d@%dKhz}",
				context->streams[i]->timing.h_addressable,
				context->streams[i]->timing.v_addressable,
				context->streams[i]->timing.h_total,
				context->streams[i]->timing.v_total,
				context->streams[i]->timing.pix_clk_100hz / 10);
	पूर्ण

	dc_enable_stereo(dc, context, dc_streams, context->stream_count);

	अगर (context->stream_count > get_seamless_boot_stream_count(context) ||
		context->stream_count == 0) अणु
		/* Must रुको क्रम no flips to be pending beक्रमe करोing optimize bw */
		रुको_क्रम_no_pipes_pending(dc, context);
		/* pplib is notअगरied अगर disp_num changed */
		dc->hwss.optimize_bandwidth(dc, context);
	पूर्ण

	अगर (dc->ctx->dce_version >= DCE_VERSION_MAX)
		TRACE_DCN_CLOCK_STATE(&context->bw_ctx.bw.dcn.clk);
	अन्यथा
		TRACE_DCE_CLOCK_STATE(&context->bw_ctx.bw.dce);

	context->stream_mask = get_stream_mask(dc, context);

	अगर (context->stream_mask != dc->current_state->stream_mask)
		dc_dmub_srv_notअगरy_stream_mask(dc->ctx->dmub_srv, context->stream_mask);

	क्रम (i = 0; i < context->stream_count; i++)
		context->streams[i]->mode_changed = false;

	dc_release_state(dc->current_state);

	dc->current_state = context;

	dc_retain_state(dc->current_state);

	वापस result;
पूर्ण

bool dc_commit_state(काष्ठा dc *dc, काष्ठा dc_state *context)
अणु
	क्रमागत dc_status result = DC_ERROR_UNEXPECTED;
	पूर्णांक i;

	अगर (!context_changed(dc, context))
		वापस DC_OK;

	DC_LOG_DC("%s: %d streams\n",
				__func__, context->stream_count);

	क्रम (i = 0; i < context->stream_count; i++) अणु
		काष्ठा dc_stream_state *stream = context->streams[i];

		dc_stream_log(dc, stream);
	पूर्ण

	result = dc_commit_state_no_check(dc, context);

	वापस (result == DC_OK);
पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
bool dc_acquire_release_mpc_3dlut(
		काष्ठा dc *dc, bool acquire,
		काष्ठा dc_stream_state *stream,
		काष्ठा dc_3dlut **lut,
		काष्ठा dc_transfer_func **shaper)
अणु
	पूर्णांक pipe_idx;
	bool ret = false;
	bool found_pipe_idx = false;
	स्थिर काष्ठा resource_pool *pool = dc->res_pool;
	काष्ठा resource_context *res_ctx = &dc->current_state->res_ctx;
	पूर्णांक mpcc_id = 0;

	अगर (pool && res_ctx) अणु
		अगर (acquire) अणु
			/*find pipe idx क्रम the given stream*/
			क्रम (pipe_idx = 0; pipe_idx < pool->pipe_count; pipe_idx++) अणु
				अगर (res_ctx->pipe_ctx[pipe_idx].stream == stream) अणु
					found_pipe_idx = true;
					mpcc_id = res_ctx->pipe_ctx[pipe_idx].plane_res.hubp->inst;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा
			found_pipe_idx = true;/*क्रम release pipe_idx is not required*/

		अगर (found_pipe_idx) अणु
			अगर (acquire && pool->funcs->acquire_post_bldn_3dlut)
				ret = pool->funcs->acquire_post_bldn_3dlut(res_ctx, pool, mpcc_id, lut, shaper);
			अन्यथा अगर (!acquire && pool->funcs->release_post_bldn_3dlut)
				ret = pool->funcs->release_post_bldn_3dlut(res_ctx, pool, lut, shaper);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण
#पूर्ण_अगर
अटल bool is_flip_pending_in_pipes(काष्ठा dc *dc, काष्ठा dc_state *context)
अणु
	पूर्णांक i;
	काष्ठा pipe_ctx *pipe;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		pipe = &context->res_ctx.pipe_ctx[i];

		अगर (!pipe->plane_state)
			जारी;

		/* Must set to false to start with, due to OR in update function */
		pipe->plane_state->status.is_flip_pending = false;
		dc->hwss.update_pending_status(pipe);
		अगर (pipe->plane_state->status.is_flip_pending)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

व्योम dc_post_update_surfaces_to_stream(काष्ठा dc *dc)
अणु
	पूर्णांक i;
	काष्ठा dc_state *context = dc->current_state;

	अगर ((!dc->optimized_required) || get_seamless_boot_stream_count(context) > 0)
		वापस;

	post_surface_trace(dc);

	अगर (is_flip_pending_in_pipes(dc, context))
		वापस;

	क्रम (i = 0; i < dc->res_pool->pipe_count; i++)
		अगर (context->res_ctx.pipe_ctx[i].stream == शून्य ||
		    context->res_ctx.pipe_ctx[i].plane_state == शून्य) अणु
			context->res_ctx.pipe_ctx[i].pipe_idx = i;
			dc->hwss.disable_plane(dc, &context->res_ctx.pipe_ctx[i]);
		पूर्ण

	dc->hwss.optimize_bandwidth(dc, context);

	dc->optimized_required = false;
	dc->wm_optimized_required = false;
पूर्ण

अटल व्योम init_state(काष्ठा dc *dc, काष्ठा dc_state *context)
अणु
	/* Each context must have their own instance of VBA and in order to
	 * initialize and obtain IP and SOC the base DML instance from DC is
	 * initially copied पूर्णांकo every context
	 */
#अगर_घोषित CONFIG_DRM_AMD_DC_DCN
	स_नकल(&context->bw_ctx.dml, &dc->dml, माप(काष्ठा display_mode_lib));
#पूर्ण_अगर
पूर्ण

काष्ठा dc_state *dc_create_state(काष्ठा dc *dc)
अणु
	काष्ठा dc_state *context = kvzalloc(माप(काष्ठा dc_state),
					    GFP_KERNEL);

	अगर (!context)
		वापस शून्य;

	init_state(dc, context);

	kref_init(&context->refcount);

	वापस context;
पूर्ण

काष्ठा dc_state *dc_copy_state(काष्ठा dc_state *src_ctx)
अणु
	पूर्णांक i, j;
	काष्ठा dc_state *new_ctx = kvदो_स्मृति(माप(काष्ठा dc_state), GFP_KERNEL);

	अगर (!new_ctx)
		वापस शून्य;
	स_नकल(new_ctx, src_ctx, माप(काष्ठा dc_state));

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
			काष्ठा pipe_ctx *cur_pipe = &new_ctx->res_ctx.pipe_ctx[i];

			अगर (cur_pipe->top_pipe)
				cur_pipe->top_pipe =  &new_ctx->res_ctx.pipe_ctx[cur_pipe->top_pipe->pipe_idx];

			अगर (cur_pipe->bottom_pipe)
				cur_pipe->bottom_pipe = &new_ctx->res_ctx.pipe_ctx[cur_pipe->bottom_pipe->pipe_idx];

			अगर (cur_pipe->prev_odm_pipe)
				cur_pipe->prev_odm_pipe =  &new_ctx->res_ctx.pipe_ctx[cur_pipe->prev_odm_pipe->pipe_idx];

			अगर (cur_pipe->next_odm_pipe)
				cur_pipe->next_odm_pipe = &new_ctx->res_ctx.pipe_ctx[cur_pipe->next_odm_pipe->pipe_idx];

	पूर्ण

	क्रम (i = 0; i < new_ctx->stream_count; i++) अणु
			dc_stream_retain(new_ctx->streams[i]);
			क्रम (j = 0; j < new_ctx->stream_status[i].plane_count; j++)
				dc_plane_state_retain(
					new_ctx->stream_status[i].plane_states[j]);
	पूर्ण

	kref_init(&new_ctx->refcount);

	वापस new_ctx;
पूर्ण

व्योम dc_retain_state(काष्ठा dc_state *context)
अणु
	kref_get(&context->refcount);
पूर्ण

अटल व्योम dc_state_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा dc_state *context = container_of(kref, काष्ठा dc_state, refcount);
	dc_resource_state_deकाष्ठा(context);
	kvमुक्त(context);
पूर्ण

व्योम dc_release_state(काष्ठा dc_state *context)
अणु
	kref_put(&context->refcount, dc_state_मुक्त);
पूर्ण

bool dc_set_generic_gpio_क्रम_stereo(bool enable,
		काष्ठा gpio_service *gpio_service)
अणु
	क्रमागत gpio_result gpio_result = GPIO_RESULT_NON_SPECIFIC_ERROR;
	काष्ठा gpio_pin_info pin_info;
	काष्ठा gpio *generic;
	काष्ठा gpio_generic_mux_config *config = kzalloc(माप(काष्ठा gpio_generic_mux_config),
			   GFP_KERNEL);

	अगर (!config)
		वापस false;
	pin_info = dal_gpio_get_generic_pin_info(gpio_service, GPIO_ID_GENERIC, 0);

	अगर (pin_info.mask == 0xFFFFFFFF || pin_info.offset == 0xFFFFFFFF) अणु
		kमुक्त(config);
		वापस false;
	पूर्ण अन्यथा अणु
		generic = dal_gpio_service_create_generic_mux(
			gpio_service,
			pin_info.offset,
			pin_info.mask);
	पूर्ण

	अगर (!generic) अणु
		kमुक्त(config);
		वापस false;
	पूर्ण

	gpio_result = dal_gpio_खोलो(generic, GPIO_MODE_OUTPUT);

	config->enable_output_from_mux = enable;
	config->mux_select = GPIO_SIGNAL_SOURCE_PASS_THROUGH_STEREO_SYNC;

	अगर (gpio_result == GPIO_RESULT_OK)
		gpio_result = dal_mux_setup_config(generic, config);

	अगर (gpio_result == GPIO_RESULT_OK) अणु
		dal_gpio_बंद(generic);
		dal_gpio_destroy_generic_mux(&generic);
		kमुक्त(config);
		वापस true;
	पूर्ण अन्यथा अणु
		dal_gpio_बंद(generic);
		dal_gpio_destroy_generic_mux(&generic);
		kमुक्त(config);
		वापस false;
	पूर्ण
पूर्ण

अटल bool is_surface_in_context(
		स्थिर काष्ठा dc_state *context,
		स्थिर काष्ठा dc_plane_state *plane_state)
अणु
	पूर्णांक j;

	क्रम (j = 0; j < MAX_PIPES; j++) अणु
		स्थिर काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[j];

		अगर (plane_state == pipe_ctx->plane_state) अणु
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल क्रमागत surface_update_type get_plane_info_update_type(स्थिर काष्ठा dc_surface_update *u)
अणु
	जोड़ surface_update_flags *update_flags = &u->surface->update_flags;
	क्रमागत surface_update_type update_type = UPDATE_TYPE_FAST;

	अगर (!u->plane_info)
		वापस UPDATE_TYPE_FAST;

	अगर (u->plane_info->color_space != u->surface->color_space) अणु
		update_flags->bits.color_space_change = 1;
		elevate_update_type(&update_type, UPDATE_TYPE_MED);
	पूर्ण

	अगर (u->plane_info->horizontal_mirror != u->surface->horizontal_mirror) अणु
		update_flags->bits.horizontal_mirror_change = 1;
		elevate_update_type(&update_type, UPDATE_TYPE_MED);
	पूर्ण

	अगर (u->plane_info->rotation != u->surface->rotation) अणु
		update_flags->bits.rotation_change = 1;
		elevate_update_type(&update_type, UPDATE_TYPE_FULL);
	पूर्ण

	अगर (u->plane_info->क्रमmat != u->surface->क्रमmat) अणु
		update_flags->bits.pixel_क्रमmat_change = 1;
		elevate_update_type(&update_type, UPDATE_TYPE_FULL);
	पूर्ण

	अगर (u->plane_info->stereo_क्रमmat != u->surface->stereo_क्रमmat) अणु
		update_flags->bits.stereo_क्रमmat_change = 1;
		elevate_update_type(&update_type, UPDATE_TYPE_FULL);
	पूर्ण

	अगर (u->plane_info->per_pixel_alpha != u->surface->per_pixel_alpha) अणु
		update_flags->bits.per_pixel_alpha_change = 1;
		elevate_update_type(&update_type, UPDATE_TYPE_MED);
	पूर्ण

	अगर (u->plane_info->global_alpha_value != u->surface->global_alpha_value) अणु
		update_flags->bits.global_alpha_change = 1;
		elevate_update_type(&update_type, UPDATE_TYPE_MED);
	पूर्ण

	अगर (u->plane_info->dcc.enable != u->surface->dcc.enable
			|| u->plane_info->dcc.independent_64b_blks != u->surface->dcc.independent_64b_blks
			|| u->plane_info->dcc.meta_pitch != u->surface->dcc.meta_pitch) अणु
		update_flags->bits.dcc_change = 1;
		elevate_update_type(&update_type, UPDATE_TYPE_MED);
	पूर्ण

	अगर (resource_pixel_क्रमmat_to_bpp(u->plane_info->क्रमmat) !=
			resource_pixel_क्रमmat_to_bpp(u->surface->क्रमmat)) अणु
		/* dअगरferent bytes per element will require full bandwidth
		 * and DML calculation
		 */
		update_flags->bits.bpp_change = 1;
		elevate_update_type(&update_type, UPDATE_TYPE_FULL);
	पूर्ण

	अगर (u->plane_info->plane_size.surface_pitch != u->surface->plane_size.surface_pitch
			|| u->plane_info->plane_size.chroma_pitch != u->surface->plane_size.chroma_pitch) अणु
		update_flags->bits.plane_size_change = 1;
		elevate_update_type(&update_type, UPDATE_TYPE_MED);
	पूर्ण


	अगर (स_भेद(&u->plane_info->tiling_info, &u->surface->tiling_info,
			माप(जोड़ dc_tiling_info)) != 0) अणु
		update_flags->bits.swizzle_change = 1;
		elevate_update_type(&update_type, UPDATE_TYPE_MED);

		/* toकरो: below are HW dependent, we should add a hook to
		 * DCE/N resource and validated there.
		 */
		अगर (u->plane_info->tiling_info.gfx9.swizzle != DC_SW_LINEAR) अणु
			/* swizzled mode requires RQ to be setup properly,
			 * thus need to run DML to calculate RQ settings
			 */
			update_flags->bits.bandwidth_change = 1;
			elevate_update_type(&update_type, UPDATE_TYPE_FULL);
		पूर्ण
	पूर्ण

	/* This should be UPDATE_TYPE_FAST अगर nothing has changed. */
	वापस update_type;
पूर्ण

अटल क्रमागत surface_update_type get_scaling_info_update_type(
		स्थिर काष्ठा dc_surface_update *u)
अणु
	जोड़ surface_update_flags *update_flags = &u->surface->update_flags;

	अगर (!u->scaling_info)
		वापस UPDATE_TYPE_FAST;

	अगर (u->scaling_info->clip_rect.width != u->surface->clip_rect.width
			|| u->scaling_info->clip_rect.height != u->surface->clip_rect.height
			|| u->scaling_info->dst_rect.width != u->surface->dst_rect.width
			|| u->scaling_info->dst_rect.height != u->surface->dst_rect.height
			|| u->scaling_info->scaling_quality.पूर्णांकeger_scaling !=
				u->surface->scaling_quality.पूर्णांकeger_scaling
			) अणु
		update_flags->bits.scaling_change = 1;

		अगर ((u->scaling_info->dst_rect.width < u->surface->dst_rect.width
			|| u->scaling_info->dst_rect.height < u->surface->dst_rect.height)
				&& (u->scaling_info->dst_rect.width < u->surface->src_rect.width
					|| u->scaling_info->dst_rect.height < u->surface->src_rect.height))
			/* Making dst rect smaller requires a bandwidth change */
			update_flags->bits.bandwidth_change = 1;
	पूर्ण

	अगर (u->scaling_info->src_rect.width != u->surface->src_rect.width
		|| u->scaling_info->src_rect.height != u->surface->src_rect.height) अणु

		update_flags->bits.scaling_change = 1;
		अगर (u->scaling_info->src_rect.width > u->surface->src_rect.width
				|| u->scaling_info->src_rect.height > u->surface->src_rect.height)
			/* Making src rect bigger requires a bandwidth change */
			update_flags->bits.घड़ी_change = 1;
	पूर्ण

	अगर (u->scaling_info->src_rect.x != u->surface->src_rect.x
			|| u->scaling_info->src_rect.y != u->surface->src_rect.y
			|| u->scaling_info->clip_rect.x != u->surface->clip_rect.x
			|| u->scaling_info->clip_rect.y != u->surface->clip_rect.y
			|| u->scaling_info->dst_rect.x != u->surface->dst_rect.x
			|| u->scaling_info->dst_rect.y != u->surface->dst_rect.y)
		update_flags->bits.position_change = 1;

	अगर (update_flags->bits.घड़ी_change
			|| update_flags->bits.bandwidth_change
			|| update_flags->bits.scaling_change)
		वापस UPDATE_TYPE_FULL;

	अगर (update_flags->bits.position_change)
		वापस UPDATE_TYPE_MED;

	वापस UPDATE_TYPE_FAST;
पूर्ण

अटल क्रमागत surface_update_type det_surface_update(स्थिर काष्ठा dc *dc,
		स्थिर काष्ठा dc_surface_update *u)
अणु
	स्थिर काष्ठा dc_state *context = dc->current_state;
	क्रमागत surface_update_type type;
	क्रमागत surface_update_type overall_type = UPDATE_TYPE_FAST;
	जोड़ surface_update_flags *update_flags = &u->surface->update_flags;

	अगर (u->flip_addr)
		update_flags->bits.addr_update = 1;

	अगर (!is_surface_in_context(context, u->surface) || u->surface->क्रमce_full_update) अणु
		update_flags->raw = 0xFFFFFFFF;
		वापस UPDATE_TYPE_FULL;
	पूर्ण

	update_flags->raw = 0; // Reset all flags

	type = get_plane_info_update_type(u);
	elevate_update_type(&overall_type, type);

	type = get_scaling_info_update_type(u);
	elevate_update_type(&overall_type, type);

	अगर (u->flip_addr)
		update_flags->bits.addr_update = 1;

	अगर (u->in_transfer_func)
		update_flags->bits.in_transfer_func_change = 1;

	अगर (u->input_csc_color_matrix)
		update_flags->bits.input_csc_change = 1;

	अगर (u->coeff_reduction_factor)
		update_flags->bits.coeff_reduction_change = 1;

	अगर (u->gamut_remap_matrix)
		update_flags->bits.gamut_remap_change = 1;

	अगर (u->gamma) अणु
		क्रमागत surface_pixel_क्रमmat क्रमmat = SURFACE_PIXEL_FORMAT_GRPH_BEGIN;

		अगर (u->plane_info)
			क्रमmat = u->plane_info->क्रमmat;
		अन्यथा अगर (u->surface)
			क्रमmat = u->surface->क्रमmat;

		अगर (dce_use_lut(क्रमmat))
			update_flags->bits.gamma_change = 1;
	पूर्ण

	अगर (u->hdr_mult.value)
		अगर (u->hdr_mult.value != u->surface->hdr_mult.value) अणु
			update_flags->bits.hdr_mult = 1;
			elevate_update_type(&overall_type, UPDATE_TYPE_MED);
		पूर्ण

	अगर (update_flags->bits.in_transfer_func_change) अणु
		type = UPDATE_TYPE_MED;
		elevate_update_type(&overall_type, type);
	पूर्ण

	अगर (update_flags->bits.input_csc_change
			|| update_flags->bits.coeff_reduction_change
			|| update_flags->bits.gamma_change
			|| update_flags->bits.gamut_remap_change) अणु
		type = UPDATE_TYPE_FULL;
		elevate_update_type(&overall_type, type);
	पूर्ण

	वापस overall_type;
पूर्ण

अटल क्रमागत surface_update_type check_update_surfaces_क्रम_stream(
		काष्ठा dc *dc,
		काष्ठा dc_surface_update *updates,
		पूर्णांक surface_count,
		काष्ठा dc_stream_update *stream_update,
		स्थिर काष्ठा dc_stream_status *stream_status)
अणु
	पूर्णांक i;
	क्रमागत surface_update_type overall_type = UPDATE_TYPE_FAST;

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	अगर (dc->idle_optimizations_allowed)
		overall_type = UPDATE_TYPE_FULL;

#पूर्ण_अगर
	अगर (stream_status == शून्य || stream_status->plane_count != surface_count)
		overall_type = UPDATE_TYPE_FULL;

	अगर (stream_update && stream_update->pending_test_pattern) अणु
		overall_type = UPDATE_TYPE_FULL;
	पूर्ण

	/* some stream updates require passive update */
	अगर (stream_update) अणु
		जोड़ stream_update_flags *su_flags = &stream_update->stream->update_flags;

		अगर ((stream_update->src.height != 0 && stream_update->src.width != 0) ||
			(stream_update->dst.height != 0 && stream_update->dst.width != 0) ||
			stream_update->पूर्णांकeger_scaling_update)
			su_flags->bits.scaling = 1;

		अगर (stream_update->out_transfer_func)
			su_flags->bits.out_tf = 1;

		अगर (stream_update->abm_level)
			su_flags->bits.abm_level = 1;

		अगर (stream_update->dpms_off)
			su_flags->bits.dpms_off = 1;

		अगर (stream_update->gamut_remap)
			su_flags->bits.gamut_remap = 1;

		अगर (stream_update->wb_update)
			su_flags->bits.wb_update = 1;

		अगर (stream_update->dsc_config)
			su_flags->bits.dsc_changed = 1;

		अगर (su_flags->raw != 0)
			overall_type = UPDATE_TYPE_FULL;

		अगर (stream_update->output_csc_transक्रमm || stream_update->output_color_space)
			su_flags->bits.out_csc = 1;
	पूर्ण

	क्रम (i = 0 ; i < surface_count; i++) अणु
		क्रमागत surface_update_type type =
				det_surface_update(dc, &updates[i]);

		elevate_update_type(&overall_type, type);
	पूर्ण

	वापस overall_type;
पूर्ण

/*
 * dc_check_update_surfaces_क्रम_stream() - Determine update type (fast, med, or full)
 *
 * See :c:type:`क्रमागत surface_update_type <surface_update_type>` क्रम explanation of update types
 */
क्रमागत surface_update_type dc_check_update_surfaces_क्रम_stream(
		काष्ठा dc *dc,
		काष्ठा dc_surface_update *updates,
		पूर्णांक surface_count,
		काष्ठा dc_stream_update *stream_update,
		स्थिर काष्ठा dc_stream_status *stream_status)
अणु
	पूर्णांक i;
	क्रमागत surface_update_type type;

	अगर (stream_update)
		stream_update->stream->update_flags.raw = 0;
	क्रम (i = 0; i < surface_count; i++)
		updates[i].surface->update_flags.raw = 0;

	type = check_update_surfaces_क्रम_stream(dc, updates, surface_count, stream_update, stream_status);
	अगर (type == UPDATE_TYPE_FULL) अणु
		अगर (stream_update) अणु
			uपूर्णांक32_t dsc_changed = stream_update->stream->update_flags.bits.dsc_changed;
			stream_update->stream->update_flags.raw = 0xFFFFFFFF;
			stream_update->stream->update_flags.bits.dsc_changed = dsc_changed;
		पूर्ण
		क्रम (i = 0; i < surface_count; i++)
			updates[i].surface->update_flags.raw = 0xFFFFFFFF;
	पूर्ण

	अगर (type == UPDATE_TYPE_FAST) अणु
		// If there's an available घड़ी comparator, we use that.
		अगर (dc->clk_mgr->funcs->are_घड़ी_states_equal) अणु
			अगर (!dc->clk_mgr->funcs->are_घड़ी_states_equal(&dc->clk_mgr->clks, &dc->current_state->bw_ctx.bw.dcn.clk))
				dc->optimized_required = true;
		// Else we fallback to mem compare.
		पूर्ण अन्यथा अगर (स_भेद(&dc->current_state->bw_ctx.bw.dcn.clk, &dc->clk_mgr->clks, दुरत्व(काष्ठा dc_घड़ीs, prev_p_state_change_support)) != 0) अणु
			dc->optimized_required = true;
		पूर्ण

		dc->optimized_required |= dc->wm_optimized_required;
	पूर्ण

	वापस type;
पूर्ण

अटल काष्ठा dc_stream_status *stream_get_status(
	काष्ठा dc_state *ctx,
	काष्ठा dc_stream_state *stream)
अणु
	uपूर्णांक8_t i;

	क्रम (i = 0; i < ctx->stream_count; i++) अणु
		अगर (stream == ctx->streams[i]) अणु
			वापस &ctx->stream_status[i];
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल स्थिर क्रमागत surface_update_type update_surface_trace_level = UPDATE_TYPE_FULL;

अटल व्योम copy_surface_update_to_plane(
		काष्ठा dc_plane_state *surface,
		काष्ठा dc_surface_update *srf_update)
अणु
	अगर (srf_update->flip_addr) अणु
		surface->address = srf_update->flip_addr->address;
		surface->flip_immediate =
			srf_update->flip_addr->flip_immediate;
		surface->समय.समय_elapsed_in_us[surface->समय.index] =
			srf_update->flip_addr->flip_बारtamp_in_us -
				surface->समय.prev_update_समय_in_us;
		surface->समय.prev_update_समय_in_us =
			srf_update->flip_addr->flip_बारtamp_in_us;
		surface->समय.index++;
		अगर (surface->समय.index >= DC_PLANE_UPDATE_TIMES_MAX)
			surface->समय.index = 0;

		surface->triplebuffer_flips = srf_update->flip_addr->triplebuffer_flips;
	पूर्ण

	अगर (srf_update->scaling_info) अणु
		surface->scaling_quality =
				srf_update->scaling_info->scaling_quality;
		surface->dst_rect =
				srf_update->scaling_info->dst_rect;
		surface->src_rect =
				srf_update->scaling_info->src_rect;
		surface->clip_rect =
				srf_update->scaling_info->clip_rect;
	पूर्ण

	अगर (srf_update->plane_info) अणु
		surface->color_space =
				srf_update->plane_info->color_space;
		surface->क्रमmat =
				srf_update->plane_info->क्रमmat;
		surface->plane_size =
				srf_update->plane_info->plane_size;
		surface->rotation =
				srf_update->plane_info->rotation;
		surface->horizontal_mirror =
				srf_update->plane_info->horizontal_mirror;
		surface->stereo_क्रमmat =
				srf_update->plane_info->stereo_क्रमmat;
		surface->tiling_info =
				srf_update->plane_info->tiling_info;
		surface->visible =
				srf_update->plane_info->visible;
		surface->per_pixel_alpha =
				srf_update->plane_info->per_pixel_alpha;
		surface->global_alpha =
				srf_update->plane_info->global_alpha;
		surface->global_alpha_value =
				srf_update->plane_info->global_alpha_value;
		surface->dcc =
				srf_update->plane_info->dcc;
		surface->layer_index =
				srf_update->plane_info->layer_index;
	पूर्ण

	अगर (srf_update->gamma &&
			(surface->gamma_correction !=
					srf_update->gamma)) अणु
		स_नकल(&surface->gamma_correction->entries,
			&srf_update->gamma->entries,
			माप(काष्ठा dc_gamma_entries));
		surface->gamma_correction->is_identity =
			srf_update->gamma->is_identity;
		surface->gamma_correction->num_entries =
			srf_update->gamma->num_entries;
		surface->gamma_correction->type =
			srf_update->gamma->type;
	पूर्ण

	अगर (srf_update->in_transfer_func &&
			(surface->in_transfer_func !=
				srf_update->in_transfer_func)) अणु
		surface->in_transfer_func->sdr_ref_white_level =
			srf_update->in_transfer_func->sdr_ref_white_level;
		surface->in_transfer_func->tf =
			srf_update->in_transfer_func->tf;
		surface->in_transfer_func->type =
			srf_update->in_transfer_func->type;
		स_नकल(&surface->in_transfer_func->tf_pts,
			&srf_update->in_transfer_func->tf_pts,
			माप(काष्ठा dc_transfer_func_distributed_poपूर्णांकs));
	पूर्ण

	अगर (srf_update->func_shaper &&
			(surface->in_shaper_func !=
			srf_update->func_shaper))
		स_नकल(surface->in_shaper_func, srf_update->func_shaper,
		माप(*surface->in_shaper_func));

	अगर (srf_update->lut3d_func &&
			(surface->lut3d_func !=
			srf_update->lut3d_func))
		स_नकल(surface->lut3d_func, srf_update->lut3d_func,
		माप(*surface->lut3d_func));

	अगर (srf_update->hdr_mult.value)
		surface->hdr_mult =
				srf_update->hdr_mult;

	अगर (srf_update->blend_tf &&
			(surface->blend_tf !=
			srf_update->blend_tf))
		स_नकल(surface->blend_tf, srf_update->blend_tf,
		माप(*surface->blend_tf));

	अगर (srf_update->input_csc_color_matrix)
		surface->input_csc_color_matrix =
			*srf_update->input_csc_color_matrix;

	अगर (srf_update->coeff_reduction_factor)
		surface->coeff_reduction_factor =
			*srf_update->coeff_reduction_factor;

	अगर (srf_update->gamut_remap_matrix)
		surface->gamut_remap_matrix =
			*srf_update->gamut_remap_matrix;
पूर्ण

अटल व्योम copy_stream_update_to_stream(काष्ठा dc *dc,
					 काष्ठा dc_state *context,
					 काष्ठा dc_stream_state *stream,
					 काष्ठा dc_stream_update *update)
अणु
	काष्ठा dc_context *dc_ctx = dc->ctx;

	अगर (update == शून्य || stream == शून्य)
		वापस;

	अगर (update->src.height && update->src.width)
		stream->src = update->src;

	अगर (update->dst.height && update->dst.width)
		stream->dst = update->dst;

	अगर (update->out_transfer_func &&
	    stream->out_transfer_func != update->out_transfer_func) अणु
		stream->out_transfer_func->sdr_ref_white_level =
			update->out_transfer_func->sdr_ref_white_level;
		stream->out_transfer_func->tf = update->out_transfer_func->tf;
		stream->out_transfer_func->type =
			update->out_transfer_func->type;
		स_नकल(&stream->out_transfer_func->tf_pts,
		       &update->out_transfer_func->tf_pts,
		       माप(काष्ठा dc_transfer_func_distributed_poपूर्णांकs));
	पूर्ण

	अगर (update->hdr_अटल_metadata)
		stream->hdr_अटल_metadata = *update->hdr_अटल_metadata;

	अगर (update->abm_level)
		stream->abm_level = *update->abm_level;

	अगर (update->periodic_पूर्णांकerrupt0)
		stream->periodic_पूर्णांकerrupt0 = *update->periodic_पूर्णांकerrupt0;

	अगर (update->periodic_पूर्णांकerrupt1)
		stream->periodic_पूर्णांकerrupt1 = *update->periodic_पूर्णांकerrupt1;

	अगर (update->gamut_remap)
		stream->gamut_remap_matrix = *update->gamut_remap;

	/* Note: this being updated after mode set is currently not a use हाल
	 * however अगर it arises OCSC would need to be reprogrammed at the
	 * minimum
	 */
	अगर (update->output_color_space)
		stream->output_color_space = *update->output_color_space;

	अगर (update->output_csc_transक्रमm)
		stream->csc_color_matrix = *update->output_csc_transक्रमm;

	अगर (update->vrr_infopacket)
		stream->vrr_infopacket = *update->vrr_infopacket;

	अगर (update->dpms_off)
		stream->dpms_off = *update->dpms_off;

	अगर (update->vsc_infopacket)
		stream->vsc_infopacket = *update->vsc_infopacket;

	अगर (update->vsp_infopacket)
		stream->vsp_infopacket = *update->vsp_infopacket;

	अगर (update->dither_option)
		stream->dither_option = *update->dither_option;

	अगर (update->pending_test_pattern)
		stream->test_pattern = *update->pending_test_pattern;
	/* update current stream with ग_लिखोback info */
	अगर (update->wb_update) अणु
		पूर्णांक i;

		stream->num_wb_info = update->wb_update->num_wb_info;
		ASSERT(stream->num_wb_info <= MAX_DWB_PIPES);
		क्रम (i = 0; i < stream->num_wb_info; i++)
			stream->ग_लिखोback_info[i] =
				update->wb_update->ग_लिखोback_info[i];
	पूर्ण
	अगर (update->dsc_config) अणु
		काष्ठा dc_dsc_config old_dsc_cfg = stream->timing.dsc_cfg;
		uपूर्णांक32_t old_dsc_enabled = stream->timing.flags.DSC;
		uपूर्णांक32_t enable_dsc = (update->dsc_config->num_slices_h != 0 &&
				       update->dsc_config->num_slices_v != 0);

		/* Use temporarry context क्रम validating new DSC config */
		काष्ठा dc_state *dsc_validate_context = dc_create_state(dc);

		अगर (dsc_validate_context) अणु
			dc_resource_state_copy_स्थिरruct(dc->current_state, dsc_validate_context);

			stream->timing.dsc_cfg = *update->dsc_config;
			stream->timing.flags.DSC = enable_dsc;
			अगर (!dc->res_pool->funcs->validate_bandwidth(dc, dsc_validate_context, true)) अणु
				stream->timing.dsc_cfg = old_dsc_cfg;
				stream->timing.flags.DSC = old_dsc_enabled;
				update->dsc_config = शून्य;
			पूर्ण

			dc_release_state(dsc_validate_context);
		पूर्ण अन्यथा अणु
			DC_ERROR("Failed to allocate new validate context for DSC change\n");
			update->dsc_config = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम commit_planes_करो_stream_update(काष्ठा dc *dc,
		काष्ठा dc_stream_state *stream,
		काष्ठा dc_stream_update *stream_update,
		क्रमागत surface_update_type update_type,
		काष्ठा dc_state *context)
अणु
	पूर्णांक j;

	// Stream updates
	क्रम (j = 0; j < dc->res_pool->pipe_count; j++) अणु
		काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[j];

		अगर (!pipe_ctx->top_pipe &&  !pipe_ctx->prev_odm_pipe && pipe_ctx->stream == stream) अणु

			अगर (stream_update->periodic_पूर्णांकerrupt0 &&
					dc->hwss.setup_periodic_पूर्णांकerrupt)
				dc->hwss.setup_periodic_पूर्णांकerrupt(dc, pipe_ctx, VLINE0);

			अगर (stream_update->periodic_पूर्णांकerrupt1 &&
					dc->hwss.setup_periodic_पूर्णांकerrupt)
				dc->hwss.setup_periodic_पूर्णांकerrupt(dc, pipe_ctx, VLINE1);

			अगर ((stream_update->hdr_अटल_metadata && !stream->use_dynamic_meta) ||
					stream_update->vrr_infopacket ||
					stream_update->vsc_infopacket ||
					stream_update->vsp_infopacket) अणु
				resource_build_info_frame(pipe_ctx);
				dc->hwss.update_info_frame(pipe_ctx);
			पूर्ण

			अगर (stream_update->hdr_अटल_metadata &&
					stream->use_dynamic_meta &&
					dc->hwss.set_dmdata_attributes &&
					pipe_ctx->stream->dmdata_address.quad_part != 0)
				dc->hwss.set_dmdata_attributes(pipe_ctx);

			अगर (stream_update->gamut_remap)
				dc_stream_set_gamut_remap(dc, stream);

			अगर (stream_update->output_csc_transक्रमm)
				dc_stream_program_csc_matrix(dc, stream);

			अगर (stream_update->dither_option) अणु
				काष्ठा pipe_ctx *odm_pipe = pipe_ctx->next_odm_pipe;
				resource_build_bit_depth_reduction_params(pipe_ctx->stream,
									&pipe_ctx->stream->bit_depth_params);
				pipe_ctx->stream_res.opp->funcs->opp_program_fmt(pipe_ctx->stream_res.opp,
						&stream->bit_depth_params,
						&stream->clamping);
				जबतक (odm_pipe) अणु
					odm_pipe->stream_res.opp->funcs->opp_program_fmt(odm_pipe->stream_res.opp,
							&stream->bit_depth_params,
							&stream->clamping);
					odm_pipe = odm_pipe->next_odm_pipe;
				पूर्ण
			पूर्ण


			/* Full fe update*/
			अगर (update_type == UPDATE_TYPE_FAST)
				जारी;

			अगर (stream_update->dsc_config)
				dp_update_dsc_config(pipe_ctx);

			अगर (stream_update->pending_test_pattern) अणु
				dc_link_dp_set_test_pattern(stream->link,
					stream->test_pattern.type,
					stream->test_pattern.color_space,
					stream->test_pattern.p_link_settings,
					stream->test_pattern.p_custom_pattern,
					stream->test_pattern.cust_pattern_size);
			पूर्ण

			अगर (stream_update->dpms_off) अणु
				अगर (*stream_update->dpms_off) अणु
					core_link_disable_stream(pipe_ctx);
					/* क्रम dpms, keep acquired resources*/
					अगर (pipe_ctx->stream_res.audio && !dc->debug.az_endpoपूर्णांक_mute_only)
						pipe_ctx->stream_res.audio->funcs->az_disable(pipe_ctx->stream_res.audio);

					dc->optimized_required = true;

				पूर्ण अन्यथा अणु
					अगर (get_seamless_boot_stream_count(context) == 0)
						dc->hwss.prepare_bandwidth(dc, dc->current_state);

					core_link_enable_stream(dc->current_state, pipe_ctx);
				पूर्ण
			पूर्ण

			अगर (stream_update->abm_level && pipe_ctx->stream_res.abm) अणु
				bool should_program_abm = true;

				// अगर otg funcs defined check अगर blanked beक्रमe programming
				अगर (pipe_ctx->stream_res.tg->funcs->is_blanked)
					अगर (pipe_ctx->stream_res.tg->funcs->is_blanked(pipe_ctx->stream_res.tg))
						should_program_abm = false;

				अगर (should_program_abm) अणु
					अगर (*stream_update->abm_level == ABM_LEVEL_IMMEDIATE_DISABLE) अणु
						dc->hwss.set_abm_immediate_disable(pipe_ctx);
					पूर्ण अन्यथा अणु
						pipe_ctx->stream_res.abm->funcs->set_abm_level(
							pipe_ctx->stream_res.abm, stream->abm_level);
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम commit_planes_क्रम_stream(काष्ठा dc *dc,
		काष्ठा dc_surface_update *srf_updates,
		पूर्णांक surface_count,
		काष्ठा dc_stream_state *stream,
		काष्ठा dc_stream_update *stream_update,
		क्रमागत surface_update_type update_type,
		काष्ठा dc_state *context)
अणु
	पूर्णांक i, j;
	काष्ठा pipe_ctx *top_pipe_to_program = शून्य;

	अगर (get_seamless_boot_stream_count(context) > 0 && surface_count > 0) अणु
		/* Optimize seamless boot flag keeps घड़ीs and watermarks high until
		 * first flip. After first flip, optimization is required to lower
		 * bandwidth. Important to note that it is expected UEFI will
		 * only light up a single display on POST, thereक्रमe we only expect
		 * one stream with seamless boot flag set.
		 */
		अगर (stream->apply_seamless_boot_optimization) अणु
			stream->apply_seamless_boot_optimization = false;

			अगर (get_seamless_boot_stream_count(context) == 0)
				dc->optimized_required = true;
		पूर्ण
	पूर्ण

	अगर (update_type == UPDATE_TYPE_FULL) अणु
#अगर defined(CONFIG_DRM_AMD_DC_DCN)
		dc_allow_idle_optimizations(dc, false);

#पूर्ण_अगर
		अगर (get_seamless_boot_stream_count(context) == 0)
			dc->hwss.prepare_bandwidth(dc, context);

		context_घड़ी_प्रकारrace(dc, context);
	पूर्ण

	क्रम (j = 0; j < dc->res_pool->pipe_count; j++) अणु
		काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[j];

		अगर (!pipe_ctx->top_pipe &&
			!pipe_ctx->prev_odm_pipe &&
			pipe_ctx->stream &&
			pipe_ctx->stream == stream) अणु
			top_pipe_to_program = pipe_ctx;
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_DRM_AMD_DC_DCN
	अगर (stream->test_pattern.type != DP_TEST_PATTERN_VIDEO_MODE) अणु
		काष्ठा pipe_ctx *mpcc_pipe;
		काष्ठा pipe_ctx *odm_pipe;

		क्रम (mpcc_pipe = top_pipe_to_program; mpcc_pipe; mpcc_pipe = mpcc_pipe->bottom_pipe)
			क्रम (odm_pipe = mpcc_pipe; odm_pipe; odm_pipe = odm_pipe->next_odm_pipe)
				odm_pipe->ttu_regs.min_ttu_vblank = MAX_TTU;
	पूर्ण
#पूर्ण_अगर

	अगर ((update_type != UPDATE_TYPE_FAST) && stream->update_flags.bits.dsc_changed)
		अगर (top_pipe_to_program->stream_res.tg->funcs->lock_द्विगुनbuffer_enable) अणु
			अगर (should_use_dmub_lock(stream->link)) अणु
				जोड़ dmub_hw_lock_flags hw_locks = अणु 0 पूर्ण;
				काष्ठा dmub_hw_lock_inst_flags inst_flags = अणु 0 पूर्ण;

				hw_locks.bits.lock_dig = 1;
				inst_flags.dig_inst = top_pipe_to_program->stream_res.tg->inst;

				dmub_hw_lock_mgr_cmd(dc->ctx->dmub_srv,
							true,
							&hw_locks,
							&inst_flags);
			पूर्ण अन्यथा
				top_pipe_to_program->stream_res.tg->funcs->lock_द्विगुनbuffer_enable(
						top_pipe_to_program->stream_res.tg);
		पूर्ण

	अगर ((update_type != UPDATE_TYPE_FAST) && dc->hwss.पूर्णांकerdependent_update_lock)
		dc->hwss.पूर्णांकerdependent_update_lock(dc, context, true);
	अन्यथा
		/* Lock the top pipe जबतक updating plane addrs, since मुक्तsync requires
		 *  plane addr update event triggers to be synchronized.
		 *  top_pipe_to_program is expected to never be शून्य
		 */
		dc->hwss.pipe_control_lock(dc, top_pipe_to_program, true);

	// Stream updates
	अगर (stream_update)
		commit_planes_करो_stream_update(dc, stream, stream_update, update_type, context);

	अगर (surface_count == 0) अणु
		/*
		 * In हाल of turning off screen, no need to program front end a second समय.
		 * just वापस after program blank.
		 */
		अगर (dc->hwss.apply_ctx_क्रम_surface)
			dc->hwss.apply_ctx_क्रम_surface(dc, stream, 0, context);
		अगर (dc->hwss.program_front_end_क्रम_ctx)
			dc->hwss.program_front_end_क्रम_ctx(dc, context);

		अगर ((update_type != UPDATE_TYPE_FAST) && dc->hwss.पूर्णांकerdependent_update_lock)
			dc->hwss.पूर्णांकerdependent_update_lock(dc, context, false);
		अन्यथा
			dc->hwss.pipe_control_lock(dc, top_pipe_to_program, false);

		dc->hwss.post_unlock_program_front_end(dc, context);
		वापस;
	पूर्ण

	अगर (!IS_DIAG_DC(dc->ctx->dce_environment)) अणु
		क्रम (i = 0; i < surface_count; i++) अणु
			काष्ठा dc_plane_state *plane_state = srf_updates[i].surface;
			/*set logical flag क्रम lock/unlock use*/
			क्रम (j = 0; j < dc->res_pool->pipe_count; j++) अणु
				काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[j];
				अगर (!pipe_ctx->plane_state)
					जारी;
				अगर (pipe_ctx->plane_state != plane_state)
					जारी;
				plane_state->triplebuffer_flips = false;
				अगर (update_type == UPDATE_TYPE_FAST &&
					dc->hwss.program_triplebuffer != शून्य &&
					!plane_state->flip_immediate && dc->debug.enable_tri_buf) अणु
						/*triple buffer क्रम VUpdate  only*/
						plane_state->triplebuffer_flips = true;
				पूर्ण
			पूर्ण
			अगर (update_type == UPDATE_TYPE_FULL) अणु
				/* क्रमce vsync flip when reconfiguring pipes to prevent underflow */
				plane_state->flip_immediate = false;
			पूर्ण
		पूर्ण
	पूर्ण

	// Update Type FULL, Surface updates
	क्रम (j = 0; j < dc->res_pool->pipe_count; j++) अणु
		काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[j];

		अगर (!pipe_ctx->top_pipe &&
			!pipe_ctx->prev_odm_pipe &&
			pipe_ctx->stream &&
			pipe_ctx->stream == stream) अणु
			काष्ठा dc_stream_status *stream_status = शून्य;

			अगर (!pipe_ctx->plane_state)
				जारी;

			/* Full fe update*/
			अगर (update_type == UPDATE_TYPE_FAST)
				जारी;

			ASSERT(!pipe_ctx->plane_state->triplebuffer_flips);

			अगर (dc->hwss.program_triplebuffer != शून्य && dc->debug.enable_tri_buf) अणु
				/*turn off triple buffer क्रम full update*/
				dc->hwss.program_triplebuffer(
					dc, pipe_ctx, pipe_ctx->plane_state->triplebuffer_flips);
			पूर्ण
			stream_status =
				stream_get_status(context, pipe_ctx->stream);

			अगर (dc->hwss.apply_ctx_क्रम_surface)
				dc->hwss.apply_ctx_क्रम_surface(
					dc, pipe_ctx->stream, stream_status->plane_count, context);
		पूर्ण
	पूर्ण
	अगर (dc->hwss.program_front_end_क्रम_ctx && update_type != UPDATE_TYPE_FAST) अणु
		dc->hwss.program_front_end_क्रम_ctx(dc, context);
#अगर_घोषित CONFIG_DRM_AMD_DC_DCN
		अगर (dc->debug.validate_dml_output) अणु
			क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
				काष्ठा pipe_ctx cur_pipe = context->res_ctx.pipe_ctx[i];
				अगर (cur_pipe.stream == शून्य)
					जारी;

				cur_pipe.plane_res.hubp->funcs->validate_dml_output(
						cur_pipe.plane_res.hubp, dc->ctx,
						&context->res_ctx.pipe_ctx[i].rq_regs,
						&context->res_ctx.pipe_ctx[i].dlg_regs,
						&context->res_ctx.pipe_ctx[i].ttu_regs);
			पूर्ण
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	// Update Type FAST, Surface updates
	अगर (update_type == UPDATE_TYPE_FAST) अणु
		अगर (dc->hwss.set_flip_control_gsl)
			क्रम (i = 0; i < surface_count; i++) अणु
				काष्ठा dc_plane_state *plane_state = srf_updates[i].surface;

				क्रम (j = 0; j < dc->res_pool->pipe_count; j++) अणु
					काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[j];

					अगर (pipe_ctx->stream != stream)
						जारी;

					अगर (pipe_ctx->plane_state != plane_state)
						जारी;

					// GSL has to be used क्रम flip immediate
					dc->hwss.set_flip_control_gsl(pipe_ctx,
							plane_state->flip_immediate);
				पूर्ण
			पूर्ण
		/* Perक्रमm requested Updates */
		क्रम (i = 0; i < surface_count; i++) अणु
			काष्ठा dc_plane_state *plane_state = srf_updates[i].surface;

			क्रम (j = 0; j < dc->res_pool->pipe_count; j++) अणु
				काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[j];

				अगर (pipe_ctx->stream != stream)
					जारी;

				अगर (pipe_ctx->plane_state != plane_state)
					जारी;
				/*program triple buffer after lock based on flip type*/
				अगर (dc->hwss.program_triplebuffer != शून्य && dc->debug.enable_tri_buf) अणु
					/*only enable triplebuffer क्रम  fast_update*/
					dc->hwss.program_triplebuffer(
						dc, pipe_ctx, plane_state->triplebuffer_flips);
				पूर्ण
				अगर (srf_updates[i].flip_addr)
					dc->hwss.update_plane_addr(dc, pipe_ctx);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर ((update_type != UPDATE_TYPE_FAST) && dc->hwss.पूर्णांकerdependent_update_lock)
		dc->hwss.पूर्णांकerdependent_update_lock(dc, context, false);
	अन्यथा
		dc->hwss.pipe_control_lock(dc, top_pipe_to_program, false);

	अगर ((update_type != UPDATE_TYPE_FAST) && stream->update_flags.bits.dsc_changed)
		अगर (top_pipe_to_program->stream_res.tg->funcs->lock_द्विगुनbuffer_enable) अणु
			top_pipe_to_program->stream_res.tg->funcs->रुको_क्रम_state(
					top_pipe_to_program->stream_res.tg,
					CRTC_STATE_VACTIVE);
			top_pipe_to_program->stream_res.tg->funcs->रुको_क्रम_state(
					top_pipe_to_program->stream_res.tg,
					CRTC_STATE_VBLANK);
			top_pipe_to_program->stream_res.tg->funcs->रुको_क्रम_state(
					top_pipe_to_program->stream_res.tg,
					CRTC_STATE_VACTIVE);

			अगर (stream && should_use_dmub_lock(stream->link)) अणु
				जोड़ dmub_hw_lock_flags hw_locks = अणु 0 पूर्ण;
				काष्ठा dmub_hw_lock_inst_flags inst_flags = अणु 0 पूर्ण;

				hw_locks.bits.lock_dig = 1;
				inst_flags.dig_inst = top_pipe_to_program->stream_res.tg->inst;

				dmub_hw_lock_mgr_cmd(dc->ctx->dmub_srv,
							false,
							&hw_locks,
							&inst_flags);
			पूर्ण अन्यथा
				top_pipe_to_program->stream_res.tg->funcs->lock_द्विगुनbuffer_disable(
					top_pipe_to_program->stream_res.tg);
		पूर्ण

	अगर (update_type != UPDATE_TYPE_FAST)
		dc->hwss.post_unlock_program_front_end(dc, context);

	// Fire manual trigger only when bottom plane is flipped
	क्रम (j = 0; j < dc->res_pool->pipe_count; j++) अणु
		काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[j];

		अगर (!pipe_ctx->plane_state)
			जारी;

		अगर (pipe_ctx->bottom_pipe || pipe_ctx->next_odm_pipe ||
				!pipe_ctx->stream || pipe_ctx->stream != stream ||
				!pipe_ctx->plane_state->update_flags.bits.addr_update ||
				pipe_ctx->plane_state->skip_manual_trigger)
			जारी;

		अगर (pipe_ctx->stream_res.tg->funcs->program_manual_trigger)
			pipe_ctx->stream_res.tg->funcs->program_manual_trigger(pipe_ctx->stream_res.tg);
	पूर्ण
पूर्ण

व्योम dc_commit_updates_क्रम_stream(काष्ठा dc *dc,
		काष्ठा dc_surface_update *srf_updates,
		पूर्णांक surface_count,
		काष्ठा dc_stream_state *stream,
		काष्ठा dc_stream_update *stream_update,
		काष्ठा dc_state *state)
अणु
	स्थिर काष्ठा dc_stream_status *stream_status;
	क्रमागत surface_update_type update_type;
	काष्ठा dc_state *context;
	काष्ठा dc_context *dc_ctx = dc->ctx;
	पूर्णांक i, j;

	stream_status = dc_stream_get_status(stream);
	context = dc->current_state;

	update_type = dc_check_update_surfaces_क्रम_stream(
				dc, srf_updates, surface_count, stream_update, stream_status);

	अगर (update_type >= update_surface_trace_level)
		update_surface_trace(dc, srf_updates, surface_count);


	अगर (update_type >= UPDATE_TYPE_FULL) अणु

		/* initialize scratch memory क्रम building context */
		context = dc_create_state(dc);
		अगर (context == शून्य) अणु
			DC_ERROR("Failed to allocate new validate context!\n");
			वापस;
		पूर्ण

		dc_resource_state_copy_स्थिरruct(state, context);

		क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
			काष्ठा pipe_ctx *new_pipe = &context->res_ctx.pipe_ctx[i];
			काष्ठा pipe_ctx *old_pipe = &dc->current_state->res_ctx.pipe_ctx[i];

			अगर (new_pipe->plane_state && new_pipe->plane_state != old_pipe->plane_state)
				new_pipe->plane_state->क्रमce_full_update = true;
		पूर्ण
	पूर्ण


	क्रम (i = 0; i < surface_count; i++) अणु
		काष्ठा dc_plane_state *surface = srf_updates[i].surface;

		copy_surface_update_to_plane(surface, &srf_updates[i]);

		अगर (update_type >= UPDATE_TYPE_MED) अणु
			क्रम (j = 0; j < dc->res_pool->pipe_count; j++) अणु
				काष्ठा pipe_ctx *pipe_ctx =
					&context->res_ctx.pipe_ctx[j];

				अगर (pipe_ctx->plane_state != surface)
					जारी;

				resource_build_scaling_params(pipe_ctx);
			पूर्ण
		पूर्ण
	पूर्ण

	copy_stream_update_to_stream(dc, context, stream, stream_update);

	अगर (update_type >= UPDATE_TYPE_FULL) अणु
		अगर (!dc->res_pool->funcs->validate_bandwidth(dc, context, false)) अणु
			DC_ERROR("Mode validation failed for stream update!\n");
			dc_release_state(context);
			वापस;
		पूर्ण
	पूर्ण

	TRACE_DC_PIPE_STATE(pipe_ctx, i, MAX_PIPES);

	commit_planes_क्रम_stream(
				dc,
				srf_updates,
				surface_count,
				stream,
				stream_update,
				update_type,
				context);
	/*update current_State*/
	अगर (dc->current_state != context) अणु

		काष्ठा dc_state *old = dc->current_state;

		dc->current_state = context;
		dc_release_state(old);

		क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
			काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];

			अगर (pipe_ctx->plane_state && pipe_ctx->stream == stream)
				pipe_ctx->plane_state->क्रमce_full_update = false;
		पूर्ण
	पूर्ण
	/*let's use current_state to update watermark etc*/
	अगर (update_type >= UPDATE_TYPE_FULL) अणु
		dc_post_update_surfaces_to_stream(dc);

		अगर (dc_ctx->dce_version >= DCE_VERSION_MAX)
			TRACE_DCN_CLOCK_STATE(&context->bw_ctx.bw.dcn.clk);
		अन्यथा
			TRACE_DCE_CLOCK_STATE(&context->bw_ctx.bw.dce);
	पूर्ण

	वापस;

पूर्ण

uपूर्णांक8_t dc_get_current_stream_count(काष्ठा dc *dc)
अणु
	वापस dc->current_state->stream_count;
पूर्ण

काष्ठा dc_stream_state *dc_get_stream_at_index(काष्ठा dc *dc, uपूर्णांक8_t i)
अणु
	अगर (i < dc->current_state->stream_count)
		वापस dc->current_state->streams[i];
	वापस शून्य;
पूर्ण

काष्ठा dc_stream_state *dc_stream_find_from_link(स्थिर काष्ठा dc_link *link)
अणु
	uपूर्णांक8_t i;
	काष्ठा dc_context *ctx = link->ctx;

	क्रम (i = 0; i < ctx->dc->current_state->stream_count; i++) अणु
		अगर (ctx->dc->current_state->streams[i]->link == link)
			वापस ctx->dc->current_state->streams[i];
	पूर्ण

	वापस शून्य;
पूर्ण

क्रमागत dc_irq_source dc_पूर्णांकerrupt_to_irq_source(
		काष्ठा dc *dc,
		uपूर्णांक32_t src_id,
		uपूर्णांक32_t ext_id)
अणु
	वापस dal_irq_service_to_irq_source(dc->res_pool->irqs, src_id, ext_id);
पूर्ण

/*
 * dc_पूर्णांकerrupt_set() - Enable/disable an AMD hw पूर्णांकerrupt source
 */
bool dc_पूर्णांकerrupt_set(काष्ठा dc *dc, क्रमागत dc_irq_source src, bool enable)
अणु

	अगर (dc == शून्य)
		वापस false;

	वापस dal_irq_service_set(dc->res_pool->irqs, src, enable);
पूर्ण

व्योम dc_पूर्णांकerrupt_ack(काष्ठा dc *dc, क्रमागत dc_irq_source src)
अणु
	dal_irq_service_ack(dc->res_pool->irqs, src);
पूर्ण

व्योम dc_घातer_करोwn_on_boot(काष्ठा dc *dc)
अणु
	अगर (dc->ctx->dce_environment != DCE_ENV_VIRTUAL_HW &&
			dc->hwss.घातer_करोwn_on_boot)
		dc->hwss.घातer_करोwn_on_boot(dc);
पूर्ण

व्योम dc_set_घातer_state(
	काष्ठा dc *dc,
	क्रमागत dc_acpi_cm_घातer_state घातer_state)
अणु
	काष्ठा kref refcount;
	काष्ठा display_mode_lib *dml;

	अगर (!dc->current_state)
		वापस;

	चयन (घातer_state) अणु
	हाल DC_ACPI_CM_POWER_STATE_D0:
		dc_resource_state_स्थिरruct(dc, dc->current_state);

		अगर (dc->ctx->dmub_srv)
			dc_dmub_srv_रुको_phy_init(dc->ctx->dmub_srv);

		dc->hwss.init_hw(dc);

		अगर (dc->hwss.init_sys_ctx != शून्य &&
			dc->vm_pa_config.valid) अणु
			dc->hwss.init_sys_ctx(dc->hwseq, dc, &dc->vm_pa_config);
		पूर्ण

		अवरोध;
	शेष:
		ASSERT(dc->current_state->stream_count == 0);
		/* Zero out the current context so that on resume we start with
		 * clean state, and dc hw programming optimizations will not
		 * cause any trouble.
		 */
		dml = kzalloc(माप(काष्ठा display_mode_lib),
				GFP_KERNEL);

		ASSERT(dml);
		अगर (!dml)
			वापस;

		/* Preserve refcount */
		refcount = dc->current_state->refcount;
		/* Preserve display mode lib */
		स_नकल(dml, &dc->current_state->bw_ctx.dml, माप(काष्ठा display_mode_lib));

		dc_resource_state_deकाष्ठा(dc->current_state);
		स_रखो(dc->current_state, 0,
				माप(*dc->current_state));

		dc->current_state->refcount = refcount;
		dc->current_state->bw_ctx.dml = *dml;

		kमुक्त(dml);

		अवरोध;
	पूर्ण
पूर्ण

व्योम dc_resume(काष्ठा dc *dc)
अणु
	uपूर्णांक32_t i;

	क्रम (i = 0; i < dc->link_count; i++)
		core_link_resume(dc->links[i]);
पूर्ण

bool dc_is_dmcu_initialized(काष्ठा dc *dc)
अणु
	काष्ठा dmcu *dmcu = dc->res_pool->dmcu;

	अगर (dmcu)
		वापस dmcu->funcs->is_dmcu_initialized(dmcu);
	वापस false;
पूर्ण

bool dc_submit_i2c(
		काष्ठा dc *dc,
		uपूर्णांक32_t link_index,
		काष्ठा i2c_command *cmd)
अणु

	काष्ठा dc_link *link = dc->links[link_index];
	काष्ठा ddc_service *ddc = link->ddc;
	वापस dce_i2c_submit_command(
		dc->res_pool,
		ddc->ddc_pin,
		cmd);
पूर्ण

bool dc_submit_i2c_oem(
		काष्ठा dc *dc,
		काष्ठा i2c_command *cmd)
अणु
	काष्ठा ddc_service *ddc = dc->res_pool->oem_device;
	वापस dce_i2c_submit_command(
		dc->res_pool,
		ddc->ddc_pin,
		cmd);
पूर्ण

अटल bool link_add_remote_sink_helper(काष्ठा dc_link *dc_link, काष्ठा dc_sink *sink)
अणु
	अगर (dc_link->sink_count >= MAX_SINKS_PER_LINK) अणु
		BREAK_TO_DEBUGGER();
		वापस false;
	पूर्ण

	dc_sink_retain(sink);

	dc_link->remote_sinks[dc_link->sink_count] = sink;
	dc_link->sink_count++;

	वापस true;
पूर्ण

/*
 * dc_link_add_remote_sink() - Create a sink and attach it to an existing link
 *
 * EDID length is in bytes
 */
काष्ठा dc_sink *dc_link_add_remote_sink(
		काष्ठा dc_link *link,
		स्थिर uपूर्णांक8_t *edid,
		पूर्णांक len,
		काष्ठा dc_sink_init_data *init_data)
अणु
	काष्ठा dc_sink *dc_sink;
	क्रमागत dc_edid_status edid_status;

	अगर (len > DC_MAX_EDID_BUFFER_SIZE) अणु
		dm_error("Max EDID buffer size breached!\n");
		वापस शून्य;
	पूर्ण

	अगर (!init_data) अणु
		BREAK_TO_DEBUGGER();
		वापस शून्य;
	पूर्ण

	अगर (!init_data->link) अणु
		BREAK_TO_DEBUGGER();
		वापस शून्य;
	पूर्ण

	dc_sink = dc_sink_create(init_data);

	अगर (!dc_sink)
		वापस शून्य;

	स_हटाओ(dc_sink->dc_edid.raw_edid, edid, len);
	dc_sink->dc_edid.length = len;

	अगर (!link_add_remote_sink_helper(
			link,
			dc_sink))
		जाओ fail_add_sink;

	edid_status = dm_helpers_parse_edid_caps(
			link->ctx,
			&dc_sink->dc_edid,
			&dc_sink->edid_caps);

	/*
	 * Treat device as no EDID device अगर EDID
	 * parsing fails
	 */
	अगर (edid_status != EDID_OK) अणु
		dc_sink->dc_edid.length = 0;
		dm_error("Bad EDID, status%d!\n", edid_status);
	पूर्ण

	वापस dc_sink;

fail_add_sink:
	dc_sink_release(dc_sink);
	वापस शून्य;
पूर्ण

/*
 * dc_link_हटाओ_remote_sink() - Remove a remote sink from a dc_link
 *
 * Note that this just हटाओs the काष्ठा dc_sink - it करोesn't
 * program hardware or alter other members of dc_link
 */
व्योम dc_link_हटाओ_remote_sink(काष्ठा dc_link *link, काष्ठा dc_sink *sink)
अणु
	पूर्णांक i;

	अगर (!link->sink_count) अणु
		BREAK_TO_DEBUGGER();
		वापस;
	पूर्ण

	क्रम (i = 0; i < link->sink_count; i++) अणु
		अगर (link->remote_sinks[i] == sink) अणु
			dc_sink_release(sink);
			link->remote_sinks[i] = शून्य;

			/* shrink array to हटाओ empty place */
			जबतक (i < link->sink_count - 1) अणु
				link->remote_sinks[i] = link->remote_sinks[i+1];
				i++;
			पूर्ण
			link->remote_sinks[i] = शून्य;
			link->sink_count--;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

व्योम dc_रुको_क्रम_vblank(काष्ठा dc *dc, काष्ठा dc_stream_state *stream)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < dc->res_pool->pipe_count; i++)
		अगर (dc->current_state->res_ctx.pipe_ctx[i].stream == stream) अणु
			काष्ठा timing_generator *tg =
				dc->current_state->res_ctx.pipe_ctx[i].stream_res.tg;
			tg->funcs->रुको_क्रम_state(tg, CRTC_STATE_VBLANK);
			अवरोध;
		पूर्ण
पूर्ण

व्योम get_घड़ी_requirements_क्रम_state(काष्ठा dc_state *state, काष्ठा AsicStateEx *info)
अणु
	info->displayClock				= (अचिन्हित पूर्णांक)state->bw_ctx.bw.dcn.clk.dispclk_khz;
	info->engineClock				= (अचिन्हित पूर्णांक)state->bw_ctx.bw.dcn.clk.dcfclk_khz;
	info->memoryClock				= (अचिन्हित पूर्णांक)state->bw_ctx.bw.dcn.clk.dramclk_khz;
	info->maxSupportedDppClock		= (अचिन्हित पूर्णांक)state->bw_ctx.bw.dcn.clk.max_supported_dppclk_khz;
	info->dppClock					= (अचिन्हित पूर्णांक)state->bw_ctx.bw.dcn.clk.dppclk_khz;
	info->socClock					= (अचिन्हित पूर्णांक)state->bw_ctx.bw.dcn.clk.socclk_khz;
	info->dcfClockDeepSleep			= (अचिन्हित पूर्णांक)state->bw_ctx.bw.dcn.clk.dcfclk_deep_sleep_khz;
	info->fClock					= (अचिन्हित पूर्णांक)state->bw_ctx.bw.dcn.clk.fclk_khz;
	info->phyClock					= (अचिन्हित पूर्णांक)state->bw_ctx.bw.dcn.clk.phyclk_khz;
पूर्ण
क्रमागत dc_status dc_set_घड़ी(काष्ठा dc *dc, क्रमागत dc_घड़ी_प्रकारype घड़ी_प्रकारype, uपूर्णांक32_t clk_khz, uपूर्णांक32_t stepping)
अणु
	अगर (dc->hwss.set_घड़ी)
		वापस dc->hwss.set_घड़ी(dc, घड़ी_प्रकारype, clk_khz, stepping);
	वापस DC_ERROR_UNEXPECTED;
पूर्ण
व्योम dc_get_घड़ी(काष्ठा dc *dc, क्रमागत dc_घड़ी_प्रकारype घड़ी_प्रकारype, काष्ठा dc_घड़ी_config *घड़ी_cfg)
अणु
	अगर (dc->hwss.get_घड़ी)
		dc->hwss.get_घड़ी(dc, घड़ी_प्रकारype, घड़ी_cfg);
पूर्ण

/* enable/disable eDP PSR without specअगरy stream क्रम eDP */
bool dc_set_psr_allow_active(काष्ठा dc *dc, bool enable)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < dc->current_state->stream_count ; i++) अणु
		काष्ठा dc_link *link;
		काष्ठा dc_stream_state *stream = dc->current_state->streams[i];

		link = stream->link;
		अगर (!link)
			जारी;

		अगर (link->psr_settings.psr_feature_enabled) अणु
			अगर (enable && !link->psr_settings.psr_allow_active)
				वापस dc_link_set_psr_allow_active(link, true, false, false);
			अन्यथा अगर (!enable && link->psr_settings.psr_allow_active)
				वापस dc_link_set_psr_allow_active(link, false, true, false);
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_DCN)

व्योम dc_allow_idle_optimizations(काष्ठा dc *dc, bool allow)
अणु
	अगर (dc->debug.disable_idle_घातer_optimizations)
		वापस;

	अगर (dc->clk_mgr->funcs->is_smu_present)
		अगर (!dc->clk_mgr->funcs->is_smu_present(dc->clk_mgr))
			वापस;

	अगर (allow == dc->idle_optimizations_allowed)
		वापस;

	अगर (dc->hwss.apply_idle_घातer_optimizations && dc->hwss.apply_idle_घातer_optimizations(dc, allow))
		dc->idle_optimizations_allowed = allow;
पूर्ण

/*
 * blank all streams, and set min and max memory घड़ी to
 * lowest and highest DPM level, respectively
 */
व्योम dc_unlock_memory_घड़ी_frequency(काष्ठा dc *dc)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < MAX_PIPES; i++)
		अगर (dc->current_state->res_ctx.pipe_ctx[i].plane_state)
			core_link_disable_stream(&dc->current_state->res_ctx.pipe_ctx[i]);

	dc->clk_mgr->funcs->set_hard_min_memclk(dc->clk_mgr, false);
	dc->clk_mgr->funcs->set_hard_max_memclk(dc->clk_mgr);
पूर्ण

/*
 * set min memory घड़ी to the min required क्रम current mode,
 * max to maxDPM, and unblank streams
 */
व्योम dc_lock_memory_घड़ी_frequency(काष्ठा dc *dc)
अणु
	अचिन्हित पूर्णांक i;

	dc->clk_mgr->funcs->get_memclk_states_from_smu(dc->clk_mgr);
	dc->clk_mgr->funcs->set_hard_min_memclk(dc->clk_mgr, true);
	dc->clk_mgr->funcs->set_hard_max_memclk(dc->clk_mgr);

	क्रम (i = 0; i < MAX_PIPES; i++)
		अगर (dc->current_state->res_ctx.pipe_ctx[i].plane_state)
			core_link_enable_stream(dc->current_state, &dc->current_state->res_ctx.pipe_ctx[i]);
पूर्ण

bool dc_is_plane_eligible_क्रम_idle_optimizations(काष्ठा dc *dc, काष्ठा dc_plane_state *plane,
		काष्ठा dc_cursor_attributes *cursor_attr)
अणु
	अगर (dc->hwss.करोes_plane_fit_in_mall && dc->hwss.करोes_plane_fit_in_mall(dc, plane, cursor_attr))
		वापस true;
	वापस false;
पूर्ण

/* cleanup on driver unload */
व्योम dc_hardware_release(काष्ठा dc *dc)
अणु
	अगर (dc->hwss.hardware_release)
		dc->hwss.hardware_release(dc);
पूर्ण
#पूर्ण_अगर

/**
 *****************************************************************************
 *  Function: dc_enable_dmub_notअगरications
 *
 *  @brief
 *		Returns whether dmub notअगरication can be enabled
 *
 *  @param
 *		[in] dc: dc काष्ठाure
 *
 *	@वापस
 *		True to enable dmub notअगरications, False otherwise
 *****************************************************************************
 */
bool dc_enable_dmub_notअगरications(काष्ठा dc *dc)
अणु
	/* dmub aux needs dmub notअगरications to be enabled */
	वापस dc->debug.enable_dmub_aux_क्रम_legacy_ddc;
पूर्ण

/**
 *****************************************************************************
 *  Function: dc_process_dmub_aux_transfer_async
 *
 *  @brief
 *		Submits aux command to dmub via inbox message
 *		Sets port index appropriately क्रम legacy DDC
 *
 *  @param
 *		[in] dc: dc काष्ठाure
 *		[in] link_index: link index
 *		[in] payload: aux payload
 *
 *	@वापस
 *		True अगर successful, False अगर failure
 *****************************************************************************
 */
bool dc_process_dmub_aux_transfer_async(काष्ठा dc *dc,
				uपूर्णांक32_t link_index,
				काष्ठा aux_payload *payload)
अणु
	uपूर्णांक8_t action;
	जोड़ dmub_rb_cmd cmd = अणु0पूर्ण;
	काष्ठा dc_dmub_srv *dmub_srv = dc->ctx->dmub_srv;

	ASSERT(payload->length <= 16);

	cmd.dp_aux_access.header.type = DMUB_CMD__DP_AUX_ACCESS;
	cmd.dp_aux_access.header.payload_bytes = 0;
	cmd.dp_aux_access.aux_control.type = AUX_CHANNEL_LEGACY_DDC;
	cmd.dp_aux_access.aux_control.instance = dc->links[link_index]->ddc_hw_inst;
	cmd.dp_aux_access.aux_control.sw_crc_enabled = 0;
	cmd.dp_aux_access.aux_control.समयout = 0;
	cmd.dp_aux_access.aux_control.dpaux.address = payload->address;
	cmd.dp_aux_access.aux_control.dpaux.is_i2c_over_aux = payload->i2c_over_aux;
	cmd.dp_aux_access.aux_control.dpaux.length = payload->length;

	/* set aux action */
	अगर (payload->i2c_over_aux) अणु
		अगर (payload->ग_लिखो) अणु
			अगर (payload->mot)
				action = DP_AUX_REQ_ACTION_I2C_WRITE_MOT;
			अन्यथा
				action = DP_AUX_REQ_ACTION_I2C_WRITE;
		पूर्ण अन्यथा अणु
			अगर (payload->mot)
				action = DP_AUX_REQ_ACTION_I2C_READ_MOT;
			अन्यथा
				action = DP_AUX_REQ_ACTION_I2C_READ;
			पूर्ण
	पूर्ण अन्यथा अणु
		अगर (payload->ग_लिखो)
			action = DP_AUX_REQ_ACTION_DPCD_WRITE;
		अन्यथा
			action = DP_AUX_REQ_ACTION_DPCD_READ;
	पूर्ण

	cmd.dp_aux_access.aux_control.dpaux.action = action;

	अगर (payload->length && payload->ग_लिखो) अणु
		स_नकल(cmd.dp_aux_access.aux_control.dpaux.data,
			payload->data,
			payload->length
			);
	पूर्ण

	dc_dmub_srv_cmd_queue(dmub_srv, &cmd);
	dc_dmub_srv_cmd_execute(dmub_srv);
	dc_dmub_srv_रुको_idle(dmub_srv);

	वापस true;
पूर्ण

/**
 *****************************************************************************
 *  Function: dc_disable_accelerated_mode
 *
 *  @brief
 *		disable accelerated mode
 *
 *  @param
 *		[in] dc: dc काष्ठाure
 *
 *****************************************************************************
 */
व्योम dc_disable_accelerated_mode(काष्ठा dc *dc)
अणु
	bios_set_scratch_acc_mode_change(dc->ctx->dc_bios, 0);
पूर्ण
