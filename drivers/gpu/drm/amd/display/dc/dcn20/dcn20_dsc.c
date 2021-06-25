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
 * Authors: AMD
 *
 */

#समावेश "reg_helper.h"
#समावेश "dcn20_dsc.h"
#समावेश "dsc/dscc_types.h"

अटल व्योम dsc_log_pps(काष्ठा display_stream_compressor *dsc, काष्ठा drm_dsc_config *pps);
अटल bool dsc_prepare_config(स्थिर काष्ठा dsc_config *dsc_cfg, काष्ठा dsc_reg_values *dsc_reg_vals,
			काष्ठा dsc_optc_config *dsc_optc_cfg);
अटल व्योम dsc_init_reg_values(काष्ठा dsc_reg_values *reg_vals);
अटल व्योम dsc_update_from_dsc_parameters(काष्ठा dsc_reg_values *reg_vals, स्थिर काष्ठा dsc_parameters *dsc_params);
अटल व्योम dsc_ग_लिखो_to_रेजिस्टरs(काष्ठा display_stream_compressor *dsc, स्थिर काष्ठा dsc_reg_values *reg_vals);
अटल क्रमागत dsc_pixel_क्रमmat dsc_dc_pixel_encoding_to_dsc_pixel_क्रमmat(क्रमागत dc_pixel_encoding dc_pix_enc, bool is_ycbcr422_simple);
अटल क्रमागत dsc_bits_per_comp dsc_dc_color_depth_to_dsc_bits_per_comp(क्रमागत dc_color_depth);

/* Object I/F functions */
अटल व्योम dsc2_get_enc_caps(काष्ठा dsc_enc_caps *dsc_enc_caps, पूर्णांक pixel_घड़ी_100Hz);
अटल व्योम dsc2_पढ़ो_state(काष्ठा display_stream_compressor *dsc, काष्ठा dcn_dsc_state *s);
अटल bool dsc2_validate_stream(काष्ठा display_stream_compressor *dsc, स्थिर काष्ठा dsc_config *dsc_cfg);
अटल व्योम dsc2_set_config(काष्ठा display_stream_compressor *dsc, स्थिर काष्ठा dsc_config *dsc_cfg,
		काष्ठा dsc_optc_config *dsc_optc_cfg);
अटल bool dsc2_get_packed_pps(काष्ठा display_stream_compressor *dsc, स्थिर काष्ठा dsc_config *dsc_cfg, uपूर्णांक8_t *dsc_packed_pps);
अटल व्योम dsc2_enable(काष्ठा display_stream_compressor *dsc, पूर्णांक opp_pipe);
अटल व्योम dsc2_disable(काष्ठा display_stream_compressor *dsc);

स्थिर काष्ठा dsc_funcs dcn20_dsc_funcs = अणु
	.dsc_get_enc_caps = dsc2_get_enc_caps,
	.dsc_पढ़ो_state = dsc2_पढ़ो_state,
	.dsc_validate_stream = dsc2_validate_stream,
	.dsc_set_config = dsc2_set_config,
	.dsc_get_packed_pps = dsc2_get_packed_pps,
	.dsc_enable = dsc2_enable,
	.dsc_disable = dsc2_disable,
पूर्ण;

/* Macro definitios क्रम REG_SET macros*/
#घोषणा CTX \
	dsc20->base.ctx

#घोषणा REG(reg)\
	dsc20->dsc_regs->reg

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	dsc20->dsc_shअगरt->field_name, dsc20->dsc_mask->field_name
#घोषणा DC_LOGGER \
	dsc->ctx->logger

क्रमागत dsc_bits_per_comp अणु
	DSC_BPC_8 = 8,
	DSC_BPC_10 = 10,
	DSC_BPC_12 = 12,
	DSC_BPC_UNKNOWN
पूर्ण;

/* API functions (बाह्यal or via काष्ठाure->function_poपूर्णांकer) */

व्योम dsc2_स्थिरruct(काष्ठा dcn20_dsc *dsc,
		काष्ठा dc_context *ctx,
		पूर्णांक inst,
		स्थिर काष्ठा dcn20_dsc_रेजिस्टरs *dsc_regs,
		स्थिर काष्ठा dcn20_dsc_shअगरt *dsc_shअगरt,
		स्थिर काष्ठा dcn20_dsc_mask *dsc_mask)
अणु
	dsc->base.ctx = ctx;
	dsc->base.inst = inst;
	dsc->base.funcs = &dcn20_dsc_funcs;

	dsc->dsc_regs = dsc_regs;
	dsc->dsc_shअगरt = dsc_shअगरt;
	dsc->dsc_mask = dsc_mask;

	dsc->max_image_width = 5184;
पूर्ण


#घोषणा DCN20_MAX_PIXEL_CLOCK_Mhz      1188
#घोषणा DCN20_MAX_DISPLAY_CLOCK_Mhz    1200

/* This वापसs the capabilities क्रम a single DSC encoder engine. Number of slices and total throughput
 * can be द्विगुनd, tripled etc. by using additional DSC engines.
 */
