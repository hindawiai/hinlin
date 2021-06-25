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

#समावेश "reg_helper.h"

#समावेश "core_types.h"
#समावेश "link_encoder.h"
#समावेश "dcn10_link_encoder.h"
#समावेश "stream_encoder.h"
#समावेश "i2caux_interface.h"
#समावेश "dc_bios_types.h"

#समावेश "gpio_service_interface.h"

#घोषणा CTX \
	enc10->base.ctx
#घोषणा DC_LOGGER \
	enc10->base.ctx->logger

#घोषणा REG(reg)\
	(enc10->link_regs->reg)

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	enc10->link_shअगरt->field_name, enc10->link_mask->field_name


/*
 * @brief
 * Trigger Source Select
 * ASIC-dependent, actual values क्रम रेजिस्टर programming
 */
#घोषणा DCN10_DIG_FE_SOURCE_SELECT_INVALID 0x0
#घोषणा DCN10_DIG_FE_SOURCE_SELECT_DIGA 0x1
#घोषणा DCN10_DIG_FE_SOURCE_SELECT_DIGB 0x2
#घोषणा DCN10_DIG_FE_SOURCE_SELECT_DIGC 0x4
#घोषणा DCN10_DIG_FE_SOURCE_SELECT_DIGD 0x08
#घोषणा DCN10_DIG_FE_SOURCE_SELECT_DIGE 0x10
#घोषणा DCN10_DIG_FE_SOURCE_SELECT_DIGF 0x20
#घोषणा DCN10_DIG_FE_SOURCE_SELECT_DIGG 0x40

क्रमागत अणु
	DP_MST_UPDATE_MAX_RETRY = 50
पूर्ण;

अटल स्थिर काष्ठा link_encoder_funcs dcn10_lnk_enc_funcs = अणु
	.validate_output_with_stream =
		dcn10_link_encoder_validate_output_with_stream,
	.hw_init = dcn10_link_encoder_hw_init,
	.setup = dcn10_link_encoder_setup,
	.enable_पंचांगds_output = dcn10_link_encoder_enable_पंचांगds_output,
	.enable_dp_output = dcn10_link_encoder_enable_dp_output,
	.enable_dp_mst_output = dcn10_link_encoder_enable_dp_mst_output,
	.disable_output = dcn10_link_encoder_disable_output,
	.dp_set_lane_settings = dcn10_link_encoder_dp_set_lane_settings,
	.dp_set_phy_pattern = dcn10_link_encoder_dp_set_phy_pattern,
	.update_mst_stream_allocation_table =
		dcn10_link_encoder_update_mst_stream_allocation_table,
	.psr_program_dp_dphy_fast_training =
			dcn10_psr_program_dp_dphy_fast_training,
	.psr_program_secondary_packet = dcn10_psr_program_secondary_packet,
	.connect_dig_be_to_fe = dcn10_link_encoder_connect_dig_be_to_fe,
	.enable_hpd = dcn10_link_encoder_enable_hpd,
	.disable_hpd = dcn10_link_encoder_disable_hpd,
	.is_dig_enabled = dcn10_is_dig_enabled,
	.get_dig_frontend = dcn10_get_dig_frontend,
	.get_dig_mode = dcn10_get_dig_mode,
	.destroy = dcn10_link_encoder_destroy,
	.get_max_link_cap = dcn10_link_encoder_get_max_link_cap,
पूर्ण;

अटल क्रमागत bp_result link_transmitter_control(
	काष्ठा dcn10_link_encoder *enc10,
	काष्ठा bp_transmitter_control *cntl)
अणु
	क्रमागत bp_result result;
	काष्ठा dc_bios *bp = enc10->base.ctx->dc_bios;

	result = bp->funcs->transmitter_control(bp, cntl);

	वापस result;
पूर्ण

अटल व्योम enable_phy_bypass_mode(
	काष्ठा dcn10_link_encoder *enc10,
	bool enable)
अणु
	/* This रेजिस्टर resides in DP back end block;
	 * transmitter is used क्रम the offset
	 */
	REG_UPDATE(DP_DPHY_CNTL, DPHY_BYPASS, enable);

पूर्ण

अटल व्योम disable_prbs_symbols(
	काष्ठा dcn10_link_encoder *enc10,
	bool disable)
अणु
	/* This रेजिस्टर resides in DP back end block;
	 * transmitter is used क्रम the offset
	 */
	REG_UPDATE_4(DP_DPHY_CNTL,
			DPHY_ATEST_SEL_LANE0, disable,
			DPHY_ATEST_SEL_LANE1, disable,
			DPHY_ATEST_SEL_LANE2, disable,
			DPHY_ATEST_SEL_LANE3, disable);
पूर्ण

अटल व्योम disable_prbs_mode(
	काष्ठा dcn10_link_encoder *enc10)
अणु
	REG_UPDATE(DP_DPHY_PRBS_CNTL, DPHY_PRBS_EN, 0);
पूर्ण

अटल व्योम program_pattern_symbols(
	काष्ठा dcn10_link_encoder *enc10,
	uपूर्णांक16_t pattern_symbols[8])
अणु
	/* This रेजिस्टर resides in DP back end block;
	 * transmitter is used क्रम the offset
	 */
	REG_SET_3(DP_DPHY_SYM0, 0,
			DPHY_SYM1, pattern_symbols[0],
			DPHY_SYM2, pattern_symbols[1],
			DPHY_SYM3, pattern_symbols[2]);

	/* This रेजिस्टर resides in DP back end block;
	 * transmitter is used क्रम the offset
	 */
	REG_SET_3(DP_DPHY_SYM1, 0,
			DPHY_SYM4, pattern_symbols[3],
			DPHY_SYM5, pattern_symbols[4],
			DPHY_SYM6, pattern_symbols[5]);

	/* This रेजिस्टर resides in DP back end block;
	 * transmitter is used क्रम the offset
	 */
	REG_SET_2(DP_DPHY_SYM2, 0,
			DPHY_SYM7, pattern_symbols[6],
			DPHY_SYM8, pattern_symbols[7]);
पूर्ण

अटल व्योम set_dp_phy_pattern_d102(
	काष्ठा dcn10_link_encoder *enc10)
अणु
	/* Disable PHY Bypass mode to setup the test pattern */
	enable_phy_bypass_mode(enc10, false);

	/* For 10-bit PRBS or debug symbols
	 * please use the following sequence:
	 *
	 * Enable debug symbols on the lanes
	 */
	disable_prbs_symbols(enc10, true);

	/* Disable PRBS mode */
	disable_prbs_mode(enc10);

	/* Program debug symbols to be output */
	अणु
		uपूर्णांक16_t pattern_symbols[8] = अणु
			0x2AA, 0x2AA, 0x2AA, 0x2AA,
			0x2AA, 0x2AA, 0x2AA, 0x2AA
		पूर्ण;

		program_pattern_symbols(enc10, pattern_symbols);
	पूर्ण

	/* Enable phy bypass mode to enable the test pattern */

	enable_phy_bypass_mode(enc10, true);
पूर्ण

अटल व्योम set_link_training_complete(
	काष्ठा dcn10_link_encoder *enc10,
	bool complete)
अणु
	/* This रेजिस्टर resides in DP back end block;
	 * transmitter is used क्रम the offset
	 */
	REG_UPDATE(DP_LINK_CNTL, DP_LINK_TRAINING_COMPLETE, complete);

पूर्ण

व्योम dcn10_link_encoder_set_dp_phy_pattern_training_pattern(
	काष्ठा link_encoder *enc,
	uपूर्णांक32_t index)
