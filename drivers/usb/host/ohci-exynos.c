<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * SAMSUNG EXYNOS USB HOST OHCI Controller
 *
 * Copyright (C) 2011 Samsung Electronics Co.Ltd
 * Author: Jingoo Han <jg1.han@samsung.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>

#समावेश "ohci.h"

#घोषणा DRIVER_DESC "OHCI Exynos driver"

अटल स्थिर अक्षर hcd_name[] = "ohci-exynos";
अटल काष्ठा hc_driver __पढ़ो_mostly exynos_ohci_hc_driver;

#घोषणा to_exynos_ohci(hcd) (काष्ठा exynos_ohci_hcd *)(hcd_to_ohci(hcd)->priv)

#घोषणा PHY_NUMBER 3

काष्ठा exynos_ohci_hcd अणु
	काष्ठा clk *clk;
	काष्ठा device_node *of_node;
	काष्ठा phy *phy[PHY_NUMBER];
	bool legacy_phy;
पूर्ण;

अटल पूर्णांक exynos_ohci_get_phy(काष्ठा device *dev,
				काष्ठा exynos_ohci_hcd *exynos_ohci)
अणु
	काष्ठा device_node *child;
	काष्ठा phy *phy;
	पूर्णांक phy_number, num_phys;
	पूर्णांक ret;

	/* Get PHYs क्रम the controller */
	num_phys = of_count_phandle_with_args(dev->of_node, "phys",
					      "#phy-cells");
	क्रम (phy_number = 0; phy_number < num_phys; phy_number++) अणु
		phy = devm_of_phy_get_by_index(dev, dev->of_node, phy_number);
		अगर (IS_ERR(phy))
			वापस PTR_ERR(phy);
		exynos_ohci->phy[phy_number] = phy;
	पूर्ण
	अगर (num_phys > 0)
		वापस 0;

	/* Get PHYs using legacy bindings */
	क्रम_each_available_child_of_node(dev->of_node, child) अणु
		ret = of_property_पढ़ो_u32(child, "reg", &phy_number);
		अगर (ret) अणु
			dev_err(dev, "Failed to parse device tree\n");
			of_node_put(child);
			वापस ret;
		पूर्ण

		अगर (phy_number >= PHY_NUMBER) अणु
			dev_err(dev, "Invalid number of PHYs\n");
			of_node_put(child);
			वापस -EINVAL;
		पूर्ण

		phy = devm_of_phy_get(dev, child, शून्य);
		exynos_ohci->phy[phy_number] = phy;
		अगर (IS_ERR(phy)) अणु
			ret = PTR_ERR(phy);
			अगर (ret == -EPROBE_DEFER) अणु
				of_node_put(child);
				वापस ret;
			पूर्ण अन्यथा अगर (ret != -ENOSYS && ret != -ENODEV) अणु
				dev_err(dev,
					"Error retrieving usb2 phy: %d\n", ret);
				of_node_put(child);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	exynos_ohci->legacy_phy = true;
	वापस 0;
पूर्ण

