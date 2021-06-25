<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Generic platक्रमm ehci driver
 *
 * Copyright 2007 Steven Brown <sbrown@cortland.com>
 * Copyright 2010-2012 Hauke Mehrtens <hauke@hauke-m.de>
 * Copyright 2014 Hans de Goede <hdegoede@redhat.com>
 *
 * Derived from the ohci-ssb driver
 * Copyright 2007 Michael Buesch <m@bues.ch>
 *
 * Derived from the EHCI-PCI driver
 * Copyright (c) 2000-2004 by David Brownell
 *
 * Derived from the ohci-pci driver
 * Copyright 1999 Roman Weissgaerber
 * Copyright 2000-2002 David Brownell
 * Copyright 1999 Linus Torvalds
 * Copyright 1999 Gregory P. Smith
 */
#समावेश <linux/acpi.h>
#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>
#समावेश <linux/sys_soc.h>
#समावेश <linux/समयr.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/usb/ehci_pdriver.h>
#समावेश <linux/usb/of.h>

#समावेश "ehci.h"

#घोषणा DRIVER_DESC "EHCI generic platform driver"
#घोषणा EHCI_MAX_CLKS 4
#घोषणा hcd_to_ehci_priv(h) ((काष्ठा ehci_platक्रमm_priv *)hcd_to_ehci(h)->priv)

#घोषणा BCM_USB_FIFO_THRESHOLD	0x00800040
#घोषणा bcm_iproc_insnreg01	hostpc[0]

काष्ठा ehci_platक्रमm_priv अणु
	काष्ठा clk *clks[EHCI_MAX_CLKS];
	काष्ठा reset_control *rsts;
	bool reset_on_resume;
	bool quirk_poll;
	काष्ठा समयr_list poll_समयr;
	काष्ठा delayed_work poll_work;
पूर्ण;

अटल स्थिर अक्षर hcd_name[] = "ehci-platform";

