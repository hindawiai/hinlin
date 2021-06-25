<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * corgi.c  --  SoC audio क्रम Corgi
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
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpपन.स>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <mach/corgi.h>
#समावेश <mach/audपन.स>

#समावेश "../codecs/wm8731.h"
#समावेश "pxa2xx-i2s.h"

#घोषणा CORGI_HP        0
#घोषणा CORGI_MIC       1
#घोषणा CORGI_LINE      2
#घोषणा CORGI_HEADSET   3
#घोषणा CORGI_HP_OFF    4
#घोषणा CORGI_SPK_ON    0
#घोषणा CORGI_SPK_OFF   1

 /* audio घड़ी in Hz - rounded from 12.235MHz */
#घोषणा CORGI_AUDIO_CLOCK 12288000

अटल पूर्णांक corgi_jack_func;
अटल पूर्णांक corgi_spk_func;

अटल व्योम corgi_ext_control(काष्ठा snd_soc_dapm_context *dapm)
अणु
	snd_soc_dapm_mutex_lock(dapm);

	/* set up jack connection */
	चयन (corgi_jack_func) अणु
	हाल CORGI_HP:
		/* set = unmute headphone */
		gpio_set_value(CORGI_GPIO_MUTE_L, 1);
		gpio_set_value(CORGI_GPIO_MUTE_R, 1);
		snd_soc_dapm_disable_pin_unlocked(dapm, "Mic Jack");
		snd_soc_dapm_disable_pin_unlocked(dapm, "Line Jack");
		snd_soc_dapm_enable_pin_unlocked(dapm, "Headphone Jack");
		snd_soc_dapm_disable_pin_unlocked(dapm, "Headset Jack");
		अवरोध;
	हाल CORGI_MIC:
		/* reset = mute headphone */
		gpio_set_value(CORGI_GPIO_MUTE_L, 0);
		gpio_set_value(CORGI_GPIO_MUTE_R, 0);
		snd_soc_dapm_enable_pin_unlocked(dapm, "Mic Jack");
		snd_soc_dapm_disable_pin_unlocked(dapm, "Line Jack");
		snd_soc_dapm_disable_pin_unlocked(dapm, "Headphone Jack");
		snd_soc_dapm_disable_pin_unlocked(dapm, "Headset Jack");
		अवरोध;
	हाल CORGI_LINE:
		gpio_set_value(CORGI_GPIO_MUTE_L, 0);
		gpio_set_value(CORGI_GPIO_MUTE_R, 0);
		snd_soc_dapm_disable_pin_unlocked(dapm, "Mic Jack");
		snd_soc_dapm_enable_pin_unlocked(dapm, "Line Jack");
		snd_soc_dapm_disable_pin_unlocked(dapm, "Headphone Jack");
		snd_soc_dapm_disable_pin_unlocked(dapm, "Headset Jack");
		अवरोध;
	हाल CORGI_HEADSET:
		gpio_set_value(CORGI_GPIO_MUTE_L, 0);
		gpio_set_value(CORGI_GPIO_MUTE_R, 1);
		snd_soc_dapm_enable_pin_unlocked(dapm, "Mic Jack");
		snd_soc_dapm_disable_pin_unlocked(dapm, "Line Jack");
		snd_soc_dapm_disable_pin_unlocked(dapm, "Headphone Jack");
		snd_soc_dapm_enable_pin_unlocked(dapm, "Headset Jack");
		अवरोध;
	पूर्ण

	अगर (corgi_spk_func == CORGI_SPK_ON)
		snd_soc_dapm_enable_pin_unlocked(dapm, "Ext Spk");
	अन्यथा
		snd_soc_dapm_disable_pin_unlocked(dapm, "Ext Spk");

	/* संकेत a DAPM event */
	snd_soc_dapm_sync_unlocked(dapm);

	snd_soc_dapm_mutex_unlock(dapm);
पूर्ण

अटल पूर्णांक corgi_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);

	/* check the jack status at stream startup */
	corgi_ext_control(&rtd->card->dapm);

	वापस 0;
पूर्ण

/* we need to unmute the HP at shutकरोwn as the mute burns घातer on corgi */
अटल व्योम corgi_shutकरोwn(काष्ठा snd_pcm_substream *substream)
अणु
	/* set = unmute headphone */
	gpio_set_value(CORGI_GPIO_MUTE_L, 1);
	gpio_set_value(CORGI_GPIO_MUTE_R, 1);
पूर्ण

