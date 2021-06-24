<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * mag3110.c - Support क्रम Freescale MAG3110 magnetometer sensor
 *
 * Copyright (c) 2013 Peter Meerwald <pmeerw@pmeerw.net>
 *
 * (7-bit I2C slave address 0x0e)
 *
 * TODO: irq, user offset, oversampling, continuous mode
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/delay.h>
#समावेश <linux/regulator/consumer.h>

#घोषणा MAG3110_STATUS 0x00
#घोषणा MAG3110_OUT_X 0x01 /* MSB first */
#घोषणा MAG3110_OUT_Y 0x03
#घोषणा MAG3110_OUT_Z 0x05
#घोषणा MAG3110_WHO_AM_I 0x07
#घोषणा MAG3110_SYSMOD 0x08
#घोषणा MAG3110_OFF_X 0x09 /* MSB first */
#घोषणा MAG3110_OFF_Y 0x0b
#घोषणा MAG3110_OFF_Z 0x0d
#घोषणा MAG3110_DIE_TEMP 0x0f
#घोषणा MAG3110_CTRL_REG1 0x10
#घोषणा MAG3110_CTRL_REG2 0x11

#घोषणा MAG3110_STATUS_DRDY (BIT(2) | BIT(1) | BIT(0))

#घोषणा MAG3110_CTRL_DR_MASK (BIT(7) | BIT(6) | BIT(5))
#घोषणा MAG3110_CTRL_DR_SHIFT 5
#घोषणा MAG3110_CTRL_DR_DEFAULT 0

#घोषणा MAG3110_SYSMOD_MODE_MASK GENMASK(1, 0)

#घोषणा MAG3110_CTRL_TM BIT(1) /* trigger single measurement */
#घोषणा MAG3110_CTRL_AC BIT(0) /* continuous measurements */

#घोषणा MAG3110_CTRL_AUTO_MRST_EN BIT(7) /* magnetic स्वतः-reset */
#घोषणा MAG3110_CTRL_RAW BIT(5) /* measurements not user-offset corrected */

#घोषणा MAG3110_DEVICE_ID 0xc4

/* Each client has this additional data */
काष्ठा mag3110_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;
	u8 ctrl_reg1;
	पूर्णांक sleep_val;
	काष्ठा regulator *vdd_reg;
	काष्ठा regulator *vddio_reg;
	/* Ensure natural alignment of बारtamp */
	काष्ठा अणु
		__be16 channels[3];
		u8 temperature;
		s64 ts __aligned(8);
	पूर्ण scan;
पूर्ण;

