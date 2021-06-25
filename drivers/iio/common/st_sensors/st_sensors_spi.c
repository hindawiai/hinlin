<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * STMicroelectronics sensors spi library driver
 *
 * Copyright 2012-2013 STMicroelectronics Inc.
 *
 * Denis Ciocca <denis.ciocca@st.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>

#समावेश <linux/iio/common/st_sensors_spi.h>
#समावेश "st_sensors_core.h"

#घोषणा ST_SENSORS_SPI_MULTIREAD	0xc0

अटल स्थिर काष्ठा regmap_config st_sensors_spi_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल स्थिर काष्ठा regmap_config st_sensors_spi_regmap_multiपढ़ो_bit_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.पढ़ो_flag_mask = ST_SENSORS_SPI_MULTIREAD,
पूर्ण;

/*
 * st_sensors_is_spi_3_wire() - check अगर SPI 3-wire mode has been selected
 * @spi: spi device reference.
 *
 * Return: true अगर SPI 3-wire mode is selected, false otherwise.
 */
अटल bool st_sensors_is_spi_3_wire(काष्ठा spi_device *spi)
अणु
	काष्ठा st_sensors_platक्रमm_data *pdata;
	काष्ठा device *dev = &spi->dev;

	अगर (device_property_पढ़ो_bool(dev, "spi-3wire"))
		वापस true;

	pdata = dev_get_platdata(dev);
	अगर (pdata && pdata->spi_3wire)
		वापस true;

	वापस false;
पूर्ण

/*
 * st_sensors_configure_spi_3_wire() - configure SPI 3-wire अगर needed
 * @spi: spi device reference.
 * @settings: sensor specअगरic settings reference.
 *
 * Return: 0 on success, अन्यथा a negative error code.
 */
अटल पूर्णांक st_sensors_configure_spi_3_wire(काष्ठा spi_device *spi,
					   काष्ठा st_sensor_settings *settings)
अणु
	अगर (settings->sim.addr) अणु
		u8 buffer[] = अणु
			settings->sim.addr,
			settings->sim.value
		पूर्ण;

		वापस spi_ग_लिखो(spi, buffer, 2);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * st_sensors_spi_configure() - configure SPI पूर्णांकerface
 * @indio_dev: IIO device reference.
 * @spi: spi device reference.
 *
 * Return: 0 on success, अन्यथा a negative error code.
 */
पूर्णांक st_sensors_spi_configure(काष्ठा iio_dev *indio_dev,
			     काष्ठा spi_device *spi)
अणु
	काष्ठा st_sensor_data *sdata = iio_priv(indio_dev);
	स्थिर काष्ठा regmap_config *config;
	पूर्णांक err;

	अगर (st_sensors_is_spi_3_wire(spi)) अणु
		err = st_sensors_configure_spi_3_wire(spi,
						      sdata->sensor_settings);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (sdata->sensor_settings->multi_पढ़ो_bit)
		config = &st_sensors_spi_regmap_multiपढ़ो_bit_config;
	अन्यथा
		config = &st_sensors_spi_regmap_config;

	sdata->regmap = devm_regmap_init_spi(spi, config);
	अगर (IS_ERR(sdata->regmap)) अणु
		dev_err(&spi->dev, "Failed to register spi regmap (%ld)\n",
			PTR_ERR(sdata->regmap));
		वापस PTR_ERR(sdata->regmap);
	पूर्ण

	spi_set_drvdata(spi, indio_dev);

	indio_dev->name = spi->modalias;

	sdata->dev = &spi->dev;
	sdata->irq = spi->irq;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(st_sensors_spi_configure);

MODULE_AUTHOR("Denis Ciocca <denis.ciocca@st.com>");
MODULE_DESCRIPTION("STMicroelectronics ST-sensors spi driver");
MODULE_LICENSE("GPL v2");
