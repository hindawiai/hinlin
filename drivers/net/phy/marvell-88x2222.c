<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Marvell 88x2222 dual-port multi-speed ethernet transceiver.
 *
 * Supports:
 *	XAUI on the host side.
 *	1000Base-X or 10GBase-R on the line side.
 *	SGMII over 1000Base-X.
 */
#समावेश <linux/module.h>
#समावेश <linux/phy.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/delay.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/marvell_phy.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/sfp.h>
#समावेश <linux/netdevice.h>

/* Port PCS Configuration */
#घोषणा	MV_PCS_CONFIG		0xF002
#घोषणा	MV_PCS_HOST_XAUI	0x73
#घोषणा	MV_PCS_LINE_10GBR	(0x71 << 8)
#घोषणा	MV_PCS_LINE_1GBX_AN	(0x7B << 8)
#घोषणा	MV_PCS_LINE_SGMII_AN	(0x7F << 8)

/* Port Reset and Power Down */
#घोषणा	MV_PORT_RST	0xF003
#घोषणा	MV_LINE_RST_SW	BIT(15)
#घोषणा	MV_HOST_RST_SW	BIT(7)
#घोषणा	MV_PORT_RST_SW	(MV_LINE_RST_SW | MV_HOST_RST_SW)

/* PMD Receive Signal Detect */
#घोषणा	MV_RX_SIGNAL_DETECT		0x000A
#घोषणा	MV_RX_SIGNAL_DETECT_GLOBAL	BIT(0)

/* 1000Base-X/SGMII Control Register */
#घोषणा	MV_1GBX_CTRL		(0x2000 + MII_BMCR)

/* 1000BASE-X/SGMII Status Register */
#घोषणा	MV_1GBX_STAT		(0x2000 + MII_BMSR)

/* 1000Base-X Auto-Negotiation Advertisement Register */
#घोषणा	MV_1GBX_ADVERTISE	(0x2000 + MII_ADVERTISE)

/* 1000Base-X PHY Specअगरic Status Register */
#घोषणा	MV_1GBX_PHY_STAT		0xA003
#घोषणा	MV_1GBX_PHY_STAT_AN_RESOLVED	BIT(11)
#घोषणा	MV_1GBX_PHY_STAT_DUPLEX		BIT(13)
#घोषणा	MV_1GBX_PHY_STAT_SPEED100	BIT(14)
#घोषणा	MV_1GBX_PHY_STAT_SPEED1000	BIT(15)

#घोषणा	AUTONEG_TIMEOUT	3

काष्ठा mv2222_data अणु
	phy_पूर्णांकerface_t line_पूर्णांकerface;
	__ETHTOOL_DECLARE_LINK_MODE_MASK(supported);
	bool sfp_link;
पूर्ण;

/* SFI PMA transmit enable */
अटल पूर्णांक mv2222_tx_enable(काष्ठा phy_device *phydev)
अणु
	वापस phy_clear_bits_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_PMA_TXDIS,
				  MDIO_PMD_TXDIS_GLOBAL);
पूर्ण

/* SFI PMA transmit disable */
अटल पूर्णांक mv2222_tx_disable(काष्ठा phy_device *phydev)
अणु
	वापस phy_set_bits_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_PMA_TXDIS,
				MDIO_PMD_TXDIS_GLOBAL);
पूर्ण

अटल पूर्णांक mv2222_soft_reset(काष्ठा phy_device *phydev)
अणु
	पूर्णांक val, ret;

	ret = phy_ग_लिखो_mmd(phydev, MDIO_MMD_VEND2, MV_PORT_RST,
			    MV_PORT_RST_SW);
	अगर (ret < 0)
		वापस ret;

	वापस phy_पढ़ो_mmd_poll_समयout(phydev, MDIO_MMD_VEND2, MV_PORT_RST,
					 val, !(val & MV_PORT_RST_SW),
					 5000, 1000000, true);
पूर्ण

