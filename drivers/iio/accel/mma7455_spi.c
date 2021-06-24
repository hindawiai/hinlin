<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IIO accel SPI driver क्रम Freescale MMA7455L 3-axis 10-bit accelerometer
 * Copyright 2015 Joachim Eastwood <manabian@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>

#समावेश "mma7455.h"

अटल पूर्णांक mma7455_spi_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);
	काष्ठा regmap *regmap;

	regmap = devm_regmap_init_spi(spi, &mma7455_core_regmap);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	वापस mma7455_core_probe(&spi->dev, regmap, id->name);
पूर्ण

अटल पूर्णांक mma7455_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	वापस mma7455_core_हटाओ(&spi->dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id mma7455_spi_ids[] = अणु
	अणु "mma7455", 0 पूर्ण,
	अणु "mma7456", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, mma7455_spi_ids);

अटल काष्ठा spi_driver mma7455_spi_driver = अणु
	.probe = mma7455_spi_probe,
	.हटाओ = mma7455_spi_हटाओ,
	.id_table = mma7455_spi_ids,
	.driver = अणु
		.name = "mma7455-spi",
	पूर्ण,
पूर्ण;
module_spi_driver(mma7455_spi_driver);

MODULE_AUTHOR("Joachim Eastwood <manabian@gmail.com>");
MODULE_DESCRIPTION("Freescale MMA7455L SPI accelerometer driver");
MODULE_LICENSE("GPL v2");
