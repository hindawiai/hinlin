<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hardware monitoring driver क्रम Analog Devices ADM1275 Hot-Swap Controller
 * and Digital Power Monitor
 *
 * Copyright (c) 2011 Ericsson AB.
 * Copyright (c) 2018 Guenter Roeck
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/bitops.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/log2.h>
#समावेश "pmbus.h"

क्रमागत chips अणु adm1075, adm1272, adm1275, adm1276, adm1278, adm1293, adm1294 पूर्ण;

#घोषणा ADM1275_MFR_STATUS_IOUT_WARN2	BIT(0)
#घोषणा ADM1293_MFR_STATUS_VAUX_UV_WARN	BIT(5)
#घोषणा ADM1293_MFR_STATUS_VAUX_OV_WARN	BIT(6)

#घोषणा ADM1275_PEAK_IOUT		0xd0
#घोषणा ADM1275_PEAK_VIN		0xd1
#घोषणा ADM1275_PEAK_VOUT		0xd2
#घोषणा ADM1275_PMON_CONFIG		0xd4

#घोषणा ADM1275_VIN_VOUT_SELECT		BIT(6)
#घोषणा ADM1275_VRANGE			BIT(5)
#घोषणा ADM1075_IRANGE_50		BIT(4)
#घोषणा ADM1075_IRANGE_25		BIT(3)
#घोषणा ADM1075_IRANGE_MASK		(BIT(3) | BIT(4))

#घोषणा ADM1272_IRANGE			BIT(0)

#घोषणा ADM1278_TEMP1_EN		BIT(3)
#घोषणा ADM1278_VIN_EN			BIT(2)
#घोषणा ADM1278_VOUT_EN			BIT(1)

#घोषणा ADM1293_IRANGE_25		0
#घोषणा ADM1293_IRANGE_50		BIT(6)
#घोषणा ADM1293_IRANGE_100		BIT(7)
#घोषणा ADM1293_IRANGE_200		(BIT(6) | BIT(7))
#घोषणा ADM1293_IRANGE_MASK		(BIT(6) | BIT(7))

#घोषणा ADM1293_VIN_SEL_012		BIT(2)
#घोषणा ADM1293_VIN_SEL_074		BIT(3)
#घोषणा ADM1293_VIN_SEL_210		(BIT(2) | BIT(3))
#घोषणा ADM1293_VIN_SEL_MASK		(BIT(2) | BIT(3))

#घोषणा ADM1293_VAUX_EN			BIT(1)

#घोषणा ADM1278_PEAK_TEMP		0xd7
#घोषणा ADM1275_IOUT_WARN2_LIMIT	0xd7
#घोषणा ADM1275_DEVICE_CONFIG		0xd8

#घोषणा ADM1275_IOUT_WARN2_SELECT	BIT(4)

#घोषणा ADM1276_PEAK_PIN		0xda
#घोषणा ADM1075_READ_VAUX		0xdd
#घोषणा ADM1075_VAUX_OV_WARN_LIMIT	0xde
#घोषणा ADM1075_VAUX_UV_WARN_LIMIT	0xdf
#घोषणा ADM1293_IOUT_MIN		0xe3
#घोषणा ADM1293_PIN_MIN			0xe4
#घोषणा ADM1075_VAUX_STATUS		0xf6

#घोषणा ADM1075_VAUX_OV_WARN		BIT(7)
#घोषणा ADM1075_VAUX_UV_WARN		BIT(6)

#घोषणा ADM1275_VI_AVG_SHIFT		0
#घोषणा ADM1275_VI_AVG_MASK		GENMASK(ADM1275_VI_AVG_SHIFT + 2, \
						ADM1275_VI_AVG_SHIFT)
#घोषणा ADM1275_SAMPLES_AVG_MAX		128

#घोषणा ADM1278_PWR_AVG_SHIFT		11
#घोषणा ADM1278_PWR_AVG_MASK		GENMASK(ADM1278_PWR_AVG_SHIFT + 2, \
						ADM1278_PWR_AVG_SHIFT)
#घोषणा ADM1278_VI_AVG_SHIFT		8
#घोषणा ADM1278_VI_AVG_MASK		GENMASK(ADM1278_VI_AVG_SHIFT + 2, \
						ADM1278_VI_AVG_SHIFT)

काष्ठा adm1275_data अणु
	पूर्णांक id;
	bool have_oc_fault;
	bool have_uc_fault;
	bool have_vout;
	bool have_vaux_status;
	bool have_mfr_vaux_status;
	bool have_iout_min;
	bool have_pin_min;
	bool have_pin_max;
	bool have_temp_max;
	bool have_घातer_sampling;
	काष्ठा pmbus_driver_info info;
