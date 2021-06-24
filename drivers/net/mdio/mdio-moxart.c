<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* MOXA ART Ethernet (RTL8201CP) MDIO पूर्णांकerface driver
 *
 * Copyright (C) 2013 Jonas Jensen <jonas.jensen@gmail.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा REG_PHY_CTRL            0
#घोषणा REG_PHY_WRITE_DATA      4

/* REG_PHY_CTRL */
#घोषणा MIIWR                   BIT(27) /* init ग_लिखो sequence (स्वतः cleared)*/
#घोषणा MIIRD                   BIT(26)
#घोषणा REGAD_MASK              0x3e00000
#घोषणा PHYAD_MASK              0x1f0000
#घोषणा MIIRDATA_MASK           0xffff

/* REG_PHY_WRITE_DATA */
#घोषणा MIIWDATA_MASK           0xffff

काष्ठा moxart_mdio_data अणु
	व्योम __iomem		*base;
पूर्ण;

अटल पूर्णांक moxart_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक mii_id, पूर्णांक regnum)
अणु
	काष्ठा moxart_mdio_data *data = bus->priv;
	u32 ctrl = 0;
	अचिन्हित पूर्णांक count = 5;

	dev_dbg(&bus->dev, "%s\n", __func__);

	ctrl |= MIIRD | ((mii_id << 16) & PHYAD_MASK) |
		((regnum << 21) & REGAD_MASK);

	ग_लिखोl(ctrl, data->base + REG_PHY_CTRL);

	करो अणु
		ctrl = पढ़ोl(data->base + REG_PHY_CTRL);

		अगर (!(ctrl & MIIRD))
			वापस ctrl & MIIRDATA_MASK;

		mdelay(10);
		count--;
	पूर्ण जबतक (count > 0);

	dev_dbg(&bus->dev, "%s timed out\n", __func__);

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक moxart_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक mii_id,
			     पूर्णांक regnum, u16 value)
अणु
	काष्ठा moxart_mdio_data *data = bus->priv;
	u32 ctrl = 0;
	अचिन्हित पूर्णांक count = 5;

	dev_dbg(&bus->dev, "%s\n", __func__);

	ctrl |= MIIWR | ((mii_id << 16) & PHYAD_MASK) |
		((regnum << 21) & REGAD_MASK);

	value &= MIIWDATA_MASK;

	ग_लिखोl(value, data->base + REG_PHY_WRITE_DATA);
	ग_लिखोl(ctrl, data->base + REG_PHY_CTRL);

	करो अणु
		ctrl = पढ़ोl(data->base + REG_PHY_CTRL);

		अगर (!(ctrl & MIIWR))
			वापस 0;

		mdelay(10);
		count--;
	पूर्ण जबतक (count > 0);

	dev_dbg(&bus->dev, "%s timed out\n", __func__);

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक moxart_mdio_reset(काष्ठा mii_bus *bus)
अणु
	पूर्णांक data, i;

	क्रम (i = 0; i < PHY_MAX_ADDR; i++) अणु
		data = moxart_mdio_पढ़ो(bus, i, MII_BMCR);
		अगर (data < 0)
			जारी;

		data |= BMCR_RESET;
		अगर (moxart_mdio_ग_लिखो(bus, i, MII_BMCR, data) < 0)
			जारी;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक moxart_mdio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा mii_bus *bus;
	काष्ठा moxart_mdio_data *data;
	पूर्णांक ret, i;

	bus = mdiobus_alloc_size(माप(*data));
	अगर (!bus)
		वापस -ENOMEM;

	bus->name = "MOXA ART Ethernet MII";
	bus->पढ़ो = &moxart_mdio_पढ़ो;
	bus->ग_लिखो = &moxart_mdio_ग_लिखो;
	bus->reset = &moxart_mdio_reset;
	snम_लिखो(bus->id, MII_BUS_ID_SIZE, "%s-%d-mii", pdev->name, pdev->id);
	bus->parent = &pdev->dev;

	/* Setting PHY_MAC_INTERRUPT here even अगर it has no effect,
	 * of_mdiobus_रेजिस्टर() sets these PHY_POLL.
	 * Ideally, the पूर्णांकerrupt from MAC controller could be used to
	 * detect link state changes, not polling, i.e. अगर there was
	 * a way phy_driver could set PHY_HAS_INTERRUPT but have that
	 * पूर्णांकerrupt handled in ethernet drivercode.
	 */
	क्रम (i = 0; i < PHY_MAX_ADDR; i++)
		bus->irq[i] = PHY_MAC_INTERRUPT;

	data = bus->priv;
	data->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(data->base)) अणु
		ret = PTR_ERR(data->base);
		जाओ err_out_मुक्त_mdiobus;
	पूर्ण

	ret = of_mdiobus_रेजिस्टर(bus, np);
	अगर (ret < 0)
		जाओ err_out_मुक्त_mdiobus;

	platक्रमm_set_drvdata(pdev, bus);

	वापस 0;

err_out_मुक्त_mdiobus:
	mdiobus_मुक्त(bus);
	वापस ret;
पूर्ण

अटल पूर्णांक moxart_mdio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mii_bus *bus = platक्रमm_get_drvdata(pdev);

	mdiobus_unरेजिस्टर(bus);
	mdiobus_मुक्त(bus);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id moxart_mdio_dt_ids[] = अणु
	अणु .compatible = "moxa,moxart-mdio" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, moxart_mdio_dt_ids);

अटल काष्ठा platक्रमm_driver moxart_mdio_driver = अणु
	.probe = moxart_mdio_probe,
	.हटाओ = moxart_mdio_हटाओ,
	.driver = अणु
		.name = "moxart-mdio",
		.of_match_table = moxart_mdio_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(moxart_mdio_driver);

MODULE_DESCRIPTION("MOXA ART MDIO interface driver");
MODULE_AUTHOR("Jonas Jensen <jonas.jensen@gmail.com>");
MODULE_LICENSE("GPL v2");
