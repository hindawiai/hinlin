<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * mt8192-afe-common.h  --  Mediatek 8192 audio driver definitions
 *
 * Copyright (c) 2020 MediaTek Inc.
 * Author: Shane Chien <shane.chien@mediatek.com>
 */

#अगर_अघोषित _MT_8192_AFE_COMMON_H_
#घोषणा _MT_8192_AFE_COMMON_H_

#समावेश <linux/list.h>
#समावेश <linux/regmap.h>
#समावेश <sound/soc.h>

#समावेश "../common/mtk-base-afe.h"
#समावेश "mt8192-reg.h"

क्रमागत अणु
	MT8192_MEMIF_DL1,
	MT8192_MEMIF_DL12,
	MT8192_MEMIF_DL2,
	MT8192_MEMIF_DL3,
	MT8192_MEMIF_DL4,
	MT8192_MEMIF_DL5,
	MT8192_MEMIF_DL6,
	MT8192_MEMIF_DL7,
	MT8192_MEMIF_DL8,
	MT8192_MEMIF_DL9,
	MT8192_MEMIF_DAI,
	MT8192_MEMIF_DAI2,
	MT8192_MEMIF_MOD_DAI,
	MT8192_MEMIF_VUL12,
	MT8192_MEMIF_VUL2,
	MT8192_MEMIF_VUL3,
	MT8192_MEMIF_VUL4,
	MT8192_MEMIF_VUL5,
	MT8192_MEMIF_VUL6,
	MT8192_MEMIF_AWB,
	MT8192_MEMIF_AWB2,
	MT8192_MEMIF_HDMI,
	MT8192_MEMIF_NUM,
	MT8192_DAI_ADDA = MT8192_MEMIF_NUM,
	MT8192_DAI_ADDA_CH34,
	MT8192_DAI_AP_DMIC,
	MT8192_DAI_AP_DMIC_CH34,
	MT8192_DAI_VOW,
	MT8192_DAI_CONNSYS_I2S,
	MT8192_DAI_I2S_0,
	MT8192_DAI_I2S_1,
	MT8192_DAI_I2S_2,
	MT8192_DAI_I2S_3,
	MT8192_DAI_I2S_5,
	MT8192_DAI_I2S_6,
	MT8192_DAI_I2S_7,
	MT8192_DAI_I2S_8,
	MT8192_DAI_I2S_9,
	MT8192_DAI_HW_GAIN_1,
	MT8192_DAI_HW_GAIN_2,
	MT8192_DAI_SRC_1,
	MT8192_DAI_SRC_2,
	MT8192_DAI_PCM_1,
	MT8192_DAI_PCM_2,
	MT8192_DAI_TDM,
	MT8192_DAI_NUM,
पूर्ण;

क्रमागत अणु
	MT8192_IRQ_0,
	MT8192_IRQ_1,
	MT8192_IRQ_2,
	MT8192_IRQ_3,
	MT8192_IRQ_4,
	MT8192_IRQ_5,
	MT8192_IRQ_6,
	MT8192_IRQ_7,
	MT8192_IRQ_8,
	MT8192_IRQ_9,
	MT8192_IRQ_10,
	MT8192_IRQ_11,
	MT8192_IRQ_12,
	MT8192_IRQ_13,
	MT8192_IRQ_14,
	MT8192_IRQ_15,
	MT8192_IRQ_16,
	MT8192_IRQ_17,
	MT8192_IRQ_18,
	MT8192_IRQ_19,
	MT8192_IRQ_20,
	MT8192_IRQ_21,
	MT8192_IRQ_22,
	MT8192_IRQ_23,
	MT8192_IRQ_24,
	MT8192_IRQ_25,
	MT8192_IRQ_26,
	MT8192_IRQ_31,	/* used only क्रम TDM */
	MT8192_IRQ_NUM,
पूर्ण;

क्रमागत अणु
	MTKAIF_PROTOCOL_1 = 0,
	MTKAIF_PROTOCOL_2,
	MTKAIF_PROTOCOL_2_CLK_P2,
पूर्ण;

क्रमागत अणु
	MTK_AFE_ADDA_DL_GAIN_MUTE = 0,
	MTK_AFE_ADDA_DL_GAIN_NORMAL = 0xf74f,
	/* SA suggest apply -0.3db to audio/speech path */
पूर्ण;

/* MCLK */
क्रमागत अणु
	MT8192_I2S0_MCK = 0,
	MT8192_I2S1_MCK,
	MT8192_I2S2_MCK,
	MT8192_I2S3_MCK,
	MT8192_I2S4_MCK,
	MT8192_I2S4_BCK,
	MT8192_I2S5_MCK,
	MT8192_I2S6_MCK,
	MT8192_I2S7_MCK,
	MT8192_I2S8_MCK,
	MT8192_I2S9_MCK,
	MT8192_MCK_NUM,
पूर्ण;

काष्ठा clk;

काष्ठा mt8192_afe_निजी अणु
	काष्ठा clk **clk;
	काष्ठा regmap *topckgen;
	काष्ठा regmap *apmixedsys;
	काष्ठा regmap *infracfg;
	पूर्णांक stf_positive_gain_db;
	पूर्णांक pm_runसमय_bypass_reg_ctl;

	/* dai */
	bool dai_on[MT8192_DAI_NUM];
	व्योम *dai_priv[MT8192_DAI_NUM];

	/* adda */
	पूर्णांक mtkaअगर_protocol;
	पूर्णांक mtkaअगर_chosen_phase[4];
	पूर्णांक mtkaअगर_phase_cycle[4];
	पूर्णांक mtkaअगर_calibration_num_phase;
	पूर्णांक mtkaअगर_dmic;
	पूर्णांक mtkaअगर_dmic_ch34;
	पूर्णांक mtkaअगर_adda6_only;

	/* mck */
	पूर्णांक mck_rate[MT8192_MCK_NUM];
पूर्ण;

पूर्णांक mt8192_dai_adda_रेजिस्टर(काष्ठा mtk_base_afe *afe);
पूर्णांक mt8192_dai_i2s_रेजिस्टर(काष्ठा mtk_base_afe *afe);
पूर्णांक mt8192_dai_hw_gain_रेजिस्टर(काष्ठा mtk_base_afe *afe);
पूर्णांक mt8192_dai_src_रेजिस्टर(काष्ठा mtk_base_afe *afe);
पूर्णांक mt8192_dai_pcm_रेजिस्टर(काष्ठा mtk_base_afe *afe);
पूर्णांक mt8192_dai_tdm_रेजिस्टर(काष्ठा mtk_base_afe *afe);

अचिन्हित पूर्णांक mt8192_general_rate_transक्रमm(काष्ठा device *dev,
					   अचिन्हित पूर्णांक rate);
अचिन्हित पूर्णांक mt8192_rate_transक्रमm(काष्ठा device *dev,
				   अचिन्हित पूर्णांक rate, पूर्णांक aud_blk);

पूर्णांक mt8192_dai_set_priv(काष्ठा mtk_base_afe *afe, पूर्णांक id,
			पूर्णांक priv_size, स्थिर व्योम *priv_data);

#पूर्ण_अगर
