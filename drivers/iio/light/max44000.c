<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MAX44000 Ambient and Infrared Proximity Sensor
 *
 * Copyright (c) 2016, Intel Corporation.
 *
 * Data sheet: https://datasheets.maximपूर्णांकegrated.com/en/ds/MAX44000.pdf
 *
 * 7-bit I2C slave address 0x4a
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/util_macros.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/acpi.h>

#घोषणा MAX44000_DRV_NAME		"max44000"

/* Registers in datasheet order */
#घोषणा MAX44000_REG_STATUS		0x00
#घोषणा MAX44000_REG_CFG_MAIN		0x01
#घोषणा MAX44000_REG_CFG_RX		0x02
#घोषणा MAX44000_REG_CFG_TX		0x03
#घोषणा MAX44000_REG_ALS_DATA_HI	0x04
#घोषणा MAX44000_REG_ALS_DATA_LO	0x05
#घोषणा MAX44000_REG_PRX_DATA		0x16
#घोषणा MAX44000_REG_ALS_UPTHR_HI	0x06
#घोषणा MAX44000_REG_ALS_UPTHR_LO	0x07
#घोषणा MAX44000_REG_ALS_LOTHR_HI	0x08
#घोषणा MAX44000_REG_ALS_LOTHR_LO	0x09
#घोषणा MAX44000_REG_PST		0x0a
#घोषणा MAX44000_REG_PRX_IND		0x0b
#घोषणा MAX44000_REG_PRX_THR		0x0c
#घोषणा MAX44000_REG_TRIM_GAIN_GREEN	0x0f
#घोषणा MAX44000_REG_TRIM_GAIN_IR	0x10

/* REG_CFG bits */
#घोषणा MAX44000_CFG_ALSINTE            0x01
#घोषणा MAX44000_CFG_PRXINTE            0x02
#घोषणा MAX44000_CFG_MASK               0x1c
#घोषणा MAX44000_CFG_MODE_SHUTDOWN      0x00
#घोषणा MAX44000_CFG_MODE_ALS_GIR       0x04
#घोषणा MAX44000_CFG_MODE_ALS_G         0x08
#घोषणा MAX44000_CFG_MODE_ALS_IR        0x0c
#घोषणा MAX44000_CFG_MODE_ALS_PRX       0x10
#घोषणा MAX44000_CFG_MODE_PRX           0x14
#घोषणा MAX44000_CFG_TRIM               0x20

/*
 * Upper 4 bits are not करोcumented but start as 1 on घातerup
 * Setting them to 0 causes proximity to misbehave so set them to 1
 */
#घोषणा MAX44000_REG_CFG_RX_DEFAULT 0xf0

/* REG_RX bits */
#घोषणा MAX44000_CFG_RX_ALSTIM_MASK	0x0c
#घोषणा MAX44000_CFG_RX_ALSTIM_SHIFT	2
#घोषणा MAX44000_CFG_RX_ALSPGA_MASK	0x03
#घोषणा MAX44000_CFG_RX_ALSPGA_SHIFT	0

/* REG_TX bits */
#घोषणा MAX44000_LED_CURRENT_MASK	0xf
#घोषणा MAX44000_LED_CURRENT_MAX	11
#घोषणा MAX44000_LED_CURRENT_DEFAULT	6

#घोषणा MAX44000_ALSDATA_OVERFLOW	0x4000

काष्ठा max44000_data अणु
	काष्ठा mutex lock;
	काष्ठा regmap *regmap;
	/* Ensure naturally aligned बारtamp */
	काष्ठा अणु
		u16 channels[2];
		s64 ts __aligned(8);
	पूर्ण scan;
पूर्ण;

/* Default scale is set to the minimum of 0.03125 or 1 / (1 << 5) lux */
#घोषणा MAX44000_ALS_TO_LUX_DEFAULT_FRACTION_LOG2 5

/* Scale can be multiplied by up to 128x via ALSPGA क्रम measurement gain */
अटल स्थिर पूर्णांक max44000_alspga_shअगरt[] = अणु0, 2, 4, 7पूर्ण;
#घोषणा MAX44000_ALSPGA_MAX_SHIFT 7

/*
 * Scale can be multiplied by up to 64x via ALSTIM because of lost resolution
 *
 * This scaling factor is hidden from userspace and instead accounted क्रम when
 * पढ़ोing raw values from the device.
 *
 * This makes it possible to cleanly expose ALSPGA as IIO_CHAN_INFO_SCALE and
 * ALSTIM as IIO_CHAN_INFO_INT_TIME without the values affecting each other.
 *
 * Handling this पूर्णांकernally is also required क्रम buffer support because the
 * channel's scan_type can't be modअगरied dynamically.
 */
