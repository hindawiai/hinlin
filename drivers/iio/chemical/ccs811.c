<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ccs811.c - Support क्रम AMS CCS811 VOC Sensor
 *
 * Copyright (C) 2017 Narcisa Vasile <narcisaanamaria12@gmail.com>
 *
 * Datasheet: ams.com/content/करोwnload/951091/2269479/CCS811_DS000459_3-00.pdf
 *
 * IIO driver क्रम AMS CCS811 (I2C address 0x5A/0x5B set by ADDR Low/High)
 *
 * TODO:
 * 1. Make the drive mode selectable क्रमm userspace
 * 2. Add support क्रम पूर्णांकerrupts
 * 3. Adjust समय to रुको क्रम data to be पढ़ोy based on selected operation mode
 * 4. Read error रेजिस्टर and put the inक्रमmation in logs
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/module.h>

#घोषणा CCS811_STATUS		0x00
#घोषणा CCS811_MEAS_MODE	0x01
#घोषणा CCS811_ALG_RESULT_DATA	0x02
#घोषणा CCS811_RAW_DATA		0x03
#घोषणा CCS811_HW_ID		0x20
#घोषणा CCS811_HW_ID_VALUE	0x81
#घोषणा CCS811_HW_VERSION	0x21
#घोषणा CCS811_HW_VERSION_VALUE	0x10
#घोषणा CCS811_HW_VERSION_MASK	0xF0
#घोषणा CCS811_ERR		0xE0
/* Used to transition from boot to application mode */
#घोषणा CCS811_APP_START	0xF4
#घोषणा CCS811_SW_RESET		0xFF

/* Status रेजिस्टर flags */
#घोषणा CCS811_STATUS_ERROR		BIT(0)
#घोषणा CCS811_STATUS_DATA_READY	BIT(3)
#घोषणा CCS811_STATUS_APP_VALID_MASK	BIT(4)
#घोषणा CCS811_STATUS_APP_VALID_LOADED	BIT(4)
/*
 * Value of FW_MODE bit of STATUS रेजिस्टर describes the sensor's state:
 * 0: Firmware is in boot mode, this allows new firmware to be loaded
 * 1: Firmware is in application mode. CCS811 is पढ़ोy to take ADC measurements
 */
#घोषणा CCS811_STATUS_FW_MODE_MASK	BIT(7)
#घोषणा CCS811_STATUS_FW_MODE_APPLICATION	BIT(7)

/* Measurement modes */
#घोषणा CCS811_MODE_IDLE	0x00
#घोषणा CCS811_MODE_IAQ_1SEC	0x10
#घोषणा CCS811_MODE_IAQ_10SEC	0x20
#घोषणा CCS811_MODE_IAQ_60SEC	0x30
#घोषणा CCS811_MODE_RAW_DATA	0x40

#घोषणा CCS811_MEAS_MODE_INTERRUPT	BIT(3)

#घोषणा CCS811_VOLTAGE_MASK	0x3FF

काष्ठा ccs811_पढ़ोing अणु
	__be16 co2;
	__be16 voc;
	u8 status;
	u8 error;
	__be16 raw_data;
पूर्ण __attribute__((__packed__));

काष्ठा ccs811_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock; /* Protect पढ़ोings */
	काष्ठा ccs811_पढ़ोing buffer;
	काष्ठा iio_trigger *drdy_trig;
	काष्ठा gpio_desc *wakeup_gpio;
	bool drdy_trig_on;
	/* Ensures correct alignment of बारtamp अगर present */
	काष्ठा अणु
		s16 channels[2];
		s64 ts __aligned(8);
	पूर्ण scan;
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec ccs811_channels[] = अणु
	अणु
		.type = IIO_CURRENT,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE),
		.scan_index = -1,
	पूर्ण, अणु
		.type = IIO_VOLTAGE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE),
		.scan_index = -1,
	पूर्ण, अणु
		.type = IIO_CONCENTRATION,
		.channel2 = IIO_MOD_CO2,
		.modअगरied = 1,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE),
		.scan_index = 0,
		.scan_type = अणु
			.sign = 'u',
			.realbits = 16,
			.storagebits = 16,
			.endianness = IIO_BE,
		पूर्ण,
	पूर्ण, अणु
		.type = IIO_CONCENTRATION,
		.channel2 = IIO_MOD_VOC,
		.modअगरied = 1,
		.info_mask_separate =  BIT(IIO_CHAN_INFO_RAW) |
				       BIT(IIO_CHAN_INFO_SCALE),
		.scan_index = 1,
		.scan_type = अणु
			.sign = 'u',
			.realbits = 16,
			.storagebits = 16,
			.endianness = IIO_BE,
		पूर्ण,
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(2),
पूर्ण;

