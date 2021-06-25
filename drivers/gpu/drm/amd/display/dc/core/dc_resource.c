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

#समावेश <linux/slab.h>

#समावेश "dm_services.h"

#समावेश "resource.h"
#समावेश "include/irq_service_interface.h"
#समावेश "link_encoder.h"
#समावेश "stream_encoder.h"
#समावेश "opp.h"
#समावेश "timing_generator.h"
#समावेश "transform.h"
#समावेश "dccg.h"
#समावेश "dchubbub.h"
#समावेश "dpp.h"
#समावेश "core_types.h"
#समावेश "set_mode_types.h"
#समावेश "virtual/virtual_stream_encoder.h"
#समावेश "dpcd_defs.h"

#अगर defined(CONFIG_DRM_AMD_DC_SI)
#समावेश "dce60/dce60_resource.h"
#पूर्ण_अगर
#समावेश "dce80/dce80_resource.h"
#समावेश "dce100/dce100_resource.h"
#समावेश "dce110/dce110_resource.h"
#समावेश "dce112/dce112_resource.h"
#समावेश "dce120/dce120_resource.h"
#अगर defined(CONFIG_DRM_AMD_DC_DCN)
#समावेश "dcn10/dcn10_resource.h"
#समावेश "dcn20/dcn20_resource.h"
#समावेश "dcn21/dcn21_resource.h"
#समावेश "dcn30/dcn30_resource.h"
#समावेश "dcn301/dcn301_resource.h"
#समावेश "dcn302/dcn302_resource.h"
#पूर्ण_अगर

#घोषणा DC_LOGGER_INIT(logger)

क्रमागत dce_version resource_parse_asic_id(काष्ठा hw_asic_id asic_id)
अणु
	क्रमागत dce_version dc_version = DCE_VERSION_UNKNOWN;
	चयन (asic_id.chip_family) अणु

#अगर defined(CONFIG_DRM_AMD_DC_SI)
	हाल FAMILY_SI:
		अगर (ASIC_REV_IS_TAHITI_P(asic_id.hw_पूर्णांकernal_rev) ||
		    ASIC_REV_IS_PITCAIRN_PM(asic_id.hw_पूर्णांकernal_rev) ||
		    ASIC_REV_IS_CAPEVERDE_M(asic_id.hw_पूर्णांकernal_rev))
			dc_version = DCE_VERSION_6_0;
		अन्यथा अगर (ASIC_REV_IS_OLAND_M(asic_id.hw_पूर्णांकernal_rev))
			dc_version = DCE_VERSION_6_4;
		अन्यथा
			dc_version = DCE_VERSION_6_1;
		अवरोध;
#पूर्ण_अगर
	हाल FAMILY_CI:
		dc_version = DCE_VERSION_8_0;
		अवरोध;
	हाल FAMILY_KV:
		अगर (ASIC_REV_IS_KALINDI(asic_id.hw_पूर्णांकernal_rev) ||
		    ASIC_REV_IS_BHAVANI(asic_id.hw_पूर्णांकernal_rev) ||
		    ASIC_REV_IS_GODAVARI(asic_id.hw_पूर्णांकernal_rev))
			dc_version = DCE_VERSION_8_3;
		अन्यथा
			dc_version = DCE_VERSION_8_1;
		अवरोध;
	हाल FAMILY_CZ:
		dc_version = DCE_VERSION_11_0;
		अवरोध;

	हाल FAMILY_VI:
		अगर (ASIC_REV_IS_TONGA_P(asic_id.hw_पूर्णांकernal_rev) ||
				ASIC_REV_IS_FIJI_P(asic_id.hw_पूर्णांकernal_rev)) अणु
			dc_version = DCE_VERSION_10_0;
			अवरोध;
		पूर्ण
		अगर (ASIC_REV_IS_POLARIS10_P(asic_id.hw_पूर्णांकernal_rev) ||
				ASIC_REV_IS_POLARIS11_M(asic_id.hw_पूर्णांकernal_rev) ||
				ASIC_REV_IS_POLARIS12_V(asic_id.hw_पूर्णांकernal_rev)) अणु
			dc_version = DCE_VERSION_11_2;
		पूर्ण
		अगर (ASIC_REV_IS_VEGAM(asic_id.hw_पूर्णांकernal_rev))
			dc_version = DCE_VERSION_11_22;
		अवरोध;
	हाल FAMILY_AI:
		अगर (ASICREV_IS_VEGA20_P(asic_id.hw_पूर्णांकernal_rev))
			dc_version = DCE_VERSION_12_1;
		अन्यथा
			dc_version = DCE_VERSION_12_0;
		अवरोध;
#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	हाल FAMILY_RV:
		dc_version = DCN_VERSION_1_0;
		अगर (ASICREV_IS_RAVEN2(asic_id.hw_पूर्णांकernal_rev))
			dc_version = DCN_VERSION_1_01;
		अगर (ASICREV_IS_RENOIR(asic_id.hw_पूर्णांकernal_rev))
			dc_version = DCN_VERSION_2_1;
		अगर (ASICREV_IS_GREEN_SARDINE(asic_id.hw_पूर्णांकernal_rev))
			dc_version = DCN_VERSION_2_1;
		अवरोध;

	हाल FAMILY_NV:
		dc_version = DCN_VERSION_2_0;
		अगर (ASICREV_IS_SIENNA_CICHLID_P(asic_id.hw_पूर्णांकernal_rev))
			dc_version = DCN_VERSION_3_0;
		अगर (ASICREV_IS_DIMGREY_CAVEFISH_P(asic_id.hw_पूर्णांकernal_rev))
			dc_version = DCN_VERSION_3_02;
		अवरोध;

	हाल FAMILY_VGH:
		dc_version = DCN_VERSION_3_01;
		अवरोध;
#पूर्ण_अगर
	शेष:
		dc_version = DCE_VERSION_UNKNOWN;
		अवरोध;
	पूर्ण
	वापस dc_version;
पूर्ण

काष्ठा resource_pool *dc_create_resource_pool(काष्ठा dc  *dc,
					      स्थिर काष्ठा dc_init_data *init_data,
					      क्रमागत dce_version dc_version)
अणु
	काष्ठा resource_pool *res_pool = शून्य;

	चयन (dc_version) अणु
#अगर defined(CONFIG_DRM_AMD_DC_SI)
	हाल DCE_VERSION_6_0:
		res_pool = dce60_create_resource_pool(
			init_data->num_भव_links, dc);
		अवरोध;
	हाल DCE_VERSION_6_1:
		res_pool = dce61_create_resource_pool(
			init_data->num_भव_links, dc);
		अवरोध;
	हाल DCE_VERSION_6_4:
		res_pool = dce64_create_resource_pool(
			init_data->num_भव_links, dc);
		अवरोध;
#पूर्ण_अगर
	हाल DCE_VERSION_8_0:
		res_pool = dce80_create_resource_pool(
				init_data->num_भव_links, dc);
		अवरोध;
	हाल DCE_VERSION_8_1:
		res_pool = dce81_create_resource_pool(
				init_data->num_भव_links, dc);
		अवरोध;
	हाल DCE_VERSION_8_3:
		res_pool = dce83_create_resource_pool(
				init_data->num_भव_links, dc);
		अवरोध;
	हाल DCE_VERSION_10_0:
		res_pool = dce100_create_resource_pool(
				init_data->num_भव_links, dc);
		अवरोध;
	हाल DCE_VERSION_11_0:
		res_pool = dce110_create_resource_pool(
				init_data->num_भव_links, dc,
				init_data->asic_id);
		अवरोध;
	हाल DCE_VERSION_11_2:
	हाल DCE_VERSION_11_22:
		res_pool = dce112_create_resource_pool(
				init_data->num_भव_links, dc);
		अवरोध;
	हाल DCE_VERSION_12_0:
	हाल DCE_VERSION_12_1:
		res_pool = dce120_create_resource_pool(
				init_data->num_भव_links, dc);
		अवरोध;

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	हाल DCN_VERSION_1_0:
	हाल DCN_VERSION_1_01:
		res_pool = dcn10_create_resource_pool(init_data, dc);
		अवरोध;
	हाल DCN_VERSION_2_0:
		res_pool = dcn20_create_resource_pool(init_data, dc);
		अवरोध;
	हाल DCN_VERSION_2_1:
		res_pool = dcn21_create_resource_pool(init_data, dc);
		अवरोध;
	हाल DCN_VERSION_3_0:
		res_pool = dcn30_create_resource_pool(init_data, dc);
		अवरोध;
	हाल DCN_VERSION_3_01:
		res_pool = dcn301_create_resource_pool(init_data, dc);
		अवरोध;
	हाल DCN_VERSION_3_02:
		res_pool = dcn302_create_resource_pool(init_data, dc);
		अवरोध;
#पूर्ण_अगर
	शेष:
		अवरोध;
	पूर्ण

	अगर (res_pool != शून्य) अणु
		अगर (dc->ctx->dc_bios->fw_info_valid) अणु
			res_pool->ref_घड़ीs.xtalin_घड़ी_inKhz =
				dc->ctx->dc_bios->fw_info.pll_info.crystal_frequency;
			/* initialize with firmware data first, no all
			 * ASIC have DCCG SW component. FPGA or
			 * simulation need initialization of
			 * dccg_ref_घड़ी_inKhz, dchub_ref_घड़ी_inKhz
			 * with xtalin_घड़ी_inKhz
			 */
			res_pool->ref_घड़ीs.dccg_ref_घड़ी_inKhz =
				res_pool->ref_घड़ीs.xtalin_घड़ी_inKhz;
			res_pool->ref_घड़ीs.dchub_ref_घड़ी_inKhz =
				res_pool->ref_घड़ीs.xtalin_घड़ी_inKhz;
		पूर्ण अन्यथा
			ASSERT_CRITICAL(false);
	पूर्ण

	वापस res_pool;
पूर्ण

व्योम dc_destroy_resource_pool(काष्ठा dc  *dc)
अणु
	अगर (dc) अणु
		अगर (dc->res_pool)
			dc->res_pool->funcs->destroy(&dc->res_pool);

		kमुक्त(dc->hwseq);
	पूर्ण
पूर्ण

अटल व्योम update_num_audio(
	स्थिर काष्ठा resource_straps *straps,
	अचिन्हित पूर्णांक *num_audio,
	काष्ठा audio_support *aud_support)
अणु
	aud_support->dp_audio = true;
	aud_support->hdmi_audio_native = false;
	aud_support->hdmi_audio_on_करोngle = false;

	अगर (straps->hdmi_disable == 0) अणु
		अगर (straps->dc_pinstraps_audio & 0x2) अणु
			aud_support->hdmi_audio_on_करोngle = true;
			aud_support->hdmi_audio_native = true;
		पूर्ण
	पूर्ण

	चयन (straps->audio_stream_number) अणु
	हाल 0: /* multi streams supported */
		अवरोध;
	हाल 1: /* multi streams not supported */
		*num_audio = 1;
		अवरोध;
	शेष:
		DC_ERR("DC: unexpected audio fuse!\n");
	पूर्ण
पूर्ण

bool resource_स्थिरruct(
	अचिन्हित पूर्णांक num_भव_links,
	काष्ठा dc  *dc,
	काष्ठा resource_pool *pool,
	स्थिर काष्ठा resource_create_funcs *create_funcs)
अणु
	काष्ठा dc_context *ctx = dc->ctx;
	स्थिर काष्ठा resource_caps *caps = pool->res_cap;
	पूर्णांक i;
	अचिन्हित पूर्णांक num_audio = caps->num_audio;
	काष्ठा resource_straps straps = अणु0पूर्ण;

	अगर (create_funcs->पढ़ो_dce_straps)
		create_funcs->पढ़ो_dce_straps(dc->ctx, &straps);

	pool->audio_count = 0;
	अगर (create_funcs->create_audio) अणु
		/* find the total number of streams available via the
		 * AZALIA_F0_CODEC_PIN_CONTROL_RESPONSE_CONFIGURATION_DEFAULT
		 * रेजिस्टरs (one क्रम each pin) starting from pin 1
		 * up to the max number of audio pins.
		 * We stop on the first pin where
		 * PORT_CONNECTIVITY == 1 (as inकाष्ठाed by HW team).
		 */
		update_num_audio(&straps, &num_audio, &pool->audio_support);
		क्रम (i = 0; i < caps->num_audio; i++) अणु
			काष्ठा audio *aud = create_funcs->create_audio(ctx, i);

			अगर (aud == शून्य) अणु
				DC_ERR("DC: failed to create audio!\n");
				वापस false;
			पूर्ण
			अगर (!aud->funcs->endpoपूर्णांक_valid(aud)) अणु
				aud->funcs->destroy(&aud);
				अवरोध;
			पूर्ण
			pool->audios[i] = aud;
			pool->audio_count++;
		पूर्ण
	पूर्ण

	pool->stream_enc_count = 0;
	अगर (create_funcs->create_stream_encoder) अणु
		क्रम (i = 0; i < caps->num_stream_encoder; i++) अणु
			pool->stream_enc[i] = create_funcs->create_stream_encoder(i, ctx);
			अगर (pool->stream_enc[i] == शून्य)
				DC_ERR("DC: failed to create stream_encoder!\n");
			pool->stream_enc_count++;
		पूर्ण
	पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	क्रम (i = 0; i < caps->num_mpc_3dlut; i++) अणु
		pool->mpc_lut[i] = dc_create_3dlut_func();
		अगर (pool->mpc_lut[i] == शून्य)
			DC_ERR("DC: failed to create MPC 3dlut!\n");
		pool->mpc_shaper[i] = dc_create_transfer_func();
		अगर (pool->mpc_shaper[i] == शून्य)
			DC_ERR("DC: failed to create MPC shaper!\n");
	पूर्ण
#पूर्ण_अगर
	dc->caps.dynamic_audio = false;
	अगर (pool->audio_count < pool->stream_enc_count) अणु
		dc->caps.dynamic_audio = true;
	पूर्ण
	क्रम (i = 0; i < num_भव_links; i++) अणु
		pool->stream_enc[pool->stream_enc_count] =
			भव_stream_encoder_create(
					ctx, ctx->dc_bios);
		अगर (pool->stream_enc[pool->stream_enc_count] == शून्य) अणु
			DC_ERR("DC: failed to create stream_encoder!\n");
			वापस false;
		पूर्ण
		pool->stream_enc_count++;
	पूर्ण

	dc->hwseq = create_funcs->create_hwseq(ctx);

	वापस true;
पूर्ण
अटल पूर्णांक find_matching_घड़ी_source(
		स्थिर काष्ठा resource_pool *pool,
		काष्ठा घड़ी_source *घड़ी_source)
अणु

	पूर्णांक i;

	क्रम (i = 0; i < pool->clk_src_count; i++) अणु
		अगर (pool->घड़ी_sources[i] == घड़ी_source)
			वापस i;
	पूर्ण
	वापस -1;
पूर्ण

व्योम resource_unreference_घड़ी_source(
		काष्ठा resource_context *res_ctx,
		स्थिर काष्ठा resource_pool *pool,
		काष्ठा घड़ी_source *घड़ी_source)
अणु
	पूर्णांक i = find_matching_घड़ी_source(pool, घड़ी_source);

	अगर (i > -1)
		res_ctx->घड़ी_source_ref_count[i]--;

	अगर (pool->dp_घड़ी_source == घड़ी_source)
		res_ctx->dp_घड़ी_source_ref_count--;
पूर्ण

व्योम resource_reference_घड़ी_source(
		काष्ठा resource_context *res_ctx,
		स्थिर काष्ठा resource_pool *pool,
		काष्ठा घड़ी_source *घड़ी_source)
अणु
	पूर्णांक i = find_matching_घड़ी_source(pool, घड़ी_source);

	अगर (i > -1)
		res_ctx->घड़ी_source_ref_count[i]++;

	अगर (pool->dp_घड़ी_source == घड़ी_source)
		res_ctx->dp_घड़ी_source_ref_count++;
पूर्ण

पूर्णांक resource_get_घड़ी_source_reference(
		काष्ठा resource_context *res_ctx,
		स्थिर काष्ठा resource_pool *pool,
		काष्ठा घड़ी_source *घड़ी_source)
अणु
	पूर्णांक i = find_matching_घड़ी_source(pool, घड़ी_source);

	अगर (i > -1)
		वापस res_ctx->घड़ी_source_ref_count[i];

	अगर (pool->dp_घड़ी_source == घड़ी_source)
		वापस res_ctx->dp_घड़ी_source_ref_count;

	वापस -1;
