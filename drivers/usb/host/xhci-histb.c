<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * xHCI host controller driver क्रम HiSilicon STB SoCs
 *
 * Copyright (C) 2017-2018 HiSilicon Co., Ltd. http://www.hisilicon.com
 *
 * Authors: Jianguo Sun <sunjianguo1@huawei.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>

#समावेश "xhci.h"

#घोषणा GTXTHRCFG		0xc108
#घोषणा GRXTHRCFG		0xc10c
#घोषणा REG_GUSB2PHYCFG0	0xc200
#घोषणा BIT_UTMI_8_16		BIT(3)
#घोषणा BIT_UTMI_ULPI		BIT(4)
#घोषणा BIT_FREECLK_EXIST	BIT(30)

#घोषणा REG_GUSB3PIPECTL0	0xc2c0
#घोषणा USB3_DEEMPHASIS_MASK	GENMASK(2, 1)
#घोषणा USB3_DEEMPHASIS0	BIT(1)
#घोषणा USB3_TX_MARGIN1		BIT(4)

काष्ठा xhci_hcd_histb अणु
	काष्ठा device		*dev;
	काष्ठा usb_hcd		*hcd;
	व्योम __iomem		*ctrl;
	काष्ठा clk		*bus_clk;
	काष्ठा clk		*uपंचांगi_clk;
	काष्ठा clk		*pipe_clk;
	काष्ठा clk		*suspend_clk;
	काष्ठा reset_control	*soft_reset;
पूर्ण;

अटल अंतरभूत काष्ठा xhci_hcd_histb *hcd_to_histb(काष्ठा usb_hcd *hcd)
अणु
	वापस dev_get_drvdata(hcd->self.controller);
पूर्ण

अटल पूर्णांक xhci_histb_config(काष्ठा xhci_hcd_histb *histb)
अणु
	काष्ठा device_node *np = histb->dev->of_node;
	u32 regval;

	अगर (of_property_match_string(np, "phys-names", "inno") >= 0) अणु
		/* USB2 PHY chose ulpi 8bit पूर्णांकerface */
		regval = पढ़ोl(histb->ctrl + REG_GUSB2PHYCFG0);
		regval &= ~BIT_UTMI_ULPI;
		regval &= ~(BIT_UTMI_8_16);
		regval &= ~BIT_FREECLK_EXIST;
		ग_लिखोl(regval, histb->ctrl + REG_GUSB2PHYCFG0);
	पूर्ण

	अगर (of_property_match_string(np, "phys-names", "combo") >= 0) अणु
		/*
		 * ग_लिखो 0x010c0012 to GUSB3PIPECTL0
		 * GUSB3PIPECTL0[5:3] = 010 : Tx Margin = 900mV ,
		 * decrease TX voltage
		 * GUSB3PIPECTL0[2:1] = 01 : Tx Deemphasis = -3.5dB,
		 * refer to xHCI spec
		 */
		regval = पढ़ोl(histb->ctrl + REG_GUSB3PIPECTL0);
		regval &= ~USB3_DEEMPHASIS_MASK;
		regval |= USB3_DEEMPHASIS0;
		regval |= USB3_TX_MARGIN1;
		ग_लिखोl(regval, histb->ctrl + REG_GUSB3PIPECTL0);
	पूर्ण

	ग_लिखोl(0x23100000, histb->ctrl + GTXTHRCFG);
	ग_लिखोl(0x23100000, histb->ctrl + GRXTHRCFG);

	वापस 0;
पूर्ण

अटल पूर्णांक xhci_histb_clks_get(काष्ठा xhci_hcd_histb *histb)
अणु
	काष्ठा device *dev = histb->dev;

	histb->bus_clk = devm_clk_get(dev, "bus");
	अगर (IS_ERR(histb->bus_clk)) अणु
		dev_err(dev, "fail to get bus clk\n");
		वापस PTR_ERR(histb->bus_clk);
	पूर्ण

	histb->uपंचांगi_clk = devm_clk_get(dev, "utmi");
	अगर (IS_ERR(histb->uपंचांगi_clk)) अणु
		dev_err(dev, "fail to get utmi clk\n");
		वापस PTR_ERR(histb->uपंचांगi_clk);
	पूर्ण

	histb->pipe_clk = devm_clk_get(dev, "pipe");
	अगर (IS_ERR(histb->pipe_clk)) अणु
		dev_err(dev, "fail to get pipe clk\n");
		वापस PTR_ERR(histb->pipe_clk);
	पूर्ण

	histb->suspend_clk = devm_clk_get(dev, "suspend");
	अगर (IS_ERR(histb->suspend_clk)) अणु
		dev_err(dev, "fail to get suspend clk\n");
		वापस PTR_ERR(histb->suspend_clk);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xhci_histb_host_enable(काष्ठा xhci_hcd_histb *histb)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(histb->bus_clk);
	अगर (ret) अणु
		dev_err(histb->dev, "failed to enable bus clk\n");
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(histb->uपंचांगi_clk);
	अगर (ret) अणु
		dev_err(histb->dev, "failed to enable utmi clk\n");
		जाओ err_uपंचांगi_clk;
	पूर्ण

	ret = clk_prepare_enable(histb->pipe_clk);
	अगर (ret) अणु
		dev_err(histb->dev, "failed to enable pipe clk\n");
		जाओ err_pipe_clk;
	पूर्ण

	ret = clk_prepare_enable(histb->suspend_clk);
	अगर (ret) अणु
		dev_err(histb->dev, "failed to enable suspend clk\n");
		जाओ err_suspend_clk;
	पूर्ण

	reset_control_deनिश्चित(histb->soft_reset);

	वापस 0;

