<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MEN 16z188 Analog to Digial Converter
 *
 * Copyright (C) 2014 MEN Mikroelektronik GmbH (www.men.de)
 * Author: Johannes Thumshirn <johannes.thumshirn@men.de>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mcb.h>
#समावेश <linux/पन.स>
#समावेश <linux/iio/iपन.स>

#घोषणा Z188_ADC_MAX_CHAN	8
#घोषणा Z188_ADC_GAIN		0x0700000
#घोषणा Z188_MODE_VOLTAGE	BIT(27)
#घोषणा Z188_CFG_AUTO		0x1
#घोषणा Z188_CTRL_REG		0x40

#घोषणा ADC_DATA(x) (((x) >> 2) & 0x7ffffc)
#घोषणा ADC_OVR(x) ((x) & 0x1)

काष्ठा z188_adc अणु
	काष्ठा resource *mem;
	व्योम __iomem *base;
पूर्ण;

#घोषणा Z188_ADC_CHANNEL(idx) अणु					\
		.type = IIO_VOLTAGE,				\
		.indexed = 1,					\
		.channel = (idx),				\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),   \
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec z188_adc_iio_channels[] = अणु
	Z188_ADC_CHANNEL(0),
	Z188_ADC_CHANNEL(1),
	Z188_ADC_CHANNEL(2),
	Z188_ADC_CHANNEL(3),
	Z188_ADC_CHANNEL(4),
	Z188_ADC_CHANNEL(5),
	Z188_ADC_CHANNEL(6),
	Z188_ADC_CHANNEL(7),
पूर्ण;

अटल पूर्णांक z188_iio_पढ़ो_raw(काष्ठा iio_dev *iio_dev,
			काष्ठा iio_chan_spec स्थिर *chan,
			पूर्णांक *val,
			पूर्णांक *val2,
			दीर्घ info)
अणु
	काष्ठा z188_adc *adc = iio_priv(iio_dev);
	पूर्णांक ret;
	u16 पंचांगp;

	चयन (info) अणु
	हाल IIO_CHAN_INFO_RAW:
		पंचांगp = पढ़ोw(adc->base + chan->channel * 4);

		अगर (ADC_OVR(पंचांगp)) अणु
			dev_info(&iio_dev->dev,
				"Oversampling error on ADC channel %d\n",
				chan->channel);
			वापस -EIO;
		पूर्ण
		*val = ADC_DATA(पंचांगp);
		ret = IIO_VAL_INT;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info z188_adc_info = अणु
	.पढ़ो_raw = &z188_iio_पढ़ो_raw,
पूर्ण;

अटल व्योम men_z188_config_channels(व्योम __iomem *addr)
अणु
	पूर्णांक i;
	u32 cfg;
	u32 ctl;

	ctl = पढ़ोl(addr + Z188_CTRL_REG);
	ctl |= Z188_CFG_AUTO;
	ग_लिखोl(ctl, addr + Z188_CTRL_REG);

	क्रम (i = 0; i < Z188_ADC_MAX_CHAN; i++) अणु
		cfg = पढ़ोl(addr + i);
		cfg &= ~Z188_ADC_GAIN;
		cfg |= Z188_MODE_VOLTAGE;
		ग_लिखोl(cfg, addr + i);
	पूर्ण
पूर्ण

अटल पूर्णांक men_z188_probe(काष्ठा mcb_device *dev,
			स्थिर काष्ठा mcb_device_id *id)
अणु
	काष्ठा z188_adc *adc;
	काष्ठा iio_dev *indio_dev;
	काष्ठा resource *mem;

	indio_dev = devm_iio_device_alloc(&dev->dev, माप(काष्ठा z188_adc));
	अगर (!indio_dev)
		वापस -ENOMEM;

	adc = iio_priv(indio_dev);
	indio_dev->name = "z188-adc";
	indio_dev->info = &z188_adc_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = z188_adc_iio_channels;
	indio_dev->num_channels = ARRAY_SIZE(z188_adc_iio_channels);

	mem = mcb_request_mem(dev, "z188-adc");
	अगर (IS_ERR(mem))
		वापस PTR_ERR(mem);

	adc->base = ioremap(mem->start, resource_size(mem));
	अगर (adc->base == शून्य)
		जाओ err;

	men_z188_config_channels(adc->base);

	adc->mem = mem;
	mcb_set_drvdata(dev, indio_dev);

	वापस iio_device_रेजिस्टर(indio_dev);

err:
	mcb_release_mem(mem);
	वापस -ENXIO;
पूर्ण

अटल व्योम men_z188_हटाओ(काष्ठा mcb_device *dev)
अणु
	काष्ठा iio_dev *indio_dev  = mcb_get_drvdata(dev);
	काष्ठा z188_adc *adc = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	iounmap(adc->base);
	mcb_release_mem(adc->mem);
पूर्ण

अटल स्थिर काष्ठा mcb_device_id men_z188_ids[] = अणु
	अणु .device = 0xbc पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(mcb, men_z188_ids);

अटल काष्ठा mcb_driver men_z188_driver = अणु
	.driver = अणु
		.name = "z188-adc",
		.owner = THIS_MODULE,
	पूर्ण,
	.probe = men_z188_probe,
	.हटाओ = men_z188_हटाओ,
	.id_table = men_z188_ids,
पूर्ण;
module_mcb_driver(men_z188_driver);

MODULE_AUTHOR("Johannes Thumshirn <johannes.thumshirn@men.de>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("IIO ADC driver for MEN 16z188 ADC Core");
MODULE_ALIAS("mcb:16z188");
MODULE_IMPORT_NS(MCB);
