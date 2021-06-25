<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * iio/adc/ad799x.c
 * Copyright (C) 2010-2011 Michael Hennerich, Analog Devices Inc.
 *
 * based on iio/adc/max1363
 * Copyright (C) 2008-2010 Jonathan Cameron
 *
 * based on linux/drivers/i2c/chips/max123x
 * Copyright (C) 2002-2004 Stefan Eletzhofer
 *
 * based on linux/drivers/acron/अक्षर/pcf8583.c
 * Copyright (C) 2000 Russell King
 *
 * ad799x.c
 *
 * Support क्रम ad7991, ad7995, ad7999, ad7992, ad7993, ad7994, ad7997,
 * ad7998 and similar chips.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/bitops.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>

#घोषणा AD799X_CHANNEL_SHIFT			4

/*
 * AD7991, AD7995 and AD7999 defines
 */

#घोषणा AD7991_REF_SEL				0x08
#घोषणा AD7991_FLTR				0x04
#घोषणा AD7991_BIT_TRIAL_DELAY			0x02
#घोषणा AD7991_SAMPLE_DELAY			0x01

/*
 * AD7992, AD7993, AD7994, AD7997 and AD7998 defines
 */

#घोषणा AD7998_FLTR				BIT(3)
#घोषणा AD7998_ALERT_EN				BIT(2)
#घोषणा AD7998_BUSY_ALERT			BIT(1)
#घोषणा AD7998_BUSY_ALERT_POL			BIT(0)

#घोषणा AD7998_CONV_RES_REG			0x0
#घोषणा AD7998_ALERT_STAT_REG			0x1
#घोषणा AD7998_CONF_REG				0x2
#घोषणा AD7998_CYCLE_TMR_REG			0x3

#घोषणा AD7998_DATALOW_REG(x)			((x) * 3 + 0x4)
#घोषणा AD7998_DATAHIGH_REG(x)			((x) * 3 + 0x5)
#घोषणा AD7998_HYST_REG(x)			((x) * 3 + 0x6)

#घोषणा AD7998_CYC_MASK				GENMASK(2, 0)
#घोषणा AD7998_CYC_DIS				0x0
#घोषणा AD7998_CYC_TCONF_32			0x1
#घोषणा AD7998_CYC_TCONF_64			0x2
#घोषणा AD7998_CYC_TCONF_128			0x3
#घोषणा AD7998_CYC_TCONF_256			0x4
#घोषणा AD7998_CYC_TCONF_512			0x5
#घोषणा AD7998_CYC_TCONF_1024			0x6
#घोषणा AD7998_CYC_TCONF_2048			0x7

#घोषणा AD7998_ALERT_STAT_CLEAR			0xFF

/*
 * AD7997 and AD7997 defines
 */

#घोषणा AD7997_8_READ_SINGLE			BIT(7)
#घोषणा AD7997_8_READ_SEQUENCE			(BIT(6) | BIT(5) | BIT(4))

क्रमागत अणु
	ad7991,
	ad7995,
	ad7999,
	ad7992,
	ad7993,
	ad7994,
	ad7997,
	ad7998
पूर्ण;

/**
 * काष्ठा ad799x_chip_config - chip specअगरic inक्रमmation
 * @channel:		channel specअगरication
 * @शेष_config:	device शेष configuration
 * @info:		poपूर्णांकer to iio_info काष्ठा
 */
काष्ठा ad799x_chip_config अणु
	स्थिर काष्ठा iio_chan_spec	channel[9];
	u16				शेष_config;
	स्थिर काष्ठा iio_info		*info;
पूर्ण;

/**
 * काष्ठा ad799x_chip_info - chip specअगरic inक्रमmation
 * @num_channels:	number of channels
 * @noirq_config:	device configuration w/o IRQ
 * @irq_config:		device configuration w/IRQ
 */
काष्ठा ad799x_chip_info अणु
	पूर्णांक				num_channels;
	स्थिर काष्ठा ad799x_chip_config	noirq_config;
	स्थिर काष्ठा ad799x_chip_config	irq_config;
