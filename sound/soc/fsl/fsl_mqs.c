<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// ALSA SoC IMX MQS driver
//
// Copyright (C) 2014-2015 Freescale Semiconductor, Inc.
// Copyright 2019 NXP

#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/mfd/syscon/imx6q-iomuxc-gpr.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of.h>
#समावेश <linux/pm.h>
#समावेश <linux/slab.h>
#समावेश <sound/soc.h>
#समावेश <sound/pcm.h>
#समावेश <sound/initval.h>

#घोषणा REG_MQS_CTRL		0x00

#घोषणा MQS_EN_MASK			(0x1 << 28)
#घोषणा MQS_EN_SHIFT			(28)
#घोषणा MQS_SW_RST_MASK			(0x1 << 24)
#घोषणा MQS_SW_RST_SHIFT		(24)
#घोषणा MQS_OVERSAMPLE_MASK		(0x1 << 20)
#घोषणा MQS_OVERSAMPLE_SHIFT		(20)
#घोषणा MQS_CLK_DIV_MASK		(0xFF << 0)
#घोषणा MQS_CLK_DIV_SHIFT		(0)

/* codec निजी data */
काष्ठा fsl_mqs अणु
	काष्ठा regmap *regmap;
	काष्ठा clk *mclk;
	काष्ठा clk *ipg;

	अचिन्हित पूर्णांक reg_iomuxc_gpr2;
	अचिन्हित पूर्णांक reg_mqs_ctrl;
	bool use_gpr;
पूर्ण;

#घोषणा FSL_MQS_RATES	(SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000)
#घोषणा FSL_MQS_FORMATS	SNDRV_PCM_FMTBIT_S16_LE

