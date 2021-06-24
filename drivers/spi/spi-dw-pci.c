<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PCI पूर्णांकerface driver क्रम DW SPI Core
 *
 * Copyright (c) 2009, 2014 Intel Corporation.
 */

#समावेश <linux/pci.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/module.h>

#समावेश "spi-dw.h"

#घोषणा DRIVER_NAME "dw_spi_pci"

/* HW info क्रम MRST Clk Control Unit, 32b reg per controller */
#घोषणा MRST_SPI_CLK_BASE	100000000	/* 100m */
#घोषणा MRST_CLK_SPI_REG	0xff11d86c
#घोषणा CLK_SPI_BDIV_OFFSET	0
#घोषणा CLK_SPI_BDIV_MASK	0x00000007
#घोषणा CLK_SPI_CDIV_OFFSET	9
#घोषणा CLK_SPI_CDIV_MASK	0x00000e00
#घोषणा CLK_SPI_DISABLE_OFFSET	8

काष्ठा spi_pci_desc अणु
	पूर्णांक	(*setup)(काष्ठा dw_spi *);
	u16	num_cs;
	u16	bus_num;
	u32	max_freq;
पूर्ण;

अटल पूर्णांक spi_mid_init(काष्ठा dw_spi *dws)
अणु
	व्योम __iomem *clk_reg;
	u32 clk_cभाग;

	clk_reg = ioremap(MRST_CLK_SPI_REG, 16);
	अगर (!clk_reg)
		वापस -ENOMEM;

	/* Get SPI controller operating freq info */
	clk_cभाग = पढ़ोl(clk_reg + dws->bus_num * माप(u32));
	clk_cभाग &= CLK_SPI_CDIV_MASK;
	clk_cभाग >>= CLK_SPI_CDIV_OFFSET;
	dws->max_freq = MRST_SPI_CLK_BASE / (clk_cभाग + 1);

	iounmap(clk_reg);

	dw_spi_dma_setup_mfld(dws);

	वापस 0;
पूर्ण

अटल पूर्णांक spi_generic_init(काष्ठा dw_spi *dws)
अणु
	dw_spi_dma_setup_generic(dws);

	वापस 0;
पूर्ण

अटल काष्ठा spi_pci_desc spi_pci_mid_desc_1 = अणु
	.setup = spi_mid_init,
	.num_cs = 5,
	.bus_num = 0,
पूर्ण;

अटल काष्ठा spi_pci_desc spi_pci_mid_desc_2 = अणु
	.setup = spi_mid_init,
	.num_cs = 2,
	.bus_num = 1,
पूर्ण;

अटल काष्ठा spi_pci_desc spi_pci_ehl_desc = अणु
	.setup = spi_generic_init,
	.num_cs = 2,
	.bus_num = -1,
	.max_freq = 100000000,
पूर्ण;

अटल पूर्णांक spi_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा dw_spi *dws;
	काष्ठा spi_pci_desc *desc = (काष्ठा spi_pci_desc *)ent->driver_data;
	पूर्णांक pci_bar = 0;
	पूर्णांक ret;

	ret = pcim_enable_device(pdev);
	अगर (ret)
		वापस ret;

	dws = devm_kzalloc(&pdev->dev, माप(*dws), GFP_KERNEL);
	अगर (!dws)
		वापस -ENOMEM;

	/* Get basic io resource and map it */
	dws->paddr = pci_resource_start(pdev, pci_bar);
	pci_set_master(pdev);

	ret = pcim_iomap_regions(pdev, 1 << pci_bar, pci_name(pdev));
	अगर (ret)
		वापस ret;

	ret = pci_alloc_irq_vectors(pdev, 1, 1, PCI_IRQ_ALL_TYPES);
	अगर (ret < 0)
		वापस ret;

	dws->regs = pcim_iomap_table(pdev)[pci_bar];
	dws->irq = pci_irq_vector(pdev, 0);

	/*
	 * Specअगरic handling क्रम platक्रमms, like dma setup,
	 * घड़ी rate, FIFO depth.
	 */
	अगर (desc) अणु
		dws->num_cs = desc->num_cs;
		dws->bus_num = desc->bus_num;
		dws->max_freq = desc->max_freq;

		अगर (desc->setup) अणु
			ret = desc->setup(dws);
			अगर (ret)
				जाओ err_मुक्त_irq_vectors;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = -ENODEV;
		जाओ err_मुक्त_irq_vectors;
	पूर्ण

	ret = dw_spi_add_host(&pdev->dev, dws);
	अगर (ret)
		जाओ err_मुक्त_irq_vectors;

	/* PCI hook and SPI hook use the same drv data */
	pci_set_drvdata(pdev, dws);

	dev_info(&pdev->dev, "found PCI SPI controller(ID: %04x:%04x)\n",
		pdev->venकरोr, pdev->device);

	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, 1000);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_put_स्वतःsuspend(&pdev->dev);
	pm_runसमय_allow(&pdev->dev);

	वापस 0;

err_मुक्त_irq_vectors:
	pci_मुक्त_irq_vectors(pdev);
	वापस ret;
पूर्ण

अटल व्योम spi_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा dw_spi *dws = pci_get_drvdata(pdev);

	pm_runसमय_क्रमbid(&pdev->dev);
	pm_runसमय_get_noresume(&pdev->dev);

	dw_spi_हटाओ_host(dws);
	pci_मुक्त_irq_vectors(pdev);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक spi_suspend(काष्ठा device *dev)
अणु
	काष्ठा dw_spi *dws = dev_get_drvdata(dev);

	वापस dw_spi_suspend_host(dws);
पूर्ण

अटल पूर्णांक spi_resume(काष्ठा device *dev)
अणु
	काष्ठा dw_spi *dws = dev_get_drvdata(dev);

	वापस dw_spi_resume_host(dws);
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(dw_spi_pm_ops, spi_suspend, spi_resume);

अटल स्थिर काष्ठा pci_device_id pci_ids[] = अणु
	/* Intel MID platक्रमm SPI controller 0 */
	/*
	 * The access to the device 8086:0801 is disabled by HW, since it's
	 * exclusively used by SCU to communicate with MSIC.
	 */
	/* Intel MID platक्रमm SPI controller 1 */
	अणु PCI_VDEVICE(INTEL, 0x0800), (kernel_uदीर्घ_t)&spi_pci_mid_desc_1पूर्ण,
	/* Intel MID platक्रमm SPI controller 2 */
	अणु PCI_VDEVICE(INTEL, 0x0812), (kernel_uदीर्घ_t)&spi_pci_mid_desc_2पूर्ण,
	/* Intel Elkhart Lake PSE SPI controllers */
	अणु PCI_VDEVICE(INTEL, 0x4b84), (kernel_uदीर्घ_t)&spi_pci_ehl_descपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4b85), (kernel_uदीर्घ_t)&spi_pci_ehl_descपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4b86), (kernel_uदीर्घ_t)&spi_pci_ehl_descपूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4b87), (kernel_uदीर्घ_t)&spi_pci_ehl_descपूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, pci_ids);

अटल काष्ठा pci_driver dw_spi_driver = अणु
	.name =		DRIVER_NAME,
	.id_table =	pci_ids,
	.probe =	spi_pci_probe,
	.हटाओ =	spi_pci_हटाओ,
	.driver         = अणु
		.pm     = &dw_spi_pm_ops,
	पूर्ण,
पूर्ण;

module_pci_driver(dw_spi_driver);

MODULE_AUTHOR("Feng Tang <feng.tang@intel.com>");
MODULE_DESCRIPTION("PCI interface driver for DW SPI Core");
MODULE_LICENSE("GPL v2");
