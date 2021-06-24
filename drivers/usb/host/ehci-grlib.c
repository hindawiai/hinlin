<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम Aeroflex Gaisler GRLIB GRUSBHC EHCI host controller
 *
 * GRUSBHC is typically found on LEON/GRLIB SoCs
 *
 * (c) Jan Andersson <jan@gaisler.com>
 *
 * Based on ehci-ppc-of.c which is:
 * (c) Valentine Barshak <vbarshak@ru.mvista.com>
 * and in turn based on "ehci-ppc-soc.c" by Stefan Roese <sr@denx.de>
 * and "ohci-ppc-of.c" by Sylvain Munaut <tnt@246tNt.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/संकेत.स>

#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>

#घोषणा GRUSBHC_HCIVERSION 0x0100 /* Known value of cap. reg. HCIVERSION */

अटल स्थिर काष्ठा hc_driver ehci_grlib_hc_driver = अणु
	.description		= hcd_name,
	.product_desc		= "GRLIB GRUSBHC EHCI",
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
	.relinquish_port	= ehci_relinquish_port,
	.port_handed_over	= ehci_port_handed_over,

	.clear_tt_buffer_complete	= ehci_clear_tt_buffer_complete,
पूर्ण;


अटल पूर्णांक ehci_hcd_grlib_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा device_node *dn = op->dev.of_node;
	काष्ठा usb_hcd *hcd;
	काष्ठा ehci_hcd	*ehci = शून्य;
	काष्ठा resource res;
	u32 hc_capbase;
	पूर्णांक irq;
	पूर्णांक rv;

	अगर (usb_disabled())
		वापस -ENODEV;

	dev_dbg(&op->dev, "initializing GRUSBHC EHCI USB Controller\n");

	rv = of_address_to_resource(dn, 0, &res);
	अगर (rv)
		वापस rv;

	/* usb_create_hcd requires dma_mask != शून्य */
	op->dev.dma_mask = &op->dev.coherent_dma_mask;
	hcd = usb_create_hcd(&ehci_grlib_hc_driver, &op->dev,
			"GRUSBHC EHCI USB");
	अगर (!hcd)
		वापस -ENOMEM;

	hcd->rsrc_start = res.start;
	hcd->rsrc_len = resource_size(&res);

	irq = irq_of_parse_and_map(dn, 0);
	अगर (irq == NO_IRQ) अणु
		dev_err(&op->dev, "%s: irq_of_parse_and_map failed\n",
			__खाता__);
		rv = -EBUSY;
		जाओ err_irq;
	पूर्ण

	hcd->regs = devm_ioremap_resource(&op->dev, &res);
	अगर (IS_ERR(hcd->regs)) अणु
		rv = PTR_ERR(hcd->regs);
		जाओ err_ioremap;
	पूर्ण

	ehci = hcd_to_ehci(hcd);

	ehci->caps = hcd->regs;

	/* determine endianness of this implementation */
	hc_capbase = ehci_पढ़ोl(ehci, &ehci->caps->hc_capbase);
	अगर (HC_VERSION(ehci, hc_capbase) != GRUSBHC_HCIVERSION) अणु
		ehci->big_endian_mmio = 1;
		ehci->big_endian_desc = 1;
		ehci->big_endian_capbase = 1;
	पूर्ण

	rv = usb_add_hcd(hcd, irq, 0);
	अगर (rv)
		जाओ err_ioremap;

	device_wakeup_enable(hcd->self.controller);
	वापस 0;

err_ioremap:
	irq_dispose_mapping(irq);
err_irq:
	usb_put_hcd(hcd);

	वापस rv;
पूर्ण


अटल पूर्णांक ehci_hcd_grlib_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(op);

	dev_dbg(&op->dev, "stopping GRLIB GRUSBHC EHCI USB Controller\n");

	usb_हटाओ_hcd(hcd);

	irq_dispose_mapping(hcd->irq);

	usb_put_hcd(hcd);

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा of_device_id ehci_hcd_grlib_of_match[] = अणु
	अणु
		.name = "GAISLER_EHCI",
	 पूर्ण,
	अणु
		.name = "01_026",
	 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ehci_hcd_grlib_of_match);


अटल काष्ठा platक्रमm_driver ehci_grlib_driver = अणु
	.probe		= ehci_hcd_grlib_probe,
	.हटाओ		= ehci_hcd_grlib_हटाओ,
	.shutकरोwn	= usb_hcd_platक्रमm_shutकरोwn,
	.driver = अणु
		.name = "grlib-ehci",
		.of_match_table = ehci_hcd_grlib_of_match,
	पूर्ण,
पूर्ण;
