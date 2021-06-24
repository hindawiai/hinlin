<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * adjd_s311.c - Support क्रम ADJD-S311-CR999 digital color sensor
 *
 * Copyright (C) 2012 Peter Meerwald <pmeerw@pmeerw.net>
 *
 * driver क्रम ADJD-S311-CR999 digital color sensor (10-bit channels क्रम
 * red, green, blue, clear); 7-bit I2C slave address 0x74
 *
 * limitations: no calibration, no offset mode, no sleep mode
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/err.h>
#समावेश <linux/irq.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/triggered_buffer.h>

#घोषणा ADJD_S311_DRV_NAME "adjd_s311"

#घोषणा ADJD_S311_CTRL		0x00
#घोषणा ADJD_S311_CONFIG	0x01
#घोषणा ADJD_S311_CAP_RED	0x06
#घोषणा ADJD_S311_CAP_GREEN	0x07
#घोषणा ADJD_S311_CAP_BLUE	0x08
#घोषणा ADJD_S311_CAP_CLEAR	0x09
#घोषणा ADJD_S311_INT_RED	0x0a
#घोषणा ADJD_S311_INT_GREEN	0x0c
#घोषणा ADJD_S311_INT_BLUE	0x0e
#घोषणा ADJD_S311_INT_CLEAR	0x10
#घोषणा ADJD_S311_DATA_RED	0x40
#घोषणा ADJD_S311_DATA_GREEN	0x42
#घोषणा ADJD_S311_DATA_BLUE	0x44
#घोषणा ADJD_S311_DATA_CLEAR	0x46
#घोषणा ADJD_S311_OFFSET_RED	0x48
#घोषणा ADJD_S311_OFFSET_GREEN	0x49
#घोषणा ADJD_S311_OFFSET_BLUE	0x4a
#घोषणा ADJD_S311_OFFSET_CLEAR	0x4b

#घोषणा ADJD_S311_CTRL_GOFS	0x02
#घोषणा ADJD_S311_CTRL_GSSR	0x01
#घोषणा ADJD_S311_CAP_MASK	0x0f
#घोषणा ADJD_S311_INT_MASK	0x0fff
#घोषणा ADJD_S311_DATA_MASK	0x03ff

काष्ठा adjd_s311_data अणु
	काष्ठा i2c_client *client;
	u16 *buffer;
पूर्ण;

क्रमागत adjd_s311_channel_idx अणु
	IDX_RED, IDX_GREEN, IDX_BLUE, IDX_CLEAR
पूर्ण;

#घोषणा ADJD_S311_DATA_REG(chan) (ADJD_S311_DATA_RED + (chan) * 2)
#घोषणा ADJD_S311_INT_REG(chan) (ADJD_S311_INT_RED + (chan) * 2)
#घोषणा ADJD_S311_CAP_REG(chan) (ADJD_S311_CAP_RED + (chan))

