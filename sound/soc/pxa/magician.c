<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SoC audio क्रम HTC Magician
 *
 * Copyright (c) 2006 Philipp Zabel <philipp.zabel@gmail.com>
 *
 * based on spitz.c,
 * Authors: Liam Girdwood <lrg@slimlogic.co.uk>
 *          Riअक्षरd Purdie <riअक्षरd@खोलोedhand.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/समयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/i2c.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/uda1380.h>

#समावेश <mach/magician.h>
#समावेश <यंत्र/mach-types.h>
#समावेश "../codecs/uda1380.h"
#समावेश "pxa2xx-i2s.h"
#समावेश "pxa-ssp.h"

#घोषणा MAGICIAN_MIC       0
#घोषणा MAGICIAN_MIC_EXT   1

अटल पूर्णांक magician_hp_चयन;
अटल पूर्णांक magician_spk_चयन = 1;
अटल पूर्णांक magician_in_sel = MAGICIAN_MIC;

अटल व्योम magician_ext_control(काष्ठा snd_soc_dapm_context *dapm)
अणु

	snd_soc_dapm_mutex_lock(dapm);

	अगर (magician_spk_चयन)
		snd_soc_dapm_enable_pin_unlocked(dapm, "Speaker");
	अन्यथा
		snd_soc_dapm_disable_pin_unlocked(dapm, "Speaker");
	अगर (magician_hp_चयन)
		snd_soc_dapm_enable_pin_unlocked(dapm, "Headphone Jack");
	अन्यथा
		snd_soc_dapm_disable_pin_unlocked(dapm, "Headphone Jack");

	चयन (magician_in_sel) अणु
	हाल MAGICIAN_MIC:
		snd_soc_dapm_disable_pin_unlocked(dapm, "Headset Mic");
		snd_soc_dapm_enable_pin_unlocked(dapm, "Call Mic");
		अवरोध;
	हाल MAGICIAN_MIC_EXT:
		snd_soc_dapm_disable_pin_unlocked(dapm, "Call Mic");
		snd_soc_dapm_enable_pin_unlocked(dapm, "Headset Mic");
		अवरोध;
	पूर्ण

	snd_soc_dapm_sync_unlocked(dapm);

	snd_soc_dapm_mutex_unlock(dapm);
पूर्ण

अटल पूर्णांक magician_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);

	/* check the jack status at stream startup */
	magician_ext_control(&rtd->card->dapm);

	वापस 0;
पूर्ण

/*
 * Magician uses SSP port क्रम playback.
 */
