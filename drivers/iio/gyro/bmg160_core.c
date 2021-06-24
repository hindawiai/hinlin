<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * BMG160 Gyro Sensor driver
 * Copyright (c) 2014, Intel Corporation.
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश "bmg160.h"

#घोषणा BMG160_IRQ_NAME		"bmg160_event"

#घोषणा BMG160_REG_CHIP_ID		0x00
#घोषणा BMG160_CHIP_ID_VAL		0x0F

#घोषणा BMG160_REG_PMU_LPW		0x11
#घोषणा BMG160_MODE_NORMAL		0x00
#घोषणा BMG160_MODE_DEEP_SUSPEND	0x20
#घोषणा BMG160_MODE_SUSPEND		0x80

#घोषणा BMG160_REG_RANGE		0x0F

#घोषणा BMG160_RANGE_2000DPS		0
#घोषणा BMG160_RANGE_1000DPS		1
#घोषणा BMG160_RANGE_500DPS		2
#घोषणा BMG160_RANGE_250DPS		3
#घोषणा BMG160_RANGE_125DPS		4

#घोषणा BMG160_REG_PMU_BW		0x10
#घोषणा BMG160_NO_FILTER		0
#घोषणा BMG160_DEF_BW			100
#घोषणा BMG160_REG_PMU_BW_RES		BIT(7)

#घोषणा BMG160_GYRO_REG_RESET		0x14
#घोषणा BMG160_GYRO_RESET_VAL		0xb6

#घोषणा BMG160_REG_INT_MAP_0		0x17
#घोषणा BMG160_INT_MAP_0_BIT_ANY	BIT(1)

#घोषणा BMG160_REG_INT_MAP_1		0x18
#घोषणा BMG160_INT_MAP_1_BIT_NEW_DATA	BIT(0)

#घोषणा BMG160_REG_INT_RST_LATCH	0x21
#घोषणा BMG160_INT_MODE_LATCH_RESET	0x80
#घोषणा BMG160_INT_MODE_LATCH_INT	0x0F
#घोषणा BMG160_INT_MODE_NON_LATCH_INT	0x00

#घोषणा BMG160_REG_INT_EN_0		0x15
#घोषणा BMG160_DATA_ENABLE_INT		BIT(7)

#घोषणा BMG160_REG_INT_EN_1		0x16
#घोषणा BMG160_INT1_BIT_OD		BIT(1)

#घोषणा BMG160_REG_XOUT_L		0x02
#घोषणा BMG160_AXIS_TO_REG(axis)	(BMG160_REG_XOUT_L + (axis * 2))

#घोषणा BMG160_REG_SLOPE_THRES		0x1B
#घोषणा BMG160_SLOPE_THRES_MASK	0x0F

#घोषणा BMG160_REG_MOTION_INTR		0x1C
#घोषणा BMG160_INT_MOTION_X		BIT(0)
#घोषणा BMG160_INT_MOTION_Y		BIT(1)
#घोषणा BMG160_INT_MOTION_Z		BIT(2)
#घोषणा BMG160_ANY_DUR_MASK		0x30
#घोषणा BMG160_ANY_DUR_SHIFT		4

#घोषणा BMG160_REG_INT_STATUS_2	0x0B
#घोषणा BMG160_ANY_MOTION_MASK		0x07
#घोषणा BMG160_ANY_MOTION_BIT_X		BIT(0)
#घोषणा BMG160_ANY_MOTION_BIT_Y		BIT(1)
#घोषणा BMG160_ANY_MOTION_BIT_Z		BIT(2)

#घोषणा BMG160_REG_TEMP		0x08
#घोषणा BMG160_TEMP_CENTER_VAL		23

#घोषणा BMG160_MAX_STARTUP_TIME_MS	80

#घोषणा BMG160_AUTO_SUSPEND_DELAY_MS	2000

काष्ठा bmg160_data अणु
	काष्ठा regmap *regmap;
	काष्ठा regulator_bulk_data regulators[2];
	काष्ठा iio_trigger *dपढ़ोy_trig;
	काष्ठा iio_trigger *motion_trig;
	काष्ठा iio_mount_matrix orientation;
	काष्ठा mutex mutex;
	s16 buffer[8];
	u32 dps_range;
	पूर्णांक ev_enable_state;
	पूर्णांक slope_thres;
	bool dपढ़ोy_trigger_on;
	bool motion_trigger_on;
	पूर्णांक irq;
पूर्ण;

क्रमागत bmg160_axis अणु
	AXIS_X,
	AXIS_Y,
	AXIS_Z,
	AXIS_MAX,
पूर्ण;

अटल स्थिर काष्ठा अणु
	पूर्णांक odr;
	पूर्णांक filter;
	पूर्णांक bw_bits;
पूर्ण bmg160_samp_freq_table[] = अणु अणु100, 32, 0x07पूर्ण,
			       अणु200, 64, 0x06पूर्ण,
			       अणु100, 12, 0x05पूर्ण,
			       अणु200, 23, 0x04पूर्ण,
			       अणु400, 47, 0x03पूर्ण,
			       अणु1000, 116, 0x02पूर्ण,
			       अणु2000, 230, 0x01पूर्ण पूर्ण;

अटल स्थिर काष्ठा अणु
	पूर्णांक scale;
	पूर्णांक dps_range;
