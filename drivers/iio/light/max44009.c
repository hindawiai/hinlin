<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * max44009.c - Support क्रम MAX44009 Ambient Light Sensor
 *
 * Copyright (c) 2019 Robert Eshleman <bobbyeshleman@gmail.com>
 *
 * Datasheet: https://datasheets.maximपूर्णांकegrated.com/en/ds/MAX44009.pdf
 *
 * TODO: Support continuous mode and configuring from manual mode to
 *	 स्वतःmatic mode.
 *
 * Default I2C address: 0x4a
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/bits.h>
#समावेश <linux/i2c.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/util_macros.h>

#घोषणा MAX44009_DRV_NAME "max44009"

/* Registers in datasheet order */
#घोषणा MAX44009_REG_INT_STATUS 0x0
#घोषणा MAX44009_REG_INT_EN 0x1
#घोषणा MAX44009_REG_CFG 0x2
#घोषणा MAX44009_REG_LUX_HI 0x3
#घोषणा MAX44009_REG_LUX_LO 0x4
#घोषणा MAX44009_REG_UPPER_THR 0x5
#घोषणा MAX44009_REG_LOWER_THR 0x6
#घोषणा MAX44009_REG_THR_TIMER 0x7

#घोषणा MAX44009_CFG_TIM_MASK GENMASK(2, 0)
#घोषणा MAX44009_CFG_MAN_MODE_MASK BIT(6)

/* The maximum rising threshold क्रम the max44009 */
#घोषणा MAX44009_MAXIMUM_THRESHOLD 7520256

#घोषणा MAX44009_THRESH_EXP_MASK (0xf << 4)
#घोषणा MAX44009_THRESH_EXP_RSHIFT 4
#घोषणा MAX44009_THRESH_MANT_LSHIFT 4
#घोषणा MAX44009_THRESH_MANT_MASK 0xf

#घोषणा MAX44009_UPPER_THR_MINIMUM 15

/* The max44009 always scales raw पढ़ोings by 0.045 and is non-configurable */
#घोषणा MAX44009_SCALE_NUMERATOR 45
#घोषणा MAX44009_SCALE_DENOMINATOR 1000

/* The fixed-poपूर्णांक fractional multiplier क्रम de-scaling threshold values */
#घोषणा MAX44009_FRACT_MULT 1000000

अटल स्थिर u32 max44009_पूर्णांक_समय_ns_array[] = अणु
	800000000,
	400000000,
	200000000,
	100000000,
	50000000, /* Manual mode only */
	25000000, /* Manual mode only */
	12500000, /* Manual mode only */
	6250000,  /* Manual mode only */
पूर्ण;

अटल स्थिर अक्षर max44009_पूर्णांक_समय_str[] =
	"0.8 "
	"0.4 "
	"0.2 "
	"0.1 "
	"0.05 "
	"0.025 "
	"0.0125 "
	"0.00625";

काष्ठा max44009_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;
पूर्ण;

अटल स्थिर काष्ठा iio_event_spec max44009_event_spec[] = अणु
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_RISING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE) |
				 BIT(IIO_EV_INFO_ENABLE),
	पूर्ण,
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_FALLING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE) |
				 BIT(IIO_EV_INFO_ENABLE),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec max44009_channels[] = अणु
	अणु
		.type = IIO_LIGHT,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED) |
				      BIT(IIO_CHAN_INFO_INT_TIME),
		.event_spec = max44009_event_spec,
		.num_event_specs = ARRAY_SIZE(max44009_event_spec),
	पूर्ण,
पूर्ण;

अटल पूर्णांक max44009_पढ़ो_पूर्णांक_समय(काष्ठा max44009_data *data)
अणु

	पूर्णांक ret = i2c_smbus_पढ़ो_byte_data(data->client, MAX44009_REG_CFG);

	अगर (ret < 0)
		वापस ret;

	वापस max44009_पूर्णांक_समय_ns_array[ret & MAX44009_CFG_TIM_MASK];
पूर्ण

अटल पूर्णांक max44009_ग_लिखो_पूर्णांक_समय(काष्ठा max44009_data *data,
				   पूर्णांक val, पूर्णांक val2)
