<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012-2014, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mutex.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

/* IADC रेजिस्टर and bit definition */
#घोषणा IADC_REVISION2				0x1
#घोषणा IADC_REVISION2_SUPPORTED_IADC		1

#घोषणा IADC_PERPH_TYPE				0x4
#घोषणा IADC_PERPH_TYPE_ADC			8

#घोषणा IADC_PERPH_SUBTYPE			0x5
#घोषणा IADC_PERPH_SUBTYPE_IADC			3

#घोषणा IADC_STATUS1				0x8
#घोषणा IADC_STATUS1_OP_MODE			4
#घोषणा IADC_STATUS1_REQ_STS			BIT(1)
#घोषणा IADC_STATUS1_EOC			BIT(0)
#घोषणा IADC_STATUS1_REQ_STS_EOC_MASK		0x3

#घोषणा IADC_MODE_CTL				0x40
#घोषणा IADC_OP_MODE_SHIFT			3
#घोषणा IADC_OP_MODE_NORMAL			0
#घोषणा IADC_TRIM_EN				BIT(0)

#घोषणा IADC_EN_CTL1				0x46
#घोषणा IADC_EN_CTL1_SET			BIT(7)

#घोषणा IADC_CH_SEL_CTL				0x48

#घोषणा IADC_DIG_PARAM				0x50
#घोषणा IADC_DIG_DEC_RATIO_SEL_SHIFT		2

#घोषणा IADC_HW_SETTLE_DELAY			0x51

#घोषणा IADC_CONV_REQ				0x52
#घोषणा IADC_CONV_REQ_SET			BIT(7)

#घोषणा IADC_FAST_AVG_CTL			0x5a
#घोषणा IADC_FAST_AVG_EN			0x5b
#घोषणा IADC_FAST_AVG_EN_SET			BIT(7)

#घोषणा IADC_PERH_RESET_CTL3			0xda
#घोषणा IADC_FOLLOW_WARM_RB			BIT(2)

#घोषणा IADC_DATA				0x60	/* 16 bits */

#घोषणा IADC_SEC_ACCESS				0xd0
#घोषणा IADC_SEC_ACCESS_DATA			0xa5

#घोषणा IADC_NOMINAL_RSENSE			0xf4
#घोषणा IADC_NOMINAL_RSENSE_SIGN_MASK		BIT(7)

#घोषणा IADC_REF_GAIN_MICRO_VOLTS		17857

#घोषणा IADC_INT_RSENSE_DEVIATION		15625	/* nano Ohms per bit */

#घोषणा IADC_INT_RSENSE_IDEAL_VALUE		10000	/* micro Ohms */
#घोषणा IADC_INT_RSENSE_DEFAULT_VALUE		7800	/* micro Ohms */
#घोषणा IADC_INT_RSENSE_DEFAULT_GF		9000	/* micro Ohms */
#घोषणा IADC_INT_RSENSE_DEFAULT_SMIC		9700	/* micro Ohms */

#घोषणा IADC_CONV_TIME_MIN_US			2000
#घोषणा IADC_CONV_TIME_MAX_US			2100

#घोषणा IADC_DEF_PRESCALING			0 /* 1:1 */
#घोषणा IADC_DEF_DECIMATION			0 /* 512 */
#घोषणा IADC_DEF_HW_SETTLE_TIME			0 /* 0 us */
#घोषणा IADC_DEF_AVG_SAMPLES			0 /* 1 sample */

/* IADC channel list */
#घोषणा IADC_INT_RSENSE				0
#घोषणा IADC_EXT_RSENSE				1
#घोषणा IADC_GAIN_17P857MV			3
#घोषणा IADC_EXT_OFFSET_CSP_CSN			5
#घोषणा IADC_INT_OFFSET_CSP2_CSN2		6

/**
 * काष्ठा iadc_chip - IADC Current ADC device काष्ठाure.
 * @regmap: regmap क्रम रेजिस्टर पढ़ो/ग_लिखो.
 * @dev: This device poपूर्णांकer.
 * @base: base offset क्रम the ADC peripheral.
 * @rsense: Values of the पूर्णांकernal and बाह्यal sense resister in micro Ohms.
 * @poll_eoc: Poll क्रम end of conversion instead of रुकोing क्रम IRQ.
 * @offset: Raw offset values क्रम the पूर्णांकernal and बाह्यal channels.
 * @gain: Raw gain of the channels.
 * @lock: ADC lock क्रम access to the peripheral.
 * @complete: ADC notअगरication after end of conversion पूर्णांकerrupt is received.
 */
