<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tsys02d.c - Support क्रम Measurement-Specialties tsys02d temperature sensor
 *
 * Copyright (c) 2015 Measurement-Specialties
 *
 * (7-bit I2C slave address 0x40)
 *
 * Datasheet:
 *  http://www.meas-spec.com/करोwnloads/Digital_Sensor_TSYS02D.pdf
 */

#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/module.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#समावेश "../common/ms_sensors/ms_sensors_i2c.h"

#घोषणा TSYS02D_RESET				0xFE

अटल स्थिर पूर्णांक tsys02d_samp_freq[4] = अणु 20, 40, 70, 140 पूर्ण;
/* String copy of the above स्थिर क्रम पढ़ोability purpose */
अटल स्थिर अक्षर tsys02d_show_samp_freq[] = "20 40 70 140";

अटल पूर्णांक tsys02d_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *channel, पूर्णांक *val,
			    पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक ret;
	s32 temperature;
	काष्ठा ms_ht_dev *dev_data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_PROCESSED:
		चयन (channel->type) अणु
		हाल IIO_TEMP:	/* in milli तओC */
			ret = ms_sensors_ht_पढ़ो_temperature(dev_data,
							     &temperature);
			अगर (ret)
				वापस ret;
			*val = temperature;

			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*val = tsys02d_samp_freq[dev_data->res_index];

		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक tsys02d_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा ms_ht_dev *dev_data = iio_priv(indio_dev);
	पूर्णांक i, ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		i = ARRAY_SIZE(tsys02d_samp_freq);
		जबतक (i-- > 0)
			अगर (val == tsys02d_samp_freq[i])
				अवरोध;
		अगर (i < 0)
			वापस -EINVAL;
		mutex_lock(&dev_data->lock);
		dev_data->res_index = i;
		ret = ms_sensors_ग_लिखो_resolution(dev_data, i);
		mutex_unlock(&dev_data->lock);

		वापस ret;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec tsys02d_channels[] = अणु
	अणु
		.type = IIO_TEMP,
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_PROCESSED),
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ),
	पूर्ण
पूर्ण;

अटल sमाप_प्रकार tsys02_पढ़ो_battery_low(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ms_ht_dev *dev_data = iio_priv(indio_dev);

	वापस ms_sensors_show_battery_low(dev_data, buf);
पूर्ण

अटल IIO_CONST_ATTR_SAMP_FREQ_AVAIL(tsys02d_show_samp_freq);
अटल IIO_DEVICE_ATTR(battery_low, S_IRUGO,
		       tsys02_पढ़ो_battery_low, शून्य, 0);

अटल काष्ठा attribute *tsys02d_attributes[] = अणु
	&iio_स्थिर_attr_sampling_frequency_available.dev_attr.attr,
	&iio_dev_attr_battery_low.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group tsys02d_attribute_group = अणु
	.attrs = tsys02d_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info tsys02d_info = अणु
	.पढ़ो_raw = tsys02d_पढ़ो_raw,
	.ग_लिखो_raw = tsys02d_ग_लिखो_raw,
	.attrs = &tsys02d_attribute_group,
पूर्ण;

अटल पूर्णांक tsys02d_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा ms_ht_dev *dev_data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;
	u64 serial_number;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_WRITE_BYTE_DATA |
				     I2C_FUNC_SMBUS_WRITE_BYTE |
				     I2C_FUNC_SMBUS_READ_I2C_BLOCK)) अणु
		dev_err(&client->dev,
			"Adapter does not support some i2c transaction\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*dev_data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	dev_data = iio_priv(indio_dev);
	dev_data->client = client;
	dev_data->res_index = 0;
	mutex_init(&dev_data->lock);

	indio_dev->info = &tsys02d_info;
	indio_dev->name = id->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = tsys02d_channels;
	indio_dev->num_channels = ARRAY_SIZE(tsys02d_channels);

	i2c_set_clientdata(client, indio_dev);

	ret = ms_sensors_reset(client, TSYS02D_RESET, 15000);
	अगर (ret)
		वापस ret;

	ret = ms_sensors_पढ़ो_serial(client, &serial_number);
	अगर (ret)
		वापस ret;
	dev_info(&client->dev, "Serial number : %llx", serial_number);

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tsys02d_id[] = अणु
	अणु"tsys02d", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tsys02d_id);

अटल काष्ठा i2c_driver tsys02d_driver = अणु
	.probe = tsys02d_probe,
	.id_table = tsys02d_id,
	.driver = अणु
		   .name = "tsys02d",
		   पूर्ण,
पूर्ण;

module_i2c_driver(tsys02d_driver);

MODULE_DESCRIPTION("Measurement-Specialties tsys02d temperature driver");
MODULE_AUTHOR("William Markezana <william.markezana@meas-spec.com>");
MODULE_AUTHOR("Ludovic Tancerel <ludovic.tancerel@maplehightech.com>");
MODULE_LICENSE("GPL v2");
