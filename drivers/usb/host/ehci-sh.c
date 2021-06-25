<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SuperH EHCI host controller driver
 *
 * Copyright (C) 2010  Paul Mundt
 *
 * Based on ohci-sh.c and ehci-aपंचांगel.c.
 */
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>

काष्ठा ehci_sh_priv अणु
	काष्ठा clk *iclk, *fclk;
	काष्ठा usb_hcd *hcd;
पूर्ण;

अटल पूर्णांक ehci_sh_reset(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा ehci_hcd	*ehci = hcd_to_ehci(hcd);

	ehci->caps = hcd->regs;

	वापस ehci_setup(hcd);
पूर्ण

अटल स्थिर काष्ठा hc_driver ehci_sh_hc_driver = अणु
	.description			= hcd_name,
	.product_desc			= "SuperH EHCI",
	.hcd_priv_size			= माप(काष्ठा ehci_hcd),

	/*
	 * generic hardware linkage
	 */
	.irq				= ehci_irq,
	.flags				= HCD_USB2 | HCD_DMA | HCD_MEMORY | HCD_BH,

	/*
	 * basic lअगरecycle operations
	 */
	.reset				= ehci_sh_reset,
	.start				= ehci_run,
	.stop				= ehci_stop,
	.shutकरोwn			= ehci_shutकरोwn,

	/*
	 * managing i/o requests and associated device resources
	 */
	.urb_enqueue			= ehci_urb_enqueue,
	.urb_dequeue			= ehci_urb_dequeue,
	.endpoपूर्णांक_disable		= ehci_endpoपूर्णांक_disable,
	.endpoपूर्णांक_reset			= ehci_endpoपूर्णांक_reset,

	/*
	 * scheduling support
	 */
	.get_frame_number		= ehci_get_frame,

	/*
	 * root hub support
	 */
	.hub_status_data		= ehci_hub_status_data,
	.hub_control			= ehci_hub_control,

#अगर_घोषित CONFIG_PM
	.bus_suspend			= ehci_bus_suspend,
	.bus_resume			= ehci_bus_resume,
#पूर्ण_अगर

	.relinquish_port		= ehci_relinquish_port,
	.port_handed_over		= ehci_port_handed_over,
	.clear_tt_buffer_complete	= ehci_clear_tt_buffer_complete,
पूर्ण;

अटल पूर्णांक ehci_hcd_sh_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा ehci_sh_priv *priv;
	काष्ठा usb_hcd *hcd;
	पूर्णांक irq, ret;

	अगर (usb_disabled())
		वापस -ENODEV;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0) अणु
		ret = -ENODEV;
		जाओ fail_create_hcd;
	पूर्ण

	/* initialize hcd */
	hcd = usb_create_hcd(&ehci_sh_hc_driver, &pdev->dev,
			     dev_name(&pdev->dev));
	अगर (!hcd) अणु
		ret = -ENOMEM;
		जाओ fail_create_hcd;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	hcd->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(hcd->regs)) अणु
		ret = PTR_ERR(hcd->regs);
		जाओ fail_request_resource;
	पूर्ण
	hcd->rsrc_start = res->start;
	hcd->rsrc_len = resource_size(res);

	priv = devm_kzalloc(&pdev->dev, माप(काष्ठा ehci_sh_priv),
			    GFP_KERNEL);
	अगर (!priv) अणु
		ret = -ENOMEM;
		जाओ fail_request_resource;
	पूर्ण

	/* These are optional, we करोn't care अगर they fail */
	priv->fclk = devm_clk_get(&pdev->dev, "usb_fck");
	अगर (IS_ERR(priv->fclk))
		priv->fclk = शून्य;

	priv->iclk = devm_clk_get(&pdev->dev, "usb_ick");
	अगर (IS_ERR(priv->iclk))
		priv->iclk = शून्य;

	clk_enable(priv->fclk);
	clk_enable(priv->iclk);

	ret = usb_add_hcd(hcd, irq, IRQF_SHARED);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "Failed to add hcd");
		जाओ fail_add_hcd;
	पूर्ण
	device_wakeup_enable(hcd->self.controller);

	priv->hcd = hcd;
	platक्रमm_set_drvdata(pdev, priv);

	वापस ret;

fail_add_hcd:
	clk_disable(priv->iclk);
	clk_disable(priv->fclk);

fail_request_resource:
	usb_put_hcd(hcd);
fail_create_hcd:
	dev_err(&pdev->dev, "init %s fail, %d\n", dev_name(&pdev->dev), ret);

	वापस ret;
पूर्ण

अटल पूर्णांक ehci_hcd_sh_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ehci_sh_priv *priv = platक्रमm_get_drvdata(pdev);
	काष्ठा usb_hcd *hcd = priv->hcd;

	usb_हटाओ_hcd(hcd);
	usb_put_hcd(hcd);

	clk_disable(priv->fclk);
	clk_disable(priv->iclk);

	वापस 0;
पूर्ण

अटल व्योम ehci_hcd_sh_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ehci_sh_priv *priv = platक्रमm_get_drvdata(pdev);
	काष्ठा usb_hcd *hcd = priv->hcd;

	अगर (hcd->driver->shutकरोwn)
		hcd->driver->shutकरोwn(hcd);
पूर्ण

अटल काष्ठा platक्रमm_driver ehci_hcd_sh_driver = अणु
	.probe		= ehci_hcd_sh_probe,
	.हटाओ		= ehci_hcd_sh_हटाओ,
	.shutकरोwn	= ehci_hcd_sh_shutकरोwn,
	.driver		= अणु
		.name	= "sh_ehci",
	पूर्ण,
पूर्ण;

MODULE_ALIAS("platform:sh_ehci");
