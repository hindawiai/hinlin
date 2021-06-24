<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम EHCI UHP on Aपंचांगel chips
 *
 *  Copyright (C) 2009 Aपंचांगel Corporation,
 *                     Nicolas Ferre <nicolas.ferre@aपंचांगel.com>
 *
 *  Based on various ehci-*.c drivers
 */

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>

#समावेश "ehci.h"

#घोषणा DRIVER_DESC "EHCI Atmel driver"

अटल स्थिर अक्षर hcd_name[] = "ehci-atmel";

/* पूर्णांकerface and function घड़ीs */
#घोषणा hcd_to_aपंचांगel_ehci_priv(h) \
	((काष्ठा aपंचांगel_ehci_priv *)hcd_to_ehci(h)->priv)

काष्ठा aपंचांगel_ehci_priv अणु
	काष्ठा clk *iclk;
	काष्ठा clk *uclk;
	bool घड़ीed;
पूर्ण;

अटल काष्ठा hc_driver __पढ़ो_mostly ehci_aपंचांगel_hc_driver;

अटल स्थिर काष्ठा ehci_driver_overrides ehci_aपंचांगel_drv_overrides __initस्थिर = अणु
	.extra_priv_size = माप(काष्ठा aपंचांगel_ehci_priv),
पूर्ण;

/*-------------------------------------------------------------------------*/

अटल व्योम aपंचांगel_start_घड़ी(काष्ठा aपंचांगel_ehci_priv *aपंचांगel_ehci)
अणु
	अगर (aपंचांगel_ehci->घड़ीed)
		वापस;

	clk_prepare_enable(aपंचांगel_ehci->uclk);
	clk_prepare_enable(aपंचांगel_ehci->iclk);
	aपंचांगel_ehci->घड़ीed = true;
पूर्ण

अटल व्योम aपंचांगel_stop_घड़ी(काष्ठा aपंचांगel_ehci_priv *aपंचांगel_ehci)
अणु
	अगर (!aपंचांगel_ehci->घड़ीed)
		वापस;

	clk_disable_unprepare(aपंचांगel_ehci->iclk);
	clk_disable_unprepare(aपंचांगel_ehci->uclk);
	aपंचांगel_ehci->घड़ीed = false;
पूर्ण

अटल व्योम aपंचांगel_start_ehci(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(pdev);
	काष्ठा aपंचांगel_ehci_priv *aपंचांगel_ehci = hcd_to_aपंचांगel_ehci_priv(hcd);

	dev_dbg(&pdev->dev, "start\n");
	aपंचांगel_start_घड़ी(aपंचांगel_ehci);
पूर्ण

अटल व्योम aपंचांगel_stop_ehci(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(pdev);
	काष्ठा aपंचांगel_ehci_priv *aपंचांगel_ehci = hcd_to_aपंचांगel_ehci_priv(hcd);

	dev_dbg(&pdev->dev, "stop\n");
	aपंचांगel_stop_घड़ी(aपंचांगel_ehci);
पूर्ण

/*-------------------------------------------------------------------------*/

अटल पूर्णांक ehci_aपंचांगel_drv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_hcd *hcd;
	स्थिर काष्ठा hc_driver *driver = &ehci_aपंचांगel_hc_driver;
	काष्ठा resource *res;
	काष्ठा ehci_hcd *ehci;
	काष्ठा aपंचांगel_ehci_priv *aपंचांगel_ehci;
	पूर्णांक irq;
	पूर्णांक retval;

	अगर (usb_disabled())
		वापस -ENODEV;

	pr_debug("Initializing Atmel-SoC USB Host Controller\n");

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0) अणु
		retval = -ENODEV;
		जाओ fail_create_hcd;
	पूर्ण

	/* Right now device-tree probed devices करोn't get dma_mask set.
	 * Since shared usb code relies on it, set it here क्रम now.
	 * Once we have dma capability bindings this can go away.
	 */
	retval = dma_coerce_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (retval)
		जाओ fail_create_hcd;

	hcd = usb_create_hcd(driver, &pdev->dev, dev_name(&pdev->dev));
	अगर (!hcd) अणु
		retval = -ENOMEM;
		जाओ fail_create_hcd;
	पूर्ण
	aपंचांगel_ehci = hcd_to_aपंचांगel_ehci_priv(hcd);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	hcd->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(hcd->regs)) अणु
		retval = PTR_ERR(hcd->regs);
		जाओ fail_request_resource;
	पूर्ण

	hcd->rsrc_start = res->start;
	hcd->rsrc_len = resource_size(res);

	aपंचांगel_ehci->iclk = devm_clk_get(&pdev->dev, "ehci_clk");
	अगर (IS_ERR(aपंचांगel_ehci->iclk)) अणु
		dev_err(&pdev->dev, "Error getting interface clock\n");
		retval = -ENOENT;
		जाओ fail_request_resource;
	पूर्ण

	aपंचांगel_ehci->uclk = devm_clk_get(&pdev->dev, "usb_clk");
	अगर (IS_ERR(aपंचांगel_ehci->uclk)) अणु
		dev_err(&pdev->dev, "failed to get uclk\n");
		retval = PTR_ERR(aपंचांगel_ehci->uclk);
		जाओ fail_request_resource;
	पूर्ण

	ehci = hcd_to_ehci(hcd);
	/* रेजिस्टरs start at offset 0x0 */
	ehci->caps = hcd->regs;

	aपंचांगel_start_ehci(pdev);

	retval = usb_add_hcd(hcd, irq, IRQF_SHARED);
	अगर (retval)
		जाओ fail_add_hcd;
	device_wakeup_enable(hcd->self.controller);

	वापस retval;

