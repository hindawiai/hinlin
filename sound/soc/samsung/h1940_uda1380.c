<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// h1940_uda1380.c - ALSA SoC Audio Layer
//
// Copyright (c) 2010 Arnaud Patard <arnaud.patard@rtp-net.org>
// Copyright (c) 2010 Vasily Khoruzhick <anarsoul@gmail.com>
//
// Based on version from Arnaud Patard <arnaud.patard@rtp-net.org>

#समावेश <linux/types.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/module.h>

#समावेश <sound/soc.h>
#समावेश <sound/jack.h>

#समावेश "regs-iis.h"
#समावेश "s3c24xx-i2s.h"

अटल स्थिर अचिन्हित पूर्णांक rates[] = अणु
	11025,
	22050,
	44100,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list hw_rates = अणु
	.count = ARRAY_SIZE(rates),
	.list = rates,
पूर्ण;

अटल काष्ठा gpio_desc *gpiod_speaker_घातer;

अटल काष्ठा snd_soc_jack hp_jack;

अटल काष्ठा snd_soc_jack_pin hp_jack_pins[] = अणु
	अणु
		.pin	= "Headphone Jack",
		.mask	= SND_JACK_HEADPHONE,
	पूर्ण,
	अणु
		.pin	= "Speaker",
		.mask	= SND_JACK_HEADPHONE,
		.invert	= 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_jack_gpio hp_jack_gpios[] = अणु
	अणु
		.name			= "hp-gpio",
		.report			= SND_JACK_HEADPHONE,
		.invert			= 1,
		.debounce_समय		= 200,
	पूर्ण,
पूर्ण;

अटल पूर्णांक h1940_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	वापस snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0,
					SNDRV_PCM_HW_PARAM_RATE,
					&hw_rates);
पूर्ण

अटल पूर्णांक h1940_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	पूर्णांक भाग;
	पूर्णांक ret;
	अचिन्हित पूर्णांक rate = params_rate(params);

	चयन (rate) अणु
	हाल 11025:
	हाल 22050:
	हाल 44100:
		भाग = s3c24xx_i2s_get_घड़ीrate() / (384 * rate);
		अगर (s3c24xx_i2s_get_घड़ीrate() % (384 * rate) > (192 * rate))
			भाग++;
		अवरोध;
	शेष:
		dev_err(rtd->dev, "%s: rate %d is not supported\n",
			__func__, rate);
		वापस -EINVAL;
	पूर्ण

	/* select घड़ी source */
	ret = snd_soc_dai_set_sysclk(cpu_dai, S3C24XX_CLKSRC_PCLK, rate,
			SND_SOC_CLOCK_OUT);
	अगर (ret < 0)
		वापस ret;

	/* set MCLK भागision क्रम sample rate */
	ret = snd_soc_dai_set_clkभाग(cpu_dai, S3C24XX_DIV_MCLK,
		S3C2410_IISMOD_384FS);
	अगर (ret < 0)
		वापस ret;

	/* set BCLK भागision क्रम sample rate */
	ret = snd_soc_dai_set_clkभाग(cpu_dai, S3C24XX_DIV_BCLK,
		S3C2410_IISMOD_32FS);
	अगर (ret < 0)
		वापस ret;

	/* set prescaler भागision क्रम sample rate */
	ret = snd_soc_dai_set_clkभाग(cpu_dai, S3C24XX_DIV_PRESCALER,
		S3C24XX_PRESCALE(भाग, भाग));
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_ops h1940_ops = अणु
	.startup	= h1940_startup,
	.hw_params	= h1940_hw_params,
पूर्ण;

