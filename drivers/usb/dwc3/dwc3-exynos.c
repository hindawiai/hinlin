<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * dwc3-exynos.c - Samsung Exynos DWC3 Specअगरic Glue layer
 *
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Author: Anton Tikhomirov <av.tikhomirov@samsung.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/regulator/consumer.h>

#घोषणा DWC3_EXYNOS_MAX_CLOCKS	4

काष्ठा dwc3_exynos_driverdata अणु
	स्थिर अक्षर		*clk_names[DWC3_EXYNOS_MAX_CLOCKS];
	पूर्णांक			num_clks;
	पूर्णांक			suspend_clk_idx;
पूर्ण;

काष्ठा dwc3_exynos अणु
	काष्ठा device		*dev;

	स्थिर अक्षर		**clk_names;
	काष्ठा clk		*clks[DWC3_EXYNOS_MAX_CLOCKS];
	पूर्णांक			num_clks;
	पूर्णांक			suspend_clk_idx;

	काष्ठा regulator	*vdd33;
	काष्ठा regulator	*vdd10;
पूर्ण;

अटल पूर्णांक dwc3_exynos_हटाओ_child(काष्ठा device *dev, व्योम *unused)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);

	platक्रमm_device_unरेजिस्टर(pdev);

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_exynos_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dwc3_exynos	*exynos;
	काष्ठा device		*dev = &pdev->dev;
	काष्ठा device_node	*node = dev->of_node;
	स्थिर काष्ठा dwc3_exynos_driverdata *driver_data;
	पूर्णांक			i, ret;

	exynos = devm_kzalloc(dev, माप(*exynos), GFP_KERNEL);
	अगर (!exynos)
		वापस -ENOMEM;

	driver_data = of_device_get_match_data(dev);
	exynos->dev = dev;
	exynos->num_clks = driver_data->num_clks;
	exynos->clk_names = (स्थिर अक्षर **)driver_data->clk_names;
	exynos->suspend_clk_idx = driver_data->suspend_clk_idx;

	platक्रमm_set_drvdata(pdev, exynos);

	क्रम (i = 0; i < exynos->num_clks; i++) अणु
		exynos->clks[i] = devm_clk_get(dev, exynos->clk_names[i]);
		अगर (IS_ERR(exynos->clks[i])) अणु
			dev_err(dev, "failed to get clock: %s\n",
				exynos->clk_names[i]);
			वापस PTR_ERR(exynos->clks[i]);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < exynos->num_clks; i++) अणु
		ret = clk_prepare_enable(exynos->clks[i]);
		अगर (ret) अणु
			जबतक (i-- > 0)
				clk_disable_unprepare(exynos->clks[i]);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (exynos->suspend_clk_idx >= 0)
		clk_prepare_enable(exynos->clks[exynos->suspend_clk_idx]);

	exynos->vdd33 = devm_regulator_get(dev, "vdd33");
	अगर (IS_ERR(exynos->vdd33)) अणु
		ret = PTR_ERR(exynos->vdd33);
		जाओ vdd33_err;
	पूर्ण
	ret = regulator_enable(exynos->vdd33);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable VDD33 supply\n");
		जाओ vdd33_err;
	पूर्ण

	exynos->vdd10 = devm_regulator_get(dev, "vdd10");
	अगर (IS_ERR(exynos->vdd10)) अणु
		ret = PTR_ERR(exynos->vdd10);
		जाओ vdd10_err;
	पूर्ण
	ret = regulator_enable(exynos->vdd10);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable VDD10 supply\n");
		जाओ vdd10_err;
	पूर्ण

	अगर (node) अणु
		ret = of_platक्रमm_populate(node, शून्य, शून्य, dev);
		अगर (ret) अणु
			dev_err(dev, "failed to add dwc3 core\n");
			जाओ populate_err;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(dev, "no device node, failed to add dwc3 core\n");
		ret = -ENODEV;
		जाओ populate_err;
	पूर्ण

	वापस 0;

populate_err:
	regulator_disable(exynos->vdd10);
vdd10_err:
	regulator_disable(exynos->vdd33);
