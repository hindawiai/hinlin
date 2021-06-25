<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Sensortek STK8BA50 3-Axis Accelerometer
 *
 * Copyright (c) 2015, Intel Corporation.
 *
 * STK8BA50 7-bit I2C address: 0x18.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/trigger_consumer.h>

#घोषणा STK8BA50_REG_XOUT			0x02
#घोषणा STK8BA50_REG_YOUT			0x04
#घोषणा STK8BA50_REG_ZOUT			0x06
#घोषणा STK8BA50_REG_RANGE			0x0F
#घोषणा STK8BA50_REG_BWSEL			0x10
#घोषणा STK8BA50_REG_POWMODE			0x11
#घोषणा STK8BA50_REG_SWRST			0x14
#घोषणा STK8BA50_REG_INTEN2			0x17
#घोषणा STK8BA50_REG_INTMAP2			0x1A

#घोषणा STK8BA50_MODE_NORMAL			0
#घोषणा STK8BA50_MODE_SUSPEND			1
#घोषणा STK8BA50_MODE_POWERBIT			BIT(7)
#घोषणा STK8BA50_DATA_SHIFT			6
#घोषणा STK8BA50_RESET_CMD			0xB6
#घोषणा STK8BA50_SR_1792HZ_IDX			7
#घोषणा STK8BA50_DREADY_INT_MASK		0x10
#घोषणा STK8BA50_DREADY_INT_MAP			0x81
#घोषणा STK8BA50_ALL_CHANNEL_MASK		7
#घोषणा STK8BA50_ALL_CHANNEL_SIZE		6

#घोषणा STK8BA50_DRIVER_NAME			"stk8ba50"
#घोषणा STK8BA50_IRQ_NAME			"stk8ba50_event"

#घोषणा STK8BA50_SCALE_AVAIL			"0.0384 0.0767 0.1534 0.3069"

/*
 * The accelerometer has four measurement ranges:
 * +/-2g; +/-4g; +/-8g; +/-16g
 *
 * Acceleration values are 10-bit, 2's complement.
 * Scales are calculated as following:
 *
 * scale1 = (2 + 2) * 9.81 / (2^10 - 1)   = 0.0384
 * scale2 = (4 + 4) * 9.81 / (2^10 - 1)   = 0.0767
 * etc.
 *
 * Scales are stored in this क्रमmat:
 * अणु <रेजिस्टर value>, <scale value> पूर्ण
 *
 * Locally, the range is stored as a table index.
 */
अटल स्थिर काष्ठा अणु
	u8 reg_val;
	u32 scale_val;
पूर्ण stk8ba50_scale_table[] = अणु
	अणु3, 38400पूर्ण, अणु5, 76700पूर्ण, अणु8, 153400पूर्ण, अणु12, 306900पूर्ण
पूर्ण;

/* Sample rates are stored as अणु <रेजिस्टर value>, <Hz value> पूर्ण */
अटल स्थिर काष्ठा अणु
	u8 reg_val;
	u16 samp_freq;
पूर्ण stk8ba50_samp_freq_table[] = अणु
	अणु0x08, 14पूर्ण,  अणु0x09, 25पूर्ण,  अणु0x0A, 56पूर्ण,  अणु0x0B, 112पूर्ण,
	अणु0x0C, 224पूर्ण, अणु0x0D, 448पूर्ण, अणु0x0E, 896पूर्ण, अणु0x0F, 1792पूर्ण
पूर्ण;

/* Used to map scan mask bits to their corresponding channel रेजिस्टर. */
अटल स्थिर पूर्णांक stk8ba50_channel_table[] = अणु
	STK8BA50_REG_XOUT,
	STK8BA50_REG_YOUT,
	STK8BA50_REG_ZOUT
पूर्ण;

काष्ठा stk8ba50_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;
	पूर्णांक range;
	u8 sample_rate_idx;
	काष्ठा iio_trigger *dपढ़ोy_trig;
	bool dपढ़ोy_trigger_on;
	/*
	 * 3 x 16-bit channels (10-bit data, 6-bit padding) +
	 * 1 x 16 padding +
	 * 4 x 16 64-bit बारtamp
	 */
	s16 buffer[8];
पूर्ण;