/*
 * The CCS811 घातers-up in boot mode. A setup ग_लिखो to CCS811_APP_START will
 * transition the sensor to application mode.
 */
अटल पूर्णांक ccs811_start_sensor_application(काष्ठा i2c_client *client)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, CCS811_STATUS);
	अगर (ret < 0)
		वापस ret;

	अगर ((ret & CCS811_STATUS_FW_MODE_APPLICATION))
		वापस 0;

	अगर ((ret & CCS811_STATUS_APP_VALID_MASK) !=
	    CCS811_STATUS_APP_VALID_LOADED)
		वापस -EIO;

	ret = i2c_smbus_ग_लिखो_byte(client, CCS811_APP_START);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, CCS811_STATUS);
	अगर (ret < 0)
		वापस ret;

	अगर ((ret & CCS811_STATUS_FW_MODE_MASK) !=
	    CCS811_STATUS_FW_MODE_APPLICATION) अणु
		dev_err(&client->dev, "Application failed to start. Sensor is still in boot mode.\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ccs811_setup(काष्ठा i2c_client *client)
अणु
	पूर्णांक ret;

	ret = ccs811_start_sensor_application(client);
	अगर (ret < 0)
		वापस ret;

	वापस i2c_smbus_ग_लिखो_byte_data(client, CCS811_MEAS_MODE,
					 CCS811_MODE_IAQ_1SEC);
पूर्ण

अटल व्योम ccs811_set_wakeup(काष्ठा ccs811_data *data, bool enable)
अणु
	अगर (!data->wakeup_gpio)
		वापस;

	gpiod_set_value(data->wakeup_gpio, enable);

	अगर (enable)
		usleep_range(50, 60);
	अन्यथा
		usleep_range(20, 30);
पूर्ण

अटल पूर्णांक ccs811_get_measurement(काष्ठा ccs811_data *data)
अणु
	पूर्णांक ret, tries = 11;

	ccs811_set_wakeup(data, true);

	/* Maximum रुकोing समय: 1s, as measurements are made every second */
	जबतक (tries-- > 0) अणु
		ret = i2c_smbus_पढ़ो_byte_data(data->client, CCS811_STATUS);
		अगर (ret < 0)
			वापस ret;

		अगर ((ret & CCS811_STATUS_DATA_READY) || tries == 0)
			अवरोध;
		msleep(100);
	पूर्ण
	अगर (!(ret & CCS811_STATUS_DATA_READY))
		वापस -EIO;

	ret = i2c_smbus_पढ़ो_i2c_block_data(data->client,
					    CCS811_ALG_RESULT_DATA, 8,
					    (अक्षर *)&data->buffer);
	ccs811_set_wakeup(data, false);

	वापस ret;
पूर्ण

अटल पूर्णांक ccs811_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा ccs811_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;
		mutex_lock(&data->lock);
		ret = ccs811_get_measurement(data);
		अगर (ret < 0) अणु
			mutex_unlock(&data->lock);
			iio_device_release_direct_mode(indio_dev);
			वापस ret;
		पूर्ण

		चयन (chan->type) अणु
		हाल IIO_VOLTAGE:
			*val = be16_to_cpu(data->buffer.raw_data) &
					   CCS811_VOLTAGE_MASK;
			ret = IIO_VAL_INT;
			अवरोध;
		हाल IIO_CURRENT:
			*val = be16_to_cpu(data->buffer.raw_data) >> 10;
			ret = IIO_VAL_INT;
			अवरोध;
		हाल IIO_CONCENTRATION:
			चयन (chan->channel2) अणु
			हाल IIO_MOD_CO2:
				*val = be16_to_cpu(data->buffer.co2);
				ret =  IIO_VAL_INT;
				अवरोध;
			हाल IIO_MOD_VOC:
				*val = be16_to_cpu(data->buffer.voc);
				ret = IIO_VAL_INT;
				अवरोध;
			शेष:
				ret = -EINVAL;
			पूर्ण
			अवरोध;
		शेष:
			ret = -EINVAL;
		पूर्ण
		mutex_unlock(&data->lock);
		iio_device_release_direct_mode(indio_dev);

		वापस ret;

	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_VOLTAGE:
			*val = 1;
			*val2 = 612903;
			वापस IIO_VAL_INT_PLUS_MICRO;
		हाल IIO_CURRENT:
			*val = 0;
			*val2 = 1000;
			वापस IIO_VAL_INT_PLUS_MICRO;
		हाल IIO_CONCENTRATION:
			चयन (chan->channel2) अणु
			हाल IIO_MOD_CO2:
				*val = 0;
				*val2 = 100;
				वापस IIO_VAL_INT_PLUS_MICRO;
			हाल IIO_MOD_VOC:
				*val = 0;
				*val2 = 100;
				वापस IIO_VAL_INT_PLUS_न_अंकO;
			शेष:
				वापस -EINVAL;
			पूर्ण
		शेष:
			वापस -EINVAL;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info ccs811_info = अणु
	.पढ़ो_raw = ccs811_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक ccs811_set_trigger_state(काष्ठा iio_trigger *trig,
				    bool state)
अणु
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	काष्ठा ccs811_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, CCS811_MEAS_MODE);
	अगर (ret < 0)
		वापस ret;

	अगर (state)
		ret |= CCS811_MEAS_MODE_INTERRUPT;
	अन्यथा
		ret &= ~CCS811_MEAS_MODE_INTERRUPT;

	data->drdy_trig_on = state;

	वापस i2c_smbus_ग_लिखो_byte_data(data->client, CCS811_MEAS_MODE, ret);
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops ccs811_trigger_ops = अणु
	.set_trigger_state = ccs811_set_trigger_state,
