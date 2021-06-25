<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ADXRS290 SPI Gyroscope Driver
 *
 * Copyright (C) 2020 Nishant Malpani <nish.malpani25@gmail.com>
 * Copyright (C) 2020 Analog Devices, Inc.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>

#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/trigger_consumer.h>

#घोषणा ADXRS290_ADI_ID		0xAD
#घोषणा ADXRS290_MEMS_ID	0x1D
#घोषणा ADXRS290_DEV_ID		0x92

#घोषणा ADXRS290_REG_ADI_ID	0x00
#घोषणा ADXRS290_REG_MEMS_ID	0x01
#घोषणा ADXRS290_REG_DEV_ID	0x02
#घोषणा ADXRS290_REG_REV_ID	0x03
#घोषणा ADXRS290_REG_SN0	0x04 /* Serial Number Registers, 4 bytes */
#घोषणा ADXRS290_REG_DATAX0	0x08 /* Roll Rate o/p Data Regs, 2 bytes */
#घोषणा ADXRS290_REG_DATAY0	0x0A /* Pitch Rate o/p Data Regs, 2 bytes */
#घोषणा ADXRS290_REG_TEMP0	0x0C
#घोषणा ADXRS290_REG_POWER_CTL	0x10
#घोषणा ADXRS290_REG_FILTER	0x11
#घोषणा ADXRS290_REG_DATA_RDY	0x12

#घोषणा ADXRS290_READ		BIT(7)
#घोषणा ADXRS290_TSM		BIT(0)
#घोषणा ADXRS290_MEASUREMENT	BIT(1)
#घोषणा ADXRS290_DATA_RDY_OUT	BIT(0)
#घोषणा ADXRS290_SYNC_MASK	GENMASK(1, 0)
#घोषणा ADXRS290_SYNC(x)	FIELD_PREP(ADXRS290_SYNC_MASK, x)
#घोषणा ADXRS290_LPF_MASK	GENMASK(2, 0)
#घोषणा ADXRS290_LPF(x)		FIELD_PREP(ADXRS290_LPF_MASK, x)
#घोषणा ADXRS290_HPF_MASK	GENMASK(7, 4)
#घोषणा ADXRS290_HPF(x)		FIELD_PREP(ADXRS290_HPF_MASK, x)

#घोषणा ADXRS290_READ_REG(reg)	(ADXRS290_READ | (reg))

#घोषणा ADXRS290_MAX_TRANSITION_TIME_MS 100

क्रमागत adxrs290_mode अणु
	ADXRS290_MODE_STANDBY,
	ADXRS290_MODE_MEASUREMENT,
पूर्ण;

क्रमागत adxrs290_scan_index अणु
	ADXRS290_IDX_X,
	ADXRS290_IDX_Y,
	ADXRS290_IDX_TEMP,
	ADXRS290_IDX_TS,
पूर्ण;

काष्ठा adxrs290_state अणु
	काष्ठा spi_device	*spi;
	/* Serialize पढ़ोs and their subsequent processing */
	काष्ठा mutex		lock;
	क्रमागत adxrs290_mode	mode;
	अचिन्हित पूर्णांक		lpf_3db_freq_idx;
	अचिन्हित पूर्णांक		hpf_3db_freq_idx;
	काष्ठा iio_trigger      *dपढ़ोy_trig;
	/* Ensure correct alignment of बारtamp when present */
	काष्ठा अणु
		s16 channels[3];
		s64 ts __aligned(8);
	पूर्ण buffer;
पूर्ण;

/*
 * Available cut-off frequencies of the low pass filter in Hz.
 * The पूर्णांकeger part and fractional part are represented separately.
 */
अटल स्थिर पूर्णांक adxrs290_lpf_3db_freq_hz_table[][2] = अणु
	[0] = अणु480, 0पूर्ण,
	[1] = अणु320, 0पूर्ण,
	[2] = अणु160, 0पूर्ण,
	[3] = अणु80, 0पूर्ण,
	[4] = अणु56, 600000पूर्ण,
	[5] = अणु40, 0पूर्ण,
	[6] = अणु28, 300000पूर्ण,
	[7] = अणु20, 0पूर्ण,
पूर्ण;

