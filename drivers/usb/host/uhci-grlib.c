<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * UHCI HCD (Host Controller Driver) क्रम GRLIB GRUSBHC
 *
 * Copyright (c) 2011 Jan Andersson <jan@gaisler.com>
 *
 * This file is based on UHCI PCI HCD:
 * (C) Copyright 1999 Linus Torvalds
 * (C) Copyright 1999-2002 Johannes Erdfelt, johannes@erdfelt.com
 * (C) Copyright 1999 Randy Dunlap
 * (C) Copyright 1999 Georg Acher, acher@in.tum.de
 * (C) Copyright 1999 Deti Fliegl, deti@fliegl.de
 * (C) Copyright 1999 Thomas Sailer, sailer@अगरe.ee.ethz.ch
 * (C) Copyright 1999 Roman Weissgaerber, weissg@vienna.at
 * (C) Copyright 2000 Yggdrasil Computing, Inc. (port of new PCI पूर्णांकerface
 *               support from usb-ohci.c by Adam Richter, adam@yggdrasil.com).
 * (C) Copyright 1999 Gregory P. Smith (from usb-ohci.c)
 * (C) Copyright 2004-2007 Alan Stern, stern@rowland.harvard.edu
 */

#समावेश <linux/device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>

अटल पूर्णांक uhci_grlib_init(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा uhci_hcd *uhci = hcd_to_uhci(hcd);

	/*
	 * Probe to determine the endianness of the controller.
	 * We know that bit 7 of the PORTSC1 रेजिस्टर is always set
	 * and bit 15 is always clear.  If uhci_पढ़ोw() yields a value
	 * with bit 7 (0x80) turned on then the current little-endian
	 * setting is correct.  Otherwise we assume the value was
	 * byte-swapped; hence the रेजिस्टर पूर्णांकerface and presumably
	 * also the descriptors are big-endian.
	 */
	अगर (!(uhci_पढ़ोw(uhci, USBPORTSC1) & 0x80)) अणु
		uhci->big_endian_mmio = 1;
		uhci->big_endian_desc = 1;
	पूर्ण

	uhci->rh_numports = uhci_count_ports(hcd);

	/* Set up poपूर्णांकers to to generic functions */
	uhci->reset_hc = uhci_generic_reset_hc;
	uhci->check_and_reset_hc = uhci_generic_check_and_reset_hc;
	/* No special actions need to be taken क्रम the functions below */
	uhci->configure_hc = शून्य;
	uhci->resume_detect_पूर्णांकerrupts_are_broken = शून्य;
	uhci->global_suspend_mode_is_broken = शून्य;

	/* Reset अगर the controller isn't alपढ़ोy safely quiescent. */
	check_and_reset_hc(uhci);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hc_driver uhci_grlib_hc_driver = अणु
	.description =		hcd_name,
	.product_desc =		"GRLIB GRUSBHC UHCI Host Controller",
	.hcd_priv_size =	माप(काष्ठा uhci_hcd),

	/* Generic hardware linkage */
	.irq =			uhci_irq,
	.flags =		HCD_MEMORY | HCD_DMA | HCD_USB11,

	/* Basic lअगरecycle operations */
	.reset =		uhci_grlib_init,
	.start =		uhci_start,
#अगर_घोषित CONFIG_PM
	.pci_suspend =		शून्य,
	.pci_resume =		शून्य,
	.bus_suspend =		uhci_rh_suspend,
	.bus_resume =		uhci_rh_resume,
#पूर्ण_अगर
	.stop =			uhci_stop,

	.urb_enqueue =		uhci_urb_enqueue,
	.urb_dequeue =		uhci_urb_dequeue,

	.endpoपूर्णांक_disable =	uhci_hcd_endpoपूर्णांक_disable,
	.get_frame_number =	uhci_hcd_get_frame_number,

	.hub_status_data =	uhci_hub_status_data,
	.hub_control =		uhci_hub_control,
पूर्ण;


अटल पूर्णांक uhci_hcd_grlib_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा device_node *dn = op->dev.of_node;
	काष्ठा usb_hcd *hcd;
	काष्ठा uhci_hcd	*uhci = शून्य;
	काष्ठा resource res;
	पूर्णांक irq;
	पूर्णांक rv;

	अगर (usb_disabled())
		वापस -ENODEV;

	dev_dbg(&op->dev, "initializing GRUSBHC UHCI USB Controller\n");

	rv = of_address_to_resource(dn, 0, &res);
	अगर (rv)
		वापस rv;

	/* usb_create_hcd requires dma_mask != शून्य */
	op->dev.dma_mask = &op->dev.coherent_dma_mask;
	hcd = usb_create_hcd(&uhci_grlib_hc_driver, &op->dev,
			"GRUSBHC UHCI USB");
	अगर (!hcd)
		वापस -ENOMEM;

	hcd->rsrc_start = res.start;
	hcd->rsrc_len = resource_size(&res);

	irq = irq_of_parse_and_map(dn, 0);
	अगर (irq == NO_IRQ) अणु
		prपूर्णांकk(KERN_ERR "%s: irq_of_parse_and_map failed\n", __खाता__);
		rv = -EBUSY;
		जाओ err_usb;
	पूर्ण

	hcd->regs = devm_ioremap_resource(&op->dev, &res);
	अगर (IS_ERR(hcd->regs)) अणु
		rv = PTR_ERR(hcd->regs);
		जाओ err_irq;
	पूर्ण

	uhci = hcd_to_uhci(hcd);

	uhci->regs = hcd->regs;

	rv = usb_add_hcd(hcd, irq, 0);
	अगर (rv)
		जाओ err_irq;

	device_wakeup_enable(hcd->self.controller);
	वापस 0;

err_irq:
	irq_dispose_mapping(irq);
err_usb:
	usb_put_hcd(hcd);

	वापस rv;
पूर्ण

अटल पूर्णांक uhci_hcd_grlib_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(op);

	dev_dbg(&op->dev, "stopping GRLIB GRUSBHC UHCI USB Controller\n");

	usb_हटाओ_hcd(hcd);

	irq_dispose_mapping(hcd->irq);
	usb_put_hcd(hcd);

	वापस 0;
पूर्ण

/* Make sure the controller is quiescent and that we're not using it
 * any more.  This is मुख्यly क्रम the benefit of programs which, like kexec,
 * expect the hardware to be idle: not करोing DMA or generating IRQs.
 *
 * This routine may be called in a damaged or failing kernel.  Hence we
 * करो not acquire the spinlock beक्रमe shutting करोwn the controller.
 */
अटल व्योम uhci_hcd_grlib_shutकरोwn(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(op);

	uhci_hc_died(hcd_to_uhci(hcd));
पूर्ण

अटल स्थिर काष्ठा of_device_id uhci_hcd_grlib_of_match[] = अणु
	अणु .name = "GAISLER_UHCI", पूर्ण,
	अणु .name = "01_027", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, uhci_hcd_grlib_of_match);


अटल काष्ठा platक्रमm_driver uhci_grlib_driver = अणु
	.probe		= uhci_hcd_grlib_probe,
	.हटाओ		= uhci_hcd_grlib_हटाओ,
	.shutकरोwn	= uhci_hcd_grlib_shutकरोwn,
	.driver = अणु
		.name = "grlib-uhci",
		.of_match_table = uhci_hcd_grlib_of_match,
	पूर्ण,
पूर्ण;
