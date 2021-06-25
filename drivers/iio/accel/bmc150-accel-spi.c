<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * 3-axis accelerometer driver supporting SPI Bosch-Sensortec accelerometer chip
 * Copyright तऊ 2015 Pengutronix, Markus Pargmann <mpa@pengutronix.de>
 */

#समावेश <linux/device.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/acpi.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>

#समावेश "bmc150-accel.h"

अटल पूर्णांक bmc150_accel_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा regmap *regmap;
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);

	regmap = devm_regmap_init_spi(spi, &bmc150_regmap_conf);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&spi->dev, "Failed to initialize spi regmap\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	वापस bmc150_accel_core_probe(&spi->dev, regmap, spi->irq, id->name,
				       true);
पूर्ण

अटल पूर्णांक bmc150_accel_हटाओ(काष्ठा spi_device *spi)
अणु
	वापस bmc150_accel_core_हटाओ(&spi->dev);
पूर्ण

अटल स्थिर काष्ठा acpi_device_id bmc150_accel_acpi_match[] = अणु
	अणु"BSBA0150",	bmc150पूर्ण,
	अणु"BMC150A",	bmc150पूर्ण,
	अणु"BMI055A",	bmi055पूर्ण,
	अणु"BMA0255",	bma255पूर्ण,
	अणु"BMA250E",	bma250eपूर्ण,
	अणु"BMA222",	bma222पूर्ण,
	अणु"BMA222E",	bma222eपूर्ण,
	अणु"BMA0280",	bma280पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, bmc150_accel_acpi_match);

अटल स्थिर काष्ठा spi_device_id bmc150_accel_id[] = अणु
	अणु"bmc150_accel",	bmc150पूर्ण,
	अणु"bmi055_accel",	bmi055पूर्ण,
	अणु"bma255",		bma255पूर्ण,
	अणु"bma250e",		bma250eपूर्ण,
	अणु"bma222",		bma222पूर्ण,
	अणु"bma222e",		bma222eपूर्ण,
	अणु"bma280",		bma280पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, bmc150_accel_id);

अटल काष्ठा spi_driver bmc150_accel_driver = अणु
	.driver = अणु
		.name	= "bmc150_accel_spi",
		.acpi_match_table = ACPI_PTR(bmc150_accel_acpi_match),
		.pm	= &bmc150_accel_pm_ops,
	पूर्ण,
	.probe		= bmc150_accel_probe,
	.हटाओ		= bmc150_accel_हटाओ,
	.id_table	= bmc150_accel_id,
पूर्ण;
module_spi_driver(bmc150_accel_driver);

MODULE_AUTHOR("Markus Pargmann <mpa@pengutronix.de>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("BMC150 SPI accelerometer driver");
