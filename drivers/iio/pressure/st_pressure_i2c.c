<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * STMicroelectronics pressures driver
 *
 * Copyright 2013 STMicroelectronics Inc.
 *
 * Denis Ciocca <denis.ciocca@st.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/iio/iपन.स>

#समावेश <linux/iio/common/st_sensors.h>
#समावेश <linux/iio/common/st_sensors_i2c.h>
#समावेश "st_pressure.h"

अटल स्थिर काष्ठा of_device_id st_press_of_match[] = अणु
	अणु
		.compatible = "st,lps001wp-press",
		.data = LPS001WP_PRESS_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lps25h-press",
		.data = LPS25H_PRESS_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lps331ap-press",
		.data = LPS331AP_PRESS_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lps22hb-press",
		.data = LPS22HB_PRESS_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lps33hw",
		.data = LPS33HW_PRESS_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lps35hw",
		.data = LPS35HW_PRESS_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lps22hh",
		.data = LPS22HH_PRESS_DEV_NAME,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, st_press_of_match);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id st_press_acpi_match[] = अणु
	अणु"SNO9210", LPS22HBपूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, st_press_acpi_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id st_press_id_table[] = अणु
	अणु LPS001WP_PRESS_DEV_NAME, LPS001WP पूर्ण,
	अणु LPS25H_PRESS_DEV_NAME,  LPS25H पूर्ण,
	अणु LPS331AP_PRESS_DEV_NAME, LPS331AP पूर्ण,
	अणु LPS22HB_PRESS_DEV_NAME, LPS22HB पूर्ण,
	अणु LPS33HW_PRESS_DEV_NAME, LPS33HW पूर्ण,
	अणु LPS35HW_PRESS_DEV_NAME, LPS35HW पूर्ण,
	अणु LPS22HH_PRESS_DEV_NAME, LPS22HH पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, st_press_id_table);

अटल पूर्णांक st_press_i2c_probe(काष्ठा i2c_client *client,
			      स्थिर काष्ठा i2c_device_id *id)
अणु
	स्थिर काष्ठा st_sensor_settings *settings;
	काष्ठा st_sensor_data *press_data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	st_sensors_dev_name_probe(&client->dev, client->name, माप(client->name));

	settings = st_press_get_settings(client->name);
	अगर (!settings) अणु
		dev_err(&client->dev, "device name %s not recognized.\n",
			client->name);
		वापस -ENODEV;
	पूर्ण

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*press_data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	press_data = iio_priv(indio_dev);
	press_data->sensor_settings = (काष्ठा st_sensor_settings *)settings;

	ret = st_sensors_i2c_configure(indio_dev, client);
	अगर (ret < 0)
		वापस ret;

	ret = st_press_common_probe(indio_dev);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक st_press_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	st_press_common_हटाओ(i2c_get_clientdata(client));

	वापस 0;
पूर्ण

अटल काष्ठा i2c_driver st_press_driver = अणु
	.driver = अणु
		.name = "st-press-i2c",
		.of_match_table = st_press_of_match,
		.acpi_match_table = ACPI_PTR(st_press_acpi_match),
	पूर्ण,
	.probe = st_press_i2c_probe,
	.हटाओ = st_press_i2c_हटाओ,
	.id_table = st_press_id_table,
पूर्ण;
module_i2c_driver(st_press_driver);

MODULE_AUTHOR("Denis Ciocca <denis.ciocca@st.com>");
MODULE_DESCRIPTION("STMicroelectronics pressures i2c driver");
MODULE_LICENSE("GPL v2");
