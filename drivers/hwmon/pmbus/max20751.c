<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hardware monitoring driver क्रम Maxim MAX20751
 *
 * Copyright (c) 2015 Guenter Roeck
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश "pmbus.h"

अटल काष्ठा pmbus_driver_info max20751_info = अणु
	.pages = 1,
	.क्रमmat[PSC_VOLTAGE_IN] = linear,
	.क्रमmat[PSC_VOLTAGE_OUT] = vid,
	.vrm_version[0] = vr12,
	.क्रमmat[PSC_TEMPERATURE] = linear,
	.क्रमmat[PSC_CURRENT_OUT] = linear,
	.क्रमmat[PSC_POWER] = linear,
	.func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
		PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
		PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP |
		PMBUS_HAVE_POUT,
पूर्ण;

अटल पूर्णांक max20751_probe(काष्ठा i2c_client *client)
अणु
	वापस pmbus_करो_probe(client, &max20751_info);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max20751_id[] = अणु
	अणु"max20751", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, max20751_id);

अटल काष्ठा i2c_driver max20751_driver = अणु
	.driver = अणु
		   .name = "max20751",
		   पूर्ण,
	.probe_new = max20751_probe,
	.id_table = max20751_id,
पूर्ण;

module_i2c_driver(max20751_driver);

MODULE_AUTHOR("Guenter Roeck <linux@roeck-us.net>");
MODULE_DESCRIPTION("PMBus driver for Maxim MAX20751");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(PMBUS);
