<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Support क्रम AMS AS73211 JENCOLOR(R) Digital XYZ Sensor
 *
 * Author: Christian Eggers <ceggers@arri.de>
 *
 * Copyright (c) 2020 ARRI Lighting
 *
 * Color light sensor with 16-bit channels क्रम x, y, z and temperature);
 * 7-bit I2C slave address 0x74 .. 0x77.
 *
 * Datasheet: https://ams.com/करोcuments/20143/36005/AS73211_DS000556_3-01.pdf
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pm.h>

#घोषणा HZ_PER_KHZ 1000

#घोषणा AS73211_DRV_NAME "as73211"

/* AS73211 configuration रेजिस्टरs */
#घोषणा AS73211_REG_OSR    0x0
#घोषणा AS73211_REG_AGEN   0x2
#घोषणा AS73211_REG_CREG1  0x6
#घोषणा AS73211_REG_CREG2  0x7
#घोषणा AS73211_REG_CREG3  0x8

/* AS73211 output रेजिस्टर bank */
#घोषणा AS73211_OUT_OSR_STATUS    0
#घोषणा AS73211_OUT_TEMP          1
#घोषणा AS73211_OUT_MRES1         2
#घोषणा AS73211_OUT_MRES2         3
#घोषणा AS73211_OUT_MRES3         4

#घोषणा AS73211_OSR_SS            BIT(7)
#घोषणा AS73211_OSR_PD            BIT(6)
#घोषणा AS73211_OSR_SW_RES        BIT(3)
#घोषणा AS73211_OSR_DOS_MASK      GENMASK(2, 0)
#घोषणा AS73211_OSR_DOS_CONFIG    FIELD_PREP(AS73211_OSR_DOS_MASK, 0x2)
#घोषणा AS73211_OSR_DOS_MEASURE   FIELD_PREP(AS73211_OSR_DOS_MASK, 0x3)

#घोषणा AS73211_AGEN_DEVID_MASK   GENMASK(7, 4)
#घोषणा AS73211_AGEN_DEVID(x)     FIELD_PREP(AS73211_AGEN_DEVID_MASK, (x))
#घोषणा AS73211_AGEN_MUT_MASK     GENMASK(3, 0)
#घोषणा AS73211_AGEN_MUT(x)       FIELD_PREP(AS73211_AGEN_MUT_MASK, (x))

#घोषणा AS73211_CREG1_GAIN_MASK   GENMASK(7, 4)
#घोषणा AS73211_CREG1_GAIN_1      11
#घोषणा AS73211_CREG1_TIME_MASK   GENMASK(3, 0)

#घोषणा AS73211_CREG3_CCLK_MASK   GENMASK(1, 0)

#घोषणा AS73211_OSR_STATUS_OUTCONVOF  BIT(15)
#घोषणा AS73211_OSR_STATUS_MRESOF     BIT(14)
#घोषणा AS73211_OSR_STATUS_ADCOF      BIT(13)
#घोषणा AS73211_OSR_STATUS_LDATA      BIT(12)
#घोषणा AS73211_OSR_STATUS_NDATA      BIT(11)
#घोषणा AS73211_OSR_STATUS_NOTREADY   BIT(10)

#घोषणा AS73211_SAMPLE_FREQ_BASE      1024000

#घोषणा AS73211_SAMPLE_TIME_NUM       15
#घोषणा AS73211_SAMPLE_TIME_MAX_MS    BIT(AS73211_SAMPLE_TIME_NUM - 1)

/* Available sample frequencies are 1.024MHz multiplied by घातers of two. */
अटल स्थिर पूर्णांक as73211_samp_freq_avail[] = अणु
	AS73211_SAMPLE_FREQ_BASE * 1,
	AS73211_SAMPLE_FREQ_BASE * 2,
	AS73211_SAMPLE_FREQ_BASE * 4,
	AS73211_SAMPLE_FREQ_BASE * 8,
