<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AD5421 Digital to analog converters  driver
 *
 * Copyright 2011 Analog Devices Inc.
 */

#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/dac/ad5421.h>


#घोषणा AD5421_REG_DAC_DATA		0x1
#घोषणा AD5421_REG_CTRL			0x2
#घोषणा AD5421_REG_OFFSET		0x3
#घोषणा AD5421_REG_GAIN			0x4
/* load dac and fault shared the same रेजिस्टर number. Writing to it will cause
 * a dac load command, पढ़ोing from it will वापस the fault status रेजिस्टर */
#घोषणा AD5421_REG_LOAD_DAC		0x5
#घोषणा AD5421_REG_FAULT		0x5
#घोषणा AD5421_REG_FORCE_ALARM_CURRENT	0x6
#घोषणा AD5421_REG_RESET		0x7
#घोषणा AD5421_REG_START_CONVERSION	0x8
#घोषणा AD5421_REG_NOOP			0x9

#घोषणा AD5421_CTRL_WATCHDOG_DISABLE	BIT(12)
#घोषणा AD5421_CTRL_AUTO_FAULT_READBACK	BIT(11)
#घोषणा AD5421_CTRL_MIN_CURRENT		BIT(9)
#घोषणा AD5421_CTRL_ADC_SOURCE_TEMP	BIT(8)
#घोषणा AD5421_CTRL_ADC_ENABLE		BIT(7)
#घोषणा AD5421_CTRL_PWR_DOWN_INT_VREF	BIT(6)

#घोषणा AD5421_FAULT_SPI			BIT(15)
#घोषणा AD5421_FAULT_PEC			BIT(14)
#घोषणा AD5421_FAULT_OVER_CURRENT		BIT(13)
#घोषणा AD5421_FAULT_UNDER_CURRENT		BIT(12)
#घोषणा AD5421_FAULT_TEMP_OVER_140		BIT(11)
#घोषणा AD5421_FAULT_TEMP_OVER_100		BIT(10)
#घोषणा AD5421_FAULT_UNDER_VOLTAGE_6V		BIT(9)
#घोषणा AD5421_FAULT_UNDER_VOLTAGE_12V		BIT(8)

/* These bits will cause the fault pin to go high */
#घोषणा AD5421_FAULT_TRIGGER_IRQ \
	(AD5421_FAULT_SPI | AD5421_FAULT_PEC | AD5421_FAULT_OVER_CURRENT | \
	AD5421_FAULT_UNDER_CURRENT | AD5421_FAULT_TEMP_OVER_140)

/**
 * काष्ठा ad5421_state - driver instance specअगरic data
 * @spi:		spi_device
 * @ctrl:		control रेजिस्टर cache
 * @current_range:	current range which the device is configured क्रम
 * @data:		spi transfer buffers
 * @fault_mask:		software masking of events
 * @lock:		lock to protect the data buffer during SPI ops
 */
काष्ठा ad5421_state अणु
	काष्ठा spi_device		*spi;
	अचिन्हित पूर्णांक			ctrl;
	क्रमागत ad5421_current_range	current_range;
	अचिन्हित पूर्णांक			fault_mask;
	काष्ठा mutex			lock;

	/*
	 * DMA (thus cache coherency मुख्यtenance) requires the
	 * transfer buffers to live in their own cache lines.
	 */
	जोड़ अणु
		__be32 d32;
		u8 d8[4];
	पूर्ण data[2] ____cacheline_aligned;
पूर्ण;

अटल स्थिर काष्ठा iio_event_spec ad5421_current_event[] = अणु
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

अटल स्थिर काष्ठा iio_event_spec ad5421_temp_event[] = अणु
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_RISING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE) |
			BIT(IIO_EV_INFO_ENABLE),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec ad5421_channels[] = अणु
	अणु
		.type = IIO_CURRENT,
		.indexed = 1,
		.output = 1,
		.channel = 0,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_CALIBSCALE) |
			BIT(IIO_CHAN_INFO_CALIBBIAS),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) |
			BIT(IIO_CHAN_INFO_OFFSET),
		.scan_type = अणु
			.sign = 'u',
			.realbits = 16,
			.storagebits = 16,
		पूर्ण,
		.event_spec = ad5421_current_event,
		.num_event_specs = ARRAY_SIZE(ad5421_current_event),
	पूर्ण,
	अणु
		.type = IIO_TEMP,
		.channel = -1,
		.event_spec = ad5421_temp_event,
		.num_event_specs = ARRAY_SIZE(ad5421_temp_event),
	पूर्ण,
