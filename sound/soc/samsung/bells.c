<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Bells audio support
//
// Copyright 2012 Wolfson Microelectronics

#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/jack.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/module.h>

#समावेश "../codecs/wm5102.h"
#समावेश "../codecs/wm9081.h"

/* BCLK2 is fixed at this currently */
#घोषणा BCLK2_RATE (64 * 8000)

/*
 * Expect a 24.576MHz crystal अगर one is fitted (the driver will function
 * अगर this is not fitted).
 */
#घोषणा MCLK_RATE 24576000

#घोषणा SYS_AUDIO_RATE 44100
#घोषणा SYS_MCLK_RATE  (SYS_AUDIO_RATE * 512)

#घोषणा DAI_AP_DSP    0
#घोषणा DAI_DSP_CODEC 1
#घोषणा DAI_CODEC_CP  2
#घोषणा DAI_CODEC_SUB 3

काष्ठा bells_drvdata अणु
	पूर्णांक sysclk_rate;
	पूर्णांक asyncclk_rate;
पूर्ण;

अटल काष्ठा bells_drvdata wm2200_drvdata = अणु
	.sysclk_rate = 22579200,
पूर्ण;

अटल काष्ठा bells_drvdata wm5102_drvdata = अणु
	.sysclk_rate = 45158400,
	.asyncclk_rate = 49152000,
पूर्ण;

अटल काष्ठा bells_drvdata wm5110_drvdata = अणु
	.sysclk_rate = 135475200,
	.asyncclk_rate = 147456000,
पूर्ण;

