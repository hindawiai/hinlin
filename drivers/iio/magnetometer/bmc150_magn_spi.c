<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * 3-axis magnetometer driver support following SPI Bosch-Sensortec chips:
 *  - BMC150
 *  - BMC156
 *  - BMM150
 *
 * Copyright (c) 2016, Intel Corporation.
 */
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/acpi.h>
#समावेश <linux/regmap.h>

#समावेश "bmc150_magn.h"

अटल पूर्णांक bmc150_magn_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा regmap *regmap;
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);

	regmap = devm_regmap_init_spi(spi, &bmc150_magn_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&spi->dev, "Failed to register spi regmap: %pe\n",
			regmap);
		वापस PTR_ERR(regmap);
	पूर्ण
	वापस bmc150_magn_probe(&spi->dev, regmap, spi->irq, id->name);
पूर्ण

अटल पूर्णांक bmc150_magn_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	bmc150_magn_हटाओ(&spi->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id bmc150_magn_spi_id[] = अणु
	अणु"bmc150_magn", 0पूर्ण,
	अणु"bmc156_magn", 0पूर्ण,
	अणु"bmm150_magn", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, bmc150_magn_spi_id);

अटल स्थिर काष्ठा acpi_device_id bmc150_magn_acpi_match[] = अणु
	अणु"BMC150B", 0पूर्ण,
	अणु"BMC156B", 0पूर्ण,
	अणु"BMM150B", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, bmc150_magn_acpi_match);

अटल काष्ठा spi_driver bmc150_magn_spi_driver = अणु
	.probe		= bmc150_magn_spi_probe,
	.हटाओ		= bmc150_magn_spi_हटाओ,
	.id_table	= bmc150_magn_spi_id,
	.driver = अणु
		.acpi_match_table = ACPI_PTR(bmc150_magn_acpi_match),
		.name	= "bmc150_magn_spi",
	पूर्ण,
पूर्ण;
module_spi_driver(bmc150_magn_spi_driver);

MODULE_AUTHOR("Daniel Baluta <daniel.baluta@intel.com");
MODULE_DESCRIPTION("BMC150 magnetometer SPI driver");
MODULE_LICENSE("GPL v2");
