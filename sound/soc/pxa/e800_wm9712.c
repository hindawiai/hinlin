<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * e800-wm9712.c  --  SoC audio क्रम e800
 *
 * Copyright 2007 (c) Ian Molton <spyro@f2s.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/gpपन.स>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <mach/audपन.स>
#समावेश <mach/eseries-gpपन.स>

अटल पूर्णांक e800_spk_amp_event(काष्ठा snd_soc_dapm_widget *w,
				काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	अगर (event & SND_SOC_DAPM_PRE_PMU)
		gpio_set_value(GPIO_E800_SPK_AMP_ON, 1);
	अन्यथा अगर (event & SND_SOC_DAPM_POST_PMD)
		gpio_set_value(GPIO_E800_SPK_AMP_ON, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक e800_hp_amp_event(काष्ठा snd_soc_dapm_widget *w,
				काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	अगर (event & SND_SOC_DAPM_PRE_PMU)
		gpio_set_value(GPIO_E800_HP_AMP_OFF, 0);
	अन्यथा अगर (event & SND_SOC_DAPM_POST_PMD)
		gpio_set_value(GPIO_E800_HP_AMP_OFF, 1);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget e800_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_MIC("Mic (Internal1)", शून्य),
	SND_SOC_DAPM_MIC("Mic (Internal2)", शून्य),
	SND_SOC_DAPM_SPK("Speaker", शून्य),
	SND_SOC_DAPM_PGA_E("Headphone Amp", SND_SOC_NOPM, 0, 0, शून्य, 0,
			e800_hp_amp_event, SND_SOC_DAPM_PRE_PMU |
			SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_PGA_E("Speaker Amp", SND_SOC_NOPM, 0, 0, शून्य, 0,
			e800_spk_amp_event, SND_SOC_DAPM_PRE_PMU |
			SND_SOC_DAPM_POST_PMD),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route audio_map[] = अणु
	अणु"Headphone Jack", शून्य, "HPOUTL"पूर्ण,
	अणु"Headphone Jack", शून्य, "HPOUTR"पूर्ण,
	अणु"Headphone Jack", शून्य, "Headphone Amp"पूर्ण,

	अणु"Speaker Amp", शून्य, "MONOOUT"पूर्ण,
	अणु"Speaker", शून्य, "Speaker Amp"पूर्ण,

	अणु"MIC1", शून्य, "Mic (Internal1)"पूर्ण,
	अणु"MIC2", शून्य, "Mic (Internal2)"पूर्ण,
पूर्ण;


SND_SOC_DAILINK_DEFS(ac97,
	DAILINK_COMP_ARRAY(COMP_CPU("pxa2xx-ac97")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm9712-codec", "wm9712-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("pxa-pcm-audio")));

SND_SOC_DAILINK_DEFS(ac97_aux,
	DAILINK_COMP_ARRAY(COMP_CPU("pxa2xx-ac97-aux")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm9712-codec", "wm9712-aux")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("pxa-pcm-audio")));

अटल काष्ठा snd_soc_dai_link e800_dai[] = अणु
	अणु
		.name = "AC97",
		.stream_name = "AC97 HiFi",
		SND_SOC_DAILINK_REG(ac97),
	पूर्ण,
	अणु
		.name = "AC97 Aux",
		.stream_name = "AC97 Aux",
		SND_SOC_DAILINK_REG(ac97_aux),
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_card e800 = अणु
	.name = "Toshiba e800",
	.owner = THIS_MODULE,
	.dai_link = e800_dai,
	.num_links = ARRAY_SIZE(e800_dai),

	.dapm_widमाला_लो = e800_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(e800_dapm_widमाला_लो),
	.dapm_routes = audio_map,
	.num_dapm_routes = ARRAY_SIZE(audio_map),
पूर्ण;

अटल काष्ठा gpio e800_audio_gpios[] = अणु
	अणु GPIO_E800_SPK_AMP_ON, GPIOF_OUT_INIT_HIGH, "Headphone amp" पूर्ण,
	अणु GPIO_E800_HP_AMP_OFF, GPIOF_OUT_INIT_HIGH, "Speaker amp" पूर्ण,
पूर्ण;

अटल पूर्णांक e800_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = &e800;
	पूर्णांक ret;

	ret = gpio_request_array(e800_audio_gpios,
				 ARRAY_SIZE(e800_audio_gpios));
	अगर (ret)
		वापस ret;

	card->dev = &pdev->dev;

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
	अगर (ret) अणु
		dev_err(&pdev->dev, "snd_soc_register_card() failed: %d\n",
			ret);
		gpio_मुक्त_array(e800_audio_gpios, ARRAY_SIZE(e800_audio_gpios));
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक e800_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	gpio_मुक्त_array(e800_audio_gpios, ARRAY_SIZE(e800_audio_gpios));
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver e800_driver = अणु
	.driver		= अणु
		.name	= "e800-audio",
		.pm     = &snd_soc_pm_ops,
	पूर्ण,
	.probe		= e800_probe,
	.हटाओ		= e800_हटाओ,
पूर्ण;

module_platक्रमm_driver(e800_driver);

/* Module inक्रमmation */
MODULE_AUTHOR("Ian Molton <spyro@f2s.com>");
MODULE_DESCRIPTION("ALSA SoC driver for e800");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:e800-audio");
