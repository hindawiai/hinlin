<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Broadcom Northstar USB 3.0 PHY Driver
 *
 * Copyright (C) 2016 Rafaध Miधecki <rafal@milecki.pl>
 * Copyright (C) 2016 Broadcom
 *
 * All magic values used क्रम initialization (and related comments) were obtained
 * from Broadcom's SDK:
 * Copyright (c) Broadcom Corp, 2012
 */

#समावेश <linux/bcma/bcma.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/slab.h>

#घोषणा BCM_NS_USB3_PHY_BASE_ADDR_REG	0x1f
#घोषणा BCM_NS_USB3_PHY_PLL30_BLOCK	0x8000
#घोषणा BCM_NS_USB3_PHY_TX_PMD_BLOCK	0x8040
#घोषणा BCM_NS_USB3_PHY_PIPE_BLOCK	0x8060

/* Registers of PLL30 block */
#घोषणा BCM_NS_USB3_PLL_CONTROL		0x01
#घोषणा BCM_NS_USB3_PLLA_CONTROL0	0x0a
#घोषणा BCM_NS_USB3_PLLA_CONTROL1	0x0b

/* Registers of TX PMD block */
#घोषणा BCM_NS_USB3_TX_PMD_CONTROL1	0x01

/* Registers of PIPE block */
#घोषणा BCM_NS_USB3_LFPS_CMP		0x02
#घोषणा BCM_NS_USB3_LFPS_DEGLITCH	0x03

क्रमागत bcm_ns_family अणु
	BCM_NS_UNKNOWN,
	BCM_NS_AX,
	BCM_NS_BX,
पूर्ण;

काष्ठा bcm_ns_usb3 अणु
	काष्ठा device *dev;
	क्रमागत bcm_ns_family family;
	व्योम __iomem *dmp;
	काष्ठा mdio_device *mdiodev;
	काष्ठा phy *phy;
पूर्ण;

अटल स्थिर काष्ठा of_device_id bcm_ns_usb3_id_table[] = अणु
	अणु
		.compatible = "brcm,ns-ax-usb3-phy",
		.data = (पूर्णांक *)BCM_NS_AX,
	पूर्ण,
	अणु
		.compatible = "brcm,ns-bx-usb3-phy",
		.data = (पूर्णांक *)BCM_NS_BX,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक bcm_ns_usb3_mdio_phy_ग_लिखो(काष्ठा bcm_ns_usb3 *usb3, u16 reg,
				      u16 value);

अटल पूर्णांक bcm_ns_usb3_phy_init_ns_bx(काष्ठा bcm_ns_usb3 *usb3)
अणु
	पूर्णांक err;

	/* USB3 PLL Block */
	err = bcm_ns_usb3_mdio_phy_ग_लिखो(usb3, BCM_NS_USB3_PHY_BASE_ADDR_REG,
					 BCM_NS_USB3_PHY_PLL30_BLOCK);
	अगर (err < 0)
		वापस err;

	/* Assert Ana_Pllseq start */
	bcm_ns_usb3_mdio_phy_ग_लिखो(usb3, BCM_NS_USB3_PLL_CONTROL, 0x1000);

	/* Assert CML Divider ratio to 26 */
	bcm_ns_usb3_mdio_phy_ग_लिखो(usb3, BCM_NS_USB3_PLLA_CONTROL0, 0x6400);

	/* Asserting PLL Reset */
	bcm_ns_usb3_mdio_phy_ग_लिखो(usb3, BCM_NS_USB3_PLLA_CONTROL1, 0xc000);

	/* Deaaserting PLL Reset */
	bcm_ns_usb3_mdio_phy_ग_लिखो(usb3, BCM_NS_USB3_PLLA_CONTROL1, 0x8000);

	/* Deनिश्चितing USB3 प्रणाली reset */
	ग_लिखोl(0, usb3->dmp + BCMA_RESET_CTL);

	/* PLL frequency monitor enable */
	bcm_ns_usb3_mdio_phy_ग_लिखो(usb3, BCM_NS_USB3_PLL_CONTROL, 0x9000);

	/* PIPE Block */
	bcm_ns_usb3_mdio_phy_ग_लिखो(usb3, BCM_NS_USB3_PHY_BASE_ADDR_REG,
				   BCM_NS_USB3_PHY_PIPE_BLOCK);

	/* CMPMAX & CMPMINTH setting */
	bcm_ns_usb3_mdio_phy_ग_लिखो(usb3, BCM_NS_USB3_LFPS_CMP, 0xf30d);

	/* DEGLITCH MIN & MAX setting */
	bcm_ns_usb3_mdio_phy_ग_लिखो(usb3, BCM_NS_USB3_LFPS_DEGLITCH, 0x6302);

	/* TXPMD block */
	bcm_ns_usb3_mdio_phy_ग_लिखो(usb3, BCM_NS_USB3_PHY_BASE_ADDR_REG,
				   BCM_NS_USB3_PHY_TX_PMD_BLOCK);

	/* Enabling SSC */
	bcm_ns_usb3_mdio_phy_ग_लिखो(usb3, BCM_NS_USB3_TX_PMD_CONTROL1, 0x1003);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_ns_usb3_phy_init_ns_ax(काष्ठा bcm_ns_usb3 *usb3)
