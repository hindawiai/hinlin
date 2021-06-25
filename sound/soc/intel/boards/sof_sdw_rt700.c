<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright (c) 2020 Intel Corporation

/*
 *  sof_sdw_rt700 - Helpers to handle RT700 from generic machine driver
 */

#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/input.h>
#समावेश <sound/control.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-acpi.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/jack.h>
#समावेश "sof_sdw_common.h"

अटल स्थिर काष्ठा snd_soc_dapm_widget rt700_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphones", शून्य),
	SND_SOC_DAPM_MIC("AMIC", शून्य),
	SND_SOC_DAPM_SPK("Speaker", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt700_map[] = अणु
	/* Headphones */
	अणु "Headphones", शून्य, "rt700 HP" पूर्ण,
	अणु "Speaker", शून्य, "rt700 SPK" पूर्ण,
	अणु "rt700 MIC2", शून्य, "AMIC" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt700_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Headphones"),
	SOC_DAPM_PIN_SWITCH("AMIC"),
	SOC_DAPM_PIN_SWITCH("Speaker"),
पूर्ण;

अटल काष्ठा snd_soc_jack_pin rt700_jack_pins[] = अणु
	अणु
		.pin    = "Headphones",
		.mask   = SND_JACK_HEADPHONE,
	पूर्ण,
	अणु
		.pin    = "AMIC",
		.mask   = SND_JACK_MICROPHONE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक rt700_rtd_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा mc_निजी *ctx = snd_soc_card_get_drvdata(card);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा snd_soc_jack *jack;
	पूर्णांक ret;

	card->components = devm_kaप्र_लिखो(card->dev, GFP_KERNEL,
					  "%s hs:rt700",
					  card->components);
	अगर (!card->components)
		वापस -ENOMEM;

	ret = snd_soc_add_card_controls(card, rt700_controls,
					ARRAY_SIZE(rt700_controls));
	अगर (ret) अणु
		dev_err(card->dev, "rt700 controls addition failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dapm_new_controls(&card->dapm, rt700_widमाला_लो,
					ARRAY_SIZE(rt700_widमाला_लो));
	अगर (ret) अणु
		dev_err(card->dev, "rt700 widgets addition failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dapm_add_routes(&card->dapm, rt700_map,
				      ARRAY_SIZE(rt700_map));

	अगर (ret) अणु
		dev_err(card->dev, "rt700 map addition failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_card_jack_new(rtd->card, "Headset Jack",
				    SND_JACK_HEADSET | SND_JACK_BTN_0 |
				    SND_JACK_BTN_1 | SND_JACK_BTN_2 |
				    SND_JACK_BTN_3,
				    &ctx->sdw_headset,
				    rt700_jack_pins,
				    ARRAY_SIZE(rt700_jack_pins));
	अगर (ret) अणु
		dev_err(rtd->card->dev, "Headset Jack creation failed: %d\n",
			ret);
		वापस ret;
	पूर्ण

	jack = &ctx->sdw_headset;

	snd_jack_set_key(jack->jack, SND_JACK_BTN_0, KEY_PLAYPAUSE);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_1, KEY_VOICECOMMAND);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_2, KEY_VOLUMEUP);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_3, KEY_VOLUMEDOWN);

	ret = snd_soc_component_set_jack(component, jack, शून्य);
	अगर (ret)
		dev_err(rtd->card->dev, "Headset Jack call-back failed: %d\n",
			ret);

	वापस ret;
पूर्ण

पूर्णांक sof_sdw_rt700_init(स्थिर काष्ठा snd_soc_acpi_link_adr *link,
		       काष्ठा snd_soc_dai_link *dai_links,
		       काष्ठा sof_sdw_codec_info *info,
		       bool playback)
अणु
	/*
	 * headset should be initialized once.
	 * Do it with dai link क्रम playback.
	 */
	अगर (!playback)
		वापस 0;

	dai_links->init = rt700_rtd_init;

	वापस 0;
पूर्ण
