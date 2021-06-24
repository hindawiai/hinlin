<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hardware monitoring driver क्रम FSP 3Y-Power PSUs
 *
 * Copyright (c) 2021 Vथँclav Kubernथँt, CESNET
 *
 * This driver is mostly reverse engineered with the help of a tool called pmbus_peek written by
 * David Brownell (and later aकरोpted by Jan Kundrथँt). The device has some sort of a timing issue
 * when चयनing pages, details are explained in the code. The driver support is limited. It
 * exposes only the values, that have been tested to work correctly. Unsupported values either
 * aren't supported by the devices or their encondings are unknown.
 */

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश "pmbus.h"

#घोषणा YM2151_PAGE_12V_LOG	0x00
#घोषणा YM2151_PAGE_12V_REAL	0x00
#घोषणा YM2151_PAGE_5VSB_LOG	0x01
#घोषणा YM2151_PAGE_5VSB_REAL	0x20
#घोषणा YH5151E_PAGE_12V_LOG	0x00
#घोषणा YH5151E_PAGE_12V_REAL	0x00
#घोषणा YH5151E_PAGE_5V_LOG	0x01
#घोषणा YH5151E_PAGE_5V_REAL	0x10
#घोषणा YH5151E_PAGE_3V3_LOG	0x02
#घोषणा YH5151E_PAGE_3V3_REAL	0x11

क्रमागत chips अणु
	ym2151e,
	yh5151e
पूर्ण;

काष्ठा fsp3y_data अणु
	काष्ठा pmbus_driver_info info;
	पूर्णांक chip;
	पूर्णांक page;

	bool vout_linear_11;
पूर्ण;

#घोषणा to_fsp3y_data(x) container_of(x, काष्ठा fsp3y_data, info)

अटल पूर्णांक page_log_to_page_real(पूर्णांक page_log, क्रमागत chips chip)
अणु
	चयन (chip) अणु
	हाल ym2151e:
		चयन (page_log) अणु
		हाल YM2151_PAGE_12V_LOG:
			वापस YM2151_PAGE_12V_REAL;
		हाल YM2151_PAGE_5VSB_LOG:
			वापस YM2151_PAGE_5VSB_REAL;
		पूर्ण
		वापस -EINVAL;
	हाल yh5151e:
		चयन (page_log) अणु
		हाल YH5151E_PAGE_12V_LOG:
			वापस YH5151E_PAGE_12V_REAL;
		हाल YH5151E_PAGE_5V_LOG:
			वापस YH5151E_PAGE_5V_REAL;
		हाल YH5151E_PAGE_3V3_LOG:
			वापस YH5151E_PAGE_3V3_REAL;
		पूर्ण
		वापस -EINVAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक set_page(काष्ठा i2c_client *client, पूर्णांक page_log)
अणु
	स्थिर काष्ठा pmbus_driver_info *info = pmbus_get_driver_info(client);
	काष्ठा fsp3y_data *data = to_fsp3y_data(info);
	पूर्णांक rv;
	पूर्णांक page_real;

	अगर (page_log < 0)
		वापस 0;

	page_real = page_log_to_page_real(page_log, data->chip);
	अगर (page_real < 0)
		वापस page_real;

	अगर (data->page != page_real) अणु
		rv = i2c_smbus_ग_लिखो_byte_data(client, PMBUS_PAGE, page_real);
		अगर (rv < 0)
			वापस rv;

		data->page = page_real;

		/*
		 * Testing showed that the device has a timing issue. After
		 * setting a page, it takes a जबतक, beक्रमe the device actually
		 * gives the correct values from the correct page. 20 ms was
		 * tested to be enough to not give wrong values (15 ms wasn't
		 * enough).
		 */
		usleep_range(20000, 30000);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsp3y_पढ़ो_byte_data(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक reg)
अणु
	स्थिर काष्ठा pmbus_driver_info *info = pmbus_get_driver_info(client);
	काष्ठा fsp3y_data *data = to_fsp3y_data(info);
	पूर्णांक rv;

	/*
	 * Inject an exponent क्रम non-compliant YH5151-E.
	 */
	अगर (data->vout_linear_11 && reg == PMBUS_VOUT_MODE)
		वापस 0x1A;

	rv = set_page(client, page);
	अगर (rv < 0)
		वापस rv;

	वापस i2c_smbus_पढ़ो_byte_data(client, reg);
पूर्ण

अटल पूर्णांक fsp3y_पढ़ो_word_data(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक phase, पूर्णांक reg)
अणु
	स्थिर काष्ठा pmbus_driver_info *info = pmbus_get_driver_info(client);
	काष्ठा fsp3y_data *data = to_fsp3y_data(info);
	पूर्णांक rv;

	/*
	 * This masks commands which weren't tested to work correctly. Some of
	 * the masked commands वापस 0xFFFF. These would probably get tagged as
	 * invalid by pmbus_core. Other ones करो वापस values which might be
	 * useful (that is, they are not 0xFFFF), but their encoding is unknown,
	 * and so they are unsupported.
	 */
	चयन (reg) अणु
	हाल PMBUS_READ_FAN_SPEED_1:
	हाल PMBUS_READ_IIN:
	हाल PMBUS_READ_IOUT:
	हाल PMBUS_READ_PIN:
	हाल PMBUS_READ_POUT:
	हाल PMBUS_READ_TEMPERATURE_1:
	हाल PMBUS_READ_TEMPERATURE_2:
	हाल PMBUS_READ_TEMPERATURE_3:
	हाल PMBUS_READ_VIN:
	हाल PMBUS_READ_VOUT:
	हाल PMBUS_STATUS_WORD:
		अवरोध;
	शेष:
		वापस -ENXIO;
	पूर्ण

	rv = set_page(client, page);
	अगर (rv < 0)
		वापस rv;

	rv = i2c_smbus_पढ़ो_word_data(client, reg);
	अगर (rv < 0)
		वापस rv;

	/*
	 * Handle YH-5151E non-compliant linear11 vout voltage.
	 */
	अगर (data->vout_linear_11 && reg == PMBUS_READ_VOUT)
		rv = sign_extend32(rv, 10) & 0xffff;

	वापस rv;
