<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * dwc3-keystone.c - Keystone Specअगरic Glue layer
 *
 * Copyright (C) 2010-2013 Texas Instruments Incorporated - https://www.ti.com
 *
 * Author: WingMan Kwok <w-kwok2@ti.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/pm_runसमय.स>

/* USBSS रेजिस्टर offsets */
#घोषणा USBSS_REVISION		0x0000
#घोषणा USBSS_SYSCONFIG		0x0010
#घोषणा USBSS_IRQ_EOI		0x0018
#घोषणा USBSS_IRQSTATUS_RAW_0	0x0020
#घोषणा USBSS_IRQSTATUS_0	0x0024
#घोषणा USBSS_IRQENABLE_SET_0	0x0028
#घोषणा USBSS_IRQENABLE_CLR_0	0x002c

/* IRQ रेजिस्टर bits */
#घोषणा USBSS_IRQ_EOI_LINE(n)	BIT(n)
#घोषणा USBSS_IRQ_EVENT_ST	BIT(0)
#घोषणा USBSS_IRQ_COREIRQ_EN	BIT(0)
#घोषणा USBSS_IRQ_COREIRQ_CLR	BIT(0)

काष्ठा dwc3_keystone अणु
	काष्ठा device			*dev;
	व्योम __iomem			*usbss;
	काष्ठा phy			*usb3_phy;
पूर्ण;

अटल अंतरभूत u32 kdwc3_पढ़ोl(व्योम __iomem *base, u32 offset)
अणु
	वापस पढ़ोl(base + offset);
पूर्ण

अटल अंतरभूत व्योम kdwc3_ग_लिखोl(व्योम __iomem *base, u32 offset, u32 value)
अणु
	ग_लिखोl(value, base + offset);
पूर्ण

अटल व्योम kdwc3_enable_irqs(काष्ठा dwc3_keystone *kdwc)
अणु
	u32 val;

	val = kdwc3_पढ़ोl(kdwc->usbss, USBSS_IRQENABLE_SET_0);
	val |= USBSS_IRQ_COREIRQ_EN;
	kdwc3_ग_लिखोl(kdwc->usbss, USBSS_IRQENABLE_SET_0, val);
पूर्ण

अटल व्योम kdwc3_disable_irqs(काष्ठा dwc3_keystone *kdwc)
अणु
	u32 val;

	val = kdwc3_पढ़ोl(kdwc->usbss, USBSS_IRQENABLE_SET_0);
	val &= ~USBSS_IRQ_COREIRQ_EN;
	kdwc3_ग_लिखोl(kdwc->usbss, USBSS_IRQENABLE_SET_0, val);
पूर्ण

