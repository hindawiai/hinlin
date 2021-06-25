<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (C) 2015 - 2016 Samsung Electronics Co., Ltd.
//
// Authors: Inha Song <ideal.song@samsung.com>
//          Sylwester Nawrocki <s.nawrocki@samsung.com>

#समावेश <linux/clk.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

#समावेश "i2s.h"
#समावेश "../codecs/wm5110.h"

/*
 * The source घड़ी is XCLKOUT with its mux set to the बाह्यal fixed rate
 * oscillator (XXTI).
 */
#घोषणा MCLK_RATE	24000000U

#घोषणा TM2_DAI_AIF1	0
#घोषणा TM2_DAI_AIF2	1

काष्ठा पंचांग2_machine_priv अणु
	काष्ठा snd_soc_component *component;
	अचिन्हित पूर्णांक sysclk_rate;
	काष्ठा gpio_desc *gpio_mic_bias;
पूर्ण;

अटल पूर्णांक पंचांग2_start_sysclk(काष्ठा snd_soc_card *card)
अणु
	काष्ठा पंचांग2_machine_priv *priv = snd_soc_card_get_drvdata(card);
	काष्ठा snd_soc_component *component = priv->component;
	पूर्णांक ret;

	ret = snd_soc_component_set_pll(component, WM5110_FLL1_REFCLK,
				    ARIZONA_FLL_SRC_MCLK1,
				    MCLK_RATE,
				    priv->sysclk_rate);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to set FLL1 source: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_component_set_pll(component, WM5110_FLL1,
				    ARIZONA_FLL_SRC_MCLK1,
				    MCLK_RATE,
				    priv->sysclk_rate);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to start FLL1: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_component_set_sysclk(component, ARIZONA_CLK_SYSCLK,
				       ARIZONA_CLK_SRC_FLL1,
				       priv->sysclk_rate,
				       SND_SOC_CLOCK_IN);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to set SYSCLK source: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पंचांग2_stop_sysclk(काष्ठा snd_soc_card *card)
अणु
	काष्ठा पंचांग2_machine_priv *priv = snd_soc_card_get_drvdata(card);
	काष्ठा snd_soc_component *component = priv->component;
	पूर्णांक ret;

	ret = snd_soc_component_set_pll(component, WM5110_FLL1, 0, 0, 0);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to stop FLL1: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_component_set_sysclk(component, ARIZONA_CLK_SYSCLK,
				       ARIZONA_CLK_SRC_FLL1, 0, 0);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to stop SYSCLK: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पंचांग2_aअगर1_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_component *component = asoc_rtd_to_codec(rtd, 0)->component;
	काष्ठा पंचांग2_machine_priv *priv = snd_soc_card_get_drvdata(rtd->card);

	चयन (params_rate(params)) अणु
	हाल 4000:
	हाल 8000:
	हाल 12000:
	हाल 16000:
	हाल 24000:
	हाल 32000:
	हाल 48000:
	हाल 96000:
	हाल 192000:
		/* Highest possible SYSCLK frequency: 147.456MHz */
		priv->sysclk_rate = 147456000U;
		अवरोध;
	हाल 11025:
	हाल 22050:
	हाल 44100:
	हाल 88200:
	हाल 176400:
		/* Highest possible SYSCLK frequency: 135.4752 MHz */
		priv->sysclk_rate = 135475200U;
		अवरोध;
	शेष:
		dev_err(component->dev, "Not supported sample rate: %d\n",
			params_rate(params));
		वापस -EINVAL;
	पूर्ण

	वापस पंचांग2_start_sysclk(rtd->card);
पूर्ण

अटल काष्ठा snd_soc_ops पंचांग2_aअगर1_ops = अणु
	.hw_params = पंचांग2_aअगर1_hw_params,
पूर्ण;

