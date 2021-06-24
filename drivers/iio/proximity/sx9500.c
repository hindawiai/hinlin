<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014 Intel Corporation
 *
 * Driver क्रम Semtech's SX9500 capacitive proximity/button solution.
 * Datasheet available at
 * <http://www.semtech.com/images/datasheet/sx9500.pdf>.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/irq.h>
#समावेश <linux/acpi.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/regmap.h>
#समावेश <linux/pm.h>
#समावेश <linux/delay.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/trigger_consumer.h>

#घोषणा SX9500_DRIVER_NAME		"sx9500"
#घोषणा SX9500_IRQ_NAME			"sx9500_event"

/* Register definitions. */
#घोषणा SX9500_REG_IRQ_SRC		0x00
#घोषणा SX9500_REG_STAT			0x01
#घोषणा SX9500_REG_IRQ_MSK		0x03

#घोषणा SX9500_REG_PROX_CTRL0		0x06
#घोषणा SX9500_REG_PROX_CTRL1		0x07
#घोषणा SX9500_REG_PROX_CTRL2		0x08
#घोषणा SX9500_REG_PROX_CTRL3		0x09
#घोषणा SX9500_REG_PROX_CTRL4		0x0a
#घोषणा SX9500_REG_PROX_CTRL5		0x0b
#घोषणा SX9500_REG_PROX_CTRL6		0x0c
#घोषणा SX9500_REG_PROX_CTRL7		0x0d
#घोषणा SX9500_REG_PROX_CTRL8		0x0e

#घोषणा SX9500_REG_SENSOR_SEL		0x20
#घोषणा SX9500_REG_USE_MSB		0x21
#घोषणा SX9500_REG_USE_LSB		0x22
#घोषणा SX9500_REG_AVG_MSB		0x23
#घोषणा SX9500_REG_AVG_LSB		0x24
#घोषणा SX9500_REG_DIFF_MSB		0x25
#घोषणा SX9500_REG_DIFF_LSB		0x26
#घोषणा SX9500_REG_OFFSET_MSB		0x27
#घोषणा SX9500_REG_OFFSET_LSB		0x28

#घोषणा SX9500_REG_RESET		0x7f

/* Write this to REG_RESET to करो a soft reset. */
#घोषणा SX9500_SOFT_RESET		0xde

#घोषणा SX9500_SCAN_PERIOD_MASK		GENMASK(6, 4)
#घोषणा SX9500_SCAN_PERIOD_SHIFT	4

/*
 * These serve क्रम identअगरying IRQ source in the IRQ_SRC रेजिस्टर, and
 * also क्रम masking the IRQs in the IRQ_MSK रेजिस्टर.
 */
#घोषणा SX9500_CLOSE_IRQ		BIT(6)
#घोषणा SX9500_FAR_IRQ			BIT(5)
#घोषणा SX9500_CONVDONE_IRQ		BIT(3)

#घोषणा SX9500_PROXSTAT_SHIFT		4
#घोषणा SX9500_COMPSTAT_MASK		GENMASK(3, 0)

#घोषणा SX9500_NUM_CHANNELS		4
#घोषणा SX9500_CHAN_MASK		GENMASK(SX9500_NUM_CHANNELS - 1, 0)

काष्ठा sx9500_data अणु
	काष्ठा mutex mutex;
	काष्ठा i2c_client *client;
	काष्ठा iio_trigger *trig;
	काष्ठा regmap *regmap;
	काष्ठा gpio_desc *gpiod_rst;
	/*
	 * Last पढ़ोing of the proximity status क्रम each channel.  We
	 * only send an event to user space when this changes.
	 */
	bool prox_stat[SX9500_NUM_CHANNELS];
	bool event_enabled[SX9500_NUM_CHANNELS];
	bool trigger_enabled;
	u16 *buffer;
	/* Remember enabled channels and sample rate during suspend. */
	अचिन्हित पूर्णांक suspend_ctrl0;
	काष्ठा completion completion;
	पूर्णांक data_rdy_users, बंद_far_users;
	पूर्णांक channel_users[SX9500_NUM_CHANNELS];
पूर्ण;

अटल स्थिर काष्ठा iio_event_spec sx9500_events[] = अणु
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_EITHER,
		.mask_separate = BIT(IIO_EV_INFO_ENABLE),
	पूर्ण,
पूर्ण;

