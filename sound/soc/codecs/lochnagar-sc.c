<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Lochnagar sound card driver
//
// Copyright (c) 2017-2019 Cirrus Logic, Inc. and
//                         Cirrus Logic International Semiconductor Ltd.
//
// Author: Charles Keepax <ckeepax@खोलोsource.cirrus.com>
//         Piotr Stankiewicz <piotrs@खोलोsource.cirrus.com>

#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <sound/soc.h>

#समावेश <linux/mfd/lochnagar.h>
#समावेश <linux/mfd/lochnagar1_regs.h>
#समावेश <linux/mfd/lochnagar2_regs.h>

काष्ठा lochnagar_sc_priv अणु
	काष्ठा clk *mclk;
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget lochnagar_sc_widमाला_लो[] = अणु
	SND_SOC_DAPM_LINE("Line Jack", शून्य),
	SND_SOC_DAPM_LINE("USB Audio", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route lochnagar_sc_routes[] = अणु
	अणु "Line Jack", शून्य, "AIF1 Playback" पूर्ण,
	अणु "AIF1 Capture", शून्य, "Line Jack" पूर्ण,

	अणु "USB Audio", शून्य, "USB1 Playback" पूर्ण,
	अणु "USB Audio", शून्य, "USB2 Playback" पूर्ण,
	अणु "USB1 Capture", शून्य, "USB Audio" पूर्ण,
	अणु "USB2 Capture", शून्य, "USB Audio" पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lochnagar_sc_chan_vals[] = अणु
	4, 8,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list lochnagar_sc_chan_स्थिरraपूर्णांक = अणु
	.count = ARRAY_SIZE(lochnagar_sc_chan_vals),
	.list = lochnagar_sc_chan_vals,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lochnagar_sc_rate_vals[] = अणु
	8000, 16000, 24000, 32000, 48000, 96000, 192000,
	22050, 44100, 88200, 176400,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list lochnagar_sc_rate_स्थिरraपूर्णांक = अणु
	.count = ARRAY_SIZE(lochnagar_sc_rate_vals),
	.list = lochnagar_sc_rate_vals,
पूर्ण;

अटल पूर्णांक lochnagar_sc_hw_rule_rate(काष्ठा snd_pcm_hw_params *params,
				     काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_पूर्णांकerval range = अणु
		.min = 8000,
		.max = 24576000 / hw_param_पूर्णांकerval(params, rule->deps[0])->max,
	पूर्ण;

	वापस snd_पूर्णांकerval_refine(hw_param_पूर्णांकerval(params, rule->var),
				   &range);
पूर्ण

अटल पूर्णांक lochnagar_sc_startup(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *comp = dai->component;
	काष्ठा lochnagar_sc_priv *priv = snd_soc_component_get_drvdata(comp);
	पूर्णांक ret;

	ret = snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
					 SNDRV_PCM_HW_PARAM_RATE,
					 &lochnagar_sc_rate_स्थिरraपूर्णांक);
	अगर (ret)
		वापस ret;

	वापस snd_pcm_hw_rule_add(substream->runसमय, 0,
				   SNDRV_PCM_HW_PARAM_RATE,
				   lochnagar_sc_hw_rule_rate, priv,
				   SNDRV_PCM_HW_PARAM_FRAME_BITS, -1);
पूर्ण

अटल पूर्णांक lochnagar_sc_line_startup(काष्ठा snd_pcm_substream *substream,
				     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *comp = dai->component;
	काष्ठा lochnagar_sc_priv *priv = snd_soc_component_get_drvdata(comp);
	पूर्णांक ret;

	ret = clk_prepare_enable(priv->mclk);
	अगर (ret < 0) अणु
		dev_err(dai->dev, "Failed to enable MCLK: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = lochnagar_sc_startup(substream, dai);
	अगर (ret)
		वापस ret;

	वापस snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
					  SNDRV_PCM_HW_PARAM_CHANNELS,
					  &lochnagar_sc_chan_स्थिरraपूर्णांक);
पूर्ण

अटल व्योम lochnagar_sc_line_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *comp = dai->component;
	काष्ठा lochnagar_sc_priv *priv = snd_soc_component_get_drvdata(comp);

	clk_disable_unprepare(priv->mclk);
पूर्ण

अटल पूर्णांक lochnagar_sc_check_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt,
				  अचिन्हित पूर्णांक tar)
अणु
	tar |= SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF;

	अगर ((fmt & ~SND_SOC_DAIFMT_CLOCK_MASK) != tar)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक lochnagar_sc_set_line_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	वापस lochnagar_sc_check_fmt(dai, fmt, SND_SOC_DAIFMT_CBS_CFS);
पूर्ण

अटल पूर्णांक lochnagar_sc_set_usb_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	वापस lochnagar_sc_check_fmt(dai, fmt, SND_SOC_DAIFMT_CBM_CFM);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops lochnagar_sc_line_ops = अणु
	.startup = lochnagar_sc_line_startup,
	.shutकरोwn = lochnagar_sc_line_shutकरोwn,
	.set_fmt = lochnagar_sc_set_line_fmt,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops lochnagar_sc_usb_ops = अणु
	.startup = lochnagar_sc_startup,
	.set_fmt = lochnagar_sc_set_usb_fmt,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver lochnagar_sc_dai[] = अणु
	अणु
		.name = "lochnagar-line",
		.playback = अणु
			.stream_name = "AIF1 Playback",
			.channels_min = 4,
			.channels_max = 8,
			.rates = SNDRV_PCM_RATE_KNOT,
			.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF1 Capture",
			.channels_min = 4,
			.channels_max = 8,
			.rates = SNDRV_PCM_RATE_KNOT,
			.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE,
		पूर्ण,
		.ops = &lochnagar_sc_line_ops,
		.symmetric_rate = true,
		.symmetric_sample_bits = true,
	पूर्ण,
	अणु
		.name = "lochnagar-usb1",
		.playback = अणु
			.stream_name = "USB1 Playback",
			.channels_min = 1,
			.channels_max = 8,
			.rates = SNDRV_PCM_RATE_KNOT,
			.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE,
		पूर्ण,
		.capture = अणु
			.stream_name = "USB1 Capture",
			.channels_min = 1,
			.channels_max = 8,
			.rates = SNDRV_PCM_RATE_KNOT,
			.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE,
		पूर्ण,
		.ops = &lochnagar_sc_usb_ops,
		.symmetric_rate = true,
		.symmetric_sample_bits = true,
	पूर्ण,
	अणु
		.name = "lochnagar-usb2",
		.playback = अणु
			.stream_name = "USB2 Playback",
			.channels_min = 1,
			.channels_max = 8,
			.rates = SNDRV_PCM_RATE_KNOT,
			.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE,
		पूर्ण,
		.capture = अणु
			.stream_name = "USB2 Capture",
			.channels_min = 1,
			.channels_max = 8,
			.rates = SNDRV_PCM_RATE_KNOT,
			.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE,
		पूर्ण,
		.ops = &lochnagar_sc_usb_ops,
		.symmetric_rate = true,
		.symmetric_sample_bits = true,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver lochnagar_sc_driver = अणु
	.non_legacy_dai_naming = 1,

	.dapm_widमाला_लो = lochnagar_sc_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(lochnagar_sc_widमाला_लो),
	.dapm_routes = lochnagar_sc_routes,
	.num_dapm_routes = ARRAY_SIZE(lochnagar_sc_routes),
पूर्ण;

अटल पूर्णांक lochnagar_sc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lochnagar_sc_priv *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->mclk = devm_clk_get(&pdev->dev, "mclk");
	अगर (IS_ERR(priv->mclk)) अणु
		ret = PTR_ERR(priv->mclk);
		dev_err(&pdev->dev, "Failed to get MCLK: %d\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, priv);

	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					       &lochnagar_sc_driver,
					       lochnagar_sc_dai,
					       ARRAY_SIZE(lochnagar_sc_dai));
पूर्ण

अटल स्थिर काष्ठा of_device_id lochnagar_of_match[] = अणु
	अणु .compatible = "cirrus,lochnagar2-soundcard" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lochnagar_of_match);

अटल काष्ठा platक्रमm_driver lochnagar_sc_codec_driver = अणु
	.driver = अणु
		.name = "lochnagar-soundcard",
		.of_match_table = of_match_ptr(lochnagar_of_match),
	पूर्ण,

	.probe = lochnagar_sc_probe,
पूर्ण;
module_platक्रमm_driver(lochnagar_sc_codec_driver);

MODULE_DESCRIPTION("ASoC Lochnagar Sound Card Driver");
MODULE_AUTHOR("Piotr Stankiewicz <piotrs@opensource.cirrus.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:lochnagar-soundcard");
