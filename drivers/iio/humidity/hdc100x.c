<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * hdc100x.c - Support क्रम the TI HDC100x temperature + humidity sensors
 *
 * Copyright (C) 2015, 2018
 * Author: Matt Ranostay <matt.ranostay@konsulko.com>
 *
 * Datasheets:
 * https://www.ti.com/product/HDC1000/datasheet
 * https://www.ti.com/product/HDC1008/datasheet
 * https://www.ti.com/product/HDC1010/datasheet
 * https://www.ti.com/product/HDC1050/datasheet
 * https://www.ti.com/product/HDC1080/datasheet
 */

#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>

#घोषणा HDC100X_REG_TEMP			0x00
#घोषणा HDC100X_REG_HUMIDITY			0x01

#घोषणा HDC100X_REG_CONFIG			0x02
#घोषणा HDC100X_REG_CONFIG_ACQ_MODE		BIT(12)
#घोषणा HDC100X_REG_CONFIG_HEATER_EN		BIT(13)

काष्ठा hdc100x_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;
	u16 config;

	/* पूर्णांकegration समय of the sensor */
	पूर्णांक adc_पूर्णांक_us[2];
	/* Ensure natural alignment of बारtamp */
	काष्ठा अणु
		__be16 channels[2];
		s64 ts __aligned(8);
	पूर्ण scan;
पूर्ण;

/* पूर्णांकegration समय in us */
अटल स्थिर पूर्णांक hdc100x_पूर्णांक_समय[][3] = अणु
	अणु 6350, 3650, 0 पूर्ण,	/* IIO_TEMP channel*/
	अणु 6500, 3850, 2500 पूर्ण,	/* IIO_HUMIDITYRELATIVE channel */
पूर्ण;

/* HDC100X_REG_CONFIG shअगरt and mask values */
अटल स्थिर काष्ठा अणु
	पूर्णांक shअगरt;
	पूर्णांक mask;
पूर्ण hdc100x_resolution_shअगरt[2] = अणु
	अणु /* IIO_TEMP channel */
		.shअगरt = 10,
		.mask = 1
	पूर्ण,
	अणु /* IIO_HUMIDITYRELATIVE channel */
		.shअगरt = 8,
		.mask = 3,
	पूर्ण,
पूर्ण;

अटल IIO_CONST_ATTR(temp_पूर्णांकegration_समय_available,
		"0.00365 0.00635");

अटल IIO_CONST_ATTR(humidityrelative_पूर्णांकegration_समय_available,
		"0.0025 0.00385 0.0065");

अटल IIO_CONST_ATTR(out_current_heater_raw_available,
		"0 1");

अटल काष्ठा attribute *hdc100x_attributes[] = अणु
	&iio_स्थिर_attr_temp_पूर्णांकegration_समय_available.dev_attr.attr,
	&iio_स्थिर_attr_humidityrelative_पूर्णांकegration_समय_available.dev_attr.attr,
	&iio_स्थिर_attr_out_current_heater_raw_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group hdc100x_attribute_group = अणु
	.attrs = hdc100x_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec hdc100x_channels[] = अणु
	अणु
		.type = IIO_TEMP,
		.address = HDC100X_REG_TEMP,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SCALE) |
			BIT(IIO_CHAN_INFO_INT_TIME) |
			BIT(IIO_CHAN_INFO_OFFSET),
		.scan_index = 0,
		.scan_type = अणु
			.sign = 's',
			.realbits = 16,
			.storagebits = 16,
			.endianness = IIO_BE,
		पूर्ण,
	पूर्ण,
	अणु
		.type = IIO_HUMIDITYRELATIVE,
		.address = HDC100X_REG_HUMIDITY,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SCALE) |
			BIT(IIO_CHAN_INFO_INT_TIME),
		.scan_index = 1,
		.scan_type = अणु
			.sign = 'u',
			.realbits = 16,
			.storagebits = 16,
			.endianness = IIO_BE,
		पूर्ण,
	पूर्ण,
	अणु
		.type = IIO_CURRENT,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.extend_name = "heater",
		.output = 1,
		.scan_index = -1,
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(2),
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ hdc100x_scan_masks[] = अणु0x3, 0पूर्ण;

