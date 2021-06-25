<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019 MediaTek Inc.
 *
 * Author:
 *  Min Guo <min.guo@mediatek.com>
 *  Yongदीर्घ Wu <yongदीर्घ.wu@mediatek.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/usb/role.h>
#समावेश <linux/usb/usb_phy_generic.h>
#समावेश "musb_core.h"
#समावेश "musb_dma.h"

#घोषणा USB_L1INTS		0x00a0
#घोषणा USB_L1INTM		0x00a4
#घोषणा MTK_MUSB_TXFUNCADDR	0x0480

/* MediaTek controller toggle enable and status reg */
#घोषणा MUSB_RXTOG		0x80
#घोषणा MUSB_RXTOGEN		0x82
#घोषणा MUSB_TXTOG		0x84
#घोषणा MUSB_TXTOGEN		0x86
#घोषणा MTK_TOGGLE_EN		GENMASK(15, 0)

#घोषणा TX_INT_STATUS		BIT(0)
#घोषणा RX_INT_STATUS		BIT(1)
#घोषणा USBCOM_INT_STATUS	BIT(2)
#घोषणा DMA_INT_STATUS		BIT(3)

#घोषणा DMA_INTR_STATUS_MSK	GENMASK(7, 0)
#घोषणा DMA_INTR_UNMASK_SET_MSK	GENMASK(31, 24)

काष्ठा mtk_glue अणु
	काष्ठा device *dev;
	काष्ठा musb *musb;
	काष्ठा platक्रमm_device *musb_pdev;
	काष्ठा platक्रमm_device *usb_phy;
	काष्ठा phy *phy;
	काष्ठा usb_phy *xceiv;
	क्रमागत phy_mode phy_mode;
	काष्ठा clk *मुख्य;
	काष्ठा clk *mcu;
	काष्ठा clk *univpll;
	क्रमागत usb_role role;
	काष्ठा usb_role_चयन *role_sw;
पूर्ण;

अटल पूर्णांक mtk_musb_clks_get(काष्ठा mtk_glue *glue)
अणु
	काष्ठा device *dev = glue->dev;

	glue->मुख्य = devm_clk_get(dev, "main");
	अगर (IS_ERR(glue->मुख्य)) अणु
		dev_err(dev, "fail to get main clock\n");
		वापस PTR_ERR(glue->मुख्य);
	पूर्ण

	glue->mcu = devm_clk_get(dev, "mcu");
	अगर (IS_ERR(glue->mcu)) अणु
		dev_err(dev, "fail to get mcu clock\n");
		वापस PTR_ERR(glue->mcu);
	पूर्ण

	glue->univpll = devm_clk_get(dev, "univpll");
	अगर (IS_ERR(glue->univpll)) अणु
		dev_err(dev, "fail to get univpll clock\n");
		वापस PTR_ERR(glue->univpll);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_musb_clks_enable(काष्ठा mtk_glue *glue)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(glue->मुख्य);
	अगर (ret) अणु
		dev_err(glue->dev, "failed to enable main clock\n");
		जाओ err_मुख्य_clk;
	पूर्ण

	ret = clk_prepare_enable(glue->mcu);
	अगर (ret) अणु
		dev_err(glue->dev, "failed to enable mcu clock\n");
		जाओ err_mcu_clk;
	पूर्ण

	ret = clk_prepare_enable(glue->univpll);
	अगर (ret) अणु
		dev_err(glue->dev, "failed to enable univpll clock\n");
		जाओ err_univpll_clk;
	पूर्ण

	वापस 0;

err_univpll_clk:
	clk_disable_unprepare(glue->mcu);
err_mcu_clk:
	clk_disable_unprepare(glue->मुख्य);
err_मुख्य_clk:
	वापस ret;
पूर्ण

अटल व्योम mtk_musb_clks_disable(काष्ठा mtk_glue *glue)
अणु
	clk_disable_unprepare(glue->univpll);
	clk_disable_unprepare(glue->mcu);
	clk_disable_unprepare(glue->मुख्य);
पूर्ण

