<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PCIe PHY driver क्रम Lantiq VRX200 and ARX300 SoCs.
 *
 * Copyright (C) 2019 Martin Blumenstingl <martin.blumenstingl@googlemail.com>
 *
 * Based on the BSP (called "UGW") driver:
 *  Copyright (C) 2009-2015 Lei Chuanhua <chuanhua.lei@lantiq.com>
 *  Copyright (C) 2016 Intel Corporation
 *
 * TODO: PHY modes other than 36MHz (without "SSC")
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/bits.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>

#समावेश <dt-bindings/phy/phy-lantiq-vrx200-pcie.h>

#घोषणा PCIE_PHY_PLL_CTRL1				0x44

#घोषणा PCIE_PHY_PLL_CTRL2				0x46
#घोषणा PCIE_PHY_PLL_CTRL2_CONST_SDM_MASK		GENMASK(7, 0)
#घोषणा PCIE_PHY_PLL_CTRL2_CONST_SDM_EN			BIT(8)
#घोषणा PCIE_PHY_PLL_CTRL2_PLL_SDM_EN			BIT(9)

#घोषणा PCIE_PHY_PLL_CTRL3				0x48
#घोषणा PCIE_PHY_PLL_CTRL3_EXT_MMD_DIV_RATIO_EN		BIT(1)
#घोषणा PCIE_PHY_PLL_CTRL3_EXT_MMD_DIV_RATIO_MASK	GENMASK(6, 4)

#घोषणा PCIE_PHY_PLL_CTRL4				0x4a
#घोषणा PCIE_PHY_PLL_CTRL5				0x4c
#घोषणा PCIE_PHY_PLL_CTRL6				0x4e
#घोषणा PCIE_PHY_PLL_CTRL7				0x50
#घोषणा PCIE_PHY_PLL_A_CTRL1				0x52

#घोषणा PCIE_PHY_PLL_A_CTRL2				0x54
#घोषणा PCIE_PHY_PLL_A_CTRL2_LF_MODE_EN			BIT(14)

#घोषणा PCIE_PHY_PLL_A_CTRL3				0x56
#घोषणा PCIE_PHY_PLL_A_CTRL3_MMD_MASK			GENMASK(15, 13)

#घोषणा PCIE_PHY_PLL_STATUS				0x58

#घोषणा PCIE_PHY_TX1_CTRL1				0x60
#घोषणा PCIE_PHY_TX1_CTRL1_FORCE_EN			BIT(3)
#घोषणा PCIE_PHY_TX1_CTRL1_LOAD_EN			BIT(4)

#घोषणा PCIE_PHY_TX1_CTRL2				0x62
#घोषणा PCIE_PHY_TX1_CTRL3				0x64
#घोषणा PCIE_PHY_TX1_A_CTRL1				0x66
#घोषणा PCIE_PHY_TX1_A_CTRL2				0x68
#घोषणा PCIE_PHY_TX1_MOD1				0x6a
#घोषणा PCIE_PHY_TX1_MOD2				0x6c
#घोषणा PCIE_PHY_TX1_MOD3				0x6e

#घोषणा PCIE_PHY_TX2_CTRL1				0x70
#घोषणा PCIE_PHY_TX2_CTRL1_LOAD_EN			BIT(4)

#घोषणा PCIE_PHY_TX2_CTRL2				0x72
#घोषणा PCIE_PHY_TX2_A_CTRL1				0x76
#घोषणा PCIE_PHY_TX2_A_CTRL2				0x78
#घोषणा PCIE_PHY_TX2_MOD1				0x7a
#घोषणा PCIE_PHY_TX2_MOD2				0x7c
#घोषणा PCIE_PHY_TX2_MOD3				0x7e

#घोषणा PCIE_PHY_RX1_CTRL1				0xa0
#घोषणा PCIE_PHY_RX1_CTRL1_LOAD_EN			BIT(1)

#घोषणा PCIE_PHY_RX1_CTRL2				0xa2
#घोषणा PCIE_PHY_RX1_CDR				0xa4
#घोषणा PCIE_PHY_RX1_EI					0xa6
#घोषणा PCIE_PHY_RX1_A_CTRL				0xaa

