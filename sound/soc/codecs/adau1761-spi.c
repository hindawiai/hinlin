<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम ADAU1361/ADAU1461/ADAU1761/ADAU1961 codec
 *
 * Copyright 2014 Analog Devices Inc.
 *  Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>
#समावेश <sound/soc.h>

#समावेश "adau1761.h"

अटल व्योम adau1761_spi_चयन_mode(काष्ठा device *dev)
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

अटल पूर्णांक adau1761_spi_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);
	काष्ठा regmap_config config;

	अगर (!id)
		वापस -EINVAL;

	config = adau1761_regmap_config;
	config.val_bits = 8;
	config.reg_bits = 24;
	config.पढ़ो_flag_mask = 0x1;

	वापस adau1761_probe(&spi->dev,
		devm_regmap_init_spi(spi, &config),
		id->driver_data, adau1761_spi_चयन_mode);
पूर्ण

अटल पूर्णांक adau1761_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	adau17x1_हटाओ(&spi->dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id adau1761_spi_id[] = अणु
	अणु "adau1361", ADAU1361 पूर्ण,
	अणु "adau1461", ADAU1761 पूर्ण,
	अणु "adau1761", ADAU1761 पूर्ण,
	अणु "adau1961", ADAU1361 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, adau1761_spi_id);

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id adau1761_spi_dt_ids[] = अणु
	अणु .compatible = "adi,adau1361", पूर्ण,
	अणु .compatible = "adi,adau1461", पूर्ण,
	अणु .compatible = "adi,adau1761", पूर्ण,
	अणु .compatible = "adi,adau1961", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, adau1761_spi_dt_ids);
#पूर्ण_अगर

अटल काष्ठा spi_driver adau1761_spi_driver = अणु
	.driver = अणु
		.name = "adau1761",
		.of_match_table = of_match_ptr(adau1761_spi_dt_ids),
	पूर्ण,
	.probe = adau1761_spi_probe,
	.हटाओ = adau1761_spi_हटाओ,
	.id_table = adau1761_spi_id,
पूर्ण;
module_spi_driver(adau1761_spi_driver);

MODULE_DESCRIPTION("ASoC ADAU1361/ADAU1461/ADAU1761/ADAU1961 CODEC SPI driver");
MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_LICENSE("GPL");
