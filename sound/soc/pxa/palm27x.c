<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/sound/soc/pxa/palm27x.c
 *
 * SoC Audio driver क्रम Palm T|X, T5 and LअगरeDrive
 *
 * based on tosa.c
 *
 * Copyright (C) 2008 Marek Vasut <marek.vasut@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/device.h>
#समावेश <linux/gpपन.स>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/jack.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <mach/audपन.स>
#समावेश <linux/platक्रमm_data/asoc-palm27x.h>

अटल काष्ठा snd_soc_jack hs_jack;

/* Headphones jack detection DAPM pins */
अटल काष्ठा snd_soc_jack_pin hs_jack_pins[] = अणु
	अणु
		.pin    = "Headphone Jack",
		.mask   = SND_JACK_HEADPHONE,
	पूर्ण,
पूर्ण;

/* Headphones jack detection gpios */
अटल काष्ठा snd_soc_jack_gpio hs_jack_gpios[] = अणु
	[0] = अणु
		/* gpio is set on per-platक्रमm basis */
		.name           = "hp-gpio",
		.report         = SND_JACK_HEADPHONE,
		.debounce_समय	= 200,
	पूर्ण,
पूर्ण;

/* Palm27x machine dapm widमाला_लो */
अटल स्थिर काष्ठा snd_soc_dapm_widget palm27x_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_SPK("Ext. Speaker", शून्य),
	SND_SOC_DAPM_MIC("Ext. Microphone", शून्य),
पूर्ण;

/* PalmTX audio map */
अटल स्थिर काष्ठा snd_soc_dapm_route audio_map[] = अणु
	/* headphone connected to HPOUTL, HPOUTR */
	अणु"Headphone Jack", शून्य, "HPOUTL"पूर्ण,
	अणु"Headphone Jack", शून्य, "HPOUTR"पूर्ण,

	/* ext speaker connected to ROUT2, LOUT2 */
	अणु"Ext. Speaker", शून्य, "LOUT2"पूर्ण,
	अणु"Ext. Speaker", शून्य, "ROUT2"पूर्ण,

	/* mic connected to MIC1 */
	अणु"MIC1", शून्य, "Ext. Microphone"पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_card palm27x_asoc;

अटल पूर्णांक palm27x_ac97_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	पूर्णांक err;

	/* Jack detection API stuff */
	err = snd_soc_card_jack_new(rtd->card, "Headphone Jack",
				    SND_JACK_HEADPHONE, &hs_jack, hs_jack_pins,
				    ARRAY_SIZE(hs_jack_pins));
	अगर (err)
		वापस err;

	err = snd_soc_jack_add_gpios(&hs_jack, ARRAY_SIZE(hs_jack_gpios),
				hs_jack_gpios);

	वापस err;
पूर्ण

SND_SOC_DAILINK_DEFS(hअगरi,
	DAILINK_COMP_ARRAY(COMP_CPU("pxa2xx-ac97")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm9712-codec", "wm9712-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("pxa-pcm-audio")));

SND_SOC_DAILINK_DEFS(aux,
	DAILINK_COMP_ARRAY(COMP_CPU("pxa2xx-ac97-aux")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm9712-codec", "wm9712-aux")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("pxa-pcm-audio")));

अटल काष्ठा snd_soc_dai_link palm27x_dai[] = अणु
अणु
	.name = "AC97 HiFi",
	.stream_name = "AC97 HiFi",
	.init = palm27x_ac97_init,
	SND_SOC_DAILINK_REG(hअगरi),
पूर्ण,
अणु
	.name = "AC97 Aux",
	.stream_name = "AC97 Aux",
	SND_SOC_DAILINK_REG(aux),
पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_card palm27x_asoc = अणु
	.name = "Palm/PXA27x",
	.owner = THIS_MODULE,
	.dai_link = palm27x_dai,
	.num_links = ARRAY_SIZE(palm27x_dai),
	.dapm_widमाला_लो = palm27x_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(palm27x_dapm_widमाला_लो),
	.dapm_routes = audio_map,
	.num_dapm_routes = ARRAY_SIZE(audio_map),
	.fully_routed = true,
पूर्ण;

अटल पूर्णांक palm27x_asoc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	अगर (!(machine_is_palmtx() || machine_is_palmt5() ||
		machine_is_palmld() || machine_is_palmte2()))
		वापस -ENODEV;

	अगर (!pdev->dev.platक्रमm_data) अणु
		dev_err(&pdev->dev, "please supply platform_data\n");
		वापस -ENODEV;
	पूर्ण

	hs_jack_gpios[0].gpio = ((काष्ठा palm27x_asoc_info *)
			(pdev->dev.platक्रमm_data))->jack_gpio;

	palm27x_asoc.dev = &pdev->dev;

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, &palm27x_asoc);
	अगर (ret)
		dev_err(&pdev->dev, "snd_soc_register_card() failed: %d\n",
			ret);
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver palm27x_wm9712_driver = अणु
	.probe		= palm27x_asoc_probe,
	.driver		= अणु
		.name		= "palm27x-asoc",
		.pm     = &snd_soc_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(palm27x_wm9712_driver);

/* Module inक्रमmation */
MODULE_AUTHOR("Marek Vasut <marek.vasut@gmail.com>");
MODULE_DESCRIPTION("ALSA SoC Palm T|X, T5 and LifeDrive");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:palm27x-asoc");
