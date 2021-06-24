<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * mdio.c: Generic support क्रम MDIO-compatible transceivers
 * Copyright 2006-2009 Solarflare Communications Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/capability.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ethtool.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/module.h>

MODULE_DESCRIPTION("Generic support for MDIO-compatible transceivers");
MODULE_AUTHOR("Copyright 2006-2009 Solarflare Communications Inc.");
MODULE_LICENSE("GPL");

/**
 * mdio45_probe - probe क्रम an MDIO (clause 45) device
 * @mdio: MDIO पूर्णांकerface
 * @prtad: Expected PHY address
 *
 * This sets @prtad and @mmds in the MDIO पूर्णांकerface अगर successful.
 * Returns 0 on success, negative on error.
 */
पूर्णांक mdio45_probe(काष्ठा mdio_अगर_info *mdio, पूर्णांक prtad)
अणु
	पूर्णांक mmd, stat2, devs1, devs2;

	/* Assume PHY must have at least one of PMA/PMD, WIS, PCS, PHY
	 * XS or DTE XS; give up अगर none is present. */
	क्रम (mmd = 1; mmd <= 5; mmd++) अणु
		/* Is this MMD present? */
		stat2 = mdio->mdio_पढ़ो(mdio->dev, prtad, mmd, MDIO_STAT2);
		अगर (stat2 < 0 ||
		    (stat2 & MDIO_STAT2_DEVPRST) != MDIO_STAT2_DEVPRST_VAL)
			जारी;

		/* It should tell us about all the other MMDs */
		devs1 = mdio->mdio_पढ़ो(mdio->dev, prtad, mmd, MDIO_DEVS1);
		devs2 = mdio->mdio_पढ़ो(mdio->dev, prtad, mmd, MDIO_DEVS2);
		अगर (devs1 < 0 || devs2 < 0)
			जारी;

		mdio->prtad = prtad;
		mdio->mmds = devs1 | (devs2 << 16);
		वापस 0;
	पूर्ण

	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL(mdio45_probe);

/**
 * mdio_set_flag - set or clear flag in an MDIO रेजिस्टर
 * @mdio: MDIO पूर्णांकerface
 * @prtad: PHY address
 * @devad: MMD address
 * @addr: Register address
 * @mask: Mask क्रम flag (single bit set)
 * @sense: New value of flag
 *
 * This debounces changes: it करोes not ग_लिखो the रेजिस्टर अगर the flag
 * alपढ़ोy has the proper value.  Returns 0 on success, negative on error.
 */
पूर्णांक mdio_set_flag(स्थिर काष्ठा mdio_अगर_info *mdio,
		  पूर्णांक prtad, पूर्णांक devad, u16 addr, पूर्णांक mask,
		  bool sense)
अणु
	पूर्णांक old_val = mdio->mdio_पढ़ो(mdio->dev, prtad, devad, addr);
	पूर्णांक new_val;

	अगर (old_val < 0)
		वापस old_val;
	अगर (sense)
		new_val = old_val | mask;
	अन्यथा
		new_val = old_val & ~mask;
	अगर (old_val == new_val)
		वापस 0;
	वापस mdio->mdio_ग_लिखो(mdio->dev, prtad, devad, addr, new_val);
पूर्ण
EXPORT_SYMBOL(mdio_set_flag);

/**
 * mdio45_links_ok - is link status up/OK
 * @mdio: MDIO पूर्णांकerface
 * @mmd_mask: Mask क्रम MMDs to check
 *
 * Returns 1 अगर the PHY reports link status up/OK, 0 otherwise.
 * @mmd_mask is normally @mdio->mmds, but अगर loopback is enabled
 * the MMDs being bypassed should be excluded from the mask.
 */
