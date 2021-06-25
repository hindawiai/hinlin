<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hardware monitoring driver क्रम IR35221
 *
 * Copyright (C) IBM Corporation 2017.
 */

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश "pmbus.h"

#घोषणा IR35221_MFR_VIN_PEAK		0xc5
#घोषणा IR35221_MFR_VOUT_PEAK		0xc6
#घोषणा IR35221_MFR_IOUT_PEAK		0xc7
#घोषणा IR35221_MFR_TEMP_PEAK		0xc8
#घोषणा IR35221_MFR_VIN_VALLEY		0xc9
#घोषणा IR35221_MFR_VOUT_VALLEY		0xca
#घोषणा IR35221_MFR_IOUT_VALLEY		0xcb
#घोषणा IR35221_MFR_TEMP_VALLEY		0xcc

अटल पूर्णांक ir35221_पढ़ो_word_data(काष्ठा i2c_client *client, पूर्णांक page,
				  पूर्णांक phase, पूर्णांक reg)
अणु
	पूर्णांक ret;

	चयन (reg) अणु
	हाल PMBUS_VIRT_READ_VIN_MAX:
		ret = pmbus_पढ़ो_word_data(client, page, phase,
					   IR35221_MFR_VIN_PEAK);
		अवरोध;
	हाल PMBUS_VIRT_READ_VOUT_MAX:
		ret = pmbus_पढ़ो_word_data(client, page, phase,
					   IR35221_MFR_VOUT_PEAK);
		अवरोध;
	हाल PMBUS_VIRT_READ_IOUT_MAX:
		ret = pmbus_पढ़ो_word_data(client, page, phase,
					   IR35221_MFR_IOUT_PEAK);
		अवरोध;
	हाल PMBUS_VIRT_READ_TEMP_MAX:
		ret = pmbus_पढ़ो_word_data(client, page, phase,
					   IR35221_MFR_TEMP_PEAK);
		अवरोध;
	हाल PMBUS_VIRT_READ_VIN_MIN:
		ret = pmbus_पढ़ो_word_data(client, page, phase,
					   IR35221_MFR_VIN_VALLEY);
		अवरोध;
	हाल PMBUS_VIRT_READ_VOUT_MIN:
		ret = pmbus_पढ़ो_word_data(client, page, phase,
					   IR35221_MFR_VOUT_VALLEY);
		अवरोध;
	हाल PMBUS_VIRT_READ_IOUT_MIN:
		ret = pmbus_पढ़ो_word_data(client, page, phase,
					   IR35221_MFR_IOUT_VALLEY);
		अवरोध;
	हाल PMBUS_VIRT_READ_TEMP_MIN:
		ret = pmbus_पढ़ो_word_data(client, page, phase,
					   IR35221_MFR_TEMP_VALLEY);
		अवरोध;
	शेष:
		ret = -ENODATA;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ir35221_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा pmbus_driver_info *info;
	u8 buf[I2C_SMBUS_BLOCK_MAX];
	पूर्णांक ret;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_READ_BYTE_DATA
				| I2C_FUNC_SMBUS_READ_WORD_DATA
				| I2C_FUNC_SMBUS_READ_BLOCK_DATA))
		वापस -ENODEV;

	ret = i2c_smbus_पढ़ो_block_data(client, PMBUS_MFR_ID, buf);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Failed to read PMBUS_MFR_ID\n");
		वापस ret;
	पूर्ण
	अगर (ret != 2 || म_भेदन(buf, "RI", म_माप("RI"))) अणु
		dev_err(&client->dev, "MFR_ID unrecognised\n");
		वापस -ENODEV;
	पूर्ण

	ret = i2c_smbus_पढ़ो_block_data(client, PMBUS_MFR_MODEL, buf);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Failed to read PMBUS_MFR_MODEL\n");
		वापस ret;
	पूर्ण
	अगर (ret != 2 || !(buf[0] == 0x6c && buf[1] == 0x00)) अणु
		dev_err(&client->dev, "MFR_MODEL unrecognised\n");
		वापस -ENODEV;
	पूर्ण

	info = devm_kzalloc(&client->dev, माप(काष्ठा pmbus_driver_info),
			    GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->पढ़ो_word_data = ir35221_पढ़ो_word_data;

	info->pages = 2;
	info->क्रमmat[PSC_VOLTAGE_IN] = linear;
	info->क्रमmat[PSC_VOLTAGE_OUT] = linear;
	info->क्रमmat[PSC_CURRENT_IN] = linear;
	info->क्रमmat[PSC_CURRENT_OUT] = linear;
	info->क्रमmat[PSC_POWER] = linear;
	info->क्रमmat[PSC_TEMPERATURE] = linear;

	info->func[0] = PMBUS_HAVE_VIN
		| PMBUS_HAVE_VOUT | PMBUS_HAVE_IIN
		| PMBUS_HAVE_IOUT | PMBUS_HAVE_PIN
		| PMBUS_HAVE_POUT | PMBUS_HAVE_TEMP
		| PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_STATUS_IOUT
		| PMBUS_HAVE_STATUS_INPUT | PMBUS_HAVE_STATUS_TEMP;
	info->func[1] = info->func[0];

	वापस pmbus_करो_probe(client, info);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ir35221_id[] = अणु
	अणु"ir35221", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, ir35221_id);

अटल काष्ठा i2c_driver ir35221_driver = अणु
	.driver = अणु
		.name	= "ir35221",
	पूर्ण,
	.probe_new	= ir35221_probe,
	.id_table	= ir35221_id,
पूर्ण;

module_i2c_driver(ir35221_driver);

MODULE_AUTHOR("Samuel Mendoza-Jonas <sam@mendozajonas.com");
MODULE_DESCRIPTION("PMBus driver for IR35221");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(PMBUS);
