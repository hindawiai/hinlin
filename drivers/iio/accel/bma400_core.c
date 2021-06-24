<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Core IIO driver क्रम Bosch BMA400 triaxial acceleration sensor.
 *
 * Copyright 2019 Dan Robertson <dan@dlrobertson.com>
 *
 * TODO:
 *  - Support क्रम घातer management
 *  - Support events and पूर्णांकerrupts
 *  - Create channel क्रम step count
 *  - Create channel क्रम sensor समय
 */

#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>

#समावेश "bma400.h"

/*
 * The G-range selection may be one of 2g, 4g, 8, or 16g. The scale may
 * be selected with the acc_range bits of the ACC_CONFIG1 रेजिस्टर.
 * NB: This buffer is populated in the device init.
 */
अटल पूर्णांक bma400_scales[8];

/*
 * See the ACC_CONFIG1 section of the datasheet.
 * NB: This buffer is populated in the device init.
 */
अटल पूर्णांक bma400_sample_freqs[14];

अटल स्थिर पूर्णांक bma400_osr_range[] = अणु 0, 1, 3 पूर्ण;

/* See the ACC_CONFIG0 section of the datasheet */
क्रमागत bma400_घातer_mode अणु
	POWER_MODE_SLEEP   = 0x00,
	POWER_MODE_LOW     = 0x01,
	POWER_MODE_NORMAL  = 0x02,
	POWER_MODE_INVALID = 0x03,
पूर्ण;

काष्ठा bma400_sample_freq अणु
	पूर्णांक hz;
	पूर्णांक uhz;
पूर्ण;

काष्ठा bma400_data अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा regulator_bulk_data regulators[BMA400_NUM_REGULATORS];
	काष्ठा mutex mutex; /* data रेजिस्टर lock */
	काष्ठा iio_mount_matrix orientation;
	क्रमागत bma400_घातer_mode घातer_mode;
	काष्ठा bma400_sample_freq sample_freq;
	पूर्णांक oversampling_ratio;
	पूर्णांक scale;
पूर्ण;

अटल bool bma400_is_writable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल BMA400_CHIP_ID_REG:
	हाल BMA400_ERR_REG:
	हाल BMA400_STATUS_REG:
	हाल BMA400_X_AXIS_LSB_REG:
	हाल BMA400_X_AXIS_MSB_REG:
	हाल BMA400_Y_AXIS_LSB_REG:
	हाल BMA400_Y_AXIS_MSB_REG:
	हाल BMA400_Z_AXIS_LSB_REG:
	हाल BMA400_Z_AXIS_MSB_REG:
	हाल BMA400_SENSOR_TIME0:
	हाल BMA400_SENSOR_TIME1:
	हाल BMA400_SENSOR_TIME2:
	हाल BMA400_EVENT_REG:
	हाल BMA400_INT_STAT0_REG:
	हाल BMA400_INT_STAT1_REG:
	हाल BMA400_INT_STAT2_REG:
	हाल BMA400_TEMP_DATA_REG:
	हाल BMA400_FIFO_LENGTH0_REG:
	हाल BMA400_FIFO_LENGTH1_REG:
	हाल BMA400_FIFO_DATA_REG:
	हाल BMA400_STEP_CNT0_REG:
	हाल BMA400_STEP_CNT1_REG:
	हाल BMA400_STEP_CNT3_REG:
	हाल BMA400_STEP_STAT_REG:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल bool bma400_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल BMA400_ERR_REG:
	हाल BMA400_STATUS_REG:
	हाल BMA400_X_AXIS_LSB_REG:
	हाल BMA400_X_AXIS_MSB_REG:
	हाल BMA400_Y_AXIS_LSB_REG:
	हाल BMA400_Y_AXIS_MSB_REG:
	हाल BMA400_Z_AXIS_LSB_REG:
	हाल BMA400_Z_AXIS_MSB_REG:
	हाल BMA400_SENSOR_TIME0:
	हाल BMA400_SENSOR_TIME1:
	हाल BMA400_SENSOR_TIME2:
	हाल BMA400_EVENT_REG:
	हाल BMA400_INT_STAT0_REG:
	हाल BMA400_INT_STAT1_REG:
	हाल BMA400_INT_STAT2_REG:
	हाल BMA400_TEMP_DATA_REG:
	हाल BMA400_FIFO_LENGTH0_REG:
	हाल BMA400_FIFO_LENGTH1_REG:
	हाल BMA400_FIFO_DATA_REG:
	हाल BMA400_STEP_CNT0_REG:
	हाल BMA400_STEP_CNT1_REG:
	हाल BMA400_STEP_CNT3_REG:
	हाल BMA400_STEP_STAT_REG:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

