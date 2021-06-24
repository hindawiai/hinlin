<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * opt3001.c - Texas Instruments OPT3001 Light Sensor
 *
 * Copyright (C) 2014 Texas Instruments Incorporated - https://www.ti.com
 *
 * Author: Andreas Dannenberg <dannenberg@ti.com>
 * Based on previous work from: Felipe Balbi <balbi@ti.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#समावेश <linux/iio/events.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#घोषणा OPT3001_RESULT		0x00
#घोषणा OPT3001_CONFIGURATION	0x01
#घोषणा OPT3001_LOW_LIMIT	0x02
#घोषणा OPT3001_HIGH_LIMIT	0x03
#घोषणा OPT3001_MANUFACTURER_ID	0x7e
#घोषणा OPT3001_DEVICE_ID	0x7f

#घोषणा OPT3001_CONFIGURATION_RN_MASK	(0xf << 12)
#घोषणा OPT3001_CONFIGURATION_RN_AUTO	(0xc << 12)

#घोषणा OPT3001_CONFIGURATION_CT	BIT(11)

#घोषणा OPT3001_CONFIGURATION_M_MASK	(3 << 9)
#घोषणा OPT3001_CONFIGURATION_M_SHUTDOWN (0 << 9)
#घोषणा OPT3001_CONFIGURATION_M_SINGLE	(1 << 9)
#घोषणा OPT3001_CONFIGURATION_M_CONTINUOUS (2 << 9) /* also 3 << 9 */

#घोषणा OPT3001_CONFIGURATION_OVF	BIT(8)
#घोषणा OPT3001_CONFIGURATION_CRF	BIT(7)
#घोषणा OPT3001_CONFIGURATION_FH	BIT(6)
#घोषणा OPT3001_CONFIGURATION_FL	BIT(5)
#घोषणा OPT3001_CONFIGURATION_L		BIT(4)
#घोषणा OPT3001_CONFIGURATION_POL	BIT(3)
#घोषणा OPT3001_CONFIGURATION_ME	BIT(2)

#घोषणा OPT3001_CONFIGURATION_FC_MASK	(3 << 0)

/* The end-of-conversion enable is located in the low-limit रेजिस्टर */
#घोषणा OPT3001_LOW_LIMIT_EOC_ENABLE	0xc000

#घोषणा OPT3001_REG_EXPONENT(n)		((n) >> 12)
#घोषणा OPT3001_REG_MANTISSA(n)		((n) & 0xfff)

#घोषणा OPT3001_INT_TIME_LONG		800000
#घोषणा OPT3001_INT_TIME_SHORT		100000

/*
 * Time to रुको क्रम conversion result to be पढ़ोy. The device datasheet
 * sect. 6.5 states results are पढ़ोy after total पूर्णांकegration समय plus 3ms.
 * This results in worst-हाल max values of 113ms or 883ms, respectively.
 * Add some slack to be on the safe side.
 */
#घोषणा OPT3001_RESULT_READY_SHORT	150
#घोषणा OPT3001_RESULT_READY_LONG	1000

काष्ठा opt3001 अणु
	काष्ठा i2c_client	*client;
	काष्ठा device		*dev;

	काष्ठा mutex		lock;
	bool			ok_to_ignore_lock;
	bool			result_पढ़ोy;
	रुको_queue_head_t	result_पढ़ोy_queue;
	u16			result;

	u32			पूर्णांक_समय;
	u32			mode;

	u16			high_thresh_mantissa;
	u16			low_thresh_mantissa;

	u8			high_thresh_exp;
	u8			low_thresh_exp;

	bool			use_irq;
पूर्ण;

काष्ठा opt3001_scale अणु
	पूर्णांक	val;
	पूर्णांक	val2;
पूर्ण;

