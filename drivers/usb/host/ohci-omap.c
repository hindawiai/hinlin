<शैली गुरु>
// SPDX-License-Identअगरier: GPL-1.0+
/*
 * OHCI HCD (Host Controller Driver) क्रम USB.
 *
 * (C) Copyright 1999 Roman Weissgaerber <weissg@vienna.at>
 * (C) Copyright 2000-2005 David Brownell
 * (C) Copyright 2002 Hewlett-Packard Company
 *
 * OMAP Bus Glue
 *
 * Modअगरied क्रम OMAP by Tony Lindgren <tony@atomide.com>
 * Based on the 2.4 OMAP OHCI driver originally करोne by MontaVista Software Inc.
 * and on ohci-sa1111.c by Christopher Hoover <ch@hpl.hp.com>
 *
 * This file is licenced under the GPL.
 */

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पन.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>

#समावेश "ohci.h"

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/mach-types.h>

#समावेश <mach/mux.h>

#समावेश <mach/hardware.h>
#समावेश <mach/usb.h>


/* OMAP-1510 OHCI has its own MMU क्रम DMA */
#घोषणा OMAP1510_LB_MEMSIZE	32	/* Should be same as SDRAM size */
#घोषणा OMAP1510_LB_CLOCK_DIV	0xfffec10c
#घोषणा OMAP1510_LB_MMU_CTL	0xfffec208
#घोषणा OMAP1510_LB_MMU_LCK	0xfffec224
#घोषणा OMAP1510_LB_MMU_LD_TLB	0xfffec228
#घोषणा OMAP1510_LB_MMU_CAM_H	0xfffec22c
#घोषणा OMAP1510_LB_MMU_CAM_L	0xfffec230
#घोषणा OMAP1510_LB_MMU_RAM_H	0xfffec234
#घोषणा OMAP1510_LB_MMU_RAM_L	0xfffec238

#घोषणा DRIVER_DESC "OHCI OMAP driver"

काष्ठा ohci_omap_priv अणु
	काष्ठा clk *usb_host_ck;
	काष्ठा clk *usb_dc_ck;
	काष्ठा gpio_desc *घातer;
	काष्ठा gpio_desc *overcurrent;
पूर्ण;

अटल स्थिर अक्षर hcd_name[] = "ohci-omap";
अटल काष्ठा hc_driver __पढ़ो_mostly ohci_omap_hc_driver;

#घोषणा hcd_to_ohci_omap_priv(h) \
	((काष्ठा ohci_omap_priv *)hcd_to_ohci(h)->priv)

अटल व्योम omap_ohci_घड़ी_घातer(काष्ठा ohci_omap_priv *priv, पूर्णांक on)
अणु
	अगर (on) अणु
		clk_enable(priv->usb_dc_ck);
		clk_enable(priv->usb_host_ck);
		/* guesstimate क्रम T5 == 1x 32K घड़ी + APLL lock समय */
		udelay(100);
	पूर्ण अन्यथा अणु
		clk_disable(priv->usb_host_ck);
		clk_disable(priv->usb_dc_ck);
	पूर्ण
पूर्ण

/*
 * Board specअगरic gang-चयनed transceiver घातer on/off.
 * NOTE:  OSK supplies घातer from DC, not battery.
 */
अटल पूर्णांक omap_ohci_transceiver_घातer(काष्ठा ohci_omap_priv *priv, पूर्णांक on)
अणु
	अगर (on) अणु
		अगर (machine_is_omap_innovator() && cpu_is_omap1510())
			__raw_ग_लिखोb(__raw_पढ़ोb(INNOVATOR_FPGA_CAM_USB_CONTROL)
				| ((1 << 5/*usb1*/) | (1 << 3/*usb2*/)),
			       INNOVATOR_FPGA_CAM_USB_CONTROL);
		अन्यथा अगर (priv->घातer)
			gpiod_set_value_cansleep(priv->घातer, 0);
	पूर्ण अन्यथा अणु
		अगर (machine_is_omap_innovator() && cpu_is_omap1510())
			__raw_ग_लिखोb(__raw_पढ़ोb(INNOVATOR_FPGA_CAM_USB_CONTROL)
				& ~((1 << 5/*usb1*/) | (1 << 3/*usb2*/)),
			       INNOVATOR_FPGA_CAM_USB_CONTROL);
		अन्यथा अगर (priv->घातer)
			gpiod_set_value_cansleep(priv->घातer, 1);
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ARCH_OMAP15XX
/*
 * OMAP-1510 specअगरic Local Bus घड़ी on/off
 */
