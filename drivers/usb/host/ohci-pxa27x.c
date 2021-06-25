<शैली गुरु>
// SPDX-License-Identअगरier: GPL-1.0+
/*
 * OHCI HCD (Host Controller Driver) क्रम USB.
 *
 * (C) Copyright 1999 Roman Weissgaerber <weissg@vienna.at>
 * (C) Copyright 2000-2002 David Brownell <dbrownell@users.sourceक्रमge.net>
 * (C) Copyright 2002 Hewlett-Packard Company
 *
 * Bus Glue क्रम pxa27x
 *
 * Written by Christopher Hoover <ch@hpl.hp.com>
 * Based on fragments of previous driver by Russell King et al.
 *
 * Modअगरied क्रम LH7A404 from ohci-sa1111.c
 *  by Durgesh Pattamatta <pattamattad@sharpsec.com>
 *
 * Modअगरied क्रम pxa27x from ohci-lh7a404.c
 *  by Nick Bane <nick@cecomputing.co.uk> 26-8-2004
 *
 * This file is licenced under the GPL.
 */

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/platक्रमm_data/usb-ohci-pxa27x.h>
#समावेश <linux/platक्रमm_data/usb-pxa3xx-ulpi.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/usb/otg.h>

#समावेश <mach/hardware.h>

#समावेश "ohci.h"

#घोषणा DRIVER_DESC "OHCI PXA27x/PXA3x driver"

/*
 * UHC: USB Host Controller (OHCI-like) रेजिस्टर definitions
 */
#घोषणा UHCREV		(0x0000) /* UHC HCI Spec Revision */
#घोषणा UHCHCON		(0x0004) /* UHC Host Control Register */
#घोषणा UHCCOMS		(0x0008) /* UHC Command Status Register */
#घोषणा UHCINTS		(0x000C) /* UHC Interrupt Status Register */
#घोषणा UHCINTE		(0x0010) /* UHC Interrupt Enable */
#घोषणा UHCINTD		(0x0014) /* UHC Interrupt Disable */
#घोषणा UHCHCCA		(0x0018) /* UHC Host Controller Comm. Area */
#घोषणा UHCPCED		(0x001C) /* UHC Period Current Endpt Descr */
#घोषणा UHCCHED		(0x0020) /* UHC Control Head Endpt Descr */
#घोषणा UHCCCED		(0x0024) /* UHC Control Current Endpt Descr */
#घोषणा UHCBHED		(0x0028) /* UHC Bulk Head Endpt Descr */
#घोषणा UHCBCED		(0x002C) /* UHC Bulk Current Endpt Descr */
#घोषणा UHCDHEAD	(0x0030) /* UHC Done Head */
#घोषणा UHCFMI		(0x0034) /* UHC Frame Interval */
#घोषणा UHCFMR		(0x0038) /* UHC Frame Reमुख्यing */
#घोषणा UHCFMN		(0x003C) /* UHC Frame Number */
#घोषणा UHCPERS		(0x0040) /* UHC Periodic Start */
#घोषणा UHCLS		(0x0044) /* UHC Low Speed Threshold */

#घोषणा UHCRHDA		(0x0048) /* UHC Root Hub Descriptor A */
#घोषणा UHCRHDA_NOCP	(1 << 12)	/* No over current protection */
#घोषणा UHCRHDA_OCPM	(1 << 11)	/* Over Current Protection Mode */
#घोषणा UHCRHDA_POTPGT(x) \
			(((x) & 0xff) << 24) /* Power On To Power Good Time */

#घोषणा UHCRHDB		(0x004C) /* UHC Root Hub Descriptor B */
#घोषणा UHCRHS		(0x0050) /* UHC Root Hub Status */
#घोषणा UHCRHPS1	(0x0054) /* UHC Root Hub Port 1 Status */
#घोषणा UHCRHPS2	(0x0058) /* UHC Root Hub Port 2 Status */
#घोषणा UHCRHPS3	(0x005C) /* UHC Root Hub Port 3 Status */

