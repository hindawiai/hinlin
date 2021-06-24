<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Meson G12A USB2 PHY driver
 *
 * Copyright (C) 2017 Martin Blumenstingl <martin.blumenstingl@googlemail.com>
 * Copyright (C) 2017 Amlogic, Inc. All rights reserved
 * Copyright (C) 2019 BayLibre, SAS
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा PHY_CTRL_R0						0x0
#घोषणा PHY_CTRL_R1						0x4
#घोषणा PHY_CTRL_R2						0x8
#घोषणा PHY_CTRL_R3						0xc
	#घोषणा PHY_CTRL_R3_SQUELCH_REF				GENMASK(1, 0)
	#घोषणा PHY_CTRL_R3_HSDIC_REF				GENMASK(3, 2)
	#घोषणा PHY_CTRL_R3_DISC_THRESH				GENMASK(7, 4)

#घोषणा PHY_CTRL_R4						0x10
	#घोषणा PHY_CTRL_R4_CALIB_CODE_7_0			GENMASK(7, 0)
	#घोषणा PHY_CTRL_R4_CALIB_CODE_15_8			GENMASK(15, 8)
	#घोषणा PHY_CTRL_R4_CALIB_CODE_23_16			GENMASK(23, 16)
	#घोषणा PHY_CTRL_R4_I_C2L_CAL_EN			BIT(24)
	#घोषणा PHY_CTRL_R4_I_C2L_CAL_RESET_N			BIT(25)
	#घोषणा PHY_CTRL_R4_I_C2L_CAL_DONE			BIT(26)
	#घोषणा PHY_CTRL_R4_TEST_BYPASS_MODE_EN			BIT(27)
	#घोषणा PHY_CTRL_R4_I_C2L_BIAS_TRIM_1_0			GENMASK(29, 28)
	#घोषणा PHY_CTRL_R4_I_C2L_BIAS_TRIM_3_2			GENMASK(31, 30)

#घोषणा PHY_CTRL_R5						0x14
#घोषणा PHY_CTRL_R6						0x18
#घोषणा PHY_CTRL_R7						0x1c
#घोषणा PHY_CTRL_R8						0x20
#घोषणा PHY_CTRL_R9						0x24
#घोषणा PHY_CTRL_R10						0x28
#घोषणा PHY_CTRL_R11						0x2c
#घोषणा PHY_CTRL_R12						0x30
#घोषणा PHY_CTRL_R13						0x34
	#घोषणा PHY_CTRL_R13_CUSTOM_PATTERN_19			GENMASK(7, 0)
	#घोषणा PHY_CTRL_R13_LOAD_STAT				BIT(14)
	#घोषणा PHY_CTRL_R13_UPDATE_PMA_SIGNALS			BIT(15)
	#घोषणा PHY_CTRL_R13_MIN_COUNT_FOR_SYNC_DET		GENMASK(20, 16)
	#घोषणा PHY_CTRL_R13_CLEAR_HOLD_HS_DISCONNECT		BIT(21)
	#घोषणा PHY_CTRL_R13_BYPASS_HOST_DISCONNECT_VAL		BIT(22)
	#घोषणा PHY_CTRL_R13_BYPASS_HOST_DISCONNECT_EN		BIT(23)
	#घोषणा PHY_CTRL_R13_I_C2L_HS_EN			BIT(24)
	#घोषणा PHY_CTRL_R13_I_C2L_FS_EN			BIT(25)
	#घोषणा PHY_CTRL_R13_I_C2L_LS_EN			BIT(26)
	#घोषणा PHY_CTRL_R13_I_C2L_HS_OE			BIT(27)
	#घोषणा PHY_CTRL_R13_I_C2L_FS_OE			BIT(28)
	#घोषणा PHY_CTRL_R13_I_C2L_HS_RX_EN			BIT(29)
	#घोषणा PHY_CTRL_R13_I_C2L_FSLS_RX_EN			BIT(30)

#घोषणा PHY_CTRL_R14						0x38
	#घोषणा PHY_CTRL_R14_I_RDP_EN				BIT(0)
	#घोषणा PHY_CTRL_R14_I_RPU_SW1_EN			BIT(1)
	#घोषणा PHY_CTRL_R14_I_RPU_SW2_EN			GENMASK(3, 2)
	#घोषणा PHY_CTRL_R14_PG_RSTN				BIT(4)
	#घोषणा PHY_CTRL_R14_I_C2L_DATA_16_8			BIT(5)
	#घोषणा PHY_CTRL_R14_I_C2L_ASSERT_SINGLE_EN_ZERO	BIT(6)
	#घोषणा PHY_CTRL_R14_BYPASS_CTRL_7_0			GENMASK(15, 8)
	#घोषणा PHY_CTRL_R14_BYPASS_CTRL_15_8			GENMASK(23, 16)

