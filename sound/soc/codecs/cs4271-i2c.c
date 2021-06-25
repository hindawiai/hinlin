<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * CS4271 I2C audio driver
 *
 * Copyright (c) 2010 Alexander Sverdlin <subaparts@yandex.ru>
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <sound/soc.h>
#समावेश "cs4271.h"

अटल पूर्णांक cs4271_i2c_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap_config config;

	config = cs4271_regmap_config;
	config.reg_bits = 8;
	config.val_bits = 8;

	वापस cs4271_probe(&client->dev,
			    devm_regmap_init_i2c(client, &config));
पूर्ण

अटल स्थिर काष्ठा i2c_device_id cs4271_i2c_id[] = अणु
	अणु "cs4271", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, cs4271_i2c_id);

अटल काष्ठा i2c_driver cs4271_i2c_driver = अणु
	.driver = अणु
		.name = "cs4271",
		.of_match_table = of_match_ptr(cs4271_dt_ids),
	पूर्ण,
	.probe = cs4271_i2c_probe,
	.id_table = cs4271_i2c_id,
पूर्ण;
module_i2c_driver(cs4271_i2c_driver);

MODULE_DESCRIPTION("ASoC CS4271 I2C Driver");
MODULE_AUTHOR("Alexander Sverdlin <subaparts@yandex.ru>");
MODULE_LICENSE("GPL");
