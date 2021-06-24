<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम the Texas Instruments DP83TC811 PHY
 *
 * Copyright (C) 2018 Texas Instruments Incorporated - http://www.ti.com/
 *
 */

#समावेश <linux/ethtool.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mii.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/phy.h>
#समावेश <linux/netdevice.h>

#घोषणा DP83TC811_PHY_ID	0x2000a253
#घोषणा DP83811_DEVADDR		0x1f

#घोषणा MII_DP83811_SGMII_CTRL	0x09
#घोषणा MII_DP83811_INT_STAT1	0x12
#घोषणा MII_DP83811_INT_STAT2	0x13
#घोषणा MII_DP83811_INT_STAT3	0x18
#घोषणा MII_DP83811_RESET_CTRL	0x1f

#घोषणा DP83811_HW_RESET	BIT(15)
#घोषणा DP83811_SW_RESET	BIT(14)

/* INT_STAT1 bits */
#घोषणा DP83811_RX_ERR_HF_INT_EN	BIT(0)
#घोषणा DP83811_MS_TRAINING_INT_EN	BIT(1)
#घोषणा DP83811_ANEG_COMPLETE_INT_EN	BIT(2)
#घोषणा DP83811_ESD_EVENT_INT_EN	BIT(3)
#घोषणा DP83811_WOL_INT_EN		BIT(4)
#घोषणा DP83811_LINK_STAT_INT_EN	BIT(5)
#घोषणा DP83811_ENERGY_DET_INT_EN	BIT(6)
#घोषणा DP83811_LINK_QUAL_INT_EN	BIT(7)

/* INT_STAT2 bits */
#घोषणा DP83811_JABBER_DET_INT_EN	BIT(0)
#घोषणा DP83811_POLARITY_INT_EN		BIT(1)
#घोषणा DP83811_SLEEP_MODE_INT_EN	BIT(2)
#घोषणा DP83811_OVERTEMP_INT_EN		BIT(3)
#घोषणा DP83811_OVERVOLTAGE_INT_EN	BIT(6)
#घोषणा DP83811_UNDERVOLTAGE_INT_EN	BIT(7)

/* INT_STAT3 bits */
#घोषणा DP83811_LPS_INT_EN	BIT(0)
#घोषणा DP83811_NO_FRAME_INT_EN	BIT(3)
#घोषणा DP83811_POR_DONE_INT_EN	BIT(4)

#घोषणा MII_DP83811_RXSOP1	0x04a5
#घोषणा MII_DP83811_RXSOP2	0x04a6
#घोषणा MII_DP83811_RXSOP3	0x04a7

/* WoL Registers */
#घोषणा MII_DP83811_WOL_CFG	0x04a0
#घोषणा MII_DP83811_WOL_STAT	0x04a1
#घोषणा MII_DP83811_WOL_DA1	0x04a2
#घोषणा MII_DP83811_WOL_DA2	0x04a3
#घोषणा MII_DP83811_WOL_DA3	0x04a4

/* WoL bits */
#घोषणा DP83811_WOL_MAGIC_EN	BIT(0)
#घोषणा DP83811_WOL_SECURE_ON	BIT(5)
#घोषणा DP83811_WOL_EN		BIT(7)
#घोषणा DP83811_WOL_INDICATION_SEL BIT(8)
#घोषणा DP83811_WOL_CLR_INDICATION BIT(11)

/* SGMII CTRL bits */
#घोषणा DP83811_TDR_AUTO		BIT(8)
#घोषणा DP83811_SGMII_EN		BIT(12)
#घोषणा DP83811_SGMII_AUTO_NEG_EN	BIT(13)
#घोषणा DP83811_SGMII_TX_ERR_DIS	BIT(14)
#घोषणा DP83811_SGMII_SOFT_RESET	BIT(15)

