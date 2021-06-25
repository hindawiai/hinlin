<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम Vitesse PHYs
 *
 * Author: Kriston Carson
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mii.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/phy.h>

/* Vitesse Extended Page Magic Register(s) */
#घोषणा MII_VSC82X4_EXT_PAGE_16E	0x10
#घोषणा MII_VSC82X4_EXT_PAGE_17E	0x11
#घोषणा MII_VSC82X4_EXT_PAGE_18E	0x12

/* Vitesse Extended Control Register 1 */
#घोषणा MII_VSC8244_EXT_CON1           0x17
#घोषणा MII_VSC8244_EXTCON1_INIT       0x0000
#घोषणा MII_VSC8244_EXTCON1_TX_SKEW_MASK	0x0c00
#घोषणा MII_VSC8244_EXTCON1_RX_SKEW_MASK	0x0300
#घोषणा MII_VSC8244_EXTCON1_TX_SKEW	0x0800
#घोषणा MII_VSC8244_EXTCON1_RX_SKEW	0x0200

/* Vitesse Interrupt Mask Register */
#घोषणा MII_VSC8244_IMASK		0x19
#घोषणा MII_VSC8244_IMASK_IEN		0x8000
#घोषणा MII_VSC8244_IMASK_SPEED		0x4000
#घोषणा MII_VSC8244_IMASK_LINK		0x2000
#घोषणा MII_VSC8244_IMASK_DUPLEX	0x1000
#घोषणा MII_VSC8244_IMASK_MASK		0xf000

#घोषणा MII_VSC8221_IMASK_MASK		0xa000

/* Vitesse Interrupt Status Register */
#घोषणा MII_VSC8244_ISTAT		0x1a
#घोषणा MII_VSC8244_ISTAT_STATUS	0x8000
#घोषणा MII_VSC8244_ISTAT_SPEED		0x4000
#घोषणा MII_VSC8244_ISTAT_LINK		0x2000
#घोषणा MII_VSC8244_ISTAT_DUPLEX	0x1000
#घोषणा MII_VSC8244_ISTAT_MASK		(MII_VSC8244_ISTAT_SPEED | \
					 MII_VSC8244_ISTAT_LINK | \
					 MII_VSC8244_ISTAT_DUPLEX)

#घोषणा MII_VSC8221_ISTAT_MASK		MII_VSC8244_ISTAT_LINK

/* Vitesse Auxiliary Control/Status Register */
#घोषणा MII_VSC8244_AUX_CONSTAT		0x1c
#घोषणा MII_VSC8244_AUXCONSTAT_INIT	0x0000
#घोषणा MII_VSC8244_AUXCONSTAT_DUPLEX	0x0020
#घोषणा MII_VSC8244_AUXCONSTAT_SPEED	0x0018
#घोषणा MII_VSC8244_AUXCONSTAT_GBIT	0x0010
#घोषणा MII_VSC8244_AUXCONSTAT_100	0x0008

#घोषणा MII_VSC8221_AUXCONSTAT_INIT	0x0004 /* need to set this bit? */
#घोषणा MII_VSC8221_AUXCONSTAT_RESERVED	0x0004

/* Vitesse Extended Page Access Register */
#घोषणा MII_VSC82X4_EXT_PAGE_ACCESS	0x1f

/* Vitesse VSC8601 Extended PHY Control Register 1 */
#घोषणा MII_VSC8601_EPHY_CTL		0x17
#घोषणा MII_VSC8601_EPHY_CTL_RGMII_SKEW	(1 << 8)

#घोषणा PHY_ID_VSC8234			0x000fc620
#घोषणा PHY_ID_VSC8244			0x000fc6c0
#घोषणा PHY_ID_VSC8572			0x000704d0
#घोषणा PHY_ID_VSC8601			0x00070420
#घोषणा PHY_ID_VSC7385			0x00070450
#घोषणा PHY_ID_VSC7388			0x00070480
#घोषणा PHY_ID_VSC7395			0x00070550
#घोषणा PHY_ID_VSC7398			0x00070580
#घोषणा PHY_ID_VSC8662			0x00070660
#घोषणा PHY_ID_VSC8221			0x000fc550
#घोषणा PHY_ID_VSC8211			0x000fc4b0

