<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/* Copyright (c) 2015, The Linux Foundation. All rights reserved. */
/* Copyright (c) 2020 Sartura Ltd. */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा MDIO_MODE_REG				0x40
#घोषणा MDIO_ADDR_REG				0x44
#घोषणा MDIO_DATA_WRITE_REG			0x48
#घोषणा MDIO_DATA_READ_REG			0x4c
#घोषणा MDIO_CMD_REG				0x50
#घोषणा MDIO_CMD_ACCESS_BUSY		BIT(16)
#घोषणा MDIO_CMD_ACCESS_START		BIT(8)
#घोषणा MDIO_CMD_ACCESS_CODE_READ	0
#घोषणा MDIO_CMD_ACCESS_CODE_WRITE	1
#घोषणा MDIO_CMD_ACCESS_CODE_C45_ADDR	0
#घोषणा MDIO_CMD_ACCESS_CODE_C45_WRITE	1
#घोषणा MDIO_CMD_ACCESS_CODE_C45_READ	2

/* 0 = Clause 22, 1 = Clause 45 */
#घोषणा MDIO_MODE_C45				BIT(8)

#घोषणा IPQ4019_MDIO_TIMEOUT	10000
#घोषणा IPQ4019_MDIO_SLEEP		10

काष्ठा ipq4019_mdio_data अणु
	व्योम __iomem	*membase;
पूर्ण;

अटल पूर्णांक ipq4019_mdio_रुको_busy(काष्ठा mii_bus *bus)
अणु
	काष्ठा ipq4019_mdio_data *priv = bus->priv;
	अचिन्हित पूर्णांक busy;

	वापस पढ़ोl_poll_समयout(priv->membase + MDIO_CMD_REG, busy,
				  (busy & MDIO_CMD_ACCESS_BUSY) == 0,
				  IPQ4019_MDIO_SLEEP, IPQ4019_MDIO_TIMEOUT);
पूर्ण

अटल पूर्णांक ipq4019_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक mii_id, पूर्णांक regnum)
अणु
	काष्ठा ipq4019_mdio_data *priv = bus->priv;
	अचिन्हित पूर्णांक data;
	अचिन्हित पूर्णांक cmd;

	अगर (ipq4019_mdio_रुको_busy(bus))
		वापस -ETIMEDOUT;

	/* Clause 45 support */
	अगर (regnum & MII_ADDR_C45) अणु
		अचिन्हित पूर्णांक mmd = (regnum >> 16) & 0x1F;
		अचिन्हित पूर्णांक reg = regnum & 0xFFFF;

		/* Enter Clause 45 mode */
		data = पढ़ोl(priv->membase + MDIO_MODE_REG);

		data |= MDIO_MODE_C45;

		ग_लिखोl(data, priv->membase + MDIO_MODE_REG);

		/* issue the phy address and mmd */
		ग_लिखोl((mii_id << 8) | mmd, priv->membase + MDIO_ADDR_REG);

		/* issue reg */
		ग_लिखोl(reg, priv->membase + MDIO_DATA_WRITE_REG);

		cmd = MDIO_CMD_ACCESS_START | MDIO_CMD_ACCESS_CODE_C45_ADDR;
	पूर्ण अन्यथा अणु
		/* Enter Clause 22 mode */
		data = पढ़ोl(priv->membase + MDIO_MODE_REG);

		data &= ~MDIO_MODE_C45;

		ग_लिखोl(data, priv->membase + MDIO_MODE_REG);

		/* issue the phy address and reg */
		ग_लिखोl((mii_id << 8) | regnum, priv->membase + MDIO_ADDR_REG);

		cmd = MDIO_CMD_ACCESS_START | MDIO_CMD_ACCESS_CODE_READ;
	पूर्ण

	/* issue पढ़ो command */
	ग_लिखोl(cmd, priv->membase + MDIO_CMD_REG);

	/* Wait पढ़ो complete */
	अगर (ipq4019_mdio_रुको_busy(bus))
		वापस -ETIMEDOUT;

	अगर (regnum & MII_ADDR_C45) अणु
		cmd = MDIO_CMD_ACCESS_START | MDIO_CMD_ACCESS_CODE_C45_READ;

		ग_लिखोl(cmd, priv->membase + MDIO_CMD_REG);

		अगर (ipq4019_mdio_रुको_busy(bus))
			वापस -ETIMEDOUT;
	पूर्ण

	/* Read and वापस data */
	वापस पढ़ोl(priv->membase + MDIO_DATA_READ_REG);
