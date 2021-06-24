<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Clause 45 PHY support
 */
#समावेश <linux/ethtool.h>
#समावेश <linux/export.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/mii.h>
#समावेश <linux/phy.h>

/**
 * genphy_c45_pma_can_sleep - checks अगर the PMA have sleep support
 * @phydev: target phy_device काष्ठा
 */
अटल bool genphy_c45_pma_can_sleep(काष्ठा phy_device *phydev)
अणु
	पूर्णांक stat1;

	stat1 = phy_पढ़ो_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_STAT1);
	अगर (stat1 < 0)
		वापस false;

	वापस !!(stat1 & MDIO_STAT1_LPOWERABLE);
पूर्ण

/**
 * genphy_c45_pma_resume - wakes up the PMA module
 * @phydev: target phy_device काष्ठा
 */
पूर्णांक genphy_c45_pma_resume(काष्ठा phy_device *phydev)
अणु
	अगर (!genphy_c45_pma_can_sleep(phydev))
		वापस -EOPNOTSUPP;

	वापस phy_clear_bits_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_CTRL1,
				  MDIO_CTRL1_LPOWER);
पूर्ण
EXPORT_SYMBOL_GPL(genphy_c45_pma_resume);

/**
 * genphy_c45_pma_suspend - suspends the PMA module
 * @phydev: target phy_device काष्ठा
 */
पूर्णांक genphy_c45_pma_suspend(काष्ठा phy_device *phydev)
अणु
	अगर (!genphy_c45_pma_can_sleep(phydev))
		वापस -EOPNOTSUPP;

	वापस phy_set_bits_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_CTRL1,
				MDIO_CTRL1_LPOWER);
पूर्ण
EXPORT_SYMBOL_GPL(genphy_c45_pma_suspend);

/**
 * genphy_c45_pma_setup_क्रमced - configures a क्रमced speed
 * @phydev: target phy_device काष्ठा
 */
पूर्णांक genphy_c45_pma_setup_क्रमced(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ctrl1, ctrl2, ret;

	/* Half duplex is not supported */
	अगर (phydev->duplex != DUPLEX_FULL)
		वापस -EINVAL;

	ctrl1 = phy_पढ़ो_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_CTRL1);
	अगर (ctrl1 < 0)
		वापस ctrl1;

	ctrl2 = phy_पढ़ो_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_CTRL2);
	अगर (ctrl2 < 0)
		वापस ctrl2;

	ctrl1 &= ~MDIO_CTRL1_SPEEDSEL;
	/*
	 * PMA/PMD type selection is 1.7.5:0 not 1.7.3:0.  See 45.2.1.6.1
	 * in 802.3-2012 and 802.3-2015.
	 */
	ctrl2 &= ~(MDIO_PMA_CTRL2_TYPE | 0x30);

	चयन (phydev->speed) अणु
	हाल SPEED_10:
		ctrl2 |= MDIO_PMA_CTRL2_10BT;
		अवरोध;
	हाल SPEED_100:
		ctrl1 |= MDIO_PMA_CTRL1_SPEED100;
		ctrl2 |= MDIO_PMA_CTRL2_100BTX;
		अवरोध;
	हाल SPEED_1000:
		ctrl1 |= MDIO_PMA_CTRL1_SPEED1000;
		/* Assume 1000base-T */
		ctrl2 |= MDIO_PMA_CTRL2_1000BT;
		अवरोध;
	हाल SPEED_2500:
		ctrl1 |= MDIO_CTRL1_SPEED2_5G;
		/* Assume 2.5Gbase-T */
		ctrl2 |= MDIO_PMA_CTRL2_2_5GBT;
		अवरोध;
	हाल SPEED_5000:
		ctrl1 |= MDIO_CTRL1_SPEED5G;
		/* Assume 5Gbase-T */
		ctrl2 |= MDIO_PMA_CTRL2_5GBT;
		अवरोध;
	हाल SPEED_10000:
		ctrl1 |= MDIO_CTRL1_SPEED10G;
		/* Assume 10Gbase-T */
		ctrl2 |= MDIO_PMA_CTRL2_10GBT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = phy_ग_लिखो_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_CTRL1, ctrl1);
	अगर (ret < 0)
		वापस ret;

	ret = phy_ग_लिखो_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_CTRL2, ctrl2);
	अगर (ret < 0)
		वापस ret;

	वापस genphy_c45_an_disable_aneg(phydev);
