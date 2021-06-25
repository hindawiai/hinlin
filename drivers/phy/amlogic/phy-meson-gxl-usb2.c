<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Meson GXL and GXM USB2 PHY driver
 *
 * Copyright (C) 2017 Martin Blumenstingl <martin.blumenstingl@googlemail.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>

/* bits [31:27] are पढ़ो-only */
#घोषणा U2P_R0							0x0
	#घोषणा U2P_R0_BYPASS_SEL				BIT(0)
	#घोषणा U2P_R0_BYPASS_DM_EN				BIT(1)
	#घोषणा U2P_R0_BYPASS_DP_EN				BIT(2)
	#घोषणा U2P_R0_TXBITSTUFF_ENH				BIT(3)
	#घोषणा U2P_R0_TXBITSTUFF_EN				BIT(4)
	#घोषणा U2P_R0_DM_PULLDOWN				BIT(5)
	#घोषणा U2P_R0_DP_PULLDOWN				BIT(6)
	#घोषणा U2P_R0_DP_VBUS_VLD_EXT_SEL			BIT(7)
	#घोषणा U2P_R0_DP_VBUS_VLD_EXT				BIT(8)
	#घोषणा U2P_R0_ADP_PRB_EN				BIT(9)
	#घोषणा U2P_R0_ADP_DISCHARGE				BIT(10)
	#घोषणा U2P_R0_ADP_CHARGE				BIT(11)
	#घोषणा U2P_R0_DRV_VBUS					BIT(12)
	#घोषणा U2P_R0_ID_PULLUP				BIT(13)
	#घोषणा U2P_R0_LOOPBACK_EN_B				BIT(14)
	#घोषणा U2P_R0_OTG_DISABLE				BIT(15)
	#घोषणा U2P_R0_COMMON_ONN				BIT(16)
	#घोषणा U2P_R0_FSEL_MASK				GENMASK(19, 17)
	#घोषणा U2P_R0_REF_CLK_SEL_MASK				GENMASK(21, 20)
	#घोषणा U2P_R0_POWER_ON_RESET				BIT(22)
	#घोषणा U2P_R0_V_ATE_TEST_EN_B_MASK			GENMASK(24, 23)
	#घोषणा U2P_R0_ID_SET_ID_DQ				BIT(25)
	#घोषणा U2P_R0_ATE_RESET				BIT(26)
	#घोषणा U2P_R0_FSV_MINUS				BIT(27)
	#घोषणा U2P_R0_FSV_PLUS					BIT(28)
	#घोषणा U2P_R0_BYPASS_DM_DATA				BIT(29)
	#घोषणा U2P_R0_BYPASS_DP_DATA				BIT(30)

#घोषणा U2P_R1							0x4
	#घोषणा U2P_R1_BURN_IN_TEST				BIT(0)
	#घोषणा U2P_R1_ACA_ENABLE				BIT(1)
	#घोषणा U2P_R1_DCD_ENABLE				BIT(2)
	#घोषणा U2P_R1_VDAT_SRC_EN_B				BIT(3)
	#घोषणा U2P_R1_VDAT_DET_EN_B				BIT(4)
	#घोषणा U2P_R1_CHARGES_SEL				BIT(5)
	#घोषणा U2P_R1_TX_PREEMP_PULSE_TUNE			BIT(6)
	#घोषणा U2P_R1_TX_PREEMP_AMP_TUNE_MASK			GENMASK(8, 7)
	#घोषणा U2P_R1_TX_RES_TUNE_MASK				GENMASK(10, 9)
	#घोषणा U2P_R1_TX_RISE_TUNE_MASK			GENMASK(12, 11)
	#घोषणा U2P_R1_TX_VREF_TUNE_MASK			GENMASK(16, 13)
	#घोषणा U2P_R1_TX_FSLS_TUNE_MASK			GENMASK(20, 17)
	#घोषणा U2P_R1_TX_HSXV_TUNE_MASK			GENMASK(22, 21)
	#घोषणा U2P_R1_OTG_TUNE_MASK				GENMASK(25, 23)
	#घोषणा U2P_R1_SQRX_TUNE_MASK				GENMASK(28, 26)
	#घोषणा U2P_R1_COMP_DIS_TUNE_MASK			GENMASK(31, 29)

