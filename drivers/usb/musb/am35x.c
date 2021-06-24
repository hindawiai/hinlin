<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Texas Instruments AM35x "glue layer"
 *
 * Copyright (c) 2010, by Texas Instruments
 *
 * Based on the DA8xx "glue layer" code.
 * Copyright (c) 2008-2009, MontaVista Software, Inc. <source@mvista.com>
 *
 * This file is part of the Inventra Controller Driver क्रम Linux.
 */

#समावेश <linux/module.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/usb/usb_phy_generic.h>
#समावेश <linux/platक्रमm_data/usb-omap.h>

#समावेश "musb_core.h"

/*
 * AM35x specअगरic definitions
 */
/* USB 2.0 OTG module रेजिस्टरs */
#घोषणा USB_REVISION_REG	0x00
#घोषणा USB_CTRL_REG		0x04
#घोषणा USB_STAT_REG		0x08
#घोषणा USB_EMULATION_REG	0x0c
/* 0x10 Reserved */
#घोषणा USB_AUTOREQ_REG		0x14
#घोषणा USB_SRP_FIX_TIME_REG	0x18
#घोषणा USB_TEARDOWN_REG	0x1c
#घोषणा EP_INTR_SRC_REG		0x20
#घोषणा EP_INTR_SRC_SET_REG	0x24
#घोषणा EP_INTR_SRC_CLEAR_REG	0x28
#घोषणा EP_INTR_MASK_REG	0x2c
#घोषणा EP_INTR_MASK_SET_REG	0x30
#घोषणा EP_INTR_MASK_CLEAR_REG	0x34
#घोषणा EP_INTR_SRC_MASKED_REG	0x38
#घोषणा CORE_INTR_SRC_REG	0x40
#घोषणा CORE_INTR_SRC_SET_REG	0x44
#घोषणा CORE_INTR_SRC_CLEAR_REG	0x48
#घोषणा CORE_INTR_MASK_REG	0x4c
#घोषणा CORE_INTR_MASK_SET_REG	0x50
#घोषणा CORE_INTR_MASK_CLEAR_REG 0x54
#घोषणा CORE_INTR_SRC_MASKED_REG 0x58
/* 0x5c Reserved */
#घोषणा USB_END_OF_INTR_REG	0x60

/* Control रेजिस्टर bits */
#घोषणा AM35X_SOFT_RESET_MASK	1

/* USB पूर्णांकerrupt रेजिस्टर bits */
#घोषणा AM35X_INTR_USB_SHIFT	16
#घोषणा AM35X_INTR_USB_MASK	(0x1ff << AM35X_INTR_USB_SHIFT)
#घोषणा AM35X_INTR_DRVVBUS	0x100
#घोषणा AM35X_INTR_RX_SHIFT	16
#घोषणा AM35X_INTR_TX_SHIFT	0
#घोषणा AM35X_TX_EP_MASK	0xffff		/* EP0 + 15 Tx EPs */
#घोषणा AM35X_RX_EP_MASK	0xfffe		/* 15 Rx EPs */
#घोषणा AM35X_TX_INTR_MASK	(AM35X_TX_EP_MASK << AM35X_INTR_TX_SHIFT)
#घोषणा AM35X_RX_INTR_MASK	(AM35X_RX_EP_MASK << AM35X_INTR_RX_SHIFT)

#घोषणा USB_MENTOR_CORE_OFFSET	0x400

काष्ठा am35x_glue अणु
	काष्ठा device		*dev;
	काष्ठा platक्रमm_device	*musb;
	काष्ठा platक्रमm_device	*phy;
	काष्ठा clk		*phy_clk;
	काष्ठा clk		*clk;
पूर्ण;

/*
 * am35x_musb_enable - enable पूर्णांकerrupts
 */
