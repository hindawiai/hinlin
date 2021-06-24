<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Driver क्रम the Texas Instruments DP83867 PHY
 *
 * Copyright (C) 2015 Texas Instruments Inc.
 */

#समावेश <linux/ethtool.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mii.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/phy.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/bitfield.h>

#समावेश <dt-bindings/net/ti-dp83867.h>

#घोषणा DP83867_PHY_ID		0x2000a231
#घोषणा DP83867_DEVADDR		0x1f

#घोषणा MII_DP83867_PHYCTRL	0x10
#घोषणा MII_DP83867_PHYSTS	0x11
#घोषणा MII_DP83867_MICR	0x12
#घोषणा MII_DP83867_ISR		0x13
#घोषणा DP83867_CFG2		0x14
#घोषणा DP83867_CFG3		0x1e
#घोषणा DP83867_CTRL		0x1f

/* Extended Registers */
#घोषणा DP83867_FLD_THR_CFG	0x002e
#घोषणा DP83867_CFG4		0x0031
#घोषणा DP83867_CFG4_SGMII_ANEG_MASK (BIT(5) | BIT(6))
#घोषणा DP83867_CFG4_SGMII_ANEG_TIMER_11MS   (3 << 5)
#घोषणा DP83867_CFG4_SGMII_ANEG_TIMER_800US  (2 << 5)
#घोषणा DP83867_CFG4_SGMII_ANEG_TIMER_2US    (1 << 5)
#घोषणा DP83867_CFG4_SGMII_ANEG_TIMER_16MS   (0 << 5)

#घोषणा DP83867_RGMIICTL	0x0032
#घोषणा DP83867_STRAP_STS1	0x006E
#घोषणा DP83867_STRAP_STS2	0x006f
#घोषणा DP83867_RGMIIDCTL	0x0086
#घोषणा DP83867_RXFCFG		0x0134
#घोषणा DP83867_RXFPMD1	0x0136
#घोषणा DP83867_RXFPMD2	0x0137
#घोषणा DP83867_RXFPMD3	0x0138
#घोषणा DP83867_RXFSOP1	0x0139
#घोषणा DP83867_RXFSOP2	0x013A
#घोषणा DP83867_RXFSOP3	0x013B
#घोषणा DP83867_IO_MUX_CFG	0x0170
#घोषणा DP83867_SGMIICTL	0x00D3
#घोषणा DP83867_10M_SGMII_CFG   0x016F
#घोषणा DP83867_10M_SGMII_RATE_ADAPT_MASK BIT(7)

#घोषणा DP83867_SW_RESET	BIT(15)
#घोषणा DP83867_SW_RESTART	BIT(14)

/* MICR Interrupt bits */
#घोषणा MII_DP83867_MICR_AN_ERR_INT_EN		BIT(15)
#घोषणा MII_DP83867_MICR_SPEED_CHNG_INT_EN	BIT(14)
#घोषणा MII_DP83867_MICR_DUP_MODE_CHNG_INT_EN	BIT(13)
#घोषणा MII_DP83867_MICR_PAGE_RXD_INT_EN	BIT(12)
#घोषणा MII_DP83867_MICR_AUTONEG_COMP_INT_EN	BIT(11)
#घोषणा MII_DP83867_MICR_LINK_STS_CHNG_INT_EN	BIT(10)
#घोषणा MII_DP83867_MICR_FALSE_CARRIER_INT_EN	BIT(8)
#घोषणा MII_DP83867_MICR_SLEEP_MODE_CHNG_INT_EN	BIT(4)
#घोषणा MII_DP83867_MICR_WOL_INT_EN		BIT(3)
#घोषणा MII_DP83867_MICR_XGMII_ERR_INT_EN	BIT(2)
#घोषणा MII_DP83867_MICR_POL_CHNG_INT_EN	BIT(1)
#घोषणा MII_DP83867_MICR_JABBER_INT_EN		BIT(0)

/* RGMIICTL bits */
#घोषणा DP83867_RGMII_TX_CLK_DELAY_EN		BIT(1)
#घोषणा DP83867_RGMII_RX_CLK_DELAY_EN		BIT(0)

/* SGMIICTL bits */
#घोषणा DP83867_SGMII_TYPE		BIT(14)

/* RXFCFG bits*/
#घोषणा DP83867_WOL_MAGIC_EN		BIT(0)
#घोषणा DP83867_WOL_BCAST_EN		BIT(2)
#घोषणा DP83867_WOL_UCAST_EN		BIT(4)
#घोषणा DP83867_WOL_SEC_EN		BIT(5)
#घोषणा DP83867_WOL_ENH_MAC		BIT(7)

/* STRAP_STS1 bits */
#घोषणा DP83867_STRAP_STS1_RESERVED		BIT(11)