अटल व्योम dsc2_get_enc_caps(काष्ठा dsc_enc_caps *dsc_enc_caps, पूर्णांक pixel_घड़ी_100Hz)
अणु
	dsc_enc_caps->dsc_version = 0x21; /* v1.2 - DP spec defined it in reverse order and we kept it */

	dsc_enc_caps->slice_caps.bits.NUM_SLICES_1 = 1;
	dsc_enc_caps->slice_caps.bits.NUM_SLICES_2 = 1;
	dsc_enc_caps->slice_caps.bits.NUM_SLICES_3 = 1;
	dsc_enc_caps->slice_caps.bits.NUM_SLICES_4 = 1;

	dsc_enc_caps->lb_bit_depth = 13;
	dsc_enc_caps->is_block_pred_supported = true;

	dsc_enc_caps->color_क्रमmats.bits.RGB = 1;
	dsc_enc_caps->color_क्रमmats.bits.YCBCR_444 = 1;
	dsc_enc_caps->color_क्रमmats.bits.YCBCR_SIMPLE_422 = 1;
	dsc_enc_caps->color_क्रमmats.bits.YCBCR_NATIVE_422 = 0;
	dsc_enc_caps->color_क्रमmats.bits.YCBCR_NATIVE_420 = 1;

	dsc_enc_caps->color_depth.bits.COLOR_DEPTH_8_BPC = 1;
	dsc_enc_caps->color_depth.bits.COLOR_DEPTH_10_BPC = 1;
	dsc_enc_caps->color_depth.bits.COLOR_DEPTH_12_BPC = 1;

	/* Maximum total throughput with all the slices combined. This is dअगरferent from how DP spec specअगरies it.
	 * Our decoder's total throughput in Pix/s is equal to DISPCLK. This is then shared between slices.
	 * The value below is the असलolute maximum value. The actual throughput may be lower, but it'll always
	 * be sufficient to process the input pixel rate fed पूर्णांकo a single DSC engine.
	 */
	dsc_enc_caps->max_total_throughput_mps = DCN20_MAX_DISPLAY_CLOCK_Mhz;

	/* For pixel घड़ी bigger than a single-pipe limit we'll need two engines, which then द्विगुनs our
	 * throughput and number of slices, but also पूर्णांकroduces a lower limit of 2 slices
	 */
	अगर (pixel_घड़ी_100Hz >= DCN20_MAX_PIXEL_CLOCK_Mhz*10000) अणु
		dsc_enc_caps->slice_caps.bits.NUM_SLICES_1 = 0;
		dsc_enc_caps->slice_caps.bits.NUM_SLICES_8 = 1;
		dsc_enc_caps->max_total_throughput_mps = DCN20_MAX_DISPLAY_CLOCK_Mhz * 2;
	पूर्ण

	// TODO DSC: This is actually image width limitation, not a slice width. This should be added to the criteria to use ODM.
	dsc_enc_caps->max_slice_width = 5184; /* (including 64 overlap pixels क्रम eDP MSO mode) */
	dsc_enc_caps->bpp_increment_भाग = 16; /* 1/16th of a bit */
पूर्ण


/* this function पढ़ो dsc related रेजिस्टर fields to be logged later in dcn10_log_hw_state
 * पूर्णांकo a dcn_dsc_state काष्ठा.
 */
अटल व्योम dsc2_पढ़ो_state(काष्ठा display_stream_compressor *dsc, काष्ठा dcn_dsc_state *s)
अणु
	काष्ठा dcn20_dsc *dsc20 = TO_DCN20_DSC(dsc);

	REG_GET(DSC_TOP_CONTROL, DSC_CLOCK_EN, &s->dsc_घड़ी_en);
	REG_GET(DSCC_PPS_CONFIG3, SLICE_WIDTH, &s->dsc_slice_width);
	REG_GET(DSCC_PPS_CONFIG1, BITS_PER_PIXEL, &s->dsc_bits_per_pixel);
	REG_GET(DSCC_PPS_CONFIG3, SLICE_HEIGHT, &s->dsc_slice_height);
	REG_GET(DSCC_PPS_CONFIG1, CHUNK_SIZE, &s->dsc_chunk_size);
	REG_GET(DSCC_PPS_CONFIG2, PIC_WIDTH, &s->dsc_pic_width);
	REG_GET(DSCC_PPS_CONFIG2, PIC_HEIGHT, &s->dsc_pic_height);
	REG_GET(DSCC_PPS_CONFIG7, SLICE_BPG_OFFSET, &s->dsc_slice_bpg_offset);
पूर्ण


अटल bool dsc2_validate_stream(काष्ठा display_stream_compressor *dsc, स्थिर काष्ठा dsc_config *dsc_cfg)
अणु
	काष्ठा dsc_optc_config dsc_optc_cfg;
	काष्ठा dcn20_dsc *dsc20 = TO_DCN20_DSC(dsc);

	अगर (dsc_cfg->pic_width > dsc20->max_image_width)
		वापस false;

	वापस dsc_prepare_config(dsc_cfg, &dsc20->reg_vals, &dsc_optc_cfg);
पूर्ण


अटल व्योम dsc_config_log(काष्ठा display_stream_compressor *dsc, स्थिर काष्ठा dsc_config *config)
अणु
	DC_LOG_DSC("\tnum_slices_h %d", config->dc_dsc_cfg.num_slices_h);
	DC_LOG_DSC("\tnum_slices_v %d", config->dc_dsc_cfg.num_slices_v);
	DC_LOG_DSC("\tbits_per_pixel %d (%d.%04d)",
		config->dc_dsc_cfg.bits_per_pixel,
		config->dc_dsc_cfg.bits_per_pixel / 16,
		((config->dc_dsc_cfg.bits_per_pixel % 16) * 10000) / 16);
	DC_LOG_DSC("\tcolor_depth %d", config->color_depth);
पूर्ण

अटल व्योम dsc2_set_config(काष्ठा display_stream_compressor *dsc, स्थिर काष्ठा dsc_config *dsc_cfg,
		काष्ठा dsc_optc_config *dsc_optc_cfg)
अणु
	bool is_config_ok;
	काष्ठा dcn20_dsc *dsc20 = TO_DCN20_DSC(dsc);

	DC_LOG_DSC(" ");
	DC_LOG_DSC("Setting DSC Config at DSC inst %d", dsc->inst);
	dsc_config_log(dsc, dsc_cfg);
	is_config_ok = dsc_prepare_config(dsc_cfg, &dsc20->reg_vals, dsc_optc_cfg);
	ASSERT(is_config_ok);
	DC_LOG_DSC("programming DSC Picture Parameter Set (PPS):");
	dsc_log_pps(dsc, &dsc20->reg_vals.pps);
	dsc_ग_लिखो_to_रेजिस्टरs(dsc, &dsc20->reg_vals);
पूर्ण


