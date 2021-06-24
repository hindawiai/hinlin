<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * tosa.c  --  SoC audio क्रम Tosa
 *
 * Copyright 2005 Wolfson Microelectronics PLC.
 * Copyright 2005 Openedhand Ltd.
 *
 * Authors: Liam Girdwood <lrg@slimlogic.co.uk>
 *          Riअक्षरd Purdie <riअक्षरd@खोलोedhand.com>
 *
 * GPIO's
 *  1 - Jack Insertion
 *  5 - Hookचयन (headset answer/hang up चयन)
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/device.h>
#समावेश <linux/gpपन.स>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <mach/tosa.h>
#समावेश <mach/audपन.स>

#घोषणा TOSA_HP        0
#घोषणा TOSA_MIC_INT   1
#घोषणा TOSA_HEADSET   2
#घोषणा TOSA_HP_OFF    3
#घोषणा TOSA_SPK_ON    0
#घोषणा TOSA_SPK_OFF   1

अटल पूर्णांक tosa_jack_func;
अटल पूर्णांक tosa_spk_func;

अटल व्योम tosa_ext_control(काष्ठा snd_soc_dapm_context *dapm)
अणु

	snd_soc_dapm_mutex_lock(dapm);

	/* set up jack connection */
	चयन (tosa_jack_func) अणु
	हाल TOSA_HP:
		snd_soc_dapm_disable_pin_unlocked(dapm, "Mic (Internal)");
		snd_soc_dapm_enable_pin_unlocked(dapm, "Headphone Jack");
		snd_soc_dapm_disable_pin_unlocked(dapm, "Headset Jack");
		अवरोध;
	हाल TOSA_MIC_INT:
		snd_soc_dapm_enable_pin_unlocked(dapm, "Mic (Internal)");
		snd_soc_dapm_disable_pin_unlocked(dapm, "Headphone Jack");
		snd_soc_dapm_disable_pin_unlocked(dapm, "Headset Jack");
		अवरोध;
	हाल TOSA_HEADSET:
		snd_soc_dapm_disable_pin_unlocked(dapm, "Mic (Internal)");
		snd_soc_dapm_disable_pin_unlocked(dapm, "Headphone Jack");
		snd_soc_dapm_enable_pin_unlocked(dapm, "Headset Jack");
		अवरोध;
	पूर्ण

	अगर (tosa_spk_func == TOSA_SPK_ON)
		snd_soc_dapm_enable_pin_unlocked(dapm, "Speaker");
	अन्यथा
		snd_soc_dapm_disable_pin_unlocked(dapm, "Speaker");

	snd_soc_dapm_sync_unlocked(dapm);

	snd_soc_dapm_mutex_unlock(dapm);
पूर्ण

अटल पूर्णांक tosa_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);

	/* check the jack status at stream startup */
	tosa_ext_control(&rtd->card->dapm);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops tosa_ops = अणु
	.startup = tosa_startup,
पूर्ण;

