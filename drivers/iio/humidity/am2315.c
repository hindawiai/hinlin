<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Aosong AM2315 relative humidity and temperature
 *
 * Copyright (c) 2016, Intel Corporation.
 *
 * 7-bit I2C address: 0x5C.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>

#घोषणा AM2315_REG_HUM_MSB			0x00
#घोषणा AM2315_REG_HUM_LSB			0x01
#घोषणा AM2315_REG_TEMP_MSB			0x02
#घोषणा AM2315_REG_TEMP_LSB			0x03

#घोषणा AM2315_FUNCTION_READ			0x03
#घोषणा AM2315_HUM_OFFSET			2
#घोषणा AM2315_TEMP_OFFSET			4
#घोषणा AM2315_ALL_CHANNEL_MASK			GENMASK(1, 0)

#घोषणा AM2315_DRIVER_NAME			"am2315"

काष्ठा am2315_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;
	s16 buffer[8]; /* 2x16-bit channels + 2x16 padding + 4x16 बारtamp */
पूर्ण;

काष्ठा am2315_sensor_data अणु
	s16 hum_data;
	s16 temp_data;
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec am2315_channels[] = अणु
	अणु
		.type = IIO_HUMIDITYRELATIVE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE),
		.scan_index = 0,
		.scan_type = अणु
			.sign = 's',
			.realbits = 16,
			.storagebits = 16,
			.endianness = IIO_CPU,
		पूर्ण,
	पूर्ण,
	अणु
		.type = IIO_TEMP,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE),
		.scan_index = 1,
		.scan_type = अणु
			.sign = 's',
			.realbits = 16,
			.storagebits = 16,
			.endianness = IIO_CPU,
		पूर्ण,
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(2),
पूर्ण;

/* CRC calculation algorithm, as specअगरied in the datasheet (page 13). */
अटल u16 am2315_crc(u8 *data, u8 nr_bytes)
अणु
	पूर्णांक i;
	u16 crc = 0xffff;

	जबतक (nr_bytes--) अणु
		crc ^= *data++;
		क्रम (i = 0; i < 8; i++) अणु
			अगर (crc & 0x01) अणु
				crc >>= 1;
				crc ^= 0xA001;
			पूर्ण अन्यथा अणु
				crc >>= 1;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस crc;
पूर्ण

/* Simple function that sends a few bytes to the device to wake it up. */
अटल व्योम am2315_ping(काष्ठा i2c_client *client)
अणु
	i2c_smbus_पढ़ो_byte_data(client, AM2315_REG_HUM_MSB);
पूर्ण

अटल पूर्णांक am2315_पढ़ो_data(काष्ठा am2315_data *data,
			    काष्ठा am2315_sensor_data *sensor_data)
अणु
	पूर्णांक ret;
	/* tx_buf क्रमmat: <function code> <start addr> <nr of regs to पढ़ो> */
	u8 tx_buf[3] = अणु AM2315_FUNCTION_READ, AM2315_REG_HUM_MSB, 4 पूर्ण;
	/*
	 * rx_buf क्रमmat:
	 * <function code> <number of रेजिस्टरs पढ़ो>
	 * <humidity MSB> <humidity LSB> <temp MSB> <temp LSB>
	 * <CRC LSB> <CRC MSB>
	 */
	u8 rx_buf[8];
	u16 crc;

	/* First wake up the device. */
	am2315_ping(data->client);

	mutex_lock(&data->lock);
	ret = i2c_master_send(data->client, tx_buf, माप(tx_buf));
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "failed to send read request\n");
		जाओ निकास_unlock;
	पूर्ण
	/* Wait 2-3 ms, then पढ़ो back the data sent by the device. */
	usleep_range(2000, 3000);
	/* Do a bulk data पढ़ो, then pick out what we need. */
	ret = i2c_master_recv(data->client, rx_buf, माप(rx_buf));
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "failed to read sensor data\n");
		जाओ निकास_unlock;
	पूर्ण
	mutex_unlock(&data->lock);
	/*
	 * Do a CRC check on the data and compare it to the value
	 * calculated by the device.
	 */
	crc = am2315_crc(rx_buf, माप(rx_buf) - 2);
	अगर ((crc & 0xff) != rx_buf[6] || (crc >> 8) != rx_buf[7]) अणु
		dev_err(&data->client->dev, "failed to verify sensor data\n");
		वापस -EIO;
	पूर्ण

	sensor_data->hum_data = (rx_buf[AM2315_HUM_OFFSET] << 8) |
				 rx_buf[AM2315_HUM_OFFSET + 1];
	sensor_data->temp_data = (rx_buf[AM2315_TEMP_OFFSET] << 8) |
				  rx_buf[AM2315_TEMP_OFFSET + 1];

	वापस ret;

