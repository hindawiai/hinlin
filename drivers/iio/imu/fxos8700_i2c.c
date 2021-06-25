<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * FXOS8700 - NXP IMU, I2C bits
 *
 * 7-bit I2C slave address determined by SA1 and SA0 logic level
 * inमाला_दो represented in the following table:
 *      SA1  |  SA0  |  Slave Address
 *      0    |  0    |  0x1E
 *      0    |  1    |  0x1D
 *      1    |  0    |  0x1C
 *      1    |  1    |  0x1F
 */
#समावेश <linux/acpi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/regmap.h>

#समावेश "fxos8700.h"

अटल पूर्णांक fxos8700_i2c_probe(काष्ठा i2c_client *client,
			      स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap *regmap;
	स्थिर अक्षर *name = शून्य;

	regmap = devm_regmap_init_i2c(client, &fxos8700_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&client->dev, "Failed to register i2c regmap %ld\n", PTR_ERR(regmap));
		वापस PTR_ERR(regmap);
	पूर्ण

	अगर (id)
		name = id->name;

	वापस fxos8700_core_probe(&client->dev, regmap, name, false);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id fxos8700_i2c_id[] = अणु
	अणु"fxos8700", 0पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, fxos8700_i2c_id);

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

अटल काष्ठा i2c_driver fxos8700_i2c_driver = अणु
	.driver = अणु
		.name                   = "fxos8700_i2c",
		.acpi_match_table       = ACPI_PTR(fxos8700_acpi_match),
		.of_match_table         = fxos8700_of_match,
	पूर्ण,
	.probe          = fxos8700_i2c_probe,
	.id_table       = fxos8700_i2c_id,
पूर्ण;
module_i2c_driver(fxos8700_i2c_driver);

MODULE_AUTHOR("Robert Jones <rjones@gateworks.com>");
MODULE_DESCRIPTION("FXOS8700 I2C driver");
MODULE_LICENSE("GPL v2");
