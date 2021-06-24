<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hardware monitoring driver क्रम LM25056 / LM25066 / LM5064 / LM5066
 *
 * Copyright (c) 2011 Ericsson AB.
 * Copyright (c) 2013 Guenter Roeck
 */

#समावेश <linux/bitops.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/log2.h>
#समावेश "pmbus.h"

क्रमागत chips अणु lm25056, lm25066, lm5064, lm5066, lm5066i पूर्ण;

#घोषणा LM25066_READ_VAUX		0xd0
#घोषणा LM25066_MFR_READ_IIN		0xd1
#घोषणा LM25066_MFR_READ_PIN		0xd2
#घोषणा LM25066_MFR_IIN_OC_WARN_LIMIT	0xd3
#घोषणा LM25066_MFR_PIN_OP_WARN_LIMIT	0xd4
#घोषणा LM25066_READ_PIN_PEAK		0xd5
#घोषणा LM25066_CLEAR_PIN_PEAK		0xd6
#घोषणा LM25066_DEVICE_SETUP		0xd9
#घोषणा LM25066_READ_AVG_VIN		0xdc
#घोषणा LM25066_SAMPLES_FOR_AVG		0xdb
#घोषणा LM25066_READ_AVG_VOUT		0xdd
#घोषणा LM25066_READ_AVG_IIN		0xde
#घोषणा LM25066_READ_AVG_PIN		0xdf

#घोषणा LM25066_DEV_SETUP_CL		BIT(4)	/* Current limit */

#घोषणा LM25066_SAMPLES_FOR_AVG_MAX	4096

/* LM25056 only */

#घोषणा LM25056_VAUX_OV_WARN_LIMIT	0xe3
#घोषणा LM25056_VAUX_UV_WARN_LIMIT	0xe4

#घोषणा LM25056_MFR_STS_VAUX_OV_WARN	BIT(1)
#घोषणा LM25056_MFR_STS_VAUX_UV_WARN	BIT(0)

काष्ठा __coeff अणु
	लघु m, b, R;
पूर्ण;

#घोषणा PSC_CURRENT_IN_L	(PSC_NUM_CLASSES)
#घोषणा PSC_POWER_L		(PSC_NUM_CLASSES + 1)