अणु
	काष्ठा dcn10_link_encoder *enc10 = TO_DCN10_LINK_ENC(enc);
	/* Write Training Pattern */

	REG_WRITE(DP_DPHY_TRAINING_PATTERN_SEL, index);

	/* Set HW Register Training Complete to false */

	set_link_training_complete(enc10, false);

	/* Disable PHY Bypass mode to output Training Pattern */

	enable_phy_bypass_mode(enc10, false);

	/* Disable PRBS mode */
	disable_prbs_mode(enc10);
पूर्ण

अटल व्योम setup_panel_mode(
	काष्ठा dcn10_link_encoder *enc10,
	क्रमागत dp_panel_mode panel_mode)
अणु
	uपूर्णांक32_t value;

	अगर (!REG(DP_DPHY_INTERNAL_CTRL))
		वापस;

	value = REG_READ(DP_DPHY_INTERNAL_CTRL);

	चयन (panel_mode) अणु
	हाल DP_PANEL_MODE_EDP:
		value = 0x1;
		अवरोध;
	हाल DP_PANEL_MODE_SPECIAL:
		value = 0x11;
		अवरोध;
	शेष:
		value = 0x0;
		अवरोध;
	पूर्ण

	REG_WRITE(DP_DPHY_INTERNAL_CTRL, value);
पूर्ण

अटल व्योम set_dp_phy_pattern_symbol_error(
	काष्ठा dcn10_link_encoder *enc10)
अणु
	/* Disable PHY Bypass mode to setup the test pattern */
	enable_phy_bypass_mode(enc10, false);

	/* program correct panel mode*/
	setup_panel_mode(enc10, DP_PANEL_MODE_DEFAULT);

	/* A PRBS23 pattern is used क्रम most DP electrical measurements. */

	/* Enable PRBS symbols on the lanes */
	disable_prbs_symbols(enc10, false);

	/* For PRBS23 Set bit DPHY_PRBS_SEL=1 and Set bit DPHY_PRBS_EN=1 */
	REG_UPDATE_2(DP_DPHY_PRBS_CNTL,
			DPHY_PRBS_SEL, 1,
			DPHY_PRBS_EN, 1);

	/* Enable phy bypass mode to enable the test pattern */
	enable_phy_bypass_mode(enc10, true);
पूर्ण

अटल व्योम set_dp_phy_pattern_prbs7(
	काष्ठा dcn10_link_encoder *enc10)
अणु
	/* Disable PHY Bypass mode to setup the test pattern */
	enable_phy_bypass_mode(enc10, false);

	/* A PRBS7 pattern is used क्रम most DP electrical measurements. */

	/* Enable PRBS symbols on the lanes */
	disable_prbs_symbols(enc10, false);

	/* For PRBS7 Set bit DPHY_PRBS_SEL=0 and Set bit DPHY_PRBS_EN=1 */
	REG_UPDATE_2(DP_DPHY_PRBS_CNTL,
			DPHY_PRBS_SEL, 0,
			DPHY_PRBS_EN, 1);

	/* Enable phy bypass mode to enable the test pattern */
	enable_phy_bypass_mode(enc10, true);
पूर्ण

अटल व्योम set_dp_phy_pattern_80bit_custom(
	काष्ठा dcn10_link_encoder *enc10,
	स्थिर uपूर्णांक8_t *pattern)
अणु
	/* Disable PHY Bypass mode to setup the test pattern */
	enable_phy_bypass_mode(enc10, false);

	/* Enable debug symbols on the lanes */

	disable_prbs_symbols(enc10, true);

	/* Enable PHY bypass mode to enable the test pattern */
	/* TODO is it really needed ? */

	enable_phy_bypass_mode(enc10, true);

	/* Program 80 bit custom pattern */
	अणु
		uपूर्णांक16_t pattern_symbols[8];

		pattern_symbols[0] =
			((pattern[1] & 0x03) << 8) | pattern[0];
		pattern_symbols[1] =
			((pattern[2] & 0x0f) << 6) | ((pattern[1] >> 2) & 0x3f);
		pattern_symbols[2] =
			((pattern[3] & 0x3f) << 4) | ((pattern[2] >> 4) & 0x0f);
		pattern_symbols[3] =
			(pattern[4] << 2) | ((pattern[3] >> 6) & 0x03);
		pattern_symbols[4] =
			((pattern[6] & 0x03) << 8) | pattern[5];
		pattern_symbols[5] =
			((pattern[7] & 0x0f) << 6) | ((pattern[6] >> 2) & 0x3f);
		pattern_symbols[6] =
			((pattern[8] & 0x3f) << 4) | ((pattern[7] >> 4) & 0x0f);
		pattern_symbols[7] =
			(pattern[9] << 2) | ((pattern[8] >> 6) & 0x03);

		program_pattern_symbols(enc10, pattern_symbols);
	पूर्ण

	/* Enable phy bypass mode to enable the test pattern */

	enable_phy_bypass_mode(enc10, true);
पूर्ण

अटल व्योम set_dp_phy_pattern_hbr2_compliance_cp2520_2(
	काष्ठा dcn10_link_encoder *enc10,
	अचिन्हित पूर्णांक cp2520_pattern)
अणु

	/* previously there is a रेजिस्टर DP_HBR2_EYE_PATTERN
	 * that is enabled to get the pattern.
	 * But it करोes not work with the latest spec change,
	 * so we are programming the following रेजिस्टरs manually.
	 *
	 * The following settings have been confirmed
	 * by Nick Chorney and Sandra Liu
	 */

	/* Disable PHY Bypass mode to setup the test pattern */

	enable_phy_bypass_mode(enc10, false);

	/* Setup DIG encoder in DP SST mode */
	enc10->base.funcs->setup(&enc10->base, SIGNAL_TYPE_DISPLAY_PORT);

	/* ensure normal panel mode. */
	setup_panel_mode(enc10, DP_PANEL_MODE_DEFAULT);

	/* no vbid after BS (SR)
	 * DP_LINK_FRAMING_CNTL changed history Sandra Liu
	 * 11000260 / 11000104 / 110000FC
	 */
	REG_UPDATE_3(DP_LINK_FRAMING_CNTL,
			DP_IDLE_BS_INTERVAL, 0xFC,
			DP_VBID_DISABLE, 1,
			DP_VID_ENHANCED_FRAME_MODE, 1);

	/* swap every BS with SR */
	REG_UPDATE(DP_DPHY_SCRAM_CNTL, DPHY_SCRAMBLER_BS_COUNT, 0);

	/* select cp2520 patterns */
	अगर (REG(DP_DPHY_HBR2_PATTERN_CONTROL))
		REG_UPDATE(DP_DPHY_HBR2_PATTERN_CONTROL,
				DP_DPHY_HBR2_PATTERN_CONTROL, cp2520_pattern);
	अन्यथा
		/* pre-DCE11 can only generate CP2520 pattern 2 */
		ASSERT(cp2520_pattern == 2);

	/* set link training complete */
	set_link_training_complete(enc10, true);

	/* disable video stream */
	REG_UPDATE(DP_VID_STREAM_CNTL, DP_VID_STREAM_ENABLE, 0);

	/* Disable PHY Bypass mode to setup the test pattern */
	enable_phy_bypass_mode(enc10, false);
पूर्ण

अटल व्योम set_dp_phy_pattern_passthrough_mode(
	काष्ठा dcn10_link_encoder *enc10,
	क्रमागत dp_panel_mode panel_mode)
