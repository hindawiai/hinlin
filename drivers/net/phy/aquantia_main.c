<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम Aquantia PHY
 *
 * Author: Shaohui Xie <Shaohui.Xie@मुक्तscale.com>
 *
 * Copyright 2015 Freescale Semiconductor, Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/phy.h>

#समावेश "aquantia.h"

#घोषणा PHY_ID_AQ1202	0x03a1b445
#घोषणा PHY_ID_AQ2104	0x03a1b460
#घोषणा PHY_ID_AQR105	0x03a1b4a2
#घोषणा PHY_ID_AQR106	0x03a1b4d0
#घोषणा PHY_ID_AQR107	0x03a1b4e0
#घोषणा PHY_ID_AQCS109	0x03a1b5c2
#घोषणा PHY_ID_AQR405	0x03a1b4b0

#घोषणा MDIO_PHYXS_VEND_IF_STATUS		0xe812
#घोषणा MDIO_PHYXS_VEND_IF_STATUS_TYPE_MASK	GENMASK(7, 3)
#घोषणा MDIO_PHYXS_VEND_IF_STATUS_TYPE_KR	0
#घोषणा MDIO_PHYXS_VEND_IF_STATUS_TYPE_XFI	2
#घोषणा MDIO_PHYXS_VEND_IF_STATUS_TYPE_USXGMII	3
#घोषणा MDIO_PHYXS_VEND_IF_STATUS_TYPE_SGMII	6
#घोषणा MDIO_PHYXS_VEND_IF_STATUS_TYPE_OCSGMII	10

#घोषणा MDIO_AN_VEND_PROV			0xc400
#घोषणा MDIO_AN_VEND_PROV_1000BASET_FULL	BIT(15)
#घोषणा MDIO_AN_VEND_PROV_1000BASET_HALF	BIT(14)
#घोषणा MDIO_AN_VEND_PROV_DOWNSHIFT_EN		BIT(4)
#घोषणा MDIO_AN_VEND_PROV_DOWNSHIFT_MASK	GENMASK(3, 0)
#घोषणा MDIO_AN_VEND_PROV_DOWNSHIFT_DFLT	4

#घोषणा MDIO_AN_TX_VEND_STATUS1			0xc800
#घोषणा MDIO_AN_TX_VEND_STATUS1_RATE_MASK	GENMASK(3, 1)
#घोषणा MDIO_AN_TX_VEND_STATUS1_10BASET		0
#घोषणा MDIO_AN_TX_VEND_STATUS1_100BASETX	1
#घोषणा MDIO_AN_TX_VEND_STATUS1_1000BASET	2
#घोषणा MDIO_AN_TX_VEND_STATUS1_10GBASET	3
#घोषणा MDIO_AN_TX_VEND_STATUS1_2500BASET	4
#घोषणा MDIO_AN_TX_VEND_STATUS1_5000BASET	5
#घोषणा MDIO_AN_TX_VEND_STATUS1_FULL_DUPLEX	BIT(0)

#घोषणा MDIO_AN_TX_VEND_INT_STATUS1		0xcc00
#घोषणा MDIO_AN_TX_VEND_INT_STATUS1_DOWNSHIFT	BIT(1)

#घोषणा MDIO_AN_TX_VEND_INT_STATUS2		0xcc01
#घोषणा MDIO_AN_TX_VEND_INT_STATUS2_MASK	BIT(0)

#घोषणा MDIO_AN_TX_VEND_INT_MASK2		0xd401
#घोषणा MDIO_AN_TX_VEND_INT_MASK2_LINK		BIT(0)

#घोषणा MDIO_AN_RX_LP_STAT1			0xe820
#घोषणा MDIO_AN_RX_LP_STAT1_1000BASET_FULL	BIT(15)
#घोषणा MDIO_AN_RX_LP_STAT1_1000BASET_HALF	BIT(14)
#घोषणा MDIO_AN_RX_LP_STAT1_SHORT_REACH		BIT(13)
#घोषणा MDIO_AN_RX_LP_STAT1_AQRATE_DOWNSHIFT	BIT(12)
#घोषणा MDIO_AN_RX_LP_STAT1_AQ_PHY		BIT(2)

#घोषणा MDIO_AN_RX_LP_STAT4			0xe823
#घोषणा MDIO_AN_RX_LP_STAT4_FW_MAJOR		GENMASK(15, 8)
#घोषणा MDIO_AN_RX_LP_STAT4_FW_MINOR		GENMASK(7, 0)

