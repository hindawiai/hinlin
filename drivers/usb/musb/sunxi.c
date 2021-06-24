<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Allwinner sun4i MUSB Glue Layer
 *
 * Copyright (C) 2015 Hans de Goede <hdegoede@redhat.com>
 *
 * Based on code from
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/extcon.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/phy/phy-sun4i-usb.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>
#समावेश <linux/soc/sunxi/sunxi_sram.h>
#समावेश <linux/usb/musb.h>
#समावेश <linux/usb/of.h>
#समावेश <linux/usb/usb_phy_generic.h>
#समावेश <linux/workqueue.h>
#समावेश "musb_core.h"

/*
 * Register offsets, note sunxi musb has a dअगरferent layout then most
 * musb implementations, we translate the layout in musb_पढ़ोb & मित्रs.
 */
#घोषणा SUNXI_MUSB_POWER			0x0040
#घोषणा SUNXI_MUSB_DEVCTL			0x0041
#घोषणा SUNXI_MUSB_INDEX			0x0042
#घोषणा SUNXI_MUSB_VEND0			0x0043
#घोषणा SUNXI_MUSB_INTRTX			0x0044
#घोषणा SUNXI_MUSB_INTRRX			0x0046
#घोषणा SUNXI_MUSB_INTRTXE			0x0048
#घोषणा SUNXI_MUSB_INTRRXE			0x004a
#घोषणा SUNXI_MUSB_INTRUSB			0x004c
#घोषणा SUNXI_MUSB_INTRUSBE			0x0050
#घोषणा SUNXI_MUSB_FRAME			0x0054
#घोषणा SUNXI_MUSB_TXFIFOSZ			0x0090
#घोषणा SUNXI_MUSB_TXFIFOADD			0x0092
#घोषणा SUNXI_MUSB_RXFIFOSZ			0x0094
#घोषणा SUNXI_MUSB_RXFIFOADD			0x0096
#घोषणा SUNXI_MUSB_FADDR			0x0098
#घोषणा SUNXI_MUSB_TXFUNCADDR			0x0098
#घोषणा SUNXI_MUSB_TXHUBADDR			0x009a
#घोषणा SUNXI_MUSB_TXHUBPORT			0x009b
#घोषणा SUNXI_MUSB_RXFUNCADDR			0x009c
#घोषणा SUNXI_MUSB_RXHUBADDR			0x009e
#घोषणा SUNXI_MUSB_RXHUBPORT			0x009f
#घोषणा SUNXI_MUSB_CONFIGDATA			0x00c0

/* VEND0 bits */
#घोषणा SUNXI_MUSB_VEND0_PIO_MODE		0

/* flags */
#घोषणा SUNXI_MUSB_FL_ENABLED			0
#घोषणा SUNXI_MUSB_FL_HOSTMODE			1
#घोषणा SUNXI_MUSB_FL_HOSTMODE_PEND		2
#घोषणा SUNXI_MUSB_FL_VBUS_ON			3
#घोषणा SUNXI_MUSB_FL_PHY_ON			4
#घोषणा SUNXI_MUSB_FL_HAS_SRAM			5
#घोषणा SUNXI_MUSB_FL_HAS_RESET			6
#घोषणा SUNXI_MUSB_FL_NO_CONFIGDATA		7
#घोषणा SUNXI_MUSB_FL_PHY_MODE_PEND		8

/* Our पढ़ो/ग_लिखो methods need access and करो not get passed in a musb ref :| */
अटल काष्ठा musb *sunxi_musb;

काष्ठा sunxi_glue अणु
	काष्ठा device		*dev;
	काष्ठा musb		*musb;
	काष्ठा platक्रमm_device	*musb_pdev;
	काष्ठा clk		*clk;
	काष्ठा reset_control	*rst;
	काष्ठा phy		*phy;
	काष्ठा platक्रमm_device	*usb_phy;
	काष्ठा usb_phy		*xceiv;
	क्रमागत phy_mode		phy_mode;
	अचिन्हित दीर्घ		flags;
	काष्ठा work_काष्ठा	work;
	काष्ठा extcon_dev	*extcon;
	काष्ठा notअगरier_block	host_nb;
पूर्ण;

