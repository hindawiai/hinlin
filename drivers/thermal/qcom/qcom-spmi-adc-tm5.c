<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2020 Linaro Limited
 *
 * Based on original driver:
 * Copyright (c) 2012-2020, The Linux Foundation. All rights reserved.
 */
#समावेश <linux/bitfield.h>
#समावेश <linux/iio/adc/qcom-vadc-common.h>
#समावेश <linux/iio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/thermal.h>

/*
 * Thermal monitoring block consists of 8 (ADC_TM5_NUM_CHANNELS) channels. Each
 * channel is programmed to use one of ADC channels क्रम voltage comparison.
 * Voltages are programmed using ADC codes, so we have to convert temp to
 * voltage and then to ADC code value.
 *
 * Configuration of TM channels must match configuration of corresponding ADC
 * channels.
 */

#घोषणा ADC5_MAX_CHANNEL                        0xc0
#घोषणा ADC_TM5_NUM_CHANNELS		8

#घोषणा ADC_TM5_STATUS_LOW			0x0a

#घोषणा ADC_TM5_STATUS_HIGH			0x0b

#घोषणा ADC_TM5_NUM_BTM				0x0f

#घोषणा ADC_TM5_ADC_DIG_PARAM			0x42

#घोषणा ADC_TM5_FAST_AVG_CTL			(ADC_TM5_ADC_DIG_PARAM + 1)
#घोषणा ADC_TM5_FAST_AVG_EN				BIT(7)

#घोषणा ADC_TM5_MEAS_INTERVAL_CTL		(ADC_TM5_ADC_DIG_PARAM + 2)
#घोषणा ADC_TM5_TIMER1					3 /* 3.9ms */

#घोषणा ADC_TM5_MEAS_INTERVAL_CTL2		(ADC_TM5_ADC_DIG_PARAM + 3)
#घोषणा ADC_TM5_MEAS_INTERVAL_CTL2_MASK			0xf0
#घोषणा ADC_TM5_TIMER2					10 /* 1 second */
#घोषणा ADC_TM5_MEAS_INTERVAL_CTL3_MASK			0xf
#घोषणा ADC_TM5_TIMER3					4 /* 4 second */

#घोषणा ADC_TM_EN_CTL1				0x46
#घोषणा ADC_TM_EN					BIT(7)
#घोषणा ADC_TM_CONV_REQ				0x47
#घोषणा ADC_TM_CONV_REQ_EN				BIT(7)

#घोषणा ADC_TM5_M_CHAN_BASE			0x60

#घोषणा ADC_TM5_M_ADC_CH_SEL_CTL(n)		(ADC_TM5_M_CHAN_BASE + ((n) * 8) + 0)
#घोषणा ADC_TM5_M_LOW_THR0(n)			(ADC_TM5_M_CHAN_BASE + ((n) * 8) + 1)
#घोषणा ADC_TM5_M_LOW_THR1(n)			(ADC_TM5_M_CHAN_BASE + ((n) * 8) + 2)
#घोषणा ADC_TM5_M_HIGH_THR0(n)			(ADC_TM5_M_CHAN_BASE + ((n) * 8) + 3)
#घोषणा ADC_TM5_M_HIGH_THR1(n)			(ADC_TM5_M_CHAN_BASE + ((n) * 8) + 4)
#घोषणा ADC_TM5_M_MEAS_INTERVAL_CTL(n)		(ADC_TM5_M_CHAN_BASE + ((n) * 8) + 5)
#घोषणा ADC_TM5_M_CTL(n)			(ADC_TM5_M_CHAN_BASE + ((n) * 8) + 6)
#घोषणा ADC_TM5_M_CTL_HW_SETTLE_DELAY_MASK		0xf
#घोषणा ADC_TM5_M_CTL_CAL_SEL_MASK			0x30
#घोषणा ADC_TM5_M_CTL_CAL_VAL				0x40
#घोषणा ADC_TM5_M_EN(n)				(ADC_TM5_M_CHAN_BASE + ((n) * 8) + 7)
#घोषणा ADC_TM5_M_MEAS_EN				BIT(7)
#घोषणा ADC_TM5_M_HIGH_THR_INT_EN			BIT(1)
#घोषणा ADC_TM5_M_LOW_THR_INT_EN			BIT(0)

क्रमागत adc5_समयr_select अणु
	ADC5_TIMER_SEL_1 = 0,
	ADC5_TIMER_SEL_2,
	ADC5_TIMER_SEL_3,
	ADC5_TIMER_SEL_NONE,
