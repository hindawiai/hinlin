<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * isl29501.c: ISL29501 Time of Flight sensor driver.
 *
 * Copyright (C) 2018
 * Author: Mathieu Othacehe <m.othacehe@gmail.com>
 *
 * 7-bit I2C slave address: 0x57
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/err.h>
#समावेश <linux/of_device.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/triggered_buffer.h>

/* Control, setting and status रेजिस्टरs */
#घोषणा ISL29501_DEVICE_ID			0x00
#घोषणा ISL29501_ID				0x0A

/* Sampling control रेजिस्टरs */
#घोषणा ISL29501_INTEGRATION_PERIOD		0x10
#घोषणा ISL29501_SAMPLE_PERIOD			0x11

/* Closed loop calibration रेजिस्टरs */
#घोषणा ISL29501_CROSSTALK_I_MSB		0x24
#घोषणा ISL29501_CROSSTALK_I_LSB		0x25
#घोषणा ISL29501_CROSSTALK_I_EXPONENT		0x26
#घोषणा ISL29501_CROSSTALK_Q_MSB		0x27
#घोषणा ISL29501_CROSSTALK_Q_LSB		0x28
#घोषणा ISL29501_CROSSTALK_Q_EXPONENT		0x29
#घोषणा ISL29501_CROSSTALK_GAIN_MSB		0x2A
#घोषणा ISL29501_CROSSTALK_GAIN_LSB		0x2B
#घोषणा ISL29501_MAGNITUDE_REF_EXP		0x2C
#घोषणा ISL29501_MAGNITUDE_REF_MSB		0x2D
#घोषणा ISL29501_MAGNITUDE_REF_LSB		0x2E
#घोषणा ISL29501_PHASE_OFFSET_MSB		0x2F
#घोषणा ISL29501_PHASE_OFFSET_LSB		0x30

/* Analog control रेजिस्टरs */
#घोषणा ISL29501_DRIVER_RANGE			0x90
#घोषणा ISL29501_EMITTER_DAC			0x91

#घोषणा ISL29501_COMMAND_REGISTER		0xB0

/* Commands */
#घोषणा ISL29501_EMUL_SAMPLE_START_PIN		0x49
#घोषणा ISL29501_RESET_ALL_REGISTERS		0xD7
#घोषणा ISL29501_RESET_INT_SM			0xD1

/* Ambiant light and temperature corrections */
#घोषणा ISL29501_TEMP_REFERENCE			0x31
#घोषणा ISL29501_PHASE_EXPONENT			0x33
#घोषणा ISL29501_TEMP_COEFF_A			0x34
#घोषणा ISL29501_TEMP_COEFF_B			0x39
#घोषणा ISL29501_AMBIANT_COEFF_A		0x36
#घोषणा ISL29501_AMBIANT_COEFF_B		0x3B

/* Data output रेजिस्टरs */
#घोषणा ISL29501_DISTANCE_MSB_DATA		0xD1
#घोषणा ISL29501_DISTANCE_LSB_DATA		0xD2
#घोषणा ISL29501_PRECISION_MSB			0xD3
#घोषणा ISL29501_PRECISION_LSB			0xD4
#घोषणा ISL29501_MAGNITUDE_EXPONENT		0xD5
#घोषणा ISL29501_MAGNITUDE_MSB			0xD6
#घोषणा ISL29501_MAGNITUDE_LSB			0xD7
#घोषणा ISL29501_PHASE_MSB			0xD8
#घोषणा ISL29501_PHASE_LSB			0xD9
#घोषणा ISL29501_I_RAW_EXPONENT			0xDA
#घोषणा ISL29501_I_RAW_MSB			0xDB
#घोषणा ISL29501_I_RAW_LSB			0xDC
#घोषणा ISL29501_Q_RAW_EXPONENT			0xDD
#घोषणा ISL29501_Q_RAW_MSB			0xDE
#घोषणा ISL29501_Q_RAW_LSB			0xDF
#घोषणा ISL29501_DIE_TEMPERATURE		0xE2
#घोषणा ISL29501_AMBIENT_LIGHT			0xE3
#घोषणा ISL29501_GAIN_MSB			0xE6
#घोषणा ISL29501_GAIN_LSB			0xE7

#घोषणा ISL29501_MAX_EXP_VAL 15

#घोषणा ISL29501_INT_TIME_AVAILABLE \
	"0.00007 0.00014 0.00028 0.00057 0.00114 " \
	"0.00228 0.00455 0.00910 0.01820 0.03640 " \
	"0.07281 0.14561"

