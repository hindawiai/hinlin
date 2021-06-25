<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2011 Marvell International Ltd. All rights reserved.
 * Author: Chao Xie <chao.xie@marvell.com>
 *        Neil Zhang <zhangwm@marvell.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/usb/of.h>
#समावेश <linux/platक्रमm_data/mv_usb.h>
#समावेश <linux/पन.स>

#समावेश <linux/usb/hcd.h>

#समावेश "ehci.h"

/* रेजिस्टरs */
#घोषणा U2x_CAPREGS_OFFSET       0x100

#घोषणा CAPLENGTH_MASK         (0xff)

#घोषणा hcd_to_ehci_hcd_mv(h) ((काष्ठा ehci_hcd_mv *)hcd_to_ehci(h)->priv)

काष्ठा ehci_hcd_mv अणु
	/* Which mode करोes this ehci running OTG/Host ? */
	पूर्णांक mode;

	व्योम __iomem *base;
	व्योम __iomem *cap_regs;
	व्योम __iomem *op_regs;

	काष्ठा usb_phy *otg;
	काष्ठा clk *clk;

	काष्ठा phy *phy;

	पूर्णांक (*set_vbus)(अचिन्हित पूर्णांक vbus);
पूर्ण;

अटल व्योम ehci_घड़ी_enable(काष्ठा ehci_hcd_mv *ehci_mv)
अणु
	clk_prepare_enable(ehci_mv->clk);
पूर्ण

अटल व्योम ehci_घड़ी_disable(काष्ठा ehci_hcd_mv *ehci_mv)
अणु
	clk_disable_unprepare(ehci_mv->clk);
पूर्ण

अटल पूर्णांक mv_ehci_enable(काष्ठा ehci_hcd_mv *ehci_mv)
अणु
	ehci_घड़ी_enable(ehci_mv);
	वापस phy_init(ehci_mv->phy);
पूर्ण

अटल व्योम mv_ehci_disable(काष्ठा ehci_hcd_mv *ehci_mv)
अणु
	phy_निकास(ehci_mv->phy);
	ehci_घड़ी_disable(ehci_mv);
पूर्ण

