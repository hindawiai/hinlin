<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * BMI160 - Bosch IMU, I2C bits
 *
 * Copyright (c) 2016, Intel Corporation.
 *
 * 7-bit I2C slave address is:
 *      - 0x68 अगर SDO is pulled to GND
 *      - 0x69 अगर SDO is pulled to VDDIO
 */
#समावेश <linux/acpi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>

#समावेश "bmi160.h"

अटल पूर्णांक bmi160_i2c_probe(काष्ठा i2c_client *client,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap *regmap;
	स्थिर अक्षर *name = शून्य;

	regmap = devm_regmap_init_i2c(client, &bmi160_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&client->dev, "Failed to register i2c regmap: %pe\n",
			regmap);
		वापस PTR_ERR(regmap);
	पूर्ण

	अगर (id)
		name = id->name;

	वापस bmi160_core_probe(&client->dev, regmap, name, false);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id bmi160_i2c_id[] = अणु
	अणु"bmi160", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, bmi160_i2c_id);

अटल स्थिर काष्ठा acpi_device_id bmi160_acpi_match[] = अणु
	अणु"BMI0160", 0पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, bmi160_acpi_match);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id bmi160_of_match[] = अणु
	अणु .compatible = "bosch,bmi160" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bmi160_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver bmi160_i2c_driver = अणु
	.driver = अणु
		.name			= "bmi160_i2c",
		.acpi_match_table	= ACPI_PTR(bmi160_acpi_match),
		.of_match_table		= of_match_ptr(bmi160_of_match),
	पूर्ण,
	.probe		= bmi160_i2c_probe,
	.id_table	= bmi160_i2c_id,
पूर्ण;
module_i2c_driver(bmi160_i2c_driver);

MODULE_AUTHOR("Daniel Baluta <daniel.baluta@intel.com>");
MODULE_DESCRIPTION("BMI160 I2C driver");
MODULE_LICENSE("GPL v2");
