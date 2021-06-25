<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * htu21.c - Support क्रम Measurement-Specialties
 *           htu21 temperature & humidity sensor
 *	     and humidity part of MS8607 sensor
 *
 * Copyright (c) 2014 Measurement-Specialties
 *
 * (7-bit I2C slave address 0x40)
 *
 * Datasheet:
 *  http://www.meas-spec.com/करोwnloads/HTU21D.pdf
 * Datasheet:
 *  http://www.meas-spec.com/करोwnloads/MS8607-02BA01.pdf
 */

#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#समावेश "../common/ms_sensors/ms_sensors_i2c.h"

#घोषणा HTU21_RESET				0xFE

क्रमागत अणु
	HTU21,
	MS8607
पूर्ण;

अटल स्थिर पूर्णांक htu21_samp_freq[4] = अणु 20, 40, 70, 120 पूर्ण;
/* String copy of the above स्थिर क्रम पढ़ोability purpose */
अटल स्थिर अक्षर htu21_show_samp_freq[] = "20 40 70 120";

अटल पूर्णांक htu21_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			  काष्ठा iio_chan_spec स्थिर *channel, पूर्णांक *val,
			  पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक ret, temperature;
	अचिन्हित पूर्णांक humidity;
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
		हाल IIO_HUMIDITYRELATIVE:	/* in milli %RH */
			ret = ms_sensors_ht_पढ़ो_humidity(dev_data,
							  &humidity);
			अगर (ret)
				वापस ret;
			*val = humidity;

			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*val = htu21_samp_freq[dev_data->res_index];

		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक htu21_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा ms_ht_dev *dev_data = iio_priv(indio_dev);
	पूर्णांक i, ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		i = ARRAY_SIZE(htu21_samp_freq);
		जबतक (i-- > 0)
			अगर (val == htu21_samp_freq[i])
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

अटल स्थिर काष्ठा iio_chan_spec htu21_channels[] = अणु
	अणु
		.type = IIO_TEMP,
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_PROCESSED),
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ),
	 पूर्ण,
	अणु
		.type = IIO_HUMIDITYRELATIVE,
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_PROCESSED),
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ),
	 पूर्ण
पूर्ण;

/*
 * Meas Spec recommendation is to not पढ़ो temperature
 * on this driver part क्रम MS8607
 */
अटल स्थिर काष्ठा iio_chan_spec ms8607_channels[] = अणु
	अणु
		.type = IIO_HUMIDITYRELATIVE,
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_PROCESSED),
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ),
	 पूर्ण
पूर्ण;

अटल sमाप_प्रकार htu21_show_battery_low(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ms_ht_dev *dev_data = iio_priv(indio_dev);

	वापस ms_sensors_show_battery_low(dev_data, buf);
पूर्ण

अटल sमाप_प्रकार htu21_show_heater(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ms_ht_dev *dev_data = iio_priv(indio_dev);

	वापस ms_sensors_show_heater(dev_data, buf);
पूर्ण

अटल sमाप_प्रकार htu21_ग_लिखो_heater(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ms_ht_dev *dev_data = iio_priv(indio_dev);

	वापस ms_sensors_ग_लिखो_heater(dev_data, buf, len);
पूर्ण

अटल IIO_CONST_ATTR_SAMP_FREQ_AVAIL(htu21_show_samp_freq);
अटल IIO_DEVICE_ATTR(battery_low, S_IRUGO,
		       htu21_show_battery_low, शून्य, 0);
अटल IIO_DEVICE_ATTR(heater_enable, S_IRUGO | S_IWUSR,
		       htu21_show_heater, htu21_ग_लिखो_heater, 0);

अटल काष्ठा attribute *htu21_attributes[] = अणु
	&iio_स्थिर_attr_sampling_frequency_available.dev_attr.attr,
	&iio_dev_attr_battery_low.dev_attr.attr,
	&iio_dev_attr_heater_enable.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group htu21_attribute_group = अणु
	.attrs = htu21_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info htu21_info = अणु
	.पढ़ो_raw = htu21_पढ़ो_raw,
	.ग_लिखो_raw = htu21_ग_लिखो_raw,
	.attrs = &htu21_attribute_group,
पूर्ण;

अटल पूर्णांक htu21_probe(काष्ठा i2c_client *client,
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

	indio_dev->info = &htu21_info;
	indio_dev->name = id->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	अगर (id->driver_data == MS8607) अणु
		indio_dev->channels = ms8607_channels;
		indio_dev->num_channels = ARRAY_SIZE(ms8607_channels);
	पूर्ण अन्यथा अणु
		indio_dev->channels = htu21_channels;
		indio_dev->num_channels = ARRAY_SIZE(htu21_channels);
	पूर्ण

	i2c_set_clientdata(client, indio_dev);

	ret = ms_sensors_reset(client, HTU21_RESET, 15000);
	अगर (ret)
		वापस ret;

	ret = ms_sensors_पढ़ो_serial(client, &serial_number);
	अगर (ret)
		वापस ret;
	dev_info(&client->dev, "Serial number : %llx", serial_number);

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id htu21_id[] = अणु
	अणु"htu21", HTU21पूर्ण,
	अणु"ms8607-humidity", MS8607पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, htu21_id);

अटल स्थिर काष्ठा of_device_id htu21_of_match[] = अणु
	अणु .compatible = "meas,htu21", पूर्ण,
	अणु .compatible = "meas,ms8607-humidity", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, htu21_of_match);

अटल काष्ठा i2c_driver htu21_driver = अणु
	.probe = htu21_probe,
	.id_table = htu21_id,
	.driver = अणु
		   .name = "htu21",
		   .of_match_table = htu21_of_match,
		   पूर्ण,
पूर्ण;

module_i2c_driver(htu21_driver);

MODULE_DESCRIPTION("Measurement-Specialties htu21 temperature and humidity driver");
MODULE_AUTHOR("William Markezana <william.markezana@meas-spec.com>");
MODULE_AUTHOR("Ludovic Tancerel <ludovic.tancerel@maplehightech.com>");
MODULE_LICENSE("GPL v2");
