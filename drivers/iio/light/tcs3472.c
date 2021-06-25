<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tcs3472.c - Support क्रम TAOS TCS3472 color light-to-digital converter
 *
 * Copyright (c) 2013 Peter Meerwald <pmeerw@pmeerw.net>
 *
 * Color light sensor with 16-bit channels क्रम red, green, blue, clear);
 * 7-bit I2C slave address 0x39 (TCS34721, TCS34723) or 0x29 (TCS34725,
 * TCS34727)
 *
 * Datasheet: http://ams.com/eng/content/करोwnload/319364/1117183/file/TCS3472_Datasheet_EN_v2.pdf
 *
 * TODO: रुको समय
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/triggered_buffer.h>

#घोषणा TCS3472_DRV_NAME "tcs3472"

#घोषणा TCS3472_COMMAND BIT(7)
#घोषणा TCS3472_AUTO_INCR BIT(5)
#घोषणा TCS3472_SPECIAL_FUNC (BIT(5) | BIT(6))

#घोषणा TCS3472_INTR_CLEAR (TCS3472_COMMAND | TCS3472_SPECIAL_FUNC | 0x06)

#घोषणा TCS3472_ENABLE (TCS3472_COMMAND | 0x00)
#घोषणा TCS3472_ATIME (TCS3472_COMMAND | 0x01)
#घोषणा TCS3472_WTIME (TCS3472_COMMAND | 0x03)
#घोषणा TCS3472_AILT (TCS3472_COMMAND | TCS3472_AUTO_INCR | 0x04)
#घोषणा TCS3472_AIHT (TCS3472_COMMAND | TCS3472_AUTO_INCR | 0x06)
#घोषणा TCS3472_PERS (TCS3472_COMMAND | 0x0c)
#घोषणा TCS3472_CONFIG (TCS3472_COMMAND | 0x0d)
#घोषणा TCS3472_CONTROL (TCS3472_COMMAND | 0x0f)
#घोषणा TCS3472_ID (TCS3472_COMMAND | 0x12)
#घोषणा TCS3472_STATUS (TCS3472_COMMAND | 0x13)
#घोषणा TCS3472_CDATA (TCS3472_COMMAND | TCS3472_AUTO_INCR | 0x14)
#घोषणा TCS3472_RDATA (TCS3472_COMMAND | TCS3472_AUTO_INCR | 0x16)
#घोषणा TCS3472_GDATA (TCS3472_COMMAND | TCS3472_AUTO_INCR | 0x18)
#घोषणा TCS3472_BDATA (TCS3472_COMMAND | TCS3472_AUTO_INCR | 0x1a)

#घोषणा TCS3472_STATUS_AINT BIT(4)
#घोषणा TCS3472_STATUS_AVALID BIT(0)
#घोषणा TCS3472_ENABLE_AIEN BIT(4)
#घोषणा TCS3472_ENABLE_AEN BIT(1)
#घोषणा TCS3472_ENABLE_PON BIT(0)
#घोषणा TCS3472_CONTROL_AGAIN_MASK (BIT(0) | BIT(1))

काष्ठा tcs3472_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;
	u16 low_thresh;
	u16 high_thresh;
	u8 enable;
	u8 control;
	u8 aसमय;
	u8 apers;
	u16 buffer[8]; /* 4 16-bit channels + 64-bit बारtamp */
पूर्ण;

अटल स्थिर काष्ठा iio_event_spec tcs3472_events[] = अणु
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
		.mask_separate = BIT(IIO_EV_INFO_ENABLE) |
				 BIT(IIO_EV_INFO_PERIOD),
	पूर्ण,
पूर्ण;

#घोषणा TCS3472_CHANNEL(_color, _si, _addr) अणु \
	.type = IIO_INTENSITY, \
	.modअगरied = 1, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW), \
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_CALIBSCALE) | \
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
	.event_spec = _si ? शून्य : tcs3472_events, \
	.num_event_specs = _si ? 0 : ARRAY_SIZE(tcs3472_events), \
पूर्ण

अटल स्थिर पूर्णांक tcs3472_agains[] = अणु 1, 4, 16, 60 पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec tcs3472_channels[] = अणु
	TCS3472_CHANNEL(CLEAR, 0, TCS3472_CDATA),
	TCS3472_CHANNEL(RED, 1, TCS3472_RDATA),
	TCS3472_CHANNEL(GREEN, 2, TCS3472_GDATA),
	TCS3472_CHANNEL(BLUE, 3, TCS3472_BDATA),
	IIO_CHAN_SOFT_TIMESTAMP(4),
