<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/*
 * Driver क्रम Microsemi VSC85xx PHYs
 *
 * Author: Nagaraju Lakkaraju
 * License: Dual MIT/GPL
 * Copyright (c) 2016 Microsemi Corporation
 */

#समावेश <linux/firmware.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/mii.h>
#समावेश <linux/phy.h>
#समावेश <linux/of.h>
#समावेश <linux/netdevice.h>
#समावेश <dt-bindings/net/mscc-phy-vsc8531.h>
#समावेश "mscc_serdes.h"
#समावेश "mscc.h"

अटल स्थिर काष्ठा vsc85xx_hw_stat vsc85xx_hw_stats[] = अणु
	अणु
		.string	= "phy_receive_errors",
		.reg	= MSCC_PHY_ERR_RX_CNT,
		.page	= MSCC_PHY_PAGE_STANDARD,
		.mask	= ERR_CNT_MASK,
	पूर्ण, अणु
		.string	= "phy_false_carrier",
		.reg	= MSCC_PHY_ERR_FALSE_CARRIER_CNT,
		.page	= MSCC_PHY_PAGE_STANDARD,
		.mask	= ERR_CNT_MASK,
	पूर्ण, अणु
		.string	= "phy_cu_media_link_disconnect",
		.reg	= MSCC_PHY_ERR_LINK_DISCONNECT_CNT,
		.page	= MSCC_PHY_PAGE_STANDARD,
		.mask	= ERR_CNT_MASK,
	पूर्ण, अणु
		.string	= "phy_cu_media_crc_good_count",
		.reg	= MSCC_PHY_CU_MEDIA_CRC_VALID_CNT,
		.page	= MSCC_PHY_PAGE_EXTENDED,
		.mask	= VALID_CRC_CNT_CRC_MASK,
	पूर्ण, अणु
		.string	= "phy_cu_media_crc_error_count",
		.reg	= MSCC_PHY_EXT_PHY_CNTL_4,
		.page	= MSCC_PHY_PAGE_EXTENDED,
		.mask	= ERR_CNT_MASK,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vsc85xx_hw_stat vsc8584_hw_stats[] = अणु
	अणु
		.string	= "phy_receive_errors",
		.reg	= MSCC_PHY_ERR_RX_CNT,
		.page	= MSCC_PHY_PAGE_STANDARD,
		.mask	= ERR_CNT_MASK,
	पूर्ण, अणु
		.string	= "phy_false_carrier",
		.reg	= MSCC_PHY_ERR_FALSE_CARRIER_CNT,
		.page	= MSCC_PHY_PAGE_STANDARD,
		.mask	= ERR_CNT_MASK,
	पूर्ण, अणु
		.string	= "phy_cu_media_link_disconnect",
		.reg	= MSCC_PHY_ERR_LINK_DISCONNECT_CNT,
		.page	= MSCC_PHY_PAGE_STANDARD,
		.mask	= ERR_CNT_MASK,
	पूर्ण, अणु
		.string	= "phy_cu_media_crc_good_count",
		.reg	= MSCC_PHY_CU_MEDIA_CRC_VALID_CNT,
		.page	= MSCC_PHY_PAGE_EXTENDED,
		.mask	= VALID_CRC_CNT_CRC_MASK,
	पूर्ण, अणु
		.string	= "phy_cu_media_crc_error_count",
		.reg	= MSCC_PHY_EXT_PHY_CNTL_4,
		.page	= MSCC_PHY_PAGE_EXTENDED,
		.mask	= ERR_CNT_MASK,
	पूर्ण, अणु
		.string	= "phy_serdes_tx_good_pkt_count",
		.reg	= MSCC_PHY_SERDES_TX_VALID_CNT,
		.page	= MSCC_PHY_PAGE_EXTENDED_3,
		.mask	= VALID_CRC_CNT_CRC_MASK,
	पूर्ण, अणु
		.string	= "phy_serdes_tx_bad_crc_count",
		.reg	= MSCC_PHY_SERDES_TX_CRC_ERR_CNT,
		.page	= MSCC_PHY_PAGE_EXTENDED_3,
		.mask	= ERR_CNT_MASK,
	पूर्ण, अणु
		.string	= "phy_serdes_rx_good_pkt_count",
		.reg	= MSCC_PHY_SERDES_RX_VALID_CNT,
		.page	= MSCC_PHY_PAGE_EXTENDED_3,
		.mask	= VALID_CRC_CNT_CRC_MASK,
	पूर्ण, अणु
		.string	= "phy_serdes_rx_bad_crc_count",
		.reg	= MSCC_PHY_SERDES_RX_CRC_ERR_CNT,
		.page	= MSCC_PHY_PAGE_EXTENDED_3,
		.mask	= ERR_CNT_MASK,
	पूर्ण,
पूर्ण;

#अगर IS_ENABLED(CONFIG_OF_MDIO)
अटल स्थिर काष्ठा vsc8531_edge_rate_table edge_table[] = अणु
	अणुMSCC_VDDMAC_3300, अणु 0, 2,  4,  7, 10, 17, 29, 53पूर्ण पूर्ण,
	अणुMSCC_VDDMAC_2500, अणु 0, 3,  6, 10, 14, 23, 37, 63पूर्ण पूर्ण,
	अणुMSCC_VDDMAC_1800, अणु 0, 5,  9, 16, 23, 35, 52, 76पूर्ण पूर्ण,
	अणुMSCC_VDDMAC_1500, अणु 0, 6, 14, 21, 29, 42, 58, 77पूर्ण पूर्ण,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक vsc85xx_phy_पढ़ो_page(काष्ठा phy_device *phydev)
अणु
	वापस __phy_पढ़ो(phydev, MSCC_EXT_PAGE_ACCESS);
पूर्ण

अटल पूर्णांक vsc85xx_phy_ग_लिखो_page(काष्ठा phy_device *phydev, पूर्णांक page)
अणु
	वापस __phy_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, page);
पूर्ण

अटल पूर्णांक vsc85xx_get_sset_count(काष्ठा phy_device *phydev)
अणु
	काष्ठा vsc8531_निजी *priv = phydev->priv;

	अगर (!priv)
		वापस 0;

	वापस priv->nstats;
पूर्ण

अटल व्योम vsc85xx_get_strings(काष्ठा phy_device *phydev, u8 *data)
अणु
	काष्ठा vsc8531_निजी *priv = phydev->priv;
	पूर्णांक i;

	अगर (!priv)
		वापस;

	क्रम (i = 0; i < priv->nstats; i++)
		strlcpy(data + i * ETH_GSTRING_LEN, priv->hw_stats[i].string,
			ETH_GSTRING_LEN);
पूर्ण

अटल u64 vsc85xx_get_stat(काष्ठा phy_device *phydev, पूर्णांक i)
अणु
	काष्ठा vsc8531_निजी *priv = phydev->priv;
	पूर्णांक val;

	val = phy_पढ़ो_paged(phydev, priv->hw_stats[i].page,
			     priv->hw_stats[i].reg);
	अगर (val < 0)
		वापस U64_MAX;

	val = val & priv->hw_stats[i].mask;
	priv->stats[i] += val;

	वापस priv->stats[i];
पूर्ण

