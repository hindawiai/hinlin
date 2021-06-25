<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Marvell Berlin SATA PHY driver
 *
 * Copyright (C) 2014 Marvell Technology Group Ltd.
 *
 * Antoine Tथऊnart <antoine.tenart@मुक्त-electrons.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>

#घोषणा HOST_VSA_ADDR		0x0
#घोषणा HOST_VSA_DATA		0x4
#घोषणा PORT_SCR_CTL		0x2c
#घोषणा PORT_VSR_ADDR		0x78
#घोषणा PORT_VSR_DATA		0x7c

#घोषणा CONTROL_REGISTER	0x0
#घोषणा MBUS_SIZE_CONTROL	0x4

#घोषणा POWER_DOWN_PHY0			BIT(6)
#घोषणा POWER_DOWN_PHY1			BIT(14)
#घोषणा MBUS_WRITE_REQUEST_SIZE_128	(BIT(2) << 16)
#घोषणा MBUS_READ_REQUEST_SIZE_128	(BIT(2) << 19)

#घोषणा BG2_PHY_BASE		0x080
#घोषणा BG2Q_PHY_BASE		0x200

/* रेजिस्टर 0x01 */
#घोषणा REF_FREF_SEL_25		BIT(0)
#घोषणा PHY_BERLIN_MODE_SATA	(0x0 << 5)

/* रेजिस्टर 0x02 */
#घोषणा USE_MAX_PLL_RATE	BIT(12)

/* रेजिस्टर 0x23 */
#घोषणा DATA_BIT_WIDTH_10	(0x0 << 10)
#घोषणा DATA_BIT_WIDTH_20	(0x1 << 10)
#घोषणा DATA_BIT_WIDTH_40	(0x2 << 10)

/* रेजिस्टर 0x25 */
#घोषणा PHY_GEN_MAX_1_5		(0x0 << 10)
#घोषणा PHY_GEN_MAX_3_0		(0x1 << 10)
#घोषणा PHY_GEN_MAX_6_0		(0x2 << 10)

काष्ठा phy_berlin_desc अणु
	काष्ठा phy	*phy;
	u32		घातer_bit;
	अचिन्हित	index;
पूर्ण;

काष्ठा phy_berlin_priv अणु
	व्योम __iomem		*base;
	spinlock_t		lock;
	काष्ठा clk		*clk;
	काष्ठा phy_berlin_desc	**phys;
	अचिन्हित		nphys;
	u32			phy_base;
पूर्ण;

अटल अंतरभूत व्योम phy_berlin_sata_reg_setbits(व्योम __iomem *ctrl_reg,
			       u32 phy_base, u32 reg, u32 mask, u32 val)
अणु
	u32 regval;

	/* select रेजिस्टर */
	ग_लिखोl(phy_base + reg, ctrl_reg + PORT_VSR_ADDR);

	/* set bits */
	regval = पढ़ोl(ctrl_reg + PORT_VSR_DATA);
	regval &= ~mask;
	regval |= val;
	ग_लिखोl(regval, ctrl_reg + PORT_VSR_DATA);
पूर्ण

अटल पूर्णांक phy_berlin_sata_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा phy_berlin_desc *desc = phy_get_drvdata(phy);
	काष्ठा phy_berlin_priv *priv = dev_get_drvdata(phy->dev.parent);
	व्योम __iomem *ctrl_reg = priv->base + 0x60 + (desc->index * 0x80);
	u32 regval;

	clk_prepare_enable(priv->clk);

	spin_lock(&priv->lock);

	/* Power on PHY */
	ग_लिखोl(CONTROL_REGISTER, priv->base + HOST_VSA_ADDR);
	regval = पढ़ोl(priv->base + HOST_VSA_DATA);
	regval &= ~desc->घातer_bit;
	ग_लिखोl(regval, priv->base + HOST_VSA_DATA);

	/* Configure MBus */
	ग_लिखोl(MBUS_SIZE_CONTROL, priv->base + HOST_VSA_ADDR);
	regval = पढ़ोl(priv->base + HOST_VSA_DATA);
	regval |= MBUS_WRITE_REQUEST_SIZE_128 | MBUS_READ_REQUEST_SIZE_128;
	ग_लिखोl(regval, priv->base + HOST_VSA_DATA);

	/* set PHY mode and ref freq to 25 MHz */
	phy_berlin_sata_reg_setbits(ctrl_reg, priv->phy_base, 0x01,
				    0x00ff,
				    REF_FREF_SEL_25 | PHY_BERLIN_MODE_SATA);

	/* set PHY up to 6 Gbps */
	phy_berlin_sata_reg_setbits(ctrl_reg, priv->phy_base, 0x25,
				    0x0c00, PHY_GEN_MAX_6_0);

	/* set 40 bits width */
	phy_berlin_sata_reg_setbits(ctrl_reg, priv->phy_base, 0x23,
				    0x0c00, DATA_BIT_WIDTH_40);

	/* use max pll rate */
	phy_berlin_sata_reg_setbits(ctrl_reg, priv->phy_base, 0x02,
				    0x0000, USE_MAX_PLL_RATE);

	/* set Gen3 controller speed */
	regval = पढ़ोl(ctrl_reg + PORT_SCR_CTL);
	regval &= ~GENMASK(7, 4);
	regval |= 0x30;
	ग_लिखोl(regval, ctrl_reg + PORT_SCR_CTL);

	spin_unlock(&priv->lock);

	clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक phy_berlin_sata_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा phy_berlin_desc *desc = phy_get_drvdata(phy);
	काष्ठा phy_berlin_priv *priv = dev_get_drvdata(phy->dev.parent);
	u32 regval;

	clk_prepare_enable(priv->clk);

	spin_lock(&priv->lock);

	/* Power करोwn PHY */
	ग_लिखोl(CONTROL_REGISTER, priv->base + HOST_VSA_ADDR);
	regval = पढ़ोl(priv->base + HOST_VSA_DATA);
	regval |= desc->घातer_bit;
	ग_लिखोl(regval, priv->base + HOST_VSA_DATA);

	spin_unlock(&priv->lock);

	clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण

अटल काष्ठा phy *phy_berlin_sata_phy_xlate(काष्ठा device *dev,
					     काष्ठा of_phandle_args *args)
अणु
	काष्ठा phy_berlin_priv *priv = dev_get_drvdata(dev);
	पूर्णांक i;

	अगर (WARN_ON(args->args[0] >= priv->nphys))
		वापस ERR_PTR(-ENODEV);

	क्रम (i = 0; i < priv->nphys; i++) अणु
		अगर (priv->phys[i]->index == args->args[0])
			अवरोध;
	पूर्ण

	अगर (i == priv->nphys)
		वापस ERR_PTR(-ENODEV);

	वापस priv->phys[i]->phy;
पूर्ण

अटल स्थिर काष्ठा phy_ops phy_berlin_sata_ops = अणु
	.घातer_on	= phy_berlin_sata_घातer_on,
	.घातer_off	= phy_berlin_sata_घातer_off,
	.owner		= THIS_MODULE,
पूर्ण;

अटल u32 phy_berlin_घातer_करोwn_bits[] = अणु
	POWER_DOWN_PHY0,
	POWER_DOWN_PHY1,
पूर्ण;

अटल पूर्णांक phy_berlin_sata_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *child;
	काष्ठा phy *phy;
	काष्ठा phy_provider *phy_provider;
	काष्ठा phy_berlin_priv *priv;
	काष्ठा resource *res;
	पूर्णांक ret, i = 0;
	u32 phy_id;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -EINVAL;

	priv->base = devm_ioremap(dev, res->start, resource_size(res));
	अगर (!priv->base)
		वापस -ENOMEM;

	priv->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(priv->clk))
		वापस PTR_ERR(priv->clk);

	priv->nphys = of_get_child_count(dev->of_node);
	अगर (priv->nphys == 0)
		वापस -ENODEV;

	priv->phys = devm_kसुस्मृति(dev, priv->nphys, माप(*priv->phys),
				  GFP_KERNEL);
	अगर (!priv->phys)
		वापस -ENOMEM;

	अगर (of_device_is_compatible(dev->of_node, "marvell,berlin2-sata-phy"))
		priv->phy_base = BG2_PHY_BASE;
	अन्यथा
		priv->phy_base = BG2Q_PHY_BASE;

	dev_set_drvdata(dev, priv);
	spin_lock_init(&priv->lock);

	क्रम_each_available_child_of_node(dev->of_node, child) अणु
		काष्ठा phy_berlin_desc *phy_desc;

		अगर (of_property_पढ़ो_u32(child, "reg", &phy_id)) अणु
			dev_err(dev, "missing reg property in node %pOFn\n",
				child);
			ret = -EINVAL;
			जाओ put_child;
		पूर्ण

		अगर (phy_id >= ARRAY_SIZE(phy_berlin_घातer_करोwn_bits)) अणु
			dev_err(dev, "invalid reg in node %pOFn\n", child);
			ret = -EINVAL;
			जाओ put_child;
		पूर्ण

		phy_desc = devm_kzalloc(dev, माप(*phy_desc), GFP_KERNEL);
		अगर (!phy_desc) अणु
			ret = -ENOMEM;
			जाओ put_child;
		पूर्ण

		phy = devm_phy_create(dev, शून्य, &phy_berlin_sata_ops);
		अगर (IS_ERR(phy)) अणु
			dev_err(dev, "failed to create PHY %d\n", phy_id);
			ret = PTR_ERR(phy);
			जाओ put_child;
		पूर्ण

		phy_desc->phy = phy;
		phy_desc->घातer_bit = phy_berlin_घातer_करोwn_bits[phy_id];
		phy_desc->index = phy_id;
		phy_set_drvdata(phy, phy_desc);

		priv->phys[i++] = phy_desc;

		/* Make sure the PHY is off */
		phy_berlin_sata_घातer_off(phy);
	पूर्ण

	phy_provider =
		devm_of_phy_provider_रेजिस्टर(dev, phy_berlin_sata_phy_xlate);
	वापस PTR_ERR_OR_ZERO(phy_provider);
put_child:
	of_node_put(child);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id phy_berlin_sata_of_match[] = अणु
	अणु .compatible = "marvell,berlin2-sata-phy" पूर्ण,
	अणु .compatible = "marvell,berlin2q-sata-phy" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, phy_berlin_sata_of_match);

अटल काष्ठा platक्रमm_driver phy_berlin_sata_driver = अणु
	.probe	= phy_berlin_sata_probe,
	.driver	= अणु
		.name		= "phy-berlin-sata",
		.of_match_table	= phy_berlin_sata_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(phy_berlin_sata_driver);

MODULE_DESCRIPTION("Marvell Berlin SATA PHY driver");
MODULE_AUTHOR("Antoine Tथऊnart <antoine.tenart@free-electrons.com>");
MODULE_LICENSE("GPL v2");
