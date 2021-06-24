<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ADS1015 - Texas Instruments Analog-to-Digital Converter
 *
 * Copyright (c) 2016, Intel Corporation.
 *
 * IIO driver क्रम ADS1015 ADC 7-bit I2C slave address:
 *	* 0x48 - ADDR connected to Ground
 *	* 0x49 - ADDR connected to Vdd
 *	* 0x4A - ADDR connected to SDA
 *	* 0x4B - ADDR connected to SCL
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/i2c.h>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/mutex.h>
#समावेश <linux/delay.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/types.h>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/trigger_consumer.h>

#घोषणा ADS1015_DRV_NAME "ads1015"

#घोषणा ADS1015_CHANNELS 8

#घोषणा ADS1015_CONV_REG	0x00
#घोषणा ADS1015_CFG_REG		0x01
#घोषणा ADS1015_LO_THRESH_REG	0x02
#घोषणा ADS1015_HI_THRESH_REG	0x03

#घोषणा ADS1015_CFG_COMP_QUE_SHIFT	0
#घोषणा ADS1015_CFG_COMP_LAT_SHIFT	2
#घोषणा ADS1015_CFG_COMP_POL_SHIFT	3
#घोषणा ADS1015_CFG_COMP_MODE_SHIFT	4
#घोषणा ADS1015_CFG_DR_SHIFT	5
#घोषणा ADS1015_CFG_MOD_SHIFT	8
#घोषणा ADS1015_CFG_PGA_SHIFT	9
#घोषणा ADS1015_CFG_MUX_SHIFT	12

#घोषणा ADS1015_CFG_COMP_QUE_MASK	GENMASK(1, 0)
#घोषणा ADS1015_CFG_COMP_LAT_MASK	BIT(2)
#घोषणा ADS1015_CFG_COMP_POL_MASK	BIT(3)
#घोषणा ADS1015_CFG_COMP_MODE_MASK	BIT(4)
#घोषणा ADS1015_CFG_DR_MASK	GENMASK(7, 5)
#घोषणा ADS1015_CFG_MOD_MASK	BIT(8)
#घोषणा ADS1015_CFG_PGA_MASK	GENMASK(11, 9)
#घोषणा ADS1015_CFG_MUX_MASK	GENMASK(14, 12)

/* Comparator queue and disable field */
#घोषणा ADS1015_CFG_COMP_DISABLE	3

/* Comparator polarity field */
#घोषणा ADS1015_CFG_COMP_POL_LOW	0
#घोषणा ADS1015_CFG_COMP_POL_HIGH	1

/* Comparator mode field */
#घोषणा ADS1015_CFG_COMP_MODE_TRAD	0
#घोषणा ADS1015_CFG_COMP_MODE_WINDOW	1

/* device operating modes */
#घोषणा ADS1015_CONTINUOUS	0
#घोषणा ADS1015_SINGLESHOT	1

#घोषणा ADS1015_SLEEP_DELAY_MS		2000
#घोषणा ADS1015_DEFAULT_PGA		2
#घोषणा ADS1015_DEFAULT_DATA_RATE	4
#घोषणा ADS1015_DEFAULT_CHAN		0

क्रमागत chip_ids अणु
	ADSXXXX = 0,
	ADS1015,
	ADS1115,
पूर्ण;

क्रमागत ads1015_channels अणु
	ADS1015_AIN0_AIN1 = 0,
	ADS1015_AIN0_AIN3,
	ADS1015_AIN1_AIN3,
	ADS1015_AIN2_AIN3,
	ADS1015_AIN0,
	ADS1015_AIN1,
	ADS1015_AIN2,
	ADS1015_AIN3,
	ADS1015_TIMESTAMP,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ads1015_data_rate[] = अणु
	128, 250, 490, 920, 1600, 2400, 3300, 3300
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ads1115_data_rate[] = अणु
	8, 16, 32, 64, 128, 250, 475, 860
पूर्ण;

/*
 * Translation from PGA bits to full-scale positive and negative input voltage
 * range in mV
 */
अटल पूर्णांक ads1015_fullscale_range[] = अणु
	6144, 4096, 2048, 1024, 512, 256, 256, 256
पूर्ण;

/*
 * Translation from COMP_QUE field value to the number of successive पढ़ोings
 * exceed the threshold values beक्रमe an पूर्णांकerrupt is generated
 */
अटल स्थिर पूर्णांक ads1015_comp_queue[] = अणु 1, 2, 4 पूर्ण;

अटल स्थिर काष्ठा iio_event_spec ads1015_events[] = अणु
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_RISING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE) |
				BIT(IIO_EV_INFO_ENABLE),
	पूर्ण, अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_FALLING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE),
	पूर्ण, अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_EITHER,
		.mask_separate = BIT(IIO_EV_INFO_ENABLE) |
				BIT(IIO_EV_INFO_PERIOD),
	पूर्ण,
