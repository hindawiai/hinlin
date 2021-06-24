<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel Broxton-P I2S Machine Driver
 *
 * Copyright (C) 2014-2016, Intel Corporation. All rights reserved.
 *
 * Modअगरied from:
 *   Intel Skylake I2S Machine driver
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-acpi.h>
#समावेश <sound/jack.h>
#समावेश <sound/pcm_params.h>
#समावेश "../../codecs/hdac_hdmi.h"
#समावेश "../../codecs/rt298.h"
#समावेश "hda_dsp_common.h"

/* Headset jack detection DAPM pins */
अटल काष्ठा snd_soc_jack broxton_headset;
अटल काष्ठा snd_soc_jack broxton_hdmi[3];

काष्ठा bxt_hdmi_pcm अणु
	काष्ठा list_head head;
	काष्ठा snd_soc_dai *codec_dai;
	पूर्णांक device;
पूर्ण;

काष्ठा bxt_rt286_निजी अणु
	काष्ठा list_head hdmi_pcm_list;
	bool common_hdmi_codec_drv;
पूर्ण;

क्रमागत अणु
	BXT_DPCM_AUDIO_PB = 0,
	BXT_DPCM_AUDIO_CP,
	BXT_DPCM_AUDIO_REF_CP,
	BXT_DPCM_AUDIO_DMIC_CP,
	BXT_DPCM_AUDIO_HDMI1_PB,
	BXT_DPCM_AUDIO_HDMI2_PB,
	BXT_DPCM_AUDIO_HDMI3_PB,
पूर्ण;

