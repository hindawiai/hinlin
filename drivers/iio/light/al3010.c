<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AL3010 - Dyna Image Ambient Light Sensor
 *
 * Copyright (c) 2014, Intel Corporation.
 * Copyright (c) 2016, Dyna-Image Corp.
 * Copyright (c) 2020, David Heidelberg, Michaध Mirosधaw, Dmitry Osipenko
 *
 * IIO driver क्रम AL3010 (7-bit I2C slave address 0x1C).
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

#घोषणा AL3010_DRV_NAME "al3010"

#घोषणा AL3010_REG_SYSTEM		0x00
#घोषणा AL3010_REG_DATA_LOW		0x0c
#घोषणा AL3010_REG_CONFIG		0x10

#घोषणा AL3010_CONFIG_DISABLE		0x00
#घोषणा AL3010_CONFIG_ENABLE		0x01

#घोषणा AL3010_GAIN_MASK		GENMASK(6,4)

#घोषणा AL3010_SCALE_AVAILABLE "1.1872 0.2968 0.0742 0.018"

क्रमागत al3xxxx_range अणु
	AL3XXX_RANGE_1, /* 77806 lx */
	AL3XXX_RANGE_2, /* 19542 lx */
	AL3XXX_RANGE_3, /*  4863 lx */
	AL3XXX_RANGE_4  /*  1216 lx */
पूर्ण;

अटल स्थिर पूर्णांक al3010_scales[][2] = अणु
	अणु0, 1187200पूर्ण, अणु0, 296800पूर्ण, अणु0, 74200पूर्ण, अणु0, 18600पूर्ण
पूर्ण;

काष्ठा al3010_data अणु
	काष्ठा i2c_client *client;
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec al3010_channels[] = अणु
	अणु
		.type	= IIO_LIGHT,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE),
	पूर्ण
पूर्ण;

अटल IIO_CONST_ATTR(in_illuminance_scale_available, AL3010_SCALE_AVAILABLE);

अटल काष्ठा attribute *al3010_attributes[] = अणु
	&iio_स्थिर_attr_in_illuminance_scale_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group al3010_attribute_group = अणु
	.attrs = al3010_attributes,
पूर्ण;

अटल पूर्णांक al3010_set_pwr(काष्ठा i2c_client *client, bool pwr)
अणु
	u8 val = pwr ? AL3010_CONFIG_ENABLE : AL3010_CONFIG_DISABLE;
	वापस i2c_smbus_ग_लिखो_byte_data(client, AL3010_REG_SYSTEM, val);
पूर्ण

अटल व्योम al3010_set_pwr_off(व्योम *_data)
अणु
	काष्ठा al3010_data *data = _data;

	al3010_set_pwr(data->client, false);
पूर्ण

अटल पूर्णांक al3010_init(काष्ठा al3010_data *data)
अणु
	पूर्णांक ret;

	ret = al3010_set_pwr(data->client, true);

	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, AL3010_REG_CONFIG,
					FIELD_PREP(AL3010_GAIN_MASK,
						   AL3XXX_RANGE_3));
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक al3010_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
			   पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा al3010_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		/*
		 * ALS ADC value is stored in two adjacent रेजिस्टरs:
		 * - low byte of output is stored at AL3010_REG_DATA_LOW
		 * - high byte of output is stored at AL3010_REG_DATA_LOW + 1
		 */
		ret = i2c_smbus_पढ़ो_word_data(data->client,
					       AL3010_REG_DATA_LOW);
		अगर (ret < 0)
			वापस ret;
		*val = ret;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		ret = i2c_smbus_पढ़ो_byte_data(data->client,
					       AL3010_REG_CONFIG);
		अगर (ret < 0)
			वापस ret;

		ret = FIELD_GET(AL3010_GAIN_MASK, ret);
		*val = al3010_scales[ret][0];
		*val2 = al3010_scales[ret][1];

		वापस IIO_VAL_INT_PLUS_MICRO;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक al3010_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val,
			    पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा al3010_data *data = iio_priv(indio_dev);
	पूर्णांक i;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		क्रम (i = 0; i < ARRAY_SIZE(al3010_scales); i++) अणु
			अगर (val != al3010_scales[i][0] ||
			    val2 != al3010_scales[i][1])
				जारी;

			वापस i2c_smbus_ग_लिखो_byte_data(data->client,
					AL3010_REG_CONFIG,
					FIELD_PREP(AL3010_GAIN_MASK, i));
		पूर्ण
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info al3010_info = अणु
	.पढ़ो_raw	= al3010_पढ़ो_raw,
	.ग_लिखो_raw	= al3010_ग_लिखो_raw,
	.attrs		= &al3010_attribute_group,
पूर्ण;

अटल पूर्णांक al3010_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा al3010_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;

	indio_dev->info = &al3010_info;
	indio_dev->name = AL3010_DRV_NAME;
	indio_dev->channels = al3010_channels;
	indio_dev->num_channels = ARRAY_SIZE(al3010_channels);
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = al3010_init(data);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "al3010 chip init failed\n");
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(&client->dev,
					al3010_set_pwr_off,
					data);
	अगर (ret < 0)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

अटल पूर्णांक __maybe_unused al3010_suspend(काष्ठा device *dev)
अणु
	वापस al3010_set_pwr(to_i2c_client(dev), false);
पूर्ण

अटल पूर्णांक __maybe_unused al3010_resume(काष्ठा device *dev)
अणु
	वापस al3010_set_pwr(to_i2c_client(dev), true);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(al3010_pm_ops, al3010_suspend, al3010_resume);

अटल स्थिर काष्ठा i2c_device_id al3010_id[] = अणु
	अणु"al3010", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, al3010_id);

अटल स्थिर काष्ठा of_device_id al3010_of_match[] = अणु
	अणु .compatible = "dynaimage,al3010", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, al3010_of_match);

अटल काष्ठा i2c_driver al3010_driver = अणु
	.driver = अणु
		.name = AL3010_DRV_NAME,
		.of_match_table = al3010_of_match,
		.pm = &al3010_pm_ops,
	पूर्ण,
	.probe		= al3010_probe,
	.id_table	= al3010_id,
पूर्ण;
module_i2c_driver(al3010_driver);

MODULE_AUTHOR("Daniel Baluta <daniel.baluta@nxp.com>");
MODULE_AUTHOR("David Heidelberg <david@ixit.cz>");
MODULE_DESCRIPTION("AL3010 Ambient Light Sensor driver");
MODULE_LICENSE("GPL v2");