स्थिर काष्ठा regmap_config bma400_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = BMA400_CMD_REG,
	.cache_type = REGCACHE_RBTREE,
	.ग_लिखोable_reg = bma400_is_writable_reg,
	.अस्थिर_reg = bma400_is_अस्थिर_reg,
पूर्ण;
EXPORT_SYMBOL(bma400_regmap_config);

अटल स्थिर काष्ठा iio_mount_matrix *
bma400_accel_get_mount_matrix(स्थिर काष्ठा iio_dev *indio_dev,
			      स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा bma400_data *data = iio_priv(indio_dev);

	वापस &data->orientation;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec_ext_info bma400_ext_info[] = अणु
	IIO_MOUNT_MATRIX(IIO_SHARED_BY_सूची, bma400_accel_get_mount_matrix),
	अणु पूर्ण
पूर्ण;

#घोषणा BMA400_ACC_CHANNEL(_axis) अणु \
	.type = IIO_ACCEL, \
	.modअगरied = 1, \
	.channel2 = IIO_MOD_##_axis, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW), \
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SAMP_FREQ) | \
		BIT(IIO_CHAN_INFO_SCALE) | \
		BIT(IIO_CHAN_INFO_OVERSAMPLING_RATIO), \
	.info_mask_shared_by_type_available = BIT(IIO_CHAN_INFO_SAMP_FREQ) | \
		BIT(IIO_CHAN_INFO_SCALE) | \
		BIT(IIO_CHAN_INFO_OVERSAMPLING_RATIO), \
	.ext_info = bma400_ext_info, \
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec bma400_channels[] = अणु
	BMA400_ACC_CHANNEL(X),
	BMA400_ACC_CHANNEL(Y),
	BMA400_ACC_CHANNEL(Z),
	अणु
		.type = IIO_TEMP,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SAMP_FREQ),
	पूर्ण,
पूर्ण;

अटल पूर्णांक bma400_get_temp_reg(काष्ठा bma400_data *data, पूर्णांक *val, पूर्णांक *val2)
अणु
	अचिन्हित पूर्णांक raw_temp;
	पूर्णांक host_temp;
	पूर्णांक ret;

	अगर (data->घातer_mode == POWER_MODE_SLEEP)
		वापस -EBUSY;

	ret = regmap_पढ़ो(data->regmap, BMA400_TEMP_DATA_REG, &raw_temp);
	अगर (ret)
		वापस ret;

	host_temp = sign_extend32(raw_temp, 7);
	/*
	 * The क्रमmula क्रम the TEMP_DATA रेजिस्टर in the datasheet
	 * is: x * 0.5 + 23
	 */
	*val = (host_temp >> 1) + 23;
	*val2 = (host_temp & 0x1) * 500000;
	वापस IIO_VAL_INT_PLUS_MICRO;
पूर्ण

अटल पूर्णांक bma400_get_accel_reg(काष्ठा bma400_data *data,
				स्थिर काष्ठा iio_chan_spec *chan,
				पूर्णांक *val)
