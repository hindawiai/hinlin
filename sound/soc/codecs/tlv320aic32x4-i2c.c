<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * Copyright 2011-2019 NW Digital Radio
 *
 * Author: Annaliese McDermond <nh6z@nh6z.net>
 *
 * Based on sound/soc/codecs/wm8974 and TI driver क्रम kernel 2.6.27.
 *
 */

#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <sound/soc.h>

#समावेश "tlv320aic32x4.h"

अटल पूर्णांक aic32x4_i2c_probe(काष्ठा i2c_client *i2c,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap *regmap;
	काष्ठा regmap_config config;

	config = aic32x4_regmap_config;
	config.reg_bits = 8;
	config.val_bits = 8;

	regmap = devm_regmap_init_i2c(i2c, &config);
	वापस aic32x4_probe(&i2c->dev, regmap);
पूर्ण

अटल पूर्णांक aic32x4_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	वापस aic32x4_हटाओ(&i2c->dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id aic32x4_i2c_id[] = अणु
	अणु "tlv320aic32x4", 0 पूर्ण,
	अणु "tlv320aic32x6", 1 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, aic32x4_i2c_id);

अटल स्थिर काष्ठा of_device_id aic32x4_of_id[] = अणु
	अणु .compatible = "ti,tlv320aic32x4", पूर्ण,
	अणु .compatible = "ti,tlv320aic32x6", पूर्ण,
	अणु /* senitel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, aic32x4_of_id);

अटल काष्ठा i2c_driver aic32x4_i2c_driver = अणु
	.driver = अणु
		.name = "tlv320aic32x4",
		.of_match_table = aic32x4_of_id,
	पूर्ण,
	.probe =    aic32x4_i2c_probe,
	.हटाओ =   aic32x4_i2c_हटाओ,
	.id_table = aic32x4_i2c_id,
पूर्ण;

module_i2c_driver(aic32x4_i2c_driver);

MODULE_DESCRIPTION("ASoC TLV320AIC32x4 codec driver I2C");
MODULE_AUTHOR("Annaliese McDermond <nh6z@nh6z.net>");
MODULE_LICENSE("GPL");
