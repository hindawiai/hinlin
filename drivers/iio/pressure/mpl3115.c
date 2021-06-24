<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * mpl3115.c - Support क्रम Freescale MPL3115A2 pressure/temperature sensor
 *
 * Copyright (c) 2013 Peter Meerwald <pmeerw@pmeerw.net>
 *
 * (7-bit I2C slave address 0x60)
 *
 * TODO: FIFO buffer, alसमयter mode, oversampling, continuous mode,
 * पूर्णांकerrupts, user offset correction, raw mode
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/delay.h>

#घोषणा MPL3115_STATUS 0x00
#घोषणा MPL3115_OUT_PRESS 0x01 /* MSB first, 20 bit */
#घोषणा MPL3115_OUT_TEMP 0x04 /* MSB first, 12 bit */
#घोषणा MPL3115_WHO_AM_I 0x0c
#घोषणा MPL3115_CTRL_REG1 0x26

#घोषणा MPL3115_DEVICE_ID 0xc4

#घोषणा MPL3115_STATUS_PRESS_RDY BIT(2)
#घोषणा MPL3115_STATUS_TEMP_RDY BIT(1)

#घोषणा MPL3115_CTRL_RESET BIT(2) /* software reset */
#घोषणा MPL3115_CTRL_OST BIT(1) /* initiate measurement */
#घोषणा MPL3115_CTRL_ACTIVE BIT(0) /* continuous measurement */
#घोषणा MPL3115_CTRL_OS_258MS (BIT(5) | BIT(4)) /* 64x oversampling */

काष्ठा mpl3115_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;
	u8 ctrl_reg1;
पूर्ण;

अटल पूर्णांक mpl3115_request(काष्ठा mpl3115_data *data)
अणु
	पूर्णांक ret, tries = 15;

	/* trigger measurement */
	ret = i2c_smbus_ग_लिखो_byte_data(data->client, MPL3115_CTRL_REG1,
		data->ctrl_reg1 | MPL3115_CTRL_OST);
	अगर (ret < 0)
		वापस ret;

	जबतक (tries-- > 0) अणु
		ret = i2c_smbus_पढ़ो_byte_data(data->client, MPL3115_CTRL_REG1);
		अगर (ret < 0)
			वापस ret;
		/* रुको क्रम data पढ़ोy, i.e. OST cleared */
		अगर (!(ret & MPL3115_CTRL_OST))
			अवरोध;
		msleep(20);
	पूर्ण

	अगर (tries < 0) अणु
		dev_err(&data->client->dev, "data not ready\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mpl3115_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा mpl3115_data *data = iio_priv(indio_dev);
	__be32 पंचांगp = 0;
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;

		चयन (chan->type) अणु
		हाल IIO_PRESSURE: /* in 0.25 pascal / LSB */
			mutex_lock(&data->lock);
			ret = mpl3115_request(data);
			अगर (ret < 0) अणु
				mutex_unlock(&data->lock);
				अवरोध;
			पूर्ण
			ret = i2c_smbus_पढ़ो_i2c_block_data(data->client,
				MPL3115_OUT_PRESS, 3, (u8 *) &पंचांगp);
			mutex_unlock(&data->lock);
			अगर (ret < 0)
				अवरोध;
			*val = be32_to_cpu(पंचांगp) >> 12;
			ret = IIO_VAL_INT;
			अवरोध;
		हाल IIO_TEMP: /* in 0.0625 celsius / LSB */
			mutex_lock(&data->lock);
			ret = mpl3115_request(data);
			अगर (ret < 0) अणु
				mutex_unlock(&data->lock);
				अवरोध;
			पूर्ण
			ret = i2c_smbus_पढ़ो_i2c_block_data(data->client,
				MPL3115_OUT_TEMP, 2, (u8 *) &पंचांगp);
			mutex_unlock(&data->lock);
			अगर (ret < 0)
				अवरोध;
			*val = sign_extend32(be32_to_cpu(पंचांगp) >> 20, 11);
			ret = IIO_VAL_INT;
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		iio_device_release_direct_mode(indio_dev);
		वापस ret;

	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_PRESSURE:
			*val = 0;
			*val2 = 250; /* want kilopascal */
			वापस IIO_VAL_INT_PLUS_MICRO;
		हाल IIO_TEMP:
			*val = 0;
			*val2 = 62500;
			वापस IIO_VAL_INT_PLUS_MICRO;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल irqवापस_t mpl3115_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा mpl3115_data *data = iio_priv(indio_dev);
	/*
	 * 32-bit channel + 16-bit channel + padding + ts
	 * Note that it is possible क्रम only one of the first 2
	 * channels to be enabled. If that happens, the first element
	 * of the buffer may be either 16 or 32-bits.  As such we cannot
	 * use a simple काष्ठाure definition to express this data layout.
	 */
	u8 buffer[16] __aligned(8);
	पूर्णांक ret, pos = 0;

	mutex_lock(&data->lock);
	ret = mpl3115_request(data);
	अगर (ret < 0) अणु
		mutex_unlock(&data->lock);
		जाओ करोne;
	पूर्ण

	स_रखो(buffer, 0, माप(buffer));
	अगर (test_bit(0, indio_dev->active_scan_mask)) अणु
		ret = i2c_smbus_पढ़ो_i2c_block_data(data->client,
			MPL3115_OUT_PRESS, 3, &buffer[pos]);
		अगर (ret < 0) अणु
			mutex_unlock(&data->lock);
			जाओ करोne;
		पूर्ण
		pos += 4;
	पूर्ण

	अगर (test_bit(1, indio_dev->active_scan_mask)) अणु
		ret = i2c_smbus_पढ़ो_i2c_block_data(data->client,
			MPL3115_OUT_TEMP, 2, &buffer[pos]);
		अगर (ret < 0) अणु
			mutex_unlock(&data->lock);
			जाओ करोne;
		पूर्ण
	पूर्ण
	mutex_unlock(&data->lock);

	iio_push_to_buffers_with_बारtamp(indio_dev, buffer,
		iio_get_समय_ns(indio_dev));

करोne:
	iio_trigger_notअगरy_करोne(indio_dev->trig);
	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec mpl3115_channels[] = अणु
	अणु
		.type = IIO_PRESSURE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),
		.scan_index = 0,
		.scan_type = अणु
			.sign = 'u',
			.realbits = 20,
			.storagebits = 32,
			.shअगरt = 12,
			.endianness = IIO_BE,
		पूर्ण
	पूर्ण,
	अणु
		.type = IIO_TEMP,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),
		.scan_index = 1,
		.scan_type = अणु
			.sign = 's',
			.realbits = 12,
			.storagebits = 16,
			.shअगरt = 4,
			.endianness = IIO_BE,
		पूर्ण
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(2),
पूर्ण;

