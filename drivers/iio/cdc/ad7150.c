<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * AD7150 capacitive sensor driver supporting AD7150/1/6
 *
 * Copyright 2010-2011 Analog Devices Inc.
 * Copyright 2021 Jonathan Cameron <Jonathan.Cameron@huawei.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/events.h>

#घोषणा AD7150_STATUS_REG		0
#घोषणा   AD7150_STATUS_OUT1		BIT(3)
#घोषणा   AD7150_STATUS_OUT2		BIT(5)
#घोषणा AD7150_CH1_DATA_HIGH_REG	1
#घोषणा AD7150_CH2_DATA_HIGH_REG	3
#घोषणा AD7150_CH1_AVG_HIGH_REG		5
#घोषणा AD7150_CH2_AVG_HIGH_REG		7
#घोषणा AD7150_CH1_SENSITIVITY_REG	9
#घोषणा AD7150_CH1_THR_HOLD_H_REG	9
#घोषणा AD7150_CH1_TIMEOUT_REG		10
#घोषणा   AD7150_CH_TIMEOUT_RECEDING	GENMASK(3, 0)
#घोषणा   AD7150_CH_TIMEOUT_APPROACHING	GENMASK(7, 4)
#घोषणा AD7150_CH1_SETUP_REG		11
#घोषणा AD7150_CH2_SENSITIVITY_REG	12
#घोषणा AD7150_CH2_THR_HOLD_H_REG	12
#घोषणा AD7150_CH2_TIMEOUT_REG		13
#घोषणा AD7150_CH2_SETUP_REG		14
#घोषणा AD7150_CFG_REG			15
#घोषणा   AD7150_CFG_FIX		BIT(7)
#घोषणा   AD7150_CFG_THRESHTYPE_MSK	GENMASK(6, 5)
#घोषणा   AD7150_CFG_TT_NEG		0x0
#घोषणा   AD7150_CFG_TT_POS		0x1
#घोषणा   AD7150_CFG_TT_IN_WINDOW	0x2
#घोषणा   AD7150_CFG_TT_OUT_WINDOW	0x3
#घोषणा AD7150_PD_TIMER_REG		16
#घोषणा AD7150_CH1_CAPDAC_REG		17
#घोषणा AD7150_CH2_CAPDAC_REG		18
#घोषणा AD7150_SN3_REG			19
#घोषणा AD7150_SN2_REG			20
#घोषणा AD7150_SN1_REG			21
#घोषणा AD7150_SN0_REG			22
#घोषणा AD7150_ID_REG			23

क्रमागत अणु
	AD7150,
	AD7151,
पूर्ण;

/**
 * काष्ठा ad7150_chip_info - instance specअगरic chip data
 * @client: i2c client क्रम this device
 * @threshold: thresholds क्रम simple capacitance value events
 * @thresh_sensitivity: threshold क्रम simple capacitance offset
 *	from 'average' value.
 * @thresh_समयout: a समयout, in samples from the moment an
 *	adaptive threshold event occurs to when the average
 *	value jumps to current value.  Note made up of two fields,
 *      3:0 are क्रम समयout receding - applies अगर below lower threshold
 *      7:4 are क्रम समयout approaching - applies अगर above upper threshold
 * @state_lock: ensure consistent state of this काष्ठाure wrt the
 *	hardware.
 * @पूर्णांकerrupts: one or two पूर्णांकerrupt numbers depending on device type.
 * @पूर्णांक_enabled: is a given पूर्णांकerrupt currently enabled.
 * @type: threshold type
 * @dir: threshold direction
 */
काष्ठा ad7150_chip_info अणु
	काष्ठा i2c_client *client;
	u16 threshold[2][2];
	u8 thresh_sensitivity[2][2];
	u8 thresh_समयout[2][2];
	काष्ठा mutex state_lock;
	पूर्णांक पूर्णांकerrupts[2];
	bool पूर्णांक_enabled[2];
	क्रमागत iio_event_type type;
	क्रमागत iio_event_direction dir;
पूर्ण;

