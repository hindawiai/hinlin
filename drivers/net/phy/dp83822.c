<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Driver क्रम the Texas Instruments DP83822, DP83825 and DP83826 PHYs.
 *
 * Copyright (C) 2017 Texas Instruments Inc.
 */

#समावेश <linux/ethtool.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mii.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/phy.h>
#समावेश <linux/netdevice.h>

#घोषणा DP83822_PHY_ID	        0x2000a240
#घोषणा DP83825S_PHY_ID		0x2000a140
#घोषणा DP83825I_PHY_ID		0x2000a150
#घोषणा DP83825CM_PHY_ID	0x2000a160
#घोषणा DP83825CS_PHY_ID	0x2000a170
#घोषणा DP83826C_PHY_ID		0x2000a130
#घोषणा DP83826NC_PHY_ID	0x2000a110

#घोषणा DP83822_DEVADDR		0x1f

#घोषणा MII_DP83822_CTRL_2	0x0a
#घोषणा MII_DP83822_PHYSTS	0x10
#घोषणा MII_DP83822_PHYSCR	0x11
#घोषणा MII_DP83822_MISR1	0x12
#घोषणा MII_DP83822_MISR2	0x13
#घोषणा MII_DP83822_FCSCR	0x14
#घोषणा MII_DP83822_RCSR	0x17
#घोषणा MII_DP83822_RESET_CTRL	0x1f
#घोषणा MII_DP83822_GENCFG	0x465
#घोषणा MII_DP83822_SOR1	0x467

/* GENCFG */
#घोषणा DP83822_SIG_DET_LOW	BIT(0)

/* Control Register 2 bits */
#घोषणा DP83822_FX_ENABLE	BIT(14)

#घोषणा DP83822_HW_RESET	BIT(15)
#घोषणा DP83822_SW_RESET	BIT(14)

/* PHY STS bits */
#घोषणा DP83822_PHYSTS_DUPLEX			BIT(2)
#घोषणा DP83822_PHYSTS_10			BIT(1)
#घोषणा DP83822_PHYSTS_LINK			BIT(0)

/* PHYSCR Register Fields */
#घोषणा DP83822_PHYSCR_INT_OE		BIT(0) /* Interrupt Output Enable */
#घोषणा DP83822_PHYSCR_INTEN		BIT(1) /* Interrupt Enable */

/* MISR1 bits */
#घोषणा DP83822_RX_ERR_HF_INT_EN	BIT(0)
#घोषणा DP83822_FALSE_CARRIER_HF_INT_EN	BIT(1)
#घोषणा DP83822_ANEG_COMPLETE_INT_EN	BIT(2)
#घोषणा DP83822_DUP_MODE_CHANGE_INT_EN	BIT(3)
#घोषणा DP83822_SPEED_CHANGED_INT_EN	BIT(4)
#घोषणा DP83822_LINK_STAT_INT_EN	BIT(5)
#घोषणा DP83822_ENERGY_DET_INT_EN	BIT(6)
#घोषणा DP83822_LINK_QUAL_INT_EN	BIT(7)

/* MISR2 bits */
#घोषणा DP83822_JABBER_DET_INT_EN	BIT(0)
#घोषणा DP83822_WOL_PKT_INT_EN		BIT(1)
#घोषणा DP83822_SLEEP_MODE_INT_EN	BIT(2)
#घोषणा DP83822_MDI_XOVER_INT_EN	BIT(3)
#घोषणा DP83822_LB_FIFO_INT_EN		BIT(4)
#घोषणा DP83822_PAGE_RX_INT_EN		BIT(5)
#घोषणा DP83822_ANEG_ERR_INT_EN		BIT(6)
#घोषणा DP83822_EEE_ERROR_CHANGE_INT_EN	BIT(7)

/* INT_STAT1 bits */
#घोषणा DP83822_WOL_INT_EN	BIT(4)
#घोषणा DP83822_WOL_INT_STAT	BIT(12)

