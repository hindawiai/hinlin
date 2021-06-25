<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2015 Microchip Technology
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mii.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/phy.h>
#समावेश <linux/microchipphy.h>
#समावेश <linux/delay.h>
#समावेश <linux/of.h>
#समावेश <dt-bindings/net/microchip-lan78xx.h>

#घोषणा DRIVER_AUTHOR	"WOOJUNG HUH <woojung.huh@microchip.com>"
#घोषणा DRIVER_DESC	"Microchip LAN88XX PHY driver"

काष्ठा lan88xx_priv अणु
	पूर्णांक	chip_id;
	पूर्णांक	chip_rev;
	__u32	wolopts;
पूर्ण;

अटल पूर्णांक lan88xx_पढ़ो_page(काष्ठा phy_device *phydev)
अणु
	वापस __phy_पढ़ो(phydev, LAN88XX_EXT_PAGE_ACCESS);
पूर्ण

अटल पूर्णांक lan88xx_ग_लिखो_page(काष्ठा phy_device *phydev, पूर्णांक page)
अणु
	वापस __phy_ग_लिखो(phydev, LAN88XX_EXT_PAGE_ACCESS, page);
पूर्ण

अटल पूर्णांक lan88xx_phy_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	पूर्णांक rc;

	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED) अणु
		/* unmask all source and clear them beक्रमe enable */
		rc = phy_ग_लिखो(phydev, LAN88XX_INT_MASK, 0x7FFF);
		rc = phy_पढ़ो(phydev, LAN88XX_INT_STS);
		rc = phy_ग_लिखो(phydev, LAN88XX_INT_MASK,
			       LAN88XX_INT_MASK_MDINTPIN_EN_ |
			       LAN88XX_INT_MASK_LINK_CHANGE_);
	पूर्ण अन्यथा अणु
		rc = phy_ग_लिखो(phydev, LAN88XX_INT_MASK, 0);
		अगर (rc)
			वापस rc;

		/* Ack पूर्णांकerrupts after they have been disabled */
		rc = phy_पढ़ो(phydev, LAN88XX_INT_STS);
	पूर्ण

	वापस rc < 0 ? rc : 0;
पूर्ण