पूर्ण;

#घोषणा to_adm1275_data(x)  container_of(x, काष्ठा adm1275_data, info)

काष्ठा coefficients अणु
	s16 m;
	s16 b;
	s16 R;
पूर्ण;

अटल स्थिर काष्ठा coefficients adm1075_coefficients[] = अणु
	[0] = अणु 27169, 0, -1 पूर्ण,		/* voltage */
	[1] = अणु 806, 20475, -1 पूर्ण,	/* current, irange25 */
	[2] = अणु 404, 20475, -1 पूर्ण,	/* current, irange50 */
	[3] = अणु 8549, 0, -1 पूर्ण,		/* घातer, irange25 */
	[4] = अणु 4279, 0, -1 पूर्ण,		/* घातer, irange50 */
पूर्ण;

अटल स्थिर काष्ठा coefficients adm1272_coefficients[] = अणु
	[0] = अणु 6770, 0, -2 पूर्ण,		/* voltage, vrange 60V */
	[1] = अणु 4062, 0, -2 पूर्ण,		/* voltage, vrange 100V */
	[2] = अणु 1326, 20480, -1 पूर्ण,	/* current, vsense range 15mV */
	[3] = अणु 663, 20480, -1 पूर्ण,	/* current, vsense range 30mV */
	[4] = अणु 3512, 0, -2 पूर्ण,		/* घातer, vrange 60V, irange 15mV */
	[5] = अणु 21071, 0, -3 पूर्ण,		/* घातer, vrange 100V, irange 15mV */
	[6] = अणु 17561, 0, -3 पूर्ण,		/* घातer, vrange 60V, irange 30mV */
	[7] = अणु 10535, 0, -3 पूर्ण,		/* घातer, vrange 100V, irange 30mV */
	[8] = अणु 42, 31871, -1 पूर्ण,	/* temperature */

पूर्ण;

अटल स्थिर काष्ठा coefficients adm1275_coefficients[] = अणु
	[0] = अणु 19199, 0, -2 पूर्ण,		/* voltage, vrange set */
	[1] = अणु 6720, 0, -1 पूर्ण,		/* voltage, vrange not set */
	[2] = अणु 807, 20475, -1 पूर्ण,	/* current */
पूर्ण;

अटल स्थिर काष्ठा coefficients adm1276_coefficients[] = अणु
	[0] = अणु 19199, 0, -2 पूर्ण,		/* voltage, vrange set */
	[1] = अणु 6720, 0, -1 पूर्ण,		/* voltage, vrange not set */
	[2] = अणु 807, 20475, -1 पूर्ण,	/* current */
	[3] = अणु 6043, 0, -2 पूर्ण,		/* घातer, vrange set */
	[4] = अणु 2115, 0, -1 पूर्ण,		/* घातer, vrange not set */
पूर्ण;

अटल स्थिर काष्ठा coefficients adm1278_coefficients[] = अणु
	[0] = अणु 19599, 0, -2 पूर्ण,		/* voltage */
	[1] = अणु 800, 20475, -1 पूर्ण,	/* current */
	[2] = अणु 6123, 0, -2 पूर्ण,		/* घातer */
	[3] = अणु 42, 31880, -1 पूर्ण,	/* temperature */
पूर्ण;

अटल स्थिर काष्ठा coefficients adm1293_coefficients[] = अणु
	[0] = अणु 3333, -1, 0 पूर्ण,		/* voltage, vrange 1.2V */
	[1] = अणु 5552, -5, -1 पूर्ण,		/* voltage, vrange 7.4V */
	[2] = अणु 19604, -50, -2 पूर्ण,	/* voltage, vrange 21V */
	[3] = अणु 8000, -100, -2 पूर्ण,	/* current, irange25 */
	[4] = अणु 4000, -100, -2 पूर्ण,	/* current, irange50 */
	[5] = अणु 20000, -1000, -3 पूर्ण,	/* current, irange100 */
	[6] = अणु 10000, -1000, -3 पूर्ण,	/* current, irange200 */
	[7] = अणु 10417, 0, -1 पूर्ण,		/* घातer, 1.2V, irange25 */
	[8] = अणु 5208, 0, -1 पूर्ण,		/* घातer, 1.2V, irange50 */
	[9] = अणु 26042, 0, -2 पूर्ण,		/* घातer, 1.2V, irange100 */
	[10] = अणु 13021, 0, -2 पूर्ण,	/* घातer, 1.2V, irange200 */
	[11] = अणु 17351, 0, -2 पूर्ण,	/* घातer, 7.4V, irange25 */
	[12] = अणु 8676, 0, -2 पूर्ण,		/* घातer, 7.4V, irange50 */
	[13] = अणु 4338, 0, -2 पूर्ण,		/* घातer, 7.4V, irange100 */
	[14] = अणु 21689, 0, -3 पूर्ण,	/* घातer, 7.4V, irange200 */
	[15] = अणु 6126, 0, -2 पूर्ण,		/* घातer, 21V, irange25 */
	[16] = अणु 30631, 0, -3 पूर्ण,	/* घातer, 21V, irange50 */
	[17] = अणु 15316, 0, -3 पूर्ण,	/* घातer, 21V, irange100 */
	[18] = अणु 7658, 0, -3 पूर्ण,		/* घातer, 21V, irange200 */
