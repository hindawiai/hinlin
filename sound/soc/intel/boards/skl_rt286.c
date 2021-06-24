<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel Skylake I2S Machine Driver
 *
 * Copyright (C) 2014-2015, Intel Corporation. All rights reserved.
 *
 * Modअगरied from:
 *   Intel Broadwell Wildcatpoपूर्णांक SST Audio
 *
 *   Copyright (C) 2013, Intel Corporation. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/jack.h>
#समावेश <sound/pcm_params.h>
#समावेश "../../codecs/rt286.h"
#समावेश "../../codecs/hdac_hdmi.h"

अटल काष्ठा snd_soc_jack skylake_headset;
अटल काष्ठा snd_soc_jack skylake_hdmi[3];

काष्ठा skl_hdmi_pcm अणु
	काष्ठा list_head head;
	काष्ठा snd_soc_dai *codec_dai;
	पूर्णांक device;
पूर्ण;

काष्ठा skl_rt286_निजी अणु
	काष्ठा list_head hdmi_pcm_list;
पूर्ण;

क्रमागत अणु
	SKL_DPCM_AUDIO_PB = 0,
	SKL_DPCM_AUDIO_DB_PB,
	SKL_DPCM_AUDIO_CP,
	SKL_DPCM_AUDIO_REF_CP,
	SKL_DPCM_AUDIO_DMIC_CP,
	SKL_DPCM_AUDIO_HDMI1_PB,
	SKL_DPCM_AUDIO_HDMI2_PB,
	SKL_DPCM_AUDIO_HDMI3_PB,
पूर्ण;

