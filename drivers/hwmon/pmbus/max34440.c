<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hardware monitoring driver क्रम Maxim MAX34440/MAX34441
 *
 * Copyright (c) 2011 Ericsson AB.
 * Copyright (c) 2012 Guenter Roeck
 */

#समावेश <linux/bitops.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश "pmbus.h"

क्रमागत chips अणु max34440, max34441, max34446, max34451, max34460, max34461 पूर्ण;

#घोषणा MAX34440_MFR_VOUT_PEAK		0xd4
#घोषणा MAX34440_MFR_IOUT_PEAK		0xd5
#घोषणा MAX34440_MFR_TEMPERATURE_PEAK	0xd6
#घोषणा MAX34440_MFR_VOUT_MIN		0xd7

#घोषणा MAX34446_MFR_POUT_PEAK		0xe0
#घोषणा MAX34446_MFR_POUT_AVG		0xe1
#घोषणा MAX34446_MFR_IOUT_AVG		0xe2
#घोषणा MAX34446_MFR_TEMPERATURE_AVG	0xe3

#घोषणा MAX34440_STATUS_OC_WARN		BIT(0)
#घोषणा MAX34440_STATUS_OC_FAULT	BIT(1)
#घोषणा MAX34440_STATUS_OT_FAULT	BIT(5)
#घोषणा MAX34440_STATUS_OT_WARN		BIT(6)

/*
 * The whole max344* family have IOUT_OC_WARN_LIMIT and IOUT_OC_FAULT_LIMIT
 * swapped from the standard pmbus spec addresses.
 */
#घोषणा MAX34440_IOUT_OC_WARN_LIMIT	0x46
#घोषणा MAX34440_IOUT_OC_FAULT_LIMIT	0x4A

#घोषणा MAX34451_MFR_CHANNEL_CONFIG	0xe4
#घोषणा MAX34451_MFR_CHANNEL_CONFIG_SEL_MASK	0x3f

काष्ठा max34440_data अणु
	पूर्णांक id;
	काष्ठा pmbus_driver_info info;
पूर्ण;

#घोषणा to_max34440_data(x)  container_of(x, काष्ठा max34440_data, info)

अटल स्थिर काष्ठा i2c_device_id max34440_id[];

अटल पूर्णांक max34440_पढ़ो_word_data(काष्ठा i2c_client *client, पूर्णांक page,
				   पूर्णांक phase, पूर्णांक reg)
अणु
	पूर्णांक ret;
	स्थिर काष्ठा pmbus_driver_info *info = pmbus_get_driver_info(client);
	स्थिर काष्ठा max34440_data *data = to_max34440_data(info);

	चयन (reg) अणु
	हाल PMBUS_IOUT_OC_FAULT_LIMIT:
		ret = pmbus_पढ़ो_word_data(client, page, phase,
					   MAX34440_IOUT_OC_FAULT_LIMIT);
		अवरोध;
	हाल PMBUS_IOUT_OC_WARN_LIMIT:
		ret = pmbus_पढ़ो_word_data(client, page, phase,
					   MAX34440_IOUT_OC_WARN_LIMIT);
		अवरोध;
	हाल PMBUS_VIRT_READ_VOUT_MIN:
		ret = pmbus_पढ़ो_word_data(client, page, phase,
					   MAX34440_MFR_VOUT_MIN);
		अवरोध;
	हाल PMBUS_VIRT_READ_VOUT_MAX:
		ret = pmbus_पढ़ो_word_data(client, page, phase,
					   MAX34440_MFR_VOUT_PEAK);
		अवरोध;
	हाल PMBUS_VIRT_READ_IOUT_AVG:
		अगर (data->id != max34446 && data->id != max34451)
			वापस -ENXIO;
		ret = pmbus_पढ़ो_word_data(client, page, phase,
					   MAX34446_MFR_IOUT_AVG);
		अवरोध;
	हाल PMBUS_VIRT_READ_IOUT_MAX:
		ret = pmbus_पढ़ो_word_data(client, page, phase,
					   MAX34440_MFR_IOUT_PEAK);
		अवरोध;
	हाल PMBUS_VIRT_READ_POUT_AVG:
		अगर (data->id != max34446)
			वापस -ENXIO;
		ret = pmbus_पढ़ो_word_data(client, page, phase,
					   MAX34446_MFR_POUT_AVG);
		अवरोध;
	हाल PMBUS_VIRT_READ_POUT_MAX:
		अगर (data->id != max34446)
			वापस -ENXIO;
		ret = pmbus_पढ़ो_word_data(client, page, phase,
					   MAX34446_MFR_POUT_PEAK);
		अवरोध;
	हाल PMBUS_VIRT_READ_TEMP_AVG:
		अगर (data->id != max34446 && data->id != max34460 &&
		    data->id != max34461)
			वापस -ENXIO;
		ret = pmbus_पढ़ो_word_data(client, page, phase,
					   MAX34446_MFR_TEMPERATURE_AVG);
		अवरोध;
	हाल PMBUS_VIRT_READ_TEMP_MAX:
		ret = pmbus_पढ़ो_word_data(client, page, phase,
					   MAX34440_MFR_TEMPERATURE_PEAK);
		अवरोध;
	हाल PMBUS_VIRT_RESET_POUT_HISTORY:
		अगर (data->id != max34446)
			वापस -ENXIO;
		ret = 0;
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

