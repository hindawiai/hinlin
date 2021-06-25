<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Sensirion SCD30 carbon dioxide sensor core driver
 *
 * Copyright (c) 2020 Tomasz Duszynski <tomasz.duszynski@octakon.com>
 */
#समावेश <linux/bits.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/माला.स>
#समावेश <linux/sysfs.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>

#समावेश "scd30.h"

#घोषणा SCD30_PRESSURE_COMP_MIN_MBAR 700
#घोषणा SCD30_PRESSURE_COMP_MAX_MBAR 1400
#घोषणा SCD30_PRESSURE_COMP_DEFAULT 1013
#घोषणा SCD30_MEAS_INTERVAL_MIN_S 2
#घोषणा SCD30_MEAS_INTERVAL_MAX_S 1800
#घोषणा SCD30_MEAS_INTERVAL_DEFAULT SCD30_MEAS_INTERVAL_MIN_S
#घोषणा SCD30_FRC_MIN_PPM 400
#घोषणा SCD30_FRC_MAX_PPM 2000
#घोषणा SCD30_TEMP_OFFSET_MAX 655360
#घोषणा SCD30_EXTRA_TIMEOUT_PER_S 250

क्रमागत अणु
	SCD30_CONC,
	SCD30_TEMP,
	SCD30_HR,
पूर्ण;

अटल पूर्णांक scd30_command_ग_लिखो(काष्ठा scd30_state *state, क्रमागत scd30_cmd cmd, u16 arg)
अणु
	वापस state->command(state, cmd, arg, शून्य, 0);
पूर्ण

अटल पूर्णांक scd30_command_पढ़ो(काष्ठा scd30_state *state, क्रमागत scd30_cmd cmd, u16 *val)
अणु
	__be16 पंचांगp;
	पूर्णांक ret;

	ret = state->command(state, cmd, 0, &पंचांगp, माप(पंचांगp));
	*val = be16_to_cpup(&पंचांगp);

	वापस ret;
पूर्ण

अटल पूर्णांक scd30_reset(काष्ठा scd30_state *state)
अणु
	पूर्णांक ret;
	u16 val;

	ret = scd30_command_ग_लिखो(state, CMD_RESET, 0);
	अगर (ret)
		वापस ret;

	/* sensor boots up within 2 secs */
	msleep(2000);
	/*
	 * Power-on-reset causes sensor to produce some glitch on i2c bus and
	 * some controllers end up in error state. Try to recover by placing
	 * any data on the bus.
	 */
	scd30_command_पढ़ो(state, CMD_MEAS_READY, &val);

	वापस 0;
पूर्ण

/* simplअगरied भग्न to fixed poपूर्णांक conversion with a scaling factor of 0.01 */
अटल पूर्णांक scd30_भग्न_to_fp(पूर्णांक भग्न32)
अणु
	पूर्णांक fraction, shअगरt,
	    mantissa = भग्न32 & GENMASK(22, 0),
	    sign = (भग्न32 & BIT(31)) ? -1 : 1,
	    exp = (भग्न32 & ~BIT(31)) >> 23;

	/* special हाल 0 */
	अगर (!exp && !mantissa)
		वापस 0;

	exp -= 127;
	अगर (exp < 0) अणु
		exp = -exp;
		/* वापस values ranging from 1 to 99 */
		वापस sign * ((((BIT(23) + mantissa) * 100) >> 23) >> exp);
	पूर्ण

	/* वापस values starting at 100 */
	shअगरt = 23 - exp;
	भग्न32 = BIT(exp) + (mantissa >> shअगरt);
	fraction = mantissa & GENMASK(shअगरt - 1, 0);

	वापस sign * (भग्न32 * 100 + ((fraction * 100) >> shअगरt));
पूर्ण

