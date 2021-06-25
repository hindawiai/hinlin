<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>

#समावेश "bmp280.h"

अटल पूर्णांक bmp280_i2c_probe(काष्ठा i2c_client *client,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap *regmap;
	स्थिर काष्ठा regmap_config *regmap_config;

	चयन (id->driver_data) अणु
	हाल BMP180_CHIP_ID:
		regmap_config = &bmp180_regmap_config;
		अवरोध;
	हाल BMP280_CHIP_ID:
	हाल BME280_CHIP_ID:
		regmap_config = &bmp280_regmap_config;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap = devm_regmap_init_i2c(client, regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&client->dev, "failed to allocate register map\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	वापस bmp280_common_probe(&client->dev,
				   regmap,
				   id->driver_data,
				   id->name,
				   client->irq);
पूर्ण

अटल स्थिर काष्ठा of_device_id bmp280_of_i2c_match[] = अणु
	अणु .compatible = "bosch,bme280", .data = (व्योम *)BME280_CHIP_ID पूर्ण,
	अणु .compatible = "bosch,bmp280", .data = (व्योम *)BMP280_CHIP_ID पूर्ण,
	अणु .compatible = "bosch,bmp180", .data = (व्योम *)BMP180_CHIP_ID पूर्ण,
	अणु .compatible = "bosch,bmp085", .data = (व्योम *)BMP180_CHIP_ID पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bmp280_of_i2c_match);

अटल स्थिर काष्ठा i2c_device_id bmp280_i2c_id[] = अणु
	अणु"bmp280", BMP280_CHIP_ID पूर्ण,
	अणु"bmp180", BMP180_CHIP_ID पूर्ण,
	अणु"bmp085", BMP180_CHIP_ID पूर्ण,
	अणु"bme280", BME280_CHIP_ID पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, bmp280_i2c_id);

अटल काष्ठा i2c_driver bmp280_i2c_driver = अणु
	.driver = अणु
		.name	= "bmp280",
		.of_match_table = bmp280_of_i2c_match,
		.pm = &bmp280_dev_pm_ops,
	पूर्ण,
	.probe		= bmp280_i2c_probe,
	.id_table	= bmp280_i2c_id,
पूर्ण;
module_i2c_driver(bmp280_i2c_driver);

MODULE_AUTHOR("Vlad Dogaru <vlad.dogaru@intel.com>");
MODULE_DESCRIPTION("Driver for Bosch Sensortec BMP180/BMP280 pressure and temperature sensor");
MODULE_LICENSE("GPL v2");