अटल पूर्णांक magician_playback_hw_params(काष्ठा snd_pcm_substream *substream,
				       काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	अचिन्हित पूर्णांक width;
	पूर्णांक ret = 0;

	/* set codec DAI configuration */
	ret = snd_soc_dai_set_fmt(codec_dai, SND_SOC_DAIFMT_MSB |
			SND_SOC_DAIFMT_NB_NF | SND_SOC_DAIFMT_CBS_CFS);
	अगर (ret < 0)
		वापस ret;

	/* set cpu DAI configuration */
	ret = snd_soc_dai_set_fmt(cpu_dai, SND_SOC_DAIFMT_DSP_A |
			SND_SOC_DAIFMT_NB_IF | SND_SOC_DAIFMT_CBS_CFS);
	अगर (ret < 0)
		वापस ret;

	width = snd_pcm_क्रमmat_physical_width(params_क्रमmat(params));
	ret = snd_soc_dai_set_tdm_slot(cpu_dai, 1, 0, 1, width);
	अगर (ret < 0)
		वापस ret;

	/* set audio घड़ी as घड़ी source */
	ret = snd_soc_dai_set_sysclk(cpu_dai, PXA_SSP_CLK_AUDIO, 0,
			SND_SOC_CLOCK_OUT);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

/*
 * Magician uses I2S क्रम capture.
 */
अटल पूर्णांक magician_capture_hw_params(काष्ठा snd_pcm_substream *substream,
				      काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	पूर्णांक ret = 0;

	/* set codec DAI configuration */
	ret = snd_soc_dai_set_fmt(codec_dai,
			SND_SOC_DAIFMT_MSB | SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBS_CFS);
	अगर (ret < 0)
		वापस ret;

	/* set cpu DAI configuration */
	ret = snd_soc_dai_set_fmt(cpu_dai,
			SND_SOC_DAIFMT_MSB | SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBS_CFS);
	अगर (ret < 0)
		वापस ret;

	/* set the I2S प्रणाली घड़ी as output */
	ret = snd_soc_dai_set_sysclk(cpu_dai, PXA2XX_I2S_SYSCLK, 0,
			SND_SOC_CLOCK_OUT);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops magician_capture_ops = अणु
	.startup = magician_startup,
	.hw_params = magician_capture_hw_params,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_ops magician_playback_ops = अणु
	.startup = magician_startup,
	.hw_params = magician_playback_hw_params,
पूर्ण;

अटल पूर्णांक magician_get_hp(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.पूर्णांकeger.value[0] = magician_hp_चयन;
	वापस 0;
पूर्ण

अटल पूर्णांक magician_set_hp(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_card *card = snd_kcontrol_chip(kcontrol);

	अगर (magician_hp_चयन == ucontrol->value.पूर्णांकeger.value[0])
		वापस 0;

	magician_hp_चयन = ucontrol->value.पूर्णांकeger.value[0];
	magician_ext_control(&card->dapm);
	वापस 1;
पूर्ण

अटल पूर्णांक magician_get_spk(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.पूर्णांकeger.value[0] = magician_spk_चयन;
	वापस 0;
पूर्ण

अटल पूर्णांक magician_set_spk(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_card *card = snd_kcontrol_chip(kcontrol);

	अगर (magician_spk_चयन == ucontrol->value.पूर्णांकeger.value[0])
		वापस 0;

	magician_spk_चयन = ucontrol->value.पूर्णांकeger.value[0];
	magician_ext_control(&card->dapm);
	वापस 1;
पूर्ण

अटल पूर्णांक magician_get_input(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.क्रमागतerated.item[0] = magician_in_sel;
	वापस 0;
पूर्ण

अटल पूर्णांक magician_set_input(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	अगर (magician_in_sel == ucontrol->value.क्रमागतerated.item[0])
		वापस 0;

	magician_in_sel = ucontrol->value.क्रमागतerated.item[0];

	चयन (magician_in_sel) अणु
	हाल MAGICIAN_MIC:
		gpio_set_value(EGPIO_MAGICIAN_IN_SEL1, 1);
		अवरोध;
	हाल MAGICIAN_MIC_EXT:
		gpio_set_value(EGPIO_MAGICIAN_IN_SEL1, 0);
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक magician_spk_घातer(काष्ठा snd_soc_dapm_widget *w,
				काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	gpio_set_value(EGPIO_MAGICIAN_SPK_POWER, SND_SOC_DAPM_EVENT_ON(event));
	वापस 0;
पूर्ण

अटल पूर्णांक magician_hp_घातer(काष्ठा snd_soc_dapm_widget *w,
				काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	gpio_set_value(EGPIO_MAGICIAN_EP_POWER, SND_SOC_DAPM_EVENT_ON(event));
	वापस 0;
पूर्ण

अटल पूर्णांक magician_mic_bias(काष्ठा snd_soc_dapm_widget *w,
				काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	gpio_set_value(EGPIO_MAGICIAN_MIC_POWER, SND_SOC_DAPM_EVENT_ON(event));
	वापस 0;
पूर्ण

/* magician machine dapm widमाला_लो */
अटल स्थिर काष्ठा snd_soc_dapm_widget uda1380_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone Jack", magician_hp_घातer),
	SND_SOC_DAPM_SPK("Speaker", magician_spk_घातer),
	SND_SOC_DAPM_MIC("Call Mic", magician_mic_bias),
	SND_SOC_DAPM_MIC("Headset Mic", magician_mic_bias),
पूर्ण;

/* magician machine audio_map */
अटल स्थिर काष्ठा snd_soc_dapm_route audio_map[] = अणु

	/* Headphone connected to VOUTL, VOUTR */
	अणु"Headphone Jack", शून्य, "VOUTL"पूर्ण,
	अणु"Headphone Jack", शून्य, "VOUTR"पूर्ण,

	/* Speaker connected to VOUTL, VOUTR */
	अणु"Speaker", शून्य, "VOUTL"पूर्ण,
	अणु"Speaker", शून्य, "VOUTR"पूर्ण,

	/* Mics are connected to VINM */
	अणु"VINM", शून्य, "Headset Mic"पूर्ण,
	अणु"VINM", शून्य, "Call Mic"पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर input_select[] = अणु"Call Mic", "Headset Mic"पूर्ण;
अटल स्थिर काष्ठा soc_क्रमागत magician_in_sel_क्रमागत =
	SOC_ENUM_SINGLE_EXT(2, input_select);

अटल स्थिर काष्ठा snd_kcontrol_new uda1380_magician_controls[] = अणु
	SOC_SINGLE_BOOL_EXT("Headphone Switch",
			(अचिन्हित दीर्घ)&magician_hp_चयन,
			magician_get_hp, magician_set_hp),
	SOC_SINGLE_BOOL_EXT("Speaker Switch",
			(अचिन्हित दीर्घ)&magician_spk_चयन,
			magician_get_spk, magician_set_spk),
	SOC_ENUM_EXT("Input Select", magician_in_sel_क्रमागत,
			magician_get_input, magician_set_input),
पूर्ण;

/* magician digital audio पूर्णांकerface glue - connects codec <--> CPU */
SND_SOC_DAILINK_DEFS(playback,
	DAILINK_COMP_ARRAY(COMP_CPU("pxa-ssp-dai.0")),
	DAILINK_COMP_ARRAY(COMP_CODEC("uda1380-codec.0-0018",
				      "uda1380-hifi-playback")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("pxa-pcm-audio")));

SND_SOC_DAILINK_DEFS(capture,
	DAILINK_COMP_ARRAY(COMP_CPU("pxa2xx-i2s")),
	DAILINK_COMP_ARRAY(COMP_CODEC("uda1380-codec.0-0018",
				      "uda1380-hifi-capture")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("pxa-pcm-audio")));

अटल काष्ठा snd_soc_dai_link magician_dai[] = अणु
अणु
	.name = "uda1380",
	.stream_name = "UDA1380 Playback",
	.ops = &magician_playback_ops,
	SND_SOC_DAILINK_REG(playback),
पूर्ण,
अणु
	.name = "uda1380",
	.stream_name = "UDA1380 Capture",
	.ops = &magician_capture_ops,
	SND_SOC_DAILINK_REG(capture),
पूर्ण
पूर्ण;

/* magician audio machine driver */
अटल काष्ठा snd_soc_card snd_soc_card_magician = अणु
	.name = "Magician",
	.owner = THIS_MODULE,
	.dai_link = magician_dai,
	.num_links = ARRAY_SIZE(magician_dai),

	.controls = uda1380_magician_controls,
	.num_controls = ARRAY_SIZE(uda1380_magician_controls),
	.dapm_widमाला_लो = uda1380_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(uda1380_dapm_widमाला_लो),
	.dapm_routes = audio_map,
	.num_dapm_routes = ARRAY_SIZE(audio_map),
	.fully_routed = true,
पूर्ण;

अटल काष्ठा platक्रमm_device *magician_snd_device;

/*
 * FIXME: move पूर्णांकo magician board file once merged पूर्णांकo the pxa tree
 */
अटल काष्ठा uda1380_platक्रमm_data uda1380_info = अणु
	.gpio_घातer = EGPIO_MAGICIAN_CODEC_POWER,
	.gpio_reset = EGPIO_MAGICIAN_CODEC_RESET,
	.dac_clk    = UDA1380_DAC_CLK_WSPLL,
पूर्ण;

अटल काष्ठा i2c_board_info i2c_board_info[] = अणु
	अणु
		I2C_BOARD_INFO("uda1380", 0x18),
		.platक्रमm_data = &uda1380_info,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init magician_init(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा i2c_adapter *adapter;
	काष्ठा i2c_client *client;

	अगर (!machine_is_magician())
		वापस -ENODEV;

	adapter = i2c_get_adapter(0);
	अगर (!adapter)
		वापस -ENODEV;
	client = i2c_new_client_device(adapter, i2c_board_info);
	i2c_put_adapter(adapter);
	अगर (IS_ERR(client))
		वापस PTR_ERR(client);

	ret = gpio_request(EGPIO_MAGICIAN_SPK_POWER, "SPK_POWER");
	अगर (ret)
		जाओ err_request_spk;
	ret = gpio_request(EGPIO_MAGICIAN_EP_POWER, "EP_POWER");
	अगर (ret)
		जाओ err_request_ep;
	ret = gpio_request(EGPIO_MAGICIAN_MIC_POWER, "MIC_POWER");
	अगर (ret)
		जाओ err_request_mic;
	ret = gpio_request(EGPIO_MAGICIAN_IN_SEL0, "IN_SEL0");
	अगर (ret)
		जाओ err_request_in_sel0;
	ret = gpio_request(EGPIO_MAGICIAN_IN_SEL1, "IN_SEL1");
	अगर (ret)
		जाओ err_request_in_sel1;

	gpio_set_value(EGPIO_MAGICIAN_IN_SEL0, 0);

	magician_snd_device = platक्रमm_device_alloc("soc-audio", -1);
	अगर (!magician_snd_device) अणु
		ret = -ENOMEM;
		जाओ err_pdev;
	पूर्ण

	platक्रमm_set_drvdata(magician_snd_device, &snd_soc_card_magician);
	ret = platक्रमm_device_add(magician_snd_device);
	अगर (ret) अणु
		platक्रमm_device_put(magician_snd_device);
		जाओ err_pdev;
	पूर्ण

	वापस 0;

err_pdev:
	gpio_मुक्त(EGPIO_MAGICIAN_IN_SEL1);
err_request_in_sel1:
	gpio_मुक्त(EGPIO_MAGICIAN_IN_SEL0);
err_request_in_sel0:
	gpio_मुक्त(EGPIO_MAGICIAN_MIC_POWER);
err_request_mic:
	gpio_मुक्त(EGPIO_MAGICIAN_EP_POWER);
err_request_ep:
	gpio_मुक्त(EGPIO_MAGICIAN_SPK_POWER);
err_request_spk:
	वापस ret;
पूर्ण

अटल व्योम __निकास magician_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(magician_snd_device);

	gpio_set_value(EGPIO_MAGICIAN_SPK_POWER, 0);
	gpio_set_value(EGPIO_MAGICIAN_EP_POWER, 0);
	gpio_set_value(EGPIO_MAGICIAN_MIC_POWER, 0);

	gpio_मुक्त(EGPIO_MAGICIAN_IN_SEL1);
	gpio_मुक्त(EGPIO_MAGICIAN_IN_SEL0);
	gpio_मुक्त(EGPIO_MAGICIAN_MIC_POWER);
	gpio_मुक्त(EGPIO_MAGICIAN_EP_POWER);
	gpio_मुक्त(EGPIO_MAGICIAN_SPK_POWER);
पूर्ण

module_init(magician_init);
module_निकास(magician_निकास);

MODULE_AUTHOR("Philipp Zabel");
MODULE_DESCRIPTION("ALSA SoC Magician");
MODULE_LICENSE("GPL");
