<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vcnl4000.c - Support क्रम Vishay VCNL4000/4010/4020/4040/4200 combined ambient
 * light and proximity sensor
 *
 * Copyright 2012 Peter Meerwald <pmeerw@pmeerw.net>
 * Copyright 2019 Pursim SPC
 * Copyright 2020 Mathieu Othacehe <m.othacehe@gmail.com>
 *
 * IIO driver क्रम:
 *   VCNL4000/10/20 (7-bit I2C slave address 0x13)
 *   VCNL4040 (7-bit I2C slave address 0x60)
 *   VCNL4200 (7-bit I2C slave address 0x51)
 *
 * TODO:
 *   allow to adjust IR current
 *   पूर्णांकerrupts (VCNL4040, VCNL4200)
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>

#घोषणा VCNL4000_DRV_NAME "vcnl4000"
#घोषणा VCNL4000_PROD_ID	0x01
#घोषणा VCNL4010_PROD_ID	0x02 /* क्रम VCNL4020, VCNL4010 */
#घोषणा VCNL4040_PROD_ID	0x86
#घोषणा VCNL4200_PROD_ID	0x58

#घोषणा VCNL4000_COMMAND	0x80 /* Command रेजिस्टर */
#घोषणा VCNL4000_PROD_REV	0x81 /* Product ID and Revision ID */
#घोषणा VCNL4010_PROX_RATE      0x82 /* Proximity rate */
#घोषणा VCNL4000_LED_CURRENT	0x83 /* IR LED current क्रम proximity mode */
#घोषणा VCNL4000_AL_PARAM	0x84 /* Ambient light parameter रेजिस्टर */
#घोषणा VCNL4010_ALS_PARAM      0x84 /* ALS rate */
#घोषणा VCNL4000_AL_RESULT_HI	0x85 /* Ambient light result रेजिस्टर, MSB */
#घोषणा VCNL4000_AL_RESULT_LO	0x86 /* Ambient light result रेजिस्टर, LSB */
#घोषणा VCNL4000_PS_RESULT_HI	0x87 /* Proximity result रेजिस्टर, MSB */
#घोषणा VCNL4000_PS_RESULT_LO	0x88 /* Proximity result रेजिस्टर, LSB */
#घोषणा VCNL4000_PS_MEAS_FREQ	0x89 /* Proximity test संकेत frequency */
#घोषणा VCNL4010_INT_CTRL	0x89 /* Interrupt control */
#घोषणा VCNL4000_PS_MOD_ADJ	0x8a /* Proximity modulator timing adjusपंचांगent */
#घोषणा VCNL4010_LOW_THR_HI     0x8a /* Low threshold, MSB */
#घोषणा VCNL4010_LOW_THR_LO     0x8b /* Low threshold, LSB */
#घोषणा VCNL4010_HIGH_THR_HI    0x8c /* High threshold, MSB */
#घोषणा VCNL4010_HIGH_THR_LO    0x8d /* High threshold, LSB */
#घोषणा VCNL4010_ISR		0x8e /* Interrupt status */

#घोषणा VCNL4200_AL_CONF	0x00 /* Ambient light configuration */
#घोषणा VCNL4200_PS_CONF1	0x03 /* Proximity configuration */
#घोषणा VCNL4200_PS_DATA	0x08 /* Proximity data */
#घोषणा VCNL4200_AL_DATA	0x09 /* Ambient light data */
#घोषणा VCNL4200_DEV_ID		0x0e /* Device ID, slave address and version */

#घोषणा VCNL4040_DEV_ID		0x0c /* Device ID and version */

/* Bit masks क्रम COMMAND रेजिस्टर */
#घोषणा VCNL4000_AL_RDY		BIT(6) /* ALS data पढ़ोy? */
#घोषणा VCNL4000_PS_RDY		BIT(5) /* proximity data पढ़ोy? */
#घोषणा VCNL4000_AL_OD		BIT(4) /* start on-demand ALS measurement */
#घोषणा VCNL4000_PS_OD		BIT(3) /* start on-demand proximity measurement */
#घोषणा VCNL4000_ALS_EN		BIT(2) /* start ALS measurement */
#घोषणा VCNL4000_PROX_EN	BIT(1) /* start proximity measurement */
#घोषणा VCNL4000_SELF_TIMED_EN	BIT(0) /* start self-समयd measurement */

/* Bit masks क्रम पूर्णांकerrupt रेजिस्टरs. */
#घोषणा VCNL4010_INT_THR_SEL	BIT(0) /* Select threshold पूर्णांकerrupt source */
#घोषणा VCNL4010_INT_THR_EN	BIT(1) /* Threshold पूर्णांकerrupt type */
#घोषणा VCNL4010_INT_ALS_EN	BIT(2) /* Enable on ALS data पढ़ोy */
#घोषणा VCNL4010_INT_PROX_EN	BIT(3) /* Enable on proximity data पढ़ोy */

