<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * mtk-afe-fe-dais.h  --  Mediatek afe fe dai चालक definition
 *
 * Copyright (c) 2016 MediaTek Inc.
 * Author: Garlic Tseng <garlic.tseng@mediatek.com>
 */

#अगर_अघोषित _MTK_AFE_FE_DAI_H_
#घोषणा _MTK_AFE_FE_DAI_H_

काष्ठा snd_soc_dai_ops;
काष्ठा mtk_base_afe;
काष्ठा mtk_base_afe_memअगर;

पूर्णांक mtk_afe_fe_startup(काष्ठा snd_pcm_substream *substream,
		       काष्ठा snd_soc_dai *dai);
व्योम mtk_afe_fe_shutकरोwn(काष्ठा snd_pcm_substream *substream,
			 काष्ठा snd_soc_dai *dai);
पूर्णांक mtk_afe_fe_hw_params(काष्ठा snd_pcm_substream *substream,
			 काष्ठा snd_pcm_hw_params *params,
			 काष्ठा snd_soc_dai *dai);
पूर्णांक mtk_afe_fe_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
		       काष्ठा snd_soc_dai *dai);
पूर्णांक mtk_afe_fe_prepare(काष्ठा snd_pcm_substream *substream,
		       काष्ठा snd_soc_dai *dai);
पूर्णांक mtk_afe_fe_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
		       काष्ठा snd_soc_dai *dai);

बाह्य स्थिर काष्ठा snd_soc_dai_ops mtk_afe_fe_ops;

पूर्णांक mtk_dynamic_irq_acquire(काष्ठा mtk_base_afe *afe);
पूर्णांक mtk_dynamic_irq_release(काष्ठा mtk_base_afe *afe, पूर्णांक irq_id);
पूर्णांक mtk_afe_suspend(काष्ठा snd_soc_component *component);
पूर्णांक mtk_afe_resume(काष्ठा snd_soc_component *component);

पूर्णांक mtk_memअगर_set_enable(काष्ठा mtk_base_afe *afe, पूर्णांक id);
पूर्णांक mtk_memअगर_set_disable(काष्ठा mtk_base_afe *afe, पूर्णांक id);
पूर्णांक mtk_memअगर_set_addr(काष्ठा mtk_base_afe *afe, पूर्णांक id,
		       अचिन्हित अक्षर *dma_area,
		       dma_addr_t dma_addr,
		       माप_प्रकार dma_bytes);
पूर्णांक mtk_memअगर_set_channel(काष्ठा mtk_base_afe *afe,
			  पूर्णांक id, अचिन्हित पूर्णांक channel);
पूर्णांक mtk_memअगर_set_rate(काष्ठा mtk_base_afe *afe,
		       पूर्णांक id, अचिन्हित पूर्णांक rate);
पूर्णांक mtk_memअगर_set_rate_substream(काष्ठा snd_pcm_substream *substream,
				 पूर्णांक id, अचिन्हित पूर्णांक rate);
पूर्णांक mtk_memअगर_set_क्रमmat(काष्ठा mtk_base_afe *afe,
			 पूर्णांक id, snd_pcm_क्रमmat_t क्रमmat);
पूर्णांक mtk_memअगर_set_pbuf_size(काष्ठा mtk_base_afe *afe,
			    पूर्णांक id, पूर्णांक pbuf_size);
#पूर्ण_अगर
