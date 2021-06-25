<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * TSC2004 touchscreen driver
 *
 * Copyright (C) 2015 QWERTY Embedded Design
 * Copyright (C) 2015 EMAC Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/input.h>
#समावेश <linux/of.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश "tsc200x-core.h"

अटल स्थिर काष्ठा input_id tsc2004_input_id = अणु
	.bustype = BUS_I2C,
	.product = 2004,
पूर्ण;

अटल पूर्णांक tsc2004_cmd(काष्ठा device *dev, u8 cmd)
अणु
	u8 tx = TSC200X_CMD | TSC200X_CMD_12BIT | cmd;
	s32 data;
	काष्ठा i2c_client *i2c = to_i2c_client(dev);

	data = i2c_smbus_ग_लिखो_byte(i2c, tx);
	अगर (data < 0) अणु
		dev_err(dev, "%s: failed, command: %x i2c error: %d\n",
			__func__, cmd, data);
		वापस data;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tsc2004_probe(काष्ठा i2c_client *i2c,
			 स्थिर काष्ठा i2c_device_id *id)

अणु
	वापस tsc200x_probe(&i2c->dev, i2c->irq, &tsc2004_input_id,
			     devm_regmap_init_i2c(i2c, &tsc200x_regmap_config),
			     tsc2004_cmd);
पूर्ण

अटल पूर्णांक tsc2004_हटाओ(काष्ठा i2c_client *i2c)
अणु
	वापस tsc200x_हटाओ(&i2c->dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tsc2004_idtable[] = अणु
	अणु "tsc2004", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tsc2004_idtable);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id tsc2004_of_match[] = अणु
	अणु .compatible = "ti,tsc2004" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tsc2004_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver tsc2004_driver = अणु
	.driver = अणु
		.name   = "tsc2004",
		.of_match_table = of_match_ptr(tsc2004_of_match),
		.pm     = &tsc200x_pm_ops,
	पूर्ण,
	.id_table       = tsc2004_idtable,
	.probe          = tsc2004_probe,
	.हटाओ         = tsc2004_हटाओ,
पूर्ण;
module_i2c_driver(tsc2004_driver);

MODULE_AUTHOR("Michael Welling <mwelling@ieee.org>");
MODULE_DESCRIPTION("TSC2004 Touchscreen Driver");
MODULE_LICENSE("GPL");
