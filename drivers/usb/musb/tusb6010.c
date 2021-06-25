<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * TUSB6010 USB 2.0 OTG Dual Role controller
 *
 * Copyright (C) 2006 Nokia Corporation
 * Tony Lindgren <tony@atomide.com>
 *
 * Notes:
 * - Driver assumes that पूर्णांकerface to बाह्यal host (मुख्य CPU) is
 *   configured क्रम NOR FLASH पूर्णांकerface instead of VLYNQ serial
 *   पूर्णांकerface.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/usb.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/usb/usb_phy_generic.h>

#समावेश "musb_core.h"

काष्ठा tusb6010_glue अणु
	काष्ठा device		*dev;
	काष्ठा platक्रमm_device	*musb;
	काष्ठा platक्रमm_device	*phy;
पूर्ण;

अटल व्योम tusb_musb_set_vbus(काष्ठा musb *musb, पूर्णांक is_on);

#घोषणा TUSB_REV_MAJOR(reg_val)		((reg_val >> 4) & 0xf)
#घोषणा TUSB_REV_MINOR(reg_val)		(reg_val & 0xf)

/*
 * Checks the revision. We need to use the DMA रेजिस्टर as 3.0 करोes not
 * have correct versions क्रम TUSB_PRCM_REV or TUSB_INT_CTRL_REV.
 */
अटल u8 tusb_get_revision(काष्ठा musb *musb)
अणु
	व्योम __iomem	*tbase = musb->ctrl_base;
	u32		die_id;
	u8		rev;

	rev = musb_पढ़ोl(tbase, TUSB_DMA_CTRL_REV) & 0xff;
	अगर (TUSB_REV_MAJOR(rev) == 3) अणु
		die_id = TUSB_DIDR1_HI_CHIP_REV(musb_पढ़ोl(tbase,
				TUSB_DIDR1_HI));
		अगर (die_id >= TUSB_DIDR1_HI_REV_31)
			rev |= 1;
	पूर्ण

	वापस rev;
पूर्ण

अटल व्योम tusb_prपूर्णांक_revision(काष्ठा musb *musb)
अणु
	व्योम __iomem	*tbase = musb->ctrl_base;
	u8		rev;

	rev = musb->tusb_revision;

	pr_info("tusb: %s%i.%i %s%i.%i %s%i.%i %s%i.%i %s%i %s%i.%i\n",
		"prcm",
		TUSB_REV_MAJOR(musb_पढ़ोl(tbase, TUSB_PRCM_REV)),
		TUSB_REV_MINOR(musb_पढ़ोl(tbase, TUSB_PRCM_REV)),
		"int",
		TUSB_REV_MAJOR(musb_पढ़ोl(tbase, TUSB_INT_CTRL_REV)),
		TUSB_REV_MINOR(musb_पढ़ोl(tbase, TUSB_INT_CTRL_REV)),
		"gpio",
		TUSB_REV_MAJOR(musb_पढ़ोl(tbase, TUSB_GPIO_REV)),
		TUSB_REV_MINOR(musb_पढ़ोl(tbase, TUSB_GPIO_REV)),
		"dma",
		TUSB_REV_MAJOR(musb_पढ़ोl(tbase, TUSB_DMA_CTRL_REV)),
		TUSB_REV_MINOR(musb_पढ़ोl(tbase, TUSB_DMA_CTRL_REV)),
		"dieid",
		TUSB_DIDR1_HI_CHIP_REV(musb_पढ़ोl(tbase, TUSB_DIDR1_HI)),
		"rev",
		TUSB_REV_MAJOR(rev), TUSB_REV_MINOR(rev));
पूर्ण

#घोषणा WBUS_QUIRK_MASK	(TUSB_PHY_OTG_CTRL_TESTM2 | TUSB_PHY_OTG_CTRL_TESTM1 \
				| TUSB_PHY_OTG_CTRL_TESTM0)

/*
 * Workaround क्रम spontaneous WBUS wake-up issue #2 क्रम tusb3.0.
 * Disables घातer detection in PHY क्रम the duration of idle.
 */
अटल व्योम tusb_wbus_quirk(काष्ठा musb *musb, पूर्णांक enabled)
अणु
	व्योम __iomem	*tbase = musb->ctrl_base;
	अटल u32	phy_otg_ctrl, phy_otg_ena;
	u32		पंचांगp;

	अगर (enabled) अणु
		phy_otg_ctrl = musb_पढ़ोl(tbase, TUSB_PHY_OTG_CTRL);
		phy_otg_ena = musb_पढ़ोl(tbase, TUSB_PHY_OTG_CTRL_ENABLE);
		पंचांगp = TUSB_PHY_OTG_CTRL_WRPROTECT
				| phy_otg_ena | WBUS_QUIRK_MASK;
		musb_ग_लिखोl(tbase, TUSB_PHY_OTG_CTRL, पंचांगp);
		पंचांगp = phy_otg_ena & ~WBUS_QUIRK_MASK;
		पंचांगp |= TUSB_PHY_OTG_CTRL_WRPROTECT | TUSB_PHY_OTG_CTRL_TESTM2;
		musb_ग_लिखोl(tbase, TUSB_PHY_OTG_CTRL_ENABLE, पंचांगp);
		dev_dbg(musb->controller, "Enabled tusb wbus quirk ctrl %08x ena %08x\n",
			musb_पढ़ोl(tbase, TUSB_PHY_OTG_CTRL),
			musb_पढ़ोl(tbase, TUSB_PHY_OTG_CTRL_ENABLE));
	पूर्ण अन्यथा अगर (musb_पढ़ोl(tbase, TUSB_PHY_OTG_CTRL_ENABLE)
					& TUSB_PHY_OTG_CTRL_TESTM2) अणु
		पंचांगp = TUSB_PHY_OTG_CTRL_WRPROTECT | phy_otg_ctrl;
		musb_ग_लिखोl(tbase, TUSB_PHY_OTG_CTRL, पंचांगp);
		पंचांगp = TUSB_PHY_OTG_CTRL_WRPROTECT | phy_otg_ena;
		musb_ग_लिखोl(tbase, TUSB_PHY_OTG_CTRL_ENABLE, पंचांगp);
		dev_dbg(musb->controller, "Disabled tusb wbus quirk ctrl %08x ena %08x\n",
			musb_पढ़ोl(tbase, TUSB_PHY_OTG_CTRL),
			musb_पढ़ोl(tbase, TUSB_PHY_OTG_CTRL_ENABLE));
		phy_otg_ctrl = 0;
		phy_otg_ena = 0;
	पूर्ण
पूर्ण

अटल u32 tusb_fअगरo_offset(u8 epnum)
अणु
	वापस 0x200 + (epnum * 0x20);
पूर्ण

अटल u32 tusb_ep_offset(u8 epnum, u16 offset)
अणु
	वापस 0x10 + offset;
पूर्ण

/* TUSB mapping: "flat" plus ep0 special हालs */
अटल व्योम tusb_ep_select(व्योम __iomem *mbase, u8 epnum)
अणु
	musb_ग_लिखोb(mbase, MUSB_INDEX, epnum);
पूर्ण

/*
 * TUSB6010 करोesn't allow 8-bit access; 16-bit access is the minimum.
 */
