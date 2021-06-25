<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * amd5536udc_pci.c -- AMD 5536 UDC high/full speed USB device controller
 *
 * Copyright (C) 2005-2007 AMD (https://www.amd.com)
 * Author: Thomas Dahlmann
 */

/*
 * The AMD5536 UDC is part of the x86 southbridge AMD Geode CS5536.
 * It is a USB Highspeed DMA capable USB device controller. Beside ep0 it
 * provides 4 IN and 4 OUT endpoपूर्णांकs (bulk or पूर्णांकerrupt type).
 *
 * Make sure that UDC is asचिन्हित to port 4 by BIOS settings (port can also
 * be used as host port) and UOC bits PAD_EN and APU are set (should be करोne
 * by BIOS init).
 *
 * UDC DMA requires 32-bit aligned buffers so DMA with gadget ether करोes not
 * work without updating NET_IP_ALIGN. Or PIO mode (module param "use_dma=0")
 * can be used with gadget ether.
 *
 * This file करोes pci device registration, and the core driver implementation
 * is करोne in amd5536udc.c
 *
 * The driver is split so as to use the core UDC driver which is based on
 * Synopsys device controller IP (dअगरferent than HS OTG IP) in UDCs
 * पूर्णांकegrated to SoC platक्रमms.
 *
 */

/* Driver strings */
#घोषणा UDC_MOD_DESCRIPTION		"AMD 5536 UDC - USB Device Controller"

/* प्रणाली */
#समावेश <linux/device.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/pci.h>

/* udc specअगरic */
#समावेश "amd5536udc.h"

/* poपूर्णांकer to device object */
अटल काष्ठा udc *udc;

/* description */
अटल स्थिर अक्षर name[] = "amd5536udc-pci";

/* Reset all pci context */
अटल व्योम udc_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा udc		*dev;

	dev = pci_get_drvdata(pdev);

	usb_del_gadget_udc(&udc->gadget);
	/* gadget driver must not be रेजिस्टरed */
	अगर (WARN_ON(dev->driver))
		वापस;

	/* dma pool cleanup */
	मुक्त_dma_pools(dev);

	/* reset controller */
	ग_लिखोl(AMD_BIT(UDC_DEVCFG_SOFTRESET), &dev->regs->cfg);
	मुक्त_irq(pdev->irq, dev);
	iounmap(dev->virt_addr);
	release_mem_region(pci_resource_start(pdev, 0),
			   pci_resource_len(pdev, 0));
	pci_disable_device(pdev);

	udc_हटाओ(dev);
पूर्ण

/* Called by pci bus driver to init pci context */
अटल पूर्णांक udc_pci_probe(
	काष्ठा pci_dev *pdev,
	स्थिर काष्ठा pci_device_id *id
)
अणु
	काष्ठा udc		*dev;
	अचिन्हित दीर्घ		resource;
	अचिन्हित दीर्घ		len;
	पूर्णांक			retval = 0;

	/* one udc only */
	अगर (udc) अणु
		dev_dbg(&pdev->dev, "already probed\n");
		वापस -EBUSY;
	पूर्ण

	/* init */
	dev = kzalloc(माप(काष्ठा udc), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	/* pci setup */
	अगर (pci_enable_device(pdev) < 0) अणु
		retval = -ENODEV;
		जाओ err_pcidev;
	पूर्ण

	/* PCI resource allocation */
	resource = pci_resource_start(pdev, 0);
	len = pci_resource_len(pdev, 0);

	अगर (!request_mem_region(resource, len, name)) अणु
		dev_dbg(&pdev->dev, "pci device used already\n");
		retval = -EBUSY;
		जाओ err_memreg;
	पूर्ण

	dev->virt_addr = ioremap(resource, len);
	अगर (!dev->virt_addr) अणु
		dev_dbg(&pdev->dev, "start address cannot be mapped\n");
		retval = -EFAULT;
		जाओ err_ioremap;
	पूर्ण

	अगर (!pdev->irq) अणु
		dev_err(&pdev->dev, "irq not set\n");
		retval = -ENODEV;
		जाओ err_irq;
	पूर्ण

	spin_lock_init(&dev->lock);
	/* udc csr रेजिस्टरs base */
	dev->csr = dev->virt_addr + UDC_CSR_ADDR;
	/* dev रेजिस्टरs base */
	dev->regs = dev->virt_addr + UDC_DEVCFG_ADDR;
	/* ep रेजिस्टरs base */
	dev->ep_regs = dev->virt_addr + UDC_EPREGS_ADDR;
	/* fअगरo's base */
	dev->rxfअगरo = (u32 __iomem *)(dev->virt_addr + UDC_RXFIFO_ADDR);
	dev->txfअगरo = (u32 __iomem *)(dev->virt_addr + UDC_TXFIFO_ADDR);

	अगर (request_irq(pdev->irq, udc_irq, IRQF_SHARED, name, dev) != 0) अणु
		dev_dbg(&pdev->dev, "request_irq(%d) fail\n", pdev->irq);
		retval = -EBUSY;
		जाओ err_irq;
	पूर्ण

	pci_set_drvdata(pdev, dev);

	/* chip revision क्रम Hs AMD5536 */
	dev->chiprev = pdev->revision;

	pci_set_master(pdev);
	pci_try_set_mwi(pdev);

	dev->phys_addr = resource;
	dev->irq = pdev->irq;
	dev->pdev = pdev;
	dev->dev = &pdev->dev;

	/* init dma pools */
	अगर (use_dma) अणु
		retval = init_dma_pools(dev);
		अगर (retval != 0)
			जाओ err_dma;
	पूर्ण

	/* general probing */
	अगर (udc_probe(dev)) अणु
		retval = -ENODEV;
		जाओ err_probe;
	पूर्ण
	वापस 0;

err_probe:
	अगर (use_dma)
		मुक्त_dma_pools(dev);
err_dma:
	मुक्त_irq(pdev->irq, dev);
err_irq:
	iounmap(dev->virt_addr);
err_ioremap:
	release_mem_region(resource, len);
err_memreg:
	pci_disable_device(pdev);
err_pcidev:
	kमुक्त(dev);
	वापस retval;
पूर्ण

/* PCI device parameters */
अटल स्थिर काष्ठा pci_device_id pci_id[] = अणु
	अणु
		PCI_DEVICE(PCI_VENDOR_ID_AMD, 0x2096),
		.class =	PCI_CLASS_SERIAL_USB_DEVICE,
		.class_mask =	0xffffffff,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, pci_id);

/* PCI functions */
अटल काष्ठा pci_driver udc_pci_driver = अणु
	.name =		name,
	.id_table =	pci_id,
	.probe =	udc_pci_probe,
	.हटाओ =	udc_pci_हटाओ,
पूर्ण;
module_pci_driver(udc_pci_driver);

MODULE_DESCRIPTION(UDC_MOD_DESCRIPTION);
MODULE_AUTHOR("Thomas Dahlmann");
MODULE_LICENSE("GPL");
