<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SPEAr thermal driver.
 *
 * Copyright (C) 2011-2012 ST Microelectronics
 * Author: Vincenzo Frascino <vincenzo.frascino@st.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/thermal.h>

#घोषणा MD_FACTOR	1000

/* SPEAr Thermal Sensor Dev Structure */
काष्ठा spear_thermal_dev अणु
	/* poपूर्णांकer to base address of the thermal sensor */
	व्योम __iomem *thermal_base;
	/* clk काष्ठाure */
	काष्ठा clk *clk;
	/* poपूर्णांकer to thermal flags */
	अचिन्हित पूर्णांक flags;
पूर्ण;

अटल अंतरभूत पूर्णांक thermal_get_temp(काष्ठा thermal_zone_device *thermal,
				पूर्णांक *temp)
अणु
	काष्ठा spear_thermal_dev *stdev = thermal->devdata;

	/*
	 * Data are पढ़ोy to be पढ़ो after 628 usec from POWERDOWN संकेत
	 * (PDN) = 1
	 */
	*temp = (पढ़ोl_relaxed(stdev->thermal_base) & 0x7F) * MD_FACTOR;
	वापस 0;
पूर्ण

अटल काष्ठा thermal_zone_device_ops ops = अणु
	.get_temp = thermal_get_temp,
पूर्ण;

अटल पूर्णांक __maybe_unused spear_thermal_suspend(काष्ठा device *dev)
अणु
	काष्ठा thermal_zone_device *spear_thermal = dev_get_drvdata(dev);
	काष्ठा spear_thermal_dev *stdev = spear_thermal->devdata;
	अचिन्हित पूर्णांक actual_mask = 0;

	/* Disable SPEAr Thermal Sensor */
	actual_mask = पढ़ोl_relaxed(stdev->thermal_base);
	ग_लिखोl_relaxed(actual_mask & ~stdev->flags, stdev->thermal_base);

	clk_disable(stdev->clk);
	dev_info(dev, "Suspended.\n");

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused spear_thermal_resume(काष्ठा device *dev)
अणु
	काष्ठा thermal_zone_device *spear_thermal = dev_get_drvdata(dev);
	काष्ठा spear_thermal_dev *stdev = spear_thermal->devdata;
	अचिन्हित पूर्णांक actual_mask = 0;
	पूर्णांक ret = 0;

	ret = clk_enable(stdev->clk);
	अगर (ret) अणु
		dev_err(dev, "Can't enable clock\n");
		वापस ret;
	पूर्ण

	/* Enable SPEAr Thermal Sensor */
	actual_mask = पढ़ोl_relaxed(stdev->thermal_base);
	ग_लिखोl_relaxed(actual_mask | stdev->flags, stdev->thermal_base);

	dev_info(dev, "Resumed.\n");

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(spear_thermal_pm_ops, spear_thermal_suspend,
		spear_thermal_resume);

अटल पूर्णांक spear_thermal_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा thermal_zone_device *spear_thermal = शून्य;
	काष्ठा spear_thermal_dev *stdev;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा resource *res;
	पूर्णांक ret = 0, val;

	अगर (!np || !of_property_पढ़ो_u32(np, "st,thermal-flags", &val)) अणु
		dev_err(&pdev->dev, "Failed: DT Pdata not passed\n");
		वापस -EINVAL;
	पूर्ण

	stdev = devm_kzalloc(&pdev->dev, माप(*stdev), GFP_KERNEL);
	अगर (!stdev)
		वापस -ENOMEM;

	/* Enable thermal sensor */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	stdev->thermal_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(stdev->thermal_base))
		वापस PTR_ERR(stdev->thermal_base);

	stdev->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(stdev->clk)) अणु
		dev_err(&pdev->dev, "Can't get clock\n");
		वापस PTR_ERR(stdev->clk);
	पूर्ण

	ret = clk_enable(stdev->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Can't enable clock\n");
		वापस ret;
	पूर्ण

	stdev->flags = val;
	ग_लिखोl_relaxed(stdev->flags, stdev->thermal_base);

	spear_thermal = thermal_zone_device_रेजिस्टर("spear_thermal", 0, 0,
				stdev, &ops, शून्य, 0, 0);
	अगर (IS_ERR(spear_thermal)) अणु
		dev_err(&pdev->dev, "thermal zone device is NULL\n");
		ret = PTR_ERR(spear_thermal);
		जाओ disable_clk;
	पूर्ण
	ret = thermal_zone_device_enable(spear_thermal);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Cannot enable thermal zone\n");
		जाओ unरेजिस्टर_tzd;
	पूर्ण

	platक्रमm_set_drvdata(pdev, spear_thermal);

	dev_info(&spear_thermal->device, "Thermal Sensor Loaded at: 0x%p.\n",
			stdev->thermal_base);

	वापस 0;

unरेजिस्टर_tzd:
	thermal_zone_device_unरेजिस्टर(spear_thermal);
disable_clk:
	clk_disable(stdev->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक spear_thermal_निकास(काष्ठा platक्रमm_device *pdev)
अणु
	अचिन्हित पूर्णांक actual_mask = 0;
	काष्ठा thermal_zone_device *spear_thermal = platक्रमm_get_drvdata(pdev);
	काष्ठा spear_thermal_dev *stdev = spear_thermal->devdata;

	thermal_zone_device_unरेजिस्टर(spear_thermal);

	/* Disable SPEAr Thermal Sensor */
	actual_mask = पढ़ोl_relaxed(stdev->thermal_base);
	ग_लिखोl_relaxed(actual_mask & ~stdev->flags, stdev->thermal_base);

	clk_disable(stdev->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id spear_thermal_id_table[] = अणु
	अणु .compatible = "st,thermal-spear1340" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, spear_thermal_id_table);

अटल काष्ठा platक्रमm_driver spear_thermal_driver = अणु
	.probe = spear_thermal_probe,
	.हटाओ = spear_thermal_निकास,
	.driver = अणु
		.name = "spear_thermal",
		.pm = &spear_thermal_pm_ops,
		.of_match_table = spear_thermal_id_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(spear_thermal_driver);

MODULE_AUTHOR("Vincenzo Frascino <vincenzo.frascino@st.com>");
MODULE_DESCRIPTION("SPEAr thermal driver");
MODULE_LICENSE("GPL");