#घोषणा VCNL4010_INT_THR_HIGH	0 /* High threshold exceeded */
#घोषणा VCNL4010_INT_THR_LOW	1 /* Low threshold exceeded */
#घोषणा VCNL4010_INT_ALS	2 /* ALS data पढ़ोy */
#घोषणा VCNL4010_INT_PROXIMITY	3 /* Proximity data पढ़ोy */

#घोषणा VCNL4010_INT_THR \
	(BIT(VCNL4010_INT_THR_LOW) | BIT(VCNL4010_INT_THR_HIGH))
#घोषणा VCNL4010_INT_DRDY \
	(BIT(VCNL4010_INT_PROXIMITY) | BIT(VCNL4010_INT_ALS))

अटल स्थिर पूर्णांक vcnl4010_prox_sampling_frequency[][2] = अणु
	अणु1, 950000पूर्ण,
	अणु3, 906250पूर्ण,
	अणु7, 812500पूर्ण,
	अणु16, 625000पूर्ण,
	अणु31, 250000पूर्ण,
	अणु62, 500000पूर्ण,
	अणु125, 0पूर्ण,
	अणु250, 0पूर्ण,
पूर्ण;

#घोषणा VCNL4000_SLEEP_DELAY_MS	2000 /* beक्रमe we enter pm_runसमय_suspend */

क्रमागत vcnl4000_device_ids अणु
	VCNL4000,
	VCNL4010,
	VCNL4040,
	VCNL4200,
पूर्ण;

काष्ठा vcnl4200_channel अणु
	u8 reg;
	kसमय_प्रकार last_measurement;
	kसमय_प्रकार sampling_rate;
	काष्ठा mutex lock;
पूर्ण;

काष्ठा vcnl4000_data अणु
	काष्ठा i2c_client *client;
	क्रमागत vcnl4000_device_ids id;
	पूर्णांक rev;
	पूर्णांक al_scale;
	स्थिर काष्ठा vcnl4000_chip_spec *chip_spec;
	काष्ठा mutex vcnl4000_lock;
	काष्ठा vcnl4200_channel vcnl4200_al;
	काष्ठा vcnl4200_channel vcnl4200_ps;
	uपूर्णांक32_t near_level;
पूर्ण;

काष्ठा vcnl4000_chip_spec अणु
	स्थिर अक्षर *prod;
	काष्ठा iio_chan_spec स्थिर *channels;
	स्थिर पूर्णांक num_channels;
	स्थिर काष्ठा iio_info *info;
	bool irq_support;
	पूर्णांक (*init)(काष्ठा vcnl4000_data *data);
	पूर्णांक (*measure_light)(काष्ठा vcnl4000_data *data, पूर्णांक *val);
	पूर्णांक (*measure_proximity)(काष्ठा vcnl4000_data *data, पूर्णांक *val);
	पूर्णांक (*set_घातer_state)(काष्ठा vcnl4000_data *data, bool on);
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id vcnl4000_id[] = अणु
	अणु "vcnl4000", VCNL4000 पूर्ण,
	अणु "vcnl4010", VCNL4010 पूर्ण,
	अणु "vcnl4020", VCNL4010 पूर्ण,
	अणु "vcnl4040", VCNL4040 पूर्ण,
	अणु "vcnl4200", VCNL4200 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, vcnl4000_id);

अटल पूर्णांक vcnl4000_set_घातer_state(काष्ठा vcnl4000_data *data, bool on)
अणु
	/* no suspend op */
	वापस 0;
पूर्ण

अटल पूर्णांक vcnl4000_init(काष्ठा vcnl4000_data *data)
अणु
	पूर्णांक ret, prod_id;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, VCNL4000_PROD_REV);
	अगर (ret < 0)
		वापस ret;

	prod_id = ret >> 4;
	चयन (prod_id) अणु
	हाल VCNL4000_PROD_ID:
		अगर (data->id != VCNL4000)
			dev_warn(&data->client->dev,
					"wrong device id, use vcnl4000");
		अवरोध;
	हाल VCNL4010_PROD_ID:
		अगर (data->id != VCNL4010)
			dev_warn(&data->client->dev,
					"wrong device id, use vcnl4010/4020");
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	data->rev = ret & 0xf;
	data->al_scale = 250000;
	mutex_init(&data->vcnl4000_lock);

	वापस data->chip_spec->set_घातer_state(data, true);
पूर्ण;