पूर्ण;

अटल पूर्णांक adm1275_पढ़ो_pmon_config(स्थिर काष्ठा adm1275_data *data,
				    काष्ठा i2c_client *client, bool is_घातer)
अणु
	पूर्णांक shअगरt, ret;
	u16 mask;

	/*
	 * The PMON configuration रेजिस्टर is a 16-bit रेजिस्टर only on chips
	 * supporting घातer average sampling. On other chips it is an 8-bit
	 * रेजिस्टर.
	 */
	अगर (data->have_घातer_sampling) अणु
		ret = i2c_smbus_पढ़ो_word_data(client, ADM1275_PMON_CONFIG);
		mask = is_घातer ? ADM1278_PWR_AVG_MASK : ADM1278_VI_AVG_MASK;
		shअगरt = is_घातer ? ADM1278_PWR_AVG_SHIFT : ADM1278_VI_AVG_SHIFT;
	पूर्ण अन्यथा अणु
		ret = i2c_smbus_पढ़ो_byte_data(client, ADM1275_PMON_CONFIG);
		mask = ADM1275_VI_AVG_MASK;
		shअगरt = ADM1275_VI_AVG_SHIFT;
	पूर्ण
	अगर (ret < 0)
		वापस ret;

	वापस (ret & mask) >> shअगरt;
पूर्ण

अटल पूर्णांक adm1275_ग_लिखो_pmon_config(स्थिर काष्ठा adm1275_data *data,
				     काष्ठा i2c_client *client,
				     bool is_घातer, u16 word)
अणु
	पूर्णांक shअगरt, ret;
	u16 mask;

	अगर (data->have_घातer_sampling) अणु
		ret = i2c_smbus_पढ़ो_word_data(client, ADM1275_PMON_CONFIG);
		mask = is_घातer ? ADM1278_PWR_AVG_MASK : ADM1278_VI_AVG_MASK;
		shअगरt = is_घातer ? ADM1278_PWR_AVG_SHIFT : ADM1278_VI_AVG_SHIFT;
	पूर्ण अन्यथा अणु
		ret = i2c_smbus_पढ़ो_byte_data(client, ADM1275_PMON_CONFIG);
		mask = ADM1275_VI_AVG_MASK;
		shअगरt = ADM1275_VI_AVG_SHIFT;
	पूर्ण
	अगर (ret < 0)
		वापस ret;

	word = (ret & ~mask) | ((word << shअगरt) & mask);
	अगर (data->have_घातer_sampling)
		ret = i2c_smbus_ग_लिखो_word_data(client, ADM1275_PMON_CONFIG,
						word);
	अन्यथा
		ret = i2c_smbus_ग_लिखो_byte_data(client, ADM1275_PMON_CONFIG,
						word);

	वापस ret;
पूर्ण

अटल पूर्णांक adm1275_पढ़ो_word_data(काष्ठा i2c_client *client, पूर्णांक page,
				  पूर्णांक phase, पूर्णांक reg)
