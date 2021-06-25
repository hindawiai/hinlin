<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Texas Instruments DSPS platक्रमms "glue layer"
 *
 * Copyright (C) 2012, by Texas Instruments
 *
 * Based on the am35x "glue layer" code.
 *
 * This file is part of the Inventra Controller Driver क्रम Linux.
 *
 * musb_dsps.c will be a common file क्रम all the TI DSPS platक्रमms
 * such as dm64x, dm36x, dm35x, da8x, am35x and ti81x.
 * For now only ti81x is using this and in future davinci.c, am35x.c
 * da8xx.c would be merged to this file after testing.
 */

#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/module.h>
#समावेश <linux/usb/usb_phy_generic.h>
#समावेश <linux/platक्रमm_data/usb-omap.h>
#समावेश <linux/sizes.h>

#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/usb/of.h>

#समावेश <linux/debugfs.h>

#समावेश "musb_core.h"

अटल स्थिर काष्ठा of_device_id musb_dsps_of_match[];

/*
 * DSPS musb wrapper रेजिस्टर offset.
 * FIXME: This should be expanded to have all the wrapper रेजिस्टरs from TI DSPS
 * musb ips.
 */
काष्ठा dsps_musb_wrapper अणु
	u16	revision;
	u16	control;
	u16	status;
	u16	epपूर्णांकr_set;
	u16	epपूर्णांकr_clear;
	u16	epपूर्णांकr_status;
	u16	coreपूर्णांकr_set;
	u16	coreपूर्णांकr_clear;
	u16	coreपूर्णांकr_status;
	u16	phy_uपंचांगi;
	u16	mode;
	u16	tx_mode;
	u16	rx_mode;

	/* bit positions क्रम control */
	अचिन्हित	reset:5;

	/* bit positions क्रम पूर्णांकerrupt */
	अचिन्हित	usb_shअगरt:5;
	u32		usb_mask;
	u32		usb_biपंचांगap;
	अचिन्हित	drvvbus:5;

	अचिन्हित	txep_shअगरt:5;
	u32		txep_mask;
	u32		txep_biपंचांगap;

	अचिन्हित	rxep_shअगरt:5;
	u32		rxep_mask;
	u32		rxep_biपंचांगap;

	/* bit positions क्रम phy_uपंचांगi */
	अचिन्हित	otg_disable:5;

	/* bit positions क्रम mode */
	अचिन्हित	iddig:5;
	अचिन्हित	iddig_mux:5;
	/* miscellaneous stuff */
	अचिन्हित	poll_समयout;
पूर्ण;

/*
 * रेजिस्टर shaकरोw क्रम suspend
 */
काष्ठा dsps_context अणु
	u32 control;
	u32 epपूर्णांकr;
	u32 coreपूर्णांकr;
	u32 phy_uपंचांगi;
	u32 mode;
	u32 tx_mode;
	u32 rx_mode;
पूर्ण;

/*
 * DSPS glue काष्ठाure.
 */
काष्ठा dsps_glue अणु
	काष्ठा device *dev;
	काष्ठा platक्रमm_device *musb;	/* child musb pdev */
	स्थिर काष्ठा dsps_musb_wrapper *wrp; /* wrapper रेजिस्टर offsets */
	पूर्णांक vbus_irq;			/* optional vbus irq */
	अचिन्हित दीर्घ last_समयr;    /* last समयr data क्रम each instance */
	bool sw_babble_enabled;
	व्योम __iomem *usbss_base;

	काष्ठा dsps_context context;
	काष्ठा debugfs_regset32 regset;
	काष्ठा dentry *dbgfs_root;
पूर्ण;

अटल स्थिर काष्ठा debugfs_reg32 dsps_musb_regs[] = अणु
	अणु "revision",		0x00 पूर्ण,
	अणु "control",		0x14 पूर्ण,
	अणु "status",		0x18 पूर्ण,
	अणु "eoi",		0x24 पूर्ण,
	अणु "intr0_stat",		0x30 पूर्ण,
	अणु "intr1_stat",		0x34 पूर्ण,
	अणु "intr0_set",		0x38 पूर्ण,
	अणु "intr1_set",		0x3c पूर्ण,
	अणु "txmode",		0x70 पूर्ण,
	अणु "rxmode",		0x74 पूर्ण,
	अणु "autoreq",		0xd0 पूर्ण,
	अणु "srpfixtime",		0xd4 पूर्ण,
	अणु "tdown",		0xd8 पूर्ण,
	अणु "phy_utmi",		0xe0 पूर्ण,
	अणु "mode",		0xe8 पूर्ण,
पूर्ण;

अटल व्योम dsps_mod_समयr(काष्ठा dsps_glue *glue, पूर्णांक रुको_ms)
अणु
	काष्ठा musb *musb = platक्रमm_get_drvdata(glue->musb);
	पूर्णांक रुको;

	अगर (रुको_ms < 0)
		रुको = msecs_to_jअगरfies(glue->wrp->poll_समयout);
	अन्यथा
		रुको = msecs_to_jअगरfies(रुको_ms);

	mod_समयr(&musb->dev_समयr, jअगरfies + रुको);
पूर्ण