#घोषणा PHY_CTRL_R15						0x3c
#घोषणा PHY_CTRL_R16						0x40
	#घोषणा PHY_CTRL_R16_MPLL_M				GENMASK(8, 0)
	#घोषणा PHY_CTRL_R16_MPLL_N				GENMASK(14, 10)
	#घोषणा PHY_CTRL_R16_MPLL_TDC_MODE			BIT(20)
	#घोषणा PHY_CTRL_R16_MPLL_SDM_EN			BIT(21)
	#घोषणा PHY_CTRL_R16_MPLL_LOAD				BIT(22)
	#घोषणा PHY_CTRL_R16_MPLL_DCO_SDM_EN			BIT(23)
	#घोषणा PHY_CTRL_R16_MPLL_LOCK_LONG			GENMASK(25, 24)
	#घोषणा PHY_CTRL_R16_MPLL_LOCK_F			BIT(26)
	#घोषणा PHY_CTRL_R16_MPLL_FAST_LOCK			BIT(27)
	#घोषणा PHY_CTRL_R16_MPLL_EN				BIT(28)
	#घोषणा PHY_CTRL_R16_MPLL_RESET				BIT(29)
	#घोषणा PHY_CTRL_R16_MPLL_LOCK				BIT(30)
	#घोषणा PHY_CTRL_R16_MPLL_LOCK_DIG			BIT(31)

#घोषणा PHY_CTRL_R17						0x44
	#घोषणा PHY_CTRL_R17_MPLL_FRAC_IN			GENMASK(13, 0)
	#घोषणा PHY_CTRL_R17_MPLL_FIX_EN			BIT(16)
	#घोषणा PHY_CTRL_R17_MPLL_LAMBDA1			GENMASK(19, 17)
	#घोषणा PHY_CTRL_R17_MPLL_LAMBDA0			GENMASK(22, 20)
	#घोषणा PHY_CTRL_R17_MPLL_FILTER_MODE			BIT(23)
	#घोषणा PHY_CTRL_R17_MPLL_FILTER_PVT2			GENMASK(27, 24)
	#घोषणा PHY_CTRL_R17_MPLL_FILTER_PVT1			GENMASK(31, 28)

#घोषणा PHY_CTRL_R18						0x48
	#घोषणा PHY_CTRL_R18_MPLL_LKW_SEL			GENMASK(1, 0)
	#घोषणा PHY_CTRL_R18_MPLL_LK_W				GENMASK(5, 2)
	#घोषणा PHY_CTRL_R18_MPLL_LK_S				GENMASK(11, 6)
	#घोषणा PHY_CTRL_R18_MPLL_DCO_M_EN			BIT(12)
	#घोषणा PHY_CTRL_R18_MPLL_DCO_CLK_SEL			BIT(13)
	#घोषणा PHY_CTRL_R18_MPLL_PFD_GAIN			GENMASK(15, 14)
	#घोषणा PHY_CTRL_R18_MPLL_ROU				GENMASK(18, 16)
	#घोषणा PHY_CTRL_R18_MPLL_DATA_SEL			GENMASK(21, 19)
	#घोषणा PHY_CTRL_R18_MPLL_BIAS_ADJ			GENMASK(23, 22)
	#घोषणा PHY_CTRL_R18_MPLL_BB_MODE			GENMASK(25, 24)
	#घोषणा PHY_CTRL_R18_MPLL_ALPHA				GENMASK(28, 26)
	#घोषणा PHY_CTRL_R18_MPLL_ADJ_LDO			GENMASK(30, 29)
	#घोषणा PHY_CTRL_R18_MPLL_ACG_RANGE			BIT(31)

