<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hardware monitoring driver क्रम Maxim MAX8688
 *
 * Copyright (c) 2011 Ericsson AB.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश "pmbus.h"

#घोषणा MAX8688_MFR_VOUT_PEAK		0xd4
#घोषणा MAX8688_MFR_IOUT_PEAK		0xd5
#घोषणा MAX8688_MFR_TEMPERATURE_PEAK	0xd6
#घोषणा MAX8688_MFG_STATUS		0xd8

#घोषणा MAX8688_STATUS_OC_FAULT		BIT(4)
#घोषणा MAX8688_STATUS_OV_FAULT		BIT(5)
#घोषणा MAX8688_STATUS_OV_WARNING	BIT(8)
#घोषणा MAX8688_STATUS_UV_FAULT		BIT(9)
#घोषणा MAX8688_STATUS_UV_WARNING	BIT(10)
#घोषणा MAX8688_STATUS_UC_FAULT		BIT(11)
#घोषणा MAX8688_STATUS_OC_WARNING	BIT(12)
#घोषणा MAX8688_STATUS_OT_FAULT		BIT(13)
#घोषणा MAX8688_STATUS_OT_WARNING	BIT(14)

अटल पूर्णांक max8688_पढ़ो_word_data(काष्ठा i2c_client *client, पूर्णांक page,
				  पूर्णांक phase, पूर्णांक reg)
अणु
	पूर्णांक ret;

	अगर (page > 0)
		वापस -ENXIO;

	चयन (reg) अणु
	हाल PMBUS_VIRT_READ_VOUT_MAX:
		ret = pmbus_पढ़ो_word_data(client, 0, 0xff,
					   MAX8688_MFR_VOUT_PEAK);
		अवरोध;
	हाल PMBUS_VIRT_READ_IOUT_MAX:
		ret = pmbus_पढ़ो_word_data(client, 0, 0xff,
					   MAX8688_MFR_IOUT_PEAK);
		अवरोध;
	हाल PMBUS_VIRT_READ_TEMP_MAX:
		ret = pmbus_पढ़ो_word_data(client, 0, 0xff,
					   MAX8688_MFR_TEMPERATURE_PEAK);
		अवरोध;
	हाल PMBUS_VIRT_RESET_VOUT_HISTORY:
	हाल PMBUS_VIRT_RESET_IOUT_HISTORY:
	हाल PMBUS_VIRT_RESET_TEMP_HISTORY:
		ret = 0;
		अवरोध;
	शेष:
		ret = -ENODATA;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक max8688_ग_लिखो_word_data(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक reg,
				   u16 word)
अणु
	पूर्णांक ret;

	चयन (reg) अणु
	हाल PMBUS_VIRT_RESET_VOUT_HISTORY:
		ret = pmbus_ग_लिखो_word_data(client, 0, MAX8688_MFR_VOUT_PEAK,
					    0);
		अवरोध;
	हाल PMBUS_VIRT_RESET_IOUT_HISTORY:
		ret = pmbus_ग_लिखो_word_data(client, 0, MAX8688_MFR_IOUT_PEAK,
					    0);
		अवरोध;
	हाल PMBUS_VIRT_RESET_TEMP_HISTORY:
		ret = pmbus_ग_लिखो_word_data(client, 0,
					    MAX8688_MFR_TEMPERATURE_PEAK,
					    0xffff);
		अवरोध;
	शेष:
		ret = -ENODATA;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक max8688_पढ़ो_byte_data(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक reg)
