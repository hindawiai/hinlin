<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only
 *
 * ALSA SoC TLV320AIC3x codec driver I2C पूर्णांकerface
 *
 * Author:      Arun KS, <arunks@mistralsolutions.com>
 * Copyright:   (C) 2008 Mistral Solutions Pvt Ltd.,
 *
 * Based on sound/soc/codecs/wm8731.c by Riअक्षरd Purdie
 *
 */

#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <sound/soc.h>

#समावेश "tlv320aic3x.h"

अटल पूर्णांक aic3x_i2c_probe(काष्ठा i2c_client *i2c, स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap *regmap;
	काष्ठा regmap_config config;

	config = aic3x_regmap;
	config.reg_bits = 8;
	config.val_bits = 8;

	regmap = devm_regmap_init_i2c(i2c, &config);
	वापस aic3x_probe(&i2c->dev, regmap, id->driver_data);
पूर्ण

अटल पूर्णांक aic3x_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	वापस aic3x_हटाओ(&i2c->dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id aic3x_i2c_id[] = अणु
	अणु "tlv320aic3x", AIC3X_MODEL_3X पूर्ण,
	अणु "tlv320aic33", AIC3X_MODEL_33 पूर्ण,
	अणु "tlv320aic3007", AIC3X_MODEL_3007 पूर्ण,
	अणु "tlv320aic3104", AIC3X_MODEL_3104 पूर्ण,
	अणु "tlv320aic3106", AIC3X_MODEL_3106 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, aic3x_i2c_id);

अटल स्थिर काष्ठा of_device_id aic3x_of_id[] = अणु
	अणु .compatible = "ti,tlv320aic3x", पूर्ण,
	अणु .compatible = "ti,tlv320aic33" पूर्ण,
	अणु .compatible = "ti,tlv320aic3007" पूर्ण,
	अणु .compatible = "ti,tlv320aic3104" पूर्ण,
	अणु .compatible = "ti,tlv320aic3106" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, aic3x_of_id);

अटल काष्ठा i2c_driver aic3x_i2c_driver = अणु
	.driver = अणु
		.name = "tlv320aic3x",
		.of_match_table = aic3x_of_id,
	पूर्ण,
	.probe = aic3x_i2c_probe,
	.हटाओ = aic3x_i2c_हटाओ,
	.id_table = aic3x_i2c_id,
पूर्ण;

module_i2c_driver(aic3x_i2c_driver);

MODULE_DESCRIPTION("ASoC TLV320AIC3x codec driver I2C");
MODULE_AUTHOR("Arun KS <arunks@mistralsolutions.com>");
MODULE_LICENSE("GPL");