अटल पूर्णांक mtk_otg_चयन_set(काष्ठा mtk_glue *glue, क्रमागत usb_role role)
अणु
	काष्ठा musb *musb = glue->musb;
	u8 devctl = पढ़ोb(musb->mregs + MUSB_DEVCTL);
	क्रमागत usb_role new_role;

	अगर (role == glue->role)
		वापस 0;

	चयन (role) अणु
	हाल USB_ROLE_HOST:
		musb->xceiv->otg->state = OTG_STATE_A_WAIT_VRISE;
		glue->phy_mode = PHY_MODE_USB_HOST;
		new_role = USB_ROLE_HOST;
		अगर (glue->role == USB_ROLE_NONE)
			phy_घातer_on(glue->phy);

		devctl |= MUSB_DEVCTL_SESSION;
		musb_ग_लिखोb(musb->mregs, MUSB_DEVCTL, devctl);
		MUSB_HST_MODE(musb);
		अवरोध;
	हाल USB_ROLE_DEVICE:
		musb->xceiv->otg->state = OTG_STATE_B_IDLE;
		glue->phy_mode = PHY_MODE_USB_DEVICE;
		new_role = USB_ROLE_DEVICE;
		devctl &= ~MUSB_DEVCTL_SESSION;
		musb_ग_लिखोb(musb->mregs, MUSB_DEVCTL, devctl);
		अगर (glue->role == USB_ROLE_NONE)
			phy_घातer_on(glue->phy);

		MUSB_DEV_MODE(musb);
		अवरोध;
	हाल USB_ROLE_NONE:
		glue->phy_mode = PHY_MODE_USB_OTG;
		new_role = USB_ROLE_NONE;
		devctl &= ~MUSB_DEVCTL_SESSION;
		musb_ग_लिखोb(musb->mregs, MUSB_DEVCTL, devctl);
		अगर (glue->role != USB_ROLE_NONE)
			phy_घातer_off(glue->phy);

		अवरोध;
	शेष:
		dev_err(glue->dev, "Invalid State\n");
		वापस -EINVAL;
	पूर्ण

	glue->role = new_role;
	phy_set_mode(glue->phy, glue->phy_mode);

	वापस 0;
पूर्ण

अटल पूर्णांक musb_usb_role_sx_set(काष्ठा usb_role_चयन *sw, क्रमागत usb_role role)
अणु
	वापस mtk_otg_चयन_set(usb_role_चयन_get_drvdata(sw), role);
पूर्ण

अटल क्रमागत usb_role musb_usb_role_sx_get(काष्ठा usb_role_चयन *sw)
अणु
	काष्ठा mtk_glue *glue = usb_role_चयन_get_drvdata(sw);

	वापस glue->role;
पूर्ण

अटल पूर्णांक mtk_otg_चयन_init(काष्ठा mtk_glue *glue)
अणु
	काष्ठा usb_role_चयन_desc role_sx_desc = अणु 0 पूर्ण;

	role_sx_desc.set = musb_usb_role_sx_set;
	role_sx_desc.get = musb_usb_role_sx_get;
	role_sx_desc.fwnode = dev_fwnode(glue->dev);
	role_sx_desc.driver_data = glue;
	glue->role_sw = usb_role_चयन_रेजिस्टर(glue->dev, &role_sx_desc);

	वापस PTR_ERR_OR_ZERO(glue->role_sw);
पूर्ण

अटल व्योम mtk_otg_चयन_निकास(काष्ठा mtk_glue *glue)
अणु
	वापस usb_role_चयन_unरेजिस्टर(glue->role_sw);
पूर्ण

अटल irqवापस_t generic_पूर्णांकerrupt(पूर्णांक irq, व्योम *__hci)
अणु
	अचिन्हित दीर्घ flags;
	irqवापस_t retval = IRQ_NONE;
	काष्ठा musb *musb = __hci;

	spin_lock_irqsave(&musb->lock, flags);
	musb->पूर्णांक_usb = musb_clearb(musb->mregs, MUSB_INTRUSB);
	musb->पूर्णांक_rx = musb_clearw(musb->mregs, MUSB_INTRRX);
	musb->पूर्णांक_tx = musb_clearw(musb->mregs, MUSB_INTRTX);

	अगर ((musb->पूर्णांक_usb & MUSB_INTR_RESET) && !is_host_active(musb)) अणु
		/* ep0 FADDR must be 0 when (re)entering peripheral mode */
		musb_ep_select(musb->mregs, 0);
		musb_ग_लिखोb(musb->mregs, MUSB_FADDR, 0);
	पूर्ण

	अगर (musb->पूर्णांक_usb || musb->पूर्णांक_tx || musb->पूर्णांक_rx)
		retval = musb_पूर्णांकerrupt(musb);

	spin_unlock_irqrestore(&musb->lock, flags);

	वापस retval;
पूर्ण

