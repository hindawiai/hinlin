<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* drivers/net/phy/realtek.c
 *
 * Driver क्रम Realtek PHYs
 *
 * Author: Johnson Leung <r58129@मुक्तscale.com>
 *
 * Copyright (c) 2004 Freescale Semiconductor, Inc.
 */
#समावेश <linux/bitops.h>
#समावेश <linux/phy.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>

#घोषणा RTL821x_PHYSR				0x11
#घोषणा RTL821x_PHYSR_DUPLEX			BIT(13)
#घोषणा RTL821x_PHYSR_SPEED			GENMASK(15, 14)

#घोषणा RTL821x_INER				0x12
#घोषणा RTL8211B_INER_INIT			0x6400
#घोषणा RTL8211E_INER_LINK_STATUS		BIT(10)
#घोषणा RTL8211F_INER_LINK_STATUS		BIT(4)

#घोषणा RTL821x_INSR				0x13

#घोषणा RTL821x_EXT_PAGE_SELECT			0x1e
#घोषणा RTL821x_PAGE_SELECT			0x1f

#घोषणा RTL8211F_PHYCR1				0x18
#घोषणा RTL8211F_INSR				0x1d

#घोषणा RTL8211F_TX_DELAY			BIT(8)
#घोषणा RTL8211F_RX_DELAY			BIT(3)

#घोषणा RTL8211F_ALDPS_PLL_OFF			BIT(1)
#घोषणा RTL8211F_ALDPS_ENABLE			BIT(2)
#घोषणा RTL8211F_ALDPS_XTAL_OFF			BIT(12)

#घोषणा RTL8211E_CTRL_DELAY			BIT(13)
#घोषणा RTL8211E_TX_DELAY			BIT(12)
#घोषणा RTL8211E_RX_DELAY			BIT(11)

#घोषणा RTL8201F_ISR				0x1e
#घोषणा RTL8201F_ISR_ANERR			BIT(15)
#घोषणा RTL8201F_ISR_DUPLEX			BIT(13)
#घोषणा RTL8201F_ISR_LINK			BIT(11)
#घोषणा RTL8201F_ISR_MASK			(RTL8201F_ISR_ANERR | \
						 RTL8201F_ISR_DUPLEX | \
						 RTL8201F_ISR_LINK)
#घोषणा RTL8201F_IER				0x13

#घोषणा RTL8366RB_POWER_SAVE			0x15
#घोषणा RTL8366RB_POWER_SAVE_ON			BIT(12)

#घोषणा RTL_SUPPORTS_5000FULL			BIT(14)
#घोषणा RTL_SUPPORTS_2500FULL			BIT(13)
#घोषणा RTL_SUPPORTS_10000FULL			BIT(0)
#घोषणा RTL_ADV_2500FULL			BIT(7)
#घोषणा RTL_LPADV_10000FULL			BIT(11)
#घोषणा RTL_LPADV_5000FULL			BIT(6)
#घोषणा RTL_LPADV_2500FULL			BIT(5)

#घोषणा RTL9000A_GINMR				0x14
#घोषणा RTL9000A_GINMR_LINK_STATUS		BIT(4)

#घोषणा RTLGEN_SPEED_MASK			0x0630

#घोषणा RTL_GENERIC_PHYID			0x001cc800

MODULE_DESCRIPTION("Realtek PHY driver");
MODULE_AUTHOR("Johnson Leung");
MODULE_LICENSE("GPL");

अटल पूर्णांक rtl821x_पढ़ो_page(काष्ठा phy_device *phydev)
अणु
	वापस __phy_पढ़ो(phydev, RTL821x_PAGE_SELECT);
पूर्ण

अटल पूर्णांक rtl821x_ग_लिखो_page(काष्ठा phy_device *phydev, पूर्णांक page)
अणु
	वापस __phy_ग_लिखो(phydev, RTL821x_PAGE_SELECT, page);
पूर्ण

अटल पूर्णांक rtl8201_ack_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	err = phy_पढ़ो(phydev, RTL8201F_ISR);

	वापस (err < 0) ? err : 0;
पूर्ण

अटल पूर्णांक rtl821x_ack_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	err = phy_पढ़ो(phydev, RTL821x_INSR);

	वापस (err < 0) ? err : 0;
पूर्ण

अटल पूर्णांक rtl8211f_ack_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	err = phy_पढ़ो_paged(phydev, 0xa43, RTL8211F_INSR);

	वापस (err < 0) ? err : 0;
पूर्ण

