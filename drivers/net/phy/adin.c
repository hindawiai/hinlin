<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/**
 *  Driver क्रम Analog Devices Industrial Ethernet PHYs
 *
 * Copyright 2019 Analog Devices Inc.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ethtool_netlink.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mii.h>
#समावेश <linux/phy.h>
#समावेश <linux/property.h>

#घोषणा PHY_ID_ADIN1200				0x0283bc20
#घोषणा PHY_ID_ADIN1300				0x0283bc30

#घोषणा ADIN1300_MII_EXT_REG_PTR		0x0010
#घोषणा ADIN1300_MII_EXT_REG_DATA		0x0011

#घोषणा ADIN1300_PHY_CTRL1			0x0012
#घोषणा   ADIN1300_AUTO_MDI_EN			BIT(10)
#घोषणा   ADIN1300_MAN_MDIX_EN			BIT(9)
#घोषणा   ADIN1300_DIAG_CLK_EN			BIT(2)

#घोषणा ADIN1300_RX_ERR_CNT			0x0014

#घोषणा ADIN1300_PHY_CTRL_STATUS2		0x0015
#घोषणा   ADIN1300_NRG_PD_EN			BIT(3)
#घोषणा   ADIN1300_NRG_PD_TX_EN			BIT(2)
#घोषणा   ADIN1300_NRG_PD_STATUS		BIT(1)

#घोषणा ADIN1300_PHY_CTRL2			0x0016
#घोषणा   ADIN1300_DOWNSPEED_AN_100_EN		BIT(11)
#घोषणा   ADIN1300_DOWNSPEED_AN_10_EN		BIT(10)
#घोषणा   ADIN1300_GROUP_MDIO_EN		BIT(6)
#घोषणा   ADIN1300_DOWNSPEEDS_EN	\
	(ADIN1300_DOWNSPEED_AN_100_EN | ADIN1300_DOWNSPEED_AN_10_EN)

#घोषणा ADIN1300_PHY_CTRL3			0x0017
#घोषणा   ADIN1300_LINKING_EN			BIT(13)
#घोषणा   ADIN1300_DOWNSPEED_RETRIES_MSK	GENMASK(12, 10)

#घोषणा ADIN1300_INT_MASK_REG			0x0018
#घोषणा   ADIN1300_INT_MDIO_SYNC_EN		BIT(9)
#घोषणा   ADIN1300_INT_ANEG_STAT_CHNG_EN	BIT(8)
#घोषणा   ADIN1300_INT_ANEG_PAGE_RX_EN		BIT(6)
#घोषणा   ADIN1300_INT_IDLE_ERR_CNT_EN		BIT(5)
#घोषणा   ADIN1300_INT_MAC_FIFO_OU_EN		BIT(4)
#घोषणा   ADIN1300_INT_RX_STAT_CHNG_EN		BIT(3)
#घोषणा   ADIN1300_INT_LINK_STAT_CHNG_EN	BIT(2)
#घोषणा   ADIN1300_INT_SPEED_CHNG_EN		BIT(1)
#घोषणा   ADIN1300_INT_HW_IRQ_EN		BIT(0)
#घोषणा ADIN1300_INT_MASK_EN	\
	(ADIN1300_INT_LINK_STAT_CHNG_EN | ADIN1300_INT_HW_IRQ_EN)
#घोषणा ADIN1300_INT_STATUS_REG			0x0019

#घोषणा ADIN1300_PHY_STATUS1			0x001a
#घोषणा   ADIN1300_PAIR_01_SWAP			BIT(11)

/* EEE रेजिस्टर addresses, accessible via Clause 22 access using
 * ADIN1300_MII_EXT_REG_PTR & ADIN1300_MII_EXT_REG_DATA.
 * The bit-fields are the same as specअगरied by IEEE क्रम EEE.
 */
#घोषणा ADIN1300_EEE_CAP_REG			0x8000
#घोषणा ADIN1300_EEE_ADV_REG			0x8001
#घोषणा ADIN1300_EEE_LPABLE_REG			0x8002
#घोषणा ADIN1300_CLOCK_STOP_REG			0x9400
#घोषणा ADIN1300_LPI_WAKE_ERR_CNT_REG		0xa000

#घोषणा ADIN1300_CDIAG_RUN			0xba1b
#घोषणा   ADIN1300_CDIAG_RUN_EN			BIT(0)

/*
 * The XSIM3/2/1 and XSHRT3/2/1 are actually relative.
 * For CDIAG_DTLD_RSLTS(0) it's ADIN1300_CDIAG_RSLT_XSIM3/2/1
 * For CDIAG_DTLD_RSLTS(1) it's ADIN1300_CDIAG_RSLT_XSIM3/2/0
 * For CDIAG_DTLD_RSLTS(2) it's ADIN1300_CDIAG_RSLT_XSIM3/1/0
 * For CDIAG_DTLD_RSLTS(3) it's ADIN1300_CDIAG_RSLT_XSIM2/1/0
 */