पूर्ण
EXPORT_SYMBOL_GPL(genphy_c45_pma_setup_क्रमced);

/**
 * genphy_c45_an_config_aneg - configure advertisement रेजिस्टरs
 * @phydev: target phy_device काष्ठा
 *
 * Configure advertisement रेजिस्टरs based on modes set in phydev->advertising
 *
 * Returns negative त्रुटि_सं code on failure, 0 अगर advertisement didn't change,
 * or 1 अगर advertised modes changed.
 */
पूर्णांक genphy_c45_an_config_aneg(काष्ठा phy_device *phydev)
अणु
	पूर्णांक changed, ret;
	u32 adv;

	linkmode_and(phydev->advertising, phydev->advertising,
		     phydev->supported);

	changed = genphy_config_eee_advert(phydev);

	adv = linkmode_adv_to_mii_adv_t(phydev->advertising);

	ret = phy_modअगरy_mmd_changed(phydev, MDIO_MMD_AN, MDIO_AN_ADVERTISE,
				     ADVERTISE_ALL | ADVERTISE_100BASE4 |
				     ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM,
				     adv);
	अगर (ret < 0)
		वापस ret;
	अगर (ret > 0)
		changed = 1;

	adv = linkmode_adv_to_mii_10gbt_adv_t(phydev->advertising);

	ret = phy_modअगरy_mmd_changed(phydev, MDIO_MMD_AN, MDIO_AN_10GBT_CTRL,
				     MDIO_AN_10GBT_CTRL_ADV10G |
				     MDIO_AN_10GBT_CTRL_ADV5G |
				     MDIO_AN_10GBT_CTRL_ADV2_5G, adv);
	अगर (ret < 0)
		वापस ret;
	अगर (ret > 0)
		changed = 1;

	वापस changed;
पूर्ण
EXPORT_SYMBOL_GPL(genphy_c45_an_config_aneg);

/**
 * genphy_c45_an_disable_aneg - disable स्वतः-negotiation
 * @phydev: target phy_device काष्ठा
 *
 * Disable स्वतः-negotiation in the Clause 45 PHY. The link parameters
 * parameters are controlled through the PMA/PMD MMD रेजिस्टरs.
 *
 * Returns zero on success, negative त्रुटि_सं code on failure.
 */
पूर्णांक genphy_c45_an_disable_aneg(काष्ठा phy_device *phydev)
अणु

	वापस phy_clear_bits_mmd(phydev, MDIO_MMD_AN, MDIO_CTRL1,
				  MDIO_AN_CTRL1_ENABLE | MDIO_AN_CTRL1_RESTART);
पूर्ण
EXPORT_SYMBOL_GPL(genphy_c45_an_disable_aneg);

/**
 * genphy_c45_restart_aneg - Enable and restart स्वतः-negotiation
 * @phydev: target phy_device काष्ठा
 *
 * This assumes that the स्वतः-negotiation MMD is present.
 *
 * Enable and restart स्वतः-negotiation.
 */
पूर्णांक genphy_c45_restart_aneg(काष्ठा phy_device *phydev)
अणु
	वापस phy_set_bits_mmd(phydev, MDIO_MMD_AN, MDIO_CTRL1,
				MDIO_AN_CTRL1_ENABLE | MDIO_AN_CTRL1_RESTART);
पूर्ण
EXPORT_SYMBOL_GPL(genphy_c45_restart_aneg);

/**
 * genphy_c45_check_and_restart_aneg - Enable and restart स्वतः-negotiation
 * @phydev: target phy_device काष्ठा
 * @restart: whether aneg restart is requested
 *
 * This assumes that the स्वतः-negotiation MMD is present.
 *
 * Check, and restart स्वतः-negotiation अगर needed.
 */