#घोषणा ISL29501_CURRENT_SCALE_AVAILABLE \
	"0.0039 0.0078 0.0118 0.0157 0.0196 " \
	"0.0235 0.0275 0.0314 0.0352 0.0392 " \
	"0.0431 0.0471 0.0510 0.0549 0.0588"

क्रमागत isl29501_correction_coeff अणु
	COEFF_TEMP_A,
	COEFF_TEMP_B,
	COEFF_LIGHT_A,
	COEFF_LIGHT_B,
	COEFF_MAX,
पूर्ण;

काष्ठा isl29501_निजी अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;
	/* Exact representation of correction coefficients. */
	अचिन्हित पूर्णांक shaकरोw_coeffs[COEFF_MAX];
पूर्ण;

क्रमागत isl29501_रेजिस्टर_name अणु
	REG_DISTANCE,
	REG_PHASE,
	REG_TEMPERATURE,
	REG_AMBIENT_LIGHT,
	REG_GAIN,
	REG_GAIN_BIAS,
	REG_PHASE_EXP,
	REG_CALIB_PHASE_TEMP_A,
	REG_CALIB_PHASE_TEMP_B,
	REG_CALIB_PHASE_LIGHT_A,
	REG_CALIB_PHASE_LIGHT_B,
	REG_DISTANCE_BIAS,
	REG_TEMPERATURE_BIAS,
	REG_INT_TIME,
	REG_SAMPLE_TIME,
	REG_DRIVER_RANGE,
	REG_EMITTER_DAC,
पूर्ण;

काष्ठा isl29501_रेजिस्टर_desc अणु
	u8 msb;
	u8 lsb;
पूर्ण;

अटल स्थिर काष्ठा isl29501_रेजिस्टर_desc isl29501_रेजिस्टरs[] = अणु
	[REG_DISTANCE] = अणु
		.msb = ISL29501_DISTANCE_MSB_DATA,
		.lsb = ISL29501_DISTANCE_LSB_DATA,
	पूर्ण,
	[REG_PHASE] = अणु
		.msb = ISL29501_PHASE_MSB,
		.lsb = ISL29501_PHASE_LSB,
	पूर्ण,
	[REG_TEMPERATURE] = अणु
		.lsb = ISL29501_DIE_TEMPERATURE,
	पूर्ण,
	[REG_AMBIENT_LIGHT] = अणु
		.lsb = ISL29501_AMBIENT_LIGHT,
	पूर्ण,
	[REG_GAIN] = अणु
		.msb = ISL29501_GAIN_MSB,
		.lsb = ISL29501_GAIN_LSB,
	पूर्ण,
	[REG_GAIN_BIAS] = अणु
		.msb = ISL29501_CROSSTALK_GAIN_MSB,
		.lsb = ISL29501_CROSSTALK_GAIN_LSB,
	पूर्ण,
	[REG_PHASE_EXP] = अणु
		.lsb = ISL29501_PHASE_EXPONENT,
	पूर्ण,
	[REG_CALIB_PHASE_TEMP_A] = अणु
		.lsb = ISL29501_TEMP_COEFF_A,
	पूर्ण,
	[REG_CALIB_PHASE_TEMP_B] = अणु
		.lsb = ISL29501_TEMP_COEFF_B,
	पूर्ण,
	[REG_CALIB_PHASE_LIGHT_A] = अणु
		.lsb = ISL29501_AMBIANT_COEFF_A,
	पूर्ण,
	[REG_CALIB_PHASE_LIGHT_B] = अणु
		.lsb = ISL29501_AMBIANT_COEFF_B,
	पूर्ण,
	[REG_DISTANCE_BIAS] = अणु
		.msb = ISL29501_PHASE_OFFSET_MSB,
		.lsb = ISL29501_PHASE_OFFSET_LSB,
	पूर्ण,
	[REG_TEMPERATURE_BIAS] = अणु
		.lsb = ISL29501_TEMP_REFERENCE,
	पूर्ण,
	[REG_INT_TIME] = अणु
		.lsb = ISL29501_INTEGRATION_PERIOD,
	पूर्ण,
	[REG_SAMPLE_TIME] = अणु
		.lsb = ISL29501_SAMPLE_PERIOD,
	पूर्ण,
	[REG_DRIVER_RANGE] = अणु
		.lsb = ISL29501_DRIVER_RANGE,
	पूर्ण,
	[REG_EMITTER_DAC] = अणु
		.lsb = ISL29501_EMITTER_DAC,
	पूर्ण,
पूर्ण;

अटल पूर्णांक isl29501_रेजिस्टर_पढ़ो(काष्ठा isl29501_निजी *isl29501,
				  क्रमागत isl29501_रेजिस्टर_name name,
				  u32 *val)