अटल स्थिर u8 ad7150_addresses[][6] = अणु
	अणु AD7150_CH1_DATA_HIGH_REG, AD7150_CH1_AVG_HIGH_REG,
	  AD7150_CH1_SETUP_REG, AD7150_CH1_THR_HOLD_H_REG,
	  AD7150_CH1_SENSITIVITY_REG, AD7150_CH1_TIMEOUT_REG पूर्ण,
	अणु AD7150_CH2_DATA_HIGH_REG, AD7150_CH2_AVG_HIGH_REG,
	  AD7150_CH2_SETUP_REG, AD7150_CH2_THR_HOLD_H_REG,
	  AD7150_CH2_SENSITIVITY_REG, AD7150_CH2_TIMEOUT_REG पूर्ण,
पूर्ण;

अटल पूर्णांक ad7150_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val,
			   पूर्णांक *val2,
			   दीर्घ mask)
अणु
	काष्ठा ad7150_chip_info *chip = iio_priv(indio_dev);
	पूर्णांक channel = chan->channel;
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = i2c_smbus_पढ़ो_word_swapped(chip->client,
						  ad7150_addresses[channel][0]);
		अगर (ret < 0)
			वापस ret;
		*val = ret >> 4;

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_AVERAGE_RAW:
		ret = i2c_smbus_पढ़ो_word_swapped(chip->client,
						  ad7150_addresses[channel][1]);
		अगर (ret < 0)
			वापस ret;
		*val = ret;

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		/*
		 * Base units क्रम capacitance are nano farads and the value
		 * calculated from the datasheet क्रमmula is in picofarad
		 * so multiply by 1000
		 */
		*val = 1000;
		*val2 = 40944 >> 4; /* To match shअगरt in _RAW */
		वापस IIO_VAL_FRACTIONAL;
	हाल IIO_CHAN_INFO_OFFSET:
		*val = -(12288 >> 4); /* To match shअगरt in _RAW */
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		/* Strangely same क्रम both 1 and 2 chan parts */
		*val = 100;
		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ad7150_पढ़ो_event_config(काष्ठा iio_dev *indio_dev,
				    स्थिर काष्ठा iio_chan_spec *chan,
				    क्रमागत iio_event_type type,
				    क्रमागत iio_event_direction dir)
अणु
	काष्ठा ad7150_chip_info *chip = iio_priv(indio_dev);
	u8 threshtype;
	bool thrfixed;
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(chip->client, AD7150_CFG_REG);
	अगर (ret < 0)
		वापस ret;

	threshtype = FIELD_GET(AD7150_CFG_THRESHTYPE_MSK, ret);

	/*check अगर threshold mode is fixed or adaptive*/
	thrfixed = FIELD_GET(AD7150_CFG_FIX, ret);

	चयन (type) अणु
	हाल IIO_EV_TYPE_THRESH_ADAPTIVE:
		अगर (dir == IIO_EV_सूची_RISING)
			वापस !thrfixed && (threshtype == AD7150_CFG_TT_POS);
		वापस !thrfixed && (threshtype == AD7150_CFG_TT_NEG);
	हाल IIO_EV_TYPE_THRESH:
		अगर (dir == IIO_EV_सूची_RISING)
			वापस thrfixed && (threshtype == AD7150_CFG_TT_POS);
		वापस thrfixed && (threshtype == AD7150_CFG_TT_NEG);
	शेष:
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

/* state_lock should be held to ensure consistent state */
अटल पूर्णांक ad7150_ग_लिखो_event_params(काष्ठा iio_dev *indio_dev,
				     अचिन्हित पूर्णांक chan,
				     क्रमागत iio_event_type type,
				     क्रमागत iio_event_direction dir)