पूर्ण;

#घोषणा ADS1015_V_CHAN(_chan, _addr) अणु				\
	.type = IIO_VOLTAGE,					\
	.indexed = 1,						\
	.address = _addr,					\
	.channel = _chan,					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |		\
				BIT(IIO_CHAN_INFO_SCALE) |	\
				BIT(IIO_CHAN_INFO_SAMP_FREQ),	\
	.scan_index = _addr,					\
	.scan_type = अणु						\
		.sign = 's',					\
		.realbits = 12,					\
		.storagebits = 16,				\
		.shअगरt = 4,					\
		.endianness = IIO_CPU,				\
	पूर्ण,							\
	.event_spec = ads1015_events,				\
	.num_event_specs = ARRAY_SIZE(ads1015_events),		\
	.datasheet_name = "AIN"#_chan,				\
पूर्ण

#घोषणा ADS1015_V_DIFF_CHAN(_chan, _chan2, _addr) अणु		\
	.type = IIO_VOLTAGE,					\
	.dअगरferential = 1,					\
	.indexed = 1,						\
	.address = _addr,					\
	.channel = _chan,					\
	.channel2 = _chan2,					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |		\
				BIT(IIO_CHAN_INFO_SCALE) |	\
				BIT(IIO_CHAN_INFO_SAMP_FREQ),	\
	.scan_index = _addr,					\
	.scan_type = अणु						\
		.sign = 's',					\
		.realbits = 12,					\
		.storagebits = 16,				\
		.shअगरt = 4,					\
		.endianness = IIO_CPU,				\
	पूर्ण,							\
	.event_spec = ads1015_events,				\
	.num_event_specs = ARRAY_SIZE(ads1015_events),		\
	.datasheet_name = "AIN"#_chan"-AIN"#_chan2,		\
पूर्ण

#घोषणा ADS1115_V_CHAN(_chan, _addr) अणु				\
	.type = IIO_VOLTAGE,					\
	.indexed = 1,						\
	.address = _addr,					\
	.channel = _chan,					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |		\
				BIT(IIO_CHAN_INFO_SCALE) |	\
				BIT(IIO_CHAN_INFO_SAMP_FREQ),	\
	.scan_index = _addr,					\
	.scan_type = अणु						\
		.sign = 's',					\
		.realbits = 16,					\
		.storagebits = 16,				\
		.endianness = IIO_CPU,				\
	पूर्ण,							\
	.event_spec = ads1015_events,				\
	.num_event_specs = ARRAY_SIZE(ads1015_events),		\
	.datasheet_name = "AIN"#_chan,				\
पूर्ण

#घोषणा ADS1115_V_DIFF_CHAN(_chan, _chan2, _addr) अणु		\
	.type = IIO_VOLTAGE,					\
	.dअगरferential = 1,					\
	.indexed = 1,						\
	.address = _addr,					\
	.channel = _chan,					\
	.channel2 = _chan2,					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |		\
				BIT(IIO_CHAN_INFO_SCALE) |	\
				BIT(IIO_CHAN_INFO_SAMP_FREQ),	\
	.scan_index = _addr,					\
	.scan_type = अणु						\
		.sign = 's',					\
		.realbits = 16,					\
		.storagebits = 16,				\
		.endianness = IIO_CPU,				\
	पूर्ण,							\
	.event_spec = ads1015_events,				\
	.num_event_specs = ARRAY_SIZE(ads1015_events),		\
	.datasheet_name = "AIN"#_chan"-AIN"#_chan2,		\
पूर्ण

काष्ठा ads1015_channel_data अणु
	bool enabled;
	अचिन्हित पूर्णांक pga;
	अचिन्हित पूर्णांक data_rate;
पूर्ण;

काष्ठा ads1015_thresh_data अणु
	अचिन्हित पूर्णांक comp_queue;
	पूर्णांक high_thresh;
	पूर्णांक low_thresh;
पूर्ण;

काष्ठा ads1015_data अणु
	काष्ठा regmap *regmap;
	/*
	 * Protects ADC ops, e.g: concurrent sysfs/buffered
	 * data पढ़ोs, configuration updates
	 */
	काष्ठा mutex lock;
	काष्ठा ads1015_channel_data channel_data[ADS1015_CHANNELS];

	अचिन्हित पूर्णांक event_channel;
	अचिन्हित पूर्णांक comp_mode;
	काष्ठा ads1015_thresh_data thresh_data[ADS1015_CHANNELS];

	अचिन्हित पूर्णांक *data_rate;
	/*
	 * Set to true when the ADC is चयनed to the continuous-conversion
	 * mode and निकासs from a घातer-करोwn state.  This flag is used to aव्योम
	 * getting the stale result from the conversion रेजिस्टर.
	 */
	bool conv_invalid;
पूर्ण;

