<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * HX711: analog to digital converter क्रम weight sensor module
 *
 * Copyright (c) 2016 Andreas Klinger <ak@it-klinger.de>
 */
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/regulator/consumer.h>

/* gain to pulse and scale conversion */
#घोषणा HX711_GAIN_MAX		3
#घोषणा HX711_RESET_GAIN	128

काष्ठा hx711_gain_to_scale अणु
	पूर्णांक			gain;
	पूर्णांक			gain_pulse;
	पूर्णांक			scale;
	पूर्णांक			channel;
पूर्ण;

/*
 * .scale depends on AVDD which in turn is known as soon as the regulator
 * is available
 * thereक्रमe we set .scale in hx711_probe()
 *
 * channel A in करोcumentation is channel 0 in source code
 * channel B in करोcumentation is channel 1 in source code
 */
अटल काष्ठा hx711_gain_to_scale hx711_gain_to_scale[HX711_GAIN_MAX] = अणु
	अणु 128, 1, 0, 0 पूर्ण,
	अणु  32, 2, 0, 1 पूर्ण,
	अणु  64, 3, 0, 0 पूर्ण
पूर्ण;

अटल पूर्णांक hx711_get_gain_to_pulse(पूर्णांक gain)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < HX711_GAIN_MAX; i++)
		अगर (hx711_gain_to_scale[i].gain == gain)
			वापस hx711_gain_to_scale[i].gain_pulse;
	वापस 1;
पूर्ण

अटल पूर्णांक hx711_get_gain_to_scale(पूर्णांक gain)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < HX711_GAIN_MAX; i++)
		अगर (hx711_gain_to_scale[i].gain == gain)
			वापस hx711_gain_to_scale[i].scale;
	वापस 0;
पूर्ण

अटल पूर्णांक hx711_get_scale_to_gain(पूर्णांक scale)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < HX711_GAIN_MAX; i++)
		अगर (hx711_gain_to_scale[i].scale == scale)
			वापस hx711_gain_to_scale[i].gain;
	वापस -EINVAL;
पूर्ण

काष्ठा hx711_data अणु
	काष्ठा device		*dev;
	काष्ठा gpio_desc	*gpiod_pd_sck;
	काष्ठा gpio_desc	*gpiod_करोut;
	काष्ठा regulator	*reg_avdd;
	पूर्णांक			gain_set;	/* gain set on device */
	पूर्णांक			gain_chan_a;	/* gain क्रम channel A */
	काष्ठा mutex		lock;
	/*
	 * triggered buffer
	 * 2x32-bit channel + 64-bit बारtamp
	 */
	u32			buffer[4];
	/*
	 * delay after a rising edge on SCK until the data is पढ़ोy DOUT
	 * this is dependent on the hx711 where the datasheet tells a
	 * maximum value of 100 ns
	 * but also on potential parasitic capacities on the wiring
	 */
	u32			data_पढ़ोy_delay_ns;
	u32			घड़ी_frequency;
पूर्ण;

अटल पूर्णांक hx711_cycle(काष्ठा hx711_data *hx711_data)
अणु
	अचिन्हित दीर्घ flags;

	/*
	 * अगर preempted क्रम more then 60us जबतक PD_SCK is high:
	 * hx711 is going in reset
	 * ==> measuring is false
	 */
	local_irq_save(flags);
	gpiod_set_value(hx711_data->gpiod_pd_sck, 1);

	/*
	 * रुको until DOUT is पढ़ोy
	 * it turned out that parasitic capacities are extending the समय
	 * until DOUT has reached it's value
	 */
	ndelay(hx711_data->data_पढ़ोy_delay_ns);

	/*
	 * here we are not रुकोing क्रम 0.2 us as suggested by the datasheet,
	 * because the oscilloscope showed in a test scenario
	 * at least 1.15 us क्रम PD_SCK high (T3 in datasheet)
	 * and 0.56 us क्रम PD_SCK low on TI Sitara with 800 MHz
	 */
	gpiod_set_value(hx711_data->gpiod_pd_sck, 0);
	local_irq_restore(flags);

	/*
	 * make it a square wave क्रम addressing हालs with capacitance on
	 * PC_SCK
	 */
	ndelay(hx711_data->data_पढ़ोy_delay_ns);

	/* sample as late as possible */
	वापस gpiod_get_value(hx711_data->gpiod_करोut);
पूर्ण

