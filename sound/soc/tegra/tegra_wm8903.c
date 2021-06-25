<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tegra_wm8903.c - Tegra machine ASoC driver क्रम boards using WM8903 codec.
 *
 * Author: Stephen Warren <swarren@nvidia.com>
 * Copyright (C) 2010-2012 - NVIDIA, Inc.
 *
 * Based on code copyright/by:
 *
 * (c) 2009, 2010 Nvidia Graphics Pvt. Ltd.
 *
 * Copyright 2007 Wolfson Microelectronics PLC.
 * Author: Graeme Gregory
 *         graeme.gregory@wolfsonmicro.com or linux@wolfsonmicro.com
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/of_gpपन.स>

#समावेश <sound/core.h>
#समावेश <sound/jack.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

#समावेश "../codecs/wm8903.h"

#समावेश "tegra_asoc_utils.h"

#घोषणा DRV_NAME "tegra-snd-wm8903"

काष्ठा tegra_wm8903 अणु
	पूर्णांक gpio_spkr_en;
	पूर्णांक gpio_hp_det;
	पूर्णांक gpio_hp_mute;
	पूर्णांक gpio_पूर्णांक_mic_en;
	पूर्णांक gpio_ext_mic_en;
	काष्ठा tegra_asoc_utils_data util_data;
पूर्ण;