#घोषणा ADIN1300_CDIAG_DTLD_RSLTS(x)		(0xba1d + (x))
#घोषणा   ADIN1300_CDIAG_RSLT_BUSY		BIT(10)
#घोषणा   ADIN1300_CDIAG_RSLT_XSIM3		BIT(9)
#घोषणा   ADIN1300_CDIAG_RSLT_XSIM2		BIT(8)
#घोषणा   ADIN1300_CDIAG_RSLT_XSIM1		BIT(7)
#घोषणा   ADIN1300_CDIAG_RSLT_SIM		BIT(6)
#घोषणा   ADIN1300_CDIAG_RSLT_XSHRT3		BIT(5)
#घोषणा   ADIN1300_CDIAG_RSLT_XSHRT2		BIT(4)
#घोषणा   ADIN1300_CDIAG_RSLT_XSHRT1		BIT(3)
#घोषणा   ADIN1300_CDIAG_RSLT_SHRT		BIT(2)
#घोषणा   ADIN1300_CDIAG_RSLT_OPEN		BIT(1)
#घोषणा   ADIN1300_CDIAG_RSLT_GOOD		BIT(0)

#घोषणा ADIN1300_CDIAG_FLT_DIST(x)		(0xba21 + (x))

#घोषणा ADIN1300_GE_SOFT_RESET_REG		0xff0c
#घोषणा   ADIN1300_GE_SOFT_RESET		BIT(0)

#घोषणा ADIN1300_GE_RGMII_CFG_REG		0xff23
#घोषणा   ADIN1300_GE_RGMII_RX_MSK		GENMASK(8, 6)
#घोषणा   ADIN1300_GE_RGMII_RX_SEL(x)		\
		FIELD_PREP(ADIN1300_GE_RGMII_RX_MSK, x)
#घोषणा   ADIN1300_GE_RGMII_GTX_MSK		GENMASK(5, 3)
#घोषणा   ADIN1300_GE_RGMII_GTX_SEL(x)		\
		FIELD_PREP(ADIN1300_GE_RGMII_GTX_MSK, x)
#घोषणा   ADIN1300_GE_RGMII_RXID_EN		BIT(2)
#घोषणा   ADIN1300_GE_RGMII_TXID_EN		BIT(1)
#घोषणा   ADIN1300_GE_RGMII_EN			BIT(0)

/* RGMII पूर्णांकernal delay settings क्रम rx and tx क्रम ADIN1300 */
#घोषणा ADIN1300_RGMII_1_60_NS			0x0001
#घोषणा ADIN1300_RGMII_1_80_NS			0x0002
#घोषणा	ADIN1300_RGMII_2_00_NS			0x0000
#घोषणा	ADIN1300_RGMII_2_20_NS			0x0006
#घोषणा	ADIN1300_RGMII_2_40_NS			0x0007

#घोषणा ADIN1300_GE_RMII_CFG_REG		0xff24
#घोषणा   ADIN1300_GE_RMII_FIFO_DEPTH_MSK	GENMASK(6, 4)
#घोषणा   ADIN1300_GE_RMII_FIFO_DEPTH_SEL(x)	\
		FIELD_PREP(ADIN1300_GE_RMII_FIFO_DEPTH_MSK, x)
#घोषणा   ADIN1300_GE_RMII_EN			BIT(0)

/* RMII fअगरo depth values */
#घोषणा ADIN1300_RMII_4_BITS			0x0000
#घोषणा ADIN1300_RMII_8_BITS			0x0001
#घोषणा ADIN1300_RMII_12_BITS			0x0002
#घोषणा ADIN1300_RMII_16_BITS			0x0003
#घोषणा ADIN1300_RMII_20_BITS			0x0004
#घोषणा ADIN1300_RMII_24_BITS			0x0005

/**
 * काष्ठा adin_cfg_reg_map - map a config value to aरेजिस्टर value
 * @cfg:	value in device configuration
 * @reg:	value in the रेजिस्टर
 */
काष्ठा adin_cfg_reg_map अणु
	पूर्णांक cfg;
	पूर्णांक reg;
पूर्ण;

अटल स्थिर काष्ठा adin_cfg_reg_map adin_rgmii_delays[] = अणु
	अणु 1600, ADIN1300_RGMII_1_60_NS पूर्ण,
	अणु 1800, ADIN1300_RGMII_1_80_NS पूर्ण,
	अणु 2000, ADIN1300_RGMII_2_00_NS पूर्ण,
	अणु 2200, ADIN1300_RGMII_2_20_NS पूर्ण,
	अणु 2400, ADIN1300_RGMII_2_40_NS पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा adin_cfg_reg_map adin_rmii_fअगरo_depths[] = अणु
	अणु 4,  ADIN1300_RMII_4_BITS पूर्ण,
	अणु 8,  ADIN1300_RMII_8_BITS पूर्ण,
	अणु 12, ADIN1300_RMII_12_BITS पूर्ण,
	अणु 16, ADIN1300_RMII_16_BITS पूर्ण,
	अणु 20, ADIN1300_RMII_20_BITS पूर्ण,
	अणु 24, ADIN1300_RMII_24_BITS पूर्ण,
	अणु पूर्ण,
