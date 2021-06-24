<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// dmaengine.c - Samsung dmaengine wrapper
//
// Author: Mark Brown <broonie@linaro.org>
// Copyright 2013 Linaro

#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/soc.h>

#समावेश "dma.h"

पूर्णांक samsung_asoc_dma_platक्रमm_रेजिस्टर(काष्ठा device *dev, dma_filter_fn filter,
				       स्थिर अक्षर *tx, स्थिर अक्षर *rx,
				       काष्ठा device *dma_dev)
अणु
	काष्ठा snd_dmaengine_pcm_config *pcm_conf;

	pcm_conf = devm_kzalloc(dev, माप(*pcm_conf), GFP_KERNEL);
	अगर (!pcm_conf)
		वापस -ENOMEM;

	pcm_conf->prepare_slave_config = snd_dmaengine_pcm_prepare_slave_config;
	pcm_conf->compat_filter_fn = filter;
	pcm_conf->dma_dev = dma_dev;

	pcm_conf->chan_names[SNDRV_PCM_STREAM_PLAYBACK] = tx;
	pcm_conf->chan_names[SNDRV_PCM_STREAM_CAPTURE] = rx;

	वापस devm_snd_dmaengine_pcm_रेजिस्टर(dev, pcm_conf,
				SND_DMAENGINE_PCM_FLAG_COMPAT);
पूर्ण
EXPORT_SYMBOL_GPL(samsung_asoc_dma_platक्रमm_रेजिस्टर);

MODULE_AUTHOR("Mark Brown <broonie@linaro.org>");
MODULE_DESCRIPTION("Samsung dmaengine ASoC driver");
MODULE_LICENSE("GPL");
