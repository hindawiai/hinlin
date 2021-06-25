<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Rockchip machine ASoC driver क्रम RK3288 boards that have an HDMI and analog
 * audio output
 *
 * Copyright (c) 2016, Collabora Ltd.
 *
 * Authors: Sjoerd Simons <sjoerd.simons@collabora.com>,
 *	    Roमुख्य Perier <roमुख्य.perier@collabora.com>
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
#समावेश <sound/soc-dapm.h>

#समावेश "rockchip_i2s.h"

#घोषणा DRV_NAME "rk3288-snd-hdmi-analog"

काष्ठा rk_drvdata अणु
	पूर्णांक gpio_hp_en;
	पूर्णांक gpio_hp_det;
पूर्ण;

अटल पूर्णांक rk_hp_घातer(काष्ठा snd_soc_dapm_widget *w,
		       काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	काष्ठा rk_drvdata *machine = snd_soc_card_get_drvdata(w->dapm->card);

	अगर (!gpio_is_valid(machine->gpio_hp_en))
		वापस 0;

	gpio_set_value_cansleep(machine->gpio_hp_en,
				SND_SOC_DAPM_EVENT_ON(event));

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_jack headphone_jack;
अटल काष्ठा snd_soc_jack_pin headphone_jack_pins[] = अणु
	अणु
		.pin = "Analog",
		.mask = SND_JACK_HEADPHONE
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget rk_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Analog", rk_hp_घातer),
	SND_SOC_DAPM_LINE("HDMI", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rk_mc_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Analog"),
	SOC_DAPM_PIN_SWITCH("HDMI"),
पूर्ण;

अटल पूर्णांक rk_hw_params(काष्ठा snd_pcm_substream *substream,
			काष्ठा snd_pcm_hw_params *params)
अणु
	पूर्णांक ret = 0;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	पूर्णांक mclk;

	चयन (params_rate(params)) अणु
	हाल 8000:
	हाल 16000:
	हाल 24000:
	हाल 32000:
	हाल 48000:
	हाल 64000:
	हाल 96000:
		mclk = 12288000;
		अवरोध;
	हाल 192000:
		mclk = 24576000;
		अवरोध;
	हाल 11025:
	हाल 22050:
	हाल 44100:
	हाल 88200:
		mclk = 11289600;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = snd_soc_dai_set_sysclk(cpu_dai, 0, mclk,
				     SND_SOC_CLOCK_OUT);

	अगर (ret && ret != -ENOTSUPP) अणु
		dev_err(codec_dai->dev, "Can't set cpu clock %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dai_set_sysclk(codec_dai, 0, mclk,
				     SND_SOC_CLOCK_IN);
	अगर (ret && ret != -ENOTSUPP) अणु
		dev_err(codec_dai->dev, "Can't set codec clock %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_jack_gpio rk_hp_jack_gpio = अणु
	.name = "Headphone detection",
	.report = SND_JACK_HEADPHONE,
	.debounce_समय = 150
पूर्ण;

अटल पूर्णांक rk_init(काष्ठा snd_soc_pcm_runसमय *runसमय)
अणु
	काष्ठा rk_drvdata *machine = snd_soc_card_get_drvdata(runसमय->card);

	/* Enable Headset Jack detection */
	अगर (gpio_is_valid(machine->gpio_hp_det)) अणु
		snd_soc_card_jack_new(runसमय->card, "Headphone Jack",
				      SND_JACK_HEADPHONE, &headphone_jack,
				      headphone_jack_pins,
				      ARRAY_SIZE(headphone_jack_pins));
		rk_hp_jack_gpio.gpio = machine->gpio_hp_det;
		snd_soc_jack_add_gpios(&headphone_jack, 1, &rk_hp_jack_gpio);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops rk_ops = अणु
	.hw_params = rk_hw_params,
पूर्ण;

SND_SOC_DAILINK_DEFS(audio,
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, शून्य),
			   COMP_CODEC("hdmi-audio-codec.2.auto", "i2s-hifi")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

अटल काष्ठा snd_soc_dai_link rk_dailink = अणु
	.name = "Codecs",
	.stream_name = "Audio",
	.init = rk_init,
	.ops = &rk_ops,
	/* Set codecs as slave */
	.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
		SND_SOC_DAIFMT_CBS_CFS,
	SND_SOC_DAILINK_REG(audio),
पूर्ण;

अटल काष्ठा snd_soc_card snd_soc_card_rk = अणु
	.name = "ROCKCHIP-I2S",
	.dai_link = &rk_dailink,
	.num_links = 1,
	.num_aux_devs = 0,
	.dapm_widमाला_लो = rk_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(rk_dapm_widमाला_लो),
	.controls = rk_mc_controls,
	.num_controls = ARRAY_SIZE(rk_mc_controls),
पूर्ण;

अटल पूर्णांक snd_rk_mc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0;
	काष्ठा snd_soc_card *card = &snd_soc_card_rk;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा rk_drvdata *machine;
	काष्ठा of_phandle_args args;

	machine = devm_kzalloc(&pdev->dev, माप(काष्ठा rk_drvdata),
			       GFP_KERNEL);
	अगर (!machine)
		वापस -ENOMEM;

	card->dev = &pdev->dev;

	machine->gpio_hp_det = of_get_named_gpio(np,
		"rockchip,hp-det-gpios", 0);
	अगर (!gpio_is_valid(machine->gpio_hp_det) && machine->gpio_hp_det != -ENODEV)
		वापस machine->gpio_hp_det;

	machine->gpio_hp_en = of_get_named_gpio(np,
		"rockchip,hp-en-gpios", 0);
	अगर (!gpio_is_valid(machine->gpio_hp_en) && machine->gpio_hp_en != -ENODEV)
		वापस machine->gpio_hp_en;

	अगर (gpio_is_valid(machine->gpio_hp_en)) अणु
		ret = devm_gpio_request_one(&pdev->dev, machine->gpio_hp_en,
					    GPIOF_OUT_INIT_LOW, "hp_en");
		अगर (ret) अणु
			dev_err(card->dev, "cannot get hp_en gpio\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = snd_soc_of_parse_card_name(card, "rockchip,model");
	अगर (ret) अणु
		dev_err(card->dev, "SoC parse card name failed %d\n", ret);
		वापस ret;
	पूर्ण

	rk_dailink.codecs[0].of_node = of_parse_phandle(np,
							"rockchip,audio-codec",
							0);
	अगर (!rk_dailink.codecs[0].of_node) अणु
		dev_err(&pdev->dev,
			"Property 'rockchip,audio-codec' missing or invalid\n");
		वापस -EINVAL;
	पूर्ण
	ret = of_parse_phandle_with_fixed_args(np, "rockchip,audio-codec",
					       0, 0, &args);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"Unable to parse property 'rockchip,audio-codec'\n");
		वापस ret;
	पूर्ण

	ret = snd_soc_get_dai_name(&args, &rk_dailink.codecs[0].dai_name);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Unable to get codec_dai_name\n");
		वापस ret;
	पूर्ण

	rk_dailink.cpus->of_node = of_parse_phandle(np, "rockchip,i2s-controller",
						  0);
	अगर (!rk_dailink.cpus->of_node) अणु
		dev_err(&pdev->dev,
			"Property 'rockchip,i2s-controller' missing or invalid\n");
		वापस -EINVAL;
	पूर्ण

	rk_dailink.platक्रमms->of_node = rk_dailink.cpus->of_node;

	ret = snd_soc_of_parse_audio_routing(card, "rockchip,routing");
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"Unable to parse 'rockchip,routing' property\n");
		वापस ret;
	पूर्ण

	snd_soc_card_set_drvdata(card, machine);

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
	अगर (ret == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"Soc register card failed %d\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id rockchip_sound_of_match[] = अणु
	अणु .compatible = "rockchip,rk3288-hdmi-analog", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, rockchip_sound_of_match);

अटल काष्ठा platक्रमm_driver rockchip_sound_driver = अणु
	.probe = snd_rk_mc_probe,
	.driver = अणु
		.name = DRV_NAME,
		.pm = &snd_soc_pm_ops,
		.of_match_table = rockchip_sound_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rockchip_sound_driver);

MODULE_AUTHOR("Sjoerd Simons <sjoerd.simons@collabora.com>");
MODULE_DESCRIPTION("Rockchip RK3288 machine ASoC driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRV_NAME);