अटल पूर्णांक adjd_s311_req_data(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा adjd_s311_data *data = iio_priv(indio_dev);
	पूर्णांक tries = 10;

	पूर्णांक ret = i2c_smbus_ग_लिखो_byte_data(data->client, ADJD_S311_CTRL,
		ADJD_S311_CTRL_GSSR);
	अगर (ret < 0)
		वापस ret;

	जबतक (tries--) अणु
		ret = i2c_smbus_पढ़ो_byte_data(data->client, ADJD_S311_CTRL);
		अगर (ret < 0)
			वापस ret;
		अगर (!(ret & ADJD_S311_CTRL_GSSR))
			अवरोध;
		msleep(20);
	पूर्ण

	अगर (tries < 0) अणु
		dev_err(&data->client->dev,
			"adjd_s311_req_data() failed, data not ready\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adjd_s311_पढ़ो_data(काष्ठा iio_dev *indio_dev, u8 reg, पूर्णांक *val)
अणु
	काष्ठा adjd_s311_data *data = iio_priv(indio_dev);

	पूर्णांक ret = adjd_s311_req_data(indio_dev);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_पढ़ो_word_data(data->client, reg);
	अगर (ret < 0)
		वापस ret;

	*val = ret & ADJD_S311_DATA_MASK;

	वापस 0;
पूर्ण

अटल irqवापस_t adjd_s311_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा adjd_s311_data *data = iio_priv(indio_dev);
	s64 समय_ns = iio_get_समय_ns(indio_dev);
	पूर्णांक i, j = 0;

	पूर्णांक ret = adjd_s311_req_data(indio_dev);
	अगर (ret < 0)
		जाओ करोne;

	क्रम_each_set_bit(i, indio_dev->active_scan_mask,
		indio_dev->masklength) अणु
		ret = i2c_smbus_पढ़ो_word_data(data->client,
			ADJD_S311_DATA_REG(i));
		अगर (ret < 0)
			जाओ करोne;

		data->buffer[j++] = ret & ADJD_S311_DATA_MASK;
	पूर्ण

	iio_push_to_buffers_with_बारtamp(indio_dev, data->buffer, समय_ns);

करोne:
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

#घोषणा ADJD_S311_CHANNEL(_color, _scan_idx) अणु \
	.type = IIO_INTENSITY, \
	.modअगरied = 1, \
	.address = (IDX_##_color), \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | \
		BIT(IIO_CHAN_INFO_HARDWAREGAIN) | \
		BIT(IIO_CHAN_INFO_INT_TIME), \
	.channel2 = (IIO_MOD_LIGHT_##_color), \
	.scan_index = (_scan_idx), \
	.scan_type = अणु \
		.sign = 'u', \
		.realbits = 10, \
		.storagebits = 16, \
		.endianness = IIO_CPU, \
	पूर्ण, \
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec adjd_s311_channels[] = अणु
	ADJD_S311_CHANNEL(RED, 0),
	ADJD_S311_CHANNEL(GREEN, 1),
	ADJD_S311_CHANNEL(BLUE, 2),
	ADJD_S311_CHANNEL(CLEAR, 3),
	IIO_CHAN_SOFT_TIMESTAMP(4),
पूर्ण;

अटल पूर्णांक adjd_s311_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा adjd_s311_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = adjd_s311_पढ़ो_data(indio_dev,
			ADJD_S311_DATA_REG(chan->address), val);
		अगर (ret < 0)
			वापस ret;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_HARDWAREGAIN:
		ret = i2c_smbus_पढ़ो_byte_data(data->client,
			ADJD_S311_CAP_REG(chan->address));
		अगर (ret < 0)
			वापस ret;
		*val = ret & ADJD_S311_CAP_MASK;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_INT_TIME:
		ret = i2c_smbus_पढ़ो_word_data(data->client,
			ADJD_S311_INT_REG(chan->address));
		अगर (ret < 0)
			वापस ret;
		*val = 0;
		/*
		 * not करोcumented, based on measurement:
		 * 4095 LSBs correspond to roughly 4 ms
		 */
		*val2 = ret & ADJD_S311_INT_MASK;
		वापस IIO_VAL_INT_PLUS_MICRO;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक adjd_s311_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा adjd_s311_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_HARDWAREGAIN:
		अगर (val < 0 || val > ADJD_S311_CAP_MASK)
			वापस -EINVAL;

		वापस i2c_smbus_ग_लिखो_byte_data(data->client,
			ADJD_S311_CAP_REG(chan->address), val);
	हाल IIO_CHAN_INFO_INT_TIME:
		अगर (val != 0 || val2 < 0 || val2 > ADJD_S311_INT_MASK)
			वापस -EINVAL;

		वापस i2c_smbus_ग_लिखो_word_data(data->client,
			ADJD_S311_INT_REG(chan->address), val2);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक adjd_s311_update_scan_mode(काष्ठा iio_dev *indio_dev,
	स्थिर अचिन्हित दीर्घ *scan_mask)
अणु
	काष्ठा adjd_s311_data *data = iio_priv(indio_dev);

	kमुक्त(data->buffer);
	data->buffer = kदो_स्मृति(indio_dev->scan_bytes, GFP_KERNEL);
	अगर (data->buffer == शून्य)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_info adjd_s311_info = अणु
	.पढ़ो_raw = adjd_s311_पढ़ो_raw,
	.ग_लिखो_raw = adjd_s311_ग_लिखो_raw,
	.update_scan_mode = adjd_s311_update_scan_mode,
पूर्ण;

अटल पूर्णांक adjd_s311_probe(काष्ठा i2c_client *client,
			   स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा adjd_s311_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक err;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (indio_dev == शून्य)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;

	indio_dev->info = &adjd_s311_info;
	indio_dev->name = ADJD_S311_DRV_NAME;
	indio_dev->channels = adjd_s311_channels;
	indio_dev->num_channels = ARRAY_SIZE(adjd_s311_channels);
	indio_dev->modes = INDIO_सूचीECT_MODE;

	err = iio_triggered_buffer_setup(indio_dev, शून्य,
		adjd_s311_trigger_handler, शून्य);
	अगर (err < 0)
		वापस err;

	err = iio_device_रेजिस्टर(indio_dev);
	अगर (err)
		जाओ निकास_unreg_buffer;

	dev_info(&client->dev, "ADJD-S311 color sensor registered\n");

	वापस 0;

निकास_unreg_buffer:
	iio_triggered_buffer_cleanup(indio_dev);
	वापस err;
पूर्ण

अटल पूर्णांक adjd_s311_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा adjd_s311_data *data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);
	kमुक्त(data->buffer);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id adjd_s311_id[] = अणु
	अणु "adjd_s311", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adjd_s311_id);

अटल काष्ठा i2c_driver adjd_s311_driver = अणु
	.driver = अणु
		.name	= ADJD_S311_DRV_NAME,
	पूर्ण,
	.probe		= adjd_s311_probe,
	.हटाओ		= adjd_s311_हटाओ,
	.id_table	= adjd_s311_id,
पूर्ण;
module_i2c_driver(adjd_s311_driver);

MODULE_AUTHOR("Peter Meerwald <pmeerw@pmeerw.net>");
MODULE_DESCRIPTION("ADJD-S311 color sensor");
MODULE_LICENSE("GPL");