अटल पूर्णांक mag3110_request(काष्ठा mag3110_data *data)
अणु
	पूर्णांक ret, tries = 150;

	अगर ((data->ctrl_reg1 & MAG3110_CTRL_AC) == 0) अणु
		/* trigger measurement */
		ret = i2c_smbus_ग_लिखो_byte_data(data->client, MAG3110_CTRL_REG1,
			data->ctrl_reg1 | MAG3110_CTRL_TM);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	जबतक (tries-- > 0) अणु
		ret = i2c_smbus_पढ़ो_byte_data(data->client, MAG3110_STATUS);
		अगर (ret < 0)
			वापस ret;
		/* रुको क्रम data पढ़ोy */
		अगर ((ret & MAG3110_STATUS_DRDY) == MAG3110_STATUS_DRDY)
			अवरोध;

		अगर (data->sleep_val <= 20)
			usleep_range(data->sleep_val * 250, data->sleep_val * 500);
		अन्यथा
			msleep(20);
	पूर्ण

	अगर (tries < 0) अणु
		dev_err(&data->client->dev, "data not ready\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mag3110_पढ़ो(काष्ठा mag3110_data *data, __be16 buf[3])
अणु
	पूर्णांक ret;

	mutex_lock(&data->lock);
	ret = mag3110_request(data);
	अगर (ret < 0) अणु
		mutex_unlock(&data->lock);
		वापस ret;
	पूर्ण
	ret = i2c_smbus_पढ़ो_i2c_block_data(data->client,
		MAG3110_OUT_X, 3 * माप(__be16), (u8 *) buf);
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार mag3110_show_पूर्णांक_plus_micros(अक्षर *buf,
	स्थिर पूर्णांक (*vals)[2], पूर्णांक n)
अणु
	माप_प्रकार len = 0;

	जबतक (n-- > 0)
		len += scnम_लिखो(buf + len, PAGE_SIZE - len,
			"%d.%06d ", vals[n][0], vals[n][1]);

	/* replace trailing space by newline */
	buf[len - 1] = '\n';

	वापस len;
पूर्ण

अटल पूर्णांक mag3110_get_पूर्णांक_plus_micros_index(स्थिर पूर्णांक (*vals)[2], पूर्णांक n,
					पूर्णांक val, पूर्णांक val2)
अणु
	जबतक (n-- > 0)
		अगर (val == vals[n][0] && val2 == vals[n][1])
			वापस n;

	वापस -EINVAL;
पूर्ण

अटल स्थिर पूर्णांक mag3110_samp_freq[8][2] = अणु
	अणु80, 0पूर्ण, अणु40, 0पूर्ण, अणु20, 0पूर्ण, अणु10, 0पूर्ण, अणु5, 0पूर्ण, अणु2, 500000पूर्ण,
	अणु1, 250000पूर्ण, अणु0, 625000पूर्ण
पूर्ण;

अटल sमाप_प्रकार mag3110_show_samp_freq_avail(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस mag3110_show_पूर्णांक_plus_micros(buf, mag3110_samp_freq, 8);
पूर्ण

अटल IIO_DEV_ATTR_SAMP_FREQ_AVAIL(mag3110_show_samp_freq_avail);

अटल पूर्णांक mag3110_get_samp_freq_index(काष्ठा mag3110_data *data,
	पूर्णांक val, पूर्णांक val2)
अणु
	वापस mag3110_get_पूर्णांक_plus_micros_index(mag3110_samp_freq, 8, val,
		val2);
पूर्ण

अटल पूर्णांक mag3110_calculate_sleep(काष्ठा mag3110_data *data)
अणु
	पूर्णांक ret, i = data->ctrl_reg1 >> MAG3110_CTRL_DR_SHIFT;

	अगर (mag3110_samp_freq[i][0] > 0)
		ret = 1000 / mag3110_samp_freq[i][0];
	अन्यथा
		ret = 1000;

	वापस ret == 0 ? 1 : ret;
पूर्ण

अटल पूर्णांक mag3110_standby(काष्ठा mag3110_data *data)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(data->client, MAG3110_CTRL_REG1,
		data->ctrl_reg1 & ~MAG3110_CTRL_AC);
पूर्ण

अटल पूर्णांक mag3110_रुको_standby(काष्ठा mag3110_data *data)
अणु
	पूर्णांक ret, tries = 30;

	/*
	 * Takes up to 1/ODR to come out of active mode पूर्णांकo stby
	 * Longest expected period is 12.5seconds.
	 * We'll sleep क्रम 500ms between checks
	 */
	जबतक (tries-- > 0) अणु
		ret = i2c_smbus_पढ़ो_byte_data(data->client, MAG3110_SYSMOD);
		अगर (ret < 0) अणु
			dev_err(&data->client->dev, "i2c error\n");
			वापस ret;
		पूर्ण
		/* रुको क्रम standby */
		अगर ((ret & MAG3110_SYSMOD_MODE_MASK) == 0)
			अवरोध;

		msleep_पूर्णांकerruptible(500);
	पूर्ण

	अगर (tries < 0) अणु
		dev_err(&data->client->dev, "device not entering standby mode\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mag3110_active(काष्ठा mag3110_data *data)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(data->client, MAG3110_CTRL_REG1,
					 data->ctrl_reg1);
पूर्ण

/* वापसs >0 अगर active, 0 अगर in standby and <0 on error */
अटल पूर्णांक mag3110_is_active(काष्ठा mag3110_data *data)
अणु
	पूर्णांक reg;

	reg = i2c_smbus_पढ़ो_byte_data(data->client, MAG3110_CTRL_REG1);
	अगर (reg < 0)
		वापस reg;

	वापस reg & MAG3110_CTRL_AC;
पूर्ण

अटल पूर्णांक mag3110_change_config(काष्ठा mag3110_data *data, u8 reg, u8 val)
अणु
	पूर्णांक ret;
	पूर्णांक is_active;

	mutex_lock(&data->lock);

	is_active = mag3110_is_active(data);
	अगर (is_active < 0) अणु
		ret = is_active;
		जाओ fail;
	पूर्ण

	/* config can only be changed when in standby */
	अगर (is_active > 0) अणु
		ret = mag3110_standby(data);
		अगर (ret < 0)
			जाओ fail;
	पूर्ण

	/*
	 * After coming out of active we must रुको क्रम the part
	 * to transition to STBY. This can take up to 1 /ODR to occur
	 */
	ret = mag3110_रुको_standby(data);
	अगर (ret < 0)
		जाओ fail;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, reg, val);
	अगर (ret < 0)
		जाओ fail;

	अगर (is_active > 0) अणु
		ret = mag3110_active(data);
		अगर (ret < 0)
			जाओ fail;
	पूर्ण

	ret = 0;
fail:
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक mag3110_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा mag3110_data *data = iio_priv(indio_dev);
	__be16 buffer[3];
	पूर्णांक i, ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;

		चयन (chan->type) अणु
		हाल IIO_MAGN: /* in 0.1 uT / LSB */
			ret = mag3110_पढ़ो(data, buffer);
			अगर (ret < 0)
				जाओ release;
			*val = sign_extend32(
				be16_to_cpu(buffer[chan->scan_index]), 15);
			ret = IIO_VAL_INT;
			अवरोध;
		हाल IIO_TEMP: /* in 1 C / LSB */
			mutex_lock(&data->lock);
			ret = mag3110_request(data);
			अगर (ret < 0) अणु
				mutex_unlock(&data->lock);
				जाओ release;
			पूर्ण
			ret = i2c_smbus_पढ़ो_byte_data(data->client,
				MAG3110_DIE_TEMP);
			mutex_unlock(&data->lock);
			अगर (ret < 0)
				जाओ release;
			*val = sign_extend32(ret, 7);
			ret = IIO_VAL_INT;
			अवरोध;
		शेष:
			ret = -EINVAL;
		पूर्ण
release:
		iio_device_release_direct_mode(indio_dev);
		वापस ret;

	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_MAGN:
			*val = 0;
			*val2 = 1000;
			वापस IIO_VAL_INT_PLUS_MICRO;
		हाल IIO_TEMP:
			*val = 1000;
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		i = data->ctrl_reg1 >> MAG3110_CTRL_DR_SHIFT;
		*val = mag3110_samp_freq[i][0];
		*val2 = mag3110_samp_freq[i][1];
		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_CALIBBIAS:
		ret = i2c_smbus_पढ़ो_word_swapped(data->client,
			MAG3110_OFF_X +	2 * chan->scan_index);
		अगर (ret < 0)
			वापस ret;
		*val = sign_extend32(ret >> 1, 14);
		वापस IIO_VAL_INT;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mag3110_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा mag3110_data *data = iio_priv(indio_dev);
	पूर्णांक rate, ret;

	ret = iio_device_claim_direct_mode(indio_dev);
	अगर (ret)
		वापस ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		rate = mag3110_get_samp_freq_index(data, val, val2);
		अगर (rate < 0) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		data->ctrl_reg1 &= 0xff & ~MAG3110_CTRL_DR_MASK
					& ~MAG3110_CTRL_AC;
		data->ctrl_reg1 |= rate << MAG3110_CTRL_DR_SHIFT;
		data->sleep_val = mag3110_calculate_sleep(data);
		अगर (data->sleep_val < 40)
			data->ctrl_reg1 |= MAG3110_CTRL_AC;

		ret = mag3110_change_config(data, MAG3110_CTRL_REG1,
					    data->ctrl_reg1);
		अवरोध;
	हाल IIO_CHAN_INFO_CALIBBIAS:
		अगर (val < -10000 || val > 10000) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		ret = i2c_smbus_ग_लिखो_word_swapped(data->client,
			MAG3110_OFF_X + 2 * chan->scan_index, val << 1);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	iio_device_release_direct_mode(indio_dev);
	वापस ret;
पूर्ण

अटल irqवापस_t mag3110_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा mag3110_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = mag3110_पढ़ो(data, data->scan.channels);
	अगर (ret < 0)
		जाओ करोne;

	अगर (test_bit(3, indio_dev->active_scan_mask)) अणु
		ret = i2c_smbus_पढ़ो_byte_data(data->client,
			MAG3110_DIE_TEMP);
		अगर (ret < 0)
			जाओ करोne;
		data->scan.temperature = ret;
	पूर्ण

	iio_push_to_buffers_with_बारtamp(indio_dev, &data->scan,
		iio_get_समय_ns(indio_dev));

करोne:
	iio_trigger_notअगरy_करोne(indio_dev->trig);
	वापस IRQ_HANDLED;
पूर्ण

#घोषणा MAG3110_CHANNEL(axis, idx) अणु \
	.type = IIO_MAGN, \
	.modअगरied = 1, \
	.channel2 = IIO_MOD_##axis, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | \
		BIT(IIO_CHAN_INFO_CALIBBIAS), \
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SAMP_FREQ) | \
		BIT(IIO_CHAN_INFO_SCALE), \
	.scan_index = idx, \
	.scan_type = अणु \
		.sign = 's', \
		.realbits = 16, \
		.storagebits = 16, \
		.endianness = IIO_BE, \
	पूर्ण, \
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec mag3110_channels[] = अणु
	MAG3110_CHANNEL(X, 0),
	MAG3110_CHANNEL(Y, 1),
	MAG3110_CHANNEL(Z, 2),
	अणु
		.type = IIO_TEMP,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SCALE),
		.scan_index = 3,
		.scan_type = अणु
			.sign = 's',
			.realbits = 8,
			.storagebits = 8,
			पूर्ण,
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(4),
पूर्ण;

