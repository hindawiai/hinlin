<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * EHCI HCD (Host Controller Driver) क्रम USB.
 *
 * Bus Glue क्रम Xilinx EHCI core on the of_platक्रमm bus
 *
 * Copyright (c) 2009 Xilinx, Inc.
 *
 * Based on "ehci-ppc-of.c" by Valentine Barshak <vbarshak@ru.mvista.com>
 * and "ehci-ppc-soc.c" by Stefan Roese <sr@denx.de>
 * and "ohci-ppc-of.c" by Sylvain Munaut <tnt@246tNt.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/संकेत.स>

#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>

/**
 * ehci_xilinx_port_handed_over - hand the port out अगर failed to enable it
 * @hcd:	Poपूर्णांकer to the usb_hcd device to which the host controller bound
 * @portnum:Port number to which the device is attached.
 *
 * This function is used as a place to tell the user that the Xilinx USB host
 * controller करोes support LS devices. And in an HS only configuration, it
 * करोes not support FS devices either. It is hoped that this can help a
 * confused user.
 *
 * There are हालs when the host controller fails to enable the port due to,
 * क्रम example, insufficient घातer that can be supplied to the device from
 * the USB bus. In those हालs, the messages prपूर्णांकed here are not helpful.
 */
अटल पूर्णांक ehci_xilinx_port_handed_over(काष्ठा usb_hcd *hcd, पूर्णांक portnum)
अणु
	dev_warn(hcd->self.controller, "port %d cannot be enabled\n", portnum);
	अगर (hcd->has_tt) अणु
		dev_warn(hcd->self.controller,
			"Maybe you have connected a low speed device?\n");

		dev_warn(hcd->self.controller,
			"We do not support low speed devices\n");
	पूर्ण अन्यथा अणु
		dev_warn(hcd->self.controller,
			"Maybe your device is not a high speed device?\n");
		dev_warn(hcd->self.controller,
			"The USB host controller does not support full speed "
			"nor low speed devices\n");
		dev_warn(hcd->self.controller,
			"You can reconfigure the host controller to have "
			"full speed support\n");
	पूर्ण

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा hc_driver ehci_xilinx_of_hc_driver = अणु
	.description		= hcd_name,
	.product_desc		= "OF EHCI",
	.hcd_priv_size		= माप(काष्ठा ehci_hcd),

	/*
	 * generic hardware linkage
	 */
	.irq			= ehci_irq,
	.flags			= HCD_MEMORY | HCD_DMA | HCD_USB2 | HCD_BH,

	/*
	 * basic lअगरecycle operations
	 */
	.reset			= ehci_setup,
	.start			= ehci_run,
	.stop			= ehci_stop,
	.shutकरोwn		= ehci_shutकरोwn,

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
#अगर_घोषित	CONFIG_PM
	.bus_suspend		= ehci_bus_suspend,
	.bus_resume		= ehci_bus_resume,
#पूर्ण_अगर
	.relinquish_port	= शून्य,
	.port_handed_over	= ehci_xilinx_port_handed_over,

	.clear_tt_buffer_complete = ehci_clear_tt_buffer_complete,
पूर्ण;

/**
 * ehci_hcd_xilinx_of_probe - Probe method क्रम the USB host controller
 * @op:		poपूर्णांकer to the platक्रमm_device bound to the host controller
 *
 * This function requests resources and sets up appropriate properties क्रम the
 * host controller. Because the Xilinx USB host controller can be configured
 * as HS only or HS/FS only, it checks the configuration in the device tree
 * entry, and sets an appropriate value क्रम hcd->has_tt.
 */
अटल पूर्णांक ehci_hcd_xilinx_of_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा device_node *dn = op->dev.of_node;
	काष्ठा usb_hcd *hcd;
	काष्ठा ehci_hcd	*ehci;
	काष्ठा resource res;
	पूर्णांक irq;
	पूर्णांक rv;
	पूर्णांक *value;

	अगर (usb_disabled())
		वापस -ENODEV;

	dev_dbg(&op->dev, "initializing XILINX-OF USB Controller\n");

	rv = of_address_to_resource(dn, 0, &res);
	अगर (rv)
		वापस rv;

	hcd = usb_create_hcd(&ehci_xilinx_of_hc_driver, &op->dev,
				"XILINX-OF USB");
	अगर (!hcd)
		वापस -ENOMEM;

	hcd->rsrc_start = res.start;
	hcd->rsrc_len = resource_size(&res);

	irq = irq_of_parse_and_map(dn, 0);
	अगर (!irq) अणु
		dev_err(&op->dev, "%s: irq_of_parse_and_map failed\n",
			__खाता__);
		rv = -EBUSY;
		जाओ err_irq;
	पूर्ण

	hcd->regs = devm_ioremap_resource(&op->dev, &res);
	अगर (IS_ERR(hcd->regs)) अणु
		rv = PTR_ERR(hcd->regs);
		जाओ err_irq;
	पूर्ण

	ehci = hcd_to_ehci(hcd);

	/* This core always has big-endian रेजिस्टर पूर्णांकerface and uses
	 * big-endian memory descriptors.
	 */
	ehci->big_endian_mmio = 1;
	ehci->big_endian_desc = 1;

	/* Check whether the FS support option is selected in the hardware.
	 */
	value = (पूर्णांक *)of_get_property(dn, "xlnx,support-usb-fs", शून्य);
	अगर (value && (*value == 1)) अणु
		ehci_dbg(ehci, "USB host controller supports FS devices\n");
		hcd->has_tt = 1;
	पूर्ण अन्यथा अणु
		ehci_dbg(ehci,
			"USB host controller is HS only\n");
		hcd->has_tt = 0;
	पूर्ण

	/* Debug रेजिस्टरs are at the first 0x100 region
	 */
	ehci->caps = hcd->regs + 0x100;

	rv = usb_add_hcd(hcd, irq, 0);
	अगर (rv == 0) अणु
		device_wakeup_enable(hcd->self.controller);
		वापस 0;
	पूर्ण

err_irq:
	usb_put_hcd(hcd);

	वापस rv;
पूर्ण

/**
 * ehci_hcd_xilinx_of_हटाओ - shutकरोwn hcd and release resources
 * @op:		poपूर्णांकer to platक्रमm_device काष्ठाure that is to be हटाओd
 *
 * Remove the hcd काष्ठाure, and release resources that has been requested
 * during probe.
 */
अटल पूर्णांक ehci_hcd_xilinx_of_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(op);

	dev_dbg(&op->dev, "stopping XILINX-OF USB Controller\n");

	usb_हटाओ_hcd(hcd);

	usb_put_hcd(hcd);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ehci_hcd_xilinx_of_match[] = अणु
		अणु.compatible = "xlnx,xps-usb-host-1.00.a",पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ehci_hcd_xilinx_of_match);

अटल काष्ठा platक्रमm_driver ehci_hcd_xilinx_of_driver = अणु
	.probe		= ehci_hcd_xilinx_of_probe,
	.हटाओ		= ehci_hcd_xilinx_of_हटाओ,
	.shutकरोwn	= usb_hcd_platक्रमm_shutकरोwn,
	.driver = अणु
		.name = "xilinx-of-ehci",
		.of_match_table = ehci_hcd_xilinx_of_match,
	पूर्ण,
पूर्ण;