पूर्ण

bool resource_are_vblanks_synchronizable(
	काष्ठा dc_stream_state *stream1,
	काष्ठा dc_stream_state *stream2)
अणु
	uपूर्णांक32_t base60_refresh_rates[] = अणु10, 20, 5पूर्ण;
	uपूर्णांक8_t i;
	uपूर्णांक8_t rr_count = माप(base60_refresh_rates)/माप(base60_refresh_rates[0]);
	uपूर्णांक64_t frame_समय_dअगरf;

	अगर (stream1->ctx->dc->config.vblank_alignment_dto_params &&
		stream1->ctx->dc->config.vblank_alignment_max_frame_समय_dअगरf > 0 &&
		dc_is_dp_संकेत(stream1->संकेत) &&
		dc_is_dp_संकेत(stream2->संकेत) &&
		false == stream1->has_non_synchronizable_pclk &&
		false == stream2->has_non_synchronizable_pclk &&
		stream1->timing.flags.VBLANK_SYNCHRONIZABLE &&
		stream2->timing.flags.VBLANK_SYNCHRONIZABLE) अणु
		/* disable refresh rates higher than 60Hz क्रम now */
		अगर (stream1->timing.pix_clk_100hz*100/stream1->timing.h_total/
				stream1->timing.v_total > 60)
			वापस false;
		अगर (stream2->timing.pix_clk_100hz*100/stream2->timing.h_total/
				stream2->timing.v_total > 60)
			वापस false;
		frame_समय_dअगरf = (uपूर्णांक64_t)10000 *
			stream1->timing.h_total *
			stream1->timing.v_total *
			stream2->timing.pix_clk_100hz;
		frame_समय_dअगरf = भाग_u64(frame_समय_dअगरf, stream1->timing.pix_clk_100hz);
		frame_समय_dअगरf = भाग_u64(frame_समय_dअगरf, stream2->timing.h_total);
		frame_समय_dअगरf = भाग_u64(frame_समय_dअगरf, stream2->timing.v_total);
		क्रम (i = 0; i < rr_count; i++) अणु
			पूर्णांक64_t dअगरf = (पूर्णांक64_t)भाग_u64(frame_समय_dअगरf * base60_refresh_rates[i], 10) - 10000;

			अगर (dअगरf < 0)
				dअगरf = -dअगरf;
			अगर (dअगरf < stream1->ctx->dc->config.vblank_alignment_max_frame_समय_dअगरf)
				वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

bool resource_are_streams_timing_synchronizable(
	काष्ठा dc_stream_state *stream1,
	काष्ठा dc_stream_state *stream2)
अणु
	अगर (stream1->timing.h_total != stream2->timing.h_total)
		वापस false;

	अगर (stream1->timing.v_total != stream2->timing.v_total)
		वापस false;

	अगर (stream1->timing.h_addressable
				!= stream2->timing.h_addressable)
		वापस false;

	अगर (stream1->timing.v_addressable
				!= stream2->timing.v_addressable)
		वापस false;

	अगर (stream1->timing.v_front_porch
				!= stream2->timing.v_front_porch)
		वापस false;

	अगर (stream1->timing.pix_clk_100hz
				!= stream2->timing.pix_clk_100hz)
		वापस false;

	अगर (stream1->clamping.c_depth != stream2->clamping.c_depth)
		वापस false;

	अगर (stream1->phy_pix_clk != stream2->phy_pix_clk
			&& (!dc_is_dp_संकेत(stream1->संकेत)
			|| !dc_is_dp_संकेत(stream2->संकेत)))
		वापस false;

	अगर (stream1->view_क्रमmat != stream2->view_क्रमmat)
		वापस false;

	अगर (stream1->ignore_msa_timing_param || stream2->ignore_msa_timing_param)
		वापस false;

	वापस true;
पूर्ण
अटल bool is_dp_and_hdmi_sharable(
		काष्ठा dc_stream_state *stream1,
		काष्ठा dc_stream_state *stream2)
अणु
	अगर (stream1->ctx->dc->caps.disable_dp_clk_share)
		वापस false;

	अगर (stream1->clamping.c_depth != COLOR_DEPTH_888 ||
		stream2->clamping.c_depth != COLOR_DEPTH_888)
		वापस false;

	वापस true;

पूर्ण

अटल bool is_sharable_clk_src(
	स्थिर काष्ठा pipe_ctx *pipe_with_clk_src,
	स्थिर काष्ठा pipe_ctx *pipe)
अणु
	अगर (pipe_with_clk_src->घड़ी_source == शून्य)
		वापस false;

	अगर (pipe_with_clk_src->stream->संकेत == SIGNAL_TYPE_VIRTUAL)
		वापस false;

	अगर (dc_is_dp_संकेत(pipe_with_clk_src->stream->संकेत) ||
		(dc_is_dp_संकेत(pipe->stream->संकेत) &&
		!is_dp_and_hdmi_sharable(pipe_with_clk_src->stream,
				     pipe->stream)))
		वापस false;

	अगर (dc_is_hdmi_संकेत(pipe_with_clk_src->stream->संकेत)
			&& dc_is_dual_link_संकेत(pipe->stream->संकेत))
		वापस false;

	अगर (dc_is_hdmi_संकेत(pipe->stream->संकेत)
			&& dc_is_dual_link_संकेत(pipe_with_clk_src->stream->संकेत))
		वापस false;

	अगर (!resource_are_streams_timing_synchronizable(
			pipe_with_clk_src->stream, pipe->stream))
		वापस false;

	वापस true;
पूर्ण

काष्ठा घड़ी_source *resource_find_used_clk_src_क्रम_sharing(
					काष्ठा resource_context *res_ctx,
					काष्ठा pipe_ctx *pipe_ctx)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		अगर (is_sharable_clk_src(&res_ctx->pipe_ctx[i], pipe_ctx))
			वापस res_ctx->pipe_ctx[i].घड़ी_source;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल क्रमागत pixel_क्रमmat convert_pixel_क्रमmat_to_dalsurface(
		क्रमागत surface_pixel_क्रमmat surface_pixel_क्रमmat)
अणु
	क्रमागत pixel_क्रमmat dal_pixel_क्रमmat = PIXEL_FORMAT_UNKNOWN;

	चयन (surface_pixel_क्रमmat) अणु
	हाल SURFACE_PIXEL_FORMAT_GRPH_PALETA_256_COLORS:
		dal_pixel_क्रमmat = PIXEL_FORMAT_INDEX8;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB1555:
		dal_pixel_क्रमmat = PIXEL_FORMAT_RGB565;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_RGB565:
		dal_pixel_क्रमmat = PIXEL_FORMAT_RGB565;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB8888:
		dal_pixel_क्रमmat = PIXEL_FORMAT_ARGB8888;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR8888:
		dal_pixel_क्रमmat = PIXEL_FORMAT_ARGB8888;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010:
		dal_pixel_क्रमmat = PIXEL_FORMAT_ARGB2101010;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010:
		dal_pixel_क्रमmat = PIXEL_FORMAT_ARGB2101010;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010_XR_BIAS:
		dal_pixel_क्रमmat = PIXEL_FORMAT_ARGB2101010_XRBIAS;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616F:
		dal_pixel_क्रमmat = PIXEL_FORMAT_FP16;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_VIDEO_420_YCbCr:
	हाल SURFACE_PIXEL_FORMAT_VIDEO_420_YCrCb:
		dal_pixel_क्रमmat = PIXEL_FORMAT_420BPP8;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCbCr:
	हाल SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCrCb:
		dal_pixel_क्रमmat = PIXEL_FORMAT_420BPP10;
		अवरोध;
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616:
	शेष:
		dal_pixel_क्रमmat = PIXEL_FORMAT_UNKNOWN;
		अवरोध;
	पूर्ण
	वापस dal_pixel_क्रमmat;
पूर्ण

अटल अंतरभूत व्योम get_vp_scan_direction(
	क्रमागत dc_rotation_angle rotation,
	bool horizontal_mirror,
	bool *orthogonal_rotation,
	bool *flip_vert_scan_dir,
	bool *flip_horz_scan_dir)
अणु
	*orthogonal_rotation = false;
	*flip_vert_scan_dir = false;
	*flip_horz_scan_dir = false;
	अगर (rotation == ROTATION_ANGLE_180) अणु
		*flip_vert_scan_dir = true;
		*flip_horz_scan_dir = true;
	पूर्ण अन्यथा अगर (rotation == ROTATION_ANGLE_90) अणु
		*orthogonal_rotation = true;
		*flip_horz_scan_dir = true;
	पूर्ण अन्यथा अगर (rotation == ROTATION_ANGLE_270) अणु
		*orthogonal_rotation = true;
		*flip_vert_scan_dir = true;
	पूर्ण

	अगर (horizontal_mirror)
		*flip_horz_scan_dir = !*flip_horz_scan_dir;
पूर्ण

पूर्णांक get_num_mpc_splits(काष्ठा pipe_ctx *pipe)
अणु
	पूर्णांक mpc_split_count = 0;
	काष्ठा pipe_ctx *other_pipe = pipe->bottom_pipe;

	जबतक (other_pipe && other_pipe->plane_state == pipe->plane_state) अणु
		mpc_split_count++;
		other_pipe = other_pipe->bottom_pipe;
	पूर्ण
	other_pipe = pipe->top_pipe;
	जबतक (other_pipe && other_pipe->plane_state == pipe->plane_state) अणु
		mpc_split_count++;
		other_pipe = other_pipe->top_pipe;
	पूर्ण

	वापस mpc_split_count;
पूर्ण

पूर्णांक get_num_odm_splits(काष्ठा pipe_ctx *pipe)
अणु
	पूर्णांक odm_split_count = 0;
	काष्ठा pipe_ctx *next_pipe = pipe->next_odm_pipe;
	जबतक (next_pipe) अणु
		odm_split_count++;
		next_pipe = next_pipe->next_odm_pipe;
	पूर्ण
	pipe = pipe->prev_odm_pipe;
	जबतक (pipe) अणु
		odm_split_count++;
		pipe = pipe->prev_odm_pipe;
	पूर्ण
	वापस odm_split_count;
पूर्ण

अटल व्योम calculate_split_count_and_index(काष्ठा pipe_ctx *pipe_ctx, पूर्णांक *split_count, पूर्णांक *split_idx)
अणु
	*split_count = get_num_odm_splits(pipe_ctx);
	*split_idx = 0;
	अगर (*split_count == 0) अणु
		/*Check क्रम mpc split*/
		काष्ठा pipe_ctx *split_pipe = pipe_ctx->top_pipe;

		*split_count = get_num_mpc_splits(pipe_ctx);
		जबतक (split_pipe && split_pipe->plane_state == pipe_ctx->plane_state) अणु
			(*split_idx)++;
			split_pipe = split_pipe->top_pipe;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*Get odm split index*/
		काष्ठा pipe_ctx *split_pipe = pipe_ctx->prev_odm_pipe;

		जबतक (split_pipe) अणु
			(*split_idx)++;
			split_pipe = split_pipe->prev_odm_pipe;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम calculate_viewport(काष्ठा pipe_ctx *pipe_ctx)
अणु
	स्थिर काष्ठा dc_plane_state *plane_state = pipe_ctx->plane_state;
	स्थिर काष्ठा dc_stream_state *stream = pipe_ctx->stream;
	काष्ठा scaler_data *data = &pipe_ctx->plane_res.scl_data;
	काष्ठा rect surf_src = plane_state->src_rect;
	काष्ठा rect clip, dest;
	पूर्णांक vpc_भाग = (data->क्रमmat == PIXEL_FORMAT_420BPP8
			|| data->क्रमmat == PIXEL_FORMAT_420BPP10) ? 2 : 1;
	पूर्णांक split_count = 0;
	पूर्णांक split_idx = 0;
	bool orthogonal_rotation, flip_y_start, flip_x_start;

	calculate_split_count_and_index(pipe_ctx, &split_count, &split_idx);

	अगर (stream->view_क्रमmat == VIEW_3D_FORMAT_SIDE_BY_SIDE ||
		stream->view_क्रमmat == VIEW_3D_FORMAT_TOP_AND_BOTTOM) अणु
		split_count = 0;
		split_idx = 0;
	पूर्ण

	/* The actual clip is an पूर्णांकersection between stream
	 * source and surface clip
	 */
	dest = plane_state->dst_rect;
	clip.x = stream->src.x > plane_state->clip_rect.x ?
			stream->src.x : plane_state->clip_rect.x;

	clip.width = stream->src.x + stream->src.width <
			plane_state->clip_rect.x + plane_state->clip_rect.width ?
			stream->src.x + stream->src.width - clip.x :
			plane_state->clip_rect.x + plane_state->clip_rect.width - clip.x ;

	clip.y = stream->src.y > plane_state->clip_rect.y ?
			stream->src.y : plane_state->clip_rect.y;

	clip.height = stream->src.y + stream->src.height <
			plane_state->clip_rect.y + plane_state->clip_rect.height ?
			stream->src.y + stream->src.height - clip.y :
			plane_state->clip_rect.y + plane_state->clip_rect.height - clip.y ;

	/*
	 * Need to calculate how scan origin is shअगरted in vp space
	 * to correctly rotate clip and dst
	 */
	get_vp_scan_direction(
			plane_state->rotation,
			plane_state->horizontal_mirror,
			&orthogonal_rotation,
			&flip_y_start,
			&flip_x_start);

	अगर (orthogonal_rotation) अणु
		swap(clip.x, clip.y);
		swap(clip.width, clip.height);
		swap(dest.x, dest.y);
		swap(dest.width, dest.height);
	पूर्ण
	अगर (flip_x_start) अणु
		clip.x = dest.x + dest.width - clip.x - clip.width;
		dest.x = 0;
	पूर्ण
	अगर (flip_y_start) अणु
		clip.y = dest.y + dest.height - clip.y - clip.height;
		dest.y = 0;
	पूर्ण

	/* offset = surf_src.ofs + (clip.ofs - surface->dst_rect.ofs) * scl_ratio
	 * num_pixels = clip.num_pix * scl_ratio
	 */
	data->viewport.x = surf_src.x + (clip.x - dest.x) * surf_src.width / dest.width;
	data->viewport.width = clip.width * surf_src.width / dest.width;

	data->viewport.y = surf_src.y + (clip.y - dest.y) * surf_src.height / dest.height;
	data->viewport.height = clip.height * surf_src.height / dest.height;

	/* Handle split */
	अगर (split_count) अणु
		/* extra pixels in the भागision reमुख्यder need to go to pipes after
		 * the extra pixel index minus one(epimo) defined here as:
		 */
		पूर्णांक epimo = 0;

		अगर (orthogonal_rotation) अणु
			अगर (flip_y_start)
				split_idx = split_count - split_idx;

			epimo = split_count - data->viewport.height % (split_count + 1);

			data->viewport.y += (data->viewport.height / (split_count + 1)) * split_idx;
			अगर (split_idx > epimo)
				data->viewport.y += split_idx - epimo - 1;
			data->viewport.height = data->viewport.height / (split_count + 1) + (split_idx > epimo ? 1 : 0);
		पूर्ण अन्यथा अणु
			अगर (flip_x_start)
				split_idx = split_count - split_idx;

			epimo = split_count - data->viewport.width % (split_count + 1);

			data->viewport.x += (data->viewport.width / (split_count + 1)) * split_idx;
			अगर (split_idx > epimo)
				data->viewport.x += split_idx - epimo - 1;
			data->viewport.width = data->viewport.width / (split_count + 1) + (split_idx > epimo ? 1 : 0);
		पूर्ण
	पूर्ण

	/* Round करोwn, compensate in init */
	data->viewport_c.x = data->viewport.x / vpc_भाग;
	data->viewport_c.y = data->viewport.y / vpc_भाग;
	data->inits.h_c = (data->viewport.x % vpc_भाग) != 0 ? dc_fixpt_half : dc_fixpt_zero;
	data->inits.v_c = (data->viewport.y % vpc_भाग) != 0 ? dc_fixpt_half : dc_fixpt_zero;

	/* Round up, assume original video size always even dimensions */
	data->viewport_c.width = (data->viewport.width + vpc_भाग - 1) / vpc_भाग;
	data->viewport_c.height = (data->viewport.height + vpc_भाग - 1) / vpc_भाग;

	data->viewport_unadjusted = data->viewport;
	data->viewport_c_unadjusted = data->viewport_c;
