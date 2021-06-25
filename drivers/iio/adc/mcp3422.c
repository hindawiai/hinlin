<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * mcp3422.c - driver क्रम the Microchip mcp3421/2/3/4/5/6/7/8 chip family
 *
 * Copyright (C) 2013, Angelo Compagnucci
 * Author: Angelo Compagnucci <angelo.compagnucci@gmail.com>
 *
 * Datasheet: http://ww1.microchip.com/करोwnloads/en/deviceकरोc/22088b.pdf
 *            https://ww1.microchip.com/करोwnloads/en/DeviceDoc/22226a.pdf
 *            https://ww1.microchip.com/करोwnloads/en/DeviceDoc/22072b.pdf
 *
 * This driver exports the value of analog input voltage to sysfs, the
 * voltage unit is nV.
 */

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/delay.h>
#समावेश <linux/sysfs.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

/* Masks */
#घोषणा MCP3422_CHANNEL_MASK	0x60
#घोषणा MCP3422_PGA_MASK	0x03
#घोषणा MCP3422_SRATE_MASK	0x0C
#घोषणा MCP3422_SRATE_240	0x0
#घोषणा MCP3422_SRATE_60	0x1
#घोषणा MCP3422_SRATE_15	0x2
#घोषणा MCP3422_SRATE_3	0x3
#घोषणा MCP3422_PGA_1	0
#घोषणा MCP3422_PGA_2	1
#घोषणा MCP3422_PGA_4	2
#घोषणा MCP3422_PGA_8	3
#घोषणा MCP3422_CONT_SAMPLING	0x10

#घोषणा MCP3422_CHANNEL(config)	(((config) & MCP3422_CHANNEL_MASK) >> 5)
#घोषणा MCP3422_PGA(config)	((config) & MCP3422_PGA_MASK)
#घोषणा MCP3422_SAMPLE_RATE(config)	(((config) & MCP3422_SRATE_MASK) >> 2)

#घोषणा MCP3422_CHANNEL_VALUE(value) (((value) << 5) & MCP3422_CHANNEL_MASK)
#घोषणा MCP3422_PGA_VALUE(value) ((value) & MCP3422_PGA_MASK)
#घोषणा MCP3422_SAMPLE_RATE_VALUE(value) ((value << 2) & MCP3422_SRATE_MASK)

#घोषणा MCP3422_CHAN(_index) \
	अणु \
		.type = IIO_VOLTAGE, \
		.indexed = 1, \
		.channel = _index, \
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) \
				| BIT(IIO_CHAN_INFO_SCALE), \
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SAMP_FREQ), \
	पूर्ण

अटल स्थिर पूर्णांक mcp3422_scales[4][4] = अणु
	अणु 1000000, 500000, 250000, 125000 पूर्ण,
	अणु 250000,  125000, 62500,  31250  पूर्ण,
	अणु 62500,   31250,  15625,  7812   पूर्ण,
	अणु 15625,   7812,   3906,   1953   पूर्ण पूर्ण;

/* Constant msleep बार क्रम data acquisitions */
अटल स्थिर पूर्णांक mcp3422_पढ़ो_बार[4] = अणु
	[MCP3422_SRATE_240] = 1000 / 240,
	[MCP3422_SRATE_60] = 1000 / 60,
	[MCP3422_SRATE_15] = 1000 / 15,
	[MCP3422_SRATE_3] = 1000 / 3 पूर्ण;

/* sample rates to पूर्णांकeger conversion table */
अटल स्थिर पूर्णांक mcp3422_sample_rates[4] = अणु
	[MCP3422_SRATE_240] = 240,
	[MCP3422_SRATE_60] = 60,
	[MCP3422_SRATE_15] = 15,
	[MCP3422_SRATE_3] = 3 पूर्ण;

/* sample rates to sign extension table */
अटल स्थिर पूर्णांक mcp3422_sign_extend[4] = अणु
	[MCP3422_SRATE_240] = 11,
	[MCP3422_SRATE_60] = 13,
	[MCP3422_SRATE_15] = 15,
	[MCP3422_SRATE_3] = 17 पूर्ण;

/* Client data (each client माला_लो its own) */
काष्ठा mcp3422 अणु
	काष्ठा i2c_client *i2c;
	u8 id;
	u8 config;
	u8 pga[4];
	काष्ठा mutex lock;
पूर्ण;

अटल पूर्णांक mcp3422_update_config(काष्ठा mcp3422 *adc, u8 newconfig)
अणु
	पूर्णांक ret;

	ret = i2c_master_send(adc->i2c, &newconfig, 1);
	अगर (ret > 0) अणु
		adc->config = newconfig;
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mcp3422_पढ़ो(काष्ठा mcp3422 *adc, पूर्णांक *value, u8 *config)
अणु
	पूर्णांक ret = 0;
	u8 sample_rate = MCP3422_SAMPLE_RATE(adc->config);
	u8 buf[4] = अणु0, 0, 0, 0पूर्ण;
	u32 temp;

	अगर (sample_rate == MCP3422_SRATE_3) अणु
		ret = i2c_master_recv(adc->i2c, buf, 4);
		temp = get_unaligned_be24(&buf[0]);
		*config = buf[3];
	पूर्ण अन्यथा अणु
		ret = i2c_master_recv(adc->i2c, buf, 3);
		temp = get_unaligned_be16(&buf[0]);
		*config = buf[2];
	पूर्ण

	*value = sign_extend32(temp, mcp3422_sign_extend[sample_rate]);

	वापस ret;