अटल u8 tusb_पढ़ोb(व्योम __iomem *addr, u32 offset)
अणु
	u16 पंचांगp;
	u8 val;

	पंचांगp = __raw_पढ़ोw(addr + (offset & ~1));
	अगर (offset & 1)
		val = (पंचांगp >> 8);
	अन्यथा
		val = पंचांगp & 0xff;

	वापस val;
पूर्ण

अटल व्योम tusb_ग_लिखोb(व्योम __iomem *addr, u32 offset, u8 data)
अणु
	u16 पंचांगp;

	पंचांगp = __raw_पढ़ोw(addr + (offset & ~1));
	अगर (offset & 1)
		पंचांगp = (data << 8) | (पंचांगp & 0xff);
	अन्यथा
		पंचांगp = (पंचांगp & 0xff00) | data;

	__raw_ग_लिखोw(पंचांगp, addr + (offset & ~1));
पूर्ण

/*
 * TUSB 6010 may use a parallel bus that करोesn't support byte ops;
 * so both loading and unloading FIFOs need explicit byte counts.
 */

अटल अंतरभूत व्योम
tusb_fअगरo_ग_लिखो_unaligned(व्योम __iomem *fअगरo, स्थिर u8 *buf, u16 len)
अणु
	u32		val;
	पूर्णांक		i;

	अगर (len > 4) अणु
		क्रम (i = 0; i < (len >> 2); i++) अणु
			स_नकल(&val, buf, 4);
			musb_ग_लिखोl(fअगरo, 0, val);
			buf += 4;
		पूर्ण
		len %= 4;
	पूर्ण
	अगर (len > 0) अणु
		/* Write the rest 1 - 3 bytes to FIFO */
		स_नकल(&val, buf, len);
		musb_ग_लिखोl(fअगरo, 0, val);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम tusb_fअगरo_पढ़ो_unaligned(व्योम __iomem *fअगरo,
						व्योम *buf, u16 len)
अणु
	u32		val;
	पूर्णांक		i;

	अगर (len > 4) अणु
		क्रम (i = 0; i < (len >> 2); i++) अणु
			val = musb_पढ़ोl(fअगरo, 0);
			स_नकल(buf, &val, 4);
			buf += 4;
		पूर्ण
		len %= 4;
	पूर्ण
	अगर (len > 0) अणु
		/* Read the rest 1 - 3 bytes from FIFO */
		val = musb_पढ़ोl(fअगरo, 0);
		स_नकल(buf, &val, len);
	पूर्ण
पूर्ण

अटल व्योम tusb_ग_लिखो_fअगरo(काष्ठा musb_hw_ep *hw_ep, u16 len, स्थिर u8 *buf)
अणु
	काष्ठा musb *musb = hw_ep->musb;
	व्योम __iomem	*ep_conf = hw_ep->conf;
	व्योम __iomem	*fअगरo = hw_ep->fअगरo;
	u8		epnum = hw_ep->epnum;

	prefetch(buf);

	dev_dbg(musb->controller, "%cX ep%d fifo %p count %d buf %p\n",
			'T', epnum, fअगरo, len, buf);

	अगर (epnum)
		musb_ग_लिखोl(ep_conf, TUSB_EP_TX_OFFSET,
			TUSB_EP_CONFIG_XFR_SIZE(len));
	अन्यथा
		musb_ग_लिखोl(ep_conf, 0, TUSB_EP0_CONFIG_सूची_TX |
			TUSB_EP0_CONFIG_XFR_SIZE(len));

	अगर (likely((0x01 & (अचिन्हित दीर्घ) buf) == 0)) अणु

		/* Best हाल is 32bit-aligned destination address */
		अगर ((0x02 & (अचिन्हित दीर्घ) buf) == 0) अणु
			अगर (len >= 4) अणु
				ioग_लिखो32_rep(fअगरo, buf, len >> 2);
				buf += (len & ~0x03);
				len &= 0x03;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (len >= 2) अणु
				u32 val;
				पूर्णांक i;

				/* Cannot use ग_लिखोsw, fअगरo is 32-bit */
				क्रम (i = 0; i < (len >> 2); i++) अणु
					val = (u32)(*(u16 *)buf);
					buf += 2;
					val |= (*(u16 *)buf) << 16;
					buf += 2;
					musb_ग_लिखोl(fअगरo, 0, val);
				पूर्ण
				len &= 0x03;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (len > 0)
		tusb_fअगरo_ग_लिखो_unaligned(fअगरo, buf, len);
पूर्ण

अटल व्योम tusb_पढ़ो_fअगरo(काष्ठा musb_hw_ep *hw_ep, u16 len, u8 *buf)
अणु
	काष्ठा musb *musb = hw_ep->musb;
	व्योम __iomem	*ep_conf = hw_ep->conf;
	व्योम __iomem	*fअगरo = hw_ep->fअगरo;
	u8		epnum = hw_ep->epnum;

	dev_dbg(musb->controller, "%cX ep%d fifo %p count %d buf %p\n",
			'R', epnum, fअगरo, len, buf);

	अगर (epnum)
		musb_ग_लिखोl(ep_conf, TUSB_EP_RX_OFFSET,
			TUSB_EP_CONFIG_XFR_SIZE(len));
	अन्यथा
		musb_ग_लिखोl(ep_conf, 0, TUSB_EP0_CONFIG_XFR_SIZE(len));

	अगर (likely((0x01 & (अचिन्हित दीर्घ) buf) == 0)) अणु

		/* Best हाल is 32bit-aligned destination address */
		अगर ((0x02 & (अचिन्हित दीर्घ) buf) == 0) अणु
			अगर (len >= 4) अणु
				ioपढ़ो32_rep(fअगरo, buf, len >> 2);
				buf += (len & ~0x03);
				len &= 0x03;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (len >= 2) अणु
				u32 val;
				पूर्णांक i;

				/* Cannot use पढ़ोsw, fअगरo is 32-bit */
				क्रम (i = 0; i < (len >> 2); i++) अणु
					val = musb_पढ़ोl(fअगरo, 0);
					*(u16 *)buf = (u16)(val & 0xffff);
					buf += 2;
					*(u16 *)buf = (u16)(val >> 16);
					buf += 2;
				पूर्ण
				len &= 0x03;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (len > 0)
		tusb_fअगरo_पढ़ो_unaligned(fअगरo, buf, len);
पूर्ण

अटल काष्ठा musb *the_musb;

/* This is used by gadget drivers, and OTG transceiver logic, allowing
 * at most mA current to be drawn from VBUS during a Default-B session
 * (that is, जबतक VBUS exceeds 4.4V).  In Default-A (including pure host
 * mode), or low घातer Default-B sessions, something अन्यथा supplies घातer.
 * Caller must take care of locking.
 */