अणु
	__le16 raw_accel;
	पूर्णांक lsb_reg;
	पूर्णांक ret;

	अगर (data->घातer_mode == POWER_MODE_SLEEP)
		वापस -EBUSY;

	चयन (chan->channel2) अणु
	हाल IIO_MOD_X:
		lsb_reg = BMA400_X_AXIS_LSB_REG;
		अवरोध;
	हाल IIO_MOD_Y:
		lsb_reg = BMA400_Y_AXIS_LSB_REG;
		अवरोध;
	हाल IIO_MOD_Z:
		lsb_reg = BMA400_Z_AXIS_LSB_REG;
		अवरोध;
	शेष:
		dev_err(data->dev, "invalid axis channel modifier\n");
		वापस -EINVAL;
	पूर्ण

	/* bulk पढ़ो two रेजिस्टरs, with the base being the LSB रेजिस्टर */
	ret = regmap_bulk_पढ़ो(data->regmap, lsb_reg, &raw_accel,
			       माप(raw_accel));
	अगर (ret)
		वापस ret;

	*val = sign_extend32(le16_to_cpu(raw_accel), 11);
	वापस IIO_VAL_INT;
पूर्ण

अटल व्योम bma400_output_data_rate_from_raw(पूर्णांक raw, अचिन्हित पूर्णांक *val,
					     अचिन्हित पूर्णांक *val2)
अणु
	*val = BMA400_ACC_ODR_MAX_HZ >> (BMA400_ACC_ODR_MAX_RAW - raw);
	अगर (raw > BMA400_ACC_ODR_MIN_RAW)
		*val2 = 0;
	अन्यथा
		*val2 = 500000;
पूर्ण

अटल पूर्णांक bma400_get_accel_output_data_rate(काष्ठा bma400_data *data)
अणु
	अचिन्हित पूर्णांक val;
	अचिन्हित पूर्णांक odr;
	पूर्णांक ret;

	चयन (data->घातer_mode) अणु
	हाल POWER_MODE_LOW:
		/*
		 * Runs at a fixed rate in low-घातer mode. See section 4.3
		 * in the datasheet.
		 */
		bma400_output_data_rate_from_raw(BMA400_ACC_ODR_LP_RAW,
						 &data->sample_freq.hz,
						 &data->sample_freq.uhz);
		वापस 0;
	हाल POWER_MODE_NORMAL:
		/*
		 * In normal mode the ODR can be found in the ACC_CONFIG1
		 * रेजिस्टर.
		 */
		ret = regmap_पढ़ो(data->regmap, BMA400_ACC_CONFIG1_REG, &val);
		अगर (ret)
			जाओ error;

		odr = val & BMA400_ACC_ODR_MASK;
		अगर (odr < BMA400_ACC_ODR_MIN_RAW ||
		    odr > BMA400_ACC_ODR_MAX_RAW) अणु
			ret = -EINVAL;
			जाओ error;
		पूर्ण

		bma400_output_data_rate_from_raw(odr, &data->sample_freq.hz,
						 &data->sample_freq.uhz);
		वापस 0;
	हाल POWER_MODE_SLEEP:
		data->sample_freq.hz = 0;
		data->sample_freq.uhz = 0;
		वापस 0;
	शेष:
		ret = 0;
		जाओ error;
	पूर्ण
error:
	data->sample_freq.hz = -1;
	data->sample_freq.uhz = -1;
	वापस ret;
पूर्ण

अटल पूर्णांक bma400_set_accel_output_data_rate(काष्ठा bma400_data *data,
					     पूर्णांक hz, पूर्णांक uhz)
अणु
	अचिन्हित पूर्णांक idx;
	अचिन्हित पूर्णांक odr;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	अगर (hz >= BMA400_ACC_ODR_MIN_WHOLE_HZ) अणु
		अगर (uhz || hz > BMA400_ACC_ODR_MAX_HZ)
			वापस -EINVAL;

		/* Note this works because MIN_WHOLE_HZ is odd */
		idx = __ffs(hz);

		अगर (hz >> idx != BMA400_ACC_ODR_MIN_WHOLE_HZ)
			वापस -EINVAL;

		idx += BMA400_ACC_ODR_MIN_RAW + 1;
	पूर्ण अन्यथा अगर (hz == BMA400_ACC_ODR_MIN_HZ && uhz == 500000) अणु
		idx = BMA400_ACC_ODR_MIN_RAW;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	ret = regmap_पढ़ो(data->regmap, BMA400_ACC_CONFIG1_REG, &val);
	अगर (ret)
		वापस ret;

	/* preserve the range and normal mode osr */
	odr = (~BMA400_ACC_ODR_MASK & val) | idx;

	ret = regmap_ग_लिखो(data->regmap, BMA400_ACC_CONFIG1_REG, odr);
	अगर (ret)
		वापस ret;

	bma400_output_data_rate_from_raw(idx, &data->sample_freq.hz,
					 &data->sample_freq.uhz);
	वापस 0;
