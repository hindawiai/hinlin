<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/spi/spi.h>
#समावेश <linux/regmap.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/module.h>

#समावेश "bmg160.h"

अटल स्थिर काष्ठा regmap_config bmg160_regmap_spi_conf = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 0x3f,
पूर्ण;

अटल पूर्णांक bmg160_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा regmap *regmap;
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);

	regmap = devm_regmap_init_spi(spi, &bmg160_regmap_spi_conf);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&spi->dev, "Failed to register spi regmap: %pe\n",
			regmap);
		वापस PTR_ERR(regmap);
	पूर्ण

	वापस bmg160_core_probe(&spi->dev, regmap, spi->irq, id->name);
पूर्ण

अटल पूर्णांक bmg160_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	bmg160_core_हटाओ(&spi->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id bmg160_spi_id[] = अणु
	अणु"bmg160", 0पूर्ण,
	अणु"bmi055_gyro", 0पूर्ण,
	अणु"bmi088_gyro", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(spi, bmg160_spi_id);

अटल काष्ठा spi_driver bmg160_spi_driver = अणु
	.driver = अणु
		.name	= "bmg160_spi",
		.pm	= &bmg160_pm_ops,
	पूर्ण,
	.probe		= bmg160_spi_probe,
	.हटाओ		= bmg160_spi_हटाओ,
	.id_table	= bmg160_spi_id,
पूर्ण;
module_spi_driver(bmg160_spi_driver);

MODULE_AUTHOR("Markus Pargmann <mpa@pengutronix.de>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("BMG160 SPI Gyro driver");
