<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file is part the core part STM32 DFSDM driver
 *
 * Copyright (C) 2017, STMicroelectronics - All Rights Reserved
 * Author(s): Arnaud Pouliquen <arnaud.pouliquen@st.com> क्रम STMicroelectronics.
 */

#समावेश <linux/clk.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#समावेश "stm32-dfsdm.h"

काष्ठा sपंचांग32_dfsdm_dev_data अणु
	अचिन्हित पूर्णांक num_filters;
	अचिन्हित पूर्णांक num_channels;
	स्थिर काष्ठा regmap_config *regmap_cfg;
पूर्ण;

#घोषणा STM32H7_DFSDM_NUM_FILTERS	4
#घोषणा STM32H7_DFSDM_NUM_CHANNELS	8
#घोषणा STM32MP1_DFSDM_NUM_FILTERS	6
#घोषणा STM32MP1_DFSDM_NUM_CHANNELS	8

अटल bool sपंचांग32_dfsdm_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	अगर (reg < DFSDM_FILTER_BASE_ADR)
		वापस false;

	/*
	 * Mask is करोne on रेजिस्टर to aव्योम to list रेजिस्टरs of all
	 * filter instances.
	 */
	चयन (reg & DFSDM_FILTER_REG_MASK) अणु
	हाल DFSDM_CR1(0) & DFSDM_FILTER_REG_MASK:
	हाल DFSDM_ISR(0) & DFSDM_FILTER_REG_MASK:
	हाल DFSDM_JDATAR(0) & DFSDM_FILTER_REG_MASK:
	हाल DFSDM_RDATAR(0) & DFSDM_FILTER_REG_MASK:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल स्थिर काष्ठा regmap_config sपंचांग32h7_dfsdm_regmap_cfg = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = माप(u32),
	.max_रेजिस्टर = 0x2B8,
	.अस्थिर_reg = sपंचांग32_dfsdm_अस्थिर_reg,
	.fast_io = true,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_dfsdm_dev_data sपंचांग32h7_dfsdm_data = अणु
	.num_filters = STM32H7_DFSDM_NUM_FILTERS,
	.num_channels = STM32H7_DFSDM_NUM_CHANNELS,
	.regmap_cfg = &sपंचांग32h7_dfsdm_regmap_cfg,
पूर्ण;

अटल स्थिर काष्ठा regmap_config sपंचांग32mp1_dfsdm_regmap_cfg = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = माप(u32),
	.max_रेजिस्टर = 0x7fc,
	.अस्थिर_reg = sपंचांग32_dfsdm_अस्थिर_reg,
	.fast_io = true,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_dfsdm_dev_data sपंचांग32mp1_dfsdm_data = अणु
	.num_filters = STM32MP1_DFSDM_NUM_FILTERS,
	.num_channels = STM32MP1_DFSDM_NUM_CHANNELS,
	.regmap_cfg = &sपंचांग32mp1_dfsdm_regmap_cfg,
पूर्ण;

काष्ठा dfsdm_priv अणु
	काष्ठा platक्रमm_device *pdev; /* platक्रमm device */

	काष्ठा sपंचांग32_dfsdm dfsdm; /* common data exported क्रम all instances */

	अचिन्हित पूर्णांक spi_clk_out_भाग; /* SPI clkout भागider value */
	atomic_t n_active_ch;	/* number of current active channels */

	काष्ठा clk *clk; /* DFSDM घड़ी */
	काष्ठा clk *aclk; /* audio घड़ी */
पूर्ण;

अटल अंतरभूत काष्ठा dfsdm_priv *to_sपंचांग32_dfsdm_priv(काष्ठा sपंचांग32_dfsdm *dfsdm)
अणु
	वापस container_of(dfsdm, काष्ठा dfsdm_priv, dfsdm);
पूर्ण

अटल पूर्णांक sपंचांग32_dfsdm_clk_prepare_enable(काष्ठा sपंचांग32_dfsdm *dfsdm)
अणु
	काष्ठा dfsdm_priv *priv = to_sपंचांग32_dfsdm_priv(dfsdm);
	पूर्णांक ret;

	ret = clk_prepare_enable(priv->clk);
	अगर (ret || !priv->aclk)
		वापस ret;

	ret = clk_prepare_enable(priv->aclk);
	अगर (ret)
		clk_disable_unprepare(priv->clk);

	वापस ret;
