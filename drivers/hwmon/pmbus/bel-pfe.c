<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Hardware monitoring driver क्रम BEL PFE family घातer supplies.
 *
 * Copyright (c) 2019 Facebook Inc.
 */

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pmbus.h>

#समावेश "pmbus.h"

क्रमागत chips अणुpfe1100, pfe3000पूर्ण;

/*
 * Disable status check क्रम pfe3000 devices, because some devices report
 * communication error (invalid command) क्रम VOUT_MODE command (0x20)
 * although correct VOUT_MODE (0x16) is वापसed: it leads to incorrect
 * exponent in linear mode.
 */
अटल काष्ठा pmbus_platक्रमm_data pfe3000_plat_data = अणु
	.flags = PMBUS_SKIP_STATUS_CHECK,
पूर्ण;

अटल काष्ठा pmbus_driver_info pfe_driver_info[] = अणु
	[pfe1100] = अणु
		.pages = 1,
		.क्रमmat[PSC_VOLTAGE_IN] = linear,
		.क्रमmat[PSC_VOLTAGE_OUT] = linear,
		.क्रमmat[PSC_CURRENT_IN] = linear,
		.क्रमmat[PSC_CURRENT_OUT] = linear,
		.क्रमmat[PSC_POWER] = linear,
		.क्रमmat[PSC_TEMPERATURE] = linear,
		.क्रमmat[PSC_FAN] = linear,

		.func[0] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
			   PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
			   PMBUS_HAVE_POUT |
			   PMBUS_HAVE_VIN | PMBUS_HAVE_IIN |
			   PMBUS_HAVE_PIN | PMBUS_HAVE_STATUS_INPUT |
			   PMBUS_HAVE_TEMP | PMBUS_HAVE_TEMP2 |
			   PMBUS_HAVE_STATUS_TEMP |
			   PMBUS_HAVE_FAN12,
	पूर्ण,

	[pfe3000] = अणु
		.pages = 7,
		.क्रमmat[PSC_VOLTAGE_IN] = linear,
		.क्रमmat[PSC_VOLTAGE_OUT] = linear,
		.क्रमmat[PSC_CURRENT_IN] = linear,
		.क्रमmat[PSC_CURRENT_OUT] = linear,
		.क्रमmat[PSC_POWER] = linear,
		.क्रमmat[PSC_TEMPERATURE] = linear,
		.क्रमmat[PSC_FAN] = linear,

		/* Page 0: V1. */
		.func[0] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
			   PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
			   PMBUS_HAVE_POUT | PMBUS_HAVE_FAN12 |
			   PMBUS_HAVE_VIN | PMBUS_HAVE_IIN |
			   PMBUS_HAVE_PIN | PMBUS_HAVE_STATUS_INPUT |
			   PMBUS_HAVE_TEMP | PMBUS_HAVE_TEMP2 |
			   PMBUS_HAVE_TEMP3 | PMBUS_HAVE_STATUS_TEMP |
			   PMBUS_HAVE_VCAP,

		/* Page 1: Vsb. */
		.func[1] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
			   PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
			   PMBUS_HAVE_PIN | PMBUS_HAVE_STATUS_INPUT |
			   PMBUS_HAVE_POUT,

		/*
		 * Page 2: V1 Ishare.
		 * Page 3: Reserved.
		 * Page 4: V1 Cathode.
		 * Page 5: Vsb Cathode.
		 * Page 6: V1 Sense.
		 */
		.func[2] = PMBUS_HAVE_VOUT,
		.func[4] = PMBUS_HAVE_VOUT,
		.func[5] = PMBUS_HAVE_VOUT,
		.func[6] = PMBUS_HAVE_VOUT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id pfe_device_id[];

अटल पूर्णांक pfe_pmbus_probe(काष्ठा i2c_client *client)
अणु
	पूर्णांक model;

	model = (पूर्णांक)i2c_match_id(pfe_device_id, client)->driver_data;

	/*
	 * PFE3000-12-069RA devices may not stay in page 0 during device
	 * probe which leads to probe failure (पढ़ो status word failed).
	 * So let's set the device to page 0 at the beginning.
	 */
	अगर (model == pfe3000) अणु
		client->dev.platक्रमm_data = &pfe3000_plat_data;
		i2c_smbus_ग_लिखो_byte_data(client, PMBUS_PAGE, 0);
	पूर्ण

	वापस pmbus_करो_probe(client, &pfe_driver_info[model]);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id pfe_device_id[] = अणु
	अणु"pfe1100", pfe1100पूर्ण,
	अणु"pfe3000", pfe3000पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, pfe_device_id);

अटल काष्ठा i2c_driver pfe_pmbus_driver = अणु
	.driver = अणु
		   .name = "bel-pfe",
	पूर्ण,
	.probe_new = pfe_pmbus_probe,
	.id_table = pfe_device_id,
पूर्ण;

module_i2c_driver(pfe_pmbus_driver);

MODULE_AUTHOR("Tao Ren <rentao.bupt@gmail.com>");
MODULE_DESCRIPTION("PMBus driver for BEL PFE Family Power Supplies");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(PMBUS);
