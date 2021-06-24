<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ADC driver क्रम the RICOH RN5T618 घातer management chip family
 *
 * Copyright (C) 2019 Andreas Kemnade
 */

#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mfd/rn5t618.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/completion.h>
#समावेश <linux/regmap.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/slab.h>

#घोषणा RN5T618_ADC_CONVERSION_TIMEOUT   (msecs_to_jअगरfies(500))
#घोषणा RN5T618_REFERENCE_VOLT 2500

/* mask क्रम selecting channels क्रम single conversion */
#घोषणा RN5T618_ADCCNT3_CHANNEL_MASK 0x7
/* average 4-समय conversion mode */
#घोषणा RN5T618_ADCCNT3_AVG BIT(3)
/* set क्रम starting a single conversion, माला_लो cleared by hw when करोne */
#घोषणा RN5T618_ADCCNT3_GODONE BIT(4)
/* स्वतःmatic conversion, period is in ADCCNT2, selected channels are
 * in ADCCNT1
 */
#घोषणा RN5T618_ADCCNT3_AUTO BIT(5)
#घोषणा RN5T618_ADCEND_IRQ BIT(0)

काष्ठा rn5t618_adc_data अणु
	काष्ठा device *dev;
	काष्ठा rn5t618 *rn5t618;
	काष्ठा completion conv_completion;
	पूर्णांक irq;
पूर्ण;

काष्ठा rn5t618_channel_ratios अणु
	u16 numerator;
	u16 denominator;
पूर्ण;

क्रमागत rn5t618_channels अणु
	LIMMON = 0,
	VBAT,
	VADP,
	VUSB,
	VSYS,
	VTHM,
	AIN1,
	AIN0
पूर्ण;

अटल स्थिर काष्ठा rn5t618_channel_ratios rn5t618_ratios[8] = अणु
	[LIMMON] = अणु50, 32पूर्ण, /* measured across 20mOhm, amplअगरied by 32 */
	[VBAT] = अणु2, 1पूर्ण,
	[VADP] = अणु3, 1पूर्ण,
	[VUSB] = अणु3, 1पूर्ण,
	[VSYS] = अणु3, 1पूर्ण,
	[VTHM] = अणु1, 1पूर्ण,
	[AIN1] = अणु1, 1पूर्ण,
	[AIN0] = अणु1, 1पूर्ण,
पूर्ण;

अटल पूर्णांक rn5t618_पढ़ो_adc_reg(काष्ठा rn5t618 *rn5t618, पूर्णांक reg, u16 *val)
अणु
	u8 data[2];
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(rn5t618->regmap, reg, data, माप(data));
	अगर (ret < 0)
		वापस ret;

	*val = (data[0] << 4) | (data[1] & 0xF);

	वापस 0;
पूर्ण

