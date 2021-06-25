<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * pulsedlight-lidar-lite-v2.c - Support क्रम PulsedLight LIDAR sensor
 *
 * Copyright (C) 2015, 2017-2018
 * Author: Matt Ranostay <matt.ranostay@konsulko.com>
 *
 * TODO: पूर्णांकerrupt mode, and संकेत strength reporting
 */

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/trigger_consumer.h>

#घोषणा LIDAR_REG_CONTROL		0x00
#घोषणा LIDAR_REG_CONTROL_ACQUIRE	BIT(2)

#घोषणा LIDAR_REG_STATUS		0x01
#घोषणा LIDAR_REG_STATUS_INVALID	BIT(3)
#घोषणा LIDAR_REG_STATUS_READY		BIT(0)

#घोषणा LIDAR_REG_DATA_HBYTE		0x0f
#घोषणा LIDAR_REG_DATA_LBYTE		0x10
#घोषणा LIDAR_REG_DATA_WORD_READ	BIT(7)

#घोषणा LIDAR_REG_PWR_CONTROL	0x65

#घोषणा LIDAR_DRV_NAME "lidar"

काष्ठा lidar_data अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा i2c_client *client;

	पूर्णांक (*xfer)(काष्ठा lidar_data *data, u8 reg, u8 *val, पूर्णांक len);
	पूर्णांक i2c_enabled;

	u16 buffer[8]; /* 2 byte distance + 8 byte बारtamp */
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec lidar_channels[] = अणु
	अणु
		.type = IIO_DISTANCE,
		.info_mask_separate =
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
		.scan_index = 0,
		.scan_type = अणु
			.sign = 'u',
			.realbits = 16,
			.storagebits = 16,
		पूर्ण,
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(1),
पूर्ण;

अटल पूर्णांक lidar_i2c_xfer(काष्ठा lidar_data *data, u8 reg, u8 *val, पूर्णांक len)
अणु
	काष्ठा i2c_client *client = data->client;
	काष्ठा i2c_msg msg[2];
	पूर्णांक ret;

	msg[0].addr = client->addr;
	msg[0].flags = client->flags | I2C_M_STOP;
	msg[0].len = 1;
	msg[0].buf  = (अक्षर *) &reg;

	msg[1].addr = client->addr;
	msg[1].flags = client->flags | I2C_M_RD;
	msg[1].len = len;
	msg[1].buf = (अक्षर *) val;

	ret = i2c_transfer(client->adapter, msg, 2);

	वापस (ret == 2) ? 0 : -EIO;
पूर्ण

अटल पूर्णांक lidar_smbus_xfer(काष्ठा lidar_data *data, u8 reg, u8 *val, पूर्णांक len)
अणु
	काष्ठा i2c_client *client = data->client;
	पूर्णांक ret;

	/*
	 * Device needs a STOP condition between address ग_लिखो, and data पढ़ो
	 * so in turn i2c_smbus_पढ़ो_byte_data cannot be used
	 */

	जबतक (len--) अणु
		ret = i2c_smbus_ग_लिखो_byte(client, reg++);
		अगर (ret < 0) अणु
			dev_err(&client->dev, "cannot write addr value");
			वापस ret;
		पूर्ण

		ret = i2c_smbus_पढ़ो_byte(client);
		अगर (ret < 0) अणु
			dev_err(&client->dev, "cannot read data value");
			वापस ret;
		पूर्ण

		*(val++) = ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lidar_पढ़ो_byte(काष्ठा lidar_data *data, u8 reg)
अणु
	पूर्णांक ret;
	u8 val;

	ret = data->xfer(data, reg, &val, 1);
	अगर (ret < 0)
		वापस ret;

	वापस val;
पूर्ण

अटल अंतरभूत पूर्णांक lidar_ग_लिखो_control(काष्ठा lidar_data *data, पूर्णांक val)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(data->client, LIDAR_REG_CONTROL, val);
पूर्ण

अटल अंतरभूत पूर्णांक lidar_ग_लिखो_घातer(काष्ठा lidar_data *data, पूर्णांक val)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(data->client,
					 LIDAR_REG_PWR_CONTROL, val);
पूर्ण

अटल पूर्णांक lidar_पढ़ो_measurement(काष्ठा lidar_data *data, u16 *reg)
अणु
	__be16 value;
	पूर्णांक ret = data->xfer(data, LIDAR_REG_DATA_HBYTE |
			(data->i2c_enabled ? LIDAR_REG_DATA_WORD_READ : 0),
			(u8 *) &value, 2);

	अगर (!ret)
		*reg = be16_to_cpu(value);

	वापस ret;
पूर्ण

