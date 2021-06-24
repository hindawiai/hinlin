<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ms5637.c - Support क्रम Measurement-Specialties MS5637, MS5805
 *            MS5837 and MS8607 pressure & temperature sensor
 *
 * Copyright (c) 2015 Measurement-Specialties
 *
 * (7-bit I2C slave address 0x76)
 *
 * Datasheet:
 *  http://www.meas-spec.com/करोwnloads/MS5637-02BA03.pdf
 * Datasheet:
 *  http://www.meas-spec.com/करोwnloads/MS5805-02BA01.pdf
 * Datasheet:
 *  http://www.meas-spec.com/करोwnloads/MS5837-30BA.pdf
 * Datasheet:
 *  http://www.meas-spec.com/करोwnloads/MS8607-02BA01.pdf
 */

#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/i2c.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/mutex.h>

#समावेश "../common/ms_sensors/ms_sensors_i2c.h"

काष्ठा ms_tp_data अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा ms_tp_hw_data *hw;
पूर्ण;

अटल स्थिर पूर्णांक ms5637_samp_freq[6] = अणु 960, 480, 240, 120, 60, 30 पूर्ण;

अटल sमाप_प्रकार ms5637_show_samp_freq(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ms_tp_dev *dev_data = iio_priv(indio_dev);
	पूर्णांक i, len = 0;

	क्रम (i = 0; i <= dev_data->hw->max_res_index; i++)
		len += sysfs_emit_at(buf, len, "%u ", ms5637_samp_freq[i]);
	sysfs_emit_at(buf, len - 1, "\n");

	वापस len;
पूर्ण

अटल पूर्णांक ms5637_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *channel, पूर्णांक *val,
			   पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक ret;
	पूर्णांक temperature;
	अचिन्हित पूर्णांक pressure;
	काष्ठा ms_tp_dev *dev_data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_PROCESSED:
		ret = ms_sensors_पढ़ो_temp_and_pressure(dev_data,
							&temperature,
							&pressure);
		अगर (ret)
			वापस ret;

		चयन (channel->type) अणु
		हाल IIO_TEMP:	/* in milli तओC */
			*val = temperature;

			वापस IIO_VAL_INT;
		हाल IIO_PRESSURE:	/* in kPa */
			*val = pressure / 1000;
			*val2 = (pressure % 1000) * 1000;

			वापस IIO_VAL_INT_PLUS_MICRO;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*val = ms5637_samp_freq[dev_data->res_index];

		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ms5637_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा ms_tp_dev *dev_data = iio_priv(indio_dev);
	पूर्णांक i;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		i = ARRAY_SIZE(ms5637_samp_freq);
		जबतक (i-- > 0)
			अगर (val == ms5637_samp_freq[i])
				अवरोध;
		अगर (i < 0)
			वापस -EINVAL;
		dev_data->res_index = i;

		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec ms5637_channels[] = अणु
	अणु
		.type = IIO_TEMP,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ),
	पूर्ण,
	अणु
		.type = IIO_PRESSURE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ),
	पूर्ण
पूर्ण;

अटल IIO_DEV_ATTR_SAMP_FREQ_AVAIL(ms5637_show_samp_freq);

अटल काष्ठा attribute *ms5637_attributes[] = अणु
	&iio_dev_attr_sampling_frequency_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ms5637_attribute_group = अणु
	.attrs = ms5637_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info ms5637_info = अणु
	.पढ़ो_raw = ms5637_पढ़ो_raw,
	.ग_लिखो_raw = ms5637_ग_लिखो_raw,
	.attrs = &ms5637_attribute_group,
पूर्ण;

अटल पूर्णांक ms5637_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	स्थिर काष्ठा ms_tp_data *data;
	काष्ठा ms_tp_dev *dev_data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_READ_WORD_DATA |
				     I2C_FUNC_SMBUS_WRITE_BYTE |
				     I2C_FUNC_SMBUS_READ_I2C_BLOCK)) अणु
		dev_err(&client->dev,
			"Adapter does not support some i2c transaction\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (id)
		data = (स्थिर काष्ठा ms_tp_data *)id->driver_data;
	अन्यथा
		data = device_get_match_data(&client->dev);
	अगर (!data)
		वापस -EINVAL;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*dev_data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	dev_data = iio_priv(indio_dev);
	dev_data->client = client;
	dev_data->res_index = data->hw->max_res_index;
	dev_data->hw = data->hw;
	mutex_init(&dev_data->lock);

	indio_dev->info = &ms5637_info;
	indio_dev->name = data->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = ms5637_channels;
	indio_dev->num_channels = ARRAY_SIZE(ms5637_channels);

	i2c_set_clientdata(client, indio_dev);

	ret = ms_sensors_reset(client, 0x1E, 3000);
	अगर (ret)
		वापस ret;

	ret = ms_sensors_tp_पढ़ो_prom(dev_data);
	अगर (ret)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा ms_tp_hw_data ms5637_hw_data  = अणु
	.prom_len = 7,
	.max_res_index = 5
पूर्ण;

अटल स्थिर काष्ठा ms_tp_hw_data ms5803_hw_data  = अणु
	.prom_len = 8,
	.max_res_index = 4
पूर्ण;

अटल स्थिर काष्ठा ms_tp_data ms5637_data = अणु .name = "ms5637", .hw = &ms5637_hw_data पूर्ण;

अटल स्थिर काष्ठा ms_tp_data ms5803_data = अणु .name = "ms5803", .hw = &ms5803_hw_data पूर्ण;

अटल स्थिर काष्ठा ms_tp_data ms5805_data = अणु .name = "ms5805", .hw = &ms5637_hw_data पूर्ण;

अटल स्थिर काष्ठा ms_tp_data ms5837_data = अणु .name = "ms5837", .hw = &ms5637_hw_data पूर्ण;

अटल स्थिर काष्ठा ms_tp_data ms8607_data = अणु
	.name = "ms8607-temppressure",
	.hw = &ms5637_hw_data,
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id ms5637_id[] = अणु
	अणु"ms5637", (kernel_uदीर्घ_t)&ms5637_data पूर्ण,
	अणु"ms5805", (kernel_uदीर्घ_t)&ms5805_data पूर्ण,
	अणु"ms5837", (kernel_uदीर्घ_t)&ms5837_data पूर्ण,
	अणु"ms8607-temppressure", (kernel_uदीर्घ_t)&ms8607_data पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ms5637_id);

अटल स्थिर काष्ठा of_device_id ms5637_of_match[] = अणु
	अणु .compatible = "meas,ms5637", .data = &ms5637_data पूर्ण,
	अणु .compatible = "meas,ms5803", .data = &ms5803_data पूर्ण,
	अणु .compatible = "meas,ms5805", .data = &ms5805_data पूर्ण,
	अणु .compatible = "meas,ms5837", .data = &ms5837_data पूर्ण,
	अणु .compatible = "meas,ms8607-temppressure", .data = &ms8607_data पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ms5637_of_match);

अटल काष्ठा i2c_driver ms5637_driver = अणु
	.probe = ms5637_probe,
	.id_table = ms5637_id,
	.driver = अणु
		   .name = "ms5637",
		   .of_match_table = ms5637_of_match,
		   पूर्ण,
पूर्ण;

module_i2c_driver(ms5637_driver);

MODULE_DESCRIPTION("Measurement-Specialties ms5637 temperature & pressure driver");
MODULE_AUTHOR("William Markezana <william.markezana@meas-spec.com>");
MODULE_AUTHOR("Ludovic Tancerel <ludovic.tancerel@maplehightech.com>");
MODULE_LICENSE("GPL v2");