अटल पूर्णांक h1940_spk_घातer(काष्ठा snd_soc_dapm_widget *w,
				काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	अगर (SND_SOC_DAPM_EVENT_ON(event))
		gpiod_set_value(gpiod_speaker_घातer, 1);
	अन्यथा
		gpiod_set_value(gpiod_speaker_घातer, 0);

	वापस 0;
पूर्ण

/* h1940 machine dapm widमाला_लो */
अटल स्थिर काष्ठा snd_soc_dapm_widget uda1380_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_MIC("Mic Jack", शून्य),
	SND_SOC_DAPM_SPK("Speaker", h1940_spk_घातer),
पूर्ण;

/* h1940 machine audio_map */
अटल स्थिर काष्ठा snd_soc_dapm_route audio_map[] = अणु
	/* headphone connected to VOUTLHP, VOUTRHP */
	अणु"Headphone Jack", शून्य, "VOUTLHP"पूर्ण,
	अणु"Headphone Jack", शून्य, "VOUTRHP"पूर्ण,

	/* ext speaker connected to VOUTL, VOUTR  */
	अणु"Speaker", शून्य, "VOUTL"पूर्ण,
	अणु"Speaker", शून्य, "VOUTR"पूर्ण,

	/* mic is connected to VINM */
	अणु"VINM", शून्य, "Mic Jack"पूर्ण,
पूर्ण;

अटल पूर्णांक h1940_uda1380_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	snd_soc_card_jack_new(rtd->card, "Headphone Jack", SND_JACK_HEADPHONE,
		&hp_jack, hp_jack_pins, ARRAY_SIZE(hp_jack_pins));

	snd_soc_jack_add_gpios(&hp_jack, ARRAY_SIZE(hp_jack_gpios),
		hp_jack_gpios);

	वापस 0;
पूर्ण

/* s3c24xx digital audio पूर्णांकerface glue - connects codec <--> CPU */
SND_SOC_DAILINK_DEFS(uda1380,
	DAILINK_COMP_ARRAY(COMP_CPU("s3c24xx-iis")),
	DAILINK_COMP_ARRAY(COMP_CODEC("uda1380-codec.0-001a", "uda1380-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("s3c24xx-iis")));

अटल काष्ठा snd_soc_dai_link h1940_uda1380_dai[] = अणु
	अणु
		.name		= "uda1380",
		.stream_name	= "UDA1380 Duplex",
		.init		= h1940_uda1380_init,
		.dai_fmt	= SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
				  SND_SOC_DAIFMT_CBS_CFS,
		.ops		= &h1940_ops,
		SND_SOC_DAILINK_REG(uda1380),
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_card h1940_asoc = अणु
	.name = "h1940",
	.owner = THIS_MODULE,
	.dai_link = h1940_uda1380_dai,
	.num_links = ARRAY_SIZE(h1940_uda1380_dai),

	.dapm_widमाला_लो = uda1380_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(uda1380_dapm_widमाला_लो),
	.dapm_routes = audio_map,
	.num_dapm_routes = ARRAY_SIZE(audio_map),
पूर्ण;

अटल पूर्णांक h1940_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;

	h1940_asoc.dev = dev;
	hp_jack_gpios[0].gpiod_dev = dev;
	gpiod_speaker_घातer = devm_gpiod_get(&pdev->dev, "speaker-power",
					     GPIOD_OUT_LOW);

	अगर (IS_ERR(gpiod_speaker_घातer)) अणु
		dev_err(dev, "Could not get gpio\n");
		वापस PTR_ERR(gpiod_speaker_घातer);
	पूर्ण

	वापस devm_snd_soc_रेजिस्टर_card(dev, &h1940_asoc);
पूर्ण

अटल काष्ठा platक्रमm_driver h1940_audio_driver = अणु
	.driver = अणु
		.name = "h1940-audio",
		.pm = &snd_soc_pm_ops,
	पूर्ण,
	.probe = h1940_probe,
पूर्ण;
module_platक्रमm_driver(h1940_audio_driver);

/* Module inक्रमmation */
MODULE_AUTHOR("Arnaud Patard, Vasily Khoruzhick");
MODULE_DESCRIPTION("ALSA SoC H1940");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:h1940-audio");