अणु
	काष्ठा i2c_client *client = data->client;
	पूर्णांक ret, पूर्णांक_समय, config;
	s64 ns;

	ns = val * NSEC_PER_SEC + val2;
	पूर्णांक_समय = find_बंदst_descending(
			ns,
			max44009_पूर्णांक_समय_ns_array,
			ARRAY_SIZE(max44009_पूर्णांक_समय_ns_array));

	ret = i2c_smbus_पढ़ो_byte_data(client, MAX44009_REG_CFG);
	अगर (ret < 0)
		वापस ret;

	config = ret;
	config &= पूर्णांक_समय;

	/*
	 * To set the पूर्णांकegration समय, the device must also be in manual
	 * mode.
	 */
	config |= MAX44009_CFG_MAN_MODE_MASK;

	वापस i2c_smbus_ग_लिखो_byte_data(client, MAX44009_REG_CFG, config);
पूर्ण

अटल पूर्णांक max44009_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val,
			      पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा max44009_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	अगर (mask == IIO_CHAN_INFO_INT_TIME && chan->type == IIO_LIGHT) अणु
		mutex_lock(&data->lock);
		ret = max44009_ग_लिखो_पूर्णांक_समय(data, val, val2);
		mutex_unlock(&data->lock);
		वापस ret;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक max44009_ग_लिखो_raw_get_fmt(काष्ठा iio_dev *indio_dev,
				      काष्ठा iio_chan_spec स्थिर *chan,
				      दीर्घ mask)
अणु
	वापस IIO_VAL_INT_PLUS_न_अंकO;
पूर्ण

अटल पूर्णांक max44009_lux_raw(u8 hi, u8 lo)
अणु
	पूर्णांक mantissa;
	पूर्णांक exponent;

	/*
	 * The mantissa consists of the low nibble of the Lux High Byte
	 * and the low nibble of the Lux Low Byte.
	 */
	mantissa = ((hi & 0xf) << 4) | (lo & 0xf);

	/* The exponent byte is just the upper nibble of the Lux High Byte */
	exponent = (hi >> 4) & 0xf;

	/*
	 * The exponent value is base 2 to the घातer of the raw exponent byte.
	 */
	exponent = 1 << exponent;

	वापस exponent * mantissa;
पूर्ण

#घोषणा MAX44009_READ_LUX_XFER_LEN (4)

अटल पूर्णांक max44009_पढ़ो_lux_raw(काष्ठा max44009_data *data)
अणु
	पूर्णांक ret;
	u8 hireg = MAX44009_REG_LUX_HI;
	u8 loreg = MAX44009_REG_LUX_LO;
	u8 lo = 0;
	u8 hi = 0;

	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr = data->client->addr,
			.flags = 0,
			.len = माप(hireg),
			.buf = &hireg,
		पूर्ण,
		अणु
			.addr = data->client->addr,
			.flags = I2C_M_RD,
			.len = माप(hi),
			.buf = &hi,
		पूर्ण,
		अणु
			.addr = data->client->addr,
			.flags = 0,
			.len = माप(loreg),
			.buf = &loreg,
		पूर्ण,
		अणु
			.addr = data->client->addr,
			.flags = I2C_M_RD,
			.len = माप(lo),
			.buf = &lo,
		पूर्ण
	पूर्ण;

	/*
	 * Use i2c_transfer instead of smbus पढ़ो because i2c_transfer
	 * करोes NOT use a stop bit between address ग_लिखो and data पढ़ो.
	 * Using a stop bit causes disjoपूर्णांक upper/lower byte पढ़ोs and
	 * reduces accuracy.
	 */
	ret = i2c_transfer(data->client->adapter,
			   msgs, MAX44009_READ_LUX_XFER_LEN);

	अगर (ret != MAX44009_READ_LUX_XFER_LEN)
		वापस -EIO;

	वापस max44009_lux_raw(hi, lo);
पूर्ण

अटल पूर्णांक max44009_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
			     पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा max44009_data *data = iio_priv(indio_dev);
	पूर्णांक lux_raw;
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_PROCESSED:
		चयन (chan->type) अणु
		हाल IIO_LIGHT:
			ret = max44009_पढ़ो_lux_raw(data);
			अगर (ret < 0)
				वापस ret;
			lux_raw = ret;

			*val = lux_raw * MAX44009_SCALE_NUMERATOR;
			*val2 = MAX44009_SCALE_DENOMINATOR;
			वापस IIO_VAL_FRACTIONAL;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_INT_TIME:
		चयन (chan->type) अणु
		हाल IIO_LIGHT:
			ret = max44009_पढ़ो_पूर्णांक_समय(data);
			अगर (ret < 0)
				वापस ret;

			*val2 = ret;
			*val = 0;
			वापस IIO_VAL_INT_PLUS_न_अंकO;
		शेष:
			वापस -EINVAL;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल IIO_CONST_ATTR(illuminance_पूर्णांकegration_समय_available,
		      max44009_पूर्णांक_समय_str);