अटल व्योम vsc85xx_get_stats(काष्ठा phy_device *phydev,
			      काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा vsc8531_निजी *priv = phydev->priv;
	पूर्णांक i;

	अगर (!priv)
		वापस;

	क्रम (i = 0; i < priv->nstats; i++)
		data[i] = vsc85xx_get_stat(phydev, i);
पूर्ण

अटल पूर्णांक vsc85xx_led_cntl_set(काष्ठा phy_device *phydev,
				u8 led_num,
				u8 mode)
अणु
	पूर्णांक rc;
	u16 reg_val;

	mutex_lock(&phydev->lock);
	reg_val = phy_पढ़ो(phydev, MSCC_PHY_LED_MODE_SEL);
	reg_val &= ~LED_MODE_SEL_MASK(led_num);
	reg_val |= LED_MODE_SEL(led_num, (u16)mode);
	rc = phy_ग_लिखो(phydev, MSCC_PHY_LED_MODE_SEL, reg_val);
	mutex_unlock(&phydev->lock);

	वापस rc;
पूर्ण

अटल पूर्णांक vsc85xx_mdix_get(काष्ठा phy_device *phydev, u8 *mdix)
अणु
	u16 reg_val;

	reg_val = phy_पढ़ो(phydev, MSCC_PHY_DEV_AUX_CNTL);
	अगर (reg_val & HP_AUTO_MDIX_X_OVER_IND_MASK)
		*mdix = ETH_TP_MDI_X;
	अन्यथा
		*mdix = ETH_TP_MDI;

	वापस 0;
पूर्ण

अटल पूर्णांक vsc85xx_mdix_set(काष्ठा phy_device *phydev, u8 mdix)
अणु
	पूर्णांक rc;
	u16 reg_val;

	reg_val = phy_पढ़ो(phydev, MSCC_PHY_BYPASS_CONTROL);
	अगर (mdix == ETH_TP_MDI || mdix == ETH_TP_MDI_X) अणु
		reg_val |= (DISABLE_PAIR_SWAP_CORR_MASK |
			    DISABLE_POLARITY_CORR_MASK  |
			    DISABLE_HP_AUTO_MDIX_MASK);
	पूर्ण अन्यथा अणु
		reg_val &= ~(DISABLE_PAIR_SWAP_CORR_MASK |
			     DISABLE_POLARITY_CORR_MASK  |
			     DISABLE_HP_AUTO_MDIX_MASK);
	पूर्ण
	rc = phy_ग_लिखो(phydev, MSCC_PHY_BYPASS_CONTROL, reg_val);
	अगर (rc)
		वापस rc;

	reg_val = 0;

	अगर (mdix == ETH_TP_MDI)
		reg_val = FORCE_MDI_CROSSOVER_MDI;
	अन्यथा अगर (mdix == ETH_TP_MDI_X)
		reg_val = FORCE_MDI_CROSSOVER_MDIX;

	rc = phy_modअगरy_paged(phydev, MSCC_PHY_PAGE_EXTENDED,
			      MSCC_PHY_EXT_MODE_CNTL, FORCE_MDI_CROSSOVER_MASK,
			      reg_val);
	अगर (rc < 0)
		वापस rc;

	वापस genphy_restart_aneg(phydev);
पूर्ण

अटल पूर्णांक vsc85xx_करोwnshअगरt_get(काष्ठा phy_device *phydev, u8 *count)
अणु
	पूर्णांक reg_val;

	reg_val = phy_पढ़ो_paged(phydev, MSCC_PHY_PAGE_EXTENDED,
				 MSCC_PHY_ACTIPHY_CNTL);
	अगर (reg_val < 0)
		वापस reg_val;

	reg_val &= DOWNSHIFT_CNTL_MASK;
	अगर (!(reg_val & DOWNSHIFT_EN))
		*count = DOWNSHIFT_DEV_DISABLE;
	अन्यथा
		*count = ((reg_val & ~DOWNSHIFT_EN) >> DOWNSHIFT_CNTL_POS) + 2;

	वापस 0;
पूर्ण

अटल पूर्णांक vsc85xx_करोwnshअगरt_set(काष्ठा phy_device *phydev, u8 count)
अणु
	अगर (count == DOWNSHIFT_DEV_DEFAULT_COUNT) अणु
		/* Default करोwnshअगरt count 3 (i.e. Bit3:2 = 0b01) */
		count = ((1 << DOWNSHIFT_CNTL_POS) | DOWNSHIFT_EN);
	पूर्ण अन्यथा अगर (count > DOWNSHIFT_COUNT_MAX || count == 1) अणु
		phydev_err(phydev, "Downshift count should be 2,3,4 or 5\n");
		वापस -दुस्फल;
	पूर्ण अन्यथा अगर (count) अणु
		/* Downshअगरt count is either 2,3,4 or 5 */
		count = (((count - 2) << DOWNSHIFT_CNTL_POS) | DOWNSHIFT_EN);
	पूर्ण

	वापस phy_modअगरy_paged(phydev, MSCC_PHY_PAGE_EXTENDED,
				MSCC_PHY_ACTIPHY_CNTL, DOWNSHIFT_CNTL_MASK,
				count);
पूर्ण

अटल पूर्णांक vsc85xx_wol_set(काष्ठा phy_device *phydev,
			   काष्ठा ethtool_wolinfo *wol)
अणु
	पूर्णांक rc;
	u16 reg_val;
	u8  i;
	u16 pwd[3] = अणु0, 0, 0पूर्ण;
	काष्ठा ethtool_wolinfo *wol_conf = wol;
	u8 *mac_addr = phydev->attached_dev->dev_addr;

	mutex_lock(&phydev->lock);
	rc = phy_select_page(phydev, MSCC_PHY_PAGE_EXTENDED_2);
	अगर (rc < 0) अणु
		rc = phy_restore_page(phydev, rc, rc);
		जाओ out_unlock;
	पूर्ण

	अगर (wol->wolopts & WAKE_MAGIC) अणु
		/* Store the device address क्रम the magic packet */
		क्रम (i = 0; i < ARRAY_SIZE(pwd); i++)
			pwd[i] = mac_addr[5 - (i * 2 + 1)] << 8 |
				 mac_addr[5 - i * 2];
		__phy_ग_लिखो(phydev, MSCC_PHY_WOL_LOWER_MAC_ADDR, pwd[0]);
		__phy_ग_लिखो(phydev, MSCC_PHY_WOL_MID_MAC_ADDR, pwd[1]);
		__phy_ग_लिखो(phydev, MSCC_PHY_WOL_UPPER_MAC_ADDR, pwd[2]);
	पूर्ण अन्यथा अणु
		__phy_ग_लिखो(phydev, MSCC_PHY_WOL_LOWER_MAC_ADDR, 0);
		__phy_ग_लिखो(phydev, MSCC_PHY_WOL_MID_MAC_ADDR, 0);
		__phy_ग_लिखो(phydev, MSCC_PHY_WOL_UPPER_MAC_ADDR, 0);
	पूर्ण

	अगर (wol_conf->wolopts & WAKE_MAGICSECURE) अणु
		क्रम (i = 0; i < ARRAY_SIZE(pwd); i++)
			pwd[i] = wol_conf->sopass[5 - (i * 2 + 1)] << 8 |
				 wol_conf->sopass[5 - i * 2];
		__phy_ग_लिखो(phydev, MSCC_PHY_WOL_LOWER_PASSWD, pwd[0]);
		__phy_ग_लिखो(phydev, MSCC_PHY_WOL_MID_PASSWD, pwd[1]);
		__phy_ग_लिखो(phydev, MSCC_PHY_WOL_UPPER_PASSWD, pwd[2]);
	पूर्ण अन्यथा अणु
		__phy_ग_लिखो(phydev, MSCC_PHY_WOL_LOWER_PASSWD, 0);
		__phy_ग_लिखो(phydev, MSCC_PHY_WOL_MID_PASSWD, 0);
		__phy_ग_लिखो(phydev, MSCC_PHY_WOL_UPPER_PASSWD, 0);
	पूर्ण

	reg_val = __phy_पढ़ो(phydev, MSCC_PHY_WOL_MAC_CONTROL);
	अगर (wol_conf->wolopts & WAKE_MAGICSECURE)
		reg_val |= SECURE_ON_ENABLE;
	अन्यथा
		reg_val &= ~SECURE_ON_ENABLE;
	__phy_ग_लिखो(phydev, MSCC_PHY_WOL_MAC_CONTROL, reg_val);

	rc = phy_restore_page(phydev, rc, rc > 0 ? 0 : rc);
	अगर (rc < 0)
		जाओ out_unlock;

	अगर (wol->wolopts & WAKE_MAGIC) अणु
		/* Enable the WOL पूर्णांकerrupt */
		reg_val = phy_पढ़ो(phydev, MII_VSC85XX_INT_MASK);
		reg_val |= MII_VSC85XX_INT_MASK_WOL;
		rc = phy_ग_लिखो(phydev, MII_VSC85XX_INT_MASK, reg_val);
		अगर (rc)
			जाओ out_unlock;
	पूर्ण अन्यथा अणु
		/* Disable the WOL पूर्णांकerrupt */
		reg_val = phy_पढ़ो(phydev, MII_VSC85XX_INT_MASK);
		reg_val &= (~MII_VSC85XX_INT_MASK_WOL);
		rc = phy_ग_लिखो(phydev, MII_VSC85XX_INT_MASK, reg_val);
		अगर (rc)
			जाओ out_unlock;
	पूर्ण
	/* Clear WOL iterrupt status */
	reg_val = phy_पढ़ो(phydev, MII_VSC85XX_INT_STATUS);

out_unlock:
	mutex_unlock(&phydev->lock);

	वापस rc;
पूर्ण

अटल व्योम vsc85xx_wol_get(काष्ठा phy_device *phydev,
			    काष्ठा ethtool_wolinfo *wol)
अणु
	पूर्णांक rc;
	u16 reg_val;
	u8  i;
	u16 pwd[3] = अणु0, 0, 0पूर्ण;
	काष्ठा ethtool_wolinfo *wol_conf = wol;

	mutex_lock(&phydev->lock);
	rc = phy_select_page(phydev, MSCC_PHY_PAGE_EXTENDED_2);
	अगर (rc < 0)
		जाओ out_unlock;

	reg_val = __phy_पढ़ो(phydev, MSCC_PHY_WOL_MAC_CONTROL);
	अगर (reg_val & SECURE_ON_ENABLE)
		wol_conf->wolopts |= WAKE_MAGICSECURE;
	अगर (wol_conf->wolopts & WAKE_MAGICSECURE) अणु
		pwd[0] = __phy_पढ़ो(phydev, MSCC_PHY_WOL_LOWER_PASSWD);
		pwd[1] = __phy_पढ़ो(phydev, MSCC_PHY_WOL_MID_PASSWD);
		pwd[2] = __phy_पढ़ो(phydev, MSCC_PHY_WOL_UPPER_PASSWD);
		क्रम (i = 0; i < ARRAY_SIZE(pwd); i++) अणु
			wol_conf->sopass[5 - i * 2] = pwd[i] & 0x00ff;
			wol_conf->sopass[5 - (i * 2 + 1)] = (pwd[i] & 0xff00)
							    >> 8;
		पूर्ण
	पूर्ण

out_unlock:
	phy_restore_page(phydev, rc, rc > 0 ? 0 : rc);
	mutex_unlock(&phydev->lock);
पूर्ण

#अगर IS_ENABLED(CONFIG_OF_MDIO)
अटल पूर्णांक vsc85xx_edge_rate_magic_get(काष्ठा phy_device *phydev)
अणु
	u32 vdd, sd;
	पूर्णांक i, j;
	काष्ठा device *dev = &phydev->mdio.dev;
	काष्ठा device_node *of_node = dev->of_node;
	u8 sd_array_size = ARRAY_SIZE(edge_table[0].slowकरोwn);

	अगर (!of_node)
		वापस -ENODEV;

	अगर (of_property_पढ़ो_u32(of_node, "vsc8531,vddmac", &vdd))
		vdd = MSCC_VDDMAC_3300;

	अगर (of_property_पढ़ो_u32(of_node, "vsc8531,edge-slowdown", &sd))
		sd = 0;

	क्रम (i = 0; i < ARRAY_SIZE(edge_table); i++)
		अगर (edge_table[i].vddmac == vdd)
			क्रम (j = 0; j < sd_array_size; j++)
				अगर (edge_table[i].slowकरोwn[j] == sd)
					वापस (sd_array_size - j - 1);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक vsc85xx_dt_led_mode_get(काष्ठा phy_device *phydev,
				   अक्षर *led,
				   u32 शेष_mode)
अणु
	काष्ठा vsc8531_निजी *priv = phydev->priv;
	काष्ठा device *dev = &phydev->mdio.dev;
	काष्ठा device_node *of_node = dev->of_node;
	u32 led_mode;
	पूर्णांक err;

	अगर (!of_node)
		वापस -ENODEV;

	led_mode = शेष_mode;
	err = of_property_पढ़ो_u32(of_node, led, &led_mode);
	अगर (!err && !(BIT(led_mode) & priv->supp_led_modes)) अणु
		phydev_err(phydev, "DT %s invalid\n", led);
		वापस -EINVAL;
	पूर्ण

	वापस led_mode;
पूर्ण

#अन्यथा
अटल पूर्णांक vsc85xx_edge_rate_magic_get(काष्ठा phy_device *phydev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक vsc85xx_dt_led_mode_get(काष्ठा phy_device *phydev,
				   अक्षर *led,
				   u8 शेष_mode)
अणु
	वापस शेष_mode;
पूर्ण
#पूर्ण_अगर /* CONFIG_OF_MDIO */

अटल पूर्णांक vsc85xx_dt_led_modes_get(काष्ठा phy_device *phydev,
				    u32 *शेष_mode)
अणु
	काष्ठा vsc8531_निजी *priv = phydev->priv;
	अक्षर led_dt_prop[28];
	पूर्णांक i, ret;

	क्रम (i = 0; i < priv->nleds; i++) अणु
		ret = प्र_लिखो(led_dt_prop, "vsc8531,led-%d-mode", i);
		अगर (ret < 0)
			वापस ret;

		ret = vsc85xx_dt_led_mode_get(phydev, led_dt_prop,
					      शेष_mode[i]);
		अगर (ret < 0)
			वापस ret;
		priv->leds_mode[i] = ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vsc85xx_edge_rate_cntl_set(काष्ठा phy_device *phydev, u8 edge_rate)
अणु
	पूर्णांक rc;

	mutex_lock(&phydev->lock);
	rc = phy_modअगरy_paged(phydev, MSCC_PHY_PAGE_EXTENDED_2,
			      MSCC_PHY_WOL_MAC_CONTROL, EDGE_RATE_CNTL_MASK,
			      edge_rate << EDGE_RATE_CNTL_POS);
	mutex_unlock(&phydev->lock);

	वापस rc;
पूर्ण

अटल पूर्णांक vsc85xx_mac_अगर_set(काष्ठा phy_device *phydev,
			      phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	पूर्णांक rc;
	u16 reg_val;

	mutex_lock(&phydev->lock);
	reg_val = phy_पढ़ो(phydev, MSCC_PHY_EXT_PHY_CNTL_1);
	reg_val &= ~(MAC_IF_SELECTION_MASK);
	चयन (पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
	हाल PHY_INTERFACE_MODE_RGMII_ID:
	हाल PHY_INTERFACE_MODE_RGMII:
		reg_val |= (MAC_IF_SELECTION_RGMII << MAC_IF_SELECTION_POS);
		अवरोध;
	हाल PHY_INTERFACE_MODE_RMII:
		reg_val |= (MAC_IF_SELECTION_RMII << MAC_IF_SELECTION_POS);
		अवरोध;
	हाल PHY_INTERFACE_MODE_MII:
	हाल PHY_INTERFACE_MODE_GMII:
		reg_val |= (MAC_IF_SELECTION_GMII << MAC_IF_SELECTION_POS);
		अवरोध;
	शेष:
		rc = -EINVAL;
		जाओ out_unlock;
	पूर्ण
	rc = phy_ग_लिखो(phydev, MSCC_PHY_EXT_PHY_CNTL_1, reg_val);
	अगर (rc)
		जाओ out_unlock;

	rc = genphy_soft_reset(phydev);

out_unlock:
	mutex_unlock(&phydev->lock);

	वापस rc;
पूर्ण

/* Set the RGMII RX and TX घड़ी skews inभागidually, according to the PHY
 * पूर्णांकerface type, to:
 *  * 0.2 ns (their शेष, and lowest, hardware value) अगर delays should
 *    not be enabled
 *  * 2.0 ns (which causes the data to be sampled at exactly half way between
 *    घड़ी transitions at 1000 Mbps) अगर delays should be enabled
 */
अटल पूर्णांक vsc85xx_rgmii_set_skews(काष्ठा phy_device *phydev, u32 rgmii_cntl,
				   u16 rgmii_rx_delay_mask,
				   u16 rgmii_tx_delay_mask)
अणु
	u16 rgmii_rx_delay_pos = ffs(rgmii_rx_delay_mask) - 1;
	u16 rgmii_tx_delay_pos = ffs(rgmii_tx_delay_mask) - 1;
	u16 reg_val = 0;
	पूर्णांक rc;

	mutex_lock(&phydev->lock);

	अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_RXID ||
	    phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_ID)
		reg_val |= RGMII_CLK_DELAY_2_0_NS << rgmii_rx_delay_pos;
	अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_TXID ||
	    phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_ID)
		reg_val |= RGMII_CLK_DELAY_2_0_NS << rgmii_tx_delay_pos;

	rc = phy_modअगरy_paged(phydev, MSCC_PHY_PAGE_EXTENDED_2,
			      rgmii_cntl,
			      rgmii_rx_delay_mask | rgmii_tx_delay_mask,
			      reg_val);

	mutex_unlock(&phydev->lock);

	वापस rc;
पूर्ण

अटल पूर्णांक vsc85xx_शेष_config(काष्ठा phy_device *phydev)
अणु
	पूर्णांक rc;

	phydev->mdix_ctrl = ETH_TP_MDI_AUTO;

	अगर (phy_पूर्णांकerface_mode_is_rgmii(phydev->पूर्णांकerface)) अणु
		rc = vsc85xx_rgmii_set_skews(phydev, VSC8502_RGMII_CNTL,
					     VSC8502_RGMII_RX_DELAY_MASK,
					     VSC8502_RGMII_TX_DELAY_MASK);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vsc85xx_get_tunable(काष्ठा phy_device *phydev,
			       काष्ठा ethtool_tunable *tuna, व्योम *data)
अणु
	चयन (tuna->id) अणु
	हाल ETHTOOL_PHY_DOWNSHIFT:
		वापस vsc85xx_करोwnshअगरt_get(phydev, (u8 *)data);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक vsc85xx_set_tunable(काष्ठा phy_device *phydev,
			       काष्ठा ethtool_tunable *tuna,
			       स्थिर व्योम *data)
अणु
	चयन (tuna->id) अणु
	हाल ETHTOOL_PHY_DOWNSHIFT:
		वापस vsc85xx_करोwnshअगरt_set(phydev, *(u8 *)data);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/* mdiobus lock should be locked when using this function */
अटल व्योम vsc85xx_tr_ग_लिखो(काष्ठा phy_device *phydev, u16 addr, u32 val)
अणु
	__phy_ग_लिखो(phydev, MSCC_PHY_TR_MSB, val >> 16);
	__phy_ग_लिखो(phydev, MSCC_PHY_TR_LSB, val & GENMASK(15, 0));
	__phy_ग_लिखो(phydev, MSCC_PHY_TR_CNTL, TR_WRITE | TR_ADDR(addr));
पूर्ण

अटल पूर्णांक vsc8531_pre_init_seq_set(काष्ठा phy_device *phydev)
अणु
	पूर्णांक rc;
	अटल स्थिर काष्ठा reg_val init_seq[] = अणु
		अणु0x0f90, 0x00688980पूर्ण,
		अणु0x0696, 0x00000003पूर्ण,
		अणु0x07fa, 0x0050100fपूर्ण,
		अणु0x1686, 0x00000004पूर्ण,
	पूर्ण;
	अचिन्हित पूर्णांक i;
	पूर्णांक oldpage;

	rc = phy_modअगरy_paged(phydev, MSCC_PHY_PAGE_STANDARD,
			      MSCC_PHY_EXT_CNTL_STATUS, SMI_BROADCAST_WR_EN,
			      SMI_BROADCAST_WR_EN);
	अगर (rc < 0)
		वापस rc;
	rc = phy_modअगरy_paged(phydev, MSCC_PHY_PAGE_TEST,
			      MSCC_PHY_TEST_PAGE_24, 0, 0x0400);
	अगर (rc < 0)
		वापस rc;
	rc = phy_modअगरy_paged(phydev, MSCC_PHY_PAGE_TEST,
			      MSCC_PHY_TEST_PAGE_5, 0x0a00, 0x0e00);
	अगर (rc < 0)
		वापस rc;
	rc = phy_modअगरy_paged(phydev, MSCC_PHY_PAGE_TEST,
			      MSCC_PHY_TEST_PAGE_8, TR_CLK_DISABLE, TR_CLK_DISABLE);
	अगर (rc < 0)
		वापस rc;

	mutex_lock(&phydev->lock);
	oldpage = phy_select_page(phydev, MSCC_PHY_PAGE_TR);
	अगर (oldpage < 0)
		जाओ out_unlock;

	क्रम (i = 0; i < ARRAY_SIZE(init_seq); i++)
		vsc85xx_tr_ग_लिखो(phydev, init_seq[i].reg, init_seq[i].val);

out_unlock:
	oldpage = phy_restore_page(phydev, oldpage, oldpage);
	mutex_unlock(&phydev->lock);

	वापस oldpage;
पूर्ण

अटल पूर्णांक vsc85xx_eee_init_seq_set(काष्ठा phy_device *phydev)
अणु
	अटल स्थिर काष्ठा reg_val init_eee[] = अणु
		अणु0x0f82, 0x0012b00aपूर्ण,
		अणु0x1686, 0x00000004पूर्ण,
		अणु0x168c, 0x00d2c46fपूर्ण,
		अणु0x17a2, 0x00000620पूर्ण,
		अणु0x16a0, 0x00eeffddपूर्ण,
		अणु0x16a6, 0x00071448पूर्ण,
		अणु0x16a4, 0x0013132fपूर्ण,
		अणु0x16a8, 0x00000000पूर्ण,
		अणु0x0ffc, 0x00c0a028पूर्ण,
		अणु0x0fe8, 0x0091b06cपूर्ण,
		अणु0x0fea, 0x00041600पूर्ण,
		अणु0x0f80, 0x00000af4पूर्ण,
		अणु0x0fec, 0x00901809पूर्ण,
		अणु0x0fee, 0x0000a6a1पूर्ण,
		अणु0x0ffe, 0x00b01007पूर्ण,
		अणु0x16b0, 0x00eeff00पूर्ण,
		अणु0x16b2, 0x00007000पूर्ण,
		अणु0x16b4, 0x00000814पूर्ण,
	पूर्ण;
	अचिन्हित पूर्णांक i;
	पूर्णांक oldpage;

	mutex_lock(&phydev->lock);
	oldpage = phy_select_page(phydev, MSCC_PHY_PAGE_TR);
	अगर (oldpage < 0)
		जाओ out_unlock;

	क्रम (i = 0; i < ARRAY_SIZE(init_eee); i++)
		vsc85xx_tr_ग_लिखो(phydev, init_eee[i].reg, init_eee[i].val);

out_unlock:
	oldpage = phy_restore_page(phydev, oldpage, oldpage);
	mutex_unlock(&phydev->lock);

	वापस oldpage;
पूर्ण

/* phydev->bus->mdio_lock should be locked when using this function */
पूर्णांक phy_base_ग_लिखो(काष्ठा phy_device *phydev, u32 regnum, u16 val)
अणु
	अगर (unlikely(!mutex_is_locked(&phydev->mdio.bus->mdio_lock))) अणु
		dev_err(&phydev->mdio.dev, "MDIO bus lock not held!\n");
		dump_stack();
	पूर्ण

	वापस __phy_package_ग_लिखो(phydev, regnum, val);
पूर्ण

/* phydev->bus->mdio_lock should be locked when using this function */
पूर्णांक phy_base_पढ़ो(काष्ठा phy_device *phydev, u32 regnum)
अणु
	अगर (unlikely(!mutex_is_locked(&phydev->mdio.bus->mdio_lock))) अणु
		dev_err(&phydev->mdio.dev, "MDIO bus lock not held!\n");
		dump_stack();
	पूर्ण

	वापस __phy_package_पढ़ो(phydev, regnum);
पूर्ण

u32 vsc85xx_csr_पढ़ो(काष्ठा phy_device *phydev,
		     क्रमागत csr_target target, u32 reg)
अणु
	अचिन्हित दीर्घ deadline;
	u32 val, val_l, val_h;

	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_CSR_CNTL);

	/* CSR रेजिस्टरs are grouped under dअगरferent Target IDs.
	 * 6-bit Target_ID is split between MSCC_EXT_PAGE_CSR_CNTL_20 and
	 * MSCC_EXT_PAGE_CSR_CNTL_19 रेजिस्टरs.
	 * Target_ID[5:2] maps to bits[3:0] of MSCC_EXT_PAGE_CSR_CNTL_20
	 * and Target_ID[1:0] maps to bits[13:12] of MSCC_EXT_PAGE_CSR_CNTL_19.
	 */

	/* Setup the Target ID */
	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_CSR_CNTL_20,
		       MSCC_PHY_CSR_CNTL_20_TARGET(target >> 2));

	अगर ((target >> 2 == 0x1) || (target >> 2 == 0x3))
		/* non-MACsec access */
		target &= 0x3;
	अन्यथा
		target = 0;

	/* Trigger CSR Action - Read पूर्णांकo the CSR's */
	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_CSR_CNTL_19,
		       MSCC_PHY_CSR_CNTL_19_CMD | MSCC_PHY_CSR_CNTL_19_READ |
		       MSCC_PHY_CSR_CNTL_19_REG_ADDR(reg) |
		       MSCC_PHY_CSR_CNTL_19_TARGET(target));

	/* Wait क्रम रेजिस्टर access*/
	deadline = jअगरfies + msecs_to_jअगरfies(PROC_CMD_NCOMPLETED_TIMEOUT_MS);
	करो अणु
		usleep_range(500, 1000);
		val = phy_base_पढ़ो(phydev, MSCC_EXT_PAGE_CSR_CNTL_19);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, deadline) &&
		!(val & MSCC_PHY_CSR_CNTL_19_CMD));

	अगर (!(val & MSCC_PHY_CSR_CNTL_19_CMD))
		वापस 0xffffffff;

	/* Read the Least Signअगरicant Word (LSW) (17) */
	val_l = phy_base_पढ़ो(phydev, MSCC_EXT_PAGE_CSR_CNTL_17);

	/* Read the Most Signअगरicant Word (MSW) (18) */
	val_h = phy_base_पढ़ो(phydev, MSCC_EXT_PAGE_CSR_CNTL_18);

	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS,
		       MSCC_PHY_PAGE_STANDARD);

	वापस (val_h << 16) | val_l;
