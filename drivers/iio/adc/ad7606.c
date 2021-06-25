<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * AD7606 SPI ADC driver
 *
 * Copyright 2011 Analog Devices Inc.
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/util_macros.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/trigger_consumer.h>

#समावेश "ad7606.h"

/*
 * Scales are computed as 5000/32768 and 10000/32768 respectively,
 * so that when applied to the raw values they provide mV values
 */
अटल स्थिर अचिन्हित पूर्णांक ad7606_scale_avail[2] = अणु
	152588, 305176
पूर्ण;


अटल स्थिर अचिन्हित पूर्णांक ad7616_sw_scale_avail[3] = अणु
	76293, 152588, 305176
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ad7606_oversampling_avail[7] = अणु
	1, 2, 4, 8, 16, 32, 64,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ad7616_oversampling_avail[8] = अणु
	1, 2, 4, 8, 16, 32, 64, 128,
पूर्ण;

अटल पूर्णांक ad7606_reset(काष्ठा ad7606_state *st)
अणु
	अगर (st->gpio_reset) अणु
		gpiod_set_value(st->gpio_reset, 1);
		ndelay(100); /* t_reset >= 100ns */
		gpiod_set_value(st->gpio_reset, 0);
		वापस 0;
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक ad7606_reg_access(काष्ठा iio_dev *indio_dev,
			     अचिन्हित पूर्णांक reg,
			     अचिन्हित पूर्णांक ग_लिखोval,
			     अचिन्हित पूर्णांक *पढ़ोval)
अणु
	काष्ठा ad7606_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&st->lock);
	अगर (पढ़ोval) अणु
		ret = st->bops->reg_पढ़ो(st, reg);
		अगर (ret < 0)
			जाओ err_unlock;
		*पढ़ोval = ret;
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = st->bops->reg_ग_लिखो(st, reg, ग_लिखोval);
	पूर्ण
