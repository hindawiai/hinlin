<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम NXP FXAS21002C Gyroscope - Core
 *
 * Copyright (C) 2019 Linaro Ltd.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <linux/iio/events.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>

#समावेश "fxas21002c.h"

#घोषणा FXAS21002C_CHIP_ID_1	0xD6
#घोषणा FXAS21002C_CHIP_ID_2	0xD7

क्रमागत fxas21002c_mode_state अणु
	FXAS21002C_MODE_STANDBY,
	FXAS21002C_MODE_READY,
	FXAS21002C_MODE_ACTIVE,
पूर्ण;

#घोषणा FXAS21002C_STANDBY_ACTIVE_TIME_MS	62
#घोषणा FXAS21002C_READY_ACTIVE_TIME_MS		7

#घोषणा FXAS21002C_ODR_LIST_MAX		10

#घोषणा FXAS21002C_SCALE_FRACTIONAL	32
#घोषणा FXAS21002C_RANGE_LIMIT_DOUBLE	2000

#घोषणा FXAS21002C_AXIS_TO_REG(axis) (FXAS21002C_REG_OUT_X_MSB + ((axis) * 2))

अटल स्थिर काष्ठा reg_field fxas21002c_reg_fields[] = अणु
	[F_DR_STATUS]		= REG_FIELD(FXAS21002C_REG_STATUS, 0, 7),
	[F_OUT_X_MSB]		= REG_FIELD(FXAS21002C_REG_OUT_X_MSB, 0, 7),
	[F_OUT_X_LSB]		= REG_FIELD(FXAS21002C_REG_OUT_X_LSB, 0, 7),
	[F_OUT_Y_MSB]		= REG_FIELD(FXAS21002C_REG_OUT_Y_MSB, 0, 7),
	[F_OUT_Y_LSB]		= REG_FIELD(FXAS21002C_REG_OUT_Y_LSB, 0, 7),
	[F_OUT_Z_MSB]		= REG_FIELD(FXAS21002C_REG_OUT_Z_MSB, 0, 7),
	[F_OUT_Z_LSB]		= REG_FIELD(FXAS21002C_REG_OUT_Z_LSB, 0, 7),
	[F_ZYX_OW]		= REG_FIELD(FXAS21002C_REG_DR_STATUS, 7, 7),
	[F_Z_OW]		= REG_FIELD(FXAS21002C_REG_DR_STATUS, 6, 6),
	[F_Y_OW]		= REG_FIELD(FXAS21002C_REG_DR_STATUS, 5, 5),
	[F_X_OW]		= REG_FIELD(FXAS21002C_REG_DR_STATUS, 4, 4),
	[F_ZYX_DR]		= REG_FIELD(FXAS21002C_REG_DR_STATUS, 3, 3),
	[F_Z_DR]		= REG_FIELD(FXAS21002C_REG_DR_STATUS, 2, 2),
	[F_Y_DR]		= REG_FIELD(FXAS21002C_REG_DR_STATUS, 1, 1),
	[F_X_DR]		= REG_FIELD(FXAS21002C_REG_DR_STATUS, 0, 0),
	[F_OVF]			= REG_FIELD(FXAS21002C_REG_F_STATUS, 7, 7),
	[F_WMKF]		= REG_FIELD(FXAS21002C_REG_F_STATUS, 6, 6),
	[F_CNT]			= REG_FIELD(FXAS21002C_REG_F_STATUS, 0, 5),
	[F_MODE]		= REG_FIELD(FXAS21002C_REG_F_SETUP, 6, 7),
	[F_WMRK]		= REG_FIELD(FXAS21002C_REG_F_SETUP, 0, 5),
	[F_EVENT]		= REG_FIELD(FXAS21002C_REG_F_EVENT, 5, 5),
	[FE_TIME]		= REG_FIELD(FXAS21002C_REG_F_EVENT, 0, 4),
	[F_BOOTEND]		= REG_FIELD(FXAS21002C_REG_INT_SRC_FLAG, 3, 3),
	[F_SRC_FIFO]		= REG_FIELD(FXAS21002C_REG_INT_SRC_FLAG, 2, 2),
	[F_SRC_RT]		= REG_FIELD(FXAS21002C_REG_INT_SRC_FLAG, 1, 1),
	[F_SRC_DRDY]		= REG_FIELD(FXAS21002C_REG_INT_SRC_FLAG, 0, 0),
	[F_WHO_AM_I]		= REG_FIELD(FXAS21002C_REG_WHO_AM_I, 0, 7),
	[F_BW]			= REG_FIELD(FXAS21002C_REG_CTRL0, 6, 7),
	[F_SPIW]		= REG_FIELD(FXAS21002C_REG_CTRL0, 5, 5),
	[F_SEL]			= REG_FIELD(FXAS21002C_REG_CTRL0, 3, 4),
	[F_HPF_EN]		= REG_FIELD(FXAS21002C_REG_CTRL0, 2, 2),
	[F_FS]			= REG_FIELD(FXAS21002C_REG_CTRL0, 0, 1),
	[F_ELE]			= REG_FIELD(FXAS21002C_REG_RT_CFG, 3, 3),
	[F_ZTEFE]		= REG_FIELD(FXAS21002C_REG_RT_CFG, 2, 2),
	[F_YTEFE]		= REG_FIELD(FXAS21002C_REG_RT_CFG, 1, 1),
	[F_XTEFE]		= REG_FIELD(FXAS21002C_REG_RT_CFG, 0, 0),
	[F_EA]			= REG_FIELD(FXAS21002C_REG_RT_SRC, 6, 6),
	[F_ZRT]			= REG_FIELD(FXAS21002C_REG_RT_SRC, 5, 5),
	[F_ZRT_POL]		= REG_FIELD(FXAS21002C_REG_RT_SRC, 4, 4),
	[F_YRT]			= REG_FIELD(FXAS21002C_REG_RT_SRC, 3, 3),
	[F_YRT_POL]		= REG_FIELD(FXAS21002C_REG_RT_SRC, 2, 2),
	[F_XRT]			= REG_FIELD(FXAS21002C_REG_RT_SRC, 1, 1),
	[F_XRT_POL]		= REG_FIELD(FXAS21002C_REG_RT_SRC, 0, 0),
	[F_DBCNTM]		= REG_FIELD(FXAS21002C_REG_RT_THS, 7, 7),
	[F_THS]			= REG_FIELD(FXAS21002C_REG_RT_SRC, 0, 6),
	[F_RT_COUNT]		= REG_FIELD(FXAS21002C_REG_RT_COUNT, 0, 7),
	[F_TEMP]		= REG_FIELD(FXAS21002C_REG_TEMP, 0, 7),
	[F_RST]			= REG_FIELD(FXAS21002C_REG_CTRL1, 6, 6),
	[F_ST]			= REG_FIELD(FXAS21002C_REG_CTRL1, 5, 5),
	[F_DR]			= REG_FIELD(FXAS21002C_REG_CTRL1, 2, 4),
	[F_ACTIVE]		= REG_FIELD(FXAS21002C_REG_CTRL1, 1, 1),
	[F_READY]		= REG_FIELD(FXAS21002C_REG_CTRL1, 0, 0),
	[F_INT_CFG_FIFO]	= REG_FIELD(FXAS21002C_REG_CTRL2, 7, 7),
	[F_INT_EN_FIFO]		= REG_FIELD(FXAS21002C_REG_CTRL2, 6, 6),
	[F_INT_CFG_RT]		= REG_FIELD(FXAS21002C_REG_CTRL2, 5, 5),
	[F_INT_EN_RT]		= REG_FIELD(FXAS21002C_REG_CTRL2, 4, 4),
	[F_INT_CFG_DRDY]	= REG_FIELD(FXAS21002C_REG_CTRL2, 3, 3),
	[F_INT_EN_DRDY]		= REG_FIELD(FXAS21002C_REG_CTRL2, 2, 2),
	[F_IPOL]		= REG_FIELD(FXAS21002C_REG_CTRL2, 1, 1),
	[F_PP_OD]		= REG_FIELD(FXAS21002C_REG_CTRL2, 0, 0),
	[F_WRAPTOONE]		= REG_FIELD(FXAS21002C_REG_CTRL3, 3, 3),
	[F_EXTCTRLEN]		= REG_FIELD(FXAS21002C_REG_CTRL3, 2, 2),
	[F_FS_DOUBLE]		= REG_FIELD(FXAS21002C_REG_CTRL3, 0, 0),
