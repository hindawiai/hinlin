<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * drivers/net/phy/at803x.c
 *
 * Driver क्रम Qualcomm Atheros AR803x PHY
 *
 * Author: Matus Ujhelyi <ujhelyi.m@gmail.com>
 */

#समावेश <linux/phy.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool_netlink.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/bitfield.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <dt-bindings/net/qca-ar803x.h>

#घोषणा AT803X_SPECIFIC_FUNCTION_CONTROL	0x10
#घोषणा AT803X_SFC_ASSERT_CRS			BIT(11)
#घोषणा AT803X_SFC_FORCE_LINK			BIT(10)
#घोषणा AT803X_SFC_MDI_CROSSOVER_MODE_M		GENMASK(6, 5)
#घोषणा AT803X_SFC_AUTOMATIC_CROSSOVER		0x3
#घोषणा AT803X_SFC_MANUAL_MDIX			0x1
#घोषणा AT803X_SFC_MANUAL_MDI			0x0
#घोषणा AT803X_SFC_SQE_TEST			BIT(2)
#घोषणा AT803X_SFC_POLARITY_REVERSAL		BIT(1)
#घोषणा AT803X_SFC_DISABLE_JABBER		BIT(0)

#घोषणा AT803X_SPECIFIC_STATUS			0x11
#घोषणा AT803X_SS_SPEED_MASK			(3 << 14)
#घोषणा AT803X_SS_SPEED_1000			(2 << 14)
#घोषणा AT803X_SS_SPEED_100			(1 << 14)
#घोषणा AT803X_SS_SPEED_10			(0 << 14)
#घोषणा AT803X_SS_DUPLEX			BIT(13)
#घोषणा AT803X_SS_SPEED_DUPLEX_RESOLVED		BIT(11)
#घोषणा AT803X_SS_MDIX				BIT(6)

#घोषणा AT803X_INTR_ENABLE			0x12
#घोषणा AT803X_INTR_ENABLE_AUTONEG_ERR		BIT(15)
#घोषणा AT803X_INTR_ENABLE_SPEED_CHANGED	BIT(14)
#घोषणा AT803X_INTR_ENABLE_DUPLEX_CHANGED	BIT(13)
#घोषणा AT803X_INTR_ENABLE_PAGE_RECEIVED	BIT(12)
#घोषणा AT803X_INTR_ENABLE_LINK_FAIL		BIT(11)
#घोषणा AT803X_INTR_ENABLE_LINK_SUCCESS		BIT(10)
#घोषणा AT803X_INTR_ENABLE_WIRESPEED_DOWNGRADE	BIT(5)
#घोषणा AT803X_INTR_ENABLE_POLARITY_CHANGED	BIT(1)
#घोषणा AT803X_INTR_ENABLE_WOL			BIT(0)

#घोषणा AT803X_INTR_STATUS			0x13

#घोषणा AT803X_SMART_SPEED			0x14
#घोषणा AT803X_SMART_SPEED_ENABLE		BIT(5)
#घोषणा AT803X_SMART_SPEED_RETRY_LIMIT_MASK	GENMASK(4, 2)
#घोषणा AT803X_SMART_SPEED_BYPASS_TIMER		BIT(1)
#घोषणा AT803X_CDT				0x16
#घोषणा AT803X_CDT_MDI_PAIR_MASK		GENMASK(9, 8)
#घोषणा AT803X_CDT_ENABLE_TEST			BIT(0)
#घोषणा AT803X_CDT_STATUS			0x1c
#घोषणा AT803X_CDT_STATUS_STAT_NORMAL		0
#घोषणा AT803X_CDT_STATUS_STAT_SHORT		1
#घोषणा AT803X_CDT_STATUS_STAT_OPEN		2
#घोषणा AT803X_CDT_STATUS_STAT_FAIL		3
#घोषणा AT803X_CDT_STATUS_STAT_MASK		GENMASK(9, 8)
#घोषणा AT803X_CDT_STATUS_DELTA_TIME_MASK	GENMASK(7, 0)
#घोषणा AT803X_LED_CONTROL			0x18

#घोषणा AT803X_DEVICE_ADDR			0x03
#घोषणा AT803X_LOC_MAC_ADDR_0_15_OFFSET		0x804C
#घोषणा AT803X_LOC_MAC_ADDR_16_31_OFFSET	0x804B
#घोषणा AT803X_LOC_MAC_ADDR_32_47_OFFSET	0x804A
#घोषणा AT803X_REG_CHIP_CONFIG			0x1f
#घोषणा AT803X_BT_BX_REG_SEL			0x8000

#घोषणा AT803X_DEBUG_ADDR			0x1D
#घोषणा AT803X_DEBUG_DATA			0x1E

#घोषणा AT803X_MODE_CFG_MASK			0x0F
#घोषणा AT803X_MODE_CFG_SGMII			0x01

#घोषणा AT803X_PSSR			0x11	/*PHY-Specअगरic Status Register*/
#घोषणा AT803X_PSSR_MR_AN_COMPLETE	0x0200

#घोषणा AT803X_DEBUG_REG_0			0x00
#घोषणा AT803X_DEBUG_RX_CLK_DLY_EN		BIT(15)

#घोषणा AT803X_DEBUG_REG_5			0x05
#घोषणा AT803X_DEBUG_TX_CLK_DLY_EN		BIT(8)

#घोषणा AT803X_DEBUG_REG_1F			0x1F
#घोषणा AT803X_DEBUG_PLL_ON			BIT(2)
#घोषणा AT803X_DEBUG_RGMII_1V8			BIT(3)

/* AT803x supports either the XTAL input pad, an पूर्णांकernal PLL or the
 * DSP as घड़ी reference क्रम the घड़ी output pad. The XTAL reference
 * is only used क्रम 25 MHz output, all other frequencies need the PLL.
 * The DSP as a घड़ी reference is used in synchronous ethernet
 * applications.
 *
 * By शेष the PLL is only enabled अगर there is a link. Otherwise
 * the PHY will go पूर्णांकo low घातer state and disabled the PLL. You can
 * set the PLL_ON bit (see debug रेजिस्टर 0x1f) to keep the PLL always
 * enabled.
 */
#घोषणा AT803X_MMD7_CLK25M			0x8016
#घोषणा AT803X_CLK_OUT_MASK			GENMASK(4, 2)
#घोषणा AT803X_CLK_OUT_25MHZ_XTAL		0
#घोषणा AT803X_CLK_OUT_25MHZ_DSP		1
#घोषणा AT803X_CLK_OUT_50MHZ_PLL		2
#घोषणा AT803X_CLK_OUT_50MHZ_DSP		3
#घोषणा AT803X_CLK_OUT_62_5MHZ_PLL		4
#घोषणा AT803X_CLK_OUT_62_5MHZ_DSP		5
#घोषणा AT803X_CLK_OUT_125MHZ_PLL		6
#घोषणा AT803X_CLK_OUT_125MHZ_DSP		7

