<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम NXP FXAS21002C Gyroscope - I2C
 *
 * Copyright (C) 2018 Linaro Ltd.
 */

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>

#समावेश "fxas21002c.h"

अटल स्थिर काष्ठा regmap_config fxas21002c_regmap_i2c_conf = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = FXAS21002C_REG_CTRL3,
पूर्ण;

अटल पूर्णांक fxas21002c_i2c_probe(काष्ठा i2c_client *i2c)
अणु
	काष्ठा regmap *regmap;

	regmap = devm_regmap_init_i2c(i2c, &fxas21002c_regmap_i2c_conf);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&i2c->dev, "Failed to register i2c regmap: %ld\n",
			PTR_ERR(regmap));
		वापस PTR_ERR(regmap);
	पूर्ण

	वापस fxas21002c_core_probe(&i2c->dev, regmap, i2c->irq, i2c->name);
पूर्ण

अटल पूर्णांक fxas21002c_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	fxas21002c_core_हटाओ(&i2c->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id fxas21002c_i2c_id[] = अणु
	अणु "fxas21002c", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, fxas21002c_i2c_id);

अटल स्थिर काष्ठा of_device_id fxas21002c_i2c_of_match[] = अणु
	अणु .compatible = "nxp,fxas21002c", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, fxas21002c_i2c_of_match);

अटल काष्ठा i2c_driver fxas21002c_i2c_driver = अणु
	.driver = अणु
		.name = "fxas21002c_i2c",
		.pm = &fxas21002c_pm_ops,
		.of_match_table = fxas21002c_i2c_of_match,
	पूर्ण,
	.probe_new	= fxas21002c_i2c_probe,
	.हटाओ		= fxas21002c_i2c_हटाओ,
	.id_table	= fxas21002c_i2c_id,
पूर्ण;
module_i2c_driver(fxas21002c_i2c_driver);

MODULE_AUTHOR("Rui Miguel Silva <rui.silva@linaro.org>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("FXAS21002C I2C Gyro driver");