MODULE_DESCRIPTION("Vitesse PHY driver");
MODULE_AUTHOR("Kriston Carson");
MODULE_LICENSE("GPL");

अटल पूर्णांक vsc824x_add_skew(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;
	पूर्णांक extcon;

	extcon = phy_पढ़ो(phydev, MII_VSC8244_EXT_CON1);

	अगर (extcon < 0)
		वापस extcon;

	extcon &= ~(MII_VSC8244_EXTCON1_TX_SKEW_MASK |
			MII_VSC8244_EXTCON1_RX_SKEW_MASK);

	extcon |= (MII_VSC8244_EXTCON1_TX_SKEW |
			MII_VSC8244_EXTCON1_RX_SKEW);

	err = phy_ग_लिखो(phydev, MII_VSC8244_EXT_CON1, extcon);

	वापस err;
पूर्ण

अटल पूर्णांक vsc824x_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	err = phy_ग_लिखो(phydev, MII_VSC8244_AUX_CONSTAT,
			MII_VSC8244_AUXCONSTAT_INIT);
	अगर (err < 0)
		वापस err;

	अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_ID)
		err = vsc824x_add_skew(phydev);

	वापस err;
पूर्ण

#घोषणा VSC73XX_EXT_PAGE_ACCESS 0x1f

अटल पूर्णांक vsc73xx_पढ़ो_page(काष्ठा phy_device *phydev)
अणु
	वापस __phy_पढ़ो(phydev, VSC73XX_EXT_PAGE_ACCESS);
पूर्ण

अटल पूर्णांक vsc73xx_ग_लिखो_page(काष्ठा phy_device *phydev, पूर्णांक page)
अणु
	वापस __phy_ग_लिखो(phydev, VSC73XX_EXT_PAGE_ACCESS, page);
पूर्ण

अटल व्योम vsc73xx_config_init(काष्ठा phy_device *phydev)
अणु
	/* Receiver init */
	phy_ग_लिखो(phydev, 0x1f, 0x2a30);
	phy_modअगरy(phydev, 0x0c, 0x0300, 0x0200);
	phy_ग_लिखो(phydev, 0x1f, 0x0000);

	/* Config LEDs 0x61 */
	phy_modअगरy(phydev, MII_TPISTATUS, 0xff00, 0x0061);
पूर्ण

