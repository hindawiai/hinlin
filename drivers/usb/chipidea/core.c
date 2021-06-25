<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * core.c - ChipIdea USB IP core family device controller
 *
 * Copyright (C) 2008 Chipidea - MIPS Technologies, Inc. All rights reserved.
 * Copyright (C) 2020 NXP
 *
 * Author: David Lopo
 *	   Peter Chen <peter.chen@nxp.com>
 *
 * Main Features:
 * - Four transfers are supported, usbtest is passed
 * - USB Certअगरication क्रम gadget: CH9 and Mass Storage are passed
 * - Low घातer mode
 * - USB wakeup
 */
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/extcon.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/idr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/usb/chipidea.h>
#समावेश <linux/usb/of.h>
#समावेश <linux/of.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/usb/ehci_def.h>

#समावेश "ci.h"
#समावेश "udc.h"
#समावेश "bits.h"
#समावेश "host.h"
#समावेश "otg.h"
#समावेश "otg_fsm.h"

/* Controller रेजिस्टर map */
अटल स्थिर u8 ci_regs_nolpm[] = अणु
	[CAP_CAPLENGTH]		= 0x00U,
	[CAP_HCCPARAMS]		= 0x08U,
	[CAP_DCCPARAMS]		= 0x24U,
	[CAP_TESTMODE]		= 0x38U,
	[OP_USBCMD]		= 0x00U,
	[OP_USBSTS]		= 0x04U,
	[OP_USBINTR]		= 0x08U,
	[OP_DEVICEADDR]		= 0x14U,
	[OP_ENDPTLISTADDR]	= 0x18U,
	[OP_TTCTRL]		= 0x1CU,
	[OP_BURSTSIZE]		= 0x20U,
	[OP_ULPI_VIEWPORT]	= 0x30U,
	[OP_PORTSC]		= 0x44U,
	[OP_DEVLC]		= 0x84U,
	[OP_OTGSC]		= 0x64U,
	[OP_USBMODE]		= 0x68U,
	[OP_ENDPTSETUPSTAT]	= 0x6CU,
	[OP_ENDPTPRIME]		= 0x70U,
	[OP_ENDPTFLUSH]		= 0x74U,
	[OP_ENDPTSTAT]		= 0x78U,
	[OP_ENDPTCOMPLETE]	= 0x7CU,
	[OP_ENDPTCTRL]		= 0x80U,
पूर्ण;

अटल स्थिर u8 ci_regs_lpm[] = अणु
	[CAP_CAPLENGTH]		= 0x00U,
	[CAP_HCCPARAMS]		= 0x08U,
	[CAP_DCCPARAMS]		= 0x24U,
	[CAP_TESTMODE]		= 0xFCU,
	[OP_USBCMD]		= 0x00U,
	[OP_USBSTS]		= 0x04U,
	[OP_USBINTR]		= 0x08U,
	[OP_DEVICEADDR]		= 0x14U,
	[OP_ENDPTLISTADDR]	= 0x18U,
	[OP_TTCTRL]		= 0x1CU,
	[OP_BURSTSIZE]		= 0x20U,
	[OP_ULPI_VIEWPORT]	= 0x30U,
	[OP_PORTSC]		= 0x44U,
	[OP_DEVLC]		= 0x84U,
	[OP_OTGSC]		= 0xC4U,
	[OP_USBMODE]		= 0xC8U,
	[OP_ENDPTSETUPSTAT]	= 0xD8U,
	[OP_ENDPTPRIME]		= 0xDCU,
	[OP_ENDPTFLUSH]		= 0xE0U,
	[OP_ENDPTSTAT]		= 0xE4U,
	[OP_ENDPTCOMPLETE]	= 0xE8U,
	[OP_ENDPTCTRL]		= 0xECU,
पूर्ण;

अटल व्योम hw_alloc_regmap(काष्ठा ci_hdrc *ci, bool is_lpm)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < OP_ENDPTCTRL; i++)
		ci->hw_bank.regmap[i] =
			(i <= CAP_LAST ? ci->hw_bank.cap : ci->hw_bank.op) +
			(is_lpm ? ci_regs_lpm[i] : ci_regs_nolpm[i]);

	क्रम (; i <= OP_LAST; i++)
		ci->hw_bank.regmap[i] = ci->hw_bank.op +
			4 * (i - OP_ENDPTCTRL) +
			(is_lpm
			 ? ci_regs_lpm[OP_ENDPTCTRL]
			 : ci_regs_nolpm[OP_ENDPTCTRL]);

पूर्ण

अटल क्रमागत ci_revision ci_get_revision(काष्ठा ci_hdrc *ci)
अणु
	पूर्णांक ver = hw_पढ़ो_id_reg(ci, ID_ID, VERSION) >> __ffs(VERSION);
	क्रमागत ci_revision rev = CI_REVISION_UNKNOWN;

	अगर (ver == 0x2) अणु
		rev = hw_पढ़ो_id_reg(ci, ID_ID, REVISION)
			>> __ffs(REVISION);
		rev += CI_REVISION_20;
	पूर्ण अन्यथा अगर (ver == 0x0) अणु
		rev = CI_REVISION_1X;
	पूर्ण

	वापस rev;
पूर्ण

/**
 * hw_पढ़ो_पूर्णांकr_enable: वापसs पूर्णांकerrupt enable रेजिस्टर
 *
 * @ci: the controller
 *
 * This function वापसs रेजिस्टर data
 */
u32 hw_पढ़ो_पूर्णांकr_enable(काष्ठा ci_hdrc *ci)
अणु
	वापस hw_पढ़ो(ci, OP_USBINTR, ~0);
पूर्ण

/**
 * hw_पढ़ो_पूर्णांकr_status: वापसs पूर्णांकerrupt status रेजिस्टर
 *
 * @ci: the controller
 *
 * This function वापसs रेजिस्टर data
 */
u32 hw_पढ़ो_पूर्णांकr_status(काष्ठा ci_hdrc *ci)
अणु
	वापस hw_पढ़ो(ci, OP_USBSTS, ~0);
पूर्ण

/**
 * hw_port_test_set: ग_लिखोs port test mode (execute without पूर्णांकerruption)
 * @ci: the controller
 * @mode: new value
 *
 * This function वापसs an error code
 */
पूर्णांक hw_port_test_set(काष्ठा ci_hdrc *ci, u8 mode)
अणु
	स्थिर u8 TEST_MODE_MAX = 7;

	अगर (mode > TEST_MODE_MAX)
		वापस -EINVAL;

	hw_ग_लिखो(ci, OP_PORTSC, PORTSC_PTC, mode << __ffs(PORTSC_PTC));
	वापस 0;
पूर्ण

/**
 * hw_port_test_get: पढ़ोs port test mode value
 *
 * @ci: the controller
 *
 * This function वापसs port test mode value
 */
u8 hw_port_test_get(काष्ठा ci_hdrc *ci)
अणु
	वापस hw_पढ़ो(ci, OP_PORTSC, PORTSC_PTC) >> __ffs(PORTSC_PTC);
