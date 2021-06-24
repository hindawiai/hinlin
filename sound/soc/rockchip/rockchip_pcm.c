<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2018 Rockchip Electronics Co. Ltd.
 */

#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/dmaengine_pcm.h>

#समावेश "rockchip_pcm.h"

अटल स्थिर काष्ठा snd_pcm_hardware snd_rockchip_hardware = अणु
	.info			= SNDRV_PCM_INFO_MMAP |
				  SNDRV_PCM_INFO_MMAP_VALID |
				  SNDRV_PCM_INFO_PAUSE |
				  SNDRV_PCM_INFO_RESUME |
				  SNDRV_PCM_INFO_INTERLEAVED,
	.period_bytes_min	= 32,
	.period_bytes_max	= 8192,
	.periods_min		= 1,
	.periods_max		= 52,
	.buffer_bytes_max	= 64 * 1024,
	.fअगरo_size		= 32,
पूर्ण;

अटल स्थिर काष्ठा snd_dmaengine_pcm_config rk_dmaengine_pcm_config = अणु
	.pcm_hardware = &snd_rockchip_hardware,
	.prepare_slave_config = snd_dmaengine_pcm_prepare_slave_config,
	.pपुनः_स्मृति_buffer_size = 32 * 1024,
पूर्ण;

पूर्णांक rockchip_pcm_platक्रमm_रेजिस्टर(काष्ठा device *dev)
अणु
	वापस devm_snd_dmaengine_pcm_रेजिस्टर(dev, &rk_dmaengine_pcm_config,
		SND_DMAENGINE_PCM_FLAG_COMPAT);
पूर्ण
EXPORT_SYMBOL_GPL(rockchip_pcm_platक्रमm_रेजिस्टर);

MODULE_LICENSE("GPL v2");
