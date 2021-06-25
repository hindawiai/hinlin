<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hardware monitoring driver क्रम LTC2978 and compatible chips.
 *
 * Copyright (c) 2011 Ericsson AB.
 * Copyright (c) 2013, 2014, 2015 Guenter Roeck
 * Copyright (c) 2015 Linear Technology
 * Copyright (c) 2018 Analog Devices Inc.
 */

#समावेश <linux/delay.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regulator/driver.h>
#समावेश "pmbus.h"

क्रमागत chips अणु
	/* Managers */
	ltc2972, ltc2974, ltc2975, ltc2977, ltc2978, ltc2979, ltc2980,
	/* Controllers */
	ltc3880, ltc3882, ltc3883, ltc3884, ltc3886, ltc3887, ltc3889, ltc7880,
	/* Modules */
	lपंचांग2987, lपंचांग4664, lपंचांग4675, lपंचांग4676, lपंचांग4677, lपंचांग4678, lपंचांग4680, lपंचांग4686,
	lपंचांग4700,
पूर्ण;

/* Common क्रम all chips */
#घोषणा LTC2978_MFR_VOUT_PEAK		0xdd
#घोषणा LTC2978_MFR_VIN_PEAK		0xde
#घोषणा LTC2978_MFR_TEMPERATURE_PEAK	0xdf
#घोषणा LTC2978_MFR_SPECIAL_ID		0xe7	/* Unकरोcumented on LTC3882 */
#घोषणा LTC2978_MFR_COMMON		0xef

/* LTC2974, LTC2975, LCT2977, LTC2980, LTC2978, and LTM2987 */
#घोषणा LTC2978_MFR_VOUT_MIN		0xfb
#घोषणा LTC2978_MFR_VIN_MIN		0xfc
#घोषणा LTC2978_MFR_TEMPERATURE_MIN	0xfd

/* LTC2974, LTC2975 */
#घोषणा LTC2974_MFR_IOUT_PEAK		0xd7
#घोषणा LTC2974_MFR_IOUT_MIN		0xd8

/* LTC3880, LTC3882, LTC3883, LTC3887, LTM4675, and LTM4676 */
#घोषणा LTC3880_MFR_IOUT_PEAK		0xd7
#घोषणा LTC3880_MFR_CLEAR_PEAKS		0xe3
#घोषणा LTC3880_MFR_TEMPERATURE2_PEAK	0xf4

/* LTC3883, LTC3884, LTC3886, LTC3889 and LTC7880 only */
#घोषणा LTC3883_MFR_IIN_PEAK		0xe1


/* LTC2975 only */
#घोषणा LTC2975_MFR_IIN_PEAK		0xc4
#घोषणा LTC2975_MFR_IIN_MIN		0xc5
#घोषणा LTC2975_MFR_PIN_PEAK		0xc6
#घोषणा LTC2975_MFR_PIN_MIN		0xc7

#घोषणा LTC2978_ID_MASK			0xfff0

#घोषणा LTC2972_ID			0x0310
#घोषणा LTC2974_ID			0x0210
#घोषणा LTC2975_ID			0x0220
#घोषणा LTC2977_ID			0x0130
#घोषणा LTC2978_ID_REV1			0x0110	/* Early revision */
#घोषणा LTC2978_ID_REV2			0x0120
#घोषणा LTC2979_ID_A			0x8060
#घोषणा LTC2979_ID_B			0x8070
#घोषणा LTC2980_ID_A			0x8030	/* A/B क्रम two die IDs */
#घोषणा LTC2980_ID_B			0x8040
#घोषणा LTC3880_ID			0x4020
#घोषणा LTC3882_ID			0x4200
#घोषणा LTC3882_ID_D1			0x4240	/* Dash 1 */
#घोषणा LTC3883_ID			0x4300
#घोषणा LTC3884_ID			0x4C00
#घोषणा LTC3886_ID			0x4600
#घोषणा LTC3887_ID			0x4700
#घोषणा LTM2987_ID_A			0x8010	/* A/B क्रम two die IDs */
#घोषणा LTM2987_ID_B			0x8020
#घोषणा LTC3889_ID			0x4900
#घोषणा LTC7880_ID			0x49E0
#घोषणा LTM4664_ID			0x4120
#घोषणा LTM4675_ID			0x47a0
#घोषणा LTM4676_ID_REV1			0x4400
#घोषणा LTM4676_ID_REV2			0x4480
#घोषणा LTM4676A_ID			0x47e0
#घोषणा LTM4677_ID_REV1			0x47B0
#घोषणा LTM4677_ID_REV2			0x47D0
#घोषणा LTM4678_ID_REV1			0x4100
#घोषणा LTM4678_ID_REV2			0x4110
#घोषणा LTM4680_ID			0x4140
#घोषणा LTM4686_ID			0x4770
#घोषणा LTM4700_ID			0x4130

