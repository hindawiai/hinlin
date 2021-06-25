<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright(c) 2018 Intel Corporation.

/*
 * Intel Geminilake I2S Machine Driver with MAX98357A & RT5682 Codecs
 *
 * Modअगरied from:
 *   Intel Apollolake I2S Machine driver
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
#समावेश "../../codecs/rt5682.h"
#समावेश "../../codecs/hdac_hdmi.h"
#समावेश "hda_dsp_common.h"

/* The platक्रमm घड़ी outमाला_दो 19.2Mhz घड़ी to codec as I2S MCLK */
#घोषणा GLK_PLAT_CLK_FREQ 19200000
#घोषणा RT5682_PLL_FREQ (48000 * 512)
#घोषणा GLK_REALTEK_CODEC_DAI "rt5682-aif1"
#घोषणा GLK_MAXIM_CODEC_DAI "HiFi"
#घोषणा MAXIM_DEV0_NAME "MX98357A:00"
#घोषणा DUAL_CHANNEL 2
#घोषणा QUAD_CHANNEL 4
#घोषणा NAME_SIZE 32

अटल काष्ठा snd_soc_jack geminilake_hdmi[3];

काष्ठा glk_hdmi_pcm अणु
	काष्ठा list_head head;
	काष्ठा snd_soc_dai *codec_dai;
	पूर्णांक device;
पूर्ण;

काष्ठा glk_card_निजी अणु
	काष्ठा snd_soc_jack geminilake_headset;
	काष्ठा list_head hdmi_pcm_list;
	bool common_hdmi_codec_drv;
पूर्ण;

