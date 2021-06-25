<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * ALSA SoC TLV320AIC3x codec driver SPI पूर्णांकerface
 *
 * Author:      Arun KS, <arunks@mistralsolutions.com>
 * Copyright:   (C) 2008 Mistral Solutions Pvt Ltd.,
 *
 * Based on sound/soc/codecs/wm8731.c by Riअक्षरd Purdie
 *
 */

#समावेश <linux/spi/spi.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <sound/soc.h>

#समावेश "tlv320aic3x.h"

अटल पूर्णांक aic3x_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा regmap *regmap;
	काष्ठा regmap_config config;
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);

	config = aic3x_regmap;
	config.reg_bits = 7;
	config.pad_bits = 1;
	config.val_bits = 8;
	config.पढ़ो_flag_mask = 0x01;

	dev_dbg(&spi->dev, "probing tlv320aic3x spi device\n");

	regmap = devm_regmap_init_spi(spi, &config);
	वापस aic3x_probe(&spi->dev, regmap, id->driver_data);
पूर्ण

अटल पूर्णांक aic3x_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	वापस aic3x_हटाओ(&spi->dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id aic3x_spi_id[] = अणु
	अणु "tlv320aic3x", AIC3X_MODEL_3X पूर्ण,
	अणु "tlv320aic33", AIC3X_MODEL_33 पूर्ण,
	अणु "tlv320aic3007", AIC3X_MODEL_3007 पूर्ण,
	अणु "tlv320aic3104", AIC3X_MODEL_3104 पूर्ण,
	अणु "tlv320aic3106", AIC3X_MODEL_3106 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, aic3x_spi_id);

अटल स्थिर काष्ठा of_device_id aic3x_of_id[] = अणु
	अणु .compatible = "ti,tlv320aic3x", पूर्ण,
	अणु .compatible = "ti,tlv320aic33" पूर्ण,
	अणु .compatible = "ti,tlv320aic3007" पूर्ण,
	अणु .compatible = "ti,tlv320aic3104" पूर्ण,
	अणु .compatible = "ti,tlv320aic3106" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, aic3x_of_id);

अटल काष्ठा spi_driver aic3x_spi_driver = अणु
	.driver = अणु
		.name = "tlv320aic3x",
		.owner = THIS_MODULE,
		.of_match_table = aic3x_of_id,
	पूर्ण,
	.probe = aic3x_spi_probe,
	.हटाओ = aic3x_spi_हटाओ,
	.id_table = aic3x_spi_id,
पूर्ण;

module_spi_driver(aic3x_spi_driver);

MODULE_DESCRIPTION("ASoC TLV320AIC3x codec driver SPI");
MODULE_AUTHOR("Arun KS <arunks@mistralsolutions.com>");
MODULE_LICENSE("GPL");
