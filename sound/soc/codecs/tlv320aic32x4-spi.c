<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * Copyright 2011-2019 NW Digital Radio
 *
 * Author: Annaliese McDermond <nh6z@nh6z.net>
 *
 * Based on sound/soc/codecs/wm8974 and TI driver क्रम kernel 2.6.27.
 *
 */

#समावेश <linux/spi/spi.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <sound/soc.h>

#समावेश "tlv320aic32x4.h"

अटल पूर्णांक aic32x4_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा regmap *regmap;
	काष्ठा regmap_config config;

	config = aic32x4_regmap_config;
	config.reg_bits = 7;
	config.pad_bits = 1;
	config.val_bits = 8;
	config.पढ़ो_flag_mask = 0x01;

	regmap = devm_regmap_init_spi(spi, &config);
	वापस aic32x4_probe(&spi->dev, regmap);
पूर्ण

अटल पूर्णांक aic32x4_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	वापस aic32x4_हटाओ(&spi->dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id aic32x4_spi_id[] = अणु
	अणु "tlv320aic32x4", 0 पूर्ण,
	अणु "tlv320aic32x6", 1 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, aic32x4_spi_id);

अटल स्थिर काष्ठा of_device_id aic32x4_of_id[] = अणु
	अणु .compatible = "ti,tlv320aic32x4", पूर्ण,
	अणु .compatible = "ti,tlv320aic32x6", पूर्ण,
	अणु /* senitel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, aic32x4_of_id);

अटल काष्ठा spi_driver aic32x4_spi_driver = अणु
	.driver = अणु
		.name = "tlv320aic32x4",
		.owner = THIS_MODULE,
		.of_match_table = aic32x4_of_id,
	पूर्ण,
	.probe =    aic32x4_spi_probe,
	.हटाओ =   aic32x4_spi_हटाओ,
	.id_table = aic32x4_spi_id,
पूर्ण;

module_spi_driver(aic32x4_spi_driver);

MODULE_DESCRIPTION("ASoC TLV320AIC32x4 codec driver SPI");
MODULE_AUTHOR("Annaliese McDermond <nh6z@nh6z.net>");
MODULE_LICENSE("GPL");
