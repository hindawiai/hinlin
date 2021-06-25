<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * 3-axis accelerometer driver supporting following Bosch-Sensortec chips:
 *  - BMI088
 *
 * Copyright (c) 2018-2021, Topic Embedded Products
 */

#समावेश <linux/delay.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "bmi088-accel.h"

#घोषणा BMI088_ACCEL_REG_CHIP_ID			0x00
#घोषणा BMI088_ACCEL_REG_ERROR				0x02

#घोषणा BMI088_ACCEL_REG_INT_STATUS			0x1D
#घोषणा BMI088_ACCEL_INT_STATUS_BIT_DRDY		BIT(7)

#घोषणा BMI088_ACCEL_REG_RESET				0x7E
#घोषणा BMI088_ACCEL_RESET_VAL				0xB6

#घोषणा BMI088_ACCEL_REG_PWR_CTRL			0x7D
#घोषणा BMI088_ACCEL_REG_PWR_CONF			0x7C

#घोषणा BMI088_ACCEL_REG_INT_MAP_DATA			0x58
#घोषणा BMI088_ACCEL_INT_MAP_DATA_BIT_INT1_DRDY		BIT(2)
#घोषणा BMI088_ACCEL_INT_MAP_DATA_BIT_INT2_FWM		BIT(5)

#घोषणा BMI088_ACCEL_REG_INT1_IO_CONF			0x53
#घोषणा BMI088_ACCEL_INT1_IO_CONF_BIT_ENABLE_OUT	BIT(3)
#घोषणा BMI088_ACCEL_INT1_IO_CONF_BIT_LVL		BIT(1)

#घोषणा BMI088_ACCEL_REG_INT2_IO_CONF			0x54
#घोषणा BMI088_ACCEL_INT2_IO_CONF_BIT_ENABLE_OUT	BIT(3)
#घोषणा BMI088_ACCEL_INT2_IO_CONF_BIT_LVL		BIT(1)

#घोषणा BMI088_ACCEL_REG_ACC_CONF			0x40
#घोषणा BMI088_ACCEL_MODE_ODR_MASK			0x0f

#घोषणा BMI088_ACCEL_REG_ACC_RANGE			0x41
#घोषणा BMI088_ACCEL_RANGE_3G				0x00
#घोषणा BMI088_ACCEL_RANGE_6G				0x01
#घोषणा BMI088_ACCEL_RANGE_12G				0x02
#घोषणा BMI088_ACCEL_RANGE_24G				0x03

#घोषणा BMI088_ACCEL_REG_TEMP				0x22
#घोषणा BMI088_ACCEL_REG_TEMP_SHIFT			5
#घोषणा BMI088_ACCEL_TEMP_UNIT				125
#घोषणा BMI088_ACCEL_TEMP_OFFSET			23000

#घोषणा BMI088_ACCEL_REG_XOUT_L				0x12
#घोषणा BMI088_ACCEL_AXIS_TO_REG(axis) \
	(BMI088_ACCEL_REG_XOUT_L + (axis * 2))

#घोषणा BMI088_ACCEL_MAX_STARTUP_TIME_US		1000
#घोषणा BMI088_AUTO_SUSPEND_DELAY_MS			2000

#घोषणा BMI088_ACCEL_REG_FIFO_STATUS			0x0E
#घोषणा BMI088_ACCEL_REG_FIFO_CONFIG0			0x48
#घोषणा BMI088_ACCEL_REG_FIFO_CONFIG1			0x49
#घोषणा BMI088_ACCEL_REG_FIFO_DATA			0x3F
#घोषणा BMI088_ACCEL_FIFO_LENGTH			100

#घोषणा BMI088_ACCEL_FIFO_MODE_FIFO			0x40
#घोषणा BMI088_ACCEL_FIFO_MODE_STREAM			0x80

क्रमागत bmi088_accel_axis अणु
	AXIS_X,
	AXIS_Y,
	AXIS_Z,
पूर्ण;