पूर्ण bmg160_scale_table[] = अणु अणु 1065, BMG160_RANGE_2000DPSपूर्ण,
			   अणु 532, BMG160_RANGE_1000DPSपूर्ण,
			   अणु 266, BMG160_RANGE_500DPSपूर्ण,
			   अणु 133, BMG160_RANGE_250DPSपूर्ण,
			   अणु 66, BMG160_RANGE_125DPSपूर्ण पूर्ण;

अटल पूर्णांक bmg160_set_mode(काष्ठा bmg160_data *data, u8 mode)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);
	पूर्णांक ret;

	ret = regmap_ग_लिखो(data->regmap, BMG160_REG_PMU_LPW, mode);
	अगर (ret < 0) अणु
		dev_err(dev, "Error writing reg_pmu_lpw\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bmg160_convert_freq_to_bit(पूर्णांक val)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(bmg160_samp_freq_table); ++i) अणु
		अगर (bmg160_samp_freq_table[i].odr == val)
			वापस bmg160_samp_freq_table[i].bw_bits;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक bmg160_set_bw(काष्ठा bmg160_data *data, पूर्णांक val)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);
	पूर्णांक ret;
	पूर्णांक bw_bits;

	bw_bits = bmg160_convert_freq_to_bit(val);
	अगर (bw_bits < 0)
		वापस bw_bits;

	ret = regmap_ग_लिखो(data->regmap, BMG160_REG_PMU_BW, bw_bits);
	अगर (ret < 0) अणु
		dev_err(dev, "Error writing reg_pmu_bw\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bmg160_get_filter(काष्ठा bmg160_data *data, पूर्णांक *val)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);
	पूर्णांक ret;
	पूर्णांक i;
	अचिन्हित पूर्णांक bw_bits;

	ret = regmap_पढ़ो(data->regmap, BMG160_REG_PMU_BW, &bw_bits);
	अगर (ret < 0) अणु
		dev_err(dev, "Error reading reg_pmu_bw\n");
		वापस ret;
	पूर्ण

	/* Ignore the पढ़ोonly reserved bit. */
	bw_bits &= ~BMG160_REG_PMU_BW_RES;

	क्रम (i = 0; i < ARRAY_SIZE(bmg160_samp_freq_table); ++i) अणु
		अगर (bmg160_samp_freq_table[i].bw_bits == bw_bits)
			अवरोध;
	पूर्ण

	*val = bmg160_samp_freq_table[i].filter;

	वापस ret ? ret : IIO_VAL_INT;
पूर्ण


अटल पूर्णांक bmg160_set_filter(काष्ठा bmg160_data *data, पूर्णांक val)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(bmg160_samp_freq_table); ++i) अणु
		अगर (bmg160_samp_freq_table[i].filter == val)
			अवरोध;
	पूर्ण

	ret = regmap_ग_लिखो(data->regmap, BMG160_REG_PMU_BW,
			   bmg160_samp_freq_table[i].bw_bits);
	अगर (ret < 0) अणु
		dev_err(dev, "Error writing reg_pmu_bw\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bmg160_chip_init(काष्ठा bmg160_data *data)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	/*
	 * Reset chip to get it in a known good state. A delay of 30ms after
	 * reset is required according to the datasheet.
	 */
	regmap_ग_लिखो(data->regmap, BMG160_GYRO_REG_RESET,
		     BMG160_GYRO_RESET_VAL);
	usleep_range(30000, 30700);

	ret = regmap_पढ़ो(data->regmap, BMG160_REG_CHIP_ID, &val);
	अगर (ret < 0) अणु
		dev_err(dev, "Error reading reg_chip_id\n");
		वापस ret;
	पूर्ण

	dev_dbg(dev, "Chip Id %x\n", val);
	अगर (val != BMG160_CHIP_ID_VAL) अणु
		dev_err(dev, "invalid chip %x\n", val);
		वापस -ENODEV;
	पूर्ण

	ret = bmg160_set_mode(data, BMG160_MODE_NORMAL);
	अगर (ret < 0)
		वापस ret;

	/* Wait upto 500 ms to be पढ़ोy after changing mode */
	usleep_range(500, 1000);

	/* Set Bandwidth */
	ret = bmg160_set_bw(data, BMG160_DEF_BW);
	अगर (ret < 0)
		वापस ret;

	/* Set Default Range */
	ret = regmap_ग_लिखो(data->regmap, BMG160_REG_RANGE, BMG160_RANGE_500DPS);
	अगर (ret < 0) अणु
		dev_err(dev, "Error writing reg_range\n");
		वापस ret;
	पूर्ण
	data->dps_range = BMG160_RANGE_500DPS;

	ret = regmap_पढ़ो(data->regmap, BMG160_REG_SLOPE_THRES, &val);
	अगर (ret < 0) अणु
		dev_err(dev, "Error reading reg_slope_thres\n");
		वापस ret;
	पूर्ण
	data->slope_thres = val;

	/* Set शेष पूर्णांकerrupt mode */
	ret = regmap_update_bits(data->regmap, BMG160_REG_INT_EN_1,
				 BMG160_INT1_BIT_OD, 0);
	अगर (ret < 0) अणु
		dev_err(dev, "Error updating bits in reg_int_en_1\n");
		वापस ret;
	पूर्ण

	ret = regmap_ग_लिखो(data->regmap, BMG160_REG_INT_RST_LATCH,
			   BMG160_INT_MODE_LATCH_INT |
			   BMG160_INT_MODE_LATCH_RESET);
	अगर (ret < 0) अणु
		dev_err(dev,
			"Error writing reg_motion_intr\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bmg160_set_घातer_state(काष्ठा bmg160_data *data, bool on)
अणु
#अगर_घोषित CONFIG_PM
	काष्ठा device *dev = regmap_get_device(data->regmap);
	पूर्णांक ret;

	अगर (on)
		ret = pm_runसमय_get_sync(dev);
	अन्यथा अणु
		pm_runसमय_mark_last_busy(dev);
		ret = pm_runसमय_put_स्वतःsuspend(dev);
	पूर्ण

	अगर (ret < 0) अणु
		dev_err(dev, "Failed: bmg160_set_power_state for %d\n", on);

		अगर (on)
			pm_runसमय_put_noidle(dev);

		वापस ret;
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक bmg160_setup_any_motion_पूर्णांकerrupt(काष्ठा bmg160_data *data,
					     bool status)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);
	पूर्णांक ret;

	/* Enable/Disable INT_MAP0 mapping */
	ret = regmap_update_bits(data->regmap, BMG160_REG_INT_MAP_0,
				 BMG160_INT_MAP_0_BIT_ANY,
				 (status ? BMG160_INT_MAP_0_BIT_ANY : 0));
	अगर (ret < 0) अणु
		dev_err(dev, "Error updating bits reg_int_map0\n");
		वापस ret;
	पूर्ण

	/* Enable/Disable slope पूर्णांकerrupts */
	अगर (status) अणु
		/* Update slope thres */
		ret = regmap_ग_लिखो(data->regmap, BMG160_REG_SLOPE_THRES,
				   data->slope_thres);
		अगर (ret < 0) अणु
			dev_err(dev, "Error writing reg_slope_thres\n");
			वापस ret;
		पूर्ण

		ret = regmap_ग_लिखो(data->regmap, BMG160_REG_MOTION_INTR,
				   BMG160_INT_MOTION_X | BMG160_INT_MOTION_Y |
				   BMG160_INT_MOTION_Z);
		अगर (ret < 0) अणु
			dev_err(dev, "Error writing reg_motion_intr\n");
			वापस ret;
		पूर्ण

		/*
		 * New data पूर्णांकerrupt is always non-latched,
		 * which will have higher priority, so no need
		 * to set latched mode, we will be flooded anyway with INTR
		 */
		अगर (!data->dपढ़ोy_trigger_on) अणु
			ret = regmap_ग_लिखो(data->regmap,
					   BMG160_REG_INT_RST_LATCH,
					   BMG160_INT_MODE_LATCH_INT |
					   BMG160_INT_MODE_LATCH_RESET);
			अगर (ret < 0) अणु
				dev_err(dev, "Error writing reg_rst_latch\n");
				वापस ret;
			पूर्ण
		पूर्ण

		ret = regmap_ग_लिखो(data->regmap, BMG160_REG_INT_EN_0,
				   BMG160_DATA_ENABLE_INT);

	पूर्ण अन्यथा अणु
		ret = regmap_ग_लिखो(data->regmap, BMG160_REG_INT_EN_0, 0);
	पूर्ण

	अगर (ret < 0) अणु
		dev_err(dev, "Error writing reg_int_en0\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bmg160_setup_new_data_पूर्णांकerrupt(काष्ठा bmg160_data *data,
					   bool status)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);
	पूर्णांक ret;

	/* Enable/Disable INT_MAP1 mapping */
	ret = regmap_update_bits(data->regmap, BMG160_REG_INT_MAP_1,
				 BMG160_INT_MAP_1_BIT_NEW_DATA,
				 (status ? BMG160_INT_MAP_1_BIT_NEW_DATA : 0));
	अगर (ret < 0) अणु
		dev_err(dev, "Error updating bits in reg_int_map1\n");
		वापस ret;
	पूर्ण

	अगर (status) अणु
		ret = regmap_ग_लिखो(data->regmap, BMG160_REG_INT_RST_LATCH,
				   BMG160_INT_MODE_NON_LATCH_INT |
				   BMG160_INT_MODE_LATCH_RESET);
		अगर (ret < 0) अणु
			dev_err(dev, "Error writing reg_rst_latch\n");
			वापस ret;
		पूर्ण

		ret = regmap_ग_लिखो(data->regmap, BMG160_REG_INT_EN_0,
				   BMG160_DATA_ENABLE_INT);

	पूर्ण अन्यथा अणु
		/* Restore पूर्णांकerrupt mode */
		ret = regmap_ग_लिखो(data->regmap, BMG160_REG_INT_RST_LATCH,
				   BMG160_INT_MODE_LATCH_INT |
				   BMG160_INT_MODE_LATCH_RESET);
		अगर (ret < 0) अणु
			dev_err(dev, "Error writing reg_rst_latch\n");
			वापस ret;
		पूर्ण

		ret = regmap_ग_लिखो(data->regmap, BMG160_REG_INT_EN_0, 0);
	पूर्ण

	अगर (ret < 0) अणु
		dev_err(dev, "Error writing reg_int_en0\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bmg160_get_bw(काष्ठा bmg160_data *data, पूर्णांक *val)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);	
	पूर्णांक i;
	अचिन्हित पूर्णांक bw_bits;
	पूर्णांक ret;

	ret = regmap_पढ़ो(data->regmap, BMG160_REG_PMU_BW, &bw_bits);
	अगर (ret < 0) अणु
		dev_err(dev, "Error reading reg_pmu_bw\n");
		वापस ret;
	पूर्ण

	/* Ignore the पढ़ोonly reserved bit. */
	bw_bits &= ~BMG160_REG_PMU_BW_RES;

	क्रम (i = 0; i < ARRAY_SIZE(bmg160_samp_freq_table); ++i) अणु
		अगर (bmg160_samp_freq_table[i].bw_bits == bw_bits) अणु
			*val = bmg160_samp_freq_table[i].odr;
			वापस IIO_VAL_INT;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक bmg160_set_scale(काष्ठा bmg160_data *data, पूर्णांक val)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);
	पूर्णांक ret, i;

	क्रम (i = 0; i < ARRAY_SIZE(bmg160_scale_table); ++i) अणु
		अगर (bmg160_scale_table[i].scale == val) अणु
			ret = regmap_ग_लिखो(data->regmap, BMG160_REG_RANGE,
					   bmg160_scale_table[i].dps_range);
			अगर (ret < 0) अणु
				dev_err(dev, "Error writing reg_range\n");
				वापस ret;
			पूर्ण
			data->dps_range = bmg160_scale_table[i].dps_range;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक bmg160_get_temp(काष्ठा bmg160_data *data, पूर्णांक *val)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);
	पूर्णांक ret;
	अचिन्हित पूर्णांक raw_val;

	mutex_lock(&data->mutex);
	ret = bmg160_set_घातer_state(data, true);
	अगर (ret < 0) अणु
		mutex_unlock(&data->mutex);
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(data->regmap, BMG160_REG_TEMP, &raw_val);
	अगर (ret < 0) अणु
		dev_err(dev, "Error reading reg_temp\n");
		bmg160_set_घातer_state(data, false);
		mutex_unlock(&data->mutex);
		वापस ret;
	पूर्ण

	*val = sign_extend32(raw_val, 7);
	ret = bmg160_set_घातer_state(data, false);
	mutex_unlock(&data->mutex);
	अगर (ret < 0)
		वापस ret;

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक bmg160_get_axis(काष्ठा bmg160_data *data, पूर्णांक axis, पूर्णांक *val)
अणु
	काष्ठा device *dev = regmap_get_device(data->regmap);
	पूर्णांक ret;
	__le16 raw_val;

	mutex_lock(&data->mutex);
	ret = bmg160_set_घातer_state(data, true);
	अगर (ret < 0) अणु
		mutex_unlock(&data->mutex);
		वापस ret;
	पूर्ण

	ret = regmap_bulk_पढ़ो(data->regmap, BMG160_AXIS_TO_REG(axis), &raw_val,
			       माप(raw_val));
	अगर (ret < 0) अणु
		dev_err(dev, "Error reading axis %d\n", axis);
		bmg160_set_घातer_state(data, false);
		mutex_unlock(&data->mutex);
		वापस ret;
	पूर्ण

	*val = sign_extend32(le16_to_cpu(raw_val), 15);
	ret = bmg160_set_घातer_state(data, false);
	mutex_unlock(&data->mutex);
	अगर (ret < 0)
		वापस ret;

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक bmg160_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा bmg160_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		चयन (chan->type) अणु
		हाल IIO_TEMP:
			वापस bmg160_get_temp(data, val);
		हाल IIO_ANGL_VEL:
			अगर (iio_buffer_enabled(indio_dev))
				वापस -EBUSY;
			अन्यथा
				वापस bmg160_get_axis(data, chan->scan_index,
						       val);
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_OFFSET:
		अगर (chan->type == IIO_TEMP) अणु
			*val = BMG160_TEMP_CENTER_VAL;
			वापस IIO_VAL_INT;
		पूर्ण अन्यथा
			वापस -EINVAL;
	हाल IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		वापस bmg160_get_filter(data, val);
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_TEMP:
			*val = 500;
			वापस IIO_VAL_INT;
		हाल IIO_ANGL_VEL:
		अणु
			पूर्णांक i;

			क्रम (i = 0; i < ARRAY_SIZE(bmg160_scale_table); ++i) अणु
				अगर (bmg160_scale_table[i].dps_range ==
							data->dps_range) अणु
					*val = 0;
					*val2 = bmg160_scale_table[i].scale;
					वापस IIO_VAL_INT_PLUS_MICRO;
				पूर्ण
			पूर्ण
			वापस -EINVAL;
		पूर्ण
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*val2 = 0;
		mutex_lock(&data->mutex);
		ret = bmg160_get_bw(data, val);
		mutex_unlock(&data->mutex);
		वापस ret;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक bmg160_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा bmg160_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		mutex_lock(&data->mutex);
		/*
		 * Section 4.2 of spec
		 * In suspend mode, the only supported operations are पढ़ोing
		 * रेजिस्टरs as well as writing to the (0x14) softreset
		 * रेजिस्टर. Since we will be in suspend mode by शेष, change
		 * mode to घातer on क्रम other ग_लिखोs.
		 */
		ret = bmg160_set_घातer_state(data, true);
		अगर (ret < 0) अणु
			mutex_unlock(&data->mutex);
			वापस ret;
		पूर्ण
		ret = bmg160_set_bw(data, val);
		अगर (ret < 0) अणु
			bmg160_set_घातer_state(data, false);
			mutex_unlock(&data->mutex);
			वापस ret;
		पूर्ण
		ret = bmg160_set_घातer_state(data, false);
		mutex_unlock(&data->mutex);
		वापस ret;
	हाल IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		अगर (val2)
			वापस -EINVAL;

		mutex_lock(&data->mutex);
		ret = bmg160_set_घातer_state(data, true);
		अगर (ret < 0) अणु
			bmg160_set_घातer_state(data, false);
			mutex_unlock(&data->mutex);
			वापस ret;
		पूर्ण
		ret = bmg160_set_filter(data, val);
		अगर (ret < 0) अणु
			bmg160_set_घातer_state(data, false);
			mutex_unlock(&data->mutex);
			वापस ret;
		पूर्ण
		ret = bmg160_set_घातer_state(data, false);
		mutex_unlock(&data->mutex);
		वापस ret;
	हाल IIO_CHAN_INFO_SCALE:
		अगर (val)
			वापस -EINVAL;

		mutex_lock(&data->mutex);
		/* Refer to comments above क्रम the suspend mode ops */
		ret = bmg160_set_घातer_state(data, true);
		अगर (ret < 0) अणु
			mutex_unlock(&data->mutex);
			वापस ret;
		पूर्ण
		ret = bmg160_set_scale(data, val2);
		अगर (ret < 0) अणु
			bmg160_set_घातer_state(data, false);
			mutex_unlock(&data->mutex);
			वापस ret;
		पूर्ण
		ret = bmg160_set_घातer_state(data, false);
		mutex_unlock(&data->mutex);
		वापस ret;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक bmg160_पढ़ो_event(काष्ठा iio_dev *indio_dev,
			     स्थिर काष्ठा iio_chan_spec *chan,
			     क्रमागत iio_event_type type,
			     क्रमागत iio_event_direction dir,
			     क्रमागत iio_event_info info,
			     पूर्णांक *val, पूर्णांक *val2)