#घोषणा LTC2972_NUM_PAGES		2
#घोषणा LTC2974_NUM_PAGES		4
#घोषणा LTC2978_NUM_PAGES		8
#घोषणा LTC3880_NUM_PAGES		2
#घोषणा LTC3883_NUM_PAGES		1

#घोषणा LTC_POLL_TIMEOUT		100	/* in milli-seconds */

#घोषणा LTC_NOT_BUSY			BIT(6)
#घोषणा LTC_NOT_PENDING			BIT(5)

/*
 * LTC2978 clears peak data whenever the CLEAR_FAULTS command is executed, which
 * happens pretty much each समय chip data is updated. Raw peak data thereक्रमe
 * करोes not provide much value. To be able to provide useful peak data, keep an
 * पूर्णांकernal cache of measured peak data, which is only cleared अगर an explicit
 * "clear peak" command is executed क्रम the sensor in question.
 */

काष्ठा ltc2978_data अणु
	क्रमागत chips id;
	u16 vin_min, vin_max;
	u16 temp_min[LTC2974_NUM_PAGES], temp_max[LTC2974_NUM_PAGES];
	u16 vout_min[LTC2978_NUM_PAGES], vout_max[LTC2978_NUM_PAGES];
	u16 iout_min[LTC2974_NUM_PAGES], iout_max[LTC2974_NUM_PAGES];
	u16 iin_min, iin_max;
	u16 pin_min, pin_max;
	u16 temp2_max;
	काष्ठा pmbus_driver_info info;
	u32 features;
पूर्ण;
#घोषणा to_ltc2978_data(x)  container_of(x, काष्ठा ltc2978_data, info)

#घोषणा FEAT_CLEAR_PEAKS	BIT(0)
#घोषणा FEAT_NEEDS_POLLING	BIT(1)

#घोषणा has_clear_peaks(d)	((d)->features & FEAT_CLEAR_PEAKS)
#घोषणा needs_polling(d)	((d)->features & FEAT_NEEDS_POLLING)

अटल पूर्णांक ltc_रुको_पढ़ोy(काष्ठा i2c_client *client)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(LTC_POLL_TIMEOUT);
	स्थिर काष्ठा pmbus_driver_info *info = pmbus_get_driver_info(client);
	काष्ठा ltc2978_data *data = to_ltc2978_data(info);
	पूर्णांक status;
	u8 mask;

	अगर (!needs_polling(data))
		वापस 0;

	/*
	 * LTC3883 करोes not support LTC_NOT_PENDING, even though
	 * the datasheet claims that it करोes.
	 */
	mask = LTC_NOT_BUSY;
	अगर (data->id != ltc3883)
		mask |= LTC_NOT_PENDING;

	करो अणु
		status = pmbus_पढ़ो_byte_data(client, 0, LTC2978_MFR_COMMON);
		अगर (status == -EBADMSG || status == -ENXIO) अणु
			/* PEC error or NACK: chip may be busy, try again */
			usleep_range(50, 100);
			जारी;
		पूर्ण
		अगर (status < 0)
			वापस status;

		अगर ((status & mask) == mask)
			वापस 0;

		usleep_range(50, 100);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक ltc_पढ़ो_word_data(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक phase,
			      पूर्णांक reg)
अणु
	पूर्णांक ret;

	ret = ltc_रुको_पढ़ोy(client);
	अगर (ret < 0)
		वापस ret;

	वापस pmbus_पढ़ो_word_data(client, page, 0xff, reg);
पूर्ण

अटल पूर्णांक ltc_पढ़ो_byte_data(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक reg)
अणु
	पूर्णांक ret;

	ret = ltc_रुको_पढ़ोy(client);
	अगर (ret < 0)
		वापस ret;

	वापस pmbus_पढ़ो_byte_data(client, page, reg);
पूर्ण

अटल पूर्णांक ltc_ग_लिखो_byte(काष्ठा i2c_client *client, पूर्णांक page, u8 byte)
अणु
	पूर्णांक ret;

	ret = ltc_रुको_पढ़ोy(client);
	अगर (ret < 0)
		वापस ret;

	वापस pmbus_ग_लिखो_byte(client, page, byte);
पूर्ण

अटल अंतरभूत पूर्णांक lin11_to_val(पूर्णांक data)
अणु
	s16 e = ((s16)data) >> 11;
	s32 m = (((s16)(data << 5)) >> 5);

	/*
	 * mantissa is 10 bit + sign, exponent adds up to 15 bit.
	 * Add 6 bit to exponent क्रम maximum accuracy (10 + 15 + 6 = 31).
	 */
	e += 6;
	वापस (e < 0 ? m >> -e : m << e);
पूर्ण

अटल पूर्णांक ltc_get_max(काष्ठा ltc2978_data *data, काष्ठा i2c_client *client,
		       पूर्णांक page, पूर्णांक reg, u16 *pmax)