अटल पूर्णांक lidar_get_measurement(काष्ठा lidar_data *data, u16 *reg)
अणु
	काष्ठा i2c_client *client = data->client;
	पूर्णांक tries = 10;
	पूर्णांक ret;

	pm_runसमय_get_sync(&client->dev);

	/* start sample */
	ret = lidar_ग_लिखो_control(data, LIDAR_REG_CONTROL_ACQUIRE);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "cannot send start measurement command");
		pm_runसमय_put_noidle(&client->dev);
		वापस ret;
	पूर्ण

	जबतक (tries--) अणु
		usleep_range(1000, 2000);

		ret = lidar_पढ़ो_byte(data, LIDAR_REG_STATUS);
		अगर (ret < 0)
			अवरोध;

		/* वापस -EINVAL since laser is likely poपूर्णांकed out of range */
		अगर (ret & LIDAR_REG_STATUS_INVALID) अणु
			*reg = 0;
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		/* sample पढ़ोy to पढ़ो */
		अगर (!(ret & LIDAR_REG_STATUS_READY)) अणु
			ret = lidar_पढ़ो_measurement(data, reg);
			अवरोध;
		पूर्ण
		ret = -EIO;
	पूर्ण
	pm_runसमय_mark_last_busy(&client->dev);
	pm_runसमय_put_स्वतःsuspend(&client->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक lidar_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			  काष्ठा iio_chan_spec स्थिर *chan,
			  पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा lidar_data *data = iio_priv(indio_dev);
	पूर्णांक ret = -EINVAL;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW: अणु
		u16 reg;

		अगर (iio_device_claim_direct_mode(indio_dev))
			वापस -EBUSY;

		ret = lidar_get_measurement(data, &reg);
		अगर (!ret) अणु
			*val = reg;
			ret = IIO_VAL_INT;
		पूर्ण
		iio_device_release_direct_mode(indio_dev);
		अवरोध;
	पूर्ण
	हाल IIO_CHAN_INFO_SCALE:
		*val = 0;
		*val2 = 10000;
		ret = IIO_VAL_INT_PLUS_MICRO;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल irqवापस_t lidar_trigger_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_poll_func *pf = निजी;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा lidar_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = lidar_get_measurement(data, data->buffer);
	अगर (!ret) अणु
		iio_push_to_buffers_with_बारtamp(indio_dev, data->buffer,
						   iio_get_समय_ns(indio_dev));
	पूर्ण अन्यथा अगर (ret != -EINVAL) अणु
		dev_err(&data->client->dev, "cannot read LIDAR measurement");
	पूर्ण

	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा iio_info lidar_info = अणु
	.पढ़ो_raw = lidar_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक lidar_probe(काष्ठा i2c_client *client,
		       स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा lidar_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;
	data = iio_priv(indio_dev);

	अगर (i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		data->xfer = lidar_i2c_xfer;
		data->i2c_enabled = 1;
	पूर्ण अन्यथा अगर (i2c_check_functionality(client->adapter,
				I2C_FUNC_SMBUS_WORD_DATA | I2C_FUNC_SMBUS_BYTE))
		data->xfer = lidar_smbus_xfer;
	अन्यथा
		वापस -EOPNOTSUPP;

	indio_dev->info = &lidar_info;
	indio_dev->name = LIDAR_DRV_NAME;
	indio_dev->channels = lidar_channels;
	indio_dev->num_channels = ARRAY_SIZE(lidar_channels);
	indio_dev->modes = INDIO_सूचीECT_MODE;

	i2c_set_clientdata(client, indio_dev);

	data->client = client;
	data->indio_dev = indio_dev;

	ret = iio_triggered_buffer_setup(indio_dev, शून्य,
					 lidar_trigger_handler, शून्य);
	अगर (ret)
		वापस ret;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ error_unreg_buffer;

	pm_runसमय_set_स्वतःsuspend_delay(&client->dev, 1000);
	pm_runसमय_use_स्वतःsuspend(&client->dev);

	ret = pm_runसमय_set_active(&client->dev);
	अगर (ret)
		जाओ error_unreg_buffer;
	pm_runसमय_enable(&client->dev);
	pm_runसमय_idle(&client->dev);

	वापस 0;

error_unreg_buffer:
	iio_triggered_buffer_cleanup(indio_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक lidar_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);

	iio_device_unरेजिस्टर(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);

	pm_runसमय_disable(&client->dev);
	pm_runसमय_set_suspended(&client->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lidar_id[] = अणु
	अणु"lidar-lite-v2", 0पूर्ण,
	अणु"lidar-lite-v3", 0पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lidar_id);

अटल स्थिर काष्ठा of_device_id lidar_dt_ids[] = अणु
	अणु .compatible = "pulsedlight,lidar-lite-v2" पूर्ण,
	अणु .compatible = "grmn,lidar-lite-v3" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lidar_dt_ids);

#अगर_घोषित CONFIG_PM
अटल पूर्णांक lidar_pm_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा lidar_data *data = iio_priv(indio_dev);

	वापस lidar_ग_लिखो_घातer(data, 0x0f);
पूर्ण

अटल पूर्णांक lidar_pm_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा lidar_data *data = iio_priv(indio_dev);
	पूर्णांक ret = lidar_ग_लिखो_घातer(data, 0);

	/* regulator and FPGA needs settling समय */
	usleep_range(15000, 20000);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops lidar_pm_ops = अणु
	SET_RUNTIME_PM_OPS(lidar_pm_runसमय_suspend,
			   lidar_pm_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा i2c_driver lidar_driver = अणु
	.driver = अणु
		.name	= LIDAR_DRV_NAME,
		.of_match_table	= lidar_dt_ids,
		.pm	= &lidar_pm_ops,
	पूर्ण,
	.probe		= lidar_probe,
	.हटाओ		= lidar_हटाओ,
	.id_table	= lidar_id,
पूर्ण;
module_i2c_driver(lidar_driver);

MODULE_AUTHOR("Matt Ranostay <matt.ranostay@konsulko.com>");
MODULE_DESCRIPTION("PulsedLight LIDAR sensor");
MODULE_LICENSE("GPL");