अणु
	पूर्णांक err;

	/* PLL30 block */
	err = bcm_ns_usb3_mdio_phy_ग_लिखो(usb3, BCM_NS_USB3_PHY_BASE_ADDR_REG,
					 BCM_NS_USB3_PHY_PLL30_BLOCK);
	अगर (err < 0)
		वापस err;

	bcm_ns_usb3_mdio_phy_ग_लिखो(usb3, BCM_NS_USB3_PLLA_CONTROL0, 0x6400);

	bcm_ns_usb3_mdio_phy_ग_लिखो(usb3, BCM_NS_USB3_PHY_BASE_ADDR_REG, 0x80e0);

	bcm_ns_usb3_mdio_phy_ग_लिखो(usb3, 0x02, 0x009c);

	/* Enable SSC */
	bcm_ns_usb3_mdio_phy_ग_लिखो(usb3, BCM_NS_USB3_PHY_BASE_ADDR_REG,
				   BCM_NS_USB3_PHY_TX_PMD_BLOCK);

	bcm_ns_usb3_mdio_phy_ग_लिखो(usb3, 0x02, 0x21d3);

	bcm_ns_usb3_mdio_phy_ग_लिखो(usb3, BCM_NS_USB3_TX_PMD_CONTROL1, 0x1003);

	/* Deनिश्चितing USB3 प्रणाली reset */
	ग_लिखोl(0, usb3->dmp + BCMA_RESET_CTL);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_ns_usb3_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा bcm_ns_usb3 *usb3 = phy_get_drvdata(phy);
	पूर्णांक err;

	/* Perक्रमm USB3 प्रणाली soft reset */
	ग_लिखोl(BCMA_RESET_CTL_RESET, usb3->dmp + BCMA_RESET_CTL);

	चयन (usb3->family) अणु
	हाल BCM_NS_AX:
		err = bcm_ns_usb3_phy_init_ns_ax(usb3);
		अवरोध;
	हाल BCM_NS_BX:
		err = bcm_ns_usb3_phy_init_ns_bx(usb3);
		अवरोध;
	शेष:
		WARN_ON(1);
		err = -ENOTSUPP;
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा phy_ops ops = अणु
	.init		= bcm_ns_usb3_phy_init,
	.owner		= THIS_MODULE,
पूर्ण;

/**************************************************
 * MDIO driver code
 **************************************************/

अटल पूर्णांक bcm_ns_usb3_mdio_phy_ग_लिखो(काष्ठा bcm_ns_usb3 *usb3, u16 reg,
				      u16 value)
अणु
	काष्ठा mdio_device *mdiodev = usb3->mdiodev;

	वापस mdiobus_ग_लिखो(mdiodev->bus, mdiodev->addr, reg, value);
पूर्ण

अटल पूर्णांक bcm_ns_usb3_mdio_probe(काष्ठा mdio_device *mdiodev)
अणु
	काष्ठा device *dev = &mdiodev->dev;
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा phy_provider *phy_provider;
	काष्ठा device_node *syscon_np;
	काष्ठा bcm_ns_usb3 *usb3;
	काष्ठा resource res;
	पूर्णांक err;

	usb3 = devm_kzalloc(dev, माप(*usb3), GFP_KERNEL);
	अगर (!usb3)
		वापस -ENOMEM;

	usb3->dev = dev;
	usb3->mdiodev = mdiodev;

	of_id = of_match_device(bcm_ns_usb3_id_table, dev);
	अगर (!of_id)
		वापस -EINVAL;
	usb3->family = (क्रमागत bcm_ns_family)of_id->data;

	syscon_np = of_parse_phandle(dev->of_node, "usb3-dmp-syscon", 0);
	err = of_address_to_resource(syscon_np, 0, &res);
	of_node_put(syscon_np);
	अगर (err)
		वापस err;

	usb3->dmp = devm_ioremap_resource(dev, &res);
	अगर (IS_ERR(usb3->dmp)) अणु
		dev_err(dev, "Failed to map DMP regs\n");
		वापस PTR_ERR(usb3->dmp);
	पूर्ण

	usb3->phy = devm_phy_create(dev, शून्य, &ops);
	अगर (IS_ERR(usb3->phy)) अणु
		dev_err(dev, "Failed to create PHY\n");
		वापस PTR_ERR(usb3->phy);
	पूर्ण

	phy_set_drvdata(usb3->phy, usb3);

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);

	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल काष्ठा mdio_driver bcm_ns_usb3_mdio_driver = अणु
	.mdiodrv = अणु
		.driver = अणु
			.name = "bcm_ns_mdio_usb3",
			.of_match_table = bcm_ns_usb3_id_table,
		पूर्ण,
	पूर्ण,
	.probe = bcm_ns_usb3_mdio_probe,
पूर्ण;

mdio_module_driver(bcm_ns_usb3_mdio_driver);

MODULE_LICENSE("GPL v2");
MODULE_DEVICE_TABLE(of, bcm_ns_usb3_id_table);
