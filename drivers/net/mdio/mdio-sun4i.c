<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Allwinner EMAC MDIO पूर्णांकerface driver
 *
 * Copyright 2012-2013 Stefan Roese <sr@denx.de>
 * Copyright 2013 Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 *
 * Based on the Linux driver provided by Allwinner:
 * Copyright (C) 1997  Sten Wang
 */

#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>

#घोषणा EMAC_MAC_MCMD_REG	(0x00)
#घोषणा EMAC_MAC_MADR_REG	(0x04)
#घोषणा EMAC_MAC_MWTD_REG	(0x08)
#घोषणा EMAC_MAC_MRDD_REG	(0x0c)
#घोषणा EMAC_MAC_MIND_REG	(0x10)
#घोषणा EMAC_MAC_SSRR_REG	(0x14)

#घोषणा MDIO_TIMEOUT		(msecs_to_jअगरfies(100))

काष्ठा sun4i_mdio_data अणु
	व्योम __iomem		*membase;
	काष्ठा regulator	*regulator;
पूर्ण;

अटल पूर्णांक sun4i_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक mii_id, पूर्णांक regnum)
अणु
	काष्ठा sun4i_mdio_data *data = bus->priv;
	अचिन्हित दीर्घ समयout_jअगरfies;
	पूर्णांक value;

	/* issue the phy address and reg */
	ग_लिखोl((mii_id << 8) | regnum, data->membase + EMAC_MAC_MADR_REG);
	/* pull up the phy io line */
	ग_लिखोl(0x1, data->membase + EMAC_MAC_MCMD_REG);

	/* Wait पढ़ो complete */
	समयout_jअगरfies = jअगरfies + MDIO_TIMEOUT;
	जबतक (पढ़ोl(data->membase + EMAC_MAC_MIND_REG) & 0x1) अणु
		अगर (समय_is_beक्रमe_jअगरfies(समयout_jअगरfies))
			वापस -ETIMEDOUT;
		msleep(1);
	पूर्ण

	/* push करोwn the phy io line */
	ग_लिखोl(0x0, data->membase + EMAC_MAC_MCMD_REG);
	/* and पढ़ो data */
	value = पढ़ोl(data->membase + EMAC_MAC_MRDD_REG);

	वापस value;
पूर्ण

अटल पूर्णांक sun4i_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक mii_id, पूर्णांक regnum,
			    u16 value)
अणु
	काष्ठा sun4i_mdio_data *data = bus->priv;
	अचिन्हित दीर्घ समयout_jअगरfies;

	/* issue the phy address and reg */
	ग_लिखोl((mii_id << 8) | regnum, data->membase + EMAC_MAC_MADR_REG);
	/* pull up the phy io line */
	ग_लिखोl(0x1, data->membase + EMAC_MAC_MCMD_REG);

	/* Wait पढ़ो complete */
	समयout_jअगरfies = jअगरfies + MDIO_TIMEOUT;
	जबतक (पढ़ोl(data->membase + EMAC_MAC_MIND_REG) & 0x1) अणु
		अगर (समय_is_beक्रमe_jअगरfies(समयout_jअगरfies))
			वापस -ETIMEDOUT;
		msleep(1);
	पूर्ण

	/* push करोwn the phy io line */
	ग_लिखोl(0x0, data->membase + EMAC_MAC_MCMD_REG);
	/* and ग_लिखो data */
	ग_लिखोl(value, data->membase + EMAC_MAC_MWTD_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_mdio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा mii_bus *bus;
	काष्ठा sun4i_mdio_data *data;
	पूर्णांक ret;

	bus = mdiobus_alloc_size(माप(*data));
	अगर (!bus)
		वापस -ENOMEM;

	bus->name = "sun4i_mii_bus";
	bus->पढ़ो = &sun4i_mdio_पढ़ो;
	bus->ग_लिखो = &sun4i_mdio_ग_लिखो;
	snम_लिखो(bus->id, MII_BUS_ID_SIZE, "%s-mii", dev_name(&pdev->dev));
	bus->parent = &pdev->dev;

	data = bus->priv;
	data->membase = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(data->membase)) अणु
		ret = PTR_ERR(data->membase);
		जाओ err_out_मुक्त_mdiobus;
	पूर्ण

	data->regulator = devm_regulator_get(&pdev->dev, "phy");
	अगर (IS_ERR(data->regulator)) अणु
		अगर (PTR_ERR(data->regulator) == -EPROBE_DEFER) अणु
			ret = -EPROBE_DEFER;
			जाओ err_out_मुक्त_mdiobus;
		पूर्ण

		dev_info(&pdev->dev, "no regulator found\n");
		data->regulator = शून्य;
	पूर्ण अन्यथा अणु
		ret = regulator_enable(data->regulator);
		अगर (ret)
			जाओ err_out_मुक्त_mdiobus;
	पूर्ण

	ret = of_mdiobus_रेजिस्टर(bus, np);
	अगर (ret < 0)
		जाओ err_out_disable_regulator;

	platक्रमm_set_drvdata(pdev, bus);

	वापस 0;

err_out_disable_regulator:
	अगर (data->regulator)
		regulator_disable(data->regulator);
err_out_मुक्त_mdiobus:
	mdiobus_मुक्त(bus);
	वापस ret;
पूर्ण

अटल पूर्णांक sun4i_mdio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mii_bus *bus = platक्रमm_get_drvdata(pdev);
	काष्ठा sun4i_mdio_data *data = bus->priv;

	mdiobus_unरेजिस्टर(bus);
	अगर (data->regulator)
		regulator_disable(data->regulator);
	mdiobus_मुक्त(bus);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sun4i_mdio_dt_ids[] = अणु
	अणु .compatible = "allwinner,sun4i-a10-mdio" पूर्ण,

	/* Deprecated */
	अणु .compatible = "allwinner,sun4i-mdio" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sun4i_mdio_dt_ids);

अटल काष्ठा platक्रमm_driver sun4i_mdio_driver = अणु
	.probe = sun4i_mdio_probe,
	.हटाओ = sun4i_mdio_हटाओ,
	.driver = अणु
		.name = "sun4i-mdio",
		.of_match_table = sun4i_mdio_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sun4i_mdio_driver);

MODULE_DESCRIPTION("Allwinner EMAC MDIO interface driver");
MODULE_AUTHOR("Maxime Ripard <maxime.ripard@free-electrons.com>");
MODULE_LICENSE("GPL v2");
