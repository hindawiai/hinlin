<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *	Driver क्रम Broadcom 63xx SOCs पूर्णांकegrated PHYs
 */
#समावेश "bcm-phy-lib.h"
#समावेश <linux/module.h>
#समावेश <linux/phy.h>

#घोषणा MII_BCM63XX_IR		0x1a	/* पूर्णांकerrupt रेजिस्टर */
#घोषणा MII_BCM63XX_IR_EN	0x4000	/* global पूर्णांकerrupt enable */
#घोषणा MII_BCM63XX_IR_DUPLEX	0x0800	/* duplex changed */
#घोषणा MII_BCM63XX_IR_SPEED	0x0400	/* speed changed */
#घोषणा MII_BCM63XX_IR_LINK	0x0200	/* link changed */
#घोषणा MII_BCM63XX_IR_GMASK	0x0100	/* global पूर्णांकerrupt mask */

MODULE_DESCRIPTION("Broadcom 63xx internal PHY driver");
MODULE_AUTHOR("Maxime Bizon <mbizon@freebox.fr>");
MODULE_LICENSE("GPL");

अटल पूर्णांक bcm63xx_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	पूर्णांक reg, err;

	reg = phy_पढ़ो(phydev, MII_BCM63XX_IR);
	अगर (reg < 0)
		वापस reg;

	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED) अणु
		err = bcm_phy_ack_पूर्णांकr(phydev);
		अगर (err)
			वापस err;

		reg &= ~MII_BCM63XX_IR_GMASK;
		err = phy_ग_लिखो(phydev, MII_BCM63XX_IR, reg);
	पूर्ण अन्यथा अणु
		reg |= MII_BCM63XX_IR_GMASK;
		err = phy_ग_लिखो(phydev, MII_BCM63XX_IR, reg);
		अगर (err)
			वापस err;

		err = bcm_phy_ack_पूर्णांकr(phydev);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक bcm63xx_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक reg, err;

	/* ASYM_PAUSE bit is marked RO in datasheet, so करोn't cheat */
	linkmode_set_bit(ETHTOOL_LINK_MODE_Pause_BIT, phydev->supported);

	reg = phy_पढ़ो(phydev, MII_BCM63XX_IR);
	अगर (reg < 0)
		वापस reg;

	/* Mask पूर्णांकerrupts globally.  */
	reg |= MII_BCM63XX_IR_GMASK;
	err = phy_ग_लिखो(phydev, MII_BCM63XX_IR, reg);
	अगर (err < 0)
		वापस err;

	/* Unmask events we are पूर्णांकerested in  */
	reg = ~(MII_BCM63XX_IR_DUPLEX |
		MII_BCM63XX_IR_SPEED |
		MII_BCM63XX_IR_LINK) |
		MII_BCM63XX_IR_EN;
	वापस phy_ग_लिखो(phydev, MII_BCM63XX_IR, reg);
पूर्ण

अटल काष्ठा phy_driver bcm63xx_driver[] = अणु
अणु
	.phy_id		= 0x00406000,
	.phy_id_mask	= 0xfffffc00,
	.name		= "Broadcom BCM63XX (1)",
	/* PHY_BASIC_FEATURES */
	.flags		= PHY_IS_INTERNAL,
	.config_init	= bcm63xx_config_init,
	.config_पूर्णांकr	= bcm63xx_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = bcm_phy_handle_पूर्णांकerrupt,
पूर्ण, अणु
	/* same phy as above, with just a dअगरferent OUI */
	.phy_id		= 0x002bdc00,
	.phy_id_mask	= 0xfffffc00,
	.name		= "Broadcom BCM63XX (2)",
	/* PHY_BASIC_FEATURES */
	.flags		= PHY_IS_INTERNAL,
	.config_init	= bcm63xx_config_init,
	.config_पूर्णांकr	= bcm63xx_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = bcm_phy_handle_पूर्णांकerrupt,
पूर्ण पूर्ण;

module_phy_driver(bcm63xx_driver);

अटल काष्ठा mdio_device_id __maybe_unused bcm63xx_tbl[] = अणु
	अणु 0x00406000, 0xfffffc00 पूर्ण,
	अणु 0x002bdc00, 0xfffffc00 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(mdio, bcm63xx_tbl);
