<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * dwc3-imx8mp.c - NXP imx8mp Specअगरic Glue layer
 *
 * Copyright (c) 2020 NXP.
 */

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "core.h"

/* USB wakeup रेजिस्टरs */
#घोषणा USB_WAKEUP_CTRL			0x00

/* Global wakeup पूर्णांकerrupt enable, also used to clear पूर्णांकerrupt */
#घोषणा USB_WAKEUP_EN			BIT(31)
/* Wakeup from connect or disconnect, only क्रम superspeed */
#घोषणा USB_WAKEUP_SS_CONN		BIT(5)
/* 0 select vbus_valid, 1 select sessvld */
#घोषणा USB_WAKEUP_VBUS_SRC_SESS_VAL	BIT(4)
/* Enable संकेत क्रम wake up from u3 state */
#घोषणा USB_WAKEUP_U3_EN		BIT(3)
/* Enable संकेत क्रम wake up from id change */
#घोषणा USB_WAKEUP_ID_EN		BIT(2)
/* Enable संकेत क्रम wake up from vbus change */
#घोषणा	USB_WAKEUP_VBUS_EN		BIT(1)
/* Enable संकेत क्रम wake up from dp/dm change */
#घोषणा USB_WAKEUP_DPDM_EN		BIT(0)

#घोषणा USB_WAKEUP_EN_MASK		GENMASK(5, 0)

काष्ठा dwc3_imx8mp अणु
	काष्ठा device			*dev;
	काष्ठा platक्रमm_device		*dwc3;
	व्योम __iomem			*glue_base;
	काष्ठा clk			*hsio_clk;
	काष्ठा clk			*suspend_clk;
	पूर्णांक				irq;
	bool				pm_suspended;
	bool				wakeup_pending;
पूर्ण;

अटल व्योम dwc3_imx8mp_wakeup_enable(काष्ठा dwc3_imx8mp *dwc3_imx)
अणु
	काष्ठा dwc3	*dwc3 = platक्रमm_get_drvdata(dwc3_imx->dwc3);
	u32		val;

	अगर (!dwc3)
		वापस;

	val = पढ़ोl(dwc3_imx->glue_base + USB_WAKEUP_CTRL);

	अगर ((dwc3->current_dr_role == DWC3_GCTL_PRTCAP_HOST) && dwc3->xhci)
		val |= USB_WAKEUP_EN | USB_WAKEUP_SS_CONN |
		       USB_WAKEUP_U3_EN | USB_WAKEUP_DPDM_EN;
	अन्यथा अगर (dwc3->current_dr_role == DWC3_GCTL_PRTCAP_DEVICE)
		val |= USB_WAKEUP_EN | USB_WAKEUP_VBUS_EN |
		       USB_WAKEUP_VBUS_SRC_SESS_VAL;

	ग_लिखोl(val, dwc3_imx->glue_base + USB_WAKEUP_CTRL);
पूर्ण

अटल व्योम dwc3_imx8mp_wakeup_disable(काष्ठा dwc3_imx8mp *dwc3_imx)
अणु
	u32 val;

	val = पढ़ोl(dwc3_imx->glue_base + USB_WAKEUP_CTRL);
	val &= ~(USB_WAKEUP_EN | USB_WAKEUP_EN_MASK);
	ग_लिखोl(val, dwc3_imx->glue_base + USB_WAKEUP_CTRL);
पूर्ण