निकास_unlock:
	mutex_unlock(&data->lock);
	वापस ret;
पूर्ण

अटल irqवापस_t am2315_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	पूर्णांक i;
	पूर्णांक ret;
	पूर्णांक bit;
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा am2315_data *data = iio_priv(indio_dev);
	काष्ठा am2315_sensor_data sensor_data;

	ret = am2315_पढ़ो_data(data, &sensor_data);
	अगर (ret < 0)
		जाओ err;

	mutex_lock(&data->lock);
	अगर (*(indio_dev->active_scan_mask) == AM2315_ALL_CHANNEL_MASK) अणु
		data->buffer[0] = sensor_data.hum_data;
		data->buffer[1] = sensor_data.temp_data;
	पूर्ण अन्यथा अणु
		i = 0;
		क्रम_each_set_bit(bit, indio_dev->active_scan_mask,
				 indio_dev->masklength) अणु
			data->buffer[i] = (bit ? sensor_data.temp_data :
						 sensor_data.hum_data);
			i++;
		पूर्ण
	पूर्ण
	mutex_unlock(&data->lock);

	iio_push_to_buffers_with_बारtamp(indio_dev, data->buffer,
					   pf->बारtamp);
err:
	iio_trigger_notअगरy_करोne(indio_dev->trig);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक am2315_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक ret;
	काष्ठा am2315_sensor_data sensor_data;
	काष्ठा am2315_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = am2315_पढ़ो_data(data, &sensor_data);
		अगर (ret < 0)
			वापस ret;
		*val = (chan->type == IIO_HUMIDITYRELATIVE) ?
				sensor_data.hum_data : sensor_data.temp_data;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = 100;
		वापस IIO_VAL_INT;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info am2315_info = अणु
	.पढ़ो_raw		= am2315_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक am2315_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा iio_dev *indio_dev;
	काष्ठा am2315_data *data;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev) अणु
		dev_err(&client->dev, "iio allocation failed!\n");
		वापस -ENOMEM;
	पूर्ण

	data = iio_priv(indio_dev);
	data->client = client;
	i2c_set_clientdata(client, indio_dev);
	mutex_init(&data->lock);

	indio_dev->info = &am2315_info;
	indio_dev->name = AM2315_DRIVER_NAME;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = am2315_channels;
	indio_dev->num_channels = ARRAY_SIZE(am2315_channels);

	ret = devm_iio_triggered_buffer_setup(&client->dev,
					indio_dev, iio_pollfunc_store_समय,
					 am2315_trigger_handler, शून्य);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "iio triggered buffer setup failed\n");
		वापस ret;
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id am2315_i2c_id[] = अणु
	अणु"am2315", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, am2315_i2c_id);

अटल स्थिर काष्ठा acpi_device_id am2315_acpi_id[] = अणु
	अणु"AOS2315", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(acpi, am2315_acpi_id);

अटल काष्ठा i2c_driver am2315_driver = अणु
	.driver = अणु
		.name = "am2315",
		.acpi_match_table = ACPI_PTR(am2315_acpi_id),
	पूर्ण,
	.probe =            am2315_probe,
	.id_table =         am2315_i2c_id,
पूर्ण;

module_i2c_driver(am2315_driver);

MODULE_AUTHOR("Tiberiu Breana <tiberiu.a.breana@intel.com>");
MODULE_DESCRIPTION("Aosong AM2315 relative humidity and temperature");
MODULE_LICENSE("GPL v2");