अटल पूर्णांक fsl_mqs_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा fsl_mqs *mqs_priv = snd_soc_component_get_drvdata(component);
	अचिन्हित दीर्घ mclk_rate;
	पूर्णांक भाग, res;
	पूर्णांक lrclk;

	mclk_rate = clk_get_rate(mqs_priv->mclk);
	lrclk = params_rate(params);

	/*
	 * mclk_rate / (oversample(32,64) * FS * 2 * भागider ) = repeat_rate;
	 * अगर repeat_rate is 8, mqs can achieve better quality.
	 * oversample rate is fix to 32 currently.
	 */
	भाग = mclk_rate / (32 * lrclk * 2 * 8);
	res = mclk_rate % (32 * lrclk * 2 * 8);

	अगर (res == 0 && भाग > 0 && भाग <= 256) अणु
		अगर (mqs_priv->use_gpr) अणु
			regmap_update_bits(mqs_priv->regmap, IOMUXC_GPR2,
					   IMX6SX_GPR2_MQS_CLK_DIV_MASK,
					   (भाग - 1) << IMX6SX_GPR2_MQS_CLK_DIV_SHIFT);
			regmap_update_bits(mqs_priv->regmap, IOMUXC_GPR2,
					   IMX6SX_GPR2_MQS_OVERSAMPLE_MASK, 0);
		पूर्ण अन्यथा अणु
			regmap_update_bits(mqs_priv->regmap, REG_MQS_CTRL,
					   MQS_CLK_DIV_MASK,
					   (भाग - 1) << MQS_CLK_DIV_SHIFT);
			regmap_update_bits(mqs_priv->regmap, REG_MQS_CTRL,
					   MQS_OVERSAMPLE_MASK, 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(component->dev, "can't get proper divider\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_mqs_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	/* Only LEFT_J & SLAVE mode is supported. */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_LEFT_J:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_mqs_startup(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा fsl_mqs *mqs_priv = snd_soc_component_get_drvdata(component);

	अगर (mqs_priv->use_gpr)
		regmap_update_bits(mqs_priv->regmap, IOMUXC_GPR2,
				   IMX6SX_GPR2_MQS_EN_MASK,
				   1 << IMX6SX_GPR2_MQS_EN_SHIFT);
	अन्यथा
		regmap_update_bits(mqs_priv->regmap, REG_MQS_CTRL,
				   MQS_EN_MASK,
				   1 << MQS_EN_SHIFT);
	वापस 0;
पूर्ण

अटल व्योम fsl_mqs_shutकरोwn(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा fsl_mqs *mqs_priv = snd_soc_component_get_drvdata(component);

	अगर (mqs_priv->use_gpr)
		regmap_update_bits(mqs_priv->regmap, IOMUXC_GPR2,
				   IMX6SX_GPR2_MQS_EN_MASK, 0);
	अन्यथा
		regmap_update_bits(mqs_priv->regmap, REG_MQS_CTRL,
				   MQS_EN_MASK, 0);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_codec_fsl_mqs = अणु
	.idle_bias_on = 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops fsl_mqs_dai_ops = अणु
	.startup = fsl_mqs_startup,
	.shutकरोwn = fsl_mqs_shutकरोwn,
	.hw_params = fsl_mqs_hw_params,
	.set_fmt = fsl_mqs_set_dai_fmt,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver fsl_mqs_dai = अणु
	.name		= "fsl-mqs-dai",
	.playback	= अणु
		.stream_name	= "Playback",
		.channels_min	= 2,
		.channels_max	= 2,
		.rates		= FSL_MQS_RATES,
		.क्रमmats	= FSL_MQS_FORMATS,
	पूर्ण,
	.ops = &fsl_mqs_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा regmap_config fsl_mqs_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = REG_MQS_CTRL,
	.cache_type = REGCACHE_NONE,
पूर्ण;

अटल पूर्णांक fsl_mqs_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *gpr_np = शून्य;
	काष्ठा fsl_mqs *mqs_priv;
	व्योम __iomem *regs;
	पूर्णांक ret;

	mqs_priv = devm_kzalloc(&pdev->dev, माप(*mqs_priv), GFP_KERNEL);
	अगर (!mqs_priv)
		वापस -ENOMEM;

	/* On i.MX6sx the MQS control रेजिस्टर is in GPR करोमुख्य
	 * But in i.MX8QM/i.MX8QXP the control रेजिस्टर is moved
	 * to its own करोमुख्य.
	 */
	अगर (of_device_is_compatible(np, "fsl,imx8qm-mqs"))
		mqs_priv->use_gpr = false;
	अन्यथा
		mqs_priv->use_gpr = true;

	अगर (mqs_priv->use_gpr) अणु
		gpr_np = of_parse_phandle(np, "gpr", 0);
		अगर (!gpr_np) अणु
			dev_err(&pdev->dev, "failed to get gpr node by phandle\n");
			वापस -EINVAL;
		पूर्ण

		mqs_priv->regmap = syscon_node_to_regmap(gpr_np);
		अगर (IS_ERR(mqs_priv->regmap)) अणु
			dev_err(&pdev->dev, "failed to get gpr regmap\n");
			ret = PTR_ERR(mqs_priv->regmap);
			जाओ err_मुक्त_gpr_np;
		पूर्ण
	पूर्ण अन्यथा अणु
		regs = devm_platक्रमm_ioremap_resource(pdev, 0);
		अगर (IS_ERR(regs))
			वापस PTR_ERR(regs);

		mqs_priv->regmap = devm_regmap_init_mmio_clk(&pdev->dev,
							     "core",
							     regs,
							     &fsl_mqs_regmap_config);
		अगर (IS_ERR(mqs_priv->regmap)) अणु
			dev_err(&pdev->dev, "failed to init regmap: %ld\n",
				PTR_ERR(mqs_priv->regmap));
			वापस PTR_ERR(mqs_priv->regmap);
		पूर्ण

		mqs_priv->ipg = devm_clk_get(&pdev->dev, "core");
		अगर (IS_ERR(mqs_priv->ipg)) अणु
			dev_err(&pdev->dev, "failed to get the clock: %ld\n",
				PTR_ERR(mqs_priv->ipg));
			वापस PTR_ERR(mqs_priv->ipg);
		पूर्ण
	पूर्ण

	mqs_priv->mclk = devm_clk_get(&pdev->dev, "mclk");
	अगर (IS_ERR(mqs_priv->mclk)) अणु
		dev_err(&pdev->dev, "failed to get the clock: %ld\n",
			PTR_ERR(mqs_priv->mclk));
		ret = PTR_ERR(mqs_priv->mclk);
		जाओ err_मुक्त_gpr_np;
	पूर्ण

	dev_set_drvdata(&pdev->dev, mqs_priv);
	pm_runसमय_enable(&pdev->dev);

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev, &soc_codec_fsl_mqs,
			&fsl_mqs_dai, 1);
	अगर (ret)
		जाओ err_मुक्त_gpr_np;
	वापस 0;

err_मुक्त_gpr_np:
	of_node_put(gpr_np);

	वापस ret;
पूर्ण

अटल पूर्णांक fsl_mqs_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक fsl_mqs_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा fsl_mqs *mqs_priv = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(mqs_priv->ipg);
	अगर (ret) अणु
		dev_err(dev, "failed to enable ipg clock\n");
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(mqs_priv->mclk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable mclk clock\n");
		clk_disable_unprepare(mqs_priv->ipg);
		वापस ret;
	पूर्ण

	अगर (mqs_priv->use_gpr)
		regmap_ग_लिखो(mqs_priv->regmap, IOMUXC_GPR2,
			     mqs_priv->reg_iomuxc_gpr2);
	अन्यथा
		regmap_ग_लिखो(mqs_priv->regmap, REG_MQS_CTRL,
			     mqs_priv->reg_mqs_ctrl);
	वापस 0;
पूर्ण

अटल पूर्णांक fsl_mqs_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा fsl_mqs *mqs_priv = dev_get_drvdata(dev);

	अगर (mqs_priv->use_gpr)
		regmap_पढ़ो(mqs_priv->regmap, IOMUXC_GPR2,
			    &mqs_priv->reg_iomuxc_gpr2);
	अन्यथा
		regmap_पढ़ो(mqs_priv->regmap, REG_MQS_CTRL,
			    &mqs_priv->reg_mqs_ctrl);

	clk_disable_unprepare(mqs_priv->mclk);
	clk_disable_unprepare(mqs_priv->ipg);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops fsl_mqs_pm_ops = अणु
	SET_RUNTIME_PM_OPS(fsl_mqs_runसमय_suspend,
			   fsl_mqs_runसमय_resume,
			   शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id fsl_mqs_dt_ids[] = अणु
	अणु .compatible = "fsl,imx8qm-mqs", पूर्ण,
	अणु .compatible = "fsl,imx6sx-mqs", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, fsl_mqs_dt_ids);

अटल काष्ठा platक्रमm_driver fsl_mqs_driver = अणु
	.probe		= fsl_mqs_probe,
	.हटाओ		= fsl_mqs_हटाओ,
	.driver		= अणु
		.name	= "fsl-mqs",
		.of_match_table = fsl_mqs_dt_ids,
		.pm = &fsl_mqs_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(fsl_mqs_driver);

MODULE_AUTHOR("Shengjiu Wang <Shengjiu.Wang@nxp.com>");
MODULE_DESCRIPTION("MQS codec driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform: fsl-mqs");