/* phy_घातer_on / off may sleep, so we use a workqueue  */
अटल व्योम sunxi_musb_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sunxi_glue *glue = container_of(work, काष्ठा sunxi_glue, work);
	bool vbus_on, phy_on;

	अगर (!test_bit(SUNXI_MUSB_FL_ENABLED, &glue->flags))
		वापस;

	अगर (test_and_clear_bit(SUNXI_MUSB_FL_HOSTMODE_PEND, &glue->flags)) अणु
		काष्ठा musb *musb = glue->musb;
		अचिन्हित दीर्घ flags;
		u8 devctl;

		spin_lock_irqsave(&musb->lock, flags);

		devctl = पढ़ोb(musb->mregs + SUNXI_MUSB_DEVCTL);
		अगर (test_bit(SUNXI_MUSB_FL_HOSTMODE, &glue->flags)) अणु
			set_bit(SUNXI_MUSB_FL_VBUS_ON, &glue->flags);
			musb->xceiv->otg->state = OTG_STATE_A_WAIT_VRISE;
			MUSB_HST_MODE(musb);
			devctl |= MUSB_DEVCTL_SESSION;
		पूर्ण अन्यथा अणु
			clear_bit(SUNXI_MUSB_FL_VBUS_ON, &glue->flags);
			musb->xceiv->otg->state = OTG_STATE_B_IDLE;
			MUSB_DEV_MODE(musb);
			devctl &= ~MUSB_DEVCTL_SESSION;
		पूर्ण
		ग_लिखोb(devctl, musb->mregs + SUNXI_MUSB_DEVCTL);

		spin_unlock_irqrestore(&musb->lock, flags);
	पूर्ण

	vbus_on = test_bit(SUNXI_MUSB_FL_VBUS_ON, &glue->flags);
	phy_on = test_bit(SUNXI_MUSB_FL_PHY_ON, &glue->flags);

	अगर (phy_on != vbus_on) अणु
		अगर (vbus_on) अणु
			phy_घातer_on(glue->phy);
			set_bit(SUNXI_MUSB_FL_PHY_ON, &glue->flags);
		पूर्ण अन्यथा अणु
			phy_घातer_off(glue->phy);
			clear_bit(SUNXI_MUSB_FL_PHY_ON, &glue->flags);
		पूर्ण
	पूर्ण

	अगर (test_and_clear_bit(SUNXI_MUSB_FL_PHY_MODE_PEND, &glue->flags))
		phy_set_mode(glue->phy, glue->phy_mode);
पूर्ण

अटल व्योम sunxi_musb_set_vbus(काष्ठा musb *musb, पूर्णांक is_on)
अणु
	काष्ठा sunxi_glue *glue = dev_get_drvdata(musb->controller->parent);

	अगर (is_on) अणु
		set_bit(SUNXI_MUSB_FL_VBUS_ON, &glue->flags);
		musb->xceiv->otg->state = OTG_STATE_A_WAIT_VRISE;
	पूर्ण अन्यथा अणु
		clear_bit(SUNXI_MUSB_FL_VBUS_ON, &glue->flags);
	पूर्ण

	schedule_work(&glue->work);
पूर्ण

अटल व्योम sunxi_musb_pre_root_reset_end(काष्ठा musb *musb)
अणु
	काष्ठा sunxi_glue *glue = dev_get_drvdata(musb->controller->parent);

	sun4i_usb_phy_set_squelch_detect(glue->phy, false);
पूर्ण

अटल व्योम sunxi_musb_post_root_reset_end(काष्ठा musb *musb)
अणु
	काष्ठा sunxi_glue *glue = dev_get_drvdata(musb->controller->parent);

	sun4i_usb_phy_set_squelch_detect(glue->phy, true);
पूर्ण