अटल पूर्णांक rtl8201_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	u16 val;
	पूर्णांक err;

	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED) अणु
		err = rtl8201_ack_पूर्णांकerrupt(phydev);
		अगर (err)
			वापस err;

		val = BIT(13) | BIT(12) | BIT(11);
		err = phy_ग_लिखो_paged(phydev, 0x7, RTL8201F_IER, val);
	पूर्ण अन्यथा अणु
		val = 0;
		err = phy_ग_लिखो_paged(phydev, 0x7, RTL8201F_IER, val);
		अगर (err)
			वापस err;

		err = rtl8201_ack_पूर्णांकerrupt(phydev);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक rtl8211b_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED) अणु
		err = rtl821x_ack_पूर्णांकerrupt(phydev);
		अगर (err)
			वापस err;

		err = phy_ग_लिखो(phydev, RTL821x_INER,
				RTL8211B_INER_INIT);
	पूर्ण अन्यथा अणु
		err = phy_ग_लिखो(phydev, RTL821x_INER, 0);
		अगर (err)
			वापस err;

		err = rtl821x_ack_पूर्णांकerrupt(phydev);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक rtl8211e_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED) अणु
		err = rtl821x_ack_पूर्णांकerrupt(phydev);
		अगर (err)
			वापस err;

		err = phy_ग_लिखो(phydev, RTL821x_INER,
				RTL8211E_INER_LINK_STATUS);
	पूर्ण अन्यथा अणु
		err = phy_ग_लिखो(phydev, RTL821x_INER, 0);
		अगर (err)
			वापस err;

		err = rtl821x_ack_पूर्णांकerrupt(phydev);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक rtl8211f_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	u16 val;
	पूर्णांक err;

	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED) अणु
		err = rtl8211f_ack_पूर्णांकerrupt(phydev);
		अगर (err)
			वापस err;

		val = RTL8211F_INER_LINK_STATUS;
		err = phy_ग_लिखो_paged(phydev, 0xa42, RTL821x_INER, val);
	पूर्ण अन्यथा अणु
		val = 0;
		err = phy_ग_लिखो_paged(phydev, 0xa42, RTL821x_INER, val);
		अगर (err)
			वापस err;

		err = rtl8211f_ack_पूर्णांकerrupt(phydev);
	पूर्ण

	वापस err;
पूर्ण

