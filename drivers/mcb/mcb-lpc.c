<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MEN Chameleon Bus.
 *
 * Copyright (C) 2014 MEN Mikroelektronik GmbH (www.men.de)
 * Author: Andreas Werner <andreas.werner@men.de>
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/dmi.h>
#समावेश <linux/mcb.h>
#समावेश <linux/पन.स>
#समावेश "mcb-internal.h"

काष्ठा priv अणु
	काष्ठा mcb_bus *bus;
	काष्ठा resource *mem;
	व्योम __iomem *base;
पूर्ण;

अटल पूर्णांक mcb_lpc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा priv *priv;
	पूर्णांक ret = 0;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!priv->mem) अणु
		dev_err(&pdev->dev, "No Memory resource\n");
		वापस -ENODEV;
	पूर्ण

	res = devm_request_mem_region(&pdev->dev, priv->mem->start,
				      resource_size(priv->mem),
				      KBUILD_MODNAME);
	अगर (!res) अणु
		dev_err(&pdev->dev, "Failed to request IO memory\n");
		वापस -EBUSY;
	पूर्ण

	priv->base = devm_ioremap(&pdev->dev, priv->mem->start,
				  resource_size(priv->mem));
	अगर (!priv->base) अणु
		dev_err(&pdev->dev, "Cannot ioremap\n");
		वापस -ENOMEM;
	पूर्ण

	platक्रमm_set_drvdata(pdev, priv);

	priv->bus = mcb_alloc_bus(&pdev->dev);
	अगर (IS_ERR(priv->bus))
		वापस PTR_ERR(priv->bus);

	ret = chameleon_parse_cells(priv->bus, priv->mem->start, priv->base);
	अगर (ret < 0) अणु
		mcb_release_bus(priv->bus);
		वापस ret;
	पूर्ण

	dev_dbg(&pdev->dev, "Found %d cells\n", ret);

	mcb_bus_add_devices(priv->bus);

	वापस 0;

पूर्ण

अटल पूर्णांक mcb_lpc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा priv *priv = platक्रमm_get_drvdata(pdev);

	mcb_release_bus(priv->bus);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_device *mcb_lpc_pdev;

अटल पूर्णांक mcb_lpc_create_platक्रमm_device(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	काष्ठा resource *res = id->driver_data;
	पूर्णांक ret;

	mcb_lpc_pdev = platक्रमm_device_alloc("mcb-lpc", -1);
	अगर (!mcb_lpc_pdev)
		वापस -ENOMEM;

	ret = platक्रमm_device_add_resources(mcb_lpc_pdev, res, 1);
	अगर (ret)
		जाओ out_put;

	ret = platक्रमm_device_add(mcb_lpc_pdev);
	अगर (ret)
		जाओ out_put;

	वापस 0;

out_put:
	platक्रमm_device_put(mcb_lpc_pdev);
	वापस ret;
पूर्ण

अटल काष्ठा resource sc24_fpga_resource = अणु
	.start = 0xe000e000,
	.end = 0xe000e000 + CHAM_HEADER_SIZE,
	.flags = IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा resource sc31_fpga_resource = अणु
	.start = 0xf000e000,
	.end = 0xf000e000 + CHAM_HEADER_SIZE,
	.flags = IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_driver mcb_lpc_driver = अणु
	.driver		= अणु
		.name = "mcb-lpc",
	पूर्ण,
	.probe		= mcb_lpc_probe,
	.हटाओ		= mcb_lpc_हटाओ,
पूर्ण;

अटल स्थिर काष्ठा dmi_प्रणाली_id mcb_lpc_dmi_table[] = अणु
	अणु
		.ident = "SC24",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "MEN"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "14SC24"),
		पूर्ण,
		.driver_data = (व्योम *)&sc24_fpga_resource,
		.callback = mcb_lpc_create_platक्रमm_device,
	पूर्ण,
	अणु
		.ident = "SC31",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "MEN"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "14SC31"),
		पूर्ण,
		.driver_data = (व्योम *)&sc31_fpga_resource,
		.callback = mcb_lpc_create_platक्रमm_device,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(dmi, mcb_lpc_dmi_table);

अटल पूर्णांक __init mcb_lpc_init(व्योम)
अणु
	अगर (!dmi_check_प्रणाली(mcb_lpc_dmi_table))
		वापस -ENODEV;

	वापस platक्रमm_driver_रेजिस्टर(&mcb_lpc_driver);
पूर्ण

अटल व्योम __निकास mcb_lpc_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(mcb_lpc_pdev);
	platक्रमm_driver_unरेजिस्टर(&mcb_lpc_driver);
पूर्ण

module_init(mcb_lpc_init);
module_निकास(mcb_lpc_निकास);

MODULE_AUTHOR("Andreas Werner <andreas.werner@men.de>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("MCB over LPC support");
MODULE_IMPORT_NS(MCB);