#घोषणा MDIO_AN_RX_VEND_STAT3			0xe832
#घोषणा MDIO_AN_RX_VEND_STAT3_AFR		BIT(0)

/* MDIO_MMD_C22EXT */
#घोषणा MDIO_C22EXT_STAT_SGMII_RX_GOOD_FRAMES		0xd292
#घोषणा MDIO_C22EXT_STAT_SGMII_RX_BAD_FRAMES		0xd294
#घोषणा MDIO_C22EXT_STAT_SGMII_RX_FALSE_CARRIER		0xd297
#घोषणा MDIO_C22EXT_STAT_SGMII_TX_GOOD_FRAMES		0xd313
#घोषणा MDIO_C22EXT_STAT_SGMII_TX_BAD_FRAMES		0xd315
#घोषणा MDIO_C22EXT_STAT_SGMII_TX_FALSE_CARRIER		0xd317
#घोषणा MDIO_C22EXT_STAT_SGMII_TX_COLLISIONS		0xd318
#घोषणा MDIO_C22EXT_STAT_SGMII_TX_LINE_COLLISIONS	0xd319
#घोषणा MDIO_C22EXT_STAT_SGMII_TX_FRAME_ALIGN_ERR	0xd31a
#घोषणा MDIO_C22EXT_STAT_SGMII_TX_RUNT_FRAMES		0xd31b

/* Venकरोr specअगरic 1, MDIO_MMD_VEND1 */
#घोषणा VEND1_GLOBAL_FW_ID			0x0020
#घोषणा VEND1_GLOBAL_FW_ID_MAJOR		GENMASK(15, 8)
#घोषणा VEND1_GLOBAL_FW_ID_MINOR		GENMASK(7, 0)

#घोषणा VEND1_GLOBAL_RSVD_STAT1			0xc885
#घोषणा VEND1_GLOBAL_RSVD_STAT1_FW_BUILD_ID	GENMASK(7, 4)
#घोषणा VEND1_GLOBAL_RSVD_STAT1_PROV_ID		GENMASK(3, 0)

#घोषणा VEND1_GLOBAL_RSVD_STAT9			0xc88d
#घोषणा VEND1_GLOBAL_RSVD_STAT9_MODE		GENMASK(7, 0)
#घोषणा VEND1_GLOBAL_RSVD_STAT9_1000BT2		0x23

#घोषणा VEND1_GLOBAL_INT_STD_STATUS		0xfc00
#घोषणा VEND1_GLOBAL_INT_VEND_STATUS		0xfc01

#घोषणा VEND1_GLOBAL_INT_STD_MASK		0xff00
#घोषणा VEND1_GLOBAL_INT_STD_MASK_PMA1		BIT(15)
#घोषणा VEND1_GLOBAL_INT_STD_MASK_PMA2		BIT(14)
#घोषणा VEND1_GLOBAL_INT_STD_MASK_PCS1		BIT(13)
#घोषणा VEND1_GLOBAL_INT_STD_MASK_PCS2		BIT(12)
#घोषणा VEND1_GLOBAL_INT_STD_MASK_PCS3		BIT(11)
#घोषणा VEND1_GLOBAL_INT_STD_MASK_PHY_XS1	BIT(10)
#घोषणा VEND1_GLOBAL_INT_STD_MASK_PHY_XS2	BIT(9)
#घोषणा VEND1_GLOBAL_INT_STD_MASK_AN1		BIT(8)
#घोषणा VEND1_GLOBAL_INT_STD_MASK_AN2		BIT(7)
#घोषणा VEND1_GLOBAL_INT_STD_MASK_GBE		BIT(6)
#घोषणा VEND1_GLOBAL_INT_STD_MASK_ALL		BIT(0)

#घोषणा VEND1_GLOBAL_INT_VEND_MASK		0xff01
#घोषणा VEND1_GLOBAL_INT_VEND_MASK_PMA		BIT(15)
#घोषणा VEND1_GLOBAL_INT_VEND_MASK_PCS		BIT(14)
#घोषणा VEND1_GLOBAL_INT_VEND_MASK_PHY_XS	BIT(13)
#घोषणा VEND1_GLOBAL_INT_VEND_MASK_AN		BIT(12)
#घोषणा VEND1_GLOBAL_INT_VEND_MASK_GBE		BIT(11)
#घोषणा VEND1_GLOBAL_INT_VEND_MASK_GLOBAL1	BIT(2)
#घोषणा VEND1_GLOBAL_INT_VEND_MASK_GLOBAL2	BIT(1)
#घोषणा VEND1_GLOBAL_INT_VEND_MASK_GLOBAL3	BIT(0)

