<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2020 Invensense, Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/delay.h>
#समावेश <linux/math64.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/kfअगरo_buf.h>

#समावेश "inv_icm42600.h"
#समावेश "inv_icm42600_temp.h"
#समावेश "inv_icm42600_buffer.h"
#समावेश "inv_icm42600_timestamp.h"

#घोषणा INV_ICM42600_ACCEL_CHAN(_modअगरier, _index, _ext_info)		\
	अणु								\
		.type = IIO_ACCEL,					\
		.modअगरied = 1,						\
		.channel2 = _modअगरier,					\
		.info_mask_separate =					\
			BIT(IIO_CHAN_INFO_RAW) |			\
			BIT(IIO_CHAN_INFO_CALIBBIAS),			\
		.info_mask_shared_by_type =				\
			BIT(IIO_CHAN_INFO_SCALE),			\
		.info_mask_shared_by_type_available =			\
			BIT(IIO_CHAN_INFO_SCALE) |			\
			BIT(IIO_CHAN_INFO_CALIBBIAS),			\
		.info_mask_shared_by_all =				\
			BIT(IIO_CHAN_INFO_SAMP_FREQ),			\
		.info_mask_shared_by_all_available =			\
			BIT(IIO_CHAN_INFO_SAMP_FREQ),			\
		.scan_index = _index,					\
		.scan_type = अणु						\
			.sign = 's',					\
			.realbits = 16,					\
			.storagebits = 16,				\
			.endianness = IIO_BE,				\
		पूर्ण,							\
		.ext_info = _ext_info,					\
	पूर्ण

क्रमागत inv_icm42600_accel_scan अणु
	INV_ICM42600_ACCEL_SCAN_X,
	INV_ICM42600_ACCEL_SCAN_Y,
	INV_ICM42600_ACCEL_SCAN_Z,
	INV_ICM42600_ACCEL_SCAN_TEMP,
	INV_ICM42600_ACCEL_SCAN_TIMESTAMP,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec_ext_info inv_icm42600_accel_ext_infos[] = अणु
	IIO_MOUNT_MATRIX(IIO_SHARED_BY_ALL, inv_icm42600_get_mount_matrix),
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec inv_icm42600_accel_channels[] = अणु
	INV_ICM42600_ACCEL_CHAN(IIO_MOD_X, INV_ICM42600_ACCEL_SCAN_X,
				inv_icm42600_accel_ext_infos),
	INV_ICM42600_ACCEL_CHAN(IIO_MOD_Y, INV_ICM42600_ACCEL_SCAN_Y,
				inv_icm42600_accel_ext_infos),
	INV_ICM42600_ACCEL_CHAN(IIO_MOD_Z, INV_ICM42600_ACCEL_SCAN_Z,
				inv_icm42600_accel_ext_infos),
	INV_ICM42600_TEMP_CHAN(INV_ICM42600_ACCEL_SCAN_TEMP),
	IIO_CHAN_SOFT_TIMESTAMP(INV_ICM42600_ACCEL_SCAN_TIMESTAMP),
पूर्ण;

/*
 * IIO buffer data: size must be a घातer of 2 and बारtamp aligned
 * 16 bytes: 6 bytes acceleration, 2 bytes temperature, 8 bytes बारtamp
 */
काष्ठा inv_icm42600_accel_buffer अणु
	काष्ठा inv_icm42600_fअगरo_sensor_data accel;
	पूर्णांक16_t temp;
	पूर्णांक64_t बारtamp __aligned(8);
पूर्ण;

#घोषणा INV_ICM42600_SCAN_MASK_ACCEL_3AXIS				\
	(BIT(INV_ICM42600_ACCEL_SCAN_X) |				\
	BIT(INV_ICM42600_ACCEL_SCAN_Y) |				\
	BIT(INV_ICM42600_ACCEL_SCAN_Z))

#घोषणा INV_ICM42600_SCAN_MASK_TEMP	BIT(INV_ICM42600_ACCEL_SCAN_TEMP)

अटल स्थिर अचिन्हित दीर्घ inv_icm42600_accel_scan_masks[] = अणु
	/* 3-axis accel + temperature */
	INV_ICM42600_SCAN_MASK_ACCEL_3AXIS | INV_ICM42600_SCAN_MASK_TEMP,
	0,
पूर्ण;

