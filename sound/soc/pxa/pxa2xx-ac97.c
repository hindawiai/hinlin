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
#समावेश <linux/dma/pxa-dma.h>

#समावेश <sound/ac97/controller.h>
#समावेश <sound/core.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/soc.h>
#समावेश <sound/pxa2xx-lib.h>
#समावेश <sound/dmaengine_pcm.h>

#समावेश <mach/hardware.h>
#समावेश <mach/regs-ac97.h>
#समावेश <mach/audपन.स>

अटल व्योम pxa2xx_ac97_warm_reset(काष्ठा ac97_controller *adrv)
अणु
	pxa2xx_ac97_try_warm_reset();

	pxa2xx_ac97_finish_reset();
पूर्ण

अटल व्योम pxa2xx_ac97_cold_reset(काष्ठा ac97_controller *adrv)
अणु
	pxa2xx_ac97_try_cold_reset();

	pxa2xx_ac97_finish_reset();
पूर्ण

अटल पूर्णांक pxa2xx_ac97_पढ़ो_actrl(काष्ठा ac97_controller *adrv, पूर्णांक slot,
				  अचिन्हित लघु reg)
अणु
	वापस pxa2xx_ac97_पढ़ो(slot, reg);
पूर्ण

अटल पूर्णांक pxa2xx_ac97_ग_लिखो_actrl(काष्ठा ac97_controller *adrv, पूर्णांक slot,
				   अचिन्हित लघु reg, अचिन्हित लघु val)
अणु
	वापस pxa2xx_ac97_ग_लिखो(slot, reg, val);
पूर्ण

अटल काष्ठा ac97_controller_ops pxa2xx_ac97_ops = अणु
	.पढ़ो	= pxa2xx_ac97_पढ़ो_actrl,
	.ग_लिखो	= pxa2xx_ac97_ग_लिखो_actrl,
	.warm_reset	= pxa2xx_ac97_warm_reset,
	.reset	= pxa2xx_ac97_cold_reset,
पूर्ण;

अटल काष्ठा snd_dmaengine_dai_dma_data pxa2xx_ac97_pcm_stereo_in = अणु
	.addr		= __PREG(PCDR),
	.addr_width	= DMA_SLAVE_BUSWIDTH_4_BYTES,
	.chan_name	= "pcm_pcm_stereo_in",
	.maxburst	= 32,
पूर्ण;

अटल काष्ठा snd_dmaengine_dai_dma_data pxa2xx_ac97_pcm_stereo_out = अणु
	.addr		= __PREG(PCDR),
	.addr_width	= DMA_SLAVE_BUSWIDTH_4_BYTES,
	.chan_name	= "pcm_pcm_stereo_out",
	.maxburst	= 32,
पूर्ण;

अटल काष्ठा snd_dmaengine_dai_dma_data pxa2xx_ac97_pcm_aux_mono_out = अणु
	.addr		= __PREG(MODR),
	.addr_width	= DMA_SLAVE_BUSWIDTH_2_BYTES,
	.chan_name	= "pcm_aux_mono_out",
	.maxburst	= 16,
पूर्ण;

अटल काष्ठा snd_dmaengine_dai_dma_data pxa2xx_ac97_pcm_aux_mono_in = अणु
	.addr		= __PREG(MODR),
	.addr_width	= DMA_SLAVE_BUSWIDTH_2_BYTES,
	.chan_name	= "pcm_aux_mono_in",
	.maxburst	= 16,
पूर्ण;

अटल काष्ठा snd_dmaengine_dai_dma_data pxa2xx_ac97_pcm_mic_mono_in = अणु
	.addr		= __PREG(MCDR),
	.addr_width	= DMA_SLAVE_BUSWIDTH_2_BYTES,
	.chan_name	= "pcm_aux_mic_mono",
	.maxburst	= 16,
पूर्ण;