अटल पूर्णांक hx711_पढ़ो(काष्ठा hx711_data *hx711_data)
अणु
	पूर्णांक i, ret;
	पूर्णांक value = 0;
	पूर्णांक val = gpiod_get_value(hx711_data->gpiod_करोut);

	/* we द्विगुन check अगर it's really करोwn */
	अगर (val)
		वापस -EIO;

	क्रम (i = 0; i < 24; i++) अणु
		value <<= 1;
		ret = hx711_cycle(hx711_data);
		अगर (ret)
			value++;
	पूर्ण

	value ^= 0x800000;

	क्रम (i = 0; i < hx711_get_gain_to_pulse(hx711_data->gain_set); i++)
		hx711_cycle(hx711_data);

	वापस value;
पूर्ण

अटल पूर्णांक hx711_रुको_क्रम_पढ़ोy(काष्ठा hx711_data *hx711_data)
अणु
	पूर्णांक i, val;

	/*
	 * in some rare हालs the reset takes quite a दीर्घ समय
	 * especially when the channel is changed.
	 * Allow up to one second क्रम it
	 */
	क्रम (i = 0; i < 100; i++) अणु
		val = gpiod_get_value(hx711_data->gpiod_करोut);
		अगर (!val)
			अवरोध;
		/* sleep at least 10 ms */
		msleep(10);
	पूर्ण
	अगर (val)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक hx711_reset(काष्ठा hx711_data *hx711_data)
अणु
	पूर्णांक val = hx711_रुको_क्रम_पढ़ोy(hx711_data);

	अगर (val) अणु
		/*
		 * an examination with the oszilloscope indicated
		 * that the first value पढ़ो after the reset is not stable
		 * अगर we reset too लघु;
		 * the लघुer the reset cycle
		 * the less reliable the first value after reset is;
		 * there were no problems encountered with a value
		 * of 10 ms or higher
		 */
		gpiod_set_value(hx711_data->gpiod_pd_sck, 1);
		msleep(10);
		gpiod_set_value(hx711_data->gpiod_pd_sck, 0);

		val = hx711_रुको_क्रम_पढ़ोy(hx711_data);

		/* after a reset the gain is 128 */
		hx711_data->gain_set = HX711_RESET_GAIN;
	पूर्ण

	वापस val;
पूर्ण

अटल पूर्णांक hx711_set_gain_क्रम_channel(काष्ठा hx711_data *hx711_data, पूर्णांक chan)
अणु
	पूर्णांक ret;

	अगर (chan == 0) अणु
		अगर (hx711_data->gain_set == 32) अणु
			hx711_data->gain_set = hx711_data->gain_chan_a;

			ret = hx711_पढ़ो(hx711_data);
			अगर (ret < 0)
				वापस ret;

			ret = hx711_रुको_क्रम_पढ़ोy(hx711_data);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (hx711_data->gain_set != 32) अणु
			hx711_data->gain_set = 32;

			ret = hx711_पढ़ो(hx711_data);
			अगर (ret < 0)
				वापस ret;

			ret = hx711_रुको_क्रम_पढ़ोy(hx711_data);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hx711_reset_पढ़ो(काष्ठा hx711_data *hx711_data, पूर्णांक chan)
अणु
	पूर्णांक ret;
	पूर्णांक val;

	/*
	 * hx711_reset() must be called from here
	 * because it could be calling hx711_पढ़ो() by itself
	 */
	अगर (hx711_reset(hx711_data)) अणु
		dev_err(hx711_data->dev, "reset failed!");
		वापस -EIO;
	पूर्ण

	ret = hx711_set_gain_क्रम_channel(hx711_data, chan);
	अगर (ret < 0)
		वापस ret;

	val = hx711_पढ़ो(hx711_data);

	वापस val;
पूर्ण

अटल पूर्णांक hx711_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				स्थिर काष्ठा iio_chan_spec *chan,
				पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा hx711_data *hx711_data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&hx711_data->lock);

		*val = hx711_reset_पढ़ो(hx711_data, chan->channel);

		mutex_unlock(&hx711_data->lock);

		अगर (*val < 0)
			वापस *val;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = 0;
		mutex_lock(&hx711_data->lock);

		*val2 = hx711_get_gain_to_scale(hx711_data->gain_set);

		mutex_unlock(&hx711_data->lock);

		वापस IIO_VAL_INT_PLUS_न_अंकO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक hx711_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *chan,
				पूर्णांक val,
				पूर्णांक val2,
				दीर्घ mask)