/* STRAP_STS2 bits */
#घोषणा DP83867_STRAP_STS2_CLK_SKEW_TX_MASK	GENMASK(6, 4)
#घोषणा DP83867_STRAP_STS2_CLK_SKEW_TX_SHIFT	4
#घोषणा DP83867_STRAP_STS2_CLK_SKEW_RX_MASK	GENMASK(2, 0)
#घोषणा DP83867_STRAP_STS2_CLK_SKEW_RX_SHIFT	0
#घोषणा DP83867_STRAP_STS2_CLK_SKEW_NONE	BIT(2)
#घोषणा DP83867_STRAP_STS2_STRAP_FLD		BIT(10)

/* PHY CTRL bits */
#घोषणा DP83867_PHYCR_TX_FIFO_DEPTH_SHIFT	14
#घोषणा DP83867_PHYCR_RX_FIFO_DEPTH_SHIFT	12
#घोषणा DP83867_PHYCR_FIFO_DEPTH_MAX		0x03
#घोषणा DP83867_PHYCR_TX_FIFO_DEPTH_MASK	GENMASK(15, 14)
#घोषणा DP83867_PHYCR_RX_FIFO_DEPTH_MASK	GENMASK(13, 12)
#घोषणा DP83867_PHYCR_RESERVED_MASK		BIT(11)
#घोषणा DP83867_PHYCR_FORCE_LINK_GOOD		BIT(10)

/* RGMIIDCTL bits */
#घोषणा DP83867_RGMII_TX_CLK_DELAY_MAX		0xf
#घोषणा DP83867_RGMII_TX_CLK_DELAY_SHIFT	4
#घोषणा DP83867_RGMII_TX_CLK_DELAY_INV	(DP83867_RGMII_TX_CLK_DELAY_MAX + 1)
#घोषणा DP83867_RGMII_RX_CLK_DELAY_MAX		0xf
#घोषणा DP83867_RGMII_RX_CLK_DELAY_SHIFT	0
#घोषणा DP83867_RGMII_RX_CLK_DELAY_INV	(DP83867_RGMII_RX_CLK_DELAY_MAX + 1)

/* IO_MUX_CFG bits */
#घोषणा DP83867_IO_MUX_CFG_IO_IMPEDANCE_MASK	0x1f
#घोषणा DP83867_IO_MUX_CFG_IO_IMPEDANCE_MAX	0x0
#घोषणा DP83867_IO_MUX_CFG_IO_IMPEDANCE_MIN	0x1f
#घोषणा DP83867_IO_MUX_CFG_CLK_O_DISABLE	BIT(6)
#घोषणा DP83867_IO_MUX_CFG_CLK_O_SEL_MASK	(0x1f << 8)
#घोषणा DP83867_IO_MUX_CFG_CLK_O_SEL_SHIFT	8

/* PHY STS bits */
#घोषणा DP83867_PHYSTS_1000			BIT(15)
#घोषणा DP83867_PHYSTS_100			BIT(14)
#घोषणा DP83867_PHYSTS_DUPLEX			BIT(13)
#घोषणा DP83867_PHYSTS_LINK			BIT(10)

/* CFG2 bits */
#घोषणा DP83867_DOWNSHIFT_EN		(BIT(8) | BIT(9))
#घोषणा DP83867_DOWNSHIFT_ATTEMPT_MASK	(BIT(10) | BIT(11))
#घोषणा DP83867_DOWNSHIFT_1_COUNT_VAL	0
#घोषणा DP83867_DOWNSHIFT_2_COUNT_VAL	1
#घोषणा DP83867_DOWNSHIFT_4_COUNT_VAL	2
#घोषणा DP83867_DOWNSHIFT_8_COUNT_VAL	3
#घोषणा DP83867_DOWNSHIFT_1_COUNT	1
#घोषणा DP83867_DOWNSHIFT_2_COUNT	2
#घोषणा DP83867_DOWNSHIFT_4_COUNT	4
#घोषणा DP83867_DOWNSHIFT_8_COUNT	8

/* CFG3 bits */
#घोषणा DP83867_CFG3_INT_OE			BIT(7)
#घोषणा DP83867_CFG3_ROBUST_AUTO_MDIX		BIT(9)

/* CFG4 bits */
#घोषणा DP83867_CFG4_PORT_MIRROR_EN              BIT(0)

/* FLD_THR_CFG */
#घोषणा DP83867_FLD_THR_CFG_ENERGY_LOST_THR_MASK	0x7

क्रमागत अणु
	DP83867_PORT_MIRROING_KEEP,
	DP83867_PORT_MIRROING_EN,
	DP83867_PORT_MIRROING_DIS,
पूर्ण;

काष्ठा dp83867_निजी अणु
	u32 rx_id_delay;
	u32 tx_id_delay;
	u32 tx_fअगरo_depth;
	u32 rx_fअगरo_depth;
	पूर्णांक io_impedance;
	पूर्णांक port_mirroring;
	bool rxctrl_strap_quirk;
	bool set_clk_output;
	u32 clk_output_sel;
	bool sgmii_ref_clk_en;
पूर्ण;