अणु
	स्थिर काष्ठा isl29501_रेजिस्टर_desc *reg = &isl29501_रेजिस्टरs[name];
	u8 msb = 0, lsb = 0;
	s32 ret;

	mutex_lock(&isl29501->lock);
	अगर (reg->msb) अणु
		ret = i2c_smbus_पढ़ो_byte_data(isl29501->client, reg->msb);
		अगर (ret < 0)
			जाओ err;
		msb = ret;
	पूर्ण

	अगर (reg->lsb) अणु
		ret = i2c_smbus_पढ़ो_byte_data(isl29501->client, reg->lsb);
		अगर (ret < 0)
			जाओ err;
		lsb = ret;
	पूर्ण
	mutex_unlock(&isl29501->lock);

	*val = (msb << 8) + lsb;

	वापस 0;
err:
	mutex_unlock(&isl29501->lock);

	वापस ret;
पूर्ण

अटल u32 isl29501_रेजिस्टर_ग_लिखो(काष्ठा isl29501_निजी *isl29501,
				   क्रमागत isl29501_रेजिस्टर_name name,
				   u32 value)
अणु
	स्थिर काष्ठा isl29501_रेजिस्टर_desc *reg = &isl29501_रेजिस्टरs[name];
	पूर्णांक ret;

	अगर (!reg->msb && value > U8_MAX)
		वापस -दुस्फल;

	अगर (value > U16_MAX)
		वापस -दुस्फल;

	mutex_lock(&isl29501->lock);
	अगर (reg->msb) अणु
		ret = i2c_smbus_ग_लिखो_byte_data(isl29501->client,
						reg->msb, value >> 8);
		अगर (ret < 0)
			जाओ err;
	पूर्ण

	ret = i2c_smbus_ग_लिखो_byte_data(isl29501->client, reg->lsb, value);