पूर्ण;

अटल स्थिर पूर्णांक fxas21002c_odr_values[] = अणु
	800, 400, 200, 100, 50, 25, 12, 12
पूर्ण;

/*
 * These values are taken from the low-pass filter cutoff frequency calculated
 * ODR * 0.lpf_values. So, क्रम ODR = 800Hz with a lpf value = 0.32
 * => LPF cutoff frequency = 800 * 0.32 = 256 Hz
 */
अटल स्थिर पूर्णांक fxas21002c_lpf_values[] = अणु
	32, 16, 8
पूर्ण;

/*
 * These values are taken from the high-pass filter cutoff frequency calculated
 * ODR * 0.0hpf_values. So, क्रम ODR = 800Hz with a hpf value = 0.018750
 * => HPF cutoff frequency = 800 * 0.018750 = 15 Hz
 */
अटल स्थिर पूर्णांक fxas21002c_hpf_values[] = अणु
	18750, 9625, 4875, 2475
पूर्ण;

अटल स्थिर पूर्णांक fxas21002c_range_values[] = अणु
	4000, 2000, 1000, 500, 250
पूर्ण;

काष्ठा fxas21002c_data अणु
	u8 chip_id;
	क्रमागत fxas21002c_mode_state mode;
	क्रमागत fxas21002c_mode_state prev_mode;

	काष्ठा mutex lock;		/* serialize data access */
	काष्ठा regmap *regmap;
	काष्ठा regmap_field *regmap_fields[F_MAX_FIELDS];
	काष्ठा iio_trigger *dपढ़ोy_trig;
	s64 बारtamp;
	पूर्णांक irq;

	काष्ठा regulator *vdd;
	काष्ठा regulator *vddio;

	/*
	 * DMA (thus cache coherency मुख्यtenance) requires the
	 * transfer buffers to live in their own cache lines.
	 */
	s16 buffer[8] ____cacheline_aligned;
