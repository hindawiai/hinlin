<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Amlogic G12A USB3 + PCIE Combo PHY driver
 *
 * Copyright (C) 2017 Amlogic, Inc. All rights reserved
 * Copyright (C) 2019 BayLibre, SAS
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <dt-bindings/phy/phy.h>

#घोषणा PHY_R0							0x00
	#घोषणा PHY_R0_PCIE_POWER_STATE				GENMASK(4, 0)
	#घोषणा PHY_R0_PCIE_USB3_SWITCH				GENMASK(6, 5)

#घोषणा PHY_R1							0x04
	#घोषणा PHY_R1_PHY_TX1_TERM_OFFSET			GENMASK(4, 0)
	#घोषणा PHY_R1_PHY_TX0_TERM_OFFSET			GENMASK(9, 5)
	#घोषणा PHY_R1_PHY_RX1_EQ				GENMASK(12, 10)
	#घोषणा PHY_R1_PHY_RX0_EQ				GENMASK(15, 13)
	#घोषणा PHY_R1_PHY_LOS_LEVEL				GENMASK(20, 16)
	#घोषणा PHY_R1_PHY_LOS_BIAS				GENMASK(23, 21)
	#घोषणा PHY_R1_PHY_REF_CLKDIV2				BIT(24)
	#घोषणा PHY_R1_PHY_MPLL_MULTIPLIER			GENMASK(31, 25)

#घोषणा PHY_R2							0x08
	#घोषणा PHY_R2_PCS_TX_DEEMPH_GEN2_6DB			GENMASK(5, 0)
	#घोषणा PHY_R2_PCS_TX_DEEMPH_GEN2_3P5DB			GENMASK(11, 6)
	#घोषणा PHY_R2_PCS_TX_DEEMPH_GEN1			GENMASK(17, 12)
	#घोषणा PHY_R2_PHY_TX_VBOOST_LVL			GENMASK(20, 18)

#घोषणा PHY_R4							0x10
	#घोषणा PHY_R4_PHY_CR_WRITE				BIT(0)
	#घोषणा PHY_R4_PHY_CR_READ				BIT(1)
	#घोषणा PHY_R4_PHY_CR_DATA_IN				GENMASK(17, 2)
	#घोषणा PHY_R4_PHY_CR_CAP_DATA				BIT(18)
	#घोषणा PHY_R4_PHY_CR_CAP_ADDR				BIT(19)

#घोषणा PHY_R5							0x14
	#घोषणा PHY_R5_PHY_CR_DATA_OUT				GENMASK(15, 0)
	#घोषणा PHY_R5_PHY_CR_ACK				BIT(16)
	#घोषणा PHY_R5_PHY_BS_OUT				BIT(17)

#घोषणा PCIE_RESET_DELAY					500

काष्ठा phy_g12a_usb3_pcie_priv अणु
	काष्ठा regmap		*regmap;
	काष्ठा regmap		*regmap_cr;
	काष्ठा clk		*clk_ref;
	काष्ठा reset_control	*reset;
	काष्ठा phy		*phy;
	अचिन्हित पूर्णांक		mode;
पूर्ण;

अटल स्थिर काष्ठा regmap_config phy_g12a_usb3_pcie_regmap_conf = अणु
	.reg_bits = 8,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = PHY_R5,
पूर्ण;

अटल पूर्णांक phy_g12a_usb3_pcie_cr_bus_addr(काष्ठा phy_g12a_usb3_pcie_priv *priv,
					  अचिन्हित पूर्णांक addr)
अणु
	अचिन्हित पूर्णांक val, reg;
	पूर्णांक ret;

	reg = FIELD_PREP(PHY_R4_PHY_CR_DATA_IN, addr);

	regmap_ग_लिखो(priv->regmap, PHY_R4, reg);
	regmap_ग_लिखो(priv->regmap, PHY_R4, reg);

	regmap_ग_लिखो(priv->regmap, PHY_R4, reg | PHY_R4_PHY_CR_CAP_ADDR);

	ret = regmap_पढ़ो_poll_समयout(priv->regmap, PHY_R5, val,
				       (val & PHY_R5_PHY_CR_ACK),
				       5, 1000);
	अगर (ret)
		वापस ret;

	regmap_ग_लिखो(priv->regmap, PHY_R4, reg);

	ret = regmap_पढ़ो_poll_समयout(priv->regmap, PHY_R5, val,
				       !(val & PHY_R5_PHY_CR_ACK),
				       5, 1000);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक phy_g12a_usb3_pcie_cr_bus_पढ़ो(व्योम *context, अचिन्हित पूर्णांक addr,
					  अचिन्हित पूर्णांक *data)
