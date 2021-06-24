<शैली गुरु>
/* Copyright 2015 Advanced Micro Devices, Inc. */


#समावेश "dm_services.h"
#समावेश "dc.h"
#समावेश "inc/core_types.h"
#समावेश "include/ddc_service_types.h"
#समावेश "include/i2caux_interface.h"
#समावेश "link_hwss.h"
#समावेश "hw_sequencer.h"
#समावेश "dc_link_dp.h"
#समावेश "dc_link_ddc.h"
#समावेश "dm_helpers.h"
#समावेश "dpcd_defs.h"
#समावेश "dsc.h"
#समावेश "resource.h"
#समावेश "link_enc_cfg.h"
#समावेश "clk_mgr.h"

अटल uपूर्णांक8_t convert_to_count(uपूर्णांक8_t lttpr_repeater_count)
अणु
	चयन (lttpr_repeater_count) अणु
	हाल 0x80: // 1 lttpr repeater
		वापस 1;
	हाल 0x40: // 2 lttpr repeaters
		वापस 2;
	हाल 0x20: // 3 lttpr repeaters
		वापस 3;
	हाल 0x10: // 4 lttpr repeaters
		वापस 4;
	हाल 0x08: // 5 lttpr repeaters
		वापस 5;
	हाल 0x04: // 6 lttpr repeaters
		वापस 6;
	हाल 0x02: // 7 lttpr repeaters
		वापस 7;
	हाल 0x01: // 8 lttpr repeaters
		वापस 8;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0; // invalid value
पूर्ण

अटल अंतरभूत bool is_immediate_करोwnstream(काष्ठा dc_link *link, uपूर्णांक32_t offset)
अणु
	वापस (convert_to_count(link->dpcd_caps.lttpr_caps.phy_repeater_cnt) == offset);
पूर्ण

क्रमागत dc_status core_link_पढ़ो_dpcd(
	काष्ठा dc_link *link,
	uपूर्णांक32_t address,
	uपूर्णांक8_t *data,
	uपूर्णांक32_t size)
अणु
	अगर (!link->aux_access_disabled &&
			!dm_helpers_dp_पढ़ो_dpcd(link->ctx,
			link, address, data, size)) अणु
		वापस DC_ERROR_UNEXPECTED;
	पूर्ण

	वापस DC_OK;
पूर्ण

क्रमागत dc_status core_link_ग_लिखो_dpcd(
	काष्ठा dc_link *link,
	uपूर्णांक32_t address,
	स्थिर uपूर्णांक8_t *data,
	uपूर्णांक32_t size)
अणु
	अगर (!link->aux_access_disabled &&
			!dm_helpers_dp_ग_लिखो_dpcd(link->ctx,
			link, address, data, size)) अणु
		वापस DC_ERROR_UNEXPECTED;
	पूर्ण

	वापस DC_OK;
पूर्ण

व्योम dp_receiver_घातer_ctrl(काष्ठा dc_link *link, bool on)
अणु
	uपूर्णांक8_t state;

	state = on ? DP_POWER_STATE_D0 : DP_POWER_STATE_D3;

	अगर (link->sync_lt_in_progress)
		वापस;

	core_link_ग_लिखो_dpcd(link, DP_SET_POWER, &state,
			माप(state));
पूर्ण

व्योम dp_enable_link_phy(
	काष्ठा dc_link *link,
	क्रमागत संकेत_type संकेत,
	क्रमागत घड़ी_source_id घड़ी_source,
	स्थिर काष्ठा dc_link_settings *link_settings)