अणु
	काष्ठा ad7150_chip_info *chip = iio_priv(indio_dev);
	पूर्णांक rising = (dir == IIO_EV_सूची_RISING);

	/* Only update value live, अगर parameter is in use */
	अगर ((type != chip->type) || (dir != chip->dir))
		वापस 0;

	चयन (type) अणु
		/* Note completely dअगरferent from the adaptive versions */
	हाल IIO_EV_TYPE_THRESH: अणु
		u16 value = chip->threshold[rising][chan];
		वापस i2c_smbus_ग_लिखो_word_swapped(chip->client,
						    ad7150_addresses[chan][3],
						    value);
	पूर्ण
	हाल IIO_EV_TYPE_THRESH_ADAPTIVE: अणु
		पूर्णांक ret;
		u8 sens, समयout;

		sens = chip->thresh_sensitivity[rising][chan];
		ret = i2c_smbus_ग_लिखो_byte_data(chip->client,
						ad7150_addresses[chan][4],
						sens);
		अगर (ret)
			वापस ret;

		/*
		 * Single समयout रेजिस्टर contains समयouts क्रम both
		 * directions.
		 */
		समयout = FIELD_PREP(AD7150_CH_TIMEOUT_APPROACHING,
				     chip->thresh_समयout[1][chan]);
		समयout |= FIELD_PREP(AD7150_CH_TIMEOUT_RECEDING,
				      chip->thresh_समयout[0][chan]);
		वापस i2c_smbus_ग_लिखो_byte_data(chip->client,
						 ad7150_addresses[chan][5],
						 समयout);
	पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ad7150_ग_लिखो_event_config(काष्ठा iio_dev *indio_dev,
				     स्थिर काष्ठा iio_chan_spec *chan,
				     क्रमागत iio_event_type type,
				     क्रमागत iio_event_direction dir, पूर्णांक state)
अणु
	काष्ठा ad7150_chip_info *chip = iio_priv(indio_dev);
	पूर्णांक ret = 0;

	/*
	 * There is only a single shared control and no on chip
	 * पूर्णांकerrupt disables क्रम the two पूर्णांकerrupt lines.
	 * So, enabling will चयन the events configured to enable
	 * whatever was most recently requested and अगर necessary enable_irq()
	 * the पूर्णांकerrupt and any disable will disable_irq() क्रम that
	 * channels पूर्णांकerrupt.
	 */
	अगर (!state) अणु
		अगर ((chip->पूर्णांक_enabled[chan->channel]) &&
		    (type == chip->type) && (dir == chip->dir)) अणु
			disable_irq(chip->पूर्णांकerrupts[chan->channel]);
			chip->पूर्णांक_enabled[chan->channel] = false;
		पूर्ण
		वापस 0;
	पूर्ण

	mutex_lock(&chip->state_lock);
	अगर ((type != chip->type) || (dir != chip->dir)) अणु
		पूर्णांक rising = (dir == IIO_EV_सूची_RISING);
		u8 thresh_type, cfg, fixed;

		/*
		 * Need to temporarily disable both पूर्णांकerrupts अगर
		 * enabled - this is to aव्योम races around changing
		 * config and thresholds.
		 * Note enable/disable_irq() are reference counted so
		 * no need to check अगर alपढ़ोy enabled.
		 */
		disable_irq(chip->पूर्णांकerrupts[0]);
		disable_irq(chip->पूर्णांकerrupts[1]);

		ret = i2c_smbus_पढ़ो_byte_data(chip->client, AD7150_CFG_REG);
		अगर (ret < 0)
			जाओ error_ret;

		cfg = ret & ~(AD7150_CFG_THRESHTYPE_MSK | AD7150_CFG_FIX);

		अगर (type == IIO_EV_TYPE_THRESH_ADAPTIVE)
			fixed = 0;
		अन्यथा
			fixed = 1;

		अगर (rising)
			thresh_type = AD7150_CFG_TT_POS;
		अन्यथा
			thresh_type = AD7150_CFG_TT_NEG;

		cfg |= FIELD_PREP(AD7150_CFG_FIX, fixed) |
			FIELD_PREP(AD7150_CFG_THRESHTYPE_MSK, thresh_type);

		ret = i2c_smbus_ग_लिखो_byte_data(chip->client, AD7150_CFG_REG,
						cfg);
		अगर (ret < 0)
			जाओ error_ret;

		/*
		 * There is a potential race condition here, but not easy
		 * to बंद given we can't disable the पूर्णांकerrupt at the
		 * chip side of things. Rely on the status bit.
		 */
		chip->type = type;
		chip->dir = dir;

		/* update control attributes */
		ret = ad7150_ग_लिखो_event_params(indio_dev, chan->channel, type,
						dir);
		अगर (ret)
			जाओ error_ret;
		/* reenable any irq's we disabled whilst changing mode */
		enable_irq(chip->पूर्णांकerrupts[0]);
		enable_irq(chip->पूर्णांकerrupts[1]);
	पूर्ण
	अगर (!chip->पूर्णांक_enabled[chan->channel]) अणु
		enable_irq(chip->पूर्णांकerrupts[chan->channel]);
		chip->पूर्णांक_enabled[chan->channel] = true;
	पूर्ण

