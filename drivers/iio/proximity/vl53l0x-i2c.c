<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम ST VL53L0X FlightSense ToF Ranging Sensor on a i2c bus.
 *
 * Copyright (C) 2016 STMicroelectronics Imaging Division.
 * Copyright (C) 2018 Song Qiang <songqiang1304521@gmail.com>
 * Copyright (C) 2020 Ivan Drobyshevskyi <drobyshevskyi@gmail.com>
 *
 * Datasheet available at
 * <https://www.st.com/resource/en/datasheet/vl53l0x.pdf>
 *
 * Default 7-bit i2c slave address 0x29.
 *
 * TODO: FIFO buffer, continuous mode, range selection, sensor ID check.
 */

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>

#समावेश <linux/iio/iपन.स>

#घोषणा VL_REG_SYSRANGE_START				0x00

#घोषणा VL_REG_SYSRANGE_MODE_MASK			GENMASK(3, 0)
#घोषणा VL_REG_SYSRANGE_MODE_SINGLESHOT			0x00
#घोषणा VL_REG_SYSRANGE_MODE_START_STOP			BIT(0)
#घोषणा VL_REG_SYSRANGE_MODE_BACKTOBACK			BIT(1)
#घोषणा VL_REG_SYSRANGE_MODE_TIMED			BIT(2)
#घोषणा VL_REG_SYSRANGE_MODE_HISTOGRAM			BIT(3)

#घोषणा VL_REG_SYSTEM_INTERRUPT_CONFIG_GPIO		0x0A
#घोषणा VL_REG_SYSTEM_INTERRUPT_GPIO_NEW_SAMPLE_READY	BIT(2)

#घोषणा VL_REG_SYSTEM_INTERRUPT_CLEAR			0x0B

#घोषणा VL_REG_RESULT_INT_STATUS			0x13
#घोषणा VL_REG_RESULT_RANGE_STATUS			0x14
#घोषणा VL_REG_RESULT_RANGE_STATUS_COMPLETE		BIT(0)

काष्ठा vl53l0x_data अणु
	काष्ठा i2c_client *client;
	काष्ठा completion completion;
पूर्ण;

अटल irqवापस_t vl53l0x_handle_irq(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा iio_dev *indio_dev = priv;
	काष्ठा vl53l0x_data *data = iio_priv(indio_dev);

	complete(&data->completion);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक vl53l0x_configure_irq(काष्ठा i2c_client *client,
				 काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा vl53l0x_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = devm_request_irq(&client->dev, client->irq, vl53l0x_handle_irq,
			IRQF_TRIGGER_FALLING, indio_dev->name, indio_dev);
	अगर (ret) अणु
		dev_err(&client->dev, "devm_request_irq error: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = i2c_smbus_ग_लिखो_byte_data(data->client,
			VL_REG_SYSTEM_INTERRUPT_CONFIG_GPIO,
			VL_REG_SYSTEM_INTERRUPT_GPIO_NEW_SAMPLE_READY);
	अगर (ret < 0)
		dev_err(&client->dev, "failed to configure IRQ: %d\n", ret);

	वापस ret;
पूर्ण

अटल व्योम vl53l0x_clear_irq(काष्ठा vl53l0x_data *data)
अणु
	काष्ठा device *dev = &data->client->dev;
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client,
					VL_REG_SYSTEM_INTERRUPT_CLEAR, 1);
	अगर (ret < 0)
		dev_err(dev, "failed to clear error irq: %d\n", ret);

	ret = i2c_smbus_ग_लिखो_byte_data(data->client,
					VL_REG_SYSTEM_INTERRUPT_CLEAR, 0);
	अगर (ret < 0)
		dev_err(dev, "failed to clear range irq: %d\n", ret);

	ret = i2c_smbus_पढ़ो_byte_data(data->client, VL_REG_RESULT_INT_STATUS);
	अगर (ret < 0 || ret & 0x07)
		dev_err(dev, "failed to clear irq: %d\n", ret);
पूर्ण

अटल पूर्णांक vl53l0x_पढ़ो_proximity(काष्ठा vl53l0x_data *data,
				  स्थिर काष्ठा iio_chan_spec *chan,
				  पूर्णांक *val)
अणु
	काष्ठा i2c_client *client = data->client;
	u16 tries = 20;
	u8 buffer[12];
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(client, VL_REG_SYSRANGE_START, 1);
	अगर (ret < 0)
		वापस ret;

	अगर (data->client->irq) अणु
		reinit_completion(&data->completion);

		ret = रुको_क्रम_completion_समयout(&data->completion, HZ/10);
		अगर (ret < 0)
			वापस ret;
		अन्यथा अगर (ret == 0)
			वापस -ETIMEDOUT;

		vl53l0x_clear_irq(data);
	पूर्ण अन्यथा अणु
		करो अणु
			ret = i2c_smbus_पढ़ो_byte_data(client,
					       VL_REG_RESULT_RANGE_STATUS);
			अगर (ret < 0)
				वापस ret;

			अगर (ret & VL_REG_RESULT_RANGE_STATUS_COMPLETE)
				अवरोध;

			usleep_range(1000, 5000);
		पूर्ण जबतक (--tries);
		अगर (!tries)
			वापस -ETIMEDOUT;
	पूर्ण

	ret = i2c_smbus_पढ़ो_i2c_block_data(client, VL_REG_RESULT_RANGE_STATUS,
					    12, buffer);
	अगर (ret < 0)
		वापस ret;
	अन्यथा अगर (ret != 12)
		वापस -EREMOTEIO;

	/* Values should be between 30~1200 in millimeters. */
	*val = (buffer[10] << 8) + buffer[11];

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec vl53l0x_channels[] = अणु
	अणु
		.type = IIO_DISTANCE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE),
	पूर्ण,
