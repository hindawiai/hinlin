<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ASoC machine driver क्रम Intel Broadwell platक्रमms with RT5677 codec
 *
 * Copyright (c) 2014, The Chromium OS Authors.  All rights reserved.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/delay.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/jack.h>
#समावेश <sound/soc-acpi.h>

#समावेश "../../codecs/rt5677.h"

काष्ठा bdw_rt5677_priv अणु
	काष्ठा gpio_desc *gpio_hp_en;
	काष्ठा snd_soc_component *component;
पूर्ण;

अटल पूर्णांक bdw_rt5677_event_hp(काष्ठा snd_soc_dapm_widget *w,
			काष्ठा snd_kcontrol *k, पूर्णांक event)
अणु
	काष्ठा snd_soc_dapm_context *dapm = w->dapm;
	काष्ठा snd_soc_card *card = dapm->card;
	काष्ठा bdw_rt5677_priv *bdw_rt5677 = snd_soc_card_get_drvdata(card);

	अगर (SND_SOC_DAPM_EVENT_ON(event))
		msleep(70);

	gpiod_set_value_cansleep(bdw_rt5677->gpio_hp_en,
		SND_SOC_DAPM_EVENT_ON(event));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget bdw_rt5677_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone", bdw_rt5677_event_hp),
	SND_SOC_DAPM_SPK("Speaker", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_MIC("Local DMICs", शून्य),
	SND_SOC_DAPM_MIC("Remote DMICs", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route bdw_rt5677_map[] = अणु
	/* Speakers */
	अणु"Speaker", शून्य, "PDM1L"पूर्ण,
	अणु"Speaker", शून्य, "PDM1R"पूर्ण,

	/* Headset jack connectors */
	अणु"Headphone", शून्य, "LOUT1"पूर्ण,
	अणु"Headphone", शून्य, "LOUT2"पूर्ण,
	अणु"IN1P", शून्य, "Headset Mic"पूर्ण,
	अणु"IN1N", शून्य, "Headset Mic"पूर्ण,

	/* Digital MICs
	 * Local DMICs: the two DMICs on the मुख्यboard
	 * Remote DMICs: the two DMICs on the camera module
	 */
	अणु"DMIC L1", शून्य, "Remote DMICs"पूर्ण,
	अणु"DMIC R1", शून्य, "Remote DMICs"पूर्ण,
	अणु"DMIC L2", शून्य, "Local DMICs"पूर्ण,
	अणु"DMIC R2", शून्य, "Local DMICs"पूर्ण,

	/* CODEC BE connections */
	अणु"SSP0 CODEC IN", शून्य, "AIF1 Capture"पूर्ण,
	अणु"AIF1 Playback", शून्य, "SSP0 CODEC OUT"पूर्ण,
	अणु"DSP Capture", शून्य, "DSP Buffer"पूर्ण,

	/* DSP Clock Connections */
	अणु "DSP Buffer", शून्य, "SSP0 CODEC IN" पूर्ण,
	अणु "SSP0 CODEC IN", शून्य, "DSPTX" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new bdw_rt5677_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Speaker"),
	SOC_DAPM_PIN_SWITCH("Headphone"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Local DMICs"),
	SOC_DAPM_PIN_SWITCH("Remote DMICs"),
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

अटल काष्ठा snd_soc_jack_gpio headphone_jack_gpio = अणु
	.name			= "plug-det",
	.report			= SND_JACK_HEADPHONE,
	.debounce_समय		= 200,
पूर्ण;

अटल काष्ठा snd_soc_jack_gpio mic_jack_gpio = अणु
	.name			= "mic-present",
	.report			= SND_JACK_MICROPHONE,
	.debounce_समय		= 200,
	.invert			= 1,
पूर्ण;

/* GPIO indexes defined by ACPI */
क्रमागत अणु
	RT5677_GPIO_PLUG_DET		= 0,
	RT5677_GPIO_MIC_PRESENT_L	= 1,
	RT5677_GPIO_HOTWORD_DET_L	= 2,
	RT5677_GPIO_DSP_INT		= 3,
	RT5677_GPIO_HP_AMP_SHDN_L	= 4,
पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_params plug_det_gpio = अणु RT5677_GPIO_PLUG_DET, 0, false पूर्ण;
अटल स्थिर काष्ठा acpi_gpio_params mic_present_gpio = अणु RT5677_GPIO_MIC_PRESENT_L, 0, false पूर्ण;
अटल स्थिर काष्ठा acpi_gpio_params headphone_enable_gpio = अणु RT5677_GPIO_HP_AMP_SHDN_L, 0, false पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_mapping bdw_rt5677_gpios[] = अणु
	अणु "plug-det-gpios", &plug_det_gpio, 1 पूर्ण,
	अणु "mic-present-gpios", &mic_present_gpio, 1 पूर्ण,
	अणु "headphone-enable-gpios", &headphone_enable_gpio, 1 पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

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

अटल पूर्णांक bdw_rt5677_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	पूर्णांक ret;

	ret = snd_soc_dai_set_sysclk(codec_dai, RT5677_SCLK_S_MCLK, 24576000,
		SND_SOC_CLOCK_IN);
	अगर (ret < 0) अणु
		dev_err(rtd->dev, "can't set codec sysclk configuration\n");
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक bdw_rt5677_dsp_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	पूर्णांक ret;

	ret = snd_soc_dai_set_sysclk(codec_dai, RT5677_SCLK_S_PLL1, 24576000,
		SND_SOC_CLOCK_IN);
	अगर (ret < 0) अणु
		dev_err(rtd->dev, "can't set codec sysclk configuration\n");
		वापस ret;
	पूर्ण
	ret = snd_soc_dai_set_pll(codec_dai, 0, RT5677_PLL1_S_MCLK,
		24000000, 24576000);
	अगर (ret < 0) अणु
		dev_err(rtd->dev, "can't set codec pll configuration\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops bdw_rt5677_ops = अणु
	.hw_params = bdw_rt5677_hw_params,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_ops bdw_rt5677_dsp_ops = अणु
	.hw_params = bdw_rt5677_dsp_hw_params,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक channels[] = अणु
	2,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_channels = अणु
	.count = ARRAY_SIZE(channels),
	.list = channels,
	.mask = 0,
पूर्ण;

अटल पूर्णांक bdw_rt5677_fe_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	/* Board supports stereo configuration only */
	runसमय->hw.channels_max = 2;
	वापस snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0,
					  SNDRV_PCM_HW_PARAM_CHANNELS,
					  &स्थिरraपूर्णांकs_channels);
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops bdw_rt5677_fe_ops = अणु
	.startup = bdw_rt5677_fe_startup,
पूर्ण;

अटल पूर्णांक bdw_rt5677_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा bdw_rt5677_priv *bdw_rt5677 =
			snd_soc_card_get_drvdata(rtd->card);
	काष्ठा snd_soc_component *component = asoc_rtd_to_codec(rtd, 0)->component;
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	पूर्णांक ret;

	ret = devm_acpi_dev_add_driver_gpios(component->dev, bdw_rt5677_gpios);
	अगर (ret)
		dev_warn(component->dev, "Failed to add driver gpios\n");

	/* Enable codec ASRC function क्रम Stereo DAC/Stereo1 ADC/DMIC/I2S1.
	 * The ASRC घड़ी source is clk_i2s1_asrc.
	 */
	rt5677_sel_asrc_clk_src(component, RT5677_DA_STEREO_FILTER |
			RT5677_AD_STEREO1_FILTER | RT5677_I2S1_SOURCE,
			RT5677_CLK_SEL_I2S1_ASRC);
	/* Enable codec ASRC function क्रम Mono ADC L.
	 * The ASRC घड़ी source is clk_sys2_asrc.
	 */
	rt5677_sel_asrc_clk_src(component, RT5677_AD_MONO_L_FILTER,
			RT5677_CLK_SEL_SYS2);

	/* Request rt5677 GPIO क्रम headphone amp control */
	bdw_rt5677->gpio_hp_en = gpiod_get(component->dev, "headphone-enable",
					   GPIOD_OUT_LOW);
	अगर (IS_ERR(bdw_rt5677->gpio_hp_en)) अणु
		dev_err(component->dev, "Can't find HP_AMP_SHDN_L gpio\n");
		वापस PTR_ERR(bdw_rt5677->gpio_hp_en);
	पूर्ण

	/* Create and initialize headphone jack */
	अगर (!snd_soc_card_jack_new(rtd->card, "Headphone Jack",
			SND_JACK_HEADPHONE, &headphone_jack,
			&headphone_jack_pin, 1)) अणु
		headphone_jack_gpio.gpiod_dev = component->dev;
		अगर (snd_soc_jack_add_gpios(&headphone_jack, 1,
				&headphone_jack_gpio))
			dev_err(component->dev, "Can't add headphone jack gpio\n");
	पूर्ण अन्यथा अणु
		dev_err(component->dev, "Can't create headphone jack\n");
	पूर्ण

	/* Create and initialize mic jack */
	अगर (!snd_soc_card_jack_new(rtd->card, "Mic Jack",
			SND_JACK_MICROPHONE, &mic_jack,
			&mic_jack_pin, 1)) अणु
		mic_jack_gpio.gpiod_dev = component->dev;
		अगर (snd_soc_jack_add_gpios(&mic_jack, 1, &mic_jack_gpio))
			dev_err(component->dev, "Can't add mic jack gpio\n");
	पूर्ण अन्यथा अणु
		dev_err(component->dev, "Can't create mic jack\n");
	पूर्ण
	bdw_rt5677->component = component;

	snd_soc_dapm_क्रमce_enable_pin(dapm, "MICBIAS1");
	वापस 0;
पूर्ण

अटल व्योम bdw_rt5677_निकास(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा bdw_rt5677_priv *bdw_rt5677 =
			snd_soc_card_get_drvdata(rtd->card);

	/*
	 * The .निकास() can be reached without going through the .init()
	 * so explicitly test अगर the gpiod is valid
	 */
	अगर (!IS_ERR_OR_शून्य(bdw_rt5677->gpio_hp_en))
		gpiod_put(bdw_rt5677->gpio_hp_en);
पूर्ण

/* broadwell digital audio पूर्णांकerface glue - connects codec <--> CPU */
SND_SOC_DAILINK_DEF(dummy,
	DAILINK_COMP_ARRAY(COMP_DUMMY()));

SND_SOC_DAILINK_DEF(fe,
	DAILINK_COMP_ARRAY(COMP_CPU("System Pin")));

SND_SOC_DAILINK_DEF(platक्रमm,
	DAILINK_COMP_ARRAY(COMP_PLATFORM("haswell-pcm-audio")));

SND_SOC_DAILINK_DEF(be,
	DAILINK_COMP_ARRAY(COMP_CODEC("i2c-RT5677CE:00", "rt5677-aif1")));

SND_SOC_DAILINK_DEF(ssp0_port,
	    DAILINK_COMP_ARRAY(COMP_CPU("ssp0-port")));

/* Wake on voice पूर्णांकerface */
SND_SOC_DAILINK_DEFS(dsp,
	DAILINK_COMP_ARRAY(COMP_CPU("spi-RT5677AA:00")),
	DAILINK_COMP_ARRAY(COMP_CODEC("i2c-RT5677CE:00", "rt5677-dspbuffer")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("spi-RT5677AA:00")));

अटल काष्ठा snd_soc_dai_link bdw_rt5677_dais[] = अणु
	/* Front End DAI links */
	अणु
		.name = "System PCM",
		.stream_name = "System Playback/Capture",
		.nonatomic = 1,
		.dynamic = 1,
		.trigger = अणु
			SND_SOC_DPCM_TRIGGER_POST,
			SND_SOC_DPCM_TRIGGER_POST
		पूर्ण,
		.dpcm_capture = 1,
		.dpcm_playback = 1,
		.ops = &bdw_rt5677_fe_ops,
		SND_SOC_DAILINK_REG(fe, dummy, platक्रमm),
	पूर्ण,

	/* Non-DPCM links */
	अणु
		.name = "Codec DSP",
		.stream_name = "Wake on Voice",
		.capture_only = 1,
		.ops = &bdw_rt5677_dsp_ops,
		SND_SOC_DAILINK_REG(dsp),
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
		.be_hw_params_fixup = broadwell_ssp0_fixup,
		.ops = &bdw_rt5677_ops,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.init = bdw_rt5677_init,
		.निकास = bdw_rt5677_निकास,
		SND_SOC_DAILINK_REG(ssp0_port, be, platक्रमm),
	पूर्ण,
पूर्ण;

अटल पूर्णांक bdw_rt5677_suspend_pre(काष्ठा snd_soc_card *card)
अणु
	काष्ठा bdw_rt5677_priv *bdw_rt5677 = snd_soc_card_get_drvdata(card);
	काष्ठा snd_soc_dapm_context *dapm;

	अगर (bdw_rt5677->component) अणु
		dapm = snd_soc_component_get_dapm(bdw_rt5677->component);
		snd_soc_dapm_disable_pin(dapm, "MICBIAS1");
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bdw_rt5677_resume_post(काष्ठा snd_soc_card *card)
अणु
	काष्ठा bdw_rt5677_priv *bdw_rt5677 = snd_soc_card_get_drvdata(card);
	काष्ठा snd_soc_dapm_context *dapm;

	अगर (bdw_rt5677->component) अणु
		dapm = snd_soc_component_get_dapm(bdw_rt5677->component);
		snd_soc_dapm_क्रमce_enable_pin(dapm, "MICBIAS1");
	पूर्ण
	वापस 0;
पूर्ण

/* use space beक्रमe codec name to simplअगरy card ID, and simplअगरy driver name */
#घोषणा SOF_CARD_NAME "bdw rt5677" /* card name will be 'sof-bdw rt5677' */
#घोषणा SOF_DRIVER_NAME "SOF"

#घोषणा CARD_NAME "bdw-rt5677"
#घोषणा DRIVER_NAME शून्य /* card name will be used क्रम driver name */

/* ASoC machine driver क्रम Broadwell DSP + RT5677 */
अटल काष्ठा snd_soc_card bdw_rt5677_card = अणु
	.name = CARD_NAME,
	.driver_name = DRIVER_NAME,
	.owner = THIS_MODULE,
	.dai_link = bdw_rt5677_dais,
	.num_links = ARRAY_SIZE(bdw_rt5677_dais),
	.dapm_widमाला_लो = bdw_rt5677_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(bdw_rt5677_widमाला_लो),
	.dapm_routes = bdw_rt5677_map,
	.num_dapm_routes = ARRAY_SIZE(bdw_rt5677_map),
	.controls = bdw_rt5677_controls,
	.num_controls = ARRAY_SIZE(bdw_rt5677_controls),
	.fully_routed = true,
	.suspend_pre = bdw_rt5677_suspend_pre,
	.resume_post = bdw_rt5677_resume_post,
पूर्ण;

अटल पूर्णांक bdw_rt5677_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bdw_rt5677_priv *bdw_rt5677;
	काष्ठा snd_soc_acpi_mach *mach;
	पूर्णांक ret;

	bdw_rt5677_card.dev = &pdev->dev;

	/* Allocate driver निजी काष्ठा */
	bdw_rt5677 = devm_kzalloc(&pdev->dev, माप(काष्ठा bdw_rt5677_priv),
		GFP_KERNEL);
	अगर (!bdw_rt5677) अणु
		dev_err(&pdev->dev, "Can't allocate bdw_rt5677\n");
		वापस -ENOMEM;
	पूर्ण

	/* override plaक्रमm name, अगर required */
	mach = pdev->dev.platक्रमm_data;
	ret = snd_soc_fixup_dai_links_platक्रमm_name(&bdw_rt5677_card,
						    mach->mach_params.platक्रमm);
	अगर (ret)
		वापस ret;

	/* set card and driver name */
	अगर (snd_soc_acpi_sof_parent(&pdev->dev)) अणु
		bdw_rt5677_card.name = SOF_CARD_NAME;
		bdw_rt5677_card.driver_name = SOF_DRIVER_NAME;
	पूर्ण अन्यथा अणु
		bdw_rt5677_card.name = CARD_NAME;
		bdw_rt5677_card.driver_name = DRIVER_NAME;
	पूर्ण

	snd_soc_card_set_drvdata(&bdw_rt5677_card, bdw_rt5677);

	वापस devm_snd_soc_रेजिस्टर_card(&pdev->dev, &bdw_rt5677_card);
पूर्ण

अटल काष्ठा platक्रमm_driver bdw_rt5677_audio = अणु
	.probe = bdw_rt5677_probe,
	.driver = अणु
		.name = "bdw-rt5677",
		.pm = &snd_soc_pm_ops
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(bdw_rt5677_audio)

/* Module inक्रमmation */
MODULE_AUTHOR("Ben Zhang");
MODULE_DESCRIPTION("Intel Broadwell RT5677 machine driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:bdw-rt5677");
