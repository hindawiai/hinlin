<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel Broxton-P I2S Machine Driver
 *
 * Copyright (C) 2016, Intel Corporation. All rights reserved.
 *
 * Modअगरied from:
 *   Intel Skylake I2S Machine driver
 */

#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/core.h>
#समावेश <sound/jack.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-acpi.h>
#समावेश "../../codecs/hdac_hdmi.h"
#समावेश "../../codecs/da7219.h"
#समावेश "../../codecs/da7219-aad.h"
#समावेश "../common/soc-intel-quirks.h"
#समावेश "hda_dsp_common.h"

#घोषणा BXT_DIALOG_CODEC_DAI	"da7219-hifi"
#घोषणा BXT_MAXIM_CODEC_DAI	"HiFi"
#घोषणा MAX98390_DEV0_NAME	"i2c-MX98390:00"
#घोषणा MAX98390_DEV1_NAME	"i2c-MX98390:01"
#घोषणा DUAL_CHANNEL		2
#घोषणा QUAD_CHANNEL		4

#घोषणा SPKAMP_MAX98357A	1
#घोषणा SPKAMP_MAX98390	2

अटल काष्ठा snd_soc_jack broxton_headset;
अटल काष्ठा snd_soc_jack broxton_hdmi[3];

काष्ठा bxt_hdmi_pcm अणु
	काष्ठा list_head head;
	काष्ठा snd_soc_dai *codec_dai;
	पूर्णांक device;
पूर्ण;

काष्ठा bxt_card_निजी अणु
	काष्ठा list_head hdmi_pcm_list;
	bool common_hdmi_codec_drv;
	पूर्णांक spkamp;
पूर्ण;

क्रमागत अणु
	BXT_DPCM_AUDIO_PB = 0,
	BXT_DPCM_AUDIO_CP,
	BXT_DPCM_AUDIO_HS_PB,
	BXT_DPCM_AUDIO_REF_CP,
	BXT_DPCM_AUDIO_DMIC_CP,
	BXT_DPCM_AUDIO_HDMI1_PB,
	BXT_DPCM_AUDIO_HDMI2_PB,
	BXT_DPCM_AUDIO_HDMI3_PB,
पूर्ण;

