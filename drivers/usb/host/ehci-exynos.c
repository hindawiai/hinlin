<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Samsung Exynos USB HOST EHCI Controller
 *
 * Copyright (C) 2011 Samsung Electronics Co.Ltd
 * Author: Jingoo Han <jg1.han@samsung.com>
 * Author: Joonyoung Shim <jy0922.shim@samsung.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>

#समावेश "ehci.h"

#घोषणा DRIVER_DESC "EHCI Exynos driver"

#घोषणा EHCI_INSNREG00(base)			(base + 0x90)
#घोषणा EHCI_INSNREG00_ENA_INCR16		(0x1 << 25)
#घोषणा EHCI_INSNREG00_ENA_INCR8		(0x1 << 24)
#घोषणा EHCI_INSNREG00_ENA_INCR4		(0x1 << 23)
#घोषणा EHCI_INSNREG00_ENA_INCRX_ALIGN		(0x1 << 22)
#घोषणा EHCI_INSNREG00_ENABLE_DMA_BURST	\
	(EHCI_INSNREG00_ENA_INCR16 | EHCI_INSNREG00_ENA_INCR8 |	\
	 EHCI_INSNREG00_ENA_INCR4 | EHCI_INSNREG00_ENA_INCRX_ALIGN)

अटल स्थिर अक्षर hcd_name[] = "ehci-exynos";
अटल काष्ठा hc_driver __पढ़ो_mostly exynos_ehci_hc_driver;

#घोषणा PHY_NUMBER 3

काष्ठा exynos_ehci_hcd अणु
	काष्ठा clk *clk;
	काष्ठा device_node *of_node;
	काष्ठा phy *phy[PHY_NUMBER];
	bool legacy_phy;
पूर्ण;

#घोषणा to_exynos_ehci(hcd) (काष्ठा exynos_ehci_hcd *)(hcd_to_ehci(hcd)->priv)

अटल पूर्णांक exynos_ehci_get_phy(काष्ठा device *dev,
				काष्ठा exynos_ehci_hcd *exynos_ehci)
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
		exynos_ehci->phy[phy_number] = phy;
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
		exynos_ehci->phy[phy_number] = phy;
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

	exynos_ehci->legacy_phy = true;
	वापस 0;
पूर्ण