पूर्ण;

काष्ठा adc_पंचांग5_data अणु
	स्थिर u32	full_scale_code_volt;
	अचिन्हित पूर्णांक	*decimation;
	अचिन्हित पूर्णांक	*hw_settle;
पूर्ण;

क्रमागत adc_पंचांग5_cal_method अणु
	ADC_TM5_NO_CAL = 0,
	ADC_TM5_RATIOMETRIC_CAL,
	ADC_TM5_ABSOLUTE_CAL
पूर्ण;

काष्ठा adc_पंचांग5_chip;

/**
 * काष्ठा adc_पंचांग5_channel - ADC Thermal Monitoring channel data.
 * @channel: channel number.
 * @adc_channel: corresponding ADC channel number.
 * @cal_method: calibration method.
 * @prescale: channel scaling perक्रमmed on the input संकेत.
 * @hw_settle_समय: the समय between AMUX being configured and the
 *	start of conversion.
 * @iio: IIO channel instance used by this channel.
 * @chip: ADC TM chip instance.
 * @tzd: thermal zone device used by this channel.
 */
काष्ठा adc_पंचांग5_channel अणु
	अचिन्हित पूर्णांक		channel;
	अचिन्हित पूर्णांक		adc_channel;
	क्रमागत adc_पंचांग5_cal_method	cal_method;
	अचिन्हित पूर्णांक		prescale;
	अचिन्हित पूर्णांक		hw_settle_समय;
	काष्ठा iio_channel	*iio;
	काष्ठा adc_पंचांग5_chip	*chip;
	काष्ठा thermal_zone_device *tzd;
पूर्ण;

/**
 * काष्ठा adc_पंचांग5_chip - ADC Thermal Monitoring properties
 * @regmap: SPMI ADC5 Thermal Monitoring  peripheral रेजिस्टर map field.
 * @dev: SPMI ADC5 device.
 * @data: software configuration data.
 * @channels: array of ADC TM channel data.
 * @nchannels: amount of channels defined/allocated
 * @decimation: sampling rate supported क्रम the channel.
 * @avg_samples: ability to provide single result from the ADC
 *	that is an average of multiple measurements.
 * @base: base address of TM रेजिस्टरs.
 */
काष्ठा adc_पंचांग5_chip अणु
	काष्ठा regmap		*regmap;
	काष्ठा device		*dev;
	स्थिर काष्ठा adc_पंचांग5_data	*data;
	काष्ठा adc_पंचांग5_channel	*channels;
	अचिन्हित पूर्णांक		nchannels;
	अचिन्हित पूर्णांक		decimation;
	अचिन्हित पूर्णांक		avg_samples;
	u16			base;
पूर्ण;

अटल स्थिर काष्ठा adc_पंचांग5_data adc_पंचांग5_data_pmic = अणु
	.full_scale_code_volt = 0x70e4,
	.decimation = (अचिन्हित पूर्णांक []) अणु 250, 420, 840 पूर्ण,
	.hw_settle = (अचिन्हित पूर्णांक []) अणु 15, 100, 200, 300, 400, 500, 600, 700,
					 1000, 2000, 4000, 8000, 16000, 32000,
					 64000, 128000 पूर्ण,
पूर्ण;

अटल पूर्णांक adc_पंचांग5_पढ़ो(काष्ठा adc_पंचांग5_chip *adc_पंचांग, u16 offset, u8 *data, पूर्णांक len)
अणु
	वापस regmap_bulk_पढ़ो(adc_पंचांग->regmap, adc_पंचांग->base + offset, data, len);
पूर्ण

अटल पूर्णांक adc_पंचांग5_ग_लिखो(काष्ठा adc_पंचांग5_chip *adc_पंचांग, u16 offset, u8 *data, पूर्णांक len)
अणु
	वापस regmap_bulk_ग_लिखो(adc_पंचांग->regmap, adc_पंचांग->base + offset, data, len);
पूर्ण

अटल पूर्णांक adc_पंचांग5_reg_update(काष्ठा adc_पंचांग5_chip *adc_पंचांग, u16 offset, u8 mask, u8 val)
अणु
	वापस regmap_ग_लिखो_bits(adc_पंचांग->regmap, adc_पंचांग->base + offset, mask, val);
पूर्ण