अणु
	काष्ठा link_encoder *link_enc;
	काष्ठा dc  *dc = link->ctx->dc;
	काष्ठा dmcu *dmcu = dc->res_pool->dmcu;

	काष्ठा pipe_ctx *pipes =
			link->dc->current_state->res_ctx.pipe_ctx;
	काष्ठा घड़ी_source *dp_cs =
			link->dc->res_pool->dp_घड़ी_source;
	अचिन्हित पूर्णांक i;

	/* Link should always be asचिन्हित encoder when en-/disabling. */
	अगर (link->is_dig_mapping_flexible && dc->res_pool->funcs->link_encs_assign)
		link_enc = link_enc_cfg_get_link_enc_used_by_link(link->dc->current_state, link);
	अन्यथा
		link_enc = link->link_enc;
	ASSERT(link_enc);

	अगर (link->connector_संकेत == SIGNAL_TYPE_EDP) अणु
		link->dc->hwss.edp_घातer_control(link, true);
		link->dc->hwss.edp_रुको_क्रम_hpd_पढ़ोy(link, true);
	पूर्ण

	/* If the current pixel घड़ी source is not DTO(happens after
	 * चयनing from HDMI passive करोngle to DP on the same connector),
	 * चयन the pixel घड़ी source to DTO.
	 */
	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		अगर (pipes[i].stream != शून्य &&
			pipes[i].stream->link == link) अणु
			अगर (pipes[i].घड़ी_source != शून्य &&
					pipes[i].घड़ी_source->id != CLOCK_SOURCE_ID_DP_DTO) अणु
				pipes[i].घड़ी_source = dp_cs;
				pipes[i].stream_res.pix_clk_params.requested_pix_clk_100hz =
						pipes[i].stream->timing.pix_clk_100hz;
				pipes[i].घड़ी_source->funcs->program_pix_clk(
							pipes[i].घड़ी_source,
							&pipes[i].stream_res.pix_clk_params,
							&pipes[i].pll_settings);
			पूर्ण
		पूर्ण
	पूर्ण

	link->cur_link_settings = *link_settings;

	अगर (dc->clk_mgr->funcs->notअगरy_link_rate_change)
		dc->clk_mgr->funcs->notअगरy_link_rate_change(dc->clk_mgr, link);

	अगर (dmcu != शून्य && dmcu->funcs->lock_phy)
		dmcu->funcs->lock_phy(dmcu);

	अगर (dc_is_dp_sst_संकेत(संकेत)) अणु
		link_enc->funcs->enable_dp_output(
						link_enc,
						link_settings,
						घड़ी_source);
	पूर्ण अन्यथा अणु
		link_enc->funcs->enable_dp_mst_output(
						link_enc,
						link_settings,
						घड़ी_source);
	पूर्ण

	अगर (dmcu != शून्य && dmcu->funcs->unlock_phy)
		dmcu->funcs->unlock_phy(dmcu);

	dp_receiver_घातer_ctrl(link, true);
पूर्ण

व्योम edp_add_delay_क्रम_T9(काष्ठा dc_link *link)
अणु
	अगर (link->local_sink &&
			link->local_sink->edid_caps.panel_patch.extra_delay_backlight_off > 0)
		udelay(link->local_sink->edid_caps.panel_patch.extra_delay_backlight_off * 1000);
पूर्ण

bool edp_receiver_पढ़ोy_T9(काष्ठा dc_link *link)
अणु
	अचिन्हित पूर्णांक tries = 0;
	अचिन्हित अक्षर sinkstatus = 0;
	अचिन्हित अक्षर edpRev = 0;
	क्रमागत dc_status result;

	result = core_link_पढ़ो_dpcd(link, DP_EDP_DPCD_REV, &edpRev, माप(edpRev));

    /* start from eDP version 1.2, SINK_STAUS indicate the sink is पढ़ोy.*/
	अगर (result == DC_OK && edpRev >= DP_EDP_12) अणु
		करो अणु
			sinkstatus = 1;
			result = core_link_पढ़ो_dpcd(link, DP_SINK_STATUS, &sinkstatus, माप(sinkstatus));
			अगर (sinkstatus == 0)
				अवरोध;
			अगर (result != DC_OK)
				अवरोध;
			udelay(100); //MAx T9
		पूर्ण जबतक (++tries < 50);
	पूर्ण

	वापस result;
