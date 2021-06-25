<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Broadcom specअगरic Advanced Microcontroller Bus
 * Broadcom USB-core driver (BCMA bus glue)
 *
 * Copyright 2011-2015 Hauke Mehrtens <hauke@hauke-m.de>
 * Copyright 2015 Felix Fietkau <nbd@खोलोwrt.org>
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
#समावेश <linux/bcma/bcma.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/usb/ehci_pdriver.h>
#समावेश <linux/usb/ohci_pdriver.h>

MODULE_AUTHOR("Hauke Mehrtens");
MODULE_DESCRIPTION("Common USB driver for BCMA Bus");
MODULE_LICENSE("GPL");

/* See BCMA_CLKCTLST_EXTRESREQ and BCMA_CLKCTLST_EXTRESST */
#घोषणा USB_BCMA_CLKCTLST_USB_CLK_REQ			0x00000100

काष्ठा bcma_hcd_device अणु
	काष्ठा bcma_device *core;
	काष्ठा platक्रमm_device *ehci_dev;
	काष्ठा platक्रमm_device *ohci_dev;
	काष्ठा gpio_desc *gpio_desc;
पूर्ण;

/* Wait क्रम biपंचांगask in a रेजिस्टर to get set or cleared.
 * समयout is in units of ten-microseconds.
 */
अटल पूर्णांक bcma_रुको_bits(काष्ठा bcma_device *dev, u16 reg, u32 biपंचांगask,
			  पूर्णांक समयout)
अणु
	पूर्णांक i;
	u32 val;

	क्रम (i = 0; i < समयout; i++) अणु
		val = bcma_पढ़ो32(dev, reg);
		अगर ((val & biपंचांगask) == biपंचांगask)
			वापस 0;
		udelay(10);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम bcma_hcd_4716wa(काष्ठा bcma_device *dev)
अणु
#अगर_घोषित CONFIG_BCMA_DRIVER_MIPS
	/* Work around क्रम 4716 failures. */
	अगर (dev->bus->chipinfo.id == 0x4716) अणु
		u32 पंचांगp;

		पंचांगp = bcma_cpu_घड़ी(&dev->bus->drv_mips);
		अगर (पंचांगp >= 480000000)
			पंचांगp = 0x1846b; /* set CDR to 0x11(fast) */
		अन्यथा अगर (पंचांगp == 453000000)
			पंचांगp = 0x1046b; /* set CDR to 0x10(slow) */
		अन्यथा
			पंचांगp = 0;

		/* Change Shim mdio control reg to fix host not acking at
		 * high frequencies
		 */
		अगर (पंचांगp) अणु
			bcma_ग_लिखो32(dev, 0x524, 0x1); /* ग_लिखो sel to enable */
			udelay(500);

			bcma_ग_लिखो32(dev, 0x524, पंचांगp);
			udelay(500);
			bcma_ग_लिखो32(dev, 0x524, 0x4ab);
			udelay(500);
			bcma_पढ़ो32(dev, 0x528);
			bcma_ग_लिखो32(dev, 0x528, 0x80000000);
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_BCMA_DRIVER_MIPS */
पूर्ण