पूर्ण

अटल पूर्णांक mcp3422_पढ़ो_channel(काष्ठा mcp3422 *adc,
				काष्ठा iio_chan_spec स्थिर *channel, पूर्णांक *value)
अणु
	पूर्णांक ret;
	u8 config;
	u8 req_channel = channel->channel;

	mutex_lock(&adc->lock);

	अगर (req_channel != MCP3422_CHANNEL(adc->config)) अणु
		config = adc->config;
		config &= ~MCP3422_CHANNEL_MASK;
		config |= MCP3422_CHANNEL_VALUE(req_channel);
		config &= ~MCP3422_PGA_MASK;
		config |= MCP3422_PGA_VALUE(adc->pga[req_channel]);
		ret = mcp3422_update_config(adc, config);
		अगर (ret < 0) अणु
			mutex_unlock(&adc->lock);
			वापस ret;
		पूर्ण
		msleep(mcp3422_पढ़ो_बार[MCP3422_SAMPLE_RATE(adc->config)]);
	पूर्ण

	ret = mcp3422_पढ़ो(adc, value, &config);

	mutex_unlock(&adc->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक mcp3422_पढ़ो_raw(काष्ठा iio_dev *iio,
			काष्ठा iio_chan_spec स्थिर *channel, पूर्णांक *val1,
			पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा mcp3422 *adc = iio_priv(iio);
	पूर्णांक err;

	u8 sample_rate = MCP3422_SAMPLE_RATE(adc->config);
	u8 pga		 = MCP3422_PGA(adc->config);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		err = mcp3422_पढ़ो_channel(adc, channel, val1);
		अगर (err < 0)
			वापस -EINVAL;
		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:

		*val1 = 0;
		*val2 = mcp3422_scales[sample_rate][pga];
		वापस IIO_VAL_INT_PLUS_न_अंकO;

	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*val1 = mcp3422_sample_rates[MCP3422_SAMPLE_RATE(adc->config)];
		वापस IIO_VAL_INT;

	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mcp3422_ग_लिखो_raw(काष्ठा iio_dev *iio,
			काष्ठा iio_chan_spec स्थिर *channel, पूर्णांक val1,
			पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा mcp3422 *adc = iio_priv(iio);
	u8 temp;
	u8 config = adc->config;
	u8 req_channel = channel->channel;
	u8 sample_rate = MCP3422_SAMPLE_RATE(config);
	u8 i;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		अगर (val1 != 0)
			वापस -EINVAL;

		क्रम (i = 0; i < ARRAY_SIZE(mcp3422_scales[0]); i++) अणु
			अगर (val2 == mcp3422_scales[sample_rate][i]) अणु
				adc->pga[req_channel] = i;

				config &= ~MCP3422_CHANNEL_MASK;
				config |= MCP3422_CHANNEL_VALUE(req_channel);
				config &= ~MCP3422_PGA_MASK;
				config |= MCP3422_PGA_VALUE(adc->pga[req_channel]);

				वापस mcp3422_update_config(adc, config);
			पूर्ण
		पूर्ण
		वापस -EINVAL;

	हाल IIO_CHAN_INFO_SAMP_FREQ:
		चयन (val1) अणु
		हाल 240:
			temp = MCP3422_SRATE_240;
			अवरोध;
		हाल 60:
			temp = MCP3422_SRATE_60;
			अवरोध;
		हाल 15:
			temp = MCP3422_SRATE_15;
			अवरोध;
		हाल 3:
			अगर (adc->id > 4)
				वापस -EINVAL;
			temp = MCP3422_SRATE_3;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		config &= ~MCP3422_CHANNEL_MASK;
		config |= MCP3422_CHANNEL_VALUE(req_channel);
		config &= ~MCP3422_SRATE_MASK;
		config |= MCP3422_SAMPLE_RATE_VALUE(temp);

		वापस mcp3422_update_config(adc, config);

	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mcp3422_ग_लिखो_raw_get_fmt(काष्ठा iio_dev *indio_dev,
		काष्ठा iio_chan_spec स्थिर *chan, दीर्घ mask)
अणु
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		वापस IIO_VAL_INT_PLUS_न_अंकO;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		वापस IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार mcp3422_show_samp_freqs(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mcp3422 *adc = iio_priv(dev_to_iio_dev(dev));

	अगर (adc->id > 4)
		वापस प्र_लिखो(buf, "240 60 15\n");

	वापस प्र_लिखो(buf, "240 60 15 3\n");
पूर्ण

अटल sमाप_प्रकार mcp3422_show_scales(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mcp3422 *adc = iio_priv(dev_to_iio_dev(dev));
	u8 sample_rate = MCP3422_SAMPLE_RATE(adc->config);

	वापस प्र_लिखो(buf, "0.%09u 0.%09u 0.%09u 0.%09u\n",
		mcp3422_scales[sample_rate][0],
		mcp3422_scales[sample_rate][1],
		mcp3422_scales[sample_rate][2],
		mcp3422_scales[sample_rate][3]);
पूर्ण

अटल IIO_DEVICE_ATTR(sampling_frequency_available, S_IRUGO,
		mcp3422_show_samp_freqs, शून्य, 0);
अटल IIO_DEVICE_ATTR(in_voltage_scale_available, S_IRUGO,
		mcp3422_show_scales, शून्य, 0);

अटल काष्ठा attribute *mcp3422_attributes[] = अणु
	&iio_dev_attr_sampling_frequency_available.dev_attr.attr,
	&iio_dev_attr_in_voltage_scale_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group mcp3422_attribute_group = अणु
	.attrs = mcp3422_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec mcp3421_channels[] = अणु
	MCP3422_CHAN(0),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec mcp3422_channels[] = अणु
	MCP3422_CHAN(0),
	MCP3422_CHAN(1),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec mcp3424_channels[] = अणु
	MCP3422_CHAN(0),
	MCP3422_CHAN(1),
	MCP3422_CHAN(2),
	MCP3422_CHAN(3),
पूर्ण;

अटल स्थिर काष्ठा iio_info mcp3422_info = अणु
	.पढ़ो_raw = mcp3422_पढ़ो_raw,
	.ग_लिखो_raw = mcp3422_ग_लिखो_raw,
	.ग_लिखो_raw_get_fmt = mcp3422_ग_लिखो_raw_get_fmt,
	.attrs = &mcp3422_attribute_group,
पूर्ण;

अटल पूर्णांक mcp3422_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा mcp3422 *adc;
	पूर्णांक err;
	u8 config;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		वापस -EOPNOTSUPP;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*adc));
	अगर (!indio_dev)
		वापस -ENOMEM;

	adc = iio_priv(indio_dev);
	adc->i2c = client;
	adc->id = (u8)(id->driver_data);

	mutex_init(&adc->lock);

	indio_dev->name = dev_name(&client->dev);
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &mcp3422_info;

	चयन (adc->id) अणु
	हाल 1:
	हाल 5:
		indio_dev->channels = mcp3421_channels;
		indio_dev->num_channels = ARRAY_SIZE(mcp3421_channels);
		अवरोध;
	हाल 2:
	हाल 3:
	हाल 6:
	हाल 7:
		indio_dev->channels = mcp3422_channels;
		indio_dev->num_channels = ARRAY_SIZE(mcp3422_channels);
		अवरोध;
	हाल 4:
	हाल 8:
		indio_dev->channels = mcp3424_channels;
		indio_dev->num_channels = ARRAY_SIZE(mcp3424_channels);
		अवरोध;
	पूर्ण

	/* meaningful शेष configuration */
	config = (MCP3422_CONT_SAMPLING
		| MCP3422_CHANNEL_VALUE(0)
		| MCP3422_PGA_VALUE(MCP3422_PGA_1)
		| MCP3422_SAMPLE_RATE_VALUE(MCP3422_SRATE_240));
	err = mcp3422_update_config(adc, config);
	अगर (err < 0)
		वापस err;

	err = devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
	अगर (err < 0)
		वापस err;

	i2c_set_clientdata(client, indio_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id mcp3422_id[] = अणु
	अणु "mcp3421", 1 पूर्ण,
	अणु "mcp3422", 2 पूर्ण,
	अणु "mcp3423", 3 पूर्ण,
	अणु "mcp3424", 4 पूर्ण,
	अणु "mcp3425", 5 पूर्ण,
	अणु "mcp3426", 6 पूर्ण,
	अणु "mcp3427", 7 पूर्ण,
	अणु "mcp3428", 8 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mcp3422_id);

अटल स्थिर काष्ठा of_device_id mcp3422_of_match[] = अणु
	अणु .compatible = "mcp3422" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mcp3422_of_match);

अटल काष्ठा i2c_driver mcp3422_driver = अणु
	.driver = अणु
		.name = "mcp3422",
		.of_match_table = mcp3422_of_match,
	पूर्ण,
	.probe = mcp3422_probe,
	.id_table = mcp3422_id,
पूर्ण;
module_i2c_driver(mcp3422_driver);

MODULE_AUTHOR("Angelo Compagnucci <angelo.compagnucci@gmail.com>");
MODULE_DESCRIPTION("Microchip mcp3421/2/3/4/5/6/7/8 driver");
MODULE_LICENSE("GPL v2");
