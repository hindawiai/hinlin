<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Device access क्रम Dialog DA9063 modules
 *
 * Copyright 2012 Dialog Semiconductors Ltd.
 * Copyright 2013 Philipp Zabel, Pengutronix
 *
 * Author: Krystian Garbaciak, Dialog Semiconductor
 * Author: Michal Hajduk, Dialog Semiconductor
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mutex.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/regmap.h>

#समावेश <linux/mfd/da9063/core.h>
#समावेश <linux/mfd/da9063/रेजिस्टरs.h>

#समावेश <linux/proc_fs.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/uaccess.h>


अटल स्थिर काष्ठा resource da9063_regulators_resources[] = अणु
	अणु
		.name	= "LDO_LIM",
		.start	= DA9063_IRQ_LDO_LIM,
		.end	= DA9063_IRQ_LDO_LIM,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource da9063_rtc_resources[] = अणु
	अणु
		.name	= "ALARM",
		.start	= DA9063_IRQ_ALARM,
		.end	= DA9063_IRQ_ALARM,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु
		.name	= "TICK",
		.start	= DA9063_IRQ_TICK,
		.end	= DA9063_IRQ_TICK,
		.flags	= IORESOURCE_IRQ,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा resource da9063_onkey_resources[] = अणु
	अणु
		.name	= "ONKEY",
		.start	= DA9063_IRQ_ONKEY,
		.end	= DA9063_IRQ_ONKEY,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource da9063_hwmon_resources[] = अणु
	अणु
		.start	= DA9063_IRQ_ADC_RDY,
		.end	= DA9063_IRQ_ADC_RDY,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;


अटल स्थिर काष्ठा mfd_cell da9063_common_devs[] = अणु
	अणु
		.name		= DA9063_DRVNAME_REGULATORS,
		.num_resources	= ARRAY_SIZE(da9063_regulators_resources),
		.resources	= da9063_regulators_resources,
	पूर्ण,
	अणु
		.name		= DA9063_DRVNAME_LEDS,
	पूर्ण,
	अणु
		.name		= DA9063_DRVNAME_WATCHDOG,
		.of_compatible	= "dlg,da9063-watchdog",
	पूर्ण,
	अणु
		.name		= DA9063_DRVNAME_HWMON,
		.num_resources	= ARRAY_SIZE(da9063_hwmon_resources),
		.resources	= da9063_hwmon_resources,
	पूर्ण,
	अणु
		.name		= DA9063_DRVNAME_ONKEY,
		.num_resources	= ARRAY_SIZE(da9063_onkey_resources),
		.resources	= da9063_onkey_resources,
		.of_compatible = "dlg,da9063-onkey",
	पूर्ण,
	अणु
		.name		= DA9063_DRVNAME_VIBRATION,
	पूर्ण,
पूर्ण;

/* Only present on DA9063 , not on DA9063L */
अटल स्थिर काष्ठा mfd_cell da9063_devs[] = अणु
	अणु
		.name		= DA9063_DRVNAME_RTC,
		.num_resources	= ARRAY_SIZE(da9063_rtc_resources),
		.resources	= da9063_rtc_resources,
		.of_compatible	= "dlg,da9063-rtc",
	पूर्ण,
पूर्ण;

अटल पूर्णांक da9063_clear_fault_log(काष्ठा da9063 *da9063)
अणु
	पूर्णांक ret = 0;
	पूर्णांक fault_log = 0;

	ret = regmap_पढ़ो(da9063->regmap, DA9063_REG_FAULT_LOG, &fault_log);
	अगर (ret < 0) अणु
		dev_err(da9063->dev, "Cannot read FAULT_LOG.\n");
		वापस -EIO;
	पूर्ण

	अगर (fault_log) अणु
		अगर (fault_log & DA9063_TWD_ERROR)
			dev_dbg(da9063->dev,
				"Fault log entry detected: DA9063_TWD_ERROR\n");
		अगर (fault_log & DA9063_POR)
			dev_dbg(da9063->dev,
				"Fault log entry detected: DA9063_POR\n");
		अगर (fault_log & DA9063_VDD_FAULT)
			dev_dbg(da9063->dev,
				"Fault log entry detected: DA9063_VDD_FAULT\n");
		अगर (fault_log & DA9063_VDD_START)
			dev_dbg(da9063->dev,
				"Fault log entry detected: DA9063_VDD_START\n");
		अगर (fault_log & DA9063_TEMP_CRIT)
			dev_dbg(da9063->dev,
				"Fault log entry detected: DA9063_TEMP_CRIT\n");
		अगर (fault_log & DA9063_KEY_RESET)
			dev_dbg(da9063->dev,
				"Fault log entry detected: DA9063_KEY_RESET\n");
		अगर (fault_log & DA9063_NSHUTDOWN)
			dev_dbg(da9063->dev,
				"Fault log entry detected: DA9063_NSHUTDOWN\n");
		अगर (fault_log & DA9063_WAIT_SHUT)
			dev_dbg(da9063->dev,
				"Fault log entry detected: DA9063_WAIT_SHUT\n");
	पूर्ण

	ret = regmap_ग_लिखो(da9063->regmap,
			   DA9063_REG_FAULT_LOG,
			   fault_log);
	अगर (ret < 0)
		dev_err(da9063->dev,
			"Cannot reset FAULT_LOG values %d\n", ret);

	वापस ret;
पूर्ण

पूर्णांक da9063_device_init(काष्ठा da9063 *da9063, अचिन्हित पूर्णांक irq)
अणु
	पूर्णांक ret;

	ret = da9063_clear_fault_log(da9063);
	अगर (ret < 0)
		dev_err(da9063->dev, "Cannot clear fault log\n");

	da9063->flags = 0;
	da9063->irq_base = -1;
	da9063->chip_irq = irq;

	ret = da9063_irq_init(da9063);
	अगर (ret) अणु
		dev_err(da9063->dev, "Cannot initialize interrupts.\n");
		वापस ret;
	पूर्ण

	da9063->irq_base = regmap_irq_chip_get_base(da9063->regmap_irq);

	ret = devm_mfd_add_devices(da9063->dev, PLATFORM_DEVID_NONE,
				   da9063_common_devs,
				   ARRAY_SIZE(da9063_common_devs),
				   शून्य, da9063->irq_base, शून्य);
	अगर (ret) अणु
		dev_err(da9063->dev, "Failed to add child devices\n");
		वापस ret;
	पूर्ण

	अगर (da9063->type == PMIC_TYPE_DA9063) अणु
		ret = devm_mfd_add_devices(da9063->dev, PLATFORM_DEVID_NONE,
					   da9063_devs, ARRAY_SIZE(da9063_devs),
					   शून्य, da9063->irq_base, शून्य);
		अगर (ret) अणु
			dev_err(da9063->dev, "Failed to add child devices\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

MODULE_DESCRIPTION("PMIC driver for Dialog DA9063");
MODULE_AUTHOR("Krystian Garbaciak");
MODULE_AUTHOR("Michal Hajduk");
MODULE_LICENSE("GPL");
