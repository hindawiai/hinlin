<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Texas Instruments Ethernet Switch Driver
 *
 * Copyright (C) 2013 Texas Instruments
 *
 * Module Author: Mugunthan V N <mugunthanvnm@ti.com>
 *
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/phy.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#समावेश "cpsw.h"

/* AM33xx SoC specअगरic definitions क्रम the CONTROL port */
#घोषणा AM33XX_GMII_SEL_MODE_MII	0
#घोषणा AM33XX_GMII_SEL_MODE_RMII	1
#घोषणा AM33XX_GMII_SEL_MODE_RGMII	2

#घोषणा AM33XX_GMII_SEL_RMII2_IO_CLK_EN	BIT(7)
#घोषणा AM33XX_GMII_SEL_RMII1_IO_CLK_EN	BIT(6)
#घोषणा AM33XX_GMII_SEL_RGMII2_IDMODE	BIT(5)
#घोषणा AM33XX_GMII_SEL_RGMII1_IDMODE	BIT(4)

#घोषणा GMII_SEL_MODE_MASK		0x3

काष्ठा cpsw_phy_sel_priv अणु
	काष्ठा device	*dev;
	u32 __iomem	*gmii_sel;
	bool		rmii_घड़ी_बाह्यal;
	व्योम (*cpsw_phy_sel)(काष्ठा cpsw_phy_sel_priv *priv,
			     phy_पूर्णांकerface_t phy_mode, पूर्णांक slave);
पूर्ण;


अटल व्योम cpsw_gmii_sel_am3352(काष्ठा cpsw_phy_sel_priv *priv,
				 phy_पूर्णांकerface_t phy_mode, पूर्णांक slave)
अणु
	u32 reg;
	u32 mask;
	u32 mode = 0;
	bool rgmii_id = false;

	reg = पढ़ोl(priv->gmii_sel);

	चयन (phy_mode) अणु
	हाल PHY_INTERFACE_MODE_RMII:
		mode = AM33XX_GMII_SEL_MODE_RMII;
		अवरोध;

	हाल PHY_INTERFACE_MODE_RGMII:
		mode = AM33XX_GMII_SEL_MODE_RGMII;
		अवरोध;

	हाल PHY_INTERFACE_MODE_RGMII_ID:
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
		mode = AM33XX_GMII_SEL_MODE_RGMII;
		rgmii_id = true;
		अवरोध;

	शेष:
		dev_warn(priv->dev,
			 "Unsupported PHY mode: \"%s\". Defaulting to MII.\n",
			phy_modes(phy_mode));
		fallthrough;
	हाल PHY_INTERFACE_MODE_MII:
		mode = AM33XX_GMII_SEL_MODE_MII;
		अवरोध;
	पूर्ण

	mask = GMII_SEL_MODE_MASK << (slave * 2) | BIT(slave + 6);
	mask |= BIT(slave + 4);
	mode <<= slave * 2;

	अगर (priv->rmii_घड़ी_बाह्यal) अणु
		अगर (slave == 0)
			mode |= AM33XX_GMII_SEL_RMII1_IO_CLK_EN;
		अन्यथा
			mode |= AM33XX_GMII_SEL_RMII2_IO_CLK_EN;
	पूर्ण

	अगर (rgmii_id) अणु
		अगर (slave == 0)
			mode |= AM33XX_GMII_SEL_RGMII1_IDMODE;
		अन्यथा
			mode |= AM33XX_GMII_SEL_RGMII2_IDMODE;
	पूर्ण

	reg &= ~mask;
	reg |= mode;

	ग_लिखोl(reg, priv->gmii_sel);
पूर्ण

अटल व्योम cpsw_gmii_sel_dra7xx(काष्ठा cpsw_phy_sel_priv *priv,
				 phy_पूर्णांकerface_t phy_mode, पूर्णांक slave)