अणु
	/* program correct panel mode */
	setup_panel_mode(enc10, panel_mode);

	/* restore LINK_FRAMING_CNTL and DPHY_SCRAMBLER_BS_COUNT
	 * in हाल we were करोing HBR2 compliance pattern beक्रमe
	 */
	REG_UPDATE_3(DP_LINK_FRAMING_CNTL,
			DP_IDLE_BS_INTERVAL, 0x2000,
			DP_VBID_DISABLE, 0,
			DP_VID_ENHANCED_FRAME_MODE, 1);

	REG_UPDATE(DP_DPHY_SCRAM_CNTL, DPHY_SCRAMBLER_BS_COUNT, 0x1FF);

	/* set link training complete */
	set_link_training_complete(enc10, true);

	/* Disable PHY Bypass mode to setup the test pattern */
	enable_phy_bypass_mode(enc10, false);

	/* Disable PRBS mode */
	disable_prbs_mode(enc10);
पूर्ण

/* वापस value is bit-vector */
अटल uपूर्णांक8_t get_frontend_source(
	क्रमागत engine_id engine)
अणु
	चयन (engine) अणु
	हाल ENGINE_ID_DIGA:
		वापस DCN10_DIG_FE_SOURCE_SELECT_DIGA;
	हाल ENGINE_ID_DIGB:
		वापस DCN10_DIG_FE_SOURCE_SELECT_DIGB;
	हाल ENGINE_ID_DIGC:
		वापस DCN10_DIG_FE_SOURCE_SELECT_DIGC;
	हाल ENGINE_ID_DIGD:
		वापस DCN10_DIG_FE_SOURCE_SELECT_DIGD;
	हाल ENGINE_ID_DIGE:
		वापस DCN10_DIG_FE_SOURCE_SELECT_DIGE;
	हाल ENGINE_ID_DIGF:
		वापस DCN10_DIG_FE_SOURCE_SELECT_DIGF;
	हाल ENGINE_ID_DIGG:
		वापस DCN10_DIG_FE_SOURCE_SELECT_DIGG;
	शेष:
		ASSERT_CRITICAL(false);
		वापस DCN10_DIG_FE_SOURCE_SELECT_INVALID;
	पूर्ण
पूर्ण

अचिन्हित पूर्णांक dcn10_get_dig_frontend(काष्ठा link_encoder *enc)
अणु
	काष्ठा dcn10_link_encoder *enc10 = TO_DCN10_LINK_ENC(enc);
	पूर्णांक32_t value;
	क्रमागत engine_id result;

	REG_GET(DIG_BE_CNTL, DIG_FE_SOURCE_SELECT, &value);

	चयन (value) अणु
	हाल DCN10_DIG_FE_SOURCE_SELECT_DIGA:
		result = ENGINE_ID_DIGA;
		अवरोध;
	हाल DCN10_DIG_FE_SOURCE_SELECT_DIGB:
		result = ENGINE_ID_DIGB;
		अवरोध;
	हाल DCN10_DIG_FE_SOURCE_SELECT_DIGC:
		result = ENGINE_ID_DIGC;
		अवरोध;
	हाल DCN10_DIG_FE_SOURCE_SELECT_DIGD:
		result = ENGINE_ID_DIGD;
		अवरोध;
	हाल DCN10_DIG_FE_SOURCE_SELECT_DIGE:
		result = ENGINE_ID_DIGE;
		अवरोध;
	हाल DCN10_DIG_FE_SOURCE_SELECT_DIGF:
		result = ENGINE_ID_DIGF;
		अवरोध;
	हाल DCN10_DIG_FE_SOURCE_SELECT_DIGG:
		result = ENGINE_ID_DIGG;
		अवरोध;
	शेष:
		// invalid source select DIG
		result = ENGINE_ID_UNKNOWN;
	पूर्ण

	वापस result;

पूर्ण

व्योम enc1_configure_encoder(
	काष्ठा dcn10_link_encoder *enc10,
	स्थिर काष्ठा dc_link_settings *link_settings)
अणु
	/* set number of lanes */
	REG_SET(DP_CONFIG, 0,
			DP_UDI_LANES, link_settings->lane_count - LANE_COUNT_ONE);

	/* setup scrambler */
	REG_UPDATE(DP_DPHY_SCRAM_CNTL, DPHY_SCRAMBLER_ADVANCE, 1);
पूर्ण

व्योम dcn10_psr_program_dp_dphy_fast_training(काष्ठा link_encoder *enc,
			bool निकास_link_training_required)
अणु
	काष्ठा dcn10_link_encoder *enc10 = TO_DCN10_LINK_ENC(enc);

	अगर (निकास_link_training_required)
		REG_UPDATE(DP_DPHY_FAST_TRAINING,
				DPHY_RX_FAST_TRAINING_CAPABLE, 1);
	अन्यथा अणु
		REG_UPDATE(DP_DPHY_FAST_TRAINING,
				DPHY_RX_FAST_TRAINING_CAPABLE, 0);
		/*In DCE 11, we are able to pre-program a Force SR रेजिस्टर
		 * to be able to trigger SR symbol after 5 idle patterns
		 * transmitted. Upon PSR Exit, DMCU can trigger
		 * DPHY_LOAD_BS_COUNT_START = 1. Upon writing 1 to
		 * DPHY_LOAD_BS_COUNT_START and the पूर्णांकernal counter
		 * reaches DPHY_LOAD_BS_COUNT, the next BS symbol will be
		 * replaced by SR symbol once.
		 */

		REG_UPDATE(DP_DPHY_BS_SR_SWAP_CNTL, DPHY_LOAD_BS_COUNT, 0x5);
	पूर्ण
पूर्ण

व्योम dcn10_psr_program_secondary_packet(काष्ठा link_encoder *enc,
			अचिन्हित पूर्णांक sdp_transmit_line_num_deadline)
अणु
	काष्ठा dcn10_link_encoder *enc10 = TO_DCN10_LINK_ENC(enc);

	REG_UPDATE_2(DP_SEC_CNTL1,
		DP_SEC_GSP0_LINE_NUM, sdp_transmit_line_num_deadline,
		DP_SEC_GSP0_PRIORITY, 1);
पूर्ण

bool dcn10_is_dig_enabled(काष्ठा link_encoder *enc)
अणु
	काष्ठा dcn10_link_encoder *enc10 = TO_DCN10_LINK_ENC(enc);
	uपूर्णांक32_t value;

	REG_GET(DIG_BE_EN_CNTL, DIG_ENABLE, &value);
	वापस value;
पूर्ण

अटल व्योम link_encoder_disable(काष्ठा dcn10_link_encoder *enc10)
अणु
	/* reset training pattern */
	REG_SET(DP_DPHY_TRAINING_PATTERN_SEL, 0,
			DPHY_TRAINING_PATTERN_SEL, 0);

	/* reset training complete */
	REG_UPDATE(DP_LINK_CNTL, DP_LINK_TRAINING_COMPLETE, 0);

	/* reset panel mode */
	setup_panel_mode(enc10, DP_PANEL_MODE_DEFAULT);
पूर्ण

अटल व्योम hpd_initialize(
	काष्ठा dcn10_link_encoder *enc10)
अणु
	/* Associate HPD with DIG_BE */
	क्रमागत hpd_source_id hpd_source = enc10->base.hpd_source;

	REG_UPDATE(DIG_BE_CNTL, DIG_HPD_SELECT, hpd_source);
पूर्ण

bool dcn10_link_encoder_validate_dvi_output(
	स्थिर काष्ठा dcn10_link_encoder *enc10,
	क्रमागत संकेत_type connector_संकेत,
	क्रमागत संकेत_type संकेत,
	स्थिर काष्ठा dc_crtc_timing *crtc_timing)