पूर्ण
bool edp_receiver_पढ़ोy_T7(काष्ठा dc_link *link)
अणु
	अचिन्हित अक्षर sinkstatus = 0;
	अचिन्हित अक्षर edpRev = 0;
	क्रमागत dc_status result;

	/* use असलolute समय stamp to स्थिरrain max T7*/
	अचिन्हित दीर्घ दीर्घ enter_बारtamp = 0;
	अचिन्हित दीर्घ दीर्घ finish_बारtamp = 0;
	अचिन्हित दीर्घ दीर्घ समय_प्रकारaken_in_ns = 0;

	result = core_link_पढ़ो_dpcd(link, DP_EDP_DPCD_REV, &edpRev, माप(edpRev));

	अगर (result == DC_OK && edpRev >= DP_EDP_12) अणु
		/* start from eDP version 1.2, SINK_STAUS indicate the sink is पढ़ोy.*/
		enter_बारtamp = dm_get_बारtamp(link->ctx);
		करो अणु
			sinkstatus = 0;
			result = core_link_पढ़ो_dpcd(link, DP_SINK_STATUS, &sinkstatus, माप(sinkstatus));
			अगर (sinkstatus == 1)
				अवरोध;
			अगर (result != DC_OK)
				अवरोध;
			udelay(25);
			finish_बारtamp = dm_get_बारtamp(link->ctx);
			समय_प्रकारaken_in_ns = dm_get_elapse_समय_in_ns(link->ctx, finish_बारtamp, enter_बारtamp);
		पूर्ण जबतक (समय_प्रकारaken_in_ns < 50 * 1000000); //MAx T7 is 50ms
	पूर्ण

	अगर (link->local_sink &&
			link->local_sink->edid_caps.panel_patch.extra_t7_ms > 0)
		udelay(link->local_sink->edid_caps.panel_patch.extra_t7_ms * 1000);

	वापस result;
पूर्ण

व्योम dp_disable_link_phy(काष्ठा dc_link *link, क्रमागत संकेत_type संकेत)
अणु
	काष्ठा dc  *dc = link->ctx->dc;
	काष्ठा dmcu *dmcu = dc->res_pool->dmcu;
	काष्ठा link_encoder *link_enc;

	/* Link should always be asचिन्हित encoder when en-/disabling. */
	अगर (link->is_dig_mapping_flexible && dc->res_pool->funcs->link_encs_assign)
		link_enc = link_enc_cfg_get_link_enc_used_by_link(link->dc->current_state, link);
	अन्यथा
		link_enc = link->link_enc;
	ASSERT(link_enc);

	अगर (!link->wa_flags.dp_keep_receiver_घातered)
		dp_receiver_घातer_ctrl(link, false);

	अगर (संकेत == SIGNAL_TYPE_EDP) अणु
		अगर (link->dc->hwss.edp_backlight_control)
			link->dc->hwss.edp_backlight_control(link, false);
		link_enc->funcs->disable_output(link_enc, संकेत);
		link->dc->hwss.edp_घातer_control(link, false);
	पूर्ण अन्यथा अणु
		अगर (dmcu != शून्य && dmcu->funcs->lock_phy)
			dmcu->funcs->lock_phy(dmcu);

		link_enc->funcs->disable_output(link_enc, संकेत);

		अगर (dmcu != शून्य && dmcu->funcs->unlock_phy)
			dmcu->funcs->unlock_phy(dmcu);
	पूर्ण

	/* Clear current link setting.*/
	स_रखो(&link->cur_link_settings, 0,
			माप(link->cur_link_settings));

	अगर (dc->clk_mgr->funcs->notअगरy_link_rate_change)
		dc->clk_mgr->funcs->notअगरy_link_rate_change(dc->clk_mgr, link);
पूर्ण

व्योम dp_disable_link_phy_mst(काष्ठा dc_link *link, क्रमागत संकेत_type संकेत)
अणु
	/* MST disable link only when no stream use the link */
	अगर (link->mst_stream_alloc_table.stream_count > 0)
		वापस;

	dp_disable_link_phy(link, संकेत);

	/* set the sink to SST mode after disabling the link */
	dp_enable_mst_on_sink(link, false);