पूर्ण;

क्रमागत fxas21002c_channel_index अणु
	CHANNEL_SCAN_INDEX_X,
	CHANNEL_SCAN_INDEX_Y,
	CHANNEL_SCAN_INDEX_Z,
	CHANNEL_SCAN_MAX,
पूर्ण;

अटल पूर्णांक fxas21002c_odr_hz_from_value(काष्ठा fxas21002c_data *data, u8 value)
अणु
	पूर्णांक odr_value_max = ARRAY_SIZE(fxas21002c_odr_values) - 1;

	value = min_t(u8, value, odr_value_max);

	वापस fxas21002c_odr_values[value];
पूर्ण

अटल पूर्णांक fxas21002c_odr_value_from_hz(काष्ठा fxas21002c_data *data,
					अचिन्हित पूर्णांक hz)
अणु
	पूर्णांक odr_table_size = ARRAY_SIZE(fxas21002c_odr_values);
	पूर्णांक i;

	क्रम (i = 0; i < odr_table_size; i++)
		अगर (fxas21002c_odr_values[i] == hz)
			वापस i;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक fxas21002c_lpf_bw_from_value(काष्ठा fxas21002c_data *data, u8 value)
अणु
	पूर्णांक lpf_value_max = ARRAY_SIZE(fxas21002c_lpf_values) - 1;

	value = min_t(u8, value, lpf_value_max);

	वापस fxas21002c_lpf_values[value];
पूर्ण

अटल पूर्णांक fxas21002c_lpf_value_from_bw(काष्ठा fxas21002c_data *data,
					अचिन्हित पूर्णांक hz)
अणु
	पूर्णांक lpf_table_size = ARRAY_SIZE(fxas21002c_lpf_values);
	पूर्णांक i;

	क्रम (i = 0; i < lpf_table_size; i++)
		अगर (fxas21002c_lpf_values[i] == hz)
			वापस i;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक fxas21002c_hpf_sel_from_value(काष्ठा fxas21002c_data *data, u8 value)
अणु
	पूर्णांक hpf_value_max = ARRAY_SIZE(fxas21002c_hpf_values) - 1;

	value = min_t(u8, value, hpf_value_max);

	वापस fxas21002c_hpf_values[value];
पूर्ण

अटल पूर्णांक fxas21002c_hpf_value_from_sel(काष्ठा fxas21002c_data *data,
					 अचिन्हित पूर्णांक hz)
अणु
	पूर्णांक hpf_table_size = ARRAY_SIZE(fxas21002c_hpf_values);
	पूर्णांक i;

	क्रम (i = 0; i < hpf_table_size; i++)
		अगर (fxas21002c_hpf_values[i] == hz)
			वापस i;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक fxas21002c_range_fs_from_value(काष्ठा fxas21002c_data *data,
					  u8 value)
अणु
	पूर्णांक range_value_max = ARRAY_SIZE(fxas21002c_range_values) - 1;
	अचिन्हित पूर्णांक fs_द्विगुन;
	पूर्णांक ret;

	/* We need to check अगर FS_DOUBLE is enabled to offset the value */
	ret = regmap_field_पढ़ो(data->regmap_fields[F_FS_DOUBLE], &fs_द्विगुन);
	अगर (ret < 0)
		वापस ret;

	अगर (!fs_द्विगुन)
		value += 1;

	value = min_t(u8, value, range_value_max);

	वापस fxas21002c_range_values[value];
पूर्ण

अटल पूर्णांक fxas21002c_range_value_from_fs(काष्ठा fxas21002c_data *data,
					  अचिन्हित पूर्णांक range)
अणु
	पूर्णांक range_table_size = ARRAY_SIZE(fxas21002c_range_values);
	bool found = false;
	पूर्णांक fs_द्विगुन = 0;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < range_table_size; i++)
		अगर (fxas21002c_range_values[i] == range) अणु
			found = true;
			अवरोध;
		पूर्ण

	अगर (!found)
		वापस -EINVAL;

	अगर (range > FXAS21002C_RANGE_LIMIT_DOUBLE)
		fs_द्विगुन = 1;

	ret = regmap_field_ग_लिखो(data->regmap_fields[F_FS_DOUBLE], fs_द्विगुन);
	अगर (ret < 0)
		वापस ret;

	वापस i;
