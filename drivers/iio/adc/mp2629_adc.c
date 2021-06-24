<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MP2629 Driver क्रम ADC
 *
 * Copyright 2020 Monolithic Power Systems, Inc
 *
 * Author: Saravanan Sekar <sravanhome@gmail.com>
 */

#समावेश <linux/iio/driver.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/machine.h>
#समावेश <linux/mfd/mp2629.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#घोषणा	MP2629_REG_ADC_CTRL		0x03
#घोषणा	MP2629_REG_BATT_VOLT		0x0e
#घोषणा	MP2629_REG_SYSTEM_VOLT		0x0f
#घोषणा	MP2629_REG_INPUT_VOLT		0x11
#घोषणा	MP2629_REG_BATT_CURRENT		0x12
#घोषणा	MP2629_REG_INPUT_CURRENT	0x13

#घोषणा	MP2629_ADC_START		BIT(7)
#घोषणा	MP2629_ADC_CONTINUOUS		BIT(6)

#घोषणा MP2629_MAP(_mp, _mpc) IIO_MAP(#_mp, "mp2629_charger", "mp2629-"_mpc)

#घोषणा MP2629_ADC_CHAN(_ch, _type) अणु				\
	.type = _type,						\
	.indexed = 1,						\
	.datasheet_name = #_ch,					\
	.channel = MP2629_ ## _ch,				\
	.address = MP2629_REG_ ## _ch,				\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
पूर्ण

काष्ठा mp2629_adc अणु
	काष्ठा regmap *regmap;
	काष्ठा device *dev;
पूर्ण;

अटल काष्ठा iio_chan_spec mp2629_channels[] = अणु
	MP2629_ADC_CHAN(BATT_VOLT, IIO_VOLTAGE),
	MP2629_ADC_CHAN(SYSTEM_VOLT, IIO_VOLTAGE),
	MP2629_ADC_CHAN(INPUT_VOLT, IIO_VOLTAGE),
	MP2629_ADC_CHAN(BATT_CURRENT, IIO_CURRENT),
	MP2629_ADC_CHAN(INPUT_CURRENT, IIO_CURRENT)
पूर्ण;

अटल काष्ठा iio_map mp2629_adc_maps[] = अणु
	MP2629_MAP(BATT_VOLT, "batt-volt"),
	MP2629_MAP(SYSTEM_VOLT, "system-volt"),
	MP2629_MAP(INPUT_VOLT, "input-volt"),
	MP2629_MAP(BATT_CURRENT, "batt-current"),
	MP2629_MAP(INPUT_CURRENT, "input-current")
पूर्ण;

अटल पूर्णांक mp2629_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			काष्ठा iio_chan_spec स्थिर *chan,
			पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा mp2629_adc *info = iio_priv(indio_dev);
	अचिन्हित पूर्णांक rval;
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = regmap_पढ़ो(info->regmap, chan->address, &rval);
		अगर (ret)
			वापस ret;

		अगर (chan->address == MP2629_INPUT_VOLT)
			rval &= GENMASK(6, 0);
		*val = rval;
		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->channel) अणु
		हाल MP2629_BATT_VOLT:
		हाल MP2629_SYSTEM_VOLT:
			*val = 20;
			वापस IIO_VAL_INT;

		हाल MP2629_INPUT_VOLT:
			*val = 60;
			वापस IIO_VAL_INT;

		हाल MP2629_BATT_CURRENT:
			*val = 175;
			*val2 = 10;
			वापस IIO_VAL_FRACTIONAL;

		हाल MP2629_INPUT_CURRENT:
			*val = 133;
			*val2 = 10;
			वापस IIO_VAL_FRACTIONAL;

		शेष:
			वापस -EINVAL;
		पूर्ण

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info mp2629_adc_info = अणु
	.पढ़ो_raw = &mp2629_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक mp2629_adc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mp2629_data *ddata = dev_get_drvdata(dev->parent);
	काष्ठा mp2629_adc *info;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*info));
	अगर (!indio_dev)
		वापस -ENOMEM;

	info = iio_priv(indio_dev);
	info->regmap = ddata->regmap;
	info->dev = dev;
	platक्रमm_set_drvdata(pdev, indio_dev);

	ret = regmap_update_bits(info->regmap, MP2629_REG_ADC_CTRL,
				MP2629_ADC_START | MP2629_ADC_CONTINUOUS,
				MP2629_ADC_START | MP2629_ADC_CONTINUOUS);
	अगर (ret) अणु
		dev_err(dev, "adc enable fail: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = iio_map_array_रेजिस्टर(indio_dev, mp2629_adc_maps);
	अगर (ret) अणु
		dev_err(dev, "IIO maps register fail: %d\n", ret);
		जाओ fail_disable;
	पूर्ण

	indio_dev->name = "mp2629-adc";
	indio_dev->dev.parent = dev;
	indio_dev->channels = mp2629_channels;
	indio_dev->num_channels = ARRAY_SIZE(mp2629_channels);
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &mp2629_adc_info;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(dev, "IIO device register fail: %d\n", ret);
		जाओ fail_map_unरेजिस्टर;
	पूर्ण

	वापस 0;

fail_map_unरेजिस्टर:
	iio_map_array_unरेजिस्टर(indio_dev);

fail_disable:
	regmap_update_bits(info->regmap, MP2629_REG_ADC_CTRL,
					 MP2629_ADC_CONTINUOUS, 0);
	regmap_update_bits(info->regmap, MP2629_REG_ADC_CTRL,
					 MP2629_ADC_START, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक mp2629_adc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा mp2629_adc *info = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	iio_map_array_unरेजिस्टर(indio_dev);

	regmap_update_bits(info->regmap, MP2629_REG_ADC_CTRL,
					 MP2629_ADC_CONTINUOUS, 0);
	regmap_update_bits(info->regmap, MP2629_REG_ADC_CTRL,
					 MP2629_ADC_START, 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mp2629_adc_of_match[] = अणु
	अणु .compatible = "mps,mp2629_adc"पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mp2629_adc_of_match);

अटल काष्ठा platक्रमm_driver mp2629_adc_driver = अणु
	.driver = अणु
		.name = "mp2629_adc",
		.of_match_table = mp2629_adc_of_match,
	पूर्ण,
	.probe		= mp2629_adc_probe,
	.हटाओ		= mp2629_adc_हटाओ,
पूर्ण;
module_platक्रमm_driver(mp2629_adc_driver);

MODULE_AUTHOR("Saravanan Sekar <sravanhome@gmail.com>");
MODULE_DESCRIPTION("MP2629 ADC driver");
MODULE_LICENSE("GPL");
