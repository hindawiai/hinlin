<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Generic platक्रमm ohci driver
 *
 * Copyright 2007 Michael Buesch <m@bues.ch>
 * Copyright 2011-2012 Hauke Mehrtens <hauke@hauke-m.de>
 * Copyright 2014 Hans de Goede <hdegoede@redhat.com>
 *
 * Derived from the OCHI-SSB driver
 * Derived from the OHCI-PCI driver
 * Copyright 1999 Roman Weissgaerber
 * Copyright 2000-2002 David Brownell
 * Copyright 1999 Linus Torvalds
 * Copyright 1999 Gregory P. Smith
 */

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>
#समावेश <linux/usb/ohci_pdriver.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>

#समावेश "ohci.h"

#घोषणा DRIVER_DESC "OHCI generic platform driver"
#घोषणा OHCI_MAX_CLKS 3
#घोषणा hcd_to_ohci_priv(h) ((काष्ठा ohci_platक्रमm_priv *)hcd_to_ohci(h)->priv)

काष्ठा ohci_platक्रमm_priv अणु
	काष्ठा clk *clks[OHCI_MAX_CLKS];
	काष्ठा reset_control *resets;
पूर्ण;

अटल स्थिर अक्षर hcd_name[] = "ohci-platform";

अटल पूर्णांक ohci_platक्रमm_घातer_on(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(dev);
	काष्ठा ohci_platक्रमm_priv *priv = hcd_to_ohci_priv(hcd);
	पूर्णांक clk, ret;

	क्रम (clk = 0; clk < OHCI_MAX_CLKS && priv->clks[clk]; clk++) अणु
		ret = clk_prepare_enable(priv->clks[clk]);
		अगर (ret)
			जाओ err_disable_clks;
	पूर्ण

	वापस 0;

err_disable_clks:
	जबतक (--clk >= 0)
		clk_disable_unprepare(priv->clks[clk]);

	वापस ret;
पूर्ण

अटल व्योम ohci_platक्रमm_घातer_off(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(dev);
	काष्ठा ohci_platक्रमm_priv *priv = hcd_to_ohci_priv(hcd);
	पूर्णांक clk;

	क्रम (clk = OHCI_MAX_CLKS - 1; clk >= 0; clk--)
		अगर (priv->clks[clk])
			clk_disable_unprepare(priv->clks[clk]);
पूर्ण

अटल काष्ठा hc_driver __पढ़ो_mostly ohci_platक्रमm_hc_driver;

अटल स्थिर काष्ठा ohci_driver_overrides platक्रमm_overrides __initस्थिर = अणु
	.product_desc =		"Generic Platform OHCI controller",
	.extra_priv_size =	माप(काष्ठा ohci_platक्रमm_priv),
पूर्ण;

अटल काष्ठा usb_ohci_pdata ohci_platक्रमm_शेषs = अणु
	.घातer_on =		ohci_platक्रमm_घातer_on,
	.घातer_suspend =	ohci_platक्रमm_घातer_off,
	.घातer_off =		ohci_platक्रमm_घातer_off,
पूर्ण;

अटल पूर्णांक ohci_platक्रमm_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा usb_hcd *hcd;
	काष्ठा resource *res_mem;
	काष्ठा usb_ohci_pdata *pdata = dev_get_platdata(&dev->dev);
	काष्ठा ohci_platक्रमm_priv *priv;
	काष्ठा ohci_hcd *ohci;
	पूर्णांक err, irq, clk = 0;

	अगर (usb_disabled())
		वापस -ENODEV;

	/*
	 * Use reasonable शेषs so platक्रमms करोn't have to provide these
	 * with DT probing on ARM.
	 */
	अगर (!pdata)
		pdata = &ohci_platक्रमm_शेषs;

	err = dma_coerce_mask_and_coherent(&dev->dev, DMA_BIT_MASK(32));
	अगर (err)
		वापस err;

	irq = platक्रमm_get_irq(dev, 0);
	अगर (irq < 0)
		वापस irq;

	hcd = usb_create_hcd(&ohci_platक्रमm_hc_driver, &dev->dev,
			dev_name(&dev->dev));
	अगर (!hcd)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(dev, hcd);
	dev->dev.platक्रमm_data = pdata;
	priv = hcd_to_ohci_priv(hcd);
	ohci = hcd_to_ohci(hcd);

	अगर (pdata == &ohci_platक्रमm_शेषs && dev->dev.of_node) अणु
		अगर (of_property_पढ़ो_bool(dev->dev.of_node, "big-endian-regs"))
			ohci->flags |= OHCI_QUIRK_BE_MMIO;

		अगर (of_property_पढ़ो_bool(dev->dev.of_node, "big-endian-desc"))
			ohci->flags |= OHCI_QUIRK_BE_DESC;

		अगर (of_property_पढ़ो_bool(dev->dev.of_node, "big-endian"))
			ohci->flags |= OHCI_QUIRK_BE_MMIO | OHCI_QUIRK_BE_DESC;

		अगर (of_property_पढ़ो_bool(dev->dev.of_node, "no-big-frame-no"))
			ohci->flags |= OHCI_QUIRK_FRAME_NO;

		अगर (of_property_पढ़ो_bool(dev->dev.of_node,
					  "remote-wakeup-connected"))
			ohci->hc_control = OHCI_CTRL_RWC;

		of_property_पढ़ो_u32(dev->dev.of_node, "num-ports",
				     &ohci->num_ports);

		क्रम (clk = 0; clk < OHCI_MAX_CLKS; clk++) अणु
			priv->clks[clk] = of_clk_get(dev->dev.of_node, clk);
			अगर (IS_ERR(priv->clks[clk])) अणु
				err = PTR_ERR(priv->clks[clk]);
				अगर (err == -EPROBE_DEFER)
					जाओ err_put_clks;
				priv->clks[clk] = शून्य;
				अवरोध;
			पूर्ण
		पूर्ण

		priv->resets = devm_reset_control_array_get_optional_shared(
								&dev->dev);
		अगर (IS_ERR(priv->resets)) अणु
			err = PTR_ERR(priv->resets);
			जाओ err_put_clks;
		पूर्ण

		err = reset_control_deनिश्चित(priv->resets);
		अगर (err)
			जाओ err_put_clks;
	पूर्ण

	अगर (pdata->big_endian_desc)
		ohci->flags |= OHCI_QUIRK_BE_DESC;
	अगर (pdata->big_endian_mmio)
		ohci->flags |= OHCI_QUIRK_BE_MMIO;
	अगर (pdata->no_big_frame_no)
		ohci->flags |= OHCI_QUIRK_FRAME_NO;
	अगर (pdata->num_ports)
		ohci->num_ports = pdata->num_ports;

#अगर_अघोषित CONFIG_USB_OHCI_BIG_ENDIAN_MMIO
	अगर (ohci->flags & OHCI_QUIRK_BE_MMIO) अणु
		dev_err(&dev->dev,
			"Error: CONFIG_USB_OHCI_BIG_ENDIAN_MMIO not set\n");
		err = -EINVAL;
		जाओ err_reset;
	पूर्ण
#पूर्ण_अगर
#अगर_अघोषित CONFIG_USB_OHCI_BIG_ENDIAN_DESC
	अगर (ohci->flags & OHCI_QUIRK_BE_DESC) अणु
		dev_err(&dev->dev,
			"Error: CONFIG_USB_OHCI_BIG_ENDIAN_DESC not set\n");
		err = -EINVAL;
		जाओ err_reset;
	पूर्ण
#पूर्ण_अगर

	pm_runसमय_set_active(&dev->dev);
	pm_runसमय_enable(&dev->dev);
	अगर (pdata->घातer_on) अणु
		err = pdata->घातer_on(dev);
		अगर (err < 0)
			जाओ err_reset;
	पूर्ण

	res_mem = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);
	hcd->regs = devm_ioremap_resource(&dev->dev, res_mem);
	अगर (IS_ERR(hcd->regs)) अणु
		err = PTR_ERR(hcd->regs);
		जाओ err_घातer;
	पूर्ण
	hcd->rsrc_start = res_mem->start;
	hcd->rsrc_len = resource_size(res_mem);

	err = usb_add_hcd(hcd, irq, IRQF_SHARED);
	अगर (err)
		जाओ err_घातer;

	device_wakeup_enable(hcd->self.controller);

	platक्रमm_set_drvdata(dev, hcd);

	वापस err;

err_घातer:
	अगर (pdata->घातer_off)
		pdata->घातer_off(dev);
err_reset:
	pm_runसमय_disable(&dev->dev);
	reset_control_निश्चित(priv->resets);
err_put_clks:
	जबतक (--clk >= 0)
		clk_put(priv->clks[clk]);

	अगर (pdata == &ohci_platक्रमm_शेषs)
		dev->dev.platक्रमm_data = शून्य;

	usb_put_hcd(hcd);

	वापस err;
पूर्ण

अटल पूर्णांक ohci_platक्रमm_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(dev);
	काष्ठा usb_ohci_pdata *pdata = dev_get_platdata(&dev->dev);
	काष्ठा ohci_platक्रमm_priv *priv = hcd_to_ohci_priv(hcd);
	पूर्णांक clk;

	pm_runसमय_get_sync(&dev->dev);
	usb_हटाओ_hcd(hcd);

	अगर (pdata->घातer_off)
		pdata->घातer_off(dev);

	reset_control_निश्चित(priv->resets);

	क्रम (clk = 0; clk < OHCI_MAX_CLKS && priv->clks[clk]; clk++)
		clk_put(priv->clks[clk]);

	usb_put_hcd(hcd);

	pm_runसमय_put_sync(&dev->dev);
	pm_runसमय_disable(&dev->dev);

	अगर (pdata == &ohci_platक्रमm_शेषs)
		dev->dev.platक्रमm_data = शून्य;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक ohci_platक्रमm_suspend(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd *hcd = dev_get_drvdata(dev);
	काष्ठा usb_ohci_pdata *pdata = dev->platक्रमm_data;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	bool करो_wakeup = device_may_wakeup(dev);
	पूर्णांक ret;

	ret = ohci_suspend(hcd, करो_wakeup);
	अगर (ret)
		वापस ret;

	अगर (pdata->घातer_suspend)
		pdata->घातer_suspend(pdev);

	वापस ret;
पूर्ण

अटल पूर्णांक ohci_platक्रमm_resume(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd *hcd = dev_get_drvdata(dev);
	काष्ठा usb_ohci_pdata *pdata = dev_get_platdata(dev);
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);

	अगर (pdata->घातer_on) अणु
		पूर्णांक err = pdata->घातer_on(pdev);
		अगर (err < 0)
			वापस err;
	पूर्ण

	ohci_resume(hcd, false);

	pm_runसमय_disable(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा of_device_id ohci_platक्रमm_ids[] = अणु
	अणु .compatible = "generic-ohci", पूर्ण,
	अणु .compatible = "cavium,octeon-6335-ohci", पूर्ण,
	अणु .compatible = "ti,ohci-omap3", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ohci_platक्रमm_ids);

अटल स्थिर काष्ठा platक्रमm_device_id ohci_platक्रमm_table[] = अणु
	अणु "ohci-platform", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, ohci_platक्रमm_table);

अटल SIMPLE_DEV_PM_OPS(ohci_platक्रमm_pm_ops, ohci_platक्रमm_suspend,
	ohci_platक्रमm_resume);

अटल काष्ठा platक्रमm_driver ohci_platक्रमm_driver = अणु
	.id_table	= ohci_platक्रमm_table,
	.probe		= ohci_platक्रमm_probe,
	.हटाओ		= ohci_platक्रमm_हटाओ,
	.shutकरोwn	= usb_hcd_platक्रमm_shutकरोwn,
	.driver		= अणु
		.name	= "ohci-platform",
		.pm	= &ohci_platक्रमm_pm_ops,
		.of_match_table = ohci_platक्रमm_ids,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init ohci_platक्रमm_init(व्योम)
अणु
	अगर (usb_disabled())
		वापस -ENODEV;

	pr_info("%s: " DRIVER_DESC "\n", hcd_name);

	ohci_init_driver(&ohci_platक्रमm_hc_driver, &platक्रमm_overrides);
	वापस platक्रमm_driver_रेजिस्टर(&ohci_platक्रमm_driver);
पूर्ण
module_init(ohci_platक्रमm_init);

अटल व्योम __निकास ohci_platक्रमm_cleanup(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ohci_platक्रमm_driver);
पूर्ण
module_निकास(ohci_platक्रमm_cleanup);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR("Hauke Mehrtens");
MODULE_AUTHOR("Alan Stern");
MODULE_LICENSE("GPL");
