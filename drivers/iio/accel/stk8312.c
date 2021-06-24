<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Sensortek STK8312 3-Axis Accelerometer
 *
 * Copyright (c) 2015, Intel Corporation.
 *
 * IIO driver क्रम STK8312; 7-bit I2C address: 0x3D.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/trigger_consumer.h>

#घोषणा STK8312_REG_XOUT		0x00
#घोषणा STK8312_REG_YOUT		0x01
#घोषणा STK8312_REG_ZOUT		0x02
#घोषणा STK8312_REG_INTSU		0x06
#घोषणा STK8312_REG_MODE		0x07
#घोषणा STK8312_REG_SR			0x08
#घोषणा STK8312_REG_STH			0x13
#घोषणा STK8312_REG_RESET		0x20
#घोषणा STK8312_REG_AFECTRL		0x24
#घोषणा STK8312_REG_OTPADDR		0x3D
#घोषणा STK8312_REG_OTPDATA		0x3E
#घोषणा STK8312_REG_OTPCTRL		0x3F

#घोषणा STK8312_MODE_ACTIVE		BIT(0)
#घोषणा STK8312_MODE_STANDBY		0x00
#घोषणा STK8312_MODE_INT_AH_PP		0xC0	/* active-high, push-pull */
#घोषणा STK8312_DREADY_BIT		BIT(4)
#घोषणा STK8312_RNG_6G			1
#घोषणा STK8312_RNG_SHIFT		6
#घोषणा STK8312_RNG_MASK		GENMASK(7, 6)
#घोषणा STK8312_SR_MASK			GENMASK(2, 0)
#घोषणा STK8312_SR_400HZ_IDX		0
#घोषणा STK8312_ALL_CHANNEL_MASK	GENMASK(2, 0)
#घोषणा STK8312_ALL_CHANNEL_SIZE	3

#घोषणा STK8312_DRIVER_NAME		"stk8312"
#घोषणा STK8312_IRQ_NAME		"stk8312_event"

/*
 * The accelerometer has two measurement ranges:
 *
 * -6g - +6g (8-bit, चिन्हित)
 * -16g - +16g (8-bit, चिन्हित)
 *
 * scale1 = (6 + 6) * 9.81 / (2^8 - 1)     = 0.4616
 * scale2 = (16 + 16) * 9.81 / (2^8 - 1)   = 1.2311
 */
#घोषणा STK8312_SCALE_AVAIL		"0.4616 1.2311"

अटल स्थिर पूर्णांक stk8312_scale_table[][2] = अणु
	अणु0, 461600पूर्ण, अणु1, 231100पूर्ण
पूर्ण;

अटल स्थिर काष्ठा अणु
	पूर्णांक val;
	पूर्णांक val2;
पूर्ण stk8312_samp_freq_table[] = अणु
	अणु400, 0पूर्ण, अणु200, 0पूर्ण, अणु100, 0पूर्ण, अणु50, 0पूर्ण, अणु25, 0पूर्ण,
	अणु12, 500000पूर्ण, अणु6, 250000पूर्ण, अणु3, 125000पूर्ण
पूर्ण;

#घोषणा STK8312_ACCEL_CHANNEL(index, reg, axis) अणु			\
	.type = IIO_ACCEL,						\
	.address = reg,							\
	.modअगरied = 1,							\
	.channel2 = IIO_MOD_##axis,					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),			\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) |		\
				    BIT(IIO_CHAN_INFO_SAMP_FREQ),	\
	.scan_index = index,						\
	.scan_type = अणु							\
		.sign = 's',						\
		.realbits = 8,						\
		.storagebits = 8,					\
		.endianness = IIO_CPU,					\
	पूर्ण,								\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec stk8312_channels[] = अणु
	STK8312_ACCEL_CHANNEL(0, STK8312_REG_XOUT, X),
	STK8312_ACCEL_CHANNEL(1, STK8312_REG_YOUT, Y),
	STK8312_ACCEL_CHANNEL(2, STK8312_REG_ZOUT, Z),
	IIO_CHAN_SOFT_TIMESTAMP(3),
पूर्ण;

काष्ठा stk8312_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;
	u8 range;
	u8 sample_rate_idx;
	u8 mode;
	काष्ठा iio_trigger *dपढ़ोy_trig;
	bool dपढ़ोy_trigger_on;
	s8 buffer[16]; /* 3x8-bit channels + 5x8 padding + 64-bit बारtamp */
