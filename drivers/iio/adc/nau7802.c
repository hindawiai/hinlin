<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम the Nuvoton NAU7802 ADC
 *
 * Copyright 2013 Free Electrons
 */

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/रुको.h>
#समावेश <linux/log2.h>
#समावेश <linux/of.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#घोषणा NAU7802_REG_PUCTRL	0x00
#घोषणा NAU7802_PUCTRL_RR(x)		(x << 0)
#घोषणा NAU7802_PUCTRL_RR_BIT		NAU7802_PUCTRL_RR(1)
#घोषणा NAU7802_PUCTRL_PUD(x)		(x << 1)
#घोषणा NAU7802_PUCTRL_PUD_BIT		NAU7802_PUCTRL_PUD(1)
#घोषणा NAU7802_PUCTRL_PUA(x)		(x << 2)
#घोषणा NAU7802_PUCTRL_PUA_BIT		NAU7802_PUCTRL_PUA(1)
#घोषणा NAU7802_PUCTRL_PUR(x)		(x << 3)
#घोषणा NAU7802_PUCTRL_PUR_BIT		NAU7802_PUCTRL_PUR(1)
#घोषणा NAU7802_PUCTRL_CS(x)		(x << 4)
#घोषणा NAU7802_PUCTRL_CS_BIT		NAU7802_PUCTRL_CS(1)
#घोषणा NAU7802_PUCTRL_CR(x)		(x << 5)
#घोषणा NAU7802_PUCTRL_CR_BIT		NAU7802_PUCTRL_CR(1)
#घोषणा NAU7802_PUCTRL_AVDDS(x)		(x << 7)
#घोषणा NAU7802_PUCTRL_AVDDS_BIT	NAU7802_PUCTRL_AVDDS(1)
#घोषणा NAU7802_REG_CTRL1	0x01
#घोषणा NAU7802_CTRL1_VLDO(x)		(x << 3)
#घोषणा NAU7802_CTRL1_GAINS(x)		(x)
#घोषणा NAU7802_CTRL1_GAINS_BITS	0x07
#घोषणा NAU7802_REG_CTRL2	0x02
#घोषणा NAU7802_CTRL2_CHS(x)		(x << 7)
#घोषणा NAU7802_CTRL2_CRS(x)		(x << 4)
#घोषणा NAU7802_SAMP_FREQ_320	0x07
#घोषणा NAU7802_CTRL2_CHS_BIT		NAU7802_CTRL2_CHS(1)
#घोषणा NAU7802_REG_ADC_B2	0x12
#घोषणा NAU7802_REG_ADC_B1	0x13
#घोषणा NAU7802_REG_ADC_B0	0x14
#घोषणा NAU7802_REG_ADC_CTRL	0x15

#घोषणा NAU7802_MIN_CONVERSIONS 6

काष्ठा nau7802_state अणु
	काष्ठा i2c_client	*client;
	s32			last_value;
	काष्ठा mutex		lock;
	काष्ठा mutex		data_lock;
	u32			vref_mv;
	u32			conversion_count;
	u32			min_conversions;
	u8			sample_rate;
	u32			scale_avail[8];
	काष्ठा completion	value_ok;
पूर्ण;

#घोषणा NAU7802_CHANNEL(chan) अणु					\
	.type = IIO_VOLTAGE,					\
	.indexed = 1,						\
	.channel = (chan),					\
	.scan_index = (chan),					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) |	\
				BIT(IIO_CHAN_INFO_SAMP_FREQ)	\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec nau7802_chan_array[] = अणु
	NAU7802_CHANNEL(0),
	NAU7802_CHANNEL(1),
पूर्ण;

अटल स्थिर u16 nau7802_sample_freq_avail[] = अणु10, 20, 40, 80,
						10, 10, 10, 320पूर्ण;

अटल sमाप_प्रकार nau7802_show_scales(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nau7802_state *st = iio_priv(dev_to_iio_dev(dev));
	पूर्णांक i, len = 0;

	क्रम (i = 0; i < ARRAY_SIZE(st->scale_avail); i++)
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "0.%09d ",
				 st->scale_avail[i]);

	buf[len-1] = '\n';

	वापस len;
