<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) STMicroelectronics 2017
 *
 * Author: Fabrice Gasnier <fabrice.gasnier@st.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/pm_runसमय.स>

/* STM32 VREFBUF रेजिस्टरs */
#घोषणा STM32_VREFBUF_CSR		0x00

/* STM32 VREFBUF CSR bitfields */
#घोषणा STM32_VRS			GENMASK(6, 4)
#घोषणा STM32_VRR			BIT(3)
#घोषणा STM32_HIZ			BIT(1)
#घोषणा STM32_ENVR			BIT(0)

#घोषणा STM32_VREFBUF_AUTO_SUSPEND_DELAY_MS	10

काष्ठा sपंचांग32_vrefbuf अणु
	व्योम __iomem *base;
	काष्ठा clk *clk;
	काष्ठा device *dev;
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक sपंचांग32_vrefbuf_voltages[] = अणु
	/* Matches resp. VRS = 000b, 001b, 010b, 011b */
	2500000, 2048000, 1800000, 1500000,
पूर्ण;

अटल पूर्णांक sपंचांग32_vrefbuf_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा sपंचांग32_vrefbuf *priv = rdev_get_drvdata(rdev);
	u32 val;
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(priv->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(priv->dev);
		वापस ret;
	पूर्ण

	val = पढ़ोl_relaxed(priv->base + STM32_VREFBUF_CSR);
	val = (val & ~STM32_HIZ) | STM32_ENVR;
	ग_लिखोl_relaxed(val, priv->base + STM32_VREFBUF_CSR);

	/*
	 * Vrefbuf startup समय depends on बाह्यal capacitor: रुको here क्रम
	 * VRR to be set. That means output has reached expected value.
	 * ~650us sleep should be enough क्रम caps up to 1.5uF. Use 10ms as
	 * arbitrary समयout.
	 */
	ret = पढ़ोl_poll_समयout(priv->base + STM32_VREFBUF_CSR, val,
				 val & STM32_VRR, 650, 10000);
	अगर (ret) अणु
		dev_err(&rdev->dev, "stm32 vrefbuf timed out!\n");
		val = पढ़ोl_relaxed(priv->base + STM32_VREFBUF_CSR);
		val = (val & ~STM32_ENVR) | STM32_HIZ;
		ग_लिखोl_relaxed(val, priv->base + STM32_VREFBUF_CSR);
	पूर्ण

	pm_runसमय_mark_last_busy(priv->dev);
	pm_runसमय_put_स्वतःsuspend(priv->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_vrefbuf_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा sपंचांग32_vrefbuf *priv = rdev_get_drvdata(rdev);
	u32 val;
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(priv->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(priv->dev);
		वापस ret;
	पूर्ण

	val = पढ़ोl_relaxed(priv->base + STM32_VREFBUF_CSR);
	val &= ~STM32_ENVR;
	ग_लिखोl_relaxed(val, priv->base + STM32_VREFBUF_CSR);

	pm_runसमय_mark_last_busy(priv->dev);
	pm_runसमय_put_स्वतःsuspend(priv->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_vrefbuf_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा sपंचांग32_vrefbuf *priv = rdev_get_drvdata(rdev);
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(priv->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(priv->dev);
		वापस ret;
	पूर्ण

	ret = पढ़ोl_relaxed(priv->base + STM32_VREFBUF_CSR) & STM32_ENVR;

	pm_runसमय_mark_last_busy(priv->dev);
	pm_runसमय_put_स्वतःsuspend(priv->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_vrefbuf_set_voltage_sel(काष्ठा regulator_dev *rdev,
					 अचिन्हित sel)
अणु
	काष्ठा sपंचांग32_vrefbuf *priv = rdev_get_drvdata(rdev);
	u32 val;
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(priv->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(priv->dev);
		वापस ret;
	पूर्ण

	val = पढ़ोl_relaxed(priv->base + STM32_VREFBUF_CSR);
	val = (val & ~STM32_VRS) | FIELD_PREP(STM32_VRS, sel);
	ग_लिखोl_relaxed(val, priv->base + STM32_VREFBUF_CSR);

	pm_runसमय_mark_last_busy(priv->dev);
	pm_runसमय_put_स्वतःsuspend(priv->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_vrefbuf_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा sपंचांग32_vrefbuf *priv = rdev_get_drvdata(rdev);
	u32 val;
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(priv->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(priv->dev);
		वापस ret;
	पूर्ण

	val = पढ़ोl_relaxed(priv->base + STM32_VREFBUF_CSR);
	ret = FIELD_GET(STM32_VRS, val);

	pm_runसमय_mark_last_busy(priv->dev);
	pm_runसमय_put_स्वतःsuspend(priv->dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा regulator_ops sपंचांग32_vrefbuf_volt_ops = अणु
	.enable		= sपंचांग32_vrefbuf_enable,
	.disable	= sपंचांग32_vrefbuf_disable,
	.is_enabled	= sपंचांग32_vrefbuf_is_enabled,
	.get_voltage_sel = sपंचांग32_vrefbuf_get_voltage_sel,
	.set_voltage_sel = sपंचांग32_vrefbuf_set_voltage_sel,
	.list_voltage	= regulator_list_voltage_table,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc sपंचांग32_vrefbuf_regu = अणु
	.name = "vref",
	.supply_name = "vdda",
	.volt_table = sपंचांग32_vrefbuf_voltages,
	.n_voltages = ARRAY_SIZE(sपंचांग32_vrefbuf_voltages),
	.ops = &sपंचांग32_vrefbuf_volt_ops,
	.off_on_delay = 1000,
	.type = REGULATOR_VOLTAGE,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक sपंचांग32_vrefbuf_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_vrefbuf *priv;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_dev *rdev;
	पूर्णांक ret;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	priv->dev = &pdev->dev;

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	priv->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(priv->clk))
		वापस PTR_ERR(priv->clk);

	pm_runसमय_get_noresume(&pdev->dev);
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev,
					 STM32_VREFBUF_AUTO_SUSPEND_DELAY_MS);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	ret = clk_prepare_enable(priv->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "clk prepare failed with error %d\n", ret);
		जाओ err_pm_stop;
	पूर्ण

	config.dev = &pdev->dev;
	config.driver_data = priv;
	config.of_node = pdev->dev.of_node;
	config.init_data = of_get_regulator_init_data(&pdev->dev,
						      pdev->dev.of_node,
						      &sपंचांग32_vrefbuf_regu);

	rdev = regulator_रेजिस्टर(&sपंचांग32_vrefbuf_regu, &config);
	अगर (IS_ERR(rdev)) अणु
		ret = PTR_ERR(rdev);
		dev_err(&pdev->dev, "register failed with error %d\n", ret);
		जाओ err_clk_dis;
	पूर्ण
	platक्रमm_set_drvdata(pdev, rdev);

	pm_runसमय_mark_last_busy(&pdev->dev);
	pm_runसमय_put_स्वतःsuspend(&pdev->dev);

	वापस 0;

err_clk_dis:
	clk_disable_unprepare(priv->clk);
err_pm_stop:
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_set_suspended(&pdev->dev);
	pm_runसमय_put_noidle(&pdev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_vrefbuf_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regulator_dev *rdev = platक्रमm_get_drvdata(pdev);
	काष्ठा sपंचांग32_vrefbuf *priv = rdev_get_drvdata(rdev);

	pm_runसमय_get_sync(&pdev->dev);
	regulator_unरेजिस्टर(rdev);
	clk_disable_unprepare(priv->clk);
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_set_suspended(&pdev->dev);
	pm_runसमय_put_noidle(&pdev->dev);

	वापस 0;
पूर्ण;

अटल पूर्णांक __maybe_unused sपंचांग32_vrefbuf_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा regulator_dev *rdev = dev_get_drvdata(dev);
	काष्ठा sपंचांग32_vrefbuf *priv = rdev_get_drvdata(rdev);

	clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_vrefbuf_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा regulator_dev *rdev = dev_get_drvdata(dev);
	काष्ठा sपंचांग32_vrefbuf *priv = rdev_get_drvdata(rdev);

	वापस clk_prepare_enable(priv->clk);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sपंचांग32_vrefbuf_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(sपंचांग32_vrefbuf_runसमय_suspend,
			   sपंचांग32_vrefbuf_runसमय_resume,
			   शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id __maybe_unused sपंचांग32_vrefbuf_of_match[] = अणु
	अणु .compatible = "st,stm32-vrefbuf", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_vrefbuf_of_match);

अटल काष्ठा platक्रमm_driver sपंचांग32_vrefbuf_driver = अणु
	.probe = sपंचांग32_vrefbuf_probe,
	.हटाओ = sपंचांग32_vrefbuf_हटाओ,
	.driver = अणु
		.name  = "stm32-vrefbuf",
		.of_match_table = of_match_ptr(sपंचांग32_vrefbuf_of_match),
		.pm = &sपंचांग32_vrefbuf_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sपंचांग32_vrefbuf_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Fabrice Gasnier <fabrice.gasnier@st.com>");
MODULE_DESCRIPTION("STMicroelectronics STM32 VREFBUF driver");
MODULE_ALIAS("platform:stm32-vrefbuf");
