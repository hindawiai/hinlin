<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Driver क्रम the Texas Instruments DP83869 PHY
 * Copyright (C) 2019 Texas Instruments Inc.
 */

#समावेश <linux/ethtool.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mii.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/phy.h>
#समावेश <linux/delay.h>
#समावेश <linux/bitfield.h>

#समावेश <dt-bindings/net/ti-dp83869.h>

#घोषणा DP83869_PHY_ID		0x2000a0f1
#घोषणा DP83869_DEVADDR		0x1f

#घोषणा MII_DP83869_PHYCTRL	0x10
#घोषणा MII_DP83869_MICR	0x12
#घोषणा MII_DP83869_ISR		0x13
#घोषणा DP83869_CFG2		0x14
#घोषणा DP83869_CTRL		0x1f
#घोषणा DP83869_CFG4		0x1e

/* Extended Registers */
#घोषणा DP83869_GEN_CFG3        0x0031
#घोषणा DP83869_RGMIICTL	0x0032
#घोषणा DP83869_STRAP_STS1	0x006e
#घोषणा DP83869_RGMIIDCTL	0x0086
#घोषणा DP83869_RXFCFG		0x0134
#घोषणा DP83869_RXFPMD1		0x0136
#घोषणा DP83869_RXFPMD2		0x0137
#घोषणा DP83869_RXFPMD3		0x0138
#घोषणा DP83869_RXFSOP1		0x0139
#घोषणा DP83869_RXFSOP2		0x013A
#घोषणा DP83869_RXFSOP3		0x013B
#घोषणा DP83869_IO_MUX_CFG	0x0170
#घोषणा DP83869_OP_MODE		0x01df
#घोषणा DP83869_FX_CTRL		0x0c00

#घोषणा DP83869_SW_RESET	BIT(15)
#घोषणा DP83869_SW_RESTART	BIT(14)

/* MICR Interrupt bits */
#घोषणा MII_DP83869_MICR_AN_ERR_INT_EN		BIT(15)
#घोषणा MII_DP83869_MICR_SPEED_CHNG_INT_EN	BIT(14)
#घोषणा MII_DP83869_MICR_DUP_MODE_CHNG_INT_EN	BIT(13)
#घोषणा MII_DP83869_MICR_PAGE_RXD_INT_EN	BIT(12)
#घोषणा MII_DP83869_MICR_AUTONEG_COMP_INT_EN	BIT(11)
#घोषणा MII_DP83869_MICR_LINK_STS_CHNG_INT_EN	BIT(10)
#घोषणा MII_DP83869_MICR_FALSE_CARRIER_INT_EN	BIT(8)
#घोषणा MII_DP83869_MICR_SLEEP_MODE_CHNG_INT_EN	BIT(4)
#घोषणा MII_DP83869_MICR_WOL_INT_EN		BIT(3)
#घोषणा MII_DP83869_MICR_XGMII_ERR_INT_EN	BIT(2)
#घोषणा MII_DP83869_MICR_POL_CHNG_INT_EN	BIT(1)
#घोषणा MII_DP83869_MICR_JABBER_INT_EN		BIT(0)

#घोषणा MII_DP83869_BMCR_DEFAULT	(BMCR_ANENABLE | \
					 BMCR_FULLDPLX | \
					 BMCR_SPEED1000)

#घोषणा MII_DP83869_FIBER_ADVERTISE    (ADVERTISED_FIBRE | \
					ADVERTISED_Pause | \
					ADVERTISED_Asym_Pause)

/* This is the same bit mask as the BMCR so re-use the BMCR शेष */
#घोषणा DP83869_FX_CTRL_DEFAULT	MII_DP83869_BMCR_DEFAULT

/* CFG1 bits */
#घोषणा DP83869_CFG1_DEFAULT	(ADVERTISE_1000HALF | \
				 ADVERTISE_1000FULL | \
				 CTL1000_AS_MASTER)

/* RGMIICTL bits */
#घोषणा DP83869_RGMII_TX_CLK_DELAY_EN		BIT(1)
#घोषणा DP83869_RGMII_RX_CLK_DELAY_EN		BIT(0)

/* RGMIIDCTL */
#घोषणा DP83869_RGMII_CLK_DELAY_SHIFT		4
#घोषणा DP83869_CLK_DELAY_DEF			7

/* STRAP_STS1 bits */
#घोषणा DP83869_STRAP_OP_MODE_MASK		GENMASK(2, 0)
#घोषणा DP83869_STRAP_STS1_RESERVED		BIT(11)
#घोषणा DP83869_STRAP_MIRROR_ENABLED           BIT(12)

/* PHYCTRL bits */
#घोषणा DP83869_RX_FIFO_SHIFT	12
#घोषणा DP83869_TX_FIFO_SHIFT	14

