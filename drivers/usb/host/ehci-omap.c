<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ehci-omap.c - driver क्रम USBHOST on OMAP3/4 processors
 *
 * Bus Glue क्रम the EHCI controllers in OMAP3/4
 * Tested on several OMAP3 boards, and OMAP4 Pandaboard
 *
 * Copyright (C) 2007-2013 Texas Instruments, Inc.
 *	Author: Vikram Pandita <vikram.pandita@ti.com>
 *	Author: Anand Gadiyar <gadiyar@ti.com>
 *	Author: Keshava Munegowda <keshava_mgowda@ti.com>
 *	Author: Roger Quadros <rogerq@ti.com>
 *
 * Copyright (C) 2009 Nokia Corporation
 *	Contact: Felipe Balbi <felipe.balbi@nokia.com>
 *
 * Based on "ehci-fsl.c" and "ehci-au1xxx.c" ehci glue layers
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb/ulpi.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/clk.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/of.h>
#समावेश <linux/dma-mapping.h>

#समावेश "ehci.h"

#समावेश <linux/platक्रमm_data/usb-omap.h>

/* EHCI Register Set */
#घोषणा EHCI_INSNREG04					(0xA0)
#घोषणा EHCI_INSNREG04_DISABLE_UNSUSPEND		(1 << 5)
#घोषणा	EHCI_INSNREG05_ULPI				(0xA4)
#घोषणा	EHCI_INSNREG05_ULPI_CONTROL_SHIFT		31
#घोषणा	EHCI_INSNREG05_ULPI_PORTSEL_SHIFT		24
#घोषणा	EHCI_INSNREG05_ULPI_OPSEL_SHIFT			22
#घोषणा	EHCI_INSNREG05_ULPI_REGADD_SHIFT		16
#घोषणा	EHCI_INSNREG05_ULPI_EXTREGADD_SHIFT		8
#घोषणा	EHCI_INSNREG05_ULPI_WRDATA_SHIFT		0

#घोषणा DRIVER_DESC "OMAP-EHCI Host Controller driver"

अटल स्थिर अक्षर hcd_name[] = "ehci-omap";

/*-------------------------------------------------------------------------*/

काष्ठा omap_hcd अणु
	काष्ठा usb_phy *phy[OMAP3_HS_USB_PORTS]; /* one PHY क्रम each port */
	पूर्णांक nports;
पूर्ण;

अटल अंतरभूत व्योम ehci_ग_लिखो(व्योम __iomem *base, u32 reg, u32 val)
अणु
	__raw_ग_लिखोl(val, base + reg);
पूर्ण

अटल अंतरभूत u32 ehci_पढ़ो(व्योम __iomem *base, u32 reg)
अणु
	वापस __raw_पढ़ोl(base + reg);
पूर्ण

/* configure so an HC device and id are always provided */
/* always called with process context; sleeping is OK */

अटल काष्ठा hc_driver __पढ़ो_mostly ehci_omap_hc_driver;

अटल स्थिर काष्ठा ehci_driver_overrides ehci_omap_overrides __initस्थिर = अणु
	.extra_priv_size = माप(काष्ठा omap_hcd),
पूर्ण;

/**
 * ehci_hcd_omap_probe - initialize TI-based HCDs
 * @pdev: Poपूर्णांकer to this platक्रमm device's inक्रमmation
 *
 * Allocates basic resources क्रम this USB host controller, and
 * then invokes the start() method क्रम the HCD associated with it
 * through the hotplug entry's driver_data.
 */
