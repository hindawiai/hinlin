<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * es8328.c  --  ES8328 ALSA SoC SPI Audio driver
 *
 * Copyright 2014 Sutajio Ko-Usagi PTE LTD
 *
 * Author: Sean Cross <xobs@kosagi.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>
#समावेश <sound/soc.h>
#समावेश "es8328.h"

अटल स्थिर काष्ठा of_device_id es8328_of_match[] = अणु
	अणु .compatible = "everest,es8328", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, es8328_of_match);

अटल पूर्णांक es8328_spi_probe(काष्ठा spi_device *spi)
अणु
	वापस es8328_probe(&spi->dev,
			devm_regmap_init_spi(spi, &es8328_regmap_config));
पूर्ण

अटल काष्ठा spi_driver es8328_spi_driver = अणु
	.driver = अणु
		.name		= "es8328",
		.of_match_table	= es8328_of_match,
	पूर्ण,
	.probe	= es8328_spi_probe,
पूर्ण;

module_spi_driver(es8328_spi_driver);
MODULE_DESCRIPTION("ASoC ES8328 audio CODEC SPI driver");
MODULE_AUTHOR("Sean Cross <xobs@kosagi.com>");
MODULE_LICENSE("GPL");