#घोषणा MII_DP83822_RXSOP1	0x04a5
#घोषणा	MII_DP83822_RXSOP2	0x04a6
#घोषणा	MII_DP83822_RXSOP3	0x04a7

/* WoL Registers */
#घोषणा	MII_DP83822_WOL_CFG	0x04a0
#घोषणा	MII_DP83822_WOL_STAT	0x04a1
#घोषणा	MII_DP83822_WOL_DA1	0x04a2
#घोषणा	MII_DP83822_WOL_DA2	0x04a3
#घोषणा	MII_DP83822_WOL_DA3	0x04a4

/* WoL bits */
#घोषणा DP83822_WOL_MAGIC_EN	BIT(0)
#घोषणा DP83822_WOL_SECURE_ON	BIT(5)
#घोषणा DP83822_WOL_EN		BIT(7)
#घोषणा DP83822_WOL_INDICATION_SEL BIT(8)
#घोषणा DP83822_WOL_CLR_INDICATION BIT(11)

/* RSCR bits */
#घोषणा DP83822_RX_CLK_SHIFT	BIT(12)
#घोषणा DP83822_TX_CLK_SHIFT	BIT(11)

/* SOR1 mode */
#घोषणा DP83822_STRAP_MODE1	0
#घोषणा DP83822_STRAP_MODE2	BIT(0)
#घोषणा DP83822_STRAP_MODE3	BIT(1)
#घोषणा DP83822_STRAP_MODE4	GENMASK(1, 0)

#घोषणा DP83822_COL_STRAP_MASK	GENMASK(11, 10)
#घोषणा DP83822_COL_SHIFT	10
#घोषणा DP83822_RX_ER_STR_MASK	GENMASK(9, 8)
#घोषणा DP83822_RX_ER_SHIFT	8

#घोषणा MII_DP83822_FIBER_ADVERTISE    (ADVERTISED_TP | ADVERTISED_MII | \
					ADVERTISED_FIBRE | \
					ADVERTISED_Pause | ADVERTISED_Asym_Pause)

काष्ठा dp83822_निजी अणु
	bool fx_संकेत_det_low;
	पूर्णांक fx_enabled;
	u16 fx_sd_enable;
पूर्ण;