#घोषणा STK8BA50_ACCEL_CHANNEL(index, reg, axis) अणु			\
	.type = IIO_ACCEL,						\
	.address = reg,							\
	.modअगरied = 1,							\
	.channel2 = IIO_MOD_##axis,					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),			\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),		\
				    BIT(IIO_CHAN_INFO_SAMP_FREQ),	\
	.scan_index = index,						\
	.scan_type = अणु							\
		.sign = 's',						\
		.realbits = 10,						\
		.storagebits = 16,					\
		.shअगरt = STK8BA50_DATA_SHIFT,				\
		.endianness = IIO_CPU,					\
	पूर्ण,								\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec stk8ba50_channels[] = अणु
	STK8BA50_ACCEL_CHANNEL(0, STK8BA50_REG_XOUT, X),
	STK8BA50_ACCEL_CHANNEL(1, STK8BA50_REG_YOUT, Y),
	STK8BA50_ACCEL_CHANNEL(2, STK8BA50_REG_ZOUT, Z),
	IIO_CHAN_SOFT_TIMESTAMP(3),
पूर्ण;

अटल IIO_CONST_ATTR(in_accel_scale_available, STK8BA50_SCALE_AVAIL);

अटल IIO_CONST_ATTR_SAMP_FREQ_AVAIL("14 25 56 112 224 448 896 1792");

अटल काष्ठा attribute *stk8ba50_attributes[] = अणु
	&iio_स्थिर_attr_in_accel_scale_available.dev_attr.attr,
	&iio_स्थिर_attr_sampling_frequency_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group stk8ba50_attribute_group = अणु
	.attrs = stk8ba50_attributes
पूर्ण;

अटल पूर्णांक stk8ba50_पढ़ो_accel(काष्ठा stk8ba50_data *data, u8 reg)
अणु
	पूर्णांक ret;
	काष्ठा i2c_client *client = data->client;

	ret = i2c_smbus_पढ़ो_word_data(client, reg);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "register read failed\n");
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक stk8ba50_data_rdy_trigger_set_state(काष्ठा iio_trigger *trig,
					       bool state)
अणु
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	काष्ठा stk8ba50_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	अगर (state)
		ret = i2c_smbus_ग_लिखो_byte_data(data->client,
			STK8BA50_REG_INTEN2, STK8BA50_DREADY_INT_MASK);
	अन्यथा
		ret = i2c_smbus_ग_लिखो_byte_data(data->client,
			STK8BA50_REG_INTEN2, 0x00);

	अगर (ret < 0)
		dev_err(&data->client->dev, "failed to set trigger state\n");
	अन्यथा
		data->dपढ़ोy_trigger_on = state;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops stk8ba50_trigger_ops = अणु
	.set_trigger_state = stk8ba50_data_rdy_trigger_set_state,
पूर्ण;

अटल पूर्णांक stk8ba50_set_घातer(काष्ठा stk8ba50_data *data, bool mode)
अणु
	पूर्णांक ret;
	u8 masked_reg;
	काष्ठा i2c_client *client = data->client;

	ret = i2c_smbus_पढ़ो_byte_data(client, STK8BA50_REG_POWMODE);
	अगर (ret < 0)
		जाओ निकास_err;

	अगर (mode)
		masked_reg = ret | STK8BA50_MODE_POWERBIT;
	अन्यथा
		masked_reg = ret & (~STK8BA50_MODE_POWERBIT);

	ret = i2c_smbus_ग_लिखो_byte_data(client, STK8BA50_REG_POWMODE,
					masked_reg);
	अगर (ret < 0)
		जाओ निकास_err;

	वापस ret;

निकास_err:
	dev_err(&client->dev, "failed to change sensor mode\n");
	वापस ret;
पूर्ण