अटल bool dsc2_get_packed_pps(काष्ठा display_stream_compressor *dsc, स्थिर काष्ठा dsc_config *dsc_cfg, uपूर्णांक8_t *dsc_packed_pps)
अणु
	bool is_config_ok;
	काष्ठा dsc_reg_values dsc_reg_vals;
	काष्ठा dsc_optc_config dsc_optc_cfg;

	स_रखो(&dsc_reg_vals, 0, माप(dsc_reg_vals));
	स_रखो(&dsc_optc_cfg, 0, माप(dsc_optc_cfg));

	DC_LOG_DSC("Getting packed DSC PPS for DSC Config:");
	dsc_config_log(dsc, dsc_cfg);
	DC_LOG_DSC("DSC Picture Parameter Set (PPS):");
	is_config_ok = dsc_prepare_config(dsc_cfg, &dsc_reg_vals, &dsc_optc_cfg);
	ASSERT(is_config_ok);
	drm_dsc_pps_payload_pack((काष्ठा drm_dsc_picture_parameter_set *)dsc_packed_pps, &dsc_reg_vals.pps);
	dsc_log_pps(dsc, &dsc_reg_vals.pps);

	वापस is_config_ok;
पूर्ण


अटल व्योम dsc2_enable(काष्ठा display_stream_compressor *dsc, पूर्णांक opp_pipe)
अणु
	काष्ठा dcn20_dsc *dsc20 = TO_DCN20_DSC(dsc);
	पूर्णांक dsc_घड़ी_en;
	पूर्णांक dsc_fw_config;
	पूर्णांक enabled_opp_pipe;

	DC_LOG_DSC("enable DSC %d at opp pipe %d", dsc->inst, opp_pipe);

	REG_GET(DSC_TOP_CONTROL, DSC_CLOCK_EN, &dsc_घड़ी_en);
	REG_GET_2(DSCRM_DSC_FORWARD_CONFIG, DSCRM_DSC_FORWARD_EN, &dsc_fw_config, DSCRM_DSC_OPP_PIPE_SOURCE, &enabled_opp_pipe);
	अगर ((dsc_घड़ी_en || dsc_fw_config) && enabled_opp_pipe != opp_pipe) अणु
		DC_LOG_DSC("ERROR: DSC %d at opp pipe %d already enabled!", dsc->inst, enabled_opp_pipe);
		ASSERT(0);
	पूर्ण

	REG_UPDATE(DSC_TOP_CONTROL,
		DSC_CLOCK_EN, 1);

	REG_UPDATE_2(DSCRM_DSC_FORWARD_CONFIG,
		DSCRM_DSC_FORWARD_EN, 1,
		DSCRM_DSC_OPP_PIPE_SOURCE, opp_pipe);
पूर्ण


अटल व्योम dsc2_disable(काष्ठा display_stream_compressor *dsc)
अणु
	काष्ठा dcn20_dsc *dsc20 = TO_DCN20_DSC(dsc);
	पूर्णांक dsc_घड़ी_en;
	पूर्णांक dsc_fw_config;
	पूर्णांक enabled_opp_pipe;

	DC_LOG_DSC("disable DSC %d", dsc->inst);

	REG_GET(DSC_TOP_CONTROL, DSC_CLOCK_EN, &dsc_घड़ी_en);
	REG_GET_2(DSCRM_DSC_FORWARD_CONFIG, DSCRM_DSC_FORWARD_EN, &dsc_fw_config, DSCRM_DSC_OPP_PIPE_SOURCE, &enabled_opp_pipe);
	अगर (!dsc_घड़ी_en || !dsc_fw_config) अणु
		DC_LOG_DSC("ERROR: DSC %d at opp pipe %d already disabled!", dsc->inst, enabled_opp_pipe);
		ASSERT(0);
	पूर्ण

	REG_UPDATE(DSCRM_DSC_FORWARD_CONFIG,
		DSCRM_DSC_FORWARD_EN, 0);

	REG_UPDATE(DSC_TOP_CONTROL,
		DSC_CLOCK_EN, 0);
पूर्ण


/* This module's पूर्णांकernal functions */
अटल व्योम dsc_log_pps(काष्ठा display_stream_compressor *dsc, काष्ठा drm_dsc_config *pps)
अणु
	पूर्णांक i;
	पूर्णांक bits_per_pixel = pps->bits_per_pixel;

	DC_LOG_DSC("\tdsc_version_major %d", pps->dsc_version_major);
	DC_LOG_DSC("\tdsc_version_minor %d", pps->dsc_version_minor);
	DC_LOG_DSC("\tbits_per_component %d", pps->bits_per_component);
	DC_LOG_DSC("\tline_buf_depth %d", pps->line_buf_depth);
	DC_LOG_DSC("\tblock_pred_enable %d", pps->block_pred_enable);
	DC_LOG_DSC("\tconvert_rgb %d", pps->convert_rgb);
	DC_LOG_DSC("\tsimple_422 %d", pps->simple_422);
	DC_LOG_DSC("\tvbr_enable %d", pps->vbr_enable);
	DC_LOG_DSC("\tbits_per_pixel %d (%d.%04d)", bits_per_pixel, bits_per_pixel / 16, ((bits_per_pixel % 16) * 10000) / 16);
	DC_LOG_DSC("\tpic_height %d", pps->pic_height);
	DC_LOG_DSC("\tpic_width %d", pps->pic_width);
	DC_LOG_DSC("\tslice_height %d", pps->slice_height);
	DC_LOG_DSC("\tslice_width %d", pps->slice_width);
	DC_LOG_DSC("\tslice_chunk_size %d", pps->slice_chunk_size);
	DC_LOG_DSC("\tinitial_xmit_delay %d", pps->initial_xmit_delay);
	DC_LOG_DSC("\tinitial_dec_delay %d", pps->initial_dec_delay);
	DC_LOG_DSC("\tinitial_scale_value %d", pps->initial_scale_value);
	DC_LOG_DSC("\tscale_increment_interval %d", pps->scale_increment_पूर्णांकerval);
	DC_LOG_DSC("\tscale_decrement_interval %d", pps->scale_decrement_पूर्णांकerval);
	DC_LOG_DSC("\tfirst_line_bpg_offset %d", pps->first_line_bpg_offset);
	DC_LOG_DSC("\tnfl_bpg_offset %d", pps->nfl_bpg_offset);
	DC_LOG_DSC("\tslice_bpg_offset %d", pps->slice_bpg_offset);
	DC_LOG_DSC("\tinitial_offset %d", pps->initial_offset);
	DC_LOG_DSC("\tfinal_offset %d", pps->final_offset);
	DC_LOG_DSC("\tflatness_min_qp %d", pps->flatness_min_qp);
	DC_LOG_DSC("\tflatness_max_qp %d", pps->flatness_max_qp);
	/* DC_LOG_DSC("\trc_parameter_set %d", pps->rc_parameter_set); */
	DC_LOG_DSC("\tnative_420 %d", pps->native_420);
	DC_LOG_DSC("\tnative_422 %d", pps->native_422);
	DC_LOG_DSC("\tsecond_line_bpg_offset %d", pps->second_line_bpg_offset);
	DC_LOG_DSC("\tnsl_bpg_offset %d", pps->nsl_bpg_offset);
	DC_LOG_DSC("\tsecond_line_offset_adj %d", pps->second_line_offset_adj);
	DC_LOG_DSC("\trc_model_size %d", pps->rc_model_size);
	DC_LOG_DSC("\trc_edge_factor %d", pps->rc_edge_factor);
	DC_LOG_DSC("\trc_quant_incr_limit0 %d", pps->rc_quant_incr_limit0);
	DC_LOG_DSC("\trc_quant_incr_limit1 %d", pps->rc_quant_incr_limit1);
	DC_LOG_DSC("\trc_tgt_offset_high %d", pps->rc_tgt_offset_high);
	DC_LOG_DSC("\trc_tgt_offset_low %d", pps->rc_tgt_offset_low);

	क्रम (i = 0; i < NUM_BUF_RANGES - 1; i++)
		DC_LOG_DSC("\trc_buf_thresh[%d] %d", i, pps->rc_buf_thresh[i]);

	क्रम (i = 0; i < NUM_BUF_RANGES; i++) अणु
		DC_LOG_DSC("\trc_range_parameters[%d].range_min_qp %d", i, pps->rc_range_params[i].range_min_qp);
		DC_LOG_DSC("\trc_range_parameters[%d].range_max_qp %d", i, pps->rc_range_params[i].range_max_qp);
		DC_LOG_DSC("\trc_range_parameters[%d].range_bpg_offset %d", i, pps->rc_range_params[i].range_bpg_offset);
	पूर्ण
