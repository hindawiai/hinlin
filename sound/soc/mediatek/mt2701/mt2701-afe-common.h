<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * mt2701-afe-common.h  --  Mediatek 2701 audio driver definitions
 *
 * Copyright (c) 2016 MediaTek Inc.
 * Author: Garlic Tseng <garlic.tseng@mediatek.com>
 */

#अगर_अघोषित _MT_2701_AFE_COMMON_H_
#घोषणा _MT_2701_AFE_COMMON_H_

#समावेश <sound/soc.h>
#समावेश <linux/clk.h>
#समावेश <linux/regmap.h>
#समावेश "mt2701-reg.h"
#समावेश "../common/mtk-base-afe.h"

#घोषणा MT2701_PLL_DOMAIN_0_RATE	98304000
#घोषणा MT2701_PLL_DOMAIN_1_RATE	90316800

क्रमागत अणु
	MT2701_MEMIF_DL1,
	MT2701_MEMIF_DL2,
	MT2701_MEMIF_DL3,
	MT2701_MEMIF_DL4,
	MT2701_MEMIF_DL5,
	MT2701_MEMIF_DL_SINGLE_NUM,
	MT2701_MEMIF_DLM = MT2701_MEMIF_DL_SINGLE_NUM,
	MT2701_MEMIF_UL1,
	MT2701_MEMIF_UL2,
	MT2701_MEMIF_UL3,
	MT2701_MEMIF_UL4,
	MT2701_MEMIF_UL5,
	MT2701_MEMIF_DLBT,
	MT2701_MEMIF_ULBT,
	MT2701_MEMIF_NUM,
	MT2701_IO_I2S = MT2701_MEMIF_NUM,
	MT2701_IO_2ND_I2S,
	MT2701_IO_3RD_I2S,
	MT2701_IO_4TH_I2S,
	MT2701_IO_5TH_I2S,
	MT2701_IO_6TH_I2S,
	MT2701_IO_MRG,
पूर्ण;

क्रमागत अणु
	MT2701_IRQ_ASYS_IRQ1,
	MT2701_IRQ_ASYS_IRQ2,
	MT2701_IRQ_ASYS_IRQ3,
	MT2701_IRQ_ASYS_END,
पूर्ण;

क्रमागत audio_base_घड़ी अणु
	MT2701_INFRA_SYS_AUDIO,
	MT2701_TOP_AUD_MCLK_SRC0,
	MT2701_TOP_AUD_MCLK_SRC1,
	MT2701_TOP_AUD_A1SYS,
	MT2701_TOP_AUD_A2SYS,
	MT2701_AUDSYS_AFE,
	MT2701_AUDSYS_AFE_CONN,
	MT2701_AUDSYS_A1SYS,
	MT2701_AUDSYS_A2SYS,
	MT2701_BASE_CLK_NUM,
पूर्ण;

काष्ठा mt2701_i2s_data अणु
	पूर्णांक i2s_ctrl_reg;
	पूर्णांक i2s_asrc_fs_shअगरt;
	पूर्णांक i2s_asrc_fs_mask;
पूर्ण;

काष्ठा mt2701_i2s_path अणु
	पूर्णांक mclk_rate;
	पूर्णांक on[MTK_STREAM_NUM];
	पूर्णांक occupied[MTK_STREAM_NUM];
	स्थिर काष्ठा mt2701_i2s_data *i2s_data[MTK_STREAM_NUM];
	काष्ठा clk *hop_ck[MTK_STREAM_NUM];
	काष्ठा clk *sel_ck;
	काष्ठा clk *भाग_ck;
	काष्ठा clk *mclk_ck;
	काष्ठा clk *asrco_ck;
पूर्ण;

काष्ठा mt2701_soc_variants अणु
	bool has_one_heart_mode;
	पूर्णांक i2s_num;
पूर्ण;

काष्ठा mt2701_afe_निजी अणु
	काष्ठा mt2701_i2s_path *i2s_path;
	काष्ठा clk *base_ck[MT2701_BASE_CLK_NUM];
	काष्ठा clk *mrgअगर_ck;
	bool mrg_enable[MTK_STREAM_NUM];

	स्थिर काष्ठा mt2701_soc_variants *soc;
पूर्ण;

#पूर्ण_अगर
