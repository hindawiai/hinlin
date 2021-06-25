<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
* OHCI HCD (Host Controller Driver) क्रम USB.
*
* Copyright (C) 2010 ST Microelectronics.
* Deepak Sikri<deepak.sikri@st.com>
*
* Based on various ohci-*.c drivers
*/

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>

#समावेश "ohci.h"

#घोषणा DRIVER_DESC "OHCI SPEAr driver"

अटल स्थिर अक्षर hcd_name[] = "SPEAr-ohci";
काष्ठा spear_ohci अणु
	काष्ठा clk *clk;
पूर्ण;

#घोषणा to_spear_ohci(hcd)     (काष्ठा spear_ohci *)(hcd_to_ohci(hcd)->priv)

अटल काष्ठा hc_driver __पढ़ो_mostly ohci_spear_hc_driver;

अटल पूर्णांक spear_ohci_hcd_drv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा hc_driver *driver = &ohci_spear_hc_driver;
	काष्ठा usb_hcd *hcd = शून्य;
	काष्ठा clk *usbh_clk;
	काष्ठा spear_ohci *sohci_p;
	काष्ठा resource *res;
	पूर्णांक retval, irq;

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

	hcd->rsrc_start = pdev->resource[0].start;
	hcd->rsrc_len = resource_size(res);

	sohci_p = to_spear_ohci(hcd);
	sohci_p->clk = usbh_clk;

	clk_prepare_enable(sohci_p->clk);

	retval = usb_add_hcd(hcd, platक्रमm_get_irq(pdev, 0), 0);
	अगर (retval == 0) अणु
		device_wakeup_enable(hcd->self.controller);
		वापस retval;
	पूर्ण

	clk_disable_unprepare(sohci_p->clk);
err_put_hcd:
	usb_put_hcd(hcd);
fail:
	dev_err(&pdev->dev, "init fail, %d\n", retval);

	वापस retval;
पूर्ण

अटल पूर्णांक spear_ohci_hcd_drv_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(pdev);
	काष्ठा spear_ohci *sohci_p = to_spear_ohci(hcd);

	usb_हटाओ_hcd(hcd);
	अगर (sohci_p->clk)
		clk_disable_unprepare(sohci_p->clk);

	usb_put_hcd(hcd);
	वापस 0;
पूर्ण

#अगर defined(CONFIG_PM)
अटल पूर्णांक spear_ohci_hcd_drv_suspend(काष्ठा platक्रमm_device *pdev,
		pm_message_t message)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(pdev);
	काष्ठा ohci_hcd	*ohci = hcd_to_ohci(hcd);
	काष्ठा spear_ohci *sohci_p = to_spear_ohci(hcd);
	bool करो_wakeup = device_may_wakeup(&pdev->dev);
	पूर्णांक ret;

	अगर (समय_beक्रमe(jअगरfies, ohci->next_statechange))
		msleep(5);
	ohci->next_statechange = jअगरfies;

	ret = ohci_suspend(hcd, करो_wakeup);
	अगर (ret)
		वापस ret;

	clk_disable_unprepare(sohci_p->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक spear_ohci_hcd_drv_resume(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(dev);
	काष्ठा ohci_hcd	*ohci = hcd_to_ohci(hcd);
	काष्ठा spear_ohci *sohci_p = to_spear_ohci(hcd);

	अगर (समय_beक्रमe(jअगरfies, ohci->next_statechange))
		msleep(5);
	ohci->next_statechange = jअगरfies;

	clk_prepare_enable(sohci_p->clk);
	ohci_resume(hcd, false);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id spear_ohci_id_table[] = अणु
	अणु .compatible = "st,spear600-ohci", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, spear_ohci_id_table);

/* Driver definition to रेजिस्टर with the platक्रमm bus */
अटल काष्ठा platक्रमm_driver spear_ohci_hcd_driver = अणु
	.probe =	spear_ohci_hcd_drv_probe,
	.हटाओ =	spear_ohci_hcd_drv_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend =	spear_ohci_hcd_drv_suspend,
	.resume =	spear_ohci_hcd_drv_resume,
#पूर्ण_अगर
	.driver = अणु
		.name = "spear-ohci",
		.of_match_table = spear_ohci_id_table,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ohci_driver_overrides spear_overrides __initस्थिर = अणु
	.extra_priv_size = माप(काष्ठा spear_ohci),
पूर्ण;
अटल पूर्णांक __init ohci_spear_init(व्योम)
अणु
	अगर (usb_disabled())
		वापस -ENODEV;

	pr_info("%s: " DRIVER_DESC "\n", hcd_name);

	ohci_init_driver(&ohci_spear_hc_driver, &spear_overrides);
	वापस platक्रमm_driver_रेजिस्टर(&spear_ohci_hcd_driver);
पूर्ण
module_init(ohci_spear_init);

अटल व्योम __निकास ohci_spear_cleanup(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&spear_ohci_hcd_driver);
पूर्ण
module_निकास(ohci_spear_cleanup);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR("Deepak Sikri");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:spear-ohci");