अटल पूर्णांक ehci_hcd_omap_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा usbhs_omap_platक्रमm_data *pdata = dev_get_platdata(dev);
	काष्ठा resource	*res;
	काष्ठा usb_hcd	*hcd;
	व्योम __iomem *regs;
	पूर्णांक ret;
	पूर्णांक irq;
	पूर्णांक i;
	काष्ठा omap_hcd	*omap;

	अगर (usb_disabled())
		वापस -ENODEV;

	अगर (!dev->parent) अणु
		dev_err(dev, "Missing parent device\n");
		वापस -ENODEV;
	पूर्ण

	/* For DT boot, get platक्रमm data from parent. i.e. usbhshost */
	अगर (dev->of_node) अणु
		pdata = dev_get_platdata(dev->parent);
		dev->platक्रमm_data = pdata;
	पूर्ण

	अगर (!pdata) अणु
		dev_err(dev, "Missing platform data\n");
		वापस -ENODEV;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	res =  platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	/*
	 * Right now device-tree probed devices करोn't get dma_mask set.
	 * Since shared usb code relies on it, set it here क्रम now.
	 * Once we have dma capability bindings this can go away.
	 */
	ret = dma_coerce_mask_and_coherent(dev, DMA_BIT_MASK(32));
	अगर (ret)
		वापस ret;

	ret = -ENODEV;
	hcd = usb_create_hcd(&ehci_omap_hc_driver, dev,
			dev_name(dev));
	अगर (!hcd) अणु
		dev_err(dev, "Failed to create HCD\n");
		वापस -ENOMEM;
	पूर्ण

	hcd->rsrc_start = res->start;
	hcd->rsrc_len = resource_size(res);
	hcd->regs = regs;
	hcd_to_ehci(hcd)->caps = regs;

	omap = (काष्ठा omap_hcd *)hcd_to_ehci(hcd)->priv;
	omap->nports = pdata->nports;

	platक्रमm_set_drvdata(pdev, hcd);

	/* get the PHY devices अगर needed */
	क्रम (i = 0 ; i < omap->nports ; i++) अणु
		काष्ठा usb_phy *phy;

		/* get the PHY device */
		phy = devm_usb_get_phy_by_phandle(dev, "phys", i);
		अगर (IS_ERR(phy)) अणु
			ret = PTR_ERR(phy);
			अगर (ret == -ENODEV) अणु /* no PHY */
				phy = शून्य;
				जारी;
			पूर्ण

			अगर (ret != -EPROBE_DEFER)
				dev_err(dev, "Can't get PHY for port %d: %d\n",
					i, ret);
			जाओ err_phy;
		पूर्ण

		omap->phy[i] = phy;

		अगर (pdata->port_mode[i] == OMAP_EHCI_PORT_MODE_PHY) अणु
			usb_phy_init(omap->phy[i]);
			/* bring PHY out of suspend */
			usb_phy_set_suspend(omap->phy[i], 0);
		पूर्ण
	पूर्ण

	pm_runसमय_enable(dev);
	pm_runसमय_get_sync(dev);

	/*
	 * An unकरोcumented "feature" in the OMAP3 EHCI controller,
	 * causes suspended ports to be taken out of suspend when
	 * the USBCMD.Run/Stop bit is cleared (क्रम example when
	 * we करो ehci_bus_suspend).
	 * This अवरोधs suspend-resume अगर the root-hub is allowed
	 * to suspend. Writing 1 to this unकरोcumented रेजिस्टर bit
	 * disables this feature and restores normal behavior.
	 */
	ehci_ग_लिखो(regs, EHCI_INSNREG04,
				EHCI_INSNREG04_DISABLE_UNSUSPEND);

	ret = usb_add_hcd(hcd, irq, IRQF_SHARED);
	अगर (ret) अणु
		dev_err(dev, "failed to add hcd with err %d\n", ret);
		जाओ err_pm_runसमय;
	पूर्ण
	device_wakeup_enable(hcd->self.controller);

	/*
	 * Bring PHYs out of reset क्रम non PHY modes.
	 * Even though HSIC mode is a PHY-less mode, the reset
	 * line exists between the chips and can be modelled
	 * as a PHY device क्रम reset control.
	 */
	क्रम (i = 0; i < omap->nports; i++) अणु
		अगर (!omap->phy[i] ||
		     pdata->port_mode[i] == OMAP_EHCI_PORT_MODE_PHY)
			जारी;

		usb_phy_init(omap->phy[i]);
		/* bring PHY out of suspend */
		usb_phy_set_suspend(omap->phy[i], 0);
	पूर्ण

	वापस 0;

err_pm_runसमय:
	pm_runसमय_put_sync(dev);
	pm_runसमय_disable(dev);

err_phy:
	क्रम (i = 0; i < omap->nports; i++) अणु
		अगर (omap->phy[i])
			usb_phy_shutकरोwn(omap->phy[i]);
	पूर्ण

	usb_put_hcd(hcd);

	वापस ret;
पूर्ण


/**
 * ehci_hcd_omap_हटाओ - shutकरोwn processing क्रम EHCI HCDs
 * @pdev: USB Host Controller being हटाओd
 *
 * Reverses the effect of usb_ehci_hcd_omap_probe(), first invoking
 * the HCD's stop() method.  It is always called from a thपढ़ो
 * context, normally "rmmod", "apmd", or something similar.
 */
अटल पूर्णांक ehci_hcd_omap_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा usb_hcd *hcd = dev_get_drvdata(dev);
	काष्ठा omap_hcd *omap = (काष्ठा omap_hcd *)hcd_to_ehci(hcd)->priv;
	पूर्णांक i;

	usb_हटाओ_hcd(hcd);

	क्रम (i = 0; i < omap->nports; i++) अणु
		अगर (omap->phy[i])
			usb_phy_shutकरोwn(omap->phy[i]);
	पूर्ण

	usb_put_hcd(hcd);
	pm_runसमय_put_sync(dev);
	pm_runसमय_disable(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id omap_ehci_dt_ids[] = अणु
	अणु .compatible = "ti,ehci-omap" पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, omap_ehci_dt_ids);

अटल काष्ठा platक्रमm_driver ehci_hcd_omap_driver = अणु
	.probe			= ehci_hcd_omap_probe,
	.हटाओ			= ehci_hcd_omap_हटाओ,
	.shutकरोwn		= usb_hcd_platक्रमm_shutकरोwn,
	/*.suspend		= ehci_hcd_omap_suspend, */
	/*.resume		= ehci_hcd_omap_resume, */
	.driver = अणु
		.name		= hcd_name,
		.of_match_table = omap_ehci_dt_ids,
	पूर्ण
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल पूर्णांक __init ehci_omap_init(व्योम)
अणु
	अगर (usb_disabled())
		वापस -ENODEV;

	pr_info("%s: " DRIVER_DESC "\n", hcd_name);

	ehci_init_driver(&ehci_omap_hc_driver, &ehci_omap_overrides);
	वापस platक्रमm_driver_रेजिस्टर(&ehci_hcd_omap_driver);
पूर्ण
module_init(ehci_omap_init);

अटल व्योम __निकास ehci_omap_cleanup(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ehci_hcd_omap_driver);
पूर्ण
module_निकास(ehci_omap_cleanup);

MODULE_ALIAS("platform:ehci-omap");
MODULE_AUTHOR("Texas Instruments, Inc.");
MODULE_AUTHOR("Felipe Balbi <felipe.balbi@nokia.com>");
MODULE_AUTHOR("Roger Quadros <rogerq@ti.com>");

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