अटल पूर्णांक max34440_ग_लिखो_word_data(काष्ठा i2c_client *client, पूर्णांक page,
				    पूर्णांक reg, u16 word)
अणु
	स्थिर काष्ठा pmbus_driver_info *info = pmbus_get_driver_info(client);
	स्थिर काष्ठा max34440_data *data = to_max34440_data(info);
	पूर्णांक ret;

	चयन (reg) अणु
	हाल PMBUS_IOUT_OC_FAULT_LIMIT:
		ret = pmbus_ग_लिखो_word_data(client, page, MAX34440_IOUT_OC_FAULT_LIMIT,
					    word);
		अवरोध;
	हाल PMBUS_IOUT_OC_WARN_LIMIT:
		ret = pmbus_ग_लिखो_word_data(client, page, MAX34440_IOUT_OC_WARN_LIMIT,
					    word);
		अवरोध;
	हाल PMBUS_VIRT_RESET_POUT_HISTORY:
		ret = pmbus_ग_लिखो_word_data(client, page,
					    MAX34446_MFR_POUT_PEAK, 0);
		अगर (ret)
			अवरोध;
		ret = pmbus_ग_लिखो_word_data(client, page,
					    MAX34446_MFR_POUT_AVG, 0);
		अवरोध;
	हाल PMBUS_VIRT_RESET_VOUT_HISTORY:
		ret = pmbus_ग_लिखो_word_data(client, page,
					    MAX34440_MFR_VOUT_MIN, 0x7fff);
		अगर (ret)
			अवरोध;
		ret = pmbus_ग_लिखो_word_data(client, page,
					    MAX34440_MFR_VOUT_PEAK, 0);
		अवरोध;
	हाल PMBUS_VIRT_RESET_IOUT_HISTORY:
		ret = pmbus_ग_लिखो_word_data(client, page,
					    MAX34440_MFR_IOUT_PEAK, 0);
		अगर (!ret && (data->id == max34446 || data->id == max34451))
			ret = pmbus_ग_लिखो_word_data(client, page,
					MAX34446_MFR_IOUT_AVG, 0);

		अवरोध;
	हाल PMBUS_VIRT_RESET_TEMP_HISTORY:
		ret = pmbus_ग_लिखो_word_data(client, page,
					    MAX34440_MFR_TEMPERATURE_PEAK,
					    0x8000);
		अगर (!ret && data->id == max34446)
			ret = pmbus_ग_लिखो_word_data(client, page,
					MAX34446_MFR_TEMPERATURE_AVG, 0);
		अवरोध;
	शेष:
		ret = -ENODATA;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक max34440_पढ़ो_byte_data(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक reg)
