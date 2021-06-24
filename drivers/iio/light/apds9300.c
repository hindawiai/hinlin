<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * apds9300.c - IIO driver क्रम Avago APDS9300 ambient light sensor
 *
 * Copyright 2013 Oleksandr Kravchenko <o.v.kravchenko@globallogic.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/events.h>

#घोषणा APDS9300_DRV_NAME "apds9300"
#घोषणा APDS9300_IRQ_NAME "apds9300_event"

/* Command रेजिस्टर bits */
#घोषणा APDS9300_CMD	BIT(7) /* Select command रेजिस्टर. Must ग_लिखो as 1 */
#घोषणा APDS9300_WORD	BIT(5) /* I2C ग_लिखो/पढ़ो: अगर 1 word, अगर 0 byte */
#घोषणा APDS9300_CLEAR	BIT(6) /* Interrupt clear. Clears pending पूर्णांकerrupt */

/* Register set */
#घोषणा APDS9300_CONTROL	0x00 /* Control of basic functions */
#घोषणा APDS9300_THRESHLOWLOW	0x02 /* Low byte of low पूर्णांकerrupt threshold */
#घोषणा APDS9300_THRESHHIGHLOW	0x04 /* Low byte of high पूर्णांकerrupt threshold */
#घोषणा APDS9300_INTERRUPT	0x06 /* Interrupt control */
#घोषणा APDS9300_DATA0LOW	0x0c /* Low byte of ADC channel 0 */
#घोषणा APDS9300_DATA1LOW	0x0e /* Low byte of ADC channel 1 */

/* Power on/off value क्रम APDS9300_CONTROL रेजिस्टर */
#घोषणा APDS9300_POWER_ON	0x03
#घोषणा APDS9300_POWER_OFF	0x00

/* Interrupts */
#घोषणा APDS9300_INTR_ENABLE	0x10
/* Interrupt Persist Function: Any value outside of threshold range */
#घोषणा APDS9300_THRESH_INTR	0x01

#घोषणा APDS9300_THRESH_MAX	0xffff /* Max threshold value */

काष्ठा apds9300_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex mutex;
	पूर्णांक घातer_state;
	पूर्णांक thresh_low;
	पूर्णांक thresh_hi;
	पूर्णांक पूर्णांकr_en;
पूर्ण;

/* Lux calculation */

/* Calculated values 1000 * (CH1/CH0)^1.4 क्रम CH1/CH0 from 0 to 0.52 */
अटल स्थिर u16 apds9300_lux_ratio[] = अणु
	0, 2, 4, 7, 11, 15, 19, 24, 29, 34, 40, 45, 51, 57, 64, 70, 77, 84, 91,
	98, 105, 112, 120, 128, 136, 144, 152, 160, 168, 177, 185, 194, 203,
	212, 221, 230, 239, 249, 258, 268, 277, 287, 297, 307, 317, 327, 337,
	347, 358, 368, 379, 390, 400,
पूर्ण;

अटल अचिन्हित दीर्घ apds9300_calculate_lux(u16 ch0, u16 ch1)
अणु
	अचिन्हित दीर्घ lux, पंचांगp;

	/* aव्योम भागision by zero */
	अगर (ch0 == 0)
		वापस 0;

	पंचांगp = DIV_ROUND_UP(ch1 * 100, ch0);
	अगर (पंचांगp <= 52) अणु
		lux = 3150 * ch0 - (अचिन्हित दीर्घ)DIV_ROUND_UP_ULL(ch0
				* apds9300_lux_ratio[पंचांगp] * 5930ull, 1000);
	पूर्ण अन्यथा अगर (पंचांगp <= 65) अणु
		lux = 2290 * ch0 - 2910 * ch1;
	पूर्ण अन्यथा अगर (पंचांगp <= 80) अणु
		lux = 1570 * ch0 - 1800 * ch1;
	पूर्ण अन्यथा अगर (पंचांगp <= 130) अणु
		lux = 338 * ch0 - 260 * ch1;
	पूर्ण अन्यथा अणु
		lux = 0;
	पूर्ण

	वापस lux / 100000;
पूर्ण