अटल पूर्णांक platक्रमm_घड़ी_control(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *k, पूर्णांक  event)
अणु
	पूर्णांक ret = 0;
	काष्ठा snd_soc_dapm_context *dapm = w->dapm;
	काष्ठा snd_soc_card *card = dapm->card;
	काष्ठा snd_soc_dai *codec_dai;

	codec_dai = snd_soc_card_get_codec_dai(card, BXT_DIALOG_CODEC_DAI);
	अगर (!codec_dai) अणु
		dev_err(card->dev, "Codec dai not found; Unable to set/unset codec pll\n");
		वापस -EIO;
	पूर्ण

	अगर (SND_SOC_DAPM_EVENT_OFF(event)) अणु
		ret = snd_soc_dai_set_pll(codec_dai, 0,
			DA7219_SYSCLK_MCLK, 0, 0);
		अगर (ret)
			dev_err(card->dev, "failed to stop PLL: %d\n", ret);
	पूर्ण अन्यथा अगर(SND_SOC_DAPM_EVENT_ON(event)) अणु
		ret = snd_soc_dai_set_pll(codec_dai, 0,
			DA7219_SYSCLK_PLL_SRM, 0, DA7219_PLL_FREQ_OUT_98304);
		अगर (ret)
			dev_err(card->dev, "failed to start PLL: %d\n", ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new broxton_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Headphone Jack"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new max98357a_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Spk"),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new max98390_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Left Spk"),
	SOC_DAPM_PIN_SWITCH("Right Spk"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget broxton_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_MIC("SoC DMIC", शून्य),
	SND_SOC_DAPM_SPK("HDMI1", शून्य),
	SND_SOC_DAPM_SPK("HDMI2", शून्य),
	SND_SOC_DAPM_SPK("HDMI3", शून्य),
	SND_SOC_DAPM_SUPPLY("Platform Clock", SND_SOC_NOPM, 0, 0,
			platक्रमm_घड़ी_control,	SND_SOC_DAPM_POST_PMD|SND_SOC_DAPM_PRE_PMU),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget max98357a_widमाला_लो[] = अणु
	SND_SOC_DAPM_SPK("Spk", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget max98390_widमाला_लो[] = अणु
	SND_SOC_DAPM_SPK("Left Spk", शून्य),
	SND_SOC_DAPM_SPK("Right Spk", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route audio_map[] = अणु
	/* HP jack connectors - unknown अगर we have jack detection */
	अणु"Headphone Jack", शून्य, "HPL"पूर्ण,
	अणु"Headphone Jack", शून्य, "HPR"पूर्ण,

	/* other jacks */
	अणु"MIC", शून्य, "Headset Mic"पूर्ण,

	/* digital mics */
	अणु"DMic", शून्य, "SoC DMIC"पूर्ण,

	/* CODEC BE connections */
	अणु"HDMI1", शून्य, "hif5-0 Output"पूर्ण,
	अणु"HDMI2", शून्य, "hif6-0 Output"पूर्ण,
	अणु"HDMI2", शून्य, "hif7-0 Output"पूर्ण,

	अणु"hifi3", शून्य, "iDisp3 Tx"पूर्ण,
	अणु"iDisp3 Tx", शून्य, "iDisp3_out"पूर्ण,
	अणु"hifi2", शून्य, "iDisp2 Tx"पूर्ण,
	अणु"iDisp2 Tx", शून्य, "iDisp2_out"पूर्ण,
	अणु"hifi1", शून्य, "iDisp1 Tx"पूर्ण,
	अणु"iDisp1 Tx", शून्य, "iDisp1_out"पूर्ण,

	/* DMIC */
	अणु"dmic01_hifi", शून्य, "DMIC01 Rx"पूर्ण,
	अणु"DMIC01 Rx", शून्य, "DMIC AIF"पूर्ण,

	अणु "Headphone Jack", शून्य, "Platform Clock" पूर्ण,
	अणु "Headset Mic", शून्य, "Platform Clock" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route max98357a_routes[] = अणु
	/* speaker */
	अणु"Spk", शून्य, "Speaker"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route max98390_routes[] = अणु
	/* Speaker */
	अणु"Left Spk", शून्य, "Left BE_OUT"पूर्ण,
	अणु"Right Spk", शून्य, "Right BE_OUT"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route broxton_map[] = अणु
	अणु"HiFi Playback", शून्य, "ssp5 Tx"पूर्ण,
	अणु"ssp5 Tx", शून्य, "codec0_out"पूर्ण,

	अणु"Playback", शून्य, "ssp1 Tx"पूर्ण,
	अणु"ssp1 Tx", शून्य, "codec1_out"पूर्ण,

	अणु"codec0_in", शून्य, "ssp1 Rx"पूर्ण,
	अणु"ssp1 Rx", शून्य, "Capture"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route gemini_map[] = अणु
	अणु"HiFi Playback", शून्य, "ssp1 Tx"पूर्ण,
	अणु"ssp1 Tx", शून्य, "codec0_out"पूर्ण,

	अणु"Playback", शून्य, "ssp2 Tx"पूर्ण,
	अणु"ssp2 Tx", शून्य, "codec1_out"पूर्ण,

	अणु"codec0_in", शून्य, "ssp2 Rx"पूर्ण,
	अणु"ssp2 Rx", शून्य, "Capture"पूर्ण,
पूर्ण;

अटल पूर्णांक broxton_ssp_fixup(काष्ठा snd_soc_pcm_runसमय *rtd,
			काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_पूर्णांकerval *rate = hw_param_पूर्णांकerval(params,
			SNDRV_PCM_HW_PARAM_RATE);
	काष्ठा snd_पूर्णांकerval *chan = hw_param_पूर्णांकerval(params,
			SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा snd_mask *fmt = hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT);

	/* The ADSP will convert the FE rate to 48k, stereo */
	rate->min = rate->max = 48000;
	chan->min = chan->max = DUAL_CHANNEL;

	/* set SSP to 24 bit */
	snd_mask_none(fmt);
	snd_mask_set_क्रमmat(fmt, SNDRV_PCM_FORMAT_S24_LE);

	वापस 0;
पूर्ण

अटल पूर्णांक broxton_da7219_codec_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	पूर्णांक ret;
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_component *component = asoc_rtd_to_codec(rtd, 0)->component;
	पूर्णांक clk_freq;

	/* Configure sysclk क्रम codec */
	अगर (soc_पूर्णांकel_is_cml())
		clk_freq = 24000000;
	अन्यथा
		clk_freq = 19200000;

	ret = snd_soc_dai_set_sysclk(codec_dai, DA7219_CLKSRC_MCLK, clk_freq,
				     SND_SOC_CLOCK_IN);

	अगर (ret) अणु
		dev_err(rtd->dev, "can't set codec sysclk configuration\n");
		वापस ret;
	पूर्ण

	/*
	 * Headset buttons map to the google Reference headset.
	 * These can be configured by userspace.
	 */
	ret = snd_soc_card_jack_new(rtd->card, "Headset Jack",
			SND_JACK_HEADSET | SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			SND_JACK_BTN_2 | SND_JACK_BTN_3 | SND_JACK_LINEOUT,
			&broxton_headset, शून्य, 0);
	अगर (ret) अणु
		dev_err(rtd->dev, "Headset Jack creation failed: %d\n", ret);
		वापस ret;
	पूर्ण

	snd_jack_set_key(broxton_headset.jack, SND_JACK_BTN_0, KEY_PLAYPAUSE);
	snd_jack_set_key(broxton_headset.jack, SND_JACK_BTN_1, KEY_VOLUMEUP);
	snd_jack_set_key(broxton_headset.jack, SND_JACK_BTN_2, KEY_VOLUMEDOWN);
	snd_jack_set_key(broxton_headset.jack, SND_JACK_BTN_3,
			 KEY_VOICECOMMAND);

	da7219_aad_jack_det(component, &broxton_headset);

	snd_soc_dapm_ignore_suspend(&rtd->card->dapm, "SoC DMIC");

	वापस ret;
पूर्ण

अटल पूर्णांक broxton_hdmi_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा bxt_card_निजी *ctx = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा snd_soc_dai *dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा bxt_hdmi_pcm *pcm;

	pcm = devm_kzalloc(rtd->card->dev, माप(*pcm), GFP_KERNEL);
	अगर (!pcm)
		वापस -ENOMEM;

	pcm->device = BXT_DPCM_AUDIO_HDMI1_PB + dai->id;
	pcm->codec_dai = dai;

	list_add_tail(&pcm->head, &ctx->hdmi_pcm_list);

	वापस 0;
पूर्ण

अटल पूर्णांक broxton_da7219_fe_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_dapm_context *dapm;
	काष्ठा snd_soc_component *component = asoc_rtd_to_cpu(rtd, 0)->component;

	dapm = snd_soc_component_get_dapm(component);
	snd_soc_dapm_ignore_suspend(dapm, "Reference Capture");

	वापस 0;
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक rates[] = अणु
	48000,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_rates = अणु
	.count = ARRAY_SIZE(rates),
	.list  = rates,
	.mask = 0,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक channels[] = अणु
	DUAL_CHANNEL,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_channels = अणु
	.count = ARRAY_SIZE(channels),
	.list = channels,
	.mask = 0,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक channels_quad[] = अणु
	QUAD_CHANNEL,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_channels_quad = अणु
	.count = ARRAY_SIZE(channels_quad),
	.list = channels_quad,
	.mask = 0,
पूर्ण;

अटल पूर्णांक bxt_fe_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	/*
	 * On this platक्रमm क्रम PCM device we support,
	 * 48Khz
	 * stereo
	 * 16 bit audio
	 */

	runसमय->hw.channels_max = DUAL_CHANNEL;
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
					   &स्थिरraपूर्णांकs_channels);

	runसमय->hw.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE;
	snd_pcm_hw_स्थिरraपूर्णांक_msbits(runसमय, 0, 16, 16);

	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0,
				SNDRV_PCM_HW_PARAM_RATE, &स्थिरraपूर्णांकs_rates);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops broxton_da7219_fe_ops = अणु
	.startup = bxt_fe_startup,
पूर्ण;

अटल पूर्णांक broxton_dmic_fixup(काष्ठा snd_soc_pcm_runसमय *rtd,
			काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_पूर्णांकerval *chan = hw_param_पूर्णांकerval(params,
						SNDRV_PCM_HW_PARAM_CHANNELS);
	अगर (params_channels(params) == 2)
		chan->min = chan->max = 2;
	अन्यथा
		chan->min = chan->max = 4;

	वापस 0;
पूर्ण

अटल पूर्णांक broxton_dmic_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	runसमय->hw.channels_min = runसमय->hw.channels_max = QUAD_CHANNEL;
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
			&स्थिरraपूर्णांकs_channels_quad);

	वापस snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
			SNDRV_PCM_HW_PARAM_RATE, &स्थिरraपूर्णांकs_rates);
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops broxton_dmic_ops = अणु
	.startup = broxton_dmic_startup,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक rates_16000[] = अणु
	16000,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_16000 = अणु
	.count = ARRAY_SIZE(rates_16000),
	.list  = rates_16000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ch_mono[] = अणु
	1,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_refcap = अणु
	.count = ARRAY_SIZE(ch_mono),
	.list  = ch_mono,
पूर्ण;

अटल पूर्णांक broxton_refcap_startup(काष्ठा snd_pcm_substream *substream)
अणु
	substream->runसमय->hw.channels_max = 1;
	snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
				   SNDRV_PCM_HW_PARAM_CHANNELS,
				   &स्थिरraपूर्णांकs_refcap);

	वापस snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
			SNDRV_PCM_HW_PARAM_RATE,
			&स्थिरraपूर्णांकs_16000);
