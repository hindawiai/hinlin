<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * VEML6030 Ambient Light Sensor
 *
 * Copyright (c) 2019, Rishi Gupta <gupt21@gmail.com>
 *
 * Datasheet: https://www.vishay.com/करोcs/84366/veml6030.pdf
 * Appnote-84367: https://www.vishay.com/करोcs/84367/designingveml6030.pdf
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/err.h>
#समावेश <linux/regmap.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/events.h>

/* Device रेजिस्टरs */
#घोषणा VEML6030_REG_ALS_CONF   0x00
#घोषणा VEML6030_REG_ALS_WH     0x01
#घोषणा VEML6030_REG_ALS_WL     0x02
#घोषणा VEML6030_REG_ALS_PSM    0x03
#घोषणा VEML6030_REG_ALS_DATA   0x04
#घोषणा VEML6030_REG_WH_DATA    0x05
#घोषणा VEML6030_REG_ALS_INT    0x06

/* Bit masks क्रम specअगरic functionality */
#घोषणा VEML6030_ALS_IT       GENMASK(9, 6)
#घोषणा VEML6030_PSM          GENMASK(2, 1)
#घोषणा VEML6030_ALS_PERS     GENMASK(5, 4)
#घोषणा VEML6030_ALS_GAIN     GENMASK(12, 11)
#घोषणा VEML6030_PSM_EN       BIT(0)
#घोषणा VEML6030_INT_TH_LOW   BIT(15)
#घोषणा VEML6030_INT_TH_HIGH  BIT(14)
#घोषणा VEML6030_ALS_INT_EN   BIT(1)
#घोषणा VEML6030_ALS_SD       BIT(0)

/*
 * The resolution depends on both gain and पूर्णांकegration समय. The
 * cur_resolution stores one of the resolution mentioned in the
 * table during startup and माला_लो updated whenever पूर्णांकegration समय
 * or gain is changed.
 *
 * Table 'resolution and maximum detection range' in appnote 84367
 * is visualized as a 2D array. The cur_gain stores index of gain
 * in this table (0-3) जबतक the cur_पूर्णांकegration_समय holds index
 * of पूर्णांकegration समय (0-5).
 */
काष्ठा veml6030_data अणु
	काष्ठा i2c_client *client;
	काष्ठा regmap *regmap;
	पूर्णांक cur_resolution;
	पूर्णांक cur_gain;
	पूर्णांक cur_पूर्णांकegration_समय;
पूर्ण;

/* Integration समय available in seconds */
अटल IIO_CONST_ATTR(in_illuminance_पूर्णांकegration_समय_available,
				"0.025 0.05 0.1 0.2 0.4 0.8");

/*
 * Scale is 1/gain. Value 0.125 is ALS gain x (1/8), 0.25 is
 * ALS gain x (1/4), 1.0 = ALS gain x 1 and 2.0 is ALS gain x 2.
 */
अटल IIO_CONST_ATTR(in_illuminance_scale_available,
				"0.125 0.25 1.0 2.0");

अटल काष्ठा attribute *veml6030_attributes[] = अणु
	&iio_स्थिर_attr_in_illuminance_पूर्णांकegration_समय_available.dev_attr.attr,
	&iio_स्थिर_attr_in_illuminance_scale_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group veml6030_attr_group = अणु
	.attrs = veml6030_attributes,
पूर्ण;

/*
 * Persistence = 1/2/4/8 x पूर्णांकegration समय
 * Minimum समय क्रम which light पढ़ोings must stay above configured
 * threshold to निश्चित the पूर्णांकerrupt.
 */
अटल स्थिर अक्षर * स्थिर period_values[] = अणु
		"0.1 0.2 0.4 0.8",
		"0.2 0.4 0.8 1.6",
		"0.4 0.8 1.6 3.2",
		"0.8 1.6 3.2 6.4",
		"0.05 0.1 0.2 0.4",
		"0.025 0.050 0.1 0.2"
पूर्ण;

/*
 * Return list of valid period values in seconds corresponding to
 * the currently active पूर्णांकegration समय.
 */
