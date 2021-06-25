<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * mt8183-afe-common.h  --  Mediatek 8183 audio driver definitions
 *
 * Copyright (c) 2018 MediaTek Inc.
 * Author: KaiChieh Chuang <kaichieh.chuang@mediatek.com>
 */

#अगर_अघोषित _MT_8183_AFE_COMMON_H_
#घोषणा _MT_8183_AFE_COMMON_H_

#समावेश <sound/soc.h>
#समावेश <linux/list.h>
#समावेश <linux/regmap.h>
#समावेश "../common/mtk-base-afe.h"

क्रमागत अणु
	MT8183_MEMIF_DL1,
	MT8183_MEMIF_DL2,
	MT8183_MEMIF_DL3,
	MT8183_MEMIF_VUL12,
	MT8183_MEMIF_VUL2,
	MT8183_MEMIF_AWB,
	MT8183_MEMIF_AWB2,
	MT8183_MEMIF_MOD_DAI,
	MT8183_MEMIF_HDMI,
	MT8183_MEMIF_NUM,
	MT8183_DAI_ADDA = MT8183_MEMIF_NUM,
	MT8183_DAI_PCM_1,
	MT8183_DAI_PCM_2,
	MT8183_DAI_I2S_0,
	MT8183_DAI_I2S_1,
	MT8183_DAI_I2S_2,
	MT8183_DAI_I2S_3,
	MT8183_DAI_I2S_5,
	MT8183_DAI_TDM,
	MT8183_DAI_HOSTLESS_LPBK,
	MT8183_DAI_HOSTLESS_SPEECH,
	MT8183_DAI_NUM,
पूर्ण;

क्रमागत अणु
	MT8183_IRQ_0,
	MT8183_IRQ_1,
	MT8183_IRQ_2,
	MT8183_IRQ_3,
	MT8183_IRQ_4,
	MT8183_IRQ_5,
	MT8183_IRQ_6,
	MT8183_IRQ_7,
	MT8183_IRQ_8,	/* hw bundle to TDM */
	MT8183_IRQ_11,
	MT8183_IRQ_12,
	MT8183_IRQ_NUM,
पूर्ण;

क्रमागत अणु
	MT8183_MTKAIF_PROTOCOL_1 = 0,
	MT8183_MTKAIF_PROTOCOL_2,
	MT8183_MTKAIF_PROTOCOL_2_CLK_P2,
पूर्ण;

/* MCLK */
क्रमागत अणु
	MT8183_I2S0_MCK = 0,
	MT8183_I2S1_MCK,
	MT8183_I2S2_MCK,
	MT8183_I2S3_MCK,
	MT8183_I2S4_MCK,
	MT8183_I2S4_BCK,
	MT8183_I2S5_MCK,
	MT8183_MCK_NUM,
पूर्ण;

काष्ठा clk;

काष्ठा mt8183_afe_निजी अणु
	काष्ठा clk **clk;

	पूर्णांक pm_runसमय_bypass_reg_ctl;

	/* dai */
	व्योम *dai_priv[MT8183_DAI_NUM];

	/* adda */
	पूर्णांक mtkaअगर_protocol;
	पूर्णांक mtkaअगर_calibration_ok;
	पूर्णांक mtkaअगर_chosen_phase[4];
	पूर्णांक mtkaअगर_phase_cycle[4];
	पूर्णांक mtkaअगर_calibration_num_phase;
	पूर्णांक mtkaअगर_dmic;

	/* mck */
	पूर्णांक mck_rate[MT8183_MCK_NUM];
पूर्ण;

अचिन्हित पूर्णांक mt8183_general_rate_transक्रमm(काष्ठा device *dev,
					   अचिन्हित पूर्णांक rate);
अचिन्हित पूर्णांक mt8183_rate_transक्रमm(काष्ठा device *dev,
				   अचिन्हित पूर्णांक rate, पूर्णांक aud_blk);

/* dai रेजिस्टर */
पूर्णांक mt8183_dai_adda_रेजिस्टर(काष्ठा mtk_base_afe *afe);
पूर्णांक mt8183_dai_pcm_रेजिस्टर(काष्ठा mtk_base_afe *afe);
पूर्णांक mt8183_dai_i2s_रेजिस्टर(काष्ठा mtk_base_afe *afe);
पूर्णांक mt8183_dai_tdm_रेजिस्टर(काष्ठा mtk_base_afe *afe);
पूर्णांक mt8183_dai_hostless_रेजिस्टर(काष्ठा mtk_base_afe *afe);
#पूर्ण_अगर