पूर्ण

अटल पूर्णांक bma400_get_accel_oversampling_ratio(काष्ठा bma400_data *data)
अणु
	अचिन्हित पूर्णांक val;
	अचिन्हित पूर्णांक osr;
	पूर्णांक ret;

	/*
	 * The oversampling ratio is stored in a dअगरferent रेजिस्टर
	 * based on the घातer-mode. In normal mode the OSR is stored
	 * in ACC_CONFIG1. In low-घातer mode it is stored in
	 * ACC_CONFIG0.
	 */
	चयन (data->घातer_mode) अणु
	हाल POWER_MODE_LOW:
		ret = regmap_पढ़ो(data->regmap, BMA400_ACC_CONFIG0_REG, &val);
		अगर (ret) अणु
			data->oversampling_ratio = -1;
			वापस ret;
		पूर्ण

		osr = (val & BMA400_LP_OSR_MASK) >> BMA400_LP_OSR_SHIFT;

		data->oversampling_ratio = osr;
		वापस 0;
	हाल POWER_MODE_NORMAL:
		ret = regmap_पढ़ो(data->regmap, BMA400_ACC_CONFIG1_REG, &val);
		अगर (ret) अणु
			data->oversampling_ratio = -1;
			वापस ret;
		पूर्ण

		osr = (val & BMA400_NP_OSR_MASK) >> BMA400_NP_OSR_SHIFT;

		data->oversampling_ratio = osr;
		वापस 0;
	हाल POWER_MODE_SLEEP:
		data->oversampling_ratio = 0;
		वापस 0;
	शेष:
		data->oversampling_ratio = -1;
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक bma400_set_accel_oversampling_ratio(काष्ठा bma400_data *data,
					       पूर्णांक val)
अणु
	अचिन्हित पूर्णांक acc_config;
	पूर्णांक ret;

	अगर (val & ~BMA400_TWO_BITS_MASK)
		वापस -EINVAL;

	/*
	 * The oversampling ratio is stored in a dअगरferent रेजिस्टर
	 * based on the घातer-mode.
	 */
	चयन (data->घातer_mode) अणु
	हाल POWER_MODE_LOW:
		ret = regmap_पढ़ो(data->regmap, BMA400_ACC_CONFIG0_REG,
				  &acc_config);
		अगर (ret)
			वापस ret;

		ret = regmap_ग_लिखो(data->regmap, BMA400_ACC_CONFIG0_REG,
				   (acc_config & ~BMA400_LP_OSR_MASK) |
				   (val << BMA400_LP_OSR_SHIFT));
		अगर (ret) अणु
			dev_err(data->dev, "Failed to write out OSR\n");
			वापस ret;
		पूर्ण

		data->oversampling_ratio = val;
		वापस 0;
	हाल POWER_MODE_NORMAL:
		ret = regmap_पढ़ो(data->regmap, BMA400_ACC_CONFIG1_REG,
				  &acc_config);
		अगर (ret)
			वापस ret;

		ret = regmap_ग_लिखो(data->regmap, BMA400_ACC_CONFIG1_REG,
				   (acc_config & ~BMA400_NP_OSR_MASK) |
				   (val << BMA400_NP_OSR_SHIFT));
		अगर (ret) अणु
			dev_err(data->dev, "Failed to write out OSR\n");
			वापस ret;
		पूर्ण

		data->oversampling_ratio = val;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक bma400_accel_scale_to_raw(काष्ठा bma400_data *data,
				     अचिन्हित पूर्णांक val)