काष्ठा ltq_vrx200_pcie_phy_priv अणु
	काष्ठा phy			*phy;
	अचिन्हित पूर्णांक			mode;
	काष्ठा device			*dev;
	काष्ठा regmap			*phy_regmap;
	काष्ठा regmap			*rcu_regmap;
	काष्ठा clk			*pdi_clk;
	काष्ठा clk			*phy_clk;
	काष्ठा reset_control		*phy_reset;
	काष्ठा reset_control		*pcie_reset;
	u32				rcu_ahb_endian_offset;
	u32				rcu_ahb_endian_big_endian_mask;
पूर्ण;

अटल व्योम ltq_vrx200_pcie_phy_common_setup(काष्ठा phy *phy)
अणु
	काष्ठा ltq_vrx200_pcie_phy_priv *priv = phy_get_drvdata(phy);

	/* PLL Setting */
	regmap_ग_लिखो(priv->phy_regmap, PCIE_PHY_PLL_A_CTRL1, 0x120e);

	/* increase the bias reference voltage */
	regmap_ग_लिखो(priv->phy_regmap, PCIE_PHY_PLL_A_CTRL2, 0x39d7);
	regmap_ग_लिखो(priv->phy_regmap, PCIE_PHY_PLL_A_CTRL3, 0x0900);

	/* Endcnt */
	regmap_ग_लिखो(priv->phy_regmap, PCIE_PHY_RX1_EI, 0x0004);
	regmap_ग_लिखो(priv->phy_regmap, PCIE_PHY_RX1_A_CTRL, 0x6803);

	regmap_update_bits(priv->phy_regmap, PCIE_PHY_TX1_CTRL1,
			   PCIE_PHY_TX1_CTRL1_FORCE_EN,
			   PCIE_PHY_TX1_CTRL1_FORCE_EN);

	/* predrv_ser_en */
	regmap_ग_लिखो(priv->phy_regmap, PCIE_PHY_TX1_A_CTRL2, 0x0706);

	/* ctrl_lim */
	regmap_ग_लिखो(priv->phy_regmap, PCIE_PHY_TX1_CTRL3, 0x1fff);

	/* ctrl */
	regmap_ग_लिखो(priv->phy_regmap, PCIE_PHY_TX1_A_CTRL1, 0x0810);

	/* predrv_ser_en */
	regmap_update_bits(priv->phy_regmap, PCIE_PHY_TX2_A_CTRL2, 0x7f00,
			   0x4700);

	/* RTERM */
	regmap_ग_लिखो(priv->phy_regmap, PCIE_PHY_TX1_CTRL2, 0x2e00);

	/* Improved 100MHz घड़ी output  */
	regmap_ग_लिखो(priv->phy_regmap, PCIE_PHY_TX2_CTRL2, 0x3096);
	regmap_ग_लिखो(priv->phy_regmap, PCIE_PHY_TX2_A_CTRL2, 0x4707);

	/* Reduced CDR BW to aव्योम glitches */
	regmap_ग_लिखो(priv->phy_regmap, PCIE_PHY_RX1_CDR, 0x0235);
पूर्ण

अटल व्योम pcie_phy_36mhz_mode_setup(काष्ठा phy *phy)
अणु
	काष्ठा ltq_vrx200_pcie_phy_priv *priv = phy_get_drvdata(phy);

	regmap_update_bits(priv->phy_regmap, PCIE_PHY_PLL_CTRL3,
			   PCIE_PHY_PLL_CTRL3_EXT_MMD_DIV_RATIO_EN, 0x0000);

	regmap_update_bits(priv->phy_regmap, PCIE_PHY_PLL_CTRL3,
			   PCIE_PHY_PLL_CTRL3_EXT_MMD_DIV_RATIO_MASK, 0x0000);

	regmap_update_bits(priv->phy_regmap, PCIE_PHY_PLL_CTRL2,
			   PCIE_PHY_PLL_CTRL2_PLL_SDM_EN,
			   PCIE_PHY_PLL_CTRL2_PLL_SDM_EN);

	regmap_update_bits(priv->phy_regmap, PCIE_PHY_PLL_CTRL2,
			   PCIE_PHY_PLL_CTRL2_CONST_SDM_EN,
			   PCIE_PHY_PLL_CTRL2_CONST_SDM_EN);

	regmap_update_bits(priv->phy_regmap, PCIE_PHY_PLL_A_CTRL3,
			   PCIE_PHY_PLL_A_CTRL3_MMD_MASK,
			   FIELD_PREP(PCIE_PHY_PLL_A_CTRL3_MMD_MASK, 0x1));

	regmap_update_bits(priv->phy_regmap, PCIE_PHY_PLL_A_CTRL2,
			   PCIE_PHY_PLL_A_CTRL2_LF_MODE_EN, 0x0000);

	/* स्थिर_sdm */
	regmap_ग_लिखो(priv->phy_regmap, PCIE_PHY_PLL_CTRL1, 0x38e4);

	regmap_update_bits(priv->phy_regmap, PCIE_PHY_PLL_CTRL2,
			   PCIE_PHY_PLL_CTRL2_CONST_SDM_MASK,
			   FIELD_PREP(PCIE_PHY_PLL_CTRL2_CONST_SDM_MASK,
				      0xee));

	/* pllmod */
	regmap_ग_लिखो(priv->phy_regmap, PCIE_PHY_PLL_CTRL7, 0x0002);
	regmap_ग_लिखो(priv->phy_regmap, PCIE_PHY_PLL_CTRL6, 0x3a04);
	regmap_ग_लिखो(priv->phy_regmap, PCIE_PHY_PLL_CTRL5, 0xfae3);
	regmap_ग_लिखो(priv->phy_regmap, PCIE_PHY_PLL_CTRL4, 0x1b72);