पूर्ण;

अटल स्थिर काष्ठा snd_soc_ops broxton_refcap_ops = अणु
	.startup = broxton_refcap_startup,
पूर्ण;

/* broxton digital audio पूर्णांकerface glue - connects codec <--> CPU */
SND_SOC_DAILINK_DEF(dummy,
	DAILINK_COMP_ARRAY(COMP_DUMMY()));

SND_SOC_DAILINK_DEF(प्रणाली,
	DAILINK_COMP_ARRAY(COMP_CPU("System Pin")));

SND_SOC_DAILINK_DEF(प्रणाली2,
	DAILINK_COMP_ARRAY(COMP_CPU("System Pin2")));

SND_SOC_DAILINK_DEF(reference,
	DAILINK_COMP_ARRAY(COMP_CPU("Reference Pin")));

SND_SOC_DAILINK_DEF(dmic,
	DAILINK_COMP_ARRAY(COMP_CPU("DMIC Pin")));

SND_SOC_DAILINK_DEF(hdmi1,
	DAILINK_COMP_ARRAY(COMP_CPU("HDMI1 Pin")));

SND_SOC_DAILINK_DEF(hdmi2,
	DAILINK_COMP_ARRAY(COMP_CPU("HDMI2 Pin")));

SND_SOC_DAILINK_DEF(hdmi3,
	DAILINK_COMP_ARRAY(COMP_CPU("HDMI3 Pin")));

 /* Back End DAI */