/* bits [31:14] are पढ़ो-only */
#घोषणा U2P_R2							0x8
	#घोषणा U2P_R2_TESTDATA_IN_MASK				GENMASK(7, 0)
	#घोषणा U2P_R2_TESTADDR_MASK				GENMASK(11, 8)
	#घोषणा U2P_R2_TESTDATA_OUT_SEL				BIT(12)
	#घोषणा U2P_R2_TESTCLK					BIT(13)
	#घोषणा U2P_R2_TESTDATA_OUT_MASK			GENMASK(17, 14)
	#घोषणा U2P_R2_ACA_PIN_RANGE_C				BIT(18)
	#घोषणा U2P_R2_ACA_PIN_RANGE_B				BIT(19)
	#घोषणा U2P_R2_ACA_PIN_RANGE_A				BIT(20)
	#घोषणा U2P_R2_ACA_PIN_GND				BIT(21)
	#घोषणा U2P_R2_ACA_PIN_FLOAT				BIT(22)
	#घोषणा U2P_R2_CHARGE_DETECT				BIT(23)
	#घोषणा U2P_R2_DEVICE_SESSION_VALID			BIT(24)
	#घोषणा U2P_R2_ADP_PROBE				BIT(25)
	#घोषणा U2P_R2_ADP_SENSE				BIT(26)
	#घोषणा U2P_R2_SESSION_END				BIT(27)
	#घोषणा U2P_R2_VBUS_VALID				BIT(28)
	#घोषणा U2P_R2_B_VALID					BIT(29)
	#घोषणा U2P_R2_A_VALID					BIT(30)
	#घोषणा U2P_R2_ID_DIG					BIT(31)

#घोषणा U2P_R3							0xc

#घोषणा RESET_COMPLETE_TIME				500

काष्ठा phy_meson_gxl_usb2_priv अणु
	काष्ठा regmap		*regmap;
	क्रमागत phy_mode		mode;
	पूर्णांक			is_enabled;
	काष्ठा clk		*clk;
	काष्ठा reset_control	*reset;
पूर्ण;

अटल स्थिर काष्ठा regmap_config phy_meson_gxl_usb2_regmap_conf = अणु
	.reg_bits = 8,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = U2P_R3,
पूर्ण;

अटल पूर्णांक phy_meson_gxl_usb2_init(काष्ठा phy *phy)
अणु
	काष्ठा phy_meson_gxl_usb2_priv *priv = phy_get_drvdata(phy);
	पूर्णांक ret;

	ret = reset_control_reset(priv->reset);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(priv->clk);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक phy_meson_gxl_usb2_निकास(काष्ठा phy *phy)
अणु
	काष्ठा phy_meson_gxl_usb2_priv *priv = phy_get_drvdata(phy);

	clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक phy_meson_gxl_usb2_reset(काष्ठा phy *phy)
अणु
	काष्ठा phy_meson_gxl_usb2_priv *priv = phy_get_drvdata(phy);

	अगर (priv->is_enabled) अणु
		/* reset the PHY and रुको until settings are stabilized */
		regmap_update_bits(priv->regmap, U2P_R0, U2P_R0_POWER_ON_RESET,
				   U2P_R0_POWER_ON_RESET);
		udelay(RESET_COMPLETE_TIME);
		regmap_update_bits(priv->regmap, U2P_R0, U2P_R0_POWER_ON_RESET,
				   0);
		udelay(RESET_COMPLETE_TIME);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक phy_meson_gxl_usb2_set_mode(काष्ठा phy *phy,
				       क्रमागत phy_mode mode, पूर्णांक submode)
अणु
	काष्ठा phy_meson_gxl_usb2_priv *priv = phy_get_drvdata(phy);

	चयन (mode) अणु
	हाल PHY_MODE_USB_HOST:
	हाल PHY_MODE_USB_OTG:
		regmap_update_bits(priv->regmap, U2P_R0, U2P_R0_DM_PULLDOWN,
				   U2P_R0_DM_PULLDOWN);
		regmap_update_bits(priv->regmap, U2P_R0, U2P_R0_DP_PULLDOWN,
				   U2P_R0_DP_PULLDOWN);
		regmap_update_bits(priv->regmap, U2P_R0, U2P_R0_ID_PULLUP,
				   U2P_R0_ID_PULLUP);
		अवरोध;

	हाल PHY_MODE_USB_DEVICE:
		regmap_update_bits(priv->regmap, U2P_R0, U2P_R0_DM_PULLDOWN,
				   0);
		regmap_update_bits(priv->regmap, U2P_R0, U2P_R0_DP_PULLDOWN,
				   0);
		regmap_update_bits(priv->regmap, U2P_R0, U2P_R0_ID_PULLUP,
				   U2P_R0_ID_PULLUP);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	phy_meson_gxl_usb2_reset(phy);

	priv->mode = mode;

	वापस 0;