पूर्ण

अटल पूर्णांक fxas21002c_mode_get(काष्ठा fxas21002c_data *data)
अणु
	अचिन्हित पूर्णांक active;
	अचिन्हित पूर्णांक पढ़ोy;
	पूर्णांक ret;

	ret = regmap_field_पढ़ो(data->regmap_fields[F_ACTIVE], &active);
	अगर (ret < 0)
		वापस ret;
	अगर (active)
		वापस FXAS21002C_MODE_ACTIVE;

	ret = regmap_field_पढ़ो(data->regmap_fields[F_READY], &पढ़ोy);
	अगर (ret < 0)
		वापस ret;
	अगर (पढ़ोy)
		वापस FXAS21002C_MODE_READY;

	वापस FXAS21002C_MODE_STANDBY;
पूर्ण

अटल पूर्णांक fxas21002c_mode_set(काष्ठा fxas21002c_data *data,
			       क्रमागत fxas21002c_mode_state mode)
अणु
	पूर्णांक ret;

	अगर (mode == data->mode)
		वापस 0;

	अगर (mode == FXAS21002C_MODE_READY)
		ret = regmap_field_ग_लिखो(data->regmap_fields[F_READY], 1);
	अन्यथा
		ret = regmap_field_ग_लिखो(data->regmap_fields[F_READY], 0);
	अगर (ret < 0)
		वापस ret;

	अगर (mode == FXAS21002C_MODE_ACTIVE)
		ret = regmap_field_ग_लिखो(data->regmap_fields[F_ACTIVE], 1);
	अन्यथा
		ret = regmap_field_ग_लिखो(data->regmap_fields[F_ACTIVE], 0);
	अगर (ret < 0)
		वापस ret;

	/* अगर going to active रुको the setup बार */
	अगर (mode == FXAS21002C_MODE_ACTIVE &&
	    data->mode == FXAS21002C_MODE_STANDBY)
		msleep_पूर्णांकerruptible(FXAS21002C_STANDBY_ACTIVE_TIME_MS);

	अगर (data->mode == FXAS21002C_MODE_READY)
		msleep_पूर्णांकerruptible(FXAS21002C_READY_ACTIVE_TIME_MS);

	data->prev_mode = data->mode;
	data->mode = mode;

	वापस ret;
पूर्ण

अटल पूर्णांक fxas21002c_ग_लिखो(काष्ठा fxas21002c_data *data,
			    क्रमागत fxas21002c_fields field, पूर्णांक bits)
अणु
	पूर्णांक actual_mode;
	पूर्णांक ret;

	mutex_lock(&data->lock);

	actual_mode = fxas21002c_mode_get(data);
	अगर (actual_mode < 0) अणु
		ret = actual_mode;
		जाओ out_unlock;
	पूर्ण

	ret = fxas21002c_mode_set(data, FXAS21002C_MODE_READY);
	अगर (ret < 0)
		जाओ out_unlock;

	ret = regmap_field_ग_लिखो(data->regmap_fields[field], bits);
	अगर (ret < 0)
		जाओ out_unlock;

	ret = fxas21002c_mode_set(data, data->prev_mode);

out_unlock:
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक  fxas21002c_pm_get(काष्ठा fxas21002c_data *data)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0)
		pm_runसमय_put_noidle(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक  fxas21002c_pm_put(काष्ठा fxas21002c_data *data)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);

	pm_runसमय_mark_last_busy(dev);

	वापस pm_runसमय_put_स्वतःsuspend(dev);
पूर्ण

अटल पूर्णांक fxas21002c_temp_get(काष्ठा fxas21002c_data *data, पूर्णांक *val)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);
	अचिन्हित पूर्णांक temp;
	पूर्णांक ret;

	mutex_lock(&data->lock);
	ret = fxas21002c_pm_get(data);
	अगर (ret < 0)
		जाओ data_unlock;

	ret = regmap_field_पढ़ो(data->regmap_fields[F_TEMP], &temp);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read temp: %d\n", ret);
		fxas21002c_pm_put(data);
		जाओ data_unlock;
	पूर्ण

	*val = sign_extend32(temp, 7);

	ret = fxas21002c_pm_put(data);
	अगर (ret < 0)
		जाओ data_unlock;

	ret = IIO_VAL_INT;