/* Headset jack detection DAPM pins */
अटल काष्ठा snd_soc_jack_pin skylake_headset_pins[] = अणु
	अणु
		.pin = "Mic Jack",
		.mask = SND_JACK_MICROPHONE,
	पूर्ण,
	अणु
		.pin = "Headphone Jack",
		.mask = SND_JACK_HEADPHONE,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new skylake_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Speaker"),
	SOC_DAPM_PIN_SWITCH("Headphone Jack"),
	SOC_DAPM_PIN_SWITCH("Mic Jack"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget skylake_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_SPK("Speaker", शून्य),
	SND_SOC_DAPM_MIC("Mic Jack", शून्य),
	SND_SOC_DAPM_MIC("DMIC2", शून्य),
	SND_SOC_DAPM_MIC("SoC DMIC", शून्य),
	SND_SOC_DAPM_SPK("HDMI1", शून्य),
	SND_SOC_DAPM_SPK("HDMI2", शून्य),
	SND_SOC_DAPM_SPK("HDMI3", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route skylake_rt286_map[] = अणु
	/* speaker */
	अणु"Speaker", शून्य, "SPOR"पूर्ण,
	अणु"Speaker", शून्य, "SPOL"पूर्ण,

	/* HP jack connectors - unknown अगर we have jack deteck */
	अणु"Headphone Jack", शून्य, "HPO Pin"पूर्ण,

	/* other jacks */
	अणु"MIC1", शून्य, "Mic Jack"पूर्ण,

	/* digital mics */
	अणु"DMIC1 Pin", शून्य, "DMIC2"पूर्ण,
	अणु"DMic", शून्य, "SoC DMIC"पूर्ण,

	/* CODEC BE connections */
	अणु "AIF1 Playback", शून्य, "ssp0 Tx"पूर्ण,
	अणु "ssp0 Tx", शून्य, "codec0_out"पूर्ण,
	अणु "ssp0 Tx", शून्य, "codec1_out"पूर्ण,

	अणु "codec0_in", शून्य, "ssp0 Rx" पूर्ण,
	अणु "codec1_in", शून्य, "ssp0 Rx" पूर्ण,
	अणु "ssp0 Rx", शून्य, "AIF1 Capture" पूर्ण,

	अणु "dmic01_hifi", शून्य, "DMIC01 Rx" पूर्ण,
	अणु "DMIC01 Rx", शून्य, "DMIC AIF" पूर्ण,

	अणु "hifi3", शून्य, "iDisp3 Tx"पूर्ण,
	अणु "iDisp3 Tx", शून्य, "iDisp3_out"पूर्ण,
	अणु "hifi2", शून्य, "iDisp2 Tx"पूर्ण,
	अणु "iDisp2 Tx", शून्य, "iDisp2_out"पूर्ण,
	अणु "hifi1", शून्य, "iDisp1 Tx"पूर्ण,
	अणु "iDisp1 Tx", शून्य, "iDisp1_out"पूर्ण,

पूर्ण;

अटल पूर्णांक skylake_rt286_fe_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_dapm_context *dapm;
	काष्ठा snd_soc_component *component = asoc_rtd_to_cpu(rtd, 0)->component;

	dapm = snd_soc_component_get_dapm(component);
	snd_soc_dapm_ignore_suspend(dapm, "Reference Capture");

	वापस 0;
पूर्ण

अटल पूर्णांक skylake_rt286_codec_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_component *component = asoc_rtd_to_codec(rtd, 0)->component;
	पूर्णांक ret;

	ret = snd_soc_card_jack_new(rtd->card, "Headset",
		SND_JACK_HEADSET | SND_JACK_BTN_0,
		&skylake_headset,
		skylake_headset_pins, ARRAY_SIZE(skylake_headset_pins));

	अगर (ret)
		वापस ret;

	rt286_mic_detect(component, &skylake_headset);

	snd_soc_dapm_ignore_suspend(&rtd->card->dapm, "SoC DMIC");

	वापस 0;
पूर्ण

अटल पूर्णांक skylake_hdmi_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा skl_rt286_निजी *ctx = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा snd_soc_dai *dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा skl_hdmi_pcm *pcm;

	pcm = devm_kzalloc(rtd->card->dev, माप(*pcm), GFP_KERNEL);
	अगर (!pcm)
		वापस -ENOMEM;

	pcm->device = SKL_DPCM_AUDIO_HDMI1_PB + dai->id;
	pcm->codec_dai = dai;

	list_add_tail(&pcm->head, &ctx->hdmi_pcm_list);

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
	2,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_channels = अणु
	.count = ARRAY_SIZE(channels),
	.list = channels,
	.mask = 0,
पूर्ण;

अटल पूर्णांक skl_fe_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	/*
	 * on this platक्रमm क्रम PCM device we support,
	 *	48Khz
	 *	stereo
	 *	16 bit audio
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

अटल स्थिर काष्ठा snd_soc_ops skylake_rt286_fe_ops = अणु
	.startup = skl_fe_startup,
पूर्ण;

अटल पूर्णांक skylake_ssp0_fixup(काष्ठा snd_soc_pcm_runसमय *rtd,
			काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_पूर्णांकerval *rate = hw_param_पूर्णांकerval(params,
			SNDRV_PCM_HW_PARAM_RATE);
	काष्ठा snd_पूर्णांकerval *chan = hw_param_पूर्णांकerval(params,
						SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा snd_mask *fmt = hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT);

	/* The output is 48KHz, stereo, 16bits */
	rate->min = rate->max = 48000;
	chan->min = chan->max = 2;

	/* set SSP0 to 24 bit */
	snd_mask_none(fmt);
	snd_mask_set_क्रमmat(fmt, SNDRV_PCM_FORMAT_S24_LE);
	वापस 0;
पूर्ण

अटल पूर्णांक skylake_rt286_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	पूर्णांक ret;

	ret = snd_soc_dai_set_sysclk(codec_dai, RT286_SCLK_S_PLL, 24000000,
		SND_SOC_CLOCK_IN);
	अगर (ret < 0)
		dev_err(rtd->dev, "set codec sysclk failed: %d\n", ret);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops skylake_rt286_ops = अणु
	.hw_params = skylake_rt286_hw_params,
पूर्ण;

अटल पूर्णांक skylake_dmic_fixup(काष्ठा snd_soc_pcm_runसमय *rtd,
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

अटल स्थिर अचिन्हित पूर्णांक channels_dmic[] = अणु
	2, 4,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_dmic_channels = अणु
	.count = ARRAY_SIZE(channels_dmic),
	.list = channels_dmic,
	.mask = 0,
पूर्ण;

अटल पूर्णांक skylake_dmic_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	runसमय->hw.channels_max = 4;
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
					   &स्थिरraपूर्णांकs_dmic_channels);

	वापस snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
			SNDRV_PCM_HW_PARAM_RATE, &स्थिरraपूर्णांकs_rates);
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops skylake_dmic_ops = अणु
	.startup = skylake_dmic_startup,
पूर्ण;

SND_SOC_DAILINK_DEF(dummy,
	DAILINK_COMP_ARRAY(COMP_DUMMY()));

SND_SOC_DAILINK_DEF(प्रणाली,
	DAILINK_COMP_ARRAY(COMP_CPU("System Pin")));

SND_SOC_DAILINK_DEF(deepbuffer,
	DAILINK_COMP_ARRAY(COMP_CPU("Deepbuffer Pin")));

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

SND_SOC_DAILINK_DEF(ssp0_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("SSP0 Pin")));
SND_SOC_DAILINK_DEF(ssp0_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("i2c-INT343A:00", "rt286-aif1")));