अटल पूर्णांक tusb_draw_घातer(काष्ठा usb_phy *x, अचिन्हित mA)
अणु
	काष्ठा musb	*musb = the_musb;
	व्योम __iomem	*tbase = musb->ctrl_base;
	u32		reg;

	/* tps65030 seems to consume max 100mA, with maybe 60mA available
	 * (measured on one board) क्रम things other than tps and tusb.
	 *
	 * Boards sharing the CPU घड़ी with CLKIN will need to prevent
	 * certain idle sleep states जबतक the USB link is active.
	 *
	 * REVISIT we could use VBUS to supply only _one_ of अणु 1.5V, 3.3V पूर्ण.
	 * The actual current usage would be very board-specअगरic.  For now,
	 * it's simpler to just use an aggregate (also board-specअगरic).
	 */
	अगर (x->otg->शेष_a || mA < (musb->min_घातer << 1))
		mA = 0;

	reg = musb_पढ़ोl(tbase, TUSB_PRCM_MNGMT);
	अगर (mA) अणु
		musb->is_bus_घातered = 1;
		reg |= TUSB_PRCM_MNGMT_15_SW_EN | TUSB_PRCM_MNGMT_33_SW_EN;
	पूर्ण अन्यथा अणु
		musb->is_bus_घातered = 0;
		reg &= ~(TUSB_PRCM_MNGMT_15_SW_EN | TUSB_PRCM_MNGMT_33_SW_EN);
	पूर्ण
	musb_ग_लिखोl(tbase, TUSB_PRCM_MNGMT, reg);

	dev_dbg(musb->controller, "draw max %d mA VBUS\n", mA);
	वापस 0;
पूर्ण

/* workaround क्रम issue 13:  change घड़ी during chip idle
 * (to be fixed in rev3 silicon) ... symptoms include disconnect
 * or looping suspend/resume cycles
 */
अटल व्योम tusb_set_घड़ी_source(काष्ठा musb *musb, अचिन्हित mode)
अणु
	व्योम __iomem	*tbase = musb->ctrl_base;
	u32		reg;

	reg = musb_पढ़ोl(tbase, TUSB_PRCM_CONF);
	reg &= ~TUSB_PRCM_CONF_SYS_CLKSEL(0x3);

	/* 0 = refclk (clkin, XI)
	 * 1 = PHY 60 MHz (पूर्णांकernal PLL)
	 * 2 = not supported
	 * 3 = what?
	 */
	अगर (mode > 0)
		reg |= TUSB_PRCM_CONF_SYS_CLKSEL(mode & 0x3);

	musb_ग_लिखोl(tbase, TUSB_PRCM_CONF, reg);

	/* FIXME tusb6010_platक्रमm_reसमय(mode == 0); */
पूर्ण

/*
 * Idle TUSB6010 until next wake-up event; NOR access always wakes.
 * Other code ensures that we idle unless we're connected _and_ the
 * USB link is not suspended ... and tells us the relevant wakeup
 * events.  SW_EN क्रम voltage is handled separately.
 */
अटल व्योम tusb_allow_idle(काष्ठा musb *musb, u32 wakeup_enables)
अणु
	व्योम __iomem	*tbase = musb->ctrl_base;
	u32		reg;

	अगर ((wakeup_enables & TUSB_PRCM_WBUS)
			&& (musb->tusb_revision == TUSB_REV_30))
		tusb_wbus_quirk(musb, 1);

	tusb_set_घड़ी_source(musb, 0);

	wakeup_enables |= TUSB_PRCM_WNORCS;
	musb_ग_लिखोl(tbase, TUSB_PRCM_WAKEUP_MASK, ~wakeup_enables);

	/* REVISIT ग_लिखोup of WID implies that अगर WID set and ID is grounded,
	 * TUSB_PHY_OTG_CTRL.TUSB_PHY_OTG_CTRL_OTG_ID_PULLUP must be cleared.
	 * Presumably that's mostly to save घातer, hence WID is immaterial ...
	 */

	reg = musb_पढ़ोl(tbase, TUSB_PRCM_MNGMT);
	/* issue 4: when driving vbus, use hiघातer (vbus_det) comparator */
	अगर (is_host_active(musb)) अणु
		reg |= TUSB_PRCM_MNGMT_OTG_VBUS_DET_EN;
		reg &= ~TUSB_PRCM_MNGMT_OTG_SESS_END_EN;
	पूर्ण अन्यथा अणु
		reg |= TUSB_PRCM_MNGMT_OTG_SESS_END_EN;
		reg &= ~TUSB_PRCM_MNGMT_OTG_VBUS_DET_EN;
	पूर्ण
	reg |= TUSB_PRCM_MNGMT_PM_IDLE | TUSB_PRCM_MNGMT_DEV_IDLE;
	musb_ग_लिखोl(tbase, TUSB_PRCM_MNGMT, reg);

	dev_dbg(musb->controller, "idle, wake on %02x\n", wakeup_enables);
पूर्ण

/*
 * Updates cable VBUS status. Caller must take care of locking.
 */
अटल पूर्णांक tusb_musb_vbus_status(काष्ठा musb *musb)
अणु
	व्योम __iomem	*tbase = musb->ctrl_base;
	u32		otg_stat, prcm_mngmt;
	पूर्णांक		ret = 0;

	otg_stat = musb_पढ़ोl(tbase, TUSB_DEV_OTG_STAT);
	prcm_mngmt = musb_पढ़ोl(tbase, TUSB_PRCM_MNGMT);

	/* Temporarily enable VBUS detection अगर it was disabled क्रम
	 * suspend mode. Unless it's enabled otg_stat and devctl will
	 * not show correct VBUS state.
	 */
	अगर (!(prcm_mngmt & TUSB_PRCM_MNGMT_OTG_VBUS_DET_EN)) अणु
		u32 पंचांगp = prcm_mngmt;
		पंचांगp |= TUSB_PRCM_MNGMT_OTG_VBUS_DET_EN;
		musb_ग_लिखोl(tbase, TUSB_PRCM_MNGMT, पंचांगp);
		otg_stat = musb_पढ़ोl(tbase, TUSB_DEV_OTG_STAT);
		musb_ग_लिखोl(tbase, TUSB_PRCM_MNGMT, prcm_mngmt);
	पूर्ण

	अगर (otg_stat & TUSB_DEV_OTG_STAT_VBUS_VALID)
		ret = 1;

	वापस ret;
पूर्ण