अटल पूर्णांक vcnl4200_set_घातer_state(काष्ठा vcnl4000_data *data, bool on)
अणु
	u16 val = on ? 0 /* घातer on */ : 1 /* shut करोwn */;
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_word_data(data->client, VCNL4200_AL_CONF, val);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_ग_लिखो_word_data(data->client, VCNL4200_PS_CONF1, val);
	अगर (ret < 0)
		वापस ret;

	अगर (on) अणु
		/* Wait at least one पूर्णांकegration cycle beक्रमe fetching data */
		data->vcnl4200_al.last_measurement = kसमय_get();
		data->vcnl4200_ps.last_measurement = kसमय_get();
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vcnl4200_init(काष्ठा vcnl4000_data *data)
अणु
	पूर्णांक ret, id;

	ret = i2c_smbus_पढ़ो_word_data(data->client, VCNL4200_DEV_ID);
	अगर (ret < 0)
		वापस ret;

	id = ret & 0xff;

	अगर (id != VCNL4200_PROD_ID) अणु
		ret = i2c_smbus_पढ़ो_word_data(data->client, VCNL4040_DEV_ID);
		अगर (ret < 0)
			वापस ret;

		id = ret & 0xff;

		अगर (id != VCNL4040_PROD_ID)
			वापस -ENODEV;
	पूर्ण

	dev_dbg(&data->client->dev, "device id 0x%x", id);

	data->rev = (ret >> 8) & 0xf;

	data->vcnl4200_al.reg = VCNL4200_AL_DATA;
	data->vcnl4200_ps.reg = VCNL4200_PS_DATA;
	चयन (id) अणु
	हाल VCNL4200_PROD_ID:
		/* Default रुको समय is 50ms, add 20% tolerance. */
		data->vcnl4200_al.sampling_rate = kसमय_set(0, 60000 * 1000);
		/* Default रुको समय is 4.8ms, add 20% tolerance. */
		data->vcnl4200_ps.sampling_rate = kसमय_set(0, 5760 * 1000);
		data->al_scale = 24000;
		अवरोध;
	हाल VCNL4040_PROD_ID:
		/* Default रुको समय is 80ms, add 20% tolerance. */
		data->vcnl4200_al.sampling_rate = kसमय_set(0, 96000 * 1000);
		/* Default रुको समय is 5ms, add 20% tolerance. */
		data->vcnl4200_ps.sampling_rate = kसमय_set(0, 6000 * 1000);
		data->al_scale = 120000;
		अवरोध;
	पूर्ण
	mutex_init(&data->vcnl4200_al.lock);
	mutex_init(&data->vcnl4200_ps.lock);

	ret = data->chip_spec->set_घातer_state(data, true);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण;

अटल पूर्णांक vcnl4000_पढ़ो_data(काष्ठा vcnl4000_data *data, u8 data_reg, पूर्णांक *val)
अणु
	s32 ret;

	ret = i2c_smbus_पढ़ो_word_swapped(data->client, data_reg);
	अगर (ret < 0)
		वापस ret;

	*val = ret;
	वापस 0;
पूर्ण

अटल पूर्णांक vcnl4000_ग_लिखो_data(काष्ठा vcnl4000_data *data, u8 data_reg, पूर्णांक val)
अणु
	अगर (val > U16_MAX)
		वापस -दुस्फल;

	वापस i2c_smbus_ग_लिखो_word_swapped(data->client, data_reg, val);
पूर्ण


अटल पूर्णांक vcnl4000_measure(काष्ठा vcnl4000_data *data, u8 req_mask,
				u8 rdy_mask, u8 data_reg, पूर्णांक *val)
अणु
	पूर्णांक tries = 20;
	पूर्णांक ret;

	mutex_lock(&data->vcnl4000_lock);

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, VCNL4000_COMMAND,
					req_mask);
	अगर (ret < 0)
		जाओ fail;

	/* रुको क्रम data to become पढ़ोy */
	जबतक (tries--) अणु
		ret = i2c_smbus_पढ़ो_byte_data(data->client, VCNL4000_COMMAND);
		अगर (ret < 0)
			जाओ fail;
		अगर (ret & rdy_mask)
			अवरोध;
		msleep(20); /* measurement takes up to 100 ms */
	पूर्ण

	अगर (tries < 0) अणु
		dev_err(&data->client->dev,
			"vcnl4000_measure() failed, data not ready\n");
		ret = -EIO;
		जाओ fail;
	पूर्ण

	ret = vcnl4000_पढ़ो_data(data, data_reg, val);
	अगर (ret < 0)
		जाओ fail;

	mutex_unlock(&data->vcnl4000_lock);

	वापस 0;

