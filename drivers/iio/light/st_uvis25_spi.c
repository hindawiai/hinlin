<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * STMicroelectronics uvis25 spi driver
 *
 * Copyright 2017 STMicroelectronics Inc.
 *
 * Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/slab.h>
#समावेश <linux/regmap.h>

#समावेश "st_uvis25.h"

#घोषणा UVIS25_SENSORS_SPI_READ		BIT(7)
#घोषणा UVIS25_SPI_AUTO_INCREMENT	BIT(6)

अटल स्थिर काष्ठा regmap_config st_uvis25_spi_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.पढ़ो_flag_mask = UVIS25_SENSORS_SPI_READ | UVIS25_SPI_AUTO_INCREMENT,
	.ग_लिखो_flag_mask = UVIS25_SPI_AUTO_INCREMENT,
पूर्ण;

अटल पूर्णांक st_uvis25_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा regmap *regmap;

	regmap = devm_regmap_init_spi(spi, &st_uvis25_spi_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&spi->dev, "Failed to register spi regmap %ld\n",
			PTR_ERR(regmap));
		वापस PTR_ERR(regmap);
	पूर्ण

	वापस st_uvis25_probe(&spi->dev, spi->irq, regmap);
पूर्ण

अटल स्थिर काष्ठा of_device_id st_uvis25_spi_of_match[] = अणु
	अणु .compatible = "st,uvis25", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, st_uvis25_spi_of_match);

अटल स्थिर काष्ठा spi_device_id st_uvis25_spi_id_table[] = अणु
	अणु ST_UVIS25_DEV_NAME पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, st_uvis25_spi_id_table);

अटल काष्ठा spi_driver st_uvis25_driver = अणु
	.driver = अणु
		.name = "st_uvis25_spi",
		.pm = &st_uvis25_pm_ops,
		.of_match_table = st_uvis25_spi_of_match,
	पूर्ण,
	.probe = st_uvis25_spi_probe,
	.id_table = st_uvis25_spi_id_table,
पूर्ण;
module_spi_driver(st_uvis25_driver);

MODULE_AUTHOR("Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>");
MODULE_DESCRIPTION("STMicroelectronics uvis25 spi driver");
MODULE_LICENSE("GPL v2");