अणु
	पूर्णांक raw;

	अगर (val == 0)
		वापस -EINVAL;

	/* Note this works because BMA400_SCALE_MIN is odd */
	raw = __ffs(val);

	अगर (val >> raw != BMA400_SCALE_MIN)
		वापस -EINVAL;

	वापस raw;
पूर्ण

अटल पूर्णांक bma400_get_accel_scale(काष्ठा bma400_data *data)
अणु
	अचिन्हित पूर्णांक raw_scale;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(data->regmap, BMA400_ACC_CONFIG1_REG, &val);
	अगर (ret)
		वापस ret;

	raw_scale = (val & BMA400_ACC_SCALE_MASK) >> BMA400_SCALE_SHIFT;
	अगर (raw_scale > BMA400_TWO_BITS_MASK)
		वापस -EINVAL;

	data->scale = BMA400_SCALE_MIN << raw_scale;

	वापस 0;
पूर्ण

अटल पूर्णांक bma400_set_accel_scale(काष्ठा bma400_data *data, अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक acc_config;
	पूर्णांक raw;
	पूर्णांक ret;

	ret = regmap_पढ़ो(data->regmap, BMA400_ACC_CONFIG1_REG, &acc_config);
	अगर (ret)
		वापस ret;

	raw = bma400_accel_scale_to_raw(data, val);
	अगर (raw < 0)
		वापस raw;

	ret = regmap_ग_लिखो(data->regmap, BMA400_ACC_CONFIG1_REG,
			   (acc_config & ~BMA400_ACC_SCALE_MASK) |
			   (raw << BMA400_SCALE_SHIFT));
	अगर (ret)
		वापस ret;

	data->scale = val;
	वापस 0;
पूर्ण

अटल पूर्णांक bma400_get_घातer_mode(काष्ठा bma400_data *data)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(data->regmap, BMA400_STATUS_REG, &val);
	अगर (ret) अणु
		dev_err(data->dev, "Failed to read status register\n");
		वापस ret;
	पूर्ण

	data->घातer_mode = (val >> 1) & BMA400_TWO_BITS_MASK;
	वापस 0;
पूर्ण

अटल पूर्णांक bma400_set_घातer_mode(काष्ठा bma400_data *data,
				 क्रमागत bma400_घातer_mode mode)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(data->regmap, BMA400_ACC_CONFIG0_REG, &val);
	अगर (ret)
		वापस ret;

	अगर (data->घातer_mode == mode)
		वापस 0;

	अगर (mode == POWER_MODE_INVALID)
		वापस -EINVAL;

	/* Preserve the low-घातer oversample ratio etc */
	ret = regmap_ग_लिखो(data->regmap, BMA400_ACC_CONFIG0_REG,
			   mode | (val & ~BMA400_TWO_BITS_MASK));
	अगर (ret) अणु
		dev_err(data->dev, "Failed to write to power-mode\n");
		वापस ret;
	पूर्ण

	data->घातer_mode = mode;

	/*
	 * Update our cached osr and odr based on the new
	 * घातer-mode.
	 */
	bma400_get_accel_output_data_rate(data);
	bma400_get_accel_oversampling_ratio(data);
	वापस 0;
पूर्ण

अटल व्योम bma400_init_tables(व्योम)
अणु
	पूर्णांक raw;
	पूर्णांक i;

	क्रम (i = 0; i + 1 < ARRAY_SIZE(bma400_sample_freqs); i += 2) अणु
		raw = (i / 2) + 5;
		bma400_output_data_rate_from_raw(raw, &bma400_sample_freqs[i],
						 &bma400_sample_freqs[i + 1]);
	पूर्ण

	क्रम (i = 0; i + 1 < ARRAY_SIZE(bma400_scales); i += 2) अणु
		raw = i / 2;
		bma400_scales[i] = 0;
		bma400_scales[i + 1] = BMA400_SCALE_MIN << raw;
	पूर्ण
पूर्ण

अटल पूर्णांक bma400_init(काष्ठा bma400_data *data)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	/* Try to पढ़ो chip_id रेजिस्टर. It must वापस 0x90. */
	ret = regmap_पढ़ो(data->regmap, BMA400_CHIP_ID_REG, &val);
	अगर (ret) अणु
		dev_err(data->dev, "Failed to read chip id register\n");
		जाओ out;
	पूर्ण

	अगर (val != BMA400_ID_REG_VAL) अणु
		dev_err(data->dev, "Chip ID mismatch\n");
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	data->regulators[BMA400_VDD_REGULATOR].supply = "vdd";
	data->regulators[BMA400_VDDIO_REGULATOR].supply = "vddio";
	ret = devm_regulator_bulk_get(data->dev,
				      ARRAY_SIZE(data->regulators),
				      data->regulators);
	अगर (ret) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(data->dev,
				"Failed to get regulators: %d\n",
				ret);

		जाओ out;
	पूर्ण
	ret = regulator_bulk_enable(ARRAY_SIZE(data->regulators),
				    data->regulators);
	अगर (ret) अणु
		dev_err(data->dev, "Failed to enable regulators: %d\n",
			ret);
		जाओ out;
	पूर्ण

	ret = bma400_get_घातer_mode(data);
	अगर (ret) अणु
		dev_err(data->dev, "Failed to get the initial power-mode\n");
		जाओ err_reg_disable;
	पूर्ण

	अगर (data->घातer_mode != POWER_MODE_NORMAL) अणु
		ret = bma400_set_घातer_mode(data, POWER_MODE_NORMAL);
		अगर (ret) अणु
			dev_err(data->dev, "Failed to wake up the device\n");
			जाओ err_reg_disable;
		पूर्ण
		/*
		 * TODO: The datasheet रुकोs 1500us here in the example, but
		 * lists 2/ODR as the wakeup समय.
		 */
		usleep_range(1500, 2000);
	पूर्ण

	bma400_init_tables();

	ret = bma400_get_accel_output_data_rate(data);
	अगर (ret)
		जाओ err_reg_disable;

	ret = bma400_get_accel_oversampling_ratio(data);
	अगर (ret)
		जाओ err_reg_disable;

	ret = bma400_get_accel_scale(data);
	अगर (ret)
		जाओ err_reg_disable;

	/*
	 * Once the पूर्णांकerrupt engine is supported we might use the
	 * data_src_reg, but क्रम now ensure this is set to the
	 * variable ODR filter selectable by the sample frequency
	 * channel.
	 */
	वापस regmap_ग_लिखो(data->regmap, BMA400_ACC_CONFIG2_REG, 0x00);

err_reg_disable:
	regulator_bulk_disable(ARRAY_SIZE(data->regulators),
			       data->regulators);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक bma400_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
			   पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा bma400_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_PROCESSED:
		mutex_lock(&data->mutex);
		ret = bma400_get_temp_reg(data, val, val2);
		mutex_unlock(&data->mutex);
		वापस ret;
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&data->mutex);
		ret = bma400_get_accel_reg(data, chan, val);
		mutex_unlock(&data->mutex);
		वापस ret;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		चयन (chan->type) अणु
		हाल IIO_ACCEL:
			अगर (data->sample_freq.hz < 0)
				वापस -EINVAL;

			*val = data->sample_freq.hz;
			*val2 = data->sample_freq.uhz;
			वापस IIO_VAL_INT_PLUS_MICRO;
		हाल IIO_TEMP:
			/*
			 * Runs at a fixed sampling frequency. See Section 4.4
			 * of the datasheet.
			 */
			*val = 6;
			*val2 = 250000;
			वापस IIO_VAL_INT_PLUS_MICRO;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_SCALE:
		*val = 0;
		*val2 = data->scale;
		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		/*
		 * TODO: We could aव्योम this logic and वापसing -EINVAL here अगर
		 * we set both the low-घातer and normal mode OSR रेजिस्टरs when
		 * we configure the device.
		 */
		अगर (data->oversampling_ratio < 0)
			वापस -EINVAL;

		*val = data->oversampling_ratio;
		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक bma400_पढ़ो_avail(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     स्थिर पूर्णांक **vals, पूर्णांक *type, पूर्णांक *length,
			     दीर्घ mask)
