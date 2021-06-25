<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ADXL372 3-Axis Digital Accelerometer SPI driver
 *
 * Copyright 2018 Analog Devices Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/spi/spi.h>

#समावेश "adxl372.h"

अटल स्थिर काष्ठा regmap_config adxl372_spi_regmap_config = अणु
	.reg_bits = 7,
	.pad_bits = 1,
	.val_bits = 8,
	.पढ़ो_flag_mask = BIT(0),
	.पढ़ोable_noinc_reg = adxl372_पढ़ोable_noinc_reg,
पूर्ण;

अटल पूर्णांक adxl372_spi_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);
	काष्ठा regmap *regmap;

	regmap = devm_regmap_init_spi(spi, &adxl372_spi_regmap_config);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	वापस adxl372_probe(&spi->dev, regmap, spi->irq, id->name);
पूर्ण

अटल स्थिर काष्ठा spi_device_id adxl372_spi_id[] = अणु
	अणु "adxl372", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, adxl372_spi_id);

अटल स्थिर काष्ठा of_device_id adxl372_of_match[] = अणु
	अणु .compatible = "adi,adxl372" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, adxl372_of_match);

अटल काष्ठा spi_driver adxl372_spi_driver = अणु
	.driver = अणु
		.name = "adxl372_spi",
		.of_match_table = adxl372_of_match,
	पूर्ण,
	.probe = adxl372_spi_probe,
	.id_table = adxl372_spi_id,
पूर्ण;

module_spi_driver(adxl372_spi_driver);

MODULE_AUTHOR("Stefan Popa <stefan.popa@analog.com>");
MODULE_DESCRIPTION("Analog Devices ADXL372 3-axis accelerometer SPI driver");
MODULE_LICENSE("GPL");