अटल स्थिर काष्ठा iio_info mpl3115_info = अणु
	.पढ़ो_raw = &mpl3115_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक mpl3115_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा mpl3115_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, MPL3115_WHO_AM_I);
	अगर (ret < 0)
		वापस ret;
	अगर (ret != MPL3115_DEVICE_ID)
		वापस -ENODEV;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	data->client = client;
	mutex_init(&data->lock);

	i2c_set_clientdata(client, indio_dev);
	indio_dev->info = &mpl3115_info;
	indio_dev->name = id->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = mpl3115_channels;
	indio_dev->num_channels = ARRAY_SIZE(mpl3115_channels);

	/* software reset, I2C transfer is पातed (fails) */
	i2c_smbus_ग_लिखो_byte_data(client, MPL3115_CTRL_REG1,
		MPL3115_CTRL_RESET);
	msleep(50);

	data->ctrl_reg1 = MPL3115_CTRL_OS_258MS;
	ret = i2c_smbus_ग_लिखो_byte_data(client, MPL3115_CTRL_REG1,
		data->ctrl_reg1);
	अगर (ret < 0)
		वापस ret;

	ret = iio_triggered_buffer_setup(indio_dev, शून्य,
		mpl3115_trigger_handler, शून्य);
	अगर (ret < 0)
		वापस ret;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0)
		जाओ buffer_cleanup;
	वापस 0;

buffer_cleanup:
	iio_triggered_buffer_cleanup(indio_dev);
	वापस ret;
पूर्ण

अटल पूर्णांक mpl3115_standby(काष्ठा mpl3115_data *data)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(data->client, MPL3115_CTRL_REG1,
		data->ctrl_reg1 & ~MPL3115_CTRL_ACTIVE);
पूर्ण

अटल पूर्णांक mpl3115_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);

	iio_device_unरेजिस्टर(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);
	mpl3115_standby(iio_priv(indio_dev));

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mpl3115_suspend(काष्ठा device *dev)
अणु
	वापस mpl3115_standby(iio_priv(i2c_get_clientdata(
		to_i2c_client(dev))));
पूर्ण

अटल पूर्णांक mpl3115_resume(काष्ठा device *dev)
अणु
	काष्ठा mpl3115_data *data = iio_priv(i2c_get_clientdata(
		to_i2c_client(dev)));

	वापस i2c_smbus_ग_लिखो_byte_data(data->client, MPL3115_CTRL_REG1,
		data->ctrl_reg1);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(mpl3115_pm_ops, mpl3115_suspend, mpl3115_resume);
#घोषणा MPL3115_PM_OPS (&mpl3115_pm_ops)
#अन्यथा
#घोषणा MPL3115_PM_OPS शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id mpl3115_id[] = अणु
	अणु "mpl3115", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mpl3115_id);

अटल स्थिर काष्ठा of_device_id mpl3115_of_match[] = अणु
	अणु .compatible = "fsl,mpl3115" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mpl3115_of_match);

अटल काष्ठा i2c_driver mpl3115_driver = अणु
	.driver = अणु
		.name	= "mpl3115",
		.of_match_table = mpl3115_of_match,
		.pm	= MPL3115_PM_OPS,
	पूर्ण,
	.probe = mpl3115_probe,
	.हटाओ = mpl3115_हटाओ,
	.id_table = mpl3115_id,
पूर्ण;
module_i2c_driver(mpl3115_driver);

MODULE_AUTHOR("Peter Meerwald <pmeerw@pmeerw.net>");
MODULE_DESCRIPTION("Freescale MPL3115 pressure/temperature driver");
MODULE_LICENSE("GPL");