अटल पूर्णांक scd30_पढ़ो_meas(काष्ठा scd30_state *state)
अणु
	पूर्णांक i, ret;

	ret = state->command(state, CMD_READ_MEAS, 0, state->meas, माप(state->meas));
	अगर (ret)
		वापस ret;

	be32_to_cpu_array(state->meas, (__be32 *)state->meas, ARRAY_SIZE(state->meas));

	क्रम (i = 0; i < ARRAY_SIZE(state->meas); i++)
		state->meas[i] = scd30_भग्न_to_fp(state->meas[i]);

	/*
	 * co2 is left unprocessed जबतक temperature and humidity are scaled
	 * to milli deg C and milli percent respectively.
	 */
	state->meas[SCD30_TEMP] *= 10;
	state->meas[SCD30_HR] *= 10;

	वापस 0;
पूर्ण

अटल पूर्णांक scd30_रुको_meas_irq(काष्ठा scd30_state *state)
अणु
	पूर्णांक ret, समयout;

	reinit_completion(&state->meas_पढ़ोy);
	enable_irq(state->irq);
	समयout = msecs_to_jअगरfies(state->meas_पूर्णांकerval * (1000 + SCD30_EXTRA_TIMEOUT_PER_S));
	ret = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&state->meas_पढ़ोy, समयout);
	अगर (ret > 0)
		ret = 0;
	अन्यथा अगर (!ret)
		ret = -ETIMEDOUT;

	disable_irq(state->irq);

	वापस ret;
पूर्ण

अटल पूर्णांक scd30_रुको_meas_poll(काष्ठा scd30_state *state)
अणु
	पूर्णांक समयout = state->meas_पूर्णांकerval * SCD30_EXTRA_TIMEOUT_PER_S, tries = 5;

	करो अणु
		पूर्णांक ret;
		u16 val;

		ret = scd30_command_पढ़ो(state, CMD_MEAS_READY, &val);
		अगर (ret)
			वापस -EIO;

		/* new measurement available */
		अगर (val)
			अवरोध;

		msleep_पूर्णांकerruptible(समयout);
	पूर्ण जबतक (--tries);

	वापस tries ? 0 : -ETIMEDOUT;
पूर्ण

अटल पूर्णांक scd30_पढ़ो_poll(काष्ठा scd30_state *state)
अणु
	पूर्णांक ret;

	ret = scd30_रुको_meas_poll(state);
	अगर (ret)
		वापस ret;

	वापस scd30_पढ़ो_meas(state);
पूर्ण

अटल पूर्णांक scd30_पढ़ो(काष्ठा scd30_state *state)
अणु
	अगर (state->irq > 0)
		वापस scd30_रुको_meas_irq(state);

	वापस scd30_पढ़ो_poll(state);
पूर्ण

