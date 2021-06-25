<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Hardware monitoring driver क्रम Infineon IR38064
 *
 * Copyright (c) 2017 Google Inc
 *
 * VOUT_MODE is not supported by the device. The driver fakes VOUT linear16
 * mode with exponent value -8 as direct mode with m=256/b=0/R=0.
 *          
 * The device supports VOUT_PEAK, IOUT_PEAK, and TEMPERATURE_PEAK, however
 * this driver करोes not currently support them.
 */

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश "pmbus.h"

अटल काष्ठा pmbus_driver_info ir38064_info = अणु
	.pages = 1,
	.क्रमmat[PSC_VOLTAGE_IN] = linear,
	.क्रमmat[PSC_VOLTAGE_OUT] = direct,
	.क्रमmat[PSC_CURRENT_OUT] = linear,
	.क्रमmat[PSC_POWER] = linear,
	.क्रमmat[PSC_TEMPERATURE] = linear,
	.m[PSC_VOLTAGE_OUT] = 256,
	.b[PSC_VOLTAGE_OUT] = 0,
	.R[PSC_VOLTAGE_OUT] = 0,
	.func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_STATUS_INPUT
	    | PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP
	    | PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
	    | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT
	    | PMBUS_HAVE_POUT,
पूर्ण;

अटल पूर्णांक ir38064_probe(काष्ठा i2c_client *client)
अणु
	वापस pmbus_करो_probe(client, &ir38064_info);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ir38064_id[] = अणु
	अणु"ir38064", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, ir38064_id);

/* This is the driver that will be inserted */
अटल काष्ठा i2c_driver ir38064_driver = अणु
	.driver = अणु
		   .name = "ir38064",
		   पूर्ण,
	.probe_new = ir38064_probe,
	.id_table = ir38064_id,
पूर्ण;

module_i2c_driver(ir38064_driver);

MODULE_AUTHOR("Maxim Sloyko <maxims@google.com>");
MODULE_DESCRIPTION("PMBus driver for Infineon IR38064");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(PMBUS);