अटल पूर्णांक dp83867_ack_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err = phy_पढ़ो(phydev, MII_DP83867_ISR);

	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक dp83867_set_wol(काष्ठा phy_device *phydev,
			   काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा net_device *ndev = phydev->attached_dev;
	u16 val_rxcfg, val_micr;
	u8 *mac;

	val_rxcfg = phy_पढ़ो_mmd(phydev, DP83867_DEVADDR, DP83867_RXFCFG);
	val_micr = phy_पढ़ो(phydev, MII_DP83867_MICR);

	अगर (wol->wolopts & (WAKE_MAGIC | WAKE_MAGICSECURE | WAKE_UCAST |
			    WAKE_BCAST)) अणु
		val_rxcfg |= DP83867_WOL_ENH_MAC;
		val_micr |= MII_DP83867_MICR_WOL_INT_EN;

		अगर (wol->wolopts & WAKE_MAGIC) अणु
			mac = (u8 *)ndev->dev_addr;

			अगर (!is_valid_ether_addr(mac))
				वापस -EINVAL;

			phy_ग_लिखो_mmd(phydev, DP83867_DEVADDR, DP83867_RXFPMD1,
				      (mac[1] << 8 | mac[0]));
			phy_ग_लिखो_mmd(phydev, DP83867_DEVADDR, DP83867_RXFPMD2,
				      (mac[3] << 8 | mac[2]));
			phy_ग_लिखो_mmd(phydev, DP83867_DEVADDR, DP83867_RXFPMD3,
				      (mac[5] << 8 | mac[4]));

			val_rxcfg |= DP83867_WOL_MAGIC_EN;
		पूर्ण अन्यथा अणु
			val_rxcfg &= ~DP83867_WOL_MAGIC_EN;
		पूर्ण

		अगर (wol->wolopts & WAKE_MAGICSECURE) अणु
			phy_ग_लिखो_mmd(phydev, DP83867_DEVADDR, DP83867_RXFSOP1,
				      (wol->sopass[1] << 8) | wol->sopass[0]);
			phy_ग_लिखो_mmd(phydev, DP83867_DEVADDR, DP83867_RXFSOP2,
				      (wol->sopass[3] << 8) | wol->sopass[2]);
			phy_ग_लिखो_mmd(phydev, DP83867_DEVADDR, DP83867_RXFSOP3,
				      (wol->sopass[5] << 8) | wol->sopass[4]);

			val_rxcfg |= DP83867_WOL_SEC_EN;
		पूर्ण अन्यथा अणु
			val_rxcfg &= ~DP83867_WOL_SEC_EN;
		पूर्ण

		अगर (wol->wolopts & WAKE_UCAST)
			val_rxcfg |= DP83867_WOL_UCAST_EN;
		अन्यथा
			val_rxcfg &= ~DP83867_WOL_UCAST_EN;

		अगर (wol->wolopts & WAKE_BCAST)
			val_rxcfg |= DP83867_WOL_BCAST_EN;
		अन्यथा
			val_rxcfg &= ~DP83867_WOL_BCAST_EN;
	पूर्ण अन्यथा अणु
		val_rxcfg &= ~DP83867_WOL_ENH_MAC;
		val_micr &= ~MII_DP83867_MICR_WOL_INT_EN;
	पूर्ण

	phy_ग_लिखो_mmd(phydev, DP83867_DEVADDR, DP83867_RXFCFG, val_rxcfg);
	phy_ग_लिखो(phydev, MII_DP83867_MICR, val_micr);

	वापस 0;
पूर्ण

अटल व्योम dp83867_get_wol(काष्ठा phy_device *phydev,
			    काष्ठा ethtool_wolinfo *wol)
अणु
	u16 value, sopass_val;

	wol->supported = (WAKE_UCAST | WAKE_BCAST | WAKE_MAGIC |
			WAKE_MAGICSECURE);
	wol->wolopts = 0;

	value = phy_पढ़ो_mmd(phydev, DP83867_DEVADDR, DP83867_RXFCFG);

	अगर (value & DP83867_WOL_UCAST_EN)
		wol->wolopts |= WAKE_UCAST;

	अगर (value & DP83867_WOL_BCAST_EN)
		wol->wolopts |= WAKE_BCAST;

	अगर (value & DP83867_WOL_MAGIC_EN)
		wol->wolopts |= WAKE_MAGIC;

	अगर (value & DP83867_WOL_SEC_EN) अणु
		sopass_val = phy_पढ़ो_mmd(phydev, DP83867_DEVADDR,
					  DP83867_RXFSOP1);
		wol->sopass[0] = (sopass_val & 0xff);
		wol->sopass[1] = (sopass_val >> 8);

		sopass_val = phy_पढ़ो_mmd(phydev, DP83867_DEVADDR,
					  DP83867_RXFSOP2);
		wol->sopass[2] = (sopass_val & 0xff);
		wol->sopass[3] = (sopass_val >> 8);

		sopass_val = phy_पढ़ो_mmd(phydev, DP83867_DEVADDR,
					  DP83867_RXFSOP3);
		wol->sopass[4] = (sopass_val & 0xff);
		wol->sopass[5] = (sopass_val >> 8);

		wol->wolopts |= WAKE_MAGICSECURE;
	पूर्ण

	अगर (!(value & DP83867_WOL_ENH_MAC))
		wol->wolopts = 0;
पूर्ण

अटल पूर्णांक dp83867_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	पूर्णांक micr_status, err;

	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED) अणु
		err = dp83867_ack_पूर्णांकerrupt(phydev);
		अगर (err)
			वापस err;

		micr_status = phy_पढ़ो(phydev, MII_DP83867_MICR);
		अगर (micr_status < 0)
			वापस micr_status;

		micr_status |=
			(MII_DP83867_MICR_AN_ERR_INT_EN |
			MII_DP83867_MICR_SPEED_CHNG_INT_EN |
			MII_DP83867_MICR_AUTONEG_COMP_INT_EN |
			MII_DP83867_MICR_LINK_STS_CHNG_INT_EN |
			MII_DP83867_MICR_DUP_MODE_CHNG_INT_EN |
			MII_DP83867_MICR_SLEEP_MODE_CHNG_INT_EN);

		err = phy_ग_लिखो(phydev, MII_DP83867_MICR, micr_status);
	पूर्ण अन्यथा अणु
		micr_status = 0x0;
		err = phy_ग_लिखो(phydev, MII_DP83867_MICR, micr_status);
		अगर (err)
			वापस err;

		err = dp83867_ack_पूर्णांकerrupt(phydev);
	पूर्ण

	वापस err;
