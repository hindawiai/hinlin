<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ADC driver क्रम Basin Cove PMIC
 *
 * Copyright (C) 2012 Intel Corporation
 * Author: Bin Yang <bin.yang@पूर्णांकel.com>
 *
 * Rewritten क्रम upstream by:
 *	 Vincent Pelletier <plr.vincent@gmail.com>
 *	 Andy Shevchenko <andriy.shevchenko@linux.पूर्णांकel.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/completion.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/पूर्णांकel_soc_pmic.h>
#समावेश <linux/mfd/पूर्णांकel_soc_pmic_mrfld.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश <linux/iio/driver.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/machine.h>

#समावेश <यंत्र/unaligned.h>

#घोषणा BCOVE_GPADCREQ			0xDC
#घोषणा BCOVE_GPADCREQ_BUSY		BIT(0)
#घोषणा BCOVE_GPADCREQ_IRQEN		BIT(1)

#घोषणा BCOVE_ADCIRQ_ALL (		\
	BCOVE_ADCIRQ_BATTEMP |		\
	BCOVE_ADCIRQ_SYSTEMP |		\
	BCOVE_ADCIRQ_BATTID |		\
	BCOVE_ADCIRQ_VIBATT |		\
	BCOVE_ADCIRQ_CCTICK)

#घोषणा BCOVE_ADC_TIMEOUT		msecs_to_jअगरfies(1000)

अटल स्थिर u8 mrfld_adc_requests[] = अणु
	BCOVE_ADCIRQ_VIBATT,
	BCOVE_ADCIRQ_BATTID,
	BCOVE_ADCIRQ_VIBATT,
	BCOVE_ADCIRQ_SYSTEMP,
	BCOVE_ADCIRQ_BATTEMP,
	BCOVE_ADCIRQ_BATTEMP,
	BCOVE_ADCIRQ_SYSTEMP,
	BCOVE_ADCIRQ_SYSTEMP,
	BCOVE_ADCIRQ_SYSTEMP,
पूर्ण;

काष्ठा mrfld_adc अणु
	काष्ठा regmap *regmap;
	काष्ठा completion completion;
	/* Lock to protect the IPC transfers */
	काष्ठा mutex lock;
पूर्ण;

अटल irqवापस_t mrfld_adc_thपढ़ो_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा iio_dev *indio_dev = data;
	काष्ठा mrfld_adc *adc = iio_priv(indio_dev);

	complete(&adc->completion);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mrfld_adc_single_conv(काष्ठा iio_dev *indio_dev,
				 काष्ठा iio_chan_spec स्थिर *chan,
				 पूर्णांक *result)
अणु
	काष्ठा mrfld_adc *adc = iio_priv(indio_dev);
	काष्ठा regmap *regmap = adc->regmap;
	अचिन्हित पूर्णांक req;
	दीर्घ समयout;
	__be16 value;
	पूर्णांक ret;

	reinit_completion(&adc->completion);

	regmap_update_bits(regmap, BCOVE_MADCIRQ, BCOVE_ADCIRQ_ALL, 0);
	regmap_update_bits(regmap, BCOVE_MIRQLVL1, BCOVE_LVL1_ADC, 0);

	ret = regmap_पढ़ो_poll_समयout(regmap, BCOVE_GPADCREQ, req,
				       !(req & BCOVE_GPADCREQ_BUSY),
				       2000, 1000000);
	अगर (ret)
		जाओ करोne;

	req = mrfld_adc_requests[chan->channel];
	ret = regmap_ग_लिखो(regmap, BCOVE_GPADCREQ, BCOVE_GPADCREQ_IRQEN | req);
	अगर (ret)
		जाओ करोne;

	समयout = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&adc->completion,
							    BCOVE_ADC_TIMEOUT);
	अगर (समयout < 0) अणु
		ret = समयout;
		जाओ करोne;
	पूर्ण
	अगर (समयout == 0) अणु
		ret = -ETIMEDOUT;
		जाओ करोne;
	पूर्ण

	ret = regmap_bulk_पढ़ो(regmap, chan->address, &value, माप(value));
	अगर (ret)
		जाओ करोne;

	*result = be16_to_cpu(value);
	ret = IIO_VAL_INT;

करोne:
	regmap_update_bits(regmap, BCOVE_MIRQLVL1, BCOVE_LVL1_ADC, 0xff);
	regmap_update_bits(regmap, BCOVE_MADCIRQ, BCOVE_ADCIRQ_ALL, 0xff);

	वापस ret;
पूर्ण

अटल पूर्णांक mrfld_adc_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan,
			      पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा mrfld_adc *adc = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&adc->lock);
		ret = mrfld_adc_single_conv(indio_dev, chan, val);
		mutex_unlock(&adc->lock);
		वापस ret;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info mrfld_adc_iio_info = अणु
	.पढ़ो_raw = &mrfld_adc_पढ़ो_raw,