अणु
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		*type = IIO_VAL_INT_PLUS_MICRO;
		*vals = bma400_scales;
		*length = ARRAY_SIZE(bma400_scales);
		वापस IIO_AVAIL_LIST;
	हाल IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		*type = IIO_VAL_INT;
		*vals = bma400_osr_range;
		*length = ARRAY_SIZE(bma400_osr_range);
		वापस IIO_AVAIL_RANGE;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*type = IIO_VAL_INT_PLUS_MICRO;
		*vals = bma400_sample_freqs;
		*length = ARRAY_SIZE(bma400_sample_freqs);
		वापस IIO_AVAIL_LIST;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक bma400_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val, पूर्णांक val2,
			    दीर्घ mask)
अणु
	काष्ठा bma400_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		/*
		 * The sample frequency is पढ़ोonly क्रम the temperature
		 * रेजिस्टर and a fixed value in low-घातer mode.
		 */
		अगर (chan->type != IIO_ACCEL)
			वापस -EINVAL;

		mutex_lock(&data->mutex);
		ret = bma400_set_accel_output_data_rate(data, val, val2);
		mutex_unlock(&data->mutex);
		वापस ret;
	हाल IIO_CHAN_INFO_SCALE:
		अगर (val != 0 ||
		    val2 < BMA400_SCALE_MIN || val2 > BMA400_SCALE_MAX)
			वापस -EINVAL;

		mutex_lock(&data->mutex);
		ret = bma400_set_accel_scale(data, val2);
		mutex_unlock(&data->mutex);
		वापस ret;
	हाल IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		mutex_lock(&data->mutex);
		ret = bma400_set_accel_oversampling_ratio(data, val);
		mutex_unlock(&data->mutex);
		वापस ret;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक bma400_ग_लिखो_raw_get_fmt(काष्ठा iio_dev *indio_dev,
				    काष्ठा iio_chan_spec स्थिर *chan,
				    दीर्घ mask)
