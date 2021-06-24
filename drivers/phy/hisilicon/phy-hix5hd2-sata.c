<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2014 Linaro Ltd.
 * Copyright (c) 2014 HiSilicon Limited.
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#घोषणा SATA_PHY0_CTLL		0xa0
#घोषणा MPLL_MULTIPLIER_SHIFT	1
#घोषणा MPLL_MULTIPLIER_MASK	0xfe
#घोषणा MPLL_MULTIPLIER_50M	0x3c
#घोषणा MPLL_MULTIPLIER_100M	0x1e
#घोषणा PHY_RESET		BIT(0)
#घोषणा REF_SSP_EN		BIT(9)
#घोषणा SSC_EN			BIT(10)
#घोषणा REF_USE_PAD		BIT(23)

#घोषणा SATA_PORT_PHYCTL	0x174
#घोषणा SPEED_MODE_MASK		0x6f0000
#घोषणा HALF_RATE_SHIFT		16
#घोषणा PHY_CONFIG_SHIFT	18
#घोषणा GEN2_EN_SHIFT		21
#घोषणा SPEED_CTRL		BIT(20)

#घोषणा SATA_PORT_PHYCTL1	0x148
#घोषणा AMPLITUDE_MASK		0x3ffffe
#घोषणा AMPLITUDE_GEN3		0x68
#घोषणा AMPLITUDE_GEN3_SHIFT	15
#घोषणा AMPLITUDE_GEN2		0x56
#घोषणा AMPLITUDE_GEN2_SHIFT	8
#घोषणा AMPLITUDE_GEN1		0x56
#घोषणा AMPLITUDE_GEN1_SHIFT	1

#घोषणा SATA_PORT_PHYCTL2	0x14c
#घोषणा PREEMPH_MASK		0x3ffff
#घोषणा PREEMPH_GEN3		0x20
#घोषणा PREEMPH_GEN3_SHIFT	12
#घोषणा PREEMPH_GEN2		0x15
#घोषणा PREEMPH_GEN2_SHIFT	6
#घोषणा PREEMPH_GEN1		0x5
#घोषणा PREEMPH_GEN1_SHIFT	0

काष्ठा hix5hd2_priv अणु
	व्योम __iomem	*base;
	काष्ठा regmap	*peri_ctrl;
पूर्ण;

क्रमागत phy_speed_mode अणु
	SPEED_MODE_GEN1 = 0,
	SPEED_MODE_GEN2 = 1,
	SPEED_MODE_GEN3 = 2,
पूर्ण;