/* PHY_CTRL lower bytes 0x48 are declared as reserved */
#घोषणा DP83869_PHY_CTRL_DEFAULT	0x48
#घोषणा DP83869_PHYCR_FIFO_DEPTH_MASK	GENMASK(15, 12)
#घोषणा DP83869_PHYCR_RESERVED_MASK	BIT(11)

/* IO_MUX_CFG bits */
#घोषणा DP83869_IO_MUX_CFG_IO_IMPEDANCE_CTRL	0x1f

#घोषणा DP83869_IO_MUX_CFG_IO_IMPEDANCE_MAX	0x0
#घोषणा DP83869_IO_MUX_CFG_IO_IMPEDANCE_MIN	0x1f
#घोषणा DP83869_IO_MUX_CFG_CLK_O_SEL_MASK	(0x1f << 8)
#घोषणा DP83869_IO_MUX_CFG_CLK_O_SEL_SHIFT	8

/* CFG3 bits */
#घोषणा DP83869_CFG3_PORT_MIRROR_EN              BIT(0)

/* CFG4 bits */
#घोषणा DP83869_INT_OE	BIT(7)

/* OP MODE */
#घोषणा DP83869_OP_MODE_MII			BIT(5)
#घोषणा DP83869_SGMII_RGMII_BRIDGE		BIT(6)

/* RXFCFG bits*/
#घोषणा DP83869_WOL_MAGIC_EN		BIT(0)
#घोषणा DP83869_WOL_PATTERN_EN		BIT(1)
#घोषणा DP83869_WOL_BCAST_EN		BIT(2)
#घोषणा DP83869_WOL_UCAST_EN		BIT(4)
#घोषणा DP83869_WOL_SEC_EN		BIT(5)
#घोषणा DP83869_WOL_ENH_MAC		BIT(7)

/* CFG2 bits */
#घोषणा DP83869_DOWNSHIFT_EN		(BIT(8) | BIT(9))
#घोषणा DP83869_DOWNSHIFT_ATTEMPT_MASK	(BIT(10) | BIT(11))
#घोषणा DP83869_DOWNSHIFT_1_COUNT_VAL	0
#घोषणा DP83869_DOWNSHIFT_2_COUNT_VAL	1
#घोषणा DP83869_DOWNSHIFT_4_COUNT_VAL	2
#घोषणा DP83869_DOWNSHIFT_8_COUNT_VAL	3
#घोषणा DP83869_DOWNSHIFT_1_COUNT	1
#घोषणा DP83869_DOWNSHIFT_2_COUNT	2
#घोषणा DP83869_DOWNSHIFT_4_COUNT	4
#घोषणा DP83869_DOWNSHIFT_8_COUNT	8

क्रमागत अणु
	DP83869_PORT_MIRRORING_KEEP,
	DP83869_PORT_MIRRORING_EN,
	DP83869_PORT_MIRRORING_DIS,
पूर्ण;

काष्ठा dp83869_निजी अणु
	पूर्णांक tx_fअगरo_depth;
	पूर्णांक rx_fअगरo_depth;
	s32 rx_पूर्णांक_delay;
	s32 tx_पूर्णांक_delay;
	पूर्णांक io_impedance;
	पूर्णांक port_mirroring;
	bool rxctrl_strap_quirk;
	पूर्णांक clk_output_sel;
	पूर्णांक mode;
पूर्ण;

अटल पूर्णांक dp83869_पढ़ो_status(काष्ठा phy_device *phydev)
अणु
	काष्ठा dp83869_निजी *dp83869 = phydev->priv;
	पूर्णांक ret;

	ret = genphy_पढ़ो_status(phydev);
	अगर (ret)
		वापस ret;

	अगर (linkmode_test_bit(ETHTOOL_LINK_MODE_FIBRE_BIT, phydev->supported)) अणु
		अगर (phydev->link) अणु
			अगर (dp83869->mode == DP83869_RGMII_100_BASE)
				phydev->speed = SPEED_100;
		पूर्ण अन्यथा अणु
			phydev->speed = SPEED_UNKNOWN;
			phydev->duplex = DUPLEX_UNKNOWN;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dp83869_ack_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err = phy_पढ़ो(phydev, MII_DP83869_ISR);

	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक dp83869_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	पूर्णांक micr_status = 0, err;

	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED) अणु
		err = dp83869_ack_पूर्णांकerrupt(phydev);
		अगर (err)
			वापस err;

		micr_status = phy_पढ़ो(phydev, MII_DP83869_MICR);
		अगर (micr_status < 0)
			वापस micr_status;

		micr_status |=
			(MII_DP83869_MICR_AN_ERR_INT_EN |
			MII_DP83869_MICR_SPEED_CHNG_INT_EN |
			MII_DP83869_MICR_AUTONEG_COMP_INT_EN |
			MII_DP83869_MICR_LINK_STS_CHNG_INT_EN |
			MII_DP83869_MICR_DUP_MODE_CHNG_INT_EN |
			MII_DP83869_MICR_SLEEP_MODE_CHNG_INT_EN);

		err = phy_ग_लिखो(phydev, MII_DP83869_MICR, micr_status);
	पूर्ण अन्यथा अणु
		err = phy_ग_लिखो(phydev, MII_DP83869_MICR, micr_status);
		अगर (err)
			वापस err;

		err = dp83869_ack_पूर्णांकerrupt(phydev);
	पूर्ण

	वापस err;
