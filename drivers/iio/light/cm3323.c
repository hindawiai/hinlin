<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * CM3323 - Capella Color Light Sensor
 *
 * Copyright (c) 2015, Intel Corporation.
 *
 * IIO driver क्रम CM3323 (7-bit I2C slave address 0x10)
 *
 * TODO: calibscale to correct the lens factor
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#घोषणा CM3323_DRV_NAME "cm3323"

#घोषणा CM3323_CMD_CONF		0x00
#घोषणा CM3323_CMD_RED_DATA	0x08
#घोषणा CM3323_CMD_GREEN_DATA	0x09
#घोषणा CM3323_CMD_BLUE_DATA	0x0A
#घोषणा CM3323_CMD_CLEAR_DATA	0x0B

#घोषणा CM3323_CONF_SD_BIT	BIT(0) /* sensor disable */
#घोषणा CM3323_CONF_AF_BIT	BIT(1) /* स्वतः/manual क्रमce mode */
#घोषणा CM3323_CONF_IT_MASK	GENMASK(6, 4)
#घोषणा CM3323_CONF_IT_SHIFT	4

#घोषणा CM3323_INT_TIME_AVAILABLE "0.04 0.08 0.16 0.32 0.64 1.28"

अटल स्थिर काष्ठा अणु
	पूर्णांक val;
	पूर्णांक val2;
पूर्ण cm3323_पूर्णांक_समय[] = अणु
	अणु0, 40000पूर्ण,  /* 40 ms */
	अणु0, 80000पूर्ण,  /* 80 ms */
	अणु0, 160000पूर्ण, /* 160 ms */
	अणु0, 320000पूर्ण, /* 320 ms */
	अणु0, 640000पूर्ण, /* 640 ms */
	अणु1, 280000पूर्ण, /* 1280 ms */
पूर्ण;

काष्ठा cm3323_data अणु
	काष्ठा i2c_client *client;
	u16 reg_conf;
	काष्ठा mutex mutex;
पूर्ण;

#घोषणा CM3323_COLOR_CHANNEL(_color, _addr) अणु \
	.type = IIO_INTENSITY, \
	.modअगरied = 1, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW), \
	.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_INT_TIME), \
	.channel2 = IIO_MOD_LIGHT_##_color, \
	.address = _addr, \
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec cm3323_channels[] = अणु
	CM3323_COLOR_CHANNEL(RED, CM3323_CMD_RED_DATA),
	CM3323_COLOR_CHANNEL(GREEN, CM3323_CMD_GREEN_DATA),
	CM3323_COLOR_CHANNEL(BLUE, CM3323_CMD_BLUE_DATA),
	CM3323_COLOR_CHANNEL(CLEAR, CM3323_CMD_CLEAR_DATA),
पूर्ण;

अटल IIO_CONST_ATTR_INT_TIME_AVAIL(CM3323_INT_TIME_AVAILABLE);

अटल काष्ठा attribute *cm3323_attributes[] = अणु
	&iio_स्थिर_attr_पूर्णांकegration_समय_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group cm3323_attribute_group = अणु
	.attrs = cm3323_attributes,
पूर्ण;