/* The AR8035 has another mask which is compatible with the AR8031/AR8033 mask
 * but करोesn't support choosing between XTAL/PLL and DSP.
 */
#घोषणा AT8035_CLK_OUT_MASK			GENMASK(4, 3)

#घोषणा AT803X_CLK_OUT_STRENGTH_MASK		GENMASK(8, 7)
#घोषणा AT803X_CLK_OUT_STRENGTH_FULL		0
#घोषणा AT803X_CLK_OUT_STRENGTH_HALF		1
#घोषणा AT803X_CLK_OUT_STRENGTH_QUARTER		2

#घोषणा AT803X_DEFAULT_DOWNSHIFT 5
#घोषणा AT803X_MIN_DOWNSHIFT 2
#घोषणा AT803X_MAX_DOWNSHIFT 9

#घोषणा AT803X_MMD3_SMARTEEE_CTL1		0x805b
#घोषणा AT803X_MMD3_SMARTEEE_CTL2		0x805c
#घोषणा AT803X_MMD3_SMARTEEE_CTL3		0x805d
#घोषणा AT803X_MMD3_SMARTEEE_CTL3_LPI_EN	BIT(8)

#घोषणा ATH9331_PHY_ID 0x004dd041
#घोषणा ATH8030_PHY_ID 0x004dd076
#घोषणा ATH8031_PHY_ID 0x004dd074
#घोषणा ATH8032_PHY_ID 0x004dd023
#घोषणा ATH8035_PHY_ID 0x004dd072
#घोषणा AT8030_PHY_ID_MASK			0xffffffef

#घोषणा AT803X_PAGE_FIBER		0
#घोषणा AT803X_PAGE_COPPER		1

MODULE_DESCRIPTION("Qualcomm Atheros AR803x PHY driver");
MODULE_AUTHOR("Matus Ujhelyi");
MODULE_LICENSE("GPL");

काष्ठा at803x_priv अणु
	पूर्णांक flags;
#घोषणा AT803X_KEEP_PLL_ENABLED	BIT(0)	/* करोn't turn off पूर्णांकernal PLL */
#घोषणा AT803X_DISABLE_SMARTEEE	BIT(1)
	u16 clk_25m_reg;
	u16 clk_25m_mask;
	u8 smarteee_lpi_tw_1g;
	u8 smarteee_lpi_tw_100m;
	काष्ठा regulator_dev *vddio_rdev;
	काष्ठा regulator_dev *vddh_rdev;
	काष्ठा regulator *vddio;
पूर्ण;

काष्ठा at803x_context अणु
	u16 bmcr;
	u16 advertise;
	u16 control1000;
	u16 पूर्णांक_enable;
	u16 smart_speed;
	u16 led_control;
पूर्ण;

अटल पूर्णांक at803x_debug_reg_पढ़ो(काष्ठा phy_device *phydev, u16 reg)
अणु
	पूर्णांक ret;

	ret = phy_ग_लिखो(phydev, AT803X_DEBUG_ADDR, reg);
	अगर (ret < 0)
		वापस ret;

	वापस phy_पढ़ो(phydev, AT803X_DEBUG_DATA);
पूर्ण

अटल पूर्णांक at803x_debug_reg_mask(काष्ठा phy_device *phydev, u16 reg,
				 u16 clear, u16 set)
अणु
	u16 val;
	पूर्णांक ret;

	ret = at803x_debug_reg_पढ़ो(phydev, reg);
	अगर (ret < 0)
		वापस ret;

	val = ret & 0xffff;
	val &= ~clear;
	val |= set;

	वापस phy_ग_लिखो(phydev, AT803X_DEBUG_DATA, val);
पूर्ण

अटल पूर्णांक at803x_ग_लिखो_page(काष्ठा phy_device *phydev, पूर्णांक page)
अणु
	पूर्णांक mask;
	पूर्णांक set;

	अगर (page == AT803X_PAGE_COPPER) अणु
		set = AT803X_BT_BX_REG_SEL;
		mask = 0;
	पूर्ण अन्यथा अणु
		set = 0;
		mask = AT803X_BT_BX_REG_SEL;
	पूर्ण

	वापस __phy_modअगरy(phydev, AT803X_REG_CHIP_CONFIG, mask, set);
पूर्ण

