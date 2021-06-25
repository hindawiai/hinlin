<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2009-2015 Cavium, Inc.
 */

#समावेश <linux/gfp.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "mdio-cavium.h"

अटल पूर्णांक octeon_mdiobus_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cavium_mdiobus *bus;
	काष्ठा mii_bus *mii_bus;
	काष्ठा resource *res_mem;
	resource_माप_प्रकार mdio_phys;
	resource_माप_प्रकार regsize;
	जोड़ cvmx_smix_en smi_en;
	पूर्णांक err = -ENOENT;

	mii_bus = devm_mdiobus_alloc_size(&pdev->dev, माप(*bus));
	अगर (!mii_bus)
		वापस -ENOMEM;

	res_mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (res_mem == शून्य) अणु
		dev_err(&pdev->dev, "found no memory resource\n");
		वापस -ENXIO;
	पूर्ण

	bus = mii_bus->priv;
	bus->mii_bus = mii_bus;
	mdio_phys = res_mem->start;
	regsize = resource_size(res_mem);

	अगर (!devm_request_mem_region(&pdev->dev, mdio_phys, regsize,
				     res_mem->name)) अणु
		dev_err(&pdev->dev, "request_mem_region failed\n");
		वापस -ENXIO;
	पूर्ण

	bus->रेजिस्टर_base = devm_ioremap(&pdev->dev, mdio_phys, regsize);
	अगर (!bus->रेजिस्टर_base) अणु
		dev_err(&pdev->dev, "dev_ioremap failed\n");
		वापस -ENOMEM;
	पूर्ण

	smi_en.u64 = 0;
	smi_en.s.en = 1;
	oct_mdio_ग_लिखोq(smi_en.u64, bus->रेजिस्टर_base + SMI_EN);

	bus->mii_bus->name = KBUILD_MODNAME;
	snम_लिखो(bus->mii_bus->id, MII_BUS_ID_SIZE, "%px", bus->रेजिस्टर_base);
	bus->mii_bus->parent = &pdev->dev;

	bus->mii_bus->पढ़ो = cavium_mdiobus_पढ़ो;
	bus->mii_bus->ग_लिखो = cavium_mdiobus_ग_लिखो;

	platक्रमm_set_drvdata(pdev, bus);

	err = of_mdiobus_रेजिस्टर(bus->mii_bus, pdev->dev.of_node);
	अगर (err)
		जाओ fail_रेजिस्टर;

	dev_info(&pdev->dev, "Probed\n");

	वापस 0;
fail_रेजिस्टर:
	smi_en.u64 = 0;
	oct_mdio_ग_लिखोq(smi_en.u64, bus->रेजिस्टर_base + SMI_EN);
	वापस err;
पूर्ण

अटल पूर्णांक octeon_mdiobus_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cavium_mdiobus *bus;
	जोड़ cvmx_smix_en smi_en;

	bus = platक्रमm_get_drvdata(pdev);

	mdiobus_unरेजिस्टर(bus->mii_bus);
	smi_en.u64 = 0;
	oct_mdio_ग_लिखोq(smi_en.u64, bus->रेजिस्टर_base + SMI_EN);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id octeon_mdiobus_match[] = अणु
	अणु
		.compatible = "cavium,octeon-3860-mdio",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, octeon_mdiobus_match);

अटल काष्ठा platक्रमm_driver octeon_mdiobus_driver = अणु
	.driver = अणु
		.name		= KBUILD_MODNAME,
		.of_match_table = octeon_mdiobus_match,
	पूर्ण,
	.probe		= octeon_mdiobus_probe,
	.हटाओ		= octeon_mdiobus_हटाओ,
पूर्ण;

module_platक्रमm_driver(octeon_mdiobus_driver);

MODULE_DESCRIPTION("Cavium OCTEON MDIO bus driver");
MODULE_AUTHOR("David Daney");
MODULE_LICENSE("GPL v2");
