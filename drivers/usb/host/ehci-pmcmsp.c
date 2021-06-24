<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PMC MSP EHCI (Host Controller Driver) क्रम USB.
 *
 * (C) Copyright 2006-2010 PMC-Sierra Inc
 */

/* includes */
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/usb.h>
#समावेश <msp_usb.h>

/* stream disable*/
#घोषणा USB_CTRL_MODE_STREAM_DISABLE	0x10

/* threshold */
#घोषणा USB_CTRL_FIFO_THRESH		0x00300000

/* रेजिस्टर offset क्रम usb_mode */
#घोषणा USB_EHCI_REG_USB_MODE		0x68

/* रेजिस्टर offset क्रम usb fअगरo */
#घोषणा USB_EHCI_REG_USB_FIFO		0x24

/* रेजिस्टर offset क्रम usb status */
#घोषणा USB_EHCI_REG_USB_STATUS		0x44

/* serial/parallel transceiver */
#घोषणा USB_EHCI_REG_BIT_STAT_STS	(1<<29)

/* TWI USB0 host device pin */
#घोषणा MSP_PIN_USB0_HOST_DEV		49

/* TWI USB1 host device pin */
#घोषणा MSP_PIN_USB1_HOST_DEV		50


अटल व्योम usb_hcd_tdi_set_mode(काष्ठा ehci_hcd *ehci)
अणु
	u8 *base;
	u8 *statreg;
	u8 *fअगरoreg;
	u32 val;
	काष्ठा ehci_regs *reg_base = ehci->regs;

	/* get रेजिस्टर base */
	base = (u8 *)reg_base + USB_EHCI_REG_USB_MODE;
	statreg = (u8 *)reg_base + USB_EHCI_REG_USB_STATUS;
	fअगरoreg = (u8 *)reg_base + USB_EHCI_REG_USB_FIFO;

	/* Disable controller mode stream */
	val = ehci_पढ़ोl(ehci, (u32 *)base);
	ehci_ग_लिखोl(ehci, (val | USB_CTRL_MODE_STREAM_DISABLE),
			(u32 *)base);

	/* clear STS to select parallel transceiver पूर्णांकerface */
	val = ehci_पढ़ोl(ehci, (u32 *)statreg);
	val = val & ~USB_EHCI_REG_BIT_STAT_STS;
	ehci_ग_लिखोl(ehci, val, (u32 *)statreg);

	/* ग_लिखो to set the proper fअगरo threshold */
	ehci_ग_लिखोl(ehci, USB_CTRL_FIFO_THRESH, (u32 *)fअगरoreg);

	/* set TWI GPIO USB_HOST_DEV pin high */
	gpio_direction_output(MSP_PIN_USB0_HOST_DEV, 1);
पूर्ण

/* called during probe() after chip reset completes */
अटल पूर्णांक ehci_msp_setup(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ehci_hcd		*ehci = hcd_to_ehci(hcd);
	पूर्णांक			retval;

	ehci->big_endian_mmio = 1;
	ehci->big_endian_desc = 1;

	ehci->caps = hcd->regs;
	hcd->has_tt = 1;

	retval = ehci_setup(hcd);
	अगर (retval)
		वापस retval;

	usb_hcd_tdi_set_mode(ehci);

	वापस retval;
पूर्ण


/* configure so an HC device and id are always provided
 * always called with process context; sleeping is OK
 */

अटल पूर्णांक usb_hcd_msp_map_regs(काष्ठा mspusb_device *dev)
अणु
	काष्ठा resource *res;
	काष्ठा platक्रमm_device *pdev = &dev->dev;
	u32 res_len;
	पूर्णांक retval;

	/* MAB रेजिस्टर space */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (res == शून्य)
		वापस -ENOMEM;
	res_len = resource_size(res);
	अगर (!request_mem_region(res->start, res_len, "mab regs"))
		वापस -EBUSY;

	dev->mab_regs = ioremap(res->start, res_len);
	अगर (dev->mab_regs == शून्य) अणु
		retval = -ENOMEM;
		जाओ err1;
	पूर्ण

	/* MSP USB रेजिस्टर space */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 2);
	अगर (res == शून्य) अणु
		retval = -ENOMEM;
		जाओ err2;
	पूर्ण
	res_len = resource_size(res);
	अगर (!request_mem_region(res->start, res_len, "usbid regs")) अणु
		retval = -EBUSY;
		जाओ err2;
	पूर्ण
	dev->usbid_regs = ioremap(res->start, res_len);
	अगर (dev->usbid_regs == शून्य) अणु
		retval = -ENOMEM;
		जाओ err3;
	पूर्ण

	वापस 0;
err3:
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 2);
	res_len = resource_size(res);
	release_mem_region(res->start, res_len);
err2:
	iounmap(dev->mab_regs);
err1:
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	res_len = resource_size(res);
	release_mem_region(res->start, res_len);
	dev_err(&pdev->dev, "Failed to map non-EHCI regs.\n");
	वापस retval;
पूर्ण

/**
 * usb_hcd_msp_probe - initialize PMC MSP-based HCDs
 * @driver:	Poपूर्णांकer to hc driver instance
 * @dev:	USB controller to probe
 *
 * Context: task context, might sleep
 *
 * Allocates basic resources क्रम this USB host controller, and
 * then invokes the start() method क्रम the HCD associated with it
 * through the hotplug entry's driver_data.
 */
