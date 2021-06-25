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

#समावेश "reg_helper.h"

#समावेश <linux/delay.h>
#समावेश "core_types.h"
#समावेश "link_encoder.h"
#समावेश "dcn21_link_encoder.h"
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

#घोषणा IND_REG(index) \
	(enc10->link_regs->index)

अटल काष्ठा mpll_cfg dcn21_mpll_cfg_ref[] = अणु
	// RBR
	अणु
		.hdmimode_enable = 0,
		.ref_range = 1,
		.ref_clk_mpllb_भाग = 1,
		.mpllb_ssc_en = 1,
		.mpllb_भाग5_clk_en = 1,
		.mpllb_multiplier = 238,
		.mpllb_fracn_en = 0,
		.mpllb_fracn_quot = 0,
		.mpllb_fracn_rem = 0,
		.mpllb_fracn_den = 1,
		.mpllb_ssc_up_spपढ़ो = 0,
		.mpllb_ssc_peak = 44237,
		.mpllb_ssc_stepsize = 59454,
		.mpllb_भाग_clk_en = 0,
		.mpllb_भाग_multiplier = 0,
		.mpllb_hdmi_भाग = 0,
		.mpllb_tx_clk_भाग = 2,
		.tx_vboost_lvl = 5,
		.mpllb_pmix_en = 1,
		.mpllb_word_भाग2_en = 0,
		.mpllb_ana_v2i = 2,
		.mpllb_ana_freq_vco = 2,
		.mpllb_ana_cp_पूर्णांक = 9,
		.mpllb_ana_cp_prop = 15,
		.hdmi_pixel_clk_भाग = 0,
	पूर्ण,
	// HBR
	अणु
		.hdmimode_enable = 0,
		.ref_range = 1,
		.ref_clk_mpllb_भाग = 1,
		.mpllb_ssc_en = 1,
		.mpllb_भाग5_clk_en = 1,
		.mpllb_multiplier = 192,
		.mpllb_fracn_en = 1,
		.mpllb_fracn_quot = 32768,
		.mpllb_fracn_rem = 0,
		.mpllb_fracn_den = 1,
		.mpllb_ssc_up_spपढ़ो = 0,
		.mpllb_ssc_peak = 36864,
		.mpllb_ssc_stepsize = 49545,
		.mpllb_भाग_clk_en = 0,
		.mpllb_भाग_multiplier = 0,
		.mpllb_hdmi_भाग = 0,
		.mpllb_tx_clk_भाग = 1,
		.tx_vboost_lvl = 5,
		.mpllb_pmix_en = 1,
		.mpllb_word_भाग2_en = 0,
		.mpllb_ana_v2i = 2,
		.mpllb_ana_freq_vco = 3,
		.mpllb_ana_cp_पूर्णांक = 9,
		.mpllb_ana_cp_prop = 15,
		.hdmi_pixel_clk_भाग = 0,
	पूर्ण,
	//HBR2
	अणु
		.hdmimode_enable = 0,
		.ref_range = 1,
		.ref_clk_mpllb_भाग = 1,
		.mpllb_ssc_en = 1,
		.mpllb_भाग5_clk_en = 1,
		.mpllb_multiplier = 192,
		.mpllb_fracn_en = 1,
		.mpllb_fracn_quot = 32768,
		.mpllb_fracn_rem = 0,
		.mpllb_fracn_den = 1,
		.mpllb_ssc_up_spपढ़ो = 0,
		.mpllb_ssc_peak = 36864,
		.mpllb_ssc_stepsize = 49545,
		.mpllb_भाग_clk_en = 0,
		.mpllb_भाग_multiplier = 0,
		.mpllb_hdmi_भाग = 0,
		.mpllb_tx_clk_भाग = 0,
		.tx_vboost_lvl = 5,
		.mpllb_pmix_en = 1,
		.mpllb_word_भाग2_en = 0,
		.mpllb_ana_v2i = 2,
		.mpllb_ana_freq_vco = 3,
		.mpllb_ana_cp_पूर्णांक = 9,
		.mpllb_ana_cp_prop = 15,
		.hdmi_pixel_clk_भाग = 0,
	पूर्ण,
	//HBR3
	अणु
		.hdmimode_enable = 0,
		.ref_range = 1,
		.ref_clk_mpllb_भाग = 1,
		.mpllb_ssc_en = 1,
		.mpllb_भाग5_clk_en = 1,
		.mpllb_multiplier = 304,
		.mpllb_fracn_en = 1,
		.mpllb_fracn_quot = 49152,
		.mpllb_fracn_rem = 0,
		.mpllb_fracn_den = 1,
		.mpllb_ssc_up_spपढ़ो = 0,
		.mpllb_ssc_peak = 55296,
		.mpllb_ssc_stepsize = 74318,
		.mpllb_भाग_clk_en = 0,
		.mpllb_भाग_multiplier = 0,
		.mpllb_hdmi_भाग = 0,
		.mpllb_tx_clk_भाग = 0,
		.tx_vboost_lvl = 5,
		.mpllb_pmix_en = 1,
		.mpllb_word_भाग2_en = 0,
		.mpllb_ana_v2i = 2,
		.mpllb_ana_freq_vco = 1,
		.mpllb_ana_cp_पूर्णांक = 7,
		.mpllb_ana_cp_prop = 16,
		.hdmi_pixel_clk_भाग = 0,
	पूर्ण,
