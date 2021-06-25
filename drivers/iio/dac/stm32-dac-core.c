<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file is part of STM32 DAC driver
 *
 * Copyright (C) 2017, STMicroelectronics - All Rights Reserved
 * Author: Fabrice Gasnier <fabrice.gasnier@st.com>.
 *
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reset.h>

#समावेश "stm32-dac-core.h"

/**
 * काष्ठा sपंचांग32_dac_priv - sपंचांग32 DAC core निजी data
 * @pclk:		peripheral घड़ी common क्रम all DACs
 * @vref:		regulator reference
 * @common:		Common data क्रम all DAC instances
 */
काष्ठा sपंचांग32_dac_priv अणु
	काष्ठा clk *pclk;
	काष्ठा regulator *vref;
	काष्ठा sपंचांग32_dac_common common;
पूर्ण;

/**
 * काष्ठा sपंचांग32_dac_cfg - DAC configuration
 * @has_hfsel: DAC has high frequency control
 */
काष्ठा sपंचांग32_dac_cfg अणु
	bool has_hfsel;
पूर्ण;

अटल काष्ठा sपंचांग32_dac_priv *to_sपंचांग32_dac_priv(काष्ठा sपंचांग32_dac_common *com)
अणु
	वापस container_of(com, काष्ठा sपंचांग32_dac_priv, common);
पूर्ण

अटल स्थिर काष्ठा regmap_config sपंचांग32_dac_regmap_cfg = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = माप(u32),
	.max_रेजिस्टर = 0x3fc,
पूर्ण;

अटल पूर्णांक sपंचांग32_dac_core_hw_start(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_dac_common *common = dev_get_drvdata(dev);
	काष्ठा sपंचांग32_dac_priv *priv = to_sपंचांग32_dac_priv(common);
	पूर्णांक ret;

	ret = regulator_enable(priv->vref);
	अगर (ret < 0) अणु
		dev_err(dev, "vref enable failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(priv->pclk);
	अगर (ret < 0) अणु
		dev_err(dev, "pclk enable failed: %d\n", ret);
		जाओ err_regulator_disable;
	पूर्ण

	वापस 0;

err_regulator_disable:
	regulator_disable(priv->vref);

	वापस ret;
पूर्ण

अटल व्योम sपंचांग32_dac_core_hw_stop(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_dac_common *common = dev_get_drvdata(dev);
	काष्ठा sपंचांग32_dac_priv *priv = to_sपंचांग32_dac_priv(common);

	clk_disable_unprepare(priv->pclk);
	regulator_disable(priv->vref);
पूर्ण

अटल पूर्णांक sपंचांग32_dac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा sपंचांग32_dac_cfg *cfg;
	काष्ठा sपंचांग32_dac_priv *priv;
	काष्ठा regmap *regmap;
	काष्ठा resource *res;
	व्योम __iomem *mmio;
	काष्ठा reset_control *rst;
	पूर्णांक ret;

	अगर (!dev->of_node)
		वापस -ENODEV;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, &priv->common);

	cfg = (स्थिर काष्ठा sपंचांग32_dac_cfg *)
		of_match_device(dev->driver->of_match_table, dev)->data;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	mmio = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(mmio))
		वापस PTR_ERR(mmio);

	regmap = devm_regmap_init_mmio_clk(dev, "pclk", mmio,
					   &sपंचांग32_dac_regmap_cfg);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);
	priv->common.regmap = regmap;

	priv->pclk = devm_clk_get(dev, "pclk");
	अगर (IS_ERR(priv->pclk)) अणु
		ret = PTR_ERR(priv->pclk);
		dev_err(dev, "pclk get failed\n");
		वापस ret;
	पूर्ण

	priv->vref = devm_regulator_get(dev, "vref");
	अगर (IS_ERR(priv->vref)) अणु
		ret = PTR_ERR(priv->vref);
		dev_err(dev, "vref get failed, %d\n", ret);
		वापस ret;
	पूर्ण

	pm_runसमय_get_noresume(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);

	ret = sपंचांग32_dac_core_hw_start(dev);
	अगर (ret)
		जाओ err_pm_stop;

	ret = regulator_get_voltage(priv->vref);
	अगर (ret < 0) अणु
		dev_err(dev, "vref get voltage failed, %d\n", ret);
		जाओ err_hw_stop;
	पूर्ण
	priv->common.vref_mv = ret / 1000;
	dev_dbg(dev, "vref+=%dmV\n", priv->common.vref_mv);

	rst = devm_reset_control_get_optional_exclusive(dev, शून्य);
	अगर (rst) अणु
		अगर (IS_ERR(rst)) अणु
			ret = dev_err_probe(dev, PTR_ERR(rst), "reset get failed\n");
			जाओ err_hw_stop;
		पूर्ण

		reset_control_निश्चित(rst);
		udelay(2);
		reset_control_deनिश्चित(rst);
	पूर्ण

	अगर (cfg && cfg->has_hfsel) अणु
		/* When घड़ी speed is higher than 80MHz, set HFSEL */
		priv->common.hfsel = (clk_get_rate(priv->pclk) > 80000000UL);
		ret = regmap_update_bits(regmap, STM32_DAC_CR,
					 STM32H7_DAC_CR_HFSEL,
					 priv->common.hfsel ?
					 STM32H7_DAC_CR_HFSEL : 0);
		अगर (ret)
			जाओ err_hw_stop;
	पूर्ण


	ret = of_platक्रमm_populate(pdev->dev.of_node, शून्य, शून्य, dev);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to populate DT children\n");
		जाओ err_hw_stop;
	पूर्ण

	pm_runसमय_put(dev);

	वापस 0;