पूर्ण

अटल पूर्णांक ltq_vrx200_pcie_phy_रुको_क्रम_pll(काष्ठा phy *phy)
अणु
	काष्ठा ltq_vrx200_pcie_phy_priv *priv = phy_get_drvdata(phy);
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक ret;

	ret = regmap_पढ़ो_poll_समयout(priv->phy_regmap, PCIE_PHY_PLL_STATUS,
				       पंचांगp, ((पंचांगp & 0x0070) == 0x0070), 10,
				       10000);
	अगर (ret) अणु
		dev_err(priv->dev, "PLL Link timeout, PLL status = 0x%04x\n",
			पंचांगp);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ltq_vrx200_pcie_phy_apply_workarounds(काष्ठा phy *phy)
अणु
	काष्ठा ltq_vrx200_pcie_phy_priv *priv = phy_get_drvdata(phy);
	अटल स्थिर काष्ठा reg_शेष slices[] =  अणु
		अणु
			.reg = PCIE_PHY_TX1_CTRL1,
			.def = PCIE_PHY_TX1_CTRL1_LOAD_EN,
		पूर्ण,
		अणु
			.reg = PCIE_PHY_TX2_CTRL1,
			.def = PCIE_PHY_TX2_CTRL1_LOAD_EN,
		पूर्ण,
		अणु
			.reg = PCIE_PHY_RX1_CTRL1,
			.def = PCIE_PHY_RX1_CTRL1_LOAD_EN,
		पूर्ण
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(slices); i++) अणु
		/* enable load_en */
		regmap_update_bits(priv->phy_regmap, slices[i].reg,
				   slices[i].def, slices[i].def);

		udelay(1);

		/* disable load_en */
		regmap_update_bits(priv->phy_regmap, slices[i].reg,
				   slices[i].def, 0x0);
	पूर्ण

	क्रम (i = 0; i < 5; i++) अणु
		/* TX2 modulation */
		regmap_ग_लिखो(priv->phy_regmap, PCIE_PHY_TX2_MOD1, 0x1ffe);
		regmap_ग_लिखो(priv->phy_regmap, PCIE_PHY_TX2_MOD2, 0xfffe);
		regmap_ग_लिखो(priv->phy_regmap, PCIE_PHY_TX2_MOD3, 0x0601);
		usleep_range(1000, 2000);
		regmap_ग_लिखो(priv->phy_regmap, PCIE_PHY_TX2_MOD3, 0x0001);

		/* TX1 modulation */
		regmap_ग_लिखो(priv->phy_regmap, PCIE_PHY_TX1_MOD1, 0x1ffe);
		regmap_ग_लिखो(priv->phy_regmap, PCIE_PHY_TX1_MOD2, 0xfffe);
		regmap_ग_लिखो(priv->phy_regmap, PCIE_PHY_TX1_MOD3, 0x0601);
		usleep_range(1000, 2000);
		regmap_ग_लिखो(priv->phy_regmap, PCIE_PHY_TX1_MOD3, 0x0001);
	पूर्ण
पूर्ण

