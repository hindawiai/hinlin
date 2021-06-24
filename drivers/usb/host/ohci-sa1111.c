<शैली गुरु>
// SPDX-License-Identअगरier: GPL-1.0+
/*
 * OHCI HCD (Host Controller Driver) क्रम USB.
 *
 * (C) Copyright 1999 Roman Weissgaerber <weissg@vienna.at>
 * (C) Copyright 2000-2002 David Brownell <dbrownell@users.sourceक्रमge.net>
 * (C) Copyright 2002 Hewlett-Packard Company
 *
 * SA1111 Bus Glue
 *
 * Written by Christopher Hoover <ch@hpl.hp.com>
 * Based on fragments of previous driver by Russell King et al.
 *
 * This file is licenced under the GPL.
 */

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/hardware/sa1111.h>

#अगर_अघोषित CONFIG_SA1111
#त्रुटि "This file is SA-1111 bus glue.  CONFIG_SA1111 must be defined."
#पूर्ण_अगर

#घोषणा USB_STATUS	0x0118
#घोषणा USB_RESET	0x011c
#घोषणा USB_IRQTEST	0x0120

#घोषणा USB_RESET_FORCEIFRESET	(1 << 0)
#घोषणा USB_RESET_FORCEHCRESET	(1 << 1)
#घोषणा USB_RESET_CLKGENRESET	(1 << 2)
#घोषणा USB_RESET_SIMSCALEDOWN	(1 << 3)
#घोषणा USB_RESET_USBINTTEST	(1 << 4)
#घोषणा USB_RESET_SLEEPSTBYEN	(1 << 5)
#घोषणा USB_RESET_PWRSENSELOW	(1 << 6)
#घोषणा USB_RESET_PWRCTRLLOW	(1 << 7)

#घोषणा USB_STATUS_IRQHCIRMTWKUP  (1 <<  7)
#घोषणा USB_STATUS_IRQHCIBUFFACC  (1 <<  8)
#घोषणा USB_STATUS_NIRQHCIM       (1 <<  9)
#घोषणा USB_STATUS_NHCIMFCLR      (1 << 10)
#घोषणा USB_STATUS_USBPWRSENSE    (1 << 11)

