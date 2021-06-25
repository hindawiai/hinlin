<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hardware monitoring driver क्रम LTC3815
 *
 * Copyright (c) 2015 Linear Technology
 * Copyright (c) 2015 Guenter Roeck
 */

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश "pmbus.h"

#घोषणा LTC3815_MFR_IOUT_PEAK	0xd7
#घोषणा LTC3815_MFR_VOUT_PEAK	0xdd
#घोषणा LTC3815_MFR_VIN_PEAK	0xde
#घोषणा LTC3815_MFR_TEMP_PEAK	0xdf
#घोषणा LTC3815_MFR_IIN_PEAK	0xe1
#घोषणा LTC3815_MFR_SPECIAL_ID	0xe7

#घोषणा LTC3815_ID		0x8000
#घोषणा LTC3815_ID_MASK		0xff00

अटल पूर्णांक ltc3815_पढ़ो_byte_data(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक reg)
अणु
	पूर्णांक ret;

	चयन (reg) अणु
	हाल PMBUS_VOUT_MODE:
		/*
		 * The chip वापसs 0x3e, suggesting VID mode with manufacturer
		 * specअगरic VID codes. Since the output voltage is reported
		 * with a LSB of 0.5mV, override and report direct mode with
		 * appropriate coefficients.
		 */
		ret = 0x40;
		अवरोध;
	शेष:
		ret = -ENODATA;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ltc3815_ग_लिखो_byte(काष्ठा i2c_client *client, पूर्णांक page, u8 reg)
अणु
	पूर्णांक ret;

	चयन (reg) अणु
	हाल PMBUS_CLEAR_FAULTS:
		/*
		 * LTC3815 करोes not support the CLEAR_FAULTS command.
		 * Emulate it by clearing the status रेजिस्टर.
		 */
		ret = pmbus_पढ़ो_word_data(client, 0, 0xff, PMBUS_STATUS_WORD);
		अगर (ret > 0) अणु
			pmbus_ग_लिखो_word_data(client, 0, PMBUS_STATUS_WORD,
					      ret);
			ret = 0;
		पूर्ण
		अवरोध;
	शेष:
		ret = -ENODATA;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ltc3815_पढ़ो_word_data(काष्ठा i2c_client *client, पूर्णांक page,
				  पूर्णांक phase, पूर्णांक reg)
अणु
	पूर्णांक ret;

	चयन (reg) अणु
	हाल PMBUS_VIRT_READ_VIN_MAX:
		ret = pmbus_पढ़ो_word_data(client, page, phase,
					   LTC3815_MFR_VIN_PEAK);
		अवरोध;
	हाल PMBUS_VIRT_READ_VOUT_MAX:
		ret = pmbus_पढ़ो_word_data(client, page, phase,
					   LTC3815_MFR_VOUT_PEAK);
		अवरोध;
	हाल PMBUS_VIRT_READ_TEMP_MAX:
		ret = pmbus_पढ़ो_word_data(client, page, phase,
					   LTC3815_MFR_TEMP_PEAK);
		अवरोध;
	हाल PMBUS_VIRT_READ_IOUT_MAX:
		ret = pmbus_पढ़ो_word_data(client, page, phase,
					   LTC3815_MFR_IOUT_PEAK);
		अवरोध;
	हाल PMBUS_VIRT_READ_IIN_MAX:
		ret = pmbus_पढ़ो_word_data(client, page, phase,
					   LTC3815_MFR_IIN_PEAK);
		अवरोध;
	हाल PMBUS_VIRT_RESET_VOUT_HISTORY:
	हाल PMBUS_VIRT_RESET_VIN_HISTORY:
	हाल PMBUS_VIRT_RESET_TEMP_HISTORY:
	हाल PMBUS_VIRT_RESET_IOUT_HISTORY:
	हाल PMBUS_VIRT_RESET_IIN_HISTORY:
		ret = 0;
		अवरोध;
	शेष:
		ret = -ENODATA;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ltc3815_ग_लिखो_word_data(काष्ठा i2c_client *client, पूर्णांक page,
				   पूर्णांक reg, u16 word)