अटल irqवापस_t sunxi_musb_पूर्णांकerrupt(पूर्णांक irq, व्योम *__hci)
अणु
	काष्ठा musb *musb = __hci;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&musb->lock, flags);

	musb->पूर्णांक_usb = पढ़ोb(musb->mregs + SUNXI_MUSB_INTRUSB);
	अगर (musb->पूर्णांक_usb)
		ग_लिखोb(musb->पूर्णांक_usb, musb->mregs + SUNXI_MUSB_INTRUSB);

	अगर ((musb->पूर्णांक_usb & MUSB_INTR_RESET) && !is_host_active(musb)) अणु
		/* ep0 FADDR must be 0 when (re)entering peripheral mode */
		musb_ep_select(musb->mregs, 0);
		musb_ग_लिखोb(musb->mregs, MUSB_FADDR, 0);
	पूर्ण

	musb->पूर्णांक_tx = पढ़ोw(musb->mregs + SUNXI_MUSB_INTRTX);
	अगर (musb->पूर्णांक_tx)
		ग_लिखोw(musb->पूर्णांक_tx, musb->mregs + SUNXI_MUSB_INTRTX);

	musb->पूर्णांक_rx = पढ़ोw(musb->mregs + SUNXI_MUSB_INTRRX);
	अगर (musb->पूर्णांक_rx)
		ग_लिखोw(musb->पूर्णांक_rx, musb->mregs + SUNXI_MUSB_INTRRX);

	musb_पूर्णांकerrupt(musb);

	spin_unlock_irqrestore(&musb->lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sunxi_musb_host_notअगरier(काष्ठा notअगरier_block *nb,
				    अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा sunxi_glue *glue = container_of(nb, काष्ठा sunxi_glue, host_nb);

	अगर (event)
		set_bit(SUNXI_MUSB_FL_HOSTMODE, &glue->flags);
	अन्यथा
		clear_bit(SUNXI_MUSB_FL_HOSTMODE, &glue->flags);

	set_bit(SUNXI_MUSB_FL_HOSTMODE_PEND, &glue->flags);
	schedule_work(&glue->work);

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक sunxi_musb_init(काष्ठा musb *musb)
अणु
	काष्ठा sunxi_glue *glue = dev_get_drvdata(musb->controller->parent);
	पूर्णांक ret;

	sunxi_musb = musb;
	musb->phy = glue->phy;
	musb->xceiv = glue->xceiv;

	अगर (test_bit(SUNXI_MUSB_FL_HAS_SRAM, &glue->flags)) अणु
		ret = sunxi_sram_claim(musb->controller->parent);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = clk_prepare_enable(glue->clk);
	अगर (ret)
		जाओ error_sram_release;

	अगर (test_bit(SUNXI_MUSB_FL_HAS_RESET, &glue->flags)) अणु
		ret = reset_control_deनिश्चित(glue->rst);
		अगर (ret)
			जाओ error_clk_disable;
	पूर्ण

	ग_लिखोb(SUNXI_MUSB_VEND0_PIO_MODE, musb->mregs + SUNXI_MUSB_VEND0);

	/* Register notअगरier beक्रमe calling phy_init() */
	ret = devm_extcon_रेजिस्टर_notअगरier(glue->dev, glue->extcon,
					EXTCON_USB_HOST, &glue->host_nb);
	अगर (ret)
		जाओ error_reset_निश्चित;

	ret = phy_init(glue->phy);
	अगर (ret)
		जाओ error_reset_निश्चित;

	musb->isr = sunxi_musb_पूर्णांकerrupt;

	/* Stop the musb-core from करोing runसमय pm (not supported on sunxi) */
	pm_runसमय_get(musb->controller);

	वापस 0;

error_reset_निश्चित:
	अगर (test_bit(SUNXI_MUSB_FL_HAS_RESET, &glue->flags))
		reset_control_निश्चित(glue->rst);
error_clk_disable:
	clk_disable_unprepare(glue->clk);
error_sram_release:
	अगर (test_bit(SUNXI_MUSB_FL_HAS_SRAM, &glue->flags))
		sunxi_sram_release(musb->controller->parent);
	वापस ret;
पूर्ण

अटल पूर्णांक sunxi_musb_निकास(काष्ठा musb *musb)
अणु
	काष्ठा sunxi_glue *glue = dev_get_drvdata(musb->controller->parent);

	pm_runसमय_put(musb->controller);

	cancel_work_sync(&glue->work);
	अगर (test_bit(SUNXI_MUSB_FL_PHY_ON, &glue->flags))
		phy_घातer_off(glue->phy);

	phy_निकास(glue->phy);

	अगर (test_bit(SUNXI_MUSB_FL_HAS_RESET, &glue->flags))
		reset_control_निश्चित(glue->rst);

	clk_disable_unprepare(glue->clk);
	अगर (test_bit(SUNXI_MUSB_FL_HAS_SRAM, &glue->flags))
		sunxi_sram_release(musb->controller->parent);

	devm_usb_put_phy(glue->dev, glue->xceiv);

	वापस 0;
पूर्ण

अटल व्योम sunxi_musb_enable(काष्ठा musb *musb)
अणु
	काष्ठा sunxi_glue *glue = dev_get_drvdata(musb->controller->parent);

	glue->musb = musb;

	/* musb_core करोes not call us in a balanced manner */
	अगर (test_and_set_bit(SUNXI_MUSB_FL_ENABLED, &glue->flags))
		वापस;

	schedule_work(&glue->work);
पूर्ण

अटल व्योम sunxi_musb_disable(काष्ठा musb *musb)
अणु
	काष्ठा sunxi_glue *glue = dev_get_drvdata(musb->controller->parent);

	clear_bit(SUNXI_MUSB_FL_ENABLED, &glue->flags);
पूर्ण

अटल काष्ठा dma_controller *
sunxi_musb_dma_controller_create(काष्ठा musb *musb, व्योम __iomem *base)
अणु
	वापस शून्य;
पूर्ण

अटल व्योम sunxi_musb_dma_controller_destroy(काष्ठा dma_controller *c)
अणु
पूर्ण

अटल पूर्णांक sunxi_musb_set_mode(काष्ठा musb *musb, u8 mode)
अणु
	काष्ठा sunxi_glue *glue = dev_get_drvdata(musb->controller->parent);
	क्रमागत phy_mode new_mode;

	चयन (mode) अणु
	हाल MUSB_HOST:
		new_mode = PHY_MODE_USB_HOST;
		अवरोध;
	हाल MUSB_PERIPHERAL:
		new_mode = PHY_MODE_USB_DEVICE;
		अवरोध;
	हाल MUSB_OTG:
		new_mode = PHY_MODE_USB_OTG;
		अवरोध;
	शेष:
		dev_err(musb->controller->parent,
			"Error requested mode not supported by this kernel\n");
		वापस -EINVAL;
	पूर्ण

	अगर (glue->phy_mode == new_mode)
		वापस 0;

	अगर (musb->port_mode != MUSB_OTG) अणु
		dev_err(musb->controller->parent,
			"Error changing modes is only supported in dual role mode\n");
		वापस -EINVAL;
	पूर्ण

	अगर (musb->port1_status & USB_PORT_STAT_ENABLE)
		musb_root_disconnect(musb);

	/*
	 * phy_set_mode may sleep, and we're called with a spinlock held,
	 * so let sunxi_musb_work deal with it.
	 */
	glue->phy_mode = new_mode;
	set_bit(SUNXI_MUSB_FL_PHY_MODE_PEND, &glue->flags);
	schedule_work(&glue->work);

	वापस 0;
पूर्ण

अटल पूर्णांक sunxi_musb_recover(काष्ठा musb *musb)
अणु
	काष्ठा sunxi_glue *glue = dev_get_drvdata(musb->controller->parent);

	/*
	 * Schedule a phy_set_mode with the current glue->phy_mode value,
	 * this will क्रमce end the current session.
	 */
	set_bit(SUNXI_MUSB_FL_PHY_MODE_PEND, &glue->flags);
	schedule_work(&glue->work);

	वापस 0;
पूर्ण

/*
 * sunxi musb रेजिस्टर layout
 * 0x00 - 0x17	fअगरo regs, 1 दीर्घ per fअगरo
 * 0x40 - 0x57	generic control regs (घातer - frame)
 * 0x80 - 0x8f	ep control regs (addressed through hw_ep->regs, indexed)
 * 0x90 - 0x97	fअगरo control regs (indexed)
 * 0x98 - 0x9f	multipoपूर्णांक / busctl regs (indexed)
 * 0xc0		configdata reg
 */

अटल u32 sunxi_musb_fअगरo_offset(u8 epnum)
अणु
	वापस (epnum * 4);
पूर्ण

अटल u32 sunxi_musb_ep_offset(u8 epnum, u16 offset)
अणु
	WARN_ONCE(offset != 0,
		  "sunxi_musb_ep_offset called with non 0 offset\n");

	वापस 0x80; /* indexed, so ignore epnum */
पूर्ण

अटल u32 sunxi_musb_busctl_offset(u8 epnum, u16 offset)
अणु
	वापस SUNXI_MUSB_TXFUNCADDR + offset;
पूर्ण

अटल u8 sunxi_musb_पढ़ोb(व्योम __iomem *addr, u32 offset)
अणु
	काष्ठा sunxi_glue *glue;

	अगर (addr == sunxi_musb->mregs) अणु
		/* generic control or fअगरo control reg access */
		चयन (offset) अणु
		हाल MUSB_FADDR:
			वापस पढ़ोb(addr + SUNXI_MUSB_FADDR);
		हाल MUSB_POWER:
			वापस पढ़ोb(addr + SUNXI_MUSB_POWER);
		हाल MUSB_INTRUSB:
			वापस पढ़ोb(addr + SUNXI_MUSB_INTRUSB);
		हाल MUSB_INTRUSBE:
			वापस पढ़ोb(addr + SUNXI_MUSB_INTRUSBE);
		हाल MUSB_INDEX:
			वापस पढ़ोb(addr + SUNXI_MUSB_INDEX);
		हाल MUSB_TESTMODE:
			वापस 0; /* No tesपंचांगode on sunxi */
		हाल MUSB_DEVCTL:
			वापस पढ़ोb(addr + SUNXI_MUSB_DEVCTL);
		हाल MUSB_TXFIFOSZ:
			वापस पढ़ोb(addr + SUNXI_MUSB_TXFIFOSZ);
		हाल MUSB_RXFIFOSZ:
			वापस पढ़ोb(addr + SUNXI_MUSB_RXFIFOSZ);
		हाल MUSB_CONFIGDATA + 0x10: /* See musb_पढ़ो_configdata() */
			glue = dev_get_drvdata(sunxi_musb->controller->parent);
			/* A33 saves a reg, and we get to hardcode this */
			अगर (test_bit(SUNXI_MUSB_FL_NO_CONFIGDATA,
				     &glue->flags))
				वापस 0xde;

			वापस पढ़ोb(addr + SUNXI_MUSB_CONFIGDATA);
		/* Offset क्रम these is fixed by sunxi_musb_busctl_offset() */
		हाल SUNXI_MUSB_TXFUNCADDR:
		हाल SUNXI_MUSB_TXHUBADDR:
		हाल SUNXI_MUSB_TXHUBPORT:
		हाल SUNXI_MUSB_RXFUNCADDR:
		हाल SUNXI_MUSB_RXHUBADDR:
		हाल SUNXI_MUSB_RXHUBPORT:
			/* multipoपूर्णांक / busctl reg access */
			वापस पढ़ोb(addr + offset);
		शेष:
			dev_err(sunxi_musb->controller->parent,
				"Error unknown readb offset %u\n", offset);
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अगर (addr == (sunxi_musb->mregs + 0x80)) अणु
		/* ep control reg access */
		/* sunxi has a 2 byte hole beक्रमe the txtype रेजिस्टर */
		अगर (offset >= MUSB_TXTYPE)
			offset += 2;
		वापस पढ़ोb(addr + offset);
	पूर्ण

	dev_err(sunxi_musb->controller->parent,
		"Error unknown readb at 0x%x bytes offset\n",
		(पूर्णांक)(addr - sunxi_musb->mregs));
	वापस 0;
पूर्ण

अटल व्योम sunxi_musb_ग_लिखोb(व्योम __iomem *addr, अचिन्हित offset, u8 data)
अणु
	अगर (addr == sunxi_musb->mregs) अणु
		/* generic control or fअगरo control reg access */
		चयन (offset) अणु
		हाल MUSB_FADDR:
			वापस ग_लिखोb(data, addr + SUNXI_MUSB_FADDR);
		हाल MUSB_POWER:
			वापस ग_लिखोb(data, addr + SUNXI_MUSB_POWER);
		हाल MUSB_INTRUSB:
			वापस ग_लिखोb(data, addr + SUNXI_MUSB_INTRUSB);
		हाल MUSB_INTRUSBE:
			वापस ग_लिखोb(data, addr + SUNXI_MUSB_INTRUSBE);
		हाल MUSB_INDEX:
			वापस ग_लिखोb(data, addr + SUNXI_MUSB_INDEX);
		हाल MUSB_TESTMODE:
			अगर (data)
				dev_warn(sunxi_musb->controller->parent,
					"sunxi-musb does not have testmode\n");
			वापस;
		हाल MUSB_DEVCTL:
			वापस ग_लिखोb(data, addr + SUNXI_MUSB_DEVCTL);
		हाल MUSB_TXFIFOSZ:
			वापस ग_लिखोb(data, addr + SUNXI_MUSB_TXFIFOSZ);
		हाल MUSB_RXFIFOSZ:
			वापस ग_लिखोb(data, addr + SUNXI_MUSB_RXFIFOSZ);
		/* Offset क्रम these is fixed by sunxi_musb_busctl_offset() */
		हाल SUNXI_MUSB_TXFUNCADDR:
		हाल SUNXI_MUSB_TXHUBADDR:
		हाल SUNXI_MUSB_TXHUBPORT:
		हाल SUNXI_MUSB_RXFUNCADDR:
		हाल SUNXI_MUSB_RXHUBADDR:
		हाल SUNXI_MUSB_RXHUBPORT:
			/* multipoपूर्णांक / busctl reg access */
			वापस ग_लिखोb(data, addr + offset);
		शेष:
			dev_err(sunxi_musb->controller->parent,
				"Error unknown writeb offset %u\n", offset);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अगर (addr == (sunxi_musb->mregs + 0x80)) अणु
		/* ep control reg access */
		अगर (offset >= MUSB_TXTYPE)
			offset += 2;
		वापस ग_लिखोb(data, addr + offset);
	पूर्ण

	dev_err(sunxi_musb->controller->parent,
		"Error unknown writeb at 0x%x bytes offset\n",
		(पूर्णांक)(addr - sunxi_musb->mregs));
पूर्ण

अटल u16 sunxi_musb_पढ़ोw(व्योम __iomem *addr, u32 offset)
अणु
	अगर (addr == sunxi_musb->mregs) अणु
		/* generic control or fअगरo control reg access */
		चयन (offset) अणु
		हाल MUSB_INTRTX:
			वापस पढ़ोw(addr + SUNXI_MUSB_INTRTX);
		हाल MUSB_INTRRX:
			वापस पढ़ोw(addr + SUNXI_MUSB_INTRRX);
		हाल MUSB_INTRTXE:
			वापस पढ़ोw(addr + SUNXI_MUSB_INTRTXE);
		हाल MUSB_INTRRXE:
			वापस पढ़ोw(addr + SUNXI_MUSB_INTRRXE);
		हाल MUSB_FRAME:
			वापस पढ़ोw(addr + SUNXI_MUSB_FRAME);
		हाल MUSB_TXFIFOADD:
			वापस पढ़ोw(addr + SUNXI_MUSB_TXFIFOADD);
		हाल MUSB_RXFIFOADD:
			वापस पढ़ोw(addr + SUNXI_MUSB_RXFIFOADD);
		हाल MUSB_HWVERS:
			वापस 0; /* sunxi musb version is not known */
		शेष:
			dev_err(sunxi_musb->controller->parent,
				"Error unknown readw offset %u\n", offset);
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अगर (addr == (sunxi_musb->mregs + 0x80)) अणु
		/* ep control reg access */
		वापस पढ़ोw(addr + offset);
	पूर्ण

	dev_err(sunxi_musb->controller->parent,
		"Error unknown readw at 0x%x bytes offset\n",
		(पूर्णांक)(addr - sunxi_musb->mregs));
	वापस 0;
पूर्ण

अटल व्योम sunxi_musb_ग_लिखोw(व्योम __iomem *addr, अचिन्हित offset, u16 data)
अणु
	अगर (addr == sunxi_musb->mregs) अणु
		/* generic control or fअगरo control reg access */
		चयन (offset) अणु
		हाल MUSB_INTRTX:
			वापस ग_लिखोw(data, addr + SUNXI_MUSB_INTRTX);
		हाल MUSB_INTRRX:
			वापस ग_लिखोw(data, addr + SUNXI_MUSB_INTRRX);
		हाल MUSB_INTRTXE:
			वापस ग_लिखोw(data, addr + SUNXI_MUSB_INTRTXE);
		हाल MUSB_INTRRXE:
			वापस ग_लिखोw(data, addr + SUNXI_MUSB_INTRRXE);
		हाल MUSB_FRAME:
			वापस ग_लिखोw(data, addr + SUNXI_MUSB_FRAME);
		हाल MUSB_TXFIFOADD:
			वापस ग_लिखोw(data, addr + SUNXI_MUSB_TXFIFOADD);
		हाल MUSB_RXFIFOADD:
			वापस ग_लिखोw(data, addr + SUNXI_MUSB_RXFIFOADD);
		शेष:
			dev_err(sunxi_musb->controller->parent,
				"Error unknown writew offset %u\n", offset);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अगर (addr == (sunxi_musb->mregs + 0x80)) अणु
		/* ep control reg access */
		वापस ग_लिखोw(data, addr + offset);
	पूर्ण

	dev_err(sunxi_musb->controller->parent,
		"Error unknown writew at 0x%x bytes offset\n",
		(पूर्णांक)(addr - sunxi_musb->mregs));
पूर्ण

अटल स्थिर काष्ठा musb_platक्रमm_ops sunxi_musb_ops = अणु
	.quirks		= MUSB_INDEXED_EP,
	.init		= sunxi_musb_init,
	.निकास		= sunxi_musb_निकास,
	.enable		= sunxi_musb_enable,
	.disable	= sunxi_musb_disable,
	.fअगरo_offset	= sunxi_musb_fअगरo_offset,
	.ep_offset	= sunxi_musb_ep_offset,
	.busctl_offset	= sunxi_musb_busctl_offset,
	.पढ़ोb		= sunxi_musb_पढ़ोb,
	.ग_लिखोb		= sunxi_musb_ग_लिखोb,
	.पढ़ोw		= sunxi_musb_पढ़ोw,
	.ग_लिखोw		= sunxi_musb_ग_लिखोw,
	.dma_init	= sunxi_musb_dma_controller_create,
	.dma_निकास	= sunxi_musb_dma_controller_destroy,
	.set_mode	= sunxi_musb_set_mode,
	.recover	= sunxi_musb_recover,
	.set_vbus	= sunxi_musb_set_vbus,
	.pre_root_reset_end = sunxi_musb_pre_root_reset_end,
	.post_root_reset_end = sunxi_musb_post_root_reset_end,
पूर्ण;

/* Allwinner OTG supports up to 5 endpoपूर्णांकs */
#घोषणा SUNXI_MUSB_MAX_EP_NUM	6
#घोषणा SUNXI_MUSB_RAM_BITS	11

अटल काष्ठा musb_fअगरo_cfg sunxi_musb_mode_cfg[] = अणु
	MUSB_EP_FIFO_SINGLE(1, FIFO_TX, 512),
	MUSB_EP_FIFO_SINGLE(1, FIFO_RX, 512),
	MUSB_EP_FIFO_SINGLE(2, FIFO_TX, 512),
	MUSB_EP_FIFO_SINGLE(2, FIFO_RX, 512),
	MUSB_EP_FIFO_SINGLE(3, FIFO_TX, 512),
	MUSB_EP_FIFO_SINGLE(3, FIFO_RX, 512),
	MUSB_EP_FIFO_SINGLE(4, FIFO_TX, 512),
	MUSB_EP_FIFO_SINGLE(4, FIFO_RX, 512),
	MUSB_EP_FIFO_SINGLE(5, FIFO_TX, 512),
	MUSB_EP_FIFO_SINGLE(5, FIFO_RX, 512),
पूर्ण;

/* H3/V3s OTG supports only 4 endpoपूर्णांकs */
#घोषणा SUNXI_MUSB_MAX_EP_NUM_H3	5

अटल काष्ठा musb_fअगरo_cfg sunxi_musb_mode_cfg_h3[] = अणु
	MUSB_EP_FIFO_SINGLE(1, FIFO_TX, 512),
	MUSB_EP_FIFO_SINGLE(1, FIFO_RX, 512),
	MUSB_EP_FIFO_SINGLE(2, FIFO_TX, 512),
	MUSB_EP_FIFO_SINGLE(2, FIFO_RX, 512),
	MUSB_EP_FIFO_SINGLE(3, FIFO_TX, 512),
	MUSB_EP_FIFO_SINGLE(3, FIFO_RX, 512),
	MUSB_EP_FIFO_SINGLE(4, FIFO_TX, 512),
	MUSB_EP_FIFO_SINGLE(4, FIFO_RX, 512),
पूर्ण;

अटल स्थिर काष्ठा musb_hdrc_config sunxi_musb_hdrc_config = अणु
	.fअगरo_cfg       = sunxi_musb_mode_cfg,
	.fअगरo_cfg_size  = ARRAY_SIZE(sunxi_musb_mode_cfg),
	.multipoपूर्णांक	= true,
	.dyn_fअगरo	= true,
	.num_eps	= SUNXI_MUSB_MAX_EP_NUM,
	.ram_bits	= SUNXI_MUSB_RAM_BITS,
पूर्ण;

अटल काष्ठा musb_hdrc_config sunxi_musb_hdrc_config_h3 = अणु
	.fअगरo_cfg       = sunxi_musb_mode_cfg_h3,
	.fअगरo_cfg_size  = ARRAY_SIZE(sunxi_musb_mode_cfg_h3),
	.multipoपूर्णांक	= true,
	.dyn_fअगरo	= true,
	.num_eps	= SUNXI_MUSB_MAX_EP_NUM_H3,
	.ram_bits	= SUNXI_MUSB_RAM_BITS,
पूर्ण;


अटल पूर्णांक sunxi_musb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा musb_hdrc_platक्रमm_data	pdata;
	काष्ठा platक्रमm_device_info	pinfo;
	काष्ठा sunxi_glue		*glue;
	काष्ठा device_node		*np = pdev->dev.of_node;
	पूर्णांक ret;

	अगर (!np) अणु
		dev_err(&pdev->dev, "Error no device tree node found\n");
		वापस -EINVAL;
	पूर्ण

	glue = devm_kzalloc(&pdev->dev, माप(*glue), GFP_KERNEL);
	अगर (!glue)
		वापस -ENOMEM;

	स_रखो(&pdata, 0, माप(pdata));
	चयन (usb_get_dr_mode(&pdev->dev)) अणु
#अगर defined CONFIG_USB_MUSB_DUAL_ROLE || defined CONFIG_USB_MUSB_HOST
	हाल USB_DR_MODE_HOST:
		pdata.mode = MUSB_HOST;
		glue->phy_mode = PHY_MODE_USB_HOST;
		अवरोध;
#पूर्ण_अगर
#अगर defined CONFIG_USB_MUSB_DUAL_ROLE || defined CONFIG_USB_MUSB_GADGET
	हाल USB_DR_MODE_PERIPHERAL:
		pdata.mode = MUSB_PERIPHERAL;
		glue->phy_mode = PHY_MODE_USB_DEVICE;
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_USB_MUSB_DUAL_ROLE
	हाल USB_DR_MODE_OTG:
		pdata.mode = MUSB_OTG;
		glue->phy_mode = PHY_MODE_USB_OTG;
		अवरोध;
#पूर्ण_अगर
	शेष:
		dev_err(&pdev->dev, "Invalid or missing 'dr_mode' property\n");
		वापस -EINVAL;
	पूर्ण
	pdata.platक्रमm_ops	= &sunxi_musb_ops;
	अगर (!of_device_is_compatible(np, "allwinner,sun8i-h3-musb"))
		pdata.config = &sunxi_musb_hdrc_config;
	अन्यथा
		pdata.config = &sunxi_musb_hdrc_config_h3;

	glue->dev = &pdev->dev;
	INIT_WORK(&glue->work, sunxi_musb_work);
	glue->host_nb.notअगरier_call = sunxi_musb_host_notअगरier;

	अगर (of_device_is_compatible(np, "allwinner,sun4i-a10-musb"))
		set_bit(SUNXI_MUSB_FL_HAS_SRAM, &glue->flags);

	अगर (of_device_is_compatible(np, "allwinner,sun6i-a31-musb"))
		set_bit(SUNXI_MUSB_FL_HAS_RESET, &glue->flags);

	अगर (of_device_is_compatible(np, "allwinner,sun8i-a33-musb") ||
	    of_device_is_compatible(np, "allwinner,sun8i-h3-musb")) अणु
		set_bit(SUNXI_MUSB_FL_HAS_RESET, &glue->flags);
		set_bit(SUNXI_MUSB_FL_NO_CONFIGDATA, &glue->flags);
	पूर्ण

	glue->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(glue->clk)) अणु
		dev_err(&pdev->dev, "Error getting clock: %ld\n",
			PTR_ERR(glue->clk));
		वापस PTR_ERR(glue->clk);
	पूर्ण

	अगर (test_bit(SUNXI_MUSB_FL_HAS_RESET, &glue->flags)) अणु
		glue->rst = devm_reset_control_get(&pdev->dev, शून्य);
		अगर (IS_ERR(glue->rst)) अणु
			अगर (PTR_ERR(glue->rst) == -EPROBE_DEFER)
				वापस -EPROBE_DEFER;
			dev_err(&pdev->dev, "Error getting reset %ld\n",
				PTR_ERR(glue->rst));
			वापस PTR_ERR(glue->rst);
		पूर्ण
	पूर्ण

	glue->extcon = extcon_get_edev_by_phandle(&pdev->dev, 0);
	अगर (IS_ERR(glue->extcon)) अणु
		अगर (PTR_ERR(glue->extcon) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		dev_err(&pdev->dev, "Invalid or missing extcon\n");
		वापस PTR_ERR(glue->extcon);
	पूर्ण

	glue->phy = devm_phy_get(&pdev->dev, "usb");
	अगर (IS_ERR(glue->phy)) अणु
		अगर (PTR_ERR(glue->phy) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		dev_err(&pdev->dev, "Error getting phy %ld\n",
			PTR_ERR(glue->phy));
		वापस PTR_ERR(glue->phy);
	पूर्ण

	glue->usb_phy = usb_phy_generic_रेजिस्टर();
	अगर (IS_ERR(glue->usb_phy)) अणु
		dev_err(&pdev->dev, "Error registering usb-phy %ld\n",
			PTR_ERR(glue->usb_phy));
		वापस PTR_ERR(glue->usb_phy);
	पूर्ण

	glue->xceiv = devm_usb_get_phy(&pdev->dev, USB_PHY_TYPE_USB2);
	अगर (IS_ERR(glue->xceiv)) अणु
		ret = PTR_ERR(glue->xceiv);
		dev_err(&pdev->dev, "Error getting usb-phy %d\n", ret);
		जाओ err_unरेजिस्टर_usb_phy;
	पूर्ण

	platक्रमm_set_drvdata(pdev, glue);

	स_रखो(&pinfo, 0, माप(pinfo));
	pinfo.name	 = "musb-hdrc";
	pinfo.id	= PLATFORM_DEVID_AUTO;
	pinfo.parent	= &pdev->dev;
	pinfo.fwnode	= of_fwnode_handle(pdev->dev.of_node);
	pinfo.of_node_reused = true;
	pinfo.res	= pdev->resource;
	pinfo.num_res	= pdev->num_resources;
	pinfo.data	= &pdata;
	pinfo.size_data = माप(pdata);

	glue->musb_pdev = platक्रमm_device_रेजिस्टर_full(&pinfo);
	अगर (IS_ERR(glue->musb_pdev)) अणु
		ret = PTR_ERR(glue->musb_pdev);
		dev_err(&pdev->dev, "Error registering musb dev: %d\n", ret);
		जाओ err_unरेजिस्टर_usb_phy;
	पूर्ण

	वापस 0;

err_unरेजिस्टर_usb_phy:
	usb_phy_generic_unरेजिस्टर(glue->usb_phy);
	वापस ret;
पूर्ण

अटल पूर्णांक sunxi_musb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sunxi_glue *glue = platक्रमm_get_drvdata(pdev);
	काष्ठा platक्रमm_device *usb_phy = glue->usb_phy;

	platक्रमm_device_unरेजिस्टर(glue->musb_pdev);
	usb_phy_generic_unरेजिस्टर(usb_phy);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sunxi_musb_match[] = अणु
	अणु .compatible = "allwinner,sun4i-a10-musb", पूर्ण,
	अणु .compatible = "allwinner,sun6i-a31-musb", पूर्ण,
	अणु .compatible = "allwinner,sun8i-a33-musb", पूर्ण,
	अणु .compatible = "allwinner,sun8i-h3-musb", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sunxi_musb_match);

अटल काष्ठा platक्रमm_driver sunxi_musb_driver = अणु
	.probe = sunxi_musb_probe,
	.हटाओ = sunxi_musb_हटाओ,
	.driver = अणु
		.name = "musb-sunxi",
		.of_match_table = sunxi_musb_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sunxi_musb_driver);

MODULE_DESCRIPTION("Allwinner sunxi MUSB Glue Layer");
MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_LICENSE("GPL v2");
