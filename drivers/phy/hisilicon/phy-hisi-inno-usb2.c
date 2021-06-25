<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * HiSilicon INNO USB2 PHY Driver.
 *
 * Copyright (c) 2016-2017 HiSilicon Technologies Co., Ltd.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/reset.h>

#घोषणा INNO_PHY_PORT_NUM	2
#घोषणा REF_CLK_STABLE_TIME	100	/* unit:us */
#घोषणा UTMI_CLK_STABLE_TIME	200	/* unit:us */
#घोषणा TEST_CLK_STABLE_TIME	2	/* unit:ms */
#घोषणा PHY_CLK_STABLE_TIME	2	/* unit:ms */
#घोषणा UTMI_RST_COMPLETE_TIME	2	/* unit:ms */
#घोषणा POR_RST_COMPLETE_TIME	300	/* unit:us */
#घोषणा PHY_TEST_DATA		GENMASK(7, 0)
#घोषणा PHY_TEST_ADDR		GENMASK(15, 8)
#घोषणा PHY_TEST_PORT		GENMASK(18, 16)
#घोषणा PHY_TEST_WREN		BIT(21)
#घोषणा PHY_TEST_CLK		BIT(22)	/* rising edge active */
#घोषणा PHY_TEST_RST		BIT(23)	/* low active */
#घोषणा PHY_CLK_ENABLE		BIT(2)

काष्ठा hisi_inno_phy_port अणु
	काष्ठा reset_control *uपंचांगi_rst;
	काष्ठा hisi_inno_phy_priv *priv;
पूर्ण;

काष्ठा hisi_inno_phy_priv अणु
	व्योम __iomem *mmio;
	काष्ठा clk *ref_clk;
	काष्ठा reset_control *por_rst;
	काष्ठा hisi_inno_phy_port ports[INNO_PHY_PORT_NUM];
पूर्ण;

अटल व्योम hisi_inno_phy_ग_लिखो_reg(काष्ठा hisi_inno_phy_priv *priv,
				    u8 port, u32 addr, u32 data)
अणु
	व्योम __iomem *reg = priv->mmio;
	u32 val;

	val = (data & PHY_TEST_DATA) |
	      ((addr << 8) & PHY_TEST_ADDR) |
	      ((port << 16) & PHY_TEST_PORT) |
	      PHY_TEST_WREN | PHY_TEST_RST;
	ग_लिखोl(val, reg);

	val |= PHY_TEST_CLK;
	ग_लिखोl(val, reg);

	val &= ~PHY_TEST_CLK;
	ग_लिखोl(val, reg);
पूर्ण

अटल व्योम hisi_inno_phy_setup(काष्ठा hisi_inno_phy_priv *priv)
अणु
	/* The phy clk is controlled by the port0 रेजिस्टर 0x06. */
	hisi_inno_phy_ग_लिखो_reg(priv, 0, 0x06, PHY_CLK_ENABLE);
	msleep(PHY_CLK_STABLE_TIME);
पूर्ण

अटल पूर्णांक hisi_inno_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा hisi_inno_phy_port *port = phy_get_drvdata(phy);
	काष्ठा hisi_inno_phy_priv *priv = port->priv;
	पूर्णांक ret;

	ret = clk_prepare_enable(priv->ref_clk);
	अगर (ret)
		वापस ret;
	udelay(REF_CLK_STABLE_TIME);

	reset_control_deनिश्चित(priv->por_rst);
	udelay(POR_RST_COMPLETE_TIME);

	/* Set up phy रेजिस्टरs */
	hisi_inno_phy_setup(priv);

	reset_control_deनिश्चित(port->uपंचांगi_rst);
	udelay(UTMI_RST_COMPLETE_TIME);

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_inno_phy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा hisi_inno_phy_port *port = phy_get_drvdata(phy);
	काष्ठा hisi_inno_phy_priv *priv = port->priv;

	reset_control_निश्चित(port->uपंचांगi_rst);
	reset_control_निश्चित(priv->por_rst);
	clk_disable_unprepare(priv->ref_clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops hisi_inno_phy_ops = अणु
	.init = hisi_inno_phy_init,
	.निकास = hisi_inno_phy_निकास,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक hisi_inno_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा hisi_inno_phy_priv *priv;
	काष्ठा phy_provider *provider;
	काष्ठा device_node *child;
	पूर्णांक i = 0;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->mmio = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->mmio)) अणु
		ret = PTR_ERR(priv->mmio);
		वापस ret;
	पूर्ण

	priv->ref_clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(priv->ref_clk))
		वापस PTR_ERR(priv->ref_clk);

	priv->por_rst = devm_reset_control_get_exclusive(dev, शून्य);
	अगर (IS_ERR(priv->por_rst))
		वापस PTR_ERR(priv->por_rst);

	क्रम_each_child_of_node(np, child) अणु
		काष्ठा reset_control *rst;
		काष्ठा phy *phy;

		rst = of_reset_control_get_exclusive(child, शून्य);
		अगर (IS_ERR(rst))
			वापस PTR_ERR(rst);
		priv->ports[i].uपंचांगi_rst = rst;
		priv->ports[i].priv = priv;

		phy = devm_phy_create(dev, child, &hisi_inno_phy_ops);
		अगर (IS_ERR(phy))
			वापस PTR_ERR(phy);

		phy_set_bus_width(phy, 8);
		phy_set_drvdata(phy, &priv->ports[i]);
		i++;

		अगर (i > INNO_PHY_PORT_NUM) अणु
			dev_warn(dev, "Support %d ports in maximum\n", i);
			अवरोध;
		पूर्ण
	पूर्ण

	provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);
	वापस PTR_ERR_OR_ZERO(provider);
पूर्ण

अटल स्थिर काष्ठा of_device_id hisi_inno_phy_of_match[] = अणु
	अणु .compatible = "hisilicon,inno-usb2-phy", पूर्ण,
	अणु .compatible = "hisilicon,hi3798cv200-usb2-phy", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, hisi_inno_phy_of_match);

अटल काष्ठा platक्रमm_driver hisi_inno_phy_driver = अणु
	.probe	= hisi_inno_phy_probe,
	.driver = अणु
		.name	= "hisi-inno-phy",
		.of_match_table	= hisi_inno_phy_of_match,
	पूर्ण
पूर्ण;
module_platक्रमm_driver(hisi_inno_phy_driver);

MODULE_DESCRIPTION("HiSilicon INNO USB2 PHY Driver");
MODULE_LICENSE("GPL v2");