vdd33_err:
	क्रम (i = exynos->num_clks - 1; i >= 0; i--)
		clk_disable_unprepare(exynos->clks[i]);

	अगर (exynos->suspend_clk_idx >= 0)
		clk_disable_unprepare(exynos->clks[exynos->suspend_clk_idx]);

	वापस ret;
पूर्ण

अटल पूर्णांक dwc3_exynos_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dwc3_exynos	*exynos = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	device_क्रम_each_child(&pdev->dev, शून्य, dwc3_exynos_हटाओ_child);

	क्रम (i = exynos->num_clks - 1; i >= 0; i--)
		clk_disable_unprepare(exynos->clks[i]);

	अगर (exynos->suspend_clk_idx >= 0)
		clk_disable_unprepare(exynos->clks[exynos->suspend_clk_idx]);

	regulator_disable(exynos->vdd33);
	regulator_disable(exynos->vdd10);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dwc3_exynos_driverdata exynos5250_drvdata = अणु
	.clk_names = अणु "usbdrd30" पूर्ण,
	.num_clks = 1,
	.suspend_clk_idx = -1,
पूर्ण;

अटल स्थिर काष्ठा dwc3_exynos_driverdata exynos5433_drvdata = अणु
	.clk_names = अणु "aclk", "susp_clk", "pipe_pclk", "phyclk" पूर्ण,
	.num_clks = 4,
	.suspend_clk_idx = 1,
पूर्ण;

अटल स्थिर काष्ठा dwc3_exynos_driverdata exynos7_drvdata = अणु
	.clk_names = अणु "usbdrd30", "usbdrd30_susp_clk", "usbdrd30_axius_clk" पूर्ण,
	.num_clks = 3,
	.suspend_clk_idx = 1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id exynos_dwc3_match[] = अणु
	अणु
		.compatible = "samsung,exynos5250-dwusb3",
		.data = &exynos5250_drvdata,
	पूर्ण, अणु
		.compatible = "samsung,exynos5433-dwusb3",
		.data = &exynos5433_drvdata,
	पूर्ण, अणु
		.compatible = "samsung,exynos7-dwusb3",
		.data = &exynos7_drvdata,
	पूर्ण, अणु
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, exynos_dwc3_match);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक dwc3_exynos_suspend(काष्ठा device *dev)
अणु
	काष्ठा dwc3_exynos *exynos = dev_get_drvdata(dev);
	पूर्णांक i;

	क्रम (i = exynos->num_clks - 1; i >= 0; i--)
		clk_disable_unprepare(exynos->clks[i]);

	regulator_disable(exynos->vdd33);
	regulator_disable(exynos->vdd10);

	वापस 0;
पूर्ण

अटल पूर्णांक dwc3_exynos_resume(काष्ठा device *dev)
अणु
	काष्ठा dwc3_exynos *exynos = dev_get_drvdata(dev);
	पूर्णांक i, ret;

	ret = regulator_enable(exynos->vdd33);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable VDD33 supply\n");
		वापस ret;
	पूर्ण
	ret = regulator_enable(exynos->vdd10);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable VDD10 supply\n");
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < exynos->num_clks; i++) अणु
		ret = clk_prepare_enable(exynos->clks[i]);
		अगर (ret) अणु
			जबतक (i-- > 0)
				clk_disable_unprepare(exynos->clks[i]);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops dwc3_exynos_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(dwc3_exynos_suspend, dwc3_exynos_resume)
पूर्ण;

#घोषणा DEV_PM_OPS	(&dwc3_exynos_dev_pm_ops)
#अन्यथा
#घोषणा DEV_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल काष्ठा platक्रमm_driver dwc3_exynos_driver = अणु
	.probe		= dwc3_exynos_probe,
	.हटाओ		= dwc3_exynos_हटाओ,
	.driver		= अणु
		.name	= "exynos-dwc3",
		.of_match_table = exynos_dwc3_match,
		.pm	= DEV_PM_OPS,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(dwc3_exynos_driver);

MODULE_AUTHOR("Anton Tikhomirov <av.tikhomirov@samsung.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("DesignWare USB3 Exynos Glue Layer");