पूर्ण

अटल व्योम hw_रुको_phy_stable(व्योम)
अणु
	/*
	 * The phy needs some delay to output the stable status from low
	 * घातer mode. And क्रम OTGSC, the status inमाला_दो are debounced
	 * using a 1 ms समय स्थिरant, so, delay 2ms क्रम controller to get
	 * the stable status, like vbus and id when the phy leaves low घातer.
	 */
	usleep_range(2000, 2500);
पूर्ण

/* The PHY enters/leaves low घातer mode */
अटल व्योम ci_hdrc_enter_lpm_common(काष्ठा ci_hdrc *ci, bool enable)
अणु
	क्रमागत ci_hw_regs reg = ci->hw_bank.lpm ? OP_DEVLC : OP_PORTSC;
	bool lpm = !!(hw_पढ़ो(ci, reg, PORTSC_PHCD(ci->hw_bank.lpm)));

	अगर (enable && !lpm)
		hw_ग_लिखो(ci, reg, PORTSC_PHCD(ci->hw_bank.lpm),
				PORTSC_PHCD(ci->hw_bank.lpm));
	अन्यथा अगर (!enable && lpm)
		hw_ग_लिखो(ci, reg, PORTSC_PHCD(ci->hw_bank.lpm),
				0);
पूर्ण

अटल व्योम ci_hdrc_enter_lpm(काष्ठा ci_hdrc *ci, bool enable)
अणु
	वापस ci->platdata->enter_lpm(ci, enable);
पूर्ण

अटल पूर्णांक hw_device_init(काष्ठा ci_hdrc *ci, व्योम __iomem *base)
अणु
	u32 reg;

	/* bank is a module variable */
	ci->hw_bank.असल = base;

	ci->hw_bank.cap = ci->hw_bank.असल;
	ci->hw_bank.cap += ci->platdata->capoffset;
	ci->hw_bank.op = ci->hw_bank.cap + (ioपढ़ो32(ci->hw_bank.cap) & 0xff);

	hw_alloc_regmap(ci, false);
	reg = hw_पढ़ो(ci, CAP_HCCPARAMS, HCCPARAMS_LEN) >>
		__ffs(HCCPARAMS_LEN);
	ci->hw_bank.lpm  = reg;
	अगर (reg)
		hw_alloc_regmap(ci, !!reg);
	ci->hw_bank.size = ci->hw_bank.op - ci->hw_bank.असल;
	ci->hw_bank.size += OP_LAST;
	ci->hw_bank.size /= माप(u32);

	reg = hw_पढ़ो(ci, CAP_DCCPARAMS, DCCPARAMS_DEN) >>
		__ffs(DCCPARAMS_DEN);
	ci->hw_ep_max = reg * 2;   /* cache hw ENDPT_MAX */

	अगर (ci->hw_ep_max > ENDPT_MAX)
		वापस -ENODEV;

	ci_hdrc_enter_lpm(ci, false);

	/* Disable all पूर्णांकerrupts bits */
	hw_ग_लिखो(ci, OP_USBINTR, 0xffffffff, 0);

	/* Clear all पूर्णांकerrupts status bits*/
	hw_ग_लिखो(ci, OP_USBSTS, 0xffffffff, 0xffffffff);

	ci->rev = ci_get_revision(ci);

	dev_dbg(ci->dev,
		"revision: %d, lpm: %d; cap: %px op: %px\n",
		ci->rev, ci->hw_bank.lpm, ci->hw_bank.cap, ci->hw_bank.op);

	/* setup lock mode ? */

	/* ENDPTSETUPSTAT is '0' by शेष */

	/* HCSPARAMS.bf.ppc SHOULD BE zero क्रम device */

	वापस 0;
पूर्ण

व्योम hw_phymode_configure(काष्ठा ci_hdrc *ci)
अणु
	u32 portsc, lpm, sts = 0;

	चयन (ci->platdata->phy_mode) अणु
	हाल USBPHY_INTERFACE_MODE_UTMI:
		portsc = PORTSC_PTS(PTS_UTMI);
		lpm = DEVLC_PTS(PTS_UTMI);
		अवरोध;
	हाल USBPHY_INTERFACE_MODE_UTMIW:
		portsc = PORTSC_PTS(PTS_UTMI) | PORTSC_PTW;
		lpm = DEVLC_PTS(PTS_UTMI) | DEVLC_PTW;
		अवरोध;
	हाल USBPHY_INTERFACE_MODE_ULPI:
		portsc = PORTSC_PTS(PTS_ULPI);
		lpm = DEVLC_PTS(PTS_ULPI);
		अवरोध;
	हाल USBPHY_INTERFACE_MODE_SERIAL:
		portsc = PORTSC_PTS(PTS_SERIAL);
		lpm = DEVLC_PTS(PTS_SERIAL);
		sts = 1;
		अवरोध;
	हाल USBPHY_INTERFACE_MODE_HSIC:
		portsc = PORTSC_PTS(PTS_HSIC);
		lpm = DEVLC_PTS(PTS_HSIC);
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	अगर (ci->hw_bank.lpm) अणु
		hw_ग_लिखो(ci, OP_DEVLC, DEVLC_PTS(7) | DEVLC_PTW, lpm);
		अगर (sts)
			hw_ग_लिखो(ci, OP_DEVLC, DEVLC_STS, DEVLC_STS);
	पूर्ण अन्यथा अणु
		hw_ग_लिखो(ci, OP_PORTSC, PORTSC_PTS(7) | PORTSC_PTW, portsc);
		अगर (sts)
			hw_ग_लिखो(ci, OP_PORTSC, PORTSC_STS, PORTSC_STS);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(hw_phymode_configure);

/**
 * _ci_usb_phy_init: initialize phy taking in account both phy and usb_phy
 * पूर्णांकerfaces
 * @ci: the controller
 *
 * This function वापसs an error code अगर the phy failed to init
 */
अटल पूर्णांक _ci_usb_phy_init(काष्ठा ci_hdrc *ci)
अणु
	पूर्णांक ret;

	अगर (ci->phy) अणु
		ret = phy_init(ci->phy);
		अगर (ret)
			वापस ret;

		ret = phy_घातer_on(ci->phy);
		अगर (ret) अणु
			phy_निकास(ci->phy);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = usb_phy_init(ci->usb_phy);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * _ci_usb_phy_निकास: deinitialize phy taking in account both phy and usb_phy
 * पूर्णांकerfaces
 * @ci: the controller
 */
अटल व्योम ci_usb_phy_निकास(काष्ठा ci_hdrc *ci)
अणु
	अगर (ci->platdata->flags & CI_HDRC_OVERRIDE_PHY_CONTROL)
		वापस;

	अगर (ci->phy) अणु
		phy_घातer_off(ci->phy);
		phy_निकास(ci->phy);
	पूर्ण अन्यथा अणु
		usb_phy_shutकरोwn(ci->usb_phy);
	पूर्ण
