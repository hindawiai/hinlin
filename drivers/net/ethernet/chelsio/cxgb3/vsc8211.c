<शैली गुरु>
/*
 * Copyright (c) 2005-2008 Chelsio, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#समावेश "common.h"

/* VSC8211 PHY specअगरic रेजिस्टरs. */
क्रमागत अणु
	VSC8211_SIGDET_CTRL = 19,
	VSC8211_EXT_CTRL = 23,
	VSC8211_INTR_ENABLE = 25,
	VSC8211_INTR_STATUS = 26,
	VSC8211_LED_CTRL = 27,
	VSC8211_AUX_CTRL_STAT = 28,
	VSC8211_EXT_PAGE_AXS = 31,
पूर्ण;

क्रमागत अणु
	VSC_INTR_RX_ERR = 1 << 0,
	VSC_INTR_MS_ERR = 1 << 1,  /* master/slave resolution error */
	VSC_INTR_CABLE = 1 << 2,  /* cable impairment */
	VSC_INTR_FALSE_CARR = 1 << 3,  /* false carrier */
	VSC_INTR_MEDIA_CHG = 1 << 4,  /* AMS media change */
	VSC_INTR_RX_FIFO = 1 << 5,  /* Rx FIFO over/underflow */
	VSC_INTR_TX_FIFO = 1 << 6,  /* Tx FIFO over/underflow */
	VSC_INTR_DESCRAMBL = 1 << 7,  /* descrambler lock-lost */
	VSC_INTR_SYMBOL_ERR = 1 << 8,  /* symbol error */
	VSC_INTR_NEG_DONE = 1 << 10, /* स्वतःneg करोne */
	VSC_INTR_NEG_ERR = 1 << 11, /* स्वतःneg error */
	VSC_INTR_DPLX_CHG = 1 << 12, /* duplex change */
	VSC_INTR_LINK_CHG = 1 << 13, /* link change */
	VSC_INTR_SPD_CHG = 1 << 14, /* speed change */
	VSC_INTR_ENABLE = 1 << 15, /* पूर्णांकerrupt enable */
पूर्ण;

क्रमागत अणु
	VSC_CTRL_CLAUSE37_VIEW = 1 << 4,   /* Switch to Clause 37 view */
	VSC_CTRL_MEDIA_MODE_HI = 0xf000    /* High part of media mode select */
पूर्ण;

#घोषणा CFG_CHG_INTR_MASK (VSC_INTR_LINK_CHG | VSC_INTR_NEG_ERR | \
			   VSC_INTR_DPLX_CHG | VSC_INTR_SPD_CHG | \
	 		   VSC_INTR_NEG_DONE)
#घोषणा INTR_MASK (CFG_CHG_INTR_MASK | VSC_INTR_TX_FIFO | VSC_INTR_RX_FIFO | \
		   VSC_INTR_ENABLE)

/* PHY specअगरic auxiliary control & status रेजिस्टर fields */
#घोषणा S_ACSR_ACTIPHY_TMR    0
#घोषणा M_ACSR_ACTIPHY_TMR    0x3
#घोषणा V_ACSR_ACTIPHY_TMR(x) ((x) << S_ACSR_ACTIPHY_TMR)

#घोषणा S_ACSR_SPEED    3
#घोषणा M_ACSR_SPEED    0x3
#घोषणा G_ACSR_SPEED(x) (((x) >> S_ACSR_SPEED) & M_ACSR_SPEED)

#घोषणा S_ACSR_DUPLEX 5
#घोषणा F_ACSR_DUPLEX (1 << S_ACSR_DUPLEX)

#घोषणा S_ACSR_ACTIPHY 6
#घोषणा F_ACSR_ACTIPHY (1 << S_ACSR_ACTIPHY)

/*
 * Reset the PHY.  This PHY completes reset immediately so we never रुको.
 */
