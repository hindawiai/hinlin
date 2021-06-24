<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright 2010 Maurus Cuelenaere <mcuelenaere@gmail.com>
//
// Based on smdk6410_wm8987.c
//     Copyright 2007 Wolfson Microelectronics PLC. - linux@wolfsonmicro.com
//     Graeme Gregory - graeme.gregory@wolfsonmicro.com

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>

#समावेश <sound/soc.h>
#समावेश <sound/jack.h>

#समावेश "i2s.h"
#समावेश "../codecs/wm8750.h"

/*
 * WM8987 is रेजिस्टर compatible with WM8750, so using that as base driver.
 */

अटल काष्ठा snd_soc_card snd_soc_smartq;

अटल पूर्णांक smartq_hअगरi_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	अचिन्हित पूर्णांक clk = 0;
	पूर्णांक ret;

	चयन (params_rate(params)) अणु
	हाल 8000:
	हाल 16000:
	हाल 32000:
	हाल 48000:
	हाल 96000:
		clk = 12288000;
		अवरोध;
	हाल 11025:
	हाल 22050:
	हाल 44100:
	हाल 88200:
		clk = 11289600;
		अवरोध;
	पूर्ण

	/* Use PCLK क्रम I2S संकेत generation */
	ret = snd_soc_dai_set_sysclk(cpu_dai, SAMSUNG_I2S_RCLKSRC_0,
					0, SND_SOC_CLOCK_IN);
	अगर (ret < 0)
		वापस ret;

	/* Gate the RCLK output on PAD */
	ret = snd_soc_dai_set_sysclk(cpu_dai, SAMSUNG_I2S_CDCLK,
					0, SND_SOC_CLOCK_IN);
	अगर (ret < 0)
		वापस ret;

	/* set the codec प्रणाली घड़ी क्रम DAC and ADC */
	ret = snd_soc_dai_set_sysclk(codec_dai, WM8750_SYSCLK, clk,
				     SND_SOC_CLOCK_IN);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

/*
 * SmartQ WM8987 HiFi DAI operations.
 */
अटल काष्ठा snd_soc_ops smartq_hअगरi_ops = अणु
	.hw_params = smartq_hअगरi_hw_params,
पूर्ण;

अटल काष्ठा snd_soc_jack smartq_jack;

अटल काष्ठा snd_soc_jack_pin smartq_jack_pins[] = अणु
	/* Disable speaker when headphone is plugged in */
	अणु
		.pin	= "Internal Speaker",
		.mask	= SND_JACK_HEADPHONE,
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_jack_gpio smartq_jack_gpios[] = अणु
	अणु
		.gpio		= -1,
		.name		= "headphone detect",
		.report		= SND_JACK_HEADPHONE,
		.debounce_समय	= 200,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8987_smartq_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Internal Speaker"),
	SOC_DAPM_PIN_SWITCH("Headphone Jack"),
	SOC_DAPM_PIN_SWITCH("Internal Mic"),
पूर्ण;

अटल पूर्णांक smartq_speaker_event(काष्ठा snd_soc_dapm_widget *w,
				काष्ठा snd_kcontrol *k,
				पूर्णांक event)
अणु
	काष्ठा gpio_desc *gpio = snd_soc_card_get_drvdata(&snd_soc_smartq);

	gpiod_set_value(gpio, SND_SOC_DAPM_EVENT_OFF(event));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8987_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_SPK("Internal Speaker", smartq_speaker_event),
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_MIC("Internal Mic", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route audio_map[] = अणु
	अणु"Headphone Jack", शून्य, "LOUT2"पूर्ण,
	अणु"Headphone Jack", शून्य, "ROUT2"पूर्ण,

	अणु"Internal Speaker", शून्य, "LOUT2"पूर्ण,
	अणु"Internal Speaker", शून्य, "ROUT2"पूर्ण,

	अणु"Mic Bias", शून्य, "Internal Mic"पूर्ण,
	अणु"LINPUT2", शून्य, "Mic Bias"पूर्ण,
पूर्ण;

अटल पूर्णांक smartq_wm8987_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_dapm_context *dapm = &rtd->card->dapm;
	पूर्णांक err = 0;

	/* set endpoपूर्णांकs to not connected */
	snd_soc_dapm_nc_pin(dapm, "LINPUT1");
	snd_soc_dapm_nc_pin(dapm, "RINPUT1");
	snd_soc_dapm_nc_pin(dapm, "OUT3");
	snd_soc_dapm_nc_pin(dapm, "ROUT1");

	/* Headphone jack detection */
	err = snd_soc_card_jack_new(rtd->card, "Headphone Jack",
				    SND_JACK_HEADPHONE, &smartq_jack,
				    smartq_jack_pins,
				    ARRAY_SIZE(smartq_jack_pins));
	अगर (err)
		वापस err;

	err = snd_soc_jack_add_gpios(&smartq_jack,
				     ARRAY_SIZE(smartq_jack_gpios),
				     smartq_jack_gpios);

	वापस err;
पूर्ण

SND_SOC_DAILINK_DEFS(wm8987,
	DAILINK_COMP_ARRAY(COMP_CPU("samsung-i2s.0")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm8750.0-0x1a", "wm8750-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("samsung-i2s.0")));

अटल काष्ठा snd_soc_dai_link smartq_dai[] = अणु
	अणु
		.name		= "wm8987",
		.stream_name	= "SmartQ Hi-Fi",
		.init		= smartq_wm8987_init,
		.dai_fmt	= SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
				  SND_SOC_DAIFMT_CBS_CFS,
		.ops		= &smartq_hअगरi_ops,
		SND_SOC_DAILINK_REG(wm8987),
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_card snd_soc_smartq = अणु
	.name = "SmartQ",
	.owner = THIS_MODULE,
	.dai_link = smartq_dai,
	.num_links = ARRAY_SIZE(smartq_dai),

	.dapm_widमाला_लो = wm8987_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(wm8987_dapm_widमाला_लो),
	.dapm_routes = audio_map,
	.num_dapm_routes = ARRAY_SIZE(audio_map),
	.controls = wm8987_smartq_controls,
	.num_controls = ARRAY_SIZE(wm8987_smartq_controls),
पूर्ण;

अटल पूर्णांक smartq_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gpio_desc *gpio;
	पूर्णांक ret;

	platक्रमm_set_drvdata(pdev, &snd_soc_smartq);

	/* Initialise GPIOs used by amplअगरiers */
	gpio = devm_gpiod_get(&pdev->dev, "amplifiers shutdown",
			      GPIOD_OUT_HIGH);
	अगर (IS_ERR(gpio)) अणु
		dev_err(&pdev->dev, "Failed to register GPK12\n");
		ret = PTR_ERR(gpio);
		जाओ out;
	पूर्ण
	snd_soc_card_set_drvdata(&snd_soc_smartq, gpio);

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, &snd_soc_smartq);
	अगर (ret)
		dev_err(&pdev->dev, "Failed to register card\n");

out:
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver smartq_driver = अणु
	.driver = अणु
		.name = "smartq-audio",
	पूर्ण,
	.probe = smartq_probe,
पूर्ण;

module_platक्रमm_driver(smartq_driver);

/* Module inक्रमmation */
MODULE_AUTHOR("Maurus Cuelenaere <mcuelenaere@gmail.com>");
MODULE_DESCRIPTION("ALSA SoC SmartQ WM8987");
MODULE_LICENSE("GPL");