अटल पूर्णांक exynos_ohci_phy_enable(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd *hcd = dev_get_drvdata(dev);
	काष्ठा exynos_ohci_hcd *exynos_ohci = to_exynos_ohci(hcd);
	पूर्णांक i;
	पूर्णांक ret = 0;

	क्रम (i = 0; ret == 0 && i < PHY_NUMBER; i++)
		अगर (!IS_ERR(exynos_ohci->phy[i]))
			ret = phy_घातer_on(exynos_ohci->phy[i]);
	अगर (ret)
		क्रम (i--; i >= 0; i--)
			अगर (!IS_ERR(exynos_ohci->phy[i]))
				phy_घातer_off(exynos_ohci->phy[i]);

	वापस ret;
पूर्ण

अटल व्योम exynos_ohci_phy_disable(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd *hcd = dev_get_drvdata(dev);
	काष्ठा exynos_ohci_hcd *exynos_ohci = to_exynos_ohci(hcd);
	पूर्णांक i;

	क्रम (i = 0; i < PHY_NUMBER; i++)
		अगर (!IS_ERR(exynos_ohci->phy[i]))
			phy_घातer_off(exynos_ohci->phy[i]);
पूर्ण

अटल पूर्णांक exynos_ohci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा exynos_ohci_hcd *exynos_ohci;
	काष्ठा usb_hcd *hcd;
	काष्ठा resource *res;
	पूर्णांक irq;
	पूर्णांक err;

	/*
	 * Right now device-tree probed devices करोn't get dma_mask set.
	 * Since shared usb code relies on it, set it here क्रम now.
	 * Once we move to full device tree support this will vanish off.
	 */
	err = dma_coerce_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (err)
		वापस err;

	hcd = usb_create_hcd(&exynos_ohci_hc_driver,
				&pdev->dev, dev_name(&pdev->dev));
	अगर (!hcd) अणु
		dev_err(&pdev->dev, "Unable to create HCD\n");
		वापस -ENOMEM;
	पूर्ण

	exynos_ohci = to_exynos_ohci(hcd);

	err = exynos_ohci_get_phy(&pdev->dev, exynos_ohci);
	अगर (err)
		जाओ fail_clk;

	exynos_ohci->clk = devm_clk_get(&pdev->dev, "usbhost");

	अगर (IS_ERR(exynos_ohci->clk)) अणु
		dev_err(&pdev->dev, "Failed to get usbhost clock\n");
		err = PTR_ERR(exynos_ohci->clk);
		जाओ fail_clk;
	पूर्ण

	err = clk_prepare_enable(exynos_ohci->clk);
	अगर (err)
		जाओ fail_clk;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	hcd->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(hcd->regs)) अणु
		err = PTR_ERR(hcd->regs);
		जाओ fail_io;
	पूर्ण
	hcd->rsrc_start = res->start;
	hcd->rsrc_len = resource_size(res);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		err = irq;
		जाओ fail_io;
	पूर्ण

	platक्रमm_set_drvdata(pdev, hcd);

	err = exynos_ohci_phy_enable(&pdev->dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to enable USB phy\n");
		जाओ fail_io;
	पूर्ण

	/*
	 * Workaround: reset of_node poपूर्णांकer to aव्योम conflict between legacy
	 * Exynos OHCI port subnodes and generic USB device bindings
	 */
	exynos_ohci->of_node = pdev->dev.of_node;
	अगर (exynos_ohci->legacy_phy)
		pdev->dev.of_node = शून्य;

	err = usb_add_hcd(hcd, irq, IRQF_SHARED);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to add USB HCD\n");
		जाओ fail_add_hcd;
	पूर्ण
	device_wakeup_enable(hcd->self.controller);
	वापस 0;

fail_add_hcd:
	exynos_ohci_phy_disable(&pdev->dev);
	pdev->dev.of_node = exynos_ohci->of_node;
fail_io:
	clk_disable_unprepare(exynos_ohci->clk);
fail_clk:
	usb_put_hcd(hcd);
	वापस err;
पूर्ण

अटल पूर्णांक exynos_ohci_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(pdev);
	काष्ठा exynos_ohci_hcd *exynos_ohci = to_exynos_ohci(hcd);

	pdev->dev.of_node = exynos_ohci->of_node;

	usb_हटाओ_hcd(hcd);

	exynos_ohci_phy_disable(&pdev->dev);

	clk_disable_unprepare(exynos_ohci->clk);

	usb_put_hcd(hcd);

	वापस 0;
पूर्ण

अटल व्योम exynos_ohci_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(pdev);

	अगर (hcd->driver->shutकरोwn)
		hcd->driver->shutकरोwn(hcd);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक exynos_ohci_suspend(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd *hcd = dev_get_drvdata(dev);
	काष्ठा exynos_ohci_hcd *exynos_ohci = to_exynos_ohci(hcd);
	bool करो_wakeup = device_may_wakeup(dev);
	पूर्णांक rc = ohci_suspend(hcd, करो_wakeup);

	अगर (rc)
		वापस rc;

	exynos_ohci_phy_disable(dev);

	clk_disable_unprepare(exynos_ohci->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक exynos_ohci_resume(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd *hcd			= dev_get_drvdata(dev);
	काष्ठा exynos_ohci_hcd *exynos_ohci	= to_exynos_ohci(hcd);
	पूर्णांक ret;

	clk_prepare_enable(exynos_ohci->clk);

	ret = exynos_ohci_phy_enable(dev);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable USB phy\n");
		clk_disable_unprepare(exynos_ohci->clk);
		वापस ret;
	पूर्ण

	ohci_resume(hcd, false);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा exynos_ohci_suspend	शून्य
#घोषणा exynos_ohci_resume	शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा ohci_driver_overrides exynos_overrides __initस्थिर = अणु
	.extra_priv_size =	माप(काष्ठा exynos_ohci_hcd),
पूर्ण;

अटल स्थिर काष्ठा dev_pm_ops exynos_ohci_pm_ops = अणु
	.suspend	= exynos_ohci_suspend,
	.resume		= exynos_ohci_resume,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id exynos_ohci_match[] = अणु
	अणु .compatible = "samsung,exynos4210-ohci" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, exynos_ohci_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver exynos_ohci_driver = अणु
	.probe		= exynos_ohci_probe,
	.हटाओ		= exynos_ohci_हटाओ,
	.shutकरोwn	= exynos_ohci_shutकरोwn,
	.driver = अणु
		.name	= "exynos-ohci",
		.pm	= &exynos_ohci_pm_ops,
		.of_match_table	= of_match_ptr(exynos_ohci_match),
	पूर्ण
पूर्ण;
अटल पूर्णांक __init ohci_exynos_init(व्योम)
अणु
	अगर (usb_disabled())
		वापस -ENODEV;

	pr_info("%s: " DRIVER_DESC "\n", hcd_name);
	ohci_init_driver(&exynos_ohci_hc_driver, &exynos_overrides);
	वापस platक्रमm_driver_रेजिस्टर(&exynos_ohci_driver);
पूर्ण
module_init(ohci_exynos_init);

अटल व्योम __निकास ohci_exynos_cleanup(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&exynos_ohci_driver);
पूर्ण
module_निकास(ohci_exynos_cleanup);

MODULE_ALIAS("platform:exynos-ohci");
MODULE_AUTHOR("Jingoo Han <jg1.han@samsung.com>");
MODULE_LICENSE("GPL v2");