पूर्ण

/**
 * ci_usb_phy_init: initialize phy according to dअगरferent phy type
 * @ci: the controller
 *
 * This function वापसs an error code अगर usb_phy_init has failed
 */
अटल पूर्णांक ci_usb_phy_init(काष्ठा ci_hdrc *ci)
अणु
	पूर्णांक ret;

	अगर (ci->platdata->flags & CI_HDRC_OVERRIDE_PHY_CONTROL)
		वापस 0;

	चयन (ci->platdata->phy_mode) अणु
	हाल USBPHY_INTERFACE_MODE_UTMI:
	हाल USBPHY_INTERFACE_MODE_UTMIW:
	हाल USBPHY_INTERFACE_MODE_HSIC:
		ret = _ci_usb_phy_init(ci);
		अगर (!ret)
			hw_रुको_phy_stable();
		अन्यथा
			वापस ret;
		hw_phymode_configure(ci);
		अवरोध;
	हाल USBPHY_INTERFACE_MODE_ULPI:
	हाल USBPHY_INTERFACE_MODE_SERIAL:
		hw_phymode_configure(ci);
		ret = _ci_usb_phy_init(ci);
		अगर (ret)
			वापस ret;
		अवरोध;
	शेष:
		ret = _ci_usb_phy_init(ci);
		अगर (!ret)
			hw_रुको_phy_stable();
	पूर्ण

	वापस ret;
पूर्ण


/**
 * ci_platक्रमm_configure: करो controller configure
 * @ci: the controller
 *
 */
व्योम ci_platक्रमm_configure(काष्ठा ci_hdrc *ci)
अणु
	bool is_device_mode, is_host_mode;

	is_device_mode = hw_पढ़ो(ci, OP_USBMODE, USBMODE_CM) == USBMODE_CM_DC;
	is_host_mode = hw_पढ़ो(ci, OP_USBMODE, USBMODE_CM) == USBMODE_CM_HC;

	अगर (is_device_mode) अणु
		phy_set_mode(ci->phy, PHY_MODE_USB_DEVICE);

		अगर (ci->platdata->flags & CI_HDRC_DISABLE_DEVICE_STREAMING)
			hw_ग_लिखो(ci, OP_USBMODE, USBMODE_CI_SDIS,
				 USBMODE_CI_SDIS);
	पूर्ण

	अगर (is_host_mode) अणु
		phy_set_mode(ci->phy, PHY_MODE_USB_HOST);

		अगर (ci->platdata->flags & CI_HDRC_DISABLE_HOST_STREAMING)
			hw_ग_लिखो(ci, OP_USBMODE, USBMODE_CI_SDIS,
				 USBMODE_CI_SDIS);
	पूर्ण

	अगर (ci->platdata->flags & CI_HDRC_FORCE_FULLSPEED) अणु
		अगर (ci->hw_bank.lpm)
			hw_ग_लिखो(ci, OP_DEVLC, DEVLC_PFSC, DEVLC_PFSC);
		अन्यथा
			hw_ग_लिखो(ci, OP_PORTSC, PORTSC_PFSC, PORTSC_PFSC);
	पूर्ण

	अगर (ci->platdata->flags & CI_HDRC_SET_NON_ZERO_TTHA)
		hw_ग_लिखो(ci, OP_TTCTRL, TTCTRL_TTHA_MASK, TTCTRL_TTHA);

	hw_ग_लिखो(ci, OP_USBCMD, 0xff0000, ci->platdata->itc_setting << 16);

	अगर (ci->platdata->flags & CI_HDRC_OVERRIDE_AHB_BURST)
		hw_ग_लिखो_id_reg(ci, ID_SBUSCFG, AHBBRST_MASK,
			ci->platdata->ahb_burst_config);

	/* override burst size, take effect only when ahb_burst_config is 0 */
	अगर (!hw_पढ़ो_id_reg(ci, ID_SBUSCFG, AHBBRST_MASK)) अणु
		अगर (ci->platdata->flags & CI_HDRC_OVERRIDE_TX_BURST)
			hw_ग_लिखो(ci, OP_BURSTSIZE, TX_BURST_MASK,
			ci->platdata->tx_burst_size << __ffs(TX_BURST_MASK));

		अगर (ci->platdata->flags & CI_HDRC_OVERRIDE_RX_BURST)
			hw_ग_लिखो(ci, OP_BURSTSIZE, RX_BURST_MASK,
				ci->platdata->rx_burst_size);
	पूर्ण
पूर्ण

/**
 * hw_controller_reset: करो controller reset
 * @ci: the controller
  *
 * This function वापसs an error code
 */
अटल पूर्णांक hw_controller_reset(काष्ठा ci_hdrc *ci)
अणु
	पूर्णांक count = 0;

	hw_ग_लिखो(ci, OP_USBCMD, USBCMD_RST, USBCMD_RST);
	जबतक (hw_पढ़ो(ci, OP_USBCMD, USBCMD_RST)) अणु
		udelay(10);
		अगर (count++ > 1000)
			वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * hw_device_reset: resets chip (execute without पूर्णांकerruption)
 * @ci: the controller
 *
 * This function वापसs an error code
 */
पूर्णांक hw_device_reset(काष्ठा ci_hdrc *ci)
अणु
	पूर्णांक ret;

	/* should flush & stop beक्रमe reset */
	hw_ग_लिखो(ci, OP_ENDPTFLUSH, ~0, ~0);
	hw_ग_लिखो(ci, OP_USBCMD, USBCMD_RS, 0);

	ret = hw_controller_reset(ci);
	अगर (ret) अणु
		dev_err(ci->dev, "error resetting controller, ret=%d\n", ret);
		वापस ret;
	पूर्ण

	अगर (ci->platdata->notअगरy_event) अणु
		ret = ci->platdata->notअगरy_event(ci,
			CI_HDRC_CONTROLLER_RESET_EVENT);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* USBMODE should be configured step by step */
	hw_ग_लिखो(ci, OP_USBMODE, USBMODE_CM, USBMODE_CM_IDLE);
	hw_ग_लिखो(ci, OP_USBMODE, USBMODE_CM, USBMODE_CM_DC);
	/* HW >= 2.3 */
	hw_ग_लिखो(ci, OP_USBMODE, USBMODE_SLOM, USBMODE_SLOM);

	अगर (hw_पढ़ो(ci, OP_USBMODE, USBMODE_CM) != USBMODE_CM_DC) अणु
		dev_err(ci->dev, "cannot enter in %s device mode\n",
			ci_role(ci)->name);
		dev_err(ci->dev, "lpm = %i\n", ci->hw_bank.lpm);
		वापस -ENODEV;
	पूर्ण

	ci_platक्रमm_configure(ci);

	वापस 0;
पूर्ण

