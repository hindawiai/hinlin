<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel LPSS PCI support.
 *
 * Copyright (C) 2015, Intel Corporation
 *
 * Authors: Andy Shevchenko <andriy.shevchenko@linux.पूर्णांकel.com>
 *          Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/property.h>

#समावेश "intel-lpss.h"

अटल पूर्णांक पूर्णांकel_lpss_pci_probe(काष्ठा pci_dev *pdev,
				स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा पूर्णांकel_lpss_platक्रमm_info *info;
	पूर्णांक ret;

	ret = pcim_enable_device(pdev);
	अगर (ret)
		वापस ret;

	info = devm_kmemdup(&pdev->dev, (व्योम *)id->driver_data, माप(*info),
			    GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->mem = &pdev->resource[0];
	info->irq = pdev->irq;

	pdev->d3cold_delay = 0;

	/* Probably it is enough to set this क्रम iDMA capable devices only */
	pci_set_master(pdev);
	pci_try_set_mwi(pdev);

	ret = पूर्णांकel_lpss_probe(&pdev->dev, info);
	अगर (ret)
		वापस ret;

	pm_runसमय_put(&pdev->dev);
	pm_runसमय_allow(&pdev->dev);

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_lpss_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	pm_runसमय_क्रमbid(&pdev->dev);
	pm_runसमय_get_sync(&pdev->dev);

	पूर्णांकel_lpss_हटाओ(&pdev->dev);
पूर्ण

अटल INTEL_LPSS_PM_OPS(पूर्णांकel_lpss_pci_pm_ops);

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

अटल स्थिर काष्ठा पूर्णांकel_lpss_platक्रमm_info bxt_uart_info = अणु
	.clk_rate = 100000000,
	.clk_con_id = "baudclk",
	.swnode = &uart_node,
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

अटल स्थिर काष्ठा property_entry glk_i2c_properties[] = अणु
	PROPERTY_ENTRY_U32("i2c-sda-hold-time-ns", 313),
	PROPERTY_ENTRY_U32("i2c-sda-falling-time-ns", 171),
	PROPERTY_ENTRY_U32("i2c-scl-falling-time-ns", 290),
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा software_node glk_i2c_node = अणु
	.properties = glk_i2c_properties,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_lpss_platक्रमm_info glk_i2c_info = अणु
	.clk_rate = 133000000,
	.swnode = &glk_i2c_node,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_lpss_platक्रमm_info cnl_i2c_info = अणु
	.clk_rate = 216000000,
	.swnode = &spt_i2c_node,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_lpss_platक्रमm_info ehl_i2c_info = अणु
	.clk_rate = 100000000,
	.swnode = &bxt_i2c_node,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id पूर्णांकel_lpss_pci_ids[] = अणु
	/* CML-LP */
	अणु PCI_VDEVICE(INTEL, 0x02a8), (kernel_uदीर्घ_t)&spt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x02a9), (kernel_uदीर्घ_t)&spt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x02aa), (kernel_uदीर्घ_t)&spt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x02ab), (kernel_uदीर्घ_t)&spt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x02c5), (kernel_uदीर्घ_t)&cnl_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x02c6), (kernel_uदीर्घ_t)&cnl_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x02c7), (kernel_uदीर्घ_t)&spt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x02e8), (kernel_uदीर्घ_t)&cnl_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x02e9), (kernel_uदीर्घ_t)&cnl_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x02ea), (kernel_uदीर्घ_t)&cnl_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x02eb), (kernel_uदीर्घ_t)&cnl_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x02fb), (kernel_uदीर्घ_t)&spt_info पूर्ण,
	/* CML-H */
	अणु PCI_VDEVICE(INTEL, 0x06a8), (kernel_uदीर्घ_t)&spt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x06a9), (kernel_uदीर्घ_t)&spt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x06aa), (kernel_uदीर्घ_t)&spt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x06ab), (kernel_uदीर्घ_t)&spt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x06c7), (kernel_uदीर्घ_t)&spt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x06e8), (kernel_uदीर्घ_t)&cnl_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x06e9), (kernel_uदीर्घ_t)&cnl_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x06ea), (kernel_uदीर्घ_t)&cnl_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x06eb), (kernel_uदीर्घ_t)&cnl_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x06fb), (kernel_uदीर्घ_t)&spt_info पूर्ण,
	/* BXT A-Step */
	अणु PCI_VDEVICE(INTEL, 0x0aac), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x0aae), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x0ab0), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x0ab2), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x0ab4), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x0ab6), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x0ab8), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x0aba), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x0abc), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x0abe), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x0ac0), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x0ac2), (kernel_uदीर्घ_t)&bxt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x0ac4), (kernel_uदीर्घ_t)&bxt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x0ac6), (kernel_uदीर्घ_t)&bxt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x0aee), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	/* BXT B-Step */
	अणु PCI_VDEVICE(INTEL, 0x1aac), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1aae), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1ab0), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1ab2), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1ab4), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1ab6), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1ab8), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1aba), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1abc), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1abe), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1ac0), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1ac2), (kernel_uदीर्घ_t)&bxt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1ac4), (kernel_uदीर्घ_t)&bxt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1ac6), (kernel_uदीर्घ_t)&bxt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1aee), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	/* EBG */
	अणु PCI_VDEVICE(INTEL, 0x1bad), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1bae), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	/* GLK */
	अणु PCI_VDEVICE(INTEL, 0x31ac), (kernel_uदीर्घ_t)&glk_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x31ae), (kernel_uदीर्घ_t)&glk_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x31b0), (kernel_uदीर्घ_t)&glk_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x31b2), (kernel_uदीर्घ_t)&glk_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x31b4), (kernel_uदीर्घ_t)&glk_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x31b6), (kernel_uदीर्घ_t)&glk_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x31b8), (kernel_uदीर्घ_t)&glk_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x31ba), (kernel_uदीर्घ_t)&glk_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x31bc), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x31be), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x31c0), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x31c2), (kernel_uदीर्घ_t)&bxt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x31c4), (kernel_uदीर्घ_t)&bxt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x31c6), (kernel_uदीर्घ_t)&bxt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x31ee), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	/* ICL-LP */
	अणु PCI_VDEVICE(INTEL, 0x34a8), (kernel_uदीर्घ_t)&spt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x34a9), (kernel_uदीर्घ_t)&spt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x34aa), (kernel_uदीर्घ_t)&spt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x34ab), (kernel_uदीर्घ_t)&spt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x34c5), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x34c6), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x34c7), (kernel_uदीर्घ_t)&spt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x34e8), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x34e9), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x34ea), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x34eb), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x34fb), (kernel_uदीर्घ_t)&spt_info पूर्ण,
	/* TGL-H */
	अणु PCI_VDEVICE(INTEL, 0x43a7), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x43a8), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x43a9), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x43aa), (kernel_uदीर्घ_t)&bxt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x43ab), (kernel_uदीर्घ_t)&bxt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x43ad), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x43ae), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x43d8), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x43da), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x43e8), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x43e9), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x43ea), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x43eb), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x43fb), (kernel_uदीर्घ_t)&bxt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x43fd), (kernel_uदीर्घ_t)&bxt_info पूर्ण,
	/* EHL */
	अणु PCI_VDEVICE(INTEL, 0x4b28), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4b29), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4b2a), (kernel_uदीर्घ_t)&bxt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4b2b), (kernel_uदीर्घ_t)&bxt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4b37), (kernel_uदीर्घ_t)&bxt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4b44), (kernel_uदीर्घ_t)&ehl_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4b45), (kernel_uदीर्घ_t)&ehl_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4b4b), (kernel_uदीर्घ_t)&ehl_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4b4c), (kernel_uदीर्घ_t)&ehl_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4b4d), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4b78), (kernel_uदीर्घ_t)&ehl_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4b79), (kernel_uदीर्घ_t)&ehl_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4b7a), (kernel_uदीर्घ_t)&ehl_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4b7b), (kernel_uदीर्घ_t)&ehl_i2c_info पूर्ण,
	/* JSL */
	अणु PCI_VDEVICE(INTEL, 0x4da8), (kernel_uदीर्घ_t)&spt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4da9), (kernel_uदीर्घ_t)&spt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4daa), (kernel_uदीर्घ_t)&spt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4dab), (kernel_uदीर्घ_t)&spt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4dc5), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4dc6), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4dc7), (kernel_uदीर्घ_t)&spt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4de8), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4de9), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4dea), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4deb), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4dfb), (kernel_uदीर्घ_t)&spt_info पूर्ण,
	/* ADL-P */
	अणु PCI_VDEVICE(INTEL, 0x51a8), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x51a9), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x51aa), (kernel_uदीर्घ_t)&bxt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x51ab), (kernel_uदीर्घ_t)&bxt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x51c5), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x51c6), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x51c7), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x51e8), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x51e9), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x51ea), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x51eb), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x51fb), (kernel_uदीर्घ_t)&bxt_info पूर्ण,
	/* APL */
	अणु PCI_VDEVICE(INTEL, 0x5aac), (kernel_uदीर्घ_t)&apl_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x5aae), (kernel_uदीर्घ_t)&apl_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x5ab0), (kernel_uदीर्घ_t)&apl_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x5ab2), (kernel_uदीर्घ_t)&apl_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x5ab4), (kernel_uदीर्घ_t)&apl_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x5ab6), (kernel_uदीर्घ_t)&apl_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x5ab8), (kernel_uदीर्घ_t)&apl_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x5aba), (kernel_uदीर्घ_t)&apl_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x5abc), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x5abe), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x5ac0), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x5ac2), (kernel_uदीर्घ_t)&bxt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x5ac4), (kernel_uदीर्घ_t)&bxt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x5ac6), (kernel_uदीर्घ_t)&bxt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x5aee), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	/* ADL-S */
	अणु PCI_VDEVICE(INTEL, 0x7aa8), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x7aa9), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x7aaa), (kernel_uदीर्घ_t)&bxt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x7aab), (kernel_uदीर्घ_t)&bxt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x7acc), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x7acd), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x7ace), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x7acf), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x7adc), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x7af9), (kernel_uदीर्घ_t)&bxt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x7afb), (kernel_uदीर्घ_t)&bxt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x7afc), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x7afd), (kernel_uदीर्घ_t)&bxt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x7afe), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	/* LKF */
	अणु PCI_VDEVICE(INTEL, 0x98a8), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x98a9), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x98c7), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	/* SPT-LP */
	अणु PCI_VDEVICE(INTEL, 0x9d27), (kernel_uदीर्घ_t)&spt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9d28), (kernel_uदीर्घ_t)&spt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9d29), (kernel_uदीर्घ_t)&spt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9d2a), (kernel_uदीर्घ_t)&spt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9d60), (kernel_uदीर्घ_t)&spt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9d61), (kernel_uदीर्घ_t)&spt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9d62), (kernel_uदीर्घ_t)&spt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9d63), (kernel_uदीर्घ_t)&spt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9d64), (kernel_uदीर्घ_t)&spt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9d65), (kernel_uदीर्घ_t)&spt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9d66), (kernel_uदीर्घ_t)&spt_uart_info पूर्ण,
	/* CNL-LP */
	अणु PCI_VDEVICE(INTEL, 0x9da8), (kernel_uदीर्घ_t)&spt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9da9), (kernel_uदीर्घ_t)&spt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9daa), (kernel_uदीर्घ_t)&spt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9dab), (kernel_uदीर्घ_t)&spt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9dc5), (kernel_uदीर्घ_t)&cnl_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9dc6), (kernel_uदीर्घ_t)&cnl_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9dc7), (kernel_uदीर्घ_t)&spt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9de8), (kernel_uदीर्घ_t)&cnl_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9de9), (kernel_uदीर्घ_t)&cnl_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9dea), (kernel_uदीर्घ_t)&cnl_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9deb), (kernel_uदीर्घ_t)&cnl_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x9dfb), (kernel_uदीर्घ_t)&spt_info पूर्ण,
	/* TGL-LP */
	अणु PCI_VDEVICE(INTEL, 0xa0a8), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa0a9), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa0aa), (kernel_uदीर्घ_t)&spt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa0ab), (kernel_uदीर्घ_t)&spt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa0c5), (kernel_uदीर्घ_t)&spt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa0c6), (kernel_uदीर्घ_t)&spt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa0c7), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa0d8), (kernel_uदीर्घ_t)&spt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa0d9), (kernel_uदीर्घ_t)&spt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa0da), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa0db), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa0dc), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa0dd), (kernel_uदीर्घ_t)&bxt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa0de), (kernel_uदीर्घ_t)&spt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa0df), (kernel_uदीर्घ_t)&spt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa0e8), (kernel_uदीर्घ_t)&spt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa0e9), (kernel_uदीर्घ_t)&spt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa0ea), (kernel_uदीर्घ_t)&spt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa0eb), (kernel_uदीर्घ_t)&spt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa0fb), (kernel_uदीर्घ_t)&spt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa0fd), (kernel_uदीर्घ_t)&spt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa0fe), (kernel_uदीर्घ_t)&spt_info पूर्ण,
	/* SPT-H */
	अणु PCI_VDEVICE(INTEL, 0xa127), (kernel_uदीर्घ_t)&spt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa128), (kernel_uदीर्घ_t)&spt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa129), (kernel_uदीर्घ_t)&spt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa12a), (kernel_uदीर्घ_t)&spt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa160), (kernel_uदीर्घ_t)&spt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa161), (kernel_uदीर्घ_t)&spt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa162), (kernel_uदीर्घ_t)&spt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa166), (kernel_uदीर्घ_t)&spt_uart_info पूर्ण,
	/* KBL-H */
	अणु PCI_VDEVICE(INTEL, 0xa2a7), (kernel_uदीर्घ_t)&spt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa2a8), (kernel_uदीर्घ_t)&spt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa2a9), (kernel_uदीर्घ_t)&spt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa2aa), (kernel_uदीर्घ_t)&spt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa2e0), (kernel_uदीर्घ_t)&spt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa2e1), (kernel_uदीर्घ_t)&spt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa2e2), (kernel_uदीर्घ_t)&spt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa2e3), (kernel_uदीर्घ_t)&spt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa2e6), (kernel_uदीर्घ_t)&spt_uart_info पूर्ण,
	/* CNL-H */
	अणु PCI_VDEVICE(INTEL, 0xa328), (kernel_uदीर्घ_t)&spt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa329), (kernel_uदीर्घ_t)&spt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa32a), (kernel_uदीर्घ_t)&spt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa32b), (kernel_uदीर्घ_t)&spt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa347), (kernel_uदीर्घ_t)&spt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa368), (kernel_uदीर्घ_t)&cnl_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa369), (kernel_uदीर्घ_t)&cnl_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa36a), (kernel_uदीर्घ_t)&cnl_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa36b), (kernel_uदीर्घ_t)&cnl_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa37b), (kernel_uदीर्घ_t)&spt_info पूर्ण,
	/* CML-V */
	अणु PCI_VDEVICE(INTEL, 0xa3a7), (kernel_uदीर्घ_t)&spt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa3a8), (kernel_uदीर्घ_t)&spt_uart_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa3a9), (kernel_uदीर्घ_t)&spt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa3aa), (kernel_uदीर्घ_t)&spt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa3e0), (kernel_uदीर्घ_t)&spt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa3e1), (kernel_uदीर्घ_t)&spt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa3e2), (kernel_uदीर्घ_t)&spt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa3e3), (kernel_uदीर्घ_t)&spt_i2c_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa3e6), (kernel_uदीर्घ_t)&spt_uart_info पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, पूर्णांकel_lpss_pci_ids);

अटल काष्ठा pci_driver पूर्णांकel_lpss_pci_driver = अणु
	.name = "intel-lpss",
	.id_table = पूर्णांकel_lpss_pci_ids,
	.probe = पूर्णांकel_lpss_pci_probe,
	.हटाओ = पूर्णांकel_lpss_pci_हटाओ,
	.driver = अणु
		.pm = &पूर्णांकel_lpss_pci_pm_ops,
	पूर्ण,
पूर्ण;

module_pci_driver(पूर्णांकel_lpss_pci_driver);

MODULE_AUTHOR("Andy Shevchenko <andriy.shevchenko@linux.intel.com>");
MODULE_AUTHOR("Mika Westerberg <mika.westerberg@linux.intel.com>");
MODULE_DESCRIPTION("Intel LPSS PCI driver");
MODULE_LICENSE("GPL v2");
