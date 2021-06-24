<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2011 Freescale Semiconductor, Inc. All Rights Reserved.
 *
 * Based on sound/soc/imx/imx-pcm-dma-mx2.c
 */

#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/dmaengine_pcm.h>

#समावेश "mxs-pcm.h"

अटल स्थिर काष्ठा snd_pcm_hardware snd_mxs_hardware = अणु
	.info			= SNDRV_PCM_INFO_MMAP |
				  SNDRV_PCM_INFO_MMAP_VALID |
				  SNDRV_PCM_INFO_PAUSE |
				  SNDRV_PCM_INFO_RESUME |
				  SNDRV_PCM_INFO_INTERLEAVED |
				  SNDRV_PCM_INFO_HALF_DUPLEX,
	.period_bytes_min	= 32,
	.period_bytes_max	= 8192,
	.periods_min		= 1,
	.periods_max		= 52,
	.buffer_bytes_max	= 64 * 1024,
	.fअगरo_size		= 32,
पूर्ण;

अटल स्थिर काष्ठा snd_dmaengine_pcm_config mxs_dmaengine_pcm_config = अणु
	.pcm_hardware = &snd_mxs_hardware,
	.pपुनः_स्मृति_buffer_size = 64 * 1024,
पूर्ण;

पूर्णांक mxs_pcm_platक्रमm_रेजिस्टर(काष्ठा device *dev)
अणु
	वापस devm_snd_dmaengine_pcm_रेजिस्टर(dev, &mxs_dmaengine_pcm_config,
		SND_DMAENGINE_PCM_FLAG_HALF_DUPLEX);
पूर्ण
EXPORT_SYMBOL_GPL(mxs_pcm_platक्रमm_रेजिस्टर);

MODULE_LICENSE("GPL");
