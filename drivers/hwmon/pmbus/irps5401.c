<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Hardware monitoring driver क्रम the Infineon IRPS5401M PMIC.
 *
 * Copyright (c) 2019 SED Systems, a भागision of Calian Ltd.
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

#घोषणा IRPS5401_SW_FUNC (PMBUS_HAVE_VIN | PMBUS_HAVE_IIN | \
			  PMBUS_HAVE_STATUS_INPUT | \
			  PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT | \
			  PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT | \
			  PMBUS_HAVE_PIN | PMBUS_HAVE_POUT | \
			  PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP)

#घोषणा IRPS5401_LDO_FUNC (PMBUS_HAVE_VIN | \
			   PMBUS_HAVE_STATUS_INPUT | \
			   PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT | \
			   PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT | \
			   PMBUS_HAVE_PIN | PMBUS_HAVE_POUT | \
			   PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP)

अटल काष्ठा pmbus_driver_info irps5401_info = अणु
	.pages = 5,
	.func[0] = IRPS5401_SW_FUNC,
	.func[1] = IRPS5401_SW_FUNC,
	.func[2] = IRPS5401_SW_FUNC,
	.func[3] = IRPS5401_SW_FUNC,
	.func[4] = IRPS5401_LDO_FUNC,
पूर्ण;

अटल पूर्णांक irps5401_probe(काष्ठा i2c_client *client)
अणु
	वापस pmbus_करो_probe(client, &irps5401_info);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id irps5401_id[] = अणु
	अणु"irps5401", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, irps5401_id);

अटल काष्ठा i2c_driver irps5401_driver = अणु
	.driver = अणु
		   .name = "irps5401",
		   पूर्ण,
	.probe_new = irps5401_probe,
	.id_table = irps5401_id,
पूर्ण;

module_i2c_driver(irps5401_driver);

MODULE_AUTHOR("Robert Hancock");
MODULE_DESCRIPTION("PMBus driver for Infineon IRPS5401");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(PMBUS);