पूर्ण

अटल काष्ठा pmbus_driver_info fsp3y_info[] = अणु
	[ym2151e] = अणु
		.pages = 2,
		.func[YM2151_PAGE_12V_LOG] =
			PMBUS_HAVE_VOUT | PMBUS_HAVE_IOUT |
			PMBUS_HAVE_PIN | PMBUS_HAVE_POUT  |
			PMBUS_HAVE_TEMP | PMBUS_HAVE_TEMP2 |
			PMBUS_HAVE_VIN | PMBUS_HAVE_IIN |
			PMBUS_HAVE_FAN12,
		.func[YM2151_PAGE_5VSB_LOG] =
			PMBUS_HAVE_VOUT | PMBUS_HAVE_IOUT,
			PMBUS_HAVE_IIN,
		.पढ़ो_word_data = fsp3y_पढ़ो_word_data,
		.पढ़ो_byte_data = fsp3y_पढ़ो_byte_data,
	पूर्ण,
	[yh5151e] = अणु
		.pages = 3,
		.func[YH5151E_PAGE_12V_LOG] =
			PMBUS_HAVE_VOUT | PMBUS_HAVE_IOUT |
			PMBUS_HAVE_POUT  |
			PMBUS_HAVE_TEMP | PMBUS_HAVE_TEMP2 | PMBUS_HAVE_TEMP3,
		.func[YH5151E_PAGE_5V_LOG] =
			PMBUS_HAVE_VOUT | PMBUS_HAVE_IOUT |
			PMBUS_HAVE_POUT,
		.func[YH5151E_PAGE_3V3_LOG] =
			PMBUS_HAVE_VOUT | PMBUS_HAVE_IOUT |
			PMBUS_HAVE_POUT,
		.पढ़ो_word_data = fsp3y_पढ़ो_word_data,
		.पढ़ो_byte_data = fsp3y_पढ़ो_byte_data,
	पूर्ण
पूर्ण;

अटल पूर्णांक fsp3y_detect(काष्ठा i2c_client *client)
अणु
	पूर्णांक rv;
	u8 buf[I2C_SMBUS_BLOCK_MAX + 1];

	rv = i2c_smbus_पढ़ो_block_data(client, PMBUS_MFR_MODEL, buf);
	अगर (rv < 0)
		वापस rv;

	buf[rv] = '\0';

	अगर (rv == 8) अणु
		अगर (!म_भेद(buf, "YM-2151E"))
			वापस ym2151e;
		अन्यथा अगर (!म_भेद(buf, "YH-5151E"))
			वापस yh5151e;
	पूर्ण

	dev_err(&client->dev, "Unsupported model %.*s\n", rv, buf);
	वापस -ENODEV;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id fsp3y_id[] = अणु
	अणु"ym2151e", ym2151eपूर्ण,
	अणु"yh5151e", yh5151eपूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक fsp3y_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा fsp3y_data *data;
	स्थिर काष्ठा i2c_device_id *id;
	पूर्णांक rv;

	data = devm_kzalloc(&client->dev, माप(काष्ठा fsp3y_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->chip = fsp3y_detect(client);
	अगर (data->chip < 0)
		वापस data->chip;

	id = i2c_match_id(fsp3y_id, client);
	अगर (data->chip != id->driver_data)
		dev_warn(&client->dev, "Device mismatch: Configured %s (%d), detected %d\n",
			 id->name, (पूर्णांक)id->driver_data, data->chip);

	rv = i2c_smbus_पढ़ो_byte_data(client, PMBUS_PAGE);
	अगर (rv < 0)
		वापस rv;
	data->page = rv;

	data->info = fsp3y_info[data->chip];

	/*
	 * YH-5151E someबार reports vout in linear11 and someबार in
	 * linear16. This depends on the exact inभागidual piece of hardware. One
	 * YH-5151E can use linear16 and another might use linear11 instead.
	 *
	 * The क्रमmat can be recognized by पढ़ोing VOUT_MODE - अगर it करोesn't
	 * report a valid exponent, then vout uses linear11. Otherwise, the
	 * device is compliant and uses linear16.
	 */
	data->vout_linear_11 = false;
	अगर (data->chip == yh5151e) अणु
		rv = i2c_smbus_पढ़ो_byte_data(client, PMBUS_VOUT_MODE);
		अगर (rv < 0)
			वापस rv;

		अगर (rv == 0xFF)
			data->vout_linear_11 = true;
	पूर्ण

	वापस pmbus_करो_probe(client, &data->info);
पूर्ण

MODULE_DEVICE_TABLE(i2c, fsp3y_id);

अटल काष्ठा i2c_driver fsp3y_driver = अणु
	.driver = अणु
		   .name = "fsp3y",
		   पूर्ण,
	.probe_new = fsp3y_probe,
	.id_table = fsp3y_id
पूर्ण;

module_i2c_driver(fsp3y_driver);

MODULE_AUTHOR("Vथँclav Kubernथँt");
MODULE_DESCRIPTION("PMBus driver for FSP/3Y-Power power supplies");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(PMBUS);
