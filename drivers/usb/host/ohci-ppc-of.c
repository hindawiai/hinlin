<शैली गुरु>
// SPDX-License-Identअगरier: GPL-1.0+
/*
 * OHCI HCD (Host Controller Driver) क्रम USB.
 *
 * (C) Copyright 1999 Roman Weissgaerber <weissg@vienna.at>
 * (C) Copyright 2000-2002 David Brownell <dbrownell@users.sourceक्रमge.net>
 * (C) Copyright 2002 Hewlett-Packard Company
 * (C) Copyright 2006 Sylvain Munaut <tnt@246tNt.com>
 *
 * Bus glue क्रम OHCI HC on the of_platक्रमm bus
 *
 * Modअगरied क्रम of_platक्रमm bus from ohci-sa1111.c
 *
 * This file is licenced under the GPL.
 */

#समावेश <linux/संकेत.स>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/prom.h>


अटल पूर्णांक
ohci_ppc_of_start(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ohci_hcd	*ohci = hcd_to_ohci(hcd);
	पूर्णांक		ret;

	अगर ((ret = ohci_init(ohci)) < 0)
		वापस ret;

	अगर ((ret = ohci_run(ohci)) < 0) अणु
		dev_err(hcd->self.controller, "can't start %s\n",
			hcd->self.bus_name);
		ohci_stop(hcd);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hc_driver ohci_ppc_of_hc_driver = अणु
	.description =		hcd_name,
	.product_desc =		"OF OHCI",
	.hcd_priv_size =	माप(काष्ठा ohci_hcd),

	/*
	 * generic hardware linkage
	 */
	.irq =			ohci_irq,
	.flags =		HCD_USB11 | HCD_DMA | HCD_MEMORY,

	/*
	 * basic lअगरecycle operations
	 */
	.start =		ohci_ppc_of_start,
	.stop =			ohci_stop,
	.shutकरोwn = 		ohci_shutकरोwn,

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


अटल पूर्णांक ohci_hcd_ppc_of_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा device_node *dn = op->dev.of_node;
	काष्ठा usb_hcd *hcd;
	काष्ठा ohci_hcd	*ohci;
	काष्ठा resource res;
	पूर्णांक irq;

	पूर्णांक rv;
	पूर्णांक is_bigendian;
	काष्ठा device_node *np;

	अगर (usb_disabled())
		वापस -ENODEV;

	is_bigendian =
		of_device_is_compatible(dn, "ohci-bigendian") ||
		of_device_is_compatible(dn, "ohci-be");

	dev_dbg(&op->dev, "initializing PPC-OF USB Controller\n");

	rv = of_address_to_resource(dn, 0, &res);
	अगर (rv)
		वापस rv;

	hcd = usb_create_hcd(&ohci_ppc_of_hc_driver, &op->dev, "PPC-OF USB");
	अगर (!hcd)
		वापस -ENOMEM;

	hcd->rsrc_start = res.start;
	hcd->rsrc_len = resource_size(&res);

	hcd->regs = devm_ioremap_resource(&op->dev, &res);
	अगर (IS_ERR(hcd->regs)) अणु
		rv = PTR_ERR(hcd->regs);
		जाओ err_rmr;
	पूर्ण

	irq = irq_of_parse_and_map(dn, 0);
	अगर (irq == NO_IRQ) अणु
		dev_err(&op->dev, "%s: irq_of_parse_and_map failed\n",
			__खाता__);
		rv = -EBUSY;
		जाओ err_rmr;
	पूर्ण

	ohci = hcd_to_ohci(hcd);
	अगर (is_bigendian) अणु
		ohci->flags |= OHCI_QUIRK_BE_MMIO | OHCI_QUIRK_BE_DESC;
		अगर (of_device_is_compatible(dn, "fsl,mpc5200-ohci"))
			ohci->flags |= OHCI_QUIRK_FRAME_NO;
		अगर (of_device_is_compatible(dn, "mpc5200-ohci"))
			ohci->flags |= OHCI_QUIRK_FRAME_NO;
	पूर्ण

	ohci_hcd_init(ohci);

	rv = usb_add_hcd(hcd, irq, 0);
	अगर (rv == 0) अणु
		device_wakeup_enable(hcd->self.controller);
		वापस 0;
	पूर्ण

	/* by now, 440epx is known to show usb_23 erratum */
	np = of_find_compatible_node(शून्य, शून्य, "ibm,usb-ehci-440epx");

	/* Work around - At this poपूर्णांक ohci_run has executed, the
	* controller is running, everything, the root ports, etc., is
	* set up.  If the ehci driver is loaded, put the ohci core in
	* the suspended state.  The ehci driver will bring it out of
	* suspended state when / अगर a non-high speed USB device is
	* attached to the USB Host port.  If the ehci driver is not
	* loaded, करो nothing. request_mem_region is used to test अगर
	* the ehci driver is loaded.
	*/
	अगर (np !=  शून्य) अणु
		अगर (!of_address_to_resource(np, 0, &res)) अणु
			अगर (!request_mem_region(res.start, 0x4, hcd_name)) अणु
				ग_लिखोl_be((पढ़ोl_be(&ohci->regs->control) |
					OHCI_USB_SUSPEND), &ohci->regs->control);
					(व्योम) पढ़ोl_be(&ohci->regs->control);
			पूर्ण अन्यथा
				release_mem_region(res.start, 0x4);
		पूर्ण अन्यथा
			pr_debug("%s: cannot get ehci offset from fdt\n", __खाता__);
	पूर्ण

	irq_dispose_mapping(irq);
err_rmr:
 	usb_put_hcd(hcd);

	वापस rv;
पूर्ण

अटल पूर्णांक ohci_hcd_ppc_of_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(op);

	dev_dbg(&op->dev, "stopping PPC-OF USB Controller\n");

	usb_हटाओ_hcd(hcd);

	irq_dispose_mapping(hcd->irq);

	usb_put_hcd(hcd);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ohci_hcd_ppc_of_match[] = अणु
#अगर_घोषित CONFIG_USB_OHCI_HCD_PPC_OF_BE
	अणु
		.name = "usb",
		.compatible = "ohci-bigendian",
	पूर्ण,
	अणु
		.name = "usb",
		.compatible = "ohci-be",
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_USB_OHCI_HCD_PPC_OF_LE
	अणु
		.name = "usb",
		.compatible = "ohci-littledian",
	पूर्ण,
	अणु
		.name = "usb",
		.compatible = "ohci-le",
	पूर्ण,
#पूर्ण_अगर
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ohci_hcd_ppc_of_match);

#अगर	!defined(CONFIG_USB_OHCI_HCD_PPC_OF_BE) && \
	!defined(CONFIG_USB_OHCI_HCD_PPC_OF_LE)
#त्रुटि "No endianness selected for ppc-of-ohci"
#पूर्ण_अगर


अटल काष्ठा platक्रमm_driver ohci_hcd_ppc_of_driver = अणु
	.probe		= ohci_hcd_ppc_of_probe,
	.हटाओ		= ohci_hcd_ppc_of_हटाओ,
	.shutकरोwn	= usb_hcd_platक्रमm_shutकरोwn,
	.driver = अणु
		.name = "ppc-of-ohci",
		.of_match_table = ohci_hcd_ppc_of_match,
	पूर्ण,
पूर्ण;

