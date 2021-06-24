<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * edma-pcm.c - eDMA PCM driver using dmaengine क्रम AM3xxx, AM4xxx
 *
 * Copyright (C) 2014 Texas Instruments, Inc.
 *
 * Author: Peter Ujfalusi <peter.ujfalusi@ti.com>
 *
 * Based on: sound/soc/tegra/tegra_pcm.c
 */

#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/dmaengine_pcm.h>

#समावेश "edma-pcm.h"

अटल स्थिर काष्ठा snd_pcm_hardware edma_pcm_hardware = अणु
	.info			= SNDRV_PCM_INFO_MMAP |
				  SNDRV_PCM_INFO_MMAP_VALID |
				  SNDRV_PCM_INFO_PAUSE | SNDRV_PCM_INFO_RESUME |
				  SNDRV_PCM_INFO_NO_PERIOD_WAKEUP |
				  SNDRV_PCM_INFO_INTERLEAVED,
	.buffer_bytes_max	= 128 * 1024,
	.period_bytes_min	= 32,
	.period_bytes_max	= 64 * 1024,
	.periods_min		= 2,
	.periods_max		= 19, /* Limit by edma dmaengine driver */
पूर्ण;

अटल स्थिर काष्ठा snd_dmaengine_pcm_config edma_dmaengine_pcm_config = अणु
	.pcm_hardware = &edma_pcm_hardware,
	.prepare_slave_config = snd_dmaengine_pcm_prepare_slave_config,
	.pपुनः_स्मृति_buffer_size = 128 * 1024,
पूर्ण;

पूर्णांक edma_pcm_platक्रमm_रेजिस्टर(काष्ठा device *dev)
अणु
	काष्ठा snd_dmaengine_pcm_config *config;

	अगर (dev->of_node)
		वापस devm_snd_dmaengine_pcm_रेजिस्टर(dev,
						&edma_dmaengine_pcm_config, 0);

	config = devm_kzalloc(dev, माप(*config), GFP_KERNEL);
	अगर (!config)
		वापस -ENOMEM;

	*config = edma_dmaengine_pcm_config;

	config->chan_names[0] = "tx";
	config->chan_names[1] = "rx";

	वापस devm_snd_dmaengine_pcm_रेजिस्टर(dev, config, 0);
पूर्ण
EXPORT_SYMBOL_GPL(edma_pcm_platक्रमm_रेजिस्टर);

MODULE_AUTHOR("Peter Ujfalusi <peter.ujfalusi@ti.com>");
MODULE_DESCRIPTION("eDMA PCM ASoC platform driver");
MODULE_LICENSE("GPL");
