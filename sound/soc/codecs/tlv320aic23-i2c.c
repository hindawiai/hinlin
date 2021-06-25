<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ALSA SoC TLV320AIC23 codec driver I2C पूर्णांकerface
 *
 * Author:      Arun KS, <arunks@mistralsolutions.com>
 * Copyright:   (C) 2008 Mistral Solutions Pvt Ltd.,
 *
 * Based on sound/soc/codecs/wm8731.c by Riअक्षरd Purdie
 */

#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <sound/soc.h>

#समावेश "tlv320aic23.h"

अटल पूर्णांक tlv320aic23_i2c_probe(काष्ठा i2c_client *i2c,
				 स्थिर काष्ठा i2c_device_id *i2c_id)
अणु
	काष्ठा regmap *regmap;

	अगर (!i2c_check_functionality(i2c->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EINVAL;

	regmap = devm_regmap_init_i2c(i2c, &tlv320aic23_regmap);
	वापस tlv320aic23_probe(&i2c->dev, regmap);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tlv320aic23_id[] = अणु
	अणु"tlv320aic23", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, tlv320aic23_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id tlv320aic23_of_match[] = अणु
	अणु .compatible = "ti,tlv320aic23", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tlv320aic23_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver tlv320aic23_i2c_driver = अणु
	.driver = अणु
		   .name = "tlv320aic23-codec",
		   .of_match_table = of_match_ptr(tlv320aic23_of_match),
		   पूर्ण,
	.probe = tlv320aic23_i2c_probe,
	.id_table = tlv320aic23_id,
पूर्ण;

module_i2c_driver(tlv320aic23_i2c_driver);

MODULE_DESCRIPTION("ASoC TLV320AIC23 codec driver I2C");
MODULE_AUTHOR("Arun KS <arunks@mistralsolutions.com>");
MODULE_LICENSE("GPL");