/* based on arch/mips/brcm-boards/bcm947xx/pcibios.c */
अटल व्योम bcma_hcd_init_chip_mips(काष्ठा bcma_device *dev)
अणु
	u32 पंचांगp;

	/*
	 * USB 2.0 special considerations:
	 *
	 * 1. Since the core supports both OHCI and EHCI functions, it must
	 *    only be reset once.
	 *
	 * 2. In addition to the standard SI reset sequence, the Host Control
	 *    Register must be programmed to bring the USB core and various
	 *    phy components out of reset.
	 */
	अगर (!bcma_core_is_enabled(dev)) अणु
		bcma_core_enable(dev, 0);
		mdelay(10);
		अगर (dev->id.rev >= 5) अणु
			/* Enable Misc PLL */
			पंचांगp = bcma_पढ़ो32(dev, 0x1e0);
			पंचांगp |= 0x100;
			bcma_ग_लिखो32(dev, 0x1e0, पंचांगp);
			अगर (bcma_रुको_bits(dev, 0x1e0, 1 << 24, 100))
				prपूर्णांकk(KERN_EMERG "Failed to enable misc PPL!\n");

			/* Take out of resets */
			bcma_ग_लिखो32(dev, 0x200, 0x4ff);
			udelay(25);
			bcma_ग_लिखो32(dev, 0x200, 0x6ff);
			udelay(25);

			/* Make sure digital and AFE are locked in USB PHY */
			bcma_ग_लिखो32(dev, 0x524, 0x6b);
			udelay(50);
			पंचांगp = bcma_पढ़ो32(dev, 0x524);
			udelay(50);
			bcma_ग_लिखो32(dev, 0x524, 0xab);
			udelay(50);
			पंचांगp = bcma_पढ़ो32(dev, 0x524);
			udelay(50);
			bcma_ग_लिखो32(dev, 0x524, 0x2b);
			udelay(50);
			पंचांगp = bcma_पढ़ो32(dev, 0x524);
			udelay(50);
			bcma_ग_लिखो32(dev, 0x524, 0x10ab);
			udelay(50);
			पंचांगp = bcma_पढ़ो32(dev, 0x524);

			अगर (bcma_रुको_bits(dev, 0x528, 0xc000, 10000)) अणु
				पंचांगp = bcma_पढ़ो32(dev, 0x528);
				prपूर्णांकk(KERN_EMERG
				       "USB20H mdio_rddata 0x%08x\n", पंचांगp);
			पूर्ण
			bcma_ग_लिखो32(dev, 0x528, 0x80000000);
			पंचांगp = bcma_पढ़ो32(dev, 0x314);
			udelay(265);
			bcma_ग_लिखो32(dev, 0x200, 0x7ff);
			udelay(10);

			/* Take USB and HSIC out of non-driving modes */
			bcma_ग_लिखो32(dev, 0x510, 0);
		पूर्ण अन्यथा अणु
			bcma_ग_लिखो32(dev, 0x200, 0x7ff);

			udelay(1);
		पूर्ण

		bcma_hcd_4716wa(dev);
	पूर्ण
पूर्ण

/*
 * bcma_hcd_usb20_old_arm_init - Initialize old USB 2.0 controller on ARM
 *
 * Old USB 2.0 core is identअगरied as BCMA_CORE_USB20_HOST and was पूर्णांकroduced
 * दीर्घ beक्रमe Northstar devices. It seems some cheaper chipsets like BCM53573
 * still use it.
 * Initialization of this old core dअगरfers between MIPS and ARM.
 */
