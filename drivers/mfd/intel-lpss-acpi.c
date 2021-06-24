<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel LPSS ACPI support.
 *
 * Copyright (C) 2015, Intel Corporation
 *
 * Authors: Andy Shevchenko <andriy.shevchenko@linux.पूर्णांकel.com>
 *          Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>

#समावेश "intel-lpss.h"

अटल स्थिर काष्ठा पूर्णांकel_lpss_platक्रमm_info spt_info = अणु
	.clk_rate = 120000000,
पूर्ण;

अटल स्थिर काष्ठा property_entry spt_i2c_properties[] = अणु
	PROPERTY_ENTRY_U32("i2c-sda-hold-time-ns", 230),
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा software_node spt_i2c_node = अणु
	.properties = spt_i2c_properties,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_lpss_platक्रमm_info spt_i2c_info = अणु
	.clk_rate = 120000000,
	.swnode = &spt_i2c_node,
पूर्ण;

अटल स्थिर काष्ठा property_entry uart_properties[] = अणु
	PROPERTY_ENTRY_U32("reg-io-width", 4),
	PROPERTY_ENTRY_U32("reg-shift", 2),
	PROPERTY_ENTRY_BOOL("snps,uart-16550-compatible"),
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा software_node uart_node = अणु
	.properties = uart_properties,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_lpss_platक्रमm_info spt_uart_info = अणु
	.clk_rate = 120000000,
	.clk_con_id = "baudclk",
	.swnode = &uart_node,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_lpss_platक्रमm_info bxt_info = अणु
	.clk_rate = 100000000,
पूर्ण;

अटल स्थिर काष्ठा property_entry bxt_i2c_properties[] = अणु
	PROPERTY_ENTRY_U32("i2c-sda-hold-time-ns", 42),
	PROPERTY_ENTRY_U32("i2c-sda-falling-time-ns", 171),
	PROPERTY_ENTRY_U32("i2c-scl-falling-time-ns", 208),
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा software_node bxt_i2c_node = अणु
	.properties = bxt_i2c_properties,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_lpss_platक्रमm_info bxt_i2c_info = अणु
	.clk_rate = 133000000,
	.swnode = &bxt_i2c_node,
पूर्ण;

अटल स्थिर काष्ठा property_entry apl_i2c_properties[] = अणु
	PROPERTY_ENTRY_U32("i2c-sda-hold-time-ns", 207),
	PROPERTY_ENTRY_U32("i2c-sda-falling-time-ns", 171),
	PROPERTY_ENTRY_U32("i2c-scl-falling-time-ns", 208),
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा software_node apl_i2c_node = अणु
	.properties = apl_i2c_properties,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_lpss_platक्रमm_info apl_i2c_info = अणु
	.clk_rate = 133000000,
	.swnode = &apl_i2c_node,
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id पूर्णांकel_lpss_acpi_ids[] = अणु
	/* SPT */
	अणु "INT3440", (kernel_uदीर्घ_t)&spt_info पूर्ण,
	अणु "INT3441", (kernel_uदीर्घ_t)&spt_info पूर्ण,
	अणु "INT3442", (kernel_uदीर्घ_t)&spt_i2c_info पूर्ण,
	अणु "INT3443", (kernel_uदीर्घ_t)&spt_i2c_info पूर्ण,
	अणु "INT3444", (kernel_uदीर्घ_t)&spt_i2c_info पूर्ण,
	अणु "INT3445", (kernel_uदीर्घ_t)&spt_i2c_info पूर्ण,
	अणु "INT3446", (kernel_uदीर्घ_t)&spt_i2c_info पूर्ण,
	अणु "INT3447", (kernel_uदीर्घ_t)&spt_i2c_info पूर्ण,
	अणु "INT3448", (kernel_uदीर्घ_t)&spt_uart_info पूर्ण,
	अणु "INT3449", (kernel_uदीर्घ_t)&spt_uart_info पूर्ण,
	अणु "INT344A", (kernel_uदीर्घ_t)&spt_uart_info पूर्ण,
	/* BXT */
	अणु "80860AAC", (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु "80860ABC", (kernel_uदीर्घ_t)&bxt_info पूर्ण,
	अणु "80860AC2", (kernel_uदीर्घ_t)&bxt_info पूर्ण,
	/* APL */
	अणु "80865AAC", (kernel_uदीर्घ_t)&apl_i2c_info पूर्ण,
	अणु "80865ABC", (kernel_uदीर्घ_t)&bxt_info पूर्ण,
	अणु "80865AC2", (kernel_uदीर्घ_t)&bxt_info पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, पूर्णांकel_lpss_acpi_ids);

अटल पूर्णांक पूर्णांकel_lpss_acpi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा पूर्णांकel_lpss_platक्रमm_info *info;
	स्थिर काष्ठा acpi_device_id *id;

	id = acpi_match_device(पूर्णांकel_lpss_acpi_ids, &pdev->dev);
	अगर (!id)
		वापस -ENODEV;

	info = devm_kmemdup(&pdev->dev, (व्योम *)id->driver_data, माप(*info),
			    GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	info->irq = platक्रमm_get_irq(pdev, 0);

	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	वापस पूर्णांकel_lpss_probe(&pdev->dev, info);
पूर्ण

अटल पूर्णांक पूर्णांकel_lpss_acpi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांकel_lpss_हटाओ(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल INTEL_LPSS_PM_OPS(पूर्णांकel_lpss_acpi_pm_ops);

अटल काष्ठा platक्रमm_driver पूर्णांकel_lpss_acpi_driver = अणु
	.probe = पूर्णांकel_lpss_acpi_probe,
	.हटाओ = पूर्णांकel_lpss_acpi_हटाओ,
	.driver = अणु
		.name = "intel-lpss",
		.acpi_match_table = पूर्णांकel_lpss_acpi_ids,
		.pm = &पूर्णांकel_lpss_acpi_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(पूर्णांकel_lpss_acpi_driver);

MODULE_AUTHOR("Andy Shevchenko <andriy.shevchenko@linux.intel.com>");
MODULE_AUTHOR("Mika Westerberg <mika.westerberg@linux.intel.com>");
MODULE_DESCRIPTION("Intel LPSS ACPI driver");
MODULE_LICENSE("GPL v2");