#घोषणा SX9500_CHANNEL(idx)					\
	अणु							\
		.type = IIO_PROXIMITY,				\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),	\
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ), \
		.indexed = 1,					\
		.channel = idx,					\
		.event_spec = sx9500_events,			\
		.num_event_specs = ARRAY_SIZE(sx9500_events),	\
		.scan_index = idx,				\
		.scan_type = अणु					\
			.sign = 'u',				\
			.realbits = 16,				\
			.storagebits = 16,			\
			.shअगरt = 0,				\
		पूर्ण,						\
	पूर्ण

अटल स्थिर काष्ठा iio_chan_spec sx9500_channels[] = अणु
	SX9500_CHANNEL(0),
	SX9500_CHANNEL(1),
	SX9500_CHANNEL(2),
	SX9500_CHANNEL(3),
	IIO_CHAN_SOFT_TIMESTAMP(4),
पूर्ण;

अटल स्थिर काष्ठा अणु
	पूर्णांक val;
	पूर्णांक val2;
पूर्ण sx9500_samp_freq_table[] = अणु
	अणु33, 333333पूर्ण,
	अणु16, 666666पूर्ण,
	अणु11, 111111पूर्ण,
	अणु8, 333333पूर्ण,
	अणु6, 666666पूर्ण,
	अणु5, 0पूर्ण,
	अणु3, 333333पूर्ण,
	अणु2, 500000पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक sx9500_scan_period_table[] = अणु
	30, 60, 90, 120, 150, 200, 300, 400,
पूर्ण;

अटल स्थिर काष्ठा regmap_range sx9500_writable_reg_ranges[] = अणु
	regmap_reg_range(SX9500_REG_IRQ_MSK, SX9500_REG_IRQ_MSK),
	regmap_reg_range(SX9500_REG_PROX_CTRL0, SX9500_REG_PROX_CTRL8),
	regmap_reg_range(SX9500_REG_SENSOR_SEL, SX9500_REG_SENSOR_SEL),
	regmap_reg_range(SX9500_REG_OFFSET_MSB, SX9500_REG_OFFSET_LSB),
	regmap_reg_range(SX9500_REG_RESET, SX9500_REG_RESET),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table sx9500_ग_लिखोable_regs = अणु
	.yes_ranges = sx9500_writable_reg_ranges,
	.n_yes_ranges = ARRAY_SIZE(sx9500_writable_reg_ranges),
पूर्ण;

/*
 * All allocated रेजिस्टरs are पढ़ोable, so we just list unallocated
 * ones.
 */