अटल irqवापस_t ci_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ci_hdrc *ci = data;
	irqवापस_t ret = IRQ_NONE;
	u32 otgsc = 0;

	अगर (ci->in_lpm) अणु
		disable_irq_nosync(irq);
		ci->wakeup_पूर्णांक = true;
		pm_runसमय_get(ci->dev);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (ci->is_otg) अणु
		otgsc = hw_पढ़ो_otgsc(ci, ~0);
		अगर (ci_otg_is_fsm_mode(ci)) अणु
			ret = ci_otg_fsm_irq(ci);
			अगर (ret == IRQ_HANDLED)
				वापस ret;
		पूर्ण
	पूर्ण

	/*
	 * Handle id change पूर्णांकerrupt, it indicates device/host function
	 * चयन.
	 */
	अगर (ci->is_otg && (otgsc & OTGSC_IDIE) && (otgsc & OTGSC_IDIS)) अणु
		ci->id_event = true;
		/* Clear ID change irq status */
		hw_ग_लिखो_otgsc(ci, OTGSC_IDIS, OTGSC_IDIS);
		ci_otg_queue_work(ci);
		वापस IRQ_HANDLED;
	पूर्ण

	/*
	 * Handle vbus change पूर्णांकerrupt, it indicates device connection
	 * and disconnection events.
	 */
	अगर (ci->is_otg && (otgsc & OTGSC_BSVIE) && (otgsc & OTGSC_BSVIS)) अणु
		ci->b_sess_valid_event = true;
		/* Clear BSV irq */
		hw_ग_लिखो_otgsc(ci, OTGSC_BSVIS, OTGSC_BSVIS);
		ci_otg_queue_work(ci);
		वापस IRQ_HANDLED;
	पूर्ण

	/* Handle device/host पूर्णांकerrupt */
	अगर (ci->role != CI_ROLE_END)
		ret = ci_role(ci)->irq(ci);

	वापस ret;
पूर्ण

अटल पूर्णांक ci_cable_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event,
			     व्योम *ptr)
अणु
	काष्ठा ci_hdrc_cable *cbl = container_of(nb, काष्ठा ci_hdrc_cable, nb);
	काष्ठा ci_hdrc *ci = cbl->ci;

	cbl->connected = event;
	cbl->changed = true;

	ci_irq(ci->irq, ci);
	वापस NOTIFY_DONE;
पूर्ण

अटल क्रमागत usb_role ci_usb_role_चयन_get(काष्ठा usb_role_चयन *sw)
अणु
	काष्ठा ci_hdrc *ci = usb_role_चयन_get_drvdata(sw);
	क्रमागत usb_role role;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ci->lock, flags);
	role = ci_role_to_usb_role(ci);
	spin_unlock_irqrestore(&ci->lock, flags);

	वापस role;
पूर्ण

अटल पूर्णांक ci_usb_role_चयन_set(काष्ठा usb_role_चयन *sw,
				  क्रमागत usb_role role)
अणु
	काष्ठा ci_hdrc *ci = usb_role_चयन_get_drvdata(sw);
	काष्ठा ci_hdrc_cable *cable = शून्य;
	क्रमागत usb_role current_role = ci_role_to_usb_role(ci);
	क्रमागत ci_role ci_role = usb_role_to_ci_role(role);
	अचिन्हित दीर्घ flags;

	अगर ((ci_role != CI_ROLE_END && !ci->roles[ci_role]) ||
	    (current_role == role))
		वापस 0;

	pm_runसमय_get_sync(ci->dev);
	/* Stop current role */
	spin_lock_irqsave(&ci->lock, flags);
	अगर (current_role == USB_ROLE_DEVICE)
		cable = &ci->platdata->vbus_extcon;
	अन्यथा अगर (current_role == USB_ROLE_HOST)
		cable = &ci->platdata->id_extcon;

	अगर (cable) अणु
		cable->changed = true;
		cable->connected = false;
		ci_irq(ci->irq, ci);
		spin_unlock_irqrestore(&ci->lock, flags);
		अगर (ci->wq && role != USB_ROLE_NONE)
			flush_workqueue(ci->wq);
		spin_lock_irqsave(&ci->lock, flags);
	पूर्ण

	cable = शून्य;

	/* Start target role */
	अगर (role == USB_ROLE_DEVICE)
		cable = &ci->platdata->vbus_extcon;
	अन्यथा अगर (role == USB_ROLE_HOST)
		cable = &ci->platdata->id_extcon;

	अगर (cable) अणु
		cable->changed = true;
		cable->connected = true;
		ci_irq(ci->irq, ci);
	पूर्ण
	spin_unlock_irqrestore(&ci->lock, flags);
	pm_runसमय_put_sync(ci->dev);

	वापस 0;
पूर्ण

अटल काष्ठा usb_role_चयन_desc ci_role_चयन = अणु
	.set = ci_usb_role_चयन_set,
	.get = ci_usb_role_चयन_get,
	.allow_userspace_control = true,
पूर्ण;

अटल पूर्णांक ci_get_platdata(काष्ठा device *dev,
		काष्ठा ci_hdrc_platक्रमm_data *platdata)