fail_add_hcd:
	aपंचांगel_stop_ehci(pdev);
fail_request_resource:
	usb_put_hcd(hcd);
fail_create_hcd:
	dev_err(&pdev->dev, "init %s fail, %d\n",
		dev_name(&pdev->dev), retval);

	वापस retval;
पूर्ण

अटल पूर्णांक ehci_aपंचांगel_drv_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(pdev);

	usb_हटाओ_hcd(hcd);
	usb_put_hcd(hcd);

	aपंचांगel_stop_ehci(pdev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ehci_aपंचांगel_drv_suspend(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd *hcd = dev_get_drvdata(dev);
	काष्ठा aपंचांगel_ehci_priv *aपंचांगel_ehci = hcd_to_aपंचांगel_ehci_priv(hcd);
	पूर्णांक ret;

	ret = ehci_suspend(hcd, false);
	अगर (ret)
		वापस ret;

	aपंचांगel_stop_घड़ी(aपंचांगel_ehci);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ehci_aपंचांगel_drv_resume(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd *hcd = dev_get_drvdata(dev);
	काष्ठा aपंचांगel_ehci_priv *aपंचांगel_ehci = hcd_to_aपंचांगel_ehci_priv(hcd);

	aपंचांगel_start_घड़ी(aपंचांगel_ehci);
	ehci_resume(hcd, false);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id aपंचांगel_ehci_dt_ids[] = अणु
	अणु .compatible = "atmel,at91sam9g45-ehci" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, aपंचांगel_ehci_dt_ids);
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(ehci_aपंचांगel_pm_ops, ehci_aपंचांगel_drv_suspend,
					ehci_aपंचांगel_drv_resume);

अटल काष्ठा platक्रमm_driver ehci_aपंचांगel_driver = अणु
	.probe		= ehci_aपंचांगel_drv_probe,
	.हटाओ		= ehci_aपंचांगel_drv_हटाओ,
	.shutकरोwn	= usb_hcd_platक्रमm_shutकरोwn,
	.driver		= अणु
		.name	= "atmel-ehci",
		.pm	= &ehci_aपंचांगel_pm_ops,
		.of_match_table	= of_match_ptr(aपंचांगel_ehci_dt_ids),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ehci_aपंचांगel_init(व्योम)
अणु
	अगर (usb_disabled())
		वापस -ENODEV;

	pr_info("%s: " DRIVER_DESC "\n", hcd_name);
	ehci_init_driver(&ehci_aपंचांगel_hc_driver, &ehci_aपंचांगel_drv_overrides);
	वापस platक्रमm_driver_रेजिस्टर(&ehci_aपंचांगel_driver);
पूर्ण
module_init(ehci_aपंचांगel_init);

अटल व्योम __निकास ehci_aपंचांगel_cleanup(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ehci_aपंचांगel_driver);
पूर्ण
module_निकास(ehci_aपंचांगel_cleanup);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_ALIAS("platform:atmel-ehci");
MODULE_AUTHOR("Nicolas Ferre");
MODULE_LICENSE("GPL");