अटल bool ads1015_event_channel_enabled(काष्ठा ads1015_data *data)
अणु
	वापस (data->event_channel != ADS1015_CHANNELS);
पूर्ण

अटल व्योम ads1015_event_channel_enable(काष्ठा ads1015_data *data, पूर्णांक chan,
					 पूर्णांक comp_mode)
अणु
	WARN_ON(ads1015_event_channel_enabled(data));

	data->event_channel = chan;
	data->comp_mode = comp_mode;
पूर्ण

अटल व्योम ads1015_event_channel_disable(काष्ठा ads1015_data *data, पूर्णांक chan)
अणु
	data->event_channel = ADS1015_CHANNELS;
पूर्ण

अटल bool ads1015_is_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल ADS1015_CFG_REG:
	हाल ADS1015_LO_THRESH_REG:
	हाल ADS1015_HI_THRESH_REG:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config ads1015_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 16,
	.max_रेजिस्टर = ADS1015_HI_THRESH_REG,
	.ग_लिखोable_reg = ads1015_is_ग_लिखोable_reg,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec ads1015_channels[] = अणु
	ADS1015_V_DIFF_CHAN(0, 1, ADS1015_AIN0_AIN1),
	ADS1015_V_DIFF_CHAN(0, 3, ADS1015_AIN0_AIN3),
	ADS1015_V_DIFF_CHAN(1, 3, ADS1015_AIN1_AIN3),
	ADS1015_V_DIFF_CHAN(2, 3, ADS1015_AIN2_AIN3),
	ADS1015_V_CHAN(0, ADS1015_AIN0),
	ADS1015_V_CHAN(1, ADS1015_AIN1),
	ADS1015_V_CHAN(2, ADS1015_AIN2),
	ADS1015_V_CHAN(3, ADS1015_AIN3),
	IIO_CHAN_SOFT_TIMESTAMP(ADS1015_TIMESTAMP),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec ads1115_channels[] = अणु
	ADS1115_V_DIFF_CHAN(0, 1, ADS1015_AIN0_AIN1),
	ADS1115_V_DIFF_CHAN(0, 3, ADS1015_AIN0_AIN3),
	ADS1115_V_DIFF_CHAN(1, 3, ADS1015_AIN1_AIN3),
	ADS1115_V_DIFF_CHAN(2, 3, ADS1015_AIN2_AIN3),
	ADS1115_V_CHAN(0, ADS1015_AIN0),
	ADS1115_V_CHAN(1, ADS1015_AIN1),
	ADS1115_V_CHAN(2, ADS1015_AIN2),
	ADS1115_V_CHAN(3, ADS1015_AIN3),
	IIO_CHAN_SOFT_TIMESTAMP(ADS1015_TIMESTAMP),
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल पूर्णांक ads1015_set_घातer_state(काष्ठा ads1015_data *data, bool on)
अणु
	पूर्णांक ret;
	काष्ठा device *dev = regmap_get_device(data->regmap);

	अगर (on) अणु
		ret = pm_runसमय_get_sync(dev);
		अगर (ret < 0)
			pm_runसमय_put_noidle(dev);
	पूर्ण अन्यथा अणु
		pm_runसमय_mark_last_busy(dev);
		ret = pm_runसमय_put_स्वतःsuspend(dev);
	पूर्ण

	वापस ret < 0 ? ret : 0;
पूर्ण

#अन्यथा /* !CONFIG_PM */

अटल पूर्णांक ads1015_set_घातer_state(काष्ठा ads1015_data *data, bool on)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* !CONFIG_PM */

अटल
पूर्णांक ads1015_get_adc_result(काष्ठा ads1015_data *data, पूर्णांक chan, पूर्णांक *val)
अणु
	पूर्णांक ret, pga, dr, dr_old, conv_समय;
	अचिन्हित पूर्णांक old, mask, cfg;

	अगर (chan < 0 || chan >= ADS1015_CHANNELS)
		वापस -EINVAL;

	ret = regmap_पढ़ो(data->regmap, ADS1015_CFG_REG, &old);
	अगर (ret)
		वापस ret;

	pga = data->channel_data[chan].pga;
	dr = data->channel_data[chan].data_rate;
	mask = ADS1015_CFG_MUX_MASK | ADS1015_CFG_PGA_MASK |
		ADS1015_CFG_DR_MASK;
	cfg = chan << ADS1015_CFG_MUX_SHIFT | pga << ADS1015_CFG_PGA_SHIFT |
		dr << ADS1015_CFG_DR_SHIFT;

	अगर (ads1015_event_channel_enabled(data)) अणु
		mask |= ADS1015_CFG_COMP_QUE_MASK | ADS1015_CFG_COMP_MODE_MASK;
		cfg |= data->thresh_data[chan].comp_queue <<
				ADS1015_CFG_COMP_QUE_SHIFT |
			data->comp_mode <<
				ADS1015_CFG_COMP_MODE_SHIFT;
	पूर्ण

	cfg = (old & ~mask) | (cfg & mask);
	अगर (old != cfg) अणु
		ret = regmap_ग_लिखो(data->regmap, ADS1015_CFG_REG, cfg);
		अगर (ret)
			वापस ret;
		data->conv_invalid = true;
	पूर्ण
	अगर (data->conv_invalid) अणु
		dr_old = (old & ADS1015_CFG_DR_MASK) >> ADS1015_CFG_DR_SHIFT;
		conv_समय = DIV_ROUND_UP(USEC_PER_SEC, data->data_rate[dr_old]);
		conv_समय += DIV_ROUND_UP(USEC_PER_SEC, data->data_rate[dr]);
		conv_समय += conv_समय / 10; /* 10% पूर्णांकernal घड़ी inaccuracy */
		usleep_range(conv_समय, conv_समय + 1);
		data->conv_invalid = false;
	पूर्ण

	वापस regmap_पढ़ो(data->regmap, ADS1015_CONV_REG, val);