अणु
	पूर्णांक ret = 0;
	पूर्णांक mfg_status;

	अगर (page >= 0) अणु
		ret = pmbus_set_page(client, page, 0xff);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	चयन (reg) अणु
	हाल PMBUS_STATUS_IOUT:
		mfg_status = pmbus_पढ़ो_word_data(client, 0, 0xff,
						  PMBUS_STATUS_MFR_SPECIFIC);
		अगर (mfg_status < 0)
			वापस mfg_status;
		अगर (mfg_status & MAX34440_STATUS_OC_WARN)
			ret |= PB_IOUT_OC_WARNING;
		अगर (mfg_status & MAX34440_STATUS_OC_FAULT)
			ret |= PB_IOUT_OC_FAULT;
		अवरोध;
	हाल PMBUS_STATUS_TEMPERATURE:
		mfg_status = pmbus_पढ़ो_word_data(client, 0, 0xff,
						  PMBUS_STATUS_MFR_SPECIFIC);
		अगर (mfg_status < 0)
			वापस mfg_status;
		अगर (mfg_status & MAX34440_STATUS_OT_WARN)
			ret |= PB_TEMP_OT_WARNING;
		अगर (mfg_status & MAX34440_STATUS_OT_FAULT)
			ret |= PB_TEMP_OT_FAULT;
		अवरोध;
	शेष:
		ret = -ENODATA;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक max34451_set_supported_funcs(काष्ठा i2c_client *client,
					 काष्ठा max34440_data *data)