अटल पूर्णांक at803x_पढ़ो_page(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ccr = __phy_पढ़ो(phydev, AT803X_REG_CHIP_CONFIG);

	अगर (ccr < 0)
		वापस ccr;

	अगर (ccr & AT803X_BT_BX_REG_SEL)
		वापस AT803X_PAGE_COPPER;

	वापस AT803X_PAGE_FIBER;
पूर्ण

अटल पूर्णांक at803x_enable_rx_delay(काष्ठा phy_device *phydev)
अणु
	वापस at803x_debug_reg_mask(phydev, AT803X_DEBUG_REG_0, 0,
				     AT803X_DEBUG_RX_CLK_DLY_EN);
पूर्ण

अटल पूर्णांक at803x_enable_tx_delay(काष्ठा phy_device *phydev)
अणु
	वापस at803x_debug_reg_mask(phydev, AT803X_DEBUG_REG_5, 0,
				     AT803X_DEBUG_TX_CLK_DLY_EN);
पूर्ण

अटल पूर्णांक at803x_disable_rx_delay(काष्ठा phy_device *phydev)
अणु
	वापस at803x_debug_reg_mask(phydev, AT803X_DEBUG_REG_0,
				     AT803X_DEBUG_RX_CLK_DLY_EN, 0);
पूर्ण

अटल पूर्णांक at803x_disable_tx_delay(काष्ठा phy_device *phydev)
अणु
	वापस at803x_debug_reg_mask(phydev, AT803X_DEBUG_REG_5,
				     AT803X_DEBUG_TX_CLK_DLY_EN, 0);
पूर्ण

/* save relevant PHY रेजिस्टरs to निजी copy */
अटल व्योम at803x_context_save(काष्ठा phy_device *phydev,
				काष्ठा at803x_context *context)
अणु
	context->bmcr = phy_पढ़ो(phydev, MII_BMCR);
	context->advertise = phy_पढ़ो(phydev, MII_ADVERTISE);
	context->control1000 = phy_पढ़ो(phydev, MII_CTRL1000);
	context->पूर्णांक_enable = phy_पढ़ो(phydev, AT803X_INTR_ENABLE);
	context->smart_speed = phy_पढ़ो(phydev, AT803X_SMART_SPEED);
	context->led_control = phy_पढ़ो(phydev, AT803X_LED_CONTROL);
पूर्ण

/* restore relevant PHY रेजिस्टरs from निजी copy */
अटल व्योम at803x_context_restore(काष्ठा phy_device *phydev,
				   स्थिर काष्ठा at803x_context *context)
अणु
	phy_ग_लिखो(phydev, MII_BMCR, context->bmcr);
	phy_ग_लिखो(phydev, MII_ADVERTISE, context->advertise);
	phy_ग_लिखो(phydev, MII_CTRL1000, context->control1000);
	phy_ग_लिखो(phydev, AT803X_INTR_ENABLE, context->पूर्णांक_enable);
	phy_ग_लिखो(phydev, AT803X_SMART_SPEED, context->smart_speed);
	phy_ग_लिखो(phydev, AT803X_LED_CONTROL, context->led_control);
पूर्ण

अटल पूर्णांक at803x_set_wol(काष्ठा phy_device *phydev,
			  काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा net_device *ndev = phydev->attached_dev;
	स्थिर u8 *mac;
	पूर्णांक ret;
	u32 value;
	अचिन्हित पूर्णांक i, offsets[] = अणु
		AT803X_LOC_MAC_ADDR_32_47_OFFSET,
		AT803X_LOC_MAC_ADDR_16_31_OFFSET,
		AT803X_LOC_MAC_ADDR_0_15_OFFSET,
	पूर्ण;

	अगर (!ndev)
		वापस -ENODEV;

	अगर (wol->wolopts & WAKE_MAGIC) अणु
		mac = (स्थिर u8 *) ndev->dev_addr;

		अगर (!is_valid_ether_addr(mac))
			वापस -EINVAL;

		क्रम (i = 0; i < 3; i++)
			phy_ग_लिखो_mmd(phydev, AT803X_DEVICE_ADDR, offsets[i],
				      mac[(i * 2) + 1] | (mac[(i * 2)] << 8));

		value = phy_पढ़ो(phydev, AT803X_INTR_ENABLE);
		value |= AT803X_INTR_ENABLE_WOL;
		ret = phy_ग_लिखो(phydev, AT803X_INTR_ENABLE, value);
		अगर (ret)
			वापस ret;
		value = phy_पढ़ो(phydev, AT803X_INTR_STATUS);
	पूर्ण अन्यथा अणु
		value = phy_पढ़ो(phydev, AT803X_INTR_ENABLE);
		value &= (~AT803X_INTR_ENABLE_WOL);
		ret = phy_ग_लिखो(phydev, AT803X_INTR_ENABLE, value);
		अगर (ret)
			वापस ret;
		value = phy_पढ़ो(phydev, AT803X_INTR_STATUS);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम at803x_get_wol(काष्ठा phy_device *phydev,
			   काष्ठा ethtool_wolinfo *wol)
अणु
	u32 value;

	wol->supported = WAKE_MAGIC;
	wol->wolopts = 0;

	value = phy_पढ़ो(phydev, AT803X_INTR_ENABLE);
	अगर (value & AT803X_INTR_ENABLE_WOL)
		wol->wolopts |= WAKE_MAGIC;
पूर्ण

अटल पूर्णांक at803x_suspend(काष्ठा phy_device *phydev)
अणु
	पूर्णांक value;
	पूर्णांक wol_enabled;

	value = phy_पढ़ो(phydev, AT803X_INTR_ENABLE);
	wol_enabled = value & AT803X_INTR_ENABLE_WOL;

	अगर (wol_enabled)
		value = BMCR_ISOLATE;
	अन्यथा
		value = BMCR_PDOWN;

	phy_modअगरy(phydev, MII_BMCR, 0, value);

	वापस 0;
पूर्ण

अटल पूर्णांक at803x_resume(काष्ठा phy_device *phydev)
अणु
	वापस phy_modअगरy(phydev, MII_BMCR, BMCR_PDOWN | BMCR_ISOLATE, 0);
पूर्ण

अटल पूर्णांक at803x_rgmii_reg_set_voltage_sel(काष्ठा regulator_dev *rdev,
					    अचिन्हित पूर्णांक selector)
अणु
	काष्ठा phy_device *phydev = rdev_get_drvdata(rdev);

	अगर (selector)
		वापस at803x_debug_reg_mask(phydev, AT803X_DEBUG_REG_1F,
					     0, AT803X_DEBUG_RGMII_1V8);
	अन्यथा
		वापस at803x_debug_reg_mask(phydev, AT803X_DEBUG_REG_1F,
					     AT803X_DEBUG_RGMII_1V8, 0);
पूर्ण

अटल पूर्णांक at803x_rgmii_reg_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा phy_device *phydev = rdev_get_drvdata(rdev);
	पूर्णांक val;

	val = at803x_debug_reg_पढ़ो(phydev, AT803X_DEBUG_REG_1F);
	अगर (val < 0)
		वापस val;

	वापस (val & AT803X_DEBUG_RGMII_1V8) ? 1 : 0;
पूर्ण

अटल स्थिर काष्ठा regulator_ops vddio_regulator_ops = अणु
	.list_voltage = regulator_list_voltage_table,
	.set_voltage_sel = at803x_rgmii_reg_set_voltage_sel,
	.get_voltage_sel = at803x_rgmii_reg_get_voltage_sel,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक vddio_voltage_table[] = अणु
	1500000,
	1800000,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc vddio_desc = अणु
	.name = "vddio",
	.of_match = of_match_ptr("vddio-regulator"),
	.n_voltages = ARRAY_SIZE(vddio_voltage_table),
	.volt_table = vddio_voltage_table,
	.ops = &vddio_regulator_ops,
	.type = REGULATOR_VOLTAGE,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops vddh_regulator_ops = अणु
पूर्ण;

अटल स्थिर काष्ठा regulator_desc vddh_desc = अणु
	.name = "vddh",
	.of_match = of_match_ptr("vddh-regulator"),
	.n_voltages = 1,
	.fixed_uV = 2500000,
	.ops = &vddh_regulator_ops,
	.type = REGULATOR_VOLTAGE,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक at8031_रेजिस्टर_regulators(काष्ठा phy_device *phydev)
अणु
	काष्ठा at803x_priv *priv = phydev->priv;
	काष्ठा device *dev = &phydev->mdio.dev;
	काष्ठा regulator_config config = अणु पूर्ण;

	config.dev = dev;
	config.driver_data = phydev;

	priv->vddio_rdev = devm_regulator_रेजिस्टर(dev, &vddio_desc, &config);
	अगर (IS_ERR(priv->vddio_rdev)) अणु
		phydev_err(phydev, "failed to register VDDIO regulator\n");
		वापस PTR_ERR(priv->vddio_rdev);
	पूर्ण

	priv->vddh_rdev = devm_regulator_रेजिस्टर(dev, &vddh_desc, &config);
	अगर (IS_ERR(priv->vddh_rdev)) अणु
		phydev_err(phydev, "failed to register VDDH regulator\n");
		वापस PTR_ERR(priv->vddh_rdev);
	पूर्ण

	वापस 0;
पूर्ण

अटल bool at803x_match_phy_id(काष्ठा phy_device *phydev, u32 phy_id)
अणु
	वापस (phydev->phy_id & phydev->drv->phy_id_mask)
		== (phy_id & phydev->drv->phy_id_mask);
पूर्ण

अटल पूर्णांक at803x_parse_dt(काष्ठा phy_device *phydev)
अणु
	काष्ठा device_node *node = phydev->mdio.dev.of_node;
	काष्ठा at803x_priv *priv = phydev->priv;
	u32 freq, strength, tw;
	अचिन्हित पूर्णांक sel;
	पूर्णांक ret;

	अगर (!IS_ENABLED(CONFIG_OF_MDIO))
		वापस 0;

	अगर (of_property_पढ़ो_bool(node, "qca,disable-smarteee"))
		priv->flags |= AT803X_DISABLE_SMARTEEE;

	अगर (!of_property_पढ़ो_u32(node, "qca,smarteee-tw-us-1g", &tw)) अणु
		अगर (!tw || tw > 255) अणु
			phydev_err(phydev, "invalid qca,smarteee-tw-us-1g\n");
			वापस -EINVAL;
		पूर्ण
		priv->smarteee_lpi_tw_1g = tw;
	पूर्ण

	अगर (!of_property_पढ़ो_u32(node, "qca,smarteee-tw-us-100m", &tw)) अणु
		अगर (!tw || tw > 255) अणु
			phydev_err(phydev, "invalid qca,smarteee-tw-us-100m\n");
			वापस -EINVAL;
		पूर्ण
		priv->smarteee_lpi_tw_100m = tw;
	पूर्ण

	ret = of_property_पढ़ो_u32(node, "qca,clk-out-frequency", &freq);
	अगर (!ret) अणु
		चयन (freq) अणु
		हाल 25000000:
			sel = AT803X_CLK_OUT_25MHZ_XTAL;
			अवरोध;
		हाल 50000000:
			sel = AT803X_CLK_OUT_50MHZ_PLL;
			अवरोध;
		हाल 62500000:
			sel = AT803X_CLK_OUT_62_5MHZ_PLL;
			अवरोध;
		हाल 125000000:
			sel = AT803X_CLK_OUT_125MHZ_PLL;
			अवरोध;
		शेष:
			phydev_err(phydev, "invalid qca,clk-out-frequency\n");
			वापस -EINVAL;
		पूर्ण

		priv->clk_25m_reg |= FIELD_PREP(AT803X_CLK_OUT_MASK, sel);
		priv->clk_25m_mask |= AT803X_CLK_OUT_MASK;

		/* Fixup क्रम the AR8030/AR8035. This chip has another mask and
		 * करोesn't support the DSP reference. Eg. the lowest bit of the
		 * mask. The upper two bits select the same frequencies. Mask
		 * the lowest bit here.
		 *
		 * Warning:
		 *   There was no datasheet क्रम the AR8030 available so this is
		 *   just a guess. But the AR8035 is listed as pin compatible
		 *   to the AR8030 so there might be a good chance it works on
		 *   the AR8030 too.
		 */
		अगर (at803x_match_phy_id(phydev, ATH8030_PHY_ID) ||
		    at803x_match_phy_id(phydev, ATH8035_PHY_ID)) अणु
			priv->clk_25m_reg &= AT8035_CLK_OUT_MASK;
			priv->clk_25m_mask &= AT8035_CLK_OUT_MASK;
		पूर्ण
	पूर्ण

	ret = of_property_पढ़ो_u32(node, "qca,clk-out-strength", &strength);
	अगर (!ret) अणु
		priv->clk_25m_mask |= AT803X_CLK_OUT_STRENGTH_MASK;
		चयन (strength) अणु
		हाल AR803X_STRENGTH_FULL:
			priv->clk_25m_reg |= AT803X_CLK_OUT_STRENGTH_FULL;
			अवरोध;
		हाल AR803X_STRENGTH_HALF:
			priv->clk_25m_reg |= AT803X_CLK_OUT_STRENGTH_HALF;
			अवरोध;
		हाल AR803X_STRENGTH_QUARTER:
			priv->clk_25m_reg |= AT803X_CLK_OUT_STRENGTH_QUARTER;
			अवरोध;
		शेष:
			phydev_err(phydev, "invalid qca,clk-out-strength\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Only supported on AR8031/AR8033, the AR8030/AR8035 use strapping
	 * options.
	 */
	अगर (at803x_match_phy_id(phydev, ATH8031_PHY_ID)) अणु
		अगर (of_property_पढ़ो_bool(node, "qca,keep-pll-enabled"))
			priv->flags |= AT803X_KEEP_PLL_ENABLED;

		ret = at8031_रेजिस्टर_regulators(phydev);
		अगर (ret < 0)
			वापस ret;

		priv->vddio = devm_regulator_get_optional(&phydev->mdio.dev,
							  "vddio");
		अगर (IS_ERR(priv->vddio)) अणु
			phydev_err(phydev, "failed to get VDDIO regulator\n");
			वापस PTR_ERR(priv->vddio);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक at803x_probe(काष्ठा phy_device *phydev)
अणु
	काष्ठा device *dev = &phydev->mdio.dev;
	काष्ठा at803x_priv *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	phydev->priv = priv;

	ret = at803x_parse_dt(phydev);
	अगर (ret)
		वापस ret;

	अगर (priv->vddio) अणु
		ret = regulator_enable(priv->vddio);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Some bootloaders leave the fiber page selected.
	 * Switch to the copper page, as otherwise we पढ़ो
	 * the PHY capabilities from the fiber side.
	 */
	अगर (at803x_match_phy_id(phydev, ATH8031_PHY_ID)) अणु
		phy_lock_mdio_bus(phydev);
		ret = at803x_ग_लिखो_page(phydev, AT803X_PAGE_COPPER);
		phy_unlock_mdio_bus(phydev);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;

err:
	अगर (priv->vddio)
		regulator_disable(priv->vddio);

	वापस ret;
पूर्ण

अटल व्योम at803x_हटाओ(काष्ठा phy_device *phydev)
अणु
	काष्ठा at803x_priv *priv = phydev->priv;

	अगर (priv->vddio)
		regulator_disable(priv->vddio);
पूर्ण

अटल पूर्णांक at803x_smarteee_config(काष्ठा phy_device *phydev)
अणु
	काष्ठा at803x_priv *priv = phydev->priv;
	u16 mask = 0, val = 0;
	पूर्णांक ret;

	अगर (priv->flags & AT803X_DISABLE_SMARTEEE)
		वापस phy_modअगरy_mmd(phydev, MDIO_MMD_PCS,
				      AT803X_MMD3_SMARTEEE_CTL3,
				      AT803X_MMD3_SMARTEEE_CTL3_LPI_EN, 0);

	अगर (priv->smarteee_lpi_tw_1g) अणु
		mask |= 0xff00;
		val |= priv->smarteee_lpi_tw_1g << 8;
	पूर्ण
	अगर (priv->smarteee_lpi_tw_100m) अणु
		mask |= 0x00ff;
		val |= priv->smarteee_lpi_tw_100m;
	पूर्ण
	अगर (!mask)
		वापस 0;

	ret = phy_modअगरy_mmd(phydev, MDIO_MMD_PCS, AT803X_MMD3_SMARTEEE_CTL1,
			     mask, val);
	अगर (ret)
		वापस ret;

	वापस phy_modअगरy_mmd(phydev, MDIO_MMD_PCS, AT803X_MMD3_SMARTEEE_CTL3,
			      AT803X_MMD3_SMARTEEE_CTL3_LPI_EN,
			      AT803X_MMD3_SMARTEEE_CTL3_LPI_EN);
पूर्ण

अटल पूर्णांक at803x_clk_out_config(काष्ठा phy_device *phydev)
अणु
	काष्ठा at803x_priv *priv = phydev->priv;

	अगर (!priv->clk_25m_mask)
		वापस 0;

	वापस phy_modअगरy_mmd(phydev, MDIO_MMD_AN, AT803X_MMD7_CLK25M,
			      priv->clk_25m_mask, priv->clk_25m_reg);
पूर्ण

अटल पूर्णांक at8031_pll_config(काष्ठा phy_device *phydev)
अणु
	काष्ठा at803x_priv *priv = phydev->priv;

	/* The शेष after hardware reset is PLL OFF. After a soft reset, the
	 * values are retained.
	 */
	अगर (priv->flags & AT803X_KEEP_PLL_ENABLED)
		वापस at803x_debug_reg_mask(phydev, AT803X_DEBUG_REG_1F,
					     0, AT803X_DEBUG_PLL_ON);
	अन्यथा
		वापस at803x_debug_reg_mask(phydev, AT803X_DEBUG_REG_1F,
					     AT803X_DEBUG_PLL_ON, 0);
पूर्ण

अटल पूर्णांक at803x_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	/* The RX and TX delay शेष is:
	 *   after HW reset: RX delay enabled and TX delay disabled
	 *   after SW reset: RX delay enabled, जबतक TX delay retains the
	 *   value beक्रमe reset.
	 */
	अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_ID ||
	    phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_RXID)
		ret = at803x_enable_rx_delay(phydev);
	अन्यथा
		ret = at803x_disable_rx_delay(phydev);
	अगर (ret < 0)
		वापस ret;

	अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_ID ||
	    phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_TXID)
		ret = at803x_enable_tx_delay(phydev);
	अन्यथा
		ret = at803x_disable_tx_delay(phydev);
	अगर (ret < 0)
		वापस ret;

	ret = at803x_smarteee_config(phydev);
	अगर (ret < 0)
		वापस ret;

	ret = at803x_clk_out_config(phydev);
	अगर (ret < 0)
		वापस ret;

	अगर (at803x_match_phy_id(phydev, ATH8031_PHY_ID)) अणु
		ret = at8031_pll_config(phydev);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Ar803x extended next page bit is enabled by शेष. Cisco
	 * multigig चयनes पढ़ो this bit and attempt to negotiate 10Gbps
	 * rates even अगर the next page bit is disabled. This is incorrect
	 * behaviour but we still need to accommodate it. XNP is only needed
	 * क्रम 10Gbps support, so disable XNP.
	 */
	वापस phy_modअगरy(phydev, MII_ADVERTISE, MDIO_AN_CTRL1_XNP, 0);
पूर्ण

अटल पूर्णांक at803x_ack_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;

	err = phy_पढ़ो(phydev, AT803X_INTR_STATUS);

	वापस (err < 0) ? err : 0;
पूर्ण

अटल पूर्णांक at803x_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	पूर्णांक err;
	पूर्णांक value;

	value = phy_पढ़ो(phydev, AT803X_INTR_ENABLE);

	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED) अणु
		/* Clear any pending पूर्णांकerrupts */
		err = at803x_ack_पूर्णांकerrupt(phydev);
		अगर (err)
			वापस err;

		value |= AT803X_INTR_ENABLE_AUTONEG_ERR;
		value |= AT803X_INTR_ENABLE_SPEED_CHANGED;
		value |= AT803X_INTR_ENABLE_DUPLEX_CHANGED;
		value |= AT803X_INTR_ENABLE_LINK_FAIL;
		value |= AT803X_INTR_ENABLE_LINK_SUCCESS;

		err = phy_ग_लिखो(phydev, AT803X_INTR_ENABLE, value);
	पूर्ण अन्यथा अणु
		err = phy_ग_लिखो(phydev, AT803X_INTR_ENABLE, 0);
		अगर (err)
			वापस err;

		/* Clear any pending पूर्णांकerrupts */
		err = at803x_ack_पूर्णांकerrupt(phydev);
	पूर्ण

	वापस err;