पूर्ण;

अटल स्थिर पूर्णांक as73211_hardwaregain_avail[] = अणु
	1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048,
पूर्ण;

/**
 * काष्ठा as73211_data - Instance data क्रम one AS73211
 * @client: I2C client.
 * @osr:    Cached Operational State Register.
 * @creg1:  Cached Configuration Register 1.
 * @creg2:  Cached Configuration Register 2.
 * @creg3:  Cached Configuration Register 3.
 * @mutex:  Keeps cached रेजिस्टरs in sync with the device.
 * @completion: Completion to रुको क्रम पूर्णांकerrupt.
 * @पूर्णांक_समय_avail: Available पूर्णांकegration बार (depend on sampling frequency).
 */
काष्ठा as73211_data अणु
	काष्ठा i2c_client *client;
	u8 osr;
	u8 creg1;
	u8 creg2;
	u8 creg3;
	काष्ठा mutex mutex;
	काष्ठा completion completion;
	पूर्णांक पूर्णांक_समय_avail[AS73211_SAMPLE_TIME_NUM * 2];
पूर्ण;

#घोषणा AS73211_COLOR_CHANNEL(_color, _si, _addr) अणु \
	.type = IIO_INTENSITY, \
	.modअगरied = 1, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE), \
	.info_mask_shared_by_type = \
		BIT(IIO_CHAN_INFO_SAMP_FREQ) | \
		BIT(IIO_CHAN_INFO_HARDWAREGAIN) | \
		BIT(IIO_CHAN_INFO_INT_TIME), \
	.info_mask_shared_by_type_available = \
		BIT(IIO_CHAN_INFO_SAMP_FREQ) | \
		BIT(IIO_CHAN_INFO_HARDWAREGAIN) | \
		BIT(IIO_CHAN_INFO_INT_TIME), \
	.channel2 = IIO_MOD_##_color, \
	.address = _addr, \
	.scan_index = _si, \
	.scan_type = अणु \
		.sign = 'u', \
		.realbits = 16, \
		.storagebits = 16, \
		.endianness = IIO_LE, \
	पूर्ण, \
पूर्ण

#घोषणा AS73211_OFFSET_TEMP_INT    (-66)
#घोषणा AS73211_OFFSET_TEMP_MICRO  900000
#घोषणा AS73211_SCALE_TEMP_INT     0
#घोषणा AS73211_SCALE_TEMP_MICRO   50000

#घोषणा AS73211_SCALE_X 277071108  /* nW/m^2 */
#घोषणा AS73211_SCALE_Y 298384270  /* nW/m^2 */
#घोषणा AS73211_SCALE_Z 160241927  /* nW/m^2 */

/* Channel order MUST match devices result रेजिस्टर order */
#घोषणा AS73211_SCAN_INDEX_TEMP 0
#घोषणा AS73211_SCAN_INDEX_X    1
#घोषणा AS73211_SCAN_INDEX_Y    2
#घोषणा AS73211_SCAN_INDEX_Z    3
#घोषणा AS73211_SCAN_INDEX_TS   4

#घोषणा AS73211_SCAN_MASK_COLOR ( \
	BIT(AS73211_SCAN_INDEX_X) |   \
	BIT(AS73211_SCAN_INDEX_Y) |   \
	BIT(AS73211_SCAN_INDEX_Z))

#घोषणा AS73211_SCAN_MASK_ALL (    \
	BIT(AS73211_SCAN_INDEX_TEMP) | \
	AS73211_SCAN_MASK_COLOR)