अणु
	काष्ठा extcon_dev *ext_vbus, *ext_id;
	काष्ठा ci_hdrc_cable *cable;
	पूर्णांक ret;

	अगर (!platdata->phy_mode)
		platdata->phy_mode = of_usb_get_phy_mode(dev->of_node);

	अगर (!platdata->dr_mode)
		platdata->dr_mode = usb_get_dr_mode(dev);

	अगर (platdata->dr_mode == USB_DR_MODE_UNKNOWN)
		platdata->dr_mode = USB_DR_MODE_OTG;

	अगर (platdata->dr_mode != USB_DR_MODE_PERIPHERAL) अणु
		/* Get the vbus regulator */
		platdata->reg_vbus = devm_regulator_get_optional(dev, "vbus");
		अगर (PTR_ERR(platdata->reg_vbus) == -EPROBE_DEFER) अणु
			वापस -EPROBE_DEFER;
		पूर्ण अन्यथा अगर (PTR_ERR(platdata->reg_vbus) == -ENODEV) अणु
			/* no vbus regulator is needed */
			platdata->reg_vbus = शून्य;
		पूर्ण अन्यथा अगर (IS_ERR(platdata->reg_vbus)) अणु
			dev_err(dev, "Getting regulator error: %ld\n",
				PTR_ERR(platdata->reg_vbus));
			वापस PTR_ERR(platdata->reg_vbus);
		पूर्ण
		/* Get TPL support */
		अगर (!platdata->tpl_support)
			platdata->tpl_support =
				of_usb_host_tpl_support(dev->of_node);
	पूर्ण

	अगर (platdata->dr_mode == USB_DR_MODE_OTG) अणु
		/* We can support HNP and SRP of OTG 2.0 */
		platdata->ci_otg_caps.otg_rev = 0x0200;
		platdata->ci_otg_caps.hnp_support = true;
		platdata->ci_otg_caps.srp_support = true;

		/* Update otg capabilities by DT properties */
		ret = of_usb_update_otg_caps(dev->of_node,
					&platdata->ci_otg_caps);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (usb_get_maximum_speed(dev) == USB_SPEED_FULL)
		platdata->flags |= CI_HDRC_FORCE_FULLSPEED;

	of_property_पढ़ो_u32(dev->of_node, "phy-clkgate-delay-us",
				     &platdata->phy_clkgate_delay_us);

	platdata->itc_setting = 1;

	of_property_पढ़ो_u32(dev->of_node, "itc-setting",
					&platdata->itc_setting);

	ret = of_property_पढ़ो_u32(dev->of_node, "ahb-burst-config",
				&platdata->ahb_burst_config);
	अगर (!ret) अणु
		platdata->flags |= CI_HDRC_OVERRIDE_AHB_BURST;
	पूर्ण अन्यथा अगर (ret != -EINVAL) अणु
		dev_err(dev, "failed to get ahb-burst-config\n");
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32(dev->of_node, "tx-burst-size-dword",
				&platdata->tx_burst_size);
	अगर (!ret) अणु
		platdata->flags |= CI_HDRC_OVERRIDE_TX_BURST;
	पूर्ण अन्यथा अगर (ret != -EINVAL) अणु
		dev_err(dev, "failed to get tx-burst-size-dword\n");
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32(dev->of_node, "rx-burst-size-dword",
				&platdata->rx_burst_size);
	अगर (!ret) अणु
		platdata->flags |= CI_HDRC_OVERRIDE_RX_BURST;
	पूर्ण अन्यथा अगर (ret != -EINVAL) अणु
		dev_err(dev, "failed to get rx-burst-size-dword\n");
		वापस ret;
	पूर्ण

	अगर (of_find_property(dev->of_node, "non-zero-ttctrl-ttha", शून्य))
		platdata->flags |= CI_HDRC_SET_NON_ZERO_TTHA;

	ext_id = ERR_PTR(-ENODEV);
	ext_vbus = ERR_PTR(-ENODEV);
	अगर (of_property_पढ़ो_bool(dev->of_node, "extcon")) अणु
		/* Each one of them is not mandatory */
		ext_vbus = extcon_get_edev_by_phandle(dev, 0);
		अगर (IS_ERR(ext_vbus) && PTR_ERR(ext_vbus) != -ENODEV)
			वापस PTR_ERR(ext_vbus);

		ext_id = extcon_get_edev_by_phandle(dev, 1);
		अगर (IS_ERR(ext_id) && PTR_ERR(ext_id) != -ENODEV)
			वापस PTR_ERR(ext_id);
	पूर्ण

	cable = &platdata->vbus_extcon;
	cable->nb.notअगरier_call = ci_cable_notअगरier;
	cable->edev = ext_vbus;

	अगर (!IS_ERR(ext_vbus)) अणु
		ret = extcon_get_state(cable->edev, EXTCON_USB);
		अगर (ret)
			cable->connected = true;
		अन्यथा
			cable->connected = false;
	पूर्ण

	cable = &platdata->id_extcon;
	cable->nb.notअगरier_call = ci_cable_notअगरier;
	cable->edev = ext_id;

	अगर (!IS_ERR(ext_id)) अणु
		ret = extcon_get_state(cable->edev, EXTCON_USB_HOST);
		अगर (ret)
			cable->connected = true;
		अन्यथा
			cable->connected = false;
	पूर्ण

	अगर (device_property_पढ़ो_bool(dev, "usb-role-switch"))
		ci_role_चयन.fwnode = dev->fwnode;

	platdata->pctl = devm_pinctrl_get(dev);
	अगर (!IS_ERR(platdata->pctl)) अणु
		काष्ठा pinctrl_state *p;

		p = pinctrl_lookup_state(platdata->pctl, "default");
		अगर (!IS_ERR(p))
			platdata->pins_शेष = p;

		p = pinctrl_lookup_state(platdata->pctl, "host");
		अगर (!IS_ERR(p))
			platdata->pins_host = p;

		p = pinctrl_lookup_state(platdata->pctl, "device");
		अगर (!IS_ERR(p))
			platdata->pins_device = p;
	पूर्ण

	अगर (!platdata->enter_lpm)
		platdata->enter_lpm = ci_hdrc_enter_lpm_common;

	वापस 0;
पूर्ण