पूर्ण

अटल irqवापस_t at803x_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक irq_status, पूर्णांक_enabled;

	irq_status = phy_पढ़ो(phydev, AT803X_INTR_STATUS);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	/* Read the current enabled पूर्णांकerrupts */
	पूर्णांक_enabled = phy_पढ़ो(phydev, AT803X_INTR_ENABLE);
	अगर (पूर्णांक_enabled < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	/* See अगर this was one of our enabled पूर्णांकerrupts */
	अगर (!(irq_status & पूर्णांक_enabled))
		वापस IRQ_NONE;

	phy_trigger_machine(phydev);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम at803x_link_change_notअगरy(काष्ठा phy_device *phydev)
अणु
	/*
	 * Conduct a hardware reset क्रम AT8030 every समय a link loss is
	 * संकेतled. This is necessary to circumvent a hardware bug that
	 * occurs when the cable is unplugged जबतक TX packets are pending
	 * in the FIFO. In such हालs, the FIFO enters an error mode it
	 * cannot recover from by software.
	 */
	अगर (phydev->state == PHY_NOLINK && phydev->mdio.reset_gpio) अणु
		काष्ठा at803x_context context;

		at803x_context_save(phydev, &context);

		phy_device_reset(phydev, 1);
		msleep(1);
		phy_device_reset(phydev, 0);
		msleep(1);

		at803x_context_restore(phydev, &context);

		phydev_dbg(phydev, "%s(): phy was reset\n", __func__);
	पूर्ण
पूर्ण

अटल पूर्णांक at803x_पढ़ो_status(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ss, err, old_link = phydev->link;

	/* Update the link, but वापस अगर there was an error */
	err = genphy_update_link(phydev);
	अगर (err)
		वापस err;

	/* why bother the PHY अगर nothing can have changed */
	अगर (phydev->स्वतःneg == AUTONEG_ENABLE && old_link && phydev->link)
		वापस 0;

	phydev->speed = SPEED_UNKNOWN;
	phydev->duplex = DUPLEX_UNKNOWN;
	phydev->छोड़ो = 0;
	phydev->asym_छोड़ो = 0;

	err = genphy_पढ़ो_lpa(phydev);
	अगर (err < 0)
		वापस err;

	/* Read the AT8035 PHY-Specअगरic Status रेजिस्टर, which indicates the
	 * speed and duplex that the PHY is actually using, irrespective of
	 * whether we are in स्वतःneg mode or not.
	 */
	ss = phy_पढ़ो(phydev, AT803X_SPECIFIC_STATUS);
	अगर (ss < 0)
		वापस ss;

	अगर (ss & AT803X_SS_SPEED_DUPLEX_RESOLVED) अणु
		पूर्णांक sfc;

		sfc = phy_पढ़ो(phydev, AT803X_SPECIFIC_FUNCTION_CONTROL);
		अगर (sfc < 0)
			वापस sfc;

		चयन (ss & AT803X_SS_SPEED_MASK) अणु
		हाल AT803X_SS_SPEED_10:
			phydev->speed = SPEED_10;
			अवरोध;
		हाल AT803X_SS_SPEED_100:
			phydev->speed = SPEED_100;
			अवरोध;
		हाल AT803X_SS_SPEED_1000:
			phydev->speed = SPEED_1000;
			अवरोध;
		पूर्ण
		अगर (ss & AT803X_SS_DUPLEX)
			phydev->duplex = DUPLEX_FULL;
		अन्यथा
			phydev->duplex = DUPLEX_HALF;

		अगर (ss & AT803X_SS_MDIX)
			phydev->mdix = ETH_TP_MDI_X;
		अन्यथा
			phydev->mdix = ETH_TP_MDI;

		चयन (FIELD_GET(AT803X_SFC_MDI_CROSSOVER_MODE_M, sfc)) अणु
		हाल AT803X_SFC_MANUAL_MDI:
			phydev->mdix_ctrl = ETH_TP_MDI;
			अवरोध;
		हाल AT803X_SFC_MANUAL_MDIX:
			phydev->mdix_ctrl = ETH_TP_MDI_X;
			अवरोध;
		हाल AT803X_SFC_AUTOMATIC_CROSSOVER:
			phydev->mdix_ctrl = ETH_TP_MDI_AUTO;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (phydev->स्वतःneg == AUTONEG_ENABLE && phydev->स्वतःneg_complete)
		phy_resolve_aneg_छोड़ो(phydev);

	वापस 0;
पूर्ण

अटल पूर्णांक at803x_config_mdix(काष्ठा phy_device *phydev, u8 ctrl)
अणु
	u16 val;

	चयन (ctrl) अणु
	हाल ETH_TP_MDI:
		val = AT803X_SFC_MANUAL_MDI;
		अवरोध;
	हाल ETH_TP_MDI_X:
		val = AT803X_SFC_MANUAL_MDIX;
		अवरोध;
	हाल ETH_TP_MDI_AUTO:
		val = AT803X_SFC_AUTOMATIC_CROSSOVER;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस phy_modअगरy_changed(phydev, AT803X_SPECIFIC_FUNCTION_CONTROL,
			  AT803X_SFC_MDI_CROSSOVER_MODE_M,
			  FIELD_PREP(AT803X_SFC_MDI_CROSSOVER_MODE_M, val));
पूर्ण

अटल पूर्णांक at803x_config_aneg(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	ret = at803x_config_mdix(phydev, phydev->mdix_ctrl);
	अगर (ret < 0)
		वापस ret;

	/* Changes of the midx bits are disruptive to the normal operation;
	 * thereक्रमe any changes to these रेजिस्टरs must be followed by a
	 * software reset to take effect.
	 */
	अगर (ret == 1) अणु
		ret = genphy_soft_reset(phydev);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस genphy_config_aneg(phydev);
पूर्ण

अटल पूर्णांक at803x_get_करोwnshअगरt(काष्ठा phy_device *phydev, u8 *d)
अणु
	पूर्णांक val;

	val = phy_पढ़ो(phydev, AT803X_SMART_SPEED);
	अगर (val < 0)
		वापस val;

	अगर (val & AT803X_SMART_SPEED_ENABLE)
		*d = FIELD_GET(AT803X_SMART_SPEED_RETRY_LIMIT_MASK, val) + 2;
	अन्यथा
		*d = DOWNSHIFT_DEV_DISABLE;

	वापस 0;
पूर्ण

अटल पूर्णांक at803x_set_करोwnshअगरt(काष्ठा phy_device *phydev, u8 cnt)
अणु
	u16 mask, set;
	पूर्णांक ret;

	चयन (cnt) अणु
	हाल DOWNSHIFT_DEV_DEFAULT_COUNT:
		cnt = AT803X_DEFAULT_DOWNSHIFT;
		fallthrough;
	हाल AT803X_MIN_DOWNSHIFT ... AT803X_MAX_DOWNSHIFT:
		set = AT803X_SMART_SPEED_ENABLE |
		      AT803X_SMART_SPEED_BYPASS_TIMER |
		      FIELD_PREP(AT803X_SMART_SPEED_RETRY_LIMIT_MASK, cnt - 2);
		mask = AT803X_SMART_SPEED_RETRY_LIMIT_MASK;
		अवरोध;
	हाल DOWNSHIFT_DEV_DISABLE:
		set = 0;
		mask = AT803X_SMART_SPEED_ENABLE |
		       AT803X_SMART_SPEED_BYPASS_TIMER;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = phy_modअगरy_changed(phydev, AT803X_SMART_SPEED, mask, set);

	/* After changing the smart speed settings, we need to perक्रमm a
	 * software reset, use phy_init_hw() to make sure we set the
	 * reapply any values which might got lost during software reset.
	 */
	अगर (ret == 1)
		ret = phy_init_hw(phydev);

	वापस ret;
पूर्ण

अटल पूर्णांक at803x_get_tunable(काष्ठा phy_device *phydev,
			      काष्ठा ethtool_tunable *tuna, व्योम *data)
अणु
	चयन (tuna->id) अणु
	हाल ETHTOOL_PHY_DOWNSHIFT:
		वापस at803x_get_करोwnshअगरt(phydev, data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक at803x_set_tunable(काष्ठा phy_device *phydev,
			      काष्ठा ethtool_tunable *tuna, स्थिर व्योम *data)
अणु
	चयन (tuna->id) अणु
	हाल ETHTOOL_PHY_DOWNSHIFT:
		वापस at803x_set_करोwnshअगरt(phydev, *(स्थिर u8 *)data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक at803x_cable_test_result_trans(u16 status)
अणु
	चयन (FIELD_GET(AT803X_CDT_STATUS_STAT_MASK, status)) अणु
	हाल AT803X_CDT_STATUS_STAT_NORMAL:
		वापस ETHTOOL_A_CABLE_RESULT_CODE_OK;
	हाल AT803X_CDT_STATUS_STAT_SHORT:
		वापस ETHTOOL_A_CABLE_RESULT_CODE_SAME_SHORT;
	हाल AT803X_CDT_STATUS_STAT_OPEN:
		वापस ETHTOOL_A_CABLE_RESULT_CODE_OPEN;
	हाल AT803X_CDT_STATUS_STAT_FAIL:
	शेष:
		वापस ETHTOOL_A_CABLE_RESULT_CODE_UNSPEC;
	पूर्ण
पूर्ण

अटल bool at803x_cdt_test_failed(u16 status)
अणु
	वापस FIELD_GET(AT803X_CDT_STATUS_STAT_MASK, status) ==
		AT803X_CDT_STATUS_STAT_FAIL;
पूर्ण

अटल bool at803x_cdt_fault_length_valid(u16 status)
अणु
	चयन (FIELD_GET(AT803X_CDT_STATUS_STAT_MASK, status)) अणु
	हाल AT803X_CDT_STATUS_STAT_OPEN:
	हाल AT803X_CDT_STATUS_STAT_SHORT:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक at803x_cdt_fault_length(u16 status)
अणु
	पूर्णांक dt;

	/* According to the datasheet the distance to the fault is
	 * DELTA_TIME * 0.824 meters.
	 *
	 * The author suspect the correct क्रमmula is:
	 *
	 *   fault_distance = DELTA_TIME * (c * VF) / 125MHz / 2
	 *
	 * where c is the speed of light, VF is the velocity factor of
	 * the twisted pair cable, 125MHz the counter frequency and
	 * we need to भागide by 2 because the hardware will measure the
	 * round trip समय to the fault and back to the PHY.
	 *
	 * With a VF of 0.69 we get the factor 0.824 mentioned in the
	 * datasheet.
	 */
	dt = FIELD_GET(AT803X_CDT_STATUS_DELTA_TIME_MASK, status);

	वापस (dt * 824) / 10;
पूर्ण

अटल पूर्णांक at803x_cdt_start(काष्ठा phy_device *phydev, पूर्णांक pair)
अणु
	u16 cdt;

	cdt = FIELD_PREP(AT803X_CDT_MDI_PAIR_MASK, pair) |
	      AT803X_CDT_ENABLE_TEST;

	वापस phy_ग_लिखो(phydev, AT803X_CDT, cdt);
पूर्ण

अटल पूर्णांक at803x_cdt_रुको_क्रम_completion(काष्ठा phy_device *phydev)
अणु
	पूर्णांक val, ret;

	/* One test run takes about 25ms */
	ret = phy_पढ़ो_poll_समयout(phydev, AT803X_CDT, val,
				    !(val & AT803X_CDT_ENABLE_TEST),
				    30000, 100000, true);

	वापस ret < 0 ? ret : 0;
पूर्ण

अटल पूर्णांक at803x_cable_test_one_pair(काष्ठा phy_device *phydev, पूर्णांक pair)
अणु
	अटल स्थिर पूर्णांक ethtool_pair[] = अणु
		ETHTOOL_A_CABLE_PAIR_A,
		ETHTOOL_A_CABLE_PAIR_B,
		ETHTOOL_A_CABLE_PAIR_C,
		ETHTOOL_A_CABLE_PAIR_D,
	पूर्ण;
	पूर्णांक ret, val;

	ret = at803x_cdt_start(phydev, pair);
	अगर (ret)
		वापस ret;

	ret = at803x_cdt_रुको_क्रम_completion(phydev);
	अगर (ret)
		वापस ret;

	val = phy_पढ़ो(phydev, AT803X_CDT_STATUS);
	अगर (val < 0)
		वापस val;

	अगर (at803x_cdt_test_failed(val))
		वापस 0;

	ethnl_cable_test_result(phydev, ethtool_pair[pair],
				at803x_cable_test_result_trans(val));

	अगर (at803x_cdt_fault_length_valid(val))
		ethnl_cable_test_fault_length(phydev, ethtool_pair[pair],
					      at803x_cdt_fault_length(val));

	वापस 1;
पूर्ण

अटल पूर्णांक at803x_cable_test_get_status(काष्ठा phy_device *phydev,
					bool *finished)
अणु
	अचिन्हित दीर्घ pair_mask;
	पूर्णांक retries = 20;
	पूर्णांक pair, ret;

	अगर (phydev->phy_id == ATH9331_PHY_ID ||
	    phydev->phy_id == ATH8032_PHY_ID)
		pair_mask = 0x3;
	अन्यथा
		pair_mask = 0xf;

	*finished = false;

	/* According to the datasheet the CDT can be perक्रमmed when
	 * there is no link partner or when the link partner is
	 * स्वतः-negotiating. Starting the test will restart the AN
	 * स्वतःmatically. It seems that करोing this repeatedly we will
	 * get a slot where our link partner won't disturb our
	 * measurement.
	 */
	जबतक (pair_mask && retries--) अणु
		क्रम_each_set_bit(pair, &pair_mask, 4) अणु
			ret = at803x_cable_test_one_pair(phydev, pair);
			अगर (ret < 0)
				वापस ret;
			अगर (ret)
				clear_bit(pair, &pair_mask);
		पूर्ण
		अगर (pair_mask)
			msleep(250);
	पूर्ण

	*finished = true;

	वापस 0;
पूर्ण

अटल पूर्णांक at803x_cable_test_start(काष्ठा phy_device *phydev)
अणु
	/* Enable स्वतः-negotiation, but advertise no capabilities, no link
	 * will be established. A restart of the स्वतः-negotiation is not
	 * required, because the cable test will स्वतःmatically अवरोध the link.
	 */
	phy_ग_लिखो(phydev, MII_BMCR, BMCR_ANENABLE);
	phy_ग_लिखो(phydev, MII_ADVERTISE, ADVERTISE_CSMA);
	अगर (phydev->phy_id != ATH9331_PHY_ID &&
	    phydev->phy_id != ATH8032_PHY_ID)
		phy_ग_लिखो(phydev, MII_CTRL1000, 0);

	/* we करो all the (समय consuming) work later */
	वापस 0;
पूर्ण

अटल काष्ठा phy_driver at803x_driver[] = अणु
अणु
	/* Qualcomm Atheros AR8035 */
	PHY_ID_MATCH_EXACT(ATH8035_PHY_ID),
	.name			= "Qualcomm Atheros AR8035",
	.flags			= PHY_POLL_CABLE_TEST,
	.probe			= at803x_probe,
	.हटाओ			= at803x_हटाओ,
	.config_aneg		= at803x_config_aneg,
	.config_init		= at803x_config_init,
	.soft_reset		= genphy_soft_reset,
	.set_wol		= at803x_set_wol,
	.get_wol		= at803x_get_wol,
	.suspend		= at803x_suspend,
	.resume			= at803x_resume,
	/* PHY_GBIT_FEATURES */
	.पढ़ो_status		= at803x_पढ़ो_status,
	.config_पूर्णांकr		= at803x_config_पूर्णांकr,
	.handle_पूर्णांकerrupt	= at803x_handle_पूर्णांकerrupt,
	.get_tunable		= at803x_get_tunable,
	.set_tunable		= at803x_set_tunable,
	.cable_test_start	= at803x_cable_test_start,
	.cable_test_get_status	= at803x_cable_test_get_status,
पूर्ण, अणु
	/* Qualcomm Atheros AR8030 */
	.phy_id			= ATH8030_PHY_ID,
	.name			= "Qualcomm Atheros AR8030",
	.phy_id_mask		= AT8030_PHY_ID_MASK,
	.probe			= at803x_probe,
	.हटाओ			= at803x_हटाओ,
	.config_init		= at803x_config_init,
	.link_change_notअगरy	= at803x_link_change_notअगरy,
	.set_wol		= at803x_set_wol,
	.get_wol		= at803x_get_wol,
	.suspend		= at803x_suspend,
	.resume			= at803x_resume,
	/* PHY_BASIC_FEATURES */
	.config_पूर्णांकr		= at803x_config_पूर्णांकr,
	.handle_पूर्णांकerrupt	= at803x_handle_पूर्णांकerrupt,
पूर्ण, अणु
	/* Qualcomm Atheros AR8031/AR8033 */
	PHY_ID_MATCH_EXACT(ATH8031_PHY_ID),
	.name			= "Qualcomm Atheros AR8031/AR8033",
	.flags			= PHY_POLL_CABLE_TEST,
	.probe			= at803x_probe,
	.हटाओ			= at803x_हटाओ,
	.config_init		= at803x_config_init,
	.config_aneg		= at803x_config_aneg,
	.soft_reset		= genphy_soft_reset,
	.set_wol		= at803x_set_wol,
	.get_wol		= at803x_get_wol,
	.suspend		= at803x_suspend,
	.resume			= at803x_resume,
	.पढ़ो_page		= at803x_पढ़ो_page,
	.ग_लिखो_page		= at803x_ग_लिखो_page,
	/* PHY_GBIT_FEATURES */
	.पढ़ो_status		= at803x_पढ़ो_status,
	.config_पूर्णांकr		= &at803x_config_पूर्णांकr,
	.handle_पूर्णांकerrupt	= at803x_handle_पूर्णांकerrupt,
	.get_tunable		= at803x_get_tunable,
	.set_tunable		= at803x_set_tunable,
	.cable_test_start	= at803x_cable_test_start,
	.cable_test_get_status	= at803x_cable_test_get_status,
पूर्ण, अणु
	/* Qualcomm Atheros AR8032 */
	PHY_ID_MATCH_EXACT(ATH8032_PHY_ID),
	.name			= "Qualcomm Atheros AR8032",
	.probe			= at803x_probe,
	.हटाओ			= at803x_हटाओ,
	.flags			= PHY_POLL_CABLE_TEST,
	.config_init		= at803x_config_init,
	.link_change_notअगरy	= at803x_link_change_notअगरy,
	.set_wol		= at803x_set_wol,
	.get_wol		= at803x_get_wol,
	.suspend		= at803x_suspend,
	.resume			= at803x_resume,
	/* PHY_BASIC_FEATURES */
	.config_पूर्णांकr		= at803x_config_पूर्णांकr,
	.handle_पूर्णांकerrupt	= at803x_handle_पूर्णांकerrupt,
	.cable_test_start	= at803x_cable_test_start,
	.cable_test_get_status	= at803x_cable_test_get_status,
पूर्ण, अणु
	/* ATHEROS AR9331 */
	PHY_ID_MATCH_EXACT(ATH9331_PHY_ID),
	.name			= "Qualcomm Atheros AR9331 built-in PHY",
	.suspend		= at803x_suspend,
	.resume			= at803x_resume,
	.flags			= PHY_POLL_CABLE_TEST,
	/* PHY_BASIC_FEATURES */
	.config_पूर्णांकr		= &at803x_config_पूर्णांकr,
	.handle_पूर्णांकerrupt	= at803x_handle_पूर्णांकerrupt,
	.cable_test_start	= at803x_cable_test_start,
	.cable_test_get_status	= at803x_cable_test_get_status,
	.पढ़ो_status		= at803x_पढ़ो_status,
	.soft_reset		= genphy_soft_reset,
	.config_aneg		= at803x_config_aneg,
पूर्ण पूर्ण;

module_phy_driver(at803x_driver);

अटल काष्ठा mdio_device_id __maybe_unused atheros_tbl[] = अणु
	अणु ATH8030_PHY_ID, AT8030_PHY_ID_MASK पूर्ण,
	अणु PHY_ID_MATCH_EXACT(ATH8031_PHY_ID) पूर्ण,
	अणु PHY_ID_MATCH_EXACT(ATH8032_PHY_ID) पूर्ण,
	अणु PHY_ID_MATCH_EXACT(ATH8035_PHY_ID) पूर्ण,
	अणु PHY_ID_MATCH_EXACT(ATH9331_PHY_ID) पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(mdio, atheros_tbl);