अटल पूर्णांक vsc738x_config_init(काष्ठा phy_device *phydev)
अणु
	u16 rev;
	/* This magic sequence appear in the application note
	 * "VSC7385/7388 PHY Configuration".
	 *
	 * Maybe one day we will get to know what it all means.
	 */
	phy_ग_लिखो(phydev, 0x1f, 0x2a30);
	phy_modअगरy(phydev, 0x08, 0x0200, 0x0200);
	phy_ग_लिखो(phydev, 0x1f, 0x52b5);
	phy_ग_लिखो(phydev, 0x10, 0xb68a);
	phy_modअगरy(phydev, 0x12, 0xff07, 0x0003);
	phy_modअगरy(phydev, 0x11, 0x00ff, 0x00a2);
	phy_ग_लिखो(phydev, 0x10, 0x968a);
	phy_ग_लिखो(phydev, 0x1f, 0x2a30);
	phy_modअगरy(phydev, 0x08, 0x0200, 0x0000);
	phy_ग_लिखो(phydev, 0x1f, 0x0000);

	/* Read revision */
	rev = phy_पढ़ो(phydev, MII_PHYSID2);
	rev &= 0x0f;

	/* Special quirk क्रम revision 0 */
	अगर (rev == 0) अणु
		phy_ग_लिखो(phydev, 0x1f, 0x2a30);
		phy_modअगरy(phydev, 0x08, 0x0200, 0x0200);
		phy_ग_लिखो(phydev, 0x1f, 0x52b5);
		phy_ग_लिखो(phydev, 0x12, 0x0000);
		phy_ग_लिखो(phydev, 0x11, 0x0689);
		phy_ग_लिखो(phydev, 0x10, 0x8f92);
		phy_ग_लिखो(phydev, 0x1f, 0x52b5);
		phy_ग_लिखो(phydev, 0x12, 0x0000);
		phy_ग_लिखो(phydev, 0x11, 0x0e35);
		phy_ग_लिखो(phydev, 0x10, 0x9786);
		phy_ग_लिखो(phydev, 0x1f, 0x2a30);
		phy_modअगरy(phydev, 0x08, 0x0200, 0x0000);
		phy_ग_लिखो(phydev, 0x17, 0xff80);
		phy_ग_लिखो(phydev, 0x17, 0x0000);
	पूर्ण

	phy_ग_लिखो(phydev, 0x1f, 0x0000);
	phy_ग_लिखो(phydev, 0x12, 0x0048);

	अगर (rev == 0) अणु
		phy_ग_लिखो(phydev, 0x1f, 0x2a30);
		phy_ग_लिखो(phydev, 0x14, 0x6600);
		phy_ग_लिखो(phydev, 0x1f, 0x0000);
		phy_ग_लिखो(phydev, 0x18, 0xa24e);
	पूर्ण अन्यथा अणु
		phy_ग_लिखो(phydev, 0x1f, 0x2a30);
		phy_modअगरy(phydev, 0x16, 0x0fc0, 0x0240);
		phy_modअगरy(phydev, 0x14, 0x6000, 0x4000);
		/* bits 14-15 in extended रेजिस्टर 0x14 controls DACG amplitude
		 * 6 = -8%, 2 is hardware शेष
		 */
		phy_ग_लिखो(phydev, 0x1f, 0x0001);
		phy_modअगरy(phydev, 0x14, 0xe000, 0x6000);
		phy_ग_लिखो(phydev, 0x1f, 0x0000);
	पूर्ण

	vsc73xx_config_init(phydev);

	वापस 0;
पूर्ण

अटल पूर्णांक vsc739x_config_init(काष्ठा phy_device *phydev)
अणु
	/* This magic sequence appears in the VSC7395 SparX-G5e application
	 * note "VSC7395/VSC7398 PHY Configuration"
	 *
	 * Maybe one day we will get to know what it all means.
	 */
	phy_ग_लिखो(phydev, 0x1f, 0x2a30);
	phy_modअगरy(phydev, 0x08, 0x0200, 0x0200);
	phy_ग_लिखो(phydev, 0x1f, 0x52b5);
	phy_ग_लिखो(phydev, 0x10, 0xb68a);
	phy_modअगरy(phydev, 0x12, 0xff07, 0x0003);
	phy_modअगरy(phydev, 0x11, 0x00ff, 0x00a2);
	phy_ग_लिखो(phydev, 0x10, 0x968a);
	phy_ग_लिखो(phydev, 0x1f, 0x2a30);
	phy_modअगरy(phydev, 0x08, 0x0200, 0x0000);
	phy_ग_लिखो(phydev, 0x1f, 0x0000);

	phy_ग_लिखो(phydev, 0x1f, 0x0000);
	phy_ग_लिखो(phydev, 0x12, 0x0048);
	phy_ग_लिखो(phydev, 0x1f, 0x2a30);
	phy_modअगरy(phydev, 0x16, 0x0fc0, 0x0240);
	phy_modअगरy(phydev, 0x14, 0x6000, 0x4000);
	phy_ग_लिखो(phydev, 0x1f, 0x0001);
	phy_modअगरy(phydev, 0x14, 0xe000, 0x6000);
	phy_ग_लिखो(phydev, 0x1f, 0x0000);

	vsc73xx_config_init(phydev);

	वापस 0;
पूर्ण

अटल पूर्णांक vsc73xx_config_aneg(काष्ठा phy_device *phydev)
अणु
	/* The VSC73xx चयनes करोes not like to be inकाष्ठाed to
	 * करो स्वतःnegotiation in any way, it prefers that you just go
	 * with the घातer-on/reset शेषs. Writing some रेजिस्टरs will
	 * just make स्वतःnegotiation permanently fail.
	 */
	वापस 0;
