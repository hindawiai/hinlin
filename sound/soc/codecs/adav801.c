<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ADAV801 audio driver
 *
 * Copyright 2014 Analog Devices Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/regmap.h>

#समावेश <sound/soc.h>

#समावेश "adav80x.h"

अटल स्थिर काष्ठा spi_device_id adav80x_spi_id[] = अणु
	अणु "adav801", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, adav80x_spi_id);

अटल पूर्णांक adav80x_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा regmap_config config;

	config = adav80x_regmap_config;
	config.पढ़ो_flag_mask = 0x01;

	वापस adav80x_bus_probe(&spi->dev, devm_regmap_init_spi(spi, &config));
पूर्ण

अटल काष्ठा spi_driver adav80x_spi_driver = अणु
	.driver = अणु
		.name	= "adav801",
	पूर्ण,
	.probe		= adav80x_spi_probe,
	.id_table	= adav80x_spi_id,
पूर्ण;
module_spi_driver(adav80x_spi_driver);

MODULE_DESCRIPTION("ASoC ADAV801 driver");
MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_AUTHOR("Yi Li <yi.li@analog.com>>");
MODULE_LICENSE("GPL");
