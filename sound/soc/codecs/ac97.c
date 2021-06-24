<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ac97.c  --  ALSA Soc AC97 codec support
 *
 * Copyright 2005 Wolfson Microelectronics PLC.
 * Author: Liam Girdwood <lrg@slimlogic.co.uk>
 *
 * Generic AC97 support.
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>

अटल स्थिर काष्ठा snd_soc_dapm_widget ac97_widमाला_लो[] = अणु
	SND_SOC_DAPM_INPUT("RX"),
	SND_SOC_DAPM_OUTPUT("TX"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route ac97_routes[] = अणु
	अणु "AC97 Capture", शून्य, "RX" पूर्ण,
	अणु "TX", शून्य, "AC97 Playback" पूर्ण,
पूर्ण;

अटल पूर्णांक ac97_prepare(काष्ठा snd_pcm_substream *substream,
			काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा snd_ac97 *ac97 = snd_soc_component_get_drvdata(component);

	पूर्णांक reg = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) ?
		  AC97_PCM_FRONT_DAC_RATE : AC97_PCM_LR_ADC_RATE;
	वापस snd_ac97_set_rate(ac97, reg, substream->runसमय->rate);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops ac97_dai_ops = अणु
	.prepare	= ac97_prepare,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver ac97_dai = अणु
	.name = "ac97-hifi",
	.playback = अणु
		.stream_name = "AC97 Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_KNOT,
		.क्रमmats = SND_SOC_STD_AC97_FMTS,पूर्ण,
	.capture = अणु
		.stream_name = "AC97 Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_KNOT,
		.क्रमmats = SND_SOC_STD_AC97_FMTS,पूर्ण,
	.ops = &ac97_dai_ops,
पूर्ण;

अटल पूर्णांक ac97_soc_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_ac97 *ac97;
	काष्ठा snd_ac97_bus *ac97_bus;
	काष्ठा snd_ac97_ढाँचा ac97_ढाँचा;
	पूर्णांक ret;

	/* add codec as bus device क्रम standard ac97 */
	ret = snd_ac97_bus(component->card->snd_card, 0, soc_ac97_ops,
			   शून्य, &ac97_bus);
	अगर (ret < 0)
		वापस ret;

	स_रखो(&ac97_ढाँचा, 0, माप(काष्ठा snd_ac97_ढाँचा));
	ret = snd_ac97_mixer(ac97_bus, &ac97_ढाँचा, &ac97);
	अगर (ret < 0)
		वापस ret;

	snd_soc_component_set_drvdata(component, ac97);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक ac97_soc_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_ac97 *ac97 = snd_soc_component_get_drvdata(component);

	snd_ac97_suspend(ac97);

	वापस 0;
पूर्ण

अटल पूर्णांक ac97_soc_resume(काष्ठा snd_soc_component *component)
अणु

	काष्ठा snd_ac97 *ac97 = snd_soc_component_get_drvdata(component);

	snd_ac97_resume(ac97);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा ac97_soc_suspend शून्य
#घोषणा ac97_soc_resume शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_ac97 = अणु
	.probe			= ac97_soc_probe,
	.suspend		= ac97_soc_suspend,
	.resume			= ac97_soc_resume,
	.dapm_widमाला_लो		= ac97_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(ac97_widमाला_लो),
	.dapm_routes		= ac97_routes,
	.num_dapm_routes	= ARRAY_SIZE(ac97_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक ac97_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
			&soc_component_dev_ac97, &ac97_dai, 1);
पूर्ण

अटल पूर्णांक ac97_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ac97_codec_driver = अणु
	.driver = अणु
		.name = "ac97-codec",
	पूर्ण,

	.probe = ac97_probe,
	.हटाओ = ac97_हटाओ,
पूर्ण;

module_platक्रमm_driver(ac97_codec_driver);

MODULE_DESCRIPTION("Soc Generic AC97 driver");
MODULE_AUTHOR("Liam Girdwood");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:ac97-codec");
