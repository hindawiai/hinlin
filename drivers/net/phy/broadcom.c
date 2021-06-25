<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *	drivers/net/phy/broadcom.c
 *
 *	Broadcom BCM5411, BCM5421 and BCM5461 Gigabit Ethernet
 *	transceivers.
 *
 *	Copyright (c) 2006  Maciej W. Rozycki
 *
 *	Inspired by code written by Amy Fong.
 */

#समावेश "bcm-phy-lib.h"
#समावेश <linux/module.h>
#समावेश <linux/phy.h>
#समावेश <linux/brcmphy.h>
#समावेश <linux/of.h>

#घोषणा BRCM_PHY_MODEL(phydev) \
	((phydev)->drv->phy_id & (phydev)->drv->phy_id_mask)

#घोषणा BRCM_PHY_REV(phydev) \
	((phydev)->drv->phy_id & ~((phydev)->drv->phy_id_mask))

MODULE_DESCRIPTION("Broadcom PHY driver");
MODULE_AUTHOR("Maciej W. Rozycki");
MODULE_LICENSE("GPL");

अटल पूर्णांक bcm54xx_config_घड़ी_delay(काष्ठा phy_device *phydev)
अणु
	पूर्णांक rc, val;

	/* handling PHY's पूर्णांकernal RX घड़ी delay */
	val = bcm54xx_auxctl_पढ़ो(phydev, MII_BCM54XX_AUXCTL_SHDWSEL_MISC);
	val |= MII_BCM54XX_AUXCTL_MISC_WREN;
	अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII ||
	    phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_TXID) अणु
		/* Disable RGMII RXC-RXD skew */
		val &= ~MII_BCM54XX_AUXCTL_SHDWSEL_MISC_RGMII_SKEW_EN;
	पूर्ण
	अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_ID ||
	    phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_RXID) अणु
		/* Enable RGMII RXC-RXD skew */
		val |= MII_BCM54XX_AUXCTL_SHDWSEL_MISC_RGMII_SKEW_EN;
	पूर्ण
	rc = bcm54xx_auxctl_ग_लिखो(phydev, MII_BCM54XX_AUXCTL_SHDWSEL_MISC,
				  val);
	अगर (rc < 0)
		वापस rc;

	/* handling PHY's पूर्णांकernal TX घड़ी delay */
	val = bcm_phy_पढ़ो_shaकरोw(phydev, BCM54810_SHD_CLK_CTL);
	अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII ||
	    phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_RXID) अणु
		/* Disable पूर्णांकernal TX घड़ी delay */
		val &= ~BCM54810_SHD_CLK_CTL_GTXCLK_EN;
	पूर्ण
	अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_ID ||
	    phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_TXID) अणु
		/* Enable पूर्णांकernal TX घड़ी delay */
		val |= BCM54810_SHD_CLK_CTL_GTXCLK_EN;
	पूर्ण
	rc = bcm_phy_ग_लिखो_shaकरोw(phydev, BCM54810_SHD_CLK_CTL, val);
	अगर (rc < 0)
		वापस rc;

	वापस 0;
पूर्ण

अटल पूर्णांक bcm54210e_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक val;

	bcm54xx_config_घड़ी_delay(phydev);

	अगर (phydev->dev_flags & PHY_BRCM_EN_MASTER_MODE) अणु
		val = phy_पढ़ो(phydev, MII_CTRL1000);
		val |= CTL1000_AS_MASTER | CTL1000_ENABLE_MASTER;
		phy_ग_लिखो(phydev, MII_CTRL1000, val);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bcm54612e_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक reg;

	bcm54xx_config_घड़ी_delay(phydev);

	/* Enable CLK125 MUX on LED4 अगर ref घड़ी is enabled. */
	अगर (!(phydev->dev_flags & PHY_BRCM_RX_REFCLK_UNUSED)) अणु
		पूर्णांक err;

		reg = bcm_phy_पढ़ो_exp(phydev, BCM54612E_EXP_SPARE0);
		err = bcm_phy_ग_लिखो_exp(phydev, BCM54612E_EXP_SPARE0,
					BCM54612E_LED4_CLK125OUT_EN | reg);

		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bcm54616s_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक rc, val;

	अगर (phydev->पूर्णांकerface != PHY_INTERFACE_MODE_SGMII &&
	    phydev->पूर्णांकerface != PHY_INTERFACE_MODE_1000BASEX)
		वापस 0;

	/* Ensure proper पूर्णांकerface mode is selected. */
	/* Disable RGMII mode */
	val = bcm54xx_auxctl_पढ़ो(phydev, MII_BCM54XX_AUXCTL_SHDWSEL_MISC);
	अगर (val < 0)
		वापस val;
	val &= ~MII_BCM54XX_AUXCTL_SHDWSEL_MISC_RGMII_EN;
	val |= MII_BCM54XX_AUXCTL_MISC_WREN;
	rc = bcm54xx_auxctl_ग_लिखो(phydev, MII_BCM54XX_AUXCTL_SHDWSEL_MISC,
				  val);
	अगर (rc < 0)
		वापस rc;

	/* Select 1000BASE-X रेजिस्टर set (primary SerDes) */
	val = bcm_phy_पढ़ो_shaकरोw(phydev, BCM54XX_SHD_MODE);
	अगर (val < 0)
		वापस val;
	val |= BCM54XX_SHD_MODE_1000BX;
	rc = bcm_phy_ग_लिखो_shaकरोw(phydev, BCM54XX_SHD_MODE, val);
	अगर (rc < 0)
		वापस rc;

	/* Power करोwn SerDes पूर्णांकerface */
	rc = phy_set_bits(phydev, MII_BMCR, BMCR_PDOWN);
	अगर (rc < 0)
		वापस rc;

	/* Select proper पूर्णांकerface mode */
	val &= ~BCM54XX_SHD_INTF_SEL_MASK;
	val |= phydev->पूर्णांकerface == PHY_INTERFACE_MODE_SGMII ?
		BCM54XX_SHD_INTF_SEL_SGMII :
		BCM54XX_SHD_INTF_SEL_GBIC;
	rc = bcm_phy_ग_लिखो_shaकरोw(phydev, BCM54XX_SHD_MODE, val);
	अगर (rc < 0)
		वापस rc;

	/* Power up SerDes पूर्णांकerface */
	rc = phy_clear_bits(phydev, MII_BMCR, BMCR_PDOWN);
	अगर (rc < 0)
		वापस rc;

	/* Select copper रेजिस्टर set */
	val &= ~BCM54XX_SHD_MODE_1000BX;
	rc = bcm_phy_ग_लिखो_shaकरोw(phydev, BCM54XX_SHD_MODE, val);
	अगर (rc < 0)
		वापस rc;

	/* Power up copper पूर्णांकerface */
	वापस phy_clear_bits(phydev, MII_BMCR, BMCR_PDOWN);
