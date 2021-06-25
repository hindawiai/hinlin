<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hardware monitoring driver क्रम PMBus devices
 *
 * Copyright (c) 2010, 2011 Ericsson AB.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/i2c.h>
#समावेश <linux/pmbus.h>
#समावेश "pmbus.h"

काष्ठा pmbus_device_info अणु
	पूर्णांक pages;
	u32 flags;
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id pmbus_id[];

/*
 * Find sensor groups and status रेजिस्टरs on each page.
 */
अटल व्योम pmbus_find_sensor_groups(काष्ठा i2c_client *client,
				     काष्ठा pmbus_driver_info *info)
अणु
	पूर्णांक page;

	/* Sensors detected on page 0 only */
	अगर (pmbus_check_word_रेजिस्टर(client, 0, PMBUS_READ_VIN))
		info->func[0] |= PMBUS_HAVE_VIN;
	अगर (pmbus_check_word_रेजिस्टर(client, 0, PMBUS_READ_VCAP))
		info->func[0] |= PMBUS_HAVE_VCAP;
	अगर (pmbus_check_word_रेजिस्टर(client, 0, PMBUS_READ_IIN))
		info->func[0] |= PMBUS_HAVE_IIN;
	अगर (pmbus_check_word_रेजिस्टर(client, 0, PMBUS_READ_PIN))
		info->func[0] |= PMBUS_HAVE_PIN;
	अगर (info->func[0]
	    && pmbus_check_byte_रेजिस्टर(client, 0, PMBUS_STATUS_INPUT))
		info->func[0] |= PMBUS_HAVE_STATUS_INPUT;
	अगर (pmbus_check_byte_रेजिस्टर(client, 0, PMBUS_FAN_CONFIG_12) &&
	    pmbus_check_word_रेजिस्टर(client, 0, PMBUS_READ_FAN_SPEED_1)) अणु
		info->func[0] |= PMBUS_HAVE_FAN12;
		अगर (pmbus_check_byte_रेजिस्टर(client, 0, PMBUS_STATUS_FAN_12))
			info->func[0] |= PMBUS_HAVE_STATUS_FAN12;
	पूर्ण
	अगर (pmbus_check_byte_रेजिस्टर(client, 0, PMBUS_FAN_CONFIG_34) &&
	    pmbus_check_word_रेजिस्टर(client, 0, PMBUS_READ_FAN_SPEED_3)) अणु
		info->func[0] |= PMBUS_HAVE_FAN34;
		अगर (pmbus_check_byte_रेजिस्टर(client, 0, PMBUS_STATUS_FAN_34))
			info->func[0] |= PMBUS_HAVE_STATUS_FAN34;
	पूर्ण
	अगर (pmbus_check_word_रेजिस्टर(client, 0, PMBUS_READ_TEMPERATURE_1))
		info->func[0] |= PMBUS_HAVE_TEMP;
	अगर (pmbus_check_word_रेजिस्टर(client, 0, PMBUS_READ_TEMPERATURE_2))
		info->func[0] |= PMBUS_HAVE_TEMP2;
	अगर (pmbus_check_word_रेजिस्टर(client, 0, PMBUS_READ_TEMPERATURE_3))
		info->func[0] |= PMBUS_HAVE_TEMP3;
	अगर (info->func[0] & (PMBUS_HAVE_TEMP | PMBUS_HAVE_TEMP2
			     | PMBUS_HAVE_TEMP3)
	    && pmbus_check_byte_रेजिस्टर(client, 0,
					 PMBUS_STATUS_TEMPERATURE))
			info->func[0] |= PMBUS_HAVE_STATUS_TEMP;

	/* Sensors detected on all pages */
	क्रम (page = 0; page < info->pages; page++) अणु
		अगर (pmbus_check_word_रेजिस्टर(client, page, PMBUS_READ_VOUT)) अणु
			info->func[page] |= PMBUS_HAVE_VOUT;
			अगर (pmbus_check_byte_रेजिस्टर(client, page,
						      PMBUS_STATUS_VOUT))
				info->func[page] |= PMBUS_HAVE_STATUS_VOUT;
		पूर्ण
		अगर (pmbus_check_word_रेजिस्टर(client, page, PMBUS_READ_IOUT)) अणु
			info->func[page] |= PMBUS_HAVE_IOUT;
			अगर (pmbus_check_byte_रेजिस्टर(client, 0,
						      PMBUS_STATUS_IOUT))
				info->func[page] |= PMBUS_HAVE_STATUS_IOUT;
		पूर्ण
		अगर (pmbus_check_word_रेजिस्टर(client, page, PMBUS_READ_POUT))
			info->func[page] |= PMBUS_HAVE_POUT;
	पूर्ण