पूर्ण

अटल व्योम calculate_recout(काष्ठा pipe_ctx *pipe_ctx)
अणु
	स्थिर काष्ठा dc_plane_state *plane_state = pipe_ctx->plane_state;
	स्थिर काष्ठा dc_stream_state *stream = pipe_ctx->stream;
	काष्ठा scaler_data *data = &pipe_ctx->plane_res.scl_data;
	काष्ठा rect surf_clip = plane_state->clip_rect;
	bool pri_split_tb = pipe_ctx->bottom_pipe &&
			pipe_ctx->bottom_pipe->plane_state == pipe_ctx->plane_state &&
			stream->view_क्रमmat == VIEW_3D_FORMAT_TOP_AND_BOTTOM;
	bool sec_split_tb = pipe_ctx->top_pipe &&
			pipe_ctx->top_pipe->plane_state == pipe_ctx->plane_state &&
			stream->view_क्रमmat == VIEW_3D_FORMAT_TOP_AND_BOTTOM;
	पूर्णांक split_count = 0;
	पूर्णांक split_idx = 0;

	calculate_split_count_and_index(pipe_ctx, &split_count, &split_idx);

	/*
	 * Only the lefपंचांगost ODM pipe should be offset by a nonzero distance
	 */
	अगर (!pipe_ctx->prev_odm_pipe) अणु
		data->recout.x = stream->dst.x;
		अगर (stream->src.x < surf_clip.x)
			data->recout.x += (surf_clip.x - stream->src.x) * stream->dst.width
						/ stream->src.width;

	पूर्ण अन्यथा
		data->recout.x = 0;

	अगर (stream->src.x > surf_clip.x)
		surf_clip.width -= stream->src.x - surf_clip.x;
	data->recout.width = surf_clip.width * stream->dst.width / stream->src.width;
	अगर (data->recout.width + data->recout.x > stream->dst.x + stream->dst.width)
		data->recout.width = stream->dst.x + stream->dst.width - data->recout.x;

	data->recout.y = stream->dst.y;
	अगर (stream->src.y < surf_clip.y)
		data->recout.y += (surf_clip.y - stream->src.y) * stream->dst.height
						/ stream->src.height;
	अन्यथा अगर (stream->src.y > surf_clip.y)
		surf_clip.height -= stream->src.y - surf_clip.y;

	data->recout.height = surf_clip.height * stream->dst.height / stream->src.height;
	अगर (data->recout.height + data->recout.y > stream->dst.y + stream->dst.height)
		data->recout.height = stream->dst.y + stream->dst.height - data->recout.y;

	/* Handle h & v split, handle rotation using viewport */
	अगर (sec_split_tb) अणु
		data->recout.y += data->recout.height / 2;
		/* Floor primary pipe, उच्चमान 2ndary pipe */
		data->recout.height = (data->recout.height + 1) / 2;
	पूर्ण अन्यथा अगर (pri_split_tb)
		data->recout.height /= 2;
	अन्यथा अगर (split_count) अणु
		/* extra pixels in the भागision reमुख्यder need to go to pipes after
		 * the extra pixel index minus one(epimo) defined here as:
		 */
		पूर्णांक epimo = split_count - data->recout.width % (split_count + 1);

		/*no recout offset due to odm */
		अगर (!pipe_ctx->next_odm_pipe && !pipe_ctx->prev_odm_pipe) अणु
			data->recout.x += (data->recout.width / (split_count + 1)) * split_idx;
			अगर (split_idx > epimo)
				data->recout.x += split_idx - epimo - 1;
		पूर्ण
		data->recout.width = data->recout.width / (split_count + 1) + (split_idx > epimo ? 1 : 0);
	पूर्ण
पूर्ण

अटल व्योम calculate_scaling_ratios(काष्ठा pipe_ctx *pipe_ctx)
अणु
	स्थिर काष्ठा dc_plane_state *plane_state = pipe_ctx->plane_state;
	स्थिर काष्ठा dc_stream_state *stream = pipe_ctx->stream;
	काष्ठा rect surf_src = plane_state->src_rect;
	स्थिर पूर्णांक in_w = stream->src.width;
	स्थिर पूर्णांक in_h = stream->src.height;
	स्थिर पूर्णांक out_w = stream->dst.width;
	स्थिर पूर्णांक out_h = stream->dst.height;

	/*Swap surf_src height and width since scaling ratios are in recout rotation*/
	अगर (pipe_ctx->plane_state->rotation == ROTATION_ANGLE_90 ||
			pipe_ctx->plane_state->rotation == ROTATION_ANGLE_270)
		swap(surf_src.height, surf_src.width);

	pipe_ctx->plane_res.scl_data.ratios.horz = dc_fixpt_from_fraction(
					surf_src.width,
					plane_state->dst_rect.width);
	pipe_ctx->plane_res.scl_data.ratios.vert = dc_fixpt_from_fraction(
					surf_src.height,
					plane_state->dst_rect.height);

	अगर (stream->view_क्रमmat == VIEW_3D_FORMAT_SIDE_BY_SIDE)
		pipe_ctx->plane_res.scl_data.ratios.horz.value *= 2;
	अन्यथा अगर (stream->view_क्रमmat == VIEW_3D_FORMAT_TOP_AND_BOTTOM)
		pipe_ctx->plane_res.scl_data.ratios.vert.value *= 2;

	pipe_ctx->plane_res.scl_data.ratios.vert.value = भाग64_s64(
		pipe_ctx->plane_res.scl_data.ratios.vert.value * in_h, out_h);
	pipe_ctx->plane_res.scl_data.ratios.horz.value = भाग64_s64(
		pipe_ctx->plane_res.scl_data.ratios.horz.value * in_w, out_w);

	pipe_ctx->plane_res.scl_data.ratios.horz_c = pipe_ctx->plane_res.scl_data.ratios.horz;
	pipe_ctx->plane_res.scl_data.ratios.vert_c = pipe_ctx->plane_res.scl_data.ratios.vert;

	अगर (pipe_ctx->plane_res.scl_data.क्रमmat == PIXEL_FORMAT_420BPP8
			|| pipe_ctx->plane_res.scl_data.क्रमmat == PIXEL_FORMAT_420BPP10) अणु
		pipe_ctx->plane_res.scl_data.ratios.horz_c.value /= 2;
		pipe_ctx->plane_res.scl_data.ratios.vert_c.value /= 2;
	पूर्ण
	pipe_ctx->plane_res.scl_data.ratios.horz = dc_fixpt_truncate(
			pipe_ctx->plane_res.scl_data.ratios.horz, 19);
	pipe_ctx->plane_res.scl_data.ratios.vert = dc_fixpt_truncate(
			pipe_ctx->plane_res.scl_data.ratios.vert, 19);
	pipe_ctx->plane_res.scl_data.ratios.horz_c = dc_fixpt_truncate(
			pipe_ctx->plane_res.scl_data.ratios.horz_c, 19);
	pipe_ctx->plane_res.scl_data.ratios.vert_c = dc_fixpt_truncate(
			pipe_ctx->plane_res.scl_data.ratios.vert_c, 19);
पूर्ण

अटल अंतरभूत व्योम adjust_vp_and_init_क्रम_seamless_clip(
		bool flip_scan_dir,
		पूर्णांक recout_skip,
		पूर्णांक src_size,
		पूर्णांक taps,
		काष्ठा fixed31_32 ratio,
		काष्ठा fixed31_32 *init,
		पूर्णांक *vp_offset,
		पूर्णांक *vp_size)
अणु
	अगर (!flip_scan_dir) अणु
		/* Adjust क्रम viewport end clip-off */
		अगर ((*vp_offset + *vp_size) < src_size) अणु
			पूर्णांक vp_clip = src_size - *vp_size - *vp_offset;
			पूर्णांक पूर्णांक_part = dc_fixpt_न्यूनमान(dc_fixpt_sub(*init, ratio));

			पूर्णांक_part = पूर्णांक_part > 0 ? पूर्णांक_part : 0;
			*vp_size += पूर्णांक_part < vp_clip ? पूर्णांक_part : vp_clip;
		पूर्ण

		/* Adjust क्रम non-0 viewport offset */
		अगर (*vp_offset) अणु
			पूर्णांक पूर्णांक_part;

			*init = dc_fixpt_add(*init, dc_fixpt_mul_पूर्णांक(ratio, recout_skip));
			पूर्णांक_part = dc_fixpt_न्यूनमान(*init) - *vp_offset;
			अगर (पूर्णांक_part < taps) अणु
				पूर्णांक पूर्णांक_adj = *vp_offset >= (taps - पूर्णांक_part) ?
							(taps - पूर्णांक_part) : *vp_offset;
				*vp_offset -= पूर्णांक_adj;
				*vp_size += पूर्णांक_adj;
				पूर्णांक_part += पूर्णांक_adj;
			पूर्ण अन्यथा अगर (पूर्णांक_part > taps) अणु
				*vp_offset += पूर्णांक_part - taps;
				*vp_size -= पूर्णांक_part - taps;
				पूर्णांक_part = taps;
			पूर्ण
			init->value &= 0xffffffff;
			*init = dc_fixpt_add_पूर्णांक(*init, पूर्णांक_part);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Adjust क्रम non-0 viewport offset */
		अगर (*vp_offset) अणु
			पूर्णांक पूर्णांक_part = dc_fixpt_न्यूनमान(dc_fixpt_sub(*init, ratio));

			पूर्णांक_part = पूर्णांक_part > 0 ? पूर्णांक_part : 0;
			*vp_size += पूर्णांक_part < *vp_offset ? पूर्णांक_part : *vp_offset;
			*vp_offset -= पूर्णांक_part < *vp_offset ? पूर्णांक_part : *vp_offset;
		पूर्ण

		/* Adjust क्रम viewport end clip-off */
		अगर ((*vp_offset + *vp_size) < src_size) अणु
			पूर्णांक पूर्णांक_part;
			पूर्णांक end_offset = src_size - *vp_offset - *vp_size;

			/*
			 * this is init अगर vp had no offset, keep in mind this is from the
			 * right side of vp due to scan direction
			 */
			*init = dc_fixpt_add(*init, dc_fixpt_mul_पूर्णांक(ratio, recout_skip));
			/*
			 * this is the dअगरference between first pixel of viewport available to पढ़ो
			 * and init position, takning पूर्णांकo account scan direction
			 */
			पूर्णांक_part = dc_fixpt_न्यूनमान(*init) - end_offset;
			अगर (पूर्णांक_part < taps) अणु
				पूर्णांक पूर्णांक_adj = end_offset >= (taps - पूर्णांक_part) ?
							(taps - पूर्णांक_part) : end_offset;
				*vp_size += पूर्णांक_adj;
				पूर्णांक_part += पूर्णांक_adj;
			पूर्ण अन्यथा अगर (पूर्णांक_part > taps) अणु
				*vp_size += पूर्णांक_part - taps;
				पूर्णांक_part = taps;
			पूर्ण
			init->value &= 0xffffffff;
			*init = dc_fixpt_add_पूर्णांक(*init, पूर्णांक_part);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम calculate_inits_and_adj_vp(काष्ठा pipe_ctx *pipe_ctx)
अणु
	स्थिर काष्ठा dc_plane_state *plane_state = pipe_ctx->plane_state;
	स्थिर काष्ठा dc_stream_state *stream = pipe_ctx->stream;
	काष्ठा pipe_ctx *odm_pipe = pipe_ctx;
	काष्ठा scaler_data *data = &pipe_ctx->plane_res.scl_data;
	काष्ठा rect src = pipe_ctx->plane_state->src_rect;
	पूर्णांक recout_skip_h, recout_skip_v, surf_size_h, surf_size_v;
	पूर्णांक vpc_भाग = (data->क्रमmat == PIXEL_FORMAT_420BPP8
			|| data->क्रमmat == PIXEL_FORMAT_420BPP10) ? 2 : 1;
	bool orthogonal_rotation, flip_vert_scan_dir, flip_horz_scan_dir;
	पूर्णांक odm_idx = 0;

	/*
	 * Need to calculate the scan direction क्रम viewport to make adjusपंचांगents
	 */
	get_vp_scan_direction(
			plane_state->rotation,
			plane_state->horizontal_mirror,
			&orthogonal_rotation,
			&flip_vert_scan_dir,
			&flip_horz_scan_dir);

	/* Calculate src rect rotation adjusted to recout space */
	surf_size_h = src.x + src.width;
	surf_size_v = src.y + src.height;
	अगर (flip_horz_scan_dir)
		src.x = 0;
	अगर (flip_vert_scan_dir)
		src.y = 0;
	अगर (orthogonal_rotation) अणु
		swap(src.x, src.y);
		swap(src.width, src.height);
	पूर्ण

	/*modअगरied recout_skip_h calculation due to odm having no recout offset*/
	जबतक (odm_pipe->prev_odm_pipe) अणु
		odm_idx++;
		odm_pipe = odm_pipe->prev_odm_pipe;
	पूर्ण
	/*odm_pipe is the lefपंचांगost pipe in the ODM group*/
	recout_skip_h = odm_idx * data->recout.width;

	/* Recout matching initial vp offset = recout_offset - (stream dst offset +
	 *			((surf dst offset - stream src offset) * 1/ stream scaling ratio)
	 *			- (surf surf_src offset * 1/ full scl ratio))
	 */
	recout_skip_h += odm_pipe->plane_res.scl_data.recout.x
				- (stream->dst.x + (plane_state->dst_rect.x - stream->src.x)
					* stream->dst.width / stream->src.width -
					src.x * plane_state->dst_rect.width / src.width
					* stream->dst.width / stream->src.width);


	recout_skip_v = data->recout.y - (stream->dst.y + (plane_state->dst_rect.y - stream->src.y)
					* stream->dst.height / stream->src.height -
					src.y * plane_state->dst_rect.height / src.height
					* stream->dst.height / stream->src.height);
	अगर (orthogonal_rotation)
		swap(recout_skip_h, recout_skip_v);
	/*
	 * Init calculated according to क्रमmula:
	 * 	init = (scaling_ratio + number_of_taps + 1) / 2
	 * 	init_bot = init + scaling_ratio
	 * 	init_c = init + truncated_vp_c_offset(from calculate viewport)
	 */
	data->inits.h = dc_fixpt_truncate(dc_fixpt_भाग_पूर्णांक(
			dc_fixpt_add_पूर्णांक(data->ratios.horz, data->taps.h_taps + 1), 2), 19);

	data->inits.h_c = dc_fixpt_truncate(dc_fixpt_add(data->inits.h_c, dc_fixpt_भाग_पूर्णांक(
			dc_fixpt_add_पूर्णांक(data->ratios.horz_c, data->taps.h_taps_c + 1), 2)), 19);

	data->inits.v = dc_fixpt_truncate(dc_fixpt_भाग_पूर्णांक(
			dc_fixpt_add_पूर्णांक(data->ratios.vert, data->taps.v_taps + 1), 2), 19);

	data->inits.v_c = dc_fixpt_truncate(dc_fixpt_add(data->inits.v_c, dc_fixpt_भाग_पूर्णांक(
			dc_fixpt_add_पूर्णांक(data->ratios.vert_c, data->taps.v_taps_c + 1), 2)), 19);

	/*
	 * Taps, inits and scaling ratios are in recout space need to rotate
	 * to viewport rotation beक्रमe adjusपंचांगent
	 */
	adjust_vp_and_init_क्रम_seamless_clip(
			flip_horz_scan_dir,
			recout_skip_h,
			surf_size_h,
			orthogonal_rotation ? data->taps.v_taps : data->taps.h_taps,
			orthogonal_rotation ? data->ratios.vert : data->ratios.horz,
			orthogonal_rotation ? &data->inits.v : &data->inits.h,
			&data->viewport.x,
			&data->viewport.width);
	adjust_vp_and_init_क्रम_seamless_clip(
			flip_horz_scan_dir,
			recout_skip_h,
			surf_size_h / vpc_भाग,
			orthogonal_rotation ? data->taps.v_taps_c : data->taps.h_taps_c,
			orthogonal_rotation ? data->ratios.vert_c : data->ratios.horz_c,
			orthogonal_rotation ? &data->inits.v_c : &data->inits.h_c,
			&data->viewport_c.x,
			&data->viewport_c.width);
	adjust_vp_and_init_क्रम_seamless_clip(
			flip_vert_scan_dir,
			recout_skip_v,
			surf_size_v,
			orthogonal_rotation ? data->taps.h_taps : data->taps.v_taps,
			orthogonal_rotation ? data->ratios.horz : data->ratios.vert,
			orthogonal_rotation ? &data->inits.h : &data->inits.v,
			&data->viewport.y,
			&data->viewport.height);
	adjust_vp_and_init_क्रम_seamless_clip(
			flip_vert_scan_dir,
			recout_skip_v,
			surf_size_v / vpc_भाग,
			orthogonal_rotation ? data->taps.h_taps_c : data->taps.v_taps_c,
			orthogonal_rotation ? data->ratios.horz_c : data->ratios.vert_c,
			orthogonal_rotation ? &data->inits.h_c : &data->inits.v_c,
			&data->viewport_c.y,
			&data->viewport_c.height);

	/* Interlaced inits based on final vert inits */
	data->inits.v_bot = dc_fixpt_add(data->inits.v, data->ratios.vert);
	data->inits.v_c_bot = dc_fixpt_add(data->inits.v_c, data->ratios.vert_c);