अटल पूर्णांक vsc8211_reset(काष्ठा cphy *cphy, पूर्णांक रुको)
अणु
	वापस t3_phy_reset(cphy, MDIO_DEVAD_NONE, 0);
पूर्ण

अटल पूर्णांक vsc8211_पूर्णांकr_enable(काष्ठा cphy *cphy)
अणु
	वापस t3_mdio_ग_लिखो(cphy, MDIO_DEVAD_NONE, VSC8211_INTR_ENABLE,
			     INTR_MASK);
पूर्ण

अटल पूर्णांक vsc8211_पूर्णांकr_disable(काष्ठा cphy *cphy)
अणु
	वापस t3_mdio_ग_लिखो(cphy, MDIO_DEVAD_NONE, VSC8211_INTR_ENABLE, 0);
पूर्ण

अटल पूर्णांक vsc8211_पूर्णांकr_clear(काष्ठा cphy *cphy)
अणु
	u32 val;

	/* Clear PHY पूर्णांकerrupts by पढ़ोing the रेजिस्टर. */
	वापस t3_mdio_पढ़ो(cphy, MDIO_DEVAD_NONE, VSC8211_INTR_STATUS, &val);
पूर्ण

अटल पूर्णांक vsc8211_स्वतःneg_enable(काष्ठा cphy *cphy)
अणु
	वापस t3_mdio_change_bits(cphy, MDIO_DEVAD_NONE, MII_BMCR,
				   BMCR_PDOWN | BMCR_ISOLATE,
				   BMCR_ANENABLE | BMCR_ANRESTART);
पूर्ण

अटल पूर्णांक vsc8211_स्वतःneg_restart(काष्ठा cphy *cphy)
अणु
	वापस t3_mdio_change_bits(cphy, MDIO_DEVAD_NONE, MII_BMCR,
				   BMCR_PDOWN | BMCR_ISOLATE,
				   BMCR_ANRESTART);
पूर्ण

अटल पूर्णांक vsc8211_get_link_status(काष्ठा cphy *cphy, पूर्णांक *link_ok,
				   पूर्णांक *speed, पूर्णांक *duplex, पूर्णांक *fc)
अणु
	अचिन्हित पूर्णांक bmcr, status, lpa, adv;
	पूर्णांक err, sp = -1, dplx = -1, छोड़ो = 0;

	err = t3_mdio_पढ़ो(cphy, MDIO_DEVAD_NONE, MII_BMCR, &bmcr);
	अगर (!err)
		err = t3_mdio_पढ़ो(cphy, MDIO_DEVAD_NONE, MII_BMSR, &status);
	अगर (err)
		वापस err;

	अगर (link_ok) अणु
		/*
		 * BMSR_LSTATUS is latch-low, so अगर it is 0 we need to पढ़ो it
		 * once more to get the current link state.
		 */
		अगर (!(status & BMSR_LSTATUS))
			err = t3_mdio_पढ़ो(cphy, MDIO_DEVAD_NONE, MII_BMSR,
					   &status);
		अगर (err)
			वापस err;
		*link_ok = (status & BMSR_LSTATUS) != 0;
	पूर्ण
	अगर (!(bmcr & BMCR_ANENABLE)) अणु
		dplx = (bmcr & BMCR_FULLDPLX) ? DUPLEX_FULL : DUPLEX_HALF;
		अगर (bmcr & BMCR_SPEED1000)
			sp = SPEED_1000;
		अन्यथा अगर (bmcr & BMCR_SPEED100)
			sp = SPEED_100;
		अन्यथा
			sp = SPEED_10;
	पूर्ण अन्यथा अगर (status & BMSR_ANEGCOMPLETE) अणु
		err = t3_mdio_पढ़ो(cphy, MDIO_DEVAD_NONE, VSC8211_AUX_CTRL_STAT,
				   &status);
		अगर (err)
			वापस err;

		dplx = (status & F_ACSR_DUPLEX) ? DUPLEX_FULL : DUPLEX_HALF;
		sp = G_ACSR_SPEED(status);
		अगर (sp == 0)
			sp = SPEED_10;
		अन्यथा अगर (sp == 1)
			sp = SPEED_100;
		अन्यथा
			sp = SPEED_1000;

		अगर (fc && dplx == DUPLEX_FULL) अणु
			err = t3_mdio_पढ़ो(cphy, MDIO_DEVAD_NONE, MII_LPA,
					   &lpa);
			अगर (!err)
				err = t3_mdio_पढ़ो(cphy, MDIO_DEVAD_NONE,
						   MII_ADVERTISE, &adv);
			अगर (err)
				वापस err;

			अगर (lpa & adv & ADVERTISE_PAUSE_CAP)
				छोड़ो = PAUSE_RX | PAUSE_TX;
			अन्यथा अगर ((lpa & ADVERTISE_PAUSE_CAP) &&
				 (lpa & ADVERTISE_PAUSE_ASYM) &&
				 (adv & ADVERTISE_PAUSE_ASYM))
				छोड़ो = PAUSE_TX;
			अन्यथा अगर ((lpa & ADVERTISE_PAUSE_ASYM) &&
				 (adv & ADVERTISE_PAUSE_CAP))
				छोड़ो = PAUSE_RX;
		पूर्ण
	पूर्ण
	अगर (speed)
		*speed = sp;
	अगर (duplex)
		*duplex = dplx;
	अगर (fc)
		*fc = छोड़ो;
	वापस 0;
