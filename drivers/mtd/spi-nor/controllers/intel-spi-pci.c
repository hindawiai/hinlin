<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel PCH/PCU SPI flash PCI driver.
 *
 * Copyright (C) 2016, Intel Corporation
 * Author: Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश "intel-spi.h"

#घोषणा BCR		0xdc
#घोषणा BCR_WPD		BIT(0)

अटल स्थिर काष्ठा पूर्णांकel_spi_boardinfo bxt_info = अणु
	.type = INTEL_SPI_BXT,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_spi_boardinfo cnl_info = अणु
	.type = INTEL_SPI_CNL,
पूर्ण;

अटल पूर्णांक पूर्णांकel_spi_pci_probe(काष्ठा pci_dev *pdev,
			       स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा पूर्णांकel_spi_boardinfo *info;
	काष्ठा पूर्णांकel_spi *ispi;
	u32 bcr;
	पूर्णांक ret;

	ret = pcim_enable_device(pdev);
	अगर (ret)
		वापस ret;

	info = devm_kmemdup(&pdev->dev, (व्योम *)id->driver_data, माप(*info),
			    GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	/* Try to make the chip पढ़ो/ग_लिखो */
	pci_पढ़ो_config_dword(pdev, BCR, &bcr);
	अगर (!(bcr & BCR_WPD)) अणु
		bcr |= BCR_WPD;
		pci_ग_लिखो_config_dword(pdev, BCR, bcr);
		pci_पढ़ो_config_dword(pdev, BCR, &bcr);
	पूर्ण
	info->ग_लिखोable = !!(bcr & BCR_WPD);

	ispi = पूर्णांकel_spi_probe(&pdev->dev, &pdev->resource[0], info);
	अगर (IS_ERR(ispi))
		वापस PTR_ERR(ispi);

	pci_set_drvdata(pdev, ispi);
	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_spi_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	पूर्णांकel_spi_हटाओ(pci_get_drvdata(pdev));
पूर्ण

अटल स्थिर काष्ठा pci_device_id पूर्णांकel_spi_pci_ids[] = अणु
	अणु PCI_VDEVICE(INTEL, 0x02a4), (अचिन्हित दीर्घ)&bxt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x06a4), (अचिन्हित दीर्घ)&bxt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x18e0), (अचिन्हित दीर्घ)&bxt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x19e0), (अचिन्हित दीर्घ)&bxt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x1bca), (अचिन्हित दीर्घ)&bxt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x34a4), (अचिन्हित दीर्घ)&bxt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x43a4), (अचिन्हित दीर्घ)&cnl_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4b24), (अचिन्हित दीर्घ)&bxt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x4da4), (अचिन्हित दीर्घ)&bxt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x51a4), (अचिन्हित दीर्घ)&cnl_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0x7aa4), (अचिन्हित दीर्घ)&cnl_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa0a4), (अचिन्हित दीर्घ)&bxt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa1a4), (अचिन्हित दीर्घ)&bxt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa224), (अचिन्हित दीर्घ)&bxt_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa324), (अचिन्हित दीर्घ)&cnl_info पूर्ण,
	अणु PCI_VDEVICE(INTEL, 0xa3a4), (अचिन्हित दीर्घ)&bxt_info पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, पूर्णांकel_spi_pci_ids);

अटल काष्ठा pci_driver पूर्णांकel_spi_pci_driver = अणु
	.name = "intel-spi",
	.id_table = पूर्णांकel_spi_pci_ids,
	.probe = पूर्णांकel_spi_pci_probe,
	.हटाओ = पूर्णांकel_spi_pci_हटाओ,
पूर्ण;

module_pci_driver(पूर्णांकel_spi_pci_driver);

MODULE_DESCRIPTION("Intel PCH/PCU SPI flash PCI driver");
MODULE_AUTHOR("Mika Westerberg <mika.westerberg@linux.intel.com>");
MODULE_LICENSE("GPL v2");