पूर्णांक mdio45_links_ok(स्थिर काष्ठा mdio_अगर_info *mdio, u32 mmd_mask)
अणु
	पूर्णांक devad, reg;

	अगर (!mmd_mask) अणु
		/* Use असलence of XGMII faults in lieu of link state */
		reg = mdio->mdio_पढ़ो(mdio->dev, mdio->prtad,
				      MDIO_MMD_PHYXS, MDIO_STAT2);
		वापस reg >= 0 && !(reg & MDIO_STAT2_RXFAULT);
	पूर्ण

	क्रम (devad = 0; mmd_mask; devad++) अणु
		अगर (mmd_mask & (1 << devad)) अणु
			mmd_mask &= ~(1 << devad);

			/* Reset the latched status and fault flags */
			mdio->mdio_पढ़ो(mdio->dev, mdio->prtad,
					devad, MDIO_STAT1);
			अगर (devad == MDIO_MMD_PMAPMD || devad == MDIO_MMD_PCS ||
			    devad == MDIO_MMD_PHYXS || devad == MDIO_MMD_DTEXS)
				mdio->mdio_पढ़ो(mdio->dev, mdio->prtad,
						devad, MDIO_STAT2);

			/* Check the current status and fault flags */
			reg = mdio->mdio_पढ़ो(mdio->dev, mdio->prtad,
					      devad, MDIO_STAT1);
			अगर (reg < 0 ||
			    (reg & (MDIO_STAT1_FAULT | MDIO_STAT1_LSTATUS)) !=
			    MDIO_STAT1_LSTATUS)
				वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL(mdio45_links_ok);

/**
 * mdio45_nway_restart - restart स्वतः-negotiation क्रम this पूर्णांकerface
 * @mdio: MDIO पूर्णांकerface
 *
 * Returns 0 on success, negative on error.
 */
पूर्णांक mdio45_nway_restart(स्थिर काष्ठा mdio_अगर_info *mdio)
अणु
	अगर (!(mdio->mmds & MDIO_DEVS_AN))
		वापस -EOPNOTSUPP;

	mdio_set_flag(mdio, mdio->prtad, MDIO_MMD_AN, MDIO_CTRL1,
		      MDIO_AN_CTRL1_RESTART, true);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mdio45_nway_restart);

अटल u32 mdio45_get_an(स्थिर काष्ठा mdio_अगर_info *mdio, u16 addr)
अणु
	u32 result = 0;
	पूर्णांक reg;

	reg = mdio->mdio_पढ़ो(mdio->dev, mdio->prtad, MDIO_MMD_AN, addr);
	अगर (reg & ADVERTISE_10HALF)
		result |= ADVERTISED_10baseT_Half;
	अगर (reg & ADVERTISE_10FULL)
		result |= ADVERTISED_10baseT_Full;
	अगर (reg & ADVERTISE_100HALF)
		result |= ADVERTISED_100baseT_Half;
	अगर (reg & ADVERTISE_100FULL)
		result |= ADVERTISED_100baseT_Full;
	अगर (reg & ADVERTISE_PAUSE_CAP)
		result |= ADVERTISED_Pause;
	अगर (reg & ADVERTISE_PAUSE_ASYM)
		result |= ADVERTISED_Asym_Pause;
	वापस result;
पूर्ण

/**
 * mdio45_ethtool_gset_npage - get settings क्रम ETHTOOL_GSET
 * @mdio: MDIO पूर्णांकerface
 * @ecmd: Ethtool request काष्ठाure
 * @npage_adv: Modes currently advertised on next pages
 * @npage_lpa: Modes advertised by link partner on next pages
 *
 * The @ecmd parameter is expected to have been cleared beक्रमe calling
 * mdio45_ethtool_gset_npage().
 *
 * Since the CSRs क्रम स्वतः-negotiation using next pages are not fully
 * standardised, this function करोes not attempt to decode them.  The
 * caller must pass them in.
 */
व्योम mdio45_ethtool_gset_npage(स्थिर काष्ठा mdio_अगर_info *mdio,
			       काष्ठा ethtool_cmd *ecmd,
			       u32 npage_adv, u32 npage_lpa)