पूर्ण

bool dp_set_hw_training_pattern(
	काष्ठा dc_link *link,
	क्रमागत dc_dp_training_pattern pattern,
	uपूर्णांक32_t offset)
अणु
	क्रमागत dp_test_pattern test_pattern = DP_TEST_PATTERN_UNSUPPORTED;

	चयन (pattern) अणु
	हाल DP_TRAINING_PATTERN_SEQUENCE_1:
		test_pattern = DP_TEST_PATTERN_TRAINING_PATTERN1;
		अवरोध;
	हाल DP_TRAINING_PATTERN_SEQUENCE_2:
		test_pattern = DP_TEST_PATTERN_TRAINING_PATTERN2;
		अवरोध;
	हाल DP_TRAINING_PATTERN_SEQUENCE_3:
		test_pattern = DP_TEST_PATTERN_TRAINING_PATTERN3;
		अवरोध;
	हाल DP_TRAINING_PATTERN_SEQUENCE_4:
		test_pattern = DP_TEST_PATTERN_TRAINING_PATTERN4;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	dp_set_hw_test_pattern(link, test_pattern, शून्य, 0);

	वापस true;
पूर्ण

व्योम dp_set_hw_lane_settings(
	काष्ठा dc_link *link,
	स्थिर काष्ठा link_training_settings *link_settings,
	uपूर्णांक32_t offset)
अणु
	काष्ठा link_encoder *encoder = link->link_enc;

	अगर ((link->lttpr_mode == LTTPR_MODE_NON_TRANSPARENT) && !is_immediate_करोwnstream(link, offset))
		वापस;

	/* call Encoder to set lane settings */
	encoder->funcs->dp_set_lane_settings(encoder, link_settings);
पूर्ण

व्योम dp_set_hw_test_pattern(
	काष्ठा dc_link *link,
	क्रमागत dp_test_pattern test_pattern,
	uपूर्णांक8_t *custom_pattern,
	uपूर्णांक32_t custom_pattern_size)
अणु
	काष्ठा encoder_set_dp_phy_pattern_param pattern_param = अणु0पूर्ण;
	काष्ठा link_encoder *encoder = link->link_enc;

	pattern_param.dp_phy_pattern = test_pattern;
	pattern_param.custom_pattern = custom_pattern;
	pattern_param.custom_pattern_size = custom_pattern_size;
	pattern_param.dp_panel_mode = dp_get_panel_mode(link);

	encoder->funcs->dp_set_phy_pattern(encoder, &pattern_param);
पूर्ण

व्योम dp_retrain_link_dp_test(काष्ठा dc_link *link,
			काष्ठा dc_link_settings *link_setting,
			bool skip_video_pattern)
अणु
	काष्ठा pipe_ctx *pipes =
			&link->dc->current_state->res_ctx.pipe_ctx[0];
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		अगर (pipes[i].stream != शून्य &&
			!pipes[i].top_pipe && !pipes[i].prev_odm_pipe &&
			pipes[i].stream->link != शून्य &&
			pipes[i].stream_res.stream_enc != शून्य &&
			pipes[i].stream->link == link) अणु
			udelay(100);

			pipes[i].stream_res.stream_enc->funcs->dp_blank(
					pipes[i].stream_res.stream_enc);

			/* disable any test pattern that might be active */
			dp_set_hw_test_pattern(link,
					DP_TEST_PATTERN_VIDEO_MODE, शून्य, 0);

			dp_receiver_घातer_ctrl(link, false);

			link->dc->hwss.disable_stream(&pipes[i]);
			अगर ((&pipes[i])->stream_res.audio && !link->dc->debug.az_endpoपूर्णांक_mute_only)
				(&pipes[i])->stream_res.audio->funcs->az_disable((&pipes[i])->stream_res.audio);

			link->link_enc->funcs->disable_output(
					link->link_enc,
					SIGNAL_TYPE_DISPLAY_PORT);

			/* Clear current link setting. */
			स_रखो(&link->cur_link_settings, 0,
				माप(link->cur_link_settings));

			perक्रमm_link_training_with_retries(
					link_setting,
					skip_video_pattern,
					LINK_TRAINING_ATTEMPTS,
					&pipes[i],
					SIGNAL_TYPE_DISPLAY_PORT);

			link->dc->hwss.enable_stream(&pipes[i]);

			link->dc->hwss.unblank_stream(&pipes[i],
					link_setting);

			अगर (pipes[i].stream_res.audio) अणु
				/* notअगरy audio driver क्रम
				 * audio modes of monitor */
				pipes[i].stream_res.audio->funcs->az_enable(
						pipes[i].stream_res.audio);

				/* un-mute audio */
				/* TODO: audio should be per stream rather than
				 * per link */
				pipes[i].stream_res.stream_enc->funcs->
				audio_mute_control(
					pipes[i].stream_res.stream_enc, false);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा DC_LOGGER \
	dsc->ctx->logger
