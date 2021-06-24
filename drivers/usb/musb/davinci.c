<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2005-2006 by Texas Instruments
 *
 * This file is part of the Inventra Controller Driver क्रम Linux.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/list.h>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/usb/usb_phy_generic.h>

#समावेश <mach/cputype.h>
#समावेश <mach/hardware.h>

#समावेश <यंत्र/mach-types.h>

#समावेश "musb_core.h"

#समावेश "davinci.h"
#समावेश "cppi_dma.h"


#घोषणा USB_PHY_CTRL	IO_ADDRESS(USBPHY_CTL_PADDR)
#घोषणा DM355_DEEPSLEEP	IO_ADDRESS(DM355_DEEPSLEEP_PADDR)

काष्ठा davinci_glue अणु
	काष्ठा device		*dev;
	काष्ठा platक्रमm_device	*musb;
	काष्ठा clk		*clk;
	bool			vbus_state;
	काष्ठा gpio_desc	*vbus;
	काष्ठा work_काष्ठा	vbus_work;
पूर्ण;

/* REVISIT (PM) we should be able to keep the PHY in low घातer mode most
 * of the समय (24 MHZ oscillator and PLL off, etc) by setting POWER.D0
 * and, when in host mode, स्वतःsuspending idle root ports... PHYPLLON
 * (overriding SUSPENDM?) then likely needs to stay off.
 */

अटल अंतरभूत व्योम phy_on(व्योम)
अणु
	u32	phy_ctrl = __raw_पढ़ोl(USB_PHY_CTRL);

	/* घातer everything up; start the on-chip PHY and its PLL */
	phy_ctrl &= ~(USBPHY_OSCPDWN | USBPHY_OTGPDWN | USBPHY_PHYPDWN);
	phy_ctrl |= USBPHY_SESNDEN | USBPHY_VBDTCTEN | USBPHY_PHYPLLON;
	__raw_ग_लिखोl(phy_ctrl, USB_PHY_CTRL);

	/* रुको क्रम PLL to lock beक्रमe proceeding */
	जबतक ((__raw_पढ़ोl(USB_PHY_CTRL) & USBPHY_PHYCLKGD) == 0)
		cpu_relax();
पूर्ण

अटल अंतरभूत व्योम phy_off(व्योम)
अणु
	u32	phy_ctrl = __raw_पढ़ोl(USB_PHY_CTRL);

	/* घातerकरोwn the on-chip PHY, its PLL, and the OTG block */
	phy_ctrl &= ~(USBPHY_SESNDEN | USBPHY_VBDTCTEN | USBPHY_PHYPLLON);
	phy_ctrl |= USBPHY_OSCPDWN | USBPHY_OTGPDWN | USBPHY_PHYPDWN;
	__raw_ग_लिखोl(phy_ctrl, USB_PHY_CTRL);
पूर्ण

अटल पूर्णांक dma_off = 1;

अटल व्योम davinci_musb_enable(काष्ठा musb *musb)
अणु
	u32	पंचांगp, old, val;

	/* workaround:  setup irqs through both रेजिस्टर sets */
	पंचांगp = (musb->epmask & DAVINCI_USB_TX_ENDPTS_MASK)
			<< DAVINCI_USB_TXINT_SHIFT;
	musb_ग_लिखोl(musb->ctrl_base, DAVINCI_USB_INT_MASK_SET_REG, पंचांगp);
	old = पंचांगp;
	पंचांगp = (musb->epmask & (0xfffe & DAVINCI_USB_RX_ENDPTS_MASK))
			<< DAVINCI_USB_RXINT_SHIFT;
	musb_ग_लिखोl(musb->ctrl_base, DAVINCI_USB_INT_MASK_SET_REG, पंचांगp);
	पंचांगp |= old;

	val = ~MUSB_INTR_SOF;
	पंचांगp |= ((val & 0x01ff) << DAVINCI_USB_USBINT_SHIFT);
	musb_ग_लिखोl(musb->ctrl_base, DAVINCI_USB_INT_MASK_SET_REG, पंचांगp);

	अगर (is_dma_capable() && !dma_off)
		prपूर्णांकk(KERN_WARNING "%s %s: dma not reactivated\n",
				__खाता__, __func__);
	अन्यथा
		dma_off = 0;

	/* क्रमce a DRVVBUS irq so we can start polling क्रम ID change */
	musb_ग_लिखोl(musb->ctrl_base, DAVINCI_USB_INT_SET_REG,
			DAVINCI_INTR_DRVVBUS << DAVINCI_USB_USBINT_SHIFT);