अटल पूर्णांक ltq_vrx200_pcie_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा ltq_vrx200_pcie_phy_priv *priv = phy_get_drvdata(phy);
	पूर्णांक ret;

	अगर (of_device_is_big_endian(priv->dev->of_node))
		regmap_update_bits(priv->rcu_regmap,
				   priv->rcu_ahb_endian_offset,
				   priv->rcu_ahb_endian_big_endian_mask,
				   priv->rcu_ahb_endian_big_endian_mask);
	अन्यथा
		regmap_update_bits(priv->rcu_regmap,
				   priv->rcu_ahb_endian_offset,
				   priv->rcu_ahb_endian_big_endian_mask, 0x0);

	ret = reset_control_निश्चित(priv->phy_reset);
	अगर (ret)
		जाओ err;

	udelay(1);

	ret = reset_control_deनिश्चित(priv->phy_reset);
	अगर (ret)
		जाओ err;

	udelay(1);

	ret = reset_control_deनिश्चित(priv->pcie_reset);
	अगर (ret)
		जाओ err_निश्चित_phy_reset;

	/* Make sure PHY PLL is stable */
	usleep_range(20, 40);

	वापस 0;

err_निश्चित_phy_reset:
	reset_control_निश्चित(priv->phy_reset);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक ltq_vrx200_pcie_phy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा ltq_vrx200_pcie_phy_priv *priv = phy_get_drvdata(phy);
	पूर्णांक ret;

	ret = reset_control_निश्चित(priv->pcie_reset);
	अगर (ret)
		वापस ret;

	ret = reset_control_निश्चित(priv->phy_reset);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक ltq_vrx200_pcie_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा ltq_vrx200_pcie_phy_priv *priv = phy_get_drvdata(phy);
	पूर्णांक ret;

	/* Enable PDI to access PCIe PHY रेजिस्टर */
	ret = clk_prepare_enable(priv->pdi_clk);
	अगर (ret)
		जाओ err;

	/* Configure PLL and PHY घड़ी */
	ltq_vrx200_pcie_phy_common_setup(phy);

	pcie_phy_36mhz_mode_setup(phy);

	/* Enable the PCIe PHY and make PLL setting take effect */
	ret = clk_prepare_enable(priv->phy_clk);
	अगर (ret)
		जाओ err_disable_pdi_clk;

	/* Check अगर we are in "startup ready" status */
	ret = ltq_vrx200_pcie_phy_रुको_क्रम_pll(phy);
	अगर (ret)
		जाओ err_disable_phy_clk;

	ltq_vrx200_pcie_phy_apply_workarounds(phy);

	वापस 0;

err_disable_phy_clk:
	clk_disable_unprepare(priv->phy_clk);
