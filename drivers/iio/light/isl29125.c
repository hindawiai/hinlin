<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * isl29125.c - Support क्रम Intersil ISL29125 RGB light sensor
 *
 * Copyright (c) 2014 Peter Meerwald <pmeerw@pmeerw.net>
 *
 * RGB light sensor with 16-bit channels क्रम red, green, blue);
 * 7-bit I2C slave address 0x44
 *
 * TODO: पूर्णांकerrupt support, IR compensation, thresholds, 12bit
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

#घोषणा ISL29125_DRV_NAME "isl29125"

#घोषणा ISL29125_DEVICE_ID 0x00
#घोषणा ISL29125_CONF1 0x01
#घोषणा ISL29125_CONF2 0x02
#घोषणा ISL29125_CONF3 0x03
#घोषणा ISL29125_STATUS 0x08
#घोषणा ISL29125_GREEN_DATA 0x09
#घोषणा ISL29125_RED_DATA 0x0b
#घोषणा ISL29125_BLUE_DATA 0x0d

#घोषणा ISL29125_ID 0x7d

#घोषणा ISL29125_MODE_MASK GENMASK(2, 0)
#घोषणा ISL29125_MODE_PD 0x0
#घोषणा ISL29125_MODE_G 0x1
#घोषणा ISL29125_MODE_R 0x2
#घोषणा ISL29125_MODE_B 0x3
#घोषणा ISL29125_MODE_RGB 0x5

#घोषणा ISL29125_SENSING_RANGE_0 5722   /* 375 lux full range */
#घोषणा ISL29125_SENSING_RANGE_1 152590 /* 10k lux full range */

#घोषणा ISL29125_MODE_RANGE BIT(3)

#घोषणा ISL29125_STATUS_CONV BIT(1)

काष्ठा isl29125_data अणु
	काष्ठा i2c_client *client;
	u8 conf1;
	u16 buffer[8]; /* 3x 16-bit, padding, 8 bytes बारtamp */
पूर्ण;

#घोषणा ISL29125_CHANNEL(_color, _si) अणु \
	.type = IIO_INTENSITY, \
	.modअगरied = 1, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW), \
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE), \
	.channel2 = IIO_MOD_LIGHT_##_color, \
	.scan_index = _si, \
	.scan_type = अणु \
		.sign = 'u', \
		.realbits = 16, \
		.storagebits = 16, \
		.endianness = IIO_CPU, \
	पूर्ण, \
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec isl29125_channels[] = अणु
	ISL29125_CHANNEL(GREEN, 0),
	ISL29125_CHANNEL(RED, 1),
	ISL29125_CHANNEL(BLUE, 2),
	IIO_CHAN_SOFT_TIMESTAMP(3),
पूर्ण;

अटल स्थिर काष्ठा अणु
	u8 mode, data;
पूर्ण isl29125_regs[] = अणु
	अणुISL29125_MODE_G, ISL29125_GREEN_DATAपूर्ण,
	अणुISL29125_MODE_R, ISL29125_RED_DATAपूर्ण,
	अणुISL29125_MODE_B, ISL29125_BLUE_DATAपूर्ण,
पूर्ण;

अटल पूर्णांक isl29125_पढ़ो_data(काष्ठा isl29125_data *data, पूर्णांक si)
अणु
	पूर्णांक tries = 5;
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, ISL29125_CONF1,
		data->conf1 | isl29125_regs[si].mode);
	अगर (ret < 0)
		वापस ret;

	msleep(101);

	जबतक (tries--) अणु
		ret = i2c_smbus_पढ़ो_byte_data(data->client, ISL29125_STATUS);
		अगर (ret < 0)
			जाओ fail;
		अगर (ret & ISL29125_STATUS_CONV)
			अवरोध;
		msleep(20);
	पूर्ण

	अगर (tries < 0) अणु
		dev_err(&data->client->dev, "data not ready\n");
		ret = -EIO;
		जाओ fail;
	पूर्ण

	ret = i2c_smbus_पढ़ो_word_data(data->client, isl29125_regs[si].data);

fail:
	i2c_smbus_ग_लिखो_byte_data(data->client, ISL29125_CONF1, data->conf1);
	वापस ret;
पूर्ण

अटल पूर्णांक isl29125_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा isl29125_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;
		ret = isl29125_पढ़ो_data(data, chan->scan_index);
		iio_device_release_direct_mode(indio_dev);
		अगर (ret < 0)
			वापस ret;
		*val = ret;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = 0;
		अगर (data->conf1 & ISL29125_MODE_RANGE)
			*val2 = ISL29125_SENSING_RANGE_1; /*10k lux full range*/
		अन्यथा
			*val2 = ISL29125_SENSING_RANGE_0; /*375 lux full range*/
		वापस IIO_VAL_INT_PLUS_MICRO;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक isl29125_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा isl29125_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		अगर (val != 0)
			वापस -EINVAL;
		अगर (val2 == ISL29125_SENSING_RANGE_1)
			data->conf1 |= ISL29125_MODE_RANGE;
		अन्यथा अगर (val2 == ISL29125_SENSING_RANGE_0)
			data->conf1 &= ~ISL29125_MODE_RANGE;
		अन्यथा
			वापस -EINVAL;
		वापस i2c_smbus_ग_लिखो_byte_data(data->client, ISL29125_CONF1,
			data->conf1);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल irqवापस_t isl29125_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा isl29125_data *data = iio_priv(indio_dev);
	पूर्णांक i, j = 0;

	क्रम_each_set_bit(i, indio_dev->active_scan_mask,
		indio_dev->masklength) अणु
		पूर्णांक ret = i2c_smbus_पढ़ो_word_data(data->client,
			isl29125_regs[i].data);
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

