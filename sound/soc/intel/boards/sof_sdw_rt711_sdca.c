<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright (c) 2020 Intel Corporation

/*
 *  sof_sdw_rt711_sdca - Helpers to handle RT711-SDCA from generic machine driver
 */

#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/input.h>
#समावेश <linux/soundwire/sdw.h>
#समावेश <linux/soundwire/sdw_type.h>
#समावेश <sound/control.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-acpi.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/jack.h>
#समावेश "sof_sdw_common.h"

/*
 * Note this MUST be called beक्रमe snd_soc_रेजिस्टर_card(), so that the props
 * are in place beक्रमe the codec component driver's probe function parses them.
 */
अटल पूर्णांक rt711_sdca_add_codec_device_props(स्थिर अक्षर *sdw_dev_name)
अणु
	काष्ठा property_entry props[MAX_NO_PROPS] = अणुपूर्ण;
	काष्ठा device *sdw_dev;
	पूर्णांक ret;

	sdw_dev = bus_find_device_by_name(&sdw_bus_type, शून्य, sdw_dev_name);
	अगर (!sdw_dev)
		वापस -EPROBE_DEFER;

	अगर (SOF_RT711_JDSRC(sof_sdw_quirk)) अणु
		props[0] = PROPERTY_ENTRY_U32("realtek,jd-src",
					      SOF_RT711_JDSRC(sof_sdw_quirk));
	पूर्ण

	ret = device_add_properties(sdw_dev, props);
	put_device(sdw_dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget rt711_sdca_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt711_sdca_map[] = अणु
	/* Headphones */
	अणु "Headphone", शून्य, "rt711 HP" पूर्ण,
	अणु "rt711 MIC2", शून्य, "Headset Mic" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rt711_sdca_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Headphone"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
पूर्ण;

अटल काष्ठा snd_soc_jack_pin rt711_sdca_jack_pins[] = अणु
	अणु
		.pin    = "Headphone",
		.mask   = SND_JACK_HEADPHONE,
	पूर्ण,
	अणु
		.pin    = "Headset Mic",
		.mask   = SND_JACK_MICROPHONE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक rt711_sdca_rtd_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा mc_निजी *ctx = snd_soc_card_get_drvdata(card);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा snd_soc_jack *jack;
	पूर्णांक ret;

	card->components = devm_kaप्र_लिखो(card->dev, GFP_KERNEL,
					  "%s hs:rt711-sdca",
					  card->components);
	अगर (!card->components)
		वापस -ENOMEM;

	ret = snd_soc_add_card_controls(card, rt711_sdca_controls,
					ARRAY_SIZE(rt711_sdca_controls));
	अगर (ret) अणु
		dev_err(card->dev, "rt711-sdca controls addition failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dapm_new_controls(&card->dapm, rt711_sdca_widमाला_लो,
					ARRAY_SIZE(rt711_sdca_widमाला_लो));
	अगर (ret) अणु
		dev_err(card->dev, "rt711-sdca widgets addition failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dapm_add_routes(&card->dapm, rt711_sdca_map,
				      ARRAY_SIZE(rt711_sdca_map));

	अगर (ret) अणु
		dev_err(card->dev, "rt711-sdca map addition failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_card_jack_new(rtd->card, "Headset Jack",
				    SND_JACK_HEADSET | SND_JACK_BTN_0 |
				    SND_JACK_BTN_1 | SND_JACK_BTN_2 |
				    SND_JACK_BTN_3,
				    &ctx->sdw_headset,
				    rt711_sdca_jack_pins,
				    ARRAY_SIZE(rt711_sdca_jack_pins));
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

पूर्णांक sof_sdw_rt711_sdca_निकास(काष्ठा device *dev, काष्ठा snd_soc_dai_link *dai_link)
अणु
	काष्ठा device *sdw_dev;

	sdw_dev = bus_find_device_by_name(&sdw_bus_type, शून्य,
					  dai_link->codecs[0].name);
	अगर (!sdw_dev)
		वापस -EINVAL;

	device_हटाओ_properties(sdw_dev);
	put_device(sdw_dev);

	वापस 0;
पूर्ण

पूर्णांक sof_sdw_rt711_sdca_init(स्थिर काष्ठा snd_soc_acpi_link_adr *link,
			    काष्ठा snd_soc_dai_link *dai_links,
			    काष्ठा sof_sdw_codec_info *info,
			    bool playback)
अणु
	पूर्णांक ret;

	/*
	 * headset should be initialized once.
	 * Do it with dai link क्रम playback.
	 */
	अगर (!playback)
		वापस 0;

	ret = rt711_sdca_add_codec_device_props(dai_links->codecs[0].name);
	अगर (ret < 0)
		वापस ret;

	dai_links->init = rt711_sdca_rtd_init;

	वापस 0;
पूर्ण
