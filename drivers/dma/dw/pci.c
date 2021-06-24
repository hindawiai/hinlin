<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCI driver क्रम the Synopsys DesignWare DMA Controller
 *
 * Copyright (C) 2013 Intel Corporation
 * Author: Andy Shevchenko <andriy.shevchenko@linux.पूर्णांकel.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/device.h>

#समावेश "internal.h"

अटल पूर्णांक dw_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *pid)
अणु
	स्थिर काष्ठा dw_dma_chip_pdata *drv_data = (व्योम *)pid->driver_data;
	काष्ठा dw_dma_chip_pdata *data;
	काष्ठा dw_dma_chip *chip;
	पूर्णांक ret;

	ret = pcim_enable_device(pdev);
	अगर (ret)
		वापस ret;

	ret = pcim_iomap_regions(pdev, 1 << 0, pci_name(pdev));
	अगर (ret) अणु
		dev_err(&pdev->dev, "I/O memory remapping failed\n");
		वापस ret;
	पूर्ण

	pci_set_master(pdev);
	pci_try_set_mwi(pdev);

	ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
	अगर (ret)
		वापस ret;

	ret = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32));
	अगर (ret)
		वापस ret;

	data = devm_kmemdup(&pdev->dev, drv_data, माप(*drv_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	chip = devm_kzalloc(&pdev->dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	chip->dev = &pdev->dev;
	chip->id = pdev->devfn;
	chip->regs = pcim_iomap_table(pdev)[0];
	chip->irq = pdev->irq;
	chip->pdata = data->pdata;

	data->chip = chip;

	ret = data->probe(chip);
	अगर (ret)
		वापस ret;

	dw_dma_acpi_controller_रेजिस्टर(chip->dw);

	pci_set_drvdata(pdev, data);

	वापस 0;
पूर्ण

अटल व्योम dw_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा dw_dma_chip_pdata *data = pci_get_drvdata(pdev);
	काष्ठा dw_dma_chip *chip = data->chip;
	पूर्णांक ret;

	dw_dma_acpi_controller_मुक्त(chip->dw);

	ret = data->हटाओ(chip);
	अगर (ret)
		dev_warn(&pdev->dev, "can't remove device properly: %d\n", ret);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP

अटल पूर्णांक dw_pci_suspend_late(काष्ठा device *dev)
अणु
	काष्ठा dw_dma_chip_pdata *data = dev_get_drvdata(dev);
	काष्ठा dw_dma_chip *chip = data->chip;

	वापस करो_dw_dma_disable(chip);
पूर्ण;

अटल पूर्णांक dw_pci_resume_early(काष्ठा device *dev)
अणु
	काष्ठा dw_dma_chip_pdata *data = dev_get_drvdata(dev);
	काष्ठा dw_dma_chip *chip = data->chip;

	वापस करो_dw_dma_enable(chip);
पूर्ण;

#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा dev_pm_ops dw_pci_dev_pm_ops = अणु
	SET_LATE_SYSTEM_SLEEP_PM_OPS(dw_pci_suspend_late, dw_pci_resume_early)
पूर्ण;

अटल स्थिर काष्ठा pci_device_id dw_pci_id_table[] = अणु
	/* Medfield (GPDMA) */
	अणु PCI_VDEVICE(INTEL, 0x0827), (kernel_uदीर्घ_t)&dw_dma_chip_pdata पूर्ण,

	/* BayTrail */
	अणु PCI_VDEVICE(INTEL, 0x0f06), (kernel_uदीर्घ_t)&dw_dma_chip_pdata पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x0f40), (kernel_uदीर्घ_t)&dw_dma_chip_pdata पूर्ण,

	/* Merrअगरield */
	अणु PCI_VDEVICE(INTEL, 0x11a2), (kernel_uदीर्घ_t)&idma32_chip_pdata पूर्ण,

	/* Braswell */
	अणु PCI_VDEVICE(INTEL, 0x2286), (kernel_uदीर्घ_t)&dw_dma_chip_pdata पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x22c0), (kernel_uदीर्घ_t)&dw_dma_chip_pdata पूर्ण,

	/* Elkhart Lake iDMA 32-bit (PSE DMA) */
	अणु PCI_VDEVICE(INTEL, 0x4bb4), (kernel_uदीर्घ_t)&idma32_chip_pdata पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4bb5), (kernel_uदीर्घ_t)&idma32_chip_pdata पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4bb6), (kernel_uदीर्घ_t)&idma32_chip_pdata पूर्ण,

	/* Haswell */
	अणु PCI_VDEVICE(INTEL, 0x9c60), (kernel_uदीर्घ_t)&dw_dma_chip_pdata पूर्ण,

	/* Broadwell */
	अणु PCI_VDEVICE(INTEL, 0x9ce0), (kernel_uदीर्घ_t)&dw_dma_chip_pdata पूर्ण,

	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, dw_pci_id_table);

अटल काष्ठा pci_driver dw_pci_driver = अणु
	.name		= "dw_dmac_pci",
	.id_table	= dw_pci_id_table,
	.probe		= dw_pci_probe,
	.हटाओ		= dw_pci_हटाओ,
	.driver	= अणु
		.pm	= &dw_pci_dev_pm_ops,
	पूर्ण,
पूर्ण;

module_pci_driver(dw_pci_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Synopsys DesignWare DMA Controller PCI driver");
MODULE_AUTHOR("Andy Shevchenko <andriy.shevchenko@linux.intel.com>");