पूर्ण

पूर्णांक vsc85xx_csr_ग_लिखो(काष्ठा phy_device *phydev,
		      क्रमागत csr_target target, u32 reg, u32 val)
अणु
	अचिन्हित दीर्घ deadline;

	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_CSR_CNTL);

	/* CSR रेजिस्टरs are grouped under dअगरferent Target IDs.
	 * 6-bit Target_ID is split between MSCC_EXT_PAGE_CSR_CNTL_20 and
	 * MSCC_EXT_PAGE_CSR_CNTL_19 रेजिस्टरs.
	 * Target_ID[5:2] maps to bits[3:0] of MSCC_EXT_PAGE_CSR_CNTL_20
	 * and Target_ID[1:0] maps to bits[13:12] of MSCC_EXT_PAGE_CSR_CNTL_19.
	 */

	/* Setup the Target ID */
	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_CSR_CNTL_20,
		       MSCC_PHY_CSR_CNTL_20_TARGET(target >> 2));

	/* Write the Least Signअगरicant Word (LSW) (17) */
	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_CSR_CNTL_17, (u16)val);

	/* Write the Most Signअगरicant Word (MSW) (18) */
	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_CSR_CNTL_18, (u16)(val >> 16));

	अगर ((target >> 2 == 0x1) || (target >> 2 == 0x3))
		/* non-MACsec access */
		target &= 0x3;
	अन्यथा
		target = 0;

	/* Trigger CSR Action - Write पूर्णांकo the CSR's */
	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_CSR_CNTL_19,
		       MSCC_PHY_CSR_CNTL_19_CMD |
		       MSCC_PHY_CSR_CNTL_19_REG_ADDR(reg) |
		       MSCC_PHY_CSR_CNTL_19_TARGET(target));

	/* Wait क्रम रेजिस्टर access */
	deadline = jअगरfies + msecs_to_jअगरfies(PROC_CMD_NCOMPLETED_TIMEOUT_MS);
	करो अणु
		usleep_range(500, 1000);
		val = phy_base_पढ़ो(phydev, MSCC_EXT_PAGE_CSR_CNTL_19);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, deadline) &&
		 !(val & MSCC_PHY_CSR_CNTL_19_CMD));

	अगर (!(val & MSCC_PHY_CSR_CNTL_19_CMD))
		वापस -ETIMEDOUT;

	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS,
		       MSCC_PHY_PAGE_STANDARD);

	वापस 0;
पूर्ण

/* bus->mdio_lock should be locked when using this function */
अटल व्योम vsc8584_csr_ग_लिखो(काष्ठा phy_device *phydev, u16 addr, u32 val)
अणु
	phy_base_ग_लिखो(phydev, MSCC_PHY_TR_MSB, val >> 16);
	phy_base_ग_लिखो(phydev, MSCC_PHY_TR_LSB, val & GENMASK(15, 0));
	phy_base_ग_लिखो(phydev, MSCC_PHY_TR_CNTL, TR_WRITE | TR_ADDR(addr));
पूर्ण

/* bus->mdio_lock should be locked when using this function */
पूर्णांक vsc8584_cmd(काष्ठा phy_device *phydev, u16 val)
अणु
	अचिन्हित दीर्घ deadline;
	u16 reg_val;

	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS,
		       MSCC_PHY_PAGE_EXTENDED_GPIO);

	phy_base_ग_लिखो(phydev, MSCC_PHY_PROC_CMD, PROC_CMD_NCOMPLETED | val);

	deadline = jअगरfies + msecs_to_jअगरfies(PROC_CMD_NCOMPLETED_TIMEOUT_MS);
	करो अणु
		reg_val = phy_base_पढ़ो(phydev, MSCC_PHY_PROC_CMD);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, deadline) &&
		 (reg_val & PROC_CMD_NCOMPLETED) &&
		 !(reg_val & PROC_CMD_FAILED));

	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDARD);

	अगर (reg_val & PROC_CMD_FAILED)
		वापस -EIO;

	अगर (reg_val & PROC_CMD_NCOMPLETED)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

/* bus->mdio_lock should be locked when using this function */
अटल पूर्णांक vsc8584_micro_deनिश्चित_reset(काष्ठा phy_device *phydev,
					bool patch_en)
अणु
	u32 enable, release;

	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS,
		       MSCC_PHY_PAGE_EXTENDED_GPIO);

	enable = RUN_FROM_INT_ROM | MICRO_CLK_EN | DW8051_CLK_EN;
	release = MICRO_NSOFT_RESET | RUN_FROM_INT_ROM | DW8051_CLK_EN |
		MICRO_CLK_EN;

	अगर (patch_en) अणु
		enable |= MICRO_PATCH_EN;
		release |= MICRO_PATCH_EN;

		/* Clear all patches */
		phy_base_ग_लिखो(phydev, MSCC_INT_MEM_CNTL, READ_RAM);
	पूर्ण

	/* Enable 8051 Micro घड़ी; CLEAR/SET patch present; disable PRAM घड़ी
	 * override and addr. स्वतः-incr; operate at 125 MHz
	 */
	phy_base_ग_लिखो(phydev, MSCC_DW8051_CNTL_STATUS, enable);
	/* Release 8051 Micro SW reset */
	phy_base_ग_लिखो(phydev, MSCC_DW8051_CNTL_STATUS, release);

	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDARD);

	वापस 0;
पूर्ण

/* bus->mdio_lock should be locked when using this function */
अटल पूर्णांक vsc8584_micro_निश्चित_reset(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;
	u16 reg;

	ret = vsc8584_cmd(phydev, PROC_CMD_NOP);
	अगर (ret)
		वापस ret;

	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS,
		       MSCC_PHY_PAGE_EXTENDED_GPIO);

	reg = phy_base_पढ़ो(phydev, MSCC_INT_MEM_CNTL);
	reg &= ~EN_PATCH_RAM_TRAP_ADDR(4);
	phy_base_ग_लिखो(phydev, MSCC_INT_MEM_CNTL, reg);

	phy_base_ग_लिखो(phydev, MSCC_TRAP_ROM_ADDR(4), 0x005b);
	phy_base_ग_लिखो(phydev, MSCC_PATCH_RAM_ADDR(4), 0x005b);

	reg = phy_base_पढ़ो(phydev, MSCC_INT_MEM_CNTL);
	reg |= EN_PATCH_RAM_TRAP_ADDR(4);
	phy_base_ग_लिखो(phydev, MSCC_INT_MEM_CNTL, reg);

	phy_base_ग_लिखो(phydev, MSCC_PHY_PROC_CMD, PROC_CMD_NOP);

	reg = phy_base_पढ़ो(phydev, MSCC_DW8051_CNTL_STATUS);
	reg &= ~MICRO_NSOFT_RESET;
	phy_base_ग_लिखो(phydev, MSCC_DW8051_CNTL_STATUS, reg);

	phy_base_ग_लिखो(phydev, MSCC_PHY_PROC_CMD, PROC_CMD_MCB_ACCESS_MAC_CONF |
		       PROC_CMD_SGMII_PORT(0) | PROC_CMD_NO_MAC_CONF |
		       PROC_CMD_READ);

	reg = phy_base_पढ़ो(phydev, MSCC_INT_MEM_CNTL);
	reg &= ~EN_PATCH_RAM_TRAP_ADDR(4);
	phy_base_ग_लिखो(phydev, MSCC_INT_MEM_CNTL, reg);

	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDARD);

	वापस 0;
पूर्ण

/* bus->mdio_lock should be locked when using this function */
अटल पूर्णांक vsc8584_get_fw_crc(काष्ठा phy_device *phydev, u16 start, u16 size,
			      u16 *crc)
अणु
	पूर्णांक ret;

	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_EXTENDED);

	phy_base_ग_लिखो(phydev, MSCC_PHY_VERIPHY_CNTL_2, start);
	phy_base_ग_लिखो(phydev, MSCC_PHY_VERIPHY_CNTL_3, size);

	/* Start Micro command */
	ret = vsc8584_cmd(phydev, PROC_CMD_CRC16);
	अगर (ret)
		जाओ out;

	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_EXTENDED);

	*crc = phy_base_पढ़ो(phydev, MSCC_PHY_VERIPHY_CNTL_2);

out:
	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDARD);

	वापस ret;
पूर्ण

/* bus->mdio_lock should be locked when using this function */
अटल पूर्णांक vsc8584_patch_fw(काष्ठा phy_device *phydev,
			    स्थिर काष्ठा firmware *fw)
अणु
	पूर्णांक i, ret;

	ret = vsc8584_micro_निश्चित_reset(phydev);
	अगर (ret) अणु
		dev_err(&phydev->mdio.dev,
			"%s: failed to assert reset of micro\n", __func__);
		वापस ret;
	पूर्ण

	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS,
		       MSCC_PHY_PAGE_EXTENDED_GPIO);

	/* Hold 8051 Micro in SW Reset, Enable स्वतः incr address and patch घड़ी
	 * Disable the 8051 Micro घड़ी
	 */
	phy_base_ग_लिखो(phydev, MSCC_DW8051_CNTL_STATUS, RUN_FROM_INT_ROM |
		       AUTOINC_ADDR | PATCH_RAM_CLK | MICRO_CLK_EN |
		       MICRO_CLK_DIVIDE(2));
	phy_base_ग_लिखो(phydev, MSCC_INT_MEM_CNTL, READ_PRAM | INT_MEM_WRITE_EN |
		       INT_MEM_DATA(2));
	phy_base_ग_लिखो(phydev, MSCC_INT_MEM_ADDR, 0x0000);

	क्रम (i = 0; i < fw->size; i++)
		phy_base_ग_लिखो(phydev, MSCC_INT_MEM_CNTL, READ_PRAM |
			       INT_MEM_WRITE_EN | fw->data[i]);

	/* Clear पूर्णांकernal memory access */
	phy_base_ग_लिखो(phydev, MSCC_INT_MEM_CNTL, READ_RAM);

	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDARD);

	वापस 0;
पूर्ण

/* bus->mdio_lock should be locked when using this function */
अटल bool vsc8574_is_serdes_init(काष्ठा phy_device *phydev)
अणु
	u16 reg;
	bool ret;

	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS,
		       MSCC_PHY_PAGE_EXTENDED_GPIO);

	reg = phy_base_पढ़ो(phydev, MSCC_TRAP_ROM_ADDR(1));
	अगर (reg != 0x3eb7) अणु
		ret = false;
		जाओ out;
	पूर्ण

	reg = phy_base_पढ़ो(phydev, MSCC_PATCH_RAM_ADDR(1));
	अगर (reg != 0x4012) अणु
		ret = false;
		जाओ out;
	पूर्ण

	reg = phy_base_पढ़ो(phydev, MSCC_INT_MEM_CNTL);
	अगर (reg != EN_PATCH_RAM_TRAP_ADDR(1)) अणु
		ret = false;
		जाओ out;
	पूर्ण

	reg = phy_base_पढ़ो(phydev, MSCC_DW8051_CNTL_STATUS);
	अगर ((MICRO_NSOFT_RESET | RUN_FROM_INT_ROM |  DW8051_CLK_EN |
	     MICRO_CLK_EN) != (reg & MSCC_DW8051_VLD_MASK)) अणु
		ret = false;
		जाओ out;
	पूर्ण

	ret = true;