अटल काष्ठा attribute *mag3110_attributes[] = अणु
	&iio_dev_attr_sampling_frequency_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group mag3110_group = अणु
	.attrs = mag3110_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info mag3110_info = अणु
	.attrs = &mag3110_group,
	.पढ़ो_raw = &mag3110_पढ़ो_raw,
	.ग_लिखो_raw = &mag3110_ग_लिखो_raw,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ mag3110_scan_masks[] = अणु0x7, 0xf, 0पूर्ण;

अटल पूर्णांक mag3110_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा mag3110_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);

	data->vdd_reg = devm_regulator_get(&client->dev, "vdd");
	अगर (IS_ERR(data->vdd_reg))
		वापस dev_err_probe(&client->dev, PTR_ERR(data->vdd_reg),
				     "failed to get VDD regulator!\n");

	data->vddio_reg = devm_regulator_get(&client->dev, "vddio");
	अगर (IS_ERR(data->vddio_reg))
		वापस dev_err_probe(&client->dev, PTR_ERR(data->vddio_reg),
				     "failed to get VDDIO regulator!\n");

	ret = regulator_enable(data->vdd_reg);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to enable VDD regulator!\n");
		वापस ret;
	पूर्ण

	ret = regulator_enable(data->vddio_reg);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to enable VDDIO regulator!\n");
		जाओ disable_regulator_vdd;
	पूर्ण

	ret = i2c_smbus_पढ़ो_byte_data(client, MAG3110_WHO_AM_I);
	अगर (ret < 0)
		जाओ disable_regulators;
	अगर (ret != MAG3110_DEVICE_ID) अणु
		ret = -ENODEV;
		जाओ disable_regulators;
	पूर्ण

	data->client = client;
	mutex_init(&data->lock);

	i2c_set_clientdata(client, indio_dev);
	indio_dev->info = &mag3110_info;
	indio_dev->name = id->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = mag3110_channels;
	indio_dev->num_channels = ARRAY_SIZE(mag3110_channels);
	indio_dev->available_scan_masks = mag3110_scan_masks;

	data->ctrl_reg1 = MAG3110_CTRL_DR_DEFAULT << MAG3110_CTRL_DR_SHIFT;
	data->sleep_val = mag3110_calculate_sleep(data);
	अगर (data->sleep_val < 40)
		data->ctrl_reg1 |= MAG3110_CTRL_AC;

	ret = mag3110_change_config(data, MAG3110_CTRL_REG1, data->ctrl_reg1);
	अगर (ret < 0)
		जाओ disable_regulators;

	ret = i2c_smbus_ग_लिखो_byte_data(client, MAG3110_CTRL_REG2,
		MAG3110_CTRL_AUTO_MRST_EN);
	अगर (ret < 0)
		जाओ standby_on_error;

	ret = iio_triggered_buffer_setup(indio_dev, शून्य,
		mag3110_trigger_handler, शून्य);
	अगर (ret < 0)
		जाओ standby_on_error;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0)
		जाओ buffer_cleanup;
	वापस 0;

