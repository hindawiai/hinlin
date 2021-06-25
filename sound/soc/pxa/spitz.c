<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * spitz.c  --  SoC audio क्रम Sharp SL-Cxx00 models Spitz, Borzoi and Akita
 *
 * Copyright 2005 Wolfson Microelectronics PLC.
 * Copyright 2005 Openedhand Ltd.
 *
 * Authors: Liam Girdwood <lrg@slimlogic.co.uk>
 *          Riअक्षरd Purdie <riअक्षरd@खोलोedhand.com>
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

#समावेश <यंत्र/mach-types.h>
#समावेश <mach/spitz.h>
#समावेश "../codecs/wm8750.h"
#समावेश "pxa2xx-i2s.h"

#घोषणा SPITZ_HP        0
#घोषणा SPITZ_MIC       1
#घोषणा SPITZ_LINE      2
#घोषणा SPITZ_HEADSET   3
#घोषणा SPITZ_HP_OFF    4
#घोषणा SPITZ_SPK_ON    0
#घोषणा SPITZ_SPK_OFF   1

 /* audio घड़ी in Hz - rounded from 12.235MHz */
#घोषणा SPITZ_AUDIO_CLOCK 12288000

अटल पूर्णांक spitz_jack_func;
अटल पूर्णांक spitz_spk_func;
अटल पूर्णांक spitz_mic_gpio;

अटल व्योम spitz_ext_control(काष्ठा snd_soc_dapm_context *dapm)
अणु
	snd_soc_dapm_mutex_lock(dapm);

	अगर (spitz_spk_func == SPITZ_SPK_ON)
		snd_soc_dapm_enable_pin_unlocked(dapm, "Ext Spk");
	अन्यथा
		snd_soc_dapm_disable_pin_unlocked(dapm, "Ext Spk");

	/* set up jack connection */
	चयन (spitz_jack_func) अणु
	हाल SPITZ_HP:
		/* enable and unmute hp jack, disable mic bias */
		snd_soc_dapm_disable_pin_unlocked(dapm, "Headset Jack");
		snd_soc_dapm_disable_pin_unlocked(dapm, "Mic Jack");
		snd_soc_dapm_disable_pin_unlocked(dapm, "Line Jack");
		snd_soc_dapm_enable_pin_unlocked(dapm, "Headphone Jack");
		gpio_set_value(SPITZ_GPIO_MUTE_L, 1);
		gpio_set_value(SPITZ_GPIO_MUTE_R, 1);
		अवरोध;
	हाल SPITZ_MIC:
		/* enable mic jack and bias, mute hp */
		snd_soc_dapm_disable_pin_unlocked(dapm, "Headphone Jack");
		snd_soc_dapm_disable_pin_unlocked(dapm, "Headset Jack");
		snd_soc_dapm_disable_pin_unlocked(dapm, "Line Jack");
		snd_soc_dapm_enable_pin_unlocked(dapm, "Mic Jack");
		gpio_set_value(SPITZ_GPIO_MUTE_L, 0);
		gpio_set_value(SPITZ_GPIO_MUTE_R, 0);
		अवरोध;
	हाल SPITZ_LINE:
		/* enable line jack, disable mic bias and mute hp */
		snd_soc_dapm_disable_pin_unlocked(dapm, "Headphone Jack");
		snd_soc_dapm_disable_pin_unlocked(dapm, "Headset Jack");
		snd_soc_dapm_disable_pin_unlocked(dapm, "Mic Jack");
		snd_soc_dapm_enable_pin_unlocked(dapm, "Line Jack");
		gpio_set_value(SPITZ_GPIO_MUTE_L, 0);
		gpio_set_value(SPITZ_GPIO_MUTE_R, 0);
		अवरोध;
	हाल SPITZ_HEADSET:
		/* enable and unmute headset jack enable mic bias, mute L hp */
		snd_soc_dapm_disable_pin_unlocked(dapm, "Headphone Jack");
		snd_soc_dapm_enable_pin_unlocked(dapm, "Mic Jack");
		snd_soc_dapm_disable_pin_unlocked(dapm, "Line Jack");
		snd_soc_dapm_enable_pin_unlocked(dapm, "Headset Jack");
		gpio_set_value(SPITZ_GPIO_MUTE_L, 0);
		gpio_set_value(SPITZ_GPIO_MUTE_R, 1);
		अवरोध;
	हाल SPITZ_HP_OFF:

		/* jack हटाओd, everything off */
		snd_soc_dapm_disable_pin_unlocked(dapm, "Headphone Jack");
		snd_soc_dapm_disable_pin_unlocked(dapm, "Headset Jack");
		snd_soc_dapm_disable_pin_unlocked(dapm, "Mic Jack");
		snd_soc_dapm_disable_pin_unlocked(dapm, "Line Jack");
		gpio_set_value(SPITZ_GPIO_MUTE_L, 0);
		gpio_set_value(SPITZ_GPIO_MUTE_R, 0);
		अवरोध;
	पूर्ण

	snd_soc_dapm_sync_unlocked(dapm);

	snd_soc_dapm_mutex_unlock(dapm);
