<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * veml6070.c - Support क्रम Vishay VEML6070 UV A light sensor
 *
 * Copyright 2016 Peter Meerwald-Stadler <pmeerw@pmeerw.net>
 *
 * IIO driver क्रम VEML6070 (7-bit I2C slave addresses 0x38 and 0x39)
 *
 * TODO: पूर्णांकegration समय, ACK संकेत
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#घोषणा VEML6070_DRV_NAME "veml6070"

#घोषणा VEML6070_ADDR_CONFIG_DATA_MSB 0x38 /* पढ़ो: MSB data, ग_लिखो: config */
#घोषणा VEML6070_ADDR_DATA_LSB	0x39 /* LSB data */

#घोषणा VEML6070_COMMAND_ACK	BIT(5) /* उठाओ पूर्णांकerrupt when over threshold */
#घोषणा VEML6070_COMMAND_IT	GENMASK(3, 2) /* bit mask पूर्णांकegration समय */
#घोषणा VEML6070_COMMAND_RSRVD	BIT(1) /* reserved, set to 1 */
#घोषणा VEML6070_COMMAND_SD	BIT(0) /* shutकरोwn mode when set */

#घोषणा VEML6070_IT_10	0x04 /* पूर्णांकegration समय 1x */

काष्ठा veml6070_data अणु
	काष्ठा i2c_client *client1;
	काष्ठा i2c_client *client2;
	u8 config;
	काष्ठा mutex lock;
पूर्ण;

अटल पूर्णांक veml6070_पढ़ो(काष्ठा veml6070_data *data)
अणु
	पूर्णांक ret;
	u8 msb, lsb;

	mutex_lock(&data->lock);

	/* disable shutकरोwn */
	ret = i2c_smbus_ग_लिखो_byte(data->client1,
	    data->config & ~VEML6070_COMMAND_SD);
	अगर (ret < 0)
		जाओ out;

	msleep(125 + 10); /* measurement takes up to 125 ms क्रम IT 1x */

	ret = i2c_smbus_पढ़ो_byte(data->client2); /* पढ़ो MSB, address 0x39 */
	अगर (ret < 0)
		जाओ out;
	msb = ret;

	ret = i2c_smbus_पढ़ो_byte(data->client1); /* पढ़ो LSB, address 0x38 */
	अगर (ret < 0)
		जाओ out;
	lsb = ret;

	/* shutकरोwn again */
	ret = i2c_smbus_ग_लिखो_byte(data->client1, data->config);
	अगर (ret < 0)
		जाओ out;

	ret = (msb << 8) | lsb;

out:
	mutex_unlock(&data->lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec veml6070_channels[] = अणु
	अणु
		.type = IIO_INTENSITY,
		.modअगरied = 1,
		.channel2 = IIO_MOD_LIGHT_UV,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
	पूर्ण,
	अणु
		.type = IIO_UVINDEX,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),
	पूर्ण
पूर्ण;

अटल पूर्णांक veml6070_to_uv_index(अचिन्हित val)
अणु
	/*
	 * conversion of raw UV पूर्णांकensity values to UV index depends on
	 * पूर्णांकegration समय (IT) and value of the resistor connected to
	 * the RSET pin (शेष: 270 KOhm)
	 */
	अचिन्हित uvi[11] = अणु
		187, 373, 560, /* low */
		746, 933, 1120, /* moderate */
		1308, 1494, /* high */
		1681, 1868, 2054पूर्ण; /* very high */
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(uvi); i++)
		अगर (val <= uvi[i])
			वापस i;

	वापस 11; /* extreme */
पूर्ण

अटल पूर्णांक veml6070_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *chan,
				पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा veml6070_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
	हाल IIO_CHAN_INFO_PROCESSED:
		ret = veml6070_पढ़ो(data);
		अगर (ret < 0)
			वापस ret;
		अगर (mask == IIO_CHAN_INFO_PROCESSED)
			*val = veml6070_to_uv_index(ret);
		अन्यथा
			*val = ret;
		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info veml6070_info = अणु
	.पढ़ो_raw = veml6070_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक veml6070_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा veml6070_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client1 = client;
	mutex_init(&data->lock);

	indio_dev->info = &veml6070_info;
	indio_dev->channels = veml6070_channels;
	indio_dev->num_channels = ARRAY_SIZE(veml6070_channels);
	indio_dev->name = VEML6070_DRV_NAME;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	data->client2 = i2c_new_dummy_device(client->adapter, VEML6070_ADDR_DATA_LSB);
	अगर (IS_ERR(data->client2)) अणु
		dev_err(&client->dev, "i2c device for second chip address failed\n");
		वापस PTR_ERR(data->client2);
	पूर्ण

	data->config = VEML6070_IT_10 | VEML6070_COMMAND_RSRVD |
		VEML6070_COMMAND_SD;
	ret = i2c_smbus_ग_लिखो_byte(data->client1, data->config);
	अगर (ret < 0)
		जाओ fail;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0)
		जाओ fail;

	वापस ret;

fail:
	i2c_unरेजिस्टर_device(data->client2);
	वापस ret;
पूर्ण

अटल पूर्णांक veml6070_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा veml6070_data *data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	i2c_unरेजिस्टर_device(data->client2);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id veml6070_id[] = अणु
	अणु "veml6070", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, veml6070_id);

अटल काष्ठा i2c_driver veml6070_driver = अणु
	.driver = अणु
		.name   = VEML6070_DRV_NAME,
	पूर्ण,
	.probe  = veml6070_probe,
	.हटाओ  = veml6070_हटाओ,
	.id_table = veml6070_id,
पूर्ण;

module_i2c_driver(veml6070_driver);

MODULE_AUTHOR("Peter Meerwald-Stadler <pmeerw@pmeerw.net>");
MODULE_DESCRIPTION("Vishay VEML6070 UV A light sensor driver");
MODULE_LICENSE("GPL");