अटल पूर्णांक cm3323_init(काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक ret;
	काष्ठा cm3323_data *data = iio_priv(indio_dev);

	ret = i2c_smbus_पढ़ो_word_data(data->client, CM3323_CMD_CONF);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error reading reg_conf\n");
		वापस ret;
	पूर्ण

	/* enable sensor and set स्वतः क्रमce mode */
	ret &= ~(CM3323_CONF_SD_BIT | CM3323_CONF_AF_BIT);

	ret = i2c_smbus_ग_लिखो_word_data(data->client, CM3323_CMD_CONF, ret);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error writing reg_conf\n");
		वापस ret;
	पूर्ण

	data->reg_conf = ret;

	वापस 0;
पूर्ण

अटल व्योम cm3323_disable(व्योम *data)
अणु
	पूर्णांक ret;
	काष्ठा iio_dev *indio_dev = data;
	काष्ठा cm3323_data *cm_data = iio_priv(indio_dev);

	ret = i2c_smbus_ग_लिखो_word_data(cm_data->client, CM3323_CMD_CONF,
					CM3323_CONF_SD_BIT);
	अगर (ret < 0)
		dev_err(&cm_data->client->dev, "Error writing reg_conf\n");
पूर्ण

अटल पूर्णांक cm3323_set_it_bits(काष्ठा cm3323_data *data, पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक i, ret;
	u16 reg_conf;

	क्रम (i = 0; i < ARRAY_SIZE(cm3323_पूर्णांक_समय); i++) अणु
		अगर (val == cm3323_पूर्णांक_समय[i].val &&
		    val2 == cm3323_पूर्णांक_समय[i].val2) अणु
			reg_conf = data->reg_conf & ~CM3323_CONF_IT_MASK;
			reg_conf |= i << CM3323_CONF_IT_SHIFT;

			ret = i2c_smbus_ग_लिखो_word_data(data->client,
							CM3323_CMD_CONF,
							reg_conf);
			अगर (ret < 0)
				वापस ret;

			data->reg_conf = reg_conf;

			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cm3323_get_it_bits(काष्ठा cm3323_data *data)
अणु
	पूर्णांक bits;

	bits = (data->reg_conf & CM3323_CONF_IT_MASK) >>
		CM3323_CONF_IT_SHIFT;

	अगर (bits >= ARRAY_SIZE(cm3323_पूर्णांक_समय))
		वापस -EINVAL;

	वापस bits;
पूर्ण

अटल पूर्णांक cm3323_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
			   पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक ret;
	काष्ठा cm3323_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&data->mutex);
		ret = i2c_smbus_पढ़ो_word_data(data->client, chan->address);
		अगर (ret < 0) अणु
			mutex_unlock(&data->mutex);
			वापस ret;
		पूर्ण
		*val = ret;
		mutex_unlock(&data->mutex);

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_INT_TIME:
		mutex_lock(&data->mutex);
		ret = cm3323_get_it_bits(data);
		अगर (ret < 0) अणु
			mutex_unlock(&data->mutex);
			वापस ret;
		पूर्ण

		*val = cm3323_पूर्णांक_समय[ret].val;
		*val2 = cm3323_पूर्णांक_समय[ret].val2;
		mutex_unlock(&data->mutex);

		वापस IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक cm3323_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val,
			    पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा cm3323_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_INT_TIME:
		mutex_lock(&data->mutex);
		ret = cm3323_set_it_bits(data, val, val2);
		mutex_unlock(&data->mutex);

		वापस ret;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info cm3323_info = अणु
	.पढ़ो_raw	= cm3323_पढ़ो_raw,
	.ग_लिखो_raw	= cm3323_ग_लिखो_raw,
	.attrs		= &cm3323_attribute_group,
पूर्ण;

अटल पूर्णांक cm3323_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा cm3323_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;

	mutex_init(&data->mutex);

	indio_dev->info = &cm3323_info;
	indio_dev->name = CM3323_DRV_NAME;
	indio_dev->channels = cm3323_channels;
	indio_dev->num_channels = ARRAY_SIZE(cm3323_channels);
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = cm3323_init(indio_dev);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "cm3323 chip init failed\n");
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(&client->dev, cm3323_disable, indio_dev);
	अगर (ret < 0)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id cm3323_id[] = अणु
	अणु"cm3323", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, cm3323_id);

अटल काष्ठा i2c_driver cm3323_driver = अणु
	.driver = अणु
		.name = CM3323_DRV_NAME,
	पूर्ण,
	.probe		= cm3323_probe,
	.id_table	= cm3323_id,
पूर्ण;

module_i2c_driver(cm3323_driver);

MODULE_AUTHOR("Daniel Baluta <daniel.baluta@intel.com>");
MODULE_DESCRIPTION("Capella CM3323 Color Light Sensor driver");
MODULE_LICENSE("GPL v2");