अटल irqवापस_t adc_पंचांग5_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा adc_पंचांग5_chip *chip = data;
	u8 status_low, status_high, ctl;
	पूर्णांक ret, i;

	ret = adc_पंचांग5_पढ़ो(chip, ADC_TM5_STATUS_LOW, &status_low, माप(status_low));
	अगर (unlikely(ret)) अणु
		dev_err(chip->dev, "read status low failed: %d\n", ret);
		वापस IRQ_HANDLED;
	पूर्ण

	ret = adc_पंचांग5_पढ़ो(chip, ADC_TM5_STATUS_HIGH, &status_high, माप(status_high));
	अगर (unlikely(ret)) अणु
		dev_err(chip->dev, "read status high failed: %d\n", ret);
		वापस IRQ_HANDLED;
	पूर्ण

	क्रम (i = 0; i < chip->nchannels; i++) अणु
		bool upper_set = false, lower_set = false;
		अचिन्हित पूर्णांक ch = chip->channels[i].channel;

		/* No TZD, we warned at the boot समय */
		अगर (!chip->channels[i].tzd)
			जारी;

		ret = adc_पंचांग5_पढ़ो(chip, ADC_TM5_M_EN(ch), &ctl, माप(ctl));
		अगर (unlikely(ret)) अणु
			dev_err(chip->dev, "ctl read failed: %d, channel %d\n", ret, i);
			जारी;
		पूर्ण

		अगर (!(ctl & ADC_TM5_M_MEAS_EN))
			जारी;

		lower_set = (status_low & BIT(ch)) &&
			(ctl & ADC_TM5_M_LOW_THR_INT_EN);

		upper_set = (status_high & BIT(ch)) &&
			(ctl & ADC_TM5_M_HIGH_THR_INT_EN);

		अगर (upper_set || lower_set)
			thermal_zone_device_update(chip->channels[i].tzd,
						   THERMAL_EVENT_UNSPECIFIED);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक adc_पंचांग5_get_temp(व्योम *data, पूर्णांक *temp)
अणु
	काष्ठा adc_पंचांग5_channel *channel = data;
	पूर्णांक ret;

	अगर (!channel || !channel->iio)
		वापस -EINVAL;

	ret = iio_पढ़ो_channel_processed(channel->iio, temp);
	अगर (ret < 0)
		वापस ret;

	अगर (ret != IIO_VAL_INT)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक adc_पंचांग5_disable_channel(काष्ठा adc_पंचांग5_channel *channel)
अणु
	काष्ठा adc_पंचांग5_chip *chip = channel->chip;
	अचिन्हित पूर्णांक reg = ADC_TM5_M_EN(channel->channel);

	वापस adc_पंचांग5_reg_update(chip, reg,
				  ADC_TM5_M_MEAS_EN |
				  ADC_TM5_M_HIGH_THR_INT_EN |
				  ADC_TM5_M_LOW_THR_INT_EN,
				  0);
पूर्ण