अटल पूर्णांक ehci_platक्रमm_reset(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(hcd->self.controller);
	काष्ठा usb_ehci_pdata *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा ehci_hcd *ehci = hcd_to_ehci(hcd);
	पूर्णांक retval;

	ehci->has_synopsys_hc_bug = pdata->has_synopsys_hc_bug;

	अगर (pdata->pre_setup) अणु
		retval = pdata->pre_setup(hcd);
		अगर (retval < 0)
			वापस retval;
	पूर्ण

	ehci->caps = hcd->regs + pdata->caps_offset;
	retval = ehci_setup(hcd);
	अगर (retval)
		वापस retval;

	अगर (pdata->no_io_watchकरोg)
		ehci->need_io_watchकरोg = 0;

	अगर (of_device_is_compatible(pdev->dev.of_node, "brcm,xgs-iproc-ehci"))
		ehci_ग_लिखोl(ehci, BCM_USB_FIFO_THRESHOLD,
			    &ehci->regs->bcm_iproc_insnreg01);

	वापस 0;
पूर्ण

अटल पूर्णांक ehci_platक्रमm_घातer_on(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(dev);
	काष्ठा ehci_platक्रमm_priv *priv = hcd_to_ehci_priv(hcd);
	पूर्णांक clk, ret;

	क्रम (clk = 0; clk < EHCI_MAX_CLKS && priv->clks[clk]; clk++) अणु
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

अटल व्योम ehci_platक्रमm_घातer_off(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(dev);
	काष्ठा ehci_platक्रमm_priv *priv = hcd_to_ehci_priv(hcd);
	पूर्णांक clk;

	क्रम (clk = EHCI_MAX_CLKS - 1; clk >= 0; clk--)
		अगर (priv->clks[clk])
			clk_disable_unprepare(priv->clks[clk]);
पूर्ण

अटल काष्ठा hc_driver __पढ़ो_mostly ehci_platक्रमm_hc_driver;

अटल स्थिर काष्ठा ehci_driver_overrides platक्रमm_overrides __initस्थिर = अणु
	.reset =		ehci_platक्रमm_reset,
	.extra_priv_size =	माप(काष्ठा ehci_platक्रमm_priv),
पूर्ण;

अटल काष्ठा usb_ehci_pdata ehci_platक्रमm_शेषs = अणु
	.घातer_on =		ehci_platक्रमm_घातer_on,
	.घातer_suspend =	ehci_platक्रमm_घातer_off,
	.घातer_off =		ehci_platक्रमm_घातer_off,
पूर्ण;

/**
 * quirk_poll_check_port_status - Poll port_status अगर the device sticks
 * @ehci: the ehci hcd poपूर्णांकer
 *
 * Since EHCI/OHCI controllers on R-Car Gen3 SoCs are possible to be getting
 * stuck very rarely after a full/low usb device was disconnected. To
 * detect such a situation, the controllers require a special way which poll
 * the EHCI PORTSC रेजिस्टर.
 *
 * Return: true अगर the controller's port_status indicated getting stuck
 */
अटल bool quirk_poll_check_port_status(काष्ठा ehci_hcd *ehci)
अणु
	u32 port_status = ehci_पढ़ोl(ehci, &ehci->regs->port_status[0]);

	अगर (!(port_status & PORT_OWNER) &&
	     (port_status & PORT_POWER) &&
	    !(port_status & PORT_CONNECT) &&
	     (port_status & PORT_LS_MASK))
		वापस true;

	वापस false;
पूर्ण

/**
 * quirk_poll_rebind_companion - rebind comanion device to recover
 * @ehci: the ehci hcd poपूर्णांकer
 *
 * Since EHCI/OHCI controllers on R-Car Gen3 SoCs are possible to be getting
 * stuck very rarely after a full/low usb device was disconnected. To
 * recover from such a situation, the controllers require changing the OHCI
 * functional state.
 */
अटल व्योम quirk_poll_rebind_companion(काष्ठा ehci_hcd *ehci)
अणु
	काष्ठा device *companion_dev;
	काष्ठा usb_hcd *hcd = ehci_to_hcd(ehci);

	companion_dev = usb_of_get_companion_dev(hcd->self.controller);
	अगर (!companion_dev)
		वापस;

	device_release_driver(companion_dev);
	अगर (device_attach(companion_dev) < 0)
		ehci_err(ehci, "%s: failed\n", __func__);

	put_device(companion_dev);
पूर्ण

अटल व्योम quirk_poll_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ehci_platक्रमm_priv *priv =
		container_of(to_delayed_work(work), काष्ठा ehci_platक्रमm_priv,
			     poll_work);
	काष्ठा ehci_hcd *ehci = container_of((व्योम *)priv, काष्ठा ehci_hcd,
					     priv);

	/* check the status twice to reduce misdetection rate */
	अगर (!quirk_poll_check_port_status(ehci))
		वापस;
	udelay(10);
	अगर (!quirk_poll_check_port_status(ehci))
		वापस;

	ehci_dbg(ehci, "%s: detected getting stuck. rebind now!\n", __func__);
	quirk_poll_rebind_companion(ehci);
पूर्ण

अटल व्योम quirk_poll_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा ehci_platक्रमm_priv *priv = from_समयr(priv, t, poll_समयr);
	काष्ठा ehci_hcd *ehci = container_of((व्योम *)priv, काष्ठा ehci_hcd,
					     priv);

	अगर (quirk_poll_check_port_status(ehci)) अणु
		/*
		 * Now scheduling the work क्रम testing the port more. Note that
		 * updating the status is possible to be delayed when
		 * reconnection. So, this uses delayed work with 5 ms delay
		 * to aव्योम misdetection.
		 */
		schedule_delayed_work(&priv->poll_work, msecs_to_jअगरfies(5));
	पूर्ण

	mod_समयr(&priv->poll_समयr, jअगरfies + HZ);
पूर्ण

अटल व्योम quirk_poll_init(काष्ठा ehci_platक्रमm_priv *priv)
अणु
	INIT_DELAYED_WORK(&priv->poll_work, quirk_poll_work);
	समयr_setup(&priv->poll_समयr, quirk_poll_समयr, 0);
	mod_समयr(&priv->poll_समयr, jअगरfies + HZ);
पूर्ण

अटल व्योम quirk_poll_end(काष्ठा ehci_platक्रमm_priv *priv)
अणु
	del_समयr_sync(&priv->poll_समयr);
	cancel_delayed_work(&priv->poll_work);
पूर्ण

अटल स्थिर काष्ठा soc_device_attribute quirk_poll_match[] = अणु
	अणु .family = "R-Car Gen3" पूर्ण,
	अणु /* sentinel*/ पूर्ण
पूर्ण;

अटल पूर्णांक ehci_platक्रमm_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा usb_hcd *hcd;
	काष्ठा resource *res_mem;
	काष्ठा usb_ehci_pdata *pdata = dev_get_platdata(&dev->dev);
	काष्ठा ehci_platक्रमm_priv *priv;
	काष्ठा ehci_hcd *ehci;
	पूर्णांक err, irq, clk = 0;

	अगर (usb_disabled())
		वापस -ENODEV;

	/*
	 * Use reasonable शेषs so platक्रमms करोn't have to provide these
	 * with DT probing on ARM.
	 */
	अगर (!pdata)
		pdata = &ehci_platक्रमm_शेषs;

	err = dma_coerce_mask_and_coherent(&dev->dev,
		pdata->dma_mask_64 ? DMA_BIT_MASK(64) : DMA_BIT_MASK(32));
	अगर (err) अणु
		dev_err(&dev->dev, "Error: DMA mask configuration failed\n");
		वापस err;
	पूर्ण

	irq = platक्रमm_get_irq(dev, 0);
	अगर (irq < 0)
		वापस irq;

	hcd = usb_create_hcd(&ehci_platक्रमm_hc_driver, &dev->dev,
			     dev_name(&dev->dev));
	अगर (!hcd)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(dev, hcd);
	dev->dev.platक्रमm_data = pdata;
	priv = hcd_to_ehci_priv(hcd);
	ehci = hcd_to_ehci(hcd);

	अगर (pdata == &ehci_platक्रमm_शेषs && dev->dev.of_node) अणु
		अगर (of_property_पढ़ो_bool(dev->dev.of_node, "big-endian-regs"))
			ehci->big_endian_mmio = 1;

		अगर (of_property_पढ़ो_bool(dev->dev.of_node, "big-endian-desc"))
			ehci->big_endian_desc = 1;

		अगर (of_property_पढ़ो_bool(dev->dev.of_node, "big-endian"))
			ehci->big_endian_mmio = ehci->big_endian_desc = 1;

		अगर (of_property_पढ़ो_bool(dev->dev.of_node, "spurious-oc"))
			ehci->spurious_oc = 1;

		अगर (of_property_पढ़ो_bool(dev->dev.of_node,
					  "needs-reset-on-resume"))
			priv->reset_on_resume = true;

		अगर (of_property_पढ़ो_bool(dev->dev.of_node,
					  "has-transaction-translator"))
			hcd->has_tt = 1;

		अगर (soc_device_match(quirk_poll_match))
			priv->quirk_poll = true;

		क्रम (clk = 0; clk < EHCI_MAX_CLKS; clk++) अणु
			priv->clks[clk] = of_clk_get(dev->dev.of_node, clk);
			अगर (IS_ERR(priv->clks[clk])) अणु
				err = PTR_ERR(priv->clks[clk]);
				अगर (err == -EPROBE_DEFER)
					जाओ err_put_clks;
				priv->clks[clk] = शून्य;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	priv->rsts = devm_reset_control_array_get_optional_shared(&dev->dev);
	अगर (IS_ERR(priv->rsts)) अणु
		err = PTR_ERR(priv->rsts);
		जाओ err_put_clks;
	पूर्ण

	err = reset_control_deनिश्चित(priv->rsts);
	अगर (err)
		जाओ err_put_clks;

	अगर (pdata->big_endian_desc)
		ehci->big_endian_desc = 1;
	अगर (pdata->big_endian_mmio)
		ehci->big_endian_mmio = 1;
	अगर (pdata->has_tt)
		hcd->has_tt = 1;
	अगर (pdata->reset_on_resume)
		priv->reset_on_resume = true;
	अगर (pdata->spurious_oc)
		ehci->spurious_oc = 1;

#अगर_अघोषित CONFIG_USB_EHCI_BIG_ENDIAN_MMIO
	अगर (ehci->big_endian_mmio) अणु
		dev_err(&dev->dev,
			"Error: CONFIG_USB_EHCI_BIG_ENDIAN_MMIO not set\n");
		err = -EINVAL;
		जाओ err_reset;
	पूर्ण
#पूर्ण_अगर
#अगर_अघोषित CONFIG_USB_EHCI_BIG_ENDIAN_DESC
	अगर (ehci->big_endian_desc) अणु
		dev_err(&dev->dev,
			"Error: CONFIG_USB_EHCI_BIG_ENDIAN_DESC not set\n");
		err = -EINVAL;
		जाओ err_reset;
	पूर्ण
#पूर्ण_अगर

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
	device_enable_async_suspend(hcd->self.controller);
	platक्रमm_set_drvdata(dev, hcd);

	अगर (priv->quirk_poll)
		quirk_poll_init(priv);

	वापस err;

err_घातer:
	अगर (pdata->घातer_off)
		pdata->घातer_off(dev);
err_reset:
	reset_control_निश्चित(priv->rsts);
err_put_clks:
	जबतक (--clk >= 0)
		clk_put(priv->clks[clk]);

	अगर (pdata == &ehci_platक्रमm_शेषs)
		dev->dev.platक्रमm_data = शून्य;

	usb_put_hcd(hcd);

	वापस err;
पूर्ण

अटल पूर्णांक ehci_platक्रमm_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(dev);
	काष्ठा usb_ehci_pdata *pdata = dev_get_platdata(&dev->dev);
	काष्ठा ehci_platक्रमm_priv *priv = hcd_to_ehci_priv(hcd);
	पूर्णांक clk;

	अगर (priv->quirk_poll)
		quirk_poll_end(priv);

	usb_हटाओ_hcd(hcd);

	अगर (pdata->घातer_off)
		pdata->घातer_off(dev);

	reset_control_निश्चित(priv->rsts);

	क्रम (clk = 0; clk < EHCI_MAX_CLKS && priv->clks[clk]; clk++)
		clk_put(priv->clks[clk]);

	usb_put_hcd(hcd);

	अगर (pdata == &ehci_platक्रमm_शेषs)
		dev->dev.platक्रमm_data = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ehci_platक्रमm_suspend(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd *hcd = dev_get_drvdata(dev);
	काष्ठा usb_ehci_pdata *pdata = dev_get_platdata(dev);
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा ehci_platक्रमm_priv *priv = hcd_to_ehci_priv(hcd);
	bool करो_wakeup = device_may_wakeup(dev);
	पूर्णांक ret;

	अगर (priv->quirk_poll)
		quirk_poll_end(priv);

	ret = ehci_suspend(hcd, करो_wakeup);
	अगर (ret)
		वापस ret;

	अगर (pdata->घातer_suspend)
		pdata->घातer_suspend(pdev);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused ehci_platक्रमm_resume(काष्ठा device *dev)
अणु
	काष्ठा usb_hcd *hcd = dev_get_drvdata(dev);
	काष्ठा usb_ehci_pdata *pdata = dev_get_platdata(dev);
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा ehci_platक्रमm_priv *priv = hcd_to_ehci_priv(hcd);
	काष्ठा device *companion_dev;

	अगर (pdata->घातer_on) अणु
		पूर्णांक err = pdata->घातer_on(pdev);
		अगर (err < 0)
			वापस err;
	पूर्ण

	companion_dev = usb_of_get_companion_dev(hcd->self.controller);
	अगर (companion_dev) अणु
		device_pm_रुको_क्रम_dev(hcd->self.controller, companion_dev);
		put_device(companion_dev);
	पूर्ण

	ehci_resume(hcd, priv->reset_on_resume);

	pm_runसमय_disable(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);

	अगर (priv->quirk_poll)
		quirk_poll_init(priv);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id vt8500_ehci_ids[] = अणु
	अणु .compatible = "via,vt8500-ehci", पूर्ण,
	अणु .compatible = "wm,prizm-ehci", पूर्ण,
	अणु .compatible = "generic-ehci", पूर्ण,
	अणु .compatible = "cavium,octeon-6335-ehci", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, vt8500_ehci_ids);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id ehci_acpi_match[] = अणु
	अणु "PNP0D20", 0 पूर्ण, /* EHCI controller without debug */
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, ehci_acpi_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा platक्रमm_device_id ehci_platक्रमm_table[] = अणु
	अणु "ehci-platform", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, ehci_platक्रमm_table);

अटल SIMPLE_DEV_PM_OPS(ehci_platक्रमm_pm_ops, ehci_platक्रमm_suspend,
	ehci_platक्रमm_resume);

अटल काष्ठा platक्रमm_driver ehci_platक्रमm_driver = अणु
	.id_table	= ehci_platक्रमm_table,
	.probe		= ehci_platक्रमm_probe,
	.हटाओ		= ehci_platक्रमm_हटाओ,
	.shutकरोwn	= usb_hcd_platक्रमm_shutकरोwn,
	.driver		= अणु
		.name	= "ehci-platform",
		.pm	= pm_ptr(&ehci_platक्रमm_pm_ops),
		.of_match_table = vt8500_ehci_ids,
		.acpi_match_table = ACPI_PTR(ehci_acpi_match),
	पूर्ण
पूर्ण;

अटल पूर्णांक __init ehci_platक्रमm_init(व्योम)
अणु
	अगर (usb_disabled())
		वापस -ENODEV;

	pr_info("%s: " DRIVER_DESC "\n", hcd_name);

	ehci_init_driver(&ehci_platक्रमm_hc_driver, &platक्रमm_overrides);
	वापस platक्रमm_driver_रेजिस्टर(&ehci_platक्रमm_driver);
पूर्ण
module_init(ehci_platक्रमm_init);

अटल व्योम __निकास ehci_platक्रमm_cleanup(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ehci_platक्रमm_driver);
पूर्ण
module_निकास(ehci_platक्रमm_cleanup);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR("Hauke Mehrtens");
MODULE_AUTHOR("Alan Stern");
MODULE_LICENSE("GPL");
