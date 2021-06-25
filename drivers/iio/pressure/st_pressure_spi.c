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
#समावेश <linux/spi/spi.h>
#समावेश <linux/iio/iपन.स>

#समावेश <linux/iio/common/st_sensors.h>
#समावेश <linux/iio/common/st_sensors_spi.h>
#समावेश "st_pressure.h"

/*
 * For new single-chip sensors use <device_name> as compatible string.
 * For old single-chip devices keep <device_name>-press to मुख्यtain
 * compatibility
 */
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

अटल पूर्णांक st_press_spi_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा st_sensor_settings *settings;
	काष्ठा st_sensor_data *press_data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक err;

	st_sensors_dev_name_probe(&spi->dev, spi->modalias, माप(spi->modalias));

	settings = st_press_get_settings(spi->modalias);
	अगर (!settings) अणु
		dev_err(&spi->dev, "device name %s not recognized.\n",
			spi->modalias);
		वापस -ENODEV;
	पूर्ण

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*press_data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	press_data = iio_priv(indio_dev);
	press_data->sensor_settings = (काष्ठा st_sensor_settings *)settings;

	err = st_sensors_spi_configure(indio_dev, spi);
	अगर (err < 0)
		वापस err;

	err = st_press_common_probe(indio_dev);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक st_press_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	st_press_common_हटाओ(spi_get_drvdata(spi));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id st_press_id_table[] = अणु
	अणु LPS001WP_PRESS_DEV_NAME पूर्ण,
	अणु LPS25H_PRESS_DEV_NAME पूर्ण,
	अणु LPS331AP_PRESS_DEV_NAME पूर्ण,
	अणु LPS22HB_PRESS_DEV_NAME पूर्ण,
	अणु LPS33HW_PRESS_DEV_NAME पूर्ण,
	अणु LPS35HW_PRESS_DEV_NAME पूर्ण,
	अणु LPS22HH_PRESS_DEV_NAME पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, st_press_id_table);

अटल काष्ठा spi_driver st_press_driver = अणु
	.driver = अणु
		.name = "st-press-spi",
		.of_match_table = st_press_of_match,
	पूर्ण,
	.probe = st_press_spi_probe,
	.हटाओ = st_press_spi_हटाओ,
	.id_table = st_press_id_table,
पूर्ण;
module_spi_driver(st_press_driver);

MODULE_AUTHOR("Denis Ciocca <denis.ciocca@st.com>");
MODULE_DESCRIPTION("STMicroelectronics pressures spi driver");
MODULE_LICENSE("GPL v2");
