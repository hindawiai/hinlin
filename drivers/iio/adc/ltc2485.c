<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ltc2485.c - Driver क्रम Linear Technology LTC2485 ADC
 *
 * Copyright (C) 2016 Alison Schofield <amsfield22@gmail.com>
 *
 * Datasheet: http://cds.linear.com/करोcs/en/datasheet/2485fd.pdf
 */

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

/* Power-on configuration: rejects both 50/60Hz, operates at 1x speed */
#घोषणा LTC2485_CONFIG_DEFAULT		0

काष्ठा ltc2485_data अणु
	काष्ठा i2c_client	*client;
	kसमय_प्रकार			समय_prev;	/* last conversion */
पूर्ण;

अटल व्योम ltc2485_रुको_conv(काष्ठा ltc2485_data *data)
अणु
	स्थिर अचिन्हित पूर्णांक conv_समय = 147;	/* conversion समय ms */
	अचिन्हित पूर्णांक समय_elapsed;

	/* delay अगर conversion समय not passed since last पढ़ो or ग_लिखो */
	समय_elapsed = kसमय_ms_delta(kसमय_get(), data->समय_prev);

	अगर (समय_elapsed < conv_समय)
		msleep(conv_समय - समय_elapsed);
पूर्ण

अटल पूर्णांक ltc2485_पढ़ो(काष्ठा ltc2485_data *data, पूर्णांक *val)
अणु
	काष्ठा i2c_client *client = data->client;
	__be32 buf = 0;
	पूर्णांक ret;

	ltc2485_रुको_conv(data);

	ret = i2c_master_recv(client, (अक्षर *)&buf, 4);
	अगर (ret < 0)  अणु
		dev_err(&client->dev, "i2c_master_recv failed\n");
		वापस ret;
	पूर्ण
	data->समय_prev = kसमय_get();
	*val = sign_extend32(be32_to_cpu(buf) >> 6, 24);

	वापस ret;
पूर्ण

अटल पूर्णांक ltc2485_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा ltc2485_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	अगर (mask == IIO_CHAN_INFO_RAW) अणु
		ret = ltc2485_पढ़ो(data, val);
		अगर (ret < 0)
			वापस ret;

		वापस IIO_VAL_INT;

	पूर्ण अन्यथा अगर (mask == IIO_CHAN_INFO_SCALE) अणु
		*val = 5000;			/* on board vref millivolts */
		*val2 = 25;			/* 25 (24 + sign) data bits */
		वापस IIO_VAL_FRACTIONAL_LOG2;

	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec ltc2485_channel[] = अणु
	अणु
		.type = IIO_VOLTAGE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE)
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_info ltc2485_info = अणु
	.पढ़ो_raw = ltc2485_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक ltc2485_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा ltc2485_data *data;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C |
				     I2C_FUNC_SMBUS_WRITE_BYTE))
		वापस -EOPNOTSUPP;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;

	indio_dev->name = id->name;
	indio_dev->info = &ltc2485_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = ltc2485_channel;
	indio_dev->num_channels = ARRAY_SIZE(ltc2485_channel);

	ret = i2c_smbus_ग_लिखो_byte(data->client, LTC2485_CONFIG_DEFAULT);
	अगर (ret < 0)
		वापस ret;

	data->समय_prev = kसमय_get();

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ltc2485_id[] = अणु
	अणु "ltc2485", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ltc2485_id);

अटल काष्ठा i2c_driver ltc2485_driver = अणु
	.driver = अणु
		.name = "ltc2485",
	पूर्ण,
	.probe = ltc2485_probe,
	.id_table = ltc2485_id,
पूर्ण;
module_i2c_driver(ltc2485_driver);

MODULE_AUTHOR("Alison Schofield <amsfield22@gmail.com>");
MODULE_DESCRIPTION("Linear Technology LTC2485 ADC driver");
MODULE_LICENSE("GPL v2");