अटल पूर्णांक dp83811_ack_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	err = phy_पढ़ो(phydev, MII_DP83811_INT_STAT1);
	अगर (err < 0)
		वापस err;

	err = phy_पढ़ो(phydev, MII_DP83811_INT_STAT2);
	अगर (err < 0)
		वापस err;

	err = phy_पढ़ो(phydev, MII_DP83811_INT_STAT3);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक dp83811_set_wol(काष्ठा phy_device *phydev,
			   काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा net_device *ndev = phydev->attached_dev;
	स्थिर u8 *mac;
	u16 value;

	अगर (wol->wolopts & (WAKE_MAGIC | WAKE_MAGICSECURE)) अणु
		mac = (स्थिर u8 *)ndev->dev_addr;

		अगर (!is_valid_ether_addr(mac))
			वापस -EINVAL;

		/* MAC addresses start with byte 5, but stored in mac[0].
		 * 811 PHYs store bytes 4|5, 2|3, 0|1
		 */
		phy_ग_लिखो_mmd(phydev, DP83811_DEVADDR, MII_DP83811_WOL_DA1,
			      (mac[1] << 8) | mac[0]);
		phy_ग_लिखो_mmd(phydev, DP83811_DEVADDR, MII_DP83811_WOL_DA2,
			      (mac[3] << 8) | mac[2]);
		phy_ग_लिखो_mmd(phydev, DP83811_DEVADDR, MII_DP83811_WOL_DA3,
			      (mac[5] << 8) | mac[4]);

		value = phy_पढ़ो_mmd(phydev, DP83811_DEVADDR,
				     MII_DP83811_WOL_CFG);
		अगर (wol->wolopts & WAKE_MAGIC)
			value |= DP83811_WOL_MAGIC_EN;
		अन्यथा
			value &= ~DP83811_WOL_MAGIC_EN;

		अगर (wol->wolopts & WAKE_MAGICSECURE) अणु
			phy_ग_लिखो_mmd(phydev, DP83811_DEVADDR,
				      MII_DP83811_RXSOP1,
				      (wol->sopass[1] << 8) | wol->sopass[0]);
			phy_ग_लिखो_mmd(phydev, DP83811_DEVADDR,
				      MII_DP83811_RXSOP2,
				      (wol->sopass[3] << 8) | wol->sopass[2]);
			phy_ग_लिखो_mmd(phydev, DP83811_DEVADDR,
				      MII_DP83811_RXSOP3,
				      (wol->sopass[5] << 8) | wol->sopass[4]);
			value |= DP83811_WOL_SECURE_ON;
		पूर्ण अन्यथा अणु
			value &= ~DP83811_WOL_SECURE_ON;
		पूर्ण

		/* Clear any pending WoL पूर्णांकerrupt */
		phy_पढ़ो(phydev, MII_DP83811_INT_STAT1);

		value |= DP83811_WOL_EN | DP83811_WOL_INDICATION_SEL |
			 DP83811_WOL_CLR_INDICATION;

		वापस phy_ग_लिखो_mmd(phydev, DP83811_DEVADDR,
				     MII_DP83811_WOL_CFG, value);
	पूर्ण अन्यथा अणु
		वापस phy_clear_bits_mmd(phydev, DP83811_DEVADDR,
					  MII_DP83811_WOL_CFG, DP83811_WOL_EN);
	पूर्ण

पूर्ण

अटल व्योम dp83811_get_wol(काष्ठा phy_device *phydev,
			    काष्ठा ethtool_wolinfo *wol)
अणु
	u16 sopass_val;
	पूर्णांक value;

	wol->supported = (WAKE_MAGIC | WAKE_MAGICSECURE);
	wol->wolopts = 0;

	value = phy_पढ़ो_mmd(phydev, DP83811_DEVADDR, MII_DP83811_WOL_CFG);

	अगर (value & DP83811_WOL_MAGIC_EN)
		wol->wolopts |= WAKE_MAGIC;

	अगर (value & DP83811_WOL_SECURE_ON) अणु
		sopass_val = phy_पढ़ो_mmd(phydev, DP83811_DEVADDR,
					  MII_DP83811_RXSOP1);
		wol->sopass[0] = (sopass_val & 0xff);
		wol->sopass[1] = (sopass_val >> 8);

		sopass_val = phy_पढ़ो_mmd(phydev, DP83811_DEVADDR,
					  MII_DP83811_RXSOP2);
		wol->sopass[2] = (sopass_val & 0xff);
		wol->sopass[3] = (sopass_val >> 8);

		sopass_val = phy_पढ़ो_mmd(phydev, DP83811_DEVADDR,
					  MII_DP83811_RXSOP3);
		wol->sopass[4] = (sopass_val & 0xff);
		wol->sopass[5] = (sopass_val >> 8);

		wol->wolopts |= WAKE_MAGICSECURE;
	पूर्ण

	/* WoL is not enabled so set wolopts to 0 */
	अगर (!(value & DP83811_WOL_EN))
		wol->wolopts = 0;
पूर्ण

अटल पूर्णांक dp83811_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	पूर्णांक misr_status, err;

	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED) अणु
		err = dp83811_ack_पूर्णांकerrupt(phydev);
		अगर (err)
			वापस err;

		misr_status = phy_पढ़ो(phydev, MII_DP83811_INT_STAT1);
		अगर (misr_status < 0)
			वापस misr_status;

		misr_status |= (DP83811_RX_ERR_HF_INT_EN |
				DP83811_MS_TRAINING_INT_EN |
				DP83811_ANEG_COMPLETE_INT_EN |
				DP83811_ESD_EVENT_INT_EN |
				DP83811_WOL_INT_EN |
				DP83811_LINK_STAT_INT_EN |
				DP83811_ENERGY_DET_INT_EN |
				DP83811_LINK_QUAL_INT_EN);

		err = phy_ग_लिखो(phydev, MII_DP83811_INT_STAT1, misr_status);
		अगर (err < 0)
			वापस err;

		misr_status = phy_पढ़ो(phydev, MII_DP83811_INT_STAT2);
		अगर (misr_status < 0)
			वापस misr_status;

		misr_status |= (DP83811_JABBER_DET_INT_EN |
				DP83811_POLARITY_INT_EN |
				DP83811_SLEEP_MODE_INT_EN |
				DP83811_OVERTEMP_INT_EN |
				DP83811_OVERVOLTAGE_INT_EN |
				DP83811_UNDERVOLTAGE_INT_EN);

		err = phy_ग_लिखो(phydev, MII_DP83811_INT_STAT2, misr_status);
		अगर (err < 0)
			वापस err;

		misr_status = phy_पढ़ो(phydev, MII_DP83811_INT_STAT3);
		अगर (misr_status < 0)
			वापस misr_status;

		misr_status |= (DP83811_LPS_INT_EN |
				DP83811_NO_FRAME_INT_EN |
				DP83811_POR_DONE_INT_EN);

		err = phy_ग_लिखो(phydev, MII_DP83811_INT_STAT3, misr_status);

	पूर्ण अन्यथा अणु
		err = phy_ग_लिखो(phydev, MII_DP83811_INT_STAT1, 0);
		अगर (err < 0)
			वापस err;

		err = phy_ग_लिखो(phydev, MII_DP83811_INT_STAT2, 0);
		अगर (err < 0)
			वापस err;

		err = phy_ग_लिखो(phydev, MII_DP83811_INT_STAT3, 0);
		अगर (err < 0)
			वापस err;

		err = dp83811_ack_पूर्णांकerrupt(phydev);
	पूर्ण

	वापस err;
