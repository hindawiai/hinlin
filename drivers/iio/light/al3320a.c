<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AL3320A - Dyna Image Ambient Light Sensor
 *
 * Copyright (c) 2014, Intel Corporation.
 *
 * IIO driver क्रम AL3320A (7-bit I2C slave address 0x1C).
 *
 * TODO: पूर्णांकerrupt support, thresholds
 * When the driver will get support क्रम पूर्णांकerrupt handling, then पूर्णांकerrupt
 * will need to be disabled beक्रमe turning sensor OFF in order to aव्योम
 * potential races with the पूर्णांकerrupt handling.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#घोषणा AL3320A_DRV_NAME "al3320a"

#घोषणा AL3320A_REG_CONFIG		0x00
#घोषणा AL3320A_REG_STATUS		0x01
#घोषणा AL3320A_REG_INT			0x02
#घोषणा AL3320A_REG_WAIT		0x06
#घोषणा AL3320A_REG_CONFIG_RANGE	0x07
#घोषणा AL3320A_REG_PERSIST		0x08
#घोषणा AL3320A_REG_MEAN_TIME		0x09
#घोषणा AL3320A_REG_ADUMMY		0x0A
#घोषणा AL3320A_REG_DATA_LOW		0x22

#घोषणा AL3320A_REG_LOW_THRESH_LOW	0x30
#घोषणा AL3320A_REG_LOW_THRESH_HIGH	0x31
#घोषणा AL3320A_REG_HIGH_THRESH_LOW	0x32
#घोषणा AL3320A_REG_HIGH_THRESH_HIGH	0x33

#घोषणा AL3320A_CONFIG_DISABLE		0x00
#घोषणा AL3320A_CONFIG_ENABLE		0x01

#घोषणा AL3320A_GAIN_MASK		GENMASK(2, 1)

/* chip params शेष values */
#घोषणा AL3320A_DEFAULT_MEAN_TIME	4
#घोषणा AL3320A_DEFAULT_WAIT_TIME	0 /* no रुकोing */

#घोषणा AL3320A_SCALE_AVAILABLE "0.512 0.128 0.032 0.01"

क्रमागत al3320a_range अणु
	AL3320A_RANGE_1, /* 33.28 Klx */
	AL3320A_RANGE_2, /* 8.32 Klx  */
	AL3320A_RANGE_3, /* 2.08 Klx  */
	AL3320A_RANGE_4  /* 0.65 Klx  */
पूर्ण;

अटल स्थिर पूर्णांक al3320a_scales[][2] = अणु
	अणु0, 512000पूर्ण, अणु0, 128000पूर्ण, अणु0, 32000पूर्ण, अणु0, 10000पूर्ण
पूर्ण;

काष्ठा al3320a_data अणु
	काष्ठा i2c_client *client;
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec al3320a_channels[] = अणु
	अणु
		.type	= IIO_LIGHT,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE),
	पूर्ण
पूर्ण;

अटल IIO_CONST_ATTR(in_illuminance_scale_available, AL3320A_SCALE_AVAILABLE);

अटल काष्ठा attribute *al3320a_attributes[] = अणु
	&iio_स्थिर_attr_in_illuminance_scale_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group al3320a_attribute_group = अणु
	.attrs = al3320a_attributes,
पूर्ण;

अटल पूर्णांक al3320a_set_pwr(काष्ठा i2c_client *client, bool pwr)
अणु
	u8 val = pwr ? AL3320A_CONFIG_ENABLE : AL3320A_CONFIG_DISABLE;
	वापस i2c_smbus_ग_लिखो_byte_data(client, AL3320A_REG_CONFIG, val);
पूर्ण

अटल व्योम al3320a_set_pwr_off(व्योम *_data)
अणु
	काष्ठा al3320a_data *data = _data;

	al3320a_set_pwr(data->client, false);
पूर्ण

