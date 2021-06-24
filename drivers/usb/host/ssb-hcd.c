<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Sonics Silicon Backplane
 * Broadcom USB-core driver  (SSB bus glue)
 *
 * Copyright 2011-2012 Hauke Mehrtens <hauke@hauke-m.de>
 *
 * Based on ssb-ohci driver
 * Copyright 2007 Michael Buesch <m@bues.ch>
 *
 * Derived from the OHCI-PCI driver
 * Copyright 1999 Roman Weissgaerber
 * Copyright 2000-2002 David Brownell
 * Copyright 1999 Linus Torvalds
 * Copyright 1999 Gregory P. Smith
 *
 * Derived from the USBcore related parts of Broadcom-SB
 * Copyright 2005-2011 Broadcom Corporation
 */
#समावेश <linux/ssb/ssb.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb/ehci_pdriver.h>
#समावेश <linux/usb/ohci_pdriver.h>

MODULE_AUTHOR("Hauke Mehrtens");
MODULE_DESCRIPTION("Common USB driver for SSB Bus");
MODULE_LICENSE("GPL");

#घोषणा SSB_HCD_TMSLOW_HOSTMODE	(1 << 29)

काष्ठा ssb_hcd_device अणु
	काष्ठा platक्रमm_device *ehci_dev;
	काष्ठा platक्रमm_device *ohci_dev;

	u32 enable_flags;
पूर्ण;

अटल व्योम ssb_hcd_5354wa(काष्ठा ssb_device *dev)
अणु
#अगर_घोषित CONFIG_SSB_DRIVER_MIPS
	/* Work around क्रम 5354 failures */
	अगर (dev->id.revision == 2 && dev->bus->chip_id == 0x5354) अणु
		/* Change syn01 reg */
		ssb_ग_लिखो32(dev, 0x894, 0x00fe00fe);

		/* Change syn03 reg */
		ssb_ग_लिखो32(dev, 0x89c, ssb_पढ़ो32(dev, 0x89c) | 0x1);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम ssb_hcd_usb20wa(काष्ठा ssb_device *dev)
अणु
	अगर (dev->id.coreid == SSB_DEV_USB20_HOST) अणु
		/*
		 * USB 2.0 special considerations:
		 *
		 * In addition to the standard SSB reset sequence, the Host
		 * Control Register must be programmed to bring the USB core
		 * and various phy components out of reset.
		 */
		ssb_ग_लिखो32(dev, 0x200, 0x7ff);

		/* Change Flush control reg */
		ssb_ग_लिखो32(dev, 0x400, ssb_पढ़ो32(dev, 0x400) & ~8);
		ssb_पढ़ो32(dev, 0x400);

		/* Change Shim control reg */
		ssb_ग_लिखो32(dev, 0x304, ssb_पढ़ो32(dev, 0x304) & ~0x100);
		ssb_पढ़ो32(dev, 0x304);

		udelay(1);

		ssb_hcd_5354wa(dev);
	पूर्ण
पूर्ण

/* based on arch/mips/brcm-boards/bcm947xx/pcibios.c */
अटल u32 ssb_hcd_init_chip(काष्ठा ssb_device *dev)
अणु
	u32 flags = 0;

	अगर (dev->id.coreid == SSB_DEV_USB11_HOSTDEV)
		/* Put the device पूर्णांकo host-mode. */
		flags |= SSB_HCD_TMSLOW_HOSTMODE;

	ssb_device_enable(dev, flags);

	ssb_hcd_usb20wa(dev);

	वापस flags;
पूर्ण

अटल स्थिर काष्ठा usb_ehci_pdata ehci_pdata = अणु
पूर्ण;

अटल स्थिर काष्ठा usb_ohci_pdata ohci_pdata = अणु
पूर्ण;

अटल काष्ठा platक्रमm_device *ssb_hcd_create_pdev(काष्ठा ssb_device *dev, bool ohci, u32 addr, u32 len)
अणु
	काष्ठा platक्रमm_device *hci_dev;
	काष्ठा resource hci_res[2];
	पूर्णांक ret;

	स_रखो(hci_res, 0, माप(hci_res));

	hci_res[0].start = addr;
	hci_res[0].end = hci_res[0].start + len - 1;
	hci_res[0].flags = IORESOURCE_MEM;

	hci_res[1].start = dev->irq;
	hci_res[1].flags = IORESOURCE_IRQ;

	hci_dev = platक्रमm_device_alloc(ohci ? "ohci-platform" :
					"ehci-platform" , 0);
	अगर (!hci_dev)
		वापस ERR_PTR(-ENOMEM);

	hci_dev->dev.parent = dev->dev;
	hci_dev->dev.dma_mask = &hci_dev->dev.coherent_dma_mask;

	ret = platक्रमm_device_add_resources(hci_dev, hci_res,
					    ARRAY_SIZE(hci_res));
	अगर (ret)
		जाओ err_alloc;
	अगर (ohci)
		ret = platक्रमm_device_add_data(hci_dev, &ohci_pdata,
					       माप(ohci_pdata));
	अन्यथा
		ret = platक्रमm_device_add_data(hci_dev, &ehci_pdata,
					       माप(ehci_pdata));
	अगर (ret)
		जाओ err_alloc;
	ret = platक्रमm_device_add(hci_dev);
	अगर (ret)
		जाओ err_alloc;

	वापस hci_dev;