पूर्ण

अटल bool dsc_prepare_config(स्थिर काष्ठा dsc_config *dsc_cfg, काष्ठा dsc_reg_values *dsc_reg_vals,
			काष्ठा dsc_optc_config *dsc_optc_cfg)
अणु
	काष्ठा dsc_parameters dsc_params;

	/* Validate input parameters */
	ASSERT(dsc_cfg->dc_dsc_cfg.num_slices_h);
	ASSERT(dsc_cfg->dc_dsc_cfg.num_slices_v);
	ASSERT(dsc_cfg->dc_dsc_cfg.version_minor == 1 || dsc_cfg->dc_dsc_cfg.version_minor == 2);
	ASSERT(dsc_cfg->pic_width);
	ASSERT(dsc_cfg->pic_height);
	ASSERT((dsc_cfg->dc_dsc_cfg.version_minor == 1 &&
		  (8 <= dsc_cfg->dc_dsc_cfg.linebuf_depth && dsc_cfg->dc_dsc_cfg.linebuf_depth <= 13)) ||
		(dsc_cfg->dc_dsc_cfg.version_minor == 2 &&
		  ((8 <= dsc_cfg->dc_dsc_cfg.linebuf_depth && dsc_cfg->dc_dsc_cfg.linebuf_depth <= 15) ||
		    dsc_cfg->dc_dsc_cfg.linebuf_depth == 0)));
	ASSERT(96 <= dsc_cfg->dc_dsc_cfg.bits_per_pixel && dsc_cfg->dc_dsc_cfg.bits_per_pixel <= 0x3ff); // 6.0 <= bits_per_pixel <= 63.9375

	अगर (!dsc_cfg->dc_dsc_cfg.num_slices_v || !dsc_cfg->dc_dsc_cfg.num_slices_h ||
		!(dsc_cfg->dc_dsc_cfg.version_minor == 1 || dsc_cfg->dc_dsc_cfg.version_minor == 2) ||
		!dsc_cfg->pic_width || !dsc_cfg->pic_height ||
		!((dsc_cfg->dc_dsc_cfg.version_minor == 1 && // v1.1 line buffer depth range:
			8 <= dsc_cfg->dc_dsc_cfg.linebuf_depth && dsc_cfg->dc_dsc_cfg.linebuf_depth <= 13) ||
		(dsc_cfg->dc_dsc_cfg.version_minor == 2 && // v1.2 line buffer depth range:
			((8 <= dsc_cfg->dc_dsc_cfg.linebuf_depth && dsc_cfg->dc_dsc_cfg.linebuf_depth <= 15) ||
			dsc_cfg->dc_dsc_cfg.linebuf_depth == 0))) ||
		!(96 <= dsc_cfg->dc_dsc_cfg.bits_per_pixel && dsc_cfg->dc_dsc_cfg.bits_per_pixel <= 0x3ff)) अणु
		dm_output_to_console("%s: Invalid parameters\n", __func__);
		वापस false;
	पूर्ण

	dsc_init_reg_values(dsc_reg_vals);

	/* Copy input config */
	dsc_reg_vals->pixel_क्रमmat = dsc_dc_pixel_encoding_to_dsc_pixel_क्रमmat(dsc_cfg->pixel_encoding, dsc_cfg->dc_dsc_cfg.ycbcr422_simple);
	dsc_reg_vals->num_slices_h = dsc_cfg->dc_dsc_cfg.num_slices_h;
	dsc_reg_vals->num_slices_v = dsc_cfg->dc_dsc_cfg.num_slices_v;
	dsc_reg_vals->pps.dsc_version_minor = dsc_cfg->dc_dsc_cfg.version_minor;
	dsc_reg_vals->pps.pic_width = dsc_cfg->pic_width;
	dsc_reg_vals->pps.pic_height = dsc_cfg->pic_height;
	dsc_reg_vals->pps.bits_per_component = dsc_dc_color_depth_to_dsc_bits_per_comp(dsc_cfg->color_depth);
	dsc_reg_vals->pps.block_pred_enable = dsc_cfg->dc_dsc_cfg.block_pred_enable;
	dsc_reg_vals->pps.line_buf_depth = dsc_cfg->dc_dsc_cfg.linebuf_depth;
	dsc_reg_vals->alternate_ich_encoding_en = dsc_reg_vals->pps.dsc_version_minor == 1 ? 0 : 1;
	dsc_reg_vals->ich_reset_at_eol = (dsc_cfg->is_odm || dsc_reg_vals->num_slices_h > 1) ? 0xF : 0;

	// TODO: in addition to validating slice height (pic height must be भागisible by slice height),
	// see what happens when the same condition करोesn't apply क्रम slice_width/pic_width.
	dsc_reg_vals->pps.slice_width = dsc_cfg->pic_width / dsc_cfg->dc_dsc_cfg.num_slices_h;
	dsc_reg_vals->pps.slice_height = dsc_cfg->pic_height / dsc_cfg->dc_dsc_cfg.num_slices_v;

	ASSERT(dsc_reg_vals->pps.slice_height * dsc_cfg->dc_dsc_cfg.num_slices_v == dsc_cfg->pic_height);
	अगर (!(dsc_reg_vals->pps.slice_height * dsc_cfg->dc_dsc_cfg.num_slices_v == dsc_cfg->pic_height)) अणु
		dm_output_to_console("%s: pix height %d not divisible by num_slices_v %d\n\n", __func__, dsc_cfg->pic_height, dsc_cfg->dc_dsc_cfg.num_slices_v);
		वापस false;
	पूर्ण

	dsc_reg_vals->bpp_x32 = dsc_cfg->dc_dsc_cfg.bits_per_pixel << 1;
	अगर (dsc_reg_vals->pixel_क्रमmat == DSC_PIXFMT_NATIVE_YCBCR420 || dsc_reg_vals->pixel_क्रमmat == DSC_PIXFMT_NATIVE_YCBCR422)
		dsc_reg_vals->pps.bits_per_pixel = dsc_reg_vals->bpp_x32;
	अन्यथा
		dsc_reg_vals->pps.bits_per_pixel = dsc_reg_vals->bpp_x32 >> 1;

	dsc_reg_vals->pps.convert_rgb = dsc_reg_vals->pixel_क्रमmat == DSC_PIXFMT_RGB ? 1 : 0;
	dsc_reg_vals->pps.native_422 = (dsc_reg_vals->pixel_क्रमmat == DSC_PIXFMT_NATIVE_YCBCR422);
	dsc_reg_vals->pps.native_420 = (dsc_reg_vals->pixel_क्रमmat == DSC_PIXFMT_NATIVE_YCBCR420);
	dsc_reg_vals->pps.simple_422 = (dsc_reg_vals->pixel_क्रमmat == DSC_PIXFMT_SIMPLE_YCBCR422);

	अगर (dscc_compute_dsc_parameters(&dsc_reg_vals->pps, &dsc_params)) अणु
		dm_output_to_console("%s: DSC config failed\n", __func__);
		वापस false;
	पूर्ण

	dsc_update_from_dsc_parameters(dsc_reg_vals, &dsc_params);

	dsc_optc_cfg->bytes_per_pixel = dsc_params.bytes_per_pixel;
	dsc_optc_cfg->slice_width = dsc_reg_vals->pps.slice_width;
	dsc_optc_cfg->is_pixel_क्रमmat_444 = dsc_reg_vals->pixel_क्रमmat == DSC_PIXFMT_RGB ||
					dsc_reg_vals->pixel_क्रमmat == DSC_PIXFMT_YCBCR444 ||
					dsc_reg_vals->pixel_क्रमmat == DSC_PIXFMT_SIMPLE_YCBCR422;

	वापस true;
