<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Ingenic JZ4740 "glue layer"
 *
 * Copyright (C) 2013, Apelete Seketeli <apelete@seketeli.net>
 */

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/usb/role.h>
#समावेश <linux/usb/usb_phy_generic.h>

#समावेश "musb_core.h"

काष्ठा jz4740_glue अणु
	काष्ठा platक्रमm_device	*pdev;
	काष्ठा musb		*musb;
	काष्ठा clk		*clk;
	काष्ठा usb_role_चयन	*role_sw;
पूर्ण;

अटल irqवापस_t jz4740_musb_पूर्णांकerrupt(पूर्णांक irq, व्योम *__hci)
अणु
	अचिन्हित दीर्घ	flags;
	irqवापस_t	retval = IRQ_NONE, retval_dma = IRQ_NONE;
	काष्ठा musb	*musb = __hci;

	अगर (IS_ENABLED(CONFIG_USB_INVENTRA_DMA) && musb->dma_controller)
		retval_dma = dma_controller_irq(irq, musb->dma_controller);

	spin_lock_irqsave(&musb->lock, flags);

	musb->पूर्णांक_usb = musb_पढ़ोb(musb->mregs, MUSB_INTRUSB);
	musb->पूर्णांक_tx = musb_पढ़ोw(musb->mregs, MUSB_INTRTX);
	musb->पूर्णांक_rx = musb_पढ़ोw(musb->mregs, MUSB_INTRRX);

	/*
	 * The controller is gadget only, the state of the host mode IRQ bits is
	 * undefined. Mask them to make sure that the musb driver core will
	 * never see them set
	 */
	musb->पूर्णांक_usb &= MUSB_INTR_SUSPEND | MUSB_INTR_RESUME |
			 MUSB_INTR_RESET | MUSB_INTR_SOF;

	अगर (musb->पूर्णांक_usb || musb->पूर्णांक_tx || musb->पूर्णांक_rx)
		retval = musb_पूर्णांकerrupt(musb);

	spin_unlock_irqrestore(&musb->lock, flags);

	अगर (retval == IRQ_HANDLED || retval_dma == IRQ_HANDLED)
		वापस IRQ_HANDLED;

	वापस IRQ_NONE;
पूर्ण

अटल काष्ठा musb_fअगरo_cfg jz4740_musb_fअगरo_cfg[] = अणु
	अणु .hw_ep_num = 1, .style = FIFO_TX, .maxpacket = 512, पूर्ण,
	अणु .hw_ep_num = 1, .style = FIFO_RX, .maxpacket = 512, पूर्ण,
	अणु .hw_ep_num = 2, .style = FIFO_TX, .maxpacket = 64, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा musb_hdrc_config jz4740_musb_config = अणु
	/* Silicon करोes not implement USB OTG. */
	.multipoपूर्णांक	= 0,
	/* Max EPs scanned, driver will decide which EP can be used. */
	.num_eps	= 4,
	/* RAMbits needed to configure EPs from table */
	.ram_bits	= 9,
	.fअगरo_cfg	= jz4740_musb_fअगरo_cfg,
	.fअगरo_cfg_size	= ARRAY_SIZE(jz4740_musb_fअगरo_cfg),
पूर्ण;

अटल पूर्णांक jz4740_musb_role_चयन_set(काष्ठा usb_role_चयन *sw,
				       क्रमागत usb_role role)
अणु
	काष्ठा jz4740_glue *glue = usb_role_चयन_get_drvdata(sw);
	काष्ठा usb_phy *phy = glue->musb->xceiv;

	चयन (role) अणु
	हाल USB_ROLE_NONE:
		atomic_notअगरier_call_chain(&phy->notअगरier, USB_EVENT_NONE, phy);
		अवरोध;
	हाल USB_ROLE_DEVICE:
		atomic_notअगरier_call_chain(&phy->notअगरier, USB_EVENT_VBUS, phy);
		अवरोध;
	हाल USB_ROLE_HOST:
		atomic_notअगरier_call_chain(&phy->notअगरier, USB_EVENT_ID, phy);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक jz4740_musb_init(काष्ठा musb *musb)