अटल पूर्णांक scd30_पढ़ो_raw(काष्ठा iio_dev *indio_dev, काष्ठा iio_chan_spec स्थिर *chan,
			  पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा scd30_state *state = iio_priv(indio_dev);
	पूर्णांक ret = -EINVAL;
	u16 पंचांगp;

	mutex_lock(&state->lock);
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
	हाल IIO_CHAN_INFO_PROCESSED:
		अगर (chan->output) अणु
			*val = state->pressure_comp;
			ret = IIO_VAL_INT;
			अवरोध;
		पूर्ण

		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			अवरोध;

		ret = scd30_पढ़ो(state);
		अगर (ret) अणु
			iio_device_release_direct_mode(indio_dev);
			अवरोध;
		पूर्ण

		*val = state->meas[chan->address];
		iio_device_release_direct_mode(indio_dev);
		ret = IIO_VAL_INT;
		अवरोध;
	हाल IIO_CHAN_INFO_SCALE:
		*val = 0;
		*val2 = 1;
		ret = IIO_VAL_INT_PLUS_MICRO;
		अवरोध;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		ret = scd30_command_पढ़ो(state, CMD_MEAS_INTERVAL, &पंचांगp);
		अगर (ret)
			अवरोध;

		*val = 0;
		*val2 = 1000000000 / पंचांगp;
		ret = IIO_VAL_INT_PLUS_न_अंकO;
		अवरोध;
	हाल IIO_CHAN_INFO_CALIBBIAS:
		ret = scd30_command_पढ़ो(state, CMD_TEMP_OFFSET, &पंचांगp);
		अगर (ret)
			अवरोध;

		*val = पंचांगp;
		ret = IIO_VAL_INT;
		अवरोध;
	पूर्ण
	mutex_unlock(&state->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक scd30_ग_लिखो_raw(काष्ठा iio_dev *indio_dev, काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा scd30_state *state = iio_priv(indio_dev);
	पूर्णांक ret = -EINVAL;

	mutex_lock(&state->lock);
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		अगर (val)
			अवरोध;

		val = 1000000000 / val2;
		अगर (val < SCD30_MEAS_INTERVAL_MIN_S || val > SCD30_MEAS_INTERVAL_MAX_S)
			अवरोध;

		ret = scd30_command_ग_लिखो(state, CMD_MEAS_INTERVAL, val);
		अगर (ret)
			अवरोध;

		state->meas_पूर्णांकerval = val;
		अवरोध;
	हाल IIO_CHAN_INFO_RAW:
		चयन (chan->type) अणु
		हाल IIO_PRESSURE:
			अगर (val < SCD30_PRESSURE_COMP_MIN_MBAR ||
			    val > SCD30_PRESSURE_COMP_MAX_MBAR)
				अवरोध;

			ret = scd30_command_ग_लिखो(state, CMD_START_MEAS, val);
			अगर (ret)
				अवरोध;

			state->pressure_comp = val;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_CALIBBIAS:
		अगर (val < 0 || val > SCD30_TEMP_OFFSET_MAX)
			अवरोध;
		/*
		 * Manufacturer करोes not explicitly specअगरy min/max sensible
		 * values hence check is omitted क्रम simplicity.
		 */
		ret = scd30_command_ग_लिखो(state, CMD_TEMP_OFFSET / 10, val);
	पूर्ण
	mutex_unlock(&state->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक scd30_ग_लिखो_raw_get_fmt(काष्ठा iio_dev *indio_dev, काष्ठा iio_chan_spec स्थिर *chan,
				   दीर्घ mask)
अणु
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		वापस IIO_VAL_INT_PLUS_न_अंकO;
	हाल IIO_CHAN_INFO_RAW:
	हाल IIO_CHAN_INFO_CALIBBIAS:
		वापस IIO_VAL_INT;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर पूर्णांक scd30_pressure_raw_available[] = अणु
	SCD30_PRESSURE_COMP_MIN_MBAR, 1, SCD30_PRESSURE_COMP_MAX_MBAR,
पूर्ण;

अटल स्थिर पूर्णांक scd30_temp_calibbias_available[] = अणु
	0, 10, SCD30_TEMP_OFFSET_MAX,
पूर्ण;

अटल पूर्णांक scd30_पढ़ो_avail(काष्ठा iio_dev *indio_dev, काष्ठा iio_chan_spec स्थिर *chan,
			    स्थिर पूर्णांक **vals, पूर्णांक *type, पूर्णांक *length, दीर्घ mask)
अणु
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		*vals = scd30_pressure_raw_available;
		*type = IIO_VAL_INT;

		वापस IIO_AVAIL_RANGE;
	हाल IIO_CHAN_INFO_CALIBBIAS:
		*vals = scd30_temp_calibbias_available;
		*type = IIO_VAL_INT;

		वापस IIO_AVAIL_RANGE;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार sampling_frequency_available_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
						 अक्षर *buf)
अणु
	पूर्णांक i = SCD30_MEAS_INTERVAL_MIN_S;
	sमाप_प्रकार len = 0;

	करो अणु
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "0.%09u ", 1000000000 / i);
		/*
		 * Not all values fit PAGE_SIZE buffer hence prपूर्णांक every 6th
		 * (each frequency dअगरfers by 6s in समय करोमुख्य from the
		 * adjacent). Unlisted but valid ones are still accepted.
		 */
		i += 6;
	पूर्ण जबतक (i <= SCD30_MEAS_INTERVAL_MAX_S);

	buf[len - 1] = '\n';

	वापस len;
पूर्ण

अटल sमाप_प्रकार calibration_स्वतः_enable_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
					    अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा scd30_state *state = iio_priv(indio_dev);
	पूर्णांक ret;
	u16 val;

	mutex_lock(&state->lock);
	ret = scd30_command_पढ़ो(state, CMD_ASC, &val);
	mutex_unlock(&state->lock);

	वापस ret ?: प्र_लिखो(buf, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार calibration_स्वतः_enable_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
					     स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा scd30_state *state = iio_priv(indio_dev);
	bool val;
	पूर्णांक ret;

	ret = kstrtobool(buf, &val);
	अगर (ret)
		वापस ret;

	mutex_lock(&state->lock);
	ret = scd30_command_ग_लिखो(state, CMD_ASC, val);
	mutex_unlock(&state->lock);

	वापस ret ?: len;
पूर्ण

अटल sमाप_प्रकार calibration_क्रमced_value_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
					     अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा scd30_state *state = iio_priv(indio_dev);
	पूर्णांक ret;
	u16 val;

	mutex_lock(&state->lock);
	ret = scd30_command_पढ़ो(state, CMD_FRC, &val);
	mutex_unlock(&state->lock);

	वापस ret ?: प्र_लिखो(buf, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार calibration_क्रमced_value_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
					      स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा scd30_state *state = iio_priv(indio_dev);
	पूर्णांक ret;
	u16 val;

	ret = kstrtou16(buf, 0, &val);
	अगर (ret)
		वापस ret;

	अगर (val < SCD30_FRC_MIN_PPM || val > SCD30_FRC_MAX_PPM)
		वापस -EINVAL;

	mutex_lock(&state->lock);
	ret = scd30_command_ग_लिखो(state, CMD_FRC, val);
	mutex_unlock(&state->lock);

	वापस ret ?: len;
पूर्ण

अटल IIO_DEVICE_ATTR_RO(sampling_frequency_available, 0);
अटल IIO_DEVICE_ATTR_RW(calibration_स्वतः_enable, 0);
अटल IIO_DEVICE_ATTR_RW(calibration_क्रमced_value, 0);

अटल काष्ठा attribute *scd30_attrs[] = अणु
	&iio_dev_attr_sampling_frequency_available.dev_attr.attr,
	&iio_dev_attr_calibration_स्वतः_enable.dev_attr.attr,
	&iio_dev_attr_calibration_क्रमced_value.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group scd30_attr_group = अणु
	.attrs = scd30_attrs,
पूर्ण;

अटल स्थिर काष्ठा iio_info scd30_info = अणु
	.attrs = &scd30_attr_group,
	.पढ़ो_raw = scd30_पढ़ो_raw,
	.ग_लिखो_raw = scd30_ग_लिखो_raw,
	.ग_लिखो_raw_get_fmt = scd30_ग_लिखो_raw_get_fmt,
	.पढ़ो_avail = scd30_पढ़ो_avail,
पूर्ण;

#घोषणा SCD30_CHAN_SCAN_TYPE(_sign, _realbits) .scan_type = अणु \
	.sign = _sign, \
	.realbits = _realbits, \
	.storagebits = 32, \
	.endianness = IIO_CPU, \
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec scd30_channels[] = अणु
	अणु
		/*
		 * this channel is special in a sense we are pretending that
		 * sensor is able to change measurement chamber pressure but in
		 * fact we're just setting pressure compensation value
		 */
		.type = IIO_PRESSURE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_separate_available = BIT(IIO_CHAN_INFO_RAW),
		.output = 1,
		.scan_index = -1,
	पूर्ण,
	अणु
		.type = IIO_CONCENTRATION,
		.channel2 = IIO_MOD_CO2,
		.address = SCD30_CONC,
		.scan_index = SCD30_CONC,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE),
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ),
		.modअगरied = 1,

		SCD30_CHAN_SCAN_TYPE('u', 20),
	पूर्ण,
	अणु
		.type = IIO_TEMP,
		.address = SCD30_TEMP,
		.scan_index = SCD30_TEMP,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED) |
				      BIT(IIO_CHAN_INFO_CALIBBIAS),
		.info_mask_separate_available = BIT(IIO_CHAN_INFO_CALIBBIAS),
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ),

		SCD30_CHAN_SCAN_TYPE('s', 18),
	पूर्ण,
	अणु
		.type = IIO_HUMIDITYRELATIVE,
		.address = SCD30_HR,
		.scan_index = SCD30_HR,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ),

		SCD30_CHAN_SCAN_TYPE('u', 17),
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(3),
पूर्ण;