पूर्ण

/*
 * Identअगरy chip parameters.
 */
अटल पूर्णांक pmbus_identअगरy(काष्ठा i2c_client *client,
			  काष्ठा pmbus_driver_info *info)
अणु
	पूर्णांक ret = 0;

	अगर (!info->pages) अणु
		/*
		 * Check अगर the PAGE command is supported. If it is,
		 * keep setting the page number until it fails or until the
		 * maximum number of pages has been reached. Assume that
		 * this is the number of pages supported by the chip.
		 */
		अगर (pmbus_check_byte_रेजिस्टर(client, 0, PMBUS_PAGE)) अणु
			पूर्णांक page;

			क्रम (page = 1; page < PMBUS_PAGES; page++) अणु
				अगर (pmbus_set_page(client, page, 0xff) < 0)
					अवरोध;
			पूर्ण
			pmbus_set_page(client, 0, 0xff);
			info->pages = page;
		पूर्ण अन्यथा अणु
			info->pages = 1;
		पूर्ण

		pmbus_clear_faults(client);
	पूर्ण

	अगर (pmbus_check_byte_रेजिस्टर(client, 0, PMBUS_VOUT_MODE)) अणु
		पूर्णांक vout_mode, i;

		vout_mode = pmbus_पढ़ो_byte_data(client, 0, PMBUS_VOUT_MODE);
		अगर (vout_mode >= 0 && vout_mode != 0xff) अणु
			चयन (vout_mode >> 5) अणु
			हाल 0:
				अवरोध;
			हाल 1:
				info->क्रमmat[PSC_VOLTAGE_OUT] = vid;
				क्रम (i = 0; i < info->pages; i++)
					info->vrm_version[i] = vr11;
				अवरोध;
			हाल 2:
				info->क्रमmat[PSC_VOLTAGE_OUT] = direct;
				अवरोध;
			शेष:
				ret = -ENODEV;
				जाओ पात;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * We should check अगर the COEFFICIENTS रेजिस्टर is supported.
	 * If it is, and the chip is configured क्रम direct mode, we can पढ़ो
	 * the coefficients from the chip, one set per group of sensor
	 * रेजिस्टरs.
	 *
	 * To करो this, we will need access to a chip which actually supports the
	 * COEFFICIENTS command, since the command is too complex to implement
	 * without testing it. Until then, पात अगर a chip configured क्रम direct
	 * mode was detected.
	 */
	अगर (info->क्रमmat[PSC_VOLTAGE_OUT] == direct) अणु
		ret = -ENODEV;
		जाओ पात;
	पूर्ण

	/* Try to find sensor groups  */
	pmbus_find_sensor_groups(client, info);
पात:
	वापस ret;
पूर्ण