पूर्ण

अटल irqवापस_t dp83867_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक irq_status, irq_enabled;

	irq_status = phy_पढ़ो(phydev, MII_DP83867_ISR);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	irq_enabled = phy_पढ़ो(phydev, MII_DP83867_MICR);
	अगर (irq_enabled < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	अगर (!(irq_status & irq_enabled))
		वापस IRQ_NONE;

	phy_trigger_machine(phydev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक dp83867_पढ़ो_status(काष्ठा phy_device *phydev)
अणु
	पूर्णांक status = phy_पढ़ो(phydev, MII_DP83867_PHYSTS);
	पूर्णांक ret;

	ret = genphy_पढ़ो_status(phydev);
	अगर (ret)
		वापस ret;

	अगर (status < 0)
		वापस status;

	अगर (status & DP83867_PHYSTS_DUPLEX)
		phydev->duplex = DUPLEX_FULL;
	अन्यथा
		phydev->duplex = DUPLEX_HALF;

	अगर (status & DP83867_PHYSTS_1000)
		phydev->speed = SPEED_1000;
	अन्यथा अगर (status & DP83867_PHYSTS_100)
		phydev->speed = SPEED_100;
	अन्यथा
		phydev->speed = SPEED_10;

	वापस 0;
पूर्ण

अटल पूर्णांक dp83867_get_करोwnshअगरt(काष्ठा phy_device *phydev, u8 *data)
अणु
	पूर्णांक val, cnt, enable, count;

	val = phy_पढ़ो(phydev, DP83867_CFG2);
	अगर (val < 0)
		वापस val;

	enable = FIELD_GET(DP83867_DOWNSHIFT_EN, val);
	cnt = FIELD_GET(DP83867_DOWNSHIFT_ATTEMPT_MASK, val);

	चयन (cnt) अणु
	हाल DP83867_DOWNSHIFT_1_COUNT_VAL:
		count = DP83867_DOWNSHIFT_1_COUNT;
		अवरोध;
	हाल DP83867_DOWNSHIFT_2_COUNT_VAL:
		count = DP83867_DOWNSHIFT_2_COUNT;
		अवरोध;
	हाल DP83867_DOWNSHIFT_4_COUNT_VAL:
		count = DP83867_DOWNSHIFT_4_COUNT;
		अवरोध;
	हाल DP83867_DOWNSHIFT_8_COUNT_VAL:
		count = DP83867_DOWNSHIFT_8_COUNT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	*data = enable ? count : DOWNSHIFT_DEV_DISABLE;

	वापस 0;
पूर्ण

अटल पूर्णांक dp83867_set_करोwnshअगरt(काष्ठा phy_device *phydev, u8 cnt)
अणु
	पूर्णांक val, count;

	अगर (cnt > DP83867_DOWNSHIFT_8_COUNT)
		वापस -E2BIG;

	अगर (!cnt)
		वापस phy_clear_bits(phydev, DP83867_CFG2,
				      DP83867_DOWNSHIFT_EN);

	चयन (cnt) अणु
	हाल DP83867_DOWNSHIFT_1_COUNT:
		count = DP83867_DOWNSHIFT_1_COUNT_VAL;
		अवरोध;
	हाल DP83867_DOWNSHIFT_2_COUNT:
		count = DP83867_DOWNSHIFT_2_COUNT_VAL;
		अवरोध;
	हाल DP83867_DOWNSHIFT_4_COUNT:
		count = DP83867_DOWNSHIFT_4_COUNT_VAL;
		अवरोध;
	हाल DP83867_DOWNSHIFT_8_COUNT:
		count = DP83867_DOWNSHIFT_8_COUNT_VAL;
		अवरोध;
	शेष:
		phydev_err(phydev,
			   "Downshift count must be 1, 2, 4 or 8\n");
		वापस -EINVAL;
	पूर्ण

	val = DP83867_DOWNSHIFT_EN;
	val |= FIELD_PREP(DP83867_DOWNSHIFT_ATTEMPT_MASK, count);

	वापस phy_modअगरy(phydev, DP83867_CFG2,
			  DP83867_DOWNSHIFT_EN | DP83867_DOWNSHIFT_ATTEMPT_MASK,
			  val);
पूर्ण

अटल पूर्णांक dp83867_get_tunable(काष्ठा phy_device *phydev,
			       काष्ठा ethtool_tunable *tuna, व्योम *data)
अणु
	चयन (tuna->id) अणु
	हाल ETHTOOL_PHY_DOWNSHIFT:
		वापस dp83867_get_करोwnshअगरt(phydev, data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक dp83867_set_tunable(काष्ठा phy_device *phydev,
			       काष्ठा ethtool_tunable *tuna, स्थिर व्योम *data)
अणु
	चयन (tuna->id) अणु
	हाल ETHTOOL_PHY_DOWNSHIFT:
		वापस dp83867_set_करोwnshअगरt(phydev, *(स्थिर u8 *)data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक dp83867_config_port_mirroring(काष्ठा phy_device *phydev)
अणु
	काष्ठा dp83867_निजी *dp83867 =
		(काष्ठा dp83867_निजी *)phydev->priv;

	अगर (dp83867->port_mirroring == DP83867_PORT_MIRROING_EN)
		phy_set_bits_mmd(phydev, DP83867_DEVADDR, DP83867_CFG4,
				 DP83867_CFG4_PORT_MIRROR_EN);
	अन्यथा
		phy_clear_bits_mmd(phydev, DP83867_DEVADDR, DP83867_CFG4,
				   DP83867_CFG4_PORT_MIRROR_EN);
	वापस 0;
पूर्ण

अटल पूर्णांक dp83867_verअगरy_rgmii_cfg(काष्ठा phy_device *phydev)
अणु
	काष्ठा dp83867_निजी *dp83867 = phydev->priv;

	/* Existing behavior was to use शेष pin strapping delay in rgmii
	 * mode, but rgmii should have meant no delay.  Warn existing users.
	 */
	अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII) अणु
		स्थिर u16 val = phy_पढ़ो_mmd(phydev, DP83867_DEVADDR,
					     DP83867_STRAP_STS2);
		स्थिर u16 txskew = (val & DP83867_STRAP_STS2_CLK_SKEW_TX_MASK) >>
				   DP83867_STRAP_STS2_CLK_SKEW_TX_SHIFT;
		स्थिर u16 rxskew = (val & DP83867_STRAP_STS2_CLK_SKEW_RX_MASK) >>
				   DP83867_STRAP_STS2_CLK_SKEW_RX_SHIFT;

		अगर (txskew != DP83867_STRAP_STS2_CLK_SKEW_NONE ||
		    rxskew != DP83867_STRAP_STS2_CLK_SKEW_NONE)
			phydev_warn(phydev,
				    "PHY has delays via pin strapping, but phy-mode = 'rgmii'\n"
				    "Should be 'rgmii-id' to use internal delays txskew:%x rxskew:%x\n",
				    txskew, rxskew);
	पूर्ण

	/* RX delay *must* be specअगरied अगर पूर्णांकernal delay of RX is used. */
	अगर ((phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_ID ||
	     phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_RXID) &&
	     dp83867->rx_id_delay == DP83867_RGMII_RX_CLK_DELAY_INV) अणु
		phydev_err(phydev, "ti,rx-internal-delay must be specified\n");
		वापस -EINVAL;
	पूर्ण

	/* TX delay *must* be specअगरied अगर पूर्णांकernal delay of TX is used. */
	अगर ((phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_ID ||
	     phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_TXID) &&
	     dp83867->tx_id_delay == DP83867_RGMII_TX_CLK_DELAY_INV) अणु
		phydev_err(phydev, "ti,tx-internal-delay must be specified\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_OF_MDIO)
अटल पूर्णांक dp83867_of_init(काष्ठा phy_device *phydev)
अणु
	काष्ठा dp83867_निजी *dp83867 = phydev->priv;
	काष्ठा device *dev = &phydev->mdio.dev;
	काष्ठा device_node *of_node = dev->of_node;
	पूर्णांक ret;

	अगर (!of_node)
		वापस -ENODEV;

	/* Optional configuration */
	ret = of_property_पढ़ो_u32(of_node, "ti,clk-output-sel",
				   &dp83867->clk_output_sel);
	/* If not set, keep शेष */
	अगर (!ret) अणु
		dp83867->set_clk_output = true;
		/* Valid values are 0 to DP83867_CLK_O_SEL_REF_CLK or
		 * DP83867_CLK_O_SEL_OFF.
		 */
		अगर (dp83867->clk_output_sel > DP83867_CLK_O_SEL_REF_CLK &&
		    dp83867->clk_output_sel != DP83867_CLK_O_SEL_OFF) अणु
			phydev_err(phydev, "ti,clk-output-sel value %u out of range\n",
				   dp83867->clk_output_sel);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (of_property_पढ़ो_bool(of_node, "ti,max-output-impedance"))
		dp83867->io_impedance = DP83867_IO_MUX_CFG_IO_IMPEDANCE_MAX;
	अन्यथा अगर (of_property_पढ़ो_bool(of_node, "ti,min-output-impedance"))
		dp83867->io_impedance = DP83867_IO_MUX_CFG_IO_IMPEDANCE_MIN;
	अन्यथा
		dp83867->io_impedance = -1; /* leave at शेष */

	dp83867->rxctrl_strap_quirk = of_property_पढ़ो_bool(of_node,
							    "ti,dp83867-rxctrl-strap-quirk");

	dp83867->sgmii_ref_clk_en = of_property_पढ़ो_bool(of_node,
							  "ti,sgmii-ref-clock-output-enable");

	dp83867->rx_id_delay = DP83867_RGMII_RX_CLK_DELAY_INV;
	ret = of_property_पढ़ो_u32(of_node, "ti,rx-internal-delay",
				   &dp83867->rx_id_delay);
	अगर (!ret && dp83867->rx_id_delay > DP83867_RGMII_RX_CLK_DELAY_MAX) अणु
		phydev_err(phydev,
			   "ti,rx-internal-delay value of %u out of range\n",
			   dp83867->rx_id_delay);
		वापस -EINVAL;
	पूर्ण

	dp83867->tx_id_delay = DP83867_RGMII_TX_CLK_DELAY_INV;
	ret = of_property_पढ़ो_u32(of_node, "ti,tx-internal-delay",
				   &dp83867->tx_id_delay);
	अगर (!ret && dp83867->tx_id_delay > DP83867_RGMII_TX_CLK_DELAY_MAX) अणु
		phydev_err(phydev,
			   "ti,tx-internal-delay value of %u out of range\n",
			   dp83867->tx_id_delay);
		वापस -EINVAL;
	पूर्ण

	अगर (of_property_पढ़ो_bool(of_node, "enet-phy-lane-swap"))
		dp83867->port_mirroring = DP83867_PORT_MIRROING_EN;

	अगर (of_property_पढ़ो_bool(of_node, "enet-phy-lane-no-swap"))
		dp83867->port_mirroring = DP83867_PORT_MIRROING_DIS;

	ret = of_property_पढ़ो_u32(of_node, "ti,fifo-depth",
				   &dp83867->tx_fअगरo_depth);
	अगर (ret) अणु
		ret = of_property_पढ़ो_u32(of_node, "tx-fifo-depth",
					   &dp83867->tx_fअगरo_depth);
		अगर (ret)
			dp83867->tx_fअगरo_depth =
					DP83867_PHYCR_FIFO_DEPTH_4_B_NIB;
	पूर्ण

	अगर (dp83867->tx_fअगरo_depth > DP83867_PHYCR_FIFO_DEPTH_MAX) अणु
		phydev_err(phydev, "tx-fifo-depth value %u out of range\n",
			   dp83867->tx_fअगरo_depth);
		वापस -EINVAL;
	पूर्ण

	ret = of_property_पढ़ो_u32(of_node, "rx-fifo-depth",
				   &dp83867->rx_fअगरo_depth);
	अगर (ret)
		dp83867->rx_fअगरo_depth = DP83867_PHYCR_FIFO_DEPTH_4_B_NIB;

	अगर (dp83867->rx_fअगरo_depth > DP83867_PHYCR_FIFO_DEPTH_MAX) अणु
		phydev_err(phydev, "rx-fifo-depth value %u out of range\n",
			   dp83867->rx_fअगरo_depth);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक dp83867_of_init(काष्ठा phy_device *phydev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_OF_MDIO */

अटल पूर्णांक dp83867_probe(काष्ठा phy_device *phydev)
अणु
	काष्ठा dp83867_निजी *dp83867;

	dp83867 = devm_kzalloc(&phydev->mdio.dev, माप(*dp83867),
			       GFP_KERNEL);
	अगर (!dp83867)
		वापस -ENOMEM;

	phydev->priv = dp83867;

	वापस dp83867_of_init(phydev);
पूर्ण

अटल पूर्णांक dp83867_config_init(काष्ठा phy_device *phydev)
अणु
	काष्ठा dp83867_निजी *dp83867 = phydev->priv;
	पूर्णांक ret, val, bs;
	u16 delay;

	/* Force speed optimization क्रम the PHY even अगर it strapped */
	ret = phy_modअगरy(phydev, DP83867_CFG2, DP83867_DOWNSHIFT_EN,
			 DP83867_DOWNSHIFT_EN);
	अगर (ret)
		वापस ret;

	ret = dp83867_verअगरy_rgmii_cfg(phydev);
	अगर (ret)
		वापस ret;

	/* RX_DV/RX_CTRL strapped in mode 1 or mode 2 workaround */
	अगर (dp83867->rxctrl_strap_quirk)
		phy_clear_bits_mmd(phydev, DP83867_DEVADDR, DP83867_CFG4,
				   BIT(7));

	bs = phy_पढ़ो_mmd(phydev, DP83867_DEVADDR, DP83867_STRAP_STS2);
	अगर (bs & DP83867_STRAP_STS2_STRAP_FLD) अणु
		/* When using strap to enable FLD, the ENERGY_LOST_FLD_THR will
		 * be set to 0x2. This may causes the PHY link to be unstable -
		 * the शेष value 0x1 need to be restored.
		 */
		ret = phy_modअगरy_mmd(phydev, DP83867_DEVADDR,
				     DP83867_FLD_THR_CFG,
				     DP83867_FLD_THR_CFG_ENERGY_LOST_THR_MASK,
				     0x1);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (phy_पूर्णांकerface_is_rgmii(phydev) ||
	    phydev->पूर्णांकerface == PHY_INTERFACE_MODE_SGMII) अणु
		val = phy_पढ़ो(phydev, MII_DP83867_PHYCTRL);
		अगर (val < 0)
			वापस val;

		val &= ~DP83867_PHYCR_TX_FIFO_DEPTH_MASK;
		val |= (dp83867->tx_fअगरo_depth <<
			DP83867_PHYCR_TX_FIFO_DEPTH_SHIFT);

		अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_SGMII) अणु
			val &= ~DP83867_PHYCR_RX_FIFO_DEPTH_MASK;
			val |= (dp83867->rx_fअगरo_depth <<
				DP83867_PHYCR_RX_FIFO_DEPTH_SHIFT);
		पूर्ण

		ret = phy_ग_लिखो(phydev, MII_DP83867_PHYCTRL, val);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (phy_पूर्णांकerface_is_rgmii(phydev)) अणु
		val = phy_पढ़ो(phydev, MII_DP83867_PHYCTRL);
		अगर (val < 0)
			वापस val;

		/* The code below checks अगर "port mirroring" N/A MODE4 has been
		 * enabled during घातer on bootstrap.
		 *
		 * Such N/A mode enabled by mistake can put PHY IC in some
		 * पूर्णांकernal testing mode and disable RGMII transmission.
		 *
		 * In this particular हाल one needs to check STRAP_STS1
		 * रेजिस्टर's bit 11 (marked as RESERVED).
		 */

		bs = phy_पढ़ो_mmd(phydev, DP83867_DEVADDR, DP83867_STRAP_STS1);
		अगर (bs & DP83867_STRAP_STS1_RESERVED)
			val &= ~DP83867_PHYCR_RESERVED_MASK;

		ret = phy_ग_लिखो(phydev, MII_DP83867_PHYCTRL, val);
		अगर (ret)
			वापस ret;

		/* If rgmii mode with no पूर्णांकernal delay is selected, we करो NOT use
		 * aligned mode as one might expect.  Instead we use the PHY's शेष
		 * based on pin strapping.  And the "mode 0" शेष is to *use*
		 * पूर्णांकernal delay with a value of 7 (2.00 ns).
		 *
		 * Set up RGMII delays
		 */
		val = phy_पढ़ो_mmd(phydev, DP83867_DEVADDR, DP83867_RGMIICTL);

		val &= ~(DP83867_RGMII_TX_CLK_DELAY_EN | DP83867_RGMII_RX_CLK_DELAY_EN);
		अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_ID)
			val |= (DP83867_RGMII_TX_CLK_DELAY_EN | DP83867_RGMII_RX_CLK_DELAY_EN);

		अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_TXID)
			val |= DP83867_RGMII_TX_CLK_DELAY_EN;

		अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_RXID)
			val |= DP83867_RGMII_RX_CLK_DELAY_EN;

		phy_ग_लिखो_mmd(phydev, DP83867_DEVADDR, DP83867_RGMIICTL, val);

		delay = 0;
		अगर (dp83867->rx_id_delay != DP83867_RGMII_RX_CLK_DELAY_INV)
			delay |= dp83867->rx_id_delay;
		अगर (dp83867->tx_id_delay != DP83867_RGMII_TX_CLK_DELAY_INV)
			delay |= dp83867->tx_id_delay <<
				 DP83867_RGMII_TX_CLK_DELAY_SHIFT;

		phy_ग_लिखो_mmd(phydev, DP83867_DEVADDR, DP83867_RGMIIDCTL,
			      delay);
	पूर्ण

	/* If specअगरied, set io impedance */
	अगर (dp83867->io_impedance >= 0)
		phy_modअगरy_mmd(phydev, DP83867_DEVADDR, DP83867_IO_MUX_CFG,
			       DP83867_IO_MUX_CFG_IO_IMPEDANCE_MASK,
			       dp83867->io_impedance);

	अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_SGMII) अणु
		/* For support SPEED_10 in SGMII mode
		 * DP83867_10M_SGMII_RATE_ADAPT bit
		 * has to be cleared by software. That
		 * करोes not affect SPEED_100 and
		 * SPEED_1000.
		 */
		ret = phy_modअगरy_mmd(phydev, DP83867_DEVADDR,
				     DP83867_10M_SGMII_CFG,
				     DP83867_10M_SGMII_RATE_ADAPT_MASK,
				     0);
		अगर (ret)
			वापस ret;

		/* After reset SGMII Autoneg समयr is set to 2us (bits 6 and 5
		 * are 01). That is not enough to finalize स्वतःneg on some
		 * devices. Increase this समयr duration to maximum 16ms.
		 */
		ret = phy_modअगरy_mmd(phydev, DP83867_DEVADDR,
				     DP83867_CFG4,
				     DP83867_CFG4_SGMII_ANEG_MASK,
				     DP83867_CFG4_SGMII_ANEG_TIMER_16MS);

		अगर (ret)
			वापस ret;

		val = phy_पढ़ो_mmd(phydev, DP83867_DEVADDR, DP83867_SGMIICTL);
		/* SGMII type is set to 4-wire mode by शेष.
		 * If we place appropriate property in dts (see above)
		 * चयन on 6-wire mode.
		 */
		अगर (dp83867->sgmii_ref_clk_en)
			val |= DP83867_SGMII_TYPE;
		अन्यथा
			val &= ~DP83867_SGMII_TYPE;
		phy_ग_लिखो_mmd(phydev, DP83867_DEVADDR, DP83867_SGMIICTL, val);
	पूर्ण

	val = phy_पढ़ो(phydev, DP83867_CFG3);
	/* Enable Interrupt output INT_OE in CFG3 रेजिस्टर */
	अगर (phy_पूर्णांकerrupt_is_valid(phydev))
		val |= DP83867_CFG3_INT_OE;

	val |= DP83867_CFG3_ROBUST_AUTO_MDIX;
	phy_ग_लिखो(phydev, DP83867_CFG3, val);

	अगर (dp83867->port_mirroring != DP83867_PORT_MIRROING_KEEP)
		dp83867_config_port_mirroring(phydev);

	/* Clock output selection अगर muxing property is set */
	अगर (dp83867->set_clk_output) अणु
		u16 mask = DP83867_IO_MUX_CFG_CLK_O_DISABLE;

		अगर (dp83867->clk_output_sel == DP83867_CLK_O_SEL_OFF) अणु
			val = DP83867_IO_MUX_CFG_CLK_O_DISABLE;
		पूर्ण अन्यथा अणु
			mask |= DP83867_IO_MUX_CFG_CLK_O_SEL_MASK;
			val = dp83867->clk_output_sel <<
			      DP83867_IO_MUX_CFG_CLK_O_SEL_SHIFT;
		पूर्ण

		phy_modअगरy_mmd(phydev, DP83867_DEVADDR, DP83867_IO_MUX_CFG,
			       mask, val);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dp83867_phy_reset(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	err = phy_ग_लिखो(phydev, DP83867_CTRL, DP83867_SW_RESTART);
	अगर (err < 0)
		वापस err;

	usleep_range(10, 20);

	वापस phy_modअगरy(phydev, MII_DP83867_PHYCTRL,
			 DP83867_PHYCR_FORCE_LINK_GOOD, 0);
पूर्ण

अटल काष्ठा phy_driver dp83867_driver[] = अणु
	अणु
		.phy_id		= DP83867_PHY_ID,
		.phy_id_mask	= 0xfffffff0,
		.name		= "TI DP83867",
		/* PHY_GBIT_FEATURES */

		.probe          = dp83867_probe,
		.config_init	= dp83867_config_init,
		.soft_reset	= dp83867_phy_reset,

		.पढ़ो_status	= dp83867_पढ़ो_status,
		.get_tunable	= dp83867_get_tunable,
		.set_tunable	= dp83867_set_tunable,

		.get_wol	= dp83867_get_wol,
		.set_wol	= dp83867_set_wol,

		/* IRQ related */
		.config_पूर्णांकr	= dp83867_config_पूर्णांकr,
		.handle_पूर्णांकerrupt = dp83867_handle_पूर्णांकerrupt,

		.suspend	= genphy_suspend,
		.resume		= genphy_resume,
	पूर्ण,
पूर्ण;
module_phy_driver(dp83867_driver);

अटल काष्ठा mdio_device_id __maybe_unused dp83867_tbl[] = अणु
	अणु DP83867_PHY_ID, 0xfffffff0 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(mdio, dp83867_tbl);

MODULE_DESCRIPTION("Texas Instruments DP83867 PHY driver");
MODULE_AUTHOR("Dan Murphy <dmurphy@ti.com");
MODULE_LICENSE("GPL v2");