#घोषणा UHCSTAT		(0x0060) /* UHC Status Register */
#घोषणा UHCSTAT_UPS3	(1 << 16)	/* USB Power Sense Port3 */
#घोषणा UHCSTAT_SBMAI	(1 << 15)	/* System Bus Master Abort Interrupt*/
#घोषणा UHCSTAT_SBTAI	(1 << 14)	/* System Bus Target Abort Interrupt*/
#घोषणा UHCSTAT_UPRI	(1 << 13)	/* USB Port Resume Interrupt */
#घोषणा UHCSTAT_UPS2	(1 << 12)	/* USB Power Sense Port 2 */
#घोषणा UHCSTAT_UPS1	(1 << 11)	/* USB Power Sense Port 1 */
#घोषणा UHCSTAT_HTA	(1 << 10)	/* HCI Target Abort */
#घोषणा UHCSTAT_HBA	(1 << 8)	/* HCI Buffer Active */
#घोषणा UHCSTAT_RWUE	(1 << 7)	/* HCI Remote Wake Up Event */

#घोषणा UHCHR           (0x0064) /* UHC Reset Register */
#घोषणा UHCHR_SSEP3	(1 << 11)	/* Sleep Standby Enable क्रम Port3 */
#घोषणा UHCHR_SSEP2	(1 << 10)	/* Sleep Standby Enable क्रम Port2 */
#घोषणा UHCHR_SSEP1	(1 << 9)	/* Sleep Standby Enable क्रम Port1 */
#घोषणा UHCHR_PCPL	(1 << 7)	/* Power control polarity low */
#घोषणा UHCHR_PSPL	(1 << 6)	/* Power sense polarity low */
#घोषणा UHCHR_SSE	(1 << 5)	/* Sleep Standby Enable */
#घोषणा UHCHR_UIT	(1 << 4)	/* USB Interrupt Test */
#घोषणा UHCHR_SSDC	(1 << 3)	/* Simulation Scale Down Clock */
#घोषणा UHCHR_CGR	(1 << 2)	/* Clock Generation Reset */
#घोषणा UHCHR_FHR	(1 << 1)	/* Force Host Controller Reset */
#घोषणा UHCHR_FSBIR	(1 << 0)	/* Force System Bus Iface Reset */

#घोषणा UHCHIE          (0x0068) /* UHC Interrupt Enable Register*/
#घोषणा UHCHIE_UPS3IE	(1 << 14)	/* Power Sense Port3 IntEn */
#घोषणा UHCHIE_UPRIE	(1 << 13)	/* Port Resume IntEn */
#घोषणा UHCHIE_UPS2IE	(1 << 12)	/* Power Sense Port2 IntEn */
#घोषणा UHCHIE_UPS1IE	(1 << 11)	/* Power Sense Port1 IntEn */
#घोषणा UHCHIE_TAIE	(1 << 10)	/* HCI Interface Transfer Abort
					   Interrupt Enable*/
#घोषणा UHCHIE_HBAIE	(1 << 8)	/* HCI Buffer Active IntEn */
#घोषणा UHCHIE_RWIE	(1 << 7)	/* Remote Wake-up IntEn */

#घोषणा UHCHIT          (0x006C) /* UHC Interrupt Test रेजिस्टर */

#घोषणा PXA_UHC_MAX_PORTNUM    3

अटल स्थिर अक्षर hcd_name[] = "ohci-pxa27x";

अटल काष्ठा hc_driver __पढ़ो_mostly ohci_pxa27x_hc_driver;

काष्ठा pxa27x_ohci अणु
	काष्ठा clk	*clk;
	व्योम __iomem	*mmio_base;
	काष्ठा regulator *vbus[3];
	bool		vbus_enabled[3];
पूर्ण;