अणु
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_SCALE:
		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info bma400_info = अणु
	.पढ़ो_raw          = bma400_पढ़ो_raw,
	.पढ़ो_avail        = bma400_पढ़ो_avail,
	.ग_लिखो_raw         = bma400_ग_लिखो_raw,
	.ग_लिखो_raw_get_fmt = bma400_ग_लिखो_raw_get_fmt,
पूर्ण;

पूर्णांक bma400_probe(काष्ठा device *dev, काष्ठा regmap *regmap, स्थिर अक्षर *name)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा bma400_data *data;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	data->regmap = regmap;
	data->dev = dev;

	ret = bma400_init(data);
	अगर (ret)
		वापस ret;

	ret = iio_पढ़ो_mount_matrix(dev, "mount-matrix", &data->orientation);
	अगर (ret)
		वापस ret;

	mutex_init(&data->mutex);
	indio_dev->name = name;
	indio_dev->info = &bma400_info;
	indio_dev->channels = bma400_channels;
	indio_dev->num_channels = ARRAY_SIZE(bma400_channels);
	indio_dev->modes = INDIO_सूचीECT_MODE;

	dev_set_drvdata(dev, indio_dev);

	वापस iio_device_रेजिस्टर(indio_dev);
पूर्ण
EXPORT_SYMBOL(bma400_probe);

पूर्णांक bma400_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा bma400_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->mutex);
	ret = bma400_set_घातer_mode(data, POWER_MODE_SLEEP);
	mutex_unlock(&data->mutex);

	regulator_bulk_disable(ARRAY_SIZE(data->regulators),
			       data->regulators);

	iio_device_unरेजिस्टर(indio_dev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(bma400_हटाओ);

MODULE_AUTHOR("Dan Robertson <dan@dlrobertson.com>");
MODULE_DESCRIPTION("Bosch BMA400 triaxial acceleration sensor core");
MODULE_LICENSE("GPL");