data_unlock:
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक fxas21002c_axis_get(काष्ठा fxas21002c_data *data,
			       पूर्णांक index, पूर्णांक *val)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);
	__be16 axis_be;
	पूर्णांक ret;

	mutex_lock(&data->lock);
	ret = fxas21002c_pm_get(data);
	अगर (ret < 0)
		जाओ data_unlock;

	ret = regmap_bulk_पढ़ो(data->regmap, FXAS21002C_AXIS_TO_REG(index),
			       &axis_be, माप(axis_be));
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read axis: %d: %d\n", index, ret);
		fxas21002c_pm_put(data);
		जाओ data_unlock;
	पूर्ण

	*val = sign_extend32(be16_to_cpu(axis_be), 15);

	ret = fxas21002c_pm_put(data);
	अगर (ret < 0)
		जाओ data_unlock;

	ret = IIO_VAL_INT;

data_unlock:
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक fxas21002c_odr_get(काष्ठा fxas21002c_data *data, पूर्णांक *odr)
अणु
	अचिन्हित पूर्णांक odr_bits;
	पूर्णांक ret;

	mutex_lock(&data->lock);
	ret = regmap_field_पढ़ो(data->regmap_fields[F_DR], &odr_bits);
	अगर (ret < 0)
		जाओ data_unlock;

	*odr = fxas21002c_odr_hz_from_value(data, odr_bits);

	ret = IIO_VAL_INT;

data_unlock:
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक fxas21002c_odr_set(काष्ठा fxas21002c_data *data, पूर्णांक odr)
अणु
	पूर्णांक odr_bits;

	odr_bits = fxas21002c_odr_value_from_hz(data, odr);
	अगर (odr_bits < 0)
		वापस odr_bits;

	वापस fxas21002c_ग_लिखो(data, F_DR, odr_bits);
पूर्ण

अटल पूर्णांक fxas21002c_lpf_get(काष्ठा fxas21002c_data *data, पूर्णांक *val2)
अणु
	अचिन्हित पूर्णांक bw_bits;
	पूर्णांक ret;

	mutex_lock(&data->lock);
	ret = regmap_field_पढ़ो(data->regmap_fields[F_BW], &bw_bits);
	अगर (ret < 0)
		जाओ data_unlock;

	*val2 = fxas21002c_lpf_bw_from_value(data, bw_bits) * 10000;

	ret = IIO_VAL_INT_PLUS_MICRO;

data_unlock:
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक fxas21002c_lpf_set(काष्ठा fxas21002c_data *data, पूर्णांक bw)
अणु
	पूर्णांक bw_bits;
	पूर्णांक odr;
	पूर्णांक ret;

	bw_bits = fxas21002c_lpf_value_from_bw(data, bw);
	अगर (bw_bits < 0)
		वापस bw_bits;

	/*
	 * From table 33 of the device spec, क्रम ODR = 25Hz and 12.5 value 0.08
	 * is not allowed and क्रम ODR = 12.5 value 0.16 is also not allowed
	 */
	ret = fxas21002c_odr_get(data, &odr);
	अगर (ret < 0)
		वापस -EINVAL;

	अगर ((odr == 25 && bw_bits > 0x01) || (odr == 12 && bw_bits > 0))
		वापस -EINVAL;

	वापस fxas21002c_ग_लिखो(data, F_BW, bw_bits);
पूर्ण

अटल पूर्णांक fxas21002c_hpf_get(काष्ठा fxas21002c_data *data, पूर्णांक *val2)
अणु
	अचिन्हित पूर्णांक sel_bits;
	पूर्णांक ret;

	mutex_lock(&data->lock);
	ret = regmap_field_पढ़ो(data->regmap_fields[F_SEL], &sel_bits);
	अगर (ret < 0)
		जाओ data_unlock;

	*val2 = fxas21002c_hpf_sel_from_value(data, sel_bits);

	ret = IIO_VAL_INT_PLUS_MICRO;

data_unlock:
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक fxas21002c_hpf_set(काष्ठा fxas21002c_data *data, पूर्णांक sel)
अणु
	पूर्णांक sel_bits;

	sel_bits = fxas21002c_hpf_value_from_sel(data, sel);
	अगर (sel_bits < 0)
		वापस sel_bits;

	वापस fxas21002c_ग_लिखो(data, F_SEL, sel_bits);
पूर्ण

अटल पूर्णांक fxas21002c_scale_get(काष्ठा fxas21002c_data *data, पूर्णांक *val)
अणु
	पूर्णांक fs_bits;
	पूर्णांक scale;
	पूर्णांक ret;

	mutex_lock(&data->lock);
	ret = regmap_field_पढ़ो(data->regmap_fields[F_FS], &fs_bits);
	अगर (ret < 0)
		जाओ data_unlock;

	scale = fxas21002c_range_fs_from_value(data, fs_bits);
	अगर (scale < 0) अणु
		ret = scale;
		जाओ data_unlock;
	पूर्ण

	*val = scale;

data_unlock:
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक fxas21002c_scale_set(काष्ठा fxas21002c_data *data, पूर्णांक range)
अणु
	पूर्णांक fs_bits;

	fs_bits = fxas21002c_range_value_from_fs(data, range);
	अगर (fs_bits < 0)
		वापस fs_bits;

	वापस fxas21002c_ग_लिखो(data, F_FS, fs_bits);