अणु
	काष्ठा hx711_data *hx711_data = iio_priv(indio_dev);
	पूर्णांक ret;
	पूर्णांक gain;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		/*
		 * a scale greater than 1 mV per LSB is not possible
		 * with the HX711, thereक्रमe val must be 0
		 */
		अगर (val != 0)
			वापस -EINVAL;

		mutex_lock(&hx711_data->lock);

		gain = hx711_get_scale_to_gain(val2);
		अगर (gain < 0) अणु
			mutex_unlock(&hx711_data->lock);
			वापस gain;
		पूर्ण

		अगर (gain != hx711_data->gain_set) अणु
			hx711_data->gain_set = gain;
			अगर (gain != 32)
				hx711_data->gain_chan_a = gain;

			ret = hx711_पढ़ो(hx711_data);
			अगर (ret < 0) अणु
				mutex_unlock(&hx711_data->lock);
				वापस ret;
			पूर्ण
		पूर्ण

		mutex_unlock(&hx711_data->lock);
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hx711_ग_लिखो_raw_get_fmt(काष्ठा iio_dev *indio_dev,
		काष्ठा iio_chan_spec स्थिर *chan,
		दीर्घ mask)
अणु
	वापस IIO_VAL_INT_PLUS_न_अंकO;
पूर्ण

अटल irqवापस_t hx711_trigger(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा hx711_data *hx711_data = iio_priv(indio_dev);
	पूर्णांक i, j = 0;

	mutex_lock(&hx711_data->lock);

	स_रखो(hx711_data->buffer, 0, माप(hx711_data->buffer));

	क्रम (i = 0; i < indio_dev->masklength; i++) अणु
		अगर (!test_bit(i, indio_dev->active_scan_mask))
			जारी;

		hx711_data->buffer[j] = hx711_reset_पढ़ो(hx711_data,
					indio_dev->channels[i].channel);
		j++;
	पूर्ण

	iio_push_to_buffers_with_बारtamp(indio_dev, hx711_data->buffer,
							pf->बारtamp);

	mutex_unlock(&hx711_data->lock);

	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल sमाप_प्रकार hx711_scale_available_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा iio_dev_attr *iio_attr = to_iio_dev_attr(attr);
	पूर्णांक channel = iio_attr->address;
	पूर्णांक i, len = 0;

	क्रम (i = 0; i < HX711_GAIN_MAX; i++)
		अगर (hx711_gain_to_scale[i].channel == channel)
			len += प्र_लिखो(buf + len, "0.%09d ",
					hx711_gain_to_scale[i].scale);

	len += प्र_लिखो(buf + len, "\n");

	वापस len;
पूर्ण

अटल IIO_DEVICE_ATTR(in_voltage0_scale_available, S_IRUGO,
	hx711_scale_available_show, शून्य, 0);

अटल IIO_DEVICE_ATTR(in_voltage1_scale_available, S_IRUGO,
	hx711_scale_available_show, शून्य, 1);

अटल काष्ठा attribute *hx711_attributes[] = अणु
	&iio_dev_attr_in_voltage0_scale_available.dev_attr.attr,
	&iio_dev_attr_in_voltage1_scale_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group hx711_attribute_group = अणु
	.attrs = hx711_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info hx711_iio_info = अणु
	.पढ़ो_raw		= hx711_पढ़ो_raw,
	.ग_लिखो_raw		= hx711_ग_लिखो_raw,
	.ग_लिखो_raw_get_fmt	= hx711_ग_लिखो_raw_get_fmt,
	.attrs			= &hx711_attribute_group,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec hx711_chan_spec[] = अणु
	अणु
		.type = IIO_VOLTAGE,
		.channel = 0,
		.indexed = 1,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),
		.scan_index = 0,
		.scan_type = अणु
			.sign = 'u',
			.realbits = 24,
			.storagebits = 32,
			.endianness = IIO_CPU,
		पूर्ण,
	पूर्ण,
	अणु
		.type = IIO_VOLTAGE,
		.channel = 1,
		.indexed = 1,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),
		.scan_index = 1,
		.scan_type = अणु
			.sign = 'u',
			.realbits = 24,
			.storagebits = 32,
			.endianness = IIO_CPU,
		पूर्ण,
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(2),
पूर्ण;