अटल स्थिर काष्ठा opt3001_scale opt3001_scales[] = अणु
	अणु
		.val = 40,
		.val2 = 950000,
	पूर्ण,
	अणु
		.val = 81,
		.val2 = 900000,
	पूर्ण,
	अणु
		.val = 163,
		.val2 = 800000,
	पूर्ण,
	अणु
		.val = 327,
		.val2 = 600000,
	पूर्ण,
	अणु
		.val = 655,
		.val2 = 200000,
	पूर्ण,
	अणु
		.val = 1310,
		.val2 = 400000,
	पूर्ण,
	अणु
		.val = 2620,
		.val2 = 800000,
	पूर्ण,
	अणु
		.val = 5241,
		.val2 = 600000,
	पूर्ण,
	अणु
		.val = 10483,
		.val2 = 200000,
	पूर्ण,
	अणु
		.val = 20966,
		.val2 = 400000,
	पूर्ण,
	अणु
		.val = 83865,
		.val2 = 600000,
	पूर्ण,
पूर्ण;

अटल पूर्णांक opt3001_find_scale(स्थिर काष्ठा opt3001 *opt, पूर्णांक val,
		पूर्णांक val2, u8 *exponent)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(opt3001_scales); i++) अणु
		स्थिर काष्ठा opt3001_scale *scale = &opt3001_scales[i];

		/*
		 * Combine the पूर्णांकeger and micro parts क्रम comparison
		 * purposes. Use milli lux precision to aव्योम 32-bit पूर्णांकeger
		 * overflows.
		 */
		अगर ((val * 1000 + val2 / 1000) <=
				(scale->val * 1000 + scale->val2 / 1000)) अणु
			*exponent = i;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम opt3001_to_iio_ret(काष्ठा opt3001 *opt, u8 exponent,
		u16 mantissa, पूर्णांक *val, पूर्णांक *val2)
अणु
	पूर्णांक lux;

	lux = 10 * (mantissa << exponent);
	*val = lux / 1000;
	*val2 = (lux - (*val * 1000)) * 1000;
पूर्ण

अटल व्योम opt3001_set_mode(काष्ठा opt3001 *opt, u16 *reg, u16 mode)
अणु
	*reg &= ~OPT3001_CONFIGURATION_M_MASK;
	*reg |= mode;
	opt->mode = mode;
पूर्ण

अटल IIO_CONST_ATTR_INT_TIME_AVAIL("0.1 0.8");

अटल काष्ठा attribute *opt3001_attributes[] = अणु
	&iio_स्थिर_attr_पूर्णांकegration_समय_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group opt3001_attribute_group = अणु
	.attrs = opt3001_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_event_spec opt3001_event_spec[] = अणु
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_RISING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE) |
			BIT(IIO_EV_INFO_ENABLE),
	पूर्ण,
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_FALLING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE) |
			BIT(IIO_EV_INFO_ENABLE),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec opt3001_channels[] = अणु
	अणु
		.type = IIO_LIGHT,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED) |
				BIT(IIO_CHAN_INFO_INT_TIME),
		.event_spec = opt3001_event_spec,
		.num_event_specs = ARRAY_SIZE(opt3001_event_spec),
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(1),
पूर्ण;