fail:
	mutex_unlock(&data->vcnl4000_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक vcnl4200_measure(काष्ठा vcnl4000_data *data,
		काष्ठा vcnl4200_channel *chan, पूर्णांक *val)
अणु
	पूर्णांक ret;
	s64 delta;
	kसमय_प्रकार next_measurement;

	mutex_lock(&chan->lock);

	next_measurement = kसमय_add(chan->last_measurement,
			chan->sampling_rate);
	delta = kसमय_us_delta(next_measurement, kसमय_get());
	अगर (delta > 0)
		usleep_range(delta, delta + 500);
	chan->last_measurement = kसमय_get();

	mutex_unlock(&chan->lock);

	ret = i2c_smbus_पढ़ो_word_data(data->client, chan->reg);
	अगर (ret < 0)
		वापस ret;

	*val = ret;

	वापस 0;
पूर्ण

अटल पूर्णांक vcnl4000_measure_light(काष्ठा vcnl4000_data *data, पूर्णांक *val)
अणु
	वापस vcnl4000_measure(data,
			VCNL4000_AL_OD, VCNL4000_AL_RDY,
			VCNL4000_AL_RESULT_HI, val);
पूर्ण

अटल पूर्णांक vcnl4200_measure_light(काष्ठा vcnl4000_data *data, पूर्णांक *val)
अणु
	वापस vcnl4200_measure(data, &data->vcnl4200_al, val);
पूर्ण

अटल पूर्णांक vcnl4000_measure_proximity(काष्ठा vcnl4000_data *data, पूर्णांक *val)
अणु
	वापस vcnl4000_measure(data,
			VCNL4000_PS_OD, VCNL4000_PS_RDY,
			VCNL4000_PS_RESULT_HI, val);
पूर्ण

अटल पूर्णांक vcnl4200_measure_proximity(काष्ठा vcnl4000_data *data, पूर्णांक *val)
अणु
	वापस vcnl4200_measure(data, &data->vcnl4200_ps, val);
पूर्ण

अटल पूर्णांक vcnl4010_पढ़ो_proxy_samp_freq(काष्ठा vcnl4000_data *data, पूर्णांक *val,
					 पूर्णांक *val2)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, VCNL4010_PROX_RATE);
	अगर (ret < 0)
		वापस ret;

	अगर (ret >= ARRAY_SIZE(vcnl4010_prox_sampling_frequency))
		वापस -EINVAL;

	*val = vcnl4010_prox_sampling_frequency[ret][0];
	*val2 = vcnl4010_prox_sampling_frequency[ret][1];

	वापस 0;
पूर्ण

अटल bool vcnl4010_is_in_periodic_mode(काष्ठा vcnl4000_data *data)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, VCNL4000_COMMAND);
	अगर (ret < 0)
		वापस false;

	वापस !!(ret & VCNL4000_SELF_TIMED_EN);
पूर्ण

अटल पूर्णांक vcnl4000_set_pm_runसमय_state(काष्ठा vcnl4000_data *data, bool on)
अणु
	काष्ठा device *dev = &data->client->dev;
	पूर्णांक ret;

	अगर (on) अणु
		ret = pm_runसमय_get_sync(dev);
		अगर (ret < 0)
			pm_runसमय_put_noidle(dev);
	पूर्ण अन्यथा अणु
		pm_runसमय_mark_last_busy(dev);
		ret = pm_runसमय_put_स्वतःsuspend(dev);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vcnl4000_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *chan,
				पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक ret;
	काष्ठा vcnl4000_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = vcnl4000_set_pm_runसमय_state(data, true);
		अगर  (ret < 0)
			वापस ret;

		चयन (chan->type) अणु
		हाल IIO_LIGHT:
			ret = data->chip_spec->measure_light(data, val);
			अगर (!ret)
				ret = IIO_VAL_INT;
			अवरोध;
		हाल IIO_PROXIMITY:
			ret = data->chip_spec->measure_proximity(data, val);
			अगर (!ret)
				ret = IIO_VAL_INT;
			अवरोध;
		शेष:
			ret = -EINVAL;
		पूर्ण
		vcnl4000_set_pm_runसमय_state(data, false);
		वापस ret;
	हाल IIO_CHAN_INFO_SCALE:
		अगर (chan->type != IIO_LIGHT)
			वापस -EINVAL;

		*val = 0;
		*val2 = data->al_scale;
		वापस IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक vcnl4010_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक ret;
	काष्ठा vcnl4000_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
	हाल IIO_CHAN_INFO_SCALE:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;

		/* Protect against event capture. */
		अगर (vcnl4010_is_in_periodic_mode(data)) अणु
			ret = -EBUSY;
		पूर्ण अन्यथा अणु
			ret = vcnl4000_पढ़ो_raw(indio_dev, chan, val, val2,
						mask);
		पूर्ण

		iio_device_release_direct_mode(indio_dev);
		वापस ret;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		चयन (chan->type) अणु
		हाल IIO_PROXIMITY:
			ret = vcnl4010_पढ़ो_proxy_samp_freq(data, val, val2);
			अगर (ret < 0)
				वापस ret;
			वापस IIO_VAL_INT_PLUS_MICRO;
		शेष:
			वापस -EINVAL;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक vcnl4010_पढ़ो_avail(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       स्थिर पूर्णांक **vals, पूर्णांक *type, पूर्णांक *length,
			       दीर्घ mask)
अणु
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*vals = (पूर्णांक *)vcnl4010_prox_sampling_frequency;
		*type = IIO_VAL_INT_PLUS_MICRO;
		*length = 2 * ARRAY_SIZE(vcnl4010_prox_sampling_frequency);
		वापस IIO_AVAIL_LIST;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक vcnl4010_ग_लिखो_proxy_samp_freq(काष्ठा vcnl4000_data *data, पूर्णांक val,
					  पूर्णांक val2)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक index = -1;

	क्रम (i = 0; i < ARRAY_SIZE(vcnl4010_prox_sampling_frequency); i++) अणु
		अगर (val == vcnl4010_prox_sampling_frequency[i][0] &&
		    val2 == vcnl4010_prox_sampling_frequency[i][1]) अणु
			index = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (index < 0)
		वापस -EINVAL;

	वापस i2c_smbus_ग_लिखो_byte_data(data->client, VCNL4010_PROX_RATE,
					 index);
