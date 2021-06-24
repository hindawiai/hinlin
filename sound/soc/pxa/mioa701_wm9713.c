<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Handles the Mitac mioa701 SoC प्रणाली
 *
 * Copyright (C) 2008 Robert Jarzmik
 *
 * This is a little schema of the sound पूर्णांकerconnections :
 *
 *    Sagem X200                 Wolfson WM9713
 *    +--------+             +-------------------+      Rear Speaker
 *    |        |             |                   |           /-+
 *    |        +--->----->---+MONOIN         SPKL+--->----+-+  |
 *    |  GSM   |             |                   |        | |  |
 *    |        +--->----->---+PCBEEP         SPKR+--->----+-+  |
 *    |  CHIP  |             |                   |           \-+
 *    |        +---<-----<---+MONO               |
 *    |        |             |                   |      Front Speaker
 *    +--------+             |                   |           /-+
 *                           |                HPL+--->----+-+  |
 *                           |                   |        | |  |
 *                           |               OUT3+--->----+-+  |
 *                           |                   |           \-+
 *                           |                   |
 *                           |                   |     Front Micro
 *                           |                   |         +
 *                           |               MIC1+-----<--+o+
 *                           |                   |         +
 *                           +-------------------+        ---
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <mach/audपन.स>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/ac97_codec.h>

#समावेश "../codecs/wm9713.h"

#घोषणा AC97_GPIO_PULL		0x58

/* Use GPIO8 क्रम rear speaker amplअगरier */
अटल पूर्णांक rear_amp_घातer(काष्ठा snd_soc_component *component, पूर्णांक घातer)
अणु
	अचिन्हित लघु reg;

	अगर (घातer) अणु
		reg = snd_soc_component_पढ़ो(component, AC97_GPIO_CFG);
		snd_soc_component_ग_लिखो(component, AC97_GPIO_CFG, reg | 0x0100);
		reg = snd_soc_component_पढ़ो(component, AC97_GPIO_PULL);
		snd_soc_component_ग_लिखो(component, AC97_GPIO_PULL, reg | (1<<15));
	पूर्ण अन्यथा अणु
		reg = snd_soc_component_पढ़ो(component, AC97_GPIO_CFG);
		snd_soc_component_ग_लिखो(component, AC97_GPIO_CFG, reg & ~0x0100);
		reg = snd_soc_component_पढ़ो(component, AC97_GPIO_PULL);
		snd_soc_component_ग_लिखो(component, AC97_GPIO_PULL, reg & ~(1<<15));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rear_amp_event(काष्ठा snd_soc_dapm_widget *widget,
			  काष्ठा snd_kcontrol *kctl, पूर्णांक event)
अणु
	काष्ठा snd_soc_card *card = widget->dapm->card;
	काष्ठा snd_soc_pcm_runसमय *rtd;
	काष्ठा snd_soc_component *component;

	rtd = snd_soc_get_pcm_runसमय(card, &card->dai_link[0]);
	component = asoc_rtd_to_codec(rtd, 0)->component;
	वापस rear_amp_घातer(component, SND_SOC_DAPM_EVENT_ON(event));
पूर्ण