अटल irqवापस_t mtk_musb_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	irqवापस_t retval = IRQ_NONE;
	काष्ठा musb *musb = (काष्ठा musb *)dev_id;
	u32 l1_पूर्णांकs;

	l1_पूर्णांकs = musb_पढ़ोl(musb->mregs, USB_L1INTS) &
			musb_पढ़ोl(musb->mregs, USB_L1INTM);

	अगर (l1_पूर्णांकs & (TX_INT_STATUS | RX_INT_STATUS | USBCOM_INT_STATUS))
		retval = generic_पूर्णांकerrupt(irq, musb);

#अगर defined(CONFIG_USB_INVENTRA_DMA)
	अगर (l1_पूर्णांकs & DMA_INT_STATUS)
		retval = dma_controller_irq(irq, musb->dma_controller);
#पूर्ण_अगर
	वापस retval;
पूर्ण

अटल u32 mtk_musb_busctl_offset(u8 epnum, u16 offset)
अणु
	वापस MTK_MUSB_TXFUNCADDR + offset + 8 * epnum;
पूर्ण

अटल u8 mtk_musb_clearb(व्योम __iomem *addr, अचिन्हित पूर्णांक offset)
अणु
	u8 data;

	/* W1C */
	data = musb_पढ़ोb(addr, offset);
	musb_ग_लिखोb(addr, offset, data);
	वापस data;
पूर्ण

अटल u16 mtk_musb_clearw(व्योम __iomem *addr, अचिन्हित पूर्णांक offset)
अणु
	u16 data;

	/* W1C */
	data = musb_पढ़ोw(addr, offset);
	musb_ग_लिखोw(addr, offset, data);
	वापस data;
पूर्ण

अटल पूर्णांक mtk_musb_set_mode(काष्ठा musb *musb, u8 mode)
अणु
	काष्ठा device *dev = musb->controller;
	काष्ठा mtk_glue *glue = dev_get_drvdata(dev->parent);
	क्रमागत phy_mode new_mode;
	क्रमागत usb_role new_role;

	चयन (mode) अणु
	हाल MUSB_HOST:
		new_mode = PHY_MODE_USB_HOST;
		new_role = USB_ROLE_HOST;
		अवरोध;
	हाल MUSB_PERIPHERAL:
		new_mode = PHY_MODE_USB_DEVICE;
		new_role = USB_ROLE_DEVICE;
		अवरोध;
	हाल MUSB_OTG:
		new_mode = PHY_MODE_USB_OTG;
		new_role = USB_ROLE_NONE;
		अवरोध;
	शेष:
		dev_err(glue->dev, "Invalid mode request\n");
		वापस -EINVAL;
	पूर्ण

	अगर (glue->phy_mode == new_mode)
		वापस 0;

	अगर (musb->port_mode != MUSB_OTG) अणु
		dev_err(glue->dev, "Does not support changing modes\n");
		वापस -EINVAL;
	पूर्ण

	mtk_otg_चयन_set(glue, new_role);
	वापस 0;
पूर्ण

अटल पूर्णांक mtk_musb_init(काष्ठा musb *musb)
अणु
	काष्ठा device *dev = musb->controller;
	काष्ठा mtk_glue *glue = dev_get_drvdata(dev->parent);
	पूर्णांक ret;

	glue->musb = musb;
	musb->phy = glue->phy;
	musb->xceiv = glue->xceiv;
	musb->is_host = false;
	musb->isr = mtk_musb_पूर्णांकerrupt;

	/* Set TX/RX toggle enable */
	musb_ग_लिखोw(musb->mregs, MUSB_TXTOGEN, MTK_TOGGLE_EN);
	musb_ग_लिखोw(musb->mregs, MUSB_RXTOGEN, MTK_TOGGLE_EN);

	अगर (musb->port_mode == MUSB_OTG) अणु
		ret = mtk_otg_चयन_init(glue);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = phy_init(glue->phy);
	अगर (ret)
		जाओ err_phy_init;

	ret = phy_घातer_on(glue->phy);
	अगर (ret)
		जाओ err_phy_घातer_on;

	phy_set_mode(glue->phy, glue->phy_mode);

#अगर defined(CONFIG_USB_INVENTRA_DMA)
	musb_ग_लिखोl(musb->mregs, MUSB_HSDMA_INTR,
		    DMA_INTR_STATUS_MSK | DMA_INTR_UNMASK_SET_MSK);
#पूर्ण_अगर
	musb_ग_लिखोl(musb->mregs, USB_L1INTM, TX_INT_STATUS | RX_INT_STATUS |
		    USBCOM_INT_STATUS | DMA_INT_STATUS);
	वापस 0;

err_phy_घातer_on:
	phy_निकास(glue->phy);