पूर्ण;

अटल irqवापस_t ccs811_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा ccs811_data *data = iio_priv(indio_dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_i2c_block_data(client, CCS811_ALG_RESULT_DATA,
					    माप(data->scan.channels),
					    (u8 *)data->scan.channels);
	अगर (ret != 4) अणु
		dev_err(&client->dev, "cannot read sensor data\n");
		जाओ err;
	पूर्ण

	iio_push_to_buffers_with_बारtamp(indio_dev, &data->scan,
					   iio_get_समय_ns(indio_dev));

err:
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t ccs811_data_rdy_trigger_poll(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा ccs811_data *data = iio_priv(indio_dev);

	अगर (data->drdy_trig_on)
		iio_trigger_poll(data->drdy_trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ccs811_reset(काष्ठा i2c_client *client)
अणु
	काष्ठा gpio_desc *reset_gpio;
	पूर्णांक ret;

	reset_gpio = devm_gpiod_get_optional(&client->dev, "reset",
					     GPIOD_OUT_LOW);
	अगर (IS_ERR(reset_gpio))
		वापस PTR_ERR(reset_gpio);

	/* Try to reset using nRESET pin अगर available अन्यथा करो SW reset */
	अगर (reset_gpio) अणु
		gpiod_set_value(reset_gpio, 1);
		usleep_range(20, 30);
		gpiod_set_value(reset_gpio, 0);
	पूर्ण अन्यथा अणु
		/*
		 * As per the datasheet, this sequence of values needs to be
		 * written to the SW_RESET रेजिस्टर क्रम triggering the soft
		 * reset in the device and placing it in boot mode.
		 */
		अटल स्थिर u8 reset_seq[] = अणु
			0x11, 0xE5, 0x72, 0x8A,
		पूर्ण;

		ret = i2c_smbus_ग_लिखो_i2c_block_data(client, CCS811_SW_RESET,
					     माप(reset_seq), reset_seq);
		अगर (ret < 0) अणु
			dev_err(&client->dev, "Failed to reset sensor\n");
			वापस ret;
		पूर्ण
	पूर्ण

	/* tSTART delay required after reset */
	usleep_range(1000, 2000);

	वापस 0;
पूर्ण

अटल पूर्णांक ccs811_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा ccs811_data *data;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_WRITE_BYTE
				     | I2C_FUNC_SMBUS_BYTE_DATA
				     | I2C_FUNC_SMBUS_READ_I2C_BLOCK))
		वापस -EOPNOTSUPP;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;

	data->wakeup_gpio = devm_gpiod_get_optional(&client->dev, "wakeup",
						    GPIOD_OUT_HIGH);
	अगर (IS_ERR(data->wakeup_gpio))
		वापस PTR_ERR(data->wakeup_gpio);

	ccs811_set_wakeup(data, true);

	ret = ccs811_reset(client);
	अगर (ret) अणु
		ccs811_set_wakeup(data, false);
		वापस ret;
	पूर्ण

	/* Check hardware id (should be 0x81 क्रम this family of devices) */
	ret = i2c_smbus_पढ़ो_byte_data(client, CCS811_HW_ID);
	अगर (ret < 0) अणु
		ccs811_set_wakeup(data, false);
		वापस ret;
	पूर्ण

	अगर (ret != CCS811_HW_ID_VALUE) अणु
		dev_err(&client->dev, "hardware id doesn't match CCS81x\n");
		ccs811_set_wakeup(data, false);
		वापस -ENODEV;
	पूर्ण

	ret = i2c_smbus_पढ़ो_byte_data(client, CCS811_HW_VERSION);
	अगर (ret < 0) अणु
		ccs811_set_wakeup(data, false);
		वापस ret;
	पूर्ण

	अगर ((ret & CCS811_HW_VERSION_MASK) != CCS811_HW_VERSION_VALUE) अणु
		dev_err(&client->dev, "no CCS811 sensor\n");
		ccs811_set_wakeup(data, false);
		वापस -ENODEV;
	पूर्ण

	ret = ccs811_setup(client);
	अगर (ret < 0) अणु
		ccs811_set_wakeup(data, false);
		वापस ret;
	पूर्ण

	ccs811_set_wakeup(data, false);

	mutex_init(&data->lock);

	indio_dev->name = id->name;
	indio_dev->info = &ccs811_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	indio_dev->channels = ccs811_channels;
	indio_dev->num_channels = ARRAY_SIZE(ccs811_channels);

	अगर (client->irq > 0) अणु
		ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
						ccs811_data_rdy_trigger_poll,
						शून्य,
						IRQF_TRIGGER_FALLING |
						IRQF_ONESHOT,
						"ccs811_irq", indio_dev);
		अगर (ret) अणु
			dev_err(&client->dev, "irq request error %d\n", -ret);
			जाओ err_घातeroff;
		पूर्ण

		data->drdy_trig = devm_iio_trigger_alloc(&client->dev,
							 "%s-dev%d",
							 indio_dev->name,
							 indio_dev->id);
		अगर (!data->drdy_trig) अणु
			ret = -ENOMEM;
			जाओ err_घातeroff;
		पूर्ण

		data->drdy_trig->ops = &ccs811_trigger_ops;
		iio_trigger_set_drvdata(data->drdy_trig, indio_dev);
		indio_dev->trig = data->drdy_trig;
		iio_trigger_get(indio_dev->trig);
		ret = iio_trigger_रेजिस्टर(data->drdy_trig);
		अगर (ret)
			जाओ err_घातeroff;
	पूर्ण

	ret = iio_triggered_buffer_setup(indio_dev, शून्य,
					 ccs811_trigger_handler, शून्य);

	अगर (ret < 0) अणु
		dev_err(&client->dev, "triggered buffer setup failed\n");
		जाओ err_trigger_unरेजिस्टर;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "unable to register iio device\n");
		जाओ err_buffer_cleanup;
	पूर्ण
	वापस 0;