अणु
	पूर्णांक reg;
	u32 speed;

	BUILD_BUG_ON(MDIO_SUPPORTS_C22 != ETH_MDIO_SUPPORTS_C22);
	BUILD_BUG_ON(MDIO_SUPPORTS_C45 != ETH_MDIO_SUPPORTS_C45);

	ecmd->transceiver = XCVR_INTERNAL;
	ecmd->phy_address = mdio->prtad;
	ecmd->mdio_support =
		mdio->mode_support & (MDIO_SUPPORTS_C45 | MDIO_SUPPORTS_C22);

	reg = mdio->mdio_पढ़ो(mdio->dev, mdio->prtad, MDIO_MMD_PMAPMD,
			      MDIO_CTRL2);
	चयन (reg & MDIO_PMA_CTRL2_TYPE) अणु
	हाल MDIO_PMA_CTRL2_10GBT:
	हाल MDIO_PMA_CTRL2_1000BT:
	हाल MDIO_PMA_CTRL2_100BTX:
	हाल MDIO_PMA_CTRL2_10BT:
		ecmd->port = PORT_TP;
		ecmd->supported = SUPPORTED_TP;
		reg = mdio->mdio_पढ़ो(mdio->dev, mdio->prtad, MDIO_MMD_PMAPMD,
				      MDIO_SPEED);
		अगर (reg & MDIO_SPEED_10G)
			ecmd->supported |= SUPPORTED_10000baseT_Full;
		अगर (reg & MDIO_PMA_SPEED_1000)
			ecmd->supported |= (SUPPORTED_1000baseT_Full |
					    SUPPORTED_1000baseT_Half);
		अगर (reg & MDIO_PMA_SPEED_100)
			ecmd->supported |= (SUPPORTED_100baseT_Full |
					    SUPPORTED_100baseT_Half);
		अगर (reg & MDIO_PMA_SPEED_10)
			ecmd->supported |= (SUPPORTED_10baseT_Full |
					    SUPPORTED_10baseT_Half);
		ecmd->advertising = ADVERTISED_TP;
		अवरोध;

	हाल MDIO_PMA_CTRL2_10GBCX4:
		ecmd->port = PORT_OTHER;
		ecmd->supported = 0;
		ecmd->advertising = 0;
		अवरोध;

	हाल MDIO_PMA_CTRL2_10GBKX4:
	हाल MDIO_PMA_CTRL2_10GBKR:
	हाल MDIO_PMA_CTRL2_1000BKX:
		ecmd->port = PORT_OTHER;
		ecmd->supported = SUPPORTED_Backplane;
		reg = mdio->mdio_पढ़ो(mdio->dev, mdio->prtad, MDIO_MMD_PMAPMD,
				      MDIO_PMA_EXTABLE);
		अगर (reg & MDIO_PMA_EXTABLE_10GBKX4)
			ecmd->supported |= SUPPORTED_10000baseKX4_Full;
		अगर (reg & MDIO_PMA_EXTABLE_10GBKR)
			ecmd->supported |= SUPPORTED_10000baseKR_Full;
		अगर (reg & MDIO_PMA_EXTABLE_1000BKX)
			ecmd->supported |= SUPPORTED_1000baseKX_Full;
		reg = mdio->mdio_पढ़ो(mdio->dev, mdio->prtad, MDIO_MMD_PMAPMD,
				      MDIO_PMA_10GBR_FECABLE);
		अगर (reg & MDIO_PMA_10GBR_FECABLE_ABLE)
			ecmd->supported |= SUPPORTED_10000baseR_FEC;
		ecmd->advertising = ADVERTISED_Backplane;
		अवरोध;

	/* All the other defined modes are flavours of optical */
	शेष:
		ecmd->port = PORT_FIBRE;
		ecmd->supported = SUPPORTED_FIBRE;
		ecmd->advertising = ADVERTISED_FIBRE;
		अवरोध;
	पूर्ण

	अगर (mdio->mmds & MDIO_DEVS_AN) अणु
		ecmd->supported |= SUPPORTED_Autoneg;
		reg = mdio->mdio_पढ़ो(mdio->dev, mdio->prtad, MDIO_MMD_AN,
				      MDIO_CTRL1);
		अगर (reg & MDIO_AN_CTRL1_ENABLE) अणु
			ecmd->स्वतःneg = AUTONEG_ENABLE;
			ecmd->advertising |=
				ADVERTISED_Autoneg |
				mdio45_get_an(mdio, MDIO_AN_ADVERTISE) |
				npage_adv;
		पूर्ण अन्यथा अणु
			ecmd->स्वतःneg = AUTONEG_DISABLE;
		पूर्ण
	पूर्ण अन्यथा अणु
		ecmd->स्वतःneg = AUTONEG_DISABLE;
	पूर्ण

	अगर (ecmd->स्वतःneg) अणु
		u32 modes = 0;
		पूर्णांक an_stat = mdio->mdio_पढ़ो(mdio->dev, mdio->prtad,
					      MDIO_MMD_AN, MDIO_STAT1);

		/* If AN is complete and successful, report best common
		 * mode, otherwise report best advertised mode. */
		अगर (an_stat & MDIO_AN_STAT1_COMPLETE) अणु
			ecmd->lp_advertising =
				mdio45_get_an(mdio, MDIO_AN_LPA) | npage_lpa;
			अगर (an_stat & MDIO_AN_STAT1_LPABLE)
				ecmd->lp_advertising |= ADVERTISED_Autoneg;
			modes = ecmd->advertising & ecmd->lp_advertising;
		पूर्ण
		अगर ((modes & ~ADVERTISED_Autoneg) == 0)
			modes = ecmd->advertising;

		अगर (modes & (ADVERTISED_10000baseT_Full |
			     ADVERTISED_10000baseKX4_Full |
			     ADVERTISED_10000baseKR_Full)) अणु
			speed = SPEED_10000;
			ecmd->duplex = DUPLEX_FULL;
		पूर्ण अन्यथा अगर (modes & (ADVERTISED_1000baseT_Full |
				    ADVERTISED_1000baseT_Half |
				    ADVERTISED_1000baseKX_Full)) अणु
			speed = SPEED_1000;
			ecmd->duplex = !(modes & ADVERTISED_1000baseT_Half);
		पूर्ण अन्यथा अगर (modes & (ADVERTISED_100baseT_Full |
				    ADVERTISED_100baseT_Half)) अणु
			speed = SPEED_100;
			ecmd->duplex = !!(modes & ADVERTISED_100baseT_Full);
		पूर्ण अन्यथा अणु
			speed = SPEED_10;
			ecmd->duplex = !!(modes & ADVERTISED_10baseT_Full);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Report क्रमced settings */
		reg = mdio->mdio_पढ़ो(mdio->dev, mdio->prtad, MDIO_MMD_PMAPMD,
				      MDIO_CTRL1);
		speed = (((reg & MDIO_PMA_CTRL1_SPEED1000) ? 100 : 1)
			 * ((reg & MDIO_PMA_CTRL1_SPEED100) ? 100 : 10));
		ecmd->duplex = (reg & MDIO_CTRL1_FULLDPLX ||
				speed == SPEED_10000);
	पूर्ण

	ethtool_cmd_speed_set(ecmd, speed);

	/* 10GBASE-T MDI/MDI-X */
	अगर (ecmd->port == PORT_TP
	    && (ethtool_cmd_speed(ecmd) == SPEED_10000)) अणु
		चयन (mdio->mdio_पढ़ो(mdio->dev, mdio->prtad, MDIO_MMD_PMAPMD,
					MDIO_PMA_10GBT_SWAPPOL)) अणु
		हाल MDIO_PMA_10GBT_SWAPPOL_ABNX | MDIO_PMA_10GBT_SWAPPOL_CDNX:
			ecmd->eth_tp_mdix = ETH_TP_MDI;
			अवरोध;
		हाल 0:
			ecmd->eth_tp_mdix = ETH_TP_MDI_X;
			अवरोध;
		शेष:
			/* It's complicated... */
			ecmd->eth_tp_mdix = ETH_TP_MDI_INVALID;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(mdio45_ethtool_gset_npage);

