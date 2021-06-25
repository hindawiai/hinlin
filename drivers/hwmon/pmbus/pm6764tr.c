<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Hardware monitoring driver क्रम STMicroelectronics digital controller PM6764TR
 */

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pmbus.h>
#समावेश "pmbus.h"

#घोषणा PM6764TR_PMBUS_READ_VOUT	0xD4

अटल पूर्णांक pm6764tr_पढ़ो_word_data(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक phase, पूर्णांक reg)
अणु
	पूर्णांक ret;

	चयन (reg) अणु
	हाल PMBUS_VIRT_READ_VMON:
		ret = pmbus_पढ़ो_word_data(client, page, phase, PM6764TR_PMBUS_READ_VOUT);
		अवरोध;
	शेष:
		ret = -ENODATA;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल काष्ठा pmbus_driver_info pm6764tr_info = अणु
	.pages = 1,
	.क्रमmat[PSC_VOLTAGE_IN] = linear,
	.क्रमmat[PSC_VOLTAGE_OUT] = vid,
	.क्रमmat[PSC_TEMPERATURE] = linear,
	.क्रमmat[PSC_CURRENT_OUT] = linear,
	.क्रमmat[PSC_POWER] = linear,
	.func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_IIN |  PMBUS_HAVE_PIN |
	    PMBUS_HAVE_IOUT | PMBUS_HAVE_POUT | PMBUS_HAVE_VMON |
		PMBUS_HAVE_STATUS_IOUT | PMBUS_HAVE_STATUS_VOUT |
		PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
	.पढ़ो_word_data = pm6764tr_पढ़ो_word_data,
पूर्ण;

अटल पूर्णांक pm6764tr_probe(काष्ठा i2c_client *client)
अणु
	वापस pmbus_करो_probe(client, &pm6764tr_info);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id pm6764tr_id[] = अणु
	अणु"pm6764tr", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, pm6764tr_id);

अटल स्थिर काष्ठा of_device_id __maybe_unused pm6764tr_of_match[] = अणु
	अणु.compatible = "st,pm6764tr"पूर्ण,
	अणुपूर्ण
पूर्ण;

/* This is the driver that will be inserted */
अटल काष्ठा i2c_driver pm6764tr_driver = अणु
	.driver = अणु
		   .name = "pm6764tr",
		   .of_match_table = of_match_ptr(pm6764tr_of_match),
		   पूर्ण,
	.probe_new = pm6764tr_probe,
	.id_table = pm6764tr_id,
पूर्ण;

module_i2c_driver(pm6764tr_driver);

MODULE_AUTHOR("Charles Hsu");
MODULE_DESCRIPTION("PMBus driver for  ST PM6764TR");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(PMBUS);
