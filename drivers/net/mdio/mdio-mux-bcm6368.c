<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Broadcom BCM6368 mdiomux bus controller driver
 *
 * Copyright (C) 2021 थlvaro Fernथँndez Rojas <noltari@gmail.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mdio-mux.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>

#घोषणा MDIOC_REG		0x0
#घोषणा MDIOC_EXT_MASK		BIT(16)
#घोषणा MDIOC_REG_SHIFT		20
#घोषणा MDIOC_PHYID_SHIFT	25
#घोषणा MDIOC_RD_MASK		BIT(30)
#घोषणा MDIOC_WR_MASK		BIT(31)

#घोषणा MDIOD_REG		0x4

काष्ठा bcm6368_mdiomux_desc अणु
	व्योम *mux_handle;
	व्योम __iomem *base;
	काष्ठा device *dev;
	काष्ठा mii_bus *mii_bus;
	पूर्णांक ext_phy;
पूर्ण;

अटल पूर्णांक bcm6368_mdiomux_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक loc)
अणु
	काष्ठा bcm6368_mdiomux_desc *md = bus->priv;
	uपूर्णांक32_t reg;
	पूर्णांक ret;

	__raw_ग_लिखोl(0, md->base + MDIOC_REG);

	reg = MDIOC_RD_MASK |
	      (phy_id << MDIOC_PHYID_SHIFT) |
	      (loc << MDIOC_REG_SHIFT);
	अगर (md->ext_phy)
		reg |= MDIOC_EXT_MASK;

	__raw_ग_लिखोl(reg, md->base + MDIOC_REG);
	udelay(50);
	ret = __raw_पढ़ोw(md->base + MDIOD_REG);

	वापस ret;
पूर्ण

अटल पूर्णांक bcm6368_mdiomux_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक loc,
				 uपूर्णांक16_t val)
अणु
	काष्ठा bcm6368_mdiomux_desc *md = bus->priv;
	uपूर्णांक32_t reg;

	__raw_ग_लिखोl(0, md->base + MDIOC_REG);

	reg = MDIOC_WR_MASK |
	      (phy_id << MDIOC_PHYID_SHIFT) |
	      (loc << MDIOC_REG_SHIFT);
	अगर (md->ext_phy)
		reg |= MDIOC_EXT_MASK;
	reg |= val;

	__raw_ग_लिखोl(reg, md->base + MDIOC_REG);
	udelay(50);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm6368_mdiomux_चयन_fn(पूर्णांक current_child, पूर्णांक desired_child,
				     व्योम *data)
अणु
	काष्ठा bcm6368_mdiomux_desc *md = data;

	md->ext_phy = desired_child;

	वापस 0;
पूर्ण

अटल पूर्णांक bcm6368_mdiomux_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcm6368_mdiomux_desc *md;
	काष्ठा mii_bus *bus;
	काष्ठा resource *res;
	पूर्णांक rc;

	md = devm_kzalloc(&pdev->dev, माप(*md), GFP_KERNEL);
	अगर (!md)
		वापस -ENOMEM;
	md->dev = &pdev->dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -EINVAL;

	/*
	 * Just ioremap, as this MDIO block is usually पूर्णांकegrated पूर्णांकo an
	 * Ethernet MAC controller रेजिस्टर range
	 */
	md->base = devm_ioremap(&pdev->dev, res->start, resource_size(res));
	अगर (!md->base) अणु
		dev_err(&pdev->dev, "failed to ioremap register\n");
		वापस -ENOMEM;
	पूर्ण

	md->mii_bus = devm_mdiobus_alloc(&pdev->dev);
	अगर (!md->mii_bus) अणु
		dev_err(&pdev->dev, "mdiomux bus alloc failed\n");
		वापस ENOMEM;
	पूर्ण

	bus = md->mii_bus;
	bus->priv = md;
	bus->name = "BCM6368 MDIO mux bus";
	snम_लिखो(bus->id, MII_BUS_ID_SIZE, "%s-%d", pdev->name, pdev->id);
	bus->parent = &pdev->dev;
	bus->पढ़ो = bcm6368_mdiomux_पढ़ो;
	bus->ग_लिखो = bcm6368_mdiomux_ग_लिखो;
	bus->phy_mask = 0x3f;
	bus->dev.of_node = pdev->dev.of_node;

	rc = mdiobus_रेजिस्टर(bus);
	अगर (rc) अणु
		dev_err(&pdev->dev, "mdiomux registration failed\n");
		वापस rc;
	पूर्ण

	platक्रमm_set_drvdata(pdev, md);

	rc = mdio_mux_init(md->dev, md->dev->of_node,
			   bcm6368_mdiomux_चयन_fn, &md->mux_handle, md,
			   md->mii_bus);
	अगर (rc) अणु
		dev_info(md->dev, "mdiomux initialization failed\n");
		जाओ out_रेजिस्टर;
	पूर्ण

	dev_info(&pdev->dev, "Broadcom BCM6368 MDIO mux bus\n");

	वापस 0;

out_रेजिस्टर:
	mdiobus_unरेजिस्टर(bus);
	वापस rc;
पूर्ण

अटल पूर्णांक bcm6368_mdiomux_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcm6368_mdiomux_desc *md = platक्रमm_get_drvdata(pdev);

	mdio_mux_uninit(md->mux_handle);
	mdiobus_unरेजिस्टर(md->mii_bus);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm6368_mdiomux_ids[] = अणु
	अणु .compatible = "brcm,bcm6368-mdio-mux", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm6368_mdiomux_ids);

अटल काष्ठा platक्रमm_driver bcm6368_mdiomux_driver = अणु
	.driver = अणु
		.name = "bcm6368-mdio-mux",
		.of_match_table = bcm6368_mdiomux_ids,
	पूर्ण,
	.probe	= bcm6368_mdiomux_probe,
	.हटाओ	= bcm6368_mdiomux_हटाओ,
पूर्ण;
module_platक्रमm_driver(bcm6368_mdiomux_driver);

MODULE_AUTHOR("थlvaro Fernथँndez Rojas <noltari@gmail.com>");
MODULE_DESCRIPTION("BCM6368 mdiomux bus controller driver");
MODULE_LICENSE("GPL v2");