/* enable accelerometer sensor and FIFO ग_लिखो */
अटल पूर्णांक inv_icm42600_accel_update_scan_mode(काष्ठा iio_dev *indio_dev,
					       स्थिर अचिन्हित दीर्घ *scan_mask)
अणु
	काष्ठा inv_icm42600_state *st = iio_device_get_drvdata(indio_dev);
	काष्ठा inv_icm42600_बारtamp *ts = iio_priv(indio_dev);
	काष्ठा inv_icm42600_sensor_conf conf = INV_ICM42600_SENSOR_CONF_INIT;
	अचिन्हित पूर्णांक fअगरo_en = 0;
	अचिन्हित पूर्णांक sleep_temp = 0;
	अचिन्हित पूर्णांक sleep_accel = 0;
	अचिन्हित पूर्णांक sleep;
	पूर्णांक ret;

	mutex_lock(&st->lock);

	अगर (*scan_mask & INV_ICM42600_SCAN_MASK_TEMP) अणु
		/* enable temp sensor */
		ret = inv_icm42600_set_temp_conf(st, true, &sleep_temp);
		अगर (ret)
			जाओ out_unlock;
		fअगरo_en |= INV_ICM42600_SENSOR_TEMP;
	पूर्ण

	अगर (*scan_mask & INV_ICM42600_SCAN_MASK_ACCEL_3AXIS) अणु
		/* enable accel sensor */
		conf.mode = INV_ICM42600_SENSOR_MODE_LOW_NOISE;
		ret = inv_icm42600_set_accel_conf(st, &conf, &sleep_accel);
		अगर (ret)
			जाओ out_unlock;
		fअगरo_en |= INV_ICM42600_SENSOR_ACCEL;
	पूर्ण

	/* update data FIFO ग_लिखो */
	inv_icm42600_बारtamp_apply_odr(ts, 0, 0, 0);
	ret = inv_icm42600_buffer_set_fअगरo_en(st, fअगरo_en | st->fअगरo.en);
	अगर (ret)
		जाओ out_unlock;

	ret = inv_icm42600_buffer_update_watermark(st);

out_unlock:
	mutex_unlock(&st->lock);
	/* sleep maximum required समय */
	अगर (sleep_accel > sleep_temp)
		sleep = sleep_accel;
	अन्यथा
		sleep = sleep_temp;
	अगर (sleep)
		msleep(sleep);
	वापस ret;
पूर्ण

अटल पूर्णांक inv_icm42600_accel_पढ़ो_sensor(काष्ठा inv_icm42600_state *st,
					  काष्ठा iio_chan_spec स्थिर *chan,
					  पूर्णांक16_t *val)
अणु
	काष्ठा device *dev = regmap_get_device(st->map);
	काष्ठा inv_icm42600_sensor_conf conf = INV_ICM42600_SENSOR_CONF_INIT;
	अचिन्हित पूर्णांक reg;
	__be16 *data;
	पूर्णांक ret;

	अगर (chan->type != IIO_ACCEL)
		वापस -EINVAL;

	चयन (chan->channel2) अणु
	हाल IIO_MOD_X:
		reg = INV_ICM42600_REG_ACCEL_DATA_X;
		अवरोध;
	हाल IIO_MOD_Y:
		reg = INV_ICM42600_REG_ACCEL_DATA_Y;
		अवरोध;
	हाल IIO_MOD_Z:
		reg = INV_ICM42600_REG_ACCEL_DATA_Z;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	pm_runसमय_get_sync(dev);
	mutex_lock(&st->lock);

	/* enable accel sensor */
	conf.mode = INV_ICM42600_SENSOR_MODE_LOW_NOISE;
	ret = inv_icm42600_set_accel_conf(st, &conf, शून्य);
	अगर (ret)
		जाओ निकास;

	/* पढ़ो accel रेजिस्टर data */
	data = (__be16 *)&st->buffer[0];
	ret = regmap_bulk_पढ़ो(st->map, reg, data, माप(*data));
	अगर (ret)
		जाओ निकास;

	*val = (पूर्णांक16_t)be16_to_cpup(data);
	अगर (*val == INV_ICM42600_DATA_INVALID)
		ret = -EINVAL;
निकास:
	mutex_unlock(&st->lock);
	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);
	वापस ret;
पूर्ण