पूर्ण

अटल व्योम sपंचांग32_dfsdm_clk_disable_unprepare(काष्ठा sपंचांग32_dfsdm *dfsdm)
अणु
	काष्ठा dfsdm_priv *priv = to_sपंचांग32_dfsdm_priv(dfsdm);

	clk_disable_unprepare(priv->aclk);
	clk_disable_unprepare(priv->clk);
पूर्ण

/**
 * sपंचांग32_dfsdm_start_dfsdm - start global dfsdm पूर्णांकerface.
 *
 * Enable पूर्णांकerface अगर n_active_ch is not null.
 * @dfsdm: Handle used to retrieve dfsdm context.
 */
पूर्णांक sपंचांग32_dfsdm_start_dfsdm(काष्ठा sपंचांग32_dfsdm *dfsdm)
अणु
	काष्ठा dfsdm_priv *priv = to_sपंचांग32_dfsdm_priv(dfsdm);
	काष्ठा device *dev = &priv->pdev->dev;
	अचिन्हित पूर्णांक clk_भाग = priv->spi_clk_out_भाग, clk_src;
	पूर्णांक ret;

	अगर (atomic_inc_वापस(&priv->n_active_ch) == 1) अणु
		ret = pm_runसमय_get_sync(dev);
		अगर (ret < 0) अणु
			pm_runसमय_put_noidle(dev);
			जाओ error_ret;
		पूर्ण

		/* select घड़ी source, e.g. 0 क्रम "dfsdm" or 1 क्रम "audio" */
		clk_src = priv->aclk ? 1 : 0;
		ret = regmap_update_bits(dfsdm->regmap, DFSDM_CHCFGR1(0),
					 DFSDM_CHCFGR1_CKOUTSRC_MASK,
					 DFSDM_CHCFGR1_CKOUTSRC(clk_src));
		अगर (ret < 0)
			जाओ pm_put;

		/* Output the SPI CLKOUT (अगर clk_भाग == 0 घड़ी अगर OFF) */
		ret = regmap_update_bits(dfsdm->regmap, DFSDM_CHCFGR1(0),
					 DFSDM_CHCFGR1_CKOUTDIV_MASK,
					 DFSDM_CHCFGR1_CKOUTDIV(clk_भाग));
		अगर (ret < 0)
			जाओ pm_put;

		/* Global enable of DFSDM पूर्णांकerface */
		ret = regmap_update_bits(dfsdm->regmap, DFSDM_CHCFGR1(0),
					 DFSDM_CHCFGR1_DFSDMEN_MASK,
					 DFSDM_CHCFGR1_DFSDMEN(1));
		अगर (ret < 0)
			जाओ pm_put;
	पूर्ण

	dev_dbg(dev, "%s: n_active_ch %d\n", __func__,
		atomic_पढ़ो(&priv->n_active_ch));

	वापस 0;

pm_put:
	pm_runसमय_put_sync(dev);
error_ret:
	atomic_dec(&priv->n_active_ch);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sपंचांग32_dfsdm_start_dfsdm);

/**
 * sपंचांग32_dfsdm_stop_dfsdm - stop global DFSDM पूर्णांकerface.
 *
 * Disable पूर्णांकerface अगर n_active_ch is null
 * @dfsdm: Handle used to retrieve dfsdm context.
 */
पूर्णांक sपंचांग32_dfsdm_stop_dfsdm(काष्ठा sपंचांग32_dfsdm *dfsdm)
अणु
	काष्ठा dfsdm_priv *priv = to_sपंचांग32_dfsdm_priv(dfsdm);
	पूर्णांक ret;

	अगर (atomic_dec_and_test(&priv->n_active_ch)) अणु
		/* Global disable of DFSDM पूर्णांकerface */
		ret = regmap_update_bits(dfsdm->regmap, DFSDM_CHCFGR1(0),
					 DFSDM_CHCFGR1_DFSDMEN_MASK,
					 DFSDM_CHCFGR1_DFSDMEN(0));
		अगर (ret < 0)
			वापस ret;

		/* Stop SPI CLKOUT */
		ret = regmap_update_bits(dfsdm->regmap, DFSDM_CHCFGR1(0),
					 DFSDM_CHCFGR1_CKOUTDIV_MASK,
					 DFSDM_CHCFGR1_CKOUTDIV(0));
		अगर (ret < 0)
			वापस ret;

		pm_runसमय_put_sync(&priv->pdev->dev);
	पूर्ण
	dev_dbg(&priv->pdev->dev, "%s: n_active_ch %d\n", __func__,
		atomic_पढ़ो(&priv->n_active_ch));

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sपंचांग32_dfsdm_stop_dfsdm);