पूर्ण

अटल पूर्णांक vsc8211_get_link_status_fiber(काष्ठा cphy *cphy, पूर्णांक *link_ok,
					 पूर्णांक *speed, पूर्णांक *duplex, पूर्णांक *fc)
अणु
	अचिन्हित पूर्णांक bmcr, status, lpa, adv;
	पूर्णांक err, sp = -1, dplx = -1, छोड़ो = 0;

	err = t3_mdio_पढ़ो(cphy, MDIO_DEVAD_NONE, MII_BMCR, &bmcr);
	अगर (!err)
		err = t3_mdio_पढ़ो(cphy, MDIO_DEVAD_NONE, MII_BMSR, &status);
	अगर (err)
		वापस err;

	अगर (link_ok) अणु
		/*
		 * BMSR_LSTATUS is latch-low, so अगर it is 0 we need to पढ़ो it
		 * once more to get the current link state.
		 */
		अगर (!(status & BMSR_LSTATUS))
			err = t3_mdio_पढ़ो(cphy, MDIO_DEVAD_NONE, MII_BMSR,
					   &status);
		अगर (err)
			वापस err;
		*link_ok = (status & BMSR_LSTATUS) != 0;
	पूर्ण
	अगर (!(bmcr & BMCR_ANENABLE)) अणु
		dplx = (bmcr & BMCR_FULLDPLX) ? DUPLEX_FULL : DUPLEX_HALF;
		अगर (bmcr & BMCR_SPEED1000)
			sp = SPEED_1000;
		अन्यथा अगर (bmcr & BMCR_SPEED100)
			sp = SPEED_100;
		अन्यथा
			sp = SPEED_10;
	पूर्ण अन्यथा अगर (status & BMSR_ANEGCOMPLETE) अणु
		err = t3_mdio_पढ़ो(cphy, MDIO_DEVAD_NONE, MII_LPA, &lpa);
		अगर (!err)
			err = t3_mdio_पढ़ो(cphy, MDIO_DEVAD_NONE, MII_ADVERTISE,
					   &adv);
		अगर (err)
			वापस err;

		अगर (adv & lpa & ADVERTISE_1000XFULL) अणु
			dplx = DUPLEX_FULL;
			sp = SPEED_1000;
		पूर्ण अन्यथा अगर (adv & lpa & ADVERTISE_1000XHALF) अणु
			dplx = DUPLEX_HALF;
			sp = SPEED_1000;
		पूर्ण

		अगर (fc && dplx == DUPLEX_FULL) अणु
			अगर (lpa & adv & ADVERTISE_1000XPAUSE)
				छोड़ो = PAUSE_RX | PAUSE_TX;
			अन्यथा अगर ((lpa & ADVERTISE_1000XPAUSE) &&
				 (adv & lpa & ADVERTISE_1000XPSE_ASYM))
				छोड़ो = PAUSE_TX;
			अन्यथा अगर ((lpa & ADVERTISE_1000XPSE_ASYM) &&
				 (adv & ADVERTISE_1000XPAUSE))
				छोड़ो = PAUSE_RX;
		पूर्ण
	पूर्ण
	अगर (speed)
		*speed = sp;
	अगर (duplex)
		*duplex = dplx;
	अगर (fc)
		*fc = छोड़ो;
	वापस 0;