अटल स्थिर पूर्णांक bmi088_sample_freqs[] = अणु
	12, 500000,
	25, 0,
	50, 0,
	100, 0,
	200, 0,
	400, 0,
	800, 0,
	1600, 0,
पूर्ण;

/* Available OSR (over sampling rate) sets the 3dB cut-off frequency */
क्रमागत bmi088_osr_modes अणु
	BMI088_ACCEL_MODE_OSR_NORMAL = 0xA,
	BMI088_ACCEL_MODE_OSR_2 = 0x9,
	BMI088_ACCEL_MODE_OSR_4 = 0x8,
पूर्ण;

/* Available ODR (output data rates) in Hz */
क्रमागत bmi088_odr_modes अणु
	BMI088_ACCEL_MODE_ODR_12_5 = 0x5,
	BMI088_ACCEL_MODE_ODR_25 = 0x6,
	BMI088_ACCEL_MODE_ODR_50 = 0x7,
	BMI088_ACCEL_MODE_ODR_100 = 0x8,
	BMI088_ACCEL_MODE_ODR_200 = 0x9,
	BMI088_ACCEL_MODE_ODR_400 = 0xa,
	BMI088_ACCEL_MODE_ODR_800 = 0xb,
	BMI088_ACCEL_MODE_ODR_1600 = 0xc,
पूर्ण;

काष्ठा bmi088_scale_info अणु
	पूर्णांक scale;
	u8 reg_range;
पूर्ण;

काष्ठा bmi088_accel_chip_info अणु
	स्थिर अक्षर *name;
	u8 chip_id;
	स्थिर काष्ठा iio_chan_spec *channels;
	पूर्णांक num_channels;
पूर्ण;

काष्ठा bmi088_accel_data अणु
	काष्ठा regmap *regmap;
	स्थिर काष्ठा bmi088_accel_chip_info *chip_info;
	u8 buffer[2] ____cacheline_aligned; /* shared DMA safe buffer */
पूर्ण;

अटल स्थिर काष्ठा regmap_range bmi088_अस्थिर_ranges[] = अणु
	/* All रेजिस्टरs below 0x40 are अस्थिर, except the CHIP ID. */
	regmap_reg_range(BMI088_ACCEL_REG_ERROR, 0x3f),
	/* Mark the RESET as अस्थिर too, it is self-clearing */
	regmap_reg_range(BMI088_ACCEL_REG_RESET, BMI088_ACCEL_REG_RESET),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table bmi088_अस्थिर_table = अणु
	.yes_ranges	= bmi088_अस्थिर_ranges,
	.n_yes_ranges	= ARRAY_SIZE(bmi088_अस्थिर_ranges),
पूर्ण;

स्थिर काष्ठा regmap_config bmi088_regmap_conf = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 0x7E,
	.अस्थिर_table = &bmi088_अस्थिर_table,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;
EXPORT_SYMBOL_GPL(bmi088_regmap_conf);

अटल पूर्णांक bmi088_accel_घातer_up(काष्ठा bmi088_accel_data *data)
अणु
	पूर्णांक ret;

	/* Enable accelerometer and temperature sensor */
	ret = regmap_ग_लिखो(data->regmap, BMI088_ACCEL_REG_PWR_CTRL, 0x4);
	अगर (ret)
		वापस ret;

	/* Datasheet recommends to रुको at least 5ms beक्रमe communication */
	usleep_range(5000, 6000);

	/* Disable suspend mode */
	ret = regmap_ग_लिखो(data->regmap, BMI088_ACCEL_REG_PWR_CONF, 0x0);
	अगर (ret)
		वापस ret;

	/* Recommended at least 1ms beक्रमe further communication */
	usleep_range(1000, 1200);

	वापस 0;
पूर्ण

