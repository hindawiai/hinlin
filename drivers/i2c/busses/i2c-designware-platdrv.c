<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Synopsys DesignWare I2C adapter driver.
 *
 * Based on the TI DAVINCI I2C adapter driver.
 *
 * Copyright (C) 2006 Texas Instruments.
 * Copyright (C) 2007 MontaVista Software Inc.
 * Copyright (C) 2009 Provigent Ltd.
 */
#समावेश <linux/acpi.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmi.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/suspend.h>

#समावेश "i2c-designware-core.h"

अटल u32 i2c_dw_get_clk_rate_khz(काष्ठा dw_i2c_dev *dev)
अणु
	वापस clk_get_rate(dev->clk)/1000;
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id dw_i2c_acpi_match[] = अणु
	अणु "INT33C2", 0 पूर्ण,
	अणु "INT33C3", 0 पूर्ण,
	अणु "INT3432", 0 पूर्ण,
	अणु "INT3433", 0 पूर्ण,
	अणु "80860F41", ACCESS_NO_IRQ_SUSPEND पूर्ण,
	अणु "808622C1", ACCESS_NO_IRQ_SUSPEND पूर्ण,
	अणु "AMD0010", ACCESS_INTR_MASK पूर्ण,
	अणु "AMDI0010", ACCESS_INTR_MASK पूर्ण,
	अणु "AMDI0510", 0 पूर्ण,
	अणु "APMC0D0F", 0 पूर्ण,
	अणु "HISI02A1", 0 पूर्ण,
	अणु "HISI02A2", 0 पूर्ण,
	अणु "HISI02A3", 0 पूर्ण,
	अणु "HYGO0010", ACCESS_INTR_MASK पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, dw_i2c_acpi_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_OF
#घोषणा BT1_I2C_CTL			0x100
#घोषणा BT1_I2C_CTL_ADDR_MASK		GENMASK(7, 0)
#घोषणा BT1_I2C_CTL_WR			BIT(8)
#घोषणा BT1_I2C_CTL_GO			BIT(31)
#घोषणा BT1_I2C_DI			0x104
#घोषणा BT1_I2C_DO			0x108

अटल पूर्णांक bt1_i2c_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val)
अणु
	काष्ठा dw_i2c_dev *dev = context;
	पूर्णांक ret;

	/*
	 * Note these methods shouldn't ever fail because the प्रणाली controller
	 * रेजिस्टरs are memory mapped. We check the वापस value just in हाल.
	 */
	ret = regmap_ग_लिखो(dev->sysmap, BT1_I2C_CTL,
			   BT1_I2C_CTL_GO | (reg & BT1_I2C_CTL_ADDR_MASK));
	अगर (ret)
		वापस ret;

	वापस regmap_पढ़ो(dev->sysmap, BT1_I2C_DO, val);
पूर्ण

अटल पूर्णांक bt1_i2c_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	काष्ठा dw_i2c_dev *dev = context;
	पूर्णांक ret;

	ret = regmap_ग_लिखो(dev->sysmap, BT1_I2C_DI, val);
	अगर (ret)
		वापस ret;

	वापस regmap_ग_लिखो(dev->sysmap, BT1_I2C_CTL,
		BT1_I2C_CTL_GO | BT1_I2C_CTL_WR | (reg & BT1_I2C_CTL_ADDR_MASK));
पूर्ण

अटल काष्ठा regmap_config bt1_i2c_cfg = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.fast_io = true,
	.reg_पढ़ो = bt1_i2c_पढ़ो,
	.reg_ग_लिखो = bt1_i2c_ग_लिखो,
	.max_रेजिस्टर = DW_IC_COMP_TYPE,
पूर्ण;

अटल पूर्णांक bt1_i2c_request_regs(काष्ठा dw_i2c_dev *dev)
अणु
	dev->sysmap = syscon_node_to_regmap(dev->dev->of_node->parent);
	अगर (IS_ERR(dev->sysmap))
		वापस PTR_ERR(dev->sysmap);

	dev->map = devm_regmap_init(dev->dev, शून्य, dev, &bt1_i2c_cfg);
	वापस PTR_ERR_OR_ZERO(dev->map);
पूर्ण

#घोषणा MSCC_ICPU_CFG_TWI_DELAY		0x0
#घोषणा MSCC_ICPU_CFG_TWI_DELAY_ENABLE	BIT(0)
#घोषणा MSCC_ICPU_CFG_TWI_SPIKE_FILTER	0x4

अटल पूर्णांक mscc_twi_set_sda_hold_समय(काष्ठा dw_i2c_dev *dev)
अणु
	ग_लिखोl((dev->sda_hold_समय << 1) | MSCC_ICPU_CFG_TWI_DELAY_ENABLE,
	       dev->ext + MSCC_ICPU_CFG_TWI_DELAY);

	वापस 0;
पूर्ण