अटल काष्ठा snd_soc_jack_pin broxton_headset_pins[] = अणु
	अणु
		.pin = "Mic Jack",
		.mask = SND_JACK_MICROPHONE,
	पूर्ण,
	अणु
		.pin = "Headphone Jack",
		.mask = SND_JACK_HEADPHONE,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new broxton_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Speaker"),
	SOC_DAPM_PIN_SWITCH("Headphone Jack"),
	SOC_DAPM_PIN_SWITCH("Mic Jack"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget broxton_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_SPK("Speaker", शून्य),
	SND_SOC_DAPM_MIC("Mic Jack", शून्य),
	SND_SOC_DAPM_MIC("DMIC2", शून्य),
	SND_SOC_DAPM_MIC("SoC DMIC", शून्य),
	SND_SOC_DAPM_SPK("HDMI1", शून्य),
	SND_SOC_DAPM_SPK("HDMI2", शून्य),
	SND_SOC_DAPM_SPK("HDMI3", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route broxton_rt298_map[] = अणु
	/* speaker */
	अणु"Speaker", शून्य, "SPOR"पूर्ण,
	अणु"Speaker", शून्य, "SPOL"पूर्ण,

	/* HP jack connectors - unknown अगर we have jack detect */
	अणु"Headphone Jack", शून्य, "HPO Pin"पूर्ण,

	/* other jacks */
	अणु"MIC1", शून्य, "Mic Jack"पूर्ण,

	/* digital mics */
	अणु"DMIC1 Pin", शून्य, "DMIC2"पूर्ण,
	अणु"DMic", शून्य, "SoC DMIC"पूर्ण,

	अणु"HDMI1", शून्य, "hif5-0 Output"पूर्ण,
	अणु"HDMI2", शून्य, "hif6-0 Output"पूर्ण,
	अणु"HDMI2", शून्य, "hif7-0 Output"पूर्ण,

	/* CODEC BE connections */
	अणु "AIF1 Playback", शून्य, "ssp5 Tx"पूर्ण,
	अणु "ssp5 Tx", शून्य, "codec0_out"पूर्ण,
	अणु "ssp5 Tx", शून्य, "codec1_out"पूर्ण,

	अणु "codec0_in", शून्य, "ssp5 Rx" पूर्ण,
	अणु "ssp5 Rx", शून्य, "AIF1 Capture" पूर्ण,

	अणु "dmic01_hifi", शून्य, "DMIC01 Rx" पूर्ण,
	अणु "DMIC01 Rx", शून्य, "Capture" पूर्ण,

	अणु "hifi3", शून्य, "iDisp3 Tx"पूर्ण,
	अणु "iDisp3 Tx", शून्य, "iDisp3_out"पूर्ण,
	अणु "hifi2", शून्य, "iDisp2 Tx"पूर्ण,
	अणु "iDisp2 Tx", शून्य, "iDisp2_out"पूर्ण,
	अणु "hifi1", शून्य, "iDisp1 Tx"पूर्ण,
	अणु "iDisp1 Tx", शून्य, "iDisp1_out"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route geminilake_rt298_map[] = अणु
	/* speaker */
	अणु"Speaker", शून्य, "SPOR"पूर्ण,
	अणु"Speaker", शून्य, "SPOL"पूर्ण,

	/* HP jack connectors - unknown अगर we have jack detect */
	अणु"Headphone Jack", शून्य, "HPO Pin"पूर्ण,

	/* other jacks */
	अणु"MIC1", शून्य, "Mic Jack"पूर्ण,

	/* digital mics */
	अणु"DMIC1 Pin", शून्य, "DMIC2"पूर्ण,
	अणु"DMic", शून्य, "SoC DMIC"पूर्ण,

	अणु"HDMI1", शून्य, "hif5-0 Output"पूर्ण,
	अणु"HDMI2", शून्य, "hif6-0 Output"पूर्ण,
	अणु"HDMI2", शून्य, "hif7-0 Output"पूर्ण,

	/* CODEC BE connections */
	अणु "AIF1 Playback", शून्य, "ssp2 Tx"पूर्ण,
	अणु "ssp2 Tx", शून्य, "codec0_out"पूर्ण,
	अणु "ssp2 Tx", शून्य, "codec1_out"पूर्ण,

	अणु "codec0_in", शून्य, "ssp2 Rx" पूर्ण,
	अणु "ssp2 Rx", शून्य, "AIF1 Capture" पूर्ण,

	अणु "dmic01_hifi", शून्य, "DMIC01 Rx" पूर्ण,
	अणु "DMIC01 Rx", शून्य, "Capture" पूर्ण,

	अणु "dmic_voice", शून्य, "DMIC16k Rx" पूर्ण,
	अणु "DMIC16k Rx", शून्य, "Capture" पूर्ण,

	अणु "hifi3", शून्य, "iDisp3 Tx"पूर्ण,
	अणु "iDisp3 Tx", शून्य, "iDisp3_out"पूर्ण,
	अणु "hifi2", शून्य, "iDisp2 Tx"पूर्ण,
	अणु "iDisp2 Tx", शून्य, "iDisp2_out"पूर्ण,
	अणु "hifi1", शून्य, "iDisp1 Tx"पूर्ण,
	अणु "iDisp1 Tx", शून्य, "iDisp1_out"पूर्ण,
पूर्ण;

अटल पूर्णांक broxton_rt298_fe_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_dapm_context *dapm;
	काष्ठा snd_soc_component *component = asoc_rtd_to_cpu(rtd, 0)->component;

	dapm = snd_soc_component_get_dapm(component);
	snd_soc_dapm_ignore_suspend(dapm, "Reference Capture");

	वापस 0;
पूर्ण

अटल पूर्णांक broxton_rt298_codec_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_component *component = asoc_rtd_to_codec(rtd, 0)->component;
	पूर्णांक ret = 0;

	ret = snd_soc_card_jack_new(rtd->card, "Headset",
		SND_JACK_HEADSET | SND_JACK_BTN_0,
		&broxton_headset,
		broxton_headset_pins, ARRAY_SIZE(broxton_headset_pins));

	अगर (ret)
		वापस ret;

	rt298_mic_detect(component, &broxton_headset);

	snd_soc_dapm_ignore_suspend(&rtd->card->dapm, "SoC DMIC");

	वापस 0;
पूर्ण

अटल पूर्णांक broxton_hdmi_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा bxt_rt286_निजी *ctx = snd_soc_card_get_drvdata(rtd->card);
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

अटल पूर्णांक broxton_ssp5_fixup(काष्ठा snd_soc_pcm_runसमय *rtd,
			काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_पूर्णांकerval *rate = hw_param_पूर्णांकerval(params,
					SNDRV_PCM_HW_PARAM_RATE);
	काष्ठा snd_पूर्णांकerval *chan = hw_param_पूर्णांकerval(params,
					SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा snd_mask *fmt = hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT);

	/* The ADSP will covert the FE rate to 48k, stereo */
	rate->min = rate->max = 48000;
	chan->min = chan->max = 2;

	/* set SSP5 to 24 bit */
	snd_mask_none(fmt);
	snd_mask_set_क्रमmat(fmt, SNDRV_PCM_FORMAT_S24_LE);

	वापस 0;
पूर्ण

अटल पूर्णांक broxton_rt298_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	पूर्णांक ret;

	ret = snd_soc_dai_set_sysclk(codec_dai, RT298_SCLK_S_PLL,
					19200000, SND_SOC_CLOCK_IN);
	अगर (ret < 0) अणु
		dev_err(rtd->dev, "can't set codec sysclk configuration\n");
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops broxton_rt298_ops = अणु
	.hw_params = broxton_rt298_hw_params,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक rates[] = अणु
	48000,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_rates = अणु
	.count = ARRAY_SIZE(rates),
	.list  = rates,
	.mask = 0,
पूर्ण;

अटल पूर्णांक broxton_dmic_fixup(काष्ठा snd_soc_pcm_runसमय *rtd,
				काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_पूर्णांकerval *chan = hw_param_पूर्णांकerval(params,
						SNDRV_PCM_HW_PARAM_CHANNELS);
	chan->min = chan->max = 4;

	वापस 0;
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक channels_dmic[] = अणु
	1, 2, 3, 4,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_dmic_channels = अणु
	.count = ARRAY_SIZE(channels_dmic),
	.list = channels_dmic,
	.mask = 0,
पूर्ण;

अटल पूर्णांक broxton_dmic_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	runसमय->hw.channels_max = 4;
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
					&स्थिरraपूर्णांकs_dmic_channels);

	वापस snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
				SNDRV_PCM_HW_PARAM_RATE, &स्थिरraपूर्णांकs_rates);
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops broxton_dmic_ops = अणु
	.startup = broxton_dmic_startup,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक channels[] = अणु
	2,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_channels = अणु
	.count = ARRAY_SIZE(channels),
	.list = channels,
	.mask = 0,
पूर्ण;

अटल पूर्णांक bxt_fe_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	/*
	 * on this platक्रमm क्रम PCM device we support:
	 *      48Khz
	 *      stereo
	 *	16-bit audio
	 */

	runसमय->hw.channels_max = 2;
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
				&स्थिरraपूर्णांकs_channels);

	runसमय->hw.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE;
	snd_pcm_hw_स्थिरraपूर्णांक_msbits(runसमय, 0, 16, 16);
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0,
				SNDRV_PCM_HW_PARAM_RATE, &स्थिरraपूर्णांकs_rates);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops broxton_rt286_fe_ops = अणु
	.startup = bxt_fe_startup,