पूर्ण;

/**
 * काष्ठा adin_clause45_mmd_map - map to convert Clause 45 regs to Clause 22
 * @devad:		device address used in Clause 45 access
 * @cl45_regnum:	रेजिस्टर address defined by Clause 45
 * @adin_regnum:	equivalent रेजिस्टर address accessible via Clause 22
 */
काष्ठा adin_clause45_mmd_map अणु
	पूर्णांक devad;
	u16 cl45_regnum;
	u16 adin_regnum;
पूर्ण;

अटल स्थिर काष्ठा adin_clause45_mmd_map adin_clause45_mmd_map[] = अणु
	अणु MDIO_MMD_PCS,	MDIO_PCS_EEE_ABLE,	ADIN1300_EEE_CAP_REG पूर्ण,
	अणु MDIO_MMD_AN,	MDIO_AN_EEE_LPABLE,	ADIN1300_EEE_LPABLE_REG पूर्ण,
	अणु MDIO_MMD_AN,	MDIO_AN_EEE_ADV,	ADIN1300_EEE_ADV_REG पूर्ण,
	अणु MDIO_MMD_PCS,	MDIO_CTRL1,		ADIN1300_CLOCK_STOP_REG पूर्ण,
	अणु MDIO_MMD_PCS, MDIO_PCS_EEE_WK_ERR,	ADIN1300_LPI_WAKE_ERR_CNT_REG पूर्ण,
पूर्ण;

काष्ठा adin_hw_stat अणु
	स्थिर अक्षर *string;
	u16 reg1;
	u16 reg2;
पूर्ण;

अटल स्थिर काष्ठा adin_hw_stat adin_hw_stats[] = अणु
	अणु "total_frames_checked_count",		0x940A, 0x940B पूर्ण, /* hi + lo */
	अणु "length_error_frames_count",		0x940C पूर्ण,
	अणु "alignment_error_frames_count",	0x940D पूर्ण,
	अणु "symbol_error_count",			0x940E पूर्ण,
	अणु "oversized_frames_count",		0x940F पूर्ण,
	अणु "undersized_frames_count",		0x9410 पूर्ण,
	अणु "odd_nibble_frames_count",		0x9411 पूर्ण,
	अणु "odd_preamble_packet_count",		0x9412 पूर्ण,
	अणु "dribble_bits_frames_count",		0x9413 पूर्ण,
	अणु "false_carrier_events_count",		0x9414 पूर्ण,
पूर्ण;

/**
 * काष्ठा adin_priv - ADIN PHY driver निजी data
 * @stats:		statistic counters क्रम the PHY
 */
काष्ठा adin_priv अणु
	u64			stats[ARRAY_SIZE(adin_hw_stats)];
पूर्ण;

अटल पूर्णांक adin_lookup_reg_value(स्थिर काष्ठा adin_cfg_reg_map *tbl, पूर्णांक cfg)
अणु
	माप_प्रकार i;

	क्रम (i = 0; tbl[i].cfg; i++) अणु
		अगर (tbl[i].cfg == cfg)
			वापस tbl[i].reg;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल u32 adin_get_reg_value(काष्ठा phy_device *phydev,
			      स्थिर अक्षर *prop_name,
			      स्थिर काष्ठा adin_cfg_reg_map *tbl,
			      u32 dflt)
अणु
	काष्ठा device *dev = &phydev->mdio.dev;
	u32 val;
	पूर्णांक rc;

	अगर (device_property_पढ़ो_u32(dev, prop_name, &val))
		वापस dflt;

	rc = adin_lookup_reg_value(tbl, val);
	अगर (rc < 0) अणु
		phydev_warn(phydev,
			    "Unsupported value %u for %s using default (%u)\n",
			    val, prop_name, dflt);
		वापस dflt;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक adin_config_rgmii_mode(काष्ठा phy_device *phydev)
अणु
	u32 val;
	पूर्णांक reg;

	अगर (!phy_पूर्णांकerface_is_rgmii(phydev))
		वापस phy_clear_bits_mmd(phydev, MDIO_MMD_VEND1,
					  ADIN1300_GE_RGMII_CFG_REG,
					  ADIN1300_GE_RGMII_EN);

	reg = phy_पढ़ो_mmd(phydev, MDIO_MMD_VEND1, ADIN1300_GE_RGMII_CFG_REG);
	अगर (reg < 0)
		वापस reg;

	reg |= ADIN1300_GE_RGMII_EN;

	अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_ID ||
	    phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_RXID) अणु
		reg |= ADIN1300_GE_RGMII_RXID_EN;

		val = adin_get_reg_value(phydev, "adi,rx-internal-delay-ps",
					 adin_rgmii_delays,
					 ADIN1300_RGMII_2_00_NS);
		reg &= ~ADIN1300_GE_RGMII_RX_MSK;
		reg |= ADIN1300_GE_RGMII_RX_SEL(val);
	पूर्ण अन्यथा अणु
		reg &= ~ADIN1300_GE_RGMII_RXID_EN;
	पूर्ण

	अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_ID ||
	    phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_TXID) अणु
		reg |= ADIN1300_GE_RGMII_TXID_EN;

		val = adin_get_reg_value(phydev, "adi,tx-internal-delay-ps",
					 adin_rgmii_delays,
					 ADIN1300_RGMII_2_00_NS);
		reg &= ~ADIN1300_GE_RGMII_GTX_MSK;
		reg |= ADIN1300_GE_RGMII_GTX_SEL(val);
	पूर्ण अन्यथा अणु
		reg &= ~ADIN1300_GE_RGMII_TXID_EN;
	पूर्ण

	वापस phy_ग_लिखो_mmd(phydev, MDIO_MMD_VEND1,
			     ADIN1300_GE_RGMII_CFG_REG, reg);
