<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * xhci-plat.c - xHCI host controller driver platक्रमm Bus Glue.
 *
 * Copyright (C) 2012 Texas Instruments Incorporated - https://www.ti.com
 * Author: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
 *
 * A lot of code borrowed from the Linux xHCI driver.
 */

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/usb/phy.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>
#समावेश <linux/usb/of.h>

#समावेश "xhci.h"
#समावेश "xhci-plat.h"
#समावेश "xhci-mvebu.h"
#समावेश "xhci-rcar.h"

अटल काष्ठा hc_driver __पढ़ो_mostly xhci_plat_hc_driver;

अटल पूर्णांक xhci_plat_setup(काष्ठा usb_hcd *hcd);
अटल पूर्णांक xhci_plat_start(काष्ठा usb_hcd *hcd);

अटल स्थिर काष्ठा xhci_driver_overrides xhci_plat_overrides __initस्थिर = अणु
	.extra_priv_size = माप(काष्ठा xhci_plat_priv),
	.reset = xhci_plat_setup,
	.start = xhci_plat_start,
पूर्ण;

अटल व्योम xhci_priv_plat_start(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा xhci_plat_priv *priv = hcd_to_xhci_priv(hcd);

	अगर (priv->plat_start)
		priv->plat_start(hcd);
पूर्ण

अटल पूर्णांक xhci_priv_plat_setup(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा xhci_plat_priv *priv = hcd_to_xhci_priv(hcd);

	अगर (!priv->plat_setup)
		वापस 0;

	वापस priv->plat_setup(hcd);
पूर्ण

अटल पूर्णांक xhci_priv_init_quirk(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा xhci_plat_priv *priv = hcd_to_xhci_priv(hcd);

	अगर (!priv->init_quirk)
		वापस 0;

	वापस priv->init_quirk(hcd);
पूर्ण

अटल पूर्णांक xhci_priv_suspend_quirk(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा xhci_plat_priv *priv = hcd_to_xhci_priv(hcd);

	अगर (!priv->suspend_quirk)
		वापस 0;

	वापस priv->suspend_quirk(hcd);
पूर्ण

अटल पूर्णांक xhci_priv_resume_quirk(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा xhci_plat_priv *priv = hcd_to_xhci_priv(hcd);

	अगर (!priv->resume_quirk)
		वापस 0;

	वापस priv->resume_quirk(hcd);
पूर्ण

अटल व्योम xhci_plat_quirks(काष्ठा device *dev, काष्ठा xhci_hcd *xhci)
अणु
	काष्ठा xhci_plat_priv *priv = xhci_to_priv(xhci);

	/*
	 * As of now platक्रमm drivers करोn't provide MSI support so we ensure
	 * here that the generic code करोes not try to make a pci_dev from our
	 * dev काष्ठा in order to setup MSI
	 */
	xhci->quirks |= XHCI_PLAT | priv->quirks;
पूर्ण

/* called during probe() after chip reset completes */
अटल पूर्णांक xhci_plat_setup(काष्ठा usb_hcd *hcd)
अणु
	पूर्णांक ret;


	ret = xhci_priv_init_quirk(hcd);
	अगर (ret)
		वापस ret;

	वापस xhci_gen_setup(hcd, xhci_plat_quirks);
पूर्ण

अटल पूर्णांक xhci_plat_start(काष्ठा usb_hcd *hcd)
अणु
	xhci_priv_plat_start(hcd);
	वापस xhci_run(hcd);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा xhci_plat_priv xhci_plat_marvell_armada = अणु
	.init_quirk = xhci_mvebu_mbus_init_quirk,
पूर्ण;

अटल स्थिर काष्ठा xhci_plat_priv xhci_plat_marvell_armada3700 = अणु
	.plat_setup = xhci_mvebu_a3700_plat_setup,
	.init_quirk = xhci_mvebu_a3700_init_quirk,
पूर्ण;

अटल स्थिर काष्ठा xhci_plat_priv xhci_plat_renesas_rcar_gen2 = अणु
	SET_XHCI_PLAT_PRIV_FOR_RCAR(XHCI_RCAR_FIRMWARE_NAME_V1)
पूर्ण;

अटल स्थिर काष्ठा xhci_plat_priv xhci_plat_renesas_rcar_gen3 = अणु
	SET_XHCI_PLAT_PRIV_FOR_RCAR(XHCI_RCAR_FIRMWARE_NAME_V3)
पूर्ण;

अटल स्थिर काष्ठा xhci_plat_priv xhci_plat_brcm = अणु
	.quirks = XHCI_RESET_ON_RESUME,
पूर्ण;

अटल स्थिर काष्ठा of_device_id usb_xhci_of_match[] = अणु
	अणु
		.compatible = "generic-xhci",
	पूर्ण, अणु
		.compatible = "xhci-platform",
	पूर्ण, अणु
		.compatible = "marvell,armada-375-xhci",
		.data = &xhci_plat_marvell_armada,
	पूर्ण, अणु
		.compatible = "marvell,armada-380-xhci",
		.data = &xhci_plat_marvell_armada,
	पूर्ण, अणु
		.compatible = "marvell,armada3700-xhci",
		.data = &xhci_plat_marvell_armada3700,
	पूर्ण, अणु
		.compatible = "renesas,xhci-r8a7790",
		.data = &xhci_plat_renesas_rcar_gen2,
	पूर्ण, अणु
		.compatible = "renesas,xhci-r8a7791",
		.data = &xhci_plat_renesas_rcar_gen2,
	पूर्ण, अणु
		.compatible = "renesas,xhci-r8a7793",
		.data = &xhci_plat_renesas_rcar_gen2,
	पूर्ण, अणु
		.compatible = "renesas,xhci-r8a7795",
		.data = &xhci_plat_renesas_rcar_gen3,
	पूर्ण, अणु
		.compatible = "renesas,xhci-r8a7796",
		.data = &xhci_plat_renesas_rcar_gen3,
	पूर्ण, अणु
		.compatible = "renesas,rcar-gen2-xhci",
		.data = &xhci_plat_renesas_rcar_gen2,
	पूर्ण, अणु
		.compatible = "renesas,rcar-gen3-xhci",
		.data = &xhci_plat_renesas_rcar_gen3,
	पूर्ण, अणु
		.compatible = "brcm,xhci-brcm-v2",
		.data = &xhci_plat_brcm,
	पूर्ण, अणु
		.compatible = "brcm,bcm7445-xhci",
		.data = &xhci_plat_brcm,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, usb_xhci_of_match);
#पूर्ण_अगर

अटल पूर्णांक xhci_plat_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा xhci_plat_priv *priv_match;
	स्थिर काष्ठा hc_driver	*driver;
	काष्ठा device		*sysdev, *पंचांगpdev;
	काष्ठा xhci_hcd		*xhci;
	काष्ठा resource         *res;
	काष्ठा usb_hcd		*hcd;
	पूर्णांक			ret;
	पूर्णांक			irq;
	काष्ठा xhci_plat_priv	*priv = शून्य;


	अगर (usb_disabled())
		वापस -ENODEV;

	driver = &xhci_plat_hc_driver;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	/*
	 * sysdev must poपूर्णांक to a device that is known to the प्रणाली firmware
	 * or PCI hardware. We handle these three हालs here:
	 * 1. xhci_plat comes from firmware
	 * 2. xhci_plat is child of a device from firmware (dwc3-plat)
	 * 3. xhci_plat is gअक्रमchild of a pci device (dwc3-pci)
	 */
	क्रम (sysdev = &pdev->dev; sysdev; sysdev = sysdev->parent) अणु
		अगर (is_of_node(sysdev->fwnode) ||
			is_acpi_device_node(sysdev->fwnode))
			अवरोध;
#अगर_घोषित CONFIG_PCI
		अन्यथा अगर (sysdev->bus == &pci_bus_type)
			अवरोध;
#पूर्ण_अगर
	पूर्ण

	अगर (!sysdev)
		sysdev = &pdev->dev;

	/* Try to set 64-bit DMA first */
	अगर (WARN_ON(!sysdev->dma_mask))
		/* Platक्रमm did not initialize dma_mask */
		ret = dma_coerce_mask_and_coherent(sysdev,
						   DMA_BIT_MASK(64));
	अन्यथा
		ret = dma_set_mask_and_coherent(sysdev, DMA_BIT_MASK(64));

	/* If seting 64-bit DMA mask fails, fall back to 32-bit DMA mask */
	अगर (ret) अणु
		ret = dma_set_mask_and_coherent(sysdev, DMA_BIT_MASK(32));
		अगर (ret)
			वापस ret;
	पूर्ण

	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_get_noresume(&pdev->dev);

	hcd = __usb_create_hcd(driver, sysdev, &pdev->dev,
			       dev_name(&pdev->dev), शून्य);
	अगर (!hcd) अणु
		ret = -ENOMEM;
		जाओ disable_runसमय;
	पूर्ण

	hcd->regs = devm_platक्रमm_get_and_ioremap_resource(pdev, 0, &res);
	अगर (IS_ERR(hcd->regs)) अणु
		ret = PTR_ERR(hcd->regs);
		जाओ put_hcd;
	पूर्ण

	hcd->rsrc_start = res->start;
	hcd->rsrc_len = resource_size(res);

	xhci = hcd_to_xhci(hcd);

	/*
	 * Not all platक्रमms have clks so it is not an error अगर the
	 * घड़ी करो not exist.
	 */
	xhci->reg_clk = devm_clk_get_optional(&pdev->dev, "reg");
	अगर (IS_ERR(xhci->reg_clk)) अणु
		ret = PTR_ERR(xhci->reg_clk);
		जाओ put_hcd;
	पूर्ण

	ret = clk_prepare_enable(xhci->reg_clk);
	अगर (ret)
		जाओ put_hcd;

	xhci->clk = devm_clk_get_optional(&pdev->dev, शून्य);
	अगर (IS_ERR(xhci->clk)) अणु
		ret = PTR_ERR(xhci->clk);
		जाओ disable_reg_clk;
	पूर्ण

	ret = clk_prepare_enable(xhci->clk);
	अगर (ret)
		जाओ disable_reg_clk;

	अगर (pdev->dev.of_node)
		priv_match = of_device_get_match_data(&pdev->dev);
	अन्यथा
		priv_match = dev_get_platdata(&pdev->dev);

	अगर (priv_match) अणु
		priv = hcd_to_xhci_priv(hcd);
		/* Just copy data क्रम now */
		*priv = *priv_match;
	पूर्ण

	device_set_wakeup_capable(&pdev->dev, true);

	xhci->मुख्य_hcd = hcd;
	xhci->shared_hcd = __usb_create_hcd(driver, sysdev, &pdev->dev,
			dev_name(&pdev->dev), hcd);
	अगर (!xhci->shared_hcd) अणु
		ret = -ENOMEM;
		जाओ disable_clk;
	पूर्ण

	/* imod_पूर्णांकerval is the पूर्णांकerrupt moderation value in nanoseconds. */
	xhci->imod_पूर्णांकerval = 40000;

	/* Iterate over all parent nodes क्रम finding quirks */
	क्रम (पंचांगpdev = &pdev->dev; पंचांगpdev; पंचांगpdev = पंचांगpdev->parent) अणु

		अगर (device_property_पढ़ो_bool(पंचांगpdev, "usb2-lpm-disable"))
			xhci->quirks |= XHCI_HW_LPM_DISABLE;

		अगर (device_property_पढ़ो_bool(पंचांगpdev, "usb3-lpm-capable"))
			xhci->quirks |= XHCI_LPM_SUPPORT;

		अगर (device_property_पढ़ो_bool(पंचांगpdev, "quirk-broken-port-ped"))
			xhci->quirks |= XHCI_BROKEN_PORT_PED;

		device_property_पढ़ो_u32(पंचांगpdev, "imod-interval-ns",
					 &xhci->imod_पूर्णांकerval);
	पूर्ण

	hcd->usb_phy = devm_usb_get_phy_by_phandle(sysdev, "usb-phy", 0);
	अगर (IS_ERR(hcd->usb_phy)) अणु
		ret = PTR_ERR(hcd->usb_phy);
		अगर (ret == -EPROBE_DEFER)
			जाओ put_usb3_hcd;
		hcd->usb_phy = शून्य;
	पूर्ण अन्यथा अणु
		ret = usb_phy_init(hcd->usb_phy);
		अगर (ret)
			जाओ put_usb3_hcd;
	पूर्ण

	hcd->tpl_support = of_usb_host_tpl_support(sysdev->of_node);
	xhci->shared_hcd->tpl_support = hcd->tpl_support;

	अगर (priv) अणु
		ret = xhci_priv_plat_setup(hcd);
		अगर (ret)
			जाओ disable_usb_phy;
	पूर्ण

	अगर ((xhci->quirks & XHCI_SKIP_PHY_INIT) || (priv && (priv->quirks & XHCI_SKIP_PHY_INIT)))
		hcd->skip_phy_initialization = 1;

	अगर (priv && (priv->quirks & XHCI_SG_TRB_CACHE_SIZE_QUIRK))
		xhci->quirks |= XHCI_SG_TRB_CACHE_SIZE_QUIRK;

	ret = usb_add_hcd(hcd, irq, IRQF_SHARED);
	अगर (ret)
		जाओ disable_usb_phy;

	अगर (HCC_MAX_PSA(xhci->hcc_params) >= 4)
		xhci->shared_hcd->can_करो_streams = 1;

	ret = usb_add_hcd(xhci->shared_hcd, irq, IRQF_SHARED);
	अगर (ret)
		जाओ dealloc_usb2_hcd;

	device_enable_async_suspend(&pdev->dev);
	pm_runसमय_put_noidle(&pdev->dev);

	/*
	 * Prevent runसमय pm from being on as शेष, users should enable
	 * runसमय pm using घातer/control in sysfs.
	 */
	pm_runसमय_क्रमbid(&pdev->dev);

	वापस 0;


dealloc_usb2_hcd:
	usb_हटाओ_hcd(hcd);

disable_usb_phy:
	usb_phy_shutकरोwn(hcd->usb_phy);

put_usb3_hcd:
	usb_put_hcd(xhci->shared_hcd);

disable_clk:
	clk_disable_unprepare(xhci->clk);

disable_reg_clk:
	clk_disable_unprepare(xhci->reg_clk);

put_hcd:
	usb_put_hcd(hcd);

disable_runसमय:
	pm_runसमय_put_noidle(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक xhci_plat_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा usb_hcd	*hcd = platक्रमm_get_drvdata(dev);
	काष्ठा xhci_hcd	*xhci = hcd_to_xhci(hcd);
	काष्ठा clk *clk = xhci->clk;
	काष्ठा clk *reg_clk = xhci->reg_clk;
	काष्ठा usb_hcd *shared_hcd = xhci->shared_hcd;

	pm_runसमय_get_sync(&dev->dev);
	xhci->xhc_state |= XHCI_STATE_REMOVING;

	usb_हटाओ_hcd(shared_hcd);
	xhci->shared_hcd = शून्य;
	usb_phy_shutकरोwn(hcd->usb_phy);

	usb_हटाओ_hcd(hcd);
	usb_put_hcd(shared_hcd);

	clk_disable_unprepare(clk);
	clk_disable_unprepare(reg_clk);
	usb_put_hcd(hcd);

	pm_runसमय_disable(&dev->dev);
	pm_runसमय_put_noidle(&dev->dev);
	pm_runसमय_set_suspended(&dev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused xhci_plat_suspend(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd	*hcd = dev_get_drvdata(dev);
	काष्ठा xhci_hcd	*xhci = hcd_to_xhci(hcd);
	पूर्णांक ret;

	ret = xhci_priv_suspend_quirk(hcd);
	अगर (ret)
		वापस ret;
	/*
	 * xhci_suspend() needs `करो_wakeup` to know whether host is allowed
	 * to करो wakeup during suspend.
	 */
	वापस xhci_suspend(xhci, device_may_wakeup(dev));
पूर्ण

अटल पूर्णांक __maybe_unused xhci_plat_resume(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd	*hcd = dev_get_drvdata(dev);
	काष्ठा xhci_hcd	*xhci = hcd_to_xhci(hcd);
	पूर्णांक ret;

	ret = xhci_priv_resume_quirk(hcd);
	अगर (ret)
		वापस ret;

	ret = xhci_resume(xhci, 0);
	अगर (ret)
		वापस ret;

	pm_runसमय_disable(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused xhci_plat_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd  *hcd = dev_get_drvdata(dev);
	काष्ठा xhci_hcd *xhci = hcd_to_xhci(hcd);
	पूर्णांक ret;

	ret = xhci_priv_suspend_quirk(hcd);
	अगर (ret)
		वापस ret;

	वापस xhci_suspend(xhci, true);
पूर्ण

अटल पूर्णांक __maybe_unused xhci_plat_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd  *hcd = dev_get_drvdata(dev);
	काष्ठा xhci_hcd *xhci = hcd_to_xhci(hcd);

	वापस xhci_resume(xhci, 0);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops xhci_plat_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(xhci_plat_suspend, xhci_plat_resume)

	SET_RUNTIME_PM_OPS(xhci_plat_runसमय_suspend,
			   xhci_plat_runसमय_resume,
			   शून्य)
पूर्ण;

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id usb_xhci_acpi_match[] = अणु
	/* XHCI-compliant USB Controller */
	अणु "PNP0D10", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, usb_xhci_acpi_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver usb_xhci_driver = अणु
	.probe	= xhci_plat_probe,
	.हटाओ	= xhci_plat_हटाओ,
	.shutकरोwn = usb_hcd_platक्रमm_shutकरोwn,
	.driver	= अणु
		.name = "xhci-hcd",
		.pm = &xhci_plat_pm_ops,
		.of_match_table = of_match_ptr(usb_xhci_of_match),
		.acpi_match_table = ACPI_PTR(usb_xhci_acpi_match),
	पूर्ण,
पूर्ण;
MODULE_ALIAS("platform:xhci-hcd");

अटल पूर्णांक __init xhci_plat_init(व्योम)
अणु
	xhci_init_driver(&xhci_plat_hc_driver, &xhci_plat_overrides);
	वापस platक्रमm_driver_रेजिस्टर(&usb_xhci_driver);
पूर्ण
module_init(xhci_plat_init);

अटल व्योम __निकास xhci_plat_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&usb_xhci_driver);
पूर्ण
module_निकास(xhci_plat_निकास);

MODULE_DESCRIPTION("xHCI Platform Host Controller Driver");
MODULE_LICENSE("GPL");