#अगर 0
अटल व्योम dump_hci_status(काष्ठा usb_hcd *hcd, स्थिर अक्षर *label)
अणु
	अचिन्हित दीर्घ status = पढ़ोl_relaxed(hcd->regs + USB_STATUS);

	prपूर्णांकk(KERN_DEBUG "%s USB_STATUS = { %s%s%s%s%s}\n", label,
	     ((status & USB_STATUS_IRQHCIRMTWKUP) ? "IRQHCIRMTWKUP " : ""),
	     ((status & USB_STATUS_IRQHCIBUFFACC) ? "IRQHCIBUFFACC " : ""),
	     ((status & USB_STATUS_NIRQHCIM) ? "" : "IRQHCIM "),
	     ((status & USB_STATUS_NHCIMFCLR) ? "" : "HCIMFCLR "),
	     ((status & USB_STATUS_USBPWRSENSE) ? "USBPWRSENSE " : ""));
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ohci_sa1111_reset(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ohci_hcd *ohci = hcd_to_ohci(hcd);

	ohci_hcd_init(ohci);
	वापस ohci_init(ohci);
पूर्ण

अटल पूर्णांक ohci_sa1111_start(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ohci_hcd	*ohci = hcd_to_ohci(hcd);
	पूर्णांक ret;

	ret = ohci_run(ohci);
	अगर (ret < 0) अणु
		ohci_err(ohci, "can't start\n");
		ohci_stop(hcd);
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा hc_driver ohci_sa1111_hc_driver = अणु
	.description =		hcd_name,
	.product_desc =		"SA-1111 OHCI",
	.hcd_priv_size =	माप(काष्ठा ohci_hcd),

	/*
	 * generic hardware linkage
	 */
	.irq =			ohci_irq,
	.flags =		HCD_USB11 | HCD_DMA | HCD_MEMORY,

	/*
	 * basic lअगरecycle operations
	 */
	.reset =		ohci_sa1111_reset,
	.start =		ohci_sa1111_start,
	.stop =			ohci_stop,
	.shutकरोwn =		ohci_shutकरोwn,

	/*
	 * managing i/o requests and associated device resources
	 */
	.urb_enqueue =		ohci_urb_enqueue,
	.urb_dequeue =		ohci_urb_dequeue,
	.endpoपूर्णांक_disable =	ohci_endpoपूर्णांक_disable,

	/*
	 * scheduling support
	 */
	.get_frame_number =	ohci_get_frame,

	/*
	 * root hub support
	 */
	.hub_status_data =	ohci_hub_status_data,
	.hub_control =		ohci_hub_control,
#अगर_घोषित	CONFIG_PM
	.bus_suspend =		ohci_bus_suspend,
	.bus_resume =		ohci_bus_resume,
#पूर्ण_अगर
	.start_port_reset =	ohci_start_port_reset,
पूर्ण;

अटल पूर्णांक sa1111_start_hc(काष्ठा sa1111_dev *dev)
अणु
	अचिन्हित पूर्णांक usb_rst = 0;
	पूर्णांक ret;

	dev_dbg(&dev->dev, "starting SA-1111 OHCI USB Controller\n");

	अगर (machine_is_xp860() ||
	    machine_is_assabet() ||
	    machine_is_pfs168() ||
	    machine_is_badge4())
		usb_rst = USB_RESET_PWRSENSELOW | USB_RESET_PWRCTRLLOW;

	/*
	 * Configure the घातer sense and control lines.  Place the USB
	 * host controller in reset.
	 */
	ग_लिखोl_relaxed(usb_rst | USB_RESET_FORCEIFRESET | USB_RESET_FORCEHCRESET,
		      dev->mapbase + USB_RESET);

	/*
	 * Now, carefully enable the USB घड़ी, and take
	 * the USB host controller out of reset.
	 */
	ret = sa1111_enable_device(dev);
	अगर (ret == 0) अणु
		udelay(11);
		ग_लिखोl_relaxed(usb_rst, dev->mapbase + USB_RESET);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम sa1111_stop_hc(काष्ठा sa1111_dev *dev)
अणु
	अचिन्हित पूर्णांक usb_rst;

	dev_dbg(&dev->dev, "stopping SA-1111 OHCI USB Controller\n");

	/*
	 * Put the USB host controller पूर्णांकo reset.
	 */
	usb_rst = पढ़ोl_relaxed(dev->mapbase + USB_RESET);
	ग_लिखोl_relaxed(usb_rst | USB_RESET_FORCEIFRESET | USB_RESET_FORCEHCRESET,
		      dev->mapbase + USB_RESET);

	/*
	 * Stop the USB घड़ी.
	 */
	sa1111_disable_device(dev);
पूर्ण

/**
 * ohci_hcd_sa1111_probe - initialize SA-1111-based HCDs
 *
 * Allocates basic resources क्रम this USB host controller, and
 * then invokes the start() method क्रम the HCD associated with it.
 */
अटल पूर्णांक ohci_hcd_sa1111_probe(काष्ठा sa1111_dev *dev)
अणु
	काष्ठा usb_hcd *hcd;
	पूर्णांक ret, irq;

	अगर (usb_disabled())
		वापस -ENODEV;

	/*
	 * We करोn't call dma_set_mask_and_coherent() here because the
	 * DMA mask has alपढ़ोy been appropraitely setup by the core
	 * SA-1111 bus code (which includes bug workarounds.)
	 */

	hcd = usb_create_hcd(&ohci_sa1111_hc_driver, &dev->dev, "sa1111");
	अगर (!hcd)
		वापस -ENOMEM;

	hcd->rsrc_start = dev->res.start;
	hcd->rsrc_len = resource_size(&dev->res);

	irq = sa1111_get_irq(dev, 1);
	अगर (irq <= 0) अणु
		ret = irq ? : -ENXIO;
		जाओ err1;
	पूर्ण

	अगर (!request_mem_region(hcd->rsrc_start, hcd->rsrc_len, hcd_name)) अणु
		dev_dbg(&dev->dev, "request_mem_region failed\n");
		ret = -EBUSY;
		जाओ err1;
	पूर्ण

	hcd->regs = dev->mapbase;

	ret = sa1111_start_hc(dev);
	अगर (ret)
		जाओ err2;

	ret = usb_add_hcd(hcd, irq, 0);
	अगर (ret == 0) अणु
		device_wakeup_enable(hcd->self.controller);
		वापस ret;
	पूर्ण

	sa1111_stop_hc(dev);
 err2:
	release_mem_region(hcd->rsrc_start, hcd->rsrc_len);
 err1:
	usb_put_hcd(hcd);
	वापस ret;
पूर्ण

/**
 * ohci_hcd_sa1111_हटाओ - shutकरोwn processing क्रम SA-1111-based HCDs
 * @dev: USB Host Controller being हटाओd
 *
 * Reverses the effect of ohci_hcd_sa1111_probe(), first invoking
 * the HCD's stop() method.
 */
अटल व्योम ohci_hcd_sa1111_हटाओ(काष्ठा sa1111_dev *dev)
अणु
	काष्ठा usb_hcd *hcd = sa1111_get_drvdata(dev);

	usb_हटाओ_hcd(hcd);
	sa1111_stop_hc(dev);
	release_mem_region(hcd->rsrc_start, hcd->rsrc_len);
	usb_put_hcd(hcd);
पूर्ण

अटल व्योम ohci_hcd_sa1111_shutकरोwn(काष्ठा device *_dev)
अणु
	काष्ठा sa1111_dev *dev = to_sa1111_device(_dev);
	काष्ठा usb_hcd *hcd = sa1111_get_drvdata(dev);

	अगर (test_bit(HCD_FLAG_HW_ACCESSIBLE, &hcd->flags)) अणु
		hcd->driver->shutकरोwn(hcd);
		sa1111_stop_hc(dev);
	पूर्ण
पूर्ण

अटल काष्ठा sa1111_driver ohci_hcd_sa1111_driver = अणु
	.drv = अणु
		.name	= "sa1111-ohci",
		.owner	= THIS_MODULE,
		.shutकरोwn = ohci_hcd_sa1111_shutकरोwn,
	पूर्ण,
	.devid		= SA1111_DEVID_USB,
	.probe		= ohci_hcd_sa1111_probe,
	.हटाओ		= ohci_hcd_sa1111_हटाओ,
पूर्ण;
