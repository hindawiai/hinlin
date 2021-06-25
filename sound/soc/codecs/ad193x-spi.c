<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AD1938/AD1939 audio driver
 *
 * Copyright 2014 Analog Devices Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/regmap.h>

#समावेश <sound/soc.h>

#समावेश "ad193x.h"

अटल पूर्णांक ad193x_spi_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);
	काष्ठा regmap_config config;

	config = ad193x_regmap_config;
	config.val_bits = 8;
	config.reg_bits = 16;
	config.पढ़ो_flag_mask = 0x09;
	config.ग_लिखो_flag_mask = 0x08;

	वापस ad193x_probe(&spi->dev, devm_regmap_init_spi(spi, &config),
			    (क्रमागत ad193x_type)id->driver_data);
पूर्ण

अटल स्थिर काष्ठा spi_device_id ad193x_spi_id[] = अणु
	अणु "ad193x", AD193X पूर्ण,
	अणु "ad1933", AD1933 पूर्ण,
	अणु "ad1934", AD1934 पूर्ण,
	अणु "ad1938", AD193X पूर्ण,
	अणु "ad1939", AD193X पूर्ण,
	अणु "adau1328", AD193X पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad193x_spi_id);

अटल काष्ठा spi_driver ad193x_spi_driver = अणु
	.driver = अणु
		.name	= "ad193x",
	पूर्ण,
	.probe		= ad193x_spi_probe,
	.id_table	= ad193x_spi_id,
पूर्ण;
module_spi_driver(ad193x_spi_driver);

MODULE_DESCRIPTION("ASoC AD1938/AD1939 audio CODEC driver");
MODULE_AUTHOR("Barry Song <21cnbao@gmail.com>");
MODULE_LICENSE("GPL");