/*
 * If no vbus irq from the PMIC is configured, we need to poll VBUS status.
 */
अटल व्योम dsps_mod_समयr_optional(काष्ठा dsps_glue *glue)
अणु
	अगर (glue->vbus_irq)
		वापस;

	dsps_mod_समयr(glue, -1);
पूर्ण

/* USBSS  / USB AM335x */
#घोषणा USBSS_IRQ_STATUS	0x28
#घोषणा USBSS_IRQ_ENABLER	0x2c
#घोषणा USBSS_IRQ_CLEARR	0x30

#घोषणा USBSS_IRQ_PD_COMP	(1 << 2)

/*
 * dsps_musb_enable - enable पूर्णांकerrupts
 */
अटल व्योम dsps_musb_enable(काष्ठा musb *musb)
अणु
	काष्ठा device *dev = musb->controller;
	काष्ठा dsps_glue *glue = dev_get_drvdata(dev->parent);
	स्थिर काष्ठा dsps_musb_wrapper *wrp = glue->wrp;
	व्योम __iomem *reg_base = musb->ctrl_base;
	u32 epmask, coremask;

	/* Workaround: setup IRQs through both रेजिस्टर sets. */
	epmask = ((musb->epmask & wrp->txep_mask) << wrp->txep_shअगरt) |
	       ((musb->epmask & wrp->rxep_mask) << wrp->rxep_shअगरt);
	coremask = (wrp->usb_biपंचांगap & ~MUSB_INTR_SOF);

	musb_ग_लिखोl(reg_base, wrp->epपूर्णांकr_set, epmask);
	musb_ग_लिखोl(reg_base, wrp->coreपूर्णांकr_set, coremask);
	/*
	 * start polling क्रम runसमय PM active and idle,
	 * and क्रम ID change in dual-role idle mode.
	 */
	अगर (musb->xceiv->otg->state == OTG_STATE_B_IDLE)
		dsps_mod_समयr(glue, -1);
पूर्ण

/*
 * dsps_musb_disable - disable HDRC and flush पूर्णांकerrupts
 */
अटल व्योम dsps_musb_disable(काष्ठा musb *musb)
अणु
	काष्ठा device *dev = musb->controller;
	काष्ठा dsps_glue *glue = dev_get_drvdata(dev->parent);
	स्थिर काष्ठा dsps_musb_wrapper *wrp = glue->wrp;
	व्योम __iomem *reg_base = musb->ctrl_base;

	musb_ग_लिखोl(reg_base, wrp->coreपूर्णांकr_clear, wrp->usb_biपंचांगap);
	musb_ग_लिखोl(reg_base, wrp->epपूर्णांकr_clear,
			 wrp->txep_biपंचांगap | wrp->rxep_biपंचांगap);
	del_समयr_sync(&musb->dev_समयr);
पूर्ण

/* Caller must take musb->lock */
अटल पूर्णांक dsps_check_status(काष्ठा musb *musb, व्योम *unused)
अणु
	व्योम __iomem *mregs = musb->mregs;
	काष्ठा device *dev = musb->controller;
	काष्ठा dsps_glue *glue = dev_get_drvdata(dev->parent);
	स्थिर काष्ठा dsps_musb_wrapper *wrp = glue->wrp;
	u8 devctl;
	पूर्णांक skip_session = 0;

	अगर (glue->vbus_irq)
		del_समयr(&musb->dev_समयr);

	/*
	 * We poll because DSPS IP's won't expose several OTG-critical
	 * status change events (from the transceiver) otherwise.
	 */
	devctl = musb_पढ़ोb(mregs, MUSB_DEVCTL);
	dev_dbg(musb->controller, "Poll devctl %02x (%s)\n", devctl,
				usb_otg_state_string(musb->xceiv->otg->state));

	चयन (musb->xceiv->otg->state) अणु
	हाल OTG_STATE_A_WAIT_VRISE:
		अगर (musb->port_mode == MUSB_HOST) अणु
			musb->xceiv->otg->state = OTG_STATE_A_WAIT_BCON;
			dsps_mod_समयr_optional(glue);
			अवरोध;
		पूर्ण
		fallthrough;

	हाल OTG_STATE_A_WAIT_BCON:
		/* keep VBUS on क्रम host-only mode */
		अगर (musb->port_mode == MUSB_HOST) अणु
			dsps_mod_समयr_optional(glue);
			अवरोध;
		पूर्ण
		musb_ग_लिखोb(musb->mregs, MUSB_DEVCTL, 0);
		skip_session = 1;
		fallthrough;

	हाल OTG_STATE_A_IDLE:
	हाल OTG_STATE_B_IDLE:
		अगर (!glue->vbus_irq) अणु
			अगर (devctl & MUSB_DEVCTL_BDEVICE) अणु
				musb->xceiv->otg->state = OTG_STATE_B_IDLE;
				MUSB_DEV_MODE(musb);
			पूर्ण अन्यथा अणु
				musb->xceiv->otg->state = OTG_STATE_A_IDLE;
				MUSB_HST_MODE(musb);
			पूर्ण

			अगर (musb->port_mode == MUSB_PERIPHERAL)
				skip_session = 1;

			अगर (!(devctl & MUSB_DEVCTL_SESSION) && !skip_session)
				musb_ग_लिखोb(mregs, MUSB_DEVCTL,
					    MUSB_DEVCTL_SESSION);
		पूर्ण
		dsps_mod_समयr_optional(glue);
		अवरोध;
	हाल OTG_STATE_A_WAIT_VFALL:
		musb->xceiv->otg->state = OTG_STATE_A_WAIT_VRISE;
		musb_ग_लिखोl(musb->ctrl_base, wrp->coreपूर्णांकr_set,
			    MUSB_INTR_VBUSERROR << wrp->usb_shअगरt);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम otg_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा musb *musb = from_समयr(musb, t, dev_समयr);
	काष्ठा device *dev = musb->controller;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	err = pm_runसमय_get(dev);
	अगर ((err != -EINPROGRESS) && err < 0) अणु
		dev_err(dev, "Poll could not pm_runtime_get: %i\n", err);
		pm_runसमय_put_noidle(dev);

		वापस;
	पूर्ण

	spin_lock_irqsave(&musb->lock, flags);
	err = musb_queue_resume_work(musb, dsps_check_status, शून्य);
	अगर (err < 0)
		dev_err(dev, "%s resume work: %i\n", __func__, err);
	spin_unlock_irqrestore(&musb->lock, flags);
	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);
