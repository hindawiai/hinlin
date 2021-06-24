<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
//
// Copyright (c) 2018 BayLibre, SAS.
// Author: Jerome Brunet <jbrunet@baylibre.com>

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/module.h>
#समावेश <sound/soc.h>

काष्ठा es7241_घड़ी_mode अणु
	अचिन्हित पूर्णांक rate_min;
	अचिन्हित पूर्णांक rate_max;
	अचिन्हित पूर्णांक *slv_mfs;
	अचिन्हित पूर्णांक slv_mfs_num;
	अचिन्हित पूर्णांक mst_mfs;
	अचिन्हित पूर्णांक mst_m0:1;
	अचिन्हित पूर्णांक mst_m1:1;
पूर्ण;

काष्ठा es7241_chip अणु
	स्थिर काष्ठा es7241_घड़ी_mode *modes;
	अचिन्हित पूर्णांक mode_num;
पूर्ण;

काष्ठा es7241_data अणु
	काष्ठा gpio_desc *reset;
	काष्ठा gpio_desc *m0;
	काष्ठा gpio_desc *m1;
	अचिन्हित पूर्णांक fmt;
	अचिन्हित पूर्णांक mclk;
	bool is_slave;
	स्थिर काष्ठा es7241_chip *chip;
पूर्ण;

अटल व्योम es7241_set_mode(काष्ठा es7241_data *priv,  पूर्णांक m0, पूर्णांक m1)
अणु
	/* put the device in reset */
	gpiod_set_value_cansleep(priv->reset, 0);

	/* set the mode */
	gpiod_set_value_cansleep(priv->m0, m0);
	gpiod_set_value_cansleep(priv->m1, m1);

	/* take the device out of reset - datasheet करोes not specअगरy a delay */
	gpiod_set_value_cansleep(priv->reset, 1);
पूर्ण

अटल पूर्णांक es7241_set_slave_mode(काष्ठा es7241_data *priv,
				 स्थिर काष्ठा es7241_घड़ी_mode *mode,
				 अचिन्हित पूर्णांक mfs)
अणु
	पूर्णांक j;

	अगर (!mfs)
		जाओ out_ok;

	क्रम (j = 0; j < mode->slv_mfs_num; j++) अणु
		अगर (mode->slv_mfs[j] == mfs)
			जाओ out_ok;
	पूर्ण

	वापस -EINVAL;

