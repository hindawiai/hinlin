<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Russell King, Deep Blue Solutions Ltd.
 *
 * Partly derived from CP110 comphy driver by Antoine Tenart
 * <antoine.tenart@bootlin.com>
 */
#समावेश <linux/delay.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा MAX_A38X_COMPHY	6
#घोषणा MAX_A38X_PORTS	3

#घोषणा COMPHY_CFG1		0x00
#घोषणा  COMPHY_CFG1_GEN_TX(x)		((x) << 26)
#घोषणा  COMPHY_CFG1_GEN_TX_MSK		COMPHY_CFG1_GEN_TX(15)
#घोषणा  COMPHY_CFG1_GEN_RX(x)		((x) << 22)
#घोषणा  COMPHY_CFG1_GEN_RX_MSK		COMPHY_CFG1_GEN_RX(15)
#घोषणा  GEN_SGMII_1_25GBPS		6
#घोषणा  GEN_SGMII_3_125GBPS		8

#घोषणा COMPHY_STAT1		0x18
#घोषणा  COMPHY_STAT1_PLL_RDY_TX	BIT(3)
#घोषणा  COMPHY_STAT1_PLL_RDY_RX	BIT(2)

#घोषणा COMPHY_SELECTOR		0xfc

काष्ठा a38x_comphy;

काष्ठा a38x_comphy_lane अणु
	व्योम __iomem *base;
	काष्ठा a38x_comphy *priv;
	अचिन्हित पूर्णांक n;

	पूर्णांक port;
पूर्ण;

काष्ठा a38x_comphy अणु
	व्योम __iomem *base;
	व्योम __iomem *conf;
	काष्ठा device *dev;
	काष्ठा a38x_comphy_lane lane[MAX_A38X_COMPHY];
पूर्ण;

अटल स्थिर u8 gbe_mux[MAX_A38X_COMPHY][MAX_A38X_PORTS] = अणु
	अणु 0, 0, 0 पूर्ण,
	अणु 4, 5, 0 पूर्ण,
	अणु 0, 4, 0 पूर्ण,
	अणु 0, 0, 4 पूर्ण,
	अणु 0, 3, 0 पूर्ण,
	अणु 0, 0, 3 पूर्ण,
पूर्ण;

अटल व्योम a38x_set_conf(काष्ठा a38x_comphy_lane *lane, bool enable)
अणु
	काष्ठा a38x_comphy *priv = lane->priv;
	u32 conf;

	अगर (priv->conf) अणु
		conf = पढ़ोl_relaxed(priv->conf);
		अगर (enable)
			conf |= BIT(lane->port);
		अन्यथा
			conf &= ~BIT(lane->port);
		ग_लिखोl(conf, priv->conf);
	पूर्ण
पूर्ण

अटल व्योम a38x_comphy_set_reg(काष्ठा a38x_comphy_lane *lane,
				अचिन्हित पूर्णांक offset, u32 mask, u32 value)
अणु
	u32 val;

	val = पढ़ोl_relaxed(lane->base + offset) & ~mask;
	ग_लिखोl(val | value, lane->base + offset);
पूर्ण

अटल व्योम a38x_comphy_set_speed(काष्ठा a38x_comphy_lane *lane,
				  अचिन्हित पूर्णांक gen_tx, अचिन्हित पूर्णांक gen_rx)
अणु
	a38x_comphy_set_reg(lane, COMPHY_CFG1,
			    COMPHY_CFG1_GEN_TX_MSK | COMPHY_CFG1_GEN_RX_MSK,
			    COMPHY_CFG1_GEN_TX(gen_tx) |
		            COMPHY_CFG1_GEN_RX(gen_rx));
पूर्ण

अटल पूर्णांक a38x_comphy_poll(काष्ठा a38x_comphy_lane *lane,
			    अचिन्हित पूर्णांक offset, u32 mask, u32 value)
अणु
	u32 val;
	पूर्णांक ret;

	ret = पढ़ोl_relaxed_poll_समयout_atomic(lane->base + offset, val,
						(val & mask) == value,
						1000, 150000);

	अगर (ret)
		dev_err(lane->priv->dev,
			"comphy%u: timed out waiting for status\n", lane->n);

	वापस ret;
पूर्ण

/*
 * We only support changing the speed क्रम comphys configured क्रम GBE.
 * Since that is all we करो, we only poll क्रम PLL पढ़ोy status.
 */