पूर्ण

अटल व्योम dsps_musb_clear_ep_rxपूर्णांकr(काष्ठा musb *musb, पूर्णांक epnum)
अणु
	u32 epपूर्णांकr;
	काष्ठा dsps_glue *glue = dev_get_drvdata(musb->controller->parent);
	स्थिर काष्ठा dsps_musb_wrapper *wrp = glue->wrp;

	/* musb->lock might alपढ़ोy been held */
	epपूर्णांकr = (1 << epnum) << wrp->rxep_shअगरt;
	musb_ग_लिखोl(musb->ctrl_base, wrp->epपूर्णांकr_status, epपूर्णांकr);
पूर्ण

अटल irqवापस_t dsps_पूर्णांकerrupt(पूर्णांक irq, व्योम *hci)
अणु
	काष्ठा musb  *musb = hci;
	व्योम __iomem *reg_base = musb->ctrl_base;
	काष्ठा device *dev = musb->controller;
	काष्ठा dsps_glue *glue = dev_get_drvdata(dev->parent);
	स्थिर काष्ठा dsps_musb_wrapper *wrp = glue->wrp;
	अचिन्हित दीर्घ flags;
	irqवापस_t ret = IRQ_NONE;
	u32 epपूर्णांकr, usbपूर्णांकr;

	spin_lock_irqsave(&musb->lock, flags);

	/* Get endpoपूर्णांक पूर्णांकerrupts */
	epपूर्णांकr = musb_पढ़ोl(reg_base, wrp->epपूर्णांकr_status);
	musb->पूर्णांक_rx = (epपूर्णांकr & wrp->rxep_biपंचांगap) >> wrp->rxep_shअगरt;
	musb->पूर्णांक_tx = (epपूर्णांकr & wrp->txep_biपंचांगap) >> wrp->txep_shअगरt;

	अगर (epपूर्णांकr)
		musb_ग_लिखोl(reg_base, wrp->epपूर्णांकr_status, epपूर्णांकr);

	/* Get usb core पूर्णांकerrupts */
	usbपूर्णांकr = musb_पढ़ोl(reg_base, wrp->coreपूर्णांकr_status);
	अगर (!usbपूर्णांकr && !epपूर्णांकr)
		जाओ out;

	musb->पूर्णांक_usb =	(usbपूर्णांकr & wrp->usb_biपंचांगap) >> wrp->usb_shअगरt;
	अगर (usbपूर्णांकr)
		musb_ग_लिखोl(reg_base, wrp->coreपूर्णांकr_status, usbपूर्णांकr);

	dev_dbg(musb->controller, "usbintr (%x) epintr(%x)\n",
			usbपूर्णांकr, epपूर्णांकr);

	अगर (usbपूर्णांकr & ((1 << wrp->drvvbus) << wrp->usb_shअगरt)) अणु
		पूर्णांक drvvbus = musb_पढ़ोl(reg_base, wrp->status);
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
			dsps_mod_समयr_optional(glue);
			WARNING("VBUS error workaround (delay coming)\n");
		पूर्ण अन्यथा अगर (drvvbus) अणु
			MUSB_HST_MODE(musb);
			musb->xceiv->otg->state = OTG_STATE_A_WAIT_VRISE;
			dsps_mod_समयr_optional(glue);
		पूर्ण अन्यथा अणु
			musb->is_active = 0;
			MUSB_DEV_MODE(musb);
			musb->xceiv->otg->state = OTG_STATE_B_IDLE;
		पूर्ण

		/* NOTE: this must complete घातer-on within 100 ms. */
		dev_dbg(musb->controller, "VBUS %s (%s)%s, devctl %02x\n",
				drvvbus ? "on" : "off",
				usb_otg_state_string(musb->xceiv->otg->state),
				err ? " ERROR" : "",
				devctl);
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (musb->पूर्णांक_tx || musb->पूर्णांक_rx || musb->पूर्णांक_usb)
		ret |= musb_पूर्णांकerrupt(musb);

	/* Poll क्रम ID change and connect */
	चयन (musb->xceiv->otg->state) अणु
	हाल OTG_STATE_B_IDLE:
	हाल OTG_STATE_A_WAIT_BCON:
		dsps_mod_समयr_optional(glue);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