अणु
	/*
	 * Each of the channel 0-15 can be configured to monitor the following
	 * functions based on MFR_CHANNEL_CONFIG[5:0]
	 * 0x10: Sequencing + voltage monitoring (only valid क्रम PAGES 0ै 11)
	 * 0x20: Voltage monitoring (no sequencing)
	 * 0x21: Voltage पढ़ो only
	 * 0x22: Current monitoring
	 * 0x23: Current पढ़ो only
	 * 0x30: General-purpose input active low
	 * 0x34: General-purpose input active high
	 * 0x00:  Disabled
	 */

	पूर्णांक page, rv;

	क्रम (page = 0; page < 16; page++) अणु
		rv = i2c_smbus_ग_लिखो_byte_data(client, PMBUS_PAGE, page);
		अगर (rv < 0)
			वापस rv;

		rv = i2c_smbus_पढ़ो_word_data(client,
					      MAX34451_MFR_CHANNEL_CONFIG);
		अगर (rv < 0)
			वापस rv;

		चयन (rv & MAX34451_MFR_CHANNEL_CONFIG_SEL_MASK) अणु
		हाल 0x10:
		हाल 0x20:
			data->info.func[page] = PMBUS_HAVE_VOUT |
				PMBUS_HAVE_STATUS_VOUT;
			अवरोध;
		हाल 0x21:
			data->info.func[page] = PMBUS_HAVE_VOUT;
			अवरोध;
		हाल 0x22:
			data->info.func[page] = PMBUS_HAVE_IOUT |
				PMBUS_HAVE_STATUS_IOUT;
			अवरोध;
		हाल 0x23:
			data->info.func[page] = PMBUS_HAVE_IOUT;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा pmbus_driver_info max34440_info[] = अणु
	[max34440] = अणु
		.pages = 14,
		.क्रमmat[PSC_VOLTAGE_IN] = direct,
		.क्रमmat[PSC_VOLTAGE_OUT] = direct,
		.क्रमmat[PSC_TEMPERATURE] = direct,
		.क्रमmat[PSC_CURRENT_OUT] = direct,
		.m[PSC_VOLTAGE_IN] = 1,
		.b[PSC_VOLTAGE_IN] = 0,
		.R[PSC_VOLTAGE_IN] = 3,	    /* R = 0 in datasheet reflects mV */
		.m[PSC_VOLTAGE_OUT] = 1,
		.b[PSC_VOLTAGE_OUT] = 0,
		.R[PSC_VOLTAGE_OUT] = 3,    /* R = 0 in datasheet reflects mV */
		.m[PSC_CURRENT_OUT] = 1,
		.b[PSC_CURRENT_OUT] = 0,
		.R[PSC_CURRENT_OUT] = 3,    /* R = 0 in datasheet reflects mA */
		.m[PSC_TEMPERATURE] = 1,
		.b[PSC_TEMPERATURE] = 0,
		.R[PSC_TEMPERATURE] = 2,
		.func[0] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT,
		.func[1] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT,
		.func[2] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT,
		.func[3] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT,
		.func[4] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT,
		.func[5] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT,
		.func[6] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[7] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[8] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[9] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[10] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[11] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[12] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[13] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.पढ़ो_byte_data = max34440_पढ़ो_byte_data,
		.पढ़ो_word_data = max34440_पढ़ो_word_data,
		.ग_लिखो_word_data = max34440_ग_लिखो_word_data,
	पूर्ण,
	[max34441] = अणु
		.pages = 12,
		.क्रमmat[PSC_VOLTAGE_IN] = direct,
		.क्रमmat[PSC_VOLTAGE_OUT] = direct,
		.क्रमmat[PSC_TEMPERATURE] = direct,
		.क्रमmat[PSC_CURRENT_OUT] = direct,
		.क्रमmat[PSC_FAN] = direct,
		.m[PSC_VOLTAGE_IN] = 1,
		.b[PSC_VOLTAGE_IN] = 0,
		.R[PSC_VOLTAGE_IN] = 3,
		.m[PSC_VOLTAGE_OUT] = 1,
		.b[PSC_VOLTAGE_OUT] = 0,
		.R[PSC_VOLTAGE_OUT] = 3,
		.m[PSC_CURRENT_OUT] = 1,
		.b[PSC_CURRENT_OUT] = 0,
		.R[PSC_CURRENT_OUT] = 3,
		.m[PSC_TEMPERATURE] = 1,
		.b[PSC_TEMPERATURE] = 0,
		.R[PSC_TEMPERATURE] = 2,
		.m[PSC_FAN] = 1,
		.b[PSC_FAN] = 0,
		.R[PSC_FAN] = 0,
		.func[0] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT,
		.func[1] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT,
		.func[2] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT,
		.func[3] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT,
		.func[4] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT,
		.func[5] = PMBUS_HAVE_FAN12 | PMBUS_HAVE_STATUS_FAN12,
		.func[6] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[7] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[8] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[9] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[10] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[11] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.पढ़ो_byte_data = max34440_पढ़ो_byte_data,
		.पढ़ो_word_data = max34440_पढ़ो_word_data,
		.ग_लिखो_word_data = max34440_ग_लिखो_word_data,
	पूर्ण,
	[max34446] = अणु
		.pages = 7,
		.क्रमmat[PSC_VOLTAGE_IN] = direct,
		.क्रमmat[PSC_VOLTAGE_OUT] = direct,
		.क्रमmat[PSC_TEMPERATURE] = direct,
		.क्रमmat[PSC_CURRENT_OUT] = direct,
		.क्रमmat[PSC_POWER] = direct,
		.m[PSC_VOLTAGE_IN] = 1,
		.b[PSC_VOLTAGE_IN] = 0,
		.R[PSC_VOLTAGE_IN] = 3,
		.m[PSC_VOLTAGE_OUT] = 1,
		.b[PSC_VOLTAGE_OUT] = 0,
		.R[PSC_VOLTAGE_OUT] = 3,
		.m[PSC_CURRENT_OUT] = 1,
		.b[PSC_CURRENT_OUT] = 0,
		.R[PSC_CURRENT_OUT] = 3,
		.m[PSC_POWER] = 1,
		.b[PSC_POWER] = 0,
		.R[PSC_POWER] = 3,
		.m[PSC_TEMPERATURE] = 1,
		.b[PSC_TEMPERATURE] = 0,
		.R[PSC_TEMPERATURE] = 2,
		.func[0] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT | PMBUS_HAVE_POUT,
		.func[1] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT,
		.func[2] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT | PMBUS_HAVE_POUT,
		.func[3] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT,
		.func[4] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[5] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[6] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.पढ़ो_byte_data = max34440_पढ़ो_byte_data,
		.पढ़ो_word_data = max34440_पढ़ो_word_data,
		.ग_लिखो_word_data = max34440_ग_लिखो_word_data,
	पूर्ण,
	[max34451] = अणु
		.pages = 21,
		.क्रमmat[PSC_VOLTAGE_OUT] = direct,
		.क्रमmat[PSC_TEMPERATURE] = direct,
		.क्रमmat[PSC_CURRENT_OUT] = direct,
		.m[PSC_VOLTAGE_OUT] = 1,
		.b[PSC_VOLTAGE_OUT] = 0,
		.R[PSC_VOLTAGE_OUT] = 3,
		.m[PSC_CURRENT_OUT] = 1,
		.b[PSC_CURRENT_OUT] = 0,
		.R[PSC_CURRENT_OUT] = 2,
		.m[PSC_TEMPERATURE] = 1,
		.b[PSC_TEMPERATURE] = 0,
		.R[PSC_TEMPERATURE] = 2,
		/* func 0-15 is set dynamically beक्रमe probing */
		.func[16] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[17] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[18] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[19] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[20] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.पढ़ो_word_data = max34440_पढ़ो_word_data,
		.ग_लिखो_word_data = max34440_ग_लिखो_word_data,
	पूर्ण,
	[max34460] = अणु
		.pages = 18,
		.क्रमmat[PSC_VOLTAGE_OUT] = direct,
		.क्रमmat[PSC_TEMPERATURE] = direct,
		.m[PSC_VOLTAGE_OUT] = 1,
		.b[PSC_VOLTAGE_OUT] = 0,
		.R[PSC_VOLTAGE_OUT] = 3,
		.m[PSC_TEMPERATURE] = 1,
		.b[PSC_TEMPERATURE] = 0,
		.R[PSC_TEMPERATURE] = 2,
		.func[0] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[1] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[2] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[3] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[4] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[5] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[6] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[7] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[8] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[9] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[10] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[11] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[13] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[14] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[15] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[16] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[17] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.पढ़ो_word_data = max34440_पढ़ो_word_data,
		.ग_लिखो_word_data = max34440_ग_लिखो_word_data,
	पूर्ण,
	[max34461] = अणु
		.pages = 23,
		.क्रमmat[PSC_VOLTAGE_OUT] = direct,
		.क्रमmat[PSC_TEMPERATURE] = direct,
		.m[PSC_VOLTAGE_OUT] = 1,
		.b[PSC_VOLTAGE_OUT] = 0,
		.R[PSC_VOLTAGE_OUT] = 3,
		.m[PSC_TEMPERATURE] = 1,
		.b[PSC_TEMPERATURE] = 0,
		.R[PSC_TEMPERATURE] = 2,
		.func[0] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[1] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[2] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[3] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[4] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[5] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[6] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[7] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[8] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[9] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[10] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[11] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[12] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[13] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[14] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		.func[15] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT,
		/* page 16 is reserved */
		.func[17] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[18] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[19] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[20] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.func[21] = PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP,
		.पढ़ो_word_data = max34440_पढ़ो_word_data,
		.ग_लिखो_word_data = max34440_ग_लिखो_word_data,
	पूर्ण,
