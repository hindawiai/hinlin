<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ALSA SoC TLV320AIC23 codec driver SPI पूर्णांकerface
 *
 * Author:      Arun KS, <arunks@mistralsolutions.com>
 * Copyright:   (C) 2008 Mistral Solutions Pvt Ltd.,
 *
 * Based on sound/soc/codecs/wm8731.c by Riअक्षरd Purdie
 */

#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>
#समावेश <sound/soc.h>

#समावेश "tlv320aic23.h"

अटल पूर्णांक aic23_spi_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret;
	काष्ठा regmap *regmap;

	dev_dbg(&spi->dev, "probing tlv320aic23 spi device\n");

	spi->mode = SPI_MODE_0;
	ret = spi_setup(spi);
	अगर (ret < 0)
		वापस ret;

	regmap = devm_regmap_init_spi(spi, &tlv320aic23_regmap);
	वापस tlv320aic23_probe(&spi->dev, regmap);
पूर्ण

अटल काष्ठा spi_driver aic23_spi = अणु
	.driver = अणु
		.name = "tlv320aic23",
	पूर्ण,
	.probe = aic23_spi_probe,
पूर्ण;

module_spi_driver(aic23_spi);

MODULE_DESCRIPTION("ASoC TLV320AIC23 codec driver SPI");
MODULE_AUTHOR("Arun KS <arunks@mistralsolutions.com>");
MODULE_LICENSE("GPL");