पूर्ण

अटल पूर्णांक ipq4019_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक mii_id, पूर्णांक regnum,
							 u16 value)
अणु
	काष्ठा ipq4019_mdio_data *priv = bus->priv;
	अचिन्हित पूर्णांक data;
	अचिन्हित पूर्णांक cmd;

	अगर (ipq4019_mdio_रुको_busy(bus))
		वापस -ETIMEDOUT;

	/* Clause 45 support */
	अगर (regnum & MII_ADDR_C45) अणु
		अचिन्हित पूर्णांक mmd = (regnum >> 16) & 0x1F;
		अचिन्हित पूर्णांक reg = regnum & 0xFFFF;

		/* Enter Clause 45 mode */
		data = पढ़ोl(priv->membase + MDIO_MODE_REG);

		data |= MDIO_MODE_C45;

		ग_लिखोl(data, priv->membase + MDIO_MODE_REG);

		/* issue the phy address and mmd */
		ग_लिखोl((mii_id << 8) | mmd, priv->membase + MDIO_ADDR_REG);

		/* issue reg */
		ग_लिखोl(reg, priv->membase + MDIO_DATA_WRITE_REG);

		cmd = MDIO_CMD_ACCESS_START | MDIO_CMD_ACCESS_CODE_C45_ADDR;

		ग_लिखोl(cmd, priv->membase + MDIO_CMD_REG);

		अगर (ipq4019_mdio_रुको_busy(bus))
			वापस -ETIMEDOUT;
	पूर्ण अन्यथा अणु
		/* Enter Clause 22 mode */
		data = पढ़ोl(priv->membase + MDIO_MODE_REG);

		data &= ~MDIO_MODE_C45;

		ग_लिखोl(data, priv->membase + MDIO_MODE_REG);

		/* issue the phy address and reg */
		ग_लिखोl((mii_id << 8) | regnum, priv->membase + MDIO_ADDR_REG);
	पूर्ण

	/* issue ग_लिखो data */
	ग_लिखोl(value, priv->membase + MDIO_DATA_WRITE_REG);

	/* issue ग_लिखो command */
	अगर (regnum & MII_ADDR_C45)
		cmd = MDIO_CMD_ACCESS_START | MDIO_CMD_ACCESS_CODE_C45_WRITE;
	अन्यथा
		cmd = MDIO_CMD_ACCESS_START | MDIO_CMD_ACCESS_CODE_WRITE;

	ग_लिखोl(cmd, priv->membase + MDIO_CMD_REG);

	/* Wait ग_लिखो complete */
	अगर (ipq4019_mdio_रुको_busy(bus))
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक ipq4019_mdio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ipq4019_mdio_data *priv;
	काष्ठा mii_bus *bus;
	पूर्णांक ret;

	bus = devm_mdiobus_alloc_size(&pdev->dev, माप(*priv));
	अगर (!bus)
		वापस -ENOMEM;

	priv = bus->priv;

	priv->membase = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->membase))
		वापस PTR_ERR(priv->membase);

	bus->name = "ipq4019_mdio";
	bus->पढ़ो = ipq4019_mdio_पढ़ो;
	bus->ग_लिखो = ipq4019_mdio_ग_लिखो;
	bus->parent = &pdev->dev;
	snम_लिखो(bus->id, MII_BUS_ID_SIZE, "%s%d", pdev->name, pdev->id);

	ret = of_mdiobus_रेजिस्टर(bus, pdev->dev.of_node);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Cannot register MDIO bus!\n");
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, bus);

	वापस 0;
पूर्ण

अटल पूर्णांक ipq4019_mdio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mii_bus *bus = platक्रमm_get_drvdata(pdev);

	mdiobus_unरेजिस्टर(bus);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ipq4019_mdio_dt_ids[] = अणु
	अणु .compatible = "qcom,ipq4019-mdio" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ipq4019_mdio_dt_ids);

अटल काष्ठा platक्रमm_driver ipq4019_mdio_driver = अणु
	.probe = ipq4019_mdio_probe,
	.हटाओ = ipq4019_mdio_हटाओ,
	.driver = अणु
		.name = "ipq4019-mdio",
		.of_match_table = ipq4019_mdio_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ipq4019_mdio_driver);

MODULE_DESCRIPTION("ipq4019 MDIO interface driver");
MODULE_AUTHOR("Qualcomm Atheros");
MODULE_LICENSE("Dual BSD/GPL");
