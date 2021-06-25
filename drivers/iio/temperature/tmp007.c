<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * पंचांगp007.c - Support क्रम TI TMP007 IR thermopile sensor with पूर्णांकegrated math engine
 *
 * Copyright (c) 2017 Manivannan Sadhasivam <manivannanece23@gmail.com>
 *
 * Driver क्रम the Texas Instruments I2C 16-bit IR thermopile sensor
 *
 * (7-bit I2C slave address (0x40 - 0x47), changeable via ADR pins)
 *
 * Note:
 * 1. This driver assumes that the sensor has been calibrated beक्रमehand
 * 2. Limit threshold events are enabled at the start
 * 3. Operating mode: INT
 */

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/pm.h>
#समावेश <linux/bitops.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/events.h>

#घोषणा TMP007_TDIE 0x01
#घोषणा TMP007_CONFIG 0x02
#घोषणा TMP007_TOBJECT 0x03
#घोषणा TMP007_STATUS 0x04
#घोषणा TMP007_STATUS_MASK 0x05
#घोषणा TMP007_TOBJ_HIGH_LIMIT 0x06
#घोषणा TMP007_TOBJ_LOW_LIMIT 0x07
#घोषणा TMP007_TDIE_HIGH_LIMIT 0x08
#घोषणा TMP007_TDIE_LOW_LIMIT 0x09
#घोषणा TMP007_MANUFACTURER_ID 0x1e
#घोषणा TMP007_DEVICE_ID 0x1f

#घोषणा TMP007_CONFIG_CONV_EN BIT(12)
#घोषणा TMP007_CONFIG_TC_EN BIT(6)
#घोषणा TMP007_CONFIG_CR_MASK GENMASK(11, 9)
#घोषणा TMP007_CONFIG_ALERT_EN BIT(8)
#घोषणा TMP007_CONFIG_CR_SHIFT 9

/* Status रेजिस्टर flags */
#घोषणा TMP007_STATUS_ALERT BIT(15)
#घोषणा TMP007_STATUS_CONV_READY BIT(14)
#घोषणा TMP007_STATUS_OHF BIT(13)
#घोषणा TMP007_STATUS_OLF BIT(12)
#घोषणा TMP007_STATUS_LHF BIT(11)
#घोषणा TMP007_STATUS_LLF BIT(10)
#घोषणा TMP007_STATUS_DATA_VALID BIT(9)

#घोषणा TMP007_MANUFACTURER_MAGIC 0x5449
#घोषणा TMP007_DEVICE_MAGIC 0x0078

#घोषणा TMP007_TEMP_SHIFT 2

काष्ठा पंचांगp007_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;
	u16 config;
	u16 status_mask;
पूर्ण;

अटल स्थिर पूर्णांक पंचांगp007_avgs[5][2] = अणु अणु4, 0पूर्ण, अणु2, 0पूर्ण, अणु1, 0पूर्ण,
					अणु0, 500000पूर्ण, अणु0, 250000पूर्ण पूर्ण;

अटल पूर्णांक पंचांगp007_पढ़ो_temperature(काष्ठा पंचांगp007_data *data, u8 reg)
अणु
	s32 ret;
	पूर्णांक tries = 50;

	जबतक (tries-- > 0) अणु
		ret = i2c_smbus_पढ़ो_word_swapped(data->client,
			TMP007_STATUS);
		अगर (ret < 0)
			वापस ret;
		अगर ((ret & TMP007_STATUS_CONV_READY) &&
			!(ret & TMP007_STATUS_DATA_VALID))
				अवरोध;
		msleep(100);
	पूर्ण

	अगर (tries < 0)
		वापस -EIO;

	वापस i2c_smbus_पढ़ो_word_swapped(data->client, reg);
पूर्ण

अटल पूर्णांक पंचांगp007_घातerकरोwn(काष्ठा पंचांगp007_data *data)
अणु
	वापस i2c_smbus_ग_लिखो_word_swapped(data->client, TMP007_CONFIG,
			data->config & ~TMP007_CONFIG_CONV_EN);
पूर्ण

