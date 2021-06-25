<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * पंचांगp006.c - Support क्रम TI TMP006 IR thermopile sensor
 *
 * Copyright (c) 2013 Peter Meerwald <pmeerw@pmeerw.net>
 *
 * Driver क्रम the Texas Instruments I2C 16-bit IR thermopile sensor
 *
 * (7-bit I2C slave address 0x40, changeable via ADR pins)
 *
 * TODO: data पढ़ोy irq
 */

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/pm.h>
#समावेश <linux/bitops.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#घोषणा TMP006_VOBJECT 0x00
#घोषणा TMP006_TAMBIENT 0x01
#घोषणा TMP006_CONFIG 0x02
#घोषणा TMP006_MANUFACTURER_ID 0xfe
#घोषणा TMP006_DEVICE_ID 0xff

#घोषणा TMP006_TAMBIENT_SHIFT 2

#घोषणा TMP006_CONFIG_RESET BIT(15)
#घोषणा TMP006_CONFIG_DRDY_EN BIT(8)
#घोषणा TMP006_CONFIG_DRDY BIT(7)

#घोषणा TMP006_CONFIG_MOD_MASK GENMASK(14, 12)

#घोषणा TMP006_CONFIG_CR_MASK GENMASK(11, 9)
#घोषणा TMP006_CONFIG_CR_SHIFT 9

#घोषणा TMP006_MANUFACTURER_MAGIC 0x5449
#घोषणा TMP006_DEVICE_MAGIC 0x0067

काष्ठा पंचांगp006_data अणु
	काष्ठा i2c_client *client;
	u16 config;
पूर्ण;

अटल पूर्णांक पंचांगp006_पढ़ो_measurement(काष्ठा पंचांगp006_data *data, u8 reg)
अणु
	s32 ret;
	पूर्णांक tries = 50;

	जबतक (tries-- > 0) अणु
		ret = i2c_smbus_पढ़ो_word_swapped(data->client,
			TMP006_CONFIG);
		अगर (ret < 0)
			वापस ret;
		अगर (ret & TMP006_CONFIG_DRDY)
			अवरोध;
		msleep(100);
	पूर्ण

	अगर (tries < 0)
		वापस -EIO;

	वापस i2c_smbus_पढ़ो_word_swapped(data->client, reg);
पूर्ण

अटल स्थिर पूर्णांक पंचांगp006_freqs[5][2] = अणु अणु4, 0पूर्ण, अणु2, 0पूर्ण, अणु1, 0पूर्ण,
					अणु0, 500000पूर्ण, अणु0, 250000पूर्ण पूर्ण;

अटल पूर्णांक पंचांगp006_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *channel, पूर्णांक *val,
			    पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा पंचांगp006_data *data = iio_priv(indio_dev);
	s32 ret;
	पूर्णांक cr;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (channel->type == IIO_VOLTAGE) अणु
			/* LSB is 156.25 nV */
			ret = पंचांगp006_पढ़ो_measurement(data, TMP006_VOBJECT);
			अगर (ret < 0)
				वापस ret;
			*val = sign_extend32(ret, 15);
		पूर्ण अन्यथा अगर (channel->type == IIO_TEMP) अणु
			/* LSB is 0.03125 degrees Celsius */
			ret = पंचांगp006_पढ़ो_measurement(data, TMP006_TAMBIENT);
			अगर (ret < 0)
				वापस ret;
			*val = sign_extend32(ret, 15) >> TMP006_TAMBIENT_SHIFT;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		अगर (channel->type == IIO_VOLTAGE) अणु
			*val = 0;
			*val2 = 156250;
		पूर्ण अन्यथा अगर (channel->type == IIO_TEMP) अणु
			*val = 31;
			*val2 = 250000;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		cr = (data->config & TMP006_CONFIG_CR_MASK)
			>> TMP006_CONFIG_CR_SHIFT;
		*val = पंचांगp006_freqs[cr][0];
		*val2 = पंचांगp006_freqs[cr][1];
		वापस IIO_VAL_INT_PLUS_MICRO;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक पंचांगp006_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक val,
			    पूर्णांक val2,
			    दीर्घ mask)
अणु
	काष्ठा पंचांगp006_data *data = iio_priv(indio_dev);
	पूर्णांक i;

	अगर (mask != IIO_CHAN_INFO_SAMP_FREQ)
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(पंचांगp006_freqs); i++)
		अगर ((val == पंचांगp006_freqs[i][0]) &&
		    (val2 == पंचांगp006_freqs[i][1])) अणु
			data->config &= ~TMP006_CONFIG_CR_MASK;
			data->config |= i << TMP006_CONFIG_CR_SHIFT;

			वापस i2c_smbus_ग_लिखो_word_swapped(data->client,
							    TMP006_CONFIG,
							    data->config);

		पूर्ण
	वापस -EINVAL;