अटल पूर्णांक bells_set_bias_level(काष्ठा snd_soc_card *card,
				काष्ठा snd_soc_dapm_context *dapm,
				क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd;
	काष्ठा snd_soc_dai *codec_dai;
	काष्ठा snd_soc_component *component;
	काष्ठा bells_drvdata *bells = card->drvdata;
	पूर्णांक ret;

	rtd = snd_soc_get_pcm_runसमय(card, &card->dai_link[DAI_DSP_CODEC]);
	codec_dai = asoc_rtd_to_codec(rtd, 0);
	component = codec_dai->component;

	अगर (dapm->dev != codec_dai->dev)
		वापस 0;

	चयन (level) अणु
	हाल SND_SOC_BIAS_PREPARE:
		अगर (dapm->bias_level != SND_SOC_BIAS_STANDBY)
			अवरोध;

		ret = snd_soc_component_set_pll(component, WM5102_FLL1,
					    ARIZONA_FLL_SRC_MCLK1,
					    MCLK_RATE,
					    bells->sysclk_rate);
		अगर (ret < 0)
			pr_err("Failed to start FLL: %d\n", ret);

		अगर (bells->asyncclk_rate) अणु
			ret = snd_soc_component_set_pll(component, WM5102_FLL2,
						    ARIZONA_FLL_SRC_AIF2BCLK,
						    BCLK2_RATE,
						    bells->asyncclk_rate);
			अगर (ret < 0)
				pr_err("Failed to start FLL: %d\n", ret);
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bells_set_bias_level_post(काष्ठा snd_soc_card *card,
				     काष्ठा snd_soc_dapm_context *dapm,
				     क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd;
	काष्ठा snd_soc_dai *codec_dai;
	काष्ठा snd_soc_component *component;
	काष्ठा bells_drvdata *bells = card->drvdata;
	पूर्णांक ret;

	rtd = snd_soc_get_pcm_runसमय(card, &card->dai_link[DAI_DSP_CODEC]);
	codec_dai = asoc_rtd_to_codec(rtd, 0);
	component = codec_dai->component;

	अगर (dapm->dev != codec_dai->dev)
		वापस 0;

	चयन (level) अणु
	हाल SND_SOC_BIAS_STANDBY:
		ret = snd_soc_component_set_pll(component, WM5102_FLL1, 0, 0, 0);
		अगर (ret < 0) अणु
			pr_err("Failed to stop FLL: %d\n", ret);
			वापस ret;
		पूर्ण

		अगर (bells->asyncclk_rate) अणु
			ret = snd_soc_component_set_pll(component, WM5102_FLL2,
						    0, 0, 0);
			अगर (ret < 0) अणु
				pr_err("Failed to stop FLL: %d\n", ret);
				वापस ret;
			पूर्ण
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	dapm->bias_level = level;

	वापस 0;
पूर्ण

अटल पूर्णांक bells_late_probe(काष्ठा snd_soc_card *card)
अणु
	काष्ठा bells_drvdata *bells = card->drvdata;
	काष्ठा snd_soc_pcm_runसमय *rtd;
	काष्ठा snd_soc_component *wm0010;
	काष्ठा snd_soc_component *component;
	काष्ठा snd_soc_dai *aअगर1_dai;
	काष्ठा snd_soc_dai *aअगर2_dai;
	काष्ठा snd_soc_dai *aअगर3_dai;
	काष्ठा snd_soc_dai *wm9081_dai;
	पूर्णांक ret;

	rtd = snd_soc_get_pcm_runसमय(card, &card->dai_link[DAI_AP_DSP]);
	wm0010 = asoc_rtd_to_codec(rtd, 0)->component;

	rtd = snd_soc_get_pcm_runसमय(card, &card->dai_link[DAI_DSP_CODEC]);
	component = asoc_rtd_to_codec(rtd, 0)->component;
	aअगर1_dai = asoc_rtd_to_codec(rtd, 0);

	ret = snd_soc_component_set_sysclk(component, ARIZONA_CLK_SYSCLK,
				       ARIZONA_CLK_SRC_FLL1,
				       bells->sysclk_rate,
				       SND_SOC_CLOCK_IN);
	अगर (ret != 0) अणु
		dev_err(component->dev, "Failed to set SYSCLK: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_component_set_sysclk(wm0010, 0, 0, SYS_MCLK_RATE, 0);
	अगर (ret != 0) अणु
		dev_err(wm0010->dev, "Failed to set WM0010 clock: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dai_set_sysclk(aअगर1_dai, ARIZONA_CLK_SYSCLK, 0, 0);
	अगर (ret != 0)
		dev_err(aअगर1_dai->dev, "Failed to set AIF1 clock: %d\n", ret);

	ret = snd_soc_component_set_sysclk(component, ARIZONA_CLK_OPCLK, 0,
				       SYS_MCLK_RATE, SND_SOC_CLOCK_OUT);
	अगर (ret != 0)
		dev_err(component->dev, "Failed to set OPCLK: %d\n", ret);

	अगर (card->num_rtd == DAI_CODEC_CP)
		वापस 0;

	ret = snd_soc_component_set_sysclk(component, ARIZONA_CLK_ASYNCCLK,
				       ARIZONA_CLK_SRC_FLL2,
				       bells->asyncclk_rate,
				       SND_SOC_CLOCK_IN);
	अगर (ret != 0) अणु
		dev_err(component->dev, "Failed to set ASYNCCLK: %d\n", ret);
		वापस ret;
	पूर्ण

	rtd = snd_soc_get_pcm_runसमय(card, &card->dai_link[DAI_CODEC_CP]);
	aअगर2_dai = asoc_rtd_to_cpu(rtd, 0);

	ret = snd_soc_dai_set_sysclk(aअगर2_dai, ARIZONA_CLK_ASYNCCLK, 0, 0);
	अगर (ret != 0) अणु
		dev_err(aअगर2_dai->dev, "Failed to set AIF2 clock: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (card->num_rtd == DAI_CODEC_SUB)
		वापस 0;

	rtd = snd_soc_get_pcm_runसमय(card, &card->dai_link[DAI_CODEC_SUB]);
	aअगर3_dai = asoc_rtd_to_cpu(rtd, 0);
	wm9081_dai = asoc_rtd_to_codec(rtd, 0);

	ret = snd_soc_dai_set_sysclk(aअगर3_dai, ARIZONA_CLK_SYSCLK, 0, 0);
	अगर (ret != 0) अणु
		dev_err(aअगर1_dai->dev, "Failed to set AIF1 clock: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_component_set_sysclk(wm9081_dai->component, WM9081_SYSCLK_MCLK,
				       0, SYS_MCLK_RATE, 0);
	अगर (ret != 0) अणु
		dev_err(wm9081_dai->dev, "Failed to set MCLK: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_pcm_stream baseband_params = अणु
	.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE,
	.rate_min = 8000,
	.rate_max = 8000,
	.channels_min = 2,
	.channels_max = 2,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_pcm_stream sub_params = अणु
	.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE,
	.rate_min = SYS_AUDIO_RATE,
	.rate_max = SYS_AUDIO_RATE,
	.channels_min = 2,
	.channels_max = 2,
पूर्ण;

SND_SOC_DAILINK_DEFS(wm2200_cpu_dsp,
	DAILINK_COMP_ARRAY(COMP_CPU("samsung-i2s.0")),
	DAILINK_COMP_ARRAY(COMP_CODEC("spi0.0", "wm0010-sdi1")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("samsung-i2s.0")));

SND_SOC_DAILINK_DEFS(wm2200_dsp_codec,
	DAILINK_COMP_ARRAY(COMP_CPU("wm0010-sdi2")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm2200.1-003a", "wm2200")));

अटल काष्ठा snd_soc_dai_link bells_dai_wm2200[] = अणु
	अणु
		.name = "CPU-DSP",
		.stream_name = "CPU-DSP",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBM_CFM,
		SND_SOC_DAILINK_REG(wm2200_cpu_dsp),
	पूर्ण,
	अणु
		.name = "DSP-CODEC",
		.stream_name = "DSP-CODEC",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBM_CFM,
		.params = &sub_params,
		.ignore_suspend = 1,
		SND_SOC_DAILINK_REG(wm2200_dsp_codec),
	पूर्ण,
पूर्ण;

SND_SOC_DAILINK_DEFS(wm5102_cpu_dsp,
	DAILINK_COMP_ARRAY(COMP_CPU("samsung-i2s.0")),
	DAILINK_COMP_ARRAY(COMP_CODEC("spi0.0", "wm0010-sdi1")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("samsung-i2s.0")));

SND_SOC_DAILINK_DEFS(wm5102_dsp_codec,
	DAILINK_COMP_ARRAY(COMP_CPU("wm0010-sdi2")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm5102-codec", "wm5102-aif1")));

SND_SOC_DAILINK_DEFS(wm5102_baseband,
	DAILINK_COMP_ARRAY(COMP_CPU("wm5102-aif2")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm1250-ev1.1-0027", "wm1250-ev1")));

SND_SOC_DAILINK_DEFS(wm5102_sub,
	DAILINK_COMP_ARRAY(COMP_CPU("wm5102-aif3")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm9081.1-006c", "wm9081-hifi")));

अटल काष्ठा snd_soc_dai_link bells_dai_wm5102[] = अणु
	अणु
		.name = "CPU-DSP",
		.stream_name = "CPU-DSP",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBM_CFM,
		SND_SOC_DAILINK_REG(wm5102_cpu_dsp),
	पूर्ण,
	अणु
		.name = "DSP-CODEC",
		.stream_name = "DSP-CODEC",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBM_CFM,
		.params = &sub_params,
		.ignore_suspend = 1,
		SND_SOC_DAILINK_REG(wm5102_dsp_codec),
	पूर्ण,
	अणु
		.name = "Baseband",
		.stream_name = "Baseband",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBM_CFM,
		.ignore_suspend = 1,
		.params = &baseband_params,
		SND_SOC_DAILINK_REG(wm5102_baseband),
	पूर्ण,
	अणु
		.name = "Sub",
		.stream_name = "Sub",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBS_CFS,
		.ignore_suspend = 1,
		.params = &sub_params,
		SND_SOC_DAILINK_REG(wm5102_sub),
	पूर्ण,
पूर्ण;

SND_SOC_DAILINK_DEFS(wm5110_cpu_dsp,
	DAILINK_COMP_ARRAY(COMP_CPU("samsung-i2s.0")),
	DAILINK_COMP_ARRAY(COMP_CODEC("spi0.0", "wm0010-sdi1")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("samsung-i2s.0")));

SND_SOC_DAILINK_DEFS(wm5110_dsp_codec,
	DAILINK_COMP_ARRAY(COMP_CPU("wm0010-sdi2")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm5110-codec", "wm5110-aif1")));

SND_SOC_DAILINK_DEFS(wm5110_baseband,
	DAILINK_COMP_ARRAY(COMP_CPU("wm5110-aif2")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm1250-ev1.1-0027", "wm1250-ev1")));


SND_SOC_DAILINK_DEFS(wm5110_sub,
	DAILINK_COMP_ARRAY(COMP_CPU("wm5110-aif3")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm9081.1-006c", "wm9081-hifi")));

अटल काष्ठा snd_soc_dai_link bells_dai_wm5110[] = अणु
	अणु
		.name = "CPU-DSP",
		.stream_name = "CPU-DSP",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBM_CFM,
		SND_SOC_DAILINK_REG(wm5110_cpu_dsp),
	पूर्ण,
	अणु
		.name = "DSP-CODEC",
		.stream_name = "DSP-CODEC",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBM_CFM,
		.params = &sub_params,
		.ignore_suspend = 1,
		SND_SOC_DAILINK_REG(wm5110_dsp_codec),
	पूर्ण,
	अणु
		.name = "Baseband",
		.stream_name = "Baseband",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBM_CFM,
		.ignore_suspend = 1,
		.params = &baseband_params,
		SND_SOC_DAILINK_REG(wm5110_baseband),
	पूर्ण,
	अणु
		.name = "Sub",
		.stream_name = "Sub",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
				| SND_SOC_DAIFMT_CBS_CFS,
		.ignore_suspend = 1,
		.params = &sub_params,
		SND_SOC_DAILINK_REG(wm5110_sub),
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_codec_conf bells_codec_conf[] = अणु
	अणु
		.dlc = COMP_CODEC_CONF("wm9081.1-006c"),
		.name_prefix = "Sub",
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_dapm_widget bells_widमाला_लो[] = अणु
	SND_SOC_DAPM_MIC("DMIC", शून्य),
पूर्ण;

अटल काष्ठा snd_soc_dapm_route bells_routes[] = अणु
	अणु "Sub CLK_SYS", शून्य, "OPCLK" पूर्ण,
	अणु "CLKIN", शून्य, "OPCLK" पूर्ण,

	अणु "DMIC", शून्य, "MICBIAS2" पूर्ण,
	अणु "IN2L", शून्य, "DMIC" पूर्ण,
	अणु "IN2R", शून्य, "DMIC" पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_card bells_cards[] = अणु
	अणु
		.name = "Bells WM2200",
		.owner = THIS_MODULE,
		.dai_link = bells_dai_wm2200,
		.num_links = ARRAY_SIZE(bells_dai_wm2200),
		.codec_conf = bells_codec_conf,
		.num_configs = ARRAY_SIZE(bells_codec_conf),

		.late_probe = bells_late_probe,

		.dapm_widमाला_लो = bells_widमाला_लो,
		.num_dapm_widमाला_लो = ARRAY_SIZE(bells_widमाला_लो),
		.dapm_routes = bells_routes,
		.num_dapm_routes = ARRAY_SIZE(bells_routes),

		.set_bias_level = bells_set_bias_level,
		.set_bias_level_post = bells_set_bias_level_post,

		.drvdata = &wm2200_drvdata,
	पूर्ण,
	अणु
		.name = "Bells WM5102",
		.owner = THIS_MODULE,
		.dai_link = bells_dai_wm5102,
		.num_links = ARRAY_SIZE(bells_dai_wm5102),
		.codec_conf = bells_codec_conf,
		.num_configs = ARRAY_SIZE(bells_codec_conf),

		.late_probe = bells_late_probe,

		.dapm_widमाला_लो = bells_widमाला_लो,
		.num_dapm_widमाला_लो = ARRAY_SIZE(bells_widमाला_लो),
		.dapm_routes = bells_routes,
		.num_dapm_routes = ARRAY_SIZE(bells_routes),

		.set_bias_level = bells_set_bias_level,
		.set_bias_level_post = bells_set_bias_level_post,

		.drvdata = &wm5102_drvdata,
	पूर्ण,
	अणु
		.name = "Bells WM5110",
		.owner = THIS_MODULE,
		.dai_link = bells_dai_wm5110,
		.num_links = ARRAY_SIZE(bells_dai_wm5110),
		.codec_conf = bells_codec_conf,
		.num_configs = ARRAY_SIZE(bells_codec_conf),

		.late_probe = bells_late_probe,

		.dapm_widमाला_लो = bells_widमाला_लो,
		.num_dapm_widमाला_लो = ARRAY_SIZE(bells_widमाला_लो),
		.dapm_routes = bells_routes,
		.num_dapm_routes = ARRAY_SIZE(bells_routes),

		.set_bias_level = bells_set_bias_level,
		.set_bias_level_post = bells_set_bias_level_post,

		.drvdata = &wm5110_drvdata,
	पूर्ण,
पूर्ण;

अटल पूर्णांक bells_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	bells_cards[pdev->id].dev = &pdev->dev;

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, &bells_cards[pdev->id]);
	अगर (ret)
		dev_err(&pdev->dev,
			"snd_soc_register_card(%s) failed: %d\n",
			bells_cards[pdev->id].name, ret);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver bells_driver = अणु
	.driver = अणु
		.name = "bells",
		.pm = &snd_soc_pm_ops,
	पूर्ण,
	.probe = bells_probe,
पूर्ण;

module_platक्रमm_driver(bells_driver);

MODULE_DESCRIPTION("Bells audio support");
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:bells");
