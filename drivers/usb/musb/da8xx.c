<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Texas Instruments DA8xx/OMAP-L1x "glue layer"
 *
 * Copyright (c) 2008-2009 MontaVista Software, Inc. <source@mvista.com>
 *
 * Based on the DaVinci "glue layer" code.
 * Copyright (C) 2005-2006 by Texas Instruments
 *
 * DT support
 * Copyright (c) 2016 Petr Kulhavy <petr@barix.com>
 *
 * This file is part of the Inventra Controller Driver क्रम Linux.
 */

#समावेश <linux/module.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/usb/usb_phy_generic.h>

#समावेश "musb_core.h"

/*
 * DA8XX specअगरic definitions
 */

/* USB 2.0 OTG module रेजिस्टरs */
#घोषणा DA8XX_USB_REVISION_REG	0x00
#घोषणा DA8XX_USB_CTRL_REG	0x04
#घोषणा DA8XX_USB_STAT_REG	0x08
#घोषणा DA8XX_USB_EMULATION_REG 0x0c
#घोषणा DA8XX_USB_SRP_FIX_TIME_REG 0x18
#घोषणा DA8XX_USB_INTR_SRC_REG	0x20
#घोषणा DA8XX_USB_INTR_SRC_SET_REG 0x24
#घोषणा DA8XX_USB_INTR_SRC_CLEAR_REG 0x28
#घोषणा DA8XX_USB_INTR_MASK_REG 0x2c
#घोषणा DA8XX_USB_INTR_MASK_SET_REG 0x30
#घोषणा DA8XX_USB_INTR_MASK_CLEAR_REG 0x34
#घोषणा DA8XX_USB_INTR_SRC_MASKED_REG 0x38
#घोषणा DA8XX_USB_END_OF_INTR_REG 0x3c
#घोषणा DA8XX_USB_GENERIC_RNDIS_EP_SIZE_REG(n) (0x50 + (((n) - 1) << 2))

/* Control रेजिस्टर bits */
#घोषणा DA8XX_SOFT_RESET_MASK	1

#घोषणा DA8XX_USB_TX_EP_MASK	0x1f		/* EP0 + 4 Tx EPs */
#घोषणा DA8XX_USB_RX_EP_MASK	0x1e		/* 4 Rx EPs */

/* USB पूर्णांकerrupt रेजिस्टर bits */
#घोषणा DA8XX_INTR_USB_SHIFT	16
#घोषणा DA8XX_INTR_USB_MASK	(0x1ff << DA8XX_INTR_USB_SHIFT) /* 8 Mentor */
					/* पूर्णांकerrupts and DRVVBUS पूर्णांकerrupt */
#घोषणा DA8XX_INTR_DRVVBUS	0x100
#घोषणा DA8XX_INTR_RX_SHIFT	8
#घोषणा DA8XX_INTR_RX_MASK	(DA8XX_USB_RX_EP_MASK << DA8XX_INTR_RX_SHIFT)
#घोषणा DA8XX_INTR_TX_SHIFT	0
#घोषणा DA8XX_INTR_TX_MASK	(DA8XX_USB_TX_EP_MASK << DA8XX_INTR_TX_SHIFT)

#घोषणा DA8XX_MENTOR_CORE_OFFSET 0x400

काष्ठा da8xx_glue अणु
	काष्ठा device		*dev;
	काष्ठा platक्रमm_device	*musb;
	काष्ठा platक्रमm_device	*usb_phy;
	काष्ठा clk		*clk;
	काष्ठा phy		*phy;
पूर्ण;

/*
 * Because we करोn't set CTRL.UINT, it's "important" to:
 *	- not पढ़ो/ग_लिखो INTRUSB/INTRUSBE (except during
 *	  initial setup, as a workaround);
 *	- use INTSET/INTCLR instead.
 */

/**
 * da8xx_musb_enable - enable पूर्णांकerrupts
 */
अटल व्योम da8xx_musb_enable(काष्ठा musb *musb)
अणु
	व्योम __iomem *reg_base = musb->ctrl_base;
	u32 mask;

	/* Workaround: setup IRQs through both रेजिस्टर sets. */
	mask = ((musb->epmask & DA8XX_USB_TX_EP_MASK) << DA8XX_INTR_TX_SHIFT) |
	       ((musb->epmask & DA8XX_USB_RX_EP_MASK) << DA8XX_INTR_RX_SHIFT) |
	       DA8XX_INTR_USB_MASK;
	musb_ग_लिखोl(reg_base, DA8XX_USB_INTR_MASK_SET_REG, mask);

	/* Force the DRVVBUS IRQ so we can start polling क्रम ID change. */
	musb_ग_लिखोl(reg_base, DA8XX_USB_INTR_SRC_SET_REG,
			DA8XX_INTR_DRVVBUS << DA8XX_INTR_USB_SHIFT);