पूर्ण;

काष्ठा ad799x_state अणु
	काष्ठा i2c_client		*client;
	स्थिर काष्ठा ad799x_chip_config	*chip_config;
	काष्ठा regulator		*reg;
	काष्ठा regulator		*vref;
	अचिन्हित			id;
	u16				config;

	u8				*rx_buf;
	अचिन्हित पूर्णांक			transfer_size;
पूर्ण;

अटल पूर्णांक ad799x_ग_लिखो_config(काष्ठा ad799x_state *st, u16 val)
अणु
	चयन (st->id) अणु
	हाल ad7997:
	हाल ad7998:
		वापस i2c_smbus_ग_लिखो_word_swapped(st->client, AD7998_CONF_REG,
			val);
	हाल ad7992:
	हाल ad7993:
	हाल ad7994:
		वापस i2c_smbus_ग_लिखो_byte_data(st->client, AD7998_CONF_REG,
			val);
	शेष:
		/* Will be written when करोing a conversion */
		st->config = val;
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक ad799x_पढ़ो_config(काष्ठा ad799x_state *st)
अणु
	चयन (st->id) अणु
	हाल ad7997:
	हाल ad7998:
		वापस i2c_smbus_पढ़ो_word_swapped(st->client, AD7998_CONF_REG);
	हाल ad7992:
	हाल ad7993:
	हाल ad7994:
		वापस i2c_smbus_पढ़ो_byte_data(st->client, AD7998_CONF_REG);
	शेष:
		/* No पढ़ोback support */
		वापस st->config;
	पूर्ण
पूर्ण

अटल पूर्णांक ad799x_update_config(काष्ठा ad799x_state *st, u16 config)
अणु
	पूर्णांक ret;

	ret = ad799x_ग_लिखो_config(st, config);
	अगर (ret < 0)
		वापस ret;
	ret = ad799x_पढ़ो_config(st);
	अगर (ret < 0)
		वापस ret;
	st->config = ret;

	वापस 0;
पूर्ण

अटल irqवापस_t ad799x_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा ad799x_state *st = iio_priv(indio_dev);
	पूर्णांक b_sent;
	u8 cmd;

	चयन (st->id) अणु
	हाल ad7991:
	हाल ad7995:
	हाल ad7999:
		cmd = st->config |
			(*indio_dev->active_scan_mask << AD799X_CHANNEL_SHIFT);
		अवरोध;
	हाल ad7992:
	हाल ad7993:
	हाल ad7994:
		cmd = (*indio_dev->active_scan_mask << AD799X_CHANNEL_SHIFT) |
			AD7998_CONV_RES_REG;
		अवरोध;
	हाल ad7997:
	हाल ad7998:
		cmd = AD7997_8_READ_SEQUENCE | AD7998_CONV_RES_REG;
		अवरोध;
	शेष:
		cmd = 0;
	पूर्ण

	b_sent = i2c_smbus_पढ़ो_i2c_block_data(st->client,
			cmd, st->transfer_size, st->rx_buf);
	अगर (b_sent < 0)
		जाओ out;

	iio_push_to_buffers_with_बारtamp(indio_dev, st->rx_buf,
			iio_get_समय_ns(indio_dev));
out:
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ad799x_update_scan_mode(काष्ठा iio_dev *indio_dev,
	स्थिर अचिन्हित दीर्घ *scan_mask)
अणु
	काष्ठा ad799x_state *st = iio_priv(indio_dev);

	kमुक्त(st->rx_buf);
	st->rx_buf = kदो_स्मृति(indio_dev->scan_bytes, GFP_KERNEL);
	अगर (!st->rx_buf)
		वापस -ENOMEM;

	st->transfer_size = biपंचांगap_weight(scan_mask, indio_dev->masklength) * 2;

	चयन (st->id) अणु
	हाल ad7992:
	हाल ad7993:
	हाल ad7994:
	हाल ad7997:
	हाल ad7998:
		st->config &= ~(GENMASK(7, 0) << AD799X_CHANNEL_SHIFT);
		st->config |= (*scan_mask << AD799X_CHANNEL_SHIFT);
		वापस ad799x_ग_लिखो_config(st, st->config);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक ad799x_scan_direct(काष्ठा ad799x_state *st, अचिन्हित ch)