अणु
	u32 reg;
	u32 mask;
	u32 mode = 0;

	reg = पढ़ोl(priv->gmii_sel);

	चयन (phy_mode) अणु
	हाल PHY_INTERFACE_MODE_RMII:
		mode = AM33XX_GMII_SEL_MODE_RMII;
		अवरोध;

	हाल PHY_INTERFACE_MODE_RGMII:
	हाल PHY_INTERFACE_MODE_RGMII_ID:
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
		mode = AM33XX_GMII_SEL_MODE_RGMII;
		अवरोध;

	शेष:
		dev_warn(priv->dev,
			 "Unsupported PHY mode: \"%s\". Defaulting to MII.\n",
			phy_modes(phy_mode));
		fallthrough;
	हाल PHY_INTERFACE_MODE_MII:
		mode = AM33XX_GMII_SEL_MODE_MII;
		अवरोध;
	पूर्ण

	चयन (slave) अणु
	हाल 0:
		mask = GMII_SEL_MODE_MASK;
		अवरोध;
	हाल 1:
		mask = GMII_SEL_MODE_MASK << 4;
		mode <<= 4;
		अवरोध;
	शेष:
		dev_err(priv->dev, "invalid slave number...\n");
		वापस;
	पूर्ण

	अगर (priv->rmii_घड़ी_बाह्यal)
		dev_err(priv->dev, "RMII External clock is not supported\n");

	reg &= ~mask;
	reg |= mode;

	ग_लिखोl(reg, priv->gmii_sel);
पूर्ण

अटल काष्ठा platक्रमm_driver cpsw_phy_sel_driver;
अटल पूर्णांक match(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	स्थिर काष्ठा device_node *node = (स्थिर काष्ठा device_node *)data;
	वापस dev->of_node == node &&
		dev->driver == &cpsw_phy_sel_driver.driver;
पूर्ण

व्योम cpsw_phy_sel(काष्ठा device *dev, phy_पूर्णांकerface_t phy_mode, पूर्णांक slave)
अणु
	काष्ठा device_node *node;
	काष्ठा cpsw_phy_sel_priv *priv;

	node = of_parse_phandle(dev->of_node, "cpsw-phy-sel", 0);
	अगर (!node) अणु
		node = of_get_child_by_name(dev->of_node, "cpsw-phy-sel");
		अगर (!node) अणु
			dev_err(dev, "Phy mode driver DT not found\n");
			वापस;
		पूर्ण
	पूर्ण

	dev = bus_find_device(&platक्रमm_bus_type, शून्य, node, match);
	अगर (!dev) अणु
		dev_err(dev, "unable to find platform device for %pOF\n", node);
		जाओ out;
	पूर्ण

	priv = dev_get_drvdata(dev);

	priv->cpsw_phy_sel(priv, phy_mode, slave);

	put_device(dev);
out:
	of_node_put(node);
पूर्ण
EXPORT_SYMBOL_GPL(cpsw_phy_sel);

अटल स्थिर काष्ठा of_device_id cpsw_phy_sel_id_table[] = अणु
	अणु
		.compatible	= "ti,am3352-cpsw-phy-sel",
		.data		= &cpsw_gmii_sel_am3352,
	पूर्ण,
	अणु
		.compatible	= "ti,dra7xx-cpsw-phy-sel",
		.data		= &cpsw_gmii_sel_dra7xx,
	पूर्ण,
	अणु
		.compatible	= "ti,am43xx-cpsw-phy-sel",
		.data		= &cpsw_gmii_sel_am3352,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक cpsw_phy_sel_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource	*res;
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा cpsw_phy_sel_priv *priv;

	of_id = of_match_node(cpsw_phy_sel_id_table, pdev->dev.of_node);
	अगर (!of_id)
		वापस -EINVAL;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv) अणु
		dev_err(&pdev->dev, "unable to alloc memory for cpsw phy sel\n");
		वापस -ENOMEM;
	पूर्ण

	priv->dev = &pdev->dev;
	priv->cpsw_phy_sel = of_id->data;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "gmii-sel");
	priv->gmii_sel = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(priv->gmii_sel))
		वापस PTR_ERR(priv->gmii_sel);

	अगर (of_find_property(pdev->dev.of_node, "rmii-clock-ext", शून्य))
		priv->rmii_घड़ी_बाह्यal = true;

	dev_set_drvdata(&pdev->dev, priv);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver cpsw_phy_sel_driver = अणु
	.probe		= cpsw_phy_sel_probe,
	.driver		= अणु
		.name	= "cpsw-phy-sel",
		.of_match_table = cpsw_phy_sel_id_table,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(cpsw_phy_sel_driver);
