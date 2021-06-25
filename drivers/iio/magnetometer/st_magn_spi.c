<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * STMicroelectronics magnetometers driver
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
#समावेश "st_magn.h"

/*
 * For new single-chip sensors use <device_name> as compatible string.
 * For old single-chip devices keep <device_name>-magn to मुख्यtain
 * compatibility
 * For multi-chip devices, use <device_name>-magn to distinguish which
 * capability is being used
 */
अटल स्थिर काष्ठा of_device_id st_magn_of_match[] = अणु
	अणु
		.compatible = "st,lis3mdl-magn",
		.data = LIS3MDL_MAGN_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lsm303agr-magn",
		.data = LSM303AGR_MAGN_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lis2mdl",
		.data = LIS2MDL_MAGN_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lsm9ds1-magn",
		.data = LSM9DS1_MAGN_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,iis2mdc",
		.data = IIS2MDC_MAGN_DEV_NAME,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, st_magn_of_match);

अटल पूर्णांक st_magn_spi_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा st_sensor_settings *settings;
	काष्ठा st_sensor_data *mdata;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक err;

	st_sensors_dev_name_probe(&spi->dev, spi->modalias, माप(spi->modalias));

	settings = st_magn_get_settings(spi->modalias);
	अगर (!settings) अणु
		dev_err(&spi->dev, "device name %s not recognized.\n",
			spi->modalias);
		वापस -ENODEV;
	पूर्ण

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*mdata));
	अगर (!indio_dev)
		वापस -ENOMEM;

	mdata = iio_priv(indio_dev);
	mdata->sensor_settings = (काष्ठा st_sensor_settings *)settings;

	err = st_sensors_spi_configure(indio_dev, spi);
	अगर (err < 0)
		वापस err;

	err = st_magn_common_probe(indio_dev);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक st_magn_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	st_magn_common_हटाओ(indio_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id st_magn_id_table[] = अणु
	अणु LIS3MDL_MAGN_DEV_NAME पूर्ण,
	अणु LSM303AGR_MAGN_DEV_NAME पूर्ण,
	अणु LIS2MDL_MAGN_DEV_NAME पूर्ण,
	अणु LSM9DS1_MAGN_DEV_NAME पूर्ण,
	अणु IIS2MDC_MAGN_DEV_NAME पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, st_magn_id_table);

अटल काष्ठा spi_driver st_magn_driver = अणु
	.driver = अणु
		.name = "st-magn-spi",
		.of_match_table = st_magn_of_match,
	पूर्ण,
	.probe = st_magn_spi_probe,
	.हटाओ = st_magn_spi_हटाओ,
	.id_table = st_magn_id_table,
पूर्ण;
module_spi_driver(st_magn_driver);

MODULE_AUTHOR("Denis Ciocca <denis.ciocca@st.com>");
MODULE_DESCRIPTION("STMicroelectronics magnetometers spi driver");
MODULE_LICENSE("GPL v2");