अणु
	uपूर्णांक32_t max_pixel_घड़ी = TMDS_MAX_PIXEL_CLOCK;

	अगर (संकेत == SIGNAL_TYPE_DVI_DUAL_LINK)
		max_pixel_घड़ी *= 2;

	/* This handles the हाल of HDMI करोwngrade to DVI we करोn't want to
	 * we करोn't want to cap the pixel घड़ी अगर the DDI is not DVI.
	 */
	अगर (connector_संकेत != SIGNAL_TYPE_DVI_DUAL_LINK &&
			connector_संकेत != SIGNAL_TYPE_DVI_SINGLE_LINK)
		max_pixel_घड़ी = enc10->base.features.max_hdmi_pixel_घड़ी;

	/* DVI only support RGB pixel encoding */
	अगर (crtc_timing->pixel_encoding != PIXEL_ENCODING_RGB)
		वापस false;

	/*connect DVI via adpater's HDMI connector*/
	अगर ((connector_संकेत == SIGNAL_TYPE_DVI_SINGLE_LINK ||
		connector_संकेत == SIGNAL_TYPE_HDMI_TYPE_A) &&
		संकेत != SIGNAL_TYPE_HDMI_TYPE_A &&
		crtc_timing->pix_clk_100hz > (TMDS_MAX_PIXEL_CLOCK * 10))
		वापस false;
	अगर (crtc_timing->pix_clk_100hz < (TMDS_MIN_PIXEL_CLOCK * 10))
		वापस false;

	अगर (crtc_timing->pix_clk_100hz > (max_pixel_घड़ी * 10))
		वापस false;

	/* DVI supports 6/8bpp single-link and 10/16bpp dual-link */
	चयन (crtc_timing->display_color_depth) अणु
	हाल COLOR_DEPTH_666:
	हाल COLOR_DEPTH_888:
	अवरोध;
	हाल COLOR_DEPTH_101010:
	हाल COLOR_DEPTH_161616:
		अगर (संकेत != SIGNAL_TYPE_DVI_DUAL_LINK)
			वापस false;
	अवरोध;
	शेष:
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool dcn10_link_encoder_validate_hdmi_output(
	स्थिर काष्ठा dcn10_link_encoder *enc10,
	स्थिर काष्ठा dc_crtc_timing *crtc_timing,
	स्थिर काष्ठा dc_edid_caps *edid_caps,
	पूर्णांक adjusted_pix_clk_100hz)
अणु
	क्रमागत dc_color_depth max_deep_color =
			enc10->base.features.max_hdmi_deep_color;

	// check pixel घड़ी against edid specअगरied max TMDS clk
	अगर (edid_caps->max_पंचांगds_clk_mhz != 0 &&
			adjusted_pix_clk_100hz > edid_caps->max_पंचांगds_clk_mhz * 10000)
		वापस false;

	अगर (max_deep_color < crtc_timing->display_color_depth)
		वापस false;

	अगर (crtc_timing->display_color_depth < COLOR_DEPTH_888)
		वापस false;
	अगर (adjusted_pix_clk_100hz < (TMDS_MIN_PIXEL_CLOCK * 10))
		वापस false;

	अगर ((adjusted_pix_clk_100hz == 0) ||
		(adjusted_pix_clk_100hz > (enc10->base.features.max_hdmi_pixel_घड़ी * 10)))
		वापस false;

	/* DCE11 HW करोes not support 420 */
	अगर (!enc10->base.features.hdmi_ycbcr420_supported &&
			crtc_timing->pixel_encoding == PIXEL_ENCODING_YCBCR420)
		वापस false;

	अगर (!enc10->base.features.flags.bits.HDMI_6GB_EN &&
		adjusted_pix_clk_100hz >= 3000000)
		वापस false;
	अगर (enc10->base.ctx->dc->debug.hdmi20_disable &&
		crtc_timing->pixel_encoding == PIXEL_ENCODING_YCBCR420)
		वापस false;
	वापस true;
पूर्ण

bool dcn10_link_encoder_validate_dp_output(
	स्थिर काष्ठा dcn10_link_encoder *enc10,
	स्थिर काष्ठा dc_crtc_timing *crtc_timing)
अणु
	अगर (crtc_timing->pixel_encoding == PIXEL_ENCODING_YCBCR420) अणु
		अगर (!enc10->base.features.dp_ycbcr420_supported)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

व्योम dcn10_link_encoder_स्थिरruct(
	काष्ठा dcn10_link_encoder *enc10,
	स्थिर काष्ठा encoder_init_data *init_data,
	स्थिर काष्ठा encoder_feature_support *enc_features,
	स्थिर काष्ठा dcn10_link_enc_रेजिस्टरs *link_regs,
	स्थिर काष्ठा dcn10_link_enc_aux_रेजिस्टरs *aux_regs,
	स्थिर काष्ठा dcn10_link_enc_hpd_रेजिस्टरs *hpd_regs,
	स्थिर काष्ठा dcn10_link_enc_shअगरt *link_shअगरt,
	स्थिर काष्ठा dcn10_link_enc_mask *link_mask)
अणु
	काष्ठा bp_encoder_cap_info bp_cap_info = अणु0पूर्ण;
	स्थिर काष्ठा dc_vbios_funcs *bp_funcs = init_data->ctx->dc_bios->funcs;
	क्रमागत bp_result result = BP_RESULT_OK;

	enc10->base.funcs = &dcn10_lnk_enc_funcs;
	enc10->base.ctx = init_data->ctx;
	enc10->base.id = init_data->encoder;

	enc10->base.hpd_source = init_data->hpd_source;
	enc10->base.connector = init_data->connector;

	enc10->base.preferred_engine = ENGINE_ID_UNKNOWN;

	enc10->base.features = *enc_features;

	enc10->base.transmitter = init_data->transmitter;

	/* set the flag to indicate whether driver poll the I2C data pin
	 * जबतक करोing the DP sink detect
	 */