अणु
	काष्ठा bmg160_data *data = iio_priv(indio_dev);

	*val2 = 0;
	चयन (info) अणु
	हाल IIO_EV_INFO_VALUE:
		*val = data->slope_thres & BMG160_SLOPE_THRES_MASK;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक bmg160_ग_लिखो_event(काष्ठा iio_dev *indio_dev,
			      स्थिर काष्ठा iio_chan_spec *chan,
			      क्रमागत iio_event_type type,
			      क्रमागत iio_event_direction dir,
			      क्रमागत iio_event_info info,
			      पूर्णांक val, पूर्णांक val2)
अणु
	काष्ठा bmg160_data *data = iio_priv(indio_dev);

	चयन (info) अणु
	हाल IIO_EV_INFO_VALUE:
		अगर (data->ev_enable_state)
			वापस -EBUSY;
		data->slope_thres &= ~BMG160_SLOPE_THRES_MASK;
		data->slope_thres |= (val & BMG160_SLOPE_THRES_MASK);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bmg160_पढ़ो_event_config(काष्ठा iio_dev *indio_dev,
				    स्थिर काष्ठा iio_chan_spec *chan,
				    क्रमागत iio_event_type type,
				    क्रमागत iio_event_direction dir)
अणु

	काष्ठा bmg160_data *data = iio_priv(indio_dev);

	वापस data->ev_enable_state;