SND_SOC_DAILINK_DEF(ssp5_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("SSP5 Pin")));
SND_SOC_DAILINK_DEF(ssp5_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("MX98357A:00",
				      BXT_MAXIM_CODEC_DAI)));
SND_SOC_DAILINK_DEF(max98390_codec,
	DAILINK_COMP_ARRAY(
	/* Left */	COMP_CODEC(MAX98390_DEV0_NAME, "max98390-aif1"),
	/* Right */	COMP_CODEC(MAX98390_DEV1_NAME, "max98390-aif1")));

SND_SOC_DAILINK_DEF(ssp1_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("SSP1 Pin")));
SND_SOC_DAILINK_DEF(ssp1_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("i2c-DLGS7219:00",
				      BXT_DIALOG_CODEC_DAI)));

SND_SOC_DAILINK_DEF(dmic_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("DMIC01 Pin")));

SND_SOC_DAILINK_DEF(dmic16k_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("DMIC16k Pin")));

SND_SOC_DAILINK_DEF(dmic_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("dmic-codec", "dmic-hifi")));

SND_SOC_DAILINK_DEF(idisp1_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("iDisp1 Pin")));
SND_SOC_DAILINK_DEF(idisp1_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("ehdaudio0D2", "intel-hdmi-hifi1")));