अणु
	पूर्णांक ret;

	ret = ltc_पढ़ो_word_data(client, page, 0xff, reg);
	अगर (ret >= 0) अणु
		अगर (lin11_to_val(ret) > lin11_to_val(*pmax))
			*pmax = ret;
		ret = *pmax;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ltc_get_min(काष्ठा ltc2978_data *data, काष्ठा i2c_client *client,
		       पूर्णांक page, पूर्णांक reg, u16 *pmin)
अणु
	पूर्णांक ret;

	ret = ltc_पढ़ो_word_data(client, page, 0xff, reg);
	अगर (ret >= 0) अणु
		अगर (lin11_to_val(ret) < lin11_to_val(*pmin))
			*pmin = ret;
		ret = *pmin;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ltc2978_पढ़ो_word_data_common(काष्ठा i2c_client *client, पूर्णांक page,
					 पूर्णांक reg)
अणु
	स्थिर काष्ठा pmbus_driver_info *info = pmbus_get_driver_info(client);
	काष्ठा ltc2978_data *data = to_ltc2978_data(info);
	पूर्णांक ret;

	चयन (reg) अणु
	हाल PMBUS_VIRT_READ_VIN_MAX:
		ret = ltc_get_max(data, client, page, LTC2978_MFR_VIN_PEAK,
				  &data->vin_max);
		अवरोध;
	हाल PMBUS_VIRT_READ_VOUT_MAX:
		ret = ltc_पढ़ो_word_data(client, page, 0xff,
					 LTC2978_MFR_VOUT_PEAK);
		अगर (ret >= 0) अणु
			/*
			 * VOUT is 16 bit अचिन्हित with fixed exponent,
			 * so we can compare it directly
			 */
			अगर (ret > data->vout_max[page])
				data->vout_max[page] = ret;
			ret = data->vout_max[page];
		पूर्ण
		अवरोध;
	हाल PMBUS_VIRT_READ_TEMP_MAX:
		ret = ltc_get_max(data, client, page,
				  LTC2978_MFR_TEMPERATURE_PEAK,
				  &data->temp_max[page]);
		अवरोध;
	हाल PMBUS_VIRT_RESET_VOUT_HISTORY:
	हाल PMBUS_VIRT_RESET_VIN_HISTORY:
	हाल PMBUS_VIRT_RESET_TEMP_HISTORY:
		ret = 0;
		अवरोध;
	शेष:
		ret = ltc_रुको_पढ़ोy(client);
		अगर (ret < 0)
			वापस ret;
		ret = -ENODATA;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ltc2978_पढ़ो_word_data(काष्ठा i2c_client *client, पूर्णांक page,
				  पूर्णांक phase, पूर्णांक reg)
अणु
	स्थिर काष्ठा pmbus_driver_info *info = pmbus_get_driver_info(client);
	काष्ठा ltc2978_data *data = to_ltc2978_data(info);
	पूर्णांक ret;

	चयन (reg) अणु
	हाल PMBUS_VIRT_READ_VIN_MIN:
		ret = ltc_get_min(data, client, page, LTC2978_MFR_VIN_MIN,
				  &data->vin_min);
		अवरोध;
	हाल PMBUS_VIRT_READ_VOUT_MIN:
		ret = ltc_पढ़ो_word_data(client, page, phase,
					 LTC2978_MFR_VOUT_MIN);
		अगर (ret >= 0) अणु
			/*
			 * VOUT_MIN is known to not be supported on some lots
			 * of LTC2978 revision 1, and will वापस the maximum
			 * possible voltage अगर पढ़ो. If VOUT_MAX is valid and
			 * lower than the पढ़ोing of VOUT_MIN, use it instead.
			 */
			अगर (data->vout_max[page] && ret > data->vout_max[page])
				ret = data->vout_max[page];
			अगर (ret < data->vout_min[page])
				data->vout_min[page] = ret;
			ret = data->vout_min[page];
		पूर्ण
		अवरोध;
	हाल PMBUS_VIRT_READ_TEMP_MIN:
		ret = ltc_get_min(data, client, page,
				  LTC2978_MFR_TEMPERATURE_MIN,
				  &data->temp_min[page]);
		अवरोध;
	हाल PMBUS_VIRT_READ_IOUT_MAX:
	हाल PMBUS_VIRT_RESET_IOUT_HISTORY:
	हाल PMBUS_VIRT_READ_TEMP2_MAX:
	हाल PMBUS_VIRT_RESET_TEMP2_HISTORY:
		ret = -ENXIO;
		अवरोध;
	शेष:
		ret = ltc2978_पढ़ो_word_data_common(client, page, reg);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ltc2974_पढ़ो_word_data(काष्ठा i2c_client *client, पूर्णांक page,
				  पूर्णांक phase, पूर्णांक reg)