पूर्णांक genphy_c45_check_and_restart_aneg(काष्ठा phy_device *phydev, bool restart)
अणु
	पूर्णांक ret;

	अगर (!restart) अणु
		/* Configure and restart aneg अगर it wasn't set beक्रमe */
		ret = phy_पढ़ो_mmd(phydev, MDIO_MMD_AN, MDIO_CTRL1);
		अगर (ret < 0)
			वापस ret;

		अगर (!(ret & MDIO_AN_CTRL1_ENABLE))
			restart = true;
	पूर्ण

	अगर (restart)
		वापस genphy_c45_restart_aneg(phydev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(genphy_c45_check_and_restart_aneg);

/**
 * genphy_c45_aneg_करोne - वापस स्वतः-negotiation complete status
 * @phydev: target phy_device काष्ठा
 *
 * This assumes that the स्वतः-negotiation MMD is present.
 *
 * Reads the status रेजिस्टर from the स्वतः-negotiation MMD, वापसing:
 * - positive अगर स्वतः-negotiation is complete
 * - negative त्रुटि_सं code on error
 * - zero otherwise
 */
पूर्णांक genphy_c45_aneg_करोne(काष्ठा phy_device *phydev)
अणु
	पूर्णांक val = phy_पढ़ो_mmd(phydev, MDIO_MMD_AN, MDIO_STAT1);

	वापस val < 0 ? val : val & MDIO_AN_STAT1_COMPLETE ? 1 : 0;
पूर्ण
EXPORT_SYMBOL_GPL(genphy_c45_aneg_करोne);

/**
 * genphy_c45_पढ़ो_link - पढ़ो the overall link status from the MMDs
 * @phydev: target phy_device काष्ठा
 *
 * Read the link status from the specअगरied MMDs, and अगर they all indicate
 * that the link is up, set phydev->link to 1.  If an error is encountered,
 * a negative त्रुटि_सं will be वापसed, otherwise zero.
 */
पूर्णांक genphy_c45_पढ़ो_link(काष्ठा phy_device *phydev)
अणु
	u32 mmd_mask = MDIO_DEVS_PMAPMD;
	पूर्णांक val, devad;
	bool link = true;

	अगर (phydev->c45_ids.mmds_present & MDIO_DEVS_AN) अणु
		val = phy_पढ़ो_mmd(phydev, MDIO_MMD_AN, MDIO_CTRL1);
		अगर (val < 0)
			वापस val;

		/* Autoneg is being started, thereक्रमe disregard current
		 * link status and report link as करोwn.
		 */
		अगर (val & MDIO_AN_CTRL1_RESTART) अणु
			phydev->link = 0;
			वापस 0;
		पूर्ण
	पूर्ण

	जबतक (mmd_mask && link) अणु
		devad = __ffs(mmd_mask);
		mmd_mask &= ~BIT(devad);

		/* The link state is latched low so that momentary link
		 * drops can be detected. Do not द्विगुन-पढ़ो the status
		 * in polling mode to detect such लघु link drops except
		 * the link was alपढ़ोy करोwn.
		 */
		अगर (!phy_polling_mode(phydev) || !phydev->link) अणु
			val = phy_पढ़ो_mmd(phydev, devad, MDIO_STAT1);
			अगर (val < 0)
				वापस val;
			अन्यथा अगर (val & MDIO_STAT1_LSTATUS)
				जारी;
		पूर्ण

		val = phy_पढ़ो_mmd(phydev, devad, MDIO_STAT1);
		अगर (val < 0)
			वापस val;

		अगर (!(val & MDIO_STAT1_LSTATUS))
			link = false;
	पूर्ण

	phydev->link = link;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(genphy_c45_पढ़ो_link);

/**
 * genphy_c45_पढ़ो_lpa - पढ़ो the link partner advertisement and छोड़ो
 * @phydev: target phy_device काष्ठा
 *
 * Read the Clause 45 defined base (7.19) and 10G (7.33) status रेजिस्टरs,
 * filling in the link partner advertisement, छोड़ो and asym_छोड़ो members
 * in @phydev.  This assumes that the स्वतः-negotiation MMD is present, and
 * the backplane bit (7.48.0) is clear.  Clause 45 PHY drivers are expected
 * to fill in the reमुख्यder of the link partner advert from venकरोr रेजिस्टरs.
 */
पूर्णांक genphy_c45_पढ़ो_lpa(काष्ठा phy_device *phydev)
अणु
	पूर्णांक val;

	val = phy_पढ़ो_mmd(phydev, MDIO_MMD_AN, MDIO_STAT1);
	अगर (val < 0)
		वापस val;

	अगर (!(val & MDIO_AN_STAT1_COMPLETE)) अणु
		linkmode_clear_bit(ETHTOOL_LINK_MODE_Autoneg_BIT,
				   phydev->lp_advertising);
		mii_10gbt_stat_mod_linkmode_lpa_t(phydev->lp_advertising, 0);
		mii_adv_mod_linkmode_adv_t(phydev->lp_advertising, 0);
		phydev->छोड़ो = 0;
		phydev->asym_छोड़ो = 0;

		वापस 0;
	पूर्ण

	linkmode_mod_bit(ETHTOOL_LINK_MODE_Autoneg_BIT, phydev->lp_advertising,
			 val & MDIO_AN_STAT1_LPABLE);

	/* Read the link partner's base page advertisement */
	val = phy_पढ़ो_mmd(phydev, MDIO_MMD_AN, MDIO_AN_LPA);
	अगर (val < 0)
		वापस val;

	mii_adv_mod_linkmode_adv_t(phydev->lp_advertising, val);
	phydev->छोड़ो = val & LPA_PAUSE_CAP ? 1 : 0;
	phydev->asym_छोड़ो = val & LPA_PAUSE_ASYM ? 1 : 0;

	/* Read the link partner's 10G advertisement */
	val = phy_पढ़ो_mmd(phydev, MDIO_MMD_AN, MDIO_AN_10GBT_STAT);
	अगर (val < 0)
		वापस val;

	mii_10gbt_stat_mod_linkmode_lpa_t(phydev->lp_advertising, val);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(genphy_c45_पढ़ो_lpa);

/**
 * genphy_c45_पढ़ो_pma - पढ़ो link speed etc from PMA
 * @phydev: target phy_device काष्ठा
 */
पूर्णांक genphy_c45_पढ़ो_pma(काष्ठा phy_device *phydev)
अणु
	पूर्णांक val;

	linkmode_zero(phydev->lp_advertising);

	val = phy_पढ़ो_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_CTRL1);
	अगर (val < 0)
		वापस val;

	चयन (val & MDIO_CTRL1_SPEEDSEL) अणु
	हाल 0:
		phydev->speed = SPEED_10;
		अवरोध;
	हाल MDIO_PMA_CTRL1_SPEED100:
		phydev->speed = SPEED_100;
		अवरोध;
	हाल MDIO_PMA_CTRL1_SPEED1000:
		phydev->speed = SPEED_1000;
		अवरोध;
	हाल MDIO_CTRL1_SPEED2_5G:
		phydev->speed = SPEED_2500;
		अवरोध;
	हाल MDIO_CTRL1_SPEED5G:
		phydev->speed = SPEED_5000;
		अवरोध;
	हाल MDIO_CTRL1_SPEED10G:
		phydev->speed = SPEED_10000;
		अवरोध;
	शेष:
		phydev->speed = SPEED_UNKNOWN;
		अवरोध;
	पूर्ण

	phydev->duplex = DUPLEX_FULL;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(genphy_c45_पढ़ो_pma);

