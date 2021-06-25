<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * 3-axis accelerometer driver supporting following I2C Bosch-Sensortec chips:
 *  - BMC150
 *  - BMI055
 *  - BMA255
 *  - BMA250E
 *  - BMA222
 *  - BMA222E
 *  - BMA280
 *
 * Copyright (c) 2014, Intel Corporation.
 */

#समावेश <linux/device.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/acpi.h>
#समावेश <linux/regmap.h>

#समावेश "bmc150-accel.h"

अटल पूर्णांक bmc150_accel_probe(काष्ठा i2c_client *client,
			      स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap *regmap;
	स्थिर अक्षर *name = शून्य;
	bool block_supported =
		i2c_check_functionality(client->adapter, I2C_FUNC_I2C) ||
		i2c_check_functionality(client->adapter,
					I2C_FUNC_SMBUS_READ_I2C_BLOCK);
	काष्ठा acpi_device __maybe_unused *adev;
	पूर्णांक ret;

	regmap = devm_regmap_init_i2c(client, &bmc150_regmap_conf);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&client->dev, "Failed to initialize i2c regmap\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	अगर (id)
		name = id->name;

	ret = bmc150_accel_core_probe(&client->dev, regmap, client->irq, name, block_supported);
	अगर (ret)
		वापस ret;

	/*
	 * Some BOSC0200 acpi_devices describe 2 accelerometers in a single ACPI
	 * device, try instantiating a second i2c_client क्रम an I2cSerialBusV2
	 * ACPI resource with index 1. The !id check aव्योमs recursion when
	 * bmc150_accel_probe() माला_लो called क्रम the second client.
	 */
#अगर_घोषित CONFIG_ACPI
	adev = ACPI_COMPANION(&client->dev);
	अगर (!id && adev && म_भेद(acpi_device_hid(adev), "BOSC0200") == 0) अणु
		काष्ठा i2c_board_info board_info = अणु
			.type = "bmc150_accel",
			/*
			 * The 2nd accel sits in the base of 2-in-1s. Note this
			 * name is अटल, as there should never be more then 1
			 * BOSC0200 ACPI node with 2 accelerometers in it.
			 */
			.dev_name = "BOSC0200:base",
			.fwnode = client->dev.fwnode,
			.irq = -ENOENT,
		पूर्ण;
		काष्ठा i2c_client *second_dev;

		second_dev = i2c_acpi_new_device(&client->dev, 1, &board_info);
		अगर (!IS_ERR(second_dev))
			bmc150_set_second_device(second_dev);
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक bmc150_accel_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा i2c_client *second_dev = bmc150_get_second_device(client);

	i2c_unरेजिस्टर_device(second_dev);

	वापस bmc150_accel_core_हटाओ(&client->dev);
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
	अणु"BOSC0200"पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, bmc150_accel_acpi_match);

अटल स्थिर काष्ठा i2c_device_id bmc150_accel_id[] = अणु
	अणु"bmc150_accel",	bmc150पूर्ण,
	अणु"bmi055_accel",	bmi055पूर्ण,
	अणु"bma255",		bma255पूर्ण,
	अणु"bma250e",		bma250eपूर्ण,
	अणु"bma222",		bma222पूर्ण,
	अणु"bma222e",		bma222eपूर्ण,
	अणु"bma280",		bma280पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, bmc150_accel_id);

अटल स्थिर काष्ठा of_device_id bmc150_accel_of_match[] = अणु
	अणु .compatible = "bosch,bmc150_accel" पूर्ण,
	अणु .compatible = "bosch,bmi055_accel" पूर्ण,
	अणु .compatible = "bosch,bma255" पूर्ण,
	अणु .compatible = "bosch,bma250e" पूर्ण,
	अणु .compatible = "bosch,bma222" पूर्ण,
	अणु .compatible = "bosch,bma222e" पूर्ण,
	अणु .compatible = "bosch,bma280" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bmc150_accel_of_match);

अटल काष्ठा i2c_driver bmc150_accel_driver = अणु
	.driver = अणु
		.name	= "bmc150_accel_i2c",
		.of_match_table = bmc150_accel_of_match,
		.acpi_match_table = ACPI_PTR(bmc150_accel_acpi_match),
		.pm	= &bmc150_accel_pm_ops,
	पूर्ण,
	.probe		= bmc150_accel_probe,
	.हटाओ		= bmc150_accel_हटाओ,
	.id_table	= bmc150_accel_id,
पूर्ण;
module_i2c_driver(bmc150_accel_driver);

MODULE_AUTHOR("Srinivas Pandruvada <srinivas.pandruvada@linux.intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("BMC150 I2C accelerometer driver");