पूर्ण

अटल irqवापस_t dp83811_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	bool trigger_machine = false;
	पूर्णांक irq_status;

	/* The INT_STAT रेजिस्टरs 1, 2 and 3 are holding the पूर्णांकerrupt status
	 * in the upper half (15:8), जबतक the lower half (7:0) is used क्रम
	 * controlling the पूर्णांकerrupt enable state of those inभागidual पूर्णांकerrupt
	 * sources. To determine the possible पूर्णांकerrupt sources, just पढ़ो the
	 * INT_STAT* रेजिस्टर and use it directly to know which पूर्णांकerrupts have
	 * been enabled previously or not.
	 */
	irq_status = phy_पढ़ो(phydev, MII_DP83811_INT_STAT1);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण
	अगर (irq_status & ((irq_status & GENMASK(7, 0)) << 8))
		trigger_machine = true;

	irq_status = phy_पढ़ो(phydev, MII_DP83811_INT_STAT2);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण
	अगर (irq_status & ((irq_status & GENMASK(7, 0)) << 8))
		trigger_machine = true;

	irq_status = phy_पढ़ो(phydev, MII_DP83811_INT_STAT3);
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

अटल पूर्णांक dp83811_config_aneg(काष्ठा phy_device *phydev)
अणु
	पूर्णांक value, err;

	अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_SGMII) अणु
		value = phy_पढ़ो(phydev, MII_DP83811_SGMII_CTRL);
		अगर (phydev->स्वतःneg == AUTONEG_ENABLE) अणु
			err = phy_ग_लिखो(phydev, MII_DP83811_SGMII_CTRL,
					(DP83811_SGMII_AUTO_NEG_EN | value));
			अगर (err < 0)
				वापस err;
		पूर्ण अन्यथा अणु
			err = phy_ग_लिखो(phydev, MII_DP83811_SGMII_CTRL,
					(~DP83811_SGMII_AUTO_NEG_EN & value));
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण

	वापस genphy_config_aneg(phydev);