पूर्ण

/**
 * da8xx_musb_disable - disable HDRC and flush पूर्णांकerrupts
 */
अटल व्योम da8xx_musb_disable(काष्ठा musb *musb)
अणु
	व्योम __iomem *reg_base = musb->ctrl_base;

	musb_ग_लिखोl(reg_base, DA8XX_USB_INTR_MASK_CLEAR_REG,
		    DA8XX_INTR_USB_MASK |
		    DA8XX_INTR_TX_MASK | DA8XX_INTR_RX_MASK);
	musb_ग_लिखोl(reg_base, DA8XX_USB_END_OF_INTR_REG, 0);
पूर्ण

#घोषणा portstate(sपंचांगt)		sपंचांगt

अटल व्योम da8xx_musb_set_vbus(काष्ठा musb *musb, पूर्णांक is_on)
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
	 * We poll because DaVinci's won't expose several OTG-critical
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
		/*
		 * Wait till VBUS falls below SessionEnd (~0.2 V); the 1.3
		 * RTL seems to mis-handle session "start" otherwise (or in
		 * our हाल "recover"), in routine "VBUS was valid by the समय
		 * VBUSERR got reported during क्रमागतeration" हालs.
		 */
		अगर (devctl & MUSB_DEVCTL_VBUS) अणु
			mod_समयr(&musb->dev_समयr, jअगरfies + POLL_SECONDS * HZ);
			अवरोध;
		पूर्ण
		musb->xceiv->otg->state = OTG_STATE_A_WAIT_VRISE;
		musb_ग_लिखोl(musb->ctrl_base, DA8XX_USB_INTR_SRC_SET_REG,
			    MUSB_INTR_VBUSERROR << DA8XX_INTR_USB_SHIFT);
		अवरोध;
	हाल OTG_STATE_B_IDLE:
		/*
		 * There's no ID-changed IRQ, so we have no good way to tell
		 * when to चयन to the A-Default state machine (by setting
		 * the DEVCTL.Session bit).
		 *
		 * Workaround:  whenever we're in B_IDLE, try setting the
		 * session flag every few seconds.  If it works, ID was
		 * grounded and we're now in the A-Default state machine.
		 *
		 * NOTE: setting the session flag is _supposed_ to trigger
		 * SRP but clearly it करोesn't.
		 */
		musb_ग_लिखोb(mregs, MUSB_DEVCTL, devctl | MUSB_DEVCTL_SESSION);
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

अटल व्योम da8xx_musb_try_idle(काष्ठा musb *musb, अचिन्हित दीर्घ समयout)
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