err:
	mutex_unlock(&isl29501->lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार isl29501_पढ़ो_ext(काष्ठा iio_dev *indio_dev,
				 uपूर्णांकptr_t निजी,
				 स्थिर काष्ठा iio_chan_spec *chan,
				 अक्षर *buf)
अणु
	काष्ठा isl29501_निजी *isl29501 = iio_priv(indio_dev);
	क्रमागत isl29501_रेजिस्टर_name reg = निजी;
	पूर्णांक ret;
	u32 value, gain, coeff, exp;

	चयन (reg) अणु
	हाल REG_GAIN:
	हाल REG_GAIN_BIAS:
		ret = isl29501_रेजिस्टर_पढ़ो(isl29501, reg, &gain);
		अगर (ret < 0)
			वापस ret;

		value = gain;
		अवरोध;
	हाल REG_CALIB_PHASE_TEMP_A:
	हाल REG_CALIB_PHASE_TEMP_B:
	हाल REG_CALIB_PHASE_LIGHT_A:
	हाल REG_CALIB_PHASE_LIGHT_B:
		ret = isl29501_रेजिस्टर_पढ़ो(isl29501, REG_PHASE_EXP, &exp);
		अगर (ret < 0)
			वापस ret;

		ret = isl29501_रेजिस्टर_पढ़ो(isl29501, reg, &coeff);
		अगर (ret < 0)
			वापस ret;

		value = coeff << exp;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस प्र_लिखो(buf, "%u\n", value);
पूर्ण

अटल पूर्णांक isl29501_set_shaकरोw_coeff(काष्ठा isl29501_निजी *isl29501,
				     क्रमागत isl29501_रेजिस्टर_name reg,
				     अचिन्हित पूर्णांक val)
अणु
	क्रमागत isl29501_correction_coeff coeff;

	चयन (reg) अणु
	हाल REG_CALIB_PHASE_TEMP_A:
		coeff = COEFF_TEMP_A;
		अवरोध;
	हाल REG_CALIB_PHASE_TEMP_B:
		coeff = COEFF_TEMP_B;
		अवरोध;
	हाल REG_CALIB_PHASE_LIGHT_A:
		coeff = COEFF_LIGHT_A;
		अवरोध;
	हाल REG_CALIB_PHASE_LIGHT_B:
		coeff = COEFF_LIGHT_B;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	isl29501->shaकरोw_coeffs[coeff] = val;

	वापस 0;
पूर्ण

अटल पूर्णांक isl29501_ग_लिखो_coeff(काष्ठा isl29501_निजी *isl29501,
				क्रमागत isl29501_correction_coeff coeff,
				पूर्णांक val)
अणु
	क्रमागत isl29501_रेजिस्टर_name reg;

	चयन (coeff) अणु
	हाल COEFF_TEMP_A:
		reg = REG_CALIB_PHASE_TEMP_A;
		अवरोध;
	हाल COEFF_TEMP_B:
		reg = REG_CALIB_PHASE_TEMP_B;
		अवरोध;
	हाल COEFF_LIGHT_A:
		reg = REG_CALIB_PHASE_LIGHT_A;
		अवरोध;
	हाल COEFF_LIGHT_B:
		reg = REG_CALIB_PHASE_LIGHT_B;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस isl29501_रेजिस्टर_ग_लिखो(isl29501, reg, val);
पूर्ण

अटल अचिन्हित पूर्णांक isl29501_find_corr_exp(अचिन्हित पूर्णांक val,
					   अचिन्हित पूर्णांक max_exp,
					   अचिन्हित पूर्णांक max_mantissa)
अणु
	अचिन्हित पूर्णांक exp = 1;

	/*
	 * Correction coefficients are represented under
	 * mantissa * 2^exponent क्रमm, where mantissa and exponent
	 * are stored in two separate रेजिस्टरs of the sensor.
	 *
	 * Compute and वापस the lowest exponent such as:
	 *	     mantissa = value / 2^exponent
	 *
	 *  where mantissa < max_mantissa.
	 */
	अगर (val <= max_mantissa)
		वापस 0;

	जबतक ((val >> exp) > max_mantissa) अणु
		exp++;

		अगर (exp > max_exp)
			वापस max_exp;
	पूर्ण

	वापस exp;
पूर्ण

अटल sमाप_प्रकार isl29501_ग_लिखो_ext(काष्ठा iio_dev *indio_dev,
				  uपूर्णांकptr_t निजी,
				  स्थिर काष्ठा iio_chan_spec *chan,
				  स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा isl29501_निजी *isl29501 = iio_priv(indio_dev);
	क्रमागत isl29501_रेजिस्टर_name reg = निजी;
	अचिन्हित पूर्णांक val;
	पूर्णांक max_exp = 0;
	पूर्णांक ret;
	पूर्णांक i;

	ret = kstrtouपूर्णांक(buf, 10, &val);
	अगर (ret)
		वापस ret;

	चयन (reg) अणु
	हाल REG_GAIN_BIAS:
		अगर (val > U16_MAX)
			वापस -दुस्फल;

		ret = isl29501_रेजिस्टर_ग_लिखो(isl29501, reg, val);
		अगर (ret < 0)
			वापस ret;

		अवरोध;
	हाल REG_CALIB_PHASE_TEMP_A:
	हाल REG_CALIB_PHASE_TEMP_B:
	हाल REG_CALIB_PHASE_LIGHT_A:
	हाल REG_CALIB_PHASE_LIGHT_B:

		अगर (val > (U8_MAX << ISL29501_MAX_EXP_VAL))
			वापस -दुस्फल;

		/* Store the correction coefficient under its exact क्रमm. */
		ret = isl29501_set_shaकरोw_coeff(isl29501, reg, val);
		अगर (ret < 0)
			वापस ret;

		/*
		 * Find the highest exponent needed to represent
		 * correction coefficients.
		 */
		क्रम (i = 0; i < COEFF_MAX; i++) अणु
			पूर्णांक corr;
			पूर्णांक corr_exp;

			corr = isl29501->shaकरोw_coeffs[i];
			corr_exp = isl29501_find_corr_exp(corr,
							  ISL29501_MAX_EXP_VAL,
							  U8_MAX / 2);
			dev_dbg(&isl29501->client->dev,
				"found exp of corr(%d) = %d\n", corr, corr_exp);

			max_exp = max(max_exp, corr_exp);
		पूर्ण

		/*
		 * Represent every correction coefficient under
		 * mantissa * 2^max_exponent क्रमm and क्रमce the
		 * writing of those coefficients on the sensor.
		 */
		क्रम (i = 0; i < COEFF_MAX; i++) अणु
			पूर्णांक corr;
			पूर्णांक mantissa;

			corr = isl29501->shaकरोw_coeffs[i];
			अगर (!corr)
				जारी;

			mantissa = corr >> max_exp;

			ret = isl29501_ग_लिखो_coeff(isl29501, i, mantissa);
			अगर (ret < 0)
				वापस ret;
		पूर्ण

		ret = isl29501_रेजिस्टर_ग_लिखो(isl29501, REG_PHASE_EXP, max_exp);
		अगर (ret < 0)
			वापस ret;

		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस len;
पूर्ण

#घोषणा _ISL29501_EXT_INFO(_name, _ident) अणु \
	.name = _name, \
	.पढ़ो = isl29501_पढ़ो_ext, \
	.ग_लिखो = isl29501_ग_लिखो_ext, \
	.निजी = _ident, \
	.shared = IIO_SEPARATE, \
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec_ext_info isl29501_ext_info[] = अणु
	_ISL29501_EXT_INFO("agc_gain", REG_GAIN),
	_ISL29501_EXT_INFO("agc_gain_bias", REG_GAIN_BIAS),
	_ISL29501_EXT_INFO("calib_phase_temp_a", REG_CALIB_PHASE_TEMP_A),
	_ISL29501_EXT_INFO("calib_phase_temp_b", REG_CALIB_PHASE_TEMP_B),
	_ISL29501_EXT_INFO("calib_phase_light_a", REG_CALIB_PHASE_LIGHT_A),
	_ISL29501_EXT_INFO("calib_phase_light_b", REG_CALIB_PHASE_LIGHT_B),
	अणु पूर्ण,
पूर्ण;

#घोषणा ISL29501_DISTANCE_SCAN_INDEX 0
#घोषणा ISL29501_TIMESTAMP_SCAN_INDEX 1

अटल स्थिर काष्ठा iio_chan_spec isl29501_channels[] = अणु
	अणु
		.type = IIO_PROXIMITY,
		.scan_index = ISL29501_DISTANCE_SCAN_INDEX,
		.info_mask_separate =
			BIT(IIO_CHAN_INFO_RAW)   |
			BIT(IIO_CHAN_INFO_SCALE) |
			BIT(IIO_CHAN_INFO_CALIBBIAS),
		.scan_type = अणु
			.sign = 'u',
			.realbits = 16,
			.storagebits = 16,
			.endianness = IIO_CPU,
		पूर्ण,
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_INT_TIME) |
				BIT(IIO_CHAN_INFO_SAMP_FREQ),
		.ext_info = isl29501_ext_info,
	पूर्ण,
	अणु
		.type = IIO_PHASE,
		.scan_index = -1,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				BIT(IIO_CHAN_INFO_SCALE),
	पूर्ण,
	अणु
		.type = IIO_CURRENT,
		.scan_index = -1,
		.output = 1,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				BIT(IIO_CHAN_INFO_SCALE),
	पूर्ण,
	अणु
		.type = IIO_TEMP,
		.scan_index = -1,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				BIT(IIO_CHAN_INFO_SCALE)     |
				BIT(IIO_CHAN_INFO_CALIBBIAS),
	पूर्ण,
	अणु
		.type = IIO_INTENSITY,
		.scan_index = -1,
		.modअगरied = 1,
		.channel2 = IIO_MOD_LIGHT_CLEAR,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				BIT(IIO_CHAN_INFO_SCALE),
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(ISL29501_TIMESTAMP_SCAN_INDEX),
पूर्ण;

अटल पूर्णांक isl29501_reset_रेजिस्टरs(काष्ठा isl29501_निजी *isl29501)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(isl29501->client,
					ISL29501_COMMAND_REGISTER,
					ISL29501_RESET_ALL_REGISTERS);
	अगर (ret < 0) अणु
		dev_err(&isl29501->client->dev,
			"cannot reset registers %d\n", ret);
		वापस ret;
	पूर्ण

	ret = i2c_smbus_ग_लिखो_byte_data(isl29501->client,
					ISL29501_COMMAND_REGISTER,
					ISL29501_RESET_INT_SM);
	अगर (ret < 0)
		dev_err(&isl29501->client->dev,
			"cannot reset state machine %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक isl29501_begin_acquisition(काष्ठा isl29501_निजी *isl29501)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(isl29501->client,
					ISL29501_COMMAND_REGISTER,
					ISL29501_EMUL_SAMPLE_START_PIN);
	अगर (ret < 0)
		dev_err(&isl29501->client->dev,
			"cannot begin acquisition %d\n", ret);

	वापस ret;
पूर्ण

अटल IIO_CONST_ATTR_INT_TIME_AVAIL(ISL29501_INT_TIME_AVAILABLE);
अटल IIO_CONST_ATTR(out_current_scale_available,
		      ISL29501_CURRENT_SCALE_AVAILABLE);

अटल काष्ठा attribute *isl29501_attributes[] = अणु
	&iio_स्थिर_attr_पूर्णांकegration_समय_available.dev_attr.attr,
	&iio_स्थिर_attr_out_current_scale_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group isl29501_attribute_group = अणु
	.attrs = isl29501_attributes,
पूर्ण;

अटल स्थिर पूर्णांक isl29501_current_scale_table[][2] = अणु
	अणु0, 3900पूर्ण, अणु0, 7800पूर्ण, अणु0, 11800पूर्ण, अणु0, 15700पूर्ण,
	अणु0, 19600पूर्ण, अणु0, 23500पूर्ण, अणु0, 27500पूर्ण, अणु0, 31400पूर्ण,
	अणु0, 35200पूर्ण, अणु0, 39200पूर्ण, अणु0, 43100पूर्ण, अणु0, 47100पूर्ण,
	अणु0, 51000पूर्ण, अणु0, 54900पूर्ण, अणु0, 58800पूर्ण,
पूर्ण;

अटल स्थिर पूर्णांक isl29501_पूर्णांक_समय[][2] = अणु
	अणु0, 70पूर्ण,    /* 0.07 ms */
	अणु0, 140पूर्ण,   /* 0.14 ms */
	अणु0, 280पूर्ण,   /* 0.28 ms */
	अणु0, 570पूर्ण,   /* 0.57 ms */
	अणु0, 1140पूर्ण,  /* 1.14 ms */
	अणु0, 2280पूर्ण,  /* 2.28 ms */
	अणु0, 4550पूर्ण,  /* 4.55 ms */
	अणु0, 9100पूर्ण,  /* 9.11 ms */
	अणु0, 18200पूर्ण, /* 18.2 ms */
	अणु0, 36400पूर्ण, /* 36.4 ms */
	अणु0, 72810पूर्ण, /* 72.81 ms */
	अणु0, 145610पूर्ण /* 145.28 ms */
पूर्ण;

अटल पूर्णांक isl29501_get_raw(काष्ठा isl29501_निजी *isl29501,
			    स्थिर काष्ठा iio_chan_spec *chan,
			    पूर्णांक *raw)
अणु
	पूर्णांक ret;

	चयन (chan->type) अणु
	हाल IIO_PROXIMITY:
		ret = isl29501_रेजिस्टर_पढ़ो(isl29501, REG_DISTANCE, raw);
		अगर (ret < 0)
			वापस ret;

		वापस IIO_VAL_INT;
	हाल IIO_INTENSITY:
		ret = isl29501_रेजिस्टर_पढ़ो(isl29501,
					     REG_AMBIENT_LIGHT,
					     raw);
		अगर (ret < 0)
			वापस ret;

		वापस IIO_VAL_INT;
	हाल IIO_PHASE:
		ret = isl29501_रेजिस्टर_पढ़ो(isl29501, REG_PHASE, raw);
		अगर (ret < 0)
			वापस ret;

		वापस IIO_VAL_INT;
	हाल IIO_CURRENT:
		ret = isl29501_रेजिस्टर_पढ़ो(isl29501, REG_EMITTER_DAC, raw);
		अगर (ret < 0)
			वापस ret;

		वापस IIO_VAL_INT;
	हाल IIO_TEMP:
		ret = isl29501_रेजिस्टर_पढ़ो(isl29501, REG_TEMPERATURE, raw);
		अगर (ret < 0)
			वापस ret;

		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक isl29501_get_scale(काष्ठा isl29501_निजी *isl29501,
			      स्थिर काष्ठा iio_chan_spec *chan,
			      पूर्णांक *val, पूर्णांक *val2)
अणु
	पूर्णांक ret;
	u32 current_scale;

	चयन (chan->type) अणु
	हाल IIO_PROXIMITY:
		/* distance = raw_distance * 33.31 / 65536 (m) */
		*val = 3331;
		*val2 = 6553600;

		वापस IIO_VAL_FRACTIONAL;
	हाल IIO_PHASE:
		/* phase = raw_phase * 2pi / 65536 (rad) */
		*val = 0;
		*val2 = 95874;

		वापस IIO_VAL_INT_PLUS_न_अंकO;
	हाल IIO_INTENSITY:
		/* light = raw_light * 35 / 10000 (mA) */
		*val = 35;
		*val2 = 10000;

		वापस IIO_VAL_FRACTIONAL;
	हाल IIO_CURRENT:
		ret = isl29501_रेजिस्टर_पढ़ो(isl29501,
					     REG_DRIVER_RANGE,
					     &current_scale);
		अगर (ret < 0)
			वापस ret;

		अगर (current_scale > ARRAY_SIZE(isl29501_current_scale_table))
			वापस -EINVAL;

		अगर (!current_scale) अणु
			*val = 0;
			*val2 = 0;
			वापस IIO_VAL_INT;
		पूर्ण

		*val = isl29501_current_scale_table[current_scale - 1][0];
		*val2 = isl29501_current_scale_table[current_scale - 1][1];

		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_TEMP:
		/* temperature = raw_temperature * 125 / 100000 (milli तओC) */
		*val = 125;
		*val2 = 100000;

		वापस IIO_VAL_FRACTIONAL;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक isl29501_get_calibbias(काष्ठा isl29501_निजी *isl29501,
				  स्थिर काष्ठा iio_chan_spec *chan,
				  पूर्णांक *bias)
अणु
	चयन (chan->type) अणु
	हाल IIO_PROXIMITY:
		वापस isl29501_रेजिस्टर_पढ़ो(isl29501,
					      REG_DISTANCE_BIAS,
					      bias);
	हाल IIO_TEMP:
		वापस isl29501_रेजिस्टर_पढ़ो(isl29501,
					      REG_TEMPERATURE_BIAS,
					      bias);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक isl29501_get_पूर्णांकसमय(काष्ठा isl29501_निजी *isl29501,
				पूर्णांक *val, पूर्णांक *val2)
अणु
	पूर्णांक ret;
	u32 पूर्णांकसमय;

	ret = isl29501_रेजिस्टर_पढ़ो(isl29501, REG_INT_TIME, &पूर्णांकसमय);
	अगर (ret < 0)
		वापस ret;

	अगर (पूर्णांकसमय >= ARRAY_SIZE(isl29501_पूर्णांक_समय))
		वापस -EINVAL;

	*val = isl29501_पूर्णांक_समय[पूर्णांकसमय][0];
	*val2 = isl29501_पूर्णांक_समय[पूर्णांकसमय][1];

	वापस IIO_VAL_INT_PLUS_MICRO;
पूर्ण

अटल पूर्णांक isl29501_get_freq(काष्ठा isl29501_निजी *isl29501,
			     पूर्णांक *val, पूर्णांक *val2)
अणु
	पूर्णांक ret;
	पूर्णांक sample_समय;
	अचिन्हित दीर्घ दीर्घ freq;
	u32 temp;

	ret = isl29501_रेजिस्टर_पढ़ो(isl29501, REG_SAMPLE_TIME, &sample_समय);
	अगर (ret < 0)
		वापस ret;

	/* freq = 1 / (0.000450 * (sample_समय + 1) * 10^-6) */
	freq = 1000000ULL * 1000000ULL;

	करो_भाग(freq, 450 * (sample_समय + 1));

	temp = करो_भाग(freq, 1000000);
	*val = freq;
	*val2 = temp;

	वापस IIO_VAL_INT_PLUS_MICRO;
पूर्ण

अटल पूर्णांक isl29501_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
			     पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा isl29501_निजी *isl29501 = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		वापस isl29501_get_raw(isl29501, chan, val);
	हाल IIO_CHAN_INFO_SCALE:
		वापस isl29501_get_scale(isl29501, chan, val, val2);
	हाल IIO_CHAN_INFO_INT_TIME:
		वापस isl29501_get_पूर्णांकसमय(isl29501, val, val2);
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		वापस isl29501_get_freq(isl29501, val, val2);
	हाल IIO_CHAN_INFO_CALIBBIAS:
		वापस isl29501_get_calibbias(isl29501, chan, val);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक isl29501_set_raw(काष्ठा isl29501_निजी *isl29501,
			    स्थिर काष्ठा iio_chan_spec *chan,
			    पूर्णांक raw)
अणु
	चयन (chan->type) अणु
	हाल IIO_CURRENT:
		वापस isl29501_रेजिस्टर_ग_लिखो(isl29501, REG_EMITTER_DAC, raw);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक isl29501_set_पूर्णांकसमय(काष्ठा isl29501_निजी *isl29501,
				पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(isl29501_पूर्णांक_समय); i++) अणु
		अगर (isl29501_पूर्णांक_समय[i][0] == val &&
		    isl29501_पूर्णांक_समय[i][1] == val2) अणु
			वापस isl29501_रेजिस्टर_ग_लिखो(isl29501,
						       REG_INT_TIME,
						       i);
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक isl29501_set_scale(काष्ठा isl29501_निजी *isl29501,
			      स्थिर काष्ठा iio_chan_spec *chan,
			      पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक i;

	अगर (chan->type != IIO_CURRENT)
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(isl29501_current_scale_table); i++) अणु
		अगर (isl29501_current_scale_table[i][0] == val &&
		    isl29501_current_scale_table[i][1] == val2) अणु
			वापस isl29501_रेजिस्टर_ग_लिखो(isl29501,
						       REG_DRIVER_RANGE,
						       i + 1);
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक isl29501_set_calibbias(काष्ठा isl29501_निजी *isl29501,
				  स्थिर काष्ठा iio_chan_spec *chan,
				  पूर्णांक bias)
अणु
	चयन (chan->type) अणु
	हाल IIO_PROXIMITY:
		वापस isl29501_रेजिस्टर_ग_लिखो(isl29501,
					      REG_DISTANCE_BIAS,
					      bias);
	हाल IIO_TEMP:
		वापस isl29501_रेजिस्टर_ग_लिखो(isl29501,
					       REG_TEMPERATURE_BIAS,
					       bias);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक isl29501_set_freq(काष्ठा isl29501_निजी *isl29501,
			     पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक freq;
	अचिन्हित दीर्घ दीर्घ sample_समय;

	/* sample_freq = 1 / (0.000450 * (sample_समय + 1) * 10^-6) */
	freq = val * 1000000 + val2 % 1000000;
	sample_समय = 2222ULL * 1000000ULL;
	करो_भाग(sample_समय, freq);

	sample_समय -= 1;

	अगर (sample_समय > 255)
		वापस -दुस्फल;

	वापस isl29501_रेजिस्टर_ग_लिखो(isl29501, REG_SAMPLE_TIME, sample_समय);
पूर्ण

अटल पूर्णांक isl29501_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan,
			      पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा isl29501_निजी *isl29501 = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		वापस isl29501_set_raw(isl29501, chan, val);
	हाल IIO_CHAN_INFO_INT_TIME:
		वापस isl29501_set_पूर्णांकसमय(isl29501, val, val2);
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		वापस isl29501_set_freq(isl29501, val, val2);
	हाल IIO_CHAN_INFO_SCALE:
		वापस isl29501_set_scale(isl29501, chan, val, val2);
	हाल IIO_CHAN_INFO_CALIBBIAS:
		वापस isl29501_set_calibbias(isl29501, chan, val);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info isl29501_info = अणु
	.पढ़ो_raw = &isl29501_पढ़ो_raw,
	.ग_लिखो_raw = &isl29501_ग_लिखो_raw,
	.attrs = &isl29501_attribute_group,
पूर्ण;

अटल पूर्णांक isl29501_init_chip(काष्ठा isl29501_निजी *isl29501)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(isl29501->client, ISL29501_DEVICE_ID);
	अगर (ret < 0) अणु
		dev_err(&isl29501->client->dev, "Error reading device id\n");
		वापस ret;
	पूर्ण

	अगर (ret != ISL29501_ID) अणु
		dev_err(&isl29501->client->dev,
			"Wrong chip id, got %x expected %x\n",
			ret, ISL29501_DEVICE_ID);
		वापस -ENODEV;
	पूर्ण

	ret = isl29501_reset_रेजिस्टरs(isl29501);
	अगर (ret < 0)
		वापस ret;

	वापस isl29501_begin_acquisition(isl29501);
पूर्ण

अटल irqवापस_t isl29501_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा isl29501_निजी *isl29501 = iio_priv(indio_dev);
	स्थिर अचिन्हित दीर्घ *active_mask = indio_dev->active_scan_mask;
	u32 buffer[4] = अणुपूर्ण; /* 1x16-bit + ts */

	अगर (test_bit(ISL29501_DISTANCE_SCAN_INDEX, active_mask))
		isl29501_रेजिस्टर_पढ़ो(isl29501, REG_DISTANCE, buffer);

	iio_push_to_buffers_with_बारtamp(indio_dev, buffer, pf->बारtamp);
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक isl29501_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा isl29501_निजी *isl29501;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*isl29501));
	अगर (!indio_dev)
		वापस -ENOMEM;

	isl29501 = iio_priv(indio_dev);

	i2c_set_clientdata(client, indio_dev);
	isl29501->client = client;

	mutex_init(&isl29501->lock);

	ret = isl29501_init_chip(isl29501);
	अगर (ret < 0)
		वापस ret;

	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = isl29501_channels;
	indio_dev->num_channels = ARRAY_SIZE(isl29501_channels);
	indio_dev->name = client->name;
	indio_dev->info = &isl29501_info;

	ret = devm_iio_triggered_buffer_setup(&client->dev, indio_dev,
					      iio_pollfunc_store_समय,
					      isl29501_trigger_handler,
					      शून्य);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "unable to setup iio triggered buffer\n");
		वापस ret;
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id isl29501_id[] = अणु
	अणु"isl29501", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, isl29501_id);

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id isl29501_i2c_matches[] = अणु
	अणु .compatible = "renesas,isl29501" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, isl29501_i2c_matches);
#पूर्ण_अगर

अटल काष्ठा i2c_driver isl29501_driver = अणु
	.driver = अणु
		.name	= "isl29501",
	पूर्ण,
	.id_table	= isl29501_id,
	.probe		= isl29501_probe,
पूर्ण;
module_i2c_driver(isl29501_driver);

MODULE_AUTHOR("Mathieu Othacehe <m.othacehe@gmail.com>");
MODULE_DESCRIPTION("ISL29501 Time of Flight sensor driver");
MODULE_LICENSE("GPL v2");
