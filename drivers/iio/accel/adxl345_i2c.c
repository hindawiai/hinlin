<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ADXL345 3-Axis Digital Accelerometer I2C driver
 *
 * Copyright (c) 2017 Eva Rachel Retuya <eraretuya@gmail.com>
 *
 * 7-bit I2C slave address: 0x1D (ALT ADDRESS pin tied to VDDIO) or
 * 0x53 (ALT ADDRESS pin grounded)
 */

#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>

#समावेश "adxl345.h"

अटल स्थिर काष्ठा regmap_config adxl345_i2c_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल पूर्णांक adxl345_i2c_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap *regmap;

	अगर (!id)
		वापस -ENODEV;

	regmap = devm_regmap_init_i2c(client, &adxl345_i2c_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&client->dev, "Error initializing i2c regmap: %ld\n",
			PTR_ERR(regmap));
		वापस PTR_ERR(regmap);
	पूर्ण

	वापस adxl345_core_probe(&client->dev, regmap, id->driver_data,
				  id->name);
पूर्ण

अटल पूर्णांक adxl345_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	वापस adxl345_core_हटाओ(&client->dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id adxl345_i2c_id[] = अणु
	अणु "adxl345", ADXL345 पूर्ण,
	अणु "adxl375", ADXL375 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, adxl345_i2c_id);

अटल स्थिर काष्ठा of_device_id adxl345_of_match[] = अणु
	अणु .compatible = "adi,adxl345" पूर्ण,
	अणु .compatible = "adi,adxl375" पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, adxl345_of_match);

अटल काष्ठा i2c_driver adxl345_i2c_driver = अणु
	.driver = अणु
		.name	= "adxl345_i2c",
		.of_match_table = adxl345_of_match,
	पूर्ण,
	.probe		= adxl345_i2c_probe,
	.हटाओ		= adxl345_i2c_हटाओ,
	.id_table	= adxl345_i2c_id,
पूर्ण;

module_i2c_driver(adxl345_i2c_driver);

MODULE_AUTHOR("Eva Rachel Retuya <eraretuya@gmail.com>");
MODULE_DESCRIPTION("ADXL345 3-Axis Digital Accelerometer I2C driver");
MODULE_LICENSE("GPL v2");