पूर्ण


अटल क्रमागत dsc_pixel_क्रमmat dsc_dc_pixel_encoding_to_dsc_pixel_क्रमmat(क्रमागत dc_pixel_encoding dc_pix_enc, bool is_ycbcr422_simple)
अणु
	क्रमागत dsc_pixel_क्रमmat dsc_pix_fmt = DSC_PIXFMT_UNKNOWN;

	/* NOTE: We करोn't support DSC_PIXFMT_SIMPLE_YCBCR422 */

	चयन (dc_pix_enc) अणु
	हाल PIXEL_ENCODING_RGB:
		dsc_pix_fmt = DSC_PIXFMT_RGB;
		अवरोध;
	हाल PIXEL_ENCODING_YCBCR422:
		अगर (is_ycbcr422_simple)
			dsc_pix_fmt = DSC_PIXFMT_SIMPLE_YCBCR422;
		अन्यथा
			dsc_pix_fmt = DSC_PIXFMT_NATIVE_YCBCR422;
		अवरोध;
	हाल PIXEL_ENCODING_YCBCR444:
		dsc_pix_fmt = DSC_PIXFMT_YCBCR444;
		अवरोध;
	हाल PIXEL_ENCODING_YCBCR420:
		dsc_pix_fmt = DSC_PIXFMT_NATIVE_YCBCR420;
		अवरोध;
	शेष:
		dsc_pix_fmt = DSC_PIXFMT_UNKNOWN;
		अवरोध;
	पूर्ण

	ASSERT(dsc_pix_fmt != DSC_PIXFMT_UNKNOWN);
	वापस dsc_pix_fmt;
पूर्ण


अटल क्रमागत dsc_bits_per_comp dsc_dc_color_depth_to_dsc_bits_per_comp(क्रमागत dc_color_depth dc_color_depth)
अणु
	क्रमागत dsc_bits_per_comp bpc = DSC_BPC_UNKNOWN;

	चयन (dc_color_depth) अणु
	हाल COLOR_DEPTH_888:
		bpc = DSC_BPC_8;
		अवरोध;
	हाल COLOR_DEPTH_101010:
		bpc = DSC_BPC_10;
		अवरोध;
	हाल COLOR_DEPTH_121212:
		bpc = DSC_BPC_12;
		अवरोध;
	शेष:
		bpc = DSC_BPC_UNKNOWN;
		अवरोध;
	पूर्ण

	वापस bpc;