अटल पूर्णांक apds9300_get_adc_val(काष्ठा apds9300_data *data, पूर्णांक adc_number)
अणु
	पूर्णांक ret;
	u8 flags = APDS9300_CMD | APDS9300_WORD;

	अगर (!data->घातer_state)
		वापस -EBUSY;

	/* Select ADC0 or ADC1 data रेजिस्टर */
	flags |= adc_number ? APDS9300_DATA1LOW : APDS9300_DATA0LOW;

	ret = i2c_smbus_पढ़ो_word_data(data->client, flags);
	अगर (ret < 0)
		dev_err(&data->client->dev,
			"failed to read ADC%d value\n", adc_number);

	वापस ret;
पूर्ण

अटल पूर्णांक apds9300_set_thresh_low(काष्ठा apds9300_data *data, पूर्णांक value)
अणु
	पूर्णांक ret;

	अगर (!data->घातer_state)
		वापस -EBUSY;

	अगर (value > APDS9300_THRESH_MAX)
		वापस -EINVAL;

	ret = i2c_smbus_ग_लिखो_word_data(data->client, APDS9300_THRESHLOWLOW
			| APDS9300_CMD | APDS9300_WORD, value);
	अगर (ret) अणु
		dev_err(&data->client->dev, "failed to set thresh_low\n");
		वापस ret;
	पूर्ण
	data->thresh_low = value;

	वापस 0;
पूर्ण

अटल पूर्णांक apds9300_set_thresh_hi(काष्ठा apds9300_data *data, पूर्णांक value)
अणु
	पूर्णांक ret;

	अगर (!data->घातer_state)
		वापस -EBUSY;

	अगर (value > APDS9300_THRESH_MAX)
		वापस -EINVAL;

	ret = i2c_smbus_ग_लिखो_word_data(data->client, APDS9300_THRESHHIGHLOW
			| APDS9300_CMD | APDS9300_WORD, value);
	अगर (ret) अणु
		dev_err(&data->client->dev, "failed to set thresh_hi\n");
		वापस ret;
	पूर्ण
	data->thresh_hi = value;

	वापस 0;
पूर्ण

अटल पूर्णांक apds9300_set_पूर्णांकr_state(काष्ठा apds9300_data *data, पूर्णांक state)
अणु
	पूर्णांक ret;
	u8 cmd;

	अगर (!data->घातer_state)
		वापस -EBUSY;

	cmd = state ? APDS9300_INTR_ENABLE | APDS9300_THRESH_INTR : 0x00;
	ret = i2c_smbus_ग_लिखो_byte_data(data->client,
			APDS9300_INTERRUPT | APDS9300_CMD, cmd);
	अगर (ret) अणु
		dev_err(&data->client->dev,
			"failed to set interrupt state %d\n", state);
		वापस ret;
	पूर्ण
	data->पूर्णांकr_en = state;

	वापस 0;
पूर्ण

अटल पूर्णांक apds9300_set_घातer_state(काष्ठा apds9300_data *data, पूर्णांक state)
अणु
	पूर्णांक ret;
	u8 cmd;

	cmd = state ? APDS9300_POWER_ON : APDS9300_POWER_OFF;
	ret = i2c_smbus_ग_लिखो_byte_data(data->client,
			APDS9300_CONTROL | APDS9300_CMD, cmd);
	अगर (ret) अणु
		dev_err(&data->client->dev,
			"failed to set power state %d\n", state);
		वापस ret;
	पूर्ण
	data->घातer_state = state;

	वापस 0;
पूर्ण

अटल व्योम apds9300_clear_पूर्णांकr(काष्ठा apds9300_data *data)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte(data->client, APDS9300_CLEAR | APDS9300_CMD);
	अगर (ret < 0)
		dev_err(&data->client->dev, "failed to clear interrupt\n");
पूर्ण