err_alloc:
	platक्रमm_device_put(hci_dev);
	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक ssb_hcd_probe(काष्ठा ssb_device *dev,
				   स्थिर काष्ठा ssb_device_id *id)
अणु
	पूर्णांक err, पंचांगp;
	पूर्णांक start, len;
	u16 chipid_top;
	u16 coreid = dev->id.coreid;
	काष्ठा ssb_hcd_device *usb_dev;

	/* USBcores are only connected on embedded devices. */
	chipid_top = (dev->bus->chip_id & 0xFF00);
	अगर (chipid_top != 0x4700 && chipid_top != 0x5300)
		वापस -ENODEV;

	/* TODO: Probably need checks here; is the core connected? */

	अगर (dma_set_mask_and_coherent(dev->dma_dev, DMA_BIT_MASK(32)))
		वापस -EOPNOTSUPP;

	usb_dev = devm_kzalloc(dev->dev, माप(काष्ठा ssb_hcd_device),
			       GFP_KERNEL);
	अगर (!usb_dev)
		वापस -ENOMEM;

	/* We currently always attach SSB_DEV_USB11_HOSTDEV
	 * as HOST OHCI. If we want to attach it as Client device,
	 * we must branch here and call पूर्णांकo the (yet to
	 * be written) Client mode driver. Same क्रम हटाओ(). */
	usb_dev->enable_flags = ssb_hcd_init_chip(dev);

	पंचांगp = ssb_पढ़ो32(dev, SSB_ADMATCH0);

	start = ssb_admatch_base(पंचांगp);
	len = (coreid == SSB_DEV_USB20_HOST) ? 0x800 : ssb_admatch_size(पंचांगp);
	usb_dev->ohci_dev = ssb_hcd_create_pdev(dev, true, start, len);
	अगर (IS_ERR(usb_dev->ohci_dev))
		वापस PTR_ERR(usb_dev->ohci_dev);

	अगर (coreid == SSB_DEV_USB20_HOST) अणु
		start = ssb_admatch_base(पंचांगp) + 0x800; /* ehci core offset */
		usb_dev->ehci_dev = ssb_hcd_create_pdev(dev, false, start, len);
		अगर (IS_ERR(usb_dev->ehci_dev)) अणु
			err = PTR_ERR(usb_dev->ehci_dev);
			जाओ err_unरेजिस्टर_ohci_dev;
		पूर्ण
	पूर्ण

	ssb_set_drvdata(dev, usb_dev);
	वापस 0;

err_unरेजिस्टर_ohci_dev:
	platक्रमm_device_unरेजिस्टर(usb_dev->ohci_dev);
	वापस err;
पूर्ण

अटल व्योम ssb_hcd_हटाओ(काष्ठा ssb_device *dev)
अणु
	काष्ठा ssb_hcd_device *usb_dev = ssb_get_drvdata(dev);
	काष्ठा platक्रमm_device *ohci_dev = usb_dev->ohci_dev;
	काष्ठा platक्रमm_device *ehci_dev = usb_dev->ehci_dev;

	अगर (ohci_dev)
		platक्रमm_device_unरेजिस्टर(ohci_dev);
	अगर (ehci_dev)
		platक्रमm_device_unरेजिस्टर(ehci_dev);

	ssb_device_disable(dev, 0);
पूर्ण

अटल व्योम ssb_hcd_shutकरोwn(काष्ठा ssb_device *dev)
अणु
	ssb_device_disable(dev, 0);
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक ssb_hcd_suspend(काष्ठा ssb_device *dev, pm_message_t state)
अणु
	ssb_device_disable(dev, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक ssb_hcd_resume(काष्ठा ssb_device *dev)
अणु
	काष्ठा ssb_hcd_device *usb_dev = ssb_get_drvdata(dev);

	ssb_device_enable(dev, usb_dev->enable_flags);

	वापस 0;
पूर्ण

#अन्यथा /* !CONFIG_PM */
#घोषणा ssb_hcd_suspend	शून्य
#घोषणा ssb_hcd_resume	शून्य
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा ssb_device_id ssb_hcd_table[] = अणु
	SSB_DEVICE(SSB_VENDOR_BROADCOM, SSB_DEV_USB11_HOSTDEV, SSB_ANY_REV),
	SSB_DEVICE(SSB_VENDOR_BROADCOM, SSB_DEV_USB11_HOST, SSB_ANY_REV),
	SSB_DEVICE(SSB_VENDOR_BROADCOM, SSB_DEV_USB20_HOST, SSB_ANY_REV),
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(ssb, ssb_hcd_table);

अटल काष्ठा ssb_driver ssb_hcd_driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= ssb_hcd_table,
	.probe		= ssb_hcd_probe,
	.हटाओ		= ssb_hcd_हटाओ,
	.shutकरोwn	= ssb_hcd_shutकरोwn,
	.suspend	= ssb_hcd_suspend,
	.resume		= ssb_hcd_resume,
पूर्ण;

अटल पूर्णांक __init ssb_hcd_init(व्योम)
अणु
	वापस ssb_driver_रेजिस्टर(&ssb_hcd_driver);
पूर्ण
module_init(ssb_hcd_init);

अटल व्योम __निकास ssb_hcd_निकास(व्योम)
अणु
	ssb_driver_unरेजिस्टर(&ssb_hcd_driver);
पूर्ण
module_निकास(ssb_hcd_निकास);
