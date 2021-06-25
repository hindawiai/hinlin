<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Samsung SoC USB 1.1/2.0 PHY driver
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 * Author: Kamil Debski <k.debski@samsung.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>
#समावेश "phy-samsung-usb2.h"

अटल पूर्णांक samsung_usb2_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा samsung_usb2_phy_instance *inst = phy_get_drvdata(phy);
	काष्ठा samsung_usb2_phy_driver *drv = inst->drv;
	पूर्णांक ret;

	dev_dbg(drv->dev, "Request to power_on \"%s\" usb phy\n",
		inst->cfg->label);

	अगर (drv->vbus) अणु
		ret = regulator_enable(drv->vbus);
		अगर (ret)
			जाओ err_regulator;
	पूर्ण

	ret = clk_prepare_enable(drv->clk);
	अगर (ret)
		जाओ err_मुख्य_clk;
	ret = clk_prepare_enable(drv->ref_clk);
	अगर (ret)
		जाओ err_instance_clk;
	अगर (inst->cfg->घातer_on) अणु
		spin_lock(&drv->lock);
		ret = inst->cfg->घातer_on(inst);
		spin_unlock(&drv->lock);
		अगर (ret)
			जाओ err_घातer_on;
	पूर्ण

	वापस 0;

err_घातer_on:
	clk_disable_unprepare(drv->ref_clk);
err_instance_clk:
	clk_disable_unprepare(drv->clk);
err_मुख्य_clk:
	अगर (drv->vbus)
		regulator_disable(drv->vbus);
err_regulator:
	वापस ret;
पूर्ण

अटल पूर्णांक samsung_usb2_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा samsung_usb2_phy_instance *inst = phy_get_drvdata(phy);
	काष्ठा samsung_usb2_phy_driver *drv = inst->drv;
	पूर्णांक ret = 0;

	dev_dbg(drv->dev, "Request to power_off \"%s\" usb phy\n",
		inst->cfg->label);
	अगर (inst->cfg->घातer_off) अणु
		spin_lock(&drv->lock);
		ret = inst->cfg->घातer_off(inst);
		spin_unlock(&drv->lock);
		अगर (ret)
			वापस ret;
	पूर्ण
	clk_disable_unprepare(drv->ref_clk);
	clk_disable_unprepare(drv->clk);
	अगर (drv->vbus)
		ret = regulator_disable(drv->vbus);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा phy_ops samsung_usb2_phy_ops = अणु
	.घातer_on	= samsung_usb2_phy_घातer_on,
	.घातer_off	= samsung_usb2_phy_घातer_off,
	.owner		= THIS_MODULE,
पूर्ण;

अटल काष्ठा phy *samsung_usb2_phy_xlate(काष्ठा device *dev,
					काष्ठा of_phandle_args *args)
अणु
	काष्ठा samsung_usb2_phy_driver *drv;

	drv = dev_get_drvdata(dev);
	अगर (!drv)
		वापस ERR_PTR(-EINVAL);

	अगर (WARN_ON(args->args[0] >= drv->cfg->num_phys))
		वापस ERR_PTR(-ENODEV);

	वापस drv->instances[args->args[0]].phy;
पूर्ण

अटल स्थिर काष्ठा of_device_id samsung_usb2_phy_of_match[] = अणु
#अगर_घोषित CONFIG_PHY_EXYNOS4X12_USB2
	अणु
		.compatible = "samsung,exynos3250-usb2-phy",
		.data = &exynos3250_usb2_phy_config,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PHY_EXYNOS4210_USB2
	अणु
		.compatible = "samsung,exynos4210-usb2-phy",
		.data = &exynos4210_usb2_phy_config,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PHY_EXYNOS4X12_USB2
	अणु
		.compatible = "samsung,exynos4x12-usb2-phy",
		.data = &exynos4x12_usb2_phy_config,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PHY_EXYNOS5250_USB2
	अणु
		.compatible = "samsung,exynos5250-usb2-phy",
		.data = &exynos5250_usb2_phy_config,
	पूर्ण,
	अणु
		.compatible = "samsung,exynos5420-usb2-phy",
		.data = &exynos5420_usb2_phy_config,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PHY_S5PV210_USB2
	अणु
		.compatible = "samsung,s5pv210-usb2-phy",
		.data = &s5pv210_usb2_phy_config,
	पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, samsung_usb2_phy_of_match);