अटल स्थिर काष्ठा iio_chan_spec as73211_channels[] = अणु
	अणु
		.type = IIO_TEMP,
		.info_mask_separate =
			BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_OFFSET) |
			BIT(IIO_CHAN_INFO_SCALE),
		.address = AS73211_OUT_TEMP,
		.scan_index = AS73211_SCAN_INDEX_TEMP,
		.scan_type = अणु
			.sign = 'u',
			.realbits = 16,
			.storagebits = 16,
			.endianness = IIO_LE,
		पूर्ण
	पूर्ण,
	AS73211_COLOR_CHANNEL(X, AS73211_SCAN_INDEX_X, AS73211_OUT_MRES1),
	AS73211_COLOR_CHANNEL(Y, AS73211_SCAN_INDEX_Y, AS73211_OUT_MRES2),
	AS73211_COLOR_CHANNEL(Z, AS73211_SCAN_INDEX_Z, AS73211_OUT_MRES3),
	IIO_CHAN_SOFT_TIMESTAMP(AS73211_SCAN_INDEX_TS),
पूर्ण;

अटल अचिन्हित पूर्णांक as73211_पूर्णांकegration_समय_1024cyc(काष्ठा as73211_data *data)
अणु
	/*
	 * Return पूर्णांकegration समय in units of 1024 घड़ी cycles. Integration समय
	 * in CREG1 is in घातers of 2 (x 1024 cycles).
	 */
	वापस BIT(FIELD_GET(AS73211_CREG1_TIME_MASK, data->creg1));
पूर्ण

अटल अचिन्हित पूर्णांक as73211_पूर्णांकegration_समय_us(काष्ठा as73211_data *data,
						 अचिन्हित पूर्णांक पूर्णांकegration_समय_1024cyc)
अणु
	/*
	 * f_samp is configured in CREG3 in घातers of 2 (x 1.024 MHz)
	 * t_cycl is configured in CREG1 in घातers of 2 (x 1024 cycles)
	 * t_पूर्णांक_us = 1 / (f_samp) * t_cycl * US_PER_SEC
	 *          = 1 / (2^CREG3_CCLK * 1,024,000) * 2^CREG1_CYCLES * 1,024 * US_PER_SEC
	 *          = 2^(-CREG3_CCLK) * 2^CREG1_CYCLES * 1,000
	 * In order to get rid of negative exponents, we extend the "fraction"
	 * by 2^3 (CREG3_CCLK,max = 3)
	 * t_पूर्णांक_us = 2^(3-CREG3_CCLK) * 2^CREG1_CYCLES * 125
	 */
	वापस BIT(3 - FIELD_GET(AS73211_CREG3_CCLK_MASK, data->creg3)) *
		पूर्णांकegration_समय_1024cyc * 125;
पूर्ण

अटल व्योम as73211_पूर्णांकegration_समय_calc_avail(काष्ठा as73211_data *data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(data->पूर्णांक_समय_avail) / 2; i++) अणु
		अचिन्हित पूर्णांक समय_us = as73211_पूर्णांकegration_समय_us(data, BIT(i));

		data->पूर्णांक_समय_avail[i * 2 + 0] = समय_us / USEC_PER_SEC;
		data->पूर्णांक_समय_avail[i * 2 + 1] = समय_us % USEC_PER_SEC;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक as73211_gain(काष्ठा as73211_data *data)
अणु
	/* gain can be calculated from CREG1 as 2^(11 - CREG1_GAIN) */
	वापस BIT(AS73211_CREG1_GAIN_1 - FIELD_GET(AS73211_CREG1_GAIN_MASK, data->creg1));
पूर्ण