अणु
	स्थिर काष्ठा pmbus_driver_info *info = pmbus_get_driver_info(client);
	काष्ठा ltc2978_data *data = to_ltc2978_data(info);
	पूर्णांक ret;

	चयन (reg) अणु
	हाल PMBUS_VIRT_READ_IOUT_MAX:
		ret = ltc_get_max(data, client, page, LTC2974_MFR_IOUT_PEAK,
				  &data->iout_max[page]);
		अवरोध;
	हाल PMBUS_VIRT_READ_IOUT_MIN:
		ret = ltc_get_min(data, client, page, LTC2974_MFR_IOUT_MIN,
				  &data->iout_min[page]);
		अवरोध;
	हाल PMBUS_VIRT_RESET_IOUT_HISTORY:
		ret = 0;
		अवरोध;
	शेष:
		ret = ltc2978_पढ़ो_word_data(client, page, phase, reg);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ltc2975_पढ़ो_word_data(काष्ठा i2c_client *client, पूर्णांक page,
				  पूर्णांक phase, पूर्णांक reg)
अणु
	स्थिर काष्ठा pmbus_driver_info *info = pmbus_get_driver_info(client);
	काष्ठा ltc2978_data *data = to_ltc2978_data(info);
	पूर्णांक ret;

	चयन (reg) अणु
	हाल PMBUS_VIRT_READ_IIN_MAX:
		ret = ltc_get_max(data, client, page, LTC2975_MFR_IIN_PEAK,
				  &data->iin_max);
		अवरोध;
	हाल PMBUS_VIRT_READ_IIN_MIN:
		ret = ltc_get_min(data, client, page, LTC2975_MFR_IIN_MIN,
				  &data->iin_min);
		अवरोध;
	हाल PMBUS_VIRT_READ_PIN_MAX:
		ret = ltc_get_max(data, client, page, LTC2975_MFR_PIN_PEAK,
				  &data->pin_max);
		अवरोध;
	हाल PMBUS_VIRT_READ_PIN_MIN:
		ret = ltc_get_min(data, client, page, LTC2975_MFR_PIN_MIN,
				  &data->pin_min);
		अवरोध;
	हाल PMBUS_VIRT_RESET_IIN_HISTORY:
	हाल PMBUS_VIRT_RESET_PIN_HISTORY:
		ret = 0;
		अवरोध;
	शेष:
		ret = ltc2978_पढ़ो_word_data(client, page, phase, reg);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ltc3880_पढ़ो_word_data(काष्ठा i2c_client *client, पूर्णांक page,
				  पूर्णांक phase, पूर्णांक reg)
अणु
	स्थिर काष्ठा pmbus_driver_info *info = pmbus_get_driver_info(client);
	काष्ठा ltc2978_data *data = to_ltc2978_data(info);
	पूर्णांक ret;

	चयन (reg) अणु
	हाल PMBUS_VIRT_READ_IOUT_MAX:
		ret = ltc_get_max(data, client, page, LTC3880_MFR_IOUT_PEAK,
				  &data->iout_max[page]);
		अवरोध;
	हाल PMBUS_VIRT_READ_TEMP2_MAX:
		ret = ltc_get_max(data, client, page,
				  LTC3880_MFR_TEMPERATURE2_PEAK,
				  &data->temp2_max);
		अवरोध;
	हाल PMBUS_VIRT_READ_VIN_MIN:
	हाल PMBUS_VIRT_READ_VOUT_MIN:
	हाल PMBUS_VIRT_READ_TEMP_MIN:
		ret = -ENXIO;
		अवरोध;
	हाल PMBUS_VIRT_RESET_IOUT_HISTORY:
	हाल PMBUS_VIRT_RESET_TEMP2_HISTORY:
		ret = 0;
		अवरोध;
	शेष:
		ret = ltc2978_पढ़ो_word_data_common(client, page, reg);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ltc3883_पढ़ो_word_data(काष्ठा i2c_client *client, पूर्णांक page,
				  पूर्णांक phase, पूर्णांक reg)
अणु
	स्थिर काष्ठा pmbus_driver_info *info = pmbus_get_driver_info(client);
	काष्ठा ltc2978_data *data = to_ltc2978_data(info);
	पूर्णांक ret;

	चयन (reg) अणु
	हाल PMBUS_VIRT_READ_IIN_MAX:
		ret = ltc_get_max(data, client, page, LTC3883_MFR_IIN_PEAK,
				  &data->iin_max);
		अवरोध;
	हाल PMBUS_VIRT_RESET_IIN_HISTORY:
		ret = 0;
		अवरोध;
	शेष:
		ret = ltc3880_पढ़ो_word_data(client, page, phase, reg);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ltc2978_clear_peaks(काष्ठा ltc2978_data *data,
			       काष्ठा i2c_client *client, पूर्णांक page)
