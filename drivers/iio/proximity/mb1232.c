<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * mb1232.c - Support क्रम MaxBotix I2CXL-MaxSonar-EZ series ultrasonic
 *   ranger with i2c पूर्णांकerface
 * actually tested with mb1232 type
 *
 * Copyright (c) 2019 Andreas Klinger <ak@it-klinger.de>
 *
 * For details about the device see:
 * https://www.maxbotix.com/करोcuments/I2CXL-MaxSonar-EZ_Datasheet.pdf
 */

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/bitops.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>

/* रेजिस्टरs of MaxSonar device */
#घोषणा MB1232_RANGE_COMMAND	0x51	/* Command क्रम पढ़ोing range */
#घोषणा MB1232_ADDR_UNLOCK_1	0xAA	/* Command 1 क्रम changing address */
#घोषणा MB1232_ADDR_UNLOCK_2	0xA5	/* Command 2 क्रम changing address */

काष्ठा mb1232_data अणु
	काष्ठा i2c_client	*client;

	काष्ठा mutex		lock;

	/*
	 * optionally a gpio can be used to announce when ranging has
	 * finished
	 * since we are just using the falling trigger of it we request
	 * only the पूर्णांकerrupt क्रम announcing when data is पढ़ोy to be पढ़ो
	 */
	काष्ठा completion	ranging;
	पूर्णांक			irqnr;
	/* Ensure correct alignment of data to push to IIO buffer */
	काष्ठा अणु
		s16 distance;
		s64 ts __aligned(8);
	पूर्ण scan;
पूर्ण;

अटल irqवापस_t mb1232_handle_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा iio_dev *indio_dev = dev_id;
	काष्ठा mb1232_data *data = iio_priv(indio_dev);

	complete(&data->ranging);

	वापस IRQ_HANDLED;
पूर्ण

अटल s16 mb1232_पढ़ो_distance(काष्ठा mb1232_data *data)
अणु
	काष्ठा i2c_client *client = data->client;
	पूर्णांक ret;
	s16 distance;
	__be16 buf;

	mutex_lock(&data->lock);

	reinit_completion(&data->ranging);

	ret = i2c_smbus_ग_लिखो_byte(client, MB1232_RANGE_COMMAND);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "write command - err: %d\n", ret);
		जाओ error_unlock;
	पूर्ण

	अगर (data->irqnr >= 0) अणु
		/* it cannot take more than 100 ms */
		ret = रुको_क्रम_completion_समाप्तable_समयout(&data->ranging,
									HZ/10);
		अगर (ret < 0)
			जाओ error_unlock;
		अन्यथा अगर (ret == 0) अणु
			ret = -ETIMEDOUT;
			जाओ error_unlock;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* use simple sleep अगर announce irq is not connected */
		msleep(15);
	पूर्ण

	ret = i2c_master_recv(client, (अक्षर *)&buf, माप(buf));
	अगर (ret < 0) अणु
		dev_err(&client->dev, "i2c_master_recv: ret=%d\n", ret);
		जाओ error_unlock;
	पूर्ण

	distance = __be16_to_cpu(buf);
	/* check क्रम not वापसing misleading error codes */
	अगर (distance < 0) अणु
		dev_err(&client->dev, "distance=%d\n", distance);
		ret = -EINVAL;
		जाओ error_unlock;
	पूर्ण

	mutex_unlock(&data->lock);

	वापस distance;

error_unlock:
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल irqवापस_t mb1232_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा mb1232_data *data = iio_priv(indio_dev);

	data->scan.distance = mb1232_पढ़ो_distance(data);
	अगर (data->scan.distance < 0)
		जाओ err;

	iio_push_to_buffers_with_बारtamp(indio_dev, &data->scan,
					   pf->बारtamp);

err:
	iio_trigger_notअगरy_करोne(indio_dev->trig);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mb1232_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *channel, पूर्णांक *val,
			    पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा mb1232_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	अगर (channel->type != IIO_DISTANCE)
		वापस -EINVAL;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = mb1232_पढ़ो_distance(data);
		अगर (ret < 0)
			वापस ret;
		*val = ret;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		/* 1 LSB is 1 cm */
		*val = 0;
		*val2 = 10000;
		वापस IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec mb1232_channels[] = अणु
	अणु
		.type = IIO_DISTANCE,
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
	IIO_CHAN_SOFT_TIMESTAMP(1),
पूर्ण;

अटल स्थिर काष्ठा iio_info mb1232_info = अणु
	.पढ़ो_raw = mb1232_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक mb1232_probe(काष्ठा i2c_client *client,
					 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा mb1232_data *data;
	पूर्णांक ret;
	काष्ठा device *dev = &client->dev;

	अगर (!i2c_check_functionality(client->adapter,
					I2C_FUNC_SMBUS_READ_BYTE |
					I2C_FUNC_SMBUS_WRITE_BYTE))
		वापस -ENODEV;

	indio_dev = devm_iio_device_alloc(dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;

	indio_dev->info = &mb1232_info;
	indio_dev->name = id->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = mb1232_channels;
	indio_dev->num_channels = ARRAY_SIZE(mb1232_channels);

	mutex_init(&data->lock);

	init_completion(&data->ranging);

	data->irqnr = irq_of_parse_and_map(dev->of_node, 0);
	अगर (data->irqnr <= 0) अणु
		/* usage of पूर्णांकerrupt is optional */
		data->irqnr = -1;
	पूर्ण अन्यथा अणु
		ret = devm_request_irq(dev, data->irqnr, mb1232_handle_irq,
				IRQF_TRIGGER_FALLING, id->name, indio_dev);
		अगर (ret < 0) अणु
			dev_err(dev, "request_irq: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = devm_iio_triggered_buffer_setup(dev, indio_dev,
			iio_pollfunc_store_समय, mb1232_trigger_handler, शून्य);
	अगर (ret < 0) अणु
		dev_err(dev, "setup of iio triggered buffer failed\n");
		वापस ret;
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id of_mb1232_match[] = अणु
	अणु .compatible = "maxbotix,mb1202", पूर्ण,
	अणु .compatible = "maxbotix,mb1212", पूर्ण,
	अणु .compatible = "maxbotix,mb1222", पूर्ण,
	अणु .compatible = "maxbotix,mb1232", पूर्ण,
	अणु .compatible = "maxbotix,mb1242", पूर्ण,
	अणु .compatible = "maxbotix,mb7040", पूर्ण,
	अणु .compatible = "maxbotix,mb7137", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, of_mb1232_match);

अटल स्थिर काष्ठा i2c_device_id mb1232_id[] = अणु
	अणु "maxbotix-mb1202", पूर्ण,
	अणु "maxbotix-mb1212", पूर्ण,
	अणु "maxbotix-mb1222", पूर्ण,
	अणु "maxbotix-mb1232", पूर्ण,
	अणु "maxbotix-mb1242", पूर्ण,
	अणु "maxbotix-mb7040", पूर्ण,
	अणु "maxbotix-mb7137", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mb1232_id);

अटल काष्ठा i2c_driver mb1232_driver = अणु
	.driver = अणु
		.name	= "maxbotix-mb1232",
		.of_match_table	= of_mb1232_match,
	पूर्ण,
	.probe = mb1232_probe,
	.id_table = mb1232_id,
पूर्ण;
module_i2c_driver(mb1232_driver);

MODULE_AUTHOR("Andreas Klinger <ak@it-klinger.de>");
MODULE_DESCRIPTION("Maxbotix I2CXL-MaxSonar i2c ultrasonic ranger driver");
MODULE_LICENSE("GPL");
