<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SSM2602 SPI audio driver
 *
 * Copyright 2014 Analog Devices Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/regmap.h>

#समावेश <sound/soc.h>

#समावेश "ssm2602.h"

अटल पूर्णांक ssm2602_spi_probe(काष्ठा spi_device *spi)
अणु
	वापस ssm2602_probe(&spi->dev, SSM2602,
		devm_regmap_init_spi(spi, &ssm2602_regmap_config));
पूर्ण

अटल स्थिर काष्ठा of_device_id ssm2602_of_match[] = अणु
	अणु .compatible = "adi,ssm2602", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ssm2602_of_match);

अटल काष्ठा spi_driver ssm2602_spi_driver = अणु
	.driver = अणु
		.name	= "ssm2602",
		.of_match_table = ssm2602_of_match,
	पूर्ण,
	.probe		= ssm2602_spi_probe,
पूर्ण;
module_spi_driver(ssm2602_spi_driver);

MODULE_DESCRIPTION("ASoC SSM2602 SPI driver");
MODULE_AUTHOR("Cliff Cai");
MODULE_LICENSE("GPL");
