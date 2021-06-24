<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
* Driver क्रम EHCI HCD on SPEAr SOC
*
* Copyright (C) 2010 ST Micro Electronics,
* Deepak Sikri <deepak.sikri@st.com>
*
* Based on various ehci-*.c drivers
*/

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>

#समावेश "ehci.h"

#घोषणा DRIVER_DESC "EHCI SPEAr driver"

अटल स्थिर अक्षर hcd_name[] = "SPEAr-ehci";

काष्ठा spear_ehci अणु
	काष्ठा clk *clk;
पूर्ण;

#घोषणा to_spear_ehci(hcd)	(काष्ठा spear_ehci *)(hcd_to_ehci(hcd)->priv)

अटल काष्ठा hc_driver __पढ़ो_mostly ehci_spear_hc_driver;

अटल पूर्णांक __maybe_unused ehci_spear_drv_suspend(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd *hcd = dev_get_drvdata(dev);
	bool करो_wakeup = device_may_wakeup(dev);

	वापस ehci_suspend(hcd, करो_wakeup);
पूर्ण

अटल पूर्णांक __maybe_unused ehci_spear_drv_resume(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd *hcd = dev_get_drvdata(dev);

	ehci_resume(hcd, false);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ehci_spear_pm_ops, ehci_spear_drv_suspend,
		ehci_spear_drv_resume);

अटल पूर्णांक spear_ehci_hcd_drv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_hcd *hcd ;
	काष्ठा spear_ehci *sehci;
	काष्ठा resource *res;
	काष्ठा clk *usbh_clk;
	स्थिर काष्ठा hc_driver *driver = &ehci_spear_hc_driver;
	पूर्णांक irq, retval;

	अगर (usb_disabled())
		वापस -ENODEV;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		retval = irq;
		जाओ fail;
	पूर्ण

	/*
	 * Right now device-tree probed devices करोn't get dma_mask set.
	 * Since shared usb code relies on it, set it here क्रम now.
	 * Once we have dma capability bindings this can go away.
	 */
	retval = dma_coerce_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (retval)
		जाओ fail;

	usbh_clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(usbh_clk)) अणु
		dev_err(&pdev->dev, "Error getting interface clock\n");
		retval = PTR_ERR(usbh_clk);
		जाओ fail;
	पूर्ण

	hcd = usb_create_hcd(driver, &pdev->dev, dev_name(&pdev->dev));
	अगर (!hcd) अणु
		retval = -ENOMEM;
		जाओ fail;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	hcd->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(hcd->regs)) अणु
		retval = PTR_ERR(hcd->regs);
		जाओ err_put_hcd;
	पूर्ण
	hcd->rsrc_start = res->start;
	hcd->rsrc_len = resource_size(res);

	sehci = to_spear_ehci(hcd);
	sehci->clk = usbh_clk;

	/* रेजिस्टरs start at offset 0x0 */
	hcd_to_ehci(hcd)->caps = hcd->regs;

	clk_prepare_enable(sehci->clk);
	retval = usb_add_hcd(hcd, irq, IRQF_SHARED);
	अगर (retval)
		जाओ err_stop_ehci;

	device_wakeup_enable(hcd->self.controller);
	वापस retval;

err_stop_ehci:
	clk_disable_unprepare(sehci->clk);
err_put_hcd:
	usb_put_hcd(hcd);
fail:
	dev_err(&pdev->dev, "init fail, %d\n", retval);

	वापस retval ;
पूर्ण

अटल पूर्णांक spear_ehci_hcd_drv_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(pdev);
	काष्ठा spear_ehci *sehci = to_spear_ehci(hcd);

	usb_हटाओ_hcd(hcd);

	अगर (sehci->clk)
		clk_disable_unprepare(sehci->clk);
	usb_put_hcd(hcd);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id spear_ehci_id_table[] = अणु
	अणु .compatible = "st,spear600-ehci", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, spear_ehci_id_table);

अटल काष्ठा platक्रमm_driver spear_ehci_hcd_driver = अणु
	.probe		= spear_ehci_hcd_drv_probe,
	.हटाओ		= spear_ehci_hcd_drv_हटाओ,
	.shutकरोwn	= usb_hcd_platक्रमm_shutकरोwn,
	.driver		= अणु
		.name = "spear-ehci",
		.bus = &platक्रमm_bus_type,
		.pm = pm_ptr(&ehci_spear_pm_ops),
		.of_match_table = spear_ehci_id_table,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ehci_driver_overrides spear_overrides __initस्थिर = अणु
	.extra_priv_size = माप(काष्ठा spear_ehci),
पूर्ण;

अटल पूर्णांक __init ehci_spear_init(व्योम)
अणु
	अगर (usb_disabled())
		वापस -ENODEV;

	pr_info("%s: " DRIVER_DESC "\n", hcd_name);

	ehci_init_driver(&ehci_spear_hc_driver, &spear_overrides);
	वापस platक्रमm_driver_रेजिस्टर(&spear_ehci_hcd_driver);
पूर्ण
module_init(ehci_spear_init);

अटल व्योम __निकास ehci_spear_cleanup(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&spear_ehci_hcd_driver);
पूर्ण
module_निकास(ehci_spear_cleanup);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_ALIAS("platform:spear-ehci");
MODULE_AUTHOR("Deepak Sikri");
MODULE_LICENSE("GPL");