पूर्ण;

अटल पूर्णांक tcs3472_req_data(काष्ठा tcs3472_data *data)
अणु
	पूर्णांक tries = 50;
	पूर्णांक ret;

	जबतक (tries--) अणु
		ret = i2c_smbus_पढ़ो_byte_data(data->client, TCS3472_STATUS);
		अगर (ret < 0)
			वापस ret;
		अगर (ret & TCS3472_STATUS_AVALID)
			अवरोध;
		msleep(20);
	पूर्ण

	अगर (tries < 0) अणु
		dev_err(&data->client->dev, "data not ready\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tcs3472_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा tcs3472_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;
		ret = tcs3472_req_data(data);
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
	हाल IIO_CHAN_INFO_CALIBSCALE:
		*val = tcs3472_agains[data->control &
			TCS3472_CONTROL_AGAIN_MASK];
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_INT_TIME:
		*val = 0;
		*val2 = (256 - data->aसमय) * 2400;
		वापस IIO_VAL_INT_PLUS_MICRO;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक tcs3472_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा tcs3472_data *data = iio_priv(indio_dev);
	पूर्णांक i;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_CALIBSCALE:
		अगर (val2 != 0)
			वापस -EINVAL;
		क्रम (i = 0; i < ARRAY_SIZE(tcs3472_agains); i++) अणु
			अगर (val == tcs3472_agains[i]) अणु
				data->control &= ~TCS3472_CONTROL_AGAIN_MASK;
				data->control |= i;
				वापस i2c_smbus_ग_लिखो_byte_data(
					data->client, TCS3472_CONTROL,
					data->control);
			पूर्ण
		पूर्ण
		वापस -EINVAL;
	हाल IIO_CHAN_INFO_INT_TIME:
		अगर (val != 0)
			वापस -EINVAL;
		क्रम (i = 0; i < 256; i++) अणु
			अगर (val2 == (256 - i) * 2400) अणु
				data->aसमय = i;
				वापस i2c_smbus_ग_लिखो_byte_data(
					data->client, TCS3472_ATIME,
					data->aसमय);
			पूर्ण

		पूर्ण
		वापस -EINVAL;
	पूर्ण
	वापस -EINVAL;
पूर्ण

/*
 * Translation from APERS field value to the number of consecutive out-of-range
 * clear channel values beक्रमe an पूर्णांकerrupt is generated
 */
अटल स्थिर पूर्णांक tcs3472_पूर्णांकr_pers[] = अणु
	0, 1, 2, 3, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60
पूर्ण;

अटल पूर्णांक tcs3472_पढ़ो_event(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
	क्रमागत iio_event_direction dir, क्रमागत iio_event_info info, पूर्णांक *val,
	पूर्णांक *val2)
अणु
	काष्ठा tcs3472_data *data = iio_priv(indio_dev);
	पूर्णांक ret;
	अचिन्हित पूर्णांक period;

	mutex_lock(&data->lock);

	चयन (info) अणु
	हाल IIO_EV_INFO_VALUE:
		*val = (dir == IIO_EV_सूची_RISING) ?
			data->high_thresh : data->low_thresh;
		ret = IIO_VAL_INT;
		अवरोध;
	हाल IIO_EV_INFO_PERIOD:
		period = (256 - data->aसमय) * 2400 *
			tcs3472_पूर्णांकr_pers[data->apers];
		*val = period / USEC_PER_SEC;
		*val2 = period % USEC_PER_SEC;
		ret = IIO_VAL_INT_PLUS_MICRO;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक tcs3472_ग_लिखो_event(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
	क्रमागत iio_event_direction dir, क्रमागत iio_event_info info, पूर्णांक val,
	पूर्णांक val2)
अणु
	काष्ठा tcs3472_data *data = iio_priv(indio_dev);
	पूर्णांक ret;
	u8 command;
	पूर्णांक period;
	पूर्णांक i;

	mutex_lock(&data->lock);
	चयन (info) अणु
	हाल IIO_EV_INFO_VALUE:
		चयन (dir) अणु
		हाल IIO_EV_सूची_RISING:
			command = TCS3472_AIHT;
			अवरोध;
		हाल IIO_EV_सूची_FALLING:
			command = TCS3472_AILT;
			अवरोध;
		शेष:
			ret = -EINVAL;
			जाओ error;
		पूर्ण
		ret = i2c_smbus_ग_लिखो_word_data(data->client, command, val);
		अगर (ret)
			जाओ error;

		अगर (dir == IIO_EV_सूची_RISING)
			data->high_thresh = val;
		अन्यथा
			data->low_thresh = val;
		अवरोध;
	हाल IIO_EV_INFO_PERIOD:
		period = val * USEC_PER_SEC + val2;
		क्रम (i = 1; i < ARRAY_SIZE(tcs3472_पूर्णांकr_pers) - 1; i++) अणु
			अगर (period <= (256 - data->aसमय) * 2400 *
					tcs3472_पूर्णांकr_pers[i])
				अवरोध;
		पूर्ण
		ret = i2c_smbus_ग_लिखो_byte_data(data->client, TCS3472_PERS, i);
		अगर (ret)
			जाओ error;

		data->apers = i;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
error:
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक tcs3472_पढ़ो_event_config(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
	क्रमागत iio_event_direction dir)
अणु
	काष्ठा tcs3472_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->lock);
	ret = !!(data->enable & TCS3472_ENABLE_AIEN);
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक tcs3472_ग_लिखो_event_config(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
	क्रमागत iio_event_direction dir, पूर्णांक state)
