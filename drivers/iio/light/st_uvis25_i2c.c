<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * STMicroelectronics uvis25 i2c driver
 *
 * Copyright 2017 STMicroelectronics Inc.
 *
 * Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/regmap.h>

#समावेश "st_uvis25.h"

#घोषणा UVIS25_I2C_AUTO_INCREMENT	BIT(7)

अटल स्थिर काष्ठा regmap_config st_uvis25_i2c_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.ग_लिखो_flag_mask = UVIS25_I2C_AUTO_INCREMENT,
	.पढ़ो_flag_mask = UVIS25_I2C_AUTO_INCREMENT,
पूर्ण;

अटल पूर्णांक st_uvis25_i2c_probe(काष्ठा i2c_client *client,
			       स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap *regmap;

	regmap = devm_regmap_init_i2c(client, &st_uvis25_i2c_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&client->dev, "Failed to register i2c regmap %ld\n",
			PTR_ERR(regmap));
		वापस PTR_ERR(regmap);
	पूर्ण

	वापस st_uvis25_probe(&client->dev, client->irq, regmap);
पूर्ण

अटल स्थिर काष्ठा of_device_id st_uvis25_i2c_of_match[] = अणु
	अणु .compatible = "st,uvis25", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, st_uvis25_i2c_of_match);

अटल स्थिर काष्ठा i2c_device_id st_uvis25_i2c_id_table[] = अणु
	अणु ST_UVIS25_DEV_NAME पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, st_uvis25_i2c_id_table);

अटल काष्ठा i2c_driver st_uvis25_driver = अणु
	.driver = अणु
		.name = "st_uvis25_i2c",
		.pm = &st_uvis25_pm_ops,
		.of_match_table = st_uvis25_i2c_of_match,
	पूर्ण,
	.probe = st_uvis25_i2c_probe,
	.id_table = st_uvis25_i2c_id_table,
पूर्ण;
module_i2c_driver(st_uvis25_driver);

MODULE_AUTHOR("Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>");
MODULE_DESCRIPTION("STMicroelectronics uvis25 i2c driver");
MODULE_LICENSE("GPL v2");
