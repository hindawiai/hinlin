<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/sound/pxa2xx-ac97.c -- AC97 support क्रम the Intel PXA2xx chip.
 *
 * Author:	Nicolas Pitre
 * Created:	Dec 02, 2004
 * Copyright:	MontaVista Software Inc.
 */

#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/initval.h>
#समावेश <sound/pxa2xx-lib.h>
#समावेश <sound/dmaengine_pcm.h>

#समावेश <mach/regs-ac97.h>
#समावेश <mach/audपन.स>

अटल व्योम pxa2xx_ac97_legacy_reset(काष्ठा snd_ac97 *ac97)
अणु
	अगर (!pxa2xx_ac97_try_cold_reset())
		pxa2xx_ac97_try_warm_reset();

	pxa2xx_ac97_finish_reset();
पूर्ण

अटल अचिन्हित लघु pxa2xx_ac97_legacy_पढ़ो(काष्ठा snd_ac97 *ac97,
					      अचिन्हित लघु reg)
अणु
	पूर्णांक ret;

	ret = pxa2xx_ac97_पढ़ो(ac97->num, reg);
	अगर (ret < 0)
		वापस 0;
	अन्यथा
		वापस (अचिन्हित लघु)(ret & 0xffff);
पूर्ण

अटल व्योम pxa2xx_ac97_legacy_ग_लिखो(काष्ठा snd_ac97 *ac97,
				     अचिन्हित लघु reg, अचिन्हित लघु val)
अणु
	पूर्णांक __always_unused ret;

	ret = pxa2xx_ac97_ग_लिखो(ac97->num, reg, val);
पूर्ण

अटल स्थिर काष्ठा snd_ac97_bus_ops pxa2xx_ac97_ops = अणु
	.पढ़ो	= pxa2xx_ac97_legacy_पढ़ो,
	.ग_लिखो	= pxa2xx_ac97_legacy_ग_लिखो,
	.reset	= pxa2xx_ac97_legacy_reset,
पूर्ण;

अटल काष्ठा snd_pcm *pxa2xx_ac97_pcm;
अटल काष्ठा snd_ac97 *pxa2xx_ac97_ac97;

अटल पूर्णांक pxa2xx_ac97_pcm_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	pxa2xx_audio_ops_t *platक्रमm_ops;
	पूर्णांक ret, i;

	ret = pxa2xx_pcm_खोलो(substream);
	अगर (ret)
		वापस ret;

	runसमय->hw.channels_min = 2;
	runसमय->hw.channels_max = 2;

	i = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) ?
		AC97_RATES_FRONT_DAC : AC97_RATES_ADC;
	runसमय->hw.rates = pxa2xx_ac97_ac97->rates[i];
	snd_pcm_limit_hw_rates(runसमय);

	platक्रमm_ops = substream->pcm->card->dev->platक्रमm_data;
	अगर (platक्रमm_ops && platक्रमm_ops->startup) अणु
		ret = platक्रमm_ops->startup(substream, platक्रमm_ops->priv);
		अगर (ret < 0)
			pxa2xx_pcm_बंद(substream);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक pxa2xx_ac97_pcm_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	pxa2xx_audio_ops_t *platक्रमm_ops;

	platक्रमm_ops = substream->pcm->card->dev->platक्रमm_data;
	अगर (platक्रमm_ops && platक्रमm_ops->shutकरोwn)
		platक्रमm_ops->shutकरोwn(substream, platक्रमm_ops->priv);

	वापस 0;
पूर्ण

अटल पूर्णांक pxa2xx_ac97_pcm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक reg = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) ?
		  AC97_PCM_FRONT_DAC_RATE : AC97_PCM_LR_ADC_RATE;
	पूर्णांक ret;

	ret = pxa2xx_pcm_prepare(substream);
	अगर (ret < 0)
		वापस ret;

	वापस snd_ac97_set_rate(pxa2xx_ac97_ac97, reg, runसमय->rate);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP

अटल पूर्णांक pxa2xx_ac97_करो_suspend(काष्ठा snd_card *card)
अणु
	pxa2xx_audio_ops_t *platक्रमm_ops = card->dev->platक्रमm_data;

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3cold);
	snd_ac97_suspend(pxa2xx_ac97_ac97);
	अगर (platक्रमm_ops && platक्रमm_ops->suspend)
		platक्रमm_ops->suspend(platक्रमm_ops->priv);

	वापस pxa2xx_ac97_hw_suspend();
पूर्ण

अटल पूर्णांक pxa2xx_ac97_करो_resume(काष्ठा snd_card *card)
अणु
	pxa2xx_audio_ops_t *platक्रमm_ops = card->dev->platक्रमm_data;
	पूर्णांक rc;

	rc = pxa2xx_ac97_hw_resume();
	अगर (rc)
		वापस rc;

	अगर (platक्रमm_ops && platक्रमm_ops->resume)
		platक्रमm_ops->resume(platक्रमm_ops->priv);
	snd_ac97_resume(pxa2xx_ac97_ac97);
	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);

	वापस 0;
पूर्ण

अटल पूर्णांक pxa2xx_ac97_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	अगर (card)
		ret = pxa2xx_ac97_करो_suspend(card);

	वापस ret;
पूर्ण

अटल पूर्णांक pxa2xx_ac97_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	अगर (card)
		ret = pxa2xx_ac97_करो_resume(card);

	वापस ret;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(pxa2xx_ac97_pm_ops, pxa2xx_ac97_suspend, pxa2xx_ac97_resume);
