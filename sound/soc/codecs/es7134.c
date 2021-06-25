<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2017 BayLibre, SAS.
 * Author: Jerome Brunet <jbrunet@baylibre.com>
 */

#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/module.h>
#समावेश <sound/soc.h>

/*
 * The everest 7134 is a very simple DA converter with no रेजिस्टर
 */

काष्ठा es7134_घड़ी_mode अणु
	अचिन्हित पूर्णांक rate_min;
	अचिन्हित पूर्णांक rate_max;
	अचिन्हित पूर्णांक *mclk_fs;
	अचिन्हित पूर्णांक mclk_fs_num;
पूर्ण;

काष्ठा es7134_chip अणु
	काष्ठा snd_soc_dai_driver *dai_drv;
	स्थिर काष्ठा es7134_घड़ी_mode *modes;
	अचिन्हित पूर्णांक mode_num;
	स्थिर काष्ठा snd_soc_dapm_widget *extra_widमाला_लो;
	अचिन्हित पूर्णांक extra_widget_num;
	स्थिर काष्ठा snd_soc_dapm_route *extra_routes;
	अचिन्हित पूर्णांक extra_route_num;
पूर्ण;

काष्ठा es7134_data अणु
	अचिन्हित पूर्णांक mclk;
	स्थिर काष्ठा es7134_chip *chip;
पूर्ण;

