<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * mt6797-afe-common.h  --  Mediatek 6797 audio driver definitions
 *
 * Copyright (c) 2018 MediaTek Inc.
 * Author: KaiChieh Chuang <kaichieh.chuang@mediatek.com>
 */

#अगर_अघोषित _MT_6797_AFE_COMMON_H_
#घोषणा _MT_6797_AFE_COMMON_H_

#समावेश <sound/soc.h>
#समावेश <linux/list.h>
#समावेश <linux/regmap.h>
#समावेश "../common/mtk-base-afe.h"

क्रमागत अणु
	MT6797_MEMIF_DL1,
	MT6797_MEMIF_DL2,
	MT6797_MEMIF_DL3,
	MT6797_MEMIF_VUL,
	MT6797_MEMIF_AWB,
	MT6797_MEMIF_VUL12,
	MT6797_MEMIF_DAI,
	MT6797_MEMIF_MOD_DAI,
	MT6797_MEMIF_NUM,
	MT6797_DAI_ADDA = MT6797_MEMIF_NUM,
	MT6797_DAI_PCM_1,
	MT6797_DAI_PCM_2,
	MT6797_DAI_HOSTLESS_LPBK,
	MT6797_DAI_HOSTLESS_SPEECH,
	MT6797_DAI_NUM,
पूर्ण;

क्रमागत अणु
	MT6797_IRQ_1,
	MT6797_IRQ_2,
	MT6797_IRQ_3,
	MT6797_IRQ_4,
	MT6797_IRQ_7,
	MT6797_IRQ_NUM,
पूर्ण;

काष्ठा clk;

काष्ठा mt6797_afe_निजी अणु
	काष्ठा clk **clk;
पूर्ण;

अचिन्हित पूर्णांक mt6797_general_rate_transक्रमm(काष्ठा device *dev,
					   अचिन्हित पूर्णांक rate);
अचिन्हित पूर्णांक mt6797_rate_transक्रमm(काष्ठा device *dev,
				   अचिन्हित पूर्णांक rate, पूर्णांक aud_blk);

/* dai रेजिस्टर */
पूर्णांक mt6797_dai_adda_रेजिस्टर(काष्ठा mtk_base_afe *afe);
पूर्णांक mt6797_dai_pcm_रेजिस्टर(काष्ठा mtk_base_afe *afe);
पूर्णांक mt6797_dai_hostless_रेजिस्टर(काष्ठा mtk_base_afe *afe);
#पूर्ण_अगर