अटल पूर्णांक dw_i2c_of_configure(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dw_i2c_dev *dev = platक्रमm_get_drvdata(pdev);

	चयन (dev->flags & MODEL_MASK) अणु
	हाल MODEL_MSCC_OCELOT:
		dev->ext = devm_platक्रमm_ioremap_resource(pdev, 1);
		अगर (!IS_ERR(dev->ext))
			dev->set_sda_hold_समय = mscc_twi_set_sda_hold_समय;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id dw_i2c_of_match[] = अणु
	अणु .compatible = "snps,designware-i2c", पूर्ण,
	अणु .compatible = "mscc,ocelot-i2c", .data = (व्योम *)MODEL_MSCC_OCELOT पूर्ण,
	अणु .compatible = "baikal,bt1-sys-i2c", .data = (व्योम *)MODEL_BAIKAL_BT1 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, dw_i2c_of_match);
#अन्यथा
अटल पूर्णांक bt1_i2c_request_regs(काष्ठा dw_i2c_dev *dev)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक dw_i2c_of_configure(काष्ठा platक्रमm_device *pdev)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

अटल व्योम dw_i2c_plat_pm_cleanup(काष्ठा dw_i2c_dev *dev)
अणु
	pm_runसमय_disable(dev->dev);

	अगर (dev->shared_with_punit)
		pm_runसमय_put_noidle(dev->dev);
पूर्ण