अणु
	काष्ठा phy_g12a_usb3_pcie_priv *priv = context;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = phy_g12a_usb3_pcie_cr_bus_addr(priv, addr);
	अगर (ret)
		वापस ret;

	regmap_ग_लिखो(priv->regmap, PHY_R4, 0);
	regmap_ग_लिखो(priv->regmap, PHY_R4, PHY_R4_PHY_CR_READ);

	ret = regmap_पढ़ो_poll_समयout(priv->regmap, PHY_R5, val,
				       (val & PHY_R5_PHY_CR_ACK),
				       5, 1000);
	अगर (ret)
		वापस ret;

	*data = FIELD_GET(PHY_R5_PHY_CR_DATA_OUT, val);

	regmap_ग_लिखो(priv->regmap, PHY_R4, 0);

	ret = regmap_पढ़ो_poll_समयout(priv->regmap, PHY_R5, val,
				       !(val & PHY_R5_PHY_CR_ACK),
				       5, 1000);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक phy_g12a_usb3_pcie_cr_bus_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक addr,
					   अचिन्हित पूर्णांक data)
अणु
	काष्ठा phy_g12a_usb3_pcie_priv *priv = context;
	अचिन्हित पूर्णांक val, reg;
	पूर्णांक ret;

	ret = phy_g12a_usb3_pcie_cr_bus_addr(priv, addr);
	अगर (ret)
		वापस ret;

	reg = FIELD_PREP(PHY_R4_PHY_CR_DATA_IN, data);

	regmap_ग_लिखो(priv->regmap, PHY_R4, reg);
	regmap_ग_लिखो(priv->regmap, PHY_R4, reg);

	regmap_ग_लिखो(priv->regmap, PHY_R4, reg | PHY_R4_PHY_CR_CAP_DATA);

	ret = regmap_पढ़ो_poll_समयout(priv->regmap, PHY_R5, val,
				       (val & PHY_R5_PHY_CR_ACK),
				       5, 1000);
	अगर (ret)
		वापस ret;

	regmap_ग_लिखो(priv->regmap, PHY_R4, reg);

	ret = regmap_पढ़ो_poll_समयout(priv->regmap, PHY_R5, val,
				       (val & PHY_R5_PHY_CR_ACK) == 0,
				       5, 1000);
	अगर (ret)
		वापस ret;

	regmap_ग_लिखो(priv->regmap, PHY_R4, reg);

	regmap_ग_लिखो(priv->regmap, PHY_R4, reg | PHY_R4_PHY_CR_WRITE);

	ret = regmap_पढ़ो_poll_समयout(priv->regmap, PHY_R5, val,
				       (val & PHY_R5_PHY_CR_ACK),
				       5, 1000);
	अगर (ret)
		वापस ret;

	regmap_ग_लिखो(priv->regmap, PHY_R4, reg);

	ret = regmap_पढ़ो_poll_समयout(priv->regmap, PHY_R5, val,
				       (val & PHY_R5_PHY_CR_ACK) == 0,
				       5, 1000);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config phy_g12a_usb3_pcie_cr_regmap_conf = अणु
	.reg_bits = 16,
	.val_bits = 16,
	.reg_पढ़ो = phy_g12a_usb3_pcie_cr_bus_पढ़ो,
	.reg_ग_लिखो = phy_g12a_usb3_pcie_cr_bus_ग_लिखो,
	.max_रेजिस्टर = 0xffff,
	.disable_locking = true,
पूर्ण;