/* IIO क्रमmat पूर्णांक + nano */
अटल स्थिर पूर्णांक inv_icm42600_accel_scale[] = अणु
	/* +/- 16G => 0.004788403 m/s-2 */
	[2 * INV_ICM42600_ACCEL_FS_16G] = 0,
	[2 * INV_ICM42600_ACCEL_FS_16G + 1] = 4788403,
	/* +/- 8G => 0.002394202 m/s-2 */
	[2 * INV_ICM42600_ACCEL_FS_8G] = 0,
	[2 * INV_ICM42600_ACCEL_FS_8G + 1] = 2394202,
	/* +/- 4G => 0.001197101 m/s-2 */
	[2 * INV_ICM42600_ACCEL_FS_4G] = 0,
	[2 * INV_ICM42600_ACCEL_FS_4G + 1] = 1197101,
	/* +/- 2G => 0.000598550 m/s-2 */
	[2 * INV_ICM42600_ACCEL_FS_2G] = 0,
	[2 * INV_ICM42600_ACCEL_FS_2G + 1] = 598550,
पूर्ण;

अटल पूर्णांक inv_icm42600_accel_पढ़ो_scale(काष्ठा inv_icm42600_state *st,
					 पूर्णांक *val, पूर्णांक *val2)
अणु
	अचिन्हित पूर्णांक idx;

	idx = st->conf.accel.fs;

	*val = inv_icm42600_accel_scale[2 * idx];
	*val2 = inv_icm42600_accel_scale[2 * idx + 1];
	वापस IIO_VAL_INT_PLUS_न_अंकO;
पूर्ण

अटल पूर्णांक inv_icm42600_accel_ग_लिखो_scale(काष्ठा inv_icm42600_state *st,
					  पूर्णांक val, पूर्णांक val2)
अणु
	काष्ठा device *dev = regmap_get_device(st->map);
	अचिन्हित पूर्णांक idx;
	काष्ठा inv_icm42600_sensor_conf conf = INV_ICM42600_SENSOR_CONF_INIT;
	पूर्णांक ret;

	क्रम (idx = 0; idx < ARRAY_SIZE(inv_icm42600_accel_scale); idx += 2) अणु
		अगर (val == inv_icm42600_accel_scale[idx] &&
		    val2 == inv_icm42600_accel_scale[idx + 1])
			अवरोध;
	पूर्ण
	अगर (idx >= ARRAY_SIZE(inv_icm42600_accel_scale))
		वापस -EINVAL;

	conf.fs = idx / 2;

	pm_runसमय_get_sync(dev);
	mutex_lock(&st->lock);

	ret = inv_icm42600_set_accel_conf(st, &conf, शून्य);

	mutex_unlock(&st->lock);
	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);

	वापस ret;
पूर्ण

/* IIO क्रमmat पूर्णांक + micro */
अटल स्थिर पूर्णांक inv_icm42600_accel_odr[] = अणु
	/* 12.5Hz */
	12, 500000,
	/* 25Hz */
	25, 0,
	/* 50Hz */
	50, 0,
	/* 100Hz */
	100, 0,
	/* 200Hz */
	200, 0,
	/* 1kHz */
	1000, 0,
	/* 2kHz */
	2000, 0,
	/* 4kHz */
	4000, 0,
पूर्ण;

अटल स्थिर पूर्णांक inv_icm42600_accel_odr_conv[] = अणु
	INV_ICM42600_ODR_12_5HZ,
	INV_ICM42600_ODR_25HZ,
	INV_ICM42600_ODR_50HZ,
	INV_ICM42600_ODR_100HZ,
	INV_ICM42600_ODR_200HZ,
	INV_ICM42600_ODR_1KHZ_LN,
	INV_ICM42600_ODR_2KHZ_LN,
	INV_ICM42600_ODR_4KHZ_LN,
पूर्ण;

अटल पूर्णांक inv_icm42600_accel_पढ़ो_odr(काष्ठा inv_icm42600_state *st,
				       पूर्णांक *val, पूर्णांक *val2)
अणु
	अचिन्हित पूर्णांक odr;
	अचिन्हित पूर्णांक i;

	odr = st->conf.accel.odr;

	क्रम (i = 0; i < ARRAY_SIZE(inv_icm42600_accel_odr_conv); ++i) अणु
		अगर (inv_icm42600_accel_odr_conv[i] == odr)
			अवरोध;
	पूर्ण
	अगर (i >= ARRAY_SIZE(inv_icm42600_accel_odr_conv))
		वापस -EINVAL;

	*val = inv_icm42600_accel_odr[2 * i];
	*val2 = inv_icm42600_accel_odr[2 * i + 1];

	वापस IIO_VAL_INT_PLUS_MICRO;