अटल पूर्णांक bcma_hcd_usb20_old_arm_init(काष्ठा bcma_hcd_device *usb_dev)
अणु
	काष्ठा bcma_device *core = usb_dev->core;
	काष्ठा device *dev = &core->dev;
	काष्ठा bcma_device *pmu_core;

	usleep_range(10000, 20000);
	अगर (core->id.rev < 5)
		वापस 0;

	pmu_core = bcma_find_core(core->bus, BCMA_CORE_PMU);
	अगर (!pmu_core) अणु
		dev_err(dev, "Could not find PMU core\n");
		वापस -ENOENT;
	पूर्ण

	/* Take USB core out of reset */
	bcma_aग_लिखो32(core, BCMA_IOCTL, BCMA_IOCTL_CLK | BCMA_IOCTL_FGC);
	usleep_range(100, 200);
	bcma_aग_लिखो32(core, BCMA_RESET_CTL, BCMA_RESET_CTL_RESET);
	usleep_range(100, 200);
	bcma_aग_लिखो32(core, BCMA_RESET_CTL, 0);
	usleep_range(100, 200);
	bcma_aग_लिखो32(core, BCMA_IOCTL, BCMA_IOCTL_CLK);
	usleep_range(100, 200);

	/* Enable Misc PLL */
	bcma_ग_लिखो32(core, BCMA_CLKCTLST, BCMA_CLKCTLST_FORCEHT |
					  BCMA_CLKCTLST_HQCLKREQ |
					  USB_BCMA_CLKCTLST_USB_CLK_REQ);
	usleep_range(100, 200);

	bcma_ग_लिखो32(core, 0x510, 0xc7f85000);
	bcma_ग_लिखो32(core, 0x510, 0xc7f85003);
	usleep_range(300, 600);

	/* Program USB PHY PLL parameters */
	bcma_ग_लिखो32(pmu_core, BCMA_CC_PMU_PLLCTL_ADDR, 0x6);
	bcma_ग_लिखो32(pmu_core, BCMA_CC_PMU_PLLCTL_DATA, 0x005360c1);
	usleep_range(100, 200);
	bcma_ग_लिखो32(pmu_core, BCMA_CC_PMU_PLLCTL_ADDR, 0x7);
	bcma_ग_लिखो32(pmu_core, BCMA_CC_PMU_PLLCTL_DATA, 0x0);
	usleep_range(100, 200);
	bcma_set32(pmu_core, BCMA_CC_PMU_CTL, BCMA_CC_PMU_CTL_PLL_UPD);
	usleep_range(100, 200);

	bcma_ग_लिखो32(core, 0x510, 0x7f8d007);
	udelay(1000);

	/* Take controller out of reset */
	bcma_ग_लिखो32(core, 0x200, 0x4ff);
	usleep_range(25, 50);
	bcma_ग_लिखो32(core, 0x200, 0x6ff);
	usleep_range(25, 50);
	bcma_ग_लिखो32(core, 0x200, 0x7ff);
	usleep_range(25, 50);

	of_platक्रमm_शेष_populate(dev->of_node, शून्य, dev);

	वापस 0;
पूर्ण

अटल व्योम bcma_hcd_usb20_ns_init_hc(काष्ठा bcma_device *dev)
अणु
	u32 val;

	/* Set packet buffer OUT threshold */
	val = bcma_पढ़ो32(dev, 0x94);
	val &= 0xffff;
	val |= 0x80 << 16;
	bcma_ग_लिखो32(dev, 0x94, val);

	/* Enable अवरोध memory transfer */
	val = bcma_पढ़ो32(dev, 0x9c);
	val |= 1;
	bcma_ग_लिखो32(dev, 0x9c, val);

	/*
	 * Broadcom initializes PHY and then रुकोs to ensure HC is पढ़ोy to be
	 * configured. In our हाल the order is reversed. We just initialized
	 * controller and we let HCD initialize PHY, so let's रुको (sleep) now.
	 */
	usleep_range(1000, 2000);
पूर्ण

/*
 * bcma_hcd_usb20_ns_init - Initialize Northstar USB 2.0 controller
 */
अटल पूर्णांक bcma_hcd_usb20_ns_init(काष्ठा bcma_hcd_device *bcma_hcd)
अणु
	काष्ठा bcma_device *core = bcma_hcd->core;
	काष्ठा bcma_chipinfo *ci = &core->bus->chipinfo;
	काष्ठा device *dev = &core->dev;

	bcma_core_enable(core, 0);

	अगर (ci->id == BCMA_CHIP_ID_BCM4707 ||
	    ci->id == BCMA_CHIP_ID_BCM53018)
		bcma_hcd_usb20_ns_init_hc(core);

	of_platक्रमm_शेष_populate(dev->of_node, शून्य, dev);

	वापस 0;
पूर्ण

अटल व्योम bcma_hci_platक्रमm_घातer_gpio(काष्ठा bcma_device *dev, bool val)
अणु
	काष्ठा bcma_hcd_device *usb_dev = bcma_get_drvdata(dev);

	अगर (IS_ERR_OR_शून्य(usb_dev->gpio_desc))
		वापस;

	gpiod_set_value(usb_dev->gpio_desc, val);
पूर्ण