अटल काष्ठा __coeff lm25066_coeff[6][PSC_NUM_CLASSES + 2] = अणु
	[lm25056] = अणु
		[PSC_VOLTAGE_IN] = अणु
			.m = 16296,
			.R = -2,
		पूर्ण,
		[PSC_CURRENT_IN] = अणु
			.m = 13797,
			.R = -2,
		पूर्ण,
		[PSC_CURRENT_IN_L] = अणु
			.m = 6726,
			.R = -2,
		पूर्ण,
		[PSC_POWER] = अणु
			.m = 5501,
			.R = -3,
		पूर्ण,
		[PSC_POWER_L] = अणु
			.m = 26882,
			.R = -4,
		पूर्ण,
		[PSC_TEMPERATURE] = अणु
			.m = 1580,
			.b = -14500,
			.R = -2,
		पूर्ण,
	पूर्ण,
	[lm25066] = अणु
		[PSC_VOLTAGE_IN] = अणु
			.m = 22070,
			.R = -2,
		पूर्ण,
		[PSC_VOLTAGE_OUT] = अणु
			.m = 22070,
			.R = -2,
		पूर्ण,
		[PSC_CURRENT_IN] = अणु
			.m = 13661,
			.R = -2,
		पूर्ण,
		[PSC_CURRENT_IN_L] = अणु
			.m = 6852,
			.R = -2,
		पूर्ण,
		[PSC_POWER] = अणु
			.m = 736,
			.R = -2,
		पूर्ण,
		[PSC_POWER_L] = अणु
			.m = 369,
			.R = -2,
		पूर्ण,
		[PSC_TEMPERATURE] = अणु
			.m = 16,
		पूर्ण,
	पूर्ण,
	[lm5064] = अणु
		[PSC_VOLTAGE_IN] = अणु
			.m = 4611,
			.R = -2,
		पूर्ण,
		[PSC_VOLTAGE_OUT] = अणु
			.m = 4621,
			.R = -2,
		पूर्ण,
		[PSC_CURRENT_IN] = अणु
			.m = 10742,
			.R = -2,
		पूर्ण,
		[PSC_CURRENT_IN_L] = अणु
			.m = 5456,
			.R = -2,
		पूर्ण,
		[PSC_POWER] = अणु
			.m = 1204,
			.R = -3,
		पूर्ण,
		[PSC_POWER_L] = अणु
			.m = 612,
			.R = -3,
		पूर्ण,
		[PSC_TEMPERATURE] = अणु
			.m = 16,
		पूर्ण,
	पूर्ण,
	[lm5066] = अणु
		[PSC_VOLTAGE_IN] = अणु
			.m = 4587,
			.R = -2,
		पूर्ण,
		[PSC_VOLTAGE_OUT] = अणु
			.m = 4587,
			.R = -2,
		पूर्ण,
		[PSC_CURRENT_IN] = अणु
			.m = 10753,
			.R = -2,
		पूर्ण,
		[PSC_CURRENT_IN_L] = अणु
			.m = 5405,
			.R = -2,
		पूर्ण,
		[PSC_POWER] = अणु
			.m = 1204,
			.R = -3,
		पूर्ण,
		[PSC_POWER_L] = अणु
			.m = 605,
			.R = -3,
		पूर्ण,
		[PSC_TEMPERATURE] = अणु
			.m = 16,
		पूर्ण,
	पूर्ण,
	[lm5066i] = अणु
		[PSC_VOLTAGE_IN] = अणु
			.m = 4617,
			.b = -140,
			.R = -2,
		पूर्ण,
		[PSC_VOLTAGE_OUT] = अणु
			.m = 4602,
			.b = 500,
			.R = -2,
		पूर्ण,
		[PSC_CURRENT_IN] = अणु
			.m = 15076,
			.b = -504,
			.R = -2,
		पूर्ण,
		[PSC_CURRENT_IN_L] = अणु
			.m = 7645,
			.b = 100,
			.R = -2,
		पूर्ण,
		[PSC_POWER] = अणु
			.m = 1701,
			.b = -4000,
			.R = -3,
		पूर्ण,
		[PSC_POWER_L] = अणु
			.m = 861,
			.b = -965,
			.R = -3,
		पूर्ण,
		[PSC_TEMPERATURE] = अणु
			.m = 16,
		पूर्ण,
	पूर्ण,
पूर्ण;

काष्ठा lm25066_data अणु
	पूर्णांक id;
	u16 rlimit;			/* Maximum रेजिस्टर value */
	काष्ठा pmbus_driver_info info;
पूर्ण;

#घोषणा to_lm25066_data(x)  container_of(x, काष्ठा lm25066_data, info)

अटल स्थिर काष्ठा i2c_device_id lm25066_id[];

अटल पूर्णांक lm25066_पढ़ो_word_data(काष्ठा i2c_client *client, पूर्णांक page,
				  पूर्णांक phase, पूर्णांक reg)
