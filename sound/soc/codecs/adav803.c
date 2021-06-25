<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ADAV803 audio driver
 *
 * Copyright 2014 Analog Devices Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>

#समावेश <sound/soc.h>

#समावेश "adav80x.h"

अटल स्थिर काष्ठा i2c_device_id adav803_id[] = अणु
	अणु "adav803", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adav803_id);

अटल पूर्णांक adav803_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	वापस adav80x_bus_probe(&client->dev,
		devm_regmap_init_i2c(client, &adav80x_regmap_config));
पूर्ण

अटल काष्ठा i2c_driver adav803_driver = अणु
	.driver = अणु
		.name = "adav803",
	पूर्ण,
	.probe = adav803_probe,
	.id_table = adav803_id,
पूर्ण;
module_i2c_driver(adav803_driver);

MODULE_DESCRIPTION("ASoC ADAV803 driver");
MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_AUTHOR("Yi Li <yi.li@analog.com>>");
MODULE_LICENSE("GPL");