पूर्ण

अटल पूर्णांक fxas21002c_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
			       पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा fxas21002c_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		चयन (chan->type) अणु
		हाल IIO_TEMP:
			वापस fxas21002c_temp_get(data, val);
		हाल IIO_ANGL_VEL:
			वापस fxas21002c_axis_get(data, chan->scan_index, val);
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_ANGL_VEL:
			*val2 = FXAS21002C_SCALE_FRACTIONAL;
			ret = fxas21002c_scale_get(data, val);
			अगर (ret < 0)
				वापस ret;

			वापस IIO_VAL_FRACTIONAL;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		*val = 0;
		वापस fxas21002c_lpf_get(data, val2);
	हाल IIO_CHAN_INFO_HIGH_PASS_FILTER_3DB_FREQUENCY:
		*val = 0;
		वापस fxas21002c_hpf_get(data, val2);
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*val2 = 0;
		वापस fxas21002c_odr_get(data, val);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक fxas21002c_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val,
				पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा fxas21002c_data *data = iio_priv(indio_dev);
	पूर्णांक range;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		अगर (val2)
			वापस -EINVAL;

		वापस fxas21002c_odr_set(data, val);
	हाल IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		अगर (val)
			वापस -EINVAL;

		val2 = val2 / 10000;
		वापस fxas21002c_lpf_set(data, val2);
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_ANGL_VEL:
			range = (((val * 1000 + val2 / 1000) *
				  FXAS21002C_SCALE_FRACTIONAL) / 1000);
			वापस fxas21002c_scale_set(data, range);
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_HIGH_PASS_FILTER_3DB_FREQUENCY:
		वापस fxas21002c_hpf_set(data, val2);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल IIO_CONST_ATTR_SAMP_FREQ_AVAIL("12.5 25 50 100 200 400 800");

अटल IIO_CONST_ATTR(in_anglvel_filter_low_pass_3db_frequency_available,
		      "0.32 0.16 0.08");

अटल IIO_CONST_ATTR(in_anglvel_filter_high_pass_3db_frequency_available,
		      "0.018750 0.009625 0.004875 0.002475");

अटल IIO_CONST_ATTR(in_anglvel_scale_available,
		      "125.0 62.5 31.25 15.625 7.8125");

अटल काष्ठा attribute *fxas21002c_attributes[] = अणु
	&iio_स्थिर_attr_sampling_frequency_available.dev_attr.attr,
	&iio_स्थिर_attr_in_anglvel_filter_low_pass_3db_frequency_available.dev_attr.attr,
	&iio_स्थिर_attr_in_anglvel_filter_high_pass_3db_frequency_available.dev_attr.attr,
	&iio_स्थिर_attr_in_anglvel_scale_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group fxas21002c_attrs_group = अणु
	.attrs = fxas21002c_attributes,
पूर्ण;

#घोषणा FXAS21002C_CHANNEL(_axis) अणु					\
	.type = IIO_ANGL_VEL,						\
	.modअगरied = 1,							\
	.channel2 = IIO_MOD_##_axis,					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),			\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) |		\
		BIT(IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY) |	\
		BIT(IIO_CHAN_INFO_HIGH_PASS_FILTER_3DB_FREQUENCY) |	\
		BIT(IIO_CHAN_INFO_SAMP_FREQ),				\
	.scan_index = CHANNEL_SCAN_INDEX_##_axis,			\
	.scan_type = अणु							\
		.sign = 's',						\
		.realbits = 16,						\
		.storagebits = 16,					\
		.endianness = IIO_BE,					\
	पूर्ण,								\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec fxas21002c_channels[] = अणु
	अणु
		.type = IIO_TEMP,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.scan_index = -1,
	पूर्ण,
	FXAS21002C_CHANNEL(X),
	FXAS21002C_CHANNEL(Y),
	FXAS21002C_CHANNEL(Z),
पूर्ण;

अटल स्थिर काष्ठा iio_info fxas21002c_info = अणु
	.attrs			= &fxas21002c_attrs_group,
	.पढ़ो_raw		= &fxas21002c_पढ़ो_raw,
	.ग_लिखो_raw		= &fxas21002c_ग_लिखो_raw,
पूर्ण;

अटल irqवापस_t fxas21002c_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा fxas21002c_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->lock);
	ret = regmap_bulk_पढ़ो(data->regmap, FXAS21002C_REG_OUT_X_MSB,
			       data->buffer, CHANNEL_SCAN_MAX * माप(s16));
	अगर (ret < 0)
		जाओ out_unlock;

	iio_push_to_buffers_with_बारtamp(indio_dev, data->buffer,
					   data->बारtamp);