अटल पूर्णांक omap_1510_local_bus_घातer(पूर्णांक on)
अणु
	अगर (on) अणु
		omap_ग_लिखोl((1 << 1) | (1 << 0), OMAP1510_LB_MMU_CTL);
		udelay(200);
	पूर्ण अन्यथा अणु
		omap_ग_लिखोl(0, OMAP1510_LB_MMU_CTL);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * OMAP-1510 specअगरic Local Bus initialization
 * NOTE: This assumes 32MB memory size in OMAP1510LB_MEMSIZE.
 *       See also arch/mach-omap/memory.h क्रम __virt_to_dma() and
 *       __dma_to_virt() which need to match with the physical
 *       Local Bus address below.
 */
अटल पूर्णांक omap_1510_local_bus_init(व्योम)
अणु
	अचिन्हित पूर्णांक tlb;
	अचिन्हित दीर्घ lbaddr, physaddr;

	omap_ग_लिखोl((omap_पढ़ोl(OMAP1510_LB_CLOCK_DIV) & 0xfffffff8) | 0x4,
	       OMAP1510_LB_CLOCK_DIV);

	/* Configure the Local Bus MMU table */
	क्रम (tlb = 0; tlb < OMAP1510_LB_MEMSIZE; tlb++) अणु
		lbaddr = tlb * 0x00100000 + OMAP1510_LB_OFFSET;
		physaddr = tlb * 0x00100000 + PHYS_OFFSET;
		omap_ग_लिखोl((lbaddr & 0x0fffffff) >> 22, OMAP1510_LB_MMU_CAM_H);
		omap_ग_लिखोl(((lbaddr & 0x003ffc00) >> 6) | 0xc,
		       OMAP1510_LB_MMU_CAM_L);
		omap_ग_लिखोl(physaddr >> 16, OMAP1510_LB_MMU_RAM_H);
		omap_ग_लिखोl((physaddr & 0x0000fc00) | 0x300, OMAP1510_LB_MMU_RAM_L);
		omap_ग_लिखोl(tlb << 4, OMAP1510_LB_MMU_LCK);
		omap_ग_लिखोl(0x1, OMAP1510_LB_MMU_LD_TLB);
	पूर्ण

	/* Enable the walking table */
	omap_ग_लिखोl(omap_पढ़ोl(OMAP1510_LB_MMU_CTL) | (1 << 3), OMAP1510_LB_MMU_CTL);
	udelay(200);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा omap_1510_local_bus_घातer(x)	अणुपूर्ण
#घोषणा omap_1510_local_bus_init()	अणुपूर्ण
#पूर्ण_अगर

#अगर_घोषित	CONFIG_USB_OTG

अटल व्योम start_hnp(काष्ठा ohci_hcd *ohci)
अणु
	काष्ठा usb_hcd *hcd = ohci_to_hcd(ohci);
	स्थिर अचिन्हित	port = hcd->self.otg_port - 1;
	अचिन्हित दीर्घ	flags;
	u32 l;

	otg_start_hnp(hcd->usb_phy->otg);

	local_irq_save(flags);
	hcd->usb_phy->otg->state = OTG_STATE_A_SUSPEND;
	ग_लिखोl (RH_PS_PSS, &ohci->regs->roothub.portstatus [port]);
	l = omap_पढ़ोl(OTG_CTRL);
	l &= ~OTG_A_BUSREQ;
	omap_ग_लिखोl(l, OTG_CTRL);
	local_irq_restore(flags);
पूर्ण

#पूर्ण_अगर

/*-------------------------------------------------------------------------*/