अटल स्थिर काष्ठा usb_ehci_pdata ehci_pdata = अणु
पूर्ण;

अटल स्थिर काष्ठा usb_ohci_pdata ohci_pdata = अणु
पूर्ण;

अटल काष्ठा platक्रमm_device *bcma_hcd_create_pdev(काष्ठा bcma_device *dev,
						    स्थिर अक्षर *name, u32 addr,
						    स्थिर व्योम *data,
						    माप_प्रकार size)
अणु
	काष्ठा platक्रमm_device *hci_dev;
	काष्ठा resource hci_res[2];
	पूर्णांक ret;

	स_रखो(hci_res, 0, माप(hci_res));

	hci_res[0].start = addr;
	hci_res[0].end = hci_res[0].start + 0x1000 - 1;
	hci_res[0].flags = IORESOURCE_MEM;

	hci_res[1].start = dev->irq;
	hci_res[1].flags = IORESOURCE_IRQ;

	hci_dev = platक्रमm_device_alloc(name, 0);
	अगर (!hci_dev)
		वापस ERR_PTR(-ENOMEM);

	hci_dev->dev.parent = &dev->dev;
	hci_dev->dev.dma_mask = &hci_dev->dev.coherent_dma_mask;

	ret = platक्रमm_device_add_resources(hci_dev, hci_res,
					    ARRAY_SIZE(hci_res));
	अगर (ret)
		जाओ err_alloc;
	अगर (data)
		ret = platक्रमm_device_add_data(hci_dev, data, size);
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

अटल पूर्णांक bcma_hcd_usb20_init(काष्ठा bcma_hcd_device *usb_dev)
अणु
	काष्ठा bcma_device *dev = usb_dev->core;
	काष्ठा bcma_chipinfo *chipinfo = &dev->bus->chipinfo;
	u32 ohci_addr;
	पूर्णांक err;

	अगर (dma_set_mask_and_coherent(dev->dma_dev, DMA_BIT_MASK(32)))
		वापस -EOPNOTSUPP;

	bcma_hcd_init_chip_mips(dev);

	/* In AI chips EHCI is addrspace 0, OHCI is 1 */
	ohci_addr = dev->addr_s[0];
	अगर ((chipinfo->id == BCMA_CHIP_ID_BCM5357 ||
	     chipinfo->id == BCMA_CHIP_ID_BCM4749)
	    && chipinfo->rev == 0)
		ohci_addr = 0x18009000;

	usb_dev->ohci_dev = bcma_hcd_create_pdev(dev, "ohci-platform",
						 ohci_addr, &ohci_pdata,
						 माप(ohci_pdata));
	अगर (IS_ERR(usb_dev->ohci_dev))
		वापस PTR_ERR(usb_dev->ohci_dev);

	usb_dev->ehci_dev = bcma_hcd_create_pdev(dev, "ehci-platform",
						 dev->addr, &ehci_pdata,
						 माप(ehci_pdata));
	अगर (IS_ERR(usb_dev->ehci_dev)) अणु
		err = PTR_ERR(usb_dev->ehci_dev);
		जाओ err_unरेजिस्टर_ohci_dev;
	पूर्ण

	वापस 0;

err_unरेजिस्टर_ohci_dev:
	platक्रमm_device_unरेजिस्टर(usb_dev->ohci_dev);
	वापस err;
पूर्ण

अटल पूर्णांक bcma_hcd_usb30_init(काष्ठा bcma_hcd_device *bcma_hcd)
अणु
	काष्ठा bcma_device *core = bcma_hcd->core;
	काष्ठा device *dev = &core->dev;

	bcma_core_enable(core, 0);

	of_platक्रमm_शेष_populate(dev->of_node, शून्य, dev);

	वापस 0;
पूर्ण