out:
	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDARD);

	वापस ret;
पूर्ण

/* bus->mdio_lock should be locked when using this function */
अटल पूर्णांक vsc8574_config_pre_init(काष्ठा phy_device *phydev)
अणु
	अटल स्थिर काष्ठा reg_val pre_init1[] = अणु
		अणु0x0fae, 0x000401bdपूर्ण,
		अणु0x0fac, 0x000f000fपूर्ण,
		अणु0x17a0, 0x00a0f147पूर्ण,
		अणु0x0fe4, 0x00052f54पूर्ण,
		अणु0x1792, 0x0027303dपूर्ण,
		अणु0x07fe, 0x00000704पूर्ण,
		अणु0x0fe0, 0x00060150पूर्ण,
		अणु0x0f82, 0x0012b00aपूर्ण,
		अणु0x0f80, 0x00000d74पूर्ण,
		अणु0x02e0, 0x00000012पूर्ण,
		अणु0x03a2, 0x00050208पूर्ण,
		अणु0x03b2, 0x00009186पूर्ण,
		अणु0x0fb0, 0x000e3700पूर्ण,
		अणु0x1688, 0x00049f81पूर्ण,
		अणु0x0fd2, 0x0000ffffपूर्ण,
		अणु0x168a, 0x00039fa2पूर्ण,
		अणु0x1690, 0x0020640bपूर्ण,
		अणु0x0258, 0x00002220पूर्ण,
		अणु0x025a, 0x00002a20पूर्ण,
		अणु0x025c, 0x00003060पूर्ण,
		अणु0x025e, 0x00003fa0पूर्ण,
		अणु0x03a6, 0x0000e0f0पूर्ण,
		अणु0x0f92, 0x00001489पूर्ण,
		अणु0x16a2, 0x00007000पूर्ण,
		अणु0x16a6, 0x00071448पूर्ण,
		अणु0x16a0, 0x00eeffddपूर्ण,
		अणु0x0fe8, 0x0091b06cपूर्ण,
		अणु0x0fea, 0x00041600पूर्ण,
		अणु0x16b0, 0x00eeff00पूर्ण,
		अणु0x16b2, 0x00007000पूर्ण,
		अणु0x16b4, 0x00000814पूर्ण,
		अणु0x0f90, 0x00688980पूर्ण,
		अणु0x03a4, 0x0000d8f0पूर्ण,
		अणु0x0fc0, 0x00000400पूर्ण,
		अणु0x07fa, 0x0050100fपूर्ण,
		अणु0x0796, 0x00000003पूर्ण,
		अणु0x07f8, 0x00c3ff98पूर्ण,
		अणु0x0fa4, 0x0018292aपूर्ण,
		अणु0x168c, 0x00d2c46fपूर्ण,
		अणु0x17a2, 0x00000620पूर्ण,
		अणु0x16a4, 0x0013132fपूर्ण,
		अणु0x16a8, 0x00000000पूर्ण,
		अणु0x0ffc, 0x00c0a028पूर्ण,
		अणु0x0fec, 0x00901c09पूर्ण,
		अणु0x0fee, 0x0004a6a1पूर्ण,
		अणु0x0ffe, 0x00b01807पूर्ण,
	पूर्ण;
	अटल स्थिर काष्ठा reg_val pre_init2[] = अणु
		अणु0x0486, 0x0008a518पूर्ण,
		अणु0x0488, 0x006dc696पूर्ण,
		अणु0x048a, 0x00000912पूर्ण,
		अणु0x048e, 0x00000db6पूर्ण,
		अणु0x049c, 0x00596596पूर्ण,
		अणु0x049e, 0x00000514पूर्ण,
		अणु0x04a2, 0x00410280पूर्ण,
		अणु0x04a4, 0x00000000पूर्ण,
		अणु0x04a6, 0x00000000पूर्ण,
		अणु0x04a8, 0x00000000पूर्ण,
		अणु0x04aa, 0x00000000पूर्ण,
		अणु0x04ae, 0x007df7ddपूर्ण,
		अणु0x04b0, 0x006d95d4पूर्ण,
		अणु0x04b2, 0x00492410पूर्ण,
	पूर्ण;
	काष्ठा device *dev = &phydev->mdio.dev;
	स्थिर काष्ठा firmware *fw;
	अचिन्हित पूर्णांक i;
	u16 crc, reg;
	bool serdes_init;
	पूर्णांक ret;

	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDARD);

	/* all ग_लिखोs below are broadcasted to all PHYs in the same package */
	reg = phy_base_पढ़ो(phydev, MSCC_PHY_EXT_CNTL_STATUS);
	reg |= SMI_BROADCAST_WR_EN;
	phy_base_ग_लिखो(phydev, MSCC_PHY_EXT_CNTL_STATUS, reg);

	phy_base_ग_लिखो(phydev, MII_VSC85XX_INT_MASK, 0);

	/* The below रेजिस्टर ग_लिखोs are tweaking analog and electrical
	 * configuration that were determined through अक्षरacterization by PHY
	 * engineers. These करोn't mean anything more than "these are the best
	 * values".
	 */
	phy_base_ग_लिखो(phydev, MSCC_PHY_EXT_PHY_CNTL_2, 0x0040);

	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_TEST);

	phy_base_ग_लिखो(phydev, MSCC_PHY_TEST_PAGE_20, 0x4320);
	phy_base_ग_लिखो(phydev, MSCC_PHY_TEST_PAGE_24, 0x0c00);
	phy_base_ग_लिखो(phydev, MSCC_PHY_TEST_PAGE_9, 0x18ca);
	phy_base_ग_लिखो(phydev, MSCC_PHY_TEST_PAGE_5, 0x1b20);

	reg = phy_base_पढ़ो(phydev, MSCC_PHY_TEST_PAGE_8);
	reg |= TR_CLK_DISABLE;
	phy_base_ग_लिखो(phydev, MSCC_PHY_TEST_PAGE_8, reg);

	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_TR);

	क्रम (i = 0; i < ARRAY_SIZE(pre_init1); i++)
		vsc8584_csr_ग_लिखो(phydev, pre_init1[i].reg, pre_init1[i].val);

	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_EXTENDED_2);

	phy_base_ग_लिखो(phydev, MSCC_PHY_CU_PMD_TX_CNTL, 0x028e);

	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_TR);

	क्रम (i = 0; i < ARRAY_SIZE(pre_init2); i++)
		vsc8584_csr_ग_लिखो(phydev, pre_init2[i].reg, pre_init2[i].val);

	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_TEST);

	reg = phy_base_पढ़ो(phydev, MSCC_PHY_TEST_PAGE_8);
	reg &= ~TR_CLK_DISABLE;
	phy_base_ग_लिखो(phydev, MSCC_PHY_TEST_PAGE_8, reg);

	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDARD);

	/* end of ग_लिखो broadcasting */
	reg = phy_base_पढ़ो(phydev, MSCC_PHY_EXT_CNTL_STATUS);
	reg &= ~SMI_BROADCAST_WR_EN;
	phy_base_ग_लिखो(phydev, MSCC_PHY_EXT_CNTL_STATUS, reg);

	ret = request_firmware(&fw, MSCC_VSC8574_REVB_INT8051_FW, dev);
	अगर (ret) अणु
		dev_err(dev, "failed to load firmware %s, ret: %d\n",
			MSCC_VSC8574_REVB_INT8051_FW, ret);
		वापस ret;
	पूर्ण

	/* Add one byte to size क्रम the one added by the patch_fw function */
	ret = vsc8584_get_fw_crc(phydev,
				 MSCC_VSC8574_REVB_INT8051_FW_START_ADDR,
				 fw->size + 1, &crc);
	अगर (ret)
		जाओ out;

	अगर (crc == MSCC_VSC8574_REVB_INT8051_FW_CRC) अणु
		serdes_init = vsc8574_is_serdes_init(phydev);

		अगर (!serdes_init) अणु
			ret = vsc8584_micro_निश्चित_reset(phydev);
			अगर (ret) अणु
				dev_err(dev,
					"%s: failed to assert reset of micro\n",
					__func__);
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_dbg(dev, "FW CRC is not the expected one, patching FW\n");

		serdes_init = false;

		अगर (vsc8584_patch_fw(phydev, fw))
			dev_warn(dev,
				 "failed to patch FW, expect non-optimal device\n");
	पूर्ण

	अगर (!serdes_init) अणु
		phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS,
			       MSCC_PHY_PAGE_EXTENDED_GPIO);

		phy_base_ग_लिखो(phydev, MSCC_TRAP_ROM_ADDR(1), 0x3eb7);
		phy_base_ग_लिखो(phydev, MSCC_PATCH_RAM_ADDR(1), 0x4012);
		phy_base_ग_लिखो(phydev, MSCC_INT_MEM_CNTL,
			       EN_PATCH_RAM_TRAP_ADDR(1));

		vsc8584_micro_deनिश्चित_reset(phydev, false);

		/* Add one byte to size क्रम the one added by the patch_fw
		 * function
		 */
		ret = vsc8584_get_fw_crc(phydev,
					 MSCC_VSC8574_REVB_INT8051_FW_START_ADDR,
					 fw->size + 1, &crc);
		अगर (ret)
			जाओ out;

		अगर (crc != MSCC_VSC8574_REVB_INT8051_FW_CRC)
			dev_warn(dev,
				 "FW CRC after patching is not the expected one, expect non-optimal device\n");
	पूर्ण

	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS,
		       MSCC_PHY_PAGE_EXTENDED_GPIO);

	ret = vsc8584_cmd(phydev, PROC_CMD_1588_DEFAULT_INIT |
			  PROC_CMD_PHY_INIT);

out:
	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDARD);

	release_firmware(fw);

	वापस ret;
पूर्ण

/* Access LCPLL Cfg_2 */
अटल व्योम vsc8584_pll5g_cfg2_wr(काष्ठा phy_device *phydev,
				  bool disable_fsm)
अणु
	u32 rd_dat;

	rd_dat = vsc85xx_csr_पढ़ो(phydev, MACRO_CTRL, PHY_S6G_PLL5G_CFG2);
	rd_dat &= ~BIT(PHY_S6G_CFG2_FSM_DIS);
	rd_dat |= (disable_fsm << PHY_S6G_CFG2_FSM_DIS);
	vsc85xx_csr_ग_लिखो(phydev, MACRO_CTRL, PHY_S6G_PLL5G_CFG2, rd_dat);
पूर्ण

/* trigger a पढ़ो to the spcअगरied MCB */
अटल पूर्णांक vsc8584_mcb_rd_trig(काष्ठा phy_device *phydev,
			       u32 mcb_reg_addr, u8 mcb_slave_num)
अणु
	u32 rd_dat = 0;

	/* पढ़ो MCB */
	vsc85xx_csr_ग_लिखो(phydev, MACRO_CTRL, mcb_reg_addr,
			  (0x40000000 | (1L << mcb_slave_num)));

	वापस पढ़ो_poll_समयout(vsc85xx_csr_पढ़ो, rd_dat,
				 !(rd_dat & 0x40000000),
				 4000, 200000, 0,
				 phydev, MACRO_CTRL, mcb_reg_addr);
पूर्ण

/* trigger a ग_लिखो to the spcअगरied MCB */
अटल पूर्णांक vsc8584_mcb_wr_trig(काष्ठा phy_device *phydev,
			       u32 mcb_reg_addr,
			       u8 mcb_slave_num)
अणु
	u32 rd_dat = 0;

	/* ग_लिखो back MCB */
	vsc85xx_csr_ग_लिखो(phydev, MACRO_CTRL, mcb_reg_addr,
			  (0x80000000 | (1L << mcb_slave_num)));

	वापस पढ़ो_poll_समयout(vsc85xx_csr_पढ़ो, rd_dat,
				 !(rd_dat & 0x80000000),
				 4000, 200000, 0,
				 phydev, MACRO_CTRL, mcb_reg_addr);
पूर्ण

/* Sequence to Reset LCPLL क्रम the VIPER and ELISE PHY */
अटल पूर्णांक vsc8584_pll5g_reset(काष्ठा phy_device *phydev)
अणु
	bool dis_fsm;
	पूर्णांक ret = 0;

	ret = vsc8584_mcb_rd_trig(phydev, 0x11, 0);
	अगर (ret < 0)
		जाओ करोne;
	dis_fsm = 1;

	/* Reset LCPLL */
	vsc8584_pll5g_cfg2_wr(phydev, dis_fsm);

	/* ग_लिखो back LCPLL MCB */
	ret = vsc8584_mcb_wr_trig(phydev, 0x11, 0);
	अगर (ret < 0)
		जाओ करोne;

	/* 10 mSec sleep जबतक LCPLL is hold in reset */
	usleep_range(10000, 20000);

	/* पढ़ो LCPLL MCB पूर्णांकo CSRs */
	ret = vsc8584_mcb_rd_trig(phydev, 0x11, 0);
	अगर (ret < 0)
		जाओ करोne;
	dis_fsm = 0;

	/* Release the Reset of LCPLL */
	vsc8584_pll5g_cfg2_wr(phydev, dis_fsm);

	/* ग_लिखो back LCPLL MCB */
	ret = vsc8584_mcb_wr_trig(phydev, 0x11, 0);
	अगर (ret < 0)
		जाओ करोne;

	usleep_range(110000, 200000);
करोne:
	वापस ret;
पूर्ण