पूर्ण

अटल irqवापस_t ads1015_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा ads1015_data *data = iio_priv(indio_dev);
	s16 buf[8]; /* 1x s16 ADC val + 3x s16 padding +  4x s16 बारtamp */
	पूर्णांक chan, ret, res;

	स_रखो(buf, 0, माप(buf));

	mutex_lock(&data->lock);
	chan = find_first_bit(indio_dev->active_scan_mask,
			      indio_dev->masklength);
	ret = ads1015_get_adc_result(data, chan, &res);
	अगर (ret < 0) अणु
		mutex_unlock(&data->lock);
		जाओ err;
	पूर्ण

	buf[0] = res;
	mutex_unlock(&data->lock);

	iio_push_to_buffers_with_बारtamp(indio_dev, buf,
					   iio_get_समय_ns(indio_dev));

err:
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ads1015_set_scale(काष्ठा ads1015_data *data,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक scale, पूर्णांक uscale)
अणु
	पूर्णांक i;
	पूर्णांक fullscale = भाग_s64((scale * 1000000LL + uscale) <<
				(chan->scan_type.realbits - 1), 1000000);

	क्रम (i = 0; i < ARRAY_SIZE(ads1015_fullscale_range); i++) अणु
		अगर (ads1015_fullscale_range[i] == fullscale) अणु
			data->channel_data[chan->address].pga = i;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ads1015_set_data_rate(काष्ठा ads1015_data *data, पूर्णांक chan, पूर्णांक rate)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ads1015_data_rate); i++) अणु
		अगर (data->data_rate[i] == rate) अणु
			data->channel_data[chan].data_rate = i;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ads1015_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
			    पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक ret, idx;
	काष्ठा ads1015_data *data = iio_priv(indio_dev);

	mutex_lock(&data->lock);
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW: अणु
		पूर्णांक shअगरt = chan->scan_type.shअगरt;

		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			अवरोध;

		अगर (ads1015_event_channel_enabled(data) &&
				data->event_channel != chan->address) अणु
			ret = -EBUSY;
			जाओ release_direct;
		पूर्ण

		ret = ads1015_set_घातer_state(data, true);
		अगर (ret < 0)
			जाओ release_direct;

		ret = ads1015_get_adc_result(data, chan->address, val);
		अगर (ret < 0) अणु
			ads1015_set_घातer_state(data, false);
			जाओ release_direct;
		पूर्ण

		*val = sign_extend32(*val >> shअगरt, 15 - shअगरt);

		ret = ads1015_set_घातer_state(data, false);
		अगर (ret < 0)
			जाओ release_direct;

		ret = IIO_VAL_INT;
release_direct:
		iio_device_release_direct_mode(indio_dev);
		अवरोध;
	पूर्ण
	हाल IIO_CHAN_INFO_SCALE:
		idx = data->channel_data[chan->address].pga;
		*val = ads1015_fullscale_range[idx];
		*val2 = chan->scan_type.realbits - 1;
		ret = IIO_VAL_FRACTIONAL_LOG2;
		अवरोध;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		idx = data->channel_data[chan->address].data_rate;
		*val = data->data_rate[idx];
		ret = IIO_VAL_INT;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ads1015_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val,
			     पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा ads1015_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->lock);
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		ret = ads1015_set_scale(data, chan, val, val2);
		अवरोध;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		ret = ads1015_set_data_rate(data, chan->address, val);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ads1015_पढ़ो_event(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
	क्रमागत iio_event_direction dir, क्रमागत iio_event_info info, पूर्णांक *val,
	पूर्णांक *val2)