अटल sमाप_प्रकार in_illuminance_period_available_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक ret, reg, x;
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा veml6030_data *data = iio_priv(indio_dev);

	ret = regmap_पढ़ो(data->regmap, VEML6030_REG_ALS_CONF, &reg);
	अगर (ret) अणु
		dev_err(&data->client->dev,
				"can't read als conf register %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ((reg >> 6) & 0xF);
	चयन (ret) अणु
	हाल 0:
	हाल 1:
	हाल 2:
	हाल 3:
		x = ret;
		अवरोध;
	हाल 8:
		x = 4;
		अवरोध;
	हाल 12:
		x = 5;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", period_values[x]);
पूर्ण

अटल IIO_DEVICE_ATTR_RO(in_illuminance_period_available, 0);

अटल काष्ठा attribute *veml6030_event_attributes[] = अणु
	&iio_dev_attr_in_illuminance_period_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group veml6030_event_attr_group = अणु
	.attrs = veml6030_event_attributes,
पूर्ण;

अटल पूर्णांक veml6030_als_pwr_on(काष्ठा veml6030_data *data)
अणु
	वापस regmap_update_bits(data->regmap, VEML6030_REG_ALS_CONF,
				 VEML6030_ALS_SD, 0);
पूर्ण

अटल पूर्णांक veml6030_als_shut_करोwn(काष्ठा veml6030_data *data)
अणु
	वापस regmap_update_bits(data->regmap, VEML6030_REG_ALS_CONF,
				 VEML6030_ALS_SD, 1);
पूर्ण

अटल व्योम veml6030_als_shut_करोwn_action(व्योम *data)
अणु
	veml6030_als_shut_करोwn(data);
पूर्ण

अटल स्थिर काष्ठा iio_event_spec veml6030_event_spec[] = अणु
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_RISING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE),
	पूर्ण, अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_FALLING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE),
	पूर्ण, अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_EITHER,
		.mask_separate = BIT(IIO_EV_INFO_PERIOD) |
		BIT(IIO_EV_INFO_ENABLE),
	पूर्ण,
पूर्ण;

/* Channel number */
क्रमागत veml6030_chan अणु
	CH_ALS,
	CH_WHITE,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec veml6030_channels[] = अणु
	अणु
		.type = IIO_LIGHT,
		.channel = CH_ALS,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				BIT(IIO_CHAN_INFO_PROCESSED) |
				BIT(IIO_CHAN_INFO_INT_TIME) |
				BIT(IIO_CHAN_INFO_SCALE),
		.event_spec = veml6030_event_spec,
		.num_event_specs = ARRAY_SIZE(veml6030_event_spec),
	पूर्ण,
	अणु
		.type = IIO_INTENSITY,
		.channel = CH_WHITE,
		.modअगरied = 1,
		.channel2 = IIO_MOD_LIGHT_BOTH,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				BIT(IIO_CHAN_INFO_PROCESSED),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config veml6030_regmap_config = अणु
	.name = "veml6030_regmap",
	.reg_bits = 8,
	.val_bits = 16,
	.max_रेजिस्टर = VEML6030_REG_ALS_INT,
	.val_क्रमmat_endian = REGMAP_ENDIAN_LITTLE,
पूर्ण;

अटल पूर्णांक veml6030_get_पूर्णांकgrn_पंचांग(काष्ठा iio_dev *indio_dev,
						पूर्णांक *val, पूर्णांक *val2)
अणु
	पूर्णांक ret, reg;
	काष्ठा veml6030_data *data = iio_priv(indio_dev);

	ret = regmap_पढ़ो(data->regmap, VEML6030_REG_ALS_CONF, &reg);
	अगर (ret) अणु
		dev_err(&data->client->dev,
				"can't read als conf register %d\n", ret);
		वापस ret;
	पूर्ण

	चयन ((reg >> 6) & 0xF) अणु
	हाल 0:
		*val2 = 100000;
		अवरोध;
	हाल 1:
		*val2 = 200000;
		अवरोध;
	हाल 2:
		*val2 = 400000;
		अवरोध;
	हाल 3:
		*val2 = 800000;
		अवरोध;
	हाल 8:
		*val2 = 50000;
		अवरोध;
	हाल 12:
		*val2 = 25000;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	*val = 0;
	वापस IIO_VAL_INT_PLUS_MICRO;
पूर्ण