अटल पूर्णांक dp83822_set_wol(काष्ठा phy_device *phydev,
			   काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा net_device *ndev = phydev->attached_dev;
	u16 value;
	स्थिर u8 *mac;

	अगर (wol->wolopts & (WAKE_MAGIC | WAKE_MAGICSECURE)) अणु
		mac = (स्थिर u8 *)ndev->dev_addr;

		अगर (!is_valid_ether_addr(mac))
			वापस -EINVAL;

		/* MAC addresses start with byte 5, but stored in mac[0].
		 * 822 PHYs store bytes 4|5, 2|3, 0|1
		 */
		phy_ग_लिखो_mmd(phydev, DP83822_DEVADDR, MII_DP83822_WOL_DA1,
			      (mac[1] << 8) | mac[0]);
		phy_ग_लिखो_mmd(phydev, DP83822_DEVADDR, MII_DP83822_WOL_DA2,
			      (mac[3] << 8) | mac[2]);
		phy_ग_लिखो_mmd(phydev, DP83822_DEVADDR, MII_DP83822_WOL_DA3,
			      (mac[5] << 8) | mac[4]);

		value = phy_पढ़ो_mmd(phydev, DP83822_DEVADDR,
				     MII_DP83822_WOL_CFG);
		अगर (wol->wolopts & WAKE_MAGIC)
			value |= DP83822_WOL_MAGIC_EN;
		अन्यथा
			value &= ~DP83822_WOL_MAGIC_EN;

		अगर (wol->wolopts & WAKE_MAGICSECURE) अणु
			phy_ग_लिखो_mmd(phydev, DP83822_DEVADDR,
				      MII_DP83822_RXSOP1,
				      (wol->sopass[1] << 8) | wol->sopass[0]);
			phy_ग_लिखो_mmd(phydev, DP83822_DEVADDR,
				      MII_DP83822_RXSOP2,
				      (wol->sopass[3] << 8) | wol->sopass[2]);
			phy_ग_लिखो_mmd(phydev, DP83822_DEVADDR,
				      MII_DP83822_RXSOP3,
				      (wol->sopass[5] << 8) | wol->sopass[4]);
			value |= DP83822_WOL_SECURE_ON;
		पूर्ण अन्यथा अणु
			value &= ~DP83822_WOL_SECURE_ON;
		पूर्ण

		/* Clear any pending WoL पूर्णांकerrupt */
		phy_पढ़ो(phydev, MII_DP83822_MISR2);

		value |= DP83822_WOL_EN | DP83822_WOL_INDICATION_SEL |
			 DP83822_WOL_CLR_INDICATION;

		वापस phy_ग_लिखो_mmd(phydev, DP83822_DEVADDR,
				     MII_DP83822_WOL_CFG, value);
	पूर्ण अन्यथा अणु
		वापस phy_clear_bits_mmd(phydev, DP83822_DEVADDR,
					  MII_DP83822_WOL_CFG, DP83822_WOL_EN);
	पूर्ण
पूर्ण

अटल व्योम dp83822_get_wol(काष्ठा phy_device *phydev,
			    काष्ठा ethtool_wolinfo *wol)
अणु
	पूर्णांक value;
	u16 sopass_val;

	wol->supported = (WAKE_MAGIC | WAKE_MAGICSECURE);
	wol->wolopts = 0;

	value = phy_पढ़ो_mmd(phydev, DP83822_DEVADDR, MII_DP83822_WOL_CFG);

	अगर (value & DP83822_WOL_MAGIC_EN)
		wol->wolopts |= WAKE_MAGIC;

	अगर (value & DP83822_WOL_SECURE_ON) अणु
		sopass_val = phy_पढ़ो_mmd(phydev, DP83822_DEVADDR,
					  MII_DP83822_RXSOP1);
		wol->sopass[0] = (sopass_val & 0xff);
		wol->sopass[1] = (sopass_val >> 8);

		sopass_val = phy_पढ़ो_mmd(phydev, DP83822_DEVADDR,
					  MII_DP83822_RXSOP2);
		wol->sopass[2] = (sopass_val & 0xff);
		wol->sopass[3] = (sopass_val >> 8);

		sopass_val = phy_पढ़ो_mmd(phydev, DP83822_DEVADDR,
					  MII_DP83822_RXSOP3);
		wol->sopass[4] = (sopass_val & 0xff);
		wol->sopass[5] = (sopass_val >> 8);

		wol->wolopts |= WAKE_MAGICSECURE;
	पूर्ण

	/* WoL is not enabled so set wolopts to 0 */
	अगर (!(value & DP83822_WOL_EN))
		wol->wolopts = 0;
पूर्ण

अटल पूर्णांक dp83822_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	काष्ठा dp83822_निजी *dp83822 = phydev->priv;
	पूर्णांक misr_status;
	पूर्णांक physcr_status;
	पूर्णांक err;

	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED) अणु
		misr_status = phy_पढ़ो(phydev, MII_DP83822_MISR1);
		अगर (misr_status < 0)
			वापस misr_status;

		misr_status |= (DP83822_RX_ERR_HF_INT_EN |
				DP83822_FALSE_CARRIER_HF_INT_EN |
				DP83822_LINK_STAT_INT_EN |
				DP83822_ENERGY_DET_INT_EN |
				DP83822_LINK_QUAL_INT_EN);

		अगर (!dp83822->fx_enabled)
			misr_status |= DP83822_ANEG_COMPLETE_INT_EN |
				       DP83822_DUP_MODE_CHANGE_INT_EN |
				       DP83822_SPEED_CHANGED_INT_EN;


		err = phy_ग_लिखो(phydev, MII_DP83822_MISR1, misr_status);
		अगर (err < 0)
			वापस err;

		misr_status = phy_पढ़ो(phydev, MII_DP83822_MISR2);
		अगर (misr_status < 0)
			वापस misr_status;

		misr_status |= (DP83822_JABBER_DET_INT_EN |
				DP83822_SLEEP_MODE_INT_EN |
				DP83822_LB_FIFO_INT_EN |
				DP83822_PAGE_RX_INT_EN |
				DP83822_EEE_ERROR_CHANGE_INT_EN);

		अगर (!dp83822->fx_enabled)
			misr_status |= DP83822_MDI_XOVER_INT_EN |
				       DP83822_ANEG_ERR_INT_EN |
				       DP83822_WOL_PKT_INT_EN;

		err = phy_ग_लिखो(phydev, MII_DP83822_MISR2, misr_status);
		अगर (err < 0)
			वापस err;

		physcr_status = phy_पढ़ो(phydev, MII_DP83822_PHYSCR);
		अगर (physcr_status < 0)
			वापस physcr_status;

		physcr_status |= DP83822_PHYSCR_INT_OE | DP83822_PHYSCR_INTEN;

	पूर्ण अन्यथा अणु
		err = phy_ग_लिखो(phydev, MII_DP83822_MISR1, 0);
		अगर (err < 0)
			वापस err;

		err = phy_ग_लिखो(phydev, MII_DP83822_MISR1, 0);
		अगर (err < 0)
			वापस err;

		physcr_status = phy_पढ़ो(phydev, MII_DP83822_PHYSCR);
		अगर (physcr_status < 0)
			वापस physcr_status;

		physcr_status &= ~DP83822_PHYSCR_INTEN;
	पूर्ण

	वापस phy_ग_लिखो(phydev, MII_DP83822_PHYSCR, physcr_status);
