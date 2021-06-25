<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Copyright (C) 2019 IBM Corp. */

#समावेश <linux/bitfield.h>
#समावेश <linux/delay.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा DRV_NAME "mdio-aspeed"

#घोषणा ASPEED_MDIO_CTRL		0x0
#घोषणा   ASPEED_MDIO_CTRL_FIRE		BIT(31)
#घोषणा   ASPEED_MDIO_CTRL_ST		BIT(28)
#घोषणा     ASPEED_MDIO_CTRL_ST_C45	0
#घोषणा     ASPEED_MDIO_CTRL_ST_C22	1
#घोषणा   ASPEED_MDIO_CTRL_OP		GENMASK(27, 26)
#घोषणा     MDIO_C22_OP_WRITE		0b01
#घोषणा     MDIO_C22_OP_READ		0b10
#घोषणा   ASPEED_MDIO_CTRL_PHYAD	GENMASK(25, 21)
#घोषणा   ASPEED_MDIO_CTRL_REGAD	GENMASK(20, 16)
#घोषणा   ASPEED_MDIO_CTRL_MIIWDATA	GENMASK(15, 0)

#घोषणा ASPEED_MDIO_DATA		0x4
#घोषणा   ASPEED_MDIO_DATA_MDC_THRES	GENMASK(31, 24)
#घोषणा   ASPEED_MDIO_DATA_MDIO_EDGE	BIT(23)
#घोषणा   ASPEED_MDIO_DATA_MDIO_LATCH	GENMASK(22, 20)
#घोषणा   ASPEED_MDIO_DATA_IDLE		BIT(16)
#घोषणा   ASPEED_MDIO_DATA_MIIRDATA	GENMASK(15, 0)

#घोषणा ASPEED_MDIO_INTERVAL_US		100
#घोषणा ASPEED_MDIO_TIMEOUT_US		(ASPEED_MDIO_INTERVAL_US * 10)

काष्ठा aspeed_mdio अणु
	व्योम __iomem *base;
पूर्ण;

अटल पूर्णांक aspeed_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक addr, पूर्णांक regnum)
अणु
	काष्ठा aspeed_mdio *ctx = bus->priv;
	u32 ctrl;
	u32 data;
	पूर्णांक rc;

	dev_dbg(&bus->dev, "%s: addr: %d, regnum: %d\n", __func__, addr,
		regnum);

	/* Just clause 22 क्रम the moment */
	अगर (regnum & MII_ADDR_C45)
		वापस -EOPNOTSUPP;

	ctrl = ASPEED_MDIO_CTRL_FIRE
		| FIELD_PREP(ASPEED_MDIO_CTRL_ST, ASPEED_MDIO_CTRL_ST_C22)
		| FIELD_PREP(ASPEED_MDIO_CTRL_OP, MDIO_C22_OP_READ)
		| FIELD_PREP(ASPEED_MDIO_CTRL_PHYAD, addr)
		| FIELD_PREP(ASPEED_MDIO_CTRL_REGAD, regnum);

	ioग_लिखो32(ctrl, ctx->base + ASPEED_MDIO_CTRL);

	rc = पढ़ोl_poll_समयout(ctx->base + ASPEED_MDIO_DATA, data,
				data & ASPEED_MDIO_DATA_IDLE,
				ASPEED_MDIO_INTERVAL_US,
				ASPEED_MDIO_TIMEOUT_US);
	अगर (rc < 0)
		वापस rc;

	वापस FIELD_GET(ASPEED_MDIO_DATA_MIIRDATA, data);
पूर्ण

अटल पूर्णांक aspeed_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक addr, पूर्णांक regnum, u16 val)
अणु
	काष्ठा aspeed_mdio *ctx = bus->priv;
	u32 ctrl;

	dev_dbg(&bus->dev, "%s: addr: %d, regnum: %d, val: 0x%x\n",
		__func__, addr, regnum, val);

	/* Just clause 22 क्रम the moment */
	अगर (regnum & MII_ADDR_C45)
		वापस -EOPNOTSUPP;

	ctrl = ASPEED_MDIO_CTRL_FIRE
		| FIELD_PREP(ASPEED_MDIO_CTRL_ST, ASPEED_MDIO_CTRL_ST_C22)
		| FIELD_PREP(ASPEED_MDIO_CTRL_OP, MDIO_C22_OP_WRITE)
		| FIELD_PREP(ASPEED_MDIO_CTRL_PHYAD, addr)
		| FIELD_PREP(ASPEED_MDIO_CTRL_REGAD, regnum)
		| FIELD_PREP(ASPEED_MDIO_CTRL_MIIWDATA, val);

	ioग_लिखो32(ctrl, ctx->base + ASPEED_MDIO_CTRL);

	वापस पढ़ोl_poll_समयout(ctx->base + ASPEED_MDIO_CTRL, ctrl,
				  !(ctrl & ASPEED_MDIO_CTRL_FIRE),
				  ASPEED_MDIO_INTERVAL_US,
				  ASPEED_MDIO_TIMEOUT_US);
पूर्ण

अटल पूर्णांक aspeed_mdio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aspeed_mdio *ctx;
	काष्ठा mii_bus *bus;
	पूर्णांक rc;

	bus = devm_mdiobus_alloc_size(&pdev->dev, माप(*ctx));
	अगर (!bus)
		वापस -ENOMEM;

	ctx = bus->priv;
	ctx->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ctx->base))
		वापस PTR_ERR(ctx->base);

	bus->name = DRV_NAME;
	snम_लिखो(bus->id, MII_BUS_ID_SIZE, "%s%d", pdev->name, pdev->id);
	bus->parent = &pdev->dev;
	bus->पढ़ो = aspeed_mdio_पढ़ो;
	bus->ग_लिखो = aspeed_mdio_ग_लिखो;

	rc = of_mdiobus_रेजिस्टर(bus, pdev->dev.of_node);
	अगर (rc) अणु
		dev_err(&pdev->dev, "Cannot register MDIO bus!\n");
		वापस rc;
	पूर्ण

	platक्रमm_set_drvdata(pdev, bus);

	वापस 0;
पूर्ण

अटल पूर्णांक aspeed_mdio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	mdiobus_unरेजिस्टर(platक्रमm_get_drvdata(pdev));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id aspeed_mdio_of_match[] = अणु
	अणु .compatible = "aspeed,ast2600-mdio", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver aspeed_mdio_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = aspeed_mdio_of_match,
	पूर्ण,
	.probe = aspeed_mdio_probe,
	.हटाओ = aspeed_mdio_हटाओ,
पूर्ण;

module_platक्रमm_driver(aspeed_mdio_driver);

MODULE_AUTHOR("Andrew Jeffery <andrew@aj.id.au>");
MODULE_LICENSE("GPL");