पूर्ण;

अटल पूर्णांक ad5421_ग_लिखो_unlocked(काष्ठा iio_dev *indio_dev,
	अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	काष्ठा ad5421_state *st = iio_priv(indio_dev);

	st->data[0].d32 = cpu_to_be32((reg << 16) | val);

	वापस spi_ग_लिखो(st->spi, &st->data[0].d8[1], 3);
पूर्ण

अटल पूर्णांक ad5421_ग_लिखो(काष्ठा iio_dev *indio_dev, अचिन्हित पूर्णांक reg,
	अचिन्हित पूर्णांक val)
अणु
	काष्ठा ad5421_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&st->lock);
	ret = ad5421_ग_लिखो_unlocked(indio_dev, reg, val);
	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ad5421_पढ़ो(काष्ठा iio_dev *indio_dev, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा ad5421_state *st = iio_priv(indio_dev);
	पूर्णांक ret;
	काष्ठा spi_transfer t[] = अणु
		अणु
			.tx_buf = &st->data[0].d8[1],
			.len = 3,
			.cs_change = 1,
		पूर्ण, अणु
			.rx_buf = &st->data[1].d8[1],
			.len = 3,
		पूर्ण,
	पूर्ण;

	mutex_lock(&st->lock);

	st->data[0].d32 = cpu_to_be32((1 << 23) | (reg << 16));

	ret = spi_sync_transfer(st->spi, t, ARRAY_SIZE(t));
	अगर (ret >= 0)
		ret = be32_to_cpu(st->data[1].d32) & 0xffff;

	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ad5421_update_ctrl(काष्ठा iio_dev *indio_dev, अचिन्हित पूर्णांक set,
	अचिन्हित पूर्णांक clr)
अणु
	काष्ठा ad5421_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक ret;

	mutex_lock(&st->lock);

	st->ctrl &= ~clr;
	st->ctrl |= set;

	ret = ad5421_ग_लिखो_unlocked(indio_dev, AD5421_REG_CTRL, st->ctrl);

	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल irqवापस_t ad5421_fault_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा iio_dev *indio_dev = data;
	काष्ठा ad5421_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक fault;
	अचिन्हित पूर्णांक old_fault = 0;
	अचिन्हित पूर्णांक events;

	fault = ad5421_पढ़ो(indio_dev, AD5421_REG_FAULT);
	अगर (!fault)
		वापस IRQ_NONE;

	/* If we had a fault, this might mean that the DAC has lost its state
	 * and has been reset. Make sure that the control रेजिस्टर actually
	 * contains what we expect it to contain. Otherwise the watchकरोg might
	 * be enabled and we get watchकरोg समयout faults, which will render the
	 * DAC unusable. */
	ad5421_update_ctrl(indio_dev, 0, 0);


	/* The fault pin stays high as दीर्घ as a fault condition is present and
	 * it is not possible to mask fault conditions. For certain fault
	 * conditions क्रम example like over-temperature it takes some समय
	 * until the fault condition disappears. If we would निकास the पूर्णांकerrupt
	 * handler immediately after handling the event it would be entered
	 * again instantly. Thus we fall back to polling in हाल we detect that
	 * a पूर्णांकerrupt condition is still present.
	 */
	करो अणु
		/* 0xffff is a invalid value क्रम the रेजिस्टर and will only be
		 * पढ़ो अगर there has been a communication error */
		अगर (fault == 0xffff)
			fault = 0;

		/* we are only पूर्णांकerested in new events */
		events = (old_fault ^ fault) & fault;
		events &= st->fault_mask;

		अगर (events & AD5421_FAULT_OVER_CURRENT) अणु
			iio_push_event(indio_dev,
				IIO_UNMOD_EVENT_CODE(IIO_CURRENT,
					0,
					IIO_EV_TYPE_THRESH,
					IIO_EV_सूची_RISING),
			iio_get_समय_ns(indio_dev));
		पूर्ण

		अगर (events & AD5421_FAULT_UNDER_CURRENT) अणु
			iio_push_event(indio_dev,
				IIO_UNMOD_EVENT_CODE(IIO_CURRENT,
					0,
					IIO_EV_TYPE_THRESH,
					IIO_EV_सूची_FALLING),
				iio_get_समय_ns(indio_dev));
		पूर्ण

		अगर (events & AD5421_FAULT_TEMP_OVER_140) अणु
			iio_push_event(indio_dev,
				IIO_UNMOD_EVENT_CODE(IIO_TEMP,
					0,
					IIO_EV_TYPE_MAG,
					IIO_EV_सूची_RISING),
				iio_get_समय_ns(indio_dev));
		पूर्ण

		old_fault = fault;
		fault = ad5421_पढ़ो(indio_dev, AD5421_REG_FAULT);

		/* still active? go to sleep क्रम some समय */
		अगर (fault & AD5421_FAULT_TRIGGER_IRQ)
			msleep(1000);

	पूर्ण जबतक (fault & AD5421_FAULT_TRIGGER_IRQ);


	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम ad5421_get_current_min_max(काष्ठा ad5421_state *st,
	अचिन्हित पूर्णांक *min, अचिन्हित पूर्णांक *max)
अणु
	/* The current range is configured using बाह्यal pins, which are
	 * usually hard-wired and not run-समय चयनable. */
	चयन (st->current_range) अणु
	हाल AD5421_CURRENT_RANGE_4mA_20mA:
		*min = 4000;
		*max = 20000;
		अवरोध;
	हाल AD5421_CURRENT_RANGE_3mA8_21mA:
		*min = 3800;
		*max = 21000;
		अवरोध;
	हाल AD5421_CURRENT_RANGE_3mA2_24mA:
		*min = 3200;
		*max = 24000;
		अवरोध;
	शेष:
		*min = 0;
		*max = 1;
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ad5421_get_offset(काष्ठा ad5421_state *st)
अणु
	अचिन्हित पूर्णांक min, max;

	ad5421_get_current_min_max(st, &min, &max);
	वापस (min * (1 << 16)) / (max - min);
पूर्ण

अटल पूर्णांक ad5421_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
	काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val, पूर्णांक *val2, दीर्घ m)