पूर्ण


अटल व्योम dsc_init_reg_values(काष्ठा dsc_reg_values *reg_vals)
अणु
	पूर्णांक i;

	स_रखो(reg_vals, 0, माप(काष्ठा dsc_reg_values));

	/* Non-PPS values */
	reg_vals->dsc_घड़ी_enable            = 1;
	reg_vals->dsc_घड़ी_gating_disable    = 0;
	reg_vals->underflow_recovery_en       = 0;
	reg_vals->underflow_occurred_पूर्णांक_en   = 0;
	reg_vals->underflow_occurred_status   = 0;
	reg_vals->ich_reset_at_eol            = 0;
	reg_vals->alternate_ich_encoding_en   = 0;
	reg_vals->rc_buffer_model_size        = 0;
	/*reg_vals->disable_ich                 = 0;*/
	reg_vals->dsc_dbg_en                  = 0;

	क्रम (i = 0; i < 4; i++)
		reg_vals->rc_buffer_model_overflow_पूर्णांक_en[i] = 0;

	/* PPS values */
	reg_vals->pps.dsc_version_minor           = 2;
	reg_vals->pps.dsc_version_major           = 1;
	reg_vals->pps.line_buf_depth              = 9;
	reg_vals->pps.bits_per_component          = 8;
	reg_vals->pps.block_pred_enable           = 1;
	reg_vals->pps.slice_chunk_size            = 0;
	reg_vals->pps.pic_width                   = 0;
	reg_vals->pps.pic_height                  = 0;
	reg_vals->pps.slice_width                 = 0;
	reg_vals->pps.slice_height                = 0;
	reg_vals->pps.initial_xmit_delay          = 170;
	reg_vals->pps.initial_dec_delay           = 0;
	reg_vals->pps.initial_scale_value         = 0;
	reg_vals->pps.scale_increment_पूर्णांकerval    = 0;
	reg_vals->pps.scale_decrement_पूर्णांकerval    = 0;
	reg_vals->pps.nfl_bpg_offset              = 0;
	reg_vals->pps.slice_bpg_offset            = 0;
	reg_vals->pps.nsl_bpg_offset              = 0;
	reg_vals->pps.initial_offset              = 6144;
	reg_vals->pps.final_offset                = 0;
	reg_vals->pps.flatness_min_qp             = 3;
	reg_vals->pps.flatness_max_qp             = 12;
	reg_vals->pps.rc_model_size               = 8192;
	reg_vals->pps.rc_edge_factor              = 6;
	reg_vals->pps.rc_quant_incr_limit0        = 11;
	reg_vals->pps.rc_quant_incr_limit1        = 11;
	reg_vals->pps.rc_tgt_offset_low           = 3;
	reg_vals->pps.rc_tgt_offset_high          = 3;
पूर्ण

/* Updates dsc_reg_values::reg_vals::xxx fields based on the values from computed params.
 * This is required because dscc_compute_dsc_parameters वापसs a modअगरied PPS, which in turn
 * affects non-PPS रेजिस्टर values.
 */
अटल व्योम dsc_update_from_dsc_parameters(काष्ठा dsc_reg_values *reg_vals, स्थिर काष्ठा dsc_parameters *dsc_params)
अणु
	पूर्णांक i;

	reg_vals->pps = dsc_params->pps;

	// pps_computed will have the "expanded" values; need to shअगरt them to make them fit क्रम regs.
	क्रम (i = 0; i < NUM_BUF_RANGES - 1; i++)
		reg_vals->pps.rc_buf_thresh[i] = reg_vals->pps.rc_buf_thresh[i] >> 6;

	reg_vals->rc_buffer_model_size = dsc_params->rc_buffer_model_size;
पूर्ण