पूर्ण

/*
 * When handling 270 rotation in mixed SLS mode, we have
 * stream->timing.h_border_left that is non zero.  If we are करोing
 * pipe-splitting, this h_border_left value माला_लो added to recout.x and when it
 * calls calculate_inits_and_adj_vp() and
 * adjust_vp_and_init_क्रम_seamless_clip(), it can cause viewport.height क्रम a
 * pipe to be incorrect.
 *
 * To fix this, instead of using stream->timing.h_border_left, we can use
 * stream->dst.x to represent the border instead.  So we will set h_border_left
 * to 0 and shअगरt the appropriate amount in stream->dst.x.  We will then
 * perक्रमm all calculations in resource_build_scaling_params() based on this
 * and then restore the h_border_left and stream->dst.x to their original
 * values.
 *
 * shअगरt_border_left_to_dst() will shअगरt the amount of h_border_left to
 * stream->dst.x and set h_border_left to 0.  restore_border_left_from_dst()
 * will restore h_border_left and stream->dst.x back to their original values
 * We also need to make sure pipe_ctx->plane_res.scl_data.h_active uses the
 * original h_border_left value in its calculation.
 */
अटल पूर्णांक shअगरt_border_left_to_dst(काष्ठा pipe_ctx *pipe_ctx)
अणु
	पूर्णांक store_h_border_left = pipe_ctx->stream->timing.h_border_left;

	अगर (store_h_border_left) अणु
		pipe_ctx->stream->timing.h_border_left = 0;
		pipe_ctx->stream->dst.x += store_h_border_left;
	पूर्ण
	वापस store_h_border_left;
पूर्ण

अटल व्योम restore_border_left_from_dst(काष्ठा pipe_ctx *pipe_ctx,
					 पूर्णांक store_h_border_left)
अणु
	pipe_ctx->stream->dst.x -= store_h_border_left;
	pipe_ctx->stream->timing.h_border_left = store_h_border_left;
पूर्ण

bool resource_build_scaling_params(काष्ठा pipe_ctx *pipe_ctx)
अणु
	स्थिर काष्ठा dc_plane_state *plane_state = pipe_ctx->plane_state;
	काष्ठा dc_crtc_timing *timing = &pipe_ctx->stream->timing;
	bool res = false;
	पूर्णांक store_h_border_left = shअगरt_border_left_to_dst(pipe_ctx);
	DC_LOGGER_INIT(pipe_ctx->stream->ctx->logger);
	/* Important: scaling ratio calculation requires pixel क्रमmat,
	 * lb depth calculation requires recout and taps require scaling ratios.
	 * Inits require viewport, taps, ratios and recout of split pipe
	 */
	pipe_ctx->plane_res.scl_data.क्रमmat = convert_pixel_क्रमmat_to_dalsurface(
			pipe_ctx->plane_state->क्रमmat);

	calculate_scaling_ratios(pipe_ctx);

	calculate_viewport(pipe_ctx);

	अगर (pipe_ctx->plane_res.scl_data.viewport.height < MIN_VIEWPORT_SIZE ||
		pipe_ctx->plane_res.scl_data.viewport.width < MIN_VIEWPORT_SIZE) अणु
		अगर (store_h_border_left) अणु
			restore_border_left_from_dst(pipe_ctx,
				store_h_border_left);
		पूर्ण
		वापस false;
	पूर्ण

	calculate_recout(pipe_ctx);

	/**
	 * Setting line buffer pixel depth to 24bpp yields banding
	 * on certain displays, such as the Sharp 4k
	 */
	pipe_ctx->plane_res.scl_data.lb_params.depth = LB_PIXEL_DEPTH_30BPP;
	pipe_ctx->plane_res.scl_data.lb_params.alpha_en = plane_state->per_pixel_alpha;

	pipe_ctx->plane_res.scl_data.recout.x += timing->h_border_left;
	pipe_ctx->plane_res.scl_data.recout.y += timing->v_border_top;

	pipe_ctx->plane_res.scl_data.h_active = timing->h_addressable +
		store_h_border_left + timing->h_border_right;
	pipe_ctx->plane_res.scl_data.v_active = timing->v_addressable +
		timing->v_border_top + timing->v_border_bottom;
	अगर (pipe_ctx->next_odm_pipe || pipe_ctx->prev_odm_pipe)
		pipe_ctx->plane_res.scl_data.h_active /= get_num_odm_splits(pipe_ctx) + 1;

	/* Taps calculations */
	अगर (pipe_ctx->plane_res.xfm != शून्य)
		res = pipe_ctx->plane_res.xfm->funcs->transक्रमm_get_optimal_number_of_taps(
				pipe_ctx->plane_res.xfm, &pipe_ctx->plane_res.scl_data, &plane_state->scaling_quality);

	अगर (pipe_ctx->plane_res.dpp != शून्य)
		res = pipe_ctx->plane_res.dpp->funcs->dpp_get_optimal_number_of_taps(
				pipe_ctx->plane_res.dpp, &pipe_ctx->plane_res.scl_data, &plane_state->scaling_quality);


	अगर (!res) अणु
		/* Try 24 bpp linebuffer */
		pipe_ctx->plane_res.scl_data.lb_params.depth = LB_PIXEL_DEPTH_24BPP;

		अगर (pipe_ctx->plane_res.xfm != शून्य)
			res = pipe_ctx->plane_res.xfm->funcs->transक्रमm_get_optimal_number_of_taps(
					pipe_ctx->plane_res.xfm,
					&pipe_ctx->plane_res.scl_data,
					&plane_state->scaling_quality);

		अगर (pipe_ctx->plane_res.dpp != शून्य)
			res = pipe_ctx->plane_res.dpp->funcs->dpp_get_optimal_number_of_taps(
					pipe_ctx->plane_res.dpp,
					&pipe_ctx->plane_res.scl_data,
					&plane_state->scaling_quality);
	पूर्ण

	अगर (res)
		/* May need to re-check lb size after this in some obscure scenario */
		calculate_inits_and_adj_vp(pipe_ctx);

	DC_LOG_SCALER("%s pipe %d:\nViewport: height:%d width:%d x:%d y:%d  Recout: height:%d width:%d x:%d y:%d  HACTIVE:%d VACTIVE:%d\n"
			"src_rect: height:%d width:%d x:%d y:%d  dst_rect: height:%d width:%d x:%d y:%d  clip_rect: height:%d width:%d x:%d y:%d\n",
			__func__,
			pipe_ctx->pipe_idx,
			pipe_ctx->plane_res.scl_data.viewport.height,
			pipe_ctx->plane_res.scl_data.viewport.width,
			pipe_ctx->plane_res.scl_data.viewport.x,
			pipe_ctx->plane_res.scl_data.viewport.y,
			pipe_ctx->plane_res.scl_data.recout.height,
			pipe_ctx->plane_res.scl_data.recout.width,
			pipe_ctx->plane_res.scl_data.recout.x,
			pipe_ctx->plane_res.scl_data.recout.y,
			pipe_ctx->plane_res.scl_data.h_active,
			pipe_ctx->plane_res.scl_data.v_active,
			plane_state->src_rect.height,
			plane_state->src_rect.width,
			plane_state->src_rect.x,
			plane_state->src_rect.y,
			plane_state->dst_rect.height,
			plane_state->dst_rect.width,
			plane_state->dst_rect.x,
			plane_state->dst_rect.y,
			plane_state->clip_rect.height,
			plane_state->clip_rect.width,
			plane_state->clip_rect.x,
			plane_state->clip_rect.y);

	अगर (store_h_border_left)
		restore_border_left_from_dst(pipe_ctx, store_h_border_left);

	वापस res;
पूर्ण


क्रमागत dc_status resource_build_scaling_params_क्रम_context(
	स्थिर काष्ठा dc  *dc,
	काष्ठा dc_state *context)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		अगर (context->res_ctx.pipe_ctx[i].plane_state != शून्य &&
				context->res_ctx.pipe_ctx[i].stream != शून्य)
			अगर (!resource_build_scaling_params(&context->res_ctx.pipe_ctx[i]))
				वापस DC_FAIL_SCALING;
	पूर्ण

	वापस DC_OK;
पूर्ण

काष्ठा pipe_ctx *find_idle_secondary_pipe(
		काष्ठा resource_context *res_ctx,
		स्थिर काष्ठा resource_pool *pool,
		स्थिर काष्ठा pipe_ctx *primary_pipe)
अणु
	पूर्णांक i;
	काष्ठा pipe_ctx *secondary_pipe = शून्य;

	/*
	 * We add a preferred pipe mapping to aव्योम the chance that
	 * MPCCs alपढ़ोy in use will need to be reasचिन्हित to other trees.
	 * For example, अगर we went with the strict, assign backwards logic:
	 *
	 * (State 1)
	 * Display A on, no surface, top pipe = 0
	 * Display B on, no surface, top pipe = 1
	 *
	 * (State 2)
	 * Display A on, no surface, top pipe = 0
	 * Display B on, surface enable, top pipe = 1, bottom pipe = 5
	 *
	 * (State 3)
	 * Display A on, surface enable, top pipe = 0, bottom pipe = 5
	 * Display B on, surface enable, top pipe = 1, bottom pipe = 4
	 *
	 * The state 2->3 transition requires remapping MPCC 5 from display B
	 * to display A.
	 *
	 * However, with the preferred pipe logic, state 2 would look like:
	 *
	 * (State 2)
	 * Display A on, no surface, top pipe = 0
	 * Display B on, surface enable, top pipe = 1, bottom pipe = 4
	 *
	 * This would then cause 2->3 to not require remapping any MPCCs.
	 */
	अगर (primary_pipe) अणु
		पूर्णांक preferred_pipe_idx = (pool->pipe_count - 1) - primary_pipe->pipe_idx;
		अगर (res_ctx->pipe_ctx[preferred_pipe_idx].stream == शून्य) अणु
			secondary_pipe = &res_ctx->pipe_ctx[preferred_pipe_idx];
			secondary_pipe->pipe_idx = preferred_pipe_idx;
		पूर्ण
	पूर्ण

	/*
	 * search backwards क्रम the second pipe to keep pipe
	 * assignment more consistent
	 */
	अगर (!secondary_pipe)
		क्रम (i = pool->pipe_count - 1; i >= 0; i--) अणु
			अगर (res_ctx->pipe_ctx[i].stream == शून्य) अणु
				secondary_pipe = &res_ctx->pipe_ctx[i];
				secondary_pipe->pipe_idx = i;
				अवरोध;
			पूर्ण
		पूर्ण

	वापस secondary_pipe;
पूर्ण

काष्ठा pipe_ctx *resource_get_head_pipe_क्रम_stream(
		काष्ठा resource_context *res_ctx,
		काष्ठा dc_stream_state *stream)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		अगर (res_ctx->pipe_ctx[i].stream == stream
				&& !res_ctx->pipe_ctx[i].top_pipe
				&& !res_ctx->pipe_ctx[i].prev_odm_pipe)
			वापस &res_ctx->pipe_ctx[i];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा pipe_ctx *resource_get_tail_pipe(
		काष्ठा resource_context *res_ctx,
		काष्ठा pipe_ctx *head_pipe)
अणु
	काष्ठा pipe_ctx *tail_pipe;

	tail_pipe = head_pipe->bottom_pipe;

	जबतक (tail_pipe) अणु
		head_pipe = tail_pipe;
		tail_pipe = tail_pipe->bottom_pipe;
	पूर्ण

	वापस head_pipe;
पूर्ण

/*
 * A मुक्त_pipe क्रम a stream is defined here as a pipe
 * that has no surface attached yet
 */
अटल काष्ठा pipe_ctx *acquire_मुक्त_pipe_क्रम_head(
		काष्ठा dc_state *context,
		स्थिर काष्ठा resource_pool *pool,
		काष्ठा pipe_ctx *head_pipe)
अणु
	पूर्णांक i;
	काष्ठा resource_context *res_ctx = &context->res_ctx;

	अगर (!head_pipe->plane_state)
		वापस head_pipe;

	/* Re-use pipe alपढ़ोy acquired क्रम this stream अगर available*/
	क्रम (i = pool->pipe_count - 1; i >= 0; i--) अणु
		अगर (res_ctx->pipe_ctx[i].stream == head_pipe->stream &&
				!res_ctx->pipe_ctx[i].plane_state) अणु
			वापस &res_ctx->pipe_ctx[i];
		पूर्ण
	पूर्ण

	/*
	 * At this poपूर्णांक we have no re-useable pipe क्रम this stream and we need
	 * to acquire an idle one to satisfy the request
	 */

	अगर (!pool->funcs->acquire_idle_pipe_क्रम_layer)
		वापस शून्य;

	वापस pool->funcs->acquire_idle_pipe_क्रम_layer(context, pool, head_pipe->stream);
पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
अटल पूर्णांक acquire_first_split_pipe(
		काष्ठा resource_context *res_ctx,
		स्थिर काष्ठा resource_pool *pool,
		काष्ठा dc_stream_state *stream)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *split_pipe = &res_ctx->pipe_ctx[i];

		अगर (split_pipe->top_pipe &&
				split_pipe->top_pipe->plane_state == split_pipe->plane_state) अणु
			split_pipe->top_pipe->bottom_pipe = split_pipe->bottom_pipe;
			अगर (split_pipe->bottom_pipe)
				split_pipe->bottom_pipe->top_pipe = split_pipe->top_pipe;

			अगर (split_pipe->top_pipe->plane_state)
				resource_build_scaling_params(split_pipe->top_pipe);

			स_रखो(split_pipe, 0, माप(*split_pipe));
			split_pipe->stream_res.tg = pool->timing_generators[i];
			split_pipe->plane_res.hubp = pool->hubps[i];
			split_pipe->plane_res.ipp = pool->ipps[i];
			split_pipe->plane_res.dpp = pool->dpps[i];
			split_pipe->stream_res.opp = pool->opps[i];
			split_pipe->plane_res.mpcc_inst = pool->dpps[i]->inst;
			split_pipe->pipe_idx = i;

			split_pipe->stream = stream;
			वापस i;
		पूर्ण
	पूर्ण
	वापस -1;
पूर्ण
#पूर्ण_अगर

bool dc_add_plane_to_context(
		स्थिर काष्ठा dc *dc,
		काष्ठा dc_stream_state *stream,
		काष्ठा dc_plane_state *plane_state,
		काष्ठा dc_state *context)