पूर्ण

अटल irqवापस_t dp83869_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक irq_status, irq_enabled;

	irq_status = phy_पढ़ो(phydev, MII_DP83869_ISR);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	irq_enabled = phy_पढ़ो(phydev, MII_DP83869_MICR);
	अगर (irq_enabled < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	अगर (!(irq_status & irq_enabled))
		वापस IRQ_NONE;

	phy_trigger_machine(phydev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक dp83869_set_wol(काष्ठा phy_device *phydev,
			   काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा net_device *ndev = phydev->attached_dev;
	पूर्णांक val_rxcfg, val_micr;
	u8 *mac;
	पूर्णांक ret;

	val_rxcfg = phy_पढ़ो_mmd(phydev, DP83869_DEVADDR, DP83869_RXFCFG);
	अगर (val_rxcfg < 0)
		वापस val_rxcfg;

	val_micr = phy_पढ़ो(phydev, MII_DP83869_MICR);
	अगर (val_micr < 0)
		वापस val_micr;

	अगर (wol->wolopts & (WAKE_MAGIC | WAKE_MAGICSECURE | WAKE_UCAST |
			    WAKE_BCAST)) अणु
		val_rxcfg |= DP83869_WOL_ENH_MAC;
		val_micr |= MII_DP83869_MICR_WOL_INT_EN;

		अगर (wol->wolopts & WAKE_MAGIC ||
		    wol->wolopts & WAKE_MAGICSECURE) अणु
			mac = (u8 *)ndev->dev_addr;

			अगर (!is_valid_ether_addr(mac))
				वापस -EINVAL;

			ret = phy_ग_लिखो_mmd(phydev, DP83869_DEVADDR,
					    DP83869_RXFPMD1,
					    mac[1] << 8 | mac[0]);
			अगर (ret)
				वापस ret;

			ret = phy_ग_लिखो_mmd(phydev, DP83869_DEVADDR,
					    DP83869_RXFPMD2,
					    mac[3] << 8 | mac[2]);
			अगर (ret)
				वापस ret;

			ret = phy_ग_लिखो_mmd(phydev, DP83869_DEVADDR,
					    DP83869_RXFPMD3,
					    mac[5] << 8 | mac[4]);
			अगर (ret)
				वापस ret;

			val_rxcfg |= DP83869_WOL_MAGIC_EN;
		पूर्ण अन्यथा अणु
			val_rxcfg &= ~DP83869_WOL_MAGIC_EN;
		पूर्ण

		अगर (wol->wolopts & WAKE_MAGICSECURE) अणु
			ret = phy_ग_लिखो_mmd(phydev, DP83869_DEVADDR,
					    DP83869_RXFSOP1,
					    (wol->sopass[1] << 8) | wol->sopass[0]);
			अगर (ret)
				वापस ret;

			ret = phy_ग_लिखो_mmd(phydev, DP83869_DEVADDR,
					    DP83869_RXFSOP2,
					    (wol->sopass[3] << 8) | wol->sopass[2]);
			अगर (ret)
				वापस ret;
			ret = phy_ग_लिखो_mmd(phydev, DP83869_DEVADDR,
					    DP83869_RXFSOP3,
					    (wol->sopass[5] << 8) | wol->sopass[4]);
			अगर (ret)
				वापस ret;

			val_rxcfg |= DP83869_WOL_SEC_EN;
		पूर्ण अन्यथा अणु
			val_rxcfg &= ~DP83869_WOL_SEC_EN;
		पूर्ण

		अगर (wol->wolopts & WAKE_UCAST)
			val_rxcfg |= DP83869_WOL_UCAST_EN;
		अन्यथा
			val_rxcfg &= ~DP83869_WOL_UCAST_EN;

		अगर (wol->wolopts & WAKE_BCAST)
			val_rxcfg |= DP83869_WOL_BCAST_EN;
		अन्यथा
			val_rxcfg &= ~DP83869_WOL_BCAST_EN;
	पूर्ण अन्यथा अणु
		val_rxcfg &= ~DP83869_WOL_ENH_MAC;
		val_micr &= ~MII_DP83869_MICR_WOL_INT_EN;
	पूर्ण

	ret = phy_ग_लिखो_mmd(phydev, DP83869_DEVADDR, DP83869_RXFCFG, val_rxcfg);
	अगर (ret)
		वापस ret;

	वापस phy_ग_लिखो(phydev, MII_DP83869_MICR, val_micr);
पूर्ण

अटल व्योम dp83869_get_wol(काष्ठा phy_device *phydev,
			    काष्ठा ethtool_wolinfo *wol)
अणु
	पूर्णांक value, sopass_val;

	wol->supported = (WAKE_UCAST | WAKE_BCAST | WAKE_MAGIC |
			WAKE_MAGICSECURE);
	wol->wolopts = 0;

	value = phy_पढ़ो_mmd(phydev, DP83869_DEVADDR, DP83869_RXFCFG);
	अगर (value < 0) अणु
		phydev_err(phydev, "Failed to read RX CFG\n");
		वापस;
	पूर्ण

	अगर (value & DP83869_WOL_UCAST_EN)
		wol->wolopts |= WAKE_UCAST;

	अगर (value & DP83869_WOL_BCAST_EN)
		wol->wolopts |= WAKE_BCAST;

	अगर (value & DP83869_WOL_MAGIC_EN)
		wol->wolopts |= WAKE_MAGIC;

	अगर (value & DP83869_WOL_SEC_EN) अणु
		sopass_val = phy_पढ़ो_mmd(phydev, DP83869_DEVADDR,
					  DP83869_RXFSOP1);
		अगर (sopass_val < 0) अणु
			phydev_err(phydev, "Failed to read RX SOP 1\n");
			वापस;
		पूर्ण

		wol->sopass[0] = (sopass_val & 0xff);
		wol->sopass[1] = (sopass_val >> 8);

		sopass_val = phy_पढ़ो_mmd(phydev, DP83869_DEVADDR,
					  DP83869_RXFSOP2);
		अगर (sopass_val < 0) अणु
			phydev_err(phydev, "Failed to read RX SOP 2\n");
			वापस;
		पूर्ण

		wol->sopass[2] = (sopass_val & 0xff);
		wol->sopass[3] = (sopass_val >> 8);

		sopass_val = phy_पढ़ो_mmd(phydev, DP83869_DEVADDR,
					  DP83869_RXFSOP3);
		अगर (sopass_val < 0) अणु
			phydev_err(phydev, "Failed to read RX SOP 3\n");
			वापस;
		पूर्ण

		wol->sopass[4] = (sopass_val & 0xff);
		wol->sopass[5] = (sopass_val >> 8);

		wol->wolopts |= WAKE_MAGICSECURE;
	पूर्ण

	अगर (!(value & DP83869_WOL_ENH_MAC))
		wol->wolopts = 0;
पूर्ण

अटल पूर्णांक dp83869_get_करोwnshअगरt(काष्ठा phy_device *phydev, u8 *data)
अणु
	पूर्णांक val, cnt, enable, count;

	val = phy_पढ़ो(phydev, DP83869_CFG2);
	अगर (val < 0)
		वापस val;

	enable = FIELD_GET(DP83869_DOWNSHIFT_EN, val);
	cnt = FIELD_GET(DP83869_DOWNSHIFT_ATTEMPT_MASK, val);

	चयन (cnt) अणु
	हाल DP83869_DOWNSHIFT_1_COUNT_VAL:
		count = DP83869_DOWNSHIFT_1_COUNT;
		अवरोध;
	हाल DP83869_DOWNSHIFT_2_COUNT_VAL:
		count = DP83869_DOWNSHIFT_2_COUNT;
		अवरोध;
	हाल DP83869_DOWNSHIFT_4_COUNT_VAL:
		count = DP83869_DOWNSHIFT_4_COUNT;
		अवरोध;
	हाल DP83869_DOWNSHIFT_8_COUNT_VAL:
		count = DP83869_DOWNSHIFT_8_COUNT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	*data = enable ? count : DOWNSHIFT_DEV_DISABLE;

	वापस 0;
पूर्ण

अटल पूर्णांक dp83869_set_करोwnshअगरt(काष्ठा phy_device *phydev, u8 cnt)
अणु
	पूर्णांक val, count;

	अगर (cnt > DP83869_DOWNSHIFT_8_COUNT)
		वापस -EINVAL;

	अगर (!cnt)
		वापस phy_clear_bits(phydev, DP83869_CFG2,
				      DP83869_DOWNSHIFT_EN);

	चयन (cnt) अणु
	हाल DP83869_DOWNSHIFT_1_COUNT:
		count = DP83869_DOWNSHIFT_1_COUNT_VAL;
		अवरोध;
	हाल DP83869_DOWNSHIFT_2_COUNT:
		count = DP83869_DOWNSHIFT_2_COUNT_VAL;
		अवरोध;
	हाल DP83869_DOWNSHIFT_4_COUNT:
		count = DP83869_DOWNSHIFT_4_COUNT_VAL;
		अवरोध;
	हाल DP83869_DOWNSHIFT_8_COUNT:
		count = DP83869_DOWNSHIFT_8_COUNT_VAL;
		अवरोध;
	शेष:
		phydev_err(phydev,
			   "Downshift count must be 1, 2, 4 or 8\n");
		वापस -EINVAL;
	पूर्ण

	val = DP83869_DOWNSHIFT_EN;
	val |= FIELD_PREP(DP83869_DOWNSHIFT_ATTEMPT_MASK, count);

	वापस phy_modअगरy(phydev, DP83869_CFG2,
			  DP83869_DOWNSHIFT_EN | DP83869_DOWNSHIFT_ATTEMPT_MASK,
			  val);
पूर्ण

अटल पूर्णांक dp83869_get_tunable(काष्ठा phy_device *phydev,
			       काष्ठा ethtool_tunable *tuna, व्योम *data)
अणु
	चयन (tuna->id) अणु
	हाल ETHTOOL_PHY_DOWNSHIFT:
		वापस dp83869_get_करोwnshअगरt(phydev, data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक dp83869_set_tunable(काष्ठा phy_device *phydev,
			       काष्ठा ethtool_tunable *tuna, स्थिर व्योम *data)
अणु
	चयन (tuna->id) अणु
	हाल ETHTOOL_PHY_DOWNSHIFT:
		वापस dp83869_set_करोwnshअगरt(phydev, *(स्थिर u8 *)data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक dp83869_config_port_mirroring(काष्ठा phy_device *phydev)
अणु
	काष्ठा dp83869_निजी *dp83869 = phydev->priv;

	अगर (dp83869->port_mirroring == DP83869_PORT_MIRRORING_EN)
		वापस phy_set_bits_mmd(phydev, DP83869_DEVADDR,
					DP83869_GEN_CFG3,
					DP83869_CFG3_PORT_MIRROR_EN);
	अन्यथा
		वापस phy_clear_bits_mmd(phydev, DP83869_DEVADDR,
					  DP83869_GEN_CFG3,
					  DP83869_CFG3_PORT_MIRROR_EN);
पूर्ण

अटल पूर्णांक dp83869_set_strapped_mode(काष्ठा phy_device *phydev)
अणु
	काष्ठा dp83869_निजी *dp83869 = phydev->priv;
	पूर्णांक val;

	val = phy_पढ़ो_mmd(phydev, DP83869_DEVADDR, DP83869_STRAP_STS1);
	अगर (val < 0)
		वापस val;

	dp83869->mode = val & DP83869_STRAP_OP_MODE_MASK;

	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_OF_MDIO)
अटल स्थिर पूर्णांक dp83869_पूर्णांकernal_delay[] = अणु250, 500, 750, 1000, 1250, 1500,
					     1750, 2000, 2250, 2500, 2750, 3000,
					     3250, 3500, 3750, 4000पूर्ण;

अटल पूर्णांक dp83869_of_init(काष्ठा phy_device *phydev)
अणु
	काष्ठा dp83869_निजी *dp83869 = phydev->priv;
	काष्ठा device *dev = &phydev->mdio.dev;
	काष्ठा device_node *of_node = dev->of_node;
	पूर्णांक delay_size = ARRAY_SIZE(dp83869_पूर्णांकernal_delay);
	पूर्णांक ret;

	अगर (!of_node)
		वापस -ENODEV;

	dp83869->io_impedance = -EINVAL;

	/* Optional configuration */
	ret = of_property_पढ़ो_u32(of_node, "ti,clk-output-sel",
				   &dp83869->clk_output_sel);
	अगर (ret || dp83869->clk_output_sel > DP83869_CLK_O_SEL_REF_CLK)
		dp83869->clk_output_sel = DP83869_CLK_O_SEL_REF_CLK;

	ret = of_property_पढ़ो_u32(of_node, "ti,op-mode", &dp83869->mode);
	अगर (ret == 0) अणु
		अगर (dp83869->mode < DP83869_RGMII_COPPER_ETHERNET ||
		    dp83869->mode > DP83869_SGMII_COPPER_ETHERNET)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		ret = dp83869_set_strapped_mode(phydev);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (of_property_पढ़ो_bool(of_node, "ti,max-output-impedance"))
		dp83869->io_impedance = DP83869_IO_MUX_CFG_IO_IMPEDANCE_MAX;
	अन्यथा अगर (of_property_पढ़ो_bool(of_node, "ti,min-output-impedance"))
		dp83869->io_impedance = DP83869_IO_MUX_CFG_IO_IMPEDANCE_MIN;

	अगर (of_property_पढ़ो_bool(of_node, "enet-phy-lane-swap")) अणु
		dp83869->port_mirroring = DP83869_PORT_MIRRORING_EN;
	पूर्ण अन्यथा अणु
		/* If the lane swap is not in the DT then check the straps */
		ret = phy_पढ़ो_mmd(phydev, DP83869_DEVADDR, DP83869_STRAP_STS1);
		अगर (ret < 0)
			वापस ret;

		अगर (ret & DP83869_STRAP_MIRROR_ENABLED)
			dp83869->port_mirroring = DP83869_PORT_MIRRORING_EN;
		अन्यथा
			dp83869->port_mirroring = DP83869_PORT_MIRRORING_DIS;

		ret = 0;
	पूर्ण

	अगर (of_property_पढ़ो_u32(of_node, "rx-fifo-depth",
				 &dp83869->rx_fअगरo_depth))
		dp83869->rx_fअगरo_depth = DP83869_PHYCR_FIFO_DEPTH_4_B_NIB;

	अगर (of_property_पढ़ो_u32(of_node, "tx-fifo-depth",
				 &dp83869->tx_fअगरo_depth))
		dp83869->tx_fअगरo_depth = DP83869_PHYCR_FIFO_DEPTH_4_B_NIB;

	dp83869->rx_पूर्णांक_delay = phy_get_पूर्णांकernal_delay(phydev, dev,
						       &dp83869_पूर्णांकernal_delay[0],
						       delay_size, true);
	अगर (dp83869->rx_पूर्णांक_delay < 0)
		dp83869->rx_पूर्णांक_delay =
				dp83869_पूर्णांकernal_delay[DP83869_CLK_DELAY_DEF];

	dp83869->tx_पूर्णांक_delay = phy_get_पूर्णांकernal_delay(phydev, dev,
						       &dp83869_पूर्णांकernal_delay[0],
						       delay_size, false);
	अगर (dp83869->tx_पूर्णांक_delay < 0)
		dp83869->tx_पूर्णांक_delay =
				dp83869_पूर्णांकernal_delay[DP83869_CLK_DELAY_DEF];

	वापस ret;
पूर्ण
#अन्यथा
अटल पूर्णांक dp83869_of_init(काष्ठा phy_device *phydev)
अणु
	वापस dp83869_set_strapped_mode(phydev);
पूर्ण
#पूर्ण_अगर /* CONFIG_OF_MDIO */

अटल पूर्णांक dp83869_configure_rgmii(काष्ठा phy_device *phydev,
				   काष्ठा dp83869_निजी *dp83869)
अणु
	पूर्णांक ret = 0, val;

	अगर (phy_पूर्णांकerface_is_rgmii(phydev)) अणु
		val = phy_पढ़ो(phydev, MII_DP83869_PHYCTRL);
		अगर (val < 0)
			वापस val;

		val &= ~DP83869_PHYCR_FIFO_DEPTH_MASK;
		val |= (dp83869->tx_fअगरo_depth << DP83869_TX_FIFO_SHIFT);
		val |= (dp83869->rx_fअगरo_depth << DP83869_RX_FIFO_SHIFT);

		ret = phy_ग_लिखो(phydev, MII_DP83869_PHYCTRL, val);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (dp83869->io_impedance >= 0)
		ret = phy_modअगरy_mmd(phydev, DP83869_DEVADDR,
				     DP83869_IO_MUX_CFG,
				     DP83869_IO_MUX_CFG_IO_IMPEDANCE_CTRL,
				     dp83869->io_impedance &
				     DP83869_IO_MUX_CFG_IO_IMPEDANCE_CTRL);

	वापस ret;
पूर्ण

अटल पूर्णांक dp83869_configure_fiber(काष्ठा phy_device *phydev,
				   काष्ठा dp83869_निजी *dp83869)
अणु
	पूर्णांक bmcr;
	पूर्णांक ret;

	/* Only allow advertising what this PHY supports */
	linkmode_and(phydev->advertising, phydev->advertising,
		     phydev->supported);

	linkmode_set_bit(ETHTOOL_LINK_MODE_FIBRE_BIT, phydev->supported);
	linkmode_set_bit(ADVERTISED_FIBRE, phydev->advertising);

	अगर (dp83869->mode == DP83869_RGMII_1000_BASE) अणु
		linkmode_set_bit(ETHTOOL_LINK_MODE_1000baseX_Full_BIT,
				 phydev->supported);
	पूर्ण अन्यथा अणु
		linkmode_set_bit(ETHTOOL_LINK_MODE_100baseFX_Full_BIT,
				 phydev->supported);
		linkmode_set_bit(ETHTOOL_LINK_MODE_100baseFX_Half_BIT,
				 phydev->supported);

		/* Auto neg is not supported in 100base FX mode */
		bmcr = phy_पढ़ो(phydev, MII_BMCR);
		अगर (bmcr < 0)
			वापस bmcr;

		phydev->स्वतःneg = AUTONEG_DISABLE;
		linkmode_clear_bit(ETHTOOL_LINK_MODE_Autoneg_BIT, phydev->supported);
		linkmode_clear_bit(ETHTOOL_LINK_MODE_Autoneg_BIT, phydev->advertising);

		अगर (bmcr & BMCR_ANENABLE) अणु
			ret =  phy_modअगरy(phydev, MII_BMCR, BMCR_ANENABLE, 0);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण

	/* Update advertising from supported */
	linkmode_or(phydev->advertising, phydev->advertising,
		    phydev->supported);

	वापस 0;
पूर्ण

अटल पूर्णांक dp83869_configure_mode(काष्ठा phy_device *phydev,
				  काष्ठा dp83869_निजी *dp83869)
अणु
	पूर्णांक phy_ctrl_val;
	पूर्णांक ret;

	अगर (dp83869->mode < DP83869_RGMII_COPPER_ETHERNET ||
	    dp83869->mode > DP83869_SGMII_COPPER_ETHERNET)
		वापस -EINVAL;

	/* Below init sequence क्रम each operational mode is defined in
	 * section 9.4.8 of the datasheet.
	 */
	ret = phy_ग_लिखो_mmd(phydev, DP83869_DEVADDR, DP83869_OP_MODE,
			    dp83869->mode);
	अगर (ret)
		वापस ret;

	ret = phy_ग_लिखो(phydev, MII_BMCR, MII_DP83869_BMCR_DEFAULT);
	अगर (ret)
		वापस ret;

	phy_ctrl_val = (dp83869->rx_fअगरo_depth << DP83869_RX_FIFO_SHIFT |
			dp83869->tx_fअगरo_depth << DP83869_TX_FIFO_SHIFT |
			DP83869_PHY_CTRL_DEFAULT);

	चयन (dp83869->mode) अणु
	हाल DP83869_RGMII_COPPER_ETHERNET:
		ret = phy_ग_लिखो(phydev, MII_DP83869_PHYCTRL,
				phy_ctrl_val);
		अगर (ret)
			वापस ret;

		ret = phy_ग_लिखो(phydev, MII_CTRL1000, DP83869_CFG1_DEFAULT);
		अगर (ret)
			वापस ret;

		ret = dp83869_configure_rgmii(phydev, dp83869);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल DP83869_RGMII_SGMII_BRIDGE:
		ret = phy_modअगरy_mmd(phydev, DP83869_DEVADDR, DP83869_OP_MODE,
				     DP83869_SGMII_RGMII_BRIDGE,
				     DP83869_SGMII_RGMII_BRIDGE);
		अगर (ret)
			वापस ret;

		ret = phy_ग_लिखो_mmd(phydev, DP83869_DEVADDR,
				    DP83869_FX_CTRL, DP83869_FX_CTRL_DEFAULT);
		अगर (ret)
			वापस ret;

		अवरोध;
	हाल DP83869_1000M_MEDIA_CONVERT:
		ret = phy_ग_लिखो(phydev, MII_DP83869_PHYCTRL,
				phy_ctrl_val);
		अगर (ret)
			वापस ret;

		ret = phy_ग_लिखो_mmd(phydev, DP83869_DEVADDR,
				    DP83869_FX_CTRL, DP83869_FX_CTRL_DEFAULT);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल DP83869_100M_MEDIA_CONVERT:
		ret = phy_ग_लिखो(phydev, MII_DP83869_PHYCTRL,
				phy_ctrl_val);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल DP83869_SGMII_COPPER_ETHERNET:
		ret = phy_ग_लिखो(phydev, MII_DP83869_PHYCTRL,
				phy_ctrl_val);
		अगर (ret)
			वापस ret;

		ret = phy_ग_लिखो(phydev, MII_CTRL1000, DP83869_CFG1_DEFAULT);
		अगर (ret)
			वापस ret;

		ret = phy_ग_लिखो_mmd(phydev, DP83869_DEVADDR,
				    DP83869_FX_CTRL, DP83869_FX_CTRL_DEFAULT);
		अगर (ret)
			वापस ret;

		अवरोध;
	हाल DP83869_RGMII_1000_BASE:
	हाल DP83869_RGMII_100_BASE:
		ret = dp83869_configure_fiber(phydev, dp83869);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dp83869_config_init(काष्ठा phy_device *phydev)
अणु
	काष्ठा dp83869_निजी *dp83869 = phydev->priv;
	पूर्णांक ret, val;

	/* Force speed optimization क्रम the PHY even अगर it strapped */
	ret = phy_modअगरy(phydev, DP83869_CFG2, DP83869_DOWNSHIFT_EN,
			 DP83869_DOWNSHIFT_EN);
	अगर (ret)
		वापस ret;

	ret = dp83869_configure_mode(phydev, dp83869);
	अगर (ret)
		वापस ret;

	/* Enable Interrupt output INT_OE in CFG4 रेजिस्टर */
	अगर (phy_पूर्णांकerrupt_is_valid(phydev)) अणु
		val = phy_पढ़ो(phydev, DP83869_CFG4);
		val |= DP83869_INT_OE;
		phy_ग_लिखो(phydev, DP83869_CFG4, val);
	पूर्ण

	अगर (dp83869->port_mirroring != DP83869_PORT_MIRRORING_KEEP)
		dp83869_config_port_mirroring(phydev);

	/* Clock output selection अगर muxing property is set */
	अगर (dp83869->clk_output_sel != DP83869_CLK_O_SEL_REF_CLK)
		ret = phy_modअगरy_mmd(phydev,
				     DP83869_DEVADDR, DP83869_IO_MUX_CFG,
				     DP83869_IO_MUX_CFG_CLK_O_SEL_MASK,
				     dp83869->clk_output_sel <<
				     DP83869_IO_MUX_CFG_CLK_O_SEL_SHIFT);

	अगर (phy_पूर्णांकerface_is_rgmii(phydev)) अणु
		ret = phy_ग_लिखो_mmd(phydev, DP83869_DEVADDR, DP83869_RGMIIDCTL,
				    dp83869->rx_पूर्णांक_delay |
			dp83869->tx_पूर्णांक_delay << DP83869_RGMII_CLK_DELAY_SHIFT);
		अगर (ret)
			वापस ret;

		val = phy_पढ़ो_mmd(phydev, DP83869_DEVADDR, DP83869_RGMIICTL);
		val |= (DP83869_RGMII_TX_CLK_DELAY_EN |
			DP83869_RGMII_RX_CLK_DELAY_EN);

		अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_ID)
			val &= ~(DP83869_RGMII_TX_CLK_DELAY_EN |
				 DP83869_RGMII_RX_CLK_DELAY_EN);

		अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_TXID)
			val &= ~DP83869_RGMII_TX_CLK_DELAY_EN;

		अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_RXID)
			val &= ~DP83869_RGMII_RX_CLK_DELAY_EN;

		ret = phy_ग_लिखो_mmd(phydev, DP83869_DEVADDR, DP83869_RGMIICTL,
				    val);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dp83869_probe(काष्ठा phy_device *phydev)
अणु
	काष्ठा dp83869_निजी *dp83869;
	पूर्णांक ret;

	dp83869 = devm_kzalloc(&phydev->mdio.dev, माप(*dp83869),
			       GFP_KERNEL);
	अगर (!dp83869)
		वापस -ENOMEM;

	phydev->priv = dp83869;

	ret = dp83869_of_init(phydev);
	अगर (ret)
		वापस ret;

	अगर (dp83869->mode == DP83869_RGMII_100_BASE ||
	    dp83869->mode == DP83869_RGMII_1000_BASE)
		phydev->port = PORT_FIBRE;

	वापस dp83869_config_init(phydev);
पूर्ण

अटल पूर्णांक dp83869_phy_reset(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	ret = phy_ग_लिखो(phydev, DP83869_CTRL, DP83869_SW_RESET);
	अगर (ret < 0)
		वापस ret;

	usleep_range(10, 20);

	/* Global sw reset sets all रेजिस्टरs to शेष.
	 * Need to set the रेजिस्टरs in the PHY to the right config.
	 */
	वापस dp83869_config_init(phydev);
पूर्ण

अटल काष्ठा phy_driver dp83869_driver[] = अणु
	अणु
		PHY_ID_MATCH_MODEL(DP83869_PHY_ID),
		.name		= "TI DP83869",

		.probe          = dp83869_probe,
		.config_init	= dp83869_config_init,
		.soft_reset	= dp83869_phy_reset,

		/* IRQ related */
		.config_पूर्णांकr	= dp83869_config_पूर्णांकr,
		.handle_पूर्णांकerrupt = dp83869_handle_पूर्णांकerrupt,
		.पढ़ो_status	= dp83869_पढ़ो_status,

		.get_tunable	= dp83869_get_tunable,
		.set_tunable	= dp83869_set_tunable,

		.get_wol	= dp83869_get_wol,
		.set_wol	= dp83869_set_wol,

		.suspend	= genphy_suspend,
		.resume		= genphy_resume,
	पूर्ण,
पूर्ण;
module_phy_driver(dp83869_driver);

अटल काष्ठा mdio_device_id __maybe_unused dp83869_tbl[] = अणु
	अणु PHY_ID_MATCH_MODEL(DP83869_PHY_ID) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(mdio, dp83869_tbl);

MODULE_DESCRIPTION("Texas Instruments DP83869 PHY driver");
MODULE_AUTHOR("Dan Murphy <dmurphy@ti.com");
MODULE_LICENSE("GPL v2");
