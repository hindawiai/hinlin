<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम ADAU1372 codec
 *
 * Copyright 2016 Analog Devices Inc.
 *  Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <sound/soc.h>

#समावेश "adau1372.h"

अटल पूर्णांक adau1372_i2c_probe(काष्ठा i2c_client *client, स्थिर काष्ठा i2c_device_id *id)
अणु
	वापस adau1372_probe(&client->dev,
		devm_regmap_init_i2c(client, &adau1372_regmap_config), शून्य);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id adau1372_i2c_ids[] = अणु
	अणु "adau1372", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adau1372_i2c_ids);

अटल काष्ठा i2c_driver adau1372_i2c_driver = अणु
	.driver = अणु
		.name = "adau1372",
	पूर्ण,
	.probe = adau1372_i2c_probe,
	.id_table = adau1372_i2c_ids,
पूर्ण;
module_i2c_driver(adau1372_i2c_driver);

MODULE_DESCRIPTION("ASoC ADAU1372 CODEC I2C driver");
MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_LICENSE("GPL v2");