क्रमागत अणु
	GLK_DPCM_AUDIO_PB = 0,
	GLK_DPCM_AUDIO_CP,
	GLK_DPCM_AUDIO_HS_PB,
	GLK_DPCM_AUDIO_ECHO_REF_CP,
	GLK_DPCM_AUDIO_REF_CP,
	GLK_DPCM_AUDIO_DMIC_CP,
	GLK_DPCM_AUDIO_HDMI1_PB,
	GLK_DPCM_AUDIO_HDMI2_PB,
	GLK_DPCM_AUDIO_HDMI3_PB,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new geminilake_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Headphone Jack"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Spk"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget geminilake_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_SPK("Spk", शून्य),
	SND_SOC_DAPM_MIC("SoC DMIC", शून्य),
	SND_SOC_DAPM_SPK("HDMI1", शून्य),
	SND_SOC_DAPM_SPK("HDMI2", शून्य),
	SND_SOC_DAPM_SPK("HDMI3", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route geminilake_map[] = अणु
	/* HP jack connectors - unknown अगर we have jack detection */
	अणु "Headphone Jack", शून्य, "HPOL" पूर्ण,
	अणु "Headphone Jack", शून्य, "HPOR" पूर्ण,

	/* speaker */
	अणु "Spk", शून्य, "Speaker" पूर्ण,

	/* other jacks */
	अणु "IN1P", शून्य, "Headset Mic" पूर्ण,

	/* digital mics */
	अणु "DMic", शून्य, "SoC DMIC" पूर्ण,

	/* CODEC BE connections */
	अणु "HiFi Playback", शून्य, "ssp1 Tx" पूर्ण,
	अणु "ssp1 Tx", शून्य, "codec0_out" पूर्ण,

	अणु "AIF1 Playback", शून्य, "ssp2 Tx" पूर्ण,
	अणु "ssp2 Tx", शून्य, "codec1_out" पूर्ण,

	अणु "codec0_in", शून्य, "ssp2 Rx" पूर्ण,
	अणु "ssp2 Rx", शून्य, "AIF1 Capture" पूर्ण,

	अणु "HDMI1", शून्य, "hif5-0 Output" पूर्ण,
	अणु "HDMI2", शून्य, "hif6-0 Output" पूर्ण,
	अणु "HDMI2", शून्य, "hif7-0 Output" पूर्ण,

	अणु "hifi3", शून्य, "iDisp3 Tx" पूर्ण,
	अणु "iDisp3 Tx", शून्य, "iDisp3_out" पूर्ण,
	अणु "hifi2", शून्य, "iDisp2 Tx" पूर्ण,
	अणु "iDisp2 Tx", शून्य, "iDisp2_out" पूर्ण,
	अणु "hifi1", शून्य, "iDisp1 Tx" पूर्ण,
	अणु "iDisp1 Tx", शून्य, "iDisp1_out" पूर्ण,

	/* DMIC */
	अणु "dmic01_hifi", शून्य, "DMIC01 Rx" पूर्ण,
	अणु "DMIC01 Rx", शून्य, "DMIC AIF" पूर्ण,
पूर्ण;

अटल पूर्णांक geminilake_ssp_fixup(काष्ठा snd_soc_pcm_runसमय *rtd,
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

अटल पूर्णांक geminilake_rt5682_codec_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा glk_card_निजी *ctx = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा snd_soc_component *component = asoc_rtd_to_codec(rtd, 0)->component;
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_jack *jack;
	पूर्णांक ret;

	ret = snd_soc_dai_set_pll(codec_dai, 0, RT5682_PLL1_S_MCLK,
					GLK_PLAT_CLK_FREQ, RT5682_PLL_FREQ);
	अगर (ret < 0) अणु
		dev_err(rtd->dev, "can't set codec pll: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Configure sysclk क्रम codec */
	ret = snd_soc_dai_set_sysclk(codec_dai, RT5682_SCLK_S_PLL1,
					RT5682_PLL_FREQ, SND_SOC_CLOCK_IN);
	अगर (ret < 0)
		dev_err(rtd->dev, "snd_soc_dai_set_sysclk err = %d\n", ret);

	/*
	 * Headset buttons map to the google Reference headset.
	 * These can be configured by userspace.
	 */
	ret = snd_soc_card_jack_new(rtd->card, "Headset Jack",
			SND_JACK_HEADSET | SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			SND_JACK_BTN_2 | SND_JACK_BTN_3 | SND_JACK_LINEOUT,
			&ctx->geminilake_headset, शून्य, 0);
	अगर (ret) अणु
		dev_err(rtd->dev, "Headset Jack creation failed: %d\n", ret);
		वापस ret;
	पूर्ण

	jack = &ctx->geminilake_headset;

	snd_jack_set_key(jack->jack, SND_JACK_BTN_0, KEY_PLAYPAUSE);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_1, KEY_VOICECOMMAND);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_2, KEY_VOLUMEUP);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_3, KEY_VOLUMEDOWN);

	ret = snd_soc_component_set_jack(component, jack, शून्य);

	अगर (ret) अणु
		dev_err(rtd->dev, "Headset Jack call-back failed: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण;

अटल पूर्णांक geminilake_rt5682_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	पूर्णांक ret;

	/* Set valid biपंचांगask & configuration क्रम I2S in 24 bit */
	ret = snd_soc_dai_set_tdm_slot(codec_dai, 0x0, 0x0, 2, 24);
	अगर (ret < 0) अणु
		dev_err(rtd->dev, "set TDM slot err:%d\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा snd_soc_ops geminilake_rt5682_ops = अणु
	.hw_params = geminilake_rt5682_hw_params,
पूर्ण;

अटल पूर्णांक geminilake_hdmi_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा glk_card_निजी *ctx = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा snd_soc_dai *dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा glk_hdmi_pcm *pcm;

	pcm = devm_kzalloc(rtd->card->dev, माप(*pcm), GFP_KERNEL);
	अगर (!pcm)
		वापस -ENOMEM;

	pcm->device = GLK_DPCM_AUDIO_HDMI1_PB + dai->id;
	pcm->codec_dai = dai;

	list_add_tail(&pcm->head, &ctx->hdmi_pcm_list);

	वापस 0;
पूर्ण

अटल पूर्णांक geminilake_rt5682_fe_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_component *component = asoc_rtd_to_cpu(rtd, 0)->component;
	काष्ठा snd_soc_dapm_context *dapm;
	पूर्णांक ret;

	dapm = snd_soc_component_get_dapm(component);
	ret = snd_soc_dapm_ignore_suspend(dapm, "Reference Capture");
	अगर (ret) अणु
		dev_err(rtd->dev, "Ref Cap ignore suspend failed %d\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक rates[] = अणु
	48000,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_rates = अणु
	.count = ARRAY_SIZE(rates),
	.list  = rates,
	.mask = 0,
पूर्ण;

अटल अचिन्हित पूर्णांक channels_quad[] = अणु
	QUAD_CHANNEL,
पूर्ण;

अटल काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_channels_quad = अणु
	.count = ARRAY_SIZE(channels_quad),
	.list = channels_quad,
	.mask = 0,
पूर्ण;

अटल पूर्णांक geminilake_dmic_fixup(काष्ठा snd_soc_pcm_runसमय *rtd,
		काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_पूर्णांकerval *chan = hw_param_पूर्णांकerval(params,
				SNDRV_PCM_HW_PARAM_CHANNELS);

	/*
	 * set BE channel स्थिरraपूर्णांक as user FE channels
	 */
	chan->min = chan->max = 4;

	वापस 0;
पूर्ण

अटल पूर्णांक geminilake_dmic_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	runसमय->hw.channels_min = runसमय->hw.channels_max = QUAD_CHANNEL;
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
			&स्थिरraपूर्णांकs_channels_quad);

	वापस snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
			SNDRV_PCM_HW_PARAM_RATE, &स्थिरraपूर्णांकs_rates);
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops geminilake_dmic_ops = अणु
	.startup = geminilake_dmic_startup,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक rates_16000[] = अणु
	16000,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_16000 = अणु
	.count = ARRAY_SIZE(rates_16000),
	.list  = rates_16000,
पूर्ण;

अटल पूर्णांक geminilake_refcap_startup(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
				SNDRV_PCM_HW_PARAM_RATE,
				&स्थिरraपूर्णांकs_16000);
पूर्ण;

अटल स्थिर काष्ठा snd_soc_ops geminilake_refcap_ops = अणु
	.startup = geminilake_refcap_startup,
पूर्ण;

SND_SOC_DAILINK_DEF(dummy,
	DAILINK_COMP_ARRAY(COMP_DUMMY()));

SND_SOC_DAILINK_DEF(प्रणाली,
	DAILINK_COMP_ARRAY(COMP_CPU("System Pin")));

SND_SOC_DAILINK_DEF(प्रणाली2,
	DAILINK_COMP_ARRAY(COMP_CPU("System Pin2")));

SND_SOC_DAILINK_DEF(echoref,
	DAILINK_COMP_ARRAY(COMP_CPU("Echoref Pin")));

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

SND_SOC_DAILINK_DEF(ssp1_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("SSP1 Pin")));
SND_SOC_DAILINK_DEF(ssp1_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC(MAXIM_DEV0_NAME,
				      GLK_MAXIM_CODEC_DAI)));