पूर्ण

अटल पूर्णांक phy_meson_gxl_usb2_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा phy_meson_gxl_usb2_priv *priv = phy_get_drvdata(phy);

	priv->is_enabled = 0;

	/* घातer off the PHY by putting it पूर्णांकo reset mode */
	regmap_update_bits(priv->regmap, U2P_R0, U2P_R0_POWER_ON_RESET,
			   U2P_R0_POWER_ON_RESET);

	वापस 0;
पूर्ण

अटल पूर्णांक phy_meson_gxl_usb2_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा phy_meson_gxl_usb2_priv *priv = phy_get_drvdata(phy);
	पूर्णांक ret;

	priv->is_enabled = 1;

	/* घातer on the PHY by taking it out of reset mode */
	regmap_update_bits(priv->regmap, U2P_R0, U2P_R0_POWER_ON_RESET, 0);

	ret = phy_meson_gxl_usb2_set_mode(phy, priv->mode, 0);
	अगर (ret) अणु
		phy_meson_gxl_usb2_घातer_off(phy);

		dev_err(&phy->dev, "Failed to initialize PHY with mode %d\n",
			priv->mode);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops phy_meson_gxl_usb2_ops = अणु
	.init		= phy_meson_gxl_usb2_init,
	.निकास		= phy_meson_gxl_usb2_निकास,
	.घातer_on	= phy_meson_gxl_usb2_घातer_on,
	.घातer_off	= phy_meson_gxl_usb2_घातer_off,
	.set_mode	= phy_meson_gxl_usb2_set_mode,
	.reset		= phy_meson_gxl_usb2_reset,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक phy_meson_gxl_usb2_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा phy_provider *phy_provider;
	काष्ठा phy_meson_gxl_usb2_priv *priv;
	काष्ठा phy *phy;
	व्योम __iomem *base;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, priv);

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	/* start in host mode */
	priv->mode = PHY_MODE_USB_HOST;

	priv->regmap = devm_regmap_init_mmio(dev, base,
					     &phy_meson_gxl_usb2_regmap_conf);
	अगर (IS_ERR(priv->regmap))
		वापस PTR_ERR(priv->regmap);

	priv->clk = devm_clk_get_optional(dev, "phy");
	अगर (IS_ERR(priv->clk))
		वापस PTR_ERR(priv->clk);

	priv->reset = devm_reset_control_get_optional_shared(dev, "phy");
	अगर (IS_ERR(priv->reset))
		वापस PTR_ERR(priv->reset);

	phy = devm_phy_create(dev, शून्य, &phy_meson_gxl_usb2_ops);
	अगर (IS_ERR(phy)) अणु
		ret = PTR_ERR(phy);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to create PHY\n");

		वापस ret;
	पूर्ण

	phy_set_drvdata(phy, priv);

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);

	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल स्थिर काष्ठा of_device_id phy_meson_gxl_usb2_of_match[] = अणु
	अणु .compatible = "amlogic,meson-gxl-usb2-phy", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, phy_meson_gxl_usb2_of_match);

अटल काष्ठा platक्रमm_driver phy_meson_gxl_usb2_driver = अणु
	.probe	= phy_meson_gxl_usb2_probe,
	.driver	= अणु
		.name		= "phy-meson-gxl-usb2",
		.of_match_table	= phy_meson_gxl_usb2_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(phy_meson_gxl_usb2_driver);

MODULE_AUTHOR("Martin Blumenstingl <martin.blumenstingl@googlemail.com>");
MODULE_DESCRIPTION("Meson GXL and GXM USB2 PHY driver");
MODULE_LICENSE("GPL v2");