पूर्ण

अटल पूर्णांक vcnl4010_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan,
			      पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	पूर्णांक ret;
	काष्ठा vcnl4000_data *data = iio_priv(indio_dev);

	ret = iio_device_claim_direct_mode(indio_dev);
	अगर (ret)
		वापस ret;

	/* Protect against event capture. */
	अगर (vcnl4010_is_in_periodic_mode(data)) अणु
		ret = -EBUSY;
		जाओ end;
	पूर्ण

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		चयन (chan->type) अणु
		हाल IIO_PROXIMITY:
			ret = vcnl4010_ग_लिखो_proxy_samp_freq(data, val, val2);
			जाओ end;
		शेष:
			ret = -EINVAL;
			जाओ end;
		पूर्ण
	शेष:
		ret = -EINVAL;
		जाओ end;
	पूर्ण

end:
	iio_device_release_direct_mode(indio_dev);
	वापस ret;
पूर्ण

अटल पूर्णांक vcnl4010_पढ़ो_event(काष्ठा iio_dev *indio_dev,
			       स्थिर काष्ठा iio_chan_spec *chan,
			       क्रमागत iio_event_type type,
			       क्रमागत iio_event_direction dir,
			       क्रमागत iio_event_info info,
			       पूर्णांक *val, पूर्णांक *val2)
अणु
	पूर्णांक ret;
	काष्ठा vcnl4000_data *data = iio_priv(indio_dev);

	चयन (info) अणु
	हाल IIO_EV_INFO_VALUE:
		चयन (dir) अणु
		हाल IIO_EV_सूची_RISING:
			ret = vcnl4000_पढ़ो_data(data, VCNL4010_HIGH_THR_HI,
						 val);
			अगर (ret < 0)
				वापस ret;
			वापस IIO_VAL_INT;
		हाल IIO_EV_सूची_FALLING:
			ret = vcnl4000_पढ़ो_data(data, VCNL4010_LOW_THR_HI,
						 val);
			अगर (ret < 0)
				वापस ret;
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक vcnl4010_ग_लिखो_event(काष्ठा iio_dev *indio_dev,
				स्थिर काष्ठा iio_chan_spec *chan,
				क्रमागत iio_event_type type,
				क्रमागत iio_event_direction dir,
				क्रमागत iio_event_info info,
				पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक ret;
	काष्ठा vcnl4000_data *data = iio_priv(indio_dev);

	चयन (info) अणु
	हाल IIO_EV_INFO_VALUE:
		चयन (dir) अणु
		हाल IIO_EV_सूची_RISING:
			ret = vcnl4000_ग_लिखो_data(data, VCNL4010_HIGH_THR_HI,
						  val);
			अगर (ret < 0)
				वापस ret;
			वापस IIO_VAL_INT;
		हाल IIO_EV_सूची_FALLING:
			ret = vcnl4000_ग_लिखो_data(data, VCNL4010_LOW_THR_HI,
						  val);
			अगर (ret < 0)
				वापस ret;
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल bool vcnl4010_is_thr_enabled(काष्ठा vcnl4000_data *data)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, VCNL4010_INT_CTRL);
	अगर (ret < 0)
		वापस false;

	वापस !!(ret & VCNL4010_INT_THR_EN);
पूर्ण

अटल पूर्णांक vcnl4010_पढ़ो_event_config(काष्ठा iio_dev *indio_dev,
				      स्थिर काष्ठा iio_chan_spec *chan,
				      क्रमागत iio_event_type type,
				      क्रमागत iio_event_direction dir)
अणु
	काष्ठा vcnl4000_data *data = iio_priv(indio_dev);

	चयन (chan->type) अणु
	हाल IIO_PROXIMITY:
		वापस vcnl4010_is_thr_enabled(data);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक vcnl4010_config_threshold(काष्ठा iio_dev *indio_dev, bool state)
अणु
	काष्ठा vcnl4000_data *data = iio_priv(indio_dev);
	पूर्णांक ret;
	पूर्णांक icr;
	पूर्णांक command;

	अगर (state) अणु
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;

		/* Enable periodic measurement of proximity data. */
		command = VCNL4000_SELF_TIMED_EN | VCNL4000_PROX_EN;

		/*
		 * Enable पूर्णांकerrupts on threshold, क्रम proximity data by
		 * शेष.
		 */
		icr = VCNL4010_INT_THR_EN;
	पूर्ण अन्यथा अणु
		अगर (!vcnl4010_is_thr_enabled(data))
			वापस 0;

		command = 0;
		icr = 0;
	पूर्ण

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, VCNL4000_COMMAND,
					command);
	अगर (ret < 0)
		जाओ end;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, VCNL4010_INT_CTRL, icr);

