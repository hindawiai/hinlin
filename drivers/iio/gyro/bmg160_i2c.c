<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/module.h>
#समावेश <linux/acpi.h>

#समावेश "bmg160.h"

अटल स्थिर काष्ठा regmap_config bmg160_regmap_i2c_conf = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 0x3f
पूर्ण;

अटल पूर्णांक bmg160_i2c_probe(काष्ठा i2c_client *client,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap *regmap;
	स्थिर अक्षर *name = शून्य;

	regmap = devm_regmap_init_i2c(client, &bmg160_regmap_i2c_conf);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&client->dev, "Failed to register i2c regmap: %pe\n",
			regmap);
		वापस PTR_ERR(regmap);
	पूर्ण

	अगर (id)
		name = id->name;

	वापस bmg160_core_probe(&client->dev, regmap, client->irq, name);
पूर्ण

अटल पूर्णांक bmg160_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	bmg160_core_हटाओ(&client->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id bmg160_acpi_match[] = अणु
	अणु"BMG0160", 0पूर्ण,
	अणु"BMI055B", 0पूर्ण,
	अणु"BMI088B", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(acpi, bmg160_acpi_match);

अटल स्थिर काष्ठा i2c_device_id bmg160_i2c_id[] = अणु
	अणु"bmg160", 0पूर्ण,
	अणु"bmi055_gyro", 0पूर्ण,
	अणु"bmi088_gyro", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, bmg160_i2c_id);

अटल स्थिर काष्ठा of_device_id bmg160_of_match[] = अणु
	अणु .compatible = "bosch,bmg160" पूर्ण,
	अणु .compatible = "bosch,bmi055_gyro" पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, bmg160_of_match);

अटल काष्ठा i2c_driver bmg160_i2c_driver = अणु
	.driver = अणु
		.name	= "bmg160_i2c",
		.acpi_match_table = ACPI_PTR(bmg160_acpi_match),
		.of_match_table = bmg160_of_match,
		.pm	= &bmg160_pm_ops,
	पूर्ण,
	.probe		= bmg160_i2c_probe,
	.हटाओ		= bmg160_i2c_हटाओ,
	.id_table	= bmg160_i2c_id,
पूर्ण;
module_i2c_driver(bmg160_i2c_driver);

MODULE_AUTHOR("Srinivas Pandruvada <srinivas.pandruvada@linux.intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("BMG160 I2C Gyro driver");
