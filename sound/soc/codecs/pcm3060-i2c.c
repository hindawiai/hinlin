<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// PCM3060 I2C driver
//
// Copyright (C) 2018 Kirill Marinushkin <kmarinushkin@birdec.com>

#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <sound/soc.h>

#समावेश "pcm3060.h"

अटल पूर्णांक pcm3060_i2c_probe(काष्ठा i2c_client *i2c,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा pcm3060_priv *priv;

	priv = devm_kzalloc(&i2c->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, priv);

	priv->regmap = devm_regmap_init_i2c(i2c, &pcm3060_regmap);
	अगर (IS_ERR(priv->regmap))
		वापस PTR_ERR(priv->regmap);

	वापस pcm3060_probe(&i2c->dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id pcm3060_i2c_id[] = अणु
	अणु .name = "pcm3060" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, pcm3060_i2c_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id pcm3060_of_match[] = अणु
	अणु .compatible = "ti,pcm3060" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, pcm3060_of_match);
#पूर्ण_अगर /* CONFIG_OF */

अटल काष्ठा i2c_driver pcm3060_i2c_driver = अणु
	.driver = अणु
		.name = "pcm3060",
#अगर_घोषित CONFIG_OF
		.of_match_table = pcm3060_of_match,
#पूर्ण_अगर /* CONFIG_OF */
	पूर्ण,
	.id_table = pcm3060_i2c_id,
	.probe = pcm3060_i2c_probe,
पूर्ण;

module_i2c_driver(pcm3060_i2c_driver);

MODULE_DESCRIPTION("PCM3060 I2C driver");
MODULE_AUTHOR("Kirill Marinushkin <kmarinushkin@birdec.com>");
MODULE_LICENSE("GPL v2");