अटल पूर्णांक opt3001_get_lux(काष्ठा opt3001 *opt, पूर्णांक *val, पूर्णांक *val2)
अणु
	पूर्णांक ret;
	u16 mantissa;
	u16 reg;
	u8 exponent;
	u16 value;
	दीर्घ समयout;

	अगर (opt->use_irq) अणु
		/*
		 * Enable the end-of-conversion पूर्णांकerrupt mechanism. Note that
		 * करोing so will overग_लिखो the low-level limit value however we
		 * will restore this value later on.
		 */
		ret = i2c_smbus_ग_लिखो_word_swapped(opt->client,
					OPT3001_LOW_LIMIT,
					OPT3001_LOW_LIMIT_EOC_ENABLE);
		अगर (ret < 0) अणु
			dev_err(opt->dev, "failed to write register %02x\n",
					OPT3001_LOW_LIMIT);
			वापस ret;
		पूर्ण

		/* Allow IRQ to access the device despite lock being set */
		opt->ok_to_ignore_lock = true;
	पूर्ण

	/* Reset data-पढ़ोy indicator flag */
	opt->result_पढ़ोy = false;

	/* Configure क्रम single-conversion mode and start a new conversion */
	ret = i2c_smbus_पढ़ो_word_swapped(opt->client, OPT3001_CONFIGURATION);
	अगर (ret < 0) अणु
		dev_err(opt->dev, "failed to read register %02x\n",
				OPT3001_CONFIGURATION);
		जाओ err;
	पूर्ण

	reg = ret;
	opt3001_set_mode(opt, &reg, OPT3001_CONFIGURATION_M_SINGLE);

	ret = i2c_smbus_ग_लिखो_word_swapped(opt->client, OPT3001_CONFIGURATION,
			reg);
	अगर (ret < 0) अणु
		dev_err(opt->dev, "failed to write register %02x\n",
				OPT3001_CONFIGURATION);
		जाओ err;
	पूर्ण

	अगर (opt->use_irq) अणु
		/* Wait क्रम the IRQ to indicate the conversion is complete */
		ret = रुको_event_समयout(opt->result_पढ़ोy_queue,
				opt->result_पढ़ोy,
				msecs_to_jअगरfies(OPT3001_RESULT_READY_LONG));
	पूर्ण अन्यथा अणु
		/* Sleep क्रम result पढ़ोy समय */
		समयout = (opt->पूर्णांक_समय == OPT3001_INT_TIME_SHORT) ?
			OPT3001_RESULT_READY_SHORT : OPT3001_RESULT_READY_LONG;
		msleep(समयout);

		/* Check result पढ़ोy flag */
		ret = i2c_smbus_पढ़ो_word_swapped(opt->client,
						  OPT3001_CONFIGURATION);
		अगर (ret < 0) अणु
			dev_err(opt->dev, "failed to read register %02x\n",
				OPT3001_CONFIGURATION);
			जाओ err;
		पूर्ण

		अगर (!(ret & OPT3001_CONFIGURATION_CRF)) अणु
			ret = -ETIMEDOUT;
			जाओ err;
		पूर्ण

		/* Obtain value */
		ret = i2c_smbus_पढ़ो_word_swapped(opt->client, OPT3001_RESULT);
		अगर (ret < 0) अणु
			dev_err(opt->dev, "failed to read register %02x\n",
				OPT3001_RESULT);
			जाओ err;
		पूर्ण
		opt->result = ret;
		opt->result_पढ़ोy = true;
	पूर्ण

err:
	अगर (opt->use_irq)
		/* Disallow IRQ to access the device जबतक lock is active */
		opt->ok_to_ignore_lock = false;

	अगर (ret == 0)
		वापस -ETIMEDOUT;
	अन्यथा अगर (ret < 0)
		वापस ret;

	अगर (opt->use_irq) अणु
		/*
		 * Disable the end-of-conversion पूर्णांकerrupt mechanism by
		 * restoring the low-level limit value (clearing
		 * OPT3001_LOW_LIMIT_EOC_ENABLE). Note that selectively clearing
		 * those enable bits would affect the actual limit value due to
		 * bit-overlap and thereक्रमe can't be करोne.
		 */
		value = (opt->low_thresh_exp << 12) | opt->low_thresh_mantissa;
		ret = i2c_smbus_ग_लिखो_word_swapped(opt->client,
						   OPT3001_LOW_LIMIT,
						   value);
		अगर (ret < 0) अणु
			dev_err(opt->dev, "failed to write register %02x\n",
					OPT3001_LOW_LIMIT);
			वापस ret;
		पूर्ण
	पूर्ण

	exponent = OPT3001_REG_EXPONENT(opt->result);
	mantissa = OPT3001_REG_MANTISSA(opt->result);

	opt3001_to_iio_ret(opt, exponent, mantissa, val, val2);

	वापस IIO_VAL_INT_PLUS_MICRO;
पूर्ण

अटल पूर्णांक opt3001_get_पूर्णांक_समय(काष्ठा opt3001 *opt, पूर्णांक *val, पूर्णांक *val2)
अणु
	*val = 0;
	*val2 = opt->पूर्णांक_समय;

	वापस IIO_VAL_INT_PLUS_MICRO;
पूर्ण