पूर्ण

/*
 * Disable the HDRC and flush पूर्णांकerrupts
 */
अटल व्योम davinci_musb_disable(काष्ठा musb *musb)
अणु
	/* because we करोn't set CTRLR.UINT, "important" to:
	 *  - not पढ़ो/ग_लिखो INTRUSB/INTRUSBE
	 *  - (except during initial setup, as workaround)
	 *  - use INTSETR/INTCLRR instead
	 */
	musb_ग_लिखोl(musb->ctrl_base, DAVINCI_USB_INT_MASK_CLR_REG,
			  DAVINCI_USB_USBINT_MASK
			| DAVINCI_USB_TXINT_MASK
			| DAVINCI_USB_RXINT_MASK);
	musb_ग_लिखोl(musb->ctrl_base, DAVINCI_USB_EOI_REG, 0);

	अगर (is_dma_capable() && !dma_off)
		WARNING("dma still active\n");
पूर्ण


#घोषणा	portstate(sपंचांगt)		sपंचांगt

/*
 * VBUS SWITCHING IS BOARD-SPECIFIC ... at least क्रम the DM6446 EVM,
 * which करोesn't wire DRVVBUS to the FET that चयनes it.  Unclear
 * अगर that's a problem with the DM6446 chip or just with that board.
 *
 * In either हाल, the DM355 EVM स्वतःmates DRVVBUS the normal way,
 * when J10 is out, and TI करोcuments it as handling OTG.
 */

/* I2C operations are always synchronous, and require a task context.
 * With unloaded प्रणालीs, using the shared workqueue seems to suffice
 * to satisfy the 100msec A_WAIT_VRISE समयout...
 */