पूर्ण;

#घोषणा BCOVE_ADC_CHANNEL(_type, _channel, _datasheet_name, _address)	\
	अणु								\
		.indexed = 1,						\
		.type = _type,						\
		.channel = _channel,					\
		.address = _address,					\
		.datasheet_name = _datasheet_name,			\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
	पूर्ण

अटल स्थिर काष्ठा iio_chan_spec mrfld_adc_channels[] = अणु
	BCOVE_ADC_CHANNEL(IIO_VOLTAGE,    0, "CH0", 0xE9),
	BCOVE_ADC_CHANNEL(IIO_RESISTANCE, 1, "CH1", 0xEB),
	BCOVE_ADC_CHANNEL(IIO_CURRENT,    2, "CH2", 0xED),
	BCOVE_ADC_CHANNEL(IIO_TEMP,       3, "CH3", 0xCC),
	BCOVE_ADC_CHANNEL(IIO_TEMP,       4, "CH4", 0xC8),
	BCOVE_ADC_CHANNEL(IIO_TEMP,       5, "CH5", 0xCA),
	BCOVE_ADC_CHANNEL(IIO_TEMP,       6, "CH6", 0xC2),
	BCOVE_ADC_CHANNEL(IIO_TEMP,       7, "CH7", 0xC4),
	BCOVE_ADC_CHANNEL(IIO_TEMP,       8, "CH8", 0xC6),
पूर्ण;

अटल काष्ठा iio_map iio_maps[] = अणु
	IIO_MAP("CH0", "bcove-battery", "VBATRSLT"),
	IIO_MAP("CH1", "bcove-battery", "BATTID"),
	IIO_MAP("CH2", "bcove-battery", "IBATRSLT"),
	IIO_MAP("CH3", "bcove-temp",    "PMICTEMP"),
	IIO_MAP("CH4", "bcove-temp",    "BATTEMP0"),
	IIO_MAP("CH5", "bcove-temp",    "BATTEMP1"),
	IIO_MAP("CH6", "bcove-temp",    "SYSTEMP0"),
	IIO_MAP("CH7", "bcove-temp",    "SYSTEMP1"),
	IIO_MAP("CH8", "bcove-temp",    "SYSTEMP2"),
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक mrfld_adc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा पूर्णांकel_soc_pmic *pmic = dev_get_drvdata(dev->parent);
	काष्ठा iio_dev *indio_dev;
	काष्ठा mrfld_adc *adc;
	पूर्णांक irq;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(काष्ठा mrfld_adc));
	अगर (!indio_dev)
		वापस -ENOMEM;

	adc = iio_priv(indio_dev);

	mutex_init(&adc->lock);
	init_completion(&adc->completion);
	adc->regmap = pmic->regmap;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_thपढ़ोed_irq(dev, irq, शून्य, mrfld_adc_thपढ़ो_isr,
					IRQF_ONESHOT | IRQF_SHARED, pdev->name,
					indio_dev);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, indio_dev);

	indio_dev->name = pdev->name;

	indio_dev->channels = mrfld_adc_channels;
	indio_dev->num_channels = ARRAY_SIZE(mrfld_adc_channels);
	indio_dev->info = &mrfld_adc_iio_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = iio_map_array_रेजिस्टर(indio_dev, iio_maps);
	अगर (ret)
		वापस ret;

	ret = devm_iio_device_रेजिस्टर(dev, indio_dev);
	अगर (ret < 0)
		जाओ err_array_unरेजिस्टर;

	वापस 0;

err_array_unरेजिस्टर:
	iio_map_array_unरेजिस्टर(indio_dev);
	वापस ret;
पूर्ण

अटल पूर्णांक mrfld_adc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);

	iio_map_array_unरेजिस्टर(indio_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id mrfld_adc_id_table[] = अणु
	अणु .name = "mrfld_bcove_adc" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, mrfld_adc_id_table);

अटल काष्ठा platक्रमm_driver mrfld_adc_driver = अणु
	.driver = अणु
		.name = "mrfld_bcove_adc",
	पूर्ण,
	.probe = mrfld_adc_probe,
	.हटाओ = mrfld_adc_हटाओ,
	.id_table = mrfld_adc_id_table,
पूर्ण;
module_platक्रमm_driver(mrfld_adc_driver);

MODULE_AUTHOR("Bin Yang <bin.yang@intel.com>");
MODULE_AUTHOR("Vincent Pelletier <plr.vincent@gmail.com>");
MODULE_AUTHOR("Andy Shevchenko <andriy.shevchenko@linux.intel.com>");
MODULE_DESCRIPTION("ADC driver for Basin Cove PMIC");
MODULE_LICENSE("GPL v2");