अटल पूर्णांक पंचांगp007_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
		काष्ठा iio_chan_spec स्थिर *channel, पूर्णांक *val,
		पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा पंचांगp007_data *data = iio_priv(indio_dev);
	s32 ret;
	पूर्णांक conv_rate;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		चयन (channel->channel2) अणु
		हाल IIO_MOD_TEMP_AMBIENT: /* LSB: 0.03125 degree Celsius */
			ret = i2c_smbus_पढ़ो_word_swapped(data->client, TMP007_TDIE);
			अगर (ret < 0)
				वापस ret;
			अवरोध;
		हाल IIO_MOD_TEMP_OBJECT:
			ret = पंचांगp007_पढ़ो_temperature(data, TMP007_TOBJECT);
			अगर (ret < 0)
				वापस ret;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		*val = sign_extend32(ret, 15) >> TMP007_TEMP_SHIFT;

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = 31;
		*val2 = 250000;

		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		conv_rate = (data->config & TMP007_CONFIG_CR_MASK)
				>> TMP007_CONFIG_CR_SHIFT;
		*val = पंचांगp007_avgs[conv_rate][0];
		*val2 = पंचांगp007_avgs[conv_rate][1];

		वापस IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक पंचांगp007_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
		काष्ठा iio_chan_spec स्थिर *channel, पूर्णांक val,
		पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा पंचांगp007_data *data = iio_priv(indio_dev);
	पूर्णांक i;
	u16 पंचांगp;

	अगर (mask == IIO_CHAN_INFO_SAMP_FREQ) अणु
		क्रम (i = 0; i < ARRAY_SIZE(पंचांगp007_avgs); i++) अणु
			अगर ((val == पंचांगp007_avgs[i][0]) &&
			(val2 == पंचांगp007_avgs[i][1])) अणु
				पंचांगp = data->config & ~TMP007_CONFIG_CR_MASK;
				पंचांगp |= (i << TMP007_CONFIG_CR_SHIFT);

				वापस i2c_smbus_ग_लिखो_word_swapped(data->client,
								TMP007_CONFIG,
								data->config = पंचांगp);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल irqवापस_t पंचांगp007_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा पंचांगp007_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_word_swapped(data->client, TMP007_STATUS);
	अगर ((ret < 0) || !(ret & (TMP007_STATUS_OHF | TMP007_STATUS_OLF |
				TMP007_STATUS_LHF | TMP007_STATUS_LLF)))
		वापस IRQ_NONE;

	अगर (ret & TMP007_STATUS_OHF)
		iio_push_event(indio_dev,
				IIO_MOD_EVENT_CODE(IIO_TEMP, 0,
					IIO_MOD_TEMP_OBJECT,
					IIO_EV_TYPE_THRESH,
					IIO_EV_सूची_RISING),
				iio_get_समय_ns(indio_dev));

	अगर (ret & TMP007_STATUS_OLF)
		iio_push_event(indio_dev,
				IIO_MOD_EVENT_CODE(IIO_TEMP, 0,
					IIO_MOD_TEMP_OBJECT,
					IIO_EV_TYPE_THRESH,
					IIO_EV_सूची_FALLING),
				iio_get_समय_ns(indio_dev));

	अगर (ret & TMP007_STATUS_LHF)
		iio_push_event(indio_dev,
				IIO_MOD_EVENT_CODE(IIO_TEMP, 0,
					IIO_MOD_TEMP_AMBIENT,
					IIO_EV_TYPE_THRESH,
					IIO_EV_सूची_RISING),
				iio_get_समय_ns(indio_dev));

	अगर (ret & TMP007_STATUS_LLF)
		iio_push_event(indio_dev,
				IIO_MOD_EVENT_CODE(IIO_TEMP, 0,
					IIO_MOD_TEMP_AMBIENT,
					IIO_EV_TYPE_THRESH,
					IIO_EV_सूची_FALLING),
				iio_get_समय_ns(indio_dev));

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक पंचांगp007_ग_लिखो_event_config(काष्ठा iio_dev *indio_dev,
		स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
		क्रमागत iio_event_direction dir, पूर्णांक state)