पूर्ण

अटल पूर्णांक spitz_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);

	/* check the jack status at stream startup */
	spitz_ext_control(&rtd->card->dapm);

	वापस 0;
पूर्ण

अटल पूर्णांक spitz_hw_params(काष्ठा snd_pcm_substream *substream,
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

अटल स्थिर काष्ठा snd_soc_ops spitz_ops = अणु
	.startup = spitz_startup,
	.hw_params = spitz_hw_params,
पूर्ण;

अटल पूर्णांक spitz_get_jack(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.क्रमागतerated.item[0] = spitz_jack_func;
	वापस 0;
पूर्ण

अटल पूर्णांक spitz_set_jack(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_card *card = snd_kcontrol_chip(kcontrol);

	अगर (spitz_jack_func == ucontrol->value.क्रमागतerated.item[0])
		वापस 0;

	spitz_jack_func = ucontrol->value.क्रमागतerated.item[0];
	spitz_ext_control(&card->dapm);
	वापस 1;
पूर्ण

अटल पूर्णांक spitz_get_spk(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.क्रमागतerated.item[0] = spitz_spk_func;
	वापस 0;
पूर्ण

अटल पूर्णांक spitz_set_spk(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_card *card = snd_kcontrol_chip(kcontrol);

	अगर (spitz_spk_func == ucontrol->value.क्रमागतerated.item[0])
		वापस 0;

	spitz_spk_func = ucontrol->value.क्रमागतerated.item[0];
	spitz_ext_control(&card->dapm);
	वापस 1;
पूर्ण

अटल पूर्णांक spitz_mic_bias(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	gpio_set_value_cansleep(spitz_mic_gpio, SND_SOC_DAPM_EVENT_ON(event));
	वापस 0;
पूर्ण

/* spitz machine dapm widमाला_लो */
अटल स्थिर काष्ठा snd_soc_dapm_widget wm8750_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_MIC("Mic Jack", spitz_mic_bias),
	SND_SOC_DAPM_SPK("Ext Spk", शून्य),
	SND_SOC_DAPM_LINE("Line Jack", शून्य),

	/* headset is a mic and mono headphone */
	SND_SOC_DAPM_HP("Headset Jack", शून्य),
पूर्ण;

/* Spitz machine audio_map */
अटल स्थिर काष्ठा snd_soc_dapm_route spitz_audio_map[] = अणु

	/* headphone connected to LOUT1, ROUT1 */
	अणु"Headphone Jack", शून्य, "LOUT1"पूर्ण,
	अणु"Headphone Jack", शून्य, "ROUT1"पूर्ण,

	/* headset connected to ROUT1 and LINPUT1 with bias (def below) */
	अणु"Headset Jack", शून्य, "ROUT1"पूर्ण,

	/* ext speaker connected to LOUT2, ROUT2  */
	अणु"Ext Spk", शून्य, "ROUT2"पूर्ण,
	अणु"Ext Spk", शून्य, "LOUT2"पूर्ण,

	/* mic is connected to input 1 - with bias */
	अणु"LINPUT1", शून्य, "Mic Bias"पूर्ण,
	अणु"Mic Bias", शून्य, "Mic Jack"पूर्ण,

	/* line is connected to input 1 - no bias */
	अणु"LINPUT1", शून्य, "Line Jack"पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर jack_function[] = अणु"Headphone", "Mic", "Line",
	"Headset", "Off"पूर्ण;
अटल स्थिर अक्षर * स्थिर spk_function[] = अणु"On", "Off"पूर्ण;
अटल स्थिर काष्ठा soc_क्रमागत spitz_क्रमागत[] = अणु
	SOC_ENUM_SINGLE_EXT(5, jack_function),
	SOC_ENUM_SINGLE_EXT(2, spk_function),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8750_spitz_controls[] = अणु
	SOC_ENUM_EXT("Jack Function", spitz_क्रमागत[0], spitz_get_jack,
		spitz_set_jack),
	SOC_ENUM_EXT("Speaker Function", spitz_क्रमागत[1], spitz_get_spk,
		spitz_set_spk),
पूर्ण;

/* spitz digital audio पूर्णांकerface glue - connects codec <--> CPU */
SND_SOC_DAILINK_DEFS(wm8750,
	DAILINK_COMP_ARRAY(COMP_CPU("pxa2xx-i2s")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm8750.0-001b", "wm8750-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("pxa-pcm-audio")));

अटल काष्ठा snd_soc_dai_link spitz_dai = अणु
	.name = "wm8750",
	.stream_name = "WM8750",
	.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
		   SND_SOC_DAIFMT_CBS_CFS,
	.ops = &spitz_ops,
	SND_SOC_DAILINK_REG(wm8750),
पूर्ण;

/* spitz audio machine driver */
अटल काष्ठा snd_soc_card snd_soc_spitz = अणु
	.name = "Spitz",
	.owner = THIS_MODULE,
	.dai_link = &spitz_dai,
	.num_links = 1,

	.controls = wm8750_spitz_controls,
	.num_controls = ARRAY_SIZE(wm8750_spitz_controls),
	.dapm_widमाला_लो = wm8750_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(wm8750_dapm_widमाला_लो),
	.dapm_routes = spitz_audio_map,
	.num_dapm_routes = ARRAY_SIZE(spitz_audio_map),
	.fully_routed = true,
पूर्ण;

अटल पूर्णांक spitz_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = &snd_soc_spitz;
	पूर्णांक ret;

	अगर (machine_is_akita())
		spitz_mic_gpio = AKITA_GPIO_MIC_BIAS;
	अन्यथा
		spitz_mic_gpio = SPITZ_GPIO_MIC_BIAS;

	ret = gpio_request(spitz_mic_gpio, "MIC GPIO");
	अगर (ret)
		जाओ err1;

	ret = gpio_direction_output(spitz_mic_gpio, 0);
	अगर (ret)
		जाओ err2;

	card->dev = &pdev->dev;

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
	अगर (ret) अणु
		dev_err(&pdev->dev, "snd_soc_register_card() failed: %d\n",
			ret);
		जाओ err2;
	पूर्ण

	वापस 0;

err2:
	gpio_मुक्त(spitz_mic_gpio);
err1:
	वापस ret;
पूर्ण

अटल पूर्णांक spitz_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	gpio_मुक्त(spitz_mic_gpio);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver spitz_driver = अणु
	.driver		= अणु
		.name	= "spitz-audio",
		.pm     = &snd_soc_pm_ops,
	पूर्ण,
	.probe		= spitz_probe,
	.हटाओ		= spitz_हटाओ,
पूर्ण;

module_platक्रमm_driver(spitz_driver);

MODULE_AUTHOR("Richard Purdie");
MODULE_DESCRIPTION("ALSA SoC Spitz");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:spitz-audio");