पूर्ण

अटल IIO_CONST_ATTR_SAMP_FREQ_AVAIL("10 40 80 320");

अटल IIO_DEVICE_ATTR(in_voltage_scale_available, S_IRUGO, nau7802_show_scales,
		       शून्य, 0);

अटल काष्ठा attribute *nau7802_attributes[] = अणु
	&iio_स्थिर_attr_sampling_frequency_available.dev_attr.attr,
	&iio_dev_attr_in_voltage_scale_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group nau7802_attribute_group = अणु
	.attrs = nau7802_attributes,
पूर्ण;

अटल पूर्णांक nau7802_set_gain(काष्ठा nau7802_state *st, पूर्णांक gain)
अणु
	पूर्णांक ret;

	mutex_lock(&st->lock);
	st->conversion_count = 0;

	ret = i2c_smbus_पढ़ो_byte_data(st->client, NAU7802_REG_CTRL1);
	अगर (ret < 0)
		जाओ nau7802_sysfs_set_gain_out;
	ret = i2c_smbus_ग_लिखो_byte_data(st->client, NAU7802_REG_CTRL1,
					(ret & (~NAU7802_CTRL1_GAINS_BITS)) |
					gain);

nau7802_sysfs_set_gain_out:
	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक nau7802_पढ़ो_conversion(काष्ठा nau7802_state *st)
अणु
	पूर्णांक data;

	mutex_lock(&st->data_lock);
	data = i2c_smbus_पढ़ो_byte_data(st->client, NAU7802_REG_ADC_B2);
	अगर (data < 0)
		जाओ nau7802_पढ़ो_conversion_out;
	st->last_value = data << 16;

	data = i2c_smbus_पढ़ो_byte_data(st->client, NAU7802_REG_ADC_B1);
	अगर (data < 0)
		जाओ nau7802_पढ़ो_conversion_out;
	st->last_value |= data << 8;

	data = i2c_smbus_पढ़ो_byte_data(st->client, NAU7802_REG_ADC_B0);
	अगर (data < 0)
		जाओ nau7802_पढ़ो_conversion_out;
	st->last_value |= data;

	st->last_value = sign_extend32(st->last_value, 23);

nau7802_पढ़ो_conversion_out:
	mutex_unlock(&st->data_lock);

	वापस data;
पूर्ण

/*
 * Conversions are synchronised on the rising edge of NAU7802_PUCTRL_CS_BIT
 */
अटल पूर्णांक nau7802_sync(काष्ठा nau7802_state *st)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(st->client, NAU7802_REG_PUCTRL);
	अगर (ret < 0)
		वापस ret;
	ret = i2c_smbus_ग_लिखो_byte_data(st->client, NAU7802_REG_PUCTRL,
				ret | NAU7802_PUCTRL_CS_BIT);

	वापस ret;
पूर्ण

अटल irqवापस_t nau7802_eoc_trigger(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा nau7802_state *st = iio_priv(indio_dev);
	पूर्णांक status;

	status = i2c_smbus_पढ़ो_byte_data(st->client, NAU7802_REG_PUCTRL);
	अगर (status < 0)
		वापस IRQ_HANDLED;

	अगर (!(status & NAU7802_PUCTRL_CR_BIT))
		वापस IRQ_NONE;

	अगर (nau7802_पढ़ो_conversion(st) < 0)
		वापस IRQ_HANDLED;

	/*
	 * Because there is actually only one ADC क्रम both channels, we have to
	 * रुको क्रम enough conversions to happen beक्रमe getting a signअगरicant
	 * value when changing channels and the values are far apart.
	 */
	अगर (st->conversion_count < NAU7802_MIN_CONVERSIONS)
		st->conversion_count++;
	अगर (st->conversion_count >= NAU7802_MIN_CONVERSIONS)
		complete(&st->value_ok);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक nau7802_पढ़ो_irq(काष्ठा iio_dev *indio_dev,
			काष्ठा iio_chan_spec स्थिर *chan,
			पूर्णांक *val)
अणु
	काष्ठा nau7802_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	reinit_completion(&st->value_ok);
	enable_irq(st->client->irq);

	nau7802_sync(st);

	/* पढ़ो रेजिस्टरs to ensure we flush everything */
	ret = nau7802_पढ़ो_conversion(st);
	अगर (ret < 0)
		जाओ पढ़ो_chan_info_failure;

	/* Wait क्रम a conversion to finish */
	ret = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&st->value_ok,
			msecs_to_jअगरfies(1000));
	अगर (ret == 0)
		ret = -ETIMEDOUT;

	अगर (ret < 0)
		जाओ पढ़ो_chan_info_failure;

	disable_irq(st->client->irq);

	*val = st->last_value;

	वापस IIO_VAL_INT;

