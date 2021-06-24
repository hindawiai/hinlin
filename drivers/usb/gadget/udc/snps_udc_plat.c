<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * snps_udc_plat.c - Synopsys UDC Platक्रमm Driver
 *
 * Copyright (C) 2016 Broadcom
 */

#समावेश <linux/extcon.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/module.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/moduleparam.h>
#समावेश "amd5536udc.h"

/* description */
#घोषणा UDC_MOD_DESCRIPTION     "Synopsys UDC platform driver"

अटल व्योम start_udc(काष्ठा udc *udc)
अणु
	अगर (udc->driver) अणु
		dev_info(udc->dev, "Connecting...\n");
		udc_enable_dev_setup_पूर्णांकerrupts(udc);
		udc_basic_init(udc);
		udc->connected = 1;
	पूर्ण
पूर्ण

अटल व्योम stop_udc(काष्ठा udc *udc)
अणु
	पूर्णांक पंचांगp;
	u32 reg;

	spin_lock(&udc->lock);

	/* Flush the receieve fअगरo */
	reg = पढ़ोl(&udc->regs->ctl);
	reg |= AMD_BIT(UDC_DEVCTL_SRX_FLUSH);
	ग_लिखोl(reg, &udc->regs->ctl);

	reg = पढ़ोl(&udc->regs->ctl);
	reg &= ~(AMD_BIT(UDC_DEVCTL_SRX_FLUSH));
	ग_लिखोl(reg, &udc->regs->ctl);
	dev_dbg(udc->dev, "ep rx queue flushed\n");

	/* Mask पूर्णांकerrupts. Required more so when the
	 * UDC is connected to a DRD phy.
	 */
	udc_mask_unused_पूर्णांकerrupts(udc);

	/* Disconnect gadget driver */
	अगर (udc->driver) अणु
		spin_unlock(&udc->lock);
		udc->driver->disconnect(&udc->gadget);
		spin_lock(&udc->lock);

		/* empty queues */
		क्रम (पंचांगp = 0; पंचांगp < UDC_EP_NUM; पंचांगp++)
			empty_req_queue(&udc->ep[पंचांगp]);
	पूर्ण
	udc->connected = 0;

	spin_unlock(&udc->lock);
	dev_info(udc->dev, "Device disconnected\n");
पूर्ण

अटल व्योम udc_drd_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा udc *udc;

	udc = container_of(to_delayed_work(work),
			   काष्ठा udc, drd_work);

	अगर (udc->conn_type) अणु
		dev_dbg(udc->dev, "idle -> device\n");
		start_udc(udc);
	पूर्ण अन्यथा अणु
		dev_dbg(udc->dev, "device -> idle\n");
		stop_udc(udc);
	पूर्ण
पूर्ण

अटल पूर्णांक usbd_connect_notअगरy(काष्ठा notअगरier_block *self,
			       अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा udc *udc = container_of(self, काष्ठा udc, nb);

	dev_dbg(udc->dev, "%s: event: %lu\n", __func__, event);

	udc->conn_type = event;

	schedule_delayed_work(&udc->drd_work, 0);

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक udc_plat_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	काष्ठा udc *udc;
	पूर्णांक ret;

	udc = devm_kzalloc(dev, माप(*udc), GFP_KERNEL);
	अगर (!udc)
		वापस -ENOMEM;

	spin_lock_init(&udc->lock);
	udc->dev = dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	udc->virt_addr = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(udc->virt_addr))
		वापस PTR_ERR(udc->virt_addr);

	/* udc csr रेजिस्टरs base */
	udc->csr = udc->virt_addr + UDC_CSR_ADDR;

	/* dev रेजिस्टरs base */
	udc->regs = udc->virt_addr + UDC_DEVCFG_ADDR;

	/* ep रेजिस्टरs base */
	udc->ep_regs = udc->virt_addr + UDC_EPREGS_ADDR;

	/* fअगरo's base */
	udc->rxfअगरo = (u32 __iomem *)(udc->virt_addr + UDC_RXFIFO_ADDR);
	udc->txfअगरo = (u32 __iomem *)(udc->virt_addr + UDC_TXFIFO_ADDR);

	udc->phys_addr = (अचिन्हित दीर्घ)res->start;

	udc->irq = irq_of_parse_and_map(dev->of_node, 0);
	अगर (udc->irq <= 0) अणु
		dev_err(dev, "Can't parse and map interrupt\n");
		वापस -EINVAL;
	पूर्ण

	udc->udc_phy = devm_of_phy_get_by_index(dev, dev->of_node, 0);
	अगर (IS_ERR(udc->udc_phy)) अणु
		dev_err(dev, "Failed to obtain phy from device tree\n");
		वापस PTR_ERR(udc->udc_phy);
	पूर्ण

	ret = phy_init(udc->udc_phy);
	अगर (ret) अणु
		dev_err(dev, "UDC phy init failed");
		वापस ret;
	पूर्ण

	ret = phy_घातer_on(udc->udc_phy);
	अगर (ret) अणु
		dev_err(dev, "UDC phy power on failed");
		phy_निकास(udc->udc_phy);
		वापस ret;
	पूर्ण

	/* Register क्रम extcon अगर supported */
	अगर (of_get_property(dev->of_node, "extcon", शून्य)) अणु
		udc->edev = extcon_get_edev_by_phandle(dev, 0);
		अगर (IS_ERR(udc->edev)) अणु
			अगर (PTR_ERR(udc->edev) == -EPROBE_DEFER)
				वापस -EPROBE_DEFER;
			dev_err(dev, "Invalid or missing extcon\n");
			ret = PTR_ERR(udc->edev);
			जाओ निकास_phy;
		पूर्ण

		udc->nb.notअगरier_call = usbd_connect_notअगरy;
		ret = extcon_रेजिस्टर_notअगरier(udc->edev, EXTCON_USB,
					       &udc->nb);
		अगर (ret < 0) अणु
			dev_err(dev, "Can't register extcon device\n");
			जाओ निकास_phy;
		पूर्ण

		ret = extcon_get_state(udc->edev, EXTCON_USB);
		अगर (ret < 0) अणु
			dev_err(dev, "Can't get cable state\n");
			जाओ निकास_extcon;
		पूर्ण अन्यथा अगर (ret) अणु
			udc->conn_type = ret;
		पूर्ण
		INIT_DELAYED_WORK(&udc->drd_work, udc_drd_work);
	पूर्ण

	/* init dma pools */
	अगर (use_dma) अणु
		ret = init_dma_pools(udc);
		अगर (ret != 0)
			जाओ निकास_extcon;
	पूर्ण

	ret = devm_request_irq(dev, udc->irq, udc_irq, IRQF_SHARED,
			       "snps-udc", udc);
	अगर (ret < 0) अणु
		dev_err(dev, "Request irq %d failed for UDC\n", udc->irq);
		जाओ निकास_dma;
	पूर्ण

	platक्रमm_set_drvdata(pdev, udc);
	udc->chiprev = UDC_BCM_REV;

	अगर (udc_probe(udc)) अणु
		ret = -ENODEV;
		जाओ निकास_dma;
	पूर्ण
	dev_info(dev, "Synopsys UDC platform driver probe successful\n");

	वापस 0;