अटल IIO_CONST_ATTR(scale_available, "0.005722 0.152590");

अटल काष्ठा attribute *isl29125_attributes[] = अणु
	&iio_स्थिर_attr_scale_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group isl29125_attribute_group = अणु
	.attrs = isl29125_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info isl29125_info = अणु
	.पढ़ो_raw = isl29125_पढ़ो_raw,
	.ग_लिखो_raw = isl29125_ग_लिखो_raw,
	.attrs = &isl29125_attribute_group,
पूर्ण;

अटल पूर्णांक isl29125_buffer_postenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा isl29125_data *data = iio_priv(indio_dev);

	data->conf1 |= ISL29125_MODE_RGB;
	वापस i2c_smbus_ग_लिखो_byte_data(data->client, ISL29125_CONF1,
		data->conf1);
पूर्ण

अटल पूर्णांक isl29125_buffer_predisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा isl29125_data *data = iio_priv(indio_dev);

	data->conf1 &= ~ISL29125_MODE_MASK;
	data->conf1 |= ISL29125_MODE_PD;
	वापस i2c_smbus_ग_लिखो_byte_data(data->client, ISL29125_CONF1,
		data->conf1);
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops isl29125_buffer_setup_ops = अणु
	.postenable = isl29125_buffer_postenable,
	.predisable = isl29125_buffer_predisable,
पूर्ण;

अटल पूर्णांक isl29125_probe(काष्ठा i2c_client *client,
			   स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा isl29125_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (indio_dev == शून्य)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;

	indio_dev->info = &isl29125_info;
	indio_dev->name = ISL29125_DRV_NAME;
	indio_dev->channels = isl29125_channels;
	indio_dev->num_channels = ARRAY_SIZE(isl29125_channels);
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, ISL29125_DEVICE_ID);
	अगर (ret < 0)
		वापस ret;
	अगर (ret != ISL29125_ID)
		वापस -ENODEV;

	data->conf1 = ISL29125_MODE_PD | ISL29125_MODE_RANGE;
	ret = i2c_smbus_ग_लिखो_byte_data(data->client, ISL29125_CONF1,
		data->conf1);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, ISL29125_STATUS, 0);
	अगर (ret < 0)
		वापस ret;

	ret = iio_triggered_buffer_setup(indio_dev, शून्य,
		isl29125_trigger_handler, &isl29125_buffer_setup_ops);
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

अटल पूर्णांक isl29125_घातerकरोwn(काष्ठा isl29125_data *data)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(data->client, ISL29125_CONF1,
		(data->conf1 & ~ISL29125_MODE_MASK) | ISL29125_MODE_PD);
पूर्ण

अटल पूर्णांक isl29125_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);

	iio_device_unरेजिस्टर(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);
	isl29125_घातerकरोwn(iio_priv(indio_dev));

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक isl29125_suspend(काष्ठा device *dev)
अणु
	काष्ठा isl29125_data *data = iio_priv(i2c_get_clientdata(
		to_i2c_client(dev)));
	वापस isl29125_घातerकरोwn(data);
पूर्ण

अटल पूर्णांक isl29125_resume(काष्ठा device *dev)
अणु
	काष्ठा isl29125_data *data = iio_priv(i2c_get_clientdata(
		to_i2c_client(dev)));
	वापस i2c_smbus_ग_लिखो_byte_data(data->client, ISL29125_CONF1,
		data->conf1);
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(isl29125_pm_ops, isl29125_suspend, isl29125_resume);

अटल स्थिर काष्ठा i2c_device_id isl29125_id[] = अणु
	अणु "isl29125", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, isl29125_id);

अटल काष्ठा i2c_driver isl29125_driver = अणु
	.driver = अणु
		.name	= ISL29125_DRV_NAME,
		.pm	= &isl29125_pm_ops,
	पूर्ण,
	.probe		= isl29125_probe,
	.हटाओ		= isl29125_हटाओ,
	.id_table	= isl29125_id,
पूर्ण;
module_i2c_driver(isl29125_driver);

MODULE_AUTHOR("Peter Meerwald <pmeerw@pmeerw.net>");
MODULE_DESCRIPTION("ISL29125 RGB light sensor driver");
MODULE_LICENSE("GPL");
