<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * BMI160 - Bosch IMU, SPI bits
 *
 * Copyright (c) 2016, Intel Corporation.
 *
 */
#समावेश <linux/acpi.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>

#समावेश "bmi160.h"

अटल पूर्णांक bmi160_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा regmap *regmap;
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);

	regmap = devm_regmap_init_spi(spi, &bmi160_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&spi->dev, "Failed to register spi regmap: %pe\n",
			regmap);
		वापस PTR_ERR(regmap);
	पूर्ण
	वापस bmi160_core_probe(&spi->dev, regmap, id->name, true);
पूर्ण

अटल स्थिर काष्ठा spi_device_id bmi160_spi_id[] = अणु
	अणु"bmi160", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, bmi160_spi_id);

अटल स्थिर काष्ठा acpi_device_id bmi160_acpi_match[] = अणु
	अणु"BMI0160", 0पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, bmi160_acpi_match);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id bmi160_of_match[] = अणु
	अणु .compatible = "bosch,bmi160" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bmi160_of_match);
#पूर्ण_अगर

अटल काष्ठा spi_driver bmi160_spi_driver = अणु
	.probe		= bmi160_spi_probe,
	.id_table	= bmi160_spi_id,
	.driver = अणु
		.acpi_match_table	= ACPI_PTR(bmi160_acpi_match),
		.of_match_table		= of_match_ptr(bmi160_of_match),
		.name			= "bmi160_spi",
	पूर्ण,
पूर्ण;
module_spi_driver(bmi160_spi_driver);

MODULE_AUTHOR("Daniel Baluta <daniel.baluta@intel.com");
MODULE_DESCRIPTION("Bosch BMI160 SPI driver");
MODULE_LICENSE("GPL v2");