out_ok:
	es7241_set_mode(priv, 1, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक es7241_set_master_mode(काष्ठा es7241_data *priv,
				  स्थिर काष्ठा es7241_घड़ी_mode *mode,
				  अचिन्हित पूर्णांक mfs)
अणु
	/*
	 * We can't really set घड़ी ratio, अगर the mclk/lrclk is dअगरferent
	 * from what we provide, then error out
	 */
	अगर (mfs && mfs != mode->mst_mfs)
		वापस -EINVAL;

	es7241_set_mode(priv, mode->mst_m0, mode->mst_m1);

	वापस 0;
पूर्ण

अटल पूर्णांक es7241_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा es7241_data *priv = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक rate = params_rate(params);
	अचिन्हित पूर्णांक mfs = priv->mclk / rate;
	पूर्णांक i;

	क्रम (i = 0; i < priv->chip->mode_num; i++) अणु
		स्थिर काष्ठा es7241_घड़ी_mode *mode = &priv->chip->modes[i];

		अगर (rate < mode->rate_min || rate >= mode->rate_max)
			जारी;

		अगर (priv->is_slave)
			वापस es7241_set_slave_mode(priv, mode, mfs);
		अन्यथा
			वापस es7241_set_master_mode(priv, mode, mfs);
	पूर्ण

	/* should not happen */
	dev_err(dai->dev, "unsupported rate: %u\n", rate);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक es7241_set_sysclk(काष्ठा snd_soc_dai *dai, पूर्णांक clk_id,
			     अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा es7241_data *priv = snd_soc_dai_get_drvdata(dai);

	अगर (dir == SND_SOC_CLOCK_IN && clk_id == 0) अणु
		priv->mclk = freq;
		वापस 0;
	पूर्ण

	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक es7241_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा es7241_data *priv = snd_soc_dai_get_drvdata(dai);

	अगर ((fmt & SND_SOC_DAIFMT_INV_MASK) != SND_SOC_DAIFMT_NB_NF) अणु
		dev_err(dai->dev, "Unsupported dai clock inversion\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((fmt & SND_SOC_DAIFMT_FORMAT_MASK) != priv->fmt) अणु
		dev_err(dai->dev, "Invalid dai format\n");
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		priv->is_slave = true;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		priv->is_slave = false;
		अवरोध;

	शेष:
		dev_err(dai->dev, "Unsupported clock configuration\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops es7241_dai_ops = अणु
	.set_fmt	= es7241_set_fmt,
	.hw_params	= es7241_hw_params,
	.set_sysclk	= es7241_set_sysclk,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver es7241_dai = अणु
	.name = "es7241-hifi",
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_192000,
		.क्रमmats = (SNDRV_PCM_FMTBIT_S16_LE  |
			    SNDRV_PCM_FMTBIT_S24_3LE |
			    SNDRV_PCM_FMTBIT_S24_LE),
	पूर्ण,
	.ops = &es7241_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा es7241_घड़ी_mode es7241_modes[] = अणु
	अणु
		/* Single speed mode */
		.rate_min = 8000,
		.rate_max = 50000,
		.slv_mfs = (अचिन्हित पूर्णांक[]) अणु 256, 384, 512, 768, 1024 पूर्ण,
		.slv_mfs_num = 5,
		.mst_mfs = 256,
		.mst_m0 = 0,
		.mst_m1 = 0,
	पूर्ण, अणु
		/* Double speed mode */
		.rate_min = 50000,
		.rate_max = 100000,
		.slv_mfs = (अचिन्हित पूर्णांक[]) अणु 128, 192 पूर्ण,
		.slv_mfs_num = 2,
		.mst_mfs = 128,
		.mst_m0 = 1,
		.mst_m1 = 0,
	पूर्ण, अणु
		/* Quad speed mode */
		.rate_min = 100000,
		.rate_max = 200000,
		.slv_mfs = (अचिन्हित पूर्णांक[]) अणु 64 पूर्ण,
		.slv_mfs_num = 1,
		.mst_mfs = 64,
		.mst_m0 = 0,
		.mst_m1 = 1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा es7241_chip es7241_chip __maybe_unused = अणु
	.modes = es7241_modes,
	.mode_num = ARRAY_SIZE(es7241_modes),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget es7241_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_INPUT("AINL"),
	SND_SOC_DAPM_INPUT("AINR"),
	SND_SOC_DAPM_DAC("ADC", "Capture", SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_REGULATOR_SUPPLY("VDDP", 0, 0),
	SND_SOC_DAPM_REGULATOR_SUPPLY("VDDD", 0, 0),
	SND_SOC_DAPM_REGULATOR_SUPPLY("VDDA", 0, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route es7241_dapm_routes[] = अणु
	अणु "ADC", शून्य, "AINL", पूर्ण,
	अणु "ADC", शून्य, "AINR", पूर्ण,
	अणु "ADC", शून्य, "VDDA", पूर्ण,
	अणु "Capture", शून्य, "VDDP", पूर्ण,
	अणु "Capture", शून्य, "VDDD", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver es7241_component_driver = अणु
	.dapm_widमाला_लो		= es7241_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(es7241_dapm_widमाला_लो),
	.dapm_routes		= es7241_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(es7241_dapm_routes),
	.idle_bias_on		= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल व्योम es7241_parse_fmt(काष्ठा device *dev, काष्ठा es7241_data *priv)
अणु
	bool is_leftj;

	/*
	 * The क्रमmat is given by a pull resistor on the SDOUT pin:
	 * pull-up क्रम i2s, pull-करोwn क्रम left justअगरied.
	 */
	is_leftj = of_property_पढ़ो_bool(dev->of_node,
					 "everest,sdout-pull-down");
	अगर (is_leftj)
		priv->fmt = SND_SOC_DAIFMT_LEFT_J;
	अन्यथा
		priv->fmt = SND_SOC_DAIFMT_I2S;
पूर्ण

अटल पूर्णांक es7241_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा es7241_data *priv;
	पूर्णांक err;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, priv);

	priv->chip = of_device_get_match_data(dev);
	अगर (!priv->chip) अणु
		dev_err(dev, "failed to match device\n");
		वापस -ENODEV;
	पूर्ण

	es7241_parse_fmt(dev, priv);

	priv->reset = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(priv->reset)) अणु
		err = PTR_ERR(priv->reset);
		अगर (err != -EPROBE_DEFER)
			dev_err(dev, "Failed to get 'reset' gpio: %d", err);
		वापस err;
	पूर्ण

	priv->m0 = devm_gpiod_get_optional(dev, "m0", GPIOD_OUT_LOW);
	अगर (IS_ERR(priv->m0)) अणु
		err = PTR_ERR(priv->m0);
		अगर (err != -EPROBE_DEFER)
			dev_err(dev, "Failed to get 'm0' gpio: %d", err);
		वापस err;
	पूर्ण

	priv->m1 = devm_gpiod_get_optional(dev, "m1", GPIOD_OUT_LOW);
	अगर (IS_ERR(priv->m1)) अणु
		err = PTR_ERR(priv->m1);
		अगर (err != -EPROBE_DEFER)
			dev_err(dev, "Failed to get 'm1' gpio: %d", err);
		वापस err;
	पूर्ण

	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
				      &es7241_component_driver,
				      &es7241_dai, 1);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id es7241_ids[] = अणु
	अणु .compatible = "everest,es7241", .data = &es7241_chip पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, es7241_ids);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver es7241_driver = अणु
	.driver = अणु
		.name = "es7241",
		.of_match_table = of_match_ptr(es7241_ids),
	पूर्ण,
	.probe = es7241_probe,
पूर्ण;

module_platक्रमm_driver(es7241_driver);

MODULE_DESCRIPTION("ASoC ES7241 audio codec driver");
MODULE_AUTHOR("Jerome Brunet <jbrunet@baylibre.com>");
MODULE_LICENSE("GPL");
