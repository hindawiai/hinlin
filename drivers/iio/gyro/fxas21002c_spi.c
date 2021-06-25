<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम NXP Fxas21002c Gyroscope - SPI
 *
 * Copyright (C) 2019 Linaro Ltd.
 */

#समावेश <linux/err.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>

#समावेश "fxas21002c.h"

अटल स्थिर काष्ठा regmap_config fxas21002c_regmap_spi_conf = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = FXAS21002C_REG_CTRL3,
पूर्ण;

अटल पूर्णांक fxas21002c_spi_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);
	काष्ठा regmap *regmap;

	regmap = devm_regmap_init_spi(spi, &fxas21002c_regmap_spi_conf);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&spi->dev, "Failed to register spi regmap: %ld\n",
			PTR_ERR(regmap));
		वापस PTR_ERR(regmap);
	पूर्ण

	वापस fxas21002c_core_probe(&spi->dev, regmap, spi->irq, id->name);
पूर्ण

अटल पूर्णांक fxas21002c_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	fxas21002c_core_हटाओ(&spi->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id fxas21002c_spi_id[] = अणु
	अणु "fxas21002c", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, fxas21002c_spi_id);

अटल स्थिर काष्ठा of_device_id fxas21002c_spi_of_match[] = अणु
	अणु .compatible = "nxp,fxas21002c", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, fxas21002c_spi_of_match);

अटल काष्ठा spi_driver fxas21002c_spi_driver = अणु
	.driver = अणु
		.name = "fxas21002c_spi",
		.pm = &fxas21002c_pm_ops,
		.of_match_table = fxas21002c_spi_of_match,
	पूर्ण,
	.probe		= fxas21002c_spi_probe,
	.हटाओ		= fxas21002c_spi_हटाओ,
	.id_table	= fxas21002c_spi_id,
पूर्ण;
module_spi_driver(fxas21002c_spi_driver);

MODULE_AUTHOR("Rui Miguel Silva <rui.silva@linaro.org>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("FXAS21002C SPI Gyro driver");
