<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PCM179X ASoC I2C driver
 *
 * Copyright (c) Teenage Engineering AB 2016
 *
 *     Jacob Siverskog <jacob@teenage.engineering>
 */

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>

#समावेश "pcm179x.h"

अटल पूर्णांक pcm179x_i2c_probe(काष्ठा i2c_client *client,
			      स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	regmap = devm_regmap_init_i2c(client, &pcm179x_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		ret = PTR_ERR(regmap);
		dev_err(&client->dev, "Failed to allocate regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस pcm179x_common_init(&client->dev, regmap);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id pcm179x_of_match[] = अणु
	अणु .compatible = "ti,pcm1792a", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pcm179x_of_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id pcm179x_i2c_ids[] = अणु
	अणु "pcm179x", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, pcm179x_i2c_ids);

अटल काष्ठा i2c_driver pcm179x_i2c_driver = अणु
	.driver = अणु
		.name	= "pcm179x",
		.of_match_table = of_match_ptr(pcm179x_of_match),
	पूर्ण,
	.id_table	= pcm179x_i2c_ids,
	.probe		= pcm179x_i2c_probe,
पूर्ण;

module_i2c_driver(pcm179x_i2c_driver);

MODULE_DESCRIPTION("ASoC PCM179X I2C driver");
MODULE_AUTHOR("Jacob Siverskog <jacob@teenage.engineering>");
MODULE_LICENSE("GPL");