अणु
	पूर्णांक ret = 0;
	पूर्णांक mfg_status;

	अगर (page > 0)
		वापस -ENXIO;

	चयन (reg) अणु
	हाल PMBUS_STATUS_VOUT:
		mfg_status = pmbus_पढ़ो_word_data(client, 0, 0xff,
						  MAX8688_MFG_STATUS);
		अगर (mfg_status < 0)
			वापस mfg_status;
		अगर (mfg_status & MAX8688_STATUS_UV_WARNING)
			ret |= PB_VOLTAGE_UV_WARNING;
		अगर (mfg_status & MAX8688_STATUS_UV_FAULT)
			ret |= PB_VOLTAGE_UV_FAULT;
		अगर (mfg_status & MAX8688_STATUS_OV_WARNING)
			ret |= PB_VOLTAGE_OV_WARNING;
		अगर (mfg_status & MAX8688_STATUS_OV_FAULT)
			ret |= PB_VOLTAGE_OV_FAULT;
		अवरोध;
	हाल PMBUS_STATUS_IOUT:
		mfg_status = pmbus_पढ़ो_word_data(client, 0, 0xff,
						  MAX8688_MFG_STATUS);
		अगर (mfg_status < 0)
			वापस mfg_status;
		अगर (mfg_status & MAX8688_STATUS_UC_FAULT)
			ret |= PB_IOUT_UC_FAULT;
		अगर (mfg_status & MAX8688_STATUS_OC_WARNING)
			ret |= PB_IOUT_OC_WARNING;
		अगर (mfg_status & MAX8688_STATUS_OC_FAULT)
			ret |= PB_IOUT_OC_FAULT;
		अवरोध;
	हाल PMBUS_STATUS_TEMPERATURE:
		mfg_status = pmbus_पढ़ो_word_data(client, 0, 0xff,
						  MAX8688_MFG_STATUS);
		अगर (mfg_status < 0)
			वापस mfg_status;
		अगर (mfg_status & MAX8688_STATUS_OT_WARNING)
			ret |= PB_TEMP_OT_WARNING;
		अगर (mfg_status & MAX8688_STATUS_OT_FAULT)
			ret |= PB_TEMP_OT_FAULT;
		अवरोध;
	शेष:
		ret = -ENODATA;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल काष्ठा pmbus_driver_info max8688_info = अणु
	.pages = 1,
	.क्रमmat[PSC_VOLTAGE_IN] = direct,
	.क्रमmat[PSC_VOLTAGE_OUT] = direct,
	.क्रमmat[PSC_TEMPERATURE] = direct,
	.क्रमmat[PSC_CURRENT_OUT] = direct,
	.m[PSC_VOLTAGE_IN] = 19995,
	.b[PSC_VOLTAGE_IN] = 0,
	.R[PSC_VOLTAGE_IN] = -1,
	.m[PSC_VOLTAGE_OUT] = 19995,
	.b[PSC_VOLTAGE_OUT] = 0,
	.R[PSC_VOLTAGE_OUT] = -1,
	.m[PSC_CURRENT_OUT] = 23109,
	.b[PSC_CURRENT_OUT] = 0,
	.R[PSC_CURRENT_OUT] = -2,
	.m[PSC_TEMPERATURE] = -7612,
	.b[PSC_TEMPERATURE] = 335,
	.R[PSC_TEMPERATURE] = -3,
	.func[0] = PMBUS_HAVE_VOUT | PMBUS_HAVE_IOUT | PMBUS_HAVE_TEMP
		| PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_STATUS_IOUT
		| PMBUS_HAVE_STATUS_TEMP,
	.पढ़ो_byte_data = max8688_पढ़ो_byte_data,
	.पढ़ो_word_data = max8688_पढ़ो_word_data,
	.ग_लिखो_word_data = max8688_ग_लिखो_word_data,
पूर्ण;

अटल पूर्णांक max8688_probe(काष्ठा i2c_client *client)
अणु
	वापस pmbus_करो_probe(client, &max8688_info);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max8688_id[] = अणु
	अणु"max8688", 0पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, max8688_id);

/* This is the driver that will be inserted */
अटल काष्ठा i2c_driver max8688_driver = अणु
	.driver = अणु
		   .name = "max8688",
		   पूर्ण,
	.probe_new = max8688_probe,
	.id_table = max8688_id,
पूर्ण;

module_i2c_driver(max8688_driver);

MODULE_AUTHOR("Guenter Roeck");
MODULE_DESCRIPTION("PMBus driver for Maxim MAX8688");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(PMBUS);