अणु
	पूर्णांक ret;

	अगर (has_clear_peaks(data))
		ret = ltc_ग_लिखो_byte(client, 0, LTC3880_MFR_CLEAR_PEAKS);
	अन्यथा
		ret = ltc_ग_लिखो_byte(client, page, PMBUS_CLEAR_FAULTS);

	वापस ret;
पूर्ण

अटल पूर्णांक ltc2978_ग_लिखो_word_data(काष्ठा i2c_client *client, पूर्णांक page,
				    पूर्णांक reg, u16 word)
अणु
	स्थिर काष्ठा pmbus_driver_info *info = pmbus_get_driver_info(client);
	काष्ठा ltc2978_data *data = to_ltc2978_data(info);
	पूर्णांक ret;

	चयन (reg) अणु
	हाल PMBUS_VIRT_RESET_IIN_HISTORY:
		data->iin_max = 0x7c00;
		data->iin_min = 0x7bff;
		ret = ltc2978_clear_peaks(data, client, 0);
		अवरोध;
	हाल PMBUS_VIRT_RESET_PIN_HISTORY:
		data->pin_max = 0x7c00;
		data->pin_min = 0x7bff;
		ret = ltc2978_clear_peaks(data, client, 0);
		अवरोध;
	हाल PMBUS_VIRT_RESET_IOUT_HISTORY:
		data->iout_max[page] = 0x7c00;
		data->iout_min[page] = 0xfbff;
		ret = ltc2978_clear_peaks(data, client, page);
		अवरोध;
	हाल PMBUS_VIRT_RESET_TEMP2_HISTORY:
		data->temp2_max = 0x7c00;
		ret = ltc2978_clear_peaks(data, client, page);
		अवरोध;
	हाल PMBUS_VIRT_RESET_VOUT_HISTORY:
		data->vout_min[page] = 0xffff;
		data->vout_max[page] = 0;
		ret = ltc2978_clear_peaks(data, client, page);
		अवरोध;
	हाल PMBUS_VIRT_RESET_VIN_HISTORY:
		data->vin_min = 0x7bff;
		data->vin_max = 0x7c00;
		ret = ltc2978_clear_peaks(data, client, page);
		अवरोध;
	हाल PMBUS_VIRT_RESET_TEMP_HISTORY:
		data->temp_min[page] = 0x7bff;
		data->temp_max[page] = 0x7c00;
		ret = ltc2978_clear_peaks(data, client, page);
		अवरोध;
	शेष:
		ret = ltc_रुको_पढ़ोy(client);
		अगर (ret < 0)
			वापस ret;
		ret = -ENODATA;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ltc2978_id[] = अणु
	अणु"ltc2972", ltc2972पूर्ण,
	अणु"ltc2974", ltc2974पूर्ण,
	अणु"ltc2975", ltc2975पूर्ण,
	अणु"ltc2977", ltc2977पूर्ण,
	अणु"ltc2978", ltc2978पूर्ण,
	अणु"ltc2979", ltc2979पूर्ण,
	अणु"ltc2980", ltc2980पूर्ण,
	अणु"ltc3880", ltc3880पूर्ण,
	अणु"ltc3882", ltc3882पूर्ण,
	अणु"ltc3883", ltc3883पूर्ण,
	अणु"ltc3884", ltc3884पूर्ण,
	अणु"ltc3886", ltc3886पूर्ण,
	अणु"ltc3887", ltc3887पूर्ण,
	अणु"ltc3889", ltc3889पूर्ण,
	अणु"ltc7880", ltc7880पूर्ण,
	अणु"ltm2987", lपंचांग2987पूर्ण,
	अणु"ltm4664", lपंचांग4664पूर्ण,
	अणु"ltm4675", lपंचांग4675पूर्ण,
	अणु"ltm4676", lपंचांग4676पूर्ण,
	अणु"ltm4677", lपंचांग4677पूर्ण,
	अणु"ltm4678", lपंचांग4678पूर्ण,
	अणु"ltm4680", lपंचांग4680पूर्ण,
	अणु"ltm4686", lपंचांग4686पूर्ण,
	अणु"ltm4700", lपंचांग4700पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ltc2978_id);

#अगर IS_ENABLED(CONFIG_SENSORS_LTC2978_REGULATOR)
अटल स्थिर काष्ठा regulator_desc ltc2978_reg_desc[] = अणु
	PMBUS_REGULATOR("vout", 0),
	PMBUS_REGULATOR("vout", 1),
	PMBUS_REGULATOR("vout", 2),
	PMBUS_REGULATOR("vout", 3),
	PMBUS_REGULATOR("vout", 4),
	PMBUS_REGULATOR("vout", 5),
	PMBUS_REGULATOR("vout", 6),
	PMBUS_REGULATOR("vout", 7),
