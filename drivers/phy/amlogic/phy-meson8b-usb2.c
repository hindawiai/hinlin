<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Meson8, Meson8b and GXBB USB2 PHY driver
 *
 * Copyright (C) 2016 Martin Blumenstingl <martin.blumenstingl@googlemail.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/usb/of.h>

#घोषणा REG_CONFIG					0x00
	#घोषणा REG_CONFIG_CLK_EN			BIT(0)
	#घोषणा REG_CONFIG_CLK_SEL_MASK			GENMASK(3, 1)
	#घोषणा REG_CONFIG_CLK_DIV_MASK			GENMASK(10, 4)
	#घोषणा REG_CONFIG_CLK_32k_ALTSEL		BIT(15)
	#घोषणा REG_CONFIG_TEST_TRIG			BIT(31)

#घोषणा REG_CTRL					0x04
	#घोषणा REG_CTRL_SOFT_PRST			BIT(0)
	#घोषणा REG_CTRL_SOFT_HRESET			BIT(1)
	#घोषणा REG_CTRL_SS_SCALEDOWN_MODE_MASK		GENMASK(3, 2)
	#घोषणा REG_CTRL_CLK_DET_RST			BIT(4)
	#घोषणा REG_CTRL_INTR_SEL			BIT(5)
	#घोषणा REG_CTRL_CLK_DETECTED			BIT(8)
	#घोषणा REG_CTRL_SOF_SENT_RCVD_TGL		BIT(9)
	#घोषणा REG_CTRL_SOF_TOGGLE_OUT			BIT(10)
	#घोषणा REG_CTRL_POWER_ON_RESET			BIT(15)
	#घोषणा REG_CTRL_SLEEPM				BIT(16)
	#घोषणा REG_CTRL_TX_BITSTUFF_ENN_H		BIT(17)
	#घोषणा REG_CTRL_TX_BITSTUFF_ENN		BIT(18)
	#घोषणा REG_CTRL_COMMON_ON			BIT(19)
	#घोषणा REG_CTRL_REF_CLK_SEL_MASK		GENMASK(21, 20)
	#घोषणा REG_CTRL_REF_CLK_SEL_SHIFT		20
	#घोषणा REG_CTRL_FSEL_MASK			GENMASK(24, 22)
	#घोषणा REG_CTRL_FSEL_SHIFT			22
	#घोषणा REG_CTRL_PORT_RESET			BIT(25)
	#घोषणा REG_CTRL_THREAD_ID_MASK			GENMASK(31, 26)

#घोषणा REG_ENDP_INTR					0x08

/* bits [31:26], [24:21] and [15:3] seem to be पढ़ो-only */
#घोषणा REG_ADP_BC					0x0c
	#घोषणा REG_ADP_BC_VBUS_VLD_EXT_SEL		BIT(0)
	#घोषणा REG_ADP_BC_VBUS_VLD_EXT			BIT(1)
	#घोषणा REG_ADP_BC_OTG_DISABLE			BIT(2)
	#घोषणा REG_ADP_BC_ID_PULLUP			BIT(3)
	#घोषणा REG_ADP_BC_DRV_VBUS			BIT(4)
	#घोषणा REG_ADP_BC_ADP_PRB_EN			BIT(5)
	#घोषणा REG_ADP_BC_ADP_DISCHARGE		BIT(6)
	#घोषणा REG_ADP_BC_ADP_CHARGE			BIT(7)
	#घोषणा REG_ADP_BC_SESS_END			BIT(8)
	#घोषणा REG_ADP_BC_DEVICE_SESS_VLD		BIT(9)
	#घोषणा REG_ADP_BC_B_VALID			BIT(10)
	#घोषणा REG_ADP_BC_A_VALID			BIT(11)
	#घोषणा REG_ADP_BC_ID_DIG			BIT(12)
	#घोषणा REG_ADP_BC_VBUS_VALID			BIT(13)
	#घोषणा REG_ADP_BC_ADP_PROBE			BIT(14)
	#घोषणा REG_ADP_BC_ADP_SENSE			BIT(15)
	#घोषणा REG_ADP_BC_ACA_ENABLE			BIT(16)
	#घोषणा REG_ADP_BC_DCD_ENABLE			BIT(17)
	#घोषणा REG_ADP_BC_VDAT_DET_EN_B		BIT(18)
	#घोषणा REG_ADP_BC_VDAT_SRC_EN_B		BIT(19)
	#घोषणा REG_ADP_BC_CHARGE_SEL			BIT(20)
	#घोषणा REG_ADP_BC_CHARGE_DETECT		BIT(21)
	#घोषणा REG_ADP_BC_ACA_PIN_RANGE_C		BIT(22)
	#घोषणा REG_ADP_BC_ACA_PIN_RANGE_B		BIT(23)
	#घोषणा REG_ADP_BC_ACA_PIN_RANGE_A		BIT(24)
	#घोषणा REG_ADP_BC_ACA_PIN_GND			BIT(25)
	#घोषणा REG_ADP_BC_ACA_PIN_FLOAT		BIT(26)