पूर्ण

अटल पूर्णांक inv_icm42600_accel_ग_लिखो_odr(काष्ठा iio_dev *indio_dev,
					पूर्णांक val, पूर्णांक val2)
अणु
	काष्ठा inv_icm42600_state *st = iio_device_get_drvdata(indio_dev);
	काष्ठा inv_icm42600_बारtamp *ts = iio_priv(indio_dev);
	काष्ठा device *dev = regmap_get_device(st->map);
	अचिन्हित पूर्णांक idx;
	काष्ठा inv_icm42600_sensor_conf conf = INV_ICM42600_SENSOR_CONF_INIT;
	पूर्णांक ret;

	क्रम (idx = 0; idx < ARRAY_SIZE(inv_icm42600_accel_odr); idx += 2) अणु
		अगर (val == inv_icm42600_accel_odr[idx] &&
		    val2 == inv_icm42600_accel_odr[idx + 1])
			अवरोध;
	पूर्ण
	अगर (idx >= ARRAY_SIZE(inv_icm42600_accel_odr))
		वापस -EINVAL;

	conf.odr = inv_icm42600_accel_odr_conv[idx / 2];

	pm_runसमय_get_sync(dev);
	mutex_lock(&st->lock);

	ret = inv_icm42600_बारtamp_update_odr(ts, inv_icm42600_odr_to_period(conf.odr),
						iio_buffer_enabled(indio_dev));
	अगर (ret)
		जाओ out_unlock;

	ret = inv_icm42600_set_accel_conf(st, &conf, शून्य);
	अगर (ret)
		जाओ out_unlock;
	inv_icm42600_buffer_update_fअगरo_period(st);
	inv_icm42600_buffer_update_watermark(st);

out_unlock:
	mutex_unlock(&st->lock);
	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);

	वापस ret;
पूर्ण

/*
 * Calibration bias values, IIO range क्रमmat पूर्णांक + micro.
 * Value is limited to +/-1g coded on 12 bits चिन्हित. Step is 0.5mg.
 */
अटल पूर्णांक inv_icm42600_accel_calibbias[] = अणु
	-10, 42010,		/* min: -10.042010 m/sतऑ */
	0, 4903,		/* step: 0.004903 m/sतऑ */
	10, 37106,		/* max: 10.037106 m/sतऑ */
पूर्ण;

अटल पूर्णांक inv_icm42600_accel_पढ़ो_offset(काष्ठा inv_icm42600_state *st,
					  काष्ठा iio_chan_spec स्थिर *chan,
					  पूर्णांक *val, पूर्णांक *val2)
अणु
	काष्ठा device *dev = regmap_get_device(st->map);
	पूर्णांक64_t val64;
	पूर्णांक32_t bias;
	अचिन्हित पूर्णांक reg;
	पूर्णांक16_t offset;
	uपूर्णांक8_t data[2];
	पूर्णांक ret;

	अगर (chan->type != IIO_ACCEL)
		वापस -EINVAL;

	चयन (chan->channel2) अणु
	हाल IIO_MOD_X:
		reg = INV_ICM42600_REG_OFFSET_USER4;
		अवरोध;
	हाल IIO_MOD_Y:
		reg = INV_ICM42600_REG_OFFSET_USER6;
		अवरोध;
	हाल IIO_MOD_Z:
		reg = INV_ICM42600_REG_OFFSET_USER7;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	pm_runसमय_get_sync(dev);
	mutex_lock(&st->lock);

	ret = regmap_bulk_पढ़ो(st->map, reg, st->buffer, माप(data));
	स_नकल(data, st->buffer, माप(data));

	mutex_unlock(&st->lock);
	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);
	अगर (ret)
		वापस ret;

	/* 12 bits चिन्हित value */
	चयन (chan->channel2) अणु
	हाल IIO_MOD_X:
		offset = sign_extend32(((data[0] & 0xF0) << 4) | data[1], 11);
		अवरोध;
	हाल IIO_MOD_Y:
		offset = sign_extend32(((data[1] & 0x0F) << 8) | data[0], 11);
		अवरोध;
	हाल IIO_MOD_Z:
		offset = sign_extend32(((data[0] & 0xF0) << 4) | data[1], 11);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/*
	 * convert raw offset to g then to m/sतऑ
	 * 12 bits चिन्हित raw step 0.5mg to g: 5 / 10000
	 * g to m/sतऑ: 9.806650
	 * result in micro (1000000)
	 * (offset * 5 * 9.806650 * 1000000) / 10000
	 */
	val64 = (पूर्णांक64_t)offset * 5LL * 9806650LL;
	/* क्रम rounding, add + or - भागisor (10000) भागided by 2 */
	अगर (val64 >= 0)
		val64 += 10000LL / 2LL;
	अन्यथा
		val64 -= 10000LL / 2LL;
	bias = भाग_s64(val64, 10000L);
	*val = bias / 1000000L;
	*val2 = bias % 1000000L;

	वापस IIO_VAL_INT_PLUS_MICRO;