अणु
	स्थिर काष्ठा pmbus_driver_info *info = pmbus_get_driver_info(client);
	स्थिर काष्ठा lm25066_data *data = to_lm25066_data(info);
	पूर्णांक ret;

	चयन (reg) अणु
	हाल PMBUS_VIRT_READ_VMON:
		ret = pmbus_पढ़ो_word_data(client, 0, 0xff, LM25066_READ_VAUX);
		अगर (ret < 0)
			अवरोध;
		/* Adjust वापसed value to match VIN coefficients */
		चयन (data->id) अणु
		हाल lm25056:
			/* VIN: 6.14 mV VAUX: 293 uV LSB */
			ret = DIV_ROUND_CLOSEST(ret * 293, 6140);
			अवरोध;
		हाल lm25066:
			/* VIN: 4.54 mV VAUX: 283.2 uV LSB */
			ret = DIV_ROUND_CLOSEST(ret * 2832, 45400);
			अवरोध;
		हाल lm5064:
			/* VIN: 4.53 mV VAUX: 700 uV LSB */
			ret = DIV_ROUND_CLOSEST(ret * 70, 453);
			अवरोध;
		हाल lm5066:
		हाल lm5066i:
			/* VIN: 2.18 mV VAUX: 725 uV LSB */
			ret = DIV_ROUND_CLOSEST(ret * 725, 2180);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल PMBUS_READ_IIN:
		ret = pmbus_पढ़ो_word_data(client, 0, 0xff,
					   LM25066_MFR_READ_IIN);
		अवरोध;
	हाल PMBUS_READ_PIN:
		ret = pmbus_पढ़ो_word_data(client, 0, 0xff,
					   LM25066_MFR_READ_PIN);
		अवरोध;
	हाल PMBUS_IIN_OC_WARN_LIMIT:
		ret = pmbus_पढ़ो_word_data(client, 0, 0xff,
					   LM25066_MFR_IIN_OC_WARN_LIMIT);
		अवरोध;
	हाल PMBUS_PIN_OP_WARN_LIMIT:
		ret = pmbus_पढ़ो_word_data(client, 0, 0xff,
					   LM25066_MFR_PIN_OP_WARN_LIMIT);
		अवरोध;
	हाल PMBUS_VIRT_READ_VIN_AVG:
		ret = pmbus_पढ़ो_word_data(client, 0, 0xff,
					   LM25066_READ_AVG_VIN);
		अवरोध;
	हाल PMBUS_VIRT_READ_VOUT_AVG:
		ret = pmbus_पढ़ो_word_data(client, 0, 0xff,
					   LM25066_READ_AVG_VOUT);
		अवरोध;
	हाल PMBUS_VIRT_READ_IIN_AVG:
		ret = pmbus_पढ़ो_word_data(client, 0, 0xff,
					   LM25066_READ_AVG_IIN);
		अवरोध;
	हाल PMBUS_VIRT_READ_PIN_AVG:
		ret = pmbus_पढ़ो_word_data(client, 0, 0xff,
					   LM25066_READ_AVG_PIN);
		अवरोध;
	हाल PMBUS_VIRT_READ_PIN_MAX:
		ret = pmbus_पढ़ो_word_data(client, 0, 0xff,
					   LM25066_READ_PIN_PEAK);
		अवरोध;
	हाल PMBUS_VIRT_RESET_PIN_HISTORY:
		ret = 0;
		अवरोध;
	हाल PMBUS_VIRT_SAMPLES:
		ret = pmbus_पढ़ो_byte_data(client, 0, LM25066_SAMPLES_FOR_AVG);
		अगर (ret < 0)
			अवरोध;
		ret = 1 << ret;
		अवरोध;
	शेष:
		ret = -ENODATA;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक lm25056_पढ़ो_word_data(काष्ठा i2c_client *client, पूर्णांक page,
				  पूर्णांक phase, पूर्णांक reg)
अणु
	पूर्णांक ret;

	चयन (reg) अणु
	हाल PMBUS_VIRT_VMON_UV_WARN_LIMIT:
		ret = pmbus_पढ़ो_word_data(client, 0, 0xff,
					   LM25056_VAUX_UV_WARN_LIMIT);
		अगर (ret < 0)
			अवरोध;
		/* Adjust वापसed value to match VIN coefficients */
		ret = DIV_ROUND_CLOSEST(ret * 293, 6140);
		अवरोध;
	हाल PMBUS_VIRT_VMON_OV_WARN_LIMIT:
		ret = pmbus_पढ़ो_word_data(client, 0, 0xff,
					   LM25056_VAUX_OV_WARN_LIMIT);
		अगर (ret < 0)
			अवरोध;
		/* Adjust वापसed value to match VIN coefficients */
		ret = DIV_ROUND_CLOSEST(ret * 293, 6140);
		अवरोध;
	शेष:
		ret = lm25066_पढ़ो_word_data(client, page, phase, reg);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक lm25056_पढ़ो_byte_data(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक reg)
अणु
	पूर्णांक ret, s;

	चयन (reg) अणु
	हाल PMBUS_VIRT_STATUS_VMON:
		ret = pmbus_पढ़ो_byte_data(client, 0,
					   PMBUS_STATUS_MFR_SPECIFIC);
		अगर (ret < 0)
			अवरोध;
		s = 0;
		अगर (ret & LM25056_MFR_STS_VAUX_UV_WARN)
			s |= PB_VOLTAGE_UV_WARNING;
		अगर (ret & LM25056_MFR_STS_VAUX_OV_WARN)
			s |= PB_VOLTAGE_OV_WARNING;
		ret = s;
		अवरोध;
	शेष:
		ret = -ENODATA;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक lm25066_ग_लिखो_word_data(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक reg,
				   u16 word)
