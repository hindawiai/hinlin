<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	phy-mvebu-sata.c: SATA Phy driver क्रम the Marvell mvebu SoCs.
 *
 *	Copyright (C) 2013 Andrew Lunn <andrew@lunn.ch>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/clk.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>

काष्ठा priv अणु
	काष्ठा clk	*clk;
	व्योम __iomem	*base;
पूर्ण;

#घोषणा SATA_PHY_MODE_2	0x0330
#घोषणा  MODE_2_FORCE_PU_TX	BIT(0)
#घोषणा  MODE_2_FORCE_PU_RX	BIT(1)
#घोषणा  MODE_2_PU_PLL		BIT(2)
#घोषणा  MODE_2_PU_IVREF	BIT(3)
#घोषणा SATA_IF_CTRL	0x0050
#घोषणा  CTRL_PHY_SHUTDOWN	BIT(9)

अटल पूर्णांक phy_mvebu_sata_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा priv *priv = phy_get_drvdata(phy);
	u32 reg;

	clk_prepare_enable(priv->clk);

	/* Enable PLL and IVREF */
	reg = पढ़ोl(priv->base + SATA_PHY_MODE_2);
	reg |= (MODE_2_FORCE_PU_TX | MODE_2_FORCE_PU_RX |
		MODE_2_PU_PLL | MODE_2_PU_IVREF);
	ग_लिखोl(reg , priv->base + SATA_PHY_MODE_2);

	/* Enable PHY */
	reg = पढ़ोl(priv->base + SATA_IF_CTRL);
	reg &= ~CTRL_PHY_SHUTDOWN;
	ग_लिखोl(reg, priv->base + SATA_IF_CTRL);

	clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक phy_mvebu_sata_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा priv *priv = phy_get_drvdata(phy);
	u32 reg;

	clk_prepare_enable(priv->clk);

	/* Disable PLL and IVREF */
	reg = पढ़ोl(priv->base + SATA_PHY_MODE_2);
	reg &= ~(MODE_2_FORCE_PU_TX | MODE_2_FORCE_PU_RX |
		 MODE_2_PU_PLL | MODE_2_PU_IVREF);
	ग_लिखोl(reg, priv->base + SATA_PHY_MODE_2);

	/* Disable PHY */
	reg = पढ़ोl(priv->base + SATA_IF_CTRL);
	reg |= CTRL_PHY_SHUTDOWN;
	ग_लिखोl(reg, priv->base + SATA_IF_CTRL);

	clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops phy_mvebu_sata_ops = अणु
	.घातer_on	= phy_mvebu_sata_घातer_on,
	.घातer_off	= phy_mvebu_sata_घातer_off,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक phy_mvebu_sata_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा phy_provider *phy_provider;
	काष्ठा priv *priv;
	काष्ठा phy *phy;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	priv->clk = devm_clk_get(&pdev->dev, "sata");
	अगर (IS_ERR(priv->clk))
		वापस PTR_ERR(priv->clk);

	phy = devm_phy_create(&pdev->dev, शून्य, &phy_mvebu_sata_ops);
	अगर (IS_ERR(phy))
		वापस PTR_ERR(phy);

	phy_set_drvdata(phy, priv);

	phy_provider = devm_of_phy_provider_रेजिस्टर(&pdev->dev,
						     of_phy_simple_xlate);
	अगर (IS_ERR(phy_provider))
		वापस PTR_ERR(phy_provider);

	/* The boot loader may of left it on. Turn it off. */
	phy_mvebu_sata_घातer_off(phy);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id phy_mvebu_sata_of_match[] = अणु
	अणु .compatible = "marvell,mvebu-sata-phy" पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver phy_mvebu_sata_driver = अणु
	.probe	= phy_mvebu_sata_probe,
	.driver = अणु
		.name	= "phy-mvebu-sata",
		.of_match_table	= phy_mvebu_sata_of_match,
	पूर्ण
पूर्ण;
builtin_platक्रमm_driver(phy_mvebu_sata_driver);