अणु
	काष्ठा device *dev = musb->controller->parent;
	काष्ठा jz4740_glue *glue = dev_get_drvdata(dev);
	काष्ठा usb_role_चयन_desc role_sw_desc = अणु
		.set = jz4740_musb_role_चयन_set,
		.driver_data = glue,
		.fwnode = dev_fwnode(dev),
	पूर्ण;
	पूर्णांक err;

	glue->musb = musb;

	अगर (dev->of_node)
		musb->xceiv = devm_usb_get_phy_by_phandle(dev, "phys", 0);
	अन्यथा
		musb->xceiv = devm_usb_get_phy(dev, USB_PHY_TYPE_USB2);
	अगर (IS_ERR(musb->xceiv)) अणु
		err = PTR_ERR(musb->xceiv);
		अगर (err != -EPROBE_DEFER)
			dev_err(dev, "No transceiver configured: %d\n", err);
		वापस err;
	पूर्ण

	glue->role_sw = usb_role_चयन_रेजिस्टर(dev, &role_sw_desc);
	अगर (IS_ERR(glue->role_sw)) अणु
		dev_err(dev, "Failed to register USB role switch\n");
		वापस PTR_ERR(glue->role_sw);
	पूर्ण

	/*
	 * Silicon करोes not implement ConfigData रेजिस्टर.
	 * Set dyn_fअगरo to aव्योम पढ़ोing EP config from hardware.
	 */
	musb->dyn_fअगरo = true;

	musb->isr = jz4740_musb_पूर्णांकerrupt;

	वापस 0;
पूर्ण

अटल पूर्णांक jz4740_musb_निकास(काष्ठा musb *musb)
अणु
	काष्ठा jz4740_glue *glue = dev_get_drvdata(musb->controller->parent);

	usb_role_चयन_unरेजिस्टर(glue->role_sw);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा musb_platक्रमm_ops jz4740_musb_ops = अणु
	.quirks		= MUSB_DMA_INVENTRA | MUSB_INDEXED_EP,
	.fअगरo_mode	= 2,
	.init		= jz4740_musb_init,
	.निकास		= jz4740_musb_निकास,
#अगर_घोषित CONFIG_USB_INVENTRA_DMA
	.dma_init	= musbhs_dma_controller_create_noirq,
	.dma_निकास	= musbhs_dma_controller_destroy,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा musb_hdrc_platक्रमm_data jz4740_musb_pdata = अणु
	.mode		= MUSB_PERIPHERAL,
	.config		= &jz4740_musb_config,
	.platक्रमm_ops	= &jz4740_musb_ops,
पूर्ण;

अटल काष्ठा musb_fअगरo_cfg jz4770_musb_fअगरo_cfg[] = अणु
	अणु .hw_ep_num = 1, .style = FIFO_TX, .maxpacket = 512, पूर्ण,
	अणु .hw_ep_num = 1, .style = FIFO_RX, .maxpacket = 512, पूर्ण,
	अणु .hw_ep_num = 2, .style = FIFO_TX, .maxpacket = 512, पूर्ण,
	अणु .hw_ep_num = 2, .style = FIFO_RX, .maxpacket = 512, पूर्ण,
	अणु .hw_ep_num = 3, .style = FIFO_TX, .maxpacket = 512, पूर्ण,
	अणु .hw_ep_num = 3, .style = FIFO_RX, .maxpacket = 512, पूर्ण,
	अणु .hw_ep_num = 4, .style = FIFO_TX, .maxpacket = 512, पूर्ण,
	अणु .hw_ep_num = 4, .style = FIFO_RX, .maxpacket = 512, पूर्ण,
	अणु .hw_ep_num = 5, .style = FIFO_TX, .maxpacket = 512, पूर्ण,
	अणु .hw_ep_num = 5, .style = FIFO_RX, .maxpacket = 512, पूर्ण,
पूर्ण;

अटल काष्ठा musb_hdrc_config jz4770_musb_config = अणु
	.multipoपूर्णांक	= 1,
	.num_eps	= 11,
	.ram_bits	= 11,
	.fअगरo_cfg	= jz4770_musb_fअगरo_cfg,
	.fअगरo_cfg_size	= ARRAY_SIZE(jz4770_musb_fअगरo_cfg),