अटल पूर्णांक corgi_hw_params(काष्ठा snd_pcm_substream *substream,
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
	ret = snd_soc_dai_set_sysclk(codec_dai, WM8731_SYSCLK_XTAL, clk,
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

अटल स्थिर काष्ठा snd_soc_ops corgi_ops = अणु
	.startup = corgi_startup,
	.hw_params = corgi_hw_params,
	.shutकरोwn = corgi_shutकरोwn,
पूर्ण;

अटल पूर्णांक corgi_get_jack(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.क्रमागतerated.item[0] = corgi_jack_func;
	वापस 0;
पूर्ण

अटल पूर्णांक corgi_set_jack(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_card *card = snd_kcontrol_chip(kcontrol);

	अगर (corgi_jack_func == ucontrol->value.क्रमागतerated.item[0])
		वापस 0;

	corgi_jack_func = ucontrol->value.क्रमागतerated.item[0];
	corgi_ext_control(&card->dapm);
	वापस 1;
पूर्ण

अटल पूर्णांक corgi_get_spk(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.क्रमागतerated.item[0] = corgi_spk_func;
	वापस 0;
पूर्ण

अटल पूर्णांक corgi_set_spk(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_card *card =  snd_kcontrol_chip(kcontrol);

	अगर (corgi_spk_func == ucontrol->value.क्रमागतerated.item[0])
		वापस 0;

	corgi_spk_func = ucontrol->value.क्रमागतerated.item[0];
	corgi_ext_control(&card->dapm);
	वापस 1;
पूर्ण

अटल पूर्णांक corgi_amp_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	gpio_set_value(CORGI_GPIO_APM_ON, SND_SOC_DAPM_EVENT_ON(event));
	वापस 0;
पूर्ण

अटल पूर्णांक corgi_mic_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	gpio_set_value(CORGI_GPIO_MIC_BIAS, SND_SOC_DAPM_EVENT_ON(event));
	वापस 0;
पूर्ण

/* corgi machine dapm widमाला_लो */
अटल स्थिर काष्ठा snd_soc_dapm_widget wm8731_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_HP("Headphone Jack", शून्य),
SND_SOC_DAPM_MIC("Mic Jack", corgi_mic_event),
SND_SOC_DAPM_SPK("Ext Spk", corgi_amp_event),
SND_SOC_DAPM_LINE("Line Jack", शून्य),
SND_SOC_DAPM_HP("Headset Jack", शून्य),
पूर्ण;

/* Corgi machine audio map (connections to the codec pins) */
अटल स्थिर काष्ठा snd_soc_dapm_route corgi_audio_map[] = अणु

	/* headset Jack  - in = micin, out = LHPOUT*/
	अणु"Headset Jack", शून्य, "LHPOUT"पूर्ण,

	/* headphone connected to LHPOUT1, RHPOUT1 */
	अणु"Headphone Jack", शून्य, "LHPOUT"पूर्ण,
	अणु"Headphone Jack", शून्य, "RHPOUT"पूर्ण,

	/* speaker connected to LOUT, ROUT */
	अणु"Ext Spk", शून्य, "ROUT"पूर्ण,
	अणु"Ext Spk", शून्य, "LOUT"पूर्ण,

	/* mic is connected to MICIN (via right channel of headphone jack) */
	अणु"MICIN", शून्य, "Mic Jack"पूर्ण,

	/* Same as the above but no mic bias क्रम line संकेतs */
	अणु"MICIN", शून्य, "Line Jack"पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर jack_function[] = अणु"Headphone", "Mic", "Line",
	"Headset", "Off"पूर्ण;
अटल स्थिर अक्षर * स्थिर spk_function[] = अणु"On", "Off"पूर्ण;
अटल स्थिर काष्ठा soc_क्रमागत corgi_क्रमागत[] = अणु
	SOC_ENUM_SINGLE_EXT(5, jack_function),
	SOC_ENUM_SINGLE_EXT(2, spk_function),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8731_corgi_controls[] = अणु
	SOC_ENUM_EXT("Jack Function", corgi_क्रमागत[0], corgi_get_jack,
		corgi_set_jack),
	SOC_ENUM_EXT("Speaker Function", corgi_क्रमागत[1], corgi_get_spk,
		corgi_set_spk),
पूर्ण;

/* corgi digital audio पूर्णांकerface glue - connects codec <--> CPU */
SND_SOC_DAILINK_DEFS(wm8731,
	DAILINK_COMP_ARRAY(COMP_CPU("pxa2xx-i2s")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm8731.0-001b", "wm8731-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("pxa-pcm-audio")));

अटल काष्ठा snd_soc_dai_link corgi_dai = अणु
	.name = "WM8731",
	.stream_name = "WM8731",
	.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
		   SND_SOC_DAIFMT_CBS_CFS,
	.ops = &corgi_ops,
	SND_SOC_DAILINK_REG(wm8731),
पूर्ण;

/* corgi audio machine driver */
अटल काष्ठा snd_soc_card corgi = अणु
	.name = "Corgi",
	.owner = THIS_MODULE,
	.dai_link = &corgi_dai,
	.num_links = 1,

	.controls = wm8731_corgi_controls,
	.num_controls = ARRAY_SIZE(wm8731_corgi_controls),
	.dapm_widमाला_लो = wm8731_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(wm8731_dapm_widमाला_लो),
	.dapm_routes = corgi_audio_map,
	.num_dapm_routes = ARRAY_SIZE(corgi_audio_map),
	.fully_routed = true,
पूर्ण;

अटल पूर्णांक corgi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = &corgi;
	पूर्णांक ret;

	card->dev = &pdev->dev;

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
	अगर (ret)
		dev_err(&pdev->dev, "snd_soc_register_card() failed: %d\n",
			ret);
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver corgi_driver = अणु
	.driver		= अणु
		.name	= "corgi-audio",
		.pm     = &snd_soc_pm_ops,
	पूर्ण,
	.probe		= corgi_probe,
पूर्ण;

module_platक्रमm_driver(corgi_driver);

/* Module inक्रमmation */
MODULE_AUTHOR("Richard Purdie");
MODULE_DESCRIPTION("ALSA SoC Corgi");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:corgi-audio");