अटल पूर्णांक bmi088_accel_घातer_करोwn(काष्ठा bmi088_accel_data *data)
अणु
	पूर्णांक ret;

	/* Enable suspend mode */
	ret = regmap_ग_लिखो(data->regmap, BMI088_ACCEL_REG_PWR_CONF, 0x3);
	अगर (ret)
		वापस ret;

	/* Recommended at least 1ms beक्रमe further communication */
	usleep_range(1000, 1200);

	/* Disable accelerometer and temperature sensor */
	ret = regmap_ग_लिखो(data->regmap, BMI088_ACCEL_REG_PWR_CTRL, 0x0);
	अगर (ret)
		वापस ret;

	/* Datasheet recommends to रुको at least 5ms beक्रमe communication */
	usleep_range(5000, 6000);

	वापस 0;
पूर्ण

अटल पूर्णांक bmi088_accel_get_sample_freq(काष्ठा bmi088_accel_data *data,
					पूर्णांक *val, पूर्णांक *val2)
अणु
	अचिन्हित पूर्णांक value;
	पूर्णांक ret;

	ret = regmap_पढ़ो(data->regmap, BMI088_ACCEL_REG_ACC_CONF,
			  &value);
	अगर (ret)
		वापस ret;

	value &= BMI088_ACCEL_MODE_ODR_MASK;
	value -= BMI088_ACCEL_MODE_ODR_12_5;
	value <<= 1;

	अगर (value >= ARRAY_SIZE(bmi088_sample_freqs) - 1)
		वापस -EINVAL;

	*val = bmi088_sample_freqs[value];
	*val2 = bmi088_sample_freqs[value + 1];

	वापस IIO_VAL_INT_PLUS_MICRO;
पूर्ण

अटल पूर्णांक bmi088_accel_set_sample_freq(काष्ठा bmi088_accel_data *data, पूर्णांक val)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक index = 0;

	जबतक (index < ARRAY_SIZE(bmi088_sample_freqs) &&
	       bmi088_sample_freqs[index] != val)
		index += 2;

	अगर (index >= ARRAY_SIZE(bmi088_sample_freqs))
		वापस -EINVAL;

	regval = (index >> 1) + BMI088_ACCEL_MODE_ODR_12_5;

	वापस regmap_update_bits(data->regmap, BMI088_ACCEL_REG_ACC_CONF,
				  BMI088_ACCEL_MODE_ODR_MASK, regval);
पूर्ण

अटल पूर्णांक bmi088_accel_get_temp(काष्ठा bmi088_accel_data *data, पूर्णांक *val)
अणु
	पूर्णांक ret;
	s16 temp;

	ret = regmap_bulk_पढ़ो(data->regmap, BMI088_ACCEL_REG_TEMP,
			       &data->buffer, माप(__be16));
	अगर (ret)
		वापस ret;

	/* data->buffer is cacheline aligned */
	temp = be16_to_cpu(*(__be16 *)data->buffer);

	*val = temp >> BMI088_ACCEL_REG_TEMP_SHIFT;

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक bmi088_accel_get_axis(काष्ठा bmi088_accel_data *data,
				 काष्ठा iio_chan_spec स्थिर *chan,
				 पूर्णांक *val)