अटल पूर्णांक pxa2xx_ac97_hअगरi_startup(काष्ठा snd_pcm_substream *substream,
				    काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा snd_dmaengine_dai_dma_data *dma_data;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		dma_data = &pxa2xx_ac97_pcm_stereo_out;
	अन्यथा
		dma_data = &pxa2xx_ac97_pcm_stereo_in;

	snd_soc_dai_set_dma_data(cpu_dai, substream, dma_data);

	वापस 0;
पूर्ण

अटल पूर्णांक pxa2xx_ac97_aux_startup(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा snd_dmaengine_dai_dma_data *dma_data;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		dma_data = &pxa2xx_ac97_pcm_aux_mono_out;
	अन्यथा
		dma_data = &pxa2xx_ac97_pcm_aux_mono_in;

	snd_soc_dai_set_dma_data(cpu_dai, substream, dma_data);

	वापस 0;
पूर्ण

अटल पूर्णांक pxa2xx_ac97_mic_startup(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_soc_dai *cpu_dai)
अणु
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		वापस -ENODEV;
	snd_soc_dai_set_dma_data(cpu_dai, substream,
				 &pxa2xx_ac97_pcm_mic_mono_in);

	वापस 0;
पूर्ण

#घोषणा PXA2XX_AC97_RATES (SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_11025 |\
		SNDRV_PCM_RATE_16000 | SNDRV_PCM_RATE_22050 | SNDRV_PCM_RATE_44100 | \
		SNDRV_PCM_RATE_48000)

अटल स्थिर काष्ठा snd_soc_dai_ops pxa_ac97_hअगरi_dai_ops = अणु
	.startup	= pxa2xx_ac97_hअगरi_startup,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops pxa_ac97_aux_dai_ops = अणु
	.startup	= pxa2xx_ac97_aux_startup,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops pxa_ac97_mic_dai_ops = अणु
	.startup	= pxa2xx_ac97_mic_startup,
पूर्ण;

/*
 * There is only 1 physical AC97 पूर्णांकerface क्रम pxa2xx, but it
 * has extra fअगरo's that can be used क्रम aux DACs and ADCs.
 */
अटल काष्ठा snd_soc_dai_driver pxa_ac97_dai_driver[] = अणु
अणु
	.name = "pxa2xx-ac97",
	.playback = अणु
		.stream_name = "AC97 Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = PXA2XX_AC97_RATES,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,पूर्ण,
	.capture = अणु
		.stream_name = "AC97 Capture",
		.channels_min = 2,
		.channels_max = 2,
		.rates = PXA2XX_AC97_RATES,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,पूर्ण,
	.ops = &pxa_ac97_hअगरi_dai_ops,
पूर्ण,
अणु
	.name = "pxa2xx-ac97-aux",
	.playback = अणु
		.stream_name = "AC97 Aux Playback",
		.channels_min = 1,
		.channels_max = 1,
		.rates = PXA2XX_AC97_RATES,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,पूर्ण,
	.capture = अणु
		.stream_name = "AC97 Aux Capture",
		.channels_min = 1,
		.channels_max = 1,
		.rates = PXA2XX_AC97_RATES,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,पूर्ण,
	.ops = &pxa_ac97_aux_dai_ops,
पूर्ण,
अणु
	.name = "pxa2xx-ac97-mic",
	.capture = अणु
		.stream_name = "AC97 Mic Capture",
		.channels_min = 1,
		.channels_max = 1,
		.rates = PXA2XX_AC97_RATES,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,पूर्ण,
	.ops = &pxa_ac97_mic_dai_ops,
पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver pxa_ac97_component = अणु
	.name		= "pxa-ac97",
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

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id pxa2xx_ac97_dt_ids[] = अणु
	अणु .compatible = "marvell,pxa250-ac97", पूर्ण,
	अणु .compatible = "marvell,pxa270-ac97", पूर्ण,
	अणु .compatible = "marvell,pxa300-ac97", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pxa2xx_ac97_dt_ids);

#पूर्ण_अगर

अटल पूर्णांक pxa2xx_ac97_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा ac97_controller *ctrl;
	pxa2xx_audio_ops_t *pdata = pdev->dev.platक्रमm_data;
	व्योम **codecs_pdata;

	अगर (pdev->id != -1) अणु
		dev_err(&pdev->dev, "PXA2xx has only one AC97 port.\n");
		वापस -ENXIO;
	पूर्ण

	ret = pxa2xx_ac97_hw_probe(pdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "PXA2xx AC97 hw probe error (%d)\n", ret);
		वापस ret;
	पूर्ण

	codecs_pdata = pdata ? pdata->codec_pdata : शून्य;
	ctrl = snd_ac97_controller_रेजिस्टर(&pxa2xx_ac97_ops, &pdev->dev,
					    AC97_SLOTS_AVAILABLE_ALL,
					    codecs_pdata);
	अगर (IS_ERR(ctrl))
		वापस PTR_ERR(ctrl);

	platक्रमm_set_drvdata(pdev, ctrl);
	/* Punt most of the init to the SoC probe; we may need the machine
	 * driver to करो पूर्णांकeresting things with the घड़ीing to get us up
	 * and running.
	 */
	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev, &pxa_ac97_component,
					  pxa_ac97_dai_driver, ARRAY_SIZE(pxa_ac97_dai_driver));
पूर्ण

अटल पूर्णांक pxa2xx_ac97_dev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ac97_controller *ctrl = platक्रमm_get_drvdata(pdev);

	snd_ac97_controller_unरेजिस्टर(ctrl);
	pxa2xx_ac97_hw_हटाओ(pdev);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक pxa2xx_ac97_dev_suspend(काष्ठा device *dev)
अणु
	वापस pxa2xx_ac97_hw_suspend();
पूर्ण

अटल पूर्णांक pxa2xx_ac97_dev_resume(काष्ठा device *dev)
अणु
	वापस pxa2xx_ac97_hw_resume();
पूर्ण

अटल SIMPLE_DEV_PM_OPS(pxa2xx_ac97_pm_ops,
		pxa2xx_ac97_dev_suspend, pxa2xx_ac97_dev_resume);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver pxa2xx_ac97_driver = अणु
	.probe		= pxa2xx_ac97_dev_probe,
	.हटाओ		= pxa2xx_ac97_dev_हटाओ,
	.driver		= अणु
		.name	= "pxa2xx-ac97",
#अगर_घोषित CONFIG_PM_SLEEP
		.pm	= &pxa2xx_ac97_pm_ops,
#पूर्ण_अगर
		.of_match_table = of_match_ptr(pxa2xx_ac97_dt_ids),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(pxa2xx_ac97_driver);

MODULE_AUTHOR("Nicolas Pitre");
MODULE_DESCRIPTION("AC97 driver for the Intel PXA2xx chip");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:pxa2xx-ac97");
