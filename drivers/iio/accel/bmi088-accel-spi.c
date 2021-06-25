<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * 3-axis accelerometer driver supporting following Bosch-Sensortec chips:
 *  - BMI088
 *
 * Copyright (c) 2018-2020, Topic Embedded Products
 */

#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>

#समावेश "bmi088-accel.h"

अटल पूर्णांक bmi088_regmap_spi_ग_लिखो(व्योम *context, स्थिर व्योम *data, माप_प्रकार count)
अणु
	काष्ठा spi_device *spi = context;

	/* Write रेजिस्टर is same as generic SPI */
	वापस spi_ग_लिखो(spi, data, count);
पूर्ण

अटल पूर्णांक bmi088_regmap_spi_पढ़ो(व्योम *context, स्थिर व्योम *reg,
				माप_प्रकार reg_size, व्योम *val, माप_प्रकार val_size)
अणु
	काष्ठा spi_device *spi = context;
	u8 addr[2];

	addr[0] = *(u8 *)reg;
	addr[0] |= BIT(7); /* Set RW = '1' */
	addr[1] = 0; /* Read requires a dummy byte transfer */

	वापस spi_ग_लिखो_then_पढ़ो(spi, addr, माप(addr), val, val_size);
पूर्ण

अटल काष्ठा regmap_bus bmi088_regmap_bus = अणु
	.ग_लिखो = bmi088_regmap_spi_ग_लिखो,
	.पढ़ो = bmi088_regmap_spi_पढ़ो,
पूर्ण;

अटल पूर्णांक bmi088_accel_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा regmap *regmap;
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);

	regmap = devm_regmap_init(&spi->dev, &bmi088_regmap_bus,
			spi, &bmi088_regmap_conf);

	अगर (IS_ERR(regmap)) अणु
		dev_err(&spi->dev, "Failed to initialize spi regmap\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	वापस bmi088_accel_core_probe(&spi->dev, regmap, spi->irq, id->name,
				       true);
पूर्ण

अटल पूर्णांक bmi088_accel_हटाओ(काष्ठा spi_device *spi)
अणु
	वापस bmi088_accel_core_हटाओ(&spi->dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id bmi088_accel_id[] = अणु
	अणु"bmi088-accel", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, bmi088_accel_id);

अटल काष्ठा spi_driver bmi088_accel_driver = अणु
	.driver = अणु
		.name	= "bmi088_accel_spi",
		.pm	= &bmi088_accel_pm_ops,
	पूर्ण,
	.probe		= bmi088_accel_probe,
	.हटाओ		= bmi088_accel_हटाओ,
	.id_table	= bmi088_accel_id,
पूर्ण;
module_spi_driver(bmi088_accel_driver);

MODULE_AUTHOR("Niek van Agt <niek.van.agt@topicproducts.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("BMI088 accelerometer driver (SPI)");
