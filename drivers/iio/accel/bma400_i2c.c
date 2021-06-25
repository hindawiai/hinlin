<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * I2C IIO driver क्रम Bosch BMA400 triaxial acceleration sensor.
 *
 * Copyright 2019 Dan Robertson <dan@dlrobertson.com>
 *
 * I2C address is either 0x14 or 0x15 depending on SDO
 */
#समावेश <linux/i2c.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>

#समावेश "bma400.h"

अटल पूर्णांक bma400_i2c_probe(काष्ठा i2c_client *client,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap *regmap;

	regmap = devm_regmap_init_i2c(client, &bma400_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&client->dev, "failed to create regmap\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	वापस bma400_probe(&client->dev, regmap, id->name);
पूर्ण

अटल पूर्णांक bma400_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	वापस bma400_हटाओ(&client->dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id bma400_i2c_ids[] = अणु
	अणु "bma400", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, bma400_i2c_ids);

अटल स्थिर काष्ठा of_device_id bma400_of_i2c_match[] = अणु
	अणु .compatible = "bosch,bma400" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, bma400_of_i2c_match);

अटल काष्ठा i2c_driver bma400_i2c_driver = अणु
	.driver = अणु
		.name = "bma400",
		.of_match_table = bma400_of_i2c_match,
	पूर्ण,
	.probe    = bma400_i2c_probe,
	.हटाओ   = bma400_i2c_हटाओ,
	.id_table = bma400_i2c_ids,
पूर्ण;

module_i2c_driver(bma400_i2c_driver);

MODULE_AUTHOR("Dan Robertson <dan@dlrobertson.com>");
MODULE_DESCRIPTION("Bosch BMA400 triaxial acceleration sensor (I2C)");
MODULE_LICENSE("GPL");