पूर्ण;

अटल पूर्णांक max34440_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा max34440_data *data;
	पूर्णांक rv;

	data = devm_kzalloc(&client->dev, माप(काष्ठा max34440_data),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;
	data->id = i2c_match_id(max34440_id, client)->driver_data;
	data->info = max34440_info[data->id];

	अगर (data->id == max34451) अणु
		rv = max34451_set_supported_funcs(client, data);
		अगर (rv)
			वापस rv;
	पूर्ण

	वापस pmbus_करो_probe(client, &data->info);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max34440_id[] = अणु
	अणु"max34440", max34440पूर्ण,
	अणु"max34441", max34441पूर्ण,
	अणु"max34446", max34446पूर्ण,
	अणु"max34451", max34451पूर्ण,
	अणु"max34460", max34460पूर्ण,
	अणु"max34461", max34461पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max34440_id);

/* This is the driver that will be inserted */
अटल काष्ठा i2c_driver max34440_driver = अणु
	.driver = अणु
		   .name = "max34440",
		   पूर्ण,
	.probe_new = max34440_probe,
	.id_table = max34440_id,
पूर्ण;

module_i2c_driver(max34440_driver);

MODULE_AUTHOR("Guenter Roeck");
MODULE_DESCRIPTION("PMBus driver for Maxim MAX34440/MAX34441");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(PMBUS);
