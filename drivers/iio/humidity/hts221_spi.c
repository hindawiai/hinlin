<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * STMicroelectronics hts221 spi driver
 *
 * Copyright 2016 STMicroelectronics Inc.
 *
 * Lorenzo Bianconi <lorenzo.bianconi@st.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/slab.h>
#समावेश <linux/regmap.h>

#समावेश "hts221.h"

#घोषणा HTS221_SPI_READ			BIT(7)
#घोषणा HTS221_SPI_AUTO_INCREMENT	BIT(6)

अटल स्थिर काष्ठा regmap_config hts221_spi_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.ग_लिखो_flag_mask = HTS221_SPI_AUTO_INCREMENT,
	.पढ़ो_flag_mask = HTS221_SPI_READ | HTS221_SPI_AUTO_INCREMENT,
पूर्ण;

अटल पूर्णांक hts221_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा regmap *regmap;

	regmap = devm_regmap_init_spi(spi, &hts221_spi_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&spi->dev, "Failed to register spi regmap %ld\n",
			PTR_ERR(regmap));
		वापस PTR_ERR(regmap);
	पूर्ण

	वापस hts221_probe(&spi->dev, spi->irq,
			    spi->modalias, regmap);
पूर्ण

अटल स्थिर काष्ठा of_device_id hts221_spi_of_match[] = अणु
	अणु .compatible = "st,hts221", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, hts221_spi_of_match);

अटल स्थिर काष्ठा spi_device_id hts221_spi_id_table[] = अणु
	अणु HTS221_DEV_NAME पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, hts221_spi_id_table);

अटल काष्ठा spi_driver hts221_driver = अणु
	.driver = अणु
		.name = "hts221_spi",
		.pm = &hts221_pm_ops,
		.of_match_table = hts221_spi_of_match,
	पूर्ण,
	.probe = hts221_spi_probe,
	.id_table = hts221_spi_id_table,
पूर्ण;
module_spi_driver(hts221_driver);

MODULE_AUTHOR("Lorenzo Bianconi <lorenzo.bianconi@st.com>");
MODULE_DESCRIPTION("STMicroelectronics hts221 spi driver");
MODULE_LICENSE("GPL v2");
