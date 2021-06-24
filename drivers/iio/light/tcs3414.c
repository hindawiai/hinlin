<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tcs3414.c - Support क्रम TAOS TCS3414 digital color sensor
 *
 * Copyright (c) 2014 Peter Meerwald <pmeerw@pmeerw.net>
 *
 * Digital color sensor with 16-bit channels क्रम red, green, blue, clear);
 * 7-bit I2C slave address 0x39 (TCS3414) or 0x29, 0x49, 0x59 (TCS3413,
 * TCS3415, TCS3416, resp.)
 *
 * TODO: sync, पूर्णांकerrupt support, thresholds, prescaler
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/triggered_buffer.h>

#घोषणा TCS3414_DRV_NAME "tcs3414"

#घोषणा TCS3414_COMMAND BIT(7)
#घोषणा TCS3414_COMMAND_WORD (TCS3414_COMMAND | BIT(5))

#घोषणा TCS3414_CONTROL (TCS3414_COMMAND | 0x00)
#घोषणा TCS3414_TIMING (TCS3414_COMMAND | 0x01)
#घोषणा TCS3414_ID (TCS3414_COMMAND | 0x04)
#घोषणा TCS3414_GAIN (TCS3414_COMMAND | 0x07)
#घोषणा TCS3414_DATA_GREEN (TCS3414_COMMAND_WORD | 0x10)
#घोषणा TCS3414_DATA_RED (TCS3414_COMMAND_WORD | 0x12)
#घोषणा TCS3414_DATA_BLUE (TCS3414_COMMAND_WORD | 0x14)
#घोषणा TCS3414_DATA_CLEAR (TCS3414_COMMAND_WORD | 0x16)

#घोषणा TCS3414_CONTROL_ADC_VALID BIT(4)
#घोषणा TCS3414_CONTROL_ADC_EN BIT(1)
#घोषणा TCS3414_CONTROL_POWER BIT(0)

#घोषणा TCS3414_INTEG_MASK GENMASK(1, 0)
#घोषणा TCS3414_INTEG_12MS 0x0
#घोषणा TCS3414_INTEG_100MS 0x1
#घोषणा TCS3414_INTEG_400MS 0x2

#घोषणा TCS3414_GAIN_MASK GENMASK(5, 4)
#घोषणा TCS3414_GAIN_SHIFT 4

काष्ठा tcs3414_data अणु
	काष्ठा i2c_client *client;
	u8 control;
	u8 gain;
	u8 timing;
	u16 buffer[8]; /* 4x 16-bit + 8 bytes बारtamp */
पूर्ण;

#घोषणा TCS3414_CHANNEL(_color, _si, _addr) अणु \
	.type = IIO_INTENSITY, \
	.modअगरied = 1, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW), \
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) | \
		BIT(IIO_CHAN_INFO_INT_TIME), \
	.channel2 = IIO_MOD_LIGHT_##_color, \
	.address = _addr, \
	.scan_index = _si, \
	.scan_type = अणु \
		.sign = 'u', \
		.realbits = 16, \
		.storagebits = 16, \
		.endianness = IIO_CPU, \
	पूर्ण, \
पूर्ण

/* scale factors: 1/gain */
अटल स्थिर पूर्णांक tcs3414_scales[][2] = अणु
	अणु1, 0पूर्ण, अणु0, 250000पूर्ण, अणु0, 62500पूर्ण, अणु0, 15625पूर्ण
पूर्ण;

/* पूर्णांकegration समय in ms */
अटल स्थिर पूर्णांक tcs3414_बार[] = अणु 12, 100, 400 पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec tcs3414_channels[] = अणु
	TCS3414_CHANNEL(GREEN, 0, TCS3414_DATA_GREEN),
	TCS3414_CHANNEL(RED, 1, TCS3414_DATA_RED),
	TCS3414_CHANNEL(BLUE, 2, TCS3414_DATA_BLUE),
	TCS3414_CHANNEL(CLEAR, 3, TCS3414_DATA_CLEAR),
	IIO_CHAN_SOFT_TIMESTAMP(4),
पूर्ण;

