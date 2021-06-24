<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * AD7879-1/AD7889-1 touchscreen (I2C bus)
 *
 * Copyright (C) 2008-2010 Michael Hennerich, Analog Devices Inc.
 */

#समावेश <linux/input.h>	/* BUS_I2C */
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/of.h>
#समावेश <linux/pm.h>
#समावेश <linux/regmap.h>

#समावेश "ad7879.h"

#घोषणा AD7879_DEVID		0x79	/* AD7879-1/AD7889-1 */

अटल स्थिर काष्ठा regmap_config ad7879_i2c_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 16,
	.max_रेजिस्टर = 15,
पूर्ण;

अटल पूर्णांक ad7879_i2c_probe(काष्ठा i2c_client *client,
				      स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap *regmap;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_WORD_DATA)) अणु
		dev_err(&client->dev, "SMBUS Word Data not Supported\n");
		वापस -EIO;
	पूर्ण

	regmap = devm_regmap_init_i2c(client, &ad7879_i2c_regmap_config);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	वापस ad7879_probe(&client->dev, regmap, client->irq,
			    BUS_I2C, AD7879_DEVID);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ad7879_id[] = अणु
	अणु "ad7879", 0 पूर्ण,
	अणु "ad7889", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ad7879_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id ad7879_i2c_dt_ids[] = अणु
	अणु .compatible = "adi,ad7879-1", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ad7879_i2c_dt_ids);
#पूर्ण_अगर

अटल काष्ठा i2c_driver ad7879_i2c_driver = अणु
	.driver = अणु
		.name	= "ad7879",
		.pm	= &ad7879_pm_ops,
		.of_match_table = of_match_ptr(ad7879_i2c_dt_ids),
	पूर्ण,
	.probe		= ad7879_i2c_probe,
	.id_table	= ad7879_id,
पूर्ण;

module_i2c_driver(ad7879_i2c_driver);

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("AD7879(-1) touchscreen I2C bus driver");
MODULE_LICENSE("GPL");