निकास_dma:
	अगर (use_dma)
		मुक्त_dma_pools(udc);
निकास_extcon:
	अगर (udc->edev)
		extcon_unरेजिस्टर_notअगरier(udc->edev, EXTCON_USB, &udc->nb);
निकास_phy:
	अगर (udc->udc_phy) अणु
		phy_घातer_off(udc->udc_phy);
		phy_निकास(udc->udc_phy);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक udc_plat_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा udc *dev;

	dev = platक्रमm_get_drvdata(pdev);

	usb_del_gadget_udc(&dev->gadget);
	/* gadget driver must not be रेजिस्टरed */
	अगर (WARN_ON(dev->driver))
		वापस 0;

	/* dma pool cleanup */
	मुक्त_dma_pools(dev);

	udc_हटाओ(dev);

	platक्रमm_set_drvdata(pdev, शून्य);

	अगर (dev->drd_wq) अणु
		flush_workqueue(dev->drd_wq);
		destroy_workqueue(dev->drd_wq);
	पूर्ण

	phy_घातer_off(dev->udc_phy);
	phy_निकास(dev->udc_phy);
	extcon_unरेजिस्टर_notअगरier(dev->edev, EXTCON_USB, &dev->nb);

	dev_info(&pdev->dev, "Synopsys UDC platform driver removed\n");

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक udc_plat_suspend(काष्ठा device *dev)
अणु
	काष्ठा udc *udc;

	udc = dev_get_drvdata(dev);
	stop_udc(udc);

	अगर (extcon_get_state(udc->edev, EXTCON_USB) > 0) अणु
		dev_dbg(udc->dev, "device -> idle\n");
		stop_udc(udc);
	पूर्ण
	phy_घातer_off(udc->udc_phy);
	phy_निकास(udc->udc_phy);

	वापस 0;
पूर्ण

अटल पूर्णांक udc_plat_resume(काष्ठा device *dev)
अणु
	काष्ठा udc *udc;
	पूर्णांक ret;

	udc = dev_get_drvdata(dev);

	ret = phy_init(udc->udc_phy);
	अगर (ret) अणु
		dev_err(udc->dev, "UDC phy init failure");
		वापस ret;
	पूर्ण

	ret = phy_घातer_on(udc->udc_phy);
	अगर (ret) अणु
		dev_err(udc->dev, "UDC phy power on failure");
		phy_निकास(udc->udc_phy);
		वापस ret;
	पूर्ण

	अगर (extcon_get_state(udc->edev, EXTCON_USB) > 0) अणु
		dev_dbg(udc->dev, "idle -> device\n");
		start_udc(udc);
	पूर्ण

	वापस 0;
पूर्ण
अटल स्थिर काष्ठा dev_pm_ops udc_plat_pm_ops = अणु
	.suspend	= udc_plat_suspend,
	.resume		= udc_plat_resume,
पूर्ण;
#पूर्ण_अगर

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id of_udc_match[] = अणु
	अणु .compatible = "brcm,ns2-udc", पूर्ण,
	अणु .compatible = "brcm,cygnus-udc", पूर्ण,
	अणु .compatible = "brcm,iproc-udc", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_udc_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver udc_plat_driver = अणु
	.probe		= udc_plat_probe,
	.हटाओ		= udc_plat_हटाओ,
	.driver		= अणु
		.name	= "snps-udc-plat",
		.of_match_table = of_match_ptr(of_udc_match),
#अगर_घोषित CONFIG_PM_SLEEP
		.pm	= &udc_plat_pm_ops,
#पूर्ण_अगर
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(udc_plat_driver);

MODULE_DESCRIPTION(UDC_MOD_DESCRIPTION);
MODULE_AUTHOR("Broadcom");
MODULE_LICENSE("GPL v2");