अटल पूर्णांक phy_g12a_usb3_init(काष्ठा phy *phy)
अणु
	काष्ठा phy_g12a_usb3_pcie_priv *priv = phy_get_drvdata(phy);
	पूर्णांक data, ret;

	ret = reset_control_reset(priv->reset);
	अगर (ret)
		वापस ret;

	/* Switch PHY to USB3 */
	/* TODO figure out how to handle when PCIe was set in the bootloader */
	regmap_update_bits(priv->regmap, PHY_R0,
			   PHY_R0_PCIE_USB3_SWITCH,
			   PHY_R0_PCIE_USB3_SWITCH);

	/*
	 * WORKAROUND: There is SSPHY suspend bug due to
	 * which USB क्रमागतerates
	 * in HS mode instead of SS mode. Workaround it by निश्चितing
	 * LANE0.TX_ALT_BLOCK.EN_ALT_BUS to enable TX to use alt bus
	 * mode
	 */
	ret = regmap_update_bits(priv->regmap_cr, 0x102d, BIT(7), BIT(7));
	अगर (ret)
		वापस ret;

	ret = regmap_update_bits(priv->regmap_cr, 0x1010, 0xff0, 20);
	अगर (ret)
		वापस ret;

	/*
	 * Fix RX Equalization setting as follows
	 * LANE0.RX_OVRD_IN_HI. RX_EQ_EN set to 0
	 * LANE0.RX_OVRD_IN_HI.RX_EQ_EN_OVRD set to 1
	 * LANE0.RX_OVRD_IN_HI.RX_EQ set to 3
	 * LANE0.RX_OVRD_IN_HI.RX_EQ_OVRD set to 1
	 */
	ret = regmap_पढ़ो(priv->regmap_cr, 0x1006, &data);
	अगर (ret)
		वापस ret;

	data &= ~BIT(6);
	data |= BIT(7);
	data &= ~(0x7 << 8);
	data |= (0x3 << 8);
	data |= (1 << 11);
	ret = regmap_ग_लिखो(priv->regmap_cr, 0x1006, data);
	अगर (ret)
		वापस ret;

	/*
	 * Set EQ and TX launch amplitudes as follows
	 * LANE0.TX_OVRD_DRV_LO.PREEMPH set to 22
	 * LANE0.TX_OVRD_DRV_LO.AMPLITUDE set to 127
	 * LANE0.TX_OVRD_DRV_LO.EN set to 1.
	 */
	ret = regmap_पढ़ो(priv->regmap_cr, 0x1002, &data);
	अगर (ret)
		वापस ret;

	data &= ~0x3f80;
	data |= (0x16 << 7);
	data &= ~0x7f;
	data |= (0x7f | BIT(14));
	ret = regmap_ग_लिखो(priv->regmap_cr, 0x1002, data);
	अगर (ret)
		वापस ret;

	/* MPLL_LOOP_CTL.PROP_CNTRL = 8 */
	ret = regmap_update_bits(priv->regmap_cr, 0x30, 0xf << 4, 8 << 4);
	अगर (ret)
		वापस ret;

	regmap_update_bits(priv->regmap, PHY_R2,
			PHY_R2_PHY_TX_VBOOST_LVL,
			FIELD_PREP(PHY_R2_PHY_TX_VBOOST_LVL, 0x4));

	regmap_update_bits(priv->regmap, PHY_R1,
			PHY_R1_PHY_LOS_BIAS | PHY_R1_PHY_LOS_LEVEL,
			FIELD_PREP(PHY_R1_PHY_LOS_BIAS, 4) |
			FIELD_PREP(PHY_R1_PHY_LOS_LEVEL, 9));

	वापस 0;
पूर्ण

अटल पूर्णांक phy_g12a_usb3_pcie_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा phy_g12a_usb3_pcie_priv *priv = phy_get_drvdata(phy);

	अगर (priv->mode == PHY_TYPE_USB3)
		वापस 0;

	regmap_update_bits(priv->regmap, PHY_R0,
			   PHY_R0_PCIE_POWER_STATE,
			   FIELD_PREP(PHY_R0_PCIE_POWER_STATE, 0x1c));

	वापस 0;
पूर्ण

अटल पूर्णांक phy_g12a_usb3_pcie_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा phy_g12a_usb3_pcie_priv *priv = phy_get_drvdata(phy);

	अगर (priv->mode == PHY_TYPE_USB3)
		वापस 0;

	regmap_update_bits(priv->regmap, PHY_R0,
			   PHY_R0_PCIE_POWER_STATE,
			   FIELD_PREP(PHY_R0_PCIE_POWER_STATE, 0x1d));

	वापस 0;
पूर्ण

अटल पूर्णांक phy_g12a_usb3_pcie_reset(काष्ठा phy *phy)
अणु
	काष्ठा phy_g12a_usb3_pcie_priv *priv = phy_get_drvdata(phy);
	पूर्णांक ret;

	अगर (priv->mode == PHY_TYPE_USB3)
		वापस 0;

	ret = reset_control_निश्चित(priv->reset);
	अगर (ret)
		वापस ret;

	udelay(PCIE_RESET_DELAY);

	ret = reset_control_deनिश्चित(priv->reset);
	अगर (ret)
		वापस ret;

	udelay(PCIE_RESET_DELAY);

	वापस 0;
