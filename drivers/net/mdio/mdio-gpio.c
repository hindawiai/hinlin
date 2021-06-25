<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * GPIO based MDIO bitbang driver.
 * Supports OpenFirmware.
 *
 * Copyright (c) 2008 CSE Semaphore Belgium.
 *  by Laurent Pinअक्षरt <laurentp@cse-semaphore.com>
 *
 * Copyright (C) 2008, Paulius Zaleckas <paulius.zaleckas@teltonika.lt>
 *
 * Based on earlier work by
 *
 * Copyright (c) 2003 Intracom S.A.
 *  by Pantelis Antoniou <panto@पूर्णांकracom.gr>
 *
 * 2005 (c) MontaVista Software, Inc.
 * Vitaly Bordug <vbordug@ru.mvista.com>
 */

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mdio-bitbang.h>
#समावेश <linux/mdio-gpपन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/platक्रमm_data/mdio-gpपन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

काष्ठा mdio_gpio_info अणु
	काष्ठा mdiobb_ctrl ctrl;
	काष्ठा gpio_desc *mdc, *mdio, *mकरो;
पूर्ण;

अटल पूर्णांक mdio_gpio_get_data(काष्ठा device *dev,
			      काष्ठा mdio_gpio_info *bitbang)
अणु
	bitbang->mdc = devm_gpiod_get_index(dev, शून्य, MDIO_GPIO_MDC,
					    GPIOD_OUT_LOW);
	अगर (IS_ERR(bitbang->mdc))
		वापस PTR_ERR(bitbang->mdc);

	bitbang->mdio = devm_gpiod_get_index(dev, शून्य, MDIO_GPIO_MDIO,
					     GPIOD_IN);
	अगर (IS_ERR(bitbang->mdio))
		वापस PTR_ERR(bitbang->mdio);

	bitbang->mकरो = devm_gpiod_get_index_optional(dev, शून्य, MDIO_GPIO_MDO,
						     GPIOD_OUT_LOW);
	वापस PTR_ERR_OR_ZERO(bitbang->mकरो);
पूर्ण

अटल व्योम mdio_dir(काष्ठा mdiobb_ctrl *ctrl, पूर्णांक dir)
अणु
	काष्ठा mdio_gpio_info *bitbang =
		container_of(ctrl, काष्ठा mdio_gpio_info, ctrl);

	अगर (bitbang->mकरो) अणु
		/* Separate output pin. Always set its value to high
		 * when changing direction. If direction is input,
		 * assume the pin serves as pull-up. If direction is
		 * output, the शेष value is high.
		 */
		gpiod_set_value_cansleep(bitbang->mकरो, 1);
		वापस;
	पूर्ण

	अगर (dir)
		gpiod_direction_output(bitbang->mdio, 1);
	अन्यथा
		gpiod_direction_input(bitbang->mdio);
पूर्ण

अटल पूर्णांक mdio_get(काष्ठा mdiobb_ctrl *ctrl)
अणु
	काष्ठा mdio_gpio_info *bitbang =
		container_of(ctrl, काष्ठा mdio_gpio_info, ctrl);

	वापस gpiod_get_value_cansleep(bitbang->mdio);
पूर्ण

अटल व्योम mdio_set(काष्ठा mdiobb_ctrl *ctrl, पूर्णांक what)
अणु
	काष्ठा mdio_gpio_info *bitbang =
		container_of(ctrl, काष्ठा mdio_gpio_info, ctrl);

	अगर (bitbang->mकरो)
		gpiod_set_value_cansleep(bitbang->mकरो, what);
	अन्यथा
		gpiod_set_value_cansleep(bitbang->mdio, what);
पूर्ण

अटल व्योम mdc_set(काष्ठा mdiobb_ctrl *ctrl, पूर्णांक what)
अणु
	काष्ठा mdio_gpio_info *bitbang =
		container_of(ctrl, काष्ठा mdio_gpio_info, ctrl);

	gpiod_set_value_cansleep(bitbang->mdc, what);
पूर्ण

अटल स्थिर काष्ठा mdiobb_ops mdio_gpio_ops = अणु
	.owner = THIS_MODULE,
	.set_mdc = mdc_set,
	.set_mdio_dir = mdio_dir,
	.set_mdio_data = mdio_set,
	.get_mdio_data = mdio_get,
