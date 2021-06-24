<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// neo1973_wm8753.c - SoC audio क्रम Openmoko Neo1973 and Freerunner devices
//
// Copyright 2007 Openmoko Inc
// Author: Graeme Gregory <graeme@खोलोmoko.org>
// Copyright 2007 Wolfson Microelectronics PLC.
// Author: Graeme Gregory
//         graeme.gregory@wolfsonmicro.com or linux@wolfsonmicro.com
// Copyright 2009 Wolfson Microelectronics

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpio/consumer.h>

#समावेश <sound/soc.h>

#समावेश "regs-iis.h"
#समावेश "../codecs/wm8753.h"
#समावेश "s3c24xx-i2s.h"

अटल पूर्णांक neo1973_hअगरi_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	अचिन्हित पूर्णांक pll_out = 0, bclk = 0;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ iis_clkrate;

	iis_clkrate = s3c24xx_i2s_get_घड़ीrate();

	चयन (params_rate(params)) अणु
	हाल 8000:
	हाल 16000:
		pll_out = 12288000;
		अवरोध;
	हाल 48000:
		bclk = WM8753_BCLK_DIV_4;
		pll_out = 12288000;
		अवरोध;
	हाल 96000:
		bclk = WM8753_BCLK_DIV_2;
		pll_out = 12288000;
		अवरोध;
	हाल 11025:
		bclk = WM8753_BCLK_DIV_16;
		pll_out = 11289600;
		अवरोध;
	हाल 22050:
		bclk = WM8753_BCLK_DIV_8;
		pll_out = 11289600;
		अवरोध;
	हाल 44100:
		bclk = WM8753_BCLK_DIV_4;
		pll_out = 11289600;
		अवरोध;
	हाल 88200:
		bclk = WM8753_BCLK_DIV_2;
		pll_out = 11289600;
		अवरोध;
	पूर्ण

	/* set the codec प्रणाली घड़ी क्रम DAC and ADC */
	ret = snd_soc_dai_set_sysclk(codec_dai, WM8753_MCLK, pll_out,
		SND_SOC_CLOCK_IN);
	अगर (ret < 0)
		वापस ret;

	/* set MCLK भागision क्रम sample rate */
	ret = snd_soc_dai_set_clkभाग(cpu_dai, S3C24XX_DIV_MCLK,
		S3C2410_IISMOD_32FS);
	अगर (ret < 0)
		वापस ret;

	/* set codec BCLK भागision क्रम sample rate */
	ret = snd_soc_dai_set_clkभाग(codec_dai, WM8753_BCLKDIV, bclk);
	अगर (ret < 0)
		वापस ret;

	/* set prescaler भागision क्रम sample rate */
	ret = snd_soc_dai_set_clkभाग(cpu_dai, S3C24XX_DIV_PRESCALER,
		S3C24XX_PRESCALE(4, 4));
	अगर (ret < 0)
		वापस ret;

	/* codec PLL input is PCLK/4 */
	ret = snd_soc_dai_set_pll(codec_dai, WM8753_PLL1, 0,
		iis_clkrate / 4, pll_out);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक neo1973_hअगरi_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);

	/* disable the PLL */
	वापस snd_soc_dai_set_pll(codec_dai, WM8753_PLL1, 0, 0, 0);
पूर्ण

/*
 * Neo1973 WM8753 HiFi DAI opserations.
 */
अटल काष्ठा snd_soc_ops neo1973_hअगरi_ops = अणु
	.hw_params = neo1973_hअगरi_hw_params,
	.hw_मुक्त = neo1973_hअगरi_hw_मुक्त,
पूर्ण;

अटल पूर्णांक neo1973_voice_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	अचिन्हित पूर्णांक pcmभाग = 0;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ iis_clkrate;

	iis_clkrate = s3c24xx_i2s_get_घड़ीrate();

	अगर (params_rate(params) != 8000)
		वापस -EINVAL;
	अगर (params_channels(params) != 1)
		वापस -EINVAL;

	pcmभाग = WM8753_PCM_DIV_6; /* 2.048 MHz */

	/* set the codec प्रणाली घड़ी क्रम DAC and ADC */
	ret = snd_soc_dai_set_sysclk(codec_dai, WM8753_PCMCLK, 12288000,
		SND_SOC_CLOCK_IN);
	अगर (ret < 0)
		वापस ret;

	/* set codec PCM भागision क्रम sample rate */
	ret = snd_soc_dai_set_clkभाग(codec_dai, WM8753_PCMDIV, pcmभाग);
	अगर (ret < 0)
		वापस ret;

	/* configure and enable PLL क्रम 12.288MHz output */
	ret = snd_soc_dai_set_pll(codec_dai, WM8753_PLL2, 0,
		iis_clkrate / 4, 12288000);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक neo1973_voice_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);

	/* disable the PLL */
	वापस snd_soc_dai_set_pll(codec_dai, WM8753_PLL2, 0, 0, 0);