/* bus->mdio_lock should be locked when using this function */
अटल पूर्णांक vsc8584_config_pre_init(काष्ठा phy_device *phydev)
अणु
	अटल स्थिर काष्ठा reg_val pre_init1[] = अणु
		अणु0x07fa, 0x0050100fपूर्ण,
		अणु0x1688, 0x00049f81पूर्ण,
		अणु0x0f90, 0x00688980पूर्ण,
		अणु0x03a4, 0x0000d8f0पूर्ण,
		अणु0x0fc0, 0x00000400पूर्ण,
		अणु0x0f82, 0x0012b002पूर्ण,
		अणु0x1686, 0x00000004पूर्ण,
		अणु0x168c, 0x00d2c46fपूर्ण,
		अणु0x17a2, 0x00000620पूर्ण,
		अणु0x16a0, 0x00eeffddपूर्ण,
		अणु0x16a6, 0x00071448पूर्ण,
		अणु0x16a4, 0x0013132fपूर्ण,
		अणु0x16a8, 0x00000000पूर्ण,
		अणु0x0ffc, 0x00c0a028पूर्ण,
		अणु0x0fe8, 0x0091b06cपूर्ण,
		अणु0x0fea, 0x00041600पूर्ण,
		अणु0x0f80, 0x00fffaffपूर्ण,
		अणु0x0fec, 0x00901809पूर्ण,
		अणु0x0ffe, 0x00b01007पूर्ण,
		अणु0x16b0, 0x00eeff00पूर्ण,
		अणु0x16b2, 0x00007000पूर्ण,
		अणु0x16b4, 0x00000814पूर्ण,
	पूर्ण;
	अटल स्थिर काष्ठा reg_val pre_init2[] = अणु
		अणु0x0486, 0x0008a518पूर्ण,
		अणु0x0488, 0x006dc696पूर्ण,
		अणु0x048a, 0x00000912पूर्ण,
	पूर्ण;
	स्थिर काष्ठा firmware *fw;
	काष्ठा device *dev = &phydev->mdio.dev;
	अचिन्हित पूर्णांक i;
	u16 crc, reg;
	पूर्णांक ret;

	ret = vsc8584_pll5g_reset(phydev);
	अगर (ret < 0) अणु
		dev_err(dev, "failed LCPLL reset, ret: %d\n", ret);
		वापस ret;
	पूर्ण

	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDARD);

	/* all ग_लिखोs below are broadcasted to all PHYs in the same package */
	reg = phy_base_पढ़ो(phydev, MSCC_PHY_EXT_CNTL_STATUS);
	reg |= SMI_BROADCAST_WR_EN;
	phy_base_ग_लिखो(phydev, MSCC_PHY_EXT_CNTL_STATUS, reg);

	phy_base_ग_लिखो(phydev, MII_VSC85XX_INT_MASK, 0);

	reg = phy_base_पढ़ो(phydev,  MSCC_PHY_BYPASS_CONTROL);
	reg |= PARALLEL_DET_IGNORE_ADVERTISED;
	phy_base_ग_लिखो(phydev, MSCC_PHY_BYPASS_CONTROL, reg);

	/* The below रेजिस्टर ग_लिखोs are tweaking analog and electrical
	 * configuration that were determined through अक्षरacterization by PHY
	 * engineers. These करोn't mean anything more than "these are the best
	 * values".
	 */
	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_EXTENDED_3);

	phy_base_ग_लिखो(phydev, MSCC_PHY_SERDES_TX_CRC_ERR_CNT, 0x2000);

	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_TEST);

	phy_base_ग_लिखो(phydev, MSCC_PHY_TEST_PAGE_5, 0x1f20);

	reg = phy_base_पढ़ो(phydev, MSCC_PHY_TEST_PAGE_8);
	reg |= TR_CLK_DISABLE;
	phy_base_ग_लिखो(phydev, MSCC_PHY_TEST_PAGE_8, reg);

	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_TR);

	phy_base_ग_लिखो(phydev, MSCC_PHY_TR_CNTL, TR_WRITE | TR_ADDR(0x2fa4));

	reg = phy_base_पढ़ो(phydev, MSCC_PHY_TR_MSB);
	reg &= ~0x007f;
	reg |= 0x0019;
	phy_base_ग_लिखो(phydev, MSCC_PHY_TR_MSB, reg);

	phy_base_ग_लिखो(phydev, MSCC_PHY_TR_CNTL, TR_WRITE | TR_ADDR(0x0fa4));

	क्रम (i = 0; i < ARRAY_SIZE(pre_init1); i++)
		vsc8584_csr_ग_लिखो(phydev, pre_init1[i].reg, pre_init1[i].val);

	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_EXTENDED_2);

	phy_base_ग_लिखो(phydev, MSCC_PHY_CU_PMD_TX_CNTL, 0x028e);

	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_TR);

	क्रम (i = 0; i < ARRAY_SIZE(pre_init2); i++)
		vsc8584_csr_ग_लिखो(phydev, pre_init2[i].reg, pre_init2[i].val);

	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_TEST);

	reg = phy_base_पढ़ो(phydev, MSCC_PHY_TEST_PAGE_8);
	reg &= ~TR_CLK_DISABLE;
	phy_base_ग_लिखो(phydev, MSCC_PHY_TEST_PAGE_8, reg);

	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDARD);

	/* end of ग_लिखो broadcasting */
	reg = phy_base_पढ़ो(phydev, MSCC_PHY_EXT_CNTL_STATUS);
	reg &= ~SMI_BROADCAST_WR_EN;
	phy_base_ग_लिखो(phydev, MSCC_PHY_EXT_CNTL_STATUS, reg);

	ret = request_firmware(&fw, MSCC_VSC8584_REVB_INT8051_FW, dev);
	अगर (ret) अणु
		dev_err(dev, "failed to load firmware %s, ret: %d\n",
			MSCC_VSC8584_REVB_INT8051_FW, ret);
		वापस ret;
	पूर्ण

	/* Add one byte to size क्रम the one added by the patch_fw function */
	ret = vsc8584_get_fw_crc(phydev,
				 MSCC_VSC8584_REVB_INT8051_FW_START_ADDR,
				 fw->size + 1, &crc);
	अगर (ret)
		जाओ out;

	अगर (crc != MSCC_VSC8584_REVB_INT8051_FW_CRC) अणु
		dev_dbg(dev, "FW CRC is not the expected one, patching FW\n");
		अगर (vsc8584_patch_fw(phydev, fw))
			dev_warn(dev,
				 "failed to patch FW, expect non-optimal device\n");
	पूर्ण

	vsc8584_micro_deनिश्चित_reset(phydev, false);

	/* Add one byte to size क्रम the one added by the patch_fw function */
	ret = vsc8584_get_fw_crc(phydev,
				 MSCC_VSC8584_REVB_INT8051_FW_START_ADDR,
				 fw->size + 1, &crc);
	अगर (ret)
		जाओ out;

	अगर (crc != MSCC_VSC8584_REVB_INT8051_FW_CRC)
		dev_warn(dev,
			 "FW CRC after patching is not the expected one, expect non-optimal device\n");

	ret = vsc8584_micro_निश्चित_reset(phydev);
	अगर (ret)
		जाओ out;

	/* Write patch vector 0, to skip IB cal polling  */
	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_EXTENDED_GPIO);
	reg = MSCC_ROM_TRAP_SERDES_6G_CFG; /* ROM address to trap, क्रम patch vector 0 */
	ret = phy_base_ग_लिखो(phydev, MSCC_TRAP_ROM_ADDR(1), reg);
	अगर (ret)
		जाओ out;

	reg = MSCC_RAM_TRAP_SERDES_6G_CFG; /* RAM address to jump to, when patch vector 0 enabled */
	ret = phy_base_ग_लिखो(phydev, MSCC_PATCH_RAM_ADDR(1), reg);
	अगर (ret)
		जाओ out;

	reg = phy_base_पढ़ो(phydev, MSCC_INT_MEM_CNTL);
	reg |= PATCH_VEC_ZERO_EN; /* bit 8, enable patch vector 0 */
	ret = phy_base_ग_लिखो(phydev, MSCC_INT_MEM_CNTL, reg);
	अगर (ret)
		जाओ out;

	vsc8584_micro_deनिश्चित_reset(phydev, true);

out:
	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDARD);

	release_firmware(fw);

	वापस ret;
पूर्ण

अटल व्योम vsc8584_get_base_addr(काष्ठा phy_device *phydev)
अणु
	काष्ठा vsc8531_निजी *vsc8531 = phydev->priv;
	u16 val, addr;

	phy_lock_mdio_bus(phydev);
	__phy_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_EXTENDED);

	addr = __phy_पढ़ो(phydev, MSCC_PHY_EXT_PHY_CNTL_4);
	addr >>= PHY_CNTL_4_ADDR_POS;

	val = __phy_पढ़ो(phydev, MSCC_PHY_ACTIPHY_CNTL);

	__phy_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDARD);
	phy_unlock_mdio_bus(phydev);

	/* In the package, there are two pairs of PHYs (PHY0 + PHY2 and
	 * PHY1 + PHY3). The first PHY of each pair (PHY0 and PHY1) is
	 * the base PHY क्रम बारtamping operations.
	 */
	vsc8531->ts_base_addr = phydev->mdio.addr;
	vsc8531->ts_base_phy = addr;

	अगर (val & PHY_ADDR_REVERSED) अणु
		vsc8531->base_addr = phydev->mdio.addr + addr;
		अगर (addr > 1) अणु
			vsc8531->ts_base_addr += 2;
			vsc8531->ts_base_phy += 2;
		पूर्ण
	पूर्ण अन्यथा अणु
		vsc8531->base_addr = phydev->mdio.addr - addr;
		अगर (addr > 1) अणु
			vsc8531->ts_base_addr -= 2;
			vsc8531->ts_base_phy -= 2;
		पूर्ण
	पूर्ण

	vsc8531->addr = addr;
पूर्ण

अटल व्योम vsc85xx_coma_mode_release(काष्ठा phy_device *phydev)
अणु
	/* The coma mode (pin or reg) provides an optional feature that
	 * may be used to control when the PHYs become active.
	 * Alternatively the COMA_MODE pin may be connected low
	 * so that the PHYs are fully active once out of reset.
	 */

	/* Enable output (mode=0) and ग_लिखो zero to it */
	vsc85xx_phy_ग_लिखो_page(phydev, MSCC_PHY_PAGE_EXTENDED_GPIO);
	__phy_modअगरy(phydev, MSCC_PHY_GPIO_CONTROL_2,
		     MSCC_PHY_COMA_MODE | MSCC_PHY_COMA_OUTPUT, 0);
	vsc85xx_phy_ग_लिखो_page(phydev, MSCC_PHY_PAGE_STANDARD);
पूर्ण

अटल पूर्णांक vsc8584_config_host_serdes(काष्ठा phy_device *phydev)
अणु
	काष्ठा vsc8531_निजी *vsc8531 = phydev->priv;
	पूर्णांक ret;
	u16 val;

	ret = phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS,
			     MSCC_PHY_PAGE_EXTENDED_GPIO);
	अगर (ret)
		वापस ret;

	val = phy_base_पढ़ो(phydev, MSCC_PHY_MAC_CFG_FASTLINK);
	val &= ~MAC_CFG_MASK;
	अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_QSGMII) अणु
		val |= MAC_CFG_QSGMII;
	पूर्ण अन्यथा अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_SGMII) अणु
		val |= MAC_CFG_SGMII;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
		वापस ret;
	पूर्ण

	ret = phy_base_ग_लिखो(phydev, MSCC_PHY_MAC_CFG_FASTLINK, val);
	अगर (ret)
		वापस ret;

	ret = phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS,
			     MSCC_PHY_PAGE_STANDARD);
	अगर (ret)
		वापस ret;

	val = PROC_CMD_MCB_ACCESS_MAC_CONF | PROC_CMD_RST_CONF_PORT |
		PROC_CMD_READ_MOD_WRITE_PORT;
	अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_QSGMII)
		val |= PROC_CMD_QSGMII_MAC;
	अन्यथा
		val |= PROC_CMD_SGMII_MAC;

	ret = vsc8584_cmd(phydev, val);
	अगर (ret)
		वापस ret;

	usleep_range(10000, 20000);

	/* Disable SerDes क्रम 100Base-FX */
	ret = vsc8584_cmd(phydev, PROC_CMD_FIBER_MEDIA_CONF |
			  PROC_CMD_FIBER_PORT(vsc8531->addr) |
			  PROC_CMD_FIBER_DISABLE |
			  PROC_CMD_READ_MOD_WRITE_PORT |
			  PROC_CMD_RST_CONF_PORT | PROC_CMD_FIBER_100BASE_FX);
	अगर (ret)
		वापस ret;

	/* Disable SerDes क्रम 1000Base-X */
	ret = vsc8584_cmd(phydev, PROC_CMD_FIBER_MEDIA_CONF |
			  PROC_CMD_FIBER_PORT(vsc8531->addr) |
			  PROC_CMD_FIBER_DISABLE |
			  PROC_CMD_READ_MOD_WRITE_PORT |
			  PROC_CMD_RST_CONF_PORT | PROC_CMD_FIBER_1000BASE_X);
	अगर (ret)
		वापस ret;

	वापस vsc85xx_sd6g_config_v2(phydev);
पूर्ण

अटल पूर्णांक vsc8574_config_host_serdes(काष्ठा phy_device *phydev)
अणु
	काष्ठा vsc8531_निजी *vsc8531 = phydev->priv;
	पूर्णांक ret;
	u16 val;

	ret = phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS,
			     MSCC_PHY_PAGE_EXTENDED_GPIO);
	अगर (ret)
		वापस ret;

	val = phy_base_पढ़ो(phydev, MSCC_PHY_MAC_CFG_FASTLINK);
	val &= ~MAC_CFG_MASK;
	अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_QSGMII) अणु
		val |= MAC_CFG_QSGMII;
	पूर्ण अन्यथा अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_SGMII) अणु
		val |= MAC_CFG_SGMII;
	पूर्ण अन्यथा अगर (phy_पूर्णांकerface_is_rgmii(phydev)) अणु
		val |= MAC_CFG_RGMII;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
		वापस ret;
	पूर्ण

	ret = phy_base_ग_लिखो(phydev, MSCC_PHY_MAC_CFG_FASTLINK, val);
	अगर (ret)
		वापस ret;

	ret = phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS,
			     MSCC_PHY_PAGE_STANDARD);
	अगर (ret)
		वापस ret;

	अगर (!phy_पूर्णांकerface_is_rgmii(phydev)) अणु
		val = PROC_CMD_MCB_ACCESS_MAC_CONF | PROC_CMD_RST_CONF_PORT |
			PROC_CMD_READ_MOD_WRITE_PORT;
		अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_QSGMII)
			val |= PROC_CMD_QSGMII_MAC;
		अन्यथा
			val |= PROC_CMD_SGMII_MAC;

		ret = vsc8584_cmd(phydev, val);
		अगर (ret)
			वापस ret;

		usleep_range(10000, 20000);
	पूर्ण

	/* Disable SerDes क्रम 100Base-FX */
	ret = vsc8584_cmd(phydev, PROC_CMD_FIBER_MEDIA_CONF |
			  PROC_CMD_FIBER_PORT(vsc8531->addr) |
			  PROC_CMD_FIBER_DISABLE |
			  PROC_CMD_READ_MOD_WRITE_PORT |
			  PROC_CMD_RST_CONF_PORT | PROC_CMD_FIBER_100BASE_FX);
	अगर (ret)
		वापस ret;

	/* Disable SerDes क्रम 1000Base-X */
	वापस vsc8584_cmd(phydev, PROC_CMD_FIBER_MEDIA_CONF |
			   PROC_CMD_FIBER_PORT(vsc8531->addr) |
			   PROC_CMD_FIBER_DISABLE |
			   PROC_CMD_READ_MOD_WRITE_PORT |
			   PROC_CMD_RST_CONF_PORT | PROC_CMD_FIBER_1000BASE_X);
पूर्ण

