<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// rx1950.c - ALSA SoC Audio Layer
//
// Copyright (c) 2010 Vasily Khoruzhick <anarsoul@gmail.com>
//
// Based on smdk2440.c and magician.c
//
// Authors: Graeme Gregory graeme.gregory@wolfsonmicro.com
//          Philipp Zabel <philipp.zabel@gmail.com>
//          Denis Grigoriev <dgreenday@gmail.com>
//          Vasily Khoruzhick <anarsoul@gmail.com>

#समावेश <linux/types.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>

#समावेश <sound/soc.h>
#समावेश <sound/jack.h>

#समावेश "regs-iis.h"
#समावेश "s3c24xx-i2s.h"

अटल पूर्णांक rx1950_uda1380_init(काष्ठा snd_soc_pcm_runसमय *rtd);
अटल पूर्णांक rx1950_startup(काष्ठा snd_pcm_substream *substream);
अटल पूर्णांक rx1950_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params);
अटल पूर्णांक rx1950_spk_घातer(काष्ठा snd_soc_dapm_widget *w,
				काष्ठा snd_kcontrol *kcontrol, पूर्णांक event);

अटल स्थिर अचिन्हित पूर्णांक rates[] = अणु
	16000,
	44100,
	48000,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list hw_rates = अणु
	.count = ARRAY_SIZE(rates),
	.list = rates,
पूर्ण;

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
	[0] = अणु
		.name			= "hp-gpio",
		.report			= SND_JACK_HEADPHONE,
		.invert			= 1,
		.debounce_समय		= 200,
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_ops rx1950_ops = अणु
	.startup	= rx1950_startup,
	.hw_params	= rx1950_hw_params,
पूर्ण;

/* s3c24xx digital audio पूर्णांकerface glue - connects codec <--> CPU */
SND_SOC_DAILINK_DEFS(uda1380,
	DAILINK_COMP_ARRAY(COMP_CPU("s3c24xx-iis")),
	DAILINK_COMP_ARRAY(COMP_CODEC("uda1380-codec.0-001a",
				      "uda1380-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("s3c24xx-iis")));

अटल काष्ठा snd_soc_dai_link rx1950_uda1380_dai[] = अणु
	अणु
		.name		= "uda1380",
		.stream_name	= "UDA1380 Duplex",
		.init		= rx1950_uda1380_init,
		.dai_fmt	= SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
				  SND_SOC_DAIFMT_CBS_CFS,
		.ops		= &rx1950_ops,
		SND_SOC_DAILINK_REG(uda1380),
	पूर्ण,
पूर्ण;

/* rx1950 machine dapm widमाला_लो */
अटल स्थिर काष्ठा snd_soc_dapm_widget uda1380_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_MIC("Mic Jack", शून्य),
	SND_SOC_DAPM_SPK("Speaker", rx1950_spk_घातer),
पूर्ण;

/* rx1950 machine audio_map */
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

अटल काष्ठा snd_soc_card rx1950_asoc = अणु
	.name = "rx1950",
	.owner = THIS_MODULE,
	.dai_link = rx1950_uda1380_dai,
	.num_links = ARRAY_SIZE(rx1950_uda1380_dai),

	.dapm_widमाला_लो = uda1380_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(uda1380_dapm_widमाला_लो),
	.dapm_routes = audio_map,
	.num_dapm_routes = ARRAY_SIZE(audio_map),
पूर्ण;

अटल पूर्णांक rx1950_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	वापस snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0,
					SNDRV_PCM_HW_PARAM_RATE,
					&hw_rates);
पूर्ण

काष्ठा gpio_desc *gpiod_speaker_घातer;

अटल पूर्णांक rx1950_spk_घातer(काष्ठा snd_soc_dapm_widget *w,
				काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	अगर (SND_SOC_DAPM_EVENT_ON(event))
		gpiod_set_value(gpiod_speaker_घातer, 1);
	अन्यथा
		gpiod_set_value(gpiod_speaker_घातer, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक rx1950_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	पूर्णांक भाग;
	पूर्णांक ret;
	अचिन्हित पूर्णांक rate = params_rate(params);
	पूर्णांक clk_source, fs_mode;

	चयन (rate) अणु
	हाल 16000:
	हाल 48000:
		clk_source = S3C24XX_CLKSRC_PCLK;
		fs_mode = S3C2410_IISMOD_256FS;
		भाग = s3c24xx_i2s_get_घड़ीrate() / (256 * rate);
		अगर (s3c24xx_i2s_get_घड़ीrate() % (256 * rate) > (128 * rate))
			भाग++;
		अवरोध;
	हाल 44100:
	हाल 88200:
		clk_source = S3C24XX_CLKSRC_MPLL;
		fs_mode = S3C2410_IISMOD_384FS;
		भाग = 1;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "%s: rate %d is not supported\n",
			__func__, rate);
		वापस -EINVAL;
	पूर्ण

	/* select घड़ी source */
	ret = snd_soc_dai_set_sysclk(cpu_dai, clk_source, rate,
			SND_SOC_CLOCK_OUT);
	अगर (ret < 0)
		वापस ret;

	/* set MCLK भागision क्रम sample rate */
	ret = snd_soc_dai_set_clkभाग(cpu_dai, S3C24XX_DIV_MCLK,
		fs_mode);
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

अटल पूर्णांक rx1950_uda1380_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	snd_soc_card_jack_new(rtd->card, "Headphone Jack", SND_JACK_HEADPHONE,
		&hp_jack, hp_jack_pins, ARRAY_SIZE(hp_jack_pins));

	snd_soc_jack_add_gpios(&hp_jack, ARRAY_SIZE(hp_jack_gpios),
		hp_jack_gpios);

	वापस 0;
पूर्ण

अटल पूर्णांक rx1950_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;

	/* configure some gpios */
	gpiod_speaker_घातer = devm_gpiod_get(dev, "speaker-power", GPIOD_OUT_LOW);
	अगर (IS_ERR(gpiod_speaker_घातer)) अणु
		dev_err(dev, "cannot get gpio\n");
		वापस PTR_ERR(gpiod_speaker_घातer);
	पूर्ण

	hp_jack_gpios[0].gpiod_dev = dev;
	rx1950_asoc.dev = dev;

	वापस devm_snd_soc_रेजिस्टर_card(dev, &rx1950_asoc);
पूर्ण

काष्ठा platक्रमm_driver rx1950_audio = अणु
	.driver = अणु
		.name = "rx1950-audio",
		.pm = &snd_soc_pm_ops,
	पूर्ण,
	.probe = rx1950_probe,
पूर्ण;

module_platक्रमm_driver(rx1950_audio);

/* Module inक्रमmation */
MODULE_AUTHOR("Vasily Khoruzhick");
MODULE_DESCRIPTION("ALSA SoC RX1950");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:rx1950-audio");