पूर्ण

अटल IIO_CONST_ATTR(sampling_frequency_available, "4 2 1 0.5 0.25");

अटल काष्ठा attribute *पंचांगp006_attributes[] = अणु
	&iio_स्थिर_attr_sampling_frequency_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group पंचांगp006_attribute_group = अणु
	.attrs = पंचांगp006_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec पंचांगp006_channels[] = अणु
	अणु
		.type = IIO_VOLTAGE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SCALE),
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ),
	पूर्ण,
	अणु
		.type = IIO_TEMP,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SCALE),
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ),
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा iio_info पंचांगp006_info = अणु
	.पढ़ो_raw = पंचांगp006_पढ़ो_raw,
	.ग_लिखो_raw = पंचांगp006_ग_लिखो_raw,
	.attrs = &पंचांगp006_attribute_group,
पूर्ण;

अटल bool पंचांगp006_check_identअगरication(काष्ठा i2c_client *client)
अणु
	पूर्णांक mid, did;

	mid = i2c_smbus_पढ़ो_word_swapped(client, TMP006_MANUFACTURER_ID);
	अगर (mid < 0)
		वापस false;

	did = i2c_smbus_पढ़ो_word_swapped(client, TMP006_DEVICE_ID);
	अगर (did < 0)
		वापस false;

	वापस mid == TMP006_MANUFACTURER_MAGIC && did == TMP006_DEVICE_MAGIC;
पूर्ण

अटल पूर्णांक पंचांगp006_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा पंचांगp006_data *data;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_WORD_DATA))
		वापस -EOPNOTSUPP;

	अगर (!पंचांगp006_check_identअगरication(client)) अणु
		dev_err(&client->dev, "no TMP006 sensor\n");
		वापस -ENODEV;
	पूर्ण

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;

	indio_dev->name = dev_name(&client->dev);
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &पंचांगp006_info;

	indio_dev->channels = पंचांगp006_channels;
	indio_dev->num_channels = ARRAY_SIZE(पंचांगp006_channels);

	ret = i2c_smbus_पढ़ो_word_swapped(data->client, TMP006_CONFIG);
	अगर (ret < 0)
		वापस ret;
	data->config = ret;

	वापस iio_device_रेजिस्टर(indio_dev);
पूर्ण

अटल पूर्णांक पंचांगp006_घातerकरोwn(काष्ठा पंचांगp006_data *data)
अणु
	वापस i2c_smbus_ग_लिखो_word_swapped(data->client, TMP006_CONFIG,
		data->config & ~TMP006_CONFIG_MOD_MASK);
पूर्ण

अटल पूर्णांक पंचांगp006_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);

	iio_device_unरेजिस्टर(indio_dev);
	पंचांगp006_घातerकरोwn(iio_priv(indio_dev));

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक पंचांगp006_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	वापस पंचांगp006_घातerकरोwn(iio_priv(indio_dev));
पूर्ण

अटल पूर्णांक पंचांगp006_resume(काष्ठा device *dev)
अणु
	काष्ठा पंचांगp006_data *data = iio_priv(i2c_get_clientdata(
		to_i2c_client(dev)));
	वापस i2c_smbus_ग_लिखो_word_swapped(data->client, TMP006_CONFIG,
		data->config | TMP006_CONFIG_MOD_MASK);
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(पंचांगp006_pm_ops, पंचांगp006_suspend, पंचांगp006_resume);

अटल स्थिर काष्ठा i2c_device_id पंचांगp006_id[] = अणु
	अणु "tmp006", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, पंचांगp006_id);

अटल काष्ठा i2c_driver पंचांगp006_driver = अणु
	.driver = अणु
		.name	= "tmp006",
		.pm	= &पंचांगp006_pm_ops,
	पूर्ण,
	.probe = पंचांगp006_probe,
	.हटाओ = पंचांगp006_हटाओ,
	.id_table = पंचांगp006_id,
पूर्ण;
module_i2c_driver(पंचांगp006_driver);

MODULE_AUTHOR("Peter Meerwald <pmeerw@pmeerw.net>");
MODULE_DESCRIPTION("TI TMP006 IR thermopile sensor driver");
MODULE_LICENSE("GPL");