#घोषणा to_pxa27x_ohci(hcd)	(काष्ठा pxa27x_ohci *)(hcd_to_ohci(hcd)->priv)

/*
  PMM_NPS_MODE -- PMM Non-घातer चयनing mode
      Ports are घातered continuously.

  PMM_GLOBAL_MODE -- PMM global चयनing mode
      All ports are घातered at the same समय.

  PMM_PERPORT_MODE -- PMM per port चयनing mode
      Ports are घातered inभागidually.
 */
अटल पूर्णांक pxa27x_ohci_select_pmm(काष्ठा pxa27x_ohci *pxa_ohci, पूर्णांक mode)
अणु
	uपूर्णांक32_t uhcrhda = __raw_पढ़ोl(pxa_ohci->mmio_base + UHCRHDA);
	uपूर्णांक32_t uhcrhdb = __raw_पढ़ोl(pxa_ohci->mmio_base + UHCRHDB);

	चयन (mode) अणु
	हाल PMM_NPS_MODE:
		uhcrhda |= RH_A_NPS;
		अवरोध;
	हाल PMM_GLOBAL_MODE:
		uhcrhda &= ~(RH_A_NPS | RH_A_PSM);
		अवरोध;
	हाल PMM_PERPORT_MODE:
		uhcrhda &= ~(RH_A_NPS);
		uhcrhda |= RH_A_PSM;

		/* Set port घातer control mask bits, only 3 ports. */
		uhcrhdb |= (0x7<<17);
		अवरोध;
	शेष:
		prपूर्णांकk( KERN_ERR
			"Invalid mode %d, set to non-power switch mode.\n",
			mode );

		uhcrhda |= RH_A_NPS;
	पूर्ण

	__raw_ग_लिखोl(uhcrhda, pxa_ohci->mmio_base + UHCRHDA);
	__raw_ग_लिखोl(uhcrhdb, pxa_ohci->mmio_base + UHCRHDB);
	वापस 0;
पूर्ण

अटल पूर्णांक pxa27x_ohci_set_vbus_घातer(काष्ठा pxa27x_ohci *pxa_ohci,
				      अचिन्हित पूर्णांक port, bool enable)
अणु
	काष्ठा regulator *vbus = pxa_ohci->vbus[port];
	पूर्णांक ret = 0;

	अगर (IS_ERR_OR_शून्य(vbus))
		वापस 0;

	अगर (enable && !pxa_ohci->vbus_enabled[port])
		ret = regulator_enable(vbus);
	अन्यथा अगर (!enable && pxa_ohci->vbus_enabled[port])
		ret = regulator_disable(vbus);

	अगर (ret < 0)
		वापस ret;

	pxa_ohci->vbus_enabled[port] = enable;

	वापस 0;
पूर्ण

अटल पूर्णांक pxa27x_ohci_hub_control(काष्ठा usb_hcd *hcd, u16 typeReq, u16 wValue,
				   u16 wIndex, अक्षर *buf, u16 wLength)
अणु
	काष्ठा pxa27x_ohci *pxa_ohci = to_pxa27x_ohci(hcd);
	पूर्णांक ret;

	चयन (typeReq) अणु
	हाल SetPortFeature:
	हाल ClearPortFeature:
		अगर (!wIndex || wIndex > 3)
			वापस -EPIPE;

		अगर (wValue != USB_PORT_FEAT_POWER)
			अवरोध;

		ret = pxa27x_ohci_set_vbus_घातer(pxa_ohci, wIndex - 1,
						 typeReq == SetPortFeature);
		अगर (ret)
			वापस ret;
		अवरोध;
	पूर्ण

	वापस ohci_hub_control(hcd, typeReq, wValue, wIndex, buf, wLength);
पूर्ण
/*-------------------------------------------------------------------------*/

अटल अंतरभूत व्योम pxa27x_setup_hc(काष्ठा pxa27x_ohci *pxa_ohci,
				   काष्ठा pxaohci_platक्रमm_data *inf)