/**
 * genphy_c45_पढ़ो_mdix - पढ़ो mdix status from PMA
 * @phydev: target phy_device काष्ठा
 */
पूर्णांक genphy_c45_पढ़ो_mdix(काष्ठा phy_device *phydev)
अणु
	पूर्णांक val;

	अगर (phydev->speed == SPEED_10000) अणु
		val = phy_पढ़ो_mmd(phydev, MDIO_MMD_PMAPMD,
				   MDIO_PMA_10GBT_SWAPPOL);
		अगर (val < 0)
			वापस val;

		चयन (val) अणु
		हाल MDIO_PMA_10GBT_SWAPPOL_ABNX | MDIO_PMA_10GBT_SWAPPOL_CDNX:
			phydev->mdix = ETH_TP_MDI;
			अवरोध;

		हाल 0:
			phydev->mdix = ETH_TP_MDI_X;
			अवरोध;

		शेष:
			phydev->mdix = ETH_TP_MDI_INVALID;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(genphy_c45_पढ़ो_mdix);

/**
 * genphy_c45_pma_पढ़ो_abilities - पढ़ो supported link modes from PMA
 * @phydev: target phy_device काष्ठा
 *
 * Read the supported link modes from the PMA Status 2 (1.8) रेजिस्टर. If bit
 * 1.8.9 is set, the list of supported modes is build using the values in the
 * PMA Extended Abilities (1.11) रेजिस्टर, indicating 1000BASET an 10G related
 * modes. If bit 1.11.14 is set, then the list is also extended with the modes
 * in the 2.5G/5G PMA Extended रेजिस्टर (1.21), indicating अगर 2.5GBASET and
 * 5GBASET are supported.
 */
