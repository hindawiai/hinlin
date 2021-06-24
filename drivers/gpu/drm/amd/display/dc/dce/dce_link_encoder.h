<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the
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

#अगर_अघोषित __DC_LINK_ENCODER__DCE110_H__
#घोषणा __DC_LINK_ENCODER__DCE110_H__

#समावेश "link_encoder.h"

#घोषणा TO_DCE110_LINK_ENC(link_encoder)\
	container_of(link_encoder, काष्ठा dce110_link_encoder, base)

/* Not found regs in dce120 spec
 * BIOS_SCRATCH_2
 * DP_DPHY_INTERNAL_CTRL
 */

#घोषणा AUX_REG_LIST(id)\
	SRI(AUX_CONTROL, DP_AUX, id), \
	SRI(AUX_DPHY_RX_CONTROL0, DP_AUX, id), \
	SRI(AUX_DPHY_RX_CONTROL1, DP_AUX, id)

#घोषणा HPD_REG_LIST(id)\
	SRI(DC_HPD_CONTROL, HPD, id)

#घोषणा LE_COMMON_REG_LIST_BASE(id) \
	SR(DMCU_RAM_ACCESS_CTRL), \
	SR(DMCU_IRAM_RD_CTRL), \
	SR(DMCU_IRAM_RD_DATA), \
	SR(DMCU_INTERRUPT_TO_UC_EN_MASK), \
	SRI(DIG_BE_CNTL, DIG, id), \
	SRI(DIG_BE_EN_CNTL, DIG, id), \
	SRI(DP_CONFIG, DP, id), \
	SRI(DP_DPHY_CNTL, DP, id), \
	SRI(DP_DPHY_PRBS_CNTL, DP, id), \
	SRI(DP_DPHY_SCRAM_CNTL, DP, id),\
	SRI(DP_DPHY_SYM0, DP, id), \
	SRI(DP_DPHY_SYM1, DP, id), \
	SRI(DP_DPHY_SYM2, DP, id), \
	SRI(DP_DPHY_TRAINING_PATTERN_SEL, DP, id), \
	SRI(DP_LINK_CNTL, DP, id), \
	SRI(DP_LINK_FRAMING_CNTL, DP, id), \
	SRI(DP_MSE_SAT0, DP, id), \
	SRI(DP_MSE_SAT1, DP, id), \
	SRI(DP_MSE_SAT2, DP, id), \
	SRI(DP_MSE_SAT_UPDATE, DP, id), \
	SRI(DP_SEC_CNTL, DP, id), \
	SRI(DP_VID_STREAM_CNTL, DP, id), \
	SRI(DP_DPHY_FAST_TRAINING, DP, id), \
	SRI(DP_SEC_CNTL1, DP, id)

#घोषणा LE_COMMON_REG_LIST(id)\
	LE_COMMON_REG_LIST_BASE(id), \
	SRI(DP_DPHY_BS_SR_SWAP_CNTL, DP, id), \
	SRI(DP_DPHY_INTERNAL_CTRL, DP, id), \
	SR(DCI_MEM_PWR_STATUS)

#अगर defined(CONFIG_DRM_AMD_DC_SI)
#घोषणा LE_DCE60_REG_LIST(id)\
	SRI(DP_DPHY_INTERNAL_CTRL, DP, id), \
	SR(DMCU_RAM_ACCESS_CTRL), \
	SR(DMCU_IRAM_RD_CTRL), \
	SR(DMCU_IRAM_RD_DATA), \
	SR(DMCU_INTERRUPT_TO_UC_EN_MASK), \
	SRI(DIG_BE_CNTL, DIG, id), \
	SRI(DIG_BE_EN_CNTL, DIG, id), \
	SRI(DP_CONFIG, DP, id), \
	SRI(DP_DPHY_CNTL, DP, id), \
	SRI(DP_DPHY_PRBS_CNTL, DP, id), \
	SRI(DP_DPHY_SYM0, DP, id), \
	SRI(DP_DPHY_SYM1, DP, id), \
	SRI(DP_DPHY_SYM2, DP, id), \
	SRI(DP_DPHY_TRAINING_PATTERN_SEL, DP, id), \
	SRI(DP_LINK_CNTL, DP, id), \
	SRI(DP_LINK_FRAMING_CNTL, DP, id), \
	SRI(DP_MSE_SAT0, DP, id), \
	SRI(DP_MSE_SAT1, DP, id), \
	SRI(DP_MSE_SAT2, DP, id), \
	SRI(DP_MSE_SAT_UPDATE, DP, id), \
	SRI(DP_SEC_CNTL, DP, id), \
	SRI(DP_VID_STREAM_CNTL, DP, id), \
	SRI(DP_DPHY_FAST_TRAINING, DP, id), \
	SRI(DP_SEC_CNTL1, DP, id)
