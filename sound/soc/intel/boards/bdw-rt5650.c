<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ASoC machine driver क्रम Intel Broadwell platक्रमms with RT5650 codec
 *
 * Copyright 2019, The Chromium OS Authors.  All rights reserved.
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/core.h>
#समावेश <sound/jack.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-acpi.h>

#समावेश "../../codecs/rt5645.h"

काष्ठा bdw_rt5650_priv अणु
	काष्ठा gpio_desc *gpio_hp_en;
	काष्ठा snd_soc_component *component;
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget bdw_rt5650_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone", शून्य),
	SND_SOC_DAPM_SPK("Speaker", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_MIC("DMIC Pair1", शून्य),
	SND_SOC_DAPM_MIC("DMIC Pair2", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route bdw_rt5650_map[] = अणु
	/* Speakers */
	अणु"Speaker", शून्य, "SPOL"पूर्ण,
	अणु"Speaker", शून्य, "SPOR"पूर्ण,

	/* Headset jack connectors */
	अणु"Headphone", शून्य, "HPOL"पूर्ण,
	अणु"Headphone", शून्य, "HPOR"पूर्ण,
	अणु"IN1P", शून्य, "Headset Mic"पूर्ण,
	अणु"IN1N", शून्य, "Headset Mic"पूर्ण,

	/* Digital MICs
	 * DMIC Pair1 are the two DMICs connected on the DMICN1 connector.
	 * DMIC Pair2 are the two DMICs connected on the DMICN2 connector.
	 * Facing the camera, DMIC Pair1 are on the left side, DMIC Pair2
	 * are on the right side.
	 */
	अणु"DMIC L1", शून्य, "DMIC Pair1"पूर्ण,
	अणु"DMIC R1", शून्य, "DMIC Pair1"पूर्ण,
	अणु"DMIC L2", शून्य, "DMIC Pair2"पूर्ण,
	अणु"DMIC R2", शून्य, "DMIC Pair2"पूर्ण,

	/* CODEC BE connections */
	अणु"SSP0 CODEC IN", शून्य, "AIF1 Capture"पूर्ण,
	अणु"AIF1 Playback", शून्य, "SSP0 CODEC OUT"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new bdw_rt5650_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Speaker"),
	SOC_DAPM_PIN_SWITCH("Headphone"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("DMIC Pair1"),
	SOC_DAPM_PIN_SWITCH("DMIC Pair2"),
पूर्ण;


अटल काष्ठा snd_soc_jack headphone_jack;
अटल काष्ठा snd_soc_jack mic_jack;

अटल काष्ठा snd_soc_jack_pin headphone_jack_pin = अणु
	.pin	= "Headphone",
	.mask	= SND_JACK_HEADPHONE,
पूर्ण;

अटल काष्ठा snd_soc_jack_pin mic_jack_pin = अणु
	.pin	= "Headset Mic",
	.mask	= SND_JACK_MICROPHONE,
पूर्ण;

अटल पूर्णांक broadwell_ssp0_fixup(काष्ठा snd_soc_pcm_runसमय *rtd,
			काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_पूर्णांकerval *rate = hw_param_पूर्णांकerval(params,
						      SNDRV_PCM_HW_PARAM_RATE);
	काष्ठा snd_पूर्णांकerval *chan = hw_param_पूर्णांकerval(params,
						      SNDRV_PCM_HW_PARAM_CHANNELS);

	/* The ADSP will covert the FE rate to 48k, max 4-channels */
	rate->min = rate->max = 48000;
	chan->min = 2;
	chan->max = 4;

	/* set SSP0 to 24 bit */
	snd_mask_set_क्रमmat(hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT),
			    SNDRV_PCM_FORMAT_S24_LE);

	वापस 0;
पूर्ण

अटल पूर्णांक bdw_rt5650_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	पूर्णांक ret;

	/* Workaround: set codec PLL to 19.2MHz that PLL source is
	 * from MCLK(24MHz) to conक्रमm 2.4MHz DMIC घड़ी.
	 */
	ret = snd_soc_dai_set_pll(codec_dai, 0, RT5645_PLL1_S_MCLK,
		24000000, 19200000);
	अगर (ret < 0) अणु
		dev_err(rtd->dev, "can't set codec pll: %d\n", ret);
		वापस ret;
	पूर्ण

	/* The actual MCLK freq is 24MHz. The codec is told that MCLK is
	 * 24.576MHz to satisfy the requirement of rl6231_get_clk_info.
	 * ASRC is enabled on AD and DA filters to ensure good audio quality.
	 */
	ret = snd_soc_dai_set_sysclk(codec_dai, RT5645_SCLK_S_PLL1, 24576000,
		SND_SOC_CLOCK_IN);
	अगर (ret < 0) अणु
		dev_err(rtd->dev, "can't set codec sysclk configuration\n");
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा snd_soc_ops bdw_rt5650_ops = अणु
	.hw_params = bdw_rt5650_hw_params,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक channels[] = अणु
	2, 4,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_channels = अणु
	.count = ARRAY_SIZE(channels),
	.list = channels,
	.mask = 0,
पूर्ण;

अटल पूर्णांक bdw_rt5650_fe_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	/* Board supports stereo and quad configurations क्रम capture */
	अगर (substream->stream != SNDRV_PCM_STREAM_CAPTURE)
		वापस 0;

	runसमय->hw.channels_max = 4;
	वापस snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0,
					  SNDRV_PCM_HW_PARAM_CHANNELS,
					  &स्थिरraपूर्णांकs_channels);
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops bdw_rt5650_fe_ops = अणु
	.startup = bdw_rt5650_fe_startup,
पूर्ण;

अटल पूर्णांक bdw_rt5650_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा bdw_rt5650_priv *bdw_rt5650 =
		snd_soc_card_get_drvdata(rtd->card);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_component *component = codec_dai->component;
	पूर्णांक ret;

	/* Enable codec ASRC function क्रम Stereo DAC/Stereo1 ADC/DMIC/I2S1.
	 * The ASRC घड़ी source is clk_i2s1_asrc.
	 */
	rt5645_sel_asrc_clk_src(component,
				RT5645_DA_STEREO_FILTER |
				RT5645_DA_MONO_L_FILTER |
				RT5645_DA_MONO_R_FILTER |
				RT5645_AD_STEREO_FILTER |
				RT5645_AD_MONO_L_FILTER |
				RT5645_AD_MONO_R_FILTER,
				RT5645_CLK_SEL_I2S1_ASRC);

	/* TDM 4 slots 24 bit, set Rx & Tx biपंचांगask to 4 active slots */
	ret = snd_soc_dai_set_tdm_slot(codec_dai, 0xF, 0xF, 4, 24);

	अगर (ret < 0) अणु
		dev_err(rtd->dev, "can't set codec TDM slot %d\n", ret);
		वापस ret;
	पूर्ण

	/* Create and initialize headphone jack */
	अगर (snd_soc_card_jack_new(rtd->card, "Headphone Jack",
			SND_JACK_HEADPHONE, &headphone_jack,
			&headphone_jack_pin, 1)) अणु
		dev_err(component->dev, "Can't create headphone jack\n");
	पूर्ण

	/* Create and initialize mic jack */
	अगर (snd_soc_card_jack_new(rtd->card, "Mic Jack", SND_JACK_MICROPHONE,
			&mic_jack, &mic_jack_pin, 1)) अणु
		dev_err(component->dev, "Can't create mic jack\n");
	पूर्ण

	rt5645_set_jack_detect(component, &headphone_jack, &mic_jack, शून्य);

	bdw_rt5650->component = component;

	वापस 0;
पूर्ण

/* broadwell digital audio पूर्णांकerface glue - connects codec <--> CPU */
SND_SOC_DAILINK_DEF(dummy,
	DAILINK_COMP_ARRAY(COMP_DUMMY()));

SND_SOC_DAILINK_DEF(fe,
	DAILINK_COMP_ARRAY(COMP_CPU("System Pin")));

SND_SOC_DAILINK_DEF(platक्रमm,
	DAILINK_COMP_ARRAY(COMP_PLATFORM("haswell-pcm-audio")));

SND_SOC_DAILINK_DEF(be,
	DAILINK_COMP_ARRAY(COMP_CODEC("i2c-10EC5650:00", "rt5645-aif1")));

SND_SOC_DAILINK_DEF(ssp0_port,
	    DAILINK_COMP_ARRAY(COMP_CPU("ssp0-port")));

अटल काष्ठा snd_soc_dai_link bdw_rt5650_dais[] = अणु
	/* Front End DAI links */
	अणु
		.name = "System PCM",
		.stream_name = "System Playback",
		.nonatomic = 1,
		.dynamic = 1,
		.ops = &bdw_rt5650_fe_ops,
		.trigger = अणु
			SND_SOC_DPCM_TRIGGER_POST,
			SND_SOC_DPCM_TRIGGER_POST
		पूर्ण,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(fe, dummy, platक्रमm),
	पूर्ण,

	/* Back End DAI links */
	अणु
		/* SSP0 - Codec */
		.name = "Codec",
		.id = 0,
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_DSP_B | SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBS_CFS,
		.ignore_pmकरोwn_समय = 1,
		.be_hw_params_fixup = broadwell_ssp0_fixup,
		.ops = &bdw_rt5650_ops,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.init = bdw_rt5650_init,
		SND_SOC_DAILINK_REG(ssp0_port, be, platक्रमm),
	पूर्ण,
पूर्ण;

/* use space beक्रमe codec name to simplअगरy card ID, and simplअगरy driver name */
#घोषणा SOF_CARD_NAME "bdw rt5650" /* card name will be 'sof-bdw rt5650' */
#घोषणा SOF_DRIVER_NAME "SOF"

#घोषणा CARD_NAME "bdw-rt5650"
#घोषणा DRIVER_NAME शून्य /* card name will be used क्रम driver name */

/* ASoC machine driver क्रम Broadwell DSP + RT5650 */
अटल काष्ठा snd_soc_card bdw_rt5650_card = अणु
	.name = CARD_NAME,
	.driver_name = DRIVER_NAME,
	.owner = THIS_MODULE,
	.dai_link = bdw_rt5650_dais,
	.num_links = ARRAY_SIZE(bdw_rt5650_dais),
	.dapm_widमाला_लो = bdw_rt5650_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(bdw_rt5650_widमाला_लो),
	.dapm_routes = bdw_rt5650_map,
	.num_dapm_routes = ARRAY_SIZE(bdw_rt5650_map),
	.controls = bdw_rt5650_controls,
	.num_controls = ARRAY_SIZE(bdw_rt5650_controls),
	.fully_routed = true,
पूर्ण;

अटल पूर्णांक bdw_rt5650_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bdw_rt5650_priv *bdw_rt5650;
	काष्ठा snd_soc_acpi_mach *mach;
	पूर्णांक ret;

	bdw_rt5650_card.dev = &pdev->dev;

	/* Allocate driver निजी काष्ठा */
	bdw_rt5650 = devm_kzalloc(&pdev->dev, माप(काष्ठा bdw_rt5650_priv),
		GFP_KERNEL);
	अगर (!bdw_rt5650)
		वापस -ENOMEM;

	/* override plaक्रमm name, अगर required */
	mach = pdev->dev.platक्रमm_data;
	ret = snd_soc_fixup_dai_links_platक्रमm_name(&bdw_rt5650_card,
						    mach->mach_params.platक्रमm);

	अगर (ret)
		वापस ret;

	/* set card and driver name */
	अगर (snd_soc_acpi_sof_parent(&pdev->dev)) अणु
		bdw_rt5650_card.name = SOF_CARD_NAME;
		bdw_rt5650_card.driver_name = SOF_DRIVER_NAME;
	पूर्ण अन्यथा अणु
		bdw_rt5650_card.name = CARD_NAME;
		bdw_rt5650_card.driver_name = DRIVER_NAME;
	पूर्ण

	snd_soc_card_set_drvdata(&bdw_rt5650_card, bdw_rt5650);

	वापस devm_snd_soc_रेजिस्टर_card(&pdev->dev, &bdw_rt5650_card);
पूर्ण

अटल काष्ठा platक्रमm_driver bdw_rt5650_audio = अणु
	.probe = bdw_rt5650_probe,
	.driver = अणु
		.name = "bdw-rt5650",
		.pm = &snd_soc_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(bdw_rt5650_audio)

/* Module inक्रमmation */
MODULE_AUTHOR("Ben Zhang <benzh@chromium.org>");
MODULE_DESCRIPTION("Intel Broadwell RT5650 machine driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:bdw-rt5650");