अटल व्योम dsc_optc_config_log(काष्ठा display_stream_compressor *dsc,
		काष्ठा dsc_optc_config *config)
अणु
	uपूर्णांक32_t precision = 1 << 28;
	uपूर्णांक32_t bytes_per_pixel_पूर्णांक = config->bytes_per_pixel / precision;
	uपूर्णांक32_t bytes_per_pixel_mod = config->bytes_per_pixel % precision;
	uपूर्णांक64_t ll_bytes_per_pix_fraq = bytes_per_pixel_mod;

	/* 7 fractional digits decimal precision क्रम bytes per pixel is enough because DSC
	 * bits per pixel precision is 1/16th of a pixel, which means bytes per pixel precision is
	 * 1/16/8 = 1/128 of a byte, or 0.0078125 decimal
	 */
	ll_bytes_per_pix_fraq *= 10000000;
	ll_bytes_per_pix_fraq /= precision;

	DC_LOG_DSC("\tbytes_per_pixel 0x%08x (%d.%07d)",
			config->bytes_per_pixel, bytes_per_pixel_पूर्णांक, (uपूर्णांक32_t)ll_bytes_per_pix_fraq);
	DC_LOG_DSC("\tis_pixel_format_444 %d", config->is_pixel_क्रमmat_444);
	DC_LOG_DSC("\tslice_width %d", config->slice_width);
पूर्ण

bool dp_set_dsc_on_rx(काष्ठा pipe_ctx *pipe_ctx, bool enable)
अणु
	काष्ठा dc *dc = pipe_ctx->stream->ctx->dc;
	काष्ठा dc_stream_state *stream = pipe_ctx->stream;
	bool result = false;

	अगर (dc_is_भव_संकेत(stream->संकेत) || IS_FPGA_MAXIMUS_DC(dc->ctx->dce_environment))
		result = true;
	अन्यथा
		result = dm_helpers_dp_ग_लिखो_dsc_enable(dc->ctx, stream, enable);
	वापस result;
पूर्ण

/* The stream with these settings can be sent (unblanked) only after DSC was enabled on RX first,
 * i.e. after dp_enable_dsc_on_rx() had been called
 */