error_ret:
	mutex_unlock(&chip->state_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ad7150_पढ़ो_event_value(काष्ठा iio_dev *indio_dev,
				   स्थिर काष्ठा iio_chan_spec *chan,
				   क्रमागत iio_event_type type,
				   क्रमागत iio_event_direction dir,
				   क्रमागत iio_event_info info,
				   पूर्णांक *val, पूर्णांक *val2)
अणु
	काष्ठा ad7150_chip_info *chip = iio_priv(indio_dev);
	पूर्णांक rising = (dir == IIO_EV_सूची_RISING);

	/* Complex रेजिस्टर sharing going on here */
	चयन (info) अणु
	हाल IIO_EV_INFO_VALUE:
		चयन (type) अणु
		हाल IIO_EV_TYPE_THRESH_ADAPTIVE:
			*val = chip->thresh_sensitivity[rising][chan->channel];
			वापस IIO_VAL_INT;
		हाल IIO_EV_TYPE_THRESH:
			*val = chip->threshold[rising][chan->channel];
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_EV_INFO_TIMEOUT:
		*val = 0;
		*val2 = chip->thresh_समयout[rising][chan->channel] * 10000;
		वापस IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ad7150_ग_लिखो_event_value(काष्ठा iio_dev *indio_dev,
				    स्थिर काष्ठा iio_chan_spec *chan,
				    क्रमागत iio_event_type type,
				    क्रमागत iio_event_direction dir,
				    क्रमागत iio_event_info info,
				    पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक ret;
	काष्ठा ad7150_chip_info *chip = iio_priv(indio_dev);
	पूर्णांक rising = (dir == IIO_EV_सूची_RISING);

	mutex_lock(&chip->state_lock);
	चयन (info) अणु
	हाल IIO_EV_INFO_VALUE:
		चयन (type) अणु
		हाल IIO_EV_TYPE_THRESH_ADAPTIVE:
			chip->thresh_sensitivity[rising][chan->channel] = val;
			अवरोध;
		हाल IIO_EV_TYPE_THRESH:
			chip->threshold[rising][chan->channel] = val;
			अवरोध;
		शेष:
			ret = -EINVAL;
			जाओ error_ret;
		पूर्ण
		अवरोध;
	हाल IIO_EV_INFO_TIMEOUT: अणु
		/*
		 * Raw समयout is in cycles of 10 msecs as दीर्घ as both
		 * channels are enabled.
		 * In terms of INT_PLUS_MICRO, that is in units of 10,000
		 */
		पूर्णांक समयout = val2 / 10000;

		अगर (val != 0 || समयout < 0 || समयout > 15 || val2 % 10000) अणु
			ret = -EINVAL;
			जाओ error_ret;
		पूर्ण

		chip->thresh_समयout[rising][chan->channel] = समयout;
		अवरोध;
	पूर्ण
	शेष:
		ret = -EINVAL;
		जाओ error_ret;
	पूर्ण

	/* ग_लिखो back अगर active */
	ret = ad7150_ग_लिखो_event_params(indio_dev, chan->channel, type, dir);

error_ret:
	mutex_unlock(&chip->state_lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_event_spec ad7150_events[] = अणु
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
		.type = IIO_EV_TYPE_THRESH_ADAPTIVE,
		.dir = IIO_EV_सूची_RISING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE) |
			BIT(IIO_EV_INFO_ENABLE) |
			BIT(IIO_EV_INFO_TIMEOUT),
	पूर्ण, अणु
		.type = IIO_EV_TYPE_THRESH_ADAPTIVE,
		.dir = IIO_EV_सूची_FALLING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE) |
			BIT(IIO_EV_INFO_ENABLE) |
			BIT(IIO_EV_INFO_TIMEOUT),
	पूर्ण,
पूर्ण;

#घोषणा AD7150_CAPACITANCE_CHAN(_chan)	अणु			\
		.type = IIO_CAPACITANCE,			\
		.indexed = 1,					\
		.channel = _chan,				\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |	\
		BIT(IIO_CHAN_INFO_AVERAGE_RAW),			\
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) | \
			BIT(IIO_CHAN_INFO_OFFSET),		\
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ),\
		.event_spec = ad7150_events,			\
		.num_event_specs = ARRAY_SIZE(ad7150_events),	\
	पूर्ण