अटल पूर्णांक bcma_hcd_probe(काष्ठा bcma_device *core)
अणु
	पूर्णांक err;
	काष्ठा bcma_hcd_device *usb_dev;

	/* TODO: Probably need checks here; is the core connected? */

	usb_dev = devm_kzalloc(&core->dev, माप(काष्ठा bcma_hcd_device),
			       GFP_KERNEL);
	अगर (!usb_dev)
		वापस -ENOMEM;
	usb_dev->core = core;

	अगर (core->dev.of_node) अणु
		usb_dev->gpio_desc = devm_gpiod_get(&core->dev, "vcc",
						    GPIOD_OUT_HIGH);
		अगर (IS_ERR(usb_dev->gpio_desc))
			वापस PTR_ERR(usb_dev->gpio_desc);
	पूर्ण

	चयन (core->id.id) अणु
	हाल BCMA_CORE_USB20_HOST:
		अगर (IS_ENABLED(CONFIG_ARM))
			err = bcma_hcd_usb20_old_arm_init(usb_dev);
		अन्यथा अगर (IS_ENABLED(CONFIG_MIPS))
			err = bcma_hcd_usb20_init(usb_dev);
		अन्यथा
			err = -ENOTSUPP;
		अवरोध;
	हाल BCMA_CORE_NS_USB20:
		err = bcma_hcd_usb20_ns_init(usb_dev);
		अवरोध;
	हाल BCMA_CORE_NS_USB30:
		err = bcma_hcd_usb30_init(usb_dev);
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण
	अगर (err)
		वापस err;

	bcma_set_drvdata(core, usb_dev);
	वापस 0;
पूर्ण

अटल व्योम bcma_hcd_हटाओ(काष्ठा bcma_device *dev)
अणु
	काष्ठा bcma_hcd_device *usb_dev = bcma_get_drvdata(dev);
	काष्ठा platक्रमm_device *ohci_dev = usb_dev->ohci_dev;
	काष्ठा platक्रमm_device *ehci_dev = usb_dev->ehci_dev;

	अगर (ohci_dev)
		platक्रमm_device_unरेजिस्टर(ohci_dev);
	अगर (ehci_dev)
		platक्रमm_device_unरेजिस्टर(ehci_dev);

	bcma_core_disable(dev, 0);
पूर्ण

अटल व्योम bcma_hcd_shutकरोwn(काष्ठा bcma_device *dev)
अणु
	bcma_hci_platक्रमm_घातer_gpio(dev, false);
	bcma_core_disable(dev, 0);
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक bcma_hcd_suspend(काष्ठा bcma_device *dev)
अणु
	bcma_hci_platक्रमm_घातer_gpio(dev, false);
	bcma_core_disable(dev, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक bcma_hcd_resume(काष्ठा bcma_device *dev)
अणु
	bcma_hci_platक्रमm_घातer_gpio(dev, true);
	bcma_core_enable(dev, 0);

	वापस 0;
पूर्ण

#अन्यथा /* !CONFIG_PM */
#घोषणा bcma_hcd_suspend	शून्य
#घोषणा bcma_hcd_resume	शून्य
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा bcma_device_id bcma_hcd_table[] = अणु
	BCMA_CORE(BCMA_MANUF_BCM, BCMA_CORE_USB20_HOST, BCMA_ANY_REV, BCMA_ANY_CLASS),
	BCMA_CORE(BCMA_MANUF_BCM, BCMA_CORE_NS_USB20, BCMA_ANY_REV, BCMA_ANY_CLASS),
	BCMA_CORE(BCMA_MANUF_BCM, BCMA_CORE_NS_USB30, BCMA_ANY_REV, BCMA_ANY_CLASS),
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(bcma, bcma_hcd_table);

अटल काष्ठा bcma_driver bcma_hcd_driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= bcma_hcd_table,
	.probe		= bcma_hcd_probe,
	.हटाओ		= bcma_hcd_हटाओ,
	.shutकरोwn	= bcma_hcd_shutकरोwn,
	.suspend	= bcma_hcd_suspend,
	.resume		= bcma_hcd_resume,
पूर्ण;
module_bcma_driver(bcma_hcd_driver);
