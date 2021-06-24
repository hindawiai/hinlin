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

#अगर_अघोषित __DC_LINK_ENCODER__DCN21_H__
#घोषणा __DC_LINK_ENCODER__DCN21_H__

#समावेश "dcn20/dcn20_link_encoder.h"

काष्ठा dcn21_link_encoder अणु
	काष्ठा dcn10_link_encoder enc10;
	काष्ठा dpcssys_phy_seq_cfg phy_seq_cfg;
पूर्ण;

#घोषणा DPCS_DCN21_MASK_SH_LIST(mask_sh)\
	DPCS_DCN2_MASK_SH_LIST(mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_FUSE3, RDPCS_PHY_TX_VBOOST_LVL, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_FUSE2, RDPCS_PHY_DP_MPLLB_CP_PROP_GS, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_FUSE0, RDPCS_PHY_RX_VREF_CTRL, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_FUSE0, RDPCS_PHY_DP_MPLLB_CP_INT_GS, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_DMCU_DPALT_DIS_BLOCK_REG, RDPCS_DMCU_DPALT_DIS_BLOCK_REG, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL15, RDPCS_PHY_SUP_PRE_HP, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL15, RDPCS_PHY_DP_TX0_VREGDRV_BYP, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL15, RDPCS_PHY_DP_TX1_VREGDRV_BYP, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL15, RDPCS_PHY_DP_TX2_VREGDRV_BYP, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL15, RDPCS_PHY_DP_TX3_VREGDRV_BYP, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL6, RDPCS_PHY_DPALT_DP4, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_CNTL6, RDPCS_PHY_DPALT_DISABLE, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_FUSE0, RDPCS_PHY_DP_TX0_EQ_MAIN, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_FUSE0, RDPCS_PHY_DP_TX0_EQ_PRE, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_FUSE0, RDPCS_PHY_DP_TX0_EQ_POST, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_FUSE1, RDPCS_PHY_DP_TX1_EQ_MAIN, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_FUSE1, RDPCS_PHY_DP_TX1_EQ_PRE, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_FUSE1, RDPCS_PHY_DP_TX1_EQ_POST, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_FUSE2, RDPCS_PHY_DP_TX2_EQ_MAIN, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_FUSE2, RDPCS_PHY_DP_TX2_EQ_PRE, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_FUSE2, RDPCS_PHY_DP_TX2_EQ_POST, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_FUSE3, RDPCS_PHY_DP_TX3_EQ_MAIN, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_FUSE3, RDPCS_PHY_DCO_FINETUNE, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_FUSE3, RDPCS_PHY_DCO_RANGE, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_FUSE3, RDPCS_PHY_DP_TX3_EQ_PRE, mask_sh),\
	LE_SF(RDPCSTX0_RDPCSTX_PHY_FUSE3, RDPCS_PHY_DP_TX3_EQ_POST, mask_sh),\
	LE_SF(DCIO_SOFT_RESET, UNIPHYA_SOFT_RESET, mask_sh),\
	LE_SF(DCIO_SOFT_RESET, UNIPHYB_SOFT_RESET, mask_sh),\
	LE_SF(DCIO_SOFT_RESET, UNIPHYC_SOFT_RESET, mask_sh),\
	LE_SF(DCIO_SOFT_RESET, UNIPHYD_SOFT_RESET, mask_sh),\
	LE_SF(DCIO_SOFT_RESET, UNIPHYE_SOFT_RESET, mask_sh)

#घोषणा DPCS_DCN21_REG_LIST(id) \
	DPCS_DCN2_REG_LIST(id),\
	SRI(RDPCSTX_PHY_CNTL15, RDPCSTX, id),\
	SRI(RDPCSTX_DMCU_DPALT_DIS_BLOCK_REG, RDPCSTX, id)

#घोषणा LINK_ENCODER_MASK_SH_LIST_DCN21(mask_sh)\
	LINK_ENCODER_MASK_SH_LIST_DCN20(mask_sh),\
	LE_SF(UNIPHYA_CHANNEL_XBAR_CNTL, UNIPHY_CHANNEL0_XBAR_SOURCE, mask_sh),\
	LE_SF(UNIPHYA_CHANNEL_XBAR_CNTL, UNIPHY_CHANNEL1_XBAR_SOURCE, mask_sh),\
	LE_SF(UNIPHYA_CHANNEL_XBAR_CNTL, UNIPHY_CHANNEL2_XBAR_SOURCE, mask_sh),\
	LE_SF(UNIPHYA_CHANNEL_XBAR_CNTL, UNIPHY_CHANNEL3_XBAR_SOURCE, mask_sh), \
	SRI(RDPCSTX_PHY_FUSE2, RDPCSTX, id), \
	SRI(RDPCSTX_PHY_FUSE3, RDPCSTX, id), \
	SR(RDPCSTX0_RDPCSTX_SCRATCH)

व्योम dcn21_link_encoder_enable_dp_output(
	काष्ठा link_encoder *enc,
	स्थिर काष्ठा dc_link_settings *link_settings,
	क्रमागत घड़ी_source_id घड़ी_source);

व्योम dcn21_link_encoder_स्थिरruct(
	काष्ठा dcn21_link_encoder *enc21,
	स्थिर काष्ठा encoder_init_data *init_data,
	स्थिर काष्ठा encoder_feature_support *enc_features,
	स्थिर काष्ठा dcn10_link_enc_रेजिस्टरs *link_regs,
	स्थिर काष्ठा dcn10_link_enc_aux_रेजिस्टरs *aux_regs,
	स्थिर काष्ठा dcn10_link_enc_hpd_रेजिस्टरs *hpd_regs,
	स्थिर काष्ठा dcn10_link_enc_shअगरt *link_shअगरt,
	स्थिर काष्ठा dcn10_link_enc_mask *link_mask);

#पूर्ण_अगर
