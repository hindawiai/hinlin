<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SSM2602/SSM2603/SSM2604 I2C audio driver
 *
 * Copyright 2014 Analog Devices Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>

#समावेश <sound/soc.h>

#समावेश "ssm2602.h"

/*
 * ssm2602 2 wire address is determined by GPIO5
 * state during घातerup.
 *    low  = 0x1a
 *    high = 0x1b
 */
अटल पूर्णांक ssm2602_i2c_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	वापस ssm2602_probe(&client->dev, id->driver_data,
		devm_regmap_init_i2c(client, &ssm2602_regmap_config));
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ssm2602_i2c_id[] = अणु
	अणु "ssm2602", SSM2602 पूर्ण,
	अणु "ssm2603", SSM2602 पूर्ण,
	अणु "ssm2604", SSM2604 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ssm2602_i2c_id);

अटल स्थिर काष्ठा of_device_id ssm2602_of_match[] = अणु
	अणु .compatible = "adi,ssm2602", पूर्ण,
	अणु .compatible = "adi,ssm2603", पूर्ण,
	अणु .compatible = "adi,ssm2604", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ssm2602_of_match);

अटल काष्ठा i2c_driver ssm2602_i2c_driver = अणु
	.driver = अणु
		.name = "ssm2602",
		.of_match_table = ssm2602_of_match,
	पूर्ण,
	.probe = ssm2602_i2c_probe,
	.id_table = ssm2602_i2c_id,
पूर्ण;
module_i2c_driver(ssm2602_i2c_driver);

MODULE_DESCRIPTION("ASoC SSM2602/SSM2603/SSM2604 I2C driver");
MODULE_AUTHOR("Cliff Cai");
MODULE_LICENSE("GPL");
