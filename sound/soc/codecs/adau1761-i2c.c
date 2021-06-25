<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम ADAU1361/ADAU1461/ADAU1761/ADAU1961 codec
 *
 * Copyright 2014 Analog Devices Inc.
 *  Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <sound/soc.h>

#समावेश "adau1761.h"

अटल पूर्णांक adau1761_i2c_probe(काष्ठा i2c_client *client,
	स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap_config config;

	config = adau1761_regmap_config;
	config.val_bits = 8;
	config.reg_bits = 16;

	वापस adau1761_probe(&client->dev,
		devm_regmap_init_i2c(client, &config),
		id->driver_data, शून्य);
पूर्ण

अटल पूर्णांक adau1761_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	adau17x1_हटाओ(&client->dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id adau1761_i2c_ids[] = अणु
	अणु "adau1361", ADAU1361 पूर्ण,
	अणु "adau1461", ADAU1761 पूर्ण,
	अणु "adau1761", ADAU1761 पूर्ण,
	अणु "adau1961", ADAU1361 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adau1761_i2c_ids);

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id adau1761_i2c_dt_ids[] = अणु
	अणु .compatible = "adi,adau1361", पूर्ण,
	अणु .compatible = "adi,adau1461", पूर्ण,
	अणु .compatible = "adi,adau1761", पूर्ण,
	अणु .compatible = "adi,adau1961", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, adau1761_i2c_dt_ids);
#पूर्ण_अगर

अटल काष्ठा i2c_driver adau1761_i2c_driver = अणु
	.driver = अणु
		.name = "adau1761",
		.of_match_table = of_match_ptr(adau1761_i2c_dt_ids),
	पूर्ण,
	.probe = adau1761_i2c_probe,
	.हटाओ = adau1761_i2c_हटाओ,
	.id_table = adau1761_i2c_ids,
पूर्ण;
module_i2c_driver(adau1761_i2c_driver);

MODULE_DESCRIPTION("ASoC ADAU1361/ADAU1461/ADAU1761/ADAU1961 CODEC I2C driver");
MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_LICENSE("GPL");
