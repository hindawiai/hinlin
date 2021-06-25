<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/sound/arm/pxa2xx-pcm.c -- ALSA PCM पूर्णांकerface क्रम the Intel PXA2xx chip
 *
 * Author:	Nicolas Pitre
 * Created:	Nov 30, 2004
 * Copyright:	(C) 2004 MontaVista Software, Inc.
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/of.h>

#समावेश <sound/core.h>
#समावेश <sound/soc.h>
#समावेश <sound/pxa2xx-lib.h>
#समावेश <sound/dmaengine_pcm.h>

अटल स्थिर काष्ठा snd_soc_component_driver pxa2xx_soc_platक्रमm = अणु
	.pcm_स्थिरruct	= pxa2xx_soc_pcm_new,
	.pcm_deकाष्ठा	= pxa2xx_soc_pcm_मुक्त,
	.खोलो		= pxa2xx_soc_pcm_खोलो,
	.बंद		= pxa2xx_soc_pcm_बंद,
	.hw_params	= pxa2xx_soc_pcm_hw_params,
	.hw_मुक्त	= pxa2xx_soc_pcm_hw_मुक्त,
	.prepare	= pxa2xx_soc_pcm_prepare,
	.trigger	= pxa2xx_soc_pcm_trigger,
	.poपूर्णांकer	= pxa2xx_soc_pcm_poपूर्णांकer,
	.mmap		= pxa2xx_soc_pcm_mmap,
पूर्ण;

अटल पूर्णांक pxa2xx_soc_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev, &pxa2xx_soc_platक्रमm,
					       शून्य, 0);
पूर्ण

अटल काष्ठा platक्रमm_driver pxa_pcm_driver = अणु
	.driver = अणु
		.name = "pxa-pcm-audio",
	पूर्ण,

	.probe = pxa2xx_soc_platक्रमm_probe,
पूर्ण;

module_platक्रमm_driver(pxa_pcm_driver);

MODULE_AUTHOR("Nicolas Pitre");
MODULE_DESCRIPTION("Intel PXA2xx PCM DMA module");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:pxa-pcm-audio");