काष्ठा aqr107_hw_stat अणु
	स्थिर अक्षर *name;
	पूर्णांक reg;
	पूर्णांक size;
पूर्ण;

#घोषणा SGMII_STAT(n, r, s) अणु n, MDIO_C22EXT_STAT_SGMII_ ## r, s पूर्ण
अटल स्थिर काष्ठा aqr107_hw_stat aqr107_hw_stats[] = अणु
	SGMII_STAT("sgmii_rx_good_frames",	    RX_GOOD_FRAMES,	26),
	SGMII_STAT("sgmii_rx_bad_frames",	    RX_BAD_FRAMES,	26),
	SGMII_STAT("sgmii_rx_false_carrier_events", RX_FALSE_CARRIER,	 8),
	SGMII_STAT("sgmii_tx_good_frames",	    TX_GOOD_FRAMES,	26),
	SGMII_STAT("sgmii_tx_bad_frames",	    TX_BAD_FRAMES,	26),
	SGMII_STAT("sgmii_tx_false_carrier_events", TX_FALSE_CARRIER,	 8),
	SGMII_STAT("sgmii_tx_collisions",	    TX_COLLISIONS,	 8),
	SGMII_STAT("sgmii_tx_line_collisions",	    TX_LINE_COLLISIONS,	 8),
	SGMII_STAT("sgmii_tx_frame_alignment_err",  TX_FRAME_ALIGN_ERR,	16),
	SGMII_STAT("sgmii_tx_runt_frames",	    TX_RUNT_FRAMES,	22),
पूर्ण;
#घोषणा AQR107_SGMII_STAT_SZ ARRAY_SIZE(aqr107_hw_stats)

काष्ठा aqr107_priv अणु
	u64 sgmii_stats[AQR107_SGMII_STAT_SZ];
पूर्ण;

अटल पूर्णांक aqr107_get_sset_count(काष्ठा phy_device *phydev)
अणु
	वापस AQR107_SGMII_STAT_SZ;
पूर्ण

अटल व्योम aqr107_get_strings(काष्ठा phy_device *phydev, u8 *data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < AQR107_SGMII_STAT_SZ; i++)
		strscpy(data + i * ETH_GSTRING_LEN, aqr107_hw_stats[i].name,
			ETH_GSTRING_LEN);
पूर्ण