पूर्ण

अटल काष्ठा snd_soc_ops neo1973_voice_ops = अणु
	.hw_params = neo1973_voice_hw_params,
	.hw_मुक्त = neo1973_voice_hw_मुक्त,
पूर्ण;

अटल काष्ठा gpio_desc *gpiod_hp_in, *gpiod_amp_shut;
अटल पूर्णांक gta02_speaker_enabled;

अटल पूर्णांक lm4853_set_spk(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	gta02_speaker_enabled = ucontrol->value.पूर्णांकeger.value[0];

	gpiod_set_value(gpiod_hp_in, !gta02_speaker_enabled);

	वापस 0;
पूर्ण

अटल पूर्णांक lm4853_get_spk(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.पूर्णांकeger.value[0] = gta02_speaker_enabled;
	वापस 0;
पूर्ण

अटल पूर्णांक lm4853_event(काष्ठा snd_soc_dapm_widget *w,
			काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	gpiod_set_value(gpiod_amp_shut, SND_SOC_DAPM_EVENT_OFF(event));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget neo1973_wm8753_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_LINE("GSM Line Out", शून्य),
	SND_SOC_DAPM_LINE("GSM Line In", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_MIC("Handset Mic", शून्य),
	SND_SOC_DAPM_SPK("Handset Spk", शून्य),
	SND_SOC_DAPM_SPK("Stereo Out", lm4853_event),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route neo1973_wm8753_routes[] = अणु
	/* Connections to the GSM Module */
	अणु"GSM Line Out", शून्य, "MONO1"पूर्ण,
	अणु"GSM Line Out", शून्य, "MONO2"पूर्ण,
	अणु"RXP", शून्य, "GSM Line In"पूर्ण,
	अणु"RXN", शून्य, "GSM Line In"पूर्ण,

	/* Connections to Headset */
	अणु"MIC1", शून्य, "Mic Bias"पूर्ण,
	अणु"Mic Bias", शून्य, "Headset Mic"पूर्ण,

	/* Call Mic */
	अणु"MIC2", शून्य, "Mic Bias"पूर्ण,
	अणु"MIC2N", शून्य, "Mic Bias"पूर्ण,
	अणु"Mic Bias", शून्य, "Handset Mic"पूर्ण,

	/* Connect the ALC pins */
	अणु"ACIN", शून्य, "ACOP"पूर्ण,

	/* Connections to the amp */
	अणु"Stereo Out", शून्य, "LOUT1"पूर्ण,
	अणु"Stereo Out", शून्य, "ROUT1"पूर्ण,

	/* Call Speaker */
	अणु"Handset Spk", शून्य, "LOUT2"पूर्ण,
	अणु"Handset Spk", शून्य, "ROUT2"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new neo1973_wm8753_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("GSM Line Out"),
	SOC_DAPM_PIN_SWITCH("GSM Line In"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Handset Mic"),
	SOC_DAPM_PIN_SWITCH("Handset Spk"),
	SOC_DAPM_PIN_SWITCH("Stereo Out"),

	SOC_SINGLE_BOOL_EXT("Amp Spk Switch", 0,
		lm4853_get_spk,
		lm4853_set_spk),
पूर्ण;

अटल पूर्णांक neo1973_wm8753_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_card *card = rtd->card;

	/* set endpoपूर्णांकs to शेष off mode */
	snd_soc_dapm_disable_pin(&card->dapm, "GSM Line Out");
	snd_soc_dapm_disable_pin(&card->dapm, "GSM Line In");
	snd_soc_dapm_disable_pin(&card->dapm, "Headset Mic");
	snd_soc_dapm_disable_pin(&card->dapm, "Handset Mic");
	snd_soc_dapm_disable_pin(&card->dapm, "Stereo Out");
	snd_soc_dapm_disable_pin(&card->dapm, "Handset Spk");

	/* allow audio paths from the GSM modem to run during suspend */
	snd_soc_dapm_ignore_suspend(&card->dapm, "GSM Line Out");
	snd_soc_dapm_ignore_suspend(&card->dapm, "GSM Line In");
	snd_soc_dapm_ignore_suspend(&card->dapm, "Headset Mic");
	snd_soc_dapm_ignore_suspend(&card->dapm, "Handset Mic");
	snd_soc_dapm_ignore_suspend(&card->dapm, "Stereo Out");
	snd_soc_dapm_ignore_suspend(&card->dapm, "Handset Spk");

	वापस 0;
पूर्ण

SND_SOC_DAILINK_DEFS(wm8753,
	DAILINK_COMP_ARRAY(COMP_CPU("s3c24xx-iis")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm8753.0-001a", "wm8753-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("s3c24xx-iis")));

SND_SOC_DAILINK_DEFS(bluetooth,
	DAILINK_COMP_ARRAY(COMP_CPU("bt-sco-pcm")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm8753.0-001a", "wm8753-voice")));

अटल काष्ठा snd_soc_dai_link neo1973_dai[] = अणु
अणु /* Hअगरi Playback - क्रम similatious use with voice below */
	.name = "WM8753",
	.stream_name = "WM8753 HiFi",
	.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
		   SND_SOC_DAIFMT_CBM_CFM,
	.init = neo1973_wm8753_init,
	.ops = &neo1973_hअगरi_ops,
	SND_SOC_DAILINK_REG(wm8753),
पूर्ण,
अणु /* Voice via BT */
	.name = "Bluetooth",
	.stream_name = "Voice",
	.dai_fmt = SND_SOC_DAIFMT_DSP_B | SND_SOC_DAIFMT_NB_NF |
		   SND_SOC_DAIFMT_CBS_CFS,
	.ops = &neo1973_voice_ops,
	SND_SOC_DAILINK_REG(bluetooth),
पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_aux_dev neo1973_aux_devs[] = अणु
	अणु
		.dlc = COMP_AUX("dfbmcs320.0"),
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_codec_conf neo1973_codec_conf[] = अणु
	अणु
		.dlc = COMP_CODEC_CONF("lm4857.0-007c"),
		.name_prefix = "Amp",
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_card neo1973 = अणु
	.name = "neo1973gta02",
	.owner = THIS_MODULE,
	.dai_link = neo1973_dai,
	.num_links = ARRAY_SIZE(neo1973_dai),
	.aux_dev = neo1973_aux_devs,
	.num_aux_devs = ARRAY_SIZE(neo1973_aux_devs),
	.codec_conf = neo1973_codec_conf,
	.num_configs = ARRAY_SIZE(neo1973_codec_conf),

	.controls = neo1973_wm8753_controls,
	.num_controls = ARRAY_SIZE(neo1973_wm8753_controls),
	.dapm_widमाला_लो = neo1973_wm8753_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(neo1973_wm8753_dapm_widमाला_लो),
	.dapm_routes = neo1973_wm8753_routes,
	.num_dapm_routes = ARRAY_SIZE(neo1973_wm8753_routes),
	.fully_routed = true,
पूर्ण;

अटल पूर्णांक neo1973_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;

	gpiod_hp_in = devm_gpiod_get(dev, "hp", GPIOD_OUT_HIGH);
	अगर (IS_ERR(gpiod_hp_in)) अणु
		dev_err(dev, "missing gpio %s\n", "hp");
		वापस PTR_ERR(gpiod_hp_in);
	पूर्ण
	gpiod_amp_shut = devm_gpiod_get(dev, "amp-shut", GPIOD_OUT_HIGH);
	अगर (IS_ERR(gpiod_amp_shut)) अणु
		dev_err(dev, "missing gpio %s\n", "amp-shut");
		वापस PTR_ERR(gpiod_amp_shut);
	पूर्ण

	neo1973.dev = dev;
	वापस devm_snd_soc_रेजिस्टर_card(dev, &neo1973);
पूर्ण

काष्ठा platक्रमm_driver neo1973_audio = अणु
	.driver = अणु
		.name = "neo1973-audio",
		.pm = &snd_soc_pm_ops,
	पूर्ण,
	.probe = neo1973_probe,
पूर्ण;
module_platक्रमm_driver(neo1973_audio);

/* Module inक्रमmation */
MODULE_AUTHOR("Graeme Gregory, graeme@openmoko.org, www.openmoko.org");
MODULE_DESCRIPTION("ALSA SoC WM8753 Neo1973 and Frerunner");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:neo1973-audio");