/*	अगर (dal_adapter_service_is_feature_supported(as,
		FEATURE_DP_SINK_DETECT_POLL_DATA_PIN))
		enc10->base.features.flags.bits.
			DP_SINK_DETECT_POLL_DATA_PIN = true;*/

	enc10->base.output_संकेतs =
		SIGNAL_TYPE_DVI_SINGLE_LINK |
		SIGNAL_TYPE_DVI_DUAL_LINK |
		SIGNAL_TYPE_LVDS |
		SIGNAL_TYPE_DISPLAY_PORT |
		SIGNAL_TYPE_DISPLAY_PORT_MST |
		SIGNAL_TYPE_EDP |
		SIGNAL_TYPE_HDMI_TYPE_A;

	/* For DCE 8.0 and 8.1, by design, UNIPHY is hardwired to DIG_BE.
	 * SW always assign DIG_FE 1:1 mapped to DIG_FE क्रम non-MST UNIPHY.
	 * SW assign DIG_FE to non-MST UNIPHY first and MST last. So prefer
	 * DIG is per UNIPHY and used by SST DP, eDP, HDMI, DVI and LVDS.
	 * Prefer DIG assignment is decided by board design.
	 * For DCE 8.0, there are only max 6 UNIPHYs, we assume board design
	 * and VBIOS will filter out 7 UNIPHY क्रम DCE 8.0.
	 * By this, adding DIGG should not hurt DCE 8.0.
	 * This will let DCE 8.1 share DCE 8.0 as much as possible
	 */

	enc10->link_regs = link_regs;
	enc10->aux_regs = aux_regs;
	enc10->hpd_regs = hpd_regs;
	enc10->link_shअगरt = link_shअगरt;
	enc10->link_mask = link_mask;

	चयन (enc10->base.transmitter) अणु
	हाल TRANSMITTER_UNIPHY_A:
		enc10->base.preferred_engine = ENGINE_ID_DIGA;
	अवरोध;
	हाल TRANSMITTER_UNIPHY_B:
		enc10->base.preferred_engine = ENGINE_ID_DIGB;
	अवरोध;
	हाल TRANSMITTER_UNIPHY_C:
		enc10->base.preferred_engine = ENGINE_ID_DIGC;
	अवरोध;
	हाल TRANSMITTER_UNIPHY_D:
		enc10->base.preferred_engine = ENGINE_ID_DIGD;
	अवरोध;
	हाल TRANSMITTER_UNIPHY_E:
		enc10->base.preferred_engine = ENGINE_ID_DIGE;
	अवरोध;
	हाल TRANSMITTER_UNIPHY_F:
		enc10->base.preferred_engine = ENGINE_ID_DIGF;
	अवरोध;
	हाल TRANSMITTER_UNIPHY_G:
		enc10->base.preferred_engine = ENGINE_ID_DIGG;
	अवरोध;
	शेष:
		ASSERT_CRITICAL(false);
		enc10->base.preferred_engine = ENGINE_ID_UNKNOWN;
	पूर्ण

	/* शेष to one to mirror Winकरोws behavior */
	enc10->base.features.flags.bits.HDMI_6GB_EN = 1;

	result = bp_funcs->get_encoder_cap_info(enc10->base.ctx->dc_bios,
						enc10->base.id, &bp_cap_info);

	/* Override features with DCE-specअगरic values */
	अगर (result == BP_RESULT_OK) अणु
		enc10->base.features.flags.bits.IS_HBR2_CAPABLE =
				bp_cap_info.DP_HBR2_EN;
		enc10->base.features.flags.bits.IS_HBR3_CAPABLE =
				bp_cap_info.DP_HBR3_EN;
		enc10->base.features.flags.bits.HDMI_6GB_EN = bp_cap_info.HDMI_6GB_EN;
		enc10->base.features.flags.bits.DP_IS_USB_C =
				bp_cap_info.DP_IS_USB_C;
	पूर्ण अन्यथा अणु
		DC_LOG_WARNING("%s: Failed to get encoder_cap_info from VBIOS with error code %d!\n",
				__func__,
				result);
	पूर्ण
	अगर (enc10->base.ctx->dc->debug.hdmi20_disable) अणु
		enc10->base.features.flags.bits.HDMI_6GB_EN = 0;
	पूर्ण
पूर्ण

bool dcn10_link_encoder_validate_output_with_stream(
	काष्ठा link_encoder *enc,
	स्थिर काष्ठा dc_stream_state *stream)
अणु
	काष्ठा dcn10_link_encoder *enc10 = TO_DCN10_LINK_ENC(enc);
	bool is_valid;

	//अगर SCDC (340-600MHz) is disabled, set to HDMI 1.4 timing limit
	अगर (stream->sink->edid_caps.panel_patch.skip_scdc_overग_लिखो &&
		enc10->base.features.max_hdmi_pixel_घड़ी > 300000)
		enc10->base.features.max_hdmi_pixel_घड़ी = 300000;

	चयन (stream->संकेत) अणु
	हाल SIGNAL_TYPE_DVI_SINGLE_LINK:
	हाल SIGNAL_TYPE_DVI_DUAL_LINK:
		is_valid = dcn10_link_encoder_validate_dvi_output(
			enc10,
			stream->link->connector_संकेत,
			stream->संकेत,
			&stream->timing);
	अवरोध;
	हाल SIGNAL_TYPE_HDMI_TYPE_A:
		is_valid = dcn10_link_encoder_validate_hdmi_output(
				enc10,
				&stream->timing,
				&stream->sink->edid_caps,
				stream->phy_pix_clk * 10);
	अवरोध;
	हाल SIGNAL_TYPE_DISPLAY_PORT:
	हाल SIGNAL_TYPE_DISPLAY_PORT_MST:
		is_valid = dcn10_link_encoder_validate_dp_output(
					enc10, &stream->timing);
	अवरोध;
	हाल SIGNAL_TYPE_EDP:
		is_valid = (stream->timing.pixel_encoding == PIXEL_ENCODING_RGB) ? true : false;
	अवरोध;
	हाल SIGNAL_TYPE_VIRTUAL:
		is_valid = true;
		अवरोध;
	शेष:
		is_valid = false;
	अवरोध;
	पूर्ण

	वापस is_valid;
पूर्ण

व्योम dcn10_link_encoder_hw_init(
	काष्ठा link_encoder *enc)
अणु
	काष्ठा dcn10_link_encoder *enc10 = TO_DCN10_LINK_ENC(enc);
	काष्ठा bp_transmitter_control cntl = अणु 0 पूर्ण;
	क्रमागत bp_result result;

	cntl.action = TRANSMITTER_CONTROL_INIT;
	cntl.engine_id = ENGINE_ID_UNKNOWN;
	cntl.transmitter = enc10->base.transmitter;
	cntl.connector_obj_id = enc10->base.connector;
	cntl.lanes_number = LANE_COUNT_FOUR;
	cntl.coherent = false;
	cntl.hpd_sel = enc10->base.hpd_source;

	अगर (enc10->base.connector.id == CONNECTOR_ID_EDP)
		cntl.संकेत = SIGNAL_TYPE_EDP;

	result = link_transmitter_control(enc10, &cntl);

	अगर (result != BP_RESULT_OK) अणु
		DC_LOG_ERROR("%s: Failed to execute VBIOS command table!\n",
			__func__);
		BREAK_TO_DEBUGGER();
		वापस;
	पूर्ण

	अगर (enc10->base.connector.id == CONNECTOR_ID_LVDS) अणु
		cntl.action = TRANSMITTER_CONTROL_BACKLIGHT_BRIGHTNESS;

		result = link_transmitter_control(enc10, &cntl);

		ASSERT(result == BP_RESULT_OK);

	पूर्ण
	dcn10_aux_initialize(enc10);

	/* reinitialize HPD.
	 * hpd_initialize() will pass DIG_FE id to HW context.
	 * All other routine within HW context will use fe_engine_offset
	 * as DIG_FE id even caller pass DIG_FE id.
	 * So this routine must be called first.
	 */
	hpd_initialize(enc10);
पूर्ण

व्योम dcn10_link_encoder_destroy(काष्ठा link_encoder **enc)
अणु
	kमुक्त(TO_DCN10_LINK_ENC(*enc));
	*enc = शून्य;
पूर्ण

व्योम dcn10_link_encoder_setup(
	काष्ठा link_encoder *enc,
	क्रमागत संकेत_type संकेत)
अणु
	काष्ठा dcn10_link_encoder *enc10 = TO_DCN10_LINK_ENC(enc);

	चयन (संकेत) अणु
	हाल SIGNAL_TYPE_EDP:
	हाल SIGNAL_TYPE_DISPLAY_PORT:
		/* DP SST */
		REG_UPDATE(DIG_BE_CNTL, DIG_MODE, 0);
		अवरोध;
	हाल SIGNAL_TYPE_LVDS:
		/* LVDS */
		REG_UPDATE(DIG_BE_CNTL, DIG_MODE, 1);
		अवरोध;
	हाल SIGNAL_TYPE_DVI_SINGLE_LINK:
	हाल SIGNAL_TYPE_DVI_DUAL_LINK:
		/* TMDS-DVI */
		REG_UPDATE(DIG_BE_CNTL, DIG_MODE, 2);
		अवरोध;
	हाल SIGNAL_TYPE_HDMI_TYPE_A:
		/* TMDS-HDMI */
		REG_UPDATE(DIG_BE_CNTL, DIG_MODE, 3);
		अवरोध;
	हाल SIGNAL_TYPE_DISPLAY_PORT_MST:
		/* DP MST */
		REG_UPDATE(DIG_BE_CNTL, DIG_MODE, 5);
		अवरोध;
	शेष:
		ASSERT_CRITICAL(false);
		/* invalid mode ! */
		अवरोध;
	पूर्ण