अटल पूर्णांक opt3001_set_पूर्णांक_समय(काष्ठा opt3001 *opt, पूर्णांक समय)
अणु
	पूर्णांक ret;
	u16 reg;

	ret = i2c_smbus_पढ़ो_word_swapped(opt->client, OPT3001_CONFIGURATION);
	अगर (ret < 0) अणु
		dev_err(opt->dev, "failed to read register %02x\n",
				OPT3001_CONFIGURATION);
		वापस ret;
	पूर्ण

	reg = ret;

	चयन (समय) अणु
	हाल OPT3001_INT_TIME_SHORT:
		reg &= ~OPT3001_CONFIGURATION_CT;
		opt->पूर्णांक_समय = OPT3001_INT_TIME_SHORT;
		अवरोध;
	हाल OPT3001_INT_TIME_LONG:
		reg |= OPT3001_CONFIGURATION_CT;
		opt->पूर्णांक_समय = OPT3001_INT_TIME_LONG;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस i2c_smbus_ग_लिखो_word_swapped(opt->client, OPT3001_CONFIGURATION,
			reg);
पूर्ण

अटल पूर्णांक opt3001_पढ़ो_raw(काष्ठा iio_dev *iio,
		काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val, पूर्णांक *val2,
		दीर्घ mask)
