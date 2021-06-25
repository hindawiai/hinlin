<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Xilinx GMII2RGMII Converter driver
 *
 * Copyright (C) 2016 Xilinx, Inc.
 * Copyright (C) 2016 Andrew Lunn <andrew@lunn.ch>
 *
 * Author: Andrew Lunn <andrew@lunn.ch>
 * Author: Kedareswara rao Appana <appanad@xilinx.com>
 *
 * Description:
 * This driver is developed क्रम Xilinx GMII2RGMII Converter
 */
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mii.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/phy.h>
#समावेश <linux/of_mdपन.स>

#घोषणा XILINX_GMII2RGMII_REG		0x10
#घोषणा XILINX_GMII2RGMII_SPEED_MASK	(BMCR_SPEED1000 | BMCR_SPEED100)

काष्ठा gmii2rgmii अणु
	काष्ठा phy_device *phy_dev;
	काष्ठा phy_driver *phy_drv;
	काष्ठा phy_driver conv_phy_drv;
	काष्ठा mdio_device *mdio;
पूर्ण;

अटल पूर्णांक xgmiitorgmii_पढ़ो_status(काष्ठा phy_device *phydev)
अणु
	काष्ठा gmii2rgmii *priv = mdiodev_get_drvdata(&phydev->mdio);
	काष्ठा mii_bus *bus = priv->mdio->bus;
	पूर्णांक addr = priv->mdio->addr;
	u16 val = 0;
	पूर्णांक err;

	अगर (priv->phy_drv->पढ़ो_status)
		err = priv->phy_drv->पढ़ो_status(phydev);
	अन्यथा
		err = genphy_पढ़ो_status(phydev);
	अगर (err < 0)
		वापस err;

	val = mdiobus_पढ़ो(bus, addr, XILINX_GMII2RGMII_REG);
	val &= ~XILINX_GMII2RGMII_SPEED_MASK;

	अगर (phydev->speed == SPEED_1000)
		val |= BMCR_SPEED1000;
	अन्यथा अगर (phydev->speed == SPEED_100)
		val |= BMCR_SPEED100;
	अन्यथा
		val |= BMCR_SPEED10;

	mdiobus_ग_लिखो(bus, addr, XILINX_GMII2RGMII_REG, val);

	वापस 0;
पूर्ण

अटल पूर्णांक xgmiitorgmii_probe(काष्ठा mdio_device *mdiodev)
अणु
	काष्ठा device *dev = &mdiodev->dev;
	काष्ठा device_node *np = dev->of_node, *phy_node;
	काष्ठा gmii2rgmii *priv;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	phy_node = of_parse_phandle(np, "phy-handle", 0);
	अगर (!phy_node) अणु
		dev_err(dev, "Couldn't parse phy-handle\n");
		वापस -ENODEV;
	पूर्ण

	priv->phy_dev = of_phy_find_device(phy_node);
	of_node_put(phy_node);
	अगर (!priv->phy_dev) अणु
		dev_info(dev, "Couldn't find phydev\n");
		वापस -EPROBE_DEFER;
	पूर्ण

	अगर (!priv->phy_dev->drv) अणु
		dev_info(dev, "Attached phy not ready\n");
		वापस -EPROBE_DEFER;
	पूर्ण

	priv->mdio = mdiodev;
	priv->phy_drv = priv->phy_dev->drv;
	स_नकल(&priv->conv_phy_drv, priv->phy_dev->drv,
	       माप(काष्ठा phy_driver));
	priv->conv_phy_drv.पढ़ो_status = xgmiitorgmii_पढ़ो_status;
	mdiodev_set_drvdata(&priv->phy_dev->mdio, priv);
	priv->phy_dev->drv = &priv->conv_phy_drv;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id xgmiitorgmii_of_match[] = अणु
	अणु .compatible = "xlnx,gmii-to-rgmii-1.0" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, xgmiitorgmii_of_match);

अटल काष्ठा mdio_driver xgmiitorgmii_driver = अणु
	.probe	= xgmiitorgmii_probe,
	.mdiodrv.driver = अणु
		.name = "xgmiitorgmii",
		.of_match_table = xgmiitorgmii_of_match,
	पूर्ण,
पूर्ण;

mdio_module_driver(xgmiitorgmii_driver);

MODULE_DESCRIPTION("Xilinx GMII2RGMII converter driver");
MODULE_LICENSE("GPL");