#पूर्ण_अगर

#घोषणा LE_DCE80_REG_LIST(id)\
	SRI(DP_DPHY_INTERNAL_CTRL, DP, id), \
	LE_COMMON_REG_LIST_BASE(id)

#घोषणा LE_DCE100_REG_LIST(id)\
	LE_COMMON_REG_LIST_BASE(id), \
	SRI(DP_DPHY_BS_SR_SWAP_CNTL, DP, id), \
	SRI(DP_DPHY_INTERNAL_CTRL, DP, id), \
	SR(DCI_MEM_PWR_STATUS)

#घोषणा LE_DCE110_REG_LIST(id)\
	LE_COMMON_REG_LIST_BASE(id), \
	SRI(DP_DPHY_BS_SR_SWAP_CNTL, DP, id), \
	SRI(DP_DPHY_INTERNAL_CTRL, DP, id), \
	SRI(DP_DPHY_HBR2_PATTERN_CONTROL, DP, id), \
	SR(DCI_MEM_PWR_STATUS)

#घोषणा LE_DCE120_REG_LIST(id)\
	LE_COMMON_REG_LIST_BASE(id), \
	SRI(DP_DPHY_BS_SR_SWAP_CNTL, DP, id), \
	SRI(DP_DPHY_HBR2_PATTERN_CONTROL, DP, id), \
	SR(DCI_MEM_PWR_STATUS)

#घोषणा LE_DCN10_REG_LIST(id)\
	LE_COMMON_REG_LIST_BASE(id), \
	SRI(DP_DPHY_BS_SR_SWAP_CNTL, DP, id), \
	SRI(DP_DPHY_INTERNAL_CTRL, DP, id), \
	SRI(DP_DPHY_HBR2_PATTERN_CONTROL, DP, id)

काष्ठा dce110_link_enc_aux_रेजिस्टरs अणु
	uपूर्णांक32_t AUX_CONTROL;
	uपूर्णांक32_t AUX_DPHY_RX_CONTROL0;
	uपूर्णांक32_t AUX_DPHY_RX_CONTROL1;
पूर्ण;

काष्ठा dce110_link_enc_hpd_रेजिस्टरs अणु
	uपूर्णांक32_t DC_HPD_CONTROL;
पूर्ण;