अटल व्योम musb_करो_idle(काष्ठा समयr_list *t)
अणु
	काष्ठा musb	*musb = from_समयr(musb, t, dev_समयr);
	अचिन्हित दीर्घ	flags;

	spin_lock_irqsave(&musb->lock, flags);

	चयन (musb->xceiv->otg->state) अणु
	हाल OTG_STATE_A_WAIT_BCON:
		अगर ((musb->a_रुको_bcon != 0)
			&& (musb->idle_समयout == 0
				|| समय_after(jअगरfies, musb->idle_समयout))) अणु
			dev_dbg(musb->controller, "Nothing connected %s, turning off VBUS\n",
					usb_otg_state_string(musb->xceiv->otg->state));
		पूर्ण
		fallthrough;
	हाल OTG_STATE_A_IDLE:
		tusb_musb_set_vbus(musb, 0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (!musb->is_active) अणु
		u32	wakeups;

		/* रुको until hub_wq handles port change status */
		अगर (is_host_active(musb) && (musb->port1_status >> 16))
			जाओ करोne;

		अगर (!musb->gadget_driver) अणु
			wakeups = 0;
		पूर्ण अन्यथा अणु
			wakeups = TUSB_PRCM_WHOSTDISCON
				| TUSB_PRCM_WBUS
					| TUSB_PRCM_WVBUS;
			wakeups |= TUSB_PRCM_WID;
		पूर्ण
		tusb_allow_idle(musb, wakeups);
	पूर्ण
करोne:
	spin_unlock_irqrestore(&musb->lock, flags);
पूर्ण

/*
 * Maybe put TUSB6010 पूर्णांकo idle mode mode depending on USB link status,
 * like "disconnected" or "suspended".  We'll be woken out of it by
 * connect, resume, or disconnect.
 *
 * Needs to be called as the last function everywhere where there is
 * रेजिस्टर access to TUSB6010 because of NOR flash wake-up.
 * Caller should own controller spinlock.
 *
 * Delay because peripheral enables D+ pullup 3msec after SE0, and
 * we करोn't want to treat that full speed J as a wakeup event.
 * ... peripherals must draw only suspend current after 10 msec.
 */
अटल व्योम tusb_musb_try_idle(काष्ठा musb *musb, अचिन्हित दीर्घ समयout)
अणु
	अचिन्हित दीर्घ		शेष_समयout = jअगरfies + msecs_to_jअगरfies(3);
	अटल अचिन्हित दीर्घ	last_समयr;

	अगर (समयout == 0)
		समयout = शेष_समयout;

	/* Never idle अगर active, or when VBUS समयout is not set as host */
	अगर (musb->is_active || ((musb->a_रुको_bcon == 0)
			&& (musb->xceiv->otg->state == OTG_STATE_A_WAIT_BCON))) अणु
		dev_dbg(musb->controller, "%s active, deleting timer\n",
			usb_otg_state_string(musb->xceiv->otg->state));
		del_समयr(&musb->dev_समयr);
		last_समयr = jअगरfies;
		वापस;
	पूर्ण

	अगर (समय_after(last_समयr, समयout)) अणु
		अगर (!समयr_pending(&musb->dev_समयr))
			last_समयr = समयout;
		अन्यथा अणु
			dev_dbg(musb->controller, "Longer idle timer already pending, ignoring\n");
			वापस;
		पूर्ण
	पूर्ण
	last_समयr = समयout;

	dev_dbg(musb->controller, "%s inactive, for idle timer for %lu ms\n",
		usb_otg_state_string(musb->xceiv->otg->state),
		(अचिन्हित दीर्घ)jअगरfies_to_msecs(समयout - jअगरfies));
	mod_समयr(&musb->dev_समयr, समयout);
पूर्ण

/* ticks of 60 MHz घड़ी */
#घोषणा DEVCLOCK		60000000
#घोषणा OTG_TIMER_MS(msecs)	((msecs) \
		? (TUSB_DEV_OTG_TIMER_VAL((DEVCLOCK/1000)*(msecs)) \
				| TUSB_DEV_OTG_TIMER_ENABLE) \
		: 0)

अटल व्योम tusb_musb_set_vbus(काष्ठा musb *musb, पूर्णांक is_on)
अणु
	व्योम __iomem	*tbase = musb->ctrl_base;
	u32		conf, prcm, समयr;
	u8		devctl;
	काष्ठा usb_otg	*otg = musb->xceiv->otg;

	/* HDRC controls CPEN, but beware current surges during device
	 * connect.  They can trigger transient overcurrent conditions
	 * that must be ignored.
	 */

	prcm = musb_पढ़ोl(tbase, TUSB_PRCM_MNGMT);
	conf = musb_पढ़ोl(tbase, TUSB_DEV_CONF);
	devctl = musb_पढ़ोb(musb->mregs, MUSB_DEVCTL);

	अगर (is_on) अणु
		समयr = OTG_TIMER_MS(OTG_TIME_A_WAIT_VRISE);
		otg->शेष_a = 1;
		musb->xceiv->otg->state = OTG_STATE_A_WAIT_VRISE;
		devctl |= MUSB_DEVCTL_SESSION;

		conf |= TUSB_DEV_CONF_USB_HOST_MODE;
		MUSB_HST_MODE(musb);
	पूर्ण अन्यथा अणु
		u32	otg_stat;

		समयr = 0;

		/* If ID pin is grounded, we want to be a_idle */
		otg_stat = musb_पढ़ोl(tbase, TUSB_DEV_OTG_STAT);
		अगर (!(otg_stat & TUSB_DEV_OTG_STAT_ID_STATUS)) अणु
			चयन (musb->xceiv->otg->state) अणु
			हाल OTG_STATE_A_WAIT_VRISE:
			हाल OTG_STATE_A_WAIT_BCON:
				musb->xceiv->otg->state = OTG_STATE_A_WAIT_VFALL;
				अवरोध;
			हाल OTG_STATE_A_WAIT_VFALL:
				musb->xceiv->otg->state = OTG_STATE_A_IDLE;
				अवरोध;
			शेष:
				musb->xceiv->otg->state = OTG_STATE_A_IDLE;
			पूर्ण
			musb->is_active = 0;
			otg->शेष_a = 1;
			MUSB_HST_MODE(musb);
		पूर्ण अन्यथा अणु
			musb->is_active = 0;
			otg->शेष_a = 0;
			musb->xceiv->otg->state = OTG_STATE_B_IDLE;
			MUSB_DEV_MODE(musb);
		पूर्ण

		devctl &= ~MUSB_DEVCTL_SESSION;
		conf &= ~TUSB_DEV_CONF_USB_HOST_MODE;
	पूर्ण
	prcm &= ~(TUSB_PRCM_MNGMT_15_SW_EN | TUSB_PRCM_MNGMT_33_SW_EN);

	musb_ग_लिखोl(tbase, TUSB_PRCM_MNGMT, prcm);
	musb_ग_लिखोl(tbase, TUSB_DEV_OTG_TIMER, समयr);
	musb_ग_लिखोl(tbase, TUSB_DEV_CONF, conf);
	musb_ग_लिखोb(musb->mregs, MUSB_DEVCTL, devctl);

	dev_dbg(musb->controller, "VBUS %s, devctl %02x otg %3x conf %08x prcm %08x\n",
		usb_otg_state_string(musb->xceiv->otg->state),
		musb_पढ़ोb(musb->mregs, MUSB_DEVCTL),
		musb_पढ़ोl(tbase, TUSB_DEV_OTG_STAT),
		conf, prcm);
पूर्ण

/*
 * Sets the mode to OTG, peripheral or host by changing the ID detection.
 * Caller must take care of locking.
 *
 * Note that अगर a mini-A cable is plugged in the ID line will stay करोwn as
 * the weak ID pull-up is not able to pull the ID up.
 */