अटल पूर्णांक dw_i2c_plat_request_regs(काष्ठा dw_i2c_dev *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev->dev);
	पूर्णांक ret;

	चयन (dev->flags & MODEL_MASK) अणु
	हाल MODEL_BAIKAL_BT1:
		ret = bt1_i2c_request_regs(dev);
		अवरोध;
	शेष:
		dev->base = devm_platक्रमm_ioremap_resource(pdev, 0);
		ret = PTR_ERR_OR_ZERO(dev->base);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id dw_i2c_hwmon_class_dmi[] = अणु
	अणु
		.ident = "Qtechnology QT5222",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Qtechnology"),
			DMI_MATCH(DMI_PRODUCT_NAME, "QT5222"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण /* terminate list */
पूर्ण;

अटल पूर्णांक dw_i2c_plat_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा i2c_adapter *adap;
	काष्ठा dw_i2c_dev *dev;
	काष्ठा i2c_timings *t;
	पूर्णांक irq, ret;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	dev = devm_kzalloc(&pdev->dev, माप(काष्ठा dw_i2c_dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	dev->flags = (uपूर्णांकptr_t)device_get_match_data(&pdev->dev);
	dev->dev = &pdev->dev;
	dev->irq = irq;
	platक्रमm_set_drvdata(pdev, dev);

	ret = dw_i2c_plat_request_regs(dev);
	अगर (ret)
		वापस ret;

	dev->rst = devm_reset_control_get_optional_exclusive(&pdev->dev, शून्य);
	अगर (IS_ERR(dev->rst))
		वापस PTR_ERR(dev->rst);

	reset_control_deनिश्चित(dev->rst);

	t = &dev->timings;
	i2c_parse_fw_timings(&pdev->dev, t, false);

	i2c_dw_adjust_bus_speed(dev);

	अगर (pdev->dev.of_node)
		dw_i2c_of_configure(pdev);

	अगर (has_acpi_companion(&pdev->dev))
		i2c_dw_acpi_configure(&pdev->dev);

	ret = i2c_dw_validate_speed(dev);
	अगर (ret)
		जाओ निकास_reset;

	ret = i2c_dw_probe_lock_support(dev);
	अगर (ret)
		जाओ निकास_reset;

	i2c_dw_configure(dev);

	/* Optional पूर्णांकerface घड़ी */
	dev->pclk = devm_clk_get_optional(&pdev->dev, "pclk");
	अगर (IS_ERR(dev->pclk)) अणु
		ret = PTR_ERR(dev->pclk);
		जाओ निकास_reset;
	पूर्ण

	dev->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (!i2c_dw_prepare_clk(dev, true)) अणु
		u64 clk_khz;

		dev->get_clk_rate_khz = i2c_dw_get_clk_rate_khz;
		clk_khz = dev->get_clk_rate_khz(dev);

		अगर (!dev->sda_hold_समय && t->sda_hold_ns)
			dev->sda_hold_समय =
				भाग_u64(clk_khz * t->sda_hold_ns + 500000, 1000000);
	पूर्ण

	adap = &dev->adapter;
	adap->owner = THIS_MODULE;
	adap->class = dmi_check_प्रणाली(dw_i2c_hwmon_class_dmi) ?
					I2C_CLASS_HWMON : I2C_CLASS_DEPRECATED;
	ACPI_COMPANION_SET(&adap->dev, ACPI_COMPANION(&pdev->dev));
	adap->dev.of_node = pdev->dev.of_node;
	adap->nr = -1;

	अगर (dev->flags & ACCESS_NO_IRQ_SUSPEND) अणु
		dev_pm_set_driver_flags(&pdev->dev,
					DPM_FLAG_SMART_PREPARE |
					DPM_FLAG_MAY_SKIP_RESUME);
	पूर्ण अन्यथा अणु
		dev_pm_set_driver_flags(&pdev->dev,
					DPM_FLAG_SMART_PREPARE |
					DPM_FLAG_SMART_SUSPEND |
					DPM_FLAG_MAY_SKIP_RESUME);
	पूर्ण

	/* The code below assumes runसमय PM to be disabled. */
	WARN_ON(pm_runसमय_enabled(&pdev->dev));

	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, 1000);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_set_active(&pdev->dev);

	अगर (dev->shared_with_punit)
		pm_runसमय_get_noresume(&pdev->dev);

	pm_runसमय_enable(&pdev->dev);

	ret = i2c_dw_probe(dev);
	अगर (ret)
		जाओ निकास_probe;

	वापस ret;

निकास_probe:
	dw_i2c_plat_pm_cleanup(dev);
निकास_reset:
	reset_control_निश्चित(dev->rst);
	वापस ret;
पूर्ण

अटल पूर्णांक dw_i2c_plat_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dw_i2c_dev *dev = platक्रमm_get_drvdata(pdev);

	pm_runसमय_get_sync(&pdev->dev);

	i2c_del_adapter(&dev->adapter);

	dev->disable(dev);

	pm_runसमय_करोnt_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_put_sync(&pdev->dev);
	dw_i2c_plat_pm_cleanup(dev);

	reset_control_निश्चित(dev->rst);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक dw_i2c_plat_prepare(काष्ठा device *dev)
अणु
	/*
	 * If the ACPI companion device object is present क्रम this device, it
	 * may be accessed during suspend and resume of other devices via I2C
	 * operation regions, so tell the PM core and middle layers to aव्योम
	 * skipping प्रणाली suspend/resume callbacks क्रम it in that हाल.
	 */
	वापस !has_acpi_companion(dev);
पूर्ण

अटल व्योम dw_i2c_plat_complete(काष्ठा device *dev)
अणु
	/*
	 * The device can only be in runसमय suspend at this poपूर्णांक अगर it has not
	 * been resumed throughout the ending प्रणाली suspend/resume cycle, so अगर
	 * the platक्रमm firmware might mess up with it, request the runसमय PM
	 * framework to resume it.
	 */
	अगर (pm_runसमय_suspended(dev) && pm_resume_via_firmware())
		pm_request_resume(dev);
पूर्ण
#अन्यथा
#घोषणा dw_i2c_plat_prepare	शून्य
#घोषणा dw_i2c_plat_complete	शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल पूर्णांक dw_i2c_plat_suspend(काष्ठा device *dev)
अणु
	काष्ठा dw_i2c_dev *i_dev = dev_get_drvdata(dev);

	i_dev->suspended = true;

	अगर (i_dev->shared_with_punit)
		वापस 0;

	i_dev->disable(i_dev);
	i2c_dw_prepare_clk(i_dev, false);

	वापस 0;
पूर्ण

अटल पूर्णांक dw_i2c_plat_resume(काष्ठा device *dev)
अणु
	काष्ठा dw_i2c_dev *i_dev = dev_get_drvdata(dev);

	अगर (!i_dev->shared_with_punit)
		i2c_dw_prepare_clk(i_dev, true);

	i_dev->init(i_dev);
	i_dev->suspended = false;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops dw_i2c_dev_pm_ops = अणु
	.prepare = dw_i2c_plat_prepare,
	.complete = dw_i2c_plat_complete,
	SET_LATE_SYSTEM_SLEEP_PM_OPS(dw_i2c_plat_suspend, dw_i2c_plat_resume)
	SET_RUNTIME_PM_OPS(dw_i2c_plat_suspend, dw_i2c_plat_resume, शून्य)
पूर्ण;

#घोषणा DW_I2C_DEV_PMOPS (&dw_i2c_dev_pm_ops)
#अन्यथा
#घोषणा DW_I2C_DEV_PMOPS शून्य
#पूर्ण_अगर

/* Work with hotplug and coldplug */
MODULE_ALIAS("platform:i2c_designware");

अटल काष्ठा platक्रमm_driver dw_i2c_driver = अणु
	.probe = dw_i2c_plat_probe,
	.हटाओ = dw_i2c_plat_हटाओ,
	.driver		= अणु
		.name	= "i2c_designware",
		.of_match_table = of_match_ptr(dw_i2c_of_match),
		.acpi_match_table = ACPI_PTR(dw_i2c_acpi_match),
		.pm	= DW_I2C_DEV_PMOPS,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init dw_i2c_init_driver(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&dw_i2c_driver);
पूर्ण
subsys_initcall(dw_i2c_init_driver);

अटल व्योम __निकास dw_i2c_निकास_driver(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&dw_i2c_driver);
पूर्ण
module_निकास(dw_i2c_निकास_driver);

MODULE_AUTHOR("Baruch Siach <baruch@tkos.co.il>");
MODULE_DESCRIPTION("Synopsys DesignWare I2C bus adapter");
MODULE_LICENSE("GPL");
