<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/sound/soc/pxa/z2.c
 *
 * SoC Audio driver क्रम Aeronix Zipit Z2
 *
 * Copyright (C) 2009 Ken McGuire <kenm@desertweyr.com>
 * Copyright (C) 2010 Marek Vasut <marek.vasut@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/समयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpपन.स>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/jack.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <mach/hardware.h>
#समावेश <mach/audपन.स>
#समावेश <mach/z2.h>

#समावेश "../codecs/wm8750.h"
#समावेश "pxa2xx-i2s.h"

अटल काष्ठा snd_soc_card snd_soc_z2;

अटल पूर्णांक z2_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	अचिन्हित पूर्णांक clk = 0;
	पूर्णांक ret = 0;

	चयन (params_rate(params)) अणु
	हाल 8000:
	हाल 16000:
	हाल 48000:
	हाल 96000:
		clk = 12288000;
		अवरोध;
	हाल 11025:
	हाल 22050:
	हाल 44100:
		clk = 11289600;
		अवरोध;
	पूर्ण

	/* set the codec प्रणाली घड़ी क्रम DAC and ADC */
	ret = snd_soc_dai_set_sysclk(codec_dai, WM8750_SYSCLK, clk,
		SND_SOC_CLOCK_IN);
	अगर (ret < 0)
		वापस ret;

	/* set the I2S प्रणाली घड़ी as input (unused) */
	ret = snd_soc_dai_set_sysclk(cpu_dai, PXA2XX_I2S_SYSCLK, 0,
		SND_SOC_CLOCK_IN);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_jack hs_jack;

/* Headset jack detection DAPM pins */
अटल काष्ठा snd_soc_jack_pin hs_jack_pins[] = अणु
	अणु
		.pin	= "Mic Jack",
		.mask	= SND_JACK_MICROPHONE,
	पूर्ण,
	अणु
		.pin	= "Headphone Jack",
		.mask	= SND_JACK_HEADPHONE,
	पूर्ण,
	अणु
		.pin    = "Ext Spk",
		.mask   = SND_JACK_HEADPHONE,
		.invert = 1
	पूर्ण,
पूर्ण;

/* Headset jack detection gpios */
अटल काष्ठा snd_soc_jack_gpio hs_jack_gpios[] = अणु
	अणु
		.gpio		= GPIO37_ZIPITZ2_HEADSET_DETECT,
		.name		= "hsdet-gpio",
		.report		= SND_JACK_HEADSET,
		.debounce_समय	= 200,
		.invert		= 1,
	पूर्ण,
पूर्ण;

/* z2 machine dapm widमाला_लो */
अटल स्थिर काष्ठा snd_soc_dapm_widget wm8750_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_MIC("Mic Jack", शून्य),
	SND_SOC_DAPM_SPK("Ext Spk", शून्य),

	/* headset is a mic and mono headphone */
	SND_SOC_DAPM_HP("Headset Jack", शून्य),
पूर्ण;

/* Z2 machine audio_map */
अटल स्थिर काष्ठा snd_soc_dapm_route z2_audio_map[] = अणु

	/* headphone connected to LOUT1, ROUT1 */
	अणु"Headphone Jack", शून्य, "LOUT1"पूर्ण,
	अणु"Headphone Jack", शून्य, "ROUT1"पूर्ण,

	/* ext speaker connected to LOUT2, ROUT2  */
	अणु"Ext Spk", शून्य, "ROUT2"पूर्ण,
	अणु"Ext Spk", शून्य, "LOUT2"पूर्ण,

	/* mic is connected to R input 2 - with bias */
	अणु"RINPUT2", शून्य, "Mic Bias"पूर्ण,
	अणु"Mic Bias", शून्य, "Mic Jack"पूर्ण,
पूर्ण;

/*
 * Logic क्रम a wm8750 as connected on a Z2 Device
 */
अटल पूर्णांक z2_wm8750_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	पूर्णांक ret;

	/* Jack detection API stuff */
	ret = snd_soc_card_jack_new(rtd->card, "Headset Jack", SND_JACK_HEADSET,
				    &hs_jack, hs_jack_pins,
				    ARRAY_SIZE(hs_jack_pins));
	अगर (ret)
		जाओ err;

	ret = snd_soc_jack_add_gpios(&hs_jack, ARRAY_SIZE(hs_jack_gpios),
				hs_jack_gpios);
	अगर (ret)
		जाओ err;

	वापस 0;

err:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops z2_ops = अणु
	.hw_params = z2_hw_params,
पूर्ण;

/* z2 digital audio पूर्णांकerface glue - connects codec <--> CPU */
SND_SOC_DAILINK_DEFS(wm8750,
	DAILINK_COMP_ARRAY(COMP_CPU("pxa2xx-i2s")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm8750.0-001b", "wm8750-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("pxa-pcm-audio")));

अटल काष्ठा snd_soc_dai_link z2_dai = अणु
	.name		= "wm8750",
	.stream_name	= "WM8750",
	.init		= z2_wm8750_init,
	.dai_fmt	= SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			  SND_SOC_DAIFMT_CBS_CFS,
	.ops		= &z2_ops,
	SND_SOC_DAILINK_REG(wm8750),
पूर्ण;

/* z2 audio machine driver */
अटल काष्ठा snd_soc_card snd_soc_z2 = अणु
	.name		= "Z2",
	.owner		= THIS_MODULE,
	.dai_link	= &z2_dai,
	.num_links	= 1,

	.dapm_widमाला_लो = wm8750_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(wm8750_dapm_widमाला_लो),
	.dapm_routes = z2_audio_map,
	.num_dapm_routes = ARRAY_SIZE(z2_audio_map),
	.fully_routed = true,
पूर्ण;

अटल काष्ठा platक्रमm_device *z2_snd_device;

अटल पूर्णांक __init z2_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!machine_is_zipit2())
		वापस -ENODEV;

	z2_snd_device = platक्रमm_device_alloc("soc-audio", -1);
	अगर (!z2_snd_device)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(z2_snd_device, &snd_soc_z2);
	ret = platक्रमm_device_add(z2_snd_device);

	अगर (ret)
		platक्रमm_device_put(z2_snd_device);

	वापस ret;
पूर्ण

अटल व्योम __निकास z2_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(z2_snd_device);
पूर्ण

module_init(z2_init);
module_निकास(z2_निकास);

MODULE_AUTHOR("Ken McGuire <kenm@desertweyr.com>, "
		"Marek Vasut <marek.vasut@gmail.com>");
MODULE_DESCRIPTION("ALSA SoC ZipitZ2");
MODULE_LICENSE("GPL");