अटल पूर्णांक veml6030_set_पूर्णांकgrn_पंचांग(काष्ठा iio_dev *indio_dev,
						पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक ret, new_पूर्णांक_समय, पूर्णांक_idx;
	काष्ठा veml6030_data *data = iio_priv(indio_dev);

	अगर (val)
		वापस -EINVAL;

	चयन (val2) अणु
	हाल 25000:
		new_पूर्णांक_समय = 0x300;
		पूर्णांक_idx = 5;
		अवरोध;
	हाल 50000:
		new_पूर्णांक_समय = 0x200;
		पूर्णांक_idx = 4;
		अवरोध;
	हाल 100000:
		new_पूर्णांक_समय = 0x00;
		पूर्णांक_idx = 3;
		अवरोध;
	हाल 200000:
		new_पूर्णांक_समय = 0x40;
		पूर्णांक_idx = 2;
		अवरोध;
	हाल 400000:
		new_पूर्णांक_समय = 0x80;
		पूर्णांक_idx = 1;
		अवरोध;
	हाल 800000:
		new_पूर्णांक_समय = 0xC0;
		पूर्णांक_idx = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = regmap_update_bits(data->regmap, VEML6030_REG_ALS_CONF,
					VEML6030_ALS_IT, new_पूर्णांक_समय);
	अगर (ret) अणु
		dev_err(&data->client->dev,
				"can't update als integration time %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * Cache current पूर्णांकegration समय and update resolution. For every
	 * increase in पूर्णांकegration समय to next level, resolution is halved
	 * and vice-versa.
	 */
	अगर (data->cur_पूर्णांकegration_समय < पूर्णांक_idx)
		data->cur_resolution <<= पूर्णांक_idx - data->cur_पूर्णांकegration_समय;
	अन्यथा अगर (data->cur_पूर्णांकegration_समय > पूर्णांक_idx)
		data->cur_resolution >>= data->cur_पूर्णांकegration_समय - पूर्णांक_idx;

	data->cur_पूर्णांकegration_समय = पूर्णांक_idx;

	वापस ret;
पूर्ण

अटल पूर्णांक veml6030_पढ़ो_persistence(काष्ठा iio_dev *indio_dev,
						पूर्णांक *val, पूर्णांक *val2)
अणु
	पूर्णांक ret, reg, period, x, y;
	काष्ठा veml6030_data *data = iio_priv(indio_dev);

	ret = veml6030_get_पूर्णांकgrn_पंचांग(indio_dev, &x, &y);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_पढ़ो(data->regmap, VEML6030_REG_ALS_CONF, &reg);
	अगर (ret) अणु
		dev_err(&data->client->dev,
				"can't read als conf register %d\n", ret);
	पूर्ण

	/* पूर्णांकegration समय multiplied by 1/2/4/8 */
	period = y * (1 << ((reg >> 4) & 0x03));

	*val = period / 1000000;
	*val2 = period % 1000000;

	वापस IIO_VAL_INT_PLUS_MICRO;
पूर्ण

अटल पूर्णांक veml6030_ग_लिखो_persistence(काष्ठा iio_dev *indio_dev,
						पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक ret, period, x, y;
	काष्ठा veml6030_data *data = iio_priv(indio_dev);

	ret = veml6030_get_पूर्णांकgrn_पंचांग(indio_dev, &x, &y);
	अगर (ret < 0)
		वापस ret;

	अगर (!val) अणु
		period = val2 / y;
	पूर्ण अन्यथा अणु
		अगर ((val == 1) && (val2 == 600000))
			period = 1600000 / y;
		अन्यथा अगर ((val == 3) && (val2 == 200000))
			period = 3200000 / y;
		अन्यथा अगर ((val == 6) && (val2 == 400000))
			period = 6400000 / y;
		अन्यथा
			period = -1;
	पूर्ण

	अगर (period <= 0 || period > 8 || hweight8(period) != 1)
		वापस -EINVAL;

	ret = regmap_update_bits(data->regmap, VEML6030_REG_ALS_CONF,
				VEML6030_ALS_PERS, (ffs(period) - 1) << 4);
	अगर (ret)
		dev_err(&data->client->dev,
				"can't set persistence value %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक veml6030_set_als_gain(काष्ठा iio_dev *indio_dev,
						पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक ret, new_gain, gain_idx;
	काष्ठा veml6030_data *data = iio_priv(indio_dev);

	अगर (val == 0 && val2 == 125000) अणु
		new_gain = 0x1000; /* 0x02 << 11 */
		gain_idx = 3;
	पूर्ण अन्यथा अगर (val == 0 && val2 == 250000) अणु
		new_gain = 0x1800;
		gain_idx = 2;
	पूर्ण अन्यथा अगर (val == 1 && val2 == 0) अणु
		new_gain = 0x00;
		gain_idx = 1;
	पूर्ण अन्यथा अगर (val == 2 && val2 == 0) अणु
		new_gain = 0x800;
		gain_idx = 0;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	ret = regmap_update_bits(data->regmap, VEML6030_REG_ALS_CONF,
					VEML6030_ALS_GAIN, new_gain);
	अगर (ret) अणु
		dev_err(&data->client->dev,
				"can't set als gain %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * Cache currently set gain & update resolution. For every
	 * increase in the gain to next level, resolution is halved
	 * and vice-versa.
	 */
	अगर (data->cur_gain < gain_idx)
		data->cur_resolution <<= gain_idx - data->cur_gain;
	अन्यथा अगर (data->cur_gain > gain_idx)
		data->cur_resolution >>= data->cur_gain - gain_idx;

	data->cur_gain = gain_idx;

	वापस ret;
पूर्ण

अटल पूर्णांक veml6030_get_als_gain(काष्ठा iio_dev *indio_dev,
						पूर्णांक *val, पूर्णांक *val2)
अणु
	पूर्णांक ret, reg;
	काष्ठा veml6030_data *data = iio_priv(indio_dev);

	ret = regmap_पढ़ो(data->regmap, VEML6030_REG_ALS_CONF, &reg);
	अगर (ret) अणु
		dev_err(&data->client->dev,
				"can't read als conf register %d\n", ret);
		वापस ret;
	पूर्ण

	चयन ((reg >> 11) & 0x03) अणु
	हाल 0:
		*val = 1;
		*val2 = 0;
		अवरोध;
	हाल 1:
		*val = 2;
		*val2 = 0;
		अवरोध;
	हाल 2:
		*val = 0;
		*val2 = 125000;
		अवरोध;
	हाल 3:
		*val = 0;
		*val2 = 250000;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस IIO_VAL_INT_PLUS_MICRO;
पूर्ण

अटल पूर्णांक veml6030_पढ़ो_thresh(काष्ठा iio_dev *indio_dev,
						पूर्णांक *val, पूर्णांक *val2, पूर्णांक dir)
अणु
	पूर्णांक ret, reg;
	काष्ठा veml6030_data *data = iio_priv(indio_dev);

	अगर (dir == IIO_EV_सूची_RISING)
		ret = regmap_पढ़ो(data->regmap, VEML6030_REG_ALS_WH, &reg);
	अन्यथा
		ret = regmap_पढ़ो(data->regmap, VEML6030_REG_ALS_WL, &reg);
	अगर (ret) अणु
		dev_err(&data->client->dev,
				"can't read als threshold value %d\n", ret);
		वापस ret;
	पूर्ण

	*val = reg & 0xffff;
	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक veml6030_ग_लिखो_thresh(काष्ठा iio_dev *indio_dev,
						पूर्णांक val, पूर्णांक val2, पूर्णांक dir)
अणु
	पूर्णांक ret;
	काष्ठा veml6030_data *data = iio_priv(indio_dev);

	अगर (val > 0xFFFF || val < 0 || val2)
		वापस -EINVAL;

	अगर (dir == IIO_EV_सूची_RISING) अणु
		ret = regmap_ग_लिखो(data->regmap, VEML6030_REG_ALS_WH, val);
		अगर (ret)
			dev_err(&data->client->dev,
					"can't set high threshold %d\n", ret);
	पूर्ण अन्यथा अणु
		ret = regmap_ग_लिखो(data->regmap, VEML6030_REG_ALS_WL, val);
		अगर (ret)
			dev_err(&data->client->dev,
					"can't set low threshold %d\n", ret);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Provide both raw as well as light पढ़ोing in lux.
 * light (in lux) = resolution * raw पढ़ोing
 */
अटल पूर्णांक veml6030_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
			    पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक ret, reg;
	काष्ठा veml6030_data *data = iio_priv(indio_dev);
	काष्ठा regmap *regmap = data->regmap;
	काष्ठा device *dev = &data->client->dev;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
	हाल IIO_CHAN_INFO_PROCESSED:
		चयन (chan->type) अणु
		हाल IIO_LIGHT:
			ret = regmap_पढ़ो(regmap, VEML6030_REG_ALS_DATA, &reg);
			अगर (ret < 0) अणु
				dev_err(dev, "can't read als data %d\n", ret);
				वापस ret;
			पूर्ण
			अगर (mask == IIO_CHAN_INFO_PROCESSED) अणु
				*val = (reg * data->cur_resolution) / 10000;
				*val2 = (reg * data->cur_resolution) % 10000;
				वापस IIO_VAL_INT_PLUS_MICRO;
			पूर्ण
			*val = reg;
			वापस IIO_VAL_INT;
		हाल IIO_INTENSITY:
			ret = regmap_पढ़ो(regmap, VEML6030_REG_WH_DATA, &reg);
			अगर (ret < 0) अणु
				dev_err(dev, "can't read white data %d\n", ret);
				वापस ret;
			पूर्ण
			अगर (mask == IIO_CHAN_INFO_PROCESSED) अणु
				*val = (reg * data->cur_resolution) / 10000;
				*val2 = (reg * data->cur_resolution) % 10000;
				वापस IIO_VAL_INT_PLUS_MICRO;
			पूर्ण
			*val = reg;
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_INT_TIME:
		अगर (chan->type == IIO_LIGHT)
			वापस veml6030_get_पूर्णांकgrn_पंचांग(indio_dev, val, val2);
		वापस -EINVAL;
	हाल IIO_CHAN_INFO_SCALE:
		अगर (chan->type == IIO_LIGHT)
			वापस veml6030_get_als_gain(indio_dev, val, val2);
		वापस -EINVAL;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक veml6030_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *chan,
				पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_INT_TIME:
		चयन (chan->type) अणु
		हाल IIO_LIGHT:
			वापस veml6030_set_पूर्णांकgrn_पंचांग(indio_dev, val, val2);
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_LIGHT:
			वापस veml6030_set_als_gain(indio_dev, val, val2);
		शेष:
			वापस -EINVAL;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक veml6030_पढ़ो_event_val(काष्ठा iio_dev *indio_dev,
		स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
		क्रमागत iio_event_direction dir, क्रमागत iio_event_info info,
		पूर्णांक *val, पूर्णांक *val2)
अणु
	चयन (info) अणु
	हाल IIO_EV_INFO_VALUE:
		चयन (dir) अणु
		हाल IIO_EV_सूची_RISING:
		हाल IIO_EV_सूची_FALLING:
			वापस veml6030_पढ़ो_thresh(indio_dev, val, val2, dir);
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल IIO_EV_INFO_PERIOD:
		वापस veml6030_पढ़ो_persistence(indio_dev, val, val2);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक veml6030_ग_लिखो_event_val(काष्ठा iio_dev *indio_dev,
		स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
		क्रमागत iio_event_direction dir, क्रमागत iio_event_info info,
		पूर्णांक val, पूर्णांक val2)
अणु
	चयन (info) अणु
	हाल IIO_EV_INFO_VALUE:
		वापस veml6030_ग_लिखो_thresh(indio_dev, val, val2, dir);
	हाल IIO_EV_INFO_PERIOD:
		वापस veml6030_ग_लिखो_persistence(indio_dev, val, val2);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक veml6030_पढ़ो_पूर्णांकerrupt_config(काष्ठा iio_dev *indio_dev,
		स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
		क्रमागत iio_event_direction dir)
अणु
	पूर्णांक ret, reg;
	काष्ठा veml6030_data *data = iio_priv(indio_dev);

	ret = regmap_पढ़ो(data->regmap, VEML6030_REG_ALS_CONF, &reg);
	अगर (ret) अणु
		dev_err(&data->client->dev,
				"can't read als conf register %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (reg & VEML6030_ALS_INT_EN)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

/*
 * Sensor should not be measuring light when पूर्णांकerrupt is configured.
 * Thereक्रमe correct sequence to configure पूर्णांकerrupt functionality is:
 * shut करोwn -> enable/disable पूर्णांकerrupt -> घातer on
 *
 * state = 1 enables पूर्णांकerrupt, state = 0 disables पूर्णांकerrupt
 */
अटल पूर्णांक veml6030_ग_लिखो_पूर्णांकerrupt_config(काष्ठा iio_dev *indio_dev,
		स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
		क्रमागत iio_event_direction dir, पूर्णांक state)
अणु
	पूर्णांक ret;
	काष्ठा veml6030_data *data = iio_priv(indio_dev);

	अगर (state < 0 || state > 1)
		वापस -EINVAL;

	ret = veml6030_als_shut_करोwn(data);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev,
			"can't disable als to configure interrupt %d\n", ret);
		वापस ret;
	पूर्ण

	/* enable पूर्णांकerrupt + घातer on */
	ret = regmap_update_bits(data->regmap, VEML6030_REG_ALS_CONF,
			VEML6030_ALS_INT_EN | VEML6030_ALS_SD, state << 1);
	अगर (ret)
		dev_err(&data->client->dev,
			"can't enable interrupt & poweron als %d\n", ret);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info veml6030_info = अणु
	.पढ़ो_raw  = veml6030_पढ़ो_raw,
	.ग_लिखो_raw = veml6030_ग_लिखो_raw,
	.पढ़ो_event_value = veml6030_पढ़ो_event_val,
	.ग_लिखो_event_value	= veml6030_ग_लिखो_event_val,
	.पढ़ो_event_config = veml6030_पढ़ो_पूर्णांकerrupt_config,
	.ग_लिखो_event_config	= veml6030_ग_लिखो_पूर्णांकerrupt_config,
	.attrs = &veml6030_attr_group,
	.event_attrs = &veml6030_event_attr_group,
पूर्ण;

अटल स्थिर काष्ठा iio_info veml6030_info_no_irq = अणु
	.पढ़ो_raw  = veml6030_पढ़ो_raw,
	.ग_लिखो_raw = veml6030_ग_लिखो_raw,
	.attrs = &veml6030_attr_group,
पूर्ण;

अटल irqवापस_t veml6030_event_handler(पूर्णांक irq, व्योम *निजी)
अणु
	पूर्णांक ret, reg, evtdir;
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा veml6030_data *data = iio_priv(indio_dev);

	ret = regmap_पढ़ो(data->regmap, VEML6030_REG_ALS_INT, &reg);
	अगर (ret) अणु
		dev_err(&data->client->dev,
				"can't read als interrupt register %d\n", ret);
		वापस IRQ_HANDLED;
	पूर्ण

	/* Spurious पूर्णांकerrupt handling */
	अगर (!(reg & (VEML6030_INT_TH_HIGH | VEML6030_INT_TH_LOW)))
		वापस IRQ_NONE;

	अगर (reg & VEML6030_INT_TH_HIGH)
		evtdir = IIO_EV_सूची_RISING;
	अन्यथा
		evtdir = IIO_EV_सूची_FALLING;

	iio_push_event(indio_dev, IIO_UNMOD_EVENT_CODE(IIO_INTENSITY,
					0, IIO_EV_TYPE_THRESH, evtdir),
					iio_get_समय_ns(indio_dev));

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Set ALS gain to 1/8, पूर्णांकegration समय to 100 ms, PSM to mode 2,
 * persistence to 1 x पूर्णांकegration समय and the threshold
 * पूर्णांकerrupt disabled by शेष. First shutकरोwn the sensor,
 * update रेजिस्टरs and then घातer on the sensor.
 */
अटल पूर्णांक veml6030_hw_init(काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक ret, val;
	काष्ठा veml6030_data *data = iio_priv(indio_dev);
	काष्ठा i2c_client *client = data->client;

	ret = veml6030_als_shut_करोwn(data);
	अगर (ret) अणु
		dev_err(&client->dev, "can't shutdown als %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_ग_लिखो(data->regmap, VEML6030_REG_ALS_CONF, 0x1001);
	अगर (ret) अणु
		dev_err(&client->dev, "can't setup als configs %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_update_bits(data->regmap, VEML6030_REG_ALS_PSM,
				 VEML6030_PSM | VEML6030_PSM_EN, 0x03);
	अगर (ret) अणु
		dev_err(&client->dev, "can't setup default PSM %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_ग_लिखो(data->regmap, VEML6030_REG_ALS_WH, 0xFFFF);
	अगर (ret) अणु
		dev_err(&client->dev, "can't setup high threshold %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_ग_लिखो(data->regmap, VEML6030_REG_ALS_WL, 0x0000);
	अगर (ret) अणु
		dev_err(&client->dev, "can't setup low threshold %d\n", ret);
		वापस ret;
	पूर्ण

	ret = veml6030_als_pwr_on(data);
	अगर (ret) अणु
		dev_err(&client->dev, "can't poweron als %d\n", ret);
		वापस ret;
	पूर्ण

	/* Wait 4 ms to let processor & oscillator start correctly */
	usleep_range(4000, 4002);

	/* Clear stale पूर्णांकerrupt status bits अगर any during start */
	ret = regmap_पढ़ो(data->regmap, VEML6030_REG_ALS_INT, &val);
	अगर (ret < 0) अणु
		dev_err(&client->dev,
			"can't clear als interrupt status %d\n", ret);
		वापस ret;
	पूर्ण

	/* Cache currently active measurement parameters */
	data->cur_gain = 3;
	data->cur_resolution = 4608;
	data->cur_पूर्णांकegration_समय = 3;

	वापस ret;
पूर्ण

अटल पूर्णांक veml6030_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा veml6030_data *data;
	काष्ठा iio_dev *indio_dev;
	काष्ठा regmap *regmap;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		dev_err(&client->dev, "i2c adapter doesn't support plain i2c\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	regmap = devm_regmap_init_i2c(client, &veml6030_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&client->dev, "can't setup regmap\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	data->regmap = regmap;

	indio_dev->name = "veml6030";
	indio_dev->channels = veml6030_channels;
	indio_dev->num_channels = ARRAY_SIZE(veml6030_channels);
	indio_dev->modes = INDIO_सूचीECT_MODE;

	अगर (client->irq) अणु
		ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
						शून्य, veml6030_event_handler,
						IRQF_TRIGGER_LOW | IRQF_ONESHOT,
						"veml6030", indio_dev);
		अगर (ret < 0) अणु
			dev_err(&client->dev,
					"irq %d request failed\n", client->irq);
			वापस ret;
		पूर्ण
		indio_dev->info = &veml6030_info;
	पूर्ण अन्यथा अणु
		indio_dev->info = &veml6030_info_no_irq;
	पूर्ण

	ret = veml6030_hw_init(indio_dev);
	अगर (ret < 0)
		वापस ret;

	ret = devm_add_action_or_reset(&client->dev,
					veml6030_als_shut_करोwn_action, data);
	अगर (ret < 0)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

अटल पूर्णांक __maybe_unused veml6030_runसमय_suspend(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा veml6030_data *data = iio_priv(indio_dev);

	ret = veml6030_als_shut_करोwn(data);
	अगर (ret < 0)
		dev_err(&data->client->dev, "can't suspend als %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused veml6030_runसमय_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा veml6030_data *data = iio_priv(indio_dev);

	ret = veml6030_als_pwr_on(data);
	अगर (ret < 0)
		dev_err(&data->client->dev, "can't resume als %d\n", ret);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops veml6030_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(veml6030_runसमय_suspend,
				veml6030_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id veml6030_of_match[] = अणु
	अणु .compatible = "vishay,veml6030" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, veml6030_of_match);

अटल स्थिर काष्ठा i2c_device_id veml6030_id[] = अणु
	अणु "veml6030", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, veml6030_id);

अटल काष्ठा i2c_driver veml6030_driver = अणु
	.driver = अणु
		.name = "veml6030",
		.of_match_table = veml6030_of_match,
		.pm = &veml6030_pm_ops,
	पूर्ण,
	.probe = veml6030_probe,
	.id_table = veml6030_id,
पूर्ण;
module_i2c_driver(veml6030_driver);

MODULE_AUTHOR("Rishi Gupta <gupt21@gmail.com>");
MODULE_DESCRIPTION("VEML6030 Ambient Light Sensor");
MODULE_LICENSE("GPL v2");
