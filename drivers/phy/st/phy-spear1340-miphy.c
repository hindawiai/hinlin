<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ST spear1340-miphy driver
 *
 * Copyright (C) 2014 ST Microelectronics
 * Pratyush Anand <pratyush.anand@gmail.com>
 * Mohit Kumar <mohit.kumar.dhaka@gmail.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/regmap.h>

/* SPEAr1340 Registers */
/* Power Management Registers */
#घोषणा SPEAR1340_PCM_CFG			0x100
	#घोषणा SPEAR1340_PCM_CFG_SATA_POWER_EN		BIT(11)
#घोषणा SPEAR1340_PCM_WKUP_CFG			0x104
#घोषणा SPEAR1340_SWITCH_CTR			0x108

#घोषणा SPEAR1340_PERIP1_SW_RST			0x318
	#घोषणा SPEAR1340_PERIP1_SW_RSATA		BIT(12)
#घोषणा SPEAR1340_PERIP2_SW_RST			0x31C
#घोषणा SPEAR1340_PERIP3_SW_RST			0x320

/* PCIE - SATA configuration रेजिस्टरs */
#घोषणा SPEAR1340_PCIE_SATA_CFG			0x424
	/* PCIE CFG MASks */
	#घोषणा SPEAR1340_PCIE_CFG_DEVICE_PRESENT	BIT(11)
	#घोषणा SPEAR1340_PCIE_CFG_POWERUP_RESET	BIT(10)
	#घोषणा SPEAR1340_PCIE_CFG_CORE_CLK_EN		BIT(9)
	#घोषणा SPEAR1340_PCIE_CFG_AUX_CLK_EN		BIT(8)
	#घोषणा SPEAR1340_SATA_CFG_TX_CLK_EN		BIT(4)
	#घोषणा SPEAR1340_SATA_CFG_RX_CLK_EN		BIT(3)
	#घोषणा SPEAR1340_SATA_CFG_POWERUP_RESET	BIT(2)
	#घोषणा SPEAR1340_SATA_CFG_PM_CLK_EN		BIT(1)
	#घोषणा SPEAR1340_PCIE_SATA_SEL_PCIE		(0)
	#घोषणा SPEAR1340_PCIE_SATA_SEL_SATA		(1)
	#घोषणा SPEAR1340_PCIE_SATA_CFG_MASK		0xF1F
	#घोषणा SPEAR1340_PCIE_CFG_VAL	(SPEAR1340_PCIE_SATA_SEL_PCIE | \
			SPEAR1340_PCIE_CFG_AUX_CLK_EN | \
			SPEAR1340_PCIE_CFG_CORE_CLK_EN | \
			SPEAR1340_PCIE_CFG_POWERUP_RESET | \
			SPEAR1340_PCIE_CFG_DEVICE_PRESENT)
	#घोषणा SPEAR1340_SATA_CFG_VAL	(SPEAR1340_PCIE_SATA_SEL_SATA | \
			SPEAR1340_SATA_CFG_PM_CLK_EN | \
			SPEAR1340_SATA_CFG_POWERUP_RESET | \
			SPEAR1340_SATA_CFG_RX_CLK_EN | \
			SPEAR1340_SATA_CFG_TX_CLK_EN)

#घोषणा SPEAR1340_PCIE_MIPHY_CFG		0x428
	#घोषणा SPEAR1340_MIPHY_OSC_BYPASS_EXT		BIT(31)
	#घोषणा SPEAR1340_MIPHY_CLK_REF_DIV2		BIT(27)
	#घोषणा SPEAR1340_MIPHY_CLK_REF_DIV4		(2 << 27)
	#घोषणा SPEAR1340_MIPHY_CLK_REF_DIV8		(3 << 27)
	#घोषणा SPEAR1340_MIPHY_PLL_RATIO_TOP(x)	(x << 0)
	#घोषणा SPEAR1340_PCIE_MIPHY_CFG_MASK		0xF80000FF
	#घोषणा SPEAR1340_PCIE_SATA_MIPHY_CFG_SATA \
			(SPEAR1340_MIPHY_OSC_BYPASS_EXT | \
			SPEAR1340_MIPHY_CLK_REF_DIV2 | \
			SPEAR1340_MIPHY_PLL_RATIO_TOP(60))
	#घोषणा SPEAR1340_PCIE_SATA_MIPHY_CFG_SATA_25M_CRYSTAL_CLK \
			(SPEAR1340_MIPHY_PLL_RATIO_TOP(120))
	#घोषणा SPEAR1340_PCIE_SATA_MIPHY_CFG_PCIE \
			(SPEAR1340_MIPHY_OSC_BYPASS_EXT | \
			SPEAR1340_MIPHY_PLL_RATIO_TOP(25))

