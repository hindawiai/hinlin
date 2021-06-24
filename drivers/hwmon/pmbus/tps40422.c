<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hardware monitoring driver क्रम TI TPS40422
 *
 * Copyright (c) 2014 Nokia Solutions and Networks.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश "pmbus.h"

अटल काष्ठा pmbus_driver_info tps40422_info = अणु
	.pages = 2,
	.क्रमmat[PSC_VOLTAGE_IN] = linear,
	.क्रमmat[PSC_VOLTAGE_OUT] = linear,
	.क्रमmat[PSC_TEMPERATURE] = linear,
	.func[0] = PMBUS_HAVE_VOUT | PMBUS_HAVE_TEMP2
		| PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_STATUS_TEMP
		| PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT,
	.func[1] = PMBUS_HAVE_VOUT | PMBUS_HAVE_TEMP2
		| PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_STATUS_TEMP
		| PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT,
पूर्ण;

अटल पूर्णांक tps40422_probe(काष्ठा i2c_client *client)
अणु
	वापस pmbus_करो_probe(client, &tps40422_info);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tps40422_id[] = अणु
	अणु"tps40422", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, tps40422_id);

/* This is the driver that will be inserted */
अटल काष्ठा i2c_driver tps40422_driver = अणु
	.driver = अणु
		   .name = "tps40422",
		   पूर्ण,
	.probe_new = tps40422_probe,
	.id_table = tps40422_id,
पूर्ण;

module_i2c_driver(tps40422_driver);

MODULE_AUTHOR("Zhu Laiwen <richard.zhu@nsn.com>");
MODULE_DESCRIPTION("PMBus driver for TI TPS40422");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(PMBUS);
