<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// PCM3060 SPI driver
//
// Copyright (C) 2018 Kirill Marinushkin <kmarinushkin@birdec.com>

#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>
#समावेश <sound/soc.h>

#समावेश "pcm3060.h"

अटल पूर्णांक pcm3060_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा pcm3060_priv *priv;

	priv = devm_kzalloc(&spi->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	spi_set_drvdata(spi, priv);

	priv->regmap = devm_regmap_init_spi(spi, &pcm3060_regmap);
	अगर (IS_ERR(priv->regmap))
		वापस PTR_ERR(priv->regmap);

	वापस pcm3060_probe(&spi->dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id pcm3060_spi_id[] = अणु
	अणु .name = "pcm3060" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, pcm3060_spi_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id pcm3060_of_match[] = अणु
	अणु .compatible = "ti,pcm3060" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, pcm3060_of_match);
#पूर्ण_अगर /* CONFIG_OF */

अटल काष्ठा spi_driver pcm3060_spi_driver = अणु
	.driver = अणु
		.name = "pcm3060",
#अगर_घोषित CONFIG_OF
		.of_match_table = pcm3060_of_match,
#पूर्ण_अगर /* CONFIG_OF */
	पूर्ण,
	.id_table = pcm3060_spi_id,
	.probe = pcm3060_spi_probe,
पूर्ण;

module_spi_driver(pcm3060_spi_driver);

MODULE_DESCRIPTION("PCM3060 SPI driver");
MODULE_AUTHOR("Kirill Marinushkin <kmarinushkin@birdec.com>");
MODULE_LICENSE("GPL v2");