#घोषणा PHY_CTRL_R19						0x4c
#घोषणा PHY_CTRL_R20						0x50
	#घोषणा PHY_CTRL_R20_USB2_IDDET_EN			BIT(0)
	#घोषणा PHY_CTRL_R20_USB2_OTG_VBUS_TRIM_2_0		GENMASK(3, 1)
	#घोषणा PHY_CTRL_R20_USB2_OTG_VBUSDET_EN		BIT(4)
	#घोषणा PHY_CTRL_R20_USB2_AMON_EN			BIT(5)
	#घोषणा PHY_CTRL_R20_USB2_CAL_CODE_R5			BIT(6)
	#घोषणा PHY_CTRL_R20_BYPASS_OTG_DET			BIT(7)
	#घोषणा PHY_CTRL_R20_USB2_DMON_EN			BIT(8)
	#घोषणा PHY_CTRL_R20_USB2_DMON_SEL_3_0			GENMASK(12, 9)
	#घोषणा PHY_CTRL_R20_USB2_EDGE_DRV_EN			BIT(13)
	#घोषणा PHY_CTRL_R20_USB2_EDGE_DRV_TRIM_1_0		GENMASK(15, 14)
	#घोषणा PHY_CTRL_R20_USB2_BGR_ADJ_4_0			GENMASK(20, 16)
	#घोषणा PHY_CTRL_R20_USB2_BGR_START			BIT(21)
	#घोषणा PHY_CTRL_R20_USB2_BGR_VREF_4_0			GENMASK(28, 24)
	#घोषणा PHY_CTRL_R20_USB2_BGR_DBG_1_0			GENMASK(30, 29)
	#घोषणा PHY_CTRL_R20_BYPASS_CAL_DONE_R5			BIT(31)

#घोषणा PHY_CTRL_R21						0x54
	#घोषणा PHY_CTRL_R21_USB2_BGR_FORCE			BIT(0)
	#घोषणा PHY_CTRL_R21_USB2_CAL_ACK_EN			BIT(1)
	#घोषणा PHY_CTRL_R21_USB2_OTG_ACA_EN			BIT(2)
	#घोषणा PHY_CTRL_R21_USB2_TX_STRG_PD			BIT(3)
	#घोषणा PHY_CTRL_R21_USB2_OTG_ACA_TRIM_1_0		GENMASK(5, 4)
	#घोषणा PHY_CTRL_R21_BYPASS_UTMI_CNTR			GENMASK(15, 6)
	#घोषणा PHY_CTRL_R21_BYPASS_UTMI_REG			GENMASK(25, 20)

#घोषणा PHY_CTRL_R22						0x58
#घोषणा PHY_CTRL_R23						0x5c

#घोषणा RESET_COMPLETE_TIME					1000
#घोषणा PLL_RESET_COMPLETE_TIME					100

क्रमागत meson_soc_id अणु
	MESON_SOC_G12A  = 0,
	MESON_SOC_A1,
पूर्ण;

काष्ठा phy_meson_g12a_usb2_priv अणु
	काष्ठा device		*dev;
	काष्ठा regmap		*regmap;
	काष्ठा clk		*clk;
	काष्ठा reset_control	*reset;
	पूर्णांक                     soc_id;
पूर्ण;

अटल स्थिर काष्ठा regmap_config phy_meson_g12a_usb2_regmap_conf = अणु
	.reg_bits = 8,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = PHY_CTRL_R23,
पूर्ण;