/**
 * mdio45_ethtool_ksettings_get_npage - get settings क्रम ETHTOOL_GLINKSETTINGS
 * @mdio: MDIO पूर्णांकerface
 * @cmd: Ethtool request काष्ठाure
 * @npage_adv: Modes currently advertised on next pages
 * @npage_lpa: Modes advertised by link partner on next pages
 *
 * The @cmd parameter is expected to have been cleared beक्रमe calling
 * mdio45_ethtool_ksettings_get_npage().
 *
 * Since the CSRs क्रम स्वतः-negotiation using next pages are not fully
 * standardised, this function करोes not attempt to decode them.  The
 * caller must pass them in.
 */
व्योम mdio45_ethtool_ksettings_get_npage(स्थिर काष्ठा mdio_अगर_info *mdio,
					काष्ठा ethtool_link_ksettings *cmd,
					u32 npage_adv, u32 npage_lpa)
अणु
	पूर्णांक reg;
	u32 speed, supported = 0, advertising = 0, lp_advertising = 0;

	BUILD_BUG_ON(MDIO_SUPPORTS_C22 != ETH_MDIO_SUPPORTS_C22);
	BUILD_BUG_ON(MDIO_SUPPORTS_C45 != ETH_MDIO_SUPPORTS_C45);

	cmd->base.phy_address = mdio->prtad;
	cmd->base.mdio_support =
		mdio->mode_support & (MDIO_SUPPORTS_C45 | MDIO_SUPPORTS_C22);

	reg = mdio->mdio_पढ़ो(mdio->dev, mdio->prtad, MDIO_MMD_PMAPMD,
			      MDIO_CTRL2);
	चयन (reg & MDIO_PMA_CTRL2_TYPE) अणु
	हाल MDIO_PMA_CTRL2_10GBT:
	हाल MDIO_PMA_CTRL2_1000BT:
	हाल MDIO_PMA_CTRL2_100BTX:
	हाल MDIO_PMA_CTRL2_10BT:
		cmd->base.port = PORT_TP;
		supported = SUPPORTED_TP;
		reg = mdio->mdio_पढ़ो(mdio->dev, mdio->prtad, MDIO_MMD_PMAPMD,
				      MDIO_SPEED);
		अगर (reg & MDIO_SPEED_10G)
			supported |= SUPPORTED_10000baseT_Full;
		अगर (reg & MDIO_PMA_SPEED_1000)
			supported |= (SUPPORTED_1000baseT_Full |
					    SUPPORTED_1000baseT_Half);
		अगर (reg & MDIO_PMA_SPEED_100)
			supported |= (SUPPORTED_100baseT_Full |
					    SUPPORTED_100baseT_Half);
		अगर (reg & MDIO_PMA_SPEED_10)
			supported |= (SUPPORTED_10baseT_Full |
					    SUPPORTED_10baseT_Half);
		advertising = ADVERTISED_TP;
		अवरोध;

	हाल MDIO_PMA_CTRL2_10GBCX4:
		cmd->base.port = PORT_OTHER;
		supported = 0;
		advertising = 0;
		अवरोध;

	हाल MDIO_PMA_CTRL2_10GBKX4:
	हाल MDIO_PMA_CTRL2_10GBKR:
	हाल MDIO_PMA_CTRL2_1000BKX:
		cmd->base.port = PORT_OTHER;
		supported = SUPPORTED_Backplane;
		reg = mdio->mdio_पढ़ो(mdio->dev, mdio->prtad, MDIO_MMD_PMAPMD,
				      MDIO_PMA_EXTABLE);
		अगर (reg & MDIO_PMA_EXTABLE_10GBKX4)
			supported |= SUPPORTED_10000baseKX4_Full;
		अगर (reg & MDIO_PMA_EXTABLE_10GBKR)
			supported |= SUPPORTED_10000baseKR_Full;
		अगर (reg & MDIO_PMA_EXTABLE_1000BKX)
			supported |= SUPPORTED_1000baseKX_Full;
		reg = mdio->mdio_पढ़ो(mdio->dev, mdio->prtad, MDIO_MMD_PMAPMD,
				      MDIO_PMA_10GBR_FECABLE);
		अगर (reg & MDIO_PMA_10GBR_FECABLE_ABLE)
			supported |= SUPPORTED_10000baseR_FEC;
		advertising = ADVERTISED_Backplane;
		अवरोध;

	/* All the other defined modes are flavours of optical */
	शेष:
		cmd->base.port = PORT_FIBRE;
		supported = SUPPORTED_FIBRE;
		advertising = ADVERTISED_FIBRE;
		अवरोध;
	पूर्ण

	अगर (mdio->mmds & MDIO_DEVS_AN) अणु
		supported |= SUPPORTED_Autoneg;
		reg = mdio->mdio_पढ़ो(mdio->dev, mdio->prtad, MDIO_MMD_AN,
				      MDIO_CTRL1);
		अगर (reg & MDIO_AN_CTRL1_ENABLE) अणु
			cmd->base.स्वतःneg = AUTONEG_ENABLE;
			advertising |=
				ADVERTISED_Autoneg |
				mdio45_get_an(mdio, MDIO_AN_ADVERTISE) |
				npage_adv;
		पूर्ण अन्यथा अणु
			cmd->base.स्वतःneg = AUTONEG_DISABLE;
		पूर्ण
	पूर्ण अन्यथा अणु
		cmd->base.स्वतःneg = AUTONEG_DISABLE;
	पूर्ण

	अगर (cmd->base.स्वतःneg) अणु
		u32 modes = 0;
		पूर्णांक an_stat = mdio->mdio_पढ़ो(mdio->dev, mdio->prtad,
					      MDIO_MMD_AN, MDIO_STAT1);

		/* If AN is complete and successful, report best common
		 * mode, otherwise report best advertised mode.
		 */
		अगर (an_stat & MDIO_AN_STAT1_COMPLETE) अणु
			lp_advertising =
				mdio45_get_an(mdio, MDIO_AN_LPA) | npage_lpa;
			अगर (an_stat & MDIO_AN_STAT1_LPABLE)
				lp_advertising |= ADVERTISED_Autoneg;
			modes = advertising & lp_advertising;
		पूर्ण
		अगर ((modes & ~ADVERTISED_Autoneg) == 0)
			modes = advertising;

		अगर (modes & (ADVERTISED_10000baseT_Full |
			     ADVERTISED_10000baseKX4_Full |
			     ADVERTISED_10000baseKR_Full)) अणु
			speed = SPEED_10000;
			cmd->base.duplex = DUPLEX_FULL;
		पूर्ण अन्यथा अगर (modes & (ADVERTISED_1000baseT_Full |
				    ADVERTISED_1000baseT_Half |
				    ADVERTISED_1000baseKX_Full)) अणु
			speed = SPEED_1000;
			cmd->base.duplex = !(modes & ADVERTISED_1000baseT_Half);
		पूर्ण अन्यथा अगर (modes & (ADVERTISED_100baseT_Full |
				    ADVERTISED_100baseT_Half)) अणु
			speed = SPEED_100;
			cmd->base.duplex = !!(modes & ADVERTISED_100baseT_Full);
		पूर्ण अन्यथा अणु
			speed = SPEED_10;
			cmd->base.duplex = !!(modes & ADVERTISED_10baseT_Full);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Report क्रमced settings */
		reg = mdio->mdio_पढ़ो(mdio->dev, mdio->prtad, MDIO_MMD_PMAPMD,
				      MDIO_CTRL1);
		speed = (((reg & MDIO_PMA_CTRL1_SPEED1000) ? 100 : 1)
			 * ((reg & MDIO_PMA_CTRL1_SPEED100) ? 100 : 10));
		cmd->base.duplex = (reg & MDIO_CTRL1_FULLDPLX ||
				    speed == SPEED_10000);
	पूर्ण

	cmd->base.speed = speed;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.lp_advertising,
						lp_advertising);

	/* 10GBASE-T MDI/MDI-X */
	अगर (cmd->base.port == PORT_TP && (cmd->base.speed == SPEED_10000)) अणु
		चयन (mdio->mdio_पढ़ो(mdio->dev, mdio->prtad, MDIO_MMD_PMAPMD,
					MDIO_PMA_10GBT_SWAPPOL)) अणु
		हाल MDIO_PMA_10GBT_SWAPPOL_ABNX | MDIO_PMA_10GBT_SWAPPOL_CDNX:
			cmd->base.eth_tp_mdix = ETH_TP_MDI;
			अवरोध;
		हाल 0:
			cmd->base.eth_tp_mdix = ETH_TP_MDI_X;
			अवरोध;
		शेष:
			/* It's complicated... */
			cmd->base.eth_tp_mdix = ETH_TP_MDI_INVALID;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(mdio45_ethtool_ksettings_get_npage);

