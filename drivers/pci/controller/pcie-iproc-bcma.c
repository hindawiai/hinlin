<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015 Broadcom Corporation
 * Copyright (C) 2015 Hauke Mehrtens <hauke@hauke-m.de>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/bcma/bcma.h>
#समावेश <linux/ioport.h>

#समावेश "pcie-iproc.h"


/* NS: CLASS field is R/O, and set to wrong 0x200 value */
अटल व्योम bcma_pcie2_fixup_class(काष्ठा pci_dev *dev)
अणु
	dev->class = PCI_CLASS_BRIDGE_PCI << 8;
पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_BROADCOM, 0x8011, bcma_pcie2_fixup_class);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_BROADCOM, 0x8012, bcma_pcie2_fixup_class);

अटल पूर्णांक iproc_pcie_bcma_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	काष्ठा iproc_pcie *pcie = dev->sysdata;
	काष्ठा bcma_device *bdev = container_of(pcie->dev, काष्ठा bcma_device, dev);

	वापस bcma_core_irq(bdev, 5);
पूर्ण

अटल पूर्णांक iproc_pcie_bcma_probe(काष्ठा bcma_device *bdev)
अणु
	काष्ठा device *dev = &bdev->dev;
	काष्ठा iproc_pcie *pcie;
	LIST_HEAD(resources);
	काष्ठा pci_host_bridge *bridge;
	पूर्णांक ret;

	bridge = devm_pci_alloc_host_bridge(dev, माप(*pcie));
	अगर (!bridge)
		वापस -ENOMEM;

	pcie = pci_host_bridge_priv(bridge);

	pcie->dev = dev;

	pcie->type = IPROC_PCIE_PAXB_BCMA;
	pcie->base = bdev->io_addr;
	अगर (!pcie->base) अणु
		dev_err(dev, "no controller registers\n");
		वापस -ENOMEM;
	पूर्ण

	pcie->base_addr = bdev->addr;

	pcie->mem.start = bdev->addr_s[0];
	pcie->mem.end = bdev->addr_s[0] + SZ_128M - 1;
	pcie->mem.name = "PCIe MEM space";
	pcie->mem.flags = IORESOURCE_MEM;
	pci_add_resource(&resources, &pcie->mem);

	pcie->map_irq = iproc_pcie_bcma_map_irq;

	ret = iproc_pcie_setup(pcie, &resources);
	अगर (ret) अणु
		dev_err(dev, "PCIe controller setup failed\n");
		pci_मुक्त_resource_list(&resources);
		वापस ret;
	पूर्ण

	bcma_set_drvdata(bdev, pcie);
	वापस 0;
पूर्ण

अटल व्योम iproc_pcie_bcma_हटाओ(काष्ठा bcma_device *bdev)
अणु
	काष्ठा iproc_pcie *pcie = bcma_get_drvdata(bdev);

	iproc_pcie_हटाओ(pcie);
पूर्ण

अटल स्थिर काष्ठा bcma_device_id iproc_pcie_bcma_table[] = अणु
	BCMA_CORE(BCMA_MANUF_BCM, BCMA_CORE_NS_PCIEG2, BCMA_ANY_REV, BCMA_ANY_CLASS),
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(bcma, iproc_pcie_bcma_table);

अटल काष्ठा bcma_driver iproc_pcie_bcma_driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= iproc_pcie_bcma_table,
	.probe		= iproc_pcie_bcma_probe,
	.हटाओ		= iproc_pcie_bcma_हटाओ,
पूर्ण;
module_bcma_driver(iproc_pcie_bcma_driver);

MODULE_AUTHOR("Hauke Mehrtens");
MODULE_DESCRIPTION("Broadcom iProc PCIe BCMA driver");
MODULE_LICENSE("GPL v2");
