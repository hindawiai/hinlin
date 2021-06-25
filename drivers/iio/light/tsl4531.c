<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tsl4531.c - Support क्रम TAOS TSL4531 ambient light sensor
 *
 * Copyright 2013 Peter Meerwald <pmeerw@pmeerw.net>
 *
 * IIO driver क्रम the TSL4531x family
 *   TSL45311/TSL45313: 7-bit I2C slave address 0x39
 *   TSL45315/TSL45317: 7-bit I2C slave address 0x29
 *
 * TODO: single cycle measurement
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#घोषणा TSL4531_DRV_NAME "tsl4531"

#घोषणा TSL4531_COMMAND BIT(7)

#घोषणा TSL4531_CONTROL (TSL4531_COMMAND | 0x00)
#घोषणा TSL4531_CONFIG (TSL4531_COMMAND | 0x01)
#घोषणा TSL4531_DATA (TSL4531_COMMAND | 0x04)
#घोषणा TSL4531_ID (TSL4531_COMMAND | 0x0a)

/* operating modes in control रेजिस्टर */
#घोषणा TSL4531_MODE_POWERDOWN 0x00
#घोषणा TSL4531_MODE_SINGLE_ADC 0x02
#घोषणा TSL4531_MODE_NORMAL 0x03

/* पूर्णांकegration समय control in config रेजिस्टर */
#घोषणा TSL4531_TCNTRL_400MS 0x00
#घोषणा TSL4531_TCNTRL_200MS 0x01
#घोषणा TSL4531_TCNTRL_100MS 0x02

/* part number in id रेजिस्टर */
#घोषणा TSL45311_ID 0x8
#घोषणा TSL45313_ID 0x9
#घोषणा TSL45315_ID 0xa
#घोषणा TSL45317_ID 0xb
#घोषणा TSL4531_ID_SHIFT 4

काष्ठा tsl4531_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;
	पूर्णांक पूर्णांक_समय;
पूर्ण;

अटल IIO_CONST_ATTR_INT_TIME_AVAIL("0.1 0.2 0.4");

अटल काष्ठा attribute *tsl4531_attributes[] = अणु
	&iio_स्थिर_attr_पूर्णांकegration_समय_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group tsl4531_attribute_group = अणु
	.attrs = tsl4531_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec tsl4531_channels[] = अणु
	अणु
		.type = IIO_LIGHT,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SCALE) |
			BIT(IIO_CHAN_INFO_INT_TIME)
	पूर्ण
पूर्ण;

अटल पूर्णांक tsl4531_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *chan,
				पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा tsl4531_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = i2c_smbus_पढ़ो_word_data(data->client,
			TSL4531_DATA);
		अगर (ret < 0)
			वापस ret;
		*val = ret;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		/* 0.. 1x, 1 .. 2x, 2 .. 4x */
		*val = 1 << data->पूर्णांक_समय;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_INT_TIME:
		अगर (data->पूर्णांक_समय == 0)
			*val2 = 400000;
		अन्यथा अगर (data->पूर्णांक_समय == 1)
			*val2 = 200000;
		अन्यथा अगर (data->पूर्णांक_समय == 2)
			*val2 = 100000;
		अन्यथा
			वापस -EINVAL;
		*val = 0;
		वापस IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक tsl4531_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा tsl4531_data *data = iio_priv(indio_dev);
	पूर्णांक पूर्णांक_समय, ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_INT_TIME:
		अगर (val != 0)
			वापस -EINVAL;
		अगर (val2 == 400000)
			पूर्णांक_समय = 0;
		अन्यथा अगर (val2 == 200000)
			पूर्णांक_समय = 1;
		अन्यथा अगर (val2 == 100000)
			पूर्णांक_समय = 2;
		अन्यथा
			वापस -EINVAL;
		mutex_lock(&data->lock);
		ret = i2c_smbus_ग_लिखो_byte_data(data->client,
			TSL4531_CONFIG, पूर्णांक_समय);
		अगर (ret >= 0)
			data->पूर्णांक_समय = पूर्णांक_समय;
		mutex_unlock(&data->lock);
		वापस ret;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info tsl4531_info = अणु
	.पढ़ो_raw = tsl4531_पढ़ो_raw,
	.ग_लिखो_raw = tsl4531_ग_लिखो_raw,
	.attrs = &tsl4531_attribute_group,
पूर्ण;

अटल पूर्णांक tsl4531_check_id(काष्ठा i2c_client *client)
अणु
	पूर्णांक ret = i2c_smbus_पढ़ो_byte_data(client, TSL4531_ID);
	अगर (ret < 0)
		वापस ret;

	चयन (ret >> TSL4531_ID_SHIFT) अणु
	हाल TSL45311_ID:
	हाल TSL45313_ID:
	हाल TSL45315_ID:
	हाल TSL45317_ID:
		वापस 0;
	शेष:
		वापस -ENODEV;
	पूर्ण
पूर्ण

अटल पूर्णांक tsl4531_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tsl4531_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	mutex_init(&data->lock);

	ret = tsl4531_check_id(client);
	अगर (ret) अणु
		dev_err(&client->dev, "no TSL4531 sensor\n");
		वापस ret;
	पूर्ण

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, TSL4531_CONTROL,
		TSL4531_MODE_NORMAL);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, TSL4531_CONFIG,
		TSL4531_TCNTRL_400MS);
	अगर (ret < 0)
		वापस ret;

	indio_dev->info = &tsl4531_info;
	indio_dev->channels = tsl4531_channels;
	indio_dev->num_channels = ARRAY_SIZE(tsl4531_channels);
	indio_dev->name = TSL4531_DRV_NAME;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	वापस iio_device_रेजिस्टर(indio_dev);
पूर्ण

अटल पूर्णांक tsl4531_घातerकरोwn(काष्ठा i2c_client *client)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(client, TSL4531_CONTROL,
		TSL4531_MODE_POWERDOWN);
पूर्ण

अटल पूर्णांक tsl4531_हटाओ(काष्ठा i2c_client *client)
अणु
	iio_device_unरेजिस्टर(i2c_get_clientdata(client));
	tsl4531_घातerकरोwn(client);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक tsl4531_suspend(काष्ठा device *dev)
अणु
	वापस tsl4531_घातerकरोwn(to_i2c_client(dev));
पूर्ण

अटल पूर्णांक tsl4531_resume(काष्ठा device *dev)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(to_i2c_client(dev), TSL4531_CONTROL,
		TSL4531_MODE_NORMAL);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(tsl4531_pm_ops, tsl4531_suspend, tsl4531_resume);
#घोषणा TSL4531_PM_OPS (&tsl4531_pm_ops)
#अन्यथा
#घोषणा TSL4531_PM_OPS शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id tsl4531_id[] = अणु
	अणु "tsl4531", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tsl4531_id);

अटल काष्ठा i2c_driver tsl4531_driver = अणु
	.driver = अणु
		.name   = TSL4531_DRV_NAME,
		.pm	= TSL4531_PM_OPS,
	पूर्ण,
	.probe  = tsl4531_probe,
	.हटाओ = tsl4531_हटाओ,
	.id_table = tsl4531_id,
पूर्ण;

module_i2c_driver(tsl4531_driver);

MODULE_AUTHOR("Peter Meerwald <pmeerw@pmeerw.net>");
MODULE_DESCRIPTION("TAOS TSL4531 ambient light sensors driver");
MODULE_LICENSE("GPL");