काष्ठा iadc_chip अणु
	काष्ठा regmap	*regmap;
	काष्ठा device	*dev;
	u16		base;
	bool		poll_eoc;
	u32		rsense[2];
	u16		offset[2];
	u16		gain;
	काष्ठा mutex	lock;
	काष्ठा completion complete;
पूर्ण;

अटल पूर्णांक iadc_पढ़ो(काष्ठा iadc_chip *iadc, u16 offset, u8 *data)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(iadc->regmap, iadc->base + offset, &val);
	अगर (ret < 0)
		वापस ret;

	*data = val;
	वापस 0;
पूर्ण

अटल पूर्णांक iadc_ग_लिखो(काष्ठा iadc_chip *iadc, u16 offset, u8 data)
अणु
	वापस regmap_ग_लिखो(iadc->regmap, iadc->base + offset, data);
पूर्ण

अटल पूर्णांक iadc_reset(काष्ठा iadc_chip *iadc)
अणु
	u8 data;
	पूर्णांक ret;

	ret = iadc_ग_लिखो(iadc, IADC_SEC_ACCESS, IADC_SEC_ACCESS_DATA);
	अगर (ret < 0)
		वापस ret;

	ret = iadc_पढ़ो(iadc, IADC_PERH_RESET_CTL3, &data);
	अगर (ret < 0)
		वापस ret;

	ret = iadc_ग_लिखो(iadc, IADC_SEC_ACCESS, IADC_SEC_ACCESS_DATA);
	अगर (ret < 0)
		वापस ret;

	data |= IADC_FOLLOW_WARM_RB;

	वापस iadc_ग_लिखो(iadc, IADC_PERH_RESET_CTL3, data);
पूर्ण

अटल पूर्णांक iadc_set_state(काष्ठा iadc_chip *iadc, bool state)
अणु
	वापस iadc_ग_लिखो(iadc, IADC_EN_CTL1, state ? IADC_EN_CTL1_SET : 0);
पूर्ण

अटल व्योम iadc_status_show(काष्ठा iadc_chip *iadc)
अणु
	u8 mode, sta1, chan, dig, en, req;
	पूर्णांक ret;

	ret = iadc_पढ़ो(iadc, IADC_MODE_CTL, &mode);
	अगर (ret < 0)
		वापस;

	ret = iadc_पढ़ो(iadc, IADC_DIG_PARAM, &dig);
	अगर (ret < 0)
		वापस;

	ret = iadc_पढ़ो(iadc, IADC_CH_SEL_CTL, &chan);
	अगर (ret < 0)
		वापस;

	ret = iadc_पढ़ो(iadc, IADC_CONV_REQ, &req);
	अगर (ret < 0)
		वापस;

	ret = iadc_पढ़ो(iadc, IADC_STATUS1, &sta1);
	अगर (ret < 0)
		वापस;

	ret = iadc_पढ़ो(iadc, IADC_EN_CTL1, &en);
	अगर (ret < 0)
		वापस;

	dev_err(iadc->dev,
		"mode:%02x en:%02x chan:%02x dig:%02x req:%02x sta1:%02x\n",
		mode, en, chan, dig, req, sta1);
पूर्ण