अटल पूर्णांक tegra_wm8903_hw_params(काष्ठा snd_pcm_substream *substream,
					काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा tegra_wm8903 *machine = snd_soc_card_get_drvdata(card);
	पूर्णांक srate, mclk;
	पूर्णांक err;

	srate = params_rate(params);
	चयन (srate) अणु
	हाल 64000:
	हाल 88200:
	हाल 96000:
		mclk = 128 * srate;
		अवरोध;
	शेष:
		mclk = 256 * srate;
		अवरोध;
	पूर्ण
	/* FIXME: Codec only requires >= 3MHz अगर OSR==0 */
	जबतक (mclk < 6000000)
		mclk *= 2;

	err = tegra_asoc_utils_set_rate(&machine->util_data, srate, mclk);
	अगर (err < 0) अणु
		dev_err(card->dev, "Can't configure clocks\n");
		वापस err;
	पूर्ण

	err = snd_soc_dai_set_sysclk(codec_dai, 0, mclk,
					SND_SOC_CLOCK_IN);
	अगर (err < 0) अणु
		dev_err(card->dev, "codec_dai clock not set\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops tegra_wm8903_ops = अणु
	.hw_params = tegra_wm8903_hw_params,
पूर्ण;

अटल काष्ठा snd_soc_jack tegra_wm8903_hp_jack;

अटल काष्ठा snd_soc_jack_pin tegra_wm8903_hp_jack_pins[] = अणु
	अणु
		.pin = "Headphone Jack",
		.mask = SND_JACK_HEADPHONE,
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_jack_gpio tegra_wm8903_hp_jack_gpio = अणु
	.name = "headphone detect",
	.report = SND_JACK_HEADPHONE,
	.debounce_समय = 150,
	.invert = 1,
पूर्ण;

अटल काष्ठा snd_soc_jack tegra_wm8903_mic_jack;

अटल काष्ठा snd_soc_jack_pin tegra_wm8903_mic_jack_pins[] = अणु
	अणु
		.pin = "Mic Jack",
		.mask = SND_JACK_MICROPHONE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक tegra_wm8903_event_पूर्णांक_spk(काष्ठा snd_soc_dapm_widget *w,
					काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	काष्ठा snd_soc_dapm_context *dapm = w->dapm;
	काष्ठा snd_soc_card *card = dapm->card;
	काष्ठा tegra_wm8903 *machine = snd_soc_card_get_drvdata(card);

	अगर (!gpio_is_valid(machine->gpio_spkr_en))
		वापस 0;

	gpio_set_value_cansleep(machine->gpio_spkr_en,
				SND_SOC_DAPM_EVENT_ON(event));

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_wm8903_event_hp(काष्ठा snd_soc_dapm_widget *w,
					काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	काष्ठा snd_soc_dapm_context *dapm = w->dapm;
	काष्ठा snd_soc_card *card = dapm->card;
	काष्ठा tegra_wm8903 *machine = snd_soc_card_get_drvdata(card);

	अगर (!gpio_is_valid(machine->gpio_hp_mute))
		वापस 0;

	gpio_set_value_cansleep(machine->gpio_hp_mute,
				!SND_SOC_DAPM_EVENT_ON(event));

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_wm8903_event_पूर्णांक_mic(काष्ठा snd_soc_dapm_widget *w,
				      काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	काष्ठा snd_soc_dapm_context *dapm = w->dapm;
	काष्ठा snd_soc_card *card = dapm->card;
	काष्ठा tegra_wm8903 *machine = snd_soc_card_get_drvdata(card);

	अगर (!gpio_is_valid(machine->gpio_पूर्णांक_mic_en))
		वापस 0;

	gpio_set_value_cansleep(machine->gpio_पूर्णांक_mic_en,
				SND_SOC_DAPM_EVENT_ON(event));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget tegra_wm8903_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_SPK("Int Spk", tegra_wm8903_event_पूर्णांक_spk),
	SND_SOC_DAPM_HP("Headphone Jack", tegra_wm8903_event_hp),
	SND_SOC_DAPM_MIC("Mic Jack", शून्य),
	SND_SOC_DAPM_MIC("Int Mic", tegra_wm8903_event_पूर्णांक_mic),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new tegra_wm8903_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Int Spk"),
	SOC_DAPM_PIN_SWITCH("Int Mic"),
पूर्ण;

अटल पूर्णांक tegra_wm8903_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा tegra_wm8903 *machine = snd_soc_card_get_drvdata(card);
	पूर्णांक shrt = 0;

	अगर (gpio_is_valid(machine->gpio_hp_det)) अणु
		tegra_wm8903_hp_jack_gpio.gpio = machine->gpio_hp_det;
		snd_soc_card_jack_new(rtd->card, "Headphone Jack",
				      SND_JACK_HEADPHONE, &tegra_wm8903_hp_jack,
				      tegra_wm8903_hp_jack_pins,
				      ARRAY_SIZE(tegra_wm8903_hp_jack_pins));
		snd_soc_jack_add_gpios(&tegra_wm8903_hp_jack,
					1,
					&tegra_wm8903_hp_jack_gpio);
	पूर्ण

	अगर (of_property_पढ़ो_bool(card->dev->of_node, "nvidia,headset"))
		shrt = SND_JACK_MICROPHONE;

	snd_soc_card_jack_new(rtd->card, "Mic Jack", SND_JACK_MICROPHONE,
			      &tegra_wm8903_mic_jack,
			      tegra_wm8903_mic_jack_pins,
			      ARRAY_SIZE(tegra_wm8903_mic_jack_pins));
	wm8903_mic_detect(component, &tegra_wm8903_mic_jack, SND_JACK_MICROPHONE,
				shrt);

	snd_soc_dapm_क्रमce_enable_pin(&card->dapm, "MICBIAS");

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_wm8903_हटाओ(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd =
		snd_soc_get_pcm_runसमय(card, &card->dai_link[0]);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_component *component = codec_dai->component;

	wm8903_mic_detect(component, शून्य, 0, 0);

	वापस 0;
पूर्ण

SND_SOC_DAILINK_DEFS(hअगरi,
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "wm8903-hifi")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

अटल काष्ठा snd_soc_dai_link tegra_wm8903_dai = अणु
	.name = "WM8903",
	.stream_name = "WM8903 PCM",
	.init = tegra_wm8903_init,
	.ops = &tegra_wm8903_ops,
	.dai_fmt = SND_SOC_DAIFMT_I2S |
		   SND_SOC_DAIFMT_NB_NF |
		   SND_SOC_DAIFMT_CBS_CFS,
	SND_SOC_DAILINK_REG(hअगरi),
पूर्ण;

अटल काष्ठा snd_soc_card snd_soc_tegra_wm8903 = अणु
	.name = "tegra-wm8903",
	.owner = THIS_MODULE,
	.dai_link = &tegra_wm8903_dai,
	.num_links = 1,
	.हटाओ = tegra_wm8903_हटाओ,
	.controls = tegra_wm8903_controls,
	.num_controls = ARRAY_SIZE(tegra_wm8903_controls),
	.dapm_widमाला_लो = tegra_wm8903_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(tegra_wm8903_dapm_widमाला_लो),
	.fully_routed = true,
पूर्ण;

अटल पूर्णांक tegra_wm8903_driver_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा snd_soc_card *card = &snd_soc_tegra_wm8903;
	काष्ठा tegra_wm8903 *machine;
	पूर्णांक ret;

	machine = devm_kzalloc(&pdev->dev, माप(काष्ठा tegra_wm8903),
			       GFP_KERNEL);
	अगर (!machine)
		वापस -ENOMEM;

	card->dev = &pdev->dev;
	snd_soc_card_set_drvdata(card, machine);

	machine->gpio_spkr_en = of_get_named_gpio(np, "nvidia,spkr-en-gpios",
						  0);
	अगर (machine->gpio_spkr_en == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;
	अगर (gpio_is_valid(machine->gpio_spkr_en)) अणु
		ret = devm_gpio_request_one(&pdev->dev, machine->gpio_spkr_en,
					    GPIOF_OUT_INIT_LOW, "spkr_en");
		अगर (ret) अणु
			dev_err(card->dev, "cannot get spkr_en gpio\n");
			वापस ret;
		पूर्ण
	पूर्ण

	machine->gpio_hp_mute = of_get_named_gpio(np, "nvidia,hp-mute-gpios",
						  0);
	अगर (machine->gpio_hp_mute == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;
	अगर (gpio_is_valid(machine->gpio_hp_mute)) अणु
		ret = devm_gpio_request_one(&pdev->dev, machine->gpio_hp_mute,
					    GPIOF_OUT_INIT_HIGH, "hp_mute");
		अगर (ret) अणु
			dev_err(card->dev, "cannot get hp_mute gpio\n");
			वापस ret;
		पूर्ण
	पूर्ण

	machine->gpio_hp_det = of_get_named_gpio(np, "nvidia,hp-det-gpios", 0);
	अगर (machine->gpio_hp_det == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;

	machine->gpio_पूर्णांक_mic_en = of_get_named_gpio(np,
						"nvidia,int-mic-en-gpios", 0);
	अगर (machine->gpio_पूर्णांक_mic_en == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;
	अगर (gpio_is_valid(machine->gpio_पूर्णांक_mic_en)) अणु
		/* Disable पूर्णांक mic; enable संकेत is active-high */
		ret = devm_gpio_request_one(&pdev->dev,
					    machine->gpio_पूर्णांक_mic_en,
					    GPIOF_OUT_INIT_LOW, "int_mic_en");
		अगर (ret) अणु
			dev_err(card->dev, "cannot get int_mic_en gpio\n");
			वापस ret;
		पूर्ण
	पूर्ण

	machine->gpio_ext_mic_en = of_get_named_gpio(np,
						"nvidia,ext-mic-en-gpios", 0);
	अगर (machine->gpio_ext_mic_en == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;
	अगर (gpio_is_valid(machine->gpio_ext_mic_en)) अणु
		/* Enable ext mic; enable संकेत is active-low */
		ret = devm_gpio_request_one(&pdev->dev,
					    machine->gpio_ext_mic_en,
					    GPIOF_OUT_INIT_LOW, "ext_mic_en");
		अगर (ret) अणु
			dev_err(card->dev, "cannot get ext_mic_en gpio\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = snd_soc_of_parse_card_name(card, "nvidia,model");
	अगर (ret)
		वापस ret;

	ret = snd_soc_of_parse_audio_routing(card, "nvidia,audio-routing");
	अगर (ret)
		वापस ret;

	tegra_wm8903_dai.codecs->of_node = of_parse_phandle(np,
						"nvidia,audio-codec", 0);
	अगर (!tegra_wm8903_dai.codecs->of_node) अणु
		dev_err(&pdev->dev,
			"Property 'nvidia,audio-codec' missing or invalid\n");
		वापस -EINVAL;
	पूर्ण

	tegra_wm8903_dai.cpus->of_node = of_parse_phandle(np,
			"nvidia,i2s-controller", 0);
	अगर (!tegra_wm8903_dai.cpus->of_node) अणु
		dev_err(&pdev->dev,
			"Property 'nvidia,i2s-controller' missing or invalid\n");
		वापस -EINVAL;
	पूर्ण

	tegra_wm8903_dai.platक्रमms->of_node = tegra_wm8903_dai.cpus->of_node;

	ret = tegra_asoc_utils_init(&machine->util_data, &pdev->dev);
	अगर (ret)
		वापस ret;

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
	अगर (ret)
		वापस dev_err_probe(&pdev->dev, ret,
				     "snd_soc_register_card failed\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tegra_wm8903_of_match[] = अणु
	अणु .compatible = "nvidia,tegra-audio-wm8903", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra_wm8903_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.pm = &snd_soc_pm_ops,
		.of_match_table = tegra_wm8903_of_match,
	पूर्ण,
	.probe = tegra_wm8903_driver_probe,
पूर्ण;
module_platक्रमm_driver(tegra_wm8903_driver);

MODULE_AUTHOR("Stephen Warren <swarren@nvidia.com>");
MODULE_DESCRIPTION("Tegra+WM8903 machine ASoC driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
MODULE_DEVICE_TABLE(of, tegra_wm8903_of_match);