अटल irqवापस_t dwc3_imx8mp_पूर्णांकerrupt(पूर्णांक irq, व्योम *_dwc3_imx)
अणु
	काष्ठा dwc3_imx8mp	*dwc3_imx = _dwc3_imx;
	काष्ठा dwc3		*dwc = platक्रमm_get_drvdata(dwc3_imx->dwc3);

	अगर (!dwc3_imx->pm_suspended)
		वापस IRQ_HANDLED;

	disable_irq_nosync(dwc3_imx->irq);
	dwc3_imx->wakeup_pending = true;

	अगर ((dwc->current_dr_role == DWC3_GCTL_PRTCAP_HOST) && dwc->xhci)
		pm_runसमय_resume(&dwc->xhci->dev);
	अन्यथा अगर (dwc->current_dr_role == DWC3_GCTL_PRTCAP_DEVICE)
		pm_runसमय_get(dwc->dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक dwc3_imx8mp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device		*dev = &pdev->dev;
	काष्ठा device_node	*dwc3_np, *node = dev->of_node;
	काष्ठा dwc3_imx8mp	*dwc3_imx;
	पूर्णांक			err, irq;

	अगर (!node) अणु
		dev_err(dev, "device node not found\n");
		वापस -EINVAL;
	पूर्ण

	dwc3_imx = devm_kzalloc(dev, माप(*dwc3_imx), GFP_KERNEL);
	अगर (!dwc3_imx)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, dwc3_imx);

	dwc3_imx->dev = dev;

	dwc3_imx->glue_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(dwc3_imx->glue_base))
		वापस PTR_ERR(dwc3_imx->glue_base);

	dwc3_imx->hsio_clk = devm_clk_get(dev, "hsio");
	अगर (IS_ERR(dwc3_imx->hsio_clk)) अणु
		err = PTR_ERR(dwc3_imx->hsio_clk);
		dev_err(dev, "Failed to get hsio clk, err=%d\n", err);
		वापस err;
	पूर्ण

	err = clk_prepare_enable(dwc3_imx->hsio_clk);
	अगर (err) अणु
		dev_err(dev, "Failed to enable hsio clk, err=%d\n", err);
		वापस err;
	पूर्ण

	dwc3_imx->suspend_clk = devm_clk_get(dev, "suspend");
	अगर (IS_ERR(dwc3_imx->suspend_clk)) अणु
		err = PTR_ERR(dwc3_imx->suspend_clk);
		dev_err(dev, "Failed to get suspend clk, err=%d\n", err);
		जाओ disable_hsio_clk;
	पूर्ण

	err = clk_prepare_enable(dwc3_imx->suspend_clk);
	अगर (err) अणु
		dev_err(dev, "Failed to enable suspend clk, err=%d\n", err);
		जाओ disable_hsio_clk;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		err = irq;
		जाओ disable_clks;
	पूर्ण
	dwc3_imx->irq = irq;

	err = devm_request_thपढ़ोed_irq(dev, irq, शून्य, dwc3_imx8mp_पूर्णांकerrupt,
					IRQF_ONESHOT, dev_name(dev), dwc3_imx);
	अगर (err) अणु
		dev_err(dev, "failed to request IRQ #%d --> %d\n", irq, err);
		जाओ disable_clks;
	पूर्ण

	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);
	err = pm_runसमय_get_sync(dev);
	अगर (err < 0)
		जाओ disable_rpm;

	dwc3_np = of_get_compatible_child(node, "snps,dwc3");
	अगर (!dwc3_np) अणु
		err = -ENODEV;
		dev_err(dev, "failed to find dwc3 core child\n");
		जाओ disable_rpm;
	पूर्ण

	err = of_platक्रमm_populate(node, शून्य, शून्य, dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to create dwc3 core\n");
		जाओ err_node_put;
	पूर्ण

	dwc3_imx->dwc3 = of_find_device_by_node(dwc3_np);
	अगर (!dwc3_imx->dwc3) अणु
		dev_err(dev, "failed to get dwc3 platform device\n");
		err = -ENODEV;
		जाओ depopulate;
	पूर्ण
	of_node_put(dwc3_np);

	device_set_wakeup_capable(dev, true);
	pm_runसमय_put(dev);

	वापस 0;

depopulate:
	of_platक्रमm_depopulate(dev);
err_node_put:
	of_node_put(dwc3_np);
disable_rpm:
	pm_runसमय_disable(dev);
	pm_runसमय_put_noidle(dev);
disable_clks:
	clk_disable_unprepare(dwc3_imx->suspend_clk);
disable_hsio_clk:
	clk_disable_unprepare(dwc3_imx->hsio_clk);

	वापस err;
पूर्ण

अटल पूर्णांक dwc3_imx8mp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dwc3_imx8mp *dwc3_imx = platक्रमm_get_drvdata(pdev);
	काष्ठा device *dev = &pdev->dev;

	pm_runसमय_get_sync(dev);
	of_platक्रमm_depopulate(dev);

	clk_disable_unprepare(dwc3_imx->suspend_clk);
	clk_disable_unprepare(dwc3_imx->hsio_clk);

	pm_runसमय_disable(dev);
	pm_runसमय_put_noidle(dev);
	platक्रमm_set_drvdata(pdev, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused dwc3_imx8mp_suspend(काष्ठा dwc3_imx8mp *dwc3_imx,
					      pm_message_t msg)
अणु
	अगर (dwc3_imx->pm_suspended)
		वापस 0;

	/* Wakeup enable */
	अगर (PMSG_IS_AUTO(msg) || device_may_wakeup(dwc3_imx->dev))
		dwc3_imx8mp_wakeup_enable(dwc3_imx);

	dwc3_imx->pm_suspended = true;

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused dwc3_imx8mp_resume(काष्ठा dwc3_imx8mp *dwc3_imx,
					     pm_message_t msg)
अणु
	काष्ठा dwc3	*dwc = platक्रमm_get_drvdata(dwc3_imx->dwc3);
	पूर्णांक ret = 0;

	अगर (!dwc3_imx->pm_suspended)
		वापस 0;

	/* Wakeup disable */
	dwc3_imx8mp_wakeup_disable(dwc3_imx);
	dwc3_imx->pm_suspended = false;

	अगर (dwc3_imx->wakeup_pending) अणु
		dwc3_imx->wakeup_pending = false;
		अगर (dwc->current_dr_role == DWC3_GCTL_PRTCAP_DEVICE) अणु
			pm_runसमय_mark_last_busy(dwc->dev);
			pm_runसमय_put_स्वतःsuspend(dwc->dev);
		पूर्ण अन्यथा अणु
			/*
			 * Add रुको क्रम xhci चयन from suspend
			 * घड़ी to normal घड़ी to detect connection.
			 */
			usleep_range(9000, 10000);
		पूर्ण
		enable_irq(dwc3_imx->irq);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused dwc3_imx8mp_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा dwc3_imx8mp *dwc3_imx = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = dwc3_imx8mp_suspend(dwc3_imx, PMSG_SUSPEND);

	अगर (device_may_wakeup(dwc3_imx->dev))
		enable_irq_wake(dwc3_imx->irq);
	अन्यथा
		clk_disable_unprepare(dwc3_imx->suspend_clk);

	clk_disable_unprepare(dwc3_imx->hsio_clk);
	dev_dbg(dev, "dwc3 imx8mp pm suspend.\n");

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused dwc3_imx8mp_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा dwc3_imx8mp *dwc3_imx = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (device_may_wakeup(dwc3_imx->dev)) अणु
		disable_irq_wake(dwc3_imx->irq);
	पूर्ण अन्यथा अणु
		ret = clk_prepare_enable(dwc3_imx->suspend_clk);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = clk_prepare_enable(dwc3_imx->hsio_clk);
	अगर (ret)
		वापस ret;

	ret = dwc3_imx8mp_resume(dwc3_imx, PMSG_RESUME);

	pm_runसमय_disable(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);

	dev_dbg(dev, "dwc3 imx8mp pm resume.\n");

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused dwc3_imx8mp_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा dwc3_imx8mp *dwc3_imx = dev_get_drvdata(dev);

	dev_dbg(dev, "dwc3 imx8mp runtime suspend.\n");

	वापस dwc3_imx8mp_suspend(dwc3_imx, PMSG_AUTO_SUSPEND);
पूर्ण

अटल पूर्णांक __maybe_unused dwc3_imx8mp_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा dwc3_imx8mp *dwc3_imx = dev_get_drvdata(dev);

	dev_dbg(dev, "dwc3 imx8mp runtime resume.\n");

	वापस dwc3_imx8mp_resume(dwc3_imx, PMSG_AUTO_RESUME);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops dwc3_imx8mp_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(dwc3_imx8mp_pm_suspend, dwc3_imx8mp_pm_resume)
	SET_RUNTIME_PM_OPS(dwc3_imx8mp_runसमय_suspend,
			   dwc3_imx8mp_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id dwc3_imx8mp_of_match[] = अणु
	अणु .compatible = "fsl,imx8mp-dwc3", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, dwc3_imx8mp_of_match);

अटल काष्ठा platक्रमm_driver dwc3_imx8mp_driver = अणु
	.probe		= dwc3_imx8mp_probe,
	.हटाओ		= dwc3_imx8mp_हटाओ,
	.driver		= अणु
		.name	= "imx8mp-dwc3",
		.pm	= &dwc3_imx8mp_dev_pm_ops,
		.of_match_table	= dwc3_imx8mp_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(dwc3_imx8mp_driver);

MODULE_ALIAS("platform:imx8mp-dwc3");
MODULE_AUTHOR("jun.li@nxp.com");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("DesignWare USB3 imx8mp Glue Layer");