अटल स्थिर काष्ठा regmap_range sx9500_non_पढ़ोable_reg_ranges[] = अणु
	regmap_reg_range(SX9500_REG_STAT + 1, SX9500_REG_STAT + 1),
	regmap_reg_range(SX9500_REG_IRQ_MSK + 1, SX9500_REG_PROX_CTRL0 - 1),
	regmap_reg_range(SX9500_REG_PROX_CTRL8 + 1, SX9500_REG_SENSOR_SEL - 1),
	regmap_reg_range(SX9500_REG_OFFSET_LSB + 1, SX9500_REG_RESET - 1),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table sx9500_पढ़ोable_regs = अणु
	.no_ranges = sx9500_non_पढ़ोable_reg_ranges,
	.n_no_ranges = ARRAY_SIZE(sx9500_non_पढ़ोable_reg_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range sx9500_अस्थिर_reg_ranges[] = अणु
	regmap_reg_range(SX9500_REG_IRQ_SRC, SX9500_REG_STAT),
	regmap_reg_range(SX9500_REG_USE_MSB, SX9500_REG_OFFSET_LSB),
	regmap_reg_range(SX9500_REG_RESET, SX9500_REG_RESET),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table sx9500_अस्थिर_regs = अणु
	.yes_ranges = sx9500_अस्थिर_reg_ranges,
	.n_yes_ranges = ARRAY_SIZE(sx9500_अस्थिर_reg_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config sx9500_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = SX9500_REG_RESET,
	.cache_type = REGCACHE_RBTREE,

	.wr_table = &sx9500_ग_लिखोable_regs,
	.rd_table = &sx9500_पढ़ोable_regs,
	.अस्थिर_table = &sx9500_अस्थिर_regs,
पूर्ण;

अटल पूर्णांक sx9500_inc_users(काष्ठा sx9500_data *data, पूर्णांक *counter,
			    अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक biपंचांगask)
अणु
	(*counter)++;
	अगर (*counter != 1)
		/* Bit is alपढ़ोy active, nothing to करो. */
		वापस 0;

	वापस regmap_update_bits(data->regmap, reg, biपंचांगask, biपंचांगask);
पूर्ण

अटल पूर्णांक sx9500_dec_users(काष्ठा sx9500_data *data, पूर्णांक *counter,
			    अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक biपंचांगask)
अणु
	(*counter)--;
	अगर (*counter != 0)
		/* There are more users, करो not deactivate. */
		वापस 0;

	वापस regmap_update_bits(data->regmap, reg, biपंचांगask, 0);
पूर्ण

अटल पूर्णांक sx9500_inc_chan_users(काष्ठा sx9500_data *data, पूर्णांक chan)
अणु
	वापस sx9500_inc_users(data, &data->channel_users[chan],
				SX9500_REG_PROX_CTRL0, BIT(chan));
पूर्ण

अटल पूर्णांक sx9500_dec_chan_users(काष्ठा sx9500_data *data, पूर्णांक chan)
अणु
	वापस sx9500_dec_users(data, &data->channel_users[chan],
				SX9500_REG_PROX_CTRL0, BIT(chan));
पूर्ण

अटल पूर्णांक sx9500_inc_data_rdy_users(काष्ठा sx9500_data *data)
अणु
	वापस sx9500_inc_users(data, &data->data_rdy_users,
				SX9500_REG_IRQ_MSK, SX9500_CONVDONE_IRQ);
पूर्ण

अटल पूर्णांक sx9500_dec_data_rdy_users(काष्ठा sx9500_data *data)
अणु
	वापस sx9500_dec_users(data, &data->data_rdy_users,
				SX9500_REG_IRQ_MSK, SX9500_CONVDONE_IRQ);
पूर्ण

अटल पूर्णांक sx9500_inc_बंद_far_users(काष्ठा sx9500_data *data)
अणु
	वापस sx9500_inc_users(data, &data->बंद_far_users,
				SX9500_REG_IRQ_MSK,
				SX9500_CLOSE_IRQ | SX9500_FAR_IRQ);
पूर्ण

अटल पूर्णांक sx9500_dec_बंद_far_users(काष्ठा sx9500_data *data)
अणु
	वापस sx9500_dec_users(data, &data->बंद_far_users,
				SX9500_REG_IRQ_MSK,
				SX9500_CLOSE_IRQ | SX9500_FAR_IRQ);
पूर्ण

अटल पूर्णांक sx9500_पढ़ो_prox_data(काष्ठा sx9500_data *data,
				 स्थिर काष्ठा iio_chan_spec *chan,
				 पूर्णांक *val)
अणु
	पूर्णांक ret;
	__be16 regval;

	ret = regmap_ग_लिखो(data->regmap, SX9500_REG_SENSOR_SEL, chan->channel);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_bulk_पढ़ो(data->regmap, SX9500_REG_USE_MSB, &regval, 2);
	अगर (ret < 0)
		वापस ret;

	*val = be16_to_cpu(regval);

	वापस IIO_VAL_INT;
पूर्ण

/*
 * If we have no पूर्णांकerrupt support, we have to रुको क्रम a scan period
 * after enabling a channel to get a result.
 */
अटल पूर्णांक sx9500_रुको_क्रम_sample(काष्ठा sx9500_data *data)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	ret = regmap_पढ़ो(data->regmap, SX9500_REG_PROX_CTRL0, &val);
	अगर (ret < 0)
		वापस ret;

	val = (val & SX9500_SCAN_PERIOD_MASK) >> SX9500_SCAN_PERIOD_SHIFT;

	msleep(sx9500_scan_period_table[val]);

	वापस 0;
पूर्ण

अटल पूर्णांक sx9500_पढ़ो_proximity(काष्ठा sx9500_data *data,
				 स्थिर काष्ठा iio_chan_spec *chan,
				 पूर्णांक *val)
अणु
	पूर्णांक ret;

	mutex_lock(&data->mutex);

	ret = sx9500_inc_chan_users(data, chan->channel);
	अगर (ret < 0)
		जाओ out;

	ret = sx9500_inc_data_rdy_users(data);
	अगर (ret < 0)
		जाओ out_dec_chan;

	mutex_unlock(&data->mutex);

	अगर (data->client->irq > 0)
		ret = रुको_क्रम_completion_पूर्णांकerruptible(&data->completion);
	अन्यथा
		ret = sx9500_रुको_क्रम_sample(data);

	mutex_lock(&data->mutex);

	अगर (ret < 0)
		जाओ out_dec_data_rdy;

	ret = sx9500_पढ़ो_prox_data(data, chan, val);
	अगर (ret < 0)
		जाओ out_dec_data_rdy;

	ret = sx9500_dec_data_rdy_users(data);
	अगर (ret < 0)
		जाओ out_dec_chan;

	ret = sx9500_dec_chan_users(data, chan->channel);
	अगर (ret < 0)
		जाओ out;

	ret = IIO_VAL_INT;

	जाओ out;

out_dec_data_rdy:
	sx9500_dec_data_rdy_users(data);
out_dec_chan:
	sx9500_dec_chan_users(data, chan->channel);
out:
	mutex_unlock(&data->mutex);
	reinit_completion(&data->completion);

	वापस ret;
पूर्ण

अटल पूर्णांक sx9500_पढ़ो_samp_freq(काष्ठा sx9500_data *data,
				 पूर्णांक *val, पूर्णांक *val2)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक regval;

	mutex_lock(&data->mutex);
	ret = regmap_पढ़ो(data->regmap, SX9500_REG_PROX_CTRL0, &regval);
	mutex_unlock(&data->mutex);

	अगर (ret < 0)
		वापस ret;

	regval = (regval & SX9500_SCAN_PERIOD_MASK) >> SX9500_SCAN_PERIOD_SHIFT;
	*val = sx9500_samp_freq_table[regval].val;
	*val2 = sx9500_samp_freq_table[regval].val2;

	वापस IIO_VAL_INT_PLUS_MICRO;
पूर्ण

अटल पूर्णांक sx9500_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   स्थिर काष्ठा iio_chan_spec *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा sx9500_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (chan->type) अणु
	हाल IIO_PROXIMITY:
		चयन (mask) अणु
		हाल IIO_CHAN_INFO_RAW:
			ret = iio_device_claim_direct_mode(indio_dev);
			अगर (ret)
				वापस ret;
			ret = sx9500_पढ़ो_proximity(data, chan, val);
			iio_device_release_direct_mode(indio_dev);
			वापस ret;
		हाल IIO_CHAN_INFO_SAMP_FREQ:
			वापस sx9500_पढ़ो_samp_freq(data, val, val2);
		शेष:
			वापस -EINVAL;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक sx9500_set_samp_freq(काष्ठा sx9500_data *data,
				पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < ARRAY_SIZE(sx9500_samp_freq_table); i++)
		अगर (val == sx9500_samp_freq_table[i].val &&
		    val2 == sx9500_samp_freq_table[i].val2)
			अवरोध;

	अगर (i == ARRAY_SIZE(sx9500_samp_freq_table))
		वापस -EINVAL;

	mutex_lock(&data->mutex);

	ret = regmap_update_bits(data->regmap, SX9500_REG_PROX_CTRL0,
				 SX9500_SCAN_PERIOD_MASK,
				 i << SX9500_SCAN_PERIOD_SHIFT);

	mutex_unlock(&data->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक sx9500_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			    स्थिर काष्ठा iio_chan_spec *chan,
			    पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा sx9500_data *data = iio_priv(indio_dev);

	चयन (chan->type) अणु
	हाल IIO_PROXIMITY:
		चयन (mask) अणु
		हाल IIO_CHAN_INFO_SAMP_FREQ:
			वापस sx9500_set_samp_freq(data, val, val2);
		शेष:
			वापस -EINVAL;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल irqवापस_t sx9500_irq_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा sx9500_data *data = iio_priv(indio_dev);

	अगर (data->trigger_enabled)
		iio_trigger_poll(data->trig);

	/*
	 * Even अगर no event is enabled, we need to wake the thपढ़ो to
	 * clear the पूर्णांकerrupt state by पढ़ोing SX9500_REG_IRQ_SRC.  It
	 * is not possible to करो that here because regmap_पढ़ो takes a
	 * mutex.
	 */
	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल व्योम sx9500_push_events(काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val, chan;
	काष्ठा sx9500_data *data = iio_priv(indio_dev);

	ret = regmap_पढ़ो(data->regmap, SX9500_REG_STAT, &val);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "i2c transfer error in irq\n");
		वापस;
	पूर्ण

	val >>= SX9500_PROXSTAT_SHIFT;
	क्रम (chan = 0; chan < SX9500_NUM_CHANNELS; chan++) अणु
		पूर्णांक dir;
		u64 ev;
		bool new_prox = val & BIT(chan);

		अगर (!data->event_enabled[chan])
			जारी;
		अगर (new_prox == data->prox_stat[chan])
			/* No change on this channel. */
			जारी;

		dir = new_prox ? IIO_EV_सूची_FALLING : IIO_EV_सूची_RISING;
		ev = IIO_UNMOD_EVENT_CODE(IIO_PROXIMITY, chan,
					  IIO_EV_TYPE_THRESH, dir);
		iio_push_event(indio_dev, ev, iio_get_समय_ns(indio_dev));
		data->prox_stat[chan] = new_prox;
	पूर्ण
पूर्ण

अटल irqवापस_t sx9500_irq_thपढ़ो_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा sx9500_data *data = iio_priv(indio_dev);
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	mutex_lock(&data->mutex);

	ret = regmap_पढ़ो(data->regmap, SX9500_REG_IRQ_SRC, &val);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "i2c transfer error in irq\n");
		जाओ out;
	पूर्ण

	अगर (val & (SX9500_CLOSE_IRQ | SX9500_FAR_IRQ))
		sx9500_push_events(indio_dev);

	अगर (val & SX9500_CONVDONE_IRQ)
		complete(&data->completion);

out:
	mutex_unlock(&data->mutex);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sx9500_पढ़ो_event_config(काष्ठा iio_dev *indio_dev,
				    स्थिर काष्ठा iio_chan_spec *chan,
				    क्रमागत iio_event_type type,
				    क्रमागत iio_event_direction dir)
अणु
	काष्ठा sx9500_data *data = iio_priv(indio_dev);

	अगर (chan->type != IIO_PROXIMITY || type != IIO_EV_TYPE_THRESH ||
	    dir != IIO_EV_सूची_EITHER)
		वापस -EINVAL;

	वापस data->event_enabled[chan->channel];
पूर्ण

अटल पूर्णांक sx9500_ग_लिखो_event_config(काष्ठा iio_dev *indio_dev,
				     स्थिर काष्ठा iio_chan_spec *chan,
				     क्रमागत iio_event_type type,
				     क्रमागत iio_event_direction dir,
				     पूर्णांक state)
अणु
	काष्ठा sx9500_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	अगर (chan->type != IIO_PROXIMITY || type != IIO_EV_TYPE_THRESH ||
	    dir != IIO_EV_सूची_EITHER)
		वापस -EINVAL;

	mutex_lock(&data->mutex);

	अगर (state == 1) अणु
		ret = sx9500_inc_chan_users(data, chan->channel);
		अगर (ret < 0)
			जाओ out_unlock;
		ret = sx9500_inc_बंद_far_users(data);
		अगर (ret < 0)
			जाओ out_unकरो_chan;
	पूर्ण अन्यथा अणु
		ret = sx9500_dec_chan_users(data, chan->channel);
		अगर (ret < 0)
			जाओ out_unlock;
		ret = sx9500_dec_बंद_far_users(data);
		अगर (ret < 0)
			जाओ out_unकरो_chan;
	पूर्ण

	data->event_enabled[chan->channel] = state;
	जाओ out_unlock;

out_unकरो_chan:
	अगर (state == 1)
		sx9500_dec_chan_users(data, chan->channel);
	अन्यथा
		sx9500_inc_chan_users(data, chan->channel);
out_unlock:
	mutex_unlock(&data->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक sx9500_update_scan_mode(काष्ठा iio_dev *indio_dev,
				   स्थिर अचिन्हित दीर्घ *scan_mask)
अणु
	काष्ठा sx9500_data *data = iio_priv(indio_dev);

	mutex_lock(&data->mutex);
	kमुक्त(data->buffer);
	data->buffer = kzalloc(indio_dev->scan_bytes, GFP_KERNEL);
	mutex_unlock(&data->mutex);

	अगर (data->buffer == शून्य)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल IIO_CONST_ATTR_SAMP_FREQ_AVAIL(
	"2.500000 3.333333 5 6.666666 8.333333 11.111111 16.666666 33.333333");

अटल काष्ठा attribute *sx9500_attributes[] = अणु
	&iio_स्थिर_attr_sampling_frequency_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group sx9500_attribute_group = अणु
	.attrs = sx9500_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info sx9500_info = अणु
	.attrs = &sx9500_attribute_group,
	.पढ़ो_raw = &sx9500_पढ़ो_raw,
	.ग_लिखो_raw = &sx9500_ग_लिखो_raw,
	.पढ़ो_event_config = &sx9500_पढ़ो_event_config,
	.ग_लिखो_event_config = &sx9500_ग_लिखो_event_config,
	.update_scan_mode = &sx9500_update_scan_mode,
पूर्ण;

अटल पूर्णांक sx9500_set_trigger_state(काष्ठा iio_trigger *trig,
				    bool state)
अणु
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	काष्ठा sx9500_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->mutex);

	अगर (state)
		ret = sx9500_inc_data_rdy_users(data);
	अन्यथा
		ret = sx9500_dec_data_rdy_users(data);
	अगर (ret < 0)
		जाओ out;

	data->trigger_enabled = state;

out:
	mutex_unlock(&data->mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops sx9500_trigger_ops = अणु
	.set_trigger_state = sx9500_set_trigger_state,
पूर्ण;

अटल irqवापस_t sx9500_trigger_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_poll_func *pf = निजी;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा sx9500_data *data = iio_priv(indio_dev);
	पूर्णांक val, bit, ret, i = 0;

	mutex_lock(&data->mutex);

	क्रम_each_set_bit(bit, indio_dev->active_scan_mask,
			 indio_dev->masklength) अणु
		ret = sx9500_पढ़ो_prox_data(data, &indio_dev->channels[bit],
					    &val);
		अगर (ret < 0)
			जाओ out;

		data->buffer[i++] = val;
	पूर्ण

	iio_push_to_buffers_with_बारtamp(indio_dev, data->buffer,
					   iio_get_समय_ns(indio_dev));

out:
	mutex_unlock(&data->mutex);

	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sx9500_buffer_postenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा sx9500_data *data = iio_priv(indio_dev);
	पूर्णांक ret = 0, i;

	mutex_lock(&data->mutex);

	क्रम (i = 0; i < SX9500_NUM_CHANNELS; i++)
		अगर (test_bit(i, indio_dev->active_scan_mask)) अणु
			ret = sx9500_inc_chan_users(data, i);
			अगर (ret)
				अवरोध;
		पूर्ण

	अगर (ret)
		क्रम (i = i - 1; i >= 0; i--)
			अगर (test_bit(i, indio_dev->active_scan_mask))
				sx9500_dec_chan_users(data, i);

	mutex_unlock(&data->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक sx9500_buffer_predisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा sx9500_data *data = iio_priv(indio_dev);
	पूर्णांक ret = 0, i;

	mutex_lock(&data->mutex);

	क्रम (i = 0; i < SX9500_NUM_CHANNELS; i++)
		अगर (test_bit(i, indio_dev->active_scan_mask)) अणु
			ret = sx9500_dec_chan_users(data, i);
			अगर (ret)
				अवरोध;
		पूर्ण

	अगर (ret)
		क्रम (i = i - 1; i >= 0; i--)
			अगर (test_bit(i, indio_dev->active_scan_mask))
				sx9500_inc_chan_users(data, i);

	mutex_unlock(&data->mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops sx9500_buffer_setup_ops = अणु
	.postenable = sx9500_buffer_postenable,
	.predisable = sx9500_buffer_predisable,
पूर्ण;

काष्ठा sx9500_reg_शेष अणु
	u8 reg;
	u8 def;
पूर्ण;

अटल स्थिर काष्ठा sx9500_reg_शेष sx9500_शेष_regs[] = अणु
	अणु
		.reg = SX9500_REG_PROX_CTRL1,
		/* Shield enabled, small range. */
		.def = 0x43,
	पूर्ण,
	अणु
		.reg = SX9500_REG_PROX_CTRL2,
		/* x8 gain, 167kHz frequency, finest resolution. */
		.def = 0x77,
	पूर्ण,
	अणु
		.reg = SX9500_REG_PROX_CTRL3,
		/* Doze enabled, 2x scan period करोze, no raw filter. */
		.def = 0x40,
	पूर्ण,
	अणु
		.reg = SX9500_REG_PROX_CTRL4,
		/* Average threshold. */
		.def = 0x30,
	पूर्ण,
	अणु
		.reg = SX9500_REG_PROX_CTRL5,
		/*
		 * Debouncer off, lowest average negative filter,
		 * highest average positive filter.
		 */
		.def = 0x0f,
	पूर्ण,
	अणु
		.reg = SX9500_REG_PROX_CTRL6,
		/* Proximity detection threshold: 280 */
		.def = 0x0e,
	पूर्ण,
	अणु
		.reg = SX9500_REG_PROX_CTRL7,
		/*
		 * No स्वतःmatic compensation, compensate each pin
		 * independently, proximity hysteresis: 32, बंद
		 * debouncer off, far debouncer off.
		 */
		.def = 0x00,
	पूर्ण,
	अणु
		.reg = SX9500_REG_PROX_CTRL8,
		/* No stuck समयout, no periodic compensation. */
		.def = 0x00,
	पूर्ण,
	अणु
		.reg = SX9500_REG_PROX_CTRL0,
		/* Scan period: 30ms, all sensors disabled. */
		.def = 0x00,
	पूर्ण,
पूर्ण;

/* Activate all channels and perक्रमm an initial compensation. */
अटल पूर्णांक sx9500_init_compensation(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा sx9500_data *data = iio_priv(indio_dev);
	पूर्णांक i, ret;
	अचिन्हित पूर्णांक val;

	ret = regmap_update_bits(data->regmap, SX9500_REG_PROX_CTRL0,
				 SX9500_CHAN_MASK, SX9500_CHAN_MASK);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 10; i >= 0; i--) अणु
		usleep_range(10000, 20000);
		ret = regmap_पढ़ो(data->regmap, SX9500_REG_STAT, &val);
		अगर (ret < 0)
			जाओ out;
		अगर (!(val & SX9500_COMPSTAT_MASK))
			अवरोध;
	पूर्ण

	अगर (i < 0) अणु
		dev_err(&data->client->dev, "initial compensation timed out");
		ret = -ETIMEDOUT;
	पूर्ण

out:
	regmap_update_bits(data->regmap, SX9500_REG_PROX_CTRL0,
			   SX9500_CHAN_MASK, 0);
	वापस ret;
पूर्ण

अटल पूर्णांक sx9500_init_device(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा sx9500_data *data = iio_priv(indio_dev);
	पूर्णांक ret, i;
	अचिन्हित पूर्णांक val;

	अगर (data->gpiod_rst) अणु
		gpiod_set_value_cansleep(data->gpiod_rst, 0);
		usleep_range(1000, 2000);
		gpiod_set_value_cansleep(data->gpiod_rst, 1);
		usleep_range(1000, 2000);
	पूर्ण

	ret = regmap_ग_लिखो(data->regmap, SX9500_REG_IRQ_MSK, 0);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(data->regmap, SX9500_REG_RESET,
			   SX9500_SOFT_RESET);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_पढ़ो(data->regmap, SX9500_REG_IRQ_SRC, &val);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < ARRAY_SIZE(sx9500_शेष_regs); i++) अणु
		ret = regmap_ग_लिखो(data->regmap,
				   sx9500_शेष_regs[i].reg,
				   sx9500_शेष_regs[i].def);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस sx9500_init_compensation(indio_dev);
पूर्ण

अटल स्थिर काष्ठा acpi_gpio_params reset_gpios = अणु 0, 0, false पूर्ण;
अटल स्थिर काष्ठा acpi_gpio_params पूर्णांकerrupt_gpios = अणु 2, 0, false पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_mapping acpi_sx9500_gpios[] = अणु
	अणु "reset-gpios", &reset_gpios, 1 पूर्ण,
	/*
	 * Some platक्रमms have a bug in ACPI GPIO description making IRQ
	 * GPIO to be output only. Ask the GPIO core to ignore this limit.
	 */
	अणु "interrupt-gpios", &पूर्णांकerrupt_gpios, 1, ACPI_GPIO_QUIRK_NO_IO_RESTRICTION पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल व्योम sx9500_gpio_probe(काष्ठा i2c_client *client,
			      काष्ठा sx9500_data *data)
अणु
	काष्ठा gpio_desc *gpiod_पूर्णांक;
	काष्ठा device *dev;
	पूर्णांक ret;

	अगर (!client)
		वापस;

	dev = &client->dev;

	ret = devm_acpi_dev_add_driver_gpios(dev, acpi_sx9500_gpios);
	अगर (ret)
		dev_dbg(dev, "Unable to add GPIO mapping table\n");

	अगर (client->irq <= 0) अणु
		gpiod_पूर्णांक = devm_gpiod_get(dev, "interrupt", GPIOD_IN);
		अगर (IS_ERR(gpiod_पूर्णांक))
			dev_err(dev, "gpio get irq failed\n");
		अन्यथा
			client->irq = gpiod_to_irq(gpiod_पूर्णांक);
	पूर्ण

	data->gpiod_rst = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(data->gpiod_rst)) अणु
		dev_warn(dev, "gpio get reset pin failed\n");
		data->gpiod_rst = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक sx9500_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा iio_dev *indio_dev;
	काष्ठा sx9500_data *data;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (indio_dev == शून्य)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	data->client = client;
	mutex_init(&data->mutex);
	init_completion(&data->completion);
	data->trigger_enabled = false;

	data->regmap = devm_regmap_init_i2c(client, &sx9500_regmap_config);
	अगर (IS_ERR(data->regmap))
		वापस PTR_ERR(data->regmap);

	indio_dev->name = SX9500_DRIVER_NAME;
	indio_dev->channels = sx9500_channels;
	indio_dev->num_channels = ARRAY_SIZE(sx9500_channels);
	indio_dev->info = &sx9500_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	i2c_set_clientdata(client, indio_dev);

	sx9500_gpio_probe(client, data);

	ret = sx9500_init_device(indio_dev);
	अगर (ret < 0)
		वापस ret;

	अगर (client->irq <= 0)
		dev_warn(&client->dev, "no valid irq found\n");
	अन्यथा अणु
		ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
				sx9500_irq_handler, sx9500_irq_thपढ़ो_handler,
				IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				SX9500_IRQ_NAME, indio_dev);
		अगर (ret < 0)
			वापस ret;

		data->trig = devm_iio_trigger_alloc(&client->dev,
				"%s-dev%d", indio_dev->name, indio_dev->id);
		अगर (!data->trig)
			वापस -ENOMEM;

		data->trig->ops = &sx9500_trigger_ops;
		iio_trigger_set_drvdata(data->trig, indio_dev);

		ret = iio_trigger_रेजिस्टर(data->trig);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = iio_triggered_buffer_setup(indio_dev, शून्य,
					 sx9500_trigger_handler,
					 &sx9500_buffer_setup_ops);
	अगर (ret < 0)
		जाओ out_trigger_unरेजिस्टर;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0)
		जाओ out_buffer_cleanup;

	वापस 0;

out_buffer_cleanup:
	iio_triggered_buffer_cleanup(indio_dev);
out_trigger_unरेजिस्टर:
	अगर (client->irq > 0)
		iio_trigger_unरेजिस्टर(data->trig);

	वापस ret;
पूर्ण

अटल पूर्णांक sx9500_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा sx9500_data *data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);
	अगर (client->irq > 0)
		iio_trigger_unरेजिस्टर(data->trig);
	kमुक्त(data->buffer);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sx9500_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा sx9500_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->mutex);
	ret = regmap_पढ़ो(data->regmap, SX9500_REG_PROX_CTRL0,
			  &data->suspend_ctrl0);
	अगर (ret < 0)
		जाओ out;

	/*
	 * Scan period करोesn't matter because when all the sensors are
	 * deactivated the device is in sleep mode.
	 */
	ret = regmap_ग_लिखो(data->regmap, SX9500_REG_PROX_CTRL0, 0);