#घोषणा REG_DBG_UART					0x10
	#घोषणा REG_DBG_UART_BYPASS_SEL			BIT(0)
	#घोषणा REG_DBG_UART_BYPASS_DM_EN		BIT(1)
	#घोषणा REG_DBG_UART_BYPASS_DP_EN		BIT(2)
	#घोषणा REG_DBG_UART_BYPASS_DM_DATA		BIT(3)
	#घोषणा REG_DBG_UART_BYPASS_DP_DATA		BIT(4)
	#घोषणा REG_DBG_UART_FSV_MINUS			BIT(5)
	#घोषणा REG_DBG_UART_FSV_PLUS			BIT(6)
	#घोषणा REG_DBG_UART_FSV_BURN_IN_TEST		BIT(7)
	#घोषणा REG_DBG_UART_LOOPBACK_EN_B		BIT(8)
	#घोषणा REG_DBG_UART_SET_IDDQ			BIT(9)
	#घोषणा REG_DBG_UART_ATE_RESET			BIT(10)

#घोषणा REG_TEST					0x14
	#घोषणा REG_TEST_DATA_IN_MASK			GENMASK(3, 0)
	#घोषणा REG_TEST_EN_MASK			GENMASK(7, 4)
	#घोषणा REG_TEST_ADDR_MASK			GENMASK(11, 8)
	#घोषणा REG_TEST_DATA_OUT_SEL			BIT(12)
	#घोषणा REG_TEST_CLK				BIT(13)
	#घोषणा REG_TEST_VA_TEST_EN_B_MASK		GENMASK(15, 14)
	#घोषणा REG_TEST_DATA_OUT_MASK			GENMASK(19, 16)
	#घोषणा REG_TEST_DISABLE_ID_PULLUP		BIT(20)

#घोषणा REG_TUNE					0x18
	#घोषणा REG_TUNE_TX_RES_TUNE_MASK		GENMASK(1, 0)
	#घोषणा REG_TUNE_TX_HSXV_TUNE_MASK		GENMASK(3, 2)
	#घोषणा REG_TUNE_TX_VREF_TUNE_MASK		GENMASK(7, 4)
	#घोषणा REG_TUNE_TX_RISE_TUNE_MASK		GENMASK(9, 8)
	#घोषणा REG_TUNE_TX_PREEMP_PULSE_TUNE		BIT(10)
	#घोषणा REG_TUNE_TX_PREEMP_AMP_TUNE_MASK	GENMASK(12, 11)
	#घोषणा REG_TUNE_TX_FSLS_TUNE_MASK		GENMASK(16, 13)
	#घोषणा REG_TUNE_SQRX_TUNE_MASK			GENMASK(19, 17)
	#घोषणा REG_TUNE_OTG_TUNE			GENMASK(22, 20)
	#घोषणा REG_TUNE_COMP_DIS_TUNE			GENMASK(25, 23)
	#घोषणा REG_TUNE_HOST_DM_PULLDOWN		BIT(26)
	#घोषणा REG_TUNE_HOST_DP_PULLDOWN		BIT(27)