पूर्ण;


अटल bool update_cfg_data(
		काष्ठा dcn10_link_encoder *enc10,
		स्थिर काष्ठा dc_link_settings *link_settings,
		काष्ठा dpcssys_phy_seq_cfg *cfg)
अणु
	पूर्णांक i;

	cfg->load_sram_fw = false;
	cfg->use_calibration_setting = true;

	//TODO: need to implement a proper lane mapping क्रम Renoir.
	क्रम (i = 0; i < 4; i++)
		cfg->lane_en[i] = true;

	चयन (link_settings->link_rate) अणु
	हाल LINK_RATE_LOW:
		cfg->mpll_cfg = dcn21_mpll_cfg_ref[0];
		अवरोध;
	हाल LINK_RATE_HIGH:
		cfg->mpll_cfg = dcn21_mpll_cfg_ref[1];
		अवरोध;
	हाल LINK_RATE_HIGH2:
		cfg->mpll_cfg = dcn21_mpll_cfg_ref[2];
		अवरोध;
	हाल LINK_RATE_HIGH3:
		cfg->mpll_cfg = dcn21_mpll_cfg_ref[3];
		अवरोध;
	शेष:
		DC_LOG_ERROR("%s: No supported link rate found %X!\n",
				__func__, link_settings->link_rate);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

bool dcn21_link_encoder_acquire_phy(काष्ठा link_encoder *enc)
अणु
	काष्ठा dcn10_link_encoder *enc10 = TO_DCN10_LINK_ENC(enc);
	पूर्णांक value;

	अगर (enc->features.flags.bits.DP_IS_USB_C) अणु
		REG_GET(RDPCSTX_PHY_CNTL6,
				RDPCS_PHY_DPALT_DISABLE, &value);

		अगर (value == 1) अणु
			ASSERT(0);
			वापस false;
		पूर्ण
		REG_UPDATE(RDPCSTX_PHY_CNTL6,
				RDPCS_PHY_DPALT_DISABLE_ACK, 0);

		udelay(40);

		REG_GET(RDPCSTX_PHY_CNTL6,
						RDPCS_PHY_DPALT_DISABLE, &value);
		अगर (value == 1) अणु
			ASSERT(0);
			REG_UPDATE(RDPCSTX_PHY_CNTL6,
					RDPCS_PHY_DPALT_DISABLE_ACK, 1);
			वापस false;
		पूर्ण
	पूर्ण

	REG_UPDATE(RDPCSTX_PHY_CNTL6, RDPCS_PHY_DP_REF_CLK_EN, 1);

	वापस true;
पूर्ण



