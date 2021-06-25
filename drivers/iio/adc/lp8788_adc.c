<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI LP8788 MFD - ADC driver
 *
 * Copyright 2012 Texas Instruments
 *
 * Author: Milo(Woogyom) Kim <milo.kim@ti.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/driver.h>
#समावेश <linux/iio/machine.h>
#समावेश <linux/mfd/lp8788.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

/* रेजिस्टर address */
#घोषणा LP8788_ADC_CONF			0x60
#घोषणा LP8788_ADC_RAW			0x61
#घोषणा LP8788_ADC_DONE			0x63

#घोषणा ADC_CONV_START			1

काष्ठा lp8788_adc अणु
	काष्ठा lp8788 *lp;
	काष्ठा iio_map *map;
	काष्ठा mutex lock;
पूर्ण;

अटल स्थिर पूर्णांक lp8788_scale[LPADC_MAX] = अणु
	[LPADC_VBATT_5P5] = 1343101,
	[LPADC_VIN_CHG]   = 3052503,
	[LPADC_IBATT]     = 610500,
	[LPADC_IC_TEMP]   = 61050,
	[LPADC_VBATT_6P0] = 1465201,
	[LPADC_VBATT_5P0] = 1221001,
	[LPADC_ADC1]      = 610500,
	[LPADC_ADC2]      = 610500,
	[LPADC_VDD]       = 1025641,
	[LPADC_VCOIN]     = 757020,
	[LPADC_ADC3]      = 610500,
	[LPADC_ADC4]      = 610500,
पूर्ण;

अटल पूर्णांक lp8788_get_adc_result(काष्ठा lp8788_adc *adc, क्रमागत lp8788_adc_id id,
				पूर्णांक *val)
अणु
	अचिन्हित पूर्णांक msb;
	अचिन्हित पूर्णांक lsb;
	अचिन्हित पूर्णांक result;
	u8 data;
	u8 rawdata[2];
	पूर्णांक size = ARRAY_SIZE(rawdata);
	पूर्णांक retry = 5;
	पूर्णांक ret;

	data = (id << 1) | ADC_CONV_START;
	ret = lp8788_ग_लिखो_byte(adc->lp, LP8788_ADC_CONF, data);
	अगर (ret)
		जाओ err_io;

	/* retry until adc conversion is करोne */
	data = 0;
	जबतक (retry--) अणु
		usleep_range(100, 200);

		ret = lp8788_पढ़ो_byte(adc->lp, LP8788_ADC_DONE, &data);
		अगर (ret)
			जाओ err_io;

		/* conversion करोne */
		अगर (data)
			अवरोध;
	पूर्ण

	ret = lp8788_पढ़ो_multi_bytes(adc->lp, LP8788_ADC_RAW, rawdata, size);
	अगर (ret)
		जाओ err_io;

	msb = (rawdata[0] << 4) & 0x00000ff0;
	lsb = (rawdata[1] >> 4) & 0x0000000f;
	result = msb | lsb;
	*val = result;

	वापस 0;

err_io:
	वापस ret;
पूर्ण

