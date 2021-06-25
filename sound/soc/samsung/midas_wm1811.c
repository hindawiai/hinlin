<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Midas audio support
//
// Copyright (C) 2018 Simon Shields <simon@lineageos.org>
// Copyright (C) 2020 Samsung Electronics Co., Ltd.

#समावेश <linux/clk.h>
#समावेश <linux/mfd/wm8994/रेजिस्टरs.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <sound/jack.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>

#समावेश "i2s.h"
#समावेश "../codecs/wm8994.h"

/*
 * The MCLK1 घड़ी source is XCLKOUT with its mux set to the बाह्यal fixed rate
 * oscillator (XXTI).
 */
#घोषणा MCLK1_RATE 24000000U
#घोषणा MCLK2_RATE 32768U
#घोषणा DEFAULT_FLL1_RATE 11289600U

काष्ठा midas_priv अणु
	काष्ठा regulator *reg_mic_bias;
	काष्ठा regulator *reg_submic_bias;
	काष्ठा gpio_desc *gpio_fm_sel;
	काष्ठा gpio_desc *gpio_lineout_sel;
	अचिन्हित पूर्णांक fll1_rate;

	काष्ठा snd_soc_jack headset_jack;
पूर्ण;

अटल पूर्णांक midas_start_fll1(काष्ठा snd_soc_pcm_runसमय *rtd, अचिन्हित पूर्णांक rate)
अणु
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा midas_priv *priv = snd_soc_card_get_drvdata(card);
	काष्ठा snd_soc_dai *aअगर1_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	पूर्णांक ret;

	अगर (!rate)
		rate = priv->fll1_rate;
	/*
	 * If no new rate is requested, set FLL1 to a sane शेष क्रम jack
	 * detection.
	 */
	अगर (!rate)
		rate = DEFAULT_FLL1_RATE;

	अगर (rate != priv->fll1_rate && priv->fll1_rate) अणु
		/* जबतक reconfiguring, चयन to MCLK2 क्रम SYSCLK */
		ret = snd_soc_dai_set_sysclk(aअगर1_dai, WM8994_SYSCLK_MCLK2,
					     MCLK2_RATE, SND_SOC_CLOCK_IN);
		अगर (ret < 0) अणु
			dev_err(card->dev, "Unable to switch to MCLK2: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = snd_soc_dai_set_pll(aअगर1_dai, WM8994_FLL1, WM8994_FLL_SRC_MCLK1,
				  MCLK1_RATE, rate);
	अगर (ret < 0) अणु
		dev_err(card->dev, "Failed to set FLL1 rate: %d\n", ret);
		वापस ret;
	पूर्ण
	priv->fll1_rate = rate;

	ret = snd_soc_dai_set_sysclk(aअगर1_dai, WM8994_SYSCLK_FLL1,
				     priv->fll1_rate, SND_SOC_CLOCK_IN);
	अगर (ret < 0) अणु
		dev_err(card->dev, "Failed to set SYSCLK source: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dai_set_sysclk(cpu_dai, SAMSUNG_I2S_OPCLK, 0,
				     SAMSUNG_I2S_OPCLK_PCLK);
	अगर (ret < 0) अणु
		dev_err(card->dev, "Failed to set OPCLK source: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक midas_stop_fll1(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा midas_priv *priv = snd_soc_card_get_drvdata(card);
	काष्ठा snd_soc_dai *aअगर1_dai = asoc_rtd_to_codec(rtd, 0);
	पूर्णांक ret;

	ret = snd_soc_dai_set_sysclk(aअगर1_dai, WM8994_SYSCLK_MCLK2,
				     MCLK2_RATE, SND_SOC_CLOCK_IN);
	अगर (ret < 0) अणु
		dev_err(card->dev, "Unable to switch to MCLK2: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dai_set_pll(aअगर1_dai, WM8994_FLL1, 0, 0, 0);
	अगर (ret < 0) अणु
		dev_err(card->dev, "Unable to stop FLL1: %d\n", ret);
		वापस ret;
	पूर्ण

	priv->fll1_rate = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक midas_aअगर1_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd	= substream->निजी_data;
	अचिन्हित पूर्णांक pll_out;

	/* AIF1CLK should be at least 3MHz क्रम "optimal performance" */
	अगर (params_rate(params) == 8000 || params_rate(params) == 11025)
		pll_out = params_rate(params) * 512;
	अन्यथा
		pll_out = params_rate(params) * 256;

	वापस midas_start_fll1(rtd, pll_out);
पूर्ण

अटल काष्ठा snd_soc_ops midas_aअगर1_ops = अणु
	.hw_params = midas_aअगर1_hw_params,
पूर्ण;

/*
 * We only have a single बाह्यal speaker, so mix stereo data
 * to a single mono stream.
 */
अटल पूर्णांक midas_ext_spkmode(काष्ठा snd_soc_dapm_widget *w,
			     काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *codec = snd_soc_dapm_to_component(w->dapm);
	पूर्णांक ret = 0;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		ret = snd_soc_component_update_bits(codec, WM8994_SPKOUT_MIXERS,
				  WM8994_SPKMIXR_TO_SPKOUTL_MASK,
				  WM8994_SPKMIXR_TO_SPKOUTL);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		ret = snd_soc_component_update_bits(codec, WM8994_SPKOUT_MIXERS,
				  WM8994_SPKMIXR_TO_SPKOUTL_MASK,
				  0);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक midas_mic_bias(काष्ठा snd_soc_dapm_widget *w,
			  काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_card *card = w->dapm->card;
	काष्ठा midas_priv *priv = snd_soc_card_get_drvdata(card);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		वापस regulator_enable(priv->reg_mic_bias);
	हाल SND_SOC_DAPM_POST_PMD:
		वापस regulator_disable(priv->reg_mic_bias);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक midas_submic_bias(काष्ठा snd_soc_dapm_widget *w,
			     काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_card *card = w->dapm->card;
	काष्ठा midas_priv *priv = snd_soc_card_get_drvdata(card);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		वापस regulator_enable(priv->reg_submic_bias);
	हाल SND_SOC_DAPM_POST_PMD:
		वापस regulator_disable(priv->reg_submic_bias);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक midas_fm_set(काष्ठा snd_soc_dapm_widget *w,
			काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_card *card = w->dapm->card;
	काष्ठा midas_priv *priv = snd_soc_card_get_drvdata(card);

	अगर (!priv->gpio_fm_sel)
		वापस 0;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		gpiod_set_value_cansleep(priv->gpio_fm_sel, 1);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		gpiod_set_value_cansleep(priv->gpio_fm_sel, 0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक midas_line_set(काष्ठा snd_soc_dapm_widget *w,
			  काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_card *card = w->dapm->card;
	काष्ठा midas_priv *priv = snd_soc_card_get_drvdata(card);

	अगर (!priv->gpio_lineout_sel)
		वापस 0;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		gpiod_set_value_cansleep(priv->gpio_lineout_sel, 1);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		gpiod_set_value_cansleep(priv->gpio_lineout_sel, 0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new midas_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("HP"),

	SOC_DAPM_PIN_SWITCH("SPK"),
	SOC_DAPM_PIN_SWITCH("RCV"),

	SOC_DAPM_PIN_SWITCH("LINE"),
	SOC_DAPM_PIN_SWITCH("HDMI"),

	SOC_DAPM_PIN_SWITCH("Main Mic"),
	SOC_DAPM_PIN_SWITCH("Sub Mic"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),

	SOC_DAPM_PIN_SWITCH("FM In"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget midas_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("HP", शून्य),

	SND_SOC_DAPM_SPK("SPK", midas_ext_spkmode),
	SND_SOC_DAPM_SPK("RCV", शून्य),

	/* FIXME: toggle MAX77693 on i9300/i9305 */
	SND_SOC_DAPM_LINE("LINE", midas_line_set),
	SND_SOC_DAPM_LINE("HDMI", शून्य),
	SND_SOC_DAPM_LINE("FM In", midas_fm_set),

	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_MIC("Main Mic", midas_mic_bias),
	SND_SOC_DAPM_MIC("Sub Mic", midas_submic_bias),
पूर्ण;

अटल पूर्णांक midas_set_bias_level(काष्ठा snd_soc_card *card,
				काष्ठा snd_soc_dapm_context *dapm,
				क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = snd_soc_get_pcm_runसमय(card,
						  &card->dai_link[0]);
	काष्ठा snd_soc_dai *aअगर1_dai = asoc_rtd_to_codec(rtd, 0);

	अगर (dapm->dev != aअगर1_dai->dev)
		वापस 0;

	चयन (level) अणु
	हाल SND_SOC_BIAS_STANDBY:
		वापस midas_stop_fll1(rtd);
	हाल SND_SOC_BIAS_PREPARE:
		वापस midas_start_fll1(rtd, 0);
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक midas_late_probe(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = snd_soc_get_pcm_runसमय(card,
							&card->dai_link[0]);
	काष्ठा snd_soc_dai *aअगर1_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा midas_priv *priv = snd_soc_card_get_drvdata(card);
	पूर्णांक ret;

	/* Use MCLK2 as SYSCLK क्रम boot */
	ret = snd_soc_dai_set_sysclk(aअगर1_dai, WM8994_SYSCLK_MCLK2, MCLK2_RATE,
				     SND_SOC_CLOCK_IN);
	अगर (ret < 0) अणु
		dev_err(aअगर1_dai->dev, "Failed to switch to MCLK2: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_card_jack_new(card, "Headset",
			SND_JACK_HEADSET | SND_JACK_MECHANICAL |
			SND_JACK_BTN_0 | SND_JACK_BTN_1 | SND_JACK_BTN_2 |
			SND_JACK_BTN_3 | SND_JACK_BTN_4 | SND_JACK_BTN_5,
			&priv->headset_jack, शून्य, 0);
	अगर (ret)
		वापस ret;

	wm8958_mic_detect(aअगर1_dai->component, &priv->headset_jack,
			  शून्य, शून्य, शून्य, शून्य);
	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_dai_driver midas_ext_dai[] = अणु
	अणु
		.name = "Voice call",
		.playback = अणु
			.channels_min = 1,
			.channels_max = 2,
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
	अणु
		.name = "Bluetooth",
		.playback = अणु
			.channels_min = 1,
			.channels_max = 2,
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

अटल स्थिर काष्ठा snd_soc_component_driver midas_component = अणु
	.name	= "midas-audio",
पूर्ण;

SND_SOC_DAILINK_DEFS(wm1811_hअगरi,
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "wm8994-aif1")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(wm1811_voice,
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "wm8994-aif2")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(wm1811_bt,
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "wm8994-aif3")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

अटल काष्ठा snd_soc_dai_link midas_dai[] = अणु
	अणु
		.name = "WM8994 AIF1",
		.stream_name = "HiFi Primary",
		.ops = &midas_aअगर1_ops,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBM_CFM,
		SND_SOC_DAILINK_REG(wm1811_hअगरi),
	पूर्ण, अणु
		.name = "WM1811 Voice",
		.stream_name = "Voice call",
		.ignore_suspend = 1,
		SND_SOC_DAILINK_REG(wm1811_voice),
	पूर्ण, अणु
		.name = "WM1811 BT",
		.stream_name = "Bluetooth",
		.ignore_suspend = 1,
		SND_SOC_DAILINK_REG(wm1811_bt),
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_card midas_card = अणु
	.name = "Midas WM1811",
	.owner = THIS_MODULE,

	.dai_link = midas_dai,
	.num_links = ARRAY_SIZE(midas_dai),
	.controls = midas_controls,
	.num_controls = ARRAY_SIZE(midas_controls),
	.dapm_widमाला_लो = midas_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(midas_dapm_widमाला_लो),

	.set_bias_level = midas_set_bias_level,
	.late_probe = midas_late_probe,
पूर्ण;

अटल पूर्णांक midas_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *cpu_dai_node = शून्य, *codec_dai_node = शून्य;
	काष्ठा device_node *cpu = शून्य, *codec = शून्य;
	काष्ठा snd_soc_card *card = &midas_card;
	काष्ठा device *dev = &pdev->dev;
	अटल काष्ठा snd_soc_dai_link *dai_link;
	काष्ठा midas_priv *priv;
	पूर्णांक ret, i;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	snd_soc_card_set_drvdata(card, priv);
	card->dev = dev;

	priv->reg_mic_bias = devm_regulator_get(dev, "mic-bias");
	अगर (IS_ERR(priv->reg_mic_bias)) अणु
		dev_err(dev, "Failed to get mic bias regulator\n");
		वापस PTR_ERR(priv->reg_mic_bias);
	पूर्ण

	priv->reg_submic_bias = devm_regulator_get(dev, "submic-bias");
	अगर (IS_ERR(priv->reg_submic_bias)) अणु
		dev_err(dev, "Failed to get submic bias regulator\n");
		वापस PTR_ERR(priv->reg_submic_bias);
	पूर्ण

	priv->gpio_fm_sel = devm_gpiod_get_optional(dev, "fm-sel", GPIOD_OUT_HIGH);
	अगर (IS_ERR(priv->gpio_fm_sel)) अणु
		dev_err(dev, "Failed to get FM selection GPIO\n");
		वापस PTR_ERR(priv->gpio_fm_sel);
	पूर्ण

	priv->gpio_lineout_sel = devm_gpiod_get_optional(dev, "lineout-sel",
						    GPIOD_OUT_HIGH);
	अगर (IS_ERR(priv->gpio_lineout_sel)) अणु
		dev_err(dev, "Failed to get line out selection GPIO\n");
		वापस PTR_ERR(priv->gpio_lineout_sel);
	पूर्ण

	ret = snd_soc_of_parse_card_name(card, "model");
	अगर (ret < 0) अणु
		dev_err(dev, "Card name is not specified\n");
		वापस ret;
	पूर्ण

	ret = snd_soc_of_parse_audio_routing(card, "samsung,audio-routing");
	अगर (ret < 0) अणु
		dev_err(dev, "Audio routing invalid/unspecified\n");
		वापस ret;
	पूर्ण

	cpu = of_get_child_by_name(dev->of_node, "cpu");
	अगर (!cpu)
		वापस -EINVAL;

	codec = of_get_child_by_name(dev->of_node, "codec");
	अगर (!codec) अणु
		of_node_put(cpu);
		वापस -EINVAL;
	पूर्ण

	cpu_dai_node = of_parse_phandle(cpu, "sound-dai", 0);
	of_node_put(cpu);
	अगर (!cpu_dai_node) अणु
		dev_err(dev, "parsing cpu/sound-dai failed\n");
		of_node_put(codec);
		वापस -EINVAL;
	पूर्ण

	codec_dai_node = of_parse_phandle(codec, "sound-dai", 0);
	of_node_put(codec);
	अगर (!codec_dai_node) अणु
		dev_err(dev, "audio-codec property invalid/missing\n");
		ret = -EINVAL;
		जाओ put_cpu_dai_node;
	पूर्ण

	क्रम_each_card_prelinks(card, i, dai_link) अणु
		dai_link->codecs->of_node = codec_dai_node;
		dai_link->cpus->of_node = cpu_dai_node;
		dai_link->platक्रमms->of_node = cpu_dai_node;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(dev, &midas_component,
			midas_ext_dai, ARRAY_SIZE(midas_ext_dai));
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to register component: %d\n", ret);
		जाओ put_codec_dai_node;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_card(dev, card);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to register card: %d\n", ret);
		जाओ put_codec_dai_node;
	पूर्ण

	वापस 0;

put_codec_dai_node:
	of_node_put(codec_dai_node);
put_cpu_dai_node:
	of_node_put(cpu_dai_node);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id midas_of_match[] = अणु
	अणु .compatible = "samsung,midas-audio" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, midas_of_match);

अटल काष्ठा platक्रमm_driver midas_driver = अणु
	.driver = अणु
		.name = "midas-audio",
		.of_match_table = midas_of_match,
		.pm = &snd_soc_pm_ops,
	पूर्ण,
	.probe = midas_probe,
पूर्ण;
module_platक्रमm_driver(midas_driver);

MODULE_AUTHOR("Simon Shields <simon@lineageos.org>");
MODULE_DESCRIPTION("ASoC support for Midas");
MODULE_LICENSE("GPL v2");
