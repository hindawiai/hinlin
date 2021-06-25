<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * si7005.c - Support क्रम Siद_असल Si7005 humidity and temperature sensor
 *
 * Copyright (c) 2014 Peter Meerwald <pmeerw@pmeerw.net>
 *
 * (7-bit I2C slave address 0x40)
 *
 * TODO: heater, fast mode, processed mode (temp. / linearity compensation)
 */

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/pm.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#घोषणा SI7005_STATUS 0x00
#घोषणा SI7005_DATA 0x01 /* 16-bit, MSB */
#घोषणा SI7005_CONFIG 0x03
#घोषणा SI7005_ID 0x11

#घोषणा SI7005_STATUS_NRDY BIT(0)
#घोषणा SI7005_CONFIG_TEMP BIT(4)
#घोषणा SI7005_CONFIG_START BIT(0)

#घोषणा SI7005_ID_7005 0x50
#घोषणा SI7005_ID_7015 0xf0

काष्ठा si7005_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;
	u8 config;
पूर्ण;

अटल पूर्णांक si7005_पढ़ो_measurement(काष्ठा si7005_data *data, bool temp)
अणु
	पूर्णांक tries = 50;
	पूर्णांक ret;

	mutex_lock(&data->lock);

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, SI7005_CONFIG,
		data->config | SI7005_CONFIG_START |
		(temp ? SI7005_CONFIG_TEMP : 0));
	अगर (ret < 0)
		जाओ करोne;

	जबतक (tries-- > 0) अणु
		msleep(20);
		ret = i2c_smbus_पढ़ो_byte_data(data->client, SI7005_STATUS);
		अगर (ret < 0)
			जाओ करोne;
		अगर (!(ret & SI7005_STATUS_NRDY))
			अवरोध;
	पूर्ण
	अगर (tries < 0) अणु
		ret = -EIO;
		जाओ करोne;
	पूर्ण

	ret = i2c_smbus_पढ़ो_word_swapped(data->client, SI7005_DATA);

करोne:
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक si7005_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
			    पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा si7005_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = si7005_पढ़ो_measurement(data, chan->type == IIO_TEMP);
		अगर (ret < 0)
			वापस ret;
		*val = ret;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		अगर (chan->type == IIO_TEMP) अणु
			*val = 7;
			*val2 = 812500;
		पूर्ण अन्यथा अणु
			*val = 3;
			*val2 = 906250;
		पूर्ण
		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_OFFSET:
		अगर (chan->type == IIO_TEMP)
			*val = -50 * 32 * 4;
		अन्यथा
			*val = -24 * 16 * 16;
		वापस IIO_VAL_INT;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec si7005_channels[] = अणु
	अणु
		.type = IIO_HUMIDITYRELATIVE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SCALE) | BIT(IIO_CHAN_INFO_OFFSET),
	पूर्ण,
	अणु
		.type = IIO_TEMP,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SCALE) | BIT(IIO_CHAN_INFO_OFFSET),
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा iio_info si7005_info = अणु
	.पढ़ो_raw = si7005_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक si7005_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा si7005_data *data;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_WORD_DATA))
		वापस -EOPNOTSUPP;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	mutex_init(&data->lock);

	indio_dev->name = dev_name(&client->dev);
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &si7005_info;

	indio_dev->channels = si7005_channels;
	indio_dev->num_channels = ARRAY_SIZE(si7005_channels);

	ret = i2c_smbus_पढ़ो_byte_data(client, SI7005_ID);
	अगर (ret < 0)
		वापस ret;
	अगर (ret != SI7005_ID_7005 && ret != SI7005_ID_7015)
		वापस -ENODEV;

	ret = i2c_smbus_पढ़ो_byte_data(client, SI7005_CONFIG);
	अगर (ret < 0)
		वापस ret;
	data->config = ret;

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id si7005_id[] = अणु
	अणु "si7005", 0 पूर्ण,
	अणु "th02", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, si7005_id);

अटल काष्ठा i2c_driver si7005_driver = अणु
	.driver = अणु
		.name	= "si7005",
	पूर्ण,
	.probe = si7005_probe,
	.id_table = si7005_id,
पूर्ण;
module_i2c_driver(si7005_driver);

MODULE_AUTHOR("Peter Meerwald <pmeerw@pmeerw.net>");
MODULE_DESCRIPTION("Silabs Si7005 humidity and temperature sensor driver");
MODULE_LICENSE("GPL");