पूर्ण

अटल पूर्णांक bmg160_ग_लिखो_event_config(काष्ठा iio_dev *indio_dev,
				     स्थिर काष्ठा iio_chan_spec *chan,
				     क्रमागत iio_event_type type,
				     क्रमागत iio_event_direction dir,
				     पूर्णांक state)
अणु
	काष्ठा bmg160_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	अगर (state && data->ev_enable_state)
		वापस 0;

	mutex_lock(&data->mutex);

	अगर (!state && data->motion_trigger_on) अणु
		data->ev_enable_state = 0;
		mutex_unlock(&data->mutex);
		वापस 0;
	पूर्ण
	/*
	 * We will expect the enable and disable to करो operation in
	 * in reverse order. This will happen here anyway as our
	 * resume operation uses sync mode runसमय pm calls, the
	 * suspend operation will be delayed by स्वतःsuspend delay
	 * So the disable operation will still happen in reverse of
	 * enable operation. When runसमय pm is disabled the mode
	 * is always on so sequence करोesn't matter
	 */
	ret = bmg160_set_घातer_state(data, state);
	अगर (ret < 0) अणु
		mutex_unlock(&data->mutex);
		वापस ret;
	पूर्ण

	ret =  bmg160_setup_any_motion_पूर्णांकerrupt(data, state);
	अगर (ret < 0) अणु
		bmg160_set_घातer_state(data, false);
		mutex_unlock(&data->mutex);
		वापस ret;
	पूर्ण

	data->ev_enable_state = state;
	mutex_unlock(&data->mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_mount_matrix *
bmg160_get_mount_matrix(स्थिर काष्ठा iio_dev *indio_dev,
			 स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा bmg160_data *data = iio_priv(indio_dev);

	वापस &data->orientation;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec_ext_info bmg160_ext_info[] = अणु
	IIO_MOUNT_MATRIX(IIO_SHARED_BY_सूची, bmg160_get_mount_matrix),
	अणु पूर्ण
पूर्ण;

अटल IIO_CONST_ATTR_SAMP_FREQ_AVAIL("100 200 400 1000 2000");

अटल IIO_CONST_ATTR(in_anglvel_scale_available,
		      "0.001065 0.000532 0.000266 0.000133 0.000066");

अटल काष्ठा attribute *bmg160_attributes[] = अणु
	&iio_स्थिर_attr_sampling_frequency_available.dev_attr.attr,
	&iio_स्थिर_attr_in_anglvel_scale_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group bmg160_attrs_group = अणु
	.attrs = bmg160_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_event_spec bmg160_event = अणु
		.type = IIO_EV_TYPE_ROC,
		.dir = IIO_EV_सूची_EITHER,
		.mask_shared_by_type = BIT(IIO_EV_INFO_VALUE) |
				       BIT(IIO_EV_INFO_ENABLE)
पूर्ण;

#घोषणा BMG160_CHANNEL(_axis) अणु					\
	.type = IIO_ANGL_VEL,						\
	.modअगरied = 1,							\
	.channel2 = IIO_MOD_##_axis,					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),			\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) |		\
		BIT(IIO_CHAN_INFO_SAMP_FREQ) |				\
		BIT(IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY),	\
	.scan_index = AXIS_##_axis,					\
	.scan_type = अणु							\
		.sign = 's',						\
		.realbits = 16,					\
		.storagebits = 16,					\
		.endianness = IIO_LE,					\
	पूर्ण,								\
	.ext_info = bmg160_ext_info,					\
	.event_spec = &bmg160_event,					\
	.num_event_specs = 1						\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec bmg160_channels[] = अणु
	अणु
		.type = IIO_TEMP,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE) |
				      BIT(IIO_CHAN_INFO_OFFSET),
		.scan_index = -1,
	पूर्ण,
	BMG160_CHANNEL(X),
	BMG160_CHANNEL(Y),
	BMG160_CHANNEL(Z),
	IIO_CHAN_SOFT_TIMESTAMP(3),
पूर्ण;

अटल स्थिर काष्ठा iio_info bmg160_info = अणु
	.attrs			= &bmg160_attrs_group,
	.पढ़ो_raw		= bmg160_पढ़ो_raw,
	.ग_लिखो_raw		= bmg160_ग_लिखो_raw,
	.पढ़ो_event_value	= bmg160_पढ़ो_event,
	.ग_लिखो_event_value	= bmg160_ग_लिखो_event,
	.ग_लिखो_event_config	= bmg160_ग_लिखो_event_config,
	.पढ़ो_event_config	= bmg160_पढ़ो_event_config,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ bmg160_accel_scan_masks[] = अणु
					BIT(AXIS_X) | BIT(AXIS_Y) | BIT(AXIS_Z),
					0पूर्ण;

अटल irqवापस_t bmg160_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा bmg160_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->mutex);
	ret = regmap_bulk_पढ़ो(data->regmap, BMG160_REG_XOUT_L,
			       data->buffer, AXIS_MAX * 2);
	mutex_unlock(&data->mutex);
	अगर (ret < 0)
		जाओ err;

	iio_push_to_buffers_with_बारtamp(indio_dev, data->buffer,
					   pf->बारtamp);