पूर्ण

अटल पूर्णांक adin_config_rmii_mode(काष्ठा phy_device *phydev)
अणु
	u32 val;
	पूर्णांक reg;

	अगर (phydev->पूर्णांकerface != PHY_INTERFACE_MODE_RMII)
		वापस phy_clear_bits_mmd(phydev, MDIO_MMD_VEND1,
					  ADIN1300_GE_RMII_CFG_REG,
					  ADIN1300_GE_RMII_EN);

	reg = phy_पढ़ो_mmd(phydev, MDIO_MMD_VEND1, ADIN1300_GE_RMII_CFG_REG);
	अगर (reg < 0)
		वापस reg;

	reg |= ADIN1300_GE_RMII_EN;

	val = adin_get_reg_value(phydev, "adi,fifo-depth-bits",
				 adin_rmii_fअगरo_depths,
				 ADIN1300_RMII_8_BITS);

	reg &= ~ADIN1300_GE_RMII_FIFO_DEPTH_MSK;
	reg |= ADIN1300_GE_RMII_FIFO_DEPTH_SEL(val);

	वापस phy_ग_लिखो_mmd(phydev, MDIO_MMD_VEND1,
			     ADIN1300_GE_RMII_CFG_REG, reg);
पूर्ण

अटल पूर्णांक adin_get_करोwnshअगरt(काष्ठा phy_device *phydev, u8 *data)
अणु
	पूर्णांक val, cnt, enable;

	val = phy_पढ़ो(phydev, ADIN1300_PHY_CTRL2);
	अगर (val < 0)
		वापस val;

	cnt = phy_पढ़ो(phydev, ADIN1300_PHY_CTRL3);
	अगर (cnt < 0)
		वापस cnt;

	enable = FIELD_GET(ADIN1300_DOWNSPEEDS_EN, val);
	cnt = FIELD_GET(ADIN1300_DOWNSPEED_RETRIES_MSK, cnt);

	*data = (enable && cnt) ? cnt : DOWNSHIFT_DEV_DISABLE;

	वापस 0;
पूर्ण

अटल पूर्णांक adin_set_करोwnshअगरt(काष्ठा phy_device *phydev, u8 cnt)
अणु
	u16 val;
	पूर्णांक rc;

	अगर (cnt == DOWNSHIFT_DEV_DISABLE)
		वापस phy_clear_bits(phydev, ADIN1300_PHY_CTRL2,
				      ADIN1300_DOWNSPEEDS_EN);

	अगर (cnt > 7)
		वापस -E2BIG;

	val = FIELD_PREP(ADIN1300_DOWNSPEED_RETRIES_MSK, cnt);

	rc = phy_modअगरy(phydev, ADIN1300_PHY_CTRL3,
			ADIN1300_DOWNSPEED_RETRIES_MSK,
			val);
	अगर (rc < 0)
		वापस rc;

	वापस phy_set_bits(phydev, ADIN1300_PHY_CTRL2,
			    ADIN1300_DOWNSPEEDS_EN);
पूर्ण

अटल पूर्णांक adin_get_edpd(काष्ठा phy_device *phydev, u16 *tx_पूर्णांकerval)
अणु
	पूर्णांक val;

	val = phy_पढ़ो(phydev, ADIN1300_PHY_CTRL_STATUS2);
	अगर (val < 0)
		वापस val;

	अगर (ADIN1300_NRG_PD_EN & val) अणु
		अगर (val & ADIN1300_NRG_PD_TX_EN)
			/* शेष is 1 second */
			*tx_पूर्णांकerval = ETHTOOL_PHY_EDPD_DFLT_TX_MSECS;
		अन्यथा
			*tx_पूर्णांकerval = ETHTOOL_PHY_EDPD_NO_TX;
	पूर्ण अन्यथा अणु
		*tx_पूर्णांकerval = ETHTOOL_PHY_EDPD_DISABLE;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adin_set_edpd(काष्ठा phy_device *phydev, u16 tx_पूर्णांकerval)
