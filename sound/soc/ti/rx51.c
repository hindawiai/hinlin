<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * rx51.c  --  SoC audio क्रम Nokia RX-51
 *
 * Copyright (C) 2008 - 2009 Nokia Corporation
 *
 * Contact: Peter Ujfalusi <peter.ujfalusi@ti.com>
 *          Eduarकरो Valentin <eduarकरो.valentin@nokia.com>
 *          Jarkko Nikula <jarkko.nikula@biपंचांगer.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/jack.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <linux/platक्रमm_data/asoc-ti-mcbsp.h>

#समावेश <यंत्र/mach-types.h>

#समावेश "omap-mcbsp.h"

क्रमागत अणु
	RX51_JACK_DISABLED,
	RX51_JACK_TVOUT,		/* tv-out with stereo output */
	RX51_JACK_HP,			/* headphone: stereo output, no mic */
	RX51_JACK_HS,			/* headset: stereo output with mic */
पूर्ण;

काष्ठा rx51_audio_pdata अणु
	काष्ठा gpio_desc *tvout_selection_gpio;
	काष्ठा gpio_desc *jack_detection_gpio;
	काष्ठा gpio_desc *eci_sw_gpio;
	काष्ठा gpio_desc *speaker_amp_gpio;
पूर्ण;

अटल पूर्णांक rx51_spk_func;
अटल पूर्णांक rx51_dmic_func;
अटल पूर्णांक rx51_jack_func;

अटल व्योम rx51_ext_control(काष्ठा snd_soc_dapm_context *dapm)
अणु
	काष्ठा snd_soc_card *card = dapm->card;
	काष्ठा rx51_audio_pdata *pdata = snd_soc_card_get_drvdata(card);
	पूर्णांक hp = 0, hs = 0, tvout = 0;

	चयन (rx51_jack_func) अणु
	हाल RX51_JACK_TVOUT:
		tvout = 1;
		hp = 1;
		अवरोध;
	हाल RX51_JACK_HS:
		hs = 1;
		fallthrough;
	हाल RX51_JACK_HP:
		hp = 1;
		अवरोध;
	पूर्ण

	snd_soc_dapm_mutex_lock(dapm);

	अगर (rx51_spk_func)
		snd_soc_dapm_enable_pin_unlocked(dapm, "Ext Spk");
	अन्यथा
		snd_soc_dapm_disable_pin_unlocked(dapm, "Ext Spk");
	अगर (rx51_dmic_func)
		snd_soc_dapm_enable_pin_unlocked(dapm, "DMic");
	अन्यथा
		snd_soc_dapm_disable_pin_unlocked(dapm, "DMic");
	अगर (hp)
		snd_soc_dapm_enable_pin_unlocked(dapm, "Headphone Jack");
	अन्यथा
		snd_soc_dapm_disable_pin_unlocked(dapm, "Headphone Jack");
	अगर (hs)
		snd_soc_dapm_enable_pin_unlocked(dapm, "HS Mic");
	अन्यथा
		snd_soc_dapm_disable_pin_unlocked(dapm, "HS Mic");

	gpiod_set_value(pdata->tvout_selection_gpio, tvout);

	snd_soc_dapm_sync_unlocked(dapm);

	snd_soc_dapm_mutex_unlock(dapm);
पूर्ण

अटल पूर्णांक rx51_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_card *card = rtd->card;

	snd_pcm_hw_स्थिरraपूर्णांक_single(runसमय, SNDRV_PCM_HW_PARAM_CHANNELS, 2);
	rx51_ext_control(&card->dapm);

	वापस 0;
पूर्ण

अटल पूर्णांक rx51_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);

	/* Set the codec प्रणाली घड़ी क्रम DAC and ADC */
	वापस snd_soc_dai_set_sysclk(codec_dai, 0, 19200000,
				      SND_SOC_CLOCK_IN);
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops rx51_ops = अणु
	.startup = rx51_startup,
	.hw_params = rx51_hw_params,
पूर्ण;