अणु
	uपूर्णांक32_t uhchr = __raw_पढ़ोl(pxa_ohci->mmio_base + UHCHR);
	uपूर्णांक32_t uhcrhda = __raw_पढ़ोl(pxa_ohci->mmio_base + UHCRHDA);

	अगर (inf->flags & ENABLE_PORT1)
		uhchr &= ~UHCHR_SSEP1;

	अगर (inf->flags & ENABLE_PORT2)
		uhchr &= ~UHCHR_SSEP2;

	अगर (inf->flags & ENABLE_PORT3)
		uhchr &= ~UHCHR_SSEP3;

	अगर (inf->flags & POWER_CONTROL_LOW)
		uhchr |= UHCHR_PCPL;

	अगर (inf->flags & POWER_SENSE_LOW)
		uhchr |= UHCHR_PSPL;

	अगर (inf->flags & NO_OC_PROTECTION)
		uhcrhda |= UHCRHDA_NOCP;
	अन्यथा
		uhcrhda &= ~UHCRHDA_NOCP;

	अगर (inf->flags & OC_MODE_PERPORT)
		uhcrhda |= UHCRHDA_OCPM;
	अन्यथा
		uhcrhda &= ~UHCRHDA_OCPM;

	अगर (inf->घातer_on_delay) अणु
		uhcrhda &= ~UHCRHDA_POTPGT(0xff);
		uhcrhda |= UHCRHDA_POTPGT(inf->घातer_on_delay / 2);
	पूर्ण

	__raw_ग_लिखोl(uhchr, pxa_ohci->mmio_base + UHCHR);
	__raw_ग_लिखोl(uhcrhda, pxa_ohci->mmio_base + UHCRHDA);
पूर्ण

अटल अंतरभूत व्योम pxa27x_reset_hc(काष्ठा pxa27x_ohci *pxa_ohci)
अणु
	uपूर्णांक32_t uhchr = __raw_पढ़ोl(pxa_ohci->mmio_base + UHCHR);

	__raw_ग_लिखोl(uhchr | UHCHR_FHR, pxa_ohci->mmio_base + UHCHR);
	udelay(11);
	__raw_ग_लिखोl(uhchr & ~UHCHR_FHR, pxa_ohci->mmio_base + UHCHR);
पूर्ण

#अगर_घोषित CONFIG_PXA27x
बाह्य व्योम pxa27x_clear_otgph(व्योम);
#अन्यथा
#घोषणा pxa27x_clear_otgph()	करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

अटल पूर्णांक pxa27x_start_hc(काष्ठा pxa27x_ohci *pxa_ohci, काष्ठा device *dev)
अणु
	पूर्णांक retval;
	काष्ठा pxaohci_platक्रमm_data *inf;
	uपूर्णांक32_t uhchr;
	काष्ठा usb_hcd *hcd = dev_get_drvdata(dev);

	inf = dev_get_platdata(dev);

	retval = clk_prepare_enable(pxa_ohci->clk);
	अगर (retval)
		वापस retval;

	pxa27x_reset_hc(pxa_ohci);

	uhchr = __raw_पढ़ोl(pxa_ohci->mmio_base + UHCHR) | UHCHR_FSBIR;
	__raw_ग_लिखोl(uhchr, pxa_ohci->mmio_base + UHCHR);

	जबतक (__raw_पढ़ोl(pxa_ohci->mmio_base + UHCHR) & UHCHR_FSBIR)
		cpu_relax();

	pxa27x_setup_hc(pxa_ohci, inf);

	अगर (inf->init)
		retval = inf->init(dev);

	अगर (retval < 0) अणु
		clk_disable_unprepare(pxa_ohci->clk);
		वापस retval;
	पूर्ण

	अगर (cpu_is_pxa3xx())
		pxa3xx_u2d_start_hc(&hcd->self);

	uhchr = __raw_पढ़ोl(pxa_ohci->mmio_base + UHCHR) & ~UHCHR_SSE;
	__raw_ग_लिखोl(uhchr, pxa_ohci->mmio_base + UHCHR);
	__raw_ग_लिखोl(UHCHIE_UPRIE | UHCHIE_RWIE, pxa_ohci->mmio_base + UHCHIE);

	/* Clear any OTG Pin Hold */
	pxa27x_clear_otgph();
	वापस 0;
