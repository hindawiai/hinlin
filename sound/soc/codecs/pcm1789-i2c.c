<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Audio driver क्रम PCM1789 I2C
// Copyright (C) 2018 Bootlin
// Mylथउne Josseअक्रम <mylene.josseअक्रम@bootlin.com>

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>

#समावेश "pcm1789.h"

अटल पूर्णांक pcm1789_i2c_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	regmap = devm_regmap_init_i2c(client, &pcm1789_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		ret = PTR_ERR(regmap);
		dev_err(&client->dev, "Failed to allocate regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस pcm1789_common_init(&client->dev, regmap);
पूर्ण

अटल पूर्णांक pcm1789_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	वापस pcm1789_common_निकास(&client->dev);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id pcm1789_of_match[] = अणु
	अणु .compatible = "ti,pcm1789", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pcm1789_of_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id pcm1789_i2c_ids[] = अणु
	अणु "pcm1789", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, pcm1789_i2c_ids);

अटल काष्ठा i2c_driver pcm1789_i2c_driver = अणु
	.driver = अणु
		.name	= "pcm1789",
		.of_match_table = of_match_ptr(pcm1789_of_match),
	पूर्ण,
	.id_table	= pcm1789_i2c_ids,
	.probe		= pcm1789_i2c_probe,
	.हटाओ	= pcm1789_i2c_हटाओ,
पूर्ण;

module_i2c_driver(pcm1789_i2c_driver);

MODULE_DESCRIPTION("ASoC PCM1789 I2C driver");
MODULE_AUTHOR("Mylथउne Josserand <mylene.josserand@bootlin.com>");
MODULE_LICENSE("GPL");
