<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 2018 Texas Instruments Incorporated - https://www.ti.com
 *  Author: Peter Ujfalusi <peter.ujfalusi@ti.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/dmaengine_pcm.h>

#समावेश "sdma-pcm.h"

अटल स्थिर काष्ठा snd_pcm_hardware sdma_pcm_hardware = अणु
	.info			= SNDRV_PCM_INFO_MMAP |
				  SNDRV_PCM_INFO_MMAP_VALID |
				  SNDRV_PCM_INFO_PAUSE | SNDRV_PCM_INFO_RESUME |
				  SNDRV_PCM_INFO_NO_PERIOD_WAKEUP |
				  SNDRV_PCM_INFO_INTERLEAVED,
	.period_bytes_min	= 32,
	.period_bytes_max	= 64 * 1024,
	.buffer_bytes_max	= 128 * 1024,
	.periods_min		= 2,
	.periods_max		= 255,
पूर्ण;

अटल स्थिर काष्ठा snd_dmaengine_pcm_config sdma_dmaengine_pcm_config = अणु
	.pcm_hardware = &sdma_pcm_hardware,
	.prepare_slave_config = snd_dmaengine_pcm_prepare_slave_config,
	.pपुनः_स्मृति_buffer_size = 128 * 1024,
पूर्ण;

पूर्णांक sdma_pcm_platक्रमm_रेजिस्टर(काष्ठा device *dev,
			       अक्षर *txdmachan, अक्षर *rxdmachan)
अणु
	काष्ठा snd_dmaengine_pcm_config *config;
	अचिन्हित पूर्णांक flags = 0;

	/* Standard names क्रम the directions: 'tx' and 'rx' */
	अगर (!txdmachan && !rxdmachan)
		वापस devm_snd_dmaengine_pcm_रेजिस्टर(dev,
						&sdma_dmaengine_pcm_config, 0);

	config = devm_kzalloc(dev, माप(*config), GFP_KERNEL);
	अगर (!config)
		वापस -ENOMEM;

	*config = sdma_dmaengine_pcm_config;

	अगर (!txdmachan || !rxdmachan) अणु
		/* One direction only PCM */
		flags |= SND_DMAENGINE_PCM_FLAG_HALF_DUPLEX;
		अगर (!txdmachan) अणु
			txdmachan = rxdmachan;
			rxdmachan = शून्य;
		पूर्ण
	पूर्ण

	config->chan_names[0] = txdmachan;
	config->chan_names[1] = rxdmachan;

	वापस devm_snd_dmaengine_pcm_रेजिस्टर(dev, config, flags);
पूर्ण
EXPORT_SYMBOL_GPL(sdma_pcm_platक्रमm_रेजिस्टर);

MODULE_AUTHOR("Peter Ujfalusi <peter.ujfalusi@ti.com>");
MODULE_DESCRIPTION("sDMA PCM ASoC platform driver");
MODULE_LICENSE("GPL v2");