अणु
	स्थिर काष्ठा pmbus_driver_info *info = pmbus_get_driver_info(client);
	स्थिर काष्ठा adm1275_data *data = to_adm1275_data(info);
	पूर्णांक ret = 0;

	अगर (page > 0)
		वापस -ENXIO;

	चयन (reg) अणु
	हाल PMBUS_IOUT_UC_FAULT_LIMIT:
		अगर (!data->have_uc_fault)
			वापस -ENXIO;
		ret = pmbus_पढ़ो_word_data(client, 0, 0xff,
					   ADM1275_IOUT_WARN2_LIMIT);
		अवरोध;
	हाल PMBUS_IOUT_OC_FAULT_LIMIT:
		अगर (!data->have_oc_fault)
			वापस -ENXIO;
		ret = pmbus_पढ़ो_word_data(client, 0, 0xff,
					   ADM1275_IOUT_WARN2_LIMIT);
		अवरोध;
	हाल PMBUS_VOUT_OV_WARN_LIMIT:
		अगर (data->have_vout)
			वापस -ENODATA;
		ret = pmbus_पढ़ो_word_data(client, 0, 0xff,
					   ADM1075_VAUX_OV_WARN_LIMIT);
		अवरोध;
	हाल PMBUS_VOUT_UV_WARN_LIMIT:
		अगर (data->have_vout)
			वापस -ENODATA;
		ret = pmbus_पढ़ो_word_data(client, 0, 0xff,
					   ADM1075_VAUX_UV_WARN_LIMIT);
		अवरोध;
	हाल PMBUS_READ_VOUT:
		अगर (data->have_vout)
			वापस -ENODATA;
		ret = pmbus_पढ़ो_word_data(client, 0, 0xff,
					   ADM1075_READ_VAUX);
		अवरोध;
	हाल PMBUS_VIRT_READ_IOUT_MIN:
		अगर (!data->have_iout_min)
			वापस -ENXIO;
		ret = pmbus_पढ़ो_word_data(client, 0, 0xff,
					   ADM1293_IOUT_MIN);
		अवरोध;
	हाल PMBUS_VIRT_READ_IOUT_MAX:
		ret = pmbus_पढ़ो_word_data(client, 0, 0xff,
					   ADM1275_PEAK_IOUT);
		अवरोध;
	हाल PMBUS_VIRT_READ_VOUT_MAX:
		ret = pmbus_पढ़ो_word_data(client, 0, 0xff,
					   ADM1275_PEAK_VOUT);
		अवरोध;
	हाल PMBUS_VIRT_READ_VIN_MAX:
		ret = pmbus_पढ़ो_word_data(client, 0, 0xff,
					   ADM1275_PEAK_VIN);
		अवरोध;
	हाल PMBUS_VIRT_READ_PIN_MIN:
		अगर (!data->have_pin_min)
			वापस -ENXIO;
		ret = pmbus_पढ़ो_word_data(client, 0, 0xff,
					   ADM1293_PIN_MIN);
		अवरोध;
	हाल PMBUS_VIRT_READ_PIN_MAX:
		अगर (!data->have_pin_max)
			वापस -ENXIO;
		ret = pmbus_पढ़ो_word_data(client, 0, 0xff,
					   ADM1276_PEAK_PIN);
		अवरोध;
	हाल PMBUS_VIRT_READ_TEMP_MAX:
		अगर (!data->have_temp_max)
			वापस -ENXIO;
		ret = pmbus_पढ़ो_word_data(client, 0, 0xff,
					   ADM1278_PEAK_TEMP);
		अवरोध;
	हाल PMBUS_VIRT_RESET_IOUT_HISTORY:
	हाल PMBUS_VIRT_RESET_VOUT_HISTORY:
	हाल PMBUS_VIRT_RESET_VIN_HISTORY:
		अवरोध;
	हाल PMBUS_VIRT_RESET_PIN_HISTORY:
		अगर (!data->have_pin_max)
			वापस -ENXIO;
		अवरोध;
	हाल PMBUS_VIRT_RESET_TEMP_HISTORY:
		अगर (!data->have_temp_max)
			वापस -ENXIO;
		अवरोध;
	हाल PMBUS_VIRT_POWER_SAMPLES:
		अगर (!data->have_घातer_sampling)
			वापस -ENXIO;
		ret = adm1275_पढ़ो_pmon_config(data, client, true);
		अगर (ret < 0)
			अवरोध;
		ret = BIT(ret);
		अवरोध;
	हाल PMBUS_VIRT_IN_SAMPLES:
	हाल PMBUS_VIRT_CURR_SAMPLES:
		ret = adm1275_पढ़ो_pmon_config(data, client, false);
		अगर (ret < 0)
			अवरोध;
		ret = BIT(ret);
		अवरोध;
	शेष:
		ret = -ENODATA;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक adm1275_ग_लिखो_word_data(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक reg,
				   u16 word)