पढ़ो_chan_info_failure:
	disable_irq(st->client->irq);

	वापस ret;
पूर्ण

अटल पूर्णांक nau7802_पढ़ो_poll(काष्ठा iio_dev *indio_dev,
			काष्ठा iio_chan_spec स्थिर *chan,
			पूर्णांक *val)
अणु
	काष्ठा nau7802_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	nau7802_sync(st);

	/* पढ़ो रेजिस्टरs to ensure we flush everything */
	ret = nau7802_पढ़ो_conversion(st);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Because there is actually only one ADC क्रम both channels, we have to
	 * रुको क्रम enough conversions to happen beक्रमe getting a signअगरicant
	 * value when changing channels and the values are far appart.
	 */
	करो अणु
		ret = i2c_smbus_पढ़ो_byte_data(st->client, NAU7802_REG_PUCTRL);
		अगर (ret < 0)
			वापस ret;

		जबतक (!(ret & NAU7802_PUCTRL_CR_BIT)) अणु
			अगर (st->sample_rate != NAU7802_SAMP_FREQ_320)
				msleep(20);
			अन्यथा
				mdelay(4);
			ret = i2c_smbus_पढ़ो_byte_data(st->client,
							NAU7802_REG_PUCTRL);
			अगर (ret < 0)
				वापस ret;
		पूर्ण

		ret = nau7802_पढ़ो_conversion(st);
		अगर (ret < 0)
			वापस ret;
		अगर (st->conversion_count < NAU7802_MIN_CONVERSIONS)
			st->conversion_count++;
	पूर्ण जबतक (st->conversion_count < NAU7802_MIN_CONVERSIONS);

	*val = st->last_value;

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक nau7802_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा nau7802_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&st->lock);
		/*
		 * Select the channel to use
		 *   - Channel 1 is value 0 in the CHS रेजिस्टर
		 *   - Channel 2 is value 1 in the CHS रेजिस्टर
		 */
		ret = i2c_smbus_पढ़ो_byte_data(st->client, NAU7802_REG_CTRL2);
		अगर (ret < 0) अणु
			mutex_unlock(&st->lock);
			वापस ret;
		पूर्ण

		अगर (((ret & NAU7802_CTRL2_CHS_BIT) && !chan->channel) ||
				(!(ret & NAU7802_CTRL2_CHS_BIT) &&
				 chan->channel)) अणु
			st->conversion_count = 0;
			ret = i2c_smbus_ग_लिखो_byte_data(st->client,
					NAU7802_REG_CTRL2,
					NAU7802_CTRL2_CHS(chan->channel) |
					NAU7802_CTRL2_CRS(st->sample_rate));

			अगर (ret < 0) अणु
				mutex_unlock(&st->lock);
				वापस ret;
			पूर्ण
		पूर्ण

		अगर (st->client->irq)
			ret = nau7802_पढ़ो_irq(indio_dev, chan, val);
		अन्यथा
			ret = nau7802_पढ़ो_poll(indio_dev, chan, val);

		mutex_unlock(&st->lock);
		वापस ret;

	हाल IIO_CHAN_INFO_SCALE:
		ret = i2c_smbus_पढ़ो_byte_data(st->client, NAU7802_REG_CTRL1);
		अगर (ret < 0)
			वापस ret;

		/*
		 * We have 24 bits of चिन्हित data, that means 23 bits of data
		 * plus the sign bit
		 */
		*val = st->vref_mv;
		*val2 = 23 + (ret & NAU7802_CTRL1_GAINS_BITS);

		वापस IIO_VAL_FRACTIONAL_LOG2;

	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*val =  nau7802_sample_freq_avail[st->sample_rate];
		*val2 = 0;
		वापस IIO_VAL_INT;

	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक nau7802_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा nau7802_state *st = iio_priv(indio_dev);
	पूर्णांक i, ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		क्रम (i = 0; i < ARRAY_SIZE(st->scale_avail); i++)
			अगर (val2 == st->scale_avail[i])
				वापस nau7802_set_gain(st, i);

		अवरोध;

	हाल IIO_CHAN_INFO_SAMP_FREQ:
		क्रम (i = 0; i < ARRAY_SIZE(nau7802_sample_freq_avail); i++)
			अगर (val == nau7802_sample_freq_avail[i]) अणु
				mutex_lock(&st->lock);
				st->sample_rate = i;
				st->conversion_count = 0;
				ret = i2c_smbus_ग_लिखो_byte_data(st->client,
					NAU7802_REG_CTRL2,
					NAU7802_CTRL2_CRS(st->sample_rate));
				mutex_unlock(&st->lock);
				वापस ret;
			पूर्ण

		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक nau7802_ग_लिखो_raw_get_fmt(काष्ठा iio_dev *indio_dev,
				     काष्ठा iio_chan_spec स्थिर *chan,
				     दीर्घ mask)