अटल व्योम dcn21_link_encoder_release_phy(काष्ठा link_encoder *enc)
अणु
	काष्ठा dcn10_link_encoder *enc10 = TO_DCN10_LINK_ENC(enc);

	अगर (enc->features.flags.bits.DP_IS_USB_C) अणु
		REG_UPDATE(RDPCSTX_PHY_CNTL6,
				RDPCS_PHY_DPALT_DISABLE_ACK, 1);
	पूर्ण

	REG_UPDATE(RDPCSTX_PHY_CNTL6, RDPCS_PHY_DP_REF_CLK_EN, 0);

पूर्ण

व्योम dcn21_link_encoder_enable_dp_output(
	काष्ठा link_encoder *enc,
	स्थिर काष्ठा dc_link_settings *link_settings,
	क्रमागत घड़ी_source_id घड़ी_source)
अणु
	काष्ठा dcn10_link_encoder *enc10 = TO_DCN10_LINK_ENC(enc);
	काष्ठा dcn21_link_encoder *enc21 = (काष्ठा dcn21_link_encoder *) enc10;
	काष्ठा dpcssys_phy_seq_cfg *cfg = &enc21->phy_seq_cfg;

	अगर (!dcn21_link_encoder_acquire_phy(enc))
		वापस;

	अगर (!enc->ctx->dc->debug.aव्योम_vbios_exec_table) अणु
		dcn10_link_encoder_enable_dp_output(enc, link_settings, घड़ी_source);
		वापस;
	पूर्ण

	अगर (!update_cfg_data(enc10, link_settings, cfg))
		वापस;

	enc1_configure_encoder(enc10, link_settings);

	dcn10_link_encoder_setup(enc, SIGNAL_TYPE_DISPLAY_PORT);

पूर्ण

व्योम dcn21_link_encoder_enable_dp_mst_output(
	काष्ठा link_encoder *enc,
	स्थिर काष्ठा dc_link_settings *link_settings,
	क्रमागत घड़ी_source_id घड़ी_source)
अणु
	अगर (!dcn21_link_encoder_acquire_phy(enc))
		वापस;

	dcn10_link_encoder_enable_dp_mst_output(enc, link_settings, घड़ी_source);
पूर्ण

व्योम dcn21_link_encoder_disable_output(
	काष्ठा link_encoder *enc,
	क्रमागत संकेत_type संकेत)
अणु
	dcn10_link_encoder_disable_output(enc, संकेत);

	अगर (dc_is_dp_संकेत(संकेत))
		dcn21_link_encoder_release_phy(enc);
पूर्ण


अटल स्थिर काष्ठा link_encoder_funcs dcn21_link_enc_funcs = अणु
	.पढ़ो_state = link_enc2_पढ़ो_state,
	.validate_output_with_stream =
		dcn10_link_encoder_validate_output_with_stream,
	.hw_init = enc2_hw_init,
	.setup = dcn10_link_encoder_setup,
	.enable_पंचांगds_output = dcn10_link_encoder_enable_पंचांगds_output,
	.enable_dp_output = dcn21_link_encoder_enable_dp_output,
	.enable_dp_mst_output = dcn21_link_encoder_enable_dp_mst_output,
	.disable_output = dcn21_link_encoder_disable_output,
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
	.destroy = dcn10_link_encoder_destroy,
	.fec_set_enable = enc2_fec_set_enable,
	.fec_set_पढ़ोy = enc2_fec_set_पढ़ोy,
	.fec_is_active = enc2_fec_is_active,
	.get_dig_frontend = dcn10_get_dig_frontend,
	.is_in_alt_mode = dcn20_link_encoder_is_in_alt_mode,
	.get_max_link_cap = dcn20_link_encoder_get_max_link_cap,
पूर्ण;

व्योम dcn21_link_encoder_स्थिरruct(
	काष्ठा dcn21_link_encoder *enc21,
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
	काष्ठा dcn10_link_encoder *enc10 = &enc21->enc10;

	enc10->base.funcs = &dcn21_link_enc_funcs;
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