अटल पूर्णांक mv_ehci_reset(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा device *dev = hcd->self.controller;
	काष्ठा ehci_hcd_mv *ehci_mv = hcd_to_ehci_hcd_mv(hcd);
	काष्ठा ehci_hcd *ehci = hcd_to_ehci(hcd);
	u32 status;
	पूर्णांक retval;

	अगर (ehci_mv == शून्य) अणु
		dev_err(dev, "Can not find private ehci data\n");
		वापस -ENODEV;
	पूर्ण

	hcd->has_tt = 1;

	retval = ehci_setup(hcd);
	अगर (retval)
		dev_err(dev, "ehci_setup failed %d\n", retval);

	अगर (of_usb_get_phy_mode(dev->of_node) == USBPHY_INTERFACE_MODE_HSIC) अणु
		status = ehci_पढ़ोl(ehci, &ehci->regs->port_status[0]);
		status |= PORT_TEST_FORCE;
		ehci_ग_लिखोl(ehci, status, &ehci->regs->port_status[0]);
		status &= ~PORT_TEST_FORCE;
		ehci_ग_लिखोl(ehci, status, &ehci->regs->port_status[0]);
	पूर्ण

	वापस retval;
पूर्ण

अटल काष्ठा hc_driver __पढ़ो_mostly ehci_platक्रमm_hc_driver;

अटल स्थिर काष्ठा ehci_driver_overrides platक्रमm_overrides __initस्थिर = अणु
	.reset =		mv_ehci_reset,
	.extra_priv_size =	माप(काष्ठा ehci_hcd_mv),
पूर्ण;

अटल पूर्णांक mv_ehci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mv_usb_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा usb_hcd *hcd;
	काष्ठा ehci_hcd *ehci;
	काष्ठा ehci_hcd_mv *ehci_mv;
	काष्ठा resource *r;
	पूर्णांक retval;
	u32 offset;
	u32 status;

	अगर (usb_disabled())
		वापस -ENODEV;

	hcd = usb_create_hcd(&ehci_platक्रमm_hc_driver, &pdev->dev, dev_name(&pdev->dev));
	अगर (!hcd)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, hcd);
	ehci_mv = hcd_to_ehci_hcd_mv(hcd);

	ehci_mv->mode = MV_USB_MODE_HOST;
	अगर (pdata) अणु
		ehci_mv->mode = pdata->mode;
		ehci_mv->set_vbus = pdata->set_vbus;
	पूर्ण

	ehci_mv->phy = devm_phy_optional_get(&pdev->dev, "usb");
	अगर (IS_ERR(ehci_mv->phy)) अणु
		retval = PTR_ERR(ehci_mv->phy);
		अगर (retval != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Failed to get phy.\n");
		जाओ err_put_hcd;
	पूर्ण

	ehci_mv->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(ehci_mv->clk)) अणु
		dev_err(&pdev->dev, "error getting clock\n");
		retval = PTR_ERR(ehci_mv->clk);
		जाओ err_put_hcd;
	पूर्ण

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ehci_mv->base = devm_ioremap_resource(&pdev->dev, r);
	अगर (IS_ERR(ehci_mv->base)) अणु
		retval = PTR_ERR(ehci_mv->base);
		जाओ err_put_hcd;
	पूर्ण

	retval = mv_ehci_enable(ehci_mv);
	अगर (retval) अणु
		dev_err(&pdev->dev, "init phy error %d\n", retval);
		जाओ err_put_hcd;
	पूर्ण

	ehci_mv->cap_regs =
		(व्योम __iomem *) ((अचिन्हित दीर्घ) ehci_mv->base + U2x_CAPREGS_OFFSET);
	offset = पढ़ोl(ehci_mv->cap_regs) & CAPLENGTH_MASK;
	ehci_mv->op_regs =
		(व्योम __iomem *) ((अचिन्हित दीर्घ) ehci_mv->cap_regs + offset);

	hcd->rsrc_start = r->start;
	hcd->rsrc_len = resource_size(r);
	hcd->regs = ehci_mv->op_regs;

	retval = platक्रमm_get_irq(pdev, 0);
	अगर (retval < 0)
		जाओ err_disable_clk;
	hcd->irq = retval;

	ehci = hcd_to_ehci(hcd);
	ehci->caps = (काष्ठा ehci_caps __iomem *) ehci_mv->cap_regs;

	अगर (ehci_mv->mode == MV_USB_MODE_OTG) अणु
		ehci_mv->otg = devm_usb_get_phy(&pdev->dev, USB_PHY_TYPE_USB2);
		अगर (IS_ERR(ehci_mv->otg)) अणु
			retval = PTR_ERR(ehci_mv->otg);

			अगर (retval == -ENXIO)
				dev_info(&pdev->dev, "MV_USB_MODE_OTG "
						"must have CONFIG_USB_PHY enabled\n");
			अन्यथा
				dev_err(&pdev->dev,
						"unable to find transceiver\n");
			जाओ err_disable_clk;
		पूर्ण

		retval = otg_set_host(ehci_mv->otg->otg, &hcd->self);
		अगर (retval < 0) अणु
			dev_err(&pdev->dev,
				"unable to register with transceiver\n");
			retval = -ENODEV;
			जाओ err_disable_clk;
		पूर्ण
		/* otg will enable घड़ी beक्रमe use as host */
		mv_ehci_disable(ehci_mv);
	पूर्ण अन्यथा अणु
		अगर (ehci_mv->set_vbus)
			ehci_mv->set_vbus(1);

		retval = usb_add_hcd(hcd, hcd->irq, IRQF_SHARED);
		अगर (retval) अणु
			dev_err(&pdev->dev,
				"failed to add hcd with err %d\n", retval);
			जाओ err_set_vbus;
		पूर्ण
		device_wakeup_enable(hcd->self.controller);
	पूर्ण

	अगर (of_usb_get_phy_mode(pdev->dev.of_node) == USBPHY_INTERFACE_MODE_HSIC) अणु
		status = ehci_पढ़ोl(ehci, &ehci->regs->port_status[0]);
		/* These "reserved" bits actually enable HSIC mode. */
		status |= BIT(25);
		status &= ~GENMASK(31, 30);
		ehci_ग_लिखोl(ehci, status, &ehci->regs->port_status[0]);
	पूर्ण

	dev_info(&pdev->dev,
		 "successful find EHCI device with regs 0x%p irq %d"
		 " working in %s mode\n", hcd->regs, hcd->irq,
		 ehci_mv->mode == MV_USB_MODE_OTG ? "OTG" : "Host");

	वापस 0;