अटल पूर्णांक iadc_configure(काष्ठा iadc_chip *iadc, पूर्णांक channel)
अणु
	u8 decim, mode;
	पूर्णांक ret;

	/* Mode selection */
	mode = (IADC_OP_MODE_NORMAL << IADC_OP_MODE_SHIFT) | IADC_TRIM_EN;
	ret = iadc_ग_लिखो(iadc, IADC_MODE_CTL, mode);
	अगर (ret < 0)
		वापस ret;

	/* Channel selection */
	ret = iadc_ग_लिखो(iadc, IADC_CH_SEL_CTL, channel);
	अगर (ret < 0)
		वापस ret;

	/* Digital parameter setup */
	decim = IADC_DEF_DECIMATION << IADC_DIG_DEC_RATIO_SEL_SHIFT;
	ret = iadc_ग_लिखो(iadc, IADC_DIG_PARAM, decim);
	अगर (ret < 0)
		वापस ret;

	/* HW settle समय delay */
	ret = iadc_ग_लिखो(iadc, IADC_HW_SETTLE_DELAY, IADC_DEF_HW_SETTLE_TIME);
	अगर (ret < 0)
		वापस ret;

	ret = iadc_ग_लिखो(iadc, IADC_FAST_AVG_CTL, IADC_DEF_AVG_SAMPLES);
	अगर (ret < 0)
		वापस ret;

	अगर (IADC_DEF_AVG_SAMPLES)
		ret = iadc_ग_लिखो(iadc, IADC_FAST_AVG_EN, IADC_FAST_AVG_EN_SET);
	अन्यथा
		ret = iadc_ग_लिखो(iadc, IADC_FAST_AVG_EN, 0);

	अगर (ret < 0)
		वापस ret;

	अगर (!iadc->poll_eoc)
		reinit_completion(&iadc->complete);

	ret = iadc_set_state(iadc, true);
	अगर (ret < 0)
		वापस ret;

	/* Request conversion */
	वापस iadc_ग_लिखो(iadc, IADC_CONV_REQ, IADC_CONV_REQ_SET);
पूर्ण

अटल पूर्णांक iadc_poll_रुको_eoc(काष्ठा iadc_chip *iadc, अचिन्हित पूर्णांक पूर्णांकerval_us)
अणु
	अचिन्हित पूर्णांक count, retry;
	पूर्णांक ret;
	u8 sta1;

	retry = पूर्णांकerval_us / IADC_CONV_TIME_MIN_US;

	क्रम (count = 0; count < retry; count++) अणु
		ret = iadc_पढ़ो(iadc, IADC_STATUS1, &sta1);
		अगर (ret < 0)
			वापस ret;

		sta1 &= IADC_STATUS1_REQ_STS_EOC_MASK;
		अगर (sta1 == IADC_STATUS1_EOC)
			वापस 0;

		usleep_range(IADC_CONV_TIME_MIN_US, IADC_CONV_TIME_MAX_US);
	पूर्ण

	iadc_status_show(iadc);

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक iadc_पढ़ो_result(काष्ठा iadc_chip *iadc, u16 *data)
अणु
	वापस regmap_bulk_पढ़ो(iadc->regmap, iadc->base + IADC_DATA, data, 2);
पूर्ण

अटल पूर्णांक iadc_करो_conversion(काष्ठा iadc_chip *iadc, पूर्णांक chan, u16 *data)
अणु
	अचिन्हित पूर्णांक रुको;
	पूर्णांक ret;

	ret = iadc_configure(iadc, chan);
	अगर (ret < 0)
		जाओ निकास;

	रुको = BIT(IADC_DEF_AVG_SAMPLES) * IADC_CONV_TIME_MIN_US * 2;

	अगर (iadc->poll_eoc) अणु
		ret = iadc_poll_रुको_eoc(iadc, रुको);
	पूर्ण अन्यथा अणु
		ret = रुको_क्रम_completion_समयout(&iadc->complete,
			usecs_to_jअगरfies(रुको));
		अगर (!ret)
			ret = -ETIMEDOUT;
		अन्यथा
			/* द्विगुन check conversion status */
			ret = iadc_poll_रुको_eoc(iadc, IADC_CONV_TIME_MIN_US);
	पूर्ण

	अगर (!ret)
		ret = iadc_पढ़ो_result(iadc, data);
निकास:
	iadc_set_state(iadc, false);
	अगर (ret < 0)
		dev_err(iadc->dev, "conversion failed\n");

	वापस ret;
पूर्ण

