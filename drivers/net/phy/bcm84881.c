<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Broadcom BCM84881 NBASE-T PHY driver, as found on a SFP+ module.
// Copyright (C) 2019 Russell King, Deep Blue Solutions Ltd.
//
// Like the Marvell 88x3310, the Broadcom 84881 changes its host-side
// पूर्णांकerface according to the operating speed between 10GBASE-R,
// 2500BASE-X and SGMII (but unlike the 88x3310, without the control
// word).
//
// This driver only supports those aspects of the PHY that I'm able to
// observe and test with the SFP+ module, which is an incomplete subset
// of what this PHY is able to support. For example, I only assume it
// supports a single lane Serdes connection, but it may be that the PHY
// is able to support more than that.
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/phy.h>

क्रमागत अणु
	MDIO_AN_C22 = 0xffe0,
पूर्ण;

अटल पूर्णांक bcm84881_रुको_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक val;

	वापस phy_पढ़ो_mmd_poll_समयout(phydev, MDIO_MMD_PMAPMD, MDIO_CTRL1,
					 val, !(val & MDIO_CTRL1_RESET),
					 100000, 2000000, false);
पूर्ण

अटल पूर्णांक bcm84881_config_init(काष्ठा phy_device *phydev)
अणु
	चयन (phydev->पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_SGMII:
	हाल PHY_INTERFACE_MODE_2500BASEX:
	हाल PHY_INTERFACE_MODE_10GBASER:
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bcm84881_probe(काष्ठा phy_device *phydev)
अणु
	/* This driver requires PMAPMD and AN blocks */
	स्थिर u32 mmd_mask = MDIO_DEVS_PMAPMD | MDIO_DEVS_AN;

	अगर (!phydev->is_c45 ||
	    (phydev->c45_ids.devices_in_package & mmd_mask) != mmd_mask)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक bcm84881_get_features(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	ret = genphy_c45_pma_पढ़ो_abilities(phydev);
	अगर (ret)
		वापस ret;

	/* Although the PHY sets bit 1.11.8, it करोes not support 10M modes */
	linkmode_clear_bit(ETHTOOL_LINK_MODE_10baseT_Half_BIT,
			   phydev->supported);
	linkmode_clear_bit(ETHTOOL_LINK_MODE_10baseT_Full_BIT,
			   phydev->supported);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm84881_config_aneg(काष्ठा phy_device *phydev)
अणु
	bool changed = false;
	u32 adv;
	पूर्णांक ret;

	/* Wait क्रम the PHY to finish initialising, otherwise our
	 * advertisement may be overwritten.
	 */
	ret = bcm84881_रुको_init(phydev);
	अगर (ret)
		वापस ret;

	/* We करोn't support manual MDI control */
	phydev->mdix_ctrl = ETH_TP_MDI_AUTO;

	/* disabled स्वतःneg करोesn't seem to work with this PHY */
	अगर (phydev->स्वतःneg == AUTONEG_DISABLE)
		वापस -EINVAL;

	ret = genphy_c45_an_config_aneg(phydev);
	अगर (ret < 0)
		वापस ret;
	अगर (ret > 0)
		changed = true;

	adv = linkmode_adv_to_mii_ctrl1000_t(phydev->advertising);
	ret = phy_modअगरy_mmd_changed(phydev, MDIO_MMD_AN,
				     MDIO_AN_C22 + MII_CTRL1000,
				     ADVERTISE_1000FULL | ADVERTISE_1000HALF,
				     adv);
	अगर (ret < 0)
		वापस ret;
	अगर (ret > 0)
		changed = true;

	वापस genphy_c45_check_and_restart_aneg(phydev, changed);
पूर्ण

अटल पूर्णांक bcm84881_aneg_करोne(काष्ठा phy_device *phydev)
अणु
	पूर्णांक bmsr, val;

	val = phy_पढ़ो_mmd(phydev, MDIO_MMD_AN, MDIO_STAT1);
	अगर (val < 0)
		वापस val;

	bmsr = phy_पढ़ो_mmd(phydev, MDIO_MMD_AN, MDIO_AN_C22 + MII_BMSR);
	अगर (bmsr < 0)
		वापस val;

	वापस !!(val & MDIO_AN_STAT1_COMPLETE) &&
	       !!(bmsr & BMSR_ANEGCOMPLETE);
पूर्ण

अटल पूर्णांक bcm84881_पढ़ो_status(काष्ठा phy_device *phydev)
अणु
	अचिन्हित पूर्णांक mode;
	पूर्णांक bmsr, val;

	val = phy_पढ़ो_mmd(phydev, MDIO_MMD_AN, MDIO_CTRL1);
	अगर (val < 0)
		वापस val;

	अगर (val & MDIO_AN_CTRL1_RESTART) अणु
		phydev->link = 0;
		वापस 0;
	पूर्ण

	val = phy_पढ़ो_mmd(phydev, MDIO_MMD_AN, MDIO_STAT1);
	अगर (val < 0)
		वापस val;

	bmsr = phy_पढ़ो_mmd(phydev, MDIO_MMD_AN, MDIO_AN_C22 + MII_BMSR);
	अगर (bmsr < 0)
		वापस val;

	phydev->स्वतःneg_complete = !!(val & MDIO_AN_STAT1_COMPLETE) &&
				   !!(bmsr & BMSR_ANEGCOMPLETE);
	phydev->link = !!(val & MDIO_STAT1_LSTATUS) &&
		       !!(bmsr & BMSR_LSTATUS);
	अगर (phydev->स्वतःneg == AUTONEG_ENABLE && !phydev->स्वतःneg_complete)
		phydev->link = false;

	linkmode_zero(phydev->lp_advertising);
	phydev->speed = SPEED_UNKNOWN;
	phydev->duplex = DUPLEX_UNKNOWN;
	phydev->छोड़ो = 0;
	phydev->asym_छोड़ो = 0;
	phydev->mdix = 0;

	अगर (!phydev->link)
		वापस 0;

	अगर (phydev->स्वतःneg_complete) अणु
		val = genphy_c45_पढ़ो_lpa(phydev);
		अगर (val < 0)
			वापस val;

		val = phy_पढ़ो_mmd(phydev, MDIO_MMD_AN,
				   MDIO_AN_C22 + MII_STAT1000);
		अगर (val < 0)
			वापस val;

		mii_stat1000_mod_linkmode_lpa_t(phydev->lp_advertising, val);

		अगर (phydev->स्वतःneg == AUTONEG_ENABLE)
			phy_resolve_aneg_linkmode(phydev);
	पूर्ण

	अगर (phydev->स्वतःneg == AUTONEG_DISABLE) अणु
		/* disabled स्वतःneg करोesn't seem to work, so क्रमce the link
		 * करोwn.
		 */
		phydev->link = 0;
		वापस 0;
	पूर्ण

	/* Set the host link mode - we set the phy पूर्णांकerface mode and
	 * the speed according to this रेजिस्टर so that करोwnshअगरt works.
	 * We leave the duplex setting as per the resolution from the
	 * above.
	 */
	val = phy_पढ़ो_mmd(phydev, MDIO_MMD_VEND1, 0x4011);
	mode = (val & 0x1e) >> 1;
	अगर (mode == 1 || mode == 2)
		phydev->पूर्णांकerface = PHY_INTERFACE_MODE_SGMII;
	अन्यथा अगर (mode == 3)
		phydev->पूर्णांकerface = PHY_INTERFACE_MODE_10GBASER;
	अन्यथा अगर (mode == 4)
		phydev->पूर्णांकerface = PHY_INTERFACE_MODE_2500BASEX;
	चयन (mode & 7) अणु
	हाल 1:
		phydev->speed = SPEED_100;
		अवरोध;
	हाल 2:
		phydev->speed = SPEED_1000;
		अवरोध;
	हाल 3:
		phydev->speed = SPEED_10000;
		अवरोध;
	हाल 4:
		phydev->speed = SPEED_2500;
		अवरोध;
	हाल 5:
		phydev->speed = SPEED_5000;
		अवरोध;
	पूर्ण

	वापस genphy_c45_पढ़ो_mdix(phydev);
पूर्ण

अटल काष्ठा phy_driver bcm84881_drivers[] = अणु
	अणु
		.phy_id		= 0xae025150,
		.phy_id_mask	= 0xfffffff0,
		.name		= "Broadcom BCM84881",
		.config_init	= bcm84881_config_init,
		.probe		= bcm84881_probe,
		.get_features	= bcm84881_get_features,
		.config_aneg	= bcm84881_config_aneg,
		.aneg_करोne	= bcm84881_aneg_करोne,
		.पढ़ो_status	= bcm84881_पढ़ो_status,
	पूर्ण,
पूर्ण;

module_phy_driver(bcm84881_drivers);

/* FIXME: module स्वतः-loading क्रम Clause 45 PHYs seems non-functional */
अटल काष्ठा mdio_device_id __maybe_unused bcm84881_tbl[] = अणु
	अणु 0xae025150, 0xfffffff0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_AUTHOR("Russell King");
MODULE_DESCRIPTION("Broadcom BCM84881 PHY driver");
MODULE_DEVICE_TABLE(mdio, bcm84881_tbl);
MODULE_LICENSE("GPL");