काष्ठा dce110_link_enc_रेजिस्टरs अणु
	/* DMCU रेजिस्टरs */
	uपूर्णांक32_t MASTER_COMM_DATA_REG1;
	uपूर्णांक32_t MASTER_COMM_DATA_REG2;
	uपूर्णांक32_t MASTER_COMM_DATA_REG3;
	uपूर्णांक32_t MASTER_COMM_CMD_REG;
	uपूर्णांक32_t MASTER_COMM_CNTL_REG;
	uपूर्णांक32_t DMCU_RAM_ACCESS_CTRL;
	uपूर्णांक32_t DCI_MEM_PWR_STATUS;
	uपूर्णांक32_t DMU_MEM_PWR_CNTL;
	uपूर्णांक32_t DMCU_IRAM_RD_CTRL;
	uपूर्णांक32_t DMCU_IRAM_RD_DATA;
	uपूर्णांक32_t DMCU_INTERRUPT_TO_UC_EN_MASK;

	/* Common DP रेजिस्टरs */
	uपूर्णांक32_t DIG_BE_CNTL;
	uपूर्णांक32_t DIG_BE_EN_CNTL;
	uपूर्णांक32_t DP_CONFIG;
	uपूर्णांक32_t DP_DPHY_CNTL;
	uपूर्णांक32_t DP_DPHY_INTERNAL_CTRL;
	uपूर्णांक32_t DP_DPHY_PRBS_CNTL;
	uपूर्णांक32_t DP_DPHY_SCRAM_CNTL;
	uपूर्णांक32_t DP_DPHY_SYM0;
	uपूर्णांक32_t DP_DPHY_SYM1;
	uपूर्णांक32_t DP_DPHY_SYM2;
	uपूर्णांक32_t DP_DPHY_TRAINING_PATTERN_SEL;
	uपूर्णांक32_t DP_LINK_CNTL;
	uपूर्णांक32_t DP_LINK_FRAMING_CNTL;
	uपूर्णांक32_t DP_MSE_SAT0;
	uपूर्णांक32_t DP_MSE_SAT1;
	uपूर्णांक32_t DP_MSE_SAT2;
	uपूर्णांक32_t DP_MSE_SAT_UPDATE;
	uपूर्णांक32_t DP_SEC_CNTL;
	uपूर्णांक32_t DP_VID_STREAM_CNTL;
	uपूर्णांक32_t DP_DPHY_FAST_TRAINING;
	uपूर्णांक32_t DP_DPHY_BS_SR_SWAP_CNTL;
	uपूर्णांक32_t DP_DPHY_HBR2_PATTERN_CONTROL;
	uपूर्णांक32_t DP_SEC_CNTL1;
पूर्ण;

काष्ठा dce110_link_encoder अणु
	काष्ठा link_encoder base;
	स्थिर काष्ठा dce110_link_enc_रेजिस्टरs *link_regs;
	स्थिर काष्ठा dce110_link_enc_aux_रेजिस्टरs *aux_regs;
	स्थिर काष्ठा dce110_link_enc_hpd_रेजिस्टरs *hpd_regs;
पूर्ण;


व्योम dce110_link_encoder_स्थिरruct(
	काष्ठा dce110_link_encoder *enc110,
	स्थिर काष्ठा encoder_init_data *init_data,
	स्थिर काष्ठा encoder_feature_support *enc_features,
	स्थिर काष्ठा dce110_link_enc_रेजिस्टरs *link_regs,
	स्थिर काष्ठा dce110_link_enc_aux_रेजिस्टरs *aux_regs,
	स्थिर काष्ठा dce110_link_enc_hpd_रेजिस्टरs *hpd_regs);

#अगर defined(CONFIG_DRM_AMD_DC_SI)
व्योम dce60_link_encoder_स्थिरruct(
	काष्ठा dce110_link_encoder *enc110,
	स्थिर काष्ठा encoder_init_data *init_data,
	स्थिर काष्ठा encoder_feature_support *enc_features,
	स्थिर काष्ठा dce110_link_enc_रेजिस्टरs *link_regs,
	स्थिर काष्ठा dce110_link_enc_aux_रेजिस्टरs *aux_regs,
	स्थिर काष्ठा dce110_link_enc_hpd_रेजिस्टरs *hpd_regs);
#पूर्ण_अगर

bool dce110_link_encoder_validate_dvi_output(
	स्थिर काष्ठा dce110_link_encoder *enc110,
	क्रमागत संकेत_type connector_संकेत,
	क्रमागत संकेत_type संकेत,
	स्थिर काष्ठा dc_crtc_timing *crtc_timing);

bool dce110_link_encoder_validate_rgb_output(
	स्थिर काष्ठा dce110_link_encoder *enc110,
	स्थिर काष्ठा dc_crtc_timing *crtc_timing);

bool dce110_link_encoder_validate_dp_output(
	स्थिर काष्ठा dce110_link_encoder *enc110,
	स्थिर काष्ठा dc_crtc_timing *crtc_timing);