अटल पूर्णांक hdc100x_update_config(काष्ठा hdc100x_data *data, पूर्णांक mask, पूर्णांक val)
अणु
	पूर्णांक पंचांगp = (~mask & data->config) | val;
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_word_swapped(data->client,
						HDC100X_REG_CONFIG, पंचांगp);
	अगर (!ret)
		data->config = पंचांगp;

	वापस ret;
पूर्ण

अटल पूर्णांक hdc100x_set_it_समय(काष्ठा hdc100x_data *data, पूर्णांक chan, पूर्णांक val2)
अणु
	पूर्णांक shअगरt = hdc100x_resolution_shअगरt[chan].shअगरt;
	पूर्णांक ret = -EINVAL;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(hdc100x_पूर्णांक_समय[chan]); i++) अणु
		अगर (val2 && val2 == hdc100x_पूर्णांक_समय[chan][i]) अणु
			ret = hdc100x_update_config(data,
				hdc100x_resolution_shअगरt[chan].mask << shअगरt,
				i << shअगरt);
			अगर (!ret)
				data->adc_पूर्णांक_us[chan] = val2;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hdc100x_get_measurement(काष्ठा hdc100x_data *data,
				   काष्ठा iio_chan_spec स्थिर *chan)
अणु
	काष्ठा i2c_client *client = data->client;
	पूर्णांक delay = data->adc_पूर्णांक_us[chan->address];
	पूर्णांक ret;
	__be16 val;

	/* start measurement */
	ret = i2c_smbus_ग_लिखो_byte(client, chan->address);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "cannot start measurement");
		वापस ret;
	पूर्ण

	/* रुको क्रम पूर्णांकegration समय to pass */
	usleep_range(delay, delay + 1000);

	/* पढ़ो measurement */
	ret = i2c_master_recv(data->client, (अक्षर *)&val, माप(val));
	अगर (ret < 0) अणु
		dev_err(&client->dev, "cannot read sensor data\n");
		वापस ret;
	पूर्ण
	वापस be16_to_cpu(val);
पूर्ण

अटल पूर्णांक hdc100x_get_heater_status(काष्ठा hdc100x_data *data)
अणु
	वापस !!(data->config & HDC100X_REG_CONFIG_HEATER_EN);
पूर्ण

अटल पूर्णांक hdc100x_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
			    पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा hdc100x_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW: अणु
		पूर्णांक ret;

		mutex_lock(&data->lock);
		अगर (chan->type == IIO_CURRENT) अणु
			*val = hdc100x_get_heater_status(data);
			ret = IIO_VAL_INT;
		पूर्ण अन्यथा अणु
			ret = iio_device_claim_direct_mode(indio_dev);
			अगर (ret) अणु
				mutex_unlock(&data->lock);
				वापस ret;
			पूर्ण

			ret = hdc100x_get_measurement(data, chan);
			iio_device_release_direct_mode(indio_dev);
			अगर (ret >= 0) अणु
				*val = ret;
				ret = IIO_VAL_INT;
			पूर्ण
		पूर्ण
		mutex_unlock(&data->lock);
		वापस ret;
	पूर्ण
	हाल IIO_CHAN_INFO_INT_TIME:
		*val = 0;
		*val2 = data->adc_पूर्णांक_us[chan->address];
		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_SCALE:
		अगर (chan->type == IIO_TEMP) अणु
			*val = 165000;
			*val2 = 65536;
			वापस IIO_VAL_FRACTIONAL;
		पूर्ण अन्यथा अणु
			*val = 100000;
			*val2 = 65536;
			वापस IIO_VAL_FRACTIONAL;
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_OFFSET:
		*val = -15887;
		*val2 = 515151;
		वापस IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक hdc100x_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा hdc100x_data *data = iio_priv(indio_dev);
	पूर्णांक ret = -EINVAL;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_INT_TIME:
		अगर (val != 0)
			वापस -EINVAL;

		mutex_lock(&data->lock);
		ret = hdc100x_set_it_समय(data, chan->address, val2);
		mutex_unlock(&data->lock);
		वापस ret;
	हाल IIO_CHAN_INFO_RAW:
		अगर (chan->type != IIO_CURRENT || val2 != 0)
			वापस -EINVAL;

		mutex_lock(&data->lock);
		ret = hdc100x_update_config(data, HDC100X_REG_CONFIG_HEATER_EN,
					val ? HDC100X_REG_CONFIG_HEATER_EN : 0);
		mutex_unlock(&data->lock);
		वापस ret;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक hdc100x_buffer_postenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा hdc100x_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	/* Buffer is enabled. First set ACQ Mode, then attach poll func */
	mutex_lock(&data->lock);
	ret = hdc100x_update_config(data, HDC100X_REG_CONFIG_ACQ_MODE,
				    HDC100X_REG_CONFIG_ACQ_MODE);
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक hdc100x_buffer_predisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा hdc100x_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->lock);
	ret = hdc100x_update_config(data, HDC100X_REG_CONFIG_ACQ_MODE, 0);
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops hdc_buffer_setup_ops = अणु
	.postenable  = hdc100x_buffer_postenable,
	.predisable  = hdc100x_buffer_predisable,