पूर्ण;

अटल IIO_CONST_ATTR(in_accel_scale_available, STK8312_SCALE_AVAIL);

अटल IIO_CONST_ATTR_SAMP_FREQ_AVAIL("3.125 6.25 12.5 25 50 100 200 400");

अटल काष्ठा attribute *stk8312_attributes[] = अणु
	&iio_स्थिर_attr_in_accel_scale_available.dev_attr.attr,
	&iio_स्थिर_attr_sampling_frequency_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group stk8312_attribute_group = अणु
	.attrs = stk8312_attributes
पूर्ण;

अटल पूर्णांक stk8312_otp_init(काष्ठा stk8312_data *data)
अणु
	पूर्णांक ret;
	पूर्णांक count = 10;
	काष्ठा i2c_client *client = data->client;

	ret = i2c_smbus_ग_लिखो_byte_data(client, STK8312_REG_OTPADDR, 0x70);
	अगर (ret < 0)
		जाओ निकास_err;
	ret = i2c_smbus_ग_लिखो_byte_data(client, STK8312_REG_OTPCTRL, 0x02);
	अगर (ret < 0)
		जाओ निकास_err;

	करो अणु
		usleep_range(1000, 5000);
		ret = i2c_smbus_पढ़ो_byte_data(client, STK8312_REG_OTPCTRL);
		अगर (ret < 0)
			जाओ निकास_err;
		count--;
	पूर्ण जबतक (!(ret & BIT(7)) && count > 0);

	अगर (count == 0) अणु
		ret = -ETIMEDOUT;
		जाओ निकास_err;
	पूर्ण

	ret = i2c_smbus_पढ़ो_byte_data(client, STK8312_REG_OTPDATA);
	अगर (ret == 0)
		ret = -EINVAL;
	अगर (ret < 0)
		जाओ निकास_err;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, STK8312_REG_AFECTRL, ret);
	अगर (ret < 0)
		जाओ निकास_err;
	msleep(150);

	वापस 0;

निकास_err:
	dev_err(&client->dev, "failed to initialize sensor\n");
	वापस ret;
पूर्ण

अटल पूर्णांक stk8312_set_mode(काष्ठा stk8312_data *data, u8 mode)
अणु
	पूर्णांक ret;
	काष्ठा i2c_client *client = data->client;

	अगर (mode == data->mode)
		वापस 0;

	ret = i2c_smbus_ग_लिखो_byte_data(client, STK8312_REG_MODE, mode);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed to change sensor mode\n");
		वापस ret;
	पूर्ण

	data->mode = mode;
	अगर (mode & STK8312_MODE_ACTIVE) अणु
		/* Need to run OTP sequence beक्रमe entering active mode */
		usleep_range(1000, 5000);
		ret = stk8312_otp_init(data);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक stk8312_set_पूर्णांकerrupts(काष्ठा stk8312_data *data, u8 पूर्णांक_mask)
अणु
	पूर्णांक ret;
	u8 mode;
	काष्ठा i2c_client *client = data->client;

	mode = data->mode;
	/* We need to go in standby mode to modअगरy रेजिस्टरs */
	ret = stk8312_set_mode(data, STK8312_MODE_STANDBY);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_ग_लिखो_byte_data(client, STK8312_REG_INTSU, पूर्णांक_mask);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed to set interrupts\n");
		stk8312_set_mode(data, mode);
		वापस ret;
	पूर्ण

	वापस stk8312_set_mode(data, mode);
पूर्ण

अटल पूर्णांक stk8312_data_rdy_trigger_set_state(काष्ठा iio_trigger *trig,
					      bool state)
अणु
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	काष्ठा stk8312_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	अगर (state)
		ret = stk8312_set_पूर्णांकerrupts(data, STK8312_DREADY_BIT);
	अन्यथा
		ret = stk8312_set_पूर्णांकerrupts(data, 0x00);

	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "failed to set trigger state\n");
		वापस ret;
	पूर्ण

	data->dपढ़ोy_trigger_on = state;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops stk8312_trigger_ops = अणु
	.set_trigger_state = stk8312_data_rdy_trigger_set_state,
पूर्ण;

