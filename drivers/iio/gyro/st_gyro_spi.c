<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * STMicroelectronics gyroscopes driver
 *
 * Copyright 2012-2013 STMicroelectronics Inc.
 *
 * Denis Ciocca <denis.ciocca@st.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/iio/iपन.स>

#समावेश <linux/iio/common/st_sensors.h>
#समावेश <linux/iio/common/st_sensors_spi.h>
#समावेश "st_gyro.h"

/*
 * For new single-chip sensors use <device_name> as compatible string.
 * For old single-chip devices keep <device_name>-gyro to मुख्यtain
 * compatibility
 */
अटल स्थिर काष्ठा of_device_id st_gyro_of_match[] = अणु
	अणु
		.compatible = "st,l3g4200d-gyro",
		.data = L3G4200D_GYRO_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lsm330d-gyro",
		.data = LSM330D_GYRO_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lsm330dl-gyro",
		.data = LSM330DL_GYRO_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lsm330dlc-gyro",
		.data = LSM330DLC_GYRO_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,l3gd20-gyro",
		.data = L3GD20_GYRO_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,l3gd20h-gyro",
		.data = L3GD20H_GYRO_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,l3g4is-gyro",
		.data = L3G4IS_GYRO_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lsm330-gyro",
		.data = LSM330_GYRO_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lsm9ds0-gyro",
		.data = LSM9DS0_GYRO_DEV_NAME,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, st_gyro_of_match);

अटल पूर्णांक st_gyro_spi_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा st_sensor_settings *settings;
	काष्ठा st_sensor_data *gdata;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक err;

	st_sensors_dev_name_probe(&spi->dev, spi->modalias, माप(spi->modalias));

	settings = st_gyro_get_settings(spi->modalias);
	अगर (!settings) अणु
		dev_err(&spi->dev, "device name %s not recognized.\n",
			spi->modalias);
		वापस -ENODEV;
	पूर्ण

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*gdata));
	अगर (!indio_dev)
		वापस -ENOMEM;

	gdata = iio_priv(indio_dev);
	gdata->sensor_settings = (काष्ठा st_sensor_settings *)settings;

	err = st_sensors_spi_configure(indio_dev, spi);
	अगर (err < 0)
		वापस err;

	err = st_gyro_common_probe(indio_dev);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक st_gyro_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	st_gyro_common_हटाओ(spi_get_drvdata(spi));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id st_gyro_id_table[] = अणु
	अणु L3G4200D_GYRO_DEV_NAME पूर्ण,
	अणु LSM330D_GYRO_DEV_NAME पूर्ण,
	अणु LSM330DL_GYRO_DEV_NAME पूर्ण,
	अणु LSM330DLC_GYRO_DEV_NAME पूर्ण,
	अणु L3GD20_GYRO_DEV_NAME पूर्ण,
	अणु L3GD20H_GYRO_DEV_NAME पूर्ण,
	अणु L3G4IS_GYRO_DEV_NAME पूर्ण,
	अणु LSM330_GYRO_DEV_NAME पूर्ण,
	अणु LSM9DS0_GYRO_DEV_NAME पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, st_gyro_id_table);

अटल काष्ठा spi_driver st_gyro_driver = अणु
	.driver = अणु
		.name = "st-gyro-spi",
		.of_match_table = st_gyro_of_match,
	पूर्ण,
	.probe = st_gyro_spi_probe,
	.हटाओ = st_gyro_spi_हटाओ,
	.id_table = st_gyro_id_table,
पूर्ण;
module_spi_driver(st_gyro_driver);

MODULE_AUTHOR("Denis Ciocca <denis.ciocca@st.com>");
MODULE_DESCRIPTION("STMicroelectronics gyroscopes spi driver");
MODULE_LICENSE("GPL v2");
