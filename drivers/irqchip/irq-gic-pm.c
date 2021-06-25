<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016 NVIDIA CORPORATION, All Rights Reserved.
 */
#समावेश <linux/module.h>
#समावेश <linux/clk.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/irqchip/arm-gic.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>

काष्ठा gic_clk_data अणु
	अचिन्हित पूर्णांक num_घड़ीs;
	स्थिर अक्षर *स्थिर *घड़ीs;
पूर्ण;

काष्ठा gic_chip_pm अणु
	काष्ठा gic_chip_data *chip_data;
	स्थिर काष्ठा gic_clk_data *clk_data;
	काष्ठा clk_bulk_data *clks;
पूर्ण;

अटल पूर्णांक gic_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा gic_chip_pm *chip_pm = dev_get_drvdata(dev);
	काष्ठा gic_chip_data *gic = chip_pm->chip_data;
	स्थिर काष्ठा gic_clk_data *data = chip_pm->clk_data;
	पूर्णांक ret;

	ret = clk_bulk_prepare_enable(data->num_घड़ीs, chip_pm->clks);
	अगर (ret) अणु
		dev_err(dev, "clk_enable failed: %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * On the very first resume, the poपूर्णांकer to chip_pm->chip_data
	 * will be शून्य and this is पूर्णांकentional, because we करो not
	 * want to restore the GIC on the very first resume. So अगर
	 * the poपूर्णांकer is not valid just वापस.
	 */
	अगर (!gic)
		वापस 0;

	gic_dist_restore(gic);
	gic_cpu_restore(gic);

	वापस 0;
पूर्ण

अटल पूर्णांक gic_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा gic_chip_pm *chip_pm = dev_get_drvdata(dev);
	काष्ठा gic_chip_data *gic = chip_pm->chip_data;
	स्थिर काष्ठा gic_clk_data *data = chip_pm->clk_data;

	gic_dist_save(gic);
	gic_cpu_save(gic);

	clk_bulk_disable_unprepare(data->num_घड़ीs, chip_pm->clks);

	वापस 0;
पूर्ण

अटल पूर्णांक gic_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा gic_clk_data *data;
	काष्ठा gic_chip_pm *chip_pm;
	पूर्णांक ret, irq, i;

	data = of_device_get_match_data(&pdev->dev);
	अगर (!data) अणु
		dev_err(&pdev->dev, "no device match found\n");
		वापस -ENODEV;
	पूर्ण

	chip_pm = devm_kzalloc(dev, माप(*chip_pm), GFP_KERNEL);
	अगर (!chip_pm)
		वापस -ENOMEM;

	irq = irq_of_parse_and_map(dev->of_node, 0);
	अगर (!irq) अणु
		dev_err(dev, "no parent interrupt found!\n");
		वापस -EINVAL;
	पूर्ण

	chip_pm->clks = devm_kसुस्मृति(dev, data->num_घड़ीs,
				     माप(*chip_pm->clks), GFP_KERNEL);
	अगर (!chip_pm->clks)
		वापस -ENOMEM;

	क्रम (i = 0; i < data->num_घड़ीs; i++)
		chip_pm->clks[i].id = data->घड़ीs[i];

	ret = devm_clk_bulk_get(dev, data->num_घड़ीs, chip_pm->clks);
	अगर (ret)
		जाओ irq_dispose;

	chip_pm->clk_data = data;
	dev_set_drvdata(dev, chip_pm);

	pm_runसमय_enable(dev);

	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0)
		जाओ rpm_disable;

	ret = gic_of_init_child(dev, &chip_pm->chip_data, irq);
	अगर (ret)
		जाओ rpm_put;

	pm_runसमय_put(dev);

	dev_info(dev, "GIC IRQ controller registered\n");

	वापस 0;

rpm_put:
	pm_runसमय_put_sync(dev);
rpm_disable:
	pm_runसमय_disable(dev);
irq_dispose:
	irq_dispose_mapping(irq);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops gic_pm_ops = अणु
	SET_RUNTIME_PM_OPS(gic_runसमय_suspend,
			   gic_runसमय_resume, शून्य)
	SET_LATE_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				     pm_runसमय_क्रमce_resume)
पूर्ण;

अटल स्थिर अक्षर * स्थिर gic400_घड़ीs[] = अणु
	"clk",
पूर्ण;

अटल स्थिर काष्ठा gic_clk_data gic400_data = अणु
	.num_घड़ीs = ARRAY_SIZE(gic400_घड़ीs),
	.घड़ीs = gic400_घड़ीs,
पूर्ण;

अटल स्थिर काष्ठा of_device_id gic_match[] = अणु
	अणु .compatible = "nvidia,tegra210-agic",	.data = &gic400_data पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, gic_match);

अटल काष्ठा platक्रमm_driver gic_driver = अणु
	.probe		= gic_probe,
	.driver		= अणु
		.name	= "gic",
		.of_match_table	= gic_match,
		.pm	= &gic_pm_ops,
	पूर्ण
पूर्ण;

builtin_platक्रमm_driver(gic_driver);