SND_SOC_DAILINK_DEF(ssp2_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("SSP2 Pin")));
SND_SOC_DAILINK_DEF(ssp2_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("i2c-10EC5682:00",
				      GLK_REALTEK_CODEC_DAI)));

SND_SOC_DAILINK_DEF(dmic_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("DMIC01 Pin")));
SND_SOC_DAILINK_DEF(dmic_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("dmic-codec", "dmic-hifi")));

SND_SOC_DAILINK_DEF(idisp1_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("iDisp1 Pin")));
SND_SOC_DAILINK_DEF(idisp1_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("ehdaudio0D2", "intel-hdmi-hifi1")));

SND_SOC_DAILINK_DEF(idisp2_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("iDisp2 Pin")));
SND_SOC_DAILINK_DEF(idisp2_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("ehdaudio0D2", "intel-hdmi-hifi2")));

SND_SOC_DAILINK_DEF(idisp3_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("iDisp3 Pin")));
SND_SOC_DAILINK_DEF(idisp3_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("ehdaudio0D2", "intel-hdmi-hifi3")));

SND_SOC_DAILINK_DEF(platक्रमm,
	DAILINK_COMP_ARRAY(COMP_PLATFORM("0000:00:0e.0")));

/* geminilake digital audio पूर्णांकerface glue - connects codec <--> CPU */
अटल काष्ठा snd_soc_dai_link geminilake_dais[] = अणु
	/* Front End DAI links */
	[GLK_DPCM_AUDIO_PB] = अणु
		.name = "Glk Audio Port",
		.stream_name = "Audio",
		.dynamic = 1,
		.nonatomic = 1,
		.init = geminilake_rt5682_fe_init,
		.trigger = अणु
			SND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(प्रणाली, dummy, platक्रमm),
	पूर्ण,
	[GLK_DPCM_AUDIO_CP] = अणु
		.name = "Glk Audio Capture Port",
		.stream_name = "Audio Record",
		.dynamic = 1,
		.nonatomic = 1,
		.trigger = अणु
			SND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(प्रणाली, dummy, platक्रमm),
	पूर्ण,
	[GLK_DPCM_AUDIO_HS_PB] = अणु
		.name = "Glk Audio Headset Playback",
		.stream_name = "Headset Audio",
		.dpcm_playback = 1,
		.nonatomic = 1,
		.dynamic = 1,
		SND_SOC_DAILINK_REG(प्रणाली2, dummy, platक्रमm),
	पूर्ण,
	[GLK_DPCM_AUDIO_ECHO_REF_CP] = अणु
		.name = "Glk Audio Echo Reference cap",
		.stream_name = "Echoreference Capture",
		.init = शून्य,
		.dpcm_capture = 1,
		.nonatomic = 1,
		.dynamic = 1,
		SND_SOC_DAILINK_REG(echoref, dummy, platक्रमm),
	पूर्ण,
	[GLK_DPCM_AUDIO_REF_CP] = अणु
		.name = "Glk Audio Reference cap",
		.stream_name = "Refcap",
		.init = शून्य,
		.dpcm_capture = 1,
		.nonatomic = 1,
		.dynamic = 1,
		.ops = &geminilake_refcap_ops,
		SND_SOC_DAILINK_REG(reference, dummy, platक्रमm),
	पूर्ण,
	[GLK_DPCM_AUDIO_DMIC_CP] = अणु
		.name = "Glk Audio DMIC cap",
		.stream_name = "dmiccap",
		.init = शून्य,
		.dpcm_capture = 1,
		.nonatomic = 1,
		.dynamic = 1,
		.ops = &geminilake_dmic_ops,
		SND_SOC_DAILINK_REG(dmic, dummy, platक्रमm),
	पूर्ण,
	[GLK_DPCM_AUDIO_HDMI1_PB] = अणु
		.name = "Glk HDMI Port1",
		.stream_name = "Hdmi1",
		.dpcm_playback = 1,
		.init = शून्य,
		.trigger = अणु
			SND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.nonatomic = 1,
		.dynamic = 1,
		SND_SOC_DAILINK_REG(hdmi1, dummy, platक्रमm),
	पूर्ण,
	[GLK_DPCM_AUDIO_HDMI2_PB] =	अणु
		.name = "Glk HDMI Port2",
		.stream_name = "Hdmi2",
		.dpcm_playback = 1,
		.init = शून्य,
		.trigger = अणु
			SND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.nonatomic = 1,
		.dynamic = 1,
		SND_SOC_DAILINK_REG(hdmi2, dummy, platक्रमm),
	पूर्ण,
	[GLK_DPCM_AUDIO_HDMI3_PB] =	अणु
		.name = "Glk HDMI Port3",
		.stream_name = "Hdmi3",
		.trigger = अणु
			SND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.dpcm_playback = 1,
		.init = शून्य,
		.nonatomic = 1,
		.dynamic = 1,
		SND_SOC_DAILINK_REG(hdmi3, dummy, platक्रमm),
	पूर्ण,
	/* Back End DAI links */
	अणु
		/* SSP1 - Codec */
		.name = "SSP1-Codec",
		.id = 0,
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S |
			SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBS_CFS,
		.ignore_pmकरोwn_समय = 1,
		.be_hw_params_fixup = geminilake_ssp_fixup,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(ssp1_pin, ssp1_codec, platक्रमm),
	पूर्ण,
	अणु
		/* SSP2 - Codec */
		.name = "SSP2-Codec",
		.id = 1,
		.no_pcm = 1,
		.init = geminilake_rt5682_codec_init,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBS_CFS,
		.ignore_pmकरोwn_समय = 1,
		.be_hw_params_fixup = geminilake_ssp_fixup,
		.ops = &geminilake_rt5682_ops,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(ssp2_pin, ssp2_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "dmic01",
		.id = 2,
		.ignore_suspend = 1,
		.be_hw_params_fixup = geminilake_dmic_fixup,
		.dpcm_capture = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(dmic_pin, dmic_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "iDisp1",
		.id = 3,
		.init = geminilake_hdmi_init,
		.dpcm_playback = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(idisp1_pin, idisp1_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "iDisp2",
		.id = 4,
		.init = geminilake_hdmi_init,
		.dpcm_playback = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(idisp2_pin, idisp2_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "iDisp3",
		.id = 5,
		.init = geminilake_hdmi_init,
		.dpcm_playback = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(idisp3_pin, idisp3_codec, platक्रमm),
	पूर्ण,
पूर्ण;

अटल पूर्णांक glk_card_late_probe(काष्ठा snd_soc_card *card)
अणु
	काष्ठा glk_card_निजी *ctx = snd_soc_card_get_drvdata(card);
	काष्ठा snd_soc_component *component = शून्य;
	अक्षर jack_name[NAME_SIZE];
	काष्ठा glk_hdmi_pcm *pcm;
	पूर्णांक err;
	पूर्णांक i = 0;

	अगर (list_empty(&ctx->hdmi_pcm_list))
		वापस -EINVAL;

	अगर (ctx->common_hdmi_codec_drv) अणु
		pcm = list_first_entry(&ctx->hdmi_pcm_list, काष्ठा glk_hdmi_pcm,
				       head);
		component = pcm->codec_dai->component;
		वापस hda_dsp_hdmi_build_controls(card, component);
	पूर्ण

	list_क्रम_each_entry(pcm, &ctx->hdmi_pcm_list, head) अणु
		component = pcm->codec_dai->component;
		snम_लिखो(jack_name, माप(jack_name),
			"HDMI/DP, pcm=%d Jack", pcm->device);
		err = snd_soc_card_jack_new(card, jack_name,
					SND_JACK_AVOUT, &geminilake_hdmi[i],
					शून्य, 0);

		अगर (err)
			वापस err;

		err = hdac_hdmi_jack_init(pcm->codec_dai, pcm->device,
						&geminilake_hdmi[i]);
		अगर (err < 0)
			वापस err;

		i++;
	पूर्ण

	वापस hdac_hdmi_jack_port_init(component, &card->dapm);
पूर्ण

/* geminilake audio machine driver क्रम SPT + RT5682 */
अटल काष्ठा snd_soc_card glk_audio_card_rt5682_m98357a = अणु
	.name = "glkrt5682max",
	.owner = THIS_MODULE,
	.dai_link = geminilake_dais,
	.num_links = ARRAY_SIZE(geminilake_dais),
	.controls = geminilake_controls,
	.num_controls = ARRAY_SIZE(geminilake_controls),
	.dapm_widमाला_लो = geminilake_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(geminilake_widमाला_लो),
	.dapm_routes = geminilake_map,
	.num_dapm_routes = ARRAY_SIZE(geminilake_map),
	.fully_routed = true,
	.late_probe = glk_card_late_probe,
पूर्ण;

अटल पूर्णांक geminilake_audio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा glk_card_निजी *ctx;
	काष्ठा snd_soc_acpi_mach *mach;
	स्थिर अक्षर *platक्रमm_name;
	काष्ठा snd_soc_card *card;
	पूर्णांक ret;

	ctx = devm_kzalloc(&pdev->dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&ctx->hdmi_pcm_list);

	card = &glk_audio_card_rt5682_m98357a;
	card->dev = &pdev->dev;
	snd_soc_card_set_drvdata(card, ctx);

	/* override plaक्रमm name, अगर required */
	mach = pdev->dev.platक्रमm_data;
	platक्रमm_name = mach->mach_params.platक्रमm;

	ret = snd_soc_fixup_dai_links_platक्रमm_name(card, platक्रमm_name);
	अगर (ret)
		वापस ret;

	ctx->common_hdmi_codec_drv = mach->mach_params.common_hdmi_codec_drv;

	वापस devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id glk_board_ids[] = अणु
	अणु
		.name = "glk_rt5682_max98357a",
		.driver_data =
			(kernel_uदीर्घ_t)&glk_audio_card_rt5682_m98357a,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver geminilake_audio = अणु
	.probe = geminilake_audio_probe,
	.driver = अणु
		.name = "glk_rt5682_max98357a",
		.pm = &snd_soc_pm_ops,
	पूर्ण,
	.id_table = glk_board_ids,
पूर्ण;
module_platक्रमm_driver(geminilake_audio)

/* Module inक्रमmation */
MODULE_DESCRIPTION("Geminilake Audio Machine driver-RT5682 & MAX98357A in I2S mode");
MODULE_AUTHOR("Naveen Manohar <naveen.m@intel.com>");
MODULE_AUTHOR("Harsha Priya <harshapriya.n@intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:glk_rt5682_max98357a");