अणु
	वापस IIO_VAL_INT_PLUS_न_अंकO;
पूर्ण

अटल स्थिर काष्ठा iio_info nau7802_info = अणु
	.पढ़ो_raw = &nau7802_पढ़ो_raw,
	.ग_लिखो_raw = &nau7802_ग_लिखो_raw,
	.ग_लिखो_raw_get_fmt = nau7802_ग_लिखो_raw_get_fmt,
	.attrs = &nau7802_attribute_group,
पूर्ण;

अटल पूर्णांक nau7802_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा nau7802_state *st;
	काष्ठा device_node *np = client->dev.of_node;
	पूर्णांक i, ret;
	u8 data;
	u32 पंचांगp = 0;

	अगर (!client->dev.of_node) अणु
		dev_err(&client->dev, "No device tree node available.\n");
		वापस -EINVAL;
	पूर्ण

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*st));
	अगर (indio_dev == शून्य)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);

	i2c_set_clientdata(client, indio_dev);

	indio_dev->name = dev_name(&client->dev);
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &nau7802_info;

	st->client = client;

	/* Reset the device */
	ret = i2c_smbus_ग_लिखो_byte_data(st->client, NAU7802_REG_PUCTRL,
				  NAU7802_PUCTRL_RR_BIT);
	अगर (ret < 0)
		वापस ret;

	/* Enter normal operation mode */
	ret = i2c_smbus_ग_लिखो_byte_data(st->client, NAU7802_REG_PUCTRL,
				  NAU7802_PUCTRL_PUD_BIT);
	अगर (ret < 0)
		वापस ret;

	/*
	 * After about 200 usecs, the device should be पढ़ोy and then
	 * the Power Up bit will be set to 1. If not, रुको क्रम it.
	 */
	udelay(210);
	ret = i2c_smbus_पढ़ो_byte_data(st->client, NAU7802_REG_PUCTRL);
	अगर (ret < 0)
		वापस ret;
	अगर (!(ret & NAU7802_PUCTRL_PUR_BIT))
		वापस ret;

	of_property_पढ़ो_u32(np, "nuvoton,vldo", &पंचांगp);
	st->vref_mv = पंचांगp;

	data = NAU7802_PUCTRL_PUD_BIT | NAU7802_PUCTRL_PUA_BIT |
		NAU7802_PUCTRL_CS_BIT;
	अगर (पंचांगp >= 2400)
		data |= NAU7802_PUCTRL_AVDDS_BIT;

	ret = i2c_smbus_ग_लिखो_byte_data(st->client, NAU7802_REG_PUCTRL, data);
	अगर (ret < 0)
		वापस ret;
	ret = i2c_smbus_ग_लिखो_byte_data(st->client, NAU7802_REG_ADC_CTRL, 0x30);
	अगर (ret < 0)
		वापस ret;

	अगर (पंचांगp >= 2400) अणु
		data = NAU7802_CTRL1_VLDO((4500 - पंचांगp) / 300);
		ret = i2c_smbus_ग_लिखो_byte_data(st->client, NAU7802_REG_CTRL1,
						data);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Populate available ADC input ranges */
	क्रम (i = 0; i < ARRAY_SIZE(st->scale_avail); i++)
		st->scale_avail[i] = (((u64)st->vref_mv) * 1000000000ULL)
					   >> (23 + i);

	init_completion(&st->value_ok);

	/*
	 * The ADC fires continuously and we can't करो anything about
	 * it. So we need to have the IRQ disabled by शेष, and we
	 * will enable them back when we will need them..
	 */
	अगर (client->irq) अणु
		ret = request_thपढ़ोed_irq(client->irq,
				शून्य,
				nau7802_eoc_trigger,
				IRQF_TRIGGER_HIGH | IRQF_ONESHOT |
				IRQF_NO_AUTOEN,
				client->dev.driver->name,
				indio_dev);
		अगर (ret) अणु
			/*
			 * What may happen here is that our IRQ controller is
			 * not able to get level पूर्णांकerrupt but this is required
			 * by this ADC as when going over 40 sample per second,
			 * the पूर्णांकerrupt line may stay high between conversions.
			 * So, we जारी no matter what but we चयन to
			 * polling mode.
			 */
			dev_info(&client->dev,
				"Failed to allocate IRQ, using polling mode\n");
			client->irq = 0;
		पूर्ण
	पूर्ण

	अगर (!client->irq) अणु
		/*
		 * We are polling, use the fastest sample rate by
		 * शेष
		 */
		st->sample_rate = NAU7802_SAMP_FREQ_320;
		ret = i2c_smbus_ग_लिखो_byte_data(st->client, NAU7802_REG_CTRL2,
					  NAU7802_CTRL2_CRS(st->sample_rate));
		अगर (ret)
			जाओ error_मुक्त_irq;
	पूर्ण

	/* Setup the ADC channels available on the board */
	indio_dev->num_channels = ARRAY_SIZE(nau7802_chan_array);
	indio_dev->channels = nau7802_chan_array;

	mutex_init(&st->lock);
	mutex_init(&st->data_lock);

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Couldn't register the device.\n");
		जाओ error_device_रेजिस्टर;
	पूर्ण

	वापस 0;