अटल पूर्णांक exynos_ehci_phy_enable(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd *hcd = dev_get_drvdata(dev);
	काष्ठा exynos_ehci_hcd *exynos_ehci = to_exynos_ehci(hcd);
	पूर्णांक i;
	पूर्णांक ret = 0;

	क्रम (i = 0; ret == 0 && i < PHY_NUMBER; i++)
		अगर (!IS_ERR(exynos_ehci->phy[i]))
			ret = phy_घातer_on(exynos_ehci->phy[i]);
	अगर (ret)
		क्रम (i--; i >= 0; i--)
			अगर (!IS_ERR(exynos_ehci->phy[i]))
				phy_घातer_off(exynos_ehci->phy[i]);

	वापस ret;
पूर्ण

अटल व्योम exynos_ehci_phy_disable(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd *hcd = dev_get_drvdata(dev);
	काष्ठा exynos_ehci_hcd *exynos_ehci = to_exynos_ehci(hcd);
	पूर्णांक i;

	क्रम (i = 0; i < PHY_NUMBER; i++)
		अगर (!IS_ERR(exynos_ehci->phy[i]))
			phy_घातer_off(exynos_ehci->phy[i]);
पूर्ण

अटल व्योम exynos_setup_vbus_gpio(काष्ठा device *dev)
अणु
	पूर्णांक err;
	पूर्णांक gpio;

	अगर (!dev->of_node)
		वापस;

	gpio = of_get_named_gpio(dev->of_node, "samsung,vbus-gpio", 0);
	अगर (!gpio_is_valid(gpio))
		वापस;

	err = devm_gpio_request_one(dev, gpio, GPIOF_OUT_INIT_HIGH,
				    "ehci_vbus_gpio");
	अगर (err)
		dev_err(dev, "can't request ehci vbus gpio %d", gpio);
पूर्ण

अटल पूर्णांक exynos_ehci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा exynos_ehci_hcd *exynos_ehci;
	काष्ठा usb_hcd *hcd;
	काष्ठा ehci_hcd *ehci;
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

	exynos_setup_vbus_gpio(&pdev->dev);

	hcd = usb_create_hcd(&exynos_ehci_hc_driver,
			     &pdev->dev, dev_name(&pdev->dev));
	अगर (!hcd) अणु
		dev_err(&pdev->dev, "Unable to create HCD\n");
		वापस -ENOMEM;
	पूर्ण
	exynos_ehci = to_exynos_ehci(hcd);

	err = exynos_ehci_get_phy(&pdev->dev, exynos_ehci);
	अगर (err)
		जाओ fail_clk;

	exynos_ehci->clk = devm_clk_get(&pdev->dev, "usbhost");

	अगर (IS_ERR(exynos_ehci->clk)) अणु
		dev_err(&pdev->dev, "Failed to get usbhost clock\n");
		err = PTR_ERR(exynos_ehci->clk);
		जाओ fail_clk;
	पूर्ण

	err = clk_prepare_enable(exynos_ehci->clk);
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

	err = exynos_ehci_phy_enable(&pdev->dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to enable USB phy\n");
		जाओ fail_io;
	पूर्ण

	ehci = hcd_to_ehci(hcd);
	ehci->caps = hcd->regs;

	/*
	 * Workaround: reset of_node poपूर्णांकer to aव्योम conflict between legacy
	 * Exynos EHCI port subnodes and generic USB device bindings
	 */
	exynos_ehci->of_node = pdev->dev.of_node;
	अगर (exynos_ehci->legacy_phy)
		pdev->dev.of_node = शून्य;

	/* DMA burst Enable */
	ग_लिखोl(EHCI_INSNREG00_ENABLE_DMA_BURST, EHCI_INSNREG00(hcd->regs));

	err = usb_add_hcd(hcd, irq, IRQF_SHARED);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to add USB HCD\n");
		जाओ fail_add_hcd;
	पूर्ण
	device_wakeup_enable(hcd->self.controller);

	platक्रमm_set_drvdata(pdev, hcd);

	वापस 0;

fail_add_hcd:
	exynos_ehci_phy_disable(&pdev->dev);
	pdev->dev.of_node = exynos_ehci->of_node;
fail_io:
	clk_disable_unprepare(exynos_ehci->clk);
fail_clk:
	usb_put_hcd(hcd);
	वापस err;
पूर्ण

अटल पूर्णांक exynos_ehci_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(pdev);
	काष्ठा exynos_ehci_hcd *exynos_ehci = to_exynos_ehci(hcd);

	pdev->dev.of_node = exynos_ehci->of_node;

	usb_हटाओ_hcd(hcd);

	exynos_ehci_phy_disable(&pdev->dev);

	clk_disable_unprepare(exynos_ehci->clk);

	usb_put_hcd(hcd);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक exynos_ehci_suspend(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd *hcd = dev_get_drvdata(dev);
	काष्ठा exynos_ehci_hcd *exynos_ehci = to_exynos_ehci(hcd);

	bool करो_wakeup = device_may_wakeup(dev);
	पूर्णांक rc;

	rc = ehci_suspend(hcd, करो_wakeup);
	अगर (rc)
		वापस rc;

	exynos_ehci_phy_disable(dev);

	clk_disable_unprepare(exynos_ehci->clk);

	वापस rc;
पूर्ण

अटल पूर्णांक exynos_ehci_resume(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd *hcd = dev_get_drvdata(dev);
	काष्ठा exynos_ehci_hcd *exynos_ehci = to_exynos_ehci(hcd);
	पूर्णांक ret;

	ret = clk_prepare_enable(exynos_ehci->clk);
	अगर (ret)
		वापस ret;

	ret = exynos_ehci_phy_enable(dev);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable USB phy\n");
		clk_disable_unprepare(exynos_ehci->clk);
		वापस ret;
	पूर्ण

	/* DMA burst Enable */
	ग_लिखोl(EHCI_INSNREG00_ENABLE_DMA_BURST, EHCI_INSNREG00(hcd->regs));

	ehci_resume(hcd, false);
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा exynos_ehci_suspend	शून्य
#घोषणा exynos_ehci_resume	शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops exynos_ehci_pm_ops = अणु
	.suspend	= exynos_ehci_suspend,
	.resume		= exynos_ehci_resume,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id exynos_ehci_match[] = अणु
	अणु .compatible = "samsung,exynos4210-ehci" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, exynos_ehci_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver exynos_ehci_driver = अणु
	.probe		= exynos_ehci_probe,
	.हटाओ		= exynos_ehci_हटाओ,
	.shutकरोwn	= usb_hcd_platक्रमm_shutकरोwn,
	.driver = अणु
		.name	= "exynos-ehci",
		.pm	= &exynos_ehci_pm_ops,
		.of_match_table = of_match_ptr(exynos_ehci_match),
	पूर्ण
पूर्ण;
अटल स्थिर काष्ठा ehci_driver_overrides exynos_overrides __initस्थिर = अणु
	.extra_priv_size = माप(काष्ठा exynos_ehci_hcd),
पूर्ण;

अटल पूर्णांक __init ehci_exynos_init(व्योम)
अणु
	अगर (usb_disabled())
		वापस -ENODEV;

	pr_info("%s: " DRIVER_DESC "\n", hcd_name);
	ehci_init_driver(&exynos_ehci_hc_driver, &exynos_overrides);
	वापस platक्रमm_driver_रेजिस्टर(&exynos_ehci_driver);
पूर्ण
module_init(ehci_exynos_init);

अटल व्योम __निकास ehci_exynos_cleanup(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&exynos_ehci_driver);
पूर्ण
module_निकास(ehci_exynos_cleanup);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_ALIAS("platform:exynos-ehci");
MODULE_AUTHOR("Jingoo Han");
MODULE_AUTHOR("Joonyoung Shim");
MODULE_LICENSE("GPL v2");