अटल पूर्णांक ci_extcon_रेजिस्टर(काष्ठा ci_hdrc *ci)
अणु
	काष्ठा ci_hdrc_cable *id, *vbus;
	पूर्णांक ret;

	id = &ci->platdata->id_extcon;
	id->ci = ci;
	अगर (!IS_ERR_OR_शून्य(id->edev)) अणु
		ret = devm_extcon_रेजिस्टर_notअगरier(ci->dev, id->edev,
						EXTCON_USB_HOST, &id->nb);
		अगर (ret < 0) अणु
			dev_err(ci->dev, "register ID failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	vbus = &ci->platdata->vbus_extcon;
	vbus->ci = ci;
	अगर (!IS_ERR_OR_शून्य(vbus->edev)) अणु
		ret = devm_extcon_रेजिस्टर_notअगरier(ci->dev, vbus->edev,
						EXTCON_USB, &vbus->nb);
		अगर (ret < 0) अणु
			dev_err(ci->dev, "register VBUS failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल DEFINE_IDA(ci_ida);

काष्ठा platक्रमm_device *ci_hdrc_add_device(काष्ठा device *dev,
			काष्ठा resource *res, पूर्णांक nres,
			काष्ठा ci_hdrc_platक्रमm_data *platdata)
अणु
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक id, ret;

	ret = ci_get_platdata(dev, platdata);
	अगर (ret)
		वापस ERR_PTR(ret);

	id = ida_simple_get(&ci_ida, 0, 0, GFP_KERNEL);
	अगर (id < 0)
		वापस ERR_PTR(id);

	pdev = platक्रमm_device_alloc("ci_hdrc", id);
	अगर (!pdev) अणु
		ret = -ENOMEM;
		जाओ put_id;
	पूर्ण

	pdev->dev.parent = dev;

	ret = platक्रमm_device_add_resources(pdev, res, nres);
	अगर (ret)
		जाओ err;

	ret = platक्रमm_device_add_data(pdev, platdata, माप(*platdata));
	अगर (ret)
		जाओ err;

	ret = platक्रमm_device_add(pdev);
	अगर (ret)
		जाओ err;

	वापस pdev;

err:
	platक्रमm_device_put(pdev);
put_id:
	ida_simple_हटाओ(&ci_ida, id);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(ci_hdrc_add_device);

व्योम ci_hdrc_हटाओ_device(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक id = pdev->id;
	platक्रमm_device_unरेजिस्टर(pdev);
	ida_simple_हटाओ(&ci_ida, id);
पूर्ण
EXPORT_SYMBOL_GPL(ci_hdrc_हटाओ_device);

/**
 * ci_hdrc_query_available_role: get runसमय available operation mode
 *
 * The glue layer can get current operation mode (host/peripheral/otg)
 * This function should be called after ci core device has created.
 *
 * @pdev: the platक्रमm device of ci core.
 *
 * Return runसमय usb_dr_mode.
 */
क्रमागत usb_dr_mode ci_hdrc_query_available_role(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ci_hdrc *ci = platक्रमm_get_drvdata(pdev);

	अगर (!ci)
		वापस USB_DR_MODE_UNKNOWN;
	अगर (ci->roles[CI_ROLE_HOST] && ci->roles[CI_ROLE_GADGET])
		वापस USB_DR_MODE_OTG;
	अन्यथा अगर (ci->roles[CI_ROLE_HOST])
		वापस USB_DR_MODE_HOST;
	अन्यथा अगर (ci->roles[CI_ROLE_GADGET])
		वापस USB_DR_MODE_PERIPHERAL;
	अन्यथा
		वापस USB_DR_MODE_UNKNOWN;
पूर्ण
EXPORT_SYMBOL_GPL(ci_hdrc_query_available_role);

अटल अंतरभूत व्योम ci_role_destroy(काष्ठा ci_hdrc *ci)
अणु
	ci_hdrc_gadget_destroy(ci);
	ci_hdrc_host_destroy(ci);
	अगर (ci->is_otg && ci->roles[CI_ROLE_GADGET])
		ci_hdrc_otg_destroy(ci);
पूर्ण

अटल व्योम ci_get_otg_capable(काष्ठा ci_hdrc *ci)
अणु
	अगर (ci->platdata->flags & CI_HDRC_DUAL_ROLE_NOT_OTG)
		ci->is_otg = false;
	अन्यथा
		ci->is_otg = (hw_पढ़ो(ci, CAP_DCCPARAMS,
				DCCPARAMS_DC | DCCPARAMS_HC)
					== (DCCPARAMS_DC | DCCPARAMS_HC));
	अगर (ci->is_otg) अणु
		dev_dbg(ci->dev, "It is OTG capable controller\n");
		/* Disable and clear all OTG irq */
		hw_ग_लिखो_otgsc(ci, OTGSC_INT_EN_BITS | OTGSC_INT_STATUS_BITS,
							OTGSC_INT_STATUS_BITS);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार role_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	काष्ठा ci_hdrc *ci = dev_get_drvdata(dev);

	अगर (ci->role != CI_ROLE_END)
		वापस प्र_लिखो(buf, "%s\n", ci_role(ci)->name);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार role_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार n)
अणु
	काष्ठा ci_hdrc *ci = dev_get_drvdata(dev);
	क्रमागत ci_role role;
	पूर्णांक ret;

	अगर (!(ci->roles[CI_ROLE_HOST] && ci->roles[CI_ROLE_GADGET])) अणु
		dev_warn(dev, "Current configuration is not dual-role, quit\n");
		वापस -EPERM;
	पूर्ण

	क्रम (role = CI_ROLE_HOST; role < CI_ROLE_END; role++)
		अगर (!म_भेदन(buf, ci->roles[role]->name,
			     म_माप(ci->roles[role]->name)))
			अवरोध;

	अगर (role == CI_ROLE_END || role == ci->role)
		वापस -EINVAL;

	pm_runसमय_get_sync(dev);
	disable_irq(ci->irq);
	ci_role_stop(ci);
	ret = ci_role_start(ci, role);
	अगर (!ret && ci->role == CI_ROLE_GADGET)
		ci_handle_vbus_change(ci);
	enable_irq(ci->irq);
	pm_runसमय_put_sync(dev);

	वापस (ret == 0) ? n : ret;
पूर्ण
अटल DEVICE_ATTR_RW(role);

अटल काष्ठा attribute *ci_attrs[] = अणु
	&dev_attr_role.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(ci);

अटल पूर्णांक ci_hdrc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device	*dev = &pdev->dev;
	काष्ठा ci_hdrc	*ci;
	काष्ठा resource	*res;
	व्योम __iomem	*base;
	पूर्णांक		ret;
	क्रमागत usb_dr_mode dr_mode;

	अगर (!dev_get_platdata(dev)) अणु
		dev_err(dev, "platform data missing\n");
		वापस -ENODEV;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	ci = devm_kzalloc(dev, माप(*ci), GFP_KERNEL);
	अगर (!ci)
		वापस -ENOMEM;

	spin_lock_init(&ci->lock);
	ci->dev = dev;
	ci->platdata = dev_get_platdata(dev);
	ci->imx28_ग_लिखो_fix = !!(ci->platdata->flags &
		CI_HDRC_IMX28_WRITE_FIX);
	ci->supports_runसमय_pm = !!(ci->platdata->flags &
		CI_HDRC_SUPPORTS_RUNTIME_PM);
	platक्रमm_set_drvdata(pdev, ci);

	ret = hw_device_init(ci, base);
	अगर (ret < 0) अणु
		dev_err(dev, "can't initialize hardware\n");
		वापस -ENODEV;
	पूर्ण

	ret = ci_ulpi_init(ci);
	अगर (ret)
		वापस ret;

	अगर (ci->platdata->phy) अणु
		ci->phy = ci->platdata->phy;
	पूर्ण अन्यथा अगर (ci->platdata->usb_phy) अणु
		ci->usb_phy = ci->platdata->usb_phy;
	पूर्ण अन्यथा अणु
		/* Look क्रम a generic PHY first */
		ci->phy = devm_phy_get(dev->parent, "usb-phy");

		अगर (PTR_ERR(ci->phy) == -EPROBE_DEFER) अणु
			ret = -EPROBE_DEFER;
			जाओ ulpi_निकास;
		पूर्ण अन्यथा अगर (IS_ERR(ci->phy)) अणु
			ci->phy = शून्य;
		पूर्ण

		/* Look क्रम a legacy USB PHY from device-tree next */
		अगर (!ci->phy) अणु
			ci->usb_phy = devm_usb_get_phy_by_phandle(dev->parent,
								  "phys", 0);

			अगर (PTR_ERR(ci->usb_phy) == -EPROBE_DEFER) अणु
				ret = -EPROBE_DEFER;
				जाओ ulpi_निकास;
			पूर्ण अन्यथा अगर (IS_ERR(ci->usb_phy)) अणु
				ci->usb_phy = शून्य;
			पूर्ण
		पूर्ण

		/* Look क्रम any रेजिस्टरed legacy USB PHY as last resort */
		अगर (!ci->phy && !ci->usb_phy) अणु
			ci->usb_phy = devm_usb_get_phy(dev->parent,
						       USB_PHY_TYPE_USB2);

			अगर (PTR_ERR(ci->usb_phy) == -EPROBE_DEFER) अणु
				ret = -EPROBE_DEFER;
				जाओ ulpi_निकास;
			पूर्ण अन्यथा अगर (IS_ERR(ci->usb_phy)) अणु
				ci->usb_phy = शून्य;
			पूर्ण
		पूर्ण

		/* No USB PHY was found in the end */
		अगर (!ci->phy && !ci->usb_phy) अणु
			ret = -ENXIO;
			जाओ ulpi_निकास;
		पूर्ण
	पूर्ण

	ret = ci_usb_phy_init(ci);
	अगर (ret) अणु
		dev_err(dev, "unable to init phy: %d\n", ret);
		वापस ret;
	पूर्ण

	ci->hw_bank.phys = res->start;

	ci->irq = platक्रमm_get_irq(pdev, 0);
	अगर (ci->irq < 0) अणु
		ret = ci->irq;
		जाओ deinit_phy;
	पूर्ण

	ci_get_otg_capable(ci);

	dr_mode = ci->platdata->dr_mode;
	/* initialize role(s) beक्रमe the पूर्णांकerrupt is requested */
	अगर (dr_mode == USB_DR_MODE_OTG || dr_mode == USB_DR_MODE_HOST) अणु
		ret = ci_hdrc_host_init(ci);
		अगर (ret) अणु
			अगर (ret == -ENXIO)
				dev_info(dev, "doesn't support host\n");
			अन्यथा
				जाओ deinit_phy;
		पूर्ण
	पूर्ण

	अगर (dr_mode == USB_DR_MODE_OTG || dr_mode == USB_DR_MODE_PERIPHERAL) अणु
		ret = ci_hdrc_gadget_init(ci);
		अगर (ret) अणु
			अगर (ret == -ENXIO)
				dev_info(dev, "doesn't support gadget\n");
			अन्यथा
				जाओ deinit_host;
		पूर्ण
	पूर्ण

	अगर (!ci->roles[CI_ROLE_HOST] && !ci->roles[CI_ROLE_GADGET]) अणु
		dev_err(dev, "no supported roles\n");
		ret = -ENODEV;
		जाओ deinit_gadget;
	पूर्ण

	अगर (ci->is_otg && ci->roles[CI_ROLE_GADGET]) अणु
		ret = ci_hdrc_otg_init(ci);
		अगर (ret) अणु
			dev_err(dev, "init otg fails, ret = %d\n", ret);
			जाओ deinit_gadget;
		पूर्ण
	पूर्ण

	अगर (ci_role_चयन.fwnode) अणु
		ci_role_चयन.driver_data = ci;
		ci->role_चयन = usb_role_चयन_रेजिस्टर(dev,
					&ci_role_चयन);
		अगर (IS_ERR(ci->role_चयन)) अणु
			ret = PTR_ERR(ci->role_चयन);
			जाओ deinit_otg;
		पूर्ण
	पूर्ण

	अगर (ci->roles[CI_ROLE_HOST] && ci->roles[CI_ROLE_GADGET]) अणु
		अगर (ci->is_otg) अणु
			ci->role = ci_otg_role(ci);
			/* Enable ID change irq */
			hw_ग_लिखो_otgsc(ci, OTGSC_IDIE, OTGSC_IDIE);
		पूर्ण अन्यथा अणु
			/*
			 * If the controller is not OTG capable, but support
			 * role चयन, the defalt role is gadget, and the
			 * user can चयन it through debugfs.
			 */
			ci->role = CI_ROLE_GADGET;
		पूर्ण
	पूर्ण अन्यथा अणु
		ci->role = ci->roles[CI_ROLE_HOST]
			? CI_ROLE_HOST
			: CI_ROLE_GADGET;
	पूर्ण

	अगर (!ci_otg_is_fsm_mode(ci)) अणु
		/* only update vbus status क्रम peripheral */
		अगर (ci->role == CI_ROLE_GADGET) अणु
			/* Pull करोwn DP क्रम possible अक्षरger detection */
			hw_ग_लिखो(ci, OP_USBCMD, USBCMD_RS, 0);
			ci_handle_vbus_change(ci);
		पूर्ण

		ret = ci_role_start(ci, ci->role);
		अगर (ret) अणु
			dev_err(dev, "can't start %s role\n",
						ci_role(ci)->name);
			जाओ stop;
		पूर्ण
	पूर्ण

	ret = devm_request_irq(dev, ci->irq, ci_irq, IRQF_SHARED,
			ci->platdata->name, ci);
	अगर (ret)
		जाओ stop;

	ret = ci_extcon_रेजिस्टर(ci);
	अगर (ret)
		जाओ stop;

	अगर (ci->supports_runसमय_pm) अणु
		pm_runसमय_set_active(&pdev->dev);
		pm_runसमय_enable(&pdev->dev);
		pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, 2000);
		pm_runसमय_mark_last_busy(ci->dev);
		pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	पूर्ण

	अगर (ci_otg_is_fsm_mode(ci))
		ci_hdrc_otg_fsm_start(ci);

	device_set_wakeup_capable(&pdev->dev, true);
	dbg_create_files(ci);

	वापस 0;

stop:
	अगर (ci->role_चयन)
		usb_role_चयन_unरेजिस्टर(ci->role_चयन);
deinit_otg:
	अगर (ci->is_otg && ci->roles[CI_ROLE_GADGET])
		ci_hdrc_otg_destroy(ci);
deinit_gadget:
	ci_hdrc_gadget_destroy(ci);
deinit_host:
	ci_hdrc_host_destroy(ci);
deinit_phy:
	ci_usb_phy_निकास(ci);
ulpi_निकास:
	ci_ulpi_निकास(ci);

	वापस ret;
पूर्ण

अटल पूर्णांक ci_hdrc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ci_hdrc *ci = platक्रमm_get_drvdata(pdev);

	अगर (ci->role_चयन)
		usb_role_चयन_unरेजिस्टर(ci->role_चयन);

	अगर (ci->supports_runसमय_pm) अणु
		pm_runसमय_get_sync(&pdev->dev);
		pm_runसमय_disable(&pdev->dev);
		pm_runसमय_put_noidle(&pdev->dev);
	पूर्ण

	dbg_हटाओ_files(ci);
	ci_role_destroy(ci);
	ci_hdrc_enter_lpm(ci, true);
	ci_usb_phy_निकास(ci);
	ci_ulpi_निकास(ci);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
/* Prepare wakeup by SRP beक्रमe suspend */
अटल व्योम ci_otg_fsm_suspend_क्रम_srp(काष्ठा ci_hdrc *ci)
अणु
	अगर ((ci->fsm.otg->state == OTG_STATE_A_IDLE) &&
				!hw_पढ़ो_otgsc(ci, OTGSC_ID)) अणु
		hw_ग_लिखो(ci, OP_PORTSC, PORTSC_W1C_BITS | PORTSC_PP,
								PORTSC_PP);
		hw_ग_लिखो(ci, OP_PORTSC, PORTSC_W1C_BITS | PORTSC_WKCN,
								PORTSC_WKCN);
	पूर्ण
पूर्ण

/* Handle SRP when wakeup by data pulse */
अटल व्योम ci_otg_fsm_wakeup_by_srp(काष्ठा ci_hdrc *ci)
अणु
	अगर ((ci->fsm.otg->state == OTG_STATE_A_IDLE) &&
		(ci->fsm.a_bus_drop == 1) && (ci->fsm.a_bus_req == 0)) अणु
		अगर (!hw_पढ़ो_otgsc(ci, OTGSC_ID)) अणु
			ci->fsm.a_srp_det = 1;
			ci->fsm.a_bus_drop = 0;
		पूर्ण अन्यथा अणु
			ci->fsm.id = 1;
		पूर्ण
		ci_otg_queue_work(ci);
	पूर्ण
पूर्ण

अटल व्योम ci_controller_suspend(काष्ठा ci_hdrc *ci)
अणु
	disable_irq(ci->irq);
	ci_hdrc_enter_lpm(ci, true);
	अगर (ci->platdata->phy_clkgate_delay_us)
		usleep_range(ci->platdata->phy_clkgate_delay_us,
			     ci->platdata->phy_clkgate_delay_us + 50);
	usb_phy_set_suspend(ci->usb_phy, 1);
	ci->in_lpm = true;
	enable_irq(ci->irq);
पूर्ण

/*
 * Handle the wakeup पूर्णांकerrupt triggered by extcon connector
 * We need to call ci_irq again क्रम extcon since the first
 * पूर्णांकerrupt (wakeup पूर्णांक) only let the controller be out of
 * low घातer mode, but not handle any पूर्णांकerrupts.
 */
अटल व्योम ci_extcon_wakeup_पूर्णांक(काष्ठा ci_hdrc *ci)
अणु
	काष्ठा ci_hdrc_cable *cable_id, *cable_vbus;
	u32 otgsc = hw_पढ़ो_otgsc(ci, ~0);

	cable_id = &ci->platdata->id_extcon;
	cable_vbus = &ci->platdata->vbus_extcon;

	अगर (!IS_ERR(cable_id->edev) && ci->is_otg &&
		(otgsc & OTGSC_IDIE) && (otgsc & OTGSC_IDIS))
		ci_irq(ci->irq, ci);

	अगर (!IS_ERR(cable_vbus->edev) && ci->is_otg &&
		(otgsc & OTGSC_BSVIE) && (otgsc & OTGSC_BSVIS))
		ci_irq(ci->irq, ci);
पूर्ण

अटल पूर्णांक ci_controller_resume(काष्ठा device *dev)
अणु
	काष्ठा ci_hdrc *ci = dev_get_drvdata(dev);
	पूर्णांक ret;

	dev_dbg(dev, "at %s\n", __func__);

	अगर (!ci->in_lpm) अणु
		WARN_ON(1);
		वापस 0;
	पूर्ण

	ci_hdrc_enter_lpm(ci, false);

	ret = ci_ulpi_resume(ci);
	अगर (ret)
		वापस ret;

	अगर (ci->usb_phy) अणु
		usb_phy_set_suspend(ci->usb_phy, 0);
		usb_phy_set_wakeup(ci->usb_phy, false);
		hw_रुको_phy_stable();
	पूर्ण

	ci->in_lpm = false;
	अगर (ci->wakeup_पूर्णांक) अणु
		ci->wakeup_पूर्णांक = false;
		pm_runसमय_mark_last_busy(ci->dev);
		pm_runसमय_put_स्वतःsuspend(ci->dev);
		enable_irq(ci->irq);
		अगर (ci_otg_is_fsm_mode(ci))
			ci_otg_fsm_wakeup_by_srp(ci);
		ci_extcon_wakeup_पूर्णांक(ci);
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक ci_suspend(काष्ठा device *dev)
अणु
	काष्ठा ci_hdrc *ci = dev_get_drvdata(dev);

	अगर (ci->wq)
		flush_workqueue(ci->wq);
	/*
	 * Controller needs to be active during suspend, otherwise the core
	 * may run resume when the parent is at suspend अगर other driver's
	 * suspend fails, it occurs beक्रमe parent's suspend has not started,
	 * but the core suspend has finished.
	 */
	अगर (ci->in_lpm)
		pm_runसमय_resume(dev);

	अगर (ci->in_lpm) अणु
		WARN_ON(1);
		वापस 0;
	पूर्ण

	अगर (device_may_wakeup(dev)) अणु
		अगर (ci_otg_is_fsm_mode(ci))
			ci_otg_fsm_suspend_क्रम_srp(ci);

		usb_phy_set_wakeup(ci->usb_phy, true);
		enable_irq_wake(ci->irq);
	पूर्ण

	ci_controller_suspend(ci);

	वापस 0;
पूर्ण

अटल पूर्णांक ci_resume(काष्ठा device *dev)
अणु
	काष्ठा ci_hdrc *ci = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (device_may_wakeup(dev))
		disable_irq_wake(ci->irq);

	ret = ci_controller_resume(dev);
	अगर (ret)
		वापस ret;

	अगर (ci->supports_runसमय_pm) अणु
		pm_runसमय_disable(dev);
		pm_runसमय_set_active(dev);
		pm_runसमय_enable(dev);
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल पूर्णांक ci_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा ci_hdrc *ci = dev_get_drvdata(dev);

	dev_dbg(dev, "at %s\n", __func__);

	अगर (ci->in_lpm) अणु
		WARN_ON(1);
		वापस 0;
	पूर्ण

	अगर (ci_otg_is_fsm_mode(ci))
		ci_otg_fsm_suspend_क्रम_srp(ci);

	usb_phy_set_wakeup(ci->usb_phy, true);
	ci_controller_suspend(ci);

	वापस 0;
पूर्ण

अटल पूर्णांक ci_runसमय_resume(काष्ठा device *dev)
अणु
	वापस ci_controller_resume(dev);
पूर्ण

#पूर्ण_अगर /* CONFIG_PM */
अटल स्थिर काष्ठा dev_pm_ops ci_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(ci_suspend, ci_resume)
	SET_RUNTIME_PM_OPS(ci_runसमय_suspend, ci_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver ci_hdrc_driver = अणु
	.probe	= ci_hdrc_probe,
	.हटाओ	= ci_hdrc_हटाओ,
	.driver	= अणु
		.name	= "ci_hdrc",
		.pm	= &ci_pm_ops,
		.dev_groups = ci_groups,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ci_hdrc_platक्रमm_रेजिस्टर(व्योम)
अणु
	ci_hdrc_host_driver_init();
	वापस platक्रमm_driver_रेजिस्टर(&ci_hdrc_driver);
पूर्ण
module_init(ci_hdrc_platक्रमm_रेजिस्टर);

अटल व्योम __निकास ci_hdrc_platक्रमm_unरेजिस्टर(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ci_hdrc_driver);
पूर्ण
module_निकास(ci_hdrc_platक्रमm_unरेजिस्टर);

MODULE_ALIAS("platform:ci_hdrc");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("David Lopo <dlopo@chipidea.mips.com>");
MODULE_DESCRIPTION("ChipIdea HDRC Driver");