अणु
	पूर्णांक ret;

	चयन (reg) अणु
	हाल PMBUS_VIRT_RESET_IIN_HISTORY:
		ret = pmbus_ग_लिखो_word_data(client, page,
					    LTC3815_MFR_IIN_PEAK, 0);
		अवरोध;
	हाल PMBUS_VIRT_RESET_IOUT_HISTORY:
		ret = pmbus_ग_लिखो_word_data(client, page,
					    LTC3815_MFR_IOUT_PEAK, 0);
		अवरोध;
	हाल PMBUS_VIRT_RESET_VOUT_HISTORY:
		ret = pmbus_ग_लिखो_word_data(client, page,
					    LTC3815_MFR_VOUT_PEAK, 0);
		अवरोध;
	हाल PMBUS_VIRT_RESET_VIN_HISTORY:
		ret = pmbus_ग_लिखो_word_data(client, page,
					    LTC3815_MFR_VIN_PEAK, 0);
		अवरोध;
	हाल PMBUS_VIRT_RESET_TEMP_HISTORY:
		ret = pmbus_ग_लिखो_word_data(client, page,
					    LTC3815_MFR_TEMP_PEAK, 0);
		अवरोध;
	शेष:
		ret = -ENODATA;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ltc3815_id[] = अणु
	अणु"ltc3815", 0पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ltc3815_id);

अटल काष्ठा pmbus_driver_info ltc3815_info = अणु
	.pages = 1,
	.क्रमmat[PSC_VOLTAGE_IN] = direct,
	.क्रमmat[PSC_VOLTAGE_OUT] = direct,
	.क्रमmat[PSC_CURRENT_IN] = direct,
	.क्रमmat[PSC_CURRENT_OUT] = direct,
	.क्रमmat[PSC_TEMPERATURE] = direct,
	.m[PSC_VOLTAGE_IN] = 250,
	.b[PSC_VOLTAGE_IN] = 0,
	.R[PSC_VOLTAGE_IN] = 0,
	.m[PSC_VOLTAGE_OUT] = 2,
	.b[PSC_VOLTAGE_OUT] = 0,
	.R[PSC_VOLTAGE_OUT] = 3,
	.m[PSC_CURRENT_IN] = 1,
	.b[PSC_CURRENT_IN] = 0,
	.R[PSC_CURRENT_IN] = 2,
	.m[PSC_CURRENT_OUT] = 1,
	.b[PSC_CURRENT_OUT] = 0,
	.R[PSC_CURRENT_OUT] = 2,
	.m[PSC_TEMPERATURE] = 1,
	.b[PSC_TEMPERATURE] = 0,
	.R[PSC_TEMPERATURE] = 0,
	.func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_IIN | PMBUS_HAVE_VOUT |
		PMBUS_HAVE_IOUT | PMBUS_HAVE_TEMP,
	.पढ़ो_byte_data = ltc3815_पढ़ो_byte_data,
	.पढ़ो_word_data = ltc3815_पढ़ो_word_data,
	.ग_लिखो_byte = ltc3815_ग_लिखो_byte,
	.ग_लिखो_word_data = ltc3815_ग_लिखो_word_data,
पूर्ण;

अटल पूर्णांक ltc3815_probe(काष्ठा i2c_client *client)
अणु
	पूर्णांक chip_id;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_READ_WORD_DATA))
		वापस -ENODEV;

	chip_id = i2c_smbus_पढ़ो_word_data(client, LTC3815_MFR_SPECIAL_ID);
	अगर (chip_id < 0)
		वापस chip_id;
	अगर ((chip_id & LTC3815_ID_MASK) != LTC3815_ID)
		वापस -ENODEV;

	वापस pmbus_करो_probe(client, &ltc3815_info);
पूर्ण

अटल काष्ठा i2c_driver ltc3815_driver = अणु
	.driver = अणु
		   .name = "ltc3815",
		   पूर्ण,
	.probe_new = ltc3815_probe,
	.id_table = ltc3815_id,
पूर्ण;

module_i2c_driver(ltc3815_driver);

MODULE_AUTHOR("Guenter Roeck");
MODULE_DESCRIPTION("PMBus driver for LTC3815");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(PMBUS);
