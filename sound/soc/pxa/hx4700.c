<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SoC audio क्रम HP iPAQ hx4700
 *
 * Copyright (c) 2009 Philipp Zabel
 */

#समावेश <linux/module.h>
#समावेश <linux/समयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>

#समावेश <sound/core.h>
#समावेश <sound/jack.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

#समावेश <mach/hx4700.h>
#समावेश <यंत्र/mach-types.h>
#समावेश "pxa2xx-i2s.h"

अटल काष्ठा snd_soc_jack hs_jack;

/* Headphones jack detection DAPM pin */
अटल काष्ठा snd_soc_jack_pin hs_jack_pin[] = अणु
	अणु
		.pin	= "Headphone Jack",
		.mask	= SND_JACK_HEADPHONE,
	पूर्ण,
	अणु
		.pin	= "Speaker",
		/* disable speaker when hp jack is inserted */
		.mask   = SND_JACK_HEADPHONE,
		.invert	= 1,
	पूर्ण,
पूर्ण;

/* Headphones jack detection GPIO */
अटल काष्ठा snd_soc_jack_gpio hs_jack_gpio = अणु
	.gpio		= GPIO75_HX4700_EARPHONE_nDET,
	.invert		= true,
	.name		= "hp-gpio",
	.report		= SND_JACK_HEADPHONE,
	.debounce_समय	= 200,
पूर्ण;

/*
 * iPAQ hx4700 uses I2S क्रम capture and playback.
 */
अटल पूर्णांक hx4700_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	पूर्णांक ret = 0;

	/* set the I2S प्रणाली घड़ी as output */
	ret = snd_soc_dai_set_sysclk(cpu_dai, PXA2XX_I2S_SYSCLK, 0,
			SND_SOC_CLOCK_OUT);
	अगर (ret < 0)
		वापस ret;

	/* inक्रमm codec driver about घड़ी freq *
	 * (PXA I2S always uses भागider 256)    */
	ret = snd_soc_dai_set_sysclk(codec_dai, 0, 256 * params_rate(params),
			SND_SOC_CLOCK_IN);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops hx4700_ops = अणु
	.hw_params = hx4700_hw_params,
पूर्ण;

अटल पूर्णांक hx4700_spk_घातer(काष्ठा snd_soc_dapm_widget *w,
			    काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	gpio_set_value(GPIO107_HX4700_SPK_nSD, !!SND_SOC_DAPM_EVENT_ON(event));
	वापस 0;
पूर्ण

अटल पूर्णांक hx4700_hp_घातer(काष्ठा snd_soc_dapm_widget *w,
			   काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	gpio_set_value(GPIO92_HX4700_HP_DRIVER, !!SND_SOC_DAPM_EVENT_ON(event));
	वापस 0;
पूर्ण

/* hx4700 machine dapm widमाला_लो */
अटल स्थिर काष्ठा snd_soc_dapm_widget hx4700_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone Jack", hx4700_hp_घातer),
	SND_SOC_DAPM_SPK("Speaker", hx4700_spk_घातer),
	SND_SOC_DAPM_MIC("Built-in Microphone", शून्य),
पूर्ण;

/* hx4700 machine audio_map */
अटल स्थिर काष्ठा snd_soc_dapm_route hx4700_audio_map[] = अणु

	/* Headphone connected to LOUT, ROUT */
	अणु"Headphone Jack", शून्य, "LOUT"पूर्ण,
	अणु"Headphone Jack", शून्य, "ROUT"पूर्ण,

	/* Speaker connected to MOUT2 */
	अणु"Speaker", शून्य, "MOUT2"पूर्ण,

	/* Microphone connected to MICIN */
	अणु"MICIN", शून्य, "Built-in Microphone"पूर्ण,
	अणु"AIN", शून्य, "MICOUT"पूर्ण,
पूर्ण;

/*
 * Logic क्रम a ak4641 as connected on a HP iPAQ hx4700
 */
अटल पूर्णांक hx4700_ak4641_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	पूर्णांक err;

	/* Jack detection API stuff */
	err = snd_soc_card_jack_new(rtd->card, "Headphone Jack",
				    SND_JACK_HEADPHONE, &hs_jack, hs_jack_pin,
				    ARRAY_SIZE(hs_jack_pin));
	अगर (err)
		वापस err;

	err = snd_soc_jack_add_gpios(&hs_jack, 1, &hs_jack_gpio);

	वापस err;
पूर्ण

/* hx4700 digital audio पूर्णांकerface glue - connects codec <--> CPU */
SND_SOC_DAILINK_DEFS(ak4641,
	DAILINK_COMP_ARRAY(COMP_CPU("pxa2xx-i2s")),
	DAILINK_COMP_ARRAY(COMP_CODEC("ak4641.0-0012", "ak4641-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("pxa-pcm-audio")));

अटल काष्ठा snd_soc_dai_link hx4700_dai = अणु
	.name = "ak4641",
	.stream_name = "AK4641",
	.init = hx4700_ak4641_init,
	.dai_fmt = SND_SOC_DAIFMT_MSB | SND_SOC_DAIFMT_NB_NF |
		   SND_SOC_DAIFMT_CBS_CFS,
	.ops = &hx4700_ops,
	SND_SOC_DAILINK_REG(ak4641),
पूर्ण;

/* hx4700 audio machine driver */
अटल काष्ठा snd_soc_card snd_soc_card_hx4700 = अणु
	.name			= "iPAQ hx4700",
	.owner			= THIS_MODULE,
	.dai_link		= &hx4700_dai,
	.num_links		= 1,
	.dapm_widमाला_लो		= hx4700_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(hx4700_dapm_widमाला_लो),
	.dapm_routes		= hx4700_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(hx4700_audio_map),
	.fully_routed		= true,
पूर्ण;

अटल काष्ठा gpio hx4700_audio_gpios[] = अणु
	अणु GPIO107_HX4700_SPK_nSD, GPIOF_OUT_INIT_HIGH, "SPK_POWER" पूर्ण,
	अणु GPIO92_HX4700_HP_DRIVER, GPIOF_OUT_INIT_LOW, "EP_POWER" पूर्ण,
पूर्ण;

अटल पूर्णांक hx4700_audio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	अगर (!machine_is_h4700())
		वापस -ENODEV;

	ret = gpio_request_array(hx4700_audio_gpios,
				ARRAY_SIZE(hx4700_audio_gpios));
	अगर (ret)
		वापस ret;

	snd_soc_card_hx4700.dev = &pdev->dev;
	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, &snd_soc_card_hx4700);
	अगर (ret)
		gpio_मुक्त_array(hx4700_audio_gpios,
				ARRAY_SIZE(hx4700_audio_gpios));

	वापस ret;
पूर्ण

अटल पूर्णांक hx4700_audio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	gpio_set_value(GPIO92_HX4700_HP_DRIVER, 0);
	gpio_set_value(GPIO107_HX4700_SPK_nSD, 0);

	gpio_मुक्त_array(hx4700_audio_gpios, ARRAY_SIZE(hx4700_audio_gpios));
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver hx4700_audio_driver = अणु
	.driver	= अणु
		.name = "hx4700-audio",
		.pm = &snd_soc_pm_ops,
	पूर्ण,
	.probe	= hx4700_audio_probe,
	.हटाओ	= hx4700_audio_हटाओ,
पूर्ण;

module_platक्रमm_driver(hx4700_audio_driver);

MODULE_AUTHOR("Philipp Zabel");
MODULE_DESCRIPTION("ALSA SoC iPAQ hx4700");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:hx4700-audio");