end:
	अगर (state)
		iio_device_release_direct_mode(indio_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक vcnl4010_ग_लिखो_event_config(काष्ठा iio_dev *indio_dev,
				       स्थिर काष्ठा iio_chan_spec *chan,
				       क्रमागत iio_event_type type,
				       क्रमागत iio_event_direction dir,
				       पूर्णांक state)
अणु
	चयन (chan->type) अणु
	हाल IIO_PROXIMITY:
		वापस vcnl4010_config_threshold(indio_dev, state);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार vcnl4000_पढ़ो_near_level(काष्ठा iio_dev *indio_dev,
					uपूर्णांकptr_t priv,
					स्थिर काष्ठा iio_chan_spec *chan,
					अक्षर *buf)
अणु
	काष्ठा vcnl4000_data *data = iio_priv(indio_dev);

	वापस प्र_लिखो(buf, "%u\n", data->near_level);
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec_ext_info vcnl4000_ext_info[] = अणु
	अणु
		.name = "nearlevel",
		.shared = IIO_SEPARATE,
		.पढ़ो = vcnl4000_पढ़ो_near_level,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा iio_event_spec vcnl4000_event_spec[] = अणु
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_RISING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE),
	पूर्ण, अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_FALLING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE),
	पूर्ण, अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_EITHER,
		.mask_separate = BIT(IIO_EV_INFO_ENABLE),
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec vcnl4000_channels[] = अणु
	अणु
		.type = IIO_LIGHT,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SCALE),
	पूर्ण, अणु
		.type = IIO_PROXIMITY,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.ext_info = vcnl4000_ext_info,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec vcnl4010_channels[] = अणु
	अणु
		.type = IIO_LIGHT,
		.scan_index = -1,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SCALE),
	पूर्ण, अणु
		.type = IIO_PROXIMITY,
		.scan_index = 0,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SAMP_FREQ),
		.info_mask_separate_available = BIT(IIO_CHAN_INFO_SAMP_FREQ),
		.event_spec = vcnl4000_event_spec,
		.num_event_specs = ARRAY_SIZE(vcnl4000_event_spec),
		.ext_info = vcnl4000_ext_info,
		.scan_type = अणु
			.sign = 'u',
			.realbits = 16,
			.storagebits = 16,
			.endianness = IIO_CPU,
		पूर्ण,
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(1),
पूर्ण;

अटल स्थिर काष्ठा iio_info vcnl4000_info = अणु
	.पढ़ो_raw = vcnl4000_पढ़ो_raw,
पूर्ण;

अटल स्थिर काष्ठा iio_info vcnl4010_info = अणु
	.पढ़ो_raw = vcnl4010_पढ़ो_raw,
	.पढ़ो_avail = vcnl4010_पढ़ो_avail,
	.ग_लिखो_raw = vcnl4010_ग_लिखो_raw,
	.पढ़ो_event_value = vcnl4010_पढ़ो_event,
	.ग_लिखो_event_value = vcnl4010_ग_लिखो_event,
	.पढ़ो_event_config = vcnl4010_पढ़ो_event_config,
	.ग_लिखो_event_config = vcnl4010_ग_लिखो_event_config,
पूर्ण;

अटल स्थिर काष्ठा vcnl4000_chip_spec vcnl4000_chip_spec_cfg[] = अणु
	[VCNL4000] = अणु
		.prod = "VCNL4000",
		.init = vcnl4000_init,
		.measure_light = vcnl4000_measure_light,
		.measure_proximity = vcnl4000_measure_proximity,
		.set_घातer_state = vcnl4000_set_घातer_state,
		.channels = vcnl4000_channels,
		.num_channels = ARRAY_SIZE(vcnl4000_channels),
		.info = &vcnl4000_info,
		.irq_support = false,
	पूर्ण,
	[VCNL4010] = अणु
		.prod = "VCNL4010/4020",
		.init = vcnl4000_init,
		.measure_light = vcnl4000_measure_light,
		.measure_proximity = vcnl4000_measure_proximity,
		.set_घातer_state = vcnl4000_set_घातer_state,
		.channels = vcnl4010_channels,
		.num_channels = ARRAY_SIZE(vcnl4010_channels),
		.info = &vcnl4010_info,
		.irq_support = true,
	पूर्ण,
	[VCNL4040] = अणु
		.prod = "VCNL4040",
		.init = vcnl4200_init,
		.measure_light = vcnl4200_measure_light,
		.measure_proximity = vcnl4200_measure_proximity,
		.set_घातer_state = vcnl4200_set_घातer_state,
		.channels = vcnl4000_channels,
		.num_channels = ARRAY_SIZE(vcnl4000_channels),
		.info = &vcnl4000_info,
		.irq_support = false,
	पूर्ण,
	[VCNL4200] = अणु
		.prod = "VCNL4200",
		.init = vcnl4200_init,
		.measure_light = vcnl4200_measure_light,
		.measure_proximity = vcnl4200_measure_proximity,
		.set_घातer_state = vcnl4200_set_घातer_state,
		.channels = vcnl4000_channels,
		.num_channels = ARRAY_SIZE(vcnl4000_channels),
		.info = &vcnl4000_info,
		.irq_support = false,
	पूर्ण,
