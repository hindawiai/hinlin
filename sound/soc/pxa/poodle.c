<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * poodle.c  --  SoC audio क्रम Poodle
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
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/hardware/locomo.h>
#समावेश <mach/poodle.h>
#समावेश <mach/audपन.स>

#समावेश "../codecs/wm8731.h"
#समावेश "pxa2xx-i2s.h"

#घोषणा POODLE_HP        1
#घोषणा POODLE_HP_OFF    0
#घोषणा POODLE_SPK_ON    1
#घोषणा POODLE_SPK_OFF   0

 /* audio घड़ी in Hz - rounded from 12.235MHz */
#घोषणा POODLE_AUDIO_CLOCK 12288000

अटल पूर्णांक poodle_jack_func;
अटल पूर्णांक poodle_spk_func;

अटल व्योम poodle_ext_control(काष्ठा snd_soc_dapm_context *dapm)
अणु
	/* set up jack connection */
	अगर (poodle_jack_func == POODLE_HP) अणु
		/* set = unmute headphone */
		locomo_gpio_ग_लिखो(&poodle_locomo_device.dev,
			POODLE_LOCOMO_GPIO_MUTE_L, 1);
		locomo_gpio_ग_लिखो(&poodle_locomo_device.dev,
			POODLE_LOCOMO_GPIO_MUTE_R, 1);
		snd_soc_dapm_enable_pin(dapm, "Headphone Jack");
	पूर्ण अन्यथा अणु
		locomo_gpio_ग_लिखो(&poodle_locomo_device.dev,
			POODLE_LOCOMO_GPIO_MUTE_L, 0);
		locomo_gpio_ग_लिखो(&poodle_locomo_device.dev,
			POODLE_LOCOMO_GPIO_MUTE_R, 0);
		snd_soc_dapm_disable_pin(dapm, "Headphone Jack");
	पूर्ण

	/* set the endpoपूर्णांकs to their new connection states */
	अगर (poodle_spk_func == POODLE_SPK_ON)
		snd_soc_dapm_enable_pin(dapm, "Ext Spk");
	अन्यथा
		snd_soc_dapm_disable_pin(dapm, "Ext Spk");

	/* संकेत a DAPM event */
	snd_soc_dapm_sync(dapm);
पूर्ण

अटल पूर्णांक poodle_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);

	/* check the jack status at stream startup */
	poodle_ext_control(&rtd->card->dapm);

	वापस 0;
पूर्ण

/* we need to unmute the HP at shutकरोwn as the mute burns घातer on poodle */
अटल व्योम poodle_shutकरोwn(काष्ठा snd_pcm_substream *substream)
अणु
	/* set = unmute headphone */
	locomo_gpio_ग_लिखो(&poodle_locomo_device.dev,
		POODLE_LOCOMO_GPIO_MUTE_L, 1);
	locomo_gpio_ग_लिखो(&poodle_locomo_device.dev,
		POODLE_LOCOMO_GPIO_MUTE_R, 1);
पूर्ण