अटल काष्ठा attribute *max44009_attributes[] = अणु
	&iio_स्थिर_attr_illuminance_पूर्णांकegration_समय_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group max44009_attribute_group = अणु
	.attrs = max44009_attributes,
पूर्ण;

अटल पूर्णांक max44009_threshold_byte_from_fraction(पूर्णांक पूर्णांकegral, पूर्णांक fractional)
अणु
	पूर्णांक mantissa, exp;

	अगर ((पूर्णांकegral <= 0 && fractional <= 0) ||
	     पूर्णांकegral > MAX44009_MAXIMUM_THRESHOLD ||
	     (पूर्णांकegral == MAX44009_MAXIMUM_THRESHOLD && fractional != 0))
		वापस -EINVAL;

	/* Reverse scaling of fixed-poपूर्णांक पूर्णांकegral */
	mantissa = पूर्णांकegral * MAX44009_SCALE_DENOMINATOR;
	mantissa /= MAX44009_SCALE_NUMERATOR;

	/* Reverse scaling of fixed-poपूर्णांक fractional */
	mantissa += fractional / MAX44009_FRACT_MULT *
		    (MAX44009_SCALE_DENOMINATOR / MAX44009_SCALE_NUMERATOR);

	क्रम (exp = 0; mantissa > 0xff; exp++)
		mantissa >>= 1;

	mantissa >>= 4;
	mantissa &= 0xf;
	exp <<= 4;

	वापस exp | mantissa;
पूर्ण

अटल पूर्णांक max44009_get_thr_reg(क्रमागत iio_event_direction dir)
अणु
	चयन (dir) अणु
	हाल IIO_EV_सूची_RISING:
		वापस MAX44009_REG_UPPER_THR;
	हाल IIO_EV_सूची_FALLING:
		वापस MAX44009_REG_LOWER_THR;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक max44009_ग_लिखो_event_value(काष्ठा iio_dev *indio_dev,
				      स्थिर काष्ठा iio_chan_spec *chan,
				      क्रमागत iio_event_type type,
				      क्रमागत iio_event_direction dir,
				      क्रमागत iio_event_info info,
				      पूर्णांक val, पूर्णांक val2)
अणु
	काष्ठा max44009_data *data = iio_priv(indio_dev);
	पूर्णांक reg, threshold;

	अगर (info != IIO_EV_INFO_VALUE || chan->type != IIO_LIGHT)
		वापस -EINVAL;

	threshold = max44009_threshold_byte_from_fraction(val, val2);
	अगर (threshold < 0)
		वापस threshold;

	reg = max44009_get_thr_reg(dir);
	अगर (reg < 0)
		वापस reg;

	वापस i2c_smbus_ग_लिखो_byte_data(data->client, reg, threshold);
पूर्ण

अटल पूर्णांक max44009_पढ़ो_threshold(काष्ठा iio_dev *indio_dev,
				   क्रमागत iio_event_direction dir)
अणु
	काष्ठा max44009_data *data = iio_priv(indio_dev);
	पूर्णांक byte, reg;
	पूर्णांक mantissa, exponent;

	reg = max44009_get_thr_reg(dir);
	अगर (reg < 0)
		वापस reg;

	byte = i2c_smbus_पढ़ो_byte_data(data->client, reg);
	अगर (byte < 0)
		वापस byte;

	mantissa = byte & MAX44009_THRESH_MANT_MASK;
	mantissa <<= MAX44009_THRESH_MANT_LSHIFT;

	/*
	 * To get the upper threshold, always adds the minimum upper threshold
	 * value to the shअगरted byte value (see datasheet).
	 */
	अगर (dir == IIO_EV_सूची_RISING)
		mantissa += MAX44009_UPPER_THR_MINIMUM;

	/*
	 * Exponent is base 2 to the घातer of the threshold exponent byte
	 * value
	 */
	exponent = byte & MAX44009_THRESH_EXP_MASK;
	exponent >>= MAX44009_THRESH_EXP_RSHIFT;

	वापस (1 << exponent) * mantissa;
पूर्ण

अटल पूर्णांक max44009_पढ़ो_event_value(काष्ठा iio_dev *indio_dev,
				     स्थिर काष्ठा iio_chan_spec *chan,
				     क्रमागत iio_event_type type,
				     क्रमागत iio_event_direction dir,
				     क्रमागत iio_event_info info,
				     पूर्णांक *val, पूर्णांक *val2)