अटल पूर्णांक tusb_musb_set_mode(काष्ठा musb *musb, u8 musb_mode)
अणु
	व्योम __iomem	*tbase = musb->ctrl_base;
	u32		otg_stat, phy_otg_ctrl, phy_otg_ena, dev_conf;

	otg_stat = musb_पढ़ोl(tbase, TUSB_DEV_OTG_STAT);
	phy_otg_ctrl = musb_पढ़ोl(tbase, TUSB_PHY_OTG_CTRL);
	phy_otg_ena = musb_पढ़ोl(tbase, TUSB_PHY_OTG_CTRL_ENABLE);
	dev_conf = musb_पढ़ोl(tbase, TUSB_DEV_CONF);

	चयन (musb_mode) अणु

	हाल MUSB_HOST:		/* Disable PHY ID detect, ground ID */
		phy_otg_ctrl &= ~TUSB_PHY_OTG_CTRL_OTG_ID_PULLUP;
		phy_otg_ena |= TUSB_PHY_OTG_CTRL_OTG_ID_PULLUP;
		dev_conf |= TUSB_DEV_CONF_ID_SEL;
		dev_conf &= ~TUSB_DEV_CONF_SOFT_ID;
		अवरोध;
	हाल MUSB_PERIPHERAL:	/* Disable PHY ID detect, keep ID pull-up on */
		phy_otg_ctrl |= TUSB_PHY_OTG_CTRL_OTG_ID_PULLUP;
		phy_otg_ena |= TUSB_PHY_OTG_CTRL_OTG_ID_PULLUP;
		dev_conf |= (TUSB_DEV_CONF_ID_SEL | TUSB_DEV_CONF_SOFT_ID);
		अवरोध;
	हाल MUSB_OTG:		/* Use PHY ID detection */
		phy_otg_ctrl |= TUSB_PHY_OTG_CTRL_OTG_ID_PULLUP;
		phy_otg_ena |= TUSB_PHY_OTG_CTRL_OTG_ID_PULLUP;
		dev_conf &= ~(TUSB_DEV_CONF_ID_SEL | TUSB_DEV_CONF_SOFT_ID);
		अवरोध;

	शेष:
		dev_dbg(musb->controller, "Trying to set mode %i\n", musb_mode);
		वापस -EINVAL;
	पूर्ण

	musb_ग_लिखोl(tbase, TUSB_PHY_OTG_CTRL,
			TUSB_PHY_OTG_CTRL_WRPROTECT | phy_otg_ctrl);
	musb_ग_लिखोl(tbase, TUSB_PHY_OTG_CTRL_ENABLE,
			TUSB_PHY_OTG_CTRL_WRPROTECT | phy_otg_ena);
	musb_ग_लिखोl(tbase, TUSB_DEV_CONF, dev_conf);

	otg_stat = musb_पढ़ोl(tbase, TUSB_DEV_OTG_STAT);
	अगर ((musb_mode == MUSB_PERIPHERAL) &&
		!(otg_stat & TUSB_DEV_OTG_STAT_ID_STATUS))
			INFO("Cannot be peripheral with mini-A cable "
			"otg_stat: %08x\n", otg_stat);

	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
tusb_otg_पूर्णांकs(काष्ठा musb *musb, u32 पूर्णांक_src, व्योम __iomem *tbase)
अणु
	u32		otg_stat = musb_पढ़ोl(tbase, TUSB_DEV_OTG_STAT);
	अचिन्हित दीर्घ	idle_समयout = 0;
	काष्ठा usb_otg	*otg = musb->xceiv->otg;

	/* ID pin */
	अगर ((पूर्णांक_src & TUSB_INT_SRC_ID_STATUS_CHNG)) अणु
		पूर्णांक	शेष_a;

		शेष_a = !(otg_stat & TUSB_DEV_OTG_STAT_ID_STATUS);
		dev_dbg(musb->controller, "Default-%c\n", शेष_a ? 'A' : 'B');
		otg->शेष_a = शेष_a;
		tusb_musb_set_vbus(musb, शेष_a);

		/* Don't allow idling immediately */
		अगर (शेष_a)
			idle_समयout = jअगरfies + (HZ * 3);
	पूर्ण

	/* VBUS state change */
	अगर (पूर्णांक_src & TUSB_INT_SRC_VBUS_SENSE_CHNG) अणु

		/* B-dev state machine:  no vbus ~= disconnect */
		अगर (!otg->शेष_a) अणु
			/* ? musb_root_disconnect(musb); */
			musb->port1_status &=
				~(USB_PORT_STAT_CONNECTION
				| USB_PORT_STAT_ENABLE
				| USB_PORT_STAT_LOW_SPEED
				| USB_PORT_STAT_HIGH_SPEED
				| USB_PORT_STAT_TEST
				);

			अगर (otg_stat & TUSB_DEV_OTG_STAT_SESS_END) अणु
				dev_dbg(musb->controller, "Forcing disconnect (no interrupt)\n");
				अगर (musb->xceiv->otg->state != OTG_STATE_B_IDLE) अणु
					/* INTR_DISCONNECT can hide... */
					musb->xceiv->otg->state = OTG_STATE_B_IDLE;
					musb->पूर्णांक_usb |= MUSB_INTR_DISCONNECT;
				पूर्ण
				musb->is_active = 0;
			पूर्ण
			dev_dbg(musb->controller, "vbus change, %s, otg %03x\n",
				usb_otg_state_string(musb->xceiv->otg->state), otg_stat);
			idle_समयout = jअगरfies + (1 * HZ);
			schedule_delayed_work(&musb->irq_work, 0);

		पूर्ण अन्यथा /* A-dev state machine */ अणु
			dev_dbg(musb->controller, "vbus change, %s, otg %03x\n",
				usb_otg_state_string(musb->xceiv->otg->state), otg_stat);

			चयन (musb->xceiv->otg->state) अणु
			हाल OTG_STATE_A_IDLE:
				dev_dbg(musb->controller, "Got SRP, turning on VBUS\n");
				musb_platक्रमm_set_vbus(musb, 1);

				/* CONNECT can wake अगर a_रुको_bcon is set */
				अगर (musb->a_रुको_bcon != 0)
					musb->is_active = 0;
				अन्यथा
					musb->is_active = 1;

				/*
				 * OPT FS A TD.4.6 needs few seconds क्रम
				 * A_WAIT_VRISE
				 */
				idle_समयout = jअगरfies + (2 * HZ);

				अवरोध;
			हाल OTG_STATE_A_WAIT_VRISE:
				/* ignore; A-session-valid < VBUS_VALID/2,
				 * we monitor this with the समयr
				 */
				अवरोध;
			हाल OTG_STATE_A_WAIT_VFALL:
				/* REVISIT this irq triggers during लघु
				 * spikes caused by क्रमागतeration ...
				 */
				अगर (musb->vbuserr_retry) अणु
					musb->vbuserr_retry--;
					tusb_musb_set_vbus(musb, 1);
				पूर्ण अन्यथा अणु
					musb->vbuserr_retry
						= VBUSERR_RETRY_COUNT;
					tusb_musb_set_vbus(musb, 0);
				पूर्ण
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* OTG समयr expiration */
	अगर (पूर्णांक_src & TUSB_INT_SRC_OTG_TIMEOUT) अणु
		u8	devctl;

		dev_dbg(musb->controller, "%s timer, %03x\n",
			usb_otg_state_string(musb->xceiv->otg->state), otg_stat);

		चयन (musb->xceiv->otg->state) अणु
		हाल OTG_STATE_A_WAIT_VRISE:
			/* VBUS has probably been valid क्रम a जबतक now,
			 * but may well have bounced out of range a bit
			 */
			devctl = musb_पढ़ोb(musb->mregs, MUSB_DEVCTL);
			अगर (otg_stat & TUSB_DEV_OTG_STAT_VBUS_VALID) अणु
				अगर ((devctl & MUSB_DEVCTL_VBUS)
						!= MUSB_DEVCTL_VBUS) अणु
					dev_dbg(musb->controller, "devctl %02x\n", devctl);
					अवरोध;
				पूर्ण
				musb->xceiv->otg->state = OTG_STATE_A_WAIT_BCON;
				musb->is_active = 0;
				idle_समयout = jअगरfies
					+ msecs_to_jअगरfies(musb->a_रुको_bcon);
			पूर्ण अन्यथा अणु
				/* REVISIT report overcurrent to hub? */
				ERR("vbus too slow, devctl %02x\n", devctl);
				tusb_musb_set_vbus(musb, 0);
			पूर्ण
			अवरोध;
		हाल OTG_STATE_A_WAIT_BCON:
			अगर (musb->a_रुको_bcon != 0)
				idle_समयout = jअगरfies
					+ msecs_to_jअगरfies(musb->a_रुको_bcon);
			अवरोध;
		हाल OTG_STATE_A_SUSPEND:
			अवरोध;
		हाल OTG_STATE_B_WAIT_ACON:
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	schedule_delayed_work(&musb->irq_work, 0);

	वापस idle_समयout;