err_phy_init:
	mtk_otg_चयन_निकास(glue);
	वापस ret;
पूर्ण

अटल u16 mtk_musb_get_toggle(काष्ठा musb_qh *qh, पूर्णांक is_out)
अणु
	काष्ठा musb *musb = qh->hw_ep->musb;
	u8 epnum = qh->hw_ep->epnum;
	u16 toggle;

	toggle = musb_पढ़ोw(musb->mregs, is_out ? MUSB_TXTOG : MUSB_RXTOG);
	वापस toggle & (1 << epnum);
पूर्ण

अटल u16 mtk_musb_set_toggle(काष्ठा musb_qh *qh, पूर्णांक is_out, काष्ठा urb *urb)
अणु
	काष्ठा musb *musb = qh->hw_ep->musb;
	u8 epnum = qh->hw_ep->epnum;
	u16 value, toggle;

	toggle = usb_gettoggle(urb->dev, qh->epnum, is_out);

	अगर (is_out) अणु
		value = musb_पढ़ोw(musb->mregs, MUSB_TXTOG);
		value |= toggle << epnum;
		musb_ग_लिखोw(musb->mregs, MUSB_TXTOG, value);
	पूर्ण अन्यथा अणु
		value = musb_पढ़ोw(musb->mregs, MUSB_RXTOG);
		value |= toggle << epnum;
		musb_ग_लिखोw(musb->mregs, MUSB_RXTOG, value);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_musb_निकास(काष्ठा musb *musb)