अटल पूर्णांक पंचांग2_aअगर2_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_component *component = asoc_rtd_to_codec(rtd, 0)->component;
	अचिन्हित पूर्णांक asyncclk_rate;
	पूर्णांक ret;

	चयन (params_rate(params)) अणु
	हाल 8000:
	हाल 12000:
	हाल 16000:
		/* Highest possible ASYNCCLK frequency: 49.152MHz */
		asyncclk_rate = 49152000U;
		अवरोध;
	हाल 11025:
		/* Highest possible ASYNCCLK frequency: 45.1584 MHz */
		asyncclk_rate = 45158400U;
		अवरोध;
	शेष:
		dev_err(component->dev, "Not supported sample rate: %d\n",
			params_rate(params));
		वापस -EINVAL;
	पूर्ण

	ret = snd_soc_component_set_pll(component, WM5110_FLL2_REFCLK,
				    ARIZONA_FLL_SRC_MCLK1,
				    MCLK_RATE,
				    asyncclk_rate);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to set FLL2 source: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_component_set_pll(component, WM5110_FLL2,
				    ARIZONA_FLL_SRC_MCLK1,
				    MCLK_RATE,
				    asyncclk_rate);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to start FLL2: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_component_set_sysclk(component, ARIZONA_CLK_ASYNCCLK,
				       ARIZONA_CLK_SRC_FLL2,
				       asyncclk_rate,
				       SND_SOC_CLOCK_IN);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to set ASYNCCLK source: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पंचांग2_aअगर2_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_component *component = asoc_rtd_to_codec(rtd, 0)->component;
	पूर्णांक ret;

	/* disable FLL2 */
	ret = snd_soc_component_set_pll(component, WM5110_FLL2, ARIZONA_FLL_SRC_MCLK1,
				    0, 0);
	अगर (ret < 0)
		dev_err(component->dev, "Failed to stop FLL2: %d\n", ret);

	वापस ret;
पूर्ण

अटल काष्ठा snd_soc_ops पंचांग2_aअगर2_ops = अणु
	.hw_params = पंचांग2_aअगर2_hw_params,
	.hw_मुक्त = पंचांग2_aअगर2_hw_मुक्त,
पूर्ण;