पूर्णांक genphy_c45_pma_पढ़ो_abilities(काष्ठा phy_device *phydev)
अणु
	पूर्णांक val;

	linkmode_clear_bit(ETHTOOL_LINK_MODE_Autoneg_BIT, phydev->supported);
	अगर (phydev->c45_ids.mmds_present & MDIO_DEVS_AN) अणु
		val = phy_पढ़ो_mmd(phydev, MDIO_MMD_AN, MDIO_STAT1);
		अगर (val < 0)
			वापस val;

		अगर (val & MDIO_AN_STAT1_ABLE)
			linkmode_set_bit(ETHTOOL_LINK_MODE_Autoneg_BIT,
					 phydev->supported);
	पूर्ण

	val = phy_पढ़ो_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_STAT2);
	अगर (val < 0)
		वापस val;

	linkmode_mod_bit(ETHTOOL_LINK_MODE_10000baseSR_Full_BIT,
			 phydev->supported,
			 val & MDIO_PMA_STAT2_10GBSR);

	linkmode_mod_bit(ETHTOOL_LINK_MODE_10000baseLR_Full_BIT,
			 phydev->supported,
			 val & MDIO_PMA_STAT2_10GBLR);

	linkmode_mod_bit(ETHTOOL_LINK_MODE_10000baseER_Full_BIT,
			 phydev->supported,
			 val & MDIO_PMA_STAT2_10GBER);

	अगर (val & MDIO_PMA_STAT2_EXTABLE) अणु
		val = phy_पढ़ो_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_PMA_EXTABLE);
		अगर (val < 0)
			वापस val;

		linkmode_mod_bit(ETHTOOL_LINK_MODE_10000baseLRM_Full_BIT,
				 phydev->supported,
				 val & MDIO_PMA_EXTABLE_10GBLRM);
		linkmode_mod_bit(ETHTOOL_LINK_MODE_10000baseT_Full_BIT,
				 phydev->supported,
				 val & MDIO_PMA_EXTABLE_10GBT);
		linkmode_mod_bit(ETHTOOL_LINK_MODE_10000baseKX4_Full_BIT,
				 phydev->supported,
				 val & MDIO_PMA_EXTABLE_10GBKX4);
		linkmode_mod_bit(ETHTOOL_LINK_MODE_10000baseKR_Full_BIT,
				 phydev->supported,
				 val & MDIO_PMA_EXTABLE_10GBKR);
		linkmode_mod_bit(ETHTOOL_LINK_MODE_1000baseT_Full_BIT,
				 phydev->supported,
				 val & MDIO_PMA_EXTABLE_1000BT);
		linkmode_mod_bit(ETHTOOL_LINK_MODE_1000baseKX_Full_BIT,
				 phydev->supported,
				 val & MDIO_PMA_EXTABLE_1000BKX);

		linkmode_mod_bit(ETHTOOL_LINK_MODE_100baseT_Full_BIT,
				 phydev->supported,
				 val & MDIO_PMA_EXTABLE_100BTX);
		linkmode_mod_bit(ETHTOOL_LINK_MODE_100baseT_Half_BIT,
				 phydev->supported,
				 val & MDIO_PMA_EXTABLE_100BTX);

		linkmode_mod_bit(ETHTOOL_LINK_MODE_10baseT_Full_BIT,
				 phydev->supported,
				 val & MDIO_PMA_EXTABLE_10BT);
		linkmode_mod_bit(ETHTOOL_LINK_MODE_10baseT_Half_BIT,
				 phydev->supported,
				 val & MDIO_PMA_EXTABLE_10BT);

		अगर (val & MDIO_PMA_EXTABLE_NBT) अणु
			val = phy_पढ़ो_mmd(phydev, MDIO_MMD_PMAPMD,
					   MDIO_PMA_NG_EXTABLE);
			अगर (val < 0)
				वापस val;

			linkmode_mod_bit(ETHTOOL_LINK_MODE_2500baseT_Full_BIT,
					 phydev->supported,
					 val & MDIO_PMA_NG_EXTABLE_2_5GBT);

			linkmode_mod_bit(ETHTOOL_LINK_MODE_5000baseT_Full_BIT,
					 phydev->supported,
					 val & MDIO_PMA_NG_EXTABLE_5GBT);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(genphy_c45_pma_पढ़ो_abilities);