अणु
	पूर्णांक ret;
	s16 raw_val;

	ret = regmap_bulk_पढ़ो(data->regmap,
			       BMI088_ACCEL_AXIS_TO_REG(chan->scan_index),
			       data->buffer, माप(__le16));
	अगर (ret)
		वापस ret;

	raw_val = le16_to_cpu(*(__le16 *)data->buffer);
	*val = raw_val;

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक bmi088_accel_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				 काष्ठा iio_chan_spec स्थिर *chan,
				 पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा bmi088_accel_data *data = iio_priv(indio_dev);
	काष्ठा device *dev = regmap_get_device(data->regmap);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		चयन (chan->type) अणु
		हाल IIO_TEMP:
			pm_runसमय_get_sync(dev);
			ret = bmi088_accel_get_temp(data, val);
			जाओ out_पढ़ो_raw_pm_put;
		हाल IIO_ACCEL:
			pm_runसमय_get_sync(dev);
			ret = iio_device_claim_direct_mode(indio_dev);
			अगर (ret)
				जाओ out_पढ़ो_raw_pm_put;

			ret = bmi088_accel_get_axis(data, chan, val);
			iio_device_release_direct_mode(indio_dev);
			अगर (!ret)
				ret = IIO_VAL_INT;

			जाओ out_पढ़ो_raw_pm_put;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_OFFSET:
		चयन (chan->type) अणु
		हाल IIO_TEMP:
			/* Offset applies beक्रमe scale */
			*val = BMI088_ACCEL_TEMP_OFFSET/BMI088_ACCEL_TEMP_UNIT;
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_TEMP:
			/* 0.125 degrees per LSB */
			*val = BMI088_ACCEL_TEMP_UNIT;
			वापस IIO_VAL_INT;
		हाल IIO_ACCEL:
			pm_runसमय_get_sync(dev);
			ret = regmap_पढ़ो(data->regmap,
					  BMI088_ACCEL_REG_ACC_RANGE, val);
			अगर (ret)
				जाओ out_पढ़ो_raw_pm_put;

			*val2 = 15 - (*val & 0x3);
			*val = 3 * 980;
			ret = IIO_VAL_FRACTIONAL_LOG2;

			जाओ out_पढ़ो_raw_pm_put;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		pm_runसमय_get_sync(dev);
		ret = bmi088_accel_get_sample_freq(data, val, val2);
		जाओ out_पढ़ो_raw_pm_put;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;

out_पढ़ो_raw_pm_put:
	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक bmi088_accel_पढ़ो_avail(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     स्थिर पूर्णांक **vals, पूर्णांक *type, पूर्णांक *length,
			     दीर्घ mask)
अणु
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*type = IIO_VAL_INT_PLUS_MICRO;
		*vals = bmi088_sample_freqs;
		*length = ARRAY_SIZE(bmi088_sample_freqs);
		वापस IIO_AVAIL_LIST;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक bmi088_accel_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
				  काष्ठा iio_chan_spec स्थिर *chan,
				  पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा bmi088_accel_data *data = iio_priv(indio_dev);
	काष्ठा device *dev = regmap_get_device(data->regmap);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		pm_runसमय_get_sync(dev);
		ret = bmi088_accel_set_sample_freq(data, val);
		pm_runसमय_mark_last_busy(dev);
		pm_runसमय_put_स्वतःsuspend(dev);
		वापस ret;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

#घोषणा BMI088_ACCEL_CHANNEL(_axis) अणु \
	.type = IIO_ACCEL, \
	.modअगरied = 1, \
	.channel2 = IIO_MOD_##_axis, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW), \
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) | \
				BIT(IIO_CHAN_INFO_SAMP_FREQ), \
	.info_mask_shared_by_type_available = BIT(IIO_CHAN_INFO_SAMP_FREQ), \
	.scan_index = AXIS_##_axis, \
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec bmi088_accel_channels[] = अणु
	अणु
		.type = IIO_TEMP,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE) |
				      BIT(IIO_CHAN_INFO_OFFSET),
		.scan_index = -1,
	पूर्ण,
	BMI088_ACCEL_CHANNEL(X),
	BMI088_ACCEL_CHANNEL(Y),
	BMI088_ACCEL_CHANNEL(Z),
	IIO_CHAN_SOFT_TIMESTAMP(3),
पूर्ण;

अटल स्थिर काष्ठा bmi088_accel_chip_info bmi088_accel_chip_info_tbl[] = अणु
	[0] = अणु
		.name = "bmi088a",
		.chip_id = 0x1E,
		.channels = bmi088_accel_channels,
		.num_channels = ARRAY_SIZE(bmi088_accel_channels),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_info bmi088_accel_info = अणु
	.पढ़ो_raw	= bmi088_accel_पढ़ो_raw,
	.ग_लिखो_raw	= bmi088_accel_ग_लिखो_raw,
	.पढ़ो_avail	= bmi088_accel_पढ़ो_avail,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ bmi088_accel_scan_masks[] = अणु
	BIT(AXIS_X) | BIT(AXIS_Y) | BIT(AXIS_Z),
	0
पूर्ण;

