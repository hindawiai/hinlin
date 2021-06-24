<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Qualcomm IPQ8064 MDIO पूर्णांकerface driver
 *
 * Copyright (C) 2019 Christian Lamparter <chunkeey@gmail.com>
 * Copyright (C) 2020 Ansuel Smith <ansuelsmth@gmail.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

/* MII address रेजिस्टर definitions */
#घोषणा MII_ADDR_REG_ADDR                       0x10
#घोषणा MII_BUSY                                BIT(0)
#घोषणा MII_WRITE                               BIT(1)
#घोषणा MII_CLKRANGE_60_100M                    (0 << 2)
#घोषणा MII_CLKRANGE_100_150M                   (1 << 2)
#घोषणा MII_CLKRANGE_20_35M                     (2 << 2)
#घोषणा MII_CLKRANGE_35_60M                     (3 << 2)
#घोषणा MII_CLKRANGE_150_250M                   (4 << 2)
#घोषणा MII_CLKRANGE_250_300M                   (5 << 2)
#घोषणा MII_CLKRANGE_MASK			GENMASK(4, 2)
#घोषणा MII_REG_SHIFT				6
#घोषणा MII_REG_MASK				GENMASK(10, 6)
#घोषणा MII_ADDR_SHIFT				11
#घोषणा MII_ADDR_MASK				GENMASK(15, 11)

#घोषणा MII_DATA_REG_ADDR                       0x14

#घोषणा MII_MDIO_DELAY_USEC                     (1000)
#घोषणा MII_MDIO_RETRY_MSEC                     (10)

काष्ठा ipq8064_mdio अणु
	काष्ठा regmap *base; /* NSS_GMAC0_BASE */
पूर्ण;

अटल पूर्णांक
ipq8064_mdio_रुको_busy(काष्ठा ipq8064_mdio *priv)
अणु
	u32 busy;

	वापस regmap_पढ़ो_poll_समयout(priv->base, MII_ADDR_REG_ADDR, busy,
					!(busy & MII_BUSY), MII_MDIO_DELAY_USEC,
					MII_MDIO_RETRY_MSEC * USEC_PER_MSEC);
पूर्ण

अटल पूर्णांक
ipq8064_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_addr, पूर्णांक reg_offset)
अणु
	u32 miiaddr = MII_BUSY | MII_CLKRANGE_250_300M;
	काष्ठा ipq8064_mdio *priv = bus->priv;
	u32 ret_val;
	पूर्णांक err;

	/* Reject clause 45 */
	अगर (reg_offset & MII_ADDR_C45)
		वापस -EOPNOTSUPP;

	miiaddr |= ((phy_addr << MII_ADDR_SHIFT) & MII_ADDR_MASK) |
		   ((reg_offset << MII_REG_SHIFT) & MII_REG_MASK);

	regmap_ग_लिखो(priv->base, MII_ADDR_REG_ADDR, miiaddr);
	usleep_range(8, 10);

	err = ipq8064_mdio_रुको_busy(priv);
	अगर (err)
		वापस err;

	regmap_पढ़ो(priv->base, MII_DATA_REG_ADDR, &ret_val);
	वापस (पूर्णांक)ret_val;
पूर्ण

अटल पूर्णांक
ipq8064_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_addr, पूर्णांक reg_offset, u16 data)
अणु
	u32 miiaddr = MII_WRITE | MII_BUSY | MII_CLKRANGE_250_300M;
	काष्ठा ipq8064_mdio *priv = bus->priv;

	/* Reject clause 45 */
	अगर (reg_offset & MII_ADDR_C45)
		वापस -EOPNOTSUPP;

	regmap_ग_लिखो(priv->base, MII_DATA_REG_ADDR, data);

	miiaddr |= ((phy_addr << MII_ADDR_SHIFT) & MII_ADDR_MASK) |
		   ((reg_offset << MII_REG_SHIFT) & MII_REG_MASK);

	regmap_ग_लिखो(priv->base, MII_ADDR_REG_ADDR, miiaddr);
	usleep_range(8, 10);

	वापस ipq8064_mdio_रुको_busy(priv);
पूर्ण

अटल पूर्णांक
ipq8064_mdio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा ipq8064_mdio *priv;
	काष्ठा mii_bus *bus;
	पूर्णांक ret;

	bus = devm_mdiobus_alloc_size(&pdev->dev, माप(*priv));
	अगर (!bus)
		वापस -ENOMEM;

	bus->name = "ipq8064_mdio_bus";
	bus->पढ़ो = ipq8064_mdio_पढ़ो;
	bus->ग_लिखो = ipq8064_mdio_ग_लिखो;
	snम_लिखो(bus->id, MII_BUS_ID_SIZE, "%s-mii", dev_name(&pdev->dev));
	bus->parent = &pdev->dev;

	priv = bus->priv;
	priv->base = device_node_to_regmap(np);
	अगर (IS_ERR(priv->base)) अणु
		अगर (priv->base == ERR_PTR(-EPROBE_DEFER))
			वापस -EPROBE_DEFER;

		dev_err(&pdev->dev, "error getting device regmap, error=%pe\n",
			priv->base);
		वापस PTR_ERR(priv->base);
	पूर्ण

	ret = of_mdiobus_रेजिस्टर(bus, np);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, bus);
	वापस 0;
पूर्ण

अटल पूर्णांक
ipq8064_mdio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mii_bus *bus = platक्रमm_get_drvdata(pdev);

	mdiobus_unरेजिस्टर(bus);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ipq8064_mdio_dt_ids[] = अणु
	अणु .compatible = "qcom,ipq8064-mdio" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ipq8064_mdio_dt_ids);

अटल काष्ठा platक्रमm_driver ipq8064_mdio_driver = अणु
	.probe = ipq8064_mdio_probe,
	.हटाओ = ipq8064_mdio_हटाओ,
	.driver = अणु
		.name = "ipq8064-mdio",
		.of_match_table = ipq8064_mdio_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ipq8064_mdio_driver);

MODULE_DESCRIPTION("Qualcomm IPQ8064 MDIO interface driver");
MODULE_AUTHOR("Christian Lamparter <chunkeey@gmail.com>");
MODULE_AUTHOR("Ansuel Smith <ansuelsmth@gmail.com>");
MODULE_LICENSE("GPL");