अटल पूर्णांक stk8312_set_sample_rate(काष्ठा stk8312_data *data, u8 rate)
अणु
	पूर्णांक ret;
	u8 masked_reg;
	u8 mode;
	काष्ठा i2c_client *client = data->client;

	अगर (rate == data->sample_rate_idx)
		वापस 0;

	mode = data->mode;
	/* We need to go in standby mode to modअगरy रेजिस्टरs */
	ret = stk8312_set_mode(data, STK8312_MODE_STANDBY);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, STK8312_REG_SR);
	अगर (ret < 0)
		जाओ err_activate;

	masked_reg = (ret & (~STK8312_SR_MASK)) | rate;

	ret = i2c_smbus_ग_लिखो_byte_data(client, STK8312_REG_SR, masked_reg);
	अगर (ret < 0)
		जाओ err_activate;

	data->sample_rate_idx = rate;

	वापस stk8312_set_mode(data, mode);

err_activate:
	dev_err(&client->dev, "failed to set sampling rate\n");
	stk8312_set_mode(data, mode);

	वापस ret;
पूर्ण

अटल पूर्णांक stk8312_set_range(काष्ठा stk8312_data *data, u8 range)
अणु
	पूर्णांक ret;
	u8 masked_reg;
	u8 mode;
	काष्ठा i2c_client *client = data->client;

	अगर (range != 1 && range != 2)
		वापस -EINVAL;
	अन्यथा अगर (range == data->range)
		वापस 0;

	mode = data->mode;
	/* We need to go in standby mode to modअगरy रेजिस्टरs */
	ret = stk8312_set_mode(data, STK8312_MODE_STANDBY);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, STK8312_REG_STH);
	अगर (ret < 0)
		जाओ err_activate;

	masked_reg = ret & (~STK8312_RNG_MASK);
	masked_reg |= range << STK8312_RNG_SHIFT;

	ret = i2c_smbus_ग_लिखो_byte_data(client, STK8312_REG_STH, masked_reg);
	अगर (ret < 0)
		जाओ err_activate;

	data->range = range;

	वापस stk8312_set_mode(data, mode);

err_activate:
	dev_err(&client->dev, "failed to change sensor range\n");
	stk8312_set_mode(data, mode);

	वापस ret;
पूर्ण

अटल पूर्णांक stk8312_पढ़ो_accel(काष्ठा stk8312_data *data, u8 address)
अणु
	पूर्णांक ret;
	काष्ठा i2c_client *client = data->client;

	अगर (address > 2)
		वापस -EINVAL;

	ret = i2c_smbus_पढ़ो_byte_data(client, address);
	अगर (ret < 0)
		dev_err(&client->dev, "register read failed\n");

	वापस ret;
पूर्ण

अटल पूर्णांक stk8312_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा stk8312_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (iio_buffer_enabled(indio_dev))
			वापस -EBUSY;
		mutex_lock(&data->lock);
		ret = stk8312_set_mode(data, data->mode | STK8312_MODE_ACTIVE);
		अगर (ret < 0) अणु
			mutex_unlock(&data->lock);
			वापस ret;
		पूर्ण
		ret = stk8312_पढ़ो_accel(data, chan->address);
		अगर (ret < 0) अणु
			stk8312_set_mode(data,
					 data->mode & (~STK8312_MODE_ACTIVE));
			mutex_unlock(&data->lock);
			वापस ret;
		पूर्ण
		*val = sign_extend32(ret, 7);
		ret = stk8312_set_mode(data,
				       data->mode & (~STK8312_MODE_ACTIVE));
		mutex_unlock(&data->lock);
		अगर (ret < 0)
			वापस ret;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = stk8312_scale_table[data->range - 1][0];
		*val2 = stk8312_scale_table[data->range - 1][1];
		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*val = stk8312_samp_freq_table[data->sample_rate_idx].val;
		*val2 = stk8312_samp_freq_table[data->sample_rate_idx].val2;
		वापस IIO_VAL_INT_PLUS_MICRO;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक stk8312_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	पूर्णांक i;
	पूर्णांक index = -1;
	पूर्णांक ret;
	काष्ठा stk8312_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		क्रम (i = 0; i < ARRAY_SIZE(stk8312_scale_table); i++)
			अगर (val == stk8312_scale_table[i][0] &&
			    val2 == stk8312_scale_table[i][1]) अणु
				index = i + 1;
				अवरोध;
			पूर्ण
		अगर (index < 0)
			वापस -EINVAL;

		mutex_lock(&data->lock);
		ret = stk8312_set_range(data, index);
		mutex_unlock(&data->lock);

		वापस ret;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		क्रम (i = 0; i < ARRAY_SIZE(stk8312_samp_freq_table); i++)
			अगर (val == stk8312_samp_freq_table[i].val &&
			    val2 == stk8312_samp_freq_table[i].val2) अणु
				index = i;
				अवरोध;
			पूर्ण
		अगर (index < 0)
			वापस -EINVAL;
		mutex_lock(&data->lock);
		ret = stk8312_set_sample_rate(data, index);
		mutex_unlock(&data->lock);

		वापस ret;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info stk8312_info = अणु
	.पढ़ो_raw		= stk8312_पढ़ो_raw,
	.ग_लिखो_raw		= stk8312_ग_लिखो_raw,
	.attrs			= &stk8312_attribute_group,