अटल पूर्णांक vsc8584_config_init(काष्ठा phy_device *phydev)
अणु
	काष्ठा vsc8531_निजी *vsc8531 = phydev->priv;
	पूर्णांक ret, i;
	u16 val;

	phydev->mdix_ctrl = ETH_TP_MDI_AUTO;

	phy_lock_mdio_bus(phydev);

	/* Some parts of the init sequence are identical क्रम every PHY in the
	 * package. Some parts are modअगरying the GPIO रेजिस्टर bank which is a
	 * set of रेजिस्टरs that are affecting all PHYs, a few resetting the
	 * microprocessor common to all PHYs. The CRC check responsible of the
	 * checking the firmware within the 8051 microprocessor can only be
	 * accessed via the PHY whose पूर्णांकernal address in the package is 0.
	 * All PHYs' पूर्णांकerrupts mask रेजिस्टर has to be zeroed beक्रमe enabling
	 * any PHY's पूर्णांकerrupt in this रेजिस्टर.
	 * For all these reasons, we need to करो the init sequence once and only
	 * once whatever is the first PHY in the package that is initialized and
	 * करो the correct init sequence क्रम all PHYs that are package-critical
	 * in this pre-init function.
	 */
	अगर (phy_package_init_once(phydev)) अणु
		/* The following चयन statement assumes that the lowest
		 * nibble of the phy_id_mask is always 0. This works because
		 * the lowest nibble of the PHY_ID's below are also 0.
		 */
		WARN_ON(phydev->drv->phy_id_mask & 0xf);

		चयन (phydev->phy_id & phydev->drv->phy_id_mask) अणु
		हाल PHY_ID_VSC8504:
		हाल PHY_ID_VSC8552:
		हाल PHY_ID_VSC8572:
		हाल PHY_ID_VSC8574:
			ret = vsc8574_config_pre_init(phydev);
			अगर (ret)
				जाओ err;
			ret = vsc8574_config_host_serdes(phydev);
			अगर (ret)
				जाओ err;
			अवरोध;
		हाल PHY_ID_VSC856X:
		हाल PHY_ID_VSC8575:
		हाल PHY_ID_VSC8582:
		हाल PHY_ID_VSC8584:
			ret = vsc8584_config_pre_init(phydev);
			अगर (ret)
				जाओ err;
			ret = vsc8584_config_host_serdes(phydev);
			अगर (ret)
				जाओ err;
			vsc85xx_coma_mode_release(phydev);
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (ret)
			जाओ err;
	पूर्ण

	phy_unlock_mdio_bus(phydev);

	ret = vsc8584_macsec_init(phydev);
	अगर (ret)
		वापस ret;

	ret = vsc8584_ptp_init(phydev);
	अगर (ret)
		वापस ret;

	val = phy_पढ़ो(phydev, MSCC_PHY_EXT_PHY_CNTL_1);
	val &= ~(MEDIA_OP_MODE_MASK | VSC8584_MAC_IF_SELECTION_MASK);
	val |= (MEDIA_OP_MODE_COPPER << MEDIA_OP_MODE_POS) |
	       (VSC8584_MAC_IF_SELECTION_SGMII << VSC8584_MAC_IF_SELECTION_POS);
	ret = phy_ग_लिखो(phydev, MSCC_PHY_EXT_PHY_CNTL_1, val);
	अगर (ret)
		वापस ret;

	अगर (phy_पूर्णांकerface_is_rgmii(phydev)) अणु
		ret = vsc85xx_rgmii_set_skews(phydev, VSC8572_RGMII_CNTL,
					      VSC8572_RGMII_RX_DELAY_MASK,
					      VSC8572_RGMII_TX_DELAY_MASK);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = genphy_soft_reset(phydev);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < vsc8531->nleds; i++) अणु
		ret = vsc85xx_led_cntl_set(phydev, i, vsc8531->leds_mode[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;

err:
	phy_unlock_mdio_bus(phydev);
	वापस ret;
पूर्ण

अटल irqवापस_t vsc8584_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	irqवापस_t ret;
	पूर्णांक irq_status;

	irq_status = phy_पढ़ो(phydev, MII_VSC85XX_INT_STATUS);
	अगर (irq_status < 0)
		वापस IRQ_NONE;

	/* Timestamping IRQ करोes not set a bit in the global INT_STATUS, so
	 * irq_status would be 0.
	 */
	ret = vsc8584_handle_ts_पूर्णांकerrupt(phydev);
	अगर (!(irq_status & MII_VSC85XX_INT_MASK_MASK))
		वापस ret;

	अगर (irq_status & MII_VSC85XX_INT_MASK_EXT)
		vsc8584_handle_macsec_पूर्णांकerrupt(phydev);

	अगर (irq_status & MII_VSC85XX_INT_MASK_LINK_CHG)
		phy_trigger_machine(phydev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक vsc85xx_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक rc, i, phy_id;
	काष्ठा vsc8531_निजी *vsc8531 = phydev->priv;

	rc = vsc85xx_शेष_config(phydev);
	अगर (rc)
		वापस rc;

	rc = vsc85xx_mac_अगर_set(phydev, phydev->पूर्णांकerface);
	अगर (rc)
		वापस rc;

	rc = vsc85xx_edge_rate_cntl_set(phydev, vsc8531->rate_magic);
	अगर (rc)
		वापस rc;

	phy_id = phydev->drv->phy_id & phydev->drv->phy_id_mask;
	अगर (PHY_ID_VSC8531 == phy_id || PHY_ID_VSC8541 == phy_id ||
	    PHY_ID_VSC8530 == phy_id || PHY_ID_VSC8540 == phy_id) अणु
		rc = vsc8531_pre_init_seq_set(phydev);
		अगर (rc)
			वापस rc;
	पूर्ण

	rc = vsc85xx_eee_init_seq_set(phydev);
	अगर (rc)
		वापस rc;

	क्रम (i = 0; i < vsc8531->nleds; i++) अणु
		rc = vsc85xx_led_cntl_set(phydev, i, vsc8531->leds_mode[i]);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __phy_ग_लिखो_mcb_s6g(काष्ठा phy_device *phydev, u32 reg, u8 mcb,
			       u32 op)
अणु
	अचिन्हित दीर्घ deadline;
	u32 val;
	पूर्णांक ret;

	ret = vsc85xx_csr_ग_लिखो(phydev, PHY_MCB_TARGET, reg,
				op | (1 << mcb));
	अगर (ret)
		वापस -EINVAL;

	deadline = jअगरfies + msecs_to_jअगरfies(PROC_CMD_NCOMPLETED_TIMEOUT_MS);
	करो अणु
		usleep_range(500, 1000);
		val = vsc85xx_csr_पढ़ो(phydev, PHY_MCB_TARGET, reg);

		अगर (val == 0xffffffff)
			वापस -EIO;

	पूर्ण जबतक (समय_beक्रमe(jअगरfies, deadline) && (val & op));

	अगर (val & op)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

/* Trigger a पढ़ो to the specअगरied MCB */
पूर्णांक phy_update_mcb_s6g(काष्ठा phy_device *phydev, u32 reg, u8 mcb)
अणु
	वापस __phy_ग_लिखो_mcb_s6g(phydev, reg, mcb, PHY_MCB_S6G_READ);
पूर्ण

/* Trigger a ग_लिखो to the specअगरied MCB */
पूर्णांक phy_commit_mcb_s6g(काष्ठा phy_device *phydev, u32 reg, u8 mcb)
अणु
	वापस __phy_ग_लिखो_mcb_s6g(phydev, reg, mcb, PHY_MCB_S6G_WRITE);
पूर्ण

अटल पूर्णांक vsc8514_config_host_serdes(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;
	u16 val;

	ret = phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS,
			     MSCC_PHY_PAGE_EXTENDED_GPIO);
	अगर (ret)
		वापस ret;

	val = phy_base_पढ़ो(phydev, MSCC_PHY_MAC_CFG_FASTLINK);
	val &= ~MAC_CFG_MASK;
	val |= MAC_CFG_QSGMII;
	ret = phy_base_ग_लिखो(phydev, MSCC_PHY_MAC_CFG_FASTLINK, val);
	अगर (ret)
		वापस ret;

	ret = phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS,
			     MSCC_PHY_PAGE_STANDARD);
	अगर (ret)
		वापस ret;

	ret = vsc8584_cmd(phydev, PROC_CMD_NOP);
	अगर (ret)
		वापस ret;

	ret = vsc8584_cmd(phydev,
			  PROC_CMD_MCB_ACCESS_MAC_CONF |
			  PROC_CMD_RST_CONF_PORT |
			  PROC_CMD_READ_MOD_WRITE_PORT | PROC_CMD_QSGMII_MAC);
	अगर (ret) अणु
		dev_err(&phydev->mdio.dev, "%s: QSGMII error: %d\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	/* Apply 6G SerDes FOJI Algorithm
	 *  Initial condition requirement:
	 *  1. hold 8051 in reset
	 *  2. disable patch vector 0, in order to allow IB cal poll during FoJi
	 *  3. deनिश्चित 8051 reset after change patch vector status
	 *  4. proceed with FoJi (vsc85xx_sd6g_config_v2)
	 */
	vsc8584_micro_निश्चित_reset(phydev);
	val = phy_base_पढ़ो(phydev, MSCC_INT_MEM_CNTL);
	/* clear bit 8, to disable patch vector 0 */
	val &= ~PATCH_VEC_ZERO_EN;
	ret = phy_base_ग_लिखो(phydev, MSCC_INT_MEM_CNTL, val);
	/* Enable 8051 घड़ी, करोn't set patch present, disable PRAM घड़ी override */
	vsc8584_micro_deनिश्चित_reset(phydev, false);

	वापस vsc85xx_sd6g_config_v2(phydev);
पूर्ण

अटल पूर्णांक vsc8514_config_pre_init(काष्ठा phy_device *phydev)
अणु
	/* These are the settings to override the silicon शेष
	 * values to handle hardware perक्रमmance of PHY. They
	 * are set at Power-On state and reमुख्य until PHY Reset.
	 */
	अटल स्थिर काष्ठा reg_val pre_init1[] = अणु
		अणु0x0f90, 0x00688980पूर्ण,
		अणु0x0786, 0x00000003पूर्ण,
		अणु0x07fa, 0x0050100fपूर्ण,
		अणु0x0f82, 0x0012b002पूर्ण,
		अणु0x1686, 0x00000004पूर्ण,
		अणु0x168c, 0x00d2c46fपूर्ण,
		अणु0x17a2, 0x00000620पूर्ण,
		अणु0x16a0, 0x00eeffddपूर्ण,
		अणु0x16a6, 0x00071448पूर्ण,
		अणु0x16a4, 0x0013132fपूर्ण,
		अणु0x16a8, 0x00000000पूर्ण,
		अणु0x0ffc, 0x00c0a028पूर्ण,
		अणु0x0fe8, 0x0091b06cपूर्ण,
		अणु0x0fea, 0x00041600पूर्ण,
		अणु0x0f80, 0x00fffaffपूर्ण,
		अणु0x0fec, 0x00901809पूर्ण,
		अणु0x0ffe, 0x00b01007पूर्ण,
		अणु0x16b0, 0x00eeff00पूर्ण,
		अणु0x16b2, 0x00007000पूर्ण,
		अणु0x16b4, 0x00000814पूर्ण,
	पूर्ण;
	काष्ठा device *dev = &phydev->mdio.dev;
	अचिन्हित पूर्णांक i;
	u16 reg;
	पूर्णांक ret;

	ret = vsc8584_pll5g_reset(phydev);
	अगर (ret < 0) अणु
		dev_err(dev, "failed LCPLL reset, ret: %d\n", ret);
		वापस ret;
	पूर्ण

	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDARD);

	/* all ग_लिखोs below are broadcasted to all PHYs in the same package */
	reg = phy_base_पढ़ो(phydev, MSCC_PHY_EXT_CNTL_STATUS);
	reg |= SMI_BROADCAST_WR_EN;
	phy_base_ग_लिखो(phydev, MSCC_PHY_EXT_CNTL_STATUS, reg);

	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_TEST);

	reg = phy_base_पढ़ो(phydev, MSCC_PHY_TEST_PAGE_8);
	reg |= BIT(15);
	phy_base_ग_लिखो(phydev, MSCC_PHY_TEST_PAGE_8, reg);

	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_TR);

	क्रम (i = 0; i < ARRAY_SIZE(pre_init1); i++)
		vsc8584_csr_ग_लिखो(phydev, pre_init1[i].reg, pre_init1[i].val);

	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_TEST);

	reg = phy_base_पढ़ो(phydev, MSCC_PHY_TEST_PAGE_8);
	reg &= ~BIT(15);
	phy_base_ग_लिखो(phydev, MSCC_PHY_TEST_PAGE_8, reg);

	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS, MSCC_PHY_PAGE_STANDARD);

	reg = phy_base_पढ़ो(phydev, MSCC_PHY_EXT_CNTL_STATUS);
	reg &= ~SMI_BROADCAST_WR_EN;
	phy_base_ग_लिखो(phydev, MSCC_PHY_EXT_CNTL_STATUS, reg);

	/* Add pre-patching commands to:
	 * 1. enable 8051 घड़ी, operate 8051 घड़ी at 125 MHz
	 * instead of HW शेष 62.5MHz
	 * 2. ग_लिखो patch vector 0, to skip IB cal polling executed
	 * as part of the 0x80E0 ROM command
	 */
	vsc8584_micro_deनिश्चित_reset(phydev, false);

	vsc8584_micro_निश्चित_reset(phydev);
	phy_base_ग_लिखो(phydev, MSCC_EXT_PAGE_ACCESS,
		       MSCC_PHY_PAGE_EXTENDED_GPIO);
	/* ROM address to trap, क्रम patch vector 0 */
	reg = MSCC_ROM_TRAP_SERDES_6G_CFG;
	ret = phy_base_ग_लिखो(phydev, MSCC_TRAP_ROM_ADDR(1), reg);
	अगर (ret)
		जाओ err;
	/* RAM address to jump to, when patch vector 0 enabled */
	reg = MSCC_RAM_TRAP_SERDES_6G_CFG;
	ret = phy_base_ग_लिखो(phydev, MSCC_PATCH_RAM_ADDR(1), reg);
	अगर (ret)
		जाओ err;
	reg = phy_base_पढ़ो(phydev, MSCC_INT_MEM_CNTL);
	reg |= PATCH_VEC_ZERO_EN; /* bit 8, enable patch vector 0 */
	ret = phy_base_ग_लिखो(phydev, MSCC_INT_MEM_CNTL, reg);
	अगर (ret)
		जाओ err;

	/* Enable 8051 घड़ी, करोn't set patch present
	 * yet, disable PRAM घड़ी override
	 */
	vsc8584_micro_deनिश्चित_reset(phydev, false);
	वापस ret;
 err:
	/* restore 8051 and bail w error */
	vsc8584_micro_deनिश्चित_reset(phydev, false);
	वापस ret;
पूर्ण