पूर्ण

अटल पूर्णांक dp83811_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक value, err;

	value = phy_पढ़ो(phydev, MII_DP83811_SGMII_CTRL);
	अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_SGMII) अणु
		err = phy_ग_लिखो(phydev, MII_DP83811_SGMII_CTRL,
					(DP83811_SGMII_EN | value));
	पूर्ण अन्यथा अणु
		err = phy_ग_लिखो(phydev, MII_DP83811_SGMII_CTRL,
				(~DP83811_SGMII_EN & value));
	पूर्ण

	अगर (err < 0)

		वापस err;

	value = DP83811_WOL_MAGIC_EN | DP83811_WOL_SECURE_ON | DP83811_WOL_EN;

	वापस phy_clear_bits_mmd(phydev, DP83811_DEVADDR, MII_DP83811_WOL_CFG,
				  value);
पूर्ण

अटल पूर्णांक dp83811_phy_reset(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	err = phy_ग_लिखो(phydev, MII_DP83811_RESET_CTRL, DP83811_HW_RESET);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक dp83811_suspend(काष्ठा phy_device *phydev)
अणु
	पूर्णांक value;

	value = phy_पढ़ो_mmd(phydev, DP83811_DEVADDR, MII_DP83811_WOL_CFG);

	अगर (!(value & DP83811_WOL_EN))
		genphy_suspend(phydev);

	वापस 0;
पूर्ण

अटल पूर्णांक dp83811_resume(काष्ठा phy_device *phydev)
अणु
	genphy_resume(phydev);

	phy_set_bits_mmd(phydev, DP83811_DEVADDR, MII_DP83811_WOL_CFG,
			 DP83811_WOL_CLR_INDICATION);

	वापस 0;
पूर्ण

अटल काष्ठा phy_driver dp83811_driver[] = अणु
	अणु
		.phy_id = DP83TC811_PHY_ID,
		.phy_id_mask = 0xfffffff0,
		.name = "TI DP83TC811",
		/* PHY_BASIC_FEATURES */
		.config_init = dp83811_config_init,
		.config_aneg = dp83811_config_aneg,
		.soft_reset = dp83811_phy_reset,
		.get_wol = dp83811_get_wol,
		.set_wol = dp83811_set_wol,
		.config_पूर्णांकr = dp83811_config_पूर्णांकr,
		.handle_पूर्णांकerrupt = dp83811_handle_पूर्णांकerrupt,
		.suspend = dp83811_suspend,
		.resume = dp83811_resume,
	 पूर्ण,
पूर्ण;
module_phy_driver(dp83811_driver);

अटल काष्ठा mdio_device_id __maybe_unused dp83811_tbl[] = अणु
	अणु DP83TC811_PHY_ID, 0xfffffff0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(mdio, dp83811_tbl);

MODULE_DESCRIPTION("Texas Instruments DP83TC811 PHY driver");
MODULE_AUTHOR("Dan Murphy <dmurphy@ti.com");
MODULE_LICENSE("GPL");