व्योम dp_set_dsc_on_stream(काष्ठा pipe_ctx *pipe_ctx, bool enable)
अणु
	काष्ठा display_stream_compressor *dsc = pipe_ctx->stream_res.dsc;
	काष्ठा dc *dc = pipe_ctx->stream->ctx->dc;
	काष्ठा dc_stream_state *stream = pipe_ctx->stream;
	काष्ठा pipe_ctx *odm_pipe;
	पूर्णांक opp_cnt = 1;

	क्रम (odm_pipe = pipe_ctx->next_odm_pipe; odm_pipe; odm_pipe = odm_pipe->next_odm_pipe)
		opp_cnt++;

	अगर (enable) अणु
		काष्ठा dsc_config dsc_cfg;
		काष्ठा dsc_optc_config dsc_optc_cfg;
		क्रमागत optc_dsc_mode optc_dsc_mode;

		/* Enable DSC hw block */
		dsc_cfg.pic_width = (stream->timing.h_addressable + stream->timing.h_border_left + stream->timing.h_border_right) / opp_cnt;
		dsc_cfg.pic_height = stream->timing.v_addressable + stream->timing.v_border_top + stream->timing.v_border_bottom;
		dsc_cfg.pixel_encoding = stream->timing.pixel_encoding;
		dsc_cfg.color_depth = stream->timing.display_color_depth;
		dsc_cfg.is_odm = pipe_ctx->next_odm_pipe ? true : false;
		dsc_cfg.dc_dsc_cfg = stream->timing.dsc_cfg;
		ASSERT(dsc_cfg.dc_dsc_cfg.num_slices_h % opp_cnt == 0);
		dsc_cfg.dc_dsc_cfg.num_slices_h /= opp_cnt;

		dsc->funcs->dsc_set_config(dsc, &dsc_cfg, &dsc_optc_cfg);
		dsc->funcs->dsc_enable(dsc, pipe_ctx->stream_res.opp->inst);
		क्रम (odm_pipe = pipe_ctx->next_odm_pipe; odm_pipe; odm_pipe = odm_pipe->next_odm_pipe) अणु
			काष्ठा display_stream_compressor *odm_dsc = odm_pipe->stream_res.dsc;

			odm_dsc->funcs->dsc_set_config(odm_dsc, &dsc_cfg, &dsc_optc_cfg);
			odm_dsc->funcs->dsc_enable(odm_dsc, odm_pipe->stream_res.opp->inst);
		पूर्ण
		dsc_cfg.dc_dsc_cfg.num_slices_h *= opp_cnt;
		dsc_cfg.pic_width *= opp_cnt;

		optc_dsc_mode = dsc_optc_cfg.is_pixel_क्रमmat_444 ? OPTC_DSC_ENABLED_444 : OPTC_DSC_ENABLED_NATIVE_SUBSAMPLED;

		/* Enable DSC in encoder */
		अगर (dc_is_dp_संकेत(stream->संकेत) && !IS_FPGA_MAXIMUS_DC(dc->ctx->dce_environment)) अणु
			DC_LOG_DSC("Setting stream encoder DSC config for engine %d:", (पूर्णांक)pipe_ctx->stream_res.stream_enc->id);
			dsc_optc_config_log(dsc, &dsc_optc_cfg);
			pipe_ctx->stream_res.stream_enc->funcs->dp_set_dsc_config(pipe_ctx->stream_res.stream_enc,
									optc_dsc_mode,
									dsc_optc_cfg.bytes_per_pixel,
									dsc_optc_cfg.slice_width);

			/* PPS SDP is set अन्यथाwhere because it has to be करोne after DIG FE is connected to DIG BE */
		पूर्ण

		/* Enable DSC in OPTC */
		DC_LOG_DSC("Setting optc DSC config for tg instance %d:", pipe_ctx->stream_res.tg->inst);
		dsc_optc_config_log(dsc, &dsc_optc_cfg);
		pipe_ctx->stream_res.tg->funcs->set_dsc_config(pipe_ctx->stream_res.tg,
							optc_dsc_mode,
							dsc_optc_cfg.bytes_per_pixel,
							dsc_optc_cfg.slice_width);
	पूर्ण अन्यथा अणु
		/* disable DSC in OPTC */
		pipe_ctx->stream_res.tg->funcs->set_dsc_config(
				pipe_ctx->stream_res.tg,
				OPTC_DSC_DISABLED, 0, 0);

		/* disable DSC in stream encoder */
		अगर (dc_is_dp_संकेत(stream->संकेत)) अणु

			अगर (!IS_FPGA_MAXIMUS_DC(dc->ctx->dce_environment)) अणु
				pipe_ctx->stream_res.stream_enc->funcs->dp_set_dsc_config(
						pipe_ctx->stream_res.stream_enc,
						OPTC_DSC_DISABLED, 0, 0);
				pipe_ctx->stream_res.stream_enc->funcs->dp_set_dsc_pps_info_packet(
							pipe_ctx->stream_res.stream_enc, false, शून्य);
			पूर्ण
		पूर्ण

		/* disable DSC block */
		pipe_ctx->stream_res.dsc->funcs->dsc_disable(pipe_ctx->stream_res.dsc);
		क्रम (odm_pipe = pipe_ctx->next_odm_pipe; odm_pipe; odm_pipe = odm_pipe->next_odm_pipe)
			odm_pipe->stream_res.dsc->funcs->dsc_disable(odm_pipe->stream_res.dsc);
	पूर्ण
