<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Texas Instruments PCM186x Universal Audio ADC - SPI
 *
 * Copyright (C) 2015-2017 Texas Instruments Incorporated - https://www.ti.com
 *	Andreas Dannenberg <dannenberg@ti.com>
 *	Andrew F. Davis <afd@ti.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>

#समावेश "pcm186x.h"

अटल स्थिर काष्ठा of_device_id pcm186x_of_match[] = अणु
	अणु .compatible = "ti,pcm1862", .data = (व्योम *)PCM1862 पूर्ण,
	अणु .compatible = "ti,pcm1863", .data = (व्योम *)PCM1863 पूर्ण,
	अणु .compatible = "ti,pcm1864", .data = (व्योम *)PCM1864 पूर्ण,
	अणु .compatible = "ti,pcm1865", .data = (व्योम *)PCM1865 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pcm186x_of_match);

अटल पूर्णांक pcm186x_spi_probe(काष्ठा spi_device *spi)
अणु
	स्थिर क्रमागत pcm186x_type type =
			 (क्रमागत pcm186x_type)spi_get_device_id(spi)->driver_data;
	पूर्णांक irq = spi->irq;
	काष्ठा regmap *regmap;

	regmap = devm_regmap_init_spi(spi, &pcm186x_regmap);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	वापस pcm186x_probe(&spi->dev, type, irq, regmap);
पूर्ण

अटल स्थिर काष्ठा spi_device_id pcm186x_spi_id[] = अणु
	अणु "pcm1862", PCM1862 पूर्ण,
	अणु "pcm1863", PCM1863 पूर्ण,
	अणु "pcm1864", PCM1864 पूर्ण,
	अणु "pcm1865", PCM1865 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, pcm186x_spi_id);

अटल काष्ठा spi_driver pcm186x_spi_driver = अणु
	.probe		= pcm186x_spi_probe,
	.id_table	= pcm186x_spi_id,
	.driver		= अणु
		.name	= "pcm186x",
		.of_match_table = pcm186x_of_match,
	पूर्ण,
पूर्ण;
module_spi_driver(pcm186x_spi_driver);

MODULE_AUTHOR("Andreas Dannenberg <dannenberg@ti.com>");
MODULE_AUTHOR("Andrew F. Davis <afd@ti.com>");
MODULE_DESCRIPTION("PCM186x Universal Audio ADC SPI Interface Driver");
MODULE_LICENSE("GPL v2");