अटल पूर्णांक pmbus_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा pmbus_driver_info *info;
	काष्ठा pmbus_platक्रमm_data *pdata = शून्य;
	काष्ठा device *dev = &client->dev;
	काष्ठा pmbus_device_info *device_info;

	info = devm_kzalloc(dev, माप(काष्ठा pmbus_driver_info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	device_info = (काष्ठा pmbus_device_info *)i2c_match_id(pmbus_id, client)->driver_data;
	अगर (device_info->flags & PMBUS_SKIP_STATUS_CHECK) अणु
		pdata = devm_kzalloc(dev, माप(काष्ठा pmbus_platक्रमm_data),
				     GFP_KERNEL);
		अगर (!pdata)
			वापस -ENOMEM;

		pdata->flags = PMBUS_SKIP_STATUS_CHECK;
	पूर्ण

	info->pages = device_info->pages;
	info->identअगरy = pmbus_identअगरy;
	dev->platक्रमm_data = pdata;

	वापस pmbus_करो_probe(client, info);
पूर्ण

अटल स्थिर काष्ठा pmbus_device_info pmbus_info_one = अणु
	.pages = 1,
	.flags = 0
पूर्ण;
अटल स्थिर काष्ठा pmbus_device_info pmbus_info_zero = अणु
	.pages = 0,
	.flags = 0
पूर्ण;
अटल स्थिर काष्ठा pmbus_device_info pmbus_info_one_skip = अणु
	.pages = 1,
	.flags = PMBUS_SKIP_STATUS_CHECK
पूर्ण;

/*
 * Use driver_data to set the number of pages supported by the chip.
 */
अटल स्थिर काष्ठा i2c_device_id pmbus_id[] = अणु
	अणु"adp4000", (kernel_uदीर्घ_t)&pmbus_info_oneपूर्ण,
	अणु"bmr453", (kernel_uदीर्घ_t)&pmbus_info_oneपूर्ण,
	अणु"bmr454", (kernel_uदीर्घ_t)&pmbus_info_oneपूर्ण,
	अणु"dps460", (kernel_uदीर्घ_t)&pmbus_info_one_skipपूर्ण,
	अणु"dps650ab", (kernel_uदीर्घ_t)&pmbus_info_one_skipपूर्ण,
	अणु"dps800", (kernel_uदीर्घ_t)&pmbus_info_one_skipपूर्ण,
	अणु"max20796", (kernel_uदीर्घ_t)&pmbus_info_oneपूर्ण,
	अणु"mdt040", (kernel_uदीर्घ_t)&pmbus_info_oneपूर्ण,
	अणु"ncp4200", (kernel_uदीर्घ_t)&pmbus_info_oneपूर्ण,
	अणु"ncp4208", (kernel_uदीर्घ_t)&pmbus_info_oneपूर्ण,
	अणु"pdt003", (kernel_uदीर्घ_t)&pmbus_info_oneपूर्ण,
	अणु"pdt006", (kernel_uदीर्घ_t)&pmbus_info_oneपूर्ण,
	अणु"pdt012", (kernel_uदीर्घ_t)&pmbus_info_oneपूर्ण,
	अणु"pmbus", (kernel_uदीर्घ_t)&pmbus_info_zeroपूर्ण,
	अणु"sgd009", (kernel_uदीर्घ_t)&pmbus_info_one_skipपूर्ण,
	अणु"tps40400", (kernel_uदीर्घ_t)&pmbus_info_oneपूर्ण,
	अणु"tps544b20", (kernel_uदीर्घ_t)&pmbus_info_oneपूर्ण,
	अणु"tps544b25", (kernel_uदीर्घ_t)&pmbus_info_oneपूर्ण,
	अणु"tps544c20", (kernel_uदीर्घ_t)&pmbus_info_oneपूर्ण,
	अणु"tps544c25", (kernel_uदीर्घ_t)&pmbus_info_oneपूर्ण,
	अणु"udt020", (kernel_uदीर्घ_t)&pmbus_info_oneपूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, pmbus_id);

/* This is the driver that will be inserted */
अटल काष्ठा i2c_driver pmbus_driver = अणु
	.driver = अणु
		   .name = "pmbus",
		   पूर्ण,
	.probe_new = pmbus_probe,
	.id_table = pmbus_id,
पूर्ण;

module_i2c_driver(pmbus_driver);

MODULE_AUTHOR("Guenter Roeck");
MODULE_DESCRIPTION("Generic PMBus driver");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(PMBUS);
