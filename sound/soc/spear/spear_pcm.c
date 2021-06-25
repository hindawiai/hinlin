<शैली गुरु>
/*
 * ALSA PCM पूर्णांकerface क्रम ST SPEAr Processors
 *
 * sound/soc/spear/spear_pcm.c
 *
 * Copyright (C) 2012 ST Microelectronics
 * Rajeev Kumar<rajeevkumar.linux@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/module.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/spear_dma.h>
#समावेश "spear_pcm.h"

अटल स्थिर काष्ठा snd_pcm_hardware spear_pcm_hardware = अणु
	.info = (SNDRV_PCM_INFO_INTERLEAVED | SNDRV_PCM_INFO_BLOCK_TRANSFER |
		 SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_MMAP_VALID |
		 SNDRV_PCM_INFO_PAUSE | SNDRV_PCM_INFO_RESUME),
	.buffer_bytes_max = 16 * 1024, /* max buffer size */
	.period_bytes_min = 2 * 1024, /* 1 msec data minimum period size */
	.period_bytes_max = 2 * 1024, /* maximum period size */
	.periods_min = 1, /* min # periods */
	.periods_max = 8, /* max # of periods */
	.fअगरo_size = 0, /* fअगरo size in bytes */
पूर्ण;

अटल स्थिर काष्ठा snd_dmaengine_pcm_config spear_dmaengine_pcm_config = अणु
	.pcm_hardware = &spear_pcm_hardware,
	.pपुनः_स्मृति_buffer_size = 16 * 1024,
पूर्ण;

पूर्णांक devm_spear_pcm_platक्रमm_रेजिस्टर(काष्ठा device *dev,
			काष्ठा snd_dmaengine_pcm_config *config,
			bool (*filter)(काष्ठा dma_chan *chan, व्योम *slave))
अणु
	*config = spear_dmaengine_pcm_config;
	config->compat_filter_fn = filter;

	वापस devm_snd_dmaengine_pcm_रेजिस्टर(dev, config,
		SND_DMAENGINE_PCM_FLAG_NO_DT |
		SND_DMAENGINE_PCM_FLAG_COMPAT);
पूर्ण
EXPORT_SYMBOL_GPL(devm_spear_pcm_platक्रमm_रेजिस्टर);

MODULE_AUTHOR("Rajeev Kumar <rajeevkumar.linux@gmail.com>");
MODULE_DESCRIPTION("SPEAr PCM DMA module");
MODULE_LICENSE("GPL");