अणु
	काष्ठा ad5421_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक min, max;
	पूर्णांक ret;

	अगर (chan->type != IIO_CURRENT)
		वापस -EINVAL;

	चयन (m) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = ad5421_पढ़ो(indio_dev, AD5421_REG_DAC_DATA);
		अगर (ret < 0)
			वापस ret;
		*val = ret;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		ad5421_get_current_min_max(st, &min, &max);
		*val = max - min;
		*val2 = (1 << 16) * 1000;
		वापस IIO_VAL_FRACTIONAL;
	हाल IIO_CHAN_INFO_OFFSET:
		*val = ad5421_get_offset(st);
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_CALIBBIAS:
		ret = ad5421_पढ़ो(indio_dev, AD5421_REG_OFFSET);
		अगर (ret < 0)
			वापस ret;
		*val = ret - 32768;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_CALIBSCALE:
		ret = ad5421_पढ़ो(indio_dev, AD5421_REG_GAIN);
		अगर (ret < 0)
			वापस ret;
		*val = ret;
		वापस IIO_VAL_INT;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ad5421_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
	काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	स्थिर अचिन्हित पूर्णांक max_val = 1 << 16;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (val >= max_val || val < 0)
			वापस -EINVAL;

		वापस ad5421_ग_लिखो(indio_dev, AD5421_REG_DAC_DATA, val);
	हाल IIO_CHAN_INFO_CALIBBIAS:
		val += 32768;
		अगर (val >= max_val || val < 0)
			वापस -EINVAL;

		वापस ad5421_ग_लिखो(indio_dev, AD5421_REG_OFFSET, val);
	हाल IIO_CHAN_INFO_CALIBSCALE:
		अगर (val >= max_val || val < 0)
			वापस -EINVAL;

		वापस ad5421_ग_लिखो(indio_dev, AD5421_REG_GAIN, val);
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ad5421_ग_लिखो_event_config(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
	क्रमागत iio_event_direction dir, पूर्णांक state)