पूर्ण;

अटल irqवापस_t stk8312_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा stk8312_data *data = iio_priv(indio_dev);
	पूर्णांक bit, ret, i = 0;

	mutex_lock(&data->lock);
	/*
	 * Do a bulk पढ़ो अगर all channels are requested,
	 * from 0x00 (XOUT) to 0x02 (ZOUT)
	 */
	अगर (*(indio_dev->active_scan_mask) == STK8312_ALL_CHANNEL_MASK) अणु
		ret = i2c_smbus_पढ़ो_i2c_block_data(data->client,
						    STK8312_REG_XOUT,
						    STK8312_ALL_CHANNEL_SIZE,
						    data->buffer);
		अगर (ret < STK8312_ALL_CHANNEL_SIZE) अणु
			dev_err(&data->client->dev, "register read failed\n");
			mutex_unlock(&data->lock);
			जाओ err;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम_each_set_bit(bit, indio_dev->active_scan_mask,
				 indio_dev->masklength) अणु
			ret = stk8312_पढ़ो_accel(data, bit);
			अगर (ret < 0) अणु
				mutex_unlock(&data->lock);
				जाओ err;
			पूर्ण
			data->buffer[i++] = ret;
		पूर्ण
	पूर्ण
	mutex_unlock(&data->lock);

	iio_push_to_buffers_with_बारtamp(indio_dev, data->buffer,
					   pf->बारtamp);
err:
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t stk8312_data_rdy_trig_poll(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा stk8312_data *data = iio_priv(indio_dev);

	अगर (data->dपढ़ोy_trigger_on)
		iio_trigger_poll(data->dपढ़ोy_trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक stk8312_buffer_preenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा stk8312_data *data = iio_priv(indio_dev);

	वापस stk8312_set_mode(data, data->mode | STK8312_MODE_ACTIVE);
पूर्ण

अटल पूर्णांक stk8312_buffer_postdisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा stk8312_data *data = iio_priv(indio_dev);

	वापस stk8312_set_mode(data, data->mode & (~STK8312_MODE_ACTIVE));
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops stk8312_buffer_setup_ops = अणु
	.preenable   = stk8312_buffer_preenable,
	.postdisable = stk8312_buffer_postdisable,
पूर्ण;

अटल पूर्णांक stk8312_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा iio_dev *indio_dev;
	काष्ठा stk8312_data *data;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev) अणु
		dev_err(&client->dev, "iio allocation failed!\n");
		वापस -ENOMEM;
	पूर्ण

	data = iio_priv(indio_dev);
	data->client = client;
	i2c_set_clientdata(client, indio_dev);
	mutex_init(&data->lock);

	indio_dev->info = &stk8312_info;
	indio_dev->name = STK8312_DRIVER_NAME;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = stk8312_channels;
	indio_dev->num_channels = ARRAY_SIZE(stk8312_channels);

	/* A software reset is recommended at घातer-on */
	ret = i2c_smbus_ग_लिखो_byte_data(data->client, STK8312_REG_RESET, 0x00);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed to reset sensor\n");
		वापस ret;
	पूर्ण
	data->sample_rate_idx = STK8312_SR_400HZ_IDX;
	ret = stk8312_set_range(data, STK8312_RNG_6G);
	अगर (ret < 0)
		वापस ret;

	ret = stk8312_set_mode(data,
			       STK8312_MODE_INT_AH_PP | STK8312_MODE_ACTIVE);
	अगर (ret < 0)
		वापस ret;

	अगर (client->irq > 0) अणु
		ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
						stk8312_data_rdy_trig_poll,
						शून्य,
						IRQF_TRIGGER_RISING |
						IRQF_ONESHOT,
						STK8312_IRQ_NAME,
						indio_dev);
		अगर (ret < 0) अणु
			dev_err(&client->dev, "request irq %d failed\n",
				client->irq);
			जाओ err_घातer_off;
		पूर्ण

		data->dपढ़ोy_trig = devm_iio_trigger_alloc(&client->dev,
							   "%s-dev%d",
							   indio_dev->name,
							   indio_dev->id);
		अगर (!data->dपढ़ोy_trig) अणु
			ret = -ENOMEM;
			जाओ err_घातer_off;
		पूर्ण

		data->dपढ़ोy_trig->ops = &stk8312_trigger_ops;
		iio_trigger_set_drvdata(data->dपढ़ोy_trig, indio_dev);
		ret = iio_trigger_रेजिस्टर(data->dपढ़ोy_trig);
		अगर (ret) अणु
			dev_err(&client->dev, "iio trigger register failed\n");
			जाओ err_घातer_off;
		पूर्ण
	पूर्ण

	ret = iio_triggered_buffer_setup(indio_dev,
					 iio_pollfunc_store_समय,
					 stk8312_trigger_handler,
					 &stk8312_buffer_setup_ops);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "iio triggered buffer setup failed\n");
		जाओ err_trigger_unरेजिस्टर;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "device_register failed\n");
		जाओ err_buffer_cleanup;
	पूर्ण

	वापस 0;