अटल व्योम dsc_ग_लिखो_to_रेजिस्टरs(काष्ठा display_stream_compressor *dsc, स्थिर काष्ठा dsc_reg_values *reg_vals)
अणु
	uपूर्णांक32_t temp_पूर्णांक;
	काष्ठा dcn20_dsc *dsc20 = TO_DCN20_DSC(dsc);

	REG_SET(DSC_DEBUG_CONTROL, 0,
		DSC_DBG_EN, reg_vals->dsc_dbg_en);

	// dsccअगर रेजिस्टरs
	REG_SET_5(DSCCIF_CONFIG0, 0,
		INPUT_INTERFACE_UNDERFLOW_RECOVERY_EN, reg_vals->underflow_recovery_en,
		INPUT_INTERFACE_UNDERFLOW_OCCURRED_INT_EN, reg_vals->underflow_occurred_पूर्णांक_en,
		INPUT_INTERFACE_UNDERFLOW_OCCURRED_STATUS, reg_vals->underflow_occurred_status,
		INPUT_PIXEL_FORMAT, reg_vals->pixel_क्रमmat,
		DSCCIF_CONFIG0__BITS_PER_COMPONENT, reg_vals->pps.bits_per_component);

	REG_SET_2(DSCCIF_CONFIG1, 0,
		PIC_WIDTH, reg_vals->pps.pic_width,
		PIC_HEIGHT, reg_vals->pps.pic_height);

	// dscc रेजिस्टरs
	REG_SET_4(DSCC_CONFIG0, 0,
		ICH_RESET_AT_END_OF_LINE, reg_vals->ich_reset_at_eol,
		NUMBER_OF_SLICES_PER_LINE, reg_vals->num_slices_h - 1,
		ALTERNATE_ICH_ENCODING_EN, reg_vals->alternate_ich_encoding_en,
		NUMBER_OF_SLICES_IN_VERTICAL_सूचीECTION, reg_vals->num_slices_v - 1);

	REG_SET(DSCC_CONFIG1, 0,
			DSCC_RATE_CONTROL_BUFFER_MODEL_SIZE, reg_vals->rc_buffer_model_size);
	/*REG_SET_2(DSCC_CONFIG1, 0,
		DSCC_RATE_CONTROL_BUFFER_MODEL_SIZE, reg_vals->rc_buffer_model_size,
		DSCC_DISABLE_ICH, reg_vals->disable_ich);*/

	REG_SET_4(DSCC_INTERRUPT_CONTROL_STATUS, 0,
		DSCC_RATE_CONTROL_BUFFER_MODEL0_OVERFLOW_OCCURRED_INT_EN, reg_vals->rc_buffer_model_overflow_पूर्णांक_en[0],
		DSCC_RATE_CONTROL_BUFFER_MODEL1_OVERFLOW_OCCURRED_INT_EN, reg_vals->rc_buffer_model_overflow_पूर्णांक_en[1],
		DSCC_RATE_CONTROL_BUFFER_MODEL2_OVERFLOW_OCCURRED_INT_EN, reg_vals->rc_buffer_model_overflow_पूर्णांक_en[2],
		DSCC_RATE_CONTROL_BUFFER_MODEL3_OVERFLOW_OCCURRED_INT_EN, reg_vals->rc_buffer_model_overflow_पूर्णांक_en[3]);

	REG_SET_3(DSCC_PPS_CONFIG0, 0,
		DSC_VERSION_MINOR, reg_vals->pps.dsc_version_minor,
		LINEBUF_DEPTH, reg_vals->pps.line_buf_depth,
		DSCC_PPS_CONFIG0__BITS_PER_COMPONENT, reg_vals->pps.bits_per_component);

	अगर (reg_vals->pixel_क्रमmat == DSC_PIXFMT_NATIVE_YCBCR420 || reg_vals->pixel_क्रमmat == DSC_PIXFMT_NATIVE_YCBCR422)
		temp_पूर्णांक = reg_vals->bpp_x32;
	अन्यथा
		temp_पूर्णांक = reg_vals->bpp_x32 >> 1;

	REG_SET_7(DSCC_PPS_CONFIG1, 0,
		BITS_PER_PIXEL, temp_पूर्णांक,
		SIMPLE_422, reg_vals->pixel_क्रमmat == DSC_PIXFMT_SIMPLE_YCBCR422,
		CONVERT_RGB, reg_vals->pixel_क्रमmat == DSC_PIXFMT_RGB,
		BLOCK_PRED_ENABLE, reg_vals->pps.block_pred_enable,
		NATIVE_422, reg_vals->pixel_क्रमmat == DSC_PIXFMT_NATIVE_YCBCR422,
		NATIVE_420, reg_vals->pixel_क्रमmat == DSC_PIXFMT_NATIVE_YCBCR420,
		CHUNK_SIZE, reg_vals->pps.slice_chunk_size);

	REG_SET_2(DSCC_PPS_CONFIG2, 0,
		PIC_WIDTH, reg_vals->pps.pic_width,
		PIC_HEIGHT, reg_vals->pps.pic_height);

	REG_SET_2(DSCC_PPS_CONFIG3, 0,
		SLICE_WIDTH, reg_vals->pps.slice_width,
		SLICE_HEIGHT, reg_vals->pps.slice_height);

	REG_SET(DSCC_PPS_CONFIG4, 0,
		INITIAL_XMIT_DELAY, reg_vals->pps.initial_xmit_delay);

	REG_SET_2(DSCC_PPS_CONFIG5, 0,
		INITIAL_SCALE_VALUE, reg_vals->pps.initial_scale_value,
		SCALE_INCREMENT_INTERVAL, reg_vals->pps.scale_increment_पूर्णांकerval);

	REG_SET_3(DSCC_PPS_CONFIG6, 0,
		SCALE_DECREMENT_INTERVAL, reg_vals->pps.scale_decrement_पूर्णांकerval,
		FIRST_LINE_BPG_OFFSET, reg_vals->pps.first_line_bpg_offset,
		SECOND_LINE_BPG_OFFSET, reg_vals->pps.second_line_bpg_offset);

	REG_SET_2(DSCC_PPS_CONFIG7, 0,
		NFL_BPG_OFFSET, reg_vals->pps.nfl_bpg_offset,
		SLICE_BPG_OFFSET, reg_vals->pps.slice_bpg_offset);

	REG_SET_2(DSCC_PPS_CONFIG8, 0,
		NSL_BPG_OFFSET, reg_vals->pps.nsl_bpg_offset,
		SECOND_LINE_OFFSET_ADJ, reg_vals->pps.second_line_offset_adj);

	REG_SET_2(DSCC_PPS_CONFIG9, 0,
		INITIAL_OFFSET, reg_vals->pps.initial_offset,
		FINAL_OFFSET, reg_vals->pps.final_offset);

	REG_SET_3(DSCC_PPS_CONFIG10, 0,
		FLATNESS_MIN_QP, reg_vals->pps.flatness_min_qp,
		FLATNESS_MAX_QP, reg_vals->pps.flatness_max_qp,
		RC_MODEL_SIZE, reg_vals->pps.rc_model_size);

	REG_SET_5(DSCC_PPS_CONFIG11, 0,
		RC_EDGE_FACTOR, reg_vals->pps.rc_edge_factor,
		RC_QUANT_INCR_LIMIT0, reg_vals->pps.rc_quant_incr_limit0,
		RC_QUANT_INCR_LIMIT1, reg_vals->pps.rc_quant_incr_limit1,
		RC_TGT_OFFSET_LO, reg_vals->pps.rc_tgt_offset_low,
		RC_TGT_OFFSET_HI, reg_vals->pps.rc_tgt_offset_high);

	REG_SET_4(DSCC_PPS_CONFIG12, 0,
		RC_BUF_THRESH0, reg_vals->pps.rc_buf_thresh[0],
		RC_BUF_THRESH1, reg_vals->pps.rc_buf_thresh[1],
		RC_BUF_THRESH2, reg_vals->pps.rc_buf_thresh[2],
		RC_BUF_THRESH3, reg_vals->pps.rc_buf_thresh[3]);

	REG_SET_4(DSCC_PPS_CONFIG13, 0,
		RC_BUF_THRESH4, reg_vals->pps.rc_buf_thresh[4],
		RC_BUF_THRESH5, reg_vals->pps.rc_buf_thresh[5],
		RC_BUF_THRESH6, reg_vals->pps.rc_buf_thresh[6],
		RC_BUF_THRESH7, reg_vals->pps.rc_buf_thresh[7]);

	REG_SET_4(DSCC_PPS_CONFIG14, 0,
		RC_BUF_THRESH8, reg_vals->pps.rc_buf_thresh[8],
		RC_BUF_THRESH9, reg_vals->pps.rc_buf_thresh[9],
		RC_BUF_THRESH10, reg_vals->pps.rc_buf_thresh[10],
		RC_BUF_THRESH11, reg_vals->pps.rc_buf_thresh[11]);

	REG_SET_5(DSCC_PPS_CONFIG15, 0,
		RC_BUF_THRESH12, reg_vals->pps.rc_buf_thresh[12],
		RC_BUF_THRESH13, reg_vals->pps.rc_buf_thresh[13],
		RANGE_MIN_QP0, reg_vals->pps.rc_range_params[0].range_min_qp,
		RANGE_MAX_QP0, reg_vals->pps.rc_range_params[0].range_max_qp,
		RANGE_BPG_OFFSET0, reg_vals->pps.rc_range_params[0].range_bpg_offset);

	REG_SET_6(DSCC_PPS_CONFIG16, 0,
		RANGE_MIN_QP1, reg_vals->pps.rc_range_params[1].range_min_qp,
		RANGE_MAX_QP1, reg_vals->pps.rc_range_params[1].range_max_qp,
		RANGE_BPG_OFFSET1, reg_vals->pps.rc_range_params[1].range_bpg_offset,
		RANGE_MIN_QP2, reg_vals->pps.rc_range_params[2].range_min_qp,
		RANGE_MAX_QP2, reg_vals->pps.rc_range_params[2].range_max_qp,
		RANGE_BPG_OFFSET2, reg_vals->pps.rc_range_params[2].range_bpg_offset);

	REG_SET_6(DSCC_PPS_CONFIG17, 0,
		RANGE_MIN_QP3, reg_vals->pps.rc_range_params[3].range_min_qp,
		RANGE_MAX_QP3, reg_vals->pps.rc_range_params[3].range_max_qp,
		RANGE_BPG_OFFSET3, reg_vals->pps.rc_range_params[3].range_bpg_offset,
		RANGE_MIN_QP4, reg_vals->pps.rc_range_params[4].range_min_qp,
		RANGE_MAX_QP4, reg_vals->pps.rc_range_params[4].range_max_qp,
		RANGE_BPG_OFFSET4, reg_vals->pps.rc_range_params[4].range_bpg_offset);

	REG_SET_6(DSCC_PPS_CONFIG18, 0,
		RANGE_MIN_QP5, reg_vals->pps.rc_range_params[5].range_min_qp,
		RANGE_MAX_QP5, reg_vals->pps.rc_range_params[5].range_max_qp,
		RANGE_BPG_OFFSET5, reg_vals->pps.rc_range_params[5].range_bpg_offset,
		RANGE_MIN_QP6, reg_vals->pps.rc_range_params[6].range_min_qp,
		RANGE_MAX_QP6, reg_vals->pps.rc_range_params[6].range_max_qp,
		RANGE_BPG_OFFSET6, reg_vals->pps.rc_range_params[6].range_bpg_offset);

	REG_SET_6(DSCC_PPS_CONFIG19, 0,
		RANGE_MIN_QP7, reg_vals->pps.rc_range_params[7].range_min_qp,
		RANGE_MAX_QP7, reg_vals->pps.rc_range_params[7].range_max_qp,
		RANGE_BPG_OFFSET7, reg_vals->pps.rc_range_params[7].range_bpg_offset,
		RANGE_MIN_QP8, reg_vals->pps.rc_range_params[8].range_min_qp,
		RANGE_MAX_QP8, reg_vals->pps.rc_range_params[8].range_max_qp,
		RANGE_BPG_OFFSET8, reg_vals->pps.rc_range_params[8].range_bpg_offset);

	REG_SET_6(DSCC_PPS_CONFIG20, 0,
		RANGE_MIN_QP9, reg_vals->pps.rc_range_params[9].range_min_qp,
		RANGE_MAX_QP9, reg_vals->pps.rc_range_params[9].range_max_qp,
		RANGE_BPG_OFFSET9, reg_vals->pps.rc_range_params[9].range_bpg_offset,
		RANGE_MIN_QP10, reg_vals->pps.rc_range_params[10].range_min_qp,
		RANGE_MAX_QP10, reg_vals->pps.rc_range_params[10].range_max_qp,
		RANGE_BPG_OFFSET10, reg_vals->pps.rc_range_params[10].range_bpg_offset);

	REG_SET_6(DSCC_PPS_CONFIG21, 0,
		RANGE_MIN_QP11, reg_vals->pps.rc_range_params[11].range_min_qp,
		RANGE_MAX_QP11, reg_vals->pps.rc_range_params[11].range_max_qp,
		RANGE_BPG_OFFSET11, reg_vals->pps.rc_range_params[11].range_bpg_offset,
		RANGE_MIN_QP12, reg_vals->pps.rc_range_params[12].range_min_qp,
		RANGE_MAX_QP12, reg_vals->pps.rc_range_params[12].range_max_qp,
		RANGE_BPG_OFFSET12, reg_vals->pps.rc_range_params[12].range_bpg_offset);

	REG_SET_6(DSCC_PPS_CONFIG22, 0,
		RANGE_MIN_QP13, reg_vals->pps.rc_range_params[13].range_min_qp,
		RANGE_MAX_QP13, reg_vals->pps.rc_range_params[13].range_max_qp,
		RANGE_BPG_OFFSET13, reg_vals->pps.rc_range_params[13].range_bpg_offset,
		RANGE_MIN_QP14, reg_vals->pps.rc_range_params[14].range_min_qp,
		RANGE_MAX_QP14, reg_vals->pps.rc_range_params[14].range_max_qp,
		RANGE_BPG_OFFSET14, reg_vals->pps.rc_range_params[14].range_bpg_offset);

पूर्ण

