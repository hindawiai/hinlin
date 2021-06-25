<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Hisilicon Fast Ethernet MDIO Bus Driver
 *
 * Copyright (c) 2016 HiSilicon Technologies Co., Ltd.
 */

#समावेश <linux/clk.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/platक्रमm_device.h>

#घोषणा MDIO_RWCTRL		0x00
#घोषणा MDIO_RO_DATA		0x04
#घोषणा MDIO_WRITE		BIT(13)
#घोषणा MDIO_RW_FINISH		BIT(15)
#घोषणा BIT_PHY_ADDR_OFFSET	8
#घोषणा BIT_WR_DATA_OFFSET	16

काष्ठा hisi_femac_mdio_data अणु
	काष्ठा clk *clk;
	व्योम __iomem *membase;
पूर्ण;

अटल पूर्णांक hisi_femac_mdio_रुको_पढ़ोy(काष्ठा hisi_femac_mdio_data *data)
अणु
	u32 val;

	वापस पढ़ोl_poll_समयout(data->membase + MDIO_RWCTRL,
				  val, val & MDIO_RW_FINISH, 20, 10000);
पूर्ण

अटल पूर्णांक hisi_femac_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक mii_id, पूर्णांक regnum)
अणु
	काष्ठा hisi_femac_mdio_data *data = bus->priv;
	पूर्णांक ret;

	ret = hisi_femac_mdio_रुको_पढ़ोy(data);
	अगर (ret)
		वापस ret;

	ग_लिखोl((mii_id << BIT_PHY_ADDR_OFFSET) | regnum,
	       data->membase + MDIO_RWCTRL);

	ret = hisi_femac_mdio_रुको_पढ़ोy(data);
	अगर (ret)
		वापस ret;

	वापस पढ़ोl(data->membase + MDIO_RO_DATA) & 0xFFFF;
पूर्ण

अटल पूर्णांक hisi_femac_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक mii_id, पूर्णांक regnum,
				 u16 value)
अणु
	काष्ठा hisi_femac_mdio_data *data = bus->priv;
	पूर्णांक ret;

	ret = hisi_femac_mdio_रुको_पढ़ोy(data);
	अगर (ret)
		वापस ret;

	ग_लिखोl(MDIO_WRITE | (value << BIT_WR_DATA_OFFSET) |
	       (mii_id << BIT_PHY_ADDR_OFFSET) | regnum,
	       data->membase + MDIO_RWCTRL);

	वापस hisi_femac_mdio_रुको_पढ़ोy(data);
पूर्ण

अटल पूर्णांक hisi_femac_mdio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा mii_bus *bus;
	काष्ठा hisi_femac_mdio_data *data;
	पूर्णांक ret;

	bus = mdiobus_alloc_size(माप(*data));
	अगर (!bus)
		वापस -ENOMEM;

	bus->name = "hisi_femac_mii_bus";
	bus->पढ़ो = &hisi_femac_mdio_पढ़ो;
	bus->ग_लिखो = &hisi_femac_mdio_ग_लिखो;
	snम_लिखो(bus->id, MII_BUS_ID_SIZE, "%s", pdev->name);
	bus->parent = &pdev->dev;

	data = bus->priv;
	data->membase = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(data->membase)) अणु
		ret = PTR_ERR(data->membase);
		जाओ err_out_मुक्त_mdiobus;
	पूर्ण

	data->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(data->clk)) अणु
		ret = PTR_ERR(data->clk);
		जाओ err_out_मुक्त_mdiobus;
	पूर्ण

	ret = clk_prepare_enable(data->clk);
	अगर (ret)
		जाओ err_out_मुक्त_mdiobus;

	ret = of_mdiobus_रेजिस्टर(bus, np);
	अगर (ret)
		जाओ err_out_disable_clk;

	platक्रमm_set_drvdata(pdev, bus);

	वापस 0;

err_out_disable_clk:
	clk_disable_unprepare(data->clk);
err_out_मुक्त_mdiobus:
	mdiobus_मुक्त(bus);
	वापस ret;
पूर्ण

अटल पूर्णांक hisi_femac_mdio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mii_bus *bus = platक्रमm_get_drvdata(pdev);
	काष्ठा hisi_femac_mdio_data *data = bus->priv;

	mdiobus_unरेजिस्टर(bus);
	clk_disable_unprepare(data->clk);
	mdiobus_मुक्त(bus);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id hisi_femac_mdio_dt_ids[] = अणु
	अणु .compatible = "hisilicon,hisi-femac-mdio" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, hisi_femac_mdio_dt_ids);

अटल काष्ठा platक्रमm_driver hisi_femac_mdio_driver = अणु
	.probe = hisi_femac_mdio_probe,
	.हटाओ = hisi_femac_mdio_हटाओ,
	.driver = अणु
		.name = "hisi-femac-mdio",
		.of_match_table = hisi_femac_mdio_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(hisi_femac_mdio_driver);

MODULE_DESCRIPTION("Hisilicon Fast Ethernet MAC MDIO interface driver");
MODULE_AUTHOR("Dongpo Li <lidongpo@hisilicon.com>");
MODULE_LICENSE("GPL");