अटल पूर्णांक ohci_omap_reset(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ohci_hcd		*ohci = hcd_to_ohci(hcd);
	काष्ठा omap_usb_config	*config = dev_get_platdata(hcd->self.controller);
	काष्ठा ohci_omap_priv	*priv = hcd_to_ohci_omap_priv(hcd);
	पूर्णांक			need_transceiver = (config->otg != 0);
	पूर्णांक			ret;

	dev_dbg(hcd->self.controller, "starting USB Controller\n");

	अगर (config->otg) अणु
		hcd->self.otg_port = config->otg;
		/* शेष/minimum OTG घातer budget:  8 mA */
		hcd->घातer_budget = 8;
	पूर्ण

	/* boards can use OTG transceivers in non-OTG modes */
	need_transceiver = need_transceiver
			|| machine_is_omap_h2() || machine_is_omap_h3();

	/* XXX OMAP16xx only */
	अगर (config->ocpi_enable)
		config->ocpi_enable();

#अगर_घोषित	CONFIG_USB_OTG
	अगर (need_transceiver) अणु
		hcd->usb_phy = usb_get_phy(USB_PHY_TYPE_USB2);
		अगर (!IS_ERR_OR_शून्य(hcd->usb_phy)) अणु
			पूर्णांक	status = otg_set_host(hcd->usb_phy->otg,
						&ohci_to_hcd(ohci)->self);
			dev_dbg(hcd->self.controller, "init %s phy, status %d\n",
					hcd->usb_phy->label, status);
			अगर (status) अणु
				usb_put_phy(hcd->usb_phy);
				वापस status;
			पूर्ण
		पूर्ण अन्यथा अणु
			वापस -EPROBE_DEFER;
		पूर्ण
		hcd->skip_phy_initialization = 1;
		ohci->start_hnp = start_hnp;
	पूर्ण
#पूर्ण_अगर

	omap_ohci_घड़ी_घातer(priv, 1);

	अगर (cpu_is_omap15xx()) अणु
		omap_1510_local_bus_घातer(1);
		omap_1510_local_bus_init();
	पूर्ण

	ret = ohci_setup(hcd);
	अगर (ret < 0)
		वापस ret;

	अगर (config->otg || config->rwc) अणु
		ohci->hc_control = OHCI_CTRL_RWC;
		ग_लिखोl(OHCI_CTRL_RWC, &ohci->regs->control);
	पूर्ण

	/* board-specअगरic घातer चयनing and overcurrent support */
	अगर (machine_is_omap_osk() || machine_is_omap_innovator()) अणु
		u32	rh = roothub_a (ohci);

		/* घातer चयनing (ganged by शेष) */
		rh &= ~RH_A_NPS;

		/* TPS2045 चयन क्रम पूर्णांकernal transceiver (port 1) */
		अगर (machine_is_omap_osk()) अणु
			ohci_to_hcd(ohci)->घातer_budget = 250;

			rh &= ~RH_A_NOCP;

			/* gpio9 क्रम overcurrent detction */
			omap_cfg_reg(W8_1610_GPIO9);

			/* क्रम paranoia's sake:  disable USB.PUEN */
			omap_cfg_reg(W4_USB_HIGHZ);
		पूर्ण
		ohci_ग_लिखोl(ohci, rh, &ohci->regs->roothub.a);
		ohci->flags &= ~OHCI_QUIRK_HUB_POWER;
	पूर्ण अन्यथा अगर (machine_is_nokia770()) अणु
		/* We require a self-घातered hub, which should have
		 * plenty of घातer. */
		ohci_to_hcd(ohci)->घातer_budget = 0;
	पूर्ण

	/* FIXME hub_wq hub requests should manage घातer चयनing */
	omap_ohci_transceiver_घातer(priv, 1);

	/* board init will have alपढ़ोy handled HMC and mux setup.
	 * any बाह्यal transceiver should alपढ़ोy be initialized
	 * too, so all configured ports use the right संकेतing now.
	 */

	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/

/**
 * ohci_hcd_omap_probe - initialize OMAP-based HCDs
 * @pdev:	USB controller to probe
 *
 * Context: task context, might sleep
 *
 * Allocates basic resources क्रम this USB host controller, and
 * then invokes the start() method क्रम the HCD associated with it
 * through the hotplug entry's driver_data.
 */
अटल पूर्णांक ohci_hcd_omap_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक retval, irq;
	काष्ठा usb_hcd *hcd = 0;
	काष्ठा ohci_omap_priv *priv;

	अगर (pdev->num_resources != 2) अणु
		dev_err(&pdev->dev, "invalid num_resources: %i\n",
		       pdev->num_resources);
		वापस -ENODEV;
	पूर्ण

	अगर (pdev->resource[0].flags != IORESOURCE_MEM
			|| pdev->resource[1].flags != IORESOURCE_IRQ) अणु
		dev_err(&pdev->dev, "invalid resource type\n");
		वापस -ENODEV;
	पूर्ण

	hcd = usb_create_hcd(&ohci_omap_hc_driver, &pdev->dev,
			dev_name(&pdev->dev));
	अगर (!hcd)
		वापस -ENOMEM;

	hcd->rsrc_start = pdev->resource[0].start;
	hcd->rsrc_len = pdev->resource[0].end - pdev->resource[0].start + 1;
	priv = hcd_to_ohci_omap_priv(hcd);

	/* Obtain two optional GPIO lines */
	priv->घातer = devm_gpiod_get_optional(&pdev->dev, "power", GPIOD_ASIS);
	अगर (IS_ERR(priv->घातer)) अणु
		retval = PTR_ERR(priv->घातer);
		जाओ err_put_hcd;
	पूर्ण
	अगर (priv->घातer)
		gpiod_set_consumer_name(priv->घातer, "OHCI power");

	/*
	 * This "overcurrent" GPIO line isn't really used in the code,
	 * but has a designated hardware function.
	 * TODO: implement proper overcurrent handling.
	 */
	priv->overcurrent = devm_gpiod_get_optional(&pdev->dev, "overcurrent",
						    GPIOD_IN);
	अगर (IS_ERR(priv->overcurrent)) अणु
		retval = PTR_ERR(priv->overcurrent);
		जाओ err_put_hcd;
	पूर्ण
	अगर (priv->overcurrent)
		gpiod_set_consumer_name(priv->overcurrent, "OHCI overcurrent");

	priv->usb_host_ck = clk_get(&pdev->dev, "usb_hhc_ck");
	अगर (IS_ERR(priv->usb_host_ck)) अणु
		retval = PTR_ERR(priv->usb_host_ck);
		जाओ err_put_hcd;
	पूर्ण

	अगर (!cpu_is_omap15xx())
		priv->usb_dc_ck = clk_get(&pdev->dev, "usb_dc_ck");
	अन्यथा
		priv->usb_dc_ck = clk_get(&pdev->dev, "lb_ck");

	अगर (IS_ERR(priv->usb_dc_ck)) अणु
		retval = PTR_ERR(priv->usb_dc_ck);
		जाओ err_put_host_ck;
	पूर्ण

	अगर (!request_mem_region(hcd->rsrc_start, hcd->rsrc_len, hcd_name)) अणु
		dev_dbg(&pdev->dev, "request_mem_region failed\n");
		retval = -EBUSY;
		जाओ err_put_dc_ck;
	पूर्ण

	hcd->regs = ioremap(hcd->rsrc_start, hcd->rsrc_len);
	अगर (!hcd->regs) अणु
		dev_err(&pdev->dev, "can't ioremap OHCI HCD\n");
		retval = -ENOMEM;
		जाओ err2;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		retval = -ENXIO;
		जाओ err3;
	पूर्ण
	retval = usb_add_hcd(hcd, irq, 0);
	अगर (retval)
		जाओ err3;

	device_wakeup_enable(hcd->self.controller);
	वापस 0;
err3:
	iounmap(hcd->regs);
err2:
	release_mem_region(hcd->rsrc_start, hcd->rsrc_len);
err_put_dc_ck:
	clk_put(priv->usb_dc_ck);
err_put_host_ck:
	clk_put(priv->usb_host_ck);
err_put_hcd:
	usb_put_hcd(hcd);
	वापस retval;
पूर्ण


/* may be called with controller, bus, and devices active */

/**
 * ohci_hcd_omap_हटाओ - shutकरोwn processing क्रम OMAP-based HCDs
 * @pdev: USB Host Controller being हटाओd
 *
 * Context: task context, might sleep
 *
 * Reverses the effect of ohci_hcd_omap_probe(), first invoking
 * the HCD's stop() method.  It is always called from a thपढ़ो
 * context, normally "rmmod", "apmd", or something similar.
 */
अटल पूर्णांक ohci_hcd_omap_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_hcd	*hcd = platक्रमm_get_drvdata(pdev);
	काष्ठा ohci_omap_priv *priv = hcd_to_ohci_omap_priv(hcd);

	dev_dbg(hcd->self.controller, "stopping USB Controller\n");
	usb_हटाओ_hcd(hcd);
	omap_ohci_घड़ी_घातer(priv, 0);
	अगर (!IS_ERR_OR_शून्य(hcd->usb_phy)) अणु
		(व्योम) otg_set_host(hcd->usb_phy->otg, 0);
		usb_put_phy(hcd->usb_phy);
	पूर्ण
	iounmap(hcd->regs);
	release_mem_region(hcd->rsrc_start, hcd->rsrc_len);
	clk_put(priv->usb_dc_ck);
	clk_put(priv->usb_host_ck);
	usb_put_hcd(hcd);
	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/

#अगर_घोषित	CONFIG_PM

अटल पूर्णांक ohci_omap_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t message)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(pdev);
	काष्ठा ohci_hcd *ohci = hcd_to_ohci(hcd);
	काष्ठा ohci_omap_priv *priv = hcd_to_ohci_omap_priv(hcd);
	bool करो_wakeup = device_may_wakeup(&pdev->dev);
	पूर्णांक ret;

	अगर (समय_beक्रमe(jअगरfies, ohci->next_statechange))
		msleep(5);
	ohci->next_statechange = jअगरfies;

	ret = ohci_suspend(hcd, करो_wakeup);
	अगर (ret)
		वापस ret;

	omap_ohci_घड़ी_घातer(priv, 0);
	वापस ret;