अटल व्योम evm_deferred_drvvbus(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा davinci_glue *glue = container_of(work, काष्ठा davinci_glue,
						 vbus_work);

	gpiod_set_value_cansleep(glue->vbus, glue->vbus_state);
	glue->vbus_state = !glue->vbus_state;
पूर्ण

अटल व्योम davinci_musb_source_घातer(काष्ठा musb *musb, पूर्णांक is_on,
				      पूर्णांक immediate)
अणु
	काष्ठा davinci_glue *glue = dev_get_drvdata(musb->controller->parent);

	/* This GPIO handling is entirely optional */
	अगर (!glue->vbus)
		वापस;

	अगर (is_on)
		is_on = 1;

	अगर (glue->vbus_state == is_on)
		वापस;
	/* 0/1 vs "-1 == unknown/init" */
	glue->vbus_state = !is_on;

	अगर (machine_is_davinci_evm()) अणु
		अगर (immediate)
			gpiod_set_value_cansleep(glue->vbus, glue->vbus_state);
		अन्यथा
			schedule_work(&glue->vbus_work);
	पूर्ण
	अगर (immediate)
		glue->vbus_state = is_on;
पूर्ण

अटल व्योम davinci_musb_set_vbus(काष्ठा musb *musb, पूर्णांक is_on)
अणु
	WARN_ON(is_on && is_peripheral_active(musb));
	davinci_musb_source_घातer(musb, is_on, 0);
पूर्ण


#घोषणा	POLL_SECONDS	2

अटल व्योम otg_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा musb		*musb = from_समयr(musb, t, dev_समयr);
	व्योम __iomem		*mregs = musb->mregs;
	u8			devctl;
	अचिन्हित दीर्घ		flags;

	/* We poll because DaVinci's won't expose several OTG-critical
	* status change events (from the transceiver) otherwise.
	 */
	devctl = musb_पढ़ोb(mregs, MUSB_DEVCTL);
	dev_dbg(musb->controller, "poll devctl %02x (%s)\n", devctl,
		usb_otg_state_string(musb->xceiv->otg->state));

	spin_lock_irqsave(&musb->lock, flags);
	चयन (musb->xceiv->otg->state) अणु
	हाल OTG_STATE_A_WAIT_VFALL:
		/* Wait till VBUS falls below SessionEnd (~0.2V); the 1.3 RTL
		 * seems to mis-handle session "start" otherwise (or in our
		 * हाल "recover"), in routine "VBUS was valid by the समय
		 * VBUSERR got reported during क्रमागतeration" हालs.
		 */
		अगर (devctl & MUSB_DEVCTL_VBUS) अणु
			mod_समयr(&musb->dev_समयr, jअगरfies + POLL_SECONDS * HZ);
			अवरोध;
		पूर्ण
		musb->xceiv->otg->state = OTG_STATE_A_WAIT_VRISE;
		musb_ग_लिखोl(musb->ctrl_base, DAVINCI_USB_INT_SET_REG,
			MUSB_INTR_VBUSERROR << DAVINCI_USB_USBINT_SHIFT);
		अवरोध;
	हाल OTG_STATE_B_IDLE:
		/*
		 * There's no ID-changed IRQ, so we have no good way to tell
		 * when to चयन to the A-Default state machine (by setting
		 * the DEVCTL.SESSION flag).
		 *
		 * Workaround:  whenever we're in B_IDLE, try setting the
		 * session flag every few seconds.  If it works, ID was
		 * grounded and we're now in the A-Default state machine.
		 *
		 * NOTE setting the session flag is _supposed_ to trigger
		 * SRP, but clearly it करोesn't.
		 */
		musb_ग_लिखोb(mregs, MUSB_DEVCTL,
				devctl | MUSB_DEVCTL_SESSION);
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

अटल irqवापस_t davinci_musb_पूर्णांकerrupt(पूर्णांक irq, व्योम *__hci)
अणु
	अचिन्हित दीर्घ	flags;
	irqवापस_t	retval = IRQ_NONE;
	काष्ठा musb	*musb = __hci;
	काष्ठा usb_otg	*otg = musb->xceiv->otg;
	व्योम __iomem	*tibase = musb->ctrl_base;
	काष्ठा cppi	*cppi;
	u32		पंचांगp;

	spin_lock_irqsave(&musb->lock, flags);

	/* NOTE: DaVinci shaकरोws the Mentor IRQs.  Don't manage them through
	 * the Mentor रेजिस्टरs (except क्रम setup), use the TI ones and EOI.
	 *
	 * Docs describe irq "vector" रेजिस्टरs associated with the CPPI and
	 * USB EOI रेजिस्टरs.  These hold a biपंचांगask corresponding to the
	 * current IRQ, not an irq handler address.  Would using those bits
	 * resolve some of the races observed in this dispatch code??
	 */

	/* CPPI पूर्णांकerrupts share the same IRQ line, but have their own
	 * mask, state, "vector", and EOI रेजिस्टरs.
	 */
	cppi = container_of(musb->dma_controller, काष्ठा cppi, controller);
	अगर (is_cppi_enabled(musb) && musb->dma_controller && !cppi->irq)
		retval = cppi_पूर्णांकerrupt(irq, __hci);

	/* ack and handle non-CPPI पूर्णांकerrupts */
	पंचांगp = musb_पढ़ोl(tibase, DAVINCI_USB_INT_SRC_MASKED_REG);
	musb_ग_लिखोl(tibase, DAVINCI_USB_INT_SRC_CLR_REG, पंचांगp);
	dev_dbg(musb->controller, "IRQ %08x\n", पंचांगp);

	musb->पूर्णांक_rx = (पंचांगp & DAVINCI_USB_RXINT_MASK)
			>> DAVINCI_USB_RXINT_SHIFT;
	musb->पूर्णांक_tx = (पंचांगp & DAVINCI_USB_TXINT_MASK)
			>> DAVINCI_USB_TXINT_SHIFT;
	musb->पूर्णांक_usb = (पंचांगp & DAVINCI_USB_USBINT_MASK)
			>> DAVINCI_USB_USBINT_SHIFT;

	/* DRVVBUS irqs are the only proxy we have (a very poor one!) क्रम
	 * DaVinci's missing ID change IRQ.  We need an ID change IRQ to
	 * चयन appropriately between halves of the OTG state machine.
	 * Managing DEVCTL.SESSION per Mentor करोcs requires we know its
	 * value, but DEVCTL.BDEVICE is invalid without DEVCTL.SESSION set.
	 * Also, DRVVBUS pulses क्रम SRP (but not at 5V) ...
	 */
	अगर (पंचांगp & (DAVINCI_INTR_DRVVBUS << DAVINCI_USB_USBINT_SHIFT)) अणु
		पूर्णांक	drvvbus = musb_पढ़ोl(tibase, DAVINCI_USB_STAT_REG);
		व्योम __iomem *mregs = musb->mregs;
		u8	devctl = musb_पढ़ोb(mregs, MUSB_DEVCTL);
		पूर्णांक	err = musb->पूर्णांक_usb & MUSB_INTR_VBUSERROR;

		err = musb->पूर्णांक_usb & MUSB_INTR_VBUSERROR;
		अगर (err) अणु
			/* The Mentor core करोesn't debounce VBUS as needed
			 * to cope with device connect current spikes. This
			 * means it's not uncommon क्रम bus-घातered devices
			 * to get VBUS errors during क्रमागतeration.
			 *
			 * This is a workaround, but newer RTL from Mentor
			 * seems to allow a better one: "re"starting sessions
			 * without रुकोing (on EVM, a **दीर्घ** समय) क्रम VBUS
			 * to stop रेजिस्टरing in devctl.
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

		/* NOTE:  this must complete घातeron within 100 msec
		 * (OTG_TIME_A_WAIT_VRISE) but we करोn't check क्रम that.
		 */
		davinci_musb_source_घातer(musb, drvvbus, 0);
		dev_dbg(musb->controller, "VBUS %s (%s)%s, devctl %02x\n",
				drvvbus ? "on" : "off",
				usb_otg_state_string(musb->xceiv->otg->state),
				err ? " ERROR" : "",
				devctl);
		retval = IRQ_HANDLED;
	पूर्ण

	अगर (musb->पूर्णांक_tx || musb->पूर्णांक_rx || musb->पूर्णांक_usb)
		retval |= musb_पूर्णांकerrupt(musb);

	/* irq stays निश्चितed until EOI is written */
	musb_ग_लिखोl(tibase, DAVINCI_USB_EOI_REG, 0);

	/* poll क्रम ID change */
	अगर (musb->xceiv->otg->state == OTG_STATE_B_IDLE)
		mod_समयr(&musb->dev_समयr, jअगरfies + POLL_SECONDS * HZ);

	spin_unlock_irqrestore(&musb->lock, flags);

	वापस retval;
पूर्ण

अटल पूर्णांक davinci_musb_set_mode(काष्ठा musb *musb, u8 mode)
अणु
	/* EVM can't करो this (right?) */
	वापस -EIO;
पूर्ण

अटल पूर्णांक davinci_musb_init(काष्ठा musb *musb)
अणु
	व्योम __iomem	*tibase = musb->ctrl_base;
	u32		revision;
	पूर्णांक 		ret = -ENODEV;

	musb->xceiv = usb_get_phy(USB_PHY_TYPE_USB2);
	अगर (IS_ERR_OR_शून्य(musb->xceiv)) अणु
		ret = -EPROBE_DEFER;
		जाओ unरेजिस्टर;
	पूर्ण

	musb->mregs += DAVINCI_BASE_OFFSET;

	/* वापसs zero अगर e.g. not घड़ीed */
	revision = musb_पढ़ोl(tibase, DAVINCI_USB_VERSION_REG);
	अगर (revision == 0)
		जाओ fail;

	समयr_setup(&musb->dev_समयr, otg_समयr, 0);

	davinci_musb_source_घातer(musb, 0, 1);

	/* dm355 EVM swaps D+/D- क्रम संकेत पूर्णांकegrity, and
	 * is घड़ीed from the मुख्य 24 MHz crystal.
	 */
	अगर (machine_is_davinci_dm355_evm()) अणु
		u32	phy_ctrl = __raw_पढ़ोl(USB_PHY_CTRL);

		phy_ctrl &= ~(3 << 9);
		phy_ctrl |= USBPHY_DATAPOL;
		__raw_ग_लिखोl(phy_ctrl, USB_PHY_CTRL);
	पूर्ण

	/* On dm355, the शेष-A state machine needs DRVVBUS control.
	 * If we won't be a host, there's no need to turn it on.
	 */
	अगर (cpu_is_davinci_dm355()) अणु
		u32	deepsleep = __raw_पढ़ोl(DM355_DEEPSLEEP);

		deepsleep &= ~DRVVBUS_FORCE;
		__raw_ग_लिखोl(deepsleep, DM355_DEEPSLEEP);
	पूर्ण

	/* reset the controller */
	musb_ग_लिखोl(tibase, DAVINCI_USB_CTRL_REG, 0x1);

	/* start the on-chip PHY and its PLL */
	phy_on();

	msleep(5);

	/* NOTE:  irqs are in mixed mode, not bypass to pure-musb */
	pr_debug("DaVinci OTG revision %08x phy %03x control %02x\n",
		revision, __raw_पढ़ोl(USB_PHY_CTRL),
		musb_पढ़ोb(tibase, DAVINCI_USB_CTRL_REG));

	musb->isr = davinci_musb_पूर्णांकerrupt;
	वापस 0;

fail:
	usb_put_phy(musb->xceiv);
unरेजिस्टर:
	usb_phy_generic_unरेजिस्टर();
	वापस ret;
पूर्ण

अटल पूर्णांक davinci_musb_निकास(काष्ठा musb *musb)
अणु
	पूर्णांक	maxdelay = 30;
	u8	devctl, warn = 0;

	del_समयr_sync(&musb->dev_समयr);

	/* क्रमce VBUS off */
	अगर (cpu_is_davinci_dm355()) अणु
		u32	deepsleep = __raw_पढ़ोl(DM355_DEEPSLEEP);

		deepsleep &= ~DRVVBUS_FORCE;
		deepsleep |= DRVVBUS_OVERRIDE;
		__raw_ग_लिखोl(deepsleep, DM355_DEEPSLEEP);
	पूर्ण

	davinci_musb_source_घातer(musb, 0 /*off*/, 1);

	/*
	 * delay, to aव्योम problems with module reload.
	 * अगर there's no peripheral connected, this can take a
	 * दीर्घ समय to fall, especially on EVM with huge C133.
	 */
	करो अणु
		devctl = musb_पढ़ोb(musb->mregs, MUSB_DEVCTL);
		अगर (!(devctl & MUSB_DEVCTL_VBUS))
			अवरोध;
		अगर ((devctl & MUSB_DEVCTL_VBUS) != warn) अणु
			warn = devctl & MUSB_DEVCTL_VBUS;
			dev_dbg(musb->controller, "VBUS %d\n",
				warn >> MUSB_DEVCTL_VBUS_SHIFT);
		पूर्ण
		msleep(1000);
		maxdelay--;
	पूर्ण जबतक (maxdelay > 0);

	/* in OTG mode, another host might be connected */
	अगर (devctl & MUSB_DEVCTL_VBUS)
		dev_dbg(musb->controller, "VBUS off timeout (devctl %02x)\n", devctl);

	phy_off();

	usb_put_phy(musb->xceiv);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा musb_platक्रमm_ops davinci_ops = अणु
	.quirks		= MUSB_DMA_CPPI,
	.init		= davinci_musb_init,
	.निकास		= davinci_musb_निकास,

#अगर_घोषित CONFIG_USB_TI_CPPI_DMA
	.dma_init	= cppi_dma_controller_create,
	.dma_निकास	= cppi_dma_controller_destroy,
#पूर्ण_अगर
	.enable		= davinci_musb_enable,
	.disable	= davinci_musb_disable,

	.set_mode	= davinci_musb_set_mode,

	.set_vbus	= davinci_musb_set_vbus,
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_info davinci_dev_info = अणु
	.name		= "musb-hdrc",
	.id		= PLATFORM_DEVID_AUTO,
	.dma_mask	= DMA_BIT_MASK(32),
पूर्ण;

अटल पूर्णांक davinci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource			musb_resources[3];
	काष्ठा musb_hdrc_platक्रमm_data	*pdata = dev_get_platdata(&pdev->dev);
	काष्ठा platक्रमm_device		*musb;
	काष्ठा davinci_glue		*glue;
	काष्ठा platक्रमm_device_info	pinfo;
	काष्ठा clk			*clk;

	पूर्णांक				ret = -ENOMEM;

	glue = devm_kzalloc(&pdev->dev, माप(*glue), GFP_KERNEL);
	अगर (!glue)
		जाओ err0;

	clk = devm_clk_get(&pdev->dev, "usb");
	अगर (IS_ERR(clk)) अणु
		dev_err(&pdev->dev, "failed to get clock\n");
		ret = PTR_ERR(clk);
		जाओ err0;
	पूर्ण

	ret = clk_enable(clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to enable clock\n");
		जाओ err0;
	पूर्ण

	glue->dev			= &pdev->dev;
	glue->clk			= clk;

	pdata->platक्रमm_ops		= &davinci_ops;

	glue->vbus = devm_gpiod_get_optional(&pdev->dev, शून्य, GPIOD_OUT_LOW);
	अगर (IS_ERR(glue->vbus)) अणु
		ret = PTR_ERR(glue->vbus);
		जाओ err0;
	पूर्ण अन्यथा अणु
		glue->vbus_state = -1;
		INIT_WORK(&glue->vbus_work, evm_deferred_drvvbus);
	पूर्ण

	usb_phy_generic_रेजिस्टर();
	platक्रमm_set_drvdata(pdev, glue);

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

	/*
	 * For DM6467 3 resources are passed. A placeholder क्रम the 3rd
	 * resource is always there, so it's safe to always copy it...
	 */
	musb_resources[2].name = pdev->resource[2].name;
	musb_resources[2].start = pdev->resource[2].start;
	musb_resources[2].end = pdev->resource[2].end;
	musb_resources[2].flags = pdev->resource[2].flags;

	pinfo = davinci_dev_info;
	pinfo.parent = &pdev->dev;
	pinfo.res = musb_resources;
	pinfo.num_res = ARRAY_SIZE(musb_resources);
	pinfo.data = pdata;
	pinfo.size_data = माप(*pdata);

	glue->musb = musb = platक्रमm_device_रेजिस्टर_full(&pinfo);
	अगर (IS_ERR(musb)) अणु
		ret = PTR_ERR(musb);
		dev_err(&pdev->dev, "failed to register musb device: %d\n", ret);
		जाओ err1;
	पूर्ण

	वापस 0;

err1:
	clk_disable(clk);

err0:
	वापस ret;
पूर्ण

अटल पूर्णांक davinci_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा davinci_glue		*glue = platक्रमm_get_drvdata(pdev);

	platक्रमm_device_unरेजिस्टर(glue->musb);
	usb_phy_generic_unरेजिस्टर();
	clk_disable(glue->clk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver davinci_driver = अणु
	.probe		= davinci_probe,
	.हटाओ		= davinci_हटाओ,
	.driver		= अणु
		.name	= "musb-davinci",
	पूर्ण,
पूर्ण;

MODULE_DESCRIPTION("DaVinci MUSB Glue Layer");
MODULE_AUTHOR("Felipe Balbi <balbi@ti.com>");
MODULE_LICENSE("GPL v2");
module_platक्रमm_driver(davinci_driver);
