<शैली गुरु>
// SPDX-License-Identअगरier: GPL-1.0+
/*
 * EHCI HCD (Host Controller Driver) क्रम USB.
 *
 * Bus Glue क्रम PPC On-Chip EHCI driver on the of_platक्रमm bus
 * Tested on AMCC PPC 440EPx
 *
 * Valentine Barshak <vbarshak@ru.mvista.com>
 *
 * Based on "ehci-ppc-soc.c" by Stefan Roese <sr@denx.de>
 * and "ohci-ppc-of.c" by Sylvain Munaut <tnt@246tNt.com>
 *
 * This file is licenced under the GPL.
 */

#समावेश <linux/err.h>
#समावेश <linux/संकेत.स>

#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>


अटल स्थिर काष्ठा hc_driver ehci_ppc_of_hc_driver = अणु
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
	.relinquish_port	= ehci_relinquish_port,
	.port_handed_over	= ehci_port_handed_over,

	.clear_tt_buffer_complete	= ehci_clear_tt_buffer_complete,
पूर्ण;


/*
 * 440EPx Errata USBH_3
 * Fix: Enable Break Memory Transfer (BMT) in INSNREG3
 */
#घोषणा PPC440EPX_EHCI0_INSREG_BMT	(0x1 << 0)
अटल पूर्णांक
ppc44x_enable_bmt(काष्ठा device_node *dn)
अणु
	__iomem u32 *insreg_virt;

	insreg_virt = of_iomap(dn, 1);
	अगर (!insreg_virt)
		वापस  -EINVAL;

	out_be32(insreg_virt + 3, PPC440EPX_EHCI0_INSREG_BMT);

	iounmap(insreg_virt);
	वापस 0;
पूर्ण


अटल पूर्णांक ehci_hcd_ppc_of_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा device_node *dn = op->dev.of_node;
	काष्ठा usb_hcd *hcd;
	काष्ठा ehci_hcd	*ehci = शून्य;
	काष्ठा resource res;
	पूर्णांक irq;
	पूर्णांक rv;

	काष्ठा device_node *np;

	अगर (usb_disabled())
		वापस -ENODEV;

	dev_dbg(&op->dev, "initializing PPC-OF USB Controller\n");

	rv = of_address_to_resource(dn, 0, &res);
	अगर (rv)
		वापस rv;

	hcd = usb_create_hcd(&ehci_ppc_of_hc_driver, &op->dev, "PPC-OF USB");
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
	np = of_find_compatible_node(शून्य, शून्य, "ibm,usb-ohci-440epx");
	अगर (np != शून्य) अणु
		/* claim we really affected by usb23 erratum */
		अगर (!of_address_to_resource(np, 0, &res))
			ehci->ohci_hcctrl_reg =
				devm_ioremap(&op->dev,
					     res.start + OHCI_HCCTRL_OFFSET,
					     OHCI_HCCTRL_LEN);
		अन्यथा
			pr_debug("%s: no ohci offset in fdt\n", __खाता__);
		अगर (!ehci->ohci_hcctrl_reg) अणु
			pr_debug("%s: ioremap for ohci hcctrl failed\n", __खाता__);
		पूर्ण अन्यथा अणु
			ehci->has_amcc_usb23 = 1;
		पूर्ण
	पूर्ण

	अगर (of_get_property(dn, "big-endian", शून्य)) अणु
		ehci->big_endian_mmio = 1;
		ehci->big_endian_desc = 1;
	पूर्ण
	अगर (of_get_property(dn, "big-endian-regs", शून्य))
		ehci->big_endian_mmio = 1;
	अगर (of_get_property(dn, "big-endian-desc", शून्य))
		ehci->big_endian_desc = 1;

	ehci->caps = hcd->regs;

	अगर (of_device_is_compatible(dn, "ibm,usb-ehci-440epx")) अणु
		rv = ppc44x_enable_bmt(dn);
		ehci_dbg(ehci, "Break Memory Transfer (BMT) is %senabled!\n",
				rv ? "NOT ": "");
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


अटल पूर्णांक ehci_hcd_ppc_of_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(op);
	काष्ठा ehci_hcd *ehci = hcd_to_ehci(hcd);

	काष्ठा device_node *np;
	काष्ठा resource res;

	dev_dbg(&op->dev, "stopping PPC-OF USB Controller\n");

	usb_हटाओ_hcd(hcd);

	irq_dispose_mapping(hcd->irq);

	/* use request_mem_region to test अगर the ohci driver is loaded.  अगर so
	 * ensure the ohci core is operational.
	 */
	अगर (ehci->has_amcc_usb23) अणु
		np = of_find_compatible_node(शून्य, शून्य, "ibm,usb-ohci-440epx");
		अगर (np != शून्य) अणु
			अगर (!of_address_to_resource(np, 0, &res))
				अगर (!request_mem_region(res.start,
							    0x4, hcd_name))
					set_ohci_hcfs(ehci, 1);
				अन्यथा
					release_mem_region(res.start, 0x4);
			अन्यथा
				pr_debug("%s: no ohci offset in fdt\n", __खाता__);
			of_node_put(np);
		पूर्ण
	पूर्ण
	usb_put_hcd(hcd);

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा of_device_id ehci_hcd_ppc_of_match[] = अणु
	अणु
		.compatible = "usb-ehci",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ehci_hcd_ppc_of_match);


अटल काष्ठा platक्रमm_driver ehci_hcd_ppc_of_driver = अणु
	.probe		= ehci_hcd_ppc_of_probe,
	.हटाओ		= ehci_hcd_ppc_of_हटाओ,
	.shutकरोwn	= usb_hcd_platक्रमm_shutकरोwn,
	.driver = अणु
		.name = "ppc-of-ehci",
		.of_match_table = ehci_hcd_ppc_of_match,
	पूर्ण,
पूर्ण;