पूर्ण

#अगर_घोषित UNUSED
/*
 * Enable/disable स्वतः MDI/MDI-X in क्रमced link speed mode.
 */
अटल पूर्णांक vsc8211_set_स्वतःmdi(काष्ठा cphy *phy, पूर्णांक enable)
अणु
	पूर्णांक err;

	err = t3_mdio_ग_लिखो(phy, MDIO_DEVAD_NONE, VSC8211_EXT_PAGE_AXS, 0x52b5);
	अगर (err)
		वापस err;

	err = t3_mdio_ग_लिखो(phy, MDIO_DEVAD_NONE, 18, 0x12);
	अगर (err)
		वापस err;

	err = t3_mdio_ग_लिखो(phy, MDIO_DEVAD_NONE, 17, enable ? 0x2803 : 0x3003);
	अगर (err)
		वापस err;

	err = t3_mdio_ग_लिखो(phy, MDIO_DEVAD_NONE, 16, 0x87fa);
	अगर (err)
		वापस err;

	err = t3_mdio_ग_लिखो(phy, MDIO_DEVAD_NONE, VSC8211_EXT_PAGE_AXS, 0);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

पूर्णांक vsc8211_set_speed_duplex(काष्ठा cphy *phy, पूर्णांक speed, पूर्णांक duplex)
अणु
	पूर्णांक err;

	err = t3_set_phy_speed_duplex(phy, speed, duplex);
	अगर (!err)
		err = vsc8211_set_स्वतःmdi(phy, 1);
	वापस err;
पूर्ण
#पूर्ण_अगर /* UNUSED */

अटल पूर्णांक vsc8211_घातer_करोwn(काष्ठा cphy *cphy, पूर्णांक enable)
अणु
	वापस t3_mdio_change_bits(cphy, 0, MII_BMCR, BMCR_PDOWN,
				   enable ? BMCR_PDOWN : 0);
पूर्ण

अटल पूर्णांक vsc8211_पूर्णांकr_handler(काष्ठा cphy *cphy)
अणु
	अचिन्हित पूर्णांक cause;
	पूर्णांक err, cphy_cause = 0;

	err = t3_mdio_पढ़ो(cphy, MDIO_DEVAD_NONE, VSC8211_INTR_STATUS, &cause);
	अगर (err)
		वापस err;

	cause &= INTR_MASK;
	अगर (cause & CFG_CHG_INTR_MASK)
		cphy_cause |= cphy_cause_link_change;
	अगर (cause & (VSC_INTR_RX_FIFO | VSC_INTR_TX_FIFO))
		cphy_cause |= cphy_cause_fअगरo_error;
	वापस cphy_cause;
पूर्ण