err_buffer_cleanup:
	iio_triggered_buffer_cleanup(indio_dev);
err_trigger_unरेजिस्टर:
	अगर (data->dपढ़ोy_trig)
		iio_trigger_unरेजिस्टर(data->dपढ़ोy_trig);
err_घातer_off:
	stk8312_set_mode(data, STK8312_MODE_STANDBY);
	वापस ret;
पूर्ण

अटल पूर्णांक stk8312_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा stk8312_data *data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);

	अगर (data->dपढ़ोy_trig)
		iio_trigger_unरेजिस्टर(data->dपढ़ोy_trig);

	वापस stk8312_set_mode(data, STK8312_MODE_STANDBY);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक stk8312_suspend(काष्ठा device *dev)
अणु
	काष्ठा stk8312_data *data;

	data = iio_priv(i2c_get_clientdata(to_i2c_client(dev)));

	वापस stk8312_set_mode(data, data->mode & (~STK8312_MODE_ACTIVE));
पूर्ण

अटल पूर्णांक stk8312_resume(काष्ठा device *dev)
अणु
	काष्ठा stk8312_data *data;

	data = iio_priv(i2c_get_clientdata(to_i2c_client(dev)));

	वापस stk8312_set_mode(data, data->mode | STK8312_MODE_ACTIVE);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(stk8312_pm_ops, stk8312_suspend, stk8312_resume);

#घोषणा STK8312_PM_OPS (&stk8312_pm_ops)
#अन्यथा
#घोषणा STK8312_PM_OPS शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id stk8312_i2c_id[] = अणु
	अणु"STK8312", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, stk8312_i2c_id);

अटल स्थिर काष्ठा acpi_device_id stk8312_acpi_id[] = अणु
	अणु"STK8312", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(acpi, stk8312_acpi_id);

अटल काष्ठा i2c_driver stk8312_driver = अणु
	.driver = अणु
		.name = STK8312_DRIVER_NAME,
		.pm = STK8312_PM_OPS,
		.acpi_match_table = ACPI_PTR(stk8312_acpi_id),
	पूर्ण,
	.probe =            stk8312_probe,
	.हटाओ =           stk8312_हटाओ,
	.id_table =         stk8312_i2c_id,
पूर्ण;

module_i2c_driver(stk8312_driver);

MODULE_AUTHOR("Tiberiu Breana <tiberiu.a.breana@intel.com>");
MODULE_DESCRIPTION("STK8312 3-Axis Accelerometer driver");
MODULE_LICENSE("GPL v2");