err_buffer_cleanup:
	iio_triggered_buffer_cleanup(indio_dev);
err_trigger_unरेजिस्टर:
	अगर (data->drdy_trig)
		iio_trigger_unरेजिस्टर(data->drdy_trig);
err_घातeroff:
	i2c_smbus_ग_लिखो_byte_data(client, CCS811_MEAS_MODE, CCS811_MODE_IDLE);

	वापस ret;
पूर्ण

अटल पूर्णांक ccs811_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा ccs811_data *data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);
	अगर (data->drdy_trig)
		iio_trigger_unरेजिस्टर(data->drdy_trig);

	वापस i2c_smbus_ग_लिखो_byte_data(client, CCS811_MEAS_MODE,
					 CCS811_MODE_IDLE);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ccs811_id[] = अणु
	अणु"ccs811", 0पूर्ण,
	अणु	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ccs811_id);

अटल स्थिर काष्ठा of_device_id ccs811_dt_ids[] = अणु
	अणु .compatible = "ams,ccs811" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ccs811_dt_ids);

अटल काष्ठा i2c_driver ccs811_driver = अणु
	.driver = अणु
		.name = "ccs811",
		.of_match_table = ccs811_dt_ids,
	पूर्ण,
	.probe = ccs811_probe,
	.हटाओ = ccs811_हटाओ,
	.id_table = ccs811_id,
पूर्ण;
module_i2c_driver(ccs811_driver);

MODULE_AUTHOR("Narcisa Vasile <narcisaanamaria12@gmail.com>");
MODULE_DESCRIPTION("CCS811 volatile organic compounds sensor");
MODULE_LICENSE("GPL v2");