पूर्ण

/* TODO: still need depth or just pass in adjusted pixel घड़ी? */
व्योम dcn10_link_encoder_enable_पंचांगds_output(
	काष्ठा link_encoder *enc,
	क्रमागत घड़ी_source_id घड़ी_source,
	क्रमागत dc_color_depth color_depth,
	क्रमागत संकेत_type संकेत,
	uपूर्णांक32_t pixel_घड़ी)
अणु
	काष्ठा dcn10_link_encoder *enc10 = TO_DCN10_LINK_ENC(enc);
	काष्ठा bp_transmitter_control cntl = अणु 0 पूर्ण;
	क्रमागत bp_result result;

	/* Enable the PHY */

	cntl.action = TRANSMITTER_CONTROL_ENABLE;
	cntl.engine_id = enc->preferred_engine;
	cntl.transmitter = enc10->base.transmitter;
	cntl.pll_id = घड़ी_source;
	cntl.संकेत = संकेत;
	अगर (cntl.संकेत == SIGNAL_TYPE_DVI_DUAL_LINK)
		cntl.lanes_number = 8;
	अन्यथा
		cntl.lanes_number = 4;

	cntl.hpd_sel = enc10->base.hpd_source;

	cntl.pixel_घड़ी = pixel_घड़ी;
	cntl.color_depth = color_depth;

	result = link_transmitter_control(enc10, &cntl);

	अगर (result != BP_RESULT_OK) अणु
		DC_LOG_ERROR("%s: Failed to execute VBIOS command table!\n",
			__func__);
		BREAK_TO_DEBUGGER();
	पूर्ण
पूर्ण

व्योम dcn10_link_encoder_enable_पंचांगds_output_with_clk_pattern_wa(
	काष्ठा link_encoder *enc,
	क्रमागत घड़ी_source_id घड़ी_source,
	क्रमागत dc_color_depth color_depth,
	क्रमागत संकेत_type संकेत,
	uपूर्णांक32_t pixel_घड़ी)
अणु
	काष्ठा dcn10_link_encoder *enc10 = TO_DCN10_LINK_ENC(enc);

	dcn10_link_encoder_enable_पंचांगds_output(
		enc, घड़ी_source, color_depth, संकेत, pixel_घड़ी);

	REG_UPDATE(DIG_CLOCK_PATTERN, DIG_CLOCK_PATTERN, 0x1F);
पूर्ण

/* enables DP PHY output */
व्योम dcn10_link_encoder_enable_dp_output(
	काष्ठा link_encoder *enc,
	स्थिर काष्ठा dc_link_settings *link_settings,
	क्रमागत घड़ी_source_id घड़ी_source)
अणु
	काष्ठा dcn10_link_encoder *enc10 = TO_DCN10_LINK_ENC(enc);
	काष्ठा bp_transmitter_control cntl = अणु 0 पूर्ण;
	क्रमागत bp_result result;

	/* Enable the PHY */

	/* number_of_lanes is used क्रम pixel घड़ी adjust,
	 * but it's not passed to asic_control.
	 * We need to set number of lanes manually.
	 */
	enc1_configure_encoder(enc10, link_settings);

	cntl.action = TRANSMITTER_CONTROL_ENABLE;
	cntl.engine_id = enc->preferred_engine;
	cntl.transmitter = enc10->base.transmitter;
	cntl.pll_id = घड़ी_source;
	cntl.संकेत = SIGNAL_TYPE_DISPLAY_PORT;
	cntl.lanes_number = link_settings->lane_count;
	cntl.hpd_sel = enc10->base.hpd_source;
	cntl.pixel_घड़ी = link_settings->link_rate
						* LINK_RATE_REF_FREQ_IN_KHZ;
	/* TODO: check अगर undefined works */
	cntl.color_depth = COLOR_DEPTH_UNDEFINED;

	result = link_transmitter_control(enc10, &cntl);

	अगर (result != BP_RESULT_OK) अणु
		DC_LOG_ERROR("%s: Failed to execute VBIOS command table!\n",
			__func__);
		BREAK_TO_DEBUGGER();
	पूर्ण
पूर्ण

/* enables DP PHY output in MST mode */
व्योम dcn10_link_encoder_enable_dp_mst_output(
	काष्ठा link_encoder *enc,
	स्थिर काष्ठा dc_link_settings *link_settings,
	क्रमागत घड़ी_source_id घड़ी_source)
अणु
	काष्ठा dcn10_link_encoder *enc10 = TO_DCN10_LINK_ENC(enc);
	काष्ठा bp_transmitter_control cntl = अणु 0 पूर्ण;
	क्रमागत bp_result result;

	/* Enable the PHY */

	/* number_of_lanes is used क्रम pixel घड़ी adjust,
	 * but it's not passed to asic_control.
	 * We need to set number of lanes manually.
	 */
	enc1_configure_encoder(enc10, link_settings);

	cntl.action = TRANSMITTER_CONTROL_ENABLE;
	cntl.engine_id = ENGINE_ID_UNKNOWN;
	cntl.transmitter = enc10->base.transmitter;
	cntl.pll_id = घड़ी_source;
	cntl.संकेत = SIGNAL_TYPE_DISPLAY_PORT_MST;
	cntl.lanes_number = link_settings->lane_count;
	cntl.hpd_sel = enc10->base.hpd_source;
	cntl.pixel_घड़ी = link_settings->link_rate
						* LINK_RATE_REF_FREQ_IN_KHZ;
	/* TODO: check अगर undefined works */
	cntl.color_depth = COLOR_DEPTH_UNDEFINED;

	result = link_transmitter_control(enc10, &cntl);

	अगर (result != BP_RESULT_OK) अणु
		DC_LOG_ERROR("%s: Failed to execute VBIOS command table!\n",
			__func__);
		BREAK_TO_DEBUGGER();
	पूर्ण
पूर्ण
/*
 * @brief
 * Disable transmitter and its encoder
 */
व्योम dcn10_link_encoder_disable_output(
	काष्ठा link_encoder *enc,
	क्रमागत संकेत_type संकेत)
अणु
	काष्ठा dcn10_link_encoder *enc10 = TO_DCN10_LINK_ENC(enc);
	काष्ठा bp_transmitter_control cntl = अणु 0 पूर्ण;
	क्रमागत bp_result result;

	अगर (!dcn10_is_dig_enabled(enc)) अणु
		/* OF_SKIP_POWER_DOWN_INACTIVE_ENCODER */
	/*in DP_Alt_No_Connect हाल, we turn off the dig alपढ़ोy,
	after excuation the PHY w/a sequence, not allow touch PHY any more*/
		वापस;
	पूर्ण
	/* Power-करोwn RX and disable GPU PHY should be paired.
	 * Disabling PHY without घातering करोwn RX may cause
	 * symbol lock loss, on which we will get DP Sink पूर्णांकerrupt.
	 */

	/* There is a हाल क्रम the DP active करोngles
	 * where we want to disable the PHY but keep RX घातered,
	 * क्रम those we need to ignore DP Sink पूर्णांकerrupt
	 * by checking lane count that has been set
	 * on the last करो_enable_output().
	 */

	/* disable transmitter */
	cntl.action = TRANSMITTER_CONTROL_DISABLE;
	cntl.transmitter = enc10->base.transmitter;
	cntl.hpd_sel = enc10->base.hpd_source;
	cntl.संकेत = संकेत;
	cntl.connector_obj_id = enc10->base.connector;

	result = link_transmitter_control(enc10, &cntl);

	अगर (result != BP_RESULT_OK) अणु
		DC_LOG_ERROR("%s: Failed to execute VBIOS command table!\n",
			__func__);
		BREAK_TO_DEBUGGER();
		वापस;
	पूर्ण

	/* disable encoder */
	अगर (dc_is_dp_संकेत(संकेत))
		link_encoder_disable(enc10);