#घोषणा MAX44000_ALSTIM_SHIFT(alstim) (2 * (alstim))

/* Available पूर्णांकegration बार with pretty manual alignment: */
अटल स्थिर पूर्णांक max44000_पूर्णांक_समय_avail_ns_array[] = अणु
	   100000000,
	    25000000,
	     6250000,
	     1562500,
पूर्ण;
अटल स्थिर अक्षर max44000_पूर्णांक_समय_avail_str[] =
	"0.100 "
	"0.025 "
	"0.00625 "
	"0.0015625";

/* Available scales (पूर्णांकernal to ulux) with pretty manual alignment: */
अटल स्थिर पूर्णांक max44000_scale_avail_ulux_array[] = अणु
	    31250,
	   125000,
	   500000,
	  4000000,
पूर्ण;
अटल स्थिर अक्षर max44000_scale_avail_str[] =
	"0.03125 "
	"0.125 "
	"0.5 "
	 "4";

#घोषणा MAX44000_SCAN_INDEX_ALS 0
#घोषणा MAX44000_SCAN_INDEX_PRX 1

अटल स्थिर काष्ठा iio_chan_spec max44000_channels[] = अणु
	अणु
		.type = IIO_LIGHT,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) |
					    BIT(IIO_CHAN_INFO_INT_TIME),
		.scan_index = MAX44000_SCAN_INDEX_ALS,
		.scan_type = अणु
			.sign		= 'u',
			.realbits	= 14,
			.storagebits	= 16,
		पूर्ण
	पूर्ण,
	अणु
		.type = IIO_PROXIMITY,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.scan_index = MAX44000_SCAN_INDEX_PRX,
		.scan_type = अणु
			.sign		= 'u',
			.realbits	= 8,
			.storagebits	= 16,
		पूर्ण
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(2),
	अणु
		.type = IIO_CURRENT,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE),
		.extend_name = "led",
		.output = 1,
		.scan_index = -1,
	पूर्ण,
पूर्ण;

अटल पूर्णांक max44000_पढ़ो_alstim(काष्ठा max44000_data *data)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(data->regmap, MAX44000_REG_CFG_RX, &val);
	अगर (ret < 0)
		वापस ret;
	वापस (val & MAX44000_CFG_RX_ALSTIM_MASK) >> MAX44000_CFG_RX_ALSTIM_SHIFT;
पूर्ण

अटल पूर्णांक max44000_ग_लिखो_alstim(काष्ठा max44000_data *data, पूर्णांक val)
अणु
	वापस regmap_ग_लिखो_bits(data->regmap, MAX44000_REG_CFG_RX,
				 MAX44000_CFG_RX_ALSTIM_MASK,
				 val << MAX44000_CFG_RX_ALSTIM_SHIFT);
पूर्ण

अटल पूर्णांक max44000_पढ़ो_alspga(काष्ठा max44000_data *data)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(data->regmap, MAX44000_REG_CFG_RX, &val);
	अगर (ret < 0)
		वापस ret;
	वापस (val & MAX44000_CFG_RX_ALSPGA_MASK) >> MAX44000_CFG_RX_ALSPGA_SHIFT;
पूर्ण

अटल पूर्णांक max44000_ग_लिखो_alspga(काष्ठा max44000_data *data, पूर्णांक val)
अणु
	वापस regmap_ग_लिखो_bits(data->regmap, MAX44000_REG_CFG_RX,
				 MAX44000_CFG_RX_ALSPGA_MASK,
				 val << MAX44000_CFG_RX_ALSPGA_SHIFT);
पूर्ण

अटल पूर्णांक max44000_पढ़ो_alsval(काष्ठा max44000_data *data)
अणु
	u16 regval;
	__be16 val;
	पूर्णांक alstim, ret;

	ret = regmap_bulk_पढ़ो(data->regmap, MAX44000_REG_ALS_DATA_HI,
			       &val, माप(val));
	अगर (ret < 0)
		वापस ret;
	alstim = ret = max44000_पढ़ो_alstim(data);
	अगर (ret < 0)
		वापस ret;

	regval = be16_to_cpu(val);

	/*
	 * Overflow is explained on datasheet page 17.
	 *
	 * It's a warning that either the G or IR channel has become saturated
	 * and that the value in the रेजिस्टर is likely incorrect.
	 *
	 * The recommendation is to change the scale (ALSPGA).
	 * The driver just वापसs the max representable value.
	 */
	अगर (regval & MAX44000_ALSDATA_OVERFLOW)
		वापस 0x3FFF;

	वापस regval << MAX44000_ALSTIM_SHIFT(alstim);