/* must be called with as73211_data::mutex held. */
अटल पूर्णांक as73211_req_data(काष्ठा as73211_data *data)
अणु
	अचिन्हित पूर्णांक समय_us = as73211_पूर्णांकegration_समय_us(data,
							    as73211_पूर्णांकegration_समय_1024cyc(data));
	काष्ठा device *dev = &data->client->dev;
	जोड़ i2c_smbus_data smbus_data;
	u16 osr_status;
	पूर्णांक ret;

	अगर (data->client->irq)
		reinit_completion(&data->completion);

	/*
	 * During measurement, there should be no traffic on the i2c bus as the
	 * electrical noise would disturb the measurement process.
	 */
	i2c_lock_bus(data->client->adapter, I2C_LOCK_SEGMENT);

	data->osr &= ~AS73211_OSR_DOS_MASK;
	data->osr |= AS73211_OSR_DOS_MEASURE | AS73211_OSR_SS;

	smbus_data.byte = data->osr;
	ret = __i2c_smbus_xfer(data->client->adapter, data->client->addr,
			data->client->flags, I2C_SMBUS_WRITE,
			AS73211_REG_OSR, I2C_SMBUS_BYTE_DATA, &smbus_data);
	अगर (ret < 0) अणु
		i2c_unlock_bus(data->client->adapter, I2C_LOCK_SEGMENT);
		वापस ret;
	पूर्ण

	/*
	 * Reset AS73211_OSR_SS (is self clearing) in order to aव्योम unपूर्णांकentional
	 * triggering of further measurements later.
	 */
	data->osr &= ~AS73211_OSR_SS;

	/*
	 * Add 33% extra margin क्रम the समयout. fclk,min = fclk,typ - 27%.
	 */
	समय_us += समय_us / 3;
	अगर (data->client->irq) अणु
		ret = रुको_क्रम_completion_समयout(&data->completion, usecs_to_jअगरfies(समय_us));
		अगर (!ret) अणु
			dev_err(dev, "timeout waiting for READY IRQ\n");
			i2c_unlock_bus(data->client->adapter, I2C_LOCK_SEGMENT);
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Wait पूर्णांकegration समय */
		usleep_range(समय_us, 2 * समय_us);
	पूर्ण

	i2c_unlock_bus(data->client->adapter, I2C_LOCK_SEGMENT);

	ret = i2c_smbus_पढ़ो_word_data(data->client, AS73211_OUT_OSR_STATUS);
	अगर (ret < 0)
		वापस ret;

	osr_status = ret;
	अगर (osr_status != (AS73211_OSR_DOS_MEASURE | AS73211_OSR_STATUS_NDATA)) अणु
		अगर (osr_status & AS73211_OSR_SS) अणु
			dev_err(dev, "%s() Measurement has not stopped\n", __func__);
			वापस -ETIME;
		पूर्ण
		अगर (osr_status & AS73211_OSR_STATUS_NOTREADY) अणु
			dev_err(dev, "%s() Data is not ready\n", __func__);
			वापस -ENODATA;
		पूर्ण
		अगर (!(osr_status & AS73211_OSR_STATUS_NDATA)) अणु
			dev_err(dev, "%s() No new data available\n", __func__);
			वापस -ENODATA;
		पूर्ण
		अगर (osr_status & AS73211_OSR_STATUS_LDATA) अणु
			dev_err(dev, "%s() Result buffer overrun\n", __func__);
			वापस -ENOBUFS;
		पूर्ण
		अगर (osr_status & AS73211_OSR_STATUS_ADCOF) अणु
			dev_err(dev, "%s() ADC overflow\n", __func__);
			वापस -EOVERFLOW;
		पूर्ण
		अगर (osr_status & AS73211_OSR_STATUS_MRESOF) अणु
			dev_err(dev, "%s() Measurement result overflow\n", __func__);
			वापस -EOVERFLOW;
		पूर्ण
		अगर (osr_status & AS73211_OSR_STATUS_OUTCONVOF) अणु
			dev_err(dev, "%s() Timer overflow\n", __func__);
			वापस -EOVERFLOW;
		पूर्ण
		dev_err(dev, "%s() Unexpected status value\n", __func__);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक as73211_पढ़ो_raw(काष्ठा iio_dev *indio_dev, काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा as73211_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW: अणु
		पूर्णांक ret;

		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret < 0)
			वापस ret;

		ret = as73211_req_data(data);
		अगर (ret < 0) अणु
			iio_device_release_direct_mode(indio_dev);
			वापस ret;
		पूर्ण

		ret = i2c_smbus_पढ़ो_word_data(data->client, chan->address);
		iio_device_release_direct_mode(indio_dev);
		अगर (ret < 0)
			वापस ret;

		*val = ret;
		वापस IIO_VAL_INT;
	पूर्ण
	हाल IIO_CHAN_INFO_OFFSET:
		*val = AS73211_OFFSET_TEMP_INT;
		*val2 = AS73211_OFFSET_TEMP_MICRO;
		वापस IIO_VAL_INT_PLUS_MICRO;

	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_TEMP:
			*val = AS73211_SCALE_TEMP_INT;
			*val2 = AS73211_SCALE_TEMP_MICRO;
			वापस IIO_VAL_INT_PLUS_MICRO;

		हाल IIO_INTENSITY: अणु
			अचिन्हित पूर्णांक scale;

			चयन (chan->channel2) अणु
			हाल IIO_MOD_X:
				scale = AS73211_SCALE_X;
				अवरोध;
			हाल IIO_MOD_Y:
				scale = AS73211_SCALE_Y;
				अवरोध;
			हाल IIO_MOD_Z:
				scale = AS73211_SCALE_Z;
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण
			scale /= as73211_gain(data);
			scale /= as73211_पूर्णांकegration_समय_1024cyc(data);
			*val = scale;
			वापस IIO_VAL_INT;

		शेष:
			वापस -EINVAL;
		पूर्णपूर्ण

	हाल IIO_CHAN_INFO_SAMP_FREQ:
		/* f_samp is configured in CREG3 in घातers of 2 (x 1.024 MHz) */
		*val = BIT(FIELD_GET(AS73211_CREG3_CCLK_MASK, data->creg3)) *
			AS73211_SAMPLE_FREQ_BASE;
		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_HARDWAREGAIN:
		*val = as73211_gain(data);
		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_INT_TIME: अणु
		अचिन्हित पूर्णांक समय_us;

		mutex_lock(&data->mutex);
		समय_us = as73211_पूर्णांकegration_समय_us(data, as73211_पूर्णांकegration_समय_1024cyc(data));
		mutex_unlock(&data->mutex);
		*val = समय_us / USEC_PER_SEC;
		*val2 = समय_us % USEC_PER_SEC;
		वापस IIO_VAL_INT_PLUS_MICRO;

	शेष:
		वापस -EINVAL;
	पूर्णपूर्ण
