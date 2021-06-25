<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * es8328-i2c.c  --  ES8328 ALSA SoC I2C Audio driver
 *
 * Copyright 2014 Sutajio Ko-Usagi PTE LTD
 *
 * Author: Sean Cross <xobs@kosagi.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>

#समावेश <sound/soc.h>

#समावेश "es8328.h"

अटल स्थिर काष्ठा i2c_device_id es8328_id[] = अणु
	अणु "es8328", 0 पूर्ण,
	अणु "es8388", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, es8328_id);

अटल स्थिर काष्ठा of_device_id es8328_of_match[] = अणु
	अणु .compatible = "everest,es8328", पूर्ण,
	अणु .compatible = "everest,es8388", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, es8328_of_match);

अटल पूर्णांक es8328_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	वापस es8328_probe(&i2c->dev,
			devm_regmap_init_i2c(i2c, &es8328_regmap_config));
पूर्ण

अटल काष्ठा i2c_driver es8328_i2c_driver = अणु
	.driver = अणु
		.name		= "es8328",
		.of_match_table = es8328_of_match,
	पूर्ण,
	.probe    = es8328_i2c_probe,
	.id_table = es8328_id,
पूर्ण;

module_i2c_driver(es8328_i2c_driver);

MODULE_DESCRIPTION("ASoC ES8328 audio CODEC I2C driver");
MODULE_AUTHOR("Sean Cross <xobs@kosagi.com>");
MODULE_LICENSE("GPL");