err_hw_stop:
	sपंचांग32_dac_core_hw_stop(dev);
err_pm_stop:
	pm_runसमय_disable(dev);
	pm_runसमय_set_suspended(dev);
	pm_runसमय_put_noidle(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_dac_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_get_sync(&pdev->dev);
	of_platक्रमm_depopulate(&pdev->dev);
	sपंचांग32_dac_core_hw_stop(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_set_suspended(&pdev->dev);
	pm_runसमय_put_noidle(&pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_dac_core_resume(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_dac_common *common = dev_get_drvdata(dev);
	काष्ठा sपंचांग32_dac_priv *priv = to_sपंचांग32_dac_priv(common);
	पूर्णांक ret;

	अगर (priv->common.hfsel) अणु
		/* restore hfsel (maybe lost under low घातer state) */
		ret = regmap_update_bits(priv->common.regmap, STM32_DAC_CR,
					 STM32H7_DAC_CR_HFSEL,
					 STM32H7_DAC_CR_HFSEL);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस pm_runसमय_क्रमce_resume(dev);
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_dac_core_runसमय_suspend(काष्ठा device *dev)
अणु
	sपंचांग32_dac_core_hw_stop(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_dac_core_runसमय_resume(काष्ठा device *dev)
अणु
	वापस sपंचांग32_dac_core_hw_start(dev);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sपंचांग32_dac_core_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend, sपंचांग32_dac_core_resume)
	SET_RUNTIME_PM_OPS(sपंचांग32_dac_core_runसमय_suspend,
			   sपंचांग32_dac_core_runसमय_resume,
			   शून्य)
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_dac_cfg sपंचांग32h7_dac_cfg = अणु
	.has_hfsel = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sपंचांग32_dac_of_match[] = अणु
	अणु
		.compatible = "st,stm32f4-dac-core",
	पूर्ण, अणु
		.compatible = "st,stm32h7-dac-core",
		.data = (व्योम *)&sपंचांग32h7_dac_cfg,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_dac_of_match);

अटल काष्ठा platक्रमm_driver sपंचांग32_dac_driver = अणु
	.probe = sपंचांग32_dac_probe,
	.हटाओ = sपंचांग32_dac_हटाओ,
	.driver = अणु
		.name = "stm32-dac-core",
		.of_match_table = sपंचांग32_dac_of_match,
		.pm = &sपंचांग32_dac_core_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sपंचांग32_dac_driver);

MODULE_AUTHOR("Fabrice Gasnier <fabrice.gasnier@st.com>");
MODULE_DESCRIPTION("STMicroelectronics STM32 DAC core driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:stm32-dac-core");
