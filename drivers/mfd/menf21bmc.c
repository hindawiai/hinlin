<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  MEN 14F021P00 Board Management Controller (BMC) MFD Core Driver.
 *
 *  Copyright (C) 2014 MEN Mikro Elektronik Nuernberg GmbH
 */

#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mfd/core.h>

#घोषणा BMC_CMD_WDT_EXIT_PROD	0x18
#घोषणा BMC_CMD_WDT_PROD_STAT	0x19
#घोषणा BMC_CMD_REV_MAJOR	0x80
#घोषणा BMC_CMD_REV_MINOR	0x81
#घोषणा BMC_CMD_REV_MAIN	0x82

अटल काष्ठा mfd_cell menf21bmc_cell[] = अणु
	अणु .name = "menf21bmc_wdt", पूर्ण,
	अणु .name = "menf21bmc_led", पूर्ण,
	अणु .name = "menf21bmc_hwmon", पूर्ण
पूर्ण;

अटल पूर्णांक menf21bmc_wdt_निकास_prod_mode(काष्ठा i2c_client *client)
अणु
	पूर्णांक val, ret;

	val = i2c_smbus_पढ़ो_byte_data(client, BMC_CMD_WDT_PROD_STAT);
	अगर (val < 0)
		वापस val;

	/*
	 * Production mode should be not active after delivery of the Board.
	 * To be sure we check it, inक्रमm the user and निकास the mode
	 * अगर active.
	 */
	अगर (val == 0x00) अणु
		dev_info(&client->dev,
			"BMC in production mode. Exit production mode\n");

		ret = i2c_smbus_ग_लिखो_byte(client, BMC_CMD_WDT_EXIT_PROD);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
menf21bmc_probe(काष्ठा i2c_client *client, स्थिर काष्ठा i2c_device_id *ids)
अणु
	पूर्णांक rev_major, rev_minor, rev_मुख्य;
	पूर्णांक ret;

	ret = i2c_check_functionality(client->adapter,
				      I2C_FUNC_SMBUS_BYTE_DATA |
				      I2C_FUNC_SMBUS_WORD_DATA |
				      I2C_FUNC_SMBUS_BYTE);
	अगर (!ret)
		वापस -ENODEV;

	rev_major = i2c_smbus_पढ़ो_word_data(client, BMC_CMD_REV_MAJOR);
	अगर (rev_major < 0) अणु
		dev_err(&client->dev, "failed to get BMC major revision\n");
		वापस rev_major;
	पूर्ण

	rev_minor = i2c_smbus_पढ़ो_word_data(client, BMC_CMD_REV_MINOR);
	अगर (rev_minor < 0) अणु
		dev_err(&client->dev, "failed to get BMC minor revision\n");
		वापस rev_minor;
	पूर्ण

	rev_मुख्य = i2c_smbus_पढ़ो_word_data(client, BMC_CMD_REV_MAIN);
	अगर (rev_मुख्य < 0) अणु
		dev_err(&client->dev, "failed to get BMC main revision\n");
		वापस rev_मुख्य;
	पूर्ण

	dev_info(&client->dev, "FW Revision: %02d.%02d.%02d\n",
		 rev_major, rev_minor, rev_मुख्य);

	/*
	 * We have to निकास the Production Mode of the BMC to activate the
	 * Watchकरोg functionality and the BIOS lअगरe sign monitoring.
	 */
	ret = menf21bmc_wdt_निकास_prod_mode(client);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed to leave production mode\n");
		वापस ret;
	पूर्ण

	ret = devm_mfd_add_devices(&client->dev, 0, menf21bmc_cell,
				   ARRAY_SIZE(menf21bmc_cell), शून्य, 0, शून्य);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed to add BMC sub-devices\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id menf21bmc_id_table[] = अणु
	अणु "menf21bmc" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, menf21bmc_id_table);

अटल काष्ठा i2c_driver menf21bmc_driver = अणु
	.driver.name	= "menf21bmc",
	.id_table	= menf21bmc_id_table,
	.probe		= menf21bmc_probe,
पूर्ण;

module_i2c_driver(menf21bmc_driver);

MODULE_DESCRIPTION("MEN 14F021P00 BMC mfd core driver");
MODULE_AUTHOR("Andreas Werner <andreas.werner@men.de>");
MODULE_LICENSE("GPL v2");