अटल पूर्णांक mv2222_disable_aneg(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret = phy_clear_bits_mmd(phydev, MDIO_MMD_PCS, MV_1GBX_CTRL,
				     BMCR_ANENABLE | BMCR_ANRESTART);
	अगर (ret < 0)
		वापस ret;

	वापस mv2222_soft_reset(phydev);
पूर्ण

अटल पूर्णांक mv2222_enable_aneg(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret = phy_set_bits_mmd(phydev, MDIO_MMD_PCS, MV_1GBX_CTRL,
				   BMCR_ANENABLE | BMCR_RESET);
	अगर (ret < 0)
		वापस ret;

	वापस mv2222_soft_reset(phydev);
पूर्ण

अटल पूर्णांक mv2222_set_sgmii_speed(काष्ठा phy_device *phydev)
अणु
	काष्ठा mv2222_data *priv = phydev->priv;

	चयन (phydev->speed) अणु
	शेष:
	हाल SPEED_1000:
		अगर ((linkmode_test_bit(ETHTOOL_LINK_MODE_1000baseT_Full_BIT,
				       priv->supported) ||
		     linkmode_test_bit(ETHTOOL_LINK_MODE_1000baseT_Half_BIT,
				       priv->supported)))
			वापस phy_modअगरy_mmd(phydev, MDIO_MMD_PCS,
					      MV_1GBX_CTRL,
					      BMCR_SPEED1000 | BMCR_SPEED100,
					      BMCR_SPEED1000);

		fallthrough;
	हाल SPEED_100:
		अगर ((linkmode_test_bit(ETHTOOL_LINK_MODE_100baseT_Full_BIT,
				       priv->supported) ||
		     linkmode_test_bit(ETHTOOL_LINK_MODE_100baseT_Half_BIT,
				       priv->supported)))
			वापस phy_modअगरy_mmd(phydev, MDIO_MMD_PCS,
					      MV_1GBX_CTRL,
					      BMCR_SPEED1000 | BMCR_SPEED100,
					      BMCR_SPEED100);
		fallthrough;
	हाल SPEED_10:
		अगर ((linkmode_test_bit(ETHTOOL_LINK_MODE_10baseT_Full_BIT,
				       priv->supported) ||
		     linkmode_test_bit(ETHTOOL_LINK_MODE_10baseT_Half_BIT,
				       priv->supported)))
			वापस phy_modअगरy_mmd(phydev, MDIO_MMD_PCS,
					      MV_1GBX_CTRL,
					      BMCR_SPEED1000 | BMCR_SPEED100,
					      BMCR_SPEED10);

		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल bool mv2222_is_10g_capable(काष्ठा phy_device *phydev)
अणु
	काष्ठा mv2222_data *priv = phydev->priv;

	वापस (linkmode_test_bit(ETHTOOL_LINK_MODE_10000baseT_Full_BIT,
				  priv->supported) ||
		linkmode_test_bit(ETHTOOL_LINK_MODE_10000baseCR_Full_BIT,
				  priv->supported) ||
		linkmode_test_bit(ETHTOOL_LINK_MODE_10000baseSR_Full_BIT,
				  priv->supported) ||
		linkmode_test_bit(ETHTOOL_LINK_MODE_10000baseLR_Full_BIT,
				  priv->supported) ||
		linkmode_test_bit(ETHTOOL_LINK_MODE_10000baseLRM_Full_BIT,
				  priv->supported) ||
		linkmode_test_bit(ETHTOOL_LINK_MODE_10000baseER_Full_BIT,
				  priv->supported));
पूर्ण

अटल bool mv2222_is_1gbx_capable(काष्ठा phy_device *phydev)
अणु
	काष्ठा mv2222_data *priv = phydev->priv;

	वापस linkmode_test_bit(ETHTOOL_LINK_MODE_1000baseX_Full_BIT,
				 priv->supported);
पूर्ण

अटल bool mv2222_is_sgmii_capable(काष्ठा phy_device *phydev)
अणु
	काष्ठा mv2222_data *priv = phydev->priv;

	वापस (linkmode_test_bit(ETHTOOL_LINK_MODE_1000baseT_Full_BIT,
				  priv->supported) ||
		linkmode_test_bit(ETHTOOL_LINK_MODE_1000baseT_Half_BIT,
				  priv->supported) ||
		linkmode_test_bit(ETHTOOL_LINK_MODE_100baseT_Full_BIT,
				  priv->supported) ||
		linkmode_test_bit(ETHTOOL_LINK_MODE_100baseT_Half_BIT,
				  priv->supported) ||
		linkmode_test_bit(ETHTOOL_LINK_MODE_10baseT_Full_BIT,
				  priv->supported) ||
		linkmode_test_bit(ETHTOOL_LINK_MODE_10baseT_Half_BIT,
				  priv->supported));
पूर्ण

अटल पूर्णांक mv2222_config_line(काष्ठा phy_device *phydev)
अणु
	काष्ठा mv2222_data *priv = phydev->priv;

	चयन (priv->line_पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_10GBASER:
		वापस phy_ग_लिखो_mmd(phydev, MDIO_MMD_VEND2, MV_PCS_CONFIG,
				     MV_PCS_HOST_XAUI | MV_PCS_LINE_10GBR);
	हाल PHY_INTERFACE_MODE_1000BASEX:
		वापस phy_ग_लिखो_mmd(phydev, MDIO_MMD_VEND2, MV_PCS_CONFIG,
				     MV_PCS_HOST_XAUI | MV_PCS_LINE_1GBX_AN);
	हाल PHY_INTERFACE_MODE_SGMII:
		वापस phy_ग_लिखो_mmd(phydev, MDIO_MMD_VEND2, MV_PCS_CONFIG,
				     MV_PCS_HOST_XAUI | MV_PCS_LINE_SGMII_AN);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/* Switch between 1G (1000Base-X/SGMII) and 10G (10GBase-R) modes */
अटल पूर्णांक mv2222_swap_line_type(काष्ठा phy_device *phydev)
अणु
	काष्ठा mv2222_data *priv = phydev->priv;
	bool changed = false;
	पूर्णांक ret;

	चयन (priv->line_पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_10GBASER:
		अगर (mv2222_is_1gbx_capable(phydev)) अणु
			priv->line_पूर्णांकerface = PHY_INTERFACE_MODE_1000BASEX;
			changed = true;
		पूर्ण

		अगर (mv2222_is_sgmii_capable(phydev)) अणु
			priv->line_पूर्णांकerface = PHY_INTERFACE_MODE_SGMII;
			changed = true;
		पूर्ण

		अवरोध;
	हाल PHY_INTERFACE_MODE_1000BASEX:
	हाल PHY_INTERFACE_MODE_SGMII:
		अगर (mv2222_is_10g_capable(phydev)) अणु
			priv->line_पूर्णांकerface = PHY_INTERFACE_MODE_10GBASER;
			changed = true;
		पूर्ण

		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (changed) अणु
		ret = mv2222_config_line(phydev);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mv2222_setup_क्रमced(काष्ठा phy_device *phydev)
अणु
	काष्ठा mv2222_data *priv = phydev->priv;
	पूर्णांक ret;

	अगर (priv->line_पूर्णांकerface == PHY_INTERFACE_MODE_10GBASER) अणु
		अगर (phydev->speed < SPEED_10000 &&
		    phydev->speed != SPEED_UNKNOWN) अणु
			ret = mv2222_swap_line_type(phydev);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण

	अगर (priv->line_पूर्णांकerface == PHY_INTERFACE_MODE_SGMII) अणु
		ret = mv2222_set_sgmii_speed(phydev);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस mv2222_disable_aneg(phydev);
पूर्ण

अटल पूर्णांक mv2222_config_aneg(काष्ठा phy_device *phydev)
अणु
	काष्ठा mv2222_data *priv = phydev->priv;
	पूर्णांक ret, adv;

	/* SFP is not present, करो nothing */
	अगर (priv->line_पूर्णांकerface == PHY_INTERFACE_MODE_NA)
		वापस 0;

	अगर (phydev->स्वतःneg == AUTONEG_DISABLE ||
	    priv->line_पूर्णांकerface == PHY_INTERFACE_MODE_10GBASER)
		वापस mv2222_setup_क्रमced(phydev);

	adv = linkmode_adv_to_mii_adv_x(priv->supported,
					ETHTOOL_LINK_MODE_1000baseX_Full_BIT);

	ret = phy_modअगरy_mmd(phydev, MDIO_MMD_PCS, MV_1GBX_ADVERTISE,
			     ADVERTISE_1000XFULL |
			     ADVERTISE_1000XPAUSE | ADVERTISE_1000XPSE_ASYM,
			     adv);
	अगर (ret < 0)
		वापस ret;

	वापस mv2222_enable_aneg(phydev);
पूर्ण

अटल पूर्णांक mv2222_aneg_करोne(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	अगर (mv2222_is_10g_capable(phydev)) अणु
		ret = phy_पढ़ो_mmd(phydev, MDIO_MMD_PCS, MDIO_STAT1);
		अगर (ret < 0)
			वापस ret;

		अगर (ret & MDIO_STAT1_LSTATUS)
			वापस 1;
	पूर्ण

	ret = phy_पढ़ो_mmd(phydev, MDIO_MMD_PCS, MV_1GBX_STAT);
	अगर (ret < 0)
		वापस ret;

	वापस (ret & BMSR_ANEGCOMPLETE);
पूर्ण

/* Returns negative on error, 0 अगर link is करोwn, 1 अगर link is up */
अटल पूर्णांक mv2222_पढ़ो_status_10g(काष्ठा phy_device *phydev)
अणु
	अटल पूर्णांक समयout;
	पूर्णांक val, link = 0;

	val = phy_पढ़ो_mmd(phydev, MDIO_MMD_PCS, MDIO_STAT1);
	अगर (val < 0)
		वापस val;

	अगर (val & MDIO_STAT1_LSTATUS) अणु
		link = 1;

		/* 10GBASE-R करो not support स्वतः-negotiation */
		phydev->स्वतःneg = AUTONEG_DISABLE;
		phydev->speed = SPEED_10000;
		phydev->duplex = DUPLEX_FULL;
	पूर्ण अन्यथा अणु
		अगर (phydev->स्वतःneg == AUTONEG_ENABLE) अणु
			समयout++;

			अगर (समयout > AUTONEG_TIMEOUT) अणु
				समयout = 0;

				val = mv2222_swap_line_type(phydev);
				अगर (val < 0)
					वापस val;

				वापस mv2222_config_aneg(phydev);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस link;
पूर्ण

/* Returns negative on error, 0 अगर link is करोwn, 1 अगर link is up */
अटल पूर्णांक mv2222_पढ़ो_status_1g(काष्ठा phy_device *phydev)
अणु
	अटल पूर्णांक समयout;
	पूर्णांक val, link = 0;

	val = phy_पढ़ो_mmd(phydev, MDIO_MMD_PCS, MV_1GBX_STAT);
	अगर (val < 0)
		वापस val;

	अगर (phydev->स्वतःneg == AUTONEG_ENABLE &&
	    !(val & BMSR_ANEGCOMPLETE)) अणु
		समयout++;

		अगर (समयout > AUTONEG_TIMEOUT) अणु
			समयout = 0;

			val = mv2222_swap_line_type(phydev);
			अगर (val < 0)
				वापस val;

			वापस mv2222_config_aneg(phydev);
		पूर्ण

		वापस 0;
	पूर्ण

	अगर (!(val & BMSR_LSTATUS))
		वापस 0;

	link = 1;

	val = phy_पढ़ो_mmd(phydev, MDIO_MMD_PCS, MV_1GBX_PHY_STAT);
	अगर (val < 0)
		वापस val;

	अगर (val & MV_1GBX_PHY_STAT_AN_RESOLVED) अणु
		अगर (val & MV_1GBX_PHY_STAT_DUPLEX)
			phydev->duplex = DUPLEX_FULL;
		अन्यथा
			phydev->duplex = DUPLEX_HALF;

		अगर (val & MV_1GBX_PHY_STAT_SPEED1000)
			phydev->speed = SPEED_1000;
		अन्यथा अगर (val & MV_1GBX_PHY_STAT_SPEED100)
			phydev->speed = SPEED_100;
		अन्यथा
			phydev->speed = SPEED_10;
	पूर्ण

	वापस link;
पूर्ण

अटल bool mv2222_link_is_operational(काष्ठा phy_device *phydev)
अणु
	काष्ठा mv2222_data *priv = phydev->priv;
	पूर्णांक val;

	val = phy_पढ़ो_mmd(phydev, MDIO_MMD_PMAPMD, MV_RX_SIGNAL_DETECT);
	अगर (val < 0 || !(val & MV_RX_SIGNAL_DETECT_GLOBAL))
		वापस false;

	अगर (phydev->sfp_bus && !priv->sfp_link)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक mv2222_पढ़ो_status(काष्ठा phy_device *phydev)
अणु
	काष्ठा mv2222_data *priv = phydev->priv;
	पूर्णांक link;

	phydev->link = 0;
	phydev->speed = SPEED_UNKNOWN;
	phydev->duplex = DUPLEX_UNKNOWN;

	अगर (!mv2222_link_is_operational(phydev))
		वापस 0;

	अगर (priv->line_पूर्णांकerface == PHY_INTERFACE_MODE_10GBASER)
		link = mv2222_पढ़ो_status_10g(phydev);
	अन्यथा
		link = mv2222_पढ़ो_status_1g(phydev);

	अगर (link < 0)
		वापस link;

	phydev->link = link;

	वापस 0;
पूर्ण

अटल पूर्णांक mv2222_resume(काष्ठा phy_device *phydev)
अणु
	वापस mv2222_tx_enable(phydev);
पूर्ण

अटल पूर्णांक mv2222_suspend(काष्ठा phy_device *phydev)
अणु
	वापस mv2222_tx_disable(phydev);
पूर्ण

अटल पूर्णांक mv2222_get_features(काष्ठा phy_device *phydev)
अणु
	/* All supported linkmodes are set at probe */

	वापस 0;
पूर्ण

अटल पूर्णांक mv2222_config_init(काष्ठा phy_device *phydev)
अणु
	अगर (phydev->पूर्णांकerface != PHY_INTERFACE_MODE_XAUI)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक mv2222_sfp_insert(व्योम *upstream, स्थिर काष्ठा sfp_eeprom_id *id)
अणु
	काष्ठा phy_device *phydev = upstream;
	phy_पूर्णांकerface_t sfp_पूर्णांकerface;
	काष्ठा mv2222_data *priv;
	काष्ठा device *dev;
	पूर्णांक ret;

	__ETHTOOL_DECLARE_LINK_MODE_MASK(sfp_supported) = अणु 0, पूर्ण;

	priv = (काष्ठा mv2222_data *)phydev->priv;
	dev = &phydev->mdio.dev;

	sfp_parse_support(phydev->sfp_bus, id, sfp_supported);
	sfp_पूर्णांकerface = sfp_select_पूर्णांकerface(phydev->sfp_bus, sfp_supported);

	dev_info(dev, "%s SFP module inserted\n", phy_modes(sfp_पूर्णांकerface));

	अगर (sfp_पूर्णांकerface != PHY_INTERFACE_MODE_10GBASER &&
	    sfp_पूर्णांकerface != PHY_INTERFACE_MODE_1000BASEX &&
	    sfp_पूर्णांकerface != PHY_INTERFACE_MODE_SGMII) अणु
		dev_err(dev, "Incompatible SFP module inserted\n");

		वापस -EINVAL;
	पूर्ण

	priv->line_पूर्णांकerface = sfp_पूर्णांकerface;
	linkmode_and(priv->supported, phydev->supported, sfp_supported);

	ret = mv2222_config_line(phydev);
	अगर (ret < 0)
		वापस ret;

	अगर (mutex_trylock(&phydev->lock)) अणु
		ret = mv2222_config_aneg(phydev);
		mutex_unlock(&phydev->lock);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम mv2222_sfp_हटाओ(व्योम *upstream)
अणु
	काष्ठा phy_device *phydev = upstream;
	काष्ठा mv2222_data *priv;

	priv = (काष्ठा mv2222_data *)phydev->priv;

	priv->line_पूर्णांकerface = PHY_INTERFACE_MODE_NA;
	linkmode_zero(priv->supported);
पूर्ण

अटल व्योम mv2222_sfp_link_up(व्योम *upstream)
अणु
	काष्ठा phy_device *phydev = upstream;
	काष्ठा mv2222_data *priv;

	priv = phydev->priv;
	priv->sfp_link = true;
पूर्ण

अटल व्योम mv2222_sfp_link_करोwn(व्योम *upstream)
अणु
	काष्ठा phy_device *phydev = upstream;
	काष्ठा mv2222_data *priv;

	priv = phydev->priv;
	priv->sfp_link = false;
पूर्ण

अटल स्थिर काष्ठा sfp_upstream_ops sfp_phy_ops = अणु
	.module_insert = mv2222_sfp_insert,
	.module_हटाओ = mv2222_sfp_हटाओ,
	.link_up = mv2222_sfp_link_up,
	.link_करोwn = mv2222_sfp_link_करोwn,
	.attach = phy_sfp_attach,
	.detach = phy_sfp_detach,
पूर्ण;

अटल पूर्णांक mv2222_probe(काष्ठा phy_device *phydev)
अणु
	काष्ठा device *dev = &phydev->mdio.dev;
	काष्ठा mv2222_data *priv = शून्य;

	__ETHTOOL_DECLARE_LINK_MODE_MASK(supported) = अणु 0, पूर्ण;

	linkmode_set_bit(ETHTOOL_LINK_MODE_Autoneg_BIT, supported);
	linkmode_set_bit(ETHTOOL_LINK_MODE_Pause_BIT, supported);
	linkmode_set_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT, supported);
	linkmode_set_bit(ETHTOOL_LINK_MODE_FIBRE_BIT, supported);
	linkmode_set_bit(ETHTOOL_LINK_MODE_TP_BIT, supported);
	linkmode_set_bit(ETHTOOL_LINK_MODE_10baseT_Half_BIT, supported);
	linkmode_set_bit(ETHTOOL_LINK_MODE_10baseT_Full_BIT, supported);
	linkmode_set_bit(ETHTOOL_LINK_MODE_100baseT_Half_BIT, supported);
	linkmode_set_bit(ETHTOOL_LINK_MODE_100baseT_Full_BIT, supported);
	linkmode_set_bit(ETHTOOL_LINK_MODE_1000baseT_Half_BIT, supported);
	linkmode_set_bit(ETHTOOL_LINK_MODE_1000baseT_Full_BIT, supported);
	linkmode_set_bit(ETHTOOL_LINK_MODE_1000baseX_Full_BIT, supported);
	linkmode_set_bit(ETHTOOL_LINK_MODE_10000baseT_Full_BIT, supported);
	linkmode_set_bit(ETHTOOL_LINK_MODE_10000baseCR_Full_BIT, supported);
	linkmode_set_bit(ETHTOOL_LINK_MODE_10000baseSR_Full_BIT, supported);
	linkmode_set_bit(ETHTOOL_LINK_MODE_10000baseLR_Full_BIT, supported);
	linkmode_set_bit(ETHTOOL_LINK_MODE_10000baseLRM_Full_BIT, supported);
	linkmode_set_bit(ETHTOOL_LINK_MODE_10000baseER_Full_BIT, supported);

	linkmode_copy(phydev->supported, supported);

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->line_पूर्णांकerface = PHY_INTERFACE_MODE_NA;
	phydev->priv = priv;

	वापस phy_sfp_probe(phydev, &sfp_phy_ops);
पूर्ण

अटल काष्ठा phy_driver mv2222_drivers[] = अणु
	अणु
		.phy_id = MARVELL_PHY_ID_88X2222,
		.phy_id_mask = MARVELL_PHY_ID_MASK,
		.name = "Marvell 88X2222",
		.get_features = mv2222_get_features,
		.soft_reset = mv2222_soft_reset,
		.config_init = mv2222_config_init,
		.config_aneg = mv2222_config_aneg,
		.aneg_करोne = mv2222_aneg_करोne,
		.probe = mv2222_probe,
		.suspend = mv2222_suspend,
		.resume = mv2222_resume,
		.पढ़ो_status = mv2222_पढ़ो_status,
	पूर्ण,
पूर्ण;
module_phy_driver(mv2222_drivers);

अटल काष्ठा mdio_device_id __maybe_unused mv2222_tbl[] = अणु
	अणु MARVELL_PHY_ID_88X2222, MARVELL_PHY_ID_MASK पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(mdio, mv2222_tbl);

MODULE_DESCRIPTION("Marvell 88x2222 ethernet transceiver driver");
MODULE_LICENSE("GPL");