अणु
	स्थिर काष्ठा pmbus_driver_info *info = pmbus_get_driver_info(client);
	स्थिर काष्ठा lm25066_data *data = to_lm25066_data(info);
	पूर्णांक ret;

	चयन (reg) अणु
	हाल PMBUS_POUT_OP_FAULT_LIMIT:
	हाल PMBUS_POUT_OP_WARN_LIMIT:
	हाल PMBUS_VOUT_UV_WARN_LIMIT:
	हाल PMBUS_OT_FAULT_LIMIT:
	हाल PMBUS_OT_WARN_LIMIT:
	हाल PMBUS_IIN_OC_FAULT_LIMIT:
	हाल PMBUS_VIN_UV_WARN_LIMIT:
	हाल PMBUS_VIN_UV_FAULT_LIMIT:
	हाल PMBUS_VIN_OV_FAULT_LIMIT:
	हाल PMBUS_VIN_OV_WARN_LIMIT:
		word = ((s16)word < 0) ? 0 : clamp_val(word, 0, data->rlimit);
		ret = pmbus_ग_लिखो_word_data(client, 0, reg, word);
		अवरोध;
	हाल PMBUS_IIN_OC_WARN_LIMIT:
		word = ((s16)word < 0) ? 0 : clamp_val(word, 0, data->rlimit);
		ret = pmbus_ग_लिखो_word_data(client, 0,
					    LM25066_MFR_IIN_OC_WARN_LIMIT,
					    word);
		अवरोध;
	हाल PMBUS_PIN_OP_WARN_LIMIT:
		word = ((s16)word < 0) ? 0 : clamp_val(word, 0, data->rlimit);
		ret = pmbus_ग_लिखो_word_data(client, 0,
					    LM25066_MFR_PIN_OP_WARN_LIMIT,
					    word);
		अवरोध;
	हाल PMBUS_VIRT_VMON_UV_WARN_LIMIT:
		/* Adjust from VIN coefficients (क्रम LM25056) */
		word = DIV_ROUND_CLOSEST((पूर्णांक)word * 6140, 293);
		word = ((s16)word < 0) ? 0 : clamp_val(word, 0, data->rlimit);
		ret = pmbus_ग_लिखो_word_data(client, 0,
					    LM25056_VAUX_UV_WARN_LIMIT, word);
		अवरोध;
	हाल PMBUS_VIRT_VMON_OV_WARN_LIMIT:
		/* Adjust from VIN coefficients (क्रम LM25056) */
		word = DIV_ROUND_CLOSEST((पूर्णांक)word * 6140, 293);
		word = ((s16)word < 0) ? 0 : clamp_val(word, 0, data->rlimit);
		ret = pmbus_ग_लिखो_word_data(client, 0,
					    LM25056_VAUX_OV_WARN_LIMIT, word);
		अवरोध;
	हाल PMBUS_VIRT_RESET_PIN_HISTORY:
		ret = pmbus_ग_लिखो_byte(client, 0, LM25066_CLEAR_PIN_PEAK);
		अवरोध;
	हाल PMBUS_VIRT_SAMPLES:
		word = clamp_val(word, 1, LM25066_SAMPLES_FOR_AVG_MAX);
		ret = pmbus_ग_लिखो_byte_data(client, 0, LM25066_SAMPLES_FOR_AVG,
					    ilog2(word));
		अवरोध;
	शेष:
		ret = -ENODATA;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक lm25066_probe(काष्ठा i2c_client *client)
