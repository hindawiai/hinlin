<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Hardware monitoring driver क्रम Infineon IR36021
 *
 * Copyright (c) 2021 Allied Telesis
 */
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश "pmbus.h"

अटल काष्ठा pmbus_driver_info ir36021_info = अणु
	.pages = 1,
	.क्रमmat[PSC_VOLTAGE_IN] = linear,
	.क्रमmat[PSC_VOLTAGE_OUT] = linear,
	.क्रमmat[PSC_CURRENT_IN] = linear,
	.क्रमmat[PSC_CURRENT_OUT] = linear,
	.क्रमmat[PSC_POWER] = linear,
	.क्रमmat[PSC_TEMPERATURE] = linear,
	.func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_VOUT
		| PMBUS_HAVE_IIN | PMBUS_HAVE_IOUT
		| PMBUS_HAVE_PIN | PMBUS_HAVE_POUT
		| PMBUS_HAVE_TEMP | PMBUS_HAVE_TEMP2
		| PMBUS_HAVE_STATUS_TEMP,
पूर्ण;

अटल पूर्णांक ir36021_probe(काष्ठा i2c_client *client)
अणु
	u8 buf[I2C_SMBUS_BLOCK_MAX];
	पूर्णांक ret;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_READ_BYTE_DATA
				     | I2C_FUNC_SMBUS_READ_WORD_DATA
				     | I2C_FUNC_SMBUS_READ_BLOCK_DATA))
		वापस -ENODEV;

	ret = i2c_smbus_पढ़ो_i2c_block_data(client, PMBUS_MFR_MODEL, 2, buf);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Failed to read PMBUS_MFR_MODEL\n");
		वापस ret;
	पूर्ण
	अगर (ret != 2 || buf[0] != 0x01 || buf[1] != 0x2d) अणु
		dev_err(&client->dev, "MFR_MODEL unrecognised\n");
		वापस -ENODEV;
	पूर्ण

	वापस pmbus_करो_probe(client, &ir36021_info);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ir36021_id[] = अणु
	अणु "ir36021", 0 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ir36021_id);

अटल स्थिर काष्ठा of_device_id __maybe_unused ir36021_of_id[] = अणु
	अणु .compatible = "infineon,ir36021" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ir36021_of_id);

अटल काष्ठा i2c_driver ir36021_driver = अणु
	.class = I2C_CLASS_HWMON,
	.driver = अणु
		.name = "ir36021",
		.of_match_table = of_match_ptr(ir36021_of_id),
	पूर्ण,
	.probe_new = ir36021_probe,
	.id_table = ir36021_id,
पूर्ण;

module_i2c_driver(ir36021_driver);

MODULE_AUTHOR("Chris Packham <chris.packham@alliedtelesis.co.nz>");
MODULE_DESCRIPTION("PMBus driver for Infineon IR36021");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(PMBUS);