अटल पूर्णांक vsc8514_config_init(काष्ठा phy_device *phydev)
अणु
	काष्ठा vsc8531_निजी *vsc8531 = phydev->priv;
	पूर्णांक ret, i;

	phydev->mdix_ctrl = ETH_TP_MDI_AUTO;

	phy_lock_mdio_bus(phydev);

	/* Some parts of the init sequence are identical क्रम every PHY in the
	 * package. Some parts are modअगरying the GPIO रेजिस्टर bank which is a
	 * set of रेजिस्टरs that are affecting all PHYs, a few resetting the
	 * microprocessor common to all PHYs.
	 * All PHYs' पूर्णांकerrupts mask रेजिस्टर has to be zeroed beक्रमe enabling
	 * any PHY's पूर्णांकerrupt in this रेजिस्टर.
	 * For all these reasons, we need to करो the init sequence once and only
	 * once whatever is the first PHY in the package that is initialized and
	 * करो the correct init sequence क्रम all PHYs that are package-critical
	 * in this pre-init function.
	 */
	अगर (phy_package_init_once(phydev)) अणु
		ret = vsc8514_config_pre_init(phydev);
		अगर (ret)
			जाओ err;
		ret = vsc8514_config_host_serdes(phydev);
		अगर (ret)
			जाओ err;
		vsc85xx_coma_mode_release(phydev);
	पूर्ण

	phy_unlock_mdio_bus(phydev);

	ret = phy_modअगरy(phydev, MSCC_PHY_EXT_PHY_CNTL_1, MEDIA_OP_MODE_MASK,
			 MEDIA_OP_MODE_COPPER << MEDIA_OP_MODE_POS);

	अगर (ret)
		वापस ret;

	ret = genphy_soft_reset(phydev);

	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < vsc8531->nleds; i++) अणु
		ret = vsc85xx_led_cntl_set(phydev, i, vsc8531->leds_mode[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ret;

err:
	phy_unlock_mdio_bus(phydev);
	वापस ret;
पूर्ण

अटल पूर्णांक vsc85xx_ack_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक rc = 0;

	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED)
		rc = phy_पढ़ो(phydev, MII_VSC85XX_INT_STATUS);

	वापस (rc < 0) ? rc : 0;
पूर्ण

अटल पूर्णांक vsc85xx_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	पूर्णांक rc;

	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED) अणु
		rc = vsc85xx_ack_पूर्णांकerrupt(phydev);
		अगर (rc)
			वापस rc;

		vsc8584_config_macsec_पूर्णांकr(phydev);
		vsc8584_config_ts_पूर्णांकr(phydev);

		rc = phy_ग_लिखो(phydev, MII_VSC85XX_INT_MASK,
			       MII_VSC85XX_INT_MASK_MASK);
	पूर्ण अन्यथा अणु
		rc = phy_ग_लिखो(phydev, MII_VSC85XX_INT_MASK, 0);
		अगर (rc < 0)
			वापस rc;
		rc = phy_पढ़ो(phydev, MII_VSC85XX_INT_STATUS);
		अगर (rc < 0)
			वापस rc;

		rc = vsc85xx_ack_पूर्णांकerrupt(phydev);
	पूर्ण

	वापस rc;
पूर्ण