err:
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम bmg160_trig_reen(काष्ठा iio_trigger *trig)
अणु
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	काष्ठा bmg160_data *data = iio_priv(indio_dev);
	काष्ठा device *dev = regmap_get_device(data->regmap);
	पूर्णांक ret;

	/* new data पूर्णांकerrupts करोn't need ack */
	अगर (data->dपढ़ोy_trigger_on)
		वापस;

	/* Set latched mode पूर्णांकerrupt and clear any latched पूर्णांकerrupt */
	ret = regmap_ग_लिखो(data->regmap, BMG160_REG_INT_RST_LATCH,
			   BMG160_INT_MODE_LATCH_INT |
			   BMG160_INT_MODE_LATCH_RESET);
	अगर (ret < 0)
		dev_err(dev, "Error writing reg_rst_latch\n");
पूर्ण

अटल पूर्णांक bmg160_data_rdy_trigger_set_state(काष्ठा iio_trigger *trig,
					     bool state)
अणु
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	काष्ठा bmg160_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->mutex);

	अगर (!state && data->ev_enable_state && data->motion_trigger_on) अणु
		data->motion_trigger_on = false;
		mutex_unlock(&data->mutex);
		वापस 0;
	पूर्ण

	/*
	 * Refer to comment in bmg160_ग_लिखो_event_config क्रम
	 * enable/disable operation order
	 */
	ret = bmg160_set_घातer_state(data, state);
	अगर (ret < 0) अणु
		mutex_unlock(&data->mutex);
		वापस ret;
	पूर्ण
	अगर (data->motion_trig == trig)
		ret =  bmg160_setup_any_motion_पूर्णांकerrupt(data, state);
	अन्यथा
		ret = bmg160_setup_new_data_पूर्णांकerrupt(data, state);
	अगर (ret < 0) अणु
		bmg160_set_घातer_state(data, false);
		mutex_unlock(&data->mutex);
		वापस ret;
	पूर्ण
	अगर (data->motion_trig == trig)
		data->motion_trigger_on = state;
	अन्यथा
		data->dपढ़ोy_trigger_on = state;

	mutex_unlock(&data->mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops bmg160_trigger_ops = अणु
	.set_trigger_state = bmg160_data_rdy_trigger_set_state,
	.reenable = bmg160_trig_reen,
पूर्ण;

अटल irqवापस_t bmg160_event_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा bmg160_data *data = iio_priv(indio_dev);
	काष्ठा device *dev = regmap_get_device(data->regmap);
	पूर्णांक ret;
	पूर्णांक dir;
	अचिन्हित पूर्णांक val;

	ret = regmap_पढ़ो(data->regmap, BMG160_REG_INT_STATUS_2, &val);
	अगर (ret < 0) अणु
		dev_err(dev, "Error reading reg_int_status2\n");
		जाओ ack_पूर्णांकr_status;
	पूर्ण

	अगर (val & 0x08)
		dir = IIO_EV_सूची_RISING;
	अन्यथा
		dir = IIO_EV_सूची_FALLING;

	अगर (val & BMG160_ANY_MOTION_BIT_X)
		iio_push_event(indio_dev, IIO_MOD_EVENT_CODE(IIO_ANGL_VEL,
							     0,
							     IIO_MOD_X,
							     IIO_EV_TYPE_ROC,
							     dir),
			       iio_get_समय_ns(indio_dev));
	अगर (val & BMG160_ANY_MOTION_BIT_Y)
		iio_push_event(indio_dev, IIO_MOD_EVENT_CODE(IIO_ANGL_VEL,
							     0,
							     IIO_MOD_Y,
							     IIO_EV_TYPE_ROC,
							     dir),
			       iio_get_समय_ns(indio_dev));
	अगर (val & BMG160_ANY_MOTION_BIT_Z)
		iio_push_event(indio_dev, IIO_MOD_EVENT_CODE(IIO_ANGL_VEL,
							     0,
							     IIO_MOD_Z,
							     IIO_EV_TYPE_ROC,
							     dir),
			       iio_get_समय_ns(indio_dev));

ack_पूर्णांकr_status:
	अगर (!data->dपढ़ोy_trigger_on) अणु
		ret = regmap_ग_लिखो(data->regmap, BMG160_REG_INT_RST_LATCH,
				   BMG160_INT_MODE_LATCH_INT |
				   BMG160_INT_MODE_LATCH_RESET);
		अगर (ret < 0)
			dev_err(dev, "Error writing reg_rst_latch\n");
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t bmg160_data_rdy_trig_poll(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा bmg160_data *data = iio_priv(indio_dev);

	अगर (data->dपढ़ोy_trigger_on)
		iio_trigger_poll(data->dपढ़ोy_trig);
	अन्यथा अगर (data->motion_trigger_on)
		iio_trigger_poll(data->motion_trig);

	अगर (data->ev_enable_state)
		वापस IRQ_WAKE_THREAD;
	अन्यथा
		वापस IRQ_HANDLED;

पूर्ण

अटल पूर्णांक bmg160_buffer_preenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा bmg160_data *data = iio_priv(indio_dev);

	वापस bmg160_set_घातer_state(data, true);
पूर्ण

अटल पूर्णांक bmg160_buffer_postdisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा bmg160_data *data = iio_priv(indio_dev);

	वापस bmg160_set_घातer_state(data, false);
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops bmg160_buffer_setup_ops = अणु
	.preenable = bmg160_buffer_preenable,
	.postdisable = bmg160_buffer_postdisable,
पूर्ण;

अटल स्थिर अक्षर *bmg160_match_acpi_device(काष्ठा device *dev)
अणु
	स्थिर काष्ठा acpi_device_id *id;

	id = acpi_match_device(dev->driver->acpi_match_table, dev);
	अगर (!id)
		वापस शून्य;

	वापस dev_name(dev);
पूर्ण

अटल व्योम bmg160_disable_regulators(व्योम *d)
अणु
	काष्ठा bmg160_data *data = d;

	regulator_bulk_disable(ARRAY_SIZE(data->regulators), data->regulators);
पूर्ण

पूर्णांक bmg160_core_probe(काष्ठा device *dev, काष्ठा regmap *regmap, पूर्णांक irq,
		      स्थिर अक्षर *name)
अणु
	काष्ठा bmg160_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	dev_set_drvdata(dev, indio_dev);
	data->irq = irq;
	data->regmap = regmap;

	data->regulators[0].supply = "vdd";
	data->regulators[1].supply = "vddio";
	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(data->regulators),
				      data->regulators);
	अगर (ret)
		वापस dev_err_probe(dev, ret, "Failed to get regulators\n");

	ret = regulator_bulk_enable(ARRAY_SIZE(data->regulators),
				    data->regulators);
	अगर (ret)
		वापस ret;

	ret = devm_add_action_or_reset(dev, bmg160_disable_regulators, data);
	अगर (ret)
		वापस ret;

	ret = iio_पढ़ो_mount_matrix(dev, "mount-matrix",
				&data->orientation);
	अगर (ret)
		वापस ret;

	ret = bmg160_chip_init(data);
	अगर (ret < 0)
		वापस ret;

	mutex_init(&data->mutex);

	अगर (ACPI_HANDLE(dev))
		name = bmg160_match_acpi_device(dev);

	indio_dev->channels = bmg160_channels;
	indio_dev->num_channels = ARRAY_SIZE(bmg160_channels);
	indio_dev->name = name;
	indio_dev->available_scan_masks = bmg160_accel_scan_masks;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &bmg160_info;

	अगर (data->irq > 0) अणु
		ret = devm_request_thपढ़ोed_irq(dev,
						data->irq,
						bmg160_data_rdy_trig_poll,
						bmg160_event_handler,
						IRQF_TRIGGER_RISING,
						BMG160_IRQ_NAME,
						indio_dev);
		अगर (ret)
			वापस ret;

		data->dपढ़ोy_trig = devm_iio_trigger_alloc(dev,
							   "%s-dev%d",
							   indio_dev->name,
							   indio_dev->id);
		अगर (!data->dपढ़ोy_trig)
			वापस -ENOMEM;

		data->motion_trig = devm_iio_trigger_alloc(dev,
							  "%s-any-motion-dev%d",
							  indio_dev->name,
							  indio_dev->id);
		अगर (!data->motion_trig)
			वापस -ENOMEM;

		data->dपढ़ोy_trig->ops = &bmg160_trigger_ops;
		iio_trigger_set_drvdata(data->dपढ़ोy_trig, indio_dev);
		ret = iio_trigger_रेजिस्टर(data->dपढ़ोy_trig);
		अगर (ret)
			वापस ret;

		data->motion_trig->ops = &bmg160_trigger_ops;
		iio_trigger_set_drvdata(data->motion_trig, indio_dev);
		ret = iio_trigger_रेजिस्टर(data->motion_trig);
		अगर (ret) अणु
			data->motion_trig = शून्य;
			जाओ err_trigger_unरेजिस्टर;
		पूर्ण
	पूर्ण

	ret = iio_triggered_buffer_setup(indio_dev,
					 iio_pollfunc_store_समय,
					 bmg160_trigger_handler,
					 &bmg160_buffer_setup_ops);
	अगर (ret < 0) अणु
		dev_err(dev,
			"iio triggered buffer setup failed\n");
		जाओ err_trigger_unरेजिस्टर;
	पूर्ण

	ret = pm_runसमय_set_active(dev);
	अगर (ret)
		जाओ err_buffer_cleanup;

	pm_runसमय_enable(dev);
	pm_runसमय_set_स्वतःsuspend_delay(dev,
					 BMG160_AUTO_SUSPEND_DELAY_MS);
	pm_runसमय_use_स्वतःsuspend(dev);

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0) अणु
		dev_err(dev, "unable to register iio device\n");
		जाओ err_buffer_cleanup;
	पूर्ण

	वापस 0;