अटल पूर्णांक adc_पंचांग5_enable(काष्ठा adc_पंचांग5_chip *chip)
अणु
	पूर्णांक ret;
	u8 data;

	data = ADC_TM_EN;
	ret = adc_पंचांग5_ग_लिखो(chip, ADC_TM_EN_CTL1, &data, माप(data));
	अगर (ret < 0) अणु
		dev_err(chip->dev, "adc-tm enable failed\n");
		वापस ret;
	पूर्ण

	data = ADC_TM_CONV_REQ_EN;
	ret = adc_पंचांग5_ग_लिखो(chip, ADC_TM_CONV_REQ, &data, माप(data));
	अगर (ret < 0) अणु
		dev_err(chip->dev, "adc-tm request conversion failed\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adc_पंचांग5_configure(काष्ठा adc_पंचांग5_channel *channel, पूर्णांक low, पूर्णांक high)
अणु
	काष्ठा adc_पंचांग5_chip *chip = channel->chip;
	u8 buf[8];
	u16 reg = ADC_TM5_M_ADC_CH_SEL_CTL(channel->channel);
	पूर्णांक ret;

	ret = adc_पंचांग5_पढ़ो(chip, reg, buf, माप(buf));
	अगर (ret) अणु
		dev_err(chip->dev, "channel %d params read failed: %d\n", channel->channel, ret);
		वापस ret;
	पूर्ण

	buf[0] = channel->adc_channel;

	/* High temperature corresponds to low voltage threshold */
	अगर (high != पूर्णांक_उच्च) अणु
		u16 adc_code = qcom_adc_पंचांग5_temp_volt_scale(channel->prescale,
				chip->data->full_scale_code_volt, high);

		buf[1] = adc_code & 0xff;
		buf[2] = adc_code >> 8;
		buf[7] |= ADC_TM5_M_LOW_THR_INT_EN;
	पूर्ण अन्यथा अणु
		buf[7] &= ~ADC_TM5_M_LOW_THR_INT_EN;
	पूर्ण

	/* Low temperature corresponds to high voltage threshold */
	अगर (low != -पूर्णांक_उच्च) अणु
		u16 adc_code = qcom_adc_पंचांग5_temp_volt_scale(channel->prescale,
				chip->data->full_scale_code_volt, low);

		buf[3] = adc_code & 0xff;
		buf[4] = adc_code >> 8;
		buf[7] |= ADC_TM5_M_HIGH_THR_INT_EN;
	पूर्ण अन्यथा अणु
		buf[7] &= ~ADC_TM5_M_HIGH_THR_INT_EN;
	पूर्ण

	buf[5] = ADC5_TIMER_SEL_2;

	/* Set calibration select, hw_settle delay */
	buf[6] &= ~ADC_TM5_M_CTL_HW_SETTLE_DELAY_MASK;
	buf[6] |= FIELD_PREP(ADC_TM5_M_CTL_HW_SETTLE_DELAY_MASK, channel->hw_settle_समय);
	buf[6] &= ~ADC_TM5_M_CTL_CAL_SEL_MASK;
	buf[6] |= FIELD_PREP(ADC_TM5_M_CTL_CAL_SEL_MASK, channel->cal_method);

	buf[7] |= ADC_TM5_M_MEAS_EN;

	ret = adc_पंचांग5_ग_लिखो(chip, reg, buf, माप(buf));
	अगर (ret) अणु
		dev_err(chip->dev, "channel %d params write failed: %d\n", channel->channel, ret);
		वापस ret;
	पूर्ण

	वापस adc_पंचांग5_enable(chip);
पूर्ण

अटल पूर्णांक adc_पंचांग5_set_trips(व्योम *data, पूर्णांक low, पूर्णांक high)
अणु
	काष्ठा adc_पंचांग5_channel *channel = data;
	काष्ठा adc_पंचांग5_chip *chip;
	पूर्णांक ret;

	अगर (!channel)
		वापस -EINVAL;

	chip = channel->chip;
	dev_dbg(chip->dev, "%d:low(mdegC):%d, high(mdegC):%d\n",
		channel->channel, low, high);

	अगर (high == पूर्णांक_उच्च && low <= -पूर्णांक_उच्च)
		ret = adc_पंचांग5_disable_channel(channel);
	अन्यथा
		ret = adc_पंचांग5_configure(channel, low, high);

	वापस ret;
पूर्ण

अटल काष्ठा thermal_zone_of_device_ops adc_पंचांग5_ops = अणु
	.get_temp = adc_पंचांग5_get_temp,
	.set_trips = adc_पंचांग5_set_trips,
पूर्ण;

अटल पूर्णांक adc_पंचांग5_रेजिस्टर_tzd(काष्ठा adc_पंचांग5_chip *adc_पंचांग)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा thermal_zone_device *tzd;

	क्रम (i = 0; i < adc_पंचांग->nchannels; i++) अणु
		adc_पंचांग->channels[i].chip = adc_पंचांग;

		tzd = devm_thermal_zone_of_sensor_रेजिस्टर(adc_पंचांग->dev,
							   adc_पंचांग->channels[i].channel,
							   &adc_पंचांग->channels[i],
							   &adc_पंचांग5_ops);
		अगर (IS_ERR(tzd)) अणु
			dev_err(adc_पंचांग->dev, "Error registering TZ zone for channel %d: %ld\n",
				adc_पंचांग->channels[i].channel, PTR_ERR(tzd));
			वापस PTR_ERR(tzd);
		पूर्ण
		adc_पंचांग->channels[i].tzd = tzd;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adc_पंचांग5_init(काष्ठा adc_पंचांग5_chip *chip)
अणु
	u8 buf[4], channels_available;
	पूर्णांक ret;
	अचिन्हित पूर्णांक i;

	ret = adc_पंचांग5_पढ़ो(chip, ADC_TM5_NUM_BTM,
			   &channels_available, माप(channels_available));
	अगर (ret) अणु
		dev_err(chip->dev, "read failed for BTM channels\n");
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < chip->nchannels; i++) अणु
		अगर (chip->channels[i].channel >= channels_available) अणु
			dev_err(chip->dev, "Invalid channel %d\n", chip->channels[i].channel);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	buf[0] = chip->decimation;
	buf[1] = chip->avg_samples | ADC_TM5_FAST_AVG_EN;
	buf[2] = ADC_TM5_TIMER1;
	buf[3] = FIELD_PREP(ADC_TM5_MEAS_INTERVAL_CTL2_MASK, ADC_TM5_TIMER2) |
		 FIELD_PREP(ADC_TM5_MEAS_INTERVAL_CTL3_MASK, ADC_TM5_TIMER3);

	ret = adc_पंचांग5_ग_लिखो(chip, ADC_TM5_ADC_DIG_PARAM, buf, माप(buf));
	अगर (ret) अणु
		dev_err(chip->dev, "block write failed: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक adc_पंचांग5_get_dt_channel_data(काष्ठा adc_पंचांग5_chip *adc_पंचांग,
				       काष्ठा adc_पंचांग5_channel *channel,
				       काष्ठा device_node *node)