#घोषणा AD7150_CAPACITANCE_CHAN_NO_IRQ(_chan)	अणु		\
		.type = IIO_CAPACITANCE,			\
		.indexed = 1,					\
		.channel = _chan,				\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |	\
		BIT(IIO_CHAN_INFO_AVERAGE_RAW),			\
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) | \
			BIT(IIO_CHAN_INFO_OFFSET),		\
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ),\
	पूर्ण

अटल स्थिर काष्ठा iio_chan_spec ad7150_channels[] = अणु
	AD7150_CAPACITANCE_CHAN(0),
	AD7150_CAPACITANCE_CHAN(1),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec ad7150_channels_no_irq[] = अणु
	AD7150_CAPACITANCE_CHAN_NO_IRQ(0),
	AD7150_CAPACITANCE_CHAN_NO_IRQ(1),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec ad7151_channels[] = अणु
	AD7150_CAPACITANCE_CHAN(0),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec ad7151_channels_no_irq[] = अणु
	AD7150_CAPACITANCE_CHAN_NO_IRQ(0),
पूर्ण;

अटल irqवापस_t __ad7150_event_handler(व्योम *निजी, u8 status_mask,
					  पूर्णांक channel)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा ad7150_chip_info *chip = iio_priv(indio_dev);
	s64 बारtamp = iio_get_समय_ns(indio_dev);
	पूर्णांक पूर्णांक_status;

	पूर्णांक_status = i2c_smbus_पढ़ो_byte_data(chip->client, AD7150_STATUS_REG);
	अगर (पूर्णांक_status < 0)
		वापस IRQ_HANDLED;

	अगर (!(पूर्णांक_status & status_mask))
		वापस IRQ_HANDLED;

	iio_push_event(indio_dev,
		       IIO_UNMOD_EVENT_CODE(IIO_CAPACITANCE, channel,
					    chip->type, chip->dir),
		       बारtamp);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t ad7150_event_handler_ch1(पूर्णांक irq, व्योम *निजी)
अणु
	वापस __ad7150_event_handler(निजी, AD7150_STATUS_OUT1, 0);
पूर्ण

अटल irqवापस_t ad7150_event_handler_ch2(पूर्णांक irq, व्योम *निजी)
अणु
	वापस __ad7150_event_handler(निजी, AD7150_STATUS_OUT2, 1);
पूर्ण

अटल IIO_CONST_ATTR(in_capacitance_thresh_adaptive_समयout_available,
		      "[0 0.01 0.15]");

अटल काष्ठा attribute *ad7150_event_attributes[] = अणु
	&iio_स्थिर_attr_in_capacitance_thresh_adaptive_समयout_available
	.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ad7150_event_attribute_group = अणु
	.attrs = ad7150_event_attributes,
	.name = "events",
पूर्ण;

अटल स्थिर काष्ठा iio_info ad7150_info = अणु
	.event_attrs = &ad7150_event_attribute_group,
	.पढ़ो_raw = &ad7150_पढ़ो_raw,
	.पढ़ो_event_config = &ad7150_पढ़ो_event_config,
	.ग_लिखो_event_config = &ad7150_ग_लिखो_event_config,
	.पढ़ो_event_value = &ad7150_पढ़ो_event_value,
	.ग_लिखो_event_value = &ad7150_ग_लिखो_event_value,
पूर्ण;

अटल स्थिर काष्ठा iio_info ad7150_info_no_irq = अणु
	.पढ़ो_raw = &ad7150_पढ़ो_raw,
पूर्ण;

अटल व्योम ad7150_reg_disable(व्योम *data)
अणु
	काष्ठा regulator *reg = data;

	regulator_disable(reg);
पूर्ण