err_buffer_cleanup:
	iio_triggered_buffer_cleanup(indio_dev);
err_trigger_unरेजिस्टर:
	अगर (data->dपढ़ोy_trig)
		iio_trigger_unरेजिस्टर(data->dपढ़ोy_trig);
	अगर (data->motion_trig)
		iio_trigger_unरेजिस्टर(data->motion_trig);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(bmg160_core_probe);

व्योम bmg160_core_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा bmg160_data *data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	pm_runसमय_disable(dev);
	pm_runसमय_set_suspended(dev);
	pm_runसमय_put_noidle(dev);

	iio_triggered_buffer_cleanup(indio_dev);

	अगर (data->dपढ़ोy_trig) अणु
		iio_trigger_unरेजिस्टर(data->dपढ़ोy_trig);
		iio_trigger_unरेजिस्टर(data->motion_trig);
	पूर्ण

	mutex_lock(&data->mutex);
	bmg160_set_mode(data, BMG160_MODE_DEEP_SUSPEND);
	mutex_unlock(&data->mutex);
पूर्ण
EXPORT_SYMBOL_GPL(bmg160_core_हटाओ);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक bmg160_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा bmg160_data *data = iio_priv(indio_dev);

	mutex_lock(&data->mutex);
	bmg160_set_mode(data, BMG160_MODE_SUSPEND);
	mutex_unlock(&data->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक bmg160_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा bmg160_data *data = iio_priv(indio_dev);

	mutex_lock(&data->mutex);
	अगर (data->dपढ़ोy_trigger_on || data->motion_trigger_on ||
							data->ev_enable_state)
		bmg160_set_mode(data, BMG160_MODE_NORMAL);
	mutex_unlock(&data->mutex);

	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल पूर्णांक bmg160_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा bmg160_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = bmg160_set_mode(data, BMG160_MODE_SUSPEND);
	अगर (ret < 0) अणु
		dev_err(dev, "set mode failed\n");
		वापस -EAGAIN;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bmg160_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा bmg160_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = bmg160_set_mode(data, BMG160_MODE_NORMAL);
	अगर (ret < 0)
		वापस ret;

	msleep_पूर्णांकerruptible(BMG160_MAX_STARTUP_TIME_MS);

	वापस 0;
पूर्ण
#पूर्ण_अगर

स्थिर काष्ठा dev_pm_ops bmg160_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(bmg160_suspend, bmg160_resume)
	SET_RUNTIME_PM_OPS(bmg160_runसमय_suspend,
			   bmg160_runसमय_resume, शून्य)
पूर्ण;
EXPORT_SYMBOL_GPL(bmg160_pm_ops);

MODULE_AUTHOR("Srinivas Pandruvada <srinivas.pandruvada@linux.intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("BMG160 Gyro driver");