पूर्णांक __maybe_unused scd30_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा scd30_state *state  = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = scd30_command_ग_लिखो(state, CMD_STOP_MEAS, 0);
	अगर (ret)
		वापस ret;

	वापस regulator_disable(state->vdd);
पूर्ण
EXPORT_SYMBOL(scd30_suspend);

पूर्णांक __maybe_unused scd30_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा scd30_state *state = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = regulator_enable(state->vdd);
	अगर (ret)
		वापस ret;

	वापस scd30_command_ग_लिखो(state, CMD_START_MEAS, state->pressure_comp);
पूर्ण
EXPORT_SYMBOL(scd30_resume);

अटल व्योम scd30_stop_meas(व्योम *data)
अणु
	काष्ठा scd30_state *state = data;

	scd30_command_ग_लिखो(state, CMD_STOP_MEAS, 0);
पूर्ण

अटल व्योम scd30_disable_regulator(व्योम *data)
अणु
	काष्ठा scd30_state *state = data;

	regulator_disable(state->vdd);
पूर्ण

अटल irqवापस_t scd30_irq_handler(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा iio_dev *indio_dev = priv;

	अगर (iio_buffer_enabled(indio_dev)) अणु
		iio_trigger_poll(indio_dev->trig);

		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t scd30_irq_thपढ़ो_handler(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा iio_dev *indio_dev = priv;
	काष्ठा scd30_state *state = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = scd30_पढ़ो_meas(state);
	अगर (ret)
		जाओ out;

	complete_all(&state->meas_पढ़ोy);
out:
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t scd30_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा scd30_state *state = iio_priv(indio_dev);
	काष्ठा अणु
		पूर्णांक data[SCD30_MEAS_COUNT];
		s64 ts __aligned(8);
	पूर्ण scan;
	पूर्णांक ret;

	mutex_lock(&state->lock);
	अगर (!iio_trigger_using_own(indio_dev))
		ret = scd30_पढ़ो_poll(state);
	अन्यथा
		ret = scd30_पढ़ो_meas(state);
	स_रखो(&scan, 0, माप(scan));
	स_नकल(scan.data, state->meas, माप(state->meas));
	mutex_unlock(&state->lock);
	अगर (ret)
		जाओ out;

	iio_push_to_buffers_with_बारtamp(indio_dev, &scan, iio_get_समय_ns(indio_dev));
out:
	iio_trigger_notअगरy_करोne(indio_dev->trig);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक scd30_set_trigger_state(काष्ठा iio_trigger *trig, bool state)
अणु
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	काष्ठा scd30_state *st = iio_priv(indio_dev);

	अगर (state)
		enable_irq(st->irq);
	अन्यथा
		disable_irq(st->irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops scd30_trigger_ops = अणु
	.set_trigger_state = scd30_set_trigger_state,
	.validate_device = iio_trigger_validate_own_device,
पूर्ण;

अटल पूर्णांक scd30_setup_trigger(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा scd30_state *state = iio_priv(indio_dev);
	काष्ठा device *dev = indio_dev->dev.parent;
	काष्ठा iio_trigger *trig;
	पूर्णांक ret;

	trig = devm_iio_trigger_alloc(dev, "%s-dev%d", indio_dev->name, indio_dev->id);
	अगर (!trig) अणु
		dev_err(dev, "failed to allocate trigger\n");
		वापस -ENOMEM;
	पूर्ण

	trig->ops = &scd30_trigger_ops;
	iio_trigger_set_drvdata(trig, indio_dev);

	ret = devm_iio_trigger_रेजिस्टर(dev, trig);
	अगर (ret)
		वापस ret;

	indio_dev->trig = iio_trigger_get(trig);

	/*
	 * Interrupt is enabled just beक्रमe taking a fresh measurement
	 * and disabled afterwards. This means we need to ensure it is not
	 * enabled here to keep calls to enable/disable balanced.
	 */
	ret = devm_request_thपढ़ोed_irq(dev, state->irq, scd30_irq_handler,
					scd30_irq_thपढ़ो_handler,
					IRQF_TRIGGER_HIGH | IRQF_ONESHOT |
					IRQF_NO_AUTOEN,
					indio_dev->name, indio_dev);
	अगर (ret)
		dev_err(dev, "failed to request irq\n");

	वापस ret;
पूर्ण

पूर्णांक scd30_probe(काष्ठा device *dev, पूर्णांक irq, स्थिर अक्षर *name, व्योम *priv,
		scd30_command_t command)
अणु
	अटल स्थिर अचिन्हित दीर्घ scd30_scan_masks[] = अणु 0x07, 0x00 पूर्ण;
	काष्ठा scd30_state *state;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;
	u16 val;

	indio_dev = devm_iio_device_alloc(dev, माप(*state));
	अगर (!indio_dev)
		वापस -ENOMEM;

	state = iio_priv(indio_dev);
	state->dev = dev;
	state->priv = priv;
	state->irq = irq;
	state->pressure_comp = SCD30_PRESSURE_COMP_DEFAULT;
	state->meas_पूर्णांकerval = SCD30_MEAS_INTERVAL_DEFAULT;
	state->command = command;
	mutex_init(&state->lock);
	init_completion(&state->meas_पढ़ोy);

	dev_set_drvdata(dev, indio_dev);

	indio_dev->info = &scd30_info;
	indio_dev->name = name;
	indio_dev->channels = scd30_channels;
	indio_dev->num_channels = ARRAY_SIZE(scd30_channels);
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->available_scan_masks = scd30_scan_masks;

	state->vdd = devm_regulator_get(dev, "vdd");
	अगर (IS_ERR(state->vdd))
		वापस dev_err_probe(dev, PTR_ERR(state->vdd), "failed to get regulator\n");

	ret = regulator_enable(state->vdd);
	अगर (ret)
		वापस ret;

	ret = devm_add_action_or_reset(dev, scd30_disable_regulator, state);
	अगर (ret)
		वापस ret;

	ret = scd30_reset(state);
	अगर (ret) अणु
		dev_err(dev, "failed to reset device: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (state->irq > 0) अणु
		ret = scd30_setup_trigger(indio_dev);
		अगर (ret) अणु
			dev_err(dev, "failed to setup trigger: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = devm_iio_triggered_buffer_setup(dev, indio_dev, शून्य, scd30_trigger_handler, शून्य);
	अगर (ret)
		वापस ret;

	ret = scd30_command_पढ़ो(state, CMD_FW_VERSION, &val);
	अगर (ret) अणु
		dev_err(dev, "failed to read firmware version: %d\n", ret);
		वापस ret;
	पूर्ण
	dev_info(dev, "firmware version: %d.%d\n", val >> 8, (अक्षर)val);

	ret = scd30_command_ग_लिखो(state, CMD_MEAS_INTERVAL, state->meas_पूर्णांकerval);
	अगर (ret) अणु
		dev_err(dev, "failed to set measurement interval: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = scd30_command_ग_लिखो(state, CMD_START_MEAS, state->pressure_comp);
	अगर (ret) अणु
		dev_err(dev, "failed to start measurement: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(dev, scd30_stop_meas, state);
	अगर (ret)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(dev, indio_dev);
पूर्ण
EXPORT_SYMBOL(scd30_probe);

MODULE_AUTHOR("Tomasz Duszynski <tomasz.duszynski@octakon.com>");
MODULE_DESCRIPTION("Sensirion SCD30 carbon dioxide sensor core driver");
MODULE_LICENSE("GPL v2");