अटल पूर्णांक rx51_get_spk(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.क्रमागतerated.item[0] = rx51_spk_func;

	वापस 0;
पूर्ण

अटल पूर्णांक rx51_set_spk(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_card *card = snd_kcontrol_chip(kcontrol);

	अगर (rx51_spk_func == ucontrol->value.क्रमागतerated.item[0])
		वापस 0;

	rx51_spk_func = ucontrol->value.क्रमागतerated.item[0];
	rx51_ext_control(&card->dapm);

	वापस 1;
पूर्ण

अटल पूर्णांक rx51_spk_event(काष्ठा snd_soc_dapm_widget *w,
			  काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	काष्ठा snd_soc_dapm_context *dapm = w->dapm;
	काष्ठा snd_soc_card *card = dapm->card;
	काष्ठा rx51_audio_pdata *pdata = snd_soc_card_get_drvdata(card);

	gpiod_set_raw_value_cansleep(pdata->speaker_amp_gpio,
				     !!SND_SOC_DAPM_EVENT_ON(event));

	वापस 0;
पूर्ण

अटल पूर्णांक rx51_get_input(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.क्रमागतerated.item[0] = rx51_dmic_func;

	वापस 0;
पूर्ण

अटल पूर्णांक rx51_set_input(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_card *card = snd_kcontrol_chip(kcontrol);

	अगर (rx51_dmic_func == ucontrol->value.क्रमागतerated.item[0])
		वापस 0;

	rx51_dmic_func = ucontrol->value.क्रमागतerated.item[0];
	rx51_ext_control(&card->dapm);

	वापस 1;
पूर्ण

अटल पूर्णांक rx51_get_jack(काष्ठा snd_kcontrol *kcontrol,
			 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.क्रमागतerated.item[0] = rx51_jack_func;

	वापस 0;
पूर्ण

अटल पूर्णांक rx51_set_jack(काष्ठा snd_kcontrol *kcontrol,
			 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_card *card = snd_kcontrol_chip(kcontrol);

	अगर (rx51_jack_func == ucontrol->value.क्रमागतerated.item[0])
		वापस 0;

	rx51_jack_func = ucontrol->value.क्रमागतerated.item[0];
	rx51_ext_control(&card->dapm);

	वापस 1;
पूर्ण

अटल काष्ठा snd_soc_jack rx51_av_jack;

अटल काष्ठा snd_soc_jack_gpio rx51_av_jack_gpios[] = अणु
	अणु
		.name = "avdet-gpio",
		.report = SND_JACK_HEADSET,
		.invert = 1,
		.debounce_समय = 200,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget aic34_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_SPK("Ext Spk", rx51_spk_event),
	SND_SOC_DAPM_MIC("DMic", शून्य),
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_MIC("HS Mic", शून्य),
	SND_SOC_DAPM_LINE("FM Transmitter", शून्य),
	SND_SOC_DAPM_SPK("Earphone", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route audio_map[] = अणु
	अणु"Ext Spk", शून्य, "HPLOUT"पूर्ण,
	अणु"Ext Spk", शून्य, "HPROUT"पूर्ण,
	अणु"Ext Spk", शून्य, "HPLCOM"पूर्ण,
	अणु"Ext Spk", शून्य, "HPRCOM"पूर्ण,
	अणु"FM Transmitter", शून्य, "LLOUT"पूर्ण,
	अणु"FM Transmitter", शून्य, "RLOUT"पूर्ण,

	अणु"Headphone Jack", शून्य, "TPA6130A2 HPLEFT"पूर्ण,
	अणु"Headphone Jack", शून्य, "TPA6130A2 HPRIGHT"पूर्ण,
	अणु"TPA6130A2 LEFTIN", शून्य, "LLOUT"पूर्ण,
	अणु"TPA6130A2 RIGHTIN", शून्य, "RLOUT"पूर्ण,

	अणु"DMic Rate 64", शून्य, "DMic"पूर्ण,
	अणु"DMic", शून्य, "Mic Bias"पूर्ण,

	अणु"b LINE2R", शून्य, "MONO_LOUT"पूर्ण,
	अणु"Earphone", शून्य, "b HPLOUT"पूर्ण,

	अणु"LINE1L", शून्य, "HS Mic"पूर्ण,
	अणु"HS Mic", शून्य, "b Mic Bias"पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर spk_function[] = अणु"Off", "On"पूर्ण;
अटल स्थिर अक्षर * स्थिर input_function[] = अणु"ADC", "Digital Mic"पूर्ण;
अटल स्थिर अक्षर * स्थिर jack_function[] = अणु
	"Off", "TV-OUT", "Headphone", "Headset"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत rx51_क्रमागत[] = अणु
	SOC_ENUM_SINGLE_EXT(ARRAY_SIZE(spk_function), spk_function),
	SOC_ENUM_SINGLE_EXT(ARRAY_SIZE(input_function), input_function),
	SOC_ENUM_SINGLE_EXT(ARRAY_SIZE(jack_function), jack_function),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new aic34_rx51_controls[] = अणु
	SOC_ENUM_EXT("Speaker Function", rx51_क्रमागत[0],
		     rx51_get_spk, rx51_set_spk),
	SOC_ENUM_EXT("Input Select",  rx51_क्रमागत[1],
		     rx51_get_input, rx51_set_input),
	SOC_ENUM_EXT("Jack Function", rx51_क्रमागत[2],
		     rx51_get_jack, rx51_set_jack),
	SOC_DAPM_PIN_SWITCH("FM Transmitter"),
	SOC_DAPM_PIN_SWITCH("Earphone"),
पूर्ण;

अटल पूर्णांक rx51_aic34_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा rx51_audio_pdata *pdata = snd_soc_card_get_drvdata(card);
	पूर्णांक err;

	snd_soc_limit_volume(card, "TPA6130A2 Headphone Playback Volume", 42);

	err = omap_mcbsp_st_add_controls(rtd, 2);
	अगर (err < 0) अणु
		dev_err(card->dev, "Failed to add MCBSP controls\n");
		वापस err;
	पूर्ण

	/* AV jack detection */
	err = snd_soc_card_jack_new(rtd->card, "AV Jack",
				    SND_JACK_HEADSET | SND_JACK_VIDEOOUT,
				    &rx51_av_jack, शून्य, 0);
	अगर (err) अणु
		dev_err(card->dev, "Failed to add AV Jack\n");
		वापस err;
	पूर्ण

	/* prepare gpio क्रम snd_soc_jack_add_gpios */
	rx51_av_jack_gpios[0].gpio = desc_to_gpio(pdata->jack_detection_gpio);
	devm_gpiod_put(card->dev, pdata->jack_detection_gpio);

	err = snd_soc_jack_add_gpios(&rx51_av_jack,
				     ARRAY_SIZE(rx51_av_jack_gpios),
				     rx51_av_jack_gpios);
	अगर (err) अणु
		dev_err(card->dev, "Failed to add GPIOs\n");
		वापस err;
	पूर्ण

	वापस err;
पूर्ण

/* Digital audio पूर्णांकerface glue - connects codec <--> CPU */
SND_SOC_DAILINK_DEFS(aic34,
	DAILINK_COMP_ARRAY(COMP_CPU("omap-mcbsp.2")),
	DAILINK_COMP_ARRAY(COMP_CODEC("tlv320aic3x-codec.2-0018",
				      "tlv320aic3x-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("omap-mcbsp.2")));

अटल काष्ठा snd_soc_dai_link rx51_dai[] = अणु
	अणु
		.name = "TLV320AIC34",
		.stream_name = "AIC34",
		.dai_fmt = SND_SOC_DAIFMT_DSP_A | SND_SOC_DAIFMT_IB_NF |
			   SND_SOC_DAIFMT_CBM_CFM,
		.init = rx51_aic34_init,
		.ops = &rx51_ops,
		SND_SOC_DAILINK_REG(aic34),
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_aux_dev rx51_aux_dev[] = अणु
	अणु
		.dlc = COMP_AUX("tlv320aic3x-codec.2-0019"),
	पूर्ण,
	अणु
		.dlc = COMP_AUX("tpa6130a2.2-0060"),
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_codec_conf rx51_codec_conf[] = अणु
	अणु
		.dlc = COMP_CODEC_CONF("tlv320aic3x-codec.2-0019"),
		.name_prefix = "b",
	पूर्ण,
	अणु
		.dlc = COMP_CODEC_CONF("tpa6130a2.2-0060"),
		.name_prefix = "TPA6130A2",
	पूर्ण,
पूर्ण;

/* Audio card */
अटल काष्ठा snd_soc_card rx51_sound_card = अणु
	.name = "RX-51",
	.owner = THIS_MODULE,
	.dai_link = rx51_dai,
	.num_links = ARRAY_SIZE(rx51_dai),
	.aux_dev = rx51_aux_dev,
	.num_aux_devs = ARRAY_SIZE(rx51_aux_dev),
	.codec_conf = rx51_codec_conf,
	.num_configs = ARRAY_SIZE(rx51_codec_conf),
	.fully_routed = true,

	.controls = aic34_rx51_controls,
	.num_controls = ARRAY_SIZE(aic34_rx51_controls),
	.dapm_widमाला_लो = aic34_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(aic34_dapm_widमाला_लो),
	.dapm_routes = audio_map,
	.num_dapm_routes = ARRAY_SIZE(audio_map),
पूर्ण;

अटल पूर्णांक rx51_soc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rx51_audio_pdata *pdata;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा snd_soc_card *card = &rx51_sound_card;
	पूर्णांक err;

	अगर (!machine_is_nokia_rx51() && !of_machine_is_compatible("nokia,omap3-n900"))
		वापस -ENODEV;

	card->dev = &pdev->dev;

	अगर (np) अणु
		काष्ठा device_node *dai_node;

		dai_node = of_parse_phandle(np, "nokia,cpu-dai", 0);
		अगर (!dai_node) अणु
			dev_err(&pdev->dev, "McBSP node is not provided\n");
			वापस -EINVAL;
		पूर्ण
		rx51_dai[0].cpus->dai_name = शून्य;
		rx51_dai[0].platक्रमms->name = शून्य;
		rx51_dai[0].cpus->of_node = dai_node;
		rx51_dai[0].platक्रमms->of_node = dai_node;

		dai_node = of_parse_phandle(np, "nokia,audio-codec", 0);
		अगर (!dai_node) अणु
			dev_err(&pdev->dev, "Codec node is not provided\n");
			वापस -EINVAL;
		पूर्ण
		rx51_dai[0].codecs->name = शून्य;
		rx51_dai[0].codecs->of_node = dai_node;

		dai_node = of_parse_phandle(np, "nokia,audio-codec", 1);
		अगर (!dai_node) अणु
			dev_err(&pdev->dev, "Auxiliary Codec node is not provided\n");
			वापस -EINVAL;
		पूर्ण
		rx51_aux_dev[0].dlc.name = शून्य;
		rx51_aux_dev[0].dlc.of_node = dai_node;
		rx51_codec_conf[0].dlc.name = शून्य;
		rx51_codec_conf[0].dlc.of_node = dai_node;

		dai_node = of_parse_phandle(np, "nokia,headphone-amplifier", 0);
		अगर (!dai_node) अणु
			dev_err(&pdev->dev, "Headphone amplifier node is not provided\n");
			वापस -EINVAL;
		पूर्ण
		rx51_aux_dev[1].dlc.name = शून्य;
		rx51_aux_dev[1].dlc.of_node = dai_node;
		rx51_codec_conf[1].dlc.name = शून्य;
		rx51_codec_conf[1].dlc.of_node = dai_node;
	पूर्ण

	pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
	अगर (pdata == शून्य)
		वापस -ENOMEM;

	snd_soc_card_set_drvdata(card, pdata);

	pdata->tvout_selection_gpio = devm_gpiod_get(card->dev,
						     "tvout-selection",
						     GPIOD_OUT_LOW);
	अगर (IS_ERR(pdata->tvout_selection_gpio)) अणु
		dev_err(card->dev, "could not get tvout selection gpio\n");
		वापस PTR_ERR(pdata->tvout_selection_gpio);
	पूर्ण

	pdata->jack_detection_gpio = devm_gpiod_get(card->dev,
						    "jack-detection",
						    GPIOD_ASIS);
	अगर (IS_ERR(pdata->jack_detection_gpio)) अणु
		dev_err(card->dev, "could not get jack detection gpio\n");
		वापस PTR_ERR(pdata->jack_detection_gpio);
	पूर्ण

	pdata->eci_sw_gpio = devm_gpiod_get(card->dev, "eci-switch",
					    GPIOD_OUT_HIGH);
	अगर (IS_ERR(pdata->eci_sw_gpio)) अणु
		dev_err(card->dev, "could not get eci switch gpio\n");
		वापस PTR_ERR(pdata->eci_sw_gpio);
	पूर्ण

	pdata->speaker_amp_gpio = devm_gpiod_get(card->dev,
						 "speaker-amplifier",
						 GPIOD_OUT_LOW);
	अगर (IS_ERR(pdata->speaker_amp_gpio)) अणु
		dev_err(card->dev, "could not get speaker enable gpio\n");
		वापस PTR_ERR(pdata->speaker_amp_gpio);
	पूर्ण

	err = devm_snd_soc_रेजिस्टर_card(card->dev, card);
	अगर (err) अणु
		dev_err(&pdev->dev, "snd_soc_register_card failed (%d)\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id rx51_audio_of_match[] = अणु
	अणु .compatible = "nokia,n900-audio", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rx51_audio_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver rx51_soc_driver = अणु
	.driver = अणु
		.name = "rx51-audio",
		.of_match_table = of_match_ptr(rx51_audio_of_match),
	पूर्ण,
	.probe = rx51_soc_probe,
पूर्ण;

module_platक्रमm_driver(rx51_soc_driver);

MODULE_AUTHOR("Nokia Corporation");
MODULE_DESCRIPTION("ALSA SoC Nokia RX-51");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:rx51-audio");