अटल पूर्णांक lp8788_adc_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			काष्ठा iio_chan_spec स्थिर *chan,
			पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा lp8788_adc *adc = iio_priv(indio_dev);
	क्रमागत lp8788_adc_id id = chan->channel;
	पूर्णांक ret;

	mutex_lock(&adc->lock);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = lp8788_get_adc_result(adc, id, val) ? -EIO : IIO_VAL_INT;
		अवरोध;
	हाल IIO_CHAN_INFO_SCALE:
		*val = lp8788_scale[id] / 1000000;
		*val2 = lp8788_scale[id] % 1000000;
		ret = IIO_VAL_INT_PLUS_MICRO;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	mutex_unlock(&adc->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info lp8788_adc_info = अणु
	.पढ़ो_raw = &lp8788_adc_पढ़ो_raw,
पूर्ण;

#घोषणा LP8788_CHAN(_id, _type) अणु				\
		.type = _type,					\
		.indexed = 1,					\
		.channel = LPADC_##_id,				\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |	\
			BIT(IIO_CHAN_INFO_SCALE),		\
		.datasheet_name = #_id,				\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec lp8788_adc_channels[] = अणु
	[LPADC_VBATT_5P5] = LP8788_CHAN(VBATT_5P5, IIO_VOLTAGE),
	[LPADC_VIN_CHG]   = LP8788_CHAN(VIN_CHG, IIO_VOLTAGE),
	[LPADC_IBATT]     = LP8788_CHAN(IBATT, IIO_CURRENT),
	[LPADC_IC_TEMP]   = LP8788_CHAN(IC_TEMP, IIO_TEMP),
	[LPADC_VBATT_6P0] = LP8788_CHAN(VBATT_6P0, IIO_VOLTAGE),
	[LPADC_VBATT_5P0] = LP8788_CHAN(VBATT_5P0, IIO_VOLTAGE),
	[LPADC_ADC1]      = LP8788_CHAN(ADC1, IIO_VOLTAGE),
	[LPADC_ADC2]      = LP8788_CHAN(ADC2, IIO_VOLTAGE),
	[LPADC_VDD]       = LP8788_CHAN(VDD, IIO_VOLTAGE),
	[LPADC_VCOIN]     = LP8788_CHAN(VCOIN, IIO_VOLTAGE),
	[LPADC_ADC3]      = LP8788_CHAN(ADC3, IIO_VOLTAGE),
	[LPADC_ADC4]      = LP8788_CHAN(ADC4, IIO_VOLTAGE),
पूर्ण;

/* शेष maps used by iio consumer (lp8788-अक्षरger driver) */
अटल काष्ठा iio_map lp8788_शेष_iio_maps[] = अणु
	अणु
		.consumer_dev_name = "lp8788-charger",
		.consumer_channel = "lp8788_vbatt_5p0",
		.adc_channel_label = "VBATT_5P0",
	पूर्ण,
	अणु
		.consumer_dev_name = "lp8788-charger",
		.consumer_channel = "lp8788_adc1",
		.adc_channel_label = "ADC1",
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक lp8788_iio_map_रेजिस्टर(काष्ठा iio_dev *indio_dev,
				काष्ठा lp8788_platक्रमm_data *pdata,
				काष्ठा lp8788_adc *adc)
अणु
	काष्ठा iio_map *map;
	पूर्णांक ret;

	map = (!pdata || !pdata->adc_pdata) ?
		lp8788_शेष_iio_maps : pdata->adc_pdata;

	ret = iio_map_array_रेजिस्टर(indio_dev, map);
	अगर (ret) अणु
		dev_err(&indio_dev->dev, "iio map err: %d\n", ret);
		वापस ret;
	पूर्ण

	adc->map = map;
	वापस 0;
पूर्ण

अटल पूर्णांक lp8788_adc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lp8788 *lp = dev_get_drvdata(pdev->dev.parent);
	काष्ठा iio_dev *indio_dev;
	काष्ठा lp8788_adc *adc;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&pdev->dev, माप(*adc));
	अगर (!indio_dev)
		वापस -ENOMEM;

	adc = iio_priv(indio_dev);
	adc->lp = lp;
	platक्रमm_set_drvdata(pdev, indio_dev);

	ret = lp8788_iio_map_रेजिस्टर(indio_dev, lp->pdata, adc);
	अगर (ret)
		वापस ret;

	mutex_init(&adc->lock);

	indio_dev->name = pdev->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &lp8788_adc_info;
	indio_dev->channels = lp8788_adc_channels;
	indio_dev->num_channels = ARRAY_SIZE(lp8788_adc_channels);

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "iio dev register err: %d\n", ret);
		जाओ err_iio_device;
	पूर्ण

	वापस 0;

err_iio_device:
	iio_map_array_unरेजिस्टर(indio_dev);
	वापस ret;
पूर्ण

अटल पूर्णांक lp8788_adc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);

	iio_device_unरेजिस्टर(indio_dev);
	iio_map_array_unरेजिस्टर(indio_dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver lp8788_adc_driver = अणु
	.probe = lp8788_adc_probe,
	.हटाओ = lp8788_adc_हटाओ,
	.driver = अणु
		.name = LP8788_DEV_ADC,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(lp8788_adc_driver);

MODULE_DESCRIPTION("Texas Instruments LP8788 ADC Driver");
MODULE_AUTHOR("Milo Kim");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:lp8788-adc");
