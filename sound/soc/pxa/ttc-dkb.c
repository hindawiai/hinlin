<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * linux/sound/soc/pxa/ttc_dkb.c
 *
 * Copyright (C) 2012 Marvell International Ltd.
 */
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/jack.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <sound/pcm_params.h>
#समावेश "../codecs/88pm860x-codec.h"

अटल काष्ठा snd_soc_jack hs_jack, mic_jack;

अटल काष्ठा snd_soc_jack_pin hs_jack_pins[] = अणु
	अणु .pin = "Headset Stereophone",	.mask = SND_JACK_HEADPHONE, पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_jack_pin mic_jack_pins[] = अणु
	अणु .pin = "Headset Mic 2",	.mask = SND_JACK_MICROPHONE, पूर्ण,
पूर्ण;

/* ttc machine dapm widमाला_लो */
अटल स्थिर काष्ठा snd_soc_dapm_widget ttc_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headset Stereophone", शून्य),
	SND_SOC_DAPM_LINE("Lineout Out 1", शून्य),
	SND_SOC_DAPM_LINE("Lineout Out 2", शून्य),
	SND_SOC_DAPM_SPK("Ext Speaker", शून्य),
	SND_SOC_DAPM_MIC("Ext Mic 1", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic 2", शून्य),
	SND_SOC_DAPM_MIC("Ext Mic 3", शून्य),
पूर्ण;

/* ttc machine audio map */
अटल स्थिर काष्ठा snd_soc_dapm_route ttc_audio_map[] = अणु
	अणु"Headset Stereophone", शून्य, "HS1"पूर्ण,
	अणु"Headset Stereophone", शून्य, "HS2"पूर्ण,

	अणु"Ext Speaker", शून्य, "LSP"पूर्ण,
	अणु"Ext Speaker", शून्य, "LSN"पूर्ण,

	अणु"Lineout Out 1", शून्य, "LINEOUT1"पूर्ण,
	अणु"Lineout Out 2", शून्य, "LINEOUT2"पूर्ण,

	अणु"MIC1P", शून्य, "Mic1 Bias"पूर्ण,
	अणु"MIC1N", शून्य, "Mic1 Bias"पूर्ण,
	अणु"Mic1 Bias", शून्य, "Ext Mic 1"पूर्ण,

	अणु"MIC2P", शून्य, "Mic1 Bias"पूर्ण,
	अणु"MIC2N", शून्य, "Mic1 Bias"पूर्ण,
	अणु"Mic1 Bias", शून्य, "Headset Mic 2"पूर्ण,

	अणु"MIC3P", शून्य, "Mic3 Bias"पूर्ण,
	अणु"MIC3N", शून्य, "Mic3 Bias"पूर्ण,
	अणु"Mic3 Bias", शून्य, "Ext Mic 3"पूर्ण,
पूर्ण;

अटल पूर्णांक ttc_pm860x_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_component *component = asoc_rtd_to_codec(rtd, 0)->component;

	/* Headset jack detection */
	snd_soc_card_jack_new(rtd->card, "Headphone Jack", SND_JACK_HEADPHONE |
			      SND_JACK_BTN_0 | SND_JACK_BTN_1 | SND_JACK_BTN_2,
			      &hs_jack, hs_jack_pins, ARRAY_SIZE(hs_jack_pins));
	snd_soc_card_jack_new(rtd->card, "Microphone Jack", SND_JACK_MICROPHONE,
			      &mic_jack, mic_jack_pins,
			      ARRAY_SIZE(mic_jack_pins));

	/* headphone, microphone detection & headset लघु detection */
	pm860x_hs_jack_detect(component, &hs_jack, SND_JACK_HEADPHONE,
			      SND_JACK_BTN_0, SND_JACK_BTN_1, SND_JACK_BTN_2);
	pm860x_mic_jack_detect(component, &hs_jack, SND_JACK_MICROPHONE);

	वापस 0;
पूर्ण

/* ttc/td-dkb digital audio पूर्णांकerface glue - connects codec <--> CPU */
SND_SOC_DAILINK_DEFS(i2s,
	DAILINK_COMP_ARRAY(COMP_CPU("pxa-ssp-dai.1")),
	DAILINK_COMP_ARRAY(COMP_CODEC("88pm860x-codec", "88pm860x-i2s")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("mmp-pcm-audio")));

अटल काष्ठा snd_soc_dai_link ttc_pm860x_hअगरi_dai[] = अणु
अणु
	 .name = "88pm860x i2s",
	 .stream_name = "audio playback",
	 .dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBM_CFM,
	 .init = ttc_pm860x_init,
	 SND_SOC_DAILINK_REG(i2s),
पूर्ण,
पूर्ण;

/* ttc/td audio machine driver */
अटल काष्ठा snd_soc_card ttc_dkb_card = अणु
	.name = "ttc-dkb-hifi",
	.owner = THIS_MODULE,
	.dai_link = ttc_pm860x_hअगरi_dai,
	.num_links = ARRAY_SIZE(ttc_pm860x_hअगरi_dai),

	.dapm_widमाला_लो = ttc_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(ttc_dapm_widमाला_लो),
	.dapm_routes = ttc_audio_map,
	.num_dapm_routes = ARRAY_SIZE(ttc_audio_map),
पूर्ण;

अटल पूर्णांक ttc_dkb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = &ttc_dkb_card;
	पूर्णांक ret;

	card->dev = &pdev->dev;

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
	अगर (ret)
		dev_err(&pdev->dev, "snd_soc_register_card() failed: %d\n",
			ret);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver ttc_dkb_driver = अणु
	.driver		= अणु
		.name	= "ttc-dkb-audio",
		.pm     = &snd_soc_pm_ops,
	पूर्ण,
	.probe		= ttc_dkb_probe,
पूर्ण;

module_platक्रमm_driver(ttc_dkb_driver);

/* Module inक्रमmation */
MODULE_AUTHOR("Qiao Zhou, <zhouqiao@marvell.com>");
MODULE_DESCRIPTION("ALSA SoC TTC DKB");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:ttc-dkb-audio");