अणु
	पूर्णांक i;
	काष्ठा resource_pool *pool = dc->res_pool;
	काष्ठा pipe_ctx *head_pipe, *tail_pipe, *मुक्त_pipe;
	काष्ठा dc_stream_status *stream_status = शून्य;

	क्रम (i = 0; i < context->stream_count; i++)
		अगर (context->streams[i] == stream) अणु
			stream_status = &context->stream_status[i];
			अवरोध;
		पूर्ण
	अगर (stream_status == शून्य) अणु
		dm_error("Existing stream not found; failed to attach surface!\n");
		वापस false;
	पूर्ण


	अगर (stream_status->plane_count == MAX_SURFACE_NUM) अणु
		dm_error("Surface: can not attach plane_state %p! Maximum is: %d\n",
				plane_state, MAX_SURFACE_NUM);
		वापस false;
	पूर्ण

	head_pipe = resource_get_head_pipe_क्रम_stream(&context->res_ctx, stream);

	अगर (!head_pipe) अणु
		dm_error("Head pipe not found for stream_state %p !\n", stream);
		वापस false;
	पूर्ण

	/* retain new surface, but only once per stream */
	dc_plane_state_retain(plane_state);

	जबतक (head_pipe) अणु
		मुक्त_pipe = acquire_मुक्त_pipe_क्रम_head(context, pool, head_pipe);

	#अगर defined(CONFIG_DRM_AMD_DC_DCN)
		अगर (!मुक्त_pipe) अणु
			पूर्णांक pipe_idx = acquire_first_split_pipe(&context->res_ctx, pool, stream);
			अगर (pipe_idx >= 0)
				मुक्त_pipe = &context->res_ctx.pipe_ctx[pipe_idx];
		पूर्ण
	#पूर्ण_अगर
		अगर (!मुक्त_pipe) अणु
			dc_plane_state_release(plane_state);
			वापस false;
		पूर्ण

		मुक्त_pipe->plane_state = plane_state;

		अगर (head_pipe != मुक्त_pipe) अणु
			tail_pipe = resource_get_tail_pipe(&context->res_ctx, head_pipe);
			ASSERT(tail_pipe);
			मुक्त_pipe->stream_res.tg = tail_pipe->stream_res.tg;
			मुक्त_pipe->stream_res.abm = tail_pipe->stream_res.abm;
			मुक्त_pipe->stream_res.opp = tail_pipe->stream_res.opp;
			मुक्त_pipe->stream_res.stream_enc = tail_pipe->stream_res.stream_enc;
			मुक्त_pipe->stream_res.audio = tail_pipe->stream_res.audio;
			मुक्त_pipe->घड़ी_source = tail_pipe->घड़ी_source;
			मुक्त_pipe->top_pipe = tail_pipe;
			tail_pipe->bottom_pipe = मुक्त_pipe;
			अगर (!मुक्त_pipe->next_odm_pipe && tail_pipe->next_odm_pipe && tail_pipe->next_odm_pipe->bottom_pipe) अणु
				मुक्त_pipe->next_odm_pipe = tail_pipe->next_odm_pipe->bottom_pipe;
				tail_pipe->next_odm_pipe->bottom_pipe->prev_odm_pipe = मुक्त_pipe;
			पूर्ण
			अगर (!मुक्त_pipe->prev_odm_pipe && tail_pipe->prev_odm_pipe && tail_pipe->prev_odm_pipe->bottom_pipe) अणु
				मुक्त_pipe->prev_odm_pipe = tail_pipe->prev_odm_pipe->bottom_pipe;
				tail_pipe->prev_odm_pipe->bottom_pipe->next_odm_pipe = मुक्त_pipe;
			पूर्ण
		पूर्ण
		head_pipe = head_pipe->next_odm_pipe;
	पूर्ण
	/* assign new surfaces*/
	stream_status->plane_states[stream_status->plane_count] = plane_state;

	stream_status->plane_count++;

	वापस true;
पूर्ण

bool dc_हटाओ_plane_from_context(
		स्थिर काष्ठा dc *dc,
		काष्ठा dc_stream_state *stream,
		काष्ठा dc_plane_state *plane_state,
		काष्ठा dc_state *context)
अणु
	पूर्णांक i;
	काष्ठा dc_stream_status *stream_status = शून्य;
	काष्ठा resource_pool *pool = dc->res_pool;

	क्रम (i = 0; i < context->stream_count; i++)
		अगर (context->streams[i] == stream) अणु
			stream_status = &context->stream_status[i];
			अवरोध;
		पूर्ण

	अगर (stream_status == शून्य) अणु
		dm_error("Existing stream not found; failed to remove plane.\n");
		वापस false;
	पूर्ण

	/* release pipe क्रम plane*/
	क्रम (i = pool->pipe_count - 1; i >= 0; i--) अणु
		काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];

		अगर (pipe_ctx->plane_state == plane_state) अणु
			अगर (pipe_ctx->top_pipe)
				pipe_ctx->top_pipe->bottom_pipe = pipe_ctx->bottom_pipe;

			/* Second condition is to aव्योम setting शून्य to top pipe
			 * of tail pipe making it look like head pipe in subsequent
			 * deletes
			 */
			अगर (pipe_ctx->bottom_pipe && pipe_ctx->top_pipe)
				pipe_ctx->bottom_pipe->top_pipe = pipe_ctx->top_pipe;

			/*
			 * For head pipe detach surfaces from pipe क्रम tail
			 * pipe just zero it out
			 */
			अगर (!pipe_ctx->top_pipe)
				pipe_ctx->plane_state = शून्य;
			अन्यथा
				स_रखो(pipe_ctx, 0, माप(*pipe_ctx));
		पूर्ण
	पूर्ण


	क्रम (i = 0; i < stream_status->plane_count; i++) अणु
		अगर (stream_status->plane_states[i] == plane_state) अणु

			dc_plane_state_release(stream_status->plane_states[i]);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == stream_status->plane_count) अणु
		dm_error("Existing plane_state not found; failed to detach it!\n");
		वापस false;
	पूर्ण

	stream_status->plane_count--;

	/* Start at the plane we've just released, and move all the planes one index क्रमward to "trim" the array */
	क्रम (; i < stream_status->plane_count; i++)
		stream_status->plane_states[i] = stream_status->plane_states[i + 1];

	stream_status->plane_states[stream_status->plane_count] = शून्य;

	वापस true;
पूर्ण

bool dc_rem_all_planes_क्रम_stream(
		स्थिर काष्ठा dc *dc,
		काष्ठा dc_stream_state *stream,
		काष्ठा dc_state *context)
अणु
	पूर्णांक i, old_plane_count;
	काष्ठा dc_stream_status *stream_status = शून्य;
	काष्ठा dc_plane_state *del_planes[MAX_SURFACE_NUM] = अणु 0 पूर्ण;

	क्रम (i = 0; i < context->stream_count; i++)
			अगर (context->streams[i] == stream) अणु
				stream_status = &context->stream_status[i];
				अवरोध;
			पूर्ण

	अगर (stream_status == शून्य) अणु
		dm_error("Existing stream %p not found!\n", stream);
		वापस false;
	पूर्ण

	old_plane_count = stream_status->plane_count;

	क्रम (i = 0; i < old_plane_count; i++)
		del_planes[i] = stream_status->plane_states[i];

	क्रम (i = 0; i < old_plane_count; i++)
		अगर (!dc_हटाओ_plane_from_context(dc, stream, del_planes[i], context))
			वापस false;

	वापस true;
पूर्ण

अटल bool add_all_planes_क्रम_stream(
		स्थिर काष्ठा dc *dc,
		काष्ठा dc_stream_state *stream,
		स्थिर काष्ठा dc_validation_set set[],
		पूर्णांक set_count,
		काष्ठा dc_state *context)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < set_count; i++)
		अगर (set[i].stream == stream)
			अवरोध;

	अगर (i == set_count) अणु
		dm_error("Stream %p not found in set!\n", stream);
		वापस false;
	पूर्ण

	क्रम (j = 0; j < set[i].plane_count; j++)
		अगर (!dc_add_plane_to_context(dc, stream, set[i].plane_states[j], context))
			वापस false;

	वापस true;
पूर्ण

bool dc_add_all_planes_क्रम_stream(
		स्थिर काष्ठा dc *dc,
		काष्ठा dc_stream_state *stream,
		काष्ठा dc_plane_state * स्थिर *plane_states,
		पूर्णांक plane_count,
		काष्ठा dc_state *context)
अणु
	काष्ठा dc_validation_set set;
	पूर्णांक i;

	set.stream = stream;
	set.plane_count = plane_count;

	क्रम (i = 0; i < plane_count; i++)
		set.plane_states[i] = plane_states[i];

	वापस add_all_planes_क्रम_stream(dc, stream, &set, 1, context);
पूर्ण

अटल bool is_timing_changed(काष्ठा dc_stream_state *cur_stream,
		काष्ठा dc_stream_state *new_stream)
अणु
	अगर (cur_stream == शून्य)
		वापस true;

	/* If sink poपूर्णांकer changed, it means this is a hotplug, we should करो
	 * full hw setting.
	 */
	अगर (cur_stream->sink != new_stream->sink)
		वापस true;

	/* If output color space is changed, need to reprogram info frames */
	अगर (cur_stream->output_color_space != new_stream->output_color_space)
		वापस true;

	वापस स_भेद(
		&cur_stream->timing,
		&new_stream->timing,
		माप(काष्ठा dc_crtc_timing)) != 0;
पूर्ण

अटल bool are_stream_backends_same(
	काष्ठा dc_stream_state *stream_a, काष्ठा dc_stream_state *stream_b)
अणु
	अगर (stream_a == stream_b)
		वापस true;

	अगर (stream_a == शून्य || stream_b == शून्य)
		वापस false;

	अगर (is_timing_changed(stream_a, stream_b))
		वापस false;

	अगर (stream_a->dpms_off != stream_b->dpms_off)
		वापस false;

	वापस true;
पूर्ण

/*
 * dc_is_stream_unchanged() - Compare two stream states क्रम equivalence.
 *
 * Checks अगर there a dअगरference between the two states
 * that would require a mode change.
 *
 * Does not compare cursor position or attributes.
 */
bool dc_is_stream_unchanged(
	काष्ठा dc_stream_state *old_stream, काष्ठा dc_stream_state *stream)
अणु

	अगर (!are_stream_backends_same(old_stream, stream))
		वापस false;

	अगर (old_stream->ignore_msa_timing_param != stream->ignore_msa_timing_param)
		वापस false;

	वापस true;
पूर्ण

/*
 * dc_is_stream_scaling_unchanged() - Compare scaling rectangles of two streams.
 */
bool dc_is_stream_scaling_unchanged(
	काष्ठा dc_stream_state *old_stream, काष्ठा dc_stream_state *stream)
अणु
	अगर (old_stream == stream)
		वापस true;

	अगर (old_stream == शून्य || stream == शून्य)
		वापस false;

	अगर (स_भेद(&old_stream->src,
			&stream->src,
			माप(काष्ठा rect)) != 0)
		वापस false;

	अगर (स_भेद(&old_stream->dst,
			&stream->dst,
			माप(काष्ठा rect)) != 0)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम update_stream_engine_usage(
		काष्ठा resource_context *res_ctx,
		स्थिर काष्ठा resource_pool *pool,
		काष्ठा stream_encoder *stream_enc,
		bool acquired)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pool->stream_enc_count; i++) अणु
		अगर (pool->stream_enc[i] == stream_enc)
			res_ctx->is_stream_enc_acquired[i] = acquired;
	पूर्ण
पूर्ण

/* TODO: release audio object */
व्योम update_audio_usage(
		काष्ठा resource_context *res_ctx,
		स्थिर काष्ठा resource_pool *pool,
		काष्ठा audio *audio,
		bool acquired)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < pool->audio_count; i++) अणु
		अगर (pool->audios[i] == audio)
			res_ctx->is_audio_acquired[i] = acquired;
	पूर्ण
पूर्ण

अटल पूर्णांक acquire_first_मुक्त_pipe(
		काष्ठा resource_context *res_ctx,
		स्थिर काष्ठा resource_pool *pool,
		काष्ठा dc_stream_state *stream)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pool->pipe_count; i++) अणु
		अगर (!res_ctx->pipe_ctx[i].stream) अणु
			काष्ठा pipe_ctx *pipe_ctx = &res_ctx->pipe_ctx[i];

			pipe_ctx->stream_res.tg = pool->timing_generators[i];
			pipe_ctx->plane_res.mi = pool->mis[i];
			pipe_ctx->plane_res.hubp = pool->hubps[i];
			pipe_ctx->plane_res.ipp = pool->ipps[i];
			pipe_ctx->plane_res.xfm = pool->transक्रमms[i];
			pipe_ctx->plane_res.dpp = pool->dpps[i];
			pipe_ctx->stream_res.opp = pool->opps[i];
			अगर (pool->dpps[i])
				pipe_ctx->plane_res.mpcc_inst = pool->dpps[i]->inst;
			pipe_ctx->pipe_idx = i;


			pipe_ctx->stream = stream;
			वापस i;
		पूर्ण
	पूर्ण
	वापस -1;
पूर्ण

अटल काष्ठा audio *find_first_मुक्त_audio(
		काष्ठा resource_context *res_ctx,
		स्थिर काष्ठा resource_pool *pool,
		क्रमागत engine_id id,
		क्रमागत dce_version dc_version)
अणु
	पूर्णांक i, available_audio_count;

	available_audio_count = pool->audio_count;

	क्रम (i = 0; i < available_audio_count; i++) अणु
		अगर ((res_ctx->is_audio_acquired[i] == false) && (res_ctx->is_stream_enc_acquired[i] == true)) अणु
			/*we have enough audio endpoपूर्णांक, find the matching inst*/
			अगर (id != i)
				जारी;
			वापस pool->audios[i];
		पूर्ण
	पूर्ण

	/* use engine id to find मुक्त audio */
	अगर ((id < available_audio_count) && (res_ctx->is_audio_acquired[id] == false)) अणु
		वापस pool->audios[id];
	पूर्ण
	/*not found the matching one, first come first serve*/
	क्रम (i = 0; i < available_audio_count; i++) अणु
		अगर (res_ctx->is_audio_acquired[i] == false) अणु
			वापस pool->audios[i];
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * dc_add_stream_to_ctx() - Add a new dc_stream_state to a dc_state.
 */
क्रमागत dc_status dc_add_stream_to_ctx(
		काष्ठा dc *dc,
		काष्ठा dc_state *new_ctx,
		काष्ठा dc_stream_state *stream)
अणु
	क्रमागत dc_status res;
	DC_LOGGER_INIT(dc->ctx->logger);

	अगर (new_ctx->stream_count >= dc->res_pool->timing_generator_count) अणु
		DC_LOG_WARNING("Max streams reached, can't add stream %p !\n", stream);
		वापस DC_ERROR_UNEXPECTED;
	पूर्ण

	new_ctx->streams[new_ctx->stream_count] = stream;
	dc_stream_retain(stream);
	new_ctx->stream_count++;

	res = dc->res_pool->funcs->add_stream_to_ctx(dc, new_ctx, stream);
	अगर (res != DC_OK)
		DC_LOG_WARNING("Adding stream %p to context failed with err %d!\n", stream, res);

	वापस res;
पूर्ण

/*
 * dc_हटाओ_stream_from_ctx() - Remove a stream from a dc_state.
 */
क्रमागत dc_status dc_हटाओ_stream_from_ctx(
			काष्ठा dc *dc,
			काष्ठा dc_state *new_ctx,
			काष्ठा dc_stream_state *stream)
अणु
	पूर्णांक i;
	काष्ठा dc_context *dc_ctx = dc->ctx;
	काष्ठा pipe_ctx *del_pipe = resource_get_head_pipe_क्रम_stream(&new_ctx->res_ctx, stream);
	काष्ठा pipe_ctx *odm_pipe;

	अगर (!del_pipe) अणु
		DC_ERROR("Pipe not found for stream %p !\n", stream);
		वापस DC_ERROR_UNEXPECTED;
	पूर्ण

	odm_pipe = del_pipe->next_odm_pipe;

	/* Release primary pipe */
	ASSERT(del_pipe->stream_res.stream_enc);
	update_stream_engine_usage(
			&new_ctx->res_ctx,
				dc->res_pool,
			del_pipe->stream_res.stream_enc,
			false);
	/* Release link encoder from stream in new dc_state. */
	अगर (dc->res_pool->funcs->link_enc_unassign)
		dc->res_pool->funcs->link_enc_unassign(new_ctx, del_pipe->stream);

	अगर (del_pipe->stream_res.audio)
		update_audio_usage(
			&new_ctx->res_ctx,
			dc->res_pool,
			del_pipe->stream_res.audio,
			false);

	resource_unreference_घड़ी_source(&new_ctx->res_ctx,
					  dc->res_pool,
					  del_pipe->घड़ी_source);

	अगर (dc->res_pool->funcs->हटाओ_stream_from_ctx)
		dc->res_pool->funcs->हटाओ_stream_from_ctx(dc, new_ctx, stream);

	जबतक (odm_pipe) अणु
		काष्ठा pipe_ctx *next_odm_pipe = odm_pipe->next_odm_pipe;

		स_रखो(odm_pipe, 0, माप(*odm_pipe));
		odm_pipe = next_odm_pipe;
	पूर्ण
	स_रखो(del_pipe, 0, माप(*del_pipe));

	क्रम (i = 0; i < new_ctx->stream_count; i++)
		अगर (new_ctx->streams[i] == stream)
			अवरोध;

	अगर (new_ctx->streams[i] != stream) अणु
		DC_ERROR("Context doesn't have stream %p !\n", stream);
		वापस DC_ERROR_UNEXPECTED;
	पूर्ण

	dc_stream_release(new_ctx->streams[i]);
	new_ctx->stream_count--;

	/* Trim back arrays */
	क्रम (; i < new_ctx->stream_count; i++) अणु
		new_ctx->streams[i] = new_ctx->streams[i + 1];
		new_ctx->stream_status[i] = new_ctx->stream_status[i + 1];
	पूर्ण

	new_ctx->streams[new_ctx->stream_count] = शून्य;
	स_रखो(
			&new_ctx->stream_status[new_ctx->stream_count],
			0,
			माप(new_ctx->stream_status[0]));

	वापस DC_OK;