पूर्ण

bool dp_set_dsc_enable(काष्ठा pipe_ctx *pipe_ctx, bool enable)
अणु
	काष्ठा display_stream_compressor *dsc = pipe_ctx->stream_res.dsc;
	bool result = false;

	अगर (!pipe_ctx->stream->timing.flags.DSC)
		जाओ out;
	अगर (!dsc)
		जाओ out;

	अगर (enable) अणु
		अणु
			dp_set_dsc_on_stream(pipe_ctx, true);
			result = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		dp_set_dsc_on_rx(pipe_ctx, false);
		dp_set_dsc_on_stream(pipe_ctx, false);
		result = true;
	पूर्ण
out:
	वापस result;
पूर्ण

bool dp_set_dsc_pps_sdp(काष्ठा pipe_ctx *pipe_ctx, bool enable)
अणु
	काष्ठा display_stream_compressor *dsc = pipe_ctx->stream_res.dsc;
	काष्ठा dc_stream_state *stream = pipe_ctx->stream;

	अगर (!pipe_ctx->stream->timing.flags.DSC || !dsc)
		वापस false;

	अगर (enable) अणु
		काष्ठा dsc_config dsc_cfg;
		uपूर्णांक8_t dsc_packed_pps[128];

		स_रखो(&dsc_cfg, 0, माप(dsc_cfg));
		स_रखो(dsc_packed_pps, 0, 128);

		/* Enable DSC hw block */
		dsc_cfg.pic_width = stream->timing.h_addressable + stream->timing.h_border_left + stream->timing.h_border_right;
		dsc_cfg.pic_height = stream->timing.v_addressable + stream->timing.v_border_top + stream->timing.v_border_bottom;
		dsc_cfg.pixel_encoding = stream->timing.pixel_encoding;
		dsc_cfg.color_depth = stream->timing.display_color_depth;
		dsc_cfg.is_odm = pipe_ctx->next_odm_pipe ? true : false;
		dsc_cfg.dc_dsc_cfg = stream->timing.dsc_cfg;

		DC_LOG_DSC(" ");
		dsc->funcs->dsc_get_packed_pps(dsc, &dsc_cfg, &dsc_packed_pps[0]);
		अगर (dc_is_dp_संकेत(stream->संकेत)) अणु
			DC_LOG_DSC("Setting stream encoder DSC PPS SDP for engine %d\n", (पूर्णांक)pipe_ctx->stream_res.stream_enc->id);
			pipe_ctx->stream_res.stream_enc->funcs->dp_set_dsc_pps_info_packet(
									pipe_ctx->stream_res.stream_enc,
									true,
									&dsc_packed_pps[0]);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* disable DSC PPS in stream encoder */
		अगर (dc_is_dp_संकेत(stream->संकेत)) अणु
			pipe_ctx->stream_res.stream_enc->funcs->dp_set_dsc_pps_info_packet(
						pipe_ctx->stream_res.stream_enc, false, शून्य);
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण


bool dp_update_dsc_config(काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा display_stream_compressor *dsc = pipe_ctx->stream_res.dsc;

	अगर (!pipe_ctx->stream->timing.flags.DSC)
		वापस false;
	अगर (!dsc)
		वापस false;

	dp_set_dsc_on_stream(pipe_ctx, true);
	dp_set_dsc_pps_sdp(pipe_ctx, true);
	वापस true;
पूर्ण