#घोषणा RESET_COMPLETE_TIME				500
#घोषणा ACA_ENABLE_COMPLETE_TIME			50

काष्ठा phy_meson8b_usb2_match_data अणु
	bool			host_enable_aca;
पूर्ण;

काष्ठा phy_meson8b_usb2_priv अणु
	काष्ठा regmap					*regmap;
	क्रमागत usb_dr_mode				dr_mode;
	काष्ठा clk					*clk_usb_general;
	काष्ठा clk					*clk_usb;
	काष्ठा reset_control				*reset;
	स्थिर काष्ठा phy_meson8b_usb2_match_data	*match;
पूर्ण;

अटल स्थिर काष्ठा regmap_config phy_meson8b_usb2_regmap_conf = अणु
	.reg_bits = 8,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = REG_TUNE,
पूर्ण;

अटल पूर्णांक phy_meson8b_usb2_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा phy_meson8b_usb2_priv *priv = phy_get_drvdata(phy);
	u32 reg;
	पूर्णांक ret;

	अगर (!IS_ERR_OR_शून्य(priv->reset)) अणु
		ret = reset_control_reset(priv->reset);
		अगर (ret) अणु
			dev_err(&phy->dev, "Failed to trigger USB reset\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = clk_prepare_enable(priv->clk_usb_general);
	अगर (ret) अणु
		dev_err(&phy->dev, "Failed to enable USB general clock\n");
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(priv->clk_usb);
	अगर (ret) अणु
		dev_err(&phy->dev, "Failed to enable USB DDR clock\n");
		clk_disable_unprepare(priv->clk_usb_general);
		वापस ret;
	पूर्ण

	regmap_update_bits(priv->regmap, REG_CONFIG, REG_CONFIG_CLK_32k_ALTSEL,
			   REG_CONFIG_CLK_32k_ALTSEL);

	regmap_update_bits(priv->regmap, REG_CTRL, REG_CTRL_REF_CLK_SEL_MASK,
			   0x2 << REG_CTRL_REF_CLK_SEL_SHIFT);

	regmap_update_bits(priv->regmap, REG_CTRL, REG_CTRL_FSEL_MASK,
			   0x5 << REG_CTRL_FSEL_SHIFT);

	/* reset the PHY */
	regmap_update_bits(priv->regmap, REG_CTRL, REG_CTRL_POWER_ON_RESET,
			   REG_CTRL_POWER_ON_RESET);
	udelay(RESET_COMPLETE_TIME);
	regmap_update_bits(priv->regmap, REG_CTRL, REG_CTRL_POWER_ON_RESET, 0);
	udelay(RESET_COMPLETE_TIME);

	regmap_update_bits(priv->regmap, REG_CTRL, REG_CTRL_SOF_TOGGLE_OUT,
			   REG_CTRL_SOF_TOGGLE_OUT);

	अगर (priv->dr_mode == USB_DR_MODE_HOST) अणु
		regmap_update_bits(priv->regmap, REG_DBG_UART,
				   REG_DBG_UART_SET_IDDQ, 0);

		अगर (priv->match->host_enable_aca) अणु
			regmap_update_bits(priv->regmap, REG_ADP_BC,
					   REG_ADP_BC_ACA_ENABLE,
					   REG_ADP_BC_ACA_ENABLE);

			udelay(ACA_ENABLE_COMPLETE_TIME);

			regmap_पढ़ो(priv->regmap, REG_ADP_BC, &reg);
			अगर (reg & REG_ADP_BC_ACA_PIN_FLOAT) अणु
				dev_warn(&phy->dev, "USB ID detect failed!\n");
				clk_disable_unprepare(priv->clk_usb);
				clk_disable_unprepare(priv->clk_usb_general);
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक phy_meson8b_usb2_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा phy_meson8b_usb2_priv *priv = phy_get_drvdata(phy);

	अगर (priv->dr_mode == USB_DR_MODE_HOST)
		regmap_update_bits(priv->regmap, REG_DBG_UART,
				   REG_DBG_UART_SET_IDDQ,
				   REG_DBG_UART_SET_IDDQ);

	clk_disable_unprepare(priv->clk_usb);
	clk_disable_unprepare(priv->clk_usb_general);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops phy_meson8b_usb2_ops = अणु
	.घातer_on	= phy_meson8b_usb2_घातer_on,
	.घातer_off	= phy_meson8b_usb2_घातer_off,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक phy_meson8b_usb2_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा phy_meson8b_usb2_priv *priv;
	काष्ठा phy *phy;
	काष्ठा phy_provider *phy_provider;
	व्योम __iomem *base;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	priv->match = device_get_match_data(&pdev->dev);
	अगर (!priv->match)
		वापस -ENODEV;

	priv->regmap = devm_regmap_init_mmio(&pdev->dev, base,
					     &phy_meson8b_usb2_regmap_conf);
	अगर (IS_ERR(priv->regmap))
		वापस PTR_ERR(priv->regmap);

	priv->clk_usb_general = devm_clk_get(&pdev->dev, "usb_general");
	अगर (IS_ERR(priv->clk_usb_general))
		वापस PTR_ERR(priv->clk_usb_general);

	priv->clk_usb = devm_clk_get(&pdev->dev, "usb");
	अगर (IS_ERR(priv->clk_usb))
		वापस PTR_ERR(priv->clk_usb);

	priv->reset = devm_reset_control_get_optional_shared(&pdev->dev, शून्य);
	अगर (PTR_ERR(priv->reset) == -EPROBE_DEFER)
		वापस PTR_ERR(priv->reset);

	priv->dr_mode = of_usb_get_dr_mode_by_phy(pdev->dev.of_node, -1);
	अगर (priv->dr_mode == USB_DR_MODE_UNKNOWN) अणु
		dev_err(&pdev->dev,
			"missing dual role configuration of the controller\n");
		वापस -EINVAL;
	पूर्ण

	phy = devm_phy_create(&pdev->dev, शून्य, &phy_meson8b_usb2_ops);
	अगर (IS_ERR(phy)) अणु
		dev_err(&pdev->dev, "failed to create PHY\n");
		वापस PTR_ERR(phy);
	पूर्ण

	phy_set_drvdata(phy, priv);

	phy_provider =
		devm_of_phy_provider_रेजिस्टर(&pdev->dev, of_phy_simple_xlate);

	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल स्थिर काष्ठा phy_meson8b_usb2_match_data phy_meson8_usb2_match_data = अणु
	.host_enable_aca = false,
पूर्ण;

अटल स्थिर काष्ठा phy_meson8b_usb2_match_data phy_meson8b_usb2_match_data = अणु
	.host_enable_aca = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id phy_meson8b_usb2_of_match[] = अणु
	अणु
		.compatible = "amlogic,meson8-usb2-phy",
		.data = &phy_meson8_usb2_match_data
	पूर्ण,
	अणु
		.compatible = "amlogic,meson8b-usb2-phy",
		.data = &phy_meson8b_usb2_match_data
	पूर्ण,
	अणु
		.compatible = "amlogic,meson8m2-usb2-phy",
		.data = &phy_meson8b_usb2_match_data
	पूर्ण,
	अणु
		.compatible = "amlogic,meson-gxbb-usb2-phy",
		.data = &phy_meson8b_usb2_match_data
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, phy_meson8b_usb2_of_match);

अटल काष्ठा platक्रमm_driver phy_meson8b_usb2_driver = अणु
	.probe	= phy_meson8b_usb2_probe,
	.driver	= अणु
		.name		= "phy-meson-usb2",
		.of_match_table	= phy_meson8b_usb2_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(phy_meson8b_usb2_driver);

MODULE_AUTHOR("Martin Blumenstingl <martin.blumenstingl@googlemail.com>");
MODULE_DESCRIPTION("Meson8, Meson8b, Meson8m2 and GXBB USB2 PHY driver");
MODULE_LICENSE("GPL");