पूर्ण;

SND_SOC_DAILINK_DEF(dummy,
	DAILINK_COMP_ARRAY(COMP_DUMMY()));

SND_SOC_DAILINK_DEF(प्रणाली,
	DAILINK_COMP_ARRAY(COMP_CPU("System Pin")));

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

SND_SOC_DAILINK_DEF(ssp5_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("SSP5 Pin")));
SND_SOC_DAILINK_DEF(ssp5_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("i2c-INT343A:00",
				      "rt298-aif1")));

SND_SOC_DAILINK_DEF(dmic_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("DMIC01 Pin")));

SND_SOC_DAILINK_DEF(dmic_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("dmic-codec",
				      "dmic-hifi")));

SND_SOC_DAILINK_DEF(dmic16k,
	DAILINK_COMP_ARRAY(COMP_CPU("DMIC16k Pin")));

SND_SOC_DAILINK_DEF(idisp1_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("iDisp1 Pin")));
SND_SOC_DAILINK_DEF(idisp1_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("ehdaudio0D2",
				      "intel-hdmi-hifi1")));

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

/* broxton digital audio पूर्णांकerface glue - connects codec <--> CPU */
अटल काष्ठा snd_soc_dai_link broxton_rt298_dais[] = अणु
	/* Front End DAI links */
	[BXT_DPCM_AUDIO_PB] =
	अणु
		.name = "Bxt Audio Port",
		.stream_name = "Audio",
		.nonatomic = 1,
		.dynamic = 1,
		.init = broxton_rt298_fe_init,
		.trigger = अणुSND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.dpcm_playback = 1,
		.ops = &broxton_rt286_fe_ops,
		SND_SOC_DAILINK_REG(प्रणाली, dummy, platक्रमm),
	पूर्ण,
	[BXT_DPCM_AUDIO_CP] =
	अणु
		.name = "Bxt Audio Capture Port",
		.stream_name = "Audio Record",
		.nonatomic = 1,
		.dynamic = 1,
		.trigger = अणुSND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.dpcm_capture = 1,
		.ops = &broxton_rt286_fe_ops,
		SND_SOC_DAILINK_REG(प्रणाली, dummy, platक्रमm),
	पूर्ण,
	[BXT_DPCM_AUDIO_REF_CP] =
	अणु
		.name = "Bxt Audio Reference cap",
		.stream_name = "refcap",
		.init = शून्य,
		.dpcm_capture = 1,
		.nonatomic = 1,
		.dynamic = 1,
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
		.init = broxton_rt298_codec_init,
		.dai_fmt = SND_SOC_DAIFMT_DSP_A | SND_SOC_DAIFMT_NB_NF |
						SND_SOC_DAIFMT_CBS_CFS,
		.ignore_pmकरोwn_समय = 1,
		.be_hw_params_fixup = broxton_ssp5_fixup,
		.ops = &broxton_rt298_ops,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(ssp5_pin, ssp5_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "dmic01",
		.id = 1,
		.be_hw_params_fixup = broxton_dmic_fixup,
		.ignore_suspend = 1,
		.dpcm_capture = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(dmic_pin, dmic_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "dmic16k",
		.id = 2,
		.be_hw_params_fixup = broxton_dmic_fixup,
		.ignore_suspend = 1,
		.dpcm_capture = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(dmic16k, dmic_codec, platक्रमm),
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
पूर्ण;

#घोषणा NAME_SIZE	32
अटल पूर्णांक bxt_card_late_probe(काष्ठा snd_soc_card *card)
अणु
	काष्ठा bxt_rt286_निजी *ctx = snd_soc_card_get_drvdata(card);
	काष्ठा bxt_hdmi_pcm *pcm;
	काष्ठा snd_soc_component *component = शून्य;
	पूर्णांक err, i = 0;
	अक्षर jack_name[NAME_SIZE];

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


/* broxton audio machine driver क्रम SPT + RT298S */
अटल काष्ठा snd_soc_card broxton_rt298 = अणु
	.name = "broxton-rt298",
	.owner = THIS_MODULE,
	.dai_link = broxton_rt298_dais,
	.num_links = ARRAY_SIZE(broxton_rt298_dais),
	.controls = broxton_controls,
	.num_controls = ARRAY_SIZE(broxton_controls),
	.dapm_widमाला_लो = broxton_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(broxton_widमाला_लो),
	.dapm_routes = broxton_rt298_map,
	.num_dapm_routes = ARRAY_SIZE(broxton_rt298_map),
	.fully_routed = true,
	.late_probe = bxt_card_late_probe,

पूर्ण;

अटल काष्ठा snd_soc_card geminilake_rt298 = अणु
	.name = "geminilake-rt298",
	.owner = THIS_MODULE,
	.dai_link = broxton_rt298_dais,
	.num_links = ARRAY_SIZE(broxton_rt298_dais),
	.controls = broxton_controls,
	.num_controls = ARRAY_SIZE(broxton_controls),
	.dapm_widमाला_लो = broxton_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(broxton_widमाला_लो),
	.dapm_routes = geminilake_rt298_map,
	.num_dapm_routes = ARRAY_SIZE(geminilake_rt298_map),
	.fully_routed = true,
	.late_probe = bxt_card_late_probe,
पूर्ण;

अटल पूर्णांक broxton_audio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bxt_rt286_निजी *ctx;
	काष्ठा snd_soc_card *card =
			(काष्ठा snd_soc_card *)pdev->id_entry->driver_data;
	काष्ठा snd_soc_acpi_mach *mach;
	स्थिर अक्षर *platक्रमm_name;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(broxton_rt298_dais); i++) अणु
		अगर (!म_भेदन(card->dai_link[i].codecs->name, "i2c-INT343A:00",
			     I2C_NAME_SIZE)) अणु
			अगर (!म_भेदन(card->name, "broxton-rt298",
				     PLATFORM_NAME_SIZE)) अणु
				card->dai_link[i].name = "SSP5-Codec";
				card->dai_link[i].cpus->dai_name = "SSP5 Pin";
			पूर्ण अन्यथा अगर (!म_भेदन(card->name, "geminilake-rt298",
					    PLATFORM_NAME_SIZE)) अणु
				card->dai_link[i].name = "SSP2-Codec";
				card->dai_link[i].cpus->dai_name = "SSP2 Pin";
			पूर्ण
		पूर्ण
	पूर्ण

	ctx = devm_kzalloc(&pdev->dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&ctx->hdmi_pcm_list);

	card->dev = &pdev->dev;
	snd_soc_card_set_drvdata(card, ctx);

	/* override plaक्रमm name, अगर required */
	mach = pdev->dev.platक्रमm_data;
	platक्रमm_name = mach->mach_params.platक्रमm;

	ret = snd_soc_fixup_dai_links_platक्रमm_name(card,
						    platक्रमm_name);
	अगर (ret)
		वापस ret;

	ctx->common_hdmi_codec_drv = mach->mach_params.common_hdmi_codec_drv;

	वापस devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id bxt_board_ids[] = अणु
	अणु .name = "bxt_alc298s_i2s", .driver_data =
				(अचिन्हित दीर्घ)&broxton_rt298 पूर्ण,
	अणु .name = "glk_alc298s_i2s", .driver_data =
				(अचिन्हित दीर्घ)&geminilake_rt298 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver broxton_audio = अणु
	.probe = broxton_audio_probe,
	.driver = अणु
		.name = "bxt_alc298s_i2s",
		.pm = &snd_soc_pm_ops,
	पूर्ण,
	.id_table = bxt_board_ids,
पूर्ण;
module_platक्रमm_driver(broxton_audio)

/* Module inक्रमmation */
MODULE_AUTHOR("Ramesh Babu <Ramesh.Babu@intel.com>");
MODULE_AUTHOR("Senthilnathan Veppur <senthilnathanx.veppur@intel.com>");
MODULE_DESCRIPTION("Intel SST Audio for Broxton");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:bxt_alc298s_i2s");
MODULE_ALIAS("platform:glk_alc298s_i2s");