पूर्ण

अटल पूर्णांक max44000_ग_लिखो_led_current_raw(काष्ठा max44000_data *data, पूर्णांक val)
अणु
	/* Maybe we should clamp the value instead? */
	अगर (val < 0 || val > MAX44000_LED_CURRENT_MAX)
		वापस -दुस्फल;
	अगर (val >= 8)
		val += 4;
	वापस regmap_ग_लिखो_bits(data->regmap, MAX44000_REG_CFG_TX,
				 MAX44000_LED_CURRENT_MASK, val);
पूर्ण

अटल पूर्णांक max44000_पढ़ो_led_current_raw(काष्ठा max44000_data *data)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	ret = regmap_पढ़ो(data->regmap, MAX44000_REG_CFG_TX, &regval);
	अगर (ret < 0)
		वापस ret;
	regval &= MAX44000_LED_CURRENT_MASK;
	अगर (regval >= 8)
		regval -= 4;
	वापस regval;
पूर्ण

अटल पूर्णांक max44000_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा max44000_data *data = iio_priv(indio_dev);
	पूर्णांक alstim, alspga;
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		चयन (chan->type) अणु
		हाल IIO_LIGHT:
			mutex_lock(&data->lock);
			ret = max44000_पढ़ो_alsval(data);
			mutex_unlock(&data->lock);
			अगर (ret < 0)
				वापस ret;
			*val = ret;
			वापस IIO_VAL_INT;

		हाल IIO_PROXIMITY:
			mutex_lock(&data->lock);
			ret = regmap_पढ़ो(data->regmap, MAX44000_REG_PRX_DATA, &regval);
			mutex_unlock(&data->lock);
			अगर (ret < 0)
				वापस ret;
			*val = regval;
			वापस IIO_VAL_INT;

		हाल IIO_CURRENT:
			mutex_lock(&data->lock);
			ret = max44000_पढ़ो_led_current_raw(data);
			mutex_unlock(&data->lock);
			अगर (ret < 0)
				वापस ret;
			*val = ret;
			वापस IIO_VAL_INT;

		शेष:
			वापस -EINVAL;
		पूर्ण

	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_CURRENT:
			/* Output रेजिस्टर is in 10s of miliamps */
			*val = 10;
			वापस IIO_VAL_INT;

		हाल IIO_LIGHT:
			mutex_lock(&data->lock);
			alspga = ret = max44000_पढ़ो_alspga(data);
			mutex_unlock(&data->lock);
			अगर (ret < 0)
				वापस ret;

			/* Aव्योम negative shअगरts */
			*val = (1 << MAX44000_ALSPGA_MAX_SHIFT);
			*val2 = MAX44000_ALS_TO_LUX_DEFAULT_FRACTION_LOG2
					+ MAX44000_ALSPGA_MAX_SHIFT
					- max44000_alspga_shअगरt[alspga];
			वापस IIO_VAL_FRACTIONAL_LOG2;

		शेष:
			वापस -EINVAL;
		पूर्ण

	हाल IIO_CHAN_INFO_INT_TIME:
		mutex_lock(&data->lock);
		alstim = ret = max44000_पढ़ो_alstim(data);
		mutex_unlock(&data->lock);

		अगर (ret < 0)
			वापस ret;
		*val = 0;
		*val2 = max44000_पूर्णांक_समय_avail_ns_array[alstim];
		वापस IIO_VAL_INT_PLUS_न_अंकO;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक max44000_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan,
			      पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा max44000_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	अगर (mask == IIO_CHAN_INFO_RAW && chan->type == IIO_CURRENT) अणु
		mutex_lock(&data->lock);
		ret = max44000_ग_लिखो_led_current_raw(data, val);
		mutex_unlock(&data->lock);
		वापस ret;
	पूर्ण अन्यथा अगर (mask == IIO_CHAN_INFO_INT_TIME && chan->type == IIO_LIGHT) अणु
		s64 valns = val * NSEC_PER_SEC + val2;
		पूर्णांक alstim = find_बंदst_descending(valns,
				max44000_पूर्णांक_समय_avail_ns_array,
				ARRAY_SIZE(max44000_पूर्णांक_समय_avail_ns_array));
		mutex_lock(&data->lock);
		ret = max44000_ग_लिखो_alstim(data, alstim);
		mutex_unlock(&data->lock);
		वापस ret;
	पूर्ण अन्यथा अगर (mask == IIO_CHAN_INFO_SCALE && chan->type == IIO_LIGHT) अणु
		s64 valus = val * USEC_PER_SEC + val2;
		पूर्णांक alspga = find_बंदst(valus,
				max44000_scale_avail_ulux_array,
				ARRAY_SIZE(max44000_scale_avail_ulux_array));
		mutex_lock(&data->lock);
		ret = max44000_ग_लिखो_alspga(data, alspga);
		mutex_unlock(&data->lock);
		वापस ret;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक max44000_ग_लिखो_raw_get_fmt(काष्ठा iio_dev *indio_dev,
				      काष्ठा iio_chan_spec स्थिर *chan,
				      दीर्घ mask)