अटल पूर्णांक samsung_usb2_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा samsung_usb2_phy_config *cfg;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा phy_provider *phy_provider;
	काष्ठा samsung_usb2_phy_driver *drv;
	पूर्णांक i, ret;

	अगर (!pdev->dev.of_node) अणु
		dev_err(dev, "This driver is required to be instantiated from device tree\n");
		वापस -EINVAL;
	पूर्ण

	cfg = of_device_get_match_data(dev);
	अगर (!cfg)
		वापस -EINVAL;

	drv = devm_kzalloc(dev, काष्ठा_size(drv, instances, cfg->num_phys),
			   GFP_KERNEL);
	अगर (!drv)
		वापस -ENOMEM;

	dev_set_drvdata(dev, drv);
	spin_lock_init(&drv->lock);

	drv->cfg = cfg;
	drv->dev = dev;

	drv->reg_phy = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(drv->reg_phy)) अणु
		dev_err(dev, "Failed to map register memory (phy)\n");
		वापस PTR_ERR(drv->reg_phy);
	पूर्ण

	drv->reg_pmu = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
		"samsung,pmureg-phandle");
	अगर (IS_ERR(drv->reg_pmu)) अणु
		dev_err(dev, "Failed to map PMU registers (via syscon)\n");
		वापस PTR_ERR(drv->reg_pmu);
	पूर्ण

	अगर (drv->cfg->has_mode_चयन) अणु
		drv->reg_sys = syscon_regmap_lookup_by_phandle(
				pdev->dev.of_node, "samsung,sysreg-phandle");
		अगर (IS_ERR(drv->reg_sys)) अणु
			dev_err(dev, "Failed to map system registers (via syscon)\n");
			वापस PTR_ERR(drv->reg_sys);
		पूर्ण
	पूर्ण

	drv->clk = devm_clk_get(dev, "phy");
	अगर (IS_ERR(drv->clk)) अणु
		dev_err(dev, "Failed to get clock of phy controller\n");
		वापस PTR_ERR(drv->clk);
	पूर्ण

	drv->ref_clk = devm_clk_get(dev, "ref");
	अगर (IS_ERR(drv->ref_clk)) अणु
		dev_err(dev, "Failed to get reference clock for the phy controller\n");
		वापस PTR_ERR(drv->ref_clk);
	पूर्ण

	drv->ref_rate = clk_get_rate(drv->ref_clk);
	अगर (drv->cfg->rate_to_clk) अणु
		ret = drv->cfg->rate_to_clk(drv->ref_rate, &drv->ref_reg_val);
		अगर (ret)
			वापस ret;
	पूर्ण

	drv->vbus = devm_regulator_get(dev, "vbus");
	अगर (IS_ERR(drv->vbus)) अणु
		ret = PTR_ERR(drv->vbus);
		अगर (ret == -EPROBE_DEFER)
			वापस ret;
		drv->vbus = शून्य;
	पूर्ण

	क्रम (i = 0; i < drv->cfg->num_phys; i++) अणु
		अक्षर *label = drv->cfg->phys[i].label;
		काष्ठा samsung_usb2_phy_instance *p = &drv->instances[i];

		dev_dbg(dev, "Creating phy \"%s\"\n", label);
		p->phy = devm_phy_create(dev, शून्य, &samsung_usb2_phy_ops);
		अगर (IS_ERR(p->phy)) अणु
			dev_err(drv->dev, "Failed to create usb2_phy \"%s\"\n",
				label);
			वापस PTR_ERR(p->phy);
		पूर्ण

		p->cfg = &drv->cfg->phys[i];
		p->drv = drv;
		phy_set_bus_width(p->phy, 8);
		phy_set_drvdata(p->phy, p);
	पूर्ण

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev,
							samsung_usb2_phy_xlate);
	अगर (IS_ERR(phy_provider)) अणु
		dev_err(drv->dev, "Failed to register phy provider\n");
		वापस PTR_ERR(phy_provider);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver samsung_usb2_phy_driver = अणु
	.probe	= samsung_usb2_phy_probe,
	.driver = अणु
		.of_match_table	= samsung_usb2_phy_of_match,
		.name		= "samsung-usb2-phy",
		.suppress_bind_attrs = true,
	पूर्ण
पूर्ण;

module_platक्रमm_driver(samsung_usb2_phy_driver);
MODULE_DESCRIPTION("Samsung S5P/Exynos SoC USB PHY driver");
MODULE_AUTHOR("Kamil Debski <k.debski@samsung.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:samsung-usb2-phy");