पूर्ण

व्योम dcn10_link_encoder_dp_set_lane_settings(
	काष्ठा link_encoder *enc,
	स्थिर काष्ठा link_training_settings *link_settings)
अणु
	काष्ठा dcn10_link_encoder *enc10 = TO_DCN10_LINK_ENC(enc);
	जोड़ dpcd_training_lane_set training_lane_set = अणु अणु 0 पूर्ण पूर्ण;
	पूर्णांक32_t lane = 0;
	काष्ठा bp_transmitter_control cntl = अणु 0 पूर्ण;

	अगर (!link_settings) अणु
		BREAK_TO_DEBUGGER();
		वापस;
	पूर्ण

	cntl.action = TRANSMITTER_CONTROL_SET_VOLTAGE_AND_PREEMPASIS;
	cntl.transmitter = enc10->base.transmitter;
	cntl.connector_obj_id = enc10->base.connector;
	cntl.lanes_number = link_settings->link_settings.lane_count;
	cntl.hpd_sel = enc10->base.hpd_source;
	cntl.pixel_घड़ी = link_settings->link_settings.link_rate *
						LINK_RATE_REF_FREQ_IN_KHZ;

	क्रम (lane = 0; lane < link_settings->link_settings.lane_count; lane++) अणु
		/* translate lane settings */

		training_lane_set.bits.VOLTAGE_SWING_SET =
			link_settings->lane_settings[lane].VOLTAGE_SWING;
		training_lane_set.bits.PRE_EMPHASIS_SET =
			link_settings->lane_settings[lane].PRE_EMPHASIS;

		/* post cursor 2 setting only applies to HBR2 link rate */
		अगर (link_settings->link_settings.link_rate == LINK_RATE_HIGH2) अणु
			/* this is passed to VBIOS
			 * to program post cursor 2 level
			 */
			training_lane_set.bits.POST_CURSOR2_SET =
				link_settings->lane_settings[lane].POST_CURSOR2;
		पूर्ण

		cntl.lane_select = lane;
		cntl.lane_settings = training_lane_set.raw;

		/* call VBIOS table to set voltage swing and pre-emphasis */
		link_transmitter_control(enc10, &cntl);
	पूर्ण
पूर्ण

/* set DP PHY test and training patterns */
व्योम dcn10_link_encoder_dp_set_phy_pattern(
	काष्ठा link_encoder *enc,
	स्थिर काष्ठा encoder_set_dp_phy_pattern_param *param)
अणु
	काष्ठा dcn10_link_encoder *enc10 = TO_DCN10_LINK_ENC(enc);

	चयन (param->dp_phy_pattern) अणु
	हाल DP_TEST_PATTERN_TRAINING_PATTERN1:
		dcn10_link_encoder_set_dp_phy_pattern_training_pattern(enc, 0);
		अवरोध;
	हाल DP_TEST_PATTERN_TRAINING_PATTERN2:
		dcn10_link_encoder_set_dp_phy_pattern_training_pattern(enc, 1);
		अवरोध;
	हाल DP_TEST_PATTERN_TRAINING_PATTERN3:
		dcn10_link_encoder_set_dp_phy_pattern_training_pattern(enc, 2);
		अवरोध;
	हाल DP_TEST_PATTERN_TRAINING_PATTERN4:
		dcn10_link_encoder_set_dp_phy_pattern_training_pattern(enc, 3);
		अवरोध;
	हाल DP_TEST_PATTERN_D102:
		set_dp_phy_pattern_d102(enc10);
		अवरोध;
	हाल DP_TEST_PATTERN_SYMBOL_ERROR:
		set_dp_phy_pattern_symbol_error(enc10);
		अवरोध;
	हाल DP_TEST_PATTERN_PRBS7:
		set_dp_phy_pattern_prbs7(enc10);
		अवरोध;
	हाल DP_TEST_PATTERN_80BIT_CUSTOM:
		set_dp_phy_pattern_80bit_custom(
			enc10, param->custom_pattern);
		अवरोध;
	हाल DP_TEST_PATTERN_CP2520_1:
		set_dp_phy_pattern_hbr2_compliance_cp2520_2(enc10, 1);
		अवरोध;
	हाल DP_TEST_PATTERN_CP2520_2:
		set_dp_phy_pattern_hbr2_compliance_cp2520_2(enc10, 2);
		अवरोध;
	हाल DP_TEST_PATTERN_CP2520_3:
		set_dp_phy_pattern_hbr2_compliance_cp2520_2(enc10, 3);
		अवरोध;
	हाल DP_TEST_PATTERN_VIDEO_MODE: अणु
		set_dp_phy_pattern_passthrough_mode(
			enc10, param->dp_panel_mode);
		अवरोध;
	पूर्ण

	शेष:
		/* invalid phy pattern */
		ASSERT_CRITICAL(false);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम fill_stream_allocation_row_info(
	स्थिर काष्ठा link_mst_stream_allocation *stream_allocation,
	uपूर्णांक32_t *src,
	uपूर्णांक32_t *slots)
अणु
	स्थिर काष्ठा stream_encoder *stream_enc = stream_allocation->stream_enc;

	अगर (stream_enc) अणु
		*src = stream_enc->id;
		*slots = stream_allocation->slot_count;
	पूर्ण अन्यथा अणु
		*src = 0;
		*slots = 0;
	पूर्ण
पूर्ण

/* programs DP MST VC payload allocation */
व्योम dcn10_link_encoder_update_mst_stream_allocation_table(
	काष्ठा link_encoder *enc,
	स्थिर काष्ठा link_mst_stream_allocation_table *table)