अणु
	काष्ठा पंचांगp007_data *data = iio_priv(indio_dev);
	अचिन्हित पूर्णांक status_mask;
	पूर्णांक ret;

	चयन (chan->channel2) अणु
	हाल IIO_MOD_TEMP_AMBIENT:
	अगर (dir == IIO_EV_सूची_RISING)
			status_mask = TMP007_STATUS_LHF;
		अन्यथा
			status_mask = TMP007_STATUS_LLF;
		अवरोध;
	हाल IIO_MOD_TEMP_OBJECT:
		अगर (dir == IIO_EV_सूची_RISING)
			status_mask = TMP007_STATUS_OHF;
		अन्यथा
			status_mask = TMP007_STATUS_OLF;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&data->lock);
	ret = i2c_smbus_पढ़ो_word_swapped(data->client, TMP007_STATUS_MASK);
	mutex_unlock(&data->lock);
	अगर (ret < 0)
		वापस ret;

	अगर (state)
		ret |= status_mask;
	अन्यथा
		ret &= ~status_mask;

	वापस i2c_smbus_ग_लिखो_word_swapped(data->client, TMP007_STATUS_MASK,
					data->status_mask = ret);
पूर्ण

अटल पूर्णांक पंचांगp007_पढ़ो_event_config(काष्ठा iio_dev *indio_dev,
		स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
		क्रमागत iio_event_direction dir)
अणु
	काष्ठा पंचांगp007_data *data = iio_priv(indio_dev);
	अचिन्हित पूर्णांक mask;

	चयन (chan->channel2) अणु
	हाल IIO_MOD_TEMP_AMBIENT:
		अगर (dir == IIO_EV_सूची_RISING)
			mask = TMP007_STATUS_LHF;
		अन्यथा
			mask = TMP007_STATUS_LLF;
		अवरोध;
	हाल IIO_MOD_TEMP_OBJECT:
		अगर (dir == IIO_EV_सूची_RISING)
			mask = TMP007_STATUS_OHF;
		अन्यथा
			mask = TMP007_STATUS_OLF;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस !!(data->status_mask & mask);
पूर्ण

अटल पूर्णांक पंचांगp007_पढ़ो_thresh(काष्ठा iio_dev *indio_dev,
		स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
		क्रमागत iio_event_direction dir, क्रमागत iio_event_info info,
		पूर्णांक *val, पूर्णांक *val2)
अणु
	काष्ठा पंचांगp007_data *data = iio_priv(indio_dev);
	पूर्णांक ret;
	u8 reg;

	चयन (chan->channel2) अणु
	हाल IIO_MOD_TEMP_AMBIENT: /* LSB: 0.5 degree Celsius */
		अगर (dir == IIO_EV_सूची_RISING)
			reg = TMP007_TDIE_HIGH_LIMIT;
		अन्यथा
			reg = TMP007_TDIE_LOW_LIMIT;
		अवरोध;
	हाल IIO_MOD_TEMP_OBJECT:
		अगर (dir == IIO_EV_सूची_RISING)
			reg = TMP007_TOBJ_HIGH_LIMIT;
	अन्यथा
			reg = TMP007_TOBJ_LOW_LIMIT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = i2c_smbus_पढ़ो_word_swapped(data->client, reg);
	अगर (ret < 0)
		वापस ret;

	/* Shअगरt length 7 bits = 6(15:6) + 1(0.5 LSB) */
	*val = sign_extend32(ret, 15) >> 7;

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक पंचांगp007_ग_लिखो_thresh(काष्ठा iio_dev *indio_dev,
		स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
		क्रमागत iio_event_direction dir, क्रमागत iio_event_info info,
		पूर्णांक val, पूर्णांक val2)
