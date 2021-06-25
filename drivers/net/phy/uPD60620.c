<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम the Renesas PHY uPD60620.
 *
 * Copyright (C) 2015 Softing Industrial Automation GmbH
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/phy.h>

#घोषणा UPD60620_PHY_ID    0xb8242824

/* Extended Registers and values */
/* PHY Special Control/Status    */
#घोषणा PHY_PHYSCR         0x1F      /* PHY.31 */
#घोषणा PHY_PHYSCR_10MB    0x0004    /* PHY speed = 10mb */
#घोषणा PHY_PHYSCR_100MB   0x0008    /* PHY speed = 100mb */
#घोषणा PHY_PHYSCR_DUPLEX  0x0010    /* PHY Duplex */

/* PHY Special Modes */
#घोषणा PHY_SPM            0x12      /* PHY.18 */

/* Init PHY */

अटल पूर्णांक upd60620_config_init(काष्ठा phy_device *phydev)
अणु
	/* Enable support क्रम passive HUBs (could be a strap option) */
	/* PHYMODE: All speeds, HD in parallel detect */
	वापस phy_ग_लिखो(phydev, PHY_SPM, 0x0180 | phydev->mdio.addr);
पूर्ण

/* Get PHY status from common रेजिस्टरs */

अटल पूर्णांक upd60620_पढ़ो_status(काष्ठा phy_device *phydev)
अणु
	पूर्णांक phy_state;

	/* Read negotiated state */
	phy_state = phy_पढ़ो(phydev, MII_BMSR);
	अगर (phy_state < 0)
		वापस phy_state;

	phydev->link = 0;
	linkmode_zero(phydev->lp_advertising);
	phydev->छोड़ो = 0;
	phydev->asym_छोड़ो = 0;

	अगर (phy_state & (BMSR_ANEGCOMPLETE | BMSR_LSTATUS)) अणु
		phy_state = phy_पढ़ो(phydev, PHY_PHYSCR);
		अगर (phy_state < 0)
			वापस phy_state;

		अगर (phy_state & (PHY_PHYSCR_10MB | PHY_PHYSCR_100MB)) अणु
			phydev->link = 1;
			phydev->speed = SPEED_10;
			phydev->duplex = DUPLEX_HALF;

			अगर (phy_state & PHY_PHYSCR_100MB)
				phydev->speed = SPEED_100;
			अगर (phy_state & PHY_PHYSCR_DUPLEX)
				phydev->duplex = DUPLEX_FULL;

			phy_state = phy_पढ़ो(phydev, MII_LPA);
			अगर (phy_state < 0)
				वापस phy_state;

			mii_lpa_to_linkmode_lpa_t(phydev->lp_advertising,
						  phy_state);

			phy_resolve_aneg_छोड़ो(phydev);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

MODULE_DESCRIPTION("Renesas uPD60620 PHY driver");
MODULE_AUTHOR("Bernd Edlinger <bernd.edlinger@hotmail.de>");
MODULE_LICENSE("GPL");

अटल काष्ठा phy_driver upd60620_driver[1] = अणु अणु
	.phy_id         = UPD60620_PHY_ID,
	.phy_id_mask    = 0xfffffffe,
	.name           = "Renesas uPD60620",
	/* PHY_BASIC_FEATURES */
	.flags          = 0,
	.config_init    = upd60620_config_init,
	.पढ़ो_status    = upd60620_पढ़ो_status,
पूर्ण पूर्ण;

module_phy_driver(upd60620_driver);

अटल काष्ठा mdio_device_id __maybe_unused upd60620_tbl[] = अणु
	अणु UPD60620_PHY_ID, 0xfffffffe पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(mdio, upd60620_tbl);