पूर्ण

अटल काष्ठा dc_stream_state *find_pll_sharable_stream(
		काष्ठा dc_stream_state *stream_needs_pll,
		काष्ठा dc_state *context)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < context->stream_count; i++) अणु
		काष्ठा dc_stream_state *stream_has_pll = context->streams[i];

		/* We are looking क्रम non dp, non भव stream */
		अगर (resource_are_streams_timing_synchronizable(
			stream_needs_pll, stream_has_pll)
			&& !dc_is_dp_संकेत(stream_has_pll->संकेत)
			&& stream_has_pll->link->connector_संकेत
			!= SIGNAL_TYPE_VIRTUAL)
			वापस stream_has_pll;

	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक get_norm_pix_clk(स्थिर काष्ठा dc_crtc_timing *timing)
अणु
	uपूर्णांक32_t pix_clk = timing->pix_clk_100hz;
	uपूर्णांक32_t normalized_pix_clk = pix_clk;

	अगर (timing->pixel_encoding == PIXEL_ENCODING_YCBCR420)
		pix_clk /= 2;
	अगर (timing->pixel_encoding != PIXEL_ENCODING_YCBCR422) अणु
		चयन (timing->display_color_depth) अणु
		हाल COLOR_DEPTH_666:
		हाल COLOR_DEPTH_888:
			normalized_pix_clk = pix_clk;
			अवरोध;
		हाल COLOR_DEPTH_101010:
			normalized_pix_clk = (pix_clk * 30) / 24;
			अवरोध;
		हाल COLOR_DEPTH_121212:
			normalized_pix_clk = (pix_clk * 36) / 24;
		अवरोध;
		हाल COLOR_DEPTH_161616:
			normalized_pix_clk = (pix_clk * 48) / 24;
		अवरोध;
		शेष:
			ASSERT(0);
		अवरोध;
		पूर्ण
	पूर्ण
	वापस normalized_pix_clk;
पूर्ण

अटल व्योम calculate_phy_pix_clks(काष्ठा dc_stream_state *stream)
अणु
	/* update actual pixel घड़ी on all streams */
	अगर (dc_is_hdmi_संकेत(stream->संकेत))
		stream->phy_pix_clk = get_norm_pix_clk(
			&stream->timing) / 10;
	अन्यथा
		stream->phy_pix_clk =
			stream->timing.pix_clk_100hz / 10;

	अगर (stream->timing.timing_3d_क्रमmat == TIMING_3D_FORMAT_HW_FRAME_PACKING)
		stream->phy_pix_clk *= 2;
पूर्ण

अटल पूर्णांक acquire_resource_from_hw_enabled_state(
		काष्ठा resource_context *res_ctx,
		स्थिर काष्ठा resource_pool *pool,
		काष्ठा dc_stream_state *stream)
अणु
	काष्ठा dc_link *link = stream->link;
	अचिन्हित पूर्णांक i, inst, tg_inst = 0;

	/* Check क्रम enabled DIG to identअगरy enabled display */
	अगर (!link->link_enc->funcs->is_dig_enabled(link->link_enc))
		वापस -1;

	inst = link->link_enc->funcs->get_dig_frontend(link->link_enc);

	अगर (inst == ENGINE_ID_UNKNOWN)
		वापस -1;

	क्रम (i = 0; i < pool->stream_enc_count; i++) अणु
		अगर (pool->stream_enc[i]->id == inst) अणु
			tg_inst = pool->stream_enc[i]->funcs->dig_source_otg(
				pool->stream_enc[i]);
			अवरोध;
		पूर्ण
	पूर्ण

	// tg_inst not found
	अगर (i == pool->stream_enc_count)
		वापस -1;

	अगर (tg_inst >= pool->timing_generator_count)
		वापस -1;

	अगर (!res_ctx->pipe_ctx[tg_inst].stream) अणु
		काष्ठा pipe_ctx *pipe_ctx = &res_ctx->pipe_ctx[tg_inst];

		pipe_ctx->stream_res.tg = pool->timing_generators[tg_inst];
		pipe_ctx->plane_res.mi = pool->mis[tg_inst];
		pipe_ctx->plane_res.hubp = pool->hubps[tg_inst];
		pipe_ctx->plane_res.ipp = pool->ipps[tg_inst];
		pipe_ctx->plane_res.xfm = pool->transक्रमms[tg_inst];
		pipe_ctx->plane_res.dpp = pool->dpps[tg_inst];
		pipe_ctx->stream_res.opp = pool->opps[tg_inst];

		अगर (pool->dpps[tg_inst]) अणु
			pipe_ctx->plane_res.mpcc_inst = pool->dpps[tg_inst]->inst;

			// Read DPP->MPCC->OPP Pipe from HW State
			अगर (pool->mpc->funcs->पढ़ो_mpcc_state) अणु
				काष्ठा mpcc_state s = अणु0पूर्ण;

				pool->mpc->funcs->पढ़ो_mpcc_state(pool->mpc, pipe_ctx->plane_res.mpcc_inst, &s);

				अगर (s.dpp_id < MAX_MPCC)
					pool->mpc->mpcc_array[pipe_ctx->plane_res.mpcc_inst].dpp_id = s.dpp_id;

				अगर (s.bot_mpcc_id < MAX_MPCC)
					pool->mpc->mpcc_array[pipe_ctx->plane_res.mpcc_inst].mpcc_bot =
							&pool->mpc->mpcc_array[s.bot_mpcc_id];

				अगर (s.opp_id < MAX_OPP)
					pipe_ctx->stream_res.opp->mpc_tree_params.opp_id = s.opp_id;
			पूर्ण
		पूर्ण
		pipe_ctx->pipe_idx = tg_inst;

		pipe_ctx->stream = stream;
		वापस tg_inst;
	पूर्ण

	वापस -1;
पूर्ण

अटल व्योम mark_seamless_boot_stream(
		स्थिर काष्ठा dc  *dc,
		काष्ठा dc_stream_state *stream)
अणु
	काष्ठा dc_bios *dcb = dc->ctx->dc_bios;

	/* TODO: Check Linux */
	अगर (dc->config.allow_seamless_boot_optimization &&
			!dcb->funcs->is_accelerated_mode(dcb)) अणु
		अगर (dc_validate_seamless_boot_timing(dc, stream->sink, &stream->timing))
			stream->apply_seamless_boot_optimization = true;
	पूर्ण
पूर्ण

क्रमागत dc_status resource_map_pool_resources(
		स्थिर काष्ठा dc  *dc,
		काष्ठा dc_state *context,
		काष्ठा dc_stream_state *stream)
अणु
	स्थिर काष्ठा resource_pool *pool = dc->res_pool;
	पूर्णांक i;
	काष्ठा dc_context *dc_ctx = dc->ctx;
	काष्ठा pipe_ctx *pipe_ctx = शून्य;
	पूर्णांक pipe_idx = -1;

	calculate_phy_pix_clks(stream);

	mark_seamless_boot_stream(dc, stream);

	अगर (stream->apply_seamless_boot_optimization) अणु
		pipe_idx = acquire_resource_from_hw_enabled_state(
				&context->res_ctx,
				pool,
				stream);
		अगर (pipe_idx < 0)
			/* hw resource was asचिन्हित to other stream */
			stream->apply_seamless_boot_optimization = false;
	पूर्ण

	अगर (pipe_idx < 0)
		/* acquire new resources */
		pipe_idx = acquire_first_मुक्त_pipe(&context->res_ctx, pool, stream);

#अगर_घोषित CONFIG_DRM_AMD_DC_DCN
	अगर (pipe_idx < 0)
		pipe_idx = acquire_first_split_pipe(&context->res_ctx, pool, stream);
#पूर्ण_अगर

	अगर (pipe_idx < 0 || context->res_ctx.pipe_ctx[pipe_idx].stream_res.tg == शून्य)
		वापस DC_NO_CONTROLLER_RESOURCE;

	pipe_ctx = &context->res_ctx.pipe_ctx[pipe_idx];

	pipe_ctx->stream_res.stream_enc =
		dc->res_pool->funcs->find_first_मुक्त_match_stream_enc_क्रम_link(
			&context->res_ctx, pool, stream);

	अगर (!pipe_ctx->stream_res.stream_enc)
		वापस DC_NO_STREAM_ENC_RESOURCE;

	update_stream_engine_usage(
		&context->res_ctx, pool,
		pipe_ctx->stream_res.stream_enc,
		true);

	/* TODO: Add check अगर ASIC support and EDID audio */
	अगर (!stream->converter_disable_audio &&
	    dc_is_audio_capable_संकेत(pipe_ctx->stream->संकेत) &&
	    stream->audio_info.mode_count && stream->audio_info.flags.all) अणु
		pipe_ctx->stream_res.audio = find_first_मुक्त_audio(
		&context->res_ctx, pool, pipe_ctx->stream_res.stream_enc->id, dc_ctx->dce_version);

		/*
		 * Audio asचिन्हित in order first come first get.
		 * There are asics which has number of audio
		 * resources less then number of pipes
		 */
		अगर (pipe_ctx->stream_res.audio)
			update_audio_usage(&context->res_ctx, pool,
					   pipe_ctx->stream_res.audio, true);
	पूर्ण

	/* Add ABM to the resource अगर on EDP */
	अगर (pipe_ctx->stream && dc_is_embedded_संकेत(pipe_ctx->stream->संकेत)) अणु
#अगर defined(CONFIG_DRM_AMD_DC_DCN)
		अगर (pool->abm)
			pipe_ctx->stream_res.abm = pool->abm;
		अन्यथा
			pipe_ctx->stream_res.abm = pool->multiple_abms[pipe_ctx->stream_res.tg->inst];
#अन्यथा
		pipe_ctx->stream_res.abm = pool->abm;
#पूर्ण_अगर
	पूर्ण

	क्रम (i = 0; i < context->stream_count; i++)
		अगर (context->streams[i] == stream) अणु
			context->stream_status[i].primary_otg_inst = pipe_ctx->stream_res.tg->inst;
			context->stream_status[i].stream_enc_inst = pipe_ctx->stream_res.stream_enc->stream_enc_inst;
			context->stream_status[i].audio_inst =
				pipe_ctx->stream_res.audio ? pipe_ctx->stream_res.audio->inst : -1;

			वापस DC_OK;
		पूर्ण

	DC_ERROR("Stream %p not found in new ctx!\n", stream);
	वापस DC_ERROR_UNEXPECTED;
पूर्ण

/**
 * dc_resource_state_copy_स्थिरruct_current() - Creates a new dc_state from existing state
 * Is a shallow copy.  Increments refcounts on existing streams and planes.
 * @dc: copy out of dc->current_state
 * @dst_ctx: copy पूर्णांकo this
 */
व्योम dc_resource_state_copy_स्थिरruct_current(
		स्थिर काष्ठा dc *dc,
		काष्ठा dc_state *dst_ctx)
अणु
	dc_resource_state_copy_स्थिरruct(dc->current_state, dst_ctx);
पूर्ण


व्योम dc_resource_state_स्थिरruct(
		स्थिर काष्ठा dc *dc,
		काष्ठा dc_state *dst_ctx)
अणु
	dst_ctx->clk_mgr = dc->clk_mgr;
पूर्ण


bool dc_resource_is_dsc_encoding_supported(स्थिर काष्ठा dc *dc)
अणु
	वापस dc->res_pool->res_cap->num_dsc > 0;
पूर्ण


/**
 * dc_validate_global_state() - Determine अगर HW can support a given state
 * Checks HW resource availability and bandwidth requirement.
 * @dc: dc काष्ठा क्रम this driver
 * @new_ctx: state to be validated
 * @fast_validate: set to true अगर only yes/no to support matters
 *
 * Return: DC_OK अगर the result can be programmed.  Otherwise, an error code.
 */
क्रमागत dc_status dc_validate_global_state(
		काष्ठा dc *dc,
		काष्ठा dc_state *new_ctx,
		bool fast_validate)
अणु
	क्रमागत dc_status result = DC_ERROR_UNEXPECTED;
	पूर्णांक i, j;

	अगर (!new_ctx)
		वापस DC_ERROR_UNEXPECTED;

	अगर (dc->res_pool->funcs->validate_global) अणु
		result = dc->res_pool->funcs->validate_global(dc, new_ctx);
		अगर (result != DC_OK)
			वापस result;
	पूर्ण

	क्रम (i = 0; i < new_ctx->stream_count; i++) अणु
		काष्ठा dc_stream_state *stream = new_ctx->streams[i];

		क्रम (j = 0; j < dc->res_pool->pipe_count; j++) अणु
			काष्ठा pipe_ctx *pipe_ctx = &new_ctx->res_ctx.pipe_ctx[j];

			अगर (pipe_ctx->stream != stream)
				जारी;

			अगर (dc->res_pool->funcs->patch_unknown_plane_state &&
					pipe_ctx->plane_state &&
					pipe_ctx->plane_state->tiling_info.gfx9.swizzle == DC_SW_UNKNOWN) अणु
				result = dc->res_pool->funcs->patch_unknown_plane_state(pipe_ctx->plane_state);
				अगर (result != DC_OK)
					वापस result;
			पूर्ण

			/* Switch to dp घड़ी source only अगर there is
			 * no non dp stream that shares the same timing
			 * with the dp stream.
			 */
			अगर (dc_is_dp_संकेत(pipe_ctx->stream->संकेत) &&
				!find_pll_sharable_stream(stream, new_ctx)) अणु

				resource_unreference_घड़ी_source(
						&new_ctx->res_ctx,
						dc->res_pool,
						pipe_ctx->घड़ी_source);

				pipe_ctx->घड़ी_source = dc->res_pool->dp_घड़ी_source;
				resource_reference_घड़ी_source(
						&new_ctx->res_ctx,
						dc->res_pool,
						 pipe_ctx->घड़ी_source);
			पूर्ण
		पूर्ण
	पूर्ण

	result = resource_build_scaling_params_क्रम_context(dc, new_ctx);

	अगर (result == DC_OK)
		अगर (!dc->res_pool->funcs->validate_bandwidth(dc, new_ctx, fast_validate))
			result = DC_FAIL_BANDWIDTH_VALIDATE;

	वापस result;
पूर्ण

अटल व्योम patch_gamut_packet_checksum(
		काष्ठा dc_info_packet *gamut_packet)
अणु
	/* For gamut we recalc checksum */
	अगर (gamut_packet->valid) अणु
		uपूर्णांक8_t chk_sum = 0;
		uपूर्णांक8_t *ptr;
		uपूर्णांक8_t i;

		/*start of the Gamut data. */
		ptr = &gamut_packet->sb[3];

		क्रम (i = 0; i <= gamut_packet->sb[1]; i++)
			chk_sum += ptr[i];

		gamut_packet->sb[2] = (uपूर्णांक8_t) (0x100 - chk_sum);
	पूर्ण
पूर्ण