err_set_vbus:
	अगर (ehci_mv->set_vbus)
		ehci_mv->set_vbus(0);
err_disable_clk:
	mv_ehci_disable(ehci_mv);
err_put_hcd:
	usb_put_hcd(hcd);

	वापस retval;
पूर्ण

अटल पूर्णांक mv_ehci_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(pdev);
	काष्ठा ehci_hcd_mv *ehci_mv = hcd_to_ehci_hcd_mv(hcd);

	अगर (hcd->rh_रेजिस्टरed)
		usb_हटाओ_hcd(hcd);

	अगर (!IS_ERR_OR_शून्य(ehci_mv->otg))
		otg_set_host(ehci_mv->otg->otg, शून्य);

	अगर (ehci_mv->mode == MV_USB_MODE_HOST) अणु
		अगर (ehci_mv->set_vbus)
			ehci_mv->set_vbus(0);

		mv_ehci_disable(ehci_mv);
	पूर्ण

	usb_put_hcd(hcd);

	वापस 0;
पूर्ण

MODULE_ALIAS("mv-ehci");

अटल स्थिर काष्ठा platक्रमm_device_id ehci_id_table[] = अणु
	अणु"pxa-u2oehci", 0पूर्ण,
	अणु"pxa-sph", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल व्योम mv_ehci_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_hcd *hcd = platक्रमm_get_drvdata(pdev);

	अगर (!hcd->rh_रेजिस्टरed)
		वापस;

	अगर (hcd->driver->shutकरोwn)
		hcd->driver->shutकरोwn(hcd);
पूर्ण

अटल स्थिर काष्ठा of_device_id ehci_mv_dt_ids[] = अणु
	अणु .compatible = "marvell,pxau2o-ehci", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver ehci_mv_driver = अणु
	.probe = mv_ehci_probe,
	.हटाओ = mv_ehci_हटाओ,
	.shutकरोwn = mv_ehci_shutकरोwn,
	.driver = अणु
		.name = "mv-ehci",
		.bus = &platक्रमm_bus_type,
		.of_match_table = ehci_mv_dt_ids,
	पूर्ण,
	.id_table = ehci_id_table,
पूर्ण;

अटल पूर्णांक __init ehci_platक्रमm_init(व्योम)
अणु
	अगर (usb_disabled())
		वापस -ENODEV;

	ehci_init_driver(&ehci_platक्रमm_hc_driver, &platक्रमm_overrides);
	वापस platक्रमm_driver_रेजिस्टर(&ehci_mv_driver);
पूर्ण
module_init(ehci_platक्रमm_init);

अटल व्योम __निकास ehci_platक्रमm_cleanup(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ehci_mv_driver);
पूर्ण
module_निकास(ehci_platक्रमm_cleanup);

MODULE_DESCRIPTION("Marvell EHCI driver");
MODULE_AUTHOR("Chao Xie <chao.xie@marvell.com>");
MODULE_AUTHOR("Neil Zhang <zhangwm@marvell.com>");
MODULE_ALIAS("mv-ehci");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(of, ehci_mv_dt_ids);