अटल irqवापस_t vsc85xx_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक irq_status;

	irq_status = phy_पढ़ो(phydev, MII_VSC85XX_INT_STATUS);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	अगर (!(irq_status & MII_VSC85XX_INT_MASK_MASK))
		वापस IRQ_NONE;

	phy_trigger_machine(phydev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक vsc85xx_config_aneg(काष्ठा phy_device *phydev)
अणु
	पूर्णांक rc;

	rc = vsc85xx_mdix_set(phydev, phydev->mdix_ctrl);
	अगर (rc < 0)
		वापस rc;

	वापस genphy_config_aneg(phydev);
पूर्ण

अटल पूर्णांक vsc85xx_पढ़ो_status(काष्ठा phy_device *phydev)
अणु
	पूर्णांक rc;

	rc = vsc85xx_mdix_get(phydev, &phydev->mdix);
	अगर (rc < 0)
		वापस rc;

	वापस genphy_पढ़ो_status(phydev);
पूर्ण

अटल पूर्णांक vsc8514_probe(काष्ठा phy_device *phydev)
अणु
	काष्ठा vsc8531_निजी *vsc8531;
	u32 शेष_mode[4] = अणुVSC8531_LINK_1000_ACTIVITY,
	   VSC8531_LINK_100_ACTIVITY, VSC8531_LINK_ACTIVITY,
	   VSC8531_DUPLEX_COLLISIONपूर्ण;

	vsc8531 = devm_kzalloc(&phydev->mdio.dev, माप(*vsc8531), GFP_KERNEL);
	अगर (!vsc8531)
		वापस -ENOMEM;

	phydev->priv = vsc8531;

	vsc8584_get_base_addr(phydev);
	devm_phy_package_join(&phydev->mdio.dev, phydev,
			      vsc8531->base_addr, 0);

	vsc8531->nleds = 4;
	vsc8531->supp_led_modes = VSC85XX_SUPP_LED_MODES;
	vsc8531->hw_stats = vsc85xx_hw_stats;
	vsc8531->nstats = ARRAY_SIZE(vsc85xx_hw_stats);
	vsc8531->stats = devm_kसुस्मृति(&phydev->mdio.dev, vsc8531->nstats,
				      माप(u64), GFP_KERNEL);
	अगर (!vsc8531->stats)
		वापस -ENOMEM;

	वापस vsc85xx_dt_led_modes_get(phydev, शेष_mode);
पूर्ण

अटल पूर्णांक vsc8574_probe(काष्ठा phy_device *phydev)
अणु
	काष्ठा vsc8531_निजी *vsc8531;
	u32 शेष_mode[4] = अणुVSC8531_LINK_1000_ACTIVITY,
	   VSC8531_LINK_100_ACTIVITY, VSC8531_LINK_ACTIVITY,
	   VSC8531_DUPLEX_COLLISIONपूर्ण;

	vsc8531 = devm_kzalloc(&phydev->mdio.dev, माप(*vsc8531), GFP_KERNEL);
	अगर (!vsc8531)
		वापस -ENOMEM;

	phydev->priv = vsc8531;

	vsc8584_get_base_addr(phydev);
	devm_phy_package_join(&phydev->mdio.dev, phydev,
			      vsc8531->base_addr, 0);

	vsc8531->nleds = 4;
	vsc8531->supp_led_modes = VSC8584_SUPP_LED_MODES;
	vsc8531->hw_stats = vsc8584_hw_stats;
	vsc8531->nstats = ARRAY_SIZE(vsc8584_hw_stats);
	vsc8531->stats = devm_kसुस्मृति(&phydev->mdio.dev, vsc8531->nstats,
				      माप(u64), GFP_KERNEL);
	अगर (!vsc8531->stats)
		वापस -ENOMEM;

	वापस vsc85xx_dt_led_modes_get(phydev, शेष_mode);
पूर्ण

अटल पूर्णांक vsc8584_probe(काष्ठा phy_device *phydev)
अणु
	काष्ठा vsc8531_निजी *vsc8531;
	u32 शेष_mode[4] = अणुVSC8531_LINK_1000_ACTIVITY,
	   VSC8531_LINK_100_ACTIVITY, VSC8531_LINK_ACTIVITY,
	   VSC8531_DUPLEX_COLLISIONपूर्ण;
	पूर्णांक ret;

	अगर ((phydev->phy_id & MSCC_DEV_REV_MASK) != VSC8584_REVB) अणु
		dev_err(&phydev->mdio.dev, "Only VSC8584 revB is supported.\n");
		वापस -ENOTSUPP;
	पूर्ण

	vsc8531 = devm_kzalloc(&phydev->mdio.dev, माप(*vsc8531), GFP_KERNEL);
	अगर (!vsc8531)
		वापस -ENOMEM;

	phydev->priv = vsc8531;

	vsc8584_get_base_addr(phydev);
	devm_phy_package_join(&phydev->mdio.dev, phydev, vsc8531->base_addr,
			      माप(काष्ठा vsc85xx_shared_निजी));

	vsc8531->nleds = 4;
	vsc8531->supp_led_modes = VSC8584_SUPP_LED_MODES;
	vsc8531->hw_stats = vsc8584_hw_stats;
	vsc8531->nstats = ARRAY_SIZE(vsc8584_hw_stats);
	vsc8531->stats = devm_kसुस्मृति(&phydev->mdio.dev, vsc8531->nstats,
				      माप(u64), GFP_KERNEL);
	अगर (!vsc8531->stats)
		वापस -ENOMEM;

	अगर (phy_package_probe_once(phydev)) अणु
		ret = vsc8584_ptp_probe_once(phydev);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = vsc8584_ptp_probe(phydev);
	अगर (ret)
		वापस ret;

	वापस vsc85xx_dt_led_modes_get(phydev, शेष_mode);
पूर्ण

अटल पूर्णांक vsc85xx_probe(काष्ठा phy_device *phydev)
अणु
	काष्ठा vsc8531_निजी *vsc8531;
	पूर्णांक rate_magic;
	u32 शेष_mode[2] = अणुVSC8531_LINK_1000_ACTIVITY,
	   VSC8531_LINK_100_ACTIVITYपूर्ण;

	rate_magic = vsc85xx_edge_rate_magic_get(phydev);
	अगर (rate_magic < 0)
		वापस rate_magic;

	vsc8531 = devm_kzalloc(&phydev->mdio.dev, माप(*vsc8531), GFP_KERNEL);
	अगर (!vsc8531)
		वापस -ENOMEM;

	phydev->priv = vsc8531;

	vsc8531->rate_magic = rate_magic;
	vsc8531->nleds = 2;
	vsc8531->supp_led_modes = VSC85XX_SUPP_LED_MODES;
	vsc8531->hw_stats = vsc85xx_hw_stats;
	vsc8531->nstats = ARRAY_SIZE(vsc85xx_hw_stats);
	vsc8531->stats = devm_kसुस्मृति(&phydev->mdio.dev, vsc8531->nstats,
				      माप(u64), GFP_KERNEL);
	अगर (!vsc8531->stats)
		वापस -ENOMEM;

	वापस vsc85xx_dt_led_modes_get(phydev, शेष_mode);
पूर्ण

/* Microsemi VSC85xx PHYs */
अटल काष्ठा phy_driver vsc85xx_driver[] = अणु
अणु
	.phy_id		= PHY_ID_VSC8502,
	.name		= "Microsemi GE VSC8502 SyncE",
	.phy_id_mask	= 0xfffffff0,
	/* PHY_BASIC_FEATURES */
	.soft_reset	= &genphy_soft_reset,
	.config_init	= &vsc85xx_config_init,
	.config_aneg    = &vsc85xx_config_aneg,
	.पढ़ो_status	= &vsc85xx_पढ़ो_status,
	.handle_पूर्णांकerrupt = vsc85xx_handle_पूर्णांकerrupt,
	.config_पूर्णांकr	= &vsc85xx_config_पूर्णांकr,
	.suspend	= &genphy_suspend,
	.resume		= &genphy_resume,
	.probe		= &vsc85xx_probe,
	.set_wol	= &vsc85xx_wol_set,
	.get_wol	= &vsc85xx_wol_get,
	.get_tunable	= &vsc85xx_get_tunable,
	.set_tunable	= &vsc85xx_set_tunable,
	.पढ़ो_page	= &vsc85xx_phy_पढ़ो_page,
	.ग_लिखो_page	= &vsc85xx_phy_ग_लिखो_page,
	.get_sset_count = &vsc85xx_get_sset_count,
	.get_strings    = &vsc85xx_get_strings,
	.get_stats      = &vsc85xx_get_stats,
पूर्ण,
अणु
	.phy_id		= PHY_ID_VSC8504,
	.name		= "Microsemi GE VSC8504 SyncE",
	.phy_id_mask	= 0xfffffff0,
	/* PHY_GBIT_FEATURES */
	.soft_reset	= &genphy_soft_reset,
	.config_init    = &vsc8584_config_init,
	.config_aneg    = &vsc85xx_config_aneg,
	.aneg_करोne	= &genphy_aneg_करोne,
	.पढ़ो_status	= &vsc85xx_पढ़ो_status,
	.handle_पूर्णांकerrupt = vsc85xx_handle_पूर्णांकerrupt,
	.config_पूर्णांकr    = &vsc85xx_config_पूर्णांकr,
	.suspend	= &genphy_suspend,
	.resume		= &genphy_resume,
	.probe		= &vsc8574_probe,
	.set_wol	= &vsc85xx_wol_set,
	.get_wol	= &vsc85xx_wol_get,
	.get_tunable	= &vsc85xx_get_tunable,
	.set_tunable	= &vsc85xx_set_tunable,
	.पढ़ो_page	= &vsc85xx_phy_पढ़ो_page,
	.ग_लिखो_page	= &vsc85xx_phy_ग_लिखो_page,
	.get_sset_count = &vsc85xx_get_sset_count,
	.get_strings    = &vsc85xx_get_strings,
	.get_stats      = &vsc85xx_get_stats,
पूर्ण,
अणु
	.phy_id		= PHY_ID_VSC8514,
	.name		= "Microsemi GE VSC8514 SyncE",
	.phy_id_mask	= 0xfffffff0,
	.soft_reset	= &genphy_soft_reset,
	.config_init    = &vsc8514_config_init,
	.config_aneg    = &vsc85xx_config_aneg,
	.पढ़ो_status	= &vsc85xx_पढ़ो_status,
	.handle_पूर्णांकerrupt = vsc85xx_handle_पूर्णांकerrupt,
	.config_पूर्णांकr    = &vsc85xx_config_पूर्णांकr,
	.suspend	= &genphy_suspend,
	.resume		= &genphy_resume,
	.probe		= &vsc8514_probe,
	.set_wol	= &vsc85xx_wol_set,
	.get_wol	= &vsc85xx_wol_get,
	.get_tunable	= &vsc85xx_get_tunable,
	.set_tunable	= &vsc85xx_set_tunable,
	.पढ़ो_page      = &vsc85xx_phy_पढ़ो_page,
	.ग_लिखो_page     = &vsc85xx_phy_ग_लिखो_page,
	.get_sset_count = &vsc85xx_get_sset_count,
	.get_strings    = &vsc85xx_get_strings,
	.get_stats      = &vsc85xx_get_stats,
पूर्ण,
अणु
	.phy_id		= PHY_ID_VSC8530,
	.name		= "Microsemi FE VSC8530",
	.phy_id_mask	= 0xfffffff0,
	/* PHY_BASIC_FEATURES */
	.soft_reset	= &genphy_soft_reset,
	.config_init	= &vsc85xx_config_init,
	.config_aneg    = &vsc85xx_config_aneg,
	.पढ़ो_status	= &vsc85xx_पढ़ो_status,
	.handle_पूर्णांकerrupt = vsc85xx_handle_पूर्णांकerrupt,
	.config_पूर्णांकr	= &vsc85xx_config_पूर्णांकr,
	.suspend	= &genphy_suspend,
	.resume		= &genphy_resume,
	.probe		= &vsc85xx_probe,
	.set_wol	= &vsc85xx_wol_set,
	.get_wol	= &vsc85xx_wol_get,
	.get_tunable	= &vsc85xx_get_tunable,
	.set_tunable	= &vsc85xx_set_tunable,
	.पढ़ो_page	= &vsc85xx_phy_पढ़ो_page,
	.ग_लिखो_page	= &vsc85xx_phy_ग_लिखो_page,
	.get_sset_count = &vsc85xx_get_sset_count,
	.get_strings    = &vsc85xx_get_strings,
	.get_stats      = &vsc85xx_get_stats,
पूर्ण,
अणु
	.phy_id		= PHY_ID_VSC8531,
	.name		= "Microsemi VSC8531",
	.phy_id_mask    = 0xfffffff0,
	/* PHY_GBIT_FEATURES */
	.soft_reset	= &genphy_soft_reset,
	.config_init    = &vsc85xx_config_init,
	.config_aneg    = &vsc85xx_config_aneg,
	.पढ़ो_status	= &vsc85xx_पढ़ो_status,
	.handle_पूर्णांकerrupt = vsc85xx_handle_पूर्णांकerrupt,
	.config_पूर्णांकr    = &vsc85xx_config_पूर्णांकr,
	.suspend	= &genphy_suspend,
	.resume		= &genphy_resume,
	.probe		= &vsc85xx_probe,
	.set_wol	= &vsc85xx_wol_set,
	.get_wol	= &vsc85xx_wol_get,
	.get_tunable	= &vsc85xx_get_tunable,
	.set_tunable	= &vsc85xx_set_tunable,
	.पढ़ो_page	= &vsc85xx_phy_पढ़ो_page,
	.ग_लिखो_page	= &vsc85xx_phy_ग_लिखो_page,
	.get_sset_count = &vsc85xx_get_sset_count,
	.get_strings    = &vsc85xx_get_strings,
	.get_stats      = &vsc85xx_get_stats,
पूर्ण,
अणु
	.phy_id		= PHY_ID_VSC8540,
	.name		= "Microsemi FE VSC8540 SyncE",
	.phy_id_mask	= 0xfffffff0,
	/* PHY_BASIC_FEATURES */
	.soft_reset	= &genphy_soft_reset,
	.config_init	= &vsc85xx_config_init,
	.config_aneg	= &vsc85xx_config_aneg,
	.पढ़ो_status	= &vsc85xx_पढ़ो_status,
	.handle_पूर्णांकerrupt = vsc85xx_handle_पूर्णांकerrupt,
	.config_पूर्णांकr	= &vsc85xx_config_पूर्णांकr,
	.suspend	= &genphy_suspend,
	.resume		= &genphy_resume,
	.probe		= &vsc85xx_probe,
	.set_wol	= &vsc85xx_wol_set,
	.get_wol	= &vsc85xx_wol_get,
	.get_tunable	= &vsc85xx_get_tunable,
	.set_tunable	= &vsc85xx_set_tunable,
	.पढ़ो_page	= &vsc85xx_phy_पढ़ो_page,
	.ग_लिखो_page	= &vsc85xx_phy_ग_लिखो_page,
	.get_sset_count = &vsc85xx_get_sset_count,
	.get_strings    = &vsc85xx_get_strings,
	.get_stats      = &vsc85xx_get_stats,
पूर्ण,
अणु
	.phy_id		= PHY_ID_VSC8541,
	.name		= "Microsemi VSC8541 SyncE",
	.phy_id_mask    = 0xfffffff0,
	/* PHY_GBIT_FEATURES */
	.soft_reset	= &genphy_soft_reset,
	.config_init    = &vsc85xx_config_init,
	.config_aneg    = &vsc85xx_config_aneg,
	.पढ़ो_status	= &vsc85xx_पढ़ो_status,
	.handle_पूर्णांकerrupt = vsc85xx_handle_पूर्णांकerrupt,
	.config_पूर्णांकr    = &vsc85xx_config_पूर्णांकr,
	.suspend	= &genphy_suspend,
	.resume		= &genphy_resume,
	.probe		= &vsc85xx_probe,
	.set_wol	= &vsc85xx_wol_set,
	.get_wol	= &vsc85xx_wol_get,
	.get_tunable	= &vsc85xx_get_tunable,
	.set_tunable	= &vsc85xx_set_tunable,
	.पढ़ो_page	= &vsc85xx_phy_पढ़ो_page,
	.ग_लिखो_page	= &vsc85xx_phy_ग_लिखो_page,
	.get_sset_count = &vsc85xx_get_sset_count,
	.get_strings    = &vsc85xx_get_strings,
	.get_stats      = &vsc85xx_get_stats,
पूर्ण,
अणु
	.phy_id		= PHY_ID_VSC8552,
	.name		= "Microsemi GE VSC8552 SyncE",
	.phy_id_mask	= 0xfffffff0,
	/* PHY_GBIT_FEATURES */
	.soft_reset	= &genphy_soft_reset,
	.config_init    = &vsc8584_config_init,
	.config_aneg    = &vsc85xx_config_aneg,
	.पढ़ो_status	= &vsc85xx_पढ़ो_status,
	.handle_पूर्णांकerrupt = vsc85xx_handle_पूर्णांकerrupt,
	.config_पूर्णांकr    = &vsc85xx_config_पूर्णांकr,
	.suspend	= &genphy_suspend,
	.resume		= &genphy_resume,
	.probe		= &vsc8574_probe,
	.set_wol	= &vsc85xx_wol_set,
	.get_wol	= &vsc85xx_wol_get,
	.get_tunable	= &vsc85xx_get_tunable,
	.set_tunable	= &vsc85xx_set_tunable,
	.पढ़ो_page	= &vsc85xx_phy_पढ़ो_page,
	.ग_लिखो_page	= &vsc85xx_phy_ग_लिखो_page,
	.get_sset_count = &vsc85xx_get_sset_count,
	.get_strings    = &vsc85xx_get_strings,
	.get_stats      = &vsc85xx_get_stats,
पूर्ण,
अणु
	.phy_id		= PHY_ID_VSC856X,
	.name		= "Microsemi GE VSC856X SyncE",
	.phy_id_mask	= 0xfffffff0,
	/* PHY_GBIT_FEATURES */
	.soft_reset	= &genphy_soft_reset,
	.config_init    = &vsc8584_config_init,
	.config_aneg    = &vsc85xx_config_aneg,
	.पढ़ो_status	= &vsc85xx_पढ़ो_status,
	.handle_पूर्णांकerrupt = vsc85xx_handle_पूर्णांकerrupt,
	.config_पूर्णांकr    = &vsc85xx_config_पूर्णांकr,
	.suspend	= &genphy_suspend,
	.resume		= &genphy_resume,
	.probe		= &vsc8584_probe,
	.get_tunable	= &vsc85xx_get_tunable,
	.set_tunable	= &vsc85xx_set_tunable,
	.पढ़ो_page	= &vsc85xx_phy_पढ़ो_page,
	.ग_लिखो_page	= &vsc85xx_phy_ग_लिखो_page,
	.get_sset_count = &vsc85xx_get_sset_count,
	.get_strings    = &vsc85xx_get_strings,
	.get_stats      = &vsc85xx_get_stats,
पूर्ण,
अणु
	.phy_id		= PHY_ID_VSC8572,
	.name		= "Microsemi GE VSC8572 SyncE",
	.phy_id_mask	= 0xfffffff0,
	/* PHY_GBIT_FEATURES */
	.soft_reset	= &genphy_soft_reset,
	.config_init    = &vsc8584_config_init,
	.config_aneg    = &vsc85xx_config_aneg,
	.aneg_करोne	= &genphy_aneg_करोne,
	.पढ़ो_status	= &vsc85xx_पढ़ो_status,
	.handle_पूर्णांकerrupt = &vsc8584_handle_पूर्णांकerrupt,
	.config_पूर्णांकr    = &vsc85xx_config_पूर्णांकr,
	.suspend	= &genphy_suspend,
	.resume		= &genphy_resume,
	.probe		= &vsc8574_probe,
	.set_wol	= &vsc85xx_wol_set,
	.get_wol	= &vsc85xx_wol_get,
	.get_tunable	= &vsc85xx_get_tunable,
	.set_tunable	= &vsc85xx_set_tunable,
	.पढ़ो_page	= &vsc85xx_phy_पढ़ो_page,
	.ग_लिखो_page	= &vsc85xx_phy_ग_लिखो_page,
	.get_sset_count = &vsc85xx_get_sset_count,
	.get_strings    = &vsc85xx_get_strings,
	.get_stats      = &vsc85xx_get_stats,
पूर्ण,
अणु
	.phy_id		= PHY_ID_VSC8574,
	.name		= "Microsemi GE VSC8574 SyncE",
	.phy_id_mask	= 0xfffffff0,
	/* PHY_GBIT_FEATURES */
	.soft_reset	= &genphy_soft_reset,
	.config_init    = &vsc8584_config_init,
	.config_aneg    = &vsc85xx_config_aneg,
	.aneg_करोne	= &genphy_aneg_करोne,
	.पढ़ो_status	= &vsc85xx_पढ़ो_status,
	.handle_पूर्णांकerrupt = vsc85xx_handle_पूर्णांकerrupt,
	.config_पूर्णांकr    = &vsc85xx_config_पूर्णांकr,
	.suspend	= &genphy_suspend,
	.resume		= &genphy_resume,
	.probe		= &vsc8574_probe,
	.set_wol	= &vsc85xx_wol_set,
	.get_wol	= &vsc85xx_wol_get,
	.get_tunable	= &vsc85xx_get_tunable,
	.set_tunable	= &vsc85xx_set_tunable,
	.पढ़ो_page	= &vsc85xx_phy_पढ़ो_page,
	.ग_लिखो_page	= &vsc85xx_phy_ग_लिखो_page,
	.get_sset_count = &vsc85xx_get_sset_count,
	.get_strings    = &vsc85xx_get_strings,
	.get_stats      = &vsc85xx_get_stats,
पूर्ण,
अणु
	.phy_id		= PHY_ID_VSC8575,
	.name		= "Microsemi GE VSC8575 SyncE",
	.phy_id_mask	= 0xfffffff0,
	/* PHY_GBIT_FEATURES */
	.soft_reset	= &genphy_soft_reset,
	.config_init    = &vsc8584_config_init,
	.config_aneg    = &vsc85xx_config_aneg,
	.aneg_करोne	= &genphy_aneg_करोne,
	.पढ़ो_status	= &vsc85xx_पढ़ो_status,
	.handle_पूर्णांकerrupt = &vsc8584_handle_पूर्णांकerrupt,
	.config_पूर्णांकr    = &vsc85xx_config_पूर्णांकr,
	.suspend	= &genphy_suspend,
	.resume		= &genphy_resume,
	.probe		= &vsc8584_probe,
	.get_tunable	= &vsc85xx_get_tunable,
	.set_tunable	= &vsc85xx_set_tunable,
	.पढ़ो_page	= &vsc85xx_phy_पढ़ो_page,
	.ग_लिखो_page	= &vsc85xx_phy_ग_लिखो_page,
	.get_sset_count = &vsc85xx_get_sset_count,
	.get_strings    = &vsc85xx_get_strings,
	.get_stats      = &vsc85xx_get_stats,
पूर्ण,
अणु
	.phy_id		= PHY_ID_VSC8582,
	.name		= "Microsemi GE VSC8582 SyncE",
	.phy_id_mask	= 0xfffffff0,
	/* PHY_GBIT_FEATURES */
	.soft_reset	= &genphy_soft_reset,
	.config_init    = &vsc8584_config_init,
	.config_aneg    = &vsc85xx_config_aneg,
	.aneg_करोne	= &genphy_aneg_करोne,
	.पढ़ो_status	= &vsc85xx_पढ़ो_status,
	.handle_पूर्णांकerrupt = &vsc8584_handle_पूर्णांकerrupt,
	.config_पूर्णांकr    = &vsc85xx_config_पूर्णांकr,
	.suspend	= &genphy_suspend,
	.resume		= &genphy_resume,
	.probe		= &vsc8584_probe,
	.get_tunable	= &vsc85xx_get_tunable,
	.set_tunable	= &vsc85xx_set_tunable,
	.पढ़ो_page	= &vsc85xx_phy_पढ़ो_page,
	.ग_लिखो_page	= &vsc85xx_phy_ग_लिखो_page,
	.get_sset_count = &vsc85xx_get_sset_count,
	.get_strings    = &vsc85xx_get_strings,
	.get_stats      = &vsc85xx_get_stats,
पूर्ण,
अणु
	.phy_id		= PHY_ID_VSC8584,
	.name		= "Microsemi GE VSC8584 SyncE",
	.phy_id_mask	= 0xfffffff0,
	/* PHY_GBIT_FEATURES */
	.soft_reset	= &genphy_soft_reset,
	.config_init    = &vsc8584_config_init,
	.config_aneg    = &vsc85xx_config_aneg,
	.aneg_करोne	= &genphy_aneg_करोne,
	.पढ़ो_status	= &vsc85xx_पढ़ो_status,
	.handle_पूर्णांकerrupt = &vsc8584_handle_पूर्णांकerrupt,
	.config_पूर्णांकr    = &vsc85xx_config_पूर्णांकr,
	.suspend	= &genphy_suspend,
	.resume		= &genphy_resume,
	.probe		= &vsc8584_probe,
	.get_tunable	= &vsc85xx_get_tunable,
	.set_tunable	= &vsc85xx_set_tunable,
	.पढ़ो_page	= &vsc85xx_phy_पढ़ो_page,
	.ग_लिखो_page	= &vsc85xx_phy_ग_लिखो_page,
	.get_sset_count = &vsc85xx_get_sset_count,
	.get_strings    = &vsc85xx_get_strings,
	.get_stats      = &vsc85xx_get_stats,
	.link_change_notअगरy = &vsc85xx_link_change_notअगरy,
पूर्ण

पूर्ण;

module_phy_driver(vsc85xx_driver);

अटल काष्ठा mdio_device_id __maybe_unused vsc85xx_tbl[] = अणु
	अणु PHY_ID_VSC8504, 0xfffffff0, पूर्ण,
	अणु PHY_ID_VSC8514, 0xfffffff0, पूर्ण,
	अणु PHY_ID_VSC8530, 0xfffffff0, पूर्ण,
	अणु PHY_ID_VSC8531, 0xfffffff0, पूर्ण,
	अणु PHY_ID_VSC8540, 0xfffffff0, पूर्ण,
	अणु PHY_ID_VSC8541, 0xfffffff0, पूर्ण,
	अणु PHY_ID_VSC8552, 0xfffffff0, पूर्ण,
	अणु PHY_ID_VSC856X, 0xfffffff0, पूर्ण,
	अणु PHY_ID_VSC8572, 0xfffffff0, पूर्ण,
	अणु PHY_ID_VSC8574, 0xfffffff0, पूर्ण,
	अणु PHY_ID_VSC8575, 0xfffffff0, पूर्ण,
	अणु PHY_ID_VSC8582, 0xfffffff0, पूर्ण,
	अणु PHY_ID_VSC8584, 0xfffffff0, पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(mdio, vsc85xx_tbl);

MODULE_DESCRIPTION("Microsemi VSC85xx PHY driver");
MODULE_AUTHOR("Nagaraju Lakkaraju");
MODULE_LICENSE("Dual MIT/GPL");
