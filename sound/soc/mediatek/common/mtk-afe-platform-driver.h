<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * mtk-afe-platक्रमm-driver.h  --  Mediatek afe platक्रमm driver definition
 *
 * Copyright (c) 2016 MediaTek Inc.
 * Author: Garlic Tseng <garlic.tseng@mediatek.com>
 */

#अगर_अघोषित _MTK_AFE_PLATFORM_DRIVER_H_
#घोषणा _MTK_AFE_PLATFORM_DRIVER_H_

#घोषणा AFE_PCM_NAME "mtk-afe-pcm"
बाह्य स्थिर काष्ठा snd_soc_component_driver mtk_afe_pcm_platक्रमm;

काष्ठा mtk_base_afe;
काष्ठा snd_pcm;
काष्ठा snd_soc_component;
काष्ठा snd_soc_pcm_runसमय;

snd_pcm_uframes_t mtk_afe_pcm_poपूर्णांकer(काष्ठा snd_soc_component *component,
				      काष्ठा snd_pcm_substream *substream);
पूर्णांक mtk_afe_pcm_new(काष्ठा snd_soc_component *component,
		    काष्ठा snd_soc_pcm_runसमय *rtd);

पूर्णांक mtk_afe_combine_sub_dai(काष्ठा mtk_base_afe *afe);
पूर्णांक mtk_afe_add_sub_dai_control(काष्ठा snd_soc_component *component);
#पूर्ण_अगर