अटल व्योम am35x_musb_enable(काष्ठा musb *musb)
अणु
	व्योम __iomem *reg_base = musb->ctrl_base;
	u32 epmask;

	/* Workaround: setup IRQs through both रेजिस्टर sets. */
	epmask = ((musb->epmask & AM35X_TX_EP_MASK) << AM35X_INTR_TX_SHIFT) |
	       ((musb->epmask & AM35X_RX_EP_MASK) << AM35X_INTR_RX_SHIFT);

	musb_ग_लिखोl(reg_base, EP_INTR_MASK_SET_REG, epmask);
	musb_ग_लिखोl(reg_base, CORE_INTR_MASK_SET_REG, AM35X_INTR_USB_MASK);

	/* Force the DRVVBUS IRQ so we can start polling क्रम ID change. */
	musb_ग_लिखोl(reg_base, CORE_INTR_SRC_SET_REG,
			AM35X_INTR_DRVVBUS << AM35X_INTR_USB_SHIFT);
पूर्ण

/*
 * am35x_musb_disable - disable HDRC and flush पूर्णांकerrupts
 */
अटल व्योम am35x_musb_disable(काष्ठा musb *musb)
अणु
	व्योम __iomem *reg_base = musb->ctrl_base;

	musb_ग_लिखोl(reg_base, CORE_INTR_MASK_CLEAR_REG, AM35X_INTR_USB_MASK);
	musb_ग_लिखोl(reg_base, EP_INTR_MASK_CLEAR_REG,
			 AM35X_TX_INTR_MASK | AM35X_RX_INTR_MASK);
	musb_ग_लिखोl(reg_base, USB_END_OF_INTR_REG, 0);
पूर्ण

#घोषणा portstate(sपंचांगt)		sपंचांगt

अटल व्योम am35x_musb_set_vbus(काष्ठा musb *musb, पूर्णांक is_on)
अणु
	WARN_ON(is_on && is_peripheral_active(musb));
पूर्ण

#घोषणा	POLL_SECONDS	2

अटल व्योम otg_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा musb		*musb = from_समयr(musb, t, dev_समयr);
	व्योम __iomem		*mregs = musb->mregs;
	u8			devctl;
	अचिन्हित दीर्घ		flags;

	/*
	 * We poll because AM35x's won't expose several OTG-critical
	 * status change events (from the transceiver) otherwise.
	 */
	devctl = musb_पढ़ोb(mregs, MUSB_DEVCTL);
	dev_dbg(musb->controller, "Poll devctl %02x (%s)\n", devctl,
		usb_otg_state_string(musb->xceiv->otg->state));

	spin_lock_irqsave(&musb->lock, flags);
	चयन (musb->xceiv->otg->state) अणु
	हाल OTG_STATE_A_WAIT_BCON:
		devctl &= ~MUSB_DEVCTL_SESSION;
		musb_ग_लिखोb(musb->mregs, MUSB_DEVCTL, devctl);

		devctl = musb_पढ़ोb(musb->mregs, MUSB_DEVCTL);
		अगर (devctl & MUSB_DEVCTL_BDEVICE) अणु
			musb->xceiv->otg->state = OTG_STATE_B_IDLE;
			MUSB_DEV_MODE(musb);
		पूर्ण अन्यथा अणु
			musb->xceiv->otg->state = OTG_STATE_A_IDLE;
			MUSB_HST_MODE(musb);
		पूर्ण
		अवरोध;
	हाल OTG_STATE_A_WAIT_VFALL:
		musb->xceiv->otg->state = OTG_STATE_A_WAIT_VRISE;
		musb_ग_लिखोl(musb->ctrl_base, CORE_INTR_SRC_SET_REG,
			    MUSB_INTR_VBUSERROR << AM35X_INTR_USB_SHIFT);
		अवरोध;
	हाल OTG_STATE_B_IDLE:
		devctl = musb_पढ़ोb(mregs, MUSB_DEVCTL);
		अगर (devctl & MUSB_DEVCTL_BDEVICE)
			mod_समयr(&musb->dev_समयr, jअगरfies + POLL_SECONDS * HZ);
		अन्यथा
			musb->xceiv->otg->state = OTG_STATE_A_IDLE;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&musb->lock, flags);
पूर्ण