अटल irqवापस_t rn5t618_adc_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा rn5t618_adc_data *adc = data;
	अचिन्हित पूर्णांक r = 0;
	पूर्णांक ret;

	/* clear low & high threshold irqs */
	regmap_ग_लिखो(adc->rn5t618->regmap, RN5T618_IR_ADC1, 0);
	regmap_ग_लिखो(adc->rn5t618->regmap, RN5T618_IR_ADC2, 0);

	ret = regmap_पढ़ो(adc->rn5t618->regmap, RN5T618_IR_ADC3, &r);
	अगर (ret < 0)
		dev_err(adc->dev, "failed to read IRQ status: %d\n", ret);

	regmap_ग_लिखो(adc->rn5t618->regmap, RN5T618_IR_ADC3, 0);

	अगर (r & RN5T618_ADCEND_IRQ)
		complete(&adc->conv_completion);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rn5t618_adc_पढ़ो(काष्ठा iio_dev *iio_dev,
			    स्थिर काष्ठा iio_chan_spec *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा rn5t618_adc_data *adc = iio_priv(iio_dev);
	u16 raw;
	पूर्णांक ret;

	अगर (mask == IIO_CHAN_INFO_SCALE) अणु
		*val = RN5T618_REFERENCE_VOLT *
		       rn5t618_ratios[chan->channel].numerator;
		*val2 = rn5t618_ratios[chan->channel].denominator * 4095;

		वापस IIO_VAL_FRACTIONAL;
	पूर्ण

	/* select channel */
	ret = regmap_update_bits(adc->rn5t618->regmap, RN5T618_ADCCNT3,
				 RN5T618_ADCCNT3_CHANNEL_MASK,
				 chan->channel);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(adc->rn5t618->regmap, RN5T618_EN_ADCIR3,
			   RN5T618_ADCEND_IRQ);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_update_bits(adc->rn5t618->regmap, RN5T618_ADCCNT3,
				 RN5T618_ADCCNT3_AVG,
				 mask == IIO_CHAN_INFO_AVERAGE_RAW ?
				 RN5T618_ADCCNT3_AVG : 0);
	अगर (ret < 0)
		वापस ret;

	init_completion(&adc->conv_completion);
	/* single conversion */
	ret = regmap_update_bits(adc->rn5t618->regmap, RN5T618_ADCCNT3,
				 RN5T618_ADCCNT3_GODONE,
				 RN5T618_ADCCNT3_GODONE);
	अगर (ret < 0)
		वापस ret;

	ret = रुको_क्रम_completion_समयout(&adc->conv_completion,
					  RN5T618_ADC_CONVERSION_TIMEOUT);
	अगर (ret == 0) अणु
		dev_warn(adc->dev, "timeout waiting for adc result\n");
		वापस -ETIMEDOUT;
	पूर्ण

	ret = rn5t618_पढ़ो_adc_reg(adc->rn5t618,
				   RN5T618_ILIMDATAH + 2 * chan->channel,
				   &raw);
	अगर (ret < 0)
		वापस ret;

	*val = raw;

	वापस IIO_VAL_INT;
पूर्ण

अटल स्थिर काष्ठा iio_info rn5t618_adc_iio_info = अणु
	.पढ़ो_raw = &rn5t618_adc_पढ़ो,
पूर्ण;

#घोषणा RN5T618_ADC_CHANNEL(_channel, _type, _name) अणु \
	.type = _type, \
	.channel = _channel, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | \
			      BIT(IIO_CHAN_INFO_AVERAGE_RAW) | \
			      BIT(IIO_CHAN_INFO_SCALE), \
	.datasheet_name = _name, \
	.indexed = 1. \
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec rn5t618_adc_iio_channels[] = अणु
	RN5T618_ADC_CHANNEL(LIMMON, IIO_CURRENT, "LIMMON"),
	RN5T618_ADC_CHANNEL(VBAT, IIO_VOLTAGE, "VBAT"),
	RN5T618_ADC_CHANNEL(VADP, IIO_VOLTAGE, "VADP"),
	RN5T618_ADC_CHANNEL(VUSB, IIO_VOLTAGE, "VUSB"),
	RN5T618_ADC_CHANNEL(VSYS, IIO_VOLTAGE, "VSYS"),
	RN5T618_ADC_CHANNEL(VTHM, IIO_VOLTAGE, "VTHM"),
	RN5T618_ADC_CHANNEL(AIN1, IIO_VOLTAGE, "AIN1"),
	RN5T618_ADC_CHANNEL(AIN0, IIO_VOLTAGE, "AIN0")
पूर्ण;

अटल पूर्णांक rn5t618_adc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा iio_dev *iio_dev;
	काष्ठा rn5t618_adc_data *adc;
	काष्ठा rn5t618 *rn5t618 = dev_get_drvdata(pdev->dev.parent);

	iio_dev = devm_iio_device_alloc(&pdev->dev, माप(*adc));
	अगर (!iio_dev) अणु
		dev_err(&pdev->dev, "failed allocating iio device\n");
		वापस -ENOMEM;
	पूर्ण

	adc = iio_priv(iio_dev);
	adc->dev = &pdev->dev;
	adc->rn5t618 = rn5t618;

	अगर (rn5t618->irq_data)
		adc->irq = regmap_irq_get_virq(rn5t618->irq_data,
					       RN5T618_IRQ_ADC);

	अगर (adc->irq <= 0) अणु
		dev_err(&pdev->dev, "get virq failed\n");
		वापस -EINVAL;
	पूर्ण

	init_completion(&adc->conv_completion);

	iio_dev->name = dev_name(&pdev->dev);
	iio_dev->info = &rn5t618_adc_iio_info;
	iio_dev->modes = INDIO_सूचीECT_MODE;
	iio_dev->channels = rn5t618_adc_iio_channels;
	iio_dev->num_channels = ARRAY_SIZE(rn5t618_adc_iio_channels);

	/* stop any स्वतः-conversion */
	ret = regmap_ग_लिखो(rn5t618->regmap, RN5T618_ADCCNT3, 0);
	अगर (ret < 0)
		वापस ret;

	platक्रमm_set_drvdata(pdev, iio_dev);

	ret = devm_request_thपढ़ोed_irq(adc->dev, adc->irq, शून्य,
					rn5t618_adc_irq,
					IRQF_ONESHOT, dev_name(adc->dev),
					adc);
	अगर (ret < 0) अणु
		dev_err(adc->dev, "request irq %d failed: %d\n", adc->irq, ret);
		वापस ret;
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(adc->dev, iio_dev);
पूर्ण

अटल काष्ठा platक्रमm_driver rn5t618_adc_driver = अणु
	.driver = अणु
		.name   = "rn5t618-adc",
	पूर्ण,
	.probe = rn5t618_adc_probe,
पूर्ण;

module_platक्रमm_driver(rn5t618_adc_driver);
MODULE_ALIAS("platform:rn5t618-adc");
MODULE_DESCRIPTION("RICOH RN5T618 ADC driver");
MODULE_LICENSE("GPL");