अटल व्योम set_avi_info_frame(
		काष्ठा dc_info_packet *info_packet,
		काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा dc_stream_state *stream = pipe_ctx->stream;
	क्रमागत dc_color_space color_space = COLOR_SPACE_UNKNOWN;
	uपूर्णांक32_t pixel_encoding = 0;
	क्रमागत scanning_type scan_type = SCANNING_TYPE_NODATA;
	क्रमागत dc_aspect_ratio aspect = ASPECT_RATIO_NO_DATA;
	bool itc = false;
	uपूर्णांक8_t itc_value = 0;
	uपूर्णांक8_t cn0_cn1 = 0;
	अचिन्हित पूर्णांक cn0_cn1_value = 0;
	uपूर्णांक8_t *check_sum = शून्य;
	uपूर्णांक8_t byte_index = 0;
	जोड़ hdmi_info_packet hdmi_info;
	जोड़ display_content_support support = अणु0पूर्ण;
	अचिन्हित पूर्णांक vic = pipe_ctx->stream->timing.vic;
	क्रमागत dc_timing_3d_क्रमmat क्रमmat;

	स_रखो(&hdmi_info, 0, माप(जोड़ hdmi_info_packet));

	color_space = pipe_ctx->stream->output_color_space;
	अगर (color_space == COLOR_SPACE_UNKNOWN)
		color_space = (stream->timing.pixel_encoding == PIXEL_ENCODING_RGB) ?
			COLOR_SPACE_SRGB:COLOR_SPACE_YCBCR709;

	/* Initialize header */
	hdmi_info.bits.header.info_frame_type = HDMI_INFOFRAME_TYPE_AVI;
	/* InfoFrameVersion_3 is defined by CEA861F (Section 6.4), but shall
	* not be used in HDMI 2.0 (Section 10.1) */
	hdmi_info.bits.header.version = 2;
	hdmi_info.bits.header.length = HDMI_AVI_INFOFRAME_SIZE;

	/*
	 * IDO-defined (Y2,Y1,Y0 = 1,1,1) shall not be used by devices built
	 * according to HDMI 2.0 spec (Section 10.1)
	 */

	चयन (stream->timing.pixel_encoding) अणु
	हाल PIXEL_ENCODING_YCBCR422:
		pixel_encoding = 1;
		अवरोध;

	हाल PIXEL_ENCODING_YCBCR444:
		pixel_encoding = 2;
		अवरोध;
	हाल PIXEL_ENCODING_YCBCR420:
		pixel_encoding = 3;
		अवरोध;

	हाल PIXEL_ENCODING_RGB:
	शेष:
		pixel_encoding = 0;
	पूर्ण

	/* Y0_Y1_Y2 : The pixel encoding */
	/* H14b AVI InfoFrame has extension on Y-field from 2 bits to 3 bits */
	hdmi_info.bits.Y0_Y1_Y2 = pixel_encoding;

	/* A0 = 1 Active Format Inक्रमmation valid */
	hdmi_info.bits.A0 = ACTIVE_FORMAT_VALID;

	/* B0, B1 = 3; Bar info data is valid */
	hdmi_info.bits.B0_B1 = BAR_INFO_BOTH_VALID;

	hdmi_info.bits.SC0_SC1 = PICTURE_SCALING_UNIFORM;

	/* S0, S1 : Underscan / Overscan */
	/* TODO: un-hardcode scan type */
	scan_type = SCANNING_TYPE_UNDERSCAN;
	hdmi_info.bits.S0_S1 = scan_type;

	/* C0, C1 : Colorimetry */
	अगर (color_space == COLOR_SPACE_YCBCR709 ||
			color_space == COLOR_SPACE_YCBCR709_LIMITED)
		hdmi_info.bits.C0_C1 = COLORIMETRY_ITU709;
	अन्यथा अगर (color_space == COLOR_SPACE_YCBCR601 ||
			color_space == COLOR_SPACE_YCBCR601_LIMITED)
		hdmi_info.bits.C0_C1 = COLORIMETRY_ITU601;
	अन्यथा अणु
		hdmi_info.bits.C0_C1 = COLORIMETRY_NO_DATA;
	पूर्ण
	अगर (color_space == COLOR_SPACE_2020_RGB_FULLRANGE ||
			color_space == COLOR_SPACE_2020_RGB_LIMITEDRANGE ||
			color_space == COLOR_SPACE_2020_YCBCR) अणु
		hdmi_info.bits.EC0_EC2 = COLORIMETRYEX_BT2020RGBYCBCR;
		hdmi_info.bits.C0_C1   = COLORIMETRY_EXTENDED;
	पूर्ण अन्यथा अगर (color_space == COLOR_SPACE_ADOBERGB) अणु
		hdmi_info.bits.EC0_EC2 = COLORIMETRYEX_ADOBERGB;
		hdmi_info.bits.C0_C1   = COLORIMETRY_EXTENDED;
	पूर्ण

	/* TODO: un-hardcode aspect ratio */
	aspect = stream->timing.aspect_ratio;

	चयन (aspect) अणु
	हाल ASPECT_RATIO_4_3:
	हाल ASPECT_RATIO_16_9:
		hdmi_info.bits.M0_M1 = aspect;
		अवरोध;

	हाल ASPECT_RATIO_NO_DATA:
	हाल ASPECT_RATIO_64_27:
	हाल ASPECT_RATIO_256_135:
	शेष:
		hdmi_info.bits.M0_M1 = 0;
	पूर्ण

	/* Active Format Aspect ratio - same as Picture Aspect Ratio. */
	hdmi_info.bits.R0_R3 = ACTIVE_FORMAT_ASPECT_RATIO_SAME_AS_PICTURE;

	/* TODO: un-hardcode cn0_cn1 and itc */

	cn0_cn1 = 0;
	cn0_cn1_value = 0;

	itc = true;
	itc_value = 1;

	support = stream->content_support;

	अगर (itc) अणु
		अगर (!support.bits.valid_content_type) अणु
			cn0_cn1_value = 0;
		पूर्ण अन्यथा अणु
			अगर (cn0_cn1 == DISPLAY_CONTENT_TYPE_GRAPHICS) अणु
				अगर (support.bits.graphics_content == 1) अणु
					cn0_cn1_value = 0;
				पूर्ण
			पूर्ण अन्यथा अगर (cn0_cn1 == DISPLAY_CONTENT_TYPE_PHOTO) अणु
				अगर (support.bits.photo_content == 1) अणु
					cn0_cn1_value = 1;
				पूर्ण अन्यथा अणु
					cn0_cn1_value = 0;
					itc_value = 0;
				पूर्ण
			पूर्ण अन्यथा अगर (cn0_cn1 == DISPLAY_CONTENT_TYPE_CINEMA) अणु
				अगर (support.bits.cinema_content == 1) अणु
					cn0_cn1_value = 2;
				पूर्ण अन्यथा अणु
					cn0_cn1_value = 0;
					itc_value = 0;
				पूर्ण
			पूर्ण अन्यथा अगर (cn0_cn1 == DISPLAY_CONTENT_TYPE_GAME) अणु
				अगर (support.bits.game_content == 1) अणु
					cn0_cn1_value = 3;
				पूर्ण अन्यथा अणु
					cn0_cn1_value = 0;
					itc_value = 0;
				पूर्ण
			पूर्ण
		पूर्ण
		hdmi_info.bits.CN0_CN1 = cn0_cn1_value;
		hdmi_info.bits.ITC = itc_value;
	पूर्ण

	अगर (stream->qs_bit == 1) अणु
		अगर (color_space == COLOR_SPACE_SRGB ||
			color_space == COLOR_SPACE_2020_RGB_FULLRANGE)
			hdmi_info.bits.Q0_Q1   = RGB_QUANTIZATION_FULL_RANGE;
		अन्यथा अगर (color_space == COLOR_SPACE_SRGB_LIMITED ||
					color_space == COLOR_SPACE_2020_RGB_LIMITEDRANGE)
			hdmi_info.bits.Q0_Q1   = RGB_QUANTIZATION_LIMITED_RANGE;
		अन्यथा
			hdmi_info.bits.Q0_Q1   = RGB_QUANTIZATION_DEFAULT_RANGE;
	पूर्ण अन्यथा
		hdmi_info.bits.Q0_Q1   = RGB_QUANTIZATION_DEFAULT_RANGE;

	/* TODO : We should handle YCC quantization */
	/* but we करो not have matrix calculation */
	अगर (stream->qy_bit == 1) अणु
		अगर (color_space == COLOR_SPACE_SRGB ||
			color_space == COLOR_SPACE_2020_RGB_FULLRANGE)
			hdmi_info.bits.YQ0_YQ1 = YYC_QUANTIZATION_LIMITED_RANGE;
		अन्यथा अगर (color_space == COLOR_SPACE_SRGB_LIMITED ||
					color_space == COLOR_SPACE_2020_RGB_LIMITEDRANGE)
			hdmi_info.bits.YQ0_YQ1 = YYC_QUANTIZATION_LIMITED_RANGE;
		अन्यथा
			hdmi_info.bits.YQ0_YQ1 = YYC_QUANTIZATION_LIMITED_RANGE;
	पूर्ण अन्यथा
		hdmi_info.bits.YQ0_YQ1 = YYC_QUANTIZATION_LIMITED_RANGE;

	///VIC
	क्रमmat = stream->timing.timing_3d_क्रमmat;
	/*toकरो, add 3DStereo support*/
	अगर (क्रमmat != TIMING_3D_FORMAT_NONE) अणु
		// Based on HDMI specs hdmi vic needs to be converted to cea vic when 3D is enabled
		चयन (pipe_ctx->stream->timing.hdmi_vic) अणु
		हाल 1:
			vic = 95;
			अवरोध;
		हाल 2:
			vic = 94;
			अवरोध;
		हाल 3:
			vic = 93;
			अवरोध;
		हाल 4:
			vic = 98;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	/* If VIC >= 128, the Source shall use AVI InfoFrame Version 3*/
	hdmi_info.bits.VIC0_VIC7 = vic;
	अगर (vic >= 128)
		hdmi_info.bits.header.version = 3;
	/* If (C1, C0)=(1, 1) and (EC2, EC1, EC0)=(1, 1, 1),
	 * the Source shall use 20 AVI InfoFrame Version 4
	 */
	अगर (hdmi_info.bits.C0_C1 == COLORIMETRY_EXTENDED &&
			hdmi_info.bits.EC0_EC2 == COLORIMETRYEX_RESERVED) अणु
		hdmi_info.bits.header.version = 4;
		hdmi_info.bits.header.length = 14;
	पूर्ण

	/* pixel repetition
	 * PR0 - PR3 start from 0 whereas pHwPathMode->mode.timing.flags.pixel
	 * repetition start from 1 */
	hdmi_info.bits.PR0_PR3 = 0;

	/* Bar Info
	 * barTop:    Line Number of End of Top Bar.
	 * barBottom: Line Number of Start of Bottom Bar.
	 * barLeft:   Pixel Number of End of Left Bar.
	 * barRight:  Pixel Number of Start of Right Bar. */
	hdmi_info.bits.bar_top = stream->timing.v_border_top;
	hdmi_info.bits.bar_bottom = (stream->timing.v_total
			- stream->timing.v_border_bottom + 1);
	hdmi_info.bits.bar_left  = stream->timing.h_border_left;
	hdmi_info.bits.bar_right = (stream->timing.h_total
			- stream->timing.h_border_right + 1);

    /* Additional Colorimetry Extension
     * Used in conduction with C0-C1 and EC0-EC2
     * 0 = DCI-P3 RGB (D65)
     * 1 = DCI-P3 RGB (theater)
     */
	hdmi_info.bits.ACE0_ACE3 = 0;

	/* check_sum - Calculate AFMT_AVI_INFO0 ~ AFMT_AVI_INFO3 */
	check_sum = &hdmi_info.packet_raw_data.sb[0];

	*check_sum = HDMI_INFOFRAME_TYPE_AVI + hdmi_info.bits.header.length + hdmi_info.bits.header.version;

	क्रम (byte_index = 1; byte_index <= hdmi_info.bits.header.length; byte_index++)
		*check_sum += hdmi_info.packet_raw_data.sb[byte_index];

	/* one byte complement */
	*check_sum = (uपूर्णांक8_t) (0x100 - *check_sum);

	/* Store in hw_path_mode */
	info_packet->hb0 = hdmi_info.packet_raw_data.hb0;
	info_packet->hb1 = hdmi_info.packet_raw_data.hb1;
	info_packet->hb2 = hdmi_info.packet_raw_data.hb2;

	क्रम (byte_index = 0; byte_index < माप(hdmi_info.packet_raw_data.sb); byte_index++)
		info_packet->sb[byte_index] = hdmi_info.packet_raw_data.sb[byte_index];

	info_packet->valid = true;
पूर्ण

अटल व्योम set_venकरोr_info_packet(
		काष्ठा dc_info_packet *info_packet,
		काष्ठा dc_stream_state *stream)
अणु
	/* SPD info packet क्रम FreeSync */

	/* Check अगर Freesync is supported. Return अगर false. If true,
	 * set the corresponding bit in the info packet
	 */
	अगर (!stream->vsp_infopacket.valid)
		वापस;

	*info_packet = stream->vsp_infopacket;
पूर्ण

अटल व्योम set_spd_info_packet(
		काष्ठा dc_info_packet *info_packet,
		काष्ठा dc_stream_state *stream)
अणु
	/* SPD info packet क्रम FreeSync */

	/* Check अगर Freesync is supported. Return अगर false. If true,
	 * set the corresponding bit in the info packet
	 */
	अगर (!stream->vrr_infopacket.valid)
		वापस;

	*info_packet = stream->vrr_infopacket;
पूर्ण

अटल व्योम set_hdr_अटल_info_packet(
		काष्ठा dc_info_packet *info_packet,
		काष्ठा dc_stream_state *stream)
अणु
	/* HDR Static Metadata info packet क्रम HDR10 */

	अगर (!stream->hdr_अटल_metadata.valid ||
			stream->use_dynamic_meta)
		वापस;

	*info_packet = stream->hdr_अटल_metadata;
पूर्ण

अटल व्योम set_vsc_info_packet(
		काष्ठा dc_info_packet *info_packet,
		काष्ठा dc_stream_state *stream)
अणु
	अगर (!stream->vsc_infopacket.valid)
		वापस;

	*info_packet = stream->vsc_infopacket;
पूर्ण

व्योम dc_resource_state_deकाष्ठा(काष्ठा dc_state *context)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < context->stream_count; i++) अणु
		क्रम (j = 0; j < context->stream_status[i].plane_count; j++)
			dc_plane_state_release(
				context->stream_status[i].plane_states[j]);

		context->stream_status[i].plane_count = 0;
		dc_stream_release(context->streams[i]);
		context->streams[i] = शून्य;
	पूर्ण
पूर्ण

व्योम dc_resource_state_copy_स्थिरruct(
		स्थिर काष्ठा dc_state *src_ctx,
		काष्ठा dc_state *dst_ctx)
अणु
	पूर्णांक i, j;
	काष्ठा kref refcount = dst_ctx->refcount;

	*dst_ctx = *src_ctx;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		काष्ठा pipe_ctx *cur_pipe = &dst_ctx->res_ctx.pipe_ctx[i];

		अगर (cur_pipe->top_pipe)
			cur_pipe->top_pipe =  &dst_ctx->res_ctx.pipe_ctx[cur_pipe->top_pipe->pipe_idx];

		अगर (cur_pipe->bottom_pipe)
			cur_pipe->bottom_pipe = &dst_ctx->res_ctx.pipe_ctx[cur_pipe->bottom_pipe->pipe_idx];

		अगर (cur_pipe->next_odm_pipe)
			cur_pipe->next_odm_pipe =  &dst_ctx->res_ctx.pipe_ctx[cur_pipe->next_odm_pipe->pipe_idx];

		अगर (cur_pipe->prev_odm_pipe)
			cur_pipe->prev_odm_pipe = &dst_ctx->res_ctx.pipe_ctx[cur_pipe->prev_odm_pipe->pipe_idx];
	पूर्ण

	क्रम (i = 0; i < dst_ctx->stream_count; i++) अणु
		dc_stream_retain(dst_ctx->streams[i]);
		क्रम (j = 0; j < dst_ctx->stream_status[i].plane_count; j++)
			dc_plane_state_retain(
				dst_ctx->stream_status[i].plane_states[j]);
	पूर्ण

	/* context refcount should not be overridden */
	dst_ctx->refcount = refcount;

पूर्ण