अटल व्योम am35x_musb_try_idle(काष्ठा musb *musb, अचिन्हित दीर्घ समयout)
अणु
	अटल अचिन्हित दीर्घ last_समयr;

	अगर (समयout == 0)
		समयout = jअगरfies + msecs_to_jअगरfies(3);

	/* Never idle अगर active, or when VBUS समयout is not set as host */
	अगर (musb->is_active || (musb->a_रुको_bcon == 0 &&
				musb->xceiv->otg->state == OTG_STATE_A_WAIT_BCON)) अणु
		dev_dbg(musb->controller, "%s active, deleting timer\n",
			usb_otg_state_string(musb->xceiv->otg->state));
		del_समयr(&musb->dev_समयr);
		last_समयr = jअगरfies;
		वापस;
	पूर्ण

	अगर (समय_after(last_समयr, समयout) && समयr_pending(&musb->dev_समयr)) अणु
		dev_dbg(musb->controller, "Longer idle timer already pending, ignoring...\n");
		वापस;
	पूर्ण
	last_समयr = समयout;

	dev_dbg(musb->controller, "%s inactive, starting idle timer for %u ms\n",
		usb_otg_state_string(musb->xceiv->otg->state),
		jअगरfies_to_msecs(समयout - jअगरfies));
	mod_समयr(&musb->dev_समयr, समयout);
पूर्ण

अटल irqवापस_t am35x_musb_पूर्णांकerrupt(पूर्णांक irq, व्योम *hci)
अणु
	काष्ठा musb  *musb = hci;
	व्योम __iomem *reg_base = musb->ctrl_base;
	काष्ठा device *dev = musb->controller;
	काष्ठा musb_hdrc_platक्रमm_data *plat = dev_get_platdata(dev);
	काष्ठा omap_musb_board_data *data = plat->board_data;
	अचिन्हित दीर्घ flags;
	irqवापस_t ret = IRQ_NONE;
	u32 epपूर्णांकr, usbपूर्णांकr;

	spin_lock_irqsave(&musb->lock, flags);

	/* Get endpoपूर्णांक पूर्णांकerrupts */
	epपूर्णांकr = musb_पढ़ोl(reg_base, EP_INTR_SRC_MASKED_REG);

	अगर (epपूर्णांकr) अणु
		musb_ग_लिखोl(reg_base, EP_INTR_SRC_CLEAR_REG, epपूर्णांकr);

		musb->पूर्णांक_rx =
			(epपूर्णांकr & AM35X_RX_INTR_MASK) >> AM35X_INTR_RX_SHIFT;
		musb->पूर्णांक_tx =
			(epपूर्णांकr & AM35X_TX_INTR_MASK) >> AM35X_INTR_TX_SHIFT;
	पूर्ण

	/* Get usb core पूर्णांकerrupts */
	usbपूर्णांकr = musb_पढ़ोl(reg_base, CORE_INTR_SRC_MASKED_REG);
	अगर (!usbपूर्णांकr && !epपूर्णांकr)
		जाओ eoi;

	अगर (usbपूर्णांकr) अणु
		musb_ग_लिखोl(reg_base, CORE_INTR_SRC_CLEAR_REG, usbपूर्णांकr);

		musb->पूर्णांक_usb =
			(usbपूर्णांकr & AM35X_INTR_USB_MASK) >> AM35X_INTR_USB_SHIFT;
	पूर्ण
	/*
	 * DRVVBUS IRQs are the only proxy we have (a very poor one!) क्रम
	 * AM35x's missing ID change IRQ.  We need an ID change IRQ to
	 * चयन appropriately between halves of the OTG state machine.
	 * Managing DEVCTL.SESSION per Mentor करोcs requires that we know its
	 * value but DEVCTL.BDEVICE is invalid without DEVCTL.SESSION set.
	 * Also, DRVVBUS pulses क्रम SRP (but not at 5V) ...
	 */
	अगर (usbपूर्णांकr & (AM35X_INTR_DRVVBUS << AM35X_INTR_USB_SHIFT)) अणु
		पूर्णांक drvvbus = musb_पढ़ोl(reg_base, USB_STAT_REG);
		व्योम __iomem *mregs = musb->mregs;
		u8 devctl = musb_पढ़ोb(mregs, MUSB_DEVCTL);
		पूर्णांक err;

		err = musb->पूर्णांक_usb & MUSB_INTR_VBUSERROR;
		अगर (err) अणु
			/*
			 * The Mentor core करोesn't debounce VBUS as needed
			 * to cope with device connect current spikes. This
			 * means it's not uncommon क्रम bus-घातered devices
			 * to get VBUS errors during क्रमागतeration.
			 *
			 * This is a workaround, but newer RTL from Mentor
			 * seems to allow a better one: "re"-starting sessions
			 * without रुकोing क्रम VBUS to stop रेजिस्टरing in
			 * devctl.
			 */
			musb->पूर्णांक_usb &= ~MUSB_INTR_VBUSERROR;
			musb->xceiv->otg->state = OTG_STATE_A_WAIT_VFALL;
			mod_समयr(&musb->dev_समयr, jअगरfies + POLL_SECONDS * HZ);
			WARNING("VBUS error workaround (delay coming)\n");
		पूर्ण अन्यथा अगर (drvvbus) अणु
			MUSB_HST_MODE(musb);
			musb->xceiv->otg->state = OTG_STATE_A_WAIT_VRISE;
			portstate(musb->port1_status |= USB_PORT_STAT_POWER);
			del_समयr(&musb->dev_समयr);
		पूर्ण अन्यथा अणु
			musb->is_active = 0;
			MUSB_DEV_MODE(musb);
			musb->xceiv->otg->state = OTG_STATE_B_IDLE;
			portstate(musb->port1_status &= ~USB_PORT_STAT_POWER);
		पूर्ण

		/* NOTE: this must complete घातer-on within 100 ms. */
		dev_dbg(musb->controller, "VBUS %s (%s)%s, devctl %02x\n",
				drvvbus ? "on" : "off",
				usb_otg_state_string(musb->xceiv->otg->state),
				err ? " ERROR" : "",
				devctl);
		ret = IRQ_HANDLED;
	पूर्ण

	/* Drop spurious RX and TX अगर device is disconnected */
	अगर (musb->पूर्णांक_usb & MUSB_INTR_DISCONNECT) अणु
		musb->पूर्णांक_tx = 0;
		musb->पूर्णांक_rx = 0;
	पूर्ण

	अगर (musb->पूर्णांक_tx || musb->पूर्णांक_rx || musb->पूर्णांक_usb)
		ret |= musb_पूर्णांकerrupt(musb);