अटल पूर्णांक bmi088_accel_chip_init(काष्ठा bmi088_accel_data *data)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);
	पूर्णांक ret, i;
	अचिन्हित पूर्णांक val;

	/* Do a dummy पढ़ो to enable SPI पूर्णांकerface, won't harm I2C */
	regmap_पढ़ो(data->regmap, BMI088_ACCEL_REG_INT_STATUS, &val);

	/*
	 * Reset chip to get it in a known good state. A delay of 1ms after
	 * reset is required according to the data sheet
	 */
	ret = regmap_ग_लिखो(data->regmap, BMI088_ACCEL_REG_RESET,
			   BMI088_ACCEL_RESET_VAL);
	अगर (ret)
		वापस ret;

	usleep_range(1000, 2000);

	/* Do a dummy पढ़ो again after a reset to enable the SPI पूर्णांकerface */
	regmap_पढ़ो(data->regmap, BMI088_ACCEL_REG_INT_STATUS, &val);

	/* Read chip ID */
	ret = regmap_पढ़ो(data->regmap, BMI088_ACCEL_REG_CHIP_ID, &val);
	अगर (ret) अणु
		dev_err(dev, "Error: Reading chip id\n");
		वापस ret;
	पूर्ण

	/* Validate chip ID */
	क्रम (i = 0; i < ARRAY_SIZE(bmi088_accel_chip_info_tbl); i++) अणु
		अगर (bmi088_accel_chip_info_tbl[i].chip_id == val) अणु
			data->chip_info = &bmi088_accel_chip_info_tbl[i];
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == ARRAY_SIZE(bmi088_accel_chip_info_tbl)) अणु
		dev_err(dev, "Invalid chip %x\n", val);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक bmi088_accel_core_probe(काष्ठा device *dev, काष्ठा regmap *regmap,
	पूर्णांक irq, स्थिर अक्षर *name, bool block_supported)
अणु
	काष्ठा bmi088_accel_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	dev_set_drvdata(dev, indio_dev);

	data->regmap = regmap;

	ret = bmi088_accel_chip_init(data);
	अगर (ret)
		वापस ret;

	indio_dev->dev.parent = dev;
	indio_dev->channels = data->chip_info->channels;
	indio_dev->num_channels = data->chip_info->num_channels;
	indio_dev->name = name ? name : data->chip_info->name;
	indio_dev->available_scan_masks = bmi088_accel_scan_masks;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &bmi088_accel_info;

	/* Enable runसमय PM */
	pm_runसमय_get_noresume(dev);
	pm_runसमय_set_suspended(dev);
	pm_runसमय_enable(dev);
	/* We need ~6ms to startup, so set the delay to 6 seconds */
	pm_runसमय_set_स्वतःsuspend_delay(dev, 6000);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_put(dev);

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		dev_err(dev, "Unable to register iio device\n");

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(bmi088_accel_core_probe);


पूर्णांक bmi088_accel_core_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा bmi088_accel_data *data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	pm_runसमय_disable(dev);
	pm_runसमय_set_suspended(dev);
	pm_runसमय_put_noidle(dev);
	bmi088_accel_घातer_करोwn(data);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(bmi088_accel_core_हटाओ);

अटल पूर्णांक __maybe_unused bmi088_accel_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा bmi088_accel_data *data = iio_priv(indio_dev);

	वापस bmi088_accel_घातer_करोwn(data);
पूर्ण

अटल पूर्णांक __maybe_unused bmi088_accel_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा bmi088_accel_data *data = iio_priv(indio_dev);

	वापस bmi088_accel_घातer_up(data);
पूर्ण

स्थिर काष्ठा dev_pm_ops bmi088_accel_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(bmi088_accel_runसमय_suspend,
			   bmi088_accel_runसमय_resume, शून्य)
पूर्ण;
EXPORT_SYMBOL_GPL(bmi088_accel_pm_ops);

MODULE_AUTHOR("Niek van Agt <niek.van.agt@topicproducts.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("BMI088 accelerometer driver (core)");