अणु
	स्थिर अक्षर *name = node->name;
	u32 chan, value, varr[2];
	पूर्णांक ret;
	काष्ठा device *dev = adc_पंचांग->dev;
	काष्ठा of_phandle_args args;

	ret = of_property_पढ़ो_u32(node, "reg", &chan);
	अगर (ret) अणु
		dev_err(dev, "%s: invalid channel number %d\n", name, ret);
		वापस ret;
	पूर्ण

	अगर (chan >= ADC_TM5_NUM_CHANNELS) अणु
		dev_err(dev, "%s: channel number too big: %d\n", name, chan);
		वापस -EINVAL;
	पूर्ण

	channel->channel = chan;

	/*
	 * We are tied to PMIC's ADC controller, which always use single
	 * argument क्रम channel number.  So करोn't bother parsing
	 * #io-channel-cells, just enक्रमce cell_count = 1.
	 */
	ret = of_parse_phandle_with_fixed_args(node, "io-channels", 1, 0, &args);
	अगर (ret < 0) अणु
		dev_err(dev, "%s: error parsing ADC channel number %d: %d\n", name, chan, ret);
		वापस ret;
	पूर्ण
	of_node_put(args.np);

	अगर (args.args_count != 1 || args.args[0] >= ADC5_MAX_CHANNEL) अणु
		dev_err(dev, "%s: invalid ADC channel number %d\n", name, chan);
		वापस -EINVAL;
	पूर्ण
	channel->adc_channel = args.args[0];

	channel->iio = devm_of_iio_channel_get_by_name(adc_पंचांग->dev, node, शून्य);
	अगर (IS_ERR(channel->iio)) अणु
		ret = PTR_ERR(channel->iio);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "%s: error getting channel: %d\n", name, ret);
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32_array(node, "qcom,pre-scaling", varr, 2);
	अगर (!ret) अणु
		ret = qcom_adc5_prescaling_from_dt(varr[0], varr[1]);
		अगर (ret < 0) अणु
			dev_err(dev, "%s: invalid pre-scaling <%d %d>\n",
				name, varr[0], varr[1]);
			वापस ret;
		पूर्ण
		channel->prescale = ret;
	पूर्ण अन्यथा अणु
		/* 1:1 prescale is index 0 */
		channel->prescale = 0;
	पूर्ण

	ret = of_property_पढ़ो_u32(node, "qcom,hw-settle-time-us", &value);
	अगर (!ret) अणु
		ret = qcom_adc5_hw_settle_समय_from_dt(value, adc_पंचांग->data->hw_settle);
		अगर (ret < 0) अणु
			dev_err(dev, "%s invalid hw-settle-time-us %d us\n",
				name, value);
			वापस ret;
		पूर्ण
		channel->hw_settle_समय = ret;
	पूर्ण अन्यथा अणु
		channel->hw_settle_समय = VADC_DEF_HW_SETTLE_TIME;
	पूर्ण

	अगर (of_property_पढ़ो_bool(node, "qcom,ratiometric"))
		channel->cal_method = ADC_TM5_RATIOMETRIC_CAL;
	अन्यथा
		channel->cal_method = ADC_TM5_ABSOLUTE_CAL;

	वापस 0;
पूर्ण