पूर्ण

अटल पूर्णांक phy_g12a_usb3_pcie_init(काष्ठा phy *phy)
अणु
	काष्ठा phy_g12a_usb3_pcie_priv *priv = phy_get_drvdata(phy);

	अगर (priv->mode == PHY_TYPE_USB3)
		वापस phy_g12a_usb3_init(phy);

	वापस 0;
पूर्ण

अटल पूर्णांक phy_g12a_usb3_pcie_निकास(काष्ठा phy *phy)
अणु
	काष्ठा phy_g12a_usb3_pcie_priv *priv = phy_get_drvdata(phy);

	अगर (priv->mode == PHY_TYPE_USB3)
		वापस reset_control_reset(priv->reset);

	वापस 0;
पूर्ण

अटल काष्ठा phy *phy_g12a_usb3_pcie_xlate(काष्ठा device *dev,
					    काष्ठा of_phandle_args *args)
अणु
	काष्ठा phy_g12a_usb3_pcie_priv *priv = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक mode;

	अगर (args->args_count < 1) अणु
		dev_err(dev, "invalid number of arguments\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	mode = args->args[0];

	अगर (mode != PHY_TYPE_USB3 && mode != PHY_TYPE_PCIE) अणु
		dev_err(dev, "invalid phy mode select argument\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	priv->mode = mode;

	वापस priv->phy;
पूर्ण

अटल स्थिर काष्ठा phy_ops phy_g12a_usb3_pcie_ops = अणु
	.init		= phy_g12a_usb3_pcie_init,
	.निकास		= phy_g12a_usb3_pcie_निकास,
	.घातer_on	= phy_g12a_usb3_pcie_घातer_on,
	.घातer_off	= phy_g12a_usb3_pcie_घातer_off,
	.reset		= phy_g12a_usb3_pcie_reset,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक phy_g12a_usb3_pcie_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा phy_g12a_usb3_pcie_priv *priv;
	काष्ठा phy_provider *phy_provider;
	व्योम __iomem *base;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	priv->regmap = devm_regmap_init_mmio(dev, base,
					     &phy_g12a_usb3_pcie_regmap_conf);
	अगर (IS_ERR(priv->regmap))
		वापस PTR_ERR(priv->regmap);

	priv->regmap_cr = devm_regmap_init(dev, शून्य, priv,
					   &phy_g12a_usb3_pcie_cr_regmap_conf);
	अगर (IS_ERR(priv->regmap_cr))
		वापस PTR_ERR(priv->regmap_cr);

	priv->clk_ref = devm_clk_get(dev, "ref_clk");
	अगर (IS_ERR(priv->clk_ref))
		वापस PTR_ERR(priv->clk_ref);

	ret = clk_prepare_enable(priv->clk_ref);
	अगर (ret)
		जाओ err_disable_clk_ref;

	priv->reset = devm_reset_control_array_get_exclusive(dev);
	अगर (IS_ERR(priv->reset))
		वापस PTR_ERR(priv->reset);

	priv->phy = devm_phy_create(dev, np, &phy_g12a_usb3_pcie_ops);
	अगर (IS_ERR(priv->phy)) अणु
		ret = PTR_ERR(priv->phy);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to create PHY\n");

		वापस ret;
	पूर्ण

	phy_set_drvdata(priv->phy, priv);
	dev_set_drvdata(dev, priv);

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev,
						     phy_g12a_usb3_pcie_xlate);

	वापस PTR_ERR_OR_ZERO(phy_provider);

err_disable_clk_ref:
	clk_disable_unprepare(priv->clk_ref);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id phy_g12a_usb3_pcie_of_match[] = अणु
	अणु .compatible = "amlogic,g12a-usb3-pcie-phy", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, phy_g12a_usb3_pcie_of_match);

अटल काष्ठा platक्रमm_driver phy_g12a_usb3_pcie_driver = अणु
	.probe	= phy_g12a_usb3_pcie_probe,
	.driver	= अणु
		.name		= "phy-g12a-usb3-pcie",
		.of_match_table	= phy_g12a_usb3_pcie_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(phy_g12a_usb3_pcie_driver);

MODULE_AUTHOR("Neil Armstrong <narmstrong@baylibre.com>");
MODULE_DESCRIPTION("Amlogic G12A USB3 + PCIE Combo PHY driver");
MODULE_LICENSE("GPL v2");