पूर्ण;
#पूर्ण_अगर /* CONFIG_SENSORS_LTC2978_REGULATOR */

अटल पूर्णांक ltc2978_get_id(काष्ठा i2c_client *client)
अणु
	पूर्णांक chip_id;

	chip_id = i2c_smbus_पढ़ो_word_data(client, LTC2978_MFR_SPECIAL_ID);
	अगर (chip_id < 0) अणु
		स्थिर काष्ठा i2c_device_id *id;
		u8 buf[I2C_SMBUS_BLOCK_MAX];
		पूर्णांक ret;

		अगर (!i2c_check_functionality(client->adapter,
					     I2C_FUNC_SMBUS_READ_BLOCK_DATA))
			वापस -ENODEV;

		ret = i2c_smbus_पढ़ो_block_data(client, PMBUS_MFR_ID, buf);
		अगर (ret < 0)
			वापस ret;
		अगर (ret < 3 || म_भेदन(buf, "LTC", 3))
			वापस -ENODEV;

		ret = i2c_smbus_पढ़ो_block_data(client, PMBUS_MFR_MODEL, buf);
		अगर (ret < 0)
			वापस ret;
		क्रम (id = &ltc2978_id[0]; म_माप(id->name); id++) अणु
			अगर (!strnहालcmp(id->name, buf, म_माप(id->name)))
				वापस (पूर्णांक)id->driver_data;
		पूर्ण
		वापस -ENODEV;
	पूर्ण

	chip_id &= LTC2978_ID_MASK;

	अगर (chip_id == LTC2972_ID)
		वापस ltc2972;
	अन्यथा अगर (chip_id == LTC2974_ID)
		वापस ltc2974;
	अन्यथा अगर (chip_id == LTC2975_ID)
		वापस ltc2975;
	अन्यथा अगर (chip_id == LTC2977_ID)
		वापस ltc2977;
	अन्यथा अगर (chip_id == LTC2978_ID_REV1 || chip_id == LTC2978_ID_REV2)
		वापस ltc2978;
	अन्यथा अगर (chip_id == LTC2979_ID_A || chip_id == LTC2979_ID_B)
		वापस ltc2979;
	अन्यथा अगर (chip_id == LTC2980_ID_A || chip_id == LTC2980_ID_B)
		वापस ltc2980;
	अन्यथा अगर (chip_id == LTC3880_ID)
		वापस ltc3880;
	अन्यथा अगर (chip_id == LTC3882_ID || chip_id == LTC3882_ID_D1)
		वापस ltc3882;
	अन्यथा अगर (chip_id == LTC3883_ID)
		वापस ltc3883;
	अन्यथा अगर (chip_id == LTC3884_ID)
		वापस ltc3884;
	अन्यथा अगर (chip_id == LTC3886_ID)
		वापस ltc3886;
	अन्यथा अगर (chip_id == LTC3887_ID)
		वापस ltc3887;
	अन्यथा अगर (chip_id == LTC3889_ID)
		वापस ltc3889;
	अन्यथा अगर (chip_id == LTC7880_ID)
		वापस ltc7880;
	अन्यथा अगर (chip_id == LTM2987_ID_A || chip_id == LTM2987_ID_B)
		वापस lपंचांग2987;
	अन्यथा अगर (chip_id == LTM4664_ID)
		वापस lपंचांग4664;
	अन्यथा अगर (chip_id == LTM4675_ID)
		वापस lपंचांग4675;
	अन्यथा अगर (chip_id == LTM4676_ID_REV1 || chip_id == LTM4676_ID_REV2 ||
		 chip_id == LTM4676A_ID)
		वापस lपंचांग4676;
	अन्यथा अगर (chip_id == LTM4677_ID_REV1 || chip_id == LTM4677_ID_REV2)
		वापस lपंचांग4677;
	अन्यथा अगर (chip_id == LTM4678_ID_REV1 || chip_id == LTM4678_ID_REV2)
		वापस lपंचांग4678;
	अन्यथा अगर (chip_id == LTM4680_ID)
		वापस lपंचांग4680;
	अन्यथा अगर (chip_id == LTM4686_ID)
		वापस lपंचांग4686;
	अन्यथा अगर (chip_id == LTM4700_ID)
		वापस lपंचांग4700;

	dev_err(&client->dev, "Unsupported chip ID 0x%x\n", chip_id);
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक ltc2978_probe(काष्ठा i2c_client *client)
अणु
	पूर्णांक i, chip_id;
	काष्ठा ltc2978_data *data;
	काष्ठा pmbus_driver_info *info;
	स्थिर काष्ठा i2c_device_id *id;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_READ_WORD_DATA))
		वापस -ENODEV;

	data = devm_kzalloc(&client->dev, माप(काष्ठा ltc2978_data),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	chip_id = ltc2978_get_id(client);
	अगर (chip_id < 0)
		वापस chip_id;

	data->id = chip_id;
	id = i2c_match_id(ltc2978_id, client);
	अगर (data->id != id->driver_data)
		dev_warn(&client->dev,
			 "Device mismatch: Configured %s (%d), detected %d\n",
			 id->name,
			 (पूर्णांक) id->driver_data,
			 chip_id);

	info = &data->info;
	info->ग_लिखो_word_data = ltc2978_ग_लिखो_word_data;
	info->ग_लिखो_byte = ltc_ग_लिखो_byte;
	info->पढ़ो_word_data = ltc_पढ़ो_word_data;
	info->पढ़ो_byte_data = ltc_पढ़ो_byte_data;

	data->vin_min = 0x7bff;
	data->vin_max = 0x7c00;
	क्रम (i = 0; i < ARRAY_SIZE(data->vout_min); i++)
		data->vout_min[i] = 0xffff;
	क्रम (i = 0; i < ARRAY_SIZE(data->iout_min); i++)
		data->iout_min[i] = 0xfbff;
	क्रम (i = 0; i < ARRAY_SIZE(data->iout_max); i++)
		data->iout_max[i] = 0x7c00;
	क्रम (i = 0; i < ARRAY_SIZE(data->temp_min); i++)
		data->temp_min[i] = 0x7bff;
	क्रम (i = 0; i < ARRAY_SIZE(data->temp_max); i++)
		data->temp_max[i] = 0x7c00;
	data->temp2_max = 0x7c00;

	चयन (data->id) अणु
	हाल ltc2972:
		info->पढ़ो_word_data = ltc2975_पढ़ो_word_data;
		info->pages = LTC2972_NUM_PAGES;
		info->func[0] = PMBUS_HAVE_IIN | PMBUS_HAVE_PIN
		  | PMBUS_HAVE_VIN | PMBUS_HAVE_STATUS_INPUT
		  | PMBUS_HAVE_TEMP2;
		क्रम (i = 0; i < info->pages; i++) अणु
			info->func[i] |= PMBUS_HAVE_VOUT
			  | PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_POUT
			  | PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP
			  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT;
		पूर्ण
		अवरोध;
	हाल ltc2974:
		info->पढ़ो_word_data = ltc2974_पढ़ो_word_data;
		info->pages = LTC2974_NUM_PAGES;
		info->func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_STATUS_INPUT
		  | PMBUS_HAVE_TEMP2;
		क्रम (i = 0; i < info->pages; i++) अणु
			info->func[i] |= PMBUS_HAVE_VOUT
			  | PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_POUT
			  | PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP
			  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT;
		पूर्ण
		अवरोध;
	हाल ltc2975:
		info->पढ़ो_word_data = ltc2975_पढ़ो_word_data;
		info->pages = LTC2974_NUM_PAGES;
		info->func[0] = PMBUS_HAVE_IIN | PMBUS_HAVE_PIN
		  | PMBUS_HAVE_VIN | PMBUS_HAVE_STATUS_INPUT
		  | PMBUS_HAVE_TEMP2;
		क्रम (i = 0; i < info->pages; i++) अणु
			info->func[i] |= PMBUS_HAVE_VOUT
			  | PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_POUT
			  | PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP
			  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT;
		पूर्ण
		अवरोध;

	हाल ltc2977:
	हाल ltc2978:
	हाल ltc2979:
	हाल ltc2980:
	हाल lपंचांग2987:
		info->पढ़ो_word_data = ltc2978_पढ़ो_word_data;
		info->pages = LTC2978_NUM_PAGES;
		info->func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_STATUS_INPUT
		  | PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP;
		क्रम (i = 1; i < LTC2978_NUM_PAGES; i++) अणु
			info->func[i] = PMBUS_HAVE_VOUT
			  | PMBUS_HAVE_STATUS_VOUT;
		पूर्ण
		अवरोध;
	हाल ltc3880:
	हाल ltc3887:
	हाल lपंचांग4675:
	हाल lपंचांग4676:
	हाल lपंचांग4677:
	हाल lपंचांग4686:
		data->features |= FEAT_CLEAR_PEAKS | FEAT_NEEDS_POLLING;
		info->पढ़ो_word_data = ltc3880_पढ़ो_word_data;
		info->pages = LTC3880_NUM_PAGES;
		info->func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_IIN
		  | PMBUS_HAVE_STATUS_INPUT
		  | PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT
		  | PMBUS_HAVE_POUT | PMBUS_HAVE_TEMP
		  | PMBUS_HAVE_TEMP2 | PMBUS_HAVE_STATUS_TEMP;
		info->func[1] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT
		  | PMBUS_HAVE_POUT
		  | PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP;
		अवरोध;
	हाल ltc3882:
		data->features |= FEAT_CLEAR_PEAKS | FEAT_NEEDS_POLLING;
		info->पढ़ो_word_data = ltc3880_पढ़ो_word_data;
		info->pages = LTC3880_NUM_PAGES;
		info->func[0] = PMBUS_HAVE_VIN
		  | PMBUS_HAVE_STATUS_INPUT
		  | PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT
		  | PMBUS_HAVE_POUT | PMBUS_HAVE_TEMP
		  | PMBUS_HAVE_TEMP2 | PMBUS_HAVE_STATUS_TEMP;
		info->func[1] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT
		  | PMBUS_HAVE_POUT
		  | PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP;
		अवरोध;
	हाल ltc3883:
		data->features |= FEAT_CLEAR_PEAKS | FEAT_NEEDS_POLLING;
		info->पढ़ो_word_data = ltc3883_पढ़ो_word_data;
		info->pages = LTC3883_NUM_PAGES;
		info->func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_IIN
		  | PMBUS_HAVE_STATUS_INPUT
		  | PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT
		  | PMBUS_HAVE_PIN | PMBUS_HAVE_POUT | PMBUS_HAVE_TEMP
		  | PMBUS_HAVE_TEMP2 | PMBUS_HAVE_STATUS_TEMP;
		अवरोध;
	हाल ltc3884:
	हाल ltc3886:
	हाल ltc3889:
	हाल ltc7880:
	हाल lपंचांग4664:
	हाल lपंचांग4678:
	हाल lपंचांग4680:
	हाल lपंचांग4700:
		data->features |= FEAT_CLEAR_PEAKS | FEAT_NEEDS_POLLING;
		info->पढ़ो_word_data = ltc3883_पढ़ो_word_data;
		info->pages = LTC3880_NUM_PAGES;
		info->func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_IIN
		  | PMBUS_HAVE_STATUS_INPUT
		  | PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT
		  | PMBUS_HAVE_PIN | PMBUS_HAVE_POUT | PMBUS_HAVE_TEMP
		  | PMBUS_HAVE_TEMP2 | PMBUS_HAVE_STATUS_TEMP;
		info->func[1] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		  | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT
		  | PMBUS_HAVE_POUT
		  | PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

#अगर IS_ENABLED(CONFIG_SENSORS_LTC2978_REGULATOR)
	info->num_regulators = info->pages;
	info->reg_desc = ltc2978_reg_desc;
	अगर (info->num_regulators > ARRAY_SIZE(ltc2978_reg_desc)) अणु
		dev_err(&client->dev, "num_regulators too large!");
		info->num_regulators = ARRAY_SIZE(ltc2978_reg_desc);
	पूर्ण
#पूर्ण_अगर

	वापस pmbus_करो_probe(client, info);
पूर्ण


#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id ltc2978_of_match[] = अणु
	अणु .compatible = "lltc,ltc2972" पूर्ण,
	अणु .compatible = "lltc,ltc2974" पूर्ण,
	अणु .compatible = "lltc,ltc2975" पूर्ण,
	अणु .compatible = "lltc,ltc2977" पूर्ण,
	अणु .compatible = "lltc,ltc2978" पूर्ण,
	अणु .compatible = "lltc,ltc2979" पूर्ण,
	अणु .compatible = "lltc,ltc2980" पूर्ण,
	अणु .compatible = "lltc,ltc3880" पूर्ण,
	अणु .compatible = "lltc,ltc3882" पूर्ण,
	अणु .compatible = "lltc,ltc3883" पूर्ण,
	अणु .compatible = "lltc,ltc3884" पूर्ण,
	अणु .compatible = "lltc,ltc3886" पूर्ण,
	अणु .compatible = "lltc,ltc3887" पूर्ण,
	अणु .compatible = "lltc,ltc3889" पूर्ण,
	अणु .compatible = "lltc,ltc7880" पूर्ण,
	अणु .compatible = "lltc,ltm2987" पूर्ण,
	अणु .compatible = "lltc,ltm4664" पूर्ण,
	अणु .compatible = "lltc,ltm4675" पूर्ण,
	अणु .compatible = "lltc,ltm4676" पूर्ण,
	अणु .compatible = "lltc,ltm4677" पूर्ण,
	अणु .compatible = "lltc,ltm4678" पूर्ण,
	अणु .compatible = "lltc,ltm4680" पूर्ण,
	अणु .compatible = "lltc,ltm4686" पूर्ण,
	अणु .compatible = "lltc,ltm4700" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ltc2978_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver ltc2978_driver = अणु
	.driver = अणु
		   .name = "ltc2978",
		   .of_match_table = of_match_ptr(ltc2978_of_match),
		   पूर्ण,
	.probe_new = ltc2978_probe,
	.id_table = ltc2978_id,
पूर्ण;

module_i2c_driver(ltc2978_driver);

MODULE_AUTHOR("Guenter Roeck");
MODULE_DESCRIPTION("PMBus driver for LTC2978 and compatible chips");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(PMBUS);