अटल पूर्णांक adc_पंचांग5_get_dt_data(काष्ठा adc_पंचांग5_chip *adc_पंचांग, काष्ठा device_node *node)
अणु
	काष्ठा adc_पंचांग5_channel *channels;
	काष्ठा device_node *child;
	u32 value;
	पूर्णांक ret;
	काष्ठा device *dev = adc_पंचांग->dev;

	adc_पंचांग->nchannels = of_get_available_child_count(node);
	अगर (!adc_पंचांग->nchannels)
		वापस -EINVAL;

	adc_पंचांग->channels = devm_kसुस्मृति(dev, adc_पंचांग->nchannels,
					माप(*adc_पंचांग->channels), GFP_KERNEL);
	अगर (!adc_पंचांग->channels)
		वापस -ENOMEM;

	channels = adc_पंचांग->channels;

	adc_पंचांग->data = of_device_get_match_data(dev);
	अगर (!adc_पंचांग->data)
		adc_पंचांग->data = &adc_पंचांग5_data_pmic;

	ret = of_property_पढ़ो_u32(node, "qcom,decimation", &value);
	अगर (!ret) अणु
		ret = qcom_adc5_decimation_from_dt(value, adc_पंचांग->data->decimation);
		अगर (ret < 0) अणु
			dev_err(dev, "invalid decimation %d\n", value);
			वापस ret;
		पूर्ण
		adc_पंचांग->decimation = ret;
	पूर्ण अन्यथा अणु
		adc_पंचांग->decimation = ADC5_DECIMATION_DEFAULT;
	पूर्ण

	ret = of_property_पढ़ो_u32(node, "qcom,avg-samples", &value);
	अगर (!ret) अणु
		ret = qcom_adc5_avg_samples_from_dt(value);
		अगर (ret < 0) अणु
			dev_err(dev, "invalid avg-samples %d\n", value);
			वापस ret;
		पूर्ण
		adc_पंचांग->avg_samples = ret;
	पूर्ण अन्यथा अणु
		adc_पंचांग->avg_samples = VADC_DEF_AVG_SAMPLES;
	पूर्ण

	क्रम_each_available_child_of_node(node, child) अणु
		ret = adc_पंचांग5_get_dt_channel_data(adc_पंचांग, channels, child);
		अगर (ret) अणु
			of_node_put(child);
			वापस ret;
		पूर्ण

		channels++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adc_पंचांग5_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा adc_पंचांग5_chip *adc_पंचांग;
	काष्ठा regmap *regmap;
	पूर्णांक ret, irq;
	u32 reg;

	regmap = dev_get_regmap(dev->parent, शून्य);
	अगर (!regmap)
		वापस -ENODEV;

	ret = of_property_पढ़ो_u32(node, "reg", &reg);
	अगर (ret)
		वापस ret;

	adc_पंचांग = devm_kzalloc(&pdev->dev, माप(*adc_पंचांग), GFP_KERNEL);
	अगर (!adc_पंचांग)
		वापस -ENOMEM;

	adc_पंचांग->regmap = regmap;
	adc_पंचांग->dev = dev;
	adc_पंचांग->base = reg;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		dev_err(dev, "get_irq failed: %d\n", irq);
		वापस irq;
	पूर्ण

	ret = adc_पंचांग5_get_dt_data(adc_पंचांग, node);
	अगर (ret) अणु
		dev_err(dev, "get dt data failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = adc_पंचांग5_init(adc_पंचांग);
	अगर (ret) अणु
		dev_err(dev, "adc-tm init failed\n");
		वापस ret;
	पूर्ण

	ret = adc_पंचांग5_रेजिस्टर_tzd(adc_पंचांग);
	अगर (ret) अणु
		dev_err(dev, "tzd register failed\n");
		वापस ret;
	पूर्ण

	वापस devm_request_thपढ़ोed_irq(dev, irq, शून्य, adc_पंचांग5_isr,
					 IRQF_ONESHOT, "pm-adc-tm5", adc_पंचांग);
पूर्ण

अटल स्थिर काष्ठा of_device_id adc_पंचांग5_match_table[] = अणु
	अणु
		.compatible = "qcom,spmi-adc-tm5",
		.data = &adc_पंचांग5_data_pmic,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, adc_पंचांग5_match_table);

अटल काष्ठा platक्रमm_driver adc_पंचांग5_driver = अणु
	.driver = अणु
		.name = "qcom-spmi-adc-tm5",
		.of_match_table = adc_पंचांग5_match_table,
	पूर्ण,
	.probe = adc_पंचांग5_probe,
पूर्ण;
module_platक्रमm_driver(adc_पंचांग5_driver);

MODULE_DESCRIPTION("SPMI PMIC Thermal Monitor ADC driver");
MODULE_LICENSE("GPL v2");