/*
 * Available cut-off frequencies of the high pass filter in Hz.
 * The पूर्णांकeger part and fractional part are represented separately.
 */
अटल स्थिर पूर्णांक adxrs290_hpf_3db_freq_hz_table[][2] = अणु
	[0] = अणु0, 0पूर्ण,
	[1] = अणु0, 11000पूर्ण,
	[2] = अणु0, 22000पूर्ण,
	[3] = अणु0, 44000पूर्ण,
	[4] = अणु0, 87000पूर्ण,
	[5] = अणु0, 175000पूर्ण,
	[6] = अणु0, 350000पूर्ण,
	[7] = अणु0, 700000पूर्ण,
	[8] = अणु1, 400000पूर्ण,
	[9] = अणु2, 800000पूर्ण,
	[10] = अणु11, 300000पूर्ण,
पूर्ण;

अटल पूर्णांक adxrs290_get_rate_data(काष्ठा iio_dev *indio_dev, स्थिर u8 cmd, पूर्णांक *val)
अणु
	काष्ठा adxrs290_state *st = iio_priv(indio_dev);
	पूर्णांक ret = 0;
	पूर्णांक temp;

	mutex_lock(&st->lock);
	temp = spi_w8r16(st->spi, cmd);
	अगर (temp < 0) अणु
		ret = temp;
		जाओ err_unlock;
	पूर्ण

	*val = temp;