अटल स्थिर काष्ठा cphy_ops vsc8211_ops = अणु
	.reset = vsc8211_reset,
	.पूर्णांकr_enable = vsc8211_पूर्णांकr_enable,
	.पूर्णांकr_disable = vsc8211_पूर्णांकr_disable,
	.पूर्णांकr_clear = vsc8211_पूर्णांकr_clear,
	.पूर्णांकr_handler = vsc8211_पूर्णांकr_handler,
	.स्वतःneg_enable = vsc8211_स्वतःneg_enable,
	.स्वतःneg_restart = vsc8211_स्वतःneg_restart,
	.advertise = t3_phy_advertise,
	.set_speed_duplex = t3_set_phy_speed_duplex,
	.get_link_status = vsc8211_get_link_status,
	.घातer_करोwn = vsc8211_घातer_करोwn,
पूर्ण;

अटल स्थिर काष्ठा cphy_ops vsc8211_fiber_ops = अणु
	.reset = vsc8211_reset,
	.पूर्णांकr_enable = vsc8211_पूर्णांकr_enable,
	.पूर्णांकr_disable = vsc8211_पूर्णांकr_disable,
	.पूर्णांकr_clear = vsc8211_पूर्णांकr_clear,
	.पूर्णांकr_handler = vsc8211_पूर्णांकr_handler,
	.स्वतःneg_enable = vsc8211_स्वतःneg_enable,
	.स्वतःneg_restart = vsc8211_स्वतःneg_restart,
	.advertise = t3_phy_advertise_fiber,
	.set_speed_duplex = t3_set_phy_speed_duplex,
	.get_link_status = vsc8211_get_link_status_fiber,
	.घातer_करोwn = vsc8211_घातer_करोwn,
पूर्ण;

पूर्णांक t3_vsc8211_phy_prep(काष्ठा cphy *phy, काष्ठा adapter *adapter,
			पूर्णांक phy_addr, स्थिर काष्ठा mdio_ops *mdio_ops)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक val;

	cphy_init(phy, adapter, phy_addr, &vsc8211_ops, mdio_ops,
		  SUPPORTED_10baseT_Full | SUPPORTED_100baseT_Full |
		  SUPPORTED_1000baseT_Full | SUPPORTED_Autoneg | SUPPORTED_MII |
		  SUPPORTED_TP | SUPPORTED_IRQ, "10/100/1000BASE-T");
	msleep(20);       /* PHY needs ~10ms to start responding to MDIO */

	err = t3_mdio_पढ़ो(phy, MDIO_DEVAD_NONE, VSC8211_EXT_CTRL, &val);
	अगर (err)
		वापस err;
	अगर (val & VSC_CTRL_MEDIA_MODE_HI) अणु
		/* copper पूर्णांकerface, just need to configure the LEDs */
		वापस t3_mdio_ग_लिखो(phy, MDIO_DEVAD_NONE, VSC8211_LED_CTRL,
				     0x100);
	पूर्ण

	phy->caps = SUPPORTED_1000baseT_Full | SUPPORTED_Autoneg |
		    SUPPORTED_MII | SUPPORTED_FIBRE | SUPPORTED_IRQ;
	phy->desc = "1000BASE-X";
	phy->ops = &vsc8211_fiber_ops;

	err = t3_mdio_ग_लिखो(phy, MDIO_DEVAD_NONE, VSC8211_EXT_PAGE_AXS, 1);
	अगर (err)
		वापस err;

	err = t3_mdio_ग_लिखो(phy, MDIO_DEVAD_NONE, VSC8211_SIGDET_CTRL, 1);
	अगर (err)
		वापस err;

	err = t3_mdio_ग_लिखो(phy, MDIO_DEVAD_NONE, VSC8211_EXT_PAGE_AXS, 0);
	अगर (err)
		वापस err;

	err = t3_mdio_ग_लिखो(phy, MDIO_DEVAD_NONE, VSC8211_EXT_CTRL,
			    val | VSC_CTRL_CLAUSE37_VIEW);
	अगर (err)
		वापस err;

	err = vsc8211_reset(phy, 0);
	अगर (err)
		वापस err;

	udelay(5); /* delay after reset beक्रमe next SMI */
	वापस 0;
पूर्ण
