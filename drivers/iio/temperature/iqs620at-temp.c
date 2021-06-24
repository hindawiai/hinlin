<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Azoteq IQS620AT Temperature Sensor
 *
 * Copyright (C) 2019 Jeff LaBundy <jeff@labundy.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/iqs62x.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#घोषणा IQS620_TEMP_UI_OUT			0x1A

#घोषणा IQS620_TEMP_SCALE			1000
#घोषणा IQS620_TEMP_OFFSET			(-100)

अटल पूर्णांक iqs620_temp_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *chan,
				पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा iqs62x_core *iqs62x = iio_device_get_drvdata(indio_dev);
	पूर्णांक ret;
	__le16 val_buf;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = regmap_raw_पढ़ो(iqs62x->regmap, IQS620_TEMP_UI_OUT,
				      &val_buf, माप(val_buf));
		अगर (ret)
			वापस ret;

		*val = le16_to_cpu(val_buf);
		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		*val = IQS620_TEMP_SCALE;
		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_OFFSET:
		*val = IQS620_TEMP_OFFSET;
		वापस IIO_VAL_INT;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info iqs620_temp_info = अणु
	.पढ़ो_raw = &iqs620_temp_पढ़ो_raw,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec iqs620_temp_channels[] = अणु
	अणु
		.type = IIO_TEMP,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE) |
				      BIT(IIO_CHAN_INFO_OFFSET),
	पूर्ण,
पूर्ण;

अटल पूर्णांक iqs620_temp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iqs62x_core *iqs62x = dev_get_drvdata(pdev->dev.parent);
	काष्ठा iio_dev *indio_dev;

	indio_dev = devm_iio_device_alloc(&pdev->dev, 0);
	अगर (!indio_dev)
		वापस -ENOMEM;

	iio_device_set_drvdata(indio_dev, iqs62x);

	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = iqs620_temp_channels;
	indio_dev->num_channels = ARRAY_SIZE(iqs620_temp_channels);
	indio_dev->name = iqs62x->dev_desc->dev_name;
	indio_dev->info = &iqs620_temp_info;

	वापस devm_iio_device_रेजिस्टर(&pdev->dev, indio_dev);
पूर्ण

अटल काष्ठा platक्रमm_driver iqs620_temp_platक्रमm_driver = अणु
	.driver = अणु
		.name = "iqs620at-temp",
	पूर्ण,
	.probe = iqs620_temp_probe,
पूर्ण;
module_platक्रमm_driver(iqs620_temp_platक्रमm_driver);

MODULE_AUTHOR("Jeff LaBundy <jeff@labundy.com>");
MODULE_DESCRIPTION("Azoteq IQS620AT Temperature Sensor");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:iqs620at-temp");
