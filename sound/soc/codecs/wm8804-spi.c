<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm8804-spi.c  --  WM8804 S/PDIF transceiver driver - SPI
 *
 * Copyright 2015 Cirrus Logic Inc
 *
 * Author: Charles Keepax <ckeepax@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>

#समावेश "wm8804.h"

अटल पूर्णांक wm8804_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा regmap *regmap;

	regmap = devm_regmap_init_spi(spi, &wm8804_regmap_config);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	वापस wm8804_probe(&spi->dev, regmap);
पूर्ण

अटल पूर्णांक wm8804_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	wm8804_हटाओ(&spi->dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id wm8804_of_match[] = अणु
	अणु .compatible = "wlf,wm8804", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, wm8804_of_match);

अटल काष्ठा spi_driver wm8804_spi_driver = अणु
	.driver = अणु
		.name = "wm8804",
		.pm = &wm8804_pm,
		.of_match_table = wm8804_of_match,
	पूर्ण,
	.probe = wm8804_spi_probe,
	.हटाओ = wm8804_spi_हटाओ
पूर्ण;

module_spi_driver(wm8804_spi_driver);

MODULE_DESCRIPTION("ASoC WM8804 driver - SPI");
MODULE_AUTHOR("Charles Keepax <ckeepax@opensource.wolfsonmicro.com>");
MODULE_LICENSE("GPL");