err_unlock:
	mutex_unlock(&st->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ad7606_पढ़ो_samples(काष्ठा ad7606_state *st)
अणु
	अचिन्हित पूर्णांक num = st->chip_info->num_channels - 1;
	u16 *data = st->data;
	पूर्णांक ret;

	/*
	 * The frstdata संकेत is set to high जबतक and after पढ़ोing the sample
	 * of the first channel and low क्रम all other channels. This can be used
	 * to check that the incoming data is correctly aligned. During normal
	 * operation the data should never become unaligned, but some glitch or
	 * electroअटल disअक्षरge might cause an extra पढ़ो or घड़ी cycle.
	 * Monitoring the frstdata संकेत allows to recover from such failure
	 * situations.
	 */

	अगर (st->gpio_frstdata) अणु
		ret = st->bops->पढ़ो_block(st->dev, 1, data);
		अगर (ret)
			वापस ret;

		अगर (!gpiod_get_value(st->gpio_frstdata)) अणु
			ad7606_reset(st);
			वापस -EIO;
		पूर्ण

		data++;
		num--;
	पूर्ण

	वापस st->bops->पढ़ो_block(st->dev, num, data);
पूर्ण

अटल irqवापस_t ad7606_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा ad7606_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&st->lock);

	ret = ad7606_पढ़ो_samples(st);
	अगर (ret == 0)
		iio_push_to_buffers_with_बारtamp(indio_dev, st->data,
						   iio_get_समय_ns(indio_dev));

	iio_trigger_notअगरy_करोne(indio_dev->trig);
	/* The rising edge of the CONVST संकेत starts a new conversion. */
	gpiod_set_value(st->gpio_convst, 1);

	mutex_unlock(&st->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ad7606_scan_direct(काष्ठा iio_dev *indio_dev, अचिन्हित पूर्णांक ch)
अणु
	काष्ठा ad7606_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	gpiod_set_value(st->gpio_convst, 1);
	ret = रुको_क्रम_completion_समयout(&st->completion,
					  msecs_to_jअगरfies(1000));
	अगर (!ret) अणु
		ret = -ETIMEDOUT;
		जाओ error_ret;
	पूर्ण

	ret = ad7606_पढ़ो_samples(st);
	अगर (ret == 0)
		ret = st->data[ch];

error_ret:
	gpiod_set_value(st->gpio_convst, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक ad7606_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val,
			   पूर्णांक *val2,
			   दीर्घ m)
अणु
	पूर्णांक ret, ch = 0;
	काष्ठा ad7606_state *st = iio_priv(indio_dev);

	चयन (m) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;

		ret = ad7606_scan_direct(indio_dev, chan->address);
		iio_device_release_direct_mode(indio_dev);

		अगर (ret < 0)
			वापस ret;
		*val = (लघु)ret;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		अगर (st->sw_mode_en)
			ch = chan->address;
		*val = 0;
		*val2 = st->scale_avail[st->range[ch]];
		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		*val = st->oversampling;
		वापस IIO_VAL_INT;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार ad7606_show_avail(अक्षर *buf, स्थिर अचिन्हित पूर्णांक *vals,
				 अचिन्हित पूर्णांक n, bool micros)
अणु
	माप_प्रकार len = 0;
	पूर्णांक i;

	क्रम (i = 0; i < n; i++) अणु
		len += scnम_लिखो(buf + len, PAGE_SIZE - len,
			micros ? "0.%06u " : "%u ", vals[i]);
	पूर्ण
	buf[len - 1] = '\n';

	वापस len;
पूर्ण

अटल sमाप_प्रकार in_voltage_scale_available_show(काष्ठा device *dev,
					       काष्ठा device_attribute *attr,
					       अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ad7606_state *st = iio_priv(indio_dev);

	वापस ad7606_show_avail(buf, st->scale_avail, st->num_scales, true);
पूर्ण

अटल IIO_DEVICE_ATTR_RO(in_voltage_scale_available, 0);

अटल पूर्णांक ad7606_ग_लिखो_scale_hw(काष्ठा iio_dev *indio_dev, पूर्णांक ch, पूर्णांक val)
अणु
	काष्ठा ad7606_state *st = iio_priv(indio_dev);

	gpiod_set_value(st->gpio_range, val);

	वापस 0;
पूर्ण

अटल पूर्णांक ad7606_ग_लिखो_os_hw(काष्ठा iio_dev *indio_dev, पूर्णांक val)
अणु
	काष्ठा ad7606_state *st = iio_priv(indio_dev);
	DECLARE_BITMAP(values, 3);

	values[0] = val;

	gpiod_set_array_value(ARRAY_SIZE(values), st->gpio_os->desc,
			      st->gpio_os->info, values);

	/* AD7616 requires a reset to update value */
	अगर (st->chip_info->os_req_reset)
		ad7606_reset(st);

	वापस 0;
पूर्ण

अटल पूर्णांक ad7606_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक val,
			    पूर्णांक val2,
			    दीर्घ mask)
अणु
	काष्ठा ad7606_state *st = iio_priv(indio_dev);
	पूर्णांक i, ret, ch = 0;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		mutex_lock(&st->lock);
		i = find_बंदst(val2, st->scale_avail, st->num_scales);
		अगर (st->sw_mode_en)
			ch = chan->address;
		ret = st->ग_लिखो_scale(indio_dev, ch, i);
		अगर (ret < 0) अणु
			mutex_unlock(&st->lock);
			वापस ret;
		पूर्ण
		st->range[ch] = i;
		mutex_unlock(&st->lock);

		वापस 0;
	हाल IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		अगर (val2)
			वापस -EINVAL;
		i = find_बंदst(val, st->oversampling_avail,
				 st->num_os_ratios);
		mutex_lock(&st->lock);
		ret = st->ग_लिखो_os(indio_dev, i);
		अगर (ret < 0) अणु
			mutex_unlock(&st->lock);
			वापस ret;
		पूर्ण
		st->oversampling = st->oversampling_avail[i];
		mutex_unlock(&st->lock);

		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार ad7606_oversampling_ratio_avail(काष्ठा device *dev,
					       काष्ठा device_attribute *attr,
					       अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ad7606_state *st = iio_priv(indio_dev);

	वापस ad7606_show_avail(buf, st->oversampling_avail,
				 st->num_os_ratios, false);
पूर्ण

अटल IIO_DEVICE_ATTR(oversampling_ratio_available, 0444,
		       ad7606_oversampling_ratio_avail, शून्य, 0);

अटल काष्ठा attribute *ad7606_attributes_os_and_range[] = अणु
	&iio_dev_attr_in_voltage_scale_available.dev_attr.attr,
	&iio_dev_attr_oversampling_ratio_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ad7606_attribute_group_os_and_range = अणु
	.attrs = ad7606_attributes_os_and_range,
पूर्ण;

अटल काष्ठा attribute *ad7606_attributes_os[] = अणु
	&iio_dev_attr_oversampling_ratio_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ad7606_attribute_group_os = अणु
	.attrs = ad7606_attributes_os,
पूर्ण;

अटल काष्ठा attribute *ad7606_attributes_range[] = अणु
	&iio_dev_attr_in_voltage_scale_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ad7606_attribute_group_range = अणु
	.attrs = ad7606_attributes_range,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec ad7605_channels[] = अणु
	IIO_CHAN_SOFT_TIMESTAMP(4),
	AD7605_CHANNEL(0),
	AD7605_CHANNEL(1),
	AD7605_CHANNEL(2),
	AD7605_CHANNEL(3),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec ad7606_channels[] = अणु
	IIO_CHAN_SOFT_TIMESTAMP(8),
	AD7606_CHANNEL(0),
	AD7606_CHANNEL(1),
	AD7606_CHANNEL(2),
	AD7606_CHANNEL(3),
	AD7606_CHANNEL(4),
	AD7606_CHANNEL(5),
	AD7606_CHANNEL(6),
	AD7606_CHANNEL(7),
पूर्ण;

/*
 * The current assumption that this driver makes क्रम AD7616, is that it's
 * working in Hardware Mode with Serial, Burst and Sequencer modes activated.
 * To activate them, following pins must be pulled high:
 *	-SER/PAR
 *	-SEQEN
 * And following pins must be pulled low:
 *	-WR/BURST
 *	-DB4/SER1W
 */
अटल स्थिर काष्ठा iio_chan_spec ad7616_channels[] = अणु
	IIO_CHAN_SOFT_TIMESTAMP(16),
	AD7606_CHANNEL(0),
	AD7606_CHANNEL(1),
	AD7606_CHANNEL(2),
	AD7606_CHANNEL(3),
	AD7606_CHANNEL(4),
	AD7606_CHANNEL(5),
	AD7606_CHANNEL(6),
	AD7606_CHANNEL(7),
	AD7606_CHANNEL(8),
	AD7606_CHANNEL(9),
	AD7606_CHANNEL(10),
	AD7606_CHANNEL(11),
	AD7606_CHANNEL(12),
	AD7606_CHANNEL(13),
	AD7606_CHANNEL(14),
	AD7606_CHANNEL(15),
पूर्ण;

अटल स्थिर काष्ठा ad7606_chip_info ad7606_chip_info_tbl[] = अणु
	/* More devices added in future */
	[ID_AD7605_4] = अणु
		.channels = ad7605_channels,
		.num_channels = 5,
	पूर्ण,
	[ID_AD7606_8] = अणु
		.channels = ad7606_channels,
		.num_channels = 9,
		.oversampling_avail = ad7606_oversampling_avail,
		.oversampling_num = ARRAY_SIZE(ad7606_oversampling_avail),
	पूर्ण,
	[ID_AD7606_6] = अणु
		.channels = ad7606_channels,
		.num_channels = 7,
		.oversampling_avail = ad7606_oversampling_avail,
		.oversampling_num = ARRAY_SIZE(ad7606_oversampling_avail),
	पूर्ण,
	[ID_AD7606_4] = अणु
		.channels = ad7606_channels,
		.num_channels = 5,
		.oversampling_avail = ad7606_oversampling_avail,
		.oversampling_num = ARRAY_SIZE(ad7606_oversampling_avail),
	पूर्ण,
	[ID_AD7606B] = अणु
		.channels = ad7606_channels,
		.num_channels = 9,
		.oversampling_avail = ad7606_oversampling_avail,
		.oversampling_num = ARRAY_SIZE(ad7606_oversampling_avail),
	पूर्ण,
	[ID_AD7616] = अणु
		.channels = ad7616_channels,
		.num_channels = 17,
		.oversampling_avail = ad7616_oversampling_avail,
		.oversampling_num = ARRAY_SIZE(ad7616_oversampling_avail),
		.os_req_reset = true,
		.init_delay_ms = 15,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ad7606_request_gpios(काष्ठा ad7606_state *st)
अणु
	काष्ठा device *dev = st->dev;

	st->gpio_convst = devm_gpiod_get(dev, "adi,conversion-start",
					 GPIOD_OUT_LOW);
	अगर (IS_ERR(st->gpio_convst))
		वापस PTR_ERR(st->gpio_convst);

	st->gpio_reset = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(st->gpio_reset))
		वापस PTR_ERR(st->gpio_reset);

	st->gpio_range = devm_gpiod_get_optional(dev, "adi,range",
						 GPIOD_OUT_LOW);
	अगर (IS_ERR(st->gpio_range))
		वापस PTR_ERR(st->gpio_range);

	st->gpio_standby = devm_gpiod_get_optional(dev, "standby",
						   GPIOD_OUT_HIGH);
	अगर (IS_ERR(st->gpio_standby))
		वापस PTR_ERR(st->gpio_standby);

	st->gpio_frstdata = devm_gpiod_get_optional(dev, "adi,first-data",
						    GPIOD_IN);
	अगर (IS_ERR(st->gpio_frstdata))
		वापस PTR_ERR(st->gpio_frstdata);

	अगर (!st->chip_info->oversampling_num)
		वापस 0;

	st->gpio_os = devm_gpiod_get_array_optional(dev,
						    "adi,oversampling-ratio",
						    GPIOD_OUT_LOW);
	वापस PTR_ERR_OR_ZERO(st->gpio_os);
पूर्ण

/*
 * The BUSY संकेत indicates when conversions are in progress, so when a rising
 * edge of CONVST is applied, BUSY goes logic high and transitions low at the
 * end of the entire conversion process. The falling edge of the BUSY संकेत
 * triggers this पूर्णांकerrupt.
 */
अटल irqवापस_t ad7606_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा iio_dev *indio_dev = dev_id;
	काष्ठा ad7606_state *st = iio_priv(indio_dev);

	अगर (iio_buffer_enabled(indio_dev)) अणु
		gpiod_set_value(st->gpio_convst, 0);
		iio_trigger_poll_chained(st->trig);
	पूर्ण अन्यथा अणु
		complete(&st->completion);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण;

अटल पूर्णांक ad7606_validate_trigger(काष्ठा iio_dev *indio_dev,
				   काष्ठा iio_trigger *trig)
अणु
	काष्ठा ad7606_state *st = iio_priv(indio_dev);

	अगर (st->trig != trig)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक ad7606_buffer_postenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ad7606_state *st = iio_priv(indio_dev);

	gpiod_set_value(st->gpio_convst, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक ad7606_buffer_predisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ad7606_state *st = iio_priv(indio_dev);

	gpiod_set_value(st->gpio_convst, 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops ad7606_buffer_ops = अणु
	.postenable = &ad7606_buffer_postenable,
	.predisable = &ad7606_buffer_predisable,
पूर्ण;

अटल स्थिर काष्ठा iio_info ad7606_info_no_os_or_range = अणु
	.पढ़ो_raw = &ad7606_पढ़ो_raw,
	.validate_trigger = &ad7606_validate_trigger,
पूर्ण;

अटल स्थिर काष्ठा iio_info ad7606_info_os_and_range = अणु
	.पढ़ो_raw = &ad7606_पढ़ो_raw,
	.ग_लिखो_raw = &ad7606_ग_लिखो_raw,
	.attrs = &ad7606_attribute_group_os_and_range,
	.validate_trigger = &ad7606_validate_trigger,
पूर्ण;

अटल स्थिर काष्ठा iio_info ad7606_info_os_range_and_debug = अणु
	.पढ़ो_raw = &ad7606_पढ़ो_raw,
	.ग_लिखो_raw = &ad7606_ग_लिखो_raw,
	.debugfs_reg_access = &ad7606_reg_access,
	.attrs = &ad7606_attribute_group_os_and_range,
	.validate_trigger = &ad7606_validate_trigger,
पूर्ण;

अटल स्थिर काष्ठा iio_info ad7606_info_os = अणु
	.पढ़ो_raw = &ad7606_पढ़ो_raw,
	.ग_लिखो_raw = &ad7606_ग_लिखो_raw,
	.attrs = &ad7606_attribute_group_os,
	.validate_trigger = &ad7606_validate_trigger,
पूर्ण;

अटल स्थिर काष्ठा iio_info ad7606_info_range = अणु
	.पढ़ो_raw = &ad7606_पढ़ो_raw,
	.ग_लिखो_raw = &ad7606_ग_लिखो_raw,
	.attrs = &ad7606_attribute_group_range,
	.validate_trigger = &ad7606_validate_trigger,
पूर्ण;

अटल स्थिर काष्ठा iio_trigger_ops ad7606_trigger_ops = अणु
	.validate_device = iio_trigger_validate_own_device,
पूर्ण;

अटल व्योम ad7606_regulator_disable(व्योम *data)
अणु
	काष्ठा ad7606_state *st = data;

	regulator_disable(st->reg);
पूर्ण

पूर्णांक ad7606_probe(काष्ठा device *dev, पूर्णांक irq, व्योम __iomem *base_address,
		 स्थिर अक्षर *name, अचिन्हित पूर्णांक id,
		 स्थिर काष्ठा ad7606_bus_ops *bops)
अणु
	काष्ठा ad7606_state *st;
	पूर्णांक ret;
	काष्ठा iio_dev *indio_dev;

	indio_dev = devm_iio_device_alloc(dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);
	dev_set_drvdata(dev, indio_dev);

	st->dev = dev;
	mutex_init(&st->lock);
	st->bops = bops;
	st->base_address = base_address;
	/* tied to logic low, analog input range is +/- 5V */
	st->range[0] = 0;
	st->oversampling = 1;
	st->scale_avail = ad7606_scale_avail;
	st->num_scales = ARRAY_SIZE(ad7606_scale_avail);

	st->reg = devm_regulator_get(dev, "avcc");
	अगर (IS_ERR(st->reg))
		वापस PTR_ERR(st->reg);

	ret = regulator_enable(st->reg);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable specified AVcc supply\n");
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(dev, ad7606_regulator_disable, st);
	अगर (ret)
		वापस ret;

	st->chip_info = &ad7606_chip_info_tbl[id];

	अगर (st->chip_info->oversampling_num) अणु
		st->oversampling_avail = st->chip_info->oversampling_avail;
		st->num_os_ratios = st->chip_info->oversampling_num;
	पूर्ण

	ret = ad7606_request_gpios(st);
	अगर (ret)
		वापस ret;

	अगर (st->gpio_os) अणु
		अगर (st->gpio_range)
			indio_dev->info = &ad7606_info_os_and_range;
		अन्यथा
			indio_dev->info = &ad7606_info_os;
	पूर्ण अन्यथा अणु
		अगर (st->gpio_range)
			indio_dev->info = &ad7606_info_range;
		अन्यथा
			indio_dev->info = &ad7606_info_no_os_or_range;
	पूर्ण
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->name = name;
	indio_dev->channels = st->chip_info->channels;
	indio_dev->num_channels = st->chip_info->num_channels;

	init_completion(&st->completion);

	ret = ad7606_reset(st);
	अगर (ret)
		dev_warn(st->dev, "failed to RESET: no RESET GPIO specified\n");

	/* AD7616 requires al least 15ms to reconfigure after a reset */
	अगर (st->chip_info->init_delay_ms) अणु
		अगर (msleep_पूर्णांकerruptible(st->chip_info->init_delay_ms))
			वापस -ERESTARTSYS;
	पूर्ण

	st->ग_लिखो_scale = ad7606_ग_लिखो_scale_hw;
	st->ग_लिखो_os = ad7606_ग_लिखो_os_hw;

	अगर (st->bops->sw_mode_config)
		st->sw_mode_en = device_property_present(st->dev,
							 "adi,sw-mode");

	अगर (st->sw_mode_en) अणु
		/* Scale of 0.076293 is only available in sw mode */
		st->scale_avail = ad7616_sw_scale_avail;
		st->num_scales = ARRAY_SIZE(ad7616_sw_scale_avail);

		/* After reset, in software mode, तऔ10 V is set by शेष */
		स_रखो32(st->range, 2, ARRAY_SIZE(st->range));
		indio_dev->info = &ad7606_info_os_range_and_debug;

		ret = st->bops->sw_mode_config(indio_dev);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	st->trig = devm_iio_trigger_alloc(dev, "%s-dev%d",
					  indio_dev->name, indio_dev->id);
	अगर (!st->trig)
		वापस -ENOMEM;

	st->trig->ops = &ad7606_trigger_ops;
	iio_trigger_set_drvdata(st->trig, indio_dev);
	ret = devm_iio_trigger_रेजिस्टर(dev, st->trig);
	अगर (ret)
		वापस ret;

	indio_dev->trig = iio_trigger_get(st->trig);

	ret = devm_request_thपढ़ोed_irq(dev, irq,
					शून्य,
					&ad7606_पूर्णांकerrupt,
					IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					name, indio_dev);
	अगर (ret)
		वापस ret;

	ret = devm_iio_triggered_buffer_setup(dev, indio_dev,
					      &iio_pollfunc_store_समय,
					      &ad7606_trigger_handler,
					      &ad7606_buffer_ops);
	अगर (ret)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(dev, indio_dev);
पूर्ण
EXPORT_SYMBOL_GPL(ad7606_probe);

#अगर_घोषित CONFIG_PM_SLEEP

अटल पूर्णांक ad7606_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा ad7606_state *st = iio_priv(indio_dev);

	अगर (st->gpio_standby) अणु
		gpiod_set_value(st->gpio_range, 1);
		gpiod_set_value(st->gpio_standby, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ad7606_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा ad7606_state *st = iio_priv(indio_dev);

	अगर (st->gpio_standby) अणु
		gpiod_set_value(st->gpio_range, st->range[0]);
		gpiod_set_value(st->gpio_standby, 1);
		ad7606_reset(st);
	पूर्ण

	वापस 0;
पूर्ण

SIMPLE_DEV_PM_OPS(ad7606_pm_ops, ad7606_suspend, ad7606_resume);
EXPORT_SYMBOL_GPL(ad7606_pm_ops);

#पूर्ण_अगर

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("Analog Devices AD7606 ADC");
MODULE_LICENSE("GPL v2");