पूर्ण

अटल व्योम pxa27x_stop_hc(काष्ठा pxa27x_ohci *pxa_ohci, काष्ठा device *dev)
अणु
	काष्ठा pxaohci_platक्रमm_data *inf;
	काष्ठा usb_hcd *hcd = dev_get_drvdata(dev);
	uपूर्णांक32_t uhccoms;

	inf = dev_get_platdata(dev);

	अगर (cpu_is_pxa3xx())
		pxa3xx_u2d_stop_hc(&hcd->self);

	अगर (inf->निकास)
		inf->निकास(dev);

	pxa27x_reset_hc(pxa_ohci);

	/* Host Controller Reset */
	uhccoms = __raw_पढ़ोl(pxa_ohci->mmio_base + UHCCOMS) | 0x01;
	__raw_ग_लिखोl(uhccoms, pxa_ohci->mmio_base + UHCCOMS);
	udelay(10);

	clk_disable_unprepare(pxa_ohci->clk);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id pxa_ohci_dt_ids[] = अणु
	अणु .compatible = "marvell,pxa-ohci" पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, pxa_ohci_dt_ids);

अटल पूर्णांक ohci_pxa_of_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा pxaohci_platक्रमm_data *pdata;
	u32 पंचांगp;
	पूर्णांक ret;

	अगर (!np)
		वापस 0;

	/* Right now device-tree probed devices करोn't get dma_mask set.
	 * Since shared usb code relies on it, set it here क्रम now.
	 * Once we have dma capability bindings this can go away.
	 */
	ret = dma_coerce_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (ret)
		वापस ret;

	pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	अगर (of_property_पढ़ो_bool(np, "marvell,enable-port1"))
		pdata->flags |= ENABLE_PORT1;
	अगर (of_property_पढ़ो_bool(np, "marvell,enable-port2"))
		pdata->flags |= ENABLE_PORT2;
	अगर (of_property_पढ़ो_bool(np, "marvell,enable-port3"))
		pdata->flags |= ENABLE_PORT3;
	अगर (of_property_पढ़ो_bool(np, "marvell,port-sense-low"))
		pdata->flags |= POWER_SENSE_LOW;
	अगर (of_property_पढ़ो_bool(np, "marvell,power-control-low"))
		pdata->flags |= POWER_CONTROL_LOW;
	अगर (of_property_पढ़ो_bool(np, "marvell,no-oc-protection"))
		pdata->flags |= NO_OC_PROTECTION;
	अगर (of_property_पढ़ो_bool(np, "marvell,oc-mode-perport"))
		pdata->flags |= OC_MODE_PERPORT;
	अगर (!of_property_पढ़ो_u32(np, "marvell,power-on-delay", &पंचांगp))
		pdata->घातer_on_delay = पंचांगp;
	अगर (!of_property_पढ़ो_u32(np, "marvell,port-mode", &पंचांगp))
		pdata->port_mode = पंचांगp;
	अगर (!of_property_पढ़ो_u32(np, "marvell,power-budget", &पंचांगp))
		pdata->घातer_budget = पंचांगp;

	pdev->dev.platक्रमm_data = pdata;

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक ohci_pxa_of_init(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*-------------------------------------------------------------------------*/

/* configure so an HC device and id are always provided */
/* always called with process context; sleeping is OK */


/**
 * ohci_hcd_pxa27x_probe - initialize pxa27x-based HCDs
 * @pdev:	USB Host controller to probe
 *
 * Context: task context, might sleep
 *
 * Allocates basic resources क्रम this USB host controller, and
 * then invokes the start() method क्रम the HCD associated with it
 * through the hotplug entry's driver_data.
 */
अटल पूर्णांक ohci_hcd_pxa27x_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक retval, irq;
	काष्ठा usb_hcd *hcd;
	काष्ठा pxaohci_platक्रमm_data *inf;
	काष्ठा pxa27x_ohci *pxa_ohci;
	काष्ठा ohci_hcd *ohci;
	काष्ठा resource *r;
	काष्ठा clk *usb_clk;
	अचिन्हित पूर्णांक i;

	retval = ohci_pxa_of_init(pdev);
	अगर (retval)
		वापस retval;

	inf = dev_get_platdata(&pdev->dev);

	अगर (!inf)
		वापस -ENODEV;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		pr_err("no resource of IORESOURCE_IRQ");
		वापस irq;
	पूर्ण

	usb_clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(usb_clk))
		वापस PTR_ERR(usb_clk);

	hcd = usb_create_hcd(&ohci_pxa27x_hc_driver, &pdev->dev, "pxa27x");
	अगर (!hcd)
		वापस -ENOMEM;

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	hcd->regs = devm_ioremap_resource(&pdev->dev, r);
	अगर (IS_ERR(hcd->regs)) अणु
		retval = PTR_ERR(hcd->regs);
		जाओ err;
	पूर्ण
	hcd->rsrc_start = r->start;
	hcd->rsrc_len = resource_size(r);

	/* initialize "struct pxa27x_ohci" */
	pxa_ohci = to_pxa27x_ohci(hcd);
	pxa_ohci->clk = usb_clk;
	pxa_ohci->mmio_base = (व्योम __iomem *)hcd->regs;

	क्रम (i = 0; i < 3; ++i) अणु
		अक्षर name[6];

		अगर (!(inf->flags & (ENABLE_PORT1 << i)))
			जारी;

		प्र_लिखो(name, "vbus%u", i + 1);
		pxa_ohci->vbus[i] = devm_regulator_get(&pdev->dev, name);
	पूर्ण

	retval = pxa27x_start_hc(pxa_ohci, &pdev->dev);
	अगर (retval < 0) अणु
		pr_debug("pxa27x_start_hc failed");
		जाओ err;
	पूर्ण

	/* Select Power Management Mode */
	pxa27x_ohci_select_pmm(pxa_ohci, inf->port_mode);

	अगर (inf->घातer_budget)
		hcd->घातer_budget = inf->घातer_budget;

	/* The value of NDP in roothub_a is incorrect on this hardware */
	ohci = hcd_to_ohci(hcd);
	ohci->num_ports = 3;

	retval = usb_add_hcd(hcd, irq, 0);
	अगर (retval == 0) अणु
		device_wakeup_enable(hcd->self.controller);
		वापस retval;
	पूर्ण

	pxa27x_stop_hc(pxa_ohci, &pdev->dev);
 err:
	usb_put_hcd(hcd);
	वापस retval;
