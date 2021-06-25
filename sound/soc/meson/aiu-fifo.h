<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR MIT) */
/*
 * Copyright (c) 2020 BayLibre, SAS.
 * Author: Jerome Brunet <jbrunet@baylibre.com>
 */

#अगर_अघोषित _MESON_AIU_FIFO_H
#घोषणा _MESON_AIU_FIFO_H

काष्ठा snd_pcm_hardware;
काष्ठा snd_soc_component_driver;
काष्ठा snd_soc_dai_driver;
काष्ठा clk;
काष्ठा snd_pcm_ops;
काष्ठा snd_pcm_substream;
काष्ठा snd_soc_dai;
काष्ठा snd_pcm_hw_params;
काष्ठा platक्रमm_device;

काष्ठा aiu_fअगरo अणु
	काष्ठा snd_pcm_hardware *pcm;
	अचिन्हित पूर्णांक mem_offset;
	अचिन्हित पूर्णांक fअगरo_block;
	काष्ठा clk *pclk;
	पूर्णांक irq;
पूर्ण;

पूर्णांक aiu_fअगरo_dai_probe(काष्ठा snd_soc_dai *dai);
पूर्णांक aiu_fअगरo_dai_हटाओ(काष्ठा snd_soc_dai *dai);

snd_pcm_uframes_t aiu_fअगरo_poपूर्णांकer(काष्ठा snd_soc_component *component,
				   काष्ठा snd_pcm_substream *substream);

पूर्णांक aiu_fअगरo_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
		     काष्ठा snd_soc_dai *dai);
पूर्णांक aiu_fअगरo_prepare(काष्ठा snd_pcm_substream *substream,
		     काष्ठा snd_soc_dai *dai);
पूर्णांक aiu_fअगरo_hw_params(काष्ठा snd_pcm_substream *substream,
		       काष्ठा snd_pcm_hw_params *params,
		       काष्ठा snd_soc_dai *dai);
पूर्णांक aiu_fअगरo_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
		     काष्ठा snd_soc_dai *dai);
पूर्णांक aiu_fअगरo_startup(काष्ठा snd_pcm_substream *substream,
		     काष्ठा snd_soc_dai *dai);
व्योम aiu_fअगरo_shutकरोwn(काष्ठा snd_pcm_substream *substream,
		       काष्ठा snd_soc_dai *dai);
पूर्णांक aiu_fअगरo_pcm_new(काष्ठा snd_soc_pcm_runसमय *rtd,
		     काष्ठा snd_soc_dai *dai);

#पूर्ण_अगर /* _MESON_AIU_FIFO_H */
