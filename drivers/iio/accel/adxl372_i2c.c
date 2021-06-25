<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ADXL372 3-Axis Digital Accelerometer I2C driver
 *
 * Copyright 2018 Analog Devices Inc.
 */

#समावेश <linux/i2c.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>

#समावेश "adxl372.h"

अटल स्थिर काष्ठा regmap_config adxl372_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.पढ़ोable_noinc_reg = adxl372_पढ़ोable_noinc_reg,
पूर्ण;

अटल पूर्णांक adxl372_i2c_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	regmap = devm_regmap_init_i2c(client, &adxl372_regmap_config);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	ret = regmap_पढ़ो(regmap, ADXL372_REVID, &regval);
	अगर (ret < 0)
		वापस ret;

	/* Starting with the 3rd revision an I2C chip bug was fixed */
	अगर (regval < 3)
		dev_warn(&client->dev,
		"I2C might not work properly with other devices on the bus");

	वापस adxl372_probe(&client->dev, regmap, client->irq, id->name);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id adxl372_i2c_id[] = अणु
	अणु "adxl372", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adxl372_i2c_id);

अटल स्थिर काष्ठा of_device_id adxl372_of_match[] = अणु
	अणु .compatible = "adi,adxl372" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, adxl372_of_match);

अटल काष्ठा i2c_driver adxl372_i2c_driver = अणु
	.driver = अणु
		.name = "adxl372_i2c",
		.of_match_table = adxl372_of_match,
	पूर्ण,
	.probe = adxl372_i2c_probe,
	.id_table = adxl372_i2c_id,
पूर्ण;

module_i2c_driver(adxl372_i2c_driver);

MODULE_AUTHOR("Stefan Popa <stefan.popa@analog.com>");
MODULE_DESCRIPTION("Analog Devices ADXL372 3-axis accelerometer I2C driver");
MODULE_LICENSE("GPL");