अणु
	अगर (mask == IIO_CHAN_INFO_INT_TIME && chan->type == IIO_LIGHT)
		वापस IIO_VAL_INT_PLUS_न_अंकO;
	अन्यथा अगर (mask == IIO_CHAN_INFO_SCALE && chan->type == IIO_LIGHT)
		वापस IIO_VAL_INT_PLUS_MICRO;
	अन्यथा
		वापस IIO_VAL_INT;
पूर्ण

अटल IIO_CONST_ATTR(illuminance_पूर्णांकegration_समय_available, max44000_पूर्णांक_समय_avail_str);
अटल IIO_CONST_ATTR(illuminance_scale_available, max44000_scale_avail_str);

अटल काष्ठा attribute *max44000_attributes[] = अणु
	&iio_स्थिर_attr_illuminance_पूर्णांकegration_समय_available.dev_attr.attr,
	&iio_स्थिर_attr_illuminance_scale_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group max44000_attribute_group = अणु
	.attrs = max44000_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info max44000_info = अणु
	.पढ़ो_raw		= max44000_पढ़ो_raw,
	.ग_लिखो_raw		= max44000_ग_लिखो_raw,
	.ग_लिखो_raw_get_fmt	= max44000_ग_लिखो_raw_get_fmt,
	.attrs			= &max44000_attribute_group,
पूर्ण;

अटल bool max44000_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MAX44000_REG_STATUS:
	हाल MAX44000_REG_CFG_MAIN:
	हाल MAX44000_REG_CFG_RX:
	हाल MAX44000_REG_CFG_TX:
	हाल MAX44000_REG_ALS_DATA_HI:
	हाल MAX44000_REG_ALS_DATA_LO:
	हाल MAX44000_REG_PRX_DATA:
	हाल MAX44000_REG_ALS_UPTHR_HI:
	हाल MAX44000_REG_ALS_UPTHR_LO:
	हाल MAX44000_REG_ALS_LOTHR_HI:
	हाल MAX44000_REG_ALS_LOTHR_LO:
	हाल MAX44000_REG_PST:
	हाल MAX44000_REG_PRX_IND:
	हाल MAX44000_REG_PRX_THR:
	हाल MAX44000_REG_TRIM_GAIN_GREEN:
	हाल MAX44000_REG_TRIM_GAIN_IR:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool max44000_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MAX44000_REG_CFG_MAIN:
	हाल MAX44000_REG_CFG_RX:
	हाल MAX44000_REG_CFG_TX:
	हाल MAX44000_REG_ALS_UPTHR_HI:
	हाल MAX44000_REG_ALS_UPTHR_LO:
	हाल MAX44000_REG_ALS_LOTHR_HI:
	हाल MAX44000_REG_ALS_LOTHR_LO:
	हाल MAX44000_REG_PST:
	हाल MAX44000_REG_PRX_IND:
	हाल MAX44000_REG_PRX_THR:
	हाल MAX44000_REG_TRIM_GAIN_GREEN:
	हाल MAX44000_REG_TRIM_GAIN_IR:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool max44000_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MAX44000_REG_STATUS:
	हाल MAX44000_REG_ALS_DATA_HI:
	हाल MAX44000_REG_ALS_DATA_LO:
	हाल MAX44000_REG_PRX_DATA:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool max44000_precious_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस reg == MAX44000_REG_STATUS;
पूर्ण

अटल स्थिर काष्ठा regmap_config max44000_regmap_config = अणु
	.reg_bits		= 8,
	.val_bits		= 8,

	.max_रेजिस्टर		= MAX44000_REG_PRX_DATA,
	.पढ़ोable_reg		= max44000_पढ़ोable_reg,
	.ग_लिखोable_reg		= max44000_ग_लिखोable_reg,
	.अस्थिर_reg		= max44000_अस्थिर_reg,
	.precious_reg		= max44000_precious_reg,

	.use_single_पढ़ो	= true,
	.use_single_ग_लिखो	= true,
	.cache_type		= REGCACHE_RBTREE,
