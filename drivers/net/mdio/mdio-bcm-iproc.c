<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015 Broadcom Corporation
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>

#घोषणा IPROC_GPHY_MDCDIV    0x1a

#घोषणा MII_CTRL_OFFSET      0x000

#घोषणा MII_CTRL_DIV_SHIFT   0
#घोषणा MII_CTRL_PRE_SHIFT   7
#घोषणा MII_CTRL_BUSY_SHIFT  8

#घोषणा MII_DATA_OFFSET      0x004
#घोषणा MII_DATA_MASK        0xffff
#घोषणा MII_DATA_TA_SHIFT    16
#घोषणा MII_DATA_TA_VAL      2
#घोषणा MII_DATA_RA_SHIFT    18
#घोषणा MII_DATA_PA_SHIFT    23
#घोषणा MII_DATA_OP_SHIFT    28
#घोषणा MII_DATA_OP_WRITE    1
#घोषणा MII_DATA_OP_READ     2
#घोषणा MII_DATA_SB_SHIFT    30

काष्ठा iproc_mdio_priv अणु
	काष्ठा mii_bus *mii_bus;
	व्योम __iomem *base;
पूर्ण;

अटल अंतरभूत पूर्णांक iproc_mdio_रुको_क्रम_idle(व्योम __iomem *base)
अणु
	u32 val;
	अचिन्हित पूर्णांक समयout = 1000; /* loop क्रम 1s */

	करो अणु
		val = पढ़ोl(base + MII_CTRL_OFFSET);
		अगर ((val & BIT(MII_CTRL_BUSY_SHIFT)) == 0)
			वापस 0;

		usleep_range(1000, 2000);
	पूर्ण जबतक (समयout--);

	वापस -ETIMEDOUT;
पूर्ण

अटल अंतरभूत व्योम iproc_mdio_config_clk(व्योम __iomem *base)
अणु
	u32 val;

	val = (IPROC_GPHY_MDCDIV << MII_CTRL_DIV_SHIFT) |
		  BIT(MII_CTRL_PRE_SHIFT);
	ग_लिखोl(val, base + MII_CTRL_OFFSET);
पूर्ण

अटल पूर्णांक iproc_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक reg)
अणु
	काष्ठा iproc_mdio_priv *priv = bus->priv;
	u32 cmd;
	पूर्णांक rc;

	rc = iproc_mdio_रुको_क्रम_idle(priv->base);
	अगर (rc)
		वापस rc;

	/* Prepare the पढ़ो operation */
	cmd = (MII_DATA_TA_VAL << MII_DATA_TA_SHIFT) |
		(reg << MII_DATA_RA_SHIFT) |
		(phy_id << MII_DATA_PA_SHIFT) |
		BIT(MII_DATA_SB_SHIFT) |
		(MII_DATA_OP_READ << MII_DATA_OP_SHIFT);

	ग_लिखोl(cmd, priv->base + MII_DATA_OFFSET);

	rc = iproc_mdio_रुको_क्रम_idle(priv->base);
	अगर (rc)
		वापस rc;

	cmd = पढ़ोl(priv->base + MII_DATA_OFFSET) & MII_DATA_MASK;

	वापस cmd;
पूर्ण

अटल पूर्णांक iproc_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_id,
			    पूर्णांक reg, u16 val)
अणु
	काष्ठा iproc_mdio_priv *priv = bus->priv;
	u32 cmd;
	पूर्णांक rc;

	rc = iproc_mdio_रुको_क्रम_idle(priv->base);
	अगर (rc)
		वापस rc;

	/* Prepare the ग_लिखो operation */
	cmd = (MII_DATA_TA_VAL << MII_DATA_TA_SHIFT) |
		(reg << MII_DATA_RA_SHIFT) |
		(phy_id << MII_DATA_PA_SHIFT) |
		BIT(MII_DATA_SB_SHIFT) |
		(MII_DATA_OP_WRITE << MII_DATA_OP_SHIFT) |
		((u32)(val) & MII_DATA_MASK);

	ग_लिखोl(cmd, priv->base + MII_DATA_OFFSET);

	rc = iproc_mdio_रुको_क्रम_idle(priv->base);
	अगर (rc)
		वापस rc;

	वापस 0;
पूर्ण

अटल पूर्णांक iproc_mdio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iproc_mdio_priv *priv;
	काष्ठा mii_bus *bus;
	पूर्णांक rc;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base)) अणु
		dev_err(&pdev->dev, "failed to ioremap register\n");
		वापस PTR_ERR(priv->base);
	पूर्ण

	priv->mii_bus = mdiobus_alloc();
	अगर (!priv->mii_bus) अणु
		dev_err(&pdev->dev, "MDIO bus alloc failed\n");
		वापस -ENOMEM;
	पूर्ण

	bus = priv->mii_bus;
	bus->priv = priv;
	bus->name = "iProc MDIO bus";
	snम_लिखो(bus->id, MII_BUS_ID_SIZE, "%s-%d", pdev->name, pdev->id);
	bus->parent = &pdev->dev;
	bus->पढ़ो = iproc_mdio_पढ़ो;
	bus->ग_लिखो = iproc_mdio_ग_लिखो;

	iproc_mdio_config_clk(priv->base);

	rc = of_mdiobus_रेजिस्टर(bus, pdev->dev.of_node);
	अगर (rc) अणु
		dev_err(&pdev->dev, "MDIO bus registration failed\n");
		जाओ err_iproc_mdio;
	पूर्ण

	platक्रमm_set_drvdata(pdev, priv);

	dev_info(&pdev->dev, "Broadcom iProc MDIO bus registered\n");

	वापस 0;

err_iproc_mdio:
	mdiobus_मुक्त(bus);
	वापस rc;
पूर्ण

अटल पूर्णांक iproc_mdio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iproc_mdio_priv *priv = platक्रमm_get_drvdata(pdev);

	mdiobus_unरेजिस्टर(priv->mii_bus);
	mdiobus_मुक्त(priv->mii_bus);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक iproc_mdio_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा iproc_mdio_priv *priv = platक्रमm_get_drvdata(pdev);

	/* restore the mii घड़ी configuration */
	iproc_mdio_config_clk(priv->base);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops iproc_mdio_pm_ops = अणु
	.resume = iproc_mdio_resume
पूर्ण;
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा of_device_id iproc_mdio_of_match[] = अणु
	अणु .compatible = "brcm,iproc-mdio", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, iproc_mdio_of_match);

अटल काष्ठा platक्रमm_driver iproc_mdio_driver = अणु
	.driver = अणु
		.name = "iproc-mdio",
		.of_match_table = iproc_mdio_of_match,
#अगर_घोषित CONFIG_PM_SLEEP
		.pm = &iproc_mdio_pm_ops,
#पूर्ण_अगर
	पूर्ण,
	.probe = iproc_mdio_probe,
	.हटाओ = iproc_mdio_हटाओ,
पूर्ण;

module_platक्रमm_driver(iproc_mdio_driver);

MODULE_AUTHOR("Broadcom Corporation");
MODULE_DESCRIPTION("Broadcom iProc MDIO bus controller");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:iproc-mdio");