अटल पूर्णांक phy_meson_g12a_usb2_init(काष्ठा phy *phy)
अणु
	काष्ठा phy_meson_g12a_usb2_priv *priv = phy_get_drvdata(phy);
	पूर्णांक ret;
	अचिन्हित पूर्णांक value;

	ret = reset_control_reset(priv->reset);
	अगर (ret)
		वापस ret;

	udelay(RESET_COMPLETE_TIME);

	/* usb2_otg_aca_en == 0 */
	regmap_update_bits(priv->regmap, PHY_CTRL_R21,
			   PHY_CTRL_R21_USB2_OTG_ACA_EN, 0);

	/* PLL Setup : 24MHz * 20 / 1 = 480MHz */
	regmap_ग_लिखो(priv->regmap, PHY_CTRL_R16,
		     FIELD_PREP(PHY_CTRL_R16_MPLL_M, 20) |
		     FIELD_PREP(PHY_CTRL_R16_MPLL_N, 1) |
		     PHY_CTRL_R16_MPLL_LOAD |
		     FIELD_PREP(PHY_CTRL_R16_MPLL_LOCK_LONG, 1) |
		     PHY_CTRL_R16_MPLL_FAST_LOCK |
		     PHY_CTRL_R16_MPLL_EN |
		     PHY_CTRL_R16_MPLL_RESET);

	regmap_ग_लिखो(priv->regmap, PHY_CTRL_R17,
		     FIELD_PREP(PHY_CTRL_R17_MPLL_FRAC_IN, 0) |
		     FIELD_PREP(PHY_CTRL_R17_MPLL_LAMBDA1, 7) |
		     FIELD_PREP(PHY_CTRL_R17_MPLL_LAMBDA0, 7) |
		     FIELD_PREP(PHY_CTRL_R17_MPLL_FILTER_PVT2, 2) |
		     FIELD_PREP(PHY_CTRL_R17_MPLL_FILTER_PVT1, 9));

	value = FIELD_PREP(PHY_CTRL_R18_MPLL_LKW_SEL, 1) |
		FIELD_PREP(PHY_CTRL_R18_MPLL_LK_W, 9) |
		FIELD_PREP(PHY_CTRL_R18_MPLL_LK_S, 0x27) |
		FIELD_PREP(PHY_CTRL_R18_MPLL_PFD_GAIN, 1) |
		FIELD_PREP(PHY_CTRL_R18_MPLL_ROU, 7) |
		FIELD_PREP(PHY_CTRL_R18_MPLL_DATA_SEL, 3) |
		FIELD_PREP(PHY_CTRL_R18_MPLL_BIAS_ADJ, 1) |
		FIELD_PREP(PHY_CTRL_R18_MPLL_BB_MODE, 0) |
		FIELD_PREP(PHY_CTRL_R18_MPLL_ALPHA, 3) |
		FIELD_PREP(PHY_CTRL_R18_MPLL_ADJ_LDO, 1) |
		PHY_CTRL_R18_MPLL_ACG_RANGE;

	अगर (priv->soc_id == MESON_SOC_A1)
		value |= PHY_CTRL_R18_MPLL_DCO_CLK_SEL;

	regmap_ग_लिखो(priv->regmap, PHY_CTRL_R18, value);

	udelay(PLL_RESET_COMPLETE_TIME);

	/* UnReset PLL */
	regmap_ग_लिखो(priv->regmap, PHY_CTRL_R16,
		     FIELD_PREP(PHY_CTRL_R16_MPLL_M, 20) |
		     FIELD_PREP(PHY_CTRL_R16_MPLL_N, 1) |
		     PHY_CTRL_R16_MPLL_LOAD |
		     FIELD_PREP(PHY_CTRL_R16_MPLL_LOCK_LONG, 1) |
		     PHY_CTRL_R16_MPLL_FAST_LOCK |
		     PHY_CTRL_R16_MPLL_EN);

	/* PHY Tuning */
	regmap_ग_लिखो(priv->regmap, PHY_CTRL_R20,
		     FIELD_PREP(PHY_CTRL_R20_USB2_OTG_VBUS_TRIM_2_0, 4) |
		     PHY_CTRL_R20_USB2_OTG_VBUSDET_EN |
		     FIELD_PREP(PHY_CTRL_R20_USB2_DMON_SEL_3_0, 15) |
		     PHY_CTRL_R20_USB2_EDGE_DRV_EN |
		     FIELD_PREP(PHY_CTRL_R20_USB2_EDGE_DRV_TRIM_1_0, 3) |
		     FIELD_PREP(PHY_CTRL_R20_USB2_BGR_ADJ_4_0, 0) |
		     FIELD_PREP(PHY_CTRL_R20_USB2_BGR_VREF_4_0, 0) |
		     FIELD_PREP(PHY_CTRL_R20_USB2_BGR_DBG_1_0, 0));

	अगर (priv->soc_id == MESON_SOC_G12A)
		regmap_ग_लिखो(priv->regmap, PHY_CTRL_R4,
			     FIELD_PREP(PHY_CTRL_R4_CALIB_CODE_7_0, 0xf) |
			     FIELD_PREP(PHY_CTRL_R4_CALIB_CODE_15_8, 0xf) |
			     FIELD_PREP(PHY_CTRL_R4_CALIB_CODE_23_16, 0xf) |
			     PHY_CTRL_R4_TEST_BYPASS_MODE_EN |
			     FIELD_PREP(PHY_CTRL_R4_I_C2L_BIAS_TRIM_1_0, 0) |
			     FIELD_PREP(PHY_CTRL_R4_I_C2L_BIAS_TRIM_3_2, 0));
	अन्यथा अगर (priv->soc_id == MESON_SOC_A1) अणु
		regmap_ग_लिखो(priv->regmap, PHY_CTRL_R21,
			     PHY_CTRL_R21_USB2_CAL_ACK_EN |
			     PHY_CTRL_R21_USB2_TX_STRG_PD |
			     FIELD_PREP(PHY_CTRL_R21_USB2_OTG_ACA_TRIM_1_0, 2));

		/* Analog Settings */
		regmap_ग_लिखो(priv->regmap, PHY_CTRL_R13,
			     FIELD_PREP(PHY_CTRL_R13_MIN_COUNT_FOR_SYNC_DET, 7));
	पूर्ण

	/* Tuning Disconnect Threshold */
	regmap_ग_लिखो(priv->regmap, PHY_CTRL_R3,
		     FIELD_PREP(PHY_CTRL_R3_SQUELCH_REF, 0) |
		     FIELD_PREP(PHY_CTRL_R3_HSDIC_REF, 1) |
		     FIELD_PREP(PHY_CTRL_R3_DISC_THRESH, 3));

	अगर (priv->soc_id == MESON_SOC_G12A) अणु
		/* Analog Settings */
		regmap_ग_लिखो(priv->regmap, PHY_CTRL_R14, 0);
		regmap_ग_लिखो(priv->regmap, PHY_CTRL_R13,
			     PHY_CTRL_R13_UPDATE_PMA_SIGNALS |
			     FIELD_PREP(PHY_CTRL_R13_MIN_COUNT_FOR_SYNC_DET, 7));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक phy_meson_g12a_usb2_निकास(काष्ठा phy *phy)