पूर्ण;

अटल काष्ठा mii_bus *mdio_gpio_bus_init(काष्ठा device *dev,
					  काष्ठा mdio_gpio_info *bitbang,
					  पूर्णांक bus_id)
अणु
	काष्ठा mdio_gpio_platक्रमm_data *pdata = dev_get_platdata(dev);
	काष्ठा mii_bus *new_bus;

	bitbang->ctrl.ops = &mdio_gpio_ops;

	new_bus = alloc_mdio_bitbang(&bitbang->ctrl);
	अगर (!new_bus)
		वापस शून्य;

	new_bus->name = "GPIO Bitbanged MDIO";
	new_bus->parent = dev;

	अगर (bus_id != -1)
		snम_लिखो(new_bus->id, MII_BUS_ID_SIZE, "gpio-%x", bus_id);
	अन्यथा
		म_नकलन(new_bus->id, "gpio", MII_BUS_ID_SIZE);

	अगर (pdata) अणु
		new_bus->phy_mask = pdata->phy_mask;
		new_bus->phy_ignore_ta_mask = pdata->phy_ignore_ta_mask;
	पूर्ण

	अगर (dev->of_node &&
	    of_device_is_compatible(dev->of_node, "microchip,mdio-smi0")) अणु
		bitbang->ctrl.op_c22_पढ़ो = 0;
		bitbang->ctrl.op_c22_ग_लिखो = 0;
		bitbang->ctrl.override_op_c22 = 1;
	पूर्ण

	dev_set_drvdata(dev, new_bus);

	वापस new_bus;
पूर्ण

अटल व्योम mdio_gpio_bus_deinit(काष्ठा device *dev)
अणु
	काष्ठा mii_bus *bus = dev_get_drvdata(dev);

	मुक्त_mdio_bitbang(bus);
पूर्ण

अटल व्योम mdio_gpio_bus_destroy(काष्ठा device *dev)
अणु
	काष्ठा mii_bus *bus = dev_get_drvdata(dev);

	mdiobus_unरेजिस्टर(bus);
	mdio_gpio_bus_deinit(dev);
पूर्ण

अटल पूर्णांक mdio_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mdio_gpio_info *bitbang;
	काष्ठा mii_bus *new_bus;
	पूर्णांक ret, bus_id;

	bitbang = devm_kzalloc(&pdev->dev, माप(*bitbang), GFP_KERNEL);
	अगर (!bitbang)
		वापस -ENOMEM;

	ret = mdio_gpio_get_data(&pdev->dev, bitbang);
	अगर (ret)
		वापस ret;

	अगर (pdev->dev.of_node) अणु
		bus_id = of_alias_get_id(pdev->dev.of_node, "mdio-gpio");
		अगर (bus_id < 0) अणु
			dev_warn(&pdev->dev, "failed to get alias id\n");
			bus_id = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		bus_id = pdev->id;
	पूर्ण

	new_bus = mdio_gpio_bus_init(&pdev->dev, bitbang, bus_id);
	अगर (!new_bus)
		वापस -ENODEV;

	ret = of_mdiobus_रेजिस्टर(new_bus, pdev->dev.of_node);
	अगर (ret)
		mdio_gpio_bus_deinit(&pdev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक mdio_gpio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	mdio_gpio_bus_destroy(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mdio_gpio_of_match[] = अणु
	अणु .compatible = "virtual,mdio-gpio", पूर्ण,
	अणु .compatible = "microchip,mdio-smi0" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mdio_gpio_of_match);

अटल काष्ठा platक्रमm_driver mdio_gpio_driver = अणु
	.probe = mdio_gpio_probe,
	.हटाओ = mdio_gpio_हटाओ,
	.driver		= अणु
		.name	= "mdio-gpio",
		.of_match_table = mdio_gpio_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mdio_gpio_driver);

MODULE_ALIAS("platform:mdio-gpio");
MODULE_AUTHOR("Laurent Pinchart, Paulius Zaleckas");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Generic driver for MDIO bus emulation using GPIO");