क्रमागत spear1340_miphy_mode अणु
	SATA,
	PCIE,
पूर्ण;

काष्ठा spear1340_miphy_priv अणु
	/* phy mode: 0 क्रम SATA 1 क्रम PCIe */
	क्रमागत spear1340_miphy_mode	mode;
	/* regmap क्रम any soc specअगरic misc रेजिस्टरs */
	काष्ठा regmap			*misc;
	/* phy काष्ठा poपूर्णांकer */
	काष्ठा phy			*phy;
पूर्ण;

अटल पूर्णांक spear1340_miphy_sata_init(काष्ठा spear1340_miphy_priv *priv)
अणु
	regmap_update_bits(priv->misc, SPEAR1340_PCIE_SATA_CFG,
			   SPEAR1340_PCIE_SATA_CFG_MASK,
			   SPEAR1340_SATA_CFG_VAL);
	regmap_update_bits(priv->misc, SPEAR1340_PCIE_MIPHY_CFG,
			   SPEAR1340_PCIE_MIPHY_CFG_MASK,
			   SPEAR1340_PCIE_SATA_MIPHY_CFG_SATA_25M_CRYSTAL_CLK);
	/* Switch on sata घातer करोमुख्य */
	regmap_update_bits(priv->misc, SPEAR1340_PCM_CFG,
			   SPEAR1340_PCM_CFG_SATA_POWER_EN,
			   SPEAR1340_PCM_CFG_SATA_POWER_EN);
	/* Wait क्रम SATA घातer करोमुख्य on */
	msleep(20);

	/* Disable PCIE SATA Controller reset */
	regmap_update_bits(priv->misc, SPEAR1340_PERIP1_SW_RST,
			   SPEAR1340_PERIP1_SW_RSATA, 0);
	/* Wait क्रम SATA reset de-निश्चित completion */
	msleep(20);

	वापस 0;
पूर्ण

अटल पूर्णांक spear1340_miphy_sata_निकास(काष्ठा spear1340_miphy_priv *priv)
अणु
	regmap_update_bits(priv->misc, SPEAR1340_PCIE_SATA_CFG,
			   SPEAR1340_PCIE_SATA_CFG_MASK, 0);
	regmap_update_bits(priv->misc, SPEAR1340_PCIE_MIPHY_CFG,
			   SPEAR1340_PCIE_MIPHY_CFG_MASK, 0);

	/* Enable PCIE SATA Controller reset */
	regmap_update_bits(priv->misc, SPEAR1340_PERIP1_SW_RST,
			   SPEAR1340_PERIP1_SW_RSATA,
			   SPEAR1340_PERIP1_SW_RSATA);
	/* Wait क्रम SATA घातer करोमुख्य off */
	msleep(20);
	/* Switch off sata घातer करोमुख्य */
	regmap_update_bits(priv->misc, SPEAR1340_PCM_CFG,
			   SPEAR1340_PCM_CFG_SATA_POWER_EN, 0);
	/* Wait क्रम SATA reset निश्चित completion */
	msleep(20);

	वापस 0;
पूर्ण

अटल पूर्णांक spear1340_miphy_pcie_init(काष्ठा spear1340_miphy_priv *priv)
अणु
	regmap_update_bits(priv->misc, SPEAR1340_PCIE_MIPHY_CFG,
			   SPEAR1340_PCIE_MIPHY_CFG_MASK,
			   SPEAR1340_PCIE_SATA_MIPHY_CFG_PCIE);
	regmap_update_bits(priv->misc, SPEAR1340_PCIE_SATA_CFG,
			   SPEAR1340_PCIE_SATA_CFG_MASK,
			   SPEAR1340_PCIE_CFG_VAL);

	वापस 0;
पूर्ण