अणु
	काष्ठा phy_meson_g12a_usb2_priv *priv = phy_get_drvdata(phy);

	वापस reset_control_reset(priv->reset);
पूर्ण

/* set_mode is not needed, mode setting is handled via the UTMI bus */
अटल स्थिर काष्ठा phy_ops phy_meson_g12a_usb2_ops = अणु
	.init		= phy_meson_g12a_usb2_init,
	.निकास		= phy_meson_g12a_usb2_निकास,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक phy_meson_g12a_usb2_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा phy_provider *phy_provider;
	काष्ठा phy_meson_g12a_usb2_priv *priv;
	काष्ठा phy *phy;
	व्योम __iomem *base;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = dev;
	platक्रमm_set_drvdata(pdev, priv);

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	priv->soc_id = (क्रमागत meson_soc_id)of_device_get_match_data(&pdev->dev);

	priv->regmap = devm_regmap_init_mmio(dev, base,
					     &phy_meson_g12a_usb2_regmap_conf);
	अगर (IS_ERR(priv->regmap))
		वापस PTR_ERR(priv->regmap);

	priv->clk = devm_clk_get(dev, "xtal");
	अगर (IS_ERR(priv->clk))
		वापस PTR_ERR(priv->clk);

	priv->reset = devm_reset_control_get(dev, "phy");
	अगर (IS_ERR(priv->reset))
		वापस PTR_ERR(priv->reset);

	ret = reset_control_deनिश्चित(priv->reset);
	अगर (ret)
		वापस ret;

	phy = devm_phy_create(dev, शून्य, &phy_meson_g12a_usb2_ops);
	अगर (IS_ERR(phy)) अणु
		ret = PTR_ERR(phy);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to create PHY\n");

		वापस ret;
	पूर्ण

	phy_set_bus_width(phy, 8);
	phy_set_drvdata(phy, priv);

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);

	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल स्थिर काष्ठा of_device_id phy_meson_g12a_usb2_of_match[] = अणु
	अणु
		.compatible = "amlogic,g12a-usb2-phy",
		.data = (व्योम *)MESON_SOC_G12A,
	पूर्ण,
	अणु
		.compatible = "amlogic,a1-usb2-phy",
		.data = (व्योम *)MESON_SOC_A1,
	पूर्ण,
	अणु /* Sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, phy_meson_g12a_usb2_of_match);

अटल काष्ठा platक्रमm_driver phy_meson_g12a_usb2_driver = अणु
	.probe	= phy_meson_g12a_usb2_probe,
	.driver	= अणु
		.name		= "phy-meson-g12a-usb2",
		.of_match_table	= phy_meson_g12a_usb2_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(phy_meson_g12a_usb2_driver);

MODULE_AUTHOR("Martin Blumenstingl <martin.blumenstingl@googlemail.com>");
MODULE_AUTHOR("Neil Armstrong <narmstrong@baylibre.com>");
MODULE_DESCRIPTION("Meson G12A USB2 PHY driver");
MODULE_LICENSE("GPL v2");