अणु
	u8 cmd;

	चयन (st->id) अणु
	हाल ad7991:
	हाल ad7995:
	हाल ad7999:
		cmd = st->config | (BIT(ch) << AD799X_CHANNEL_SHIFT);
		अवरोध;
	हाल ad7992:
	हाल ad7993:
	हाल ad7994:
		cmd = BIT(ch) << AD799X_CHANNEL_SHIFT;
		अवरोध;
	हाल ad7997:
	हाल ad7998:
		cmd = (ch << AD799X_CHANNEL_SHIFT) | AD7997_8_READ_SINGLE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस i2c_smbus_पढ़ो_word_swapped(st->client, cmd);
पूर्ण

अटल पूर्णांक ad799x_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val,
			   पूर्णांक *val2,
			   दीर्घ m)
अणु
	पूर्णांक ret;
	काष्ठा ad799x_state *st = iio_priv(indio_dev);

	चयन (m) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;
		ret = ad799x_scan_direct(st, chan->scan_index);
		iio_device_release_direct_mode(indio_dev);

		अगर (ret < 0)
			वापस ret;
		*val = (ret >> chan->scan_type.shअगरt) &
			GENMASK(chan->scan_type.realbits - 1, 0);
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		ret = regulator_get_voltage(st->vref);
		अगर (ret < 0)
			वापस ret;
		*val = ret / 1000;
		*val2 = chan->scan_type.realbits;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	पूर्ण
	वापस -EINVAL;
पूर्ण
अटल स्थिर अचिन्हित पूर्णांक ad7998_frequencies[] = अणु
	[AD7998_CYC_DIS]	= 0,
	[AD7998_CYC_TCONF_32]	= 15625,
	[AD7998_CYC_TCONF_64]	= 7812,
	[AD7998_CYC_TCONF_128]	= 3906,
	[AD7998_CYC_TCONF_512]	= 976,
	[AD7998_CYC_TCONF_1024]	= 488,
	[AD7998_CYC_TCONF_2048]	= 244,
पूर्ण;