अटल पूर्णांक hix5hd2_sata_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा hix5hd2_priv *priv = phy_get_drvdata(phy);
	u32 val, data[2];
	पूर्णांक ret;

	अगर (priv->peri_ctrl) अणु
		ret = of_property_पढ़ो_u32_array(phy->dev.of_node,
						 "hisilicon,power-reg",
						 &data[0], 2);
		अगर (ret) अणु
			dev_err(&phy->dev, "Fail read hisilicon,power-reg\n");
			वापस ret;
		पूर्ण

		regmap_update_bits(priv->peri_ctrl, data[0],
				   BIT(data[1]), BIT(data[1]));
	पूर्ण

	/* reset phy */
	val = पढ़ोl_relaxed(priv->base + SATA_PHY0_CTLL);
	val &= ~(MPLL_MULTIPLIER_MASK | REF_USE_PAD);
	val |= MPLL_MULTIPLIER_50M << MPLL_MULTIPLIER_SHIFT |
	       REF_SSP_EN | PHY_RESET;
	ग_लिखोl_relaxed(val, priv->base + SATA_PHY0_CTLL);
	msleep(20);
	val &= ~PHY_RESET;
	ग_लिखोl_relaxed(val, priv->base + SATA_PHY0_CTLL);

	val = पढ़ोl_relaxed(priv->base + SATA_PORT_PHYCTL1);
	val &= ~AMPLITUDE_MASK;
	val |= AMPLITUDE_GEN3 << AMPLITUDE_GEN3_SHIFT |
	       AMPLITUDE_GEN2 << AMPLITUDE_GEN2_SHIFT |
	       AMPLITUDE_GEN1 << AMPLITUDE_GEN1_SHIFT;
	ग_लिखोl_relaxed(val, priv->base + SATA_PORT_PHYCTL1);

	val = पढ़ोl_relaxed(priv->base + SATA_PORT_PHYCTL2);
	val &= ~PREEMPH_MASK;
	val |= PREEMPH_GEN3 << PREEMPH_GEN3_SHIFT |
	       PREEMPH_GEN2 << PREEMPH_GEN2_SHIFT |
	       PREEMPH_GEN1 << PREEMPH_GEN1_SHIFT;
	ग_लिखोl_relaxed(val, priv->base + SATA_PORT_PHYCTL2);

	/* ensure PHYCTRL setting takes effect */
	val = पढ़ोl_relaxed(priv->base + SATA_PORT_PHYCTL);
	val &= ~SPEED_MODE_MASK;
	val |= SPEED_MODE_GEN1 << HALF_RATE_SHIFT |
	       SPEED_MODE_GEN1 << PHY_CONFIG_SHIFT |
	       SPEED_MODE_GEN1 << GEN2_EN_SHIFT | SPEED_CTRL;
	ग_लिखोl_relaxed(val, priv->base + SATA_PORT_PHYCTL);

	msleep(20);
	val &= ~SPEED_MODE_MASK;
	val |= SPEED_MODE_GEN3 << HALF_RATE_SHIFT |
	       SPEED_MODE_GEN3 << PHY_CONFIG_SHIFT |
	       SPEED_MODE_GEN3 << GEN2_EN_SHIFT | SPEED_CTRL;
	ग_लिखोl_relaxed(val, priv->base + SATA_PORT_PHYCTL);

	val &= ~(SPEED_MODE_MASK | SPEED_CTRL);
	val |= SPEED_MODE_GEN2 << HALF_RATE_SHIFT |
	       SPEED_MODE_GEN2 << PHY_CONFIG_SHIFT |
	       SPEED_MODE_GEN2 << GEN2_EN_SHIFT;
	ग_लिखोl_relaxed(val, priv->base + SATA_PORT_PHYCTL);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops hix5hd2_sata_phy_ops = अणु
	.init		= hix5hd2_sata_phy_init,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक hix5hd2_sata_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा phy_provider *phy_provider;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	काष्ठा phy *phy;
	काष्ठा hix5hd2_priv *priv;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -EINVAL;

	priv->base = devm_ioremap(dev, res->start, resource_size(res));
	अगर (!priv->base)
		वापस -ENOMEM;

	priv->peri_ctrl = syscon_regmap_lookup_by_phandle(dev->of_node,
					"hisilicon,peripheral-syscon");
	अगर (IS_ERR(priv->peri_ctrl))
		priv->peri_ctrl = शून्य;

	phy = devm_phy_create(dev, शून्य, &hix5hd2_sata_phy_ops);
	अगर (IS_ERR(phy)) अणु
		dev_err(dev, "failed to create PHY\n");
		वापस PTR_ERR(phy);
	पूर्ण

	phy_set_drvdata(phy, priv);
	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);
	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल स्थिर काष्ठा of_device_id hix5hd2_sata_phy_of_match[] = अणु
	अणु.compatible = "hisilicon,hix5hd2-sata-phy",पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, hix5hd2_sata_phy_of_match);

अटल काष्ठा platक्रमm_driver hix5hd2_sata_phy_driver = अणु
	.probe	= hix5hd2_sata_phy_probe,
	.driver = अणु
		.name	= "hix5hd2-sata-phy",
		.of_match_table	= hix5hd2_sata_phy_of_match,
	पूर्ण
पूर्ण;
module_platक्रमm_driver(hix5hd2_sata_phy_driver);

MODULE_AUTHOR("Jiancheng Xue <xuejiancheng@huawei.com>");
MODULE_DESCRIPTION("HISILICON HIX5HD2 SATA PHY driver");
MODULE_ALIAS("platform:hix5hd2-sata-phy");
MODULE_LICENSE("GPL v2");
