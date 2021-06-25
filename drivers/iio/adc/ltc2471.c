<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम Linear Technology LTC2471 and LTC2473 voltage monitors
 * The LTC2473 is identical to the 2471, but reports a dअगरferential संकेत.
 *
 * Copyright (C) 2017 Topic Embedded Products
 * Author: Mike Looijmans <mike.looijmans@topic.nl>
 */

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

क्रमागत ltc2471_chips अणु
	ltc2471,
	ltc2473,
पूर्ण;

काष्ठा ltc2471_data अणु
	काष्ठा i2c_client *client;
पूर्ण;

/* Reference voltage is 1.25V */
#घोषणा LTC2471_VREF 1250

/* Read two bytes from the I2C bus to obtain the ADC result */
अटल पूर्णांक ltc2471_get_value(काष्ठा i2c_client *client)
अणु
	पूर्णांक ret;
	__be16 buf;

	ret = i2c_master_recv(client, (अक्षर *)&buf, माप(buf));
	अगर (ret < 0)
		वापस ret;
	अगर (ret != माप(buf))
		वापस -EIO;

	/* MSB first */
	वापस be16_to_cpu(buf);
पूर्ण

अटल पूर्णांक ltc2471_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ info)
अणु
	काष्ठा ltc2471_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (info) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = ltc2471_get_value(data->client);
		अगर (ret < 0)
			वापस ret;
		*val = ret;
		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		अगर (chan->dअगरferential)
			/* Output ranges from -VREF to +VREF */
			*val = 2 * LTC2471_VREF;
		अन्यथा
			/* Output ranges from 0 to VREF */
			*val = LTC2471_VREF;
		*val2 = 16;	/* 16 data bits */
		वापस IIO_VAL_FRACTIONAL_LOG2;

	हाल IIO_CHAN_INFO_OFFSET:
		/* Only dअगरferential chip has this property */
		*val = -LTC2471_VREF;
		वापस IIO_VAL_INT;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec ltc2471_channel[] = अणु
	अणु
		.type = IIO_VOLTAGE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec ltc2473_channel[] = अणु
	अणु
		.type = IIO_VOLTAGE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) |
					    BIT(IIO_CHAN_INFO_OFFSET),
		.dअगरferential = 1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_info ltc2471_info = अणु
	.पढ़ो_raw = ltc2471_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक ltc2471_i2c_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा ltc2471_data *data;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		वापस -EOPNOTSUPP;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	data->client = client;

	indio_dev->name = id->name;
	indio_dev->info = &ltc2471_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	अगर (id->driver_data == ltc2473)
		indio_dev->channels = ltc2473_channel;
	अन्यथा
		indio_dev->channels = ltc2471_channel;
	indio_dev->num_channels = 1;

	/* Trigger once to start conversion and check अगर chip is there */
	ret = ltc2471_get_value(client);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Cannot read from device.\n");
		वापस ret;
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ltc2471_i2c_id[] = अणु
	अणु "ltc2471", ltc2471 पूर्ण,
	अणु "ltc2473", ltc2473 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ltc2471_i2c_id);

अटल काष्ठा i2c_driver ltc2471_i2c_driver = अणु
	.driver = अणु
		.name = "ltc2471",
	पूर्ण,
	.probe    = ltc2471_i2c_probe,
	.id_table = ltc2471_i2c_id,
पूर्ण;

module_i2c_driver(ltc2471_i2c_driver);

MODULE_DESCRIPTION("LTC2471/LTC2473 ADC driver");
MODULE_AUTHOR("Topic Embedded Products");
MODULE_LICENSE("GPL v2");
