<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * AD7879/AD7889 touchscreen (SPI bus)
 *
 * Copyright (C) 2008-2010 Michael Hennerich, Analog Devices Inc.
 */

#समावेश <linux/input.h>	/* BUS_SPI */
#समावेश <linux/pm.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>

#समावेश "ad7879.h"

#घोषणा AD7879_DEVID		0x7A	/* AD7879/AD7889 */

#घोषणा MAX_SPI_FREQ_HZ      5000000

#घोषणा AD7879_CMD_MAGIC     0xE0
#घोषणा AD7879_CMD_READ      BIT(2)

अटल स्थिर काष्ठा regmap_config ad7879_spi_regmap_config = अणु
	.reg_bits = 16,
	.val_bits = 16,
	.max_रेजिस्टर = 15,
	.पढ़ो_flag_mask = AD7879_CMD_MAGIC | AD7879_CMD_READ,
	.ग_लिखो_flag_mask = AD7879_CMD_MAGIC,
पूर्ण;

अटल पूर्णांक ad7879_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा regmap *regmap;

	/* करोn't exceed max specअगरied SPI CLK frequency */
	अगर (spi->max_speed_hz > MAX_SPI_FREQ_HZ) अणु
		dev_err(&spi->dev, "SPI CLK %d Hz?\n", spi->max_speed_hz);
		वापस -EINVAL;
	पूर्ण

	regmap = devm_regmap_init_spi(spi, &ad7879_spi_regmap_config);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	वापस ad7879_probe(&spi->dev, regmap, spi->irq, BUS_SPI, AD7879_DEVID);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id ad7879_spi_dt_ids[] = अणु
	अणु .compatible = "adi,ad7879", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ad7879_spi_dt_ids);
#पूर्ण_अगर

अटल काष्ठा spi_driver ad7879_spi_driver = अणु
	.driver = अणु
		.name	= "ad7879",
		.pm	= &ad7879_pm_ops,
		.of_match_table = of_match_ptr(ad7879_spi_dt_ids),
	पूर्ण,
	.probe		= ad7879_spi_probe,
पूर्ण;

module_spi_driver(ad7879_spi_driver);

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("AD7879(-1) touchscreen SPI bus driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("spi:ad7879");
