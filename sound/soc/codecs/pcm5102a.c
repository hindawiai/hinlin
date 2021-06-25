<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम the PCM5102A codec
 *
 * Author:	Florian Meier <florian.meier@koalo.de>
 *		Copyright 2013
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <sound/soc.h>

अटल काष्ठा snd_soc_dai_driver pcm5102a_dai = अणु
	.name = "pcm5102a-hifi",
	.playback = अणु
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_192000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
			   SNDRV_PCM_FMTBIT_S24_LE |
			   SNDRV_PCM_FMTBIT_S32_LE
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_component_driver soc_component_dev_pcm5102a = अणु
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक pcm5102a_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev, &soc_component_dev_pcm5102a,
			&pcm5102a_dai, 1);
पूर्ण

अटल स्थिर काष्ठा of_device_id pcm5102a_of_match[] = अणु
	अणु .compatible = "ti,pcm5102a", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pcm5102a_of_match);

अटल काष्ठा platक्रमm_driver pcm5102a_codec_driver = अणु
	.probe		= pcm5102a_probe,
	.driver		= अणु
		.name	= "pcm5102a-codec",
		.of_match_table = pcm5102a_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(pcm5102a_codec_driver);

MODULE_DESCRIPTION("ASoC PCM5102A codec driver");
MODULE_AUTHOR("Florian Meier <florian.meier@koalo.de>");
MODULE_LICENSE("GPL v2");
