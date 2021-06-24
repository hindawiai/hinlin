<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PCM3168A codec i2c driver
 *
 * Copyright (C) 2015 Imagination Technologies Ltd.
 *
 * Author: Damien Horsley <Damien.Horsley@imgtec.com>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>

#समावेश <sound/soc.h>

#समावेश "pcm3168a.h"

अटल पूर्णांक pcm3168a_i2c_probe(काष्ठा i2c_client *i2c,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap *regmap;

	regmap = devm_regmap_init_i2c(i2c, &pcm3168a_regmap);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	वापस pcm3168a_probe(&i2c->dev, regmap);
पूर्ण

अटल पूर्णांक pcm3168a_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	pcm3168a_हटाओ(&i2c->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id pcm3168a_i2c_id[] = अणु
	अणु "pcm3168a", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, pcm3168a_i2c_id);

अटल स्थिर काष्ठा of_device_id pcm3168a_of_match[] = अणु
	अणु .compatible = "ti,pcm3168a", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pcm3168a_of_match);

अटल काष्ठा i2c_driver pcm3168a_i2c_driver = अणु
	.probe		= pcm3168a_i2c_probe,
	.हटाओ		= pcm3168a_i2c_हटाओ,
	.id_table	= pcm3168a_i2c_id,
	.driver		= अणु
		.name	= "pcm3168a",
		.of_match_table = pcm3168a_of_match,
		.pm		= &pcm3168a_pm_ops,
	पूर्ण,
पूर्ण;
module_i2c_driver(pcm3168a_i2c_driver);

MODULE_DESCRIPTION("PCM3168A I2C codec driver");
MODULE_AUTHOR("Damien Horsley <Damien.Horsley@imgtec.com>");
MODULE_LICENSE("GPL v2");
