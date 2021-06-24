<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * e740-wm9705.c  --  SoC audio क्रम e740
 *
 * Copyright 2007 (c) Ian Molton <spyro@f2s.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/gpपन.स>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>

#समावेश <mach/audपन.स>
#समावेश <mach/eseries-gpपन.स>

#समावेश <यंत्र/mach-types.h>

#घोषणा E740_AUDIO_OUT 1
#घोषणा E740_AUDIO_IN  2

अटल पूर्णांक e740_audio_घातer;

अटल व्योम e740_sync_audio_घातer(पूर्णांक status)
अणु
	gpio_set_value(GPIO_E740_WM9705_nAVDD2, !status);
	gpio_set_value(GPIO_E740_AMP_ON, (status & E740_AUDIO_OUT) ? 1 : 0);
	gpio_set_value(GPIO_E740_MIC_ON, (status & E740_AUDIO_IN) ? 1 : 0);
पूर्ण

अटल पूर्णांक e740_mic_amp_event(काष्ठा snd_soc_dapm_widget *w,
				काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	अगर (event & SND_SOC_DAPM_PRE_PMU)
		e740_audio_घातer |= E740_AUDIO_IN;
	अन्यथा अगर (event & SND_SOC_DAPM_POST_PMD)
		e740_audio_घातer &= ~E740_AUDIO_IN;

	e740_sync_audio_घातer(e740_audio_घातer);

	वापस 0;
पूर्ण

अटल पूर्णांक e740_output_amp_event(काष्ठा snd_soc_dapm_widget *w,
				काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	अगर (event & SND_SOC_DAPM_PRE_PMU)
		e740_audio_घातer |= E740_AUDIO_OUT;
	अन्यथा अगर (event & SND_SOC_DAPM_POST_PMD)
		e740_audio_घातer &= ~E740_AUDIO_OUT;

	e740_sync_audio_घातer(e740_audio_घातer);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget e740_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_SPK("Speaker", शून्य),
	SND_SOC_DAPM_MIC("Mic (Internal)", शून्य),
	SND_SOC_DAPM_PGA_E("Output Amp", SND_SOC_NOPM, 0, 0, शून्य, 0,
			e740_output_amp_event, SND_SOC_DAPM_PRE_PMU |
			SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_PGA_E("Mic Amp", SND_SOC_NOPM, 0, 0, शून्य, 0,
			e740_mic_amp_event, SND_SOC_DAPM_PRE_PMU |
			SND_SOC_DAPM_POST_PMD),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route audio_map[] = अणु
	अणु"Output Amp", शून्य, "LOUT"पूर्ण,
	अणु"Output Amp", शून्य, "ROUT"पूर्ण,
	अणु"Output Amp", शून्य, "MONOOUT"पूर्ण,

	अणु"Speaker", शून्य, "Output Amp"पूर्ण,
	अणु"Headphone Jack", शून्य, "Output Amp"पूर्ण,

	अणु"MIC1", शून्य, "Mic Amp"पूर्ण,
	अणु"Mic Amp", शून्य, "Mic (Internal)"पूर्ण,
पूर्ण;

SND_SOC_DAILINK_DEFS(ac97,
	DAILINK_COMP_ARRAY(COMP_CPU("pxa2xx-ac97")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm9705-codec", "wm9705-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("pxa-pcm-audio")));

SND_SOC_DAILINK_DEFS(ac97_aux,
	DAILINK_COMP_ARRAY(COMP_CPU("pxa2xx-ac97-aux")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm9705-codec", "wm9705-aux")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("pxa-pcm-audio")));

अटल काष्ठा snd_soc_dai_link e740_dai[] = अणु
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

अटल काष्ठा snd_soc_card e740 = अणु
	.name = "Toshiba e740",
	.owner = THIS_MODULE,
	.dai_link = e740_dai,
	.num_links = ARRAY_SIZE(e740_dai),

	.dapm_widमाला_लो = e740_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(e740_dapm_widमाला_लो),
	.dapm_routes = audio_map,
	.num_dapm_routes = ARRAY_SIZE(audio_map),
	.fully_routed = true,
पूर्ण;

अटल काष्ठा gpio e740_audio_gpios[] = अणु
	अणु GPIO_E740_MIC_ON, GPIOF_OUT_INIT_LOW, "Mic amp" पूर्ण,
	अणु GPIO_E740_AMP_ON, GPIOF_OUT_INIT_LOW, "Output amp" पूर्ण,
	अणु GPIO_E740_WM9705_nAVDD2, GPIOF_OUT_INIT_HIGH, "Audio power" पूर्ण,
पूर्ण;

अटल पूर्णांक e740_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = &e740;
	पूर्णांक ret;

	ret = gpio_request_array(e740_audio_gpios,
				 ARRAY_SIZE(e740_audio_gpios));
	अगर (ret)
		वापस ret;

	card->dev = &pdev->dev;

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
	अगर (ret) अणु
		dev_err(&pdev->dev, "snd_soc_register_card() failed: %d\n",
			ret);
		gpio_मुक्त_array(e740_audio_gpios, ARRAY_SIZE(e740_audio_gpios));
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक e740_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	gpio_मुक्त_array(e740_audio_gpios, ARRAY_SIZE(e740_audio_gpios));
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver e740_driver = अणु
	.driver		= अणु
		.name	= "e740-audio",
		.pm     = &snd_soc_pm_ops,
	पूर्ण,
	.probe		= e740_probe,
	.हटाओ		= e740_हटाओ,
पूर्ण;

module_platक्रमm_driver(e740_driver);

/* Module inक्रमmation */
MODULE_AUTHOR("Ian Molton <spyro@f2s.com>");
MODULE_DESCRIPTION("ALSA SoC driver for e740");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:e740-audio");