अणु
	काष्ठा tcs3472_data *data = iio_priv(indio_dev);
	पूर्णांक ret = 0;
	u8 enable_old;

	mutex_lock(&data->lock);

	enable_old = data->enable;

	अगर (state)
		data->enable |= TCS3472_ENABLE_AIEN;
	अन्यथा
		data->enable &= ~TCS3472_ENABLE_AIEN;

	अगर (enable_old != data->enable) अणु
		ret = i2c_smbus_ग_लिखो_byte_data(data->client, TCS3472_ENABLE,
						data->enable);
		अगर (ret)
			data->enable = enable_old;
	पूर्ण
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल irqवापस_t tcs3472_event_handler(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा iio_dev *indio_dev = priv;
	काष्ठा tcs3472_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, TCS3472_STATUS);
	अगर (ret >= 0 && (ret & TCS3472_STATUS_AINT)) अणु
		iio_push_event(indio_dev, IIO_UNMOD_EVENT_CODE(IIO_INTENSITY, 0,
						IIO_EV_TYPE_THRESH,
						IIO_EV_सूची_EITHER),
				iio_get_समय_ns(indio_dev));

		i2c_smbus_पढ़ो_byte_data(data->client, TCS3472_INTR_CLEAR);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t tcs3472_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा tcs3472_data *data = iio_priv(indio_dev);
	पूर्णांक i, j = 0;

	पूर्णांक ret = tcs3472_req_data(data);
	अगर (ret < 0)
		जाओ करोne;

	क्रम_each_set_bit(i, indio_dev->active_scan_mask,
		indio_dev->masklength) अणु
		ret = i2c_smbus_पढ़ो_word_data(data->client,
			TCS3472_CDATA + 2*i);
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

अटल sमाप_प्रकार tcs3472_show_पूर्णांक_समय_available(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	माप_प्रकार len = 0;
	पूर्णांक i;

	क्रम (i = 1; i <= 256; i++)
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "0.%06d ",
			2400 * i);

	/* replace trailing space by newline */
	buf[len - 1] = '\n';

	वापस len;
पूर्ण

अटल IIO_CONST_ATTR(calibscale_available, "1 4 16 60");
अटल IIO_DEV_ATTR_INT_TIME_AVAIL(tcs3472_show_पूर्णांक_समय_available);

अटल काष्ठा attribute *tcs3472_attributes[] = अणु
	&iio_स्थिर_attr_calibscale_available.dev_attr.attr,
	&iio_dev_attr_पूर्णांकegration_समय_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group tcs3472_attribute_group = अणु
	.attrs = tcs3472_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info tcs3472_info = अणु
	.पढ़ो_raw = tcs3472_पढ़ो_raw,
	.ग_लिखो_raw = tcs3472_ग_लिखो_raw,
	.पढ़ो_event_value = tcs3472_पढ़ो_event,
	.ग_लिखो_event_value = tcs3472_ग_लिखो_event,
	.पढ़ो_event_config = tcs3472_पढ़ो_event_config,
	.ग_लिखो_event_config = tcs3472_ग_लिखो_event_config,
	.attrs = &tcs3472_attribute_group,
पूर्ण;