पूर्ण

/* This adds a skew क्रम both TX and RX घड़ीs, so the skew should only be
 * applied to "rgmii-id" पूर्णांकerfaces. It may not work as expected
 * on "rgmii-txid", "rgmii-rxid" or "rgmii" पूर्णांकerfaces. */
अटल पूर्णांक vsc8601_add_skew(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	ret = phy_पढ़ो(phydev, MII_VSC8601_EPHY_CTL);
	अगर (ret < 0)
		वापस ret;

	ret |= MII_VSC8601_EPHY_CTL_RGMII_SKEW;
	वापस phy_ग_लिखो(phydev, MII_VSC8601_EPHY_CTL, ret);
पूर्ण

अटल पूर्णांक vsc8601_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret = 0;

	अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_ID)
		ret = vsc8601_add_skew(phydev);

	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक vsc82xx_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED)
		/* Don't bother to ACK the पूर्णांकerrupts since the 824x cannot
		 * clear the पूर्णांकerrupts अगर they are disabled.
		 */
		err = phy_ग_लिखो(phydev, MII_VSC8244_IMASK,
			(phydev->drv->phy_id == PHY_ID_VSC8234 ||
			 phydev->drv->phy_id == PHY_ID_VSC8244 ||
			 phydev->drv->phy_id == PHY_ID_VSC8572 ||
			 phydev->drv->phy_id == PHY_ID_VSC8601) ?
				MII_VSC8244_IMASK_MASK :
				MII_VSC8221_IMASK_MASK);
	अन्यथा अणु
		/* The Vitesse PHY cannot clear the पूर्णांकerrupt
		 * once it has disabled them, so we clear them first
		 */
		err = phy_पढ़ो(phydev, MII_VSC8244_ISTAT);

		अगर (err < 0)
			वापस err;

		err = phy_ग_लिखो(phydev, MII_VSC8244_IMASK, 0);
	पूर्ण

	वापस err;
पूर्ण