SND_SOC_DAILINK_DEF(dmic01_pin,
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
	DAILINK_COMP_ARRAY(COMP_PLATFORM("0000:00:1f.3")));

/* skylake digital audio पूर्णांकerface glue - connects codec <--> CPU */
अटल काष्ठा snd_soc_dai_link skylake_rt286_dais[] = अणु
	/* Front End DAI links */
	[SKL_DPCM_AUDIO_PB] = अणु
		.name = "Skl Audio Port",
		.stream_name = "Audio",
		.nonatomic = 1,
		.dynamic = 1,
		.init = skylake_rt286_fe_init,
		.trigger = अणु
			SND_SOC_DPCM_TRIGGER_POST,
			SND_SOC_DPCM_TRIGGER_POST
		पूर्ण,
		.dpcm_playback = 1,
		.ops = &skylake_rt286_fe_ops,
		SND_SOC_DAILINK_REG(प्रणाली, dummy, platक्रमm),
	पूर्ण,
	[SKL_DPCM_AUDIO_DB_PB] = अणु
		.name = "Skl Deepbuffer Port",
		.stream_name = "Deep Buffer Audio",
		.nonatomic = 1,
		.dynamic = 1,
		.trigger = अणु
			SND_SOC_DPCM_TRIGGER_POST,
			SND_SOC_DPCM_TRIGGER_POST
		पूर्ण,
		.dpcm_playback = 1,
		.ops = &skylake_rt286_fe_ops,
		SND_SOC_DAILINK_REG(deepbuffer, dummy, platक्रमm),
	पूर्ण,
	[SKL_DPCM_AUDIO_CP] = अणु
		.name = "Skl Audio Capture Port",
		.stream_name = "Audio Record",
		.nonatomic = 1,
		.dynamic = 1,
		.trigger = अणु
			SND_SOC_DPCM_TRIGGER_POST,
			SND_SOC_DPCM_TRIGGER_POST
		पूर्ण,
		.dpcm_capture = 1,
		.ops = &skylake_rt286_fe_ops,
		SND_SOC_DAILINK_REG(प्रणाली, dummy, platक्रमm),
	पूर्ण,
	[SKL_DPCM_AUDIO_REF_CP] = अणु
		.name = "Skl Audio Reference cap",
		.stream_name = "refcap",
		.init = शून्य,
		.dpcm_capture = 1,
		.nonatomic = 1,
		.dynamic = 1,
		SND_SOC_DAILINK_REG(reference, dummy, platक्रमm),
	पूर्ण,
	[SKL_DPCM_AUDIO_DMIC_CP] = अणु
		.name = "Skl Audio DMIC cap",
		.stream_name = "dmiccap",
		.init = शून्य,
		.dpcm_capture = 1,
		.nonatomic = 1,
		.dynamic = 1,
		.ops = &skylake_dmic_ops,
		SND_SOC_DAILINK_REG(dmic, dummy, platक्रमm),
	पूर्ण,
	[SKL_DPCM_AUDIO_HDMI1_PB] = अणु
		.name = "Skl HDMI Port1",
		.stream_name = "Hdmi1",
		.dpcm_playback = 1,
		.init = शून्य,
		.nonatomic = 1,
		.dynamic = 1,
		SND_SOC_DAILINK_REG(hdmi1, dummy, platक्रमm),
	पूर्ण,
	[SKL_DPCM_AUDIO_HDMI2_PB] = अणु
		.name = "Skl HDMI Port2",
		.stream_name = "Hdmi2",
		.dpcm_playback = 1,
		.init = शून्य,
		.nonatomic = 1,
		.dynamic = 1,
		SND_SOC_DAILINK_REG(hdmi2, dummy, platक्रमm),
	पूर्ण,
	[SKL_DPCM_AUDIO_HDMI3_PB] = अणु
		.name = "Skl HDMI Port3",
		.stream_name = "Hdmi3",
		.dpcm_playback = 1,
		.init = शून्य,
		.nonatomic = 1,
		.dynamic = 1,
		SND_SOC_DAILINK_REG(hdmi3, dummy, platक्रमm),
	पूर्ण,

	/* Back End DAI links */
	अणु
		/* SSP0 - Codec */
		.name = "SSP0-Codec",
		.id = 0,
		.no_pcm = 1,
		.init = skylake_rt286_codec_init,
		.dai_fmt = SND_SOC_DAIFMT_I2S |
			SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBS_CFS,
		.ignore_pmकरोwn_समय = 1,
		.be_hw_params_fixup = skylake_ssp0_fixup,
		.ops = &skylake_rt286_ops,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(ssp0_pin, ssp0_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "dmic01",
		.id = 1,
		.be_hw_params_fixup = skylake_dmic_fixup,
		.ignore_suspend = 1,
		.dpcm_capture = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(dmic01_pin, dmic_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "iDisp1",
		.id = 2,
		.init = skylake_hdmi_init,
		.dpcm_playback = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(idisp1_pin, idisp1_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "iDisp2",
		.id = 3,
		.init = skylake_hdmi_init,
		.dpcm_playback = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(idisp2_pin, idisp2_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "iDisp3",
		.id = 4,
		.init = skylake_hdmi_init,
		.dpcm_playback = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(idisp3_pin, idisp3_codec, platक्रमm),
	पूर्ण,
पूर्ण;

#घोषणा NAME_SIZE	32
अटल पूर्णांक skylake_card_late_probe(काष्ठा snd_soc_card *card)
अणु
	काष्ठा skl_rt286_निजी *ctx = snd_soc_card_get_drvdata(card);
	काष्ठा skl_hdmi_pcm *pcm;
	काष्ठा snd_soc_component *component = शून्य;
	पूर्णांक err, i = 0;
	अक्षर jack_name[NAME_SIZE];

	list_क्रम_each_entry(pcm, &ctx->hdmi_pcm_list, head) अणु
		component = pcm->codec_dai->component;
		snम_लिखो(jack_name, माप(jack_name),
			"HDMI/DP, pcm=%d Jack", pcm->device);
		err = snd_soc_card_jack_new(card, jack_name,
					SND_JACK_AVOUT, &skylake_hdmi[i],
					शून्य, 0);

		अगर (err)
			वापस err;

		err = hdac_hdmi_jack_init(pcm->codec_dai, pcm->device,
						&skylake_hdmi[i]);
		अगर (err < 0)
			वापस err;

		i++;
	पूर्ण

	अगर (!component)
		वापस -EINVAL;

	वापस hdac_hdmi_jack_port_init(component, &card->dapm);
पूर्ण

/* skylake audio machine driver क्रम SPT + RT286S */
अटल काष्ठा snd_soc_card skylake_rt286 = अणु
	.name = "skylake-rt286",
	.owner = THIS_MODULE,
	.dai_link = skylake_rt286_dais,
	.num_links = ARRAY_SIZE(skylake_rt286_dais),
	.controls = skylake_controls,
	.num_controls = ARRAY_SIZE(skylake_controls),
	.dapm_widमाला_लो = skylake_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(skylake_widमाला_लो),
	.dapm_routes = skylake_rt286_map,
	.num_dapm_routes = ARRAY_SIZE(skylake_rt286_map),
	.fully_routed = true,
	.late_probe = skylake_card_late_probe,
पूर्ण;

अटल पूर्णांक skylake_audio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा skl_rt286_निजी *ctx;

	ctx = devm_kzalloc(&pdev->dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&ctx->hdmi_pcm_list);

	skylake_rt286.dev = &pdev->dev;
	snd_soc_card_set_drvdata(&skylake_rt286, ctx);

	वापस devm_snd_soc_रेजिस्टर_card(&pdev->dev, &skylake_rt286);
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id skl_board_ids[] = अणु
	अणु .name = "skl_alc286s_i2s" पूर्ण,
	अणु .name = "kbl_alc286s_i2s" पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver skylake_audio = अणु
	.probe = skylake_audio_probe,
	.driver = अणु
		.name = "skl_alc286s_i2s",
		.pm = &snd_soc_pm_ops,
	पूर्ण,
	.id_table = skl_board_ids,

पूर्ण;

module_platक्रमm_driver(skylake_audio)

/* Module inक्रमmation */
MODULE_AUTHOR("Omair Mohammed Abdullah <omair.m.abdullah@intel.com>");
MODULE_DESCRIPTION("Intel SST Audio for Skylake");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:skl_alc286s_i2s");
MODULE_ALIAS("platform:kbl_alc286s_i2s");