पूर्ण

अटल पूर्णांक as73211_पढ़ो_avail(काष्ठा iio_dev *indio_dev, काष्ठा iio_chan_spec स्थिर *chan,
			       स्थिर पूर्णांक **vals, पूर्णांक *type, पूर्णांक *length, दीर्घ mask)
अणु
	काष्ठा as73211_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*length = ARRAY_SIZE(as73211_samp_freq_avail);
		*vals = as73211_samp_freq_avail;
		*type = IIO_VAL_INT;
		वापस IIO_AVAIL_LIST;

	हाल IIO_CHAN_INFO_HARDWAREGAIN:
		*length = ARRAY_SIZE(as73211_hardwaregain_avail);
		*vals = as73211_hardwaregain_avail;
		*type = IIO_VAL_INT;
		वापस IIO_AVAIL_LIST;

	हाल IIO_CHAN_INFO_INT_TIME:
		*length = ARRAY_SIZE(data->पूर्णांक_समय_avail);
		*vals = data->पूर्णांक_समय_avail;
		*type = IIO_VAL_INT_PLUS_MICRO;
		वापस IIO_AVAIL_LIST;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक _as73211_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan __always_unused,
			       पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा as73211_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ: अणु
		पूर्णांक reg_bits, freq_kHz = val / HZ_PER_KHZ;  /* 1024, 2048, ... */

		/* val must be 1024 * 2^x */
		अगर (val < 0 || (freq_kHz * HZ_PER_KHZ) != val ||
				!is_घातer_of_2(freq_kHz) || val2)
			वापस -EINVAL;

		/* f_samp is configured in CREG3 in घातers of 2 (x 1.024 MHz (=2^10)) */
		reg_bits = ilog2(freq_kHz) - 10;
		अगर (!FIELD_FIT(AS73211_CREG3_CCLK_MASK, reg_bits))
			वापस -EINVAL;

		data->creg3 &= ~AS73211_CREG3_CCLK_MASK;
		data->creg3 |= FIELD_PREP(AS73211_CREG3_CCLK_MASK, reg_bits);
		as73211_पूर्णांकegration_समय_calc_avail(data);

		ret = i2c_smbus_ग_लिखो_byte_data(data->client, AS73211_REG_CREG3, data->creg3);
		अगर (ret < 0)
			वापस ret;

		वापस 0;
	पूर्ण
	हाल IIO_CHAN_INFO_HARDWAREGAIN: अणु
		अचिन्हित पूर्णांक reg_bits;

		अगर (val < 0 || !is_घातer_of_2(val) || val2)
			वापस -EINVAL;

		/* gain can be calculated from CREG1 as 2^(11 - CREG1_GAIN) */
		reg_bits = AS73211_CREG1_GAIN_1 - ilog2(val);
		अगर (!FIELD_FIT(AS73211_CREG1_GAIN_MASK, reg_bits))
			वापस -EINVAL;

		data->creg1 &= ~AS73211_CREG1_GAIN_MASK;
		data->creg1 |= FIELD_PREP(AS73211_CREG1_GAIN_MASK, reg_bits);

		ret = i2c_smbus_ग_लिखो_byte_data(data->client, AS73211_REG_CREG1, data->creg1);
		अगर (ret < 0)
			वापस ret;

		वापस 0;
	पूर्ण
	हाल IIO_CHAN_INFO_INT_TIME: अणु
		पूर्णांक val_us = val * USEC_PER_SEC + val2;
		पूर्णांक समय_ms;
		पूर्णांक reg_bits;

		/* f_samp is configured in CREG3 in घातers of 2 (x 1.024 MHz) */
		पूर्णांक f_samp_1_024mhz = BIT(FIELD_GET(AS73211_CREG3_CCLK_MASK, data->creg3));

		/*
		 * समय_ms = समय_us * US_PER_MS * f_samp_1_024mhz / MHZ_PER_HZ
		 *         = समय_us * f_samp_1_024mhz / 1000
		 */
		समय_ms = (val_us * f_samp_1_024mhz) / 1000;  /* 1 ms, 2 ms, ... (घातer of two) */
		अगर (समय_ms < 0 || !is_घातer_of_2(समय_ms) || समय_ms > AS73211_SAMPLE_TIME_MAX_MS)
			वापस -EINVAL;

		reg_bits = ilog2(समय_ms);
		अगर (!FIELD_FIT(AS73211_CREG1_TIME_MASK, reg_bits))
			वापस -EINVAL;  /* not possible due to previous tests */

		data->creg1 &= ~AS73211_CREG1_TIME_MASK;
		data->creg1 |= FIELD_PREP(AS73211_CREG1_TIME_MASK, reg_bits);

		ret = i2c_smbus_ग_लिखो_byte_data(data->client, AS73211_REG_CREG1, data->creg1);
		अगर (ret < 0)
			वापस ret;

		वापस 0;

	शेष:
		वापस -EINVAL;
	पूर्णपूर्ण
