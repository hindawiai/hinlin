<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * STMicroelectronics sensors i2c library driver
 *
 * Copyright 2012-2013 STMicroelectronics Inc.
 *
 * Denis Ciocca <denis.ciocca@st.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/regmap.h>

#समावेश <linux/iio/common/st_sensors_i2c.h>


#घोषणा ST_SENSORS_I2C_MULTIREAD	0x80

अटल स्थिर काष्ठा regmap_config st_sensors_i2c_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल स्थिर काष्ठा regmap_config st_sensors_i2c_regmap_multiपढ़ो_bit_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.पढ़ो_flag_mask = ST_SENSORS_I2C_MULTIREAD,
पूर्ण;

/*
 * st_sensors_i2c_configure() - configure I2C पूर्णांकerface
 * @indio_dev: IIO device reference.
 * @client: i2c client reference.
 *
 * Return: 0 on success, अन्यथा a negative error code.
 */
पूर्णांक st_sensors_i2c_configure(काष्ठा iio_dev *indio_dev,
			     काष्ठा i2c_client *client)
अणु
	काष्ठा st_sensor_data *sdata = iio_priv(indio_dev);
	स्थिर काष्ठा regmap_config *config;

	अगर (sdata->sensor_settings->multi_पढ़ो_bit)
		config = &st_sensors_i2c_regmap_multiपढ़ो_bit_config;
	अन्यथा
		config = &st_sensors_i2c_regmap_config;

	sdata->regmap = devm_regmap_init_i2c(client, config);
	अगर (IS_ERR(sdata->regmap)) अणु
		dev_err(&client->dev, "Failed to register i2c regmap (%ld)\n",
			PTR_ERR(sdata->regmap));
		वापस PTR_ERR(sdata->regmap);
	पूर्ण

	i2c_set_clientdata(client, indio_dev);

	indio_dev->name = client->name;

	sdata->dev = &client->dev;
	sdata->irq = client->irq;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(st_sensors_i2c_configure);

MODULE_AUTHOR("Denis Ciocca <denis.ciocca@st.com>");
MODULE_DESCRIPTION("STMicroelectronics ST-sensors i2c driver");
MODULE_LICENSE("GPL v2");