अटल irqवापस_t vsc82xx_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक irq_status, irq_mask;

	अगर (phydev->drv->phy_id == PHY_ID_VSC8244 ||
	    phydev->drv->phy_id == PHY_ID_VSC8572 ||
	    phydev->drv->phy_id == PHY_ID_VSC8601)
		irq_mask = MII_VSC8244_ISTAT_MASK;
	अन्यथा
		irq_mask = MII_VSC8221_ISTAT_MASK;

	irq_status = phy_पढ़ो(phydev, MII_VSC8244_ISTAT);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	अगर (!(irq_status & irq_mask))
		वापस IRQ_NONE;

	phy_trigger_machine(phydev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक vsc8221_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	err = phy_ग_लिखो(phydev, MII_VSC8244_AUX_CONSTAT,
			MII_VSC8221_AUXCONSTAT_INIT);
	वापस err;

	/* Perhaps we should set EXT_CON1 based on the पूर्णांकerface?
	 * Options are 802.3Z SerDes or SGMII
	 */
पूर्ण

/* vsc82x4_config_स्वतःcross_enable - Enable स्वतः MDI/MDI-X क्रम क्रमced links
 * @phydev: target phy_device काष्ठा
 *
 * Enable स्वतः MDI/MDI-X when in 10/100 क्रमced link speeds by writing
 * special values in the VSC8234/VSC8244 extended reserved रेजिस्टरs
 */
अटल पूर्णांक vsc82x4_config_स्वतःcross_enable(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	अगर (phydev->स्वतःneg == AUTONEG_ENABLE || phydev->speed > SPEED_100)
		वापस 0;

	/* map extended रेजिस्टरs set 0x10 - 0x1e */
	ret = phy_ग_लिखो(phydev, MII_VSC82X4_EXT_PAGE_ACCESS, 0x52b5);
	अगर (ret >= 0)
		ret = phy_ग_लिखो(phydev, MII_VSC82X4_EXT_PAGE_18E, 0x0012);
	अगर (ret >= 0)
		ret = phy_ग_लिखो(phydev, MII_VSC82X4_EXT_PAGE_17E, 0x2803);
	अगर (ret >= 0)
		ret = phy_ग_लिखो(phydev, MII_VSC82X4_EXT_PAGE_16E, 0x87fa);
	/* map standard रेजिस्टरs set 0x10 - 0x1e */
	अगर (ret >= 0)
		ret = phy_ग_लिखो(phydev, MII_VSC82X4_EXT_PAGE_ACCESS, 0x0000);
	अन्यथा
		phy_ग_लिखो(phydev, MII_VSC82X4_EXT_PAGE_ACCESS, 0x0000);

	वापस ret;
पूर्ण

/* vsc82x4_config_aneg - restart स्वतः-negotiation or ग_लिखो BMCR
 * @phydev: target phy_device काष्ठा
 *
 * Description: If स्वतः-negotiation is enabled, we configure the
 *   advertising, and then restart स्वतः-negotiation.  If it is not
 *   enabled, then we ग_लिखो the BMCR and also start the स्वतः
 *   MDI/MDI-X feature
 */
अटल पूर्णांक vsc82x4_config_aneg(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	/* Enable स्वतः MDI/MDI-X when in 10/100 क्रमced link speeds by
	 * writing special values in the VSC8234 extended reserved रेजिस्टरs
	 */
	अगर (phydev->स्वतःneg != AUTONEG_ENABLE && phydev->speed <= SPEED_100) अणु
		ret = genphy_setup_क्रमced(phydev);

		अगर (ret < 0) /* error */
			वापस ret;

		वापस vsc82x4_config_स्वतःcross_enable(phydev);
	पूर्ण

	वापस genphy_config_aneg(phydev);
पूर्ण

/* Vitesse 82xx */
अटल काष्ठा phy_driver vsc82xx_driver[] = अणु
अणु
	.phy_id         = PHY_ID_VSC8234,
	.name           = "Vitesse VSC8234",
	.phy_id_mask    = 0x000ffff0,
	/* PHY_GBIT_FEATURES */
	.config_init    = &vsc824x_config_init,
	.config_aneg    = &vsc82x4_config_aneg,
	.config_पूर्णांकr    = &vsc82xx_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = &vsc82xx_handle_पूर्णांकerrupt,
पूर्ण, अणु
	.phy_id		= PHY_ID_VSC8244,
	.name		= "Vitesse VSC8244",
	.phy_id_mask	= 0x000fffc0,
	/* PHY_GBIT_FEATURES */
	.config_init	= &vsc824x_config_init,
	.config_aneg	= &vsc82x4_config_aneg,
	.config_पूर्णांकr	= &vsc82xx_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = &vsc82xx_handle_पूर्णांकerrupt,
पूर्ण, अणु
	.phy_id         = PHY_ID_VSC8572,
	.name           = "Vitesse VSC8572",
	.phy_id_mask    = 0x000ffff0,
	/* PHY_GBIT_FEATURES */
	.config_init    = &vsc824x_config_init,
	.config_aneg    = &vsc82x4_config_aneg,
	.config_पूर्णांकr    = &vsc82xx_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = &vsc82xx_handle_पूर्णांकerrupt,
पूर्ण, अणु
	.phy_id         = PHY_ID_VSC8601,
	.name           = "Vitesse VSC8601",
	.phy_id_mask    = 0x000ffff0,
	/* PHY_GBIT_FEATURES */
	.config_init    = &vsc8601_config_init,
	.config_पूर्णांकr    = &vsc82xx_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = &vsc82xx_handle_पूर्णांकerrupt,
पूर्ण, अणु
	.phy_id         = PHY_ID_VSC7385,
	.name           = "Vitesse VSC7385",
	.phy_id_mask    = 0x000ffff0,
	/* PHY_GBIT_FEATURES */
	.config_init    = vsc738x_config_init,
	.config_aneg    = vsc73xx_config_aneg,
	.पढ़ो_page      = vsc73xx_पढ़ो_page,
	.ग_लिखो_page     = vsc73xx_ग_लिखो_page,
पूर्ण, अणु
	.phy_id         = PHY_ID_VSC7388,
	.name           = "Vitesse VSC7388",
	.phy_id_mask    = 0x000ffff0,
	/* PHY_GBIT_FEATURES */
	.config_init    = vsc738x_config_init,
	.config_aneg    = vsc73xx_config_aneg,
	.पढ़ो_page      = vsc73xx_पढ़ो_page,
	.ग_लिखो_page     = vsc73xx_ग_लिखो_page,
पूर्ण, अणु
	.phy_id         = PHY_ID_VSC7395,
	.name           = "Vitesse VSC7395",
	.phy_id_mask    = 0x000ffff0,
	/* PHY_GBIT_FEATURES */
	.config_init    = vsc739x_config_init,
	.config_aneg    = vsc73xx_config_aneg,
	.पढ़ो_page      = vsc73xx_पढ़ो_page,
	.ग_लिखो_page     = vsc73xx_ग_लिखो_page,
पूर्ण, अणु
	.phy_id         = PHY_ID_VSC7398,
	.name           = "Vitesse VSC7398",
	.phy_id_mask    = 0x000ffff0,
	/* PHY_GBIT_FEATURES */
	.config_init    = vsc739x_config_init,
	.config_aneg    = vsc73xx_config_aneg,
	.पढ़ो_page      = vsc73xx_पढ़ो_page,
	.ग_लिखो_page     = vsc73xx_ग_लिखो_page,
पूर्ण, अणु
	.phy_id         = PHY_ID_VSC8662,
	.name           = "Vitesse VSC8662",
	.phy_id_mask    = 0x000ffff0,
	/* PHY_GBIT_FEATURES */
	.config_init    = &vsc824x_config_init,
	.config_aneg    = &vsc82x4_config_aneg,
	.config_पूर्णांकr    = &vsc82xx_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = &vsc82xx_handle_पूर्णांकerrupt,
पूर्ण, अणु
	/* Vitesse 8221 */
	.phy_id		= PHY_ID_VSC8221,
	.phy_id_mask	= 0x000ffff0,
	.name		= "Vitesse VSC8221",
	/* PHY_GBIT_FEATURES */
	.config_init	= &vsc8221_config_init,
	.config_पूर्णांकr	= &vsc82xx_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = &vsc82xx_handle_पूर्णांकerrupt,
पूर्ण, अणु
	/* Vitesse 8211 */
	.phy_id		= PHY_ID_VSC8211,
	.phy_id_mask	= 0x000ffff0,
	.name		= "Vitesse VSC8211",
	/* PHY_GBIT_FEATURES */
	.config_init	= &vsc8221_config_init,
	.config_पूर्णांकr	= &vsc82xx_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = &vsc82xx_handle_पूर्णांकerrupt,
पूर्ण पूर्ण;

module_phy_driver(vsc82xx_driver);

अटल काष्ठा mdio_device_id __maybe_unused vitesse_tbl[] = अणु
	अणु PHY_ID_VSC8234, 0x000ffff0 पूर्ण,
	अणु PHY_ID_VSC8244, 0x000fffc0 पूर्ण,
	अणु PHY_ID_VSC8572, 0x000ffff0 पूर्ण,
	अणु PHY_ID_VSC7385, 0x000ffff0 पूर्ण,
	अणु PHY_ID_VSC7388, 0x000ffff0 पूर्ण,
	अणु PHY_ID_VSC7395, 0x000ffff0 पूर्ण,
	अणु PHY_ID_VSC7398, 0x000ffff0 पूर्ण,
	अणु PHY_ID_VSC8662, 0x000ffff0 पूर्ण,
	अणु PHY_ID_VSC8221, 0x000ffff0 पूर्ण,
	अणु PHY_ID_VSC8211, 0x000ffff0 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(mdio, vitesse_tbl);