अटल irqवापस_t rtl8201_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक irq_status;

	irq_status = phy_पढ़ो(phydev, RTL8201F_ISR);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	अगर (!(irq_status & RTL8201F_ISR_MASK))
		वापस IRQ_NONE;

	phy_trigger_machine(phydev);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t rtl821x_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक irq_status, irq_enabled;

	irq_status = phy_पढ़ो(phydev, RTL821x_INSR);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	irq_enabled = phy_पढ़ो(phydev, RTL821x_INER);
	अगर (irq_enabled < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	अगर (!(irq_status & irq_enabled))
		वापस IRQ_NONE;

	phy_trigger_machine(phydev);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t rtl8211f_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक irq_status;

	irq_status = phy_पढ़ो_paged(phydev, 0xa43, RTL8211F_INSR);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	अगर (!(irq_status & RTL8211F_INER_LINK_STATUS))
		वापस IRQ_NONE;

	phy_trigger_machine(phydev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rtl8211_config_aneg(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	ret = genphy_config_aneg(phydev);
	अगर (ret < 0)
		वापस ret;

	/* Quirk was copied from venकरोr driver. Unक्रमtunately it includes no
	 * description of the magic numbers.
	 */
	अगर (phydev->speed == SPEED_100 && phydev->स्वतःneg == AUTONEG_DISABLE) अणु
		phy_ग_लिखो(phydev, 0x17, 0x2138);
		phy_ग_लिखो(phydev, 0x0e, 0x0260);
	पूर्ण अन्यथा अणु
		phy_ग_लिखो(phydev, 0x17, 0x2108);
		phy_ग_लिखो(phydev, 0x0e, 0x0000);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtl8211c_config_init(काष्ठा phy_device *phydev)
अणु
	/* RTL8211C has an issue when operating in Gigabit slave mode */
	वापस phy_set_bits(phydev, MII_CTRL1000,
			    CTL1000_ENABLE_MASTER | CTL1000_AS_MASTER);
पूर्ण

अटल पूर्णांक rtl8211f_config_init(काष्ठा phy_device *phydev)
अणु
	काष्ठा device *dev = &phydev->mdio.dev;
	u16 val_txdly, val_rxdly;
	u16 val;
	पूर्णांक ret;

	val = RTL8211F_ALDPS_ENABLE | RTL8211F_ALDPS_PLL_OFF | RTL8211F_ALDPS_XTAL_OFF;
	phy_modअगरy_paged_changed(phydev, 0xa43, RTL8211F_PHYCR1, val, val);

	चयन (phydev->पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_RGMII:
		val_txdly = 0;
		val_rxdly = 0;
		अवरोध;

	हाल PHY_INTERFACE_MODE_RGMII_RXID:
		val_txdly = 0;
		val_rxdly = RTL8211F_RX_DELAY;
		अवरोध;

	हाल PHY_INTERFACE_MODE_RGMII_TXID:
		val_txdly = RTL8211F_TX_DELAY;
		val_rxdly = 0;
		अवरोध;

	हाल PHY_INTERFACE_MODE_RGMII_ID:
		val_txdly = RTL8211F_TX_DELAY;
		val_rxdly = RTL8211F_RX_DELAY;
		अवरोध;

	शेष: /* the rest of the modes imply leaving delay as is. */
		वापस 0;
	पूर्ण

	ret = phy_modअगरy_paged_changed(phydev, 0xd08, 0x11, RTL8211F_TX_DELAY,
				       val_txdly);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to update the TX delay register\n");
		वापस ret;
	पूर्ण अन्यथा अगर (ret) अणु
		dev_dbg(dev,
			"%s 2ns TX delay (and changing the value from pin-strapping RXD1 or the bootloader)\n",
			val_txdly ? "Enabling" : "Disabling");
	पूर्ण अन्यथा अणु
		dev_dbg(dev,
			"2ns TX delay was already %s (by pin-strapping RXD1 or bootloader configuration)\n",
			val_txdly ? "enabled" : "disabled");
	पूर्ण

	ret = phy_modअगरy_paged_changed(phydev, 0xd08, 0x15, RTL8211F_RX_DELAY,
				       val_rxdly);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to update the RX delay register\n");
		वापस ret;
	पूर्ण अन्यथा अगर (ret) अणु
		dev_dbg(dev,
			"%s 2ns RX delay (and changing the value from pin-strapping RXD0 or the bootloader)\n",
			val_rxdly ? "Enabling" : "Disabling");
	पूर्ण अन्यथा अणु
		dev_dbg(dev,
			"2ns RX delay was already %s (by pin-strapping RXD0 or bootloader configuration)\n",
			val_rxdly ? "enabled" : "disabled");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtl8211e_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret = 0, oldpage;
	u16 val;

	/* enable TX/RX delay क्रम rgmii-* modes, and disable them क्रम rgmii. */
	चयन (phydev->पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_RGMII:
		val = RTL8211E_CTRL_DELAY | 0;
		अवरोध;
	हाल PHY_INTERFACE_MODE_RGMII_ID:
		val = RTL8211E_CTRL_DELAY | RTL8211E_TX_DELAY | RTL8211E_RX_DELAY;
		अवरोध;
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
		val = RTL8211E_CTRL_DELAY | RTL8211E_RX_DELAY;
		अवरोध;
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
		val = RTL8211E_CTRL_DELAY | RTL8211E_TX_DELAY;
		अवरोध;
	शेष: /* the rest of the modes imply leaving delays as is. */
		वापस 0;
	पूर्ण

	/* According to a sample driver there is a 0x1c config रेजिस्टर on the
	 * 0xa4 extension page (0x7) layout. It can be used to disable/enable
	 * the RX/TX delays otherwise controlled by RXDLY/TXDLY pins.
	 * The configuration रेजिस्टर definition:
	 * 14 = reserved
	 * 13 = Force Tx RX Delay controlled by bit12 bit11,
	 * 12 = RX Delay, 11 = TX Delay
	 * 10:0 = Test && debug settings reserved by realtek
	 */
	oldpage = phy_select_page(phydev, 0x7);
	अगर (oldpage < 0)
		जाओ err_restore_page;

	ret = __phy_ग_लिखो(phydev, RTL821x_EXT_PAGE_SELECT, 0xa4);
	अगर (ret)
		जाओ err_restore_page;

	ret = __phy_modअगरy(phydev, 0x1c, RTL8211E_CTRL_DELAY
			   | RTL8211E_TX_DELAY | RTL8211E_RX_DELAY,
			   val);

err_restore_page:
	वापस phy_restore_page(phydev, oldpage, ret);
पूर्ण

अटल पूर्णांक rtl8211b_suspend(काष्ठा phy_device *phydev)
अणु
	phy_ग_लिखो(phydev, MII_MMD_DATA, BIT(9));

	वापस genphy_suspend(phydev);
पूर्ण

अटल पूर्णांक rtl8211b_resume(काष्ठा phy_device *phydev)
अणु
	phy_ग_लिखो(phydev, MII_MMD_DATA, 0);

	वापस genphy_resume(phydev);
पूर्ण

अटल पूर्णांक rtl8366rb_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	ret = phy_set_bits(phydev, RTL8366RB_POWER_SAVE,
			   RTL8366RB_POWER_SAVE_ON);
	अगर (ret) अणु
		dev_err(&phydev->mdio.dev,
			"error enabling power management\n");
	पूर्ण

	वापस ret;
पूर्ण

/* get actual speed to cover the करोwnshअगरt हाल */
अटल पूर्णांक rtlgen_get_speed(काष्ठा phy_device *phydev)
अणु
	पूर्णांक val;

	अगर (!phydev->link)
		वापस 0;

	val = phy_पढ़ो_paged(phydev, 0xa43, 0x12);
	अगर (val < 0)
		वापस val;

	चयन (val & RTLGEN_SPEED_MASK) अणु
	हाल 0x0000:
		phydev->speed = SPEED_10;
		अवरोध;
	हाल 0x0010:
		phydev->speed = SPEED_100;
		अवरोध;
	हाल 0x0020:
		phydev->speed = SPEED_1000;
		अवरोध;
	हाल 0x0200:
		phydev->speed = SPEED_10000;
		अवरोध;
	हाल 0x0210:
		phydev->speed = SPEED_2500;
		अवरोध;
	हाल 0x0220:
		phydev->speed = SPEED_5000;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtlgen_पढ़ो_status(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	ret = genphy_पढ़ो_status(phydev);
	अगर (ret < 0)
		वापस ret;

	वापस rtlgen_get_speed(phydev);
पूर्ण

अटल पूर्णांक rtlgen_पढ़ो_mmd(काष्ठा phy_device *phydev, पूर्णांक devnum, u16 regnum)
अणु
	पूर्णांक ret;

	अगर (devnum == MDIO_MMD_PCS && regnum == MDIO_PCS_EEE_ABLE) अणु
		rtl821x_ग_लिखो_page(phydev, 0xa5c);
		ret = __phy_पढ़ो(phydev, 0x12);
		rtl821x_ग_लिखो_page(phydev, 0);
	पूर्ण अन्यथा अगर (devnum == MDIO_MMD_AN && regnum == MDIO_AN_EEE_ADV) अणु
		rtl821x_ग_लिखो_page(phydev, 0xa5d);
		ret = __phy_पढ़ो(phydev, 0x10);
		rtl821x_ग_लिखो_page(phydev, 0);
	पूर्ण अन्यथा अगर (devnum == MDIO_MMD_AN && regnum == MDIO_AN_EEE_LPABLE) अणु
		rtl821x_ग_लिखो_page(phydev, 0xa5d);
		ret = __phy_पढ़ो(phydev, 0x11);
		rtl821x_ग_लिखो_page(phydev, 0);
	पूर्ण अन्यथा अणु
		ret = -EOPNOTSUPP;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rtlgen_ग_लिखो_mmd(काष्ठा phy_device *phydev, पूर्णांक devnum, u16 regnum,
			    u16 val)
अणु
	पूर्णांक ret;

	अगर (devnum == MDIO_MMD_AN && regnum == MDIO_AN_EEE_ADV) अणु
		rtl821x_ग_लिखो_page(phydev, 0xa5d);
		ret = __phy_ग_लिखो(phydev, 0x10, val);
		rtl821x_ग_लिखो_page(phydev, 0);
	पूर्ण अन्यथा अणु
		ret = -EOPNOTSUPP;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rtl822x_पढ़ो_mmd(काष्ठा phy_device *phydev, पूर्णांक devnum, u16 regnum)
अणु
	पूर्णांक ret = rtlgen_पढ़ो_mmd(phydev, devnum, regnum);

	अगर (ret != -EOPNOTSUPP)
		वापस ret;

	अगर (devnum == MDIO_MMD_PCS && regnum == MDIO_PCS_EEE_ABLE2) अणु
		rtl821x_ग_लिखो_page(phydev, 0xa6e);
		ret = __phy_पढ़ो(phydev, 0x16);
		rtl821x_ग_लिखो_page(phydev, 0);
	पूर्ण अन्यथा अगर (devnum == MDIO_MMD_AN && regnum == MDIO_AN_EEE_ADV2) अणु
		rtl821x_ग_लिखो_page(phydev, 0xa6d);
		ret = __phy_पढ़ो(phydev, 0x12);
		rtl821x_ग_लिखो_page(phydev, 0);
	पूर्ण अन्यथा अगर (devnum == MDIO_MMD_AN && regnum == MDIO_AN_EEE_LPABLE2) अणु
		rtl821x_ग_लिखो_page(phydev, 0xa6d);
		ret = __phy_पढ़ो(phydev, 0x10);
		rtl821x_ग_लिखो_page(phydev, 0);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rtl822x_ग_लिखो_mmd(काष्ठा phy_device *phydev, पूर्णांक devnum, u16 regnum,
			     u16 val)
अणु
	पूर्णांक ret = rtlgen_ग_लिखो_mmd(phydev, devnum, regnum, val);

	अगर (ret != -EOPNOTSUPP)
		वापस ret;

	अगर (devnum == MDIO_MMD_AN && regnum == MDIO_AN_EEE_ADV2) अणु
		rtl821x_ग_लिखो_page(phydev, 0xa6d);
		ret = __phy_ग_लिखो(phydev, 0x12, val);
		rtl821x_ग_लिखो_page(phydev, 0);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rtl822x_get_features(काष्ठा phy_device *phydev)
अणु
	पूर्णांक val;

	val = phy_पढ़ो_paged(phydev, 0xa61, 0x13);
	अगर (val < 0)
		वापस val;

	linkmode_mod_bit(ETHTOOL_LINK_MODE_2500baseT_Full_BIT,
			 phydev->supported, val & RTL_SUPPORTS_2500FULL);
	linkmode_mod_bit(ETHTOOL_LINK_MODE_5000baseT_Full_BIT,
			 phydev->supported, val & RTL_SUPPORTS_5000FULL);
	linkmode_mod_bit(ETHTOOL_LINK_MODE_10000baseT_Full_BIT,
			 phydev->supported, val & RTL_SUPPORTS_10000FULL);

	वापस genphy_पढ़ो_abilities(phydev);
पूर्ण

अटल पूर्णांक rtl822x_config_aneg(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret = 0;

	अगर (phydev->स्वतःneg == AUTONEG_ENABLE) अणु
		u16 adv2500 = 0;

		अगर (linkmode_test_bit(ETHTOOL_LINK_MODE_2500baseT_Full_BIT,
				      phydev->advertising))
			adv2500 = RTL_ADV_2500FULL;

		ret = phy_modअगरy_paged_changed(phydev, 0xa5d, 0x12,
					       RTL_ADV_2500FULL, adv2500);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस __genphy_config_aneg(phydev, ret);
पूर्ण

अटल पूर्णांक rtl822x_पढ़ो_status(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	अगर (phydev->स्वतःneg == AUTONEG_ENABLE) अणु
		पूर्णांक lpadv = phy_पढ़ो_paged(phydev, 0xa5d, 0x13);

		अगर (lpadv < 0)
			वापस lpadv;

		linkmode_mod_bit(ETHTOOL_LINK_MODE_10000baseT_Full_BIT,
			phydev->lp_advertising, lpadv & RTL_LPADV_10000FULL);
		linkmode_mod_bit(ETHTOOL_LINK_MODE_5000baseT_Full_BIT,
			phydev->lp_advertising, lpadv & RTL_LPADV_5000FULL);
		linkmode_mod_bit(ETHTOOL_LINK_MODE_2500baseT_Full_BIT,
			phydev->lp_advertising, lpadv & RTL_LPADV_2500FULL);
	पूर्ण

	ret = genphy_पढ़ो_status(phydev);
	अगर (ret < 0)
		वापस ret;

	वापस rtlgen_get_speed(phydev);
पूर्ण

अटल bool rtlgen_supports_2_5gbps(काष्ठा phy_device *phydev)
अणु
	पूर्णांक val;

	phy_ग_लिखो(phydev, RTL821x_PAGE_SELECT, 0xa61);
	val = phy_पढ़ो(phydev, 0x13);
	phy_ग_लिखो(phydev, RTL821x_PAGE_SELECT, 0);

	वापस val >= 0 && val & RTL_SUPPORTS_2500FULL;
पूर्ण

अटल पूर्णांक rtlgen_match_phy_device(काष्ठा phy_device *phydev)
अणु
	वापस phydev->phy_id == RTL_GENERIC_PHYID &&
	       !rtlgen_supports_2_5gbps(phydev);
पूर्ण

अटल पूर्णांक rtl8226_match_phy_device(काष्ठा phy_device *phydev)
अणु
	वापस phydev->phy_id == RTL_GENERIC_PHYID &&
	       rtlgen_supports_2_5gbps(phydev);
पूर्ण

अटल पूर्णांक rtlgen_resume(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret = genphy_resume(phydev);

	/* Internal PHY's from RTL8168h up may not be instantly पढ़ोy */
	msleep(20);

	वापस ret;
पूर्ण

अटल पूर्णांक rtl9000a_config_init(काष्ठा phy_device *phydev)
अणु
	phydev->स्वतःneg = AUTONEG_DISABLE;
	phydev->speed = SPEED_100;
	phydev->duplex = DUPLEX_FULL;

	वापस 0;
पूर्ण

अटल पूर्णांक rtl9000a_config_aneg(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;
	u16 ctl = 0;

	चयन (phydev->master_slave_set) अणु
	हाल MASTER_SLAVE_CFG_MASTER_FORCE:
		ctl |= CTL1000_AS_MASTER;
		अवरोध;
	हाल MASTER_SLAVE_CFG_SLAVE_FORCE:
		अवरोध;
	हाल MASTER_SLAVE_CFG_UNKNOWN:
	हाल MASTER_SLAVE_CFG_UNSUPPORTED:
		वापस 0;
	शेष:
		phydev_warn(phydev, "Unsupported Master/Slave mode\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	ret = phy_modअगरy_changed(phydev, MII_CTRL1000, CTL1000_AS_MASTER, ctl);
	अगर (ret == 1)
		ret = genphy_soft_reset(phydev);

	वापस ret;
पूर्ण

अटल पूर्णांक rtl9000a_पढ़ो_status(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	phydev->master_slave_get = MASTER_SLAVE_CFG_UNKNOWN;
	phydev->master_slave_state = MASTER_SLAVE_STATE_UNKNOWN;

	ret = genphy_update_link(phydev);
	अगर (ret)
		वापस ret;

	ret = phy_पढ़ो(phydev, MII_CTRL1000);
	अगर (ret < 0)
		वापस ret;
	अगर (ret & CTL1000_AS_MASTER)
		phydev->master_slave_get = MASTER_SLAVE_CFG_MASTER_FORCE;
	अन्यथा
		phydev->master_slave_get = MASTER_SLAVE_CFG_SLAVE_FORCE;

	ret = phy_पढ़ो(phydev, MII_STAT1000);
	अगर (ret < 0)
		वापस ret;
	अगर (ret & LPA_1000MSRES)
		phydev->master_slave_state = MASTER_SLAVE_STATE_MASTER;
	अन्यथा
		phydev->master_slave_state = MASTER_SLAVE_STATE_SLAVE;

	वापस 0;
पूर्ण

अटल पूर्णांक rtl9000a_ack_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	err = phy_पढ़ो(phydev, RTL8211F_INSR);

	वापस (err < 0) ? err : 0;
पूर्ण

अटल पूर्णांक rtl9000a_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	u16 val;
	पूर्णांक err;

	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED) अणु
		err = rtl9000a_ack_पूर्णांकerrupt(phydev);
		अगर (err)
			वापस err;

		val = (u16)~RTL9000A_GINMR_LINK_STATUS;
		err = phy_ग_लिखो_paged(phydev, 0xa42, RTL9000A_GINMR, val);
	पूर्ण अन्यथा अणु
		val = ~0;
		err = phy_ग_लिखो_paged(phydev, 0xa42, RTL9000A_GINMR, val);
		अगर (err)
			वापस err;

		err = rtl9000a_ack_पूर्णांकerrupt(phydev);
	पूर्ण

	वापस phy_ग_लिखो_paged(phydev, 0xa42, RTL9000A_GINMR, val);
पूर्ण

अटल irqवापस_t rtl9000a_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक irq_status;

	irq_status = phy_पढ़ो(phydev, RTL8211F_INSR);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	अगर (!(irq_status & RTL8211F_INER_LINK_STATUS))
		वापस IRQ_NONE;

	phy_trigger_machine(phydev);

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा phy_driver realtek_drvs[] = अणु
	अणु
		PHY_ID_MATCH_EXACT(0x00008201),
		.name           = "RTL8201CP Ethernet",
		.पढ़ो_page	= rtl821x_पढ़ो_page,
		.ग_लिखो_page	= rtl821x_ग_लिखो_page,
	पूर्ण, अणु
		PHY_ID_MATCH_EXACT(0x001cc816),
		.name		= "RTL8201F Fast Ethernet",
		.config_पूर्णांकr	= &rtl8201_config_पूर्णांकr,
		.handle_पूर्णांकerrupt = rtl8201_handle_पूर्णांकerrupt,
		.suspend	= genphy_suspend,
		.resume		= genphy_resume,
		.पढ़ो_page	= rtl821x_पढ़ो_page,
		.ग_लिखो_page	= rtl821x_ग_लिखो_page,
	पूर्ण, अणु
		PHY_ID_MATCH_MODEL(0x001cc880),
		.name		= "RTL8208 Fast Ethernet",
		.पढ़ो_mmd	= genphy_पढ़ो_mmd_unsupported,
		.ग_लिखो_mmd	= genphy_ग_लिखो_mmd_unsupported,
		.suspend	= genphy_suspend,
		.resume		= genphy_resume,
		.पढ़ो_page	= rtl821x_पढ़ो_page,
		.ग_लिखो_page	= rtl821x_ग_लिखो_page,
	पूर्ण, अणु
		PHY_ID_MATCH_EXACT(0x001cc910),
		.name		= "RTL8211 Gigabit Ethernet",
		.config_aneg	= rtl8211_config_aneg,
		.पढ़ो_mmd	= &genphy_पढ़ो_mmd_unsupported,
		.ग_लिखो_mmd	= &genphy_ग_लिखो_mmd_unsupported,
		.पढ़ो_page	= rtl821x_पढ़ो_page,
		.ग_लिखो_page	= rtl821x_ग_लिखो_page,
	पूर्ण, अणु
		PHY_ID_MATCH_EXACT(0x001cc912),
		.name		= "RTL8211B Gigabit Ethernet",
		.config_पूर्णांकr	= &rtl8211b_config_पूर्णांकr,
		.handle_पूर्णांकerrupt = rtl821x_handle_पूर्णांकerrupt,
		.पढ़ो_mmd	= &genphy_पढ़ो_mmd_unsupported,
		.ग_लिखो_mmd	= &genphy_ग_लिखो_mmd_unsupported,
		.suspend	= rtl8211b_suspend,
		.resume		= rtl8211b_resume,
		.पढ़ो_page	= rtl821x_पढ़ो_page,
		.ग_लिखो_page	= rtl821x_ग_लिखो_page,
	पूर्ण, अणु
		PHY_ID_MATCH_EXACT(0x001cc913),
		.name		= "RTL8211C Gigabit Ethernet",
		.config_init	= rtl8211c_config_init,
		.पढ़ो_mmd	= &genphy_पढ़ो_mmd_unsupported,
		.ग_लिखो_mmd	= &genphy_ग_लिखो_mmd_unsupported,
		.पढ़ो_page	= rtl821x_पढ़ो_page,
		.ग_लिखो_page	= rtl821x_ग_लिखो_page,
	पूर्ण, अणु
		PHY_ID_MATCH_EXACT(0x001cc914),
		.name		= "RTL8211DN Gigabit Ethernet",
		.config_पूर्णांकr	= rtl8211e_config_पूर्णांकr,
		.handle_पूर्णांकerrupt = rtl821x_handle_पूर्णांकerrupt,
		.suspend	= genphy_suspend,
		.resume		= genphy_resume,
		.पढ़ो_page	= rtl821x_पढ़ो_page,
		.ग_लिखो_page	= rtl821x_ग_लिखो_page,
	पूर्ण, अणु
		PHY_ID_MATCH_EXACT(0x001cc915),
		.name		= "RTL8211E Gigabit Ethernet",
		.config_init	= &rtl8211e_config_init,
		.config_पूर्णांकr	= &rtl8211e_config_पूर्णांकr,
		.handle_पूर्णांकerrupt = rtl821x_handle_पूर्णांकerrupt,
		.suspend	= genphy_suspend,
		.resume		= genphy_resume,
		.पढ़ो_page	= rtl821x_पढ़ो_page,
		.ग_लिखो_page	= rtl821x_ग_लिखो_page,
	पूर्ण, अणु
		PHY_ID_MATCH_EXACT(0x001cc916),
		.name		= "RTL8211F Gigabit Ethernet",
		.config_init	= &rtl8211f_config_init,
		.पढ़ो_status	= rtlgen_पढ़ो_status,
		.config_पूर्णांकr	= &rtl8211f_config_पूर्णांकr,
		.handle_पूर्णांकerrupt = rtl8211f_handle_पूर्णांकerrupt,
		.suspend	= genphy_suspend,
		.resume		= genphy_resume,
		.पढ़ो_page	= rtl821x_पढ़ो_page,
		.ग_लिखो_page	= rtl821x_ग_लिखो_page,
	पूर्ण, अणु
		.name		= "Generic FE-GE Realtek PHY",
		.match_phy_device = rtlgen_match_phy_device,
		.पढ़ो_status	= rtlgen_पढ़ो_status,
		.suspend	= genphy_suspend,
		.resume		= rtlgen_resume,
		.पढ़ो_page	= rtl821x_पढ़ो_page,
		.ग_लिखो_page	= rtl821x_ग_लिखो_page,
		.पढ़ो_mmd	= rtlgen_पढ़ो_mmd,
		.ग_लिखो_mmd	= rtlgen_ग_लिखो_mmd,
	पूर्ण, अणु
		.name		= "RTL8226 2.5Gbps PHY",
		.match_phy_device = rtl8226_match_phy_device,
		.get_features	= rtl822x_get_features,
		.config_aneg	= rtl822x_config_aneg,
		.पढ़ो_status	= rtl822x_पढ़ो_status,
		.suspend	= genphy_suspend,
		.resume		= rtlgen_resume,
		.पढ़ो_page	= rtl821x_पढ़ो_page,
		.ग_लिखो_page	= rtl821x_ग_लिखो_page,
		.पढ़ो_mmd	= rtl822x_पढ़ो_mmd,
		.ग_लिखो_mmd	= rtl822x_ग_लिखो_mmd,
	पूर्ण, अणु
		PHY_ID_MATCH_EXACT(0x001cc840),
		.name		= "RTL8226B_RTL8221B 2.5Gbps PHY",
		.get_features	= rtl822x_get_features,
		.config_aneg	= rtl822x_config_aneg,
		.पढ़ो_status	= rtl822x_पढ़ो_status,
		.suspend	= genphy_suspend,
		.resume		= rtlgen_resume,
		.पढ़ो_page	= rtl821x_पढ़ो_page,
		.ग_लिखो_page	= rtl821x_ग_लिखो_page,
		.पढ़ो_mmd	= rtl822x_पढ़ो_mmd,
		.ग_लिखो_mmd	= rtl822x_ग_लिखो_mmd,
	पूर्ण, अणु
		PHY_ID_MATCH_EXACT(0x001cc838),
		.name           = "RTL8226-CG 2.5Gbps PHY",
		.get_features   = rtl822x_get_features,
		.config_aneg    = rtl822x_config_aneg,
		.पढ़ो_status    = rtl822x_पढ़ो_status,
		.suspend        = genphy_suspend,
		.resume         = rtlgen_resume,
		.पढ़ो_page      = rtl821x_पढ़ो_page,
		.ग_लिखो_page     = rtl821x_ग_लिखो_page,
	पूर्ण, अणु
		PHY_ID_MATCH_EXACT(0x001cc848),
		.name           = "RTL8226B-CG_RTL8221B-CG 2.5Gbps PHY",
		.get_features   = rtl822x_get_features,
		.config_aneg    = rtl822x_config_aneg,
		.पढ़ो_status    = rtl822x_पढ़ो_status,
		.suspend        = genphy_suspend,
		.resume         = rtlgen_resume,
		.पढ़ो_page      = rtl821x_पढ़ो_page,
		.ग_लिखो_page     = rtl821x_ग_लिखो_page,
	पूर्ण, अणु
		PHY_ID_MATCH_EXACT(0x001cc849),
		.name           = "RTL8221B-VB-CG 2.5Gbps PHY",
		.get_features   = rtl822x_get_features,
		.config_aneg    = rtl822x_config_aneg,
		.पढ़ो_status    = rtl822x_पढ़ो_status,
		.suspend        = genphy_suspend,
		.resume         = rtlgen_resume,
		.पढ़ो_page      = rtl821x_पढ़ो_page,
		.ग_लिखो_page     = rtl821x_ग_लिखो_page,
	पूर्ण, अणु
		PHY_ID_MATCH_EXACT(0x001cc84a),
		.name           = "RTL8221B-VM-CG 2.5Gbps PHY",
		.get_features   = rtl822x_get_features,
		.config_aneg    = rtl822x_config_aneg,
		.पढ़ो_status    = rtl822x_पढ़ो_status,
		.suspend        = genphy_suspend,
		.resume         = rtlgen_resume,
		.पढ़ो_page      = rtl821x_पढ़ो_page,
		.ग_लिखो_page     = rtl821x_ग_लिखो_page,
	पूर्ण, अणु
		PHY_ID_MATCH_EXACT(0x001cc961),
		.name		= "RTL8366RB Gigabit Ethernet",
		.config_init	= &rtl8366rb_config_init,
		/* These पूर्णांकerrupts are handled by the irq controller
		 * embedded inside the RTL8366RB, they get unmasked when the
		 * irq is requested and ACKed by पढ़ोing the status रेजिस्टर,
		 * which is करोne by the irqchip code.
		 */
		.config_पूर्णांकr	= genphy_no_config_पूर्णांकr,
		.handle_पूर्णांकerrupt = genphy_handle_पूर्णांकerrupt_no_ack,
		.suspend	= genphy_suspend,
		.resume		= genphy_resume,
	पूर्ण, अणु
		PHY_ID_MATCH_EXACT(0x001ccb00),
		.name		= "RTL9000AA_RTL9000AN Ethernet",
		.features       = PHY_BASIC_T1_FEATURES,
		.config_init	= rtl9000a_config_init,
		.config_aneg	= rtl9000a_config_aneg,
		.पढ़ो_status	= rtl9000a_पढ़ो_status,
		.config_पूर्णांकr	= rtl9000a_config_पूर्णांकr,
		.handle_पूर्णांकerrupt = rtl9000a_handle_पूर्णांकerrupt,
		.suspend	= genphy_suspend,
		.resume		= genphy_resume,
		.पढ़ो_page	= rtl821x_पढ़ो_page,
		.ग_लिखो_page	= rtl821x_ग_लिखो_page,
	पूर्ण,
पूर्ण;

module_phy_driver(realtek_drvs);

अटल स्थिर काष्ठा mdio_device_id __maybe_unused realtek_tbl[] = अणु
	अणु PHY_ID_MATCH_VENDOR(0x001cc800) पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(mdio, realtek_tbl);