अटल पूर्णांक tcs3414_req_data(काष्ठा tcs3414_data *data)
अणु
	पूर्णांक tries = 25;
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, TCS3414_CONTROL,
		data->control | TCS3414_CONTROL_ADC_EN);
	अगर (ret < 0)
		वापस ret;

	जबतक (tries--) अणु
		ret = i2c_smbus_पढ़ो_byte_data(data->client, TCS3414_CONTROL);
		अगर (ret < 0)
			वापस ret;
		अगर (ret & TCS3414_CONTROL_ADC_VALID)
			अवरोध;
		msleep(20);
	पूर्ण

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, TCS3414_CONTROL,
		data->control);
	अगर (ret < 0)
		वापस ret;

	अगर (tries < 0) अणु
		dev_err(&data->client->dev, "data not ready\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tcs3414_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा tcs3414_data *data = iio_priv(indio_dev);
	पूर्णांक i, ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;
		ret = tcs3414_req_data(data);
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
	हाल IIO_CHAN_INFO_SCALE:
		i = (data->gain & TCS3414_GAIN_MASK) >> TCS3414_GAIN_SHIFT;
		*val = tcs3414_scales[i][0];
		*val2 = tcs3414_scales[i][1];
		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_INT_TIME:
		*val = 0;
		*val2 = tcs3414_बार[data->timing & TCS3414_INTEG_MASK] * 1000;
		वापस IIO_VAL_INT_PLUS_MICRO;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक tcs3414_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा tcs3414_data *data = iio_priv(indio_dev);
	पूर्णांक i;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		क्रम (i = 0; i < ARRAY_SIZE(tcs3414_scales); i++) अणु
			अगर (val == tcs3414_scales[i][0] &&
				val2 == tcs3414_scales[i][1]) अणु
				data->gain &= ~TCS3414_GAIN_MASK;
				data->gain |= i << TCS3414_GAIN_SHIFT;
				वापस i2c_smbus_ग_लिखो_byte_data(
					data->client, TCS3414_GAIN,
					data->gain);
			पूर्ण
		पूर्ण
		वापस -EINVAL;
	हाल IIO_CHAN_INFO_INT_TIME:
		अगर (val != 0)
			वापस -EINVAL;
		क्रम (i = 0; i < ARRAY_SIZE(tcs3414_बार); i++) अणु
			अगर (val2 == tcs3414_बार[i] * 1000) अणु
				data->timing &= ~TCS3414_INTEG_MASK;
				data->timing |= i;
				वापस i2c_smbus_ग_लिखो_byte_data(
					data->client, TCS3414_TIMING,
					data->timing);
			पूर्ण
		पूर्ण
		वापस -EINVAL;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल irqवापस_t tcs3414_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा tcs3414_data *data = iio_priv(indio_dev);
	पूर्णांक i, j = 0;

	क्रम_each_set_bit(i, indio_dev->active_scan_mask,
		indio_dev->masklength) अणु
		पूर्णांक ret = i2c_smbus_पढ़ो_word_data(data->client,
			TCS3414_DATA_GREEN + 2*i);
		अगर (ret < 0)
			जाओ करोne;

		data->buffer[j++] = ret;
	पूर्ण

	iio_push_to_buffers_with_बारtamp(indio_dev, data->buffer,
		iio_get_समय_ns(indio_dev));

करोne:
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल IIO_CONST_ATTR(scale_available, "1 0.25 0.0625 0.015625");
अटल IIO_CONST_ATTR_INT_TIME_AVAIL("0.012 0.1 0.4");

अटल काष्ठा attribute *tcs3414_attributes[] = अणु
	&iio_स्थिर_attr_scale_available.dev_attr.attr,
	&iio_स्थिर_attr_पूर्णांकegration_समय_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group tcs3414_attribute_group = अणु
	.attrs = tcs3414_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info tcs3414_info = अणु
	.पढ़ो_raw = tcs3414_पढ़ो_raw,
	.ग_लिखो_raw = tcs3414_ग_लिखो_raw,
	.attrs = &tcs3414_attribute_group,
पूर्ण;

अटल पूर्णांक tcs3414_buffer_postenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा tcs3414_data *data = iio_priv(indio_dev);

	data->control |= TCS3414_CONTROL_ADC_EN;
	वापस i2c_smbus_ग_लिखो_byte_data(data->client, TCS3414_CONTROL,
		data->control);
पूर्ण

अटल पूर्णांक tcs3414_buffer_predisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा tcs3414_data *data = iio_priv(indio_dev);

	data->control &= ~TCS3414_CONTROL_ADC_EN;
	वापस i2c_smbus_ग_लिखो_byte_data(data->client, TCS3414_CONTROL,
		data->control);
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops tcs3414_buffer_setup_ops = अणु
	.postenable = tcs3414_buffer_postenable,
	.predisable = tcs3414_buffer_predisable,
पूर्ण;

अटल पूर्णांक tcs3414_probe(काष्ठा i2c_client *client,
			   स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tcs3414_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (indio_dev == शून्य)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;

	indio_dev->info = &tcs3414_info;
	indio_dev->name = TCS3414_DRV_NAME;
	indio_dev->channels = tcs3414_channels;
	indio_dev->num_channels = ARRAY_SIZE(tcs3414_channels);
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, TCS3414_ID);
	अगर (ret < 0)
		वापस ret;

	चयन (ret & 0xf0) अणु
	हाल 0x00:
		dev_info(&client->dev, "TCS3404 found\n");
		अवरोध;
	हाल 0x10:
		dev_info(&client->dev, "TCS3413/14/15/16 found\n");
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	data->control = TCS3414_CONTROL_POWER;
	ret = i2c_smbus_ग_लिखो_byte_data(data->client, TCS3414_CONTROL,
		data->control);
	अगर (ret < 0)
		वापस ret;

	data->timing = TCS3414_INTEG_12MS; /* मुक्त running */
	ret = i2c_smbus_ग_लिखो_byte_data(data->client, TCS3414_TIMING,
		data->timing);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, TCS3414_GAIN);
	अगर (ret < 0)
		वापस ret;
	data->gain = ret;

	ret = iio_triggered_buffer_setup(indio_dev, शून्य,
		tcs3414_trigger_handler, &tcs3414_buffer_setup_ops);
	अगर (ret < 0)
		वापस ret;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0)
		जाओ buffer_cleanup;

	वापस 0;

