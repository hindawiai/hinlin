<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ADAU1977/ADAU1978/ADAU1979 driver
 *
 * Copyright 2014 Analog Devices Inc.
 *  Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <sound/soc.h>

#समावेश "adau1977.h"

अटल पूर्णांक adau1977_i2c_probe(काष्ठा i2c_client *client,
	स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap_config config;

	config = adau1977_regmap_config;
	config.val_bits = 8;
	config.reg_bits = 8;

	वापस adau1977_probe(&client->dev,
		devm_regmap_init_i2c(client, &config),
		id->driver_data, शून्य);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id adau1977_i2c_ids[] = अणु
	अणु "adau1977", ADAU1977 पूर्ण,
	अणु "adau1978", ADAU1978 पूर्ण,
	अणु "adau1979", ADAU1978 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adau1977_i2c_ids);

अटल काष्ठा i2c_driver adau1977_i2c_driver = अणु
	.driver = अणु
		.name = "adau1977",
	पूर्ण,
	.probe = adau1977_i2c_probe,
	.id_table = adau1977_i2c_ids,
पूर्ण;
module_i2c_driver(adau1977_i2c_driver);

MODULE_DESCRIPTION("ASoC ADAU1977/ADAU1978/ADAU1979 driver");
MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_LICENSE("GPL");
