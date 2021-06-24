<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * imx-pcm-dma-mx2.c  --  ALSA Soc Audio Layer
 *
 * Copyright 2009 Sascha Hauer <s.hauer@pengutronix.de>
 *
 * This code is based on code copyrighted by Freescale,
 * Liam Girdwood, Javier Martin and probably others.
 */
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/dmaengine_pcm.h>

#समावेश "imx-pcm.h"

अटल bool filter(काष्ठा dma_chan *chan, व्योम *param)
अणु
	अगर (!imx_dma_is_general_purpose(chan))
		वापस false;

	chan->निजी = param;

	वापस true;
पूर्ण

अटल स्थिर काष्ठा snd_dmaengine_pcm_config imx_dmaengine_pcm_config = अणु
	.prepare_slave_config = snd_dmaengine_pcm_prepare_slave_config,
	.compat_filter_fn = filter,
पूर्ण;

पूर्णांक imx_pcm_dma_init(काष्ठा platक्रमm_device *pdev, माप_प्रकार size)
अणु
	काष्ठा snd_dmaengine_pcm_config *config;

	config = devm_kzalloc(&pdev->dev,
			माप(काष्ठा snd_dmaengine_pcm_config), GFP_KERNEL);
	अगर (!config)
		वापस -ENOMEM;
	*config = imx_dmaengine_pcm_config;

	वापस devm_snd_dmaengine_pcm_रेजिस्टर(&pdev->dev,
		config,
		SND_DMAENGINE_PCM_FLAG_COMPAT);
पूर्ण
EXPORT_SYMBOL_GPL(imx_pcm_dma_init);

MODULE_LICENSE("GPL");