अटल पूर्णांक poodle_hw_params(काष्ठा snd_pcm_substream *substream,
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

अटल स्थिर काष्ठा snd_soc_ops poodle_ops = अणु
	.startup = poodle_startup,
	.hw_params = poodle_hw_params,
	.shutकरोwn = poodle_shutकरोwn,
पूर्ण;

अटल पूर्णांक poodle_get_jack(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.क्रमागतerated.item[0] = poodle_jack_func;
	वापस 0;
पूर्ण

अटल पूर्णांक poodle_set_jack(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_card *card =  snd_kcontrol_chip(kcontrol);

	अगर (poodle_jack_func == ucontrol->value.क्रमागतerated.item[0])
		वापस 0;

	poodle_jack_func = ucontrol->value.क्रमागतerated.item[0];
	poodle_ext_control(&card->dapm);
	वापस 1;
पूर्ण

अटल पूर्णांक poodle_get_spk(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.क्रमागतerated.item[0] = poodle_spk_func;
	वापस 0;
पूर्ण

अटल पूर्णांक poodle_set_spk(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_card *card =  snd_kcontrol_chip(kcontrol);

	अगर (poodle_spk_func == ucontrol->value.क्रमागतerated.item[0])
		वापस 0;

	poodle_spk_func = ucontrol->value.क्रमागतerated.item[0];
	poodle_ext_control(&card->dapm);
	वापस 1;
पूर्ण

अटल पूर्णांक poodle_amp_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	अगर (SND_SOC_DAPM_EVENT_ON(event))
		locomo_gpio_ग_लिखो(&poodle_locomo_device.dev,
			POODLE_LOCOMO_GPIO_AMP_ON, 0);
	अन्यथा
		locomo_gpio_ग_लिखो(&poodle_locomo_device.dev,
			POODLE_LOCOMO_GPIO_AMP_ON, 1);

	वापस 0;
पूर्ण

/* poodle machine dapm widमाला_लो */
अटल स्थिर काष्ठा snd_soc_dapm_widget wm8731_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_HP("Headphone Jack", शून्य),
SND_SOC_DAPM_SPK("Ext Spk", poodle_amp_event),
SND_SOC_DAPM_MIC("Microphone", शून्य),
पूर्ण;

/* Corgi machine connections to the codec pins */
अटल स्थिर काष्ठा snd_soc_dapm_route poodle_audio_map[] = अणु

	/* headphone connected to LHPOUT1, RHPOUT1 */
	अणु"Headphone Jack", शून्य, "LHPOUT"पूर्ण,
	अणु"Headphone Jack", शून्य, "RHPOUT"पूर्ण,

	/* speaker connected to LOUT, ROUT */
	अणु"Ext Spk", शून्य, "ROUT"पूर्ण,
	अणु"Ext Spk", शून्य, "LOUT"पूर्ण,

	अणु"MICIN", शून्य, "Microphone"पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर jack_function[] = अणु"Off", "Headphone"पूर्ण;
अटल स्थिर अक्षर * स्थिर spk_function[] = अणु"Off", "On"पूर्ण;
अटल स्थिर काष्ठा soc_क्रमागत poodle_क्रमागत[] = अणु
	SOC_ENUM_SINGLE_EXT(2, jack_function),
	SOC_ENUM_SINGLE_EXT(2, spk_function),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8731_poodle_controls[] = अणु
	SOC_ENUM_EXT("Jack Function", poodle_क्रमागत[0], poodle_get_jack,
		poodle_set_jack),
	SOC_ENUM_EXT("Speaker Function", poodle_क्रमागत[1], poodle_get_spk,
		poodle_set_spk),
पूर्ण;

/* poodle digital audio पूर्णांकerface glue - connects codec <--> CPU */
SND_SOC_DAILINK_DEFS(wm8731,
	DAILINK_COMP_ARRAY(COMP_CPU("pxa2xx-i2s")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm8731.0-001b", "wm8731-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("pxa-pcm-audio")));

अटल काष्ठा snd_soc_dai_link poodle_dai = अणु
	.name = "WM8731",
	.stream_name = "WM8731",
	.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
		   SND_SOC_DAIFMT_CBS_CFS,
	.ops = &poodle_ops,
	SND_SOC_DAILINK_REG(wm8731),
पूर्ण;

/* poodle audio machine driver */
अटल काष्ठा snd_soc_card poodle = अणु
	.name = "Poodle",
	.dai_link = &poodle_dai,
	.num_links = 1,
	.owner = THIS_MODULE,

	.controls = wm8731_poodle_controls,
	.num_controls = ARRAY_SIZE(wm8731_poodle_controls),
	.dapm_widमाला_लो = wm8731_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(wm8731_dapm_widमाला_लो),
	.dapm_routes = poodle_audio_map,
	.num_dapm_routes = ARRAY_SIZE(poodle_audio_map),
	.fully_routed = true,
पूर्ण;

अटल पूर्णांक poodle_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = &poodle;
	पूर्णांक ret;

	locomo_gpio_set_dir(&poodle_locomo_device.dev,
		POODLE_LOCOMO_GPIO_AMP_ON, 0);
	/* should we mute HP at startup - burning घातer ?*/
	locomo_gpio_set_dir(&poodle_locomo_device.dev,
		POODLE_LOCOMO_GPIO_MUTE_L, 0);
	locomo_gpio_set_dir(&poodle_locomo_device.dev,
		POODLE_LOCOMO_GPIO_MUTE_R, 0);

	card->dev = &pdev->dev;

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
	अगर (ret)
		dev_err(&pdev->dev, "snd_soc_register_card() failed: %d\n",
			ret);
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver poodle_driver = अणु
	.driver		= अणु
		.name	= "poodle-audio",
		.pm     = &snd_soc_pm_ops,
	पूर्ण,
	.probe		= poodle_probe,
पूर्ण;

module_platक्रमm_driver(poodle_driver);

/* Module inक्रमmation */
MODULE_AUTHOR("Richard Purdie");
MODULE_DESCRIPTION("ALSA SoC Poodle");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:poodle-audio");
