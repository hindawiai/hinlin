<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Cadence USBSS DRD Driver.
 *
 * Copyright (C) 2018-2020 Cadence.
 * Copyright (C) 2017-2018 NXP
 * Copyright (C) 2019 Texas Instruments
 *
 *
 * Author: Peter Chen <peter.chen@nxp.com>
 *         Pawel Laszczak <pawell@cadence.com>
 *         Roger Quadros <rogerq@ti.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "core.h"
#समावेश "gadget-export.h"
#समावेश "drd.h"

अटल पूर्णांक set_phy_घातer_on(काष्ठा cdns *cdns)
अणु
	पूर्णांक ret;

	ret = phy_घातer_on(cdns->usb2_phy);
	अगर (ret)
		वापस ret;

	ret = phy_घातer_on(cdns->usb3_phy);
	अगर (ret)
		phy_घातer_off(cdns->usb2_phy);

	वापस ret;
पूर्ण

अटल व्योम set_phy_घातer_off(काष्ठा cdns *cdns)
अणु
	phy_घातer_off(cdns->usb3_phy);
	phy_घातer_off(cdns->usb2_phy);
पूर्ण

/**
 * cdns3_plat_probe - probe क्रम cdns3 core device
 * @pdev: Poपूर्णांकer to cdns3 core platक्रमm device
 *
 * Returns 0 on success otherwise negative त्रुटि_सं
 */
अटल पूर्णांक cdns3_plat_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource	*res;
	काष्ठा cdns *cdns;
	व्योम __iomem *regs;
	पूर्णांक ret;

	cdns = devm_kzalloc(dev, माप(*cdns), GFP_KERNEL);
	अगर (!cdns)
		वापस -ENOMEM;

	cdns->dev = dev;
	cdns->pdata = dev_get_platdata(dev);

	platक्रमm_set_drvdata(pdev, cdns);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_IRQ, "host");
	अगर (!res) अणु
		dev_err(dev, "missing host IRQ\n");
		वापस -ENODEV;
	पूर्ण

	cdns->xhci_res[0] = *res;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "xhci");
	अगर (!res) अणु
		dev_err(dev, "couldn't get xhci resource\n");
		वापस -ENXIO;
	पूर्ण

	cdns->xhci_res[1] = *res;

	cdns->dev_irq = platक्रमm_get_irq_byname(pdev, "peripheral");

	अगर (cdns->dev_irq < 0)
		वापस cdns->dev_irq;

	regs = devm_platक्रमm_ioremap_resource_byname(pdev, "dev");
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);
	cdns->dev_regs	= regs;

	cdns->otg_irq = platक्रमm_get_irq_byname(pdev, "otg");
	अगर (cdns->otg_irq < 0)
		वापस cdns->otg_irq;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "otg");
	अगर (!res) अणु
		dev_err(dev, "couldn't get otg resource\n");
		वापस -ENXIO;
	पूर्ण

	cdns->phyrst_a_enable = device_property_पढ़ो_bool(dev, "cdns,phyrst-a-enable");

	cdns->otg_res = *res;

	cdns->wakeup_irq = platक्रमm_get_irq_byname_optional(pdev, "wakeup");
	अगर (cdns->wakeup_irq == -EPROBE_DEFER)
		वापस cdns->wakeup_irq;
	अन्यथा अगर (cdns->wakeup_irq == 0)
		वापस -EINVAL;

	अगर (cdns->wakeup_irq < 0) अणु
		dev_dbg(dev, "couldn't get wakeup irq\n");
		cdns->wakeup_irq = 0x0;
	पूर्ण

	cdns->usb2_phy = devm_phy_optional_get(dev, "cdns3,usb2-phy");
	अगर (IS_ERR(cdns->usb2_phy))
		वापस PTR_ERR(cdns->usb2_phy);

	ret = phy_init(cdns->usb2_phy);
	अगर (ret)
		वापस ret;

	cdns->usb3_phy = devm_phy_optional_get(dev, "cdns3,usb3-phy");
	अगर (IS_ERR(cdns->usb3_phy))
		वापस PTR_ERR(cdns->usb3_phy);

	ret = phy_init(cdns->usb3_phy);
	अगर (ret)
		जाओ err_phy3_init;

	ret = set_phy_घातer_on(cdns);
	अगर (ret)
		जाओ err_phy_घातer_on;

	cdns->gadget_init = cdns3_gadget_init;

	ret = cdns_init(cdns);
	अगर (ret)
		जाओ err_cdns_init;

	device_set_wakeup_capable(dev, true);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);
	अगर (!(cdns->pdata && (cdns->pdata->quirks & CDNS3_DEFAULT_PM_RUNTIME_ALLOW)))
		pm_runसमय_क्रमbid(dev);

	/*
	 * The controller needs less समय between bus and controller suspend,
	 * and we also needs a small delay to aव्योम frequently entering low
	 * घातer mode.
	 */
	pm_runसमय_set_स्वतःsuspend_delay(dev, 20);
	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_use_स्वतःsuspend(dev);

	वापस 0;

err_cdns_init:
	set_phy_घातer_off(cdns);
err_phy_घातer_on:
	phy_निकास(cdns->usb3_phy);