अटल पूर्णांक stk8ba50_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा stk8ba50_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (iio_buffer_enabled(indio_dev))
			वापस -EBUSY;
		mutex_lock(&data->lock);
		ret = stk8ba50_set_घातer(data, STK8BA50_MODE_NORMAL);
		अगर (ret < 0) अणु
			mutex_unlock(&data->lock);
			वापस -EINVAL;
		पूर्ण
		ret = stk8ba50_पढ़ो_accel(data, chan->address);
		अगर (ret < 0) अणु
			stk8ba50_set_घातer(data, STK8BA50_MODE_SUSPEND);
			mutex_unlock(&data->lock);
			वापस -EINVAL;
		पूर्ण
		*val = sign_extend32(ret >> STK8BA50_DATA_SHIFT, 9);
		stk8ba50_set_घातer(data, STK8BA50_MODE_SUSPEND);
		mutex_unlock(&data->lock);
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = 0;
		*val2 = stk8ba50_scale_table[data->range].scale_val;
		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*val = stk8ba50_samp_freq_table
				[data->sample_rate_idx].samp_freq;
		*val2 = 0;
		वापस IIO_VAL_INT;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक stk8ba50_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan,
			      पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	पूर्णांक ret;
	पूर्णांक i;
	पूर्णांक index = -1;
	काष्ठा stk8ba50_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		अगर (val != 0)
			वापस -EINVAL;

		क्रम (i = 0; i < ARRAY_SIZE(stk8ba50_scale_table); i++)
			अगर (val2 == stk8ba50_scale_table[i].scale_val) अणु
				index = i;
				अवरोध;
			पूर्ण
		अगर (index < 0)
			वापस -EINVAL;

		ret = i2c_smbus_ग_लिखो_byte_data(data->client,
				STK8BA50_REG_RANGE,
				stk8ba50_scale_table[index].reg_val);
		अगर (ret < 0)
			dev_err(&data->client->dev,
					"failed to set measurement range\n");
		अन्यथा
			data->range = index;

		वापस ret;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		क्रम (i = 0; i < ARRAY_SIZE(stk8ba50_samp_freq_table); i++)
			अगर (val == stk8ba50_samp_freq_table[i].samp_freq) अणु
				index = i;
				अवरोध;
			पूर्ण
		अगर (index < 0)
			वापस -EINVAL;

		ret = i2c_smbus_ग_लिखो_byte_data(data->client,
				STK8BA50_REG_BWSEL,
				stk8ba50_samp_freq_table[index].reg_val);
		अगर (ret < 0)
			dev_err(&data->client->dev,
					"failed to set sampling rate\n");
		अन्यथा
			data->sample_rate_idx = index;

		वापस ret;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info stk8ba50_info = अणु
	.पढ़ो_raw		= stk8ba50_पढ़ो_raw,
	.ग_लिखो_raw		= stk8ba50_ग_लिखो_raw,
	.attrs			= &stk8ba50_attribute_group,
पूर्ण;

अटल irqवापस_t stk8ba50_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा stk8ba50_data *data = iio_priv(indio_dev);
	पूर्णांक bit, ret, i = 0;

	mutex_lock(&data->lock);
	/*
	 * Do a bulk पढ़ो अगर all channels are requested,
	 * from 0x02 (XOUT1) to 0x07 (ZOUT2)
	 */
	अगर (*(indio_dev->active_scan_mask) == STK8BA50_ALL_CHANNEL_MASK) अणु
		ret = i2c_smbus_पढ़ो_i2c_block_data(data->client,
						    STK8BA50_REG_XOUT,
						    STK8BA50_ALL_CHANNEL_SIZE,
						    (u8 *)data->buffer);
		अगर (ret < STK8BA50_ALL_CHANNEL_SIZE) अणु
			dev_err(&data->client->dev, "register read failed\n");
			जाओ err;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम_each_set_bit(bit, indio_dev->active_scan_mask,
				 indio_dev->masklength) अणु
			ret = stk8ba50_पढ़ो_accel(data,
						  stk8ba50_channel_table[bit]);
			अगर (ret < 0)
				जाओ err;

			data->buffer[i++] = ret;
		पूर्ण
	पूर्ण
	iio_push_to_buffers_with_बारtamp(indio_dev, data->buffer,
					   pf->बारtamp);
