<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hardware monitoring driver क्रम Maxim MAX16064
 *
 * Copyright (c) 2011 Ericsson AB.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश "pmbus.h"

#घोषणा MAX16064_MFR_VOUT_PEAK		0xd4
#घोषणा MAX16064_MFR_TEMPERATURE_PEAK	0xd6

अटल पूर्णांक max16064_पढ़ो_word_data(काष्ठा i2c_client *client, पूर्णांक page,
				   पूर्णांक phase, पूर्णांक reg)
अणु
	पूर्णांक ret;

	चयन (reg) अणु
	हाल PMBUS_VIRT_READ_VOUT_MAX:
		ret = pmbus_पढ़ो_word_data(client, page, phase,
					   MAX16064_MFR_VOUT_PEAK);
		अवरोध;
	हाल PMBUS_VIRT_READ_TEMP_MAX:
		ret = pmbus_पढ़ो_word_data(client, page, phase,
					   MAX16064_MFR_TEMPERATURE_PEAK);
		अवरोध;
	हाल PMBUS_VIRT_RESET_VOUT_HISTORY:
	हाल PMBUS_VIRT_RESET_TEMP_HISTORY:
		ret = 0;
		अवरोध;
	शेष:
		ret = -ENODATA;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक max16064_ग_लिखो_word_data(काष्ठा i2c_client *client, पूर्णांक page,
				    पूर्णांक reg, u16 word)
अणु
	पूर्णांक ret;

	चयन (reg) अणु
	हाल PMBUS_VIRT_RESET_VOUT_HISTORY:
		ret = pmbus_ग_लिखो_word_data(client, page,
					    MAX16064_MFR_VOUT_PEAK, 0);
		अवरोध;
	हाल PMBUS_VIRT_RESET_TEMP_HISTORY:
		ret = pmbus_ग_लिखो_word_data(client, page,
					    MAX16064_MFR_TEMPERATURE_PEAK,
					    0xffff);
		अवरोध;
	शेष:
		ret = -ENODATA;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल काष्ठा pmbus_driver_info max16064_info = अणु
	.pages = 4,
	.क्रमmat[PSC_VOLTAGE_IN] = direct,
	.क्रमmat[PSC_VOLTAGE_OUT] = direct,
	.क्रमmat[PSC_TEMPERATURE] = direct,
	.m[PSC_VOLTAGE_IN] = 19995,
	.b[PSC_VOLTAGE_IN] = 0,
	.R[PSC_VOLTAGE_IN] = -1,
	.m[PSC_VOLTAGE_OUT] = 19995,
	.b[PSC_VOLTAGE_OUT] = 0,
	.R[PSC_VOLTAGE_OUT] = -1,
	.m[PSC_TEMPERATURE] = -7612,
	.b[PSC_TEMPERATURE] = 335,
	.R[PSC_TEMPERATURE] = -3,
	.func[0] = PMBUS_HAVE_VOUT | PMBUS_HAVE_TEMP
		| PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_STATUS_TEMP,
	.func[1] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
	.func[2] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
	.func[3] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
	.पढ़ो_word_data = max16064_पढ़ो_word_data,
	.ग_लिखो_word_data = max16064_ग_लिखो_word_data,
पूर्ण;

अटल पूर्णांक max16064_probe(काष्ठा i2c_client *client)
अणु
	वापस pmbus_करो_probe(client, &max16064_info);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max16064_id[] = अणु
	अणु"max16064", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, max16064_id);

/* This is the driver that will be inserted */
अटल काष्ठा i2c_driver max16064_driver = अणु
	.driver = अणु
		   .name = "max16064",
		   पूर्ण,
	.probe_new = max16064_probe,
	.id_table = max16064_id,
पूर्ण;

module_i2c_driver(max16064_driver);

MODULE_AUTHOR("Guenter Roeck");
MODULE_DESCRIPTION("PMBus driver for Maxim MAX16064");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(PMBUS);
