<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ALSA SoC Voice Codec Interface क्रम TI DAVINCI processor
 *
 * Copyright (C) 2010 Texas Instruments.
 *
 * Author: Miguel Aguilar <miguel.aguilar@ridgerun.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/davinci_voicecodec.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>
#समावेश <sound/dmaengine_pcm.h>

#समावेश "edma-pcm.h"
#समावेश "davinci-i2s.h"

#घोषणा MOD_REG_BIT(val, mask, set) करो अणु \
	अगर (set) अणु \
		val |= mask; \
	पूर्ण अन्यथा अणु \
		val &= ~mask; \
	पूर्ण \
पूर्ण जबतक (0)

काष्ठा davinci_vcअगर_dev अणु
	काष्ठा davinci_vc *davinci_vc;
	काष्ठा snd_dmaengine_dai_dma_data dma_data[2];
	पूर्णांक dma_request[2];
पूर्ण;

अटल व्योम davinci_vcअगर_start(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा davinci_vcअगर_dev *davinci_vcअगर_dev =
			snd_soc_dai_get_drvdata(asoc_rtd_to_cpu(rtd, 0));
	काष्ठा davinci_vc *davinci_vc = davinci_vcअगर_dev->davinci_vc;
	u32 w;

	/* Start the sample generator and enable transmitter/receiver */
	w = पढ़ोl(davinci_vc->base + DAVINCI_VC_CTRL);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		MOD_REG_BIT(w, DAVINCI_VC_CTRL_RSTDAC, 0);
	अन्यथा
		MOD_REG_BIT(w, DAVINCI_VC_CTRL_RSTADC, 0);

	ग_लिखोl(w, davinci_vc->base + DAVINCI_VC_CTRL);
पूर्ण

अटल व्योम davinci_vcअगर_stop(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा davinci_vcअगर_dev *davinci_vcअगर_dev =
			snd_soc_dai_get_drvdata(asoc_rtd_to_cpu(rtd, 0));
	काष्ठा davinci_vc *davinci_vc = davinci_vcअगर_dev->davinci_vc;
	u32 w;

	/* Reset transmitter/receiver and sample rate/frame sync generators */
	w = पढ़ोl(davinci_vc->base + DAVINCI_VC_CTRL);
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		MOD_REG_BIT(w, DAVINCI_VC_CTRL_RSTDAC, 1);
	अन्यथा
		MOD_REG_BIT(w, DAVINCI_VC_CTRL_RSTADC, 1);

	ग_लिखोl(w, davinci_vc->base + DAVINCI_VC_CTRL);
पूर्ण

अटल पूर्णांक davinci_vcअगर_hw_params(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_hw_params *params,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा davinci_vcअगर_dev *davinci_vcअगर_dev = snd_soc_dai_get_drvdata(dai);
	काष्ठा davinci_vc *davinci_vc = davinci_vcअगर_dev->davinci_vc;
	u32 w;

	/* Restart the codec beक्रमe setup */
	davinci_vcअगर_stop(substream);
	davinci_vcअगर_start(substream);

	/* General line settings */
	ग_लिखोl(DAVINCI_VC_CTRL_MASK, davinci_vc->base + DAVINCI_VC_CTRL);

	ग_लिखोl(DAVINCI_VC_INT_MASK, davinci_vc->base + DAVINCI_VC_INTCLR);

	ग_लिखोl(DAVINCI_VC_INT_MASK, davinci_vc->base + DAVINCI_VC_INTEN);

	w = पढ़ोl(davinci_vc->base + DAVINCI_VC_CTRL);

	/* Determine xfer data type */
	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_U8:
		MOD_REG_BIT(w, DAVINCI_VC_CTRL_RD_BITS_8 |
			    DAVINCI_VC_CTRL_RD_UNSIGNED |
			    DAVINCI_VC_CTRL_WD_BITS_8 |
			    DAVINCI_VC_CTRL_WD_UNSIGNED, 1);
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S8:
		MOD_REG_BIT(w, DAVINCI_VC_CTRL_RD_BITS_8 |
			    DAVINCI_VC_CTRL_WD_BITS_8, 1);

		MOD_REG_BIT(w, DAVINCI_VC_CTRL_RD_UNSIGNED |
			    DAVINCI_VC_CTRL_WD_UNSIGNED, 0);
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S16_LE:
		MOD_REG_BIT(w, DAVINCI_VC_CTRL_RD_BITS_8 |
			    DAVINCI_VC_CTRL_RD_UNSIGNED |
			    DAVINCI_VC_CTRL_WD_BITS_8 |
			    DAVINCI_VC_CTRL_WD_UNSIGNED, 0);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "davinci-vcif: unsupported PCM format");
		वापस -EINVAL;
	पूर्ण

	ग_लिखोl(w, davinci_vc->base + DAVINCI_VC_CTRL);

	वापस 0;
पूर्ण

अटल पूर्णांक davinci_vcअगर_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
				काष्ठा snd_soc_dai *dai)
अणु
	पूर्णांक ret = 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		davinci_vcअगर_start(substream);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		davinci_vcअगर_stop(substream);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

#घोषणा DAVINCI_VCIF_RATES	SNDRV_PCM_RATE_8000_48000

अटल स्थिर काष्ठा snd_soc_dai_ops davinci_vcअगर_dai_ops = अणु
	.trigger	= davinci_vcअगर_trigger,
	.hw_params	= davinci_vcअगर_hw_params,
पूर्ण;

अटल पूर्णांक davinci_vcअगर_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा davinci_vcअगर_dev *dev = snd_soc_dai_get_drvdata(dai);

	dai->playback_dma_data = &dev->dma_data[SNDRV_PCM_STREAM_PLAYBACK];
	dai->capture_dma_data = &dev->dma_data[SNDRV_PCM_STREAM_CAPTURE];

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_dai_driver davinci_vcअगर_dai = अणु
	.probe = davinci_vcअगर_dai_probe,
	.playback = अणु
		.channels_min = 1,
		.channels_max = 2,
		.rates = DAVINCI_VCIF_RATES,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,पूर्ण,
	.capture = अणु
		.channels_min = 1,
		.channels_max = 2,
		.rates = DAVINCI_VCIF_RATES,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,पूर्ण,
	.ops = &davinci_vcअगर_dai_ops,

पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver davinci_vcअगर_component = अणु
	.name		= "davinci-vcif",
पूर्ण;

अटल पूर्णांक davinci_vcअगर_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा davinci_vc *davinci_vc = pdev->dev.platक्रमm_data;
	काष्ठा davinci_vcअगर_dev *davinci_vcअगर_dev;
	पूर्णांक ret;

	davinci_vcअगर_dev = devm_kzalloc(&pdev->dev,
					माप(काष्ठा davinci_vcअगर_dev),
					GFP_KERNEL);
	अगर (!davinci_vcअगर_dev)
		वापस -ENOMEM;

	/* DMA tx params */
	davinci_vcअगर_dev->davinci_vc = davinci_vc;
	davinci_vcअगर_dev->dma_data[SNDRV_PCM_STREAM_PLAYBACK].filter_data =
				&davinci_vc->davinci_vcअगर.dma_tx_channel;
	davinci_vcअगर_dev->dma_data[SNDRV_PCM_STREAM_PLAYBACK].addr =
				davinci_vc->davinci_vcअगर.dma_tx_addr;

	/* DMA rx params */
	davinci_vcअगर_dev->dma_data[SNDRV_PCM_STREAM_CAPTURE].filter_data =
				&davinci_vc->davinci_vcअगर.dma_rx_channel;
	davinci_vcअगर_dev->dma_data[SNDRV_PCM_STREAM_CAPTURE].addr =
				davinci_vc->davinci_vcअगर.dma_rx_addr;

	dev_set_drvdata(&pdev->dev, davinci_vcअगर_dev);

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					      &davinci_vcअगर_component,
					      &davinci_vcअगर_dai, 1);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "could not register dai\n");
		वापस ret;
	पूर्ण

	ret = edma_pcm_platक्रमm_रेजिस्टर(&pdev->dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "register PCM failed: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver davinci_vcअगर_driver = अणु
	.probe		= davinci_vcअगर_probe,
	.driver		= अणु
		.name	= "davinci-vcif",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(davinci_vcअगर_driver);

MODULE_AUTHOR("Miguel Aguilar");
MODULE_DESCRIPTION("Texas Instruments DaVinci ASoC Voice Codec Interface");
MODULE_LICENSE("GPL");