अटल u64 aqr107_get_stat(काष्ठा phy_device *phydev, पूर्णांक index)
अणु
	स्थिर काष्ठा aqr107_hw_stat *stat = aqr107_hw_stats + index;
	पूर्णांक len_l = min(stat->size, 16);
	पूर्णांक len_h = stat->size - len_l;
	u64 ret;
	पूर्णांक val;

	val = phy_पढ़ो_mmd(phydev, MDIO_MMD_C22EXT, stat->reg);
	अगर (val < 0)
		वापस U64_MAX;

	ret = val & GENMASK(len_l - 1, 0);
	अगर (len_h) अणु
		val = phy_पढ़ो_mmd(phydev, MDIO_MMD_C22EXT, stat->reg + 1);
		अगर (val < 0)
			वापस U64_MAX;

		ret += (val & GENMASK(len_h - 1, 0)) << 16;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम aqr107_get_stats(काष्ठा phy_device *phydev,
			     काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा aqr107_priv *priv = phydev->priv;
	u64 val;
	पूर्णांक i;

	क्रम (i = 0; i < AQR107_SGMII_STAT_SZ; i++) अणु
		val = aqr107_get_stat(phydev, i);
		अगर (val == U64_MAX)
			phydev_err(phydev, "Reading HW Statistics failed for %s\n",
				   aqr107_hw_stats[i].name);
		अन्यथा
			priv->sgmii_stats[i] += val;

		data[i] = priv->sgmii_stats[i];
	पूर्ण
पूर्ण

अटल पूर्णांक aqr_config_aneg(काष्ठा phy_device *phydev)
अणु
	bool changed = false;
	u16 reg;
	पूर्णांक ret;

	अगर (phydev->स्वतःneg == AUTONEG_DISABLE)
		वापस genphy_c45_pma_setup_क्रमced(phydev);

	ret = genphy_c45_an_config_aneg(phydev);
	अगर (ret < 0)
		वापस ret;
	अगर (ret > 0)
		changed = true;

	/* Clause 45 has no standardized support क्रम 1000BaseT, thereक्रमe
	 * use venकरोr रेजिस्टरs क्रम this mode.
	 */
	reg = 0;
	अगर (linkmode_test_bit(ETHTOOL_LINK_MODE_1000baseT_Full_BIT,
			      phydev->advertising))
		reg |= MDIO_AN_VEND_PROV_1000BASET_FULL;

	अगर (linkmode_test_bit(ETHTOOL_LINK_MODE_1000baseT_Half_BIT,
			      phydev->advertising))
		reg |= MDIO_AN_VEND_PROV_1000BASET_HALF;

	ret = phy_modअगरy_mmd_changed(phydev, MDIO_MMD_AN, MDIO_AN_VEND_PROV,
				     MDIO_AN_VEND_PROV_1000BASET_HALF |
				     MDIO_AN_VEND_PROV_1000BASET_FULL, reg);
	अगर (ret < 0)
		वापस ret;
	अगर (ret > 0)
		changed = true;

	वापस genphy_c45_check_and_restart_aneg(phydev, changed);
पूर्ण

अटल पूर्णांक aqr_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	bool en = phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED;
	पूर्णांक err;

	अगर (en) अणु
		/* Clear any pending पूर्णांकerrupts beक्रमe enabling them */
		err = phy_पढ़ो_mmd(phydev, MDIO_MMD_AN, MDIO_AN_TX_VEND_INT_STATUS2);
		अगर (err < 0)
			वापस err;
	पूर्ण

	err = phy_ग_लिखो_mmd(phydev, MDIO_MMD_AN, MDIO_AN_TX_VEND_INT_MASK2,
			    en ? MDIO_AN_TX_VEND_INT_MASK2_LINK : 0);
	अगर (err < 0)
		वापस err;

	err = phy_ग_लिखो_mmd(phydev, MDIO_MMD_VEND1, VEND1_GLOBAL_INT_STD_MASK,
			    en ? VEND1_GLOBAL_INT_STD_MASK_ALL : 0);
	अगर (err < 0)
		वापस err;

	err = phy_ग_लिखो_mmd(phydev, MDIO_MMD_VEND1, VEND1_GLOBAL_INT_VEND_MASK,
			    en ? VEND1_GLOBAL_INT_VEND_MASK_GLOBAL3 |
			    VEND1_GLOBAL_INT_VEND_MASK_AN : 0);
	अगर (err < 0)
		वापस err;

	अगर (!en) अणु
		/* Clear any pending पूर्णांकerrupts after we have disabled them */
		err = phy_पढ़ो_mmd(phydev, MDIO_MMD_AN, MDIO_AN_TX_VEND_INT_STATUS2);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t aqr_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक irq_status;

	irq_status = phy_पढ़ो_mmd(phydev, MDIO_MMD_AN,
				  MDIO_AN_TX_VEND_INT_STATUS2);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	अगर (!(irq_status & MDIO_AN_TX_VEND_INT_STATUS2_MASK))
		वापस IRQ_NONE;

	phy_trigger_machine(phydev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक aqr_पढ़ो_status(काष्ठा phy_device *phydev)
अणु
	पूर्णांक val;

	अगर (phydev->स्वतःneg == AUTONEG_ENABLE) अणु
		val = phy_पढ़ो_mmd(phydev, MDIO_MMD_AN, MDIO_AN_RX_LP_STAT1);
		अगर (val < 0)
			वापस val;

		linkmode_mod_bit(ETHTOOL_LINK_MODE_1000baseT_Full_BIT,
				 phydev->lp_advertising,
				 val & MDIO_AN_RX_LP_STAT1_1000BASET_FULL);
		linkmode_mod_bit(ETHTOOL_LINK_MODE_1000baseT_Half_BIT,
				 phydev->lp_advertising,
				 val & MDIO_AN_RX_LP_STAT1_1000BASET_HALF);
	पूर्ण

	वापस genphy_c45_पढ़ो_status(phydev);
पूर्ण

अटल पूर्णांक aqr107_पढ़ो_rate(काष्ठा phy_device *phydev)
अणु
	पूर्णांक val;

	val = phy_पढ़ो_mmd(phydev, MDIO_MMD_AN, MDIO_AN_TX_VEND_STATUS1);
	अगर (val < 0)
		वापस val;

	चयन (FIELD_GET(MDIO_AN_TX_VEND_STATUS1_RATE_MASK, val)) अणु
	हाल MDIO_AN_TX_VEND_STATUS1_10BASET:
		phydev->speed = SPEED_10;
		अवरोध;
	हाल MDIO_AN_TX_VEND_STATUS1_100BASETX:
		phydev->speed = SPEED_100;
		अवरोध;
	हाल MDIO_AN_TX_VEND_STATUS1_1000BASET:
		phydev->speed = SPEED_1000;
		अवरोध;
	हाल MDIO_AN_TX_VEND_STATUS1_2500BASET:
		phydev->speed = SPEED_2500;
		अवरोध;
	हाल MDIO_AN_TX_VEND_STATUS1_5000BASET:
		phydev->speed = SPEED_5000;
		अवरोध;
	हाल MDIO_AN_TX_VEND_STATUS1_10GBASET:
		phydev->speed = SPEED_10000;
		अवरोध;
	शेष:
		phydev->speed = SPEED_UNKNOWN;
		अवरोध;
	पूर्ण

	अगर (val & MDIO_AN_TX_VEND_STATUS1_FULL_DUPLEX)
		phydev->duplex = DUPLEX_FULL;
	अन्यथा
		phydev->duplex = DUPLEX_HALF;

	वापस 0;
पूर्ण

अटल पूर्णांक aqr107_पढ़ो_status(काष्ठा phy_device *phydev)
अणु
	पूर्णांक val, ret;

	ret = aqr_पढ़ो_status(phydev);
	अगर (ret)
		वापस ret;

	अगर (!phydev->link || phydev->स्वतःneg == AUTONEG_DISABLE)
		वापस 0;

	val = phy_पढ़ो_mmd(phydev, MDIO_MMD_PHYXS, MDIO_PHYXS_VEND_IF_STATUS);
	अगर (val < 0)
		वापस val;

	चयन (FIELD_GET(MDIO_PHYXS_VEND_IF_STATUS_TYPE_MASK, val)) अणु
	हाल MDIO_PHYXS_VEND_IF_STATUS_TYPE_KR:
		phydev->पूर्णांकerface = PHY_INTERFACE_MODE_10GKR;
		अवरोध;
	हाल MDIO_PHYXS_VEND_IF_STATUS_TYPE_XFI:
		phydev->पूर्णांकerface = PHY_INTERFACE_MODE_10GBASER;
		अवरोध;
	हाल MDIO_PHYXS_VEND_IF_STATUS_TYPE_USXGMII:
		phydev->पूर्णांकerface = PHY_INTERFACE_MODE_USXGMII;
		अवरोध;
	हाल MDIO_PHYXS_VEND_IF_STATUS_TYPE_SGMII:
		phydev->पूर्णांकerface = PHY_INTERFACE_MODE_SGMII;
		अवरोध;
	हाल MDIO_PHYXS_VEND_IF_STATUS_TYPE_OCSGMII:
		phydev->पूर्णांकerface = PHY_INTERFACE_MODE_2500BASEX;
		अवरोध;
	शेष:
		phydev->पूर्णांकerface = PHY_INTERFACE_MODE_NA;
		अवरोध;
	पूर्ण

	/* Read possibly करोwnshअगरted rate from venकरोr रेजिस्टर */
	वापस aqr107_पढ़ो_rate(phydev);
पूर्ण

अटल पूर्णांक aqr107_get_करोwnshअगरt(काष्ठा phy_device *phydev, u8 *data)
अणु
	पूर्णांक val, cnt, enable;

	val = phy_पढ़ो_mmd(phydev, MDIO_MMD_AN, MDIO_AN_VEND_PROV);
	अगर (val < 0)
		वापस val;

	enable = FIELD_GET(MDIO_AN_VEND_PROV_DOWNSHIFT_EN, val);
	cnt = FIELD_GET(MDIO_AN_VEND_PROV_DOWNSHIFT_MASK, val);

	*data = enable && cnt ? cnt : DOWNSHIFT_DEV_DISABLE;

	वापस 0;
पूर्ण

अटल पूर्णांक aqr107_set_करोwnshअगरt(काष्ठा phy_device *phydev, u8 cnt)
अणु
	पूर्णांक val = 0;

	अगर (!FIELD_FIT(MDIO_AN_VEND_PROV_DOWNSHIFT_MASK, cnt))
		वापस -E2BIG;

	अगर (cnt != DOWNSHIFT_DEV_DISABLE) अणु
		val = MDIO_AN_VEND_PROV_DOWNSHIFT_EN;
		val |= FIELD_PREP(MDIO_AN_VEND_PROV_DOWNSHIFT_MASK, cnt);
	पूर्ण

	वापस phy_modअगरy_mmd(phydev, MDIO_MMD_AN, MDIO_AN_VEND_PROV,
			      MDIO_AN_VEND_PROV_DOWNSHIFT_EN |
			      MDIO_AN_VEND_PROV_DOWNSHIFT_MASK, val);
पूर्ण

अटल पूर्णांक aqr107_get_tunable(काष्ठा phy_device *phydev,
			      काष्ठा ethtool_tunable *tuna, व्योम *data)
अणु
	चयन (tuna->id) अणु
	हाल ETHTOOL_PHY_DOWNSHIFT:
		वापस aqr107_get_करोwnshअगरt(phydev, data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक aqr107_set_tunable(काष्ठा phy_device *phydev,
			      काष्ठा ethtool_tunable *tuna, स्थिर व्योम *data)
अणु
	चयन (tuna->id) अणु
	हाल ETHTOOL_PHY_DOWNSHIFT:
		वापस aqr107_set_करोwnshअगरt(phydev, *(स्थिर u8 *)data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

/* If we configure settings whilst firmware is still initializing the chip,
 * then these settings may be overwritten. Thereक्रमe make sure chip
 * initialization has completed. Use presence of the firmware ID as
 * indicator क्रम initialization having completed.
 * The chip also provides a "reset completed" bit, but it's cleared after
 * पढ़ो. Thereक्रमe function would समय out अगर called again.
 */
अटल पूर्णांक aqr107_रुको_reset_complete(काष्ठा phy_device *phydev)
अणु
	पूर्णांक val;

	वापस phy_पढ़ो_mmd_poll_समयout(phydev, MDIO_MMD_VEND1,
					 VEND1_GLOBAL_FW_ID, val, val != 0,
					 20000, 2000000, false);
पूर्ण

अटल व्योम aqr107_chip_info(काष्ठा phy_device *phydev)
अणु
	u8 fw_major, fw_minor, build_id, prov_id;
	पूर्णांक val;

	val = phy_पढ़ो_mmd(phydev, MDIO_MMD_VEND1, VEND1_GLOBAL_FW_ID);
	अगर (val < 0)
		वापस;

	fw_major = FIELD_GET(VEND1_GLOBAL_FW_ID_MAJOR, val);
	fw_minor = FIELD_GET(VEND1_GLOBAL_FW_ID_MINOR, val);

	val = phy_पढ़ो_mmd(phydev, MDIO_MMD_VEND1, VEND1_GLOBAL_RSVD_STAT1);
	अगर (val < 0)
		वापस;

	build_id = FIELD_GET(VEND1_GLOBAL_RSVD_STAT1_FW_BUILD_ID, val);
	prov_id = FIELD_GET(VEND1_GLOBAL_RSVD_STAT1_PROV_ID, val);

	phydev_dbg(phydev, "FW %u.%u, Build %u, Provisioning %u\n",
		   fw_major, fw_minor, build_id, prov_id);
पूर्ण

अटल पूर्णांक aqr107_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	/* Check that the PHY पूर्णांकerface type is compatible */
	अगर (phydev->पूर्णांकerface != PHY_INTERFACE_MODE_SGMII &&
	    phydev->पूर्णांकerface != PHY_INTERFACE_MODE_2500BASEX &&
	    phydev->पूर्णांकerface != PHY_INTERFACE_MODE_XGMII &&
	    phydev->पूर्णांकerface != PHY_INTERFACE_MODE_USXGMII &&
	    phydev->पूर्णांकerface != PHY_INTERFACE_MODE_10GKR &&
	    phydev->पूर्णांकerface != PHY_INTERFACE_MODE_10GBASER)
		वापस -ENODEV;

	WARN(phydev->पूर्णांकerface == PHY_INTERFACE_MODE_XGMII,
	     "Your devicetree is out of date, please update it. The AQR107 family doesn't support XGMII, maybe you mean USXGMII.\n");

	ret = aqr107_रुको_reset_complete(phydev);
	अगर (!ret)
		aqr107_chip_info(phydev);

	वापस aqr107_set_करोwnshअगरt(phydev, MDIO_AN_VEND_PROV_DOWNSHIFT_DFLT);
पूर्ण

अटल पूर्णांक aqcs109_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	/* Check that the PHY पूर्णांकerface type is compatible */
	अगर (phydev->पूर्णांकerface != PHY_INTERFACE_MODE_SGMII &&
	    phydev->पूर्णांकerface != PHY_INTERFACE_MODE_2500BASEX)
		वापस -ENODEV;

	ret = aqr107_रुको_reset_complete(phydev);
	अगर (!ret)
		aqr107_chip_info(phydev);

	/* AQCS109 beदीर्घs to a chip family partially supporting 10G and 5G.
	 * PMA speed ability bits are the same क्रम all members of the family,
	 * AQCS109 however supports speeds up to 2.5G only.
	 */
	ret = phy_set_max_speed(phydev, SPEED_2500);
	अगर (ret)
		वापस ret;

	वापस aqr107_set_करोwnshअगरt(phydev, MDIO_AN_VEND_PROV_DOWNSHIFT_DFLT);
पूर्ण

अटल व्योम aqr107_link_change_notअगरy(काष्ठा phy_device *phydev)
अणु
	u8 fw_major, fw_minor;
	bool करोwnshअगरt, लघु_reach, afr;
	पूर्णांक mode, val;

	अगर (phydev->state != PHY_RUNNING || phydev->स्वतःneg == AUTONEG_DISABLE)
		वापस;

	val = phy_पढ़ो_mmd(phydev, MDIO_MMD_AN, MDIO_AN_RX_LP_STAT1);
	/* call failed or link partner is no Aquantia PHY */
	अगर (val < 0 || !(val & MDIO_AN_RX_LP_STAT1_AQ_PHY))
		वापस;

	लघु_reach = val & MDIO_AN_RX_LP_STAT1_SHORT_REACH;
	करोwnshअगरt = val & MDIO_AN_RX_LP_STAT1_AQRATE_DOWNSHIFT;

	val = phy_पढ़ो_mmd(phydev, MDIO_MMD_AN, MDIO_AN_RX_LP_STAT4);
	अगर (val < 0)
		वापस;

	fw_major = FIELD_GET(MDIO_AN_RX_LP_STAT4_FW_MAJOR, val);
	fw_minor = FIELD_GET(MDIO_AN_RX_LP_STAT4_FW_MINOR, val);

	val = phy_पढ़ो_mmd(phydev, MDIO_MMD_AN, MDIO_AN_RX_VEND_STAT3);
	अगर (val < 0)
		वापस;

	afr = val & MDIO_AN_RX_VEND_STAT3_AFR;

	phydev_dbg(phydev, "Link partner is Aquantia PHY, FW %u.%u%s%s%s\n",
		   fw_major, fw_minor,
		   लघु_reach ? ", short reach mode" : "",
		   करोwnshअगरt ? ", fast-retrain downshift advertised" : "",
		   afr ? ", fast reframe advertised" : "");

	val = phy_पढ़ो_mmd(phydev, MDIO_MMD_VEND1, VEND1_GLOBAL_RSVD_STAT9);
	अगर (val < 0)
		वापस;

	mode = FIELD_GET(VEND1_GLOBAL_RSVD_STAT9_MODE, val);
	अगर (mode == VEND1_GLOBAL_RSVD_STAT9_1000BT2)
		phydev_info(phydev, "Aquantia 1000Base-T2 mode active\n");
पूर्ण

अटल पूर्णांक aqr107_suspend(काष्ठा phy_device *phydev)
अणु
	वापस phy_set_bits_mmd(phydev, MDIO_MMD_VEND1, MDIO_CTRL1,
				MDIO_CTRL1_LPOWER);
पूर्ण

अटल पूर्णांक aqr107_resume(काष्ठा phy_device *phydev)
अणु
	वापस phy_clear_bits_mmd(phydev, MDIO_MMD_VEND1, MDIO_CTRL1,
				  MDIO_CTRL1_LPOWER);
पूर्ण

अटल पूर्णांक aqr107_probe(काष्ठा phy_device *phydev)
अणु
	phydev->priv = devm_kzalloc(&phydev->mdio.dev,
				    माप(काष्ठा aqr107_priv), GFP_KERNEL);
	अगर (!phydev->priv)
		वापस -ENOMEM;

	वापस aqr_hwmon_probe(phydev);
पूर्ण

अटल काष्ठा phy_driver aqr_driver[] = अणु
अणु
	PHY_ID_MATCH_MODEL(PHY_ID_AQ1202),
	.name		= "Aquantia AQ1202",
	.config_aneg    = aqr_config_aneg,
	.config_पूर्णांकr	= aqr_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = aqr_handle_पूर्णांकerrupt,
	.पढ़ो_status	= aqr_पढ़ो_status,
पूर्ण,
अणु
	PHY_ID_MATCH_MODEL(PHY_ID_AQ2104),
	.name		= "Aquantia AQ2104",
	.config_aneg    = aqr_config_aneg,
	.config_पूर्णांकr	= aqr_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = aqr_handle_पूर्णांकerrupt,
	.पढ़ो_status	= aqr_पढ़ो_status,
पूर्ण,
अणु
	PHY_ID_MATCH_MODEL(PHY_ID_AQR105),
	.name		= "Aquantia AQR105",
	.config_aneg    = aqr_config_aneg,
	.config_पूर्णांकr	= aqr_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = aqr_handle_पूर्णांकerrupt,
	.पढ़ो_status	= aqr_पढ़ो_status,
	.suspend	= aqr107_suspend,
	.resume		= aqr107_resume,
पूर्ण,
अणु
	PHY_ID_MATCH_MODEL(PHY_ID_AQR106),
	.name		= "Aquantia AQR106",
	.config_aneg    = aqr_config_aneg,
	.config_पूर्णांकr	= aqr_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = aqr_handle_पूर्णांकerrupt,
	.पढ़ो_status	= aqr_पढ़ो_status,
पूर्ण,
अणु
	PHY_ID_MATCH_MODEL(PHY_ID_AQR107),
	.name		= "Aquantia AQR107",
	.probe		= aqr107_probe,
	.config_init	= aqr107_config_init,
	.config_aneg    = aqr_config_aneg,
	.config_पूर्णांकr	= aqr_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = aqr_handle_पूर्णांकerrupt,
	.पढ़ो_status	= aqr107_पढ़ो_status,
	.get_tunable    = aqr107_get_tunable,
	.set_tunable    = aqr107_set_tunable,
	.suspend	= aqr107_suspend,
	.resume		= aqr107_resume,
	.get_sset_count	= aqr107_get_sset_count,
	.get_strings	= aqr107_get_strings,
	.get_stats	= aqr107_get_stats,
	.link_change_notअगरy = aqr107_link_change_notअगरy,
पूर्ण,
अणु
	PHY_ID_MATCH_MODEL(PHY_ID_AQCS109),
	.name		= "Aquantia AQCS109",
	.probe		= aqr107_probe,
	.config_init	= aqcs109_config_init,
	.config_aneg    = aqr_config_aneg,
	.config_पूर्णांकr	= aqr_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = aqr_handle_पूर्णांकerrupt,
	.पढ़ो_status	= aqr107_पढ़ो_status,
	.get_tunable    = aqr107_get_tunable,
	.set_tunable    = aqr107_set_tunable,
	.suspend	= aqr107_suspend,
	.resume		= aqr107_resume,
	.get_sset_count	= aqr107_get_sset_count,
	.get_strings	= aqr107_get_strings,
	.get_stats	= aqr107_get_stats,
	.link_change_notअगरy = aqr107_link_change_notअगरy,
पूर्ण,
अणु
	PHY_ID_MATCH_MODEL(PHY_ID_AQR405),
	.name		= "Aquantia AQR405",
	.config_aneg    = aqr_config_aneg,
	.config_पूर्णांकr	= aqr_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = aqr_handle_पूर्णांकerrupt,
	.पढ़ो_status	= aqr_पढ़ो_status,
पूर्ण,
पूर्ण;

module_phy_driver(aqr_driver);

अटल काष्ठा mdio_device_id __maybe_unused aqr_tbl[] = अणु
	अणु PHY_ID_MATCH_MODEL(PHY_ID_AQ1202) पूर्ण,
	अणु PHY_ID_MATCH_MODEL(PHY_ID_AQ2104) पूर्ण,
	अणु PHY_ID_MATCH_MODEL(PHY_ID_AQR105) पूर्ण,
	अणु PHY_ID_MATCH_MODEL(PHY_ID_AQR106) पूर्ण,
	अणु PHY_ID_MATCH_MODEL(PHY_ID_AQR107) पूर्ण,
	अणु PHY_ID_MATCH_MODEL(PHY_ID_AQCS109) पूर्ण,
	अणु PHY_ID_MATCH_MODEL(PHY_ID_AQR405) पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(mdio, aqr_tbl);

MODULE_DESCRIPTION("Aquantia PHY driver");
MODULE_AUTHOR("Shaohui Xie <Shaohui.Xie@freescale.com>");
MODULE_LICENSE("GPL v2");