err_disable_pdi_clk:
	clk_disable_unprepare(priv->pdi_clk);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक ltq_vrx200_pcie_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा ltq_vrx200_pcie_phy_priv *priv = phy_get_drvdata(phy);

	clk_disable_unprepare(priv->phy_clk);
	clk_disable_unprepare(priv->pdi_clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops ltq_vrx200_pcie_phy_ops = अणु
	.init		= ltq_vrx200_pcie_phy_init,
	.निकास		= ltq_vrx200_pcie_phy_निकास,
	.घातer_on	= ltq_vrx200_pcie_phy_घातer_on,
	.घातer_off	= ltq_vrx200_pcie_phy_घातer_off,
	.owner		= THIS_MODULE,
पूर्ण;

अटल काष्ठा phy *ltq_vrx200_pcie_phy_xlate(काष्ठा device *dev,
					     काष्ठा of_phandle_args *args)
अणु
	काष्ठा ltq_vrx200_pcie_phy_priv *priv = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक mode;

	अगर (args->args_count != 1) अणु
		dev_err(dev, "invalid number of arguments\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	mode = args->args[0];

	चयन (mode) अणु
	हाल LANTIQ_PCIE_PHY_MODE_36MHZ:
		priv->mode = mode;
		अवरोध;

	हाल LANTIQ_PCIE_PHY_MODE_25MHZ:
	हाल LANTIQ_PCIE_PHY_MODE_25MHZ_SSC:
	हाल LANTIQ_PCIE_PHY_MODE_36MHZ_SSC:
	हाल LANTIQ_PCIE_PHY_MODE_100MHZ:
	हाल LANTIQ_PCIE_PHY_MODE_100MHZ_SSC:
		dev_err(dev, "PHY mode not implemented yet: %u\n", mode);
		वापस ERR_PTR(-EINVAL);

	शेष:
		dev_err(dev, "invalid PHY mode %u\n", mode);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस priv->phy;
पूर्ण

अटल पूर्णांक ltq_vrx200_pcie_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	अटल स्थिर काष्ठा regmap_config regmap_config = अणु
		.reg_bits = 8,
		.val_bits = 16,
		.reg_stride = 2,
		.max_रेजिस्टर = PCIE_PHY_RX1_A_CTRL,
	पूर्ण;
	काष्ठा ltq_vrx200_pcie_phy_priv *priv;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा phy_provider *provider;
	व्योम __iomem *base;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	priv->phy_regmap = devm_regmap_init_mmio(dev, base, &regmap_config);
	अगर (IS_ERR(priv->phy_regmap))
		वापस PTR_ERR(priv->phy_regmap);

	priv->rcu_regmap = syscon_regmap_lookup_by_phandle(dev->of_node,
							   "lantiq,rcu");
	अगर (IS_ERR(priv->rcu_regmap))
		वापस PTR_ERR(priv->rcu_regmap);

	ret = device_property_पढ़ो_u32(dev, "lantiq,rcu-endian-offset",
				       &priv->rcu_ahb_endian_offset);
	अगर (ret) अणु
		dev_err(dev,
			"failed to parse the 'lantiq,rcu-endian-offset' property\n");
		वापस ret;
	पूर्ण

	ret = device_property_पढ़ो_u32(dev, "lantiq,rcu-big-endian-mask",
				       &priv->rcu_ahb_endian_big_endian_mask);
	अगर (ret) अणु
		dev_err(dev,
			"failed to parse the 'lantiq,rcu-big-endian-mask' property\n");
		वापस ret;
	पूर्ण

	priv->pdi_clk = devm_clk_get(dev, "pdi");
	अगर (IS_ERR(priv->pdi_clk))
		वापस PTR_ERR(priv->pdi_clk);

	priv->phy_clk = devm_clk_get(dev, "phy");
	अगर (IS_ERR(priv->phy_clk))
		वापस PTR_ERR(priv->phy_clk);

	priv->phy_reset = devm_reset_control_get_exclusive(dev, "phy");
	अगर (IS_ERR(priv->phy_reset))
		वापस PTR_ERR(priv->phy_reset);

	priv->pcie_reset = devm_reset_control_get_shared(dev, "pcie");
	अगर (IS_ERR(priv->pcie_reset))
		वापस PTR_ERR(priv->pcie_reset);

	priv->dev = dev;

	priv->phy = devm_phy_create(dev, dev->of_node,
				    &ltq_vrx200_pcie_phy_ops);
	अगर (IS_ERR(priv->phy)) अणु
		dev_err(dev, "failed to create PHY\n");
		वापस PTR_ERR(priv->phy);
	पूर्ण

	phy_set_drvdata(priv->phy, priv);
	dev_set_drvdata(dev, priv);

	provider = devm_of_phy_provider_रेजिस्टर(dev,
						 ltq_vrx200_pcie_phy_xlate);

	वापस PTR_ERR_OR_ZERO(provider);
पूर्ण

अटल स्थिर काष्ठा of_device_id ltq_vrx200_pcie_phy_of_match[] = अणु
	अणु .compatible = "lantiq,vrx200-pcie-phy", पूर्ण,
	अणु .compatible = "lantiq,arx300-pcie-phy", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ltq_vrx200_pcie_phy_of_match);

अटल काष्ठा platक्रमm_driver ltq_vrx200_pcie_phy_driver = अणु
	.probe	= ltq_vrx200_pcie_phy_probe,
	.driver = अणु
		.name	= "ltq-vrx200-pcie-phy",
		.of_match_table	= ltq_vrx200_pcie_phy_of_match,
	पूर्ण
पूर्ण;
module_platक्रमm_driver(ltq_vrx200_pcie_phy_driver);

MODULE_AUTHOR("Martin Blumenstingl <martin.blumenstingl@googlemail.com>");
MODULE_DESCRIPTION("Lantiq VRX200 and ARX300 PCIe PHY driver");
MODULE_LICENSE("GPL v2");