अटल पूर्णांक ad7150_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा ad7150_chip_info *chip;
	काष्ठा iio_dev *indio_dev;
	काष्ठा regulator *reg;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*chip));
	अगर (!indio_dev)
		वापस -ENOMEM;

	chip = iio_priv(indio_dev);
	mutex_init(&chip->state_lock);
	chip->client = client;

	indio_dev->name = id->name;

	indio_dev->modes = INDIO_सूचीECT_MODE;

	reg = devm_regulator_get(&client->dev, "vdd");
	अगर (IS_ERR(reg))
		वापस PTR_ERR(reg);

	ret = regulator_enable(reg);
	अगर (ret)
		वापस ret;

	ret = devm_add_action_or_reset(&client->dev, ad7150_reg_disable, reg);
	अगर (ret)
		वापस ret;

	chip->पूर्णांकerrupts[0] = fwnode_irq_get(dev_fwnode(&client->dev), 0);
	अगर (chip->पूर्णांकerrupts[0] < 0)
		वापस chip->पूर्णांकerrupts[0];
	अगर (id->driver_data == AD7150) अणु
		chip->पूर्णांकerrupts[1] = fwnode_irq_get(dev_fwnode(&client->dev), 1);
		अगर (chip->पूर्णांकerrupts[1] < 0)
			वापस chip->पूर्णांकerrupts[1];
	पूर्ण
	अगर (chip->पूर्णांकerrupts[0] &&
	    (id->driver_data == AD7151 || chip->पूर्णांकerrupts[1])) अणु
		irq_set_status_flags(chip->पूर्णांकerrupts[0], IRQ_NOAUTOEN);
		ret = devm_request_thपढ़ोed_irq(&client->dev,
						chip->पूर्णांकerrupts[0],
						शून्य,
						&ad7150_event_handler_ch1,
						IRQF_TRIGGER_RISING |
						IRQF_ONESHOT,
						"ad7150_irq1",
						indio_dev);
		अगर (ret)
			वापस ret;

		indio_dev->info = &ad7150_info;
		चयन (id->driver_data) अणु
		हाल AD7150:
			indio_dev->channels = ad7150_channels;
			indio_dev->num_channels = ARRAY_SIZE(ad7150_channels);
			irq_set_status_flags(chip->पूर्णांकerrupts[1], IRQ_NOAUTOEN);
			ret = devm_request_thपढ़ोed_irq(&client->dev,
							chip->पूर्णांकerrupts[1],
							शून्य,
							&ad7150_event_handler_ch2,
							IRQF_TRIGGER_RISING |
							IRQF_ONESHOT,
							"ad7150_irq2",
							indio_dev);
			अगर (ret)
				वापस ret;
			अवरोध;
		हाल AD7151:
			indio_dev->channels = ad7151_channels;
			indio_dev->num_channels = ARRAY_SIZE(ad7151_channels);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

	पूर्ण अन्यथा अणु
		indio_dev->info = &ad7150_info_no_irq;
		चयन (id->driver_data) अणु
		हाल AD7150:
			indio_dev->channels = ad7150_channels_no_irq;
			indio_dev->num_channels =
				ARRAY_SIZE(ad7150_channels_no_irq);
			अवरोध;
		हाल AD7151:
			indio_dev->channels = ad7151_channels_no_irq;
			indio_dev->num_channels =
				ARRAY_SIZE(ad7151_channels_no_irq);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(indio_dev->dev.parent, indio_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ad7150_id[] = अणु
	अणु "ad7150", AD7150 पूर्ण,
	अणु "ad7151", AD7151 पूर्ण,
	अणु "ad7156", AD7150 पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, ad7150_id);

अटल स्थिर काष्ठा of_device_id ad7150_of_match[] = अणु
	अणु "adi,ad7150" पूर्ण,
	अणु "adi,ad7151" पूर्ण,
	अणु "adi,ad7156" पूर्ण,
	अणुपूर्ण
पूर्ण;
अटल काष्ठा i2c_driver ad7150_driver = अणु
	.driver = अणु
		.name = "ad7150",
		.of_match_table = ad7150_of_match,
	पूर्ण,
	.probe = ad7150_probe,
	.id_table = ad7150_id,
पूर्ण;
module_i2c_driver(ad7150_driver);

MODULE_AUTHOR("Barry Song <21cnbao@gmail.com>");
MODULE_DESCRIPTION("Analog Devices AD7150/1/6 capacitive sensor driver");
MODULE_LICENSE("GPL v2");
