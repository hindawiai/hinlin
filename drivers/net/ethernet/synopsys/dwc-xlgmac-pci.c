<शैली गुरु>
/* Synopsys DesignWare Core Enterprise Ethernet (XLGMAC) Driver
 *
 * Copyright (c) 2017 Synopsys, Inc. (www.synopsys.com)
 *
 * This program is dual-licensed; you may select either version 2 of
 * the GNU General Public License ("GPL") or BSD license ("BSD").
 *
 * This Synopsys DWC XLGMAC software driver and associated करोcumentation
 * (hereinafter the "Software") is an unsupported proprietary work of
 * Synopsys, Inc. unless otherwise expressly agreed to in writing between
 * Synopsys and you. The Software IS NOT an item of Licensed Software or a
 * Licensed Product under any End User Software License Agreement or
 * Agreement क्रम Licensed Products with Synopsys or any supplement thereto.
 * Synopsys is a रेजिस्टरed trademark of Synopsys, Inc. Other names included
 * in the SOFTWARE may be the trademarks of their respective owners.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश "dwc-xlgmac.h"
#समावेश "dwc-xlgmac-reg.h"

अटल पूर्णांक xlgmac_probe(काष्ठा pci_dev *pcidev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा device *dev = &pcidev->dev;
	काष्ठा xlgmac_resources res;
	पूर्णांक i, ret;

	ret = pcim_enable_device(pcidev);
	अगर (ret) अणु
		dev_err(dev, "ERROR: failed to enable device\n");
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < PCI_STD_NUM_BARS; i++) अणु
		अगर (pci_resource_len(pcidev, i) == 0)
			जारी;
		ret = pcim_iomap_regions(pcidev, BIT(i), XLGMAC_DRV_NAME);
		अगर (ret)
			वापस ret;
		अवरोध;
	पूर्ण

	pci_set_master(pcidev);

	स_रखो(&res, 0, माप(res));
	res.irq = pcidev->irq;
	res.addr = pcim_iomap_table(pcidev)[i];

	वापस xlgmac_drv_probe(&pcidev->dev, &res);
पूर्ण

अटल व्योम xlgmac_हटाओ(काष्ठा pci_dev *pcidev)
अणु
	xlgmac_drv_हटाओ(&pcidev->dev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id xlgmac_pci_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_SYNOPSYS, 0x7302) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, xlgmac_pci_tbl);

अटल काष्ठा pci_driver xlgmac_pci_driver = अणु
	.name		= XLGMAC_DRV_NAME,
	.id_table	= xlgmac_pci_tbl,
	.probe		= xlgmac_probe,
	.हटाओ		= xlgmac_हटाओ,
पूर्ण;

module_pci_driver(xlgmac_pci_driver);

MODULE_DESCRIPTION(XLGMAC_DRV_DESC);
MODULE_VERSION(XLGMAC_DRV_VERSION);
MODULE_AUTHOR("Jie Deng <jiedeng@synopsys.com>");
MODULE_LICENSE("Dual BSD/GPL");