अटल पूर्णांक hx711_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा hx711_data *hx711_data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;
	पूर्णांक i;

	indio_dev = devm_iio_device_alloc(dev, माप(काष्ठा hx711_data));
	अगर (!indio_dev) अणु
		dev_err(dev, "failed to allocate IIO device\n");
		वापस -ENOMEM;
	पूर्ण

	hx711_data = iio_priv(indio_dev);
	hx711_data->dev = dev;

	mutex_init(&hx711_data->lock);

	/*
	 * PD_SCK stands क्रम घातer करोwn and serial घड़ी input of HX711
	 * in the driver it is an output
	 */
	hx711_data->gpiod_pd_sck = devm_gpiod_get(dev, "sck", GPIOD_OUT_LOW);
	अगर (IS_ERR(hx711_data->gpiod_pd_sck)) अणु
		dev_err(dev, "failed to get sck-gpiod: err=%ld\n",
					PTR_ERR(hx711_data->gpiod_pd_sck));
		वापस PTR_ERR(hx711_data->gpiod_pd_sck);
	पूर्ण

	/*
	 * DOUT stands क्रम serial data output of HX711
	 * क्रम the driver it is an input
	 */
	hx711_data->gpiod_करोut = devm_gpiod_get(dev, "dout", GPIOD_IN);
	अगर (IS_ERR(hx711_data->gpiod_करोut)) अणु
		dev_err(dev, "failed to get dout-gpiod: err=%ld\n",
					PTR_ERR(hx711_data->gpiod_करोut));
		वापस PTR_ERR(hx711_data->gpiod_करोut);
	पूर्ण

	hx711_data->reg_avdd = devm_regulator_get(dev, "avdd");
	अगर (IS_ERR(hx711_data->reg_avdd))
		वापस PTR_ERR(hx711_data->reg_avdd);

	ret = regulator_enable(hx711_data->reg_avdd);
	अगर (ret < 0)
		वापस ret;

	/*
	 * with
	 * full scale dअगरferential input range: AVDD / GAIN
	 * full scale output data: 2^24
	 * we can say:
	 *     AVDD / GAIN = 2^24
	 * thereक्रमe:
	 *     1 LSB = AVDD / GAIN / 2^24
	 * AVDD is in uV, but we need 10^-9 mV
	 * approximately to fit पूर्णांकo a 32 bit number:
	 * 1 LSB = (AVDD * 100) / GAIN / 1678 [10^-9 mV]
	 */
	ret = regulator_get_voltage(hx711_data->reg_avdd);
	अगर (ret < 0)
		जाओ error_regulator;

	/* we need 10^-9 mV */
	ret *= 100;

	क्रम (i = 0; i < HX711_GAIN_MAX; i++)
		hx711_gain_to_scale[i].scale =
			ret / hx711_gain_to_scale[i].gain / 1678;

	hx711_data->gain_set = 128;
	hx711_data->gain_chan_a = 128;

	hx711_data->घड़ी_frequency = 400000;
	ret = of_property_पढ़ो_u32(np, "clock-frequency",
					&hx711_data->घड़ी_frequency);

	/*
	 * datasheet says the high level of PD_SCK has a maximum duration
	 * of 50 microseconds
	 */
	अगर (hx711_data->घड़ी_frequency < 20000) अणु
		dev_warn(dev, "clock-frequency too low - assuming 400 kHz\n");
		hx711_data->घड़ी_frequency = 400000;
	पूर्ण

	hx711_data->data_पढ़ोy_delay_ns =
				1000000000 / hx711_data->घड़ी_frequency;

	platक्रमm_set_drvdata(pdev, indio_dev);

	indio_dev->name = "hx711";
	indio_dev->info = &hx711_iio_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = hx711_chan_spec;
	indio_dev->num_channels = ARRAY_SIZE(hx711_chan_spec);

	ret = iio_triggered_buffer_setup(indio_dev, iio_pollfunc_store_समय,
							hx711_trigger, शून्य);
	अगर (ret < 0) अणु
		dev_err(dev, "setup of iio triggered buffer failed\n");
		जाओ error_regulator;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0) अणु
		dev_err(dev, "Couldn't register the device\n");
		जाओ error_buffer;
	पूर्ण

	वापस 0;

error_buffer:
	iio_triggered_buffer_cleanup(indio_dev);

error_regulator:
	regulator_disable(hx711_data->reg_avdd);

	वापस ret;
पूर्ण

अटल पूर्णांक hx711_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hx711_data *hx711_data;
	काष्ठा iio_dev *indio_dev;

	indio_dev = platक्रमm_get_drvdata(pdev);
	hx711_data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	iio_triggered_buffer_cleanup(indio_dev);

	regulator_disable(hx711_data->reg_avdd);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_hx711_match[] = अणु
	अणु .compatible = "avia,hx711", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, of_hx711_match);

अटल काष्ठा platक्रमm_driver hx711_driver = अणु
	.probe		= hx711_probe,
	.हटाओ		= hx711_हटाओ,
	.driver		= अणु
		.name		= "hx711-gpio",
		.of_match_table	= of_hx711_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(hx711_driver);

MODULE_AUTHOR("Andreas Klinger <ak@it-klinger.de>");
MODULE_DESCRIPTION("HX711 bitbanging driver - ADC for weight cells");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:hx711-gpio");

