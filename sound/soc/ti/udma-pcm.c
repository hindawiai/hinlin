<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 2020 Texas Instruments Incorporated - https://www.ti.com
 *  Author: Peter Ujfalusi <peter.ujfalusi@ti.com>
 */

#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/dmaengine_pcm.h>

#समावेश "udma-pcm.h"

अटल स्थिर काष्ठा snd_pcm_hardware udma_pcm_hardware = अणु
	.info			= SNDRV_PCM_INFO_MMAP |
				  SNDRV_PCM_INFO_MMAP_VALID |
				  SNDRV_PCM_INFO_PAUSE | SNDRV_PCM_INFO_RESUME |
				  SNDRV_PCM_INFO_NO_PERIOD_WAKEUP |
				  SNDRV_PCM_INFO_INTERLEAVED,
	.buffer_bytes_max	= SIZE_MAX,
	.period_bytes_min	= 32,
	.period_bytes_max	= SZ_64K,
	.periods_min		= 2,
	.periods_max		= अच_पूर्णांक_उच्च,
पूर्ण;

अटल स्थिर काष्ठा snd_dmaengine_pcm_config udma_dmaengine_pcm_config = अणु
	.pcm_hardware = &udma_pcm_hardware,
	.prepare_slave_config = snd_dmaengine_pcm_prepare_slave_config,
पूर्ण;

पूर्णांक udma_pcm_platक्रमm_रेजिस्टर(काष्ठा device *dev)
अणु
	वापस devm_snd_dmaengine_pcm_रेजिस्टर(dev, &udma_dmaengine_pcm_config,
					       0);
पूर्ण
EXPORT_SYMBOL_GPL(udma_pcm_platक्रमm_रेजिस्टर);

MODULE_AUTHOR("Peter Ujfalusi <peter.ujfalusi@ti.com>");
MODULE_DESCRIPTION("UDMA PCM ASoC platform driver");
MODULE_LICENSE("GPL v2");
