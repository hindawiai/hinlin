<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम Teranetics PHY
 *
 * Author: Shaohui Xie <Shaohui.Xie@मुक्तscale.com>
 *
 * Copyright 2015 Freescale Semiconductor, Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mii.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/phy.h>

MODULE_DESCRIPTION("Teranetics PHY driver");
MODULE_AUTHOR("Shaohui Xie <Shaohui.Xie@freescale.com>");
MODULE_LICENSE("GPL v2");

#घोषणा PHY_ID_TN2020	0x00a19410
#घोषणा MDIO_PHYXS_LNSTAT_SYNC0	0x0001
#घोषणा MDIO_PHYXS_LNSTAT_SYNC1	0x0002
#घोषणा MDIO_PHYXS_LNSTAT_SYNC2	0x0004
#घोषणा MDIO_PHYXS_LNSTAT_SYNC3	0x0008
#घोषणा MDIO_PHYXS_LNSTAT_ALIGN 0x1000

#घोषणा MDIO_PHYXS_LANE_READY	(MDIO_PHYXS_LNSTAT_SYNC0 | \
				MDIO_PHYXS_LNSTAT_SYNC1 | \
				MDIO_PHYXS_LNSTAT_SYNC2 | \
				MDIO_PHYXS_LNSTAT_SYNC3 | \
				MDIO_PHYXS_LNSTAT_ALIGN)

अटल पूर्णांक teranetics_aneg_करोne(काष्ठा phy_device *phydev)
अणु
	/* स्वतः negotiation state can only be checked when using copper
	 * port, अगर using fiber port, just lie it's करोne.
	 */
	अगर (!phy_पढ़ो_mmd(phydev, MDIO_MMD_VEND1, 93))
		वापस genphy_c45_aneg_करोne(phydev);

	वापस 1;
पूर्ण

अटल पूर्णांक teranetics_पढ़ो_status(काष्ठा phy_device *phydev)
अणु
	पूर्णांक reg;

	phydev->link = 1;

	phydev->speed = SPEED_10000;
	phydev->duplex = DUPLEX_FULL;

	अगर (!phy_पढ़ो_mmd(phydev, MDIO_MMD_VEND1, 93)) अणु
		reg = phy_पढ़ो_mmd(phydev, MDIO_MMD_PHYXS, MDIO_PHYXS_LNSTAT);
		अगर (reg < 0 ||
		    !((reg & MDIO_PHYXS_LANE_READY) == MDIO_PHYXS_LANE_READY)) अणु
			phydev->link = 0;
			वापस 0;
		पूर्ण

		reg = phy_पढ़ो_mmd(phydev, MDIO_MMD_AN, MDIO_STAT1);
		अगर (reg < 0 || !(reg & MDIO_STAT1_LSTATUS))
			phydev->link = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक teranetics_match_phy_device(काष्ठा phy_device *phydev)
अणु
	वापस phydev->c45_ids.device_ids[3] == PHY_ID_TN2020;
पूर्ण

अटल काष्ठा phy_driver teranetics_driver[] = अणु
अणु
	.phy_id		= PHY_ID_TN2020,
	.phy_id_mask	= 0xffffffff,
	.name		= "Teranetics TN2020",
	.features       = PHY_10GBIT_FEATURES,
	.aneg_करोne	= teranetics_aneg_करोne,
	.config_aneg    = gen10g_config_aneg,
	.पढ़ो_status	= teranetics_पढ़ो_status,
	.match_phy_device = teranetics_match_phy_device,
पूर्ण,
पूर्ण;

module_phy_driver(teranetics_driver);

अटल काष्ठा mdio_device_id __maybe_unused teranetics_tbl[] = अणु
	अणु PHY_ID_TN2020, 0xffffffff पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(mdio, teranetics_tbl);