bool dce110_link_encoder_validate_wireless_output(
	स्थिर काष्ठा dce110_link_encoder *enc110,
	स्थिर काष्ठा dc_crtc_timing *crtc_timing);

bool dce110_link_encoder_validate_output_with_stream(
	काष्ठा link_encoder *enc,
	स्थिर काष्ठा dc_stream_state *stream);

/****************** HW programming ************************/

/* initialize HW */  /* why करो we initialze aux in here? */
व्योम dce110_link_encoder_hw_init(काष्ठा link_encoder *enc);

व्योम dce110_link_encoder_destroy(काष्ठा link_encoder **enc);

/* program DIG_MODE in DIG_BE */
/* TODO can this be combined with enable_output? */
व्योम dce110_link_encoder_setup(
	काष्ठा link_encoder *enc,
	क्रमागत संकेत_type संकेत);

/* enables TMDS PHY output */
/* TODO: still need depth or just pass in adjusted pixel घड़ी? */
व्योम dce110_link_encoder_enable_पंचांगds_output(
	काष्ठा link_encoder *enc,
	क्रमागत घड़ी_source_id घड़ी_source,
	क्रमागत dc_color_depth color_depth,
	क्रमागत संकेत_type संकेत,
	uपूर्णांक32_t pixel_घड़ी);

/* enables DP PHY output */
व्योम dce110_link_encoder_enable_dp_output(
	काष्ठा link_encoder *enc,
	स्थिर काष्ठा dc_link_settings *link_settings,
	क्रमागत घड़ी_source_id घड़ी_source);

/* enables DP PHY output in MST mode */
व्योम dce110_link_encoder_enable_dp_mst_output(
	काष्ठा link_encoder *enc,
	स्थिर काष्ठा dc_link_settings *link_settings,
	क्रमागत घड़ी_source_id घड़ी_source);

/* enables LVDS PHY output */
व्योम dce110_link_encoder_enable_lvds_output(
	काष्ठा link_encoder *enc,
	क्रमागत घड़ी_source_id घड़ी_source,
	uपूर्णांक32_t pixel_घड़ी);

/* disable PHY output */
व्योम dce110_link_encoder_disable_output(
	काष्ठा link_encoder *enc,
	क्रमागत संकेत_type संकेत);

/* set DP lane settings */
व्योम dce110_link_encoder_dp_set_lane_settings(
	काष्ठा link_encoder *enc,
	स्थिर काष्ठा link_training_settings *link_settings);

व्योम dce110_link_encoder_dp_set_phy_pattern(
	काष्ठा link_encoder *enc,
	स्थिर काष्ठा encoder_set_dp_phy_pattern_param *param);

/* programs DP MST VC payload allocation */
व्योम dce110_link_encoder_update_mst_stream_allocation_table(
	काष्ठा link_encoder *enc,
	स्थिर काष्ठा link_mst_stream_allocation_table *table);

व्योम dce110_link_encoder_connect_dig_be_to_fe(
	काष्ठा link_encoder *enc,
	क्रमागत engine_id engine,
	bool connect);

अचिन्हित पूर्णांक dce110_get_dig_frontend(काष्ठा link_encoder *enc);

व्योम dce110_link_encoder_set_dp_phy_pattern_training_pattern(
	काष्ठा link_encoder *enc,
	uपूर्णांक32_t index);

व्योम dce110_link_encoder_enable_hpd(काष्ठा link_encoder *enc);

व्योम dce110_link_encoder_disable_hpd(काष्ठा link_encoder *enc);

व्योम dce110_psr_program_dp_dphy_fast_training(काष्ठा link_encoder *enc,
			bool निकास_link_training_required);

व्योम dce110_psr_program_secondary_packet(काष्ठा link_encoder *enc,
			अचिन्हित पूर्णांक sdp_transmit_line_num_deadline);

bool dce110_is_dig_enabled(काष्ठा link_encoder *enc);

व्योम dce110_link_encoder_get_max_link_cap(काष्ठा link_encoder *enc,
	काष्ठा dc_link_settings *link_settings);

#पूर्ण_अगर /* __DC_LINK_ENCODER__DCE110_H__ */
