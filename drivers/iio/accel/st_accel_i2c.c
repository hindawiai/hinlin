<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * STMicroelectronics accelerometers driver
 *
 * Copyright 2012-2013 STMicroelectronics Inc.
 *
 * Denis Ciocca <denis.ciocca@st.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/property.h>

#समावेश <linux/iio/common/st_sensors_i2c.h>
#समावेश "st_accel.h"

अटल स्थिर काष्ठा of_device_id st_accel_of_match[] = अणु
	अणु
		/* An older compatible */
		.compatible = "st,lis3lv02d",
		.data = LIS3LV02DL_ACCEL_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lis3lv02dl-accel",
		.data = LIS3LV02DL_ACCEL_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lsm303dlh-accel",
		.data = LSM303DLH_ACCEL_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lsm303dlhc-accel",
		.data = LSM303DLHC_ACCEL_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lis3dh-accel",
		.data = LIS3DH_ACCEL_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lsm330d-accel",
		.data = LSM330D_ACCEL_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lsm330dl-accel",
		.data = LSM330DL_ACCEL_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lsm330dlc-accel",
		.data = LSM330DLC_ACCEL_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lis331dl-accel",
		.data = LIS331DL_ACCEL_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lis331dlh-accel",
		.data = LIS331DLH_ACCEL_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lsm303dl-accel",
		.data = LSM303DL_ACCEL_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lsm303dlm-accel",
		.data = LSM303DLM_ACCEL_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lsm330-accel",
		.data = LSM330_ACCEL_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lsm303agr-accel",
		.data = LSM303AGR_ACCEL_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lis2dh12-accel",
		.data = LIS2DH12_ACCEL_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,h3lis331dl-accel",
		.data = H3LIS331DL_ACCEL_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lis3l02dq",
		.data = LIS3L02DQ_ACCEL_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lng2dm-accel",
		.data = LNG2DM_ACCEL_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lis2dw12",
		.data = LIS2DW12_ACCEL_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lis3de",
		.data = LIS3DE_ACCEL_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lis2de12",
		.data = LIS2DE12_ACCEL_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lis2hh12",
		.data = LIS2HH12_ACCEL_DEV_NAME,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, st_accel_of_match);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id st_accel_acpi_match[] = अणु
	अणु"SMO8840", (kernel_uदीर्घ_t)LIS2DH12_ACCEL_DEV_NAMEपूर्ण,
	अणु"SMO8A90", (kernel_uदीर्घ_t)LNG2DM_ACCEL_DEV_NAMEपूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, st_accel_acpi_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id st_accel_id_table[] = अणु
	अणु LSM303DLH_ACCEL_DEV_NAME पूर्ण,
	अणु LSM303DLHC_ACCEL_DEV_NAME पूर्ण,
	अणु LIS3DH_ACCEL_DEV_NAME पूर्ण,
	अणु LSM330D_ACCEL_DEV_NAME पूर्ण,
	अणु LSM330DL_ACCEL_DEV_NAME पूर्ण,
	अणु LSM330DLC_ACCEL_DEV_NAME पूर्ण,
	अणु LIS331DLH_ACCEL_DEV_NAME पूर्ण,
	अणु LSM303DL_ACCEL_DEV_NAME पूर्ण,
	अणु LSM303DLM_ACCEL_DEV_NAME पूर्ण,
	अणु LSM330_ACCEL_DEV_NAME पूर्ण,
	अणु LSM303AGR_ACCEL_DEV_NAME पूर्ण,
	अणु LIS2DH12_ACCEL_DEV_NAME पूर्ण,
	अणु LIS3L02DQ_ACCEL_DEV_NAME पूर्ण,
	अणु LNG2DM_ACCEL_DEV_NAME पूर्ण,
	अणु H3LIS331DL_ACCEL_DEV_NAME पूर्ण,
	अणु LIS331DL_ACCEL_DEV_NAME पूर्ण,
	अणु LIS3LV02DL_ACCEL_DEV_NAME पूर्ण,
	अणु LIS2DW12_ACCEL_DEV_NAME पूर्ण,
	अणु LIS3DE_ACCEL_DEV_NAME पूर्ण,
	अणु LIS2DE12_ACCEL_DEV_NAME पूर्ण,
	अणु LIS2HH12_ACCEL_DEV_NAME पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, st_accel_id_table);

अटल पूर्णांक st_accel_i2c_probe(काष्ठा i2c_client *client)
अणु
	स्थिर काष्ठा st_sensor_settings *settings;
	काष्ठा st_sensor_data *adata;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	st_sensors_dev_name_probe(&client->dev, client->name, माप(client->name));

	settings = st_accel_get_settings(client->name);
	अगर (!settings) अणु
		dev_err(&client->dev, "device name %s not recognized.\n",
			client->name);
		वापस -ENODEV;
	पूर्ण

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*adata));
	अगर (!indio_dev)
		वापस -ENOMEM;

	adata = iio_priv(indio_dev);
	adata->sensor_settings = (काष्ठा st_sensor_settings *)settings;

	ret = st_sensors_i2c_configure(indio_dev, client);
	अगर (ret < 0)
		वापस ret;

	ret = st_accel_common_probe(indio_dev);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक st_accel_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	st_accel_common_हटाओ(i2c_get_clientdata(client));

	वापस 0;
पूर्ण

अटल काष्ठा i2c_driver st_accel_driver = अणु
	.driver = अणु
		.name = "st-accel-i2c",
		.of_match_table = st_accel_of_match,
		.acpi_match_table = ACPI_PTR(st_accel_acpi_match),
	पूर्ण,
	.probe_new = st_accel_i2c_probe,
	.हटाओ = st_accel_i2c_हटाओ,
	.id_table = st_accel_id_table,
पूर्ण;
module_i2c_driver(st_accel_driver);

MODULE_AUTHOR("Denis Ciocca <denis.ciocca@st.com>");
MODULE_DESCRIPTION("STMicroelectronics accelerometers i2c driver");
MODULE_LICENSE("GPL v2");