अटल पूर्णांक spear1340_miphy_pcie_निकास(काष्ठा spear1340_miphy_priv *priv)
अणु
	regmap_update_bits(priv->misc, SPEAR1340_PCIE_MIPHY_CFG,
			   SPEAR1340_PCIE_MIPHY_CFG_MASK, 0);
	regmap_update_bits(priv->misc, SPEAR1340_PCIE_SATA_CFG,
			   SPEAR1340_PCIE_SATA_CFG_MASK, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक spear1340_miphy_init(काष्ठा phy *phy)
अणु
	काष्ठा spear1340_miphy_priv *priv = phy_get_drvdata(phy);
	पूर्णांक ret = 0;

	अगर (priv->mode == SATA)
		ret = spear1340_miphy_sata_init(priv);
	अन्यथा अगर (priv->mode == PCIE)
		ret = spear1340_miphy_pcie_init(priv);

	वापस ret;
पूर्ण

अटल पूर्णांक spear1340_miphy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा spear1340_miphy_priv *priv = phy_get_drvdata(phy);
	पूर्णांक ret = 0;

	अगर (priv->mode == SATA)
		ret = spear1340_miphy_sata_निकास(priv);
	अन्यथा अगर (priv->mode == PCIE)
		ret = spear1340_miphy_pcie_निकास(priv);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id spear1340_miphy_of_match[] = अणु
	अणु .compatible = "st,spear1340-miphy" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, spear1340_miphy_of_match);

अटल स्थिर काष्ठा phy_ops spear1340_miphy_ops = अणु
	.init = spear1340_miphy_init,
	.निकास = spear1340_miphy_निकास,
	.owner = THIS_MODULE,
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक spear1340_miphy_suspend(काष्ठा device *dev)
अणु
	काष्ठा spear1340_miphy_priv *priv = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	अगर (priv->mode == SATA)
		ret = spear1340_miphy_sata_निकास(priv);

	वापस ret;
पूर्ण

अटल पूर्णांक spear1340_miphy_resume(काष्ठा device *dev)
अणु
	काष्ठा spear1340_miphy_priv *priv = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	अगर (priv->mode == SATA)
		ret = spear1340_miphy_sata_init(priv);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(spear1340_miphy_pm_ops, spear1340_miphy_suspend,
			 spear1340_miphy_resume);

अटल काष्ठा phy *spear1340_miphy_xlate(काष्ठा device *dev,
					 काष्ठा of_phandle_args *args)
अणु
	काष्ठा spear1340_miphy_priv *priv = dev_get_drvdata(dev);

	अगर (args->args_count < 1) अणु
		dev_err(dev, "DT did not pass correct no of args\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	priv->mode = args->args[0];

	अगर (priv->mode != SATA && priv->mode != PCIE) अणु
		dev_err(dev, "DT did not pass correct phy mode\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	वापस priv->phy;
पूर्ण

अटल पूर्णांक spear1340_miphy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा spear1340_miphy_priv *priv;
	काष्ठा phy_provider *phy_provider;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->misc =
		syscon_regmap_lookup_by_phandle(dev->of_node, "misc");
	अगर (IS_ERR(priv->misc)) अणु
		dev_err(dev, "failed to find misc regmap\n");
		वापस PTR_ERR(priv->misc);
	पूर्ण

	priv->phy = devm_phy_create(dev, शून्य, &spear1340_miphy_ops);
	अगर (IS_ERR(priv->phy)) अणु
		dev_err(dev, "failed to create SATA PCIe PHY\n");
		वापस PTR_ERR(priv->phy);
	पूर्ण

	dev_set_drvdata(dev, priv);
	phy_set_drvdata(priv->phy, priv);

	phy_provider =
		devm_of_phy_provider_रेजिस्टर(dev, spear1340_miphy_xlate);
	अगर (IS_ERR(phy_provider)) अणु
		dev_err(dev, "failed to register phy provider\n");
		वापस PTR_ERR(phy_provider);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver spear1340_miphy_driver = अणु
	.probe		= spear1340_miphy_probe,
	.driver = अणु
		.name = "spear1340-miphy",
		.pm = &spear1340_miphy_pm_ops,
		.of_match_table = of_match_ptr(spear1340_miphy_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(spear1340_miphy_driver);

MODULE_DESCRIPTION("ST SPEAR1340-MIPHY driver");
MODULE_AUTHOR("Pratyush Anand <pratyush.anand@gmail.com>");
MODULE_LICENSE("GPL v2");
