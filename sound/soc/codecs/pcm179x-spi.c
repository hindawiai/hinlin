<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PCM179X ASoC SPI driver
 *
 * Copyright (c) Amarula Solutions B.V. 2013
 *
 *     Michael Trimarchi <michael@amarulasolutions.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/regmap.h>

#समावेश "pcm179x.h"

अटल पूर्णांक pcm179x_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	regmap = devm_regmap_init_spi(spi, &pcm179x_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		ret = PTR_ERR(regmap);
		dev_err(&spi->dev, "Failed to allocate regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस pcm179x_common_init(&spi->dev, regmap);
पूर्ण

अटल स्थिर काष्ठा of_device_id pcm179x_of_match[] = अणु
	अणु .compatible = "ti,pcm1792a", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pcm179x_of_match);

अटल स्थिर काष्ठा spi_device_id pcm179x_spi_ids[] = अणु
	अणु "pcm179x", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, pcm179x_spi_ids);

अटल काष्ठा spi_driver pcm179x_spi_driver = अणु
	.driver = अणु
		.name = "pcm179x",
		.of_match_table = of_match_ptr(pcm179x_of_match),
	पूर्ण,
	.id_table = pcm179x_spi_ids,
	.probe = pcm179x_spi_probe,
पूर्ण;

module_spi_driver(pcm179x_spi_driver);

MODULE_DESCRIPTION("ASoC PCM179X SPI driver");
MODULE_AUTHOR("Michael Trimarchi <michael@amarulasolutions.com>");
MODULE_LICENSE("GPL");