अटल पूर्णांक al3320a_init(काष्ठा al3320a_data *data)
अणु
	पूर्णांक ret;

	ret = al3320a_set_pwr(data->client, true);

	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, AL3320A_REG_CONFIG_RANGE,
					FIELD_PREP(AL3320A_GAIN_MASK,
						   AL3320A_RANGE_3));
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, AL3320A_REG_MEAN_TIME,
					AL3320A_DEFAULT_MEAN_TIME);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, AL3320A_REG_WAIT,
					AL3320A_DEFAULT_WAIT_TIME);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक al3320a_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
			    पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा al3320a_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		/*
		 * ALS ADC value is stored in two adjacent रेजिस्टरs:
		 * - low byte of output is stored at AL3320A_REG_DATA_LOW
		 * - high byte of output is stored at AL3320A_REG_DATA_LOW + 1
		 */
		ret = i2c_smbus_पढ़ो_word_data(data->client,
					       AL3320A_REG_DATA_LOW);
		अगर (ret < 0)
			वापस ret;
		*val = ret;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		ret = i2c_smbus_पढ़ो_byte_data(data->client,
					       AL3320A_REG_CONFIG_RANGE);
		अगर (ret < 0)
			वापस ret;

		ret = FIELD_GET(AL3320A_GAIN_MASK, ret);
		*val = al3320a_scales[ret][0];
		*val2 = al3320a_scales[ret][1];

		वापस IIO_VAL_INT_PLUS_MICRO;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक al3320a_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val,
			     पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा al3320a_data *data = iio_priv(indio_dev);
	पूर्णांक i;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		क्रम (i = 0; i < ARRAY_SIZE(al3320a_scales); i++) अणु
			अगर (val != al3320a_scales[i][0] ||
			    val2 != al3320a_scales[i][1])
				जारी;

			वापस i2c_smbus_ग_लिखो_byte_data(data->client,
					AL3320A_REG_CONFIG_RANGE,
					FIELD_PREP(AL3320A_GAIN_MASK, i));
		पूर्ण
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info al3320a_info = अणु
	.पढ़ो_raw	= al3320a_पढ़ो_raw,
	.ग_लिखो_raw	= al3320a_ग_लिखो_raw,
	.attrs		= &al3320a_attribute_group,
पूर्ण;

अटल पूर्णांक al3320a_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा al3320a_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;

	indio_dev->info = &al3320a_info;
	indio_dev->name = AL3320A_DRV_NAME;
	indio_dev->channels = al3320a_channels;
	indio_dev->num_channels = ARRAY_SIZE(al3320a_channels);
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = al3320a_init(data);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "al3320a chip init failed\n");
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(&client->dev,
					al3320a_set_pwr_off,
					data);
	अगर (ret < 0)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

अटल पूर्णांक __maybe_unused al3320a_suspend(काष्ठा device *dev)
अणु
	वापस al3320a_set_pwr(to_i2c_client(dev), false);
पूर्ण

अटल पूर्णांक __maybe_unused al3320a_resume(काष्ठा device *dev)
अणु
	वापस al3320a_set_pwr(to_i2c_client(dev), true);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(al3320a_pm_ops, al3320a_suspend, al3320a_resume);

अटल स्थिर काष्ठा i2c_device_id al3320a_id[] = अणु
	अणु"al3320a", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, al3320a_id);

अटल स्थिर काष्ठा of_device_id al3320a_of_match[] = अणु
	अणु .compatible = "dynaimage,al3320a", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, al3320a_of_match);

अटल काष्ठा i2c_driver al3320a_driver = अणु
	.driver = अणु
		.name = AL3320A_DRV_NAME,
		.of_match_table = al3320a_of_match,
		.pm = &al3320a_pm_ops,
	पूर्ण,
	.probe		= al3320a_probe,
	.id_table	= al3320a_id,
पूर्ण;

module_i2c_driver(al3320a_driver);

MODULE_AUTHOR("Daniel Baluta <daniel.baluta@intel.com>");
MODULE_DESCRIPTION("AL3320A Ambient Light Sensor driver");
MODULE_LICENSE("GPL v2");