अटल पूर्णांक sपंचांग32_dfsdm_parse_of(काष्ठा platक्रमm_device *pdev,
				काष्ठा dfsdm_priv *priv)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा resource *res;
	अचिन्हित दीर्घ clk_freq, भागider;
	अचिन्हित पूर्णांक spi_freq, rem;
	पूर्णांक ret;

	अगर (!node)
		वापस -EINVAL;

	priv->dfsdm.base = devm_platक्रमm_get_and_ioremap_resource(pdev, 0,
							&res);
	अगर (IS_ERR(priv->dfsdm.base))
		वापस PTR_ERR(priv->dfsdm.base);

	priv->dfsdm.phys_base = res->start;

	/*
	 * "dfsdm" घड़ी is mandatory क्रम DFSDM peripheral घड़ीing.
	 * "dfsdm" or "audio" घड़ीs can be used as source घड़ी क्रम
	 * the SPI घड़ी out संकेत and पूर्णांकernal processing, depending
	 * on use हाल.
	 */
	priv->clk = devm_clk_get(&pdev->dev, "dfsdm");
	अगर (IS_ERR(priv->clk))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(priv->clk),
				     "Failed to get clock\n");

	priv->aclk = devm_clk_get(&pdev->dev, "audio");
	अगर (IS_ERR(priv->aclk))
		priv->aclk = शून्य;

	अगर (priv->aclk)
		clk_freq = clk_get_rate(priv->aclk);
	अन्यथा
		clk_freq = clk_get_rate(priv->clk);

	/* SPI घड़ी out frequency */
	ret = of_property_पढ़ो_u32(pdev->dev.of_node, "spi-max-frequency",
				   &spi_freq);
	अगर (ret < 0) अणु
		/* No SPI master mode */
		वापस 0;
	पूर्ण

	भागider = भाग_u64_rem(clk_freq, spi_freq, &rem);
	/* Round up भागider when ckout isn't precise, not to exceed spi_freq */
	अगर (rem)
		भागider++;

	/* programmable भागider is in range of [2:256] */
	अगर (भागider < 2 || भागider > 256) अणु
		dev_err(&pdev->dev, "spi-max-frequency not achievable\n");
		वापस -EINVAL;
	पूर्ण

	/* SPI घड़ी output भागider is: भागider = CKOUTDIV + 1 */
	priv->spi_clk_out_भाग = भागider - 1;
	priv->dfsdm.spi_master_freq = clk_freq / (priv->spi_clk_out_भाग + 1);

	अगर (rem) अणु
		dev_warn(&pdev->dev, "SPI clock not accurate\n");
		dev_warn(&pdev->dev, "%ld = %d * %d + %d\n",
			 clk_freq, spi_freq, priv->spi_clk_out_भाग + 1, rem);
	पूर्ण

	वापस 0;
पूर्ण;

अटल स्थिर काष्ठा of_device_id sपंचांग32_dfsdm_of_match[] = अणु
	अणु
		.compatible = "st,stm32h7-dfsdm",
		.data = &sपंचांग32h7_dfsdm_data,
	पूर्ण,
	अणु
		.compatible = "st,stm32mp1-dfsdm",
		.data = &sपंचांग32mp1_dfsdm_data,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_dfsdm_of_match);