out_unlock:
	mutex_unlock(&data->lock);

	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक fxas21002c_chip_init(काष्ठा fxas21002c_data *data)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);
	अचिन्हित पूर्णांक chip_id;
	पूर्णांक ret;

	ret = regmap_field_पढ़ो(data->regmap_fields[F_WHO_AM_I], &chip_id);
	अगर (ret < 0)
		वापस ret;

	अगर (chip_id != FXAS21002C_CHIP_ID_1 &&
	    chip_id != FXAS21002C_CHIP_ID_2) अणु
		dev_err(dev, "chip id 0x%02x is not supported\n", chip_id);
		वापस -EINVAL;
	पूर्ण

	data->chip_id = chip_id;

	ret = fxas21002c_mode_set(data, FXAS21002C_MODE_STANDBY);
	अगर (ret < 0)
		वापस ret;

	/* Set ODR to 200HZ as शेष */
	ret = fxas21002c_odr_set(data, 200);
	अगर (ret < 0)
		dev_err(dev, "failed to set ODR: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक fxas21002c_data_rdy_trigger_set_state(काष्ठा iio_trigger *trig,
						 bool state)
अणु
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	काष्ठा fxas21002c_data *data = iio_priv(indio_dev);

	वापस regmap_field_ग_लिखो(data->regmap_fields[F_INT_EN_DRDY], state);
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops fxas21002c_trigger_ops = अणु
	.set_trigger_state = &fxas21002c_data_rdy_trigger_set_state,
पूर्ण;

अटल irqवापस_t fxas21002c_data_rdy_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा fxas21002c_data *data = iio_priv(indio_dev);

	data->बारtamp = iio_get_समय_ns(indio_dev);

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t fxas21002c_data_rdy_thपढ़ो(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा fxas21002c_data *data = iio_priv(indio_dev);
	अचिन्हित पूर्णांक data_पढ़ोy;
	पूर्णांक ret;

	ret = regmap_field_पढ़ो(data->regmap_fields[F_SRC_DRDY], &data_पढ़ोy);
	अगर (ret < 0)
		वापस IRQ_NONE;

	अगर (!data_पढ़ोy)
		वापस IRQ_NONE;

	iio_trigger_poll_chained(data->dपढ़ोy_trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक fxas21002c_trigger_probe(काष्ठा fxas21002c_data *data)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा device_node *np = indio_dev->dev.of_node;
	अचिन्हित दीर्घ irq_trig;
	bool irq_खोलो_drain;
	पूर्णांक irq1;
	पूर्णांक ret;

	अगर (!data->irq)
		वापस 0;

	irq1 = of_irq_get_byname(np, "INT1");

	अगर (irq1 == data->irq) अणु
		dev_info(dev, "using interrupt line INT1\n");
		ret = regmap_field_ग_लिखो(data->regmap_fields[F_INT_CFG_DRDY],
					 1);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	dev_info(dev, "using interrupt line INT2\n");

	irq_खोलो_drain = of_property_पढ़ो_bool(np, "drive-open-drain");

	data->dपढ़ोy_trig = devm_iio_trigger_alloc(dev, "%s-dev%d",
						   indio_dev->name,
						   indio_dev->id);
	अगर (!data->dपढ़ोy_trig)
		वापस -ENOMEM;

	irq_trig = irqd_get_trigger_type(irq_get_irq_data(data->irq));

	अगर (irq_trig == IRQF_TRIGGER_RISING) अणु
		ret = regmap_field_ग_लिखो(data->regmap_fields[F_IPOL], 1);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (irq_खोलो_drain)
		irq_trig |= IRQF_SHARED;

	ret = devm_request_thपढ़ोed_irq(dev, data->irq,
					fxas21002c_data_rdy_handler,
					fxas21002c_data_rdy_thपढ़ो,
					irq_trig, "fxas21002c_data_ready",
					indio_dev);
	अगर (ret < 0)
		वापस ret;

	data->dपढ़ोy_trig->ops = &fxas21002c_trigger_ops;
	iio_trigger_set_drvdata(data->dपढ़ोy_trig, indio_dev);

	वापस devm_iio_trigger_रेजिस्टर(dev, data->dपढ़ोy_trig);
पूर्ण

अटल पूर्णांक fxas21002c_घातer_enable(काष्ठा fxas21002c_data *data)
अणु
	पूर्णांक ret;

	ret = regulator_enable(data->vdd);
	अगर (ret < 0)
		वापस ret;

	ret = regulator_enable(data->vddio);
	अगर (ret < 0) अणु
		regulator_disable(data->vdd);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम fxas21002c_घातer_disable(काष्ठा fxas21002c_data *data)
अणु
	regulator_disable(data->vdd);
	regulator_disable(data->vddio);
पूर्ण

अटल व्योम fxas21002c_घातer_disable_action(व्योम *_data)
अणु
	काष्ठा fxas21002c_data *data = _data;

	fxas21002c_घातer_disable(data);
पूर्ण

अटल पूर्णांक fxas21002c_regulators_get(काष्ठा fxas21002c_data *data)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);

	data->vdd = devm_regulator_get(dev->parent, "vdd");
	अगर (IS_ERR(data->vdd))
		वापस PTR_ERR(data->vdd);

	data->vddio = devm_regulator_get(dev->parent, "vddio");

	वापस PTR_ERR_OR_ZERO(data->vddio);
पूर्ण

पूर्णांक fxas21002c_core_probe(काष्ठा device *dev, काष्ठा regmap *regmap, पूर्णांक irq,
			  स्थिर अक्षर *name)
अणु
	काष्ठा fxas21002c_data *data;
	काष्ठा iio_dev *indio_dev;
	काष्ठा regmap_field *f;
	पूर्णांक i;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	dev_set_drvdata(dev, indio_dev);
	data->irq = irq;
	data->regmap = regmap;

	क्रम (i = 0; i < F_MAX_FIELDS; i++) अणु
		f = devm_regmap_field_alloc(dev, data->regmap,
					    fxas21002c_reg_fields[i]);
		अगर (IS_ERR(f))
			वापस PTR_ERR(f);

		data->regmap_fields[i] = f;
	पूर्ण

	mutex_init(&data->lock);

	ret = fxas21002c_regulators_get(data);
	अगर (ret < 0)
		वापस ret;

	ret = fxas21002c_घातer_enable(data);
	अगर (ret < 0)
		वापस ret;

	ret = devm_add_action_or_reset(dev, fxas21002c_घातer_disable_action,
				       data);
	अगर (ret < 0)
		वापस ret;

	ret = fxas21002c_chip_init(data);
	अगर (ret < 0)
		वापस ret;

	indio_dev->channels = fxas21002c_channels;
	indio_dev->num_channels = ARRAY_SIZE(fxas21002c_channels);
	indio_dev->name = name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &fxas21002c_info;

	ret = fxas21002c_trigger_probe(data);
	अगर (ret < 0)
		वापस ret;

	ret = devm_iio_triggered_buffer_setup(dev, indio_dev, शून्य,
					      fxas21002c_trigger_handler, शून्य);
	अगर (ret < 0)
		वापस ret;

	ret = pm_runसमय_set_active(dev);
	अगर (ret)
		वापस ret;

	pm_runसमय_enable(dev);
	pm_runसमय_set_स्वतःsuspend_delay(dev, 2000);
	pm_runसमय_use_स्वतःsuspend(dev);

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0)
		जाओ pm_disable;

	वापस 0;