अणु
	काष्ठा ad5421_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक mask;

	चयन (chan->type) अणु
	हाल IIO_CURRENT:
		अगर (dir == IIO_EV_सूची_RISING)
			mask = AD5421_FAULT_OVER_CURRENT;
		अन्यथा
			mask = AD5421_FAULT_UNDER_CURRENT;
		अवरोध;
	हाल IIO_TEMP:
		mask = AD5421_FAULT_TEMP_OVER_140;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&st->lock);
	अगर (state)
		st->fault_mask |= mask;
	अन्यथा
		st->fault_mask &= ~mask;
	mutex_unlock(&st->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक ad5421_पढ़ो_event_config(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
	क्रमागत iio_event_direction dir)
अणु
	काष्ठा ad5421_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक mask;

	चयन (chan->type) अणु
	हाल IIO_CURRENT:
		अगर (dir == IIO_EV_सूची_RISING)
			mask = AD5421_FAULT_OVER_CURRENT;
		अन्यथा
			mask = AD5421_FAULT_UNDER_CURRENT;
		अवरोध;
	हाल IIO_TEMP:
		mask = AD5421_FAULT_TEMP_OVER_140;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस (bool)(st->fault_mask & mask);
पूर्ण

अटल पूर्णांक ad5421_पढ़ो_event_value(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
	क्रमागत iio_event_direction dir, क्रमागत iio_event_info info, पूर्णांक *val,
	पूर्णांक *val2)
अणु
	पूर्णांक ret;

	चयन (chan->type) अणु
	हाल IIO_CURRENT:
		ret = ad5421_पढ़ो(indio_dev, AD5421_REG_DAC_DATA);
		अगर (ret < 0)
			वापस ret;
		*val = ret;
		अवरोध;
	हाल IIO_TEMP:
		*val = 140000;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस IIO_VAL_INT;
पूर्ण

अटल स्थिर काष्ठा iio_info ad5421_info = अणु
	.पढ़ो_raw =		ad5421_पढ़ो_raw,
	.ग_लिखो_raw =		ad5421_ग_लिखो_raw,
	.पढ़ो_event_config =	ad5421_पढ़ो_event_config,
	.ग_लिखो_event_config =	ad5421_ग_लिखो_event_config,
	.पढ़ो_event_value =	ad5421_पढ़ो_event_value,
पूर्ण;

अटल पूर्णांक ad5421_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ad5421_platक्रमm_data *pdata = dev_get_platdata(&spi->dev);
	काष्ठा iio_dev *indio_dev;
	काष्ठा ad5421_state *st;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (indio_dev == शून्य) अणु
		dev_err(&spi->dev, "Failed to allocate iio device\n");
		वापस  -ENOMEM;
	पूर्ण

	st = iio_priv(indio_dev);
	spi_set_drvdata(spi, indio_dev);

	st->spi = spi;

	indio_dev->name = "ad5421";
	indio_dev->info = &ad5421_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = ad5421_channels;
	indio_dev->num_channels = ARRAY_SIZE(ad5421_channels);

	mutex_init(&st->lock);

	st->ctrl = AD5421_CTRL_WATCHDOG_DISABLE |
			AD5421_CTRL_AUTO_FAULT_READBACK;

	अगर (pdata) अणु
		st->current_range = pdata->current_range;
		अगर (pdata->बाह्यal_vref)
			st->ctrl |= AD5421_CTRL_PWR_DOWN_INT_VREF;
	पूर्ण अन्यथा अणु
		st->current_range = AD5421_CURRENT_RANGE_4mA_20mA;
	पूर्ण

	/* ग_लिखो initial ctrl रेजिस्टर value */
	ad5421_update_ctrl(indio_dev, 0, 0);

	अगर (spi->irq) अणु
		ret = devm_request_thपढ़ोed_irq(&spi->dev, spi->irq,
					   शून्य,
					   ad5421_fault_handler,
					   IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
					   "ad5421 fault",
					   indio_dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(&spi->dev, indio_dev);
पूर्ण

अटल काष्ठा spi_driver ad5421_driver = अणु
	.driver = अणु
		   .name = "ad5421",
	पूर्ण,
	.probe = ad5421_probe,
पूर्ण;
module_spi_driver(ad5421_driver);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("Analog Devices AD5421 DAC");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("spi:ad5421");
