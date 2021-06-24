<शैली गुरु>
/*
 * Cirrus Logic CS42448/CS42888 Audio CODEC DAI I2C driver
 *
 * Copyright (C) 2014 Freescale Semiconductor, Inc.
 *
 * Author: Nicolin Chen <Guangyu.Chen@मुक्तscale.com>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <sound/soc.h>

#समावेश "cs42xx8.h"

अटल पूर्णांक cs42xx8_i2c_probe(काष्ठा i2c_client *i2c,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret = cs42xx8_probe(&i2c->dev,
			devm_regmap_init_i2c(i2c, &cs42xx8_regmap_config));
	अगर (ret)
		वापस ret;

	pm_runसमय_enable(&i2c->dev);
	pm_request_idle(&i2c->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक cs42xx8_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	pm_runसमय_disable(&i2c->dev);

	वापस 0;
पूर्ण

अटल काष्ठा i2c_device_id cs42xx8_i2c_id[] = अणु
	अणु"cs42448", (kernel_uदीर्घ_t)&cs42448_dataपूर्ण,
	अणु"cs42888", (kernel_uदीर्घ_t)&cs42888_dataपूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, cs42xx8_i2c_id);

अटल काष्ठा i2c_driver cs42xx8_i2c_driver = अणु
	.driver = अणु
		.name = "cs42xx8",
		.pm = &cs42xx8_pm,
		.of_match_table = cs42xx8_of_match,
	पूर्ण,
	.probe = cs42xx8_i2c_probe,
	.हटाओ = cs42xx8_i2c_हटाओ,
	.id_table = cs42xx8_i2c_id,
पूर्ण;

module_i2c_driver(cs42xx8_i2c_driver);

MODULE_DESCRIPTION("Cirrus Logic CS42448/CS42888 ALSA SoC Codec I2C Driver");
MODULE_AUTHOR("Freescale Semiconductor, Inc.");
MODULE_LICENSE("GPL");