अणु
	स्थिर काष्ठा pmbus_driver_info *info = pmbus_get_driver_info(client);
	स्थिर काष्ठा adm1275_data *data = to_adm1275_data(info);
	पूर्णांक ret;

	अगर (page > 0)
		वापस -ENXIO;

	चयन (reg) अणु
	हाल PMBUS_IOUT_UC_FAULT_LIMIT:
	हाल PMBUS_IOUT_OC_FAULT_LIMIT:
		ret = pmbus_ग_लिखो_word_data(client, 0, ADM1275_IOUT_WARN2_LIMIT,
					    word);
		अवरोध;
	हाल PMBUS_VIRT_RESET_IOUT_HISTORY:
		ret = pmbus_ग_लिखो_word_data(client, 0, ADM1275_PEAK_IOUT, 0);
		अगर (!ret && data->have_iout_min)
			ret = pmbus_ग_लिखो_word_data(client, 0,
						    ADM1293_IOUT_MIN, 0);
		अवरोध;
	हाल PMBUS_VIRT_RESET_VOUT_HISTORY:
		ret = pmbus_ग_लिखो_word_data(client, 0, ADM1275_PEAK_VOUT, 0);
		अवरोध;
	हाल PMBUS_VIRT_RESET_VIN_HISTORY:
		ret = pmbus_ग_लिखो_word_data(client, 0, ADM1275_PEAK_VIN, 0);
		अवरोध;
	हाल PMBUS_VIRT_RESET_PIN_HISTORY:
		ret = pmbus_ग_लिखो_word_data(client, 0, ADM1276_PEAK_PIN, 0);
		अगर (!ret && data->have_pin_min)
			ret = pmbus_ग_लिखो_word_data(client, 0,
						    ADM1293_PIN_MIN, 0);
		अवरोध;
	हाल PMBUS_VIRT_RESET_TEMP_HISTORY:
		ret = pmbus_ग_लिखो_word_data(client, 0, ADM1278_PEAK_TEMP, 0);
		अवरोध;
	हाल PMBUS_VIRT_POWER_SAMPLES:
		अगर (!data->have_घातer_sampling)
			वापस -ENXIO;
		word = clamp_val(word, 1, ADM1275_SAMPLES_AVG_MAX);
		ret = adm1275_ग_लिखो_pmon_config(data, client, true,
						ilog2(word));
		अवरोध;
	हाल PMBUS_VIRT_IN_SAMPLES:
	हाल PMBUS_VIRT_CURR_SAMPLES:
		word = clamp_val(word, 1, ADM1275_SAMPLES_AVG_MAX);
		ret = adm1275_ग_लिखो_pmon_config(data, client, false,
						ilog2(word));
		अवरोध;
	शेष:
		ret = -ENODATA;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक adm1275_पढ़ो_byte_data(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक reg)
अणु
	स्थिर काष्ठा pmbus_driver_info *info = pmbus_get_driver_info(client);
	स्थिर काष्ठा adm1275_data *data = to_adm1275_data(info);
	पूर्णांक mfr_status, ret;

	अगर (page > 0)
		वापस -ENXIO;

	चयन (reg) अणु
	हाल PMBUS_STATUS_IOUT:
		ret = pmbus_पढ़ो_byte_data(client, page, PMBUS_STATUS_IOUT);
		अगर (ret < 0)
			अवरोध;
		अगर (!data->have_oc_fault && !data->have_uc_fault)
			अवरोध;
		mfr_status = pmbus_पढ़ो_byte_data(client, page,
						  PMBUS_STATUS_MFR_SPECIFIC);
		अगर (mfr_status < 0)
			वापस mfr_status;
		अगर (mfr_status & ADM1275_MFR_STATUS_IOUT_WARN2) अणु
			ret |= data->have_oc_fault ?
			  PB_IOUT_OC_FAULT : PB_IOUT_UC_FAULT;
		पूर्ण
		अवरोध;
	हाल PMBUS_STATUS_VOUT:
		अगर (data->have_vout)
			वापस -ENODATA;
		ret = 0;
		अगर (data->have_vaux_status) अणु
			mfr_status = pmbus_पढ़ो_byte_data(client, 0,
							  ADM1075_VAUX_STATUS);
			अगर (mfr_status < 0)
				वापस mfr_status;
			अगर (mfr_status & ADM1075_VAUX_OV_WARN)
				ret |= PB_VOLTAGE_OV_WARNING;
			अगर (mfr_status & ADM1075_VAUX_UV_WARN)
				ret |= PB_VOLTAGE_UV_WARNING;
		पूर्ण अन्यथा अगर (data->have_mfr_vaux_status) अणु
			mfr_status = pmbus_पढ़ो_byte_data(client, page,
						PMBUS_STATUS_MFR_SPECIFIC);
			अगर (mfr_status < 0)
				वापस mfr_status;
			अगर (mfr_status & ADM1293_MFR_STATUS_VAUX_OV_WARN)
				ret |= PB_VOLTAGE_OV_WARNING;
			अगर (mfr_status & ADM1293_MFR_STATUS_VAUX_UV_WARN)
				ret |= PB_VOLTAGE_UV_WARNING;
		पूर्ण
		अवरोध;
	शेष:
		ret = -ENODATA;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id adm1275_id[] = अणु
	अणु "adm1075", adm1075 पूर्ण,
	अणु "adm1272", adm1272 पूर्ण,
	अणु "adm1275", adm1275 पूर्ण,
	अणु "adm1276", adm1276 पूर्ण,
	अणु "adm1278", adm1278 पूर्ण,
	अणु "adm1293", adm1293 पूर्ण,
	अणु "adm1294", adm1294 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adm1275_id);