अणु
	पूर्णांक config;
	काष्ठा lm25066_data *data;
	काष्ठा pmbus_driver_info *info;
	काष्ठा __coeff *coeff;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_READ_BYTE_DATA))
		वापस -ENODEV;

	data = devm_kzalloc(&client->dev, माप(काष्ठा lm25066_data),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	config = i2c_smbus_पढ़ो_byte_data(client, LM25066_DEVICE_SETUP);
	अगर (config < 0)
		वापस config;

	data->id = i2c_match_id(lm25066_id, client)->driver_data;
	info = &data->info;

	info->pages = 1;
	info->क्रमmat[PSC_VOLTAGE_IN] = direct;
	info->क्रमmat[PSC_VOLTAGE_OUT] = direct;
	info->क्रमmat[PSC_CURRENT_IN] = direct;
	info->क्रमmat[PSC_TEMPERATURE] = direct;
	info->क्रमmat[PSC_POWER] = direct;

	info->func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_VMON
	  | PMBUS_HAVE_PIN | PMBUS_HAVE_IIN | PMBUS_HAVE_STATUS_INPUT
	  | PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP | PMBUS_HAVE_SAMPLES;

	अगर (data->id == lm25056) अणु
		info->func[0] |= PMBUS_HAVE_STATUS_VMON;
		info->पढ़ो_word_data = lm25056_पढ़ो_word_data;
		info->पढ़ो_byte_data = lm25056_पढ़ो_byte_data;
		data->rlimit = 0x0fff;
	पूर्ण अन्यथा अणु
		info->func[0] |= PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT;
		info->पढ़ो_word_data = lm25066_पढ़ो_word_data;
		data->rlimit = 0x0fff;
	पूर्ण
	info->ग_लिखो_word_data = lm25066_ग_लिखो_word_data;

	coeff = &lm25066_coeff[data->id][0];
	info->m[PSC_TEMPERATURE] = coeff[PSC_TEMPERATURE].m;
	info->b[PSC_TEMPERATURE] = coeff[PSC_TEMPERATURE].b;
	info->R[PSC_TEMPERATURE] = coeff[PSC_TEMPERATURE].R;
	info->m[PSC_VOLTAGE_IN] = coeff[PSC_VOLTAGE_IN].m;
	info->b[PSC_VOLTAGE_IN] = coeff[PSC_VOLTAGE_IN].b;
	info->R[PSC_VOLTAGE_IN] = coeff[PSC_VOLTAGE_IN].R;
	info->m[PSC_VOLTAGE_OUT] = coeff[PSC_VOLTAGE_OUT].m;
	info->b[PSC_VOLTAGE_OUT] = coeff[PSC_VOLTAGE_OUT].b;
	info->R[PSC_VOLTAGE_OUT] = coeff[PSC_VOLTAGE_OUT].R;
	info->R[PSC_CURRENT_IN] = coeff[PSC_CURRENT_IN].R;
	info->R[PSC_POWER] = coeff[PSC_POWER].R;
	अगर (config & LM25066_DEV_SETUP_CL) अणु
		info->m[PSC_CURRENT_IN] = coeff[PSC_CURRENT_IN_L].m;
		info->b[PSC_CURRENT_IN] = coeff[PSC_CURRENT_IN_L].b;
		info->m[PSC_POWER] = coeff[PSC_POWER_L].m;
		info->b[PSC_POWER] = coeff[PSC_POWER_L].b;
	पूर्ण अन्यथा अणु
		info->m[PSC_CURRENT_IN] = coeff[PSC_CURRENT_IN].m;
		info->b[PSC_CURRENT_IN] = coeff[PSC_CURRENT_IN].b;
		info->m[PSC_POWER] = coeff[PSC_POWER].m;
		info->b[PSC_POWER] = coeff[PSC_POWER].b;
	पूर्ण

	वापस pmbus_करो_probe(client, info);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lm25066_id[] = अणु
	अणु"lm25056", lm25056पूर्ण,
	अणु"lm25066", lm25066पूर्ण,
	अणु"lm5064", lm5064पूर्ण,
	अणु"lm5066", lm5066पूर्ण,
	अणु"lm5066i", lm5066iपूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, lm25066_id);

/* This is the driver that will be inserted */
अटल काष्ठा i2c_driver lm25066_driver = अणु
	.driver = अणु
		   .name = "lm25066",
		   पूर्ण,
	.probe_new = lm25066_probe,
	.id_table = lm25066_id,
पूर्ण;

module_i2c_driver(lm25066_driver);

MODULE_AUTHOR("Guenter Roeck");
MODULE_DESCRIPTION("PMBus driver for LM25066 and compatible chips");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(PMBUS);