अणु
	पूर्णांक ret;
	पूर्णांक threshold;

	अगर (chan->type != IIO_LIGHT || type != IIO_EV_TYPE_THRESH)
		वापस -EINVAL;

	ret = max44009_पढ़ो_threshold(indio_dev, dir);
	अगर (ret < 0)
		वापस ret;
	threshold = ret;

	*val = threshold * MAX44009_SCALE_NUMERATOR;
	*val2 = MAX44009_SCALE_DENOMINATOR;

	वापस IIO_VAL_FRACTIONAL;
पूर्ण

अटल पूर्णांक max44009_ग_लिखो_event_config(काष्ठा iio_dev *indio_dev,
				       स्थिर काष्ठा iio_chan_spec *chan,
				       क्रमागत iio_event_type type,
				       क्रमागत iio_event_direction dir,
				       पूर्णांक state)
अणु
	काष्ठा max44009_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	अगर (chan->type != IIO_LIGHT || type != IIO_EV_TYPE_THRESH)
		वापस -EINVAL;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client,
					MAX44009_REG_INT_EN, state);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Set device to trigger पूर्णांकerrupt immediately upon exceeding
	 * the threshold limit.
	 */
	वापस i2c_smbus_ग_लिखो_byte_data(data->client,
					 MAX44009_REG_THR_TIMER, 0);
पूर्ण

अटल पूर्णांक max44009_पढ़ो_event_config(काष्ठा iio_dev *indio_dev,
				      स्थिर काष्ठा iio_chan_spec *chan,
				      क्रमागत iio_event_type type,
				      क्रमागत iio_event_direction dir)
अणु
	काष्ठा max44009_data *data = iio_priv(indio_dev);

	अगर (chan->type != IIO_LIGHT || type != IIO_EV_TYPE_THRESH)
		वापस -EINVAL;

	वापस i2c_smbus_पढ़ो_byte_data(data->client, MAX44009_REG_INT_EN);
पूर्ण

अटल स्थिर काष्ठा iio_info max44009_info = अणु
	.पढ़ो_raw = max44009_पढ़ो_raw,
	.ग_लिखो_raw = max44009_ग_लिखो_raw,
	.ग_लिखो_raw_get_fmt = max44009_ग_लिखो_raw_get_fmt,
	.पढ़ो_event_value = max44009_पढ़ो_event_value,
	.पढ़ो_event_config = max44009_पढ़ो_event_config,
	.ग_लिखो_event_value = max44009_ग_लिखो_event_value,
	.ग_लिखो_event_config = max44009_ग_लिखो_event_config,
	.attrs = &max44009_attribute_group,
पूर्ण;

अटल irqवापस_t max44009_thपढ़ोed_irq_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_dev *indio_dev = p;
	काष्ठा max44009_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, MAX44009_REG_INT_STATUS);
	अगर (ret) अणु
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_LIGHT, 0,
						    IIO_EV_TYPE_THRESH,
						    IIO_EV_सूची_EITHER),
			       iio_get_समय_ns(indio_dev));

		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक max44009_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा max44009_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	indio_dev->info = &max44009_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->name = MAX44009_DRV_NAME;
	indio_dev->channels = max44009_channels;
	indio_dev->num_channels = ARRAY_SIZE(max44009_channels);
	mutex_init(&data->lock);

	/* Clear any stale पूर्णांकerrupt bit */
	ret = i2c_smbus_पढ़ो_byte_data(client, MAX44009_REG_CFG);
	अगर (ret < 0)
		वापस ret;

	अगर (client->irq > 0) अणु
		ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
						शून्य,
						max44009_thपढ़ोed_irq_handler,
						IRQF_TRIGGER_FALLING |
						IRQF_ONESHOT | IRQF_SHARED,
						"max44009_event",
						indio_dev);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max44009_id[] = अणु
	अणु "max44009", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max44009_id);

अटल काष्ठा i2c_driver max44009_driver = अणु
	.driver = अणु
		.name = MAX44009_DRV_NAME,
	पूर्ण,
	.probe = max44009_probe,
	.id_table = max44009_id,
पूर्ण;
module_i2c_driver(max44009_driver);

अटल स्थिर काष्ठा of_device_id max44009_of_match[] = अणु
	अणु .compatible = "maxim,max44009" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max44009_of_match);

MODULE_AUTHOR("Robert Eshleman <bobbyeshleman@gmail.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("MAX44009 ambient light sensor driver");