अणु
	u16 val;

	अगर (tx_पूर्णांकerval == ETHTOOL_PHY_EDPD_DISABLE)
		वापस phy_clear_bits(phydev, ADIN1300_PHY_CTRL_STATUS2,
				(ADIN1300_NRG_PD_EN | ADIN1300_NRG_PD_TX_EN));

	val = ADIN1300_NRG_PD_EN;

	चयन (tx_पूर्णांकerval) अणु
	हाल 1000: /* 1 second */
		fallthrough;
	हाल ETHTOOL_PHY_EDPD_DFLT_TX_MSECS:
		val |= ADIN1300_NRG_PD_TX_EN;
		fallthrough;
	हाल ETHTOOL_PHY_EDPD_NO_TX:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस phy_modअगरy(phydev, ADIN1300_PHY_CTRL_STATUS2,
			  (ADIN1300_NRG_PD_EN | ADIN1300_NRG_PD_TX_EN),
			  val);
पूर्ण

अटल पूर्णांक adin_get_tunable(काष्ठा phy_device *phydev,
			    काष्ठा ethtool_tunable *tuna, व्योम *data)
अणु
	चयन (tuna->id) अणु
	हाल ETHTOOL_PHY_DOWNSHIFT:
		वापस adin_get_करोwnshअगरt(phydev, data);
	हाल ETHTOOL_PHY_EDPD:
		वापस adin_get_edpd(phydev, data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक adin_set_tunable(काष्ठा phy_device *phydev,
			    काष्ठा ethtool_tunable *tuna, स्थिर व्योम *data)
अणु
	चयन (tuna->id) अणु
	हाल ETHTOOL_PHY_DOWNSHIFT:
		वापस adin_set_करोwnshअगरt(phydev, *(स्थिर u8 *)data);
	हाल ETHTOOL_PHY_EDPD:
		वापस adin_set_edpd(phydev, *(स्थिर u16 *)data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक adin_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक rc;

	phydev->mdix_ctrl = ETH_TP_MDI_AUTO;

	rc = adin_config_rgmii_mode(phydev);
	अगर (rc < 0)
		वापस rc;

	rc = adin_config_rmii_mode(phydev);
	अगर (rc < 0)
		वापस rc;

	rc = adin_set_करोwnshअगरt(phydev, 4);
	अगर (rc < 0)
		वापस rc;

	rc = adin_set_edpd(phydev, ETHTOOL_PHY_EDPD_DFLT_TX_MSECS);
	अगर (rc < 0)
		वापस rc;

	phydev_dbg(phydev, "PHY is using mode '%s'\n",
		   phy_modes(phydev->पूर्णांकerface));

	वापस 0;
पूर्ण

अटल पूर्णांक adin_phy_ack_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	/* Clear pending पूर्णांकerrupts */
	पूर्णांक rc = phy_पढ़ो(phydev, ADIN1300_INT_STATUS_REG);

	वापस rc < 0 ? rc : 0;
पूर्ण

अटल पूर्णांक adin_phy_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED) अणु
		err = adin_phy_ack_पूर्णांकr(phydev);
		अगर (err)
			वापस err;

		err = phy_set_bits(phydev, ADIN1300_INT_MASK_REG,
				   ADIN1300_INT_MASK_EN);
	पूर्ण अन्यथा अणु
		err = phy_clear_bits(phydev, ADIN1300_INT_MASK_REG,
				     ADIN1300_INT_MASK_EN);
		अगर (err)
			वापस err;

		err = adin_phy_ack_पूर्णांकr(phydev);
	पूर्ण

	वापस err;
पूर्ण

अटल irqवापस_t adin_phy_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक irq_status;

	irq_status = phy_पढ़ो(phydev, ADIN1300_INT_STATUS_REG);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	अगर (!(irq_status & ADIN1300_INT_LINK_STAT_CHNG_EN))
		वापस IRQ_NONE;

	phy_trigger_machine(phydev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक adin_cl45_to_adin_reg(काष्ठा phy_device *phydev, पूर्णांक devad,
				 u16 cl45_regnum)
अणु
	स्थिर काष्ठा adin_clause45_mmd_map *m;
	पूर्णांक i;

	अगर (devad == MDIO_MMD_VEND1)
		वापस cl45_regnum;

	क्रम (i = 0; i < ARRAY_SIZE(adin_clause45_mmd_map); i++) अणु
		m = &adin_clause45_mmd_map[i];
		अगर (m->devad == devad && m->cl45_regnum == cl45_regnum)
			वापस m->adin_regnum;
	पूर्ण

	phydev_err(phydev,
		   "No translation available for devad: %d reg: %04x\n",
		   devad, cl45_regnum);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक adin_पढ़ो_mmd(काष्ठा phy_device *phydev, पूर्णांक devad, u16 regnum)
अणु
	काष्ठा mii_bus *bus = phydev->mdio.bus;
	पूर्णांक phy_addr = phydev->mdio.addr;
	पूर्णांक adin_regnum;
	पूर्णांक err;

	adin_regnum = adin_cl45_to_adin_reg(phydev, devad, regnum);
	अगर (adin_regnum < 0)
		वापस adin_regnum;

	err = __mdiobus_ग_लिखो(bus, phy_addr, ADIN1300_MII_EXT_REG_PTR,
			      adin_regnum);
	अगर (err)
		वापस err;

	वापस __mdiobus_पढ़ो(bus, phy_addr, ADIN1300_MII_EXT_REG_DATA);
पूर्ण

अटल पूर्णांक adin_ग_लिखो_mmd(काष्ठा phy_device *phydev, पूर्णांक devad, u16 regnum,
			  u16 val)
अणु
	काष्ठा mii_bus *bus = phydev->mdio.bus;
	पूर्णांक phy_addr = phydev->mdio.addr;
	पूर्णांक adin_regnum;
	पूर्णांक err;

	adin_regnum = adin_cl45_to_adin_reg(phydev, devad, regnum);
	अगर (adin_regnum < 0)
		वापस adin_regnum;

	err = __mdiobus_ग_लिखो(bus, phy_addr, ADIN1300_MII_EXT_REG_PTR,
			      adin_regnum);
	अगर (err)
		वापस err;

	वापस __mdiobus_ग_लिखो(bus, phy_addr, ADIN1300_MII_EXT_REG_DATA, val);
पूर्ण

अटल पूर्णांक adin_config_mdix(काष्ठा phy_device *phydev)
अणु
	bool स्वतः_en, mdix_en;
	पूर्णांक reg;

	mdix_en = false;
	स्वतः_en = false;
	चयन (phydev->mdix_ctrl) अणु
	हाल ETH_TP_MDI:
		अवरोध;
	हाल ETH_TP_MDI_X:
		mdix_en = true;
		अवरोध;
	हाल ETH_TP_MDI_AUTO:
		स्वतः_en = true;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	reg = phy_पढ़ो(phydev, ADIN1300_PHY_CTRL1);
	अगर (reg < 0)
		वापस reg;

	अगर (mdix_en)
		reg |= ADIN1300_MAN_MDIX_EN;
	अन्यथा
		reg &= ~ADIN1300_MAN_MDIX_EN;

	अगर (स्वतः_en)
		reg |= ADIN1300_AUTO_MDI_EN;
	अन्यथा
		reg &= ~ADIN1300_AUTO_MDI_EN;

	वापस phy_ग_लिखो(phydev, ADIN1300_PHY_CTRL1, reg);
पूर्ण

अटल पूर्णांक adin_config_aneg(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	ret = phy_clear_bits(phydev, ADIN1300_PHY_CTRL1, ADIN1300_DIAG_CLK_EN);
	अगर (ret < 0)
		वापस ret;

	ret = phy_set_bits(phydev, ADIN1300_PHY_CTRL3, ADIN1300_LINKING_EN);
	अगर (ret < 0)
		वापस ret;

	ret = adin_config_mdix(phydev);
	अगर (ret)
		वापस ret;

	वापस genphy_config_aneg(phydev);
पूर्ण

अटल पूर्णांक adin_mdix_update(काष्ठा phy_device *phydev)
अणु
	bool स्वतः_en, mdix_en;
	bool swapped;
	पूर्णांक reg;

	reg = phy_पढ़ो(phydev, ADIN1300_PHY_CTRL1);
	अगर (reg < 0)
		वापस reg;

	स्वतः_en = !!(reg & ADIN1300_AUTO_MDI_EN);
	mdix_en = !!(reg & ADIN1300_MAN_MDIX_EN);

	/* If MDI/MDIX is क्रमced, just पढ़ो it from the control reg */
	अगर (!स्वतः_en) अणु
		अगर (mdix_en)
			phydev->mdix = ETH_TP_MDI_X;
		अन्यथा
			phydev->mdix = ETH_TP_MDI;
		वापस 0;
	पूर्ण

	/**
	 * Otherwise, we need to deduce it from the PHY status2 reg.
	 * When Auto-MDI is enabled, the ADIN1300_MAN_MDIX_EN bit implies
	 * a preference क्रम MDIX when it is set.
	 */
	reg = phy_पढ़ो(phydev, ADIN1300_PHY_STATUS1);
	अगर (reg < 0)
		वापस reg;

	swapped = !!(reg & ADIN1300_PAIR_01_SWAP);

	अगर (mdix_en != swapped)
		phydev->mdix = ETH_TP_MDI_X;
	अन्यथा
		phydev->mdix = ETH_TP_MDI;

	वापस 0;
पूर्ण

अटल पूर्णांक adin_पढ़ो_status(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	ret = adin_mdix_update(phydev);
	अगर (ret < 0)
		वापस ret;

	वापस genphy_पढ़ो_status(phydev);
पूर्ण

अटल पूर्णांक adin_soft_reset(काष्ठा phy_device *phydev)
अणु
	पूर्णांक rc;

	/* The reset bit is self-clearing, set it and रुको */
	rc = phy_set_bits_mmd(phydev, MDIO_MMD_VEND1,
			      ADIN1300_GE_SOFT_RESET_REG,
			      ADIN1300_GE_SOFT_RESET);
	अगर (rc < 0)
		वापस rc;

	msleep(20);

	/* If we get a पढ़ो error something may be wrong */
	rc = phy_पढ़ो_mmd(phydev, MDIO_MMD_VEND1,
			  ADIN1300_GE_SOFT_RESET_REG);

	वापस rc < 0 ? rc : 0;
पूर्ण

अटल पूर्णांक adin_get_sset_count(काष्ठा phy_device *phydev)
अणु
	वापस ARRAY_SIZE(adin_hw_stats);
पूर्ण

अटल व्योम adin_get_strings(काष्ठा phy_device *phydev, u8 *data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(adin_hw_stats); i++) अणु
		strlcpy(&data[i * ETH_GSTRING_LEN],
			adin_hw_stats[i].string, ETH_GSTRING_LEN);
	पूर्ण
पूर्ण

अटल पूर्णांक adin_पढ़ो_mmd_stat_regs(काष्ठा phy_device *phydev,
				   स्थिर काष्ठा adin_hw_stat *stat,
				   u32 *val)
अणु
	पूर्णांक ret;

	ret = phy_पढ़ो_mmd(phydev, MDIO_MMD_VEND1, stat->reg1);
	अगर (ret < 0)
		वापस ret;

	*val = (ret & 0xffff);

	अगर (stat->reg2 == 0)
		वापस 0;

	ret = phy_पढ़ो_mmd(phydev, MDIO_MMD_VEND1, stat->reg2);
	अगर (ret < 0)
		वापस ret;

	*val <<= 16;
	*val |= (ret & 0xffff);

	वापस 0;
पूर्ण

अटल u64 adin_get_stat(काष्ठा phy_device *phydev, पूर्णांक i)
अणु
	स्थिर काष्ठा adin_hw_stat *stat = &adin_hw_stats[i];
	काष्ठा adin_priv *priv = phydev->priv;
	u32 val;
	पूर्णांक ret;

	अगर (stat->reg1 > 0x1f) अणु
		ret = adin_पढ़ो_mmd_stat_regs(phydev, stat, &val);
		अगर (ret < 0)
			वापस (u64)(~0);
	पूर्ण अन्यथा अणु
		ret = phy_पढ़ो(phydev, stat->reg1);
		अगर (ret < 0)
			वापस (u64)(~0);
		val = (ret & 0xffff);
	पूर्ण

	priv->stats[i] += val;

	वापस priv->stats[i];
पूर्ण

अटल व्योम adin_get_stats(काष्ठा phy_device *phydev,
			   काष्ठा ethtool_stats *stats, u64 *data)
अणु
	पूर्णांक i, rc;

	/* latch copies of all the frame-checker counters */
	rc = phy_पढ़ो(phydev, ADIN1300_RX_ERR_CNT);
	अगर (rc < 0)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(adin_hw_stats); i++)
		data[i] = adin_get_stat(phydev, i);
पूर्ण

अटल पूर्णांक adin_probe(काष्ठा phy_device *phydev)
अणु
	काष्ठा device *dev = &phydev->mdio.dev;
	काष्ठा adin_priv *priv;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	phydev->priv = priv;

	वापस 0;
पूर्ण

अटल पूर्णांक adin_cable_test_start(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	ret = phy_clear_bits(phydev, ADIN1300_PHY_CTRL3, ADIN1300_LINKING_EN);
	अगर (ret < 0)
		वापस ret;

	ret = phy_clear_bits(phydev, ADIN1300_PHY_CTRL1, ADIN1300_DIAG_CLK_EN);
	अगर (ret < 0)
		वापस ret;

	/* रुको a bit क्रम the घड़ी to stabilize */
	msleep(50);

	वापस phy_set_bits_mmd(phydev, MDIO_MMD_VEND1, ADIN1300_CDIAG_RUN,
				ADIN1300_CDIAG_RUN_EN);
पूर्ण

अटल पूर्णांक adin_cable_test_report_trans(पूर्णांक result)
अणु
	पूर्णांक mask;

	अगर (result & ADIN1300_CDIAG_RSLT_GOOD)
		वापस ETHTOOL_A_CABLE_RESULT_CODE_OK;
	अगर (result & ADIN1300_CDIAG_RSLT_OPEN)
		वापस ETHTOOL_A_CABLE_RESULT_CODE_OPEN;

	/* लघु with other pairs */
	mask = ADIN1300_CDIAG_RSLT_XSHRT3 |
	       ADIN1300_CDIAG_RSLT_XSHRT2 |
	       ADIN1300_CDIAG_RSLT_XSHRT1;
	अगर (result & mask)
		वापस ETHTOOL_A_CABLE_RESULT_CODE_CROSS_SHORT;

	अगर (result & ADIN1300_CDIAG_RSLT_SHRT)
		वापस ETHTOOL_A_CABLE_RESULT_CODE_SAME_SHORT;

	वापस ETHTOOL_A_CABLE_RESULT_CODE_UNSPEC;
पूर्ण

अटल पूर्णांक adin_cable_test_report_pair(काष्ठा phy_device *phydev,
				       अचिन्हित पूर्णांक pair)
अणु
	पूर्णांक fault_rslt;
	पूर्णांक ret;

	ret = phy_पढ़ो_mmd(phydev, MDIO_MMD_VEND1,
			   ADIN1300_CDIAG_DTLD_RSLTS(pair));
	अगर (ret < 0)
		वापस ret;

	fault_rslt = adin_cable_test_report_trans(ret);

	ret = ethnl_cable_test_result(phydev, pair, fault_rslt);
	अगर (ret < 0)
		वापस ret;

	ret = phy_पढ़ो_mmd(phydev, MDIO_MMD_VEND1,
			   ADIN1300_CDIAG_FLT_DIST(pair));
	अगर (ret < 0)
		वापस ret;

	चयन (fault_rslt) अणु
	हाल ETHTOOL_A_CABLE_RESULT_CODE_OPEN:
	हाल ETHTOOL_A_CABLE_RESULT_CODE_SAME_SHORT:
	हाल ETHTOOL_A_CABLE_RESULT_CODE_CROSS_SHORT:
		वापस ethnl_cable_test_fault_length(phydev, pair, ret * 100);
	शेष:
		वापस  0;
	पूर्ण
पूर्ण

अटल पूर्णांक adin_cable_test_report(काष्ठा phy_device *phydev)
अणु
	अचिन्हित पूर्णांक pair;
	पूर्णांक ret;

	क्रम (pair = ETHTOOL_A_CABLE_PAIR_A; pair <= ETHTOOL_A_CABLE_PAIR_D; pair++) अणु
		ret = adin_cable_test_report_pair(phydev, pair);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adin_cable_test_get_status(काष्ठा phy_device *phydev,
				      bool *finished)
अणु
	पूर्णांक ret;

	*finished = false;

	ret = phy_पढ़ो_mmd(phydev, MDIO_MMD_VEND1, ADIN1300_CDIAG_RUN);
	अगर (ret < 0)
		वापस ret;

	अगर (ret & ADIN1300_CDIAG_RUN_EN)
		वापस 0;

	*finished = true;

	वापस adin_cable_test_report(phydev);
पूर्ण

अटल काष्ठा phy_driver adin_driver[] = अणु
	अणु
		PHY_ID_MATCH_MODEL(PHY_ID_ADIN1200),
		.name		= "ADIN1200",
		.flags		= PHY_POLL_CABLE_TEST,
		.probe		= adin_probe,
		.config_init	= adin_config_init,
		.soft_reset	= adin_soft_reset,
		.config_aneg	= adin_config_aneg,
		.पढ़ो_status	= adin_पढ़ो_status,
		.get_tunable	= adin_get_tunable,
		.set_tunable	= adin_set_tunable,
		.config_पूर्णांकr	= adin_phy_config_पूर्णांकr,
		.handle_पूर्णांकerrupt = adin_phy_handle_पूर्णांकerrupt,
		.get_sset_count	= adin_get_sset_count,
		.get_strings	= adin_get_strings,
		.get_stats	= adin_get_stats,
		.resume		= genphy_resume,
		.suspend	= genphy_suspend,
		.पढ़ो_mmd	= adin_पढ़ो_mmd,
		.ग_लिखो_mmd	= adin_ग_लिखो_mmd,
		.cable_test_start	= adin_cable_test_start,
		.cable_test_get_status	= adin_cable_test_get_status,
	पूर्ण,
	अणु
		PHY_ID_MATCH_MODEL(PHY_ID_ADIN1300),
		.name		= "ADIN1300",
		.flags		= PHY_POLL_CABLE_TEST,
		.probe		= adin_probe,
		.config_init	= adin_config_init,
		.soft_reset	= adin_soft_reset,
		.config_aneg	= adin_config_aneg,
		.पढ़ो_status	= adin_पढ़ो_status,
		.get_tunable	= adin_get_tunable,
		.set_tunable	= adin_set_tunable,
		.config_पूर्णांकr	= adin_phy_config_पूर्णांकr,
		.handle_पूर्णांकerrupt = adin_phy_handle_पूर्णांकerrupt,
		.get_sset_count	= adin_get_sset_count,
		.get_strings	= adin_get_strings,
		.get_stats	= adin_get_stats,
		.resume		= genphy_resume,
		.suspend	= genphy_suspend,
		.पढ़ो_mmd	= adin_पढ़ो_mmd,
		.ग_लिखो_mmd	= adin_ग_लिखो_mmd,
		.cable_test_start	= adin_cable_test_start,
		.cable_test_get_status	= adin_cable_test_get_status,
	पूर्ण,
पूर्ण;

module_phy_driver(adin_driver);

अटल काष्ठा mdio_device_id __maybe_unused adin_tbl[] = अणु
	अणु PHY_ID_MATCH_MODEL(PHY_ID_ADIN1200) पूर्ण,
	अणु PHY_ID_MATCH_MODEL(PHY_ID_ADIN1300) पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(mdio, adin_tbl);
MODULE_DESCRIPTION("Analog Devices Industrial Ethernet PHY driver");
MODULE_LICENSE("GPL");