पूर्ण;

अटल स्थिर काष्ठा musb_hdrc_platक्रमm_data jz4770_musb_pdata = अणु
	.mode		= MUSB_PERIPHERAL, /* TODO: support OTG */
	.config		= &jz4770_musb_config,
	.platक्रमm_ops	= &jz4740_musb_ops,
पूर्ण;

अटल पूर्णांक jz4740_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device			*dev = &pdev->dev;
	स्थिर काष्ठा musb_hdrc_platक्रमm_data *pdata;
	काष्ठा platक्रमm_device		*musb;
	काष्ठा jz4740_glue		*glue;
	काष्ठा clk			*clk;
	पूर्णांक				ret;

	glue = devm_kzalloc(dev, माप(*glue), GFP_KERNEL);
	अगर (!glue)
		वापस -ENOMEM;

	pdata = of_device_get_match_data(dev);
	अगर (!pdata) अणु
		dev_err(dev, "missing platform data\n");
		वापस -EINVAL;
	पूर्ण

	musb = platक्रमm_device_alloc("musb-hdrc", PLATFORM_DEVID_AUTO);
	अगर (!musb) अणु
		dev_err(dev, "failed to allocate musb device\n");
		वापस -ENOMEM;
	पूर्ण

	clk = devm_clk_get(dev, "udc");
	अगर (IS_ERR(clk)) अणु
		dev_err(dev, "failed to get clock\n");
		ret = PTR_ERR(clk);
		जाओ err_platक्रमm_device_put;
	पूर्ण

	ret = clk_prepare_enable(clk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable clock\n");
		जाओ err_platक्रमm_device_put;
	पूर्ण

	musb->dev.parent		= dev;
	musb->dev.dma_mask		= &musb->dev.coherent_dma_mask;
	musb->dev.coherent_dma_mask	= DMA_BIT_MASK(32);

	glue->pdev			= musb;
	glue->clk			= clk;

	platक्रमm_set_drvdata(pdev, glue);

	ret = platक्रमm_device_add_resources(musb, pdev->resource,
					    pdev->num_resources);
	अगर (ret) अणु
		dev_err(dev, "failed to add resources\n");
		जाओ err_clk_disable;
	पूर्ण

	ret = platक्रमm_device_add_data(musb, pdata, माप(*pdata));
	अगर (ret) अणु
		dev_err(dev, "failed to add platform_data\n");
		जाओ err_clk_disable;
	पूर्ण

	ret = platक्रमm_device_add(musb);
	अगर (ret) अणु
		dev_err(dev, "failed to register musb device\n");
		जाओ err_clk_disable;
	पूर्ण

	वापस 0;

err_clk_disable:
	clk_disable_unprepare(clk);
err_platक्रमm_device_put:
	platक्रमm_device_put(musb);
	वापस ret;
पूर्ण

अटल पूर्णांक jz4740_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा jz4740_glue *glue = platक्रमm_get_drvdata(pdev);

	platक्रमm_device_unरेजिस्टर(glue->pdev);
	clk_disable_unprepare(glue->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id jz4740_musb_of_match[] = अणु
	अणु .compatible = "ingenic,jz4740-musb", .data = &jz4740_musb_pdata पूर्ण,
	अणु .compatible = "ingenic,jz4770-musb", .data = &jz4770_musb_pdata पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, jz4740_musb_of_match);

अटल काष्ठा platक्रमm_driver jz4740_driver = अणु
	.probe		= jz4740_probe,
	.हटाओ		= jz4740_हटाओ,
	.driver		= अणु
		.name	= "musb-jz4740",
		.of_match_table = jz4740_musb_of_match,
	पूर्ण,
पूर्ण;

MODULE_DESCRIPTION("JZ4740 MUSB Glue Layer");
MODULE_AUTHOR("Apelete Seketeli <apelete@seketeli.net>");
MODULE_LICENSE("GPL v2");
module_platक्रमm_driver(jz4740_driver);