अटल irqवापस_t lan88xx_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक irq_status;

	irq_status = phy_पढ़ो(phydev, LAN88XX_INT_STS);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	अगर (!(irq_status & LAN88XX_INT_STS_LINK_CHANGE_))
		वापस IRQ_NONE;

	phy_trigger_machine(phydev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक lan88xx_suspend(काष्ठा phy_device *phydev)
अणु
	काष्ठा lan88xx_priv *priv = phydev->priv;

	/* करो not घातer करोwn PHY when WOL is enabled */
	अगर (!priv->wolopts)
		genphy_suspend(phydev);

	वापस 0;
पूर्ण

अटल पूर्णांक lan88xx_TR_reg_set(काष्ठा phy_device *phydev, u16 regaddr,
			      u32 data)
अणु
	पूर्णांक val, save_page, ret = 0;
	u16 buf;

	/* Save current page */
	save_page = phy_save_page(phydev);
	अगर (save_page < 0) अणु
		phydev_warn(phydev, "Failed to get current page\n");
		जाओ err;
	पूर्ण

	/* Switch to TR page */
	lan88xx_ग_लिखो_page(phydev, LAN88XX_EXT_PAGE_ACCESS_TR);

	ret = __phy_ग_लिखो(phydev, LAN88XX_EXT_PAGE_TR_LOW_DATA,
			  (data & 0xFFFF));
	अगर (ret < 0) अणु
		phydev_warn(phydev, "Failed to write TR low data\n");
		जाओ err;
	पूर्ण

	ret = __phy_ग_लिखो(phydev, LAN88XX_EXT_PAGE_TR_HIGH_DATA,
			  (data & 0x00FF0000) >> 16);
	अगर (ret < 0) अणु
		phydev_warn(phydev, "Failed to write TR high data\n");
		जाओ err;
	पूर्ण

	/* Config control bits [15:13] of रेजिस्टर */
	buf = (regaddr & ~(0x3 << 13));/* Clr [14:13] to ग_लिखो data in reg */
	buf |= 0x8000; /* Set [15] to Packet transmit */

	ret = __phy_ग_लिखो(phydev, LAN88XX_EXT_PAGE_TR_CR, buf);
	अगर (ret < 0) अणु
		phydev_warn(phydev, "Failed to write data in reg\n");
		जाओ err;
	पूर्ण

	usleep_range(1000, 2000);/* Wait क्रम Data to be written */
	val = __phy_पढ़ो(phydev, LAN88XX_EXT_PAGE_TR_CR);
	अगर (!(val & 0x8000))
		phydev_warn(phydev, "TR Register[0x%X] configuration failed\n",
			    regaddr);
err:
	वापस phy_restore_page(phydev, save_page, ret);
पूर्ण

अटल व्योम lan88xx_config_TR_regs(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	/* Get access to Channel 0x1, Node 0xF , Register 0x01.
	 * Write 24-bit value 0x12B00A to रेजिस्टर. Setting MrvlTrFix1000Kf,
	 * MrvlTrFix1000Kp, MasterEnableTR bits.
	 */
	err = lan88xx_TR_reg_set(phydev, 0x0F82, 0x12B00A);
	अगर (err < 0)
		phydev_warn(phydev, "Failed to Set Register[0x0F82]\n");

	/* Get access to Channel b'10, Node b'1101, Register 0x06.
	 * Write 24-bit value 0xD2C46F to रेजिस्टर. Setting SSTrKf1000Slv,
	 * SSTrKp1000Mas bits.
	 */
	err = lan88xx_TR_reg_set(phydev, 0x168C, 0xD2C46F);
	अगर (err < 0)
		phydev_warn(phydev, "Failed to Set Register[0x168C]\n");

	/* Get access to Channel b'10, Node b'1111, Register 0x11.
	 * Write 24-bit value 0x620 to रेजिस्टर. Setting rem_upd_करोne_thresh
	 * bits
	 */
	err = lan88xx_TR_reg_set(phydev, 0x17A2, 0x620);
	अगर (err < 0)
		phydev_warn(phydev, "Failed to Set Register[0x17A2]\n");

	/* Get access to Channel b'10, Node b'1101, Register 0x10.
	 * Write 24-bit value 0xEEFFDD to रेजिस्टर. Setting
	 * eee_TrKp1Long_1000, eee_TrKp2Long_1000, eee_TrKp3Long_1000,
	 * eee_TrKp1Short_1000,eee_TrKp2Short_1000, eee_TrKp3Short_1000 bits.
	 */
	err = lan88xx_TR_reg_set(phydev, 0x16A0, 0xEEFFDD);
	अगर (err < 0)
		phydev_warn(phydev, "Failed to Set Register[0x16A0]\n");

	/* Get access to Channel b'10, Node b'1101, Register 0x13.
	 * Write 24-bit value 0x071448 to रेजिस्टर. Setting
	 * slv_lpi_tr_पंचांगr_val1, slv_lpi_tr_पंचांगr_val2 bits.
	 */
	err = lan88xx_TR_reg_set(phydev, 0x16A6, 0x071448);
	अगर (err < 0)
		phydev_warn(phydev, "Failed to Set Register[0x16A6]\n");

	/* Get access to Channel b'10, Node b'1101, Register 0x12.
	 * Write 24-bit value 0x13132F to रेजिस्टर. Setting
	 * slv_sigdet_समयr_val1, slv_sigdet_समयr_val2 bits.
	 */
	err = lan88xx_TR_reg_set(phydev, 0x16A4, 0x13132F);
	अगर (err < 0)
		phydev_warn(phydev, "Failed to Set Register[0x16A4]\n");

	/* Get access to Channel b'10, Node b'1101, Register 0x14.
	 * Write 24-bit value 0x0 to रेजिस्टर. Setting eee_3level_delay,
	 * eee_TrKf_मुक्तze_delay bits.
	 */
	err = lan88xx_TR_reg_set(phydev, 0x16A8, 0x0);
	अगर (err < 0)
		phydev_warn(phydev, "Failed to Set Register[0x16A8]\n");

	/* Get access to Channel b'01, Node b'1111, Register 0x34.
	 * Write 24-bit value 0x91B06C to रेजिस्टर. Setting
	 * FastMseSearchThreshLong1000, FastMseSearchThreshShort1000,
	 * FastMseSearchUpdGain1000 bits.
	 */
	err = lan88xx_TR_reg_set(phydev, 0x0FE8, 0x91B06C);
	अगर (err < 0)
		phydev_warn(phydev, "Failed to Set Register[0x0FE8]\n");

	/* Get access to Channel b'01, Node b'1111, Register 0x3E.
	 * Write 24-bit value 0xC0A028 to रेजिस्टर. Setting
	 * FastMseKp2ThreshLong1000, FastMseKp2ThreshShort1000,
	 * FastMseKp2UpdGain1000, FastMseKp2ExitEn1000 bits.
	 */
	err = lan88xx_TR_reg_set(phydev, 0x0FFC, 0xC0A028);
	अगर (err < 0)
		phydev_warn(phydev, "Failed to Set Register[0x0FFC]\n");

	/* Get access to Channel b'01, Node b'1111, Register 0x35.
	 * Write 24-bit value 0x041600 to रेजिस्टर. Setting
	 * FastMseSearchPhShNum1000, FastMseSearchClksPerPh1000,
	 * FastMsePhChangeDelay1000 bits.
	 */
	err = lan88xx_TR_reg_set(phydev, 0x0FEA, 0x041600);
	अगर (err < 0)
		phydev_warn(phydev, "Failed to Set Register[0x0FEA]\n");

	/* Get access to Channel b'10, Node b'1101, Register 0x03.
	 * Write 24-bit value 0x000004 to रेजिस्टर. Setting TrFreeze bits.
	 */
	err = lan88xx_TR_reg_set(phydev, 0x1686, 0x000004);
	अगर (err < 0)
		phydev_warn(phydev, "Failed to Set Register[0x1686]\n");
पूर्ण

अटल पूर्णांक lan88xx_probe(काष्ठा phy_device *phydev)
अणु
	काष्ठा device *dev = &phydev->mdio.dev;
	काष्ठा lan88xx_priv *priv;
	u32 led_modes[4];
	पूर्णांक len;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->wolopts = 0;

	len = of_property_पढ़ो_variable_u32_array(dev->of_node,
						  "microchip,led-modes",
						  led_modes,
						  0,
						  ARRAY_SIZE(led_modes));
	अगर (len >= 0) अणु
		u32 reg = 0;
		पूर्णांक i;

		क्रम (i = 0; i < len; i++) अणु
			अगर (led_modes[i] > 15)
				वापस -EINVAL;
			reg |= led_modes[i] << (i * 4);
		पूर्ण
		क्रम (; i < ARRAY_SIZE(led_modes); i++)
			reg |= LAN78XX_FORCE_LED_OFF << (i * 4);
		(व्योम)phy_ग_लिखो(phydev, LAN78XX_PHY_LED_MODE_SELECT, reg);
	पूर्ण अन्यथा अगर (len == -EOVERFLOW) अणु
		वापस -EINVAL;
	पूर्ण

	/* these values can be used to identअगरy पूर्णांकernal PHY */
	priv->chip_id = phy_पढ़ो_mmd(phydev, 3, LAN88XX_MMD3_CHIP_ID);
	priv->chip_rev = phy_पढ़ो_mmd(phydev, 3, LAN88XX_MMD3_CHIP_REV);

	phydev->priv = priv;

	वापस 0;
पूर्ण

अटल व्योम lan88xx_हटाओ(काष्ठा phy_device *phydev)
अणु
	काष्ठा device *dev = &phydev->mdio.dev;
	काष्ठा lan88xx_priv *priv = phydev->priv;

	अगर (priv)
		devm_kमुक्त(dev, priv);
पूर्ण

अटल पूर्णांक lan88xx_set_wol(काष्ठा phy_device *phydev,
			   काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा lan88xx_priv *priv = phydev->priv;

	priv->wolopts = wol->wolopts;

	वापस 0;
पूर्ण

अटल व्योम lan88xx_set_mdix(काष्ठा phy_device *phydev)
अणु
	पूर्णांक buf;
	पूर्णांक val;

	चयन (phydev->mdix_ctrl) अणु
	हाल ETH_TP_MDI:
		val = LAN88XX_EXT_MODE_CTRL_MDI_;
		अवरोध;
	हाल ETH_TP_MDI_X:
		val = LAN88XX_EXT_MODE_CTRL_MDI_X_;
		अवरोध;
	हाल ETH_TP_MDI_AUTO:
		val = LAN88XX_EXT_MODE_CTRL_AUTO_MDIX_;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	phy_ग_लिखो(phydev, LAN88XX_EXT_PAGE_ACCESS, LAN88XX_EXT_PAGE_SPACE_1);
	buf = phy_पढ़ो(phydev, LAN88XX_EXT_MODE_CTRL);
	buf &= ~LAN88XX_EXT_MODE_CTRL_MDIX_MASK_;
	buf |= val;
	phy_ग_लिखो(phydev, LAN88XX_EXT_MODE_CTRL, buf);
	phy_ग_लिखो(phydev, LAN88XX_EXT_PAGE_ACCESS, LAN88XX_EXT_PAGE_SPACE_0);
पूर्ण

अटल पूर्णांक lan88xx_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक val;

	/*Zerodetect delay enable */
	val = phy_पढ़ो_mmd(phydev, MDIO_MMD_PCS,
			   PHY_ARDENNES_MMD_DEV_3_PHY_CFG);
	val |= PHY_ARDENNES_MMD_DEV_3_PHY_CFG_ZD_DLY_EN_;

	phy_ग_लिखो_mmd(phydev, MDIO_MMD_PCS, PHY_ARDENNES_MMD_DEV_3_PHY_CFG,
		      val);

	/* Config DSP रेजिस्टरs */
	lan88xx_config_TR_regs(phydev);

	वापस 0;
पूर्ण

अटल पूर्णांक lan88xx_config_aneg(काष्ठा phy_device *phydev)
अणु
	lan88xx_set_mdix(phydev);

	वापस genphy_config_aneg(phydev);
पूर्ण

अटल काष्ठा phy_driver microchip_phy_driver[] = अणु
अणु
	.phy_id		= 0x0007c130,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Microchip LAN88xx",

	/* PHY_GBIT_FEATURES */

	.probe		= lan88xx_probe,
	.हटाओ		= lan88xx_हटाओ,

	.config_init	= lan88xx_config_init,
	.config_aneg	= lan88xx_config_aneg,

	.config_पूर्णांकr	= lan88xx_phy_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = lan88xx_handle_पूर्णांकerrupt,

	.suspend	= lan88xx_suspend,
	.resume		= genphy_resume,
	.set_wol	= lan88xx_set_wol,
	.पढ़ो_page	= lan88xx_पढ़ो_page,
	.ग_लिखो_page	= lan88xx_ग_लिखो_page,
पूर्ण पूर्ण;

module_phy_driver(microchip_phy_driver);

अटल काष्ठा mdio_device_id __maybe_unused microchip_tbl[] = अणु
	अणु 0x0007c130, 0xfffffff0 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(mdio, microchip_tbl);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
