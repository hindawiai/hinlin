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
#समावेश <linux/spi/spi.h>
#समावेश <linux/iio/iपन.स>

#समावेश <linux/iio/common/st_sensors.h>
#समावेश <linux/iio/common/st_sensors_spi.h>
#समावेश "st_accel.h"

/*
 * For new single-chip sensors use <device_name> as compatible string.
 * For old single-chip devices keep <device_name>-accel to मुख्यtain
 * compatibility
 */
अटल स्थिर काष्ठा of_device_id st_accel_of_match[] = अणु
	अणु
		/* An older compatible */
		.compatible = "st,lis302dl-spi",
		.data = LIS3LV02DL_ACCEL_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lis3lv02dl-accel",
		.data = LIS3LV02DL_ACCEL_DEV_NAME,
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
		.compatible = "st,lis331dlh-accel",
		.data = LIS331DLH_ACCEL_DEV_NAME,
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
		.compatible = "st,lis3l02dq",
		.data = LIS3L02DQ_ACCEL_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lng2dm-accel",
		.data = LNG2DM_ACCEL_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,h3lis331dl-accel",
		.data = H3LIS331DL_ACCEL_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lis331dl-accel",
		.data = LIS331DL_ACCEL_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lis2dw12",
		.data = LIS2DW12_ACCEL_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lis3dhh",
		.data = LIS3DHH_ACCEL_DEV_NAME,
	पूर्ण,
	अणु
		.compatible = "st,lis3de",
		.data = LIS3DE_ACCEL_DEV_NAME,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, st_accel_of_match);

अटल पूर्णांक st_accel_spi_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा st_sensor_settings *settings;
	काष्ठा st_sensor_data *adata;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक err;

	st_sensors_dev_name_probe(&spi->dev, spi->modalias, माप(spi->modalias));

	settings = st_accel_get_settings(spi->modalias);
	अगर (!settings) अणु
		dev_err(&spi->dev, "device name %s not recognized.\n",
			spi->modalias);
		वापस -ENODEV;
	पूर्ण

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*adata));
	अगर (!indio_dev)
		वापस -ENOMEM;

	adata = iio_priv(indio_dev);
	adata->sensor_settings = (काष्ठा st_sensor_settings *)settings;

	err = st_sensors_spi_configure(indio_dev, spi);
	अगर (err < 0)
		वापस err;

	err = st_accel_common_probe(indio_dev);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक st_accel_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	st_accel_common_हटाओ(spi_get_drvdata(spi));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id st_accel_id_table[] = अणु
	अणु LIS3DH_ACCEL_DEV_NAME पूर्ण,
	अणु LSM330D_ACCEL_DEV_NAME पूर्ण,
	अणु LSM330DL_ACCEL_DEV_NAME पूर्ण,
	अणु LSM330DLC_ACCEL_DEV_NAME पूर्ण,
	अणु LIS331DLH_ACCEL_DEV_NAME पूर्ण,
	अणु LSM330_ACCEL_DEV_NAME पूर्ण,
	अणु LSM303AGR_ACCEL_DEV_NAME पूर्ण,
	अणु LIS2DH12_ACCEL_DEV_NAME पूर्ण,
	अणु LIS3L02DQ_ACCEL_DEV_NAME पूर्ण,
	अणु LNG2DM_ACCEL_DEV_NAME पूर्ण,
	अणु H3LIS331DL_ACCEL_DEV_NAME पूर्ण,
	अणु LIS331DL_ACCEL_DEV_NAME पूर्ण,
	अणु LIS3LV02DL_ACCEL_DEV_NAME पूर्ण,
	अणु LIS2DW12_ACCEL_DEV_NAME पूर्ण,
	अणु LIS3DHH_ACCEL_DEV_NAME पूर्ण,
	अणु LIS3DE_ACCEL_DEV_NAME पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, st_accel_id_table);

अटल काष्ठा spi_driver st_accel_driver = अणु
	.driver = अणु
		.name = "st-accel-spi",
		.of_match_table = st_accel_of_match,
	पूर्ण,
	.probe = st_accel_spi_probe,
	.हटाओ = st_accel_spi_हटाओ,
	.id_table = st_accel_id_table,
पूर्ण;
module_spi_driver(st_accel_driver);

MODULE_AUTHOR("Denis Ciocca <denis.ciocca@st.com>");
MODULE_DESCRIPTION("STMicroelectronics accelerometers spi driver");
MODULE_LICENSE("GPL v2");
