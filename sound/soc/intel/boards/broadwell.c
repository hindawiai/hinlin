<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel Broadwell Wildcatpoपूर्णांक SST Audio
 *
 * Copyright (C) 2013, Intel Corporation. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/jack.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc-acpi.h>

#समावेश "../../codecs/rt286.h"

अटल काष्ठा snd_soc_jack broadwell_headset;
/* Headset jack detection DAPM pins */
अटल काष्ठा snd_soc_jack_pin broadwell_headset_pins[] = अणु
	अणु
		.pin = "Mic Jack",
		.mask = SND_JACK_MICROPHONE,
	पूर्ण,
	अणु
		.pin = "Headphone Jack",
		.mask = SND_JACK_HEADPHONE,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new broadwell_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Speaker"),
	SOC_DAPM_PIN_SWITCH("Headphone Jack"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget broadwell_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_SPK("Speaker", शून्य),
	SND_SOC_DAPM_MIC("Mic Jack", शून्य),
	SND_SOC_DAPM_MIC("DMIC1", शून्य),
	SND_SOC_DAPM_MIC("DMIC2", शून्य),
	SND_SOC_DAPM_LINE("Line Jack", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route broadwell_rt286_map[] = अणु

	/* speaker */
	अणु"Speaker", शून्य, "SPOR"पूर्ण,
	अणु"Speaker", शून्य, "SPOL"पूर्ण,

	/* HP jack connectors - unknown अगर we have jack deteck */
	अणु"Headphone Jack", शून्य, "HPO Pin"पूर्ण,

	/* other jacks */
	अणु"MIC1", शून्य, "Mic Jack"पूर्ण,
	अणु"LINE1", शून्य, "Line Jack"पूर्ण,

	/* digital mics */
	अणु"DMIC1 Pin", शून्य, "DMIC1"पूर्ण,
	अणु"DMIC2 Pin", शून्य, "DMIC2"पूर्ण,

	/* CODEC BE connections */
	अणु"SSP0 CODEC IN", शून्य, "AIF1 Capture"पूर्ण,
	अणु"AIF1 Playback", शून्य, "SSP0 CODEC OUT"पूर्ण,
पूर्ण;

अटल पूर्णांक broadwell_rt286_codec_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_component *component = asoc_rtd_to_codec(rtd, 0)->component;
	पूर्णांक ret = 0;
	ret = snd_soc_card_jack_new(rtd->card, "Headset",
		SND_JACK_HEADSET | SND_JACK_BTN_0, &broadwell_headset,
		broadwell_headset_pins, ARRAY_SIZE(broadwell_headset_pins));
	अगर (ret)
		वापस ret;

	rt286_mic_detect(component, &broadwell_headset);
	वापस 0;
पूर्ण


अटल पूर्णांक broadwell_ssp0_fixup(काष्ठा snd_soc_pcm_runसमय *rtd,
			काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_पूर्णांकerval *rate = hw_param_पूर्णांकerval(params,
						      SNDRV_PCM_HW_PARAM_RATE);
	काष्ठा snd_पूर्णांकerval *chan = hw_param_पूर्णांकerval(params,
						      SNDRV_PCM_HW_PARAM_CHANNELS);

	/* The ADSP will covert the FE rate to 48k, stereo */
	rate->min = rate->max = 48000;
	chan->min = chan->max = 2;

	/* set SSP0 to 16 bit */
	params_set_क्रमmat(params, SNDRV_PCM_FORMAT_S16_LE);
	वापस 0;
पूर्ण

अटल पूर्णांक broadwell_rt286_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	पूर्णांक ret;

	ret = snd_soc_dai_set_sysclk(codec_dai, RT286_SCLK_S_PLL, 24000000,
		SND_SOC_CLOCK_IN);

	अगर (ret < 0) अणु
		dev_err(rtd->dev, "can't set codec sysclk configuration\n");
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops broadwell_rt286_ops = अणु
	.hw_params = broadwell_rt286_hw_params,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक channels[] = अणु
	2,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_channels = अणु
	.count = ARRAY_SIZE(channels),
	.list = channels,
	.mask = 0,
पूर्ण;

अटल पूर्णांक broadwell_fe_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	/* Board supports stereo configuration only */
	runसमय->hw.channels_max = 2;
	वापस snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0,
					  SNDRV_PCM_HW_PARAM_CHANNELS,
					  &स्थिरraपूर्णांकs_channels);
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops broadwell_fe_ops = अणु
	.startup = broadwell_fe_startup,
पूर्ण;

SND_SOC_DAILINK_DEF(प्रणाली,
	DAILINK_COMP_ARRAY(COMP_CPU("System Pin")));

SND_SOC_DAILINK_DEF(offload0,
	DAILINK_COMP_ARRAY(COMP_CPU("Offload0 Pin")));

SND_SOC_DAILINK_DEF(offload1,
	DAILINK_COMP_ARRAY(COMP_CPU("Offload1 Pin")));

SND_SOC_DAILINK_DEF(loopback,
	DAILINK_COMP_ARRAY(COMP_CPU("Loopback Pin")));

SND_SOC_DAILINK_DEF(dummy,
	DAILINK_COMP_ARRAY(COMP_DUMMY()));

SND_SOC_DAILINK_DEF(platक्रमm,
	DAILINK_COMP_ARRAY(COMP_PLATFORM("haswell-pcm-audio")));

SND_SOC_DAILINK_DEF(codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("i2c-INT343A:00", "rt286-aif1")));

SND_SOC_DAILINK_DEF(ssp0_port,
	    DAILINK_COMP_ARRAY(COMP_CPU("ssp0-port")));

/* broadwell digital audio पूर्णांकerface glue - connects codec <--> CPU */
अटल काष्ठा snd_soc_dai_link broadwell_rt286_dais[] = अणु
	/* Front End DAI links */
	अणु
		.name = "System PCM",
		.stream_name = "System Playback/Capture",
		.nonatomic = 1,
		.dynamic = 1,
		.trigger = अणुSND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.ops = &broadwell_fe_ops,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(प्रणाली, dummy, platक्रमm),
	पूर्ण,
	अणु
		.name = "Offload0",
		.stream_name = "Offload0 Playback",
		.nonatomic = 1,
		.dynamic = 1,
		.trigger = अणुSND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(offload0, dummy, platक्रमm),
	पूर्ण,
	अणु
		.name = "Offload1",
		.stream_name = "Offload1 Playback",
		.nonatomic = 1,
		.dynamic = 1,
		.trigger = अणुSND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(offload1, dummy, platक्रमm),
	पूर्ण,
	अणु
		.name = "Loopback PCM",
		.stream_name = "Loopback",
		.nonatomic = 1,
		.dynamic = 1,
		.trigger = अणुSND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(loopback, dummy, platक्रमm),
	पूर्ण,
	/* Back End DAI links */
	अणु
		/* SSP0 - Codec */
		.name = "Codec",
		.id = 0,
		.no_pcm = 1,
		.init = broadwell_rt286_codec_init,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBS_CFS,
		.ignore_pmकरोwn_समय = 1,
		.be_hw_params_fixup = broadwell_ssp0_fixup,
		.ops = &broadwell_rt286_ops,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(ssp0_port, codec, platक्रमm),
	पूर्ण,
पूर्ण;

अटल पूर्णांक broadwell_disable_jack(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_component *component;

	क्रम_each_card_components(card, component) अणु
		अगर (!म_भेद(component->name, "i2c-INT343A:00")) अणु

			dev_dbg(component->dev, "disabling jack detect before going to suspend.\n");
			rt286_mic_detect(component, शून्य);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक broadwell_suspend(काष्ठा snd_soc_card *card)
अणु
	वापस broadwell_disable_jack(card);
पूर्ण

अटल पूर्णांक broadwell_resume(काष्ठा snd_soc_card *card)अणु
	काष्ठा snd_soc_component *component;

	क्रम_each_card_components(card, component) अणु
		अगर (!म_भेद(component->name, "i2c-INT343A:00")) अणु

			dev_dbg(component->dev, "enabling jack detect for resume.\n");
			rt286_mic_detect(component, &broadwell_headset);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* use space beक्रमe codec name to simplअगरy card ID, and simplअगरy driver name */
#घोषणा SOF_CARD_NAME "bdw rt286" /* card name will be 'sof-bdw rt286' */
#घोषणा SOF_DRIVER_NAME "SOF"

#घोषणा CARD_NAME "broadwell-rt286"
#घोषणा DRIVER_NAME शून्य /* card name will be used क्रम driver name */

/* broadwell audio machine driver क्रम WPT + RT286S */
अटल काष्ठा snd_soc_card broadwell_rt286 = अणु
	.owner = THIS_MODULE,
	.dai_link = broadwell_rt286_dais,
	.num_links = ARRAY_SIZE(broadwell_rt286_dais),
	.controls = broadwell_controls,
	.num_controls = ARRAY_SIZE(broadwell_controls),
	.dapm_widमाला_लो = broadwell_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(broadwell_widमाला_लो),
	.dapm_routes = broadwell_rt286_map,
	.num_dapm_routes = ARRAY_SIZE(broadwell_rt286_map),
	.fully_routed = true,
	.suspend_pre = broadwell_suspend,
	.resume_post = broadwell_resume,
पूर्ण;

अटल पूर्णांक broadwell_audio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_acpi_mach *mach;
	पूर्णांक ret;

	broadwell_rt286.dev = &pdev->dev;

	/* override plaक्रमm name, अगर required */
	mach = pdev->dev.platक्रमm_data;
	ret = snd_soc_fixup_dai_links_platक्रमm_name(&broadwell_rt286,
						    mach->mach_params.platक्रमm);
	अगर (ret)
		वापस ret;

	/* set card and driver name */
	अगर (snd_soc_acpi_sof_parent(&pdev->dev)) अणु
		broadwell_rt286.name = SOF_CARD_NAME;
		broadwell_rt286.driver_name = SOF_DRIVER_NAME;
	पूर्ण अन्यथा अणु
		broadwell_rt286.name = CARD_NAME;
		broadwell_rt286.driver_name = DRIVER_NAME;
	पूर्ण

	वापस devm_snd_soc_रेजिस्टर_card(&pdev->dev, &broadwell_rt286);
पूर्ण

अटल पूर्णांक broadwell_audio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = platक्रमm_get_drvdata(pdev);

	वापस broadwell_disable_jack(card);
पूर्ण

अटल काष्ठा platक्रमm_driver broadwell_audio = अणु
	.probe = broadwell_audio_probe,
	.हटाओ = broadwell_audio_हटाओ,
	.driver = अणु
		.name = "broadwell-audio",
		.pm = &snd_soc_pm_ops
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(broadwell_audio)

/* Module inक्रमmation */
MODULE_AUTHOR("Liam Girdwood, Xingchao Wang");
MODULE_DESCRIPTION("Intel SST Audio for WPT/Broadwell");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:broadwell-audio");
