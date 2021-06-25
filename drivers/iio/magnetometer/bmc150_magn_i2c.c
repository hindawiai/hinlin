<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * 3-axis magnetometer driver supporting following I2C Bosch-Sensortec chips:
 *  - BMC150
 *  - BMC156
 *  - BMM150
 *
 * Copyright (c) 2016, Intel Corporation.
 */
#समावेश <linux/device.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/acpi.h>
#समावेश <linux/regmap.h>

#समावेश "bmc150_magn.h"

अटल पूर्णांक bmc150_magn_i2c_probe(काष्ठा i2c_client *client,
				 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap *regmap;
	स्थिर अक्षर *name = शून्य;

	regmap = devm_regmap_init_i2c(client, &bmc150_magn_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&client->dev, "Failed to initialize i2c regmap\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	अगर (id)
		name = id->name;

	वापस bmc150_magn_probe(&client->dev, regmap, client->irq, name);
पूर्ण

अटल पूर्णांक bmc150_magn_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	वापस bmc150_magn_हटाओ(&client->dev);
पूर्ण

अटल स्थिर काष्ठा acpi_device_id bmc150_magn_acpi_match[] = अणु
	अणु"BMC150B", 0पूर्ण,
	अणु"BMC156B", 0पूर्ण,
	अणु"BMM150B", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, bmc150_magn_acpi_match);

अटल स्थिर काष्ठा i2c_device_id bmc150_magn_i2c_id[] = अणु
	अणु"bmc150_magn",	0पूर्ण,
	अणु"bmc156_magn", 0पूर्ण,
	अणु"bmm150_magn", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, bmc150_magn_i2c_id);

अटल स्थिर काष्ठा of_device_id bmc150_magn_of_match[] = अणु
	अणु .compatible = "bosch,bmc150_magn" पूर्ण,
	अणु .compatible = "bosch,bmc156_magn" पूर्ण,
	अणु .compatible = "bosch,bmm150_magn" पूर्ण, /* deprecated compatible */
	अणु .compatible = "bosch,bmm150" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, bmc150_magn_of_match);

अटल काष्ठा i2c_driver bmc150_magn_driver = अणु
	.driver = अणु
		.name	= "bmc150_magn_i2c",
		.of_match_table = bmc150_magn_of_match,
		.acpi_match_table = ACPI_PTR(bmc150_magn_acpi_match),
		.pm	= &bmc150_magn_pm_ops,
	पूर्ण,
	.probe		= bmc150_magn_i2c_probe,
	.हटाओ		= bmc150_magn_i2c_हटाओ,
	.id_table	= bmc150_magn_i2c_id,
पूर्ण;
module_i2c_driver(bmc150_magn_driver);

MODULE_AUTHOR("Daniel Baluta <daniel.baluta@intel.com");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("BMC150 I2C magnetometer driver");
