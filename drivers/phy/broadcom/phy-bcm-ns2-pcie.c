<शैली गुरु>
/*
 * Copyright (C) 2016 Broadcom
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/mdपन.स>
#समावेश <linux/phy.h>
#समावेश <linux/phy/phy.h>

#घोषणा BLK_ADDR_REG_OFFSET	0x1f
#घोषणा PLL_AFE1_100MHZ_BLK	0x2100
#घोषणा PLL_CLK_AMP_OFFSET	0x03
#घोषणा PLL_CLK_AMP_2P05V	0x2b18

अटल पूर्णांक ns2_pci_phy_init(काष्ठा phy *p)
अणु
	काष्ठा mdio_device *mdiodev = phy_get_drvdata(p);
	पूर्णांक rc;

	/* select the AFE 100MHz block page */
	rc = mdiobus_ग_लिखो(mdiodev->bus, mdiodev->addr,
			   BLK_ADDR_REG_OFFSET, PLL_AFE1_100MHZ_BLK);
	अगर (rc)
		जाओ err;

	/* set the 100 MHz reference घड़ी amplitude to 2.05 v */
	rc = mdiobus_ग_लिखो(mdiodev->bus, mdiodev->addr,
			   PLL_CLK_AMP_OFFSET, PLL_CLK_AMP_2P05V);
	अगर (rc)
		जाओ err;

	वापस 0;

err:
	dev_err(&mdiodev->dev, "Error %d writing to phy\n", rc);
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा phy_ops ns2_pci_phy_ops = अणु
	.init = ns2_pci_phy_init,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक ns2_pci_phy_probe(काष्ठा mdio_device *mdiodev)
अणु
	काष्ठा device *dev = &mdiodev->dev;
	काष्ठा phy_provider *provider;
	काष्ठा phy *phy;

	phy = devm_phy_create(dev, dev->of_node, &ns2_pci_phy_ops);
	अगर (IS_ERR(phy)) अणु
		dev_err(dev, "failed to create Phy\n");
		वापस PTR_ERR(phy);
	पूर्ण

	phy_set_drvdata(phy, mdiodev);

	provider = devm_of_phy_provider_रेजिस्टर(&phy->dev,
						 of_phy_simple_xlate);
	अगर (IS_ERR(provider)) अणु
		dev_err(dev, "failed to register Phy provider\n");
		वापस PTR_ERR(provider);
	पूर्ण

	dev_info(dev, "%s PHY registered\n", dev_name(dev));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ns2_pci_phy_of_match[] = अणु
	अणु .compatible = "brcm,ns2-pcie-phy", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ns2_pci_phy_of_match);

अटल काष्ठा mdio_driver ns2_pci_phy_driver = अणु
	.mdiodrv = अणु
		.driver = अणु
			.name = "phy-bcm-ns2-pci",
			.of_match_table = ns2_pci_phy_of_match,
		पूर्ण,
	पूर्ण,
	.probe = ns2_pci_phy_probe,
पूर्ण;
mdio_module_driver(ns2_pci_phy_driver);

MODULE_AUTHOR("Broadcom");
MODULE_DESCRIPTION("Broadcom Northstar2 PCI Phy driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:phy-bcm-ns2-pci");