पूर्ण

अटल पूर्णांक ohci_omap_resume(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा usb_hcd	*hcd = platक्रमm_get_drvdata(dev);
	काष्ठा ohci_hcd	*ohci = hcd_to_ohci(hcd);
	काष्ठा ohci_omap_priv *priv = hcd_to_ohci_omap_priv(hcd);

	अगर (समय_beक्रमe(jअगरfies, ohci->next_statechange))
		msleep(5);
	ohci->next_statechange = jअगरfies;

	omap_ohci_घड़ी_घातer(priv, 1);
	ohci_resume(hcd, false);
	वापस 0;
पूर्ण

#पूर्ण_अगर

/*-------------------------------------------------------------------------*/

/*
 * Driver definition to रेजिस्टर with the OMAP bus
 */
अटल काष्ठा platक्रमm_driver ohci_hcd_omap_driver = अणु
	.probe		= ohci_hcd_omap_probe,
	.हटाओ		= ohci_hcd_omap_हटाओ,
	.shutकरोwn	= usb_hcd_platक्रमm_shutकरोwn,
#अगर_घोषित	CONFIG_PM
	.suspend	= ohci_omap_suspend,
	.resume		= ohci_omap_resume,
#पूर्ण_अगर
	.driver		= अणु
		.name	= "ohci",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ohci_driver_overrides omap_overrides __initस्थिर = अणु
	.product_desc	= "OMAP OHCI",
	.reset		= ohci_omap_reset,
	.extra_priv_size = माप(काष्ठा ohci_omap_priv),
पूर्ण;

अटल पूर्णांक __init ohci_omap_init(व्योम)
अणु
	अगर (usb_disabled())
		वापस -ENODEV;

	pr_info("%s: " DRIVER_DESC "\n", hcd_name);

	ohci_init_driver(&ohci_omap_hc_driver, &omap_overrides);
	वापस platक्रमm_driver_रेजिस्टर(&ohci_hcd_omap_driver);
पूर्ण
module_init(ohci_omap_init);

अटल व्योम __निकास ohci_omap_cleanup(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ohci_hcd_omap_driver);
पूर्ण
module_निकास(ohci_omap_cleanup);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_ALIAS("platform:ohci");
MODULE_LICENSE("GPL");