अटल पूर्णांक adm1275_probe(काष्ठा i2c_client *client)
अणु
	s32 (*config_पढ़ो_fn)(स्थिर काष्ठा i2c_client *client, u8 reg);
	u8 block_buffer[I2C_SMBUS_BLOCK_MAX + 1];
	पूर्णांक config, device_config;
	पूर्णांक ret;
	काष्ठा pmbus_driver_info *info;
	काष्ठा adm1275_data *data;
	स्थिर काष्ठा i2c_device_id *mid;
	स्थिर काष्ठा coefficients *coefficients;
	पूर्णांक vindex = -1, voindex = -1, cindex = -1, pindex = -1;
	पूर्णांक tindex = -1;
	u32 shunt;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_READ_BYTE_DATA
				     | I2C_FUNC_SMBUS_BLOCK_DATA))
		वापस -ENODEV;

	ret = i2c_smbus_पढ़ो_block_data(client, PMBUS_MFR_ID, block_buffer);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Failed to read Manufacturer ID\n");
		वापस ret;
	पूर्ण
	अगर (ret != 3 || म_भेदन(block_buffer, "ADI", 3)) अणु
		dev_err(&client->dev, "Unsupported Manufacturer ID\n");
		वापस -ENODEV;
	पूर्ण

	ret = i2c_smbus_पढ़ो_block_data(client, PMBUS_MFR_MODEL, block_buffer);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Failed to read Manufacturer Model\n");
		वापस ret;
	पूर्ण
	क्रम (mid = adm1275_id; mid->name[0]; mid++) अणु
		अगर (!strnहालcmp(mid->name, block_buffer, म_माप(mid->name)))
			अवरोध;
	पूर्ण
	अगर (!mid->name[0]) अणु
		dev_err(&client->dev, "Unsupported device\n");
		वापस -ENODEV;
	पूर्ण

	अगर (म_भेद(client->name, mid->name) != 0)
		dev_notice(&client->dev,
			   "Device mismatch: Configured %s, detected %s\n",
			   client->name, mid->name);

	अगर (mid->driver_data == adm1272 || mid->driver_data == adm1278 ||
	    mid->driver_data == adm1293 || mid->driver_data == adm1294)
		config_पढ़ो_fn = i2c_smbus_पढ़ो_word_data;
	अन्यथा
		config_पढ़ो_fn = i2c_smbus_पढ़ो_byte_data;
	config = config_पढ़ो_fn(client, ADM1275_PMON_CONFIG);
	अगर (config < 0)
		वापस config;

	device_config = config_पढ़ो_fn(client, ADM1275_DEVICE_CONFIG);
	अगर (device_config < 0)
		वापस device_config;

	data = devm_kzalloc(&client->dev, माप(काष्ठा adm1275_data),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	अगर (of_property_पढ़ो_u32(client->dev.of_node,
				 "shunt-resistor-micro-ohms", &shunt))
		shunt = 1000; /* 1 mOhm अगर not set via DT */

	अगर (shunt == 0)
		वापस -EINVAL;

	data->id = mid->driver_data;

	info = &data->info;

	info->pages = 1;
	info->क्रमmat[PSC_VOLTAGE_IN] = direct;
	info->क्रमmat[PSC_VOLTAGE_OUT] = direct;
	info->क्रमmat[PSC_CURRENT_OUT] = direct;
	info->क्रमmat[PSC_POWER] = direct;
	info->क्रमmat[PSC_TEMPERATURE] = direct;
	info->func[0] = PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
			PMBUS_HAVE_SAMPLES;

	info->पढ़ो_word_data = adm1275_पढ़ो_word_data;
	info->पढ़ो_byte_data = adm1275_पढ़ो_byte_data;
	info->ग_लिखो_word_data = adm1275_ग_लिखो_word_data;

	चयन (data->id) अणु
	हाल adm1075:
		अगर (device_config & ADM1275_IOUT_WARN2_SELECT)
			data->have_oc_fault = true;
		अन्यथा
			data->have_uc_fault = true;
		data->have_pin_max = true;
		data->have_vaux_status = true;

		coefficients = adm1075_coefficients;
		vindex = 0;
		चयन (config & ADM1075_IRANGE_MASK) अणु
		हाल ADM1075_IRANGE_25:
			cindex = 1;
			pindex = 3;
			अवरोध;
		हाल ADM1075_IRANGE_50:
			cindex = 2;
			pindex = 4;
			अवरोध;
		शेष:
			dev_err(&client->dev, "Invalid input current range");
			अवरोध;
		पूर्ण

		info->func[0] |= PMBUS_HAVE_VIN | PMBUS_HAVE_PIN
		  | PMBUS_HAVE_STATUS_INPUT;
		अगर (config & ADM1275_VIN_VOUT_SELECT)
			info->func[0] |=
			  PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT;
		अवरोध;
	हाल adm1272:
		data->have_vout = true;
		data->have_pin_max = true;
		data->have_temp_max = true;
		data->have_घातer_sampling = true;

		coefficients = adm1272_coefficients;
		vindex = (config & ADM1275_VRANGE) ? 1 : 0;
		cindex = (config & ADM1272_IRANGE) ? 3 : 2;
		/* pindex depends on the combination of the above */
		चयन (config & (ADM1275_VRANGE | ADM1272_IRANGE)) अणु
		हाल 0:
		शेष:
			pindex = 4;
			अवरोध;
		हाल ADM1275_VRANGE:
			pindex = 5;
			अवरोध;
		हाल ADM1272_IRANGE:
			pindex = 6;
			अवरोध;
		हाल ADM1275_VRANGE | ADM1272_IRANGE:
			pindex = 7;
			अवरोध;
		पूर्ण
		tindex = 8;

		info->func[0] |= PMBUS_HAVE_PIN | PMBUS_HAVE_STATUS_INPUT |
			PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT;

		/* Enable VOUT अगर not enabled (it is disabled by शेष) */
		अगर (!(config & ADM1278_VOUT_EN)) अणु
			config |= ADM1278_VOUT_EN;
			ret = i2c_smbus_ग_लिखो_byte_data(client,
							ADM1275_PMON_CONFIG,
							config);
			अगर (ret < 0) अणु
				dev_err(&client->dev,
					"Failed to enable VOUT monitoring\n");
				वापस -ENODEV;
			पूर्ण
		पूर्ण

		अगर (config & ADM1278_TEMP1_EN)
			info->func[0] |=
				PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP;
		अगर (config & ADM1278_VIN_EN)
			info->func[0] |= PMBUS_HAVE_VIN;
		अवरोध;
	हाल adm1275:
		अगर (device_config & ADM1275_IOUT_WARN2_SELECT)
			data->have_oc_fault = true;
		अन्यथा
			data->have_uc_fault = true;
		data->have_vout = true;

		coefficients = adm1275_coefficients;
		vindex = (config & ADM1275_VRANGE) ? 0 : 1;
		cindex = 2;

		अगर (config & ADM1275_VIN_VOUT_SELECT)
			info->func[0] |=
			  PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT;
		अन्यथा
			info->func[0] |=
			  PMBUS_HAVE_VIN | PMBUS_HAVE_STATUS_INPUT;
		अवरोध;
	हाल adm1276:
		अगर (device_config & ADM1275_IOUT_WARN2_SELECT)
			data->have_oc_fault = true;
		अन्यथा
			data->have_uc_fault = true;
		data->have_vout = true;
		data->have_pin_max = true;

		coefficients = adm1276_coefficients;
		vindex = (config & ADM1275_VRANGE) ? 0 : 1;
		cindex = 2;
		pindex = (config & ADM1275_VRANGE) ? 3 : 4;

		info->func[0] |= PMBUS_HAVE_VIN | PMBUS_HAVE_PIN
		  | PMBUS_HAVE_STATUS_INPUT;
		अगर (config & ADM1275_VIN_VOUT_SELECT)
			info->func[0] |=
			  PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT;
		अवरोध;
	हाल adm1278:
		data->have_vout = true;
		data->have_pin_max = true;
		data->have_temp_max = true;
		data->have_घातer_sampling = true;

		coefficients = adm1278_coefficients;
		vindex = 0;
		cindex = 1;
		pindex = 2;
		tindex = 3;

		info->func[0] |= PMBUS_HAVE_PIN | PMBUS_HAVE_STATUS_INPUT |
			PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
			PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP;

		/* Enable VOUT & TEMP1 अगर not enabled (disabled by शेष) */
		अगर ((config & (ADM1278_VOUT_EN | ADM1278_TEMP1_EN)) !=
		    (ADM1278_VOUT_EN | ADM1278_TEMP1_EN)) अणु
			config |= ADM1278_VOUT_EN | ADM1278_TEMP1_EN;
			ret = i2c_smbus_ग_लिखो_byte_data(client,
							ADM1275_PMON_CONFIG,
							config);
			अगर (ret < 0) अणु
				dev_err(&client->dev,
					"Failed to enable VOUT monitoring\n");
				वापस -ENODEV;
			पूर्ण
		पूर्ण

		अगर (config & ADM1278_VIN_EN)
			info->func[0] |= PMBUS_HAVE_VIN;
		अवरोध;
	हाल adm1293:
	हाल adm1294:
		data->have_iout_min = true;
		data->have_pin_min = true;
		data->have_pin_max = true;
		data->have_mfr_vaux_status = true;
		data->have_घातer_sampling = true;

		coefficients = adm1293_coefficients;

		voindex = 0;
		चयन (config & ADM1293_VIN_SEL_MASK) अणु
		हाल ADM1293_VIN_SEL_012:	/* 1.2V */
			vindex = 0;
			अवरोध;
		हाल ADM1293_VIN_SEL_074:	/* 7.4V */
			vindex = 1;
			अवरोध;
		हाल ADM1293_VIN_SEL_210:	/* 21V */
			vindex = 2;
			अवरोध;
		शेष:			/* disabled */
			अवरोध;
		पूर्ण

		चयन (config & ADM1293_IRANGE_MASK) अणु
		हाल ADM1293_IRANGE_25:
			cindex = 3;
			अवरोध;
		हाल ADM1293_IRANGE_50:
			cindex = 4;
			अवरोध;
		हाल ADM1293_IRANGE_100:
			cindex = 5;
			अवरोध;
		हाल ADM1293_IRANGE_200:
			cindex = 6;
			अवरोध;
		पूर्ण

		अगर (vindex >= 0)
			pindex = 7 + vindex * 4 + (cindex - 3);

		अगर (config & ADM1293_VAUX_EN)
			info->func[0] |=
				PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT;

		info->func[0] |= PMBUS_HAVE_PIN |
			PMBUS_HAVE_VIN | PMBUS_HAVE_STATUS_INPUT;

		अवरोध;
	शेष:
		dev_err(&client->dev, "Unsupported device\n");
		वापस -ENODEV;
	पूर्ण

	अगर (voindex < 0)
		voindex = vindex;
	अगर (vindex >= 0) अणु
		info->m[PSC_VOLTAGE_IN] = coefficients[vindex].m;
		info->b[PSC_VOLTAGE_IN] = coefficients[vindex].b;
		info->R[PSC_VOLTAGE_IN] = coefficients[vindex].R;
	पूर्ण
	अगर (voindex >= 0) अणु
		info->m[PSC_VOLTAGE_OUT] = coefficients[voindex].m;
		info->b[PSC_VOLTAGE_OUT] = coefficients[voindex].b;
		info->R[PSC_VOLTAGE_OUT] = coefficients[voindex].R;
	पूर्ण
	अगर (cindex >= 0) अणु
		/* Scale current with sense resistor value */
		info->m[PSC_CURRENT_OUT] =
			coefficients[cindex].m * shunt / 1000;
		info->b[PSC_CURRENT_OUT] = coefficients[cindex].b;
		info->R[PSC_CURRENT_OUT] = coefficients[cindex].R;
	पूर्ण
	अगर (pindex >= 0) अणु
		info->m[PSC_POWER] =
			coefficients[pindex].m * shunt / 1000;
		info->b[PSC_POWER] = coefficients[pindex].b;
		info->R[PSC_POWER] = coefficients[pindex].R;
	पूर्ण
	अगर (tindex >= 0) अणु
		info->m[PSC_TEMPERATURE] = coefficients[tindex].m;
		info->b[PSC_TEMPERATURE] = coefficients[tindex].b;
		info->R[PSC_TEMPERATURE] = coefficients[tindex].R;
	पूर्ण

	वापस pmbus_करो_probe(client, info);
पूर्ण

अटल काष्ठा i2c_driver adm1275_driver = अणु
	.driver = अणु
		   .name = "adm1275",
		   पूर्ण,
	.probe_new = adm1275_probe,
	.id_table = adm1275_id,
पूर्ण;

module_i2c_driver(adm1275_driver);

MODULE_AUTHOR("Guenter Roeck");
MODULE_DESCRIPTION("PMBus driver for Analog Devices ADM1275 and compatibles");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(PMBUS);
