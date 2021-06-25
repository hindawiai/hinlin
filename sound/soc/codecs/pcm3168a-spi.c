<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PCM3168A codec spi driver
 *
 * Copyright (C) 2015 Imagination Technologies Ltd.
 *
 * Author: Damien Horsley <Damien.Horsley@imgtec.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>

#समावेश <sound/soc.h>

#समावेश "pcm3168a.h"

अटल पूर्णांक pcm3168a_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा regmap *regmap;

	regmap = devm_regmap_init_spi(spi, &pcm3168a_regmap);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	वापस pcm3168a_probe(&spi->dev, regmap);
पूर्ण

अटल पूर्णांक pcm3168a_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	pcm3168a_हटाओ(&spi->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id pcm3168a_spi_id[] = अणु
	अणु "pcm3168a", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, pcm3168a_spi_id);

अटल स्थिर काष्ठा of_device_id pcm3168a_of_match[] = अणु
	अणु .compatible = "ti,pcm3168a", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pcm3168a_of_match);

अटल काष्ठा spi_driver pcm3168a_spi_driver = अणु
	.probe		= pcm3168a_spi_probe,
	.हटाओ		= pcm3168a_spi_हटाओ,
	.id_table	= pcm3168a_spi_id,
	.driver = अणु
		.name	= "pcm3168a",
		.of_match_table = pcm3168a_of_match,
		.pm		= &pcm3168a_pm_ops,
	पूर्ण,
पूर्ण;
module_spi_driver(pcm3168a_spi_driver);

MODULE_DESCRIPTION("PCM3168A SPI codec driver");
MODULE_AUTHOR("Damien Horsley <Damien.Horsley@imgtec.com>");
MODULE_LICENSE("GPL v2");