/**
 * mdio_mii_ioctl - MII ioctl पूर्णांकerface क्रम MDIO (clause 22 or 45) PHYs
 * @mdio: MDIO पूर्णांकerface
 * @mii_data: MII ioctl data काष्ठाure
 * @cmd: MII ioctl command
 *
 * Returns 0 on success, negative on error.
 */
पूर्णांक mdio_mii_ioctl(स्थिर काष्ठा mdio_अगर_info *mdio,
		   काष्ठा mii_ioctl_data *mii_data, पूर्णांक cmd)
अणु
	पूर्णांक prtad, devad;
	u16 addr = mii_data->reg_num;

	/* Validate/convert cmd to one of SIOCअणुG,Sपूर्णMIIREG */
	चयन (cmd) अणु
	हाल SIOCGMIIPHY:
		अगर (mdio->prtad == MDIO_PRTAD_NONE)
			वापस -EOPNOTSUPP;
		mii_data->phy_id = mdio->prtad;
		cmd = SIOCGMIIREG;
		अवरोध;
	हाल SIOCGMIIREG:
	हाल SIOCSMIIREG:
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	/* Validate/convert phy_id */
	अगर ((mdio->mode_support & MDIO_SUPPORTS_C45) &&
	    mdio_phy_id_is_c45(mii_data->phy_id)) अणु
		prtad = mdio_phy_id_prtad(mii_data->phy_id);
		devad = mdio_phy_id_devad(mii_data->phy_id);
	पूर्ण अन्यथा अगर ((mdio->mode_support & MDIO_SUPPORTS_C22) &&
		   mii_data->phy_id < 0x20) अणु
		prtad = mii_data->phy_id;
		devad = MDIO_DEVAD_NONE;
		addr &= 0x1f;
	पूर्ण अन्यथा अगर ((mdio->mode_support & MDIO_EMULATE_C22) &&
		   mdio->prtad != MDIO_PRTAD_NONE &&
		   mii_data->phy_id == mdio->prtad) अणु
		/* Remap commonly-used MII रेजिस्टरs. */
		prtad = mdio->prtad;
		चयन (addr) अणु
		हाल MII_BMCR:
		हाल MII_BMSR:
		हाल MII_PHYSID1:
		हाल MII_PHYSID2:
			devad = __ffs(mdio->mmds);
			अवरोध;
		हाल MII_ADVERTISE:
		हाल MII_LPA:
			अगर (!(mdio->mmds & MDIO_DEVS_AN))
				वापस -EINVAL;
			devad = MDIO_MMD_AN;
			अगर (addr == MII_ADVERTISE)
				addr = MDIO_AN_ADVERTISE;
			अन्यथा
				addr = MDIO_AN_LPA;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	अगर (cmd == SIOCGMIIREG) अणु
		पूर्णांक rc = mdio->mdio_पढ़ो(mdio->dev, prtad, devad, addr);
		अगर (rc < 0)
			वापस rc;
		mii_data->val_out = rc;
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस mdio->mdio_ग_लिखो(mdio->dev, prtad, devad, addr,
					mii_data->val_in);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(mdio_mii_ioctl);
