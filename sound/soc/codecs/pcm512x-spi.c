<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम the PCM512x CODECs
 *
 * Author:	Mark Brown <broonie@kernel.org>
 *		Copyright 2014 Linaro Ltd
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>

#समावेश "pcm512x.h"

अटल पूर्णांक pcm512x_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	regmap = devm_regmap_init_spi(spi, &pcm512x_regmap);
	अगर (IS_ERR(regmap)) अणु
		ret = PTR_ERR(regmap);
		वापस ret;
	पूर्ण

	वापस pcm512x_probe(&spi->dev, regmap);
पूर्ण

अटल पूर्णांक pcm512x_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	pcm512x_हटाओ(&spi->dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id pcm512x_spi_id[] = अणु
	अणु "pcm5121", पूर्ण,
	अणु "pcm5122", पूर्ण,
	अणु "pcm5141", पूर्ण,
	अणु "pcm5142", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, pcm512x_spi_id);

अटल स्थिर काष्ठा of_device_id pcm512x_of_match[] = अणु
	अणु .compatible = "ti,pcm5121", पूर्ण,
	अणु .compatible = "ti,pcm5122", पूर्ण,
	अणु .compatible = "ti,pcm5141", पूर्ण,
	अणु .compatible = "ti,pcm5142", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pcm512x_of_match);

अटल काष्ठा spi_driver pcm512x_spi_driver = अणु
	.probe		= pcm512x_spi_probe,
	.हटाओ		= pcm512x_spi_हटाओ,
	.id_table	= pcm512x_spi_id,
	.driver = अणु
		.name	= "pcm512x",
		.of_match_table = pcm512x_of_match,
		.pm     = &pcm512x_pm_ops,
	पूर्ण,
पूर्ण;

module_spi_driver(pcm512x_spi_driver);

MODULE_DESCRIPTION("ASoC PCM512x codec driver - SPI");
MODULE_AUTHOR("Mark Brown <broonie@kernel.org>");
MODULE_LICENSE("GPL v2");
