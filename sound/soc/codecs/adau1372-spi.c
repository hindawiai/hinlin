<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम ADAU1372 codec
 *
 * Copyright 2016 Analog Devices Inc.
 *  Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>
#समावेश <sound/soc.h>

#समावेश "adau1372.h"

अटल व्योम adau1372_spi_चयन_mode(काष्ठा device *dev)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);

	/*
	 * To get the device पूर्णांकo SPI mode CLATCH has to be pulled low three
	 * बार.  Do this by issuing three dummy पढ़ोs.
	 */
	spi_w8r8(spi, 0x00);
	spi_w8r8(spi, 0x00);
	spi_w8r8(spi, 0x00);
पूर्ण

अटल पूर्णांक adau1372_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा regmap_config config;

	config = adau1372_regmap_config;
	config.पढ़ो_flag_mask = 0x1;

	वापस adau1372_probe(&spi->dev,
		devm_regmap_init_spi(spi, &config), adau1372_spi_चयन_mode);
पूर्ण

अटल स्थिर काष्ठा spi_device_id adau1372_spi_id[] = अणु
	अणु "adau1372", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, adau1372_spi_id);

अटल काष्ठा spi_driver adau1372_spi_driver = अणु
	.driver = अणु
		.name = "adau1372",
	पूर्ण,
	.probe = adau1372_spi_probe,
	.id_table = adau1372_spi_id,
पूर्ण;
module_spi_driver(adau1372_spi_driver);

MODULE_DESCRIPTION("ASoC ADAU1372 CODEC SPI driver");
MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_LICENSE("GPL v2");