अटल sमाप_प्रकार ad799x_पढ़ो_frequency(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ad799x_state *st = iio_priv(indio_dev);

	पूर्णांक ret = i2c_smbus_पढ़ो_byte_data(st->client, AD7998_CYCLE_TMR_REG);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%u\n", ad7998_frequencies[ret & AD7998_CYC_MASK]);
पूर्ण

अटल sमाप_प्रकार ad799x_ग_लिखो_frequency(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *buf,
					 माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ad799x_state *st = iio_priv(indio_dev);

	दीर्घ val;
	पूर्णांक ret, i;

	ret = kम_से_दीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	mutex_lock(&indio_dev->mlock);
	ret = i2c_smbus_पढ़ो_byte_data(st->client, AD7998_CYCLE_TMR_REG);
	अगर (ret < 0)
		जाओ error_ret_mutex;
	/* Wipe the bits clean */
	ret &= ~AD7998_CYC_MASK;

	क्रम (i = 0; i < ARRAY_SIZE(ad7998_frequencies); i++)
		अगर (val == ad7998_frequencies[i])
			अवरोध;
	अगर (i == ARRAY_SIZE(ad7998_frequencies)) अणु
		ret = -EINVAL;
		जाओ error_ret_mutex;
	पूर्ण

	ret = i2c_smbus_ग_लिखो_byte_data(st->client, AD7998_CYCLE_TMR_REG,
		ret | i);
	अगर (ret < 0)
		जाओ error_ret_mutex;
	ret = len;

error_ret_mutex:
	mutex_unlock(&indio_dev->mlock);

	वापस ret;
पूर्ण

अटल पूर्णांक ad799x_पढ़ो_event_config(काष्ठा iio_dev *indio_dev,
				    स्थिर काष्ठा iio_chan_spec *chan,
				    क्रमागत iio_event_type type,
				    क्रमागत iio_event_direction dir)
अणु
	काष्ठा ad799x_state *st = iio_priv(indio_dev);

	अगर (!(st->config & AD7998_ALERT_EN))
		वापस 0;

	अगर ((st->config >> AD799X_CHANNEL_SHIFT) & BIT(chan->scan_index))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक ad799x_ग_लिखो_event_config(काष्ठा iio_dev *indio_dev,
				     स्थिर काष्ठा iio_chan_spec *chan,
				     क्रमागत iio_event_type type,
				     क्रमागत iio_event_direction dir,
				     पूर्णांक state)
अणु
	काष्ठा ad799x_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = iio_device_claim_direct_mode(indio_dev);
	अगर (ret)
		वापस ret;

	अगर (state)
		st->config |= BIT(chan->scan_index) << AD799X_CHANNEL_SHIFT;
	अन्यथा
		st->config &= ~(BIT(chan->scan_index) << AD799X_CHANNEL_SHIFT);

	अगर (st->config >> AD799X_CHANNEL_SHIFT)
		st->config |= AD7998_ALERT_EN;
	अन्यथा
		st->config &= ~AD7998_ALERT_EN;

	ret = ad799x_ग_लिखो_config(st, st->config);
	iio_device_release_direct_mode(indio_dev);
	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक ad799x_threshold_reg(स्थिर काष्ठा iio_chan_spec *chan,
					 क्रमागत iio_event_direction dir,
					 क्रमागत iio_event_info info)
अणु
	चयन (info) अणु
	हाल IIO_EV_INFO_VALUE:
		अगर (dir == IIO_EV_सूची_FALLING)
			वापस AD7998_DATALOW_REG(chan->channel);
		अन्यथा
			वापस AD7998_DATAHIGH_REG(chan->channel);
	हाल IIO_EV_INFO_HYSTERESIS:
		वापस AD7998_HYST_REG(chan->channel);
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ad799x_ग_लिखो_event_value(काष्ठा iio_dev *indio_dev,
				    स्थिर काष्ठा iio_chan_spec *chan,
				    क्रमागत iio_event_type type,
				    क्रमागत iio_event_direction dir,
				    क्रमागत iio_event_info info,
				    पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक ret;
	काष्ठा ad799x_state *st = iio_priv(indio_dev);

	अगर (val < 0 || val > GENMASK(chan->scan_type.realbits - 1, 0))
		वापस -EINVAL;

	mutex_lock(&indio_dev->mlock);
	ret = i2c_smbus_ग_लिखो_word_swapped(st->client,
		ad799x_threshold_reg(chan, dir, info),
		val << chan->scan_type.shअगरt);
	mutex_unlock(&indio_dev->mlock);

	वापस ret;
पूर्ण

अटल पूर्णांक ad799x_पढ़ो_event_value(काष्ठा iio_dev *indio_dev,
				    स्थिर काष्ठा iio_chan_spec *chan,
				    क्रमागत iio_event_type type,
				    क्रमागत iio_event_direction dir,
				    क्रमागत iio_event_info info,
				    पूर्णांक *val, पूर्णांक *val2)
अणु
	पूर्णांक ret;
	काष्ठा ad799x_state *st = iio_priv(indio_dev);

	mutex_lock(&indio_dev->mlock);
	ret = i2c_smbus_पढ़ो_word_swapped(st->client,
		ad799x_threshold_reg(chan, dir, info));
	mutex_unlock(&indio_dev->mlock);
	अगर (ret < 0)
		वापस ret;
	*val = (ret >> chan->scan_type.shअगरt) &
		GENMASK(chan->scan_type.realbits - 1, 0);

	वापस IIO_VAL_INT;
पूर्ण

अटल irqवापस_t ad799x_event_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा ad799x_state *st = iio_priv(निजी);
	पूर्णांक i, ret;

	ret = i2c_smbus_पढ़ो_byte_data(st->client, AD7998_ALERT_STAT_REG);
	अगर (ret <= 0)
		जाओ करोne;

	अगर (i2c_smbus_ग_लिखो_byte_data(st->client, AD7998_ALERT_STAT_REG,
		AD7998_ALERT_STAT_CLEAR) < 0)
		जाओ करोne;

	क्रम (i = 0; i < 8; i++) अणु
		अगर (ret & BIT(i))
			iio_push_event(indio_dev,
				       i & 0x1 ?
				       IIO_UNMOD_EVENT_CODE(IIO_VOLTAGE,
							    (i >> 1),
							    IIO_EV_TYPE_THRESH,
							    IIO_EV_सूची_RISING) :
				       IIO_UNMOD_EVENT_CODE(IIO_VOLTAGE,
							    (i >> 1),
							    IIO_EV_TYPE_THRESH,
							    IIO_EV_सूची_FALLING),
				       iio_get_समय_ns(indio_dev));
	पूर्ण

करोne:
	वापस IRQ_HANDLED;
पूर्ण

अटल IIO_DEV_ATTR_SAMP_FREQ(S_IWUSR | S_IRUGO,
			      ad799x_पढ़ो_frequency,
			      ad799x_ग_लिखो_frequency);
अटल IIO_CONST_ATTR_SAMP_FREQ_AVAIL("15625 7812 3906 1953 976 488 244 0");

अटल काष्ठा attribute *ad799x_event_attributes[] = अणु
	&iio_dev_attr_sampling_frequency.dev_attr.attr,
	&iio_स्थिर_attr_sampling_frequency_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ad799x_event_attrs_group = अणु
	.attrs = ad799x_event_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info ad7991_info = अणु
	.पढ़ो_raw = &ad799x_पढ़ो_raw,
	.update_scan_mode = ad799x_update_scan_mode,
पूर्ण;

अटल स्थिर काष्ठा iio_info ad7993_4_7_8_noirq_info = अणु
	.पढ़ो_raw = &ad799x_पढ़ो_raw,
	.update_scan_mode = ad799x_update_scan_mode,
पूर्ण;

अटल स्थिर काष्ठा iio_info ad7993_4_7_8_irq_info = अणु
	.पढ़ो_raw = &ad799x_पढ़ो_raw,
	.event_attrs = &ad799x_event_attrs_group,
	.पढ़ो_event_config = &ad799x_पढ़ो_event_config,
	.ग_लिखो_event_config = &ad799x_ग_लिखो_event_config,
	.पढ़ो_event_value = &ad799x_पढ़ो_event_value,
	.ग_लिखो_event_value = &ad799x_ग_लिखो_event_value,
	.update_scan_mode = ad799x_update_scan_mode,
पूर्ण;

अटल स्थिर काष्ठा iio_event_spec ad799x_events[] = अणु
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
	पूर्ण, अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_EITHER,
		.mask_separate = BIT(IIO_EV_INFO_HYSTERESIS),
	पूर्ण,
पूर्ण;

#घोषणा _AD799X_CHANNEL(_index, _realbits, _ev_spec, _num_ev_spec) अणु \
	.type = IIO_VOLTAGE, \
	.indexed = 1, \
	.channel = (_index), \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW), \
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE), \
	.scan_index = (_index), \
	.scan_type = अणु \
		.sign = 'u', \
		.realbits = (_realbits), \
		.storagebits = 16, \
		.shअगरt = 12 - (_realbits), \
		.endianness = IIO_BE, \
	पूर्ण, \
	.event_spec = _ev_spec, \
	.num_event_specs = _num_ev_spec, \
पूर्ण

#घोषणा AD799X_CHANNEL(_index, _realbits) \
	_AD799X_CHANNEL(_index, _realbits, शून्य, 0)

#घोषणा AD799X_CHANNEL_WITH_EVENTS(_index, _realbits) \
	_AD799X_CHANNEL(_index, _realbits, ad799x_events, \
		ARRAY_SIZE(ad799x_events))

अटल स्थिर काष्ठा ad799x_chip_info ad799x_chip_info_tbl[] = अणु
	[ad7991] = अणु
		.num_channels = 5,
		.noirq_config = अणु
			.channel = अणु
				AD799X_CHANNEL(0, 12),
				AD799X_CHANNEL(1, 12),
				AD799X_CHANNEL(2, 12),
				AD799X_CHANNEL(3, 12),
				IIO_CHAN_SOFT_TIMESTAMP(4),
			पूर्ण,
			.info = &ad7991_info,
		पूर्ण,
	पूर्ण,
	[ad7995] = अणु
		.num_channels = 5,
		.noirq_config = अणु
			.channel = अणु
				AD799X_CHANNEL(0, 10),
				AD799X_CHANNEL(1, 10),
				AD799X_CHANNEL(2, 10),
				AD799X_CHANNEL(3, 10),
				IIO_CHAN_SOFT_TIMESTAMP(4),
			पूर्ण,
			.info = &ad7991_info,
		पूर्ण,
	पूर्ण,
	[ad7999] = अणु
		.num_channels = 5,
		.noirq_config = अणु
			.channel = अणु
				AD799X_CHANNEL(0, 8),
				AD799X_CHANNEL(1, 8),
				AD799X_CHANNEL(2, 8),
				AD799X_CHANNEL(3, 8),
				IIO_CHAN_SOFT_TIMESTAMP(4),
			पूर्ण,
			.info = &ad7991_info,
		पूर्ण,
	पूर्ण,
	[ad7992] = अणु
		.num_channels = 3,
		.noirq_config = अणु
			.channel = अणु
				AD799X_CHANNEL(0, 12),
				AD799X_CHANNEL(1, 12),
				IIO_CHAN_SOFT_TIMESTAMP(3),
			पूर्ण,
			.info = &ad7993_4_7_8_noirq_info,
		पूर्ण,
		.irq_config = अणु
			.channel = अणु
				AD799X_CHANNEL_WITH_EVENTS(0, 12),
				AD799X_CHANNEL_WITH_EVENTS(1, 12),
				IIO_CHAN_SOFT_TIMESTAMP(3),
			पूर्ण,
			.शेष_config = AD7998_ALERT_EN | AD7998_BUSY_ALERT,
			.info = &ad7993_4_7_8_irq_info,
		पूर्ण,
	पूर्ण,
	[ad7993] = अणु
		.num_channels = 5,
		.noirq_config = अणु
			.channel = अणु
				AD799X_CHANNEL(0, 10),
				AD799X_CHANNEL(1, 10),
				AD799X_CHANNEL(2, 10),
				AD799X_CHANNEL(3, 10),
				IIO_CHAN_SOFT_TIMESTAMP(4),
			पूर्ण,
			.info = &ad7993_4_7_8_noirq_info,
		पूर्ण,
		.irq_config = अणु
			.channel = अणु
				AD799X_CHANNEL_WITH_EVENTS(0, 10),
				AD799X_CHANNEL_WITH_EVENTS(1, 10),
				AD799X_CHANNEL_WITH_EVENTS(2, 10),
				AD799X_CHANNEL_WITH_EVENTS(3, 10),
				IIO_CHAN_SOFT_TIMESTAMP(4),
			पूर्ण,
			.शेष_config = AD7998_ALERT_EN | AD7998_BUSY_ALERT,
			.info = &ad7993_4_7_8_irq_info,
		पूर्ण,
	पूर्ण,
	[ad7994] = अणु
		.num_channels = 5,
		.noirq_config = अणु
			.channel = अणु
				AD799X_CHANNEL(0, 12),
				AD799X_CHANNEL(1, 12),
				AD799X_CHANNEL(2, 12),
				AD799X_CHANNEL(3, 12),
				IIO_CHAN_SOFT_TIMESTAMP(4),
			पूर्ण,
			.info = &ad7993_4_7_8_noirq_info,
		पूर्ण,
		.irq_config = अणु
			.channel = अणु
				AD799X_CHANNEL_WITH_EVENTS(0, 12),
				AD799X_CHANNEL_WITH_EVENTS(1, 12),
				AD799X_CHANNEL_WITH_EVENTS(2, 12),
				AD799X_CHANNEL_WITH_EVENTS(3, 12),
				IIO_CHAN_SOFT_TIMESTAMP(4),
			पूर्ण,
			.शेष_config = AD7998_ALERT_EN | AD7998_BUSY_ALERT,
			.info = &ad7993_4_7_8_irq_info,
		पूर्ण,
	पूर्ण,
	[ad7997] = अणु
		.num_channels = 9,
		.noirq_config = अणु
			.channel = अणु
				AD799X_CHANNEL(0, 10),
				AD799X_CHANNEL(1, 10),
				AD799X_CHANNEL(2, 10),
				AD799X_CHANNEL(3, 10),
				AD799X_CHANNEL(4, 10),
				AD799X_CHANNEL(5, 10),
				AD799X_CHANNEL(6, 10),
				AD799X_CHANNEL(7, 10),
				IIO_CHAN_SOFT_TIMESTAMP(8),
			पूर्ण,
			.info = &ad7993_4_7_8_noirq_info,
		पूर्ण,
		.irq_config = अणु
			.channel = अणु
				AD799X_CHANNEL_WITH_EVENTS(0, 10),
				AD799X_CHANNEL_WITH_EVENTS(1, 10),
				AD799X_CHANNEL_WITH_EVENTS(2, 10),
				AD799X_CHANNEL_WITH_EVENTS(3, 10),
				AD799X_CHANNEL(4, 10),
				AD799X_CHANNEL(5, 10),
				AD799X_CHANNEL(6, 10),
				AD799X_CHANNEL(7, 10),
				IIO_CHAN_SOFT_TIMESTAMP(8),
			पूर्ण,
			.शेष_config = AD7998_ALERT_EN | AD7998_BUSY_ALERT,
			.info = &ad7993_4_7_8_irq_info,
		पूर्ण,
	पूर्ण,
	[ad7998] = अणु
		.num_channels = 9,
		.noirq_config = अणु
			.channel = अणु
				AD799X_CHANNEL(0, 12),
				AD799X_CHANNEL(1, 12),
				AD799X_CHANNEL(2, 12),
				AD799X_CHANNEL(3, 12),
				AD799X_CHANNEL(4, 12),
				AD799X_CHANNEL(5, 12),
				AD799X_CHANNEL(6, 12),
				AD799X_CHANNEL(7, 12),
				IIO_CHAN_SOFT_TIMESTAMP(8),
			पूर्ण,
			.info = &ad7993_4_7_8_noirq_info,
		पूर्ण,
		.irq_config = अणु
			.channel = अणु
				AD799X_CHANNEL_WITH_EVENTS(0, 12),
				AD799X_CHANNEL_WITH_EVENTS(1, 12),
				AD799X_CHANNEL_WITH_EVENTS(2, 12),
				AD799X_CHANNEL_WITH_EVENTS(3, 12),
				AD799X_CHANNEL(4, 12),
				AD799X_CHANNEL(5, 12),
				AD799X_CHANNEL(6, 12),
				AD799X_CHANNEL(7, 12),
				IIO_CHAN_SOFT_TIMESTAMP(8),
			पूर्ण,
			.शेष_config = AD7998_ALERT_EN | AD7998_BUSY_ALERT,
			.info = &ad7993_4_7_8_irq_info,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ad799x_probe(काष्ठा i2c_client *client,
				   स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा ad799x_state *st;
	काष्ठा iio_dev *indio_dev;
	स्थिर काष्ठा ad799x_chip_info *chip_info =
		&ad799x_chip_info_tbl[id->driver_data];

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*st));
	अगर (indio_dev == शून्य)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);
	/* this is only used क्रम device removal purposes */
	i2c_set_clientdata(client, indio_dev);

	st->id = id->driver_data;
	अगर (client->irq > 0 && chip_info->irq_config.info)
		st->chip_config = &chip_info->irq_config;
	अन्यथा
		st->chip_config = &chip_info->noirq_config;

	/* TODO: Add pdata options क्रम filtering and bit delay */

	st->reg = devm_regulator_get(&client->dev, "vcc");
	अगर (IS_ERR(st->reg))
		वापस PTR_ERR(st->reg);
	ret = regulator_enable(st->reg);
	अगर (ret)
		वापस ret;
	st->vref = devm_regulator_get(&client->dev, "vref");
	अगर (IS_ERR(st->vref)) अणु
		ret = PTR_ERR(st->vref);
		जाओ error_disable_reg;
	पूर्ण
	ret = regulator_enable(st->vref);
	अगर (ret)
		जाओ error_disable_reg;

	st->client = client;

	indio_dev->name = id->name;
	indio_dev->info = st->chip_config->info;

	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = st->chip_config->channel;
	indio_dev->num_channels = chip_info->num_channels;

	ret = ad799x_update_config(st, st->chip_config->शेष_config);
	अगर (ret)
		जाओ error_disable_vref;

	ret = iio_triggered_buffer_setup(indio_dev, शून्य,
		&ad799x_trigger_handler, शून्य);
	अगर (ret)
		जाओ error_disable_vref;

	अगर (client->irq > 0) अणु
		ret = devm_request_thपढ़ोed_irq(&client->dev,
						client->irq,
						शून्य,
						ad799x_event_handler,
						IRQF_TRIGGER_FALLING |
						IRQF_ONESHOT,
						client->name,
						indio_dev);
		अगर (ret)
			जाओ error_cleanup_ring;
	पूर्ण
	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ error_cleanup_ring;

	वापस 0;