error_device_रेजिस्टर:
	mutex_destroy(&st->lock);
	mutex_destroy(&st->data_lock);
error_मुक्त_irq:
	अगर (client->irq)
		मुक्त_irq(client->irq, indio_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक nau7802_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा nau7802_state *st = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	mutex_destroy(&st->lock);
	mutex_destroy(&st->data_lock);
	अगर (client->irq)
		मुक्त_irq(client->irq, indio_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id nau7802_i2c_id[] = अणु
	अणु "nau7802", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, nau7802_i2c_id);

अटल स्थिर काष्ठा of_device_id nau7802_dt_ids[] = अणु
	अणु .compatible = "nuvoton,nau7802" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, nau7802_dt_ids);

अटल काष्ठा i2c_driver nau7802_driver = अणु
	.probe = nau7802_probe,
	.हटाओ = nau7802_हटाओ,
	.id_table = nau7802_i2c_id,
	.driver = अणु
		   .name = "nau7802",
		   .of_match_table = nau7802_dt_ids,
	पूर्ण,
पूर्ण;

module_i2c_driver(nau7802_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Nuvoton NAU7802 ADC Driver");
MODULE_AUTHOR("Maxime Ripard <maxime.ripard@free-electrons.com>");
MODULE_AUTHOR("Alexandre Belloni <alexandre.belloni@free-electrons.com>");
