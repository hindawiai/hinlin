<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Texas Instruments PCM186x Universal Audio ADC - I2C
 *
 * Copyright (C) 2015-2017 Texas Instruments Incorporated - https://www.ti.com
 *	Andreas Dannenberg <dannenberg@ti.com>
 *	Andrew F. Davis <afd@ti.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>

#समावेश "pcm186x.h"

अटल स्थिर काष्ठा of_device_id pcm186x_of_match[] = अणु
	अणु .compatible = "ti,pcm1862", .data = (व्योम *)PCM1862 पूर्ण,
	अणु .compatible = "ti,pcm1863", .data = (व्योम *)PCM1863 पूर्ण,
	अणु .compatible = "ti,pcm1864", .data = (व्योम *)PCM1864 पूर्ण,
	अणु .compatible = "ti,pcm1865", .data = (व्योम *)PCM1865 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pcm186x_of_match);

अटल पूर्णांक pcm186x_i2c_probe(काष्ठा i2c_client *i2c,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	स्थिर क्रमागत pcm186x_type type = (क्रमागत pcm186x_type)id->driver_data;
	पूर्णांक irq = i2c->irq;
	काष्ठा regmap *regmap;

	regmap = devm_regmap_init_i2c(i2c, &pcm186x_regmap);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	वापस pcm186x_probe(&i2c->dev, type, irq, regmap);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id pcm186x_i2c_id[] = अणु
	अणु "pcm1862", PCM1862 पूर्ण,
	अणु "pcm1863", PCM1863 पूर्ण,
	अणु "pcm1864", PCM1864 पूर्ण,
	अणु "pcm1865", PCM1865 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, pcm186x_i2c_id);

अटल काष्ठा i2c_driver pcm186x_i2c_driver = अणु
	.probe		= pcm186x_i2c_probe,
	.id_table	= pcm186x_i2c_id,
	.driver		= अणु
		.name	= "pcm186x",
		.of_match_table = pcm186x_of_match,
	पूर्ण,
पूर्ण;
module_i2c_driver(pcm186x_i2c_driver);

MODULE_AUTHOR("Andreas Dannenberg <dannenberg@ti.com>");
MODULE_AUTHOR("Andrew F. Davis <afd@ti.com>");
MODULE_DESCRIPTION("PCM186x Universal Audio ADC I2C Interface Driver");
MODULE_LICENSE("GPL v2");