err_unlock:
	mutex_unlock(&st->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक adxrs290_get_temp_data(काष्ठा iio_dev *indio_dev, पूर्णांक *val)
अणु
	स्थिर u8 cmd = ADXRS290_READ_REG(ADXRS290_REG_TEMP0);
	काष्ठा adxrs290_state *st = iio_priv(indio_dev);
	पूर्णांक ret = 0;
	पूर्णांक temp;

	mutex_lock(&st->lock);
	temp = spi_w8r16(st->spi, cmd);
	अगर (temp < 0) अणु
		ret = temp;
		जाओ err_unlock;
	पूर्ण

	/* extract lower 12 bits temperature पढ़ोing */
	*val = temp & 0x0FFF;

err_unlock:
	mutex_unlock(&st->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक adxrs290_get_3db_freq(काष्ठा iio_dev *indio_dev, u8 *val, u8 *val2)
अणु
	स्थिर u8 cmd = ADXRS290_READ_REG(ADXRS290_REG_FILTER);
	काष्ठा adxrs290_state *st = iio_priv(indio_dev);
	पूर्णांक ret = 0;
	लघु temp;

	mutex_lock(&st->lock);
	temp = spi_w8r8(st->spi, cmd);
	अगर (temp < 0) अणु
		ret = temp;
		जाओ err_unlock;
	पूर्ण

	*val = FIELD_GET(ADXRS290_LPF_MASK, temp);
	*val2 = FIELD_GET(ADXRS290_HPF_MASK, temp);

err_unlock:
	mutex_unlock(&st->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक adxrs290_spi_ग_लिखो_reg(काष्ठा spi_device *spi, स्थिर u8 reg,
				  स्थिर u8 val)
अणु
	u8 buf[2];

	buf[0] = reg;
	buf[1] = val;

	वापस spi_ग_लिखो_then_पढ़ो(spi, buf, ARRAY_SIZE(buf), शून्य, 0);
पूर्ण

अटल पूर्णांक adxrs290_find_match(स्थिर पूर्णांक (*freq_tbl)[2], स्थिर पूर्णांक n,
			       स्थिर पूर्णांक val, स्थिर पूर्णांक val2)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < n; i++) अणु
		अगर (freq_tbl[i][0] == val && freq_tbl[i][1] == val2)
			वापस i;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक adxrs290_set_filter_freq(काष्ठा iio_dev *indio_dev,
				    स्थिर अचिन्हित पूर्णांक lpf_idx,
				    स्थिर अचिन्हित पूर्णांक hpf_idx)
अणु
	काष्ठा adxrs290_state *st = iio_priv(indio_dev);
	u8 val;

	val = ADXRS290_HPF(hpf_idx) | ADXRS290_LPF(lpf_idx);

	वापस adxrs290_spi_ग_लिखो_reg(st->spi, ADXRS290_REG_FILTER, val);
पूर्ण

अटल पूर्णांक adxrs290_set_mode(काष्ठा iio_dev *indio_dev, क्रमागत adxrs290_mode mode)
अणु
	काष्ठा adxrs290_state *st = iio_priv(indio_dev);
	पूर्णांक val, ret;

	अगर (st->mode == mode)
		वापस 0;

	mutex_lock(&st->lock);

	ret = spi_w8r8(st->spi, ADXRS290_READ_REG(ADXRS290_REG_POWER_CTL));
	अगर (ret < 0)
		जाओ out_unlock;

	val = ret;

	चयन (mode) अणु
	हाल ADXRS290_MODE_STANDBY:
		val &= ~ADXRS290_MEASUREMENT;
		अवरोध;
	हाल ADXRS290_MODE_MEASUREMENT:
		val |= ADXRS290_MEASUREMENT;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	ret = adxrs290_spi_ग_लिखो_reg(st->spi, ADXRS290_REG_POWER_CTL, val);
	अगर (ret < 0) अणु
		dev_err(&st->spi->dev, "unable to set mode: %d\n", ret);
		जाओ out_unlock;
	पूर्ण

	/* update cached mode */
	st->mode = mode;

out_unlock:
	mutex_unlock(&st->lock);
	वापस ret;
पूर्ण

अटल व्योम adxrs290_chip_off_action(व्योम *data)
अणु
	काष्ठा iio_dev *indio_dev = data;

	adxrs290_set_mode(indio_dev, ADXRS290_MODE_STANDBY);
पूर्ण

अटल पूर्णांक adxrs290_initial_setup(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा adxrs290_state *st = iio_priv(indio_dev);
	काष्ठा spi_device *spi = st->spi;
	पूर्णांक ret;

	ret = adxrs290_spi_ग_लिखो_reg(spi, ADXRS290_REG_POWER_CTL,
				     ADXRS290_MEASUREMENT | ADXRS290_TSM);
	अगर (ret < 0)
		वापस ret;

	st->mode = ADXRS290_MODE_MEASUREMENT;

	वापस devm_add_action_or_reset(&spi->dev, adxrs290_chip_off_action,
					indio_dev);
पूर्ण

अटल पूर्णांक adxrs290_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक *val,
			     पूर्णांक *val2,
			     दीर्घ mask)
अणु
	काष्ठा adxrs290_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक t;
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;

		चयन (chan->type) अणु
		हाल IIO_ANGL_VEL:
			ret = adxrs290_get_rate_data(indio_dev,
						     ADXRS290_READ_REG(chan->address),
						     val);
			अगर (ret < 0)
				अवरोध;

			ret = IIO_VAL_INT;
			अवरोध;
		हाल IIO_TEMP:
			ret = adxrs290_get_temp_data(indio_dev, val);
			अगर (ret < 0)
				अवरोध;

			ret = IIO_VAL_INT;
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		iio_device_release_direct_mode(indio_dev);
		वापस ret;
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_ANGL_VEL:
			/* 1 LSB = 0.005 degrees/sec */
			*val = 0;
			*val2 = 87266;
			वापस IIO_VAL_INT_PLUS_न_अंकO;
		हाल IIO_TEMP:
			/* 1 LSB = 0.1 degrees Celsius */
			*val = 100;
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		चयन (chan->type) अणु
		हाल IIO_ANGL_VEL:
			t = st->lpf_3db_freq_idx;
			*val = adxrs290_lpf_3db_freq_hz_table[t][0];
			*val2 = adxrs290_lpf_3db_freq_hz_table[t][1];
			वापस IIO_VAL_INT_PLUS_MICRO;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_HIGH_PASS_FILTER_3DB_FREQUENCY:
		चयन (chan->type) अणु
		हाल IIO_ANGL_VEL:
			t = st->hpf_3db_freq_idx;
			*val = adxrs290_hpf_3db_freq_hz_table[t][0];
			*val2 = adxrs290_hpf_3db_freq_hz_table[t][1];
			वापस IIO_VAL_INT_PLUS_MICRO;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक adxrs290_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan,
			      पूर्णांक val,
			      पूर्णांक val2,
			      दीर्घ mask)
अणु
	काष्ठा adxrs290_state *st = iio_priv(indio_dev);
	पूर्णांक ret, lpf_idx, hpf_idx;

	ret = iio_device_claim_direct_mode(indio_dev);
	अगर (ret)
		वापस ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		lpf_idx = adxrs290_find_match(adxrs290_lpf_3db_freq_hz_table,
					      ARRAY_SIZE(adxrs290_lpf_3db_freq_hz_table),
					      val, val2);
		अगर (lpf_idx < 0) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		/* caching the updated state of the low-pass filter */
		st->lpf_3db_freq_idx = lpf_idx;
		/* retrieving the current state of the high-pass filter */
		hpf_idx = st->hpf_3db_freq_idx;
		ret = adxrs290_set_filter_freq(indio_dev, lpf_idx, hpf_idx);
		अवरोध;

	हाल IIO_CHAN_INFO_HIGH_PASS_FILTER_3DB_FREQUENCY:
		hpf_idx = adxrs290_find_match(adxrs290_hpf_3db_freq_hz_table,
					      ARRAY_SIZE(adxrs290_hpf_3db_freq_hz_table),
					      val, val2);
		अगर (hpf_idx < 0) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		/* caching the updated state of the high-pass filter */
		st->hpf_3db_freq_idx = hpf_idx;
		/* retrieving the current state of the low-pass filter */
		lpf_idx = st->lpf_3db_freq_idx;
		ret = adxrs290_set_filter_freq(indio_dev, lpf_idx, hpf_idx);
		अवरोध;

	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	iio_device_release_direct_mode(indio_dev);
	वापस ret;
पूर्ण

अटल पूर्णांक adxrs290_पढ़ो_avail(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       स्थिर पूर्णांक **vals, पूर्णांक *type, पूर्णांक *length,
			       दीर्घ mask)
अणु
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		*vals = (स्थिर पूर्णांक *)adxrs290_lpf_3db_freq_hz_table;
		*type = IIO_VAL_INT_PLUS_MICRO;
		/* Values are stored in a 2D matrix */
		*length = ARRAY_SIZE(adxrs290_lpf_3db_freq_hz_table) * 2;

		वापस IIO_AVAIL_LIST;
	हाल IIO_CHAN_INFO_HIGH_PASS_FILTER_3DB_FREQUENCY:
		*vals = (स्थिर पूर्णांक *)adxrs290_hpf_3db_freq_hz_table;
		*type = IIO_VAL_INT_PLUS_MICRO;
		/* Values are stored in a 2D matrix */
		*length = ARRAY_SIZE(adxrs290_hpf_3db_freq_hz_table) * 2;

		वापस IIO_AVAIL_LIST;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक adxrs290_reg_access_rw(काष्ठा spi_device *spi, अचिन्हित पूर्णांक reg,
				  अचिन्हित पूर्णांक *पढ़ोval)
अणु
	पूर्णांक ret;

	ret = spi_w8r8(spi, ADXRS290_READ_REG(reg));
	अगर (ret < 0)
		वापस ret;

	*पढ़ोval = ret;

	वापस 0;
पूर्ण

अटल पूर्णांक adxrs290_reg_access(काष्ठा iio_dev *indio_dev, अचिन्हित पूर्णांक reg,
			       अचिन्हित पूर्णांक ग_लिखोval, अचिन्हित पूर्णांक *पढ़ोval)
अणु
	काष्ठा adxrs290_state *st = iio_priv(indio_dev);

	अगर (पढ़ोval)
		वापस adxrs290_reg_access_rw(st->spi, reg, पढ़ोval);
	अन्यथा
		वापस adxrs290_spi_ग_लिखो_reg(st->spi, reg, ग_लिखोval);
पूर्ण

अटल पूर्णांक adxrs290_data_rdy_trigger_set_state(काष्ठा iio_trigger *trig,
					       bool state)
अणु
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	काष्ठा adxrs290_state *st = iio_priv(indio_dev);
	पूर्णांक ret;
	u8 val;

	val = state ? ADXRS290_SYNC(ADXRS290_DATA_RDY_OUT) : 0;

	ret = adxrs290_spi_ग_लिखो_reg(st->spi, ADXRS290_REG_DATA_RDY, val);
	अगर (ret < 0)
		dev_err(&st->spi->dev, "failed to start data rdy interrupt\n");

	वापस ret;
पूर्ण

अटल व्योम adxrs290_reset_trig(काष्ठा iio_trigger *trig)
अणु
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	पूर्णांक val;

	/*
	 * Data पढ़ोy पूर्णांकerrupt is reset after a पढ़ो of the data रेजिस्टरs.
	 * Here, we only पढ़ो the 16b DATAY रेजिस्टरs as that marks the end of
	 * a पढ़ो of the data रेजिस्टरs and initiates a reset क्रम the पूर्णांकerrupt
	 * line.
	 */
	adxrs290_get_rate_data(indio_dev,
			       ADXRS290_READ_REG(ADXRS290_REG_DATAY0), &val);
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops adxrs290_trigger_ops = अणु
	.set_trigger_state = &adxrs290_data_rdy_trigger_set_state,
	.validate_device = &iio_trigger_validate_own_device,
	.reenable = &adxrs290_reset_trig,
पूर्ण;

अटल irqवापस_t adxrs290_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा adxrs290_state *st = iio_priv(indio_dev);
	u8 tx = ADXRS290_READ_REG(ADXRS290_REG_DATAX0);
	पूर्णांक ret;

	mutex_lock(&st->lock);

	/* exercise a bulk data capture starting from reg DATAX0... */
	ret = spi_ग_लिखो_then_पढ़ो(st->spi, &tx, माप(tx), st->buffer.channels,
				  माप(st->buffer.channels));
	अगर (ret < 0)
		जाओ out_unlock_notअगरy;

	iio_push_to_buffers_with_बारtamp(indio_dev, &st->buffer,
					   pf->बारtamp);

out_unlock_notअगरy:
	mutex_unlock(&st->lock);
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

#घोषणा ADXRS290_ANGL_VEL_CHANNEL(reg, axis) अणु				\
	.type = IIO_ANGL_VEL,						\
	.address = reg,							\
	.modअगरied = 1,							\
	.channel2 = IIO_MOD_##axis,					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),			\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) |		\
	BIT(IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY) |		\
	BIT(IIO_CHAN_INFO_HIGH_PASS_FILTER_3DB_FREQUENCY),		\
	.info_mask_shared_by_type_available =				\
	BIT(IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY) |		\
	BIT(IIO_CHAN_INFO_HIGH_PASS_FILTER_3DB_FREQUENCY),		\
	.scan_index = ADXRS290_IDX_##axis,				\
	.scan_type = अणु                                                  \
		.sign = 's',                                            \
		.realbits = 16,                                         \
		.storagebits = 16,                                      \
		.endianness = IIO_LE,					\
	पूर्ण,                                                              \
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec adxrs290_channels[] = अणु
	ADXRS290_ANGL_VEL_CHANNEL(ADXRS290_REG_DATAX0, X),
	ADXRS290_ANGL_VEL_CHANNEL(ADXRS290_REG_DATAY0, Y),
	अणु
		.type = IIO_TEMP,
		.address = ADXRS290_REG_TEMP0,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
		BIT(IIO_CHAN_INFO_SCALE),
		.scan_index = ADXRS290_IDX_TEMP,
		.scan_type = अणु
			.sign = 's',
			.realbits = 12,
			.storagebits = 16,
			.endianness = IIO_LE,
		पूर्ण,
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(ADXRS290_IDX_TS),
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ adxrs290_avail_scan_masks[] = अणु
	BIT(ADXRS290_IDX_X) | BIT(ADXRS290_IDX_Y) | BIT(ADXRS290_IDX_TEMP),
	0
पूर्ण;

अटल स्थिर काष्ठा iio_info adxrs290_info = अणु
	.पढ़ो_raw = &adxrs290_पढ़ो_raw,
	.ग_लिखो_raw = &adxrs290_ग_लिखो_raw,
	.पढ़ो_avail = &adxrs290_पढ़ो_avail,
	.debugfs_reg_access = &adxrs290_reg_access,
पूर्ण;

अटल पूर्णांक adxrs290_probe_trigger(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा adxrs290_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	अगर (!st->spi->irq) अणु
		dev_info(&st->spi->dev, "no irq, using polling\n");
		वापस 0;
	पूर्ण

	st->dपढ़ोy_trig = devm_iio_trigger_alloc(&st->spi->dev, "%s-dev%d",
						 indio_dev->name,
						 indio_dev->id);
	अगर (!st->dपढ़ोy_trig)
		वापस -ENOMEM;

	st->dपढ़ोy_trig->ops = &adxrs290_trigger_ops;
	iio_trigger_set_drvdata(st->dपढ़ोy_trig, indio_dev);

	ret = devm_request_irq(&st->spi->dev, st->spi->irq,
			       &iio_trigger_generic_data_rdy_poll,
			       IRQF_ONESHOT, "adxrs290_irq", st->dपढ़ोy_trig);
	अगर (ret < 0)
		वापस dev_err_probe(&st->spi->dev, ret,
				     "request irq %d failed\n", st->spi->irq);

	ret = devm_iio_trigger_रेजिस्टर(&st->spi->dev, st->dपढ़ोy_trig);
	अगर (ret) अणु
		dev_err(&st->spi->dev, "iio trigger register failed\n");
		वापस ret;
	पूर्ण

	indio_dev->trig = iio_trigger_get(st->dपढ़ोy_trig);

	वापस 0;
पूर्ण

अटल पूर्णांक adxrs290_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा adxrs290_state *st;
	u8 val, val2;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);
	st->spi = spi;

	indio_dev->name = "adxrs290";
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = adxrs290_channels;
	indio_dev->num_channels = ARRAY_SIZE(adxrs290_channels);
	indio_dev->info = &adxrs290_info;
	indio_dev->available_scan_masks = adxrs290_avail_scan_masks;

	mutex_init(&st->lock);

	val = spi_w8r8(spi, ADXRS290_READ_REG(ADXRS290_REG_ADI_ID));
	अगर (val != ADXRS290_ADI_ID) अणु
		dev_err(&spi->dev, "Wrong ADI ID 0x%02x\n", val);
		वापस -ENODEV;
	पूर्ण

	val = spi_w8r8(spi, ADXRS290_READ_REG(ADXRS290_REG_MEMS_ID));
	अगर (val != ADXRS290_MEMS_ID) अणु
		dev_err(&spi->dev, "Wrong MEMS ID 0x%02x\n", val);
		वापस -ENODEV;
	पूर्ण

	val = spi_w8r8(spi, ADXRS290_READ_REG(ADXRS290_REG_DEV_ID));
	अगर (val != ADXRS290_DEV_ID) अणु
		dev_err(&spi->dev, "Wrong DEV ID 0x%02x\n", val);
		वापस -ENODEV;
	पूर्ण

	/* शेष mode the gyroscope starts in */
	st->mode = ADXRS290_MODE_STANDBY;

	/* चयन to measurement mode and चयन on the temperature sensor */
	ret = adxrs290_initial_setup(indio_dev);
	अगर (ret < 0)
		वापस ret;

	/* max transition समय to measurement mode */
	msleep(ADXRS290_MAX_TRANSITION_TIME_MS);

	ret = adxrs290_get_3db_freq(indio_dev, &val, &val2);
	अगर (ret < 0)
		वापस ret;

	st->lpf_3db_freq_idx = val;
	st->hpf_3db_freq_idx = val2;

	ret = devm_iio_triggered_buffer_setup(&spi->dev, indio_dev,
					      &iio_pollfunc_store_समय,
					      &adxrs290_trigger_handler, शून्य);
	अगर (ret < 0)
		वापस dev_err_probe(&spi->dev, ret,
				     "iio triggered buffer setup failed\n");

	ret = adxrs290_probe_trigger(indio_dev);
	अगर (ret < 0)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(&spi->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id adxrs290_of_match[] = अणु
	अणु .compatible = "adi,adxrs290" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, adxrs290_of_match);

अटल काष्ठा spi_driver adxrs290_driver = अणु
	.driver = अणु
		.name = "adxrs290",
		.of_match_table = adxrs290_of_match,
	पूर्ण,
	.probe = adxrs290_probe,
पूर्ण;
module_spi_driver(adxrs290_driver);

MODULE_AUTHOR("Nishant Malpani <nish.malpani25@gmail.com>");
MODULE_DESCRIPTION("Analog Devices ADXRS290 Gyroscope SPI driver");
MODULE_LICENSE("GPL");