पूर्ण;

अटल irqवापस_t vcnl4010_irq_thपढ़ो(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_dev *indio_dev = p;
	काष्ठा vcnl4000_data *data = iio_priv(indio_dev);
	अचिन्हित दीर्घ isr;
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, VCNL4010_ISR);
	अगर (ret < 0)
		जाओ end;

	isr = ret;

	अगर (isr & VCNL4010_INT_THR) अणु
		अगर (test_bit(VCNL4010_INT_THR_LOW, &isr)) अणु
			iio_push_event(indio_dev,
				       IIO_UNMOD_EVENT_CODE(
					       IIO_PROXIMITY,
					       1,
					       IIO_EV_TYPE_THRESH,
					       IIO_EV_सूची_FALLING),
				       iio_get_समय_ns(indio_dev));
		पूर्ण

		अगर (test_bit(VCNL4010_INT_THR_HIGH, &isr)) अणु
			iio_push_event(indio_dev,
				       IIO_UNMOD_EVENT_CODE(
					       IIO_PROXIMITY,
					       1,
					       IIO_EV_TYPE_THRESH,
					       IIO_EV_सूची_RISING),
				       iio_get_समय_ns(indio_dev));
		पूर्ण

		i2c_smbus_ग_लिखो_byte_data(data->client, VCNL4010_ISR,
					  isr & VCNL4010_INT_THR);
	पूर्ण

	अगर (isr & VCNL4010_INT_DRDY && iio_buffer_enabled(indio_dev))
		iio_trigger_poll_chained(indio_dev->trig);

end:
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t vcnl4010_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा vcnl4000_data *data = iio_priv(indio_dev);
	स्थिर अचिन्हित दीर्घ *active_scan_mask = indio_dev->active_scan_mask;
	u16 buffer[8] = अणु0पूर्ण; /* 1x16-bit + ts */
	bool data_पढ़ो = false;
	अचिन्हित दीर्घ isr;
	पूर्णांक val = 0;
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, VCNL4010_ISR);
	अगर (ret < 0)
		जाओ end;

	isr = ret;

	अगर (test_bit(0, active_scan_mask)) अणु
		अगर (test_bit(VCNL4010_INT_PROXIMITY, &isr)) अणु
			ret = vcnl4000_पढ़ो_data(data,
						 VCNL4000_PS_RESULT_HI,
						 &val);
			अगर (ret < 0)
				जाओ end;

			buffer[0] = val;
			data_पढ़ो = true;
		पूर्ण
	पूर्ण

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, VCNL4010_ISR,
					isr & VCNL4010_INT_DRDY);
	अगर (ret < 0)
		जाओ end;

	अगर (!data_पढ़ो)
		जाओ end;

	iio_push_to_buffers_with_बारtamp(indio_dev, buffer,
					   iio_get_समय_ns(indio_dev));

end:
	iio_trigger_notअगरy_करोne(indio_dev->trig);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक vcnl4010_buffer_postenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा vcnl4000_data *data = iio_priv(indio_dev);
	पूर्णांक ret;
	पूर्णांक cmd;

	/* Do not enable the buffer अगर we are alपढ़ोy capturing events. */
	अगर (vcnl4010_is_in_periodic_mode(data))
		वापस -EBUSY;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, VCNL4010_INT_CTRL,
					VCNL4010_INT_PROX_EN);
	अगर (ret < 0)
		वापस ret;

	cmd = VCNL4000_SELF_TIMED_EN | VCNL4000_PROX_EN;
	वापस i2c_smbus_ग_लिखो_byte_data(data->client, VCNL4000_COMMAND, cmd);
पूर्ण

अटल पूर्णांक vcnl4010_buffer_predisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा vcnl4000_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, VCNL4010_INT_CTRL, 0);
	अगर (ret < 0)
		वापस ret;

	वापस i2c_smbus_ग_लिखो_byte_data(data->client, VCNL4000_COMMAND, 0);
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops vcnl4010_buffer_ops = अणु
	.postenable = &vcnl4010_buffer_postenable,
	.predisable = &vcnl4010_buffer_predisable,
पूर्ण;

अटल स्थिर काष्ठा iio_trigger_ops vcnl4010_trigger_ops = अणु
	.validate_device = iio_trigger_validate_own_device,
पूर्ण;