पूर्णांक usb_hcd_msp_probe(स्थिर काष्ठा hc_driver *driver,
			  काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक retval;
	काष्ठा usb_hcd *hcd;
	काष्ठा resource *res;
	काष्ठा ehci_hcd		*ehci ;

	hcd = usb_create_hcd(driver, &dev->dev, "pmcmsp");
	अगर (!hcd)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);
	अगर (res == शून्य) अणु
		pr_debug("No IOMEM resource info for %s.\n", dev->name);
		retval = -ENOMEM;
		जाओ err1;
	पूर्ण
	hcd->rsrc_start = res->start;
	hcd->rsrc_len = resource_size(res);
	अगर (!request_mem_region(hcd->rsrc_start, hcd->rsrc_len, dev->name)) अणु
		retval = -EBUSY;
		जाओ err1;
	पूर्ण
	hcd->regs = ioremap(hcd->rsrc_start, hcd->rsrc_len);
	अगर (!hcd->regs) अणु
		pr_debug("ioremap failed");
		retval = -ENOMEM;
		जाओ err2;
	पूर्ण

	res = platक्रमm_get_resource(dev, IORESOURCE_IRQ, 0);
	अगर (res == शून्य) अणु
		dev_err(&dev->dev, "No IRQ resource info for %s.\n", dev->name);
		retval = -ENOMEM;
		जाओ err3;
	पूर्ण

	/* Map non-EHCI रेजिस्टर spaces */
	retval = usb_hcd_msp_map_regs(to_mspusb_device(dev));
	अगर (retval != 0)
		जाओ err3;

	ehci = hcd_to_ehci(hcd);
	ehci->big_endian_mmio = 1;
	ehci->big_endian_desc = 1;


	retval = usb_add_hcd(hcd, res->start, IRQF_SHARED);
	अगर (retval == 0) अणु
		device_wakeup_enable(hcd->self.controller);
		वापस 0;
	पूर्ण

	usb_हटाओ_hcd(hcd);
err3:
	iounmap(hcd->regs);
err2:
	release_mem_region(hcd->rsrc_start, hcd->rsrc_len);
err1:
	usb_put_hcd(hcd);

	वापस retval;
पूर्ण



/**
 * usb_hcd_msp_हटाओ - shutकरोwn processing क्रम PMC MSP-based HCDs
 * @hcd: USB Host Controller being हटाओd
 *
 * Context: task context, might sleep
 *
 * Reverses the effect of usb_hcd_msp_probe(), first invoking
 * the HCD's stop() method.  It is always called from a thपढ़ो
 * context, normally "rmmod", "apmd", or something similar.
 *
 * may be called without controller electrically present
 * may be called with controller, bus, and devices active
 */
अटल व्योम usb_hcd_msp_हटाओ(काष्ठा usb_hcd *hcd)
अणु
	usb_हटाओ_hcd(hcd);
	iounmap(hcd->regs);
	release_mem_region(hcd->rsrc_start, hcd->rsrc_len);
	usb_put_hcd(hcd);
पूर्ण

अटल स्थिर काष्ठा hc_driver ehci_msp_hc_driver = अणु
	.description =		hcd_name,
	.product_desc =		"PMC MSP EHCI",
	.hcd_priv_size =	माप(काष्ठा ehci_hcd),

	/*
	 * generic hardware linkage
	 */
	.irq =			ehci_irq,
	.flags =		HCD_MEMORY | HCD_DMA | HCD_USB2 | HCD_BH,

	/*
	 * basic lअगरecycle operations
	 */
	.reset			= ehci_msp_setup,
	.shutकरोwn		= ehci_shutकरोwn,
	.start			= ehci_run,
	.stop			= ehci_stop,

	/*
	 * managing i/o requests and associated device resources
	 */
	.urb_enqueue		= ehci_urb_enqueue,
	.urb_dequeue		= ehci_urb_dequeue,
	.endpoपूर्णांक_disable	= ehci_endpoपूर्णांक_disable,
	.endpoपूर्णांक_reset		= ehci_endpoपूर्णांक_reset,

	/*
	 * scheduling support
	 */
	.get_frame_number	= ehci_get_frame,

	/*
	 * root hub support
	 */
	.hub_status_data	= ehci_hub_status_data,
	.hub_control		= ehci_hub_control,
	.bus_suspend		= ehci_bus_suspend,
	.bus_resume		= ehci_bus_resume,
	.relinquish_port	= ehci_relinquish_port,
	.port_handed_over	= ehci_port_handed_over,

	.clear_tt_buffer_complete	= ehci_clear_tt_buffer_complete,
पूर्ण;

अटल पूर्णांक ehci_hcd_msp_drv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	pr_debug("In ehci_hcd_msp_drv_probe");

	अगर (usb_disabled())
		वापस -ENODEV;

	gpio_request(MSP_PIN_USB0_HOST_DEV, "USB0_HOST_DEV_GPIO");

	ret = usb_hcd_msp_probe(&ehci_msp_hc_driver, pdev);

	वापस ret;
पूर्ण

अटल पूर्णांक ehci_hcd_msp_drv_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(pdev);

	usb_hcd_msp_हटाओ(hcd);

	/* मुक्त TWI GPIO USB_HOST_DEV pin */
	gpio_मुक्त(MSP_PIN_USB0_HOST_DEV);

	वापस 0;
पूर्ण

MODULE_ALIAS("pmcmsp-ehci");

अटल काष्ठा platक्रमm_driver ehci_hcd_msp_driver = अणु
	.probe		= ehci_hcd_msp_drv_probe,
	.हटाओ		= ehci_hcd_msp_drv_हटाओ,
	.driver		= अणु
		.name	= "pmcmsp-ehci",
	पूर्ण,
पूर्ण;