पूर्ण

अटल पूर्णांक as73211_ग_लिखो_raw(काष्ठा iio_dev *indio_dev, काष्ठा iio_chan_spec स्थिर *chan,
			      पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा as73211_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->mutex);

	ret = iio_device_claim_direct_mode(indio_dev);
	अगर (ret < 0)
		जाओ error_unlock;

	/* Need to चयन to config mode ... */
	अगर ((data->osr & AS73211_OSR_DOS_MASK) != AS73211_OSR_DOS_CONFIG) अणु
		data->osr &= ~AS73211_OSR_DOS_MASK;
		data->osr |= AS73211_OSR_DOS_CONFIG;

		ret = i2c_smbus_ग_लिखो_byte_data(data->client, AS73211_REG_OSR, data->osr);
		अगर (ret < 0)
			जाओ error_release;
	पूर्ण

	ret = _as73211_ग_लिखो_raw(indio_dev, chan, val, val2, mask);

error_release:
	iio_device_release_direct_mode(indio_dev);
error_unlock:
	mutex_unlock(&data->mutex);
	वापस ret;
पूर्ण

अटल irqवापस_t as73211_पढ़ोy_handler(पूर्णांक irq __always_unused, व्योम *priv)
अणु
	काष्ठा as73211_data *data = iio_priv(priv);

	complete(&data->completion);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t as73211_trigger_handler(पूर्णांक irq __always_unused, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा as73211_data *data = iio_priv(indio_dev);
	काष्ठा अणु
		__le16 chan[4];
		s64 ts __aligned(8);
	पूर्ण scan;
	पूर्णांक data_result, ret;

	mutex_lock(&data->mutex);

	data_result = as73211_req_data(data);
	अगर (data_result < 0 && data_result != -EOVERFLOW)
		जाओ करोne;  /* करोn't push any data क्रम errors other than EOVERFLOW */

	अगर (*indio_dev->active_scan_mask == AS73211_SCAN_MASK_ALL) अणु
		/* Optimization क्रम पढ़ोing all (color + temperature) channels */
		u8 addr = as73211_channels[0].address;
		काष्ठा i2c_msg msgs[] = अणु
			अणु
				.addr = data->client->addr,
				.flags = 0,
				.len = 1,
				.buf = &addr,
			पूर्ण,
			अणु
				.addr = data->client->addr,
				.flags = I2C_M_RD,
				.len = माप(scan.chan),
				.buf = (u8 *)&scan.chan,
			पूर्ण,
		पूर्ण;

		ret = i2c_transfer(data->client->adapter, msgs, ARRAY_SIZE(msgs));
		अगर (ret < 0)
			जाओ करोne;
	पूर्ण अन्यथा अणु
		/* Optimization क्रम पढ़ोing only color channels */

		/* AS73211 starts पढ़ोing at address 2 */
		ret = i2c_master_recv(data->client,
				(अक्षर *)&scan.chan[1], 3 * माप(scan.chan[1]));
		अगर (ret < 0)
			जाओ करोne;
	पूर्ण

	अगर (data_result) अणु
		/*
		 * Saturate all channels (in हाल of overflows). Temperature channel
		 * is not affected by overflows.
		 */
		scan.chan[1] = cpu_to_le16(U16_MAX);
		scan.chan[2] = cpu_to_le16(U16_MAX);
		scan.chan[3] = cpu_to_le16(U16_MAX);
	पूर्ण

	iio_push_to_buffers_with_बारtamp(indio_dev, &scan, iio_get_समय_ns(indio_dev));

करोne:
	mutex_unlock(&data->mutex);
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा iio_info as73211_info = अणु
	.पढ़ो_raw = as73211_पढ़ो_raw,
	.पढ़ो_avail = as73211_पढ़ो_avail,
	.ग_लिखो_raw = as73211_ग_लिखो_raw,
पूर्ण;

अटल पूर्णांक as73211_घातer(काष्ठा iio_dev *indio_dev, bool state)
अणु
	काष्ठा as73211_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->mutex);

	अगर (state)
		data->osr &= ~AS73211_OSR_PD;
	अन्यथा
		data->osr |= AS73211_OSR_PD;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, AS73211_REG_OSR, data->osr);

	mutex_unlock(&data->mutex);

	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम as73211_घातer_disable(व्योम *data)