अटल पूर्णांक tosa_get_jack(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.क्रमागतerated.item[0] = tosa_jack_func;
	वापस 0;
पूर्ण

अटल पूर्णांक tosa_set_jack(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_card *card = snd_kcontrol_chip(kcontrol);

	अगर (tosa_jack_func == ucontrol->value.क्रमागतerated.item[0])
		वापस 0;

	tosa_jack_func = ucontrol->value.क्रमागतerated.item[0];
	tosa_ext_control(&card->dapm);
	वापस 1;
पूर्ण

अटल पूर्णांक tosa_get_spk(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.क्रमागतerated.item[0] = tosa_spk_func;
	वापस 0;
पूर्ण

अटल पूर्णांक tosa_set_spk(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_card *card = snd_kcontrol_chip(kcontrol);

	अगर (tosa_spk_func == ucontrol->value.क्रमागतerated.item[0])
		वापस 0;

	tosa_spk_func = ucontrol->value.क्रमागतerated.item[0];
	tosa_ext_control(&card->dapm);
	वापस 1;
पूर्ण

/* tosa dapm event handlers */
अटल पूर्णांक tosa_hp_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	gpio_set_value(TOSA_GPIO_L_MUTE, SND_SOC_DAPM_EVENT_ON(event) ? 1 : 0);
	वापस 0;
पूर्ण

/* tosa machine dapm widमाला_लो */
अटल स्थिर काष्ठा snd_soc_dapm_widget tosa_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_HP("Headphone Jack", tosa_hp_event),
SND_SOC_DAPM_HP("Headset Jack", शून्य),
SND_SOC_DAPM_MIC("Mic (Internal)", शून्य),
SND_SOC_DAPM_SPK("Speaker", शून्य),
पूर्ण;

/* tosa audio map */
अटल स्थिर काष्ठा snd_soc_dapm_route audio_map[] = अणु

	/* headphone connected to HPOUTL, HPOUTR */
	अणु"Headphone Jack", शून्य, "HPOUTL"पूर्ण,
	अणु"Headphone Jack", शून्य, "HPOUTR"पूर्ण,

	/* ext speaker connected to LOUT2, ROUT2 */
	अणु"Speaker", शून्य, "LOUT2"पूर्ण,
	अणु"Speaker", शून्य, "ROUT2"पूर्ण,

	/* पूर्णांकernal mic is connected to mic1, mic2 dअगरferential - with bias */
	अणु"MIC1", शून्य, "Mic Bias"पूर्ण,
	अणु"MIC2", शून्य, "Mic Bias"पूर्ण,
	अणु"Mic Bias", शून्य, "Mic (Internal)"पूर्ण,

	/* headset is connected to HPOUTR, and LINEINR with bias */
	अणु"Headset Jack", शून्य, "HPOUTR"पूर्ण,
	अणु"LINEINR", शून्य, "Mic Bias"पूर्ण,
	अणु"Mic Bias", शून्य, "Headset Jack"पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर jack_function[] = अणु"Headphone", "Mic", "Line",
	"Headset", "Off"पूर्ण;
अटल स्थिर अक्षर * स्थिर spk_function[] = अणु"On", "Off"पूर्ण;
अटल स्थिर काष्ठा soc_क्रमागत tosa_क्रमागत[] = अणु
	SOC_ENUM_SINGLE_EXT(5, jack_function),
	SOC_ENUM_SINGLE_EXT(2, spk_function),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new tosa_controls[] = अणु
	SOC_ENUM_EXT("Jack Function", tosa_क्रमागत[0], tosa_get_jack,
		tosa_set_jack),
	SOC_ENUM_EXT("Speaker Function", tosa_क्रमागत[1], tosa_get_spk,
		tosa_set_spk),
पूर्ण;

SND_SOC_DAILINK_DEFS(ac97,
	DAILINK_COMP_ARRAY(COMP_CPU("pxa2xx-ac97")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm9712-codec", "wm9712-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("pxa-pcm-audio")));

SND_SOC_DAILINK_DEFS(ac97_aux,
	DAILINK_COMP_ARRAY(COMP_CPU("pxa2xx-ac97-aux")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm9712-codec", "wm9712-aux")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("pxa-pcm-audio")));

अटल काष्ठा snd_soc_dai_link tosa_dai[] = अणु
अणु
	.name = "AC97",
	.stream_name = "AC97 HiFi",
	.ops = &tosa_ops,
	SND_SOC_DAILINK_REG(ac97),
पूर्ण,
अणु
	.name = "AC97 Aux",
	.stream_name = "AC97 Aux",
	.ops = &tosa_ops,
	SND_SOC_DAILINK_REG(ac97_aux),
पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_card tosa = अणु
	.name = "Tosa",
	.owner = THIS_MODULE,
	.dai_link = tosa_dai,
	.num_links = ARRAY_SIZE(tosa_dai),

	.controls = tosa_controls,
	.num_controls = ARRAY_SIZE(tosa_controls),
	.dapm_widमाला_लो = tosa_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(tosa_dapm_widमाला_लो),
	.dapm_routes = audio_map,
	.num_dapm_routes = ARRAY_SIZE(audio_map),
	.fully_routed = true,
पूर्ण;

अटल पूर्णांक tosa_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = &tosa;
	पूर्णांक ret;

	ret = gpio_request_one(TOSA_GPIO_L_MUTE, GPIOF_OUT_INIT_LOW,
			       "Headphone Jack");
	अगर (ret)
		वापस ret;

	card->dev = &pdev->dev;

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
	अगर (ret) अणु
		dev_err(&pdev->dev, "snd_soc_register_card() failed: %d\n",
			ret);
		gpio_मुक्त(TOSA_GPIO_L_MUTE);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक tosa_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	gpio_मुक्त(TOSA_GPIO_L_MUTE);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver tosa_driver = अणु
	.driver		= अणु
		.name	= "tosa-audio",
		.pm     = &snd_soc_pm_ops,
	पूर्ण,
	.probe		= tosa_probe,
	.हटाओ		= tosa_हटाओ,
पूर्ण;

module_platक्रमm_driver(tosa_driver);

/* Module inक्रमmation */
MODULE_AUTHOR("Richard Purdie");
MODULE_DESCRIPTION("ALSA SoC Tosa");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:tosa-audio");