/**
 * genphy_c45_पढ़ो_status - पढ़ो PHY status
 * @phydev: target phy_device काष्ठा
 *
 * Reads status from PHY and sets phy_device members accordingly.
 */
पूर्णांक genphy_c45_पढ़ो_status(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	ret = genphy_c45_पढ़ो_link(phydev);
	अगर (ret)
		वापस ret;

	phydev->speed = SPEED_UNKNOWN;
	phydev->duplex = DUPLEX_UNKNOWN;
	phydev->छोड़ो = 0;
	phydev->asym_छोड़ो = 0;

	अगर (phydev->स्वतःneg == AUTONEG_ENABLE) अणु
		ret = genphy_c45_पढ़ो_lpa(phydev);
		अगर (ret)
			वापस ret;

		phy_resolve_aneg_linkmode(phydev);
	पूर्ण अन्यथा अणु
		ret = genphy_c45_पढ़ो_pma(phydev);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(genphy_c45_पढ़ो_status);

/**
 * genphy_c45_config_aneg - restart स्वतः-negotiation or क्रमced setup
 * @phydev: target phy_device काष्ठा
 *
 * Description: If स्वतः-negotiation is enabled, we configure the
 *   advertising, and then restart स्वतः-negotiation.  If it is not
 *   enabled, then we क्रमce a configuration.
 */
पूर्णांक genphy_c45_config_aneg(काष्ठा phy_device *phydev)
अणु
	bool changed = false;
	पूर्णांक ret;

	अगर (phydev->स्वतःneg == AUTONEG_DISABLE)
		वापस genphy_c45_pma_setup_क्रमced(phydev);

	ret = genphy_c45_an_config_aneg(phydev);
	अगर (ret < 0)
		वापस ret;
	अगर (ret > 0)
		changed = true;

	वापस genphy_c45_check_and_restart_aneg(phydev, changed);
पूर्ण
EXPORT_SYMBOL_GPL(genphy_c45_config_aneg);

/* The gen10g_* functions are the old Clause 45 stub */

पूर्णांक gen10g_config_aneg(काष्ठा phy_device *phydev)
अणु
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(gen10g_config_aneg);

पूर्णांक genphy_c45_loopback(काष्ठा phy_device *phydev, bool enable)
अणु
	वापस phy_modअगरy_mmd(phydev, MDIO_MMD_PCS, MDIO_CTRL1,
			      MDIO_PCS_CTRL1_LOOPBACK,
			      enable ? MDIO_PCS_CTRL1_LOOPBACK : 0);
पूर्ण
EXPORT_SYMBOL_GPL(genphy_c45_loopback);

काष्ठा phy_driver genphy_c45_driver = अणु
	.phy_id         = 0xffffffff,
	.phy_id_mask    = 0xffffffff,
	.name           = "Generic Clause 45 PHY",
	.पढ़ो_status    = genphy_c45_पढ़ो_status,
पूर्ण;