buffer_cleanup:
	iio_triggered_buffer_cleanup(indio_dev);
	वापस ret;
पूर्ण

अटल पूर्णांक tcs3414_घातerकरोwn(काष्ठा tcs3414_data *data)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(data->client, TCS3414_CONTROL,
		data->control & ~(TCS3414_CONTROL_POWER |
		TCS3414_CONTROL_ADC_EN));
पूर्ण

अटल पूर्णांक tcs3414_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);

	iio_device_unरेजिस्टर(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);
	tcs3414_घातerकरोwn(iio_priv(indio_dev));

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक tcs3414_suspend(काष्ठा device *dev)
अणु
	काष्ठा tcs3414_data *data = iio_priv(i2c_get_clientdata(
		to_i2c_client(dev)));
	वापस tcs3414_घातerकरोwn(data);
पूर्ण

अटल पूर्णांक tcs3414_resume(काष्ठा device *dev)
अणु
	काष्ठा tcs3414_data *data = iio_priv(i2c_get_clientdata(
		to_i2c_client(dev)));
	वापस i2c_smbus_ग_लिखो_byte_data(data->client, TCS3414_CONTROL,
		data->control);
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(tcs3414_pm_ops, tcs3414_suspend, tcs3414_resume);

अटल स्थिर काष्ठा i2c_device_id tcs3414_id[] = अणु
	अणु "tcs3414", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tcs3414_id);

अटल काष्ठा i2c_driver tcs3414_driver = अणु
	.driver = अणु
		.name	= TCS3414_DRV_NAME,
		.pm	= &tcs3414_pm_ops,
	पूर्ण,
	.probe		= tcs3414_probe,
	.हटाओ		= tcs3414_हटाओ,
	.id_table	= tcs3414_id,
पूर्ण;
module_i2c_driver(tcs3414_driver);

MODULE_AUTHOR("Peter Meerwald <pmeerw@pmeerw.net>");
MODULE_DESCRIPTION("TCS3414 digital color sensors driver");
MODULE_LICENSE("GPL");