अणु
	काष्ठा iio_dev *indio_dev = data;

	as73211_घातer(indio_dev, false);
पूर्ण

अटल पूर्णांक as73211_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा as73211_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;

	mutex_init(&data->mutex);
	init_completion(&data->completion);

	indio_dev->info = &as73211_info;
	indio_dev->name = AS73211_DRV_NAME;
	indio_dev->channels = as73211_channels;
	indio_dev->num_channels = ARRAY_SIZE(as73211_channels);
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, AS73211_REG_OSR);
	अगर (ret < 0)
		वापस ret;
	data->osr = ret;

	/* reset device */
	data->osr |= AS73211_OSR_SW_RES;
	ret = i2c_smbus_ग_लिखो_byte_data(data->client, AS73211_REG_OSR, data->osr);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, AS73211_REG_OSR);
	अगर (ret < 0)
		वापस ret;
	data->osr = ret;

	/*
	 * Reading AGEN is only possible after reset (AGEN is not available अगर
	 * device is in measurement mode).
	 */
	ret = i2c_smbus_पढ़ो_byte_data(data->client, AS73211_REG_AGEN);
	अगर (ret < 0)
		वापस ret;

	/* At the समय of writing this driver, only DEVID 2 and MUT 1 are known. */
	अगर ((ret & AS73211_AGEN_DEVID_MASK) != AS73211_AGEN_DEVID(2) ||
	    (ret & AS73211_AGEN_MUT_MASK) != AS73211_AGEN_MUT(1))
		वापस -ENODEV;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, AS73211_REG_CREG1);
	अगर (ret < 0)
		वापस ret;
	data->creg1 = ret;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, AS73211_REG_CREG2);
	अगर (ret < 0)
		वापस ret;
	data->creg2 = ret;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, AS73211_REG_CREG3);
	अगर (ret < 0)
		वापस ret;
	data->creg3 = ret;
	as73211_पूर्णांकegration_समय_calc_avail(data);

	ret = as73211_घातer(indio_dev, true);
	अगर (ret < 0)
		वापस ret;

	ret = devm_add_action_or_reset(dev, as73211_घातer_disable, indio_dev);
	अगर (ret)
		वापस ret;

	ret = devm_iio_triggered_buffer_setup(dev, indio_dev, शून्य, as73211_trigger_handler, शून्य);
	अगर (ret)
		वापस ret;

	अगर (client->irq) अणु
		ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
				शून्य,
				as73211_पढ़ोy_handler,
				IRQF_ONESHOT,
				client->name, indio_dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(dev, indio_dev);
पूर्ण

अटल पूर्णांक __maybe_unused as73211_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));

	वापस as73211_घातer(indio_dev, false);
पूर्ण

अटल पूर्णांक __maybe_unused as73211_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));

	वापस as73211_घातer(indio_dev, true);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(as73211_pm_ops, as73211_suspend, as73211_resume);

अटल स्थिर काष्ठा of_device_id as73211_of_match[] = अणु
	अणु .compatible = "ams,as73211" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, as73211_of_match);

अटल स्थिर काष्ठा i2c_device_id as73211_id[] = अणु
	अणु "as73211", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, as73211_id);

अटल काष्ठा i2c_driver as73211_driver = अणु
	.driver = अणु
		.name           = AS73211_DRV_NAME,
		.of_match_table = as73211_of_match,
		.pm             = &as73211_pm_ops,
	पूर्ण,
	.probe_new  = as73211_probe,
	.id_table   = as73211_id,
पूर्ण;
module_i2c_driver(as73211_driver);

MODULE_AUTHOR("Christian Eggers <ceggers@arri.de>");
MODULE_DESCRIPTION("AS73211 XYZ True Color Sensor driver");
MODULE_LICENSE("GPL");