पूर्ण

अटल पूर्णांक inv_icm42600_accel_ग_लिखो_offset(काष्ठा inv_icm42600_state *st,
					   काष्ठा iio_chan_spec स्थिर *chan,
					   पूर्णांक val, पूर्णांक val2)
अणु
	काष्ठा device *dev = regmap_get_device(st->map);
	पूर्णांक64_t val64;
	पूर्णांक32_t min, max;
	अचिन्हित पूर्णांक reg, regval;
	पूर्णांक16_t offset;
	पूर्णांक ret;

	अगर (chan->type != IIO_ACCEL)
		वापस -EINVAL;

	चयन (chan->channel2) अणु
	हाल IIO_MOD_X:
		reg = INV_ICM42600_REG_OFFSET_USER4;
		अवरोध;
	हाल IIO_MOD_Y:
		reg = INV_ICM42600_REG_OFFSET_USER6;
		अवरोध;
	हाल IIO_MOD_Z:
		reg = INV_ICM42600_REG_OFFSET_USER7;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* inv_icm42600_accel_calibbias: min - step - max in micro */
	min = inv_icm42600_accel_calibbias[0] * 1000000L +
	      inv_icm42600_accel_calibbias[1];
	max = inv_icm42600_accel_calibbias[4] * 1000000L +
	      inv_icm42600_accel_calibbias[5];
	val64 = (पूर्णांक64_t)val * 1000000LL + (पूर्णांक64_t)val2;
	अगर (val64 < min || val64 > max)
		वापस -EINVAL;

	/*
	 * convert m/sतऑ to g then to raw value
	 * m/sतऑ to g: 1 / 9.806650
	 * g to raw 12 bits चिन्हित, step 0.5mg: 10000 / 5
	 * val in micro (1000000)
	 * val * 10000 / (9.806650 * 1000000 * 5)
	 */
	val64 = val64 * 10000LL;
	/* क्रम rounding, add + or - भागisor (9806650 * 5) भागided by 2 */
	अगर (val64 >= 0)
		val64 += 9806650 * 5 / 2;
	अन्यथा
		val64 -= 9806650 * 5 / 2;
	offset = भाग_s64(val64, 9806650 * 5);

	/* clamp value limited to 12 bits चिन्हित */
	अगर (offset < -2048)
		offset = -2048;
	अन्यथा अगर (offset > 2047)
		offset = 2047;

	pm_runसमय_get_sync(dev);
	mutex_lock(&st->lock);

	चयन (chan->channel2) अणु
	हाल IIO_MOD_X:
		/* OFFSET_USER4 रेजिस्टर is shared */
		ret = regmap_पढ़ो(st->map, INV_ICM42600_REG_OFFSET_USER4,
				  &regval);
		अगर (ret)
			जाओ out_unlock;
		st->buffer[0] = ((offset & 0xF00) >> 4) | (regval & 0x0F);
		st->buffer[1] = offset & 0xFF;
		अवरोध;
	हाल IIO_MOD_Y:
		/* OFFSET_USER7 रेजिस्टर is shared */
		ret = regmap_पढ़ो(st->map, INV_ICM42600_REG_OFFSET_USER7,
				  &regval);
		अगर (ret)
			जाओ out_unlock;
		st->buffer[0] = offset & 0xFF;
		st->buffer[1] = ((offset & 0xF00) >> 8) | (regval & 0xF0);
		अवरोध;
	हाल IIO_MOD_Z:
		/* OFFSET_USER7 रेजिस्टर is shared */
		ret = regmap_पढ़ो(st->map, INV_ICM42600_REG_OFFSET_USER7,
				  &regval);
		अगर (ret)
			जाओ out_unlock;
		st->buffer[0] = ((offset & 0xF00) >> 4) | (regval & 0x0F);
		st->buffer[1] = offset & 0xFF;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	ret = regmap_bulk_ग_लिखो(st->map, reg, st->buffer, 2);

