<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Nuvoton NPCM7xx driver क्रम EHCI HCD
 *
 * Copyright (C) 2018 Nuvoton Technologies,
 * Avi Fishman <avi.fishman@nuvoton.com> <avअगरishman70@gmail.com>
 * Tomer Maimon <tomer.maimon@nuvoton.com> <पंचांगaimon77@gmail.com>
 *
 * Based on various ehci-spear.c driver
 */


#समावेश <linux/dma-mapping.h>

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>

#समावेश "ehci.h"

#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>

#घोषणा DRIVER_DESC "EHCI npcm7xx driver"

अटल स्थिर अक्षर hcd_name[] = "npcm7xx-ehci";

#घोषणा  USB2PHYCTL_OFFSET 0x144

#घोषणा  IPSRST2_OFFSET 0x24
#घोषणा  IPSRST3_OFFSET 0x34


अटल काष्ठा hc_driver __पढ़ो_mostly ehci_npcm7xx_hc_driver;

अटल पूर्णांक __maybe_unused ehci_npcm7xx_drv_suspend(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd *hcd = dev_get_drvdata(dev);
	bool करो_wakeup = device_may_wakeup(dev);

	वापस ehci_suspend(hcd, करो_wakeup);
पूर्ण

अटल पूर्णांक __maybe_unused ehci_npcm7xx_drv_resume(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd *hcd = dev_get_drvdata(dev);

	ehci_resume(hcd, false);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ehci_npcm7xx_pm_ops, ehci_npcm7xx_drv_suspend,
		ehci_npcm7xx_drv_resume);

अटल पूर्णांक npcm7xx_ehci_hcd_drv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_hcd *hcd;
	काष्ठा resource *res;
	काष्ठा regmap *gcr_regmap;
	काष्ठा regmap *rst_regmap;
	स्थिर काष्ठा hc_driver *driver = &ehci_npcm7xx_hc_driver;
	पूर्णांक irq;
	पूर्णांक retval;

	dev_dbg(&pdev->dev,	"initializing npcm7xx ehci USB Controller\n");

	gcr_regmap = syscon_regmap_lookup_by_compatible("nuvoton,npcm750-gcr");
	अगर (IS_ERR(gcr_regmap)) अणु
		dev_err(&pdev->dev, "%s: failed to find nuvoton,npcm750-gcr\n",
			__func__);
		वापस PTR_ERR(gcr_regmap);
	पूर्ण

	rst_regmap = syscon_regmap_lookup_by_compatible("nuvoton,npcm750-rst");
	अगर (IS_ERR(rst_regmap)) अणु
		dev_err(&pdev->dev, "%s: failed to find nuvoton,npcm750-rst\n",
			__func__);
		वापस PTR_ERR(rst_regmap);
	पूर्ण

	/********* phy init  ******/
	// reset usb host
	regmap_update_bits(rst_regmap, IPSRST2_OFFSET,
			(0x1 << 26), (0x1 << 26));
	regmap_update_bits(rst_regmap, IPSRST3_OFFSET,
			(0x1 << 25), (0x1 << 25));
	regmap_update_bits(gcr_regmap, USB2PHYCTL_OFFSET,
			(0x1 << 28), 0);

	udelay(1);

	// enable phy
	regmap_update_bits(rst_regmap, IPSRST3_OFFSET,
			(0x1 << 25), 0);

	udelay(50); // enable phy

	regmap_update_bits(gcr_regmap, USB2PHYCTL_OFFSET,
			(0x1 << 28), (0x1 << 28));

	// enable host
	regmap_update_bits(rst_regmap, IPSRST2_OFFSET,
			(0x1 << 26), 0);

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

	/* रेजिस्टरs start at offset 0x0 */
	hcd_to_ehci(hcd)->caps = hcd->regs;

	retval = usb_add_hcd(hcd, irq, IRQF_SHARED);
	अगर (retval)
		जाओ err_put_hcd;

	device_wakeup_enable(hcd->self.controller);
	वापस retval;

err_put_hcd:
	usb_put_hcd(hcd);
fail:
	dev_err(&pdev->dev, "init fail, %d\n", retval);

	वापस retval;
पूर्ण

अटल पूर्णांक npcm7xx_ehci_hcd_drv_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(pdev);

	usb_हटाओ_hcd(hcd);

	usb_put_hcd(hcd);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id npcm7xx_ehci_id_table[] = अणु
	अणु .compatible = "nuvoton,npcm750-ehci" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, npcm7xx_ehci_id_table);

अटल काष्ठा platक्रमm_driver npcm7xx_ehci_hcd_driver = अणु
	.probe		= npcm7xx_ehci_hcd_drv_probe,
	.हटाओ		= npcm7xx_ehci_hcd_drv_हटाओ,
	.shutकरोwn	= usb_hcd_platक्रमm_shutकरोwn,
	.driver		= अणु
		.name = "npcm7xx-ehci",
		.bus = &platक्रमm_bus_type,
		.pm = pm_ptr(&ehci_npcm7xx_pm_ops),
		.of_match_table = npcm7xx_ehci_id_table,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init ehci_npcm7xx_init(व्योम)
अणु
	अगर (usb_disabled())
		वापस -ENODEV;

	pr_info("%s: " DRIVER_DESC "\n", hcd_name);

	ehci_init_driver(&ehci_npcm7xx_hc_driver, शून्य);
	वापस platक्रमm_driver_रेजिस्टर(&npcm7xx_ehci_hcd_driver);
पूर्ण
module_init(ehci_npcm7xx_init);

अटल व्योम __निकास ehci_npcm7xx_cleanup(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&npcm7xx_ehci_hcd_driver);
पूर्ण
module_निकास(ehci_npcm7xx_cleanup);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_ALIAS("platform:npcm7xx-ehci");
MODULE_AUTHOR("Avi Fishman");
MODULE_LICENSE("GPL v2");
