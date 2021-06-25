<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ADXL345 3-Axis Digital Accelerometer SPI driver
 *
 * Copyright (c) 2017 Eva Rachel Retuya <eraretuya@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>

#समावेश "adxl345.h"

#घोषणा ADXL345_MAX_SPI_FREQ_HZ		5000000

अटल स्थिर काष्ठा regmap_config adxl345_spi_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	 /* Setting bits 7 and 6 enables multiple-byte पढ़ो */
	.पढ़ो_flag_mask = BIT(7) | BIT(6),
पूर्ण;

अटल पूर्णांक adxl345_spi_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);
	काष्ठा regmap *regmap;

	/* Bail out अगर max_speed_hz exceeds 5 MHz */
	अगर (spi->max_speed_hz > ADXL345_MAX_SPI_FREQ_HZ) अणु
		dev_err(&spi->dev, "SPI CLK, %d Hz exceeds 5 MHz\n",
			spi->max_speed_hz);
		वापस -EINVAL;
	पूर्ण

	regmap = devm_regmap_init_spi(spi, &adxl345_spi_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&spi->dev, "Error initializing spi regmap: %ld\n",
			PTR_ERR(regmap));
		वापस PTR_ERR(regmap);
	पूर्ण

	वापस adxl345_core_probe(&spi->dev, regmap, id->driver_data, id->name);
पूर्ण

अटल पूर्णांक adxl345_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	वापस adxl345_core_हटाओ(&spi->dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id adxl345_spi_id[] = अणु
	अणु "adxl345", ADXL345 पूर्ण,
	अणु "adxl375", ADXL375 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(spi, adxl345_spi_id);

अटल स्थिर काष्ठा of_device_id adxl345_of_match[] = अणु
	अणु .compatible = "adi,adxl345" पूर्ण,
	अणु .compatible = "adi,adxl375" पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, adxl345_of_match);

अटल काष्ठा spi_driver adxl345_spi_driver = अणु
	.driver = अणु
		.name	= "adxl345_spi",
		.of_match_table = adxl345_of_match,
	पूर्ण,
	.probe		= adxl345_spi_probe,
	.हटाओ		= adxl345_spi_हटाओ,
	.id_table	= adxl345_spi_id,
पूर्ण;

module_spi_driver(adxl345_spi_driver);

MODULE_AUTHOR("Eva Rachel Retuya <eraretuya@gmail.com>");
MODULE_DESCRIPTION("ADXL345 3-Axis Digital Accelerometer SPI driver");
MODULE_LICENSE("GPL v2");