pm_disable:
	pm_runसमय_disable(dev);
	pm_runसमय_set_suspended(dev);
	pm_runसमय_put_noidle(dev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(fxas21002c_core_probe);

व्योम fxas21002c_core_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);

	iio_device_unरेजिस्टर(indio_dev);

	pm_runसमय_disable(dev);
	pm_runसमय_set_suspended(dev);
	pm_runसमय_put_noidle(dev);
पूर्ण
EXPORT_SYMBOL_GPL(fxas21002c_core_हटाओ);

अटल पूर्णांक __maybe_unused fxas21002c_suspend(काष्ठा device *dev)
अणु
	काष्ठा fxas21002c_data *data = iio_priv(dev_get_drvdata(dev));

	fxas21002c_mode_set(data, FXAS21002C_MODE_STANDBY);
	fxas21002c_घातer_disable(data);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused fxas21002c_resume(काष्ठा device *dev)
अणु
	काष्ठा fxas21002c_data *data = iio_priv(dev_get_drvdata(dev));
	पूर्णांक ret;

	ret = fxas21002c_घातer_enable(data);
	अगर (ret < 0)
		वापस ret;

	वापस fxas21002c_mode_set(data, data->prev_mode);
पूर्ण

अटल पूर्णांक __maybe_unused fxas21002c_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा fxas21002c_data *data = iio_priv(dev_get_drvdata(dev));

	वापस fxas21002c_mode_set(data, FXAS21002C_MODE_READY);
पूर्ण

अटल पूर्णांक __maybe_unused fxas21002c_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा fxas21002c_data *data = iio_priv(dev_get_drvdata(dev));

	वापस fxas21002c_mode_set(data, FXAS21002C_MODE_ACTIVE);
पूर्ण

स्थिर काष्ठा dev_pm_ops fxas21002c_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(fxas21002c_suspend, fxas21002c_resume)
	SET_RUNTIME_PM_OPS(fxas21002c_runसमय_suspend,
			   fxas21002c_runसमय_resume, शून्य)
पूर्ण;
EXPORT_SYMBOL_GPL(fxas21002c_pm_ops);

MODULE_AUTHOR("Rui Miguel Silva <rui.silva@linaro.org>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("FXAS21002C Gyro driver");
