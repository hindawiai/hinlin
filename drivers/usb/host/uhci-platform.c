<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Generic UHCI HCD (Host Controller Driver) क्रम Platक्रमm Devices
 *
 * Copyright (c) 2011 Tony Prisk <linux@prisktech.co.nz>
 *
 * This file is based on uhci-grlib.c
 * (C) Copyright 2004-2007 Alan Stern, stern@rowland.harvard.edu
 */

#समावेश <linux/of.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>

अटल पूर्णांक uhci_platक्रमm_init(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा uhci_hcd *uhci = hcd_to_uhci(hcd);

	/* Probe number of ports अगर not alपढ़ोy provided by DT */
	अगर (!uhci->rh_numports)
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

अटल स्थिर काष्ठा hc_driver uhci_platक्रमm_hc_driver = अणु
	.description =		hcd_name,
	.product_desc =		"Generic UHCI Host Controller",
	.hcd_priv_size =	माप(काष्ठा uhci_hcd),

	/* Generic hardware linkage */
	.irq =			uhci_irq,
	.flags =		HCD_MEMORY | HCD_DMA | HCD_USB11,

	/* Basic lअगरecycle operations */
	.reset =		uhci_platक्रमm_init,
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

अटल पूर्णांक uhci_hcd_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा usb_hcd *hcd;
	काष्ठा uhci_hcd	*uhci;
	काष्ठा resource *res;
	पूर्णांक ret;

	अगर (usb_disabled())
		वापस -ENODEV;

	/*
	 * Right now device-tree probed devices करोn't get dma_mask set.
	 * Since shared usb code relies on it, set it here क्रम now.
	 * Once we have dma capability bindings this can go away.
	 */
	ret = dma_coerce_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (ret)
		वापस ret;

	hcd = usb_create_hcd(&uhci_platक्रमm_hc_driver, &pdev->dev,
			pdev->name);
	अगर (!hcd)
		वापस -ENOMEM;

	uhci = hcd_to_uhci(hcd);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	hcd->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(hcd->regs)) अणु
		ret = PTR_ERR(hcd->regs);
		जाओ err_rmr;
	पूर्ण
	hcd->rsrc_start = res->start;
	hcd->rsrc_len = resource_size(res);

	uhci->regs = hcd->regs;

	/* Grab some things from the device-tree */
	अगर (np) अणु
		u32 num_ports;

		अगर (of_property_पढ़ो_u32(np, "#ports", &num_ports) == 0) अणु
			uhci->rh_numports = num_ports;
			dev_info(&pdev->dev,
				"Detected %d ports from device-tree\n",
				num_ports);
		पूर्ण
		अगर (of_device_is_compatible(np, "aspeed,ast2400-uhci") ||
		    of_device_is_compatible(np, "aspeed,ast2500-uhci")) अणु
			uhci->is_aspeed = 1;
			dev_info(&pdev->dev,
				 "Enabled Aspeed implementation workarounds\n");
		पूर्ण
	पूर्ण

	/* Get and enable घड़ी अगर any specअगरied */
	uhci->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(uhci->clk)) अणु
		ret = PTR_ERR(uhci->clk);
		जाओ err_rmr;
	पूर्ण
	ret = clk_prepare_enable(uhci->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Error couldn't enable clock (%d)\n", ret);
		जाओ err_rmr;
	पूर्ण

	ret = usb_add_hcd(hcd, pdev->resource[1].start, IRQF_SHARED);
	अगर (ret)
		जाओ err_clk;

	device_wakeup_enable(hcd->self.controller);
	वापस 0;

err_clk:
	clk_disable_unprepare(uhci->clk);
err_rmr:
	usb_put_hcd(hcd);

	वापस ret;
पूर्ण

अटल पूर्णांक uhci_hcd_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(pdev);
	काष्ठा uhci_hcd *uhci = hcd_to_uhci(hcd);

	clk_disable_unprepare(uhci->clk);
	usb_हटाओ_hcd(hcd);
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
अटल व्योम uhci_hcd_platक्रमm_shutकरोwn(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(op);

	uhci_hc_died(hcd_to_uhci(hcd));
पूर्ण

अटल स्थिर काष्ठा of_device_id platक्रमm_uhci_ids[] = अणु
	अणु .compatible = "generic-uhci", पूर्ण,
	अणु .compatible = "platform-uhci", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, platक्रमm_uhci_ids);

अटल काष्ठा platक्रमm_driver uhci_platक्रमm_driver = अणु
	.probe		= uhci_hcd_platक्रमm_probe,
	.हटाओ		= uhci_hcd_platक्रमm_हटाओ,
	.shutकरोwn	= uhci_hcd_platक्रमm_shutकरोwn,
	.driver = अणु
		.name = "platform-uhci",
		.of_match_table = platक्रमm_uhci_ids,
	पूर्ण,
पूर्ण;