अटल पूर्णांक पंचांग2_hdmi_hw_params(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	अचिन्हित पूर्णांक bfs;
	पूर्णांक bitwidth, ret;

	bitwidth = snd_pcm_क्रमmat_width(params_क्रमmat(params));
	अगर (bitwidth < 0) अणु
		dev_err(rtd->card->dev, "Invalid bit-width: %d\n", bitwidth);
		वापस bitwidth;
	पूर्ण

	चयन (bitwidth) अणु
	हाल 48:
		bfs = 64;
		अवरोध;
	हाल 16:
		bfs = 32;
		अवरोध;
	शेष:
		dev_err(rtd->card->dev, "Unsupported bit-width: %d\n", bitwidth);
		वापस -EINVAL;
	पूर्ण

	चयन (params_rate(params)) अणु
	हाल 48000:
	हाल 96000:
	हाल 192000:
		अवरोध;
	शेष:
		dev_err(rtd->card->dev, "Unsupported sample rate: %d\n",
			params_rate(params));
		वापस -EINVAL;
	पूर्ण

	ret = snd_soc_dai_set_sysclk(cpu_dai, SAMSUNG_I2S_OPCLK,
					0, SAMSUNG_I2S_OPCLK_PCLK);
	अगर (ret < 0)
		वापस ret;

	ret = snd_soc_dai_set_clkभाग(cpu_dai, SAMSUNG_I2S_DIV_BCLK, bfs);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_ops पंचांग2_hdmi_ops = अणु
	.hw_params = पंचांग2_hdmi_hw_params,
पूर्ण;

अटल पूर्णांक पंचांग2_mic_bias(काष्ठा snd_soc_dapm_widget *w,
				काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_card *card = w->dapm->card;
	काष्ठा पंचांग2_machine_priv *priv = snd_soc_card_get_drvdata(card);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		gpiod_set_value_cansleep(priv->gpio_mic_bias,  1);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		gpiod_set_value_cansleep(priv->gpio_mic_bias,  0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पंचांग2_set_bias_level(काष्ठा snd_soc_card *card,
				काष्ठा snd_soc_dapm_context *dapm,
				क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd;

	rtd = snd_soc_get_pcm_runसमय(card, &card->dai_link[0]);

	अगर (dapm->dev != asoc_rtd_to_codec(rtd, 0)->dev)
		वापस 0;

	चयन (level) अणु
	हाल SND_SOC_BIAS_STANDBY:
		अगर (card->dapm.bias_level == SND_SOC_BIAS_OFF)
			पंचांग2_start_sysclk(card);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		पंचांग2_stop_sysclk(card);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_aux_dev पंचांग2_speaker_amp_dev;

अटल पूर्णांक पंचांग2_late_probe(काष्ठा snd_soc_card *card)
अणु
	काष्ठा पंचांग2_machine_priv *priv = snd_soc_card_get_drvdata(card);
	अचिन्हित पूर्णांक ch_map[] = अणु 0, 1 पूर्ण;
	काष्ठा snd_soc_dai *amp_pdm_dai;
	काष्ठा snd_soc_pcm_runसमय *rtd;
	काष्ठा snd_soc_dai *aअगर1_dai;
	काष्ठा snd_soc_dai *aअगर2_dai;
	पूर्णांक ret;

	rtd = snd_soc_get_pcm_runसमय(card, &card->dai_link[TM2_DAI_AIF1]);
	aअगर1_dai = asoc_rtd_to_codec(rtd, 0);
	priv->component = asoc_rtd_to_codec(rtd, 0)->component;

	ret = snd_soc_dai_set_sysclk(aअगर1_dai, ARIZONA_CLK_SYSCLK, 0, 0);
	अगर (ret < 0) अणु
		dev_err(aअगर1_dai->dev, "Failed to set SYSCLK: %d\n", ret);
		वापस ret;
	पूर्ण

	rtd = snd_soc_get_pcm_runसमय(card, &card->dai_link[TM2_DAI_AIF2]);
	aअगर2_dai = asoc_rtd_to_codec(rtd, 0);

	ret = snd_soc_dai_set_sysclk(aअगर2_dai, ARIZONA_CLK_ASYNCCLK, 0, 0);
	अगर (ret < 0) अणु
		dev_err(aअगर2_dai->dev, "Failed to set ASYNCCLK: %d\n", ret);
		वापस ret;
	पूर्ण

	amp_pdm_dai = snd_soc_find_dai(&पंचांग2_speaker_amp_dev.dlc);
	अगर (!amp_pdm_dai)
		वापस -ENODEV;

	/* Set the MAX98504 V/I sense PDM Tx DAI channel mapping */
	ret = snd_soc_dai_set_channel_map(amp_pdm_dai, ARRAY_SIZE(ch_map),
					  ch_map, 0, शून्य);
	अगर (ret < 0)
		वापस ret;

	ret = snd_soc_dai_set_tdm_slot(amp_pdm_dai, 0x3, 0x0, 2, 16);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new पंचांग2_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("HP"),
	SOC_DAPM_PIN_SWITCH("SPK"),
	SOC_DAPM_PIN_SWITCH("RCV"),
	SOC_DAPM_PIN_SWITCH("VPS"),
	SOC_DAPM_PIN_SWITCH("HDMI"),

	SOC_DAPM_PIN_SWITCH("Main Mic"),
	SOC_DAPM_PIN_SWITCH("Sub Mic"),
	SOC_DAPM_PIN_SWITCH("Third Mic"),

	SOC_DAPM_PIN_SWITCH("Headset Mic"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget पंचांग2_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("HP", शून्य),
	SND_SOC_DAPM_SPK("SPK", शून्य),
	SND_SOC_DAPM_SPK("RCV", शून्य),
	SND_SOC_DAPM_LINE("VPS", शून्य),
	SND_SOC_DAPM_LINE("HDMI", शून्य),

	SND_SOC_DAPM_MIC("Main Mic", पंचांग2_mic_bias),
	SND_SOC_DAPM_MIC("Sub Mic", शून्य),
	SND_SOC_DAPM_MIC("Third Mic", शून्य),

	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver पंचांग2_component = अणु
	.name	= "tm2-audio",
पूर्ण;

अटल काष्ठा snd_soc_dai_driver पंचांग2_ext_dai[] = अणु
	अणु
		.name = "Voice call",
		.playback = अणु
			.channels_min = 1,
			.channels_max = 4,
			.rate_min = 8000,
			.rate_max = 48000,
			.rates = (SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000 |
					SNDRV_PCM_RATE_48000),
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
		पूर्ण,
		.capture = अणु
			.channels_min = 1,
			.channels_max = 4,
			.rate_min = 8000,
			.rate_max = 48000,
			.rates = (SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000 |
					SNDRV_PCM_RATE_48000),
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "Bluetooth",
		.playback = अणु
			.channels_min = 1,
			.channels_max = 4,
			.rate_min = 8000,
			.rate_max = 16000,
			.rates = (SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000),
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
		पूर्ण,
		.capture = अणु
			.channels_min = 1,
			.channels_max = 2,
			.rate_min = 8000,
			.rate_max = 16000,
			.rates = (SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000),
			.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
		पूर्ण,
	पूर्ण,
पूर्ण;

SND_SOC_DAILINK_DEFS(aअगर1,
	DAILINK_COMP_ARRAY(COMP_CPU(SAMSUNG_I2S_DAI)),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "wm5110-aif1")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(voice,
	DAILINK_COMP_ARRAY(COMP_CPU(SAMSUNG_I2S_DAI)),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "wm5110-aif2")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(bt,
	DAILINK_COMP_ARRAY(COMP_CPU(SAMSUNG_I2S_DAI)),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "wm5110-aif3")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(hdmi,
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

अटल काष्ठा snd_soc_dai_link पंचांग2_dai_links[] = अणु
	अणु
		.name		= "WM5110 AIF1",
		.stream_name	= "HiFi Primary",
		.ops		= &पंचांग2_aअगर1_ops,
		.dai_fmt	= SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
				  SND_SOC_DAIFMT_CBM_CFM,
		SND_SOC_DAILINK_REG(aअगर1),
	पूर्ण, अणु
		.name		= "WM5110 Voice",
		.stream_name	= "Voice call",
		.ops		= &पंचांग2_aअगर2_ops,
		.dai_fmt	= SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
				  SND_SOC_DAIFMT_CBM_CFM,
		.ignore_suspend = 1,
		SND_SOC_DAILINK_REG(voice),
	पूर्ण, अणु
		.name		= "WM5110 BT",
		.stream_name	= "Bluetooth",
		.dai_fmt	= SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
				  SND_SOC_DAIFMT_CBM_CFM,
		.ignore_suspend = 1,
		SND_SOC_DAILINK_REG(bt),
	पूर्ण, अणु
		.name		= "HDMI",
		.stream_name	= "i2s1",
		.ops		= &पंचांग2_hdmi_ops,
		.dai_fmt	= SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
				  SND_SOC_DAIFMT_CBS_CFS,
		SND_SOC_DAILINK_REG(hdmi),
	पूर्ण
पूर्ण;

अटल काष्ठा snd_soc_card पंचांग2_card = अणु
	.owner			= THIS_MODULE,

	.dai_link		= पंचांग2_dai_links,
	.controls		= पंचांग2_controls,
	.num_controls		= ARRAY_SIZE(पंचांग2_controls),
	.dapm_widमाला_लो		= पंचांग2_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(पंचांग2_dapm_widमाला_लो),
	.aux_dev		= &पंचांग2_speaker_amp_dev,
	.num_aux_devs		= 1,

	.late_probe		= पंचांग2_late_probe,
	.set_bias_level		= पंचांग2_set_bias_level,
पूर्ण;

अटल पूर्णांक पंचांग2_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *cpu_dai_node[2] = अणुपूर्ण;
	काष्ठा device_node *codec_dai_node[2] = अणुपूर्ण;
	स्थिर अक्षर *cells_name = शून्य;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा snd_soc_card *card = &पंचांग2_card;
	काष्ठा पंचांग2_machine_priv *priv;
	काष्ठा snd_soc_dai_link *dai_link;
	पूर्णांक num_codecs, ret, i;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	snd_soc_card_set_drvdata(card, priv);
	card->dev = dev;

	priv->gpio_mic_bias = devm_gpiod_get(dev, "mic-bias", GPIOD_OUT_HIGH);
	अगर (IS_ERR(priv->gpio_mic_bias)) अणु
		dev_err(dev, "Failed to get mic bias gpio\n");
		वापस PTR_ERR(priv->gpio_mic_bias);
	पूर्ण

	ret = snd_soc_of_parse_card_name(card, "model");
	अगर (ret < 0) अणु
		dev_err(dev, "Card name is not specified\n");
		वापस ret;
	पूर्ण

	ret = snd_soc_of_parse_audio_routing(card, "samsung,audio-routing");
	अगर (ret < 0) अणु
		dev_err(dev, "Audio routing is not specified or invalid\n");
		वापस ret;
	पूर्ण

	card->aux_dev[0].dlc.of_node = of_parse_phandle(dev->of_node,
							"audio-amplifier", 0);
	अगर (!card->aux_dev[0].dlc.of_node) अणु
		dev_err(dev, "audio-amplifier property invalid or missing\n");
		वापस -EINVAL;
	पूर्ण

	num_codecs = of_count_phandle_with_args(dev->of_node, "audio-codec",
						 शून्य);

	/* Skip the HDMI link अगर not specअगरied in DT */
	अगर (num_codecs > 1) अणु
		card->num_links = ARRAY_SIZE(पंचांग2_dai_links);
		cells_name = "#sound-dai-cells";
	पूर्ण अन्यथा अणु
		card->num_links = ARRAY_SIZE(पंचांग2_dai_links) - 1;
	पूर्ण

	क्रम (i = 0; i < num_codecs; i++) अणु
		काष्ठा of_phandle_args args;

		ret = of_parse_phandle_with_args(dev->of_node, "i2s-controller",
						 cells_name, i, &args);
		अगर (ret) अणु
			dev_err(dev, "i2s-controller property parse error: %d\n", i);
			ret = -EINVAL;
			जाओ dai_node_put;
		पूर्ण
		cpu_dai_node[i] = args.np;

		codec_dai_node[i] = of_parse_phandle(dev->of_node,
						     "audio-codec", i);
		अगर (!codec_dai_node[i]) अणु
			dev_err(dev, "audio-codec property parse error\n");
			ret = -EINVAL;
			जाओ dai_node_put;
		पूर्ण
	पूर्ण

	/* Initialize WM5110 - I2S and HDMI - I2S1 DAI links */
	क्रम_each_card_prelinks(card, i, dai_link) अणु
		अचिन्हित पूर्णांक dai_index = 0; /* WM5110 */

		dai_link->cpus->name = शून्य;
		dai_link->platक्रमms->name = शून्य;

		अगर (num_codecs > 1 && i == card->num_links - 1)
			dai_index = 1; /* HDMI */

		dai_link->codecs->of_node = codec_dai_node[dai_index];
		dai_link->cpus->of_node = cpu_dai_node[dai_index];
		dai_link->platक्रमms->of_node = cpu_dai_node[dai_index];
	पूर्ण

	अगर (num_codecs > 1) अणु
		काष्ठा of_phandle_args args;

		/* HDMI DAI link (I2S1) */
		i = card->num_links - 1;

		ret = of_parse_phandle_with_fixed_args(dev->of_node,
						"audio-codec", 0, 1, &args);
		अगर (ret) अणु
			dev_err(dev, "audio-codec property parse error\n");
			जाओ dai_node_put;
		पूर्ण

		ret = snd_soc_get_dai_name(&args, &card->dai_link[i].codecs->dai_name);
		अगर (ret) अणु
			dev_err(dev, "Unable to get codec_dai_name\n");
			जाओ dai_node_put;
		पूर्ण
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(dev, &पंचांग2_component,
				पंचांग2_ext_dai, ARRAY_SIZE(पंचांग2_ext_dai));
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to register component: %d\n", ret);
		जाओ dai_node_put;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_card(dev, card);
	अगर (ret < 0) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Failed to register card: %d\n", ret);
		जाओ dai_node_put;
	पूर्ण

dai_node_put:
	क्रम (i = 0; i < num_codecs; i++) अणु
		of_node_put(codec_dai_node[i]);
		of_node_put(cpu_dai_node[i]);
	पूर्ण

	of_node_put(card->aux_dev[0].dlc.of_node);

	वापस ret;
पूर्ण

अटल पूर्णांक पंचांग2_pm_prepare(काष्ठा device *dev)
अणु
	काष्ठा snd_soc_card *card = dev_get_drvdata(dev);

	वापस पंचांग2_stop_sysclk(card);
पूर्ण

अटल व्योम पंचांग2_pm_complete(काष्ठा device *dev)
अणु
	काष्ठा snd_soc_card *card = dev_get_drvdata(dev);

	पंचांग2_start_sysclk(card);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops पंचांग2_pm_ops = अणु
	.prepare	= पंचांग2_pm_prepare,
	.suspend	= snd_soc_suspend,
	.resume		= snd_soc_resume,
	.complete	= पंचांग2_pm_complete,
	.मुक्तze		= snd_soc_suspend,
	.thaw		= snd_soc_resume,
	.घातeroff	= snd_soc_घातeroff,
	.restore	= snd_soc_resume,
पूर्ण;

अटल स्थिर काष्ठा of_device_id पंचांग2_of_match[] = अणु
	अणु .compatible = "samsung,tm2-audio" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, पंचांग2_of_match);

अटल काष्ठा platक्रमm_driver पंचांग2_driver = अणु
	.driver = अणु
		.name		= "tm2-audio",
		.pm		= &पंचांग2_pm_ops,
		.of_match_table	= पंचांग2_of_match,
	पूर्ण,
	.probe	= पंचांग2_probe,
पूर्ण;
module_platक्रमm_driver(पंचांग2_driver);

MODULE_AUTHOR("Inha Song <ideal.song@samsung.com>");
MODULE_DESCRIPTION("ALSA SoC Exynos TM2 Audio Support");
MODULE_LICENSE("GPL v2");