अटल पूर्णांक tcs3472_probe(काष्ठा i2c_client *client,
			   स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tcs3472_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (indio_dev == शून्य)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	mutex_init(&data->lock);

	indio_dev->info = &tcs3472_info;
	indio_dev->name = TCS3472_DRV_NAME;
	indio_dev->channels = tcs3472_channels;
	indio_dev->num_channels = ARRAY_SIZE(tcs3472_channels);
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, TCS3472_ID);
	अगर (ret < 0)
		वापस ret;

	अगर (ret == 0x44)
		dev_info(&client->dev, "TCS34721/34725 found\n");
	अन्यथा अगर (ret == 0x4d)
		dev_info(&client->dev, "TCS34723/34727 found\n");
	अन्यथा
		वापस -ENODEV;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, TCS3472_CONTROL);
	अगर (ret < 0)
		वापस ret;
	data->control = ret;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, TCS3472_ATIME);
	अगर (ret < 0)
		वापस ret;
	data->aसमय = ret;

	ret = i2c_smbus_पढ़ो_word_data(data->client, TCS3472_AILT);
	अगर (ret < 0)
		वापस ret;
	data->low_thresh = ret;

	ret = i2c_smbus_पढ़ो_word_data(data->client, TCS3472_AIHT);
	अगर (ret < 0)
		वापस ret;
	data->high_thresh = ret;

	data->apers = 1;
	ret = i2c_smbus_ग_लिखो_byte_data(data->client, TCS3472_PERS,
					data->apers);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, TCS3472_ENABLE);
	अगर (ret < 0)
		वापस ret;

	/* enable device */
	data->enable = ret | TCS3472_ENABLE_PON | TCS3472_ENABLE_AEN;
	data->enable &= ~TCS3472_ENABLE_AIEN;
	ret = i2c_smbus_ग_लिखो_byte_data(data->client, TCS3472_ENABLE,
		data->enable);
	अगर (ret < 0)
		वापस ret;

	ret = iio_triggered_buffer_setup(indio_dev, शून्य,
		tcs3472_trigger_handler, शून्य);
	अगर (ret < 0)
		वापस ret;

	अगर (client->irq) अणु
		ret = request_thपढ़ोed_irq(client->irq, शून्य,
					   tcs3472_event_handler,
					   IRQF_TRIGGER_FALLING | IRQF_SHARED |
					   IRQF_ONESHOT,
					   client->name, indio_dev);
		अगर (ret)
			जाओ buffer_cleanup;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0)
		जाओ मुक्त_irq;

	वापस 0;

मुक्त_irq:
	मुक्त_irq(client->irq, indio_dev);
buffer_cleanup:
	iio_triggered_buffer_cleanup(indio_dev);
	वापस ret;
पूर्ण

अटल पूर्णांक tcs3472_घातerकरोwn(काष्ठा tcs3472_data *data)
अणु
	पूर्णांक ret;
	u8 enable_mask = TCS3472_ENABLE_AEN | TCS3472_ENABLE_PON;

	mutex_lock(&data->lock);

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, TCS3472_ENABLE,
		data->enable & ~enable_mask);
	अगर (!ret)
		data->enable &= ~enable_mask;

	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक tcs3472_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);

	iio_device_unरेजिस्टर(indio_dev);
	मुक्त_irq(client->irq, indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);
	tcs3472_घातerकरोwn(iio_priv(indio_dev));

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक tcs3472_suspend(काष्ठा device *dev)
अणु
	काष्ठा tcs3472_data *data = iio_priv(i2c_get_clientdata(
		to_i2c_client(dev)));
	वापस tcs3472_घातerकरोwn(data);
पूर्ण

अटल पूर्णांक tcs3472_resume(काष्ठा device *dev)
अणु
	काष्ठा tcs3472_data *data = iio_priv(i2c_get_clientdata(
		to_i2c_client(dev)));
	पूर्णांक ret;
	u8 enable_mask = TCS3472_ENABLE_AEN | TCS3472_ENABLE_PON;

	mutex_lock(&data->lock);

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, TCS3472_ENABLE,
		data->enable | enable_mask);
	अगर (!ret)
		data->enable |= enable_mask;

	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(tcs3472_pm_ops, tcs3472_suspend, tcs3472_resume);

अटल स्थिर काष्ठा i2c_device_id tcs3472_id[] = अणु
	अणु "tcs3472", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tcs3472_id);

अटल काष्ठा i2c_driver tcs3472_driver = अणु
	.driver = अणु
		.name	= TCS3472_DRV_NAME,
		.pm	= &tcs3472_pm_ops,
	पूर्ण,
	.probe		= tcs3472_probe,
	.हटाओ		= tcs3472_हटाओ,
	.id_table	= tcs3472_id,
पूर्ण;
module_i2c_driver(tcs3472_driver);

MODULE_AUTHOR("Peter Meerwald <pmeerw@pmeerw.net>");
MODULE_DESCRIPTION("TCS3472 color light sensors driver");
MODULE_LICENSE("GPL");
