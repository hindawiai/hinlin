<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel Haswell Lynxpoपूर्णांक SST Audio
 *
 * Copyright (C) 2013, Intel Corporation. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-acpi.h>
#समावेश <sound/pcm_params.h>

#समावेश "../../codecs/rt5640.h"

/* Haswell ULT platक्रमms have a Headphone and Mic jack */
अटल स्थिर काष्ठा snd_soc_dapm_widget haswell_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphones", शून्य),
	SND_SOC_DAPM_MIC("Mic", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route haswell_rt5640_map[] = अणु

	अणु"Headphones", शून्य, "HPOR"पूर्ण,
	अणु"Headphones", शून्य, "HPOL"पूर्ण,
	अणु"IN2P", शून्य, "Mic"पूर्ण,

	/* CODEC BE connections */
	अणु"SSP0 CODEC IN", शून्य, "AIF1 Capture"पूर्ण,
	अणु"AIF1 Playback", शून्य, "SSP0 CODEC OUT"पूर्ण,
पूर्ण;

अटल पूर्णांक haswell_ssp0_fixup(काष्ठा snd_soc_pcm_runसमय *rtd,
			काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_पूर्णांकerval *rate = hw_param_पूर्णांकerval(params,
			SNDRV_PCM_HW_PARAM_RATE);
	काष्ठा snd_पूर्णांकerval *channels = hw_param_पूर्णांकerval(params,
						SNDRV_PCM_HW_PARAM_CHANNELS);

	/* The ADSP will covert the FE rate to 48k, stereo */
	rate->min = rate->max = 48000;
	channels->min = channels->max = 2;

	/* set SSP0 to 16 bit */
	params_set_क्रमmat(params, SNDRV_PCM_FORMAT_S16_LE);
	वापस 0;
पूर्ण

अटल पूर्णांक haswell_rt5640_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	पूर्णांक ret;

	ret = snd_soc_dai_set_sysclk(codec_dai, RT5640_SCLK_S_MCLK, 12288000,
		SND_SOC_CLOCK_IN);

	अगर (ret < 0) अणु
		dev_err(rtd->dev, "can't set codec sysclk configuration\n");
		वापस ret;
	पूर्ण

	/* set correct codec filter क्रम DAI क्रमmat and घड़ी config */
	snd_soc_component_update_bits(codec_dai->component, 0x83, 0xffff, 0x8000);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops haswell_rt5640_ops = अणु
	.hw_params = haswell_rt5640_hw_params,
पूर्ण;

SND_SOC_DAILINK_DEF(dummy,
	DAILINK_COMP_ARRAY(COMP_DUMMY()));

SND_SOC_DAILINK_DEF(प्रणाली,
	DAILINK_COMP_ARRAY(COMP_CPU("System Pin")));

SND_SOC_DAILINK_DEF(offload0,
	DAILINK_COMP_ARRAY(COMP_CPU("Offload0 Pin")));

SND_SOC_DAILINK_DEF(offload1,
	DAILINK_COMP_ARRAY(COMP_CPU("Offload1 Pin")));

SND_SOC_DAILINK_DEF(loopback,
	DAILINK_COMP_ARRAY(COMP_CPU("Loopback Pin")));

SND_SOC_DAILINK_DEF(codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("i2c-INT33CA:00", "rt5640-aif1")));

SND_SOC_DAILINK_DEF(platक्रमm,
	DAILINK_COMP_ARRAY(COMP_PLATFORM("haswell-pcm-audio")));

SND_SOC_DAILINK_DEF(ssp0_port,
	    DAILINK_COMP_ARRAY(COMP_CPU("ssp0-port")));

अटल काष्ठा snd_soc_dai_link haswell_rt5640_dais[] = अणु
	/* Front End DAI links */
	अणु
		.name = "System",
		.stream_name = "System Playback/Capture",
		.nonatomic = 1,
		.dynamic = 1,
		.trigger = अणुSND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
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
		.name = "Loopback",
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
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBS_CFS,
		.ignore_pmकरोwn_समय = 1,
		.be_hw_params_fixup = haswell_ssp0_fixup,
		.ops = &haswell_rt5640_ops,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(ssp0_port, codec, platक्रमm),
	पूर्ण,
पूर्ण;

/* audio machine driver क्रम Haswell Lynxpoपूर्णांक DSP + RT5640 */
अटल काष्ठा snd_soc_card haswell_rt5640 = अणु
	.name = "haswell-rt5640",
	.owner = THIS_MODULE,
	.dai_link = haswell_rt5640_dais,
	.num_links = ARRAY_SIZE(haswell_rt5640_dais),
	.dapm_widमाला_लो = haswell_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(haswell_widमाला_लो),
	.dapm_routes = haswell_rt5640_map,
	.num_dapm_routes = ARRAY_SIZE(haswell_rt5640_map),
	.fully_routed = true,
पूर्ण;

अटल पूर्णांक haswell_audio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_acpi_mach *mach;
	पूर्णांक ret;

	haswell_rt5640.dev = &pdev->dev;

	/* override plaक्रमm name, अगर required */
	mach = pdev->dev.platक्रमm_data;
	ret = snd_soc_fixup_dai_links_platक्रमm_name(&haswell_rt5640,
						    mach->mach_params.platक्रमm);
	अगर (ret)
		वापस ret;

	वापस devm_snd_soc_रेजिस्टर_card(&pdev->dev, &haswell_rt5640);
पूर्ण

अटल काष्ठा platक्रमm_driver haswell_audio = अणु
	.probe = haswell_audio_probe,
	.driver = अणु
		.name = "haswell-audio",
		.pm = &snd_soc_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(haswell_audio)

/* Module inक्रमmation */
MODULE_AUTHOR("Liam Girdwood, Xingchao Wang");
MODULE_DESCRIPTION("Intel SST Audio for Haswell Lynxpoint");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:haswell-audio");