err:
	mutex_unlock(&data->lock);
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t stk8ba50_data_rdy_trig_poll(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा stk8ba50_data *data = iio_priv(indio_dev);

	अगर (data->dपढ़ोy_trigger_on)
		iio_trigger_poll(data->dपढ़ोy_trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक stk8ba50_buffer_preenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा stk8ba50_data *data = iio_priv(indio_dev);

	वापस stk8ba50_set_घातer(data, STK8BA50_MODE_NORMAL);
पूर्ण

अटल पूर्णांक stk8ba50_buffer_postdisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा stk8ba50_data *data = iio_priv(indio_dev);

	वापस stk8ba50_set_घातer(data, STK8BA50_MODE_SUSPEND);
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops stk8ba50_buffer_setup_ops = अणु
	.preenable   = stk8ba50_buffer_preenable,
	.postdisable = stk8ba50_buffer_postdisable,
पूर्ण;

अटल पूर्णांक stk8ba50_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा iio_dev *indio_dev;
	काष्ठा stk8ba50_data *data;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev) अणु
		dev_err(&client->dev, "iio allocation failed!\n");
		वापस -ENOMEM;
	पूर्ण

	data = iio_priv(indio_dev);
	data->client = client;
	i2c_set_clientdata(client, indio_dev);
	mutex_init(&data->lock);

	indio_dev->info = &stk8ba50_info;
	indio_dev->name = STK8BA50_DRIVER_NAME;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = stk8ba50_channels;
	indio_dev->num_channels = ARRAY_SIZE(stk8ba50_channels);

	/* Reset all रेजिस्टरs on startup */
	ret = i2c_smbus_ग_लिखो_byte_data(client,
			STK8BA50_REG_SWRST, STK8BA50_RESET_CMD);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed to reset sensor\n");
		जाओ err_घातer_off;
	पूर्ण

	/* The शेष range is +/-2g */
	data->range = 0;

	/* The शेष sampling rate is 1792 Hz (maximum) */
	data->sample_rate_idx = STK8BA50_SR_1792HZ_IDX;

	/* Set up पूर्णांकerrupts */
	ret = i2c_smbus_ग_लिखो_byte_data(client,
			STK8BA50_REG_INTEN2, STK8BA50_DREADY_INT_MASK);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed to set up interrupts\n");
		जाओ err_घातer_off;
	पूर्ण
	ret = i2c_smbus_ग_लिखो_byte_data(client,
			STK8BA50_REG_INTMAP2, STK8BA50_DREADY_INT_MAP);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed to set up interrupts\n");
		जाओ err_घातer_off;
	पूर्ण

	अगर (client->irq > 0) अणु
		ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
						stk8ba50_data_rdy_trig_poll,
						शून्य,
						IRQF_TRIGGER_RISING |
						IRQF_ONESHOT,
						STK8BA50_IRQ_NAME,
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

		data->dपढ़ोy_trig->ops = &stk8ba50_trigger_ops;
		iio_trigger_set_drvdata(data->dपढ़ोy_trig, indio_dev);
		ret = iio_trigger_रेजिस्टर(data->dपढ़ोy_trig);
		अगर (ret) अणु
			dev_err(&client->dev, "iio trigger register failed\n");
			जाओ err_घातer_off;
		पूर्ण
	पूर्ण

	ret = iio_triggered_buffer_setup(indio_dev,
					 iio_pollfunc_store_समय,
					 stk8ba50_trigger_handler,
					 &stk8ba50_buffer_setup_ops);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "iio triggered buffer setup failed\n");
		जाओ err_trigger_unरेजिस्टर;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "device_register failed\n");
		जाओ err_buffer_cleanup;
	पूर्ण

	वापस ret;

err_buffer_cleanup:
	iio_triggered_buffer_cleanup(indio_dev);
err_trigger_unरेजिस्टर:
	अगर (data->dपढ़ोy_trig)
		iio_trigger_unरेजिस्टर(data->dपढ़ोy_trig);
err_घातer_off:
	stk8ba50_set_घातer(data, STK8BA50_MODE_SUSPEND);
	वापस ret;
पूर्ण

अटल पूर्णांक stk8ba50_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा stk8ba50_data *data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);

	अगर (data->dपढ़ोy_trig)
		iio_trigger_unरेजिस्टर(data->dपढ़ोy_trig);

	वापस stk8ba50_set_घातer(data, STK8BA50_MODE_SUSPEND);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक stk8ba50_suspend(काष्ठा device *dev)
अणु
	काष्ठा stk8ba50_data *data;

	data = iio_priv(i2c_get_clientdata(to_i2c_client(dev)));

	वापस stk8ba50_set_घातer(data, STK8BA50_MODE_SUSPEND);
पूर्ण

अटल पूर्णांक stk8ba50_resume(काष्ठा device *dev)
अणु
	काष्ठा stk8ba50_data *data;

	data = iio_priv(i2c_get_clientdata(to_i2c_client(dev)));

	वापस stk8ba50_set_घातer(data, STK8BA50_MODE_NORMAL);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(stk8ba50_pm_ops, stk8ba50_suspend, stk8ba50_resume);

#घोषणा STK8BA50_PM_OPS (&stk8ba50_pm_ops)
#अन्यथा
#घोषणा STK8BA50_PM_OPS शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id stk8ba50_i2c_id[] = अणु
	अणु"stk8ba50", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, stk8ba50_i2c_id);

अटल स्थिर काष्ठा acpi_device_id stk8ba50_acpi_id[] = अणु
	अणु"STK8BA50", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(acpi, stk8ba50_acpi_id);

अटल काष्ठा i2c_driver stk8ba50_driver = अणु
	.driver = अणु
		.name = "stk8ba50",
		.pm = STK8BA50_PM_OPS,
		.acpi_match_table = ACPI_PTR(stk8ba50_acpi_id),
	पूर्ण,
	.probe =            stk8ba50_probe,
	.हटाओ =           stk8ba50_हटाओ,
	.id_table =         stk8ba50_i2c_id,
पूर्ण;

module_i2c_driver(stk8ba50_driver);

MODULE_AUTHOR("Tiberiu Breana <tiberiu.a.breana@intel.com>");
MODULE_DESCRIPTION("STK8BA50 3-Axis Accelerometer driver");
MODULE_LICENSE("GPL v2");