out:
	spin_unlock_irqrestore(&musb->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक dsps_musb_dbg_init(काष्ठा musb *musb, काष्ठा dsps_glue *glue)
अणु
	काष्ठा dentry *root;
	अक्षर buf[128];

	प्र_लिखो(buf, "%s.dsps", dev_name(musb->controller));
	root = debugfs_create_dir(buf, usb_debug_root);
	glue->dbgfs_root = root;

	glue->regset.regs = dsps_musb_regs;
	glue->regset.nregs = ARRAY_SIZE(dsps_musb_regs);
	glue->regset.base = musb->ctrl_base;

	debugfs_create_regset32("regdump", S_IRUGO, root, &glue->regset);
	वापस 0;
पूर्ण

अटल पूर्णांक dsps_musb_init(काष्ठा musb *musb)
अणु
	काष्ठा device *dev = musb->controller;
	काष्ठा dsps_glue *glue = dev_get_drvdata(dev->parent);
	काष्ठा platक्रमm_device *parent = to_platक्रमm_device(dev->parent);
	स्थिर काष्ठा dsps_musb_wrapper *wrp = glue->wrp;
	व्योम __iomem *reg_base;
	काष्ठा resource *r;
	u32 rev, val;
	पूर्णांक ret;

	r = platक्रमm_get_resource_byname(parent, IORESOURCE_MEM, "control");
	reg_base = devm_ioremap_resource(dev, r);
	अगर (IS_ERR(reg_base))
		वापस PTR_ERR(reg_base);
	musb->ctrl_base = reg_base;

	/* NOP driver needs change अगर supporting dual instance */
	musb->xceiv = devm_usb_get_phy_by_phandle(dev->parent, "phys", 0);
	अगर (IS_ERR(musb->xceiv))
		वापस PTR_ERR(musb->xceiv);

	musb->phy = devm_phy_get(dev->parent, "usb2-phy");

	/* Returns zero अगर e.g. not घड़ीed */
	rev = musb_पढ़ोl(reg_base, wrp->revision);
	अगर (!rev)
		वापस -ENODEV;

	अगर (IS_ERR(musb->phy))  अणु
		musb->phy = शून्य;
	पूर्ण अन्यथा अणु
		ret = phy_init(musb->phy);
		अगर (ret < 0)
			वापस ret;
		ret = phy_घातer_on(musb->phy);
		अगर (ret) अणु
			phy_निकास(musb->phy);
			वापस ret;
		पूर्ण
	पूर्ण

	समयr_setup(&musb->dev_समयr, otg_समयr, 0);

	/* Reset the musb */
	musb_ग_लिखोl(reg_base, wrp->control, (1 << wrp->reset));

	musb->isr = dsps_पूर्णांकerrupt;

	/* reset the otgdisable bit, needed क्रम host mode to work */
	val = musb_पढ़ोl(reg_base, wrp->phy_uपंचांगi);
	val &= ~(1 << wrp->otg_disable);
	musb_ग_लिखोl(musb->ctrl_base, wrp->phy_uपंचांगi, val);

	/*
	 *  Check whether the dsps version has babble control enabled.
	 * In latest silicon revision the babble control logic is enabled.
	 * If MUSB_BABBLE_CTL वापसs 0x4 then we have the babble control
	 * logic enabled.
	 */
	val = musb_पढ़ोb(musb->mregs, MUSB_BABBLE_CTL);
	अगर (val & MUSB_BABBLE_RCV_DISABLE) अणु
		glue->sw_babble_enabled = true;
		val |= MUSB_BABBLE_SW_SESSION_CTRL;
		musb_ग_लिखोb(musb->mregs, MUSB_BABBLE_CTL, val);
	पूर्ण

	dsps_mod_समयr(glue, -1);

	वापस dsps_musb_dbg_init(musb, glue);
पूर्ण

अटल पूर्णांक dsps_musb_निकास(काष्ठा musb *musb)
अणु
	काष्ठा device *dev = musb->controller;
	काष्ठा dsps_glue *glue = dev_get_drvdata(dev->parent);

	del_समयr_sync(&musb->dev_समयr);
	phy_घातer_off(musb->phy);
	phy_निकास(musb->phy);
	debugfs_हटाओ_recursive(glue->dbgfs_root);

	वापस 0;
पूर्ण

अटल पूर्णांक dsps_musb_set_mode(काष्ठा musb *musb, u8 mode)
अणु
	काष्ठा device *dev = musb->controller;
	काष्ठा dsps_glue *glue = dev_get_drvdata(dev->parent);
	स्थिर काष्ठा dsps_musb_wrapper *wrp = glue->wrp;
	व्योम __iomem *ctrl_base = musb->ctrl_base;
	u32 reg;

	reg = musb_पढ़ोl(ctrl_base, wrp->mode);

	चयन (mode) अणु
	हाल MUSB_HOST:
		reg &= ~(1 << wrp->iddig);

		/*
		 * अगर we're setting mode to host-only or device-only, we're
		 * going to ignore whatever the PHY sends us and just क्रमce
		 * ID pin status by SW
		 */
		reg |= (1 << wrp->iddig_mux);

		musb_ग_लिखोl(ctrl_base, wrp->mode, reg);
		musb_ग_लिखोl(ctrl_base, wrp->phy_uपंचांगi, 0x02);
		अवरोध;
	हाल MUSB_PERIPHERAL:
		reg |= (1 << wrp->iddig);

		/*
		 * अगर we're setting mode to host-only or device-only, we're
		 * going to ignore whatever the PHY sends us and just क्रमce
		 * ID pin status by SW
		 */
		reg |= (1 << wrp->iddig_mux);

		musb_ग_लिखोl(ctrl_base, wrp->mode, reg);
		अवरोध;
	हाल MUSB_OTG:
		musb_ग_लिखोl(ctrl_base, wrp->phy_uपंचांगi, 0x02);
		अवरोध;
	शेष:
		dev_err(glue->dev, "unsupported mode %d\n", mode);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool dsps_sw_babble_control(काष्ठा musb *musb)
अणु
	u8 babble_ctl;
	bool session_restart =  false;

	babble_ctl = musb_पढ़ोb(musb->mregs, MUSB_BABBLE_CTL);
	dev_dbg(musb->controller, "babble: MUSB_BABBLE_CTL value %x\n",
		babble_ctl);
	/*
	 * check line monitor flag to check whether babble is
	 * due to noise
	 */
	dev_dbg(musb->controller, "STUCK_J is %s\n",
		babble_ctl & MUSB_BABBLE_STUCK_J ? "set" : "reset");

	अगर (babble_ctl & MUSB_BABBLE_STUCK_J) अणु
		पूर्णांक समयout = 10;

		/*
		 * babble is due to noise, then set transmit idle (d7 bit)
		 * to resume normal operation
		 */
		babble_ctl = musb_पढ़ोb(musb->mregs, MUSB_BABBLE_CTL);
		babble_ctl |= MUSB_BABBLE_FORCE_TXIDLE;
		musb_ग_लिखोb(musb->mregs, MUSB_BABBLE_CTL, babble_ctl);

		/* रुको till line monitor flag cleared */
		dev_dbg(musb->controller, "Set TXIDLE, wait J to clear\n");
		करो अणु
			babble_ctl = musb_पढ़ोb(musb->mregs, MUSB_BABBLE_CTL);
			udelay(1);
		पूर्ण जबतक ((babble_ctl & MUSB_BABBLE_STUCK_J) && समयout--);

		/* check whether stuck_at_j bit cleared */
		अगर (babble_ctl & MUSB_BABBLE_STUCK_J) अणु
			/*
			 * real babble condition has occurred
			 * restart the controller to start the
			 * session again
			 */
			dev_dbg(musb->controller, "J not cleared, misc (%x)\n",
				babble_ctl);
			session_restart = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		session_restart = true;
	पूर्ण

	वापस session_restart;
पूर्ण

अटल पूर्णांक dsps_musb_recover(काष्ठा musb *musb)
अणु
	काष्ठा device *dev = musb->controller;
	काष्ठा dsps_glue *glue = dev_get_drvdata(dev->parent);
	पूर्णांक session_restart = 0;

	अगर (glue->sw_babble_enabled)
		session_restart = dsps_sw_babble_control(musb);
	अन्यथा
		session_restart = 1;

	वापस session_restart ? 0 : -EPIPE;
पूर्ण

/* Similar to am35x, dm81xx support only 32-bit पढ़ो operation */
अटल व्योम dsps_पढ़ो_fअगरo32(काष्ठा musb_hw_ep *hw_ep, u16 len, u8 *dst)
अणु
	व्योम __iomem *fअगरo = hw_ep->fअगरo;

	अगर (len >= 4) अणु
		ioपढ़ो32_rep(fअगरo, dst, len >> 2);
		dst += len & ~0x03;
		len &= 0x03;
	पूर्ण

	/* Read any reमुख्यing 1 to 3 bytes */
	अगर (len > 0) अणु
		u32 val = musb_पढ़ोl(fअगरo, 0);
		स_नकल(dst, &val, len);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_USB_TI_CPPI41_DMA
अटल व्योम dsps_dma_controller_callback(काष्ठा dma_controller *c)
अणु
	काष्ठा musb *musb = c->musb;
	काष्ठा dsps_glue *glue = dev_get_drvdata(musb->controller->parent);
	व्योम __iomem *usbss_base = glue->usbss_base;
	u32 status;

	status = musb_पढ़ोl(usbss_base, USBSS_IRQ_STATUS);
	अगर (status & USBSS_IRQ_PD_COMP)
		musb_ग_लिखोl(usbss_base, USBSS_IRQ_STATUS, USBSS_IRQ_PD_COMP);
पूर्ण

अटल काष्ठा dma_controller *
dsps_dma_controller_create(काष्ठा musb *musb, व्योम __iomem *base)
अणु
	काष्ठा dma_controller *controller;
	काष्ठा dsps_glue *glue = dev_get_drvdata(musb->controller->parent);
	व्योम __iomem *usbss_base = glue->usbss_base;

	controller = cppi41_dma_controller_create(musb, base);
	अगर (IS_ERR_OR_शून्य(controller))
		वापस controller;

	musb_ग_लिखोl(usbss_base, USBSS_IRQ_ENABLER, USBSS_IRQ_PD_COMP);
	controller->dma_callback = dsps_dma_controller_callback;

	वापस controller;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल व्योम dsps_dma_controller_suspend(काष्ठा dsps_glue *glue)
अणु
	व्योम __iomem *usbss_base = glue->usbss_base;

	musb_ग_लिखोl(usbss_base, USBSS_IRQ_CLEARR, USBSS_IRQ_PD_COMP);
पूर्ण

अटल व्योम dsps_dma_controller_resume(काष्ठा dsps_glue *glue)
अणु
	व्योम __iomem *usbss_base = glue->usbss_base;

	musb_ग_लिखोl(usbss_base, USBSS_IRQ_ENABLER, USBSS_IRQ_PD_COMP);
पूर्ण
#पूर्ण_अगर
#अन्यथा /* CONFIG_USB_TI_CPPI41_DMA */
#अगर_घोषित CONFIG_PM_SLEEP
अटल व्योम dsps_dma_controller_suspend(काष्ठा dsps_glue *glue) अणुपूर्ण
अटल व्योम dsps_dma_controller_resume(काष्ठा dsps_glue *glue) अणुपूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_USB_TI_CPPI41_DMA */

अटल काष्ठा musb_platक्रमm_ops dsps_ops = अणु
	.quirks		= MUSB_DMA_CPPI41 | MUSB_INDEXED_EP,
	.init		= dsps_musb_init,
	.निकास		= dsps_musb_निकास,

#अगर_घोषित CONFIG_USB_TI_CPPI41_DMA
	.dma_init	= dsps_dma_controller_create,
	.dma_निकास	= cppi41_dma_controller_destroy,
#पूर्ण_अगर
	.enable		= dsps_musb_enable,
	.disable	= dsps_musb_disable,

	.set_mode	= dsps_musb_set_mode,
	.recover	= dsps_musb_recover,
	.clear_ep_rxपूर्णांकr = dsps_musb_clear_ep_rxपूर्णांकr,
पूर्ण;

अटल u64 musb_dmamask = DMA_BIT_MASK(32);

अटल पूर्णांक get_पूर्णांक_prop(काष्ठा device_node *dn, स्थिर अक्षर *s)
अणु
	पूर्णांक ret;
	u32 val;

	ret = of_property_पढ़ो_u32(dn, s, &val);
	अगर (ret)
		वापस 0;
	वापस val;
पूर्ण

अटल पूर्णांक dsps_create_musb_pdev(काष्ठा dsps_glue *glue,
		काष्ठा platक्रमm_device *parent)
अणु
	काष्ठा musb_hdrc_platक्रमm_data pdata;
	काष्ठा resource	resources[2];
	काष्ठा resource	*res;
	काष्ठा device *dev = &parent->dev;
	काष्ठा musb_hdrc_config	*config;
	काष्ठा platक्रमm_device *musb;
	काष्ठा device_node *dn = parent->dev.of_node;
	पूर्णांक ret, val;

	स_रखो(resources, 0, माप(resources));
	res = platक्रमm_get_resource_byname(parent, IORESOURCE_MEM, "mc");
	अगर (!res) अणु
		dev_err(dev, "failed to get memory.\n");
		वापस -EINVAL;
	पूर्ण
	resources[0] = *res;

	res = platक्रमm_get_resource_byname(parent, IORESOURCE_IRQ, "mc");
	अगर (!res) अणु
		dev_err(dev, "failed to get irq.\n");
		वापस -EINVAL;
	पूर्ण
	resources[1] = *res;

	/* allocate the child platक्रमm device */
	musb = platक्रमm_device_alloc("musb-hdrc",
			(resources[0].start & 0xFFF) == 0x400 ? 0 : 1);
	अगर (!musb) अणु
		dev_err(dev, "failed to allocate musb device\n");
		वापस -ENOMEM;
	पूर्ण

	musb->dev.parent		= dev;
	musb->dev.dma_mask		= &musb_dmamask;
	musb->dev.coherent_dma_mask	= musb_dmamask;
	device_set_of_node_from_dev(&musb->dev, &parent->dev);

	glue->musb = musb;

	ret = platक्रमm_device_add_resources(musb, resources,
			ARRAY_SIZE(resources));
	अगर (ret) अणु
		dev_err(dev, "failed to add resources\n");
		जाओ err;
	पूर्ण

	config = devm_kzalloc(&parent->dev, माप(*config), GFP_KERNEL);
	अगर (!config) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण
	pdata.config = config;
	pdata.platक्रमm_ops = &dsps_ops;

	config->num_eps = get_पूर्णांक_prop(dn, "mentor,num-eps");
	config->ram_bits = get_पूर्णांक_prop(dn, "mentor,ram-bits");
	config->host_port_deनिश्चित_reset_at_resume = 1;
	pdata.mode = musb_get_mode(dev);
	/* DT keeps this entry in mA, musb expects it as per USB spec */
	pdata.घातer = get_पूर्णांक_prop(dn, "mentor,power") / 2;

	ret = of_property_पढ़ो_u32(dn, "mentor,multipoint", &val);
	अगर (!ret && val)
		config->multipoपूर्णांक = true;

	config->maximum_speed = usb_get_maximum_speed(&parent->dev);
	चयन (config->maximum_speed) अणु
	हाल USB_SPEED_LOW:
	हाल USB_SPEED_FULL:
		अवरोध;
	हाल USB_SPEED_SUPER:
		dev_warn(dev, "ignore incorrect maximum_speed "
				"(super-speed) setting in dts");
		fallthrough;
	शेष:
		config->maximum_speed = USB_SPEED_HIGH;
	पूर्ण

	ret = platक्रमm_device_add_data(musb, &pdata, माप(pdata));
	अगर (ret) अणु
		dev_err(dev, "failed to add platform_data\n");
		जाओ err;
	पूर्ण

	ret = platक्रमm_device_add(musb);
	अगर (ret) अणु
		dev_err(dev, "failed to register musb device\n");
		जाओ err;
	पूर्ण
	वापस 0;

err:
	platक्रमm_device_put(musb);
	वापस ret;
पूर्ण

अटल irqवापस_t dsps_vbus_thपढ़ोed_irq(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा dsps_glue *glue = priv;
	काष्ठा musb *musb = platक्रमm_get_drvdata(glue->musb);

	अगर (!musb)
		वापस IRQ_NONE;

	dev_dbg(glue->dev, "VBUS interrupt\n");
	dsps_mod_समयr(glue, 0);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक dsps_setup_optional_vbus_irq(काष्ठा platक्रमm_device *pdev,
					काष्ठा dsps_glue *glue)
अणु
	पूर्णांक error;

	glue->vbus_irq = platक्रमm_get_irq_byname(pdev, "vbus");
	अगर (glue->vbus_irq == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;

	अगर (glue->vbus_irq <= 0) अणु
		glue->vbus_irq = 0;
		वापस 0;
	पूर्ण

	error = devm_request_thपढ़ोed_irq(glue->dev, glue->vbus_irq,
					  शून्य, dsps_vbus_thपढ़ोed_irq,
					  IRQF_ONESHOT,
					  "vbus", glue);
	अगर (error) अणु
		glue->vbus_irq = 0;
		वापस error;
	पूर्ण
	dev_dbg(glue->dev, "VBUS irq %i configured\n", glue->vbus_irq);

	वापस 0;
पूर्ण

अटल पूर्णांक dsps_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	स्थिर काष्ठा dsps_musb_wrapper *wrp;
	काष्ठा dsps_glue *glue;
	पूर्णांक ret;

	अगर (!म_भेद(pdev->name, "musb-hdrc"))
		वापस -ENODEV;

	match = of_match_node(musb_dsps_of_match, pdev->dev.of_node);
	अगर (!match) अणु
		dev_err(&pdev->dev, "fail to get matching of_match struct\n");
		वापस -EINVAL;
	पूर्ण
	wrp = match->data;

	अगर (of_device_is_compatible(pdev->dev.of_node, "ti,musb-dm816"))
		dsps_ops.पढ़ो_fअगरo = dsps_पढ़ो_fअगरo32;

	/* allocate glue */
	glue = devm_kzalloc(&pdev->dev, माप(*glue), GFP_KERNEL);
	अगर (!glue)
		वापस -ENOMEM;

	glue->dev = &pdev->dev;
	glue->wrp = wrp;
	glue->usbss_base = of_iomap(pdev->dev.parent->of_node, 0);
	अगर (!glue->usbss_base)
		वापस -ENXIO;

	अगर (usb_get_dr_mode(&pdev->dev) == USB_DR_MODE_PERIPHERAL) अणु
		ret = dsps_setup_optional_vbus_irq(pdev, glue);
		अगर (ret)
			जाओ err_iounmap;
	पूर्ण

	platक्रमm_set_drvdata(pdev, glue);
	pm_runसमय_enable(&pdev->dev);
	ret = dsps_create_musb_pdev(glue, pdev);
	अगर (ret)
		जाओ err;

	वापस 0;

err:
	pm_runसमय_disable(&pdev->dev);
err_iounmap:
	iounmap(glue->usbss_base);
	वापस ret;
पूर्ण

अटल पूर्णांक dsps_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dsps_glue *glue = platक्रमm_get_drvdata(pdev);

	platक्रमm_device_unरेजिस्टर(glue->musb);

	pm_runसमय_disable(&pdev->dev);
	iounmap(glue->usbss_base);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dsps_musb_wrapper am33xx_driver_data = अणु
	.revision		= 0x00,
	.control		= 0x14,
	.status			= 0x18,
	.epपूर्णांकr_set		= 0x38,
	.epपूर्णांकr_clear		= 0x40,
	.epपूर्णांकr_status		= 0x30,
	.coreपूर्णांकr_set		= 0x3c,
	.coreपूर्णांकr_clear		= 0x44,
	.coreपूर्णांकr_status	= 0x34,
	.phy_uपंचांगi		= 0xe0,
	.mode			= 0xe8,
	.tx_mode		= 0x70,
	.rx_mode		= 0x74,
	.reset			= 0,
	.otg_disable		= 21,
	.iddig			= 8,
	.iddig_mux		= 7,
	.usb_shअगरt		= 0,
	.usb_mask		= 0x1ff,
	.usb_biपंचांगap		= (0x1ff << 0),
	.drvvbus		= 8,
	.txep_shअगरt		= 0,
	.txep_mask		= 0xffff,
	.txep_biपंचांगap		= (0xffff << 0),
	.rxep_shअगरt		= 16,
	.rxep_mask		= 0xfffe,
	.rxep_biपंचांगap		= (0xfffe << 16),
	.poll_समयout		= 2000, /* ms */
पूर्ण;

अटल स्थिर काष्ठा of_device_id musb_dsps_of_match[] = अणु
	अणु .compatible = "ti,musb-am33xx",
		.data = &am33xx_driver_data, पूर्ण,
	अणु .compatible = "ti,musb-dm816",
		.data = &am33xx_driver_data, पूर्ण,
	अणु  पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, musb_dsps_of_match);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक dsps_suspend(काष्ठा device *dev)
अणु
	काष्ठा dsps_glue *glue = dev_get_drvdata(dev);
	स्थिर काष्ठा dsps_musb_wrapper *wrp = glue->wrp;
	काष्ठा musb *musb = platक्रमm_get_drvdata(glue->musb);
	व्योम __iomem *mbase;
	पूर्णांक ret;

	अगर (!musb)
		/* This can happen अगर the musb device is in -EPROBE_DEFER */
		वापस 0;

	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(dev);
		वापस ret;
	पूर्ण

	del_समयr_sync(&musb->dev_समयr);

	mbase = musb->ctrl_base;
	glue->context.control = musb_पढ़ोl(mbase, wrp->control);
	glue->context.epपूर्णांकr = musb_पढ़ोl(mbase, wrp->epपूर्णांकr_set);
	glue->context.coreपूर्णांकr = musb_पढ़ोl(mbase, wrp->coreपूर्णांकr_set);
	glue->context.phy_uपंचांगi = musb_पढ़ोl(mbase, wrp->phy_uपंचांगi);
	glue->context.mode = musb_पढ़ोl(mbase, wrp->mode);
	glue->context.tx_mode = musb_पढ़ोl(mbase, wrp->tx_mode);
	glue->context.rx_mode = musb_पढ़ोl(mbase, wrp->rx_mode);

	dsps_dma_controller_suspend(glue);

	वापस 0;
पूर्ण

अटल पूर्णांक dsps_resume(काष्ठा device *dev)
अणु
	काष्ठा dsps_glue *glue = dev_get_drvdata(dev);
	स्थिर काष्ठा dsps_musb_wrapper *wrp = glue->wrp;
	काष्ठा musb *musb = platक्रमm_get_drvdata(glue->musb);
	व्योम __iomem *mbase;

	अगर (!musb)
		वापस 0;

	dsps_dma_controller_resume(glue);

	mbase = musb->ctrl_base;
	musb_ग_लिखोl(mbase, wrp->control, glue->context.control);
	musb_ग_लिखोl(mbase, wrp->epपूर्णांकr_set, glue->context.epपूर्णांकr);
	musb_ग_लिखोl(mbase, wrp->coreपूर्णांकr_set, glue->context.coreपूर्णांकr);
	musb_ग_लिखोl(mbase, wrp->phy_uपंचांगi, glue->context.phy_uपंचांगi);
	musb_ग_लिखोl(mbase, wrp->mode, glue->context.mode);
	musb_ग_लिखोl(mbase, wrp->tx_mode, glue->context.tx_mode);
	musb_ग_लिखोl(mbase, wrp->rx_mode, glue->context.rx_mode);
	अगर (musb->xceiv->otg->state == OTG_STATE_B_IDLE &&
	    musb->port_mode == MUSB_OTG)
		dsps_mod_समयr(glue, -1);

	pm_runसमय_put(dev);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(dsps_pm_ops, dsps_suspend, dsps_resume);

अटल काष्ठा platक्रमm_driver dsps_usbss_driver = अणु
	.probe		= dsps_probe,
	.हटाओ         = dsps_हटाओ,
	.driver         = अणु
		.name   = "musb-dsps",
		.pm	= &dsps_pm_ops,
		.of_match_table	= musb_dsps_of_match,
	पूर्ण,
पूर्ण;

MODULE_DESCRIPTION("TI DSPS MUSB Glue Layer");
MODULE_AUTHOR("Ravi B <ravibabu@ti.com>");
MODULE_AUTHOR("Ajay Kumar Gupta <ajay.gupta@ti.com>");
MODULE_LICENSE("GPL v2");

module_platक्रमm_driver(dsps_usbss_driver);