अटल पूर्णांक iadc_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			 काष्ठा iio_chan_spec स्थिर *chan,
			 पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा iadc_chip *iadc = iio_priv(indio_dev);
	s32 isense_ua, vsense_uv;
	u16 adc_raw, vsense_raw;
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&iadc->lock);
		ret = iadc_करो_conversion(iadc, chan->channel, &adc_raw);
		mutex_unlock(&iadc->lock);
		अगर (ret < 0)
			वापस ret;

		vsense_raw = adc_raw - iadc->offset[chan->channel];

		vsense_uv = vsense_raw * IADC_REF_GAIN_MICRO_VOLTS;
		vsense_uv /= (s32)iadc->gain - iadc->offset[chan->channel];

		isense_ua = vsense_uv / iadc->rsense[chan->channel];

		dev_dbg(iadc->dev, "off %d gain %d adc %d %duV I %duA\n",
			iadc->offset[chan->channel], iadc->gain,
			adc_raw, vsense_uv, isense_ua);

		*val = isense_ua;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = 0;
		*val2 = 1000;
		वापस IIO_VAL_INT_PLUS_MICRO;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info iadc_info = अणु
	.पढ़ो_raw = iadc_पढ़ो_raw,
पूर्ण;

अटल irqवापस_t iadc_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा iadc_chip *iadc = dev_id;

	complete(&iadc->complete);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक iadc_update_offset(काष्ठा iadc_chip *iadc)
अणु
	पूर्णांक ret;

	ret = iadc_करो_conversion(iadc, IADC_GAIN_17P857MV, &iadc->gain);
	अगर (ret < 0)
		वापस ret;

	ret = iadc_करो_conversion(iadc, IADC_INT_OFFSET_CSP2_CSN2,
				 &iadc->offset[IADC_INT_RSENSE]);
	अगर (ret < 0)
		वापस ret;

	अगर (iadc->gain == iadc->offset[IADC_INT_RSENSE]) अणु
		dev_err(iadc->dev, "error: internal offset == gain %d\n",
			iadc->gain);
		वापस -EINVAL;
	पूर्ण

	ret = iadc_करो_conversion(iadc, IADC_EXT_OFFSET_CSP_CSN,
				 &iadc->offset[IADC_EXT_RSENSE]);
	अगर (ret < 0)
		वापस ret;

	अगर (iadc->gain == iadc->offset[IADC_EXT_RSENSE]) अणु
		dev_err(iadc->dev, "error: external offset == gain %d\n",
			iadc->gain);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iadc_version_check(काष्ठा iadc_chip *iadc)
अणु
	u8 val;
	पूर्णांक ret;

	ret = iadc_पढ़ो(iadc, IADC_PERPH_TYPE, &val);
	अगर (ret < 0)
		वापस ret;

	अगर (val < IADC_PERPH_TYPE_ADC) अणु
		dev_err(iadc->dev, "%d is not ADC\n", val);
		वापस -EINVAL;
	पूर्ण

	ret = iadc_पढ़ो(iadc, IADC_PERPH_SUBTYPE, &val);
	अगर (ret < 0)
		वापस ret;

	अगर (val < IADC_PERPH_SUBTYPE_IADC) अणु
		dev_err(iadc->dev, "%d is not IADC\n", val);
		वापस -EINVAL;
	पूर्ण

	ret = iadc_पढ़ो(iadc, IADC_REVISION2, &val);
	अगर (ret < 0)
		वापस ret;

	अगर (val < IADC_REVISION2_SUPPORTED_IADC) अणु
		dev_err(iadc->dev, "revision %d not supported\n", val);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iadc_rsense_पढ़ो(काष्ठा iadc_chip *iadc, काष्ठा device_node *node)
