<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * n810.c  --  SoC audio क्रम Nokia N810
 *
 * Copyright (C) 2008 Nokia Corporation
 *
 * Contact: Jarkko Nikula <jarkko.nikula@biपंचांगer.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/asoc-ti-mcbsp.h>

#समावेश "omap-mcbsp.h"

#घोषणा N810_HEADSET_AMP_GPIO	10
#घोषणा N810_SPEAKER_AMP_GPIO	101

क्रमागत अणु
	N810_JACK_DISABLED,
	N810_JACK_HP,
	N810_JACK_HS,
	N810_JACK_MIC,
पूर्ण;

अटल काष्ठा clk *sys_clkout2;
अटल काष्ठा clk *sys_clkout2_src;
अटल काष्ठा clk *func96m_clk;

अटल पूर्णांक n810_spk_func;
अटल पूर्णांक n810_jack_func;
अटल पूर्णांक n810_dmic_func;

अटल व्योम n810_ext_control(काष्ठा snd_soc_dapm_context *dapm)
अणु
	पूर्णांक hp = 0, line1l = 0;

	चयन (n810_jack_func) अणु
	हाल N810_JACK_HS:
		line1l = 1;
		fallthrough;
	हाल N810_JACK_HP:
		hp = 1;
		अवरोध;
	हाल N810_JACK_MIC:
		line1l = 1;
		अवरोध;
	पूर्ण

	snd_soc_dapm_mutex_lock(dapm);

	अगर (n810_spk_func)
		snd_soc_dapm_enable_pin_unlocked(dapm, "Ext Spk");
	अन्यथा
		snd_soc_dapm_disable_pin_unlocked(dapm, "Ext Spk");

	अगर (hp)
		snd_soc_dapm_enable_pin_unlocked(dapm, "Headphone Jack");
	अन्यथा
		snd_soc_dapm_disable_pin_unlocked(dapm, "Headphone Jack");
	अगर (line1l)
		snd_soc_dapm_enable_pin_unlocked(dapm, "HS Mic");
	अन्यथा
		snd_soc_dapm_disable_pin_unlocked(dapm, "HS Mic");

	अगर (n810_dmic_func)
		snd_soc_dapm_enable_pin_unlocked(dapm, "DMic");
	अन्यथा
		snd_soc_dapm_disable_pin_unlocked(dapm, "DMic");

	snd_soc_dapm_sync_unlocked(dapm);

	snd_soc_dapm_mutex_unlock(dapm);
पूर्ण

अटल पूर्णांक n810_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);

	snd_pcm_hw_स्थिरraपूर्णांक_single(runसमय, SNDRV_PCM_HW_PARAM_CHANNELS, 2);

	n810_ext_control(&rtd->card->dapm);
	वापस clk_prepare_enable(sys_clkout2);
पूर्ण

अटल व्योम n810_shutकरोwn(काष्ठा snd_pcm_substream *substream)
अणु
	clk_disable_unprepare(sys_clkout2);
पूर्ण

अटल पूर्णांक n810_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	पूर्णांक err;

	/* Set the codec प्रणाली घड़ी क्रम DAC and ADC */
	err = snd_soc_dai_set_sysclk(codec_dai, 0, 12000000,
					    SND_SOC_CLOCK_IN);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops n810_ops = अणु
	.startup = n810_startup,
	.hw_params = n810_hw_params,
	.shutकरोwn = n810_shutकरोwn,
पूर्ण;