अटल पूर्णांक apds9300_chip_init(काष्ठा apds9300_data *data)
अणु
	पूर्णांक ret;

	/* Need to set घातer off to ensure that the chip is off */
	ret = apds9300_set_घातer_state(data, 0);
	अगर (ret < 0)
		जाओ err;
	/*
	 * Probe the chip. To करो so we try to घातer up the device and then to
	 * पढ़ो back the 0x03 code
	 */
	ret = apds9300_set_घातer_state(data, 1);
	अगर (ret < 0)
		जाओ err;
	ret = i2c_smbus_पढ़ो_byte_data(data->client,
			APDS9300_CONTROL | APDS9300_CMD);
	अगर (ret != APDS9300_POWER_ON) अणु
		ret = -ENODEV;
		जाओ err;
	पूर्ण
	/*
	 * Disable पूर्णांकerrupt to ensure thai it is करोesn't enable
	 * i.e. after device soft reset
	 */
	ret = apds9300_set_पूर्णांकr_state(data, 0);
	अगर (ret < 0)
		जाओ err;

	वापस 0;

err:
	dev_err(&data->client->dev, "failed to init the chip\n");
	वापस ret;
पूर्ण

अटल पूर्णांक apds9300_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
		काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val, पूर्णांक *val2,
		दीर्घ mask)
अणु
	पूर्णांक ch0, ch1, ret = -EINVAL;
	काष्ठा apds9300_data *data = iio_priv(indio_dev);

	mutex_lock(&data->mutex);
	चयन (chan->type) अणु
	हाल IIO_LIGHT:
		ch0 = apds9300_get_adc_val(data, 0);
		अगर (ch0 < 0) अणु
			ret = ch0;
			अवरोध;
		पूर्ण
		ch1 = apds9300_get_adc_val(data, 1);
		अगर (ch1 < 0) अणु
			ret = ch1;
			अवरोध;
		पूर्ण
		*val = apds9300_calculate_lux(ch0, ch1);
		ret = IIO_VAL_INT;
		अवरोध;
	हाल IIO_INTENSITY:
		ret = apds9300_get_adc_val(data, chan->channel);
		अगर (ret < 0)
			अवरोध;
		*val = ret;
		ret = IIO_VAL_INT;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	mutex_unlock(&data->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक apds9300_पढ़ो_thresh(काष्ठा iio_dev *indio_dev,
		स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
		क्रमागत iio_event_direction dir, क्रमागत iio_event_info info,
		पूर्णांक *val, पूर्णांक *val2)
अणु
	काष्ठा apds9300_data *data = iio_priv(indio_dev);

	चयन (dir) अणु
	हाल IIO_EV_सूची_RISING:
		*val = data->thresh_hi;
		अवरोध;
	हाल IIO_EV_सूची_FALLING:
		*val = data->thresh_low;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक apds9300_ग_लिखो_thresh(काष्ठा iio_dev *indio_dev,
		स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
		क्रमागत iio_event_direction dir, क्रमागत iio_event_info info, पूर्णांक val,
		पूर्णांक val2)
अणु
	काष्ठा apds9300_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->mutex);
	अगर (dir == IIO_EV_सूची_RISING)
		ret = apds9300_set_thresh_hi(data, val);
	अन्यथा
		ret = apds9300_set_thresh_low(data, val);
	mutex_unlock(&data->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक apds9300_पढ़ो_पूर्णांकerrupt_config(काष्ठा iio_dev *indio_dev,
		स्थिर काष्ठा iio_chan_spec *chan,
		क्रमागत iio_event_type type,
		क्रमागत iio_event_direction dir)
अणु
	काष्ठा apds9300_data *data = iio_priv(indio_dev);

	वापस data->पूर्णांकr_en;
पूर्ण

अटल पूर्णांक apds9300_ग_लिखो_पूर्णांकerrupt_config(काष्ठा iio_dev *indio_dev,
		स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
		क्रमागत iio_event_direction dir, पूर्णांक state)
अणु
	काष्ठा apds9300_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->mutex);
	ret = apds9300_set_पूर्णांकr_state(data, state);
	mutex_unlock(&data->mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info apds9300_info_no_irq = अणु
	.पढ़ो_raw	= apds9300_पढ़ो_raw,
पूर्ण;

अटल स्थिर काष्ठा iio_info apds9300_info = अणु
	.पढ़ो_raw		= apds9300_पढ़ो_raw,
	.पढ़ो_event_value	= apds9300_पढ़ो_thresh,
	.ग_लिखो_event_value	= apds9300_ग_लिखो_thresh,
	.पढ़ो_event_config	= apds9300_पढ़ो_पूर्णांकerrupt_config,
	.ग_लिखो_event_config	= apds9300_ग_लिखो_पूर्णांकerrupt_config,
पूर्ण;

अटल स्थिर काष्ठा iio_event_spec apds9300_event_spec[] = अणु
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_RISING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE) |
			BIT(IIO_EV_INFO_ENABLE),
	पूर्ण, अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_FALLING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE) |
			BIT(IIO_EV_INFO_ENABLE),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec apds9300_channels[] = अणु
	अणु
		.type = IIO_LIGHT,
		.channel = 0,
		.indexed = true,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),
	पूर्ण, अणु
		.type = IIO_INTENSITY,
		.channel = 0,
		.channel2 = IIO_MOD_LIGHT_BOTH,
		.indexed = true,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.event_spec = apds9300_event_spec,
		.num_event_specs = ARRAY_SIZE(apds9300_event_spec),
	पूर्ण, अणु
		.type = IIO_INTENSITY,
		.channel = 1,
		.channel2 = IIO_MOD_LIGHT_IR,
		.indexed = true,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
	पूर्ण,