पूर्ण;

अटल irqवापस_t max44000_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा max44000_data *data = iio_priv(indio_dev);
	पूर्णांक index = 0;
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	mutex_lock(&data->lock);
	अगर (test_bit(MAX44000_SCAN_INDEX_ALS, indio_dev->active_scan_mask)) अणु
		ret = max44000_पढ़ो_alsval(data);
		अगर (ret < 0)
			जाओ out_unlock;
		data->scan.channels[index++] = ret;
	पूर्ण
	अगर (test_bit(MAX44000_SCAN_INDEX_PRX, indio_dev->active_scan_mask)) अणु
		ret = regmap_पढ़ो(data->regmap, MAX44000_REG_PRX_DATA, &regval);
		अगर (ret < 0)
			जाओ out_unlock;
		data->scan.channels[index] = regval;
	पूर्ण
	mutex_unlock(&data->lock);

	iio_push_to_buffers_with_बारtamp(indio_dev, &data->scan,
					   iio_get_समय_ns(indio_dev));
	iio_trigger_notअगरy_करोne(indio_dev->trig);
	वापस IRQ_HANDLED;

out_unlock:
	mutex_unlock(&data->lock);
	iio_trigger_notअगरy_करोne(indio_dev->trig);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक max44000_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा max44000_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret, reg;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;
	data = iio_priv(indio_dev);
	data->regmap = devm_regmap_init_i2c(client, &max44000_regmap_config);
	अगर (IS_ERR(data->regmap)) अणु
		dev_err(&client->dev, "regmap_init failed!\n");
		वापस PTR_ERR(data->regmap);
	पूर्ण

	i2c_set_clientdata(client, indio_dev);
	mutex_init(&data->lock);
	indio_dev->info = &max44000_info;
	indio_dev->name = MAX44000_DRV_NAME;
	indio_dev->channels = max44000_channels;
	indio_dev->num_channels = ARRAY_SIZE(max44000_channels);

	/*
	 * The device करोesn't have a reset function so we just clear some
	 * important bits at probe समय to ensure sane operation.
	 *
	 * Since we करोn't support पूर्णांकerrupts/events the threshold values are
	 * not important. We also करोn't touch trim values.
	 */

	/* Reset ALS scaling bits */
	ret = regmap_ग_लिखो(data->regmap, MAX44000_REG_CFG_RX,
			   MAX44000_REG_CFG_RX_DEFAULT);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed to write default CFG_RX: %d\n",
			ret);
		वापस ret;
	पूर्ण

	/*
	 * By शेष the LED pulse used क्रम the proximity sensor is disabled.
	 * Set a middle value so that we get some sort of valid data by शेष.
	 */
	ret = max44000_ग_लिखो_led_current_raw(data, MAX44000_LED_CURRENT_DEFAULT);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed to write init config: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Reset CFG bits to ALS_PRX mode which allows easy पढ़ोing of both values. */
	reg = MAX44000_CFG_TRIM | MAX44000_CFG_MODE_ALS_PRX;
	ret = regmap_ग_लिखो(data->regmap, MAX44000_REG_CFG_MAIN, reg);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed to write init config: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Read status at least once to clear any stale पूर्णांकerrupt bits. */
	ret = regmap_पढ़ो(data->regmap, MAX44000_REG_STATUS, &reg);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed to read init status: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = iio_triggered_buffer_setup(indio_dev, शून्य, max44000_trigger_handler, शून्य);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "iio triggered buffer setup failed\n");
		वापस ret;
	पूर्ण

	वापस iio_device_रेजिस्टर(indio_dev);
पूर्ण

अटल पूर्णांक max44000_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);

	iio_device_unरेजिस्टर(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max44000_id[] = अणु
	अणु"max44000", 0पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max44000_id);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id max44000_acpi_match[] = अणु
	अणु"MAX44000", 0पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, max44000_acpi_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver max44000_driver = अणु
	.driver = अणु
		.name	= MAX44000_DRV_NAME,
		.acpi_match_table = ACPI_PTR(max44000_acpi_match),
	पूर्ण,
	.probe		= max44000_probe,
	.हटाओ		= max44000_हटाओ,
	.id_table	= max44000_id,
पूर्ण;

module_i2c_driver(max44000_driver);

MODULE_AUTHOR("Crestez Dan Leonard <leonard.crestez@intel.com>");
MODULE_DESCRIPTION("MAX44000 Ambient and Infrared Proximity Sensor");
MODULE_LICENSE("GPL v2");