अटल पूर्णांक n810_get_spk(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.क्रमागतerated.item[0] = n810_spk_func;

	वापस 0;
पूर्ण

अटल पूर्णांक n810_set_spk(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_card *card =  snd_kcontrol_chip(kcontrol);

	अगर (n810_spk_func == ucontrol->value.क्रमागतerated.item[0])
		वापस 0;

	n810_spk_func = ucontrol->value.क्रमागतerated.item[0];
	n810_ext_control(&card->dapm);

	वापस 1;
पूर्ण

अटल पूर्णांक n810_get_jack(काष्ठा snd_kcontrol *kcontrol,
			 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.क्रमागतerated.item[0] = n810_jack_func;

	वापस 0;
पूर्ण

अटल पूर्णांक n810_set_jack(काष्ठा snd_kcontrol *kcontrol,
			 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_card *card =  snd_kcontrol_chip(kcontrol);

	अगर (n810_jack_func == ucontrol->value.क्रमागतerated.item[0])
		वापस 0;

	n810_jack_func = ucontrol->value.क्रमागतerated.item[0];
	n810_ext_control(&card->dapm);

	वापस 1;
पूर्ण

अटल पूर्णांक n810_get_input(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.क्रमागतerated.item[0] = n810_dmic_func;

	वापस 0;
पूर्ण

अटल पूर्णांक n810_set_input(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_card *card =  snd_kcontrol_chip(kcontrol);

	अगर (n810_dmic_func == ucontrol->value.क्रमागतerated.item[0])
		वापस 0;

	n810_dmic_func = ucontrol->value.क्रमागतerated.item[0];
	n810_ext_control(&card->dapm);

	वापस 1;
पूर्ण

अटल पूर्णांक n810_spk_event(काष्ठा snd_soc_dapm_widget *w,
			  काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	अगर (SND_SOC_DAPM_EVENT_ON(event))
		gpio_set_value(N810_SPEAKER_AMP_GPIO, 1);
	अन्यथा
		gpio_set_value(N810_SPEAKER_AMP_GPIO, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक n810_jack_event(काष्ठा snd_soc_dapm_widget *w,
			   काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	अगर (SND_SOC_DAPM_EVENT_ON(event))
		gpio_set_value(N810_HEADSET_AMP_GPIO, 1);
	अन्यथा
		gpio_set_value(N810_HEADSET_AMP_GPIO, 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget aic33_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_SPK("Ext Spk", n810_spk_event),
	SND_SOC_DAPM_HP("Headphone Jack", n810_jack_event),
	SND_SOC_DAPM_MIC("DMic", शून्य),
	SND_SOC_DAPM_MIC("HS Mic", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route audio_map[] = अणु
	अणु"Headphone Jack", शून्य, "HPLOUT"पूर्ण,
	अणु"Headphone Jack", शून्य, "HPROUT"पूर्ण,

	अणु"Ext Spk", शून्य, "LLOUT"पूर्ण,
	अणु"Ext Spk", शून्य, "RLOUT"पूर्ण,

	अणु"DMic Rate 64", शून्य, "DMic"पूर्ण,
	अणु"DMic", शून्य, "Mic Bias"पूर्ण,

	/*
	 * Note that the mic bias is coming from Retu/Vilma and we करोn't have
	 * control over it aपंचांग. The analog HS mic is not working. <- TODO
	 */
	अणु"LINE1L", शून्य, "HS Mic"पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *spk_function[] = अणु"Off", "On"पूर्ण;
अटल स्थिर अक्षर *jack_function[] = अणु"Off", "Headphone", "Headset", "Mic"पूर्ण;
अटल स्थिर अक्षर *input_function[] = अणु"ADC", "Digital Mic"पूर्ण;
अटल स्थिर काष्ठा soc_क्रमागत n810_क्रमागत[] = अणु
	SOC_ENUM_SINGLE_EXT(ARRAY_SIZE(spk_function), spk_function),
	SOC_ENUM_SINGLE_EXT(ARRAY_SIZE(jack_function), jack_function),
	SOC_ENUM_SINGLE_EXT(ARRAY_SIZE(input_function), input_function),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new aic33_n810_controls[] = अणु
	SOC_ENUM_EXT("Speaker Function", n810_क्रमागत[0],
		     n810_get_spk, n810_set_spk),
	SOC_ENUM_EXT("Jack Function", n810_क्रमागत[1],
		     n810_get_jack, n810_set_jack),
	SOC_ENUM_EXT("Input Select",  n810_क्रमागत[2],
		     n810_get_input, n810_set_input),
पूर्ण;

/* Digital audio पूर्णांकerface glue - connects codec <--> CPU */
SND_SOC_DAILINK_DEFS(aic33,
	DAILINK_COMP_ARRAY(COMP_CPU("48076000.mcbsp")),
	DAILINK_COMP_ARRAY(COMP_CODEC("tlv320aic3x-codec.1-0018",
				      "tlv320aic3x-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("48076000.mcbsp")));

अटल काष्ठा snd_soc_dai_link n810_dai = अणु
	.name = "TLV320AIC33",
	.stream_name = "AIC33",
	.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
		   SND_SOC_DAIFMT_CBM_CFM,
	.ops = &n810_ops,
	SND_SOC_DAILINK_REG(aic33),
पूर्ण;

/* Audio machine driver */
अटल काष्ठा snd_soc_card snd_soc_n810 = अणु
	.name = "N810",
	.owner = THIS_MODULE,
	.dai_link = &n810_dai,
	.num_links = 1,

	.controls = aic33_n810_controls,
	.num_controls = ARRAY_SIZE(aic33_n810_controls),
	.dapm_widमाला_लो = aic33_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(aic33_dapm_widमाला_लो),
	.dapm_routes = audio_map,
	.num_dapm_routes = ARRAY_SIZE(audio_map),
	.fully_routed = true,
पूर्ण;

अटल काष्ठा platक्रमm_device *n810_snd_device;

अटल पूर्णांक __init n810_soc_init(व्योम)
अणु
	पूर्णांक err;
	काष्ठा device *dev;

	अगर (!of_have_populated_dt() ||
	    (!of_machine_is_compatible("nokia,n810") &&
	     !of_machine_is_compatible("nokia,n810-wimax")))
		वापस -ENODEV;

	n810_snd_device = platक्रमm_device_alloc("soc-audio", -1);
	अगर (!n810_snd_device)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(n810_snd_device, &snd_soc_n810);
	err = platक्रमm_device_add(n810_snd_device);
	अगर (err)
		जाओ err1;

	dev = &n810_snd_device->dev;

	sys_clkout2_src = clk_get(dev, "sys_clkout2_src");
	अगर (IS_ERR(sys_clkout2_src)) अणु
		dev_err(dev, "Could not get sys_clkout2_src clock\n");
		err = PTR_ERR(sys_clkout2_src);
		जाओ err2;
	पूर्ण
	sys_clkout2 = clk_get(dev, "sys_clkout2");
	अगर (IS_ERR(sys_clkout2)) अणु
		dev_err(dev, "Could not get sys_clkout2\n");
		err = PTR_ERR(sys_clkout2);
		जाओ err3;
	पूर्ण
	/*
	 * Configure 12 MHz output on SYS_CLKOUT2. Thereक्रमe we must use
	 * 96 MHz as its parent in order to get 12 MHz
	 */
	func96m_clk = clk_get(dev, "func_96m_ck");
	अगर (IS_ERR(func96m_clk)) अणु
		dev_err(dev, "Could not get func 96M clock\n");
		err = PTR_ERR(func96m_clk);
		जाओ err4;
	पूर्ण
	clk_set_parent(sys_clkout2_src, func96m_clk);
	clk_set_rate(sys_clkout2, 12000000);

	अगर (WARN_ON((gpio_request(N810_HEADSET_AMP_GPIO, "hs_amp") < 0) ||
		    (gpio_request(N810_SPEAKER_AMP_GPIO, "spk_amp") < 0))) अणु
		err = -EINVAL;
		जाओ err4;
	पूर्ण

	gpio_direction_output(N810_HEADSET_AMP_GPIO, 0);
	gpio_direction_output(N810_SPEAKER_AMP_GPIO, 0);

	वापस 0;
err4:
	clk_put(sys_clkout2);
err3:
	clk_put(sys_clkout2_src);
err2:
	platक्रमm_device_del(n810_snd_device);
err1:
	platक्रमm_device_put(n810_snd_device);

	वापस err;
पूर्ण

अटल व्योम __निकास n810_soc_निकास(व्योम)
अणु
	gpio_मुक्त(N810_SPEAKER_AMP_GPIO);
	gpio_मुक्त(N810_HEADSET_AMP_GPIO);
	clk_put(sys_clkout2_src);
	clk_put(sys_clkout2);
	clk_put(func96m_clk);

	platक्रमm_device_unरेजिस्टर(n810_snd_device);
पूर्ण

module_init(n810_soc_init);
module_निकास(n810_soc_निकास);

MODULE_AUTHOR("Jarkko Nikula <jarkko.nikula@bitmer.com>");
MODULE_DESCRIPTION("ALSA SoC Nokia N810");
MODULE_LICENSE("GPL");