SND_SOC_DAILINK_DEF(idisp2_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("iDisp2 Pin")));
SND_SOC_DAILINK_DEF(idisp2_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("ehdaudio0D2",
				      "intel-hdmi-hifi2")));

SND_SOC_DAILINK_DEF(idisp3_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("iDisp3 Pin")));
SND_SOC_DAILINK_DEF(idisp3_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("ehdaudio0D2",
				      "intel-hdmi-hifi3")));

SND_SOC_DAILINK_DEF(platक्रमm,
	DAILINK_COMP_ARRAY(COMP_PLATFORM("0000:00:0e.0")));

अटल काष्ठा snd_soc_dai_link broxton_dais[] = अणु
	/* Front End DAI links */
	[BXT_DPCM_AUDIO_PB] =
	अणु
		.name = "Bxt Audio Port",
		.stream_name = "Audio",
		.dynamic = 1,
		.nonatomic = 1,
		.init = broxton_da7219_fe_init,
		.trigger = अणु
			SND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.dpcm_playback = 1,
		.ops = &broxton_da7219_fe_ops,
		SND_SOC_DAILINK_REG(प्रणाली, dummy, platक्रमm),
	पूर्ण,
	[BXT_DPCM_AUDIO_CP] =
	अणु
		.name = "Bxt Audio Capture Port",
		.stream_name = "Audio Record",
		.dynamic = 1,
		.nonatomic = 1,
		.trigger = अणु
			SND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.dpcm_capture = 1,
		.ops = &broxton_da7219_fe_ops,
		SND_SOC_DAILINK_REG(प्रणाली, dummy, platक्रमm),
	पूर्ण,
	[BXT_DPCM_AUDIO_HS_PB] = अणु
		.name = "Bxt Audio Headset Playback",
		.stream_name = "Headset Playback",
		.dynamic = 1,
		.nonatomic = 1,
		.trigger = अणु
			SND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.dpcm_playback = 1,
		.ops = &broxton_da7219_fe_ops,
		SND_SOC_DAILINK_REG(प्रणाली2, dummy, platक्रमm),
	पूर्ण,
	[BXT_DPCM_AUDIO_REF_CP] =
	अणु
		.name = "Bxt Audio Reference cap",
		.stream_name = "Refcap",
		.init = शून्य,
		.dpcm_capture = 1,
		.nonatomic = 1,
		.dynamic = 1,
		.ops = &broxton_refcap_ops,
		SND_SOC_DAILINK_REG(reference, dummy, platक्रमm),
	पूर्ण,
	[BXT_DPCM_AUDIO_DMIC_CP] =
	अणु
		.name = "Bxt Audio DMIC cap",
		.stream_name = "dmiccap",
		.init = शून्य,
		.dpcm_capture = 1,
		.nonatomic = 1,
		.dynamic = 1,
		.ops = &broxton_dmic_ops,
		SND_SOC_DAILINK_REG(dmic, dummy, platक्रमm),
	पूर्ण,
	[BXT_DPCM_AUDIO_HDMI1_PB] =
	अणु
		.name = "Bxt HDMI Port1",
		.stream_name = "Hdmi1",
		.dpcm_playback = 1,
		.init = शून्य,
		.nonatomic = 1,
		.dynamic = 1,
		SND_SOC_DAILINK_REG(hdmi1, dummy, platक्रमm),
	पूर्ण,
	[BXT_DPCM_AUDIO_HDMI2_PB] =
	अणु
		.name = "Bxt HDMI Port2",
		.stream_name = "Hdmi2",
		.dpcm_playback = 1,
		.init = शून्य,
		.nonatomic = 1,
		.dynamic = 1,
		SND_SOC_DAILINK_REG(hdmi2, dummy, platक्रमm),
	पूर्ण,
	[BXT_DPCM_AUDIO_HDMI3_PB] =
	अणु
		.name = "Bxt HDMI Port3",
		.stream_name = "Hdmi3",
		.dpcm_playback = 1,
		.init = शून्य,
		.nonatomic = 1,
		.dynamic = 1,
		SND_SOC_DAILINK_REG(hdmi3, dummy, platक्रमm),
	पूर्ण,
	/* Back End DAI links */
	अणु
		/* SSP5 - Codec */
		.name = "SSP5-Codec",
		.id = 0,
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S |
			SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBS_CFS,
		.ignore_pmकरोwn_समय = 1,
		.be_hw_params_fixup = broxton_ssp_fixup,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(ssp5_pin, ssp5_codec, platक्रमm),
	पूर्ण,
	अणु
		/* SSP1 - Codec */
		.name = "SSP1-Codec",
		.id = 1,
		.no_pcm = 1,
		.init = broxton_da7219_codec_init,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBS_CFS,
		.ignore_pmकरोwn_समय = 1,
		.be_hw_params_fixup = broxton_ssp_fixup,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(ssp1_pin, ssp1_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "dmic01",
		.id = 2,
		.ignore_suspend = 1,
		.be_hw_params_fixup = broxton_dmic_fixup,
		.dpcm_capture = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(dmic_pin, dmic_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "iDisp1",
		.id = 3,
		.init = broxton_hdmi_init,
		.dpcm_playback = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(idisp1_pin, idisp1_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "iDisp2",
		.id = 4,
		.init = broxton_hdmi_init,
		.dpcm_playback = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(idisp2_pin, idisp2_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "iDisp3",
		.id = 5,
		.init = broxton_hdmi_init,
		.dpcm_playback = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(idisp3_pin, idisp3_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "dmic16k",
		.id = 6,
		.be_hw_params_fixup = broxton_dmic_fixup,
		.dpcm_capture = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(dmic16k_pin, dmic_codec, platक्रमm),
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_codec_conf max98390_codec_confs[] = अणु
	अणु
		.dlc = COMP_CODEC_CONF(MAX98390_DEV0_NAME),
		.name_prefix = "Left",
	पूर्ण,
	अणु
		.dlc = COMP_CODEC_CONF(MAX98390_DEV1_NAME),
		.name_prefix = "Right",
	पूर्ण,
पूर्ण;

#घोषणा NAME_SIZE	32
अटल पूर्णांक bxt_card_late_probe(काष्ठा snd_soc_card *card)
अणु
	काष्ठा bxt_card_निजी *ctx = snd_soc_card_get_drvdata(card);
	काष्ठा bxt_hdmi_pcm *pcm;
	काष्ठा snd_soc_component *component = शून्य;
	स्थिर काष्ठा snd_kcontrol_new *controls;
	स्थिर काष्ठा snd_soc_dapm_widget *widमाला_लो;
	स्थिर काष्ठा snd_soc_dapm_route *routes;
	पूर्णांक num_controls, num_widमाला_लो, num_routes, err, i = 0;
	अक्षर jack_name[NAME_SIZE];

	चयन (ctx->spkamp) अणु
	हाल SPKAMP_MAX98357A:
		controls = max98357a_controls;
		num_controls = ARRAY_SIZE(max98357a_controls);
		widमाला_लो = max98357a_widमाला_लो;
		num_widमाला_लो = ARRAY_SIZE(max98357a_widमाला_लो);
		routes = max98357a_routes;
		num_routes = ARRAY_SIZE(max98357a_routes);
		अवरोध;
	हाल SPKAMP_MAX98390:
		controls = max98390_controls;
		num_controls = ARRAY_SIZE(max98390_controls);
		widमाला_लो = max98390_widमाला_लो;
		num_widमाला_लो = ARRAY_SIZE(max98390_widमाला_लो);
		routes = max98390_routes;
		num_routes = ARRAY_SIZE(max98390_routes);
		अवरोध;
	शेष:
		dev_err(card->dev, "Invalid speaker amplifier %d\n", ctx->spkamp);
		वापस -EINVAL;
	पूर्ण

	err = snd_soc_dapm_new_controls(&card->dapm, widमाला_लो, num_widमाला_लो);
	अगर (err) अणु
		dev_err(card->dev, "Fail to new widgets\n");
		वापस err;
	पूर्ण

	err = snd_soc_add_card_controls(card, controls, num_controls);
	अगर (err) अणु
		dev_err(card->dev, "Fail to add controls\n");
		वापस err;
	पूर्ण

	err = snd_soc_dapm_add_routes(&card->dapm, routes, num_routes);
	अगर (err) अणु
		dev_err(card->dev, "Fail to add routes\n");
		वापस err;
	पूर्ण

	अगर (soc_पूर्णांकel_is_glk())
		snd_soc_dapm_add_routes(&card->dapm, gemini_map,
					ARRAY_SIZE(gemini_map));
	अन्यथा
		snd_soc_dapm_add_routes(&card->dapm, broxton_map,
					ARRAY_SIZE(broxton_map));

	अगर (list_empty(&ctx->hdmi_pcm_list))
		वापस -EINVAL;

	अगर (ctx->common_hdmi_codec_drv) अणु
		pcm = list_first_entry(&ctx->hdmi_pcm_list, काष्ठा bxt_hdmi_pcm,
				       head);
		component = pcm->codec_dai->component;
		वापस hda_dsp_hdmi_build_controls(card, component);
	पूर्ण

	list_क्रम_each_entry(pcm, &ctx->hdmi_pcm_list, head) अणु
		component = pcm->codec_dai->component;
		snम_लिखो(jack_name, माप(jack_name),
			"HDMI/DP, pcm=%d Jack", pcm->device);
		err = snd_soc_card_jack_new(card, jack_name,
					SND_JACK_AVOUT, &broxton_hdmi[i],
					शून्य, 0);

		अगर (err)
			वापस err;

		err = hdac_hdmi_jack_init(pcm->codec_dai, pcm->device,
						&broxton_hdmi[i]);
		अगर (err < 0)
			वापस err;

		i++;
	पूर्ण

	वापस hdac_hdmi_jack_port_init(component, &card->dapm);
पूर्ण

/* broxton audio machine driver क्रम SPT + da7219 */
अटल काष्ठा snd_soc_card broxton_audio_card = अणु
	.name = "bxtda7219max",
	.owner = THIS_MODULE,
	.dai_link = broxton_dais,
	.num_links = ARRAY_SIZE(broxton_dais),
	.controls = broxton_controls,
	.num_controls = ARRAY_SIZE(broxton_controls),
	.dapm_widमाला_लो = broxton_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(broxton_widमाला_लो),
	.dapm_routes = audio_map,
	.num_dapm_routes = ARRAY_SIZE(audio_map),
	.fully_routed = true,
	.late_probe = bxt_card_late_probe,
पूर्ण;

अटल पूर्णांक broxton_audio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bxt_card_निजी *ctx;
	काष्ठा snd_soc_acpi_mach *mach;
	स्थिर अक्षर *platक्रमm_name;
	पूर्णांक ret;

	ctx = devm_kzalloc(&pdev->dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&ctx->hdmi_pcm_list);

	अगर (acpi_dev_present("MX98390", शून्य, -1))
		ctx->spkamp = SPKAMP_MAX98390;
	अन्यथा
		ctx->spkamp = SPKAMP_MAX98357A;

	broxton_audio_card.dev = &pdev->dev;
	snd_soc_card_set_drvdata(&broxton_audio_card, ctx);
	अगर (soc_पूर्णांकel_is_glk()) अणु
		अचिन्हित पूर्णांक i;

		broxton_audio_card.name = "glkda7219max";
		/* Fixup the SSP entries क्रम geminilake */
		क्रम (i = 0; i < ARRAY_SIZE(broxton_dais); i++) अणु
			/* MAXIM_CODEC is connected to SSP1. */
			अगर (!म_भेद(broxton_dais[i].codecs->dai_name,
				    BXT_MAXIM_CODEC_DAI)) अणु
				broxton_dais[i].name = "SSP1-Codec";
				broxton_dais[i].cpus->dai_name = "SSP1 Pin";
			पूर्ण
			/* DIALOG_CODE is connected to SSP2 */
			अन्यथा अगर (!म_भेद(broxton_dais[i].codecs->dai_name,
					 BXT_DIALOG_CODEC_DAI)) अणु
				broxton_dais[i].name = "SSP2-Codec";
				broxton_dais[i].cpus->dai_name = "SSP2 Pin";
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (soc_पूर्णांकel_is_cml()) अणु
		अचिन्हित पूर्णांक i;

		अगर (ctx->spkamp == SPKAMP_MAX98390) अणु
			broxton_audio_card.name = "cml_max98390_da7219";

			broxton_audio_card.codec_conf = max98390_codec_confs;
			broxton_audio_card.num_configs = ARRAY_SIZE(max98390_codec_confs);
		पूर्ण अन्यथा
			broxton_audio_card.name = "cmlda7219max";

		क्रम (i = 0; i < ARRAY_SIZE(broxton_dais); i++) अणु
			/* MAXIM_CODEC is connected to SSP1. */
			अगर (!म_भेद(broxton_dais[i].codecs->dai_name,
					BXT_MAXIM_CODEC_DAI)) अणु
				broxton_dais[i].name = "SSP1-Codec";
				broxton_dais[i].cpus->dai_name = "SSP1 Pin";

				अगर (ctx->spkamp == SPKAMP_MAX98390) अणु
					broxton_dais[i].codecs = max98390_codec;
					broxton_dais[i].num_codecs = ARRAY_SIZE(max98390_codec);
					broxton_dais[i].dpcm_capture = 1;
				पूर्ण
			पूर्ण
			/* DIALOG_CODEC is connected to SSP0 */
			अन्यथा अगर (!म_भेद(broxton_dais[i].codecs->dai_name,
					BXT_DIALOG_CODEC_DAI)) अणु
				broxton_dais[i].name = "SSP0-Codec";
				broxton_dais[i].cpus->dai_name = "SSP0 Pin";
			पूर्ण
		पूर्ण
	पूर्ण

	/* override plaक्रमm name, अगर required */
	mach = pdev->dev.platक्रमm_data;
	platक्रमm_name = mach->mach_params.platक्रमm;

	ret = snd_soc_fixup_dai_links_platक्रमm_name(&broxton_audio_card,
						    platक्रमm_name);
	अगर (ret)
		वापस ret;

	ctx->common_hdmi_codec_drv = mach->mach_params.common_hdmi_codec_drv;

	वापस devm_snd_soc_रेजिस्टर_card(&pdev->dev, &broxton_audio_card);
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id bxt_board_ids[] = अणु
	अणु .name = "bxt_da7219_max98357a" पूर्ण,
	अणु .name = "glk_da7219_max98357a" पूर्ण,
	अणु .name = "cml_da7219_max98357a" पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver broxton_audio = अणु
	.probe = broxton_audio_probe,
	.driver = अणु
		.name = "bxt_da7219_max98357a",
		.pm = &snd_soc_pm_ops,
	पूर्ण,
	.id_table = bxt_board_ids,
पूर्ण;
module_platक्रमm_driver(broxton_audio)

/* Module inक्रमmation */
MODULE_DESCRIPTION("Audio Machine driver-DA7219 & MAX98357A in I2S mode");
MODULE_AUTHOR("Sathyanarayana Nujella <sathyanarayana.nujella@intel.com>");
MODULE_AUTHOR("Rohit Ainapure <rohit.m.ainapure@intel.com>");
MODULE_AUTHOR("Harsha Priya <harshapriya.n@intel.com>");
MODULE_AUTHOR("Conrad Cooke <conrad.cooke@intel.com>");
MODULE_AUTHOR("Naveen Manohar <naveen.m@intel.com>");
MODULE_AUTHOR("Mac Chiang <mac.chiang@intel.com>");
MODULE_AUTHOR("Brent Lu <brent.lu@intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:bxt_da7219_max98357a");
MODULE_ALIAS("platform:glk_da7219_max98357a");
MODULE_ALIAS("platform:cml_da7219_max98357a");