/* mioa701 machine dapm widमाला_लो */
अटल स्थिर काष्ठा snd_soc_dapm_widget mioa701_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_SPK("Front Speaker", शून्य),
	SND_SOC_DAPM_SPK("Rear Speaker", rear_amp_event),
	SND_SOC_DAPM_MIC("Headset", शून्य),
	SND_SOC_DAPM_LINE("GSM Line Out", शून्य),
	SND_SOC_DAPM_LINE("GSM Line In", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_MIC("Front Mic", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route audio_map[] = अणु
	/* Call Mic */
	अणु"Mic Bias", शून्य, "Front Mic"पूर्ण,
	अणु"MIC1", शून्य, "Mic Bias"पूर्ण,

	/* Headset Mic */
	अणु"LINEL", शून्य, "Headset Mic"पूर्ण,
	अणु"LINER", शून्य, "Headset Mic"पूर्ण,

	/* GSM Module */
	अणु"MONOIN", शून्य, "GSM Line Out"पूर्ण,
	अणु"PCBEEP", शून्य, "GSM Line Out"पूर्ण,
	अणु"GSM Line In", शून्य, "MONO"पूर्ण,

	/* headphone connected to HPL, HPR */
	अणु"Headset", शून्य, "HPL"पूर्ण,
	अणु"Headset", शून्य, "HPR"पूर्ण,

	/* front speaker connected to HPL, OUT3 */
	अणु"Front Speaker", शून्य, "HPL"पूर्ण,
	अणु"Front Speaker", शून्य, "OUT3"पूर्ण,

	/* rear speaker connected to SPKL, SPKR */
	अणु"Rear Speaker", शून्य, "SPKL"पूर्ण,
	अणु"Rear Speaker", शून्य, "SPKR"पूर्ण,
पूर्ण;

अटल पूर्णांक mioa701_wm9713_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_component *component = asoc_rtd_to_codec(rtd, 0)->component;

	/* Prepare GPIO8 क्रम rear speaker amplअगरier */
	snd_soc_component_update_bits(component, AC97_GPIO_CFG, 0x100, 0x100);

	/* Prepare MIC input */
	snd_soc_component_update_bits(component, AC97_3D_CONTROL, 0xc000, 0xc000);

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_ops mioa701_ops;

SND_SOC_DAILINK_DEFS(ac97,
	DAILINK_COMP_ARRAY(COMP_CPU("pxa2xx-ac97")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm9713-codec", "wm9713-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("pxa-pcm-audio")));

SND_SOC_DAILINK_DEFS(ac97_aux,
	DAILINK_COMP_ARRAY(COMP_CPU("pxa2xx-ac97-aux")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm9713-codec", "wm9713-aux")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("pxa-pcm-audio")));

अटल काष्ठा snd_soc_dai_link mioa701_dai[] = अणु
	अणु
		.name = "AC97",
		.stream_name = "AC97 HiFi",
		.init = mioa701_wm9713_init,
		.ops = &mioa701_ops,
		SND_SOC_DAILINK_REG(ac97),
	पूर्ण,
	अणु
		.name = "AC97 Aux",
		.stream_name = "AC97 Aux",
		.ops = &mioa701_ops,
		SND_SOC_DAILINK_REG(ac97_aux),
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_card mioa701 = अणु
	.name = "MioA701",
	.owner = THIS_MODULE,
	.dai_link = mioa701_dai,
	.num_links = ARRAY_SIZE(mioa701_dai),

	.dapm_widमाला_लो = mioa701_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(mioa701_dapm_widमाला_लो),
	.dapm_routes = audio_map,
	.num_dapm_routes = ARRAY_SIZE(audio_map),
पूर्ण;

अटल पूर्णांक mioa701_wm9713_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक rc;

	अगर (!machine_is_mioa701())
		वापस -ENODEV;

	mioa701.dev = &pdev->dev;
	rc = devm_snd_soc_रेजिस्टर_card(&pdev->dev, &mioa701);
	अगर (!rc)
		dev_warn(&pdev->dev, "Be warned that incorrect mixers/muxes setup will "
			 "lead to overheating and possible destruction of your device."
			 " Do not use without a good knowledge of mio's board design!\n");
	वापस rc;
पूर्ण

अटल काष्ठा platक्रमm_driver mioa701_wm9713_driver = अणु
	.probe		= mioa701_wm9713_probe,
	.driver		= अणु
		.name		= "mioa701-wm9713",
		.pm     = &snd_soc_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mioa701_wm9713_driver);

/* Module inक्रमmation */
MODULE_AUTHOR("Robert Jarzmik (rjarzmik@free.fr)");
MODULE_DESCRIPTION("ALSA SoC WM9713 MIO A701");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:mioa701-wm9713");