पूर्ण

अटल irqवापस_t tusb_musb_पूर्णांकerrupt(पूर्णांक irq, व्योम *__hci)
अणु
	काष्ठा musb	*musb = __hci;
	व्योम __iomem	*tbase = musb->ctrl_base;
	अचिन्हित दीर्घ	flags, idle_समयout = 0;
	u32		पूर्णांक_mask, पूर्णांक_src;

	spin_lock_irqsave(&musb->lock, flags);

	/* Mask all पूर्णांकerrupts to allow using both edge and level GPIO irq */
	पूर्णांक_mask = musb_पढ़ोl(tbase, TUSB_INT_MASK);
	musb_ग_लिखोl(tbase, TUSB_INT_MASK, ~TUSB_INT_MASK_RESERVED_BITS);

	पूर्णांक_src = musb_पढ़ोl(tbase, TUSB_INT_SRC) & ~TUSB_INT_SRC_RESERVED_BITS;
	dev_dbg(musb->controller, "TUSB IRQ %08x\n", पूर्णांक_src);

	musb->पूर्णांक_usb = (u8) पूर्णांक_src;

	/* Acknowledge wake-up source पूर्णांकerrupts */
	अगर (पूर्णांक_src & TUSB_INT_SRC_DEV_WAKEUP) अणु
		u32	reg;
		u32	i;

		अगर (musb->tusb_revision == TUSB_REV_30)
			tusb_wbus_quirk(musb, 0);

		/* there are issues re-locking the PLL on wakeup ... */

		/* work around issue 8 */
		क्रम (i = 0xf7f7f7; i > 0xf7f7f7 - 1000; i--) अणु
			musb_ग_लिखोl(tbase, TUSB_SCRATCH_PAD, 0);
			musb_ग_लिखोl(tbase, TUSB_SCRATCH_PAD, i);
			reg = musb_पढ़ोl(tbase, TUSB_SCRATCH_PAD);
			अगर (reg == i)
				अवरोध;
			dev_dbg(musb->controller, "TUSB NOR not ready\n");
		पूर्ण

		/* work around issue 13 (2nd half) */
		tusb_set_घड़ी_source(musb, 1);

		reg = musb_पढ़ोl(tbase, TUSB_PRCM_WAKEUP_SOURCE);
		musb_ग_लिखोl(tbase, TUSB_PRCM_WAKEUP_CLEAR, reg);
		अगर (reg & ~TUSB_PRCM_WNORCS) अणु
			musb->is_active = 1;
			schedule_delayed_work(&musb->irq_work, 0);
		पूर्ण
		dev_dbg(musb->controller, "wake %sactive %02x\n",
				musb->is_active ? "" : "in", reg);

		/* REVISIT host side TUSB_PRCM_WHOSTDISCON, TUSB_PRCM_WBUS */
	पूर्ण

	अगर (पूर्णांक_src & TUSB_INT_SRC_USB_IP_CONN)
		del_समयr(&musb->dev_समयr);

	/* OTG state change reports (annoyingly) not issued by Mentor core */
	अगर (पूर्णांक_src & (TUSB_INT_SRC_VBUS_SENSE_CHNG
				| TUSB_INT_SRC_OTG_TIMEOUT
				| TUSB_INT_SRC_ID_STATUS_CHNG))
		idle_समयout = tusb_otg_पूर्णांकs(musb, पूर्णांक_src, tbase);

	/*
	 * Just clear the DMA पूर्णांकerrupt अगर it comes as the completion क्रम both
	 * TX and RX is handled by the DMA callback in tusb6010_omap
	 */
	अगर ((पूर्णांक_src & TUSB_INT_SRC_TXRX_DMA_DONE)) अणु
		u32	dma_src = musb_पढ़ोl(tbase, TUSB_DMA_INT_SRC);

		dev_dbg(musb->controller, "DMA IRQ %08x\n", dma_src);
		musb_ग_लिखोl(tbase, TUSB_DMA_INT_CLEAR, dma_src);
	पूर्ण

	/* EP पूर्णांकerrupts. In OCP mode tusb6010 mirrors the MUSB पूर्णांकerrupts */
	अगर (पूर्णांक_src & (TUSB_INT_SRC_USB_IP_TX | TUSB_INT_SRC_USB_IP_RX)) अणु
		u32	musb_src = musb_पढ़ोl(tbase, TUSB_USBIP_INT_SRC);

		musb_ग_लिखोl(tbase, TUSB_USBIP_INT_CLEAR, musb_src);
		musb->पूर्णांक_rx = (((musb_src >> 16) & 0xffff) << 1);
		musb->पूर्णांक_tx = (musb_src & 0xffff);
	पूर्ण अन्यथा अणु
		musb->पूर्णांक_rx = 0;
		musb->पूर्णांक_tx = 0;
	पूर्ण

	अगर (पूर्णांक_src & (TUSB_INT_SRC_USB_IP_TX | TUSB_INT_SRC_USB_IP_RX | 0xff))
		musb_पूर्णांकerrupt(musb);

	/* Acknowledge TUSB पूर्णांकerrupts. Clear only non-reserved bits */
	musb_ग_लिखोl(tbase, TUSB_INT_SRC_CLEAR,
		पूर्णांक_src & ~TUSB_INT_MASK_RESERVED_BITS);

	tusb_musb_try_idle(musb, idle_समयout);

	musb_ग_लिखोl(tbase, TUSB_INT_MASK, पूर्णांक_mask);
	spin_unlock_irqrestore(&musb->lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक dma_off;

/*
 * Enables TUSB6010. Caller must take care of locking.
 * REVISIT:
 * - Check what is unnecessary in MGC_HdrcStart()
 */
अटल व्योम tusb_musb_enable(काष्ठा musb *musb)
अणु
	व्योम __iomem	*tbase = musb->ctrl_base;

	/* Setup TUSB6010 मुख्य पूर्णांकerrupt mask. Enable all पूर्णांकerrupts except SOF.
	 * REVISIT: Enable and deal with TUSB_INT_SRC_USB_IP_SOF */
	musb_ग_लिखोl(tbase, TUSB_INT_MASK, TUSB_INT_SRC_USB_IP_SOF);

	/* Setup TUSB पूर्णांकerrupt, disable DMA and GPIO पूर्णांकerrupts */
	musb_ग_लिखोl(tbase, TUSB_USBIP_INT_MASK, 0);
	musb_ग_लिखोl(tbase, TUSB_DMA_INT_MASK, 0x7fffffff);
	musb_ग_लिखोl(tbase, TUSB_GPIO_INT_MASK, 0x1ff);

	/* Clear all subप्रणाली पूर्णांकerrups */
	musb_ग_लिखोl(tbase, TUSB_USBIP_INT_CLEAR, 0x7fffffff);
	musb_ग_लिखोl(tbase, TUSB_DMA_INT_CLEAR, 0x7fffffff);
	musb_ग_लिखोl(tbase, TUSB_GPIO_INT_CLEAR, 0x1ff);

	/* Acknowledge pending पूर्णांकerrupt(s) */
	musb_ग_लिखोl(tbase, TUSB_INT_SRC_CLEAR, ~TUSB_INT_MASK_RESERVED_BITS);

	/* Only 0 घड़ी cycles क्रम minimum पूर्णांकerrupt de-निश्चितion समय and
	 * पूर्णांकerrupt polarity active low seems to work reliably here */
	musb_ग_लिखोl(tbase, TUSB_INT_CTRL_CONF,
			TUSB_INT_CTRL_CONF_INT_RELCYC(0));

	irq_set_irq_type(musb->nIrq, IRQ_TYPE_LEVEL_LOW);

	/* maybe क्रमce पूर्णांकo the Default-A OTG state machine */
	अगर (!(musb_पढ़ोl(tbase, TUSB_DEV_OTG_STAT)
			& TUSB_DEV_OTG_STAT_ID_STATUS))
		musb_ग_लिखोl(tbase, TUSB_INT_SRC_SET,
				TUSB_INT_SRC_ID_STATUS_CHNG);

	अगर (is_dma_capable() && dma_off)
		prपूर्णांकk(KERN_WARNING "%s %s: dma not reactivated\n",
				__खाता__, __func__);
	अन्यथा
		dma_off = 1;
पूर्ण

/*
 * Disables TUSB6010. Caller must take care of locking.
 */
अटल व्योम tusb_musb_disable(काष्ठा musb *musb)
अणु
	व्योम __iomem	*tbase = musb->ctrl_base;

	/* FIXME stop DMA, IRQs, समयrs, ... */

	/* disable all IRQs */
	musb_ग_लिखोl(tbase, TUSB_INT_MASK, ~TUSB_INT_MASK_RESERVED_BITS);
	musb_ग_लिखोl(tbase, TUSB_USBIP_INT_MASK, 0x7fffffff);
	musb_ग_लिखोl(tbase, TUSB_DMA_INT_MASK, 0x7fffffff);
	musb_ग_लिखोl(tbase, TUSB_GPIO_INT_MASK, 0x1ff);

	del_समयr(&musb->dev_समयr);

	अगर (is_dma_capable() && !dma_off) अणु
		prपूर्णांकk(KERN_WARNING "%s %s: dma still active\n",
				__खाता__, __func__);
		dma_off = 1;
	पूर्ण
पूर्ण

/*
 * Sets up TUSB6010 CPU पूर्णांकerface specअगरic संकेतs and रेजिस्टरs
 * Note: Settings optimized क्रम OMAP24xx
 */
अटल व्योम tusb_setup_cpu_पूर्णांकerface(काष्ठा musb *musb)
अणु
	व्योम __iomem	*tbase = musb->ctrl_base;

	/*
	 * Disable GPIO[5:0] pullups (used as output DMA requests)
	 * Don't disable GPIO[7:6] as they are needed क्रम wake-up.
	 */
	musb_ग_लिखोl(tbase, TUSB_PULLUP_1_CTRL, 0x0000003F);

	/* Disable all pullups on NOR IF, DMAREQ0 and DMAREQ1 */
	musb_ग_लिखोl(tbase, TUSB_PULLUP_2_CTRL, 0x01FFFFFF);

	/* Turn GPIO[5:0] to DMAREQ[5:0] संकेतs */
	musb_ग_लिखोl(tbase, TUSB_GPIO_CONF, TUSB_GPIO_CONF_DMAREQ(0x3f));

	/* Burst size 16x16 bits, all six DMA requests enabled, DMA request
	 * de-निश्चितion समय 2 प्रणाली घड़ीs p 62 */
	musb_ग_लिखोl(tbase, TUSB_DMA_REQ_CONF,
		TUSB_DMA_REQ_CONF_BURST_SIZE(2) |
		TUSB_DMA_REQ_CONF_DMA_REQ_EN(0x3f) |
		TUSB_DMA_REQ_CONF_DMA_REQ_ASSER(2));

	/* Set 0 रुको count क्रम synchronous burst access */
	musb_ग_लिखोl(tbase, TUSB_WAIT_COUNT, 1);
पूर्ण

अटल पूर्णांक tusb_musb_start(काष्ठा musb *musb)
अणु
	व्योम __iomem	*tbase = musb->ctrl_base;
	पूर्णांक		ret = 0;
	अचिन्हित दीर्घ	flags;
	u32		reg;

	अगर (musb->board_set_घातer)
		ret = musb->board_set_घातer(1);
	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR "tusb: Cannot enable TUSB6010\n");
		वापस ret;
	पूर्ण

	spin_lock_irqsave(&musb->lock, flags);

	अगर (musb_पढ़ोl(tbase, TUSB_PROD_TEST_RESET) !=
		TUSB_PROD_TEST_RESET_VAL) अणु
		prपूर्णांकk(KERN_ERR "tusb: Unable to detect TUSB6010\n");
		जाओ err;
	पूर्ण

	musb->tusb_revision = tusb_get_revision(musb);
	tusb_prपूर्णांक_revision(musb);
	अगर (musb->tusb_revision < 2) अणु
		prपूर्णांकk(KERN_ERR "tusb: Unsupported TUSB6010 revision %i\n",
				musb->tusb_revision);
		जाओ err;
	पूर्ण

	/* The uपूर्णांक bit क्रम "USB non-PDR interrupt enable" has to be 1 when
	 * NOR FLASH पूर्णांकerface is used */
	musb_ग_लिखोl(tbase, TUSB_VLYNQ_CTRL, 8);

	/* Select PHY मुक्त running 60MHz as a प्रणाली घड़ी */
	tusb_set_घड़ी_source(musb, 1);

	/* VBus valid समयr 1us, disable DFT/Debug and VLYNQ घड़ीs क्रम
	 * घातer saving, enable VBus detect and session end comparators,
	 * enable IDpullup, enable VBus अक्षरging */
	musb_ग_लिखोl(tbase, TUSB_PRCM_MNGMT,
		TUSB_PRCM_MNGMT_VBUS_VALID_TIMER(0xa) |
		TUSB_PRCM_MNGMT_VBUS_VALID_FLT_EN |
		TUSB_PRCM_MNGMT_OTG_SESS_END_EN |
		TUSB_PRCM_MNGMT_OTG_VBUS_DET_EN |
		TUSB_PRCM_MNGMT_OTG_ID_PULLUP);
	tusb_setup_cpu_पूर्णांकerface(musb);

	/* simplअगरy:  always sense/pullup ID pins, as अगर in OTG mode */
	reg = musb_पढ़ोl(tbase, TUSB_PHY_OTG_CTRL_ENABLE);
	reg |= TUSB_PHY_OTG_CTRL_WRPROTECT | TUSB_PHY_OTG_CTRL_OTG_ID_PULLUP;
	musb_ग_लिखोl(tbase, TUSB_PHY_OTG_CTRL_ENABLE, reg);

	reg = musb_पढ़ोl(tbase, TUSB_PHY_OTG_CTRL);
	reg |= TUSB_PHY_OTG_CTRL_WRPROTECT | TUSB_PHY_OTG_CTRL_OTG_ID_PULLUP;
	musb_ग_लिखोl(tbase, TUSB_PHY_OTG_CTRL, reg);

	spin_unlock_irqrestore(&musb->lock, flags);

	वापस 0;