अणु
	काष्ठा device *dev = musb->controller;
	काष्ठा mtk_glue *glue = dev_get_drvdata(dev->parent);

	mtk_otg_चयन_निकास(glue);
	phy_घातer_off(glue->phy);
	phy_निकास(glue->phy);
	mtk_musb_clks_disable(glue);

	pm_runसमय_put_sync(dev);
	pm_runसमय_disable(dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा musb_platक्रमm_ops mtk_musb_ops = अणु
	.quirks = MUSB_DMA_INVENTRA,
	.init = mtk_musb_init,
	.get_toggle = mtk_musb_get_toggle,
	.set_toggle = mtk_musb_set_toggle,
	.निकास = mtk_musb_निकास,
#अगर_घोषित CONFIG_USB_INVENTRA_DMA
	.dma_init = musbhs_dma_controller_create_noirq,
	.dma_निकास = musbhs_dma_controller_destroy,
#पूर्ण_अगर
	.clearb = mtk_musb_clearb,
	.clearw = mtk_musb_clearw,
	.busctl_offset = mtk_musb_busctl_offset,
	.set_mode = mtk_musb_set_mode,
पूर्ण;

#घोषणा MTK_MUSB_MAX_EP_NUM	8
#घोषणा MTK_MUSB_RAM_BITS	11

अटल काष्ठा musb_fअगरo_cfg mtk_musb_mode_cfg[] = अणु
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
	अणु .hw_ep_num = 6, .style = FIFO_TX, .maxpacket = 1024, पूर्ण,
	अणु .hw_ep_num = 6, .style = FIFO_RX, .maxpacket = 1024, पूर्ण,
	अणु .hw_ep_num = 7, .style = FIFO_TX, .maxpacket = 512, पूर्ण,
	अणु .hw_ep_num = 7, .style = FIFO_RX, .maxpacket = 64, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा musb_hdrc_config mtk_musb_hdrc_config = अणु
	.fअगरo_cfg = mtk_musb_mode_cfg,
	.fअगरo_cfg_size = ARRAY_SIZE(mtk_musb_mode_cfg),
	.multipoपूर्णांक = true,
	.dyn_fअगरo = true,
	.num_eps = MTK_MUSB_MAX_EP_NUM,
	.ram_bits = MTK_MUSB_RAM_BITS,
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_info mtk_dev_info = अणु
	.name = "musb-hdrc",
	.id = PLATFORM_DEVID_AUTO,
	.dma_mask = DMA_BIT_MASK(32),
पूर्ण;

अटल पूर्णांक mtk_musb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा musb_hdrc_platक्रमm_data *pdata;
	काष्ठा mtk_glue *glue;
	काष्ठा platक्रमm_device_info pinfo;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक ret;

	glue = devm_kzalloc(dev, माप(*glue), GFP_KERNEL);
	अगर (!glue)
		वापस -ENOMEM;

	glue->dev = dev;
	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	ret = of_platक्रमm_populate(np, शून्य, शून्य, dev);
	अगर (ret) अणु
		dev_err(dev, "failed to create child devices at %p\n", np);
		वापस ret;
	पूर्ण

	ret = mtk_musb_clks_get(glue);
	अगर (ret)
		वापस ret;

	pdata->config = &mtk_musb_hdrc_config;
	pdata->platक्रमm_ops = &mtk_musb_ops;
	pdata->mode = usb_get_dr_mode(dev);

	अगर (IS_ENABLED(CONFIG_USB_MUSB_HOST))
		pdata->mode = USB_DR_MODE_HOST;
	अन्यथा अगर (IS_ENABLED(CONFIG_USB_MUSB_GADGET))
		pdata->mode = USB_DR_MODE_PERIPHERAL;

	चयन (pdata->mode) अणु
	हाल USB_DR_MODE_HOST:
		glue->phy_mode = PHY_MODE_USB_HOST;
		glue->role = USB_ROLE_HOST;
		अवरोध;
	हाल USB_DR_MODE_PERIPHERAL:
		glue->phy_mode = PHY_MODE_USB_DEVICE;
		glue->role = USB_ROLE_DEVICE;
		अवरोध;
	हाल USB_DR_MODE_OTG:
		glue->phy_mode = PHY_MODE_USB_OTG;
		glue->role = USB_ROLE_NONE;
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "Error 'dr_mode' property\n");
		वापस -EINVAL;
	पूर्ण

	glue->phy = devm_of_phy_get_by_index(dev, np, 0);
	अगर (IS_ERR(glue->phy)) अणु
		dev_err(dev, "fail to getting phy %ld\n",
			PTR_ERR(glue->phy));
		वापस PTR_ERR(glue->phy);
	पूर्ण

	glue->usb_phy = usb_phy_generic_रेजिस्टर();
	अगर (IS_ERR(glue->usb_phy)) अणु
		dev_err(dev, "fail to registering usb-phy %ld\n",
			PTR_ERR(glue->usb_phy));
		वापस PTR_ERR(glue->usb_phy);
	पूर्ण

	glue->xceiv = devm_usb_get_phy(dev, USB_PHY_TYPE_USB2);
	अगर (IS_ERR(glue->xceiv)) अणु
		ret = PTR_ERR(glue->xceiv);
		dev_err(dev, "fail to getting usb-phy %d\n", ret);
		जाओ err_unरेजिस्टर_usb_phy;
	पूर्ण

	platक्रमm_set_drvdata(pdev, glue);
	pm_runसमय_enable(dev);
	pm_runसमय_get_sync(dev);

	ret = mtk_musb_clks_enable(glue);
	अगर (ret)
		जाओ err_enable_clk;

	pinfo = mtk_dev_info;
	pinfo.parent = dev;
	pinfo.res = pdev->resource;
	pinfo.num_res = pdev->num_resources;
	pinfo.data = pdata;
	pinfo.size_data = माप(*pdata);

	glue->musb_pdev = platक्रमm_device_रेजिस्टर_full(&pinfo);
	अगर (IS_ERR(glue->musb_pdev)) अणु
		ret = PTR_ERR(glue->musb_pdev);
		dev_err(dev, "failed to register musb device: %d\n", ret);
		जाओ err_device_रेजिस्टर;
	पूर्ण

	वापस 0;

err_device_रेजिस्टर:
	mtk_musb_clks_disable(glue);
err_enable_clk:
	pm_runसमय_put_sync(dev);
	pm_runसमय_disable(dev);
err_unरेजिस्टर_usb_phy:
	usb_phy_generic_unरेजिस्टर(glue->usb_phy);
	वापस ret;
पूर्ण

अटल पूर्णांक mtk_musb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_glue *glue = platक्रमm_get_drvdata(pdev);
	काष्ठा platक्रमm_device *usb_phy = glue->usb_phy;

	platक्रमm_device_unरेजिस्टर(glue->musb_pdev);
	usb_phy_generic_unरेजिस्टर(usb_phy);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id mtk_musb_match[] = अणु
	अणु.compatible = "mediatek,mtk-musb",पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_musb_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver mtk_musb_driver = अणु
	.probe = mtk_musb_probe,
	.हटाओ = mtk_musb_हटाओ,
	.driver = अणु
		   .name = "musb-mtk",
		   .of_match_table = of_match_ptr(mtk_musb_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mtk_musb_driver);

MODULE_DESCRIPTION("MediaTek MUSB Glue Layer");
MODULE_AUTHOR("Min Guo <min.guo@mediatek.com>");
MODULE_LICENSE("GPL v2");