अणु
	काष्ठा opt3001 *opt = iio_priv(iio);
	पूर्णांक ret;

	अगर (opt->mode == OPT3001_CONFIGURATION_M_CONTINUOUS)
		वापस -EBUSY;

	अगर (chan->type != IIO_LIGHT)
		वापस -EINVAL;

	mutex_lock(&opt->lock);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_PROCESSED:
		ret = opt3001_get_lux(opt, val, val2);
		अवरोध;
	हाल IIO_CHAN_INFO_INT_TIME:
		ret = opt3001_get_पूर्णांक_समय(opt, val, val2);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	mutex_unlock(&opt->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक opt3001_ग_लिखो_raw(काष्ठा iio_dev *iio,
		काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val, पूर्णांक val2,
		दीर्घ mask)
अणु
	काष्ठा opt3001 *opt = iio_priv(iio);
	पूर्णांक ret;

	अगर (opt->mode == OPT3001_CONFIGURATION_M_CONTINUOUS)
		वापस -EBUSY;

	अगर (chan->type != IIO_LIGHT)
		वापस -EINVAL;

	अगर (mask != IIO_CHAN_INFO_INT_TIME)
		वापस -EINVAL;

	अगर (val != 0)
		वापस -EINVAL;

	mutex_lock(&opt->lock);
	ret = opt3001_set_पूर्णांक_समय(opt, val2);
	mutex_unlock(&opt->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक opt3001_पढ़ो_event_value(काष्ठा iio_dev *iio,
		स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
		क्रमागत iio_event_direction dir, क्रमागत iio_event_info info,
		पूर्णांक *val, पूर्णांक *val2)
अणु
	काष्ठा opt3001 *opt = iio_priv(iio);
	पूर्णांक ret = IIO_VAL_INT_PLUS_MICRO;

	mutex_lock(&opt->lock);

	चयन (dir) अणु
	हाल IIO_EV_सूची_RISING:
		opt3001_to_iio_ret(opt, opt->high_thresh_exp,
				opt->high_thresh_mantissa, val, val2);
		अवरोध;
	हाल IIO_EV_सूची_FALLING:
		opt3001_to_iio_ret(opt, opt->low_thresh_exp,
				opt->low_thresh_mantissa, val, val2);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	mutex_unlock(&opt->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक opt3001_ग_लिखो_event_value(काष्ठा iio_dev *iio,
		स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
		क्रमागत iio_event_direction dir, क्रमागत iio_event_info info,
		पूर्णांक val, पूर्णांक val2)
अणु
	काष्ठा opt3001 *opt = iio_priv(iio);
	पूर्णांक ret;

	u16 mantissa;
	u16 value;
	u16 reg;

	u8 exponent;

	अगर (val < 0)
		वापस -EINVAL;

	mutex_lock(&opt->lock);

	ret = opt3001_find_scale(opt, val, val2, &exponent);
	अगर (ret < 0) अणु
		dev_err(opt->dev, "can't find scale for %d.%06u\n", val, val2);
		जाओ err;
	पूर्ण

	mantissa = (((val * 1000) + (val2 / 1000)) / 10) >> exponent;
	value = (exponent << 12) | mantissa;

	चयन (dir) अणु
	हाल IIO_EV_सूची_RISING:
		reg = OPT3001_HIGH_LIMIT;
		opt->high_thresh_mantissa = mantissa;
		opt->high_thresh_exp = exponent;
		अवरोध;
	हाल IIO_EV_सूची_FALLING:
		reg = OPT3001_LOW_LIMIT;
		opt->low_thresh_mantissa = mantissa;
		opt->low_thresh_exp = exponent;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	ret = i2c_smbus_ग_लिखो_word_swapped(opt->client, reg, value);
	अगर (ret < 0) अणु
		dev_err(opt->dev, "failed to write register %02x\n", reg);
		जाओ err;
	पूर्ण

err:
	mutex_unlock(&opt->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक opt3001_पढ़ो_event_config(काष्ठा iio_dev *iio,
		स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
		क्रमागत iio_event_direction dir)
अणु
	काष्ठा opt3001 *opt = iio_priv(iio);

	वापस opt->mode == OPT3001_CONFIGURATION_M_CONTINUOUS;
पूर्ण

अटल पूर्णांक opt3001_ग_लिखो_event_config(काष्ठा iio_dev *iio,
		स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
		क्रमागत iio_event_direction dir, पूर्णांक state)
अणु
	काष्ठा opt3001 *opt = iio_priv(iio);
	पूर्णांक ret;
	u16 mode;
	u16 reg;

	अगर (state && opt->mode == OPT3001_CONFIGURATION_M_CONTINUOUS)
		वापस 0;

	अगर (!state && opt->mode == OPT3001_CONFIGURATION_M_SHUTDOWN)
		वापस 0;

	mutex_lock(&opt->lock);

	mode = state ? OPT3001_CONFIGURATION_M_CONTINUOUS
		: OPT3001_CONFIGURATION_M_SHUTDOWN;

	ret = i2c_smbus_पढ़ो_word_swapped(opt->client, OPT3001_CONFIGURATION);
	अगर (ret < 0) अणु
		dev_err(opt->dev, "failed to read register %02x\n",
				OPT3001_CONFIGURATION);
		जाओ err;
	पूर्ण

	reg = ret;
	opt3001_set_mode(opt, &reg, mode);

	ret = i2c_smbus_ग_लिखो_word_swapped(opt->client, OPT3001_CONFIGURATION,
			reg);
	अगर (ret < 0) अणु
		dev_err(opt->dev, "failed to write register %02x\n",
				OPT3001_CONFIGURATION);
		जाओ err;
	पूर्ण

err:
	mutex_unlock(&opt->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info opt3001_info = अणु
	.attrs = &opt3001_attribute_group,
	.पढ़ो_raw = opt3001_पढ़ो_raw,
	.ग_लिखो_raw = opt3001_ग_लिखो_raw,
	.पढ़ो_event_value = opt3001_पढ़ो_event_value,
	.ग_लिखो_event_value = opt3001_ग_लिखो_event_value,
	.पढ़ो_event_config = opt3001_पढ़ो_event_config,
	.ग_लिखो_event_config = opt3001_ग_लिखो_event_config,
पूर्ण;

अटल पूर्णांक opt3001_पढ़ो_id(काष्ठा opt3001 *opt)
अणु
	अक्षर manufacturer[2];
	u16 device_id;
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_word_swapped(opt->client, OPT3001_MANUFACTURER_ID);
	अगर (ret < 0) अणु
		dev_err(opt->dev, "failed to read register %02x\n",
				OPT3001_MANUFACTURER_ID);
		वापस ret;
	पूर्ण

	manufacturer[0] = ret >> 8;
	manufacturer[1] = ret & 0xff;

	ret = i2c_smbus_पढ़ो_word_swapped(opt->client, OPT3001_DEVICE_ID);
	अगर (ret < 0) अणु
		dev_err(opt->dev, "failed to read register %02x\n",
				OPT3001_DEVICE_ID);
		वापस ret;
	पूर्ण

	device_id = ret;

	dev_info(opt->dev, "Found %c%c OPT%04x\n", manufacturer[0],
			manufacturer[1], device_id);

	वापस 0;
पूर्ण

अटल पूर्णांक opt3001_configure(काष्ठा opt3001 *opt)
अणु
	पूर्णांक ret;
	u16 reg;

	ret = i2c_smbus_पढ़ो_word_swapped(opt->client, OPT3001_CONFIGURATION);
	अगर (ret < 0) अणु
		dev_err(opt->dev, "failed to read register %02x\n",
				OPT3001_CONFIGURATION);
		वापस ret;
	पूर्ण

	reg = ret;

	/* Enable स्वतःmatic full-scale setting mode */
	reg &= ~OPT3001_CONFIGURATION_RN_MASK;
	reg |= OPT3001_CONFIGURATION_RN_AUTO;

	/* Reflect status of the device's पूर्णांकegration समय setting */
	अगर (reg & OPT3001_CONFIGURATION_CT)
		opt->पूर्णांक_समय = OPT3001_INT_TIME_LONG;
	अन्यथा
		opt->पूर्णांक_समय = OPT3001_INT_TIME_SHORT;

	/* Ensure device is in shutकरोwn initially */
	opt3001_set_mode(opt, &reg, OPT3001_CONFIGURATION_M_SHUTDOWN);

	/* Configure क्रम latched winकरोw-style comparison operation */
	reg |= OPT3001_CONFIGURATION_L;
	reg &= ~OPT3001_CONFIGURATION_POL;
	reg &= ~OPT3001_CONFIGURATION_ME;
	reg &= ~OPT3001_CONFIGURATION_FC_MASK;

	ret = i2c_smbus_ग_लिखो_word_swapped(opt->client, OPT3001_CONFIGURATION,
			reg);
	अगर (ret < 0) अणु
		dev_err(opt->dev, "failed to write register %02x\n",
				OPT3001_CONFIGURATION);
		वापस ret;
	पूर्ण

	ret = i2c_smbus_पढ़ो_word_swapped(opt->client, OPT3001_LOW_LIMIT);
	अगर (ret < 0) अणु
		dev_err(opt->dev, "failed to read register %02x\n",
				OPT3001_LOW_LIMIT);
		वापस ret;
	पूर्ण

	opt->low_thresh_mantissa = OPT3001_REG_MANTISSA(ret);
	opt->low_thresh_exp = OPT3001_REG_EXPONENT(ret);

	ret = i2c_smbus_पढ़ो_word_swapped(opt->client, OPT3001_HIGH_LIMIT);
	अगर (ret < 0) अणु
		dev_err(opt->dev, "failed to read register %02x\n",
				OPT3001_HIGH_LIMIT);
		वापस ret;
	पूर्ण

	opt->high_thresh_mantissa = OPT3001_REG_MANTISSA(ret);
	opt->high_thresh_exp = OPT3001_REG_EXPONENT(ret);

	वापस 0;
पूर्ण

अटल irqवापस_t opt3001_irq(पूर्णांक irq, व्योम *_iio)
अणु
	काष्ठा iio_dev *iio = _iio;
	काष्ठा opt3001 *opt = iio_priv(iio);
	पूर्णांक ret;
	bool wake_result_पढ़ोy_queue = false;

	अगर (!opt->ok_to_ignore_lock)
		mutex_lock(&opt->lock);

	ret = i2c_smbus_पढ़ो_word_swapped(opt->client, OPT3001_CONFIGURATION);
	अगर (ret < 0) अणु
		dev_err(opt->dev, "failed to read register %02x\n",
				OPT3001_CONFIGURATION);
		जाओ out;
	पूर्ण

	अगर ((ret & OPT3001_CONFIGURATION_M_MASK) ==
			OPT3001_CONFIGURATION_M_CONTINUOUS) अणु
		अगर (ret & OPT3001_CONFIGURATION_FH)
			iio_push_event(iio,
					IIO_UNMOD_EVENT_CODE(IIO_LIGHT, 0,
							IIO_EV_TYPE_THRESH,
							IIO_EV_सूची_RISING),
					iio_get_समय_ns(iio));
		अगर (ret & OPT3001_CONFIGURATION_FL)
			iio_push_event(iio,
					IIO_UNMOD_EVENT_CODE(IIO_LIGHT, 0,
							IIO_EV_TYPE_THRESH,
							IIO_EV_सूची_FALLING),
					iio_get_समय_ns(iio));
	पूर्ण अन्यथा अगर (ret & OPT3001_CONFIGURATION_CRF) अणु
		ret = i2c_smbus_पढ़ो_word_swapped(opt->client, OPT3001_RESULT);
		अगर (ret < 0) अणु
			dev_err(opt->dev, "failed to read register %02x\n",
					OPT3001_RESULT);
			जाओ out;
		पूर्ण
		opt->result = ret;
		opt->result_पढ़ोy = true;
		wake_result_पढ़ोy_queue = true;
	पूर्ण

out:
	अगर (!opt->ok_to_ignore_lock)
		mutex_unlock(&opt->lock);

	अगर (wake_result_पढ़ोy_queue)
		wake_up(&opt->result_पढ़ोy_queue);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक opt3001_probe(काष्ठा i2c_client *client,
		स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;

	काष्ठा iio_dev *iio;
	काष्ठा opt3001 *opt;
	पूर्णांक irq = client->irq;
	पूर्णांक ret;

	iio = devm_iio_device_alloc(dev, माप(*opt));
	अगर (!iio)
		वापस -ENOMEM;

	opt = iio_priv(iio);
	opt->client = client;
	opt->dev = dev;

	mutex_init(&opt->lock);
	init_रुकोqueue_head(&opt->result_पढ़ोy_queue);
	i2c_set_clientdata(client, iio);

	ret = opt3001_पढ़ो_id(opt);
	अगर (ret)
		वापस ret;

	ret = opt3001_configure(opt);
	अगर (ret)
		वापस ret;

	iio->name = client->name;
	iio->channels = opt3001_channels;
	iio->num_channels = ARRAY_SIZE(opt3001_channels);
	iio->modes = INDIO_सूचीECT_MODE;
	iio->info = &opt3001_info;

	ret = devm_iio_device_रेजिस्टर(dev, iio);
	अगर (ret) अणु
		dev_err(dev, "failed to register IIO device\n");
		वापस ret;
	पूर्ण

	/* Make use of INT pin only अगर valid IRQ no. is given */
	अगर (irq > 0) अणु
		ret = request_thपढ़ोed_irq(irq, शून्य, opt3001_irq,
				IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				"opt3001", iio);
		अगर (ret) अणु
			dev_err(dev, "failed to request IRQ #%d\n", irq);
			वापस ret;
		पूर्ण
		opt->use_irq = true;
	पूर्ण अन्यथा अणु
		dev_dbg(opt->dev, "enabling interrupt-less operation\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक opt3001_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *iio = i2c_get_clientdata(client);
	काष्ठा opt3001 *opt = iio_priv(iio);
	पूर्णांक ret;
	u16 reg;

	अगर (opt->use_irq)
		मुक्त_irq(client->irq, iio);

	ret = i2c_smbus_पढ़ो_word_swapped(opt->client, OPT3001_CONFIGURATION);
	अगर (ret < 0) अणु
		dev_err(opt->dev, "failed to read register %02x\n",
				OPT3001_CONFIGURATION);
		वापस ret;
	पूर्ण

	reg = ret;
	opt3001_set_mode(opt, &reg, OPT3001_CONFIGURATION_M_SHUTDOWN);

	ret = i2c_smbus_ग_लिखो_word_swapped(opt->client, OPT3001_CONFIGURATION,
			reg);
	अगर (ret < 0) अणु
		dev_err(opt->dev, "failed to write register %02x\n",
				OPT3001_CONFIGURATION);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id opt3001_id[] = अणु
	अणु "opt3001", 0 पूर्ण,
	अणु पूर्ण /* Terminating Entry */
पूर्ण;
MODULE_DEVICE_TABLE(i2c, opt3001_id);

अटल स्थिर काष्ठा of_device_id opt3001_of_match[] = अणु
	अणु .compatible = "ti,opt3001" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, opt3001_of_match);

अटल काष्ठा i2c_driver opt3001_driver = अणु
	.probe = opt3001_probe,
	.हटाओ = opt3001_हटाओ,
	.id_table = opt3001_id,

	.driver = अणु
		.name = "opt3001",
		.of_match_table = opt3001_of_match,
	पूर्ण,
पूर्ण;

module_i2c_driver(opt3001_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Andreas Dannenberg <dannenberg@ti.com>");
MODULE_DESCRIPTION("Texas Instruments OPT3001 Light Sensor Driver");