काष्ठा घड़ी_source *dc_resource_find_first_मुक्त_pll(
		काष्ठा resource_context *res_ctx,
		स्थिर काष्ठा resource_pool *pool)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pool->clk_src_count; ++i) अणु
		अगर (res_ctx->घड़ी_source_ref_count[i] == 0)
			वापस pool->घड़ी_sources[i];
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम resource_build_info_frame(काष्ठा pipe_ctx *pipe_ctx)
अणु
	क्रमागत संकेत_type संकेत = SIGNAL_TYPE_NONE;
	काष्ठा encoder_info_frame *info = &pipe_ctx->stream_res.encoder_info_frame;

	/* शेष all packets to invalid */
	info->avi.valid = false;
	info->gamut.valid = false;
	info->venकरोr.valid = false;
	info->spd.valid = false;
	info->hdrsmd.valid = false;
	info->vsc.valid = false;

	संकेत = pipe_ctx->stream->संकेत;

	/* HDMi and DP have dअगरferent info packets*/
	अगर (dc_is_hdmi_संकेत(संकेत)) अणु
		set_avi_info_frame(&info->avi, pipe_ctx);

		set_venकरोr_info_packet(&info->venकरोr, pipe_ctx->stream);

		set_spd_info_packet(&info->spd, pipe_ctx->stream);

		set_hdr_अटल_info_packet(&info->hdrsmd, pipe_ctx->stream);

	पूर्ण अन्यथा अगर (dc_is_dp_संकेत(संकेत)) अणु
		set_vsc_info_packet(&info->vsc, pipe_ctx->stream);

		set_spd_info_packet(&info->spd, pipe_ctx->stream);

		set_hdr_अटल_info_packet(&info->hdrsmd, pipe_ctx->stream);
	पूर्ण

	patch_gamut_packet_checksum(&info->gamut);
पूर्ण

क्रमागत dc_status resource_map_घड़ी_resources(
		स्थिर काष्ठा dc  *dc,
		काष्ठा dc_state *context,
		काष्ठा dc_stream_state *stream)
अणु
	/* acquire new resources */
	स्थिर काष्ठा resource_pool *pool = dc->res_pool;
	काष्ठा pipe_ctx *pipe_ctx = resource_get_head_pipe_क्रम_stream(
				&context->res_ctx, stream);

	अगर (!pipe_ctx)
		वापस DC_ERROR_UNEXPECTED;

	अगर (dc_is_dp_संकेत(pipe_ctx->stream->संकेत)
		|| pipe_ctx->stream->संकेत == SIGNAL_TYPE_VIRTUAL)
		pipe_ctx->घड़ी_source = pool->dp_घड़ी_source;
	अन्यथा अणु
		pipe_ctx->घड़ी_source = शून्य;

		अगर (!dc->config.disable_disp_pll_sharing)
			pipe_ctx->घड़ी_source = resource_find_used_clk_src_क्रम_sharing(
				&context->res_ctx,
				pipe_ctx);

		अगर (pipe_ctx->घड़ी_source == शून्य)
			pipe_ctx->घड़ी_source =
				dc_resource_find_first_मुक्त_pll(
					&context->res_ctx,
					pool);
	पूर्ण

	अगर (pipe_ctx->घड़ी_source == शून्य)
		वापस DC_NO_CLOCK_SOURCE_RESOURCE;

	resource_reference_घड़ी_source(
		&context->res_ctx, pool,
		pipe_ctx->घड़ी_source);

	वापस DC_OK;
पूर्ण

/*
 * Note: We need to disable output अगर घड़ी sources change,
 * since bios करोes optimization and करोesn't apply अगर changing
 * PHY when not alपढ़ोy disabled.
 */
bool pipe_need_reprogram(
		काष्ठा pipe_ctx *pipe_ctx_old,
		काष्ठा pipe_ctx *pipe_ctx)
अणु
	अगर (!pipe_ctx_old->stream)
		वापस false;

	अगर (pipe_ctx_old->stream->sink != pipe_ctx->stream->sink)
		वापस true;

	अगर (pipe_ctx_old->stream->संकेत != pipe_ctx->stream->संकेत)
		वापस true;

	अगर (pipe_ctx_old->stream_res.audio != pipe_ctx->stream_res.audio)
		वापस true;

	अगर (pipe_ctx_old->घड़ी_source != pipe_ctx->घड़ी_source
			&& pipe_ctx_old->stream != pipe_ctx->stream)
		वापस true;

	अगर (pipe_ctx_old->stream_res.stream_enc != pipe_ctx->stream_res.stream_enc)
		वापस true;

	अगर (is_timing_changed(pipe_ctx_old->stream, pipe_ctx->stream))
		वापस true;

	अगर (pipe_ctx_old->stream->dpms_off != pipe_ctx->stream->dpms_off)
		वापस true;

	अगर (false == pipe_ctx_old->stream->link->link_state_valid &&
		false == pipe_ctx_old->stream->dpms_off)
		वापस true;

	अगर (pipe_ctx_old->stream_res.dsc != pipe_ctx->stream_res.dsc)
		वापस true;

	/* DIG link encoder resource assignment क्रम stream changed. */
	अगर (pipe_ctx_old->stream->link_enc != pipe_ctx->stream->link_enc)
		वापस true;

	वापस false;
पूर्ण

व्योम resource_build_bit_depth_reduction_params(काष्ठा dc_stream_state *stream,
		काष्ठा bit_depth_reduction_params *fmt_bit_depth)
अणु
	क्रमागत dc_dither_option option = stream->dither_option;
	क्रमागत dc_pixel_encoding pixel_encoding =
			stream->timing.pixel_encoding;

	स_रखो(fmt_bit_depth, 0, माप(*fmt_bit_depth));

	अगर (option == DITHER_OPTION_DEFAULT) अणु
		चयन (stream->timing.display_color_depth) अणु
		हाल COLOR_DEPTH_666:
			option = DITHER_OPTION_SPATIAL6;
			अवरोध;
		हाल COLOR_DEPTH_888:
			option = DITHER_OPTION_SPATIAL8;
			अवरोध;
		हाल COLOR_DEPTH_101010:
			option = DITHER_OPTION_SPATIAL10;
			अवरोध;
		शेष:
			option = DITHER_OPTION_DISABLE;
		पूर्ण
	पूर्ण

	अगर (option == DITHER_OPTION_DISABLE)
		वापस;

	अगर (option == DITHER_OPTION_TRUN6) अणु
		fmt_bit_depth->flags.TRUNCATE_ENABLED = 1;
		fmt_bit_depth->flags.TRUNCATE_DEPTH = 0;
	पूर्ण अन्यथा अगर (option == DITHER_OPTION_TRUN8 ||
			option == DITHER_OPTION_TRUN8_SPATIAL6 ||
			option == DITHER_OPTION_TRUN8_FM6) अणु
		fmt_bit_depth->flags.TRUNCATE_ENABLED = 1;
		fmt_bit_depth->flags.TRUNCATE_DEPTH = 1;
	पूर्ण अन्यथा अगर (option == DITHER_OPTION_TRUN10        ||
			option == DITHER_OPTION_TRUN10_SPATIAL6   ||
			option == DITHER_OPTION_TRUN10_SPATIAL8   ||
			option == DITHER_OPTION_TRUN10_FM8     ||
			option == DITHER_OPTION_TRUN10_FM6     ||
			option == DITHER_OPTION_TRUN10_SPATIAL8_FM6) अणु
		fmt_bit_depth->flags.TRUNCATE_ENABLED = 1;
		fmt_bit_depth->flags.TRUNCATE_DEPTH = 2;
	पूर्ण

	/* special हाल - Formatter can only reduce by 4 bits at most.
	 * When reducing from 12 to 6 bits,
	 * HW recommends we use trunc with round mode
	 * (अगर we did nothing, trunc to 10 bits would be used)
	 * note that any 12->10 bit reduction is ignored prior to DCE8,
	 * as the input was 10 bits.
	 */
	अगर (option == DITHER_OPTION_SPATIAL6_FRAME_RANDOM ||
			option == DITHER_OPTION_SPATIAL6 ||
			option == DITHER_OPTION_FM6) अणु
		fmt_bit_depth->flags.TRUNCATE_ENABLED = 1;
		fmt_bit_depth->flags.TRUNCATE_DEPTH = 2;
		fmt_bit_depth->flags.TRUNCATE_MODE = 1;
	पूर्ण

	/* spatial dither
	 * note that spatial modes 1-3 are never used
	 */
	अगर (option == DITHER_OPTION_SPATIAL6_FRAME_RANDOM            ||
			option == DITHER_OPTION_SPATIAL6 ||
			option == DITHER_OPTION_TRUN10_SPATIAL6      ||
			option == DITHER_OPTION_TRUN8_SPATIAL6) अणु
		fmt_bit_depth->flags.SPATIAL_DITHER_ENABLED = 1;
		fmt_bit_depth->flags.SPATIAL_DITHER_DEPTH = 0;
		fmt_bit_depth->flags.HIGHPASS_RANDOM = 1;
		fmt_bit_depth->flags.RGB_RANDOM =
				(pixel_encoding == PIXEL_ENCODING_RGB) ? 1 : 0;
	पूर्ण अन्यथा अगर (option == DITHER_OPTION_SPATIAL8_FRAME_RANDOM            ||
			option == DITHER_OPTION_SPATIAL8 ||
			option == DITHER_OPTION_SPATIAL8_FM6        ||
			option == DITHER_OPTION_TRUN10_SPATIAL8      ||
			option == DITHER_OPTION_TRUN10_SPATIAL8_FM6) अणु
		fmt_bit_depth->flags.SPATIAL_DITHER_ENABLED = 1;
		fmt_bit_depth->flags.SPATIAL_DITHER_DEPTH = 1;
		fmt_bit_depth->flags.HIGHPASS_RANDOM = 1;
		fmt_bit_depth->flags.RGB_RANDOM =
				(pixel_encoding == PIXEL_ENCODING_RGB) ? 1 : 0;
	पूर्ण अन्यथा अगर (option == DITHER_OPTION_SPATIAL10_FRAME_RANDOM ||
			option == DITHER_OPTION_SPATIAL10 ||
			option == DITHER_OPTION_SPATIAL10_FM8 ||
			option == DITHER_OPTION_SPATIAL10_FM6) अणु
		fmt_bit_depth->flags.SPATIAL_DITHER_ENABLED = 1;
		fmt_bit_depth->flags.SPATIAL_DITHER_DEPTH = 2;
		fmt_bit_depth->flags.HIGHPASS_RANDOM = 1;
		fmt_bit_depth->flags.RGB_RANDOM =
				(pixel_encoding == PIXEL_ENCODING_RGB) ? 1 : 0;
	पूर्ण

	अगर (option == DITHER_OPTION_SPATIAL6 ||
			option == DITHER_OPTION_SPATIAL8 ||
			option == DITHER_OPTION_SPATIAL10) अणु
		fmt_bit_depth->flags.FRAME_RANDOM = 0;
	पूर्ण अन्यथा अणु
		fmt_bit_depth->flags.FRAME_RANDOM = 1;
	पूर्ण

	//////////////////////
	//// temporal dither
	//////////////////////
	अगर (option == DITHER_OPTION_FM6           ||
			option == DITHER_OPTION_SPATIAL8_FM6     ||
			option == DITHER_OPTION_SPATIAL10_FM6     ||
			option == DITHER_OPTION_TRUN10_FM6     ||
			option == DITHER_OPTION_TRUN8_FM6      ||
			option == DITHER_OPTION_TRUN10_SPATIAL8_FM6) अणु
		fmt_bit_depth->flags.FRAME_MODULATION_ENABLED = 1;
		fmt_bit_depth->flags.FRAME_MODULATION_DEPTH = 0;
	पूर्ण अन्यथा अगर (option == DITHER_OPTION_FM8        ||
			option == DITHER_OPTION_SPATIAL10_FM8  ||
			option == DITHER_OPTION_TRUN10_FM8) अणु
		fmt_bit_depth->flags.FRAME_MODULATION_ENABLED = 1;
		fmt_bit_depth->flags.FRAME_MODULATION_DEPTH = 1;
	पूर्ण अन्यथा अगर (option == DITHER_OPTION_FM10) अणु
		fmt_bit_depth->flags.FRAME_MODULATION_ENABLED = 1;
		fmt_bit_depth->flags.FRAME_MODULATION_DEPTH = 2;
	पूर्ण

	fmt_bit_depth->pixel_encoding = pixel_encoding;
पूर्ण

क्रमागत dc_status dc_validate_stream(काष्ठा dc *dc, काष्ठा dc_stream_state *stream)
अणु
	काष्ठा dc_link *link = stream->link;
	काष्ठा timing_generator *tg = dc->res_pool->timing_generators[0];
	क्रमागत dc_status res = DC_OK;

	calculate_phy_pix_clks(stream);

	अगर (!tg->funcs->validate_timing(tg, &stream->timing))
		res = DC_FAIL_CONTROLLER_VALIDATE;

	अगर (res == DC_OK) अणु
		अगर (!link->link_enc->funcs->validate_output_with_stream(
						link->link_enc, stream))
			res = DC_FAIL_ENC_VALIDATE;
	पूर्ण

	/* TODO: validate audio ASIC caps, encoder */

	अगर (res == DC_OK)
		res = dc_link_validate_mode_timing(stream,
		      link,
		      &stream->timing);

	वापस res;
पूर्ण

क्रमागत dc_status dc_validate_plane(काष्ठा dc *dc, स्थिर काष्ठा dc_plane_state *plane_state)
अणु
	क्रमागत dc_status res = DC_OK;

	/* TODO For now validates pixel क्रमmat only */
	अगर (dc->res_pool->funcs->validate_plane)
		वापस dc->res_pool->funcs->validate_plane(plane_state, &dc->caps);

	वापस res;
पूर्ण

अचिन्हित पूर्णांक resource_pixel_क्रमmat_to_bpp(क्रमागत surface_pixel_क्रमmat क्रमmat)
अणु
	चयन (क्रमmat) अणु
	हाल SURFACE_PIXEL_FORMAT_GRPH_PALETA_256_COLORS:
		वापस 8;
	हाल SURFACE_PIXEL_FORMAT_VIDEO_420_YCbCr:
	हाल SURFACE_PIXEL_FORMAT_VIDEO_420_YCrCb:
		वापस 12;
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB1555:
	हाल SURFACE_PIXEL_FORMAT_GRPH_RGB565:
	हाल SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCbCr:
	हाल SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCrCb:
		वापस 16;
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB8888:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR8888:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010_XR_BIAS:
#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	हाल SURFACE_PIXEL_FORMAT_GRPH_RGBE:
	हाल SURFACE_PIXEL_FORMAT_GRPH_RGBE_ALPHA:
#पूर्ण_अगर
		वापस 32;
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616F:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F:
		वापस 64;
	शेष:
		ASSERT_CRITICAL(false);
		वापस -1;
	पूर्ण
पूर्ण
अटल अचिन्हित पूर्णांक get_max_audio_sample_rate(काष्ठा audio_mode *modes)
अणु
	अगर (modes) अणु
		अगर (modes->sample_rates.rate.RATE_192)
			वापस 192000;
		अगर (modes->sample_rates.rate.RATE_176_4)
			वापस 176400;
		अगर (modes->sample_rates.rate.RATE_96)
			वापस 96000;
		अगर (modes->sample_rates.rate.RATE_88_2)
			वापस 88200;
		अगर (modes->sample_rates.rate.RATE_48)
			वापस 48000;
		अगर (modes->sample_rates.rate.RATE_44_1)
			वापस 44100;
		अगर (modes->sample_rates.rate.RATE_32)
			वापस 32000;
	पूर्ण
	/*original logic when no audio info*/
	वापस 441000;
पूर्ण

व्योम get_audio_check(काष्ठा audio_info *aud_modes,
	काष्ठा audio_check *audio_chk)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक max_sample_rate = 0;

	अगर (aud_modes) अणु
		audio_chk->audio_packet_type = 0x2;/*audio sample packet AP = .25 क्रम layout0, 1 क्रम layout1*/

		audio_chk->max_audiosample_rate = 0;
		क्रम (i = 0; i < aud_modes->mode_count; i++) अणु
			max_sample_rate = get_max_audio_sample_rate(&aud_modes->modes[i]);
			अगर (audio_chk->max_audiosample_rate < max_sample_rate)
				audio_chk->max_audiosample_rate = max_sample_rate;
			/*dts takes the same as type 2: AP = 0.25*/
		पूर्ण
		/*check which one take more bandwidth*/
		अगर (audio_chk->max_audiosample_rate > 192000)
			audio_chk->audio_packet_type = 0x9;/*AP =1*/
		audio_chk->acat = 0;/*not support*/
	पूर्ण
पूर्ण

