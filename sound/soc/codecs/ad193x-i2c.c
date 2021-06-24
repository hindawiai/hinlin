<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AD1936/AD1937 audio driver
 *
 * Copyright 2014 Analog Devices Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>

#समावेश <sound/soc.h>

#समावेश "ad193x.h"

अटल स्थिर काष्ठा i2c_device_id ad193x_id[] = अणु
	अणु "ad1936", AD193X पूर्ण,
	अणु "ad1937", AD193X पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ad193x_id);

अटल पूर्णांक ad193x_i2c_probe(काष्ठा i2c_client *client,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap_config config;

	config = ad193x_regmap_config;
	config.val_bits = 8;
	config.reg_bits = 8;

	वापस ad193x_probe(&client->dev,
			    devm_regmap_init_i2c(client, &config),
			    (क्रमागत ad193x_type)id->driver_data);
पूर्ण

अटल काष्ठा i2c_driver ad193x_i2c_driver = अणु
	.driver = अणु
		.name = "ad193x",
	पूर्ण,
	.probe    = ad193x_i2c_probe,
	.id_table = ad193x_id,
पूर्ण;
module_i2c_driver(ad193x_i2c_driver);

MODULE_DESCRIPTION("ASoC AD1936/AD1937 audio CODEC driver");
MODULE_AUTHOR("Barry Song <21cnbao@gmail.com>");
MODULE_LICENSE("GPL");