अणु
	काष्ठा पंचांगp007_data *data = iio_priv(indio_dev);
	u8 reg;

	चयन (chan->channel2) अणु
	हाल IIO_MOD_TEMP_AMBIENT:
		अगर (dir == IIO_EV_सूची_RISING)
			reg = TMP007_TDIE_HIGH_LIMIT;
		अन्यथा
			reg = TMP007_TDIE_LOW_LIMIT;
		अवरोध;
	हाल IIO_MOD_TEMP_OBJECT:
		अगर (dir == IIO_EV_सूची_RISING)
			reg = TMP007_TOBJ_HIGH_LIMIT;
		अन्यथा
			reg = TMP007_TOBJ_LOW_LIMIT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Full scale threshold value is +/- 256 degree Celsius */
	अगर (val < -256 || val > 255)
		वापस -EINVAL;

	/* Shअगरt length 7 bits = 6(15:6) + 1(0.5 LSB) */
	वापस i2c_smbus_ग_लिखो_word_swapped(data->client, reg, (val << 7));
पूर्ण

अटल IIO_CONST_ATTR(sampling_frequency_available, "4 2 1 0.5 0.25");

अटल काष्ठा attribute *पंचांगp007_attributes[] = अणु
	&iio_स्थिर_attr_sampling_frequency_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group पंचांगp007_attribute_group = अणु
	.attrs = पंचांगp007_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_event_spec पंचांगp007_obj_event[] = अणु
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_RISING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE) |
			BIT(IIO_EV_INFO_ENABLE),
	पूर्ण,
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_FALLING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE) |
			BIT(IIO_EV_INFO_ENABLE),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_event_spec पंचांगp007_die_event[] = अणु
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_RISING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE) |
			BIT(IIO_EV_INFO_ENABLE),
	पूर्ण,
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_FALLING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE) |
			BIT(IIO_EV_INFO_ENABLE),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec पंचांगp007_channels[] = अणु
	अणु
		.type = IIO_TEMP,
		.modअगरied = 1,
		.channel2 = IIO_MOD_TEMP_AMBIENT,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				BIT(IIO_CHAN_INFO_SCALE),
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ),
		.event_spec = पंचांगp007_die_event,
		.num_event_specs = ARRAY_SIZE(पंचांगp007_die_event),
	पूर्ण,
	अणु
		.type = IIO_TEMP,
		.modअगरied = 1,
		.channel2 = IIO_MOD_TEMP_OBJECT,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				BIT(IIO_CHAN_INFO_SCALE),
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ),
		.event_spec = पंचांगp007_obj_event,
		.num_event_specs = ARRAY_SIZE(पंचांगp007_obj_event),
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा iio_info पंचांगp007_info = अणु
	.पढ़ो_raw = पंचांगp007_पढ़ो_raw,
	.ग_लिखो_raw = पंचांगp007_ग_लिखो_raw,
	.पढ़ो_event_config = पंचांगp007_पढ़ो_event_config,
	.ग_लिखो_event_config = पंचांगp007_ग_लिखो_event_config,
	.पढ़ो_event_value = पंचांगp007_पढ़ो_thresh,
	.ग_लिखो_event_value = पंचांगp007_ग_लिखो_thresh,
	.attrs = &पंचांगp007_attribute_group,
पूर्ण;

अटल bool पंचांगp007_identअगरy(काष्ठा i2c_client *client)
अणु
	पूर्णांक manf_id, dev_id;

	manf_id = i2c_smbus_पढ़ो_word_swapped(client, TMP007_MANUFACTURER_ID);
	अगर (manf_id < 0)
		वापस false;

	dev_id = i2c_smbus_पढ़ो_word_swapped(client, TMP007_DEVICE_ID);
	अगर (dev_id < 0)
		वापस false;

	वापस (manf_id == TMP007_MANUFACTURER_MAGIC && dev_id == TMP007_DEVICE_MAGIC);
पूर्ण

अटल व्योम पंचांगp007_घातerकरोwn_action_cb(व्योम *priv)
अणु
	काष्ठा पंचांगp007_data *data = priv;

	पंचांगp007_घातerकरोwn(data);
पूर्ण