error_cleanup_ring:
	iio_triggered_buffer_cleanup(indio_dev);
error_disable_vref:
	regulator_disable(st->vref);
error_disable_reg:
	regulator_disable(st->reg);

	वापस ret;
पूर्ण

अटल पूर्णांक ad799x_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा ad799x_state *st = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	iio_triggered_buffer_cleanup(indio_dev);
	regulator_disable(st->vref);
	regulator_disable(st->reg);
	kमुक्त(st->rx_buf);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ad799x_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा ad799x_state *st = iio_priv(indio_dev);

	regulator_disable(st->vref);
	regulator_disable(st->reg);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ad799x_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा ad799x_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = regulator_enable(st->reg);
	अगर (ret) अणु
		dev_err(dev, "Unable to enable vcc regulator\n");
		वापस ret;
	पूर्ण
	ret = regulator_enable(st->vref);
	अगर (ret) अणु
		regulator_disable(st->reg);
		dev_err(dev, "Unable to enable vref regulator\n");
		वापस ret;
	पूर्ण

	/* resync config */
	ret = ad799x_update_config(st, st->config);
	अगर (ret) अणु
		regulator_disable(st->vref);
		regulator_disable(st->reg);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ad799x_pm_ops, ad799x_suspend, ad799x_resume);

अटल स्थिर काष्ठा i2c_device_id ad799x_id[] = अणु
	अणु "ad7991", ad7991 पूर्ण,
	अणु "ad7995", ad7995 पूर्ण,
	अणु "ad7999", ad7999 पूर्ण,
	अणु "ad7992", ad7992 पूर्ण,
	अणु "ad7993", ad7993 पूर्ण,
	अणु "ad7994", ad7994 पूर्ण,
	अणु "ad7997", ad7997 पूर्ण,
	अणु "ad7998", ad7998 पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, ad799x_id);

अटल काष्ठा i2c_driver ad799x_driver = अणु
	.driver = अणु
		.name = "ad799x",
		.pm = &ad799x_pm_ops,
	पूर्ण,
	.probe = ad799x_probe,
	.हटाओ = ad799x_हटाओ,
	.id_table = ad799x_id,
पूर्ण;
module_i2c_driver(ad799x_driver);

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("Analog Devices AD799x ADC");
MODULE_LICENSE("GPL v2");