out_unlock:
	mutex_unlock(&st->lock);
	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक inv_icm42600_accel_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				       काष्ठा iio_chan_spec स्थिर *chan,
				       पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा inv_icm42600_state *st = iio_device_get_drvdata(indio_dev);
	पूर्णांक16_t data;
	पूर्णांक ret;

	चयन (chan->type) अणु
	हाल IIO_ACCEL:
		अवरोध;
	हाल IIO_TEMP:
		वापस inv_icm42600_temp_पढ़ो_raw(indio_dev, chan, val, val2, mask);
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;
		ret = inv_icm42600_accel_पढ़ो_sensor(st, chan, &data);
		iio_device_release_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;
		*val = data;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		वापस inv_icm42600_accel_पढ़ो_scale(st, val, val2);
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		वापस inv_icm42600_accel_पढ़ो_odr(st, val, val2);
	हाल IIO_CHAN_INFO_CALIBBIAS:
		वापस inv_icm42600_accel_पढ़ो_offset(st, chan, val, val2);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक inv_icm42600_accel_पढ़ो_avail(काष्ठा iio_dev *indio_dev,
					 काष्ठा iio_chan_spec स्थिर *chan,
					 स्थिर पूर्णांक **vals,
					 पूर्णांक *type, पूर्णांक *length, दीर्घ mask)
अणु
	अगर (chan->type != IIO_ACCEL)
		वापस -EINVAL;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		*vals = inv_icm42600_accel_scale;
		*type = IIO_VAL_INT_PLUS_न_अंकO;
		*length = ARRAY_SIZE(inv_icm42600_accel_scale);
		वापस IIO_AVAIL_LIST;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*vals = inv_icm42600_accel_odr;
		*type = IIO_VAL_INT_PLUS_MICRO;
		*length = ARRAY_SIZE(inv_icm42600_accel_odr);
		वापस IIO_AVAIL_LIST;
	हाल IIO_CHAN_INFO_CALIBBIAS:
		*vals = inv_icm42600_accel_calibbias;
		*type = IIO_VAL_INT_PLUS_MICRO;
		वापस IIO_AVAIL_RANGE;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक inv_icm42600_accel_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
					काष्ठा iio_chan_spec स्थिर *chan,
					पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा inv_icm42600_state *st = iio_device_get_drvdata(indio_dev);
	पूर्णांक ret;

	अगर (chan->type != IIO_ACCEL)
		वापस -EINVAL;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;
		ret = inv_icm42600_accel_ग_लिखो_scale(st, val, val2);
		iio_device_release_direct_mode(indio_dev);
		वापस ret;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		वापस inv_icm42600_accel_ग_लिखो_odr(indio_dev, val, val2);
	हाल IIO_CHAN_INFO_CALIBBIAS:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;
		ret = inv_icm42600_accel_ग_लिखो_offset(st, chan, val, val2);
		iio_device_release_direct_mode(indio_dev);
		वापस ret;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक inv_icm42600_accel_ग_लिखो_raw_get_fmt(काष्ठा iio_dev *indio_dev,
						काष्ठा iio_chan_spec स्थिर *chan,
						दीर्घ mask)
अणु
	अगर (chan->type != IIO_ACCEL)
		वापस -EINVAL;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		वापस IIO_VAL_INT_PLUS_न_अंकO;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_CALIBBIAS:
		वापस IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक inv_icm42600_accel_hwfअगरo_set_watermark(काष्ठा iio_dev *indio_dev,
						   अचिन्हित पूर्णांक val)
अणु
	काष्ठा inv_icm42600_state *st = iio_device_get_drvdata(indio_dev);
	पूर्णांक ret;

	mutex_lock(&st->lock);

	st->fअगरo.watermark.accel = val;
	ret = inv_icm42600_buffer_update_watermark(st);

	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक inv_icm42600_accel_hwfअगरo_flush(काष्ठा iio_dev *indio_dev,
					   अचिन्हित पूर्णांक count)