पूर्ण;

अटल irqवापस_t apds9300_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *dev_info = निजी;
	काष्ठा apds9300_data *data = iio_priv(dev_info);

	iio_push_event(dev_info,
		       IIO_UNMOD_EVENT_CODE(IIO_INTENSITY, 0,
					    IIO_EV_TYPE_THRESH,
					    IIO_EV_सूची_EITHER),
		       iio_get_समय_ns(dev_info));

	apds9300_clear_पूर्णांकr(data);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक apds9300_probe(काष्ठा i2c_client *client,
		स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा apds9300_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;

	ret = apds9300_chip_init(data);
	अगर (ret < 0)
		जाओ err;

	mutex_init(&data->mutex);

	indio_dev->channels = apds9300_channels;
	indio_dev->num_channels = ARRAY_SIZE(apds9300_channels);
	indio_dev->name = APDS9300_DRV_NAME;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	अगर (client->irq)
		indio_dev->info = &apds9300_info;
	अन्यथा
		indio_dev->info = &apds9300_info_no_irq;

	अगर (client->irq) अणु
		ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
				शून्य, apds9300_पूर्णांकerrupt_handler,
				IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				APDS9300_IRQ_NAME, indio_dev);
		अगर (ret) अणु
			dev_err(&client->dev, "irq request error %d\n", -ret);
			जाओ err;
		पूर्ण
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0)
		जाओ err;

	वापस 0;

err:
	/* Ensure that घातer off in हाल of error */
	apds9300_set_घातer_state(data, 0);
	वापस ret;
पूर्ण

अटल पूर्णांक apds9300_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा apds9300_data *data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	/* Ensure that घातer off and पूर्णांकerrupts are disabled */
	apds9300_set_पूर्णांकr_state(data, 0);
	apds9300_set_घातer_state(data, 0);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक apds9300_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा apds9300_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->mutex);
	ret = apds9300_set_घातer_state(data, 0);
	mutex_unlock(&data->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक apds9300_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा apds9300_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->mutex);
	ret = apds9300_set_घातer_state(data, 1);
	mutex_unlock(&data->mutex);

	वापस ret;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(apds9300_pm_ops, apds9300_suspend, apds9300_resume);
#घोषणा APDS9300_PM_OPS (&apds9300_pm_ops)
#अन्यथा
#घोषणा APDS9300_PM_OPS शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id apds9300_id[] = अणु
	अणु APDS9300_DRV_NAME, 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, apds9300_id);

अटल काष्ठा i2c_driver apds9300_driver = अणु
	.driver = अणु
		.name	= APDS9300_DRV_NAME,
		.pm	= APDS9300_PM_OPS,
	पूर्ण,
	.probe		= apds9300_probe,
	.हटाओ		= apds9300_हटाओ,
	.id_table	= apds9300_id,
पूर्ण;

module_i2c_driver(apds9300_driver);

MODULE_AUTHOR("Kravchenko Oleksandr <o.v.kravchenko@globallogic.com>");
MODULE_AUTHOR("GlobalLogic inc.");
MODULE_DESCRIPTION("APDS9300 ambient light photo sensor driver");
MODULE_LICENSE("GPL");