err_phy3_init:
	phy_निकास(cdns->usb2_phy);

	वापस ret;
पूर्ण

/**
 * cdns3_हटाओ - unbind drd driver and clean up
 * @pdev: Poपूर्णांकer to Linux platक्रमm device
 *
 * Returns 0 on success otherwise negative त्रुटि_सं
 */
अटल पूर्णांक cdns3_plat_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cdns *cdns = platक्रमm_get_drvdata(pdev);
	काष्ठा device *dev = cdns->dev;

	pm_runसमय_get_sync(dev);
	pm_runसमय_disable(dev);
	pm_runसमय_put_noidle(dev);
	cdns_हटाओ(cdns);
	set_phy_घातer_off(cdns);
	phy_निकास(cdns->usb2_phy);
	phy_निकास(cdns->usb3_phy);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक cdns3_set_platक्रमm_suspend(काष्ठा device *dev,
				      bool suspend, bool wakeup)
अणु
	काष्ठा cdns *cdns = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	अगर (cdns->pdata && cdns->pdata->platक्रमm_suspend)
		ret = cdns->pdata->platक्रमm_suspend(dev, suspend, wakeup);

	वापस ret;
पूर्ण

अटल पूर्णांक cdns3_controller_suspend(काष्ठा device *dev, pm_message_t msg)
अणु
	काष्ठा cdns *cdns = dev_get_drvdata(dev);
	bool wakeup;
	अचिन्हित दीर्घ flags;

	अगर (cdns->in_lpm)
		वापस 0;

	अगर (PMSG_IS_AUTO(msg))
		wakeup = true;
	अन्यथा
		wakeup = device_may_wakeup(dev);

	cdns3_set_platक्रमm_suspend(cdns->dev, true, wakeup);
	set_phy_घातer_off(cdns);
	spin_lock_irqsave(&cdns->lock, flags);
	cdns->in_lpm = true;
	spin_unlock_irqrestore(&cdns->lock, flags);
	dev_dbg(cdns->dev, "%s ends\n", __func__);

	वापस 0;
पूर्ण

अटल पूर्णांक cdns3_controller_resume(काष्ठा device *dev, pm_message_t msg)
अणु
	काष्ठा cdns *cdns = dev_get_drvdata(dev);
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	अगर (!cdns->in_lpm)
		वापस 0;

	अगर (cdns_घातer_is_lost(cdns)) अणु
		phy_निकास(cdns->usb2_phy);
		ret = phy_init(cdns->usb2_phy);
		अगर (ret)
			वापस ret;

		phy_निकास(cdns->usb3_phy);
		ret = phy_init(cdns->usb3_phy);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = set_phy_घातer_on(cdns);
	अगर (ret)
		वापस ret;

	cdns3_set_platक्रमm_suspend(cdns->dev, false, false);

	spin_lock_irqsave(&cdns->lock, flags);
	cdns_resume(cdns, !PMSG_IS_AUTO(msg));
	cdns->in_lpm = false;
	spin_unlock_irqrestore(&cdns->lock, flags);
	अगर (cdns->wakeup_pending) अणु
		cdns->wakeup_pending = false;
		enable_irq(cdns->wakeup_irq);
	पूर्ण
	dev_dbg(cdns->dev, "%s ends\n", __func__);

	वापस ret;
पूर्ण

अटल पूर्णांक cdns3_plat_runसमय_suspend(काष्ठा device *dev)
अणु
	वापस cdns3_controller_suspend(dev, PMSG_AUTO_SUSPEND);
पूर्ण

अटल पूर्णांक cdns3_plat_runसमय_resume(काष्ठा device *dev)
अणु
	वापस cdns3_controller_resume(dev, PMSG_AUTO_RESUME);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP

अटल पूर्णांक cdns3_plat_suspend(काष्ठा device *dev)
अणु
	काष्ठा cdns *cdns = dev_get_drvdata(dev);
	पूर्णांक ret;

	cdns_suspend(cdns);

	ret = cdns3_controller_suspend(dev, PMSG_SUSPEND);
	अगर (ret)
		वापस ret;

	अगर (device_may_wakeup(dev) && cdns->wakeup_irq)
		enable_irq_wake(cdns->wakeup_irq);

	वापस ret;
पूर्ण

अटल पूर्णांक cdns3_plat_resume(काष्ठा device *dev)
अणु
	वापस cdns3_controller_resume(dev, PMSG_RESUME);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा dev_pm_ops cdns3_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(cdns3_plat_suspend, cdns3_plat_resume)
	SET_RUNTIME_PM_OPS(cdns3_plat_runसमय_suspend,
			   cdns3_plat_runसमय_resume, शून्य)
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id of_cdns3_match[] = अणु
	अणु .compatible = "cdns,usb3" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_cdns3_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver cdns3_driver = अणु
	.probe		= cdns3_plat_probe,
	.हटाओ		= cdns3_plat_हटाओ,
	.driver		= अणु
		.name	= "cdns-usb3",
		.of_match_table	= of_match_ptr(of_cdns3_match),
		.pm	= &cdns3_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(cdns3_driver);

MODULE_ALIAS("platform:cdns3");
MODULE_AUTHOR("Pawel Laszczak <pawell@cadence.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Cadence USB3 DRD Controller Driver");