out:
	mutex_unlock(&data->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक sx9500_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा sx9500_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->mutex);
	ret = regmap_ग_लिखो(data->regmap, SX9500_REG_PROX_CTRL0,
			   data->suspend_ctrl0);
	mutex_unlock(&data->mutex);

	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा dev_pm_ops sx9500_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(sx9500_suspend, sx9500_resume)
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id sx9500_acpi_match[] = अणु
	अणु"SSX9500", 0पूर्ण,
	अणु"SASX9500", 0पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, sx9500_acpi_match);

अटल स्थिर काष्ठा of_device_id sx9500_of_match[] = अणु
	अणु .compatible = "semtech,sx9500", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sx9500_of_match);

अटल स्थिर काष्ठा i2c_device_id sx9500_id[] = अणु
	अणु"sx9500", 0पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, sx9500_id);

अटल काष्ठा i2c_driver sx9500_driver = अणु
	.driver = अणु
		.name	= SX9500_DRIVER_NAME,
		.acpi_match_table = ACPI_PTR(sx9500_acpi_match),
		.of_match_table = of_match_ptr(sx9500_of_match),
		.pm = &sx9500_pm_ops,
	पूर्ण,
	.probe		= sx9500_probe,
	.हटाओ		= sx9500_हटाओ,
	.id_table	= sx9500_id,
पूर्ण;
module_i2c_driver(sx9500_driver);

MODULE_AUTHOR("Vlad Dogaru <vlad.dogaru@intel.com>");
MODULE_DESCRIPTION("Driver for Semtech SX9500 proximity sensor");
MODULE_LICENSE("GPL v2");