अटल irqवापस_t dwc3_keystone_पूर्णांकerrupt(पूर्णांक irq, व्योम *_kdwc)
अणु
	काष्ठा dwc3_keystone	*kdwc = _kdwc;

	kdwc3_ग_लिखोl(kdwc->usbss, USBSS_IRQENABLE_CLR_0, USBSS_IRQ_COREIRQ_CLR);
	kdwc3_ग_लिखोl(kdwc->usbss, USBSS_IRQSTATUS_0, USBSS_IRQ_EVENT_ST);
	kdwc3_ग_लिखोl(kdwc->usbss, USBSS_IRQENABLE_SET_0, USBSS_IRQ_COREIRQ_EN);
	kdwc3_ग_लिखोl(kdwc->usbss, USBSS_IRQ_EOI, USBSS_IRQ_EOI_LINE(0));

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक kdwc3_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device		*dev = &pdev->dev;
	काष्ठा device_node	*node = pdev->dev.of_node;
	काष्ठा dwc3_keystone	*kdwc;
	पूर्णांक			error, irq;

	kdwc = devm_kzalloc(dev, माप(*kdwc), GFP_KERNEL);
	अगर (!kdwc)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, kdwc);

	kdwc->dev = dev;

	kdwc->usbss = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(kdwc->usbss))
		वापस PTR_ERR(kdwc->usbss);

	/* PSC dependency on AM65 needs SERDES0 to be घातered beक्रमe USB0 */
	kdwc->usb3_phy = devm_phy_optional_get(dev, "usb3-phy");
	अगर (IS_ERR(kdwc->usb3_phy))
		वापस dev_err_probe(dev, PTR_ERR(kdwc->usb3_phy), "couldn't get usb3 phy\n");

	phy_pm_runसमय_get_sync(kdwc->usb3_phy);

	error = phy_reset(kdwc->usb3_phy);
	अगर (error < 0) अणु
		dev_err(dev, "usb3 phy reset failed: %d\n", error);
		वापस error;
	पूर्ण

	error = phy_init(kdwc->usb3_phy);
	अगर (error < 0) अणु
		dev_err(dev, "usb3 phy init failed: %d\n", error);
		वापस error;
	पूर्ण

	error = phy_घातer_on(kdwc->usb3_phy);
	अगर (error < 0) अणु
		dev_err(dev, "usb3 phy power on failed: %d\n", error);
		phy_निकास(kdwc->usb3_phy);
		वापस error;
	पूर्ण

	pm_runसमय_enable(kdwc->dev);
	error = pm_runसमय_get_sync(kdwc->dev);
	अगर (error < 0) अणु
		dev_err(kdwc->dev, "pm_runtime_get_sync failed, error %d\n",
			error);
		जाओ err_irq;
	पूर्ण

	/* IRQ processing not required currently क्रम AM65 */
	अगर (of_device_is_compatible(node, "ti,am654-dwc3"))
		जाओ skip_irq;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		error = irq;
		जाओ err_irq;
	पूर्ण

	error = devm_request_irq(dev, irq, dwc3_keystone_पूर्णांकerrupt, IRQF_SHARED,
			dev_name(dev), kdwc);
	अगर (error) अणु
		dev_err(dev, "failed to request IRQ #%d --> %d\n",
				irq, error);
		जाओ err_irq;
	पूर्ण

	kdwc3_enable_irqs(kdwc);

skip_irq:
	error = of_platक्रमm_populate(node, शून्य, शून्य, dev);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to create dwc3 core\n");
		जाओ err_core;
	पूर्ण

	वापस 0;

err_core:
	kdwc3_disable_irqs(kdwc);
err_irq:
	pm_runसमय_put_sync(kdwc->dev);
	pm_runसमय_disable(kdwc->dev);
	phy_घातer_off(kdwc->usb3_phy);
	phy_निकास(kdwc->usb3_phy);
	phy_pm_runसमय_put_sync(kdwc->usb3_phy);

	वापस error;
पूर्ण

अटल पूर्णांक kdwc3_हटाओ_core(काष्ठा device *dev, व्योम *c)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);

	platक्रमm_device_unरेजिस्टर(pdev);

	वापस 0;
पूर्ण

अटल पूर्णांक kdwc3_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dwc3_keystone *kdwc = platक्रमm_get_drvdata(pdev);
	काष्ठा device_node *node = pdev->dev.of_node;

	अगर (!of_device_is_compatible(node, "ti,am654-dwc3"))
		kdwc3_disable_irqs(kdwc);

	device_क्रम_each_child(&pdev->dev, शून्य, kdwc3_हटाओ_core);
	pm_runसमय_put_sync(kdwc->dev);
	pm_runसमय_disable(kdwc->dev);

	phy_घातer_off(kdwc->usb3_phy);
	phy_निकास(kdwc->usb3_phy);
	phy_pm_runसमय_put_sync(kdwc->usb3_phy);

	platक्रमm_set_drvdata(pdev, शून्य);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id kdwc3_of_match[] = अणु
	अणु .compatible = "ti,keystone-dwc3", पूर्ण,
	अणु .compatible = "ti,am654-dwc3" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, kdwc3_of_match);

अटल काष्ठा platक्रमm_driver kdwc3_driver = अणु
	.probe		= kdwc3_probe,
	.हटाओ		= kdwc3_हटाओ,
	.driver		= अणु
		.name	= "keystone-dwc3",
		.of_match_table	= kdwc3_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(kdwc3_driver);

MODULE_ALIAS("platform:keystone-dwc3");
MODULE_AUTHOR("WingMan Kwok <w-kwok2@ti.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("DesignWare USB3 KEYSTONE Glue Layer");