पूर्ण;

अटल पूर्णांक vl53l0x_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    स्थिर काष्ठा iio_chan_spec *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा vl53l0x_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	अगर (chan->type != IIO_DISTANCE)
		वापस -EINVAL;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = vl53l0x_पढ़ो_proximity(data, chan, val);
		अगर (ret < 0)
			वापस ret;

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = 0;
		*val2 = 1000;

		वापस IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info vl53l0x_info = अणु
	.पढ़ो_raw = vl53l0x_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक vl53l0x_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा vl53l0x_data *data;
	काष्ठा iio_dev *indio_dev;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	data->client = client;
	i2c_set_clientdata(client, indio_dev);

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_READ_I2C_BLOCK |
				     I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EOPNOTSUPP;

	indio_dev->name = "vl53l0x";
	indio_dev->info = &vl53l0x_info;
	indio_dev->channels = vl53l0x_channels;
	indio_dev->num_channels = ARRAY_SIZE(vl53l0x_channels);
	indio_dev->modes = INDIO_सूचीECT_MODE;

	/* usage of पूर्णांकerrupt is optional */
	अगर (client->irq) अणु
		पूर्णांक ret;

		init_completion(&data->completion);

		ret = vl53l0x_configure_irq(client, indio_dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id vl53l0x_id[] = अणु
	अणु "vl53l0x", 0पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, vl53l0x_id);

अटल स्थिर काष्ठा of_device_id st_vl53l0x_dt_match[] = अणु
	अणु .compatible = "st,vl53l0x", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, st_vl53l0x_dt_match);

अटल काष्ठा i2c_driver vl53l0x_driver = अणु
	.driver = अणु
		.name = "vl53l0x-i2c",
		.of_match_table = st_vl53l0x_dt_match,
	पूर्ण,
	.probe_new = vl53l0x_probe,
	.id_table = vl53l0x_id,
पूर्ण;
module_i2c_driver(vl53l0x_driver);

MODULE_AUTHOR("Song Qiang <songqiang1304521@gmail.com>");
MODULE_DESCRIPTION("ST vl53l0x ToF ranging sensor driver");
MODULE_LICENSE("GPL v2");