अटल पूर्णांक es7134_check_mclk(काष्ठा snd_soc_dai *dai,
			     काष्ठा es7134_data *priv,
			     अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित पूर्णांक mfs = priv->mclk / rate;
	पूर्णांक i, j;

	क्रम (i = 0; i < priv->chip->mode_num; i++) अणु
		स्थिर काष्ठा es7134_घड़ी_mode *mode = &priv->chip->modes[i];

		अगर (rate < mode->rate_min || rate > mode->rate_max)
			जारी;

		क्रम (j = 0; j < mode->mclk_fs_num; j++) अणु
			अगर (mode->mclk_fs[j] == mfs)
				वापस 0;
		पूर्ण

		dev_err(dai->dev, "unsupported mclk_fs %u for rate %u\n",
			mfs, rate);
		वापस -EINVAL;
	पूर्ण

	/* should not happen */
	dev_err(dai->dev, "unsupported rate: %u\n", rate);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक es7134_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा es7134_data *priv = snd_soc_dai_get_drvdata(dai);

	/* mclk has not been provided, assume it is OK */
	अगर (!priv->mclk)
		वापस 0;

	वापस es7134_check_mclk(dai, priv, params_rate(params));
पूर्ण

अटल पूर्णांक es7134_set_sysclk(काष्ठा snd_soc_dai *dai, पूर्णांक clk_id,
			     अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा es7134_data *priv = snd_soc_dai_get_drvdata(dai);

	अगर (dir == SND_SOC_CLOCK_IN && clk_id == 0) अणु
		priv->mclk = freq;
		वापस 0;
	पूर्ण

	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक es7134_set_fmt(काष्ठा snd_soc_dai *codec_dai, अचिन्हित पूर्णांक fmt)
अणु
	fmt &= (SND_SOC_DAIFMT_FORMAT_MASK | SND_SOC_DAIFMT_INV_MASK |
		SND_SOC_DAIFMT_MASTER_MASK);

	अगर (fmt != (SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
		    SND_SOC_DAIFMT_CBS_CFS)) अणु
		dev_err(codec_dai->dev, "Invalid DAI format\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक es7134_component_probe(काष्ठा snd_soc_component *c)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(c);
	काष्ठा es7134_data *priv = snd_soc_component_get_drvdata(c);
	स्थिर काष्ठा es7134_chip *chip = priv->chip;
	पूर्णांक ret;

	अगर (chip->extra_widget_num) अणु
		ret = snd_soc_dapm_new_controls(dapm, chip->extra_widमाला_लो,
						chip->extra_widget_num);
		अगर (ret) अणु
			dev_err(c->dev, "failed to add extra widgets\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (chip->extra_route_num) अणु
		ret = snd_soc_dapm_add_routes(dapm, chip->extra_routes,
					      chip->extra_route_num);
		अगर (ret) अणु
			dev_err(c->dev, "failed to add extra routes\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops es7134_dai_ops = अणु
	.set_fmt	= es7134_set_fmt,
	.hw_params	= es7134_hw_params,
	.set_sysclk	= es7134_set_sysclk,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver es7134_dai = अणु
	.name = "es7134-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = (SNDRV_PCM_RATE_8000_48000 |
			  SNDRV_PCM_RATE_88200      |
			  SNDRV_PCM_RATE_96000      |
			  SNDRV_PCM_RATE_176400     |
			  SNDRV_PCM_RATE_192000),
		.क्रमmats = (SNDRV_PCM_FMTBIT_S16_LE  |
			    SNDRV_PCM_FMTBIT_S18_3LE |
			    SNDRV_PCM_FMTBIT_S20_3LE |
			    SNDRV_PCM_FMTBIT_S24_3LE |
			    SNDRV_PCM_FMTBIT_S24_LE),
	पूर्ण,
	.ops = &es7134_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा es7134_घड़ी_mode es7134_modes[] = अणु
	अणु
		/* Single speed mode */
		.rate_min = 8000,
		.rate_max = 50000,
		.mclk_fs = (अचिन्हित पूर्णांक[]) अणु 256, 384, 512, 768, 1024 पूर्ण,
		.mclk_fs_num = 5,
	पूर्ण, अणु
		/* Double speed mode */
		.rate_min = 84000,
		.rate_max = 100000,
		.mclk_fs = (अचिन्हित पूर्णांक[]) अणु 128, 192, 256, 384, 512 पूर्ण,
		.mclk_fs_num = 5,
	पूर्ण, अणु
		/* Quad speed mode */
		.rate_min = 167000,
		.rate_max = 192000,
		.mclk_fs = (अचिन्हित पूर्णांक[]) अणु 128, 192, 256 पूर्ण,
		.mclk_fs_num = 3,
	पूर्ण,
पूर्ण;

/* Digital I/O are also supplied by VDD on the es7134 */
अटल स्थिर काष्ठा snd_soc_dapm_route es7134_extra_routes[] = अणु
	अणु "Playback", शून्य, "VDD", पूर्ण
पूर्ण;

अटल स्थिर काष्ठा es7134_chip es7134_chip __maybe_unused = अणु
	.dai_drv = &es7134_dai,
	.modes = es7134_modes,
	.mode_num = ARRAY_SIZE(es7134_modes),
	.extra_routes = es7134_extra_routes,
	.extra_route_num = ARRAY_SIZE(es7134_extra_routes),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget es7134_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_OUTPUT("AOUTL"),
	SND_SOC_DAPM_OUTPUT("AOUTR"),
	SND_SOC_DAPM_DAC("DAC", "Playback", SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_REGULATOR_SUPPLY("VDD", 0, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route es7134_dapm_routes[] = अणु
	अणु "AOUTL", शून्य, "DAC" पूर्ण,
	अणु "AOUTR", शून्य, "DAC" पूर्ण,
	अणु "DAC", शून्य, "VDD" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver es7134_component_driver = अणु
	.probe			= es7134_component_probe,
	.dapm_widमाला_लो		= es7134_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(es7134_dapm_widमाला_लो),
	.dapm_routes		= es7134_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(es7134_dapm_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver es7154_dai = अणु
	.name = "es7154-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = (SNDRV_PCM_RATE_8000_48000 |
			  SNDRV_PCM_RATE_88200      |
			  SNDRV_PCM_RATE_96000),
		.क्रमmats = (SNDRV_PCM_FMTBIT_S16_LE  |
			    SNDRV_PCM_FMTBIT_S18_3LE |
			    SNDRV_PCM_FMTBIT_S20_3LE |
			    SNDRV_PCM_FMTBIT_S24_3LE |
			    SNDRV_PCM_FMTBIT_S24_LE),
	पूर्ण,
	.ops = &es7134_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा es7134_घड़ी_mode es7154_modes[] = अणु
	अणु
		/* Single speed mode */
		.rate_min = 8000,
		.rate_max = 50000,
		.mclk_fs = (अचिन्हित पूर्णांक[]) अणु 32, 64, 128, 192, 256,
					      384, 512, 768, 1024 पूर्ण,
		.mclk_fs_num = 9,
	पूर्ण, अणु
		/* Double speed mode */
		.rate_min = 84000,
		.rate_max = 100000,
		.mclk_fs = (अचिन्हित पूर्णांक[]) अणु 128, 192, 256, 384, 512,
					      768, 1024पूर्ण,
		.mclk_fs_num = 7,
	पूर्ण
पूर्ण;

/* Es7154 has a separate supply क्रम digital I/O  */
अटल स्थिर काष्ठा snd_soc_dapm_widget es7154_extra_widमाला_लो[] = अणु
	SND_SOC_DAPM_REGULATOR_SUPPLY("PVDD", 0, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route es7154_extra_routes[] = अणु
	अणु "Playback", शून्य, "PVDD", पूर्ण
पूर्ण;

अटल स्थिर काष्ठा es7134_chip es7154_chip __maybe_unused = अणु
	.dai_drv = &es7154_dai,
	.modes = es7154_modes,
	.mode_num = ARRAY_SIZE(es7154_modes),
	.extra_routes = es7154_extra_routes,
	.extra_route_num = ARRAY_SIZE(es7154_extra_routes),
	.extra_widमाला_लो = es7154_extra_widमाला_लो,
	.extra_widget_num = ARRAY_SIZE(es7154_extra_widमाला_लो),
पूर्ण;

अटल पूर्णांक es7134_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा es7134_data *priv;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, priv);

	priv->chip = of_device_get_match_data(dev);
	अगर (!priv->chip) अणु
		dev_err(dev, "failed to match device\n");
		वापस -ENODEV;
	पूर्ण

	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
				      &es7134_component_driver,
				      priv->chip->dai_drv, 1);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id es7134_ids[] = अणु
	अणु .compatible = "everest,es7134", .data = &es7134_chip पूर्ण,
	अणु .compatible = "everest,es7144", .data = &es7134_chip पूर्ण,
	अणु .compatible = "everest,es7154", .data = &es7154_chip पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, es7134_ids);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver es7134_driver = अणु
	.driver = अणु
		.name = "es7134",
		.of_match_table = of_match_ptr(es7134_ids),
	पूर्ण,
	.probe = es7134_probe,
पूर्ण;

module_platक्रमm_driver(es7134_driver);

MODULE_DESCRIPTION("ASoC ES7134 audio codec driver");
MODULE_AUTHOR("Jerome Brunet <jbrunet@baylibre.com>");
MODULE_LICENSE("GPL");