err:
	spin_unlock_irqrestore(&musb->lock, flags);

	अगर (musb->board_set_घातer)
		musb->board_set_घातer(0);

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक tusb_musb_init(काष्ठा musb *musb)
अणु
	काष्ठा platक्रमm_device	*pdev;
	काष्ठा resource		*mem;
	व्योम __iomem		*sync = शून्य;
	पूर्णांक			ret;

	musb->xceiv = usb_get_phy(USB_PHY_TYPE_USB2);
	अगर (IS_ERR_OR_शून्य(musb->xceiv))
		वापस -EPROBE_DEFER;

	pdev = to_platक्रमm_device(musb->controller);

	/* dma address क्रम async dma */
	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	musb->async = mem->start;

	/* dma address क्रम sync dma */
	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (!mem) अणु
		pr_debug("no sync dma resource?\n");
		ret = -ENODEV;
		जाओ करोne;
	पूर्ण
	musb->sync = mem->start;

	sync = ioremap(mem->start, resource_size(mem));
	अगर (!sync) अणु
		pr_debug("ioremap for sync failed\n");
		ret = -ENOMEM;
		जाओ करोne;
	पूर्ण
	musb->sync_va = sync;

	/* Offsets from base: VLYNQ at 0x000, MUSB regs at 0x400,
	 * FIFOs at 0x600, TUSB at 0x800
	 */
	musb->mregs += TUSB_BASE_OFFSET;

	ret = tusb_musb_start(musb);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "Could not start tusb6010 (%d)\n",
				ret);
		जाओ करोne;
	पूर्ण
	musb->isr = tusb_musb_पूर्णांकerrupt;

	musb->xceiv->set_घातer = tusb_draw_घातer;
	the_musb = musb;

	समयr_setup(&musb->dev_समयr, musb_करो_idle, 0);

