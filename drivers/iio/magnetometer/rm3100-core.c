<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PNI RM3100 3-axis geomagnetic sensor driver core.
 *
 * Copyright (C) 2018 Song Qiang <songqiang1304521@gmail.com>
 *
 * User Manual available at
 * <https://www.pnicorp.com/करोwnload/rm3100-user-manual/>
 *
 * TODO: event generation, pm.
 */

#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/trigger_consumer.h>

#समावेश <यंत्र/unaligned.h>

#समावेश "rm3100.h"

/* Cycle Count Registers. */
#घोषणा RM3100_REG_CC_X			0x05
#घोषणा RM3100_REG_CC_Y			0x07
#घोषणा RM3100_REG_CC_Z			0x09

/* Poll Measurement Mode रेजिस्टर. */
#घोषणा RM3100_REG_POLL			0x00
#घोषणा		RM3100_POLL_X		BIT(4)
#घोषणा		RM3100_POLL_Y		BIT(5)
#घोषणा		RM3100_POLL_Z		BIT(6)

/* Continuous Measurement Mode रेजिस्टर. */
#घोषणा RM3100_REG_CMM			0x01
#घोषणा		RM3100_CMM_START	BIT(0)
#घोषणा		RM3100_CMM_X		BIT(4)
#घोषणा		RM3100_CMM_Y		BIT(5)
#घोषणा		RM3100_CMM_Z		BIT(6)

/* TiMe Rate Configuration रेजिस्टर. */
#घोषणा RM3100_REG_TMRC			0x0B
#घोषणा RM3100_TMRC_OFFSET		0x92

/* Result Status रेजिस्टर. */
#घोषणा RM3100_REG_STATUS		0x34
#घोषणा		RM3100_STATUS_DRDY	BIT(7)

/* Measurement result रेजिस्टरs. */
#घोषणा RM3100_REG_MX2			0x24
#घोषणा RM3100_REG_MY2			0x27
#घोषणा RM3100_REG_MZ2			0x2a

#घोषणा RM3100_W_REG_START		RM3100_REG_POLL
#घोषणा RM3100_W_REG_END		RM3100_REG_TMRC
#घोषणा RM3100_R_REG_START		RM3100_REG_POLL
#घोषणा RM3100_R_REG_END		RM3100_REG_STATUS
#घोषणा RM3100_V_REG_START		RM3100_REG_POLL
#घोषणा RM3100_V_REG_END		RM3100_REG_STATUS

/*
 * This is computed by hand, is the sum of channel storage bits and padding
 * bits, which is 4+4+4+12=24 in here.
 */
#घोषणा RM3100_SCAN_BYTES		24

#घोषणा RM3100_CMM_AXIS_SHIFT		4

काष्ठा rm3100_data अणु
	काष्ठा regmap *regmap;
	काष्ठा completion measuring_करोne;
	bool use_पूर्णांकerrupt;
	पूर्णांक conversion_समय;
	पूर्णांक scale;
	u8 buffer[RM3100_SCAN_BYTES];
	काष्ठा iio_trigger *drdy_trig;

	/*
	 * This lock is क्रम protecting the consistency of series of i2c
	 * operations, that is, to make sure a measurement process will
	 * not be पूर्णांकerrupted by a set frequency operation, which should
	 * be taken where a series of i2c operation starts, released where
	 * the operation ends.
	 */
	काष्ठा mutex lock;
पूर्ण;

अटल स्थिर काष्ठा regmap_range rm3100_पढ़ोable_ranges[] = अणु
	regmap_reg_range(RM3100_R_REG_START, RM3100_R_REG_END),
पूर्ण;

स्थिर काष्ठा regmap_access_table rm3100_पढ़ोable_table = अणु
	.yes_ranges = rm3100_पढ़ोable_ranges,
	.n_yes_ranges = ARRAY_SIZE(rm3100_पढ़ोable_ranges),
पूर्ण;
EXPORT_SYMBOL_GPL(rm3100_पढ़ोable_table);

अटल स्थिर काष्ठा regmap_range rm3100_writable_ranges[] = अणु
	regmap_reg_range(RM3100_W_REG_START, RM3100_W_REG_END),
पूर्ण;

स्थिर काष्ठा regmap_access_table rm3100_writable_table = अणु
	.yes_ranges = rm3100_writable_ranges,
	.n_yes_ranges = ARRAY_SIZE(rm3100_writable_ranges),
पूर्ण;
EXPORT_SYMBOL_GPL(rm3100_writable_table);