अणु
	पूर्णांक ret, sign, पूर्णांक_sense;
	u8 deviation;

	ret = of_property_पढ़ो_u32(node, "qcom,external-resistor-micro-ohms",
				   &iadc->rsense[IADC_EXT_RSENSE]);
	अगर (ret < 0)
		iadc->rsense[IADC_EXT_RSENSE] = IADC_INT_RSENSE_IDEAL_VALUE;

	अगर (!iadc->rsense[IADC_EXT_RSENSE]) अणु
		dev_err(iadc->dev, "external resistor can't be zero Ohms");
		वापस -EINVAL;
	पूर्ण

	ret = iadc_पढ़ो(iadc, IADC_NOMINAL_RSENSE, &deviation);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Deviation value stored is an offset from 10 mili Ohms, bit 7 is
	 * the sign, the reमुख्यing bits have an LSB of 15625 nano Ohms.
	 */
	sign = (deviation & IADC_NOMINAL_RSENSE_SIGN_MASK) ? -1 : 1;

	deviation &= ~IADC_NOMINAL_RSENSE_SIGN_MASK;

	/* Scale it to nono Ohms */
	पूर्णांक_sense = IADC_INT_RSENSE_IDEAL_VALUE * 1000;
	पूर्णांक_sense += sign * deviation * IADC_INT_RSENSE_DEVIATION;
	पूर्णांक_sense /= 1000; /* micro Ohms */

	iadc->rsense[IADC_INT_RSENSE] = पूर्णांक_sense;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec iadc_channels[] = अणु
	अणु
		.type = IIO_CURRENT,
		.datasheet_name	= "INTERNAL_RSENSE",
		.channel = 0,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE),
		.indexed = 1,
	पूर्ण,
	अणु
		.type = IIO_CURRENT,
		.datasheet_name	= "EXTERNAL_RSENSE",
		.channel = 1,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE),
		.indexed = 1,
	पूर्ण,
पूर्ण;

अटल पूर्णांक iadc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा iio_dev *indio_dev;
	काष्ठा iadc_chip *iadc;
	पूर्णांक ret, irq_eoc;
	u32 res;

	indio_dev = devm_iio_device_alloc(dev, माप(*iadc));
	अगर (!indio_dev)
		वापस -ENOMEM;

	iadc = iio_priv(indio_dev);
	iadc->dev = dev;

	iadc->regmap = dev_get_regmap(dev->parent, शून्य);
	अगर (!iadc->regmap)
		वापस -ENODEV;

	init_completion(&iadc->complete);
	mutex_init(&iadc->lock);

	ret = of_property_पढ़ो_u32(node, "reg", &res);
	अगर (ret < 0)
		वापस -ENODEV;

	iadc->base = res;

	ret = iadc_version_check(iadc);
	अगर (ret < 0)
		वापस -ENODEV;

	ret = iadc_rsense_पढ़ो(iadc, node);
	अगर (ret < 0)
		वापस -ENODEV;

	dev_dbg(iadc->dev, "sense resistors %d and %d micro Ohm\n",
		iadc->rsense[IADC_INT_RSENSE],
		iadc->rsense[IADC_EXT_RSENSE]);

	irq_eoc = platक्रमm_get_irq(pdev, 0);
	अगर (irq_eoc == -EPROBE_DEFER)
		वापस irq_eoc;

	अगर (irq_eoc < 0)
		iadc->poll_eoc = true;

	ret = iadc_reset(iadc);
	अगर (ret < 0) अणु
		dev_err(dev, "reset failed\n");
		वापस ret;
	पूर्ण

	अगर (!iadc->poll_eoc) अणु
		ret = devm_request_irq(dev, irq_eoc, iadc_isr, 0,
					"spmi-iadc", iadc);
		अगर (!ret)
			enable_irq_wake(irq_eoc);
		अन्यथा
			वापस ret;
	पूर्ण अन्यथा अणु
		device_init_wakeup(iadc->dev, 1);
	पूर्ण

	ret = iadc_update_offset(iadc);
	अगर (ret < 0) अणु
		dev_err(dev, "failed offset calibration\n");
		वापस ret;
	पूर्ण

	indio_dev->name = pdev->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &iadc_info;
	indio_dev->channels = iadc_channels;
	indio_dev->num_channels = ARRAY_SIZE(iadc_channels);

	वापस devm_iio_device_रेजिस्टर(dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id iadc_match_table[] = अणु
	अणु .compatible = "qcom,spmi-iadc" पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, iadc_match_table);

अटल काष्ठा platक्रमm_driver iadc_driver = अणु
	.driver = अणु
		   .name = "qcom-spmi-iadc",
		   .of_match_table = iadc_match_table,
	पूर्ण,
	.probe = iadc_probe,
पूर्ण;

module_platक्रमm_driver(iadc_driver);

MODULE_ALIAS("platform:qcom-spmi-iadc");
MODULE_DESCRIPTION("Qualcomm SPMI PMIC current ADC driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Ivan T. Ivanov <iivanov@mm-sol.com>");