अणु
	काष्ठा dcn10_link_encoder *enc10 = TO_DCN10_LINK_ENC(enc);
	uपूर्णांक32_t value0 = 0;
	uपूर्णांक32_t value1 = 0;
	uपूर्णांक32_t value2 = 0;
	uपूर्णांक32_t slots = 0;
	uपूर्णांक32_t src = 0;
	uपूर्णांक32_t retries = 0;

	/* For CZ, there are only 3 pipes. So Virtual channel is up 3.*/

	/* --- Set MSE Stream Attribute -
	 * Setup VC Payload Table on Tx Side,
	 * Issue allocation change trigger
	 * to commit payload on both tx and rx side
	 */

	/* we should clean-up table each समय */

	अगर (table->stream_count >= 1) अणु
		fill_stream_allocation_row_info(
			&table->stream_allocations[0],
			&src,
			&slots);
	पूर्ण अन्यथा अणु
		src = 0;
		slots = 0;
	पूर्ण

	REG_UPDATE_2(DP_MSE_SAT0,
			DP_MSE_SAT_SRC0, src,
			DP_MSE_SAT_SLOT_COUNT0, slots);

	अगर (table->stream_count >= 2) अणु
		fill_stream_allocation_row_info(
			&table->stream_allocations[1],
			&src,
			&slots);
	पूर्ण अन्यथा अणु
		src = 0;
		slots = 0;
	पूर्ण

	REG_UPDATE_2(DP_MSE_SAT0,
			DP_MSE_SAT_SRC1, src,
			DP_MSE_SAT_SLOT_COUNT1, slots);

	अगर (table->stream_count >= 3) अणु
		fill_stream_allocation_row_info(
			&table->stream_allocations[2],
			&src,
			&slots);
	पूर्ण अन्यथा अणु
		src = 0;
		slots = 0;
	पूर्ण

	REG_UPDATE_2(DP_MSE_SAT1,
			DP_MSE_SAT_SRC2, src,
			DP_MSE_SAT_SLOT_COUNT2, slots);

	अगर (table->stream_count >= 4) अणु
		fill_stream_allocation_row_info(
			&table->stream_allocations[3],
			&src,
			&slots);
	पूर्ण अन्यथा अणु
		src = 0;
		slots = 0;
	पूर्ण

	REG_UPDATE_2(DP_MSE_SAT1,
			DP_MSE_SAT_SRC3, src,
			DP_MSE_SAT_SLOT_COUNT3, slots);

	/* --- रुको क्रम transaction finish */

	/* send allocation change trigger (ACT) ?
	 * this step first sends the ACT,
	 * then द्विगुन buffers the SAT पूर्णांकo the hardware
	 * making the new allocation active on the DP MST mode link
	 */

	/* DP_MSE_SAT_UPDATE:
	 * 0 - No Action
	 * 1 - Update SAT with trigger
	 * 2 - Update SAT without trigger
	 */
	REG_UPDATE(DP_MSE_SAT_UPDATE,
			DP_MSE_SAT_UPDATE, 1);

	/* रुको क्रम update to complete
	 * (i.e. DP_MSE_SAT_UPDATE field is reset to 0)
	 * then रुको क्रम the transmission
	 * of at least 16 MTP headers on immediate local link.
	 * i.e. DP_MSE_16_MTP_KEEPOUT field (पढ़ो only) is reset to 0
	 * a value of 1 indicates that DP MST mode
	 * is in the 16 MTP keepout region after a VC has been added.
	 * MST stream bandwidth (VC rate) can be configured
	 * after this bit is cleared
	 */
	करो अणु
		udelay(10);

		value0 = REG_READ(DP_MSE_SAT_UPDATE);

		REG_GET(DP_MSE_SAT_UPDATE,
				DP_MSE_SAT_UPDATE, &value1);

		REG_GET(DP_MSE_SAT_UPDATE,
				DP_MSE_16_MTP_KEEPOUT, &value2);

		/* bit field DP_MSE_SAT_UPDATE is set to 1 alपढ़ोy */
		अगर (!value1 && !value2)
			अवरोध;
		++retries;
	पूर्ण जबतक (retries < DP_MST_UPDATE_MAX_RETRY);
पूर्ण

व्योम dcn10_link_encoder_connect_dig_be_to_fe(
	काष्ठा link_encoder *enc,
	क्रमागत engine_id engine,
	bool connect)
अणु
	काष्ठा dcn10_link_encoder *enc10 = TO_DCN10_LINK_ENC(enc);
	uपूर्णांक32_t field;

	अगर (engine != ENGINE_ID_UNKNOWN) अणु

		REG_GET(DIG_BE_CNTL, DIG_FE_SOURCE_SELECT, &field);

		अगर (connect)
			field |= get_frontend_source(engine);
		अन्यथा
			field &= ~get_frontend_source(engine);

		REG_UPDATE(DIG_BE_CNTL, DIG_FE_SOURCE_SELECT, field);
	पूर्ण
पूर्ण


#घोषणा HPD_REG(reg)\
	(enc10->hpd_regs->reg)

#घोषणा HPD_REG_READ(reg_name) \
		dm_पढ़ो_reg(CTX, HPD_REG(reg_name))

#घोषणा HPD_REG_UPDATE_N(reg_name, n, ...)	\
		generic_reg_update_ex(CTX, \
				HPD_REG(reg_name), \
				n, __VA_ARGS__)

#घोषणा HPD_REG_UPDATE(reg_name, field, val)	\
		HPD_REG_UPDATE_N(reg_name, 1, \
				FN(reg_name, field), val)

व्योम dcn10_link_encoder_enable_hpd(काष्ठा link_encoder *enc)
अणु
	काष्ठा dcn10_link_encoder *enc10 = TO_DCN10_LINK_ENC(enc);

	HPD_REG_UPDATE(DC_HPD_CONTROL,
			DC_HPD_EN, 1);
पूर्ण

व्योम dcn10_link_encoder_disable_hpd(काष्ठा link_encoder *enc)
अणु
	काष्ठा dcn10_link_encoder *enc10 = TO_DCN10_LINK_ENC(enc);

	HPD_REG_UPDATE(DC_HPD_CONTROL,
			DC_HPD_EN, 0);
पूर्ण

#घोषणा AUX_REG(reg)\
	(enc10->aux_regs->reg)

#घोषणा AUX_REG_READ(reg_name) \
		dm_पढ़ो_reg(CTX, AUX_REG(reg_name))

#घोषणा AUX_REG_UPDATE_N(reg_name, n, ...)	\
		generic_reg_update_ex(CTX, \
				AUX_REG(reg_name), \
				n, __VA_ARGS__)

#घोषणा AUX_REG_UPDATE(reg_name, field, val)	\
		AUX_REG_UPDATE_N(reg_name, 1, \
				FN(reg_name, field), val)

#घोषणा AUX_REG_UPDATE_2(reg, f1, v1, f2, v2)	\
		AUX_REG_UPDATE_N(reg, 2,\
				FN(reg, f1), v1,\
				FN(reg, f2), v2)

व्योम dcn10_aux_initialize(काष्ठा dcn10_link_encoder *enc10)
अणु
	क्रमागत hpd_source_id hpd_source = enc10->base.hpd_source;

	AUX_REG_UPDATE_2(AUX_CONTROL,
			AUX_HPD_SEL, hpd_source,
			AUX_LS_READ_EN, 0);

	/* 1/4 winकरोw (the maximum allowed) */
	AUX_REG_UPDATE(AUX_DPHY_RX_CONTROL0,
			AUX_RX_RECEIVE_WINDOW, 0);
पूर्ण

क्रमागत संकेत_type dcn10_get_dig_mode(
	काष्ठा link_encoder *enc)
अणु
	काष्ठा dcn10_link_encoder *enc10 = TO_DCN10_LINK_ENC(enc);
	uपूर्णांक32_t value;
	REG_GET(DIG_BE_CNTL, DIG_MODE, &value);
	चयन (value) अणु
	हाल 1:
		वापस SIGNAL_TYPE_DISPLAY_PORT;
	हाल 2:
		वापस SIGNAL_TYPE_DVI_SINGLE_LINK;
	हाल 3:
		वापस SIGNAL_TYPE_HDMI_TYPE_A;
	हाल 5:
		वापस SIGNAL_TYPE_DISPLAY_PORT_MST;
	शेष:
		वापस SIGNAL_TYPE_NONE;
	पूर्ण
	वापस SIGNAL_TYPE_NONE;
पूर्ण

व्योम dcn10_link_encoder_get_max_link_cap(काष्ठा link_encoder *enc,
	काष्ठा dc_link_settings *link_settings)
अणु
	/* Set Default link settings */
	काष्ठा dc_link_settings max_link_cap = अणुLANE_COUNT_FOUR, LINK_RATE_HIGH,
			LINK_SPREAD_05_DOWNSPREAD_30KHZ, false, 0पूर्ण;

	/* Higher link settings based on feature supported */
	अगर (enc->features.flags.bits.IS_HBR2_CAPABLE)
		max_link_cap.link_rate = LINK_RATE_HIGH2;

	अगर (enc->features.flags.bits.IS_HBR3_CAPABLE)
		max_link_cap.link_rate = LINK_RATE_HIGH3;

	*link_settings = max_link_cap;
पूर्ण