अटल स्थिर काष्ठा regmap_range rm3100_अस्थिर_ranges[] = अणु
	regmap_reg_range(RM3100_V_REG_START, RM3100_V_REG_END),
पूर्ण;

स्थिर काष्ठा regmap_access_table rm3100_अस्थिर_table = अणु
	.yes_ranges = rm3100_अस्थिर_ranges,
	.n_yes_ranges = ARRAY_SIZE(rm3100_अस्थिर_ranges),
पूर्ण;
EXPORT_SYMBOL_GPL(rm3100_अस्थिर_table);

अटल irqवापस_t rm3100_thपढ़ो_fn(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा iio_dev *indio_dev = d;
	काष्ठा rm3100_data *data = iio_priv(indio_dev);

	/*
	 * Write operation to any रेजिस्टर or पढ़ो operation
	 * to first byte of results will clear the पूर्णांकerrupt.
	 */
	regmap_ग_लिखो(data->regmap, RM3100_REG_POLL, 0);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t rm3100_irq_handler(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा iio_dev *indio_dev = d;
	काष्ठा rm3100_data *data = iio_priv(indio_dev);

	चयन (indio_dev->currenपंचांगode) अणु
	हाल INDIO_सूचीECT_MODE:
		complete(&data->measuring_करोne);
		अवरोध;
	हाल INDIO_BUFFER_TRIGGERED:
		iio_trigger_poll(data->drdy_trig);
		अवरोध;
	शेष:
		dev_err(indio_dev->dev.parent,
			"device mode out of control, current mode: %d",
			indio_dev->currenपंचांगode);
	पूर्ण

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल पूर्णांक rm3100_रुको_measurement(काष्ठा rm3100_data *data)
अणु
	काष्ठा regmap *regmap = data->regmap;
	अचिन्हित पूर्णांक val;
	पूर्णांक tries = 20;
	पूर्णांक ret;

	/*
	 * A पढ़ो cycle of 400kbits i2c bus is about 20us, plus the समय
	 * used क्रम scheduling, a पढ़ो cycle of fast mode of this device
	 * can reach 1.7ms, it may be possible क्रम data to arrive just
	 * after we check the RM3100_REG_STATUS. In this हाल, irq_handler is
	 * called beक्रमe measuring_करोne is reinitialized, it will रुको
	 * क्रमever क्रम data that has alपढ़ोy been पढ़ोy.
	 * Reinitialize measuring_करोne beक्रमe looking up makes sure we
	 * will always capture पूर्णांकerrupt no matter when it happens.
	 */
	अगर (data->use_पूर्णांकerrupt)
		reinit_completion(&data->measuring_करोne);

	ret = regmap_पढ़ो(regmap, RM3100_REG_STATUS, &val);
	अगर (ret < 0)
		वापस ret;

	अगर ((val & RM3100_STATUS_DRDY) != RM3100_STATUS_DRDY) अणु
		अगर (data->use_पूर्णांकerrupt) अणु
			ret = रुको_क्रम_completion_समयout(&data->measuring_करोne,
				msecs_to_jअगरfies(data->conversion_समय));
			अगर (!ret)
				वापस -ETIMEDOUT;
		पूर्ण अन्यथा अणु
			करो अणु
				usleep_range(1000, 5000);

				ret = regmap_पढ़ो(regmap, RM3100_REG_STATUS,
						  &val);
				अगर (ret < 0)
					वापस ret;

				अगर (val & RM3100_STATUS_DRDY)
					अवरोध;
			पूर्ण जबतक (--tries);
			अगर (!tries)
				वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rm3100_पढ़ो_mag(काष्ठा rm3100_data *data, पूर्णांक idx, पूर्णांक *val)
अणु
	काष्ठा regmap *regmap = data->regmap;
	u8 buffer[3];
	पूर्णांक ret;

	mutex_lock(&data->lock);
	ret = regmap_ग_लिखो(regmap, RM3100_REG_POLL, BIT(4 + idx));
	अगर (ret < 0)
		जाओ unlock_वापस;

	ret = rm3100_रुको_measurement(data);
	अगर (ret < 0)
		जाओ unlock_वापस;

	ret = regmap_bulk_पढ़ो(regmap, RM3100_REG_MX2 + 3 * idx, buffer, 3);
	अगर (ret < 0)
		जाओ unlock_वापस;
	mutex_unlock(&data->lock);

	*val = sign_extend32(get_unaligned_be24(&buffer[0]), 23);

	वापस IIO_VAL_INT;

unlock_वापस:
	mutex_unlock(&data->lock);
	वापस ret;
पूर्ण

#घोषणा RM3100_CHANNEL(axis, idx)					\
	अणु								\
		.type = IIO_MAGN,					\
		.modअगरied = 1,						\
		.channel2 = IIO_MOD_##axis,				\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) |	\
			BIT(IIO_CHAN_INFO_SAMP_FREQ),			\
		.scan_index = idx,					\
		.scan_type = अणु						\
			.sign = 's',					\
			.realbits = 24,					\
			.storagebits = 32,				\
			.shअगरt = 8,					\
			.endianness = IIO_BE,				\
		पूर्ण,							\
	पूर्ण

अटल स्थिर काष्ठा iio_chan_spec rm3100_channels[] = अणु
	RM3100_CHANNEL(X, 0),
	RM3100_CHANNEL(Y, 1),
	RM3100_CHANNEL(Z, 2),
	IIO_CHAN_SOFT_TIMESTAMP(3),
पूर्ण;

अटल IIO_CONST_ATTR_SAMP_FREQ_AVAIL(
	"600 300 150 75 37 18 9 4.5 2.3 1.2 0.6 0.3 0.015 0.075"
);

अटल काष्ठा attribute *rm3100_attributes[] = अणु
	&iio_स्थिर_attr_sampling_frequency_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group rm3100_attribute_group = अणु
	.attrs = rm3100_attributes,
पूर्ण;

#घोषणा RM3100_SAMP_NUM			14

/*
 * Frequency : rm3100_samp_rates[][0].rm3100_samp_rates[][1]Hz.
 * Time between पढ़ोing: rm3100_sam_rates[][2]ms.
 * The first one is actually 1.7ms.
 */
अटल स्थिर पूर्णांक rm3100_samp_rates[RM3100_SAMP_NUM][3] = अणु
	अणु600, 0, 2पूर्ण, अणु300, 0, 3पूर्ण, अणु150, 0, 7पूर्ण, अणु75, 0, 13पूर्ण, अणु37, 0, 27पूर्ण,
	अणु18, 0, 55पूर्ण, अणु9, 0, 110पूर्ण, अणु4, 500000, 220पूर्ण, अणु2, 300000, 440पूर्ण,
	अणु1, 200000, 800पूर्ण, अणु0, 600000, 1600पूर्ण, अणु0, 300000, 3300पूर्ण,
	अणु0, 15000, 6700पूर्ण,  अणु0, 75000, 13000पूर्ण
पूर्ण;

अटल पूर्णांक rm3100_get_samp_freq(काष्ठा rm3100_data *data, पूर्णांक *val, पूर्णांक *val2)
अणु
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक ret;

	mutex_lock(&data->lock);
	ret = regmap_पढ़ो(data->regmap, RM3100_REG_TMRC, &पंचांगp);
	mutex_unlock(&data->lock);
	अगर (ret < 0)
		वापस ret;
	*val = rm3100_samp_rates[पंचांगp - RM3100_TMRC_OFFSET][0];
	*val2 = rm3100_samp_rates[पंचांगp - RM3100_TMRC_OFFSET][1];

	वापस IIO_VAL_INT_PLUS_MICRO;
पूर्ण

अटल पूर्णांक rm3100_set_cycle_count(काष्ठा rm3100_data *data, पूर्णांक val)
अणु
	पूर्णांक ret;
	u8 i;

	क्रम (i = 0; i < 3; i++) अणु
		ret = regmap_ग_लिखो(data->regmap, RM3100_REG_CC_X + 2 * i, val);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/*
	 * The scale of this sensor depends on the cycle count value, these
	 * three values are corresponding to the cycle count value 50, 100,
	 * 200. scale = output / gain * 10^4.
	 */
	चयन (val) अणु
	हाल 50:
		data->scale = 500;
		अवरोध;
	हाल 100:
		data->scale = 263;
		अवरोध;
	/*
	 * हाल 200:
	 * This function will never be called by users' code, so here we
	 * assume that it will never get a wrong parameter.
	 */
	शेष:
		data->scale = 133;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rm3100_set_samp_freq(काष्ठा iio_dev *indio_dev, पूर्णांक val, पूर्णांक val2)
अणु
	काष्ठा rm3100_data *data = iio_priv(indio_dev);
	काष्ठा regmap *regmap = data->regmap;
	अचिन्हित पूर्णांक cycle_count;
	पूर्णांक ret;
	पूर्णांक i;

	mutex_lock(&data->lock);
	/* All cycle count रेजिस्टरs use the same value. */
	ret = regmap_पढ़ो(regmap, RM3100_REG_CC_X, &cycle_count);
	अगर (ret < 0)
		जाओ unlock_वापस;

	क्रम (i = 0; i < RM3100_SAMP_NUM; i++) अणु
		अगर (val == rm3100_samp_rates[i][0] &&
		    val2 == rm3100_samp_rates[i][1])
			अवरोध;
	पूर्ण
	अगर (i == RM3100_SAMP_NUM) अणु
		ret = -EINVAL;
		जाओ unlock_वापस;
	पूर्ण

	ret = regmap_ग_लिखो(regmap, RM3100_REG_TMRC, i + RM3100_TMRC_OFFSET);
	अगर (ret < 0)
		जाओ unlock_वापस;

	/* Checking अगर cycle count रेजिस्टरs need changing. */
	अगर (val == 600 && cycle_count == 200) अणु
		ret = rm3100_set_cycle_count(data, 100);
		अगर (ret < 0)
			जाओ unlock_वापस;
	पूर्ण अन्यथा अगर (val != 600 && cycle_count == 100) अणु
		ret = rm3100_set_cycle_count(data, 200);
		अगर (ret < 0)
			जाओ unlock_वापस;
	पूर्ण

	अगर (indio_dev->currenपंचांगode == INDIO_BUFFER_TRIGGERED) अणु
		/* Writing TMRC रेजिस्टरs requires CMM reset. */
		ret = regmap_ग_लिखो(regmap, RM3100_REG_CMM, 0);
		अगर (ret < 0)
			जाओ unlock_वापस;
		ret = regmap_ग_लिखो(data->regmap, RM3100_REG_CMM,
			(*indio_dev->active_scan_mask & 0x7) <<
			RM3100_CMM_AXIS_SHIFT | RM3100_CMM_START);
		अगर (ret < 0)
			जाओ unlock_वापस;
	पूर्ण
	mutex_unlock(&data->lock);

	data->conversion_समय = rm3100_samp_rates[i][2] * 2;
	वापस 0;

unlock_वापस:
	mutex_unlock(&data->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक rm3100_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   स्थिर काष्ठा iio_chan_spec *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा rm3100_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret < 0)
			वापस ret;

		ret = rm3100_पढ़ो_mag(data, chan->scan_index, val);
		iio_device_release_direct_mode(indio_dev);

		वापस ret;
	हाल IIO_CHAN_INFO_SCALE:
		*val = 0;
		*val2 = data->scale;

		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		वापस rm3100_get_samp_freq(data, val, val2);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक rm3100_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		वापस rm3100_set_samp_freq(indio_dev, val, val2);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info rm3100_info = अणु
	.attrs = &rm3100_attribute_group,
	.पढ़ो_raw = rm3100_पढ़ो_raw,
	.ग_लिखो_raw = rm3100_ग_लिखो_raw,
पूर्ण;

अटल पूर्णांक rm3100_buffer_preenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा rm3100_data *data = iio_priv(indio_dev);

	/* Starting channels enabled. */
	वापस regmap_ग_लिखो(data->regmap, RM3100_REG_CMM,
		(*indio_dev->active_scan_mask & 0x7) << RM3100_CMM_AXIS_SHIFT |
		RM3100_CMM_START);
पूर्ण

अटल पूर्णांक rm3100_buffer_postdisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा rm3100_data *data = iio_priv(indio_dev);

	वापस regmap_ग_लिखो(data->regmap, RM3100_REG_CMM, 0);
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops rm3100_buffer_ops = अणु
	.preenable = rm3100_buffer_preenable,
	.postdisable = rm3100_buffer_postdisable,
पूर्ण;

अटल irqवापस_t rm3100_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	अचिन्हित दीर्घ scan_mask = *indio_dev->active_scan_mask;
	अचिन्हित पूर्णांक mask_len = indio_dev->masklength;
	काष्ठा rm3100_data *data = iio_priv(indio_dev);
	काष्ठा regmap *regmap = data->regmap;
	पूर्णांक ret, i, bit;

	mutex_lock(&data->lock);
	चयन (scan_mask) अणु
	हाल BIT(0) | BIT(1) | BIT(2):
		ret = regmap_bulk_पढ़ो(regmap, RM3100_REG_MX2, data->buffer, 9);
		mutex_unlock(&data->lock);
		अगर (ret < 0)
			जाओ करोne;
		/* Convert XXXYYYZZZxxx to XXXxYYYxZZZx. x क्रम paddings. */
		क्रम (i = 2; i > 0; i--)
			स_हटाओ(data->buffer + i * 4, data->buffer + i * 3, 3);
		अवरोध;
	हाल BIT(0) | BIT(1):
		ret = regmap_bulk_पढ़ो(regmap, RM3100_REG_MX2, data->buffer, 6);
		mutex_unlock(&data->lock);
		अगर (ret < 0)
			जाओ करोne;
		स_हटाओ(data->buffer + 4, data->buffer + 3, 3);
		अवरोध;
	हाल BIT(1) | BIT(2):
		ret = regmap_bulk_पढ़ो(regmap, RM3100_REG_MY2, data->buffer, 6);
		mutex_unlock(&data->lock);
		अगर (ret < 0)
			जाओ करोne;
		स_हटाओ(data->buffer + 4, data->buffer + 3, 3);
		अवरोध;
	हाल BIT(0) | BIT(2):
		ret = regmap_bulk_पढ़ो(regmap, RM3100_REG_MX2, data->buffer, 9);
		mutex_unlock(&data->lock);
		अगर (ret < 0)
			जाओ करोne;
		स_हटाओ(data->buffer + 4, data->buffer + 6, 3);
		अवरोध;
	शेष:
		क्रम_each_set_bit(bit, &scan_mask, mask_len) अणु
			ret = regmap_bulk_पढ़ो(regmap, RM3100_REG_MX2 + 3 * bit,
					       data->buffer, 3);
			अगर (ret < 0) अणु
				mutex_unlock(&data->lock);
				जाओ करोne;
			पूर्ण
		पूर्ण
		mutex_unlock(&data->lock);
	पूर्ण
	/*
	 * Always using the same buffer so that we wouldn't need to set the
	 * paddings to 0 in हाल of leaking any data.
	 */
	iio_push_to_buffers_with_बारtamp(indio_dev, data->buffer,
					   pf->बारtamp);
करोne:
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक rm3100_common_probe(काष्ठा device *dev, काष्ठा regmap *regmap, पूर्णांक irq)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा rm3100_data *data;
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	data->regmap = regmap;

	mutex_init(&data->lock);

	indio_dev->name = "rm3100";
	indio_dev->info = &rm3100_info;
	indio_dev->channels = rm3100_channels;
	indio_dev->num_channels = ARRAY_SIZE(rm3100_channels);
	indio_dev->modes = INDIO_सूचीECT_MODE | INDIO_BUFFER_TRIGGERED;
	indio_dev->currenपंचांगode = INDIO_सूचीECT_MODE;

	अगर (!irq)
		data->use_पूर्णांकerrupt = false;
	अन्यथा अणु
		data->use_पूर्णांकerrupt = true;

		init_completion(&data->measuring_करोne);
		ret = devm_request_thपढ़ोed_irq(dev,
						irq,
						rm3100_irq_handler,
						rm3100_thपढ़ो_fn,
						IRQF_TRIGGER_HIGH |
						IRQF_ONESHOT,
						indio_dev->name,
						indio_dev);
		अगर (ret < 0) अणु
			dev_err(dev, "request irq line failed.\n");
			वापस ret;
		पूर्ण

		data->drdy_trig = devm_iio_trigger_alloc(dev, "%s-drdy%d",
							 indio_dev->name,
							 indio_dev->id);
		अगर (!data->drdy_trig)
			वापस -ENOMEM;

		ret = devm_iio_trigger_रेजिस्टर(dev, data->drdy_trig);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	ret = devm_iio_triggered_buffer_setup(dev, indio_dev,
					      &iio_pollfunc_store_समय,
					      rm3100_trigger_handler,
					      &rm3100_buffer_ops);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_पढ़ो(regmap, RM3100_REG_TMRC, &पंचांगp);
	अगर (ret < 0)
		वापस ret;
	/* Initializing max रुको समय, which is द्विगुन conversion समय. */
	data->conversion_समय = rm3100_samp_rates[पंचांगp - RM3100_TMRC_OFFSET][2]
				* 2;

	/* Cycle count values may not be what we want. */
	अगर ((पंचांगp - RM3100_TMRC_OFFSET) == 0)
		rm3100_set_cycle_count(data, 100);
	अन्यथा
		rm3100_set_cycle_count(data, 200);

	वापस devm_iio_device_रेजिस्टर(dev, indio_dev);
पूर्ण
EXPORT_SYMBOL_GPL(rm3100_common_probe);

MODULE_AUTHOR("Song Qiang <songqiang1304521@gmail.com>");
MODULE_DESCRIPTION("PNI RM3100 3-axis magnetometer i2c driver");
MODULE_LICENSE("GPL v2");