पूर्ण

अटल irqवापस_t dp83822_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	bool trigger_machine = false;
	पूर्णांक irq_status;

	/* The MISR1 and MISR2 रेजिस्टरs are holding the पूर्णांकerrupt status in
	 * the upper half (15:8), जबतक the lower half (7:0) is used क्रम
	 * controlling the पूर्णांकerrupt enable state of those inभागidual पूर्णांकerrupt
	 * sources. To determine the possible पूर्णांकerrupt sources, just पढ़ो the
	 * MISR* रेजिस्टर and use it directly to know which पूर्णांकerrupts have
	 * been enabled previously or not.
	 */
	irq_status = phy_पढ़ो(phydev, MII_DP83822_MISR1);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण
	अगर (irq_status & ((irq_status & GENMASK(7, 0)) << 8))
		trigger_machine = true;

	irq_status = phy_पढ़ो(phydev, MII_DP83822_MISR2);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण
	अगर (irq_status & ((irq_status & GENMASK(7, 0)) << 8))
		trigger_machine = true;

	अगर (!trigger_machine)
		वापस IRQ_NONE;

	phy_trigger_machine(phydev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक dp8382x_disable_wol(काष्ठा phy_device *phydev)
अणु
	पूर्णांक value = DP83822_WOL_EN | DP83822_WOL_MAGIC_EN |
		    DP83822_WOL_SECURE_ON;

	वापस phy_clear_bits_mmd(phydev, DP83822_DEVADDR,
				  MII_DP83822_WOL_CFG, value);
पूर्ण

अटल पूर्णांक dp83822_पढ़ो_status(काष्ठा phy_device *phydev)
अणु
	काष्ठा dp83822_निजी *dp83822 = phydev->priv;
	पूर्णांक status = phy_पढ़ो(phydev, MII_DP83822_PHYSTS);
	पूर्णांक ctrl2;
	पूर्णांक ret;

	अगर (dp83822->fx_enabled) अणु
		अगर (status & DP83822_PHYSTS_LINK) अणु
			phydev->speed = SPEED_UNKNOWN;
			phydev->duplex = DUPLEX_UNKNOWN;
		पूर्ण अन्यथा अणु
			ctrl2 = phy_पढ़ो(phydev, MII_DP83822_CTRL_2);
			अगर (ctrl2 < 0)
				वापस ctrl2;

			अगर (!(ctrl2 & DP83822_FX_ENABLE)) अणु
				ret = phy_ग_लिखो(phydev, MII_DP83822_CTRL_2,
						DP83822_FX_ENABLE | ctrl2);
				अगर (ret < 0)
					वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	ret = genphy_पढ़ो_status(phydev);
	अगर (ret)
		वापस ret;

	अगर (status < 0)
		वापस status;

	अगर (status & DP83822_PHYSTS_DUPLEX)
		phydev->duplex = DUPLEX_FULL;
	अन्यथा
		phydev->duplex = DUPLEX_HALF;

	अगर (status & DP83822_PHYSTS_10)
		phydev->speed = SPEED_10;
	अन्यथा
		phydev->speed = SPEED_100;

	वापस 0;
पूर्ण

अटल पूर्णांक dp83822_config_init(काष्ठा phy_device *phydev)
अणु
	काष्ठा dp83822_निजी *dp83822 = phydev->priv;
	काष्ठा device *dev = &phydev->mdio.dev;
	पूर्णांक rgmii_delay;
	s32 rx_पूर्णांक_delay;
	s32 tx_पूर्णांक_delay;
	पूर्णांक err = 0;
	पूर्णांक bmcr;

	अगर (phy_पूर्णांकerface_is_rgmii(phydev)) अणु
		rx_पूर्णांक_delay = phy_get_पूर्णांकernal_delay(phydev, dev, शून्य, 0,
						      true);

		अगर (rx_पूर्णांक_delay <= 0)
			rgmii_delay = 0;
		अन्यथा
			rgmii_delay = DP83822_RX_CLK_SHIFT;

		tx_पूर्णांक_delay = phy_get_पूर्णांकernal_delay(phydev, dev, शून्य, 0,
						      false);
		अगर (tx_पूर्णांक_delay <= 0)
			rgmii_delay &= ~DP83822_TX_CLK_SHIFT;
		अन्यथा
			rgmii_delay |= DP83822_TX_CLK_SHIFT;

		अगर (rgmii_delay) अणु
			err = phy_set_bits_mmd(phydev, DP83822_DEVADDR,
					       MII_DP83822_RCSR, rgmii_delay);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	अगर (dp83822->fx_enabled) अणु
		err = phy_modअगरy(phydev, MII_DP83822_CTRL_2,
				 DP83822_FX_ENABLE, 1);
		अगर (err < 0)
			वापस err;

		/* Only allow advertising what this PHY supports */
		linkmode_and(phydev->advertising, phydev->advertising,
			     phydev->supported);

		linkmode_set_bit(ETHTOOL_LINK_MODE_FIBRE_BIT,
				 phydev->supported);
		linkmode_set_bit(ETHTOOL_LINK_MODE_FIBRE_BIT,
				 phydev->advertising);
		linkmode_set_bit(ETHTOOL_LINK_MODE_100baseFX_Full_BIT,
				 phydev->supported);
		linkmode_set_bit(ETHTOOL_LINK_MODE_100baseFX_Half_BIT,
				 phydev->supported);
		linkmode_set_bit(ETHTOOL_LINK_MODE_100baseFX_Full_BIT,
				 phydev->advertising);
		linkmode_set_bit(ETHTOOL_LINK_MODE_100baseFX_Half_BIT,
				 phydev->advertising);

		/* Auto neg is not supported in fiber mode */
		bmcr = phy_पढ़ो(phydev, MII_BMCR);
		अगर (bmcr < 0)
			वापस bmcr;

		अगर (bmcr & BMCR_ANENABLE) अणु
			err =  phy_modअगरy(phydev, MII_BMCR, BMCR_ANENABLE, 0);
			अगर (err < 0)
				वापस err;
		पूर्ण
		phydev->स्वतःneg = AUTONEG_DISABLE;
		linkmode_clear_bit(ETHTOOL_LINK_MODE_Autoneg_BIT,
				   phydev->supported);
		linkmode_clear_bit(ETHTOOL_LINK_MODE_Autoneg_BIT,
				   phydev->advertising);

		/* Setup fiber advertisement */
		err = phy_modअगरy_changed(phydev, MII_ADVERTISE,
					 MII_DP83822_FIBER_ADVERTISE,
					 MII_DP83822_FIBER_ADVERTISE);

		अगर (err < 0)
			वापस err;

		अगर (dp83822->fx_संकेत_det_low) अणु
			err = phy_set_bits_mmd(phydev, DP83822_DEVADDR,
					       MII_DP83822_GENCFG,
					       DP83822_SIG_DET_LOW);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण
	वापस dp8382x_disable_wol(phydev);
पूर्ण

अटल पूर्णांक dp8382x_config_init(काष्ठा phy_device *phydev)
अणु
	वापस dp8382x_disable_wol(phydev);
पूर्ण

अटल पूर्णांक dp83822_phy_reset(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	err = phy_ग_लिखो(phydev, MII_DP83822_RESET_CTRL, DP83822_SW_RESET);
	अगर (err < 0)
		वापस err;

	वापस phydev->drv->config_init(phydev);
पूर्ण

#अगर_घोषित CONFIG_OF_MDIO
अटल पूर्णांक dp83822_of_init(काष्ठा phy_device *phydev)
अणु
	काष्ठा dp83822_निजी *dp83822 = phydev->priv;
	काष्ठा device *dev = &phydev->mdio.dev;

	/* Signal detection क्रम the PHY is only enabled अगर the FX_EN and the
	 * SD_EN pins are strapped. Signal detection can only enabled अगर FX_EN
	 * is strapped otherwise संकेत detection is disabled क्रम the PHY.
	 */
	अगर (dp83822->fx_enabled && dp83822->fx_sd_enable)
		dp83822->fx_संकेत_det_low = device_property_present(dev,
								     "ti,link-loss-low");
	अगर (!dp83822->fx_enabled)
		dp83822->fx_enabled = device_property_present(dev,
							      "ti,fiber-mode");

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक dp83822_of_init(काष्ठा phy_device *phydev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_OF_MDIO */

अटल पूर्णांक dp83822_पढ़ो_straps(काष्ठा phy_device *phydev)
अणु
	काष्ठा dp83822_निजी *dp83822 = phydev->priv;
	पूर्णांक fx_enabled, fx_sd_enable;
	पूर्णांक val;

	val = phy_पढ़ो_mmd(phydev, DP83822_DEVADDR, MII_DP83822_SOR1);
	अगर (val < 0)
		वापस val;

	fx_enabled = (val & DP83822_COL_STRAP_MASK) >> DP83822_COL_SHIFT;
	अगर (fx_enabled == DP83822_STRAP_MODE2 ||
	    fx_enabled == DP83822_STRAP_MODE3)
		dp83822->fx_enabled = 1;

	अगर (dp83822->fx_enabled) अणु
		fx_sd_enable = (val & DP83822_RX_ER_STR_MASK) >> DP83822_RX_ER_SHIFT;
		अगर (fx_sd_enable == DP83822_STRAP_MODE3 ||
		    fx_sd_enable == DP83822_STRAP_MODE4)
			dp83822->fx_sd_enable = 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dp83822_probe(काष्ठा phy_device *phydev)
अणु
	काष्ठा dp83822_निजी *dp83822;
	पूर्णांक ret;

	dp83822 = devm_kzalloc(&phydev->mdio.dev, माप(*dp83822),
			       GFP_KERNEL);
	अगर (!dp83822)
		वापस -ENOMEM;

	phydev->priv = dp83822;

	ret = dp83822_पढ़ो_straps(phydev);
	अगर (ret)
		वापस ret;

	dp83822_of_init(phydev);

	अगर (dp83822->fx_enabled)
		phydev->port = PORT_FIBRE;

	वापस 0;
पूर्ण

अटल पूर्णांक dp83822_suspend(काष्ठा phy_device *phydev)
अणु
	पूर्णांक value;

	value = phy_पढ़ो_mmd(phydev, DP83822_DEVADDR, MII_DP83822_WOL_CFG);

	अगर (!(value & DP83822_WOL_EN))
		genphy_suspend(phydev);

	वापस 0;
पूर्ण

अटल पूर्णांक dp83822_resume(काष्ठा phy_device *phydev)
अणु
	पूर्णांक value;

	genphy_resume(phydev);

	value = phy_पढ़ो_mmd(phydev, DP83822_DEVADDR, MII_DP83822_WOL_CFG);

	phy_ग_लिखो_mmd(phydev, DP83822_DEVADDR, MII_DP83822_WOL_CFG, value |
		      DP83822_WOL_CLR_INDICATION);

	वापस 0;
पूर्ण

#घोषणा DP83822_PHY_DRIVER(_id, _name)				\
	अणु							\
		PHY_ID_MATCH_MODEL(_id),			\
		.name		= (_name),			\
		/* PHY_BASIC_FEATURES */			\
		.probe          = dp83822_probe,		\
		.soft_reset	= dp83822_phy_reset,		\
		.config_init	= dp83822_config_init,		\
		.पढ़ो_status	= dp83822_पढ़ो_status,		\
		.get_wol = dp83822_get_wol,			\
		.set_wol = dp83822_set_wol,			\
		.config_पूर्णांकr = dp83822_config_पूर्णांकr,		\
		.handle_पूर्णांकerrupt = dp83822_handle_पूर्णांकerrupt,	\
		.suspend = dp83822_suspend,			\
		.resume = dp83822_resume,			\
	पूर्ण

#घोषणा DP8382X_PHY_DRIVER(_id, _name)				\
	अणु							\
		PHY_ID_MATCH_MODEL(_id),			\
		.name		= (_name),			\
		/* PHY_BASIC_FEATURES */			\
		.soft_reset	= dp83822_phy_reset,		\
		.config_init	= dp8382x_config_init,		\
		.get_wol = dp83822_get_wol,			\
		.set_wol = dp83822_set_wol,			\
		.config_पूर्णांकr = dp83822_config_पूर्णांकr,		\
		.handle_पूर्णांकerrupt = dp83822_handle_पूर्णांकerrupt,	\
		.suspend = dp83822_suspend,			\
		.resume = dp83822_resume,			\
	पूर्ण

अटल काष्ठा phy_driver dp83822_driver[] = अणु
	DP83822_PHY_DRIVER(DP83822_PHY_ID, "TI DP83822"),
	DP8382X_PHY_DRIVER(DP83825I_PHY_ID, "TI DP83825I"),
	DP8382X_PHY_DRIVER(DP83826C_PHY_ID, "TI DP83826C"),
	DP8382X_PHY_DRIVER(DP83826NC_PHY_ID, "TI DP83826NC"),
	DP8382X_PHY_DRIVER(DP83825S_PHY_ID, "TI DP83825S"),
	DP8382X_PHY_DRIVER(DP83825CM_PHY_ID, "TI DP83825M"),
	DP8382X_PHY_DRIVER(DP83825CS_PHY_ID, "TI DP83825CS"),
पूर्ण;
module_phy_driver(dp83822_driver);

अटल काष्ठा mdio_device_id __maybe_unused dp83822_tbl[] = अणु
	अणु DP83822_PHY_ID, 0xfffffff0 पूर्ण,
	अणु DP83825I_PHY_ID, 0xfffffff0 पूर्ण,
	अणु DP83826C_PHY_ID, 0xfffffff0 पूर्ण,
	अणु DP83826NC_PHY_ID, 0xfffffff0 पूर्ण,
	अणु DP83825S_PHY_ID, 0xfffffff0 पूर्ण,
	अणु DP83825CM_PHY_ID, 0xfffffff0 पूर्ण,
	अणु DP83825CS_PHY_ID, 0xfffffff0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(mdio, dp83822_tbl);

MODULE_DESCRIPTION("Texas Instruments DP83822 PHY driver");
MODULE_AUTHOR("Dan Murphy <dmurphy@ti.com");
MODULE_LICENSE("GPL v2");