अणु
	काष्ठा inv_icm42600_state *st = iio_device_get_drvdata(indio_dev);
	पूर्णांक ret;

	अगर (count == 0)
		वापस 0;

	mutex_lock(&st->lock);

	ret = inv_icm42600_buffer_hwfअगरo_flush(st, count);
	अगर (!ret)
		ret = st->fअगरo.nb.accel;

	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info inv_icm42600_accel_info = अणु
	.पढ़ो_raw = inv_icm42600_accel_पढ़ो_raw,
	.पढ़ो_avail = inv_icm42600_accel_पढ़ो_avail,
	.ग_लिखो_raw = inv_icm42600_accel_ग_लिखो_raw,
	.ग_लिखो_raw_get_fmt = inv_icm42600_accel_ग_लिखो_raw_get_fmt,
	.debugfs_reg_access = inv_icm42600_debugfs_reg,
	.update_scan_mode = inv_icm42600_accel_update_scan_mode,
	.hwfअगरo_set_watermark = inv_icm42600_accel_hwfअगरo_set_watermark,
	.hwfअगरo_flush_to_buffer = inv_icm42600_accel_hwfअगरo_flush,
पूर्ण;

काष्ठा iio_dev *inv_icm42600_accel_init(काष्ठा inv_icm42600_state *st)
अणु
	काष्ठा device *dev = regmap_get_device(st->map);
	स्थिर अक्षर *name;
	काष्ठा inv_icm42600_बारtamp *ts;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%s-accel", st->name);
	अगर (!name)
		वापस ERR_PTR(-ENOMEM);

	indio_dev = devm_iio_device_alloc(dev, माप(*ts));
	अगर (!indio_dev)
		वापस ERR_PTR(-ENOMEM);

	ts = iio_priv(indio_dev);
	inv_icm42600_बारtamp_init(ts, inv_icm42600_odr_to_period(st->conf.accel.odr));

	iio_device_set_drvdata(indio_dev, st);
	indio_dev->name = name;
	indio_dev->info = &inv_icm42600_accel_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = inv_icm42600_accel_channels;
	indio_dev->num_channels = ARRAY_SIZE(inv_icm42600_accel_channels);
	indio_dev->available_scan_masks = inv_icm42600_accel_scan_masks;

	ret = devm_iio_kfअगरo_buffer_setup(dev, indio_dev,
					  INDIO_BUFFER_SOFTWARE,
					  &inv_icm42600_buffer_ops);
	अगर (ret)
		वापस ERR_PTR(ret);

	ret = devm_iio_device_रेजिस्टर(dev, indio_dev);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस indio_dev;
पूर्ण

पूर्णांक inv_icm42600_accel_parse_fअगरo(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा inv_icm42600_state *st = iio_device_get_drvdata(indio_dev);
	काष्ठा inv_icm42600_बारtamp *ts = iio_priv(indio_dev);
	sमाप_प्रकार i, size;
	अचिन्हित पूर्णांक no;
	स्थिर व्योम *accel, *gyro, *बारtamp;
	स्थिर पूर्णांक8_t *temp;
	अचिन्हित पूर्णांक odr;
	पूर्णांक64_t ts_val;
	काष्ठा inv_icm42600_accel_buffer buffer;

	/* parse all fअगरo packets */
	क्रम (i = 0, no = 0; i < st->fअगरo.count; i += size, ++no) अणु
		size = inv_icm42600_fअगरo_decode_packet(&st->fअगरo.data[i],
				&accel, &gyro, &temp, &बारtamp, &odr);
		/* quit अगर error or FIFO is empty */
		अगर (size <= 0)
			वापस size;

		/* skip packet अगर no accel data or data is invalid */
		अगर (accel == शून्य || !inv_icm42600_fअगरo_is_data_valid(accel))
			जारी;

		/* update odr */
		अगर (odr & INV_ICM42600_SENSOR_ACCEL)
			inv_icm42600_बारtamp_apply_odr(ts, st->fअगरo.period,
							 st->fअगरo.nb.total, no);

		/* buffer is copied to userspace, zeroing it to aव्योम any data leak */
		स_रखो(&buffer, 0, माप(buffer));
		स_नकल(&buffer.accel, accel, माप(buffer.accel));
		/* convert 8 bits FIFO temperature in high resolution क्रमmat */
		buffer.temp = temp ? (*temp * 64) : 0;
		ts_val = inv_icm42600_बारtamp_pop(ts);
		iio_push_to_buffers_with_बारtamp(indio_dev, &buffer, ts_val);
	पूर्ण

	वापस 0;
पूर्ण