अटल पूर्णांक sपंचांग32_dfsdm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dfsdm_priv *priv;
	स्थिर काष्ठा sपंचांग32_dfsdm_dev_data *dev_data;
	काष्ठा sपंचांग32_dfsdm *dfsdm;
	पूर्णांक ret;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->pdev = pdev;

	dev_data = of_device_get_match_data(&pdev->dev);

	dfsdm = &priv->dfsdm;
	dfsdm->fl_list = devm_kसुस्मृति(&pdev->dev, dev_data->num_filters,
				      माप(*dfsdm->fl_list), GFP_KERNEL);
	अगर (!dfsdm->fl_list)
		वापस -ENOMEM;

	dfsdm->num_fls = dev_data->num_filters;
	dfsdm->ch_list = devm_kसुस्मृति(&pdev->dev, dev_data->num_channels,
				      माप(*dfsdm->ch_list),
				      GFP_KERNEL);
	अगर (!dfsdm->ch_list)
		वापस -ENOMEM;
	dfsdm->num_chs = dev_data->num_channels;

	ret = sपंचांग32_dfsdm_parse_of(pdev, priv);
	अगर (ret < 0)
		वापस ret;

	dfsdm->regmap = devm_regmap_init_mmio_clk(&pdev->dev, "dfsdm",
						  dfsdm->base,
						  dev_data->regmap_cfg);
	अगर (IS_ERR(dfsdm->regmap)) अणु
		ret = PTR_ERR(dfsdm->regmap);
		dev_err(&pdev->dev, "%s: Failed to allocate regmap: %d\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, dfsdm);

	ret = sपंचांग32_dfsdm_clk_prepare_enable(dfsdm);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to start clock\n");
		वापस ret;
	पूर्ण

	pm_runसमय_get_noresume(&pdev->dev);
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	ret = of_platक्रमm_populate(pdev->dev.of_node, शून्य, शून्य, &pdev->dev);
	अगर (ret)
		जाओ pm_put;

	pm_runसमय_put(&pdev->dev);

	वापस 0;

pm_put:
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_set_suspended(&pdev->dev);
	pm_runसमय_put_noidle(&pdev->dev);
	sपंचांग32_dfsdm_clk_disable_unprepare(dfsdm);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_dfsdm_core_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_dfsdm *dfsdm = platक्रमm_get_drvdata(pdev);

	pm_runसमय_get_sync(&pdev->dev);
	of_platक्रमm_depopulate(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_set_suspended(&pdev->dev);
	pm_runसमय_put_noidle(&pdev->dev);
	sपंचांग32_dfsdm_clk_disable_unprepare(dfsdm);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_dfsdm_core_suspend(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_dfsdm *dfsdm = dev_get_drvdata(dev);
	काष्ठा dfsdm_priv *priv = to_sपंचांग32_dfsdm_priv(dfsdm);
	पूर्णांक ret;

	ret = pm_runसमय_क्रमce_suspend(dev);
	अगर (ret)
		वापस ret;

	/* Balance devm_regmap_init_mmio_clk() clk_prepare() */
	clk_unprepare(priv->clk);

	वापस pinctrl_pm_select_sleep_state(dev);
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_dfsdm_core_resume(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_dfsdm *dfsdm = dev_get_drvdata(dev);
	काष्ठा dfsdm_priv *priv = to_sपंचांग32_dfsdm_priv(dfsdm);
	पूर्णांक ret;

	ret = pinctrl_pm_select_शेष_state(dev);
	अगर (ret)
		वापस ret;

	ret = clk_prepare(priv->clk);
	अगर (ret)
		वापस ret;

	वापस pm_runसमय_क्रमce_resume(dev);
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_dfsdm_core_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_dfsdm *dfsdm = dev_get_drvdata(dev);

	sपंचांग32_dfsdm_clk_disable_unprepare(dfsdm);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_dfsdm_core_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_dfsdm *dfsdm = dev_get_drvdata(dev);

	वापस sपंचांग32_dfsdm_clk_prepare_enable(dfsdm);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sपंचांग32_dfsdm_core_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(sपंचांग32_dfsdm_core_suspend,
				sपंचांग32_dfsdm_core_resume)
	SET_RUNTIME_PM_OPS(sपंचांग32_dfsdm_core_runसमय_suspend,
			   sपंचांग32_dfsdm_core_runसमय_resume,
			   शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver sपंचांग32_dfsdm_driver = अणु
	.probe = sपंचांग32_dfsdm_probe,
	.हटाओ = sपंचांग32_dfsdm_core_हटाओ,
	.driver = अणु
		.name = "stm32-dfsdm",
		.of_match_table = sपंचांग32_dfsdm_of_match,
		.pm = &sपंचांग32_dfsdm_core_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sपंचांग32_dfsdm_driver);

MODULE_AUTHOR("Arnaud Pouliquen <arnaud.pouliquen@st.com>");
MODULE_DESCRIPTION("STMicroelectronics STM32 dfsdm driver");
MODULE_LICENSE("GPL v2");