अणु
	काष्ठा ads1015_data *data = iio_priv(indio_dev);
	पूर्णांक ret;
	अचिन्हित पूर्णांक comp_queue;
	पूर्णांक period;
	पूर्णांक dr;

	mutex_lock(&data->lock);

	चयन (info) अणु
	हाल IIO_EV_INFO_VALUE:
		*val = (dir == IIO_EV_सूची_RISING) ?
			data->thresh_data[chan->address].high_thresh :
			data->thresh_data[chan->address].low_thresh;
		ret = IIO_VAL_INT;
		अवरोध;
	हाल IIO_EV_INFO_PERIOD:
		dr = data->channel_data[chan->address].data_rate;
		comp_queue = data->thresh_data[chan->address].comp_queue;
		period = ads1015_comp_queue[comp_queue] *
			USEC_PER_SEC / data->data_rate[dr];

		*val = period / USEC_PER_SEC;
		*val2 = period % USEC_PER_SEC;
		ret = IIO_VAL_INT_PLUS_MICRO;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ads1015_ग_लिखो_event(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
	क्रमागत iio_event_direction dir, क्रमागत iio_event_info info, पूर्णांक val,
	पूर्णांक val2)
अणु
	काष्ठा ads1015_data *data = iio_priv(indio_dev);
	पूर्णांक realbits = chan->scan_type.realbits;
	पूर्णांक ret = 0;
	दीर्घ दीर्घ period;
	पूर्णांक i;
	पूर्णांक dr;

	mutex_lock(&data->lock);

	चयन (info) अणु
	हाल IIO_EV_INFO_VALUE:
		अगर (val >= 1 << (realbits - 1) || val < -1 << (realbits - 1)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (dir == IIO_EV_सूची_RISING)
			data->thresh_data[chan->address].high_thresh = val;
		अन्यथा
			data->thresh_data[chan->address].low_thresh = val;
		अवरोध;
	हाल IIO_EV_INFO_PERIOD:
		dr = data->channel_data[chan->address].data_rate;
		period = val * USEC_PER_SEC + val2;

		क्रम (i = 0; i < ARRAY_SIZE(ads1015_comp_queue) - 1; i++) अणु
			अगर (period <= ads1015_comp_queue[i] *
					USEC_PER_SEC / data->data_rate[dr])
				अवरोध;
		पूर्ण
		data->thresh_data[chan->address].comp_queue = i;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ads1015_पढ़ो_event_config(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
	क्रमागत iio_event_direction dir)
अणु
	काष्ठा ads1015_data *data = iio_priv(indio_dev);
	पूर्णांक ret = 0;

	mutex_lock(&data->lock);
	अगर (data->event_channel == chan->address) अणु
		चयन (dir) अणु
		हाल IIO_EV_सूची_RISING:
			ret = 1;
			अवरोध;
		हाल IIO_EV_सूची_EITHER:
			ret = (data->comp_mode == ADS1015_CFG_COMP_MODE_WINDOW);
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ads1015_enable_event_config(काष्ठा ads1015_data *data,
	स्थिर काष्ठा iio_chan_spec *chan, पूर्णांक comp_mode)
अणु
	पूर्णांक low_thresh = data->thresh_data[chan->address].low_thresh;
	पूर्णांक high_thresh = data->thresh_data[chan->address].high_thresh;
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	अगर (ads1015_event_channel_enabled(data)) अणु
		अगर (data->event_channel != chan->address ||
			(data->comp_mode == ADS1015_CFG_COMP_MODE_TRAD &&
				comp_mode == ADS1015_CFG_COMP_MODE_WINDOW))
			वापस -EBUSY;

		वापस 0;
	पूर्ण

	अगर (comp_mode == ADS1015_CFG_COMP_MODE_TRAD) अणु
		low_thresh = max(-1 << (chan->scan_type.realbits - 1),
				high_thresh - 1);
	पूर्ण
	ret = regmap_ग_लिखो(data->regmap, ADS1015_LO_THRESH_REG,
			low_thresh << chan->scan_type.shअगरt);
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(data->regmap, ADS1015_HI_THRESH_REG,
			high_thresh << chan->scan_type.shअगरt);
	अगर (ret)
		वापस ret;

	ret = ads1015_set_घातer_state(data, true);
	अगर (ret < 0)
		वापस ret;

	ads1015_event_channel_enable(data, chan->address, comp_mode);

	ret = ads1015_get_adc_result(data, chan->address, &val);
	अगर (ret) अणु
		ads1015_event_channel_disable(data, chan->address);
		ads1015_set_घातer_state(data, false);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ads1015_disable_event_config(काष्ठा ads1015_data *data,
	स्थिर काष्ठा iio_chan_spec *chan, पूर्णांक comp_mode)
अणु
	पूर्णांक ret;

	अगर (!ads1015_event_channel_enabled(data))
		वापस 0;

	अगर (data->event_channel != chan->address)
		वापस 0;

	अगर (data->comp_mode == ADS1015_CFG_COMP_MODE_TRAD &&
			comp_mode == ADS1015_CFG_COMP_MODE_WINDOW)
		वापस 0;

	ret = regmap_update_bits(data->regmap, ADS1015_CFG_REG,
				ADS1015_CFG_COMP_QUE_MASK,
				ADS1015_CFG_COMP_DISABLE <<
					ADS1015_CFG_COMP_QUE_SHIFT);
	अगर (ret)
		वापस ret;

	ads1015_event_channel_disable(data, chan->address);

	वापस ads1015_set_घातer_state(data, false);
पूर्ण

अटल पूर्णांक ads1015_ग_लिखो_event_config(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
	क्रमागत iio_event_direction dir, पूर्णांक state)
अणु
	काष्ठा ads1015_data *data = iio_priv(indio_dev);
	पूर्णांक ret;
	पूर्णांक comp_mode = (dir == IIO_EV_सूची_EITHER) ?
		ADS1015_CFG_COMP_MODE_WINDOW : ADS1015_CFG_COMP_MODE_TRAD;

	mutex_lock(&data->lock);

	/* Prevent from enabling both buffer and event at a समय */
	ret = iio_device_claim_direct_mode(indio_dev);
	अगर (ret) अणु
		mutex_unlock(&data->lock);
		वापस ret;
	पूर्ण

	अगर (state)
		ret = ads1015_enable_event_config(data, chan, comp_mode);
	अन्यथा
		ret = ads1015_disable_event_config(data, chan, comp_mode);

	iio_device_release_direct_mode(indio_dev);
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल irqवापस_t ads1015_event_handler(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा iio_dev *indio_dev = priv;
	काष्ठा ads1015_data *data = iio_priv(indio_dev);
	पूर्णांक val;
	पूर्णांक ret;

	/* Clear the latched ALERT/RDY pin */
	ret = regmap_पढ़ो(data->regmap, ADS1015_CONV_REG, &val);
	अगर (ret)
		वापस IRQ_HANDLED;

	अगर (ads1015_event_channel_enabled(data)) अणु
		क्रमागत iio_event_direction dir;
		u64 code;

		dir = data->comp_mode == ADS1015_CFG_COMP_MODE_TRAD ?
					IIO_EV_सूची_RISING : IIO_EV_सूची_EITHER;
		code = IIO_UNMOD_EVENT_CODE(IIO_VOLTAGE, data->event_channel,
					IIO_EV_TYPE_THRESH, dir);
		iio_push_event(indio_dev, code, iio_get_समय_ns(indio_dev));
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ads1015_buffer_preenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ads1015_data *data = iio_priv(indio_dev);

	/* Prevent from enabling both buffer and event at a समय */
	अगर (ads1015_event_channel_enabled(data))
		वापस -EBUSY;

	वापस ads1015_set_घातer_state(iio_priv(indio_dev), true);
पूर्ण

अटल पूर्णांक ads1015_buffer_postdisable(काष्ठा iio_dev *indio_dev)
अणु
	वापस ads1015_set_घातer_state(iio_priv(indio_dev), false);
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops ads1015_buffer_setup_ops = अणु
	.preenable	= ads1015_buffer_preenable,
	.postdisable	= ads1015_buffer_postdisable,
	.validate_scan_mask = &iio_validate_scan_mask_onehot,
पूर्ण;

अटल IIO_CONST_ATTR_NAMED(ads1015_scale_available, scale_available,
	"3 2 1 0.5 0.25 0.125");
अटल IIO_CONST_ATTR_NAMED(ads1115_scale_available, scale_available,
	"0.1875 0.125 0.0625 0.03125 0.015625 0.007813");

अटल IIO_CONST_ATTR_NAMED(ads1015_sampling_frequency_available,
	sampling_frequency_available, "128 250 490 920 1600 2400 3300");
अटल IIO_CONST_ATTR_NAMED(ads1115_sampling_frequency_available,
	sampling_frequency_available, "8 16 32 64 128 250 475 860");

अटल काष्ठा attribute *ads1015_attributes[] = अणु
	&iio_स्थिर_attr_ads1015_scale_available.dev_attr.attr,
	&iio_स्थिर_attr_ads1015_sampling_frequency_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ads1015_attribute_group = अणु
	.attrs = ads1015_attributes,
पूर्ण;

अटल काष्ठा attribute *ads1115_attributes[] = अणु
	&iio_स्थिर_attr_ads1115_scale_available.dev_attr.attr,
	&iio_स्थिर_attr_ads1115_sampling_frequency_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ads1115_attribute_group = अणु
	.attrs = ads1115_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info ads1015_info = अणु
	.पढ़ो_raw	= ads1015_पढ़ो_raw,
	.ग_लिखो_raw	= ads1015_ग_लिखो_raw,
	.पढ़ो_event_value = ads1015_पढ़ो_event,
	.ग_लिखो_event_value = ads1015_ग_लिखो_event,
	.पढ़ो_event_config = ads1015_पढ़ो_event_config,
	.ग_लिखो_event_config = ads1015_ग_लिखो_event_config,
	.attrs          = &ads1015_attribute_group,
पूर्ण;

अटल स्थिर काष्ठा iio_info ads1115_info = अणु
	.पढ़ो_raw	= ads1015_पढ़ो_raw,
	.ग_लिखो_raw	= ads1015_ग_लिखो_raw,
	.पढ़ो_event_value = ads1015_पढ़ो_event,
	.ग_लिखो_event_value = ads1015_ग_लिखो_event,
	.पढ़ो_event_config = ads1015_पढ़ो_event_config,
	.ग_लिखो_event_config = ads1015_ग_लिखो_event_config,
	.attrs          = &ads1115_attribute_group,
पूर्ण;

अटल पूर्णांक ads1015_client_get_channels_config(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा ads1015_data *data = iio_priv(indio_dev);
	काष्ठा device *dev = &client->dev;
	काष्ठा fwnode_handle *node;
	पूर्णांक i = -1;

	device_क्रम_each_child_node(dev, node) अणु
		u32 pval;
		अचिन्हित पूर्णांक channel;
		अचिन्हित पूर्णांक pga = ADS1015_DEFAULT_PGA;
		अचिन्हित पूर्णांक data_rate = ADS1015_DEFAULT_DATA_RATE;

		अगर (fwnode_property_पढ़ो_u32(node, "reg", &pval)) अणु
			dev_err(dev, "invalid reg on %pfw\n", node);
			जारी;
		पूर्ण

		channel = pval;
		अगर (channel >= ADS1015_CHANNELS) अणु
			dev_err(dev, "invalid channel index %d on %pfw\n",
				channel, node);
			जारी;
		पूर्ण

		अगर (!fwnode_property_पढ़ो_u32(node, "ti,gain", &pval)) अणु
			pga = pval;
			अगर (pga > 6) अणु
				dev_err(dev, "invalid gain on %pfw\n", node);
				fwnode_handle_put(node);
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		अगर (!fwnode_property_पढ़ो_u32(node, "ti,datarate", &pval)) अणु
			data_rate = pval;
			अगर (data_rate > 7) अणु
				dev_err(dev, "invalid data_rate on %pfw\n", node);
				fwnode_handle_put(node);
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		data->channel_data[channel].pga = pga;
		data->channel_data[channel].data_rate = data_rate;

		i++;
	पूर्ण

	वापस i < 0 ? -EINVAL : 0;
पूर्ण

अटल व्योम ads1015_get_channels_config(काष्ठा i2c_client *client)
अणु
	अचिन्हित पूर्णांक k;

	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा ads1015_data *data = iio_priv(indio_dev);

	अगर (!ads1015_client_get_channels_config(client))
		वापस;

	/* fallback on शेष configuration */
	क्रम (k = 0; k < ADS1015_CHANNELS; ++k) अणु
		data->channel_data[k].pga = ADS1015_DEFAULT_PGA;
		data->channel_data[k].data_rate = ADS1015_DEFAULT_DATA_RATE;
	पूर्ण
पूर्ण

अटल पूर्णांक ads1015_set_conv_mode(काष्ठा ads1015_data *data, पूर्णांक mode)
अणु
	वापस regmap_update_bits(data->regmap, ADS1015_CFG_REG,
				  ADS1015_CFG_MOD_MASK,
				  mode << ADS1015_CFG_MOD_SHIFT);
पूर्ण

अटल पूर्णांक ads1015_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा ads1015_data *data;
	पूर्णांक ret;
	क्रमागत chip_ids chip;
	पूर्णांक i;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);

	mutex_init(&data->lock);

	indio_dev->name = ADS1015_DRV_NAME;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	chip = (क्रमागत chip_ids)device_get_match_data(&client->dev);
	अगर (chip == ADSXXXX)
		chip = id->driver_data;
	चयन (chip) अणु
	हाल ADS1015:
		indio_dev->channels = ads1015_channels;
		indio_dev->num_channels = ARRAY_SIZE(ads1015_channels);
		indio_dev->info = &ads1015_info;
		data->data_rate = (अचिन्हित पूर्णांक *) &ads1015_data_rate;
		अवरोध;
	हाल ADS1115:
		indio_dev->channels = ads1115_channels;
		indio_dev->num_channels = ARRAY_SIZE(ads1115_channels);
		indio_dev->info = &ads1115_info;
		data->data_rate = (अचिन्हित पूर्णांक *) &ads1115_data_rate;
		अवरोध;
	शेष:
		dev_err(&client->dev, "Unknown chip %d\n", chip);
		वापस -EINVAL;
	पूर्ण

	data->event_channel = ADS1015_CHANNELS;
	/*
	 * Set शेष lower and upper threshold to min and max value
	 * respectively.
	 */
	क्रम (i = 0; i < ADS1015_CHANNELS; i++) अणु
		पूर्णांक realbits = indio_dev->channels[i].scan_type.realbits;

		data->thresh_data[i].low_thresh = -1 << (realbits - 1);
		data->thresh_data[i].high_thresh = (1 << (realbits - 1)) - 1;
	पूर्ण

	/* we need to keep this ABI the same as used by hwmon ADS1015 driver */
	ads1015_get_channels_config(client);

	data->regmap = devm_regmap_init_i2c(client, &ads1015_regmap_config);
	अगर (IS_ERR(data->regmap)) अणु
		dev_err(&client->dev, "Failed to allocate register map\n");
		वापस PTR_ERR(data->regmap);
	पूर्ण

	ret = devm_iio_triggered_buffer_setup(&client->dev, indio_dev, शून्य,
					      ads1015_trigger_handler,
					      &ads1015_buffer_setup_ops);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "iio triggered buffer setup failed\n");
		वापस ret;
	पूर्ण

	अगर (client->irq) अणु
		अचिन्हित दीर्घ irq_trig =
			irqd_get_trigger_type(irq_get_irq_data(client->irq));
		अचिन्हित पूर्णांक cfg_comp_mask = ADS1015_CFG_COMP_QUE_MASK |
			ADS1015_CFG_COMP_LAT_MASK | ADS1015_CFG_COMP_POL_MASK;
		अचिन्हित पूर्णांक cfg_comp =
			ADS1015_CFG_COMP_DISABLE << ADS1015_CFG_COMP_QUE_SHIFT |
			1 << ADS1015_CFG_COMP_LAT_SHIFT;

		चयन (irq_trig) अणु
		हाल IRQF_TRIGGER_LOW:
			cfg_comp |= ADS1015_CFG_COMP_POL_LOW <<
					ADS1015_CFG_COMP_POL_SHIFT;
			अवरोध;
		हाल IRQF_TRIGGER_HIGH:
			cfg_comp |= ADS1015_CFG_COMP_POL_HIGH <<
					ADS1015_CFG_COMP_POL_SHIFT;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		ret = regmap_update_bits(data->regmap, ADS1015_CFG_REG,
					cfg_comp_mask, cfg_comp);
		अगर (ret)
			वापस ret;

		ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
						शून्य, ads1015_event_handler,
						irq_trig | IRQF_ONESHOT,
						client->name, indio_dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = ads1015_set_conv_mode(data, ADS1015_CONTINUOUS);
	अगर (ret)
		वापस ret;

	data->conv_invalid = true;

	ret = pm_runसमय_set_active(&client->dev);
	अगर (ret)
		वापस ret;
	pm_runसमय_set_स्वतःsuspend_delay(&client->dev, ADS1015_SLEEP_DELAY_MS);
	pm_runसमय_use_स्वतःsuspend(&client->dev);
	pm_runसमय_enable(&client->dev);

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Failed to register IIO device\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ads1015_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा ads1015_data *data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	pm_runसमय_disable(&client->dev);
	pm_runसमय_set_suspended(&client->dev);
	pm_runसमय_put_noidle(&client->dev);

	/* घातer करोwn single shot mode */
	वापस ads1015_set_conv_mode(data, ADS1015_SINGLESHOT);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक ads1015_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा ads1015_data *data = iio_priv(indio_dev);

	वापस ads1015_set_conv_mode(data, ADS1015_SINGLESHOT);
पूर्ण

अटल पूर्णांक ads1015_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा ads1015_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = ads1015_set_conv_mode(data, ADS1015_CONTINUOUS);
	अगर (!ret)
		data->conv_invalid = true;

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops ads1015_pm_ops = अणु
	SET_RUNTIME_PM_OPS(ads1015_runसमय_suspend,
			   ads1015_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id ads1015_id[] = अणु
	अणु"ads1015", ADS1015पूर्ण,
	अणु"ads1115", ADS1115पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ads1015_id);

अटल स्थिर काष्ठा of_device_id ads1015_of_match[] = अणु
	अणु
		.compatible = "ti,ads1015",
		.data = (व्योम *)ADS1015
	पूर्ण,
	अणु
		.compatible = "ti,ads1115",
		.data = (व्योम *)ADS1115
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ads1015_of_match);

अटल काष्ठा i2c_driver ads1015_driver = अणु
	.driver = अणु
		.name = ADS1015_DRV_NAME,
		.of_match_table = ads1015_of_match,
		.pm = &ads1015_pm_ops,
	पूर्ण,
	.probe		= ads1015_probe,
	.हटाओ		= ads1015_हटाओ,
	.id_table	= ads1015_id,
पूर्ण;

module_i2c_driver(ads1015_driver);

MODULE_AUTHOR("Daniel Baluta <daniel.baluta@intel.com>");
MODULE_DESCRIPTION("Texas Instruments ADS1015 ADC driver");
MODULE_LICENSE("GPL v2");