err_suspend_clk:
	clk_disable_unprepare(histb->pipe_clk);
err_pipe_clk:
	clk_disable_unprepare(histb->uपंचांगi_clk);
err_uपंचांगi_clk:
	clk_disable_unprepare(histb->bus_clk);

	वापस ret;
पूर्ण

अटल व्योम xhci_histb_host_disable(काष्ठा xhci_hcd_histb *histb)
अणु
	reset_control_निश्चित(histb->soft_reset);

	clk_disable_unprepare(histb->suspend_clk);
	clk_disable_unprepare(histb->pipe_clk);
	clk_disable_unprepare(histb->uपंचांगi_clk);
	clk_disable_unprepare(histb->bus_clk);
पूर्ण

अटल व्योम xhci_histb_quirks(काष्ठा device *dev, काष्ठा xhci_hcd *xhci)
अणु
	/*
	 * As of now platक्रमm drivers करोn't provide MSI support so we ensure
	 * here that the generic code करोes not try to make a pci_dev from our
	 * dev काष्ठा in order to setup MSI
	 */
	xhci->quirks |= XHCI_PLAT;
पूर्ण

/* called during probe() after chip reset completes */
अटल पूर्णांक xhci_histb_setup(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा xhci_hcd_histb *histb = hcd_to_histb(hcd);
	पूर्णांक ret;

	अगर (usb_hcd_is_primary_hcd(hcd)) अणु
		ret = xhci_histb_config(histb);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस xhci_gen_setup(hcd, xhci_histb_quirks);
पूर्ण

अटल स्थिर काष्ठा xhci_driver_overrides xhci_histb_overrides __initस्थिर = अणु
	.reset = xhci_histb_setup,
पूर्ण;

अटल काष्ठा hc_driver __पढ़ो_mostly xhci_histb_hc_driver;
अटल पूर्णांक xhci_histb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा xhci_hcd_histb *histb;
	स्थिर काष्ठा hc_driver *driver;
	काष्ठा usb_hcd *hcd;
	काष्ठा xhci_hcd *xhci;
	काष्ठा resource *res;
	पूर्णांक irq;
	पूर्णांक ret = -ENODEV;

	अगर (usb_disabled())
		वापस -ENODEV;

	driver = &xhci_histb_hc_driver;
	histb = devm_kzalloc(dev, माप(*histb), GFP_KERNEL);
	अगर (!histb)
		वापस -ENOMEM;

	histb->dev = dev;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	histb->ctrl = devm_platक्रमm_get_and_ioremap_resource(pdev, 0, &res);
	अगर (IS_ERR(histb->ctrl))
		वापस PTR_ERR(histb->ctrl);

	ret = xhci_histb_clks_get(histb);
	अगर (ret)
		वापस ret;

	histb->soft_reset = devm_reset_control_get(dev, "soft");
	अगर (IS_ERR(histb->soft_reset)) अणु
		dev_err(dev, "failed to get soft reset\n");
		वापस PTR_ERR(histb->soft_reset);
	पूर्ण

	pm_runसमय_enable(dev);
	pm_runसमय_get_sync(dev);
	device_enable_async_suspend(dev);

	/* Initialize dma_mask and coherent_dma_mask to 32-bits */
	ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));
	अगर (ret)
		जाओ disable_pm;

	hcd = usb_create_hcd(driver, dev, dev_name(dev));
	अगर (!hcd) अणु
		ret = -ENOMEM;
		जाओ disable_pm;
	पूर्ण

	hcd->regs = histb->ctrl;
	hcd->rsrc_start = res->start;
	hcd->rsrc_len = resource_size(res);

	histb->hcd = hcd;
	dev_set_drvdata(hcd->self.controller, histb);

	ret = xhci_histb_host_enable(histb);
	अगर (ret)
		जाओ put_hcd;

	xhci = hcd_to_xhci(hcd);

	device_wakeup_enable(hcd->self.controller);

	xhci->मुख्य_hcd = hcd;
	xhci->shared_hcd = usb_create_shared_hcd(driver, dev, dev_name(dev),
						 hcd);
	अगर (!xhci->shared_hcd) अणु
		ret = -ENOMEM;
		जाओ disable_host;
	पूर्ण

	अगर (device_property_पढ़ो_bool(dev, "usb2-lpm-disable"))
		xhci->quirks |= XHCI_HW_LPM_DISABLE;

	अगर (device_property_पढ़ो_bool(dev, "usb3-lpm-capable"))
		xhci->quirks |= XHCI_LPM_SUPPORT;

	/* imod_पूर्णांकerval is the पूर्णांकerrupt moderation value in nanoseconds. */
	xhci->imod_पूर्णांकerval = 40000;
	device_property_पढ़ो_u32(dev, "imod-interval-ns",
				 &xhci->imod_पूर्णांकerval);

	ret = usb_add_hcd(hcd, irq, IRQF_SHARED);
	अगर (ret)
		जाओ put_usb3_hcd;

	अगर (HCC_MAX_PSA(xhci->hcc_params) >= 4)
		xhci->shared_hcd->can_करो_streams = 1;

	ret = usb_add_hcd(xhci->shared_hcd, irq, IRQF_SHARED);
	अगर (ret)
		जाओ dealloc_usb2_hcd;

	device_enable_async_suspend(dev);
	pm_runसमय_put_noidle(dev);

	/*
	 * Prevent runसमय pm from being on as शेष, users should enable
	 * runसमय pm using घातer/control in sysfs.
	 */
	pm_runसमय_क्रमbid(dev);

	वापस 0;