अटल irqवापस_t da8xx_musb_पूर्णांकerrupt(पूर्णांक irq, व्योम *hci)
अणु
	काष्ठा musb		*musb = hci;
	व्योम __iomem		*reg_base = musb->ctrl_base;
	अचिन्हित दीर्घ		flags;
	irqवापस_t		ret = IRQ_NONE;
	u32			status;

	spin_lock_irqsave(&musb->lock, flags);

	/*
	 * NOTE: DA8XX shaकरोws the Mentor IRQs.  Don't manage them through
	 * the Mentor रेजिस्टरs (except क्रम setup), use the TI ones and EOI.
	 */

	/* Acknowledge and handle non-CPPI पूर्णांकerrupts */
	status = musb_पढ़ोl(reg_base, DA8XX_USB_INTR_SRC_MASKED_REG);
	अगर (!status)
		जाओ eoi;

	musb_ग_लिखोl(reg_base, DA8XX_USB_INTR_SRC_CLEAR_REG, status);
	dev_dbg(musb->controller, "USB IRQ %08x\n", status);

	musb->पूर्णांक_rx = (status & DA8XX_INTR_RX_MASK) >> DA8XX_INTR_RX_SHIFT;
	musb->पूर्णांक_tx = (status & DA8XX_INTR_TX_MASK) >> DA8XX_INTR_TX_SHIFT;
	musb->पूर्णांक_usb = (status & DA8XX_INTR_USB_MASK) >> DA8XX_INTR_USB_SHIFT;

	/*
	 * DRVVBUS IRQs are the only proxy we have (a very poor one!) क्रम
	 * DA8xx's missing ID change IRQ.  We need an ID change IRQ to
	 * चयन appropriately between halves of the OTG state machine.
	 * Managing DEVCTL.Session per Mentor करोcs requires that we know its
	 * value but DEVCTL.BDevice is invalid without DEVCTL.Session set.
	 * Also, DRVVBUS pulses क्रम SRP (but not at 5 V)...
	 */
	अगर (status & (DA8XX_INTR_DRVVBUS << DA8XX_INTR_USB_SHIFT)) अणु
		पूर्णांक drvvbus = musb_पढ़ोl(reg_base, DA8XX_USB_STAT_REG);
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
		पूर्ण अन्यथा अगर (!(musb->पूर्णांक_usb & MUSB_INTR_BABBLE)) अणु
			/*
			 * When babble condition happens, drvvbus पूर्णांकerrupt
			 * is also generated. Ignore this drvvbus पूर्णांकerrupt
			 * and let babble पूर्णांकerrupt handler recovers the
			 * controller; otherwise, the host-mode flag is lost
			 * due to the MUSB_DEV_MODE() call below and babble
			 * recovery logic will not be called.
			 */
			musb->is_active = 0;
			MUSB_DEV_MODE(musb);
			musb->xceiv->otg->state = OTG_STATE_B_IDLE;
			portstate(musb->port1_status &= ~USB_PORT_STAT_POWER);
		पूर्ण

		dev_dbg(musb->controller, "VBUS %s (%s)%s, devctl %02x\n",
				drvvbus ? "on" : "off",
				usb_otg_state_string(musb->xceiv->otg->state),
				err ? " ERROR" : "",
				devctl);
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (musb->पूर्णांक_tx || musb->पूर्णांक_rx || musb->पूर्णांक_usb)
		ret |= musb_पूर्णांकerrupt(musb);

 eoi:
	/* EOI needs to be written क्रम the IRQ to be re-निश्चितed. */
	अगर (ret == IRQ_HANDLED || status)
		musb_ग_लिखोl(reg_base, DA8XX_USB_END_OF_INTR_REG, 0);

	/* Poll क्रम ID change */
	अगर (musb->xceiv->otg->state == OTG_STATE_B_IDLE)
		mod_समयr(&musb->dev_समयr, jअगरfies + POLL_SECONDS * HZ);

	spin_unlock_irqrestore(&musb->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक da8xx_musb_set_mode(काष्ठा musb *musb, u8 musb_mode)
अणु
	काष्ठा da8xx_glue *glue = dev_get_drvdata(musb->controller->parent);
	क्रमागत phy_mode phy_mode;

	/*
	 * The PHY has some issues when it is क्रमced in device or host mode.
	 * Unless the user request another mode, configure the PHY in OTG mode.
	 */
	अगर (!musb->is_initialized)
		वापस phy_set_mode(glue->phy, PHY_MODE_USB_OTG);

	चयन (musb_mode) अणु
	हाल MUSB_HOST:		/* Force VBUS valid, ID = 0 */
		phy_mode = PHY_MODE_USB_HOST;
		अवरोध;
	हाल MUSB_PERIPHERAL:	/* Force VBUS valid, ID = 1 */
		phy_mode = PHY_MODE_USB_DEVICE;
		अवरोध;
	हाल MUSB_OTG:		/* Don't override the VBUS/ID comparators */
		phy_mode = PHY_MODE_USB_OTG;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस phy_set_mode(glue->phy, phy_mode);
पूर्ण

अटल पूर्णांक da8xx_musb_init(काष्ठा musb *musb)
अणु
	काष्ठा da8xx_glue *glue = dev_get_drvdata(musb->controller->parent);
	व्योम __iomem *reg_base = musb->ctrl_base;
	u32 rev;
	पूर्णांक ret = -ENODEV;

	musb->mregs += DA8XX_MENTOR_CORE_OFFSET;

	ret = clk_prepare_enable(glue->clk);
	अगर (ret) अणु
		dev_err(glue->dev, "failed to enable clock\n");
		वापस ret;
	पूर्ण

	/* Returns zero अगर e.g. not घड़ीed */
	rev = musb_पढ़ोl(reg_base, DA8XX_USB_REVISION_REG);
	अगर (!rev)
		जाओ fail;

	musb->xceiv = usb_get_phy(USB_PHY_TYPE_USB2);
	अगर (IS_ERR_OR_शून्य(musb->xceiv)) अणु
		ret = -EPROBE_DEFER;
		जाओ fail;
	पूर्ण

	समयr_setup(&musb->dev_समयr, otg_समयr, 0);

	/* Reset the controller */
	musb_ग_लिखोl(reg_base, DA8XX_USB_CTRL_REG, DA8XX_SOFT_RESET_MASK);

	/* Start the on-chip PHY and its PLL. */
	ret = phy_init(glue->phy);
	अगर (ret) अणु
		dev_err(glue->dev, "Failed to init phy.\n");
		जाओ fail;
	पूर्ण

	ret = phy_घातer_on(glue->phy);
	अगर (ret) अणु
		dev_err(glue->dev, "Failed to power on phy.\n");
		जाओ err_phy_घातer_on;
	पूर्ण

	msleep(5);

	/* NOTE: IRQs are in mixed mode, not bypass to pure MUSB */
	pr_debug("DA8xx OTG revision %08x, control %02x\n", rev,
		 musb_पढ़ोb(reg_base, DA8XX_USB_CTRL_REG));

	musb->isr = da8xx_musb_पूर्णांकerrupt;
	वापस 0;

err_phy_घातer_on:
	phy_निकास(glue->phy);
fail:
	clk_disable_unprepare(glue->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक da8xx_musb_निकास(काष्ठा musb *musb)
अणु
	काष्ठा da8xx_glue *glue = dev_get_drvdata(musb->controller->parent);

	del_समयr_sync(&musb->dev_समयr);

	phy_घातer_off(glue->phy);
	phy_निकास(glue->phy);
	clk_disable_unprepare(glue->clk);

	usb_put_phy(musb->xceiv);

	वापस 0;
पूर्ण

अटल अंतरभूत u8 get_vbus_घातer(काष्ठा device *dev)
अणु
	काष्ठा regulator *vbus_supply;
	पूर्णांक current_uA;

	vbus_supply = regulator_get_optional(dev, "vbus");
	अगर (IS_ERR(vbus_supply))
		वापस 255;
	current_uA = regulator_get_current_limit(vbus_supply);
	regulator_put(vbus_supply);
	अगर (current_uA <= 0 || current_uA > 510000)
		वापस 255;
	वापस current_uA / 1000 / 2;
पूर्ण

#अगर_घोषित CONFIG_USB_TI_CPPI41_DMA
अटल व्योम da8xx_dma_controller_callback(काष्ठा dma_controller *c)
अणु
	काष्ठा musb *musb = c->musb;
	व्योम __iomem *reg_base = musb->ctrl_base;

	musb_ग_लिखोl(reg_base, DA8XX_USB_END_OF_INTR_REG, 0);
पूर्ण

अटल काष्ठा dma_controller *
da8xx_dma_controller_create(काष्ठा musb *musb, व्योम __iomem *base)
अणु
	काष्ठा dma_controller *controller;

	controller = cppi41_dma_controller_create(musb, base);
	अगर (IS_ERR_OR_शून्य(controller))
		वापस controller;

	controller->dma_callback = da8xx_dma_controller_callback;

	वापस controller;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा musb_platक्रमm_ops da8xx_ops = अणु
	.quirks		= MUSB_INDEXED_EP | MUSB_PRESERVE_SESSION |
			  MUSB_DMA_CPPI41 | MUSB_DA8XX,
	.init		= da8xx_musb_init,
	.निकास		= da8xx_musb_निकास,

	.fअगरo_mode	= 2,
#अगर_घोषित CONFIG_USB_TI_CPPI41_DMA
	.dma_init	= da8xx_dma_controller_create,
	.dma_निकास	= cppi41_dma_controller_destroy,
#पूर्ण_अगर
	.enable		= da8xx_musb_enable,
	.disable	= da8xx_musb_disable,

	.set_mode	= da8xx_musb_set_mode,
	.try_idle	= da8xx_musb_try_idle,

	.set_vbus	= da8xx_musb_set_vbus,
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_info da8xx_dev_info = अणु
	.name		= "musb-hdrc",
	.id		= PLATFORM_DEVID_AUTO,
	.dma_mask	= DMA_BIT_MASK(32),
पूर्ण;

अटल स्थिर काष्ठा musb_hdrc_config da8xx_config = अणु
	.ram_bits = 10,
	.num_eps = 5,
	.multipoपूर्णांक = 1,
पूर्ण;

अटल काष्ठा of_dev_auxdata da8xx_auxdata_lookup[] = अणु
	OF_DEV_AUXDATA("ti,da830-cppi41", 0x01e01000, "cppi41-dmaengine",
		       शून्य),
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक da8xx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource musb_resources[2];
	काष्ठा musb_hdrc_platक्रमm_data	*pdata = dev_get_platdata(&pdev->dev);
	काष्ठा da8xx_glue		*glue;
	काष्ठा platक्रमm_device_info	pinfo;
	काष्ठा clk			*clk;
	काष्ठा device_node		*np = pdev->dev.of_node;
	पूर्णांक				ret;

	glue = devm_kzalloc(&pdev->dev, माप(*glue), GFP_KERNEL);
	अगर (!glue)
		वापस -ENOMEM;

	clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(clk)) अणु
		dev_err(&pdev->dev, "failed to get clock\n");
		वापस PTR_ERR(clk);
	पूर्ण

	glue->phy = devm_phy_get(&pdev->dev, "usb-phy");
	अगर (IS_ERR(glue->phy)) अणु
		अगर (PTR_ERR(glue->phy) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "failed to get phy\n");
		वापस PTR_ERR(glue->phy);
	पूर्ण

	glue->dev			= &pdev->dev;
	glue->clk			= clk;

	अगर (IS_ENABLED(CONFIG_OF) && np) अणु
		pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
		अगर (!pdata)
			वापस -ENOMEM;

		pdata->config	= &da8xx_config;
		pdata->mode	= musb_get_mode(&pdev->dev);
		pdata->घातer	= get_vbus_घातer(&pdev->dev);
	पूर्ण

	pdata->platक्रमm_ops		= &da8xx_ops;

	glue->usb_phy = usb_phy_generic_रेजिस्टर();
	ret = PTR_ERR_OR_ZERO(glue->usb_phy);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register usb_phy\n");
		वापस ret;
	पूर्ण
	platक्रमm_set_drvdata(pdev, glue);

	ret = of_platक्रमm_populate(pdev->dev.of_node, शून्य,
				   da8xx_auxdata_lookup, &pdev->dev);
	अगर (ret)
		वापस ret;

	स_रखो(musb_resources, 0x00, माप(*musb_resources) *
			ARRAY_SIZE(musb_resources));

	musb_resources[0].name = pdev->resource[0].name;
	musb_resources[0].start = pdev->resource[0].start;
	musb_resources[0].end = pdev->resource[0].end;
	musb_resources[0].flags = pdev->resource[0].flags;

	musb_resources[1].name = pdev->resource[1].name;
	musb_resources[1].start = pdev->resource[1].start;
	musb_resources[1].end = pdev->resource[1].end;
	musb_resources[1].flags = pdev->resource[1].flags;

	pinfo = da8xx_dev_info;
	pinfo.parent = &pdev->dev;
	pinfo.res = musb_resources;
	pinfo.num_res = ARRAY_SIZE(musb_resources);
	pinfo.data = pdata;
	pinfo.size_data = माप(*pdata);

	glue->musb = platक्रमm_device_रेजिस्टर_full(&pinfo);
	ret = PTR_ERR_OR_ZERO(glue->musb);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register musb device: %d\n", ret);
		usb_phy_generic_unरेजिस्टर(glue->usb_phy);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक da8xx_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा da8xx_glue		*glue = platक्रमm_get_drvdata(pdev);

	platक्रमm_device_unरेजिस्टर(glue->musb);
	usb_phy_generic_unरेजिस्टर(glue->usb_phy);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक da8xx_suspend(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा da8xx_glue *glue = dev_get_drvdata(dev);

	ret = phy_घातer_off(glue->phy);
	अगर (ret)
		वापस ret;
	clk_disable_unprepare(glue->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक da8xx_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा da8xx_glue *glue = dev_get_drvdata(dev);

	ret = clk_prepare_enable(glue->clk);
	अगर (ret)
		वापस ret;
	वापस phy_घातer_on(glue->phy);
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(da8xx_pm_ops, da8xx_suspend, da8xx_resume);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id da8xx_id_table[] = अणु
	अणु
		.compatible = "ti,da830-musb",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, da8xx_id_table);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver da8xx_driver = अणु
	.probe		= da8xx_probe,
	.हटाओ		= da8xx_हटाओ,
	.driver		= अणु
		.name	= "musb-da8xx",
		.pm = &da8xx_pm_ops,
		.of_match_table = of_match_ptr(da8xx_id_table),
	पूर्ण,
पूर्ण;

MODULE_DESCRIPTION("DA8xx/OMAP-L1x MUSB Glue Layer");
MODULE_AUTHOR("Sergei Shtylyov <sshtylyov@ru.mvista.com>");
MODULE_LICENSE("GPL v2");
module_platक्रमm_driver(da8xx_driver);