buffer_cleanup:
	iio_triggered_buffer_cleanup(indio_dev);
standby_on_error:
	mag3110_standby(iio_priv(indio_dev));
disable_regulators:
	regulator_disable(data->vddio_reg);
disable_regulator_vdd:
	regulator_disable(data->vdd_reg);

	वापस ret;
पूर्ण

अटल पूर्णांक mag3110_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा mag3110_data *data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);
	mag3110_standby(iio_priv(indio_dev));
	regulator_disable(data->vddio_reg);
	regulator_disable(data->vdd_reg);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mag3110_suspend(काष्ठा device *dev)
अणु
	काष्ठा mag3110_data *data = iio_priv(i2c_get_clientdata(
		to_i2c_client(dev)));
	पूर्णांक ret;

	ret = mag3110_standby(iio_priv(i2c_get_clientdata(
		to_i2c_client(dev))));
	अगर (ret)
		वापस ret;

	ret = regulator_disable(data->vddio_reg);
	अगर (ret) अणु
		dev_err(dev, "failed to disable VDDIO regulator\n");
		वापस ret;
	पूर्ण

	ret = regulator_disable(data->vdd_reg);
	अगर (ret) अणु
		dev_err(dev, "failed to disable VDD regulator\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mag3110_resume(काष्ठा device *dev)
अणु
	काष्ठा mag3110_data *data = iio_priv(i2c_get_clientdata(
		to_i2c_client(dev)));
	पूर्णांक ret;

	ret = regulator_enable(data->vdd_reg);
	अगर (ret) अणु
		dev_err(dev, "failed to enable VDD regulator\n");
		वापस ret;
	पूर्ण

	ret = regulator_enable(data->vddio_reg);
	अगर (ret) अणु
		dev_err(dev, "failed to enable VDDIO regulator\n");
		regulator_disable(data->vdd_reg);
		वापस ret;
	पूर्ण

	वापस i2c_smbus_ग_लिखो_byte_data(data->client, MAG3110_CTRL_REG1,
		data->ctrl_reg1);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(mag3110_pm_ops, mag3110_suspend, mag3110_resume);
#घोषणा MAG3110_PM_OPS (&mag3110_pm_ops)
#अन्यथा
#घोषणा MAG3110_PM_OPS शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id mag3110_id[] = अणु
	अणु "mag3110", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mag3110_id);

अटल स्थिर काष्ठा of_device_id mag3110_of_match[] = अणु
	अणु .compatible = "fsl,mag3110" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mag3110_of_match);

अटल काष्ठा i2c_driver mag3110_driver = अणु
	.driver = अणु
		.name	= "mag3110",
		.of_match_table = mag3110_of_match,
		.pm	= MAG3110_PM_OPS,
	पूर्ण,
	.probe = mag3110_probe,
	.हटाओ = mag3110_हटाओ,
	.id_table = mag3110_id,
पूर्ण;
module_i2c_driver(mag3110_driver);

MODULE_AUTHOR("Peter Meerwald <pmeerw@pmeerw.net>");
MODULE_DESCRIPTION("Freescale MAG3110 magnetometer driver");
MODULE_LICENSE("GPL");