पूर्ण


/* may be called without controller electrically present */
/* may be called with controller, bus, and devices active */

/**
 * ohci_hcd_pxa27x_हटाओ - shutकरोwn processing क्रम pxa27x-based HCDs
 * @pdev: USB Host Controller being हटाओd
 *
 * Context: task context, might sleep
 *
 * Reverses the effect of ohci_hcd_pxa27x_probe(), first invoking
 * the HCD's stop() method.  It is always called from a thपढ़ो
 * context, normally "rmmod", "apmd", or something similar.
 */
अटल पूर्णांक ohci_hcd_pxa27x_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(pdev);
	काष्ठा pxa27x_ohci *pxa_ohci = to_pxa27x_ohci(hcd);
	अचिन्हित पूर्णांक i;

	usb_हटाओ_hcd(hcd);
	pxa27x_stop_hc(pxa_ohci, &pdev->dev);

	क्रम (i = 0; i < 3; ++i)
		pxa27x_ohci_set_vbus_घातer(pxa_ohci, i, false);

	usb_put_hcd(hcd);
	वापस 0;
पूर्ण

/*-------------------------------------------------------------------------*/

#अगर_घोषित CONFIG_PM
अटल पूर्णांक ohci_hcd_pxa27x_drv_suspend(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd *hcd = dev_get_drvdata(dev);
	काष्ठा pxa27x_ohci *pxa_ohci = to_pxa27x_ohci(hcd);
	काष्ठा ohci_hcd *ohci = hcd_to_ohci(hcd);
	bool करो_wakeup = device_may_wakeup(dev);
	पूर्णांक ret;


	अगर (समय_beक्रमe(jअगरfies, ohci->next_statechange))
		msleep(5);
	ohci->next_statechange = jअगरfies;

	ret = ohci_suspend(hcd, करो_wakeup);
	अगर (ret)
		वापस ret;

	pxa27x_stop_hc(pxa_ohci, dev);
	वापस ret;
पूर्ण

अटल पूर्णांक ohci_hcd_pxa27x_drv_resume(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd *hcd = dev_get_drvdata(dev);
	काष्ठा pxa27x_ohci *pxa_ohci = to_pxa27x_ohci(hcd);
	काष्ठा pxaohci_platक्रमm_data *inf = dev_get_platdata(dev);
	काष्ठा ohci_hcd *ohci = hcd_to_ohci(hcd);
	पूर्णांक status;

	अगर (समय_beक्रमe(jअगरfies, ohci->next_statechange))
		msleep(5);
	ohci->next_statechange = jअगरfies;

	status = pxa27x_start_hc(pxa_ohci, dev);
	अगर (status < 0)
		वापस status;

	/* Select Power Management Mode */
	pxa27x_ohci_select_pmm(pxa_ohci, inf->port_mode);

	ohci_resume(hcd, false);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ohci_hcd_pxa27x_pm_ops = अणु
	.suspend	= ohci_hcd_pxa27x_drv_suspend,
	.resume		= ohci_hcd_pxa27x_drv_resume,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver ohci_hcd_pxa27x_driver = अणु
	.probe		= ohci_hcd_pxa27x_probe,
	.हटाओ		= ohci_hcd_pxa27x_हटाओ,
	.shutकरोwn	= usb_hcd_platक्रमm_shutकरोwn,
	.driver		= अणु
		.name	= "pxa27x-ohci",
		.of_match_table = of_match_ptr(pxa_ohci_dt_ids),
#अगर_घोषित CONFIG_PM
		.pm	= &ohci_hcd_pxa27x_pm_ops,
#पूर्ण_अगर
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ohci_driver_overrides pxa27x_overrides __initस्थिर = अणु
	.extra_priv_size =      माप(काष्ठा pxa27x_ohci),
पूर्ण;

अटल पूर्णांक __init ohci_pxa27x_init(व्योम)
अणु
	अगर (usb_disabled())
		वापस -ENODEV;

	pr_info("%s: " DRIVER_DESC "\n", hcd_name);

	ohci_init_driver(&ohci_pxa27x_hc_driver, &pxa27x_overrides);
	ohci_pxa27x_hc_driver.hub_control = pxa27x_ohci_hub_control;

	वापस platक्रमm_driver_रेजिस्टर(&ohci_hcd_pxa27x_driver);
पूर्ण
module_init(ohci_pxa27x_init);

अटल व्योम __निकास ohci_pxa27x_cleanup(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ohci_hcd_pxa27x_driver);
पूर्ण
module_निकास(ohci_pxa27x_cleanup);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:pxa27x-ohci");
