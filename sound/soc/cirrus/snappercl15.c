<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * snappercl15.c -- SoC audio क्रम Bluewater Systems Snapper CL15 module
 *
 * Copyright (C) 2008 Bluewater Systems Ltd
 * Author: Ryan Mallon
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/soc/cirrus/ep93xx.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>

#समावेश <यंत्र/mach-types.h>

#समावेश "../codecs/tlv320aic23.h"

#घोषणा CODEC_CLOCK 5644800

अटल पूर्णांक snappercl15_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	पूर्णांक err;

	err = snd_soc_dai_set_sysclk(codec_dai, 0, CODEC_CLOCK, 
				     SND_SOC_CLOCK_IN);
	अगर (err)
		वापस err;

	err = snd_soc_dai_set_sysclk(cpu_dai, 0, CODEC_CLOCK, 
				     SND_SOC_CLOCK_OUT);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops snappercl15_ops = अणु
	.hw_params	= snappercl15_hw_params,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget tlv320aic23_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_LINE("Line In", शून्य),
	SND_SOC_DAPM_MIC("Mic Jack", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route audio_map[] = अणु
	अणु"Headphone Jack", शून्य, "LHPOUT"पूर्ण,
	अणु"Headphone Jack", शून्य, "RHPOUT"पूर्ण,

	अणु"LLINEIN", शून्य, "Line In"पूर्ण,
	अणु"RLINEIN", शून्य, "Line In"पूर्ण,

	अणु"MICIN", शून्य, "Mic Jack"पूर्ण,
पूर्ण;

SND_SOC_DAILINK_DEFS(aic23,
	DAILINK_COMP_ARRAY(COMP_CPU("ep93xx-i2s")),
	DAILINK_COMP_ARRAY(COMP_CODEC("tlv320aic23-codec.0-001a",
				      "tlv320aic23-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("ep93xx-i2s")));

अटल काष्ठा snd_soc_dai_link snappercl15_dai = अणु
	.name		= "tlv320aic23",
	.stream_name	= "AIC23",
	.dai_fmt	= SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			  SND_SOC_DAIFMT_CBS_CFS,
	.ops		= &snappercl15_ops,
	SND_SOC_DAILINK_REG(aic23),
पूर्ण;

अटल काष्ठा snd_soc_card snd_soc_snappercl15 = अणु
	.name		= "Snapper CL15",
	.owner		= THIS_MODULE,
	.dai_link	= &snappercl15_dai,
	.num_links	= 1,

	.dapm_widमाला_लो		= tlv320aic23_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(tlv320aic23_dapm_widमाला_लो),
	.dapm_routes		= audio_map,
	.num_dapm_routes	= ARRAY_SIZE(audio_map),
पूर्ण;

अटल पूर्णांक snappercl15_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = &snd_soc_snappercl15;
	पूर्णांक ret;

	ret = ep93xx_i2s_acquire();
	अगर (ret)
		वापस ret;

	card->dev = &pdev->dev;

	ret = snd_soc_रेजिस्टर_card(card);
	अगर (ret) अणु
		dev_err(&pdev->dev, "snd_soc_register_card() failed: %d\n",
			ret);
		ep93xx_i2s_release();
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक snappercl15_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = platक्रमm_get_drvdata(pdev);

	snd_soc_unरेजिस्टर_card(card);
	ep93xx_i2s_release();

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver snappercl15_driver = अणु
	.driver		= अणु
		.name	= "snappercl15-audio",
	पूर्ण,
	.probe		= snappercl15_probe,
	.हटाओ		= snappercl15_हटाओ,
पूर्ण;

module_platक्रमm_driver(snappercl15_driver);

MODULE_AUTHOR("Ryan Mallon");
MODULE_DESCRIPTION("ALSA SoC Snapper CL15");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:snappercl15-audio");