#पूर्ण_अगर

अटल स्थिर काष्ठा snd_pcm_ops pxa2xx_ac97_pcm_ops = अणु
	.खोलो		= pxa2xx_ac97_pcm_खोलो,
	.बंद		= pxa2xx_ac97_pcm_बंद,
	.hw_params	= pxa2xx_pcm_hw_params,
	.hw_मुक्त	= pxa2xx_pcm_hw_मुक्त,
	.prepare	= pxa2xx_ac97_pcm_prepare,
	.trigger	= pxa2xx_pcm_trigger,
	.poपूर्णांकer	= pxa2xx_pcm_poपूर्णांकer,
	.mmap		= pxa2xx_pcm_mmap,
पूर्ण;


अटल पूर्णांक pxa2xx_ac97_pcm_new(काष्ठा snd_card *card)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक stream, ret;

	ret = snd_pcm_new(card, "PXA2xx-PCM", 0, 1, 1, &pcm);
	अगर (ret)
		जाओ out;

	pcm->निजी_मुक्त = pxa2xx_pcm_मुक्त_dma_buffers;

	ret = dma_coerce_mask_and_coherent(card->dev, DMA_BIT_MASK(32));
	अगर (ret)
		जाओ out;

	stream = SNDRV_PCM_STREAM_PLAYBACK;
	snd_pcm_set_ops(pcm, stream, &pxa2xx_ac97_pcm_ops);
	ret = pxa2xx_pcm_pपुनः_स्मृतिate_dma_buffer(pcm, stream);
	अगर (ret)
		जाओ out;

	stream = SNDRV_PCM_STREAM_CAPTURE;
	snd_pcm_set_ops(pcm, stream, &pxa2xx_ac97_pcm_ops);
	ret = pxa2xx_pcm_pपुनः_स्मृतिate_dma_buffer(pcm, stream);
	अगर (ret)
		जाओ out;

	pxa2xx_ac97_pcm = pcm;
	ret = 0;

 out:
	वापस ret;
पूर्ण

अटल पूर्णांक pxa2xx_ac97_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा snd_card *card;
	काष्ठा snd_ac97_bus *ac97_bus;
	काष्ठा snd_ac97_ढाँचा ac97_ढाँचा;
	पूर्णांक ret;
	pxa2xx_audio_ops_t *pdata = dev->dev.platक्रमm_data;

	अगर (dev->id >= 0) अणु
		dev_err(&dev->dev, "PXA2xx has only one AC97 port.\n");
		ret = -ENXIO;
		जाओ err_dev;
	पूर्ण

	ret = snd_card_new(&dev->dev, SNDRV_DEFAULT_IDX1, SNDRV_DEFAULT_STR1,
			   THIS_MODULE, 0, &card);
	अगर (ret < 0)
		जाओ err;

	strscpy(card->driver, dev->dev.driver->name, माप(card->driver));

	ret = pxa2xx_ac97_pcm_new(card);
	अगर (ret)
		जाओ err;

	ret = pxa2xx_ac97_hw_probe(dev);
	अगर (ret)
		जाओ err;

	ret = snd_ac97_bus(card, 0, &pxa2xx_ac97_ops, शून्य, &ac97_bus);
	अगर (ret)
		जाओ err_हटाओ;
	स_रखो(&ac97_ढाँचा, 0, माप(ac97_ढाँचा));
	ret = snd_ac97_mixer(ac97_bus, &ac97_ढाँचा, &pxa2xx_ac97_ac97);
	अगर (ret)
		जाओ err_हटाओ;

	snम_लिखो(card->लघुname, माप(card->लघुname),
		 "%s", snd_ac97_get_लघु_name(pxa2xx_ac97_ac97));
	snम_लिखो(card->दीर्घname, माप(card->दीर्घname),
		 "%s (%s)", dev->dev.driver->name, card->mixername);

	अगर (pdata && pdata->codec_pdata[0])
		snd_ac97_dev_add_pdata(ac97_bus->codec[0], pdata->codec_pdata[0]);
	ret = snd_card_रेजिस्टर(card);
	अगर (ret == 0) अणु
		platक्रमm_set_drvdata(dev, card);
		वापस 0;
	पूर्ण

err_हटाओ:
	pxa2xx_ac97_hw_हटाओ(dev);
err:
	अगर (card)
		snd_card_मुक्त(card);
err_dev:
	वापस ret;
पूर्ण

अटल पूर्णांक pxa2xx_ac97_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा snd_card *card = platक्रमm_get_drvdata(dev);

	अगर (card) अणु
		snd_card_मुक्त(card);
		pxa2xx_ac97_hw_हटाओ(dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pxa2xx_ac97_driver = अणु
	.probe		= pxa2xx_ac97_probe,
	.हटाओ		= pxa2xx_ac97_हटाओ,
	.driver		= अणु
		.name	= "pxa2xx-ac97",
#अगर_घोषित CONFIG_PM_SLEEP
		.pm	= &pxa2xx_ac97_pm_ops,
#पूर्ण_अगर
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(pxa2xx_ac97_driver);

MODULE_AUTHOR("Nicolas Pitre");
MODULE_DESCRIPTION("AC97 driver for the Intel PXA2xx chip");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:pxa2xx-ac97");