dealloc_usb2_hcd:
	usb_हटाओ_hcd(hcd);
put_usb3_hcd:
	usb_put_hcd(xhci->shared_hcd);
disable_host:
	xhci_histb_host_disable(histb);
put_hcd:
	usb_put_hcd(hcd);
disable_pm:
	pm_runसमय_put_sync(dev);
	pm_runसमय_disable(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक xhci_histb_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा xhci_hcd_histb *histb = platक्रमm_get_drvdata(dev);
	काष्ठा usb_hcd *hcd = histb->hcd;
	काष्ठा xhci_hcd	*xhci = hcd_to_xhci(hcd);
	काष्ठा usb_hcd *shared_hcd = xhci->shared_hcd;

	xhci->xhc_state |= XHCI_STATE_REMOVING;

	usb_हटाओ_hcd(shared_hcd);
	xhci->shared_hcd = शून्य;
	device_wakeup_disable(&dev->dev);

	usb_हटाओ_hcd(hcd);
	usb_put_hcd(shared_hcd);

	xhci_histb_host_disable(histb);
	usb_put_hcd(hcd);
	pm_runसमय_put_sync(&dev->dev);
	pm_runसमय_disable(&dev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused xhci_histb_suspend(काष्ठा device *dev)
अणु
	काष्ठा xhci_hcd_histb *histb = dev_get_drvdata(dev);
	काष्ठा usb_hcd *hcd = histb->hcd;
	काष्ठा xhci_hcd	*xhci = hcd_to_xhci(hcd);
	पूर्णांक ret;

	ret = xhci_suspend(xhci, device_may_wakeup(dev));

	अगर (!device_may_wakeup(dev))
		xhci_histb_host_disable(histb);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused xhci_histb_resume(काष्ठा device *dev)
अणु
	काष्ठा xhci_hcd_histb *histb = dev_get_drvdata(dev);
	काष्ठा usb_hcd *hcd = histb->hcd;
	काष्ठा xhci_hcd *xhci = hcd_to_xhci(hcd);

	अगर (!device_may_wakeup(dev))
		xhci_histb_host_enable(histb);

	वापस xhci_resume(xhci, 0);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops xhci_histb_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(xhci_histb_suspend, xhci_histb_resume)
पूर्ण;
#घोषणा DEV_PM_OPS (IS_ENABLED(CONFIG_PM) ? &xhci_histb_pm_ops : शून्य)

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id histb_xhci_of_match[] = अणु
	अणु .compatible = "hisilicon,hi3798cv200-xhci"पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, histb_xhci_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver histb_xhci_driver = अणु
	.probe	= xhci_histb_probe,
	.हटाओ	= xhci_histb_हटाओ,
	.driver	= अणु
		.name = "xhci-histb",
		.pm = DEV_PM_OPS,
		.of_match_table = of_match_ptr(histb_xhci_of_match),
	पूर्ण,
पूर्ण;
MODULE_ALIAS("platform:xhci-histb");

अटल पूर्णांक __init xhci_histb_init(व्योम)
अणु
	xhci_init_driver(&xhci_histb_hc_driver, &xhci_histb_overrides);
	वापस platक्रमm_driver_रेजिस्टर(&histb_xhci_driver);
पूर्ण
module_init(xhci_histb_init);

अटल व्योम __निकास xhci_histb_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&histb_xhci_driver);
पूर्ण
module_निकास(xhci_histb_निकास);

MODULE_DESCRIPTION("HiSilicon STB xHCI Host Controller Driver");
MODULE_LICENSE("GPL v2");