अटल पूर्णांक a38x_comphy_set_mode(काष्ठा phy *phy, क्रमागत phy_mode mode, पूर्णांक sub)
अणु
	काष्ठा a38x_comphy_lane *lane = phy_get_drvdata(phy);
	अचिन्हित पूर्णांक gen;
	पूर्णांक ret;

	अगर (mode != PHY_MODE_ETHERNET)
		वापस -EINVAL;

	चयन (sub) अणु
	हाल PHY_INTERFACE_MODE_SGMII:
	हाल PHY_INTERFACE_MODE_1000BASEX:
		gen = GEN_SGMII_1_25GBPS;
		अवरोध;

	हाल PHY_INTERFACE_MODE_2500BASEX:
		gen = GEN_SGMII_3_125GBPS;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	a38x_set_conf(lane, false);

	a38x_comphy_set_speed(lane, gen, gen);

	ret = a38x_comphy_poll(lane, COMPHY_STAT1,
			       COMPHY_STAT1_PLL_RDY_TX |
			       COMPHY_STAT1_PLL_RDY_RX,
			       COMPHY_STAT1_PLL_RDY_TX |
			       COMPHY_STAT1_PLL_RDY_RX);

	अगर (ret == 0)
		a38x_set_conf(lane, true);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा phy_ops a38x_comphy_ops = अणु
	.set_mode	= a38x_comphy_set_mode,
	.owner		= THIS_MODULE,
पूर्ण;

अटल काष्ठा phy *a38x_comphy_xlate(काष्ठा device *dev,
				     काष्ठा of_phandle_args *args)
अणु
	काष्ठा a38x_comphy_lane *lane;
	काष्ठा phy *phy;
	u32 val;

	अगर (WARN_ON(args->args[0] >= MAX_A38X_PORTS))
		वापस ERR_PTR(-EINVAL);

	phy = of_phy_simple_xlate(dev, args);
	अगर (IS_ERR(phy))
		वापस phy;

	lane = phy_get_drvdata(phy);
	अगर (lane->port >= 0)
		वापस ERR_PTR(-EBUSY);

	lane->port = args->args[0];

	val = पढ़ोl_relaxed(lane->priv->base + COMPHY_SELECTOR);
	val = (val >> (4 * lane->n)) & 0xf;

	अगर (!gbe_mux[lane->n][lane->port] ||
	    val != gbe_mux[lane->n][lane->port]) अणु
		dev_warn(lane->priv->dev,
			 "comphy%u: not configured for GBE\n", lane->n);
		phy = ERR_PTR(-EINVAL);
	पूर्ण

	वापस phy;
पूर्ण

अटल पूर्णांक a38x_comphy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा phy_provider *provider;
	काष्ठा device_node *child;
	काष्ठा a38x_comphy *priv;
	काष्ठा resource *res;
	व्योम __iomem *base;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	priv->dev = &pdev->dev;
	priv->base = base;

	/* Optional */
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "conf");
	अगर (res) अणु
		priv->conf = devm_ioremap_resource(&pdev->dev, res);
		अगर (IS_ERR(priv->conf))
			वापस PTR_ERR(priv->conf);
	पूर्ण

	क्रम_each_available_child_of_node(pdev->dev.of_node, child) अणु
		काष्ठा phy *phy;
		पूर्णांक ret;
		u32 val;

		ret = of_property_पढ़ो_u32(child, "reg", &val);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev, "missing 'reg' property (%d)\n",
				ret);
			जारी;
		पूर्ण

		अगर (val >= MAX_A38X_COMPHY || priv->lane[val].base) अणु
			dev_err(&pdev->dev, "invalid 'reg' property\n");
			जारी;
		पूर्ण

		phy = devm_phy_create(&pdev->dev, child, &a38x_comphy_ops);
		अगर (IS_ERR(phy)) अणु
			of_node_put(child);
			वापस PTR_ERR(phy);
		पूर्ण

		priv->lane[val].base = base + 0x28 * val;
		priv->lane[val].priv = priv;
		priv->lane[val].n = val;
		priv->lane[val].port = -1;
		phy_set_drvdata(phy, &priv->lane[val]);
	पूर्ण

	dev_set_drvdata(&pdev->dev, priv);

	provider = devm_of_phy_provider_रेजिस्टर(&pdev->dev, a38x_comphy_xlate);

	वापस PTR_ERR_OR_ZERO(provider);
पूर्ण

अटल स्थिर काष्ठा of_device_id a38x_comphy_of_match_table[] = अणु
	अणु .compatible = "marvell,armada-380-comphy" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, a38x_comphy_of_match_table);

अटल काष्ठा platक्रमm_driver a38x_comphy_driver = अणु
	.probe	= a38x_comphy_probe,
	.driver	= अणु
		.name = "armada-38x-comphy",
		.of_match_table = a38x_comphy_of_match_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(a38x_comphy_driver);

MODULE_AUTHOR("Russell King <rmk+kernel@armlinux.org.uk>");
MODULE_DESCRIPTION("Common PHY driver for Armada 38x SoCs");
MODULE_LICENSE("GPL v2");