अटल पूर्णांक vcnl4010_probe_trigger(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा vcnl4000_data *data = iio_priv(indio_dev);
	काष्ठा i2c_client *client = data->client;
	काष्ठा iio_trigger *trigger;

	trigger = devm_iio_trigger_alloc(&client->dev, "%s-dev%d",
					 indio_dev->name, indio_dev->id);
	अगर (!trigger)
		वापस -ENOMEM;

	trigger->ops = &vcnl4010_trigger_ops;
	iio_trigger_set_drvdata(trigger, indio_dev);

	वापस devm_iio_trigger_रेजिस्टर(&client->dev, trigger);
पूर्ण

अटल पूर्णांक vcnl4000_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा vcnl4000_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	data->id = id->driver_data;
	data->chip_spec = &vcnl4000_chip_spec_cfg[data->id];

	ret = data->chip_spec->init(data);
	अगर (ret < 0)
		वापस ret;

	dev_dbg(&client->dev, "%s Ambient light/proximity sensor, Rev: %02x\n",
		data->chip_spec->prod, data->rev);

	अगर (device_property_पढ़ो_u32(&client->dev, "proximity-near-level",
				     &data->near_level))
		data->near_level = 0;

	indio_dev->info = data->chip_spec->info;
	indio_dev->channels = data->chip_spec->channels;
	indio_dev->num_channels = data->chip_spec->num_channels;
	indio_dev->name = VCNL4000_DRV_NAME;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	अगर (client->irq && data->chip_spec->irq_support) अणु
		ret = devm_iio_triggered_buffer_setup(&client->dev, indio_dev,
						      शून्य,
						      vcnl4010_trigger_handler,
						      &vcnl4010_buffer_ops);
		अगर (ret < 0) अणु
			dev_err(&client->dev,
				"unable to setup iio triggered buffer\n");
			वापस ret;
		पूर्ण

		ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
						शून्य, vcnl4010_irq_thपढ़ो,
						IRQF_TRIGGER_FALLING |
						IRQF_ONESHOT,
						"vcnl4010_irq",
						indio_dev);
		अगर (ret < 0) अणु
			dev_err(&client->dev, "irq request failed\n");
			वापस ret;
		पूर्ण

		ret = vcnl4010_probe_trigger(indio_dev);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	ret = pm_runसमय_set_active(&client->dev);
	अगर (ret < 0)
		जाओ fail_घातeroff;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0)
		जाओ fail_घातeroff;

	pm_runसमय_enable(&client->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&client->dev, VCNL4000_SLEEP_DELAY_MS);
	pm_runसमय_use_स्वतःsuspend(&client->dev);

	वापस 0;
fail_घातeroff:
	data->chip_spec->set_घातer_state(data, false);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id vcnl_4000_of_match[] = अणु
	अणु
		.compatible = "vishay,vcnl4000",
		.data = (व्योम *)VCNL4000,
	पूर्ण,
	अणु
		.compatible = "vishay,vcnl4010",
		.data = (व्योम *)VCNL4010,
	पूर्ण,
	अणु
		.compatible = "vishay,vcnl4020",
		.data = (व्योम *)VCNL4010,
	पूर्ण,
	अणु
		.compatible = "vishay,vcnl4040",
		.data = (व्योम *)VCNL4040,
	पूर्ण,
	अणु
		.compatible = "vishay,vcnl4200",
		.data = (व्योम *)VCNL4200,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, vcnl_4000_of_match);

अटल पूर्णांक vcnl4000_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा vcnl4000_data *data = iio_priv(indio_dev);

	pm_runसमय_करोnt_use_स्वतःsuspend(&client->dev);
	pm_runसमय_disable(&client->dev);
	iio_device_unरेजिस्टर(indio_dev);
	pm_runसमय_set_suspended(&client->dev);

	वापस data->chip_spec->set_घातer_state(data, false);
पूर्ण

अटल पूर्णांक __maybe_unused vcnl4000_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा vcnl4000_data *data = iio_priv(indio_dev);

	वापस data->chip_spec->set_घातer_state(data, false);
पूर्ण

अटल पूर्णांक __maybe_unused vcnl4000_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा vcnl4000_data *data = iio_priv(indio_dev);

	वापस data->chip_spec->set_घातer_state(data, true);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops vcnl4000_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(vcnl4000_runसमय_suspend,
			   vcnl4000_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा i2c_driver vcnl4000_driver = अणु
	.driver = अणु
		.name   = VCNL4000_DRV_NAME,
		.pm	= &vcnl4000_pm_ops,
		.of_match_table = vcnl_4000_of_match,
	पूर्ण,
	.probe  = vcnl4000_probe,
	.id_table = vcnl4000_id,
	.हटाओ	= vcnl4000_हटाओ,
पूर्ण;

module_i2c_driver(vcnl4000_driver);

MODULE_AUTHOR("Peter Meerwald <pmeerw@pmeerw.net>");
MODULE_AUTHOR("Mathieu Othacehe <m.othacehe@gmail.com>");
MODULE_DESCRIPTION("Vishay VCNL4000 proximity/ambient light sensor driver");
MODULE_LICENSE("GPL");