अटल पूर्णांक पंचांगp007_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *पंचांगp007_id)
अणु
	काष्ठा पंचांगp007_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_WORD_DATA))
		वापस -EOPNOTSUPP;

	अगर (!पंचांगp007_identअगरy(client)) अणु
		dev_err(&client->dev, "TMP007 not found\n");
		वापस -ENODEV;
	पूर्ण

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	mutex_init(&data->lock);

	indio_dev->name = "tmp007";
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &पंचांगp007_info;

	indio_dev->channels = पंचांगp007_channels;
	indio_dev->num_channels = ARRAY_SIZE(पंचांगp007_channels);

	/*
	 * Set Configuration रेजिस्टर:
	 * 1. Conversion ON
	 * 2. ALERT enable
	 * 3. Transient correction enable
	 */

	ret = i2c_smbus_पढ़ो_word_swapped(data->client, TMP007_CONFIG);
	अगर (ret < 0)
		वापस ret;

	data->config = ret;
	data->config |= (TMP007_CONFIG_CONV_EN | TMP007_CONFIG_ALERT_EN | TMP007_CONFIG_TC_EN);

	ret = i2c_smbus_ग_लिखो_word_swapped(data->client, TMP007_CONFIG,
					data->config);
	अगर (ret < 0)
		वापस ret;

	ret = devm_add_action_or_reset(&client->dev, पंचांगp007_घातerकरोwn_action_cb, data);
	अगर (ret)
		वापस ret;

	/*
	 * Only the following flags can activate ALERT pin. Data conversion/validity flags
	 * flags can still be polled क्रम getting temperature data
	 *
	 * Set Status Mask रेजिस्टर:
	 * 1. Object temperature high limit enable
	 * 2. Object temperature low limit enable
	 * 3. TDIE temperature high limit enable
	 * 4. TDIE temperature low limit enable
	 */

	ret = i2c_smbus_पढ़ो_word_swapped(data->client, TMP007_STATUS_MASK);
	अगर (ret < 0)
		वापस ret;

	data->status_mask = ret;
	data->status_mask |= (TMP007_STATUS_OHF | TMP007_STATUS_OLF
				| TMP007_STATUS_LHF | TMP007_STATUS_LLF);

	ret = i2c_smbus_ग_लिखो_word_swapped(data->client, TMP007_STATUS_MASK, data->status_mask);
	अगर (ret < 0)
		वापस ret;

	अगर (client->irq) अणु
		ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
				शून्य, पंचांगp007_पूर्णांकerrupt_handler,
				IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				पंचांगp007_id->name, indio_dev);
		अगर (ret) अणु
			dev_err(&client->dev, "irq request error %d\n", -ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक पंचांगp007_suspend(काष्ठा device *dev)
अणु
	काष्ठा पंचांगp007_data *data = iio_priv(i2c_get_clientdata(
			to_i2c_client(dev)));

	वापस पंचांगp007_घातerकरोwn(data);
पूर्ण

अटल पूर्णांक पंचांगp007_resume(काष्ठा device *dev)
अणु
	काष्ठा पंचांगp007_data *data = iio_priv(i2c_get_clientdata(
			to_i2c_client(dev)));

	वापस i2c_smbus_ग_लिखो_word_swapped(data->client, TMP007_CONFIG,
			data->config | TMP007_CONFIG_CONV_EN);
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(पंचांगp007_pm_ops, पंचांगp007_suspend, पंचांगp007_resume);

अटल स्थिर काष्ठा of_device_id पंचांगp007_of_match[] = अणु
	अणु .compatible = "ti,tmp007", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, पंचांगp007_of_match);

अटल स्थिर काष्ठा i2c_device_id पंचांगp007_id[] = अणु
	अणु "tmp007", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, पंचांगp007_id);

अटल काष्ठा i2c_driver पंचांगp007_driver = अणु
	.driver = अणु
		.name	= "tmp007",
		.of_match_table = पंचांगp007_of_match,
		.pm	= &पंचांगp007_pm_ops,
	पूर्ण,
	.probe		= पंचांगp007_probe,
	.id_table	= पंचांगp007_id,
पूर्ण;
module_i2c_driver(पंचांगp007_driver);

MODULE_AUTHOR("Manivannan Sadhasivam <manivannanece23@gmail.com>");
MODULE_DESCRIPTION("TI TMP007 IR thermopile sensor driver");
MODULE_LICENSE("GPL");
