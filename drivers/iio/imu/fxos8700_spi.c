<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * FXOS8700 - NXP IMU, SPI bits
 */
#समावेश <linux/acpi.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>

#समावेश "fxos8700.h"

अटल पूर्णांक fxos8700_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा regmap *regmap;
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);

	regmap = devm_regmap_init_spi(spi, &fxos8700_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&spi->dev, "Failed to register spi regmap %ld\n", PTR_ERR(regmap));
		वापस PTR_ERR(regmap);
	पूर्ण

	वापस fxos8700_core_probe(&spi->dev, regmap, id->name, true);
पूर्ण

अटल स्थिर काष्ठा spi_device_id fxos8700_spi_id[] = अणु
	अणु"fxos8700", 0पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, fxos8700_spi_id);

अटल स्थिर काष्ठा acpi_device_id fxos8700_acpi_match[] = अणु
	अणु"FXOS8700", 0पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, fxos8700_acpi_match);

अटल स्थिर काष्ठा of_device_id fxos8700_of_match[] = अणु
	अणु .compatible = "nxp,fxos8700" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, fxos8700_of_match);

अटल काष्ठा spi_driver fxos8700_spi_driver = अणु
	.probe          = fxos8700_spi_probe,
	.id_table       = fxos8700_spi_id,
	.driver = अणु
		.acpi_match_table       = ACPI_PTR(fxos8700_acpi_match),
		.of_match_table         = fxos8700_of_match,
		.name                   = "fxos8700_spi",
	पूर्ण,
पूर्ण;
module_spi_driver(fxos8700_spi_driver);

MODULE_AUTHOR("Robert Jones <rjones@gateworks.com>");
MODULE_DESCRIPTION("FXOS8700 SPI driver");
MODULE_LICENSE("GPL v2");