पूर्ण;

अटल irqवापस_t hdc100x_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा hdc100x_data *data = iio_priv(indio_dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक delay = data->adc_पूर्णांक_us[0] + data->adc_पूर्णांक_us[1];
	पूर्णांक ret;

	/* dual पढ़ो starts at temp रेजिस्टर */
	mutex_lock(&data->lock);
	ret = i2c_smbus_ग_लिखो_byte(client, HDC100X_REG_TEMP);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "cannot start measurement\n");
		जाओ err;
	पूर्ण
	usleep_range(delay, delay + 1000);

	ret = i2c_master_recv(client, (u8 *)data->scan.channels, 4);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "cannot read sensor data\n");
		जाओ err;
	पूर्ण

	iio_push_to_buffers_with_बारtamp(indio_dev, &data->scan,
					   iio_get_समय_ns(indio_dev));
err:
	mutex_unlock(&data->lock);
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा iio_info hdc100x_info = अणु
	.पढ़ो_raw = hdc100x_पढ़ो_raw,
	.ग_लिखो_raw = hdc100x_ग_लिखो_raw,
	.attrs = &hdc100x_attribute_group,
पूर्ण;

अटल पूर्णांक hdc100x_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा hdc100x_data *data;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_WORD_DATA |
				     I2C_FUNC_SMBUS_BYTE | I2C_FUNC_I2C))
		वापस -EOPNOTSUPP;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	mutex_init(&data->lock);

	indio_dev->name = dev_name(&client->dev);
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &hdc100x_info;

	indio_dev->channels = hdc100x_channels;
	indio_dev->num_channels = ARRAY_SIZE(hdc100x_channels);
	indio_dev->available_scan_masks = hdc100x_scan_masks;

	/* be sure we are in a known state */
	hdc100x_set_it_समय(data, 0, hdc100x_पूर्णांक_समय[0][0]);
	hdc100x_set_it_समय(data, 1, hdc100x_पूर्णांक_समय[1][0]);
	hdc100x_update_config(data, HDC100X_REG_CONFIG_ACQ_MODE, 0);

	ret = devm_iio_triggered_buffer_setup(&client->dev,
					 indio_dev, शून्य,
					 hdc100x_trigger_handler,
					 &hdc_buffer_setup_ops);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "iio triggered buffer setup failed\n");
		वापस ret;
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id hdc100x_id[] = अणु
	अणु "hdc100x", 0 पूर्ण,
	अणु "hdc1000", 0 पूर्ण,
	अणु "hdc1008", 0 पूर्ण,
	अणु "hdc1010", 0 पूर्ण,
	अणु "hdc1050", 0 पूर्ण,
	अणु "hdc1080", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, hdc100x_id);

अटल स्थिर काष्ठा of_device_id hdc100x_dt_ids[] = अणु
	अणु .compatible = "ti,hdc1000" पूर्ण,
	अणु .compatible = "ti,hdc1008" पूर्ण,
	अणु .compatible = "ti,hdc1010" पूर्ण,
	अणु .compatible = "ti,hdc1050" पूर्ण,
	अणु .compatible = "ti,hdc1080" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, hdc100x_dt_ids);

अटल काष्ठा i2c_driver hdc100x_driver = अणु
	.driver = अणु
		.name	= "hdc100x",
		.of_match_table = hdc100x_dt_ids,
	पूर्ण,
	.probe = hdc100x_probe,
	.id_table = hdc100x_id,
पूर्ण;
module_i2c_driver(hdc100x_driver);

MODULE_AUTHOR("Matt Ranostay <matt.ranostay@konsulko.com>");
MODULE_DESCRIPTION("TI HDC100x humidity and temperature sensor driver");
MODULE_LICENSE("GPL");