पूर्ण

/* Needs SMDSP घड़ी enabled via bcm54xx_phydsp_config() */
अटल पूर्णांक bcm50610_a0_workaround(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	err = bcm_phy_ग_लिखो_exp(phydev, MII_BCM54XX_EXP_AADJ1CH0,
				MII_BCM54XX_EXP_AADJ1CH0_SWP_ABCD_OEN |
				MII_BCM54XX_EXP_AADJ1CH0_SWSEL_THPF);
	अगर (err < 0)
		वापस err;

	err = bcm_phy_ग_लिखो_exp(phydev, MII_BCM54XX_EXP_AADJ1CH3,
				MII_BCM54XX_EXP_AADJ1CH3_ADCCKADJ);
	अगर (err < 0)
		वापस err;

	err = bcm_phy_ग_लिखो_exp(phydev, MII_BCM54XX_EXP_EXP75,
				MII_BCM54XX_EXP_EXP75_VDACCTRL);
	अगर (err < 0)
		वापस err;

	err = bcm_phy_ग_लिखो_exp(phydev, MII_BCM54XX_EXP_EXP96,
				MII_BCM54XX_EXP_EXP96_MYST);
	अगर (err < 0)
		वापस err;

	err = bcm_phy_ग_लिखो_exp(phydev, MII_BCM54XX_EXP_EXP97,
				MII_BCM54XX_EXP_EXP97_MYST);

	वापस err;
पूर्ण

अटल पूर्णांक bcm54xx_phydsp_config(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err, err2;

	/* Enable the SMDSP घड़ी */
	err = bcm54xx_auxctl_ग_लिखो(phydev,
				   MII_BCM54XX_AUXCTL_SHDWSEL_AUXCTL,
				   MII_BCM54XX_AUXCTL_ACTL_SMDSP_ENA |
				   MII_BCM54XX_AUXCTL_ACTL_TX_6DB);
	अगर (err < 0)
		वापस err;

	अगर (BRCM_PHY_MODEL(phydev) == PHY_ID_BCM50610 ||
	    BRCM_PHY_MODEL(phydev) == PHY_ID_BCM50610M) अणु
		/* Clear bit 9 to fix a phy पूर्णांकerop issue. */
		err = bcm_phy_ग_लिखो_exp(phydev, MII_BCM54XX_EXP_EXP08,
					MII_BCM54XX_EXP_EXP08_RJCT_2MHZ);
		अगर (err < 0)
			जाओ error;

		अगर (phydev->drv->phy_id == PHY_ID_BCM50610) अणु
			err = bcm50610_a0_workaround(phydev);
			अगर (err < 0)
				जाओ error;
		पूर्ण
	पूर्ण

	अगर (BRCM_PHY_MODEL(phydev) == PHY_ID_BCM57780) अणु
		पूर्णांक val;

		val = bcm_phy_पढ़ो_exp(phydev, MII_BCM54XX_EXP_EXP75);
		अगर (val < 0)
			जाओ error;

		val |= MII_BCM54XX_EXP_EXP75_CM_OSC;
		err = bcm_phy_ग_लिखो_exp(phydev, MII_BCM54XX_EXP_EXP75, val);
	पूर्ण

error:
	/* Disable the SMDSP घड़ी */
	err2 = bcm54xx_auxctl_ग_लिखो(phydev,
				    MII_BCM54XX_AUXCTL_SHDWSEL_AUXCTL,
				    MII_BCM54XX_AUXCTL_ACTL_TX_6DB);

	/* Return the first error reported. */
	वापस err ? err : err2;
पूर्ण

अटल व्योम bcm54xx_adjust_rxrefclk(काष्ठा phy_device *phydev)
अणु
	u32 orig;
	पूर्णांक val;
	bool clk125en = true;

	/* Abort अगर we are using an untested phy. */
	अगर (BRCM_PHY_MODEL(phydev) != PHY_ID_BCM57780 &&
	    BRCM_PHY_MODEL(phydev) != PHY_ID_BCM50610 &&
	    BRCM_PHY_MODEL(phydev) != PHY_ID_BCM50610M &&
	    BRCM_PHY_MODEL(phydev) != PHY_ID_BCM54210E &&
	    BRCM_PHY_MODEL(phydev) != PHY_ID_BCM54810 &&
	    BRCM_PHY_MODEL(phydev) != PHY_ID_BCM54811)
		वापस;

	val = bcm_phy_पढ़ो_shaकरोw(phydev, BCM54XX_SHD_SCR3);
	अगर (val < 0)
		वापस;

	orig = val;

	अगर ((BRCM_PHY_MODEL(phydev) == PHY_ID_BCM50610 ||
	     BRCM_PHY_MODEL(phydev) == PHY_ID_BCM50610M) &&
	    BRCM_PHY_REV(phydev) >= 0x3) अणु
		/*
		 * Here, bit 0 _disables_ CLK125 when set.
		 * This bit is set by शेष.
		 */
		clk125en = false;
	पूर्ण अन्यथा अणु
		अगर (phydev->dev_flags & PHY_BRCM_RX_REFCLK_UNUSED) अणु
			अगर (BRCM_PHY_MODEL(phydev) != PHY_ID_BCM54811) अणु
				/* Here, bit 0 _enables_ CLK125 when set */
				val &= ~BCM54XX_SHD_SCR3_DEF_CLK125;
			पूर्ण
			clk125en = false;
		पूर्ण
	पूर्ण

	अगर (!clk125en || (phydev->dev_flags & PHY_BRCM_AUTO_PWRDWN_ENABLE))
		val &= ~BCM54XX_SHD_SCR3_DLLAPD_DIS;
	अन्यथा
		val |= BCM54XX_SHD_SCR3_DLLAPD_DIS;

	अगर (phydev->dev_flags & PHY_BRCM_DIS_TXCRXC_NOENRGY) अणु
		अगर (BRCM_PHY_MODEL(phydev) == PHY_ID_BCM54210E ||
		    BRCM_PHY_MODEL(phydev) == PHY_ID_BCM54810 ||
		    BRCM_PHY_MODEL(phydev) == PHY_ID_BCM54210E)
			val |= BCM54XX_SHD_SCR3_RXCTXC_DIS;
		अन्यथा
			val |= BCM54XX_SHD_SCR3_TRDDAPD;
	पूर्ण

	अगर (orig != val)
		bcm_phy_ग_लिखो_shaकरोw(phydev, BCM54XX_SHD_SCR3, val);

	val = bcm_phy_पढ़ो_shaकरोw(phydev, BCM54XX_SHD_APD);
	अगर (val < 0)
		वापस;

	orig = val;

	अगर (!clk125en || (phydev->dev_flags & PHY_BRCM_AUTO_PWRDWN_ENABLE))
		val |= BCM54XX_SHD_APD_EN;
	अन्यथा
		val &= ~BCM54XX_SHD_APD_EN;

	अगर (orig != val)
		bcm_phy_ग_लिखो_shaकरोw(phydev, BCM54XX_SHD_APD, val);
पूर्ण

अटल पूर्णांक bcm54xx_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक reg, err, val;

	reg = phy_पढ़ो(phydev, MII_BCM54XX_ECR);
	अगर (reg < 0)
		वापस reg;

	/* Mask पूर्णांकerrupts globally.  */
	reg |= MII_BCM54XX_ECR_IM;
	err = phy_ग_लिखो(phydev, MII_BCM54XX_ECR, reg);
	अगर (err < 0)
		वापस err;

	/* Unmask events we are पूर्णांकerested in.  */
	reg = ~(MII_BCM54XX_INT_DUPLEX |
		MII_BCM54XX_INT_SPEED |
		MII_BCM54XX_INT_LINK);
	err = phy_ग_लिखो(phydev, MII_BCM54XX_IMR, reg);
	अगर (err < 0)
		वापस err;

	अगर ((BRCM_PHY_MODEL(phydev) == PHY_ID_BCM50610 ||
	     BRCM_PHY_MODEL(phydev) == PHY_ID_BCM50610M) &&
	    (phydev->dev_flags & PHY_BRCM_CLEAR_RGMII_MODE))
		bcm_phy_ग_लिखो_shaकरोw(phydev, BCM54XX_SHD_RGMII_MODE, 0);

	bcm54xx_adjust_rxrefclk(phydev);

	चयन (BRCM_PHY_MODEL(phydev)) अणु
	हाल PHY_ID_BCM50610:
	हाल PHY_ID_BCM50610M:
		err = bcm54xx_config_घड़ी_delay(phydev);
		अवरोध;
	हाल PHY_ID_BCM54210E:
		err = bcm54210e_config_init(phydev);
		अवरोध;
	हाल PHY_ID_BCM54612E:
		err = bcm54612e_config_init(phydev);
		अवरोध;
	हाल PHY_ID_BCM54616S:
		err = bcm54616s_config_init(phydev);
		अवरोध;
	हाल PHY_ID_BCM54810:
		/* For BCM54810, we need to disable BroadR-Reach function */
		val = bcm_phy_पढ़ो_exp(phydev,
				       BCM54810_EXP_BROADREACH_LRE_MISC_CTL);
		val &= ~BCM54810_EXP_BROADREACH_LRE_MISC_CTL_EN;
		err = bcm_phy_ग_लिखो_exp(phydev,
					BCM54810_EXP_BROADREACH_LRE_MISC_CTL,
					val);
		अवरोध;
	पूर्ण
	अगर (err)
		वापस err;

	bcm54xx_phydsp_config(phydev);

	/* For non-SFP setups, encode link speed पूर्णांकo LED1 and LED3 pair
	 * (green/amber).
	 * Also flash these two LEDs on activity. This means configuring
	 * them क्रम MULTICOLOR and encoding link/activity पूर्णांकo them.
	 * Don't करो this क्रम devices on an SFP module, since some of these
	 * use the LED outमाला_दो to control the SFP LOS संकेत, and changing
	 * these settings will cause LOS to malfunction.
	 */
	अगर (!phy_on_sfp(phydev)) अणु
		val = BCM5482_SHD_LEDS1_LED1(BCM_LED_SRC_MULTICOLOR1) |
			BCM5482_SHD_LEDS1_LED3(BCM_LED_SRC_MULTICOLOR1);
		bcm_phy_ग_लिखो_shaकरोw(phydev, BCM5482_SHD_LEDS1, val);

		val = BCM_LED_MULTICOLOR_IN_PHASE |
			BCM5482_SHD_LEDS1_LED1(BCM_LED_MULTICOLOR_LINK_ACT) |
			BCM5482_SHD_LEDS1_LED3(BCM_LED_MULTICOLOR_LINK_ACT);
		bcm_phy_ग_लिखो_exp(phydev, BCM_EXP_MULTICOLOR, val);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bcm54xx_resume(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	/* Writes to रेजिस्टर other than BMCR would be ignored
	 * unless we clear the PDOWN bit first
	 */
	ret = genphy_resume(phydev);
	अगर (ret < 0)
		वापस ret;

	/* Upon निकासing घातer करोwn, the PHY reमुख्यs in an पूर्णांकernal reset state
	 * क्रम 40us
	 */
	fsleep(40);

	वापस bcm54xx_config_init(phydev);
पूर्ण

अटल पूर्णांक bcm54811_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err, reg;

	/* Disable BroadR-Reach function. */
	reg = bcm_phy_पढ़ो_exp(phydev, BCM54810_EXP_BROADREACH_LRE_MISC_CTL);
	reg &= ~BCM54810_EXP_BROADREACH_LRE_MISC_CTL_EN;
	err = bcm_phy_ग_लिखो_exp(phydev, BCM54810_EXP_BROADREACH_LRE_MISC_CTL,
				reg);
	अगर (err < 0)
		वापस err;

	err = bcm54xx_config_init(phydev);

	/* Enable CLK125 MUX on LED4 अगर ref घड़ी is enabled. */
	अगर (!(phydev->dev_flags & PHY_BRCM_RX_REFCLK_UNUSED)) अणु
		reg = bcm_phy_पढ़ो_exp(phydev, BCM54612E_EXP_SPARE0);
		err = bcm_phy_ग_लिखो_exp(phydev, BCM54612E_EXP_SPARE0,
					BCM54612E_LED4_CLK125OUT_EN | reg);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक bcm5481_config_aneg(काष्ठा phy_device *phydev)
अणु
	काष्ठा device_node *np = phydev->mdio.dev.of_node;
	पूर्णांक ret;

	/* Aneg firstly. */
	ret = genphy_config_aneg(phydev);

	/* Then we can set up the delay. */
	bcm54xx_config_घड़ी_delay(phydev);

	अगर (of_property_पढ़ो_bool(np, "enet-phy-lane-swap")) अणु
		/* Lane Swap - Unकरोcumented रेजिस्टर...magic! */
		ret = bcm_phy_ग_लिखो_exp(phydev, MII_BCM54XX_EXP_SEL_ER + 0x9,
					0x11B);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

काष्ठा bcm54616s_phy_priv अणु
	bool mode_1000bx_en;
पूर्ण;

अटल पूर्णांक bcm54616s_probe(काष्ठा phy_device *phydev)
अणु
	काष्ठा bcm54616s_phy_priv *priv;
	पूर्णांक val;

	priv = devm_kzalloc(&phydev->mdio.dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	phydev->priv = priv;

	val = bcm_phy_पढ़ो_shaकरोw(phydev, BCM54XX_SHD_MODE);
	अगर (val < 0)
		वापस val;

	/* The PHY is strapped in RGMII-fiber mode when INTERF_SEL[1:0]
	 * is 01b, and the link between PHY and its link partner can be
	 * either 1000Base-X or 100Base-FX.
	 * RGMII-1000Base-X is properly supported, but RGMII-100Base-FX
	 * support is still missing as of now.
	 */
	अगर ((val & BCM54XX_SHD_INTF_SEL_MASK) == BCM54XX_SHD_INTF_SEL_RGMII) अणु
		val = bcm_phy_पढ़ो_shaकरोw(phydev, BCM54616S_SHD_100FX_CTRL);
		अगर (val < 0)
			वापस val;

		/* Bit 0 of the SerDes 100-FX Control रेजिस्टर, when set
		 * to 1, sets the MII/RGMII -> 100BASE-FX configuration.
		 * When this bit is set to 0, it sets the GMII/RGMII ->
		 * 1000BASE-X configuration.
		 */
		अगर (!(val & BCM54616S_100FX_MODE))
			priv->mode_1000bx_en = true;

		phydev->port = PORT_FIBRE;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bcm54616s_config_aneg(काष्ठा phy_device *phydev)
अणु
	काष्ठा bcm54616s_phy_priv *priv = phydev->priv;
	पूर्णांक ret;

	/* Aneg firstly. */
	अगर (priv->mode_1000bx_en)
		ret = genphy_c37_config_aneg(phydev);
	अन्यथा
		ret = genphy_config_aneg(phydev);

	/* Then we can set up the delay. */
	bcm54xx_config_घड़ी_delay(phydev);

	वापस ret;
पूर्ण

अटल पूर्णांक bcm54616s_पढ़ो_status(काष्ठा phy_device *phydev)
अणु
	काष्ठा bcm54616s_phy_priv *priv = phydev->priv;
	पूर्णांक err;

	अगर (priv->mode_1000bx_en)
		err = genphy_c37_पढ़ो_status(phydev);
	अन्यथा
		err = genphy_पढ़ो_status(phydev);

	वापस err;
पूर्ण

अटल पूर्णांक brcm_phy_setbits(काष्ठा phy_device *phydev, पूर्णांक reg, पूर्णांक set)
अणु
	पूर्णांक val;

	val = phy_पढ़ो(phydev, reg);
	अगर (val < 0)
		वापस val;

	वापस phy_ग_लिखो(phydev, reg, val | set);
पूर्ण

अटल पूर्णांक brcm_fet_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक reg, err, err2, brcmtest;

	/* Reset the PHY to bring it to a known state. */
	err = phy_ग_लिखो(phydev, MII_BMCR, BMCR_RESET);
	अगर (err < 0)
		वापस err;

	reg = phy_पढ़ो(phydev, MII_BRCM_FET_INTREG);
	अगर (reg < 0)
		वापस reg;

	/* Unmask events we are पूर्णांकerested in and mask पूर्णांकerrupts globally. */
	reg = MII_BRCM_FET_IR_DUPLEX_EN |
	      MII_BRCM_FET_IR_SPEED_EN |
	      MII_BRCM_FET_IR_LINK_EN |
	      MII_BRCM_FET_IR_ENABLE |
	      MII_BRCM_FET_IR_MASK;

	err = phy_ग_लिखो(phydev, MII_BRCM_FET_INTREG, reg);
	अगर (err < 0)
		वापस err;

	/* Enable shaकरोw रेजिस्टर access */
	brcmtest = phy_पढ़ो(phydev, MII_BRCM_FET_BRCMTEST);
	अगर (brcmtest < 0)
		वापस brcmtest;

	reg = brcmtest | MII_BRCM_FET_BT_SRE;

	err = phy_ग_लिखो(phydev, MII_BRCM_FET_BRCMTEST, reg);
	अगर (err < 0)
		वापस err;

	/* Set the LED mode */
	reg = phy_पढ़ो(phydev, MII_BRCM_FET_SHDW_AUXMODE4);
	अगर (reg < 0) अणु
		err = reg;
		जाओ करोne;
	पूर्ण

	reg &= ~MII_BRCM_FET_SHDW_AM4_LED_MASK;
	reg |= MII_BRCM_FET_SHDW_AM4_LED_MODE1;

	err = phy_ग_लिखो(phydev, MII_BRCM_FET_SHDW_AUXMODE4, reg);
	अगर (err < 0)
		जाओ करोne;

	/* Enable स्वतः MDIX */
	err = brcm_phy_setbits(phydev, MII_BRCM_FET_SHDW_MISCCTRL,
				       MII_BRCM_FET_SHDW_MC_FAME);
	अगर (err < 0)
		जाओ करोne;

	अगर (phydev->dev_flags & PHY_BRCM_AUTO_PWRDWN_ENABLE) अणु
		/* Enable स्वतः घातer करोwn */
		err = brcm_phy_setbits(phydev, MII_BRCM_FET_SHDW_AUXSTAT2,
					       MII_BRCM_FET_SHDW_AS2_APDE);
	पूर्ण

करोne:
	/* Disable shaकरोw रेजिस्टर access */
	err2 = phy_ग_लिखो(phydev, MII_BRCM_FET_BRCMTEST, brcmtest);
	अगर (!err)
		err = err2;

	वापस err;
पूर्ण

अटल पूर्णांक brcm_fet_ack_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक reg;

	/* Clear pending पूर्णांकerrupts.  */
	reg = phy_पढ़ो(phydev, MII_BRCM_FET_INTREG);
	अगर (reg < 0)
		वापस reg;

	वापस 0;
पूर्ण

अटल पूर्णांक brcm_fet_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	पूर्णांक reg, err;

	reg = phy_पढ़ो(phydev, MII_BRCM_FET_INTREG);
	अगर (reg < 0)
		वापस reg;

	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED) अणु
		err = brcm_fet_ack_पूर्णांकerrupt(phydev);
		अगर (err)
			वापस err;

		reg &= ~MII_BRCM_FET_IR_MASK;
		err = phy_ग_लिखो(phydev, MII_BRCM_FET_INTREG, reg);
	पूर्ण अन्यथा अणु
		reg |= MII_BRCM_FET_IR_MASK;
		err = phy_ग_लिखो(phydev, MII_BRCM_FET_INTREG, reg);
		अगर (err)
			वापस err;

		err = brcm_fet_ack_पूर्णांकerrupt(phydev);
	पूर्ण

	वापस err;
पूर्ण

अटल irqवापस_t brcm_fet_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक irq_status;

	irq_status = phy_पढ़ो(phydev, MII_BRCM_FET_INTREG);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	अगर (irq_status == 0)
		वापस IRQ_NONE;

	phy_trigger_machine(phydev);

	वापस IRQ_HANDLED;
पूर्ण

काष्ठा bcm54xx_phy_priv अणु
	u64	*stats;
पूर्ण;

अटल पूर्णांक bcm54xx_phy_probe(काष्ठा phy_device *phydev)
अणु
	काष्ठा bcm54xx_phy_priv *priv;

	priv = devm_kzalloc(&phydev->mdio.dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	phydev->priv = priv;

	priv->stats = devm_kसुस्मृति(&phydev->mdio.dev,
				   bcm_phy_get_sset_count(phydev), माप(u64),
				   GFP_KERNEL);
	अगर (!priv->stats)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम bcm54xx_get_stats(काष्ठा phy_device *phydev,
			      काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा bcm54xx_phy_priv *priv = phydev->priv;

	bcm_phy_get_stats(phydev, priv->stats, stats, data);
पूर्ण

अटल काष्ठा phy_driver broadcom_drivers[] = अणु
अणु
	.phy_id		= PHY_ID_BCM5411,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Broadcom BCM5411",
	/* PHY_GBIT_FEATURES */
	.get_sset_count	= bcm_phy_get_sset_count,
	.get_strings	= bcm_phy_get_strings,
	.get_stats	= bcm54xx_get_stats,
	.probe		= bcm54xx_phy_probe,
	.config_init	= bcm54xx_config_init,
	.config_पूर्णांकr	= bcm_phy_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = bcm_phy_handle_पूर्णांकerrupt,
पूर्ण, अणु
	.phy_id		= PHY_ID_BCM5421,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Broadcom BCM5421",
	/* PHY_GBIT_FEATURES */
	.get_sset_count	= bcm_phy_get_sset_count,
	.get_strings	= bcm_phy_get_strings,
	.get_stats	= bcm54xx_get_stats,
	.probe		= bcm54xx_phy_probe,
	.config_init	= bcm54xx_config_init,
	.config_पूर्णांकr	= bcm_phy_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = bcm_phy_handle_पूर्णांकerrupt,
पूर्ण, अणु
	.phy_id		= PHY_ID_BCM54210E,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Broadcom BCM54210E",
	/* PHY_GBIT_FEATURES */
	.get_sset_count	= bcm_phy_get_sset_count,
	.get_strings	= bcm_phy_get_strings,
	.get_stats	= bcm54xx_get_stats,
	.probe		= bcm54xx_phy_probe,
	.config_init	= bcm54xx_config_init,
	.config_पूर्णांकr	= bcm_phy_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = bcm_phy_handle_पूर्णांकerrupt,
पूर्ण, अणु
	.phy_id		= PHY_ID_BCM5461,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Broadcom BCM5461",
	/* PHY_GBIT_FEATURES */
	.get_sset_count	= bcm_phy_get_sset_count,
	.get_strings	= bcm_phy_get_strings,
	.get_stats	= bcm54xx_get_stats,
	.probe		= bcm54xx_phy_probe,
	.config_init	= bcm54xx_config_init,
	.config_पूर्णांकr	= bcm_phy_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = bcm_phy_handle_पूर्णांकerrupt,
पूर्ण, अणु
	.phy_id		= PHY_ID_BCM54612E,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Broadcom BCM54612E",
	/* PHY_GBIT_FEATURES */
	.get_sset_count	= bcm_phy_get_sset_count,
	.get_strings	= bcm_phy_get_strings,
	.get_stats	= bcm54xx_get_stats,
	.probe		= bcm54xx_phy_probe,
	.config_init	= bcm54xx_config_init,
	.config_पूर्णांकr	= bcm_phy_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = bcm_phy_handle_पूर्णांकerrupt,
पूर्ण, अणु
	.phy_id		= PHY_ID_BCM54616S,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Broadcom BCM54616S",
	/* PHY_GBIT_FEATURES */
	.config_init	= bcm54xx_config_init,
	.config_aneg	= bcm54616s_config_aneg,
	.config_पूर्णांकr	= bcm_phy_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = bcm_phy_handle_पूर्णांकerrupt,
	.पढ़ो_status	= bcm54616s_पढ़ो_status,
	.probe		= bcm54616s_probe,
पूर्ण, अणु
	.phy_id		= PHY_ID_BCM5464,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Broadcom BCM5464",
	/* PHY_GBIT_FEATURES */
	.get_sset_count	= bcm_phy_get_sset_count,
	.get_strings	= bcm_phy_get_strings,
	.get_stats	= bcm54xx_get_stats,
	.probe		= bcm54xx_phy_probe,
	.config_init	= bcm54xx_config_init,
	.config_पूर्णांकr	= bcm_phy_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = bcm_phy_handle_पूर्णांकerrupt,
	.suspend	= genphy_suspend,
	.resume		= genphy_resume,
पूर्ण, अणु
	.phy_id		= PHY_ID_BCM5481,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Broadcom BCM5481",
	/* PHY_GBIT_FEATURES */
	.get_sset_count	= bcm_phy_get_sset_count,
	.get_strings	= bcm_phy_get_strings,
	.get_stats	= bcm54xx_get_stats,
	.probe		= bcm54xx_phy_probe,
	.config_init	= bcm54xx_config_init,
	.config_aneg	= bcm5481_config_aneg,
	.config_पूर्णांकr	= bcm_phy_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = bcm_phy_handle_पूर्णांकerrupt,
पूर्ण, अणु
	.phy_id         = PHY_ID_BCM54810,
	.phy_id_mask    = 0xfffffff0,
	.name           = "Broadcom BCM54810",
	/* PHY_GBIT_FEATURES */
	.get_sset_count	= bcm_phy_get_sset_count,
	.get_strings	= bcm_phy_get_strings,
	.get_stats	= bcm54xx_get_stats,
	.probe		= bcm54xx_phy_probe,
	.config_init    = bcm54xx_config_init,
	.config_aneg    = bcm5481_config_aneg,
	.config_पूर्णांकr    = bcm_phy_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = bcm_phy_handle_पूर्णांकerrupt,
	.suspend	= genphy_suspend,
	.resume		= bcm54xx_resume,
पूर्ण, अणु
	.phy_id         = PHY_ID_BCM54811,
	.phy_id_mask    = 0xfffffff0,
	.name           = "Broadcom BCM54811",
	/* PHY_GBIT_FEATURES */
	.get_sset_count	= bcm_phy_get_sset_count,
	.get_strings	= bcm_phy_get_strings,
	.get_stats	= bcm54xx_get_stats,
	.probe		= bcm54xx_phy_probe,
	.config_init    = bcm54811_config_init,
	.config_aneg    = bcm5481_config_aneg,
	.config_पूर्णांकr    = bcm_phy_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = bcm_phy_handle_पूर्णांकerrupt,
	.suspend	= genphy_suspend,
	.resume		= bcm54xx_resume,
पूर्ण, अणु
	.phy_id		= PHY_ID_BCM5482,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Broadcom BCM5482",
	/* PHY_GBIT_FEATURES */
	.get_sset_count	= bcm_phy_get_sset_count,
	.get_strings	= bcm_phy_get_strings,
	.get_stats	= bcm54xx_get_stats,
	.probe		= bcm54xx_phy_probe,
	.config_init	= bcm54xx_config_init,
	.config_पूर्णांकr	= bcm_phy_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = bcm_phy_handle_पूर्णांकerrupt,
पूर्ण, अणु
	.phy_id		= PHY_ID_BCM50610,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Broadcom BCM50610",
	/* PHY_GBIT_FEATURES */
	.get_sset_count	= bcm_phy_get_sset_count,
	.get_strings	= bcm_phy_get_strings,
	.get_stats	= bcm54xx_get_stats,
	.probe		= bcm54xx_phy_probe,
	.config_init	= bcm54xx_config_init,
	.config_पूर्णांकr	= bcm_phy_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = bcm_phy_handle_पूर्णांकerrupt,
पूर्ण, अणु
	.phy_id		= PHY_ID_BCM50610M,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Broadcom BCM50610M",
	/* PHY_GBIT_FEATURES */
	.get_sset_count	= bcm_phy_get_sset_count,
	.get_strings	= bcm_phy_get_strings,
	.get_stats	= bcm54xx_get_stats,
	.probe		= bcm54xx_phy_probe,
	.config_init	= bcm54xx_config_init,
	.config_पूर्णांकr	= bcm_phy_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = bcm_phy_handle_पूर्णांकerrupt,
पूर्ण, अणु
	.phy_id		= PHY_ID_BCM57780,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Broadcom BCM57780",
	/* PHY_GBIT_FEATURES */
	.get_sset_count	= bcm_phy_get_sset_count,
	.get_strings	= bcm_phy_get_strings,
	.get_stats	= bcm54xx_get_stats,
	.probe		= bcm54xx_phy_probe,
	.config_init	= bcm54xx_config_init,
	.config_पूर्णांकr	= bcm_phy_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = bcm_phy_handle_पूर्णांकerrupt,
पूर्ण, अणु
	.phy_id		= PHY_ID_BCMAC131,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Broadcom BCMAC131",
	/* PHY_BASIC_FEATURES */
	.config_init	= brcm_fet_config_init,
	.config_पूर्णांकr	= brcm_fet_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = brcm_fet_handle_पूर्णांकerrupt,
पूर्ण, अणु
	.phy_id		= PHY_ID_BCM5241,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Broadcom BCM5241",
	/* PHY_BASIC_FEATURES */
	.config_init	= brcm_fet_config_init,
	.config_पूर्णांकr	= brcm_fet_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = brcm_fet_handle_पूर्णांकerrupt,
पूर्ण, अणु
	.phy_id		= PHY_ID_BCM5395,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Broadcom BCM5395",
	.flags		= PHY_IS_INTERNAL,
	/* PHY_GBIT_FEATURES */
	.get_sset_count	= bcm_phy_get_sset_count,
	.get_strings	= bcm_phy_get_strings,
	.get_stats	= bcm54xx_get_stats,
	.probe		= bcm54xx_phy_probe,
पूर्ण, अणु
	.phy_id		= PHY_ID_BCM53125,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Broadcom BCM53125",
	.flags		= PHY_IS_INTERNAL,
	/* PHY_GBIT_FEATURES */
	.get_sset_count	= bcm_phy_get_sset_count,
	.get_strings	= bcm_phy_get_strings,
	.get_stats	= bcm54xx_get_stats,
	.probe		= bcm54xx_phy_probe,
	.config_init	= bcm54xx_config_init,
	.config_पूर्णांकr	= bcm_phy_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = bcm_phy_handle_पूर्णांकerrupt,
पूर्ण, अणु
	.phy_id         = PHY_ID_BCM89610,
	.phy_id_mask    = 0xfffffff0,
	.name           = "Broadcom BCM89610",
	/* PHY_GBIT_FEATURES */
	.get_sset_count	= bcm_phy_get_sset_count,
	.get_strings	= bcm_phy_get_strings,
	.get_stats	= bcm54xx_get_stats,
	.probe		= bcm54xx_phy_probe,
	.config_init    = bcm54xx_config_init,
	.config_पूर्णांकr    = bcm_phy_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = bcm_phy_handle_पूर्णांकerrupt,
पूर्ण पूर्ण;

module_phy_driver(broadcom_drivers);

अटल काष्ठा mdio_device_id __maybe_unused broadcom_tbl[] = अणु
	अणु PHY_ID_BCM5411, 0xfffffff0 पूर्ण,
	अणु PHY_ID_BCM5421, 0xfffffff0 पूर्ण,
	अणु PHY_ID_BCM54210E, 0xfffffff0 पूर्ण,
	अणु PHY_ID_BCM5461, 0xfffffff0 पूर्ण,
	अणु PHY_ID_BCM54612E, 0xfffffff0 पूर्ण,
	अणु PHY_ID_BCM54616S, 0xfffffff0 पूर्ण,
	अणु PHY_ID_BCM5464, 0xfffffff0 पूर्ण,
	अणु PHY_ID_BCM5481, 0xfffffff0 पूर्ण,
	अणु PHY_ID_BCM54810, 0xfffffff0 पूर्ण,
	अणु PHY_ID_BCM54811, 0xfffffff0 पूर्ण,
	अणु PHY_ID_BCM5482, 0xfffffff0 पूर्ण,
	अणु PHY_ID_BCM50610, 0xfffffff0 पूर्ण,
	अणु PHY_ID_BCM50610M, 0xfffffff0 पूर्ण,
	अणु PHY_ID_BCM57780, 0xfffffff0 पूर्ण,
	अणु PHY_ID_BCMAC131, 0xfffffff0 पूर्ण,
	अणु PHY_ID_BCM5241, 0xfffffff0 पूर्ण,
	अणु PHY_ID_BCM5395, 0xfffffff0 पूर्ण,
	अणु PHY_ID_BCM53125, 0xfffffff0 पूर्ण,
	अणु PHY_ID_BCM89610, 0xfffffff0 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(mdio, broadcom_tbl);
