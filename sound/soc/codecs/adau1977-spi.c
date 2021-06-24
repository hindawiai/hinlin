<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ADAU1977/ADAU1978/ADAU1979 driver
 *
 * Copyright 2014 Analog Devices Inc.
 *  Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <sound/soc.h>

#समावेश "adau1977.h"

अटल व्योम adau1977_spi_चयन_mode(काष्ठा device *dev)
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

अटल पूर्णांक adau1977_spi_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);
	काष्ठा regmap_config config;

	अगर (!id)
		वापस -EINVAL;

	config = adau1977_regmap_config;
	config.val_bits = 8;
	config.reg_bits = 16;
	config.पढ़ो_flag_mask = 0x1;

	वापस adau1977_probe(&spi->dev,
		devm_regmap_init_spi(spi, &config),
		id->driver_data, adau1977_spi_चयन_mode);
पूर्ण

अटल स्थिर काष्ठा spi_device_id adau1977_spi_ids[] = अणु
	अणु "adau1977", ADAU1977 पूर्ण,
	अणु "adau1978", ADAU1978 पूर्ण,
	अणु "adau1979", ADAU1978 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, adau1977_spi_ids);

अटल स्थिर काष्ठा of_device_id adau1977_spi_of_match[] = अणु
        अणु .compatible = "adi,adau1977" पूर्ण,
        अणु .compatible = "adi,adau1978" पूर्ण,
        अणु .compatible = "adi,adau1979" पूर्ण,
        अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, adau1977_spi_of_match);

अटल काष्ठा spi_driver adau1977_spi_driver = अणु
	.driver = अणु
		.name = "adau1977",
		.of_match_table = of_match_ptr(adau1977_spi_of_match),
	पूर्ण,
	.probe = adau1977_spi_probe,
	.id_table = adau1977_spi_ids,
पूर्ण;
module_spi_driver(adau1977_spi_driver);

MODULE_DESCRIPTION("ASoC ADAU1977/ADAU1978/ADAU1979 driver");
MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_LICENSE("GPL");
