<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/sound/arm/ep93xx-pcm.c - EP93xx ALSA PCM पूर्णांकerface
 *
 * Copyright (C) 2006 Lennert Buytenhek <buytenh@wantstofly.org>
 * Copyright (C) 2006 Applied Data Systems
 *
 * Rewritten क्रम the SoC audio subप्रणाली (Based on PXA2xx code):
 *   Copyright (c) 2008 Ryan Mallon
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dmaengine.h>

#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/dmaengine_pcm.h>

#समावेश <linux/platक्रमm_data/dma-ep93xx.h>

#समावेश "ep93xx-pcm.h"

अटल स्थिर काष्ठा snd_pcm_hardware ep93xx_pcm_hardware = अणु
	.info			= (SNDRV_PCM_INFO_MMAP		|
				   SNDRV_PCM_INFO_MMAP_VALID	|
				   SNDRV_PCM_INFO_INTERLEAVED	|
				   SNDRV_PCM_INFO_BLOCK_TRANSFER),
	.buffer_bytes_max	= 131072,
	.period_bytes_min	= 32,
	.period_bytes_max	= 32768,
	.periods_min		= 1,
	.periods_max		= 32,
	.fअगरo_size		= 32,
पूर्ण;

अटल bool ep93xx_pcm_dma_filter(काष्ठा dma_chan *chan, व्योम *filter_param)
अणु
	काष्ठा ep93xx_dma_data *data = filter_param;

	अगर (data->direction == ep93xx_dma_chan_direction(chan)) अणु
		chan->निजी = data;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल स्थिर काष्ठा snd_dmaengine_pcm_config ep93xx_dmaengine_pcm_config = अणु
	.pcm_hardware = &ep93xx_pcm_hardware,
	.compat_filter_fn = ep93xx_pcm_dma_filter,
	.pपुनः_स्मृति_buffer_size = 131072,
पूर्ण;

पूर्णांक devm_ep93xx_pcm_platक्रमm_रेजिस्टर(काष्ठा device *dev)
अणु
	वापस devm_snd_dmaengine_pcm_रेजिस्टर(dev,
		&ep93xx_dmaengine_pcm_config,
		SND_DMAENGINE_PCM_FLAG_NO_DT |
		SND_DMAENGINE_PCM_FLAG_COMPAT);
पूर्ण
EXPORT_SYMBOL_GPL(devm_ep93xx_pcm_platक्रमm_रेजिस्टर);

MODULE_AUTHOR("Ryan Mallon");
MODULE_DESCRIPTION("EP93xx ALSA PCM interface");
MODULE_LICENSE("GPL");