eoi:
	/* EOI needs to be written क्रम the IRQ to be re-निश्चितed. */
	अगर (ret == IRQ_HANDLED || epपूर्णांकr || usbपूर्णांकr) अणु
		/* clear level पूर्णांकerrupt */
		अगर (data->clear_irq)
			data->clear_irq();
		/* ग_लिखो EOI */
		musb_ग_लिखोl(reg_base, USB_END_OF_INTR_REG, 0);
	पूर्ण

	/* Poll क्रम ID change */
	अगर (musb->xceiv->otg->state == OTG_STATE_B_IDLE)
		mod_समयr(&musb->dev_समयr, jअगरfies + POLL_SECONDS * HZ);

	spin_unlock_irqrestore(&musb->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक am35x_musb_set_mode(काष्ठा musb *musb, u8 musb_mode)
अणु
	काष्ठा device *dev = musb->controller;
	काष्ठा musb_hdrc_platक्रमm_data *plat = dev_get_platdata(dev);
	काष्ठा omap_musb_board_data *data = plat->board_data;
	पूर्णांक     retval = 0;

	अगर (data->set_mode)
		data->set_mode(musb_mode);
	अन्यथा
		retval = -EIO;

	वापस retval;
पूर्ण

अटल पूर्णांक am35x_musb_init(काष्ठा musb *musb)
अणु
	काष्ठा device *dev = musb->controller;
	काष्ठा musb_hdrc_platक्रमm_data *plat = dev_get_platdata(dev);
	काष्ठा omap_musb_board_data *data = plat->board_data;
	व्योम __iomem *reg_base = musb->ctrl_base;
	u32 rev;

	musb->mregs += USB_MENTOR_CORE_OFFSET;

	/* Returns zero अगर e.g. not घड़ीed */
	rev = musb_पढ़ोl(reg_base, USB_REVISION_REG);
	अगर (!rev)
		वापस -ENODEV;

	musb->xceiv = usb_get_phy(USB_PHY_TYPE_USB2);
	अगर (IS_ERR_OR_शून्य(musb->xceiv))
		वापस -EPROBE_DEFER;

	समयr_setup(&musb->dev_समयr, otg_समयr, 0);

	/* Reset the musb */
	अगर (data->reset)
		data->reset();

	/* Reset the controller */
	musb_ग_लिखोl(reg_base, USB_CTRL_REG, AM35X_SOFT_RESET_MASK);

	/* Start the on-chip PHY and its PLL. */
	अगर (data->set_phy_घातer)
		data->set_phy_घातer(1);

	msleep(5);

	musb->isr = am35x_musb_पूर्णांकerrupt;

	/* clear level पूर्णांकerrupt */
	अगर (data->clear_irq)
		data->clear_irq();

	वापस 0;
पूर्ण

अटल पूर्णांक am35x_musb_निकास(काष्ठा musb *musb)
अणु
	काष्ठा device *dev = musb->controller;
	काष्ठा musb_hdrc_platक्रमm_data *plat = dev_get_platdata(dev);
	काष्ठा omap_musb_board_data *data = plat->board_data;

	del_समयr_sync(&musb->dev_समयr);

	/* Shutकरोwn the on-chip PHY and its PLL. */
	अगर (data->set_phy_घातer)
		data->set_phy_घातer(0);

	usb_put_phy(musb->xceiv);

	वापस 0;
पूर्ण

/* AM35x supports only 32bit पढ़ो operation */
अटल व्योम am35x_पढ़ो_fअगरo(काष्ठा musb_hw_ep *hw_ep, u16 len, u8 *dst)
अणु
	व्योम __iomem *fअगरo = hw_ep->fअगरo;
	u32		val;
	पूर्णांक		i;

	/* Read क्रम 32bit-aligned destination address */
	अगर (likely((0x03 & (अचिन्हित दीर्घ) dst) == 0) && len >= 4) अणु
		पढ़ोsl(fअगरo, dst, len >> 2);
		dst += len & ~0x03;
		len &= 0x03;
	पूर्ण
	/*
	 * Now पढ़ो the reमुख्यing 1 to 3 byte or complete length अगर
	 * unaligned address.
	 */
	अगर (len > 4) अणु
		क्रम (i = 0; i < (len >> 2); i++) अणु
			*(u32 *) dst = musb_पढ़ोl(fअगरo, 0);
			dst += 4;
		पूर्ण
		len &= 0x03;
	पूर्ण
	अगर (len > 0) अणु
		val = musb_पढ़ोl(fअगरo, 0);
		स_नकल(dst, &val, len);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा musb_platक्रमm_ops am35x_ops = अणु
	.quirks		= MUSB_DMA_INVENTRA | MUSB_INDEXED_EP,
	.init		= am35x_musb_init,
	.निकास		= am35x_musb_निकास,

	.पढ़ो_fअगरo	= am35x_पढ़ो_fअगरo,
#अगर_घोषित CONFIG_USB_INVENTRA_DMA
	.dma_init	= musbhs_dma_controller_create,
	.dma_निकास	= musbhs_dma_controller_destroy,
#पूर्ण_अगर
	.enable		= am35x_musb_enable,
	.disable	= am35x_musb_disable,

	.set_mode	= am35x_musb_set_mode,
	.try_idle	= am35x_musb_try_idle,

	.set_vbus	= am35x_musb_set_vbus,
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_info am35x_dev_info = अणु
	.name		= "musb-hdrc",
	.id		= PLATFORM_DEVID_AUTO,
	.dma_mask	= DMA_BIT_MASK(32),
पूर्ण;

अटल पूर्णांक am35x_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा musb_hdrc_platक्रमm_data	*pdata = dev_get_platdata(&pdev->dev);
	काष्ठा platक्रमm_device		*musb;
	काष्ठा am35x_glue		*glue;
	काष्ठा platक्रमm_device_info	pinfo;
	काष्ठा clk			*phy_clk;
	काष्ठा clk			*clk;

	पूर्णांक				ret = -ENOMEM;

	glue = kzalloc(माप(*glue), GFP_KERNEL);
	अगर (!glue)
		जाओ err0;

	phy_clk = clk_get(&pdev->dev, "fck");
	अगर (IS_ERR(phy_clk)) अणु
		dev_err(&pdev->dev, "failed to get PHY clock\n");
		ret = PTR_ERR(phy_clk);
		जाओ err3;
	पूर्ण

	clk = clk_get(&pdev->dev, "ick");
	अगर (IS_ERR(clk)) अणु
		dev_err(&pdev->dev, "failed to get clock\n");
		ret = PTR_ERR(clk);
		जाओ err4;
	पूर्ण

	ret = clk_enable(phy_clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to enable PHY clock\n");
		जाओ err5;
	पूर्ण

	ret = clk_enable(clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to enable clock\n");
		जाओ err6;
	पूर्ण

	glue->dev			= &pdev->dev;
	glue->phy_clk			= phy_clk;
	glue->clk			= clk;

	pdata->platक्रमm_ops		= &am35x_ops;

	glue->phy = usb_phy_generic_रेजिस्टर();
	अगर (IS_ERR(glue->phy)) अणु
		ret = PTR_ERR(glue->phy);
		जाओ err7;
	पूर्ण
	platक्रमm_set_drvdata(pdev, glue);

	pinfo = am35x_dev_info;
	pinfo.parent = &pdev->dev;
	pinfo.res = pdev->resource;
	pinfo.num_res = pdev->num_resources;
	pinfo.data = pdata;
	pinfo.size_data = माप(*pdata);

	glue->musb = musb = platक्रमm_device_रेजिस्टर_full(&pinfo);
	अगर (IS_ERR(musb)) अणु
		ret = PTR_ERR(musb);
		dev_err(&pdev->dev, "failed to register musb device: %d\n", ret);
		जाओ err8;
	पूर्ण

	वापस 0;

err8:
	usb_phy_generic_unरेजिस्टर(glue->phy);

err7:
	clk_disable(clk);

err6:
	clk_disable(phy_clk);

err5:
	clk_put(clk);

err4:
	clk_put(phy_clk);

err3:
	kमुक्त(glue);

err0:
	वापस ret;
पूर्ण

अटल पूर्णांक am35x_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा am35x_glue	*glue = platक्रमm_get_drvdata(pdev);

	platक्रमm_device_unरेजिस्टर(glue->musb);
	usb_phy_generic_unरेजिस्टर(glue->phy);
	clk_disable(glue->clk);
	clk_disable(glue->phy_clk);
	clk_put(glue->clk);
	clk_put(glue->phy_clk);
	kमुक्त(glue);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक am35x_suspend(काष्ठा device *dev)
अणु
	काष्ठा am35x_glue	*glue = dev_get_drvdata(dev);
	काष्ठा musb_hdrc_platक्रमm_data *plat = dev_get_platdata(dev);
	काष्ठा omap_musb_board_data *data = plat->board_data;

	/* Shutकरोwn the on-chip PHY and its PLL. */
	अगर (data->set_phy_घातer)
		data->set_phy_घातer(0);

	clk_disable(glue->phy_clk);
	clk_disable(glue->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक am35x_resume(काष्ठा device *dev)
अणु
	काष्ठा am35x_glue	*glue = dev_get_drvdata(dev);
	काष्ठा musb_hdrc_platक्रमm_data *plat = dev_get_platdata(dev);
	काष्ठा omap_musb_board_data *data = plat->board_data;
	पूर्णांक			ret;

	/* Start the on-chip PHY and its PLL. */
	अगर (data->set_phy_घातer)
		data->set_phy_घातer(1);

	ret = clk_enable(glue->phy_clk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable PHY clock\n");
		वापस ret;
	पूर्ण

	ret = clk_enable(glue->clk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable clock\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(am35x_pm_ops, am35x_suspend, am35x_resume);

अटल काष्ठा platक्रमm_driver am35x_driver = अणु
	.probe		= am35x_probe,
	.हटाओ		= am35x_हटाओ,
	.driver		= अणु
		.name	= "musb-am35x",
		.pm	= &am35x_pm_ops,
	पूर्ण,
पूर्ण;

MODULE_DESCRIPTION("AM35x MUSB Glue Layer");
MODULE_AUTHOR("Ajay Kumar Gupta <ajay.gupta@ti.com>");
MODULE_LICENSE("GPL v2");
module_platक्रमm_driver(am35x_driver);