करोne:
	अगर (ret < 0) अणु
		अगर (sync)
			iounmap(sync);

		usb_put_phy(musb->xceiv);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक tusb_musb_निकास(काष्ठा musb *musb)
अणु
	del_समयr_sync(&musb->dev_समयr);
	the_musb = शून्य;

	अगर (musb->board_set_घातer)
		musb->board_set_घातer(0);

	iounmap(musb->sync_va);

	usb_put_phy(musb->xceiv);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा musb_platक्रमm_ops tusb_ops = अणु
	.quirks		= MUSB_DMA_TUSB_OMAP | MUSB_IN_TUSB |
			  MUSB_G_NO_SKB_RESERVE,
	.init		= tusb_musb_init,
	.निकास		= tusb_musb_निकास,

	.ep_offset	= tusb_ep_offset,
	.ep_select	= tusb_ep_select,
	.fअगरo_offset	= tusb_fअगरo_offset,
	.पढ़ोb		= tusb_पढ़ोb,
	.ग_लिखोb		= tusb_ग_लिखोb,
	.पढ़ो_fअगरo	= tusb_पढ़ो_fअगरo,
	.ग_लिखो_fअगरo	= tusb_ग_लिखो_fअगरo,
#अगर_घोषित CONFIG_USB_TUSB_OMAP_DMA
	.dma_init	= tusb_dma_controller_create,
	.dma_निकास	= tusb_dma_controller_destroy,
#पूर्ण_अगर
	.enable		= tusb_musb_enable,
	.disable	= tusb_musb_disable,

	.set_mode	= tusb_musb_set_mode,
	.try_idle	= tusb_musb_try_idle,

	.vbus_status	= tusb_musb_vbus_status,
	.set_vbus	= tusb_musb_set_vbus,
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_info tusb_dev_info = अणु
	.name		= "musb-hdrc",
	.id		= PLATFORM_DEVID_AUTO,
	.dma_mask	= DMA_BIT_MASK(32),
पूर्ण;

अटल पूर्णांक tusb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource musb_resources[3];
	काष्ठा musb_hdrc_platक्रमm_data	*pdata = dev_get_platdata(&pdev->dev);
	काष्ठा platक्रमm_device		*musb;
	काष्ठा tusb6010_glue		*glue;
	काष्ठा platक्रमm_device_info	pinfo;
	पूर्णांक				ret;

	glue = devm_kzalloc(&pdev->dev, माप(*glue), GFP_KERNEL);
	अगर (!glue)
		वापस -ENOMEM;

	glue->dev			= &pdev->dev;

	pdata->platक्रमm_ops		= &tusb_ops;

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

	musb_resources[2].name = pdev->resource[2].name;
	musb_resources[2].start = pdev->resource[2].start;
	musb_resources[2].end = pdev->resource[2].end;
	musb_resources[2].flags = pdev->resource[2].flags;

	pinfo = tusb_dev_info;
	pinfo.parent = &pdev->dev;
	pinfo.res = musb_resources;
	pinfo.num_res = ARRAY_SIZE(musb_resources);
	pinfo.data = pdata;
	pinfo.size_data = माप(*pdata);

	glue->musb = musb = platक्रमm_device_रेजिस्टर_full(&pinfo);
	अगर (IS_ERR(musb)) अणु
		ret = PTR_ERR(musb);
		dev_err(&pdev->dev, "failed to register musb device: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tusb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tusb6010_glue		*glue = platक्रमm_get_drvdata(pdev);

	platक्रमm_device_unरेजिस्टर(glue->musb);
	usb_phy_generic_unरेजिस्टर(glue->phy);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver tusb_driver = अणु
	.probe		= tusb_probe,
	.हटाओ		= tusb_हटाओ,
	.driver		= अणु
		.name	= "musb-tusb",
	पूर्ण,
पूर्ण;

MODULE_DESCRIPTION("TUSB6010 MUSB Glue Layer");
MODULE_AUTHOR("Felipe Balbi <balbi@ti.com>");
MODULE_LICENSE("GPL v2");
module_platक्रमm_driver(tusb_driver);
