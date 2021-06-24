<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * BME680 - I2C Driver
 *
 * Copyright (C) 2018 Himanshu Jha <himanshujha199640@gmail.com>
 *
 * 7-Bit I2C slave address is:
 *	- 0x76 अगर SDO is pulled to GND
 *	- 0x77 अगर SDO is pulled to VDDIO
 *
 * Note: SDO pin cannot be left भग्नing otherwise I2C address
 *	 will be undefined.
 */
#समावेश <linux/acpi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>

#समावेश "bme680.h"

अटल पूर्णांक bme680_i2c_probe(काष्ठा i2c_client *client,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap *regmap;
	स्थिर अक्षर *name = शून्य;

	regmap = devm_regmap_init_i2c(client, &bme680_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&client->dev, "Failed to register i2c regmap %ld\n", PTR_ERR(regmap));
		वापस PTR_ERR(regmap);
	पूर्ण

	अगर (id)
		name = id->name;

	वापस bme680_core_probe(&client->dev, regmap, name);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id bme680_i2c_id[] = अणु
	अणु"bme680", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, bme680_i2c_id);

अटल स्थिर काष्ठा acpi_device_id bme680_acpi_match[] = अणु
	अणु"BME0680", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, bme680_acpi_match);

अटल स्थिर काष्ठा of_device_id bme680_of_i2c_match[] = अणु
	अणु .compatible = "bosch,bme680", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bme680_of_i2c_match);

अटल काष्ठा i2c_driver bme680_i2c_driver = अणु
	.driver = अणु
		.name			= "bme680_i2c",
		.acpi_match_table       = ACPI_PTR(bme680_acpi_match),
		.of_match_table		= bme680_of_i2c_match,
	पूर्ण,
	.probe = bme680_i2c_probe,
	.id_table = bme680_i2c_id,
पूर्ण;
module_i2c_driver(bme680_i2c_driver);

MODULE_AUTHOR("Himanshu Jha <himanshujha199640@gmail.com>");
MODULE_DESCRIPTION("BME680 I2C driver");
MODULE_LICENSE("GPL v2");
